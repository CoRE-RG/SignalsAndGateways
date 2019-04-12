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

#include "CanSourceGatewayApp.h"

//FiCo4OMNeT
//Auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"

using namespace FiCo4OMNeT;

namespace SignalsAndGateways {

Define_Module(CanSourceGatewayApp);

CanSourceGatewayApp::~CanSourceGatewayApp()
{
    outgoingDataFrames.clear();
}

void CanSourceGatewayApp::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in")){
        //quick & dirty for new statistics
        CanDataFrame* df = dynamic_cast<CanDataFrame*> (msg);
        df->setTimestamp(simTime());
        send(df, "out");
    } else {
        delete msg;
    }

}

}
