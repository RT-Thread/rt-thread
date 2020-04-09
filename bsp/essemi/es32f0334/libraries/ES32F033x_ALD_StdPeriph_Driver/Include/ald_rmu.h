/**
  *********************************************************************************
  *
  * @file    ald_rmu.h
  * @brief   Header file of RMU module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_RMU_H__
#define __ALD_RMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup RMU
  * @{
  */

/** @defgroup RMU_Public_Types RMU Public Types
  * @{
  */
/**
  * @brief RMU BOR fliter
  */
typedef enum
{
    RMU_BORFLT_1 = 0x1,	/**< 1 cycle  */
    RMU_BORFLT_2 = 0x2,	/**< 2 cycles */
    RMU_BORFLT_3 = 0x3,	/**< 3 cycles */
    RMU_BORFLT_4 = 0x4,	/**< 4 cycles */
    RMU_BORFLT_5 = 0x5,	/**< 5 cycles */
    RMU_BORFLT_6 = 0x6,	/**< 6 cycles */
    RMU_BORFLT_7 = 0x7,	/**< 7 cycles */
} rmu_bor_filter_t;

/**
  * @brief RMU BOR voltage
  */
typedef enum
{
    RMU_VOL_1_7 = 0x0,	/**< 1.7V */
    RMU_VOL_2_0 = 0x1,	/**< 2.0V */
    RMU_VOL_2_1 = 0x2,	/**< 2.1V */
    RMU_VOL_2_2 = 0x3,	/**< 2.2V */
    RMU_VOL_2_3 = 0x4,	/**< 2.3V */
    RMU_VOL_2_4 = 0x5,	/**< 2.4V */
    RMU_VOL_2_5 = 0x6,	/**< 2.5V */
    RMU_VOL_2_6 = 0x7,	/**< 2.6V */
    RMU_VOL_2_8 = 0x8,	/**< 2.8V */
    RMU_VOL_3_0 = 0x9,	/**< 3.0V */
    RMU_VOL_3_1 = 0xA,	/**< 3.1V */
    RMU_VOL_3_3 = 0xB,	/**< 3.3V */
    RMU_VOL_3_6 = 0xC,	/**< 3.6V */
    RMU_VOL_3_7 = 0xD,	/**< 3.7V */
    RMU_VOL_4_0 = 0xE,	/**< 4.0V */
    RMU_VOL_4_3 = 0xF,	/**< 4.3V */
} rmu_bor_vol_t;

/**
  * @brief RMU reset status
  */
typedef enum
{
    RMU_RST_POR    = (1U << 0),	/**< POR */
    RMU_RST_WAKEUP = (1U << 1),	/**< WAKEUP */
    RMU_RST_BOR    = (1U << 2),	/**< BOR */
    RMU_RST_NMRST  = (1U << 3),	/**< NMRST */
    RMU_RST_IWDT   = (1U << 4),	/**< IWDT */
    RMU_RST_WWDT   = (1U << 5),	/**< WWDT */
    RMU_RST_LOCKUP = (1U << 6),	/**< LOCKUP */
    RMU_RST_CHIP   = (1U << 7),	/**< CHIP */
    RMU_RST_MCU    = (1U << 8),	/**< MCU */
    RMU_RST_CPU    = (1U << 9),	/**< CPU */
    RMU_RST_CFG    = (1U << 10),	/**< CFG */
    RMU_RST_CFGERR = (1U << 16),	/**< CFG Error */
} rmu_state_t;

/**
  * @brief RMU periperal select bit
  * @note  ES32F065x:
  *          AD16C4T0--TIMER0
  *          GP16C4T0--TIMER6
  *          GP16C2T0--TIMER2
  *          GP16C2T1--TIMER3
  *          BS16T0----TIMER1
  *          BS16T1----TIMER4
  *          BS16T2----TIMER5
  *          BS16T3----TIMER7
  *
  *        ES32F033x:
  *        ES32F093x:
  *          GP16C4T0--TIMER0
  *          GP16C4T1--TIMER6
  *          GP16C2T0--TIMER2
  *          GP16C2T1--TIMER3
  *          BS16T0----TIMER1
  *          BS16T1----TIMER4
  *          BS16T2----TIMER5
  *          BS16T3----TIMER7
  */
typedef enum
{
    RMU_PERH_GPIO    = (1U << 0),			/**< AHB1: GPIO */
    RMU_PERH_CRC     = (1U << 1),			/**< AHB1: CRC */
    RMU_PERH_CALC    = (1U << 2),			/**< AHB1: CALC */
    RMU_PERH_CRYPT   = (1U << 3),			/**< AHB1: CRYPT */
    RMU_PERH_TRNG    = (1U << 4),			/**< AHB1: TRNG */
    RMU_PERH_PIS     = (1U << 5),			/**< AHB1: PIS */
    RMU_PERH_CHIP    = (1U << 0)  | (1U << 27),	/**< AHB2: CHIP */
    RMU_PERH_CPU     = (1U << 1)  | (1U << 27),	/**< AHB2: CPU */
    RMU_PERH_TIMER0  = (1U << 0)  | (1U << 28),	/**< APB1: TIMER0 */
    RMU_PERH_TIMER1  = (1U << 1)  | (1U << 28),	/**< APB1: TIMER1 */
    RMU_PERH_TIMER2  = (1U << 2)  | (1U << 28),	/**< APB1: TIMER2 */
    RMU_PERH_TIMER3  = (1U << 3)  | (1U << 28),	/**< APB1: TIMER3 */
    RMU_PERH_TIMER4  = (1U << 4)  | (1U << 28),	/**< APB1: TIMER4 */
    RMU_PERH_TIMER5  = (1U << 5)  | (1U << 28),	/**< APB1: TIMER5 */
    RMU_PERH_TIMER6  = (1U << 6)  | (1U << 28),	/**< APB1: TIMER6 */
    RMU_PERH_TIMER7  = (1U << 7)  | (1U << 28),	/**< APB1: TIMER7 */
    RMU_PERH_UART0   = (1U << 8)  | (1U << 28),	/**< APB1: UART0 */
    RMU_PERH_UART1   = (1U << 9)  | (1U << 28),	/**< APB1: UART1 */
    RMU_PERH_UART2   = (1U << 10) | (1U << 28),	/**< APB1: UART2 */
    RMU_PERH_UART3   = (1U << 11) | (1U << 28),	/**< APB1: UART3 */
    RMU_PERH_USART0  = (1U << 12) | (1U << 28),	/**< APB1: EUART0 */
    RMU_PERH_USART1  = (1U << 13) | (1U << 28),	/**< APB1: EUART1 */
    RMU_PERH_SPI0    = (1U << 16) | (1U << 28),	/**< APB1: SPI0 */
    RMU_PERH_SPI1    = (1U << 17) | (1U << 28),	/**< APB1: SPI1 */
    RMU_PERH_SPI2    = (1U << 18) | (1U << 28),	/**< APB1: SPI2 */
    RMU_PERH_I2C0    = (1U << 20) | (1U << 28),	/**< APB1: I2C0 */
    RMU_PERH_I2C1    = (1U << 21) | (1U << 28),	/**< APB1: I2C1 */
    RMU_PERH_CAN0    = (1U << 24) | (1U << 28),	/**< APB1: CAN0 */
    RMU_PERH_LPTIM0  = (1U << 0)  | (1U << 29),	/**< APB2: LPTIM0 */
    RMU_PERH_LPUART0 = (1U << 2)  | (1U << 29),	/**< APB2: LPUART */
    RMU_PERH_ADC0    = (1U << 4)  | (1U << 29),	/**< APB2: ADC0 */
    RMU_PERH_ADC1    = (1U << 5)  | (1U << 29),	/**< APB2: ADC1 */
    RMU_PERH_ACMP0   = (1U << 6)  | (1U << 29),	/**< APB2: ACMP0 */
    RMU_PERH_ACMP1   = (1U << 7)  | (1U << 29),	/**< APB2: ACMP1 */
    RMU_PERH_OPAMP   = (1U << 8)  | (1U << 29),	/**< APB2: OPAMP */
    RMU_PERH_DAC0    = (1U << 9)  | (1U << 29),	/**< APB2: DAC0 */
    RMU_PERH_WWDT    = (1U << 12) | (1U << 29),	/**< APB2: WWDT */
    RMU_PERH_LCD     = (1U << 13) | (1U << 29),	/**< APB2: LCD */
    RMU_PERH_IWDT    = (1U << 14) | (1U << 29),	/**< APB2: IWDT */
    RMU_PERH_RTC     = (1U << 15) | (1U << 29),	/**< APB2: RTC */
    RMU_PERH_TSENSE  = (1U << 16) | (1U << 29),	/**< APB2: TSENSE */
    RMU_PERH_BKPC    = (1U << 17) | (1U << 29),	/**< APB2: BKPC */
    RMU_PERH_BKPRAM  = (1U << 18) | (1U << 29),	/**< APB2: BKPRAM */
} rmu_peripheral_t;
/**
  * @}
  */

/**
  * @defgroup RMU_Private_Macros RMU Private Macros
  * @{
  */
#define IS_RMU_BORFLT(x)	(((x) == RMU_BORFLT_1) || \
                             ((x) == RMU_BORFLT_2) || \
                             ((x) == RMU_BORFLT_3) || \
                             ((x) == RMU_BORFLT_4) || \
                             ((x) == RMU_BORFLT_5) || \
                             ((x) == RMU_BORFLT_6) || \
                             ((x) == RMU_BORFLT_7))
#define IS_RMU_BORVOL(x)	(((x) == RMU_VOL_1_7) || \
                             ((x) == RMU_VOL_2_0) || \
                             ((x) == RMU_VOL_2_1) || \
                             ((x) == RMU_VOL_2_2) || \
                             ((x) == RMU_VOL_2_3) || \
                             ((x) == RMU_VOL_2_4) || \
                             ((x) == RMU_VOL_2_5) || \
                             ((x) == RMU_VOL_2_6) || \
                             ((x) == RMU_VOL_2_8) || \
                             ((x) == RMU_VOL_3_0) || \
                             ((x) == RMU_VOL_3_1) || \
                             ((x) == RMU_VOL_3_3) || \
                             ((x) == RMU_VOL_3_6) || \
                             ((x) == RMU_VOL_3_7) || \
                             ((x) == RMU_VOL_4_0) || \
                             ((x) == RMU_VOL_4_3))
#define IS_RMU_STATE(x)		(((x) == RMU_RST_POR)    || \
                             ((x) == RMU_RST_WAKEUP) || \
                             ((x) == RMU_RST_BOR)    || \
                             ((x) == RMU_RST_NMRST)  || \
                             ((x) == RMU_RST_IWDT)   || \
                             ((x) == RMU_RST_WWDT)   || \
                             ((x) == RMU_RST_LOCKUP) || \
                             ((x) == RMU_RST_CHIP)   || \
                             ((x) == RMU_RST_MCU)    || \
                             ((x) == RMU_RST_CPU)    || \
                             ((x) == RMU_RST_CFG)    || \
                             ((x) == RMU_RST_CFGERR))
#define IS_RMU_STATE_CLEAR(x)	(((x) == RMU_RST_POR)    || \
                                 ((x) == RMU_RST_WAKEUP) || \
                                 ((x) == RMU_RST_BOR)    || \
                                 ((x) == RMU_RST_NMRST)  || \
                                 ((x) == RMU_RST_IWDT)   || \
                                 ((x) == RMU_RST_WWDT)   || \
                                 ((x) == RMU_RST_LOCKUP) || \
                                 ((x) == RMU_RST_CHIP)   || \
                                 ((x) == RMU_RST_MCU)    || \
                                 ((x) == RMU_RST_CPU)    || \
                                 ((x) == RMU_RST_CFG))
#define IS_RMU_PERH(x)		(((x) == RMU_PERH_GPIO)    || \
                             ((x) == RMU_PERH_CRC)     || \
                             ((x) == RMU_PERH_CALC)    || \
                             ((x) == RMU_PERH_CRYPT)   || \
                             ((x) == RMU_PERH_TRNG)    || \
                             ((x) == RMU_PERH_PIS)     || \
                             ((x) == RMU_PERH_CHIP)    || \
                             ((x) == RMU_PERH_CPU)     || \
                             ((x) == RMU_PERH_TIMER0)  || \
                             ((x) == RMU_PERH_TIMER1)  || \
                             ((x) == RMU_PERH_TIMER2)  || \
                             ((x) == RMU_PERH_TIMER3)  || \
                             ((x) == RMU_PERH_TIMER4)  || \
                             ((x) == RMU_PERH_TIMER5)  || \
                             ((x) == RMU_PERH_TIMER6)  || \
                             ((x) == RMU_PERH_TIMER7)  || \
                             ((x) == RMU_PERH_UART0)   || \
                             ((x) == RMU_PERH_UART1)   || \
                             ((x) == RMU_PERH_UART2)   || \
                             ((x) == RMU_PERH_UART3)   || \
                             ((x) == RMU_PERH_USART0)  || \
                             ((x) == RMU_PERH_USART1)  || \
                             ((x) == RMU_PERH_SPI0)    || \
                             ((x) == RMU_PERH_SPI1)    || \
                             ((x) == RMU_PERH_SPI2)    || \
                             ((x) == RMU_PERH_I2C0)    || \
                             ((x) == RMU_PERH_I2C1)    || \
                             ((x) == RMU_PERH_CAN0)    || \
                             ((x) == RMU_PERH_LPTIM0)  || \
                             ((x) == RMU_PERH_LPUART0) || \
                             ((x) == RMU_PERH_ADC0)    || \
                             ((x) == RMU_PERH_ADC1)    || \
                             ((x) == RMU_PERH_ACMP0)   || \
                             ((x) == RMU_PERH_ACMP1)   || \
                             ((x) == RMU_PERH_OPAMP)   || \
                             ((x) == RMU_PERH_DAC0)    || \
                             ((x) == RMU_PERH_WWDT)    || \
                             ((x) == RMU_PERH_LCD)     || \
                             ((x) == RMU_PERH_IWDT)    || \
                             ((x) == RMU_PERH_RTC)     || \
                             ((x) == RMU_PERH_TSENSE)    || \
                             ((x) == RMU_PERH_BKPC)    || \
                             ((x) == RMU_PERH_BKPRAM))
/**
  * @}
  */

/** @addtogroup RMU_Public_Functions
  * @{
  */
void ald_rmu_bor_config(rmu_bor_filter_t flt, rmu_bor_vol_t vol, type_func_t state);
flag_status_t ald_rmu_get_reset_status(rmu_state_t state);
void ald_rmu_clear_reset_status(rmu_state_t state);
void ald_rmu_reset_periperal(rmu_peripheral_t perh);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __ALD_RMU_H__ */
