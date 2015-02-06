/*
 * CanSequenceStructure.cpp
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#include "CanSequenceStructure.h"

namespace SignalsAndGateways {

CanSequenceStructure::CanSequenceStructure(unsigned int initDataLength) {
    dataLength = initDataLength;
    data = new char[initDataLength];
}

CanSequenceStructure::~CanSequenceStructure() {
    delete(data);
}

int CanSequenceStructure::getIdentifier() const {
    return identifier;
}

void CanSequenceStructure::setIdentifier(int newIdentifier) {
    identifier = newIdentifier;
}

bool CanSequenceStructure::isRtr() const {
    return rtr;
}

void CanSequenceStructure::setRtr(bool newRtr) {
    this->rtr = newRtr;
}

unsigned int CanSequenceStructure::getDataLength() const {
    return dataLength;
}

void CanSequenceStructure::setDataLength(unsigned int newDataLength) {
    dataLength = newDataLength;
}

char CanSequenceStructure::getData(unsigned int index) const {
    return data[index];
}

void CanSequenceStructure::setData(unsigned int index, char newData) {
    data[index] = newData;
}

}

