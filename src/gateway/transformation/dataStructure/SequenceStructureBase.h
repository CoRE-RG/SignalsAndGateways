/*
 * SequenceStructureBase.h
 *
 *  Created on: 06.02.2015
 *      Author: Philipp
 */

#ifndef SEQUENCESTRUCTUREBASE_H_
#define SEQUENCESTRUCTUREBASE_H_

#include <string>
#include <omnetpp.h>

namespace SignalsAndGateways {

class SequenceStructureBase {
public:
    SequenceStructureBase();
    virtual ~SequenceStructureBase();

    int getStaticTranslationID() const;
    void setStaticTranslationID(int newStaticTranslationId);
    std::string getStaticBusID() const;
    void setStaticBusID(std::string newStaticBusId);
    bool isActualityFlag() const;
    void setActualityFlag(bool newActualityFlag);
    simtime_t getTimestamp() const;
    void setTimestamp(simtime_t newTimestamp);
private:
    int staticTranslationID;
    std::string staticBusID;
    bool actualityFlag;
    simtime_t timestamp;
};

}

#endif /* SEQUENCESTRUCTUREBASE_H_ */
