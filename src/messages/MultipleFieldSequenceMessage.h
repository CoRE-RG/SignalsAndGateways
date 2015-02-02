/*
 * MultipleFieldSequenceMessage.h
 *
 *  Created on: Mar 28, 2014
 *      Author: sebastian
 */

#ifndef MULTIPLEFIELDSEQUENCEMESSAGE_H_
#define MULTIPLEFIELDSEQUENCEMESSAGE_H_

#include "MultipleFieldSequenceMessage_m.h"

class MultipleFieldSequenceMessage : public MultipleFieldSequenceMessage_Base
{
private:
    std::list<FieldSequenceDataStructure> fieldSequenceList;
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

     void pushFieldSequence(FieldSequenceDataStructure transportFrame){
         fieldSequenceList.push_front(transportFrame);
         addByteLength(sizeof(FieldSequenceDataStructure));
         fieldCount++;
         EV << "Field pushed to MultipleFieldSequenceMessage" << endl;
     }

     FieldSequenceDataStructure popFieldSequence(){
         EV << "Length of List: " << fieldSequenceList.size() << endl;
         FieldSequenceDataStructure element = fieldSequenceList.back();
         fieldSequenceList.pop_back();
         this->setByteLength(getByteLength()-sizeof(FieldSequenceDataStructure));
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

     void setFieldSequenceList(const std::list<FieldSequenceDataStructure>& fieldSequenceList){
         this->fieldSequenceList = fieldSequenceList;
     }

};

Register_Class(MultipleFieldSequenceMessage);

#endif /* MULTIPLEFIELDSEQUENCEMESSAGE_H_ */
