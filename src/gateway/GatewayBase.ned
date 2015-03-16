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

import signalsandgateways.gateway.routing.IGatewayRouter;
import signalsandgateways.gateway.transformation.ITransformation;
import signalsandgateways.gateway.buffering.IGatewayBuffering;

module GatewayBase
{
    parameters:
        @display("bgb=401,241;i=device/hub");
        int numPorts;
    gates:
        input lowerLayerIn[numPorts];
        output lowerLayerOut[numPorts];
    submodules:
        //module that handles the routing data
        router: <default("BaseGatewayRouter")> like IGatewayRouter {
            @display("p=313,117");
        }
        //module that performs the transformations in all directions
        transform[numPorts]: <default("NoGatewayTransformation")> like ITransformation {
            @display("p=63,117");
        }
        //module that coordinates the preBuffer behaivior
        buffering[numPorts]: <default("NoGatewayBuffering")> like IGatewayBuffering {

            @display("p=193,117");
        }
        //modules that dispatches the FieldSequenceMessage to the right TimeTriggeredBuffer
    connections:
        for i=0..numPorts-1 {
            lowerLayerIn[i] --> router.in[i];
            router.out[i] --> buffering[i].in;
            buffering[i].out --> transform[i].in;
            transform[i].out --> lowerLayerOut[i];
        }
}
