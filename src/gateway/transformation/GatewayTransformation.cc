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

#include "GatewayTransformation.h"

using namespace std;
using namespace FiCo4OMNeT;
using namespace CoRE4INET;

namespace SignalsAndGateways {

Define_Module(GatewayTransformation);

void GatewayTransformation::initialize()
{
    readConfigXML();
}

void GatewayTransformation::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        if(CanDataFrame* canFrame = dynamic_cast<CanDataFrame*>(msg)){

        }else if(PoolMessage* poolMessage = dynamic_cast<PoolMessage*>(msg)){

        }else if(AVBFrame* avbFrame = dynamic_cast<AVBFrame*>(msg)){

        }else if(CTFrame* ctFrame = dynamic_cast<CTFrame*>(msg)){

        }else if(EthernetIIFrame* ethernetFrame = dynamic_cast<EthernetIIFrame*>(msg)){

        }
    }
    delete msg;
}

void GatewayTransformation::readConfigXML(){
    cXMLElement* xmlDoc = par("configXML").xmlValue();
    string gatewayName = this->getParentModule()->getParentModule()->getName();
    string xpath = "/config/gateway[@id='" + gatewayName + "']/transformation";
    cXMLElement* xmlTransformation = xmlDoc->getElementByPath(xpath.c_str(), xmlDoc);
    if(xmlTransformation){

    }
}

EthernetIIFrame* GatewayTransformation::transformCanToBEEthernet(FiCo4OMNeT::CanDataFrame*){

}

} //namespace
