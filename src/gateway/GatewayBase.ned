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
import signalsandgateways.gateway.busConnector.BusConnector;
import ned.DatarateChannel;

//
// Consilidation of all top level modules of the gateway
//
// @author Sebastian Mueller
//

channel iocomDelay extends DatarateChannel
{
    double iocomdelay @unit(s) = default(0);
    delay = iocomdelay;
}
channel routeDelay extends DatarateChannel
{
    double routedelay @unit(s) = default(0);
    delay = routedelay;
}
channel transformDelay extends DatarateChannel
{
    double transformdelay @unit(s) = default(0);
    delay = transformdelay;
}
channel prebuffDelay extends DatarateChannel
{
    double prebuffdelay @unit(s) = default(0);
    delay = prebuffdelay;
}

module GatewayBase
{
    parameters:
    	@display("bgb=401,241;i=device/hub");
    	int countOfCanBusses = default(1);
    gates:
        //connection to the bus-systems
        inout busCon[];
        //connection to the ethernet networks
        inout ethCon[];
    submodules:
        //module that transact the communication from and to the network- and bus-interfaces
        iocom: InOutComing {
            @display("p=198,43");
        }
        busConnector: BusConnector{
            @display("p=308,43");
        }
        //module that handles the routing data
        route: Routing {
            @display("p=288,117");
        }
        //module that performs the transformations in all directions
        transform: Transformation {
            @display("p=198,192");
        }
        //module that coordinates the preBuffer behaivior
        prebuff: PreBuffer {
            @display("p=113,117");
        }
        //modules that dispatches the FieldSequenceMessage to the right TimeTriggeredBuffer
        buffering: MessageDispatcher {

            @display("p=74,43");
        }
    connections:
        for i=0..countOfCanBusses-1 {
        	busCon[i] <--> busConnector.busConnect[i];
        }
        ethCon[0] <--> iocom.appInterface++;
        iocom.out --> iocomDelay --> route.in;
        iocom.busOut --> busConnector.in;
        iocom.busIn <-- busConnector.out;
        route.out --> routeDelay --> transform.in;
        transform.out --> transformDelay --> prebuff.in;
        prebuff.out --> prebuffDelay --> iocom.in;
        prebuff.moduleConnect <--> buffering.moduleConnect;
}
