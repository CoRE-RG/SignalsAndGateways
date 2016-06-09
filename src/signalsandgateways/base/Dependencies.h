
//INET
#include "inet/common/INETDefs.h"
//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
//FiCo4OMNeT
#include "fico4omnet/base/FiCo4OMNeT_Defs.h"

#include "../features.h"

/**
 * Check for minimal OMNeT++ Version requirements
 */
#if OMNETPP_VERSION < 0x0500
#  error At least OMNeT++/OMNEST version 5.0 required
#endif

/**
 * Check for minimal INET Version requirements
 */
#if INET_VERSION < 0x0303
#  error At least INET version 3.3 required
#endif

/**
 * Check for minimal CoRE4INET Version requirements
 */
#if CORE4INET_VERSION < 0x0100
#  error At least CoRE4INET version 1.0 required
#endif

/**
 * Check for minimal FiCo4OMNeT Version requirements
 */
#if FICO4OMNET_VERSION < 0x0100
#  error At least FICO4OMNET version 1.0 required
#endif


/**
 * Check for feature availability
 */

#ifndef WITH_ETHERNET
#  error You must enable the Ethernet feature in INET framework
#endif

#ifndef WITH_CAN_COMMON
#  error You must enable the CAN feature in FiCo4OMNeT
#endif

#ifndef WITH_FR_COMMON
#  error You must enable the FlexRay feature in FiCo4OMNeT
#endif

#ifndef WITH_AVB_COMMON
#  error You must enable the AVB feature in CoRE4INET
#endif

#ifndef WITH_AS6802_COMMON
#  error You must enable the AS6802 feature in CoRE4INET
#endif

#ifndef WITH_IEEE8021Q_COMMON
#  error You must enable the IEEE 802.1Q feature in CoRE4INET
#endif
