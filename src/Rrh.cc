#include "Rrh.h"
#include <fstream>

Define_Module(Rrh);

void Rrh::recordStatisticsOnFile(cranMessage *pkt){
    std::ofstream file;
    file.open("delay.csv", std::ofstream::app);
    file << simTime() << ";" << simTime() - pkt->getCreationTime() << endl;
    file.close();
}

simtime_t Rrh::getDecompressionTime(cranMessage *pkt){
    // Compression time does not depend on packet size
    if (!par("dependentDecompressionTime").boolValue())
        return pkt->getCompression()*par("timePerCompressionUnit").doubleValue();
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

    if(msg->isSelfMessage()){
          // previous pkt is decompressed and it is removed from the buffer
          cranMessage *prev_pkt = this->buffer.front();
          this->buffer.pop();

          // !! response time expired !!
          EV << "end-to-end delay : " << simTime() - prev_pkt->getCreationTime() << endl;
          emit(this->responseTimeSignal, simTime() - prev_pkt->getRrhArrivalTime());
          emit(this->delaySignal, (simTime() - prev_pkt->getCreationTime()));
          this->recordStatisticsOnFile(prev_pkt);

          // the packet is consumed
          delete prev_pkt;
          // RRH checks if there are other packet to be transmitted
          if(this->buffer.empty())
              this->idle = true;
          else{
              this->startDecompression();
          }
      } else {
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

    simtime_t decompressionTime = this->getDecompressionTime(pkt);
    scheduleAt(simTime() + decompressionTime , this->beep);
    EV<<"[RRH] decompressionTime: "<< decompressionTime <<endl;
}

void Rrh::finish(){
    while(!this->buffer.empty()){
        cancelAndDelete(this->buffer.front());
        this->buffer.pop();
    }

    cancelEvent(this->beep);
    cancelAndDelete(this->beep);
}
