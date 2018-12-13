#include "Bbu.h"

Define_Module(Bbu);

void Bbu::initialize()
{
    beep = new cMessage();
    working = false;
}

void Bbu::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        buffer.erase(buffer.begin());
        for(int i=0; i<buffer.size(); i++){
            EV<<"Buffer["<<i<<"]: "<<buffer[i]->getId()<<endl;
        }

        // BBU checks if there are other packet to be transmitted
        if(buffer.size() == 0)
            working = false;
        else{
            beginTransmission(buffer[0]);
        }
    }else{
        // new packet from AS
        cranMessage *pkt = check_and_cast<cranMessage*>(msg);
        buffer.push_back(pkt);
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
