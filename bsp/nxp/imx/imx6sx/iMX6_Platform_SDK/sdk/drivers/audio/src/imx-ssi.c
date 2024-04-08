/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
 * @file imx-ssi.c
 * @brief SSI driver.
 *
 *  * @ingroup diag_audio
 */

#include <stdio.h>
#include "sdk.h"
#include "audio/audio.h"
#include "imx-ssi.h"
#include "registers/regsssi.h"

#define SSI_DEBUG 0
#define SSI_READ_TIMEOUT      0x400000
#define SSI_WRITE_TIMEOUT     0x400000

#if SSI_DEBUG
#define D(fmt,args...) printf(fmt, ## args)
#else
#define D(fmt,args...)
#endif

//! Default tx/rx watermakr
#define SSI_SFCSR_TX_WATERMARK      4   // Default 4
#define SSI_SFCSR_RX_WATERMARK      4   // Default 4

//! Default values for SSI registers
#define SSI_SCR_RESET_VAL	0x00000000
#define SSI_SISR_RESET_VAL      0x00003003
#define SSI_SIER_RESET_VAL      0x00003003
#define SSI_STCR_RESET_VAL      0x00000200
#define SSI_SRCR_RESET_VAL      0x00000200
#define SSI_STCCR_RESET_VAL	0x00040000
#define SSI_SRCCR_RESET_VAL	0x00040000
#define SSI_SFCSR_RESET_VAL	0x00810081
#define SSI_SACNT_RESET_VAL	0x00000000
#define SSI_SACADD_RESET_VAL	0x00000000
#define SSI_SACDAT_RESET_VAL	0x00000000
#define SSI_SATAG_RESET_VAL	0x00000000
#define SSI_STMSK_RESET_VAL	0x00000000
#define SSI_SRMSK_RESET_VAL	0x00000000
#define SSI_SACCST_RESET_VAL	0x00000000
#define SSI_SACCEN_RESET_VAL	0x00000000
#define SSI_SACCDIS_RESET_VAL	0x00000000

////////////////////////////////////Local variables and functions/////////////////////////// 

/*!
 * Dump the ssi registers which can be readable. 
 * @param  	ctrl	a pointer of audio controller(audio_ctrl_t) which presents the ssi module itself
 *			
 * @return	0 if succeeded
 *		-1 if failed   
 */
static int32_t ssi_dump(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;

    printf("=================%s dump==================\n", ctrl->name);
    printf("SCR    : 0x%08x\n", HW_SSI_SCR_RD(instance));
    printf("SISR   : 0x%08x\n", HW_SSI_SISR_RD(instance));
    printf("SIER   : 0x%08x\n", HW_SSI_SIER_RD(instance));
    printf("STCR   : 0x%08x\n", HW_SSI_STCR_RD(instance));
    printf("SRCR   : 0x%08x\n", HW_SSI_SRCR_RD(instance));
    printf("STCCR  : 0x%08x\n", HW_SSI_STCCR_RD(instance));
    printf("SRCCR  : 0x%08x\n", HW_SSI_SRCCR_RD(instance));
    printf("SFCSR  : 0x%08x\n", HW_SSI_SFCSR_RD(instance));
    printf("SACNT  : 0x%08x\n", HW_SSI_SACNT_RD(instance));
    printf("SACADD : 0x%08x\n", HW_SSI_SACADD_RD(instance));
    printf("SACDAT : 0x%08x\n", HW_SSI_SACDAT_RD(instance));
    printf("SATAG  : 0x%08x\n", HW_SSI_SATAG_RD(instance));
    printf("STMSK  : 0x%08x\n", HW_SSI_STMSK_RD(instance));
    printf("SRMSK  : 0x%08x\n", HW_SSI_SRMSK_RD(instance));
    printf("SACCST : 0x%08x\n", HW_SSI_SACCST_RD(instance));

    return 0;
}

/*! 
 * Put the ssi to soft-reset mode, and then can be configured.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t ssi_soft_reset(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;

    val = HW_SSI_SCR_RD(instance);
    val &= ~BM_SSI_SCR_SSIEN;
    HW_SSI_SCR_WR(instance, val);	

    return 0;
}

/*!
 * Set all the registers to reset values, called by ssi_init.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t ssi_registers_reset(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;
    
    //Reset control regs. All the status regs will be reset by a soft reset. 
    HW_SSI_SCR_WR(instance, SSI_SCR_RESET_VAL);
    HW_SSI_SIER_WR(instance, SSI_SIER_RESET_VAL);
    HW_SSI_STCR_WR(instance, SSI_STCR_RESET_VAL);
    HW_SSI_SRCR_WR(instance, SSI_SRCR_RESET_VAL);
    HW_SSI_STCCR_WR(instance, SSI_STCCR_RESET_VAL);
    HW_SSI_SRCCR_WR(instance, SSI_SRCCR_RESET_VAL);
    HW_SSI_SFCSR_WR(instance, SSI_SFCSR_RESET_VAL);
    HW_SSI_SACNT_WR(instance, SSI_SACNT_RESET_VAL);
    HW_SSI_SACADD_WR(instance, SSI_SACADD_RESET_VAL);
    HW_SSI_SACDAT_WR(instance, SSI_SACDAT_RESET_VAL);
    HW_SSI_STMSK_WR(instance, SSI_STMSK_RESET_VAL);
    HW_SSI_SRMSK_WR(instance, SSI_SRMSK_RESET_VAL);
    HW_SSI_SACCEN_WR(instance, SSI_SACCEN_RESET_VAL);
    HW_SSI_SACCDIS_WR(instance, SSI_SACCDIS_RESET_VAL);

    return 0;
}

/*!
 * Get the ssi's settings.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 * @param       type    SSI FIFO settings
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static uint32_t ssi_get_hw_setting(audio_ctrl_p ctrl, uint32_t type)
{
    uint32_t instance = ctrl->instance;
    uint32_t val = 0;

    switch (type) {
    case SSI_SETTING_TX_FIFO1_DATAS_CNT:
	val = (HW_SSI_SFCSR_RD(instance) & BM_SSI_SFCSR_TFCNT0) >> BP_SSI_SFCSR_TFCNT0;
        break;
    case SSI_SETTING_TX_FIFO2_DATAS_CNT:
	val = (HW_SSI_SFCSR_RD(instance) & BM_SSI_SFCSR_TFCNT1) >> BP_SSI_SFCSR_TFCNT1;
        break;
    case SSI_SETTING_RX_FIFO1_DATAS_CNT:
	val = (HW_SSI_SFCSR_RD(instance) & BM_SSI_SFCSR_RFCNT0) >> BP_SSI_SFCSR_RFCNT0;
        break;
    case SSI_SETTING_RX_FIFO2_DATAS_CNT:
	val = (HW_SSI_SFCSR_RD(instance) & BM_SSI_SFCSR_RFCNT1) >> BP_SSI_SFCSR_RFCNT1;
        break;
    case SSI_SETTING_TX_WATERMARK:
	val = (HW_SSI_SFCSR_RD(instance) & BM_SSI_SFCSR_TFWM0) >> BP_SSI_SFCSR_TFWM0;
        break;
    case SSI_SETTING_RX_WATERMARK:
	val = (HW_SSI_SFCSR_RD(instance) & BM_SSI_SFCSR_RFWM0) >> BP_SSI_SFCSR_RFWM0;
        break;
    case SSI_SETTING_TX_WORD_LEN:
	val = (HW_SSI_STCCR_RD(instance) & BM_SSI_STCCR_WL3_WL0) >> BP_SSI_STCCR_WL3_WL0;
        val = (val + 1) * 2;
        break;
    case SSI_SETTING_RX_WORD_LEN:
	val = (HW_SSI_SRCCR_RD(instance) & BM_SSI_SRCCR_WL3_WL0) >> BP_SSI_SRCCR_WL3_WL0;
        val = (val + 1) *2;
        break;
    default:
        break;
    }

    return val;
}

/*!
 * Set the ssi's settings.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 * @param       type    SSI FIFO settings
 * @param       val     FIFO watermark level value 
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static uint32_t ssi_set_hw_setting(audio_ctrl_p ctrl, uint32_t type, uint32_t val)
{
    uint32_t instance = ctrl->instance;
    uint32_t v = 0;

    switch (type) {
    case SSI_SETTING_TX_WATERMARK:
	v = HW_SSI_SFCSR_RD(instance);
	v &= ~(BM_SSI_SFCSR_TFWM0 | BM_SSI_SFCSR_TFWM1);
        v |= BF_SSI_SFCSR_TFWM0(val) | BF_SSI_SFCSR_TFWM1(val);
	HW_SSI_SFCSR_WR(instance, v);
        break;
    case SSI_SETTING_RX_WATERMARK:
	v = HW_SSI_SFCSR_RD(instance);
	v &= ~(BM_SSI_SFCSR_RFWM0 | BM_SSI_SFCSR_RFWM1);
        v |= BF_SSI_SFCSR_RFWM0(val) | BF_SSI_SFCSR_RFWM1(val);
	HW_SSI_SFCSR_WR(instance, v);
        break;
    case SSI_SETTING_TX_WORD_LEN:
	v = HW_SSI_STCCR_RD(instance);
	v &= ~BM_SSI_STCCR_WL3_WL0;
        v |= BF_SSI_STCCR_WL3_WL0((val >> 1)-1);	
	HW_SSI_STCCR_WR(instance, v);
        break;
    case SSI_SETTING_RX_WORD_LEN:
	v = HW_SSI_SRCCR_RD(instance);
	v &= ~BM_SSI_SRCCR_WL3_WL0;
        v |= BF_SSI_SRCCR_WL3_WL0((val - 2) >> 1);	
	HW_SSI_SRCCR_WR(instance, v);
        break;
    case SSI_SETTING_TX_BIT_CLOCK:
	v = HW_SSI_STCCR_RD(instance);
	v &= ~(BM_SSI_STCCR_PSR | BM_SSI_STCCR_PM7_PM0);
	v |= val;
	HW_SSI_STCCR_WR(instance, v);
        break;
    case SSI_SETTING_RX_BIT_CLOCK:
	v = HW_SSI_SRCCR_RD(instance);
	v &= ~(BM_SSI_SRCCR_DIV2 | BM_SSI_SRCCR_PSR | BM_SSI_SRCCR_PM7_PM0);
	v |= val;
	HW_SSI_SRCCR_WR(instance, v);
        break;
    case SSI_SETTING_TX_FRAME_LENGTH:
	v = HW_SSI_STCCR_RD(instance);
	v &= ~BM_SSI_STCCR_DC4_DC0;
  	v |= BF_SSI_STCCR_DC4_DC0(val);
	HW_SSI_STCCR_WR(instance, v);	
        break;
    case SSI_SETTING_RX_FRAME_LENGTH:
	v = HW_SSI_SRCCR_RD(instance);
	v &= ~BM_SSI_SRCCR_DC4_DC0;
	v |= BF_SSI_SRCCR_DC4_DC0(val);
	HW_SSI_SRCCR_WR(instance, v);
        break;
    case SSI_SETTING_CLK_FS_DIR:
        if (SSI_CLK_FS_DIR_OUTPUT == val) {
	    v = HW_SSI_STCR_RD(instance);
	    v |= BM_SSI_STCR_TXDIR | BM_SSI_STCR_TFDIR;
	    HW_SSI_STCR_WR(instance, v);
        } else if (SSI_CLK_FS_DIR_INPUT == val) {
	    v = HW_SSI_STCR_RD(instance);
	    v &= ~(BM_SSI_STCR_TXDIR | BM_SSI_STCR_TFDIR);
	    HW_SSI_STCR_WR(instance, v);
        }
        break;
    default:
        return -1;
    }

    return 0;
}

static uint32_t ssi_hw_enable(audio_ctrl_p ctrl, uint32_t type, bool enable)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;

    switch (type) {
    case SSI_HW_ENABLE_SSI:
	val = HW_SSI_SCR_RD(instance);
        if (enable){
	    val |= BM_SSI_SCR_SSIEN;
        }else{
            val &= ~BM_SSI_SCR_SSIEN;
	}
	HW_SSI_SCR_WR(instance, val);
        break;
    case SSI_HW_ENABLE_TX:
	val = HW_SSI_SCR_RD(instance);
        if (enable){
	    val |= BM_SSI_SCR_TE;
        }else{
	    val &= ~BM_SSI_SCR_TE;
	}
	HW_SSI_SCR_WR(instance, val);
        break;
    case SSI_HW_ENABLE_RX:
	val = HW_SSI_SCR_RD(instance);
        if (enable){
	    val |= BM_SSI_SCR_RE;
        }else{
	    val &= ~BM_SSI_SCR_RE;
	}
	HW_SSI_SCR_WR(instance, val);
        break;
    case SSI_HW_ENABLE_TXFIFO1:
	val = HW_SSI_STCR_RD(instance);
        if (enable)
	    val |= BM_SSI_STCR_TFEN0;
        else
	    val &= ~BM_SSI_STCR_TFEN0;
	HW_SSI_STCR_WR(instance, val);
        break;
    case SSI_HW_ENABLE_TXFIFO2:
	val = HW_SSI_STCR_RD(instance);
        if (enable)
	    val |= BM_SSI_STCR_TFEN1;
        else
	    val &= ~BM_SSI_STCR_TFEN1;
	HW_SSI_STCR_WR(instance, val);
        break;
    case SSI_HW_ENABLE_RXFIFO1:
	val = HW_SSI_SRCR_RD(instance);
        if (enable)
	    val |= BM_SSI_SRCR_RFEN0;
        else
	    val &= ~BM_SSI_SRCR_RFEN0;
	HW_SSI_SRCR_WR(instance, val);
        break;
    case SSI_HW_ENABLE_RXFIFO2:
	val = HW_SSI_SRCR_RD(instance);
        if (enable)
	    val |= BM_SSI_SRCR_RFEN1;
        else
	    val &= ~BM_SSI_SRCR_RFEN1;
	HW_SSI_SRCR_WR(instance, val);
        break;
    default:
        break;
    }

    return 0;
}

//////////////////////////////////////// APIs //////////////////////////////////////////////////////////////

int32_t ssi_init(void *priv)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;

    audmux_iomux_config();
    ssi_soft_reset(ctrl);
    ssi_registers_reset(ctrl);

    return 0;
}

int32_t ssi_config(void *priv, audio_dev_para_p para)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    uint32_t val;

    if (AUDIO_BUS_PROTOCOL_I2S == para->bus_protocol) {
        if (AUDIO_BUS_MODE_SLAVE == para->bus_mode) {
	    val = HW_SSI_SCR_RD(instance);
	    val |= BF_SSI_SCR_I2S_MODE(I2S_MODE_SLAVE);
	    HW_SSI_SCR_WR(instance, val);
            ssi_set_hw_setting(ctrl, SSI_SETTING_CLK_FS_DIR, SSI_CLK_FS_DIR_INPUT);
        } else {
	    val = HW_SSI_SCR_RD(instance);
	    val |= BF_SSI_SCR_I2S_MODE(I2S_MODE_MASTER);
	    HW_SSI_SCR_WR(instance, val);
            ssi_set_hw_setting(ctrl, SSI_SETTING_CLK_FS_DIR, SSI_CLK_FS_DIR_OUTPUT);
        }

	val = HW_SSI_SCR_RD(instance);
	val |= BM_SSI_SCR_CLK_IST | BM_SSI_SCR_SYN;
	HW_SSI_SCR_WR(instance, val);

	val = HW_SSI_STCR_RD(instance);
	val |= BM_SSI_STCR_TSCKP | BM_SSI_STCR_TEFS;
	HW_SSI_STCR_WR(instance, val);

	val = HW_SSI_STCCR_RD(instance);
        val &= ~BM_SSI_STCCR_DIV2;
	val |= BF_SSI_STCCR_DC4_DC0(1);
	val &= ~BM_SSI_STCCR_PM7_PM0;
	if(SAMPLERATE_44_1KHz == para->sample_rate){
	    val |= BF_SSI_STCCR_PM7_PM0(0xA);
	}else if(SAMPLERATE_16KHz == para->sample_rate){
	   val |= BF_SSI_STCCR_PM7_PM0(0x1E);
	}else{
		//TODO
	}
	HW_SSI_STCCR_WR(instance, val);
    } else {
        //TODO
    }

    ssi_set_hw_setting(ctrl, SSI_SETTING_TX_WORD_LEN, para->word_length);

    ssi_set_hw_setting(ctrl, SSI_SETTING_TX_WATERMARK, SSI_SFCSR_TX_WATERMARK);
    ssi_set_hw_setting(ctrl, SSI_SETTING_RX_WATERMARK, SSI_SFCSR_RX_WATERMARK);

    ssi_hw_enable(ctrl, SSI_HW_ENABLE_SSI, true);
    ssi_hw_enable(ctrl, SSI_HW_ENABLE_TXFIFO1, true);
    ssi_hw_enable(ctrl, SSI_HW_ENABLE_TX, true);

    ssi_hw_enable(ctrl, SSI_HW_ENABLE_RX, true);
    ssi_hw_enable(ctrl, SSI_HW_ENABLE_RXFIFO1, true);

    ssi_dump(ctrl);

    return 0;
}

int32_t ssi_write_fifo(void *priv, uint8_t * buf, uint32_t size, uint32_t * bytes_written)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    uint32_t i = 0;
    uint32_t wl = ssi_get_hw_setting(ctrl, SSI_SETTING_TX_WORD_LEN);

    while (i < size) {
        if (0x0E > ssi_get_hw_setting(ctrl, SSI_SETTING_TX_FIFO1_DATAS_CNT)) {
            if (wl <= 8) {
                HW_SSI_STXn_WR(instance, 0, *((uint8_t *) (buf + i)));
                i++;
            } else if (wl <= 16) {
                HW_SSI_STXn_WR(instance, 0, *((uint16_t *) (buf + i)));
                i = i + 2;
            } else {
                HW_SSI_STXn_WR(instance, 0, *((uint32_t *) (buf + i)));
                i = i + 4;
            }
        }
    }

    *bytes_written = size;

    return 0;
}

int32_t ssi_read_fifo(void *priv, uint8_t *buf, uint32_t byte2read, uint32_t * byteread)
{
    uint32_t i, size, sample_cnt;
    uint16_t *buf_ptr = (uint16_t *) buf;
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    uint32_t wl = ssi_get_hw_setting(ctrl, SSI_SETTING_RX_WORD_LEN);
    int32_t time_out_tmp;
    
    size = byte2read/(wl);
    for ( i = 0; i < size; i++, buf_ptr++) {
        time_out_tmp = SSI_READ_TIMEOUT;
        do {
            sample_cnt = ((HW_SSI_SFCSR_RD(instance)) >> 12) & 0x0F;
        } while ((time_out_tmp--) && (sample_cnt == 0));

        if (0 >= time_out_tmp) {
            return -1;
        }

        *buf_ptr = HW_SSI_SRXn_RD(instance, 0);
    }
    *byteread = byte2read;

    return 0; 
}

int32_t ssi_deinit(void *priv)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    uint32_t val;

    val = HW_SSI_SISR_RD(instance);
    val |= BM_SSI_SISR_TDE0 | BM_SSI_SISR_TDE1 | BM_SSI_SISR_TFE0 | BM_SSI_SISR_TFE1;
    HW_SSI_SISR_WR(instance, val);

    HW_SSI_SCR_WR(instance, 0);

    return 0;
}

static audio_dev_ops_t ssi_ops = {
    .init = ssi_init,
    .deinit = ssi_deinit,
    .config = ssi_config,
    .ioctl = NULL,
    .write = ssi_write_fifo,
    .read = ssi_read_fifo,
};

audio_ctrl_t imx_ssi_1 = {
    .name = "imx SSI audio controller 1",
    .instance = HW_SSI1,
    .ops = &ssi_ops,
};
audio_ctrl_t imx_ssi_2 = {
    .name = "imx SSI audio controller 2",
    .instance = HW_SSI2,
    .ops = &ssi_ops,
};
audio_ctrl_t imx_ssi_3 = {
    .name = "imx SSI audio controller 3",
    .instance = HW_SSI2,
    .ops = &ssi_ops,
};
