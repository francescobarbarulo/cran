//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Collector.h"

Define_Module(Collector);

void Collector::initialize()
{
    this->delaySignal = registerSignal("delay");
}

void Collector::handleMessage(cMessage *msg)
{
    cranMessage *pkt = check_and_cast<cranMessage*>(msg);
    emit(this->delaySignal, (simTime() - pkt->getCreationTime()));
    delete pkt;
}
