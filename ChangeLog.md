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

当前智能化设备是一个备受关注的领域，针对这一领域的特点，RT-Thread也相应的做出了积极的响应，所以这个版本开始加入sensor的应用框架（APP/算法 <--> sensor framework <--> RT-Thread device driver <--> 硬件外设）。希望在小型化的RT-Thread操作系统基础上融合智能化相关的技术，让RT-Thread成为这方面可选的OS系统之一。RT-Thread操作系统的sensor框架也尝试新的实现方式，即采用C++的方式来实现（当然也会考虑C方面的兼容，无疑C++的面向对象特性会更好，所以最终选择了C++），在这个基础上也可能融合其他的一些生态技术，例如ARM mbed平台上的一些社区组件技术。所以这个发布版本中既包括sensor框架，也包括了C++底层的一些基础支撑。

这个版本是RT-Thread 2.0.0系列正式版本的候选版本，正式版本预计会在年底正式发布，距离正式版本还会加入更完善的一些支撑（例如各种传感器驱动）。也计划2014年11月22日，在上海浦东举行RT-Thread嵌入式系统沙龙活动，欢迎大家关注并参与进行RT-Thread方方面面的技术交流。

以下是这个版本的更改记录:

## 内核

* 修正当采用高级别优化编译时，idle任务中查询是否有僵尸线程的潜在bug；

* 修正memory pool中的竞争问题；

* 在console中打开设备时，加入流标志进行打开；

## 组件

* 加入C++基础支撑组件。C++组件依赖于RT_USING_LIBC库，当使用GCC编译器时请注意查看其中的说明文档并更改ld script；
* 修正DFS中NFS打开目录的bug；
* 更改DFS ROMFS默认romfs_root为弱化符号；
* 添加DFS中dfs_file_lseek接口中关于fs的检查；
* 移除I2C core中无用的core lock锁；
* 添加sensor framework（采用C++的方式支持各种sensor）；
* 修正serial框架中DMA发送的bug（heyuanjie87）；
* 移除SPI框架中不必要的device初始化代码；
* 完善SPI Wi-Fi网卡RW009驱动并提供RSSI相关的命令；
* 修正MSH中未定义DFS_USING_WORKDIR时更改当前目录的bug；
* 修正MSH中未定义RT_LWIP_TCP时依然定义了netstat命令的bug；
* 修正MSH中未定义RT_USING_HEAP时依然定义了free命令的bug；
* 修正finsh中FINSH_USING_HISTORY相关的裁剪；
* 加入gdb stub组件，当前支持ARM Cortex-A8和Cortex-M3/4（wzyy2）；
* 统一不同编译器下使用LIBC的宏为RT_USING_LIBC，原有的宏定义RT_USING_NEWLIB/RT_USING_ARM_LIBC需要从rtconfig.h中移除，并替换成RT_USING_LIBC；
* 加入最新的lwIP分支：lwip-head，以提供IPv4/v6双栈的功能（hduffddybz）；
* YMode中打开串口设备时，添加open flag（armink）；

## bsp

* 加入北京京微雅格的M7（华山）低功耗FPGA的ARM Cortex-M3移植（aozima）；
* 加入北京京微雅格的M7 EMAC以太网驱动（aozima）；
* AT91SAM9260分支中更改RT_USING_NEWLIB为RT_USING_LIBC；
* BeagleBoneBlack分支中加入gdb stub支持（wzyy2）；
* LPC176x分支中加入C++支持；
* LPC176x分支中修正SD卡驱动返回卡信息的bug；
* 修正LPC408x分支中GCC编译时的问题；
* LPC408x分支中加入C++支持；
* 龙芯1B分支中加入UART3驱动；
* 加入飞索半导体的MB9BF568 FM4分支移植（yangfasheng）；
* mini2440分支中更改RT_USING_NEWLIB为 RT_USING_LIBC；
* stm32f0x分支中移除不同编译器下的LIBC定义，统一更改为RT_USING_LIBC；
* stm32f0x分支中加入串口接收溢出中断处理（armink）；
* stm32f40x分支中加入gdb stub支持并添加UART6驱动（wzzy2）；
* zynq7000分支中更改RT_USING_NEWLIB为RT_USING_LIBC；
* 加入ARM Cortex-M4芯片指令级的ffs实现；
* 修正MB0BF618S分支中缺少timer初始化的bug（mike mao）；

## 工具

* 移除Python 2.6中未支持的语法（xfguo）；
* 移除Windows平台中的startupinfo信息（对Python版本兼容性更好）；
* 修正CPPPATH被打乱的bug；

# RT-Thread 2.0.0 Beta更改说明

发布时间:2014/8/1

v2.0.0这个版本系列是RT-Thread当前的开发分支，如果要上新项目，建议使用这个版本来进行，预计这个版本的正式版会在年底发布。欢迎对这个版本进行测试、并反馈问题，能够早日进入到稳定版。

v2.0.0版本的开发相对活跃些，开源社区提供了强有力的支持：如Arda贡献的TM4C129x移植，Romeo贡献的frdm-k64f移植，xiaonong的LPC4300移植等，以及睿赛德服务公司捐赠的Zynq7000移植，MB9BF618S移植，以及SPI WiFi网卡的驱动代码等。

更改记录

## 内核

* 移除rt_device_init_all()函数：在系统启动时不需要再调用这个函数来初始化驱动，而是由上层应用执行rt_device_open时自动进行设备初始化；
* 修正设备对象引用计数在打开设备失败依然递增的问题；
* 增加WEAK宏用于定义/声明弱符号；
* 在执行静态内存块分配前，重置线程的errno；
* 修正timer未打开调试选项时，无用的静态函数定义（导致编译警告）；
* 启动timer前，对timer进行强制移除；
* 在执行soft timer超时函数时，打开调度器锁；
* 新增块设备的自动刷新参数，RT_DEVICE_CTRL_BLK_AUTOREFRESH；
 
## 工具

* 修正scons命令编译时，选择keil mdk (armcc)编译器时，命令行太长编译失败的问题；

## 移植

* 移除rt_device_init_all()相关的调用；
* 根据串口框架调整相关的驱动代码；
* 新增frdm-k64f移植（FreeScale K64芯片）；
* 移除K60Fxxxx移植；
* 新增LPC43xx移植（NXP LPC4357芯片）；
* 移除LPC176x中的组件初始化配置；
* 修正龙芯1B移植（ls1bdev）中链接脚本关于组件初始化部分的配置；
* 修正STM32F40x中UART3的配置；
* 修正STM32F40x中GNU GCC连接脚本中ROM/RAM大小的配置；
* 移除STM32F107中的组件初始化配置；
* 增强STM32F107 EMAC驱动性能，同时加入自动查找PHY芯片地址功能；
* 重写xplorer4330（NXP LPC4330芯片）移植（xiaonong完成）；
* 新增Zynq7000 ARM Dual Cortex-A9移植；
* 新增MB9BF618S移植；
* 新增tm4c129x移植，并加入相应的EMAC以太网驱动；

## 组件

* DFS: 新增根据设备对象获得其上装载文件系统路径的函数：dfs_filesystem_get_mounted_path(struct rt_device* device);
* DFS: 修正readdir在GNU GCC下的编译警告；
* DeviceDrivers：新增workqueue实现；
* DeviceDrivers: 修正USB Device栈中的一些拼写错误；
* DeviceDrivers: 重写serial框架，能够让串口设备驱动同时支持三种模式：poll、interrupt、DMA。模式选择需要在执行rt_device_open时，由open flags指定；
* DeviceDrivers: 加入更多的SPI设备驱动，例如RW009的SPI WiFi网口驱动（2.4G 802.11 b/g/n，WEP/WPA/WPA2，SoftAP/Station），SPI NorFlash块设备驱动，ENC28J60以太网网卡驱动；
* Finsh: list_device()命令中增加refcount的信息；
* Finsh: 修正'0'零常量无法识别的错误；
* Finsh: mv命令，实现把一个文件移动到一个目录中；
* Finsh: ifconfig命令支持对一个网络接口的基本配置；
* Finsh: 新增netstat命令，用于显示当前系统中TCP连接的状态；
* Finsh: 修正当命令行太长导致的缓冲区移除的问题；
* libc: 修正arm libc中未使用DFS时的编译警告；
* libc: 修正newlib中使用DFS时的系统调用编译警告（GNU GCC下）；
* lwIP 1.4.1: 默认打开LWIP_SO_SNDTIMEO以支持连接发送超时；
* lwIP 1.4.1: 修正MEMP_NUM_TCP_SEG定义错误的问题；
* lwIP 1.4.1: 加入RT_LWIP_REASSEMBLY_FRAG选项定义以支持IP分组及合并；
* lwIP 1.4.1: ethnet网络接口支持定义LWIP_NO_TX_THREAD/LWIP_NO_RX_THREAD，以关闭etx/erx线程；
* lwIP 1.4.1: 用户可以重新定义RT_LWIP_ETH_MTU，以修改网络中的MTU值；
* lwIP 1.4.1: 修正LWIP_NETIF_LINK_CALLBACK条件编译的问题；
* lwIP 1.4.1: 完善移植相关的注释；
* log trace: 增加log_session_lvl接口；
* log trace: log trace中的session引用更改成常量形式；
* ymodem: 增强数据接收的稳定性；

# RT-Thread 2.0.0 Alpha更改说明

发布时间:2014/4/8
	
RT-Thread 2.0.0分支的第一个技术预览版本，仅用于展示2.0.0发展分支的演化动向(按照roadmap，2.0.0这个分支会有一部分RT-Thread和Linux互补性的技术，为Linux增加更好的实时性，为RT-Thread增加更多的功能性，这份技术预览版正是朝着这个目标而努力)，欢迎反馈建议和问题。

## 组件

* msh： bugfix 和功能性增强。新的 msh 在调用外部模块方面更加方便。
* DFS： nfs 的 bugfix 和内置命令的增强。ELM FatFS加入对扇区不匹配情况下的信息输出，这样能够及时定位问题。
* JS：新添了轻量级Javascript引擎，可以在RT-Thread中直接运行javascript脚本。
* VMM：可以在qemu中运行的 Virtual Machine Module 组件。暂时只支持 realview-pb-a8 的 bsp。
* CMSIS：版本更新至 3.20
* drivers：USB 协议栈的重构。新的框架中编写驱动变得更加容易了。

## BSP

* beaglebone：串口驱动更新
* realview-a8：添加了 VMM 组件

## 工具

* 固件加入scons --target=ua -s，用于准备用户应用环境；

[发布后记]

RT-Thread 2.0.0. Alpha版本相比于RT-Thread 1.2.1，新的特性主要有两部分：
- RT-Thread + Linux双系统，这部分以RealView-A8处理器(ARM Cortex-A8单核)为蓝本，给出一个简单的双系统并行运行的demo；在没有硬件的环境下，可以使用QEMU软件虚拟方式的执行。这个链接中包含一个编译好的Linux及RT-Thread二进制包，可以直接下载进行体验。

目录中有 Linux 的内核镜像 zImage，ramdisk rootfs.cpio.gz。可以用
qemu-system-arm -M realview-pb-a8 -kernel zImage -initrd rootfs.cpio.gz -serial vc -serial vc
来启动。启动之后 Linux 的控制台在第一个串口上(Atl + Ctrl + 3)，可以直接无密码以 root 用户登录。登录之后加载内核模块：
insmod rtvmm.ko
来启动 RT-Thread。RT-Thread 启动之后控制台在第二个串口上(Atl + Ctrl + 4)。第一个串口Linux shell依然可以使用，第二个串口则是RT-Thread的shell。
- JavaScript解析器，这个是由牛头哥移植的，可以在一个非常小资料的MCU上以JavaScript脚本方式进行编程、开发。根据这种方式，也提供了RN001JS的以太网硬件模块：以JavaScript脚本语言作为二次开发，提供在线web(即WebIDE)进行编程并运行JavaScript程序。JavaScript作为一门轻量级、解释型的语言，更容易上手，配合WebIDE、及提供的一些example可以使得开发变得非常的轻松，也包括一些传感器的JavaScript例子，让做网页的人也可以玩硬件了！

# RT-Thread 1.2.1更改说明

发布时间: 2014/4/8
	
在原有的1.2.0版本的bug修正版本，也是1.2.0系列的第一个修正版本，原则上不添加任何的新功能，我们尽量会按照每个季度一个修订版本的方式推进。大家在使用的过程中有什么问题还请反馈给我们，这些问题很可能会在下个版本中修正！

以下是更改记录：

## 内核

* 用户应用，增加用户应用命令行参数支持；
* 在挂起一个任务时，把相应的定时器也关闭；

## BSP

* BeagleBone，加入更多串口驱动支持；
* 移除BSP中rt_device_init_all函数调用，改成打开设备时自动进行初始化；
* LPC176x，移除components初始化管理器；
* LPC4088，修正LED驱动的问题；
* STM32F107，移除components初始化管理器；

## 组件

* 文件系统，ELM FatFS加入对扇区不匹配情况下的信息输出，这样能够及时定位问题；
* 文件系统，NFS网络文件系统修正相关的一些编译警告信息；
* 文件系统，copy命令加入文件夹方式复制功能；
* 文件系统，RAMFS，加入到components初始化管理器中；
* 文件系统，ROMFS，用于转换文件的工具mkromfs.py，增加Linux主机的支持；
* CMSIS更新到3.2.0版本；
* 串口驱动框架加入serial->ops->control的调用；
* 命令行系统，优化msh，支持用户应用的命令行参数；
* 命令行系统，当使用msh时，默认使用msh >的命令行提示符；
* TCP/IP协议栈，导出更多的lwIP接口给用户应用；
* POSIX thread，修正了同时使用lwIP组件时的编译警告；
* 第三方组件，加入TJPGD的移植，加入libpng的移植；

## 工具

* 固件加入scons --target=ua -s，用于准备用户应用环境；

[发布后记]
* RT-Thread携带了众多的BSP，不一定能够一一保证每个分支上把RT-Thread上相应的功能使用起来。所以针对这种情况，我们有一款评估用的硬件开发板：RealBoard 4088，在上面力求把一些相关例程都添加上，这样在一个基本的BSP基础上，可以对照着把其他的组件、功能添加进去；
* RealBoard 4088使用的RT-Thread版本主要以RT-Thread 1.2.1版本为主。

# RT-Thread 1.2.0正式版本更改说明

发布时间: 2014/1/6 

实现roadmap中提到的大部分内容
	
1，文档方面已完成《RT-Thread编程手册》，同时还有论坛上jiezhi童鞋的《一起来学RT-Thread系列连载教程》
2，BSP分支方面新增cortext-A8(beaglebone)，cortext-R4(rm48x50)，UNITY-2(SEP6200),lpc408x的移植
3，组件方面：
- 加入msh(类似linux shell的风格)，能够直接执行应用程序
- 新增freemodbus 1.6.0的移植
- 新增开源的嵌入式关系数据库SQLite 3.8.1的移植
- 新增Ymodem协议
- 默认使用lwIP 1.4.1

下面是自RT-Thread 1.2.0 RC版本发布以来具体的变更履历：

## 内核

* timer.c - 使用跳跃表(skip list)实现系统定时器链表，并在bsp中的startup.c中重新加入定时器初始化函数rt_system_timer_init()
* rtdebug.h - 新增宏定义RT_DEBUG_IN_THREAD_CONTEXT
* idle.c - 在函数rt_thread_idle_excute()中一次清除所有的死线程
* scheduler.c - 新增API rt_critical_level()返回调度器上锁次数

## 移植

* cortex-m0 - 修正 cortex-m0 GCC移植中hardfault的问题点
* cortex-r4 - 在startup后释放IRQ堆栈空间
* cortex-r4 - 按字节长度分配堆栈空间

## BSP分支

* 新增lpc408x移植
* bsp/stm32f0x - 增加USART1，USART2驱动，支持finsh，支持组件初始化
* bsp/simulator - 当RTGUI配置无效时打印错误信息
* bsp/simulator - 默认情况下关闭RTGUI选项
* bsp/simulator - 增加createdef.py文件来生成VS的def文件
* bsp/simulator - 当使用VC++编译时去除_TIME_T_DEFINED的定义
* bsp/xplorer4330 - 重命名文件Retarget.c为retarget.c,否则linux系统中编译会报错
* bsp/xplorer4330 - 修正GCC编译链接时关于ENTRY的警告
* bsp/rm48x50 - 新增GCC的移植
* bsp/K60Fxxxx - 修正一个编译错误

## 组件

* dfs - 正确处理mkfs未实现的情况
* dfs - 使用指针代替index变量
* dfs - 在函数dfs_filesystem_lookup()将含义模糊的指针变量名称empty重命名为fs
* dfs - 修正dfs_unmount问题点
* dfs - 在设备打开错误时令挂载失败
* dfs/elmfat - 令elmfatfs每次都检查扇区大小
* net - 新增freemodbus 1.6.0的移植
* finsh - 新增FINSH_USING_MSH_ONLY选项
* finsh - 只有当shell设备为空时调用rt_console_get_device()
* finsh - 修正FINSH_USING_SYMTAB未定义的错误
* finsh - 重构control按键的处理
* msh - 增加文件和路径名称自动补全的功能
* msh - msh内增加执行module的功能
* msh - msh内增加更多的命令
* libc - 修正 _sys_read()/_sys_write()问题点
* external - 增加开源的嵌入式关系数据库SQLite 3.8.1的移植
* pthreads - 避免ESHUTDOWN重复定义
* mtd_nand - 在MTD nand中增加更多的调试措施
* mtd_nand - 修正操作MTD nand时起始块错误的问题
* lwip-1.4.1 - 在lwIP内加入更多的RT-Thread选项设置
* log_trace - 修正函数memmove()参数使用错误的问题
* drivers/pipe - 增加一个control命令来获得pipe剩余的空间
* drivers/serial - 如果读写长度为0，则立即返回

## 例程

* examples - 用rt_sem_control()中的RT_IPC_CMD_RESET命令rt_sem_trytake()来清除信号量
* examples - 始终打印输出测试结果
* examples - 在所有的测试结束后打印输出简报
* examples - 在TC线程中清除变量_tc_stat的TC_STAT_RUNNING状态
* examples - 重新实现loop功能，并新增finsh命令tc_loop
* examples - 在tc_stop中增加延时，由原来的延时RT_TICK_PER_SECOND/2调整为10 * RT_TICK_PER_SECOND
* examples - 在SConscript中判断TC如果被使能，在CPPPATH中增加TC路径
* examples - 新增一个in-mem-log的例子
* semaphore_priority.c - 在cleanup时释放信号量
* heap_realloc.c - 检查调用realloc(ptr, 0)是否成功
* thread_delete.c - tc线程的延时应该比tid2的延时长，保证其测试过程中正常运行
* thread_delay.c - 放宽超时判断条件，因为当RT_TICK_PER_SECOND为1000时，容易产生1个tick的误差
* semaphore_static.c - 放宽超时判断条件，因为当RT_TICK_PER_SECOND为1000时，容易产生1个tick的误差
* semaphore_dynamic.c - 放宽超时判断条件，因为当RT_TICK_PER_SECOND为1000时，容易产生1个tick的误差

其他：
* 更新README.md
	
# RT-Thread 1.2.0RC更改说明

发布时间: 2013/10/10/ 10:19
	 
主要说明: 该版本新增ARM Cortex-A8的支持(BeagleBone)，新增UNITY-2内核的支持(SEP6200)，新增Ymodem协议。

变更履历
========

[内核]

* 修正rtdef.h中的拼写错误(_MSC_VER_ -> _MSC_VER)
* 修正scheduler.c中的调试打印输出错误
* ipc - 在函数rt_event_recv()中增加对参数option有效性的检查
* device - 增加统计设备引用次数的变量ref_count
* memheap - 修正内存块分割问题点
* memheap - 优化函数rt_memheap_realloc()
* kservice - 函数声明使用rt_vsnprintf代替vsnprintf


[组件]

* dfs - 修正dfs_file.c中一处变量参数类型错误的问题
* dfs - 增加mount table
* dfs - 在building脚本中加入ramfs的支持
* dfs - 修正ramfs中O_APPEND write的问题
* dfs/elm - 在mkfs中加入device_open/close
* dfs/jffs2 - 修正jffs2_opn/opendir中的f_flag初始化问题
* dfs/jffs2 - 修正jffs2卸载问题
* pthread - 修正一处编译警告
* drivers/pipe - 增加rt_pipe_init/rt_pipe_detach
* drivers/pipe - 增加非阻塞读写和强制写模式
* drivers/pipe - 当恢复读的时候调用函数rx_indicate()
* drivers/pipe - 增加一个设备类型(pipe类型)
* drivers/portal - 实现portal设备类型
* drivers/ringbuffer - 修改一些模糊不清的函数名称
* drivers/ringbuffer - 新增put_force和putchar_force接口函数
* finsh - 当set_device时增加设备检查
* finsh - 在rx_ind中增加对shell设备的自动设置
* finsh - 增加pipe和portal设备的描述
* finsh - 在变量定义时使用别名
* finsh - 当关闭设备时注销rx_indicate
* finsh - 修正命令行太长的问题
* finsh/msh - 只有当DFS_USING_WORKDIR使能时才声明cd/pwd
* init - 为新的组件初始化机制更新连接脚本
* init - 增加组件初始化调试代码
* logtrace - 整理代码，去除编译警告
* logtrace - 增加LOG_TRACE_VERBOSE
* logtrace - 调整log values
* logtrace - 只有当finsh使能的时候才声明cmd
* libc/minilibc - 在sys/time.h中增加gettimeofday的声明
* utilities - 新增ymodem

工具:

* building.py - 增加clang静态缝隙器的支持
* building.py - 为Keil MDK增加buildlib功能
* building.py - 在clang-analyze中执行'clang -Wall -fsyntas-only'
* clang-analyze.py - 增加一个定制工具实现clang静态分析

分支:

* 新增BeagleBone的移植
* 新增SEP6200的移植
* 新增K60Fxxxx的移植
* 修正Linux中的编译错误(lm4f232, stm32f40x, xplorer4330)
* cortex-m3 - 加强hard fault的异常处理函数
* at91sam9260 - 更新串口驱动，使用组件中的通用串口驱动
* at91sam9260 - 更新工程目录结构
* at91sam9260 - 修正编译错误
* at91sam9260 - 内嵌GPLv2许可
* stm32f10x - 删除无用的文件
* stm32f10x - 更新工程目录结构
* stm32f10x - 更新工程文件
* stm32f10x - 为使用新的组件初始化更新连接脚本
* stm32f10x - 为使用新的组件初始化更新SD card驱动
* stm32f10x - 为使用新的组件初始化更新DM9000驱动
* stm32f10x - 更新串口驱动，使用组件中的通用串口驱动
* stm32f10x - 修正rtgui初始化问题
* simulator - 为使用新的组件初始化更新代码，以便支持mingw
* simulator - 支持Linux系统
* simulator - 修正Linux系统中的SDL初始化问题
* simulator - 在rt_components_init之后初始化SDL
* simulator - 将对SDL设置的内容移入drivers/SConstruct
* simulator - 在env中获得CORSS_TOOL和EXEC_PATH的值
* simulator - 支持clang-analyze
* simulator - 增加tap netif driver

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------


版本: RT-Thread 1.2.0 Beta 版本

发布时间: 2013/6/30
		
进过开发人员三个月的努力，RT-Thread 1.2.0 Beta 版本如期发布。
该版本默认采用lwIP 1.4.1协议栈，USB device stack也进一步完善。加入 log_trace 子系统，加入组件初始化升级版本，加入 ARM Cortex-R 的移植。

主要变化：

* 1，新增组件初始化功能
- 详情请看论坛帖子[新功能] 组件初始化
* 2，支持ARM Cortex-R系列处理器
- Grissiom 完成 ARM Cortex-R 的移植，目前BSP中已有TI RM48x50分支（仅支持TI CCS开发环境）
* 3，文件系统中新增 RAMFS
* 4，加入 log_trace 子系统
* 5，优化Cortex-M4线程上下文切换，使用了浮点运算的线程才保存及恢复FPU寄存器
- 详情请看论坛帖子[优化]cortex-m4f线程切换，优化FPU寄存器
* 6，新增API rt_memheap_realloc()
* 7，重新实现ringbuffer，采用镜像的方法区分“满”和“空”，同时支持任意大小的buffer
* 8，内核中加入RT_KERNEL_MALLOC/RT_KERNEL_FREE/RT_KERNEL_REALLOC宏。
如果用户未定义这些宏，将默认指向rt_malloc/rt_free/rt_realloc。
同时内核仅局限于使用这些宏来使用动态内存
* 9，在 building.py 中新增生成 cscope database 的选项
* 10，USB组件新增reset函数，支持热插拔
* 11，scons编译系统支持CCS开发环境
* 12，USB组件新增状态信息（USB_STATE_NOTATTACHED，USB_STATE_ATTACHED，USB_STATE_POWERED...）

修复问题点：

* 1，USB组件HOST可以挂起endpoints
* 2，simulator分支，修复 serial_write 问题
* 3，udisk可以被弹出
* 4，iar.py中修复绝对路径的问题
* 5，dfs_fs.h内增加dfs_mkfs()函数的申明
* 6，生成MDK工程文件的时候加入library文件
* 7，当PC不再接受数据的时候，重置VCOM相应的状态
* 8，USB组件：返回正确的LangID字符串长度给HOST
* 9，Cortex-M0，Cortex-M3，Cortex-M4上下文切换时，回收系统初始化时用到的栈空间

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------



版本: RT-Thread 1.2.0 Alpha版本

发布时间: 2013/4/10
	
遵循2013年RT-Thread roadmap，RT-Thread 1.2.0 Alpha版本发布，Alpha意味着此版本为技术预览版，仅用于展示RT-Thread 1.2.0未来的发展方向，并不适合于开发正式产品。RT-Thread 1.2.0版本是1.1.x系列的下一个分支，这个分支主要体现的是RT-Thread 1.x系列的文档情况。当然也有一些功能、代码方面的增强。

伴随着新版本的到来，RT-Thread有几个重大的转变：
1，代码托管从google code(SVN)迁移到github(GIT)
2，RT-Thread与RTGUI区分开来，并成为两个独立的开发分支
3，重视文档，将文档建设作为1.2.0版本的首要任务来抓

内核主要变化：
1，加入__rt_ffs函数用于实现32位整数中获取第一个置1的位；同时调度器中位图相关算法直接使用__rt_ffs函数；CPU移植时，可定义RT_USING_CPU_FFS，使用芯片指令完成。

2，新的中断注册机制
weety加入interrupt description功能，用于为interrupt增加更多的信息，同时中断服务例程也可以携带用户自定义的参数类型。
* 这部分对ARM7、ARM9、MIPS等影响很大，需要对CPU移植做相应的一些修改。
* 这部分对ARM Cortex-M系列芯片没有影响。

3，调整定时器插入位置，为相同超时定时的后面。

组件主要变化：
1，添加lwIP 1.4.1。
2，在finsh shell中加入module shell功能。finsh shell本身是一个C语言表达式的shell命令行，而module shell更类似于一个传统的命令行，由命令，参数等方式构成。

分支主要变化：
1，完善simulator分支，支持RTGUI，支持应用模块。
2，完善at91sam9260分支的移植及驱动更新。

编译系统主要变化：
1，开启省略编译时长命令特性，如果需要查看编译时命令行，可以使用scons --verbose查看。
2，加入生成CodeBlocks工程特性。
3，修正当系统安装使用Keil MDK 4.6+版本的问题。

github主要提交履历:
5646189b29: elm fatfs支持mkfs，并且无需提前执行dfs_mount; mount/umount/mkfs操作也不会引起reset
22786f8817: 允许用户自定义PID和VID
0001344105: 更明确的定时器运行机制，如果两个定时器在同一个时刻发生超时，那么先开始的定时器先处理
5d68ef8ec1: 修正使用64位GCC时编译finsh过程中发生错误的问题
a4d661dcf1: 修正dfs_elm.c中一处内存泄露，并且在mount fatfs失败时执行 umount fatfs操作
43228aeb9c: 修正list_tcps问题：ipaddr_ntoa不是可重入的函数。
3de4b92a68: 修正AT91SAM9260分支中PHY link状态错误的问题。
1abaa0492d
