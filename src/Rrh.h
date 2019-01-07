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
    bool working;
    // signals
    simsignal_t delaySignal;
    simsignal_t responseTimeSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t queuedJobsSignal;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void startDecompression();
};

#endif /* RRH_H_ */
