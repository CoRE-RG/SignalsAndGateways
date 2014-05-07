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

package signalsandgateways.gateway.transformation;

import signalsandgateways.gateway.IConnection;

//
// @brief Transformation of bus messages in FieldSequenceMessages and vice versa.
//
// This module converts the incoming bus message in a sequence of fields.
// On the other hand incoming messages which consists of a sequence are converted to the specified bus message.
// The conversion in a sequence of fields, which is called transport presentation, is
// necessary to convert messages from one bus type into another and offers a simple way of transportation
// within the ethernet backbone network. Which kind of transformation is used,
// is to be defined in the routing table by 'sourceType' and 'destinationType'.
//
// @author Sebastian Mueller
//
simple Transformation like IConnection
{
    parameters:
        //path to the routing table
    	xml routingTable;
    	@display("i=block/segm");
    gates:
        //Input connection for the inter module data exchange within the gateway
        input in @label (InterConnectMsg);
        //Output connection for the inter module data exchange within the gateway
        output out @label (InterConnectMsg);
}
