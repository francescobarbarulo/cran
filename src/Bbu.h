#ifndef BBU_H_
#define BBU_H_

#include <omnetpp.h>
#include <queue>
#include "cranMessage.h"

using namespace omnetpp;

class Bbu : public cSimpleModule
{
  private:
    cMessage *beep;
    std::queue<cranMessage*> buffer;
    bool working;
    // signals
    simsignal_t responseTimeSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t queuedJobsSignal;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void beginTransmission();
};

#endif /* BBU_H_ */
