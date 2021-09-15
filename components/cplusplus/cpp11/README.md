# CPP11 support for RT-Thread

## Features

Here are the C++ 11 threading features supported by rt-thread:

- Atomic.
- Conditional variables.
- Mutexes.
- Clocks.
- Threads

## How To Use

1. download the [gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm) toolchain:

   ```
   gcc version 10.2.1 20201103 (release) (GNU Arm Embedded Toolchain 10-2020-q4-major)
   ```

2. remove the following files:

   ```
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/thread
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/mutex
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/condition_variable
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/future
   rm -f toolchain/arm-none-eabi/include/pthread.h
   ```

3. clear the contents of the following files, reserving the files to prevent compilation failures:

   ```
   toolchain/arm-none-eabi/include/sys/_pthreadtypes.h
   ```

4. add c++11 compile parameter:

   ```
   CXXFLAGS = CFLAGS  + ' -std=c++14 -fabi-version=0 -MMD -MP -MF'
   ```
