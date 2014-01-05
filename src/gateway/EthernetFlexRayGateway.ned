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

import signalsandgateways.routing.Base;
import signalsandgateways.applications.ethernet.EthernetGatewayHost;
import signalsandgateways.applications.can_flexray.CanGatewayNode;

module EthernetFlexRayGateway
{
    @display("bgb=243,216");
    gates:
        inout ethg;
        inout cang;
    submodules:
        can: EthernetGatewayHost{//CanGatewayNode {
            @display("p=192,50");
        }
        tte: EthernetGatewayHost {
            @display("p=38,50");
        }
        routing: Base {
            @display("p=120,135");
        }
    connections:
        can.ethRoutingInterface <--> routing.appInterface++;
        tte.ethRoutingInterface <--> routing.appInterface++;
        
        can.ethg <--> cang; //can.gate
        tte.ethg <--> ethg;

    //submodules:
    //    routing: <lala> like IRouting {
    //        parameters:
    //            @display("p=100,50");
    //        gates:
    //            interface[numEthernetApps+numFlexRayApps];
    //    }

    //    ethernetApp[numEthernetApps]: <default("lala")> like IEthernetGatewayApplication {
    //    //can_flexrayApp[numFlexRayApps]: <default("lala")> like IFlexrayGatewayApplication;
    //        @display("p=255,50");
    //    }
    //connections:
    //    for i=0..sizeof(ethernetApp)-1 {
    //        ethernetApp[i].interface[0] <--> routing.interface[i];
    //    }
    //    //for i=0..sizeof(can_flexrayApp)-1 {
    //    //    can_flexrayApp[i].interface <--> routing.interface[i+sizeof(ethernetApp)];
    //    //}

}
