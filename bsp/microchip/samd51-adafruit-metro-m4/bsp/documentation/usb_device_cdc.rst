==============
USB Device CDC
==============

USB Device CDC (Communication Device Class)is a part of the USB Device Stack library.
It provides support for Abstract Control Model, which is one of the USB PSTN Device
Models. The device uses both a Data Class interface and a Communication Class interface
for it. For more detailed definition and description about this model, user can refer to
the related chapter in <Universal Serial Bus Communications Class Subclass Specification
for PSTN Devices, Revision 1.2>

Features
--------

* Initialization/de-initialization.
* Data transfer.
* Callbacks management on:

  * Transmission done
  * Reception done
  * Setting a new Line coding
  * Line state changing

Applications
------------

* Used as a vritual serial.


Dependencies
------------

* USB Device Driver
* USB Device Stack Core
* USB Protocol CDC


Limitations
-----------

* Only single instance can be supported, not applied for multiple case.
* The INF and CAT file would be packed in atzip file. User can extract
  them from "./usb/class/cdc/device".
* If user wants to combine CDC with other classes into one device, USB
  Device Stack Composite component should be added from the web page
  rather than USB Device Stack CDC ACM.
