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
 * @file sgtl5000.c
 * @brief Driver for the SGTL5000.
 *
 * @ingroup diag_audio
 */

#include "sdk.h"
#include "audio/audio.h"
#include "sgtl5000.h"
#include "sgtl5000_priv.h"

extern void SGTL5000PowerUp_and_clockinit(void);

struct imx_i2c_request sgtl5000_i2c_req;

// SGTL5000 specific register values
#define CHIP_REF_CTRL_REG_VALUE 0x01FF  // VDDA/2
#define CHIP_LINE_OUT_CTRL_REG_VALUE 0x0322 // VDDIO/2
#define CHIP_LINE_OUT_VOL_REG_VALUE 0x0F0F  // based on VDDA and VDDIO values
#define CHIP_CLK_TOP_CTRL_REG_VALUE 0   // pass through, Input OSC 13.5MHz, default configuration for sample rate, 48KHz
#define CHIP_PLL_CTRL_REG_VALUE ((14 << 11) | (1154))
#define CHIP_CLK_CTRL_REG_VALUE ((0x2 << 2) | (0x3))
#define CHIP_CLK_CTRL_REG_MCLK_FREQ_VALUE 0x3   /*12MHz =256*Fs */
#define CHIP_PLL_CTRL_REG_VALUE2     ((16 << 11) | (786))   // for CodecInit2

////////////////////////////// Macros  ///////////////////////////////////////////
#define DEBUG_ENABLE	1
#if DEBUG_ENABLE
#define TRACE(fmt, args...)	printf(fmt,##args)
#else
#define TRACE(fmt, args...)
#endif

#define SGTL5000_REG_WRITE(codec, reg_addr, reg_val)	\
 	do{     \
		if(0 != sgtl5000_write_reg(codec, reg_addr, reg_val)){   \
                    printf("Write %s  failed.\n", #reg_addr);   \
                    return -1;	\
               } \
	}while(0)

#define SGTL5000_REG_READ(codec, reg_addr, reg_val)	\
 	do{     \
		if(0 != sgtl5000_read_reg(codec, reg_addr, &reg_val)){   \
                    printf("Read %s  failed.\n", #reg_addr);   \
			return -1;	\
                }   \
	}while(0)

#define SGTL5000_REG_DUMP(codec, reg_addr)	\
	do{	\
		uint16_t reg_val;	\
		if(0 != sgtl5000_read_reg(codec, reg_addr, &reg_val)){   \
                    printf("Read %s  failed.\n", #reg_addr);   \
                    return -1;	\
                }    \
		printf(" %s: 0x%04x\n",  #reg_addr, reg_val); \
	}while(0)

////////////////////////////Local variables and functions /////////////////////////////////////////
static int32_t sgtl5000_init_status = 0;

static void sgtl5000_i2c_init(audio_codec_p codec)
{
    /* this init is needed only once */
//     sgtl5000_i2c_req.ctl_addr = codec->i2c_base;
//     sgtl5000_i2c_req.dev_addr = codec->i2c_dev_addr;
    sgtl5000_i2c_req.device = codec->device;
    sgtl5000_i2c_req.reg_addr_sz = 2;
    sgtl5000_i2c_req.buffer_sz = 2;

    i2c_init(codec->device->port, codec->device->freq);
}

static int32_t sgtl5000_read_reg(audio_codec_p codec, uint16_t reg_addr, uint16_t *reg_val)
{
    int res = 0;
    uint8_t data[2];
    uint8_t buf[2];

    /*device need high byte firstly, so swap them */
    buf[0] = reg_addr & 0xff;
    buf[1] = (reg_addr & 0xff00) >> 8;

    sgtl5000_i2c_req.reg_addr = (buf[0] << 8) | buf[1];
    sgtl5000_i2c_req.buffer = data;

    res = i2c_read(&sgtl5000_i2c_req);

    *reg_val = (data[0] << 8) | data[1];

    return res;
}

static int32_t sgtl5000_write_reg(audio_codec_p codec, uint16_t reg_addr,
                                       uint16_t reg_data)
{
    uint8_t data[2];
    uint8_t buf[2];

    buf[0] = reg_addr & 0xff;
    buf[1] = (reg_addr & 0xff00) >> 8;

    data[1] = reg_data & 0x00ff;
    data[0] = (reg_data & 0xff00) >> 8;

    sgtl5000_i2c_req.reg_addr = (buf[0] << 8) | buf[1];
    sgtl5000_i2c_req.buffer = data;

    return i2c_write(&sgtl5000_i2c_req);
}

static int32_t sgtl5000_dump(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    printf("------------------ %s dump ---------------------\n", codec->name);
    SGTL5000_REG_DUMP(codec, CHIP_DIG_ID_REG);
    SGTL5000_REG_DUMP(codec, CHIP_I2S0_CTRL_REG);
    SGTL5000_REG_DUMP(codec, CHIP_PLL_CTRL_REG);
    SGTL5000_REG_DUMP(codec, CHIP_CLK_CTRL_REG);
    SGTL5000_REG_DUMP(codec, CHIP_ANA_POWER_REG);
    SGTL5000_REG_DUMP(codec, CHIP_ANA_CTRL_REG);
    SGTL5000_REG_DUMP(codec, CHIP_SSS_CTRL_REG);
    SGTL5000_REG_DUMP(codec, CHIP_DIG_POWER_REG);
    SGTL5000_REG_DUMP(codec, CHIP_REF_CTRL_REG);

    return 0;
}

/* Turn up the volume */
static int32_t sgtl5000_dac_volume_up(audio_codec_p codec)
{
    uint16_t val;
    uint16_t volume;

    SGTL5000_REG_READ(codec, CHIP_ANA_HP_CTRL_REG, val);
    volume = (val) & 0x7f;

    /* min value */
    if (volume < 0x10) {
        volume = 0;
        printf("MAX Volume!\n");
    } else
        volume -= 0x10;

    val = volume | (volume << 8);
    debug_printf("0x%x\n", val);

    SGTL5000_REG_WRITE(codec, CHIP_ANA_HP_CTRL_REG, val);

    return 0;
}

/* Turn down the volume */
static int32_t sgtl5000_dac_volume_down(audio_codec_p codec)
{
    uint16_t val;
    uint16_t volume;

    SGTL5000_REG_READ(codec, CHIP_ANA_HP_CTRL_REG, val);
    volume = ((val) & 0x7f);

    /* max value */
    if (volume >= 0x6f) {
        volume = 0x7f;
        printf("MIN Volume!\n");
    } else {
        volume += 0x10;
    }

    val = volume | (volume << 8);

    SGTL5000_REG_WRITE(codec, CHIP_ANA_HP_CTRL_REG, val);

    return 0;
}

/* Mute volume */
static int32_t sgtl5000_hp_mute(audio_codec_p codec)
{
    uint16_t val;

    SGTL5000_REG_READ(codec, CHIP_ANA_CTRL_REG, val);
    val |= 1 << 4;
    SGTL5000_REG_WRITE(codec, CHIP_ANA_CTRL_REG, val);

    return 0;
}

/* Mute volume */
static int32_t sgtl5000_hp_unmute(audio_codec_p codec)
{
    uint16_t val;

    SGTL5000_REG_READ(codec, CHIP_ANA_CTRL_REG, val);
    val &= ~(1 << 4);
    SGTL5000_REG_WRITE(codec, CHIP_ANA_CTRL_REG, val);

    return 0;
}

static int32_t sgtl5000_dap_init(audio_codec_p codec)
{
    uint16_t v;

    /*Set I2S-IN->DAP->DAC->HP route */
    v = (0x1 << 8)              // I2S_IN -> DAP mixer
        | (0x1 << 6)            //DAP data source as I2S_IN
        | (0x3 << 4)            //DAC data source as DAP
        ;

    SGTL5000_REG_WRITE(codec, CHIP_SSS_CTRL_REG, v);

    /* enable DAP */
    v = (1 << 4)                // enable dap mixer
        | (1 << 0);             //enable dap
    SGTL5000_REG_WRITE(codec, DAP_CONTROL_REG, v);

    /* Power Up DAP */
    SGTL5000_REG_READ(codec, CHIP_DIG_POWER_REG, v);
    v |= (1 << 4);
    SGTL5000_REG_WRITE(codec, CHIP_DIG_POWER_REG, v);

    return 0;
}

//////////////////////////////////// APIs //////////////////////////////////
int32_t sgtl5000_init(void *priv)
{
    uint16_t v;
    audio_codec_p codec = (audio_codec_p) priv;

    if (sgtl5000_init_status) { /* sgtl5000 is inited */
        return 0;
    }

    SGTL5000PowerUp_and_clockinit();

    sgtl5000_i2c_init(codec);
    //-------------------Power Configuration-----------------------

    // Set VAG_VAL(bits 8:4)(Analog ground level) level to to VDDA/2
    // reference bias current for all the analog blocks
    // set to -50% from the nominal value
    SGTL5000_REG_WRITE(codec, CHIP_REF_CTRL_REG, CHIP_REF_CTRL_REG_VALUE);
    // Enable the internal oscillator for the charge pump (Set bit 11)
    SGTL5000_REG_WRITE(codec, CHIP_CLK_TOP_CTRL_REG, 0x0800);
    // Turn down the charge pump supply (clear bit 11)
    SGTL5000_REG_WRITE(codec, CHIP_ANA_POWER_REG, 0x4260);
    // Set LINEOUT VAG voltage to VDDIO/2 (1.375V) and bias current
    // the recommended value of 0.36mA for 10kOhm load with 1nF
    // capacitance
    SGTL5000_REG_WRITE(codec, CHIP_LINE_OUT_CTRL_REG, CHIP_LINE_OUT_CTRL_REG_VALUE);
    // Power up the VAG reference buffer. Also power off the startup
    // and simple linreg needed for power up.  These are not needed as
    // internal VDDD is already enabled above.
    SGTL5000_REG_WRITE(codec, CHIP_ANA_POWER_REG, 0x0AA0);
    /* delay for stablity after power up */
    hal_delay_us(100000);

    //------------------Startup volume configuration-----------------
    // Set LINEOUT volume based on VAG and LINEOUT_VAG values
    SGTL5000_REG_WRITE(codec, CHIP_LINE_OUT_VOL_REG, CHIP_LINE_OUT_VOL_REG_VALUE);
    // Ramp down the HP volume to the lowest level -51.5dB
    //SGTL5000RampHPVolume(HP_LOWEST_VOL);

    //----------------Other Analog Block Configuration---------------
    // Configure slow ramp up rate to minimize pop (bit 0)
    SGTL5000_REG_WRITE(codec, CHIP_REF_CTRL_REG, CHIP_REF_CTRL_REG_VALUE);
    // Enable short detect mode for headphone left/right
    // and center channel and set short detect current trip level
    // to 75mA
    SGTL5000_REG_WRITE(codec, CHIP_SHORT_CTRL_REG, 0x1106);
    // Enable Zero-cross detect for HP_OUT (bit 5) and ADC (bit 1)
    SGTL5000_REG_WRITE(codec, CHIP_ANA_CTRL_REG, 0x0133);
    // Configure to use the PLL.
    // Divisors programmed for 12.288MHz external MCLK rate and assuming 44.1kHz sample
    // rate
    /*Set I2S of SGTL5000 as Master */
    v = (0x0 << 8)              //64Fs
        | (0x1 << 7)            //master of I2S
        | (0x0 << 6)            //data is valid in rising edge of SCLK
        | (0x0 << 2)            //I2S mode
        | (0x0 << 1)            //I2S_LRCLK is not aligned to data
        | (0x0 << 0)            //defaule LRCLK polarity
        ;

    SGTL5000_REG_WRITE(codec, CHIP_I2S0_CTRL_REG, v);

    sgtl5000_dap_init(codec);

    v = 0x00;
    SGTL5000_REG_WRITE(codec, CHIP_ANA_CTRL_REG, v);
    /*Power up HP,ADC,DAC,Lineout */
    SGTL5000_REG_WRITE(codec, CHIP_ANA_POWER_REG, 0x4ff9);  // ADC is off
    /*Power up desired digital blocks: DAC, I2S_IN */
    SGTL5000_REG_READ(codec, CHIP_DIG_POWER_REG, v);
    v |= (1 << 0) | (1 << 5);
    SGTL5000_REG_WRITE(codec, CHIP_DIG_POWER_REG, v);

    SGTL5000_REG_WRITE(codec, CHIP_ANA_HP_CTRL_REG, 0x1818);
    /*Umute DAC */
    SGTL5000_REG_WRITE(codec, CHIP_ADCDAC_CTRL_REG, 0x0230);
    /* default configuration for word length, 16 bits */
    SGTL5000_REG_READ(codec, CHIP_I2S0_CTRL_REG, v);
    v &= ~(0x3 << 4);
    v |= (0x3 << 4);
    SGTL5000_REG_WRITE(codec, CHIP_I2S0_CTRL_REG, v);
    /*Set sample rate as 48kHz */
    printf("Set SR to 48KHz.\n");
    SGTL5000_REG_WRITE(codec, CHIP_CLK_TOP_CTRL_REG, CHIP_CLK_TOP_CTRL_REG_VALUE);

    SGTL5000_REG_WRITE(codec, CHIP_PLL_CTRL_REG, CHIP_PLL_CTRL_REG_VALUE);

    SGTL5000_REG_WRITE(codec, CHIP_CLK_CTRL_REG, CHIP_CLK_CTRL_REG_VALUE);

    sgtl5000_init_status = 1;

    //sgtl5000_dump(codec);

    return 0;
}

int32_t sgtl5000_i2s_config(void *priv, audio_dev_para_p para)
{
    uint16_t v;
    audio_codec_p codec = (audio_codec_p) priv;

    SGTL5000_REG_READ(codec, CHIP_I2S0_CTRL_REG, v);

    if (para->word_length == WL_16) {
        v &= ~(0x3 << 4);
        v |= (0x3 << 4);

    } else if (para->word_length == WL_20) {
        v &= ~(0x3 << 4);
        v |= (0x2 << 4);
    } else if (para->word_length == WL_24) {
        v &= ~(0x3 << 4);
        v |= (0x1 << 4);
    } else {
        v &= ~(0x3 << 4);
        v |= (0x0 << 4);
    }

    SGTL5000_REG_WRITE(codec, CHIP_I2S0_CTRL_REG, v);

    return 0;
}

int32_t sgtl5000_deinit(void *priv)
{
    sgtl5000_init_status = 0;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
audio_dev_ops_t sgtl5000_ops = {
    .init = sgtl5000_init,
    .deinit = sgtl5000_deinit,
    .config = sgtl5000_i2s_config,
};

audio_codec_t sgtl5000 = {
    .name = "sgtl5000",
    .device = &g_sgtl5000_i2c_device,
//     .i2c_base = SGTL5000_I2C_BASE,
//     .i2c_freq = 100000,
//     .i2c_dev_addr = SGTL5000_I2C_ID,
    .ops = &sgtl5000_ops,
};
