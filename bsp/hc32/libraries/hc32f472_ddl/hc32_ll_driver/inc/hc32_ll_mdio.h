/**
 *******************************************************************************
 * @file  hc32_ll_mdio.h
 * @brief This file contains all the functions prototypes of the MDIO driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
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
#ifndef __HC32_LL_MDIO_H__
#define __HC32_LL_MDIO_H__

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
 * @addtogroup LL_MDIO
 * @{
 */

#if (LL_MDIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup MDIO_Global_Types MDIO Global Types
 * @{
 */

/**
 * @brief Structure definition of MDIO initialization.
 * @note  The parameter 'u32PhyAddr' is valid when the 'u32PhyAddrMode' is equal to MDIO_PHY_ADDR_MD_SW.
 */
typedef struct {
    uint32_t u32PhyAddrBitWidth;        /*!< Specifies the bit width of the PHY address.
                                             This parameter can be a value of @ref MDIO_PHY_Addr_Bit_Width */
    uint32_t u32PhyAddrMode;            /*!< Specifies the mode of the PHY address.
                                             This parameter can be a value of @ref MDIO_PHY_Addr_Mode */
    uint32_t u32PhyAddr;                /*!< Specifies the value of the PHY address.
                                             This parameter can be a number between 0UL and 0x1FUL */
    uint32_t u32DevAddrMask;            /*!< Specifies the mask of the device address.
                                             This parameter can be a value of @ref MDIO_DEV_Addr_Mask */
    uint32_t u32DevAddr;                /*!< Specifies the value of the device address.
                                             This parameter can be a number between 0UL and 0x1FUL */
} stc_mdio_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MDIO_Global_Macros MDIO Global Macros
 * @{
 */

/**
 * @defgroup MDIO_PHY_Addr_Bit_Width MDIO PHY Addr Bit Width
 * @{
 */
#define MDIO_PHY_ADDR_5BIT              (0UL)                   /* Use 5bits address */
#define MDIO_PHY_ADDR_3BIT              (MDIO_MDCON_MD_PHYB)    /* Use 3bits address */
/**
 * @}
 */

/**
 * @defgroup MDIO_MDC_Detect_Level MDIO MDC Detect Level
 * @{
 */
#define MDIO_MDC_DETECT_LVL_LOW         (0UL)                   /*!< Detect low level  */
#define MDIO_MDC_DETECT_LVL_HIGH        (MDIO_MDCON1_SEL_EDGE)  /*!< Detect high level */
/**
 * @}
 */

/**
 * @defgroup MDIO_DEV_Addr_Mask MDIO Device Addr Mask
 * @{
 */
#define MDIO_DEV_ADDR_MASK_DISABLE      (0UL)                   /*!< Don't mask the result of the device address */
#define MDIO_DEV_ADDR_MASK_ENABLE       (MDIO_MDCON1_MD_MSDEV)  /*!< Masking the result of the device address    */
/**
 * @}
 */

/**
 * @defgroup MDIO_PHY_Addr_Mode MDIO PHY Address Mode
 * @{
 */
#define MDIO_PHY_ADDR_MD_HW             (0UL)                   /*!< Hardware address mode */
#define MDIO_PHY_ADDR_MD_SW             (MDIO_MDPHY_MD_PHYSEL)  /*!< Software address mode */
/**
 * @}
 */

/**
 * @defgroup MDIO_RX_OPERA_CODE MDIO Receive Operation Code
 * @{
 */
#define MDIO_RX_OPERA_ADDR_FRAME        (0UL)                   /*!< Address frame                        */
#define MDIO_RX_OPERA_WR_FRAME          (MDIO_MDFRM_MD_ROP_0)   /*!< Write frame                          */
#define MDIO_RX_OPERA_RD_INC_FRAME      (MDIO_MDFRM_MD_ROP_1)   /*!< Address increase frame after reading */
#define MDIO_RX_OPERA_RD_FRAME          (MDIO_MDFRM_MD_ROP)     /*!< Read frame                           */
/**
 * @}
 */

/**
 * @defgroup MDIO_RX_Convert_Bit MDIO Receive Convert Bit
 * @{
 */
#define MDIO_RX_CONV_WR                 (MDIO_MDFRM_MD_RTA_1)   /*!< Write operation */
/**
 * @}
 */

/**
 * @defgroup MDIO_Interrupt MDIO Interrupt
 * @{
 */
#define MDIO_INT_WR_FRAME_MATCH         (MDIO_MDIEN_MD_WRFIE)   /*<! PHY and device address match interrupts in write frame            */
#define MDIO_INT_ADDR_FRAME_MATCH       (MDIO_MDIEN_MD_ADRFIE)  /*<! PHY and device address match interrupts in address frame          */
#define MDIO_INT_INC_ADDR_FRAME_MATCH   (MDIO_MDIEN_MD_INCFIE)  /*<! PHY and device address match interrupts in increase address frame */
#define MDIO_INT_RD_FRAME_MATCH         (MDIO_MDIEN_MD_RDFIE)   /*<! PHY and device address match interrupts in read frame             */
#define MDIO_INT_DEV_ADDR_MATCH         (MDIO_MDIEN_MD_DEVMIE)  /*<! Device address match interrupt      */
#define MDIO_INT_DEV_ADDR_MISMATCH      (MDIO_MDIEN_MD_DEVNIE)  /*<! Device address mismatch interrupt   */
#define MDIO_INT_PHY_ADDR_MATCH         (MDIO_MDIEN_MD_PHYMIE)  /*<! PHY address match interrupt         */
#define MDIO_INT_PHY_ADDR_MISMATCH      (MDIO_MDIEN_MD_PHYNIE)  /*<! PHY address mismatch interrupt      */
#define MDIO_INT_TA_MISMATCH            (MDIO_MDIEN_MD_TANMIE)  /*<! TA bit mismatch interrupt           */
#define MDIO_INT_MDC_TIMEOUT            (MDIO_MDIEN_MD_TOIE)    /*<! MDC timeout interrupt               */
#define MDIO_INT_DATA_UNF               (MDIO_MDIEN_MD_UDRIE)   /*<! Data send underflow interrupt       */
#define MDIO_INT_DATA_OVF               (MDIO_MDIEN_MD_OVRIE)   /*<! Data receive overflow interrupt     */
#define MDIO_INT_RX_FULL                (MDIO_MDIEN_MD_RBNEIE)  /*<! Data receive buffer full interrupt  */
#define MDIO_INT_ALL                    (MDIO_INT_WR_FRAME_MATCH       | MDIO_INT_ADDR_FRAME_MATCH  | \
                                         MDIO_INT_INC_ADDR_FRAME_MATCH | MDIO_INT_RD_FRAME_MATCH    | \
                                         MDIO_INT_DEV_ADDR_MATCH       | MDIO_INT_DEV_ADDR_MISMATCH | \
                                         MDIO_INT_PHY_ADDR_MATCH       | MDIO_INT_PHY_ADDR_MISMATCH | \
                                         MDIO_INT_TA_MISMATCH          | MDIO_INT_MDC_TIMEOUT       | \
                                         MDIO_INT_DATA_UNF             | MDIO_INT_DATA_OVF          | \
                                         MDIO_INT_RX_FULL)
/**
 * @}
 */

/**
 * @defgroup MDIO_Flag MDIO Flag
 * @{
 */
#define MDIO_FLAG_WR_FRAME_MATCH        (MDIO_MDSTA_MD_WRF)     /*<! PHY and device address match flags in write frame            */
#define MDIO_FLAG_ADDR_FRAME_MATCH      (MDIO_MDSTA_MD_ADRF)    /*<! PHY and device address match flags in address frame          */
#define MDIO_FLAG_INC_ADDR_FRAME_MATCH  (MDIO_MDSTA_MD_INCF)    /*<! PHY and device address match flags in increase address frame */
#define MDIO_FLAG_RD_FRAME_MATCH        (MDIO_MDSTA_MD_RDF)     /*<! PHY and device address match flags in read frame             */
#define MDIO_FLAG_DEV_ADDR_MATCH        (MDIO_MDSTA_MD_DEVM)    /*<! Device address match flag      */
#define MDIO_FLAG_DEV_ADDR_MISMATCH     (MDIO_MDSTA_MD_DEVN)    /*<! Device address mismatch flag   */
#define MDIO_FLAG_PHY_ADDR_MATCH        (MDIO_MDSTA_MD_PHYM)    /*<! PHY address match flag         */
#define MDIO_FLAG_PHY_ADDR_MISMATCH     (MDIO_MDSTA_MD_PHYN)    /*<! PHY address mismatch flag      */
#define MDIO_FLAG_TA_MISMATCH           (MDIO_MDSTA_MD_TANM)    /*<! TA bit mismatch flag           */
#define MDIO_FLAG_MDC_TIMEOUT           (MDIO_MDSTA_MD_TO)      /*<! MDC timeout flag               */
#define MDIO_FLAG_DATA_UNF              (MDIO_MDSTA_MD_UDR)     /*<! Data send underflow flag       */
#define MDIO_FLAG_DATA_OVF              (MDIO_MDSTA_MD_OVR)     /*<! Data receive overflow flag     */
#define MDIO_FLAG_RX_FULL               (MDIO_MDSTA_MD_RBNE)    /*<! Data receive buffer full flag  */
#define MDIO_FLAG_COMM_BUSY             (MDIO_MDSTA_MD_BUSY)    /*<! Communication busy flag        */
#define MDIO_FLAG_ALL                   (MDIO_FLAG_WR_FRAME_MATCH       | MDIO_FLAG_ADDR_FRAME_MATCH  | \
                                         MDIO_FLAG_INC_ADDR_FRAME_MATCH | MDIO_FLAG_RD_FRAME_MATCH    | \
                                         MDIO_FLAG_DEV_ADDR_MATCH       | MDIO_FLAG_DEV_ADDR_MISMATCH | \
                                         MDIO_FLAG_PHY_ADDR_MATCH       | MDIO_FLAG_PHY_ADDR_MISMATCH | \
                                         MDIO_FLAG_TA_MISMATCH          | MDIO_FLAG_MDC_TIMEOUT       | \
                                         MDIO_FLAG_DATA_UNF             | MDIO_FLAG_DATA_OVF          | \
                                         MDIO_FLAG_RX_FULL              | MDIO_FLAG_COMM_BUSY)
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
 * @addtogroup MDIO_Global_Functions
 * @{
 */
/* Initialization and configuration functions */
int32_t MDIO_DeInit(CM_MDIO_TypeDef *MDIOx);
int32_t MDIO_Init(CM_MDIO_TypeDef *MDIOx, const stc_mdio_init_t *pstcMdioInit);
int32_t MDIO_StructInit(stc_mdio_init_t *pstcMdioInit);
int32_t MDIO_Reset(CM_MDIO_TypeDef *MDIOx);
void MDIO_SetDevAddrMask(CM_MDIO_TypeDef *MDIOx, uint32_t u32Mask);
uint32_t MDIO_ReadData(const CM_MDIO_TypeDef *MDIOx);
uint32_t MDIO_ReadAddr(const CM_MDIO_TypeDef *MDIOx);
void MDIO_WriteData(CM_MDIO_TypeDef *MDIOx, uint32_t u32Data);
void MDIO_SetDevAddr(CM_MDIO_TypeDef *MDIOx, uint32_t u32Addr);
void MDIO_SetPhyAddr(CM_MDIO_TypeDef *MDIOx, uint32_t u32Addr);
uint32_t MDIO_GetPhyAddr(CM_MDIO_TypeDef *MDIOx, uint32_t u32Mode);
void MDIO_MdcTimeoutConfig(CM_MDIO_TypeDef *MDIOx, uint32_t u32Level, uint32_t u32Time);
void MDIO_MdcTimeoutCmd(CM_MDIO_TypeDef *MDIOx, en_functional_state_t enNewState);
void MDIO_Cmd(CM_MDIO_TypeDef *MDIOx, en_functional_state_t enNewState);

/* Get receive frame information functions */
uint32_t MDIO_GetReceiveOperaCode(CM_MDIO_TypeDef *MDIOx);
uint32_t MDIO_GetReceivePhyAddr(CM_MDIO_TypeDef *MDIOx);
uint32_t MDIO_GetReceiveDevAddr(CM_MDIO_TypeDef *MDIOx);
uint32_t MDIO_GetReceiveConvertBit(CM_MDIO_TypeDef *MDIOx);

/* Interrupt and flag management functions */
void MDIO_IntCmd(CM_MDIO_TypeDef *MDIOx, uint32_t u32IntType, en_functional_state_t enNewState);
en_flag_status_t MDIO_GetStatus(const CM_MDIO_TypeDef *MDIOx, uint32_t u32Flag);
uint32_t MDIO_GetAllStatus(const CM_MDIO_TypeDef *MDIOx);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_MDIO_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
