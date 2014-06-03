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


FieldSequenceBuffer::FieldSequenceBuffer() {
    timeQueue = cQueue("preBuffer", pCompare);
}

FieldSequenceBuffer::~FieldSequenceBuffer() {
    timeQueue.clear();
}

void FieldSequenceBuffer::enqueue(FieldSequenceMessage* value){
    timeQueue.insert(value);
}

FieldSequenceMessage* FieldSequenceBuffer::dequeue(){
    FieldSequenceMessage* fieldSequence = NULL;
    if(!timeQueue.isEmpty()){
        fieldSequence = dynamic_cast<FieldSequenceMessage*>(timeQueue.pop());
    }else{
        opp_error("Trying to dequeue an element of FieldSequenceBuffer, but the buffer is empty!");
    }
    return fieldSequence;
}

bool FieldSequenceBuffer::isEmpty(){
    return timeQueue.isEmpty();
}

