#-------------------------------------------------------------------------------
# Copyright (C) 2012-2013 Freescale Semiconductor, Inc. All Rights Reserved.
#
# THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
# SHALL FREESCALE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
# OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
# OF SUCH DAMAGE.
#-------------------------------------------------------------------------------
include $(SDK_ROOT)/mk/common.mk


# Determine if the target is either the MX6DQ or MX6SDL.
ifeq "$(TARGET)" "mx6dq"
is_dq_or_sdl = 1
endif
ifeq "$(TARGET)" "mx6sdl"
is_dq_or_sdl = 1
is_sdl_or_sl = 1
endif
ifeq "$(TARGET)" "mx6sl"
is_sdl_or_sl = 1
endif

define SOURCES
accelerometer/src/mma8451.c
board_id/src/board_id.c
camera/src/camera_profile.c
cpu_utility/src/cpu_get_cores.c
cpu_utility/src/cpu_workpoint.c
cpu_utility/src/cpu_multicore.c
eim/src/eim.c
gpio/src/gpio.c
gpio/src/gpio_pin.cpp
i2c/src/imx_i2c_slave.c
i2c/src/imx_i2c.c
i2c/src/i2c_device.cpp
i2c/src/software_i2c_port.cpp
keypad/src/keypad_port.c
ocotp/src/ocotp.c
pmu/src/pmu_driver.cpp
pwm/src/pwm.c
rtc/src/rtc.c
rtc/src/srtc.c
sdma/src/sdma_script_info.c
sdma/src/sdma.c
snvs/src/snvs.c
spi/src/ecspi.c
spi/src/spi_device.cpp
tempmon/src/tempmon.c
timer/src/epit.c
timer/src/gpt.c
timer/src/timer.c
uart/src/imx_uart.c
usb/src/mx6x_usb.c
usb/src/usb_common.c
usb/src/usbd_drv.c
usb/src/usbh_drv.c
usdhc/src/usdhc_host.c
usdhc/src/usdhc_mmc.c
usdhc/src/usdhc_sd.c
usdhc/src/usdhc.c
audio/src/cs42888.c 
audio/src/imx_audmux.c 
audio/src/imx_spdif.c 
audio/src/imx-ssi.c 
audio/src/snd_card.c 
audio/src/wm8962.c 
endef

# Only the MX6DQ has SATA.
ifeq "$(TARGET)" "mx6dq"
SOURCES += sata/src/sata.c
endif

# only for MX6SDL and MX6SL
ifdef is_sdl_or_sl
SOURCES += epdc/src/mxc_epdc.c
endif

# Add drivers that are only available of mx6dq or mx6sdl.
ifdef is_dq_or_sdl
SOURCES += \
	audio/src/wm8958_dac.c \
	audio/src/sgtl5000.c \
	audio/src/imx_esai.c \
    caam/src/caam.c \
    camera/src/smd_sensor.c \
	enet/src/enet_drv.c \
	flexcan/src/can.c \
	gpmi/src/bch_ecc.c \
	gpmi/src/gpmi_dma_components.cpp \
	gpmi/src/gpmi_dma_isr.cpp \
	gpmi/src/gpmi_dma_sequences.cpp \
	gpmi/src/gpmi_nand_operations.cpp \
	gpmi/src/gpmi.cpp \
	hdmi/src/hdmi_common.c \
	hdmi/src/hdmi_tx_audio.c \
	hdmi/src/hdmi_tx_phy.c \
	hdmi/src/hdmi_tx.c \
	ipu/src/ips_disp_panel.c \
	ipu/src/ipu_common.c \
	ipu/src/ipu_csi.c \
	ipu/src/ipu_vdi.c \
	ipu/src/ipu_dc.c \
	ipu/src/ipu_di.c \
	ipu/src/ipu_dmfc.c \
	ipu/src/ipu_dp.c \
	ipu/src/ipu_ic.c \
	ipu/src/ipu_idmac.c \
	ldb/src/ldb.c \
	mipi/src/mipi_csi2_common.c \
	mipi/src/mipi_dsi_common.c \
	mipi/src/ov5640_mipi_fm.c \
	pcie/src/pcie_phy.c \
	pcie/src/pcie_prot.c \
	pcie/src/pcie.c \
	vdoa/src/vdoa.c \
	video/src/adv7180.c \
	vpu/src/vpu_gdi.c \
	vpu/src/vpu_io.c \
	vpu/src/vpu_lib.c \
	vpu/src/vpu_util.c
else
SOURCES += \
	lcdif/src/lcdif_drv.c \
	lcdif/src/pxp_drv.c \
	spdc/src/mxc_spdc.c \
	camera/src/smd_sensor.c \
	camera/src/csi_drv.c \
	fec/src/fec_drv.c
endif

ifeq "$(TARGET)" "mx6sl"
SOURCES += \
	dcp/src/dcp.c
endif

# Select the GPIO map source file based on chip.
ifeq "$(TARGET)" "mx6dq"
SOURCES += gpio/src/imx6dq_gpio_map.c
else ifeq "$(TARGET)" "mx6sdl"
SOURCES += gpio/src/imx6sdl_gpio_map.c
else ifeq "$(TARGET)" "mx6sl"
SOURCES += gpio/src/imx6sl_gpio_map.c
endif


include $(SDK_ROOT)/mk/targets.mk
