/**
 *******************************************************************************
 * @file  hc32f4a0_pwc.c
 * @brief This file provides firmware functions to manage the Power Control(PWC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-07-30       Zhangxl         Refine power mode switch function
   2020-08-25       Zhangxl         Modify for MISRAC2012-10.1
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_pwc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_PWC PWC
 * @brief Power Control Driver Library
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Local_Macros PWC Local Macros
 * @{
 */

/* Get the backup register address of PWC */
#define PWC_BKRx(num)       ((uint32_t)(&(M4_PWC->BKR0)) + ((uint32_t)(num) << 2U))

#define PWC_FCG0_MASK                                                           \
                (PWC_FCG0_DCU8   | PWC_FCG0_DCU7 | PWC_FCG0_DCU6    |           \
                PWC_FCG0_DCU5    | PWC_FCG0_DCU4 | PWC_FCG0_DCU3    |           \
                PWC_FCG0_DCU2    | PWC_FCG0_DCU1 | PWC_FCG0_CRC     |           \
                PWC_FCG0_TRNG    | PWC_FCG0_HASH | PWC_FCG0_AES     |           \
                PWC_FCG0_CORDIC  | PWC_FCG0_CTC  | PWC_FCG0_AOS     |           \
                PWC_FCG0_FCM     | PWC_FCG0_DMA2 | PWC_FCG0_DMA1    |           \
                PWC_FCG0_KEY     | PWC_FCG0_SRAMB| PWC_FCG0_SRAM4   |           \
                PWC_FCG0_SRAM3   | PWC_FCG0_SRAM2| PWC_FCG0_SRAM1   |           \
                PWC_FCG0_SRAMH)

#define PWC_FCG1_MASK                                                           \
                (PWC_FCG1_CAN1   | PWC_FCG1_CAN2 | PWC_FCG1_ETHER   |           \
                PWC_FCG1_QSPI    | PWC_FCG1_IIC1 | PWC_FCG1_IIC2    |           \
                PWC_FCG1_IIC3    | PWC_FCG1_IIC4 | PWC_FCG1_IIC5    |           \
                PWC_FCG1_IIC6    | PWC_FCG1_SDIOC1|PWC_FCG1_SDIOC2  |           \
                PWC_FCG1_I2S1    | PWC_FCG1_I2S2 | PWC_FCG1_I2S3    |           \
                PWC_FCG1_I2S4    | PWC_FCG1_SPI1 | PWC_FCG1_SPI2    |           \
                PWC_FCG1_SPI3    | PWC_FCG1_SPI4 | PWC_FCG1_SPI5    |           \
                PWC_FCG1_SPI6    | PWC_FCG1_USBFS| PWC_FCG1_USBHS   |           \
                PWC_FCG1_FMAC1   | PWC_FCG1_FMAC2| PWC_FCG1_FMAC3   |           \
                PWC_FCG1_FMAC4)
#define PWC_FCG2_MASK                                                           \
                (PWC_FCG2_TMR6_1| PWC_FCG2_TMR6_2 | PWC_FCG2_TMR6_3 |           \
                PWC_FCG2_TMR6_4 | PWC_FCG2_TMR6_5 | PWC_FCG2_TMR6_6 |           \
                PWC_FCG2_TMR6_7 | PWC_FCG2_TMR6_8 | PWC_FCG2_TMR4_1 |           \
                PWC_FCG2_TMR4_2 | PWC_FCG2_TMR4_3 | PWC_FCG2_HRPWM  |           \
                PWC_FCG2_TMR0_1 | PWC_FCG2_TMR0_2 | PWC_FCG2_EMB    |           \
                PWC_FCG2_TMR2_1 | PWC_FCG2_TMR2_2 | PWC_FCG2_TMR2_3 |           \
                PWC_FCG2_TMR2_4 | PWC_FCG2_TMRA_1 | PWC_FCG2_TMRA_2 |           \
                PWC_FCG2_TMRA_3 | PWC_FCG2_TMRA_4 | PWC_FCG2_TMRA_5 |           \
                PWC_FCG2_TMRA_6 | PWC_FCG2_TMRA_7 | PWC_FCG2_TMRA_8 |           \
                PWC_FCG2_TMRA_9 | PWC_FCG2_TMRA_10| PWC_FCG2_TMRA_11|           \
                PWC_FCG2_TMRA_12)
#define PWC_FCG3_MASK                                                           \
                (PWC_FCG3_ADC1  | PWC_FCG3_ADC2   | PWC_FCG3_ADC3   |           \
                PWC_FCG3_DAC1   | PWC_FCG3_DAC2   | PWC_FCG3_CMP1   |           \
                PWC_FCG3_CMP2   | PWC_FCG3_OTS    | PWC_FCG3_DVP    |           \
                PWC_FCG3_SMC    | PWC_FCG3_DMC    | PWC_FCG3_NFC    |           \
                PWC_FCG3_USART1 | PWC_FCG3_USART2 | PWC_FCG3_USART3 |           \
                PWC_FCG3_USART4 | PWC_FCG3_USART5 | PWC_FCG3_USART6 |           \
                PWC_FCG3_USART7 | PWC_FCG3_USART8 | PWC_FCG3_USART9 |           \
                PWC_FCG3_USART10| PWC_FCG3_CMBIAS)

#define PWC_RAM_MASK                                                            \
                (PWC_RAMPC0_RAMPDC0 | PWC_RAMPC0_RAMPDC1 | PWC_RAMPC0_RAMPDC2 | \
                PWC_RAMPC0_RAMPDC3  | PWC_RAMPC0_RAMPDC4 | PWC_RAMPC0_RAMPDC5 | \
                PWC_RAMPC0_RAMPDC6  | PWC_RAMPC0_RAMPDC7 | PWC_RAMPC0_RAMPDC8 | \
                PWC_RAMPC0_RAMPDC9  | PWC_RAMPC0_RAMPDC10)

#define PWC_PRAM_MASK                                                           \
                (PWC_PRAMLPC_PRAMPDC0   | PWC_PRAMLPC_PRAMPDC1 |                \
                PWC_PRAMLPC_PRAMPDC2    | PWC_PRAMLPC_PRAMPDC3 |                \
                PWC_PRAMLPC_PRAMPDC4    | PWC_PRAMLPC_PRAMPDC5 |                \
                PWC_PRAMLPC_PRAMPDC6    | PWC_PRAMLPC_PRAMPDC7 |                \
                PWC_PRAMLPC_PRAMPDC8    | PWC_PRAMLPC_PRAMPDC9)

#define PWC_PVD_FLAG_MASK                                                       \
                (PWC_PVDDSR_PVD1MON     | PWC_PVDDSR_PVD1DETFLG|                \
                PWC_PVDDSR_PVD2MON      | PWC_PVDDSR_PVD2DETFLG)

#define PWC_PDWK0_MASK                                                          \
                (PWC_PDWKE0_WKE0_0  | PWC_PDWKE0_WKE0_1     |                   \
                PWC_PDWKE0_WKE0_2   | PWC_PDWKE0_WKE0_3     |                   \
                PWC_PDWKE0_WKE1_0   | PWC_PDWKE0_WKE1_1     |                   \
                PWC_PDWKE0_WKE1_2   | PWC_PDWKE0_WKE1_3)

#define PWC_PDWK1_MASK                                                          \
                (PWC_PDWKE1_WKE2_0  | PWC_PDWKE1_WKE2_1     |                   \
                PWC_PDWKE1_WKE2_2   | PWC_PDWKE1_WKE2_3     |                   \
                PWC_PDWKE1_WKE3_0   | PWC_PDWKE1_WKE3_1     |                   \
                PWC_PDWKE1_WKE3_2   | PWC_PDWKE1_WKE3_3)

#define PWC_PDWK2_MASK                                                          \
                (PWC_PDWKE2_VD1WKE  | PWC_PDWKE2_VD2WKE     |                   \
                PWC_PDWKE2_RTCPRDWKE| PWC_PDWKE2_RTCALMWKE  |                   \
                PWC_PDWKE2_WKTMWKE  | PWC_PDWKE2_XTAL32ERWKE)

#define PWC_PDWK_FLG0_MASK                                                      \
                (PWC_PDWKF0_PTWK0F  | PWC_PDWKF0_PTWK1F     |                   \
                PWC_PDWKF0_PTWK2F   | PWC_PDWKF0_PTWK3F     |                   \
                PWC_PDWKF0_VD1WKF   | PWC_PDWKF0_VD2WKF)

#define PWC_PDWK_FLG1_MASK                                                      \
                (PWC_PDWKF1_RTCPRDWKF   | PWC_PDWKF1_RTCALMWKF  |               \
                PWC_PDWKF1_XTAL32ERWKF  | PWC_PDWKF1_WKTMWKF)

/**
 * @defgroup PWC_Check_Parameters_Validity PWC Check Parameters Validity
 * @{
 */
/*  Check PWC register lock status. */
#define IS_PWC_UNLOCKED()       ((M4_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/*  Check PWC PVD register lock status. */
#define IS_PVD_UNLOCKED()       ((M4_PWC->FPRC & PWC_FPRC_FPRCB3) == PWC_FPRC_FPRCB3)

#define IS_PWC_FCG0_UNLOCKED()  ((M4_PWC->FCG0PC & PWC_FCG0PC_PRT0) == PWC_FCG0PC_PRT0)

/*! Parameter validity check for peripheral in fcg0. */
#define IS_PWC_FCG0_PERIPH(per)                                                 \
(   ((per) != 0x00UL)                           &&                              \
    (((per) | PWC_FCG0_MASK) == PWC_FCG0_MASK))

/*! Parameter validity check for peripheral in fcg1. */
#define IS_PWC_FCG1_PERIPH(per)                                                 \
(   ((per) != 0x00UL)                           &&                              \
    (((per) | PWC_FCG1_MASK) == PWC_FCG1_MASK))

/*! Parameter validity check for peripheral in fcg2. */
#define IS_PWC_FCG2_PERIPH(per)                                                 \
(   ((per) != 0x00UL)                           &&                              \
    (((per) | PWC_FCG2_MASK) == PWC_FCG2_MASK))

/*! Parameter validity check for peripheral in fcg3. */
#define IS_PWC_FCG3_PERIPH(per)                                                 \
(   ((per) != 0x00UL)                           &&                              \
    (((per) | PWC_FCG3_MASK) == PWC_FCG3_MASK))

/*! Parameter validity check for internal RAM setting of power mode control */
#define IS_PWC_RAM_CONTROL(ram)                                                 \
(   ((ram) != 0x00UL)                           &&                              \
    (((ram) | PWC_RAM_MASK) == PWC_RAM_MASK))

/*! Parameter validity check for peripheral RAM setting of power mode control */
#define IS_PWC_PRAM_CONTROL(pram)                                               \
(   ((pram) != 0x00UL)                          &&                              \
    (((pram) | PWC_PRAM_MASK) == PWC_PRAM_MASK))

/*! Parameter validity check for RAM setting of MCU operating mode */
#define IS_PWC_RAM_MODE(mode)                                                   \
(   ((mode) == PWC_RAM_HIGH)                    ||                              \
    ((mode) == PWC_RAM_LOW))

/*! Parameter validity check for PVD channel. */
#define IS_PWC_PVD_CH(ch)                                                       \
(   ((ch) == PWC_PVD_CH1)                       ||                              \
    ((ch) == PWC_PVD_CH2))

/*! Parameter validity check for PVD2 ext. input function setting. */
#define IS_PWC_PVD2_EXINP(func)                                                 \
(   ((func) == PWC_PVD2_EXINP_ON)               ||                              \
    ((func) == PWC_PVD2_EXINP_OFF))

/*! Parameter validity check for PVD function setting. */
#define IS_PWC_PVD_EN(func)                                                     \
(   ((func) == PWC_PVD_ON)                      ||                              \
    ((func) == PWC_PVD_OFF))

/*! Parameter validity check for PVD interrupt or reset function setting. */
#define IS_PWC_PVD_IR_EN(func)                                                  \
(   ((func) == PWC_PVD_IR_ON)                   ||                              \
    ((func) == PWC_PVD_IR_OFF))

/*! Parameter validity check for PVD interrupt or reset selection. */
#define IS_PWC_PVD_IR_SEL(sel)                                                  \
(   ((sel) == PWC_PVD_RST)                      ||                              \
    ((sel) == PWC_PVD_INT))

/*! Parameter validity check for PVD compare output setting. */
#define IS_PWC_PVD_CMP_EN(out)                                                  \
(   ((out) == PWC_PVD_CMP_ON)                   ||                              \
    ((out) == PWC_PVD_CMP_OFF))

/*! Parameter validity check for PVD digital noise filter function setting. */
#define IS_PWC_PVD_DFS_EN(func)                                                 \
(   ((func) == PWC_PVD_DF_ON)                   ||                              \
    ((func) == PWC_PVD_DF_OFF))

/*! Parameter validity check for PVD digital noise filter clock setting. */
#define IS_PWC_PVD_DFS_CLK(clk)                                                 \
(   ((clk) == PWC_PVD_DFS_DIV1)                 ||                              \
    ((clk) == PWC_PVD_DFS_DIV2)                 ||                              \
    ((clk) == PWC_PVD_DFS_DIV4)                 ||                              \
    ((clk) == PWC_PVD_DFS_MUL2))

/*! Parameter validity check for PVD detect voltage setting. */
#define IS_PWC_PVD_VOLTAGE(vol)                                                 \
(   ((vol) == PWC_PVD1_2V0_PVD2_2V1)            ||                              \
    ((vol) == PWC_PVD1_2V1_PVD2_2V3)            ||                              \
    ((vol) == PWC_PVD1_2V3_PVD2_2V5)            ||                              \
    ((vol) == PWC_PVD1_2V5_PVD2_2V6)            ||                              \
    ((vol) == PWC_PVD1_2V6_PVD2_2V7)            ||                              \
    ((vol) == PWC_PVD1_2V7_PVD2_2V8)            ||                              \
    ((vol) == PWC_PVD1_2V8_PVD2_2V9)            ||                              \
    ((vol) == PWC_PVD1_2V9_PVD2_1V1))

/*! Parameter validity check for PVD NMI function setting. */
#define IS_PWC_PVD_NMI(func)                                                    \
(   ((func) == PWC_PVD_INT_MASK)                ||                              \
    ((func) == PWC_PVD_INT_NONMASK))

/*! Parameter validity check for PVD trigger setting. */
#define IS_PWC_PVD_TRIG(trig)                                                   \
(   ((trig) == PWC_PVD_TRIGGER_FALLING)         ||                              \
    ((trig) == PWC_PVD_TRIGGER_RISING)          ||                              \
    ((trig) == PWC_PVD_TRIGGER_BOTH))

/*! Parameter validity check for PVD flag. */
#define IS_PWC_PVD_GET_FLAG(flag)                                               \
(   ((flag) != 0x00U)                           &&                              \
    (((flag) | PWC_PVD_FLAG_MASK) == PWC_PVD_FLAG_MASK))

/*! Parameter validity check for wakeup0 event. */
#define IS_PWC_WAKEUP0_EVENT(evt)                                               \
(   ((evt) != 0x00U)                            &&                              \
    (((evt) | PWC_PDWK0_MASK) == PWC_PDWK0_MASK))

/*! Parameter validity check for wakeup1 event. */
#define IS_PWC_WAKEUP1_EVENT(evt)                                               \
(   ((evt) != 0x00U)                            &&                              \
    (((evt) | PWC_PDWK1_MASK) == PWC_PDWK1_MASK))

/*! Parameter validity check for wakeup2 event. */
#define IS_PWC_WAKEUP2_EVENT(evt)                                               \
(   ((evt) != 0x00U)                            &&                              \
    (((evt) | PWC_PDWK2_MASK) == PWC_PDWK2_MASK))

/*! Parameter validity check for wakeup0 flag. */
#define IS_PWC_WAKEUP0_FLAG(flag)                                               \
(   ((flag) != 0x00U)                           &&                              \
    (((flag) | PWC_PDWK_FLG0_MASK) == PWC_PDWK_FLG0_MASK))

/*! Parameter validity check for wakeup1 flag. */
#define IS_PWC_WAKEUP1_FLAG(flag)                                               \
(   ((flag) != 0x00U)                           &&                              \
    (((flag) | PWC_PDWK_FLG1_MASK) == PWC_PDWK_FLG1_MASK))

/*! Parameter validity check for power down mode wakeup event with trigger. */
#define IS_PWC_WAKEUP_TRIG_EVENT(evt)                                           \
(   ((evt) != 0x00U)                            &&                              \
    (((evt) | PWC_PD_WKUP_TRIG_MASK) == PWC_PD_WKUP_TRIG_MASK))

/*! Parameter validity check for power down mode wakeup trigger edge. */
#define IS_PWC_WAKEUP_TRIG(edge)                                                \
(   ((edge) == PWC_PD_WKUP_FALLING)             ||                              \
    ((edge) == PWC_PD_WKUP_RISING))

/*! Parameter validity check for wake up flag. */
#define IS_PWC_WKUP0_FLAG(flag)                                                 \
(   ((flag) != 0x00U)                           &&                              \
    (((flag) | PWC_PDWK_FLG0_MASK) == PWC_PDWK_FLG0_MASK))

/*! Parameter validity check for wake up flag. */
#define IS_PWC_WKUP1_FLAG(flag)                                                 \
(   ((flag) != 0x00U)                           &&                              \
    (((flag) | PWC_PDWK_FLG1_MASK) == PWC_PDWK_FLG1_MASK))

/*! Parameter validity check for stop mode drive capacity. */
#define IS_PWC_STOP_DRV(drv)                                                    \
(   ((drv) == PWC_STOP_DRV_HIGH)                ||                              \
    ((drv) == PWC_STOP_DRV_LOW))

/*! Parameter validity check for clock setting after wake-up from stop mode. */
#define IS_PWC_STOP_CLK(clk)                                                    \
(   ((clk) == PWC_STOP_CLK_KEEP)                ||                              \
    ((clk) == PWC_STOP_CLK_MRC))

/*! Parameter validity check for flash wait setting after wake-up from stop mode. */
#define IS_PWC_STOP_FLASH_WAIT(wait)                                            \
(   ((wait) == PWC_STOP_FLASH_WAIT)             ||                              \
    ((wait) == PWC_STOP_FLASH_NOWAIT))

/*! Parameter validity check for ex-bus setting in stop mode. */
#define IS_PWC_STOP_EXBUS(bus)                                                  \
(   ((bus) == PWC_STOP_EXBUS_HIZ)               ||                              \
    ((bus) == PWC_STOP_EXBUS_HOLD))

/*! Parameter validity check for VBAT Reference Voltage. */
#define IS_PWC_VBAT_REF_VOL(vol)                                                \
(   ((vol) == PWC_VBAT_REF_VOL_2P0V)            ||                              \
    ((vol) == PWC_VBAT_REF_VOL_1P8V))

/*! Parameter validity check for BACKUP RAM Flag. */
#define IS_PWC_BACKUP_RAM_FLAG(flag)                                            \
(   0U != ((flag) & (PWC_BACKUP_RAM_FLAG_RAMPDF | PWC_BACKUP_RAM_FLAG_RAMVALID)))

/*! Parameter validity check for Backup Register Number. */
#define IS_PWC_BACKUP_REGISTER_NUMBER(num)      ((num) <= 127U)

/*! Parameter validity check for WKT Clock Source. */
#define IS_PWC_WKT_CLK_SRC(src)                                                 \
(   ((src) == PWC_WKT_CLK_SRC_64HZ)             ||                              \
    ((src) == PWC_WKT_CLK_SRC_XTAL32)           ||                              \
    ((src) == PWC_WKT_CLK_SRC_RTCLRC))

/*! Parameter validity check for WKT Comparision Value. */
#define IS_PWC_WKT_COMPARISION_VALUE(val)       ((val) <= 0x0FFFU)

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Functions PWC Global Functions
 * @{
 */
/**
 * @brief  Enter power down mode.
 * @param  None
 * @retval None
 */
void PWC_EnterPowerDownMode(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->STPMCR_b.STOP, 1U);
    WRITE_REG32(bM4_PWC->PWRC0_b.PWDN, 1U);

    __WFI();
}

/**
 * @brief  Enter stop mode.
 * @param  None
 * @retval None
 */
void PWC_EnterStopMode(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->STPMCR_b.STOP, 1U);

    __WFI();
}

/**
 * @brief  Enter sleep mode.
 * @param  None
 * @retval None
 */
void PWC_EnterSleepMode(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->STPMCR_b.STOP, 0U);

     __WFI();
}

/**
 * @brief  Enable or disable the FCG0 peripheral clock.
 * @param [in] u32Fcg0Periph The peripheral in FCG0.
 *   @arg PWC_FCG0_SRAMH
 *   @arg PWC_FCG0_SRAM1
 *   @arg PWC_FCG0_SRAM2
 *   @arg PWC_FCG0_SRAM3
 *   @arg PWC_FCG0_SRAM4
 *   @arg PWC_FCG0_SRAMB
 *   @arg PWC_FCG0_KEY
 *   @arg PWC_FCG0_DMA1
 *   @arg PWC_FCG0_DMA2
 *   @arg PWC_FCG0_FCM
 *   @arg PWC_FCG0_AOS
 *   @arg PWC_FCG0_CTC
 *   @arg PWC_FCG0_CORDIC
 *   @arg PWC_FCG0_AES
 *   @arg PWC_FCG0_HASH
 *   @arg PWC_FCG0_TRNG
 *   @arg PWC_FCG0_CRC
 *   @arg PWC_FCG0_DCU1
 *   @arg PWC_FCG0_DCU2
 *   @arg PWC_FCG0_DCU3
 *   @arg PWC_FCG0_DCU4
 *   @arg PWC_FCG0_DCU5
 *   @arg PWC_FCG0_DCU6
 *   @arg PWC_FCG0_DCU7
 *   @arg PWC_FCG0_DCU8
 * @param [in] enNewState The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG0_PERIPH(u32Fcg0Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_FCG0_UNLOCKED());

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG0, u32Fcg0Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG0, u32Fcg0Periph);
    }
}

/**
 * @brief  Enable or disable the FCG1 peripheral clock.
 * @param [in] u32Fcg1Periph The peripheral in FCG1.
 *   @arg PWC_FCG1_CAN1
 *   @arg PWC_FCG1_CAN2
 *   @arg PWC_FCG1_ETHER
 *   @arg PWC_FCG1_QSPI
 *   @arg PWC_FCG1_IIC1
 *   @arg PWC_FCG1_IIC2
 *   @arg PWC_FCG1_IIC3
 *   @arg PWC_FCG1_IIC4
 *   @arg PWC_FCG1_IIC5
 *   @arg PWC_FCG1_IIC6
 *   @arg PWC_FCG1_SDIOC1
 *   @arg PWC_FCG1_SDIOC2
 *   @arg PWC_FCG1_I2S1
 *   @arg PWC_FCG1_I2S2
 *   @arg PWC_FCG1_I2S3
 *   @arg PWC_FCG1_I2S4
 *   @arg PWC_FCG1_SPI1
 *   @arg PWC_FCG1_SPI2
 *   @arg PWC_FCG1_SPI3
 *   @arg PWC_FCG1_SPI4
 *   @arg PWC_FCG1_SPI5
 *   @arg PWC_FCG1_SPI6
 *   @arg PWC_FCG1_USBFS
 *   @arg PWC_FCG1_USBHS
 *   @arg PWC_FCG1_FMAC1
 *   @arg PWC_FCG1_FMAC2
 *   @arg PWC_FCG1_FMAC3
 *   @arg PWC_FCG1_FMAC4
 * @param [in] enNewState The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG1_PERIPH(u32Fcg1Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG1, u32Fcg1Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG1, u32Fcg1Periph);
    }
}

/**
 * @brief  Enable or disable the FCG2 peripheral clock.
 * @param [in] u32Fcg2Periph The peripheral in FCG2.
 *   @arg PWC_FCG2_TMR6_1
 *   @arg PWC_FCG2_TMR6_2
 *   @arg PWC_FCG2_TMR6_3
 *   @arg PWC_FCG2_TMR6_4
 *   @arg PWC_FCG2_TMR6_5
 *   @arg PWC_FCG2_TMR6_6
 *   @arg PWC_FCG2_TMR6_7
 *   @arg PWC_FCG2_TMR6_8
 *   @arg PWC_FCG2_TMR4_1
 *   @arg PWC_FCG2_TMR4_2
 *   @arg PWC_FCG2_TMR4_3
 *   @arg PWC_FCG2_HRPWM
 *   @arg PWC_FCG2_TMR0_1
 *   @arg PWC_FCG2_TMR0_2
 *   @arg PWC_FCG2_EMB
 *   @arg PWC_FCG2_TMR2_1
 *   @arg PWC_FCG2_TMR2_2
 *   @arg PWC_FCG2_TMR2_3
 *   @arg PWC_FCG2_TMR2_4
 *   @arg PWC_FCG2_TMRA_1
 *   @arg PWC_FCG2_TMRA_2
 *   @arg PWC_FCG2_TMRA_3
 *   @arg PWC_FCG2_TMRA_4
 *   @arg PWC_FCG2_TMRA_5
 *   @arg PWC_FCG2_TMRA_6
 *   @arg PWC_FCG2_TMRA_7
 *   @arg PWC_FCG2_TMRA_8
 *   @arg PWC_FCG2_TMRA_9
 *   @arg PWC_FCG2_TMRA_10
 *   @arg PWC_FCG2_TMRA_11
 *   @arg PWC_FCG2_TMRA_12
 * @param [in] enNewState The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG2_PERIPH(u32Fcg2Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG2, u32Fcg2Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG2, u32Fcg2Periph);
    }
}

/**
 * @brief  Enable or disable the FCG3 peripheral clock.
 * @param [in] u32Fcg3Periph The peripheral in FCG3.
 *   @arg PWC_FCG3_ADC1
 *   @arg PWC_FCG3_ADC2
 *   @arg PWC_FCG3_ADC3
 *   @arg PWC_FCG3_CMBIAS
 *   @arg PWC_FCG3_DAC1
 *   @arg PWC_FCG3_DAC2
 *   @arg PWC_FCG3_CMP1
 *   @arg PWC_FCG3_CMP2
 *   @arg PWC_FCG3_OTS
 *   @arg PWC_FCG3_DVP
 *   @arg PWC_FCG3_SMC
 *   @arg PWC_FCG3_DMC
 *   @arg PWC_FCG3_NFC
 *   @arg PWC_FCG3_USART1
 *   @arg PWC_FCG3_USART2
 *   @arg PWC_FCG3_USART3
 *   @arg PWC_FCG3_USART4
 *   @arg PWC_FCG3_USART5
 *   @arg PWC_FCG3_USART6
 *   @arg PWC_FCG3_USART7
 *   @arg PWC_FCG3_USART8
 *   @arg PWC_FCG3_USART9
 *   @arg PWC_FCG3_USART10
 * @param [in] enNewState The new state of the clock output.
 *   @arg Enable
 *   @arg Disable
 * @retval None
 */
void PWC_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG3_PERIPH(u32Fcg3Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        CLEAR_REG32_BIT(M4_PWC->FCG3, u32Fcg3Periph);
    }
    else
    {
        SET_REG32_BIT(M4_PWC->FCG3, u32Fcg3Periph);
    }
}

/**
 * @brief RAM configuration for MCU operating mode and power down control.
 * @param [in] pstcRamConfig Pointer to a stc_pwc_ram_config_t structure that
 *                            contains configuration information.
 *   @arg u32RamCtrl Internal RAM setting for power mode.
 *        PWC_RAMPC0_RAMPDC0:       0x20000000 ~ 0x2000FFFF
 *        PWC_RAMPC0_RAMPDC1:       0x20010000 ~ 0x2001FFFF
 *        PWC_RAMPC0_RAMPDC2:       0x20020000 ~ 0x2002FFFF
 *        PWC_RAMPC0_RAMPDC3:       0x20030000 ~ 0x2003FFFF
 *        PWC_RAMPC0_RAMPDC4:       0x20040000 ~ 0x2004FFFF
 *        PWC_RAMPC0_RAMPDC5:       0x20050000 ~ 0x20057FFF
 *        PWC_RAMPC0_RAMPDC6:       0x20058000 ~ 0x2005FFFF
 *        PWC_RAMPC0_RAMPDC7:       0x1FFE0000 ~ 0x1FFE7FFF
 *        PWC_RAMPC0_RAMPDC8:       0x1FFE8000 ~ 0x1FFEFFFF
 *        PWC_RAMPC0_RAMPDC9:       0x1FFF0000 ~ 0x1FFF7FFF
 *        PWC_RAMPC0_RAMPDC10:      0x1FFF8000 ~ 0x1FFFFFFF
 *   @arg u32PRamCtrl Peripheral RAM setting for power mode.
 *        PWC_PRAMLPC_PRAMPDC0:     CAN1 RAM
 *        PWC_PRAMLPC_PRAMPDC1:     CAN2 RAM
 *        PWC_PRAMLPC_PRAMPDC2:     CACHE RAM
 *        PWC_PRAMLPC_PRAMPDC3:     USBFS RAM
 *        PWC_PRAMLPC_PRAMPDC4:     USBHS RAM
 *        PWC_PRAMLPC_PRAMPDC5:     Ethernet Tx RAM
 *        PWC_PRAMLPC_PRAMPDC6:     Ethernet Rx RAM
 *        PWC_PRAMLPC_PRAMPDC7:     SDIO1 RAM
 *        PWC_PRAMLPC_PRAMPDC8:     SDIO2 RAM
 *        PWC_PRAMLPC_PRAMPDC9:     NFC RAM
 *   @arg u16RamMode RAM setting for Operating mode.
 *        PWC_RAM_HIGH              MCU operating under high frequency (lower than 240MHz)
 *        PWC_RAM_LOW               MCU operating under low frequency (lower than 8MHz)
 * @retval Ok: RAM config successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_RamConfig(const stc_pwc_ram_config_t *pstcRamConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcRamConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PWC_RAM_CONTROL(pstcRamConfig->u32RamCtrl));
        DDL_ASSERT(IS_PWC_PRAM_CONTROL(pstcRamConfig->u32PRamCtrl));
        DDL_ASSERT(IS_PWC_RAM_MODE(pstcRamConfig->u16RamMode));
        DDL_ASSERT(IS_PWC_UNLOCKED());

        WRITE_REG32(M4_PWC->RAMPC0, pstcRamConfig->u32RamCtrl);
        WRITE_REG32(M4_PWC->PRAMLPC, pstcRamConfig->u32PRamCtrl);
        WRITE_REG16(M4_PWC->RAMOPM, pstcRamConfig->u16RamMode);
    }
    return enRet;
}

/**
 * @brief  Initialize PVD config structure. Fill each pstcPvdConfig with default value
 * @param  [in] pstcPvdConfig Pointer to a stc_pwc_pvd_config_t structure that
 *                            contains configuration information.
 * @retval Ok: PVD structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_PVD_StructInit(stc_pwc_pvd_config_t *pstcPvdConfig)
{
    en_result_t enRet = Ok;
    /* Check if pointer is NULL */
    if (NULL == pstcPvdConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset PVD init structure parameters values */
        pstcPvdConfig->u8PvdEn          = PWC_PVD_OFF;
        pstcPvdConfig->u8Pvd2ExtInEn    = PWC_PVD2_EXINP_OFF;
        pstcPvdConfig->u8PvdCmpOutEn    = PWC_PVD_CMP_OFF;
        pstcPvdConfig->u8PvdIntRstSel   = PWC_PVD_INT;
        pstcPvdConfig->u8PvdIntRstEn    = PWC_PVD_IR_OFF;
        pstcPvdConfig->u8FilterEn       = PWC_PVD_DF_ON;
        pstcPvdConfig->u8FilterClk      = PWC_PVD_DFS_DIV4;
        pstcPvdConfig->u8PvdVoltage     = PWC_PVD1_2V0_PVD2_2V1;
        pstcPvdConfig->u8PvdNmiEn       = PWC_PVD_INT_NONMASK;
        pstcPvdConfig->u8PvdTrigger     = PWC_PVD_TRIGGER_FALLING;
    }
    return enRet;
}

/**
 * @brief PVD configuration.
 * @param [in] u8Ch PVD channel
 *   @arg  PWC_PVD_CH1
 *   @arg  PWC_PVD_CH2
 * @param [in] pstcPvdConfig Pointer to a stc_pwc_pvd_config_t structure that
 *                            contains configuration information.
 * @retval Ok: PVD initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_PVD_Init(uint8_t u8Ch, const stc_pwc_pvd_config_t *pstcPvdConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPvdConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PVD_UNLOCKED());
        DDL_ASSERT(IS_PWC_PVD_CH(u8Ch));
        DDL_ASSERT(IS_PWC_PVD2_EXINP(pstcPvdConfig->u8Pvd2ExtInEn));
        DDL_ASSERT(IS_PWC_PVD_EN(pstcPvdConfig->u8PvdEn));
        DDL_ASSERT(IS_PWC_PVD_IR_EN(pstcPvdConfig->u8PvdIntRstEn));
        DDL_ASSERT(IS_PWC_PVD_IR_SEL(pstcPvdConfig->u8PvdIntRstSel));
        DDL_ASSERT(IS_PWC_PVD_CMP_EN(pstcPvdConfig->u8PvdCmpOutEn));
        DDL_ASSERT(IS_PWC_PVD_DFS_EN(pstcPvdConfig->u8FilterEn));
        DDL_ASSERT(IS_PWC_PVD_DFS_CLK(pstcPvdConfig->u8FilterClk));
        DDL_ASSERT(IS_PWC_PVD_VOLTAGE(pstcPvdConfig->u8PvdVoltage));
        DDL_ASSERT(IS_PWC_PVD_NMI(pstcPvdConfig->u8PvdNmiEn));
        DDL_ASSERT(IS_PWC_PVD_TRIG(pstcPvdConfig->u8PvdTrigger));

        if (PWC_PVD_CH1 == u8Ch)
        {
            WRITE_REG32(bM4_PWC->PVDCR0_b.PVD1EN,  pstcPvdConfig->u8PvdEn);
        }
        else
        {
            WRITE_REG32(bM4_PWC->PVDCR0_b.PVD2EN,  pstcPvdConfig->u8PvdEn);
            WRITE_REG32(bM4_PWC->PVDCR0_b.EXVCCINEN, pstcPvdConfig->u8Pvd2ExtInEn);

        }
        /* config PVDCMPOE before PVDIRE */
        MODIFY_REG8(M4_PWC->PVDCR1,                                                         \
                    (PWC_PVDCR1_PVD1CMPOE << (uint8_t)(u8Ch * 4U)),                         \
                    (pstcPvdConfig->u8PvdCmpOutEn) << (uint8_t)(u8Ch * 4U));

        MODIFY_REG8(M4_PWC->PVDCR1,                                                         \
                    (PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS) << (uint8_t)(u8Ch * 4U),      \
                    (pstcPvdConfig->u8PvdIntRstSel | pstcPvdConfig->u8PvdIntRstEn) << (uint8_t)(u8Ch * 4U));
        if (PWC_PVD_DF_ON == pstcPvdConfig->u8FilterEn)
        {
            /* disable filter function in advance */
            SET_REG8_BIT(M4_PWC->PVDFCR, PWC_PVDFCR_PVD1NFDIS << (uint8_t)(u8Ch * 4U));
        }
        MODIFY_REG8(M4_PWC->PVDFCR,                                                         \
                    (PWC_PVDFCR_PVD1NFDIS | PWC_PVDFCR_PVD1NFCKS) << (uint8_t)(u8Ch * 4U),  \
                    (pstcPvdConfig->u8FilterEn | pstcPvdConfig->u8FilterClk) << (uint8_t)(u8Ch * 4U));

        MODIFY_REG8(M4_PWC->PVDLCR, (PWC_PVDLCR_PVD1LVL << (uint8_t)(u8Ch * 4U)),           \
                    (pstcPvdConfig->u8PvdVoltage) << (uint8_t)(u8Ch * 4U));

        MODIFY_REG8(M4_PWC->PVDICR,                                                         \
                    (PWC_PVDICR_PVD1NMIS | PWC_PVDICR_PVD1EDGS) << (uint8_t)(u8Ch * 4U),    \
                    (pstcPvdConfig->u8PvdNmiEn | pstcPvdConfig->u8PvdTrigger) << (uint8_t)(u8Ch * 4U));
    }
    return enRet;
}

/**
 * @brief  Get PVD flag.
 * @param  [in] u8Flag PVD flag to be get
 *   @arg    PWC_PVDDSR_PVD1DETFLG: VCC across VPVD1
 *   @arg    PWC_PVDDSR_PVD2DETFLG: VCC across VPVD2
 *   @arg    PWC_PVDDSR_PVD1MON: VCC > VPVD1
 *   @arg    PWC_PVDDSR_PVD2MON: VCC > VPVD2
 * @retval An en_flag_status_t enumeration value
 *   @arg    Set
 *   @arg    Reset
 * @note   PVDxDETFLG is avaliable when PVDCR0.PVDxEN and PVDCR1.PVDxCMPOE are set to '1'
 */
en_flag_status_t PWC_PVD_GetStatus(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_PVD_GET_FLAG(u8Flag));
    return READ_REG8_BIT(M4_PWC->PVDDSR, u8Flag) ? Set:Reset;
}

/**
 * @brief  Clear PVD1 & PVD2 flag.
 * @param  None
 * @retval None
 */
void PWC_PVD_ClearStatus(void)
{
    DDL_ASSERT(IS_PVD_UNLOCKED());
    WRITE_REG32(bM4_PWC->PVDDSR_b.PVD1DETFLG, 0UL);
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u8Wkup0Evt Wakeup pin group 0 and 1.
 *  @arg    PWC_PDWKE0_WKE0_0
 *  @arg    PWC_PDWKE0_WKE0_1
 *  @arg    PWC_PDWKE0_WKE0_2
 *  @arg    PWC_PDWKE0_WKE0_3
 *  @arg    PWC_PDWKE0_WKE1_0
 *  @arg    PWC_PDWKE0_WKE1_1
 *  @arg    PWC_PDWKE0_WKE1_2
 *  @arg    PWC_PDWKE0_WKE1_3
 * @param  [in] enNewState The new state of the wakeup event.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PdWakeup0Cmd(uint8_t u8Wkup0Evt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WAKEUP0_EVENT(u8Wkup0Evt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if(Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PDWKE0, u8Wkup0Evt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKE0, u8Wkup0Evt);
    }
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u8Wkup1Evt Wakeup pin group 0 and 1.
 *  @arg    PWC_PDWKE1_WKE2_0
 *  @arg    PWC_PDWKE1_WKE2_1
 *  @arg    PWC_PDWKE1_WKE2_2
 *  @arg    PWC_PDWKE1_WKE2_3
 *  @arg    PWC_PDWKE1_WKE3_0
 *  @arg    PWC_PDWKE1_WKE3_1
 *  @arg    PWC_PDWKE1_WKE3_2
 *  @arg    PWC_PDWKE1_WKE3_3
 * @param  [in] enNewState The new state of the wakeup event.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PdWakeup1Cmd(uint8_t u8Wkup1Evt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WAKEUP1_EVENT(u8Wkup1Evt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if(Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PDWKE1, u8Wkup1Evt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKE1, u8Wkup1Evt);
    }
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u8Wkup2Evt PVD, RTC, XTAL32 and wakeup timer.
 *  @arg    PWC_PDWKE2_VD1WKE
 *  @arg    PWC_PDWKE2_VD2WKE
 *  @arg    PWC_PDWKE2_RTCPRDWKE
 *  @arg    PWC_PDWKE2_RTCALMWKE
 *  @arg    PWC_PDWKE2_XTAL32ERWKE
 *  @arg    PWC_PDWKE2_WKTMWKE
 * @param  [in] enNewState The new state of the wakeup event.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PdWakeup2Cmd(uint8_t u8Wkup2Evt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WAKEUP2_EVENT(u8Wkup2Evt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if(Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PDWKE2, u8Wkup2Evt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKE2, u8Wkup2Evt);
    }
}

/**
 * @brief  Power down mode wake up event trigger config.
 * @param  [in] u8WkupEvt PVD and wakeup pin.
 *  @arg    PWC_PD_WKUP_PVD1
 *  @arg    PWC_PD_WKUP_PVD2
 *  @arg    PWC_PD_WKUP_WKP0
 *  @arg    PWC_PD_WKUP_WKP1
 *  @arg    PWC_PD_WKUP_WKP2
 *  @arg    PWC_PD_WKUP_WKP3
 * @param  [in] u8TrigEdge The trigger edge.
 *  @arg PWC_PD_WKUP_FALLING
 *  @arg PWC_PD_WKUP_RISING
 * @retval None
 */
void PWC_PdWakeupTrigConfig(uint8_t u8WkupEvt, uint8_t u8TrigEdge)
{
    DDL_ASSERT(IS_PWC_WAKEUP_TRIG_EVENT(u8WkupEvt));
    DDL_ASSERT(IS_PWC_WAKEUP_TRIG(u8TrigEdge));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (PWC_PD_WKUP_RISING == u8TrigEdge)
    {
        SET_REG8_BIT(M4_PWC->PDWKES, u8WkupEvt);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PDWKES, u8WkupEvt);
    }
}

/**
 * @brief  Get wake up event flag.
 * @param  [in] u8Flag Wake up event.
 *  @arg    PWC_PDWKF0_PTWK0F
 *  @arg    PWC_PDWKF0_PTWK1F
 *  @arg    PWC_PDWKF0_PTWK2F
 *  @arg    PWC_PDWKF0_PTWK3F
 *  @arg    PWC_PDWKF0_VD1WKF
 *  @arg    PWC_PDWKF0_VD2WKF
 * @retval en_flag_status_t
 */
en_flag_status_t PWC_GetWakeup0Status(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_WKUP0_FLAG(u8Flag));

    return (READ_REG8_BIT(M4_PWC->PDWKF0, u8Flag) ? Set : Reset);
}

/**
 * @brief  Get wake up event flag.
 * @param  [in] u8Flag Wake up event.
 *  @arg    PWC_PDWKF1_RTCPRDWKF
 *  @arg    PWC_PDWKF1_RTCALMWKF
 *  @arg    PWC_PDWKF1_XTAL32ERWK
 *  @arg    PWC_PDWKF1_WKTMWKF
 * @retval en_flag_status_t
 */
en_flag_status_t PWC_GetWakeup1Status(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_WKUP1_FLAG(u8Flag));

    return (READ_REG8_BIT(M4_PWC->PDWKF1, u8Flag) ? Set : Reset);
}

/**
 * @brief  HRC clock power config.
 * @param  [in] enNewState The new state of HRC power state.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_HrcPwrCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->PWRC1_b.VHRCSD, enNewState);
}

/**
 * @brief  PLLA & PLLH clock power config.
 * @param  [in] enNewState The new state of PLLA & PLLH power state.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_PllPwrCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (Enable == enNewState)
    {
        SET_REG8_BIT(M4_PWC->PWRC1, PWC_PWRC1_VPLLSD);
    }
    else
    {
        CLEAR_REG8_BIT(M4_PWC->PWRC1, PWC_PWRC1_VPLLSD);
    }
}

/**
 * @brief  Switch high speed to ultra low speed, set the drive ability.
 * @param  None
 * @retval Ok: Mode switch successful.
 *         Error: Mode switch failure, check whether EFM was unlocked please.
 * @note   Before calling this API, please switch system clock to the required
 *         low speed frequency in advance, and make sure NO any flash program
 *         or erase operation background.
 */
en_result_t PWC_HighSpeedToLowSpeed(void)
{
    en_result_t enRet = Ok;
    uint32_t u32To;

    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_EFM->FRMC_b.LVM, 0x01UL);
    WRITE_REG16(M4_PWC->RAMOPM, PWC_RAM_LOW);

    u32To = 0x1000UL;
    while (1UL != READ_REG32(bM4_EFM->FRMC_b.LVM))
    {
        if (0UL == u32To--)
        {
            enRet = Error;
            break;
        }
    }
    if (Ok == enRet)
    {
        u32To = 0x1000UL;
        while(PWC_RAM_LOW != READ_REG16(M4_PWC->RAMOPM))
        {
            if (0UL == u32To--)
            {
                enRet = Error;
                break;
            }
        }
    }
    if (Ok == enRet)
    {
        MODIFY_REG8(M4_PWC->PWRC2, PWC_PWRC2_DDAS, 0x01UL);
        WRITE_REG8(M4_PWC->PWRC3, 0x00UL);
        MODIFY_REG8(M4_PWC->PWRC2, PWC_PWRC2_DVS ,PWC_NOR_DRV_LOW);
        DDL_DelayMS(1UL);
    }
    return enRet;
}

/**
 * @brief  Switch ultra low speed to high speed, set the drive ability.
 * @param  None
 * @retval Ok: Mode switch successful.
 *         Error: Mode switch failure, check whether EFM was unlocked please.
 * @note   After calling this API, the system clock is able to switch high frequency.
 */
en_result_t PWC_LowSpeedToHighSpeed(void)
{
    en_result_t enRet = Ok;
    uint32_t u32To;

    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(M4_PWC->PWRC2, PWC_PWRC2_DDAS, 0x0FUL);
    WRITE_REG8(M4_PWC->PWRC3, 0xFFUL);
    SET_REG8_BIT(M4_PWC->PWRC2, PWC_NOR_DRV_HIGH);
    DDL_DelayMS(1UL);

    WRITE_REG32(bM4_EFM->FRMC_b.LVM, 0x00UL);
    WRITE_REG16(M4_PWC->RAMOPM, PWC_RAM_HIGH);

    u32To = 0x1000UL;
    while (0UL != READ_REG32(bM4_EFM->FRMC_b.LVM))
    {
        if (0UL == u32To--)
        {
            enRet = Error;
            break;
        }
    }
    if (Ok == enRet)
    {
        u32To = 0x1000UL;
        while(PWC_RAM_HIGH != READ_REG16(M4_PWC->RAMOPM))
        {
            if (0UL == u32To--)
            {
                enRet = Error;
                break;
            }
        }
    }
    return enRet;
}

/**
 * @brief  ADC buffer config.
 * @param  [in] enNewState The new state of ADC buffer.
 *  @arg Enable
 *  @arg Disable
 * @retval None
 */
void PWC_AdcBufCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->PWRC4_b.ADBUFE, enNewState);
}

/**
 * @brief  ADC internal channel sampling selection.
 * @param  [in] u8AdcInternVol The sampling voltage for ADC internal channel.
 *  @arg PWC_AD_INTERN_REF
 *  @arg PWC_AD_VBAT_DIV2
 * @retval None
 */
void PWC_AdcInternVolSel(uint8_t u8AdcInternVol)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->PWRC4_b.ADBUFS, u8AdcInternVol);
}

/**
 * @brief  Initialize Power down mode config structure. Fill each pstcPDModeConfig with default value
 * @param  [in] pstcPDModeConfig Pointer to a stc_pwc_pd_mode_config_t structure that
 *                            contains configuration information.
 * @retval Ok: Power down mode structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_PowerDownStructInit(stc_pwc_pd_mode_config_t *pstcPDModeConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPDModeConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcPDModeConfig->u8IOState = PWC_PD_IO_STATE1;
        pstcPDModeConfig->u8PDMode = PWC_PD_MODE1;
        pstcPDModeConfig->u8WkUpSpeed = PWC_PD_WKUP_SLOW;
    }
    return enRet;
}

/**
 * @brief  Power down mode config structure.
 * @param  [in] pstcPDModeConfig Pointer to a stc_pwc_pd_mode_config_t structure that
 *                            contains configuration information.
 * @retval Ok: Power down mode config successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_PowerDownConfig(const stc_pwc_pd_mode_config_t *pstcPDModeConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcPDModeConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PWC_UNLOCKED());

        MODIFY_REG8(M4_PWC->PWRC0, (PWC_PWRC0_IORTN | PWC_PWRC0_PDMDS),         \
                    (pstcPDModeConfig->u8IOState | pstcPDModeConfig->u8PDMode));
        WRITE_REG32(bM4_PWC->PWRC1_b.PDTS, pstcPDModeConfig->u8WkUpSpeed);
    }
    return enRet;
}

/**
 * @brief Stop mode config.
 * @param [in] pstcStopConfig Chip config before entry stop mode.
 *   @arg  u8StopDrv, MCU from which speed mode entry stop mode.
 *   @arg  u16ClkKeep, System clock setting after wake-up from stop mode.
 *   @arg  u16FlashWait, Whether wait flash stable after wake-up from stop mode.
 *   @arg  u16ExBusHold, ExBus status in stop mode.
 * @retval Ok: Stop mode config successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_StopConfig(const stc_pwc_stop_mode_config *pstcStopConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        DDL_ASSERT(IS_PWC_STOP_DRV(pstcStopConfig->u8StopDrv));
        DDL_ASSERT(IS_PWC_STOP_CLK(pstcStopConfig->u16ClkKeep));
        DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(pstcStopConfig->u16FlashWait));
        DDL_ASSERT(IS_PWC_STOP_EXBUS(pstcStopConfig->u16ExBusHold));

        DDL_ASSERT(IS_PWC_UNLOCKED());

        MODIFY_REG8(M4_PWC->PWRC1, PWC_PWRC1_STPDAS, pstcStopConfig->u8StopDrv);

        MODIFY_REG16(M4_PWC->STPMCR,                                            \
                    (PWC_STPMCR_EXBUSOE | PWC_STPMCR_CKSMRC | PWC_STPMCR_FLNWT),\
                    (pstcStopConfig->u16ExBusHold | pstcStopConfig->u16ClkKeep |\
                    pstcStopConfig->u16FlashWait));
    }
    return enRet;
}

/**
 * @brief  Initialize stop mode config structure. Fill each pstcStopConfig with default value
 * @param  [in] pstcStopConfig Pointer to a stc_pwc_stop_mode_config structure that
 *                            contains configuration information.
 * @retval Ok: Stop down mode structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t PWC_StopStructInit(stc_pwc_stop_mode_config *pstcStopConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcStopConfig->u8StopDrv = PWC_STOP_DRV_HIGH;
        pstcStopConfig->u16ExBusHold = PWC_STOP_EXBUS_HIZ;
        pstcStopConfig->u16ClkKeep = PWC_STOP_CLK_KEEP;
        pstcStopConfig->u16FlashWait = PWC_STOP_FLASH_WAIT;
    }
    return enRet;
}
/**
 * @brief Stop mode wake up clock config.
 * @param [in] u16ClkKeep System clock setting after wake-up from stop mode.
 *   @arg PWC_STOP_CLK_KEEP
 *   @arg PWC_STOP_CLK_MRC
 * @retval None
 */
void PWC_StopClockKeepConfig(uint16_t u16ClkKeep)
{
    DDL_ASSERT(IS_PWC_STOP_CLK(u16ClkKeep));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG16(M4_PWC->STPMCR, PWC_STPMCR_CKSMRC, u16ClkKeep);
}

/**
 * @brief Stop mode wake up flash wait config.
 * @param [in] u16FlashWait Whether wait flash stable after wake-up from stop mode.
 *   @arg PWC_STOP_FLASH_WAIT
 *   @arg PWC_STOP_FLASH_NOWAIT
 * @retval None
 */
void PWC_StopFlashWaitConfig(uint16_t u16FlashWait)
{
    DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(u16FlashWait));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG16(M4_PWC->STPMCR, PWC_STPMCR_FLNWT, u16FlashWait);
}

/**
 * @brief Stop mode ex-bus status config.
 * @param [in] u16ExBusHold ExBus status in stop mode.
 *   @arg PWC_STOP_EXBUS_HIZ
 *   @arg PWC_STOP_EXBUS_HOLD
 * @retval None
 */
void PWC_StopExBusHoldConfig(uint16_t u16ExBusHold)
{
    DDL_ASSERT(IS_PWC_STOP_EXBUS(u16ExBusHold));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG16(M4_PWC->STPMCR, PWC_STPMCR_EXBUSOE, u16ExBusHold);
}

/**
 * @brief Stop mode driver capacity config.
 * @param [in] u8StopDrv Drive capacity while enter stop mode.
 *   @arg  PWC_STOP_DRV_HIGH
 *   @arg  PWC_STOP_DRV_LOW
 * @retval None
 */
void PWC_StopDrvConfig(uint8_t u8StopDrv)
{
    DDL_ASSERT(IS_PWC_STOP_DRV(u8StopDrv));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(M4_PWC->PWRC1, PWC_PWRC1_STPDAS, u8StopDrv);
}

/**
 * @brief  VBAT monitor reference voltage selection.
 * @param  [in] u8RefVol                VBAT monitor reference voltage.
 *         This parameter can be one of the following values:
 *           @arg PWC_VBAT_REF_VOL_1P8V:  Vbat reference voltage is 1.8V
 *           @arg PWC_VBAT_REF_VOL_2P0V:  Vbat reference voltage is 2.0V
 * @retval None
 */
void PWC_VBAT_MonitorVolSel(uint8_t u8RefVol)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_VBAT_REF_VOL(u8RefVol));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->PWRC4_b.VBATREFSEL, u8RefVol);
}

/**
 * @brief  Enable or Disable VBAT monitor.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_VBAT_MonitorCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->PWRC4_b.VBATME, enNewState);
}

/**
 * @brief  Get VBAT voltage status.
 * @param  None
 * @retval uint8_t                      VBAT voltage status
 */
uint8_t PWC_VBAT_GetVolStatus(void)
{
    uint8_t u8VolSta;

    DDL_ASSERT(IS_PWC_UNLOCKED());

    u8VolSta = (uint8_t)READ_REG32(bM4_PWC->PWRC4_b.VBATMON);

    return u8VolSta;
}

/**
 * @brief  Enable or Disable VBAT measure voltage.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_VBAT_MeasureVolCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->VBATCR_b.VBATDIVMONE, enNewState);
}

/**
 * @brief  Reset the VBAT area.
 * @param  None
 * @retval None
 */
void PWC_VBAT_Reset(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    WRITE_REG8(M4_PWC->VBATRSTR, 0xA5U);
}

/**
 * @brief  Enable or Disable VBAT power.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_VBAT_PwrCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    DDL_ASSERT(IS_PWC_UNLOCKED());
    WRITE_REG32(bM4_PWC->VBATCR_b.CSDIS, enNewState);
}

/**
 * @brief  Enable or Disable Backup RAM power.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_BkRamPwrCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (Enable == enNewState)
    {
        WRITE_REG32(bM4_PWC->VBATCR_b.VBTRSD, 0UL);
    }
    else
    {
        WRITE_REG32(bM4_PWC->VBATCR_b.VBTRSD, 1UL);
    }
}

/**
 * @brief  Get Backup RAM flag.
 * @param  [in] u8Flag                  Backup RAM flag.
 *         This parameter can be one or any combination of the following values:
 *           @arg PWC_BACKUP_RAM_FLAG_RAMPDF:   Backup RAM power down flag
 *           @arg PWC_BACKUP_RAM_FLAG_RAMVALID: Backup RAM read/write flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_GetBkRamStatus(uint8_t u8Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_RAM_FLAG(u8Flag));

    DDL_ASSERT(IS_PWC_UNLOCKED());
    if (0U != (READ_REG8_BIT(M4_PWC->VBATCR, u8Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Write Backup register.
 * @param  [in] u8RegNum                Backup register number.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 127.
 * @param  [in] u8RegVal                Value written to register
 * @retval None
 */
void PWC_WriteBackupReg(uint8_t u8RegNum, uint8_t u8RegVal)
{
    __IO uint8_t *BKR;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_REGISTER_NUMBER(u8RegNum));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    BKR = (__IO uint8_t *)PWC_BKRx(u8RegNum);
    WRITE_REG8(*BKR, u8RegVal);
}

/**
 * @brief  Read Backup register.
 * @param  [in] u8RegNum                Backup register number.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 127.
 * @retval uint8_t                      Register value
 */
uint8_t PWC_ReadBackupReg(uint8_t u8RegNum)
{
    uint8_t u8RegVal;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_REGISTER_NUMBER(u8RegNum));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    u8RegVal = READ_REG8(*((__IO uint8_t *)PWC_BKRx(u8RegNum)));

    return u8RegVal;
}

/**
 * @brief  WKT Timer Initialize.
 * @param  [in] u8ClkSrc                Clock source.
 *         This parameter can be one of the following values:
 *           @arg PWC_WKT_CLK_SRC_64HZ:     64Hz Clock
 *           @arg PWC_WKT_CLK_SRC_XTAL32:   XTAL32 Clock
 *           @arg PWC_WKT_CLK_SRC_RTCLRC:   RTCLRC Clock
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval None
 */
void PWC_WKT_Init(uint8_t u8ClkSrc, uint16_t u16CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_WKT_CLK_SRC(u8ClkSrc));
    DDL_ASSERT(IS_PWC_WKT_COMPARISION_VALUE(u16CmpVal));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(M4_PWC->WKTC2, PWC_WKTC2_WKCKS, u8ClkSrc);
    WRITE_REG8(M4_PWC->WKTC0, (uint8_t)(u16CmpVal & 0x00FFU));
    WRITE_REG8(M4_PWC->WKTC1, (uint8_t)((u16CmpVal >> 8U) & 0x000FU));
}

/**
 * @brief  Set WKT Timer compare value.
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval None
 */
void PWC_WKT_SetCompareValue(uint16_t u16CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_WKT_COMPARISION_VALUE(u16CmpVal));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG8(M4_PWC->WKTC0, (uint8_t)(u16CmpVal & 0x00FFU));
    WRITE_REG8(M4_PWC->WKTC1, (uint8_t)((u16CmpVal >> 8U) & 0x000FU));
}

/**
 * @brief  Get WKT Timer compare value.
 * @param  None
 * @retval uint16_t                     WKT Compara value
 */
uint16_t PWC_WKT_GetCompareValue(void)
{
    uint16_t u16CmpVal;

    DDL_ASSERT(IS_PWC_UNLOCKED());

    u16CmpVal  = ((uint16_t)READ_REG16_BIT(M4_PWC->WKTC1, PWC_WKTC1_WKTMCMP) << 8U);
    u16CmpVal |= READ_REG8(M4_PWC->WKTC0);

    return u16CmpVal;
}

/**
 * @brief  Enable or Disable WKT Timer.
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_WKT_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bM4_PWC->WKTC2_b.WKTCE, enNewState);
}

/**
 * @brief  Get WKT Timer count match flag.
 * @param  None
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_WKT_GetStatus(void)
{
    en_flag_status_t enFlagSta;

    DDL_ASSERT(IS_PWC_UNLOCKED());

    enFlagSta = (en_flag_status_t)READ_REG32(bM4_PWC->WKTC2_b.WKOVF);

    return enFlagSta;
}

/**
 * @brief  Clear WKT Timer count match flag.
 * @param  None
 * @retval None
 */
void PWC_WKT_ClearStatus(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    WRITE_REG32(bM4_PWC->WKTC2_b.WKOVF, 0UL);
}

/**
 * @}
 */

#endif  /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

