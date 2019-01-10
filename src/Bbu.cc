#include "Bbu.h"
#include <fstream>

Define_Module(Bbu);


void Bbu::initialize()
{
    this->beep = new cMessage();
    this->idle = true;

    // signals registration
    this->responseTimeSignal = registerSignal("responseTime");
    this->waitingTimeSignal = registerSignal("waitingTime");
    this->bbuJobsSignal = registerSignal("bbuJobs");
}

void Bbu::handleMessage(cMessage *msg)
{
    cranMessage *pkt;

    if(msg->isSelfMessage()){
        pkt = this->buffer.front();
        this->buffer.pop();
        send(pkt, "out", pkt->getDest());

        // !! response time expired !!
        emit(this->responseTimeSignal, simTime() - pkt->getBbuArrivalTime());

        // BBU checks if there are other packet to be transmitted
        if(this->buffer.empty())
            this->idle = true;
        else{
            this->beginTransmission();
        }
    } else {
        // new packet from AS
        emit(this->bbuJobsSignal, (long)this->buffer.size());

        pkt = check_and_cast<cranMessage*>(msg);
        this->buffer.push(pkt);
        pkt->setBbuArrivalTime();

        if(this->idle){
            // Bbu is idle so it can process the packet immediately
            this->idle = false;
            this->beginTransmission();
        }
    }
}

void Bbu::beginTransmission(){
    // extract the first pkt from the buffer
    cranMessage *pkt = this->buffer.front();

    // !! waiting time expired !!
    emit(this->waitingTimeSignal, simTime() - pkt->getBbuArrivalTime());

    // case compression enabled
    if (par("enableCompression").boolValue())
        pkt->compressPkt(par("compressionPercentage").intValue());

    // wait for transmission
    simtime_t transmissionTime = pkt->getSize()/par("speed").doubleValue();
    EV<<"[BBU] TransmissionTime: "<<transmissionTime<< " - of: "<<pkt->getId()<<endl;
    scheduleAt(simTime() + transmissionTime, this->beep);
}

void Bbu::finish(){
    while(!this->buffer.empty()){
        cancelAndDelete(this->buffer.front());
        this->buffer.pop();
    }

    cancelEvent(this->beep);
    cancelAndDelete(this->beep);
}
