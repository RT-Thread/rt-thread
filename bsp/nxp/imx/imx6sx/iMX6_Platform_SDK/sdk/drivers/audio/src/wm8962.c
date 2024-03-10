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

#include "sdk.h"
#include "audio/audio.h"
#include "wm8962.h"

extern int32_t esai_codec_power_on(void);

struct imx_i2c_request wm8962_i2c_req;

////////////////////////////// Macros  ///////////////////////////////////////////
#define DEBUG_ENABLE	1
#if DEBUG_ENABLE
#define TRACE(fmt, args...)	printf(fmt,##args)
#else
#define TRACE(fmt, args...)
#endif

#define WM8962_REG_WRITE(codec, reg_addr, reg_val)	\
 	do{     \
		if(0 != WM8962_i2c_write(codec, reg_addr, reg_val)){   \
            printf("Write %s  failed.\n", #reg_addr);   \
            return -1;	\
        } \
	}while(0)

#define WM8962_REG_READ(reg_addr, reg_val)	\
 	do{     \
		if(0 != WM8962_i2c_read(reg_addr, &reg_val)){   \
            printf("Read %s  failed.\n", #reg_addr);   \
			return -1;	\
        }   \
	}while(0)

static void wm8962_i2c_init(audio_codec_p codec)
{
    /* this init is needed only once */
    wm8962_i2c_req.device = codec->device;
    wm8962_i2c_req.reg_addr_sz = 2;
    wm8962_i2c_req.buffer_sz = 2;

    i2c_init(codec->device->port, codec->device->freq);
}

static uint16_t WM8962_i2c_read(audio_codec_p codec, uint16_t reg_addr)
{
    uint16_t reg_data;
    uint8_t data[2];

    /*For both data and reg_addr, WM8962 need the MSB byte to be transferred firstly. */
    wm8962_i2c_req.reg_addr = ((reg_addr & 0xFF) << 8) | ((reg_addr & 0xFF00) >> 8);
    wm8962_i2c_req.buffer = data;

    i2c_xfer(&wm8962_i2c_req, 1);

    reg_data = (data[0] << 8) | data[1];

    return reg_data;
}

static int32_t WM8962_i2c_write(audio_codec_p codec, uint32_t reg_addr, uint16_t reg_data)
{
    uint8_t data[2];

    /*For both data and reg_addr, WM8962 need the MSB byte to be transferred firstly. */
    data[1] = reg_data & 0x00ff;
    data[0] = (reg_data & 0xff00) >> 8;

    wm8962_i2c_req.reg_addr = ((reg_addr & 0xFF) << 8) | ((reg_addr & 0xFF00) >> 8);
    wm8962_i2c_req.buffer = data;

    return i2c_xfer(&wm8962_i2c_req, 0);
}
static int32_t WM8962_reg_modify(audio_codec_p codec, uint16_t reg_addr, uint16_t reg_data, uint16_t msk)
{
    uint16_t val;

    val = WM8962_i2c_read(codec, reg_addr);
    val &= ~msk;
    val |= (reg_data & msk);

    return WM8962_i2c_write(codec, reg_addr, val);
}

static int32_t WM8962_DAC_disable(void *priv)
{
    //TODO

    return 0;
}

static int32_t WM8962_Soft_Reset(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    WM8962_REG_WRITE(codec, WM8962_SOFTWARE_RESET, WM8962_ID);

    WM8962_REG_WRITE(codec, 0x7F, 0);  //PLL Software Reset 

    return 0;
}

int32_t WM8962_dump(void *priv)
{
    printf("=====WM8962 DUMP=====\n");

    return 0;
}

/* 
 *	Since there are tow FLLs within WM8962, the external osc is not necessary.
 *	So the osc can be saved if WM8962 works at SLAVE mode.
 *	Slave mode was tested on sbrth_tablet board, while master mode not yet.
 */
int32_t WM8962_DAC_configure(void *priv, audio_dev_para_p para)
{
    //uint16_t val;

    audio_codec_p codec = (audio_codec_p) priv;
    if (AUDIO_BUS_MODE_MASTER != para->bus_mode)  {
//    if (!para->is_master) {
        TRACE("The WM8962 was configured as slave. \n");
        /*
         * The FLL must be configured in slave mode, and the BCLK, LRCLK was supposed to be provided by the master.
         * Config the FLL. For BCLK = 2.8224M, Fout = (BCLK/1)*32.0/8 = 11.2896
         */
#if 0
        val = WM8962_i2c_read(codec, WM8962_FLL_CONTROL_1);    //Disable the FLL
        val &= ~WM8962_FLL_ENA;
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_1, val);

        val = WM8962_FLL_CTRL2_OUTDIV(8) | WM8962_FLL_CTRL2_REFCLK_DIV(FLL_CTRL2_REFCLK_DIV1);
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_2, val);

        val = WM8962_FLL_CTRL3_FRATIO(FLL_FRATIO_1) | 0x180;
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_3, val);
        val = WM8962_FLL_CTRL6_NUM(0);
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_6, val);

        val = WM8962_FLL_CTRL7_DEN(0x7D);   //using default value
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_7, val);

        val = WM8962_FLL_CTRL8_N(32);
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_8, val);

        val = WM8962_REG_FLL_CTRL1_REF_SRC(BCLK) | WM8962_FLL_FRAC | WM8962_FLL_ENA | 0x8;
        WM8962_REG_WRITE(codec, WM8962_FLL_CONTROL_1, val);

        // Wait a while for the FLL to be locked.
        hal_delay_us(400 * 1000);

        val = WM8962_i2c_read(codec, WM8962_INTERRUPT_STATUS_2);
        if (val & WM8962_FLL_LOCK_EINT) {
            TRACE("The FLL within WM8962 was locked.\n");
        } else {
            return -1;
        }
#endif
    } else {
        TRACE("The WM8962 was configured as master. \n");
    }

    /* Software reset and brings up VMID */
    WM8962_REG_WRITE(codec, 0x81, 0x0001); //Disable all PLLs and OSC
    WM8962_REG_WRITE(codec, 0x1C, 0x001C); //STARTUP_BIAS_ENA=1, VMID_BUF_ENA=1, VMID_RAMP=1
    WM8962_REG_WRITE(codec, 0x19, 0x00D6); //DMIC_ENA=0, OPCLK_ENA=0, VMID_SEL=01, BIAS_ENA=1, INL_ENA=0, INR_ENA=1, ADCL_ENA=0, ADCR_ENA=1, MICBIAS_ENA=1

    /* Clocking configuration */
    WM8962_reg_modify(codec, 0x08, 0x0800, 0x0820);    //CLKREG_OVD=1, SYSCLK_ENA=0
    if(SAMPLERATE_44_1KHz == para->sample_rate) {
    	WM8962_REG_WRITE(codec, 0x1B, 0x0000); //Set sample rate to 44.1kHz
    	WM8962_reg_modify(codec, 0x38, 0x0006, 0x001E);    //MCLK_RATE=0011 (256fs)
    }else if(SAMPLERATE_16KHz == para->sample_rate){
    	WM8962_REG_WRITE(codec, 0x1B, 0x0013); //Set sample rate to 16K
    	WM8962_reg_modify(codec, 0x38, 0x0006, 0x001E);    //MCLK_RATE=0011 (256fs)
    }
    WM8962_reg_modify(codec, 0x08, 0x0020, 0x0620);    //MCLK_SRC=00 (MCLK pin), SYSCLK_ENA=1 

    /* ADC->HP path configuration */
    WM8962_reg_modify(codec, 0x05, 0x0008, 0x0008);    //DAC Mute   
    WM8962_REG_WRITE(codec, 0x52, 0x0001); //CP_DYN_PWR=1 (Class W)
    WM8962_reg_modify(codec, 0x48, 0x0001, 0x0001);    //Enable charge pump

    WM8962_REG_WRITE(codec, 0x45, 0x0011);
    WM8962_REG_WRITE(codec, 0x45, 0x0033);
    WM8962_REG_WRITE(codec, 0x02, 0x0030); //HPOUTL_VOL
    WM8962_REG_WRITE(codec, 0x03, 0x0130); //HPOUTR_VOL
    WM8962_REG_WRITE(codec, 0x3D, 0x00CC); //Run DC Servo on Headphone
    hal_delay_us(1000 * 50);
    WM8962_REG_WRITE(codec, 0x45, 0x0077);
    WM8962_REG_WRITE(codec, 0x45, 0x00FF);

    WM8962_REG_WRITE(codec, 0x02, 0x0079); //HPOUTL_VOL = 0dB
    WM8962_REG_WRITE(codec, 0x03, 0x0179); //HPOUTR_VOL = 0dB

    /* ADC->Speaker path configuration */
    WM8962_REG_WRITE(codec, 0x69, 0x0000); //DACL to SPKOUTL
    WM8962_REG_WRITE(codec, 0x6A, 0x0000); //DACR to SPKOUTR
    WM8962_REG_WRITE(codec, 0x33, 0x0000); //Class D volume = 0dB, mono-mode disabled
    WM8962_REG_WRITE(codec, 0x28, 0x00F9); //SPKL PGA volume = 0dB, Zero-cross enabled
    WM8962_REG_WRITE(codec, 0x29, 0x01F9); //SPKL PGA volume = 0dB, Zero-cross enabled, Volume update
    WM8962_REG_WRITE(codec, 0x31, 0x00D0); //Enable Class D

    /* Recording path configuration */
    WM8962_REG_WRITE(codec, 0x25, 0x0002); // IN3L->INPGAL
    WM8962_REG_WRITE(codec, 0x26, 0x0002); // IN3R->INPGAR
    WM8962_REG_WRITE(codec, 0x22, 0x0009); // INPGA->MIXIN
    /* Recording vol configuration */
    WM8962_reg_modify(codec, 0x20, 0x0000, 0x0038);    //INPGAL->MIXINL vol=0dB
    WM8962_reg_modify(codec, 0x21, 0x0000, 0x0038);    //INPGAR->MIXINR vol=0dB
    WM8962_REG_WRITE(codec, 0x00, 0x0027); // INPGAL vol=6dB
    WM8962_REG_WRITE(codec, 0x01, 0x0127); // INPGAR vol=6dB and update
    WM8962_REG_WRITE(codec, 0x1A, 0x1F8);  //Enable headphone PGAs and DACs, Speaker PGSs, Unmute headphone PGAs 
    WM8962_reg_modify(codec, 0x05, 0x0000, 0x0008);    //DAC Unmute 

    return 0;
}

int32_t WM8962_DAC_init(void *priv)
{
    uint16_t id = 0;
    audio_codec_p codec = (audio_codec_p) priv;

//    i2c_init(WM8962_I2C_BASE_ADDR, 100000);
    wm8962_i2c_init(codec);

    if (0 != WM8962_Soft_Reset(codec))
        return -1;

    hal_delay_us(1000 * 500);

    id = WM8962_i2c_read(codec, WM8962_SOFTWARE_RESET);

    if (WM8962_ID != id) {
        printf("Device ID dismatch, 0x%04x while 0x%04x expected.\n", id, WM8962_ID);
        return -1;
    } else {
        printf("Codec Device ID: 0x%04x\n", id);
    }

    WM8962_REG_WRITE(codec, 0x08, 0x09C4); //Get full register access/control: CLKREG_OVD=1, SYSCLK_ENA=0

    return 0;
}

/* Close all the operations of codec*/

int32_t WM8962_DAC_deinit(void *priv)
{
    WM8962_DAC_disable(priv);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
audio_dev_ops_t wm8962_ops = {
    .init = WM8962_DAC_init,
    .deinit = WM8962_DAC_deinit,
    .config = WM8962_DAC_configure,
};

audio_codec_t wm8962 = {
    .name = "wm8962",
    .device = &g_wm8962_i2c_device,
    .ops = &wm8962_ops,
};

