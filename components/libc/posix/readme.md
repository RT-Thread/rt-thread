This folder provides functions that are not part of the standard C library but are part of the POSIX.1 (IEEE Standard 1003.1) standard.



## NOTE

1. For consistency of compilation results across the different of platforms(gcc, keil, iar) , use:
   - `#include <sys/time.h>` to instead of `#include <time.h>`
   - `#include <sys/errno.h>` to instead of `#include <errno.h>`
   - `#include <sys/signal.h>` to instead of `#include <signal.h>`

