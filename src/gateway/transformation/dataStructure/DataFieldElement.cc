/*
 * DataFieldElement.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#include <dataStructure/DataFieldElement.h>
#include <stdlib.h>

namespace dataStruct {

DataFieldElement::DataFieldElement(int dataLength) {
    this->dataLength = dataLength;
    this->data = (char*)malloc(sizeof(char)*dataLength);
    this->setFieldID("dataField");
}

DataFieldElement::~DataFieldElement() {
    free(data);
}

void DataFieldElement::dummy(){

}

} /* namespace Transformation */
