======================================
Generic IEEE 802.3 Ethernet PHY Driver
======================================

This software component supply a generic IEEE802.3 Ethernet PHY driver.
The PHY chip should be compliant IEEE 802.3 Ethernet Standard that
supports MDC/MDIO management interface for PHY register configuration.

The management interface specified here provides a simple, two-wire, serial
interface to connect a management entity and a managed PHY for the purposes of
controlling the PHY and gathering status from the PHY. This interface is
referred to as the MII Management Interface.

The management interface consists of a pair of signals that physically
transport the management information across the MII or GMII, a frame format
and a protocol specification for exchanging management frames, and a register
set that can be read and written using these frames. The register definition 
specifies a basic register set with an extension mechanism. The MII uses two
basic registers. The GMII also uses the same two basic registers and adds a
third basic register.

The MII basic register set consists of two registers referred to as the Control
register (Register 0) and the Status register (Register 1). All PHYs that
provide an MII shall incorporate the basic register set. All PHYs that provide
a GMII shall incorporate an extended basic register set consisting of the
Control register (Register 0), Status register (Register 1), and Extended
Status register (Register 15). The status and control functions defined here
are considered basic and fundamental to 100 Mb/s and 1000 Mb/s PHYs.
Registers 2 through 14 are part of the extended register set. The format of
Registers 4 through 10 are defined for the specific Auto-Negotiation protocol
used (Clause 28 or Clause 37). The format of these registers is selected by
the bit settings of Registers 1 and 15.
More information please refer to IEEE Std 802.3 Chapter 22.2.4

Features
--------

* Initialization the Ethernet PHY driver with Ethernet MAC communication
* Setting PHY address
* Reading/Writing register from PHY device
* Setting/Clearing register bit from PHY device
* Enabling/Disabling Power Down
* Restart Auto Negotiation
* Enabling/Disabling Loop Back
* Getting Link Status
* Reset PHY device

Dependencies
------------

* An instance of the Ethernet MAC driver is used by this driver.

Limitations
-----------

N/A
