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

package signalsandgateways.gateway.buffering;

//
// This module buffers incoming frames and groups incoming frames corresponding to the xml configuration. 
//
simple AccumulationGatewayBuffering like IGatewayBuffering
{
    parameters:
    	xml configXML;
    	
    	@signal[poolSizeSignal](type=unsigned long);
    	@statistic[poolMessageSize](title="pool size"; source=poolSizeSignal; record=count,sum,min,max, "vector(last)"; interpolationmode=linear);
    	
    	@signal[totalHoldUpTimeSignal](type=simtime_t);
    	@statistic[totalHoldUpTime](source=totalHoldUpTimeSignal;record=mean,min,max,vector?);
    	
    	@signal[pool*HoldUpTime](type=simtime_t);
    	@statisticTemplate[poolHoldUpTime](title="Pool-Hold-Up-Time ($name)"; record=mean,max,min,vector; interpolationmode=sample-hold);
    gates:
        input in;
        output out;
}
