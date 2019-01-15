#include "Bbu.h"
#include <fstream>

Define_Module(Bbu);


void Bbu::initialize()
{
    this->beep = new cMessage();
    this->server = NULL;

    // signals registration
    this->responseTimeSignal = registerSignal("responseTime");
    this->waitingTimeSignal = registerSignal("waitingTime");
    this->bbuJobsSignal = registerSignal("bbuJobs");
}

void Bbu::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        // !! response time expired !!
        emit(this->responseTimeSignal, simTime() - this->server->getBbuArrivalTime());
        send(this->server, "out", this->server->getDest());

        // BBU checks if there are other packet to be transmitted
        if(this->buffer.empty())
            this->server = NULL;
        else {
            this->server = this->buffer.front();
            this->buffer.pop();
            this->beginTransmission();
        }
    } else {
        // new packet from AS
        EV << "jobs in Bbu: " << (long)this->buffer.size() + (int)(bool)this->server << endl;
        emit(this->bbuJobsSignal, (long)this->buffer.size() + (int)(bool)this->server);

        cranMessage *pkt = check_and_cast<cranMessage*>(msg);
        pkt->setBbuArrivalTime();

        if(!this->server){
            // Bbu is idle so it can process the packet immediately
            this->server = pkt;
            this->beginTransmission();
        } else {
            this->buffer.push(pkt);
        }
    }
}

void Bbu::beginTransmission(){
    // !! waiting time expired !!
    emit(this->waitingTimeSignal, simTime() - this->server->getBbuArrivalTime());

    // case compression enabled
    if (par("enableCompression").boolValue())
        this->server->compressPkt(par("compressionPercentage").intValue());

    // wait for transmission
    simtime_t transmissionTime = this->server->getSize()/par("speed").doubleValue();
    EV<<"[BBU] TransmissionTime: "<<transmissionTime<< " - of: "<<this->server->getId()<<endl;
    scheduleAt(simTime() + transmissionTime, this->beep);
}

void Bbu::finish(){
    while(!this->buffer.empty()){
        cancelAndDelete(this->buffer.front());
        this->buffer.pop();
    }

    if (this->server)
        cancelAndDelete(server);

    cancelEvent(this->beep);
    cancelAndDelete(this->beep);
}
