# Change Log

## [1.6.0] - 2024-06-28:

Main changes since 1.5.0
Tested Segger Embedded Studio Version: 8.10d
Tested IAR Embedded Workbench for RISC-V Version: 3.30.1

### Known Issue:
  - some IAR projects does not work properly when optimization level is increased

### Changed:
  - soc: reorganize the directory structure
  - soc: hpm6750: declare get_frequency_for_source API for clock drver header file
  - soc: update soc cmakelists to add b ext info
  - soc: hpm6750: add feature for ioc pad ctrl setting issue
  - soc: toolchains: gcc: correct LMA for NOLOAD sections
  - soc: move eh_frame into separate section
  - boards: hpm6750xxxx apply workaround for E00029.
  - boards: change hpm5301evklite adc16 channel
  - boards: board.h: adc16: add marco BOARD_APP_ADC16_HW_TRIG_SRC_CLK_NAME
  - boards: adjust function position of adc pin initialization
  - boards: hpm6300evk and hpm6e00evk: sdram use px07 as femc dqs pin
  - boards: hpm6e00evk: rename init_sdram_pins to init_femc_pins
  - boards: hpm6e00evk: change board i2c instance to I2C0
  - drivers: can/mcan add parameter check for low-level bit timing.
  - drivers: enet: add bitfield ENET0_RMII_TXCLK_SEL for hpm6300
  - drivers: i2c: add DATACNT high byte process
  - drivers: pwm: update HRPWM process
  - drivers: spi: optimize reading speed for spi_read_data API
  - drivers: spi: add set/get data phase format APIs for spi master
  - drivers: spi: delete the spi startand operation APIs
  - drivers: adc16: remove an unused member conv_duration from adc16_config_t
  - drivers: enet: update for enet_interrupt_enable_t
  - drivers: mcan reduce unnecessary register access in mcan_read_rxfifo.
  - drivers: mtg: add calculate function param clock
  - drivers: mtg: add several calculate functions
  - drivers: mcan lookeup the mcan msg ram base via mcan_soc_msg_buf variable if the MSG_BUF is in AHB RAM.
  - drivers: adc16: disable improvement logic of adc16 for continuous sampling maximum voltage
  - drivers: mcan improve transmitter delay compensation setting logic.
  - drivers: femc: rename data_width_in_byte to cmd_data_width
  - drivers: femc: update ns2cycle() to align up
  - drivers: common: add packed attribute
  - drivers: femc: delete duplicate config
  - drivers: mtg: change the default parameters to the low order filter
  - drivers: adc16: add API adc16_set_seq_hw_trigger_enable()
  - drivers: spi : convert enumeration return in that gets parameters APIs
  - drivers: pwm: add fault recovery code.
  - driver: pwm: change pwm trig time
  - components: enet_phy: dp83867/rtl8211: move the macro definition RGMII to board-level CMakeLists.txt
  - components: eeprom_emulation: Add ATTR_RAMFUNC for all function
  - components: eeprom_emulation: add power-off protection mechanism.
  - components: dma_mgr: add burst in fixed transfer size and swap feature
  - components: spi: add full_duplex and half_duplex operating APIs
  - components: spi: support 1 to 32 bits width transfer for nonblocking APIs
  - components: usb: device: support iso transfer mult feature
  - middleware: hpm_sdmmc add emmc sleep & wakeup function.
  - middleware: tinyusb: ehci: support chain transfer
  - middleware: threadx: add low power support
  - middleware: cherryusb: update for advance descriptor
  - middleware: hpm_sdmmc:  optimized to support multiple cards
  - middleware: cherryusb/tinyusb/usbx: enable suspend isr
  - middleware: FreeRTOS: update to 202210.01 lts
  - middleware: cherryusb: update to v1.3.0
  - middleware: freertos: modify missed timer count num
  - middleware: freertos: update IAR port file
  - middleware: freertos: delete fence operations
  - middleware: freertos: make the calculation more simple.
  - middleware: hpm_sdmmc add cache control macro.
  - middleware: hpm_sdmmc: improve the logic for detecting CMD23 support.
  - middleware: freertos: add tickless stop mode support
  - middleware: freertos: add user custom process function call
  - middleware: hpm_mcl_v2: add hpm smc control.
  - middleware: freertos: place xPortxxx to isr_vector section
  - middleware: hpm_math: add dsp support for zcc
  - middleware: microros: add zcc support
  - middleware: rtos: asm adjustment for zcc toolchain
  - middleware: hpm_mcl_v2: add pwm dead area compensation.
  - middleware: hpm_mcl_v2: add dq axis decoupling function
  - middleware: cherryusb: add macro USBH_USE_CUSTOM_ISR/USBD_USE_CUSTOM_ISR
  - middleware: lvgl: upgrade to v9
  - middleware: lvgl: rewrite the scissor.
  - middleware: lvgl: upgrade allocate algorithm for draw_buf.
  - samples: rdc: remove unused dac driver in sample
  - samples: lwip/netxduo/modbus: add conditional compile for reference clock setting in RMII mode
  - samples: audio_codec: common: change FIL_SEARCH_NUM from 10 to 20
  - samples: dhyrstone: surpress build warnings
  - samples: dhrystone Optimize performance.
  - samples: coremark Optimize performance.
  - samples: drivers: spi: interrupt: transmission optimization. The transmission will start after the configuration is completed.
  - samples: adapt spi components to drive and move to the samples dir for spi sdcard samples
  - samples: cherryusb: device: change descriptor string to HPMicro
  - samples: cherryusb: device: use advanced descriptor to support high/full speed
  - samples: rename jpeg to image
  - samples: drivers: sdxc: sd_fatfs: add card hotplug support
  - samples: cherryusb: host: usbnet:  replace block to noblock for read terminal char
  - samples: cherryusb: host: usbnet: decrease lwip MEM_SIZE
  - samples: cherryusb: move host hid info print code to thread
  - samples: audio_codec: refactoring code
  - samples: spi: dma: SPI master transmission optimization
  - samples: mtg: make the open_loop_trajectory sample more readable
  - samples: drivers: adc16: add some misc optimization
  - samples: drivers: adc16: add pwmv2 support
  - samples: motor_ctrl: bldc_foc_hw: remove hardware control
  - samples: drivers: mcan add tips for the usage of tdc.
  - samples: vglite: update rtos config file to fit gptmr tickless mode
  - samples: lwip/modus/netxduo: add a function call to get the enet default interrupt config
  - samples: sdm: using pwm to provide clock for sdm sensor.
  - samples: spi_components: half_duplex: updated to support 1 to 32bits width transfer
  - samples: spi_components: full_duplex: updated to support 1 to 32bits width transfer
  - samples: add freertos tickless stop mode sample
  - samples: benchmark: update compile options for zcc
  - samples: drivers: adc16: optimize the process logic of sequence and preemption
  - samples: drivers: sei: device: tamagawa: update eeprom cmd
  - samples: adc12: optimization for trigger mux and trigger frequency settings
  - samples: sei: device: tamagawa: support EEPROM protocol
  - samples: mcl: add pwm dead area compensation.
  - samples: motor_ctrl: add dq axis decoupling function
  - samples: cherryusb: move dual_port samples to dual_port folder
  - samples: cherryusb: adapter to cherryusb v1.3.0
  - samples: drivers: adc12/adc16/dac: support abort feature in interactive terminal
  - samples: lwip: lwip_iperf: support abort feature to reselect the test mode
  - samples: lwip: common: multiple: add definitions of remote ip addresses for iperf
  - samples: motor_ctrl: bldc_lvlg_foc: add lvgl v8.3.5 for this demo
  - samples: tinyusb: uac2: support full speed
  - samples: power_mode_switch: update readme
  - samples: cherryusb: uac2: change default samplerate order
  - samples: bldc_foc: update bldc_foc_angle_align() for hardware loop
  - cmake: toolchain: add ar option to remove timestamp
  - cmake: toolchain: suppress output while querying spec
  - cmake: lld: update link option for zcc
  - cmake/scripts/soc: support b ext convertion to tools
  - cmake: sdk_app_src_glob: modify to recursive

### Fixed:
  - soc: update USE_NONVECTOR_MODE defined used
  - soc: initialize .fast_ram.* section
  - soc: iar linker: fix safe stack init
  - soc: add missing ptmr clock
  - soc: hpm6880: fix get_frequency_for_i2s error
  - soc: hpm6880: Modify the value of SPI_SOC_FIFO_DEPTH from 4 to 8. for hpm_soc_feature.h
  - soc: toolchain: iar fix iar ram_stress issue in ram_debug build.
  - boards: hpm5301evklite: fixed can't output work for gptmr samples such as pwm_generate
  - drivers: enet: fix the clearing of DMA PBL setting
  - drivers: dma: fix dma_clear_transfer_status() API
  - drivers: sdxc Fix timeout calculation issue and DMA enabling logic.
  - drivers: adc16: fix the logic of adc16_set_pmt_queue_enable() when the parameter enable is false
  - drivers: mbox: fix error that BEIE can't be operated by interface
  - drivers: spi: fixed assignment value error for  spi_set_clock_phase and spi_set_clock_polarity APIs
  - drivers: lcdc: fix ST and DMA_ST clear api.
  - drivers: mipi_dsi: fix MIPI_DSI_FMT_RGB565 config.
  - drivers: spi: fixed assignment error issue for enable/disable address phase APIs
  - drivers: i2c: fix return value type of i2c_get_data_count()
  - components: usb device/enet_phy: fix unwanted files in localize folder
  - components: panle: fix panel timing.
  - components: eeprom_emulation: demo flash crashed.
  - middleware: cherryusb: ehci: delete timeout clear before give sem
  - middleware: uC/OS-III: modify fpu context save&restore
  - middleware: cherryusb: fix freertos enter/exit critical
  - middleware: audio_codec: fix hpm_wav_decode() single channel pbuf data
  - middleware: mclv2: fix andes toolchain compiler error.
  - middleware: cherryusb: fix ehci_qh_pool init miss busid for v1.3.0
  - middleware: lwip: apps: lwiperf: fix the bug of failing to restart iperf in TCP/UDP server mode
  - middleware: tinyusb: fix _usbd_dev.speed error to support full speed
  - middleware: hpm_mcl_v2: fix uncontrolled after large changes in motor speed.
  - samples: dhyrstone: fix build issue for release type using nds toolchain
  - samples: lwip: lwip_tcpclient: fix TCP commnuication error after DHCP enabled
  - samples: lwip: lwip_tcpclient_freertos_socket: fix connection error before IP assigned from DHCP
  - samples: correct cmsis_os2/mem_pool project name
  - samples: multicore: common Fix SDP memcpy blocking issue in ram_build.
  - samples: lwip: lwip_tcpecho_xxx_rtthread_nano: fix failing to get IP by DHCP serivice
  - samples: spi_sdcard: fixed the place section name error issue
  - samples: cherryusb: audio: fix wm8960 codec volume max value
  - samples: img: jpeg_decode: fix decode when only one qtab exist.
  - samples: tflm: mlperf: remove unnecessary codes.
  - samples: fix cherryusb mic no sound error
  - samples: spi_components: polling: fixed doesn't work for polling samples
  - samples: tamagawa: fix delay times is zero.
  - samples: bldc_foc: fix hardware_foc position loop error
  - cmake: link ndsgcc itf for application
  - cmake: localize_sdk: use utf-8 as default encoding
  - cmake: ide: keep preprocessing definition

### Added:
  - soc: add zcc toolchain support
  - soc: clock_driver Add clock_set_wdg_source API.
  - soc: gcc linker: add fast_ram.init section size overflow check
  - soc: add FreeRTOS vector mode support
  - soc/board: add HPM6E80 support
  - drivers: common: add macros for .fast_ram.*
  - drivers: enet: add an API enet_get_default_interrupt_config
  - drivers: enet: add MII mode support
  - drivers: common add api for converting tick to us or ms.
  - drivers: pllctlv2 add new API to configure PLL.
  - drivers: uart: add uart_modem_write_rts_pin API
  - drivers: uart: add get/clear addr match flags APIs such as addr_match, addr_match_idle, data_lost
  - drivers: add lobs drivers
  - drivers: usb: add some APIs for low power future usage drivers: spi: add spi_slave_set_user_status API
  - drivers: usb: add suspend/resume APIs
  - drivers: usb: add enter/exit lower power suspend APIs
  - drivers: spi: add read SPI RX/TX FIFO size APIs
  - drivers: usb: add usb_set_port_test_mode() API
  - drivers: sdp add new apis.
  - drivers: mcan add new api for canceling pending transmission.
  - drivers: mtg: add get&clear event irq interface
  - drivers: qeiv2: add oneshot mode
  - drivers: add clc driver
  - drivers: add vsc driver
  - drivers: spi: add get/set shift direction APIs
  - drivers: uart: add an new API uart_try_receive_byte()
  - drivers: pixelmux: add api that set mipi dsi date type.
  - drivers: gptmr: add monitor function APIs
  - drivers: gptmr: add opmode APIs
  - drivers: gptmr: add qeimode APIs
  - components: add i2s_over_spi
  - components: codec: add wm8978
  - components: enet_phy: add jl1111 driver
  - components: add ppi components
  - components: touch: add gt9271 driver.
  - components: debug_console: add a new API console_try_receive_byte()
  - middleware: add lodepng
  - middleware: add minimp3
  - samples: cherryusb: device: add WinUSB 1.0 and WinUSB 2.0 samples
  - samples: lwip: add LPI interrupt mask setting
  - samples: add i2s_emulation sample
  - samples: lvgl_audio_player: support mp3 decoder
  - samples: uart: add uart_rx_line_status sample
  - samples: add half_duplex samples for spi_components
  - samples: add full_duplex samples for spi_components
  - samples: drivers: sdxc: emmc add new sameple for eMMC sleep & awake.
  - samples: drivers: add lobs sample
  - samples: drivers: spi: sd/sd_fatfs: support DMA transfer
  - samples: threadx: add low power mode sample
  - samples: image: add png encoder sample
  - samples: image: add png decoder sample
  - samples: audio_codec: add decoder_mp3 sample
  - samples: ppi: add parallel adc sample
  - samples: ppi: add async_sram sample
  - samples: qeov2: add wave_out sample
  - samples: qeov2: add abz_out sample
  - samples: pwm: add async fault demo
  - samples: motor_ctrl: add hardware foc
  - samples: drivers: pwmv2: add pwmv2 pair waveform
  - samples: dmav2: add dmav2_fixed_burst_swap sample
  - samples: qeiv2: add oneshot mode sample
  - samples: add smix_dao sample.
  - samples: add ecat_io sample.
  - samples: cherryusb: add one host and one device dual port sample
  - samples: add pwm/hrpwm fault mode
  - samples: lwip: add lwip_iperf_multi_ports
  - samples: drivers: tsw: add a tsn_switch sample
  - cmake: add symbol HPM_BUILD_TYPE to specify build type
  - docs: add generated cmake_intro.rst
  - docs: getting started: add zcc support related information

## [1.5.0] - 2024-03-29:

Main changes since 1.4.0

Tested Segger Embedded Studio Version: 7.32a
Tested IAR Embedded Workbench for RISC-V Version: 3.20.1

### Known Issue:
  - some IAR projects does not work properly when optimization level is increased

### Changed:
  - soc: iomux: update macro prefix in pmic_iomux and batt_iomux.
  - soc: feature: change usb endpoint max number from 8 to 16
  - soc: correct svd files and add subpart module list
  - drivers: usb: change usb_phy_get_line_state() to external function
  - drivers: qeiv2: update filter length setting
  - drivers: adc12/adc16: add sanity check for sample cycle
  - drivers: femc: add delay_cell_disable config option
  - drivers: i2s: change fifo threshold parameter.
  - drivers: i2c: replace and use the macro definition of hpm_soc_ip_feature.
  - drivers: uart: supplementary description of uart_check_status API.
  - components: enet_phy: lan8720/rtl8201/rtl8211: unify the default config with type bool
  - components: enet_phy: remove unused included header file
  - components: enet_phy: rtl8201/rtl8211: update register description
  - components: dma_mgr: change isr handler from static to public
  - middleware: tinyusb: host: use echi drivers
  - middleware: tinyusb: rename CFG_TUSB_HOST_DEVICE_MAX to CFG_TUH_DEVICE_MAX
  - middleware: tinyusb: update to v0.16
  - middleware: rtthread-nano: use soc reset_handler and define MAIN_ENTRY as entry
  - middleware: fatfs: tinyusb: adapter to tinyusb update
  - middleware: threadx: use TX_TIMER_TICKS_PER_SECOND to config work ticks
  - middleware: threadx: use samples tx_user.h
  - middleware: uC/OS-III: enable sw interrupt in OSCtxSw/OSIntCtxSw
  - middleware: ucos: ports: Added IAR portable layer for ucos.
  - middleware: cherryusb/azure_rtos: add defined __ICCRISCV__ for iar
  - middleware: hpm_math: simplify libdsp path.
  - middleware: cherryusb: update to v1.1.0
  - middleware: rtthread-nano:halt cpu when exception occur.
  - middleware: hpm_math: simplify libnn path.
  - middleware: threadx: move frequently called function to ram.
  - middleware: tinyusb: change endpoint number from 8 to 16
  - middleware: usbx: change endpoint number from 8 to 16
  - middleware: cherryusb: msc device: update to support multi lun and deinit
  - middleware: eclipse_threadx: update license
  - middleware: fatfs: tinyusb: add osal_task_delay() when use rtos wait
  - middleware: tinyusb: update CMakeLists.txt and delete custom osal_task_delay()
  - middleware: tinyusb: add debounce in port change isr
  - samples: erpc: add middleware src use middleware CMakeLists.txt
  - samples: multicore: core1: use board_init_core1() API
  - samples: multicore: coremark: delete custom reset_handler and use app_main as MAIN_ENTRY
  - samples: tinyusb: update samples to adapter tinyusb v0.16
  - samples: usbx: host: delete unused hpm_usb_host.h
  - samples: usb: delete CONFIG_USB_HOST set
  - samples: lvgl_coremark: disable freqswitch_btn when coremark running
  - samples: mono: move to driver directory.
  - samples: freertos: change configMAX_PRIORITIES from 7 to 32
  - samples: rtthread: delete unused macro RT_THREAD_PRIORITY_32
  - samples: cherryusb: usbnet: decrease rtos stack config size
  - samples: lwip: all: unify logs about IP information
  - samples: lwip: lwip_https_server: remove an unused file
  - samples: lwip: all: update DHCP progress logic
  - samples: lwip: common: remove s_pxNetIf
  - samples: lwip: adjust the directories of netconf.c/netcof.h
  - samples: lwip: common: optimize speed for getting IP from DHCP server
  - samples: lwip: rename common_lwip.c to common.c
  - samples: lwip: common: adjust the call logic of netif_set_up/netif_set_down
  - samples: lwip: common: change the time of invoking netif_user_notification
  - samples: lwip: common: rename user_notification to netif_user_notification
  - samples: lwip: adjust directory structures to be compatible with single and multiple network ports
  - samples: use generate_ide_projects for new samples
  - samples: cherryusb: device: cdc acm: reorganize directory structure
  - samplse: gptmr: t_shape_accel_decel: modify the source address mode of DMA.
  - samples: cherryusb: device: change readbuf size from 2048 to CDC_MAX_MPS
  - samples: drivers: femc: update sdram dqs config
  - samples: update app.yaml to use ip_feature
  - samples: drivers: uart: change to app uart
  - samples: audio_codec: update wm8960 I2S protocol.
  - samples: drivers: cam: change cam sample to cam_dvp sample.
  - samples: usbx: device: msc: decrease ram disk size to 16KB
  - samples: cherryusb: msc device: update to support multi lun
  - samples: driver: uart_lin: support LIN transceiver on board.
  - samples: adc: temp: rename temp to adc16_temperature
  - samples: bldc block: Compatible with both hall and qeiv2 peripherals.
  - samples: motor_ctrl: Modify the value of pwm reload.
  - samples: lwip: common: single/multiple: update the size passed into sys_mbox_new()
  - samples: lwip: common: single/multiple: replace enet_get_link_status with netif_is_link_up
  - samples: lwip: lwip_https_server: remove unused header file
  - samples: lwip: rename macro TCP_XXX_PORT
  - samples: lwip: add cmake flag for netconn/socket api
  - samples: decode_wav: sd_fafts: update sd_choose_music.
  - samples: power_mode_switch: maintain xpi0 clock on switching preset
  - samples: dhrystone Change the optmization level to O3.
  - samples: tinyusb: hid_generic_inout: delete redundant image
  - samples: power_mode_switch: hpm67/hpm63: preserve femc clock at wait/stop mode
  - samples: erpc: core1: use optimization -os
  - samples: update uart_tamagawa to use software trig if TRGM not exist.
  - samples: eeprom_emulation: reduce management area
  - samples: sdxc: use block_size instead of 512
  - samples: erpc: add -fno-exceptions compile option
  - samples: tinyusb: disable debug log print
  - boards: hpm5300evk and hpm6800evk: add delay after USB_PWR Pin init for power stable
  - boards: hpm6750evkmini: modify gptmr pins.
  - boards: hpm6200evk: modify gptmr pins.
  - boards: hpm6200evk: modify the i2c pins.
  - boards: hpm6750xxx: update sdram dqs config
  - boards: hpm6800evk:pinmux Increase drive strength for sdxc pins
  - boards: iomux: update macro prefix for pmic_iomux and batt_iomux.
  - boards: rename board feature
  - boards: update BOARD_APP_UART definition
  - boards: rename console definitions
  - boards: hpm5301evklite: update uart clock in board.c.
  - boards: hpm6750evkmini: change BOARD_GPTMR_PWM_DMA_SRC definition.
  - docs: samples: use glob in high level readme.
  - docs: update top level readme.
  - docs: netxduo: update sntp readme.
  - docs: threadx: update threadx hello readme.
  - docs: lwip: align pictures to the left
  - docs: pip: add cmake doc dependency
  - docs: add changelog to sphnix-doc.
  - scripts: ses: generate asm after build by default.
  - scripts: update linked project path logic.
  - scripts: check_board_cap.py: check ip feature's availability
  - cmake: remove CMP0116 setting.
  - cmake&scripts: clarify the error caused by core1 compiling failure.
  - scripts: ses/iar: use relpath in project file

### Added:
  - soc: hpm6360/hpm6750/hpm6800: add MAC-related definitions in OTP section
  - soc: reset: add MAIN_ENTRY macro to custom define main entry
  - soc: add hpm6850 and hpm6830 part.
  - soc: soc_modules.list: add tamper drivers
  - soc: Add IAR toolchain support.
  - soc: add ip feature to soc_modules.list
  - soc: add hpm_soc_ip_feature.h
  - soc: driver: ppor: add reset hold operation APIs
  - soc: clock_driver add the clock_get_divider API.
  - soc: sysctl: add apis to control clock preservation
  - soc: toolchains: gcc: ram linker: add ILM last address overflow check
  - drivers: mcan Add timeout counter support.
  - drivers: tamper: add tamper driver
  - drivers: cam: add cam_update_buffer2 API
  - drivers: opamp: Add user configuration code.
  - drivers: lcdc: add stride for layer config.
  - drivers: pdma: add pdma_blit_ex.
  - drivers:pllctl add out-of-bound check in pllctl driver.
  - components:uart_lin: add hpm_uart_lin_send_wakeup() API
  - components: enet_phy: add LAN8720 driver
  - components: enet_phy: add definition of enet_phy_link_status_t
  - middleware: cherryusb: host: add dual port support
  - middleware: cmsis_os2: adapter to rtthread wrapper
  - middleware: cmsis_os2: update freertos files
  - middleware: cmsis_os2: adapter to threadx wrapper
  - middleware: cmsis_os2: adapter to ucOS-III wrapper
  - middleware: hpm_sdmmc Add eMMC config partition API.
  - middleware: cherryusb Add IAR toolchain support
  - middleware: erpc Fix IAR RISC-V support issue
  - middleware: tflm: add IAR riscv support in flatbuffer
  - middleware: FreeRTOS: portable:Added IAR portable layer.
  - middleware: segger_rtt Added EWRISCV support
  - middleware: hpm_math Add nds_dsp library for IAR.
  - middleware: lwip: cc: add PACK_STRUCT_XXX definitions for IAR platform
  - middleware: uC/OS-III: enable plicsw in IAR asm code
  - middleware: add tinyengine
  - middleware: threadx: add support for gptmr.
  - middleware: threadx: add profile support.
  - middleware: add agile_modbus.
  - middleware: add cherryrb.
  - middleware: cherryusb Add missing swap32/swap16 implementation.
  - middleware: hpm_mclv2: add block type drive motors
  - middleware: cherryusb: fix usbh_core ep0 buffer index
  - boards: hpm6200xxx and hpm6750xxx: add board_init_core1() API
  - boards: add tamper feature and pins init
  - boards: hpm5300evk: add board_init_console() declaration in board.h
  - boards: hpm6750evk/hpm6750evk2: add board_dual_usb feature
  - boards: openocd: add windows guide to *_all_in_one.cfg
  - boards: openocd: soc: add reset_soc proc
  - board:add pgpio configuration on hpm5301evklite
  - samples: drivers: add mono sample.
  - samples: drivers:mcan Add timeout counter sample.
  - samples: drivers: tamper: add tamper sample
  - samples: cmsis_os2: blinky: add rtthread samples
  - samples: cmsis_os2: add msg_queue sample
  - samples: cmsis_os2: add mem_pool samples
  - samples: cmsis_os2: msg_queue: add ucOS-III support
  - samples: cmsis_os2: blinky: add ucOS-III support
  - samples: lwip: common: add a task netif_update_link_status
  - samples: lwip: add MAC address load from OPT MAC area
  - samples: cherryusb: device: cdc acm: add cdc_acm_uart_com sample
  - samples: cherryusb: device: add msc sdcard sample
  - samples: tinyengine: add person detection.
  - samples: rtos: add threadx gptmr sample.
  - samples: modbus: tcp: add tcp samples.
  - samples: modbus: rtu: add rtu sample.
  - samples: add cherryrb sample.
  - samples: cherryusb: host: add dual port sample
  - samples: cherryusb: device: add dual port sample
  - samples: cherryusb: device: add dual lun msc sample
  - samples: lwip: ports: rtthread-nano: multiple: add arch-related files
  - samples: lwip: ports: freertos: multiple: add arch-related files
  - samples: lwip: common: multiple: osal: add osTaskFunction definition
  - samples: lwip: add a lwip_tcpecho_multi_ports_rtthread-nano sample
  - samples: lwip: add a lwip_tcpecho_multi_ports_freertos
  - samples: lwip: lwip_tcpecho_xxx: add definitions for task priorities
  - samples: lwip: lwip_tcpecho_freertos_socket: newly add
  - samples: lwip: lwip_tcpclient: newly add
  - samples: lwip: add lwip_tcpclient_freertos_socket
  - samples: vglite: add sample of rotate tiger.
  - samples: lwip: lwip_tcpclient_freertos_socket: fix failure to run
  - samples: lwip: lwip_tcpclient: fix failure to run with some release-related type
  - samples: jpeg: jpeg_encode: add debounce for button.
  - docs: add cmake doc
  - docs: hpm5300evk: add qeiv2 sin/cos pins
  - scripts: support sdk project localization.
  - cmake: add nds-gcc options to sdk_lib for nds-gcc.
  - cmake/scripts: add IAR project generation support
  - cmake: add symbols to specify linker for tools.
  - cmake: add sdk_*_src_glob.
  - cmake: add custom targets for localization.

### Fixed:
  - soc: hpm6750: fix segger linker vectors order
  - soc: hpm_interrupt.h Fix compiling warning for DSP related macros
  - soc: hpm6750: otp Fix OTP program and read logic
  - soc: hpm6880: clock Fix wrong enum value for TSNS clock.
  - soc: clock driver: correct the clock name value for pll clocks.
  - soc: HPM6280: fix adc/dac clock setting
  - soc: ppor: fix ppor clear reset flag and set reset type API error
  - soc: HPM6880: fix i2s clock config driver
  - drivers: adc12: fix calibration setting error
  - drivers: cam: DMASA_FB2 need to be assigned whether FB2 buffer is enable or not.
  - drivers:can correct the logic of disabling re-transmission for ptb & stb.
  - drivers: qeo: fix driver error
  - drivers: i2s: ensure valid BCLK before call software reset.
  - drivers: pdma: fixed OUT_PS[] config.
  - components: wm8960: invert LRCLK to align with soc I2S.
  - middleware: uC/OS-III: fix register t0 unsafe.
  - middleware: ptpd: fix netShutdown error in ptpd initialization
  - middleware: cmsis_os2: task should call exit interface before exit
  - middleware: threadx: fix threadx profile RA register save and restore bug.
  - middleware: hpm_mcl: fix divide-by-zero error. refs: hpm_sdk-#1091
  - middleware: cherryusb/tinyusb/usbx: device: fix transfer_len not reset
  - middleware: cherryusb/usbx: fix dtd return problem
  - middleware: cherryusb/tinyusb/usbx: fix usb device interrupt should be check active status
  - middleware: tinyusb: fix ehci cap_reg address error
  - middleware: tinyusb: fix hid report id
  - middleware: cherryusb: fix usbd_ep_close not reset ep_enable flag
  - middleware: cherryusb: fix rndis message length check
  - middleware: freertos: fix implementation error in xPortIsInsideInterrupt.
  - boards: hpm6200evk: fix tamper pin config
  - board: openocd: all_in_one: hpm6800 config file is missed.
  - boards: openocd: all_in_one: hpm5300: correct soc config name.
  - samples: threadx hello: fix printing errors.
  - samples: drivers: ad12/adc16: fix initialization sequence for trigger source, trigger mux and trigger target config
  - samples: lwip: lwip_ptp: fix netSend error before link-up
  - samples: dma: fix dma uart init position
  - samples: drivers:spi:master_trans_large_amound_of_data Fix logic error if SPI support 4GB transfer size
  - samples: sdxc: add boundary protection for last 1024 blocks test
  - samples: lwip: common: multiple: fix typo of enet_update_dhcp_state()
  - samples: lwip: common: single/multiple: fix timeout passed into sys_arch_mbox_fetch()
  - samples: e2prom: bugfix: base read fail if run perf firstly .refs:hpm_sdk-#1499
  - samples: modbus: tcp:  use volatile to prevent the compiler from optimizing out key variables
  - samples: modbus: rtu: fixed failed to run after turning on optimization issue.
  - samples: power_mode_switch: hpm68xx: fix ddr access issue for wait/stop mode
  - samples: cherryrb: fixed stack overflow issue
  - samples: lwip: lwip_tcpecho_multi_ports_ports_rtthread-nano: fix failure to run
  - sample: jpeg: jpeg_encode: fix that udisk can't be mounted when first capture.
  - cmake: correct board search path symbol for core1.
  - cmake: gcc: fix system include path.
  - cmake: fix sdk_link_libraries failed to link std lib.
  - cmake: EXTAR_LD_FLAGS to be added as ld options.
  - docs: lwip_ptp: v1: salve: fix format error
  - docs: samples: ppor: change title from sysctl to ppor
  - docs: hpm6750evk2: fix table display error

## [1.4.0] - 2023-12-29:

Main changes since 1.3.0

Tested Segger Embedded Studio Version: 7.32

### Changed:
  - soc: hpm5301: add hpm5301
  - soc: hpm6880: add hpm6880
  - soc: HPM6750: pcfg: update dcdc dcm mode config
  - soc: clock driver: update clock_set_source_divider() and clock_get_source()
  - boards: add hpm5301evklite
  - boards: add hpm6800evk
  - boards: update clock_set_source_divider() to use clk_src_t type param
  - boards: hpm6750evkmini: use the same uart port as core1 for some samples.
  - drivers: dao: update driver support new feature on hpm6800
  - drivers: adc16: update comment about cal_avg_cfg in calibration
  - drivers: qeiv2: change adc trigmux name x to 0 and y to 1
  - drivers: femc: add overflow protect to time config
  - drivers: mcan Enlarge the range of CAN_EVENT_ERROR.
  - components: serial_nor: add subdirectory in cmakelists
  - middleware: cherryusb: update to v0.10.2
  - middleware: cherryusb: rename host and device isr
  - middleware: FreeRTOS: xPortIsInsideInterrupt() using CSR_MSCRATCH
  - middleware:hpm_sdmmc Enhanced all speed modes support for SD and eMMC.
  - middleware: usbx: device: support chain transfer
  - samples: cherryusb: host: rndis: integrate dhcp thread into ping thread for host rndis ping and iperf sample
  - samples: adc: temp: add isr for temp out of thresholds
  - samples: drivers: acmp: optimization for comparing input voltage
  - samples: lwip: add DHCP macro definition in CMakeLists.txt
  - samples: lwip_ptp: enable DHCP feature in PTP samples
  - samples: drivers: qeiv2: update API for adc-qeiv2 pin initialization
  - samples: bldc_foc: change adc buffer size from 40 words to 48 words
  - samples: remove explicitly c++ standard setting.
  - samples: driver: cam: set default cmake build type
  - samples: lwip: update to Class C static IP adress
  - samples: tinyuf2: remove unnecessary cache ops.
  - samples: lwip: lwip_tcpecho_freertos: optimization for API call in a thread-safe way
  - samples: lwip: lwip_ptp: v1: slave: update static ip
  - samples: lwip: optimize DHCP enable logic
  - samples: lwip: opts: adjust the allocation strategy of memory pool
  - samples: lwip: lwip_iperf: adjust MEM_SIZE for saving memory consumption
  - samples: lwip: lwip_tcpecho_multi_ports: update the second IP with C class
  - samples: enet: optimization for PHY selections
  - samples: dma: update uart rx circle transfer buffer size
  - samples: drivers: sdxc/emmc Correct doc for emmc sample.
  - cmake: sdk_link_libraries link libraries for supported tools.
  - cmake: add project name for hpm_sdk sub directory.
  - cmake: decouple CMAKE_BUILD_TYPE and linker script.
  - cmake: ses: remove -Ox from gcc option list.
  - cmake: set default c++ standard to c++11.
  - Update CONFIG_HAS_xxx to HPMSOC_HAS_xxx.
  - segger: enable all warnings.
  - segger: release: release optimization level use cmakelist config
  - scripts: ses: set intermediate dir in project file.
  - docs: remove quick start guide from top level readme
  - docs: change doc structure.

### Added:
  - soc: HPM5361: add trgm filter shift length feature
  - soc & drivers: hpm5300: add DMAMUX_SOC_WRITEONLY and TRGM_SOC_HAS_DMAMUX_EN features
  - drivers: lcb: add lcb driver.
  - drivers: sdxc add more APIs for timing and power control.
  - drivers: mipi_csi: add mipi csi.
  - drivers: cam: add cam_stop_safely API
  - components: usb: device: add dtd chain transfer
  - components: panel: enable panel component.
  - components: camera: ov5640: add mipi interface.
  - middleware: rtthread-nano: add v3.1.5
  - middleware: rtthread-nano: add FPU support.
  - middleware: tinyusb: device: update to support chain transfer
  - middleware: cherryusb: device: update to support chain transfer
  - middleware: vglite: add 4.0.49.
  - middleware: cherryusb: add USB_OSAL_WAITING_FOREVER for sem and mq use
  - middleware: add hpm_mcl_v2
  - middleware: lwip: add ptpd v1 & v2
  - middleware: cmsis_os2: add source files.
  - samples: mcl: add step motor.
  - samples: lwip: lwip_ptp: v2: support IEEE1588 V2
  - samples: cherryusb: add audio_v2_mic_speaker_rtthread sample
  - samples: cherryusb: host: add hid and msc rtthread samples
  - samples: cherryusb: host: usbnet: add support ec20 module sample.
  - samples: cmsis_os2: add blinky sample.
  - samples: driver: mipi_csi: add mipi_csi.
  - samples: mcan Support MCAN4-7 loopback testing.
  - cmake: support custom output file name.

### Fixed:
  - soc: fix cache maintenance at startup
  - soc: hpm53xx Correct exip API tree offset.
  - soc: toolchain: missing .fast.* in gnu ld linker script.
  - soc: fix tbss and tdata section not initialized.
  - soc: sysctl: sysctl_enable_group_resource() should be check LOC_BUSY
  - soc: hpm5300 Correct Cache size and Cacheline size.
  - boards: hpm6750evkmini Fix the issue that eMMC is still 3.3V even 1.8V is selected.
  - boards: hpm5301evklite correct jlink script device number.
  - components: camera: power_up is enable by default for ov5640/ov7725.
  - docs: samples: drivers: add numberic index.
  - drivers/soc: fix build warning
  - drivers: i2c: add slave device response judgment for master read/write APIs
  - drivers: opamp: fix opamp vssa connect error.
  - drivers: pllv2: fix pllctlv2_pll_is_stable() API
  - drivers: qeiv2: fix invalid argument check
  - drivers: dac: fix the upper limit value setting for DAC_OUTPUT
  - drivers: jpeg: fix pixel format index for out buffer.
  - drivers: uart: fix not support oversample 32 for rx idle detection on hpm5300
  - middleware:ftafs Fix SD card init crash.
  - middleware: mcl: fix path plan error.
  - middleware: hpm_sdmmc Fix the issue that IO initialization work unstable on HPM6300.
  - middleware: hpm_sdmmc Fix voltage switch setting issue for SD and eMMC.
  - middleware: hpm_sdmmc Fix the PWR and VSEL IO initiaization issue. refs:hpm-sdk-#863
  - samples: sei: fix nikon sample crc calc error.
  - samples: cherryusb: msc device: add pre-format fat12 file system in u disk
  - samples: adcx: replace const with a macro for ADC sample cycle
  - samples: tinyusb:fix the usb host pin init.
  - samples: motor_ctrl: bldc_littlevgl_foc: program crash.
  - samples: qeiv2: uvw: fix uninitialized pointer usage
  - samples: cherryusb: fix semaphore give in isr
  - samples: drivers: Fix the issue that can error example may block.
  - samples: uart_irq: fix unable to limit receive large than buffer size.
  - samples: drivers:sdxc:emmc remove infinite loop for emmc initialization.
  - samples: drivers: i2s: fix tx underflow during tx start
  - samples: lwip: lwip_tcpecho_multiple_ports: fix no echo data when receiving large amounts of data
  - samples: mcl: pwm duty set error.
  - samples: cherryusb: host: usbnet: fixed when performing a stress test with a large amount of iperf data, will send fai.
  - samples: cherryusb: audio_v2_mic_speaker_rtthread: fix mic no voice problem
  - samples: jpeg_decode: add delay after usb pins init for waiting power stable
  - samples: hfi: hpm6750evk2: fix the motor shake.
  - cmake: segger: remove workstation specific path info.
  - cmake/soc: fix heap/stack size setting for andes toolchain.
  - cmake: ses: correct device name for core1.

## [1.3.0] - 2023-09-28:

Main changes since 1.2.0

Tested Segger Embedded Studio Version: 7.32

### Changed:
  - boards: hpm6200evk/hpm6300evk: delete unwanted clock_ahb div set
  - boards: hpm6750xxx: switch dcdc work mode to dcm mode
  - docs: sdk: boards: hpm6750evk2: add pps pin information
  - component: wm8960: support sysclk pre-divider
  - components: serial_nor: add serial nor flash.
  - openocd: probes: ft2232: remove trst and srst config.
  - ip: cam：remove 0x5c MAX_WN_CYCLE register in regs.h
  - driver: cam: remove invalid register
  - drivers: i2s: update API
  - drivers: adc: adc12/adc16: rename adc16_get_busywait to adc16_is_nonblocking_mode
  - drivers: adc: adc12/adc16: update adcx_init API
  - drivers: pllctrl: update pllctrl drivers
  - drivers: spi : add spi enable and disable datamerge
  - drivers: spi : add spi_set_address_len API
  - drivers: pdgo Add missing APIs
  - drivers: uart: update uart rx idle flag process and fifo control
  - soc: delete_unnecessary_ppor_reset_bit_field
  - soc: hpm_gpiom_soc_drv.h: delete gpiom_gpio_t soc name
  - soc: delete DMA_SOC_BUS_NUM Macro
  - soc: pcfg: update pcfg SCG_CTRL related drivers
  - soc: hpm6750:startup Enable LMM1 clock before access to LMM1
  - soc: gcc ld: add memory used size check
  - middleware: cherryusb: update to v0.10.1
  - middleware: guix: demo adapts to 800 * 480 resolution
  - middleware: guix: improve demo display performance
  - middleware: cherryusb: update for midi descriptor define
  - middleware: cherryusb: update for midi
  - samples: drivers: adc: adc12/adc16: speed optimization for oneshot reading
  - samples: drivers: adc: adc12/adc16： update API call used for nonblocking judgement
  - samples: drivers: adc: adc12/adc16: update API call related to blocking setting in oneshot mode
  - samples: drivers: adc: adc12/adc16: reduce the input parameters of init_trigger_target function
  - samples: drivers: adc: adc12/adc16: update init_oneshot_config
  - samples: drivers: adc: adc12/adc16: optimization for clearing interrupt status
  - samples: drivers: pwm: Add pwm clock jitter demo
  - samples: cherryusb: hid host: separate mouse and keyboard urb
  - samples: hrpwm: Add demo for updating hrpwm frequency
  - samples: drivers:mcan Add CAN error handling and refined logic.
  - samples: mbx: move dualcore mbx sample to multicore folder
  - samples: cherryusb: update for v0.10.1
  - samples: motor_ctrl: bldc smc: gcc toolcahin enable fpu.
  - samples: lwip: lwip_tcpecho_freertos: optimization in a thread-safety way
  - samples: qeo: update qeo abz frequency configuration
  - samples: gptmr: add sent_signal sample.
  - samples: lwip: lwip_ptp: remove the dependency on pps0 pinout
  - samples: dma_manager: update for use dma_mgr_setup_channel()
  - samples: drivers: gptmr: pwm_measure: support use dma
  - samples: lwip: lwip_httpsrv/lwip_https_server: rename project names for uniform naming
  - samples: multicore: lvgl_coremark: delete custom linker files and using andes toolchain
  - samples: flash_algo: update device size.
  - samples: cherryusb: host: hid: use ep_mps to fill urb

### Added:
  - cmake: ses: support specify custom openocd board cfg file.
  - cmake: support specifying minimum sdk version in app.yaml.
  - boards: add hpm5300evk
  - components: eeprom_emulation: add hpm nor-flash support
  - components: eeprom_emulation: add eeprom emulation component
  - soc: add APIs for get or set sysctl resource status
  - drivers: common: add HPM_ALIGN_DOWN and HPM_ALIGN_UP define
  - drivers: adc: ad12/adc16: add adcx_set_blocking_read/adcx_set_nonblocking_read
  - drivers: add encoder position driver
  - drivers: lcdc: add enable/disable background in alpha blender.
  - drivers: usb: add api to set dp/dm pin pulldown resistance
  - drivers: spi: add spi_get_rx_fifo_valid_data_size and  spi_get_tx_fifo_valid_data_size APIs
  - drivers: spi: add directIO function APIs
  - drivers: enet: add rx resume API
  - drivers: adc16: add resolution setting in adc16_get_default_config API
  - drivers:rtc Add rtc_get_timeval API.
  - drivers:mcan Add mcan_transmit_via_txfifo_nonblocking API.
  - drivers: usb: add usb_hcd_set_power_ctrl_polarity() API
  - drivers: plb: add plb drivers
  - drivers: linv2: add linv2 driver
  - drivers: sei: add sei driver
  - drivers: dmav2: add dmav2 driver
  - drivers: qeo: add qeo driver
  - drivers: qeiv2: add qeiv2 driver
  - drivers: mmc: add mmc driver
  - drivers: rdc: add rdc driver
  - drivers: add opamp driver
  - drivers: bgpr: add related APIs for bgpr
  - middleware: FreeRTOS: add xPortIsInsideInterrupt() API
  - middleware: threadx: add definition automatically when enable traceX
  - middleware: freeRTOS: add use gptmr to generate interrupt
  - middleware: hpm_mcl: add hfi
  - samples: drivers: adc: adc12/adc16: add wdog feature
  - samples: add opamp demo
  - samples: cherryusb: rndis: host: add iperf sample.
  - samples: cherryusb: rndis: host: add ping sample.
  - samples: drivers: adc: adc12/adc16: add hw trigger configuration in sequence mode
  - samples: eeprom_emulation: add eeprom emulation perf test sample
  - samples: eeprom_emulation: add base api demo
  - samples: tracex: add demo for traceX usage
  - samples: cherryusb: add audio_v1_mic_speaker_midi sample
  - samples: cherryusb: add midi device sample
  - samples: drivers: sei: add sei samples
  - samples: drivers: plb: add plb demo
  - samples: drivers: mmc: add mmc demo
  - samples: drivers: qeiv2: add qeiv2 demo
  - samples: drivers: qeo: add qeo demo
  - samples: drivers: dmav2: add dmav2 demo
  - samples: drivers: linv2: add linv2 demo
  - samples: drivers: rdc: add rdc demo
  - samples: drivers: pdgo Add PDGO samples
  - samples: drivers: ewdg Add EWDG sample
  - samples: lwip: add a lwip_tcpecho_multi_ports sample
  - samples: motor_ctrl: add hfi

### Fixed:
  - cmake: fix segger default heap and stack size config
  - cmake: fix add_subdirectory_ifdef arg processing.
  - doc: boards: hpm6300evk: fix acmp pin info.
  - boards: hpm6750evkmini: fix board_init_rgb_pwm_pins() problem
  - boards: hpm6200evk: fix BOARD_G_GPIO_CTRL defined in wrong position
  - openocd: hpm6750-dual-core: fix expression warning.
  - component: wm8960: fix clock tolerance process
  - soc: toolchains: segger: block tls add with fixed order
  - soc: toolchain: gcc: fix Thread-Local Storage problem
  - soc: segger linker files: fix heap and ctors initialize
  - soc: fix interrupt complete operation
  - soc: pcfg: fix DCDC_PROT[OVERLOAD_LP] bit access
  - soc: ip: adc12: fix ADC12 threshold setting
  - soc: HPM6750: fix clock setting and frequency obatining error
  - soc: HPM6360: fix clock source definitions for ADC16
  - soc: HPM6280: fix clock source definitions for ADC16
  - soc: HPM6360: fix obtaining clock source error for DAC
  - soc: HPM6280: fix obtaining clock source for DAC
  - drivers: adc16: add bus mode enable control APIs
  - drivers: adc16: fix ahb setting
  - drivers: cam: clear the status of CAM should not affect other bits
  - drivers: trgmux: filter function can't work.
  - drivers: src: adc16: fix end count setting
  - drivers: adc/dac: fix interrupt status clearing
  - drivers: adc16: fix DMA access format
  - drivers: sdm: fix over sample rate and signal sync problem
  - drivers: pwm: fix pwm xcmp enable setting
  - drivers: pwm: correct external fault polarity setting.
  - drivers: pwm: add update hrpwm reload shadow api
  - drivers: spi: fix  can't  set change data_bits use  spi_set_data_bits API
  - drivers: ptpc: fix ptpc_clear_irq_status API issue.
  - drivers: i2c: fix i2c_clear_status API issue.
  - drivers: gptmr: fix gptmr_clear_status API issue.
  - middleware: erpc: rpmsg_lite: fix platform_in_isr() error
  - middleware:hpm_sdmmc Fix the issue sdsc cards are not supported.
  - middleware: threadx: fix D extend asm code error
  - samples: usbx: add multi devices and hot plug support
  - samples: motor_ctrl: fix adc trig invalidate.
  - samples: lwip: fix TCP reception error when size over 2KB
  - samples: lwip: DHCP failure in lwip_tcpecho_freertos
  - samples: drivers: adc: adc12: fix the status flag judgement in isr process
  - samples: rgb_led: fix cmp shadow error
  - samples: gptmr: pwm_generate: fix inaccurate duty in high frequency
  - samples: lwip: low_level_input: fix the network storm issue
  - samples: timer_basic: fix inconsistent use of defines
  - samples: drivers: adc: adc16: fix the bit of interrupt status clearing in sequence mode
  - samples: power_mode_switch: trigger system lowpower for standby mode
  - samples: touch_panel: fix error data when 5 fingers touch screen at same time.
  - samples: jpeg: jpeg_decode: fixed lcd display is tore when decoder is running
  - samples: jpeg: jpeg_decode: malloc out of memory on gcc
  - samples: drivers:can Fix abnormal behavior on can error sample.
  - samples: segger_rtt: call board_init_clock.
  - samples: drivers: acmp: fix one toggle value but multi toggle pulses
  - samples: lwip_tcpecho_freerstos: fix code stuck with gcc toolchain
  - samples: jpeg: fix JPEG_USE_UDISK compile error
  - samples: bldc_foc: fix input value range.
  - samples: cherryusb: rndis: udp_echo: fix echo extra char
  - samples: usbx: fix global var placement
  - samples: power_mode_switch: set to preset_1 after exiting wait mode.
  - samples: pla: fix pla first pulse abnormal.
  - samples: plb: fix the first pulse is abnormal.

## [1.2.0] - 2023-06-30:

Main changes since 1.1.0

Tested Segger Embedded Studio Version: 7.22

### Changed:
  - boards: hpm6750evk*: decrease core frequency from 816MHz to 648MHz
  - openocd: soc: hpm6280: simplify dual core release core1 approach.
  - cmake: segger: configure optimization level according to gcc level.
  - soc: dmamux: move it from ip to soc
  - soc: interrupt: adjust irq api. #659
  - soc: improve svd file
  - soc: hpm_soc_feature.h: remove ADC16_SOC_TEMP_CH_EN for some specified Socs
  - components: enet_phy: update the common enet phy header file
  - components: sgtl5000 and wm8960: update clock setting
  - drivers: uart: update uart driver
  - drivers: pdma: improve quality of scale
  - drivers: adc: adjust wait_dis type in adc16_config_t struct
  - drivers: enet: update rmii reference clock setting API for ENET
  - utils: hpm_swap: escape for andes toolchain.
  - middleware: hpm_sdmmc: add spi sdcard
  - middleware: motor_ctrl: change the file organization
  - middleware: motor_ctrl: remove slide control content from foc
  - middleware: lvgl: upgrade to v8.3.5 (with pdma)
  - middleware: lvgl: Add direct mode
  - middleware: cherryusb: update version to v0.8.0
  - samples: I2S_DMA and I2S Interrupt: update sample behavior
  - samples: cherryusb: hid host: separate mouse and keyboard urb
  - samples: cherryusb: increase max interface and endpoint number Configuration
  - samples: cherryusb: uac2: move setting sampling freq to isr
  - samples: cherryusb: audio: update descriptor for identification
  - samples: audio_codec: set codec voice to max and increase irq priority
  - samples: multicore: lvgl_coremark: delete custom linker files and using andes toolchain
  - samples: lvgl_audio_player: update CMakeLists.txt to using noncacheable framebuffer
  - samples: spi: clean the redundant code
  - samples: i2c: improve the processing of FIFO in ISR
  - samples: drivers: uart: update uart_rx_timeout demo
  - samples: drivers: gptmr: split sample into multiple function samples
  - samples: drivers: adc: optimization for all macro definitions in applications
  - samples: drivers: adc: update struct member names
  - samples: update clock divider setting for ADC-related examples
  - samples: cherryusb: move vid/pid etc definition to usb_config.h
  - samples: cherryusb: device: update vid to hpmicro 0x34B7
  - samples: cherryusb: change API update for v0.8
  - samples: cherryusb: device: audiov1: change to full speed mode
  - samples: tinyusb: uac2: update descriptor and sample
  - samples: lwip: disable mmc interrupt settings
  - samples: lwip: lwip_ptp: v1: sync precision improvement

### Added:
  - cmake: toolchains: add isa spec 20191213 support.
  - cmake: ses: support set ses raw option in CMakeLists.txt
  - cmake: add option to specify board search path.
  - cmake: generate compile_commands.json file
  - soc: hpm_soc_feature: add a common macro for ADC12 and ADC16
  - drivers: cam: add new APIs
  - drivers: spi: add new APIs
  - drivers: i2c: add new APIs
  - drivers: I2S: add i2s_check_data_line_status API
  - drivers: dma: add dma_set_transfer_src_width_byte_size() API
  - drivers: gptmr: add output capture APIs
  - drivers: gptmr: add gptmr_channel_get_dma_request_event api
  - drivers: adc: add adc16_trigger_pmt_by_sw API
  - drivers: enet: add some APIs related to interrupt settings
  - drivers: enet: add a new API for transmisstion
  - drivers: usb: add macro CONFIG_USB_DEVICE_FS to set full speed mode
  - components: uart_lin: add uart lin component
  - components: add smbus
  - components: add sccb
  - middleware: lvgl: add macro HPM_LVGL_FRAMEBUFFER_NONCACHEABLE
  - middleware: add AzureRTOS (threadx/usbx/netx/guix)
  - middleware: hpm_mcl: sensorless over-zero
  - middleware: add smc
  - middleware: hpm_sdmmc Add eMMC support
  - middleware: hpm_math: add bit conversion function
  - middleware: add uC/OS-III
  - middleware: cherryusb: audio: add feedback descriptor
  - middleware: cherryusb: audio: add param to set endpoint bmAttributes
  - middleware: microros: add microros foxy sources
  - samples: drivers: spi: add spi_sdcard_fatfs sample
  - samples: drivers: spi: add sd sample
  - samples: add uart_lin
  - samples: motor_ctrl: sensorless: over-zero demo
  - samples: cherryusb: add rndis host dhcp samples
  - samples: drivers: sdxc :emmc Added eMMC sample
  - samples: drivers: adc12: update irq pattern for sequence usage
  - samples: drivers: pla: add pla tamagawa demo
  - samples: drivers: gptmr: add counter_sync sample
  - samples: drivers: gptmr: add timer_basic sample
  - samples: drivers: gptmr: add t_shape_accel_decel sample
  - samples: drivers: dma/gptmr: add trigger dma transfer using gptmr event sample
  - samples: drivers: uart add uart_rx_timeout sample
  - samples: i2c: add smbus samples
  - samples: lwip: lwip_tcpecho_freertos: add self-adaption
  - samples: cherryusb: hid host: move usbh_submit_urb() out of condition
  - samples: cherryusb: add composite freertos sample
  - samples: cherryusb: add rndis freertos sample
  - samples: cherryusb: add msc freertos sample
  - samples: cherryusb: add audio v2 mic speaker freertos sample
  - samples: cherryusb: add hid mouse freertos sample
  - samples: cherryusb: add hid keyboard freertos sample
  - samples: cherryusb: add cdc acm freertos sample
  - samples: cherryusb: add rndis tcp server sample
  - samples: cherryusb: add rndis device udp_echo sample
  - samples: cherryusb: add rndis device http_server sample
  - samples: cherryusb: device: add audio_v2_speaker_sync sample
  - samples: add several uC/OS-III samples
  - samples: smc: add smc demo
  - samples: microros: add subscriber, sevice and publisher
  - samples: uC/OS-III: mutex

### Fixed:
  - cmake: ses: fix __SEGGER_RTL_vfprintf issue with nds tool in SES 7.20.
  - soc: hpm6280: Modify the number of PWM cmps.
  - soc: reset.c: __dso_handle needs to be declared for nds toolchain.
  - soc: fix max buffer length in sequence mode for ADC
  - soc: HPM6750: enet soc drv: fix set clock delay settings
  - soc:hpm6360:sdxc Correct clock divider settting issue
  - drivers: pla: missing Union Field
  - drivers: spi: fix the problem of CMD and ADDR configuration order
  - drivers: i2c: fix clock frequency error rate problem
  - drivers: i2c: clear CMPL bit in API to avoid blocking the trans
  - drivers: i2c: fix i2c slave device read and write fail
  - drivers: i2c: fix read data unexpected multi transition.
  - drivers: i2c: fix w1c clear status error
  - driver: usb: fix w1c clear flag error
  - drivers: gptmr: fix dma request enum definition
  - drivers: adc: fix logics for judging the validity of arguments
  - component: uart_lin: fix break signal problem
  - middleware: cherryusb: fix buffer size error
  - middleware: lvgl: fix fbbuffer option
  - samples: gptmr: fix pwm_measure sample compile waring
  - samples: jpeg: fix interchange format of exif support
  - samples: jpeg: fix jpeg decode
  - samples: drivers: spi: fix the problem of CMD and ADDR configuration order
  - samples: drivers: mcan: can_fd loopback test setting is incorrect
  - samples: cherryusb: http_server_freertos: fix printf content error
  - samples: cherryusb: audio: change endpoint attributes for support MACBOOK
  - samples: tinyusb: msc: increase block numbers for windows format
  - samples: lwip: lwip_httpsrv: fix reload or refresh error

## [1.1.0] - 2023-03-31:

Main changes since 1.0.0

Tested Segger Embedded Studio Version: 7.10

### Changed:
  - docs: add new docs for rtd project.
  - soc: ip: enet: update the enet register file
  - soc: ip: adc16: update the adc16 header file
  - soc: hpm_romapi - Add APIs for configuring remapping, exip regions
  - drivers: enet: improve APIs related to PPS
  - drivers: adc: change adc bus blocking interface
  - drivers: adc: optimize getting oneshot result
  - drivers: src: update the default config for ADC12&ADC16
  - boards: rename board-level APIs related to enet
  - components: enet_phy: rtl8201: update the register file
  - middleware: hpm_math: update dsp version
  - middleware: erpc: update to v1.10.0
  - samples: uart: rename uart_dma_rx_idle to uart_software_rx_idle
  - samples: uart: add hardware rx idle detection sample
  - samples: multicore: erpc: core1 add sdk_compile_options(-O1)
  - samples: drivers: gptmr: update sample output.
  - samples: lwip: common: arch: ethernetif: update a calling function name
  - samples:drivers: adc: optimize oneshot handler

### Added:
  - arch: add FPU related APIs
  - soc/board: add HPM6280 support
  - soc: HPM6750: acmp: add ACMP section
  - components: add mt9m114 support
  - drivers: add raw8 pixel format support
  - drivers: csr - Implement CSR driver
  - drivers: adc: adc16: support resolution setting
  - drivers/samples: add SDM/PLA/CRC/MCAN
  - drivers: I2C: add new API
  - drivers: adc: adc16: support resolution setting
  - drivers: enet: add enet control config for transmission
  - middleware: cherryusb: audio: update class driver and demo template
  - middleware: add mbedtls lib files with SDP acceleration
  - freeRTOS: add support for static allocation
  - samples: drivers: enet: add a pps demo
  - samples: cherryusb: add audio samples
  - samples: add the resolution parameter in all demos with ADC16
  - samples: add rfft demo
  - sampels: i2c: add interrupt b2b samples
  - samples: drivers: i2s: add an i2s_master demo
  - samples: drivers: i2s: add an i2s_slave demo
  - samples : rom_api : add sw_gm_api filter
  - samples: add the resolution parameter in all demos with ADC16

### Fixed:
  - openocd: hpm6300evk: update sdram initialization.
  - drivers: trgmux: trigmux edge filter setting error
  - drivers: enet: fix register access error
  - drivers: adc16: fix the config error of ADC16_CONFIG1
  - drivers: i2c: fix i2c timing configuration
  - drivers: SPI: fix SPI status API
  - drivers: fix gptmr cmp value don't minus one
  - drivers: mcan: correct the mcan ext_id filter issue
  - drivers: I2C: fix issue in i2c_master_address_read API
  - drivers: Self_ACK cannot be set in CAN driver
  - drivers: rtc rtc_config_alarm always return error code
  - cmake: correct source code compilation
  - soc: toolchain: gcc: initialize heap for SES
  - soc: gcc linker files: add NOLOAD keyword to noncacheable.bss section
  - soc: HPM6360: gcc: ld: correct noncacheable region name.
  - drivers: qei: Fix speed display always zero
  - middleware: freertos: disable global irq before vTaskStartScheduler
  - freeRTOS: fix trap when enable float feature
  - freeRTOS: fix tick lost
  - freeRTOS: fix segger project build warning
  - samples: drivers: i2s: fix CFGR config
  - samples: drivers: fix acmp toggle error
  - samples: lwip: fix the DHCP issue
  - samples: uart: fix irq_id judgment
  - samples: fix the order of uart pin configuration and clock configuration
  - samples: update spi dma sample
  - samples: drivers: sysctl: correct reset enable approach.
  - samples: fix dma_general_transfer sample memory out of bounds
  - samples: drivers: wdog: Fix logic issue on finding the nearest interrupt interval
  - sample: audio_codec: decoder_wav: add '\0' to fatfs path

## [1.00.0] - 2022-12-31:

Main changes since 0.14.0

Tested Segger Embedded Studio Version: 7.10

### Changed:
  - boards: add version info in banner.
  - board: lcdc: move panel para to board
  - components: spi component to support to transfer different width of data in dma handshake mode
  - drivers: rename dram to femc
  - middleware: cherryusb update to v0.7.0
  - middleware: erpc: update for support rtos
  - middleware: hpm_mcl: update api naming
  - samples: erpc: rename erpc_matrix_multiply_rpmsg to erpc_matrix_multiply_rpmsg_bm
  - samples: erpc: reorganize erpc_matrix_multiply_rpmsg samples
  - samples: erpc: move samples folder to erpc_matrix_multiply_rpmsg
  - samples: update i2c/spi dma channel and dmamux channel definition
  - ses: project template: use demo.* as output file naming.
  - soc: HPM6750: toolchains: update linker files
  - soc: HPM6360: toolchains: update linker files

### Added:
  - arch: riscv: add read_clear_csr() API
  - component: add wm8960 support
  - component: add usb device iso transfer support
  - drivers: hpm_common: include hpm_sdk_version.h.
  - drivers: common: add NOP and WFI.
  - drivers: uart: add api to recv/send byte directly.
  - soc: HPM6750 linker files: rename rpmsg_sh_mem to sh_mem
  - cmake: add sdk version header file generation.
  - middleware: tinyusb: add audio class
  - middleware: hpm_math: add NN library
  - samples: erpc: add erpc_two_way_rpc_rpmsg_rtos sample
  - samples: erpc: add erpc_matrix_multiply_rpmsg_rtos sample
  - samples: add power mode switch demo. #282
  - samples: drivers: adc: add a temperature measurement demo
  - samples: drviers: femc: add sram sample
  - samples: lwip demo for FreeRTOS
  - samples: lwip demo of interrupt usage
  - samples: tinyusb: add uac2 demo
  - samples: tflm: add face detection demo
  - samples: tflm: add MLPerf Tiny benchmark demo
  - samples: lwip: common: feature: add a LPI interrupt process

### Fixed:
  - drivers:interrupt: Fix FPU context crashing in nested irq case
  - drivers: src: adc: fix adc result in period mode
  - segger: update app directory structure in SES.
  - soc: disable irq during cache maintenance
  - middleware: lvgl: fps calculation to No.
  - samples: get off level based on board api.
  - samples: multicore: hello: core1 rgb led does not change correctly.

## [0.14.0] - 2022-10-31:

Main changes since 0.13.0

Tested Segger Embedded Studio Version: 6.34a

### Changed:
  - drivers: inc: update adc driver
  - drivers: gptmr: update reload value
  - components: enet_phy: optimize APIs
  - components: enet_phy: dp83867: rename functions
  - components: conditionally add debug_console
  - middleware: add cherryusb (0.6.0)
  - middleware: littlevgl: update to v8.3.1
  - middleware: fatfs: file name encoding in utf-8
  - middleware: freertos: support nested irq handling
  - middleware: hpm_mcl: Optimized motor control foc speed
  - samples: drivers: dma src move to dma_general_transfer folder
  - samples: lwip: update all static addresses and all gateway addresses
  - samples: lwip: lwip_iperf: optimize the interactive log
  - samples: tinyusb: device: hid_generic_inout: optimize the python script
  - openocd: HPM6750A1 silicon in hpm6750-dual-core.cfg
  - header file: update the enet/conctl register files
  - header file: Update TRGMUX0 pin input source definition
  - header file: update the ADC12 header files
  - scripts: ses: organize file in ses according to real path.
  - cmake: split gcc and ses source
  - board: bump HPM6750 DCDC voltage to 1200mv

### Fixed:
  - drivers: pdma: fix scale api issue
  - drivers: i2c: update DATACNT processing
  - drivers: i2s: fix i2s interrupt workaround in i2s_init
  - drivers: pwm: fix pwm capture function error
  - drivers: pwm: fix pwm capture configuration error
  - drivers: clock: fix error in clock_set_xxx_source
  - drivers: wdg: timeout calculation error
  - drivers: trgm_drv: bugfix: include error
  - drivers: romapi: call fencei after flash erase/write operation
  - drivers: watchdog: overflow
  - drivers: usb: host controller initialization issue
  - drivers: i2s: i2s_enable() issue fix
  - middleware: tinyusb: src: class: fix the HID report desc macro
  - samples: drivers: adc: optimize all ADC demos
  - samples: drivers: adc: fix all channel initializations  without a default value
  - samples: motor_ctrl: hardware trigger api usage error
  - samples: audio_codec: update clock process for 44100 sample rate
  - samples: lcdc: boundary pixel is incorrenct
  - samples: multicore: BOOT_HEADER was missing in multicore core0 example
  - samples: drivers: i2s: correct audio data if depth < 32bit.
  - samples: hpm_math: fft_perf_test: Fix error printing information
  - samples: fix pdm2dao noise problem
  - samples: lwip: fix the enet throughput degradation
  - soc: correct address overlapping SES XIP linker file
  - soc: correct the interrupt context switch issue
  - soc: fix Lack of interrupt claim for swi
  - boards: fix some rmii reference clock APIs

### Added:
  - boards: add hpm6750evk2 support
  - soc: add initfini.c
  - drivers: lcdc: add y8 support
  - drivers: spi: update data_length processing
  - drivers: spi:  add api to enable/disable spi dma request
  - drivers: pmp: Add pmp_config_entry API
  - components: add ipc_event_mgr
  - component: spi: add cache maintain
  - middleware: add erpc
  - samples: lwip: support self-adaptive port speed and duplex mode
  - samples: jpeg: support grayscale
  - samples: drivers: spi: use api to get data length
  - samples: drivers: spi:  add interrupt b2b sample
  - samples: drivers: mbx: add singlecore samples
  - samples: drivers: add dma circle transfer
  - samples: drivers: pwm: add pwm capture demo
  - samples: provide OTP API demo
  - samples: add cherryusb hid/msc/cdc samples
  - samples: add Guomi API example
  - samples: add erpc sample
  - samples: add segger_rtt

## [0.13.0] - 2022-07-31:

Main changes since 0.12.1

### Changed:
  - drivers: adc: fix sequence and preemption mode
  - drivers: usb: automatically change transceiver type in host mode
  - drivers: pwm: modify the interface for setting the pwm shadow register trigger function
  - drivers: sdxc: driver improvement
  - samples: jpeg demo update
  - samples: motor_ctrl: Optimize motor control performance
  - samples: motor_ctrl: Modify the pwm update method to be hardware triggered
  - samples: audio_codec: wav: Modify the interface
  - samples: audio_codec: add dao support
  - samples: tinyusb: update all USB project names
  - samples: adc: place DMA buffer in noncacheable
  - components: usb: update two struct definitions for the hcd_data_t and the dcd_data_t
  - middleware: littlevgl: update double buffer refresh approach.
  - middleware: fatfs: enable exfat format
  - middleware: fatfs: change 'USB' to lowercase
  - middleware: hpm_math: remove cache operations from the ffa interface
  - scripts: ses: update file path using $(HPM_SDK_BASE)

### Fixed:
  - drivers: gpiom: fix spelling errors in API names
  - drivers: enet: fix ptp time offset update
  - drivers: cam: fix store mode configuration
  - drivers: can: Fix the issue can timestamp cannot be enabled
  - drivers: gpio: incorrect return type gpio_get_port_interrupt_flags.
  - middleware: audio_codec: decoder_wav: fix wav codec problem
  - middleware: tinyusb: fix the alignment of _hcd_data
  - soc: driver: clock: i2s get clock error
  - soc: hpm_misc.h: fix incorrect system address mapping.
  - soc: SVD files: fix SDP peripheral reset value problem
  - soc: disable vector mode explicitly.
  - boards: correct device name in ses project
  - board: correct the printf format for frequency and register base
  - python: fix ses project generation on windows
  - samples: adc: fix not working in sequence mode and preemption mode
  - ses: set obj path for common configuration.
  - cmake: ses: put app source into separate category in ses.

### Added:
  - components: enet_phy: add rtl8211 driver
  - components: hpm_spi: add initial SPI component
  - components: add DMA Manager
  - drivers: cam: add new API
  - drivers: uart: add uart_set_baudrate API
  - drivers: spi: update dma transfer API
  - samples: tinyusb: host: add a hid demo
  - samples: drivers: spi: add master_trans_large_amount_of_data example
  - samples: decoder_wav: Add support for different bit rates and bits
  - samples: drivers: audio: automatic acquisition of i2s clock frequency
  - middleware: tinyusb: update portable file for USB host

## [0.12.1] - 2022-07-01:

Main changes since 0.12.0

### Fixed:
  - update lwipopt.h for updated enet driver

## [0.12.0] - 2022-06-30:

Tested with SES 6.32

Main changes since 0.11.0

### Changed:
  - boards: hpm6360evk has been renamed to hpm6300evk
  - boards: Use CSR_CYCLE in the clock_delay function
  - soc: hpm_soc.h: include hpm_common.h
  - driver: rename hpm_pmu_drv.c to hpm_pcfg_drv.h
  - driver: spi: change to non-blocking interfaces
  - driver: dma: update driver to adapt to different DMA instance constraints
  - components: enet_phy: update dp83867 driver
  - components: enet_phy: remove rtl8211 driver
  - cmake: enable nano newlib by default
  - cmake: move distclean to the beginning
  - middleware: littlevgl enable PDMA by default
  - middleware: tinyusb: upgrade to 0.13.0
  - samples: tinyusb: device: cdc_msc: adjust buffer size
  - samples: drivers: plic: use gpio toggle count as nested irq

### Fixed:
  - drivers: pwm: fix function name inconsistency bug
  - drivers: enet: remove "board.h" in enet driver
  - drivers: clock: Fix bugs in hpm6360 clock driver
  - drivers: clock: returns wrong adc/dac clock in HPM6360
  - drivers: dram: failed to configure 8bit mode.
  - freertos: fix issue about running on core1
  - boards: hpm6300evk pmp_entry set initial value
  - middleware: littlevgl: fix pdma cache op issue
  - middleware: littlevgl: fix doxygen markdown for pdma driver
  - middleware: lvgl: ses: update ram linker.
  - middleware: hpm_math: fix ffa cache size error
  - samples: audio_codec: remove the wrong dependency
  - samples: FATFS demo cannot support write/read if FATFS passes unaligned buffer address

### Added:
  - samples: add memstress and flash stress
  - drivers: clock: add implement common delay function based on mcycle and mcycleh register
  - boards: add hpm6300evk support
  - boards: hpm6750evkmini: motor control support
  - soc: add svd files
  - middleware: lwip: iperf: enable iperf and add udp function
  - samples: lwip: add lwip_iperf

## [0.11.0] - 2022-05-31:
Main changes since 0.10.0-hpm6360-er

### Changed:
  - readme: change the location of the starting document
  - components: change hal_adc_xx to hpm_adc_xx
  - drivers: update the I2C driver
  - cmake: change default rv_arch to rv32imac
  - cmake: modified in a zephyr-compatible way
  - drivers: uart: redefined struct with zephyr
  - cmake: change soc and board name
  - cmake: ses: support enable ext_dsp in project file.
  - samples/tinyusb/host: optimize the toggle rate of the blinking led
  - samples/tinyusb/device: replace mchtimer with board_timer for led_linking_taskk
  - samples/tinyusb/device: optimize the implement of led_blinking_task
  - soc: update IP header and soc header files

### Fixed:
  - samples: motor_ctrl: bldc_block: fix some error
  - middleware: hpm_math: fix andes toolchain compile error
  - middleware: hpm_math: fix libdsp.a error
  - middleware: hpm_math: add ext-dsp for SES
  - samples: openocd_algo: fix func_table placement.
  - boards: hpm6360evk: correct cpu frequency
  - boards: fix warning caused by code irregularities
  - boards: LED status is not the same between hpm6750mini rev-A and rev-B
  - boards: update board_led_write.

### Added:
  - driver: add spi_setup_dma_transfer() API
  - middleware: hpm_math: add software fft function
  - middleware: hpm_math: add ffa to hpm_math
  - samples: i2c: update the sample b2b
  - samples: hpm_math: add fft_performance demo
  - samples: add SPI DMA sample
  - samples: multicore coremark using debug console only
  - samples: 1588: add ptp v1 master/slave

## [0.10.0_hpm6300] - 2022-05-16:
Main changes since 0.10.0

### Changed:
  - ip register header file update
  - ses_proj: using generated complete cpu_regs_xml to replace general cpu registers xml
  - drivers: gpiom: move gpiom_gpio_t into hpm_gpiom_src.h
  - drivers: update the enet driver
  - samples: dram: change sdram test address in dma demo
  - samples: drivers: mbx: exclude flash targets for core0 as well.
  - samples: lwip: update ethernetif.c

### Fixed:
  - drivers: ptpc: update ptpc_init_timer_with_initial.
  - drivers: can: bug fix and update
  - soc: correct vector table inclusion and swi name
  - env.sh: fix HPM_SDK_BASE setting problem with msys.
  - samples: sha256_example: failed to run case 13 and 14 with gcc.

### Added:
  - soc: add HPM6360 support
  - drivers: add ffa, pllctlv2, dac
  - boards: add hpm6360evk support
  - components: add adcx module
  - components/enet_phy: add the RTL8201 driver
  - samples: drivers: dac, ffa
  - samples: rgb_red: add evkmini ver B support

## [0.10.0] - 2022-04-30:
Main changes since 0.9.0

### Changed:
  - drivers: gptmr: split irq enable/disable interface
  - drivers: can: 155 Update SJW setting in CAN driver
  - soc: HPM6750: rename safe stack symbol in link script
  - components: debug_console: wait uart tx flag on writing.

### Added:
  - drivers: enet: add 1588 support
  - drivers: can: Add TDC support
  - drivers: mchtmr: add counter init API.
  - drivers: dma: add dma_disable_channel() API
  - middleware: add wav decoder
  - samples: lwip: add ptp demos
  - samples: tinyusb: add msc, cdc demo
  - samples: audio_codec: add wav player demo
  - samples: add tinyuf2 initial support
  - samples: add initial uart dma rx idle demo

### Fixed:
  - soc: HPM6750: sysctl: fix cpu lp mode API.
  - drivers: uart: correct baudrate calculation.
  - drivers: usb: fix: no response in device mode when a USB cable is pluged out
  - boards: correct the pin setting related to USB

## [0.9.0] - 2022-04-01:
Main changes since 0.8.0

### Changed:
  - drivers: update WDG, UART, DMA, DMAMUX driver
  - drivers: enet remove enet_intf_selection
  - drivers: can: support configure bit timing via low-level bit timing parameters
  - drivers: optimize gpio driver
  - samples: exclude flash targets for mbx core1
  - samples: adjust SES project setting for coremark
  - samples: jpeg: update and integration jpeg decode samples
  - ses: use relpath for linker script in project file
  - ses: add HPM device name in generated project file
  - soc: HPM6750: add an interface selection api

### Added:
  - soc: HPM6750: add ram linker for core1
  - ses: support to use Andes toolchain
  - middleware: add hpm_math (replacing hpm_dsp)
  - samples: add lwip httpd
  - drivers: add section and alignment general instructions in hpm_common.h

### Fixed:
  - boards: hpm6750evk: fix bldc adc pinmux error
  - boards : hpm6750evk : pinmux : fix spi init pins error
  - samples: sdp: fix non-cacheable data initialization issue
  - samples: littlevgl: fix wrong picture patch in README

## [0.8.0] - 2022-03-04:
All changes since 0.7.3

### Changed:
  - rename middleware/sdmmc to middleware/hpm_sdmmc
  - place isr into .isr_vector section for irq non-vector mode
  - change csr functions to support llvm

### Fixed:
  - ses: fix issue in register xml
  - freertor: fix trap handler at non-vector mode
  - sdxc: fix software reset issue

### Added:
  - add sdk doc
  - add more sample doc
  - add multicore demo
  - i2c/uart: add dma support
  - add tensorflow lite for microcontroller

## [0.7.3] - 2022-02-23:
All changes since 0.7.2

### Changed:
  - freertos: change exception handling

## [0.7.2] - 2022-02-21:
All changes since 0.7.1

### Changed:
  - freertos: change freertos irq stack definition, passed in CMakeLists.txt, defined in linker
  - soc: hpm6750: add DISABLE_IRQ_PREEMPTIVE to check if it needs to enable irq preemption

### Fixed:
  - freertos: disable irq preemption

## [0.7.1] - 2022-02-13:

All changes since 0.7.0

### Changed:
  - drivers: adc12: update adc12_prd_config_t
  - samples: can: update case with interrupt and communication between two boards

### Fixed:
  - drivers: can: fix blocking transcation issue
  - samples: mbx: support run this example in SES
  - SES: startup: add fpu enable if abi is set to enable hw fp

### Added:
  - samples: multicore: add flash based multicore example
  - drivers: can: add apis to recvieve message for non-blocking use

## [0.7.0] - 2022-01-30:

All changes since 0.6.2

### Changed:
  - update default CPU frequency to 816MHz from 648MHz
  - update the ip headers
  - drivers: gpio: replace gpio_XXX_pins with gpio_XXX_port
  - drivers: gpio: remove pin level enum definition
  - drivers: i2s: driver update to remove mclk_div
  - drivers: ptpc: update driver
  - drivers: common: update get first set bit API
  - drivers: uart: split one enable with parameter into enable and disable interfaces
  - drivers: pwm: change name of output_channel config API
  - drivers: trgm: split separate API to enable/disable io output
  - soc: HPM6750: initialize noncacheable data in startup
  - soc: HPM6750: l1c: update fence.i call
  - samples: hello_world: add LED flashing
  - samples: littlevgl: remove lvgl example

### Fixed:
  - hpm6750evkmini: correct refresh cycle number of sdram
  - hpm6750evkmini: Fix the SDRAM memory range issue in flash_sdram_xip linker file
  - SES: remove no_relax option for linker, since segger has provide a patch to its ld for ses v6.10.
  - drivers: gpio: fix read pin issue:
  - drivers: usb: fix usb disconnection under linux environment
  - drivers: sdxc: Fixed the compatibility issue on different SD/eMMC cards in the sdcard_fatfs demo
  - drivers: gptmr: incorrect DMAEN configuration condition
  - drivers: gptmr: clear CNTRST bit after set.
  - SDK_DECLARE_EXT_ISR_M cannot work in the c++ file
  - FreeRTOS: fix ISR_STACK setting
  - components: touch: gt911: fix gpio write pin call

### Added:
  - SEG: add register definition file in generated embedded studio project
  - samples: drivers: gpiom: Add example to demonstrate gpiom's function
  - drivers: common: add macro to put data into noncacheable sections
  - middleware: integrate lwip

