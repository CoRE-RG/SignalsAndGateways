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
     void copy(const MultipleFieldSequenceMessage& other) { }
     FieldSequenceList fieldSequenceList;
     int fieldCount;
public:
     MultipleFieldSequenceMessage(const char *name=NULL, int kind=0) : MultipleFieldSequenceMessage_Base(name,kind) {
         fieldSequenceList = FieldSequenceList();
     }

     MultipleFieldSequenceMessage(const MultipleFieldSequenceMessage& other) : MultipleFieldSequenceMessage_Base(other) {
         copy(other);
     }

     MultipleFieldSequenceMessage& operator=(const MultipleFieldSequenceMessage& other) {
         if (this==&other) return *this; MultipleFieldSequenceMessage_Base::operator=(other);
         copy(other);
         return *this;
     }

     virtual MultipleFieldSequenceMessage *dup() const {
         return new MultipleFieldSequenceMessage(*this);
     }

     void pushFieldSequence(FieldSequenceDataStructure transportFrame){
         fieldSequenceList.push_front(transportFrame);
         addByteLength(sizeof(FieldSequenceDataStructure));
         fieldCount++;
     }

     FieldSequenceDataStructure popFieldSequence(){
         FieldSequenceDataStructure element = fieldSequenceList.back();
         fieldSequenceList.pop_back();
         this->setByteLength(getByteLength()-sizeof(FieldSequenceDataStructure));
         fieldCount--;
         return element;
     }

     int getFieldCount(){
         return fieldCount;
     }

     virtual FieldSequenceList& getFieldSequenceList(){
         return fieldSequenceList;
     }

     virtual void setFieldSequenceList(const FieldSequenceList& fieldSequenceList){
         this->fieldSequenceList = fieldSequenceList;
     }

};

Register_Class(MultipleFieldSequenceMessage);

#endif /* MULTIPLEFIELDSEQUENCEMESSAGE_H_ */
