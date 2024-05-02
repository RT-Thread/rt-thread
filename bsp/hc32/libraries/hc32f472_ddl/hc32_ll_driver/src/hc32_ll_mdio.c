/**
 *******************************************************************************
 * @file  hc32_ll_mdio.c
 * @brief This file provides firmware functions to manage the MDIO Serial Bus
 *        Interface(MDIO).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Optimized MDIO_DeInit function
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
#include "hc32_ll_mdio.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_MDIO MDIO
 * @brief MDIO Serial Bus Interface
 * @{
 */

#if (LL_MDIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MDIO_Local_Macros MDIO Local Macros
 * @{
 */

/* Wait timeout */
#define MDIO_RST_TIMEOUT                (0x1000UL)

/**
 * @defgroup MDIO_Check_Parameters_Validity MDIO Check Parameters Validity
 * @{
 */
#define IS_MDIO_UNIT(x)                         ((x) == CM_MDIO)

#define IS_MDIO_PHY_ADDR_BIT_WIDTH(x)                                          \
(   ((x) == MDIO_PHY_ADDR_5BIT)                 ||                             \
    ((x) == MDIO_PHY_ADDR_3BIT))

#define IS_MDIO_PHY_ADDR_MD(x)                                                 \
(   ((x) == MDIO_PHY_ADDR_MD_HW)                ||                             \
    ((x) == MDIO_PHY_ADDR_MD_SW))

#define IS_MDIO_PHY_ADDR(x)                     ((x) <= 0x1FUL)

#define IS_MDIO_DEV_ADDR_MASK(x)                                               \
(   ((x) == MDIO_DEV_ADDR_MASK_DISABLE)         ||                             \
    ((x) == MDIO_DEV_ADDR_MASK_ENABLE))

#define IS_MDIO_DEV_ADDR(x)                     ((x) <= 0x1FUL)

#define IS_MDIO_MDC_DETECT_LVL(x)                                              \
(   ((x) == MDIO_MDC_DETECT_LVL_LOW)            ||                             \
    ((x) == MDIO_MDC_DETECT_LVL_HIGH))

#define IS_MDIO_WR_DATA(x)                      ((x) <= 0xFFFFUL)

#define IS_MDIO_MDC_TIMEOUT(x)                  ((x) <= 0xFFFFUL)

#define IS_MDIO_INT(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | MDIO_INT_ALL) == MDIO_INT_ALL))

#define IS_MDIO_FLAG(x)                                                        \
(   ((x) != 0UL)                                &&                             \
    (((x) | MDIO_FLAG_ALL) == MDIO_FLAG_ALL))

#define IS_MDIO_PWC_UNLOCKED()          ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/* MDIO reset timeout */
#define MDIO_RMU_TIMEOUT                (100UL)
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
 * @defgroup MDIO_Local_Func MDIO Local Functions
 * @{
 */

/**
 * @brief  De-Initialize MDIO.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t MDIO_DeInit(CM_MDIO_TypeDef *MDIOx)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;

    /* Check parameters */
    DDL_ASSERT(IS_MDIO_PWC_UNLOCKED());

    CLR_REG32_BIT(CM_RMU->FRST1, RMU_FRST1_MDIO);
    /* Ensure reset procedure is completed */
    while (RMU_FRST1_MDIO != READ_REG32_BIT(CM_RMU->FRST1, RMU_FRST1_MDIO)) {
        u32TimeOut++;
        if (u32TimeOut > MDIO_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Initialize MDIO.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] pstcMdioInit            Pointer to a @ref stc_mdio_init_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMdioInit is NULL
 */
int32_t MDIO_Init(CM_MDIO_TypeDef *MDIOx, const stc_mdio_init_t *pstcMdioInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMdioInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
        DDL_ASSERT(IS_MDIO_PHY_ADDR_BIT_WIDTH(pstcMdioInit->u32PhyAddrBitWidth));
        DDL_ASSERT(IS_MDIO_PHY_ADDR_MD(pstcMdioInit->u32PhyAddrMode));
        DDL_ASSERT(IS_MDIO_PHY_ADDR(pstcMdioInit->u32PhyAddr));
        DDL_ASSERT(IS_MDIO_DEV_ADDR_MASK(pstcMdioInit->u32DevAddrMask));
        DDL_ASSERT(IS_MDIO_DEV_ADDR(pstcMdioInit->u32DevAddr));

        MODIFY_REG32(MDIOx->MDCON, MDIO_MDCON_MD_PHYB, pstcMdioInit->u32PhyAddrBitWidth);
        MODIFY_REG32(MDIOx->MDCON1, MDIO_MDCON1_MD_MSDEV, pstcMdioInit->u32DevAddrMask);
        if (MDIO_PHY_ADDR_MD_SW == pstcMdioInit->u32PhyAddrMode) {
            MODIFY_REG32(MDIOx->MDPHY, (MDIO_MDPHY_MD_PHYSEL | MDIO_MDPHY_MD_DEVADD | MDIO_MDPHY_MD_PHYSW),
                         (pstcMdioInit->u32PhyAddrMode | (pstcMdioInit->u32DevAddr << MDIO_MDPHY_MD_DEVADD_POS) |
                          pstcMdioInit->u32PhyAddr));
        } else {
            MODIFY_REG32(MDIOx->MDPHY, (MDIO_MDPHY_MD_PHYSEL | MDIO_MDPHY_MD_DEVADD),
                         (pstcMdioInit->u32PhyAddrMode | (pstcMdioInit->u32DevAddr << MDIO_MDPHY_MD_DEVADD_POS)));
        }

    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_mdio_init_t to default values.
 * @param  [out] pstcMdioInit           Pointer to a @ref stc_mdio_init_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: pstcMdioInit is NULL
 */
int32_t MDIO_StructInit(stc_mdio_init_t *pstcMdioInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMdioInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcMdioInit->u32PhyAddrBitWidth    = MDIO_PHY_ADDR_5BIT;
        pstcMdioInit->u32PhyAddrMode        = MDIO_PHY_ADDR_MD_HW;
        pstcMdioInit->u32PhyAddr            = 0UL;
        pstcMdioInit->u32DevAddrMask        = MDIO_DEV_ADDR_MASK_DISABLE;
        pstcMdioInit->u32DevAddr            = 1UL;
    }

    return i32Ret;
}

/**
 * @brief  Reset the MDIO.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval int32_t:
 *           - LL_OK: Software reset success
 *           - LL_ERR_TIMEOUT: Reset timeout
 */
int32_t MDIO_Reset(CM_MDIO_TypeDef *MDIOx)
{
    __IO uint32_t u32Count = MDIO_RST_TIMEOUT;
    int32_t i32Ret = LL_OK;

    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    SET_REG32_BIT(MDIOx->MDCON, MDIO_MDCON_MD_RST);
    while (0UL != READ_REG32_BIT(MDIOx->MDCON, MDIO_MDCON_MD_RST)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    return i32Ret;
}

/**
 * @brief  Set the mask of the device address.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Mask                 Select the mask.
 *         This parameter can be one of the following values:
 *           @arg MDIO_DEV_ADDR_MASK_DISABLE:   Don't mask the result of the device address
 *           @arg MDIO_DEV_ADDR_MASK_ENABLE:    Masking the result of the device address
 * @retval None
 */
void MDIO_SetDevAddrMask(CM_MDIO_TypeDef *MDIOx, uint32_t u32Mask)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_DEV_ADDR_MASK(u32Mask));

    if (MDIO_DEV_ADDR_MASK_ENABLE == u32Mask) {
        SET_REG32_BIT(MDIOx->MDCON1, MDIO_MDCON1_MD_MSDEV);
    } else {
        CLR_REG32_BIT(MDIOx->MDCON1, MDIO_MDCON1_MD_MSDEV);
    }
}

/**
 * @brief  Read data of data frame.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     Receive data.
 */
uint32_t MDIO_ReadData(const CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return READ_REG32(MDIOx->MDRXD);
}

/**
 * @brief  Read data of address frame.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     Receive data.
 */
uint32_t MDIO_ReadAddr(const CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return READ_REG32(MDIOx->MDADR);
}

/**
 * @brief  Write data.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Data                 Send data.
 *         This parameter can be a number between 0UL and 0xFFFFUL.
 * @retval None
 */
void MDIO_WriteData(CM_MDIO_TypeDef *MDIOx, uint32_t u32Data)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_WR_DATA(u32Data));

    WRITE_REG32(MDIOx->MDTXD, u32Data);
}

/**
 * @brief  Set device address.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Addr                 Device address value.
 *         This parameter can be a number between 0UL and 0x1FUL.
 * @retval None
 */
void MDIO_SetDevAddr(CM_MDIO_TypeDef *MDIOx, uint32_t u32Addr)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_DEV_ADDR(u32Addr));

    MODIFY_REG32(MDIOx->MDPHY, MDIO_MDPHY_MD_DEVADD, (u32Addr << MDIO_MDPHY_MD_DEVADD_POS));
}

/**
 * @brief  Set PHY address.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Addr                 Phy address value.
 *         This parameter can be a number between 0UL and 0x1FUL.
 * @retval None
 */
void MDIO_SetPhyAddr(CM_MDIO_TypeDef *MDIOx, uint32_t u32Addr)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_PHY_ADDR(u32Addr));

    MODIFY_REG32(MDIOx->MDPHY, MDIO_MDPHY_MD_PHYSW, u32Addr);
}

/**
 * @brief  Get PHY address.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Mode                 Phy address mode.
 *         This parameter can be one of the following values:
 *           @arg MDIO_PHY_ADDR_MD_HW:  Hardware address mode
 *           @arg MDIO_PHY_ADDR_MD_SW:  Software address mode
 * @retval uint32_t                     Phy address value.
 */
uint32_t MDIO_GetPhyAddr(CM_MDIO_TypeDef *MDIOx, uint32_t u32Mode)
{
    uint32_t u32Addr;

    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_PHY_ADDR_MD(u32Mode));

    if (MDIO_PHY_ADDR_MD_SW == u32Mode) {
        u32Addr = READ_REG32_BIT(MDIOx->MDPHY, MDIO_MDPHY_MD_PHYSW);
    } else {
        u32Addr = READ_REG32_BIT(MDIOx->MDPIN, MDIO_MDPIN_MD_PIN);
    }

    return u32Addr;
}

/**
 * @brief  Configure the MDC Timeout.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Level                Select the detect level of the MDC.
 *         This parameter can be one of the following values:
 *           @arg MDIO_MDC_DETECT_LVL_LOW:  Detect low level
 *           @arg MDIO_MDC_DETECT_LVL_HIGH: Detect high level
 * @param  [in] u32Time                 Timeout time.
 *         This parameter can be a number between 0UL and 0xFFFFUL.
 * @retval None
 */
void MDIO_MdcTimeoutConfig(CM_MDIO_TypeDef *MDIOx, uint32_t u32Level, uint32_t u32Time)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_MDC_DETECT_LVL(u32Level));
    DDL_ASSERT(IS_MDIO_MDC_TIMEOUT(u32Time));

    MODIFY_REG32(MDIOx->MDCON1, MDIO_MDCON1_SEL_EDGE, u32Level);
    MODIFY_REG32(MDIOx->MDTO, MDIO_MDTO_TOCNT, u32Time);
}

/**
 * @brief  Enable or disable the MDC timeout.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MDIO_MdcTimeoutCmd(CM_MDIO_TypeDef *MDIOx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG32_BIT(MDIOx->MDTO, MDIO_MDTO_TOEN);
    } else {
        CLR_REG32_BIT(MDIOx->MDTO, MDIO_MDTO_TOEN);
    }
}

/**
 * @brief  Enable or disable the MDIO.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MDIO_Cmd(CM_MDIO_TypeDef *MDIOx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG32_BIT(MDIOx->MDCON1, MDIO_MDCON1_MD_EN);
    } else {
        CLR_REG32_BIT(MDIOx->MDCON1, MDIO_MDCON1_MD_EN);
    }
}

/**
 * @brief  Get the operation code in receive frame.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     Operation code.
 */
uint32_t MDIO_GetReceiveOperaCode(CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return READ_REG32_BIT(MDIOx->MDFRM, MDIO_MDFRM_MD_ROP);
}

/**
 * @brief  Get the phy address in receive frame.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     Phy address.
 */
uint32_t MDIO_GetReceivePhyAddr(CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return (READ_REG32_BIT(MDIOx->MDFRM, MDIO_MDFRM_MD_RPHYAD) >> MDIO_MDFRM_MD_RPHYAD_POS);
}

/**
 * @brief  Get the device address in receive frame.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     Device address.
 */
uint32_t MDIO_GetReceiveDevAddr(CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return (READ_REG32_BIT(MDIOx->MDFRM, MDIO_MDFRM_MD_RDEVAD) >> MDIO_MDFRM_MD_RDEVAD_POS);
}

/**
 * @brief  Get the convert bit in receive frame.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     Convert bit.
 */
uint32_t MDIO_GetReceiveConvertBit(CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return READ_REG32_BIT(MDIOx->MDFRM, MDIO_MDFRM_MD_RTA);
}

/**
 * @brief  Enable or disable the specified MDIO interrupt.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32IntType              MDIO interrupt type
 *         This parameter can be any combination value of the following values:
 *           @arg @ref MDIO_Interrupt
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MDIO_IntCmd(CM_MDIO_TypeDef *MDIOx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));
    DDL_ASSERT(IS_MDIO_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(MDIOx->MDIEN, u32IntType);
    } else {
        CLR_REG32_BIT(MDIOx->MDIEN, u32IntType);
    }
}

/**
 * @brief  Get MDIO status.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @param  [in] u32Flag                 MDIO flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg MDIO_FLAG_WR_FRAME_MATCH:         PHY and device address match flags in write frame
 *           @arg MDIO_FLAG_ADDR_FRAME_MATCH:       PHY and device address match flags in address frame
 *           @arg MDIO_FLAG_INC_ADDR_FRAME_MATCH:   PHY and device address match flags in increase address frame
 *           @arg MDIO_FLAG_RD_FRAME_MATCH:         PHY and device address match flags in read frame
 *           @arg MDIO_FLAG_DEV_ADDR_MATCH:         Device address match flag
 *           @arg MDIO_FLAG_DEV_ADDR_MISMATCH:      Device address mismatch flag
 *           @arg MDIO_FLAG_PHY_ADDR_MATCH:         PHY address match flag
 *           @arg MDIO_FLAG_PHY_ADDR_MISMATCH:      PHY address mismatch flag
 *           @arg MDIO_FLAG_TA_MISMATCH:            TA bit mismatch flag
 *           @arg MDIO_FLAG_MDC_TIMEOUT:            MDC timeout flag
 *           @arg MDIO_FLAG_DATA_UNF:               Data send underflow flag
 *           @arg MDIO_FLAG_DATA_OVF:               Data receive overflow flag
 *           @arg MDIO_FLAG_RX_FULL:                Data receive buffer full flag
 *           @arg MDIO_FLAG_COMM_BUSY:              Communication busy flag
 *           @arg MDIO_FLAG_ALL:                    All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t MDIO_GetStatus(const CM_MDIO_TypeDef *MDIOx, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_MDIO_FLAG(u32Flag));

    if (0UL != READ_REG32_BIT(MDIOx->MDSTA, u32Flag)) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Get all status of the MDIO.
 * @param  [in] MDIOx                   Pointer to MDIO unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_MDIO or CM_MDIOx:  MDIO unit instance
 * @retval uint32_t                     MDIO status value.
 */
uint32_t MDIO_GetAllStatus(const CM_MDIO_TypeDef *MDIOx)
{
    /* Check parameters */
    DDL_ASSERT(IS_MDIO_UNIT(MDIOx));

    return READ_REG32(MDIOx->MDSTA);
}

/**
 * @}
 */

#endif /* LL_MDIO_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
