/*
 * SequenceStructureBase.cpp
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#include "SequenceStructureBase.h"

using namespace std;

namespace SignalsAndGateways {

SequenceStructureBase::SequenceStructureBase() {


}

SequenceStructureBase::~SequenceStructureBase() {

}

int SequenceStructureBase::getStaticTranslationID() const {
    return staticTranslationID;
}

void SequenceStructureBase::setStaticTranslationID(int newStaticTranslationId) {
    staticTranslationID = newStaticTranslationId;
}

string SequenceStructureBase::getStaticBusID() const {
    return staticBusID;
}

void SequenceStructureBase::setStaticBusID(string newStaticBusId) {
    staticBusID = newStaticBusId;
}

bool SequenceStructureBase::isActualityFlag() const {
    return actualityFlag;
}

void SequenceStructureBase::setActualityFlag(bool newActualityFlag) {
    actualityFlag = newActualityFlag;
}

simtime_t SequenceStructureBase::getTimestamp() const {
    return timestamp;
}

void SequenceStructureBase::setTimestamp(simtime_t newTimestamp) {
    timestamp = newTimestamp;
}

}

