================================
Ethernet MAC Asynchronous Driver
================================

The Ethernet MAC driver implements a 10/100 Mbps Ethernet MAC compatible with
the IEEE 802.3 standard.

Features
--------

* Initialization/de-initialization
* Enabling/disabling
* Data transfer: transmission, reception
* Enabling/disabling Interrupt
* Notifications about transfer completion and frame received via callbacks
* Address Filter for Specific 48-bit Addresses and Type ID
* Address Filter for Unicast and Multicase Addresses
* Reading/writing PHY registers

Applications
------------

Co-works with thirdpart TCP/IP stacks. E.g., Lwip, Cyclone IP stack.

Dependencies
------------

MAC capable hardware compatible with the IEEE 802.3 standard.

Concurrency
-----------

N/A

Limitations
-----------

N/A

Known issues and workarounds
----------------------------

N/A
