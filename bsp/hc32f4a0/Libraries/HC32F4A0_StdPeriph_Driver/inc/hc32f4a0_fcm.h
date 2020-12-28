/**
 *******************************************************************************
 * @file  hc32f4a0_fcm.h
 * @brief This file contains all the functions prototypes of the FCM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
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
#ifndef __HC32F4A0_FCM_H__
#define __HC32F4A0_FCM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_FCM
 * @{
 */

#if (DDL_FCM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup FCM_Global_Types FCM Global Types
 * @{
 */
/**
 * @brief  FCM Init structure definition
 */
typedef struct
{
    uint16_t u16LowerLimit;     /*!< FCM lower limit value*/

    uint16_t u16UpperLimit;     /*!< FCM upper limit value*/

    uint32_t u32TarClk;         /*!< FCM target clock source selection,         \
                                     @ref FCM_Init_Config for details */

    uint32_t u32TarClkDiv;      /*!< FCM target clock source division selection,\
                                     @ref FCM_Init_Config for details */

    uint32_t u32ExRefClkEn;     /*!< FCM external reference clock function config,  \
                                     @ref FCM_Init_Config for details    */

    uint32_t u32RefClkEdge;     /*!< FCM reference clock trigger edge selection,\
                                     @ref FCM_Init_Config for details    */

    uint32_t u32DigFilter;      /*!< FCM digital filter function config,        \
                                     @ref FCM_Init_Config for details    */

    uint32_t u32RefClk;         /*!< FCM reference clock source selection,      \
                                     @ref FCM_Init_Config for details    */

    uint32_t u32RefClkDiv;      /*!< FCM reference clock source division selection, \
                                     @ref FCM_Init_Config for details */

    uint32_t u32RstEn;          /*!< FCM abnormal reset function config,    \
                                     @ref FCM_Init_Config for details */

    uint32_t u32IntRstSel;      /*!< FCM abnormal detecting behavior selection, \
                                     @ref FCM_Init_Config */

    uint32_t u32IntType;        /*!< FCM interrupt type selection,  \
                                     @ref FCM_Init_Config for details. */
} stc_fcm_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FCM_Global_Macros FCM Global Macros
 * @{
 */

/**
 * @defgroup FCM_Registers_Reset_Value FCM Registers Reset Value
 * @{
 */
#define FCM_REG_RESET_VALUE     (0x00000000UL)
/**
 * @}
 */

/**
 * @defgroup FCM_Init_Config FCM init config
 * @{
 */

/**
 * @brief FCM target clock source selection
 */
#define FCM_TAR_CLK_XTAL        (0x00UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_XTAL32      (0x01UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_HRC         (0x02UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_LRC         (0x03UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_SWDTLRC     (0x04UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_PCLK1       (0x05UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_PLLAP       (0x06UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_MRC         (0x07UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_PLLHP       (0x08UL << FCM_MCCR_MCKS_POS)
#define FCM_TAR_CLK_RTCLRC      (0x09UL << FCM_MCCR_MCKS_POS)

/**
 * @brief FCM target clock division
 */
#define FCM_TAR_CLK_DIV1        (0x00UL)
#define FCM_TAR_CLK_DIV4        (0x01UL)
#define FCM_TAR_CLK_DIV8        (0x02UL)
#define FCM_TAR_CLK_DIV32       (0x03UL)

/**
 * @brief FCM external reference clock function config
 */
#define FCM_EX_REF_OFF          (0x00UL)
#define FCM_EX_REF_ON           (FCM_RCCR_EXREFE)

/**
 * @brief FCM reference clock edge config
 */
#define FCM_REF_CLK_RISING      (0x00UL)
#define FCM_REF_CLK_FALLING     (FCM_RCCR_EDGES_0)
#define FCM_REF_CLK_BOTH        (FCM_RCCR_EDGES_1)

/**
 * @brief FCM digital filter function config
 */
#define FCM_DF_OFF              (0x00UL)
#define FCM_DF_MCKS_DIV1        (FCM_RCCR_DNFS_0)
#define FCM_DF_MCKS_DIV4        (FCM_RCCR_DNFS_1)
#define FCM_DF_MCKS_DIV16       (FCM_RCCR_DNFS)

/**
 * @brief FCM reference clock source selection
 */
#define FCM_REF_CLK_EXINPUT     (0x00UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_XTAL        (0x10UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_XTAL32      (0x11UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_HRC         (0x12UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_LRC         (0x13UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_SWDTLRC     (0x14UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_PCLK1       (0x15UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_PCLKAP      (0x16UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_MRC         (0x17UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_PLLHP       (0x18UL << FCM_RCCR_RCKS_POS)
#define FCM_REF_CLK_RTCLRC      (0x19UL << FCM_RCCR_RCKS_POS)

/**
 * @brief FCM reference clock division
 */
#define FCM_REF_CLK_DIV32       (0x00UL)
#define FCM_REF_CLK_DIV128      (0x01UL)
#define FCM_REF_CLK_DIV1024     (0x02UL)
#define FCM_REF_CLK_DIV8192     (0x03UL)

/**
 * @brief FCM abnormal reset function config
 */
#define FCM_RST_OFF             (0x00UL)
#define FCM_RST_ON              (FCM_RIER_ERRE)

/**
 * @brief FCM abnormal behavior selection
 */
#define FCM_ERR_INT             (0x00UL)
#define FCM_ERR_RESET           (FCM_RIER_ERRINTRS)

/**
 * @brief FCM counter overflow interrupt config
 */
#define FCM_OVF_INT_OFF         (0x00UL)
#define FCM_OVF_INT_ON          (FCM_RIER_OVFIE)

/**
 * @brief FCM measure completed interrupt config
 */
#define FCM_END_INT_OFF         (0x00UL)
#define FCM_END_INT_ON          (FCM_RIER_MENDIE)

/**
 * @brief FCM error interrupt config
 */
#define FCM_ERR_INT_OFF         (0x00UL)
#define FCM_ERR_INT_ON          (FCM_RIER_ERRIE)

/**
 * @brief FCM interrupt mask
 */
#define FCM_INT_MSK             (FCM_OVF_INT_ON | FCM_END_INT_ON | FCM_ERR_INT_ON)
/**
 * @}
 */

/**
 * @defgroup FCM_Flag_Sel FCM status flag selection
 * @{
 */
#define FCM_FLAG_ERR            (FCM_SR_ERRF)
#define FCM_FLAG_END            (FCM_SR_MENDF)
#define FCM_FLAG_OVF            (FCM_SR_OVF)
#define FCM_FLAG_MSK            (FCM_SR_ERRF | FCM_SR_MENDF | FCM_SR_OVF)
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
 * @addtogroup FCM_Global_Functions
 * @{
 */
/**
 * @brief  Set FCM upper limit value.
 * @param  [in] u16Lmt
 * @retval None.
 */
__STATIC_INLINE void FCM_SetUpLimit(uint16_t u16Lmt)
{
    WRITE_REG32(M4_FCM->UVR, u16Lmt);
}

/**
 * @brief  Set FCM lower limit value.
 * @param  u16Lmt
 * @retval None
 */
__STATIC_INLINE void FCM_SetLowLimit(uint16_t u16Lmt)
{
    WRITE_REG32(M4_FCM->LVR, u16Lmt);
}

en_result_t FCM_Init(const stc_fcm_init_t *pstcFcmInit);
en_result_t FCM_StructInit(stc_fcm_init_t *pstcFcmInit);
void FCM_DeInit(void);
uint16_t FCM_GetCounter(void);
void FCM_SetUpLimit(uint16_t u16Lmt);
void FCM_SetLowLimit(uint16_t u16Lmt);
void FCM_SetTarClk(uint32_t u32Tar, uint32_t u32Div);
void FCM_SetRefClk(uint32_t u32Ref, uint32_t u32Div);
en_flag_status_t FCM_GetStatus(uint32_t u32Flag);
void FCM_ClearStatus(uint32_t u32Flag);
void FCM_Cmd(en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* DDL_FCM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_FCM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
