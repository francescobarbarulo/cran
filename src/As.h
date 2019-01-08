#ifndef AS_H_
#define AS_H_

#include <omnetpp.h>
#include "cranMessage.h"

using namespace omnetpp;

class As : public cSimpleModule
{
  private:
    cMessage *beep;
    cranMessage *pkt;
    int counter;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    int getSizefromDistribution();
};

#endif /* AS_H_ */
