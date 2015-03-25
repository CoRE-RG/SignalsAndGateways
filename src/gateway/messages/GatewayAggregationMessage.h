/*
 * GatewayAggregationMessage.h
 *
 *  Created on: 25.03.2015
 *      Author: Philipp
 */

#ifndef GATEWAYAGGREGATIONMESSAGE_H_
#define GATEWAYAGGREGATIONMESSAGE_H_

#include <list>

#include "GatewayAggregationMessage_m.h"
#include "UnitMessage_m.h"

namespace SignalsAndGateways {

class GatewayAggregationMessage : public GatewayAggregationMessage_Base
{
    private:
        std::list<UnitMessage*> units;
    public:
//        GatewayAggregationMessage() :
//            GatewayAggregationMessage_Base()
//        {
//        }

        GatewayAggregationMessage(const GatewayAggregationMessage& other) :
            GatewayAggregationMessage_Base(other)
        {
        }

        GatewayAggregationMessage(const char *name = nullptr, short kind = 0) :
            GatewayAggregationMessage_Base(name, kind)
        {
        }

        GatewayAggregationMessage& operator=(const GatewayAggregationMessage& other)
        {
            GatewayAggregationMessage_Base::operator=(other);
            return *this;
        }

        virtual GatewayAggregationMessage *dup() const
        {
            return new GatewayAggregationMessage(*this);
        }

        virtual void encapUnit(UnitMessage* unit);
        virtual UnitMessage* decapUnit();
        virtual size_t getUnitCnt();
};

} // namespace

#endif /* GATEWAYAGGREGATIONMESSAGE_H_ */
