Because of the history issue, flags in fcntl.h, such as O_CREAT, have difference types of value. Some OS use hex flags and others use octal flags.

For RT-Thread, Keil and IAR use octal flags, which is located in the `tcntl/octal` folder; newlib uses hex flags; musl uses octal flags; MSVC uses hex flags but not the standard hex flags (be different from newlib hex flags).

