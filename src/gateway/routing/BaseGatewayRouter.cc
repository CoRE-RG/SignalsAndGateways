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

#include "BaseGatewayRouter.h"

#include <algorithm>

#include "CanDataFrame_m.h"
#include "AVBFrame_m.h"
#include "CoRE4INET_CTFrame.h"

using namespace std;
using namespace FiCo4OMNeT;
using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(BaseGatewayRouter);

void BaseGatewayRouter::initialize()
{
    readConfigXML();
}

void BaseGatewayRouter::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        vector<int> destinationGateIndices;
        if(CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(canFrame->getArrivalGate()->getIndex(), "" + canFrame->getCanID());
        }else if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(avbFrame->getArrivalGate()->getIndex(), "" + avbFrame->getStreamID());
        }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(ctFrame->getArrivalGate()->getIndex(), "" + ctFrame->getCtID());
        }else if(EthernetIIFrame* ethernetFrame = dynamic_cast<EthernetIIFrame*>(msg)){
            destinationGateIndices = getDestinationGateIndices(ethernetFrame->getArrivalGate()->getIndex(), ethernetFrame->getDest().str());
        }
        for(size_t i=0; i<destinationGateIndices.size(); i++){
            if(destinationGateIndices[i] < gateSize("out")){
                send(msg->dup(), "out", destinationGateIndices[i]);
            }
        }
    }
    delete msg;
}

void BaseGatewayRouter::readConfigXML(){

}

vector<int> BaseGatewayRouter::getDestinationGateIndices(int sourceIndex, string messageID){
    vector<int> destinationGateIndices;
    int i = 0;
    for(map<int, list<string> >::iterator it = routing[sourceIndex].begin(); it != routing[sourceIndex].end(); ++it)
    {
        if(find(it->second.begin(), it->second.end(), messageID) != it->second.end()){
            destinationGateIndices[i++] = it->first;
        }
    }
    return destinationGateIndices;
}

} //namespace
