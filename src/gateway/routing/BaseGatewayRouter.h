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

#ifndef __SIGNALSANDGATEWAYS_BASEGATEWAYROUTER_H_
#define __SIGNALSANDGATEWAYS_BASEGATEWAYROUTER_H_

#include <omnetpp.h>

#include <string>
#include <map>
#include <list>
#include <vector>

namespace SignalsAndGateways {

class BaseGatewayRouter : public cSimpleModule
{
    private:
        static const std::string CANPREFIX;
        static const std::string AVBPREFIX;
        static const std::string TTEPREFIX;
        static const std::string ETHPREFIX;
    private:
        std::map<int, std::map<int, std::list<std::string> > > routing;

        /**
         * @brief Simsignal for the number of dropped frames.
         */
        simsignal_t droppedFramesSignal;
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
    private:
        void readConfigXML();
        std::vector<int> getDestinationGateIndices(int sourceIndex, std::string messageID);
};

} //namespace

#endif
