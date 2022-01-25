/*****************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_pwc.h
 **
 ** A detailed description is available at
 ** @link PwcGroup PWC description @endlink
 **
 **   - 2018-10-28  CDT  First version for Device Driver Library of PWC.
 **
 ******************************************************************************/
#ifndef __HC32F460_PWC_H__
#define __HC32F460_PWC_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

#if (DDL_PWC_ENABLE == DDL_ON)


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup PwcGroup Power Control(PWC)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  The power down mode.
 **
 ******************************************************************************/
typedef enum en_pwc_powerdown_md
{
    PowerDownMd1                    = 0u,   ///< Power down mode 1.
    PowerDownMd2                    = 1u,   ///< Power down mode 2.
    PowerDownMd3                    = 2u,   ///< Power down mode 3.
    PowerDownMd4                    = 3u,   ///< Power down mode 4.
}en_pwc_powerdown_md_t;

/**
 *******************************************************************************
 ** \brief  The IO retain status under power down mode.
 **
 ******************************************************************************/
typedef enum en_pwc_iortn
{
    IoPwrDownRetain                 = 0u,   ///< Io keep under power down mode.
    IoPwrRstRetain                  = 1u,   ///< Io keep after power reset.
    IoHighImp                       = 2u,   ///< IO high impedance either power down or power reset.
}en_pwc_iortn_t;

/**
 *******************************************************************************
 ** \brief  The driver ability while different speed mode enter stop mode.
 **
 ******************************************************************************/
typedef enum en_pwc_stopdas
{
    StopHighspeed                    = 0u,   ///< The driver ability while high speed mode enter stop mode.
    StopUlowspeed                    = 3u,   ///< The driver ability while ultra_low speed mode enter stop mode.
}en_pwc_stopdas_t;

/**
 *******************************************************************************
 ** \brief  The dynamic power driver voltage select.
 **
 ******************************************************************************/
typedef enum en_pwc_rundrvs
{
    RunUHighspeed                  = 0u,   ///< The ultra_high speed.
    RunUlowspeed                   = 2u,   ///< The ultra_low speed.
    RunHighspeed                   = 3u,   ///< The high speed.
}en_pwc_rundrvs_t;

/**
 *******************************************************************************
 ** \brief  The dynamic power driver ability scaling.
 **
 ******************************************************************************/
typedef enum en_pwc_drvability_sca
{
    Ulowspeed                       = 8u,   ///< The ultra_low speed.
    HighSpeed                       = 15u,  ///< The high speed.
}en_pwc_drvability_sca_t;

/**
 *******************************************************************************
 ** \brief  The power down wake up time select.
 **
 ******************************************************************************/
typedef enum en_pwc_waketime_sel
{
    Vcap01                          = 0u,   ///< Wake up while vcap capacitance 2*0.1uf.
    Vcap0047                        = 1u,  ///< Wake up while vcap capacitance 2*0.047uf.
}en_pwc_waketime_sel_t;

/**
 *******************************************************************************
 ** \brief  The wait or not wait flash stable while stop mode awake.
 **
 ******************************************************************************/
typedef enum en_pwc_stop_flash_sel
{
    Wait                            = 0u,  ///< wait flash stable.
    NotWait                         = 1u,  ///< Not Wait flash stable.
}en_pwc_stop_flash_sel_t;

/**
 *******************************************************************************
 ** \brief  The clk value while stop mode awake.
 **
 ******************************************************************************/
typedef enum en_pwc_stop_clk_sel
{
    ClkFix                          = 0u,  ///< clock fix.
    ClkMrc                          = 1u,  ///< clock source is MRC, only ram code.
}en_pwc_stop_clk_sel_t;

/**
 *******************************************************************************
 ** \brief  The power down wake up event edge select.
 **
 ******************************************************************************/
typedef enum en_pwc_edge_sel
{
    EdgeFalling                      = 0u,  ///< Falling edge.
    EdgeRising                       = 1u,  ///< Rising edge.
}en_pwc_edge_sel_t;

/**
 *******************************************************************************
 ** \brief  The voltage detect edge select.
 **
 ******************************************************************************/
typedef enum en_pwc_pvdedge_sel
{
    OverVcc                         = 0u,  ///< PVD > VCC.
    BelowVcc                        = 1u,  ///< PVD < VCC.
}en_pwc_pvdedge_sel_t;

/**
 *******************************************************************************
 ** \brief  The flag of wake_up timer compare result.
 **
 ******************************************************************************/
typedef enum en_pwc_wkover_flag
{
    UnEqual                         = 0u,  ///< Timer value unequal with the wake_up compare value whitch set.
    Equal                           = 1u,  ///< Timer value equal with the wake_up compare value whitch set..
}en_pwc_wkover_flag_t;

/**
 *******************************************************************************
 ** \brief  The RAM operating mode.
 **
 ******************************************************************************/
typedef enum en_pwc_ram_op_md
{
    HighSpeedMd                     = 0x8043, ///< Work at high speed.
    UlowSpeedMd                     = 0x9062, ///< Work at ultra low speed.
}en_pwc_ram_op_md_t;

/**
 *******************************************************************************
 ** \brief  The wake up clock select.
 **
 ******************************************************************************/
typedef enum en_pwc_wkclk_sel
{
    Wk64hz                          = 0u,  ///< 64Hz.
    WkXtal32                        = 1u,  ///< Xtal32.
    WkLrc                           = 2u,  ///< Lrc.
}en_pwc_wkclk_sel_t;

/**
 *******************************************************************************
 ** \brief  The pvd digital filtering sampling clock select.
 **
 ******************************************************************************/
typedef enum en_pwc_pvdfiltclk_sel
{
    PvdLrc025                       = 0u,  ///< 0.25 LRC cycle.
    PvdLrc05                        = 1u,  ///< 0.5 LRC cycle.
    PvdLrc1                         = 2u,  ///< LRC 1 div.
    PvdLrc2                         = 3u,  ///< LRC 2 div.
}en_pwc_pvdfiltclk_sel_t;

/**
 *******************************************************************************
 ** \brief  The pvd2 level select.
 **
 ******************************************************************************/
typedef enum en_pwc_pvd2level_sel
{
    Pvd2Level0                     = 0u,  ///< 2.1V.while high_speed & ultra_low speed mode, 2.20V.while ultra_high speed mode.
    Pvd2Level1                     = 1u,  ///< 2.3V.while high_speed & ultra_low speed mode, 2.40V.while ultra_high speed mode.
    Pvd2Level2                     = 2u,  ///< 2.5V.while high_speed & ultra_low speed mode, 2.67V.while ultra_high speed mode.
    Pvd2Level3                     = 3u,  ///< 2.6V.while high_speed & ultra_low speed mode, 2.77V.while ultra_high speed mode.
    Pvd2Level4                     = 4u,  ///< 2.7V.while high_speed & ultra_low speed mode, 2.88V.while ultra_high speed mode.
    Pvd2Level5                     = 5u,  ///< 2.8V.while high_speed & ultra_low speed mode, 2.98V.while ultra_high speed mode.
    Pvd2Level6                     = 6u,  ///< 2.9V.while high_speed & ultra_low speed mode, 3.08V.while ultra_high speed mode.
    Pvd2Level7                     = 7u,  ///< 1.1V.while high_speed & ultra_low speed mode, 1.15V.while ultra_high speed mode.
}en_pwc_pvd2level_sel_t;

/**
 *******************************************************************************
 ** \brief  The pvd1 level select.
 **
 ******************************************************************************/
typedef enum en_pwc_pvd1level_sel
{
    Pvd1Level0                     = 0u,  ///< 2.0V.while high_speed & ultra_low speed mode, 2.09V.while ultra_high speed mode.
    Pvd1Level1                     = 1u,  ///< 2.1V.while high_speed & ultra_low speed mode, 2.20V.while ultra_high speed mode.
    Pvd1Level2                     = 2u,  ///< 2.3V.while high_speed & ultra_low speed mode, 2.40V.while ultra_high speed mode.
    Pvd1Level3                     = 3u,  ///< 2.5V.while high_speed & ultra_low speed mode, 2.67V.while ultra_high speed mode.
    Pvd1Level4                     = 4u,  ///< 2.6V.while high_speed & ultra_low speed mode, 2.77V.while ultra_high speed mode.
    Pvd1Level5                     = 5u,  ///< 2.7V.while high_speed & ultra_low speed mode, 2.88V.while ultra_high speed mode.
    Pvd1Level6                     = 6u,  ///< 2.8V.while high_speed & ultra_low speed mode, 2.98V.while ultra_high speed mode.
    Pvd1Level7                     = 7u,  ///< 2.9V.while high_speed & ultra_low speed mode, 3.08V.while ultra_high speed mode.
}en_pwc_pvd1level_sel_t;

/**
 *******************************************************************************
 ** \brief  The pvd interrupt select.
 **
 ******************************************************************************/
 typedef enum en_pwc_pvd_int_sel
{
    NonMskInt                       = 0u,  ///< Non-maskable Interrupt.
    MskInt                          = 1u,  ///< Maskable Interrupt.
}en_pwc_pvd_int_sel_t;

/**
 *******************************************************************************
 ** \brief  The handle of pvd mode.
 **
 ******************************************************************************/
 typedef enum en_pwc_pvd_md
{
    PvdInt                          = 0u,  ///< The handle of pvd is interrupt.
    PvdReset                        = 1u,  ///< The handle of pvd is reset.
}en_pwc_pvd_md_t;

/**
 *******************************************************************************
 ** \brief  The unit of pvd detect.
 **
 ******************************************************************************/
 typedef enum en_pwc_pvd
{
    PvdU1                        = 0u,      ///< The uint1 of pvd detect.
    PvdU2                        = 1u,      ///< The unit2 of pvd detect.
}en_pwc_pvd_t;

/**
 *******************************************************************************
 ** \brief  The power mode  configuration.
 **
 ******************************************************************************/
typedef struct stc_pwc_pwr_mode_cfg
{
    en_pwc_powerdown_md_t   enPwrDownMd;    ///< Power down mode.
    en_functional_state_t   enRLdo;         ///< Enable or disable RLDO.
    en_functional_state_t   enRetSram;      ///< Enable or disable Ret_Sram.
    en_pwc_iortn_t          enIoRetain;     ///< IO retain.
    en_pwc_waketime_sel_t   enPwrDWkupTm;   ///< The power down wake up time select.
}stc_pwc_pwr_mode_cfg_t;

/**
 *******************************************************************************
 ** \brief  The stop mode configuration.
 **
 ******************************************************************************/
typedef struct stc_pwc_stop_mode_cfg
{
    en_pwc_stopdas_t        enStpDrvAbi;    ///< Driver ability while enter stop mode.
    en_pwc_stop_flash_sel_t enStopFlash;    ///< Flash mode while stop mode awake.
    en_pwc_stop_clk_sel_t   enStopClk;      ///< Clock value while stop mode awake.
    en_functional_state_t   enPll;          ///< Whether the PLL enable or disable while enter stop mode.
}stc_pwc_stop_mode_cfg_t;

/**
 *******************************************************************************
 ** \brief  The power down wake_up timer control.
 **
 ******************************************************************************/
typedef struct stc_pwc_wktm_ctl
{
    uint16_t                u16WktmCmp;     ///< The wake_up timer compare value.
    en_pwc_wkover_flag_t    enWkOverFlag;   ///< The flag of compare result.
    en_pwc_wkclk_sel_t      enWkclk;        ///< The clock of wake_up timer.
    en_functional_state_t   enWktmEn;       ///< Enable or disable wake_up timer.
}stc_pwc_wktm_ctl_t;

/**
 *******************************************************************************
 ** \brief  The pvd control.
 **
 ******************************************************************************/
typedef struct stc_pwc_pvd_ctl
{
    en_functional_state_t   enPvdIREn;      ///< Enable or disable pvd interrupt(reset).
    en_pwc_pvd_md_t         enPvdMode;      ///< The handle of pvd is interrupt or reset.
    en_functional_state_t   enPvdCmpOutEn;  ///< Enable or disable pvd output compare result .
}stc_pwc_pvd_ctl_t;

/**
 *******************************************************************************
 ** \brief  The power down wake_up event configuration.
 **
 ******************************************************************************/
typedef struct stc_pwc_pvd_cfg
{
    stc_pwc_pvd_ctl_t       stcPvd1Ctl;     ///< Pvd1 control configuration.
    stc_pwc_pvd_ctl_t       stcPvd2Ctl;     ///< Pvd2 control configuration.
    en_functional_state_t   enPvd1FilterEn; ///< Pvd1 filtering enable or disable.
    en_functional_state_t   enPvd2FilterEn; ///< Pvd2 filtering enable or disable.
    en_pwc_pvdfiltclk_sel_t enPvd1Filtclk;  ///< Pvd1 filtering sampling clock.
    en_pwc_pvdfiltclk_sel_t enPvd2Filtclk;  ///< Pvd2 filtering sampling clock.
    en_pwc_pvd1level_sel_t  enPvd1Level;    ///< Pvd1 voltage.
    en_pwc_pvd2level_sel_t  enPvd2Level;    ///< Pvd2 voltage.
    en_pwc_pvd_int_sel_t    enPvd1Int;      ///< Pvd1 interrupt.
    en_pwc_pvd_int_sel_t    enPvd2Int;      ///< Pvd2 interrupt.
}stc_pwc_pvd_cfg_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define PWC_PDWKEN0_WKUP00          ((uint8_t)0x01)
#define PWC_PDWKEN0_WKUP01          ((uint8_t)0x02)
#define PWC_PDWKEN0_WKUP02          ((uint8_t)0x04)
#define PWC_PDWKEN0_WKUP03          ((uint8_t)0x08)
#define PWC_PDWKEN0_WKUP10          ((uint8_t)0x10)
#define PWC_PDWKEN0_WKUP11          ((uint8_t)0x20)
#define PWC_PDWKEN0_WKUP12          ((uint8_t)0x40)
#define PWC_PDWKEN0_WKUP13          ((uint8_t)0x80)

#define PWC_PDWKEN1_WKUP20          ((uint8_t)0x01)
#define PWC_PDWKEN1_WKUP21          ((uint8_t)0x02)
#define PWC_PDWKEN1_WKUP22          ((uint8_t)0x04)
#define PWC_PDWKEN1_WKUP23          ((uint8_t)0x08)
#define PWC_PDWKEN1_WKUP30          ((uint8_t)0x10)
#define PWC_PDWKEN1_WKUP31          ((uint8_t)0x20)
#define PWC_PDWKEN1_WKUP32          ((uint8_t)0x40)
#define PWC_PDWKEN1_WKUP33          ((uint8_t)0x80)

#define PWC_PDWKEN2_PVD1            ((uint8_t)0x01)
#define PWC_PDWKEN2_PVD2            ((uint8_t)0x02)
#define PWC_PDWKEN2_NMI             ((uint8_t)0x04)
#define PWC_PDWKEN2_RTCPRD          ((uint8_t)0x10)
#define PWC_PDWKEN2_RTCAL           ((uint8_t)0x20)
#define PWC_PDWKEN2_WKTM            ((uint8_t)0x80)

#define PWC_PDWKUP_EDGE_WKP0        ((uint8_t)0x01)
#define PWC_PDWKUP_EDGE_WKP1        ((uint8_t)0x02)
#define PWC_PDWKUP_EDGE_WKP2        ((uint8_t)0x04)
#define PWC_PDWKUP_EDGE_WKP3        ((uint8_t)0x08)
#define PWC_PDWKUP_EDGE_PVD1        ((uint8_t)0x10)
#define PWC_PDWKUP_EDGE_PVD2        ((uint8_t)0x20)
#define PWC_PDWKUP_EDGE_NMI         ((uint8_t)0x40)

#define PWC_RAMPWRDOWN_SRAM1        ((uint32_t)0x00000001)
#define PWC_RAMPWRDOWN_SRAM2        ((uint32_t)0x00000002)
#define PWC_RAMPWRDOWN_SRAM3        ((uint32_t)0x00000004)
#define PWC_RAMPWRDOWN_SRAMH        ((uint32_t)0x00000008)
#define PWC_RAMPWRDOWN_USBFS        ((uint32_t)0x00000010)
#define PWC_RAMPWRDOWN_SDIOC0       ((uint32_t)0x00000020)
#define PWC_RAMPWRDOWN_SDIOC1       ((uint32_t)0x00000040)
#define PWC_RAMPWRDOWN_CAN          ((uint32_t)0x00000080)
#define PWC_RAMPWRDOWN_CACHE        ((uint32_t)0x00000100)
#define PWC_RAMPWRDOWN_FULL         ((uint32_t)0x000001FF)

#define PWC_STOPWKUPEN_EIRQ0        ((uint32_t)0x00000001)
#define PWC_STOPWKUPEN_EIRQ1        ((uint32_t)0x00000002)
#define PWC_STOPWKUPEN_EIRQ2        ((uint32_t)0x00000004)
#define PWC_STOPWKUPEN_EIRQ3        ((uint32_t)0x00000008)
#define PWC_STOPWKUPEN_EIRQ4        ((uint32_t)0x00000010)
#define PWC_STOPWKUPEN_EIRQ5        ((uint32_t)0x00000020)
#define PWC_STOPWKUPEN_EIRQ6        ((uint32_t)0x00000040)
#define PWC_STOPWKUPEN_EIRQ7        ((uint32_t)0x00000080)
#define PWC_STOPWKUPEN_EIRQ8        ((uint32_t)0x00000100)
#define PWC_STOPWKUPEN_EIRQ9        ((uint32_t)0x00000200)
#define PWC_STOPWKUPEN_EIRQ10       ((uint32_t)0x00000400)
#define PWC_STOPWKUPEN_EIRQ11       ((uint32_t)0x00000800)
#define PWC_STOPWKUPEN_EIRQ12       ((uint32_t)0x00001000)
#define PWC_STOPWKUPEN_EIRQ13       ((uint32_t)0x00002000)
#define PWC_STOPWKUPEN_EIRQ14       ((uint32_t)0x00004000)
#define PWC_STOPWKUPEN_EIRQ15       ((uint32_t)0x00008000)
#define PWC_STOPWKUPEN_SWDT         ((uint32_t)0x00010000)
#define PWC_STOPWKUPEN_VDU1         ((uint32_t)0x00020000)
#define PWC_STOPWKUPEN_VDU2         ((uint32_t)0x00040000)
#define PWC_STOPWKUPEN_CMPI0        ((uint32_t)0x00080000)
#define PWC_STOPWKUPEN_WKTM         ((uint32_t)0x00100000)
#define PWC_STOPWKUPEN_RTCAL        ((uint32_t)0x00200000)
#define PWC_STOPWKUPEN_RTCPRD       ((uint32_t)0x00400000)
#define PWC_STOPWKUPEN_TMR0         ((uint32_t)0x00800000)
#define PWC_STOPWKUPEN_USARTRXD     ((uint32_t)0x02000000)

#define PWC_PTWK0_WKUPFLAG          ((uint8_t)0x01)
#define PWC_PTWK1_WKUPFLAG          ((uint8_t)0x02)
#define PWC_PTWK2_WKUPFLAG          ((uint8_t)0x04)
#define PWC_PTWK3_WKUPFLAG          ((uint8_t)0x08)
#define PWC_PVD1_WKUPFLAG           ((uint8_t)0x10)
#define PWC_PVD2_WKUPFLAG           ((uint8_t)0x20)
#define PWC_NMI_WKUPFLAG            ((uint8_t)0x40)

#define PWC_RTCPRD_WKUPFALG         ((uint8_t)0x10)
#define PWC_RTCAL_WKUPFLAG          ((uint8_t)0x20)
#define PWC_WKTM_WKUPFLAG           ((uint8_t)0x80)

#define PWC_WKTMCMP_MSK             ((uint16_t)0x0FFF)

#define PWC_FCG0_PERIPH_SRAMH       ((uint32_t)0x00000001)
#define PWC_FCG0_PERIPH_SRAM12      ((uint32_t)0x00000010)
#define PWC_FCG0_PERIPH_SRAM3       ((uint32_t)0x00000100)
#define PWC_FCG0_PERIPH_SRAMRET     ((uint32_t)0x00000400)
#define PWC_FCG0_PERIPH_DMA1        ((uint32_t)0x00004000)
#define PWC_FCG0_PERIPH_DMA2        ((uint32_t)0x00008000)
#define PWC_FCG0_PERIPH_FCM         ((uint32_t)0x00010000)
#define PWC_FCG0_PERIPH_AOS         ((uint32_t)0x00020000)
#define PWC_FCG0_PERIPH_AES         ((uint32_t)0x00100000)
#define PWC_FCG0_PERIPH_HASH        ((uint32_t)0x00200000)
#define PWC_FCG0_PERIPH_TRNG        ((uint32_t)0x00400000)
#define PWC_FCG0_PERIPH_CRC         ((uint32_t)0x00800000)
#define PWC_FCG0_PERIPH_DCU1        ((uint32_t)0x01000000)
#define PWC_FCG0_PERIPH_DCU2        ((uint32_t)0x02000000)
#define PWC_FCG0_PERIPH_DCU3        ((uint32_t)0x04000000)
#define PWC_FCG0_PERIPH_DCU4        ((uint32_t)0x08000000)
#define PWC_FCG0_PERIPH_KEY         ((uint32_t)0x80000000)


#define PWC_FCG1_PERIPH_CAN         ((uint32_t)0x00000001)
#define PWC_FCG1_PERIPH_QSPI        ((uint32_t)0x00000008)
#define PWC_FCG1_PERIPH_I2C1        ((uint32_t)0x00000010)
#define PWC_FCG1_PERIPH_I2C2        ((uint32_t)0x00000020)
#define PWC_FCG1_PERIPH_I2C3        ((uint32_t)0x00000040)
#define PWC_FCG1_PERIPH_USBFS       ((uint32_t)0x00000100)
#define PWC_FCG1_PERIPH_SDIOC1      ((uint32_t)0x00000400)
#define PWC_FCG1_PERIPH_SDIOC2      ((uint32_t)0x00000800)
#define PWC_FCG1_PERIPH_I2S1        ((uint32_t)0x00001000)
#define PWC_FCG1_PERIPH_I2S2        ((uint32_t)0x00002000)
#define PWC_FCG1_PERIPH_I2S3        ((uint32_t)0x00004000)
#define PWC_FCG1_PERIPH_I2S4        ((uint32_t)0x00008000)
#define PWC_FCG1_PERIPH_SPI1        ((uint32_t)0x00010000)
#define PWC_FCG1_PERIPH_SPI2        ((uint32_t)0x00020000)
#define PWC_FCG1_PERIPH_SPI3        ((uint32_t)0x00040000)
#define PWC_FCG1_PERIPH_SPI4        ((uint32_t)0x00080000)
#define PWC_FCG1_PERIPH_USART1      ((uint32_t)0x01000000)
#define PWC_FCG1_PERIPH_USART2      ((uint32_t)0x02000000)
#define PWC_FCG1_PERIPH_USART3      ((uint32_t)0x04000000)
#define PWC_FCG1_PERIPH_USART4      ((uint32_t)0x08000000)

#define PWC_FCG2_PERIPH_TIM01       ((uint32_t)0x00000001)
#define PWC_FCG2_PERIPH_TIM02       ((uint32_t)0x00000002)
#define PWC_FCG2_PERIPH_TIMA1       ((uint32_t)0x00000004)
#define PWC_FCG2_PERIPH_TIMA2       ((uint32_t)0x00000008)
#define PWC_FCG2_PERIPH_TIMA3       ((uint32_t)0x00000010)
#define PWC_FCG2_PERIPH_TIMA4       ((uint32_t)0x00000020)
#define PWC_FCG2_PERIPH_TIMA5       ((uint32_t)0x00000040)
#define PWC_FCG2_PERIPH_TIMA6       ((uint32_t)0x00000080)
#define PWC_FCG2_PERIPH_TIM41       ((uint32_t)0x00000100)
#define PWC_FCG2_PERIPH_TIM42       ((uint32_t)0x00000200)
#define PWC_FCG2_PERIPH_TIM43       ((uint32_t)0x00000400)
#define PWC_FCG2_PERIPH_EMB         ((uint32_t)0x00008000)
#define PWC_FCG2_PERIPH_TIM61       ((uint32_t)0x00010000)
#define PWC_FCG2_PERIPH_TIM62       ((uint32_t)0x00020000)
#define PWC_FCG2_PERIPH_TIM63       ((uint32_t)0x00040000)

#define PWC_FCG3_PERIPH_ADC1        ((uint32_t)0x00000001)
#define PWC_FCG3_PERIPH_ADC2        ((uint32_t)0x00000002)
#define PWC_FCG3_PERIPH_CMP         ((uint32_t)0x00000100)
#define PWC_FCG3_PERIPH_OTS         ((uint32_t)0x00001000)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
void PWC_PowerModeCfg(const stc_pwc_pwr_mode_cfg_t* pstcPwrMdCfg);
void PWC_EnterPowerDownMd(void);

void PWC_PdWakeup0Cmd(uint32_t u32Wkup0Event, en_functional_state_t enNewState);
void PWC_PdWakeup1Cmd(uint32_t u32Wkup1Event, en_functional_state_t enNewState);
void PWC_PdWakeup2Cmd(uint32_t u32Wkup2Event, en_functional_state_t enNewState);
void PWC_PdWakeupEvtEdgeCfg(uint8_t u8WkupEvent, en_pwc_edge_sel_t enEdge);

en_flag_status_t PWC_GetWakeup0Flag(uint8_t u8WkupFlag);
en_flag_status_t PWC_GetWakeup1Flag(uint8_t u8WkupFlag);
void PWC_ClearWakeup0Flag(uint8_t u8WkupFlag);
void PWC_ClearWakeup1Flag(uint8_t u8WkupFlag);
void PWC_PwrMonitorCmd(en_functional_state_t enNewState);

void PWC_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState);
void PWC_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState);
void PWC_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState);
void PWC_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState);

en_result_t PWC_StopModeCfg(const stc_pwc_stop_mode_cfg_t*  pstcStpMdCfg);
void PWC_StopWkupCmd(uint32_t u32Wkup0Event, en_functional_state_t enNewState);

void PWC_EnterStopMd(void);
void PWC_EnterSleepMd(void);

void PWC_Xtal32CsCmd(en_functional_state_t enNewState);
void PWC_HrcPwrCmd(en_functional_state_t enNewState);
void PWC_PllPwrCmd(en_functional_state_t enNewState);
void PWC_RamPwrdownCmd(uint32_t u32RamCtlBit, en_functional_state_t enNewState);
void PWC_RamOpMdConfig(en_pwc_ram_op_md_t enRamOpMd);

void PWC_WktmControl(const stc_pwc_wktm_ctl_t* pstcWktmCtl);

void PWC_PvdCfg(const stc_pwc_pvd_cfg_t* pstcPvdCfg);
void PWC_Pvd1Cmd(en_functional_state_t enNewState);
void PWC_Pvd2Cmd(en_functional_state_t enNewState);
void PWC_ExVccCmd(en_functional_state_t enNewState);
void PWC_ClearPvdFlag(en_pwc_pvd_t enPvd);
en_flag_status_t PWC_GetPvdFlag(en_pwc_pvd_t enPvd);
en_flag_status_t PWC_GetPvdStatus(en_pwc_pvd_t enPvd);

void PWC_enNvicBackup(void);
void PWC_enNvicRecover(void);
void PWC_ClkBackup(void);
void PWC_ClkRecover(void);
void PWC_IrqClkBackup(void);
void PWC_IrqClkRecover(void);

en_result_t PWC_HS2LS(void);
en_result_t PWC_LS2HS(void);
en_result_t PWC_HS2HP(void);
en_result_t PWC_HP2HS(void);
en_result_t PWC_LS2HP(void);
en_result_t PWC_HP2LS(void);

//@} // PwcGroup

#ifdef __cplusplus
}
#endif

#endif /* DDL_PWC_ENABLE */

#endif /* __HC32F460_PWC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
