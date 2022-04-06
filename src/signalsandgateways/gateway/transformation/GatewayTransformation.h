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

#ifndef SIGNALSANDGATEWAYS_GATEWAYTRANSFORMATION_H_
#define SIGNALSANDGATEWAYS_GATEWAYTRANSFORMATION_H_

//Std
#include <string>
#include <map>
#include <list>
#include <vector>

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"

//CoRE4INET
#include "core4inet/linklayer/ethernet/AS6802/CTFrame.h"
//Auto-generated messages
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"
#include "core4inet/linklayer/ethernet/AS6802/RCFrame_m.h"
#include "core4inet/linklayer/ethernet/AS6802/TTFrame_m.h"
//FiCo4OMNeT auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"
//SignalsAndGateways auto-generated messages
#include "signalsandgateways/gateway/messages/PoolMessage_m.h"
#include "signalsandgateways/gateway/messages/UnitMessage_m.h"
#include "signalsandgateways/gateway/messages/GatewayAggregationMessage.h"

namespace SignalsAndGateways {

using namespace omnetpp;

/**
 * @brief This module receives single frames or pool messages from the buffering module.
 *
 * Corresponding to the xml configuration all frames are processed and forwarded to the right destination.
 *
 * @author Philipp Meyer, Timo Haeckel
 */
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
         * @brief Holds the information to which IEEE802.1Q ethernet destination CAN frames with the corresponding ID should be forwarded.
         */
        class QInfo{
            public:
                std::string mac;
                uint16_t vid;
                uint8_t pcp;
        };
        std::map<unsigned int, std::list<QInfo> > canToQEthernet;

        /**
         * @brief Holds the information from which destination IEEE802.1Q ethernet frames should be forwarded to CAN.
         */
        std::list<std::string> qEthernetToCan;

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

        std::list<uint16_t> avbEthernetToCan; //TODO use correct size of stream IDs

        /**
         * @brief Holds the information which CAN frames should be forwarded to which RAW frames with the corresponding ID.
         */
        std::map<unsigned int, std::list<uint16_t> > canToRawData;

        /**
         * @brief Holds the information to which CAN destination RAW frames with the corresponding ID should be forwarded.
         */
        std::list<unsigned int> rawDataToCan;

        /**
         * @brief Gateway ID in gateway config file. If auto or empty the gateway module name will be used.
         */
        std::string gatewayID;

    protected:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize() override;

        virtual void handleParameterChange(const char *parname) override;

        virtual void handleMessage(cMessage *msg) override;

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
         * @brief Transform CAN frames from an ethernet frame.
         */
        std::list<cMessage*> transformRawDataFrame(GatewayAggregationMessage* rawDataFrame);

        /**
         * @brief Add a single CAN frame into a GatewayAggregationMessage into and encapsulate it in a best effort ethernet frame.
         */
        inet::EthernetIIFrame* transformCanToBEEthernet(FiCo4OMNeT::CanDataFrame* canFrame);

        /**
         * @brief Add several CAN frames into a GatewayAggregationMessage into and encapsulate it in a best effort ethernet frame.
         */
        inet::EthernetIIFrame* transformCanToBEEthernet(std::list<FiCo4OMNeT::CanDataFrame*> canFrames);

        /**
         * @brief Add a single CAN frame into a GatewayAggregationMessage into and encapsulate it in a IEEE802.1Q ethernet frame.
         */
        CoRE4INET::EthernetIIFrameWithQTag* transformCanToQEthernet(FiCo4OMNeT::CanDataFrame* canFrame);

        /**
         * @brief Add several CAN frames into a GatewayAggregationMessage into and encapsulate it in a IEEE802.1Q ethernet frame.
         */
        CoRE4INET::EthernetIIFrameWithQTag* transformCanToQEthernet(std::list<FiCo4OMNeT::CanDataFrame*> canFrames);

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

        /**
         * @brief Add a single CAN frame into a GatewayAggregationMessage into and encapsulate it in a TT ethernet frame.
         */
        GatewayAggregationMessage* transformCanToRawData(FiCo4OMNeT::CanDataFrame* canFrame);

        /**
         * @brief Add several CAN frames into a GatewayAggregationMessage into and encapsulate it in a TT ethernet frame.
         */
        GatewayAggregationMessage* transformCanToRawData(std::list<FiCo4OMNeT::CanDataFrame*> canFrames);

        //transformCanToAVBEthernet...

        /**
         * @brief Decapsulate the GatewayAggregationMessage from the ethernetFrame and extract all CAN frames from it.
         */
        std::list<FiCo4OMNeT::CanDataFrame*> transformEthernetToCan(inet::EthernetIIFrame* ethernetFrame);

        /**
         * @brief Decapsulate the GatewayAggregationMessage from the ethernetFrame and extract all CAN frames from it.
         */
        std::list<FiCo4OMNeT::CanDataFrame*> transformRawDataToCan(GatewayAggregationMessage* rawDataFrame);

        //transformEthernetToFlexRay...

        /**
         * @brief Based on the size of the encapsulated package, the size of the ethernetFrame is set at least to the ethernet min size.
         */
        void setEthernetFrameSize(inet::EthernetIIFrame* ethernetFrame);

        /**
         * @brief Based on the size of the encapsulated package, the size of the ethernetFrameWithQTag is set at least to the IEEE802.1Q ethernet min size.
         */
        void setEthernetQFrameSize(CoRE4INET::EthernetIIFrameWithQTag* ethernetQFrame);

        /**
         * @brief Encapsulate canFrame in a UnitMessage.
         */
        UnitMessage* generateUnitMessage(FiCo4OMNeT::CanDataFrame* canFrame);

        /**
         * @brief Generate GatewayAggregationMessage containing all elements from the UnitMessages.
         */
        GatewayAggregationMessage* generateGatewayAggregationMessage(std::list<UnitMessage*> units);

        /*
         * @brief Create a message name
         *
         * @param additionalInformation string with additional message informations
         *
         * @return message name string
         */
        std::string createMessageName(const char* additionalInformation);
};

} //namespace

#endif
