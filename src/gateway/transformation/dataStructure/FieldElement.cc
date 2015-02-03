/*
 * FieldElement.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: sebastian
 */

#include <FieldElement.h>

namespace dataStruct {

FieldElement::FieldElement() {

}

FieldElement::~FieldElement() {

}

void FieldElement::setFieldID(std::string fieldID){
    fieldID_ = fieldID;
}

std::string FieldElement::getFieldID(){
    return fieldID_;
}

} /* namespace Transformation */

