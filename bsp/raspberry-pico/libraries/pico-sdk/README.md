# Pico SDK

The Pico SDK provides the headers, libraries and build system
necessary to write programs for the RP2040 based devices such as the Raspberry Pi Pico
in C, C++ or assembly language.

The Pico SDK  is designed to provide an API and programming environment that is familiar both to non-embedded C developers and embedded C developers alike.
A single program runs on the device at a time and starts with a conventional `main()` method. Standard C/C++ libraries are supported along with
C level libraries/APIs for accessing all of the RP2040's hardware include PIO (Programmable IO)

Additionally the Pico SDK provides higher level libraries for dealing with timers, synchronization, USB (TinyUSB) and multi-core programming 
along with various utilities.

The Pico SDK can be used to build anything from simple applications, full fledged runtime environments such as MicroPython, to low level software
such as RP2040's on chip bootrom itself.

Additional libraries/APIs that are not yet ready for inclusion in the Pico SDK can be found in [pico-extras](https://github.com/raspberrypi/pico-extras).   

# Documentation

See [Getting Started with the Raspberry Pi Pico](https://rptl.io/pico-get-started) for information on how to setup your
hardware, IDE/environment and for how to build and debug software for the Raspberry Pi Pico
and other RP2040 based devices.

See [Pico C/C++ SDK](https://rptl.io/pico-c-sdk) to learn more about programming using the
Pico SDK, exploring more advanced features, and complete PDF based API documentation.

See [Online Pico SDK API docs](https://rptl.io/pico-doxygen) for HTML based API documentation.

# Example code

See [pico-examples](https://github.com/raspberrypi/pico-examples) for example code you can build.

# Quick-start your own project

These instructions are exteremly terse, and Linux based only. For detailed steps,
instructions for other platforms, and just in general, we recommend you see [Pico C/C++ SDK](https://rptl.io/pico-c-sdk)

1. Install CMake (at least version 3.12), and GCC cross compiler
   ```
   sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi
   ```
1. Set up your project to point to use the Pico SDK
   
   * By cloning the Pico SDK locally (most common)
      1. `git clone` this Pico SDK repository
      1. Copy [pico_sdk_import.cmake](https://github.com/raspberrypi/pico-sdk/blob/master/external/pico_sdk_import.cmake)
         from the SDK into your project directory
      2. Set `PICO_SDK_PATH` to the SDK location in your environment, or pass it (`-DPICO_SDK_PATH=`) to cmake later.
      3. Setup a `CMakeLists.txt` like:

          ```cmake
          cmake_minimum_required(VERSION 3.12)

          # initialize the SDK based on PICO_SDK_PATH
          # note: this must happen before project()
          include(pico_sdk_import.cmake)

          project(my_project)

          # initialize the Pico SDK
          pico_sdk_init()

          # rest of your project

          ```

   * With Pico SDK as a submodule
      1. Clone the SDK as a submodule called `pico-sdk`
      1. Setup a `CMakeLists.txt` like:

          ```cmake
          cmake_minimum_required(VERSION 3.12)

          # initialize pico_sdk from submodule
          # note: this must happen before project()
          include(pico-sdk/pico_sdk_init.cmake)

          project(my_project)

          # initialize the Pico SDK
          pico_sdk_init()

          # rest of your project

          ```

   * With automatic download from github
      1. Copy [pico_sdk_import.cmake](https://github.com/raspberrypi/pico-sdk/blob/master/external/pico_sdk_import.cmake)
         from the SDK into your project directory
      1. Setup a `CMakeLists.txt` like:

          ```cmake
          cmake_minimum_required(VERSION 3.12)

          # initialize pico_sdk from GIT
          # (note this can come from environment, CMake cache etc)
          set(PICO_SDK_FETCH_FROM_GIT on)

          # pico_sdk_import.cmake is a single file copied from this SDK
          # note: this must happen before project()
          include(pico_sdk_import.cmake)

          project(my_project)

          # initialize the Pico SDK
          pico_sdk_init()

          # rest of your project

          ```

3. Setup a CMake build directory.
      For example, if not using an IDE:
      ```
      $ mkdir build
      $ cd build
      $ cmake ..
      ```

4. Write your code (see [pico-examples](https://github.com/raspberrypi/pico-examples) or the [Pico C/C++ SDK](https://rptl.io/pico-c-sdk) documentation
for more information)

   About the simplest you can do is a single source file (e.g. hello_world.c)

   ```c
   #include <stdio.h>
   #include "pico/stdlib.h"

   int main() {
       setup_default_uart();
       printf("Hello, world!\n");
       return 0;
   }
   ```
   And add the following to your `CMakeLists.txt`:

   ```cmake
   add_executable(hello_world
       hello_world.c
   )

   # Add pico_stdlib library which aggregates commonly used features
   target_link_libraries(hello_world pico_stdlib)

   # create map/bin/hex/uf2 file in addition to ELF.
   pico_add_extra_outputs(hello_world)
   ```

   Note this example uses the default UART for _stdout_; 
   if you want ot use the default USB see the [hello-usb](https://github.com/raspberrypi/pico-examples/tree/master/hello_world/usb) example.


5. Make your target from the build directory you created.
      ```sh
      $ make hello_world
      ```

6. You now have `hello_world.elf` to load via a debugger, or `hello_world.uf2` that can be installed and
run on your Raspberry Pi Pico via drag and drop.
