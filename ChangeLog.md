# RT-Thread v5.0.2 released

Change Log Since v5.0.1 Release

## Kernel

* include/rtdef.h
  * Fixed two issues with atomic volatile in bsp/simulator compiled in VS2019.
  * Added RT_USING_LIBC_ISO_ONLY macro.
  * Supported POSIX-compatible errno.
* src/kservice.c
  * Improved rt_strerror function compatibility.
* Supported DM device id management; Supported multiple threads receiving the same event at the same time.
* No longer used RT_DEBUG_LOG in rtdebug.h.
* Tidied up debug macros and added RT DEBUGING CONTEXT.
* Fixed User mode MQ receive blocking issue.
* Added priority to message queues supported in POSIX interfaces.
* Removed recursion in mutex; Removed RT_DEBUG_xxx macros.
* Implemented default weak function for rt_hw_cpu_shutdown.

## Components

* **drivers**
  * **sensor:** Fixed an error in Sensor-V1 where the return type was inconsistent; Re-implemented sensor framework as Sensor-V2.
  * **fdt:** Added the device tree child node search macro.
  * **tty:** Fixed a bug on foreground app switch; Supported TCGETA/TCSETAF/TCSETAW/TCSETA commands.
  * **serial:** Fixed an issue where the serial port sometimes sent carriage returns repeatedly.
  * Supported the Core API for dd2.0.
  * **i2c:** Optimized control interface format to add available commands.
  * **rtc:** Reconfigurable clock framework; Fixed the bug that triggered the alarm for a single time and repeatedly used the timer that did not start.
  * **hwtimer:** Overflow is invalid in oneshot mode.
  * **core:** Revised the macros of header files.
  * **wlan:** Fixed some variables not used warnings when building.
  * Moved the core header files to the path: include/drivers/core.
* **lwp**
  * Executed elf with added executable permissions check.
  * Supported more features of signals from IEEE Std 1003.1-2017.
  * Fixed possible memory leak; Fixed the setup of fake LWP in sys_execve; Fixed socket addr bug; Fixed waitpid function exception.
  * Fixed bugs on LWP kill; Fixed exit(2) and added exit_group(2); Fixed rt_memcpy to lwp_memcpy in smart source; Fixed cmd_kill (Fix cmd_kill).
  * Added fops for dfs_v2 and fixed warning for eventfd_write and eventfd_read after dfs_v1 changes.
  * Cumulative updates of lwip and lwp.
* **libc**
  * Updated the allocation mode of the libc timer id.
  * Added signalfd for system call, Added eventfd for system call.
  * Implemented lightweight timezone configuration.
  * Renamed libc.c as posix/stdio.c.
  * Optimized the epoll code to remove restrictions on descriptors.
  * Adapted rt_channel, increased the generality of some rt_channel functionality on dfs v2, and standardized signalfd.
* **dfs**
  * Fixed variable usage errors in dfs elm.c.
  * Connected the posix mqueue pair to the file system fd.
  * Modified some function prototypes of the dfs_file_ops structure and function declarations.
  * Fixed fcntl(F_SETFL) bug, and modified the error code when opening a file failed.
  * Cumulative repair of dfs changes, including forced uninstallation and pread/pwrite changes.
  * dfs v2: Added cromfs function.
* **utilities**
  * Supported ulog_async_output_enabled, Supported adt API for DM.
  * Removed zmodem.
* **mm**
  * Improved output of list_page.
  * Added unmap page API.
* **net**
  * **sal/socket:** Fixed a BUG where calling closesocket interface triggered assertions when RT_DEBUG is enabled; Fixed duplicate free on allocated buffer.
  * **sal:** Fixed the IPv4 & v6 compiling issue.
* **ktime**
  * Added RT_USING_KTIME to Kconfig build.
  * Fixed some bugs with ktime.
  * Optimized the performance of high-precision timer, deleted a useless function.
  * Change the Ktime path to: components/drivers/ktime.
* **sdio**
  * Enabled the eMMC internal cache to speed up transmission.
* **finsh**
  * Added msh autocomplete suboption feature.

## Drivers Device

* Prepared for device driver v2.0.

## Libcpu

* **aarch64:** Fixed default core binding failure on GICv2; Fixed aarch64 SMP startup failure; Supported hardware atomic; Fixed up FPU storage's size in stack and appended Q16 ~ Q31; Fixed HW atomic_t ops type from dword to qword; Supported public linker scripts; Changed aarch64 trap backtrace & coredump priority rating; Fixed an issue where AARCH64 Qemu failed to compile when SMP was disabled.
* **arm:** Fixed IAR compilation warnings: function "__LDREX" declared implicitly; Modified start_gcc.S; Fixed race condition with ldrex, strex; Fixed header file circular reference issue.
* **arc:** Fixed the thread switching bug in the arc architecture.
* **sim:** Fixed an issue with inconsistent function definitions.
* Added ARCH_ARM_CORTEX_M23 macro definitions.

## Tools

* Fixed .uvoptx/uvopt project name.
* Supported Env for finsh shell.
* Removed --dist-strip command.
* Corrected prompt message.

## Action

* Added CI to compile more drivers for the changed BSP, Added pkgs-test; Added the manual trigger and fail BSP check; Added more config for manual trigger.
* Added manual triggers for all STM32, Added the exp_STM32 SCons.
* Added the repo check for self-use; Added the code_owner review request; Added paths-ignore for format and static check.
* Fixed the path the YAML can't be folded; Fixed the flag of dist.
* Used env install script.

## Documents

* Added RT-Thread Code of Conduct; Added ktime readme doc; Added env vscode document.
* Fixed a typo in documentation.
* Updated env document, Updated qemu for windows doc; Updated quick_start_qemu_windows.

## Utest

* Adding volatile solves the problem that the test fails when the optimization level is high.
* Changed the thread size of the thread_tc thread stack to avoid stack anomalies caused by 64-bit machines; Changed the size of the thread stack to avoid stack anomalies.
* Added the signal dependency in signal test.

## BSP

* Added some new BSPs
  * ST: imx6ull, stm32u585-iot02a, stm32f405zgtx, stm32h563-st-nucleo, stm32h563-st-nucleo, stm32f407-rt-spark
  * SOPHGO: cv1800b
  * TI: msp432e401y-LaunchPad
* Supported Open Firmware API and model of PIC.
* Fixed MM32 compilation issues.
* stm32
  * stm32/stm32u5: Fixed GPIO interrupt error.
  * stm32/stm32l476-nucleo: Supported timer7 for RTduino; Supported PWM switch to SPI.
  * stm32/stm32wl55-st-nucleo: Fixed SCons compilation failure, improved link file, removed hardware floating-point support.
  * stm32/stm32f407-rt-spark: Release of the first version of rt-spark BSP; Added rt-spark to run utest link snippets under GCC.

  * stm32/stm32f401nucleo/rtduino: Supported function switching of docking pins.
  * stm32/stm32l431-BearPi: Supported the MPU6050 module.
  * stm32/rtduino: Supported tone timers and limited the maximum number of pins checked; Supported function switching of docking pins; Fixed a demo bug and modified the SPI switch function.
  * stm32/i2c driver: Replaced stm32_udelay with rt_hw_us_delay.
  * stm32/build path: Example Modified the STM32 project generation path.
* qemu
  * qemu-virt64-aarch64: Fixed qemu failed to mount elm file system.
* airm2m
  * airm2m/air32f103: Synchronized lib changes, including SRAM locking, fixing RTC acquisition frequency errors; Updated the pin num command.
* wch
  * wch/riscv/ch32v307v: Added _head_end for link file.
  * wch/riscv/ch32v208w: Fixed C++ compiling errors.
  * wch/risc-v/Libraries/ch32_drivers: Fixed UART IRQ declaration.
* imxrt
  * imxrt/imxrt1060-nxp-evk: Solved the adaptation problem of RW007 module in MIMXRT1062-EVKB board; Imxrt1060 fix wrong image reference.
  * imxrt/imxrt1021-nxp-evk: Fixed RT_ASSERT undefined RT1021 FIXED.
* renesas
  * renesas/sdhi driver: Fixed an issue where SDHI could only read the first block when attempting multiple block reads.
  * Fixed part of renesas BSP and added related CI to it; Fixed an issue where Renesas BSP compilation would not pass.
  * Added hwtimer device for renesas.
* acm32
  * acm32/acm32f0x0-nucleo: Fixed scons --dist command error.
  * Fixed some issues with acm32 BSP and added CI to it.
* bouffalo_lab
  * bouffalo_lab/bl808/d0: Added bl808 d0 core SPI and I2C drivers.
* nuvoton
  * nuvoton/numaker-m467hj: Fixed related LVGL version issues.
* Infineon
  * Infineon/psoc6-evaluationkit-062S2: Added I2C config for psoc6-evaluationkit; Fixed i2c init error; Added cyw43012 wifi module; Added BT support.
* esp32_c3
  * Realized scons compilation of ESP32-C3.
* raspberry-pico:
  * Added software simulation SPI and software simulation I2C driver code.
  * Optimized Kconfig configuration.
  * Improve UART driver.
  * Add flowcontrol and parity settings.
* phytium
  * phytium/aarch32/e2000d_rtthread: Phytium e2000 update.
  * Fixed the Phytium QSPI driver.
* hpmicro
  * Three new BSPS are added: hpm6750evk2, hpm6300evk, and hpm6200evk.
* gd32
  * gd32/arm/gd32470z-lckfb: Add SDRAM driver.
* nuclei
  * nuclei/gd32vf103_rvstar: Add USB-related configuration headers.

## Userapps

* Added support for user mode updates in MicroPython, sdl2, lua, ffmpeg.

# RT-Thread v5.0.1 released

Change log since v5.0.0 released

## Kernel

- Add stdc atomic detection. (#7536)
- Add API rt_hw_interrupt_is_disabled. (#7706)
- Add API to get object name and thread name (#7507)
- Add AMP rt_hw_cpu_id and RT_USING_SMP Macro decoupling,rt_hw_ipi_send depend on RT_USING_AMP
- Fix device_open oflag comparison error. (#7512)
- Fix thread.c variable rt_err not initialized timer.c type conversion error in iar
- Fix and add null pointer check
- Fix Avoid repeated calls device_open interface. (#7476)
- Modify rt_thread change the structure to explicit inheritance rt_object (#7131)

## Components

- DFS
  - Add dfs-v2.0
  - Fix potential Memory leak problems(#7378)
  - Fix tmpfs spinlock error. (#7216),nfs 64bit arch fault

- Libc
  - Support rt-thread CPP wrapper sub-switch macros, external third pary libc software package, picolibc heap
  - Optimize resource consumption
  - Modify redirecting header sys/ioctl to bits/ioctl, improve posix interface message queue
  - Modify if define cputime, then CLOCK_REALTIME use cputime (#7343)

- LWP
  - Add more syscall support.
  - Support file descriptor transmit (#7318)
- Support for scalable memory management (#7277)
  - Fix lwp _load_script. (#7405)
  - Modify rt_err_t change to sysret_t in the lwp_syscall (#7374)
  - Modify when fork Child process, lwp_struct_copy function adds copy working_directory function (# 7380)

- Network
  - Add more hook functions
  - Fix ping timeout calculation bug(#7545),ipv6 compatibility issues(#7339)
  - Fix next-hop finding in lwip_ip4_route_src. (#7504)
  - Modify use the interface to set the default netdev
  - optimize at_vprintfln and network related Kconfig

- Other
  - Fix Finsh offset used before range check
  - Support for scalable memory management (#7277)

## Drivers Device

- Fix cpu timer in multithreading (#7222),dtb compiling warning.
- Optimize the spi transfer speed and fix some issues
- Modify the ADC channel data type and add the built-in channel universal channel number identification
- Modify convert the current sensor framework back to v1 version and make it independent of v2 (# 7698)
- Modify changing tty's driver to a device and fixing multiple scanfs resulted in data loss issues

## Libcpu

add debug info for gdb

- arm: Optimize interrupt mode API,Fix atomic_arm.c
- aarch64: Optimize interrupt mode API,Decoupling startup process,Add no device tree mode in PSCI,Fix cache invalidate operation (#7363)
- risc-v:add ioremap for c906
- mips:Fix variable misuse

## Tools

- Add feature to filter out files to file_check.py that do not require cppcheck (#7499)- Add `--add-rtconfig` args for scons when you want to add macro definitions build time.
- Support llvm-arm 16.0; Add llvm-arm workflows.
- Fix cannot select c99 and gnu choice in Keil-MDK
- Fix the deque issue for Env['CPPDEFINES'] (#7541)
- Modify move file_check.py into ci folder

## action

- Refactoring and optimizing the execution process of ci and adding manual triggers and cppcheck checks for scons dist

## utest

- Add UtestTcTab section access under MSC and change access under gcc
- Fix strtol,the sizeof incorrect calculation,the issue of thread test case looping at high optimization levels,file open close mismatch

## bsp

fix mismatched function types in rt_pin_ops for all drv_gpio.c

- Add some new BSPs
  - apm32: apm32e103ze-evalboard apm32e103ze-tinyboard apm32f030r8-miniboard
  - at32: at32f423-start
  - essemi: es32vf2264
  - imxrt: imxrt1061-forlinx-OK1061-S
  - renesas: ra6m3-hmi-board
  - stm32: stm32f334-st-nucleo stm32l496-st-discovery
  - yichip: yc3122-pos
  - bouffalo_lab: bl808/d0
- Add RTduino support for some bsps
- Update some stm32 BSP drivers:  timer, uart v2, pwm, adc
- Update BSP
  - Add kconfig for some BSPs without kconfig
  - fix mismatched function types in rt_pin_ops for all drv_gpio.c (#7457)
  - stm32: Fixed some issues, added and improved some drivers
  - Renesas: Fixed some issues, added and improved some drivers
  - Infineon:Fix drv_gpio and spi problem,psoc6 add drv sdcard (#7522),update: READ.me use path of relative (#7500), fix spi chipselect
  - simulator:sync upstream win32 driver (#7165), Fix Linux support
  - airm2m/air32f103: update AIR32F10xLib (#7472)
  - allwinner:  update allwinnter libraries object file path (#7482)
  - apm32: add can driver and add apm32e1/s1 rtt driver support (#7170)
  - at32 : add support dac driver,update for perfection of drv_usart_v2 (#7210),fixed some
  - bouffalo_lab : add sdcard spi driver drv_i2c drv_soft_i2c hwtimer & flash driver support,update bouffalo_lab libraries && script, sdio host driver, uart driver pin && bl808-d0 ioremap mode
  - essemi: Update es32vf2264 some library functions and drivers
  - fujitsu: BSP support menuconfig
  - gd32: Add PWM driver for GD32F303
  - imxrt: Update to support Keil AC6, add link script files, improve SPI support, improve SPI support for RW007, and improve documentation
  - LPC4088: Increase support for IAR environment (# 7611)
  - lpc55sxx: update keil default project,update drv_soft_i2c drv_soft_spi drv_adc drv_wdt,add adaptation LVGL drv_lcd and drv_touch
  - raspberry-pico: add drv_soft_spi drv_adc drv_wdt drv_soft_i2c
  - rk3568:Support PSCI, amp mode

## Userapps

- Using xmake to build a system to replace the original scons
- Built in Toolchain, zlib and other software packages
- Can automatically generate images such as ext4 and fat
- Supports multiple architectures such as arm aarch64 riscv64
- Add built in QEMU runtime environment

# RT-Thread v5.0.0 released

Change log since v4.1.1 released

## kernel
- Add RT-Thread Smart features, Support user-mode app.
- Add atomic feature.
- Add nested mutex feature.
- Add rt_ssize_t data structure.
- Add static name for rt_object (#6422).
- Adopt new version macro definition version control specification: https://semver.org
- Split scheduler.c (#7103).
- Fix the Oz optimization problem of AC6 compiler in memheap.
- Fix rt_memset to be word size independent.
- Modify RT_ALIGN_SIZE as 8 by default

## Components
- Add FDT(Flattened Device Tree), TMPFS, CRomFS,
- Libc:
  - add musl libc support.
  - Improve Posix support.
- LWP:
  - Add more syscall support.
  - Add mm(virtual memory management layer) feature.
  - Improve clock accuracy.
- Network: add AF_UNIX feature.
- Drivers Device:
  - Improve device: sensor, spi, i2c, serial, can, usb, cpu_time, sdio, pwm, etc.

## BSP
- Add RT-Thread Smart support with some BSP: D1/D1s, raspberry, qemu-vexpress-a9, qemu-virt64-aarch64,qemu-virt64-riscv.
- Add company readme.md under bsp dir.
- Fix that use RT_ERROR, RT_EFULL, RT_ENOMEM, RT_EEMPTY, etc.
- Add some new BSPs:
  - bouffalo_lab: bl60x/bl70x/bl61x/bl808,
  - Infineon: 062s2, 062s3-4343w, 062s4, 062-wifi-bt, 062-ble
  - nuvoton: numaker-iot-m467, numaker-m467hj, numaker-hmi-ma35d1
  - nxp: LPC55S16, LPC55S36, LPC55S06, LPC5528, LPC55S28
  - nrf5xxx: nrf5340
  - gd32: gd32470z-lckfb, GD32303C-START
  - apm32: apm32f030r8-miniboard, apm32f051r8-evalboard, apm32f091vc-miniboard, apm32f103vb-miniboard, apm32f107vc-evalboard, apm32f407zg-evalboard,apm32f072vb-miniboard
  - n32: n32g43xcl-stb, n32g457qel-stb, n32g45xcl-stb, n32g45xml-stb, n32g45xrl-stb, n32g45xvl-stb, n32140xcl-stb, n321436_evb, n32143xml-stb, n32143xrl-stb, n32wb45xl-evb, n32g4frml-stb.
  - mm32: mm32f3270-100ask-pitaya
  - at32: at32f421-start, at32f425-start
  - stm32: stm32f723-st-disco
  - phytium: aarch32, aarch64
  - other: core-v-cv32e40p, air32f103, YS-F1Pro, etc.
- Update some stm32 BSP drivers: timer, pwm, uart v2, can, etc.
- Update BSP:
  - qemu-vexpress-a9: play the version number of QEMU when QEMU running.
  - tms320f28379d: fix the startup problem, implement PWM driver.
  - simulator: fix simulator compilation warnings, fix compile error.
  - raspberry-pico: add SMP
  - synopsys: Fix timer call-backs, Fix print syntax, Fix GNU toolchain RTT_CC alias, Use RTT_EXEC_PATH for the toolchain location substitution.
  - ti/c28x: add support to not disable global interrupt in context-switch to enable zero-latency isr for critical interrupts, add GPIO & pwm & ADC driver, update rt_vsnprintf for compliance with ti c28x cpus,add support to scons-based .project creation.
  - stm32: update all bsp projects.
  - renesas: add segger rtt function, add tft-lcd lvgl support, add ra6m4-cpk lvgl for spi-lcd support and update rt_spi_bus_attach_device_cspin function, add tft-lcd pin connection description, and fix some bugs, etc.
  - Infineon: add capsense support, add Infineon Doc and modify file structure, update spi driver, add slider driver demo, fix spi cs problem, etc.
  - nuvoton: modify RT_WEAK as rt_weak, fix building issue of Nuvoton porting, etc.
  - nxp: imxrt1170 Fix usb, Fix flexcan driver, add sdio support. lpc55s69 update PWM. lpc55sxx i2c driver fix & repair, add i2s and wm8904 driver, update spi and pwm driver. etc.
  - nrf5xxx: add spi twi drv for nrf5340, fix the Kconfig of nrf52832, etc.
  - gd32: fix bug on spi driver
  - apm32: fix apm32f0/apm32f1 gcc startup assembly file bug and fix apm32 drv_eth.c bug, add apm32F0 series MCU support, add apm32 rtt sdio/flash/sdram driver. etc.
  - at32: fixed gcc compiling usb driver errors, update for including file position and adding macros, optimize emac and usart driver code, add support usb driver. etc.
  - esp32: ESP32_C3 fix compile errors/warnings, igrate to ESP-IDF package, add I2C drivers. ESP32 support applying patch to local IDF. etc.
  - ch32: add rt_hw_context_switch_interrupt. ch32v307 add uart/spi/adc/gpio/wdt/dac/can/pwm drivers, update readme. etc.

## Libcpu
- arm: cortex-a revert safety MMU initialization, cortex-m7 change the return type of function rt_hw_cpu_dcache_ops to rt_uint32_t, etc.
- risc-v: support noncached normal memory, add rt_backtrace function, etc.
- aarch64: add rt_backtrace function, stop when no page is free.

## Tools
- Improved ci function
- Add some scons cmds: scons --exec-path=xxx, scons --exec-prefix=, scons --dist --target=xxx, scons --strict, scons --dist --project-path=xxxx, etc.

# RT-Thread v4.1.1 released

Change log since v4.1.0 released

## Kernel

* rtdef.h
    * Add BGR888 pixel format
    * be friendly to macro expansion
* add 64bit default value for stack size
* set tick HZ as 1000 by default
* enhanced rt_kprintf to support "long long" type
* use RT_KSERVICE_USING_STDLIB_MEMXXX to replace RT_KSERVICE_USING_STDLIB_MEMCP/MEMSET
* RT_KSERVICE_USING_STDLIB is open by default
* ipc
    * Add descriptions for rt_mq_recv and rt_sem_take timeout parameters
    * fix parameter name
* enable RT_DEBUG_DEVICE by default and move weak rt_hw_dealy_us in kservice.c
* Updated the Cortex-A of linker scripts for the new version of GCC, Removed C++ global constructor initialization, this method is not used in GCC4.7 and later versions
* remove the register keyword
* rename _rt_scheduler_stack_check as _scheduler_stack_check
* update comments for rt_thread_suspend
* fix comment for rt_container_of
* fixed bug of timer
* remove the executable permission of thread.c
* remove strnlen function
* add NULL check for rt_free and rt_free_align
* support perf_counter
* tighten size before check with mem_size_aligned
* Add string information for error
* fix a problem about finsh_set_prompt redefined msh command
* Unify the data type and macro definition of kernel built-in and standard LIBC library
* add macro RT_VERSION_CHECK  to implement version check
* fix the style for "rt_hw_us_delay" function
* fix the time slice logic for schedule.c

## Components

* driver
    * Detailed classification of devices types 
    * Update device type definition and command definition
    * ioctl add F_SETFL cmd
    * fix a problem that eliminate recursion
    * fix som compilation warning
* driver/serial_v2
    * add support for "termios"
    * add hardware flow control  support
    * fixed bug for RT_SERIAL_TX_BLOCKING model
    * add rt_assert for serial_v2
* driver/sensor
    * Add blood pressure sensor type
    * Add RT_SENSOR_VENDOR_MELEXIS in sensor.h
    * Add RT_SENSOR_VENDOR_MELEXIS in sensor_cmd.c
* driver/spi
    * remove _spi_bus_device_control
    * Fix rt_qspi_send symbol extension BUG
    * fix issue report #6008 rt_spi_sendrecv8
* driver/rtc
    * Adjust ops function input parameters
    * Optimize execution efficiency
    * Add get/set timestamp function
    * Enhanced date command
    * fix the parameter check about "time"
    * use gmtime_r to replace gmtime
* driver/alarm
    * Fix week alarm bug
    * Compact alarm output
    * fix a typo
* driver/inputcapture
    * add DBG_TAG for rt_inputcapure.c
* driver/hwtimer
    * add disable interrupt protection for hwtimer_isr function
* driver/hwcrypto
    * Optimize memory usage
* driver/sdio
    * Support DDR mode
    * modify the address offset problem for sdio read and write
* driver/dac
    * fix return value of rt_dac_write function
    * add get resolution method
* driver/adc
    * add a interface to get sampling resolution
    * add finsh voltage conversion command
    * implement adc_get_vref
* driver/pwm
    * clean the useless code
    * add finsh pwm function
* driver/usb
    * fix build error
    * fix stall bug on control transfers
    * add interface to get information about virtual uart connect state
    * fix usbhost hid issues
* driver/wlan
    * Modify wlan framework
* driver/phy
    * fix the PHY_FULL_DUPLEX conflicts
* driver/can
    * Add CANFD support and correct typos
    * Fix can infinite loop when can driver send error
* driver/hwcrypto
    * Correct function return value definition
* driver/pin
    * add pin operate command in MSH
* driver/touch
    * adjust the header file for touch.h
* libc
    * fix c/c++ compilation warnings and errors
    * improve sconscript
    * fix the sys/select.h problem
    * fix that some function cannot be found in unistd.h
    * Remove definitions that "posix/io" are not in use
    * fix the time bug
    * optimize the handle logic on armcc/armclang
    * fix the compiler error on iar
    * fix dlmodule compile 'SEEK_END' undeclared eror
    * the recycle logic about resource of pthread
    * fix the function pthread_barrier_init return "EINVAL" if "count" is zero.
    * solve the conflicts between libc data types and rtdef data types
    * remove strdup from rtthread.h
    * Fix clock_gettime for CLOCK_CPUTIME_ID
    * solve the libc/timer problem which the os tick can be calculated wrongly because the local variable was not initialized
    * implement extension standard C functions
    * fix the error return
    * modify the complier error in iar
    * use atomic operation to protect pthread conditional variable
    * memory leak when the value of posix semaphore is zero
    * fix a problem that function difftime() compile error in iar environment
    * pthread_mutex_destroy can't work
    * the risk for function exit() when open pthread support
    * supplement the case that exit() haven't been impletement
    * try to fix the problem about "fflush" functions in armlibc
    * use  ```__clang__``` to replace  ```__CLANG_ARM``` 
    * solve the compiling error for```_sys_ensure```
* ulog
    * Add file backend
    * Optimize unnecessary refresh
* sfud
    * support NM25Q128EVB, GD25Q32C, SST25VF080B, W25Q32BV, W25X16AV, W25X40CL
    * modify the opeated way to handle a situation that flash blocks protected 
    * keep macros in order
* sal 
    *  add draft for docking winsock
    *  rearrange sal dependencies
    *  rename sal.h as sal_low_lvl.h
* at
    * use pointer that memory had freed
    * implement about "AT server"
* lwip
    * Support windows simulator
    * add list command
* finish
    * fix list_device crash
    * Enhance system robustness
    * add available memory information for free cmd
    * add binary search algorithm
    * add new functions to get length of finish cmd 
* fal
    * support fal api for c++
    * modify PKG_USING_FAL to RT_USING_FAL
* utest
    * add cpp11 base testcase
    * enhance strength about cpp testcase
    * add posix testcase frame
    * add timeslice test
* ymodem
    * move error codes to rym_code to silence warnings
* Fix compilation warning

## BSP

* Attention, the list of new bsp we have added ：
    * at32f413, at32f415-start, at32f435-start, at32f437-start
    * cypress-psoc6-cy8cproto-4343w
    * ESP32_C3
    * gd32vf103r-start, gd32vf103v-eval
    * hc32f4a0
    * imxrt1021-nxp-evk, imxrt1170-nxp-evk
    * microchip, samc21, same54, same70, saml10
    * n32g45xvl-stb
    * ch32v103r-evt, ch569w-evt, ch32f103c8, ch32f203r-evt
    * rockchip-rk3568
    * stm32f103-100ask-mini, stm32f103-100ask-pro, stm32wle5-yizhilian-lm402

* lpc55sxx
    * fix issue that dist cannot specify a directory
    * fix building error

* stm32
    * use weak reference to handle Macro of RTDINO_xxxx
    * add new bsp for STM32WLE5JCI6
    * fix some can and pwm bug
    * select the input clk of spi based on SPI instances
    * fix the bug of can filter conflict
    * add rtc for openmv
    * add ov5640、dcmi、i2c for openmv
    * update ov5640 configuration of openmv
    * update  arduino related
    * stm32f072 support Arduino I2C and update readme
    * judge the SPI instances before operating
    * fix the io confict about SDIO and UART6(TX) DMA
    * fix the problem if use uart DMA to receive 
    * remove hardware NSS
    * Enable RNG Clock
    * avoid conflict between cmsis5 and bsp cmsis
    * add tim7 support
    * f072, f401 support TIM7/TIM11 hardware timer
    * l475, remove meaningless header file
    * stm32f407, stm32f469 optimize lvgl folder structure about simulator
    * stm32f746, cancel choose lwip and dfs by default
    * remove CMSIS/RTOS folders
    * add RTDUINO_NO_SETUP_LOOP
    * add F_CPU to indicate the frequency of CPU
    * suuport MsTimer2 library
    * add correct the command description for adc, pwm
    * add support for STM32L0 series
    * move CMSIS hearder files to common folder
    * add bootloader.bin, add the description of the bootloader in README.md for stm32h750-art-pi
    * Modify the content of flash algorithms in README.md for stm32h750-art-pi
    * fix stm32f767-st-nucleo console device name
    * create two new bsp for 100ask stm32f103 boards
    * add stm32l496zg feature, add on-chip flash
    * change the bsp name of 100ask to be consistent with other bsp and commit a bug for drv_adc.c
    * add h7 timer support
    * implement soft spi
    * use perf_counter to instead of hwtimer
    * support wireless module pinout for stm32l475
    * Add lvgl adaptation of touch screen xpt2046 for stm32f407-atk 
    * Docking lvgl for stm32f469-st-disco bsp using ft6336 touch chip
    * adapt the rtc alarm function
    * optimize pwm functions
    * Adapt RTduino package for stm32f469-st-disco BSP
    * Docking lvgl touch driver using package for stm32f469-st-disco BSP
    * Adapt lvgl for using ft6206 model touch screen for stm32f469-st-disco BSP
    * Fix the configuration of stm32f401's PWM in CubeMX
    * fix the network I/O is confict for stm32f429-atk-apollo
    * fix PWM complementary problem and function description
    * Improve the connection of RTdunio PWM for stm32f401-st-nucleo
    * add a new board f407-robomaster-c and supprot stm32 timer8
    * avoid the "recv_len" will be negative if happend accident
    * add RTdunio for stm32f103-blue-pill
    * stm32l475-atk-pandora update readme, .gitignore
    * update the Kconfig for stm32f407atk
    * remove libraries dependencies for rtduino function

* wch
    * add ch32v103r-evt bsp
    * add WCH CH569W-R0-1v0 evt board bsp port
    * ch569w-evt : add spi master driver, SPI0 tested
    * add pwm driver and spi_xfer bug fix

* gd32
    * Add gd32450i-eval board bsp
    * Complete the pins device define
    * firx adc driver
    * bug fixed gpio_mode_set miss gd32_spi->mosi_pin,gd32_spi->sck_pin
    * fix compile error in rtc: "pmu_backup_write_enable" was not found
    * Optimize GD32 bsp architecture
    * fix a bug about interrupt vetor table lost cause system exception
    * add driver of sdio
    * correct pin number in drv_gpio.c
    * fix compile error if use rtc in gd32 f1~f4
    * fix the defined error that uart I/O

* simulator
    * improve libc time and MSVC simulator
    * slove the problem of simulator can't attach SD card
    * upgrade SDL2.0 to 2.0.20
    * remove meaningless debug file
    * create new fcntl.h file for vs
    * optimize lvgl folder structure about simulator
    * avoid conflicts between winsock.h and sys/time.h
    * improve Kconfig structure add Onboard Peripheral Drivers menu
    * enable BSD socket by default
    * add RTC menuconfig
    * clean the compiler warning under windows
    * optimize the SD mount logic
    * remove LV_DISP_DEF_REFR_PERIOD which are defined manually
    * winsock implement on windows simulator
    * improve init process
    * sync lvgl win32 driver
    * fix some warnings
    * fix the problem of path cannot be find and cause failure
    * change "exit()" to "exit(1)"

* qemu
    * add compiler option "-Werror" for qemu-vexpress-a9 and qemu-virt64-aarch64
    * Add quick start guide for QEMU on macOS
    * chmod u+x shell script for qemu-risc-virt64
    * remove LV_DISP_DEF_REFR_PERIOD which are defined manually
    * rename qemu-riscv-virt64 to qemu-virt64-riscv
    * add remount operation to avoid dfs_mout fail for qemu-vexpress-a9
    * don't use sbi in m-mode for qemu-virt64-riscv
    * Add more VirtIO drivers for qemu-virt64-aarch64
    * Fixup VirtIO queue align size  for qemu-virt64-aarch64
    * improve qemu readme
    * update qemu project
    * Add VirtIO-Console and GPIO driver for qemu-virt64-aarch64
    * Update drivers' code for qemu-virt64-aarch64

* airm2m

    * fix the exception for i2c

* n32g452xx
    * add spi3
    * avoid system pause when timeout check
    * add hardware CRC support
    * update the driver about "can"

* microchip
    * Add Microchip SAM series MCU support
    * add ethernet, ADC, IIC support
    * update the serial driver for samc21/same54/same70
    * add SAML10 series

* nuvoton
    * Disable TRNG function in default configuration
    * Update nuc980iot configuration
    * remove LV_DISP_DEF_REFR_PERIOD which are defined manually
    * Add private data pointer for MTD-NAND

* at32
    * add at32f435_437 board 
    * update at32f435_437 adc driver
    * add at32f413 and at32f415 series
    * modify the folder structure
    * optimize code to improve network throughput performance

* NXP
    * rt1052 add RT-Thread studio entrance
    * imxrt1060 exchange On-chip Peripheral Drivers and Onboard Peripheral Drivers menu in Kconfig
    * prepare to support squareline studio
    * imxrt1060 optimize lvgl folder structure about simulator
    * imxrt1060 support NXP GUiGuider
    * imxrt1060 support keil armclang compiler
    * support touchpad
    * add rt1170/rt1020 bsp
    * update rt1170n menuconfig
    * Implement api docking of rt_pin_get
    * Fixed Touch pannel for imxrt1060-nxp-evk
    * mimxrt1170 Qspi flash bootup problems
    * optimize the "sconsript" under floder "applications"
    * Added LCD Touch Int pin to ioconfig
    * During testing GT911 would not come out of reset because INT pin could not be driven low or high.
    * upgrade the SDK of RT1170-EVK to 2.12
    * fix a tiny problme this is report in slack group for imxrt1060
    * remove suareline studio specific support for imxrt1060
    * update enet for rt1170
    * fix gpio interrupt bug in drv_gpio.c
    * format issue report in slack group
    * move phy driver into drivers folder
    * add double network interface and driver for phy8211F
    * add sdram driver for rt1170
    * fix the compiler error bettwen "rtc.c/rtc.h"
    * format files for rt1170

* Nuclei

    * add null CCFLAGS for Nuclei bsps

* renesas
    * add BSP doc
    * add RA2L1-CPK bsp
    * refreash the driver about flash, gpio and head file
    * add introduction of captouch
    * fix the error on drv_wdt.c
    * Add hardware i2c driver.

* essemi
    * update es32f36xx libraries
    * Adapt es32f369x for RTduino
    * Fix a bug of I2C and edit some documents 
    * remove libraries dependencies for rtduino function

* esp
    * add the bsp of esp32c3
    * Add the gpio driver and readme.md for esp32c3
    * add Kconfig esp32c3
    * add ESP32 UART driver

* k210
    * use new SDK packages
    * modify the folder structure of Kconfig

* HC32
    * Add the BSP of HC32 series
    * add rtc driver
    * Unified management interrupt vector table
    * configuration file revise
    * add usart1/2/3 configure for hc32f460
    * add can support
    * Fixed a problem where the descriptor for multiple serial ports was overwritten
    * add virtual iic driver
    * add adc support
    * fix bugs of hc32 driver adc and can
    * add rtc driver for hc32f460
    * support MDK AC6 compiler
    * fix the system crash if can bus is under bus off state
    * fix a problem that configure can filter is useless
    * fix a problem that error interrupt isn't work
    * modify precompile waring for uart,spi driver
    * add the driver about timerA
    * change RT_CONSOLE_DEVICE_NAME from "uart" to "uart1"
    * add startup file for apm32f4xx
    * add the driver of WDT

* raspberry-pico
    * optimize lvgl folder structure
    * Fix the issue of inaccurate system tick.

* nuc980

    * Fix bug when restarting and getting interrupts that are not processed

* rockchip

    * add rk2108 base support

* nrf5x

    * add doc for development on rtt-studio

* adapt lvgl 8.3.0

* n32
    * add n32 bsp
    * modify i2c and rtc drivers

* fm33lc026
    * add gpio support
    * refreash FM33LC0xx_FL_Driver to FL_xxx_v2.3.1

* apm32
    * add apm32f407ig-minibroard
    * add the F1xxx library of APM32 for APM32F10x_SDK_V1.6
    * add the F4xxx library of APM32 for APM32F4xx_SDK_V1.2

* ifx
    * add cypress board of  CY8CKIT-062S2-43012 
    * add hwtimer device

* raspi3-32

    * fix some bug of funtion '__rt_ffs'

* synwit

    * add swm341 bsp

* tms320f28379d

    * update .config: select FINSH_USING_SYMTAB
    * fix finsh problems of using sym table

## CPU

* arm
    * add dsb and isb instructions in the end of rt_hw_context_switch_to
    * fix compilation warning
    * Add exception install function
    * optimize the complier error
    * fix armclang error when enable LTO
    * fix rt_hw_cpu_dcache_ops clean invalid bug
* arm/Cortex-M33
    * Add Cortex M33
    * add macro ARCH_ARM_CORTEX_SECURE to makesure rtos system can run in the cpu safe mode
* arm/Cortex-R4
    * fix "prefethc abort"
    * add RT_USING_CPU_FFS to avoid redefined error about "__rt_ffs()"
* risc-v/virt64
    * fix parameter for call handle_trap

## Document

* Fixed the description of logging usage in the Contributing code Guide
* Update English coding style for more idiomatic use
* Overhaul of document, fixing multiple grammar mistakes and editing for clarity
* Further edits of documentation for clarity
* correct the license description
* Fix the doxygen file
* update env document append some information about menuconfig -s
* handle the grammar and wording fixes in memory.md
* update at/adc/hwtimer/i2c/pin/rtc/sensor docs

## Tools

* Fix bugs for processing command line parameters
* CI
    * update action use python@v3
    * add nxp check
    * update stm32 ci checking list
    * restrict rt-thread organization
* Copyright
    * improve copyright for old files
* Scons
    * sort the source file path
    * Add Python 3 compatibility patch
    * rtconfig.CROSS_TOOL->rtconfig.PLATFORM
    * Decouple the addition of command line arguments
    * support command: scons --target=xmake
    * Add CMAKE_EXPORT_COMPILE_COMMANDS ON for cmake
    * add new option for building library
* Readme.md add Deutsche and Spanish version
* update readme for languages choices
* append path for scons env
* Update the libs import for eclipse project
* modify the reorder problem for "include path"
* allow setting optional url for packages via envvar
* format python code
* remove .sconsign.dblite when scons clean



# RT-Thread v4.1.0 released

Change log since v4.1.0 Beta released

## Kernel

- src/clock.c add hook for rt_tick_increase
- fix thread init bug if you open RT_USING_MODULE
- Fixed issue that could all timers stop
- remove duplicated clear to 0 in the "thread.c"
- Revert modifications to the semaphore
- Fix 64 bit compilation warning
- src/device.c add RT_DEBUG_LOG

## Components

- ulog
  - Optimize code to improve readability
  - remove the useless function declaration about "localtime_r"
  - Optimize "ULOG_OUTPUT_FLOAT" to avoid use "vsnprintf" that provided by complier tools chain
  - solve the interference when enable the ulog timestamp
  - Fixed the issue LOG_HEX no output at asyn mode
- drivers
  - misc
    - modify the error name in the "dac.c"
  - remove useless head file to avoid problem about recursion
  - add the header file to avoid compiler error
  - Open RT_USING_POSIX_STDIO caused serial_v2 to compile failed
  - add the simulative spi bus drivers  that based on spi bus drivers
  - remove the complier warning in C99 about "ipc/ringbuffer.c"
  - improve serial_v2 structure
- dfs
  - offer complete path when use command "list_fd"
- libc
  - posix
    - add the included head file
    - add the header file to avoid compiler error
    - add RT_USING_POSIX_SOCKET
  - fix a typo
- net
  - adjust folder structure
  - lwip
    - integrate lwip porting layer
    - integrate and improve lwipopts.h
    - add lwip latest version
- utest
  - add dependence RT_USING_UTESTCASES
- finsh
  - remove extra code
  - fix finsh bug
- fal
  - add fal component
- utilities
  - adjust the order of compiler macros
  - var_export
    - replace the search algorithm and fix some problems
- tidy the folder name and structure about Kconfig

## BSP and CPU porting

- libcpu
  - aarch64
    - rt_hw_trap_irq get irq instead of iar when using gicv2
    - disable irq/fiq when switch thread
    - add gtimer frq set and stack align
    - add gicv3 support
  - mips
    - correct the watch dog register address about "gs232.h"
    - modify the problem that can't feed hardware watch dog
  - arm
    - fix syscall_iar.S compiler error based on cortex-m33
- essemi
  - fix bugs
- nuvoton
  - Update configuration files and fix issue
  - Nuvoton drivers updating and more LVGL supporting
  - Update drivers and project setting
  - format code
- raspberry-pico
  - add Raspberry-Pico-LVGL README.md
- simulator
  - Optimize the auto initization
- qemu
  - vexpress-a9
    - Fix a typo in qemu.sh
- n32g452xx
  - add drv_spi.c
- at91sam9260
  - add mtdnand driver to support "uffs" file system
- at32
  - upload bsp package based firmware library v2.0
  - add ingore_format.yml
- gd32
  - Optimize UART
- add Soft spi for gd32303e-eval
- ft32
  - modify the name that head files are included
- apm32
  - apm32f103xe-minibroard
    - add project and device drivers
    - update readme picture name
  - fix the startup files of apm32f1
- stm32
  - Add support with pwm6 to pwm13
  - add qspi flash and sdio for openmv h7plus
  - modify the bug that the CRC custom configuration can't work
  - stm32f469-st-disco
    - add readme in english
  - stm32f072-st-nucleo
    - add arduino support
    - support pwm for arduino
  - stm32f407-atk-explorer
    - add board identification word
  - stm32l475-atk-pandora
    - update application/arduino folder
    - enable i2c4 bus
    - fix the bug when using LCD demo
    - fullly  support analog output(PWM) and analog input(ADC)
    - support backlight with brightness adjustable
    - Adding dependencies
  - stm32h750-art-pi
    - porting LVGL to ART-Pi with Media-IO
  - stm32f769-st-disco
    - fix wrong CPPDEFINES and close lwip
    - add stm32f7xx_hal_dsi.c when using LTDC/MIPI-DSI
  - stm32h743-openmv-h7plus
    - add usbcdc for openmv
- imxrt
  - imxrt1060-nxp-evk
    - add imxrt1060-evk BSP
    - README_zh.md, led blink
    - fix gcc can't runing issue
- vango
  - add v85xxp bsp
  - migrate v85xx and v85xxp into the subcatalog of vango
  - remove duplicated files
- acm32f0x0-nucleo
  - Add some drivers
- delete swm320-lq100 bsp
- add ch579m bsp
- add air105 bsp
- add RA series bsp
- add bsp-ft32
- migrate acm32f0x0-nucleo and acm32f4xx-nucleo into the subcatalog of acm32
- migrate at91sam9260 and at91sam9g45 into the subcatalog of at91
- migrate mb9xxx series into the subcatalog of fujitsu
- migrate lsxx series into the subcatalog of loongson
- add rockchip/rk3568 bsp

## Documentation

- move documentation repo to rt-thread repo
- update documentation
- Fixed Program Memory Distribution - Basic.md

## Tools

- fix the problem that print 'b' when complier code that after RT-Threadv4.0.3
- use the relative path to create "CMakefile.txt" when use "scons" command
- allow users to set specific link scripts
- update the template for projcfg.ini in rt-studio
- keil.py Distinguish LOCAL_CFLAGS/LOCAL_CXXFLAGS, refine file control

# RT-Thread v4.1.0 Beta released

Change log since v4.0.4

## Kernel

- rt_show_version update the year
- Improve comments and parameter checking
- [pm] beautify code
- remove RT_THREAD_BLOCK
- remove .init_priority
- update notes
- Delete an extra semicolon
- change all double-empty-lines to single-empty-lines
- move some __on_rt_xxxxx_hook from rtdef.h to dedicated c soure files
- [kservice] add RT_KSERVICE_USING_STDLIB_MEMSET、 RT_KSERVICE_USING_STDLIB_MEMCPY
- [memheap] Fix 64 bit potential risk
- update Kconfig, add RT_HOOK_USING_FUNC_PTR
- Improving hooking methods
- Backward compatible with existing function-pointer based hooking method
- Using RT_USING_HOOK as an on/off switch
- Introducing a new low-overhead macro-based hooking method
- [include/rtthread.h] Add function declarations to avoid compilation warnings
- ipc init/create add flag judgement
- Adjust RT_ASSERT and RT_DEBUG_NOT_IN_INTERRUPT to maintain code style
- Add a new algorithm to find the lowest non-zero bit of a byte
- Add weak RT_KSERVICE_USING_TINY_FFS definition
- A simplified version of rt_ffs function
- Add RT_WEAK for rt_vsnprintf
- Change the return value type from signed int to int, in accordance with ISO C standards, to prevent compiler errors
- Fix rt_size_t as rt_uint32_t
- Cfg cancels rt_kprintf declaration
- [kservice] add return value's comment
- Modify rt_size_t's type
- [timer] Update the RT_TIMER_CTRL_GET_STATE code in rt_timer_control
- Fix up .bss size define in link.lds and set spsel=1 in aarch64
- remove duplicate work between idle and thread_exit
- When memheap memory management is used, rT_malloc 0 returns RT_NULL, consistent with slab and small memory management algorithms.
- Aligns the address passed in by rt_system_heap_init when using the memheap memory management algorithm
- Set rt_thread_timeout to a private function
- Add __attribute__(...) for rt_kprintf() to let the compiler check the format string parameters
- Return thread error when resumed by signal

## Components

- libc
  - Clear the POSIX/IO folder
  - Move libdl to posix folder
  - Add the support for PSE51
  - Optimize the nanosleep function
  - Add RT_USING_POSIX_STDIO
  - To deal with compilation problems under win32 platform
  - Remove getline
  - Create 'posix' folder and move related files into it
  - Put getline into posix folder
  - Optimize posix structure in libc
  - Eliminate judgments in code that rely on RT_LIBC_USING_FILEIO
  - Move libc.c/.h to posix folder
  - Remove gettid and other functions that do not comply with PSE51
  - Add RT_USING_POSIX_SELECT RT_USING_POSIX_POLL
  - Add RT_USING_POSIX_DELAY
  - Add RT_USING_POSIX_STDIO
  - Add delay.c as default
  - Select RT_USING_POSIX_STDIO for RT_LIBC_USING_FILEIO
  - Add readme
  - Revert kconfig of pthread
  - Move mmap to src folder
  - Implement delay functions as RT_USING_POSIX_DELAY
  - Fix a bug caused by two different macro encoding methods in fcntl.h
  - Improve IAR and KEIL's read write pile function
  - Memory functions add error warnings when HEAP is not enabled
  - Revise some RT_USING_POSIX to RT_USING_POSIX_DEVIO
  - Add RT_USING_POSIX_FS
  - Separate posix into a Kconfig directory
  - Fix the bug of _sys_read and _sys_write
  - Modify time.h to sys/time.h
  - Add dataqueue.c function annotation
  - Fix armclang Cpp11 memory leak and compilation warning issues
  - Add ipc header files
  - Create the mman folder

- drivers
  - Rename src folder as ipc
  - Optimize scripts for compiler judgment
  - Add rt_work_urgent
  - Change the time parameter to ticks to prevent misinterpretation of the unit as ms
  - Improve comment
  - [sdio] Fix compile warning and optimized code.
  - Rename rt_workqueue_critical_work as rt_workqueue_urgent_work
  - Fix sensor_cmd.c build error.
  - Cputime support 64bit.
  - Update cputime_cortexm.c support 64bit.
  - Add IPC for POSIX and add pipe for it
  - [components] framework update
  - Add waitqueue.c function annotation
  - Fix compile warning in cdc_vcom.c

- lwip
  - Improve lwip support for 64-bit architecture
  - Remove lwip 2.0.2
  - Fix ioctl and lwip socket definitions
  - modify annotation for sys_arch_mbox_tryfetch
  - Fix the return value for sys_arch_mbox_fetch in lwip stack
  - Fix dhcpd not including version 2.0.3
  - Define RT_USING_BIG_ENDIAN for the long-term version
  - ping cmd with specified netif in lwip-2.1.2
  - Fix sys_arch.c
  - Solve the conflict between multi BYTE_ORDER(s)
  - Fix the problem of implicit declaration for "lwip_ip4_route_src".

- dfs
  - Move dfs_posix.h to legacy/dfs/dfs_posix.h
  - Move dfs_posix dfs_poll dfs_select.c to posix folder
  - Remove dfs_select.h and dfs_poll.h
  - Update fatfs to the latest version
  - Saved dfs_poll.h dfs_select.h，add warning log
  - Remove RT_USING_LIBC from dfs_fs.h
  - Move dfs back

- Shrink pThread to POSIX. Change DFS from POSIX to POSIX from DFS
- Adjust the SAL dependency
- Implement legacy support
- Revise RT_USING_POSIX_STDIO to RT_USING_POSIX_DEVIO
- Add macro definition restrictions to finsh set Device calls

- shell
  - Update the list_timer cmd.
  - Update the code format

- kservice
  - Optimize RT_PRINTF_LONGLONG，reduce duplicate code
  - Simplification RT_PRINTF_PRECISION
  - Fix the problem of rt_strlen crashed in win32

- [kernel] Collating of Kconfig
- [ulog] Add ulog backend filter.
- [posix] Organize IO categories according to advanced Unix environment programming
- Add creat() function
- [Ymodem]  silent warnings
- Use rt_memcpy rt_memset instead of  memcpy memset
- Fixed AT component in CLI mode, the command input is too long, resulting in the array out of bounds
- [example] Remove RT_USING_TC
- Fix armclang Cpp11 memory leak and compilation warning issues
- Improve and add comments in examples/network/ including tcpserver.c

## BSP and CPU porting

- [at91sam9260] Fix "rt_interrupt_dispatch" Undefined error
- Add pulse encoder porting to imxrt1052
- libcpu
  - Solve the problem of mixing tab and space
  - [arm] Fix thumb instruction set assembly syntax error
  - [aarch64] Add smp support
  - [nuclei] Fix context switch  in nuclei
  - Fix s-mode issue
  - [t-head] Fix rt_hw_interrupt_disable/rt_hw_interrupt_enable bug
  - [libcpu] Add ARCH_CPU_BIG_ENDIAN

- Add and update gd32 bsp
  - gd32103c-eval
  - gd32105c-eval
  - gd32107c-eval
  - gd32303e-eval
  - gd32450z-eval
  - gd32105r-start
  - gd32205r-start
  - gd32305r-start

- Update n32g452xx
  - Reinit .config based on default setting
  - Regenerate rtconfig.h based on default configuration
  - Reformat code
  - Init update
  - Add rt_pin_get support
  - Add n32g45x can driver
  - Unified header file definition. "GPIO_H__" to "DRV_GPIO_H". "USART_H" to "DRV_USART_H"
  - In drv_pwm.c, variable meaning is different with RT-Thread interface definition. Fixed and tested.
  - Add support for UART4/UART5.
  - In drv_gpio.c Modify "N32F10X_PIN_NUMBERS" to "N32G45X_PIN_NUMBERS"
  - Perfect ADC driver and format code
  - Add ble support
  - Fix formatting issues
  - Remove unnecessary comments
  - Add gpio input nopull
  - rtc add version check
  - n32g452xx direct structure base at32

- Nuvoton
  - Support LVGLv81 RTT music demo for N9H30 and NUC980.
  - Update drivers
  - [N9H30/NUC980] Update SDH driver
  - Fix SDH_Set_clock function.
  - Correct EMMC, SDH0 and SDH1 options for N9H30.
  - Fix IRQ trap issues.
  - Update porting drivers and configurations.

- [raspberry-pico] Add lvgl_8.1.0 support
- simulator
  - Resolves the warning that the "Gm" option was rejected and will be removed in a future release
  - Clear the warning under vs
  - update project

- [gd32] Repair startup_gd32f30x_cl.s
- Remove the problematic rtconfig.h
- [console] Fixed an error when using device without defining RT_USING_DEVICE
- Use __clang__ instead of __CLANG_ARM

- Update essemi bsp
  - es32f0654
  - es32f369x
  - es32f365x

- [nuclei] change hbird_eval bsp to nuclei_fpga_eval
- The sconscript script in the application folder increases the recursion searching capability
- [Vango V85xx] modify NULL to RT_NULL
- fix the compiling issue for qemu-riscv64
- update K210 bsp and base on https://github.com/kendryte/K210-Micropython-OpenMV

- [lpc55s69_nxp_evk]
  - Fix the scons --dist
  - Add the fixed gcc version
  - Add the ci machine

- Correction of 'BSP /Copyright notice.md' errors

- nrf5x
  - Add the fixed lds
  - Add hwtimer driver
  - Add hwtimer config & tinyusb config
  - Fix i2c driver bug

- Remove the bsp of nrf51822
- Add tkm32f499 bsp and  flash_download app
- Remove empty rt_hw_us_delay
- [at32] Optimized the pin-index algorithm

- ra6m4
  - Organize the project configuration
  - Add DAC, ADC and SPI drivers
  - Formatting code Style
  - Add Flash Driver
  - Add SPI, Flash, ADC, DAC documentation
  - Add PWM driver
  - Fix incorrect dependency macros in scons scripts
  - Fix bugs in the code
  - Update the error description in the documentation

- MAX32660-EVK
  - Update pin map instruction
  - Add MAX32660-EVK pin map
  - drv_soft_i2c.c was not in libraries
  - delete drv_soft_i2c.c for it was not be used

- [bluetrum] add flash support
- [ra6m4-cpk] add gcc build support.

- stm32
  - Fix STM32 USB driver matching hal library version
  - stm32h743-openmv-h7plus bsp add sdram for openmv
  - Add tinyusb for stm32 driver
  - Add stm32g474-st-nucleo bsp
  - Add stm32u575-st-nucleo bsp
  - Add stm32l552ze-nucleo bsp
  - [gcc] Fix stack 0 bug, expand stack to 0x400 (same as Keil IAR)
  - Modify variable name p_tm to tm
  - drv_common.c add LOW_E for Error_Handler
  - Add i2c config for stm32l496-st-nucleo bsp
  - For STM32F4 series, CAN is configured according to different ABP1 bus frequencies
  - Improved STM32H7 series SPI driver using DMA
  - Add BSP ART-PI download algorithm
  - Add lvgl music demo for stm32f469-st-disco bsp.
  - Refresh using dma2d,screen refresh average 25fps for stm32f469-st-disco bsp
  - Add esp8266 configuration option takeover
  - add SOC_SERIES_STM32G0 to use "stm32_wdt.hiwdg.Init.Window = 0x00000FFF", otherwise the watchdog always reset.
  - Fix STM32L4 series flash will fail to erase the first time after downloading the program

  - stm32l475-atk-pandora
    - Add ADC PWM pin definition
    - Preliminary realization of Arduino ecological compatibility
    - Add lcd_fill_array()
    - Add lvgl demo
    - Add BSP_USING_LCD_SAMPLE in rttlogo.h
    - Enable SPI3-DMA2 for LCD
    - Beautify kconfig of board
    - Fix issue where board folder sconscript script did not continue scanning subfolders
    - Improve the structrue of sconscript
    - Add ESP8266 quick build option, serial port driver is changed from V2 to V1

- Fix compile warnings on qemu-vexpress-a9 platform (-Wimplicit-function-declaration)
- [qemu-a9] add lvgl support.
- [fix] The baud rate is configured according to the different APB1 frequencies. f4-series only.
- [qemu] update Kconfig
- Fix Raspi3 GPIO driver write bug
- [ls1cdev] add stack size to avoid stack overflow when boot
- [rp6m4-cpk] Add new drivers and improve BSP

## Tools

- CI
  - Optimize AutoTestCI trigger timing
  - Add scons tools test
  - Add the ci of nrf5x
  - Ci toolchain download using github link.

- Fix bug with missing brackets in eclipse.py
- Change ccflags to cflags，add LOCAL_CCFLAGS、LOCAL_CLFAGS、LOCAL_CXXFLAGS
- Fix generate .project file error
- Remove unused file 1.txt
- Update buildbot.py
- Fix adding empty lists and empty strings
- Add function of auto-update rtconfig.h

# RT-Thread v4.0.4 released

Change log since v4.0.3

## Kernel

- Update memheap auto binding policy
- Remove rt_thread_exit function
- Improve API annotations and code comments
- Standardize internal function naming
- Add recessive RT_USING_ASM_MEMCPY definition to Kconfig
- Add  RT_PRINTF_LONGLONG option to Kconfig, not selected by default
- Clear support for RT_PRINTF_LONGLONG in kservice.c
- Fix RT_PRINTF_LONGLONG is supported by default in 64-bit mode
- Solve the problem that FINSH cannot respond to serial port input in multi-core mode
- Optimize the comment for ipc
- Adjust the code to support cpu usage
- Adjust the exception handling code structure to support backtrace functionality
- Remove the mutex RT_IPC_FLAG_FIFO  function
- Remove switch_to_sethook function
- Add idle reclaimed resources
- Change defined(__CC_ARM) || defined(__CLANG_ARM) to  ifdef __ARMCC_VERSION
- Fix comment error for rt_mutex_detach().
- Remove the rt_sscanf statement
- Add RT_WEAK for rt_malloc_align,rt_free_align
- Changed the memory heap protection mechanism from FIFO to PRIO
- Remove fix priority inversion bug of mutex
- Add volatile to the rt_tick variable to prevent compiler optimization problems
- Keep the atomicity of idle task hook function calls
- Fix the crash problem after opening Oz optimization on ac6.
- Add protect to the rt_tick_increase critical section
- Add rt_mutex_trytake function
- Improve kernel stability
- Remove C99 dependencies
- Add conditional compilation for  _has_defunct_thread function
- Clarify the context
- Add get/set microsecond time control command
- Fix code comment error for function rt_memset().
- Remove rt_device_init_all() function
- Adjust graphics device driver definitions
- Unsigned comparisons should still be used when the signed comparison is undone
- Fix compile error when using LOG_HEX(...) function but RT_USING_ULOG not defined

## Components

- Support armclang
- Optimized system for suppoort gcc
- Update Libc
  - Create a gcc folder and merge the newlib and partical folders
  - Optimized system to support GCC
  - Fix support system function
  - Fix asctime_r return value
  - Lowers the action of calling printf before libc initialization to the warning level
  - Replace dfs_select.h with standard sys/select.h
  - The RT_LIBC_USING_TIME macro definition remains after RT_USING_LIBC is enabled
  - Optimized fcntil.h definition
  - Fix syscall was optimized to incorporate minilibc into syscalls.c file
  - Rebuild _libc_init_array to prevent chip startup failure under GCC
  - RT_USING_NEWLIB and math libraries are defined without libc enabled
  - Fix the conflict warning of read and write functions
  - Remove libc_signal.h and libc_fdset.h
  - Fix an issue where keil did not compile properly
  - Remove rtlibc, libc_stdio.h, libc_dirent.h, libc_ioctl.h，libc_signal.h，libc_fdset.h，libc_errno.h， libc_limits.h
  - Add delay when the scheduler is not running
  - Fix armClang support issues
  - usleep supports calling in interrupts.
  - Fix sys header file import when liBC is not enabled
  - The gettimeofday () function supports time zones and  specification set_timeval/get_timeval returns a value
  - Fix warning of posix_signal
  - Fix bug where nonegcc folder path was not added to project in Simulator Win32
  - Fix error caused by libc removing sys/errno.h file
  - Remove _TIMESPEC_DEFINED
  - Add the RT_LIBC_FIXED_TIMEZONE default value to time.c to prevent projects that do not have RT_LIBC_FIXED_TIMEZONE configured
  - Add the ability to manually set the time zone
  - Add riscv.c dlmodule can support riscv architecture
  - Implement pid_t gettid(void)
  - Implement  isatty()
  - Implement set_timeval
  - Change the libc directory to common and none-gcc
  - Remove dlib and armlibc `sys` folder
  - Fix MDK build error when using gmtime_r
  - Optimize get_timeval and  set_timeval  conditional compiled code structure
  - Update mktime support fixed timezone
  - Add microseconds time get feature in gettimeofday
  - LOG_W will cause a recursive printing if ulog timestamp function is turned on
  - Remove inherent mutex protect
- Update drivers
  - Fix stdint in cputime
  - Delete NTP configurations
  - Make rt_soft_rtc_init private
  - Bypass controlling commands in touch class to driver
  - Update the RTC device driver framework to unify and simplify RTC device registration and access
  - Add i2c bus control api
  - Update uac class, remove GPL code
  - Fix measurement unit of "percentage" to "permillage" for accuracy
  - Add spo2 sensor support in drivers/include/drivers/sensor.h and drivers/sensors/sensor.c
  - Optimize pin.h, sensor.h, rtdevice.h to avoid reverse inclusion
  - Update usb enlarge uconfig_descriptor's data array space
  - Add security devices
- [netif] Fix the eth_tx_msg protection
- Update utest
  - Add kernel testcases
  - Fix TC_FAIL_LIST_MARK_FAILED Subscript calculation error
- Fix comments error in ringbuffer and workqueue
- Update ringbuffer
  - Add an interface comment
  - Local variables are used to prevent resource competition
  - Write_index bug in rt_ringbuffer_put_force
- Update workqueue
  - Add an interface comment
  - Remove rt_delayed_work_init()
  - Privatize the rt_work_sys_workqueue_init function
  - Fix an unexpected suspension of critical condition threads
- Fixed timer ASSERT exception due to multithreaded scheduling
- Optimize the inclusion relationship between dfs.h and dirent.h
- Update finsh
  - Restore the FINSH_USING_MSH  definition for compatibility
  - Expose the finsh_getchar function
  - Fixed _cmd_xxx command unavailable due to finsh removal
  - Update Kconfig is more hierarchical
  - The finsh component can optionally include built-in commands
  - Repaie that the table key on msh do not work
  - The list-thread command adds the bind core display for multiple cores
  - Add support for tasking toolchain
  - Add mount/umount cmd
- Fix ringblk_buf  error when no longer using dynamic memory
- [timezone] implement timezone
- [DeviceDriver] Change the special device commands form 0x1X to 0x2X. It will avoid same of general device commands
- Update AT
  - Update old_urc_table to new_urc_table
  - Optimized at socket memory leak modification
  - Add at_utils_send virtual function
  - Fix at_vprintf and at_vprintfln and end_sign response
  - Fix at_server_getchar spelling error
- Add device type USBOTG to redef.h
- [newlib] fix compile error when closing RT_USING_CONSOLE
- Update rtc
  - Add RT_DEVICE_CTRL_RTC_GET_TIMEVAL and RT_DEVICE_CTRL_RTC_SET_TIMEVAL ops
  - Remove RT_DEVICE_CTRL_RTC_GET_TIME_US and RT_DEVICE_CTRL_RTC_SET_TIME_US. Add RT_DEVICE_CTRL_RTC_GET_TIMEVAL and RT_DEVICE_CTRL_RTC_SET_TIMEVAL. The RT_DEVICE_CTRL_RTC_GET_TIMEVAL cmd can get second time and microsecond time.
  - Change core.c/.h name to rtc.c /.h
  - Update rt_rtc_dev_register function name to  rt_hw_rtc_register
  - Change localtime name to localtime_r
- [ethernetif] replace rt_memcpy with SMEMCPY
- [sdio] remove rt_mmcsd_blk_init
- Update time
  - Fix an issue where POSIX related functions were not protected for critical sections
  - Adjust the judgment logic of posiX related functions to obtain time results
  - Rename nonstandard liBC functions and reposition the time.h definition
  - Revert the old code
- Fix the sem init check bug in pthread.
- Fix MMC initialization error, write card->csd as card->cid
- Update serial
  - Add CTS/RTS flowcontrol
  - Implement function of getting window's size(TIOCGWINSZ)
  - Optimized RT_USING_POSIX_TERMIOS precompilation
  - Serial_v2 support device ops feature
  - Fix the problem that serial Close did not clear the callback interface
  - Optimize send non-blocking problem when serial_close does not execute rt_completion_done
  - Optimize DMA receive processing flow and decouple the driver to call the API interface of the serial port framework
  - Added the Serial V2 framework and the Serial port driver based on STM32
  - Serial_v2 support device ops feature
  - Fix do RT_DEVICE_CTRL_CLOSE cmd when close serial device regardless of DMA config
- Update lwip
  - Fix lwIP critical section protection bug
  - Set default lwip stack for old bsp folder.
  - Change default lwip stack to lwip2.0.3
  - Fix delete useless code.
  - The "event_callback" will be change by RT-Thread dfs.
  - Adjust the string.h position
  - LWIP_TIMEVAL_PRIVATE: provided by <sys/time.h>
  - LWIP2.0.2 and 2.1.2 remove ERRNO
  - Remove ESHUTDOWN from LWIP
  - Remove the possible critical zone risk
  - Iperf speed test have been stable.
  - The overflow problem of lwip rx thread mailbox.
- [pm] Index should be less than PM_MODLUE_MAX_ID
- [cputime] Add sys/errno.h
- Update msh
  - Implement tail command
  - Fix shell msh_exec memory over-bound.
- Update dfs
  - Fix F_GETFL/F_SETFL should be handled by the drivers.
  - Change the default maximum number and type of the file system to 4
  - Add format_ignore file, exclude fatfs format check
  - Add comments for _device_fs
- Update ymodem
  - Modified the enabling conditions of YMODEM USING FILE TRANSFER
  - Check the file path's legitimacy of'sy' command
- Add new component: rt-link
- [net] Add the function of set [internet up] status, activate the callback.
- [components]  Remove uip
- Update ulog
  - Using gettimeofday for timestamp get
  - Fix thread info show when kernel not startup
  - Increase the usec check time
  - Add output locker enabled API
- Update FatFs
  - Update the mutex protection timeout can be set using Kconfig
  - Fix the time dependent function opening condition

## BSP and CPU porting

- Support armclang
- [stm32h750-artpi-h750] Complete  bsp
- [ls2k] Fix missing header file applications
- [AT32] Complete  BSP
- Add _CRT_DECLARE_NONSTDC_NAMES=0 macro definition in simulator bsp
- Refresh the project and remove rtlibc and duplicate definitions in simulator bsp
- Update libcpu
  - Modified the irq handle interface rt_hw_trap_IRq to support intercore IPI interrupt processing
  - Add interface dcache invalidate/dcache clean&invalidate
  - Adjust the stack_top to bss
  - Remove gtimer/pmu from cortex-a
  - Repair hard fault return bug
  - Add in Cortex-A to turn on the _rt_FFS implementation when RT_USING_CPU_FFS macro definition
  - Add interface to get Cortex-A Generic Timer frequency
  - Add GICV3 interrupt controller code, updated MenuConfig configuration options with utest config.h
  - Tidy up the cortex-a aarch32 boot code
  - Fix RTC driver compile error
  - add gic&gtimer interface
  - Optimized the condition for automatically enabling FPU when cortex-A does not define an exception
  - Fix inconsistent function behavior with different optimization levels
  - Correct cortex-m23 rvds.S including for armclang platform.
- Fix simulator:
  -  Fix sd_sim.c compilation error using rt_dgb instead of old debug output
  -  Refresh the project and remove rtlibc and duplicate definitions
  -  Add _CRT_DECLARE_NONSTDC_NAMES=0 macro definition
- Fix stm32f407-explorer
  - Optimize fal Settings
  - Update readme
  - Implement ESP8266 configuration in extended module driver menu
  - Optimized Kconfig file system naming, SFUD registration w25Q128 name adaptive, avoid users to set more than one step name
- Add more BSP on BSP framework:
  - VangoV85xx
  - hc32l136
  - ap32f103xe-miniboard
  - gd32407v-start
  - mm32f103x
  - ch32f103c8-core
  - n32g452xx
  - hc32l196
  - hc32f460petb
  - gd32f105c-eval
  - nrf52833
  - hc32f030c8t6-mini
  - fm33lc0xx
  - stm32l4r9-st-sensortile-box
  - stm32f302-st-nucleo
  - mm32f3270
  - stm32f407-robomaster-c
  - qemu-riscv-virt64
  - gd32350r-eval
  - stm32f407-armfly-v5
  - juicevm
  - stm32f207-st-nucleo
  - m2354
- [ch32f103c8-core] rename function name: ch32f1_hwtimer_clock_init, ch32f1_hwtimer_clock_get
- Fix thread-smart
  - Support T-HEAD Xuantie-E9xx Series CPU on Smart-EVB, eg. E906/F/D/P, E907/F/D/P
  - Formatting  code
  - Add QEMU support, and code optimization for thead extension
- [mm32f327x] Fix .ignore_format file path error
- [hc32f4a0] Fix syntax errors in scons scripts
- [x86] Enable romfs
- Replace gmtime with gmtime_r
- [swm320-lp100] Update  libraries
- [ft2004] Add gtimer support and fixed can driver initialization issues
- Fix bluetrum
  - Optimizing the uart driver
  - Fix RTC driver building errors
  - Add RT_USING_CONSOLE judgment
- [nrf52x] Optimize drv_wdt.c
- [mm32f327x] Add on-chip flash driver
- [imxrt1064-nxp-evk] Improved I2C, UART,LCD kconfig, fixed i2C imXrT_i2C_mST_xfer function that would write an address before reading data
- [w60x] Fix UART1 function unavailable
- [gd32450z-eval] Update firmware library and delete usb relate library codes
- [raspi4-32] Update raspi4-32 eth drv
- [bluetrum] Fix uart1 and uart2 cannot recv data
- Fix STM32
  - Implement rtc driver to RTC framework V2.0
  - Add spi config increases irq_type
  - Fix driver library USBH initialization errors
  - Add timeval ops for STM32 platform Sub-second timestamp.
- Remove BSP on BSP framework:
  - realview-a8
  - fh8620
  - gkipc
  - stm32f20x
  - efm32
  - zynq7000
  - stm32f1.0-mini-sysytem
- Fix unused device frame error
- Update GPL license to Apache-2.0, and format files
- Fix incorrect setting of word length when parity check is enabled on the STM32 serial port

## Tools

- Support windows cmake tool
- Optimization the EXTERN_LIB variable use
- Update eclipse project after dist
- Add default project name and project path while --dist-ide
- Fix the problem of an error when opening menuconfig after the project is dist
- Update cmake.py, add c++ support and libpath.
- Python 3 compatibility support
- Update eclipse.py to compatible tasking

# RT-Thread v4.0.3 Change Log

Change log since v4.0.2

## Kernel

* Add `__RTTHREAD__` global macro definition
* Add user heap options
* Fix bug of rt_memheap_detach
* Add rt_memory_info() for memheap.c
* Add rt_object_get_length/rt_object_get_pointers APIs
* Fix double release for thread
* Fix thread control bug about `RT_THREAD_CTRL_CLOSE` command
* Avoid deadlock (rt_hw_interrupt_disable and rt_enter_critical when enable smp)
* Fix the issue of judging the ready_table of pcpu when multi-core rt_schedule_remove_thread
* Fix the issue that the yield operation cannot release the cpu in time
* Fix the iterator failure for softtimer list timeout check
* Fix rt_timer_list_next_timeout multi-task safe
* Add timer working status query function to software timer
* Fix the software issue when the system timer thread is pending
* Fix the timer/software timer handling issue if the timeout function starts/stops/deletes this timer.
* Fix an issue with rt_timer_start being broken and destroying the timer list
* Fix the bug that the linked list is still mounted when the single timer is not modified
* Add function rt_tick_get_millisecond()
* Fix the delay_until issue
* Add mb mq value overflow-check code
* Fix the rt_event_recv function, if the event met without blocking, assigning thread->event_set/event_info will goes well
* Add the definition of the maximum value of ipc type
* Remove the call of rt_system_object_init/rt_system_tick_init from the code.
* Removes component configuration macro `RT_USING_FINSH` from the kernel
* Use object_find to implement thread_find/device_find
* The cleanup operation is executed before the current thread exits

## Components

* Fix assert in the sys_arch_mbox_fetch function when close socket
* Add dhcp start or stop function to start or stop dhcp.
* Change rt_data_queue_peak to rt_data_queue_peek.
* Update elmfat to R0.14 patch 1.
* Add SAL_INTERNET_CHECK configuration item to support turning on or off the network status check
* Solve the issue that the do_pollfd function processing the underlying network device returns error -1
* Fix the issue that when the network card device calls to close dhcp, the bottom layer no need to call the dhcp_stop function to close dhcp
* Add the function of judging the network card up and down in the sal_accept function
* Modify the spelling error of the macro definition, modify the printing error when printing the IMEI number
* Fix the issue that the server closed the connection when web socket requests the data that comes back from the server, and the socket status is incorrectly judged at that point
* Fix the issue of incorrect sal_getaddrinfo release when sal socket supports multiple network cards
* Update AT socket
  * Support alloc socket dynamically with at device
  * Update AT_SW_VERSION and adjust at_socket_ops
  * Adjust where the AT socket callback function
  * Fix at_client, avoid creating the same client repeatedly and prevent working exceptions and memory leaks.
  * Fix the bug that rx_notice out of sync when the data is received after last rt_device_read() is zero
* [FinSH] rm command supports recursive deletion of folders
* Add clear command for FINSH
* [posix] Implement usleep function
* Fix the issue of pthreads compilation error when using the new version of newlib; at the same time solve the problem of pthreads under 64-bit;
* [dlmodule] Fix crash when dlmodule exits
* Add priority & stack_size param parsing for dlmodule
* libc adds getline/getdelim functions
* Change the header file included in some libc files from <rtthread.h> to <rtconfig.h> to narrow the scope of inclusion to prevent recursive compilation
* [jffs2] error check of rt_event_recv()
* Add rt_data_queue_deinit and fix bug of dataqueue
* Change log in device driver framework
  * [pin] Add rt_pin_get to pin frame
  * [PM] Update RT-Thread PM2.0 framework
  * [audio] Fix compile warning, undefine var
  * [serial] Fix the crash caused when the serial port receiving buffer is full and ULOG_USING_ISR_LOG is not turned on
  * [wlan] Add raw frame send interface and Management frame filter interface
  * [Sensor] Add vendor info and sensor types for cmd
  * [Sensor] Support custom commands for rt_sensor_control
  * [sensor] Support TOF sensor class
  * [SFUD] Update the 'sf bench' command.
  * [spi] Fix "response+1" causing hard fault of unaligned access to SPI memory of STM32 HAL library
  * [RTC] Optimize RTC alarm function, add alarm function for SOFT_RTC
  * [hwtimer] When getting the timer count, prevent overflow update due to the interruption
  * [dirver/i2c] i2c driver supports bus lock, STOP control
  * [usb] Fix bug in device descriptor that MAC OS enumeration failed
  * Fix the bug that USB cannot recognize composite device normally
  * Fix USB host core bugs
    * Limit >4 USB ports hubs
    * Double free intf
    * dname buffer size is too small
    * Reset child pointer after detaching instance

## BSP and CPU porting

* Add license info and code cleanup for vexpress-a9 BSP
* Add HDSC hc32f4a0 BSP support
* Add support for Cypress PSoC6 series products
* Fix the lpc55 issue under Linux/GCC
* [qemu] Fix spelling mistakes of code in drv_pl041.c
* [loongson] Update the SPI driver and UART driver on the Loongson 2K1000 platform
* [allwinner_tina]Fix spi driver bug
* [smartfusion2]Support Microsemi SmartFusion2 family FPGA
* [imxrt] Add ethernet configuration for imxrt1064-nxp-evk
* Add support for architecture sparc-v8 and soc bm3803.
* [libc] libc adds getline/getdelim functions (posix.1-2008)
* Add support for c28x mcu hardware fpu
* [at32] Add link detecting thread for ethernet driver
* Fix gcc assembly option in rtconfig.py for imxrt1064-nxp-evk
* [IMXRT]Fix scons --dist in IMXRT BSP
* [ls2kdev] Initial gpio driver without irq support on ls2kdev
* Optimize BSP dist handle process
* [nrfx] Add the qspi_flash of nordic pdk
* [nrf5x] Add the BSP of nrf5x, which support UART, SPI, PWM, ADC, i2c drivers and rtc device driver
* [nrfx] Add the on-chip flash for nrf5x
* [RISC-V:K210]Add UART1~3 support for K210
* [Nuclei] Add Nuclei RISC-V Processor support
* Update BSP for mini2440
* Add soc timer cntpct
* LPC55S69: Add NS project and TFM support on LPC55S69
* Make MicroPython runs on Raspi3-64 BSP
* Add rt_hw_us_delay for W60x
* [imxrt] [driver] Add usb device driver
* Fix raspi4-32
  * Add: dma driver,  bsc driver, dsi lcd/touch driver, waveshare spi lcd/touch driver, watchdog driver, hdmi driver, sdio driver, gpio interrupt
  * Fix: eth driver, spi driver, uart driver
* Add more BSP on BSP framework:
  * At32/at32f403a-start
  * At32/at32f407-start
  * bluetrum/ab32vg1-ab-prougen
  * bm3803
  * cypress/psoc6-pioneerkit_modus
  * essemi/es32f0271
  * essemi/es32f369x
  * essemi/es32f0654
  * lpc55sxx/lpc55s69_nxp_evk_ns
  * ls2kdev
  * nrf5x
  * nuclei/gd32vf103_rvstar
  * nuclei/hbird_eval
  * nuvoton/nk-980iot
  * nuvoton/numaker-iot-m487
  * nuvoton/numaker-pfm-m487
  * raspi2
  * raspi3-32
  * raspi3-64
  * raspi4-32
  * raspi4-64
  * smartfusion2
  * thead-smart
  * tm4c123 BSP
  * zynqmp-r5-axu4ev

* Add more STM32 BSP based on new STM32 BSP framework:
  * STM32L431-BearPi
  * stm32f103-blue-pill
  * stm32f103-onenet-nbiot
  * stm32f410-st-nucleo
  * stm32f411-atk-nano
  * stm32f413-st-nucleo
  * stm32g070-st-nucleo
  * stm32h747-st-discovery
  * stm32l010-st-nucleo
  * stm32l412-st-nucleo
  * stm32l433-st-nucleo
  * stm32l496-st-nucleo
  * stm32mp157a-st-discovery
  * stm32mp157a-st-ev1
  * stm32wb55-st-nucleo
* New STM32 BSP framework:
  * Add dcmi, ov2640 and SD Card driver for stm32h743
  * Fix bug that caused system crash by changing the run_mode in low power mode
  * Fix issue when using gcc to compile the chips of stm G4 series, but chip doesn't work
  * drv_flash_f7.c supports single bank mode
  * Add stm32f103-atk-warshipv3 sram driver
  * Update void HAL_Delay(__IO uint32_t Delay)
  * Add PWM9_CONFIG default configuration and TIM3_CONFIG default configuration
  * [stm32f103-atk-warshipv3] Add sdcard driver
  * Add English readme for stm32
  * Add dac and can driver for stm32l4 and stm32f4
  * openamp driver and add rs485 driver for stm32mp157a
  * Optimize the pin-index algorithm
  * [stm32f769-disco] Support ethernet device
  * Add C++ Support
  * Fix the clock configuration issue of STM32 hardware timer
  * Adjust the interrupt priority configuration of some peripherals of the STM32 series BSP
  * Fix stm32 f1 series rtc bug
  * Support SPI/ADC/TIME on-chip peripheral driver
  * [stm32h743-atk-apollo]Support stm32h7 uart dma
  * Add stm32h743-atk-apollo support for pcf8574 and uart2
  * Support stm32h743-atk-apollo pcf8574 and uart2(485)
  * Update bsp/stm32/stm32h743-st-nucleo
  * Fix ADC channel Configuration bug for SMT32F0/L0/H7
  * Add support for onboard AP6181
  * Fix UART DMA TX
  * Add pm support by cubemx tool for stm32l4
  * Add stm32f407-atk-explorer sram driver
  * Fix PWM timer init about pwm
  * [stm32f103-atk-warshipv3]Add sdcard driver
  * Add stm32f103-atk-warshipv3 sram driver

## Tools

* Add C++ support for eclipse target
* Keep user's lib configuration while running --target=eclipse
* Add Libraries when perform `scons --dist`
* Update tools/building.py and add `tackanalysis` option
* Improve the logic of generating `rtconfig.h` files in scons with command `scons --menuconfig`
* Fix makeimg.py wrong on linux
* Add Studio IDE dist feature for stm32 BSP

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
