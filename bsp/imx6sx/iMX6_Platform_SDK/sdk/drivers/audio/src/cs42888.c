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
 * @file cs42888.c
 * @brief Driver and test for audio codec CS42888 controlled through I2C.
 *
 * @ingroup diag_audio
 */

#include "sdk.h"
#include "audio/audio.h"
#include "cs42888.h"

extern int32_t esai_codec_power_on(void);

struct imx_i2c_request cs42888_i2c_req;

////////////////////////////// Macros  ///////////////////////////////////////////

#define DEBUG_ENABLE	1
#if DEBUG_ENABLE
#define TRACE(fmt, args...)	printf(fmt,##args)
#else
#define TRACE(fmt, args...)
#endif

#define CS42888_REG_WRITE(codec, addr,val)	\
	do{\
		if(0!=cs42888_reg_write(codec, addr, val)){\
			return -1;\
		}\
	}while(0)

#define CS42888_REG_read(codec, addr, val)	\
	do{\
		if(0!=cs42888_reg_read(codec, addr, &val)){\
			return -1;\
		}\
	}while(0)

////////////////////////////Local variables and functions /////////////////////////////////////////
static void cs42888_i2c_init(audio_codec_p codec)
{
    /* this init is needed only once */
    cs42888_i2c_req.device = codec->device;
    cs42888_i2c_req.reg_addr_sz = 1;         // number of bytes of I2C device register's address
    cs42888_i2c_req.buffer_sz = 1;           // number of data bytes

    i2c_init(codec->device->port, codec->device->freq);
}

static int32_t cs42888_reg_read(audio_codec_p codec, uint8_t reg_addr, uint8_t *ret_val)
{
    cs42888_i2c_req.reg_addr = reg_addr;
    cs42888_i2c_req.buffer = ret_val;

    if (i2c_read(&cs42888_i2c_req) != 0) {
        return -1;
    }

    return 0;
}

static int32_t cs42888_reg_write(audio_codec_p codec, uint8_t reg_addr, uint8_t reg_data)
{
    cs42888_i2c_req.reg_addr = reg_addr;
    cs42888_i2c_req.buffer = &reg_data;

    return i2c_write(&cs42888_i2c_req);
}

////////////////////////////////////// APIs /////////////////////////////////////
int32_t cs42888_init(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    esai_codec_power_on();

    cs42888_i2c_init(codec);

    return 0;
}

int32_t cs42888_dev_info(void *priv, uint8_t *reg_data)
{
	audio_codec_p codec = (audio_codec_p) priv;

	if (cs42888_reg_read(codec, CS42888_REG_CHIP_ID_REV, reg_data) != 0) {
		return -1;
	}

	return 0;
}

int32_t cs42888_config(void *priv, audio_dev_para_p para)
{
    audio_codec_p codec = (audio_codec_p) priv;

    CS42888_REG_WRITE(codec, CS42888_REG_PWR_CTRL, CS42888_REG_PWR_CTRL_BIT_PDN_EN);    // Power up dac, and enter low power mode

    if (AUDIO_BUS_MODE_MASTER == para->bus_mode) {
        CS42888_REG_WRITE(codec, CS42888_REG_FUNC_MODE, CS42888_REG_FUNC_MODE_BITS_DAC_FM_MASTER_4_50K | 
				CS42888_REG_FUNC_MODE_BITS_ADC_FM_MASTER_4_50K | 
				CS42888_REG_FUNC_MODE_BITS_ADC_MCLK_512FS);   // SSM mode, X512 (32*2*4), master
    } else {
	printf("CS42888 configured as slave.\n");
	if((SAMPLERATE_44_1KHz == para->sample_rate) || (SAMPLERATE_48KHz == para->sample_rate)){
        	CS42888_REG_WRITE(codec, CS42888_REG_FUNC_MODE, CS42888_REG_FUNC_MODE_BITS_DAC_FM_SLAVE_AUTO | 
				CS42888_REG_FUNC_MODE_BITS_ADC_FM_SLAVE_AUTO | 
				CS42888_REG_FUNC_MODE_BITS_ADC_MCLK_256FS);   //  X256 (32*2*4), slave
	}else if((SAMPLERATE_32KHz == para->sample_rate) || (SAMPLERATE_16KHz == para->sample_rate)){
        	CS42888_REG_WRITE(codec, CS42888_REG_FUNC_MODE, CS42888_REG_FUNC_MODE_BITS_DAC_FM_SLAVE_AUTO | 
				CS42888_REG_FUNC_MODE_BITS_ADC_FM_SLAVE_AUTO | 
				CS42888_REG_FUNC_MODE_BITS_ADC_MCLK_384FS);  
	}
    }
    //Interface Format Setting
    CS42888_REG_WRITE(codec, CS42888_REG_INF_FMT, CS42888_REG_INF_FMT_BIT_AUX_DIF_I2S |
                      CS42888_REG_INF_FMT_BITS_DAC_DIF_LEFT_24BIT |
                      CS42888_REG_INF_FMT_BITS_ADC_DIF_LEFT_24BIT);
    CS42888_REG_WRITE(codec, CS42888_REG_TRANS_CTRL, CS42888_REG_TRANS_CTRL_BITS_ALL_AUTO_MUTE_DISABLE);    // disable auto-mute
    // mute all DACs
    CS42888_REG_WRITE(codec, CS42888_REG_DAC_MUTE, CS42888_REG_DAC_MUTE_BITS_MUTE_ALL);
    // out of low power
    CS42888_REG_WRITE(codec, CS42888_REG_PWR_CTRL, CS42888_REG_PWR_CTRL_BITS_POWER_ALL);
    //2090RCLK should be delayed.
    hal_delay_us(CS42888_PWRUP_UNMUTE_DELAY_US);
    //unmute DACs
    CS42888_REG_WRITE(codec, CS42888_REG_DAC_MUTE, CS42888_REG_DAC_MUTE_BITS_UNMUTE_ALL);

    return 0;
}

int32_t cs42888_deinit(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    CS42888_REG_WRITE(codec, CS42888_REG_PWR_CTRL, CS42888_REG_PWR_CTRL_BIT_PDN_EN);    // Enter low power mode

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
audio_dev_ops_t cs42888_ops = {
    .init = cs42888_init,
    .deinit = cs42888_deinit,
    .config = cs42888_config,
};

audio_codec_t cs42888 = {
    .name = "cs42888",
    .device = &g_cs42888_i2c_device,
    .ops = &cs42888_ops,
};
