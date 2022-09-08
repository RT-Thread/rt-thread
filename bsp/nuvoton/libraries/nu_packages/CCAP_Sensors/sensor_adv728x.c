/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-8-25       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#include "ccap_sensor.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "sensor.adv728x"
#define DBG_COLOR
#include <rtdbg.h>

#define DEF_ADV728X_ADDR      0x20
#define DEF_ADV728X_VPP_ADDR  0x22

typedef enum
{
    INPUT_CTRL      = 0x00, //Input control
    VIDEO_SEL1      = 0x01, //Video  Selection 1
    VIDEO_SEL2      = 0x02, //Video  Selection 2
    OUTPUT_CTRL     = 0x03, //Output control
    EXTOUT_CTRL     = 0x04, //Extended output control
    RESERVE1        = 0x05, //Reserved
    RESERVE2        = 0x06, //Reserved
    AUTODET_EN      = 0x07, //Autodetect enable
    CONTR_ADJ       = 0x08, //Contrast
    RESERVE3        = 0x09, //Reserved
    BRIGHT_ADJ      = 0x0A, //Brightness adjust
    HUE_ADJ         = 0x0B, //Hue adjust
    DEF_VAL_Y       = 0x0C, //Default Value Y
    DEF_VAL_C       = 0x0D, //Default Value C
    ANA_DEC_CTRL1   = 0x0E, //Analog Devices Control 1
    PWR_MAG_CTRL    = 0x0F, //Power management
    STATUS1_READ    = 0x10, //Status 1
    IDENT_READ      = 0x11, //IDENT
    STATUS2_READ    = 0x12, //Status 2
    STATUS3_READ    = 0x13, //Status 3
    ANA_CLP_CTRL    = 0x14, //Analog clamp control
    DIG_CLP_CTRL1   = 0x15, //Digital Clamp Control 1
    RESERVE4        = 0x16, //Reserved
    SHAP_FIL_CTRL1  = 0x17, //Shaping Filter Control 1
    SHAP_FIL_CTRL2  = 0x18, //Shaping Filter Control 2
    COMB_FIL_CTRL   = 0x19, //Comb filter control
    ANA_DEC_CTRL2   = 0x1D, //Analog Devices Control 2
    PIX_DLY_CTRL    = 0x27, //Pixel delay control
    MISC_GAIN_CTRL  = 0x2B, //Misc gain control
    AGC_MODE_CTRL   = 0x2C, //AGC mode control
    CHRO_GAIN_CTRL1 = 0x2D, //Chroma Gain Control 1
    CHRO_GAIN_CTRL2 = 0x2E, //Chroma Gain Control 2
    LUMA_GAIN_CTRL1 = 0x2F, //Luma Gain Control 1
    LUMA_GAIN_CTRL2 = 0x30, //Luma Gain Control 2
    VS_FIE_CTRL1    = 0x31, //VS/FIELD  Control 1
    VS_FIE_CTRL2    = 0x32, //VS/FIELD  Control 2
    VS_FIE_CTRL3    = 0x33, //VS/FIELD  Control 3
    HS_POS_CTRL1    = 0x34, //HS Position Control 1
    HS_POS_CTRL2    = 0x35, //HS Position Control 2
    HS_POS_CTRL3    = 0x36, //HS Position Control 3
    POLARITY_CTRL   = 0x37, //Polarity
    NTSC_COMB_CTRL  = 0x38, //NTSC comb control
    PAL_COMB_CTRL   = 0x39, //PAL comb control
    ADC_CTRL        = 0x3A, //ADC control
    MANU_WIN_CTRL   = 0x3D, //Manual window control
    RESAMPLE_CTRL   = 0x41, //Resample control
    CTI_DNR_CTRL1   = 0x4D, //CTI DNR  Control 1
    CTI_DNR_CTRL2   = 0x4E, //CTI DNR Control 2
    DNR_NOS_THRES   = 0x50, //DNR Noise Threshold 1
    LOCK_CNT_CTEL   = 0x51, //Lock count
    DIAG1_CTRL      = 0x5D, //DIAG1 control
    DIAG2_CTRL      = 0x5E, //DIAG2 control
    GPO_CTRL        = 0x59, //GPO
    ADC_SW3_CTRL    = 0x60, //ADC Switch 3
    OUT_SYNC_SEL1   = 0x6A, //Output Sync Select 1
    OUT_SYNC_SEL2   = 0x6B, //Output Sync Select 2
    FREERUN_LINE_LEN    = 0x8F, //Free Run Line Length 1
    CCAP1_CTRL1     = 0x99, //CCAP1
    CCAP1_CTRL2     = 0x9A, //CCAP2
    LETTER_BOX1     = 0x9B, //Letterbox 1
    LETTER_BOX2     = 0x9C, //Letterbox 2
    LETTER_BOX3     = 0x9D, //Letterbox 3
    CRC_EN_CTRL     = 0xB2, //CRC enable
    ADC_SW1_CTRL    = 0xC3, //ADC Switch 1
    ADC_SW2_CTRL    = 0xC4, //ADC Switch 2
    LETTER_BOX_CTRL1    = 0xDC, //Letterbox Control 1
    LETTER_BOX_CTRL2    = 0xDD, //Letterbox Control 2
    ST_NOISE_RB1    = 0xDE, //ST Noise Readback 1
    ST_NOISE_RB2    = 0xDF, //ST Noise Readback 2
    SD_OFFSET_CB_CH = 0xE1, //SD offset Cb channel
    SD_OFFSET_CR_CH = 0xE2, //SD offset Cr channel
    SD_SATUR_CB_CH  = 0xE3, //SD saturation Cb channel
    SD_SATUR_CR_CH  = 0xE4, //SD saturation Cr channel
    NTSC_VBIT_BEN   = 0xE5, //NTSC V bit begin
    NTSC_VBIT_END   = 0xE6, //NTSC V bit end
    NTSC_FBIT_TOG   = 0xE7, //NTSC F bit toggle
    PAL_VBIT_BEN    = 0xE8, //PAL V bit begin
    PAL_VBIT_END    = 0xE9, //PAL V bit end
    PAL_FBIT_TOG    = 0xEA, //PAL F bit toggle
    VBLANK_CTRL1    = 0xEB, //Vblank  Control 1
    VBLANK_CTRL2    = 0xEC, //Vblank  Control 2
    AFE_CTRL1       = 0xF3, //AFE Control 1
    DRV_STRENGTH    = 0xF4, //Drive strength
    IF_COMP_CTRL    = 0xF8, //IF_COMP_ CONTROL
    VS_MODE_CTRL    = 0xF9, //VS mode control
    PEAK_GAIN       = 0xFB, //Peaking gain
    DNR_NOS_THRES2  = 0xFC, //DNR Noise Threshold 2
    VPP_SLAVE_ADDR  = 0xFD, //VPP slave address
    CSITX_SLAVE_ADDR    = 0xFE, //CSI Tx slave address
    //User Sub Map 2 Register Map Details
    ACE_CTRL1       = 0x80, //ACE Control 1
    ACE_CTRL4       = 0x83, //ACE Control 4
    ACE_CTRL5       = 0x84, //ACE Control 5
    ACE_CTRL6       = 0x85, //ACE Control 6
    DITHER_CTRL     = 0x92, //Dither control
    MIN_MAX0        = 0xD9, //MIN_MAX_0
    MIN_MAX1        = 0xDA, //MIN_MAX_1
    MIN_MAX2        = 0xDB, //MIN_MAX_2
    MIN_MAX3        = 0xDC, //MIN_MAX_3
    MIN_MAX4        = 0xDD, //MIN_MAX_4
    MIN_MAX5        = 0xDE, //MIN_MAX_5
    FL_CTRL         = 0xE0, //FL control
    Y_AVG0          = 0xE1, //Y Average 0
    Y_AVG1          = 0xE2, //Y Average 1
    Y_AVG2          = 0xE3, //Y Average 2
    Y_AVG3          = 0xE4, //Y Average 3
    Y_AVG4          = 0xE5, //Y Average 4
    Y_AVG5          = 0xE6, //Y Average 5
    Y_AVG_MSB       = 0xE7, //Y average data MSB
    Y_AVG_LSB       = 0xE8, //Y average data LSB
    //Interrupt/VDP Sub Map Details
    INT_CONF1       = 0x40, //Interrupt Configuration 1
    INT_STATUS1     = 0x42, //Interrupt  Status 1
    INT_CLR1        = 0x43, //Interrupt  Clear 1
    INT_MSK1        = 0x44, //Interrupt  Mask 1
    RAW_STATUS2     = 0x45, //Raw Status 2
    INT_STATUS2     = 0x46, //Interrupt  Status 2
    INT_CLR2        = 0x47, //Interrupt  Clear 2
    INT_MSK2        = 0x48, //Interrupt  Mask 2
    RAW_STATUS3     = 0x49, //Raw Status 3
    INT_STATUS3     = 0x4A, //Interrupt  Status 3
    INT_CLR3        = 0x4B, //Interrupt  Clear 3
    INT_MSK3        = 0x4C, //Interrupt  Mask 3
    INT_STATUS4     = 0x4E, //Interrupt  Status 4
    INT_CLR4        = 0x4F, //Interrupt Clear 4
    INT_MSK4        = 0x50, //Interrupt  Mask 4
    INT_LAN0        = 0x51, //Interrupt  Latch 0
    INT_STATUS5     = 0x53, //Interrupt  Status 5
    INT_CLR5        = 0x54, //Interrupt  Clear 5
    INT_MSK5        = 0x55, //Interrupt Mask 5
    VDP_CONF1       = 0x60, //VDP_ CONFIG_1
    VDP_ADF_CONF1   = 0x62, //VDP_ADF_ CONFIG_1
    VDP_ADF_CONF2   = 0x63, //VDP_ADF_ CONFIG_2
    VDP_LINE_00E    = 0x64, //VDP_LINE_00E
    VDP_LINE_00F    = 0x65, //VDP_LINE_00F
    VDP_LINE_010    = 0x66, //VDP_LINE_010
    VDP_LINE_011    = 0x67, //VDP_LINE_011
    VDP_LINE_012    = 0x68, //VDP_LINE_012
    VDP_LINE_013    = 0x69, //VDP_LINE_013
    VDP_LINE_014    = 0x6A, //VDP_LINE_014
    VDP_LINE_015    = 0x6B, //VDP_LINE_015
    VDP_LINE_016    = 0x6C, //VDP_LINE_016
    VDP_LINE_017    = 0x6D, //VDP_LINE_017
    VDP_LINE_018    = 0x6E, //VDP_LINE_018
    VDP_LINE_019    = 0x6F, //VDP_LINE_019
    VDP_LINE_01A    = 0x70, //VDP_LINE_01A
    VDP_LINE_01B    = 0x71, //VDP_LINE_01B
    VDP_LINE_01C    = 0x72, //VDP_LINE_01C
    VDP_LINE_01D    = 0x73, //VDP_LINE_01D
    VDP_LINE_01E    = 0x74, //VDP_LINE_01E
    VDP_LINE_01F    = 0x75, //VDP_LINE_01F
    VDP_LINE_020    = 0x76, //VDP_LINE_020
    VDP_LINE_021    = 0x77, //VDP_LINE_021
    VDP_STATUS      = 0x78, //VDP_STATUS
    VDP_STATUS_CLR  = 0x78, //VDP_STATUS_ CLEAR
    VDP_CCAP_DAT0   = 0x79, //VDP_CCAP_ DATA_0
    VDP_CCAP_DAT1   = 0x7A, //VDP_CCAP_ DATA_1
    VDP_CGMS_WSS_DAT0   = 0x7D, //VDP_CGMS_ WSS_DATA_0
    VDP_CGMS_WSS_DAT1   = 0x7E, //VDP_CGMS_ WSS_DATA_1
    VDP_CGMS_WSS_DAT2   = 0x7F, //VDP_CGMS_ WSS_DATA_2
    VDP_OUTPUT_SEL  = 0x9C, //VDP_OUTPUT_SEL
    //VPP Map Details
    DEINT_RST       = 0x41, //DEINT_RESET
    I2C_DEINT_EN    = 0x55, //I2C_DEINT_ENABLE
    ADV_TIM_MODE_EN = 0x5B  //ADV_TIMING_MODE_EN
} ADV728X_REG;


static const sensor_reg_val s_sRegValue_576P_YUV[] =
{
    /* ADV728X , I2C Slave address : 0x20
     * PWDN = High (Preview mode) ; = Low(Power down)
     * Reset = High (Preview mode) ; = Low (Reset)
     */
    /* analog devices recommends */
    {PWR_MAG_CTRL, 0x00}, //Leave power-ddown mode

    {ANA_DEC_CTRL1, 0x80},
    {0x9C, 0x00},
    {0x9C, 0xFF},

    {ANA_DEC_CTRL1, 0x00}, // Enter User Sub Map
    {OUTPUT_CTRL, 0x0C}, // Enable Pixel & Sync output drivers
    {EXTOUT_CTRL, 0x07}, // Power-up INTRQ, HS & VS pads

    //{SHAP_FIL_CTRL1,0x41},  //Enable SH1
    //{0x39, 0x24},  //Disable comb filtering

    {VIDEO_SEL1, 0xC8},
    {ANA_DEC_CTRL2, 0x40}, //Enable LLC output driver
    {OUT_SYNC_SEL1, 0x00}, //The HS pin output horizontal sync
    {OUT_SYNC_SEL2, 0x11}, //The VS/FIELD/SFL pin outputs vertical sync
    //{POLARITY_CTRL,0x01},

    /* Enable autodetection */
    {INPUT_CTRL, 0x00}, //CVBS input AIN1
    {AUTODET_EN, 0xFF}, //Enable autodetection

    //{EXTOUT_CTRL,0xCD},  //Enable HS and VS/FIELD/SFL forced active
    //{POLARITY_CTRL,0x01},
    //{VS_FIE_CTRL2,0xC1},
    //{VS_FIE_CTRL3,0x04},

    /* analog devices recommends */
    {0x52, 0xCD},
    {0x80, 0x51},
    {0x81, 0x51},
    {0x82, 0x68},

    /* Set VPP Map */
    {VPP_SLAVE_ADDR, (DEF_ADV728X_VPP_ADDR << 1)}, // Set VPP Map
};

static const sensor_reg_val s_sRegValue_VPP[] =
{
    {0xA3, 0x00}, //VPP - not documented
    {0x5B, 0x00}, //VPP - Enbable Advanced Timing Mode
    {0x55, 0x80} //VPP - Enable Deinterlacer
};

static rt_err_t ccap_sensor_set_mode_adv728x(struct rt_i2c_bus_device *i2cdev, void *pvPriv, sensor_mode_info *psInfo)
{
    sensor_priv *pdev = (sensor_priv *)pvPriv;
    uint8_t au8TxData[4];
    int i;

    RT_ASSERT(i2cdev);
    RT_ASSERT(pdev);
    RT_ASSERT(psInfo);

    LOG_I("ADV728x Sensor ID:%d, Width:%d, Height:%d, FMT:%08x",
          pdev->eId,
          psInfo->sViewInfo.u32Width,
          psInfo->sViewInfo.u32Height,
          psInfo->sViewInfo.u32PixFmt);

    for (i = 0; i < psInfo->u32RegArrSize; i++)
    {
        const sensor_reg_val *psRegVal = &psInfo->psRegArr[i];
        au8TxData[0] = (uint8_t)((psRegVal->u16Addr) & 0x00FF); //addr [ 7:0]
        au8TxData[pdev->u16AddrBL] = (uint8_t)((psRegVal->u16Val) & 0x00FF);  //data [ 7:0]

        if (ccap_sensor_i2c_write(i2cdev, pdev->u16DevAddr, (rt_uint8_t *)&au8TxData[0], pdev->u16AddrBL + pdev->u16ValBL) != RT_EOK)
        {
            LOG_E("[Failed] addr=%x, data=%d\n", psRegVal->u16Addr, psRegVal->u16Val);
            return -RT_ERROR;
        }

        //LOG_I("%02x[W]: %02x@%02x", pdev->u16DevAddr, au8TxData[1], au8TxData[0]);
        //ccap_sensor_i2c_read(i2cdev, pdev->u16DevAddr, (rt_uint8_t *)&au8TxData[0], pdev->u16AddrBL, (rt_uint8_t *)&au8TxData[1], pdev->u16ValBL);
        //LOG_I("%02x[R]: %02x@%02x", pdev->u16DevAddr, au8TxData[1], au8TxData[0]);
    }

    for (i = 0; i < sizeof(s_sRegValue_VPP) / sizeof(sensor_reg_val); i++)
    {
        const sensor_reg_val *psRegVal = &s_sRegValue_VPP[i];
        au8TxData[0] = (uint8_t)((psRegVal->u16Addr) & 0x00FF); //addr [ 7:0]
        au8TxData[pdev->u16AddrBL] = (uint8_t)((psRegVal->u16Val) & 0x00FF);  //data [ 7:0]

        if (ccap_sensor_i2c_write(i2cdev, DEF_ADV728X_VPP_ADDR, (rt_uint8_t *)&au8TxData[0], pdev->u16AddrBL + pdev->u16ValBL) != RT_EOK)
        {
            LOG_E("[Failed] addr=%x, data=%d\n", psRegVal->u16Addr, psRegVal->u16Val);
            return -RT_ERROR;
        }

        //LOG_I("%02x[W]: %02x@%02x", DEF_ADV728X_VPP_ADDR, au8TxData[1], au8TxData[0]);
        //ccap_sensor_i2c_read(i2cdev, DEF_ADV728X_VPP_ADDR, (rt_uint8_t *)&au8TxData[0], pdev->u16AddrBL, (rt_uint8_t *)&au8TxData[1], pdev->u16ValBL);
        //LOG_I("%02x[R]: %02x@%02x", DEF_ADV728X_VPP_ADDR, au8TxData[1], au8TxData[0]);
    }

    return RT_EOK;
}

static sensor_mode_info adv728x_modeinfo [] =
{
    /* First setting table, 720x576xYUV */
    {
        .sViewInfo.u32Width = 720,
        .sViewInfo.u32Height = 576,
        .sViewInfo.pu8FarmAddr = RT_NULL, /*Unused*/
        .sViewInfo.u32PixFmt = (CCAP_PAR_INDATORD_VYUY | CCAP_PAR_INFMT_YUV422),
        .psRegArr = &s_sRegValue_576P_YUV[0],
        .u32RegArrSize = sizeof(s_sRegValue_576P_YUV) / sizeof(sensor_reg_val),
        .u32SenClk = 0,
        .u32Polarity  = (CCAP_PAR_SENTYPE_CCIR601 | CCAP_PAR_VSP_LOW | CCAP_PAR_VSP_LOW  | CCAP_PAR_PCLKP_HIGH),
    },
};

static const sensor_priv adv728x_priv =
{
    .eId = evCCAPSNR_ADV728X,
    .psModeInfo = &adv728x_modeinfo[0],
    .ModeInfoSize = sizeof(adv728x_modeinfo) / sizeof(sensor_mode_info),
    .u16AddrBL = 1,
    .u16ValBL = 1,
    .u16DevAddr = DEF_ADV728X_ADDR,
    .pfnSetMode = ccap_sensor_set_mode_adv728x,
    .RstActLow       = RT_TRUE,
    .RstHoldTimeInMs = 20,
    .PwrDwnActLow    = RT_TRUE,
};

ccap_sensor_dev_t nu_create_adv728x(ccap_sensor_io *psIo, const char *szName)
{
    rt_err_t ret;
    ccap_sensor_dev *pdev = rt_malloc(sizeof(ccap_sensor_dev));

    RT_ASSERT(pdev);
    RT_ASSERT(psIo);
    RT_ASSERT(szName);

    pdev->psIo  = psIo;
    ret = ccap_sensor_register(&pdev->device, szName, (void *)&adv728x_priv);

    if (ret != RT_EOK)
    {
        rt_free(pdev);
        pdev = RT_NULL;
    }

    return pdev;
}
