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
#include "TransportMessage_m.h"
#include "CanDataFrame_m.h"

Define_Module(CanSourceGatewayApp);

void CanSourceGatewayApp::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("busInterfaceIn")){
        TransportMessage *transFrame = check_and_cast<TransportMessage*>(msg);
        CanDataFrame *canDataFrame = check_and_cast<CanDataFrame *>(transFrame->decapsulate());
        EV << "CanSourceGatewayApp: firstCanArrivalTime: " << canDataFrame->getTimestamp() << endl;
        simtime_t timeDifference = simTime()-canDataFrame->getTimestamp();
        std::string canbusName = getParentModule()->gate("gate$o")->getPathEndGate()->getOwnerModule()->getParentModule()->getParentModule()->getName();
        char timeReport [85];
        sprintf(timeReport, "Time difference source- and dest. gateway: %s", timeDifference.str().c_str());
        EV << timeReport << endl;
        send(canDataFrame, "out");
        delete transFrame;
    } else {
        delete msg;
    }

}
