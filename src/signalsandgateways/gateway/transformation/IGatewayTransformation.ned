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

package signalsandgateways.gateway.transformation;

//
// Interface for the transformation module.
//
// @see ~GatewayTransformation
//
// @author Till Steinbach, Timo Haeckel
//
moduleinterface IGatewayTransformation
{
    parameters:
        //Path of the gateway configuration xml file
        xml configXML;
        
        //Gateway ID in gateway config file. If auto or empty the gateway module name will be used.
        string gatewayID;
        
    gates:
        input in;
        output out;
}
