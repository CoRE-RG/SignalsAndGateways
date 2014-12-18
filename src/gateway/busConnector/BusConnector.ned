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

package signalsandgateways.gateway.busConnector;

import signalsandgateways.gateway.IConnection;

//
// Redirects the CanDataFrames from and to the gateway.
// Incoming CanDataFrames from the connected busses are forwarded to the gateway. Outgoing CanDataFrames from the gateway are redirected to the proper CAN-bus.
//
// @author Sebastian Mueller
//
simple BusConnector like IConnection
{
    parameters:
        @display("bgb=209,144;i=block/dispatch");
  	  	int countOfCanBusses = default(1);
    gates:
        //Input connection for the inter module data exchange within the gateway
        input in @label (InterConnectMsg);
        //Output connection for the inter module data exchange within the gateway
        output out @label (InterConnectMsg);
        inout busConnect[countOfCanBusses];
        
}
