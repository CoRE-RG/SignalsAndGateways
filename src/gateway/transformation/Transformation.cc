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
}

void Transformation::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        send(transform(msg), "out");
    }
}

cPacket *Transformation::transform(cMessage *msg){
    InterConnectMsg *interDataStructure = dynamic_cast<InterConnectMsg*>(msg);
    cPacket *returnMessage = NULL;
    EV << "transform entrance" << endl;
    if(transformMap->getTransformationID(interDataStructure->getTransformationID()) > 0){
        EV << "transform: " << "transformationID > 0" << endl;
        if(strcmp(interDataStructure->getTransformationID(),"canTocan") == 0){
            EV << "transform: " << "canTocan" << endl;
            if(strcmp(interDataStructure->getFrameFormat(), "canDataFrame") == 0){
                EV << "transform: " << "canDataFrame" << endl;
                CanDataFrame *canDataFrame = dynamic_cast<CanDataFrame*>(interDataStructure->decapsulate());
                FieldSequenceDataStructure transportFrame = transformCanToTransport(canDataFrame);
                FieldSequenceMessage *fieldSequence = new FieldSequenceMessage;
                fieldSequence->setTransportFrame(transportFrame);
                interDataStructure->encapsulate(fieldSequence);
                returnMessage = interDataStructure;
            }else if(strcmp(interDataStructure->getFrameFormat(), "transportFrame") == 0){
                EV << "transform: " << "transportFrame" << endl;
                FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(interDataStructure->decapsulate());
                FieldSequenceDataStructure transportFrame = fieldSequence->getTransportFrame();
                CanDataFrame *canDataFrame = transformTransportToCan(transportFrame);
                interDataStructure->encapsulate(canDataFrame);
                returnMessage = interDataStructure;
            }
        }
    }else{
        //invalid transformation ID
    }
    return returnMessage;
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
    transportHeader->setStaticTranslationId(1);
    transportHeader->setStaticBusId(0);
    transportHeader->setActualityFlag(true);
    /*
     * Create sequence
     */
    protocolFieldSequence.pushField(transportHeader);
    EV << "protocolFieldSequence.size()" << protocolFieldSequence.size() << endl;
    protocolFieldSequence.pushField(timestamp);
    EV << "protocolFieldSequence.size()" << protocolFieldSequence.size() << endl;
    protocolFieldSequence.pushField(data);
    EV << "protocolFieldSequence.size()" << protocolFieldSequence.size() << endl;
    protocolFieldSequence.pushField(identifier);
    EV << "protocolFieldSequence.size()" << protocolFieldSequence.size() << endl;

    return protocolFieldSequence;
}


CanDataFrame *Transformation::transformTransportToCan(FieldSequenceDataStructure transportFrame){
    CanDataFrame *canDataFrame = new CanDataFrame("message");
    canDataFrame->setPeriod(0);

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
