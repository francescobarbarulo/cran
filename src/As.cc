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
    if(par("expSize").boolValue())
        size = (int)exponential(par("pktSize").doubleValue());
    else
        size = (int)lognormal(par("pktSize").doubleValue(), par("varSize").doubleValue());
    pkt = new cranMessage(counter++, size, dest, par("enableCompression").boolValue());

    send(pkt, "out");
    simtime_t time = exponential(par("interArrivalTime").doubleValue())/1000;
    EV<<"Send packet to "<<dest<<" with size "<<size<<". Next packet will be sent in "<<time<<endl;
    scheduleAt(simTime() + time, beep);
}
