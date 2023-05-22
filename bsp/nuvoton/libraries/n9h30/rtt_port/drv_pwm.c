/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-1       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_PWM)

#define LOG_TAG                 "drv.pwm"
#define DBG_ENABLE
#define DBG_SECTION_NAME        "drv.pwm"
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <stdint.h>
#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"
#include "drv_sys.h"

enum
{
    PWM_START = -1,
#if defined(BSP_USING_PWM0)
    PWM0_IDX,
#endif
    PWM_CNT
};

#define NU_PWM_BA_DISTANCE    0
#define NU_PWM_CHANNEL_NUM    4

struct nu_pwm
{
    struct rt_device_pwm dev;
    char *name;
    uint32_t base_addr;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
};

typedef struct nu_pwm *nu_pwm_t;

static struct nu_pwm nu_pwm_arr [] =
{
#if defined(BSP_USING_PWM0)
    {
        .name = "pwm0",
        .base_addr = PWM_BA,
        .rstidx = PWMRST,
        .clkidx = PWMCKEN,
    },
#endif

}; /* pwm nu_pwm */

static rt_err_t nu_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops nu_pwm_ops =
{
    .control = nu_pwm_control
};

static rt_err_t nu_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *config, rt_bool_t enable)
{
    nu_pwm_t psNuPWM = (nu_pwm_t)device;

    rt_err_t result = RT_EOK;
    rt_uint32_t ch = config->channel;

    if (enable == RT_TRUE)
    {
        uint32_t u32RegAdrrPCR = psNuPWM->base_addr + 0x8;
        uint32_t u32PCRChAlign = (!ch) ? 0x9 : (0x9 << (4 + ch * 4));

        /* Period and enable channel. */
        outpw(u32RegAdrrPCR, inpw(u32RegAdrrPCR) | u32PCRChAlign);
    }
    else
    {
        uint32_t u32RegAdrrPCR = psNuPWM->base_addr + 0x8;
        uint32_t u32PCRChAlign = (!ch) ? 0x1 : (0x1 << (4 + ch * 4));

        outpw(u32RegAdrrPCR, inpw(u32RegAdrrPCR) & ~u32PCRChAlign);
    }

    return result;
}

static rt_err_t nu_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *config)
{
    nu_pwm_t psNuPWM = (nu_pwm_t)device;
    uint32_t u32RegAdrrPPR = psNuPWM->base_addr;
    uint32_t u32RegAdrrCSR = psNuPWM->base_addr + 0x04;
    uint32_t u32RegAdrrCNR = psNuPWM->base_addr + 0xC + (config->channel * 0xC);
    uint32_t u32RegAdrrCMR = psNuPWM->base_addr + 0x10 + (config->channel * 0xC);
    uint32_t u32PWMSrcClk   = sysGetClock(SYS_PCLK) * 1000000;
    uint32_t u32CMR, u32CNR;
    double douDutyCycle; /* unit:% */
    uint32_t u32PWMOutClk;  /* unit:Hz */
    uint32_t u32Prescale, u32Divider;

    u32CNR = inpw(u32RegAdrrCNR) + 1;
    u32CMR = inpw(u32RegAdrrCMR) + 1;
    u32Prescale = ((inpw(u32RegAdrrPPR) & (0xff << ((config->channel >> 1) * 8))) >> ((config->channel >> 1) * 8)) + 1;
    u32Divider  = (inpw(u32RegAdrrCSR) & (0x7 << (4 * config->channel))) >> (4 * config->channel);

    /* Re-convert register to real value */
    if (u32Divider == 4)
        u32Divider = 1;
    else if (u32Divider == 0)
        u32Divider = 2;
    else if (u32Divider == 1)
        u32Divider = 4;
    else if (u32Divider == 2)
        u32Divider = 8;
    else // 3
        u32Divider = 16;

    douDutyCycle = (double)u32CMR / u32CNR;

    u32PWMOutClk = u32PWMSrcClk / (u32Prescale * u32Divider * u32CNR);

    config->period = 1000000000 / u32PWMOutClk;   /* In ns. */
    config->pulse  = douDutyCycle * config->period;

    LOG_I("%s %d %d %d\n", ((nu_pwm_t)device)->name, config->channel, config->period, config->pulse);

    return RT_EOK;
}

uint32_t nu_pwm_config(uint32_t u32PwmBaseAddr, uint32_t u32ChannelNum, uint32_t u32Frequency, uint32_t u32PulseInHz)
{
    uint32_t i;
    uint8_t  u8Divider = 1, u8Prescale = 0xFF;
    uint16_t u16CNR = 0xFFFF;
    uint16_t u16CMR = 0xFFFF;
    uint32_t u32RegAdrrPPR = u32PwmBaseAddr;
    uint32_t u32RegAdrrCSR = u32PwmBaseAddr + 0x04;
    uint32_t u32RegAdrrCNR = u32PwmBaseAddr + 0xC + (u32ChannelNum * 0xC);
    uint32_t u32RegAdrrCMR = u32PwmBaseAddr + 0x10 + (u32ChannelNum * 0xC);
    uint32_t u32PWMSrcClk  = sysGetClock(SYS_PCLK) * 1000000;
    uint32_t u32PWMOutClk  = 0;

    if (u32Frequency > u32PWMSrcClk)
        return 0;

    /*
      PWM_Freq = PCLK2 / (Prescale+1) / (Clock Divider) / (CNR+1)
      PCLK / PWM_Freq = (Prescale+1) * (Clock Divider) * (CNR+1)
      PCLK / PWM_Freq / (Clock Divider) = (Prescale+1) * (CNR+1)
    */

    /* clk divider could only be 1, 2, 4, 8, 16 */
    for (; u8Divider < 17; u8Divider <<= 1)
    {
        i = (u32PWMSrcClk / u32Frequency) / u8Divider;

        /* If target value is larger than CNR * prescale, need to use a larger divider */
        if (i > (0x10000 * 0x100))
            continue;

        /* CNR = 0xFFFF + 1, get a prescaler that CNR value is below 0xFFFF */
        u8Prescale = (i + 0xFFFF) / 0x10000;

        /* u8Prescale must at least be 2, otherwise the output stop */
        if (u8Prescale < 2)
            u8Prescale = 2;

        i /= u8Prescale;
        if (i < 0x10000)
        {
            if (i == 1)
                u16CNR = 1;     // Too fast, and PWM cannot generate expected frequency...
            else
                u16CNR = i;

            break;
        }
    }

    u32PWMOutClk = u32PWMSrcClk / (u8Prescale * u8Divider * u16CNR);

    /* For fill into registers. */
    u8Prescale -= 1;
    u16CNR -= 1;

    /* Convert to real register value */
    if (u8Divider == 1)
        u8Divider = 4;
    else if (u8Divider == 2)
        u8Divider = 0;
    else if (u8Divider == 4)
        u8Divider = 1;
    else if (u8Divider == 8)
        u8Divider = 2;
    else // 16
        u8Divider = 3;

    /* Every two channels share a prescaler */
    outpw(u32RegAdrrPPR, (inpw(u32RegAdrrPPR) & ~(0xff << ((u32ChannelNum >> 1) * 8))) | (u8Prescale << ((u32ChannelNum >> 1) * 8)));

    /* Update CLKSEL in specified channel in CSR field. */
    outpw(u32RegAdrrCSR, inpw(u32RegAdrrCSR) & ~(0x7 << (4 * u32ChannelNum)) | (u8Divider << (4 * u32ChannelNum)));

    u16CMR = u32Frequency * (u16CNR + 1) / u32PulseInHz;

    outpw(u32RegAdrrCMR, (u16CMR == 0) ? 0 : u16CMR - 1);
    outpw(u32RegAdrrCNR, u16CNR);

    return (u32PWMOutClk);
}

static rt_err_t nu_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *config)
{
    nu_pwm_t psNuPWM = (nu_pwm_t)device;
    rt_err_t result = -RT_EINVAL;
    rt_uint32_t u32FreqInHz;   /* unit:Hz */
    rt_uint32_t u32PulseInHz;   /* unit:% */

    if (config->period < 1000 || !config->period || !config->pulse)
        goto exit_nu_pwm_set;

    /* Calculate frequency, Unit is in us. */
    u32FreqInHz = (1000000000) / config->period;
    u32PulseInHz = (1000000000) / config->pulse;

    nu_pwm_config(psNuPWM->base_addr, config->channel, u32FreqInHz, u32PulseInHz);

    result = RT_EOK;

exit_nu_pwm_set:

    return -(result);
}

static rt_err_t nu_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *config = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    if (config->channel > NU_PWM_CHANNEL_NUM)
        return -(RT_EINVAL);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return nu_pwm_enable(device, config, RT_TRUE);
    case PWM_CMD_DISABLE:
        return nu_pwm_enable(device, config, RT_FALSE);
    case PWM_CMD_SET:
        return nu_pwm_set(device, config);
    case PWM_CMD_GET:
        return nu_pwm_get(device, config);
    default:
        break;
    }

    return -(RT_ERROR);
}

int rt_hw_pwm_init(void)
{
    rt_err_t ret;
    int i;

    for (i = (PWM_START + 1); i < PWM_CNT; i++)
    {
        nu_sys_ipclk_enable(nu_pwm_arr[i].clkidx);

        nu_sys_ip_reset(nu_pwm_arr[i].rstidx);

        ret = rt_device_pwm_register(&nu_pwm_arr[i].dev, nu_pwm_arr[i].name, &nu_pwm_ops, RT_NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif
