#ifndef RRH_H_
#define RRH_H_

#include <omnetpp.h>
#include <queue>
#include "cranMessage.h"

using namespace omnetpp;

class Rrh : public cSimpleModule
{
  private:
    cMessage *beep;
    std::queue<cranMessage*> buffer;
    bool idle;
    // signals

    simsignal_t responseTimeSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t rrhJobsSignal;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    simtime_t getDecompressionTime(cranMessage *pkt);
    void startDecompression();
    void recordStatisticsOnFile(cranMessage *pkt);
};

#endif /* RRH_H_ */
