/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_NAU88L25)

#include <rtthread.h>
#include <rtdevice.h>

#include "acodec_nau88l25.h"
#include "drv_i2s.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "acodec.nau88l25"
#define DBG_COLOR
#include <rtdbg.h>

#define DEF_NAU88L25_ADDR    0x1A

static struct rt_i2c_bus_device *g_I2cBusDev = NULL;
S_NU_NAU88L25_CONFIG *g_psCodecConfig = NULL;

static rt_err_t nau88l25_init(void);
static rt_err_t nau88l25_reset(void);
static rt_err_t nau88l25_dsp_control(struct rt_audio_configure *config);
static rt_err_t nau88l25_mixer_control(rt_uint32_t ui32Units, rt_uint32_t ui32Value);
static rt_err_t nau88l25_mixer_query(rt_uint32_t ui32Units, rt_uint32_t *ui32Value);

nu_acodec_ops nu_acodec_ops_nau88l25 =
{
    .name = "NAU88L25",
    .role = NU_ACODEC_ROLE_MASTER,
    .config = { // Default settings.
        .samplerate = 48000,
        .channels = 2,
        .samplebits = 16
    },
    .nu_acodec_init = nau88l25_init,
    .nu_acodec_reset = nau88l25_reset,

    .nu_acodec_dsp_control = nau88l25_dsp_control,
    .nu_acodec_mixer_control = nau88l25_mixer_control,
    .nu_acodec_mixer_query = nau88l25_mixer_query
};

static void nau88l25_delay_ms(rt_uint32_t nms)
{
    rt_thread_mdelay(nms);
}

static int I2C_WriteNAU88L25(uint16_t u16addr, uint16_t u16data)
{
    struct rt_i2c_msg msg;
    char au8TxData[4];

    RT_ASSERT(g_I2cBusDev != NULL);

    au8TxData[0] = (uint8_t)((u16addr >> 8) & 0x00FF);   //addr [15:8]
    au8TxData[1] = (uint8_t)(u16addr & 0x00FF);          //addr [ 7:0]
    au8TxData[2] = (uint8_t)((u16data >> 8) & 0x00FF);   //data [15:8]
    au8TxData[3] = (uint8_t)(u16data & 0x00FF);          //data [ 7:0]

    msg.addr  = DEF_NAU88L25_ADDR;               /* Slave address */
    msg.flags = RT_I2C_WR;                       /* Write flag */
    msg.buf   = (rt_uint8_t *)&au8TxData[0];     /* Slave register address */
    msg.len   = sizeof(au8TxData);               /* Number of bytes sent */

    if (g_I2cBusDev && rt_i2c_transfer(g_I2cBusDev, &msg, 1) != 1)
    {
        rt_kprintf("[Failed] addr=%x, data=%d\n", u16addr, u16data);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int I2C_ReadNAU88L25(uint16_t u16addr, uint16_t *pu16data)
{
    struct rt_i2c_msg msgs[2];
    char au8TxData[2];

    RT_ASSERT(g_I2cBusDev != NULL);
    RT_ASSERT(pu16data != NULL);

    au8TxData[0] = (uint8_t)((u16addr >> 8) & 0x00FF);   //addr [15:8]
    au8TxData[1] = (uint8_t)(u16addr & 0x00FF);          //addr [ 7:0]

    msgs[0].addr  = DEF_NAU88L25_ADDR;        /* Slave address */
    msgs[0].flags = RT_I2C_WR;                /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)&au8TxData; /* Number of bytes sent */
    msgs[0].len   = sizeof(au8TxData);        /* Number of bytes read */

    msgs[1].addr  = DEF_NAU88L25_ADDR;        /* Slave address */
    msgs[1].flags = RT_I2C_RD;                /* Read flag */
    msgs[1].buf   = (rt_uint8_t *)pu16data;   /* Read data pointer */
    msgs[1].len   = sizeof(uint16_t);         /* Number of bytes read */

    if (rt_i2c_transfer(g_I2cBusDev, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static void nau88l25_phonejack_set(S_NU_NAU88L25_CONFIG *psCodecConfig, int bEnable)
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

static rt_err_t nau88l25_probe(void)
{
    return RT_EOK;
}

static rt_err_t nau88l25_reset(void)
{
    I2C_WriteNAU88L25(0,  0x1);
    I2C_WriteNAU88L25(0,  0);   // Reset all registers
    nau88l25_delay_ms(30);

    LOG_I("Software Reset.\n");

    return RT_EOK;
}

static rt_err_t nau88l25_dsp_config(rt_uint32_t ui32SamplRate, rt_uint8_t u8ChNum, rt_uint8_t u8SamplBit)
{
    int  clkDivider;
    int  i2sPcmCtrl2;
    int  lrClkDiv;
    char bClkDiv;
    char mClkDiv;

    /* Force to set Channel number to 2 */
    u8ChNum = 2;

    I2C_WriteNAU88L25(REG_I2S_PCM_CTRL1, AIFMT0_STANDI2S | ((u8SamplBit <= 24) ? ((u8SamplBit - 16) >> 2) : WLEN0_32BIT));
    u8SamplBit = (u8SamplBit > 16) ? 32 : 16;

    if (ui32SamplRate % 11025)
    {
        /* 48000 series 12.288Mhz */
        I2C_WriteNAU88L25(REG_FLL2, 0x3126);
        I2C_WriteNAU88L25(REG_FLL3, 0x0008);

        mClkDiv = 49152000 / (ui32SamplRate * 256);
    }
    else
    {
        /* 44100 series 11.2896Mhz */
        I2C_WriteNAU88L25(REG_FLL2, 0x86C2);
        I2C_WriteNAU88L25(REG_FLL3, 0x0007);

        /* FIXME */
        if (ui32SamplRate > 44100)
            ui32SamplRate = 11025;

        mClkDiv = 45158400 / (ui32SamplRate * 256);
    }

    lrClkDiv = u8ChNum * u8SamplBit;
    bClkDiv = 256 / lrClkDiv;

    switch (mClkDiv)
    {
    case 1:
        mClkDiv = 0;
        break;
    case 2:
        mClkDiv = 2;
        break;
    case 4:
        mClkDiv = 3;
        break;
    case 8:
        mClkDiv = 4;
        break;
    case 16:
        mClkDiv = 5;
        break;
    case 32:
        mClkDiv = 6;
        break;
    case 3:
        mClkDiv = 7;
        break;
    case 6:
        mClkDiv = 10;
        break;
    case 12:
        mClkDiv = 11;
        break;
    case 24:
        mClkDiv = 12;
        break;
    case 48:
        mClkDiv = 13;
        break;
    case 96:
        mClkDiv = 14;
        break;
    case 5:
        mClkDiv = 15;
        break;
    default:
        LOG_E("mclk divider not match!\n");
        mClkDiv = 0;
        return -RT_ERROR;
    }

    clkDivider = CLK_SYSCLK_SRC_VCO | CLK_ADC_SRC_DIV2 | CLK_DAC_SRC_DIV2 | mClkDiv;
    I2C_WriteNAU88L25(REG_CLK_DIVIDER, clkDivider);

    switch (bClkDiv)
    {
    case 2:
        bClkDiv = 0;
        break;
    case 4:
        bClkDiv = 1;
        break;
    case 8:
        bClkDiv = 2;
        break;
    case 16:
        bClkDiv = 3;
        break;
    case 32:
        bClkDiv = 4;
        break;
    case 64:
        bClkDiv = 5;
        break;
    default:
        LOG_E("bclk divider not match!\n");
        bClkDiv = 0;
        return -RT_ERROR;
    }

    switch (lrClkDiv)
    {
    case 256:
        lrClkDiv = 0;
        break;
    case 128:
        lrClkDiv = 1;
        break;
    case 64:
        lrClkDiv = 2;
        break;
    case 32:
        lrClkDiv = 3;
        break;
    default:
        LOG_E("lrclk divider not match!\n");
        lrClkDiv = 0;
        return -RT_ERROR;
    }

    i2sPcmCtrl2 =  ADCDAT0_OE | MS0_MASTER | (lrClkDiv << 12) | bClkDiv;

    I2C_WriteNAU88L25(REG_I2S_PCM_CTRL2, i2sPcmCtrl2);

    return RT_EOK;
}

static rt_err_t nau88l25_init(void)
{
    I2C_WriteNAU88L25(REG_CLK_DIVIDER,  CLK_SYSCLK_SRC_VCO | CLK_ADC_SRC_DIV2 | CLK_DAC_SRC_DIV2 | MCLK_SRC_DIV4);
    I2C_WriteNAU88L25(REG_FLL1,  FLL_RATIO_512K);
    I2C_WriteNAU88L25(REG_FLL2,  0x3126);
    I2C_WriteNAU88L25(REG_FLL3,  0x0008);
    I2C_WriteNAU88L25(REG_FLL4,  0x0010);
    I2C_WriteNAU88L25(REG_FLL5,  PDB_DACICTRL | CHB_FILTER_EN);
    I2C_WriteNAU88L25(REG_FLL6,  SDM_EN | CUTOFF500);
    I2C_WriteNAU88L25(REG_FLL_VCO_RSV,  0xF13C);
    I2C_WriteNAU88L25(REG_HSD_CTRL,  HSD_AUTO_MODE | MANU_ENGND1_GND);
    I2C_WriteNAU88L25(REG_SAR_CTRL,  RES_SEL_70K_OHMS | COMP_SPEED_1US | SAMPLE_SPEED_4US);
    I2C_WriteNAU88L25(REG_I2S_PCM_CTRL1,  AIFMT0_STANDI2S);

    if (nu_acodec_ops_nau88l25.role == NU_ACODEC_ROLE_MASTER)
    {
        I2C_WriteNAU88L25(REG_I2S_PCM_CTRL2,  LRC_DIV_DIV32 | ADCDAT0_OE | MS0_MASTER | BLCKDIV_DIV8);   //301A:Master 3012:Slave
    }
    else
    {
        I2C_WriteNAU88L25(REG_I2S_PCM_CTRL2,  LRC_DIV_DIV32 | ADCDAT0_OE | MS0_SLAVE | BLCKDIV_DIV8);
        I2C_WriteNAU88L25(REG_LEFT_TIME_SLOT,  DIS_FS_SHORT_DET);
    }

    I2C_WriteNAU88L25(REG_ADC_RATE,  0x10 | ADC_RATE_128);
    I2C_WriteNAU88L25(REG_DAC_CTRL1,  0x80 | DAC_RATE_128);

    I2C_WriteNAU88L25(REG_MUTE_CTRL,  0x0000); // 0x10000
    I2C_WriteNAU88L25(REG_ADC_DGAIN_CTRL,  DGAINL_ADC0(0xEF));
    I2C_WriteNAU88L25(REG_DACL_CTRL,  DGAINL_DAC(0xAE));
    I2C_WriteNAU88L25(REG_DACR_CTRL,  DGAINR_DAC(0xAE) | DAC_CH_SEL1_RIGHT);

    I2C_WriteNAU88L25(REG_CLASSG_CTRL,  CLASSG_TIMER_64MS | CLASSG_CMP_EN_R_DAC | CLASSG_CMP_EN_L_DAC | CLASSG_EN);
    I2C_WriteNAU88L25(REG_BIAS_ADJ,  VMIDEN | VMIDSEL_125K_OHM);
    I2C_WriteNAU88L25(REG_TRIM_SETTINGS,  DRV_IBCTRHS | DRV_ICUTHS | INTEG_IBCTRHS | INTEG_ICUTHS);
    I2C_WriteNAU88L25(REG_ANALOG_CONTROL_2,  AB_ADJ | CAP_1 | CAP_0);
    I2C_WriteNAU88L25(REG_ANALOG_ADC_1,  CHOPRESETN | CHOPF0_DIV4);
    I2C_WriteNAU88L25(REG_ANALOG_ADC_2,  VREFSEL_VMIDE_P5DB | PDNOTL | LFSRRESETN);
    I2C_WriteNAU88L25(REG_RDAC,  DAC_EN_L | DAC_EN_R | CLK_DAC_EN_L | CLK_DAC_EN_R | CLK_DAC_DELAY_2NSEC | DACVREFSEL(0x3));
    I2C_WriteNAU88L25(REG_MIC_BIAS,  INT2KB | LOWNOISE | POWERUP | MICBIASLVL1_1P1x);
    I2C_WriteNAU88L25(REG_BOOST,  PDVMDFST | BIASEN | BOOSTGDIS | EN_SHRT_SHTDWN);
    I2C_WriteNAU88L25(REG_POWER_UP_CONTROL,  PUFEPGA | FEPGA_GAIN(21) | PUP_INTEG_LEFT_HP | PUP_INTEG_RIGHT_HP | PUP_DRV_INSTG_RIGHT_HP | PUP_DRV_INSTG_LEFT_HP | PUP_MAIN_DRV_RIGHT_HP | PUP_MAIN_DRV_LEFT_HP);
    I2C_WriteNAU88L25(REG_CHARGE_PUMP_AND_DOWN_CONTROL, JAMNODCLOW | RNIN);
    I2C_WriteNAU88L25(REG_ENA_CTRL,  RDAC_EN | LDAC_EN | ADC_EN | DCLK_ADC_EN | DCLK_DAC_EN | CLK_I2S_EN | 0x4);

    nu_acodec_ops_nau88l25.config.samplerate = 48000;
    nu_acodec_ops_nau88l25.config.channels = 2;
    nu_acodec_ops_nau88l25.config.samplebits = 16;

    LOG_I("Initialized done.\n");

    return RT_EOK;
}

static rt_err_t nau88l25_dsp_control(struct rt_audio_configure *config)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(config != RT_NULL);

    if (rt_memcmp((void *)config, (void *)&nu_acodec_ops_nau88l25.config, sizeof(struct rt_audio_configure)) != 0)
    {
        if ((result = nau88l25_dsp_config(config->samplerate, config->channels, config->samplebits)) == RT_EOK)
            rt_memcpy((void *)&nu_acodec_ops_nau88l25.config, (void *)config, sizeof(struct rt_audio_configure)) ;
    }
    return result;
}

static rt_err_t nau88l25_mixer_control(rt_uint32_t ui32Units, rt_uint32_t ui32Value)
{
    switch (ui32Units)
    {
    case AUDIO_MIXER_MUTE:
        if (ui32Value)
        {
            I2C_WriteNAU88L25(REG_MUTE_CTRL,  SMUTE_EN);
            nau88l25_phonejack_set(g_psCodecConfig, 0);
        }
        else
        {
            I2C_WriteNAU88L25(REG_MUTE_CTRL,  0x0000);
            nau88l25_phonejack_set(g_psCodecConfig, 1);
        }
        break;

    case AUDIO_MIXER_VOLUME:
        I2C_WriteNAU88L25(REG_DACL_CTRL,  DGAINL_DAC(ui32Value * 2));
        I2C_WriteNAU88L25(REG_DACR_CTRL,  DGAINR_DAC(ui32Value * 2) | DAC_CH_SEL1_RIGHT);
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

static rt_err_t nau88l25_mixer_query(rt_uint32_t ui32Units, rt_uint32_t *pui32Value)
{
    RT_ASSERT(pui32Value != RT_NULL);
    rt_uint16_t u16RV = 0;

    switch (ui32Units)
    {
    case AUDIO_MIXER_QUERY:
        *pui32Value = AUDIO_MIXER_VOLUME | AUDIO_MIXER_MUTE;
        break;

    case AUDIO_MIXER_MUTE:
        I2C_ReadNAU88L25(REG_MUTE_CTRL, (uint16_t *)&u16RV);
        if (u16RV & SMUTE_EN)
            *pui32Value = 1;
        else
            *pui32Value = 0;
        break;

    case AUDIO_MIXER_VOLUME:
        I2C_ReadNAU88L25(REG_DACL_CTRL, (uint16_t *)&u16RV);
        *pui32Value = u16RV / 2;
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

int nu_hw_nau88l25_init(S_NU_NAU88L25_CONFIG *psCodecConfig)
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
        goto exit_rt_hw_nau88l25_init;
    }

    /* Find I2S bus */
    psAudioDev = (struct rt_audio_device *)rt_device_find(psCodecConfig->i2s_bus_name);
    if (psAudioDev == RT_NULL)
    {
        LOG_E("Can't found I2S bus - %s ..!\n", psCodecConfig->i2s_bus_name);
        goto exit_rt_hw_nau88l25_init;
    }

    if (nau88l25_probe() != RT_EOK)
    {
        LOG_E("Can't found audio codec..!\n");
        goto exit_rt_hw_nau88l25_init;
    }

    /* Store this board setting. */
    g_psCodecConfig = psCodecConfig;
    g_I2cBusDev = psI2cBusDev;

    /* Get NuI2S device instance. */
    psNuI2s = (nu_i2s_t)psAudioDev;

    /* Register Acodec Ops */
    psNuI2s->AcodecOps = &nu_acodec_ops_nau88l25;

    /* Use Acodec default settings. */
    rt_memcpy(&psNuI2s->config, &nu_acodec_ops_nau88l25.config, sizeof(struct rt_audio_configure));

    return RT_EOK;

exit_rt_hw_nau88l25_init:

    return -RT_ERROR;
}

#endif //#if defined(NU_PKG_USING_NAU88L25)
