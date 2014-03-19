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
    this->fieldID = fieldID;
}

std::string FieldElement::getFieldID(){
    return this->fieldID;
}

void FieldElement::dummy(){

}

} /* namespace Transformation */

