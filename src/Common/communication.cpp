#include <Common/communication.hpp>
#if THIS_LIB_IS_ENABLED==1
CommunicationCartePrincipale::CommunicationCartePrincipale()
{
}
void CommunicationCartePrincipale::_envoiSerial(int idCarte, std::string data){
    if(!(this->serialMap.count(idCarte)))return;
    if(!(this->serialMap[idCarte]))return;
    this->serialMap[idCarte].println(data.c_str());
}
std::string CommunicationCartePrincipale::_receiptSerial(int idCarte){
    if(!(this->serialMap.count(idCarte)))return;
    if(!(this->serialMap[idCarte]))return;
    byte n = this->serialMap[idCarte].available();
    if(n!=0){
        char ch = this->serialMap[idCarte].read();
    }
}
void CommunicationCartePrincipale::envoyer(int idCarte, CommunicationData data)
{
    this->toSend[idCarte].push_back(data);
    return;
}

void CommunicationCartePrincipale::loop()
{
    /*pour réception vers buffer et routeur pourra servir à l'envoi
    du buffer d'envoi si on voit que ça prend trop de temps de le faire dans "envoyer" directement*/
    std::map<int, std::vector<CommunicationData>> toSend;
    for (auto const &sendPair : toSend)
    {
        int idCarte = sendPair.first;
        std::string toSendByCard ="";
        std::map<CommAction,int> checkPresence;
        for (auto it = sendPair.second.rbegin(); it != sendPair.second.rend(); ++it)
        {
            if(checkPresence.count((*it).action))continue;
            checkPresence[(*it).action]=1;
            toSendByCard+=CommunicationData::toString((*it));
            toSendByCard+=";";
        }
        toSendByCard+="@";
        this->_envoiSerial(idCarte,toSendByCard);
    }
    toSend.clear();
    std::map<int, std::vector<CommunicationData>> newReceivedBuffer;
    for (auto const &receivePair : receivedBuffer)
    {
        int idCarte = receivePair.first;
        std::map<CommAction,int> checkPresence;
        for (auto it = receivePair.second.rbegin(); it != receivePair.second.rend(); ++it){
            if(checkPresence.count((*it).action))continue;
            checkPresence[(*it).action]=1;
            if ((*it).persistence == COMM_PERSISTENCE::ERASE_NEXT_LOOP)
            {
                // ne rien faire, on ne le garde pas
            }
            else if ((*it).persistence == COMM_PERSISTENCE::KEEP_UNTIL_NEXT_RECEIVE)
            {
                newReceivedBuffer[idCarte].push_back((*it));
            }
        }
    }
    receivedBuffer = newReceivedBuffer;
    for (int idCarte = static_cast<int>(IdCarte::CARTE_MOTEUR); idCarte <= static_cast<int>(IdCarte::CARTE_EXTENSION_3); ++idCarte)
    {
        std::string reception = this->_receiptSerial(idCarte); // TODO
        CommunicationData receivedData = CommunicationData::fromString(reception);
        if (receivedData.action != CommAction::NONE)
        {
            receivedBuffer[idCarte].push_back(receivedData);
        }
    }
    // routeur();
}

/* void CommunicationCartePrincipale::routeur()
// {
}*/

CommunicationData CommunicationCartePrincipale::regarder(int idCarte)
{
    return this->receivedBuffer[idCarte].back();
}
std::vector<CommunicationData> CommunicationCartePrincipale::regarder_tout(int idCarte)
{
    return this->receivedBuffer[idCarte];
}

CommunicationCarteExtension::CommunicationCarteExtension()
{
}

void CommunicationCarteExtension::envoyer(CommunicationData data)
{
}

void CommunicationCarteExtension::loop()
{
}

CommunicationData CommunicationCarteExtension::regarder()
{
    return CommunicationData();
}
#endif