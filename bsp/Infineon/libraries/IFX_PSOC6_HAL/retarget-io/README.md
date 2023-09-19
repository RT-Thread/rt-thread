# Retarget IO

### Overview

A utility library to retarget the standard input/output (STDIO) messages to a UART port. With this library, you can directly print messages on a UART terminal using `printf()`. You can specify the TX pin, RX pin, and the baud rate through the `cy_retarget_io_init()` function. The UART HAL object is externally accessible so that you can use it with other UART HAL functions.

**NOTE:** The standard library is not standard in how it treats an I/O stream. Some implement a data buffer by default. The buffer is not flushed until it is full. In that case it may appear that your I/O is not working. You should be aware of how the library buffers data, and you should identify a buffering strategy and buffer size for a specified stream. If you supply a buffer, it must exist until the stream is closed. The following line of code disables the buffer for the standard library that accompanies the GCC compiler:

    setvbuf( stdin, NULL, _IONBF, 0 );

**NOTE:** If the application is built using newlib-nano, by default, floating point format strings (%f) are not supported. To enable this support, you must add `-u _printf_float` to the linker command line.

# RTOS Integration
To avoid concurrent access to the UART peripheral in a RTOS environment, the ARM and IAR libraries use mutexes to control access to stdio streams. For Newlib (GCC_ARM), the mutex must be implemented in _write() and can be enabled by adding `DEFINES+=CY_RTOS_AWARE` to the Makefile. For all libraries, the program must start the RTOS kernel before calling any stdio functions.

### Quick Start
1. Add `#include "cy_retarget_io.h"`
2. Call `cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);`

    `CYBSP_DEBUG_UART_TX` and `CYBSP_DEBUG_UART_RX` pins are defined in the BSP and `CY_RETARGET_IO_BAUDRATE` is set to 115200. You can use a different baud rate if you prefer.

3. Start printing using `printf()`

### Enabling Conversion of '\\n' into "\r\n"
If you want to use only '\\n' instead of "\r\n" for printing a new line using printf(), define the macro `CY_RETARGET_IO_CONVERT_LF_TO_CRLF` using the *DEFINES* variable in the application Makefile. The library will then append '\\r' before '\\n' character on the output direction (STDOUT). No conversion occurs if "\r\n" is already present.

### More information

* [API Reference Guide](https://infineon.github.io/retarget-io/html/index.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)
* [PSoC™ 6 Code Examples using ModusToolbox™ IDE](https://github.com/infineon/Code-Examples-for-ModusToolbox-Software)
* [ModusToolbox™ Software](https://github.com/Infineon/modustoolbox-software)
* [PSoC™ 6 Resources - KBA223067](https://community.cypress.com/docs/DOC-14644)

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2021.
