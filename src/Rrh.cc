#include "Rrh.h"
#include <fstream>

Define_Module(Rrh);

void Rrh::initialize()
{
    working = false;
    beep = new cMessage();
    // signal registration
    delaySignal = registerSignal("delay");
    responseTimeSignal = registerSignal("responseTime");
    waitingTimeSignal = registerSignal("waitingTime");
    queuedJobsSignal = registerSignal("queuedJobs");
}

void Rrh::handleMessage(cMessage *msg)
{
    cranMessage *pkt;
    std::ofstream file;

    if(msg->isSelfMessage()){
          // previous pkt is decompressed and it is removed from the buffer
          cranMessage *prev_pkt = buffer.front();
          buffer.pop();

          file.open("system-delay.csv", std::ofstream::app);

          // !! response time expired !!
          EV << "end-to-end delay : " << simTime() - prev_pkt->getCreationTime() << endl;
          emit(responseTimeSignal, simTime() - prev_pkt->getRrhArrivalTime());
          emit(delaySignal, (simTime() - prev_pkt->getCreationTime()));

          file << simTime() << "," << simTime() - prev_pkt->getCreationTime() << endl;
          file.close();

          // the packet is consumed
          delete(prev_pkt);
          // RRH checks if there are other packet to be transmitted
          if(buffer.empty())
              working = false;
          else{
              startDecompression();
          }
      }else{
          // new packet from Bbu
          pkt = check_and_cast<cranMessage*>(msg);
          buffer.push(pkt);
          pkt->setRrhArrivalTime();

          emit(queuedJobsSignal, buffer.size());

          if(!working){
              // RRH is idle so it can process the packet immediately
              working = true;
              startDecompression();
          }
      }
}

void Rrh::startDecompression(){
    cranMessage *pkt = buffer.front();

    // !! waiting time expired !!
    emit(waitingTimeSignal, simTime() - pkt->getRrhArrivalTime());

    // case compression enabled
    if (pkt->isCompressed()){
        simtime_t decompressionTime = par("compressionPercentage").intValue()*0.05;
        scheduleAt(simTime() + decompressionTime , beep);
        EV<<"[RRH] decompressionTime: "<<decompressionTime<<endl;
    } else {
        scheduleAt(simTime(), beep);
    }


}
