/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-05     zylx         The first version for STM32F4xx
 * 2019-4-25      misonyo      port to IMXRT
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "bsp_wm8960.h"
#include <stdlib.h>
#include <drv_log.h>
#include <rthw.h>
static rt_uint16_t wm8960_regval_tbl[56] = {
    0x0097, 0x0097, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x000a, 0x01c0, 0x0000, 0x00ff, 0x00ff, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x007b, 0x0100, 0x0032, 0x0000, 0x00c3, 0x00c3, 0x01c0, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 0x0050, 0x0050, 0x0050, 0x0050, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0040, 0x0000, 0x0000, 0x0050, 0x0050, 0x0000, 0x0002, 0x0037, 0x004d, 0x0080, 0x0008, 0x0031, 0x0026, 0x00e9,
};
static rt_uint16_t reg_cache[WM8960_CACHEREGNUM];
static void wm8960_write_reg(struct rt_i2c_bus_device *dev,  rt_uint8_t reg, rt_uint16_t val)
{
    struct rt_i2c_msg msg;
    rt_uint8_t send_buffer[2];
    RT_ASSERT(dev != RT_NULL);
    /* store temp */
    rt_uint16_t buff = val;
    reg_cache[reg] = buff;
    send_buffer[0] = (reg << 1) | ((val >> 8U) & 0x0001U);
    send_buffer[1] = (rt_uint8_t)(val & 0xFF);
    msg.addr = 0x1A;////WM8960_I2C_ADDR 0x1A
    msg.flags = RT_I2C_WR;
    msg.len = 2;
    msg.buf = send_buffer;
    rt_i2c_transfer(dev, &msg, 1);
}
static void wm8960_read_reg(struct rt_i2c_bus_device *dev, rt_uint8_t reg, rt_uint16_t *val)
{
    *val = reg_cache[reg];
}

static void wm8960_modify_reg(struct rt_i2c_bus_device *dev, rt_uint8_t reg, rt_uint16_t mask, rt_uint16_t val)
{
    uint16_t reg_val = 0;
    wm8960_read_reg(dev, reg, &reg_val);
    reg_val &= (rt_uint16_t)~mask;
    reg_val |= val;

    wm8960_write_reg(dev, reg, reg_val);
}
void WM8960_SetMasterSlave(struct rt_i2c_bus_device *dev, rt_bool_t master)
{
    if (master == 1)
    {
        wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_MS_MASK, WM8960_IFACE1_MS(WM8960_IFACE1_MASTER));
    }
    else
    {
        wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_MS_MASK, WM8960_IFACE1_MS(WM8960_IFACE1_SLAVE));
    }
}

void WM8960_SetModule(struct rt_i2c_bus_device *dev, wm8960_module_t module, rt_bool_t isEnabled)
{
    switch (module)
    {
    case kWM8960_ModuleADC:
        wm8960_modify_reg(dev, WM8960_POWER1, WM8960_POWER1_ADCL_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER1_ADCL_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER1, WM8960_POWER1_ADCR_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER1_ADCR_SHIFT));
        break;
    case kWM8960_ModuleDAC:
        wm8960_modify_reg(dev, WM8960_POWER2, WM8960_POWER2_DACL_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER2_DACL_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER2, WM8960_POWER2_DACR_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER2_DACR_SHIFT));
        break;
    case kWM8960_ModuleVREF:
        wm8960_modify_reg(dev, WM8960_POWER1, WM8960_POWER1_VREF_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER1_VREF_SHIFT));
        break;
    case kWM8960_ModuleLineIn:
        wm8960_modify_reg(dev, WM8960_POWER1, WM8960_POWER1_AINL_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER1_AINL_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER1, WM8960_POWER1_AINR_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER1_AINR_SHIFT));
        break;
    case kWM8960_ModuleLineOut:
        wm8960_modify_reg(dev, WM8960_POWER2, WM8960_POWER2_LOUT1_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER2_LOUT1_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER2, WM8960_POWER2_ROUT1_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER2_ROUT1_SHIFT));
        break;
    case kWM8960_ModuleMICB:
        wm8960_modify_reg(dev, WM8960_POWER1, WM8960_POWER1_MICB_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER1_MICB_SHIFT));
        break;
    case kWM8960_ModuleSpeaker:
        wm8960_modify_reg(dev, WM8960_POWER2, WM8960_POWER2_SPKL_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER2_SPKL_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER2, WM8960_POWER2_SPKR_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER2_SPKR_SHIFT));
        wm8960_write_reg(dev, WM8960_CLASSD1, 0xF7);
        break;
    case kWM8960_ModuleMIC:
        wm8960_modify_reg(dev, WM8960_POWER3, WM8960_POWER3_LMIC_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER3_LMIC_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER3, WM8960_POWER3_RMIC_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER3_RMIC_SHIFT));
        break;
    case kWM8960_ModuleOMIX:
        wm8960_modify_reg(dev, WM8960_POWER3, WM8960_POWER3_LOMIX_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER3_LOMIX_SHIFT));
        wm8960_modify_reg(dev, WM8960_POWER3, WM8960_POWER3_ROMIX_MASK,
                          ((uint16_t)isEnabled << WM8960_POWER3_ROMIX_SHIFT));
        break;
    default:
        break;
    }
}

void WM8960_SetDataRoute(struct rt_i2c_bus_device *dev, wm8960_route_t route)
{
    switch (route)
    {
    case kWM8960_RouteBypass:
        /* Bypass means from line-in to HP*/
        /*
         * Left LINPUT3 to left output mixer, LINPUT3 left output mixer volume = 0dB
         */
        wm8960_write_reg(dev, WM8960_LOUTMIX, 0x80);

        /*
         * Right RINPUT3 to right output mixer, RINPUT3 right output mixer volume = 0dB
         */
        wm8960_write_reg(dev, WM8960_ROUTMIX, 0x80);
        break;
    case kWM8960_RoutePlayback:
        /* Data route I2S_IN-> DAC-> HP */
        /*
         * Left DAC to left output mixer, LINPUT3 left output mixer volume = 0dB
         */
        wm8960_write_reg(dev, WM8960_LOUTMIX, 0x100);

        /*
         * Right DAC to right output mixer, RINPUT3 right output mixer volume = 0dB
         */
        wm8960_write_reg(dev, WM8960_ROUTMIX, 0x100);
        wm8960_write_reg(dev, WM8960_POWER3, 0x0C);
        /* Set power for DAC */
        WM8960_SetModule(dev, kWM8960_ModuleDAC, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleOMIX, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleLineOut, RT_TRUE);
        break;
    case kWM8960_RoutePlaybackandRecord:
        /*
         * Left DAC to left output mixer, LINPUT3 left output mixer volume = 0dB
         */
        wm8960_write_reg(dev, WM8960_LOUTMIX, 0x100);

        /*
         * Right DAC to right output mixer, RINPUT3 right output mixer volume = 0dB
         */
        wm8960_write_reg(dev, WM8960_ROUTMIX, 0x100);
        wm8960_write_reg(dev, WM8960_POWER3, 0x3C);
        WM8960_SetModule(dev, kWM8960_ModuleDAC, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleADC, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleLineIn, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleOMIX, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleLineOut, RT_TRUE);
        break;
    case kWM8960_RouteRecord:
        /* LINE_IN->ADC->I2S_OUT */
        /*
         * Left and right input boost, LIN3BOOST and RIN3BOOST = 0dB
         */
        wm8960_write_reg(dev, WM8960_POWER3, 0x30);
        /* Power up ADC and AIN */
        WM8960_SetModule(dev, kWM8960_ModuleLineIn, RT_TRUE);
        WM8960_SetModule(dev, kWM8960_ModuleADC, RT_TRUE);
        break;
    default:
        break;
    }
}

void WM8960_SetLeftInput(struct rt_i2c_bus_device *dev, wm8960_input_t input)
{
    uint16_t val = 0;

    switch (input)
    {
    case kWM8960_InputSingleEndedMic:
        /* Only LMN1 enabled, LMICBOOST to 13db, LMIC2B enabled */
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK | WM8960_POWER1_MICB_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_write_reg(dev, WM8960_LINPATH, 0x138);
        wm8960_write_reg(dev, WM8960_LINVOL, 0x117);
        break;
    case kWM8960_InputDifferentialMicInput2:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK | WM8960_POWER1_MICB_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_write_reg(dev, WM8960_LINPATH, 0x178);
        wm8960_write_reg(dev, WM8960_LINVOL, 0x117);
        break;
    case kWM8960_InputDifferentialMicInput3:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK | WM8960_POWER1_MICB_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_write_reg(dev, WM8960_LINPATH, 0x1B8);
        wm8960_write_reg(dev, WM8960_LINVOL, 0x117);
        break;
    case kWM8960_InputLineINPUT2:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_read_reg(dev,WM8960_INBMIX1, &val);
        val |= 0xE;
        wm8960_write_reg(dev, WM8960_INBMIX1, val);
        break;
    case kWM8960_InputLineINPUT3:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_read_reg(dev,WM8960_INBMIX1, &val);
        val |= 0x70;
        wm8960_write_reg(dev, WM8960_INBMIX1, val);
        break;
    default:
        break;
    }
}

void WM8960_SetRightInput(struct rt_i2c_bus_device *dev, wm8960_input_t input)
{
    uint16_t val = 0;

    switch (input)
    {
    case kWM8960_InputSingleEndedMic:
        /* Only LMN1 enabled, LMICBOOST to 13db, LMIC2B enabled */
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK | WM8960_POWER1_MICB_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_write_reg(dev, WM8960_RINPATH, 0x138);
        wm8960_write_reg(dev, WM8960_RINVOL, 0x117);
        break;
    case kWM8960_InputDifferentialMicInput2:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK | WM8960_POWER1_MICB_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_write_reg(dev, WM8960_RINPATH, 0x178);
        wm8960_write_reg(dev, WM8960_RINVOL, 0x117);
        break;
    case kWM8960_InputDifferentialMicInput3:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK | WM8960_POWER1_MICB_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_write_reg(dev, WM8960_RINPATH, 0x1B8);
        wm8960_write_reg(dev, WM8960_RINVOL, 0x117);
        break;
    case kWM8960_InputLineINPUT2:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_read_reg(dev,WM8960_INBMIX2, &val);
        val |= 0xE;
        wm8960_write_reg(dev, WM8960_INBMIX2, val);
        break;
    case kWM8960_InputLineINPUT3:
        wm8960_read_reg(dev,WM8960_POWER1, &val);
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK);
        wm8960_write_reg(dev, WM8960_POWER1, val);
        wm8960_read_reg(dev,WM8960_INBMIX2, &val);
        val |= 0x70;
        wm8960_write_reg(dev, WM8960_INBMIX2, val);
        break;
    default:
        break;
    }
}

void WM8960_SetProtocol(struct rt_i2c_bus_device *dev, wm8960_protocol_t protocol)
{
    wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_FORMAT_MASK | WM8960_IFACE1_LRP_MASK, protocol);
}

void WM8960_SetVolume(struct rt_i2c_bus_device *dev, wm8960_module_t module, rt_uint32_t volume)
{
    uint16_t vol = 0;
    switch (module)
    {
    case kWM8960_ModuleADC:
        vol = volume;
        wm8960_write_reg(dev, WM8960_LADC, vol);
        wm8960_write_reg(dev, WM8960_RADC, vol);
        /* Update volume */
        vol = 0x100 | volume;
        wm8960_write_reg(dev, WM8960_LADC, vol);
        wm8960_write_reg(dev, WM8960_RADC, vol);
        break;
    case kWM8960_ModuleDAC:
        vol = volume;
        wm8960_write_reg(dev, WM8960_LDAC, vol);
        wm8960_write_reg(dev, WM8960_RDAC, vol);
        vol = 0x100 | volume;
        wm8960_write_reg(dev, WM8960_LDAC, vol);
        wm8960_write_reg(dev, WM8960_RDAC, vol);
        break;
    case kWM8960_ModuleHP:
        vol = volume;
        wm8960_write_reg(dev, WM8960_LOUT1, vol);
        wm8960_write_reg(dev, WM8960_ROUT1, vol);
        vol = 0x100 | volume;
        wm8960_write_reg(dev, WM8960_LOUT1, vol);
        wm8960_write_reg(dev, WM8960_ROUT1, vol);
        break;
    case kWM8960_ModuleLineIn:
        vol = volume;
        wm8960_write_reg(dev, WM8960_LINVOL, vol);
        wm8960_write_reg(dev, WM8960_RINVOL, vol);
        vol = 0x100 | volume;
        wm8960_write_reg(dev, WM8960_LINVOL, vol);
        wm8960_write_reg(dev, WM8960_RINVOL, vol);
        break;
    case kWM8960_ModuleSpeaker:
        vol = volume;
        wm8960_write_reg(dev, WM8960_LOUT2, vol);
        wm8960_write_reg(dev, WM8960_ROUT2, vol);
        vol = 0x100 | volume;
        wm8960_write_reg(dev, WM8960_LOUT2, vol);
        wm8960_write_reg(dev, WM8960_ROUT2, vol);
        break;
    default:
        break;
    }
}

rt_uint32_t WM8960_GetVolume(struct rt_i2c_bus_device *dev, wm8960_module_t module)
{
    uint16_t vol = 0;
    switch (module)
    {
    case kWM8960_ModuleADC:
        wm8960_read_reg(dev,WM8960_LADC, &vol);
        vol &= 0xFF;
        break;
    case kWM8960_ModuleDAC:
        wm8960_read_reg(dev,WM8960_LDAC, &vol);
        vol &= 0xFF;
        break;
    case kWM8960_ModuleHP:
        wm8960_read_reg(dev,WM8960_LOUT1, &vol);
        vol &= 0x7F;
        break;
    case kWM8960_ModuleLineOut:
        wm8960_read_reg(dev,WM8960_LINVOL, &vol);
        vol &= 0x3F;
        break;
    default:
        vol = 0;
        break;
    }
    return vol;
}

void WM8960_SetMute(struct rt_i2c_bus_device *dev, wm8960_module_t module, rt_bool_t isEnabled)
{
    switch (module)
    {
    case kWM8960_ModuleADC:
        /*
         * Digital Mute
         */
        if (isEnabled)
        {
            wm8960_write_reg(dev, WM8960_LADC, 0x100);
            wm8960_write_reg(dev, WM8960_RADC, 0x100);
        }
        else
        {
            wm8960_write_reg(dev, WM8960_LADC, 0x1C3);
            wm8960_write_reg(dev, WM8960_RADC, 0x1C3);
        }
        break;
    case kWM8960_ModuleDAC:
        /*
         * Digital mute
         */
        if (isEnabled)
        {
            wm8960_write_reg(dev, WM8960_LDAC, 0x100);
            wm8960_write_reg(dev, WM8960_RDAC, 0x100);
        }
        else
        {
            wm8960_write_reg(dev, WM8960_LDAC, 0x1FF);
            wm8960_write_reg(dev, WM8960_RDAC, 0x1FF);
        }
        break;
    case kWM8960_ModuleHP:
        /*
         * Analog mute
         */
        if (isEnabled)
        {
            wm8960_write_reg(dev, WM8960_LOUT1, 0x100);
            wm8960_write_reg(dev, WM8960_ROUT1, 0x100);
        }
        else
        {
            wm8960_write_reg(dev, WM8960_LOUT1, 0x16F);
            wm8960_write_reg(dev, WM8960_ROUT1, 0x16F);
        }
        break;

    case kWM8960_ModuleSpeaker:
        if (isEnabled)
        {
            wm8960_write_reg(dev, WM8960_LOUT2, 0x100);
            wm8960_write_reg(dev, WM8960_ROUT2, 0x100);
        }
        else
        {
            wm8960_write_reg(dev, WM8960_LOUT2, 0x16F);
            wm8960_write_reg(dev, WM8960_ROUT2, 0x16f);
        }
        break;

    case kWM8960_ModuleLineOut:
        break;
    default:
        break;
    }
}

void WM8960_ConfigDataFormat(struct rt_i2c_bus_device *dev, rt_uint32_t sysclk, rt_uint32_t sample_rate, rt_uint32_t bits)
{
    uint32_t divider = 0;
    uint16_t val     = 0;

    /* Compute sample rate divider, dac and adc are the same sample rate */
    divider = sysclk / sample_rate;
    if (divider == 256)
    {
        val = 0;
    }
    if (divider > 256)
    {
        val = (((divider / 256U) << 6U) | ((divider / 256U) << 3U));
    }

    wm8960_write_reg(dev, WM8960_CLOCK1, val);

    /* Compute bclk divider */
    divider /= bits * 2;
    switch (divider)
    {
    case 4:
    case 5:
    case 6:
        val = (0x1C0 | divider);
        break;
    case 8:
        val = 0x1C7;
        break;
    case 11:
        val = 0x1C8;
        break;
    case 12:
        val = 0x1C9;
        break;
    case 16:
        val = 0x1CA;
        break;
    case 22:
        val = 0x1CB;
        break;
    case 24:
        val = 0x1CC;
        break;
    case 32:
        val = 0x1CF;
        break;
    default:
        break;

    }

    wm8960_write_reg(dev, WM8960_CLOCK2, val);
    /*
     * Slave mode (MS = 0), LRP = 0, 32bit WL, left justified (FORMAT[1:0]=0b01)
     */
    switch (bits)
    {
    case 16:
        wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_WL_MASK,
                          WM8960_IFACE1_WL(WM8960_IFACE1_WL_16BITS));
        break;
    case 20:
        wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_WL_MASK,
                          WM8960_IFACE1_WL(WM8960_IFACE1_WL_20BITS));
        break;
    case 24:
        wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_WL_MASK,
                          WM8960_IFACE1_WL(WM8960_IFACE1_WL_24BITS));
        break;
    case 32:
        wm8960_modify_reg(dev, WM8960_IFACE1, WM8960_IFACE1_WL_MASK,
                          WM8960_IFACE1_WL(WM8960_IFACE1_WL_32BITS));
        break;
    default:
        break;
    }
}

void WM8960_Deinit(struct rt_i2c_bus_device *dev)
{
    WM8960_SetModule(dev, kWM8960_ModuleADC, RT_FALSE);
    WM8960_SetModule(dev, kWM8960_ModuleDAC, RT_FALSE);
    WM8960_SetModule(dev, kWM8960_ModuleVREF, RT_FALSE);
    WM8960_SetModule(dev, kWM8960_ModuleLineIn, RT_FALSE);
    WM8960_SetModule(dev, kWM8960_ModuleLineOut, RT_FALSE);
    WM8960_SetModule(dev, kWM8960_ModuleSpeaker, RT_FALSE);
}

void WM8960_init(struct rt_i2c_bus_device *dev, wm8960_config_t *wm8960Config)
{
    wm8960_config_t *config = wm8960Config;
    rt_memcpy(reg_cache, wm8960_regval_tbl, sizeof(wm8960_regval_tbl));
    /* Reset the codec */
    wm8960_write_reg(dev, WM8960_RESET, 0x00);
    /*
     * VMID=50K, Enable VREF, AINL, AINR, ADCL and ADCR
     * I2S_IN (bit 0), I2S_OUT (bit 1), DAP (bit 4), DAC (bit 5), ADC (bit 6) are powered on
     */
    wm8960_write_reg(dev, WM8960_POWER1, 0xFE);
    /*
     * Enable DACL, DACR, LOUT1, ROUT1, PLL down
     */
    wm8960_write_reg(dev, WM8960_POWER2, 0x1E0);
    /*
     * Enable left and right channel input PGA, left and right output mixer
     */
    wm8960_write_reg(dev, WM8960_POWER3, 0x3C);
    /* ADC and DAC uses same clock */
    wm8960_write_reg(dev, WM8960_IFACE2, 0x40);
    /* set data route */
    WM8960_SetDataRoute(dev, config->route);
    /* set data protocol */
    WM8960_SetProtocol(dev, config->bus);
    /* set master or slave */
    WM8960_SetMasterSlave(dev, config->master_slave);
    /* select left input */
    WM8960_SetLeftInput(dev, config->leftInputSource);
    /* select right input */
    WM8960_SetRightInput(dev, config->rightInputSource);
    /* speaker power */
    if (config->enableSpeaker)
    {
        WM8960_SetModule(dev, kWM8960_ModuleSpeaker, RT_TRUE);
    }
    wm8960_write_reg(dev, WM8960_ADDCTL1, 0x0C0);
    wm8960_write_reg(dev, WM8960_ADDCTL4, 0x40);

    wm8960_write_reg(dev, WM8960_BYPASS1, 0x0);
    wm8960_write_reg(dev, WM8960_BYPASS2, 0x0);
    /*
     * ADC volume, 0dB
     */
    wm8960_write_reg(dev, WM8960_LADC, 0x1C3);
    wm8960_write_reg(dev, WM8960_RADC, 0x1C3);

    /*
     * Digital DAC volume, 0dB
     */
    wm8960_write_reg(dev, WM8960_LDAC, 0x1E0);
    wm8960_write_reg(dev, WM8960_RDAC, 0x1E0);

    /*
     * Headphone volume, LOUT1 and ROUT1, 0dB
     */
    wm8960_write_reg(dev, WM8960_LOUT1, 0x16F);
    wm8960_write_reg(dev, WM8960_ROUT1, 0x16F);

    /* Unmute DAC. */
    wm8960_write_reg(dev, WM8960_DACCTL1, 0x0000);
    wm8960_write_reg(dev, WM8960_LINVOL, 0x117);
    wm8960_write_reg(dev, WM8960_RINVOL, 0x117);

    WM8960_ConfigDataFormat(dev, config->format.mclk_HZ, config->format.sampleRate, config->format.bitWidth);
}
void WM8960_SetPlay(struct rt_i2c_bus_device *dev, uint32_t playSource)
{
    if (kWM8960_PlaySourcePGA & playSource)
    {
        wm8960_modify_reg(dev, WM8960_BYPASS1, 0x80U, 0x80U);
        wm8960_modify_reg(dev, WM8960_BYPASS2, 0x80U, 0x80U);
        wm8960_modify_reg(dev, WM8960_LOUTMIX, 0x180U, 0U);
        wm8960_modify_reg(dev, WM8960_ROUTMIX, 0x180U, 0U);
    }

    if (playSource & kWM8960_PlaySourceDAC)
    {
        wm8960_modify_reg(dev, WM8960_BYPASS1, 0x80U, 0x00U);
        wm8960_modify_reg(dev, WM8960_BYPASS2, 0x80U, 0x00U);
        wm8960_modify_reg(dev, WM8960_LOUTMIX, 0x180U, 0x100U);
        wm8960_modify_reg(dev, WM8960_ROUTMIX, 0x180U, 0x100U);
    }

    if (playSource & kWM8960_PlaySourceInput)
    {
        wm8960_modify_reg(dev, WM8960_BYPASS1, 0x80U, 0x0U);
        wm8960_modify_reg(dev, WM8960_BYPASS2, 0x80U, 0x0U);
        wm8960_modify_reg(dev, WM8960_LOUTMIX, 0x180U, 0x80U);
        wm8960_modify_reg(dev, WM8960_ROUTMIX, 0x180U, 0x80U);
    }
}
