/*
 * SequenceStructureBase.cpp
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#include "BaseTransportStructure.h"

using namespace std;

namespace SignalsAndGateways {

BaseTransportStructure::BaseTransportStructure() {


}

BaseTransportStructure::~BaseTransportStructure() {

}

int BaseTransportStructure::getStaticTranslationID() const {
    return staticTranslationID;
}

void BaseTransportStructure::setStaticTranslationID(int newStaticTranslationId) {
    staticTranslationID = newStaticTranslationId;
}

string BaseTransportStructure::getStaticBusID() const {
    return staticBusID;
}

void BaseTransportStructure::setStaticBusID(string newStaticBusId) {
    staticBusID = newStaticBusId;
}

bool BaseTransportStructure::isActualityFlag() const {
    return actualityFlag;
}

void BaseTransportStructure::setActualityFlag(bool newActualityFlag) {
    actualityFlag = newActualityFlag;
}

simtime_t BaseTransportStructure::getTimestamp() const {
    return timestamp;
}

void BaseTransportStructure::setTimestamp(simtime_t newTimestamp) {
    timestamp = newTimestamp;
}

}

