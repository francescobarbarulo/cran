#include "Bbu.h"

Define_Module(Bbu);

void Bbu::initialize()
{
    beep = new cMessage();
    working = false;
}

void Bbu::handleMessage(cMessage *msg)
{
    cranMessage *pkt;

    if(msg->isSelfMessage()){
        // previous transmission in ended and it is removed from the buffer
        buffer.pop();
        /*
        for(int i = 0; i < buffer.size(); i++){
            EV<<"Buffer["<<i<<"]: "<<buffer[i]->getId()<<endl;
        }*/

        // BBU checks if there are other packet to be transmitted
        if(buffer.empty())
            working = false;
        else{
            pkt = buffer.front();
            beginTransmission(pkt);
        }
    }else{
        // new packet from AS
        pkt = check_and_cast<cranMessage*>(msg);
        buffer.push(pkt);

        if(!working){
            // Bbu is idle so it can process the packet immediately
            working = true;
            beginTransmission(pkt);
        }
    }


}

void Bbu::beginTransmission(cranMessage *pkt){
    // case compression enabled
    if (par("enableCompression").boolValue())
        pkt->compressPkt(par("compressionPercentage").doubleValue());

    send(pkt, "out", pkt->getDest());
    simtime_t transmissionTime = pkt->getSize()/par("speed").doubleValue();
    EV<<"[BBU] TransmissionTime: "<<transmissionTime<< " - of: "<<pkt->getId()<<endl;
    scheduleAt(simTime() + transmissionTime, beep);
}
