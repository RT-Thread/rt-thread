/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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
 * @file imx_spdif.c
 * @brief Driver for spdif controller.
 *
 * @ingroup diag_audio
 */

#include "sdk.h"
#include "audio/audio.h"
#include "imx_spdif.h"
#include "registers/regsspdif.h"

#define SPDIF_DEBUG 1

#if SPDIF_DEBUG
#define D(fmt,args...) printf(fmt, ## args)
#else
#define D(fmt,args...)
#endif

#define UNUSED_VARIABLE(x)	(x) = (x)

/* Register value definitions */
#define SCR_TXFIFO_ESEL_0_SAMPLE	(0x0 << 15)
#define SCR_TXFIFO_ESEL_4_SAMPLE	(0x1 << 15)
#define SCR_TXFIFO_ESEL_8_SAMPLE	(0x2 << 15)
#define SCR_TXFIFO_ESEL_12_SAMPLE	(0x3 << 15)
#define SCR_TXFIFO_ZERO		(0 << 10)
#define SCR_TXFIFO_NORMAL	(1 << 10)
#define SCR_VAL_CLEAR		(1 << 5)
#define SCR_TXSEL_OFF		(0 << 2)
#define SCR_TXSEL_RX		(1 << 2)
#define SCR_TXSEL_NORMAL	(0x5 << 2)
#define SCR_USRC_SEL_NONE	(0x0)
#define SCR_USRC_SEL_RECV	(0x1)
#define SCR_USRC_SEL_CHIP	(0x3)

extern void spdif_clk_cfg(void);
extern unsigned int spdif_get_tx_clk_freq(void);

/*! 
 * Dump spdif readable registers.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
#if SPDIF_DEBUG
static int32_t spdif_dump(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;

    UNUSED_VARIABLE(instance);

    printf("=================%s dump==================\n", ctrl->name);

    printf("SCR: 0x%x\n", 	HW_SPDIF_SCR_RD());
    printf("SRCD: 0x%x\n", 	HW_SPDIF_SRCD_RD());
    printf("SRPC: 0x%x\n", 	HW_SPDIF_SRPC_RD());
    printf("SIE: 0x%x\n", 	HW_SPDIF_SIE_RD());
    printf("SIS: 0x%x\n", 	HW_SPDIF_SIS_RD());
    printf("SRCSH: 0x%x\n", 	HW_SPDIF_SRCSH_RD());
    printf("SRCSL: 0x%x\n", 	HW_SPDIF_SRCSL_RD());
    printf("STCSCH: 0x%x\n", 	HW_SPDIF_STCSCH_RD());
    printf("STCSCL: 0x%x\n", 	HW_SPDIF_STCSCL_RD());
    printf("SRFM: 0x%x\n", 	HW_SPDIF_SRFM_RD());
    printf("STC: 0x%x\n", 	HW_SPDIF_STC_RD());

    return 0;
}
#else
static int32_t spdif_dump(audio_ctrl_p ctrl)
{
    return 0;
}
#endif

/*! 
 * Put the spdif to soft-reset mode, and then can be configured.
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static int32_t spdif_soft_reset(audio_ctrl_p ctrl)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;
    int cycle = 0;

    UNUSED_VARIABLE(instance);

    val = HW_SPDIF_SCR_RD();
    val |= BM_SPDIF_SCR_SOFT_RESET;
    HW_SPDIF_SCR_WR(val);

    while ((HW_SPDIF_SCR_RD() &  BM_SPDIF_SCR_SOFT_RESET) && (cycle++ < 100)) ;

    return 0;
}

/*!
 * Get the spdif's settings.
 *
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 * @param       type    SPDIF hw configuration
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
static uint32_t spdif_get_hw_setting(audio_ctrl_p ctrl, uint32_t type)
{
    uint32_t instance = ctrl->instance;
    uint32_t val;

    UNUSED_VARIABLE(instance);

    switch (type) {
    case SPDIF_GET_FREQMEAS:
        val = HW_SPDIF_SRFM_RD();
        break;
    case SPDIF_GET_GAIN_SEL:
        val = (HW_SPDIF_SRPC_RD() & (0x7 << 3)) >> 3;
        break;
    case SPDIF_GET_RX_CCHANNEL_INFO_H:
        val = HW_SPDIF_SRCSH_RD();
        break;
    case SPDIF_GET_RX_CCHANNEL_INFO_L:
        val = HW_SPDIF_SRCSL_RD();
        break;
    case SPDIF_GET_RX_UCHANNEL_INFO:
        val = HW_SPDIF_SRU_RD();
        break;
    case SPDIF_GET_RX_QCHANNEL_INFO:
        val = HW_SPDIF_SRQ_RD();
        break;
    case SPDIF_GET_INT_STATUS:
        val = HW_SPDIF_SIS_RD();
    }

    return val;
}

/*!
 * Calucate the spdif's tx clock divider according the sample rate.
 *
 * @param       ctrl    a pointer of audio controller(audio_ctrl_t) which presents the ssi module
 * @param       sample_rate     sample rate to be set
 *
 * @return      the divider value
 */
static uint32_t spdif_cal_txclk_div(audio_ctrl_p ctrl, uint32_t sample_rate)
{
    float val;

    val = (float)spdif_get_tx_clk_freq() / ((float)sample_rate * 32.0f * 2.0f) + 0.5f;

    return ((uint32_t) val - 1);
}

//////////////////////////////////////// APIs //////////////////////////////////////////////////////////////

/*!
 * Initialize the spdif module and set the ssi to default status. 
 * This function will be called by the snd_card driver. 
 *
 * @param       priv    a pointer passed by audio card driver, spdif driver should change it 
 *			            to a audio_ctrl_p pointer which presents the spdif controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t spdif_init(void *priv)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;

    spdif_iomux_config();
    spdif_soft_reset(ctrl);
    spdif_clk_cfg();

    return 0;
}

/*!
 * Configure the spdif module according the parameters which was passed by audio_card driver.
 *
 * @param       priv    a pointer passed by audio card driver, spdif driver should change it
 *                      to a audio_ctrl_p pointer which presents the spdif controller.
 * @param       para    a pointer passed by audio card driver, consists of configuration parameters
 *                      for spdif controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t spdif_config(void *priv, audio_dev_para_p para)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    iec958_cchannel_t cchannel;
    uint32_t val;

    UNUSED_VARIABLE(instance);

    /* Set channel information */
    memset(&cchannel, 0, sizeof(cchannel));
    cchannel.h.ctrl.audio_format = IEC958_CON_AUDIO_PCM;
    cchannel.h.ctrl.copyright = IEC958_CON_COPYRIGHT_NONE;
    cchannel.h.ctrl.add_info = IEC958_CON_EMPHASIS_5015;
    cchannel.h.ctrl.channel_mode = IEC958_CON_CHANNEL_MODE0;
    cchannel.h.ctrl.source_number = IEC958_CON_SOURCE_NUMBER_2;

    cchannel.l.ctrl.clock_accuracy = IEC958_CON_CLOCK_ACCURACY_LEVEL2;

    if (para->sample_rate == SAMPLERATE_44_1KHz)
        cchannel.l.ctrl.sample_freq = IEC958_CON_SAMPLE_FREQ_44100;
    else if (para->sample_rate == SAMPLERATE_32KHz)
        cchannel.l.ctrl.sample_freq = IEC958_CON_SAMPLE_FREQ_32000;
    else if (para->sample_rate == SAMPLERATE_16KHz)	
	// There's no 16KHz sample rate defined in IEC958, it is supposed that the receiver
	// will measure the sample rate automatically.
	cchannel.l.ctrl.sample_freq = IEC958_CON_SAMPLE_FREQ_NOT_INDICATED;
    else                        //48K
        cchannel.l.ctrl.sample_freq = IEC958_CON_SAMPLE_FREQ_48000;

    if (para->word_length == WL_16) // 16 bits
    {
        cchannel.l.ctrl.max_len = IEC958_CON_MAX_LENGTH_20;
        cchannel.l.ctrl.sample_len = IEC958_CON_SAMPLE_LENGTH_20_16;    //IEC958_CON_SAMPLE_LENGTH_20_16;
    } else                      //wBitsPerSample == 24, 32
    {
        cchannel.l.ctrl.max_len = IEC958_CON_MAX_LENGTH_24;
        cchannel.l.ctrl.sample_len = IEC958_CON_SAMPLE_LENGTH_24_20;    //IEC958_CON_SAMPLE_LENGTH_24_20;
    }
    HW_SPDIF_STCSCH_WR(cchannel.h.data);
    HW_SPDIF_STCSCL_WR(cchannel.l.data);

    val = HW_SPDIF_SCR_RD();
    val |=
        SCR_USRC_SEL_NONE | SCR_TXSEL_NORMAL | SCR_VAL_CLEAR | SCR_TXFIFO_NORMAL |
        BM_SPDIF_SCR_TXAUTOSYNC | SCR_TXFIFO_ESEL_8_SAMPLE;
    HW_SPDIF_SCR_WR(val);

    val = HW_SPDIF_STC_RD();
    /* Select SPDIF0_CLK as tx clk */
    val &= ~(BM_SPDIF_STC_TXCLK_SOURCE);
    val |= TX_CLK_SEL_SPDIF0_CLK << BP_SPDIF_STC_TXCLK_SOURCE;
    /* Set tx clk divider */
    val &= ~(BM_SPDIF_STC_TXCLK_DF);
    val |= spdif_cal_txclk_div(ctrl, para->sample_rate) << BP_SPDIF_STC_TXCLK_DF;
    val |= BM_SPDIF_STC_TX_ALL_CLK_EN;
    HW_SPDIF_STC_WR(val);

    spdif_dump(ctrl);

    return 0;
}

/*!
 * Write datas to the spdif fifo in polling mode.
 * @param       priv    a pointer passed by audio card driver, spdif driver should change it
 *                      to a audio_ctrl_p pointer which presents the spdif controller.
 * @param       buf	points to the buffer which hold the data to be written to the spdif tx fifo
 * @param       size    the size of the buffer pointed by buf.
 * @param       bytes_written	bytes be written to the spdif tx fifo
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t spdif_write_fifo(void *priv, uint8_t * buf, uint32_t size, uint32_t * bytes_written)
{
    audio_ctrl_p ctrl = (audio_ctrl_p) priv;
    uint32_t instance = ctrl->instance;
    uint32_t i = 0;
    uint32_t val_right, val_left;

    UNUSED_VARIABLE(instance);

    while (i < size) {
        if (HW_SPDIF_SIS_RD() & BM_SPDIF_SIS_TXEM) {
            val_right = (uint32_t)(*((uint16_t *) (buf + i)));
	    val_left = (uint32_t)(*((uint16_t *) (buf + i + 2)));
            /* TODO: the msb bit of the audio data should be always at 23bit of stl or str  */
            val_right = (val_right << 8) & 0x00ffffff;
            val_left = (val_left << 8) & 0x00ffffff;

	    HW_SPDIF_STR_WR(val_right);
	    HW_SPDIF_STL_WR(val_left);

            i += 4;
        }
    }

    *bytes_written = size;

    return 0;
}

/*!
 * Close the spdif module
 * @param       priv    a pointer passed by audio card driver, spdif driver should change it
 *                      to a audio_ctrl_p pointer which presents the spdif controller.
 *
 * @return      0 if succeeded
 *              -1 if failed
 */
int32_t spdif_deinit(void *priv)
{
    return 0;
}

static audio_dev_ops_t spdif_ops = {
    .init = spdif_init,
    .deinit = spdif_deinit,
    .config = spdif_config,
    .ioctl = NULL,
    .write = spdif_write_fifo,
};

audio_ctrl_t imx_spdif = {
    .name = "imx SPDIF audio controller",
    .instance = 1,
    .ops = &spdif_ops,
};
