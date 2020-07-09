# RT-Thread v4.0.2 Change Log

Change log since v4.0.1

## Kernel

* Split the component automatic initialization to component automatic initialization and main funciton;
* Add spin lock API in SMP mode;
* Fix RT_IDLE_HOOK spelling issue;
* Add thread waiting for message queue when queue is full;
* Fix the issue of delete mq in `rt_mq_create` in some abnormal case;
* Remove the C++ keywords in the`rt_console_set_device`function;
* Remove the `suspend_thread_count` member from memory_pool structure;
* Fix the issue when block = NULL in rt_mp_free;
* Fix the issue of incorrect scheduling task sequence caused by rt_thread_yeild in system scheduling;
* Fix the issue that the interrupt is opened too late and cause the signal handling delayed;
* When disable SMP, `cpu.c` will not be added into project by default;
* Fix the issue that `rt_thread_exit` turned on the interrupt prematurely in the SMP mode, so other cores might delete this task, causing the issue in subsequent function stacks;
* Fix the issue of critical protection when `rt_thread_delete` change the status of thread;

## Components

* Fix the issue of mPool size in C++ / Queue;
* Add the error status return in C++ / Thread task join/wait function;
* Fix compilation warning in DFS/ELM FatFS;
* Add support for Linux NFS Server in DFS/NFS;
* Fix mkfs issue in DFS/UFFS;
* Add ftruncate, flock, getuid, umask APIs;
* Fix the display issue of fd with offset in list_fd command;
* Add `dfs_mount_device` API to mount a file system on a device which is already in mount_table;
* Rename the C++ keywords in DFS/rename function;
* Connnect dfs/poll, select with RT_USING_POSIX in Kconfig;
* Optimize the part of the code of finsh to make it more simple;
* When RT_USING_DEVICE is not used, finsh can use the `rt_hw_console_getchar()` function which is simple to implement and not using the device framework;
* Increase the line length of the finsh shell to more than 256 characters;
* utest can support clang compiler and C++ compiler;
* Fix possible cross-boundary issues in ulog;
* Fix compilation warning in `ulog/ulog_console_backend_output`;
* Add support for file sending and receiving feature in YModem;
* CRC16 can be calculated without the lookup talbe to reduce code size in YModem component;
* Fix the issue that stack may be wrongly released during pthread/destory;
* Fix the possible memory leaks issue which caused by pthread_create abnormal case;
* The timer-related APIs under different compiler of libc are moved to the `libc\compilers\common` folder;
* Remove redundant definitions in `dlib/sys/unistd.h` (which will cause compilation warnings);
* Add `sys/errno.h` and`sys/signal.h` header files under dlib;
* Freemodbus is no longer in the kernel, and split it as a standalone softwre package;
* AT socket updated to v1.3.0:
  - Add multi-client and multi-device function support in AT Socket, and improve the dirty data handling when AT device hardware module reboot;
  - Support netdev network card feature, which can manage and control AT device network connection through the network card interface;
* Improve AT Server function support in AT components, add AT Server data sending and receiving interfaces `at_server_send ()` and `at_server_recv ()`;
* Fix the issue of `closesocket()` in SAL component when socket closing failure after `shutdown()`;
* Improve `sal_bind ()` network card binding related function in SAL component;
* Add IPV6 related options configuration and function support to SAL and netdev;
* Improve ping command error handling and log display in the netdev;
* Add hostname configuration options and functions in lwIP component;
* Fix the assertion issue of `sys_arch_mbox_fetch()` in lwIP which may occur when a socket is closed;
* Add network card uninstallation function and support for dhcpd service stop function to the lwip component;
* Fix lwIP component compilation failure caused by closing FinSH component;
* Fix the issue that the socket may not be closed during the DHCPD task in the lwIP DHCP server;
* Add `dhcpd_stop()` interface;
* Change log in device driver framework:
  * Refactor audio driver framework;
  * Fix the issue that the receiving length is 0 in CAN and the issue of returning wrong values;
  * Add hardware encryption and decryption driver framework;
  * Fix the flag handling issue of `rt_i2c_master_send/rt_i2c_master_recv`;
  * Add input capture and pulse encoding driver framework;
  * Fix the issue that partition lock is deleted when `rt_mmcsd_blk_remove`;
  * Fix the issue that the enumerated capacity of the large-capacity card in MMC/SD exceeded the data range;
  * When the SDIO device is initialized, the function's manufacturer and product can also use the information in CIS;
  * Improve the interrupt mode handling in the sensor framework, and fix the issue that the memory is not released when registering the sensor;
  * More information are provided in command line of sensor framework;
  * Add the checking for Rx buffer size in the serial port framework, and provide a notification when RX buffer full;
  * Remove the old Nor SPI Flash driver in SPI framework, and replace with SFUD component;
  * Fix some judgements issue in the return value of SFUD;
  * Fix the definition warning of `SFUD_FLASH_DEVICE_TABLE` in SFUD;
  * Add support for W25Q64DW devices in SFUD;
  * Fix FiFo creation failure handling when creating a pipe;
  * Fix the issue of releasing RBB in advance in `rt_rbb_destroy()` function;
  * Rename the new keyword using of C++ in `rt_rbb_blk_alloc` function;
  * Unify the `struct rt_delayed_work` in workqueue to `struct rt_work`;
  * Add touch driver framework;
  * Add USB Audio class;
  * Fix RNDIS plug-in/out issue in USB device stack;
  * Add the interface callback function in USB device stack;
  * Improve wlan framework, including command line functions, handling of AP name, password length, support for netdev, better configurability, etc.

## BSP and CPU porting

* Add Clang compiler support in ARM-related CPU porting;
* Fix SCB_AIRCR definition issue in ARM Cortex-M0;
* Add ARM Cortex-M33 porting;
* Add DMB/DSB related operations for cache operations in ARM Cortex-A porting;
* Add FPU support in ARM Cortex-A porting;
* Re-organize MIPS port. And XBurst related porting are moved to X1000 BSP;
* The porting of loongson 1B and 1C CPU are combined into one GS232 porting;
* Add support for RISC-V Hummingbird processor porting;
* The context switch exit operation of risc-v is forced back to machine mode;
* Fix the issue of switch interruption during TI C28x DSP porting; 
* Add _ffs like implementation in the TI C28x DSP porting;
* Unify the .data .bss section to 8bytes alignment in GCC tool chain;
* The es32f0334 BSP is moved to `bsp/essemi/es32f0334`;
* Add `bsp/essemi/es8p508x` BSP, including UART and GPIO drivers;
* Add GD32VF103V-EVAL (RISC-V MCU) BSP, including UART driver;
* Rerange NXP i.MXRT BSP and add related BSP documents;
* Add i.MXRT1052 ATK Commander, Fire Pro BSP and i.MXRT1064 EVK BSP to the new i.MXRT BSP;
* Add BSP for NXP LPC55S6X series, and increase support for NXP official development board LPC55S69-EVK;
* Fix I2C operation (master_xfer) in LPC54114-lite BSP;
* Add Audio driver in LPC54114-lite BSP;
* Update Loongson 1B BSP and use automatic component initialization in default;
* Add Kconfig configuration for Loongson 1B BSP;
* Add QEMU/mipssim BSP for simulate RT-Thread/MIPS without MIPS hardware;
* Refactor qemu-vexpress-a9's Audio driver and fix the issue of OS Tick accuracy;
* Add LPUART driver to RV32M1 VEGA BSP;
* Remove old STM32 BSP: stm32f4xx-HAL, stm32f10x, stm32f10x-HAL, stm32f429-apollo, stm32f429-disco, stm32h743-nucleo;
* Fix the issue of `rt_hw_sci_init()` for opening the global interrupt in tms320f28379d BSP;
* Add support of soft I2C and hardware encryption module to WinnerMicro W60x BSP（AES/DES/3DES/RC/SHA1/MD3/CRC);
* Add oneshot WiFi configuration support in WinnerMicro W60x BSP;
* Add more STM32 BSP based on new STM32 BSP framework:
  * stm32f072-st-nucleo
  * stm32f103-gizwits-gokitv21
  * stm32f103-yf-ufun
  * stm32f412-st-nucleo
  * stm32f427-robomaster-a
  * stm32f429-st-disco
  * stm32f769-st-disco
  * stm32g431-st-nucleo
  * stm32h743-st-nucleo
  * stm32h750-armfly-h7-tool
  * stm32l4r5-st-nucleo
  * stm32l452-st-nucleo
* For the new STM32 BSP framework:
  * Add DMAMUX support to stm32l4+;
  * Update F7 HAL library SConscript;
  * Open the SWD port configuration on cubemx in stm32f103-atk-warshipv3 BSP;
  * Add support for SD card in stm32f427-robomaster-a BSP;
  * Add USBFS driver to stm32f412-nucleo BSP;
  * Remove use of device user data on uart driver;
  * Add QSPI FLASH support in stm32h743-atk-apollo BSP;
  * Optimized Ethernet driver;
  * Add hardware encryption and decryption driver;
  * Add MIPI LCD driver;
  * Add pulse encoding driver;
  * Optimize hardware timer driver;
  * Add support for UART 7/8 in serial driver;
  * Optimize WDT driver; 

## Tools

* Optimize scons script for eclipse in order to generate eclipse project better;
* Improve rtconfig.h generator, PATH type configuration can be generated correctly;
* Fix gcc path detection issue when using the default cross toolchain of the Linux distribution;

# RT-Thread v4.0.1 Change Log

## Kernel

* Fix the `rt_tick_from_millisecond()` compilation warning issue;
* Remove unnecessary code that disable interrupt several times during startup initialization;
* Fix the issue that the system object is not detached when handling defunct threads. 
* Add the value checking of semaphore (the maximum value of semaphore is up to 65535)
* Fix the 64-bit issue in kservice.c
* Add the checking and assertion of re-initialization of object.
* In the rt_enter_critical/rt_exit_critical function, add the checking of whether scheduler is startup or not.
* Fix the signal issue under SMP and the issue of signal information list in signal.
* Add 64-bit processor support in slab memory allocation.
* Fix the definition issue of `ENOTSUP` in libc_errno.h.
* Simplify the rtdbg.h file and use ulog to make log/debug system easier to use.
* Add the configuration of RT_USING_ARCH_DATA_TYPE, `rt_int8_t/.../rt_uint32_t` and other basic data types can be defined by BSP itself. (It is recommended to put them into the rtconfig_project.h file, so that this file can be automatically included in rtconfig.h when menuconfig generates it.)
* Add `RT_Device_Class_Sensor` type devices;
* In the case of single core, the definition of `rt_hw_spin_lock/rt_hw_spin_unlock` is redefined as the disable/enable interrupt.
* Add the `rt_strnlen()` function in kservice.c.
* Support the long long type in rt_kprintf (HubertXie);

## Components

* Remove CMSIS and move to software package as CMSIS package.
* Remove logtrace component. The system log system switches to ulog;
* Add more code to support AC6 tool chain in some BSP and components;
* In DFS file system component, clean up the log and fix the mkfs issue when index may be out of range.
* Split the running mode from sleep mode in power management, and the frequency change should be clearer. Power management is not use idle hook but execute the sleep action in idle thread directly. (How to use power management, please visit programming document for details)
* Cleanup the log of MMC/SD driver framework;
* Rewrite Sensor Framework, replace the original C++ implementation with C version, and add some corresponding sensor software packages; To use the sensor packages, please use this release;
* Add the DMA transmission operation in the serial driver framework;
* Add the consistency protection to tc_flush routine of serial driver (loogg).
* Add rt_sfud_flash_find_by_dev_name API in SFUD.
* When the Pipe device closed, if it is an unnamed Pipe device and the open count is 0, this Pipe device will be deleted.
* The delayed work implementation is added to workqueue, and the workqueue of the system is added as an option.
* Fix the data loss issue when using DMA transmission in USB CDC.
* Change the return type of finsh_getchar to int;
* Fix the errno issue in newlib/GCC tool chain.
* Change the management of pthreads to POSIX thread array instead of mapping pthread_t directly to rt_thread_t; Change the fields definition more similar with newlib/glibc in pthreads.
* Fix the thread name output in ulog.
* Add loop parameter in utest, then executes test cases repeatedly; Add thread parameter in utest to execute testcase in a new thread.
* Add delay in handshake phase to protect incomplete data reception in YModem component.
* Add netdev component, abstract netdev concept, used to management and control network interface device, and provide netdev operation commands, including ping/ifconfig/dns/netstat etc;
* Modify SAL for netdev, that is, adds the judgment of netdev status and information when the socket creating and data transmitting;
* Add options and types for UDP multicast traffic handling and IPPROTO_IP in SAL;
* Fix `itctrol()` function not support to control socketfd issues in SAL;
* Improve error log processing in AT socket;
* Fix serial receive data failed issues when AT client initialization is not completed;

## BSP

* Add ES32 chip BSP from Shanghai Eastsoft Microelectronics Co., Ltd. (EastSoft provides maintenance and support);
* Add GD32E230K-start, with ARM Cortex-M23 core BSP (xuzhuoyi)
* Add IMXRT1021-EVK BSP (NXP provides maintenance and support);
* Add the ETH hardware checksum option in IMXRT1052 ETH driver;
* Add more peripheral drivers, GPIO, LCD, SPI, camera, etc. in Kendryte K210 BSP.
* Cleanup the LPC 4088 BSP to use main function entry and support menuconfig;
* Add LPC1114 BSP with UART driver (SASANO Takayoshi, Japan);
* The double Frame Buffer mechanism and touch screen driver are added in Godson 1C BSP, then it can better to support Persimmon UI (sundm75).
* Add watchdog driver in Godson 1C BSP(sundm75);
* Add MM32 chip BSP from Shanghai MindMotion Microelectronics Co., Ltd. (MindMotion provides maintenance and support);
* Fix the SysTick interrupt handling issue in nRF52832 and add menuconfig configuration file.
* Add QSPI and SPI flash driver to Nuvoton M487 BSP (bluebear 233)
* Change the CPU porting to libcpu/arm/cortex-a folder in QEMU-VExpress A9/IMX6UL BSP;
* In QEMU-VExpress A9 BSP, the MAC address associated with the local MAC address is used for a unified MAC address in the network.
* remove stm32f0x, stm32f7-disco, stm32f107, stm32f40x, stm32l072, stm32l475-iot-disco, stm32l476-nucleo BSP (when the new STM32 BSP can completely replace these old BSP, these BSP will be removed);
* For the new STM32 BSP:
  * Add CAN driver (ylz0923)
  * Add CAN driver to stm32f103-fire-arbitrary (ylz0923)
  * stm32f746-st-disco with LCD, watchdog, SDCard, ethernet, Flash and other drivers (Jinsheng)
* More board support is added to the new STM32 BSP:
  * stm32f103-atk-warship V3 ATK Warship V3 (daizhiwang)
  * STm32f103-dofly-M3S Dofly STM32F103 Development Board
  * stm32f103-mini-system, the minimum system board for STM32F103 (daizhiwang)
  * stm32f401-st-nucleo
  * stm32f405-smdz-breadfruit sanmu electronic stm32405 development board (sunlichao)
  * stm32f469-st-disco
  * stm32h743-atk-apollo (whj4674672)
  * stm32l4r9-st-eval
  * stm32l053-st-nucleo (sun_shine)
  * stm32l475-st-discovery
  * stm32l476-st-nucleo (Vincent-VG)
  * stm32l496-ali-developer

* Add the ARC support for Synopsys Design Ware ARC EM Starter Kit (Synopsys provides maintenance and support);
* The SCI driver is added to the TMS320F28379D BSP (xuzuoyi).
* Add W60X Wi-Fi SoC chip BSP from Winner Microelectronics Co.,Ltd. (Winner Micro and RealThread provide maintenance and support);
* Fix the UART2 IO configuration issue in X1000 UART driver (Zhou Yanjie);
* Add SConscript file for each CPU porting.
* Cleanup the libcpu/arm/cortex-a code;
* The _rt_hw_context_switch_interrupt/_rt_hw_context_switch is separated in TI DSP TMS320F28379D BSP (xuzuoyi);

## Tool

* Add Makefile generation feature in scons with command `scons –target=makefile -s`. Then developer can use make to build RT-Thread under Linux or Windows.
* Add Eclipse project generation feature in scons with command `scons –target=eclipse -s`, which will put the necessary information in `.cproject` and `.project` files in current BSP folder. The developer can use Eclipse to build RT-Thread.
* Fix the multi-group same name issue when generating Keil MDK project file and add a library file into the SConscript (Eric Qiang);
* Fix the GCC Version Comparing issue
* ENV version updated to v1.1.2
  * Update scons version to 3.0.5
  * Fix VC++ warning issue
  * Fix Unicode error issue

# RT-Thread v4.0.0 Change Log

## Kernel

* Add SMP support;
* Add support for 64-bit processors;
* When the thread is running on CPU, the state of this thread is changed to RUNNING stat instead of READY state in previous version;

## Components

* When formatting the file system, adds FM_SFD option to create a volume in SFD format for FatFs; (HubretXie)
* Add file system handle pointer in `struct dfs_fd' structure;
* Fix stdio fd issue when POSIX api is used; (gbcwbz)
* Fix the `fd_is_open()` issue: when the sub-path is the same in different mounted filesystem. 
* Change the critical lock/unlock to dfs_lock/unlock in `getcwd()` function of DFS (the critical lock/unlock is different in SMP environment);
* Rewrite `list_thread/list_*` implementation of finsh cmd to avoid multi-core competition case;
* Fix the `aio_result` issue, which is returned by `aio_read_work` in AIO; (fullhan)
* Fix the mmap issue when the addr parameter is NULL; (fullhan)
* Modify the `_sys_istty` function in armlibc to correctly handle STDIN/STDOUT/STDERR; (gbcwbz)
* Modify the `_write_r` function in newlib to correctly handle stdout.
* Add lightweight processes (lwP) and corresponding system calls;
  * the lwP user application environment will be added later;
* Fix the at_socket issue when socket is a null pointer; (thomas onegd)
* Fix the select event issue in `at_recvfrom()` function in at_socket;
* Divide SAL into `sal_socket_ops/sal_proto_ops` and sal_proto_ops is implemented with gethostbyname/getaddrinfo ops etc.
* Add socket TLS layer in SAL, that is, upper application can be supported by encrypted transmission without considering lowlevel TLS at all.
* Fix the length issue of `ulog_strcpy`, which should be not exceed `ULOG_LINE_BUF_SIZE`;
* Add the macro definition of hexadecimal log output to ulog; (HubretXie)
* Add uTest component. The uTest is a unit test framework on RT-Thread, and can also be used for automatic testing on board with external Python scripts.
* Fix some compilation warnings and enumeration mismatches in drivers/audio;
* Fix the `can_rx/can_tx` issue, which is not cleared to NULL when CAN device is closed in drivers/can; (xeonxu)
* Fix drivers/hwtimer, time acquisition issue with counting down mode;
* Add drivers/adc driver framework;
* Fix the tick compensation issue when enable interrupt too early; (geniusgogo)
* Add `RT_SERIAL_USING_DMA` option in drivers/serial;
* Add QSPI support in drivers/spi framework;
* Add QSPI support in SFUD (based on the QSPI peripheral of stm32); SFUD is upgraded to version 1.1.0;
* Optimize SPI take/release function call in spi_msd;
* Fix the `blk_size` issue in `rt_rbb_blk_alloc()`;
* Fix the FS USB issue in `_get_descriptor` function;
* Fix the empty password issue in AP mode of drivers/wlan;
* Fix the return type issue in drivers/wlan;
* Remove the duplicate opening file check when open a file;

# BSP

* Change the name parameter to `cosnt char *` in `rt_hw_interrupt_install` function; (liruncong)
* Rewrite the RISC-V porting layer to make as a common and standalone porting layer for RISC-V IMAC 32/64;
* Fix `$` warning issue in Kconfig files of each BSP;
* Add the LPC54114-lite BSP, including GPIO, I2C, SDCard, SPI, SPI Flash, UART driver;
* Add Nuvoton-M487 BSP, including UART, EMAC driver; (Bluebear 233)
* Add Kendryte K210 BSP with RISC-V64 dual-core SMP BSP, including UART driver, also verified with micropython;
* Add RV32M1 VEGA BSP, including GPIO, I2C, SDCard, UART and other drivers;
* Fix the CAN driver issue in STM32F4XX-HAL BSP; (xeonxu)
* Fix UART DMA settings issue in STM32F10x/STM32F40x BSP; (zhouchuanfu)
* Fix the HEAP_BEGIN definition issue in STM32H743-Nucleo BSP; (nongxiaoming)
* Fix GPIO configuration issue in stm32f10x-HAL; (Wu Han)
* Change stm32f107 BSP as main function entry; (whj4674672)
* Fix the serial interrupt handling issue in stm32f10x BSP;
* Add PWM, RTC and watchdog drivers to stm32f10x-HAL BSP; (XXXXzzzz000)
* Fix the watchdog driver issue in stm32f4xx-HAL BSP; (XXXXzzzz000)
* Use lwIP version 2.x in stm32f40x/stm32f107 BSP.
* Fix the link issue when enable cmBacktrace package in stm32f4xx-HAL BSP; (xeonxu)
* Support Audio and microphones features in stm32f429-apollo BSP;
* Enable dlmodule support in x86 BSP; (SASANO Takayoshi)
* Addd uTest section in the link script of qemu-vexpress-a9/stm32f429-atk-apollo BSP for automatic testing;
* Change the license to Apache License v2.0 in Godson 1C BSP; (sundm75)
* Add the new BSP framework for STM32 serial chip, such as STM32 G0/F0/L0/F1/F4/F7/H7. In new BSP framework, the SoC drivers is reused. And in same time, lots of STM32 boards are supportted with new BSP framework:
  * STM32F091-Nucleo Development Board BSP
  * STM32F411-Nucleo Development Board BSP
  * STM32L432-Nucleo Development Board BSP; (sun_shine)
  * STM32F407-Discovery Development Board BSP
  * STM32F446-Nucleo Development Board BSP; (andeyqi)
  * STM32F746-Discovery Development Board BSP; (jinsheng)
  * STM32F767-Nucleo Development Board BSP; (e31207077)
  * STM32G071-Nucleo Development Board BSP;
  * ATK STM32F103 NANO Development Board BSP
  * ATK STM32F407 Explorer Development Board BSP
  * ATK STM32F429 Apollo Development Board BSP
  * ATK STM32F767 Apollo Development Board BSP
  * ATK STM32L475 Pandora IoT Development Board BSP
  * Fire STM32F103 Arbitrary Development Board BSP
  * Fire STM32F429 Challenger Development Board BSP
  * Fire STM32F767 Challenger Development Board BSP; (Hao Zhu)
  * ArmFly STM32F429-v6 Development Board BSP
  * STM32F103 iBox development board BSP; (dingo1688)
  * Dofly STM32F103 Development Board; (FindYGL)
  * STM32F107 uC/Eval Development Board BSP; (whj4674672)
  * and more, there are more developers involved for stm32 BSP framework, they are HubretXie, Hao Zhu, e190, etc. to improve the STM32 public driver.
* Add SWM320 BSP of Synwit.cn, including GPIO, HW Timer, I2C, Watchdog, PWM, RTC, SPI, UART, etc.; (provided and maintained by Synwit)
* Add TI TMS320F28379D BSP, the first DSP chip supported on RT-Thread; (xuzhuoyi)
* Fix USB driver issue in X1000; (Zhou YanJie)
* Add BSP for Synopsys Design Ware ARC EM Starter Kit, bsp/synopsys/emsk_em9d, EM9D core, including GPIO, UART and other drivers; (provided and maintained by Synopsys)

# Tool

* Provide more inforamtion when the tool chain does not exist;
* Add a draft Segger Embedded Studio project file generation command. Note that the tool chain in SES is a special version not the newlib.
* Fix the IAR library link command issue when use scons command line under;
* Fix the BSP path issue in scons `str(Dir('#'))`;
* Add `scons --pyconfig-silent` command to add some Kconfig configurations and to generate `.config` and `rtconfig.h` files;
* Update the `scons --dist` command to adapt to the new BSP framework;
* Modify the mkromfs.py script. Fix the corresponding C code generation When the romfs contains empty files or empty folders;
* Fix the issue of version string comparison issue for GNU GCC version in utils.py;
* ENV updated to V1.1.0
  * Provide better prompt information to improve user experience;
  * Add `system32` path to environment variables to avoid the `cmd` command cannot be found;
  * Add `PYTHONHOME` variable to environment variables to avoid PYTHON environment issue;

# RT-Thread v3.1.1 Change Log

## Kernel

* Support the configuration of the upward growth stack which is defined by the `ARCH_CPU_STACK_GROWS_UPWARD` macro. Because there are fewer ARCH for stacks growing upward, this configuration item does not display directly in menuconfig. When a CPU ARCH needs stacks growing upward, the configuration of `ARCH_CPU_STACK_GROWS_UPWARD` can be selected by BSP Kconfig file in default.
* Support for ARMCC V6 and later compiler (LLVM-based Compiler); currently it's mainly used in Keil MDK IDE. Please notes that the "Warnings" needs to use `Moderate Warnings` in project configuration in C/C++ (AC6) TAB; After using ARMCC v6, RT-Thread will add an additional `CLANG_ARM` macro definition; (liruncong, nongxiaoming, bernard)
* The `RT_USING_IDLE_HOOK` configuration in Kconfig becomes a separate configuration item, not limited to `RT_USING_HOOK`; (geniusgogo)

## Components

* Improve the PWM driver framework and add more interfaces.
* Fix the F_SETFL handling in ioctrl function; Fix the return value issue of fcntl function which is always 0 value.
* Fix the memheap object type issue when creating a ramfs object.
* Add power management framework for low power applications.
* Add multi-segment support for read and write operations in MC/SDIO driver framework (for stm32, you can choose a separate stm32_sdio package); (weety)
* Add ringblk_buf component for the block mode but in ringbuffer applications;
* Improve WLAN management framework with unified interfaces, management, commands, to provide more friendly support to developers and users;
* Add the conditional macro in the finsh when the MSH component is not enabled, even if the code files are compiled.
* Remove gdbstub and move to rt-thread packages.
* Upgrade and improve SAL and AT components: (linuxhan, eddylin83, slyant, luofanlu, Hubert Xie, Lawlieta, zhaojuntao, armink)
  * Fix the none cleared issue when closing socket in SAL, which lead to the socket is always holding.
  * Fix the `select()` issue for UDP communication in AT component. Add the receiving data handling to complete the clearing of received event;
  * Add the errno value when receive data timeout in at_recvfrom function in the AT component.
  * Add the receive data timeout handling in at_client_recv function in the AT component.
* Fix a possible issue in fputc function implementation when using microlib;
* Add gmtime_r implementation for ARMCC, IAR tool chain;
* Improve time function support in IAR and support 64bit time; (hichard)
* DHCPD's support for IPv6;
* Remove lwIP-1.3.2 porting and add lwIP-2.1.0 porting; lwIP-2.0.2 is still the default version.
* Add a lightweight ulog component and automatically replace the debug macro of the original rtdbg.h when it's enable.
* USB stack update
  * HOST, optimize the USB HOST timeout mechanism; fix the un-alignment visit issue in F4xx-HAL USB host driver;
  * Device: Add the check when class drivers are illegally registered; Fix the un-aligned access issue in some platforms; optimize CDC VCOM classes, add the timeout mechanism and ID definition.

## BSP

* Upgrade the wlan adaptor to the new version of Wi-Fi management framework in amebaz BSP.
* Add airkiss wifi configuration code to amebaz BSP.
* Update Apollo2 BSP with ADC, GPIO, I2C, PDM, SPI, UART and other drivers; (Haleyl)
* BeagleBone BSP is changed to main function mode, and adds Kconfig configuration file.
* DM365 BSP adds Kconfig configuration file;
* Update HiFive1 BSP and add more documentation.
* Update imx6sx BSP to main function mode, and add Kconfig configuration file.
* Change the old imxrt1052-evk BSP. The imxrt1052-related BSPs are classified into the `bsp/imxrt` directory; A touch framework is added to `bsp/imxrt`, and later will be moved into `components/drivers` directory;
* Improve stm32f4xx-HAL BSP with PWM, I2C, USB Host driver; (XuanZe, xuzhuoyi)
* Improve stm32f10x BSP with CAN driver and increase I2C driver; (wuhanstudio, AubrCool)
* Improve stm32f10x-HAL BSP with I2C, IWG, PWM, RTC and other drivers, improve UART driver; (XuanZe)
* Improve stm32f429-disco BSP and add I2C, LCD, Touch driver; (xuzhuoyi)
* Improve x86 BSP, support dlmodule function; (SASANO Takayoshi, parai)

## Tool

* Modify the building script to support Python 3; <Python 3 patches have been submitted to scons and need to wait for next scons release，maybe scons-3.0.2> (Arda)
* Add `scons --pyconfig` mode, which has a TK UI configurator; (weety)
* Support for GNU GCC 7/8 version toolchains (The `-std=c99` is not added into C-compiler flags), but please note: PThreads component failed in 2.5 and new version of newlib.

# RT-Thread 3.1.0 Change Log

## Kernel

* The main thread priority can be configured by Kconfig;
* Add the checking of kernel object type, which can effectively avoid the problem of continuing to use kernel objects after they are destroyed.
* Add the idle hook list to mount multiple idle hook, and can be configured by Kconfig.
* Add the device_ops operation set to reduce the footprint of device object.
* Remove the special memory operation in application module when using SLAB memory management algorithm.
* Move application module from the kernel to `libc/libdl`.
* Enhance the debug information output of `rtdbg.h` file.
* In Keil/IAR tool chain, the `RT_USED` is used to keep symbols and avoid to add more argument or section in link phrase.

## Components

* Remove all of external codes, which will be moved to packages in the future.
* Add initialization flag for shell, file system, network protocol stack etc to prevent repeated initialization;
* Enable the long file name feature of ELM FatFs in default.
* Change DFS FD to dynamic allocation mode. The maximum number of allocation is still DFS_FD_MAX.
* Add dfs_fdtable_get() function to get different fdtable;
* Add more DFS error messages, and provide easy to understand log when abnormal.
* Fix the disk format issue of FatFs file system when multiple FatFs file systems are mounted.
* Remove the folder enter feature in msh when input a folder name;
* Add `int finsh_set_prompt (const char * prompt);` routine for setting a custom prompt for msh;
* Add the VBUS configuration in Kconfig.
* Move the application module from kernel to `libc/libdl` component;
* Rewrite most of the management code for application module: replace the original object container with the object list; split the symbol resolution code into different processor architecture etc.
* Update the application module chapter in the programming guide, and change it into dynamic module chapter.
* Overwrite the exit() function of newlib to take over the processing of exit for a dlmodule.
* Add SAL (Socket Abstraction Layer) component for adapting different protocol stacks and network implementations, and update the relevant sections of the programming guide;
* Add AT component, including AT client, AT server and AT Socket function;
* Remove the poll/select API of DFS_NET and move them to SAL component.
* Remove the strong dependence of lwIP component for DFS_NET and replace it with Kconfig configuration in SAL.
* Add the DHCP server function with lwIP raw API;
* Fix the wait queue none-initialization issue in socket allocation of lwIP.
* When a thread is about to block on a wait queue, fix the wake up issue for `rt_wqueue_wakeup' is executed to wake up that thread;
* Add the PWM driver framework;
* Fix the sdio_irq_wakeup release issue in the MMC/SD framework.
* Fix the problem of DMA handling in the serial driver framework.
* Update SFUD to v1.0.6 version;

## BSP

* Fix the SP issue when hard fault occurs for ARM Cortex-M arch;
* Add C-Sky CK802 architecture porting;
* Add Realtek amebaz WiFi SOC (rtl8710bn) BSP;
* Update imxrt1052-evk firmware SDK to support B model chip.
* Fix the copying packets issue in the Godson 1C BSP when sending message.
* The Nuvoton m05x/m451 BSP are changed into the main() entry mode, and supports GCC compilation;
* Fix the inconsistency issue between touch range and LCD resolution in qemu-vexpress-a9.
* Add qemu-vexpress-gemini BSP for dual core A9 (RT-Thread + Linux) arch;
* Add the basic porting for Raspberry Pi 2B ;
* Add CAN and PWM drivers in stm32f4xx-HAL BSP;
* Optimize the GPIO driver in stm32f4xx-HAL BSP;
* Add UART3 driver in stm32f4xx-HAL BSP;
* Fix the I2C1 driver clock in stm32f10x BSP and WDG control interface.
* Add rt_hw_us_delay interface in stm32f10x-HAL BSP;
* Optimize the GPIO driver in stm32f10x-HAL BSP;
* Add GPIO driver and RTC driver in stm32f107 BSP;

## Tool

* ENV update to v1.0.0 final version.
* ENV added the China mirror for software package, which can speed up the software package download, update  etc.
* Fix the ENV known bugs and enhance the interaction with users.
* Add building script to detect the version of GCC & newlib;
* Add building script to detect the version of armcc;
* Add `scons --dist` function to make distribution for a BSP.
* Add `scons - dist - strip' function to make a minimal files of distribution for a BSP.
* Add `ASFLAGS/LOCAL_ASFLAGS' parameters for defined a group and pass them to assembler;
* Fix some errors in building script under the Linux environment.
* Add the C-Sky CDK IDE project generation.
* Add `scons --target=vsc -s` to generate friendly configuration files for VSCode;

# RT-Thread 3.0.4 Change Log

## Kernel

* Change the location of hook invoking in rt_event_send, which can better reflect the event value to the system view.
* Fix the rt_realloc() issue in memheap;
* Fix the vstart_addr issue in the dynamic library.
* Ensure that signal is more standardized and remove si_errno members from siginfo_t;
* Add rt_thread_mdelay() API for millisecond delay in thread.

## Components

* Fix the DFS mkfs issue of FatFs (which is a merge issue introduced in RT-Thread V3.0 upgrade).
* Fix dfs_net poll issue, if there is already received data, the upper layer can not wake up and deal with data.
* Fix the socket issue in dfs_net if lwip_socket failed(Bluebear233);
* If the dfs_net/socket feature is used within lwIP 1.x version, a compiler error will be returned.
* Fix the DFS df() information issue;
* Fix the audio device write issue while the interrupt is not properly recovered.
* Fix the one-shot timeout issue in the hardware timer driver framework.
* In ENC28J60 driver, the "link change interrupt" is enable in initialization.
* Fix the data issue in put data into ringbuffer.
* Add UDP information display in netstat command;
* Fix the USB HS issue when sending 1 bytes of data will cause two times of transmission.
* Change the registration mechanism of USB Class Driver and Class Driver can be registered in package.
* Add USB Device driver framework for HS USB.
* Enhance the compatibility of time() function for different compilers;
* Add more configuration items for DHCPD in menuconfig.

## BSP

* Temporarily remove the Andes AE210P transplant because of the mistakenly use SVC for context switching.
* Add SD/MMC drive in Allwinner ARM9 BSP;
* Add SPI and SPI Flash drivers to Allwinner ARM9 BSP.
* Add GD32's gd32303e-eval development board support;
* gd32450z-eval supports GNU GCC compilation;
* Rewriting the hifive1 board level support package for the risc-v architecture;
* About i.MX RT1052, we have completed various development board support: ATK, Fire, seeed studio;
* On i.MX RT1052, add the cache-ops functions;
* On i.MX RT1052, add I2S driver and WM8960 codec driver support;
* Improve ETH driver support (including support for Fire development board) on i.MX RT1052.
* Add Hardware Timer driver support on i.MX RT1052.
* On i.MX RT1052, add GPIO driver;
* On i.MX RT1052, add RTC driver;
* On i.MX RT1052, improve SD/MMC driver;
* On i.MX RT1052, add SPI driver and SPI Flash driver (connect to SFUD component);
* Add USB Device driver on i.MX RT1052.
* Add README files and KConfig files in LPC408x BSP;
* Add README documents in LPC5460x-LPCXpresso BSP;
* Add the display controller driver (Sundm75) in Godson 1C BSP.
* Add CAN driver in Loongson 1C BSP(Sundm75);
* In GPIO driver of Loongson 1C BSP, add (external) interrupt feature (Zhuangwei);
* Use SPI automatic initialization in Loongson 1C BSP.
* Add I2C driver in Loongson1C BSP(Sundm75);
* Add resistive touch screen driver in Loongson 1C BSP(Sundm75);
* In Loongson 1C BSP, the components initiliazation and main function is enable(Zhuangwei).
* Add self bootup in Loongson1C BSP (Zhuangwei);
* Add README files and KConfig files to Loongson 1C BSP(Zhuangwei).
* Fix the rx descriptor issue in init_rx_desc function in NUC472 BSP (Bluebear233);
* Add AC97 Audio driver in QEMU-VExpress-A9 BSP;
* Add README description file in QEMU-VExpress-A9;
* Add I2C driver in stm32f4xx-HAL BSP, and README description file;
* Add cache-ops in stm32f7-disco BSP, and README description file;
* Add README description file in stm32f10x/stm32f10x-HAL;
* Add README specification files and KConfig configuration files in stm32f40x BSP;
* Add KConfig configuration file in stm32f20x BSP;
* Add README description file to stm32f411-nucleo BSP and enable GNU GCC tool chain support;
* Add GPIO driver and README description file in stm32f429-apollo BSP;
* Add KConfig configuration files in stm32f429-armfly BSP;
* Add README description file in stm32l476-nucleo BSP;
* Because V2M-MPS2 does not support in 32-bit machine simulation operation, temporarily remove this BSP.
* Add README description file and some firmware file, such as u-boot.bin, wifi firmware etc, in X1000 BSP;
Tools
* Add detection feature for the version of GNU GCC tool chain and libc function feature.
* Add the function of VSCode editor assistance, and support scons --target=vsc -s under BSP folder to generate configuration files for VSCode.
* Add the detection of verson of IAR;
* Add the ProjectInfo (Env) function to get information about target: all source files should be compiled, all header files, all macro definitions, the search paths for header file etc.

# RT-Thread 3.0.3 Change Log

## Kernel

* Add scheduler protection when do cleanup for a detached thread;
* Fix the object_find issue when enable module feature;
* Improve POSIX signal support and add rt_signal_wait function and POSIX sigwait interface;
* When enable finsh shell, rtthread.h header file includes the API file of finsh. Therefore, the application code can use command export feature without finsh.h file;
* Improve the comments of rtdbg.h file. In RT-Thread, just use following code to add debug log feature:

```c
    #define DBG_ENABLE

    #define DBG_SECTION_NAME    "[ MOD]"
    #define DBG_LEVEL           DBG_INFO
    #define DBG_COLOR
    #include <rtdbg.h>
```

When close the DBG_ENABLE definition, the debug log will be closed. Otherwise, the `dbg_log(level, fmt, ...)` can be used to print debug information. 

DBG_SECTION_NAME - The prefix information for each log line;
DBG_LEVEL - The debug log level;
DBG_COLOR - Whether use color log in console.

## Components

* Fix the flag issue of fopen in GNU GCC;
* Fix the pthread_detach issue when used for a detached pthread;
* Fix the _TIMESPEC_DEFINED issue in IAR 8;
* Add libc_stdio_get_console() interface for returns the fd of console;
* Move UI engine component as a standalone package;
* Add a unify TF/SD card driver on SPI device bus;
* Add soft-RTC device, therefore device can synchronize with network time and maintains the time with OS tick later;
* Change the open/fcntl/ioctl API to POSIX standard  interface;
* Fix ramfs issue when update with RTT 3.0.x;
* Fix the elm fatfs umount issue; (liu2guang)
* ignore the O_CREAT flag when open a device file;
* Improve VCOM class driver in USB stack; (ChunfengMu, Aubr.Cool)

## BSP

* Fix the potential issue when enable Cortex-M hardware FPU;
* Add v2m-mps2 bsp, which is used in Keil MDK5 for Cortex-M4/M7/M23/M33 simulation;
* Add sdcard driver for stm32f10x-HAL;(liu2guang)
* Improve GNU GCC support for stm32f10x-HAL;(Xeon Xu)
* simulator bsp can be used in Windows/Visual C++ and update SDL to v2.0.7;
* Add gk7102 bsp by gokemicro;(gokemicro)
* Add allwinner F1C100s ARM9 bsp;(uestczyh222)
* Fix some issues in peripherals drive library of NXP LPC54608/i.MX RT; (Valeriy Van)

## Tools

* scons building script will automatically add `_REENT_SMALL` macro when enable newlib nanao;
* Modify building script for Python 3.x and scons 3.0

# RT-Thread v3.0.2 Change log

## Platform

* Make sure the Object_Class to a fixed value
* Add `rt_device_create/destroy` API
* Add memory trace for small memory management algorithm for memory leak and overwritten.
* Add a first version of asynchronous I/O API
* Add cputime for high resolution counter
* Add pipe device functions in DeviceDrivers
* USB Host available in stm32f4 with mass storage class
* Add 'df' command in msh
* Update UI engine and add an example
* Split `clock_time` from pthreads and add a new clock id: `CLOCK_CPUTIME_ID`
* Enable IPv6 in lwIP 2.0.2 version
* Add memlog in logtrace
* Fix closesocket issue in dfs_net
* Fix IPv6 issue in NFS
* Update JFFS2 file system with new DFS API
* Fix the issue of stat "/.." of lwext4 (parai)
* Fix the fs type search issue in mkfs
* Fix the select issue in dfs_net

## Tools

* scons: add '--useconfig' command to use an exist config file
* scons: force to use g++ for link when enable `RT_USING_CPLUSPLUS` in GNU GCC configuration
* Enable package feature in Linux/MacOS host

## BSP

* Add NUC472 bsp (bluebear)
* Update SD/MMC driver for qemu-vexpress-A9
* Add keyboard/mouse driver for qemu-vexpress-a9
* Add ADC/I2C/Flash/PWM/RTC/smbus/SPI driver for apollo2 (Haleyl)
* Add I2C/LCD/Touch driver for i.MXRT1052-EVK
* Update SD/MMC driver for mini2440 (kuangdazzidd)
* Update simulator to adapt VC++ compiler
* Add USB host driver in stm32f4xx-HAL (uestczyh222)
* Update EMAC driver for IPv6 in stm32f40x/stm32f107
* Add stm32h743-nucleo bsp (polariss)

# RT-Thread v3.0.1 Change log

## Platform:

* Add mmap()/munmap() API for POSIX compatibility.
* Fix the filesystem_operation_table issue.
* Enhance USB stack for USB slave (HID/ECM/RNDIS/WINUSB or composite device);
* Enhance USB stack for USB host (HID/MSC etc);
* Fix memory leak issue when close a pipe.  
* Fix the romfs open issue;
* Add SoftAP device in Wi-Fi framework;
* Re-order the lwIP/ETH initialization;
* Add IPv6 options in Kconfig;
* Fix the module_id issue in _rt_thread_init;

## Tools:

* Add menuconfig for Linux/Mac platform: use `scons --memuconfig` to enable it;
* Add LIBS feature for IAR project;

## BSP:

* Enhance LPC54608 BSP for kinds of compiler;
* Add GPIO/I2C/SPI driver for Loongson 1C;
* Add csd cmd in sdcard driver of mini2440;
* Add SDIO/EMAC driver for qemu-vexpress-a9 bsp;
* Enable VC++ to compile simulator bsp;
* Add stm32f4xx-HAL bsp for kinds of STM32F4 series <User can use menuconfig to select chip>;
* Fix the PHY reset in stm32f429-apollo bsp;
* Add Audio/MMC/SLCD/Touch/USB slave/RTC/SPI/SFC Flash driver in Ingenic X1000 bsp;

# RT-Thread v3.0.0 Change log
## Platform:

* Add more POSIX features, for example poll/select, signal, termios etc.
* Add waitqueue for poll feature.
* Use fops for file operation. There are two ways to visit device object: rt_device_* API, the file API(open/read/write/close etc).
* Change the type of cmd from uint8_t to int in control interface.
* Add more C++ object for RT-Thread Kernel Object.
* Add wlan driver framework for wlan device operation.
* Integrate SFUD into RT-Thread to unify the operations of spi flash.
* Update lwIP to v2.0.2 version.

## Tools:

* Enable packages, with ENV tool.
* menuconfig & Kconfig.
* Add scons --dist for make a distribution for specified BSP.

## BSP:

* more MCU porting.

## IoT:

* put more IoT components as packages, for example, MQTT, CoAP, HTTP, TLS etc.

# RT-Thread v2.1.0 Change log

This release is the final release for RT-Thread v2.1.0 branch. This release has been delayed many time. After committed fh8620 and x1000 bsp, we are proud to announce this branch release of the official version.

The change log since last stable version:

## Kernel:

* Move the init component to the kernel.
* Fix the device open flag issue.
* Add assertion hook.
* Better application module support.
* Does not lock scheduler when invoking soft-timer timeout function.

## Board Support Package:

* fh8620, which is provided by Shanghai Fullhan Microelectronics Co., Ltd. It's a IP camera chip with ARM1176, 300MHz, 16KB I-Cache and 16kB D-Cache.
* x1000 bsp. The CPU is a XBurst CPU 1.0GHz, MIPS-based, from Ingenic Semiconductor Co.,Ltd.
* imx6sx bsp, only the Cortex-A9 core porting in the NXP i.MX6 solox. BTW, another full Kinetis series porting was created in rt-thread_fsl, which is maintained by NXP employee.
* lpc5410x bsp, only the Cortex-M4 core porting.
* ls1cdev bsp for Loogson1C board.
* dm365 bsp.
* nRF51822/nRF52832 bsp.
* stm32f7-disco bsp, the first ARM Cortex-M7 porting in RT-Thread.
* stm32f411-nucleo bsp.
* Add IAR compiler support in beaglebone bsp.

## Components:

* Add more socket fd operators in DFS with a virtual lwIP file system ops.
* Add CAN/Hardware Timer device drivers.
* Fix the SDIO issue to support sdio wifi device.
* Add eMMC support in SD/MMC device drivers;
* Fix the NAT configured enter reset issue in lwIP NAT.
* RTGUI come back, but as a UI engine for blend point/line/rect and bitmap etc.
* Add nanopb porting, a small code-size Protocol Buffers implementation;
* Add paho-mqtt porting, the Eclipse Paho MQTT C/C++ client for Embedded platforms;
* Update freetype to 2.5.4 version.
* Enhance msh for file operations.
* Split the exported commands of finsh shell to a standalone section: ".rodata.name"

# RT-Thread v2.1.0 beta版本更改说明

## BSP部分

* BeagleBone加入GPIO驱动；
* 京微雅格M7，更新驱动库并改进EMAC驱动程序；
* 新加入dm365移植（包括EMAC、GPIO、I2C、MMC/SD、SPI等驱动）；
* LPC4088加入EMC、硬件定时器、CAN驱动；
* 新加入龙芯1C，智龙v2开发板移植（包括多串口驱动）；
* 更改mini2440移植为applications/drivers等的目录方式；
* 更新simulator在MS VC++上的移植，处理好初始化代码工作，完善UART控制台驱动；
* 新加入stm32f7-disco移植；
* 在stm32f10x中新加入CAN驱动及应用代码示例；
* 在stm32f40x中加入硬件定时器驱动，RTC驱动；
* 调整stm32f107为新的串口驱动框架；

## 组件

* DFS的struct stat定义中移除st_blksize成员（可以兼容于VC++中的stat定义）；
* 修正DFS中select实现的问题；
* 修正DFS中文件操作出错、关闭时的fd处理问题；
* 修正DFS中mkdir和lseek出错时的fd处理问题；
* 修正lwIP中SYS_ARCH_PROTECT/SYS_ARCH_UNPROTECT保护的问题；
* 增加CAN驱动框架；
* 增加硬件定时器驱动框架；
* SD/MMC驱动框架中增加eMMC支持；
* 修正注册SDIO驱动时驱动关联的问题；
* 修正串口驱动框架DMA发送时激活标志的问题；
* SPI Flash驱动中加入对GD25Q spi flash芯片支持；
* 增加paho-mqtt组件移植；
* 增加msh的脚本执行能力，可以在msh下执行*.sh脚本；
* 增加msh下的mkfs命令；
* 修正在Linux Telnet下使用finsh shell回车符处理的问题；
* 增加应用模块在使用armcc、gnu gcc编译器时的libc符号导出；
* 在以太网网卡驱动框架中增加ETHIF_LINK_AUTOUP/PHYUP参数用于指定初始时的链路Up/Down状态；
* 在组件初始化中导出log_trace组件；

## 内核

* 更改UNUSED/USED等更改成RT_UNUSED/RT_USED；
* 链接时增加.rodata.name section，当空间资源受限时可以把它放到性能低的内存区域；
* 完善IAR编译器下的组件自动初始化；
* 增加rt_assert_hook，在触发断言时可以执行这个钩子函数；
* 修正应用模块分散加载情况下的问题；

## 工具

* scons中定义Group时加入了本Group内的编译参数定义；
* 修正了如果Group中即包含代码，也包含二进制库时，生成的Keil MDK工程文件有两个重名Group的问题；

版本: RT-Threadv2.0.1及v2.1.0 alpha

RT-Thread v2.0.1是2.0这个系列的bug修正版，而v2.1.0 alpha则是当前开发主干的一个技术预览版本，它给出了v2.1.0这个版本系列的技术预览情况，不建议用于实际产品中，因为它可能存在大量的一些bug。

# RT-Thread v2.0.1更改说明

*  IAR用的dlib，加入THREAD_SUPPORT 和 FILE_DESCRIPTOR的支持；
*  修正finsh中echo回显模式的问题；
*  修正USB host代码的编译错误；
*  修正sensor框架回调函数的问题；
*  修正pin设备注册时的设备名称问题；

而v2.1.0 alpha这个技术预览版则沿着最初设定的roadmap技术路线进行，这其中主要包括：

*  lwip更深度的集成：把它集成到RT-Thread的文件系统接口中，这样Linux/Unix下的一些socket网络应用能够更顺利的移植到RT-Thread上，也为以后可以应用到更多地方的select接口铺路。

*  这部分是和RT-Thread发布本身无关，但也是这个版本系列设定的目标之一：开启一个云端集成开发环境的时代！云端会是什么样的，请用现代化的浏览器打开[CloudIDE](http://lab.rt-thread.org/cloudide/simulator/index.html)

# RT-Thread 2.0.0正式版更改说明

经历了大约1年的时间，RT-Thread v2.0.0的最终版本终于发布出来了。自这个版本开发以来，引入了多项功能、修改、增强等。感谢参与的诸位开发人员！
以下是自v2.0.0 RC版本以来的详细更改记录。后续我还会给出v2.0.0版本自v1.2.x版本的主要不同、看点，以及给出下一个版本的roadmap规划。

## 内核

*  console以RT_DEVICE_FLAG_STREAM参数打开字符设备；
*  在rt_memheap_free中加入更多的断言检查；

## 组件

*  更新RW009驱动以支持Wi-Fi SoftAP模式（aozima）；
*  修正sensor框架的一些问题，并加入C API接口（睿赛德服务公司提供）；
*  加入MPU6050 sensor的代码（bernard, Coing）；
*  加入BMI055 sensor的代码（Coing）；
*  当未使能heap时，修正finsh/msh中list_memheap的问题；
*  修正LIBC编译的警告；
*  加入IAR dlib相关的移植，使得应用能够使用标准的API接口；
*  修正YMode握手时可能引起的竞争问题（grissiom）；
*  更新FreeType版本到2.5.4
*  单独把C++的全局对象初始化放到cplusplus_system_init函数中，并在初始化线程中调用；
*  finsh中以RT_DEVICE_FLAG_STREAM参数打开字符设备；
*  添加VBUS组件用于Linux与RT-Thread系统之间，RT-Thread与RT-Thread系统之间通信（睿赛德服务公司捐赠）；
*  增加lwIP/NAT组件，可以做多个网口间的地址转换（Hicard）；
*  增加lwIP/DHCP服务端，用于向客户端分配IP地址（睿赛德服务公司提供）；

## BSP

*  修正LPC4357串口驱动初始化时过早打开中断的问题（nongxiaoming）；
*  重写LPC4357串口驱动，并让芯片上M4/M0核心分别都执行RT-Thread系统，两核心之间以VBUS组件进行系统间通信（睿赛德服务公司捐赠）；
*  新增RX移植（limxuzheng）；
*  新增NuMicro M051 Series移植，支持GCC、Keil MDK编译器（bright-pan）；
*  新增LPC54102移植（Coing）；
*  移除STM32F4 BSP中不需要的RT_TIMER_TICK_PER_SECOND配置（pangweishen）；
*  在Linux Clang编译分析中，强制以32位模式进行编译（grissiom）；
*  修正STM32F103中串口驱动中断过早打开的问题（armink）；

## 工具

*  增加scons中的MD5支持（bright-pan）；

# RT-Thread 2.0.0 RC 更改说明

发布时间:2014/11/4

随着RT-Thread功能越来越多，如何发布版本也成为一件头疼的事情，因为需要仔细对比最近三个月来的修改记录。这次的发布距离上一次beta版本依然是三个月的时间，但按照发布计划已然推迟了一个月进行发布。 

在这三个月中，开源社区上也发生了很多有趣的事情：

阿嘉的使用RT-Thread的四轴飞行器毕业设计惊艳亮相，采用了1个STM32F4 + 8个STM32F1进行飞行控制，总计9个MCU的另类实现方式；沿循四轴飞行器的路线，与国内匿名团队合作，采用RW009 Wi-Fi控制的迷你四轴飞行器也在稳步推进过程中。

RT-Thread做为一个开源组织参与的CSDN开源夏令营结出了丰硕的果实：
由hduffddybz参与的IPv6协议栈移植（最新版本的lwIP-head版本移植）在这次发布中已经包括进来，从而能够在使用RT-Thread的小型设备上实现TCP/IP v4/v6双栈的支持；
由wzyy2参与的GDB stub实现，也完美的支持BeagleBoneBlack开发板和STM32F4平台；
CSDN开源夏令营其他的成果，例如bluedroid移植也有了初步的成果，希望能够在后续的版本（可能会是2.1.0系列版本？）包含进来。CSDN开源夏令营是一次非常棒的活动，能够让学生提前进入实战，了解软件开发的初步知识。对开源社区来说，也是一次非常有益的社区互动活动。希望明年这个活动可以继续，关注RT-Thread、嵌入式开发的同学可以关注明年的动向。

当前智能化设备是一个备受关注的领域，针对这一领域的特点，RT-Thread也相
