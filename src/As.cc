#include "As.h"

Define_Module(As);

int As::getSizefromDistribution(){
    if(par("exponentialDistribution").boolValue())
        return (int)exponential(par("meanExponentialSize").doubleValue(), 1);

    return (int)lognormal(par("meanLognormalSize").doubleValue(), par("varianceLognormalSize").doubleValue(), 1);
}

void As::initialize()
{
    this->counter = 0;
    //new self-message to start the AS
    this->beep = new cMessage();
    scheduleAt(simTime(), this->beep);
}

void As::handleMessage(cMessage *msg)
{
    //msg is always a self-message
    int dest = intuniform(0, par("N").intValue()-1, 0);
    int size = this->getSizefromDistribution();

    // new packet creation
    this->pkt = new cranMessage(this->counter++, size, dest);
    send(this->pkt, "out");

    // waiting for the creation of next packet
    simtime_t time = exponential(par("interArrivalTime").doubleValue(), 2);
    EV<<"Send packet to "<<dest<<" with size "<<size<<". Next packet will be sent in "<<time<<endl;
    scheduleAt(simTime() + time, this->beep);
}

void As::finish(){
    cancelEvent(this->beep);
    cancelAndDelete(this->beep);
}
