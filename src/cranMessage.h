#ifndef CRANMESSAGE_H_
#define CRANMESSAGE_H_

#include <omnetpp.h>

using namespace omnetpp;

class cranMessage : public cMessage
{

  private:
    int size;
    int dest;
    bool compression;
  public:
    cranMessage(int s, int d, bool c);
    int getSize();
    int getDest();
    bool isCompressed();
    void compressPkt(double percentage);
};

#endif /* CRANMESSAGE_H_ */
