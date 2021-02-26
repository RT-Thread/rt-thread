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

#ifndef __ACODEC_NAU88L25_H__
#define __ACODEC_NAU88L25_H__

#include <rtdevice.h>

enum
{
    REG_SOFTWARE_RST,
    REG_ENA_CTRL,
    REG_I2C_ADDR_SET,
    REG_CLK_DIVIDER,
    REG_FLL1,
    REG_FLL2,
    REG_FLL3,
    REG_FLL4,
    REG_FLL5,
    REG_FLL6,
    REG_FLL_VCO_RSV,
    REG_HSD_CTRL = 0xC,                 //0xC
    REG_JACK_DET_CTRL,
    REG_INTERRUPT_MASK = 0xF,           //0xF
    REG_IRQ_STATUS,
    REG_INT_LCR_KEY_STATUS,
    REG_INTERRUPT_DIS_CTRL,
    REG_SAR_CTRL,
    REG_KEYDET_CTRL,
    REG_VDET_THRESHOLD_1,
    REG_VDET_THRESHOLD_2,
    REG_VDET_THRESHOLD_3,
    REG_VDET_THRESHOLD_4,
    REG_GPIO34_CTRL,
    REG_GPIO12_CTRL,
    REG_TDM_CTRL,
    REG_I2S_PCM_CTRL1,
    REG_I2S_PCM_CTRL2,
    REG_LEFT_TIME_SLOT,
    REG_RIGHT_TIME_SLOT,
    REG_BIQ_CTRL,
    REG_BIQ_COF1,
    REG_BIQ_COF2,
    REG_BIQ_COF3,
    REG_BIQ_COF4,
    REG_BIQ_COF5,
    REG_BIQ_COF6,
    REG_BIQ_COF7,
    REG_BIQ_COF8,
    REG_BIQ_COF9,                            //29
    REG_BIQ_COF10,
    REG_ADC_RATE,
    REG_DAC_CTRL1,
    REG_DAC_CTRL2,
    REG_DAC_DGAIN_CTRL = 0x2F,
    REG_ADC_DGAIN_CTRL,
    REG_MUTE_CTRL,
    REG_HSVOL_CTRL,
    REG_DACL_CTRL,
    REG_DACR_CTRL,
    REG_ADC_DRC_KNEE_IP12 = 0x38,
    REG_ADC_DRC_KNEE_IP34,
    REG_ADC_DRC_SLOPES,
    REG_ADC_DRC_ATKDCY,
    REG_DAC_DRC_KNEE_IP12 = 0x45,            //0x45
    REG_DAC_DRC_KNEE_IP34,
    REG_DAC_DRC_SLOPES,
    REG_DAC_DRC_ATKDCY = 0x48,               //0x48
    REG_MODE_CTRL = 0x4C,                    //0x4C
    REG_CLASSG_CTRL = 0x50,                  //0x50
    REG_OPT_EFUSE_CTRL,
    REG_MISC_CTRL = 0x55,                    //0x55

    REG_I2C_DEVICE_ID = 0x58,                //0x58
    REG_SARDOUT_RAM_STATUS,

    REG_BIAS_ADJ = 0x66,                     //0x66

    REG_TRIM_SETTINGS = 0x68,                //0x68
    REG_ANALOG_CONTROL_1,
    REG_ANALOG_CONTROL_2,

    REG_ANALOG_ADC_1 = 0x71,                 //0x71
    REG_ANALOG_ADC_2,
    REG_RDAC,
    REG_MIC_BIAS,                            //0x74
    REG_BOOST = 0x76,
    REG_FEPGA,
    REG_POWER_UP_CONTROL = 0x7F,             //0x7F
    REG_CHARGE_PUMP_AND_DOWN_CONTROL,        //0x80
    REG_CHARGE_PUMP_INPUT_READ,
    REG_GENERAL_STATUS
};


// R1 REG_ENA_CTRL

#define CLK_DRC_EN            (1)
#define CLK_SAR_EN            (1 << 1)
#define CLK_BIST_EN           (1 << 3)
#define CLK_I2S_EN            (1 << 4)
#define CLK_MODE_EN           (1 << 5)
#define DCLK_DAC_EN           (1 << 6)
#define DCLK_ADC_EN           (1 << 7)
#define ADC_EN                (1 << 8)
#define LDAC_EN               (1 << 9)
#define RDAC_EN               (1 << 10)
#define CLK_DAC_INV           (1 << 14)
#define CMLCK_ENB             (1 << 15)


// R2 REG_I2C_ADDR_SET
#define I2C_ADDDR_SEL
#define I2C_LSB_VAL_IO


// R3 REG_CLK_DIVIDER
#define MCLK_SRC_DIV1         (0)
#define MCLK_SRC_INVERTED     (1)
#define MCLK_SRC_DIV2         (2)
#define MCLK_SRC_DIV4         (3)
#define MCLK_SRC_DIV8         (4)
#define MCLK_SRC_DIV16        (5)
#define MCLK_SRC_DIV32        (6)
#define MCLK_SRC_DIV3         (7)
#define MCLK_SRC_DIV6         (10)
#define MCLK_SRC_DIV12        (11)
#define MCLK_SRC_DIV24        (12)
#define MCLK_SRC_DIV48        (13)
#define MCLK_SRC_DIV96        (14)
#define MCLK_SRC_DIV5         (15)

#define CLK_DAC_SRC_DIV1      (0)
#define CLK_DAC_SRC_DIV2      (1 << 4)
#define CLK_DAC_SRC_DIV4      (2 << 4)
#define CLK_DAC_SRC_DIV8      (3 << 4)

#define CLK_ADC_SRC_DIV1     (0)
#define CLK_ADC_SRC_DIV2     (1 << 6)
#define CLK_ADC_SRC_DIV4     (2 << 6)
#define CLK_ADC_SRC_DIV8     (3 << 6)

#define CLK_ADC_PL_INVERT     (1 << 10)
#define CLK_DAC_PL_INVERT     (1 << 11)
#define CLK_CODEC_SRC_IMCLK   (0)
#define CLK_CODEC_SRC_PIN     (1 << 13)
#define CLK_SYSCLK_SRC_VCO    (1 << 15)
#define CLK_SYSCLK_SRC_PIN    (0)

// R4 REG_FLL1
#define FLL_RATIO_512K        (1)
#define FLL_RATIO_256K        (1 << 1)
#define FLL_RATIO_128K        (1 << 2)
#define FLL_RATIO_64K         (1 << 3)
#define FLL_RATIO_32K         (1 << 4)
#define FLL_RATIO_8K          (1 << 5)
#define FLL_RATIO_4K          (1 << 6)
#define FLL_LCOK_BP           (1 << 7)
#define ICTRL_V2I_AMP2X       (1 << 8)
#define ICTRL_V2I_AMP         (1 << 9)
#define ICTRL_V2I_BOTHAMP     (3 << 8)
#define ICTRL_LATCH_1X        (1 << 10)
#define ICTRL_LATCH_2X        (3 << 10)
#define ICTRL_LATCH_3X        (7 << 10)
#define FLL1SELDAC_POS        (13)
#define FLL1SELDAC_MSK        (0x7 << FLL1SELDAC_POS)

// R5 REG_FLL2
#define FLLFRAC_POS           (0)
#define FLLFRAC_MSK           (0xFFFF << FLLFRAC_POS)

// R6 REG_FLL3
#define FLL_INTEGER(x)        (x << 0)
#define FLL_CLK_REF_SRC_MCLKPIN (0)
#define FLL_CLK_REF_SRC_BCLKPIN (1 << 11)
#define FLL_CLK_REF_SRC_FSPIN (0x3 << 10)
#define GAIN_ERR_x1           (0x0)
#define GAIN_ERR_x2           (0x1 << 12)
#define GAIN_ERR_x4           (0x2 << 12)
#define GAIN_ERR_x8           (0x3 << 12)
#define GAIN_ERR_x16          (0x4 << 12)
#define GAIN_ERR_x32          (0x5 << 12)
#define GAIN_ERR_x64          (0x6 << 12)


// R7 REG_FLL4
#define FLL_N2(x)                    (x << 0)
#define FLL_CLK_REF_DIV1             (0x0 << 10)
#define FLL_CLK_REF_DIV2             (0x1 << 10)
#define FLL_CLK_REF_DIV4             (0x2 << 10)
#define FLL_CLK_REF_DIV8             (0x3 << 10)
#define FLL_CLK_REF_DIV_4CHK_1       (0x0 << 12)
#define FLL_CLK_REF_DIV_4CHK_1_2     (0x1 << 12)
#define FLL_CLK_REF_DIV_4CHK_1_4     (0x2 << 12)
#define FLL_CLK_REF_DIV_4CHK_1_8     (0x3 << 12)
#define FLL_CLK_REF_DIV_4CHK_1_16    (0x4 << 12)
#define FLL_CLK_REF_DIV_4CHK_1_32    (0x5 << 12)


// R8 REG_FLL5
#define FLL_LOCK_LENGTH(x)            (x << 0)
#define FILTER_SW                     (0x1 << 12)
#define CLK_FILTER_SW                 (0x1 << 13)
#define CHB_FILTER_EN                 (0x1 << 14)
#define PDB_DACICTRL                  (0x1 << 15)


// R9 REG_FLL6
#define FLL_SD_DITHER_SEL_1LSB        (0x1 << 4)
#define FLL_SD_DITHER_SEL_2LSBs       (0x2 << 4)
#define FLL_SD_DITHER_SEL_3LSBs       (0x3 << 4)
#define FLL_FLTR_DITHER_SEL_1LSB      (0x1 << 6)
#define FLL_FLTR_DITHER_SEL_2LSBs     (0x2 << 6)
#define FLL_FLTR_DITHER_SEL_3LSBs     (0x3 << 6)
#define CUTOFF600                     (0x1 << 12)
#define CUTOFF500                     (0x1 << 13)
#define SDM_EN                        (0x1 << 14)
#define DCO_EN                        (0x1 << 15)



// R A REG_FLL_VCO_RSV
#define DOUT2VCO_RSV_POS       (0)
#define DOUT2VCO_RSV_Msk       (0xFFFF << FLLFRAC_POS)

// R C REG_HSD_CTRL
#define MANU_SPKR_DWN1L_OPEN   (0)
#define MANU_SPKR_DWN1L_GND    (1)
#define MANU_SPKR_DWN1R_OPEN   (0)
#define MANU_SPKR_DWN1R_GND    (1 << 1)
#define MANU_ENGND2_OPEN       (0)
#define MANU_ENGND2_GND            (1 << 2)
#define MANU_ENGND1_OPEN       (0)
#define MANU_ENGND1_GND            (1 << 3)
#define MANUAL_START           (1 << 4)
#define HSD_AUTO_MODE          (1 << 6)
#define RESET_HSD              (1 << 15)


// R D REG_JACK_DET_CTRL
#define JKDET_LOGIC_AND_GATE       (1)
#define JKDET_LOGIC_OR_GATE       (0)
#define JKDET_PL_N_INVERT      (1)
#define JKDET_PL_INVERT      (0)
#define EJECT_DT(x)          (x << 2)
#define INSERT_DT(x)         (x << 5)
#define DB_BP_MODE_BYBASS_DEBOUNCE (1 << 8)
#define DB_BP_MODE_NORMAL      (0)
#define JD_RESTART            (1)
#define JK_1_PL_GPIO2JD1      (0)
#define JK_1_PL_GPIO2JD1_INV      (1 << 10)
#define JK_1_PL_IGNORE_0      (2 << 10)
#define JK_1_PL_IGNORE_1      (3 << 10)
#define JK_2_PL_JKDETL      (0)
#define JK_2_PL_JKDETL_INV      (1 << 12)
#define JK_2_PL_IGNORE_0      (2 << 12)
#define JK_2_PL_IGNORE_1      (3 << 12)
#define JK_3_PL_GPIO3JD2      (0)
#define JK_3_PL_GPIO3JD2_INV      (1 << 14)
#define JK_3_PL_IGNORE_0      (2 << 14)
#define JK_3_PL_IGNORE_1      (3 << 14)


// R F REG_INTERRUPT_MASK
#define JK_DET_INTP_MASK                (1)
#define JK_EJECT_INTP_MASK                (1 << 2)
#define MIC_DET_INTP_MASK                (1 << 4)
#define SHORT_KEY_INTP_MASK                (1 << 5)
#define LONG_KEYINTP_MASK                (1 << 6)
#define KEY_RELEASE_INTP_MASK                (1 << 7)
#define RMS_INTP_MASK                      (1 << 8)
#define APR_EMRGENCY_SHTDWN1_INTP_MASK (1 << 9)
#define HSD_COMPLETE_INTP_MASK (1 << 10)
#define IRQ_OE                         (1 << 11)
#define IRQ_DS                         (1 << 12)
#define IRQ_PE                         (1 << 13)
#define IRQ_PS                         (1 << 14)
#define IRQ_PL                         (1 << 15)


// R 10
#define JACK_DET_IRQ_JACK_INSERT       (1)
#define JACK_DET_IRQ_JACK_INSERT_REMOVED       (2)
#define JACK_EJCT_IRQ_JACK_INSERT       (1 << 2)
#define JACK_EJCT_IRQ_JACK_INSERT_REMOVED       (2 << 2)

#define MIC_DET_INT                      (1 << 4)
#define SHORT_KEY_INT                    (1 << 5)
#define LONG_KEY_INT                     (1 << 6)
#define KEY_RELEASE_INT                  (1 << 7)
#define RMS_INT                          (1 << 8)
#define APR_EMRG_SHTDWN                  (1 << 9)
#define HSD_COMPL_ETE_INT                (1 << 10)


// R 11
#define NT_CLR_KEY_STATUS_LK0            (1)
#define NT_CLR_KEY_STATUS_LK1            (1 << 1)
#define NT_CLR_KEY_STATUS_LK2            (1 << 2)
#define NT_CLR_KEY_STATUS_LK3            (1 << 3)
#define NT_CLR_KEY_STATUS_LK4            (1 << 4)
#define NT_CLR_KEY_STATUS_LK5            (1 << 5)
#define NT_CLR_KEY_STATUS_LK6            (1 << 6)
#define NT_CLR_KEY_STATUS_LK7            (1 << 7)

#define NT_CLR_KEY_STATUS_SK0            (1 << 8)
#define NT_CLR_KEY_STATUS_SK1            (1 << 9)
#define NT_CLR_KEY_STATUS_SK2            (1 << 10)
#define NT_CLR_KEY_STATUS_SK3            (1 << 11)
#define NT_CLR_KEY_STATUS_SK4            (1 << 12)
#define NT_CLR_KEY_STATUS_SK5            (1 << 13)
#define NT_CLR_KEY_STATUS_SK6            (1 << 14)
#define NT_CLR_KEY_STATUS_SK7            (1 << 15)


// R 12
#define JACK_DET_INT_DIS                 (1)
#define JACK_EJCT_INT_DIS                (1 << 2)
#define MIC_DET_INT_DIS                  (1 << 4)
#define SHORT_KEY_INT_DIS                (1 << 5)
#define LONG_KEY_INT_DIS                 (1 << 6)
#define KEY_RELEASE_INT_DIS              (1 << 7)
#define RMS_INT_DIS                      (1 << 8)
#define SHRT_SHTD_MIN_INT_DIS            (1 << 9)
#define HSD_COMPL_ETE_INT_DIS            (1 << 10)
#define LONG_KEY0_INT_DIS                (1 << 11)
#define KEY0_RELEASE_INT_DIS             (1 << 12)
#define KEY_RELEASE_CLR_INTR             (1 << 13)


// R 13 SAR_CTRL
#define SAMPLE_SPEED_500NS               (0)
#define SAMPLE_SPEED_4US                 (1 << 0)
#define SAMPLE_SPEED_8US                 (2 << 0)
#define SAMPLE_SPEED_16US                (3 << 0)
#define COMP_SPEED_500NS                 (0 << 2)
#define COMP_SPEED_1US                   (1 << 2)
#define COMP_SPEED_2US                   (2 << 2)
#define COMP_SPEED_4US                   (3 << 2)
#define RES_SEL_35K_OHMS                 (0)
#define RES_SEL_70K_OHMS                 (1 << 4)
#define RES_SEL_170K_OHMS                (2 << 4)
#define RES_SEL_360K_OHMS                (3 << 4)
#define HV_SEL_VDDMIC                    (1 << 7)
#define HV_SEL_NCIBIAS                   (0)
#define SAR_TRACKGAIN_POS                (8)
#define SAR_TRACKGAIN_MSK                (0x7 << SAR_TRACKGAIN_POS)
#define INPUT_SEL_JKSLV                  (1 << 11)
#define INPUT_JKR2                       (0)
#define SAR_ENA                          (1 << 12)
#define SAR_OUT_INV                      (1 << 13)


// R 14
#define HY_COEFF(x)                      (x << 0)
#define SARADC_VDET_COEFF(x)             (x << 4)


#define ENABLE_LEVEL_KEY0                (0)
#define ENABLE_LEVEL_KEY1                (1 << 8)
#define ENABLE_LEVEL_KEY2                (2 << 8)
#define ENABLE_LEVEL_KEY3                (3 << 8)
#define ENABLE_LEVEL_KEY4                (4 << 8)
#define ENABLE_LEVEL_KEY5                (5 << 8)
#define ENABLE_LEVEL_KEY6                (6 << 8)
#define ENABLE_LEVEL_KEY7                (7 << 8)

#define SHORTKEY_DT_30MS                 (0)
#define SHORTKEY_DT_50MS                 (1 << 12)
#define SHORTKEY_DT_100MS                (2 << 13)

#define LONGKEY_DT_500MS                 (0)
#define LONGKEY_DT_1S                    (1 << 14)


// R 15/16/17/18
#define SARADC_VDET_THR_1357_POS         (0)
#define SARADC_VDET_THR_1357_MSK         (0xFF << SARADC_VDET_THR_1357_POS)

#define SARADC_VDET_THR_0246_POS         (8)
#define SARADC_VDET_THR_0246_MSK         (0xFF << SARADC_VDET_THR_0246_POS)


// R 19 REG_GPIO34_CTRL
#define GPIO3_OE                         (1 << 0)
#define GPIO3_DS                         (1 << 1)
#define GPIO3_PS                         (1 << 2)
#define GPIO3_PE                         (1 << 3)
#define GPIO3O                           (1 << 4)
#define GPIO4_OE                         (1 << 7)
#define GPIO4_DS                         (1 << 8)
#define GPIO4_PS                         (1 << 9)
#define GPIO4_PE                         (1 << 10)


// R 1A REG_GPIO12_CTRL
#define GPIO1_OE                         (1 << 0)
#define GPIO1_PE                         (1 << 1)
#define GPIO1_DS                         (1 << 2)
#define GPIO1_PS                         (1 << 3)
#define GPIO1SEL(x)                      (x << 4)
#define GPIO1POL                         (1 << 7)
#define GPIO2_OE                         (1 << 8)
#define GPIO2_PE                         (1 << 9)
#define GPIO2_DS                         (1 << 10)
#define GPIO2_PS                         (1 << 11)



// R 1B REG_TDM_CTRL
#define ADC_TX_SEL_SLOT(x)                  (x << 0)
#define DAC_RIGHT_SEL_SLOT(x)               (x << 4)
#define DAC_LEFT_SEL_SLOT(x)                (x << 6)
#define PCM_OFFSET_MODE_CTRL                (1 << 14)
#define TDM                                 (1 << 15)


// R 1C REG_I2S_PCM_CTRL1
#define AIFMT0_RIGHTJUST                     (0)
#define AIFMT0_LEFTJUST                      (1 << 0)
#define AIFMT0_STANDI2S                      (2 << 0)
#define AIFMT0_PCMA_B                        (3 << 0)

#define WLEN0_16BIT                          (0)
#define WLEN0_20BIT                          (1 << 2)
#define WLEN0_24BIT                          (2 << 2)
#define WLEN0_32BIT                          (3 << 2)

#define ADCPHS0_LEFT                         (0)
#define ADCPHS0_RIGHT                         (1 << 4)

#define DACPHS0_LEFT                         (0)
#define DACPHS0_RIGHT                        (1 << 5)

#define LRP0                                 (1 << 6)
#define BCP0                                 (1 << 7)
#define UA_OFFSET_1S                         (0)
#define UA_OFFSET_2S                         (1)
#define CMB8_0_NORMAL                        (0)
#define CNB8_0_8BIT                          (1 << 10)
#define ADDAP0                               (1 << 11)
#define ADCCM0_ULAW                          (2 << 12)
#define ADCCM0_ALAW                          (3 << 12)
#define DACCM0_ULAW                          (2 << 14)
#define DACCM0_ALAW                          (3 << 14)



// R 1D REG_2S_PCM_CTRL2
#define BLCKDIV_DIV2                         (0)
#define BLCKDIV_DIV4                         (1)
#define BLCKDIV_DIV8                         (2)
#define BLCKDIV_DIV16                        (3)
#define BLCKDIV_DIV32                        (4)
#define BLCKDIV_DIV64                        (5)

#define MS0_SLAVE                            (0)
#define MS0_MASTER                           (1 << 3)

#define ADCDAT0_OE                           (1 << 4)
#define ADCDAT0_PS_PULLUP                    (1 << 5)
#define ADCDAT0_PS_PULLDOWN                  (0)

#define ADCDAT0_PE                           (1 << 6)
#define PCM8BIT0                             (1 << 8)
#define TRI0                                 (1 << 9)
#define PCM_TS_EN0                           (1 << 10)
#define LRC_DIV_DIV256                       (0)
#define LRC_DIV_DIV128                       (1 << 12)
#define LRC_DIV_DIV64                        (2 << 12)
#define LRC_DIV_DIV32                        (3 << 12)
#define I2S_DRV                              (1 << 14)
#define I2S_TRI                              (1 << 15)


// R 1E REG_LEFT_TIME_SLOT
#define TSLOT_L0_POS                          (0)
#define TSLOT_L0_MSK                          (0x3FF << TSLOT_L0_POS)
#define DIS_FS_SHORT_DET                      (1 << 13)
#define FS_ERR_CMP_SEL_252MCLK                (0)
#define FS_ERR_CMP_SEL_253MCLK                (1 << 14)
#define FS_ERR_CMP_SEL_254MCLK                (2 << 14)
#define FS_ERR_CMP_SEL_255MCLK                (3 << 15)


// R 1F REG_RIGHT_TIME_SLOT
#define TSLOT_R0_POS                          (0)
#define TSLOT_R0_MSK                          (0x3FF << TSLOT_R0_POS)


// R 20 REG_BIQ_CTRL
#define BIQ_PATH_SE_ADC                       (0)
#define BIQ_PATH_SE_DAC                       (1)
#define BIQ_COF_SE_SYNC_FS                    (0)
#define BIQ_COF_SE_NO_SYNC                    (1 << 1)
#define ADC_PATH_EN                           (1 << 2)
#define DAC_PATH_EN                           (1 << 3)
#define BIQ_WRT_EN                            (1 << 4)


// R 21 REG_BIQ_COF1
#define BIQ_A1_L_POS                          (0)
#define BIQ_A1_L_MSK                          (0xFFFF << BIQ_A1_L_POS)

// R 22 REG_BIQ_COF2
#define BIQ_A1_H_POS                          (0)
#define BIQ_A1_H_MSK                          (0x7 << BIQ_A1_H_POS)

// R 23 REG_BIQ_COF3
#define BIQ_A2_L_POS                          (0)
#define BIQ_A2_L_MSK                          (0xFFFF << BIQ_A2_L_POS)

// R 24 REG_BIQ_COF4
#define BIQ_A2_H_POS                          (0)
#define BIQ_A2_H_MSK                          (0x7 << BIQ_A2_H_POS)


// R 25 REG_BIQ_COF5
#define BIQ_B0_L_POS                          (0)
#define BIQ_B0_L_MSK                          (0xFFFF << BIQ_B0_L_POS)

// R 26 REG_BIQ_COF6
#define BIQ_B0_H_POS                          (0)
#define BIQ_B0_H_MSK                          (0x7 << BIQ_B0_H_POS)


// R 27 REG_BIQ_COF7
#define BIQ_B1_L_POS                          (0)
#define BIQ_B1_L_MSK                          (0xFFFF << BIQ_B1_L_POS)

// R 28 REG_BIQ_COF8
#define BIQ_B1_H_POS                          (0)
#define BIQ_B1_H_MSK                          (0x7 << BIQ_B1_H_POS)


// R 29 REG_BIQ_COF9
#define BIQ_B2_L_POS                          (0)
#define BIQ_B2_L_MSK                          (0xFFFF << BIQ_B2_L_POS)

// R 2A REG_BIQ_COF10
#define BIQ_B2_H_POS                          (0)
#define BIQ_B2_H_MSK                          (0x7 << BIQ_B2_H_POS)


// R 2B REG_ADC_RATE
#define ADC_RATE_32                           (0)
#define ADC_RATE_64                          (1)
#define ADC_RATE_128                          (2)
#define ADC_RATE_256                           (3)

#define SMPL_RATE_48K                         (0)
#define SMPL_RATE_32K                         (1 << 5)
#define SMPL_RATE_96K                         (3 << 5)
#define SMPL_RATE_192K                        (7 << 5)


// R 2C REG_DAC_CTRL1
#define DAC_RATE_64                           (0)
#define DAC_RATE_256                          (1)
#define DAC_RATE_128                          (2)
#define DAC_RATE_32                           (4)
#define CUC_GAIN_ADJ(x)                       (x << 4)
#define DEM_DLY_N                             (1 << 14)
#define DISABLE_DEM                           (1 << 15)


// R 2D REG_DAC_CTRL2
#define DACPR_INVERT                          (1)
#define DAC_PL_INVERT                         (1 << 1)
#define DAC_STEP_SEL_DACCLK                   (4 << 4)
#define DAC_STEP_SEL_DLY1_MCLK                (5 << 4)
#define DAC_STEP_SEL_DLY2_MCLK                (6 << 4)
#define DAC_STEP_SEL_DLY3_MCLK                (7 << 4)
#define DSMOD_DITHER(x)                       (x << 7)
#define DEM_DITHER(x)                         (x << 12)


// R 2F REG_DAC_DGAIN_CTRL
#define DAC0_TO_DAC1_ST(x)                    (x << 0)
#define DAC1_TO_DAC0_ST(x)                    (x << 8)

// R 30 REG_ADC_DGAIN_CTRL
#define DGAINL_ADC0(x)                        (x)
#define ADC_TO_DAC_ST1(x)                     (x << 8)
#define ADC_TO_DAC_ST0(x)                     (x << 12)

// R 31 REG_MUTE_CTRL
#define ADC_SMUTE_EN                          (1 << 1)
#define ADC_ZC_UP_EN                          (1 << 2)
#define SMUTE_CTRL                            (1 << 8)
#define SMUTE_EN                              (1 << 9)
#define AMUTE_CTRL                            (1 << 10)
#define AMUTE_EN                              (1 << 11)
#define DAC_ZC_UP_EN                          (1 << 12)
#define PGA_SMUTE_STEP_128                    (0 << 14)
#define PGA_SMUTE_STEP_32                     (1 << 14)
#define PGA_SMUTE_STEP_16                     (2 << 14)
#define PGA_SMUTE_STEP_1                      (3 << 14)


// R 32 REG_HSVOL_CTRL
#define HSPGA1_VOL(x)                         (x << 0)
#define HSPGA0_VOL(x)                         (x << 6)
#define MUTE_HSPGA1                           (1 << 12)
#define MUTE_HSPGA0                           (1 << 13)
#define HSPGA_MUTE_AUTO_MODE                  (1 << 14)
#define HSPGA_MUTE_EN                         (1 << 15)


// R 33 REG_DACL_CTRL
#define DGAINL_DAC(x)                         (x << 0)
#define DAC_CH_SEL0_LEFT                      (0)
#define DAC_CH_SEL0_RIGHT                     (1 << 9)
#define DAC_MIXER_L                           (1 << 14)
#define DAC_MIXER_R                           (1 << 15)


// R 34 REG_DACR_CTRL
#define DGAINR_DAC(x)                         (x << 0)
#define DAC_CH_SEL1_LEFT                      (0)
#define DAC_CH_SEL1_RIGHT                     (1 << 9)

// R 38 REG_ADC_DRC_KNEE_IP12
#define DRC_KNEE1_IP_ADC1(x)                  (x << 0)
#define DRC_SMTH_ENA_ADC1                     (1 << 7)
#define DRC_KNEE2_IP_ADC1(x)                  (x << 8)
#define DRC_ENA_ADC1                          (1 << 15)


// R 39 REG_ADC_DRC_KNEE_IP34
#define DRC_KNEE3_IP_ADC1(x)                 (x << 0)
#define DRC_KNEE4_IP_ADC1(x)                 (x << 8)


// R 3A REG_ADC_DRC_SLOPES
#define DRC_LMT_SLP_ADC1_0                   (0)
#define DRC_LMT_SLP_ADC1_1_2                 (1)
#define DRC_LMT_SLP_ADC1_1_4                 (2)
#define DRC_LMT_SLP_ADC1_1_8                 (3)
#define DRC_LMT_SLP_ADC1_1_16                (4)
#define DRC_LMT_SLP_ADC1_1_32                (5)
#define DRC_LMT_SLP_ADC1_1_64                (6)
#define DRC_LMT_SLP_ADC1_1                   (7)

#define DRC_CMP1_SLP_ADC1_0                  (0)
#define DRC_CMP1_SLP_ADC1_1_2                (1 << 3)
#define DRC_CMP1_SLP_ADC1_1_4                (2 << 3)
#define DRC_CMP1_SLP_ADC1_1_8                (3 << 3)
#define DRC_CMP1_SLP_ADC1_1_16               (4 << 3)
#define DRC_CMP1_SLP_ADC1_1                  (7 << 3)

#define DRC_CMP2_SLP_ADC1_0                  (0)
#define DRC_CMP2_SLP_ADC1_1_2                (1 << 6)
#define DRC_CMP2_SLP_ADC1_1_4                (2 << 6)
#define DRC_CMP2_SLP_ADC1_1_8                (3 << 6)
#define DRC_CMP2_SLP_ADC1_1_16               (4 << 6)
#define DRC_CMP2_SLP_ADC1_1                  (7 << 6)

#define DRC_EXP_SLP_ADC1_1_1                 (0)
#define DRC_EXP_SLP_ADC1_2_1                 (1 << 9)
#define DRC_EXP_SLP_ADC1_4_1                 (2 << 9)

#define DRC_NG_SLP_ADC1_1_1                 (0)
#define DRC_NG_SLP_ADC1_2_1                 (1 << 12)
#define DRC_NG_SLP_ADC1_4_1                 (2 << 12)
#define DRC_NG_SLP_ADC1_8_1                 (3 << 12)



// R 3B REG_ADC_DRC_ATKDCY
#define DRC_DCY_ADC1_63                      (0)
#define DRC_DCY_ADC1_127                     (1)
#define DRC_DCY_ADC1_255                     (2)
#define DRC_DCY_ADC1_511                     (3)
#define DRC_DCY_ADC1_1023                    (4)
#define DRC_DCY_ADC1_2047                    (5)
#define DRC_DCY_ADC1_4095                    (6)
#define DRC_DCY_ADC1_8191                    (7)
#define DRC_DCY_ADC1_16383                   (8)
#define DRC_DCY_ADC1_32757                   (9)
#define DRC_DCY_ADC1_65535                   (10)

#define DRC_ATK_ADC1_x1                      (0)
#define DRC_ATK_ADC1_x3                      (1 << 4)
#define DRC_ATK_ADC1_x7                      (2 << 4)
#define DRC_ATK_ADC1_x15                     (3 << 4)
#define DRC_ATK_ADC1_x31                     (4 << 4)
#define DRC_ATK_ADC1_x63                     (5 << 4)
#define DRC_ATK_ADC1_x127                    (6 << 4)
#define DRC_ATK_ADC1_x255                    (7 << 4)
#define DRC_ATK_ADC1_x511                    (8 << 4)
#define DRC_ATK_ADC1_x1023                   (9 << 4)
#define DRC_ATK_ADC1_x2047                   (10 << 4)
#define DRC_ATK_ADC1_x4095                   (11 << 4)
#define DRC_ATK_ADC1_x8191                   (12 << 4)


#define DRC_PK_COEF2_ADC1_63                 (0)
#define DRC_PK_COEF2_ADC1_127                (1 << 8)
#define DRC_PK_COEF2_ADC1_255                (2 << 8)
#define DRC_PK_COEF2_ADC1_511                (3 << 8)
#define DRC_PK_COEF2_ADC1_1023               (4 << 8)
#define DRC_PK_COEF2_ADC1_2047               (5 << 8)
#define DRC_PK_COEF2_ADC1_4095               (6 << 8)
#define DRC_PK_COEF2_ADC1_8191               (7 << 8)

#define DRC_PK_COEF1_ADC1_x1                 (0)
#define DRC_PK_COEF1_ADC1_x3                 (1 << 12)
#define DRC_PK_COEF1_ADC1_x7                 (2 << 12)
#define DRC_PK_COEF1_ADC1_x15                (3 << 12)
#define DRC_PK_COEF1_ADC1_x31                (4 << 12)
#define DRC_PK_COEF1_ADC1_x63                (5 << 12)
#define DRC_PK_COEF1_ADC1_x127               (6 << 12)
#define DRC_PK_COEF1_ADC1_x255               (7 << 12)


// R 45 REG_DAC_DRC_KNEE_IP12
#define DRC_KNEE1_IP_DAC(x)                  (x)
#define DRC_SMTH_ENA_DAC                     (1 << 7)
#define DRC_KNEE2_IP_DAC(x)                  (x << 8)
#define DRC_ENA_DAC                          (1 << 15)


// R 46 REG_DAC_DRC_KNEE_IP34
#define DRC_KNEE3_IP_DAC(x)                  (x)
#define DRC_KNEE4_IP_DAC(x)                  (x << 8)

// R 47 REG_DAC_DRC_SLOPES
#define DRC_LMT_SLP_DAC_0                    (0)
#define DRC_LMT_SLP_DAC_1_2                  (1)
#define DRC_LMT_SLP_DAC_1_4                  (2)
#define DRC_LMT_SLP_DAC_1_8                  (3)
#define DRC_LMT_SLP_DAC_1_16                 (4)
#define DRC_LMT_SLP_DAC_1_32                 (5)
#define DRC_LMT_SLP_DAC_1_64                 (6)
#define DRC_LMT_SLP_DAC_1_1                  (7)

#define DRC_CMP1_SLP_DAC_0                   (0)
#define DRC_CMP1_SLP_DAC_1_2                 (1 << 3)
#define DRC_CMP1_SLP_DAC_1_4                 (2 << 3)
#define DRC_CMP1_SLP_DAC_1_8                 (3 << 3)
#define DRC_CMP1_SLP_DAC_1_16                (4 << 3)
#define DRC_CMP1_SLP_DAC_1                   (7 << 3)

#define DRC_CMP2_SLP_DAC_0                   (0)
#define DRC_CMP2_SLP_DAC_1_2                 (1 << 6)
#define DRC_CMP2_SLP_DAC_1_4                 (2 << 6)
#define DRC_CMP2_SLP_DAC_1_8                 (3 << 6)
#define DRC_CMP2_SLP_DAC_1_16                (4 << 6)
#define DRC_CMP2_SLP_DAC_1                   (7 << 6)

#define DRC_EXP_SLP_DAC_1_1                  (0)
#define DRC_EXP_SLP_DAC_2_1                  (1 << 9)
#define DRC_EXP_SLP_DAC_4_1                  (2 << 9)
#define DRC_EXP_SLP_DAC_8_1                  (3 << 9)

#define DRC_NG_SLP_DAC_1_1                  (0)
#define DRC_NG_SLP_DAC_2_1                  (1 << 12)
#define DRC_NG_SLP_DAC_4_1                  (2 << 12)
#define DRC_NG_SLP_DAC_8_1                  (3 << 12)


// R 48 REG_DAC_DRC_ATKDCY
#define DRC_DCY_DAC_63                      (0)
#define DRC_DCY_DAC_127                     (1)
#define DRC_DCY_DAC_255                     (2)
#define DRC_DCY_DAC_511                     (3)
#define DRC_DCY_DAC_1023                    (4)
#define DRC_DCY_DAC_2047                    (5)
#define DRC_DCY_DAC_4095                    (6)
#define DRC_DCY_DAC_8191                    (7)
#define DRC_DCY_DAC_16383                   (8)
#define DRC_DCY_DAC_32757                   (9)
#define DRC_DCY_DAC_65535                   (10)

#define DRC_ATK_DAC_x1                      (0)
#define DRC_ATK_DAC_x3                      (1 << 4)
#define DRC_ATK_DAC_x7                      (2 << 4)
#define DRC_ATK_DAC_x15                     (3 << 4)
#define DRC_ATK_DAC_x31                     (4 << 4)
#define DRC_ATK_DAC_x63                     (5 << 4)
#define DRC_ATK_DAC_x127                    (6 << 4)
#define DRC_ATK_DAC_x255                    (7 << 4)
#define DRC_ATK_DAC_x511                    (8 << 4)
#define DRC_ATK_DAC_x1023                   (9 << 4)
#define DRC_ATK_DAC_x2047                   (10 << 4)
#define DRC_ATK_DAC_x4095                   (11 << 4)
#define DRC_ATK_DAC_x8191                   (12 << 4)


#define DRC_PK_COEF2_DAC_63                 (0)
#define DRC_PK_COEF2_DAC_127                (1 << 8)
#define DRC_PK_COEF2_DAC_255                (2 << 8)
#define DRC_PK_COEF2_DAC_511                (3 << 8)
#define DRC_PK_COEF2_DAC_1023               (4 << 8)
#define DRC_PK_COEF2_DAC_2047               (5 << 8)
#define DRC_PK_COEF2_DAC_4095               (6 << 8)
#define DRC_PK_COEF2_DAC_8191               (7 << 8)

#define DRC_PK_COEF1_DAC_x1                 (0)
#define DRC_PK_COEF1_DAC_x3                 (1 << 12)
#define DRC_PK_COEF1_DAC_x7                 (2 << 12)
#define DRC_PK_COEF1_DAC_x15                (3 << 12)
#define DRC_PK_COEF1_DAC_x31                (4 << 12)
#define DRC_PK_COEF1_DAC_x63                (5 << 12)
#define DRC_PK_COEF1_DAC_x127               (6 << 12)
#define DRC_PK_COEF1_DAC_x255               (7 << 12)


// R 4C REG_MODE_CTRL
#define DACIN_SRC_DAC_BIQUAD                (0)
#define DACIN_SRC_DRC_DAC                   (1)
#define DACIN_SRC_DAC_MIXER                 (2)
#define DACIN_SRC_BUILDIN_SINE              (3)
#define DACIN_SRC_DRC_LAW_DECODE            (4)


// R 50 REG_CLASSG_CTRL
#define CLASSG_EN                           (1)
#define CLASSG_CMP_EN_L_DAC                 (1 << 1)
#define CLASSG_CMP_EN_R_DAC                 (1 << 2)
#define CLASSG_THRSLD_1_16                  (0)
#define CLASSG_THRSLD_1_8                   (1 << 4)
#define CLASSG_THRSLD_3_16                  (2 << 4)
#define CLASSG_THRSLD_1_4                   (3 << 4)

#define CLASSG_TIMER_1MS                    (1 << 8)
#define CLASSG_TIMER_2MS                    (2 << 8)
#define CLASSG_TIMER_8MS                    (4 << 8)
#define CLASSG_TIMER_16MS                   (8 << 8)
#define CLASSG_TIMER_32MS                   (16 << 8)
#define CLASSG_TIMER_64MS                   (32 << 8)
#define CLASSG_CLK_SRC_2M                   (0)
#define CLASSG_CLK_SRC_1_3MCLK              (1 << 14)
#define CLASSG_CLK_SRC_MCLK                 (2 << 14)
#define CLASSG_CLK_SRC_DISABLE_CLK          (3 << 14)

// R 51 REG_OPT_EFU
#define WL_BIN_POS                          (0)
#define WL_BIN_MSK                          (0x3F << WL_BIN_POS)

#define STROBE_IN                           (1 << 6)
#define PGEN_IN                             (1 << 7)
#define NR_IN                               (1 << 8)
#define STANDBY_IN                          (1 << 15)

// R 55 REG_MISC_CTRL
#define D2A_LOOP                            (1 << 1)
#define RAM_TEST_START                      (1 << 3)
#define SPIEN                               (1 << 15)
#define I2CEN                               (0)

// R 58 REG_I2C_DEVICE_ID
#define Software_ID                         (0x3)
#define Silicon_Revision_ID                 (0x7 << 2)
#define JKDETL                              (0x1 << 5)
#define GPIO3JD2                            (0x1 << 6)
#define GPIO2JD1                            (0x1 << 7)
#define I2C_DEVICE_ID                       (0x3F << 9)

// R 59 REG_SARDOUT_RAM_STATUS
#define SARADC_DOUT                         (0xff)
#define ANALOG_MUTE                         (0x1 << 10)
#define RAM_TEST_FAIL                       (0x3 << 11)
#define RATM_TEST_FINISH                    (0x1 << 13)


// R 66 REG_BIAS_ADJ
#define BIASADJ_NORMAL                      (0x0)
#define BIASADJ_9                           (0x1 << 0)
#define BIASADJ_17                          (0x2 << 0)
#define BIASADJ_11                          (0x3 << 0)
#define VMIDSEL_OPEN                        (0x0 << 4)
#define VMIDSEL_25K_OHM                     (0x1 << 4)
#define VMIDSEL_125K_OHM                    (0x2 << 4)
#define VMIDSEL_2P5K_OHM                    (0x3 << 4)
#define VMIDEN                              (0x1 << 6)
#define MUTEL                               (0x1 << 13)

// R 68 REG_TRIM_SETTINGS
#define DIS_OC_RIGHT                        (0x2)
#define DIS_OC_LEFT                         (0x4)
#define INTEG_ICUTHS                        (0x1 << 8)
#define INTEG_IBCTRHS                       (0x1 << 9)
#define DRV_ICUTHS                          (0x1 << 14)
#define DRV_IBCTRHS                         (0x1 << 15)


// R 69 REG_ANALOG_CONTROL_1
#define ENJKDETL                            (0x1 << 0)
#define JKDETLPOL                           (0x1 << 1)
#define JD1POL                              (0x1 << 2)
#define GPIO2THH_P85x                       (0x0)
#define GPIO2THH_P78x                       (0x2 << 4)
#define GPIO2THH_P6x                        (0x3 << 4)
#define GPIO2THL_P22x                       (0x0)
#define GPIO2THL_P4x                        (0x2 << 6)
#define GPIO2THL_P5x                        (0x3 << 6)
#define Pullup_GPIO2_1M                     (0x0)
#define Pullup_GPIO2_100K                   (0x1 << 8)
#define GPIO3THH_P85x                       (0x0)
#define GPIO3THH_P78x                       (0x2 << 9)
#define GPIO3THH_P6x                        (0x3 << 9)
#define GPIO3THL_P22x                       (0x0)
#define GPIO3THL_P4x                        (0x2 << 11)
#define GPIO3THL_P5x                        (0x3 << 11)
#define Pullup_GPIO3_1M                     (0x0)
#define Pullup_GPIO3_100K                   (0x1 << 13)



// R 6A REG_ANALOG_CONTROL_2
#define CAP_0                               (0x1)
#define CAP_1                               (0x1 << 1)
#define MUTEMICN                            (0x1 << 2)
#define MUTEMICP                            (0x1 << 3)
#define AB_ADJ                              (0x1 << 7)



// R 71 REG_ANALOG_ADC_1
#define CHOPF0_DIV2                         (0)
#define CHOPF0_DIV4                         (0x1 << 0)
#define CHOPF0_DIV8                         (0x2 << 0)
#define CHOPF0_DIV16                        (0x3 << 0)
#define CHOPORDER                           (0x1 << 2)
#define CHOPFIXED                           (0x1 << 3)
#define CHOPRESETN                          (0x1 << 4)
#define CHOPPHASE                           (0x1 << 5)
#define CHOPENABLE                          (0x1 << 6)
#define RESETL                              (0x1 << 8)


// R 72 REG_ANALOG_ADC_2
#define MON4TH                              (0x1 << 0)
#define MON3RD                              (0x1 << 1)
#define MON2ND                              (0x1 << 2)
#define MON1ST                              (0x1 << 3)
#define MONADD                              (0x1 << 4)
#define LFSRRESETN                          (0x1 << 5)
#define PDNOTL                              (0x1 << 6)

#define VREFSEL_ANALOG                      (0x0 << 8)
#define VREFSEL_VMIDE                       (0x1 << 8)
#define VREFSEL_VMIDE_P5DB                  (0x2 << 8)
#define VREFSEL_ANALOG_1DB                  (0x3 << 8)

#define BIAS_NORMAL                        (0x0 << 10)
#define BIAS_BOUBLE                        (0x1 << 10)
#define BIAS_HALF                          (0x2 << 10)
#define BIAS_QUARTER                       (0x3 << 10)
#define ADC_UPL                             (0x1 << 13)



// R 73 REG_RDAC
#define DACVREFSEL(x)                      (x << 2)
#define CLK_DAC_DELAY_0NSEC                (0)
#define CLK_DAC_DELAY_1NSEC                (0x1 << 4)
#define CLK_DAC_DELAY_2NSEC                (0x2 << 4)
#define CLK_DAC_DELAY_3NSEC                (0x3 << 4)
#define CLK_DAC_DELAY_4NSEC                (0x4 << 4)
#define CLK_DAC_DELAY_N3NSEC               (0x5 << 4)
#define CLK_DAC_DELAY_N2NSEC               (0x6 << 4)
#define CLK_DAC_DELAY_N1NSEC               (0x7 << 4)

#define FC_CTR                             (0x1 << 7)
#define CLK_DAC_EN_R                       (0x1 << 9)
#define CLK_DAC_EN_L                       (0x1 << 8)
#define DAC_EN_R                           (0x1 << 13)
#define DAC_EN_L                           (0x1 << 12)
#define FS_BCLK_ENB                        (0x1 << 15)


// R 74 REG_MIC_BIAS
#define MICBIASLVL1_VDDA                   (0)
#define MICBIASLVL1_1x                     (0x1 << 0)
#define MICBIASLVL1_1P1x                   (0x2 << 0)
#define MICBIASLVL1_1P2x                   (0x3 << 0)
#define MICBIASLVL1_1P3x                   (0x4 << 0)
#define MICBIASLVL1_1P4x                   (0x5 << 0)
#define MICBIASLVL1_1P53x                  (0x6 << 0)

#define NOCAP                              (0x1 << 6)
#define POWERUP                            (0x1 << 8)
#define LOWNOISE                           (0x1 << 10)
#define INT2KA                             (0x1 << 12)
#define INT2KB                             (0x1 << 14)


// R 76 REG_BOOST
#define NAMP_THRSHLD(x)                    (x << 0)
#define PAMP_THRSHLD(x)                    (x << 2)
#define HS_SHRT_THRESHLD(x)                (x << 4)
#define EN_SHRT_SHTDWN                     (0x1 << 6)
#define SHRT_SHTDWN_DIG_EN                 (0x1 << 7)
#define BOOSTGDIS                          (0x1 << 8)
#define BOOSTDIS                           (0x1 << 9)
#define BYPS_IBCTR                         (0x1 << 10)
#define DISCHRG                            (0x1 << 11)
#define BIASEN                             (0x1 << 12)
#define PDVMDFST                           (0x1 << 13)
#define STG2_SEL                           (0x1 << 14)
#define CLR_APR_EMRGENCY_SHTDWN            (0x1 << 15)


// R 77 REG_FEPGA
#define FEPGA_MODEL_ANIT_ALIASING          (0x1 << 0)
#define FEPGA_MODEL_DISCONNECT_MICPN       (0x1 << 1)
#define FEPGA_MODEL_12KOHM_SHORT           (0x1 << 3)

#define IBCTR_CODE(x)                      (x << 8)
#define IB_LOOP_CTR                        (0x1 << 11)
#define CMLCK_ADJ(x)                       (x << 12)
#define ACDC_CTRL_MICP_VREF                (0x1 << 14)
#define ACDC_CTRL_MICN_VREF                (0x1 << 15)


// R 7F REG_POWER_UP_CONTROL
#define PUP_MAIN_DRV_LEFT_HP                (0x1 << 0)
#define PUP_MAIN_DRV_RIGHT_HP               (0x1 << 1)
#define PUP_DRV_INSTG_LEFT_HP               (0x1 << 2)
#define PUP_DRV_INSTG_RIGHT_HP              (0x1 << 3)
#define PUP_INTEG_LEFT_HP                   (0x1 << 4)
#define PUP_INTEG_RIGHT_HP                  (0x1 << 5)
#define FEPGA_GAIN(x)                       (x << 8)
#define PUFEPGA                             (0x1 << 14)



// R 80 REG_CHARGE_PUMP_AND_POWER_DOWN_CONTROL
#define SHCIRSEL1_HIGH                      (0x1)
#define SHCIRSEL1_LOW                       (0)
#define SHCIRSEL2_HIGH                      (0x1 << 1)
#define SHCIRSEL2_LOW                       (0)
#define DISCHARGEVPOS                       (0x1 << 2)
#define DISCHARGEVEE                        (0x1 << 3)
#define PRECHARGE                           (0x1 << 4)
#define RNIN                                (0x1 << 5)
#define JAMFORCE1                           (0x1 << 6)
#define JAMFORCE2                           (0x1 << 7)
#define PD_DAC_ENABLE                       (0x3 << 8)
#define JAMNODCLOW                          (0x1 << 10)
#define ADCDAT_DS                           (0x1 << 12)
#define FS_DS                               (0x1 << 13)
#define BCLK_DS                             (0x1 << 14)


// R 81 REG_CHARGE_PUMP_INPUT_READ
#define FORCE1BUF                           (0x1 << 0)
#define VCOMPBUF                            (0x1 << 1)
#define VPOSOK                              (0x1 << 2)
#define RN2BUF                              (0x1 << 3)
#define NODCBUF                             (0x1 << 4)
#define MODE1BUF                            (0x1 << 5)
#define APR_EMRGNCY_SHTDWN                  (0x1 << 15)


// R 82 REG_GENERAL_STATUS
#define GPIO1_IN                            (0x1 << 0)
#define GPIO2_IN                            (0x1 << 1)
#define GPIO3_IN                            (0x1 << 2)
#define GPIO4_IN                            (0x1 << 3)
#define JKDETL1                             (0x1 << 4)
#define JKDET_ON                            (0x1 << 5)
#define JK_INSERT_INTR                      (0x1 << 6)
#define JK_EJECT_INTR                       (0x1 << 7)
#define OUT1                                (0x1 << 8)
#define OUT2                                (0x1 << 9)
#define OUT1_OUT                            (0x1 << 10)
#define OUT2_OUT                            (0x1 << 11)

typedef struct
{
    char      *i2c_bus_name;

    char      *i2s_bus_name;

    rt_int32_t pin_phonejack_en;

    rt_int32_t pin_phonejack_det;

} S_NU_NAU88L25_CONFIG;

int nu_hw_nau88l25_init(S_NU_NAU88L25_CONFIG *psCodecConfig);

#endif /* __ACODEC_NAU88L25_H__ */
