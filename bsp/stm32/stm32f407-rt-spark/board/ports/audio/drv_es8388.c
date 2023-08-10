/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2019-07-31     Zero-Free    first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_es8388.h"

/* ES8388 address */
#define ES8388_ADDR 0x10  /*0x11:CE=1;0x10:CE=0*/

struct es8388_device
{
    struct rt_i2c_bus_device *i2c;
    rt_uint16_t pin;
};

static struct es8388_device es_dev = {0};

static rt_uint16_t reg_read(rt_uint8_t addr)
{
    struct rt_i2c_msg msg[2] = {0};
    rt_uint8_t val = 0xff;

    RT_ASSERT(es_dev.i2c != RT_NULL);

    msg[0].addr  = ES8388_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 1;
    msg[0].buf   = &addr;

    msg[1].addr  = ES8388_ADDR;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = 1;
    msg[1].buf   = &val;

    if (rt_i2c_transfer(es_dev.i2c, msg, 2) != 2)
    {
        rt_kprintf("I2C read data failed, reg = 0x%02x. \n", addr);
        return 0xff;
    }

    return val;
}

static void reg_write(rt_uint8_t addr, rt_uint8_t val)
{
    struct rt_i2c_msg msgs[1] = {0};
    rt_uint8_t buff[2] = {0};

    RT_ASSERT(es_dev.i2c != RT_NULL);

    buff[0] = addr;
    buff[1] = val;

    msgs[0].addr  = ES8388_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = buff;
    msgs[0].len   = 2;

    if (rt_i2c_transfer(es_dev.i2c, msgs, 1) != 1)
    {
        rt_kprintf("I2C write data failed, reg = 0x%2x. \n", addr);
        return;
    }
}

static int es8388_set_adc_dac_volume(int mode, int volume, int dot)
{
    int res = 0;
    if (volume < -96 || volume > 0)
    {
        if (volume < -96)
            volume = -96;
        else
            volume = 0;
    }
    dot = (dot >= 5 ? 1 : 0);
    volume = (-volume << 1) + dot;
    if (mode == ES_MODE_ADC || mode == ES_MODE_DAC_ADC)
    {
        reg_write(ES8388_ADCCONTROL8, volume);
        reg_write(ES8388_ADCCONTROL9, volume);  //ADC Right Volume=0db
    }
    if (mode == ES_MODE_DAC || mode == ES_MODE_DAC_ADC)
    {
        reg_write(ES8388_DACCONTROL5, volume);
        reg_write(ES8388_DACCONTROL4, volume);
    }
    return res;
}

void es8388_set_voice_mute(rt_bool_t enable)
{
    rt_uint8_t reg = 0;

    reg = reg_read(ES8388_DACCONTROL3);
    reg = reg & 0xFB;
    reg_write(ES8388_DACCONTROL3, reg | (((int)enable) << 2));
}

rt_err_t es8388_init(const char *i2c_name, rt_uint16_t pin)
{
    es_dev.i2c = rt_i2c_bus_device_find(i2c_name);
    if (es_dev.i2c == RT_NULL)
    {
        rt_kprintf("%s bus not found\n", i2c_name);
        return -RT_ERROR;
    }

    es_dev.pin = pin;

    reg_write(ES8388_DACCONTROL3, 0x04);  // 0x04 mute/0x00 unmute&ramp;DAC unmute and  disabled digital volume control soft ramp
    /* Chip Control and Power Management */
    reg_write(ES8388_CONTROL2, 0x50);
    reg_write(ES8388_CHIPPOWER, 0x00); //normal all and power up all
    reg_write(ES8388_MASTERMODE, 0x00); //TODO:CODEC IN I2S SLAVE MODE

    /* dac */
    reg_write(ES8388_DACPOWER, 0xC0);  //disable DAC and disable Lout/Rout/1/2
    reg_write(ES8388_CONTROL1, 0x12);  //Enfr=0,Play&Record Mode,(0x17-both of mic&paly)
    // reg_write(ES8388_CONTROL2, 0);  //LPVrefBuf=0,Pdn_ana=0
    reg_write(ES8388_DACCONTROL1, 0x18);//1a 0x18:16bit iis , 0x00:24
    reg_write(ES8388_DACCONTROL2, 0x02);  //DACFsMode,SINGLE SPEED; DACFsRatio,256
    reg_write(ES8388_DACCONTROL16, 0x00); // 0x00 audio on LIN1&RIN1,  0x09 LIN2&RIN2
    reg_write(ES8388_DACCONTROL17, 0x9C); // only left DAC to left mixer enable 0db
    reg_write(ES8388_DACCONTROL20, 0x9C); // only right DAC to right mixer enable 0db
    reg_write(ES8388_DACCONTROL21, 0x80); //set internal ADC and DAC use the same LRCK clock, ADC LRCK as internal LRCK
    reg_write(ES8388_DACCONTROL23, 0x00);   //vroi=0
    es8388_set_adc_dac_volume(ES_MODE_DAC, 0, 0);          // 0db

    reg_write(ES8388_DACPOWER, 0x3c);  //0x3c Enable DAC and Enable Lout/Rout/1/2
    /* adc */
    reg_write(ES8388_ADCPOWER, 0xFF);
    reg_write(ES8388_ADCCONTROL1, 0xbb); // MIC Left and Right channel PGA gain
    reg_write(ES8388_ADCCONTROL2, 0x00);  //0x00 LINSEL & RINSEL, LIN1/RIN1 as ADC Input; DSSEL,use one DS Reg11; DSR, LINPUT1-RINPUT1
    reg_write(ES8388_ADCCONTROL3, 0x02);
    reg_write(ES8388_ADCCONTROL4, 0x0d); // Left/Right data, Left/Right justified mode, Bits length, I2S format
    reg_write(ES8388_ADCCONTROL5, 0x02);  //ADCFsMode,singel SPEED,RATIO=256
    //ALC for Microphone
    es8388_set_adc_dac_volume(ES_MODE_ADC, 0, 0);      // 0db
    reg_write(ES8388_ADCPOWER, 0x09); //Power on ADC, Enable LIN&RIN, Power off MICBIAS, set int1lp to low power mode
    /* enable es8388 PA */
    es8388_pa_power(RT_TRUE);

    reg_write(ES8388_DACCONTROL24, 0x1E); // LOUT1VOL balanced noise: 0x18
    reg_write(ES8388_DACCONTROL25, 0x1E); // ROUT1VOL balanced noise: 0x18

    return RT_EOK;
}

rt_err_t es8388_start(enum es8388_mode mode)
{
    int res = 0;
    rt_uint8_t prev_data = 0, data = 0;

    prev_data = reg_read(ES8388_DACCONTROL21);
    if (mode == ES_MODE_LINE)
    {
        reg_write(ES8388_DACCONTROL16, 0x09); // 0x00 audio on LIN1&RIN1,  0x09 LIN2&RIN2 by pass enable
        reg_write(ES8388_DACCONTROL17, 0x50); // left DAC to left mixer enable  and  LIN signal to left mixer enable 0db  : bupass enable
        reg_write(ES8388_DACCONTROL20, 0x50); // right DAC to right mixer enable  and  LIN signal to right mixer enable 0db : bupass enable
        reg_write(ES8388_DACCONTROL21, 0xC0); //enable adc
    }
    else
    {
        reg_write(ES8388_DACCONTROL21, 0x80);   //enable dac
    }
    data = reg_read(ES8388_DACCONTROL21);

    if (prev_data != data)
    {
        reg_write(ES8388_CHIPPOWER, 0xF0);   //start state machine
        // reg_write(ES8388_ADDR, ES8388_CONTROL1, 0x16);
        // reg_write(ES8388_ADDR, ES8388_CONTROL2, 0x50);
        reg_write(ES8388_CHIPPOWER, 0x00);   //start state machine
    }
    if (mode == ES_MODE_ADC || mode == ES_MODE_DAC_ADC || mode == ES_MODE_LINE)
    {
        reg_write(ES8388_ADCPOWER, 0x00);   //power up adc and line in
    }
    if (mode == ES_MODE_DAC || mode == ES_MODE_DAC_ADC || mode == ES_MODE_LINE)
    {
        reg_write(ES8388_DACPOWER, 0x3c);   //power up dac and line out
        es8388_set_voice_mute(RT_FALSE);
    }

    return res;
}

rt_err_t es8388_stop(enum es8388_mode mode)
{
    int res = 0;
    if (mode == ES_MODE_LINE)
    {
        reg_write(ES8388_DACCONTROL21, 0x80); //enable dac
        reg_write(ES8388_DACCONTROL16, 0x00); // 0x00 audio on LIN1&RIN1,  0x09 LIN2&RIN2
        reg_write(ES8388_DACCONTROL17, 0x90); // only left DAC to left mixer enable 0db
        reg_write(ES8388_DACCONTROL20, 0x90); // only right DAC to right mixer enable 0db
        return res;
    }
    if (mode == ES_MODE_DAC || mode == ES_MODE_DAC_ADC)
    {
        reg_write(ES8388_DACPOWER, 0x00);
        es8388_set_voice_mute(RT_TRUE); //res |= Es8388SetAdcDacVolume(ES_MODULE_DAC, -96, 5);      // 0db
        // reg_write(ES8388_ADDR, ES8388_DACPOWER, 0xC0);  //power down dac and line out
    }
    if (mode == ES_MODE_ADC || mode == ES_MODE_DAC_ADC)
    {
        // Es8388SetAdcDacVolume(ES_MODULE_ADC, -96, 5);      // 0db
        reg_write(ES8388_ADCPOWER, 0xFF);  //power down adc and line in
    }
    if (mode == ES_MODE_DAC_ADC)
    {
        reg_write(ES8388_DACCONTROL21, 0x9C);   //disable mclk
        // reg_write(ES8388_CONTROL1, 0x00);
        // reg_write(ES8388_CONTROL2, 0x58);
        // reg_write(ES8388_CHIPPOWER, 0xF3);  //stop state machine
    }

    return RT_EOK;
}

rt_err_t es8388_fmt_set(enum es8388_mode mode, enum es8388_format fmt)
{
    rt_uint8_t reg = 0;

    if (mode == ES_MODE_ADC || mode == ES_MODE_DAC_ADC)
    {
        reg = reg_read(ES8388_ADCCONTROL4);
        reg = reg & 0xfc;
        reg_write(ES8388_ADCCONTROL4, reg | fmt);
    }
    if (mode == ES_MODE_DAC || mode == ES_MODE_DAC_ADC)
    {
        reg = reg_read(ES8388_DACCONTROL1);
        reg = reg & 0xf9;
        reg_write(ES8388_DACCONTROL1, reg | (fmt << 1));
    }

    return RT_EOK;
}

void es8388_volume_set(rt_uint8_t volume)
{
    uint32_t real_vol = 0;
    volume = 100 - volume;
    if (volume > 100)
        volume = 100;

    real_vol = 192 * volume / 100;

    reg_write(ES8388_DACCONTROL4, (rt_uint8_t)real_vol);  // DAC L
    reg_write(ES8388_DACCONTROL5, (rt_uint8_t)real_vol);  // DAC R
}

rt_uint8_t es8388_volume_get(void)
{
    rt_uint8_t volume;

    volume = reg_read(ES8388_DACCONTROL24);
    if (volume == 0xff)
    {
        volume = 0;
    }
    else
    {
        volume *= 3;
        if (volume == 99)
            volume = 100;
    }

    return volume;
}

void es8388_pa_power(rt_bool_t enable)
{
    rt_pin_mode(es_dev.pin, PIN_MODE_OUTPUT);

    if (enable)
    {
        rt_pin_write(es_dev.pin, PIN_HIGH);
    }
    else
    {
        rt_pin_write(es_dev.pin, PIN_LOW);
    }
}

void estest()
{

    // reg_write(ES8388_DACCONTROL24, volume);
    reg_write(ES8388_ADCCONTROL1, 0x88);       /* R9,左右通道PGA增益设置 */
    reg_write(ES8388_ADCCONTROL2, 0x10);  // 使用板载麦克风
    // reg_write(ES8388_ADCCONTROL2,0x50);   // 使用耳机麦克风
    // reg_write(ES8388_ADCCONTROL3, 0xC0);
    reg_write(ES8388_ADCCONTROL8, 0x00);   // LADCVOL
    reg_write(ES8388_ADCCONTROL9, 0x00);   // RADCVOL
    reg_write(ES8388_DACCONTROL16, 0x1B);   // LMIXSEL RMIXSEL
    reg_write(ES8388_DACCONTROL17, 0x40);   // LI2LOVOL

    reg_write(ES8388_DACCONTROL24, 0x21);   // LOUT1VOL
    reg_write(ES8388_DACCONTROL25, 0x21);   // ROUT1VOL

    reg_write(ES8388_DACCONTROL24, 33); // LOUT1VOL balanced noise: 0x18
    reg_write(ES8388_DACCONTROL25, 33); // ROUT1VOL balanced noise: 0x18


}
MSH_CMD_EXPORT(estest, test mic loop)
