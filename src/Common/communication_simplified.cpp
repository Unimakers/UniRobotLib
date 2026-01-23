#include <Common/communication_simplified.hpp>
#include <SoftwareSerial.h>
void CommPrincipale::setup(int RxCommLidar, int TxCommLidar, int RxCommMoteur, int TxCommMoteur)
{
    this->lidarComm.begin(38400, SWSERIAL_8N1, RxCommLidar, TxCommLidar);
    this->motorComm.begin(38400, SWSERIAL_8N1, RxCommMoteur, TxCommMoteur);
}
bool CommPrincipale::getLidarState()
{
    return this->lidarState;
}
void CommPrincipale::sendActionToMotor(CommAction action, std::string arguments)
{
    this->motorToSend = "";
    if (this->isSendingToMotor)
    {
        this->motorToSend = "$";
    }
    this->motorToSend += (char)action;
    this->motorToSend += arguments;
}
bool CommPrincipale::getMotorState()
{
    return this->motorState;
}
void CommPrincipale::loop()
{
    if (this->lidarComm && this->lidarComm.available())
        this->lidarState = (int)(((char)this->lidarComm.read()) - '0') == 1;
    if (this->motorComm && this->motorComm.available())
        this->motorState = (int)(((char)this->motorComm.read()) - '0') == 1;
    if (this->isSendingToMotor)
    {
        char toSendCurrent;
        if (this->motorToSendIndex >= this->motorToSend.length())
        {
            toSendCurrent = '@';
            this->isSendingToMotor = false;
            this->motorToSend = "";
            this->motorToSendIndex = 0;
        }
        else
        {
            toSendCurrent = this->motorToSend[this->motorToSendIndex];
        }
        this->motorComm.write(toSendCurrent);
    }
}

//// CommESCLAVE

void CommEsclave::setup(int rxComm, int txComm)
{
    this->mainComm.begin(38400, SWSERIAL_8N1, rxComm, txComm);
}
void CommEsclave::sendState(bool value)
{
    this->stateToSend = value;
}
void CommEsclave::loop()
{
    if (this->mainComm.available())
    {
        this->finishedReception = false;
        char receiptCurrent = (char)this->mainComm.read();
        if (receiptCurrent == '$')
        {
            this->currentReception = "";
        }
        else if (receiptCurrent == '@')
        {
            this->receivedAction = (CommAction)currentReception[0];
            this->receivedArguments = currentReception.substr(1);
            this->currentReception = "";
            this->finishedReception = true;
        }
        else
        {
            this->currentReception+=receiptCurrent;
        }
    }
    this->mainComm.write(this->stateToSend ? '1' : '0');
}
CommAction CommEsclave::getAction(){
    if(this->finishedReception)return this->receivedAction;
    return CommAction::NO_NEW_DATA;
}

std::string CommEsclave::getArgs(){
    if(this->finishedReception)return this->receivedArguments;
    return "";
}