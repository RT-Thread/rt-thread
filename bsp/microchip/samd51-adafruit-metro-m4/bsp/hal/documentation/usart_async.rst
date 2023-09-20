The USART Asynchronous Driver
=============================

The universal synchronous and asynchronous receiver and transmitter
(USART) is usually used to transfer data from one device to the other.

The USART driver use a ring buffer to store received data. When the USART
raise the data received interrupt, this data will be stored in the ring buffer
at the next free location. When the ring buffer is full, the next reception
will overwrite the oldest data stored in the ring buffer. There is one
USART_BUFFER_SIZE macro per used hardware instance, e.g. for SERCOM0 the macro
is called SERCOM0_USART_BUFFER_SIZE.

On the other hand, when sending data over USART, the data is not copied to an
internal buffer, but the data buffer supplied by the user is used. The callback
will only be generated at the end of the buffer and not for each byte.

User can set action for flow control pins by function usart_set_flow_control,
if the flow control is enabled. All the available states are defined in union
usart_flow_control_state.

Note that user can set state of flow control pins only if automatic support of
the flow control is not supported by the hardware.

Features
--------

* Initialization/de-initialization
* Enabling/disabling
* Control of the following settings:

  * Baudrate
  * UART or USRT communication mode
  * Character size
  * Data order
  * Flow control
* Data transfer: transmission, reception
* Notifications about transfer done or error case via callbacks
* Status information with busy state and transfer count

Applications
------------

They are commonly used in a terminal application or low-speed communication
between devices.

Dependencies
------------

USART capable hardware, with interrupt on each character is sent or
received.

Concurrency
-----------

Write buffer should not be changed while data is being sent.


Limitations
-----------

* The driver does not support 9-bit character size.
* The "USART with ISO7816" mode can be only used in ISO7816 capable devices. 
  And the SCK pin can't be set directly. Application can use a GCLK output PIN
  to generate SCK. For example to communicate with a SMARTCARD with ISO7816
  (F = 372 ; D = 1), and baudrate=9600, the SCK pin output frequency should be
  config as 372*9600=3571200Hz. More information can be refer to ISO7816 Specification.

Known issues and workarounds
----------------------------

N/A
