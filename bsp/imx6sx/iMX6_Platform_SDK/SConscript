from building import *

cwd = GetCurrentDir()

# sdk/utility/src/runtime_support.c
# sdk/drivers/keypad/src/keypad_port.c
# sdk/drivers/snvs/src/snvs.c
# sdk/core/src/interrupt.c

src = Split('''
board/common/board_network.c
board/common/board_io_expanders.c
board/common/hardware_modules.c
apps/common/platform_init.c
apps/common/print_version.c
sdk/utility/src/sdk_version.c
sdk/utility/src/text_color.c
sdk/utility/src/menu.c
sdk/utility/src/spinlock.c
sdk/utility/src/system_util.c
sdk/core/src/ccm_pll.c
sdk/core/src/abort_handler.c
sdk/core/src/mmu.c
sdk/core/src/armv7_cache.c
sdk/core/src/gic.c
sdk/common/ioexpander/src/max7310.c
sdk/common/pmic/pfuse/pf0100.c
sdk/common/profile/profile.c
sdk/drivers/hdmi/src/hdmi_tx.c
sdk/drivers/hdmi/src/hdmi_tx_audio.c
sdk/drivers/hdmi/src/hdmi_common.c
sdk/drivers/hdmi/src/hdmi_tx_phy.c
sdk/drivers/vdoa/src/vdoa.c
sdk/drivers/i2c/src/software_i2c_port.cpp
sdk/drivers/i2c/src/imx_i2c_slave.c
sdk/drivers/i2c/src/i2c_device.cpp
sdk/drivers/i2c/src/imx_i2c.c
sdk/drivers/pmu/src/pmu_driver.cpp
sdk/drivers/sdma/src/sdma.c
sdk/drivers/sdma/src/sdma_script_info.c
sdk/drivers/eim/src/eim.c
sdk/drivers/timer/src/epit.c
sdk/drivers/timer/src/gpt.c
sdk/drivers/timer/src/timer.c
sdk/drivers/ipu/src/ipu_ic.c
sdk/drivers/ipu/src/ips_disp_panel.c
sdk/drivers/ipu/src/ipu_csi.c
sdk/drivers/ipu/src/ipu_dmfc.c
sdk/drivers/ipu/src/ipu_di.c
sdk/drivers/ipu/src/ipu_vdi.c
sdk/drivers/ipu/src/ipu_dc.c
sdk/drivers/ipu/src/ipu_idmac.c
sdk/drivers/ipu/src/ipu_dp.c
sdk/drivers/ipu/src/ipu_common.c
sdk/drivers/pcie/src/pcie_phy.c
sdk/drivers/pcie/src/pcie.c
sdk/drivers/pcie/src/pcie_prot.c
sdk/drivers/gpio/src/gpio.c
sdk/drivers/gpio/src/gpio_pin.cpp
sdk/drivers/gpio/src/imx6sdl_gpio_map.c
sdk/drivers/ocotp/src/ocotp.c
sdk/drivers/usb/src/mx6x_usb.c
sdk/drivers/usb/src/usb_common.c
sdk/drivers/usb/src/usbd_drv.c
sdk/drivers/usb/src/usbh_drv.c
sdk/drivers/caam/src/caam.c
sdk/drivers/uart/src/imx_uart.c
sdk/drivers/enet/src/enet_drv.c
sdk/drivers/tempmon/src/tempmon.c
sdk/drivers/epdc/src/mxc_epdc.c
sdk/drivers/cpu_utility/src/cpu_workpoint.c
sdk/drivers/cpu_utility/src/cpu_multicore.c
sdk/drivers/cpu_utility/src/cpu_get_cores.c
sdk/drivers/gpmi/src/gpmi_dma_components.cpp
sdk/drivers/gpmi/src/gpmi_dma_sequences.cpp
sdk/drivers/gpmi/src/bch_ecc.c
sdk/drivers/gpmi/src/gpmi_dma_isr.cpp
sdk/drivers/gpmi/src/gpmi_nand_operations.cpp
sdk/drivers/gpmi/src/gpmi.cpp
sdk/drivers/board_id/src/board_id.c
sdk/drivers/audio/src/imx_esai.c
sdk/drivers/audio/src/snd_card.c
sdk/drivers/audio/src/wm8958_dac.c
sdk/drivers/audio/src/imx-ssi.c
sdk/drivers/audio/src/imx_audmux.c
sdk/drivers/audio/src/sgtl5000.c
sdk/drivers/audio/src/imx_spdif.c
sdk/drivers/audio/src/cs42888.c
sdk/drivers/audio/src/wm8962.c
sdk/drivers/ldb/src/ldb.c
sdk/drivers/spi/src/ecspi.c
sdk/drivers/spi/src/spi_device.cpp
sdk/drivers/accelerometer/src/mma8451.c
sdk/drivers/usdhc/src/usdhc_sd.c
sdk/drivers/usdhc/src/usdhc_host.c
sdk/drivers/usdhc/src/usdhc_mmc.c
sdk/drivers/usdhc/src/usdhc.c
sdk/drivers/pwm/src/pwm.c
sdk/drivers/video/src/adv7180.c
sdk/drivers/rtc/src/rtc.c
sdk/drivers/rtc/src/srtc.c
sdk/drivers/flexcan/src/can.c
''')

CPPPATH = [
cwd + '/board/common',
cwd + '/board/mx6sdl/sabre_ai',
cwd + '/board/mx6sdl/sabre_ai/rev_b_iomux',
cwd + '/sdk',
cwd + '/sdk/common',
cwd + '/sdk/core',
cwd + '/sdk/drivers',
cwd + '/sdk/utility',
cwd + '/sdk/include',
cwd + '/sdk/include/mx6sdl',
cwd + '/sdk/include/mx6sdl/registers'
]

CPPDEFINES = ['CHIP_MX6SDL', 'BOARD_SABRE_AI', 'BOARD_REV_B']

group = DefineGroup('PlatformSDK', src, depend = [''], CPPPATH = CPPPATH, CPPDEFINES = CPPDEFINES)

Return('group')
