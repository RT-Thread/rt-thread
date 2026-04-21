/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_EADC)

#include "NuMicro.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.eadc"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define CONFIG_MAX_CHN_NUM  EADC_CH_NUM
#define DEFINE_NU_EADC(_idx)             \
    {                                    \
        .name = "eadc" #_idx,           \
        .base = EADC##_idx,              \
        .conv_power = 1,                 \
        .chn_msk = 0,                    \
        .max_chn_num = CONFIG_MAX_CHN_NUM, \
    }

/* Types / Structures ---------------------------------------------------------*/
enum
{
    EADC_START = -1,
#if defined(BSP_USING_EADC0) && defined(EADC0)
    EADC0_IDX,
#endif
    EADC_CNT
};

enum
{
    EADC_CH_0,
    EADC_CH_1,
    EADC_CH_2,
    EADC_CH_3,
    EADC_CH_4,
    EADC_CH_5,
    EADC_CH_6,
    EADC_CH_7,
    EADC_CH_8,
    EADC_CH_9,
    EADC_CH_10,
    EADC_CH_11,
    EADC_CH_12,
    EADC_CH_13,
    EADC_CH_14,
    EADC_CH_15,
    EADC_CH_VBG,        // 16, Band-gap voltage
    EADC_CH_VTEMP,      // 17, Internal Temperature sensor
    EADC_CH_AVDD_DIV4,  // 18, AVDD/4
    EADC_CH_NUM
};

struct nu_eadc
{
    struct rt_adc_device dev;
    char       *name;
    EADC_T     *base;
    uint32_t    conv_power;
    uint32_t    chn_msk;
    uint32_t    max_chn_num;
};
typedef struct nu_eadc *nu_eadc_t;

/* Static Function Prototypes ------------------------------------------------*/
static rt_err_t nu_eadc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled);
static rt_err_t nu_eadc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value);
static rt_uint8_t nu_eadc_get_resolution(struct rt_adc_device *device);
static rt_int16_t nu_eadc_get_vref(struct rt_adc_device *device);

/* Static Variables ----------------------------------------------------------*/
static struct nu_eadc nu_eadc_arr [] =
{
#if defined(BSP_USING_EADC0) && defined(EADC0)
    DEFINE_NU_EADC(0),
#endif
};

static const struct rt_adc_ops nu_adc_ops =
{
    .enabled = nu_eadc_enabled,
    .convert = nu_eadc_convert,
    .get_resolution = nu_eadc_get_resolution,
    .get_vref = nu_eadc_get_vref
};
typedef struct rt_adc_ops *rt_adc_ops_t;

static rt_uint32_t s_u32BuiltInBandGapValue = 0;

/* Functions Implementation --------------------------------------------------*/
static rt_uint8_t nu_eadc_get_resolution(struct rt_adc_device *device)
{
    return 12; /* 12-bit */
}

static rt_err_t nu_eadc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    nu_eadc_t psNuEADC = (nu_eadc_t)device;

    RT_ASSERT(device);

    if (channel >= psNuEADC->max_chn_num)
        return -(RT_EINVAL);

    if (enabled)
    {
        if (psNuEADC->chn_msk == 0)
        {
            EADC_Open(psNuEADC->base, EADC_CTL_DIFFEN_SINGLE_END);
        }

        switch (channel)
        {
        case EADC_CH_AVDD_DIV4:
            /* Enable AVDD/4 */
            SYS->IVSCTL |= SYS_IVSCTL_AVDDDIV4EN_Msk;
            break;

        case EADC_CH_VBG:
            /* Force to enable internal voltage band-gap. */
            SYS->VREFCTL |= SYS_VREFCTL_VBGFEN_Msk;
            break;

        case EADC_CH_VTEMP:
            /* Enable temperature sensor */
            SYS->IVSCTL |= SYS_IVSCTL_VTEMPEN_Msk;
            break;

        default:
            break;
        }

        psNuEADC->chn_msk |= (0x1 << channel);
    }
    else
    {
        psNuEADC->chn_msk &= ~(0x1 << channel);

        switch (channel)
        {
        case EADC_CH_AVDD_DIV4:
            /* Disable AVDD/4 */
            SYS->IVSCTL &= ~SYS_IVSCTL_AVDDDIV4EN_Msk;
            break;

        case EADC_CH_VBG:
            /* Force to enable internal voltage band-gap. */
            SYS->VREFCTL &= ~SYS_VREFCTL_VBGFEN_Msk;
            break;

        case EADC_CH_VTEMP:
            /* Disable temperature sensor */
            SYS->IVSCTL &= ~SYS_IVSCTL_VTEMPEN_Msk;
            break;

        default:
            break;
        }

        if (psNuEADC->chn_msk == 0)
        {
            EADC_Close(psNuEADC->base);
        }
    }

    return RT_EOK;
}

static rt_uint32_t _eadc_convert(nu_eadc_t psNuEADC, rt_uint32_t channel)
{
#define CONFIG_CONV_INTSEL             0
#define CONFIG_EXT_SMPL_TIME           0xff
#define CONFIG_SMPL_MODULE_ACU_TIMES   (psNuEADC->conv_power << EADC_MCTL1_ACU_Pos)

    rt_uint32_t u32ConvValue, u32ModuleNum;

    if (nu_eadc_enabled((struct rt_adc_device *)psNuEADC, channel, RT_TRUE) != RT_EOK)
    {
        return 0xFFFFFFFF;
    }

    u32ModuleNum = channel;

    /* Configure the sample module for analog input channel and software trigger source. */
    EADC_ConfigSampleModule(psNuEADC->base, u32ModuleNum, EADC_SOFTWARE_TRIGGER, channel);

    /* Set sample module external sampling time to 0xF */
    EADC_SetExtendSampleTime(psNuEADC->base, u32ModuleNum, CONFIG_EXT_SMPL_TIME);

    /* Enable Accumulate feature */
    EADC_ENABLE_ACU(psNuEADC->base, u32ModuleNum, CONFIG_SMPL_MODULE_ACU_TIMES);

    /* Enable Average feature */
    EADC_ENABLE_AVG(psNuEADC->base, u32ModuleNum);

    /* Clear the A/D ADINT0 interrupt flag for safe */
    EADC_CLR_INT_FLAG(psNuEADC->base, EADC_STATUS2_ADIF0_Msk);

    /* Enable the sample module interrupt. */
    EADC_ENABLE_INT(psNuEADC->base, (1 << CONFIG_CONV_INTSEL));
    EADC_ENABLE_SAMPLE_MODULE_INT(psNuEADC->base, CONFIG_CONV_INTSEL, (1 << u32ModuleNum));

    EADC_START_CONV(psNuEADC->base, (1 << u32ModuleNum));
    while (EADC_GET_INT_FLAG(psNuEADC->base, (1 << CONFIG_CONV_INTSEL)) == 0);

    /* Disable the sample module interrupt. */
    EADC_DISABLE_INT(psNuEADC->base, (1 << CONFIG_CONV_INTSEL));

    /* Disable Average feature */
    EADC_DISABLE_AVG(psNuEADC->base, u32ModuleNum);

    /* Disable Accumulate feature */
    EADC_DISABLE_ACU(psNuEADC->base, u32ModuleNum);

    u32ConvValue = EADC_GET_CONV_DATA(psNuEADC->base, u32ModuleNum);

    //rt_kprintf("u32ConvValue: %08x\n", u32ConvValue);

    return u32ConvValue;
}

static rt_int16_t nu_eadc_get_vref(struct rt_adc_device *device)
{
    rt_uint32_t u32VBG;

    RT_ASSERT(device);

    u32VBG = _eadc_convert((nu_eadc_t)device, EADC_CH_VBG); // VBG Channel

    /* Use Conversion result of Band-gap to calculating AVdd */
    /*
      u16Vref    s_u32BuiltInBandGapValue
    ---------- = -------------------------
       3072          i32ConversionData
    */
    // rt_kprintf("u32VBG: %d, AVDD: %d\n", u32VBG, 3072 * s_u32BuiltInBandGapValue / u32VBG);

    return (3072 * s_u32BuiltInBandGapValue / u32VBG);
}

static rt_err_t nu_eadc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    nu_eadc_t psNuEADC = (nu_eadc_t)device;
    rt_err_t ret = RT_ERROR;

    RT_ASSERT(device);
    RT_ASSERT(value);

    if (channel >= psNuEADC->max_chn_num)
    {
        *value = 0xFFFFFFFF;
        ret = RT_EINVAL;
        goto exit_nu_eadc_convert;
    }

    if ((psNuEADC->chn_msk & (1 << channel)) == 0)
    {
        *value = 0xFFFFFFFF;
        ret = RT_EBUSY;
        goto exit_nu_eadc_convert;
    }

    *value = _eadc_convert(psNuEADC, channel);

    ret = RT_EOK;

exit_nu_eadc_convert:

    return -(ret);
}

int rt_hw_eadc_init(void)
{
    int i;
    rt_err_t result;

    /* Invoke ISP function to read built-in band-gap A/D conversion result*/
    FMC_Open();
    s_u32BuiltInBandGapValue = FMC_ReadBandGap();
    FMC_Close();

    //rt_kprintf("s_u32BuiltInBandGapValue: %d\n", s_u32BuiltInBandGapValue);

    for (i = (EADC_START + 1); i < EADC_CNT; i++)
    {
        result = rt_hw_adc_register(&nu_eadc_arr[i].dev, nu_eadc_arr[i].name, &nu_adc_ops, NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_eadc_init);
#endif //#if defined(BSP_USING_EADC)
