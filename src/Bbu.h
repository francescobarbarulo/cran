/*
 * Bbu.h
 *
 *  Created on: 06 dic 2018
 *      Author: Gerardo
 */

#ifndef BBU_H_
#define BBU_H_

#include <omnetpp.h>
#include <vector>
#include "cranMessage.h"

using namespace omnetpp;

class Bbu : public cSimpleModule
{
  private:
    cMessage *beep;
    std::vector<cranMessage*> buffer;
    bool working;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void beginTransmission(cranMessage *pkt);
};

#endif /* BBU_H_ */
