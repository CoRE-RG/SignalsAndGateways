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

package signalsandgateways;

import signalsandgateways.gateway.GatewayBase;
import signalsandgateways.applications.ethernet.IEthernetGatewayHost;
import signalsandgateways.applications.can.CanGatewayNode;

//
// Interconnection between bus- and network-interfaces and the gateway functionality
//
// @see ~CanGatewayNode, ~EthernetGatewayHost, ~GatewayBase
//
// @author Sebastian Mueller, Timo Haeckel, Philipp Meyer
//
module BusEthernetGateway
{
    parameters:
        @display("i=block/layer");
        
        //Number of CAN bus ports
        int countOfCanBusses = default(1);
        //Number of Ethernet ports
        int countOfEthernetPorts = default(1);   
        //Gateway ID in gateway config file. If auto or empty the gateway module name will be used.
        string gatewayID = default("auto");
        
    gates:
        //ethernet connection
        inout ethg[countOfEthernetPorts];
        //bus connection
        inout cang[countOfCanBusses];
        
    submodules:
        //bus module
        can[countOfCanBusses]: CanGatewayNode {
            @display("p=369,100,c,130");
        }
        
        //ethernet module
        tte[countOfEthernetPorts]: <default("EthernetGatewayHost")> like IEthernetGatewayHost {
            @display("p=74,100,c,130");
        }
        
        //gateway module
        gateway: GatewayBase {
            @display("p=224,100");
            gatewayID = parent.gatewayID;
            numPorts = parent.countOfCanBusses + parent.countOfEthernetPorts;  
        }
        
    connections:
        for i=0..countOfCanBusses-1 {
            can[i].upperLayerOut --> gateway.lowerLayerIn++;
            can[i].upperLayerIn <-- gateway.lowerLayerOut++;
            can[i].gate <--> cang++;
        }
        for i=0..countOfEthernetPorts-1 {
            tte[i].upperLayerOut --> gateway.lowerLayerIn++;
            tte[i].upperLayerIn <-- gateway.lowerLayerOut++;
            tte[i].ethg <--> ethg++;
        }
}
