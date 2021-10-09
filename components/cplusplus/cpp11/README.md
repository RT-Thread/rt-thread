# C++ 11 support for RT-Thread

## Features

Here are some features about rt-thread c++11 threading futures.

- Atomic.
- Conditional variables.
- Clocks.
- Future.
- Mutexes.
- Threads.
- TLS.

## How To Use

Note that using C++ 11 in rt-thread requires modifying some of the files in the toolchain. Before modifying the tool, back up the tool chain.  

1. Enable c++11 support

   ![](figures/Snipaste_2021-09-02_16-00-09.png)

2. Download toolchain GCC 10.2.1:

   ```shell
   gcc version 10.2.1 20201103 (release) (GNU Arm Embedded Toolchain 10-2020-q4-major)
   ```

3. Delete the following files:

   ```shell
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/thread
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/mutex
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/condition_variable
   rm -f toolchain/arm-none-eabi/include/c++/10.2.1/future
   rm -f toolchain/arm-none-eabi/include/pthread.h
   ```

4. Clear the contents of the following files and keep them to prevent compilation failures:

   ```shell
   toolchain/arm-none-eabi/include/sys/_pthreadtypes.h
   ```
   
5. Update `rtconfig.py` file. add compilation parameters:

   ```shell
   CXXFLAGS = CFLAGS  + ' -std=c++11 -fabi-version=0 -MMD -MP -MF'
   ```
