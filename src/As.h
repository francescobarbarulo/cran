/*
 * As.h
 *
 *  Created on: 06 dic 2018
 *      Author: Gerardo
 */

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
};

#endif /* AS_H_ */
