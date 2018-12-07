#include "cranMessage.h"

cranMessage::cranMessage(int s, int d, bool c){
    this->size = s;
    this->dest = d;
    this->compression = c;
}
int cranMessage::getSize(){
    return this->size;
}
int cranMessage::getDest(){
    return this->dest;
}
bool cranMessage::isCompressed(){
    return this->compression;
}
