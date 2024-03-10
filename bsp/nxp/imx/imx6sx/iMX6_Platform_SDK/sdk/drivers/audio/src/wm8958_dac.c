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
#include "wm8958_dac.h"

struct imx_i2c_request wm8958_i2c_req;

////////////////////////////// Macros  ///////////////////////////////////////////
#define DEBUG_ENABLE	1
#if DEBUG_ENABLE
#define TRACE(fmt, args...)	printf(fmt,##args)
#else
#define TRACE(fmt, args...)
#endif

#define WM8958_REG_WRITE(codec, reg_addr, reg_val)	\
 	do{     \
		if(0 != WM8958_i2c_write(codec, reg_addr, reg_val)){   \
            printf("Write %s  failed.\n", #reg_addr);   \
            return -1;	\
        } \
	}while(0)

#define WM8958_REG_READ(codec, reg_addr, reg_val)	\
 	do{     \
		if(0 != WM8958_i2c_read(codec, reg_addr, &reg_val)){   \
            printf("Read %s  failed.\n", #reg_addr);   \
			return -1;	\
        }   \
	}while(0)


static void wm8958_i2c_init(audio_codec_p codec)
{
    /* this init is needed only once */
//     wm8958_i2c_req.ctl_addr = codec->i2c_base;
//     wm8958_i2c_req.dev_addr = codec->i2c_dev_addr;
    wm8958_i2c_req.device = codec->device;
    wm8958_i2c_req.reg_addr_sz = 2;
    wm8958_i2c_req.buffer_sz = 2;

    i2c_init(codec->device->port, codec->device->freq);
}

static uint16_t WM8958_i2c_read(audio_codec_p codec, uint16_t reg_addr)
{
    uint16_t reg_data;
    uint8_t data[2];

    /*For both data and reg_addr, WM8958 need the MSB byte to be transferred firstly. */
    wm8958_i2c_req.reg_addr = ((reg_addr & 0xFF) << 8) | ((reg_addr & 0xFF00) >> 8);
    wm8958_i2c_req.buffer = data;

    i2c_xfer(&wm8958_i2c_req, 1);

    reg_data = (data[0] << 8) | data[1];

    return reg_data;
}

static int32_t WM8958_i2c_write(audio_codec_p codec, uint32_t reg_addr, uint16_t reg_data)
{
    uint8_t data[2];

    /*For both data and reg_addr, WM8958 need the MSB byte to be transferred firstly. */
    data[1] = reg_data & 0x00ff;
    data[0] = (reg_data & 0xff00) >> 8;

    wm8958_i2c_req.reg_addr = ((reg_addr & 0xFF) << 8) | ((reg_addr & 0xFF00) >> 8);
    wm8958_i2c_req.buffer = data;

    return i2c_xfer(&wm8958_i2c_req, 0);
}

int32_t WM8958_dump(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    printf("=====WM8958 DUMP=====\n");
    printf("WM8958_RESET_ID: 0x%x\n", WM8958_i2c_read(codec, WM8958_REG_RESET_ID));
    printf("WM8958_REG_AIF1_RATE       : 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_AIF1_RATE));
    printf("WM8958_REG_AIF1_BCLK       : 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_AIF1_BCLK));
    printf("WM8958_REG_AIF1DAC_LRCLK   : 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_AIF1DAC_LRCLK));
    printf("WM8958_REG_AIF1_CTRL_1     : 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_AIF1_CTRL_1));
    printf("WM8958_REG_AIF1_MASTER_SLAV: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_AIF1_MASTER_SLAVE));
    printf("WM8958_REG_CLOCKING_1      : 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_CLOCKING_1));
    printf("WM8958_REG_AIF1_CLOCKING_1 : 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_AIF1_CLOCKING_1));

    printf("WM8958_REG_FLL1_CTRL1: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL1_CTRL1));
    printf("WM8958_REG_FLL1_CTRL2: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL1_CTRL2));
    printf("WM8958_REG_FLL1_CTRL3: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL1_CTRL3));
    printf("WM8958_REG_FLL1_CTRL4: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL1_CTRL4));
    printf("WM8958_REG_FLL1_CTRL5: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL1_CTRL5));
    printf("WM8958_REG_FLL2_CTRL1: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL2_CTRL1));
    printf("WM8958_REG_FLL2_CTRL2: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL2_CTRL2));
    printf("WM8958_REG_FLL2_CTRL3: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL2_CTRL3));
    printf("WM8958_REG_FLL2_CTRL4: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL2_CTRL4));
    printf("WM8958_REG_FLL2_CTRL5: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_FLL2_CTRL5));

    printf("WM8958_REG_WR_SEQ_0: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_0));
    printf("WM8958_REG_WR_SEQ_1: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_1));
    printf("WM8958_REG_WR_SEQ_2: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_2));
    printf("WM8958_REG_WR_SEQ_3: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_3));
    printf("WM8958_REG_WR_SEQ_4: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_4));
    printf("WM8958_REG_WR_SEQ_5: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_5));
    printf("WM8958_REG_WR_SEQ_6: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_6));
    printf("WM8958_REG_WR_SEQ_7: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_WR_SEQ_7));

    printf("===================\n");
    printf("\n");

    return 0;
}

static int32_t WM8958_DAC_disable(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    WM8958_REG_WRITE(codec, WM8958_REG_AIF1_DAC1_FILTER_1, 0x0200);    //Soft mute DAC1L and DAC1R
    WM8958_REG_WRITE(codec, WM8958_REG_WRITE_SEQUENCER_CTRL_1, 0x812A);    //Generic shut down
    hal_delay_us(600 * 1000);
    WM8958_REG_WRITE(codec, WM8958_REG_OUTPUT_MIXER_1, 0x0000);    //disable path from DAC1L to HPOUT1L
    WM8958_REG_WRITE(codec, WM8958_REG_OUTPUT_MIXER_2, 0x0000);    //disable path from DAC1R to HPOUT1R
    WM8958_REG_WRITE(codec, WM8958_REG_POWER_MANAGEMENT4, 0x0000); //disable DAC1L and DAC1R   

    return 0;
}

static int32_t WM8958_Soft_Reset(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;
    WM8958_REG_WRITE(codec, WM8958_REG_RESET_ID, 0x0000);

    return 0;
}

/* 
 *	Since there are tow FLLs within WM8958, the external osc is not necessary.
 *	So the osc can be saved if WM8958 works at SLAVE mode.
 *	Slave mode was tested on sbrth_tablet board, while master mode not yet.
 */
int32_t WM8958_DAC_configure(void *priv, audio_dev_para_p para)
{
    uint16_t val;

    audio_codec_p codec = (audio_codec_p) priv;
    if (AUDIO_BUS_MODE_MASTER != para->bus_mode)  {
        TRACE("The WM8958 was configured as slave. \n");
        /*
         * The FLL must be configured in slave mode, and the BCLK, LRCLK was supposed to be povided by the master. 
         *
         * Config the FLL. For BCLK = 2.8224M, Fout = (BCLK/1)*32.0/8 = 11.2896
         */
        val = WM8958_REG_FLL_CTRL5_REF_SRC(BCLK) | WM8958_REG_FLL_CTRL5_REF_DIV(FLL_REFCLK_DIV_1);
        WM8958_REG_WRITE(codec, WM8958_REG_FLL1_CTRL5, val);

        val = WM8958_REG_FLL_CTRL4_N(32);
        WM8958_REG_WRITE(codec, WM8958_REG_FLL1_CTRL4, val);

        val = WM8958_REG_FLL_CTRL3_K(0);
        WM8958_REG_WRITE(codec, WM8958_REG_FLL1_CTRL3, val);

        val = WM8958_REG_FLL_CTRL2_FRATIO(1) | WM8958_REG_FLL_CTRL2_OUTDIV(8);
        WM8958_REG_WRITE(codec, WM8958_REG_FLL1_CTRL2, val);

        // Enable the FLL
        WM8958_REG_WRITE(codec, WM8958_REG_FLL1_CTRL1, WM8958_REG_FLL_CTRL1_FLL_EN);
        // Wait a while for the FLL to be locked.
        hal_delay_us(200 * 1000);

        if (WM8958_i2c_read(codec, WM8958_REG_INT_RAW_STATUS2) & WM8958_REG_INT_RAW_STATUS2_FLL1_LOCK) {
            TRACE("The FLL within WM8958 was locked.\n");
        } else {
            printf("The FLL within WM8958 failed to be locked.\n");
            return -1;
        }
    } else {
        TRACE("The WM8958 was configured as master. \n");
    }

    /* Analogue Configuration   */
    WM8958_REG_WRITE(codec, WM8959_REG_ANTIPOP_2, 0x01E4); //Enable VMID soft start (fast), Start-up Bias Current Enabled
    WM8958_REG_WRITE(codec, WM8958_REG_POWER_MANAGEMENT0, 0x0003); //Enable bias generator, Enable VMID
    hal_delay_us(1000 * 50);

    /*Path Configuration */
    WM8958_REG_WRITE(codec, 0x601, 0x0001);    //Enable the AIF1 Timeslot 0 (Left) to DAC 1 (Left) mixer path
    WM8958_REG_WRITE(codec, 0x602, 0x0001);    //Enable the AIF1 Timeslot 0 (Right) to DAC 1 (Right) mixer path

    /*Clocking Configuration */
    WM8958_REG_WRITE(codec, 0x210, 0x0073);    //AIF1 Sample Rate = 44.1 kHz, AIF1CLK/Fs ratio = 256, so AIF1CLK is supposed to be 11.289MHz
    WM8958_REG_WRITE(codec, 0x300, 0x4010);    //AIF1 Word Length = 16-bits, AIF1 Format = I2S
    if (para->bus_mode == AUDIO_BUS_MODE_MASTER) {
        WM8958_REG_WRITE(codec, 0x302, 0x4000);    //AIF1 Master Mode
    } else {
        WM8958_REG_WRITE(codec, 0x302, 0x0000);    //AIF1 Slave Mode
    }
    WM8958_REG_WRITE(codec, 0x208, 0x000A);    //Enable the DSP processing clock for AIF1, Enable the core clock
    if (para->bus_mode == AUDIO_BUS_MODE_MASTER) {
        WM8958_REG_WRITE(codec, 0x200, 0x0003);    //Enable AIF1 Clock, AIF1 Clock Source = MCLK1 pin, AIF1CLK_DIV = 1
        // The MCLK1 is supposed to be 22.5792MHz which is a very common value.
    } else {
        WM8958_REG_WRITE(codec, 0x200, 0x0011);    //Enable AIF1 Clock, AIF1 Clock Source = FLL1
    }

    /* Headphone Enable */
    WM8958_REG_WRITE(codec, 0x01, 0x0303); //Enable bias generator, Enable VMID, Enable HPOUT1
    WM8958_REG_WRITE(codec, 0x60, 0x0022); //Enable HPOUT1 (Left) and HPOUT1 (Right) intermediate stages
    WM8958_REG_WRITE(codec, 0x4C, 0x9F25); //Enable Charge Pump
    hal_delay_us(15 * 1000);
    WM8958_REG_WRITE(codec, 0x05, 0x0303); //Enable DAC1 (Left), Enable DAC1 (Right),
    //Enable AIF1 Timeslot 0 DAC (Left) Path, Enable AIF1 Timeslot 0 DAC (Right) Path
    WM8958_REG_WRITE(codec, 0x2D, 0x0001); //Select DAC1 (Left) to Left Headphone Output PGA (HPOUT1LVOL) path
    WM8958_REG_WRITE(codec, 0x2E, 0x0001); //Select DAC1 (Right) to Right Headphone Output PGA (HPOUT1RVOL) path
    WM8958_REG_WRITE(codec, 0x03, 0x0030); //Enable Left Output Mixer (MIXOUTL), Enable Right Output Mixer (MIXOUTR)
    WM8958_REG_WRITE(codec, 0x54, 0x0033); //Enable DC Servo and trigger start-up mode on left and right channels
    hal_delay_us(1000 * 250);
    WM8958_REG_WRITE(codec, 0x60, 0x00EE); //Enable HPOUT1 (Left) and HPOUT1 (Right) intermediate and output stages. Remove clamps

    /* Unmutes */
    WM8958_REG_WRITE(codec, 0x610, 0x00C0);    //Unmute DAC 1 (Left)
    WM8958_REG_WRITE(codec, 0x611, 0x00C0);    //Unmute DAC 1 (Right)
    WM8958_REG_WRITE(codec, 0x420, 0x0000);    //Unmute the AIF1 Timeslot 0 DAC path

    return 0;
}

int32_t WM8958_DAC_init(void *priv)
{
    audio_codec_p codec = (audio_codec_p) priv;

    wm8958_i2c_init(codec);
    WM8958_Soft_Reset(codec);

    hal_delay_us(1000 * 500);

    printf("Codec Device ID: 0x%04x\n", WM8958_i2c_read(codec, WM8958_REG_RESET_ID));

    return 0;
}

/* Close all the operations of PMIC DAC */
int32_t WM8958_DAC_deinit(void *priv)
{
    WM8958_DAC_disable(priv);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
audio_dev_ops_t wm8958_ops = {
    .init = WM8958_DAC_init,
    .deinit = WM8958_DAC_deinit,
    .config = WM8958_DAC_configure,
};

audio_codec_t wm8958 = {
    .name = "wm8958",
    .device = &g_wm8958_i2c_device,
//     .i2c_base = WM8958_I2C_BASE_ADDR,
//     .i2c_freq = 100000,
//     .i2c_dev_addr = WM8958_I2C_DEV_ADDR,
    .ops = &wm8958_ops,
};

/* end of wm8903_dac.c */
