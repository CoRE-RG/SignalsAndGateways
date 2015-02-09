/*
 * CanSequenceStructure.cpp
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#include "CanTransportStructure.h"

namespace SignalsAndGateways {

CanTransportStructure::CanTransportStructure(unsigned int initDataLength) {
    dataLength = initDataLength;
    data = new char[initDataLength];
}

CanTransportStructure::~CanTransportStructure() {
    delete(data);
}

int CanTransportStructure::getIdentifier() const {
    return identifier;
}

void CanTransportStructure::setIdentifier(int newIdentifier) {
    identifier = newIdentifier;
}

bool CanTransportStructure::isRtr() const {
    return rtr;
}

void CanTransportStructure::setRtr(bool newRtr) {
    this->rtr = newRtr;
}

unsigned int CanTransportStructure::getDataLength() const {
    return dataLength;
}

void CanTransportStructure::setDataLength(unsigned int newDataLength) {
    dataLength = newDataLength;
}

char CanTransportStructure::getData(unsigned int index) const {
    return data[index];
}

void CanTransportStructure::setData(unsigned int index, char newData) {
    data[index] = newData;
}

}

