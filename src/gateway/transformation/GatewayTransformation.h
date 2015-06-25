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

#ifndef __SIGNALSANDGATEWAYS_GATEWAYTRANSFORMATION_H_
#define __SIGNALSANDGATEWAYS_GATEWAYTRANSFORMATION_H_

#include <omnetpp.h>

#include <string>
#include <map>
#include <list>
#include <vector>

#include "CanDataFrame_m.h"
#include "AVBFrame_m.h"
#include "CoRE4INET_CTFrame.h"
#include "RCFrame_m.h"
#include "TTFrame_m.h"

#include "PoolMessage_m.h"
#include "UnitMessage_m.h"
#include "GatewayAggregationMessage.h"

namespace SignalsAndGateways {

class GatewayTransformation : public cSimpleModule
{
    private:
        /**
         * @brief Size of the CRC field in a CAN frame.
         */
        static const int CANCRCBITLENGTH;
    private:
        /**
         * @brief Holds all CAN IDs this node forwards.
         */
        std::list<unsigned int> canToCan;
        /**
         * @brief Holds the information to which BE ethernet destination CAN frames with the corresponding ID should be forwarded.
         */
        std::map<unsigned int, std::list<std::string> > canToBEEthernet;
        /**
         * @brief Holds the information from which destination be ethernet frames should be forwarded to CAN.
         */
        std::list<std::string> beEthernetToCan;
        /**
         * @brief Holds the information to which RC ethernet destination CAN frames with the corresponding ID should be forwarded.
         */
        std::map<unsigned int, std::list<uint16_t> > canToRCEthernet;
        /**
         * @brief Holds the information to which TT ethernet destination CAN frames with the corresponding ID should be forwarded.
         */
        std::map<unsigned int, std::list<uint16_t> > canToTTEthernet;
        /**
         * @brief Holds the information which frames with the corresponding CT IDs should be forwarded to CAN.
         */
        std::list<uint16_t> ctEthernetToCan;
        //TODO ...
    protected:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
    private:
        /**
         * @brief Gateway configuration using information from assigned XML file.
         */
        void readConfigXML();
        /**
         * @brief The CAN frame is transformed into the proper ethernet, RC or TT frame.
         */
        std::list<cMessage*> transformCanFrame(FiCo4OMNeT::CanDataFrame* canFrame);
        /**
         * @brief CAN frames are extracted from pool message and transformed into the proper ethernet, RC or TT frame.
         */
        std::list<cMessage*> transformPoolMessage(PoolMessage* poolMessage);

        /**
         * @brief Transform CAN frames from an ethernet frame.
         */
        std::list<cMessage*> transformEthernetFrame(inet::EthernetIIFrame* ethernetFrame);

        /**
         * @brief Add a single CAN frame into a GatewayAggregationMessage into and encapsulate it in a best effort ethernet frame.
         */
        inet::EthernetIIFrame* transformCanToBEEthernet(FiCo4OMNeT::CanDataFrame* canFrame);
        /**
         * @brief Add several CAN frames into a GatewayAggregationMessage into and encapsulate it in a best effort ethernet frame.
         */
        inet::EthernetIIFrame* transformCanToBEEthernet(std::list<FiCo4OMNeT::CanDataFrame*> canFrames);
        /**
         * @brief Add a single CAN frame into a GatewayAggregationMessage into and encapsulate it in a RC ethernet frame.
         */

        CoRE4INET::RCFrame* transformCanToRCEthernet(FiCo4OMNeT::CanDataFrame* canFrame);
        /**
         * @brief Add several CAN frames into a GatewayAggregationMessage into and encapsulate it in a RC ethernet frame.
         */
        CoRE4INET::RCFrame* transformCanToRCEthernet(std::list<FiCo4OMNeT::CanDataFrame*> canFrames);
        /**
         * @brief Add a single CAN frame into a GatewayAggregationMessage into and encapsulate it in a TT ethernet frame.
         */
        CoRE4INET::TTFrame* transformCanToTTEthernet(FiCo4OMNeT::CanDataFrame* canFrame);
        /**
         * @brief Add several CAN frames into a GatewayAggregationMessage into and encapsulate it in a TT ethernet frame.
         */
        CoRE4INET::TTFrame* transformCanToTTEthernet(std::list<FiCo4OMNeT::CanDataFrame*> canFrames);
        //transformCanToAVBEthernet...

        /**
         * @brief Decapsulate the GatewayAggregationMessage from the ethernetFrame and extract all CAN frames from it.
         */
        std::list<FiCo4OMNeT::CanDataFrame*> transformEthernetToCan(inet::EthernetIIFrame* ethernetFrame);

        //transformEthernetToFlexRay...

        /**
         * @brief Based on the size of the encapsulated package, the size of the ethernetFrame is set at least to the ethernet min size.
         */
        void setEthernetFrameSize(inet::EthernetIIFrame* ethernetFrame);
        /**
         * @brief Encapsulate canFrame in a UnitMessage.
         */

        UnitMessage* generateUnitMessage(FiCo4OMNeT::CanDataFrame* canFrame);
        /**
         * @brief Generate GatewayAggregationMessage containing all elements from the UnitMessages.
         */
        GatewayAggregationMessage* generateGatewayAggregationMessage(std::list<UnitMessage*> units);

};

} //namespace

#endif
