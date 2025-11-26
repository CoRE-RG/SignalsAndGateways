# SignalsAndGateways

SignalsAndGateways using [CoRE4INET](https://github.com/CoRE-RG/CoRE4INET), [INET](https://inet.omnetpp.org/) and [FiCo4OMNeT](https://github.com/CoRE-RG/FiCo4OMNeT) to enable a heterogeneous network simulation in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It includes gateway components to enable communication between Ethernet and bus technologies.

<img src="/doc/images/signalsandgateways.png" alt="SignalsAndGateways Environment" width="75%">


## Features
At the current state it is possible to exchange data between CAN, Ethernet, TTEthernet and IEEE 802.1Q.
A gateway provides the possibility to select or implement different strategies how incoming frames should be handled. For example it is possible to transmit several CAN-frames within a single Ethernet-frame while important messages are transmitted alone to provide a fast transmission.


## Reference
If you would like to reference this project please use the following [publication](https://link.springer.com/chapter/10.1007/978-3-030-12842-5_10):

Philipp Meyer, Franz Korf, Till Steinbach, Thomas C. Schmidt, Simulation of Mixed Critical In-vehicular Networks, In: Recent Advances in Network Simulation, (Antonio Virdis, Michael Kirsche Ed.), ser. EAI/Springer Innovations in Communication and Computing, May 2019. [https://doi.org/10.1007/978-3-030-12842-5_10](https://doi.org/10.1007/978-3-030-12842-5_10) 

* [arXiv preprint](https://arxiv.org/abs/1808.03081)


## Quick Start
1. Download OMNeT++ 6.0.2
    * [https://omnetpp.org/download/](https://omnetpp.org/download/)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
    * Disable the feature 'visualization' and all dependent features (causes build issues)
3. Get INET framework 3.8.5
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
4. Get CoRE frameworks
    * GitHub: Clone [FiCo4OMNeT](https://github.com/CoRE-RG/FiCo4OMNeT), [CoRE4INET](https://github.com/CoRE-RG/CoRE4INET), and this repository and import them in OMNEST/OMNeT++
5. Working with the framework
    * See the documentation in [doc/](/doc)
    * Start the examples in the framework
    

## Status
The project has been tested on Ubuntu 22.04 (+WSL) and Windows 11. 


## Further Information
* [CoRE simulation models overview](https://core-researchgroup.de/projects/simulation.html)
* [Abstract Network Description Language (ANDL) overview](https://core-researchgroup.de/projects/simulation/abstract-network-description-language.html)

### Installation
Please see [INSTALL](/INSTALL)

### Documentation
Please see [doc/](/doc)


## IMPORTANT
The SignalsAndGateways model is under continuous development: new parts are added, bugs are corrected, and so on. We cannot assert that the implementation will work fully according to the specifications. YOU ARE RESPONSIBLE YOURSELF TO MAKE SURE THAT THE MODELS YOU USE IN YOUR SIMULATIONS WORK CORRECTLY, AND YOU'RE GETTING VALID RESULTS.
