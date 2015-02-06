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

#include <algorithm>

#include "Transformation.h"
#include "IdentifierFieldElement.h"
#include "DataFieldElement.h"
#include "TimestampFieldElement.h"
#include "TransportHeaderFieldElement.h"
#include "RTRFieldElement.h"
#include "FieldSequenceMessage_m.h"
#include "Utility.h"
#include "GlobalGatewayInformation.h"

using namespace std;
using namespace FiCo4OMNeT;

namespace SignalsAndGateways {

Define_Module(Transformation);

template <typename T>
std::string numberToString ( T number ){
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

void Transformation::initialize()
{
    gatewayName = getParentModule()->getParentModule()->getName();
    this->transformMap = new StaticTransformationIDList();
    routingTable = par("routingTable").xmlValue();
    items = routingTable->getChildren();
}

void Transformation::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        transform(msg);
    }
}

void Transformation::transform(cMessage *msg){
    InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);

    cXMLElementList routingData = interDataStructure->getRoutingData();
    for(cXMLElementList::iterator element = routingData.begin(); element != routingData.end(); ++element){
        if(strcmp((*element)->getTagName(), "source") == 0){
            source = (*element);
        }else if(strcmp((*element)->getTagName(), "destination") == 0){
            destination = (*element)->getParentNode()->getChildrenByTagName("destination");
        }else if(strcmp((*element)->getTagName(), "gatewayOptions") == 0){
            gatewayOptions = (*element);
        }
    }

    cPacket *delivery = interDataStructure->decapsulate();

    string sourceTyp = source->getFirstChildWithTag("sourceType")->getNodeValue();
    Utility::stripNonAlphaNum(sourceTyp);
    EV << "sourceType: " << sourceTyp << endl;
    string to = "To";
    Utility::stripNonAlphaNum(to);

    bool busRegistered = false;
    int destinationCount = 0;
    list<string> registerBackboneCTID;
    for(cXMLElementList::iterator element = destination.begin(); element != destination.end(); ++element){
        if(GlobalGatewayInformation::checkBusRegistered(gatewayName, Utility::stripNonAlphaNum((*element)->getFirstChildWithTag("destinationBusID")->getNodeValue()))){
            busRegistered = true;
        }
        string destinationType = (*element)->getFirstChildWithTag("destinationType")->getNodeValue();
        Utility::stripNonAlphaNum(destinationType);
        EV << "destinationType: " << destinationType << endl;

        string tranformation = sourceTyp + to + destinationType;

        switch (transformMap->getTransformationID(tranformation)) {
            case 1://canTocan
                {//to declare the scope for the assigned variables
                    InterConnectMsg *newInterDataStructure = new InterConnectMsg;
                    newInterDataStructure->setRoutingData(interDataStructure->getRoutingData());
                    newInterDataStructure->setFirstArrivalTimeOnCan(interDataStructure->getFirstArrivalTimeOnCan());
                    if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
                        if(busRegistered){
                            //send CanDataFrame to own canbusses
                            newInterDataStructure->setAssignedDestinationCount(destinationCount);
                            CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);

                            string destinationCanID = (*element)->getFirstChildWithTag("destinationObjectID")->getNodeValue();
                            Utility::stripNonAlphaNum(destinationCanID);
                            canDataFrame->setCanID(atoi(destinationCanID.c_str()));
                            newInterDataStructure->encapsulate(canDataFrame->dup());
                            send(newInterDataStructure, "out");
                        }else{
                            CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
//                            canDataFrame->setTimestamp(interDataStructure->getFirstArrivalTimeOnCan()); // Timestamp of canDataFrame is already set in the source app of the original sender
                            BaseTransportStructure* transportFrame = transformCanToTransport(canDataFrame);
                            FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
                            fieldSequence->setTransportFrame(transportFrame);
                            cXMLElementList backboneProperties;
                            backboneProperties = (*element)->getChildrenByTagName("backbone");
                            for(cXMLElementList::iterator property = backboneProperties.begin(); property != backboneProperties.end(); ++property){
                                string maxWaitingTime = (*property)->getFirstChildWithTag("holdUpTime")->getNodeValue();
                                Utility::stripNonAlphaNum(maxWaitingTime);
                                fieldSequence->setMaxWaitingTime(maxWaitingTime.c_str());
                                newInterDataStructure->encapsulate(fieldSequence);
                                string backboneTransferType = (*property)->getFirstChildWithTag("backboneTransferType")->getNodeValue();
                                Utility::stripNonAlphaNum(backboneTransferType);
                                newInterDataStructure->setBackboneTransferType(backboneTransferType.c_str());
                                string messageAccumulation = (*property)->getFirstChildWithTag("messageAccumulation")->getNodeValue();
                                Utility::stripNonAlphaNum(messageAccumulation);
                                if(strcmp(messageAccumulation.c_str(), "true") == 0){
                                    newInterDataStructure->setMessageAccumulation(true);
                                }else{
                                    newInterDataStructure->setMessageAccumulation(false);
                                }
                                string backboneID;
                                if(strcmp(backboneTransferType.c_str(), "TT") == 0 || strcmp(backboneTransferType.c_str(), "RC") == 0 ){
                                    uint16_t ctID = static_cast<uint16_t>(atoi(Utility::stripNonAlphaNum((*property)->getFirstChildWithTag("backboneCTID")->getNodeValue()).c_str()));
                                    EV << "CTID: " << ctID << endl;
                                    newInterDataStructure->setBackboneCTID(ctID);
                                    backboneID = numberToString(ctID);
                                }else if(strcmp(backboneTransferType.c_str(), "BE") == 0){
                                    string macAdress = (*property)->getFirstChildWithTag("directMacAdress")->getNodeValue();
                                    Utility::stripNonAlphaNum(macAdress);
                                    newInterDataStructure->setDirectMacAdress(macAdress.c_str());
                                    backboneID = macAdress;
                                }else{
                                    opp_error("BackboneTansferType specified in RoutingTable invalid!");
                                }
                                std::list<string>::iterator findIter = std::find(registerBackboneCTID.begin(), registerBackboneCTID.end(), backboneID);
                                if(findIter == registerBackboneCTID.end()){
                                    send(newInterDataStructure, "out");
                                    registerBackboneCTID.push_back(backboneID);
                                }else{
                                    delete newInterDataStructure;
                                }
                            }
                        }
                    }else if(dynamic_cast<FieldSequenceMessage*>(delivery) != NULL){
                        if(busRegistered){
                            FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(delivery);
                            BaseTransportStructure* transportFrame = fieldSequence->getTransportFrame();
                            CanDataFrame *canDataFrame = transformTransportToCan(dynamic_cast<CanTransportStructure*>(transportFrame), (*element));
                            newInterDataStructure->encapsulate(canDataFrame);
                            newInterDataStructure->setAssignedDestinationCount(destinationCount);
                            send(newInterDataStructure, "out");
                        }else{
                            delete newInterDataStructure;
                        }
                    }
                }
                break;
            case 2://canToFlexray

                break;
            case 3://flexrayToFlexray

                break;
            case 4://flexrayTocan

                break;
            default:
                opp_error("Error when resolving transformation type. Please check the source and destination type in your Routing-Table");
        }
        destinationCount++;
        busRegistered = false;
    }

    delete delivery;
    delete interDataStructure;
}

CanTransportStructure* Transformation::transformCanToTransport(CanDataFrame *msg){
    /*
     * Uebersetzungsprotokoll
     */
    EV << "Transformation: getCanID(): " << msg->getCanID() << endl;

    unsigned int payloadbytelength = msg->getDataArraySize();
    CanTransportStructure* protocolFieldSequence = new CanTransportStructure(payloadbytelength);
    for (unsigned int i=0; i<payloadbytelength; i++){
        protocolFieldSequence->setData(i, msg->getData(i));
    }
    protocolFieldSequence->setIdentifier(msg->getCanID());
    protocolFieldSequence->setRtr(msg->getRtr());
    protocolFieldSequence->setTimestamp(msg->getTimestamp());
    EV << "transformCanToTransport: firstCanArrivalTime: " << msg->getTimestamp() << endl;
    /*
     * Transportprotokollheader
     */
    protocolFieldSequence->setStaticTranslationID(1);
    protocolFieldSequence->setStaticBusID(msg->getNode());
    protocolFieldSequence->setActualityFlag(true);

    return protocolFieldSequence;
}


CanDataFrame *Transformation::transformTransportToCan(CanTransportStructure* transportFrame, cXMLElement* routingDestination){
    CanDataFrame *canDataFrame = new CanDataFrame();
    canDataFrame->setNode("CAN-TTE-Gateway");

    try{
        string destinationCanID = routingDestination->getFirstChildWithTag("destinationObjectID")->getNodeValue();
        Utility::stripNonAlphaNum(destinationCanID);
        canDataFrame->setCanID(atoi(destinationCanID.c_str()));
        canDataFrame->setDataArraySize(transportFrame->getDataLength());
        for (unsigned int i = 0;  i < transportFrame->getDataLength(); i++){
            canDataFrame->setData(i, transportFrame->getData(i));
        }
        canDataFrame->setRtr(transportFrame->isRtr());
        canDataFrame->setTimestamp(transportFrame->getTimestamp());
        EV << "transformTransportToCan: firstCanArrivalTime: " << transportFrame->getTimestamp() << endl;
    }catch(cException e){
        opp_error(e.what());
    }

    //delete transportFrame;

    return canDataFrame;
}

}
