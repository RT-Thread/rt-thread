# Boot Loader

The boot loader is a small piece of code that can be programmed at the
beginning of flash to act as an application loader as well as an update
mechanism for an application running on a MSP432E4 microcontroller, utilizing
either UART0, I2C0, SSI0, Ethernet or USB.  The capabilities of the boot loader
are configured via the bl_config.h include file (which is located in the
application directory, not in the boot loader source directory).
