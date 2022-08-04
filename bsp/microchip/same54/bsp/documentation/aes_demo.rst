========
AES Demo
========

The example demonstrates how to use different AES modes.

For each mode the example does crypt and decrypt tests.
It crypt predefined plain text and check if the encode output cipher matches
expectation.
It decrypt predefined cipher data and check if the decode output matches
the plain text.

All of the test information and testing results are put to debug console so that
the result can be reviewed.

Drivers & middleware
--------------------
* AES
* STDIO
* Synchronous USART

Default interface settings
--------------------------
* USART

  * No parity
  * 8-bit character size
  * 1 stop bit
  * 9600 baud-rate
