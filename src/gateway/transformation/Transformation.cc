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

#include "Transformation.h"
#include "IdentifierFieldElement.h"
#include "DataFieldElement.h"
#include "TimestampFieldElement.h"
#include "TransportHeaderFieldElement.h"
#include "FieldSequenceMessage_m.h"
#include "Utility.h"
#include "GlobalGatewayInformation.h"
#include <algorithm>


using namespace dataStruct;

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
    delete msg;
}

InterConnectMsg *Transformation::transform(cMessage *msg){
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

    cPacket *delivery = interDataStructure->getEncapsulatedPacket();

    string sourceTyp = source->getFirstChildWithTag("sourceType")->getNodeValue();
    UTLTY::Utility::stripNonAlphaNum(sourceTyp);
    EV << "sourceType: " << sourceTyp << endl;
    string to = "To";
    UTLTY::Utility::stripNonAlphaNum(to);

    bool busRegistered = false;
    int destinationCount = 0;
    list<string> registerBackboneCTID;
    for(cXMLElementList::iterator element = destination.begin(); element != destination.end(); ++element){
        if(GlobalGatewayInformation::checkBusRegistered(gatewayName, UTLTY::Utility::stripNonAlphaNum((*element)->getFirstChildWithTag("destinationBusID")->getNodeValue()))){
            busRegistered = true;
        }
        string destinationType = (*element)->getFirstChildWithTag("destinationType")->getNodeValue();
        UTLTY::Utility::stripNonAlphaNum(destinationType);
        EV << "destinationType: " << destinationType << endl;

        string tranformation = sourceTyp + to + destinationType;

        switch (transformMap->getTransformationID(tranformation)) {
            case 1://canTocan
                {//to declare the scope for the assigned variables
                    InterConnectMsg *newInterDataStructure = new InterConnectMsg;
                    newInterDataStructure->setRoutingData(interDataStructure->getRoutingData());
                    if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
                        if(busRegistered){
                            //send CanDataFrame to own canbusses
                            interDataStructure->setAssignedDestinationCount(destinationCount);
                            CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(interDataStructure->decapsulate());
                            string destinationCanID = (*element)->getFirstChildWithTag("destinationObjectID")->getNodeValue();
                            UTLTY::Utility::stripNonAlphaNum(destinationCanID);
                            canDataFrame->setCanID(atoi(destinationCanID.c_str()));
                            interDataStructure->encapsulate(canDataFrame);
                            send(interDataStructure->dup(), "out");
                        }else{
                            CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
                            canDataFrame->setArrivalTime(interDataStructure->getFirstArrivalTimeOnCan());
                            FieldSequenceDataStructure transportFrame = transformCanToTransport(canDataFrame);
                            FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
                            fieldSequence->setTransportFrame(transportFrame);
                            cXMLElementList backboneProperties;
                            backboneProperties = (*element)->getChildrenByTagName("backbone");
                            for(cXMLElementList::iterator property = backboneProperties.begin(); property != backboneProperties.end(); ++property){
                                string maxWaitingTime = (*property)->getFirstChildWithTag("holdUpTime")->getNodeValue();
                                UTLTY::Utility::stripNonAlphaNum(maxWaitingTime);
                                fieldSequence->setMaxWaitingTime(maxWaitingTime.c_str());
                                newInterDataStructure->encapsulate(fieldSequence);
                                string backboneTransferType = (*property)->getFirstChildWithTag("backboneTransferType")->getNodeValue();
                                UTLTY::Utility::stripNonAlphaNum(backboneTransferType);
                                newInterDataStructure->setBackboneTransferType(backboneTransferType.c_str());
                                string messageAccumulation = (*property)->getFirstChildWithTag("messageAccumulation")->getNodeValue();
                                UTLTY::Utility::stripNonAlphaNum(messageAccumulation);
                                if(strcmp(messageAccumulation.c_str(), "true") == 0){
                                    newInterDataStructure->setMessageAccumulation(true);
                                }else{
                                    newInterDataStructure->setMessageAccumulation(false);
                                }
                                string backboneID;
                                if(strcmp(backboneTransferType.c_str(), "TT") == 0 || strcmp(backboneTransferType.c_str(), "RC") == 0 ){
                                    int ctID = atoi(UTLTY::Utility::stripNonAlphaNum((*property)->getFirstChildWithTag("backboneCTID")->getNodeValue()).c_str());
                                    EV << "CTID: " << ctID << endl;
                                    newInterDataStructure->setBackboneCTID(ctID);
                                    backboneID = numberToString(ctID);
                                }else if(strcmp(backboneTransferType.c_str(), "BG") == 0){
                                    string macAdress = (*property)->getFirstChildWithTag("directMacAdress")->getNodeValue();
                                    UTLTY::Utility::stripNonAlphaNum(macAdress);
                                    newInterDataStructure->setDirectMacAdress(macAdress.c_str());
                                    backboneID = macAdress;
                                }else{
                                    opp_error("BackboneTansferType specified in RoutingTable invalid!");
                                }
                                std::list<string>::iterator findIter = std::find(registerBackboneCTID.begin(), registerBackboneCTID.end(), backboneID);
                                if(findIter == registerBackboneCTID.end()){
                                    send(newInterDataStructure, "out");
                                    registerBackboneCTID.push_back(backboneID);
                                }
                            }
                        }
                    }else if(dynamic_cast<FieldSequenceMessage*>(delivery) != NULL){
                        if(busRegistered){
                            FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(delivery);
                            FieldSequenceDataStructure transportFrame = fieldSequence->getTransportFrame();
                            CanDataFrame *canDataFrame = transformTransportToCan(transportFrame, (*element));
                            newInterDataStructure->encapsulate(canDataFrame);
                            newInterDataStructure->setAssignedDestinationCount(destinationCount);
                            send(newInterDataStructure, "out");
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

    return interDataStructure;
}

FieldSequenceDataStructure Transformation::transformCanToTransport(CanDataFrame *msg){
    /*
     * Uebersetzungsprotokoll
     */
    FieldSequenceDataStructure protocolFieldSequence;
    dataStruct::IdentifierFieldElement* identifier (new IdentifierFieldElement());
    EV << "Transformation: getCanID(): " << msg->getCanID() << endl;
    identifier->setIdentifier(msg->getCanID());
    dataStruct::DataFieldElement* data (new DataFieldElement(msg->getDataArraySize()));
    data->setDataLength(msg->getDataArraySize());
    for (int i=0; i<msg->getDataArraySize(); i++){
        data->setData(i, msg->getData(i));
    }

    dataStruct::TimestampFieldElement*  timestamp (new TimestampFieldElement());
    timestamp->setTimestamp(msg->getArrivalTime());
    /*
     * Transportprotokollheader
     */
    dataStruct::TransportHeaderFieldElement*  transportHeader (new TransportHeaderFieldElement());
    transportHeader->setStaticTranslationID(1);
    transportHeader->setStaticBusID(msg->getNode());
    transportHeader->setActualityFlag(true);
    /*
     * Create sequence
     */
    protocolFieldSequence.pushField(transportHeader);
    protocolFieldSequence.pushField(timestamp);
    protocolFieldSequence.pushField(data);
    protocolFieldSequence.pushField(identifier);

    return protocolFieldSequence;
}


CanDataFrame *Transformation::transformTransportToCan(FieldSequenceDataStructure transportFrame, cXMLElement* routingDestination){
    CanDataFrame *canDataFrame = new CanDataFrame();
    canDataFrame->setNode("CAN-TTE-Gateway");
    canDataFrame->setRtr(false);

    try{
        string destinationCanID = routingDestination->getFirstChildWithTag("destinationObjectID")->getNodeValue();
        UTLTY::Utility::stripNonAlphaNum(destinationCanID);
        canDataFrame->setCanID(atoi(destinationCanID.c_str()));

        DataFieldElement* dataElement = transportFrame.getField<DataFieldElement>();
        for (int i = 0;  i < dataElement->getDataLength(); i++){
            canDataFrame->setData(i, dataElement->getData(i));
        }
        canDataFrame->setLength(canDataFrame->getDataArraySize());

        TimestampFieldElement* timestampElement = transportFrame.getField<TimestampFieldElement>();
        canDataFrame->setArrivalTime(timestampElement->getTimestamp());
    }catch(cException e){
        opp_error(e.what());
    }

    transportFrame.clear();

    return canDataFrame;
}

