/*
 * As.h
 *
 *  Created on: 06 dic 2018
 *      Author: Gerardo
 */

#ifndef AS_H_
#define AS_H_

#include <omnetpp.h>

using namespace omnetpp;

class As : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* AS_H_ */
