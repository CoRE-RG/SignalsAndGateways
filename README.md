# SignalsAndGateways

SignalsAndGateways using [CoRE4INET](https://github.com/CoRE-RG/CoRE4INET), [INET](https://inet.omnetpp.org/) and [FiCo4OMNeT](https://github.com/CoRE-RG/FiCo4OMNeT) to enable a heterogeneous network simulation in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It includes gateway components to enable communication between Ethernet and bus technologies.

<img src="/doc/images/signalsandgateways.png" alt="SignalsAndGateways Environment" width="75%">


## Quick Start
1. Download OMNeT++ 5.4.1
    * [https://omnetpp.org/download/old](https://omnetpp.org/download/old)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.6.5
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
<a href="https://jenkins.core-rg.de/job/SignalsAndGateways/job/SignalsAndGateways/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways"></a>
* Tests:
<a href="https://jenkins.core-rg.de/job/SignalsAndGateways/job/SignalsAndGateways_tests/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways_tests"></a>

<table>
  <tr>
    <th></th>
    <th>Ubuntu 18.04</th>
    <th>Windows 10</th>
  </tr>
  <tr>
    <td>Building</td>
    <td><a href="https://jenkins.core-rg.de/job/SignalsAndGateways/job/SignalsAndGateways/Nodes=Ubuntu_18.04/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways/Nodes=Ubuntu_18.04"></a></td>
    <td><a href="https://jenkins.core-rg.de/job/SignalsAndGateways/job/SignalsAndGateways/Nodes=Windows_10/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways/Nodes=Windows_10"></a></td>
  </tr>
  <tr>
    <td>Tests</td>
    <td><a href="https://jenkins.core-rg.de/job/SignalsAndGateways/job/SignalsAndGateways_tests/Nodes=Ubuntu_18.04/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways_tests/Nodes=Ubuntu_18.04"></a></td>
    <td><a href="https://jenkins.core-rg.de/job/SignalsAndGateways/job/SignalsAndGateways_tests/Nodes=Windows_10/lastBuild/"><img src="https://jenkins.core-rg.de/buildStatus/icon?job=SignalsAndGateways/SignalsAndGateways_tests/Nodes=Windows_10"></a></td>
  </tr>
</table>

For further informations please see [INSTALL](/INSTALL) and [doc/](/doc)
