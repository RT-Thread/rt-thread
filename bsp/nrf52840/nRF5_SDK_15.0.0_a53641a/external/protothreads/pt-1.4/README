Protothreads are extremely lightweight stackless threads designed for
severely memory constrained systems such as small embedded systems or
sensor network nodes. Protothreads can be used with or without an
underlying operating system.

Protothreads provides a blocking context on top of an event-driven
system, without the overhead of per-thread stacks. The purpose of
protothreads is to implement sequential flow of control without
complex state machines or full multi-threading.

Main features:

    * No machine specific code - the protothreads library is pure C
    * Does not use error-prone functions such as longjmp()
    * Very small RAM overhead - only two bytes per protothread
    * Can be used with or without an OS
    * Provides blocking wait without full multi-threading or
      stack-switching
    * Freely available under a BSD-like open source license    

Example applications:

    * Memory constrained systems
    * Event-driven protocol stacks
    * Small embedded systems
    * Sensor network nodes

The protothreads library is released under an open source BSD-style
license that allows for both non-commercial and commercial usage. The
only requirement is that credit is given.

The protothreads library was written by Adam Dunkels <adam@sics.se>
with support from Oliver Schmidt <ol.sc@web.de>.

More information and new versions can be found at the protothreads
homepage:
		     http://www.sics.se/~adam/pt/

Documentation can be found in the doc/ subdirectory.

Two example programs illustrating the use of protothreads can be found
in this directory:

   example-small.c         A small example showing how to use protothreads
   example-buffer.c        The bounded buffer problem with protothreads
   example-codelock.c	   A code lock with simulated key input

To compile the examples, simply run "make".


Adam Dunkels, 3 June 2006
