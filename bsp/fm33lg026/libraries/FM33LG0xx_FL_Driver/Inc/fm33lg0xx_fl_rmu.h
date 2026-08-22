/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_rmu.h
  * @author  FMSH Application Team
  * @brief   Head file of RMU FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LG0XX_FL_RMU_H
#define __FM33LG0XX_FL_RMU_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup RMU RMU
  * @brief RMU FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RMU_FL_ES_INIT RMU Exported Init structures
  * @{
  */

/**
  * @brief FL RMU Init Sturcture definition
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RMU_FL_Exported_Constants RMU Exported Constants
  * @{
  */

#define    RMU_PDRCR_CFG_Pos                                      (1U)
#define    RMU_PDRCR_CFG_Msk                                      (0x3U << RMU_PDRCR_CFG_Pos)
#define    RMU_PDRCR_CFG                                          RMU_PDRCR_CFG_Msk

#define    RMU_PDRCR_EN_Pos                                       (0U)
#define    RMU_PDRCR_EN_Msk                                       (0x1U << RMU_PDRCR_EN_Pos)
#define    RMU_PDRCR_EN                                           RMU_PDRCR_EN_Msk

#define    RMU_BORCR_CFG_Pos                                      (2U)
#define    RMU_BORCR_CFG_Msk                                      (0x3U << RMU_BORCR_CFG_Pos)
#define    RMU_BORCR_CFG                                          RMU_BORCR_CFG_Msk

#define    RMU_BORCR_ENB_Pos                                      (0U)
#define    RMU_BORCR_ENB_Msk                                      (0x1U << RMU_BORCR_ENB_Pos)
#define    RMU_BORCR_ENB                                          RMU_BORCR_ENB_Msk

#define    RMU_LKPCR_EN_Pos                                       (1U)
#define    RMU_LKPCR_EN_Msk                                       (0x1U << RMU_LKPCR_EN_Pos)
#define    RMU_LKPCR_EN                                           RMU_LKPCR_EN_Msk

#define    RMU_RSTFR_MDFN_FLAG_Pos                                (12U)
#define    RMU_RSTFR_MDFN_FLAG_Msk                                (0x1U << RMU_RSTFR_MDFN_FLAG_Pos)
#define    RMU_RSTFR_MDFN_FLAG                                    RMU_RSTFR_MDFN_FLAG_Msk

#define    RMU_RSTFR_NRSTN_FLAG_Pos                               (11U)
#define    RMU_RSTFR_NRSTN_FLAG_Msk                               (0x1U << RMU_RSTFR_NRSTN_FLAG_Pos)
#define    RMU_RSTFR_NRSTN_FLAG                                   RMU_RSTFR_NRSTN_FLAG_Msk

#define    RMU_RSTFR_PRC_FLAG_Pos                                 (10U)
#define    RMU_RSTFR_PRC_FLAG_Msk                                 (0x1U << RMU_RSTFR_PRC_FLAG_Pos)
#define    RMU_RSTFR_PRC_FLAG                                     RMU_RSTFR_PRC_FLAG_Msk

#define    RMU_RSTFR_PORN_FLAG_Pos                                (9U)
#define    RMU_RSTFR_PORN_FLAG_Msk                                (0x1U << RMU_RSTFR_PORN_FLAG_Pos)
#define    RMU_RSTFR_PORN_FLAG                                    RMU_RSTFR_PORN_FLAG_Msk

#define    RMU_RSTFR_PDRN_FLAG_Pos                                (8U)
#define    RMU_RSTFR_PDRN_FLAG_Msk                                (0x1U << RMU_RSTFR_PDRN_FLAG_Pos)
#define    RMU_RSTFR_PDRN_FLAG                                    RMU_RSTFR_PDRN_FLAG_Msk

#define    RMU_RSTFR_SOFTN_FLAG_Pos                               (5U)
#define    RMU_RSTFR_SOFTN_FLAG_Msk                               (0x1U << RMU_RSTFR_SOFTN_FLAG_Pos)
#define    RMU_RSTFR_SOFTN_FLAG                                   RMU_RSTFR_SOFTN_FLAG_Msk

#define    RMU_RSTFR_IWDTN_FLAG_Pos                               (4U)
#define    RMU_RSTFR_IWDTN_FLAG_Msk                               (0x1U << RMU_RSTFR_IWDTN_FLAG_Pos)
#define    RMU_RSTFR_IWDTN_FLAG                                   RMU_RSTFR_IWDTN_FLAG_Msk

#define    RMU_RSTFR_WWDTN_FLAG_Pos                               (2U)
#define    RMU_RSTFR_WWDTN_FLAG_Msk                               (0x1U << RMU_RSTFR_WWDTN_FLAG_Pos)
#define    RMU_RSTFR_WWDTN_FLAG                                   RMU_RSTFR_WWDTN_FLAG_Msk

#define    RMU_RSTFR_LKUPN_FLAG_Pos                               (1U)
#define    RMU_RSTFR_LKUPN_FLAG_Msk                               (0x1U << RMU_RSTFR_LKUPN_FLAG_Pos)
#define    RMU_RSTFR_LKUPN_FLAG                                   RMU_RSTFR_LKUPN_FLAG_Msk

#define    RMU_RSTFR_NVICN_FLAG_Pos                               (0U)
#define    RMU_RSTFR_NVICN_FLAG_Msk                               (0x1U << RMU_RSTFR_NVICN_FLAG_Pos)
#define    RMU_RSTFR_NVICN_FLAG                                   RMU_RSTFR_NVICN_FLAG_Msk

#define    PERHRSTEN_KEY                                          (0x13579BDFUL)
#define    SOFTWARERESET_KEY                                      (0x5C5CAABBUL)

#define    FL_RMU_RSTAHB_DMA                                      (0x1U << 0U)
#define    FL_RMU_RSTAPB_UART5                                    (0x1fU << 0U)
#define    FL_RMU_RSTAPB_UART4                                    (0x1eU << 0U)
#define    FL_RMU_RSTAPB_UART3                                    (0x1dU << 0U)
#define    FL_RMU_RSTAPB_UART1                                    (0x1bU << 0U)
#define    FL_RMU_RSTAPB_UART0                                    (0x1aU << 0U)
#define    FL_RMU_RSTAPB_UCIR                                     (0x19U << 0U)
#define    FL_RMU_RSTAPB_U7816                                    (0x18U << 0U)
#define    FL_RMU_RSTAPB_GPTIM2                                   (0x17U << 0U)
#define    FL_RMU_RSTAPB_GPTIM1                                   (0x16U << 0U)
#define    FL_RMU_RSTAPB_GPTIM0                                   (0x15U << 0U)
#define    FL_RMU_RSTAPB_ATIM                                     (0x14U << 0U)
#define    FL_RMU_RSTAPB_BSTIM32                                  (0x13U << 0U)
#define    FL_RMU_RSTAPB_BSTIM16                                  (0x12U << 0U)
#define    FL_RMU_RSTAPB_SPI2                                     (0xfU << 0U)
#define    FL_RMU_RSTAPB_SPI1                                     (0xeU << 0U)
#define    FL_RMU_RSTAPB_SPI0                                     (0xdU << 0U)
#define    FL_RMU_RSTAPB_I2C                                      (0xbU << 0U)
#define    FL_RMU_RSTAPB_LPUART2                                  (0xaU << 0U)
#define    FL_RMU_RSTAPB_LPUART1                                  (0x9U << 0U)
#define    FL_RMU_RSTAPB_LPUART0                                  (0x8U << 0U)
#define    FL_RMU_RSTAPB_VREF                                     (0x6U << 0U)
#define    FL_RMU_RSTAPB_PGL                                      (0x5U << 0U)
#define    FL_RMU_RSTAPB_LCD                                      (0x4U << 0U)
#define    FL_RMU_RSTAPB_DAC                                      (0x3U << 0U)
#define    FL_RMU_RSTAPB_OPA                                      (0x2U << 0U)
#define    FL_RMU_RSTAPB_LPTIM16                                  (0x1U << 0U)
#define    FL_RMU_RSTAPB_LPTIM32                                  (0x0U << 0U)
#define    FL_RMU_RSTAPB_ADCCR                                    (0x38U << 0U)
#define    FL_RMU_RSTAPB_ADC                                      (0x37U << 0U)
#define    FL_RMU_RSTAPB_AES                                      (0x32U << 0U)
#define    FL_RMU_RSTAPB_CRC                                      (0x31U << 0U)
#define    FL_RMU_RSTAPB_RNG                                      (0x30U << 0U)
#define    FL_RMU_RSTAPB_DIVAS                                    (0x23U << 0U)
#define    FL_RMU_RSTAPB_CAN                                      (0x22U << 0U)
#define    FL_RMU_RSTAPB_SVD                                      (0x21U << 0U)
#define    FL_RMU_RSTAPB_COMP                                     (0x20U << 0U)



#define    FL_RMU_PDR_THRESHOLD_1P40V                             (0x0U << RMU_PDRCR_CFG_Pos)
#define    FL_RMU_PDR_THRESHOLD_1P45V                             (0x1U << RMU_PDRCR_CFG_Pos)
#define    FL_RMU_PDR_THRESHOLD_1P50V                             (0x2U << RMU_PDRCR_CFG_Pos)
#define    FL_RMU_PDR_THRESHOLD_1P55V                             (0x3U << RMU_PDRCR_CFG_Pos)


#define    FL_RMU_BOR_THRESHOLD_1P80V                             (0x0U << RMU_BORCR_CFG_Pos)
#define    FL_RMU_BOR_THRESHOLD_2P00V                             (0x1U << RMU_BORCR_CFG_Pos)
#define    FL_RMU_BOR_THRESHOLD_2P20V                             (0x2U << RMU_BORCR_CFG_Pos)
#define    FL_RMU_BOR_THRESHOLD_2P40V                             (0x3U << RMU_BORCR_CFG_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RMU_FL_Exported_Functions RMU Exported Functions
  * @{
  */

/**
  * @brief    Set Power Down Reset Voltage
  * @rmtoll   PDRCR    CFG    FL_RMU_PDR_SetThreshold
  * @param    RMUx RMU instance
  * @param    threshold This parameter can be one of the following values:
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P40V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P45V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P50V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P55V
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_PDR_SetThreshold(RMU_Type *RMUx, uint32_t threshold)
{
    MODIFY_REG(RMUx->PDRCR, RMU_PDRCR_CFG_Msk, threshold);
}

/**
  * @brief    Get Power Down Reset Voltage Setting
  * @rmtoll   PDRCR    CFG    FL_RMU_PDR_GetThreshold
  * @param    RMUx RMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P40V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P45V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P50V
  *           @arg @ref FL_RMU_PDR_THRESHOLD_1P55V
  */
__STATIC_INLINE uint32_t FL_RMU_PDR_GetThreshold(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->PDRCR, RMU_PDRCR_CFG_Msk));
}

/**
  * @brief    Get Power Down Reset Enable Status
  * @rmtoll   PDRCR    EN    FL_RMU_PDR_IsEnabled
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_PDR_IsEnabled(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->PDRCR, RMU_PDRCR_EN_Msk) == RMU_PDRCR_EN_Msk);
}

/**
  * @brief    Disable Power Down Reset
  * @rmtoll   PDRCR    EN    FL_RMU_PDR_Disable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_PDR_Disable(RMU_Type *RMUx)
{
    CLEAR_BIT(RMUx->PDRCR, RMU_PDRCR_EN_Msk);
}

/**
  * @brief    Enable Power Down Reset
  * @rmtoll   PDRCR    EN    FL_RMU_PDR_Enable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_PDR_Enable(RMU_Type *RMUx)
{
    SET_BIT(RMUx->PDRCR, RMU_PDRCR_EN_Msk);
}

/**
  * @brief    Set Brown Out Reset Voltage
  * @rmtoll   BORCR    CFG    FL_RMU_BOR_SetThreshold
  * @param    RMUx RMU instance
  * @param    threshold This parameter can be one of the following values:
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P80V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_2P00V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_2P20V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_2P40V
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BOR_SetThreshold(RMU_Type *RMUx, uint32_t threshold)
{
    MODIFY_REG(RMUx->BORCR, RMU_BORCR_CFG_Msk, threshold);
}

/**
  * @brief    Get Brown Out Reset Setting
  * @rmtoll   BORCR    CFG    FL_RMU_BOR_GetThreshold
  * @param    RMUx RMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RMU_BOR_THRESHOLD_1P80V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_2P00V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_2P20V
  *           @arg @ref FL_RMU_BOR_THRESHOLD_2P40V
  */
__STATIC_INLINE uint32_t FL_RMU_BOR_GetThreshold(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->BORCR, RMU_BORCR_CFG_Msk));
}

/**
  * @brief    Get Brown Out Reset Enable Status
  * @rmtoll   BORCR    ENB    FL_RMU_BOR_IsEnabled
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_BOR_IsEnabled(RMU_Type *RMUx)
{
    return (uint32_t)!(READ_BIT(RMUx->BORCR, RMU_BORCR_ENB_Msk) == RMU_BORCR_ENB_Msk);
}

/**
  * @brief    Disable Brown Out Reset
  * @rmtoll   BORCR    ENB    FL_RMU_BOR_Disable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BOR_Disable(RMU_Type *RMUx)
{
    SET_BIT(RMUx->BORCR, RMU_BORCR_ENB_Msk);
}

/**
  * @brief    Enable Brown Out Reset
  * @rmtoll   BORCR    ENB    FL_RMU_BOR_Enable
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_BOR_Enable(RMU_Type *RMUx)
{
    CLEAR_BIT(RMUx->BORCR, RMU_BORCR_ENB_Msk);
}

/**
  * @brief    Get LockUp Reset Enable Status
  * @rmtoll   LKPCR    EN    FL_RMU_IsEnabledLockUpReset
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsEnabledLockUpReset(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->LKPCR, RMU_LKPCR_EN_Msk) == RMU_LKPCR_EN_Msk);
}

/**
  * @brief    Disable LockUp Reset
  * @rmtoll   LKPCR    EN    FL_RMU_DisableLockUpReset
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_DisableLockUpReset(RMU_Type *RMUx)
{
    CLEAR_BIT(RMUx->LKPCR, RMU_LKPCR_EN_Msk);
}

/**
  * @brief    Enable LockUp Reset
  * @rmtoll   LKPCR    EN    FL_RMU_EnableLockUpReset
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_EnableLockUpReset(RMU_Type *RMUx)
{
    SET_BIT(RMUx->LKPCR, RMU_LKPCR_EN_Msk);
}

/**
  * @brief    Soft Reset Chip
  * @rmtoll   SOFTRST        FL_RMU_SetSoftReset
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_SetSoftReset(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->SOFTRST, SOFTWARERESET_KEY);
}

/**
  * @brief    Get MDF Reset Flag
  * @rmtoll   RSTFR    MDFN_FLAG    FL_RMU_IsActiveFlag_MDF
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_MDF(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_MDFN_FLAG_Msk) == (RMU_RSTFR_MDFN_FLAG_Msk));
}

/**
  * @brief    Clear MDF Reset Flag
  * @rmtoll   RSTFR    MDFN_FLAG    FL_RMU_ClearFlag_MDF
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_MDF(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_MDFN_FLAG_Msk);
}

/**
  * @brief    Get NRST Reset Flag
  * @rmtoll   RSTFR    NRSTN_FLAG    FL_RMU_IsActiveFlag_NRSTN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_NRSTN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_NRSTN_FLAG_Msk) == (RMU_RSTFR_NRSTN_FLAG_Msk));
}

/**
  * @brief    Clear NRST Reset Flag
  * @rmtoll   RSTFR    NRSTN_FLAG    FL_RMU_ClearFlag_NRSTN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_NRSTN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_NRSTN_FLAG_Msk);
}

/**
  * @brief    Get PRC Reset Flag
  * @rmtoll   RSTFR    PRC_FLAG    FL_RMU_IsActiveFlag_PRCN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_PRCN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_PRC_FLAG_Msk) == (RMU_RSTFR_PRC_FLAG_Msk));
}

/**
  * @brief    Clear PRC Reset Flag
  * @rmtoll   RSTFR    PRC_FLAG    FL_RMU_ClearFlag_PRCN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_PRCN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_PRC_FLAG_Msk);
}

/**
  * @brief    Get Power On Reset Flag
  * @rmtoll   RSTFR    PORN_FLAG    FL_RMU_IsActiveFlag_PORN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_PORN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_PORN_FLAG_Msk) == (RMU_RSTFR_PORN_FLAG_Msk));
}

/**
  * @brief    Clear Power On Reset Flag
  * @rmtoll   RSTFR    PORN_FLAG    FL_RMU_ClearFlag_PORN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_PORN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_PORN_FLAG_Msk);
}

/**
  * @brief    Get Power Down Reset Flag
  * @rmtoll   RSTFR    PDRN_FLAG    FL_RMU_IsActiveFlag_PDRN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_PDRN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_PDRN_FLAG_Msk) == (RMU_RSTFR_PDRN_FLAG_Msk));
}

/**
  * @brief    Clear Power Down Reset Flag
  * @rmtoll   RSTFR    PDRN_FLAG    FL_RMU_ClearFlag_PDRN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_PDRN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_PDRN_FLAG_Msk);
}

/**
  * @brief    Get Software Reset Flag
  * @rmtoll   RSTFR    SOFTN_FLAG    FL_RMU_IsActiveFlag_SOFTN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_SOFTN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_SOFTN_FLAG_Msk) == (RMU_RSTFR_SOFTN_FLAG_Msk));
}

/**
  * @brief    Clear Software Reset Flag
  * @rmtoll   RSTFR    SOFTN_FLAG    FL_RMU_ClearFlag_SOFTN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_SOFTN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_SOFTN_FLAG_Msk);
}

/**
  * @brief    Get IWDT Reset Flag
  * @rmtoll   RSTFR    IWDTN_FLAG    FL_RMU_IsActiveFlag_IWDTN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_IWDTN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_IWDTN_FLAG_Msk) == (RMU_RSTFR_IWDTN_FLAG_Msk));
}

/**
  * @brief    Clear IWDT Reset Flag
  * @rmtoll   RSTFR    IWDTN_FLAG    FL_RMU_ClearFlag_IWDTN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_IWDTN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_IWDTN_FLAG_Msk);
}

/**
  * @brief    Get WWDT Reset Flag
  * @rmtoll   RSTFR    WWDTN_FLAG    FL_RMU_IsActiveFlag_WWDTN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_WWDTN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_WWDTN_FLAG_Msk) == (RMU_RSTFR_WWDTN_FLAG_Msk));
}

/**
  * @brief    Clear WWDT Reset Flag
  * @rmtoll   RSTFR    WWDTN_FLAG    FL_RMU_ClearFlag_WWDTN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_WWDTN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_WWDTN_FLAG_Msk);
}

/**
  * @brief    Get LockUp Reset Flag
  * @rmtoll   RSTFR    LKUPN_FLAG    FL_RMU_IsActiveFlag_LKUPN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_LKUPN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_LKUPN_FLAG_Msk) == (RMU_RSTFR_LKUPN_FLAG_Msk));
}

/**
  * @brief    Clear LockUp Reset Flag
  * @rmtoll   RSTFR    LKUPN_FLAG    FL_RMU_ClearFlag_LKUPN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_LKUPN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_LKUPN_FLAG_Msk);
}

/**
  * @brief    Get NVIC Reset Flag
  * @rmtoll   RSTFR    NVICN_FLAG    FL_RMU_IsActiveFlag_NVICN
  * @param    RMUx RMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RMU_IsActiveFlag_NVICN(RMU_Type *RMUx)
{
    return (uint32_t)(READ_BIT(RMUx->RSTFR, RMU_RSTFR_NVICN_FLAG_Msk) == (RMU_RSTFR_NVICN_FLAG_Msk));
}

/**
  * @brief    Clear NVIC Reset Flag
  * @rmtoll   RSTFR    NVICN_FLAG    FL_RMU_ClearFlag_NVICN
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_ClearFlag_NVICN(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->RSTFR, RMU_RSTFR_NVICN_FLAG_Msk);
}

/**
  * @brief    Disable Peripheral Reset
  * @rmtoll   PRSTEN        FL_RMU_DisablePeripheralReset
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_DisablePeripheralReset(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->PRSTEN, (~PERHRSTEN_KEY));
}

/**
  * @brief    Enable Peripheral Reset
  * @rmtoll   PRSTEN        FL_RMU_EnablePeripheralReset
  * @param    RMUx RMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_EnablePeripheralReset(RMU_Type *RMUx)
{
    WRITE_REG(RMUx->PRSTEN, PERHRSTEN_KEY);
}

/**
  * @brief    Enable AHB Peripheral Reset
  * @rmtoll   AHBRSTCR        FL_RMU_EnableResetAHBPeripheral
  * @param    RMUx RMU instance
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RMU_RSTAHB_DMA
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_EnableResetAHBPeripheral(RMU_Type *RMUx, uint32_t peripheral)
{
    SET_BIT(RMUx->AHBRSTCR, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable APB Peripheral Reset1
  * @rmtoll   APBRSTCR        FL_RMU_EnableResetAPBPeripheral
  * @param    RMUx RMU instance
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RMU_RSTAPB_UART5
  *           @arg @ref FL_RMU_RSTAPB_UART4
  *           @arg @ref FL_RMU_RSTAPB_UART3
  *           @arg @ref FL_RMU_RSTAPB_UART1
  *           @arg @ref FL_RMU_RSTAPB_UART0
  *           @arg @ref FL_RMU_RSTAPB_UCIR
  *           @arg @ref FL_RMU_RSTAPB_U7816
  *           @arg @ref FL_RMU_RSTAPB_GPTIM2
  *           @arg @ref FL_RMU_RSTAPB_GPTIM1
  *           @arg @ref FL_RMU_RSTAPB_GPTIM0
  *           @arg @ref FL_RMU_RSTAPB_ATIM
  *           @arg @ref FL_RMU_RSTAPB_BSTIM32
  *           @arg @ref FL_RMU_RSTAPB_BSTIM16
  *           @arg @ref FL_RMU_RSTAPB_SPI2
  *           @arg @ref FL_RMU_RSTAPB_SPI1
  *           @arg @ref FL_RMU_RSTAPB_SPI0
  *           @arg @ref FL_RMU_RSTAPB_I2C
  *           @arg @ref FL_RMU_RSTAPB_LPUART2
  *           @arg @ref FL_RMU_RSTAPB_LPUART1
  *           @arg @ref FL_RMU_RSTAPB_LPUART0
  *           @arg @ref FL_RMU_RSTAPB_VREF
  *           @arg @ref FL_RMU_RSTAPB_PGL
  *           @arg @ref FL_RMU_RSTAPB_LCD
  *           @arg @ref FL_RMU_RSTAPB_DAC
  *           @arg @ref FL_RMU_RSTAPB_OPA
  *           @arg @ref FL_RMU_RSTAPB_LPTIM16
  *           @arg @ref FL_RMU_RSTAPB_LPTIM32
  *           @arg @ref FL_RMU_RSTAPB_ADCCR
  *           @arg @ref FL_RMU_RSTAPB_ADC
  *           @arg @ref FL_RMU_RSTAPB_AES
  *           @arg @ref FL_RMU_RSTAPB_CRC
  *           @arg @ref FL_RMU_RSTAPB_RNG
  *           @arg @ref FL_RMU_RSTAPB_DIVAS
  *           @arg @ref FL_RMU_RSTAPB_CAN
  *           @arg @ref FL_RMU_RSTAPB_SVD
  *           @arg @ref FL_RMU_RSTAPB_COMP
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_EnableResetAPBPeripheral(RMU_Type *RMUx, uint32_t peripheral)
{
    if(peripheral < FL_RMU_RSTAPB_COMP)
    {
        SET_BIT(RMUx->APBRSTCR1, (0x1U << peripheral));
    }
    else
    {
        SET_BIT(RMUx->APBRSTCR2, (0x1U << (peripheral - 32)));
    }
}

/**
  * @brief    Disable AHB Peripheral Reset
  * @rmtoll   AHBRSTCR        FL_RMU_DisableResetAHBPeripheral
  * @param    RMUx RMU instance
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RMU_RSTAHB_DMA
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_DisableResetAHBPeripheral(RMU_Type *RMUx, uint32_t peripheral)
{
    CLEAR_BIT(RMUx->AHBRSTCR, ((peripheral & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable APB Peripheral Reset1
  * @rmtoll   APBRSTCR        FL_RMU_DisableResetAPBPeripheral
  * @param    RMUx RMU instance
  * @param    peripheral This parameter can be one of the following values:
  *           @arg @ref FL_RMU_RSTAPB_UART5
  *           @arg @ref FL_RMU_RSTAPB_UART4
  *           @arg @ref FL_RMU_RSTAPB_UART3
  *           @arg @ref FL_RMU_RSTAPB_UART1
  *           @arg @ref FL_RMU_RSTAPB_UART0
  *           @arg @ref FL_RMU_RSTAPB_UCIR
  *           @arg @ref FL_RMU_RSTAPB_U7816
  *           @arg @ref FL_RMU_RSTAPB_GPTIM2
  *           @arg @ref FL_RMU_RSTAPB_GPTIM1
  *           @arg @ref FL_RMU_RSTAPB_GPTIM0
  *           @arg @ref FL_RMU_RSTAPB_ATIM
  *           @arg @ref FL_RMU_RSTAPB_BSTIM32
  *           @arg @ref FL_RMU_RSTAPB_BSTIM16
  *           @arg @ref FL_RMU_RSTAPB_SPI2
  *           @arg @ref FL_RMU_RSTAPB_SPI1
  *           @arg @ref FL_RMU_RSTAPB_SPI0
  *           @arg @ref FL_RMU_RSTAPB_I2C
  *           @arg @ref FL_RMU_RSTAPB_LPUART2
  *           @arg @ref FL_RMU_RSTAPB_LPUART1
  *           @arg @ref FL_RMU_RSTAPB_LPUART0
  *           @arg @ref FL_RMU_RSTAPB_VREF
  *           @arg @ref FL_RMU_RSTAPB_PGL
  *           @arg @ref FL_RMU_RSTAPB_LCD
  *           @arg @ref FL_RMU_RSTAPB_DAC
  *           @arg @ref FL_RMU_RSTAPB_OPA
  *           @arg @ref FL_RMU_RSTAPB_LPTIM16
  *           @arg @ref FL_RMU_RSTAPB_LPTIM32
  *           @arg @ref FL_RMU_RSTAPB_ADCCR
  *           @arg @ref FL_RMU_RSTAPB_ADC
  *           @arg @ref FL_RMU_RSTAPB_AES
  *           @arg @ref FL_RMU_RSTAPB_CRC
  *           @arg @ref FL_RMU_RSTAPB_RNG
  *           @arg @ref FL_RMU_RSTAPB_DIVAS
  *           @arg @ref FL_RMU_RSTAPB_CAN
  *           @arg @ref FL_RMU_RSTAPB_SVD
  *           @arg @ref FL_RMU_RSTAPB_COMP
  * @retval   None
  */
__STATIC_INLINE void FL_RMU_DisableResetAPBPeripheral(RMU_Type *RMUx, uint32_t peripheral)
{
    if(peripheral < FL_RMU_RSTAPB_COMP)
    {
        CLEAR_BIT(RMUx->APBRSTCR1, (0x1U << peripheral));
    }
    else
    {
        CLEAR_BIT(RMUx->APBRSTCR2, (0x1U << (peripheral - 32)));
    }
}

/**
  * @}
  */

/** @defgroup RMU_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

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

#endif /* __FM33LG0XX_FL_RMU_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2020-10-20*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
