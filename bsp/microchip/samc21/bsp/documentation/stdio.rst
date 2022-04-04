STDIO redirection
=================

The STDIO redirection provides means to redirect standard input/output to HAL
IO.

On initialization, the HAL IO descriptor is assigned so that all input and
output is redirected to access it. The IO descriptor can also be changed
through stdio_io_set_io(). All stdin or stdout access is redirected to the
IO descriptor. When the IO descriptor is set to NULL, all input and output 
are discarded.

For GCC redirection, the stdout and stdin buffer are turned off, the
standard _read() and _write() are overridden.

For IAR redirection, the __read() and __write() are overridden.

For Keil redirection, the Retarget.c are modified to override fputc(), fgetc(),
etc.

Features
--------

* Standard input/output redirection (e.g., printf to EDBG COM port)

Dependencies
------------

* HAL IO driver

Limitations
-----------

* IO read/write operation should be synchronous
