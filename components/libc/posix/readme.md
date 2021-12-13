This folder provides functions that are not part of the standard C library but are part of the POSIX.1 (IEEE Standard 1003.1) standard.



## NOTE

1. when you use libc interface with gcc platform, you should define ```_POSIX_C_SOURCE```. You can set it ```#define _POSIX_C_SOURCE 200809L``` at the top of this file before you quote some header files.
2. For consistency of compilation results across the different of platforms(gcc, keil, iar) , you better use ``#include <sys/time.h>`` to instead of ``#include <time.h>``.
3. According the different of platform, we realize many interfaces for them. But the number of interfaces that we reailzed for those platform is different.

