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

#include "PoolMessage_m.h"
#include "UnitMessage_m.h"
#include "GatewayAggregationMessage_m.h"

namespace SignalsAndGateways {

/**
 * TODO - Generated class
 */
class GatewayTransformation : public cSimpleModule
{
    private:
        std::vector< std::map< std::string, std::vector<int> > > canToBEEthernet;
        //...
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
    private:
        void readConfigXML();
        EthernetIIFrame* transformCanToBEEthernet(FiCo4OMNeT::CanDataFrame*);
        EthernetIIFrame* transformCanToBEEthernet(PoolMessage*);
        //...
        std::list<FiCo4OMNeT::CanDataFrame*> transformBEEthernetToCan(EthernetIIFrame*);
        GatewayAggregationMessage* generateGatewayAggregationMessage(std::list<UnitMessage*>);

};

} //namespace

#endif
