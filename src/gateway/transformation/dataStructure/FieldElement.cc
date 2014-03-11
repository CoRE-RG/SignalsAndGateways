/*
 * FieldElement.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: sebastian
 */

#include <FieldElement.h>

namespace Transformation {

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

} /* namespace Transformation */

