#include "Bbu.h"

Define_Module(Bbu);

void Bbu::initialize()
{
    beep = new cMessage();
    working = false;

    responseTimeSignal = registerSignal("responseTime");
    waitingTimeSignal = registerSignal("waitingTime");
    queuedJobsSignal = registerSignal("queuedJobs");
}

void Bbu::handleMessage(cMessage *msg)
{
    cranMessage *pkt;

    if(msg->isSelfMessage()){
        pkt = buffer.front();
        buffer.pop();
        send(pkt, "out", pkt->getDest());

        // !! response time expired !!
        emit(responseTimeSignal, simTime() - pkt->getBbuArrivalTime());

        // BBU checks if there are other packet to be transmitted
        if(buffer.empty())
            working = false;
        else{
            beginTransmission();
        }
    }else{
        // new packet from AS
        pkt = check_and_cast<cranMessage*>(msg);
        buffer.push(pkt);
        pkt->setBbuArrivalTime();

        emit(queuedJobsSignal, buffer.size());

        if(!working){
            // Bbu is idle so it can process the packet immediately
            working = true;
            beginTransmission();
        }
    }
}

void Bbu::beginTransmission(){
    // extract the first pkt from the buffer
    cranMessage *pkt = buffer.front();

    // !! waiting time expired !!
    emit(waitingTimeSignal, simTime() - pkt->getBbuArrivalTime());

    // case compression enabled
    if (par("enableCompression").boolValue())
        pkt->compressPkt(par("compressionPercentage").intValue());

    // wait for transmission
    simtime_t transmissionTime = pkt->getSize()/par("speed").doubleValue();
    EV<<"[BBU] TransmissionTime: "<<transmissionTime<< " - of: "<<pkt->getId()<<endl;
    scheduleAt(simTime() + transmissionTime, beep);
}
