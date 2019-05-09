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

//
// Interface for ethernet hosts in the gateway.
//
// @author Timo Haeckel
//
moduleinterface IEthernetGatewayHost
{
    
    parameters:
        //@display("bgb=688,409");
        
        int numberOfTT_Vlinks;
        int numberOfRC_Vlinks;
        
    gates:
        output upperLayerOut;
        input upperLayerIn;
        inout ethg;
}
