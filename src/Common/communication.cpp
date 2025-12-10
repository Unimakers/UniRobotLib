#include <Common/communication.hpp>

CommunicationCartePrincipale::CommunicationCartePrincipale()
{
}
void envoiCommunicationData(int idCarte, CommunicationData data)
{
    std::string toSend = std::to_string(static_cast<int>(data.persistence))+":"+std::to_string(static_cast<int>(data.action)) + ":" + data.argument;
    
}
CommunicationData receiptCommunicationData(int idCarte)
{
    std::string reception;
    if(reception.empty())
    {
        return commDataNone;
    }
    CommunicationData receivedData;
    if(reception.find(":") == std::string::npos)
    {
        return commDataNone;
    }
    int receivedPersistence = (std::stoi(reception.substr(0, reception.find(":"))));
    if(receivedPersistence < 0 || receivedPersistence > 1)
    {
        return commDataNone;
    }
    receivedData.persistence = static_cast<COMM_PERSISTENCE>(receivedPersistence);
    if(reception.find(":") == std::string::npos)
    {
        return commDataNone;
    }
    reception = reception.substr(reception.find(":") + 1);
    int receivedAction = (std::stoi(reception.substr(0, reception.find(":"))));
    if(receivedAction < 0 || receivedAction > 12)
    {
        return commDataNone;
    }
    receivedData.action = static_cast<CommAction>(receivedAction);
    reception = reception.substr(reception.find(":") + 1);
    if(reception.empty())
    {
        return commDataNone;
    }
    receivedData.argument = reception;
    return receivedData;
}
void CommunicationCartePrincipale::envoyer(int idCarte, CommunicationData data)
{
    envoiCommunicationData(idCarte, data);
}

void CommunicationCartePrincipale::loop()
{
    /*pour réception vers buffer et routeur pourra servir à l'envoi
    du buffer d'envoi si on voit que ça prend trop de temps de le faire dans "envoyer" directement*/
    std::map<int,std::vector<CommunicationData>> toSend;
    for(auto const& sendPair : toSend)
    {
        int idCarte = sendPair.first;
        for(auto const& data : sendPair.second)
        {
            envoiCommunicationData(idCarte, data);
        }
    }
    toSend.clear();
    std::map<int,std::vector<CommunicationData>> newReceivedBuffer;
    for(auto const& receivePair : receivedBuffer)
    {
        int idCarte = receivePair.first;
        for(auto const& data : receivePair.second)
        {
            if(data.persistence == COMM_PERSISTENCE::ERASE_NEXT_LOOP)
            {
            //ne rien faire, on ne le garde pas
            }
            else if(data.persistence == COMM_PERSISTENCE::KEEP_UNTIL_NEXT_RECEIVE)
            {
                newReceivedBuffer[idCarte].push_back(data);
            }
        }
    }
    receivedBuffer = newReceivedBuffer;
    for(int idCarte = static_cast<int>(IdCarte::CARTE_MOTEUR); idCarte <= static_cast<int>(IdCarte::CARTE_EXTENSION_3); ++idCarte)
    {
        CommunicationData receivedData = receiptCommunicationData(idCarte);
        if(receivedData.action != CommAction::NONE)
        {
            receivedBuffer[idCarte].push_back(receivedData);
        }
    }
    //routeur();
}

/* void CommunicationCartePrincipale::routeur()
// {
}*/


CommunicationData CommunicationCartePrincipale::regarder(int idCarte)
{
    return receiptCommunicationData(idCarte);
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
