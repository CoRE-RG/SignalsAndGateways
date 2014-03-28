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

#include <TimeTriggeredBuffer.h>
#include "IdentifierFieldElement.h"

TimeTriggeredBuffer::TimeTriggeredBuffer() {
    this->timeQueue = new cQueue("preBuffer", compare);
}

TimeTriggeredBuffer::~TimeTriggeredBuffer() {
    this->timeQueue->clear();
}

void TimeTriggeredBuffer::enqueue(FieldSequenceMessage* value){
//    this->buffer.insert(ValuePair(key, value));
    this->timeQueue->insert(value);
}

FieldSequenceMessage* TimeTriggeredBuffer::dequeue() const{
//    TimeBuffer::const_iterator pos =  this->buffer.find(key);
//    FieldSequence *value = NULL;
//    if(pos != buffer.end()){
//        *value = pos->second;
//    }
//    return *value;
    FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(this->timeQueue->pop());
    return fieldSequence;
}

int TimeTriggeredBuffer::compareFunc(cObject *a, cObject *b){
    FieldSequenceMessage* canA = dynamic_cast<FieldSequenceMessage*>(a);
    FieldSequenceMessage* canB = dynamic_cast<FieldSequenceMessage*>(b);
    int returnValue = 0;
    if(canA == NULL || canB == NULL){
        FieldSequenceDataStructure canA_fieldSequence = canA->getTransportFrame();
        FieldSequenceDataStructure canB_fieldSequence = canB->getTransportFrame();
        //returnValue = canA_fieldSequence->getField<IdentifierFieldElement>()->getIdentifier();
    }else{
        opp_error("Insertion of object in PreBuffer failed. Only CanDataFrame-objects are supported!");
    }
    return returnValue;
}
