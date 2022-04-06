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

#ifndef SIGNALSANDGATEWAYS_NOTRANSFORMATION_H_
#define SIGNALSANDGATEWAYS_NOTRANSFORMATION_H_

//SignalsAndGateways
#include "signalsandgateways/base/SignalsAndGateways_Defs.h"

namespace SignalsAndGateways {

using namespace omnetpp;

/**
 * @brief A transformation module with no functionality besides forwarding incoming frames.
 *
 * @author Till Steinbach
 */
class NoGatewayTransformation : public cSimpleModule
{
  protected:
    /**
     * @brief Initialization of the module.
     */
    virtual void initialize() override;

    virtual void handleMessage(cMessage *msg) override;
};

} //namespace

#endif
