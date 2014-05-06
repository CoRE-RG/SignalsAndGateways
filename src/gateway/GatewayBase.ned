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

package signalsandgateways.gateway;

import signalsandgateways.gateway.inOutComing.InOutComing;
import signalsandgateways.gateway.preBuffer.PreBuffer;
import signalsandgateways.gateway.routing.Routing;
import signalsandgateways.gateway.transformation.Transformation;
import signalsandgateways.gateway.preBuffer.MessageDispatcher;

module GatewayBase
{
    @display("bgb=401,241;i=device/hub");
    gates:
        inout busCon[];
        inout ethCon[];
    submodules:
        iocom: InOutComing {
            @display("p=198,43");
        }
        route: Routing {
            @display("p=288,117");
        }
        transform: Transformation {
            @display("p=198,192");
        }
        prebuff: PreBuffer {
            @display("p=113,117");
        }
        messagedispatcher: MessageDispatcher {

            @display("p=74,43");
        }
    connections:
        busCon[0] <--> iocom.appInterface++;
        ethCon[0] <--> iocom.appInterface++;
        iocom.out --> route.in;
        route.out --> transform.in;
        transform.out --> prebuff.in;
        prebuff.out --> iocom.in;
        prebuff.moduleConnect <--> messagedispatcher.moduleConnect;
}
