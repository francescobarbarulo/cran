/*
 * Rrh.h
 *
 *  Created on: 06 dic 2018
 *      Author: Gerardo
 */

#ifndef RRH_H_
#define RRH_H_

#include <omnetpp.h>

using namespace omnetpp;

class Rrh : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* RRH_H_ */
