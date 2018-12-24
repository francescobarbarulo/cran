#include "As.h"

Define_Module(As);

void As::initialize()
{
    //new self-message to start the AS
    beep = new cMessage();
    scheduleAt(simTime(), beep);
    counter = 0;

}

void As::handleMessage(cMessage *msg)
{
    //msg is always a self-message
    int dest = intuniform(0, par("N").intValue()-1);
    int size;

    if(par("exponentialDistribution").boolValue())
        size = (int)exponential(par("meanExponentialSize").doubleValue());
    else
        size = (int)lognormal(par("meanLognormalSize").doubleValue(), par("varianceLognormalSize").doubleValue());

    pkt = new cranMessage(counter++, size, dest, par("enableCompression").boolValue());

    send(pkt, "out");
    //simtime_t time = par("interArrivalTime").doubleValue();
    simtime_t time = exponential(par("interArrivalTime").doubleValue());
    EV<<"Send packet to "<<dest<<" with size "<<size<<". Next packet will be sent in "<<time<<endl;
    scheduleAt(simTime() + time, beep);
}
