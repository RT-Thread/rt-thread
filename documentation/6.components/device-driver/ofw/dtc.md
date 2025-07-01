@page page_device_dtc Devicetree Compiler

# Introduction to the DTC

Device Tree Compiler, dtc, takes as input a device-tree in a given format and outputs a device-tree in another format for booting kernels on embedded systems.
Typically, the input format is "dts" (device-tree source), a human readable source format, and creates a "dtb" (device-tree binary), or binary format as output.

> If the dtc tool is not installed on your host system, the dtc module will guide you through the installation.

## Generate DTS

When you have a DTB or FDT file from firmware or another runtime system, you might want to convert it into a DTS file for easier reading.
You can do this in Python or your SConscript file. For example, assuming you have `dummpy.dtb`:

```python
import os, sys

RTT_ROOT = os.getenv('RTT_ROOT')
sys.path.append(RTT_ROOT + '/tools')

from building import *
import dtc

dtc.dtb_to_dts(RTT_ROOT, "dummpy.dtb")
```

This will generate a dummpy.dts in the current directory. If a file with the same name already exists, it will be replaced.
To avoid overwriting, you can specify a different output name:

```python
[...]

dtc.dtb_to_dts(RTT_ROOT, "dummpy.dtb", "dummpy-tmp.dts")
# or
dtc.dtb_to_dts(RTT_ROOT, "dummpy.dtb", dts_name = "dummpy-tmp.dts")
```

## Generate DTB

Before generating a DTB, you may want to review the basics of DTS syntax and structure: [DeviceTree Specification](https://devicetree-specification.readthedocs.io/en/latest/chapter2-devicetree-basics.html)

### Include and Macros

By default, dtc does not support C-style preprocessing (like cpp), but you can use the C preprocessor with your DTS files.
Don't worry — our dtc module already includes this step.

If your DTS file uses dt-bindings headers or macros, you can write something like:

```c
/*
 * Used "#include" if header file need preprocessor,
 * `components/drivers/include` and current directory path is default.
 */
#include <dt-bindings/size.h>
#include "dummy.dtsi"
/* Well, if dtsi is simple, you can use "/include/", it is supported by dtc */
/include/ "chosen.dtsi"

#define MMIO_BASE   0x10000
#define MMIO_SIZE   SIZE_GB
#define MEM_BASE    (MMIO_BASE + MMIO_SIZE)

#ifndef CPU_HARDID
#define CPU_HARDID  0
#endif

#ifndef SOC_INTC
#define SOC_INTC    intc_a
#endif

/ {
    #address-cells = <2>;
    #size-cells = <2>;
    /*
     * Macros after "&" will be replaced,
     * there will affect the interrupt controller in this SoC.
     */
    interrupt-parent = <&SOC_INTC>;

    [...]

    memory {
        /* When there is a calculation, please use "()" to include them */
        reg = <0x0 MEM_BASE 0x0 (3 * SIZE_GB)>;
        device_type = "memory";
    };

    cpus {
        #size-cells = <0>;
        #address-cells = <1>;

        /* Macros after "@" will be replaced */
        cpu0: cpu@CPU_HARDID {
            reg = <CPU_HARDID>;
            device_type = "cpu";
        };
    };

    /* Macros replace support phandle name, too */
    intc_a: intc-a {
        interrupt-controller;
    };

    intc_b: intc-b {
        interrupt-controller;
    };

    [...]
};
```

To generate the DTB:

```python
import os, sys

RTT_ROOT = os.getenv('RTT_ROOT')
sys.path.append(RTT_ROOT + '/tools')

from building import *
import dtc

dtc.dts_to_dtb(RTT_ROOT, ["dummpy.dts"]
```

To append more include paths, for example, SoC DM headers:

```python
[...]

dtc.dts_to_dtb(RTT_ROOT, ["dummpy.dts"], include_paths = ['dm/include', 'firmware'])
```

### Multiple DTB

A single SoC may have different board variants.
Example `dummy.dtsi` (common base):

```c
/* SoC dummy */
/ {
    #address-cells = <2>;
    #size-cells = <2>;
    model = "Dummy SoC Board";

    [...]

    chosen {
        bootargs = "cma=8M coherent_pool=2M";
    };

    reserved-memory {
        #address-cells = <2>;
        #size-cells = <2>;

        isp_shm@100000 {
            reg = <0x0 0x100000 0x0 0x100000>;
        };

        dsp_shm@200000 {
            reg = <0x0 0x200000 0x0 0x100000>;
        };
    };

    dsp {
        status = "okay";
    };

    buddy {
        isp = <&{/reserved-memory/isp_shm@100000}>;
        dsp = <&{/reserved-memory/dsp_shm@200000}>;
    };

    uart0: uart {
        status = "disabled";
    };

    i2c0: i2c {
        status = "okay";
    };

    [...]
};
```

For a vendor-specific variant (Vendor A):

```c
/* vendorA dummy */
#include "dummy.dtsi"

/ {
    /* No phandle name can modify in place */
    chosen {
        bootargs = "console=uart0 cma=8M coherent_pool=2M";
    };
};

/* Reference and modify direct if has phandle name */
&uart0 {
    status = "okay";
    pinctrl-0 = <&uart0_m1>;
};

&i2c0 {
    status = "disabled";
};
```

To remove nodes or properties (Vendor B):

```c
/* vendorB dummy */
#include "dummy.dtsi"

/delete-node/ &dsp_shm;

/ {
    /* Delete in place if no phandle name */
    /delete-node/ dsp;

    /* Delete property */
    buddy {
        /delete-property/ dsp;
    };
};
```

To add new devices (Vendor C):

```c
/* vendorC dummy */
#include "dummy.dtsi"

&i2c0 {
    rtc@0 {
        clock-frequency = <32768>;
    };
};
```

Build all DTBs together:

```python
[...]

dtc.dts_to_dtb(RTT_ROOT, ["dummpy-vendorA.dts", "dummpy-vendorB.dts", "dummpy-vendorC.dts"])
```

This will produce `dummpy-vendorA.dtb`, `dummpy-vendorB.dtb`, and `dummpy-vendorC.dtb`

## Warnings

DTC may produce warnings that are irrelevant or noisy.
To suppress specific warnings:

```python
[...]

dtc.dts_to_dtb(RTT_ROOT, ["dummpy.dts"], ignore_warning = ["simple_bus_reg", "unit_address_vs_reg", "clocks_is_cell", "gpios_property"])
```

Make sure your DTS is valid!

## Raw options

DTC provides additional command-line options (see dtc --help). You can pass raw options like this:

```python
[...]

dtc.dtb_to_dts(RTT_ROOT, "dummpy.dtb", options = "--quiet")
dtc.dts_to_dtb(RTT_ROOT, ["dummpy.dts"], options = "--quiet")
```
