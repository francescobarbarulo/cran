#include "cranMessage.h"

cranMessage::cranMessage(int id, int s, int d){
    this->id=id;
    this->size = s;
    this->dest = d;
    this->compression = 0;
    this->times.created_at = simTime();
    EV << "pkt #" << id << " created at " << this->times.created_at << endl;
}

// setter

void cranMessage::setBbuArrivalTime(){
    this->times.bbu_arrival = simTime();
}

void cranMessage::setRrhArrivalTime(){
    this->times.rrh_arrival = simTime();
}

// getter

int cranMessage::getSize(){
    return this->size;
}

int cranMessage::getDest(){
    return this->dest;
}

int cranMessage::getCompression(){
    return this->compression;
}

int cranMessage::getId(){
    return this->id;
}

simtime_t cranMessage::getCreationTime(){
    return this->times.created_at;
}

simtime_t cranMessage::getBbuArrivalTime(){
    return this->times.bbu_arrival;
}

simtime_t cranMessage::getRrhArrivalTime(){
    return this->times.rrh_arrival;
}

// features

void cranMessage::compressPkt(int percentage){
    this->size = this->size * ((100.0 - percentage)/100.0) + 1;
    this->compression = percentage;
    EV << "compressed packet by: " << this->compression << " - new size: " << this->size << endl;
}
