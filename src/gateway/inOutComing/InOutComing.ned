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

package signalsandgateways.gateway.inOutComing;
import signalsandgateways.gateway.IConnection;

//
// Receiving and forwarding messages from and to the network nodes.
//
// This module receives messages from the network nodes of the gateway and sends the messages further in the gateway logic.
// In addition messages, which were handled by the gateway, are forwarded to the appropriate network node.
// A network node can be an ethernet or a bus node.
//
// @author Sebastian Mueller
//
simple InOutComing like IConnection
{
    parameters:
    	@display("i=block/layer");
    gates:
        //Input connection for the inter module data exchange within the gateway
        input in @label (InterConnectMsg);
        //Output connection for the inter module data exchange within the gateway
        output out @label (InterConnectMsg);
        //connection to the network nodes, which can be both bus network and ethernet networks
    	inout appInterface[] @labels(TransportMessage);
}
