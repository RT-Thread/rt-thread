/**
 *******************************************************************************
 * @file  hc32_ll_dma.c
 * @brief This file provides firmware functions to manage the Direct Memory
 *        Access (DMA).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify DMA_StructInit() default value
   2023-01-15       CDT             Modify API DMA_DeInit and add LLP address assert
   2023-06-30       CDT             Modify typo
                                    Modify blocksize assert, 1024U is valid
                                    Add API DMA_SetDataWidth()
                                    Optimize set blocksize & repeat count process
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_dma.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_DMA DMA
 * @brief Direct Memory Access Driver Library
 * @{
 */

#if (LL_DMA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DMA_Local_Macros DMA Local Macros
 * @{
 */
#define DMA_CH_REG(reg_base, ch)        (*(__IO uint32_t *)((uint32_t)(&(reg_base)) + ((ch) * 0x40UL)))

/**
 * @defgroup DMA_Check_Parameters_Validity DMA Check Parameters Validity
 * @{
 */
/* Parameter valid check for DMA unit. */
#define IS_DMA_UNIT(x)                                                          \
(   ((x) == CM_DMA1)                        ||                                  \
    ((x) == CM_DMA2))

/* Parameter valid check for DMA channel. */
#define IS_DMA_CH(x)                    ((x) <= DMA_CH7)

/* Parameter valid check for DMA multiplex channel. */
#define IS_DMA_MX_CH(x)                                                         \
(   ((x) != 0x00UL)                         &&                                  \
    (((x) | DMA_MX_CH_ALL) == DMA_MX_CH_ALL))

/* Parameter valid check for DMA block size. */
#define IS_DMA_BLOCK_SIZE(x)            ((x) <= 1024U)

/* Parameter valid check for DMA non-sequence transfer count. */
#define IS_DMA_NON_SEQ_TRANS_CNT(x)     ((x) < 4096U)

/* Parameter valid check for DMA non-sequence offset. */
#define IS_DMA_NON_SEQ_OFFSET(x)        ((x) <= ((1UL << 20U) - 1UL))

/* Parameter valid check for DMA LLP function. */
#define IS_DMA_LLP_EN(x)                                                        \
(   ((x) == DMA_LLP_ENABLE)                 ||                                  \
    ((x) == DMA_LLP_DISABLE))

/* Parameter valid check for DMA linked-list-pointer mode. */
#define IS_DMA_LLP_MD(x)                                                        \
(   ((x) == DMA_LLP_RUN)                    ||                                  \
    ((x) == DMA_LLP_WAIT))

/* Parameter valid check for address alignment of DMA linked-list-pointer descriptor  */
#define IS_DMA_LLP_ADDR_ALIGN(x)        IS_ADDR_ALIGN_WORD(x)

/* Parameter valid check for DMA error flag. */
#define IS_DMA_ERR_FLAG(x)                                                      \
(   ((x)!= 0x00000000UL)                    &&                                  \
    (((x)| DMA_FLAG_ERR_MASK) == DMA_FLAG_ERR_MASK))

/* Parameter valid check for DMA transfer flag. */
#define IS_DMA_TRANS_FLAG(x)                                                    \
(   ((x)!= 0x00000000UL)                    &&                                  \
    (((x)| DMA_FLAG_TRANS_MASK) == DMA_FLAG_TRANS_MASK))

/* Parameter valid check for DMA error interrupt. */
#define IS_DMA_ERR_INT(x)                                                       \
(   ((x)!= 0x00000000UL)                    &&                                  \
    (((x)| DMA_INT_ERR_MASK) == DMA_INT_ERR_MASK))

/* Parameter valid check for DMA transfer interrupt. */
#define IS_DMA_TRANS_INT(x)                                                     \
(   ((x)!= 0x00000000UL)                    &&                                  \
    (((x)| DMA_INT_TRANS_MASK) == DMA_INT_TRANS_MASK))

/* Parameter valid check for DMA request status. */
#define IS_DMA_REQ_STAT(x)                                                      \
(   ((x) != 0x00000000UL)                   &&                                  \
    (((x) | DMA_STAT_REQ_MASK) == DMA_STAT_REQ_MASK))

/* Parameter valid check for DMA transfer status. */
#define IS_DMA_TRANS_STAT(x)                                                    \
(   ((x) != 0x00000000UL)                   &&                                  \
    (((x) | DMA_STAT_TRANS_MASK) == DMA_STAT_TRANS_MASK))

/* Parameter valid check for DMA transfer data width. */
#define IS_DMA_DATA_WIDTH(x)                                                    \
(   ((x) == DMA_DATAWIDTH_8BIT)             ||                                  \
    ((x) == DMA_DATAWIDTH_16BIT)            ||                                  \
    ((x) == DMA_DATAWIDTH_32BIT))

/* Parameter valid check for DMA source address mode. */
#define IS_DMA_SADDR_MD(x)                                                      \
(   ((x) == DMA_SRC_ADDR_FIX)               ||                                  \
    ((x) == DMA_SRC_ADDR_INC)               ||                                  \
    ((x) == DMA_SRC_ADDR_DEC))

/* Parameter valid check for DMA destination address mode. */
#define IS_DMA_DADDR_MD(x)                                                      \
(   ((x) == DMA_DEST_ADDR_FIX)              ||                                  \
    ((x) == DMA_DEST_ADDR_INC)              ||                                  \
    ((x) == DMA_DEST_ADDR_DEC))

/* Parameter valid check for DMA repeat mode. */
#define IS_DMA_RPT_MD(x)                                                        \
(   ((x) == DMA_RPT_NONE)                   ||                                  \
    ((x) == DMA_RPT_SRC)                    ||                                  \
    ((x) == DMA_RPT_DEST)                   ||                                  \
    ((x) == DMA_RPT_BOTH))

/* Parameter valid check for DMA non_sequence mode. */
#define IS_DMA_NON_SEQ_MD(x)                                                    \
(   ((x) == DMA_NON_SEQ_NONE)               ||                                  \
    ((x) == DMA_NON_SEQ_SRC)                ||                                  \
    ((x) == DMA_NON_SEQ_DEST)               ||                                  \
    ((x) == DMA_NON_SEQ_BOTH))

/* Parameter valid check for DMA global interrupt function. */
#define IS_DMA_INT_FUNC(x)                                                      \
(   ((x) == DMA_INT_ENABLE)                 ||                                  \
    ((x) == DMA_INT_DISABLE))

/* Parameter valid check for DMA reconfig count mode. */
#define IS_DMA_RC_CNT_MD(x)                                                     \
(   ((x) == DMA_RC_CNT_KEEP)                ||                                  \
    ((x) == DMA_RC_CNT_SRC)                 ||                                  \
    ((x) == DMA_RC_CNT_DEST))

/* Parameter valid check for DMA reconfig destination address mode. */
#define IS_DMA_RC_DA_MD(x)                                                      \
(   ((x) == DMA_RC_DEST_ADDR_KEEP)          ||                                  \
    ((x) == DMA_RC_DEST_ADDR_NS)            ||                                  \
    ((x) == DMA_RC_DEST_ADDR_RPT))

/* Parameter valid check for DMA reconfig source address mode. */
#define IS_DMA_RC_SA_MD(x)                                                      \
(   ((x) == DMA_RC_SRC_ADDR_KEEP)           ||                                  \
    ((x) == DMA_RC_SRC_ADDR_NS)             ||                                  \
    ((x) == DMA_RC_SRC_ADDR_RPT))

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
 * @defgroup DMA_Global_Functions DMA Global Functions
 * @{
 */

/**
 * @brief  DMA global function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_Cmd(CM_DMA_TypeDef *DMAx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Global setting, ENABLE or DISABLE DMA */
    WRITE_REG32(DMAx->EN, enNewState);
}

/**
 * @brief  DMA error IRQ function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32ErrInt DMA error IRQ flag.  @ref DMA_Int_Request_Err_Sel, @ref DMA_Int_Trans_Err_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_ErrIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_ERR_INT(u32ErrInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE == enNewState) {
        SET_REG32_BIT(DMAx->INTMASK0, u32ErrInt);
    } else {
        CLR_REG32_BIT(DMAx->INTMASK0, u32ErrInt);
    }
}

/**
 * @brief  Get DMA error flag.
 * @param  [in] DMAx        DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32Flag     DMA error IRQ flag.  @ref DMA_Flag_Trans_Err_Sel, @ref DMA_Flag_Request_Err_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 * @note   Include transfer error flag & request error flag
 */
en_flag_status_t DMA_GetErrStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_ERR_FLAG(u32Flag));

    return (0U != READ_REG32_BIT(DMAx->INTSTAT0, u32Flag) ? SET : RESET);
}

/**
 * @brief  Clear DMA error flag.
 * @param  [in] DMAx        DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32Flag     DMA error IRQ flag. @ref DMA_Flag_Trans_Err_Sel, @ref DMA_Flag_Request_Err_Sel
 * @retval None
 * @note   Include transfer error flag & request error flag
 */
void DMA_ClearErrStatus(CM_DMA_TypeDef *DMAx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_ERR_FLAG(u32Flag));

    SET_REG32_BIT(DMAx->INTCLR0, u32Flag);
}

/**
 * @brief  DMA transfer IRQ function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32TransCompleteInt DMA transfer complete IRQ flag. @ref DMA_Int_Btc_Sel, @ref DMA_Int_Tc_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_TransCompleteIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32TransCompleteInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_TRANS_INT(u32TransCompleteInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE == enNewState) {
        SET_REG32_BIT(DMAx->INTMASK1, u32TransCompleteInt);
    } else {
        CLR_REG32_BIT(DMAx->INTMASK1, u32TransCompleteInt);
    }
}

/**
 * @brief  Get DMA transfer flag.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32Flag DMA transfer IRQ flag. @ref DMA_Flag_Btc_Sel, @ref DMA_Flag_Tc_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 * @note   Include transfer complete flag & block transfer complete flag
 */
en_flag_status_t DMA_GetTransCompleteStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_DMA_TRANS_FLAG(u32Flag));
    return ((0U != READ_REG32_BIT(DMAx->INTSTAT1, u32Flag)) ? SET : RESET);
}

/**
 * @brief  Clear DMA transfer flag.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32Flag DMA transfer complete flag.  @ref DMA_Flag_Btc_Sel, @ref DMA_Flag_Tc_Sel
 * @retval None
 * @note   Include transfer complete flag & block transfer complete flag
 */
void DMA_ClearTransCompleteStatus(CM_DMA_TypeDef *DMAx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_TRANS_FLAG(u32Flag));

    SET_REG32_BIT(DMAx->INTCLR1, u32Flag);
}

/**
 * @brief  DMA multiplex channel function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8MxCh DMA multiplex channel. @ref DMA_Mx_Channel_selection
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_MxChCmd(CM_DMA_TypeDef *DMAx, uint8_t u8MxCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_MX_CH(u8MxCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        WRITE_REG32(DMAx->CHEN, u8MxCh);
    } else {
        WRITE_REG32(DMAx->CHENCLR, u8MxCh);
    }
}

/**
 * @brief  DMA channel function config.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval int32_t
 */
int32_t DMA_ChCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        WRITE_REG32(DMAx->CHEN, ((1UL << u8Ch) & DMA_CHEN_CHEN));
    } else {
        WRITE_REG32(DMAx->CHENCLR, ((1UL << u8Ch) & DMA_CHENCLR_CHENCLR));
    }

    return LL_OK;
}

/**
 * @brief  Get DMA transfer status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32Status DMA transfer status. @ref DMA_Trans_Status_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t DMA_GetTransStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Status)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_TRANS_STAT(u32Status));

    return ((0U != READ_REG32_BIT(DMAx->CHSTAT, u32Status)) ? SET : RESET);
}

/**
 * @brief  Get DMA request status.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u32Status DMA request status. @ref DMA_Req_Status_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t DMA_GetRequestStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Status)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_REQ_STAT(u32Status));

    return ((0U != READ_REG32_BIT(DMAx->REQSTAT, u32Status)) ? SET : RESET);
}

/**
 * @brief  Config DMA source address.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Addr DMA source address.
 * @retval int32_t
 */
int32_t DMA_SetSrcAddr(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    WRITE_REG32(DMA_CH_REG(DMAx->SAR0, u8Ch), u32Addr);

    return LL_OK;
}

/**
 * @brief  Config DMA destination address.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Addr DMA destination address.
 * @retval int32_t
 */
int32_t DMA_SetDestAddr(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    WRITE_REG32(DMA_CH_REG(DMAx->DAR0, u8Ch), u32Addr);

    return LL_OK;
}

/**
 * @brief  Config DMA transfer count.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u16Count DMA transfer count (0: infinite, 1 ~ 65535).
 * @retval int32_t
 */
int32_t DMA_SetTransCount(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Count)
{
    __IO uint32_t *DTCTLx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    DTCTLx = &DMA_CH_REG(DMAx->DTCTL0, u8Ch);
    MODIFY_REG32(*DTCTLx, DMA_DTCTL_CNT, ((uint32_t)(u16Count) << DMA_DTCTL_CNT_POS));
    return LL_OK;
}

/**
 * @brief  Config DMA block size per transfer.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u16Size DMA block size (range: 0~1024, 0 is for 1024).
 * @retval int32_t
 */
int32_t DMA_SetBlockSize(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size)
{
    __IO uint32_t *DTCTLx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_BLOCK_SIZE(u16Size));

    DTCTLx = &DMA_CH_REG(DMAx->DTCTL0, u8Ch);
    MODIFY_REG32(*DTCTLx, DMA_DTCTL_BLKSIZE, u16Size);

    return LL_OK;
}

/**
 * @brief  Config DMA data width per transfer.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32DataWidth DMA data width. @ref DMA_DataWidth_Sel
 * @retval int32_t
 */
int32_t DMA_SetDataWidth(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32DataWidth)
{
    __IO uint32_t *CHxCTL0;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_DATA_WIDTH(u32DataWidth));

    CHxCTL0 = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
    MODIFY_REG32(*CHxCTL0, DMA_CHCTL_HSIZE, u32DataWidth);

    return LL_OK;
}

/**
 * @brief  Config DMA source repeat size.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u16Size DMA source repeat size (0, 1024: 1024, 1 ~ 1023).
 * @retval int32_t
 */
int32_t DMA_SetSrcRepeatSize(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size)
{
    __IO uint32_t *RPTx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_BLOCK_SIZE(u16Size));

    RPTx = &DMA_CH_REG(DMAx->RPT0, u8Ch);
    MODIFY_REG32(*RPTx, DMA_RPT_SRPT, ((uint32_t)(u16Size) << DMA_RPT_SRPT_POS));

    return LL_OK;
}

/**
 * @brief  Config DMA destination repeat size.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u16Size DMA destination repeat size (0, 1024: 1024, 1 ~ 1023).
 * @retval int32_t
 */
int32_t DMA_SetDestRepeatSize(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size)
{
    __IO uint32_t *RPTx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_BLOCK_SIZE(u16Size));

    RPTx = &DMA_CH_REG(DMAx->RPT0, u8Ch);
    MODIFY_REG32(*RPTx, DMA_RPT_DRPT, ((uint32_t)(u16Size) << DMA_RPT_DRPT_POS));

    return LL_OK;
}

/**
 * @brief  Config DMA source transfer count under non-sequence mode.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Count DMA source transfer count (0, 4096: 4096, 1 ~ 4095).
 * @retval int32_t
 */
int32_t DMA_SetNonSeqSrcCount(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Count)
{
    __IO uint32_t *SNSEQCTLx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_NON_SEQ_TRANS_CNT(u32Count));

    SNSEQCTLx = &DMA_CH_REG(DMAx->SNSEQCTL0, u8Ch);
    MODIFY_REG32(*SNSEQCTLx, DMA_SNSEQCTL_SNSCNT, (u32Count << DMA_SNSEQCTL_SNSCNT_POS));

    return LL_OK;
}

/**
 * @brief  Config DMA destination transfer count under non-sequence mode.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Count DMA destination transfer count (0, 4096: 4096, 1 ~ 4095).
 * @retval int32_t
 */
int32_t DMA_SetNonSeqDestCount(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Count)
{
    __IO uint32_t *DNSEQCTLx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_NON_SEQ_TRANS_CNT(u32Count));

    DNSEQCTLx = &DMA_CH_REG(DMAx->DNSEQCTL0, u8Ch);
    MODIFY_REG32(*DNSEQCTLx, DMA_DNSEQCTL_DNSCNT, (u32Count << DMA_DNSEQCTL_DNSCNT_POS));

    return LL_OK;
}

/**
 * @brief  Config DMA source offset number under non-sequence mode.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Offset DMA source offset (0 ~ 2^20 - 1).
 * @retval int32_t
 */
int32_t DMA_SetNonSeqSrcOffset(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Offset)
{
    __IO uint32_t *SNSEQCTLx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_NON_SEQ_OFFSET(u32Offset));

    SNSEQCTLx = &DMA_CH_REG(DMAx->SNSEQCTL0, u8Ch);
    MODIFY_REG32(*SNSEQCTLx, DMA_SNSEQCTL_SOFFSET, u32Offset);

    return LL_OK;
}

/**
 * @brief  Config DMA destination offset number under non-sequence mode.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Offset DMA destination offset (0 ~ 2^20 - 1).
 * @retval int32_t
 */
int32_t DMA_SetNonSeqDestOffset(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Offset)
{
    __IO uint32_t *DNSEQCTLx;
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_NON_SEQ_OFFSET(u32Offset));

    DNSEQCTLx = &DMA_CH_REG(DMAx->DNSEQCTL0, u8Ch);
    MODIFY_REG32(*DNSEQCTLx, DMA_DNSEQCTL_DOFFSET, u32Offset);

    return LL_OK;
}

/**
 * @brief  De-Initialize DMA channel function.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
  * @retval None
 */
void DMA_DeInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    /* Disable */
    SET_REG32_BIT(DMAx->CHENCLR, DMA_CHENCLR_CHENCLR_0 << u8Ch);

    /* Set default value. */
    WRITE_REG32(DMA_CH_REG(DMAx->SAR0, u8Ch), 0UL);
    WRITE_REG32(DMA_CH_REG(DMAx->DAR0, u8Ch), 0UL);
    CLR_REG32_BIT(DMAx->INTMASK0, (DMA_INTMASK0_MSKTRNERR_0 | DMA_INTMASK0_MSKREQERR_0) << u8Ch);
    CLR_REG32_BIT(DMAx->INTMASK1, (DMA_INTMASK1_MSKTC_0 | DMA_INTMASK1_MSKBTC_0) << u8Ch);
    SET_REG32_BIT(DMAx->INTCLR0, (DMA_INTCLR0_CLRTRNERR_0 | DMA_INTCLR0_CLRREQERR_0) << u8Ch);
    SET_REG32_BIT(DMAx->INTCLR1, (DMA_INTCLR1_CLRTC_0 | DMA_INTCLR1_CLRBTC_0) << u8Ch);

    WRITE_REG32(DMA_CH_REG(DMAx->DTCTL0, u8Ch), 1UL);
    WRITE_REG32(DMA_CH_REG(DMAx->CHCTL0, u8Ch), 0x00001000UL);
    WRITE_REG32(DMA_CH_REG(DMAx->RPT0, u8Ch), 0UL);
    WRITE_REG32(DMA_CH_REG(DMAx->SNSEQCTL0, u8Ch), 0UL);
    WRITE_REG32(DMA_CH_REG(DMAx->DNSEQCTL0, u8Ch), 0UL);
    WRITE_REG32(DMA_CH_REG(DMAx->LLP0, u8Ch), 0UL);

}

/**
 * @brief  Initialize DMA config structure. Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaInit Pointer to a stc_dma_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *         - LL_OK: DMA structure initialize successful
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t DMA_StructInit(stc_dma_init_t *pstcDmaInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDmaInit->u32IntEn       = DMA_INT_DISABLE;
        pstcDmaInit->u32SrcAddr     = 0x00UL;
        pstcDmaInit->u32DestAddr    = 0x00UL;
        pstcDmaInit->u32DataWidth   = DMA_DATAWIDTH_8BIT;
        pstcDmaInit->u32BlockSize   = 0x01UL;
        pstcDmaInit->u32TransCount  = 0x00UL;
        pstcDmaInit->u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
        pstcDmaInit->u32DestAddrInc = DMA_DEST_ADDR_FIX;
    }
    return i32Ret;
}

/**
 * @brief  DMA basic function initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] pstcDmaInit DMA config structure.
 *   @arg  u32IntEn         DMA interrupt ENABLE or DISABLE.
 *   @arg  u32SrcAddr       DMA source address.
 *   @arg  u32DestAddr      DMA destination address.
 *   @arg  u32DataWidth     DMA data width.
 *   @arg  u32BlockSize     DMA block size.
 *   @arg  u32TransCount    DMA transfer count.
 *   @arg  u32SrcAddrInc    DMA source address direction.
 *   @arg  u32DestAddrInc   DMA destination address direction.
 * @retval int32_t:
 *          - LL_OK: DMA basic function initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t DMA_Init(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_init_t *pstcDmaInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *CHCTLx;

    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_DMA_DATA_WIDTH(pstcDmaInit->u32DataWidth));
        DDL_ASSERT(IS_DMA_SADDR_MD(pstcDmaInit->u32SrcAddrInc));
        DDL_ASSERT(IS_DMA_DADDR_MD(pstcDmaInit->u32DestAddrInc));
        DDL_ASSERT(IS_DMA_BLOCK_SIZE(pstcDmaInit->u32BlockSize));
        DDL_ASSERT(IS_DMA_INT_FUNC(pstcDmaInit->u32IntEn));

        WRITE_REG32(DMA_CH_REG(DMAx->SAR0, u8Ch), pstcDmaInit->u32SrcAddr);
        WRITE_REG32(DMA_CH_REG(DMAx->DAR0, u8Ch), pstcDmaInit->u32DestAddr);

        WRITE_REG32(DMA_CH_REG(DMAx->DTCTL0, u8Ch), ((pstcDmaInit->u32BlockSize & DMA_DTCTL_BLKSIZE) | \
                                                     (pstcDmaInit->u32TransCount << DMA_DTCTL_CNT_POS)));

        CHCTLx = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx, (DMA_CHCTL_SINC | DMA_CHCTL_DINC | DMA_CHCTL_HSIZE | DMA_CHCTL_IE),       \
                     (pstcDmaInit->u32IntEn | pstcDmaInit->u32DataWidth | pstcDmaInit->u32SrcAddrInc | \
                      pstcDmaInit->u32DestAddrInc));

    }
    return i32Ret;
}

/**
 * @brief  Initialize DMA repeat mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaRepeatInit Pointer to a stc_dma_repeat_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: DMA repeat mode config structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t DMA_RepeatStructInit(stc_dma_repeat_init_t *pstcDmaRepeatInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaRepeatInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDmaRepeatInit->u32Mode       = DMA_RPT_NONE;
        pstcDmaRepeatInit->u32SrcCount  = 0x00UL;
        pstcDmaRepeatInit->u32DestCount = 0x00UL;
    }
    return i32Ret;
}

/**
 * @brief  DMA repeat mode initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] pstcDmaRepeatInit DMA repeat mode config structure.
 * @note Call this function after DMA_Init();
 */
int32_t DMA_RepeatInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_repeat_init_t *pstcDmaRepeatInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *CHCTLx;

    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaRepeatInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_DMA_RPT_MD(pstcDmaRepeatInit->u32Mode));
        DDL_ASSERT(IS_DMA_BLOCK_SIZE(pstcDmaRepeatInit->u32DestCount));
        DDL_ASSERT(IS_DMA_BLOCK_SIZE(pstcDmaRepeatInit->u32SrcCount));

        CHCTLx = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx, (DMA_CHCTL_SRPTEN | DMA_CHCTL_DRPTEN), pstcDmaRepeatInit->u32Mode);

        WRITE_REG32(DMA_CH_REG(DMAx->RPT0, u8Ch), \
                    ((pstcDmaRepeatInit->u32DestCount << DMA_RPT_DRPT_POS) | pstcDmaRepeatInit->u32SrcCount) & \
                    (DMA_RPT_DRPT | DMA_RPT_SRPT));

    }
    return i32Ret;
}

/**
 * @brief  Initialize DMA non-sequence mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaNonSeqInit Pointer to a stc_dma_nonseq_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: DMA non-sequence mode structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaNonSeqInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDmaNonSeqInit->u32Mode       = DMA_NON_SEQ_NONE;
        pstcDmaNonSeqInit->u32SrcCount   = 0x00UL;
        pstcDmaNonSeqInit->u32SrcOffset  = 0x00UL;
        pstcDmaNonSeqInit->u32DestCount  = 0x00UL;
        pstcDmaNonSeqInit->u32DestOffset = 0x00UL;
    }
    return i32Ret;
}

/**
 * @brief  DMA non-sequence mode initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] pstcDmaNonSeqInit DMA non-sequence mode config structure.
 * @retval int32_t:
 *          - LL_OK: DMA non-sequence function initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 * @note Call this function after DMA_Init();
 */
int32_t DMA_NonSeqInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *CHCTLx;

    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaNonSeqInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_DMA_NON_SEQ_MD(pstcDmaNonSeqInit->u32Mode));

        DDL_ASSERT(IS_DMA_NON_SEQ_TRANS_CNT(pstcDmaNonSeqInit->u32SrcCount));
        DDL_ASSERT(IS_DMA_NON_SEQ_TRANS_CNT(pstcDmaNonSeqInit->u32DestCount));
        DDL_ASSERT(IS_DMA_NON_SEQ_OFFSET(pstcDmaNonSeqInit->u32SrcOffset));
        DDL_ASSERT(IS_DMA_NON_SEQ_OFFSET(pstcDmaNonSeqInit->u32DestOffset));

        CHCTLx = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx, (DMA_CHCTL_SNSEQEN | DMA_CHCTL_DNSEQEN), pstcDmaNonSeqInit->u32Mode);

        WRITE_REG32(DMA_CH_REG(DMAx->SNSEQCTL0, u8Ch), ((pstcDmaNonSeqInit->u32SrcCount << DMA_SNSEQCTL_SNSCNT_POS) | \
                                                        pstcDmaNonSeqInit->u32SrcOffset));
        WRITE_REG32(DMA_CH_REG(DMAx->DNSEQCTL0, u8Ch), ((pstcDmaNonSeqInit->u32DestCount << DMA_DNSEQCTL_DNSCNT_POS) | \
                                                        pstcDmaNonSeqInit->u32DestOffset));

    }
    return i32Ret;
}

/**
 * @brief  Initialize DMA Linked List Pointer (hereafter, LLP) mode config structure.
 *          Fill each pstcDmaInit with default value
 * @param  [in] pstcDmaLlpInit Pointer to a stc_dma_llp_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: DMA LLP mode config structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaLlpInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDmaLlpInit->u32State = DMA_LLP_DISABLE;
        pstcDmaLlpInit->u32Mode  = DMA_LLP_WAIT;
        pstcDmaLlpInit->u32Addr  = 0x00UL;
    }
    return i32Ret;
}

/**
 * @brief  DMA LLP mode initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] pstcDmaLlpInit DMA LLP config structure.
 *   @arg  u32State      DMA LLP ENABLE or DISABLE.
 *   @arg  u32Mode       DMA LLP auto-run or wait request.
 *   @arg  u32Addr       DMA LLP next list pointer address.
 *   @arg  u32AddrSelect DMA LLP address mode.
 * @retval int32_t:
 *          - LL_OK: DMA LLP function initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 * @note Call this function after DMA_Init();
 */
int32_t DMA_LlpInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_llp_init_t *pstcDmaLlpInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *CHCTLx;

    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaLlpInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_DMA_LLP_EN(pstcDmaLlpInit->u32State));
        DDL_ASSERT(IS_DMA_LLP_MD(pstcDmaLlpInit->u32Mode));
        DDL_ASSERT(IS_DMA_LLP_ADDR_ALIGN(pstcDmaLlpInit->u32Addr));

        CHCTLx = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
        MODIFY_REG32(*CHCTLx, (DMA_CHCTL_LLPEN | DMA_CHCTL_LLPRUN), \
                     (pstcDmaLlpInit->u32State | pstcDmaLlpInit->u32Mode));

        WRITE_REG32(DMA_CH_REG(DMAx->LLP0, u8Ch), pstcDmaLlpInit->u32Addr & DMA_LLP_LLP);

    }

    return i32Ret;
}

/**
 * @brief  Config DMA LLP value.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] u32Addr Next link pointer address for DMA LLP mode.
 * @retval None
 */
void DMA_SetLlpAddr(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr)
{

    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_DMA_LLP_ADDR_ALIGN(u32Addr));

    WRITE_REG32(DMA_CH_REG(DMAx->LLP0, u8Ch), (u32Addr & DMA_LLP_LLP));
}

/**
 * @brief  DMA LLP ENABLE or DISABLE.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_LlpCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(DMA_CH_REG(DMAx->CHCTL0, u8Ch), DMA_CHCTL_LLPEN);

    } else {
        CLR_REG32_BIT(DMA_CH_REG(DMAx->CHCTL0, u8Ch), DMA_CHCTL_LLPEN);

    }
}

/**
 * @brief  DMA reconfig function ENABLE or DISABLE.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_ReconfigCmd(CM_DMA_TypeDef *DMAx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(DMAx->RCFGCTL, 1UL);
    } else {
        CLR_REG32_BIT(DMAx->RCFGCTL, 1UL);
    }
}

/**
 * @brief  DMA LLP ENABLE or DISABLE  for reconfig function.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void DMA_ReconfigLlpCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(DMAx->RCFGCTL, DMA_RCFGCTL_RCFGCHS | DMA_RCFGCTL_RCFGLLP, \
                 ((uint32_t)(u8Ch) << DMA_RCFGCTL_RCFGCHS_POS) | ((uint32_t)enNewState << DMA_RCFGCTL_RCFGLLP_POS));
}

/**
 * @brief  Initialize DMA re-config mode config structure.
 *          Fill each pstcDmaRCInit with default value
 * @param  [in] pstcDmaRCInit Pointer to a stc_dma_reconfig_init_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: DMA reconfig mode config structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t DMA_ReconfigStructInit(stc_dma_reconfig_init_t *pstcDmaRCInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcDmaRCInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcDmaRCInit->u32CountMode         = DMA_RC_CNT_KEEP;
        pstcDmaRCInit->u32DestAddrMode      = DMA_RC_DEST_ADDR_KEEP;
        pstcDmaRCInit->u32SrcAddrMode       = DMA_RC_SRC_ADDR_KEEP;
    }
    return i32Ret;
}

/**
 * @brief  DMA reconfig mode initialize.
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @param  [in] pstcDmaRCInit DMA reconfig mode config structure
 *   @arg  u32CountMode         DMA reconfig count mode.
 *   @arg  u32DestAddrMode      DMA reconfig destination address mode.
 *   @arg  u32SrcAddrMode       DMA reconfig source address mode.
 * @retval int32_t:
 *          - LL_OK: DMA reconfig function initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
*/
int32_t DMA_ReconfigInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_reconfig_init_t *pstcDmaRCInit)
{
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    if (NULL == pstcDmaRCInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_DMA_RC_CNT_MD(pstcDmaRCInit->u32CountMode));
        DDL_ASSERT(IS_DMA_RC_DA_MD(pstcDmaRCInit->u32DestAddrMode));
        DDL_ASSERT(IS_DMA_RC_SA_MD(pstcDmaRCInit->u32SrcAddrMode));

        MODIFY_REG32(DMAx->RCFGCTL,                                                                     \
                     (DMA_RCFGCTL_RCFGCHS | DMA_RCFGCTL_SARMD | DMA_RCFGCTL_DARMD | DMA_RCFGCTL_CNTMD), \
                     (pstcDmaRCInit->u32CountMode | pstcDmaRCInit->u32SrcAddrMode |                     \
                      pstcDmaRCInit->u32DestAddrMode | ((uint32_t)(u8Ch) << DMA_RCFGCTL_RCFGCHS_POS)));
    }
    return i32Ret;
}

/**
 * @brief  DMA get current source address
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current source address.
 */
uint32_t DMA_GetSrcAddr(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return READ_REG32(DMA_CH_REG(DMAx->MONSAR0, u8Ch));
}

/**
 * @brief  DMA get current destination address
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current destination address.
 */
uint32_t DMA_GetDestAddr(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return READ_REG32(DMA_CH_REG(DMAx->MONDAR0, u8Ch));
}

/**
 * @brief  DMA get current transfer count
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current transfer count.
 */
uint32_t DMA_GetTransCount(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(DMAx->MONDTCTL0, u8Ch)) >> DMA_DTCTL_CNT_POS) & 0xFFFFUL);
}

/**
 * @brief  DMA get current block size
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current block size.
 */
uint32_t DMA_GetBlockSize(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32_BIT(DMA_CH_REG(DMAx->MONDTCTL0, u8Ch), DMA_DTCTL_BLKSIZE));
}

/**
 * @brief  DMA get current source repeat size
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current source repeat size.
 */
uint32_t DMA_GetSrcRepeatSize(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32_BIT(DMA_CH_REG(DMAx->MONRPT0, u8Ch), DMA_RPT_SRPT));
}

/**
 * @brief  DMA get current destination repeat size
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current destination repeat size.
 */
uint32_t DMA_GetDestRepeatSize(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(DMAx->MONRPT0, u8Ch)) >> DMA_RPT_DRPT_POS) & 0x3FFUL);
}

/**
 * @brief  DMA get current source count in non-sequence mode
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current source count in non-sequence mode.
 */
uint32_t DMA_GetNonSeqSrcCount(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(DMAx->MONSNSEQCTL0, u8Ch)) >> DMA_SNSEQCTLB_SNSCNTB_POS) & 0xFFFUL);
}

/**
 * @brief  DMA get current destination count in non-sequence mode
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA,, x can be 0-1
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current destination count in non-sequence mode.
 */
uint32_t DMA_GetNonSeqDestCount(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return ((READ_REG32(DMA_CH_REG(DMAx->MONDNSEQCTL0, u8Ch)) >> DMA_DNSEQCTL_DNSCNT_POS) & 0xFFFUL);
}

/**
 * @brief  DMA get current source offset in non-sequence mode
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current source offset in non-sequence mode.
 */
uint32_t DMA_GetNonSeqSrcOffset(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32_BIT(DMA_CH_REG(DMAx->MONSNSEQCTL0, u8Ch), DMA_SNSEQCTL_SOFFSET));
}

/**
 * @brief  DMA get current destination offset in non-sequence mode
 * @param  [in] DMAx DMA unit instance.
 *   @arg  CM_DMAx or CM_DMA
 * @param  [in] u8Ch DMA channel. @ref DMA_Channel_selection
 * @retval Current destination offset in non-sequence mode.
 */
uint32_t DMA_GetNonSeqDestOffset(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch)
{
    DDL_ASSERT(IS_DMA_UNIT(DMAx));
    DDL_ASSERT(IS_DMA_CH(u8Ch));

    return (READ_REG32_BIT(DMA_CH_REG(DMAx->MONDNSEQCTL0, u8Ch), DMA_DNSEQCTL_DOFFSET));
}

/**
 * @}
 */

#endif  /* LL_DMA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
