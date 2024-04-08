/**
 *******************************************************************************
 * @file  hc32_ll_rmu.h
 * @brief This file contains all the functions prototypes of the RMU driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_RMU_H__
#define __HC32_LL_RMU_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_RMU
 * @{
 */
#if (LL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Global_Macros RMU Global Macros
 * @{
 */

/**
 * @defgroup RMU_ResetCause Rmu reset cause
 * @{
 */
#define RMU_FLAG_PWR_ON                 (RMU_RSTF0_PORF)        /*!< Power on reset */
#define RMU_FLAG_PIN                    (RMU_RSTF0_PINRF)       /*!< Reset pin reset */
#define RMU_FLAG_BROWN_OUT              (RMU_RSTF0_BORF)        /*!< Brown-out reset */
#define RMU_FLAG_PVD1                   (RMU_RSTF0_PVD1RF)      /*!< Program voltage Detection 1 reset */
#define RMU_FLAG_PVD2                   (RMU_RSTF0_PVD2RF)      /*!< Program voltage Detection 2 reset */
#define RMU_FLAG_WDT                    (RMU_RSTF0_WDRF)        /*!< Watchdog timer reset */
#define RMU_FLAG_SWDT                   (RMU_RSTF0_SWDRF)       /*!< Special watchdog timer reset */
#define RMU_FLAG_PWR_DOWN               (RMU_RSTF0_PDRF)        /*!< Power down reset */
#define RMU_FLAG_SW                     (RMU_RSTF0_SWRF)        /*!< Software reset */
#define RMU_FLAG_MPU_ERR                (RMU_RSTF0_MPUERF)      /*!< Mpu error reset */
#define RMU_FLAG_RAM_PARITY_ERR         (RMU_RSTF0_RAPERF)      /*!< Ram parity error reset */
#define RMU_FLAG_RAM_ECC                (RMU_RSTF0_RAECRF)      /*!< Ram ECC reset */
#define RMU_FLAG_CLK_ERR                (RMU_RSTF0_CKFERF)      /*!< Clk frequency error reset */
#define RMU_FLAG_XTAL_ERR               (RMU_RSTF0_XTALERF)     /*!< Xtal error reset */
#define RMU_FLAG_CPU_LOCKUP             (RMU_RSTF0_LKUPRF)      /*!< M4 Lockup reset */
#define RMU_FLAG_MX                     (RMU_RSTF0_MULTIRF)     /*!< Multiply reset cause */
#define RMU_FLAG_ALL                    (RMU_FLAG_PWR_ON | RMU_FLAG_PIN | RMU_FLAG_BROWN_OUT | RMU_FLAG_PVD1 | \
                                        RMU_FLAG_PVD2 | RMU_FLAG_WDT | RMU_FLAG_SWDT | RMU_FLAG_PWR_DOWN | \
                                        RMU_FLAG_SW | RMU_FLAG_MPU_ERR | RMU_FLAG_RAM_PARITY_ERR | RMU_FLAG_RAM_ECC | \
                                        RMU_FLAG_CLK_ERR | RMU_FLAG_XTAL_ERR | RMU_FLAG_CPU_LOCKUP | RMU_FLAG_MX)

/**
 * @}
 */

/**
 * @defgroup RMU_FRST0_Peripheral RMU FRST0 peripheral
 * @{
 */
#define RMU_FRST0_PERIPH_KEY          (RMU_FRST0_KEY)
#define RMU_FRST0_PERIPH_DMA1         (RMU_FRST0_DMA1)
#define RMU_FRST0_PERIPH_DMA2         (RMU_FRST0_DMA2)
#define RMU_FRST0_PERIPH_FCM          (RMU_FRST0_FCM)
#define RMU_FRST0_PERIPH_AOS          (RMU_FRST0_AOS)
#define RMU_FRST0_PERIPH_CTC          (RMU_FRST0_CTC)
#define RMU_FRST0_PERIPH_AES          (RMU_FRST0_AES)
#define RMU_FRST0_PERIPH_HASH         (RMU_FRST0_HASH)
#define RMU_FRST0_PERIPH_TRNG         (RMU_FRST0_TRNG)
#define RMU_FRST0_PERIPH_CRC          (RMU_FRST0_CRC)
#define RMU_FRST0_PERIPH_DCU1         (RMU_FRST0_DCU1)
#define RMU_FRST0_PERIPH_DCU2         (RMU_FRST0_DCU2)
#define RMU_FRST0_PERIPH_DCU3         (RMU_FRST0_DCU3)
#define RMU_FRST0_PERIPH_DCU4         (RMU_FRST0_DCU4)
#define RMU_FRST0_PERIPH_ALL          (0x0FF7E000UL)
/**
 * @}
 */

/**
 * @defgroup RMU_FRST1_Peripheral RMU FRST1 peripheral
 * @{
 */
#define RMU_FRST1_PERIPH_QSPI           (RMU_FRST1_QSPI)
#define RMU_FRST1_PERIPH_SPI1           (RMU_FRST1_SPI1)
#define RMU_FRST1_PERIPH_SPI2           (RMU_FRST1_SPI2)
#define RMU_FRST1_PERIPH_SPI3           (RMU_FRST1_SPI3)
#define RMU_FRST1_PERIPH_ALL            (0x00070008UL)
/**
 * @}
 */

/**
 * @defgroup RMU_FRST2_Peripheral RMU FRST2 peripheral
 * @{
 */
#define RMU_FRST2_PERIPH_TMR6           (RMU_FRST2_TMR6)
#define RMU_FRST2_PERIPH_TMR4           (RMU_FRST2_TMR4)
#define RMU_FRST2_PERIPH_TMR0           (RMU_FRST2_TMR0)
#define RMU_FRST2_PERIPH_EMB            (RMU_FRST2_EMB)
#define RMU_FRST2_PERIPH_TMRA           (RMU_FRST2_TMRA)
#define RMU_FRST2_PERIPH_ALL            (0x00109401UL)
/**
 * @}
 */

/**
 * @defgroup RMU_FRST3_Peripheral RMU FRST3 peripheral
 * @{
 */
#define RMU_FRST3_PERIPH_ADC1           (RMU_FRST3_ADC1)
#define RMU_FRST3_PERIPH_ADC2           (RMU_FRST3_ADC2)
#define RMU_FRST3_PERIPH_ADC3           (RMU_FRST3_ADC3)
#define RMU_FRST3_PERIPH_DAC            (RMU_FRST3_DAC)
#define RMU_FRST3_PERIPH_CMP1_2         (RMU_FRST3_CMP12)
#define RMU_FRST3_PERIPH_CMP3_4         (RMU_FRST3_CMP34)
#define RMU_FRST3_PERIPH_SMC            (RMU_FRST3_SMC)
#define RMU_FRST3_PERIPH_USART1         (RMU_FRST3_USART1)
#define RMU_FRST3_PERIPH_USART2         (RMU_FRST3_USART2)
#define RMU_FRST3_PERIPH_USART3         (RMU_FRST3_USART3)
#define RMU_FRST3_PERIPH_USART4         (RMU_FRST3_USART4)
#define RMU_FRST3_PERIPH_USART5         (RMU_FRST3_USART5)
#define RMU_FRST3_PERIPH_USART6         (RMU_FRST3_USART6)
#define RMU_FRST3_PERIPH_ALL            (0x03F10317UL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup RMU_Global_Functions
 * @{
 */

en_flag_status_t RMU_GetStatus(uint32_t u32RmuResetCause);
void RMU_ClearStatus(void);

void RMU_CPULockUpCmd(en_functional_state_t enNewState);

int32_t RMU_Frst0PeriphReset(uint32_t u32Frst0Periph);
int32_t RMU_Frst1PeriphReset(uint32_t u32Frst1Periph);
int32_t RMU_Frst2PeriphReset(uint32_t u32Frst2Periph);
int32_t RMU_Frst3PeriphReset(uint32_t u32Frst3Periph);

/**
 * @}
 */

#endif /* LL_RMU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_RMU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

