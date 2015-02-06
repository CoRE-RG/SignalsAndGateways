/*
 * SequenceStructureBase.cpp
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#include "StructureBase.h"

using namespace std;

namespace SignalsAndGateways {

StructureBase::StructureBase() {


}

StructureBase::~StructureBase() {

}

int StructureBase::getStaticTranslationID() const {
    return staticTranslationID;
}

void StructureBase::setStaticTranslationID(int newStaticTranslationId) {
    staticTranslationID = newStaticTranslationId;
}

string StructureBase::getStaticBusID() const {
    return staticBusID;
}

void StructureBase::setStaticBusID(string newStaticBusId) {
    staticBusID = newStaticBusId;
}

bool StructureBase::isActualityFlag() const {
    return actualityFlag;
}

void StructureBase::setActualityFlag(bool newActualityFlag) {
    actualityFlag = newActualityFlag;
}

simtime_t StructureBase::getTimestamp() const {
    return timestamp;
}

void StructureBase::setTimestamp(simtime_t newTimestamp) {
    timestamp = newTimestamp;
}

}

