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
import signalsandgateways.applications.ethernet.EthernetGatewayHost;
import signalsandgateways.applications.can_flexray.CanGatewayNode;

//
// Interconnection between bus- and network-interfaces and the gateway functionality
//
// @author Sebastian Mueller
//
module BusEthernetGateway
{
    parameters:
  	  	@display("bgb=243,216;i=device/router");
  	  	int countOfCanBusses = default(1);
    gates:
        //ethernet connection
        inout ethg;
        //bus connection
        inout cang[countOfCanBusses];
    submodules:
        //bus module
        can[countOfCanBusses]: CanGatewayNode {
            @display("p=192,50");
        }
        //ethernet module
        tte: EthernetGatewayHost {
            @display("p=38,50");
        }
        //gateway module
        gateway: GatewayBase {
            @display("p=120,135");
        }
    connections:
        for i=0..countOfCanBusses-1 {
        	can[i].busInterface <--> gateway.busCon++;
            can[i].gate <--> cang[i];
        }
        
        tte.ethInterface <--> gateway.ethCon++;
        tte.ethg <--> ethg;


}
