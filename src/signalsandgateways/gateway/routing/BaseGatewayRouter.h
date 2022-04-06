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

#ifndef SIGNALSANDGATEWAYS_BASEGATEWAYROUTER_H_
#define SIGNALSANDGATEWAYS_BASEGATEWAYROUTER_H_

//Std
#include <string>
#include <map>
#include <list>
#include <vector>

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"

namespace SignalsAndGateways {

using namespace omnetpp;

/**
 * @brief This module decides to which destinations incoming frames will be forwarded.
 *
 * @author Philipp Meyer, Timo Haeckel
 */
class BaseGatewayRouter : public cSimpleModule
{
    private:
        /**
         * @brief CAN traffic identification prefix
         */
        static const std::string CANPREFIX;

        /**
         * @brief AVB traffic identification prefix
         */
        static const std::string AVBPREFIX;

        /**
         * @brief TTE traffic identification prefix
         */
        static const std::string TTEPREFIX;

        /**
         * @brief Ethernet best effort traffic identification prefix
         */
        static const std::string ETHPREFIX;

        /**
         * @brief IEEE802.1Q traffic identification prefix
         */
        static const std::string VIDPREFIX;

        /**
         * @brief RAW Data as GatewayAggregationMessage identification prefix
         */
        static const std::string RAWPREFIX;

    private:
        std::map<int, std::map<int, std::list<std::string> > > routing;

        /**
         * @brief Simsignal for the number of dropped frames.
         */
        simsignal_t droppedFramesSignal;

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
         * @brief This method returns a vector with all gates to which a frame has to be forwarded.
         */
        std::vector<int> getDestinationGateIndices(int sourceIndex, std::string messageID);
};

} //namespace

#endif
