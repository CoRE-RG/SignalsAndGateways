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

package signalsandgateways.applications.ethernet;

import signalsandgateways.applications.ethernet.EthernetGatewayApplication;

import core4inet.nodes.ethernet.tsn.TSNEtherHost;


//
// Represents the TSN ethernet node in the ethernet backbone network with connection to the gateway.
//
// @see ~TSNEtherHost, ~EthernetGatewayApplication
//
// @author Sebastian Mueller, Ehsan Sajadi
//
module TSNEthernetGatewayHost extends TSNEtherHost like IEthernetGatewayHost
{
    parameters:
        int numberOfTT_Vlinks; // (unused) Forced by interface
        int numberOfRC_Vlinks; // (unused) Forced by interface
        
    gates:
        output upperLayerOut;
        input upperLayerIn;
        
    submodules:
        //Application for the ethernet node in the gateway
        gatewayApp: EthernetGatewayApplication {
            @display("p=282,37");
        }

        
    connections:
        gatewayApp.upperLayerOut --> upperLayerOut;
        gatewayApp.upperLayerIn <-- upperLayerIn;
}  
