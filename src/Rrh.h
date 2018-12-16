/*
 * Rrh.h
 *
 *  Created on: 06 dic 2018
 *      Author: Gerardo
 */

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
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void startDecompression(cranMessage *pkt);
};

#endif /* RRH_H_ */
