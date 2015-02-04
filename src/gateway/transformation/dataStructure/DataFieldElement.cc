/*
 * DataFieldElement.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: sebastian
 */

#include <dataStructure/DataFieldElement.h>
#include <stdlib.h>

DataFieldElement::DataFieldElement(int dataLength) {
    dataLength_ = dataLength;
    data_ = new char[dataLength];
    setFieldID("dataField");
}

DataFieldElement::~DataFieldElement() {
    //delete(data_);
}
