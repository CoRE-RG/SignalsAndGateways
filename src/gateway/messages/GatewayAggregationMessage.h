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
        void copy(const GatewayAggregationMessage& other);
    public:
        GatewayAggregationMessage(const char *name=NULL, int kind=0) : GatewayAggregationMessage_Base(name,kind)
        {
        }

        GatewayAggregationMessage(const GatewayAggregationMessage& other) : GatewayAggregationMessage_Base(other)
        {
            copy(other);
        }

        GatewayAggregationMessage& operator=(const GatewayAggregationMessage& other)
        {
            if (this==&other) return *this;
            GatewayAggregationMessage_Base::operator=(other);
            copy(other);
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
