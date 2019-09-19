# SignalsAndGateways

SignalsAndGateways using [CoRE4INET](https://github.com/CoRE-RG/CoRE4INET), [INET](https://inet.omnetpp.org/) and [FiCo4OMNeT](https://github.com/CoRE-RG/FiCo4OMNeT) to enable a heterogeneous network simulation in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It includes gateway components to enable communication between Ethernet and bus technologies.

<img src="/doc/images/signalsandgateways.png" alt="SignalsAndGateways Environment" width="75%">


## News
* Switch to OMNeT++ 5.5.1 and INET 3.6.6


## Quick Start
1. Download OMNeT++ 5.5.1
    * [https://omnetpp.org/download/](https://omnetpp.org/download/)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.6.6
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
4. Install CoRE plugins (optional)
    * OMNEST/OMNeT++ -> Help -> Install New Software...
    * URL `http://sim.core-rg.de/updates/`
    * Check [Abstract Network Description Language] | [CoRE Simulation Model Installer] | [Gantt Chart Timing Analyzer]
5. Get CoRE frameworks (GitHub or CoRE Simulation Model Installer)
    * GitHub: Clone frameworks and import it in OMNEST/OMNeT++
    * CoRE Simulation Model Installer: OMNEST/OMNeT++ -> Help -> Install CoRE Simulation Models...
6. Working with the framework
    * See the documentation in [doc/](/doc)
    * Start the examples in the framework
    

## Continuous Integration

The build state of the master branch is monitored:
* Building:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways"></a>
* Tests:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways_tests"></a>

<table>
  <tr>
    <th></th>
    <th>Ubuntu 18.04</th>
    <th>Windows 10</th>
  </tr>
  <tr>
    <td>Building</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways/Nodes=Windows_10"></td>
  </tr>
  <tr>
    <td>Tests</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways_tests/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways_tests/Nodes=Windows_10"></td>
  </tr>
</table>


## Further Information

### Installation
Please see [INSTALL](/INSTALL)

### Documentation
Please see [doc/](/doc)


## IMPORTANT
The SignalsAndGateways model is under continuous development: new parts are added, bugs are corrected, and so on. We cannot assert that the implementation will work fully according to the specifications. YOU ARE RESPONSIBLE YOURSELF TO MAKE SURE THAT THE MODELS YOU USE IN YOUR SIMULATIONS WORK CORRECTLY, AND YOU'RE GETTING VALID RESULTS.
