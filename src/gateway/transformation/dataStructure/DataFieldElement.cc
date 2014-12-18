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
    data = new char[dataLength];
    setFieldID("dataField");
}

DataFieldElement::~DataFieldElement() {
    delete(data);
}

} /* namespace Transformation */
