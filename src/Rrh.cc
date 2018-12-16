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
    cranMessage *pkt;

    if(msg->isSelfMessage()){
          /*
          std::ofstream myfile;
          myfile.open ("percentage.txt",std::ios_base::app);
          for(int i=0; i<buffer.size(); i++){
            myfile<<this->getId()<<" RRH Buffer["<<i<<"]: "<<buffer[i]->getId()<<endl;
          }
          myfile.close();*/

          // previous pkt is decompressed and it is removed from the buffer
          cranMessage *prev_pkt = buffer.front();
          buffer.pop();
          // the packet is consumed
          delete(prev_pkt);
          // RRH checks if there are other packet to be transmitted
          if(buffer.empty())
              working = false;
          else{
              pkt = buffer.front();
              startDecompression(pkt);
          }
      }else{
          // new packet from Bbu
          pkt = check_and_cast<cranMessage*>(msg);
          buffer.push(pkt);
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
