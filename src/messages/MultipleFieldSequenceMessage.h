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
    std::list<FieldSequenceDataStructure> fieldSequenceList_;
    int fieldCount_;
    void copy(const MultipleFieldSequenceMessage& other) {
        fieldSequenceList_ = other.copyFiledSequenceList();
        fieldCount_ = other.getFieldCount();
    }
public:
     MultipleFieldSequenceMessage(const char *name=NULL, int kind=0) : MultipleFieldSequenceMessage_Base(name,kind) {
         fieldSequenceList_ = FieldSequenceList();
         fieldCount_ = 0;
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
         fieldSequenceList_.push_front(transportFrame);
         addByteLength(sizeof(FieldSequenceDataStructure));
         fieldCount_++;
         EV << "Field pushed to MultipleFieldSequenceMessage" << endl;
     }

     FieldSequenceDataStructure popFieldSequence(){
         EV << "Length of List: " << fieldSequenceList_.size() << endl;
         FieldSequenceDataStructure element = fieldSequenceList_.back();
         fieldSequenceList_.pop_back();
         this->setByteLength(getByteLength()-static_cast<int64_t>(sizeof(FieldSequenceDataStructure)));
         fieldCount_--;
         return element;
     }

     int getFieldCount() const{
         return fieldCount_;
     }

     FieldSequenceList copyFiledSequenceList() const{
         return fieldSequenceList_;
     }

     FieldSequenceList& getFieldSequenceList() {
         return fieldSequenceList_;
     }

     void setFieldSequenceList(const std::list<FieldSequenceDataStructure>& fieldSequenceList){
         fieldSequenceList_ = fieldSequenceList;
     }

};

Register_Class(MultipleFieldSequenceMessage);

}

#endif /* MULTIPLEFIELDSEQUENCEMESSAGE_H_ */
