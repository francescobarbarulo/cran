/*
 * Bbu.h
 *
 *  Created on: 06 dic 2018
 *      Author: Gerardo
 */

#ifndef BBU_H_
#define BBU_H_

#include <omnetpp.h>

using namespace omnetpp;

class Bbu : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* BBU_H_ */
