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
import signalsandgateways.gateway.transformation.IGatewayTransformation;
import signalsandgateways.gateway.buffering.IGatewayBuffering;
import signalsandgateways.gateway.buffering.AccumulationGatewayBuffering;

module GatewayBase
{
    parameters:
        @display("bgb=406,639;i=device/hub");
        int numPorts;
        xml configXML = default(xmldoc("GatewayConfig.xml"));
        xml defaultConfigXML = configXML;
    gates:
        input lowerLayerIn[numPorts];
        output lowerLayerOut[numPorts];
    submodules:
        //module that handles the routing data
        router: <default("BaseGatewayRouter")> like IGatewayRouter {
            @display("p=63,100;i=block/routing");
            configXML = default(defaultConfigXML);
            gates:
                in[numPorts];
                out[numPorts];
        }
        //module that performs the transformations in all directions
        transform[numPorts]: <default("NoGatewayTransformation")> like IGatewayTransformation {
            @display("p=338,100,c,130;i=block/segm");
            configXML = default(defaultConfigXML);
        }
        //module that coordinates the preBuffer behaivior
        buffering[numPorts]: <default("NoGatewayBuffering")> like IGatewayBuffering {
            @display("p=200,100,c,130;i=block/subqueue");
            configXML = default(defaultConfigXML);
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
