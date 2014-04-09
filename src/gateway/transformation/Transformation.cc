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
}

InterConnectMsg *Transformation::transform(cMessage *msg){
    InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);

    source = interDataStructure->getRoutingData().getFirstChildWithTag("source");
    destination = interDataStructure->getRoutingData().getChildrenByTagName("destination");
    options = interDataStructure->getRoutingData().getFirstChildWithTag("options");

    cPacket *delivery = interDataStructure->decapsulate();

    const char* sourceTyp = source->getFirstChildWithTag("sourceType")->getNodeValue();
    EV << "sourceType: " << sourceTyp << endl;
    for(auto &element : destination){
        switch (transformMap->getTransformationID(*sourceTyp + "To" + *(element->getFirstChildWithTag("destinationType")->getNodeValue()))) {
            EV << "destinationType: " << element->getFirstChildWithTag("destinationType")->getNodeValue() << endl;
            case 1://canTocan
                {//to declare the scope for the assigned variables
                    if(dynamic_cast<CanDataFrame*>(delivery) != NULL){
                        CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(delivery);
                        FieldSequenceDataStructure transportFrame = transformCanToTransport(canDataFrame);
                        FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
                        fieldSequence->setTransportFrame(transportFrame);
                        interDataStructure->encapsulate(fieldSequence);
                        send(interDataStructure, "out");
                    }else if(dynamic_cast<FieldSequenceMessage*>(delivery) != NULL){
                        FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(delivery);
                        FieldSequenceDataStructure transportFrame = fieldSequence->getTransportFrame();
                        CanDataFrame *canDataFrame = transformTransportToCan(transportFrame);
                        interDataStructure->setBackboneCTID(atoi(element->getFirstChildWithTag("backboneCTID")->getNodeValue()));
                        interDataStructure->encapsulate(canDataFrame);
                        send(interDataStructure, "out");
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
    timestamp->setTimestamp(clock());
    /*
     * Transportprotokollheader
     */
    std::shared_ptr<dataStruct::TransportHeaderFieldElement>  transportHeader (new TransportHeaderFieldElement());
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


CanDataFrame *Transformation::transformTransportToCan(FieldSequenceDataStructure transportFrame){
    CanDataFrame *canDataFrame = new CanDataFrame();
    canDataFrame->setNode("CAN-TTE-Gateway");
    canDataFrame->setRtr(false);

    try{
        std::shared_ptr<IdentifierFieldElement> identifierElement  = transportFrame.getField<IdentifierFieldElement>();
        canDataFrame->setCanID(identifierElement->getIdentifier());

        std::shared_ptr<DataFieldElement> dataElement = transportFrame.getField<DataFieldElement>();
        for (int i = 0; dataElement->getDataLength() < i ; i++){
            canDataFrame->setData(dataElement->getData(i), i);
        }
        canDataFrame->setLength(canDataFrame->getDataArraySize());

        std::shared_ptr<TimestampFieldElement> timestampElement = transportFrame.getField<TimestampFieldElement>();
        //canDataFrame->setTimestamp(timestampElement->getTimestamp());
    }catch(cException e){
        opp_error(e.what());
    }

    transportFrame.clear();

    return canDataFrame;
}
