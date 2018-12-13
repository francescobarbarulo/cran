#include "Rrh.h"
#include <fstream>

Define_Module(Rrh);

void Rrh::initialize()
{
    working = false;
    beep = new cMessage();
}

void Rrh::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){

          std::ofstream myfile;
          myfile.open ("percentage.txt",std::ios_base::app);
          for(int i=0; i<buffer.size(); i++){
            myfile<<this->getId()<<" RRH Buffer["<<i<<"]: "<<buffer[i]->getId()<<endl;
          }
          myfile.close();
          buffer.erase(buffer.begin());
          // RRH checks if there are other packet to be transmitted
          if(buffer.size() == 0)
              working = false;
          else{
              startDecompression(buffer[0]);
          }
         // delete(buffer[0]);
      }else{
          // new packet from Bbu
          cranMessage *pkt = check_and_cast<cranMessage*>(msg);
          buffer.push_back(pkt);
          if(!working){
              // RRH is idle so it can process the packet immediately
              working = true;
              startDecompression(pkt);
          }
      }
}

void Rrh::startDecompression(cranMessage *pkt){
    // case compression enabled
    if (pkt->isCompressed()){
        simtime_t decompressionTime = par("compressionPercentage").intValue()*0.05;
        scheduleAt(simTime() + decompressionTime , beep);
        EV<<"[RRH] decompressionTime: "<<decompressionTime<<endl;
    } else {
        scheduleAt(simTime(), beep);
    }


}
