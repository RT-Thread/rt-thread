# Phytium Standalone SDK 2023-7-18 ChangeLog

Change Log since 2023-07-11

## drivers

- add iopad driver
# Phytium Standalone SDK 2023-7-14 ChangeLog

Change Log since 2023-07-11

## tools

- modify scripts to adapt freertos

# Phytium Standalone SDK 2023-7-11 ChangeLog

Change Log since 2023-07-11

## board

- modify fearly uart

# Phytium Standalone SDK 2023-7-06 ChangeLog

Change Log since 2023-07-03

## tools

- Resolved an issue where the header file could not be recognized after modification

* Fixed a bug where C++ logic could not generate binary

# Phytium Standalone SDK 2023-7-03 ChangeLog

Change Log since 2023-06-30

## arch

- added new features such as smcc and psci
- Remove the old smcc and psci methods

## exampe

- add psci example

# Phytium Standalone SDK 2023-6-30 ChangeLog

Change Log since 2023-06-28

## driver

- change the struct of FDcDisplayTimmingConfig

# Phytium Standalone SDK 2023-6-28 ChangeLog

Change Log since 2023-06-26

## example

- Add serial new examples

## driver

- Add new state clear function in fpl011_intr.c

# Phytium Standalone SDK 2023-6-26 ChangeLog

Change Log since 2023-06-21

## arch

- Add fpen choice in fboot.S to compatible with rtos startup

## driver

- Modify the method of reading and writing gic 64-bit registers in aarch32 mode

# Phytium Standalone SDK 2023-6-20 ChangeLog

Change Log since 2023-06-12

## board

- Added mio slave id

## example

- Added mio ddma example

# Phytium Standalone SDK 2023-06-19 ChangeLog

Change Log since 2023-06-19

## third-party

- add callback function eth_poll in LwipPortInputThread: to enable the NIC to send and receive packets steadily in FreeRTOS.

# Phytium Standalone SDK 2023-06-19 ChangeLog

Change Log since 2023-06-08

## arch

- restruct aarch32 system register access interface
- delete fcp15 file

## driver

- add windbond qspi flash support

# Phytium Standalone SDK 2023-6-16 ChangeLog

Change Log since 2023-06-15

## tools

Added some memory check tools

## doc

Added user document

## example

Added libmetal example

# Phytium Standalone SDK 2023-6-15 ChangeLog

Change Log since 2023-6-12

## driver

- Modify the framebuffer generate method and the driver lib

## driver

- adjust the lvgl and the driver relation

## example

- adapt the driver change

# Phytium Standalone SDK 2023-6-15 ChangeLog

Change Log since 2023-6-12

## sdmmc

- Modify the variable name in sdmmc.mk to resolve the issue of variable name overloading.

# Phytium Standalone SDK 2023-6-12 ChangeLog

Change Log since 2023-6-12

## example

- modify uart ddma example
- remove FDDMA_MAX_TRANSFER_LEN

## drivers

- remove FDDMA_MAX_TRANSFER_LEN

# Phytium Standalone SDK 2023-6-12 ChangeLog

Change Log since 2023-6-8

## drivers

- modify annotation and variable name in gdma driver.
- solve customer issue in gdma.

## example

- modify gdma example.

# Phytium Standalone SDK 2023-6-8 ChangeLog

Change Log since 2023-6-8

## example

- modify gic example Kconfig.
- gic example debug.

# Phytium Standalone SDK 2023-6-8 ChangeLog

Change Log since 2023-6-6

## arch

- add gcc atomic api

## example

- add atomic test example.

# Phytium Standalone SDK 2023-6-8 ChangeLog

Change Log since 2023-06-7

## example

- add cxx example
- add crypto++ example

## arch

- support c++

## lib

- add some stub functions for std c++ library

## third-party

- add crypto++

# Phytium Standalone SDK 2023-6-7 ChangeLog

Change Log since 2023-6-6

## example

- network/raw_api/tcp_client example debug: Memory double free problem solved.
- network/raw_api/tcp_client example modified: The new code is more robust and secure.

# Phytium Standalone SDK 2023-6-7 ChangeLog

Change Log since 2023-6-2

## example

- add wdt example.

# Phytium Standalone SDK 2023-6-6 ChangeLog

Change Log since 2023-6-6

## arch

- modify generic timer api

# Phytium Standalone SDK 2023-6-05 ChangeLog

Change Log since 2023-05-31

## example

- add timer example.

# Phytium Standalone SDK 2023-6-05 ChangeLog

Change Log since 2023-05-31

## baremetal

- modified license of libmetal demo
- add loadelf function for openamp example

## third-party

- add image store file
- complete remote processor operation ports

# Phytium Standalone SDK 2023-6-2 ChangeLog

Change Log since 2023-6-1

## scrips

- update settings.json (fileheader extentions update)

# Phytium Standalone SDK 2023-5-31 ChangeLog

Change Log since 2023-05-29

## tools

Added a new compilation framework

## baremetal

Added a new test code

## SDK

Add a series of makefile scripts

# Phytium Standalone SDK 2023-5-29 ChangeLog

Change Log since 2023-05-25

## example

- add ipc semaphore refactoring example.

# Phytium Standalone SDK 2023-5-29 ChangeLog

Change Log since 2023-05-23

## arch

- modify generic timer api, add virtual timer's use
- delete USE_SYS_TICK kconfig

## example

- add generic_timer example to test physical and virtual timers

# Phytium Standalone SDK 2023-05-24 v1.1.1 ChangeLog

Change Log since 2023-05-23

## README

- add developer infomation.
- install.py update including version infomation modified.

## common

- according to user issue, add a ; in fdebug.h

# Phytium Standalone SDK 2023-5-23 ChangeLog

Change Log since 2023-05-16

## example

- add LwipEthProcessLoop call in LwipTestLoop.
- add new macro definition: CONFIG_LWIP_RX_POLL to control LwipEthProcessLoop calls.

## drivers

- add new member variable: mask in struct Fxmac,which can be used to manage TX and RX interrupts.
- add new macro definition: FXMAC_INTR_MASK,which can be used to enable TX and RX interrupts.

## third-party

- delete LWIP_DEBUG_ESP_LOG in /lwip-2.1.2/Kconfig
- add new function LwipEthProcessLoop.
- add new callback function ethernetif_poll,which can poll network packets.
- add new macro definitions: FXMAC_LWIP_PORT_CONFIG_RX_POLL_RECV,which controls whether Frame received interrupts are enabled or not.

# Phytium Standalone SDK 2023-5-16 ChangeLog

Change Log since 2023-05-12

## example

- add new openamp demo,support manager core and remote core communicate always.
- Change openamp for linux demo folder name “openamp old”.

## third-party

- modified some const variable
- add some defines of service

# Phytium Standalone SDK 2023-5-12 ChangeLog

Change Log since 2023-05-10

## example

- add pcie refactoring example.

## driver

-little change to pcie driver

# Phytium Standalone SDK 2023-5-10 ChangeLog

Change Log since 2023-05-09

## board

- Modify the description in the MMUs table in the aarch64.

## aarch64

* Modify the execution mode in fmmu.c

# Phytium Standalone SDK 2023-5-09 ChangeLog

Change Log since 2023-04-28

## board

- Change the suffix of CACHE_LINE_ADDR_MASK, resolve the problem that cache flush addresses are truncated .

# Phytium Standalone SDK 2023-4-28 ChangeLog

Change Log since 2023-04-24

## example

- add gic refactoring example.

# Phytium Standalone SDK 2023-04-24 v1.1.0 ChangeLog

Change Log since 2023-04-20

## README

- add developer infomation.
- install.py update including version infomation modified.

## example

- add new refactoring examples.

# Phytium Standalone SDK 2023-4-21 ChangeLog

Change Log since 2023-04-12

## example

- add serial refactoring example.

# Phytium Standalone SDK 2023-4-20 ChangeLog

Change Log since 2023-04-15

## example

- add new spim test refactoring example.

# Phytium Standalone SDK 2023-4-18 ChangeLog

Change Log since 2023-04-13

## common

- finterrupt: modify priority icc_pmr set and icc_rpr get, according to different configurations.

# Phytium Standalone SDK 2023-4-18 ChangeLog

Change Log since 2023-04-10

## example

- add new sata test refactoring example.

# Phytium Standalone SDK 2023-4-11 ChangeLog

Change Log since 2023-04-11

## driver

- resolve the driver clock configuration in xmac cannot perform network auto-negotiation bug.

# Phytium Standalone SDK 2023-4-11 ChangeLog

Change Log since 2023-03-30

## example

- update lwip_start_up README.md : add new description about jumbo mode enable and related operating instructions.

## driver

- modify macro definitions about jumbo registers and delete useless code.

## third-party

- add new instructions which can change netif mtu manually according to the actual transmission.
- modify pbuf alloc type and delete redundant code.

# Phytium Standalone SDK 2023-3-30 ChangeLog

Change Log since 2023-03-29

## example

- lwip instructions has been updated by which we can choose driver type manually.
- update README.md : add new description about lwip probe instructions.

# Phytium Standalone SDK 2023-3-29 ChangeLog

Change Log since 2023-03-27

## example

- add new gdma test refactoring example: gdma_direct_transfer_example, gdma_bdl_transfer_example, gdma_performance_test_example.
- little change in old gdma example.

## driver

- add wait mode feature in gdma driver.

# Phytium Standalone SDK 2023-3-27 ChangeLog

Change Log since 2023-03-24

## example

- remove lib_core0 lib_core1 folder,add apu_running and rpu_running,support more example.
- modified README.md and update picture.
- fix atomic operation bug.

## doc

- add libmetal.md to introduce how to use it

## third-party

- remove extra code

# Phytium Standalone SDK 2023-3-24 ChangeLog

Change Log since 2023-03-20

## third-party

- add apps lwiperf by which we can test mac bandwidth
- modify kconfig to add a new feature : LWIP_WND_SCALE,which can boost window maximum

# Phytium Standalone SDK 2023-3-23 ChangeLog

Change Log since 2023-03-20

## example

- modify the lvgl example
- change the cmd, and interface , add the test fig and modify the readme

## driver

- modify the format
- add a dump function
- change some function and interface
- generate a new lib driver of dcdp

## third-party

- delete the unused part of port
- modify the format

# Phytium Standalone SDK 2023-3-20 ChangeLog

Change Log since 2023-03-17

## aarch

- Adapt exception frame sequence

## example

- Add some exception test example

# Phytium Standalone SDK 2023-3-17 ChangeLog

Change Log since 2023-03-17

- add pwm example

# Phytium Standalone SDK 2023-3-13 ChangeLog

Change Log since 2023-03-3

## third-party

- delete redundant code about NO_SYS macro definition
- modify kconfig ：delete config_LWIP_PORT_DEBUG_EN and add config_LWIP_USE_MEM__HEAP_DEBUG, which can manage parameters in memory debug mode
- modify LwipPortStop function : add dhcp_cleanup api and free emac after sys_thread_delete

# Phytium Standalone SDK 2023-3-3 ChangeLog

Change Log since 2023-03-3

# third-party

- delete redundant code about NO_SYS macro definition
- modify kconfig ：delete config_LWIP_PORT_DEBUG_EN and add config_LWIP_USE_MEM__HEAP_DEBUG, which can manage parameters in memory debug mode
- modify LwipPortStop function : add dhcp_cleanup api and free emac after sys_thread_delete

# Phytium Standalone SDK 2023-3-3 ChangeLog

Change Log since 2023-03-1

- add qspi example

# Phytium Standalone SDK 2023-3-2 ChangeLog

Change Log since 2023-03-01

- modify for drvier and arch de-couple

## aarch && common

- move felf, finterrupt and fsleep from common to arch, which are arch related
- move fkernel, fswap from arch to common, which are not arch related
- fix issue that f_printk have different reture type in implmentation and declaration, which is considered a warning for compiler

## make

- add drviver.mk, board.mk, arch.mk and lib.mk, to seprate src and inc to groups
- remove un-used packsource.mk
- support compiling with makefile depends
- support compiling drviver only without arch support

## drivers

- remove un-used reference to finterrupt.h
- add port folder to implment stub function of arch

## tools

- add tool export-sdk, demo the usage in export rt-thread bsp
- remove un-used export_rtt_bsp.py

# Phytium Standalone SDK 2023-3-2 ChangeLog

Change Log since 2023-03-01

## baremetal

- add multi-display test example

## driver

- add multi-display driver and change the config

## third-party

- change the lvgl/port config and adapt to the multi-display config

# Phytium Standalone SDK 2023-03-01 ChangeLog

Change Log since 2023-03-01

## example

- add can example,  modify adc example

## driver

- modify can driver

# Phytium Standalone SDK 2023-3-1 ChangeLog

Change Log since 2023-02-20

## aarch

- Modify AARCH32 and AARCH32 interrupt handler function

## driver

- fix bug of can id handler

## example

- add system/nested_interrupt test example
- adapt gic sgi test example

# Phytium Standalone SDK 2023-02-27 ChangeLog

Change Log since 2023-02-22

## example

- Adapt the OpenAMP routine to e2000q/d and fix some errors

## third party

* Fixed a flag bit error in non-IPi mode

# Phytium Standalone SDK 2023-02-24 ChangeLog

Change Log since 2023-02-22

## aarch

- move BOOT_WITH_FLUSH_CACHE code into CONFIG_USE_AARCH64_L1_TO_AARCH32

## make

- add E2000/D2000 board config loader/saver

## tools

- rename 'make boot' as 'make deploy' and move to console.mk
- add config of pre-upload image name and folder

## example

- reduce dupliace 'make boot' and unused makefile target

# Phytium Standalone SDK 2023-02-22 ChangeLog

Change Log since 2023-02-21

## aarch

- add config BOOT_WITH_FLUSH_CACHE and support flush dcache before boot image

# Phytium Standalone SDK 2023-02-21 ChangeLog

Change Log since 2023-02-21

## example

- modified uart fifo test display

# Phytium Standalone SDK 2023-02-21 ChangeLog

Change Log since 2023-02-16

## third party

- modify sfud

# Phytium Standalone SDK 2023-02-16 ChangeLog

Change Log since 2023-02-15

## example

- add uart FIFO test example
- refresh picture of uart test example

## driver

- fix bug of uart tx_send

# Phytium Standalone SDK 2023-02-15 ChangeLog

Change Log since 2023-02-13

## example

- add sfud_test example

## third party

- modify sfud

# Phytium Standalone SDK 2023-02-09 ChangeLog

Change Log since 2023-02-07

## board

- add E2000 MHU module define

## example

- add scmi example project

## driver

- add scmi base protocol support
- add mhu of E2000 support
- add scmi sensor protocol support
- add scmi performance protocol support
- add scmi communication to SCP

## doc

- add fscmi_mhu.md file that introduce how to use scmi_mhu drivers

# Phytium Standalone SDK 2023-02-07 ChangeLog

## example

- remove build_all in example
- set CONFIG_OUTPUT_BINARY as defaut ON
- modify USR_SRC_DIR in raw_api example to absolute path

## make

- remove build_all.mk
- add default_load.mk
- modify compiling output style
- add make flash_serial to support ymodem image flash

## script

- add script to support ymodem flash and serial access

# Phytium Standalone SDK 2023-01-30 ChangeLog

Change Log since 2023-01-10

## example

- Adapt to tardigrade

## driver

- Adapt to tardigrade

# Phytium Standalone SDK 2023-01-18 v1.0.0 ChangeLog

Change Log since 2023-01-12

## README

- add developer infomation
- install.py update including version infomation modified

## example

- all example xxxx_eg_configs update
- all example sdkconfig sdkconfig.h update
- get-start/hello_world readme update
- peripheral/dma/fgdma_async_memcpy/README.md update
- peripheral/gic/fgic_test/README.md update
- peripheral/ipc/fsemaphore_test/README.md update
- storage/spi_sfud/README.md update
- peripheral/media/lvgl_test/README.md update
- peripheral/media/media_test/README.md update
- system/exception_debug/main.c add stdio.h,delete fprintk.h
- peripheral/qspi/qspi_nor_flash add flash type info
- peripheral/qspi/qspi_nor_flash cmd qspi auto related codes modified

# Phytium Standalone SDK 2023-01-16 ChangeLog

Change Log since 2023-01-11

## example

- e2000q adds nand test configuration

# Phytium Standalone SDK 2023-01-11 ChangeLog

Change Log since 2023-01-11

## example

- add header for some .c .h files in example folder of media.

## driver

- add header for some .c .h files in driver folder of media

## third-party

- change folder of lvgl name to lvgl-8.3
- add header for some .c .h files in driver folder of third-party/lvgl-8.3/port

# Phytium Standalone SDK 2023-01-11 ChangeLog

Change Log since 2023-01-09

## example

- add header for some .c .h files in example folder.

## driver

- add header for some .c .h files in driver folder.

# Phytium Standalone SDK 2023-01-09 ChangeLog

Change Log since 2022-12-30

## drivers

- eth/nand/mmc module to add comments

## third-party

- libmetal/backtrace/openamp module to add comments

## example

- nand/amp module to add comments

## common

- finterrupt module to add comments

# Phytium Standalone SDK 2023-01-09 ChangeLog

Change Log since 2023-01-09

## example

- network/lwip_startup add func sys_now
- The data type of timer_base_cnt is unified from u64 to u32.
- LwipTestLoop func modified. add  LinkDetectLoop(netif).

# Phytium Standalone SDK 2023-01-04 ChangeLog

Change Log since 2023-01-03

## example

- add header for all .c .h files in example/network

## common

- add header for files (fsleep fprintf fpritk) .c  .h in common/

## third-party

- modify lwip-2.1.2/ports/kconfig
- modify lwip-2.1.2/kconfig
- add header for all .c .h files in lwip-2.1.2/ports

# Phytium Standalone SDK 2022-12-30 ChangeLog

Change Log since 2022-12-27

## drivers

- update format for eth, usb, pcie, sdmmc

# Phytium Standalone SDK 2022-12-30 ChangeLog

Change Log since 2022-12-23

## drivers

- modify format issues in gic/i2c/ipc/pin/sata/timer/watchdog

## third-party

- add sata fatfs_0.1.4 port
- delete fatfs_0.1.3 content
- delete storage/sata_fatfs content

# Phytium Standalone SDK 2022-12-30 ChangeLog

Change Log since 2022-12-22

## example

- modify peripheral/  adc nand serial

## drivers

- modify adc nand serial

## common

- Modify the header file name to be consistent with the header macro definition
- Print interface range adjustment

# Phytium Standalone SDK 2022-12-27 ChangeLog

Change Log since 2022-12-21

## example

- update print info for gic example

## drivers

- update format for can/gic/rtc
- add file declare for pin/spi/usb

## third-party

- update fatfs/littlefs/lwip/sdmmc file declare

# Phytium Standalone SDK 2022-12-21 ChangeLog

Change Log since 2022-12-20

## drivers

- modify format issues in spi
- modify format issues in pwm

## third-party

- modify format issues in sfud
- modify format issues in littlefs

# Phytium Standalone SDK 2022-12-20 ChangeLog

Change Log since 2022-12-14

## driver

- modify format issues in dma

## example

- Modify format issues in dma example

# Phytium Standalone SDK 2022-12-14 ChangeLog

Change Log since 2022-12-08

## aarch64

- modify FilePath name
- adjust macro definit and c++ support

## arch/common

- modify FilePath name
- adjust  macro definit and c++ support

## example

- adjust "printf" and remove "FT_DEBUG_PRINT_*"
- modify baremetal/example/storage/qspi_sfud/inc/qspi_sfud_example.h macro definit

## common

- modify FilePath name
- adjust macro definit and c++ support
- adjust Print interface that will be use f_printk

## README.md

- modify chip description

# Phytium Standalone SDK 2022-12-14 ChangeLog

Change Log since 2022-12-08

## third-party

- freemodbus-v16/port/port.h ,modify the #include "fcp15.h" ,only used in _aarch32_
- freemodbus-v16/port/porttimer.c,change the TIMER_CLK_FREQ_HZ as FTIMER_CLK_FREQ_HZ
- freemodbus-v16/port/porttimer.c,change the TIMER_TACHO_IRQ_ID as FTIMER_TACHO_IRQ_NUM

# Phytium Standalone SDK 2022-12-08 ChangeLog

Change Log since 2022-12-05

## example

- add LSuserShellNoWaitLoop api.This api can enables the NIC to receive data without blocking.
- modify file format  all file adopt lf format.
- add network/lwip_startup
- add network/raw_api/tcp_client
- add network/raw_api/tcp_server
- add network/raw_api/udp_client
- add network/raw_api/udp_server
- delete lwip_tftpclient
- delete lwip_echo

## third-party

- add lwip_port.c && lwip_port.h
- Restructuring the directory lwip-2.1.2/ports

# Phytium Standalone SDK 2022-12-06 ChangeLog

Change Log since 2022-12-06

## drivers

- Add media drivers ,including the dc & dp

## example

- Add media test to light the screen
- Add LVGL demo to test the benchmark

## third-party

- Add LVGL library

## README

- Add media config

# Phytium Standalone SDK 2022-12-06 ChangeLog

Change Log since 2022-12-02

## example

- merge fatfs tests (usb/sdmmc/sdio)
- merge sdmmc tests (fsdmmc/fsdio)

## driver

- fix fsdio multi-block issue
- add data barrier to avoid optim issue (fsdio/fsdmmc)

## third-party

- add fatfs 0.1.4 and related configs
- port multi storage type with glue, therefore multi storage can be used at one binary image

# Phytium Standalone SDK 2022-12-02 ChangeLog

Change Log since 2022-12-01

## example

- add freemodbus test example
- add readme file and E2000Q and E2000D configs

## third-party

- add freemodbus V1.6
- modified protocol port file of serial
- add Kconfig to select peripheral and chip
- modified third-party.mk to add complie freemodbus files

# Phytium Standalone SDK 2022-12-1 ChangeLog

Change Log sinc 2022-11-28

## board

- Unified parameter format in fparameters.h
- Move fearly_uart module  to common folder

# Phytium Standalone SDK 2022-11-04 v0.4.0 ChangeLog

Change Log since 2022-11-01

## README

- add gitee branch description

## example

- add E2000D/Q default config
- add test picture
- modified example description
- adjust example cmd
- update get-start\hello_world readme
- add  get-start\hello_world fig indicating test result
- update qspi/rtc/wdt_test/sdmmc_cmd/qspi_sfud config for d2000 board
- update letter_shell readme
- update adc/pcie/qspi example for E2000 Demo board
- update lwip_echo/exception_debug/letter_shell_test/memory_pool_test/newlibc_test readme
- update exception_debug/letter_shell_test/memory_pool_test/newlibc_test examples for E2000 Q Demo board

# Phytium Standalone SDK 2022-11-01 ChangeLog

Change Log since 2022-10-26

## drivers

- fix bug in get pin pull mode
- fix bug in gpio 4/5, irq num mistype

## example

- update spi/sdio/gpio/usb example for E2000 Q Demo board

# Phytium Standalone SDK 2022-10-26 ChangeLog

Change Log sinc 2022-10-21

## aarch

- rename system file with f prefix

## board

- rename system file with f prefix

## common

- rename system file with f prefix

## board

- adopt to new system header file

## tools

- add script to export rt-trhead BSP from SDK
- adjust Kconfig blank line to support scons

# Phytium Standalone SDK 2022-10-21 ChangeLog

Change Log sinc 2022-10-15

## drivers

- Optimize sata
- Optimize can

## third-party

- Adapt fatfs to e2000 demo board for sata

## Phytium Standalone SDK 2022-10-10 ChangeLog

Change Log since 2022-9-26

## drivers

- support fxhci in E2000
- remove support of fxhci with PCIe in FT2000/4

## example

- add hid support for fxhci_host, demo keyboard input

## third-party

- remove usb disk port in fatfs

## Phytium Standalone SDK 2022-9-26 ChangeLog

Change Log since 2022-9-23

## drivers

- Move some function from fpl011.c to fpl011_options.c
- Add RTS CTS DDMA option define

## example

- add flow control and ddma example

# Phytium Standalone SDK 2022-9-23 ChangeLog

Change Log since 2022-9-15

## drivers

- Optimize can drivers interface adapter freertos

## example

- Modify can test example, add auto loopback test

# Phytium Standalone SDK 2022-9-7 ChangeLog

Change Log since 2022-08-30

## drivers

- Add qspi boya flash quad read function
- Optimize qspi drivers interface adapter freertos
- Optimize sata drivers interface adapter freertos

## example

- Modify qspi, sfud, spiffs test example, add auto test
- Modify sata test example, add auto test

Change Log since 2022-08-29

## drivers

- repair timer_tacho error

## example

- Modify i2c test example, add auto test
- Modify timer_tacho test example, add auto test
- remove E2000 i2c_master_slave example
- move E2000 RTC example to i2c

# Phytium Standalone SDK 2022-8-29 ChangeLog

Change Log since 2022-08-24

## drivers

- Add adc drivers interface adapter freertos

## example

- Modify adc test example, add auto test

# Phytium Standalone SDK 2022-8-18 ChangeLog

Change Log since 2022-08-16

## drivers

- Add pwm drivers interface adapter freertos

## example

- Modify pwm test example, add auto test

# Phytium Standalone SDK 2022-8-11 ChangeLog

Change Log since 2022-8-16

## common

- fix generic timer tick bug
- fix early trace issue: extra operation for early trace call

## drivers

- delete spi poll-by-byte API and related code
- makeup FGpioGetPinIrqSourceType API
- fix uart compile issue

## third-party

- sdmmc: merge fsdmmc_irq and fsdmmc_poll
- sdmmc: fix csd issue, which is reversed in FT20004/D2000
- sdmmc: remove cmd-23 for FT20004/D2000, since they do not support SD-3.0
- fastfs-sd: compatible with sdmmc modifications

## example

- modify fspim_loopback, support FT20004/D2000/E2000
- modify fgpio_test, simplify code implementation
- add fddma_spi, test ok in E2000

# Phytium Standalone SDK 2022-8-16 ChangeLog

Change Log since 2022-08-11

## board/e2000/q

- add E2000Q mio pin function,board support

## example

- Modify i2c fi2c_master_slave example to support e2000q,add e2000q default configs
- Modify serial example to support e2000q,add e2000q default configs
- Modify rtc rtc_ds1339 example to support e2000q,add e2000q default configs
- Modify timer timer_tacho example to support e2000q,add e2000q default configs

# Phytium Standalone SDK 2022-8-11 v0.3.1 ChangeLog

Change Log since v0.3.0

## README

- add E2000D/S description

# Phytium Standalone SDK 2022-8-5 v0.3.0 ChangeLog

Change Log since 2022-08-04

## drivers

- Add and restruct some drivers adapter e2000 interface

## example

- Add and restruct some test examples adapter e2000 interface
- Modify the example documentations and default configs

## third-party

- Restruct adapter e2000

# Phytium Standalone SDK 2022-08-04 ChangeLog

Change Log since 2022-08-03

## example

- Modify the delay interface function in the XMAC example

# Phytium Standalone SDK 2022-08-04 ChangeLog

Change Log since 2022-08-01

## common

- add e2000d sata controller
- add can2.0 and canfd test choose config
- delete ddma and littlefs examples

# Phytium Standalone SDK 2022-08-03 ChangeLog

Change Log since 2022-08-02

## common

- add e2000d some configuration for interrupt

# Phytium Standalone SDK 2022-08-03 ChangeLog

Change Log since 2022-08-02

## drivers

- fix fgpio FGpioGetPinIrqSourceType bug

# Phytium Standalone SDK 2022-08-02 ChangeLog

Change Log since 2022-07-31

## example

- fix tftp bug

# Phytium Standalone SDK 2022-07-31 ChangeLog

Change Log since 2022-07-30

## board

- fix ROARSE and FRAC delay mis-typing, replace with ROUGH and DELICATE, for E2000 and D2000/FT2004
- add shortcut API to support set delay and get delay

## driver

- remove is_busy flag from fspim
- fix cpol and cpha mistype in fspim
- fix register value overlapping in fspim
- simplify fgpio API FGpioGetPinIrqSourceType

## third-party

- support BY25Q32BS and BY25Q64BS in sfud

# Phytium Standalone SDK 2022-07-30 ChangeLog

Change Log since 2022-7-29

## driver

- fix fnand bug
- fix fxmac bug

## third-party

- add lwip_port some user setting parameters

## example

- Modify the lwip_echo example

# Phytium Standalone SDK 2022-07-29 ChangeLog

Change Log since 2022-07-18

# board

- fix parameters pcie mem32 space, support for pcie-sata aarch32 read/write

# driver

- modify qspi, support spiffs read/write
- modify wdt, support get timeout remaining time
- fix pwm config, support pwm 0~15 channel configuration

# third-party

- fix sfud, spiffs, fatfs modules

# Phytium Standalone SDK 2022-07-27 ChangeLog

Change Log since 2022-07-14

## board

- fix parameters sdio clk hz

## driver

- modify fsdio, support DMA and PIO read/write

## third-party

- modify sdmmc, support eMMc

# Phytium Standalone SDK 2022-07-14 ChangeLog

Change Log since 2022-7-05

## driver

- add fnand controler
- add fxmac controler

## example

- add fnand_example

## third-party

- Port the fnand controller to lwip

# Phytium Standalone SDK 2022-07-13 ChangeLog

Change Log since 2022-6-20

# board

- modify e2000 iomux set function
- modify some parameters

# driver

- modify qspi read and write driver for E2000, add register port read and write data
- modify sata controller and pcie-sata read and write driver for E2000
- modify can driver for E2000, support for can and canfd
- modify pwm driver for E2000
- modify adc driver for E2000, support for adc0-0
- modify wdt driver for E2000

# example

- modify qspi norflash example
- modify sata controller read and write to support E2000
- modify can send and receive example
- modify adc example to collect voltage

# Phytium Standalone SDK 2022-07-12 ChangeLog

Change Log since 2022-07-05

# driver

- move spi dma function to fspim_dma
- modify gdma api

# board

- remove parameters of gdma1

# example

- modify fgdma and fddma example

# Phytium Standalone SDK 2022-07-05 ChangeLog

Change Log since 2022-6-30

# board

- modify e2000 fparameters_comm.h and add set mio function

# driver

- add fi2c configs and init things
- create Mio driver for E2000
- modify uart configs to support E2000

# example

- add RTC1339 example
- modify i2c/fi2c_master_slave to support E2000
- modify serial/fpl011_test to support E2000
- modify timer_tacho adapt to new iopad modifications

# Phytium Standalone SDK 2022-06-30 ChangeLog

Change Log since 2022-6-28

# board

- modify GPIO parameters in FT2000/4 and D2000
- add iopad configs for spi 0~3

# driver

- fix bug that spi busy status mis-set in interrupt mode
- add cs-set function for E2000

# third-party

- modify sfud fspim port to support cs-set

# example

- modify fspim_loopback and tested in E2000
- modify spi_sfud and tested in E2000
- modify littlefs_test and tested in E2000
- modify spiffs_test and tested in E2000

# Phytium Standalone SDK 2022-06-28 ChangeLog

Change Log since 2022-6-20

# board

- merge common parameters / early uart implmenetation of E2000 D/Q/S
- implment all io pad definition
- add iopad function to set func, pull, drive strength at one call

# driver

- update fgpio for E2000

# Phytium Standalone SDK 2022-06-20 ChangeLog

Change Log since 2022-6-16

## arch

- fix aarch32 Bss clear bug

# Phytium Standalone SDK 2022-6-16 v0.2.0 ChangeLog

Change Log since 2022-5-30

## drivers

- Restruct gmac driver
- adapt to freertos lwip function

## example

- Restruct lwip_echo example

## third-party

- modify lwip config

# Phytium Standalone SDK 2022-06-15 ChangeLog

Change Log since 2022-6-14

## drivers

- add timer_tacho driver
- modified fi2c_g.c to support e2000

## example

- add timer example
- add tacho example

## board

- Modify fparameters.h to support timer_tacho and i2c

# Phytium Standalone SDK 2022-06-14 ChangeLog

Change Log since 2022-6-10

## arch

- Add aarch32/aarch64 trace uart in assembly
- Add trace stub function in bootup process

## example

- Add example to demo exception trap

## board

- Modify fparameters.h to support assembly

# Phytium Standalone SDK 2022-6-09 ChangeLog

Change Log since 2022-6-10

## drivers

- Add nand driver

## example

- Add nand flash example

## arch

- clear HCR_EL2.TGE
- AARCH64 enable irq exception

## board

- FPinSetPull mistype

## README

- remove Linux arm aarch64 development environment

# Phytium Standalone SDK 2022-6-10 ChangeLog

Change Log since 2022-5-24

## drivers

- Restruct SDIO driver

## example

- Delete fsdio_probe example
- Add fsdio_cmd example

## third-party

- port fsdio to sdmmc freamwork
- add shell title for E2000 D/Q/S
- add prompt info for building E2000 D/Q/S images

# Phytium Standalone SDK 2022-5-24 ChangeLog

Change Log since 2022-5-18

## drivers

- Add Semaphore driver
- Restruct GDMA driver

## example

- Restruct GDMA async memcpy example
- Add Semaphore lock/unlock example

## common

- Change interrupt source trace to DEBUG level
- Fix memory-pool bug: not set is_ready flag when deinit memory-pool
- Add FASSERT_STATIC to check structure size

# Phytium Standalone SDK 2022-5-18 ChangeLog

Change Log since 2022-5-7

## drivers

- Restruct can driver
- Add pwm driver to support E2000
- Add adc driver to support E2000

## example

- Add can send and recv test
- Add pwm test
- Add adc test

## doc

- Add fcan.md

# Phytium Standalone SDK 2022-5-13 ChangeLog

Change Log since 2022-5-5

## drivers

- Add DDMA driver
- Modify SPIM driver to support E2000
- Modify GPIO driver to support E2000

## example

- Add SPI + DDMA loopback test
- Modify SPI loopback test to support E2000

## common

- Add interrupt source trace
- Skip l3 cache operations when it disabled

## doc

- Update code_convention.md
- Update PR check list

# Phytium Standalone SDK 2022-5-5 ChangeLog

Change Log since 2022-4-15

## drivers

- Slave interrupt handle modified

## example

- Change the command interface
- Add virtual eeprom
- Simulate master-slave communication at D2000

# Phytium Standalone SDK 2022-4-22 ChangeLog

Change Log since 2022-4-15

## drivers

- Restruct I2C driver
- modified master poll write read
- add master intr poll write read

## example

- Restruct fi2c_eeprom example
- Solve the problem of reading across pages
- complete eeprom page alignment

# Phytium Standalone SDK 2022-4-20 ChangeLog

Change Log since 2022-4-11

## drivers

- Restruct gmac driver
- Restruct xmac driver

## example

- Restruct ipv4 test
- Add ipv4 dhcp test
- Add ipv6 test

## third-party

- Add mac lwip port layer to support gmac and xmac
- Restruct gmac and xmac lwip interface

# Phytium Standalone SDK 2022-4-15 ChangeLog

Change Log since 2022-4-8

## drivers

- Restruct GIC driver

## common

- Restruct Interrupt code

## arch

- aarch32/64  support for interrupt preemption

# Phytium Standalone SDK 2022-4-14 ChangeLog

Change Log since 2022-4-8

## drivers

- support test mode in fspim
- support tx and rx run at the same transfer api call

## example

- add fspim loopback test
- add fspim sfud test
- add spiffs filesystem test
- add littlefs filesystem test

## third-party

- add spiffs
- add littlefs, support littlefs dry-run

## common

- modify the way debug trace to have src file + src line tag

# Phytium Standalone SDK 2022-4-8 v0.1.17 ChangeLog

Change Log since 2022-2-18

- update openamp function
- update assert method
- re-construct fgpio, support gpio interrupt
- re-construct qspi norflash and watchdog driver

# Phytium Standalone SDK 2022-3-31 ChangeLog

## drivers

- Restruct watch dog driver, add some additional functions

## example

- Restruct example of wdt test
- Improve manual documentation

# Phytium Standalone SDK 2022-3-28 ChangeLog

## drivers

- Restruct qspi norflash driver, add some additional functions
- Adapt to different norflash manufacturers

## example

- re-organize example of qspi test, broken down into peripheral and storage

# Phytium Standalone SDK 2022-3-25 ChangeLog

Chang Log since 2022-3-18

## driver

- re-construct fgpio, support gpio interrupt
- re-construct fioctrl and fiopad

## example

- add fgpio-irq to demo usage of gpio interrupt
- add fgpio-softpwm to demo generate pwm with gpio
- add fioctrl-test to demo usage of ioctrl
- add fiopad-test to demo usage of iopad

## common

- add e2000 s/d/q default configs
- support print source file and source code line in FT_DEBUG
- convert config item DON_T_BINARY_OUTPUT to OUTPUT_BINARY

# Phytium Standalone SDK 2022-3-18 ChangeLog

Chang Log since 2022-2-18

## script

- Support SDK version
- Move uninstall.py to unsetup.py

## common

- Unify assert api with FASSERT and FASSERT_MSG

## third-party

- Letter-shell: add SHELL_EXPORT_EXIT_MSG and SHELL_EXPORT_EXIT_MSG to support exit msg print when return from cmd rountine

## tools

- Remove build_all_app and intergrate_test_app

# Phytium Standalone SDK 2022-3-09 ChangeLog

Change Log since 2022-2-18

## arch

- Modified some parameters in the MMU and added FSetTlbAttributes interfaces

## third-party

- Add OpenAMP library

## example

- Add OpenAMP example

# Phytium Standalone SDK 2022-2-18 v0.1.16 ChangeLog

Change Log since 2022-2-15

- replace LICENSE with Phytium Public License 1.0 (PPL-1.0)
- update file COPYRIGHT declaration with PPL-1.0

# Phytium Standalone SDK 2022-2-15 ChangeLog

Change Log since 2022-2-7

## drivers

- add fusb driver
- add fxhci driver

## example

- add fxhci-pcie-usb example to support usb device discovery
- add fusbdisk example to port fatfs for usb mass storage device

# Phytium Standalone SDK 2022-2-10 ChangeLog

Change Log since 2021-02-7

## arch

- Modifying Some variable definitions in cache

## common

- Modify the function interface in the _cpu.c document to change the core content not to respond when the work core does not support it
- Fixing interrupt.c initialization problems

## gicv3

- Modifying cpu interface processing of multi-core interfaces in gicv3

## example

- Modifying the handling of multi-core function interfaces in Libmetal

## board

- Add a new cpu directory

# Phytium Standalone SDK 2022-2-07 ChangeLog

Change Log since 2021-12-10

## drivers

- add sata driver
- add fpcie driver

## example

- add sata test example
- add sata fatfs test example
- add pcie probe test example

# Phytium Standalone SDK 2021-12-10 v0.1.15 ChangeLog

Change Log since 2021-12-07

## third-party

- fix get ocr timeout in ft2004
- rename assert and delay macro
- rename ymodem

## example

- unify example makefile setting

# Phytium Standalone SDK 2021-12-07 ChangeLog

Change Log since 2021-12-6

## third-party

- add ymodem transfer

## example

- add rtc module test function

# Phytium Standalone SDK 2021-12-6 ChangeLog

Change Log since 2021-11-29

## drivers

1. re-construct fsdio and fsdmmc

## example

1. add memory test example
2. add fsdio probe example
3. add fsdmmc probe example
4. add fsdmmc cmd example
5. add fsdmmc fatfs example

## common

1. add slink fslink_list.c
2. add memory pool fmemory_pool.c

## configs

1. update default configs for all platform

## third-party

1. re-construct sdmmc port in poll and irq
2. add tlfs to support fmemory_pool.c

## script

1. modify serial_trans.py to improve cmd-trans in D2000

# Phytium Standalone SDK 2021-11-29 ChangeLog

Change Log since 2021-11-25

## arch

1. Add stack initialization
2. Locate the final mode in SVC mode
3. Initialize the BSS and SBSS segments
4. Copy data to the RAM
5. Enable the FPU function
6. Fpu is pushed when irq is abnormal
7. Other exceptions are treated as error exceptions

## ld

1. Add stack parameter Settings for different exceptions
2. Rename variables in different sections

## example

1. Letter_shell test modifies the makefile

# Phytium Standalone SDK 2021-11-25 ChangeLog

Change Log since v0.1.14

## third-party

- add sfud qspi test
- restruct sfud_port.c, add spi and qspi probe

## drivers

- restruct qspi norflash driver

## example

- re-organize example of qspi test
- make spi and qspi compatible in sfud

# Phytium Standalone SDK 2021-11-23 ChangeLog

Change Log since v0.1.13

## third-party

- add coremark 1.01 for core performace test
- add llcbench for cache performance test
- add memperf for memory performace test
- add unity-2.5.2 to support unit test

## drivers

- rename fxmac according to name convention
- update user interface of frtc

## example

- re-organize example with category, e.g. benchmark, eth
- add catche_bench、cormark_bench and memperf_bench

## tools

- add intergrate_test_app and unit_test_app to demo usage of two

# Phytium Standalone SDK 2021-11-17 ChangeLog

Change Log since v0.1.12

## aarch64/gcc

- remodify boot.S
- remodify crt0.S
- remodify vector.S

## aarch64

- remodify exception.c
- remodify mmu.c
- add l3cache.c

## board

- remodify parameters.c

# Phytium Standalone SDK v0.1.12 ChangeLog

Change Log since v0.1.11, 2021.11.15

## example

- add fgmac link example
- add fgmac lwip echo-ping example
- add fgmac lwip tftp example

## driver

- re-construct fgmac driver

## third-party

- modify port of fgmac lwip
- add fatfs, port for ramdisk

# Phytium Standalone SDK v0.1.11 ChangeLog

Change Log since v0.1.10, 2021.11.9

## example

- add fspi nor flash example

## driver

- re-construct fspim driver

## script

- add flash_boot.mk, support make flash monitor

## doc

- add fspim driver api reference
- add sfud reference

# Phytium Standalone SDK v0.1.10 ChangeLog

Change Log since v0.1.9, 2021.11.5

## example

- add rtc driver and test example

## driver

- re-construct wdt drivers
- add rtc driver

## doc

- add wdt driver api reference
- add rtc driver api reference

# Phytium Standalone SDK v0.1.9 ChangeLog

Change Log since v0.1.8, 2021.11.1

## example

- add uart test example

## driver

- re-construct uart fpl011 drivers

## doc

- add fpl011 driver api reference
- add uart test readme

## arch

- add L3 cache disable
- modify the savefloatRegister location
- add

# Phytium Standalone SDK v0.1.8 ChangeLog

Change Log since v0.1.7, 2021.11.1

## example

- add i2c eeprom example
- add i2c slave example

## driver

- re-construct i2c drivers
- support i2c slave

## tools

- add test utility to build example images for all supported platform

## script

- add build_all.mk to support test utility
- support make ldconfig and make setconfig

## doc

- add i2c driver api refernce
- add i2c slave & i2c eeprom readme
- add driver template
- add more design figure *.dio

## bug-fix

- fix CONFIG_USE_LIBC bug, which is converted to CONFIG_USE_G_LIBC in all example

# Phytium Standalone SDK v0.1.7 ChangeLog

Change Log since v0.1.6, 2021.10.20

- re-organize readme and docs

# Phytium Standalone SDK v0.1.6 ChangeLog

Change Log since v0.1.5, 2021.10.19

## example

- add project to demo usage of newlib

## script

- add `PHYTIUM_DEV_PATH` for all platforms
- install cross tool to `PHYTIUM_DEV_PATH`
- update GNU CC version to 10.3.1-2021.07
- modify CC libc.a for printf issue
- merge newlib to CC tool

# Phytium Standalone SDK v0.1.5 ChangeLog

Change Log since v0.1.4, 2021.10.14

## example

- add project template to support Windows10 + mingw64 developing

## script

- modify install.py to support Windows10 + mingw64
- add Windows10 cmd script to access mingw64 shell and Windows tftpd tool
- modify compiler.mk to support Windows10 + mingw64
- add uninstall.py to support uninstall sdk

# Phytium Standalone SDK v0.1.4 ChangeLog

Change Log since v0.1.3, 2021.10.13

## driver

- add iomux for E2000
- add nandflash driver for E2000

## third-party

- add yaffs2 for ramsim

## lib

- Modify the standard system call implementation

## common

- add printf for trap functions

# Phytium Standalone SDK v0.1.3 ChangeLog

Change Log since v0.1.2, 2021.10.08

## drivers

- modify sdmmc drivers for FT2000/4 and D2000 to adopt sdmmc cmd component
- add sdio driver for E2000

## example

- add mmc cmds for overall_test example

## third-party

- modify letter shell to get reture result
- add sdmmc cmd component

## script

- add install.py as alternative install script

# Phytium Standalone SDK v0.1.2 ChangeLog

Change Log since v0.1.1, 2021.9.24

## drivers

- modify gmac_dma driver adapting to freertos lwip

# Phytium Standalone SDK v0.1.1 ChangeLog

Change Log since v0.1.0

## drivers

- support watchdog timer

## baremetal/example

- add wdt_test example

# Phytium Standalone SDK v0.1.0 ChangeLog

Change Log since v0.0.11

## drivers

- support gicv3 init with multiple cores
- support watchdog timer

## baremetal/example

- add letter shell test to demo application of shell
- add libmetal test to demo core0 - core1 commuication with libmetal support

## third-party

- add letter shell 3.1
- add libmetal 1.0.0

## tools

- include elfio tools

## script

- support linkscript config with sdkconfig.h

# Phytium Standalone SDK v0.0.11 ChangeLog

Change Log since v0.0.10

## drivers

- add f_gmac for FT2000-4 and D2000
- support generic timer tick
- unify api interface for cache operation

## baremetal/example

- add gmac_test example to support gmac 'recv intrrupt'
- add lwip_test example to support 'host ping'

## third-party

- port lwip 2.1.2 for FT2000-4 and D2000 with f_gmac

# Phytium Standalone SDK v0.0.10 ChangeLog

Change Log since v0.0.9

## drivers

- add gdma for E2000

## baremetal/example

- add gdma example for aarch32/aarch64
- gdma example surpport direct and bdl mode

# Phytium Standalone SDK v0.0.9 ChangeLog

Change Log since v0.0.8

## drivers

- add pcie for FT200-4

## board

- merge D2000 board

## baremetal/example

- add pcie example for aarch32/aarch64
- pcie example surpport dma and mmio

# Phytium Standalone SDK v0.0.8 ChangeLog

Change Log since v0.0.7

## board

- support D2000
- add D2000 AARCH32/AARCH64 deconfigs

## drivers

- add sdci for D2000/FT2000-4
- add mci for E2000 (to do)
- fix timer & tacho review issues

## make

- support switch platform

Change Log sinc v0.0.6

## board

- add ft2004 io mux parameters

## common

- support delay sleep by ms and us

## configs

- add default configs for supported platform

## drivers

- add i2c drivers
- add qspi drivers
- add timer & tacho drivers

## example

- add i2c eeprom master example
- add qspi nor flash example
- add timer example for e2000

# Phytium Standalone SDK v0.0.6 ChangeLog

Change Log sinc v0.0.5

## driver

- add canfd
- xmac
- spi

## baremetal/example

- add can_test
- add spi_test

# Phytium Standalone SDK v0.0.5 ChangeLog

Change Log sinc v0.0.4

## BSP

- add board to support platforms
- support iomux, gpio and eth drivers

## Scripts

- update install.sh

## Others

- add git attr to fix cr/lr issue

# Phytium Standalone SDK v0.0.4 ChangeLog

Change Log sinc v0.0.2

## BSP

- support Rt-Thread 32 bit single and smp Mode
- Support Rt-Thread 64 bit single Mode
- 32bit , 64 bit baremetal support libc
- 32bit , 64 bit support fpu

## baremetal/example

- aarch32_math_test

## tools

- add sdkconfig.h header

# Phytium Standalone SDK v0.0.2 ChangeLog

Change Log sinc v0.0.1

## BSP

- support SYS Mode for Freertos
- support OS defined Irq/Swi handler for FreeRTOS

## Doc

- add checklist for pre-release check
- update Readme

Change Log since init

## Baremetal

### add aarch32 & aarch64 example

- aarch32_hello_world: hello world run in ft2000-4/e2000
- aarch32_qemu_debug: hello world and step debug in qemu
- aarch32_timer_irq: run with generic timer tick irq
- aarch32_cache_mmu_wr: run with cache (L1/L2/L3) and mmu enabled
- aarch32_uart_irq: run with uart tx and rx irq
- aarch64_uart_irq_send: run with uart tx and rx irq in aarch64

## BSP

- support armv8 aarch32/aarch64
- support platform FT2000-4/E2000/Qemu-AARCH32
- support cache and mmu
- support irq, system trap
- support generic timer
- support assert and debug trace
- support early uart print during system init
- support system error coding

## Lib

- support c standard lib
- support c no standard lib
- add kconfiglib to support menuconfig

## Make

- add basic compile scripts, 'complier.mk' 'ld.mk'
- add compile info print script, 'buildinfo.mk'
- add menuconfig setting script, 'preconfig.mk'
- add source code export script, 'packsource.mk'

## Scripts

- add sdk install and register script, 'export.sh'
- add utility script
