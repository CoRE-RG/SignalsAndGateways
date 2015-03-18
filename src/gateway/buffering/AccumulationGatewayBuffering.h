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

#ifndef __SIGNALSANDGATEWAYS_ACCUMULATIONGATEWAYBUFFERING_H_
#define __SIGNALSANDGATEWAYS_ACCUMULATIONGATEWAYBUFFERING_H_

#include <omnetpp.h>
#include "CanDataFrame_m.h"
#include "EtherFrame_m.h"


namespace SignalsAndGateways {

/**
 * TODO - Generated class
 */
class AccumulationGatewayBuffering : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    std::map<unsigned int,std::list<cMessage*>> poolMap;
    std::map<unsigned int,time_t> holdUpTimes;

    /**
     *
     */
    void readConfigXML();

    /**
     *
     */
    std::list<cMessage*> getPoolList(unsigned int canID);

    /**
     *
     */
    time_t getHoldUpTimeListForPool();
};

} //namespace

#endif
