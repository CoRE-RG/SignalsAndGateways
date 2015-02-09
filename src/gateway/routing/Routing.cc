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

#include "Routing.h"
#include "InterConnectMsg_m.h"
#include "CanDataFrame_m.h"
#include "CTFrame_m.h"
#include "FieldSequenceMessage_m.h"
#include "MultipleFieldSequenceMessage.h"
#include "CanTransportStructure.h"
#include "Utility.h"

using namespace FiCo4OMNeT;

namespace SignalsAndGateways {

Define_Module(Routing);

void Routing::initialize()
{
    routingTable = par("routingTable").xmlValue();
    items = routingTable->getChildren();
}

void Routing::handleMessage(cMessage *msg)
{
    InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
    cPacket *delivery = interDataStructure->decapsulate();
    if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
        CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
        canDataFrame->setNode(canDataFrame->getSenderModule()->getParentModule()->gate("gate$i")->getPathStartGate()->getOwnerModule()->getParentModule()->getName());
        const char* busname = canDataFrame->getSenderModule()->getParentModule()->gate("gate$i")->getPathStartGate()->getOwnerModule()->getParentModule()->getName();
        unsigned int canID = canDataFrame->getCanID();
        InterConnectMsg *newInterDateStructure = new InterConnectMsg;
        newInterDateStructure->encapsulate(canDataFrame);
        int i = 0;
        for(cXMLElementList::iterator element = items.begin(); element != items.end(); ++element){
            EV << "Cycle: " << i << endl;
            std::string sourceBusID = (*element)->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceBusID")->getNodeValue();
            Utility::stripNonAlphaNum(sourceBusID);
            EV << "sourceBusID: " << sourceBusID.c_str() << endl;
            if(strcmp(sourceBusID.c_str(), busname) == 0){
                std::string sourceObjectID = (*element)->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceObjectID")->getNodeValue();
                Utility::stripNonAlphaNum(sourceObjectID);
                EV << "sourceObjectID: " << sourceObjectID.c_str() << endl;
                if(atoi(sourceObjectID.c_str()) == canID){
                    newInterDateStructure->setFirstArrivalTimeOnCan(interDataStructure->getFirstArrivalTimeOnCan());
                    newInterDateStructure->setRoutingData((*element)->getChildren());
                    send(newInterDateStructure->dup(), "out");
                    EV << "RoutingData found!" << endl;
                    break;
                }
            }
            i++;
        }
        delete newInterDateStructure;
    }else if(dynamic_cast<MultipleFieldSequenceMessage*>(delivery) != NULL){
        MultipleFieldSequenceMessage *multiFieldSequence = dynamic_cast<MultipleFieldSequenceMessage*>(delivery);
        while(multiFieldSequence->getFieldCount() > 0){
            InterConnectMsg *newInterDateStructure = new InterConnectMsg;
            BaseTransportStructure* transportFrame = multiFieldSequence->popFieldSequence();
            int i = 0;
            for(cXMLElementList::iterator element = items.begin(); element != items.end(); ++element){
                EV << "Cycle: " << i << endl;
                std::string sourceBusID = (*element)->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceBusID")->getNodeValue();
                Utility::stripNonAlphaNum(sourceBusID);
                EV << "sourceBusID: " << sourceBusID.c_str() << endl;
                if(strcmp(sourceBusID.c_str(), transportFrame->getStaticBusID().c_str()) == 0){
                    std::string sourceObjectID = (*element)->getFirstChildWithTag("source")->getFirstChildWithTag ("sourceObjectID")->getNodeValue();
                    Utility::stripNonAlphaNum(sourceObjectID);
                    EV << "sourceObjectID: " << sourceObjectID.c_str() << endl;
                    if(atoi(sourceObjectID.c_str()) == dynamic_cast<CanTransportStructure*>(transportFrame)->getIdentifier()){
                        newInterDateStructure->setRoutingData((*element)->getChildren());
                        EV << "RoutingData found!" << endl;
                        break;
                    }
                }
                i++;
            }
            if(newInterDateStructure->getRoutingData().size() > 0){
                FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
                fieldSequence->setTransportFrame(transportFrame);
                newInterDateStructure->encapsulate(fieldSequence);
                send(newInterDateStructure, "out");
            } else {
                delete newInterDateStructure;
                delete transportFrame;
            }

        }
        delete multiFieldSequence;
    }

    delete msg;
}

}

