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

#include <FieldSequenceBuffer.h>
#include "IdentifierFieldElement.h"

FieldSequenceBuffer::FieldSequenceBuffer() {
    timeQueue = cQueue("preBuffer", compare);
}

FieldSequenceBuffer::~FieldSequenceBuffer() {
    timeQueue.clear();
}

void FieldSequenceBuffer::enqueue(FieldSequenceMessage* value){
    timeQueue.insert(value);
}

FieldSequenceMessage* FieldSequenceBuffer::dequeue(){
    FieldSequenceMessage* fieldSequence = dynamic_cast<FieldSequenceMessage*>(timeQueue.pop());
    return fieldSequence;
}

int FieldSequenceBuffer::compareFunc(cObject *a, cObject *b){
    FieldSequenceMessage* canA = dynamic_cast<FieldSequenceMessage*>(a);
    FieldSequenceMessage* canB = dynamic_cast<FieldSequenceMessage*>(b);
    int returnValue = 0;
    if(canA == NULL || canB == NULL){
        FieldSequenceDataStructure canA_fieldSequence = canA->getTransportFrame();
        FieldSequenceDataStructure canB_fieldSequence = canB->getTransportFrame();
        returnValue = (canA_fieldSequence.getField<IdentifierFieldElement>()->getIdentifier())-(canB_fieldSequence.getField<IdentifierFieldElement>()->getIdentifier());
    }else{
        opp_error("Insertion of object in PreBuffer failed. Only CanDataFrame-objects are supported!");
    }
    return returnValue;
}

bool FieldSequenceBuffer::isEmpty(){
    return timeQueue.isEmpty();
}
