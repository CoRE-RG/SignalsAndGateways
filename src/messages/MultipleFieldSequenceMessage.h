/*
 * MultipleFieldSequenceMessage.h
 *
 *  Created on: Mar 28, 2014
 *      Author: sebastian
 */

#ifndef MULTIPLEFIELDSEQUENCEMESSAGE_H_
#define MULTIPLEFIELDSEQUENCEMESSAGE_H_

#include "MultipleFieldSequenceMessage_m.h"

namespace SignalsAndGateways {

class MultipleFieldSequenceMessage : public MultipleFieldSequenceMessage_Base
{
private:
    std::list<BaseTransportStructure*> fieldSequenceList;
    int fieldCount;
    void copy(const MultipleFieldSequenceMessage& other) {
        fieldSequenceList = other.copyFiledSequenceList();
        fieldCount = other.getFieldCount();
    }
public:
     MultipleFieldSequenceMessage(const char *name=NULL, int kind=0) : MultipleFieldSequenceMessage_Base(name,kind) {
         fieldSequenceList = FieldSequenceList();
         fieldCount = 0;
     }

     MultipleFieldSequenceMessage(const MultipleFieldSequenceMessage& other) : MultipleFieldSequenceMessage_Base(other) {
         copy(other);
     }

     MultipleFieldSequenceMessage& operator=(const MultipleFieldSequenceMessage& other) {
         if (this==&other) return *this; MultipleFieldSequenceMessage_Base::operator=(other);
         copy(other);
         return *this;
     }

     MultipleFieldSequenceMessage *dup() const {
         return new MultipleFieldSequenceMessage(*this);
     }

     void pushFieldSequence(BaseTransportStructure* transportFrame){
         fieldSequenceList.push_front(transportFrame);
         addByteLength(sizeof *transportFrame);
         fieldCount++;
         EV << "Field pushed to MultipleFieldSequenceMessage" << endl;
     }

     BaseTransportStructure* popFieldSequence(){
         EV << "Length of List: " << fieldSequenceList.size() << endl;
         BaseTransportStructure* element = fieldSequenceList.back();
         fieldSequenceList.pop_back();
         this->setByteLength(getByteLength()-static_cast<int64_t>(sizeof *element));
         fieldCount--;
         return element;
     }

     int getFieldCount() const{
         return fieldCount;
     }

     FieldSequenceList copyFiledSequenceList() const{
         return fieldSequenceList;
     }

     FieldSequenceList& getFieldSequenceList() {
         return fieldSequenceList;
     }

     void setFieldSequenceList(const std::list<BaseTransportStructure*>& newFieldSequenceList){
         fieldSequenceList = newFieldSequenceList;
     }

};

Register_Class(MultipleFieldSequenceMessage);

}

#endif /* MULTIPLEFIELDSEQUENCEMESSAGE_H_ */
