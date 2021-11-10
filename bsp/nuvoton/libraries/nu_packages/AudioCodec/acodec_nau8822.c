/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_NAU8822)

#include <rtthread.h>
#include <rtdevice.h>

#include "acodec_nau8822.h"
#include "drv_i2s.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "acodec.nau8822"
#define DBG_COLOR
#include <rtdbg.h>

#define DEF_NAU8822_ADDR    0x1A

static struct rt_i2c_bus_device *g_I2cBusDev = NULL;
S_NU_NAU8822_CONFIG *g_psCodecConfig = NULL;

static rt_err_t nau8822_init(void);
static rt_err_t nau8822_reset(void);
static rt_err_t nau8822_dsp_control(struct rt_audio_configure *config);
static rt_err_t nau8822_mixer_control(rt_uint32_t ui32Units, rt_uint32_t ui32Value);
static rt_err_t nau8822_mixer_query(rt_uint32_t ui32Units, rt_uint32_t *ui32Value);

nu_acodec_ops nu_acodec_ops_nau8822 =
{
    .name = "NAU8822",
    .role = NU_ACODEC_ROLE_MASTER,
    .config = { // Default settings.
        .samplerate = 16000,
        .channels = 2,
        .samplebits = 16
    },
    .nu_acodec_init = nau8822_init,
    .nu_acodec_reset = nau8822_reset,

    .nu_acodec_dsp_control = nau8822_dsp_control,
    .nu_acodec_mixer_control = nau8822_mixer_control,
    .nu_acodec_mixer_query = nau8822_mixer_query
};

static void nau8822_delay_ms(rt_uint32_t nms)
{
    rt_thread_mdelay(nms);
}

static int I2C_ReadNAU8822(uint8_t u8addr, uint16_t *pu16data)
{
    struct rt_i2c_msg msgs[2];
    uint8_t u8TxData = (u8addr << 1);

    RT_ASSERT(g_I2cBusDev != NULL);
    RT_ASSERT(pu16data != NULL);

    msgs[0].addr  = DEF_NAU8822_ADDR;         /* Slave address */
    msgs[0].flags = RT_I2C_WR;                /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)&u8TxData;  /* Number of bytes sent */
    msgs[0].len   = sizeof(u8TxData);         /* Number of bytes read */

    msgs[1].addr  = DEF_NAU8822_ADDR;         /* Slave address */
    msgs[1].flags = RT_I2C_RD;                /* Read flag */
    msgs[1].buf   = (rt_uint8_t *)pu16data;   /* Read data pointer */
    msgs[1].len   = 2;                        /* Number of bytes read */

    if (rt_i2c_transfer(g_I2cBusDev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int I2C_WriteNAU8822(uint8_t u8addr, uint16_t u16data)
{
    /* Write 9-bit data to 7-bit address register of NAU8822 */
    struct rt_i2c_msg msg;
    uint8_t au8TxData[2];

    RT_ASSERT(g_I2cBusDev != NULL);

    au8TxData[0] = (uint8_t)((u8addr << 1) | (u16data >> 8));  //u8addr [7:1] | u16data [8]
    au8TxData[1] = (uint8_t)(u16data & 0x00FF);         //data [7:0]

    msg.addr  = DEF_NAU8822_ADDR;                /* Slave address */
    msg.flags = RT_I2C_WR;                       /* Write flag */
    msg.buf   = (rt_uint8_t *)&au8TxData[0];     /* Slave register address */
    msg.len   = sizeof(au8TxData);               /* Number of bytes sent */

    if (g_I2cBusDev && rt_i2c_transfer(g_I2cBusDev, &msg, 1) != 1)
    {
        rt_kprintf("[Failed] addr=%x, data=%d\n", u8addr, u16data);
        return -RT_ERROR;
    }

    {
        /* Verify */
        uint8_t au8RxData[2];
        I2C_ReadNAU8822(u8addr, (uint16_t *)&au8RxData[0]);
        rt_kprintf("Wrote addr %02x -> 0x%04x, read back -> 0x%02x%02x\n", u8addr, u16data, au8RxData[0], au8RxData[1]);
    }

    return RT_EOK;
}

static void nau8822_phonejack_set(S_NU_NAU8822_CONFIG *psCodecConfig, int bEnable)
{
    rt_pin_mode(psCodecConfig->pin_phonejack_en, PIN_MODE_OUTPUT);

    if (bEnable)
    {
        rt_pin_write(psCodecConfig->pin_phonejack_en, PIN_LOW);
    }
    else
    {
        rt_pin_write(psCodecConfig->pin_phonejack_en, PIN_HIGH);
    }
}


static rt_err_t nau8822_probe(void)
{
    return RT_EOK;
}

static rt_err_t nau8822_reset(void)
{
    I2C_WriteNAU8822(0,  0x000);   /* Reset all registers */
    nau8822_delay_ms(30);

    LOG_I("Software Reset.\n");

    return RT_EOK;
}

static rt_err_t nau8822_dsp_config(rt_uint32_t ui32SamplRate, rt_uint8_t u8ChNum, rt_uint8_t u8SamplBit)
{
    uint8_t   bClkDiv;
    uint8_t   mClkDiv;
    uint16_t  u16AudIf = 0x010; /* I2S, 16-bit */
    uint16_t  u16ClkCtrl;
    uint8_t   u8WLEN;

    if (ui32SamplRate > 48000)
        return -RT_ERROR;

    if (u8ChNum == 2)
    {
        u16AudIf = (u16AudIf & 0x1FE) | 0x0;
    }
    else
    {
        u16AudIf = (u16AudIf & 0x1FE) | 0x1;
    }

    /* Force to set Channel number to 2 */
    u8ChNum = 2;

    switch (u8SamplBit)
    {
    case 16:
        u8WLEN = 0x0;
        break;

    case 20:
        u8WLEN = 0x1;
        break;

    case 24:
        u8WLEN = 0x2;
        break;

    case 32:
        u8WLEN = 0x3;
        break;

    default:
        LOG_E("sample rate not match!\n");
        return -RT_ERROR;
    }
    u16AudIf = (u16AudIf & 0x19F) | (u8WLEN << 5);

    if (ui32SamplRate % 11025)
    {
        I2C_WriteNAU8822(36, 0x008);    //12.288Mhz
        I2C_WriteNAU8822(37, 0x00C);
        I2C_WriteNAU8822(38, 0x093);
        I2C_WriteNAU8822(39, 0x0E9);

        /* FIXME */
        if (ui32SamplRate > 48000)
            ui32SamplRate = 8000;

        mClkDiv = (48000 * 256 * u8ChNum) / (ui32SamplRate * 256);
        bClkDiv = (ui32SamplRate * 256) / (ui32SamplRate * u8ChNum * u8SamplBit);
    }
    else
    {
        I2C_WriteNAU8822(36, 0x007);    //11.2896Mhz
        I2C_WriteNAU8822(37, 0x021);
        I2C_WriteNAU8822(38, 0x161);
        I2C_WriteNAU8822(39, 0x026);

        /* FIXME */
        if (ui32SamplRate > 44100)
            ui32SamplRate = 11025;

        mClkDiv = (44100 * 256 * u8ChNum) / (ui32SamplRate * 256);
        bClkDiv = (ui32SamplRate * 256) / (ui32SamplRate * u8ChNum * u8SamplBit);
    }

    switch (mClkDiv)
    {
    case 1:
        mClkDiv = 0;
        break;
    case 2:
        mClkDiv = 2;
        break;
    case 3:
        mClkDiv = 3;
        break;
    case 4:
        mClkDiv = 4;
        break;
    case 6:
        mClkDiv = 5;
        break;
    case 8:
        mClkDiv = 6;
        break;
    case 12:
        mClkDiv = 7;
        break;
    default:
        LOG_E("mclk divider not match!\n");
        mClkDiv = 0;
        return -RT_ERROR;
    }

    switch (bClkDiv)
    {
    case 1:
        bClkDiv = 0;
        break;
    case 2:
        bClkDiv = 1;
        break;
    case 4:
        bClkDiv = 2;
        break;
    case 8:
        bClkDiv = 3;
        break;
    case 16:
        bClkDiv = 4;
        break;
    case 32:
        bClkDiv = 5;
        break;
    default:
        LOG_E("bclk divider not match!\n");
        bClkDiv = 0;
        return -RT_ERROR;
    }

    if (nu_acodec_ops_nau8822.role == NU_ACODEC_ROLE_MASTER)
    {
        u16ClkCtrl = (1 << 8) | (1 << 0);  //Use internal PLL, FS/BCLK
    }

    u16ClkCtrl = (u16ClkCtrl & 0x11F) | (mClkDiv << 5);
    u16ClkCtrl = (u16ClkCtrl & 0x1E3) | (bClkDiv << 2);

    I2C_WriteNAU8822(4,  u16AudIf);

    I2C_WriteNAU8822(6,  u16ClkCtrl);

    return RT_EOK;
}

static rt_err_t nau8822_init(void)
{
    //input source is MIC
    if (nu_acodec_ops_nau8822.role == NU_ACODEC_ROLE_MASTER)
    {
        I2C_WriteNAU8822(1,  0x03F);   /* PLLEN, MICBIASEN, ABIASEN, IOBUFEN, REFIMP(3kohm)  */
    }
    else
    {
        I2C_WriteNAU8822(1,  0x01F);   /* MICBIASEN, ABIASEN, IOBUFEN, REFIMP(3kohm)  */
    }

    I2C_WriteNAU8822(2,  0x1BF);   /* Enable L/R Headphone, ADC Mix/Boost, ADC */
    I2C_WriteNAU8822(3,  0x07F);   /* Enable L/R main mixer, DAC */
    I2C_WriteNAU8822(4,  0x010);   /* 16-bit word length, I2S format, Stereo */
    I2C_WriteNAU8822(5,  0x000);   /* Companding control and loop back mode (all disable) */
    nau8822_delay_ms(30);

    I2C_WriteNAU8822(6,  0x1AD);   /* Divide by 6, 16K */
    I2C_WriteNAU8822(7,  0x006);   /* 16K for internal filter coefficients */
    I2C_WriteNAU8822(10, 0x008);   /* DAC soft mute is disabled, DAC oversampling rate is 128x */
    I2C_WriteNAU8822(14, 0x108);   /* ADC HP filter is disabled, ADC oversampling rate is 128x */
    I2C_WriteNAU8822(15, 0x1EF);   /* ADC left digital volume control */
    I2C_WriteNAU8822(16, 0x1EF);   /* ADC right digital volume control */
    I2C_WriteNAU8822(44, 0x033);   /* LMICN/LMICP is connected to PGA */
    I2C_WriteNAU8822(47, 0x100);   /* Gain value */
    I2C_WriteNAU8822(48, 0x100);   /* Gain value */
    I2C_WriteNAU8822(50, 0x001);   /* Left DAC connected to LMIX */
    I2C_WriteNAU8822(51, 0x001);   /* Right DAC connected to RMIX */
    
    I2C_WriteNAU8822(0x34, 0x13F);
    I2C_WriteNAU8822(0x35, 0x13F);

    nu_acodec_ops_nau8822.config.samplerate = 16000;
    nu_acodec_ops_nau8822.config.channels = 2;
    nu_acodec_ops_nau8822.config.samplebits = 16;

    LOG_I("Initialized done.\n");

    return RT_EOK;
}

static rt_err_t nau8822_dsp_control(struct rt_audio_configure *config)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(config != RT_NULL);

    if (rt_memcmp((void *)config, (void *)&nu_acodec_ops_nau8822.config, sizeof(struct rt_audio_configure)) != 0)
    {
        if ((result = nau8822_dsp_config(config->samplerate, config->channels, config->samplebits)) == RT_EOK)
            rt_memcpy((void *)&nu_acodec_ops_nau8822.config, (void *)config, sizeof(struct rt_audio_configure)) ;
    }
    return result;
}

static rt_err_t nau8822_mixer_control(rt_uint32_t ui32Units, rt_uint32_t ui32Value)
{
    switch (ui32Units)
    {
    case AUDIO_MIXER_MUTE:
    {
        uint16_t u16Data;
        I2C_ReadNAU8822(10, &u16Data);
        if (ui32Value)
        {
            I2C_WriteNAU8822(10,  u16Data | (1 << 6));
            nau8822_phonejack_set(g_psCodecConfig, 0);
        }
        else
        {
            I2C_WriteNAU8822(10,  u16Data & ~(1 << 6));
            nau8822_phonejack_set(g_psCodecConfig, 1);
        }
    }
    break;
    case AUDIO_MIXER_VOLUME:
    {
        uint8_t u8DACGAIN = 256 * ui32Value / 100;
        I2C_WriteNAU8822(11,  u8DACGAIN);
        I2C_WriteNAU8822(12,  u8DACGAIN);
    }
    break;
    case AUDIO_MIXER_QUERY:
    case AUDIO_MIXER_BASS:
    case AUDIO_MIXER_MID:
    case AUDIO_MIXER_TREBLE:
    case AUDIO_MIXER_EQUALIZER:
    case AUDIO_MIXER_LINE:
    case AUDIO_MIXER_DIGITAL:
    case AUDIO_MIXER_MIC:
    case AUDIO_MIXER_VITURAL:
    case AUDIO_MIXER_EXTEND:
    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t nau8822_mixer_query(rt_uint32_t ui32Units, rt_uint32_t *pui32Value)
{
    RT_ASSERT(pui32Value != RT_NULL);
    rt_uint16_t u16RV = 0;

    switch (ui32Units)
    {
    case AUDIO_MIXER_QUERY:
        *pui32Value = AUDIO_MIXER_VOLUME | AUDIO_MIXER_MUTE;
        break;

    case AUDIO_MIXER_MUTE:
        I2C_ReadNAU8822(10, (uint16_t *)&u16RV);
        if (u16RV & (1 << 6))
            *pui32Value = 1;
        else
            *pui32Value = 0;
        break;

    case AUDIO_MIXER_VOLUME:
        I2C_ReadNAU8822(11, (uint16_t *)&u16RV);
        *pui32Value = u16RV * 100 / 256;
        break;

    case AUDIO_MIXER_BASS:
    case AUDIO_MIXER_MID:
    case AUDIO_MIXER_TREBLE:
    case AUDIO_MIXER_EQUALIZER:
    case AUDIO_MIXER_LINE:
    case AUDIO_MIXER_DIGITAL:
    case AUDIO_MIXER_MIC:
    case AUDIO_MIXER_VITURAL:
    case AUDIO_MIXER_EXTEND:
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

int nu_hw_nau8822_init(S_NU_NAU8822_CONFIG *psCodecConfig)
{
    RT_ASSERT(psCodecConfig != RT_NULL);
    struct rt_i2c_bus_device *psI2cBusDev;
    struct rt_audio_device *psAudioDev;
    nu_i2s_t psNuI2s;

    /* Find I2C bus */
    psI2cBusDev = (struct rt_i2c_bus_device *)rt_device_find(psCodecConfig->i2c_bus_name);
    if (psI2cBusDev == RT_NULL)
    {
        LOG_E("Can't found I2C bus - %s..!\n", psCodecConfig->i2c_bus_name);
        goto exit_rt_hw_nau8822_init;
    }

    /* Find I2S bus */
    psAudioDev = (struct rt_audio_device *)rt_device_find(psCodecConfig->i2s_bus_name);
    if (psAudioDev == RT_NULL)
    {
        LOG_E("Can't found I2S bus - %s ..!\n", psCodecConfig->i2s_bus_name);
        goto exit_rt_hw_nau8822_init;
    }

    if (nau8822_probe() != RT_EOK)
    {
        LOG_E("Can't found audio codec..!\n");
        goto exit_rt_hw_nau8822_init;
    }

    /* Store this board setting. */
    g_psCodecConfig = psCodecConfig;
    g_I2cBusDev = psI2cBusDev;

    /* Get NuI2S device instance. */
    psNuI2s = (nu_i2s_t)psAudioDev;

    /* Register Acodec Ops */
    psNuI2s->AcodecOps = &nu_acodec_ops_nau8822;

    /* Use Acodec default settings. */
    rt_memcpy(&psNuI2s->config, &nu_acodec_ops_nau8822.config, sizeof(struct rt_audio_configure));

    return RT_EOK;

exit_rt_hw_nau8822_init:

    return -RT_ERROR;
}

#endif //#if defined(NU_PKG_USING_NAU8822)
