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


using namespace dataStruct;

Define_Module(Transformation);

void Transformation::initialize()
{
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

    for(auto &element : interDataStructure->getRoutingData()){
        if(strcmp(element->getTagName(), "source") == 0){
            source = element;
        }else if(strcmp(element->getTagName(), "destination") == 0){
            destination = element->getParentNode()->getChildrenByTagName("destination");
        }else if(strcmp(element->getTagName(), "options") == 0){
            options = element;
        }
    }

    cPacket *delivery = interDataStructure->getEncapsulatedPacket();

    string sourceTyp = source->getFirstChildWithTag("sourceType")->getNodeValue();
    UTLTY::Utility::stripNonAlphaNum(sourceTyp);
    EV << "sourceType: " << sourceTyp << endl;
    string to = "To";
    UTLTY::Utility::stripNonAlphaNum(to);

    bool stopLoop = false;
    for(auto &element : destination){
        string destinationType = element->getFirstChildWithTag("destinationType")->getNodeValue();
        UTLTY::Utility::stripNonAlphaNum(destinationType);
        EV << "destinationType: " << destinationType << endl;

        string tranformation = sourceTyp + to + destinationType;

        EV << "tranformation: " << tranformation << endl;
        if(not(stopLoop)){
            switch (transformMap->getTransformationID(tranformation)) {
                case 1://canTocan
                    {//to declare the scope for the assigned variables
                        InterConnectMsg *newInterDataStructure = new InterConnectMsg;
                        newInterDataStructure->setRoutingData(interDataStructure->getRoutingData());
                        if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
                            CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
                            canDataFrame->setArrivalTime(interDataStructure->getFirstArrivalTimeOnCan());
                            FieldSequenceDataStructure transportFrame = transformCanToTransport(canDataFrame);
                            FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
                            fieldSequence->setTransportFrame(transportFrame);
                            simtime_t maxWaitingTime = SimTime(atoi(UTLTY::Utility::stripNonAlphaNum(options->getFirstChildWithTag("holdUpTime")->getNodeValue(), 5).c_str()));
                            fieldSequence->setMaxWaitingTime(maxWaitingTime);
                            newInterDataStructure->encapsulate(fieldSequence);
                            int ctID = atoi(UTLTY::Utility::stripNonAlphaNum(element->getFirstChildWithTag("backboneCTID")->getNodeValue(), 3).c_str());
                            EV << "CTID: " << ctID << endl;
                            newInterDataStructure->setBackboneCTID(ctID);
                            send(newInterDataStructure, "out");
                            stopLoop = true;
                        }else if(dynamic_cast<FieldSequenceMessage*>(delivery) != NULL){
                            FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(delivery);
                            FieldSequenceDataStructure transportFrame = fieldSequence->getTransportFrame();
                            CanDataFrame *canDataFrame = transformTransportToCan(transportFrame, element);
                            newInterDataStructure->encapsulate(canDataFrame);
                            send(newInterDataStructure, "out");
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
        }
    }
    return interDataStructure;
}

FieldSequenceDataStructure Transformation::transformCanToTransport(CanDataFrame *msg){
    /*
     * Uebersetzungsprotokoll
     */
    FieldSequenceDataStructure protocolFieldSequence;
    std::shared_ptr<dataStruct::IdentifierFieldElement> identifier (new IdentifierFieldElement());
    EV << "Transformation: getCanID(): " << msg->getCanID();
    identifier->setIdentifier(msg->getCanID());
    std::shared_ptr<dataStruct::DataFieldElement> data (new DataFieldElement(msg->getDataArraySize()));
    data->setDataLength(msg->getDataArraySize());
    for (unsigned int i=0; i<msg->getDataArraySize(); i++){
        data->setData(msg->getData(i), i);
    }
    std::shared_ptr<dataStruct::TimestampFieldElement>  timestamp (new TimestampFieldElement());
    timestamp->setTimestamp(msg->getArrivalTime());
    /*
     * Transportprotokollheader
     */
    std::shared_ptr<dataStruct::TransportHeaderFieldElement>  transportHeader (new TransportHeaderFieldElement());
    transportHeader->setStaticTranslationID(1);
    std::string test = msg->getNode();
    transportHeader->setStaticBusID(msg->getNode());
    std::string test2 = transportHeader->getStaticBusID();
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

        std::shared_ptr<DataFieldElement> dataElement = transportFrame.getField<DataFieldElement>();
        for (int i = 0; dataElement->getDataLength() < i ; i++){
            canDataFrame->setData(dataElement->getData(i), i);
        }
        canDataFrame->setLength(canDataFrame->getDataArraySize());

        std::shared_ptr<TimestampFieldElement> timestampElement = transportFrame.getField<TimestampFieldElement>();
        canDataFrame->setArrivalTime(timestampElement->getTimestamp());
    }catch(cException e){
        opp_error(e.what());
    }

    transportFrame.clear();

    return canDataFrame;
}

