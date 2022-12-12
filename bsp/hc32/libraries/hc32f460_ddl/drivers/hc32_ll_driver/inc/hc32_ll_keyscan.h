/**
 *******************************************************************************
 * @file  hc32_ll_keyscan.h
 * @brief This file contains all the functions prototypes of the KEYSCAN driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_KEYSCAN_H__
#define __HC32_LL_KEYSCAN_H__

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
 * @addtogroup LL_KEYSCAN
 * @{
 */

#if (LL_KEYSCAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup KEYSCAN_Global_Types KEYSCAN Global Types
 * @{
 */

/**
 * @brief  KEYSCAN configuration
 */
typedef struct {
    uint32_t u32HizCycle;           /*!< Specifies the KEYSCAN Hiz cycles.
                                        This parameter can be a value of @ref KEYSCAN_Hiz_Cycle_Sel */

    uint32_t u32LowCycle;           /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Low_Cycle_Sel */

    uint32_t u32KeyClock;           /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Clock_Sel */

    uint32_t u32KeyOut;             /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Keyout_Sel */

    uint32_t u32KeyIn;              /*!< Specifies the KEYSCAN low cycles.
                                        This parameter can be a value of @ref KEYSCAN_Keyin_Sel */
} stc_keyscan_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup KEYSCAN_Global_Macros KEYSCAN Global Macros
 * @{
 */

/**
 * @defgroup KEYSCAN_Hiz_Cycle_Sel KEYSCAN Hiz cycles during low ouput selection
 * @{
 */
#define KEYSCAN_HIZ_CYCLE_4     (0x00UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 4 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_8     (0x01UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 8 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_16    (0x02UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 16 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_32    (0x03UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 32 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_64    (0x04UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 64 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_256   (0x05UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 256 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_512   (0x06UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 512 cycles during low ouput */
#define KEYSCAN_HIZ_CYCLE_1024  (0x07UL << KEYSCAN_SCR_T_HIZ_POS)       /*!< KEYSCAN HiZ keep 1024 cycles during low ouput */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Low_Cycle_Sel KEYSCAN low level output cycles selection
 * @{
 */
#define KEYSCAN_LOW_CYCLE_4     (0x02UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^2=4 cycles */
#define KEYSCAN_LOW_CYCLE_8     (0x03UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^3=8 cycles */
#define KEYSCAN_LOW_CYCLE_16    (0x04UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^4=16 cycles */
#define KEYSCAN_LOW_CYCLE_32    (0x05UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^5=32 cycles */
#define KEYSCAN_LOW_CYCLE_64    (0x06UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^6=64 cycles */
#define KEYSCAN_LOW_CYCLE_128   (0x07UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^7=128 cycles */
#define KEYSCAN_LOW_CYCLE_256   (0x08UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^8=256 cycles */
#define KEYSCAN_LOW_CYCLE_512   (0x09UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^9=512 cycles */
#define KEYSCAN_LOW_CYCLE_1K    (0x0AUL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^10=1K cycles */
#define KEYSCAN_LOW_CYCLE_2K    (0x0BUL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^11=2K cycles */
#define KEYSCAN_LOW_CYCLE_4K    (0x0CUL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^12=4K cycles */
#define KEYSCAN_LOW_CYCLE_8K    (0x0DUL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^13=8K cycles */
#define KEYSCAN_LOW_CYCLE_16K   (0x0EUL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^14=16K cycles */
#define KEYSCAN_LOW_CYCLE_32K   (0x0FUL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^15=32K cycles */
#define KEYSCAN_LOW_CYCLE_64K   (0x10UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^16=64K cycles */
#define KEYSCAN_LOW_CYCLE_128K  (0x11UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^17=128K cycles */
#define KEYSCAN_LOW_CYCLE_256K  (0x12UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^18=256K cycles */
#define KEYSCAN_LOW_CYCLE_512K  (0x13UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^19=512K cycles */
#define KEYSCAN_LOW_CYCLE_1M    (0x14UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^20=1M cycles */
#define KEYSCAN_LOW_CYCLE_2M    (0x15UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^21=2M cycles */
#define KEYSCAN_LOW_CYCLE_4M    (0x16UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^22=4M cycles */
#define KEYSCAN_LOW_CYCLE_8M    (0x17UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^23=8M cycles */
#define KEYSCAN_LOW_CYCLE_16M   (0x18UL << KEYSCAN_SCR_T_LLEVEL_POS)    /*!< KEYSCAN low level output is 2^24=16M cycles */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Clock_Sel KEYSCAN scan clock selection
 * @{
 */
#define KEYSCAN_CLK_HCLK        (0x00UL)                    /*!< Use as HCLK KEYSCAN clock */
#define KEYSCAN_CLK_LRC         (KEYSCAN_SCR_CKSEL_0)       /*!< Use as LRC KEYSCAN clock */
#define KEYSCAN_CLK_XTAL32      (KEYSCAN_SCR_CKSEL_1)       /*!< Use as XTAL32 KEYSCAN clock */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Keyout_Sel KEYSCAN keyout pins selection
 * @{
 */
#define KEYSCAN_OUT_0T1         (0x01UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 1 are selected */
#define KEYSCAN_OUT_0T2         (0x02UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 2 are selected */
#define KEYSCAN_OUT_0T3         (0x03UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 3 are selected */
#define KEYSCAN_OUT_0T4         (0x04UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 4 are selected */
#define KEYSCAN_OUT_0T5         (0x05UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 5 are selected */
#define KEYSCAN_OUT_0T6         (0x06UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 6 are selected */
#define KEYSCAN_OUT_0T7         (0x07UL << KEYSCAN_SCR_KEYOUTSEL_POS)   /*!< KEYOUT 0 ~ 7 are selected */
/**
 * @}
 */

/**
 * @defgroup KEYSCAN_Keyin_Sel KEYSCAN keyin pins selection
 * @{
 */
#define KEYSCAN_IN_0            (KEYSCAN_SCR_KEYINSEL_0)    /*!< KEYIN(EIRQ) 0 is selected */
#define KEYSCAN_IN_1            (KEYSCAN_SCR_KEYINSEL_1)    /*!< KEYIN(EIRQ) 1 is selected */
#define KEYSCAN_IN_2            (KEYSCAN_SCR_KEYINSEL_2)    /*!< KEYIN(EIRQ) 2 is selected */
#define KEYSCAN_IN_3            (KEYSCAN_SCR_KEYINSEL_3)    /*!< KEYIN(EIRQ) 3 is selected */
#define KEYSCAN_IN_4            (KEYSCAN_SCR_KEYINSEL_4)    /*!< KEYIN(EIRQ) 4 is selected */
#define KEYSCAN_IN_5            (KEYSCAN_SCR_KEYINSEL_5)    /*!< KEYIN(EIRQ) 5 is selected */
#define KEYSCAN_IN_6            (KEYSCAN_SCR_KEYINSEL_6)    /*!< KEYIN(EIRQ) 6 is selected */
#define KEYSCAN_IN_7            (KEYSCAN_SCR_KEYINSEL_7)    /*!< KEYIN(EIRQ) 7 is selected */
#define KEYSCAN_IN_8            (KEYSCAN_SCR_KEYINSEL_8)    /*!< KEYIN(EIRQ) 8  is selected */
#define KEYSCAN_IN_9            (KEYSCAN_SCR_KEYINSEL_9)    /*!< KEYIN(EIRQ) 9  is selected */
#define KEYSCAN_IN_10           (KEYSCAN_SCR_KEYINSEL_10)   /*!< KEYIN(EIRQ) 10 is selected */
#define KEYSCAN_IN_11           (KEYSCAN_SCR_KEYINSEL_11)   /*!< KEYIN(EIRQ) 11 is selected */
#define KEYSCAN_IN_12           (KEYSCAN_SCR_KEYINSEL_12)   /*!< KEYIN(EIRQ) 12 is selected */
#define KEYSCAN_IN_13           (KEYSCAN_SCR_KEYINSEL_13)   /*!< KEYIN(EIRQ) 13 is selected */
#define KEYSCAN_IN_14           (KEYSCAN_SCR_KEYINSEL_14)   /*!< KEYIN(EIRQ) 14 is selected */
#define KEYSCAN_IN_15           (KEYSCAN_SCR_KEYINSEL_15)   /*!< KEYIN(EIRQ) 15 is selected */
#define KEYSCAN_IN_ALL          (KEYSCAN_SCR_KEYINSEL)      /*!< KEYIN(EIRQ) mask */

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
 * @addtogroup KEYSCAN_Global_Functions
 * @{
 */
/**
 * @brief  Get KEYOUT index.
 * @param  None
 * @retval uint32_t: KEYOUT index 0~7.
 */
__STATIC_INLINE uint32_t KEYSCAN_GetKeyoutIdx(void)
{
    return READ_REG32_BIT(CM_KEYSCAN->SSR, KEYSCAN_SSR_INDEX);
}

int32_t KEYSCAN_StructInit(stc_keyscan_init_t *pstcKeyscanInit);
int32_t KEYSCAN_Init(const stc_keyscan_init_t *pstcKeyscanInit);
void KEYSCAN_Cmd(en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_KEYSCAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_KEYSCAN_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
