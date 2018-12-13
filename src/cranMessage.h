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
    int id;

  public:
    cranMessage(int id, int s, int d, bool c);
    int getSize();
    int getDest();
    bool isCompressed();
    int getId();
    void compressPkt(double percentage);
};

#endif /* CRANMESSAGE_H_ */
