#include "Rrh.h"

Define_Module(Rrh);

simtime_t Rrh::getDecompressionTime(){
    // Compression time does not depend on packet size
    if (!par("dependentDecompressionTime").boolValue())
        return this->server->getCompression()*par("timePerCompressionUnit").doubleValue();
    // Compression time does depend on packet size
    return this->server->getSize()/par("decompressionSpeed").doubleValue();
}

void Rrh::initialize()
{
    this->beep = new cMessage();
    this->server = NULL;

    // signals registration
    this->responseTimeSignal = registerSignal("responseTime");
    this->waitingTimeSignal = registerSignal("waitingTime");
    this->rrhJobsSignal = registerSignal("rrhJobs");
}

void Rrh::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
          // !! response time expired !!
          EV << "end-to-end delay : " << simTime() - this->server->getCreationTime() << endl;
          emit(this->responseTimeSignal, simTime() - this->server->getRrhArrivalTime());
          // Send the packet to the collector
          send(this->server, "out");

          // RRH checks if there are other packet to be transmitted
          if (this->buffer.empty())
              this->server = NULL;
          else {
              this->server = this->buffer.front();
              this->buffer.pop();
              this->startDecompression();
          }
      } else {
          // new packet from Bbu
          emit(this->rrhJobsSignal, (long)buffer.size() + (int)(bool)this->server);

          cranMessage *pkt = check_and_cast<cranMessage*>(msg);
          pkt->setRrhArrivalTime();

          if (!this->server){
              // RRH is idle so it can process the packet immediately
              this->server = pkt;
              this->startDecompression();
          } else {
              this->buffer.push(pkt);
          }
      }
}

void Rrh::startDecompression(){
    // !! waiting time expired !!
    emit(this->waitingTimeSignal, simTime() - this->server->getRrhArrivalTime());

    simtime_t decompressionTime = this->getDecompressionTime();
    scheduleAt(simTime() + decompressionTime , this->beep);
    EV<<"[RRH] decompressionTime: "<< decompressionTime <<endl;
}

void Rrh::finish(){
    while(!this->buffer.empty()){
        cancelAndDelete(this->buffer.front());
        this->buffer.pop();
    }

    if (this->server)
        cancelAndDelete(server);

    cancelEvent(this->beep);
    cancelAndDelete(this->beep);
}
