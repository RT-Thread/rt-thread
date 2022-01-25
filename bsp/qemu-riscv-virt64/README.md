# QEMU/RISCV64 VIRT BSP Introduction

[中文页](README_ZH.md) | English

RISC-V is a free and open ISA enabling a new era of processor innovation through open standard collaboration. This project ported RT-Thread on QEMU RISCV64 VIRT machine.

## 1. Compiling

Download the cross compiler tool chain, it is recommended to use the sifive tool chain.

```
https://www.sifive.com/software
```

Select the fitting platform, we recommend Ubuntu. 

Unzip the tool chain to the specified directory.

```
export RTT_EXEC_PATH=~/gcc/bin
```

Enter `rt-thread/bsp/qemu-riscv-virt64` directory and input

```
scons
```

 `rtthread.elf` and `rtthread .bin` files are generated. 

## 2. Execution

The project provides two configurable operating modes for riscv64, defaults to run under M-Mode.

***M-Mode***

Firstly, install the `qemu-system-riscv64`.

```
sudo apt install qemu-system-misc
```

Then enter

```
./qemu-nographic.sh
```

You'll see Project start running

```
heap: [0x80035804 - 0x86435804]

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build May 21 2021
 2006 - 2021 Copyright by rt-thread team
Hello RISC-V!
msh />
```

***S-Mode***

When running in S-Mode, configuration is via menuconfig

```
scons --menuconfig
```

Select:

```
RISCV qemu virt64 configs  ---> 
    [*] RT-Thread run in riscv smode
```

Save it and compile `scons`.

To get RT-Thread running in S-Mode, enable the opensbi, and then start up the RT-Thread through opensbi.

Compile qemu or downloaded premiere-version qemu that built-in opensbi, then executing `./qemu-nographic-smode.sh` can get it successfully running.  

The qemu installed with `sudo apt install qemu-system-misc` is an ordinary-version and may compile the opensbi on its own.

```
git clone git@github.com:riscv/opensbi.git
cd opensbi
make PLATFORM=generic CROSS_COMPILE=~/gcc/bin/riscv64-unknown-elf-
```

`/build/platform/generic/firmware/fw_jump.elf` file is generated. 

Enter the following command to run:

```
qemu-system-riscv64 -nographic -machine virt -m 256M -kernel rtthread.bin -bios ~/opensbi/build/platform/generic/firmware/fw_jump.elf
```

Result is shown as follows: 

```
OpenSBI v0.9
   ____                    _____ ____ _____
  / __ \                  / ____|  _ \_   _|
 | |  | |_ __   ___ _ __ | (___ | |_) || |
 | |  | | '_ \ / _ \ '_ \ \___ \|  _ < | |
 | |__| | |_) |  __/ | | |____) | |_) || |_
  \____/| .__/ \___|_| |_|_____/|____/_____|
        | |
        |_|

Platform Name             : riscv-virtio,qemu
Platform Features         : timer,mfdeleg
.
.
.
Boot HART ISA             : rv64imafdcsu
Boot HART Features        : scounteren,mcounteren
Boot HART PMP Count       : 16
Boot HART PMP Granularity : 4
Boot HART PMP Address Bits: 54
Boot HART MHPM Count      : 0
Boot HART MHPM Count      : 0
Boot HART MIDELEG         : 0x0000000000000222
Boot HART MEDELEG         : 0x000000000000b109
heap: [0x80235a58 - 0x86635a58]

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build May 21 2021
 2006 - 2021 Copyright by rt-thread team
Hello RISC-V!
msh />
```

## 3. Condition

| Driver | Condition | Remark |
| ------ | --------- | ------ |
| UART   | Support   | UART0  |
| PLIC   | Support   | -      |
| CLIC   | Support   | -      |