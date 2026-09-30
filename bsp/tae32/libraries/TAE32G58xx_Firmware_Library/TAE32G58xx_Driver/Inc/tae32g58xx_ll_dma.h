/**
  ******************************************************************************
  * @file    tae32g58xx_ll_dma.h
  * @author  MCD Application Team
  * @brief   Header file for DMA LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_DMA_H_
#define _TAE32G58XX_LL_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup DMA_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Constants DMA LL Exported Constants
  * @brief    DMA LL Exported Constants
  * @{
  */

/**
  * @brief DMA block size max
  */
#define LL_DMA_BLOCK_SIZE_MAX       (0xfffU)

/**
  * @brief DMA Source/Destination handshaking interface type cover amend
  */
#define LL_DMA_HS_IFC_COVER_AMEND   (0x1000UL)

/**
  * @brief DMA Source/Destination handshaking interface type multiplex amend
  */
#define LL_DMA_HS_IFC_MUX_AMEND     (0x4000UL)

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Macros DMA LL Exported Macros
  * @brief    DMA LL Exported Macros
  * @{
  */

/**
  * @brief  Source address set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  addr Source address
  * @return None
  */
#define __LL_DMA_SrcAddr_Set(__DMA__, ch, addr)         WRITE_REG((__DMA__)->CH[(ch)].REG.SAR, addr)


/**
  * @brief  Destination address set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  addr Destination address
  * @return None
  */
#define __LL_DMA_DstAddr_Set(__DMA__, ch, addr)         WRITE_REG((__DMA__)->CH[(ch)].REG.DAR, addr)


/**
  * @brief  Block transfer count set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  cnt Block transfer count
  * @return None
  */
#define __LL_DMA_BlockTransCnt_Set(__DMA__, ch, cnt)    \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.DBL, DMA0_DBL_BL_Msk, (((cnt) & 0xfffUL) << DMA0_DBL_BL_Pos))


/**
  * @brief  Destination peripheral bus set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  bus Destination peripheral bus @ref DMA_PeriphBusETypeDef
  * @return None
  */
#define __LL_DMA_DstPeriphBus_Set(__DMA__, ch, bus)     \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_DMS_Msk, (((bus) & 0x1UL) << DMA0_CTR_DMS_Pos))

/**
  * @brief  Source peripheral bus set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  bus Source peripheral bus @ref DMA_PeriphBusETypeDef
  * @return None
  */
#define __LL_DMA_SrcPeriphBus_Set(__DMA__, ch, bus)     \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_SMS_Msk, (((bus) & 0x1UL) << DMA0_CTR_SMS_Pos))

/**
  * @brief  Destination burst length set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  len Destination burst length
  * @return None
  */
#define __LL_DMA_DstBurstLen_Set(__DMA__, ch, len)      \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_DBL_Msk, (((len) & 0x3UL) << DMA0_CTR_DBL_Pos))

/**
  * @brief  Source burst length set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  len Source burst length
  * @return None
  */
#define __LL_DMA_SrcBurstLen_Set(__DMA__, ch, len)      \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_SBL_Msk, (((len) & 0x3UL) << DMA0_CTR_SBL_Pos))

/**
  * @brief  Destination handshake interface set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  ifc Destination handshake interface @ref DMA_HandshakeIfcETypeDef
  * @return None
  */
#define __LL_DMA_DstHandshakeIfc_Set(__DMA__, ch, ifc)  \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_DHF_Msk, (((ifc) & 0x1fUL) << DMA0_CTR_DHF_Pos))

/**
  * @brief  Source handshake interface set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  ifc Source handshake interface @ref DMA_HandshakeIfcETypeDef
  * @return None
  */
#define __LL_DMA_SrcHandshakeIfc_Set(__DMA__, ch, ifc)  \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_SHF_Msk, (((ifc) & 0x1fUL) << DMA0_CTR_SHF_Pos))

/**
  * @brief  Destination transfer width set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  width Destination transfer width @ref DMA_TransWidthETypeDef
  * @return None
  */
#define __LL_DMA_DstTransWidth_Set(__DMA__, ch, width)  \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_DDS_Msk, (((width) & 0x3UL) << DMA0_CTR_DDS_Pos))

/**
  * @brief  Source transfer width set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  width Source transfer width @ref DMA_TransWidthETypeDef
  * @return None
  */
#define __LL_DMA_SrcTransWidth_Set(__DMA__, ch, width)  \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_SDS_Msk, (((width) & 0x3UL) << DMA0_CTR_SDS_Pos))

/**
  * @brief  Source transfer width get
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 8 bits
  * @retval 1 16 bits
  * @retval 2 32 bits
  */
#define __LL_DMA_SrcTransWidth_Get(__DMA__, ch)         \
        READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_SDS_Msk, DMA0_CTR_SDS_Pos)

/**
  * @brief  Transfer Complete Interrupt Enable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransCom_Int_En(__DMA__, ch)           SET_BIT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_CIE_Msk)

/**
  * @brief  Transfer Complete Interrupt Disable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransCom_Int_Dis(__DMA__, ch)          CLEAR_BIT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_CIE_Msk)

/**
  * @brief  Judge is Transfer Complete Interrupt Enable or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 Transfer Complete Interrupt Disable
  * @retval 1 Transfer Complete Interrupt Enable
  */
#define __LL_DMA_IsTransCpltIntEn(__DMA__, ch)          READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_CIE_Msk, DMA0_CTR_CIE_Pos)

/**
  * @brief  Transfer Half Interrupt Enable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransHalf_Int_En(__DMA__, ch)          SET_BIT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_HCIE_Msk)

/**
  * @brief  Transfer Half Interrupt Disable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransHalf_Int_Dis(__DMA__, ch)         CLEAR_BIT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_HCIE_Msk)

/**
  * @brief  Transfer Error Interrupt Enable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransErr_Int_En(__DMA__, ch)           SET_BIT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_EIE_Msk)

/**
  * @brief  Transfer Error Interrupt Disable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransErr_Int_Dis(__DMA__, ch)          CLEAR_BIT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_EIE_Msk)

/**
  * @brief  Destination address mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  mode Destination address mode @ref DMA_AddrModeETypeDef
  * @return None
  */
#define __LL_DMA_DstAddrMode_Set(__DMA__, ch, mode)     \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_DAI_Msk, (((mode) & 0x1UL) << DMA0_CTR_DAI_Pos))

/**
  * @brief  Source address mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  mode Source address mode @ref DMA_AddrModeETypeDef
  * @return None
  */
#define __LL_DMA_SrcAddrMode_Set(__DMA__, ch, mode)     \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_SAI_Msk, (((mode) & 0x1UL) << DMA0_CTR_SAI_Pos))

/**
  * @brief  Transfer type set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  type Transfer type @ref DMA_TransTypeETypeDef
  * @return None
  */
#define __LL_DMA_TransType_Set(__DMA__, ch, type)       \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_TC_Msk, (((type) & 0x3UL) << DMA0_CTR_TC_Pos))

/**
  * @brief  Transfer mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  mode Transfer mode @ref DMA_TransModeETypeDef
  * @return None
  */
#define __LL_DMA_TransMode_Set(__DMA__, ch, mode)       \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_TM_Msk, (((mode) & 0x1UL) << DMA0_CTR_TM_Pos))

/**
  * @brief  Transfer mode get
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 Single
  * @retval 1 Continue
  */
#define __LL_DMA_TransMode_Get(__DMA__, ch)             \
        READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_TM_Msk, DMA0_CTR_TM_Pos)

/**
  * @brief  Channel priority set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @param  pri DMA channel priority
  * @return None
  */
#define __LL_DMA_ChannelPri_Set(__DMA__, ch, pri)       \
        MODIFY_REG((__DMA__)->CH[(ch)].REG.CTR, DMA0_CTR_PRI_Msk, (((pri) & 0x7UL) << DMA0_CTR_PRI_Pos))


/**
  * @brief  Channel Enable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_Ch_En(__DMA__, ch)                     SET_BIT((__DMA__)->CH[(ch)].REG.CER, DMA0_CER_CEN_Msk)

/**
  * @brief  Channel Disable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_Ch_Dis(__DMA__, ch)                    CLEAR_BIT((__DMA__)->CH[(ch)].REG.CER, DMA0_CER_CEN_Msk)

/**
  * @brief  Judge is Channel Enable or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 Channel Disable
  * @retval 1 Channel Enable
  */
#define __LL_DMA_IsChEn(__DMA__, ch)                    READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.CER, DMA0_CER_CEN_Msk, DMA0_CER_CEN_Pos)

/**
  * @brief  Channel Enable Status Get
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 Channel is Disable
  * @retval 1 Channel is Enable
  */
#define __LL_DMA_ChEnSta_Get(__DMA__, ch)               \
        READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.CER, DMA0_CER_CEN_Msk, DMA0_CER_CEN_Pos)


/**
  * @brief  Judge is Channel transfer busy or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 isn't Channel transfer busy
  * @retval 1 is Channel transfer busy
  */
#define __LL_DMA_IsTransBusy(__DMA__, ch)               READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_BUSY_Msk, DMA0_STR_BUSY_Pos)

/**
  * @brief  Judge is Channel transfer complete Interrupt Pending or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 isn't Channel transfer complete Interrupt Pending
  * @retval 1 is Channel transfer complete Interrupt Pending
  */
#define __LL_DMA_IsTransCpltIntPnd(__DMA__, ch)         READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_CS_Msk, DMA0_STR_CS_Pos)

/**
  * @brief  Channel Transfer complete Interrupt Pending clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransCpltIntPnd_Clr(__DMA__, ch)       WRITE_REG((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_CS_Msk)

/**
  * @brief  Judge is Channel transfer half complete Interrupt Pending or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 isn't Channel transfer half complete Interrupt Pending
  * @retval 1 is Channel transfer half complete Interrupt Pending
  */
#define __LL_DMA_IsTransHalfCpltIntPnd(__DMA__, ch)     READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_HS_Msk, DMA0_STR_HS_Pos)

/**
  * @brief  Channel Transfer half complete Interrupt Pending clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransHalfCpltIntPnd_Clr(__DMA__, ch)   WRITE_REG((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_HS_Msk)

/**
  * @brief  Judge is Channel transfer error Interrupt Pending or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 isn't Channel transfer error Interrupt Pending
  * @retval 1 is Channel transfer error Interrupt Pending
  */
#define __LL_DMA_IsTransErrIntPnd(__DMA__, ch)          READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_ES_Msk, DMA0_STR_ES_Pos)

/**
  * @brief  Channel Transfer error Interrupt Pending clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_TransErrIntPnd_Clr(__DMA__, ch)        WRITE_REG((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_ES_Msk)

/**
  * @brief  Channel all transfer Interrupt Pending clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return None
  */
#define __LL_DMA_AllTransIntPnd_Clr(__DMA__, ch)        \
        WRITE_REG((__DMA__)->CH[(ch)].REG.STR, DMA0_STR_CS_Msk | DMA0_STR_HS_Msk | DMA0_STR_ES_Msk)

/**
  * @brief  Channel Transfer Length Get
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @return Transfer Length
  */
#define __LL_DMA_ChTransLen_Get(__DMA__, ch)            \
        READ_BIT_SHIFT((__DMA__)->CH[(ch)].REG.DTL, DMA0_DTL_DTR_Msk, DMA0_DTL_DTR_Pos)

/**
  * @brief  Judge is DMA Channel valid or not
  * @param  ch DMA channel @ref DMA_ChannelETypeDef
  * @retval 0 DMA Channel is invalid
  * @retval 1 DMA Channel is valid
  */
#define __LL_DMA_IsChannelValid(ch)                     ((ch) < DMA_CHANNEL_NUMS)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Types DMA LL Exported Types
  * @brief    DMA LL Exported Types
  * @{
  */

/**
  * @brief DMA Source/Destination Peripheral bus type definition
  */
typedef enum {
    DMA_PERIPH_BUS_AHB_MST1 = 0,    /*!< Peripheral bus AHB Master1 */
    DMA_PERIPH_BUS_AHB_MST2,        /*!< Peripheral bus AHB Master2 */
} DMA_PeriphBusETypeDef;

/**
  * brief DMA transfer type type definition
  */
typedef enum {
    DMA_TRANS_TYPE_M2M = 0,         /*!< Transfer type Memory to Memory         */
    DMA_TRANS_TYPE_M2P,             /*!< Transfer type Memory to Peripheral     */
    DMA_TRANS_TYPE_P2M,             /*!< Transfer type Peripheral to Memory     */
    DMA_TRANS_TYPE_P2P,             /*!< Transfer type Peripheral to Peripheral */
} DMA_TransTypeETypeDef;

/**
  * brief DMA transfer mode type definition
  */
typedef enum {
    DMA_TRANS_MODE_SINGLE = 0,      /*!< Transfer mode Single   */
    DMA_TRANS_MODE_CONTINUE,        /*!< Transfer mode Continue */
} DMA_TransModeETypeDef;

/**
  * @brief DMA Source/Destination burst length type definition
  */
typedef enum {
    DMA_BURST_LEN_1 = 0,            /*!< Burst length 1         */
    DMA_BURST_LEN_4,                /*!< Burst length 4         */
    DMA_BURST_LEN_8,                /*!< Burst length 8         */
    DMA_BURST_LEN_16,               /*!< Burst length 16        */
} DMA_BurstLenETypeDef;

/**
  * @brief DMA Source/Destination address mode type definition
  */
typedef enum {
    DMA_ADDR_MODE_INC = 0,          /*!< Address mode Increase  */
    DMA_ADDR_MODE_FIX,              /*!< Address mode Fixed     */
} DMA_AddrModeETypeDef;

/**
  * @brief DMA Source/Destination transfer width type definition
  */
typedef enum {
    DMA_TRANS_WIDTH_8b = 0,         /*!< Transfer width 8bit   */
    DMA_TRANS_WIDTH_16b,            /*!< Transfer width 16bit  */
    DMA_TRANS_WIDTH_32b,            /*!< Transfer width 32bit  */
} DMA_TransWidthETypeDef;

/**
  * @brief DMA Source/Destination handshaking interface type definition
  */
typedef enum {
    DMA_HANDSHAKE_IFC_MEMORY  = -1,     /*!< Handshaking interface MEMORY   */

    DMA_HANDSHAKE_IFC_I2C0_TX = 0,      /*!< Handshaking interface I2C0_TX  */
    DMA_HANDSHAKE_IFC_I2C0_RX,          /*!< Handshaking interface I2C0_RX  */
    DMA_HANDSHAKE_IFC_I2C1_TX,          /*!< Handshaking interface I2C1_TX  */
    DMA_HANDSHAKE_IFC_I2C1_RX,          /*!< Handshaking interface I2C1_RX  */
    DMA_HANDSHAKE_IFC_I2C2_TX,          /*!< Handshaking interface I2C2_TX  */
    DMA_HANDSHAKE_IFC_I2C2_RX,          /*!< Handshaking interface I2C2_RX  */

    DMA_HANDSHAKE_IFC_UART0_TX = 6,     /*!< Handshaking interface UART0_TX */
    DMA_HANDSHAKE_IFC_UART0_RX,         /*!< Handshaking interface UART0_RX */
    DMA_HANDSHAKE_IFC_UART1_TX,         /*!< Handshaking interface UART1_TX */
    DMA_HANDSHAKE_IFC_UART1_RX,         /*!< Handshaking interface UART1_RX */
    DMA_HANDSHAKE_IFC_UART2_TX,         /*!< Handshaking interface UART2_TX */
    DMA_HANDSHAKE_IFC_UART2_RX,         /*!< Handshaking interface UART2_RX */
    DMA_HANDSHAKE_IFC_UART3_TX,         /*!< Handshaking interface UART3_TX */
    DMA_HANDSHAKE_IFC_UART3_RX,         /*!< Handshaking interface UART3_RX */
    DMA_HANDSHAKE_IFC_UART4_TX,         /*!< Handshaking interface UART4_TX */
    DMA_HANDSHAKE_IFC_UART4_RX,         /*!< Handshaking interface UART4_RX */

    DMA_HANDSHAKE_IFC_SPI0_TX = 16,     /*!< Handshaking interface SPI0_TX  */
    DMA_HANDSHAKE_IFC_SPI0_RX = 17,     /*!< Handshaking interface SPI0_RX  */
    DMA_HANDSHAKE_IFC_SPI1_TX = 18,     /*!< Handshaking interface SPI1_TX  */
    DMA_HANDSHAKE_IFC_SPI1_RX = 19,     /*!< Handshaking interface SPI1_RX  */

    DMA_HANDSHAKE_IFC_XIF_TX  = 20,     /*!< Handshaking interface XIF_TX   */
    DMA_HANDSHAKE_IFC_XIF_RX  = 21,     /*!< Handshaking interface XIF_RX   */

    DMA_HANDSHAKE_IFC_PDM0_RX = 23,     /*!< Handshaking interface PDM0_RX  */
    DMA_HANDSHAKE_IFC_PDM1_RX = 25,     /*!< Handshaking interface PDM1_RX  */
    DMA_HANDSHAKE_IFC_PDM2_RX = 27,     /*!< Handshaking interface PDM2_RX  */
    DMA_HANDSHAKE_IFC_PDM3_RX = 29,     /*!< Handshaking interface PDM3_RX  */

    DMA_HANDSHAKE_IFC_HRPWM_SLV7  = LL_DMA_HS_IFC_COVER_AMEND + 23,   /*!< Handshaking interface HRPWM_SLV7   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV6  = LL_DMA_HS_IFC_COVER_AMEND + 24,   /*!< Handshaking interface HRPWM_SLV6   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV5  = LL_DMA_HS_IFC_COVER_AMEND + 25,   /*!< Handshaking interface HRPWM_SLV5   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV4  = LL_DMA_HS_IFC_COVER_AMEND + 26,   /*!< Handshaking interface HRPWM_SLV4   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV3  = LL_DMA_HS_IFC_COVER_AMEND + 27,   /*!< Handshaking interface HRPWM_SLV3   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV2  = LL_DMA_HS_IFC_COVER_AMEND + 28,   /*!< Handshaking interface HRPWM_SLV2   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV1  = LL_DMA_HS_IFC_COVER_AMEND + 29,   /*!< Handshaking interface HRPWM_SLV1   */
    DMA_HANDSHAKE_IFC_HRPWM_SLV0  = LL_DMA_HS_IFC_COVER_AMEND + 30,   /*!< Handshaking interface HRPWM_SLV0   */
    DMA_HANDSHAKE_IFC_HRPWM_MST   = LL_DMA_HS_IFC_COVER_AMEND + 31,   /*!< Handshaking interface HRPWM_MST    */

    DMA_HANDSHAKE_IFC_MUXA_ADC3    = LL_DMA_HS_IFC_MUX_AMEND + 19,    /*!< Handshaking interface mux to ADC3  */
    DMA_HANDSHAKE_IFC_MUXA_ADC2    = LL_DMA_HS_IFC_MUX_AMEND + 20,    /*!< Handshaking interface mux to ADC2  */
    DMA_HANDSHAKE_IFC_MUXA_ADC1    = LL_DMA_HS_IFC_MUX_AMEND + 21,    /*!< Handshaking interface mux to ADC1  */
    DMA_HANDSHAKE_IFC_MUXA_ADC0    = LL_DMA_HS_IFC_MUX_AMEND + 22,    /*!< Handshaking interface mux to ADC0  */

    DMA_HANDSHAKE_IFC_MUXA_PDM0_RX = LL_DMA_HS_IFC_MUX_AMEND + 23,    /*!< Handshaking interface mux to PDM0_RX   */
    DMA_HANDSHAKE_IFC_MUXA_PDM1_RX = LL_DMA_HS_IFC_MUX_AMEND + 25,    /*!< Handshaking interface mux to PDM1_RX   */
    DMA_HANDSHAKE_IFC_MUXA_PDM2_RX = LL_DMA_HS_IFC_MUX_AMEND + 27,    /*!< Handshaking interface mux to PDM2_RX   */
    DMA_HANDSHAKE_IFC_MUXA_PDM3_RX = LL_DMA_HS_IFC_MUX_AMEND + 29,    /*!< Handshaking interface mux to PDM3_RX   */
} DMA_HandshakeIfcETypeDef;

/**
  * @brief DMA Source/Destination handshaking interface multiplex type definition
  */
typedef enum {
    DMA_HANDSHAKE_IFC_MUX_MEMORY  = -1, /*!< Handshaking interface MEMORY   */

    DMA_HANDSHAKE_IFC_MUX_ADC3    = 19, /*!< Handshaking interface mux to ADC3   */
    DMA_HANDSHAKE_IFC_MUX_ADC2    = 20, /*!< Handshaking interface mux to ADC2   */
    DMA_HANDSHAKE_IFC_MUX_ADC1    = 21, /*!< Handshaking interface mux to ADC1   */
    DMA_HANDSHAKE_IFC_MUX_ADC0    = 22, /*!< Handshaking interface mux to ADC0   */

    DMA_HANDSHAKE_IFC_MUX_PDM0_RX = 23, /*!< Handshaking interface mux to PDM0_RX   */
    DMA_HANDSHAKE_IFC_MUX_PDM1_RX = 25, /*!< Handshaking interface mux to PDM1_RX   */
    DMA_HANDSHAKE_IFC_MUX_PDM2_RX = 27, /*!< Handshaking interface mux to PDM2_RX   */
    DMA_HANDSHAKE_IFC_MUX_PDM3_RX = 29, /*!< Handshaking interface mux to PDM3_RX   */
} DMA_HandshakeIfcMuxETypeDef;

/**
  * @brief DMA channel type definition
  */
typedef enum {
    DMA_CHANNEL_0 = 0,              /*!< DMA Channel 0          */
    DMA_CHANNEL_1,                  /*!< DMA Channel 1          */
    DMA_CHANNEL_2,                  /*!< DMA Channel 2          */
    DMA_CHANNEL_3,                  /*!< DMA Channel 3          */
    DMA_CHANNEL_4,                  /*!< DMA Channel 4          */
    DMA_CHANNEL_5,                  /*!< DMA Channel 5          */
    DMA_CHANNEL_NUMS,               /*!< DMA Channel Numbers    */
    DMA_CHANNEL_INVALID = 0xFF,     /*!< DMA Channel Invalid    */
} DMA_ChannelETypeDef;

/**
  * @brief DMA State type definition
  */
typedef enum {
    DMA_STATE_RESET = 0,            /*!< DMA State Reset: not yet initialized or disabled   */
    DMA_STATE_READY,                /*!< DMA State Ready: initialized and ready for use     */
    DMA_STATE_BUSY,                 /*!< DMA State Busy:  process is ongoing                */
} DMA_StateETypeDef;


/**
  * @brief DMA IRQ callback function type definition
  */
typedef void (*DMA_IRQCallback)(void *arg);

/**
  * @brief DMA LL config type definition
  */
typedef struct __DMA_LLCfgTypeDef {
    DMA_BurstLenETypeDef  src_burst;        /*!< source burst length        */
    DMA_BurstLenETypeDef  dst_burst;        /*!< destination burst length   */
    DMA_PeriphBusETypeDef src_periph_bus;   /*!< source peripheral bus      */
    DMA_PeriphBusETypeDef dst_periph_bus;   /*!< destination peripheral bus */
} DMA_LLCfgTypeDef;


/**
  * @brief DMA user config type definition
  */
typedef struct __DMA_UserCfgTypeDef {
    DMA_TransTypeETypeDef    trans_type;        /*!< Transfer type                                      */
    DMA_TransModeETypeDef    trans_mode;        /*!< Transfer mode                                      */
    DMA_AddrModeETypeDef     src_addr_mode;     /*!< Source address mode                                */
    DMA_AddrModeETypeDef     dst_addr_mode;     /*!< Destination address mode                           */
    DMA_TransWidthETypeDef   src_data_width;    /*!< Source data width                                  */
    DMA_TransWidthETypeDef   dst_data_width;    /*!< Destination data width                             */
    DMA_HandshakeIfcETypeDef src_hs_ifc;        /*!< Source handshake interface                         */
    DMA_HandshakeIfcETypeDef dst_hs_ifc;        /*!< Destination handshake interface                    */

    void *end_arg;                              /*!< Argument of transfer complete callback fucntion    */
    DMA_IRQCallback end_callback;               /*!< Transfer complete callback fucntion                */
    void *err_arg;                              /*!< Argument of transfer error callback fucntion       */
    DMA_IRQCallback err_callback;               /*!< Transfer error callback fucntion                   */
    void *half_arg;                             /*!< Argument of transfer half callback fucntion        */
    DMA_IRQCallback half_callback;              /*!< Transfer half callback fucntion                    */

    DMA_LLCfgTypeDef *ll_cfg;                   /*!< Optional LL Config Pointer                         */

    bool src_hs_ifc_mux_en;                     /*!< Source handshake interface multiplex enable        */
    bool dst_hs_ifc_mux_en;                     /*!< Destination handshake interface multiplex enable   */
    DMA_HandshakeIfcMuxETypeDef src_hs_ifc_mux; /*!< Source handshake interface multiplex               */
    DMA_HandshakeIfcMuxETypeDef dst_hs_ifc_mux; /*!< Destination handshake interface multiplex          */
} DMA_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup DMA_LL_Exported_Functions
  * @{
  */

/** @addtogroup DMA_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_DMA_Init(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, DMA_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_DMA_DeInit(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
/**
  * @}
  */


/** @addtogroup DMA_LL_Exported_Functions_Group2
  * @{
  */
DMA_ChannelETypeDef LL_DMA_ChannelRequest(void);
DMA_ChannelETypeDef LL_DMA_ChReqSpecific(DMA_ChannelETypeDef ch);
void LL_DMA_ChannelRelease(DMA_ChannelETypeDef ch);
/**
  * @}
  */


/** @addtogroup DMA_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_DMA_Start_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                   uint32_t src_addr, uint32_t dst_addr, uint32_t data_len);
LL_StatusETypeDef LL_DMA_Start_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                  uint32_t src_addr, uint32_t dst_addr, uint32_t data_len);
LL_StatusETypeDef LL_DMA_Stop_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
LL_StatusETypeDef LL_DMA_Stop_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
LL_StatusETypeDef LL_DMA_WaitComplete_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, uint32_t timeout);
/**
  * @}
  */


/** @addtogroup DMA_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_DMA_IRQHandler(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
/**
  * @}
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
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_DMA_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

