#include "Rrh.h"
#include <fstream>

Define_Module(Rrh);

simtime_t Rrh::getDecompressionTime(cranMessage *pkt){
    // Compression time does not depend on packet size
    if (!par("dependentDecompressionTime").boolValue())
        return par("compressionPercentage").intValue()*0.05;
    // Compression time does depend on packet size
    return pkt->getSize()/par("decompressionSpeed").doubleValue();
}

void Rrh::initialize()
{
    this->idle = true;
    this->beep = new cMessage();

    // signals registration
    this->delaySignal = registerSignal("delay");
    this->responseTimeSignal = registerSignal("responseTime");
    this->waitingTimeSignal = registerSignal("waitingTime");
    this->rrhJobsSignal = registerSignal("rrhJobs");
}

void Rrh::handleMessage(cMessage *msg)
{
    cranMessage *pkt;
    //std::ofstream file;

    if(msg->isSelfMessage()){
          // previous pkt is decompressed and it is removed from the buffer
          cranMessage *prev_pkt = this->buffer.front();
          this->buffer.pop();

          //file.open("system-delay.csv", std::ofstream::app);

          // !! response time expired !!
          EV << "end-to-end delay : " << simTime() - prev_pkt->getCreationTime() << endl;
          emit(this->responseTimeSignal, simTime() - prev_pkt->getRrhArrivalTime());
          emit(this->delaySignal, (simTime() - prev_pkt->getCreationTime()));

          //file << simTime() << ";" << simTime() - prev_pkt->getCreationTime() << endl;
          //file.close();

          // the packet is consumed
          delete prev_pkt;
          // RRH checks if there are other packet to be transmitted
          if(this->buffer.empty())
              this->idle = true;
          else{
              this->startDecompression();
          }
      }else{
          // new packet from Bbu
          emit(this->rrhJobsSignal, (long)buffer.size());

          pkt = check_and_cast<cranMessage*>(msg);
          this->buffer.push(pkt);
          pkt->setRrhArrivalTime();

          if(this->idle){
              // RRH is idle so it can process the packet immediately
              this->idle = false;
              this->startDecompression();
          }
      }
}

void Rrh::startDecompression(){
    cranMessage *pkt = this->buffer.front();

    // !! waiting time expired !!
    emit(this->waitingTimeSignal, simTime() - pkt->getRrhArrivalTime());

    // case compression enabled
    if ((bool)pkt->getCompression()){
        simtime_t decompressionTime = this->getDecompressionTime(pkt);
        scheduleAt(simTime() + decompressionTime , this->beep);
        EV<<"[RRH] decompressionTime: "<< decompressionTime <<endl;
    } else {
        scheduleAt(simTime(), this->beep);
    }
}

void Rrh::finish(){
    while(!this->buffer.empty()){
        cancelAndDelete(this->buffer.front());
        this->buffer.pop();
    }

    cancelEvent(this->beep);
    cancelAndDelete(this->beep);
}
