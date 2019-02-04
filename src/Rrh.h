#ifndef RRH_H_
#define RRH_H_

#include <omnetpp.h>
#include <queue>
#include "cranMessage.h"

using namespace omnetpp;

class Rrh : public cSimpleModule
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
    simsignal_t rrhJobsSignal;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    void startDecompression();
};

#endif /* RRH_H_ */
