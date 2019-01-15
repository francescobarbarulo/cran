#ifndef BBU_H_
#define BBU_H_

#include <omnetpp.h>
#include <queue>
#include "cranMessage.h"

using namespace omnetpp;

class Bbu : public cSimpleModule
{
  private:
    // self-message
    cMessage *beep;

    // service center
    std::queue<cranMessage*> buffer;
    cranMessage *server;

    // signals
    simsignal_t responseTimeSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t bbuJobsSignal;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    void beginTransmission();
};

#endif /* BBU_H_ */
