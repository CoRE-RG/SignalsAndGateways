//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef GATEWAYAGGREGATIONMESSAGE_H_
#define GATEWAYAGGREGATIONMESSAGE_H_

//Std
#include <list>
//SignalsAndGateways auto-generated messages
#include "signalsandgateways/gateway/messages/GatewayAggregationMessage_m.h"
#include "signalsandgateways/gateway/messages/UnitMessage_m.h"

namespace SignalsAndGateways {

/**
 * @brief Message for encapsulation of multiple UnitMessages
 *
 * @author Philipp Meyer
 */
class GatewayAggregationMessage : public GatewayAggregationMessage_Base
{
    private:
        std::list<UnitMessage*> unitList;

        void copy(const GatewayAggregationMessage& other);

    public:
        /**
         * @brief Constructor
         *
         * @param newName message name
         * @param kind message type
         */
        GatewayAggregationMessage(const char *newName=nullptr, short kind=0) : GatewayAggregationMessage_Base(newName,kind)
        {
        }

        /**
         * @brief Copy constructor
         */
        GatewayAggregationMessage(const GatewayAggregationMessage& other) : GatewayAggregationMessage_Base(other)
        {
            copy(other);
        }

        /**
         * @brief Assignment operator
         */
        GatewayAggregationMessage& operator=(const GatewayAggregationMessage& other)
        {
            if (this==&other) return *this;
            GatewayAggregationMessage_Base::operator=(other);
            copy(other);
            return *this;
        }

        /**
         * @brief GatewayAggregationMessage duplication
         */
        virtual GatewayAggregationMessage *dup() const override
        {
            return new GatewayAggregationMessage(*this);
        }

        /**
         * @brief encapsulates an UnitMessage
         *
         * @param unit UnitMessage pointer
         */
        virtual void encapUnit(UnitMessage* unit);

        /**
         * @brief decapsulates an UnitMessage
         *
         * @return UnitMessage pointer
         */
        virtual UnitMessage* decapUnit();

        /**
         * @brief get encapsulated units
         *
         * @return list of UnitMessage pointers
         */
        virtual std::list<UnitMessage*> getEncapUnits() const;

        /**
         * @brief Get number of encapsulated UnitMessages
         *
         * @return number of encapsulated UnitMessages
         */
        virtual size_t getUnitCnt();
};

} // namespace

#endif /* GATEWAYAGGREGATIONMESSAGE_H_ */
