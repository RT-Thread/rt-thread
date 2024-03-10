/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file  mipi_common.h
 * @brief mipi common definitions.
 *
 * @ingroup diag_mipi
 */

#ifndef _MIPI_COMMON_H_
#define _MIPI_COMMON_H_
/* Standard testbench defines files */
#include "i2c/imx_i2c.h"
#include "sdk.h"
#include <math.h>

#define DPI_MODE 1
#define IO_EXPANDER_ADDR    (0x1b)
#define MIPI_CSI_ADDR       (0x3c)  //for 5640//78

///////////////////////////////////////////////////////////////////////
////////DSI LINK DEFINITION////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define     CLKLANEBYTEPERIOD   10  //since we are using 800Mbps phy, the DSI controller working at 100Hz
#define     NUMBEROFLANES       1   //2 Data Lanes
#define 	DSI_CLK_DIV		0x107

//////////////////////////////////////////////////////////////////////
////////VIDEO DEFINITION--480x800 period 25///////////////////////////
////////////////////////////////////////////////////////////////////////
/*All these parameters are from the LCD spec*/
#define     DPITHSA             8   //hsync valid witdh
#define     DPITHBP             8   //Horizontal Back Porch
#define     DPITHACT            480 //Horizontal active pixel
#define     DPITHFP             8   //Horizontal Front Porch
#define     DPIVSALINES         4   //Vertical Synchronization witdth
#define     DPIVBPLINES         4   //Vertical Back Porch
#define     DPIVACTLINES        800 //Vertical active lines
#define     DPIVFPLINES         4   //Vertical Front Porch

#define     DPIVCHANNELID       0   //Configures the DPI Virtual Channel ID that is indexed to the Video mode packets.
#define     DPICOLORMODE        7   //DPI color coding. 0: 16bit config1; 1: 16bit config2; 2: 16bit config3; 3: 18bit config1; 4: 18bit config2; 5 to 7: 24 bit
#define     DPIDATENACTLOW      1   //Set to configure Data enable pin (dpidaten) as Active low.
#define     DPIVSYNCACTLOW      1   //Set to configure Vertical Synchronism pin (dpivsync) as Active low.
#define     DPIHSYNCACTLOW      1   //Set to configure Horizontal Synchronism pin (dpihsync) as Active low.
#define     DPICOLRMACTLOW      0   //Set to configure Shut Down pin (dpishutdn) as Active low.
#define     DPISHTDMACTLOW      0   //Set to configure Color Mode pin (dpicolcorm) as Active low
#define     ENABLE18BPPLOOSELY  0   //When in 18 bit video mode this enable the 18 bit loosely packed pixel stream

////////////////////////////////////////////////////////////////////////
/////////////////////PACKET HANDLER DEFINITION//////////////////////////
////////////////////////////////////////////////////////////////////////
#define     EOTPGENERATION       1  //Enables the generation of EOTpacket before going to Low POWER
#define     EOTPRECEPTION        0  //Programs the Core to expect for EOTpackets when transmission are received
#define     BTA_ENABLE           1  //Enables Bus Turn-Around request.
#define     EN_ECC_RX            1  //Enables ECC reception, error correction and reporting.
#define     EN_CRC_RX            1  //Enables CRC reception and error reporting
#define     EN_VID_RX            1  //Generic interface read-back Virtual Channel identification
#define     VIDEO_MODE_ENABLE    1
#define     COMMAND_MODE_ENABLE  0
#define     VID_MODE_EN          1  //Enables DPI Video mode transmission.
#define     VIDEO_MODE           3  //0-syncro w/ sync pulses; 1-synchro w/ sync events; 2,3-synchro w/ sync events
#define     LP_VSA_EN            1  //Enables the LOW power transition when in Vertical Sync Active Region
#define     LP_VBP_EN            1  //Enables the LOW power transition when in Vertical Back Porch Region
#define     LP_VFP_EN            1  //Enables the LOW power transition when in Vertical Front Porch Region
#define     LP_VACT_EN           1  //Enables the LOW power transition when in Vertical Active Line Region
#define     LP_HBP_EN            1  //Enables the LOW power transition when in Horizontal Back Porch Region
#define     LP_HFP_EN            1  //Enables the LOW power transition when in Horizontal Front Porch Region
#define     ENABLE_MULT_PKTS     0  //if there is no active video time overhead or in burst mode shoudl be set 0
#define     ENABLE_NULL_PKTS     0  //if there is no active video time overhead or in burst mode shoudl be set 0
#define     BAT_ACK_EN           0  //Enables the request for an acknowledge response at the end of a frame.
#define     BTA_MAX_TIME         0xd00
#define     PHY_LP_TO_HS         0x40
#define     PHY_HS_TO_LP         0x40

#define     GEN_SW_0P_LP_ENA     1
#define     GEN_SW_1P_LP_ENA     1
#define     GEN_SW_2P_LP_ENA     1
#define     GEN_SR_0P_LP_ENA     1
#define     GEN_SR_1P_LP_ENA     1
#define     GEN_SR_2P_LP_ENA     1
#define     DSC_SW_0P_LP_ENA     1
#define     DSC_SW_1P_LP_ENA     1
#define     DSC_SR_0P_LP_ENA     1
#define     MAX_READ_PACKET_SIZE 1
#define     GEN_LW_LP_ENA        0
#define     DCS_LW_LP_ENA        1
#define     ACK_REQUEST_ENABLE   0
#define     TEAR_FX_ENABLE       0
#define     PHY_STOP_WAIT_TIME   0x10
#define     TXREQESTCLKHS        1
#define     TXREQULPSCLK         0
#define     TXEXITULPSCLK        0
#define     TXREQULPSLAN         0
#define     TXEXITULPSLAN        0
#define     TXTRIGGERS           0

////////////////////////////////////////////////////////////////////////
/////////////////////DBI INTEFACE DEFINITION////////////////////////////
////////////////////////////////////////////////////////////////////////
#define     DBIVCHANNELID        0  //;
#define     DBIIFCONFIG          0x0b   //16bit interface 8bpp color mode
#define     DBIWRITEMAXSIZE      0x49   //;
#define     DBILUTSIZECFG        1  //;//LUT size 0-48bytes; 1-128bytes; 2-192bytes; 3-48bytes
#define     DBIOUTPARTIENA       1  //;
#define     DBIWRITECOMSIZE      0x091  //;
#define     PIXELS_PER_PACKET   480
#define     NUMBER_OF_CHUNKS    0x08
#define     NULL_PKT_SIZE       0x08

////////////////////////////////////////////////////////////////////////
//////////Video mode calc parames///////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#define     DPI2BYTECLKRATIO    DPI2LANECLKRATIO*NUMBEROFLANES  // The ratio of byte clocks per pixel clock
#define     CLKMGR_CFG          0x00
#define     DPI_CFG             (DPIVCHANNELID)|(DPICOLORMODE<<2)|(DPIDATENACTLOW<<5)| \
                                (DPIVSYNCACTLOW<<6)|(DPIHSYNCACTLOW<<7)|(DPICOLRMACTLOW<<8)|(DPISHTDMACTLOW<<9)|\
                                (ENABLE18BPPLOOSELY<<10)
#define     DBI_CFG             (DBIVCHANNELID)|(DBIIFCONFIG<<2)|(DBILUTSIZECFG<<6)|(DBIOUTPARTIENA<<8)|(DBIIFCONFIG<<9)
#define     DBI_CMD_CTRL        (DBIWRITECOMSIZE+1)|(DBIWRITEMAXSIZE<<16)
#define     PCKHDL_CFG          (EOTPGENERATION)|(EOTPRECEPTION<<1)|(BTA_ENABLE<<2)|(EN_ECC_RX<<3)|(EN_CRC_RX<<4)|(EN_VID_RX<<5)
#define     VID_MODE_CFG        (VID_MODE_EN)|(VIDEO_MODE<<1)|(LP_VSA_EN<<3)|(LP_VBP_EN<<4)| \
                                (LP_VFP_EN<<5)|(LP_VACT_EN<<6)|(LP_HBP_EN<<7)|(LP_HFP_EN<<8)| \
                                (ENABLE_MULT_PKTS<<9)|(ENABLE_NULL_PKTS<<10)|(BAT_ACK_EN<<11)
#define     VID_PKT_CFG         (PIXELS_PER_PACKET)|(NUMBER_OF_CHUNKS<<11)|(NULL_PKT_SIZE<<21)
#define     COMMAND_MODE_CFG    (COMMAND_MODE_ENABLE)|(GEN_SW_0P_LP_ENA<<1)|(GEN_SW_1P_LP_ENA<<2)| \
                                (GEN_SW_2P_LP_ENA<<3)|(GEN_SR_0P_LP_ENA<<4)|(GEN_SR_1P_LP_ENA<<5)| \
                                (GEN_SR_2P_LP_ENA<<6)|(DSC_SW_0P_LP_ENA<<7)|(DSC_SW_1P_LP_ENA<<8)| \
                                (DSC_SR_0P_LP_ENA<<9)|(MAX_READ_PACKET_SIZE<<10)|(GEN_LW_LP_ENA<<11)| \
                                (DCS_LW_LP_ENA<<12)|(ACK_REQUEST_ENABLE<<13)|(TEAR_FX_ENABLE<<14)
#define     TMR_LINE_CFG        (THSA)|(THBP<<9)|(THLINE<<18)
#define     VTIMING_CFG         (DPIVSALINES)|(DPIVBPLINES<<4)|(DPIVFPLINES<<10)|(DPIVACTLINES<<16)
#define     PHY_TIMING_CFG      (BTA_MAX_TIME)|(PHY_LP_TO_HS<<12)|(PHY_HS_TO_LP<<20)
#define     PHY_IF_CFG          (NUMBEROFLANES-1)|(PHY_STOP_WAIT_TIME<<2)
#define     PWR_UP              1
#define     PHYRSTZ             7
#define     PHY_IF_CTRL         (TXREQESTCLKHS)|(TXREQULPSCLK<<1)|(TXREQULPSLAN<<2)|(TXEXITULPSLAN<<3)|(TXTRIGGERS<<4)
#define     DBI_CONFIG_VALUE                        0xc0895e81%5

#define    HSI_MEM_BASE_ADDRESS                    MMDC1_ARB_BASE_ADDR

/* MIPI DSI Processor-to-Peripheral transaction types */
enum {
	MIPI_DSI_V_SYNC_START				= 0x01,
	MIPI_DSI_V_SYNC_END				= 0x11,
	MIPI_DSI_H_SYNC_START				= 0x21,
	MIPI_DSI_H_SYNC_END				= 0x31,

	MIPI_DSI_COLOR_MODE_OFF				= 0x02,
	MIPI_DSI_COLOR_MODE_ON				= 0x12,
	MIPI_DSI_SHUTDOWN_PERIPHERAL			= 0x22,
	MIPI_DSI_TURN_ON_PERIPHERAL			= 0x32,

	MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM		= 0x03,
	MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM		= 0x13,
	MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM		= 0x23,

	MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM		= 0x04,
	MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM		= 0x14,
	MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM		= 0x24,

	MIPI_DSI_DCS_SHORT_WRITE			= 0x05,
	MIPI_DSI_DCS_SHORT_WRITE_PARAM			= 0x15,

	MIPI_DSI_DCS_READ				= 0x06,

	MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE		= 0x37,

	MIPI_DSI_END_OF_TRANSMISSION			= 0x08,

	MIPI_DSI_NULL_PACKET				= 0x09,
	MIPI_DSI_BLANKING_PACKET			= 0x19,
	MIPI_DSI_GENERIC_LONG_WRITE			= 0x29,
	MIPI_DSI_DCS_LONG_WRITE				= 0x39,

	MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20	= 0x0c,
	MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24		= 0x1c,
	MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16		= 0x2c,

	MIPI_DSI_PACKED_PIXEL_STREAM_30			= 0x0d,
	MIPI_DSI_PACKED_PIXEL_STREAM_36			= 0x1d,
	MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12		= 0x3d,

	MIPI_DSI_PACKED_PIXEL_STREAM_16			= 0x0e,
	MIPI_DSI_PACKED_PIXEL_STREAM_18			= 0x1e,
	MIPI_DSI_PIXEL_STREAM_3BYTE_18			= 0x2e,
	MIPI_DSI_PACKED_PIXEL_STREAM_24			= 0x3e,
};

/* MIPI DCS commands */
enum {
	MIPI_DCS_NOP			= 0x00,
	MIPI_DCS_SOFT_RESET		= 0x01,
	MIPI_DCS_GET_DISPLAY_ID		= 0x04,
	MIPI_DCS_GET_RED_CHANNEL	= 0x06,
	MIPI_DCS_GET_GREEN_CHANNEL	= 0x07,
	MIPI_DCS_GET_BLUE_CHANNEL	= 0x08,
	MIPI_DCS_GET_DISPLAY_STATUS	= 0x09,
	MIPI_DCS_GET_POWER_MODE		= 0x0A,
	MIPI_DCS_GET_ADDRESS_MODE	= 0x0B,
	MIPI_DCS_GET_PIXEL_FORMAT	= 0x0C,
	MIPI_DCS_GET_DISPLAY_MODE	= 0x0D,
	MIPI_DCS_GET_SIGNAL_MODE	= 0x0E,
	MIPI_DCS_GET_DIAGNOSTIC_RESULT	= 0x0F,
	MIPI_DCS_ENTER_SLEEP_MODE	= 0x10,
	MIPI_DCS_EXIT_SLEEP_MODE	= 0x11,
	MIPI_DCS_ENTER_PARTIAL_MODE	= 0x12,
	MIPI_DCS_ENTER_NORMAL_MODE	= 0x13,
	MIPI_DCS_EXIT_INVERT_MODE	= 0x20,
	MIPI_DCS_ENTER_INVERT_MODE	= 0x21,
	MIPI_DCS_SET_GAMMA_CURVE	= 0x26,
	MIPI_DCS_SET_DISPLAY_OFF	= 0x28,
	MIPI_DCS_SET_DISPLAY_ON		= 0x29,
	MIPI_DCS_SET_COLUMN_ADDRESS	= 0x2A,
	MIPI_DCS_SET_PAGE_ADDRESS	= 0x2B,
	MIPI_DCS_WRITE_MEMORY_START	= 0x2C,
	MIPI_DCS_WRITE_LUT		= 0x2D,
	MIPI_DCS_READ_MEMORY_START	= 0x2E,
	MIPI_DCS_SET_PARTIAL_AREA	= 0x30,
	MIPI_DCS_SET_SCROLL_AREA	= 0x33,
	MIPI_DCS_SET_TEAR_OFF		= 0x34,
	MIPI_DCS_SET_TEAR_ON		= 0x35,
	MIPI_DCS_SET_ADDRESS_MODE	= 0x36,
	MIPI_DCS_SET_SCROLL_START	= 0x37,
	MIPI_DCS_EXIT_IDLE_MODE		= 0x38,
	MIPI_DCS_ENTER_IDLE_MODE	= 0x39,
	MIPI_DCS_SET_PIXEL_FORMAT	= 0x3A,
	MIPI_DCS_WRITE_MEMORY_CONTINUE	= 0x3C,
	MIPI_DCS_READ_MEMORY_CONTINUE	= 0x3E,
	MIPI_DCS_SET_TEAR_SCANLINE	= 0x44,
	MIPI_DCS_GET_SCANLINE		= 0x45,
	MIPI_DCS_READ_DDB_START		= 0xA1,
	MIPI_DCS_READ_DDB_CONTINUE	= 0xA8,
};

//! @brief The common structure for accessing mipi sensor I2C interface.
//!
//! @a address is a 16-bit sensor register address.
typedef struct {
    unsigned short addr;	//!< Sensor register address.
    unsigned short value;	//!< Data along with the register address.
    unsigned char verify;	//!< If need to verify the write operation is correctly.
    unsigned int delay_us;	//!< Time delay needed after setting regiter, the unit is us.
} cam_firmware_t;

//! @brief The register setting information for specific mipi camera mode
//!
//! When the mipi camera need to work at specific mode, a serie of regiter settings are need to be downloaded to sensor.
//
//!	The register setting should be hold in array.
//
//! @a setting is the start address of the register setting array.
//! @a size if the size of the register setting array.
typedef struct {
    cam_firmware_t *setting;	//!< Pointer to register setting array
    int size;					//!< Size of register setting array
} mipi_cam_mode_t;

//! @brief MIPI sensor capture mode id
//!
//! The mode id is corresponding to index of @a mipi_camera_modes array.
enum {
    OV5640_MODE_480X480_15FPS_RGB565,
    OV5640_MODE_VGA_640X480_15FPS_YUV422,
    OV5640_MODE_VGA_640X480_30FPS_YUV422,
};

extern cam_firmware_t ov5640_mipi_480x480_30fps_RGB565_fm[];
extern cam_firmware_t ov5640_mipi_VGA_640x480_15fps_YUV422_fm[];
extern cam_firmware_t ov5640_mipi_VGA_640x480_30fps_YUV422_fm[];

extern mipi_cam_mode_t mipi_cam_modes[];

/*!
 * @brief Set mipi sensor input clock
 *
 * MIPI sensor input clock comes from IPU. A typical camera sensor clock is 24MHz.
 *
 */
void mipi_csi2_clock_set(void);

/*!
 * @brief Provide the mipi camera power and reset
 */
void mipi_cam_power_on(void);

/*!
 * @brief Initialize and setup mipi csi interface.
 *
 * Setup MIPI-CSI2 controller and mipi sensor according to recommended sequences.
 *
 */
void mipi_csi2_config(void);

/*!
 * @brief Initialize mipi dsi interface.
 *
 * Setup MIPI DSI controller and the TRULY panel through
 * generic data interface.
 *
 */
void mipi_dsi_init(void);
#endif
