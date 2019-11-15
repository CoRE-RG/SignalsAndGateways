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

//
// Basic gateway which forwards messages from the source to the desired destination.
//
// @see ~IGatewayRouter, ~IGatewayTransformation, ~IGatewayBuffering
//
// @author Till Steinbach, Stefan Buschmann, Philipp Meyer, Timo Haeckel
//
module GatewayBase
{
    parameters:
        @display("i=device/hub");
        
        //Number of gateway ports
        int numPorts;
        //Path of the gateway configuration xml file
        xml configXML = default(xmldoc("GatewayConfig.xml"));
        //The path in configXML is the default path for the router, buffering and transform module
        xml defaultConfigXML = configXML;
        //Static delay of the router module
        double routingDelay @unit(s) = default(0s);
        //Static delay of the buffering module
        double bufferingDelay @unit(s) = default(0s);
        //Static delay of the tranform module
        double transformDelay @unit(s) = default(0s);
        
        //Gateway ID in gateway config file. If auto or empty the gateway module name will be used.
        string gatewayID = default("auto");
        *.gatewayID = gatewayID;
        
    gates:
        input lowerLayerIn[numPorts];
        output lowerLayerOut[numPorts];
        
    types:
        // Channel represents the processing delay of the router, buffering and tranform module
        channel ProcessingDelay extends ned.DelayChannel
        {
        }   
        
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
            
    connections:
        for i=0..numPorts-1 {
            lowerLayerIn[i] --> router.in[i];
            router.out[i] --> ProcessingDelay{ delay = routingDelay; } --> buffering[i].in;
            buffering[i].out --> ProcessingDelay{ delay = bufferingDelay; } --> transform[i].in;
            transform[i].out --> ProcessingDelay{ delay = transformDelay; } --> lowerLayerOut[i];
        }
}
