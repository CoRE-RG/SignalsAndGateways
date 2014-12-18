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

package signalsandgateways.gateway.routing;
import signalsandgateways.gateway.IConnection;

//
// Based on the content of the incoming message the corresponding routing data is collected.
//
// Independent of the message type, which can be CanDataFrame or MultipleFieldSequenceMessage, the
// same search keys are used.
// The routing table is specified by the parameter 'routingTable'.
//
// @author Sebastian Mueller
//
simple Routing like IConnection
{
    parameters:
        //path to the routing table
        xml routingTable;
        @display("i=block/routing");
    gates:
        //Input connection for the inter module data exchange within the gateway
   		input in @label (InterConnectMsg);
   		//Output connection for the inter module data exchange within the gateway
   		output out @label (InterConnectMsg);
}
