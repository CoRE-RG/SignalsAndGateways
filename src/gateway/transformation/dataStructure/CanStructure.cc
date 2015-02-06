/*
 * CanSequenceStructure.cpp
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#include "CanStructure.h"

namespace SignalsAndGateways {

CanStructure::CanStructure(unsigned int initDataLength) {
    dataLength = initDataLength;
    data = new char[initDataLength];
}

CanStructure::~CanStructure() {
    delete(data);
}

int CanStructure::getIdentifier() const {
    return identifier;
}

void CanStructure::setIdentifier(int newIdentifier) {
    identifier = newIdentifier;
}

bool CanStructure::isRtr() const {
    return rtr;
}

void CanStructure::setRtr(bool newRtr) {
    this->rtr = newRtr;
}

unsigned int CanStructure::getDataLength() const {
    return dataLength;
}

void CanStructure::setDataLength(unsigned int newDataLength) {
    dataLength = newDataLength;
}

char CanStructure::getData(unsigned int index) const {
    return data[index];
}

void CanStructure::setData(unsigned int index, char newData) {
    data[index] = newData;
}

}

