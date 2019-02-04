#ifndef CRANMESSAGE_H_
#define CRANMESSAGE_H_

#include <omnetpp.h>
#include <math.h>

using namespace omnetpp;

class cranMessage : public cMessage
{

  private:
    int id;
    int size;
    int dest;
    int compression;
    struct {
        simtime_t created_at;
        simtime_t bbu_arrival;
        simtime_t rrh_arrival;
    } times;

  public:
    cranMessage(int id, int s, int d);
    // setter
    void setBbuArrivalTime();
    void setRrhArrivalTime();
    // getter
    int getSize();
    int getDest();
    int getCompression();
    int getId();
    simtime_t getCreationTime();
    simtime_t getBbuArrivalTime();
    simtime_t getRrhArrivalTime();
    // features
    void compressPkt(int percentage);
};

#endif /* CRANMESSAGE_H_ */
