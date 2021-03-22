Guide: RT-Thread & U-Boot & Linux & BuildRoot running on ART-Pi board

To play more fun with art-pi, let's take rt-thread as bootloader running at
internal flash, download u-boot/kernel/rootfs from host to qspi/spi flash,
boot u-boot from qspi flash, then loading kernel to sdram or xip on qspi
flash.

Following steps should be done at first:
1, rt-thread env
2, scons2.x
3, python2.7
4, download cross compile toolchain arm-none-eabi- from
   https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

rt-thread build step:
1, cd bsp/stm32/stm32h750-artpi-h750
2, scons --menuconfig                (update rtconfig.h)
3, source ~/.env/env.sh
4, pkgs --update                     (download fal package)
5, scons

fw/u-boot/kernel install step:
msh >ry                              (download u-boot, ./demo/u-boot)
msh >ry linux                        (download kernel, ./demo/art.itb)

boot kernel:
msh >boot


note:
1, thanks to rt-thread's powerfull hardware enginner ability, we can use
   2M uart baud. to not change common ../library/HAL_xx, so the first log
   you can see is 'BOOT'.
2, there is a bug inside u-boot need to debug futher.(u-boot startup slowly)
3, rootfs on spi flash failed, seems kernel/spi driver working failed.
4, currently art.itb is included with initramfs created from buildroot.

buildroot: username root, no password just press enter



boot log:

BOOT
msh >ry
C
msh >ry linux
C
msh >boot
before jump, 90000000 msp 24040000 psp 200031d0 ctl 0


U-Boot 2021.04-rc3-00160-g3727ffa (Mar 22 2021 - 11:50:15 +0800)

Model: RT-Thread STM32H750i-Art-Pi board
DRAM:  32 MiB
MMC:   STM32 SD/MMC: 0
In:    serial@40004c00
Out:   serial@40004c00
Err:   serial@40004c00
Hit SPACE in 3 seconds to stop autoboot.
## Loading kernel from FIT Image at 90080000 ...
   Using 'conf-1' configuration
   Trying 'kernel' kernel subimage
     Description:  Vanilla Linux kernel
     Type:         Kernel Image
     Compression:  uncompressed
     Data Start:   0x900800e8
     Data Size:    4804648 Bytes = 4.6 MiB
     Architecture: ARM
     OS:           Linux
     Load Address: 0xc0008000
     Entry Point:  0xc0008000
     Hash algo:    crc32
     Hash value:   beeeab64
     Hash algo:    sha1
     Hash value:   b04fc82a06a6c386fa493a36cdd9b131f24c3a25
   Verifying Hash Integrity ... crc32+ sha1+ OK
## Loading fdt from FIT Image at 90080000 ...
   Using 'conf-1' configuration
   Trying 'fdt-1' fdt subimage
     Description:  Flattened Device Tree blob
     Type:         Flat Device Tree
     Compression:  uncompressed
     Data Start:   0x90515238
     Data Size:    16423 Bytes = 16 KiB
     Architecture: ARM
     Hash algo:    crc32
     Hash value:   7426cdac
     Hash algo:    sha1
     Hash value:   865934e6bed5f8e611e6d14f7226c628ab343fa7
   Verifying Hash Integrity ... crc32+ sha1+ OK
   Booting using the fdt blob at 0x90515238
   Loading Kernel Image
   Loading Device Tree to c17f8000, end c17ff026 ... OK

Starting kernel ...

[    0.000000] Booting Linux on physical CPU 0x0
[    0.000000] Linux version 5.12.0-rc2-28712-gbce82a062e70-dirty (fmin@fmin-OptiPlex-7060) (arm-none-eabi-gcc (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.2.1 20201103 (release), GNU ld (GNU Arm Embedded Toolchain 10-2020-q4-major)1
[    0.000000] CPU: ARMv7-M [411fc271] revision 1 (ARMv7M), cr=00000000
[    0.000000] CPU: PIPT / VIPT nonaliasing data cache, PIPT instruction cache
[    0.000000] OF: fdt: Machine model: RT-Thread STM32H750i-ART-PI board
[    0.000000] Reserved memory: created DMA memory pool at 0xc1f00000, size 1 MiB
[    0.000000] OF: reserved mem: initialized node linux,cma, compatible id shared-dma-pool
[    0.000000] Zone ranges:
[    0.000000]   Normal   [mem 0x00000000c0000000-0x00000000c1efffff]
[    0.000000] Movable zone start for each node
[    0.000000] Early memory node ranges
[    0.000000]   node   0: [mem 0x00000000c0000000-0x00000000c1efffff]
[    0.000000] Initmem setup node 0 [mem 0x00000000c0000000-0x00000000c1efffff]
[    0.000000] On node 0 totalpages: 7936
[    0.000000]   Normal zone: 62 pages used for memmap
[    0.000000]   Normal zone: 0 pages reserved
[    0.000000]   Normal zone: 7936 pages, LIFO batch:0
[    0.000000] pcpu-alloc: s0 r0 d32768 u32768 alloc=1*32768
[    0.000000] pcpu-alloc: [0] 0
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 7874
[    0.000000] Kernel command line: console=ttySTM0,2000000 root=/dev/ram loglevel=8
[    0.000000] Dentry cache hash table entries: 4096 (order: 2, 16384 bytes, linear)
[    0.000000] Inode-cache hash table entries: 2048 (order: 1, 8192 bytes, linear)
[    0.000000] mem auto-init: stack:off, heap alloc:off, heap free:off
[    0.000000] Memory: 23864K/31744K available (3973K kernel code, 495K rwdata, 1460K rodata, 1208K init, 148K bss, 7880K reserved, 0K cma-reserved)
[    0.000000] SLUB: HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] rcu: Preemptible hierarchical RCU implementation.
[    0.000000] rcu:     RCU event tracing is enabled.
[    0.000000]  Trampoline variant of Tasks RCU enabled.
[    0.000000] rcu: RCU calculated value of scheduler-enlistment delay is 10 jiffies.
[    0.000000] NR_IRQS: 16, nr_irqs: 16, preallocated irqs: 16
[    0.000000] /soc/interrupt-controller@58000000: bank0
[    0.000000] /soc/interrupt-controller@58000000: bank1
[    0.000000] /soc/interrupt-controller@58000000: bank2
[    0.000000] random: get_random_bytes called from start_kernel+0x1e9/0x364 with crng_init=0
[    0.000000] clocksource: arm_system_timer: mask: 0xffffff max_cycles: 0xffffff, max_idle_ns: 29863442 ns
[    0.000000] ARM System timer initialized as clocksource
[    0.000026] sched_clock: 32 bits at 62MHz, resolution 16ns, wraps every 34359738360ns
[    0.000285] timer@40000c00: STM32 sched_clock registered
[    0.000417] Switching to timer-based delay loop, resolution 16ns
[    0.000518] timer@40000c00: STM32 delay timer registered
[    0.000644] clocksource: timer@40000c00: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 30580167144 ns
[    0.000862] /soc/timer@40000c00: STM32 clockevent driver initialized (32 bits)
[    0.003320] Console: colour dummy device 80x30
[    0.003711] Calibrating delay loop (skipped), value calculated using timer frequency.. 125.00 BogoMIPS (lpj=625000)
[    0.003924] pid_max: default: 4096 minimum: 301
[    0.005077] Mount-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[    0.005378] Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
[    0.021073] rcu: Hierarchical SRCU implementation.
[    0.029063] devtmpfs: initialized
[    0.093875] DMA: default coherent area is set
[    0.094108] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
[    0.094465] pinctrl core: initialized pinctrl subsystem
[    0.104166] NET: Registered protocol family 16
[    0.207442] stm32h743-pinctrl soc:pin-controller: No package detected, use default one
[    0.218643] stm32h743-pinctrl soc:pin-controller: GPIOA bank added
[    0.224470] stm32h743-pinctrl soc:pin-controller: GPIOB bank added
[    0.230179] stm32h743-pinctrl soc:pin-controller: GPIOC bank added
[    0.237484] stm32h743-pinctrl soc:pin-controller: GPIOD bank added
[    0.243952] stm32h743-pinctrl soc:pin-controller: GPIOE bank added
[    0.249632] stm32h743-pinctrl soc:pin-controller: GPIOF bank added
[    0.256349] stm32h743-pinctrl soc:pin-controller: GPIOG bank added
[    0.261812] stm32h743-pinctrl soc:pin-controller: GPIOH bank added
[    0.268104] stm32h743-pinctrl soc:pin-controller: GPIOI bank added
[    0.273581] stm32h743-pinctrl soc:pin-controller: GPIOJ bank added
[    0.280050] stm32h743-pinctrl soc:pin-controller: GPIOK bank added
[    0.280394] stm32h743-pinctrl soc:pin-controller: Pinctrl STM32 initialized
[    0.446906] stm32-dma 40020000.dma-controller: STM32 DMA driver registered
[    0.461388] stm32-dma 40020400.dma-controller: STM32 DMA driver registered
[    0.483491] stm32-mdma 52000000.dma-controller: STM32 MDMA driver registered
[    0.508945] Bluetooth: Core ver 2.22
[    0.509821] NET: Registered protocol family 31
[    0.509997] Bluetooth: HCI device and connection manager initialized
[    0.510208] Bluetooth: HCI socket layer initialized
[    0.510387] Bluetooth: L2CAP socket layer initialized
[    0.510753] Bluetooth: SCO socket layer initialized
[    0.514469] clocksource: Switched to clocksource timer@40000c00
[    0.648874] NET: Registered protocol family 2
[    0.656646] tcp_listen_portaddr_hash hash table entries: 512 (order: 0, 4096 bytes, linear)
[    0.657110] TCP established hash table entries: 1024 (order: 0, 4096 bytes, linear)
[    0.657356] TCP bind hash table entries: 1024 (order: 0, 4096 bytes, linear)
[    0.657566] TCP: Hash tables configured (established 1024 bind 1024)
[    0.658823] UDP hash table entries: 256 (order: 0, 4096 bytes, linear)
[    0.659163] UDP-Lite hash table entries: 256 (order: 0, 4096 bytes, linear)
[    0.661006] NET: Registered protocol family 1
[    2.554732] random: fast init done
[    4.733734] Initialise system trusted keyrings
[    4.736051] workingset: timestamp_bits=30 max_order=13 bucket_order=0
[    4.786790] jffs2: version 2.2. (NAND) ▒© 2001-2006 Red Hat, Inc.
[    5.310040] Key type asymmetric registered
[    5.310288] Asymmetric key parser 'x509' registered
[    5.310634] io scheduler mq-deadline registered
[    5.310796] io scheduler kyber registered
[    5.316971] STM32 USART driver initialized
[    5.321119] 40004800.serial: ttySTM1 at MMIO 0x40004800 (irq = 30, base_baud = 3906250) is a stm32-usart
[    5.331415] 40004c00.serial: ttySTM0 at MMIO 0x40004c00 (irq = 31, base_baud = 3906250) is a stm32-usart
[    5.401958] printk: console [ttySTM0] enabled
[    5.405786] stm32-usart 40004c00.serial: rx dma alloc failed
[    5.406520] stm32-usart 40004c00.serial: interrupt mode used for rx (no dma)
[    5.407322] stm32-usart 40004c00.serial: tx dma alloc failed
[    5.407948] stm32-usart 40004c00.serial: interrupt mode used for tx (no dma)
[    5.431340] spi_stm32 40013000.spi: spurious IT (sr=0x00000002, ier=0x00000000)
[    6.445667] spi-nor spi0.0: w25q128 (16384 Kbytes)
[    6.446504] 1 fixed-partitions partitions found on MTD device spi0.0
[    6.447236] Creating 1 MTD partitions on "spi0.0":
[    6.447813] 0x000000000000-0x000001000000 : "root filesystem"
[    6.467611] spi_stm32 40013000.spi: driver initialized
[    6.473000] Broadcom 43xx driver loaded [ Features: NS ]
[    6.474298] Broadcom 43xx-legacy driver loaded [ Features: ID ]
[    6.480611] i2c /dev entries driver
[    6.483671] Bluetooth: HCI UART driver ver 2.3
[    6.484232] Bluetooth: HCI UART protocol H4 registered
[    8.523743] mmci-pl18x 52007000.mmc: mmc0: PL180 manf 53 rev1 at 0x52007000 irq 50,0 (pio)
[   10.593288] mmci-pl18x 48022400.mmc: mmc1: PL180 manf 53 rev1 at 0x48022400 irq 51,0 (pio)
[   10.641770] ipip: IPv4 and MPLS over IPv4 tunneling driver
[   10.648950] gre: GRE over IPv4 demultiplexor driver
[   10.649572] ip_gre: GRE over IPv4 tunneling driver
[   10.672581] NET: Registered protocol family 10
[   10.688992] Segment Routing with IPv6
[   10.690162] sit: IPv6, IPv4 and MPLS over IPv4 tunneling driver
[   10.698348] NET: Registered protocol family 17
[   10.700453] Bluetooth: RFCOMM TTY layer initialized
[   10.701171] Bluetooth: RFCOMM socket layer initialized
[   10.701949] Bluetooth: RFCOMM ver 1.11
[   10.702516] Bluetooth: HIDP (Human Interface Emulation) ver 1.2
[   10.703287] Bluetooth: HIDP socket layer initialized
[   10.706219] Loading compiled-in X.509 certificates
[   10.926267] cfg80211: Loading compiled-in X.509 certificates for regulatory database
[   10.944106] cfg80211: Loaded X.509 cert 'sforshee: 00b28ddf47aef9cea7'
[   10.947072] platform regulatory.0: Direct firmware load for regulatory.db failed with error -2
[   10.948194] cfg80211: failed to load regulatory.db
[   10.971325] Freeing unused kernel memory: 1208K
[   10.971966] This architecture does not have kernel memory protection.
[   10.972783] Run /init as init process
[   10.973166]   with arguments:
[   10.973494]     /init
[   10.973751]   with environment:
[   10.974105]     HOME=/
[   10.974371]     TERM=linux
Saving random seed: [   11.919582] random: dd: uninitialized urandom read (512 bytes read)
OK

Welcome to Buildroot
buildroot login: root
Jan  1 00:00:14 login[79]: root login on 'console'
~ # ls /dev
console     mtd0ro      tty15       tty30       tty46       tty61
fd          mtdblock0   tty16       tty31       tty47       tty62
full        null        tty17       tty32       tty48       tty63
gpiochip0   pts         tty18       tty33       tty49       tty7
gpiochip1   random      tty19       tty34       tty5        tty8
gpiochip10  shm         tty2        tty35       tty50       tty9
gpiochip2   stderr      tty20       tty36       tty51       ttySTM0
gpiochip3   stdin       tty21       tty37       tty52       ttySTM1
gpiochip4   stdout      tty22       tty38       tty53       ubi_ctrl
gpiochip5   tty         tty23       tty39       tty54       urandom
gpiochip6   tty0        tty24       tty4        tty55       vcs
gpiochip7   tty1        tty25       tty40       tty56       vcs1
gpiochip8   tty10       tty26       tty41       tty57       vcsa
gpiochip9   tty11       tty27       tty42       tty58       vcsa1
kmsg        tty12       tty28       tty43       tty59       vcsu
mem         tty13       tty29       tty44       tty6        vcsu1
mtd0        tty14       tty3        tty45       tty60       zero
~ # ps
  PID USER       VSZ STAT COMMAND
    1 root       432 S    init
    2 root         0 SW   [kthreadd]
    3 root         0 IW<  [rcu_gp]
    4 root         0 IW<  [rcu_par_gp]
    5 root         0 IW   [kworker/0:0-pm]
    6 root         0 IW<  [kworker/0:0H-ev]
    7 root         0 IW   [kworker/u2:0-ev]
    8 root         0 IW<  [mm_percpu_wq]
    9 root         0 SW   [rcu_tasks_kthre]
   10 root         0 SW   [ksoftirqd/0]
   11 root         0 IW   [rcu_preempt]
   12 root         0 SW   [kdevtmpfs]
   13 root         0 IW<  [inet_frag_wq]
   14 root         0 DW   [kworker/0:1+eve]
   15 root         0 IW<  [writeback]
   44 root         0 IW<  [kblockd]
   45 root         0 SW   [watchdogd]
   46 root         0 IW<  [kworker/0:1H]
   47 root         0 IW<  [cfg80211]
   48 root         0 SW   [kswapd0]
   50 root         0 SW   [irq/32-40013000]
   51 root         0 SW   [spi0]
   52 root         0 SW   [irq/50-mmci-pl1]
   53 root         0 DW   [kworker/0:2+eve]
   54 root         0 SW   [irq/51-mmci-pl1]
   55 root         0 IW   [kworker/0:3-eve]
   56 root         0 IW<  [ipv6_addrconf]
   57 root         0 SW<  [krfcommd]
   60 root         0 SW   [irq/31-40004c00]
   79 root       440 S    -sh
   80 root         0 IW   [kworker/u2:1-ev]
   82 root       428 R    ps
~ # [  222.374880] random: crng init done

