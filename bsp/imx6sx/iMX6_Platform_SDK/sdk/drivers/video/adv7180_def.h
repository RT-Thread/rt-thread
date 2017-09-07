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
 * @file adv7180_def.h
 * @brief common macro and data structre defination of camera.
 * @ingroup diag_adv7180
 */

#ifndef __ADV7180_DEF_H__
#define __ADV7180_DEF_H__

#include "i2c/imx_i2c.h"
#include "sdk_types.h"

//! @addtogroup diag_adv7180

//! @{

//! @brief ADV7180 video signal mode
typedef enum {
	ADV7180_NTSC = 0,	//!< Locked on (M) NTSC video signal.
	ADV7180_PAL = 1,	//!< (B, G, H, I, N)PAL video signal.
	ADV7180_NOT_LOCKED,	//!< Not locked on a signal.
} video_fmt_idx;

//! @brief Video format structure.
typedef struct {
	int32_t fmt_id;			//!< Video for linux ID.
	char name[16];			//!< Name (e.g., "NTSC", "PAL", etc.)
	uint16_t raw_width;		//!< Raw width.
	uint16_t raw_height;	//!< Raw height.
	uint16_t active_width;	//!< Active width.
	uint16_t active_height;	//!< Active height.
} video_fmt_t;


//! @brief The common structure for accessing adv7180 I2C interface.
typedef struct {
    uint8_t addr;	//!< adv7180 register address
    uint8_t value;	//!< value along with the register address
} t_adv7180_i2c_reg_param;

#define IF_NAME                    "adv7180"
#define ADV7180_INPUT_CTL              0x00	/* Input Control */
#define ADV7180_STATUS_1               0x10	/* Status #1 */
#define ADV7180_STATUS_3               0x13	/* Status #3 */
#define ADV7180_BRIGHTNESS             0x0a	/* Brightness */
#define ADV7180_IDENT                  0x11	/* IDENT */
#define ADV7180_VSYNC_FIELD_CTL_1      0x31	/* VSYNC Field Control #1 */
#define ADV7180_MANUAL_WIN_CTL         0x3d	/* Manual Window Control */
#define ADV7180_SD_SATURATION_CB       0xe3	/* SD Saturation Cb */
#define ADV7180_SD_SATURATION_CR       0xe4	/* SD Saturation Cr */
#define ADV7180_PWR_MNG                0x0f     /* Power Management */

#define ADV7180_INPUT_CONTROL_REG			0x00
#define ADV7180_INPUT_CONTROL_AD_PAL_BG_NTSC_J_SECAM	0x00
#define ADV7180_INPUT_CONTROL_AD_PAL_BG_NTSC_J_SECAM_PED 0x10
#define ADV7180_INPUT_CONTROL_AD_PAL_N_NTSC_J_SECAM	0x20
#define ADV7180_INPUT_CONTROL_AD_PAL_N_NTSC_M_SECAM	0x30
#define ADV7180_INPUT_CONTROL_NTSC_J			0x40
#define ADV7180_INPUT_CONTROL_NTSC_M			0x50
#define ADV7180_INPUT_CONTROL_PAL60			0x60
#define ADV7180_INPUT_CONTROL_NTSC_443			0x70
#define ADV7180_INPUT_CONTROL_PAL_BG			0x80
#define ADV7180_INPUT_CONTROL_PAL_N			0x90
#define ADV7180_INPUT_CONTROL_PAL_M			0xa0
#define ADV7180_INPUT_CONTROL_PAL_M_PED			0xb0
#define ADV7180_INPUT_CONTROL_PAL_COMB_N		0xc0
#define ADV7180_INPUT_CONTROL_PAL_COMB_N_PED		0xd0
#define ADV7180_INPUT_CONTROL_PAL_SECAM			0xe0
#define ADV7180_INPUT_CONTROL_PAL_SECAM_PED		0xf0

#define ADV7180_EXTENDED_OUTPUT_CONTROL_REG		0x04
#define ADV7180_EXTENDED_OUTPUT_CONTROL_NTSCDIS		0xC5

#define ADV7180_AUTODETECT_ENABLE_REG			0x07
#define ADV7180_AUTODETECT_DEFAULT			0x7f

#define ADV7180_ADI_CTRL_REG				0x0e
#define ADV7180_ADI_CTRL_IRQ_SPACE			0x20

#define ADV7180_STATUS1_REG				0x10
#define ADV7180_STATUS1_IN_LOCK		0x01
#define ADV7180_STATUS1_AUTOD_MASK	0x70
#define ADV7180_STATUS1_AUTOD_NTSM_M_J	0x00
#define ADV7180_STATUS1_AUTOD_NTSC_4_43 0x10
#define ADV7180_STATUS1_AUTOD_PAL_M	0x20
#define ADV7180_STATUS1_AUTOD_PAL_60	0x30
#define ADV7180_STATUS1_AUTOD_PAL_B_G	0x40
#define ADV7180_STATUS1_AUTOD_SECAM	0x50
#define ADV7180_STATUS1_AUTOD_PAL_COMB	0x60
#define ADV7180_STATUS1_AUTOD_SECAM_525	0x70

#define ADV7180_IDENT_REG 0x11
#define ADV7180_ID_7180 0x18

#define ADV7180_ICONF1_ADI		0x40
#define ADV7180_ICONF1_ACTIVE_LOW	0x01
#define ADV7180_ICONF1_PSYNC_ONLY	0x10
#define ADV7180_ICONF1_ACTIVE_TO_CLR	0xC0

#define ADV7180_IRQ1_LOCK	0x01
#define ADV7180_IRQ1_UNLOCK	0x02
#define ADV7180_ISR1_ADI	0x42
#define ADV7180_ICR1_ADI	0x43
#define ADV7180_IMR1_ADI	0x44
#define ADV7180_IMR2_ADI	0x48
#define ADV7180_IRQ3_AD_CHANGE	0x08
#define ADV7180_ISR3_ADI	0x4A
#define ADV7180_ICR3_ADI	0x4B
#define ADV7180_IMR3_ADI	0x4C
#define ADV7180_IMR4_ADI	0x50


//! @brief The I2C port number to which the adv7180 is connected.
//!
//! This global must be provided by the board library or application.
extern const i2c_device_info_t g_adv7180_i2c_device;

extern video_fmt_t video_fmts[];

//! @name Board support functions
//!
//! These functions are called by the driver in order to factor out board
//! specific functionality. They must be defined by the board support
//! library or the application.
//@{

/*!
 * @brief IOMUX configuration for CSI port0
 */
void csi_port0_iomux_config(void);

//@}

//! @name ADV7810 API
//@{

/*!
 * @brief Hardware and software initialize adv7180
 *
 * @return 0 on success; non-zero otherwise
 */
extern int32_t adv7180_init(void);

/*!
 * @brief Get adv7180 video format
 *
 * @return ADV7180_NTSC when the video input is NTSC, ADV7180_PAL(1) when the video input is PAL; ADV7180_NOT_LOCKED otherwise
 */
extern int32_t adv7180_get_std(void);

/*!
 * @brief Check if video format is in a interlaced mode
 *
 * @return 1 for interlaced mode, 0 for progressive mode
 */
extern int32_t adv7180_is_interlaced_mode(void);

//@}

//! @}

#endif
