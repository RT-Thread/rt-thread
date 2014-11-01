# C++ support for RT-Thread #

This is the C++ component in RT-Thread RTOS. In order to support C++ language, this component
implement a basic environment, such as new/delete operators.

Because RT-Thread RTOS is used in embedded system mostly, there are some rules for C++ applications:
1. DOES NOT use exception.
2. DOES NOT use Run-Time Type Information (RTTI).
3. Template is discouraged and it easily causes code text large.
4. Static class variables are discouraged. The time and place to call their constructor function could not be precisely controlled and make multi-threaded programming a nightmare.
5. Multiple inheritance is strongly discouraged, as it can cause intolerable confusion.

*NOTE*: For armcc compiler, the libc must be enable.
