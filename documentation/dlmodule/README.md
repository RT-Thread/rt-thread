# Dynamic Module: dlmodule #

In traditional desktop operating systems, user space and kernel space are separate. The application runs in user space, and the kernel and kernel modules run in kernel space. The kernel module can be dynamically loaded and deleted to extend the kernel functionality.  `dlmodule` is a software component of the dynamic module loading mechanism provided in kernel space of RT-Thread. In versions of RT-Thread v3.1.0, this was also called the `Application Module`. After RT-Thread v3.1.0 and later, it returned to the tradition and was named after the `dynamic module`.

`dlmodule` is more of an ELF format loader. The code segment and data segment of a separately compiled elf file are loaded into memory, and the symbols are parsed and bound to the API address exported by the kernel. The elf files are primarily placed on file systems under RT-Thread.

## Introduction ##

The dynamic module provides a mechanism for dynamically loading program modules for RT-Thread. Because it is also compiled independently of the kernel, it is more flexible to use. In terms of implementation, this is a mechanism to separate the kernel from the dynamic modules. Through this mechanism, the kernel and dynamic modules can be compiled separately, and at runtime, the compiled dynamic modules are loaded into the kernel through the module loader in the kernel.

In the dynamic module of RT-Thread, two formats are currently supported:

* `.mo` is an executable dynamic module that is suffixed with `.mo` when compiled; it can be loaded, and a main thread is automatically created in the system to execute `main()` function in this dynamic module; at the same time, `main(int argc, char**argv)` can also accept arguments on the command line.
* `.so` is a dynamic library compiled with `.so` as a suffix; it can be loaded and resided in memory, and some set of functions is used by other programs (code or dynamic modules in the kernel).

The current RT-Thread architecture supporting dynamic modules mainly includes ARM architecture and x86 architecture, and will be extended to MIPS and RISC-V architecture in the future. The RT-Thread kernel firmware section can use a variety of compiler toolchains, such as GCC, ARMCC, IAR and other toolchains; however, dynamic module partial compilation currently only supports GNU GCC toolchain compilation. Therefore, compiling the RT-Thread module requires downloading GCC tools, such as CodeSourcery's arm-none-eabi toolchain. In general, it's best to use kernel and dynamic modules to compile with the same toolchain (so that it doesn't produce inconsistent behavior in *libc*). In addition, dynamic modules can only be loaded into RAM and used for symbol resolution binding to the API address exported by the kernel. Instead of running directly in XIP mode based on Flash (because Flash can't modify the code segment again).

## Using Dynamic Module ##

When you want to use the dynamic modules in your system, you need to compile a firmware that supports dynamic modules, as well as dynamic modules that need to be run. The following two parts are compiling firmware and compiling dynamic modules.

### Compile Firmware ###

When you want to use the dynamic module, you need to open the corresponding option in the firmware configuration, use menuconfig to open the following configuration:

```c
   RT-Thread Components  --->
       POSIX layer and C standard library  --->
           [*] Enable dynamic module with dlopen/dlsym/dlclose feature
```

Also open the configuration options of the file system:

```c
   RT-Thread Components  --->
        Device virtual file system  --->
               [*] Using device virtual file system
```

The configuration parameters required for dynamic module compilation are set in *rtconfig.py* file corresponding to bsp:

```Python
M_CFLAGS = CFLAGS + '-mlong-calls -fPIC'
M_CXXFLAGS = CXXFLAGS + '-mlong-calls -fPIC'
M_LFLAGS = DEVICE + CXXFLAGS + '-Wl,--gc-sections,-z,max-page-size=0x4' +\
                                '-shared -fPIC -nostartfiles -nostdlib -static-libgcc'
M_POST_ACTION = STRIP + '-R .hash $TARGET\n' + SIZE + '$TARGET \n'
M_BIN_PATH = r'E:\qemu-dev310\fatdisk\root'
```

The relevant explanation is as follows:

* **M_CFLAGS**: C code compilation parameters used in dynamic module compilation, generally compiled here in PIC mode (that is, the code address supports floating mode execution);
- **M_CXXFLAGS**: C++ code compilation parameters used in dynamic module compilation, parameters similar to M_CFLAGS above;
- **M_LFLAGS**: Parameters when the dynamic module is linked. The same is the PIC method, and is linked in a shared library (partial link);
- **M_POST_ACTION**: the action to be performed after the dynamic module is compiled. Here, the elf file is stripped to reduce the size of the elf file.
- **M_BIN_PATH**: When the dynamic module is successfully compiled, whether the corresponding dynamic module file needs to be copied to a unified place;

Basically, these compilation configuration parameters for the ARM9, Cortex-A, and Cortex-M series are the same.

The kernel firmware also exports some function APIs to the dynamic module via  `RTM(function)`. All exported symbols information in firmware can be listed by command A under MSH:

```
list_symbols
```

The `dlmodule` loader also parses the symbols that need to be parsed in the dynamic module according to the symbol table exported here to complete the final binding action.

This symbol table will be placed in a special section named `RTMSymTab`, so the corresponding firmware link script also needs to retain this area, and will not be removed by the linker optimization. You can add the corresponding information in the link script:

```text
/* section information for modules */
. = ALIGN(4);
__rtmsymtab_start = .;
KEEP(*(RTMSymTab))
__rtmsymtab_end = .;
```

Then execute the `scons` under the BSP project directory and generate the firmware without errors. Execute the command in the BSP project directory:

`scons --target=ua -s`

to generate the kernel header file search path and global macro definitions that need to be included when compiling the dynamic module.

### Compile Dynamic Module ###

There is a separate repository on github: [rtthread-apps](https://github.com/RT-Thread/rtthread-apps) , which contains some examples of dynamic modules and dynamic libraries.

Its directory structure is as follows:

| **Directory** | **Description** |
| --- | ---------------- |
| cxx | Demonstrates how to program in C++ using dynamic modules |
| hello | A "hello world" example |
| lib | Example of dynamic library |
| md5 | Generate md5 code for a file |
| tools | *Python/SConscript* scripts required for dynamic module compilation |
| ymodem | Download a file to the file system through the serial port using the YModem protocol |

You can clone this repository locally and compile it with the scons from the command line. For Windows platforms, the ENV tool is recommended.

After entering the console command line, enter the directory where the `rtthread-apps` repo is located (the same, please ensure that the full path of this directory does not contain spaces, Chinese characters, etc.), and set two variables:

* RTT_ROOT: points to the root directory of the RT-Thread code;
- BSP_ROOT: points to the project directory of the BSP;

Use follow commands on Windows in Env tool(assuming the BSP used is qemu-vexpress-a9):

```c
set RTT_ROOT=d:\your_rtthread
set BSP_ROOT=d:\your_rtthread\bsp\qemu-vexpress-a9
```

to set the corresponding environment variable. Then use the following command to compile the dynamic module, such as the hello example:

```
scons --app=hello
```

After compiling successfully, it will generate a `hello.mo` file in the `rtthread-apps/hello` directory.

You can also compile dynamic libraries, such as the lib example:

```
scons --lib=lib
```

After compiling successfully, it will generate the `lib.so` file in the `rtthread-apps/lib` directory.

We can put these `mo` and `so` files under the RT-Thread file system. Under msh, you can simply execute the  `hello.mo`  dynamic module as a `hello` command:

```c
msh />ls
Directory /:
hello.mo            1368
lib.so              1376
msh />hello
msh />Hello, world
```

After calling hello, the main function in `hello.mo` will be executed, and the corresponding dynamic module will be exited after execution. The code for `hello/main.c` is as follows:

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello, world\n");

    return 0;
}
```

## APIs of Dynamic Module

In addition to dynamically loading and executing dynamic modules via msh, dynamic modules can be loaded or unloaded using the dynamic module API provided by RT-Thread in the main program.

### Load Dynamic Module

```c
struct rt_dlmodule *dlmodule_load(const char* pgname);
```

|**Parameter**|**Description**|
| ---- | ---- |
| pgname | Dynamic module path |
|**Return**| ——                               |
| Dynamic module pointer | Successfully loaded |
| RT_NULL | Failed    |

This function loads the dynamic module from the file system into memory, and if it is loaded correctly, returns a pointer to the module. This function does not create a thread to execute this dynamic module, just load the module into memory and parse the symbolic address.

### Execute Dynamic Module

```c
struct rt_dlmodule *dlmodule_exec(const char* pgname, const char* cmd, int cmd_size);
```

|**Parameter**|**Description**|
| ---- | ---- |
| pgname | Dynamic module path |
| cmd | Command line string including the dynamic module command itself |
| cmd_size | Command line string size |
|**Return**| ——                               |
| Dynamic module pointer | Run successfully |
| RT_NULL | Failed    |

This function loads the dynamic module according to the  `pgname` path and starts a thread to execute `main` of the dynamic module. At the same time, `cmd` is passed as the command line Parameter to `main` entry of the dynamic module.

### Exit Dynamic Module

```c
void dlmodule_exit(int ret_code);
```

|**Parameter**|**Description**|
| ---- | ---- |
| ret_code | Module's return parameter |

This function is called by the module runtime, it can set the return value of the module exit `ret_code`, and then exit from the module.

### Find Dynamic Modules

```c
struct rt_dlmodule *dlmodule_find(const char *name);
```

|**Parameter**|**Description**|
| ---- | ---- |
| name | Module name |
|**Return**| ——                 |
| Dynamic module pointer | Successful |
| RT_NULL | Failed    |

This function uses `name` to find out if there is already a dynamic module loaded in the system.

### Return Dynamic Module

```c
struct rt_dlmodule *dlmodule_self(void);
```

|**Return**|**Description**|
| ---- | ---- |
| Dynamic module pointer | Successful |
| RT_NULL | Failed     |

This function returns a pointer of the dynamic module in the calling context.

### Find Symbol

```c
rt_uint32_t dlmodule_symbol_find(const char *sym_str);
```

|**Parameter**|**Description**|
| ---- | ---- |
| sym_str | Symbol name |
|**Return**| ——                 |
| Symbol address | Successful |
| 0 | Failed     |

This function returns the symbol address based on the symbol name.

## Libdl API of POSIX Standard ##

The POSIX standard libdl API is also supported in RT-Thread dlmodule. It is similar to loading a dynamic library into memory (and parsing some of the symbol information). This dynamic library provides the corresponding set of function operations. The libdl API needs to include the header files: `#include <dlfcn.h>`

### Open Dynamic Library

```c
void * dlopen (const char * pathname, int mode);
```

|**Parameter**|**Description**|
| ---- | ---- |
| pathname | Dynamic library path name |
| mode | The mode when opening a dynamic library, not used in RT-Thread |
|**Return**| ——                 |
| Dynamic library handle (`struct dlmodule` structure pointer) | Successful |
| NULL | Failed     |

This function is similar to the `dlmodule_load` , which loads the dynamic library from the file system and returns the handle pointer of the dynamic library.

### Find Symbol

```c
void* dlsym(void *handle, const char *symbol);
```

|**Parameter**|**Description**|
| ---- | ---- |
| handle | Dynamic library handle, return value of `dlopen` |
| symbol | The symbol address to return |
|**Return**| ——                 |
| symbol address | Successful |
| NULL | Failed     |

This function looks in the dynamic library `handle` for the presence of the symbol of `symbol` , if there is an address that returns it.

### Close Dynamic Library

```
int dlclose (void *handle);
```

|**Parameter**|**Description**|
| ---- | ---- |
| handle | Dynamic library handle |
|**Return**| ——         |
| 0     | Successful |
| Negative number | Failed     |

This function closes the dynamic library pointed to by  `handle` and unloads it from memory. It should be noted that when the dynamic library is closed, the symbolic address originally returned by  `dlsym` will no longer be available. If you still try to access it, it may cause a fault error.

## FAQs

Please refer to [*User Manual of Env*](../env/env.md) for issues related to the Env tool.

### Q: Dynamic modules cannot be run successfully according to the documentation.

**A:** Please update the RT-Thread source code to version 3.1.0 and above.

### Q: Compile the project with the scons command, prompting "undefined reference to __rtmsymtab_start".

**A:**  Please refer to the qemu-vexpress-a9 BSP GCC link script file *link.lds* to add the following to the TEXT section of the project's GCC link script.

```
    /* section information for modules */
    . = ALIGN(4);
    __rtmsymtab_start = .;
    KEEP(*(RTMSymTab))
    __rtmsymtab_end = .;
```
