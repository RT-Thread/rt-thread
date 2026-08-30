/**
  ******************************************************************************
  * @file    tae32g58xx_ll_uart.h
  * @author  MCD Application Team
  * @brief   Header file for UART LL module
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
#ifndef _TAE32G58XX_LL_UART_H_
#define _TAE32G58XX_LL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"
#ifdef LL_DMA_MODULE_ENABLED
#include "tae32g58xx_ll_dma.h"
#endif


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup UART_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Macros UART LL Exported Macros
  * @brief    UART LL Exported Macros
  * @{
  */

/**
  * @brief  Auto Baud Rate Mode Set
  * @note   Can only be activated after set non-zero baud rate
  * @param  __UART__ Specifies UART peripheral
  * @param  mode Auto Baud Rate Mode @ref UART_AutoBaudRateModeETypeDef
  * @return None
  */
#define __LL_UART_AutoBaudRateMode_Set(__UART__, mode)      \
        MODIFY_REG((__UART__)->CR0, UART0_CR0_ABRM_Msk, (((mode) & 0x3UL) << UART0_CR0_ABRM_Pos))

/**
  * @brief  Auto Baud Rate Mode Set
  * @param  __UART__ Specifies UART peripheral
  * @return Auto Baud Rate Mode @ref UART_AutoBaudRateModeETypeDef
  */
#define __LL_UART_AutoBaudRateMode_Get(__UART__)            \
        READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_ABRM_Msk, UART0_CR0_ABRM_Pos)

/**
  * @brief  RX OVERDIS Mode Enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxOverdisMode_En(__UART__)                SET_BIT((__UART__)->CR0, UART0_CR0_OVDIS_Msk)

/**
  * @brief  RX OVERDIS Mode Disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxOverdisMode_Dis(__UART__)               CLEAR_BIT((__UART__)->CR0, UART0_CR0_OVDIS_Msk)

/**
  * @brief  Judge is RX OVERDIS Mode Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 RX OVERDIS Mode is Disable
  * @retval 1 RX OVERDIS Mode is Enable
  */
#define __LL_UART_IsRxOverdisModeEn(__UART__)               READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_OVDIS_Msk, UART0_CR0_OVDIS_Pos)

/**
  * @brief  LOOPBACK Mode Enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_LoopbackMode_En(__UART__)                 SET_BIT((__UART__)->CR0, UART0_CR0_LOOP_Msk)

/**
  * @brief  LOOPBACK Mode Disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_LoopbackMode_Dis(__UART__)                CLEAR_BIT((__UART__)->CR0, UART0_CR0_LOOP_Msk)

/**
  * @brief  Judge is LOOPBACK Mode Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 LOOPBACK Mode is Disable
  * @retval 1 LOOPBACK Mode is Enable
  */
#define __LL_UART_IsLoopbackModeEn(__UART__)                READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_LOOP_Msk, UART0_CR0_LOOP_Pos)

/**
  * @brief  ONEBIT Mode Enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_OneBitMode_En(__UART__)                   SET_BIT((__UART__)->CR0, UART0_CR0_ONEBIT_Msk)

/**
  * @brief  ONEBIT Mode Disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_OneBitMode_Dis(__UART__)                  CLEAR_BIT((__UART__)->CR0, UART0_CR0_ONEBIT_Msk)

/**
  * @brief  Judge is ONEBIT Mode Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 ONEBIT Mode is Disable
  * @retval 1 ONEBIT Mode is Enable
  */
#define __LL_UART_IsOneBitModeEn(__UART__)                  READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_ONEBIT_Msk, UART0_CR0_ONEBIT_Pos)

/**
  * @brief  RTO Mode FNE + RxIDEL
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RTOModeFNERxIdel_Set(__UART__)            CLEAR_BIT((__UART__)->CR0, UART0_CR0_RTOM_Msk)

/**
  * @brief  RTO Mode RxIDEL
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RTOModeRxIdel_Set(__UART__)               SET_BIT((__UART__)->CR0, UART0_CR0_RTOM_Msk)

/**
  * @brief  RTO Mode Set
  * @note   Can only be config in UART Disable state
  * @param  mode @ref UART_RTOModeETypeDef
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RTOMode_Set(__UART__, mode)               MODIFY_REG((__UART__)->CR0, UART0_CR0_RTOM_Msk, (mode & 0x01UL) << UART0_CR0_RTOM_Pos)

/**
  * @brief  RTO Mode Get
  * @param  __UART__ Specifies UART peripheral
  * @return RTO Mode @ref UART_RTOModeETypeDef
  */
#define __LL_UART_RTOMode_Get(__UART__)                     READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_RTOM_Msk, UART0_CR0_RTOM_Pos)

/**
  * @brief  Non-FIFO Mode Enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_NonFIFOMode_En(__UART__)                  SET_BIT((__UART__)->CR0, UART0_CR0_NFE_Msk)

/**
  * @brief  Non-FIFO Mode Disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_NonFIFOMode_Dis(__UART__)                 CLEAR_BIT((__UART__)->CR0, UART0_CR0_NFE_Msk)

/**
  * @brief  Oversample mode Set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  mode Oversample mode
  * @return None
  */
#define __LL_UART_OverSampleMode_Set(__UART__, mode)        \
        MODIFY_REG((__UART__)->CR0, UART0_CR0_OVER8_Msk, (((mode) & 0x1UL) << UART0_CR0_OVER8_Pos))

/**
  * @brief  Judge Over Sample is X8 or not
  * @param  __UART__ Specifies UART peripheral
  * @return Oversample mode @ref UART_OverSampETypeDef
  */
#define __LL_UART_IsOverSampleX8(__UART__)        \
        READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_OVER8_Msk, UART0_CR0_OVER8_Pos)


/**
  * @brief  Rx Timeout Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxTimeout_En(__UART__)                    SET_BIT((__UART__)->CR0, UART0_CR0_RTOE_Msk)

/**
  * @brief  Rx Timeout Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxTimeout_Dis(__UART__)                   CLEAR_BIT((__UART__)->CR0, UART0_CR0_RTOE_Msk)

/**
  * @brief  TX Pin Polarity Set
  * @param  __UART__ Specifies UART peripheral
  * @param  pol TX Pin Polarity @ref UART_PinPolETypeDef
  * @return None
  */
#define __LL_UART_TxPinPol_Set(__UART__, pol)               \
        MODIFY_REG((__UART__)->CR0, UART0_CR0_TPOL_Msk, (((pol) & 0x1UL) << UART0_CR0_TPOL_Pos))

/**
  * @brief  RX Pin Polarity Set
  * @param  __UART__ Specifies UART peripheral
  * @param  pol RX Pin Polarity @ref UART_PinPolETypeDef
  * @return None
  */
#define __LL_UART_RxPinPol_Set(__UART__, pol)               \
        MODIFY_REG((__UART__)->CR0, UART0_CR0_RPOL_Msk, (((pol) & 0x1UL) << UART0_CR0_RPOL_Pos))

/**
  * @brief  TX and RX Pin Swap Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxRxPinSwap_En(__UART__)                  SET_BIT((__UART__)->CR0, UART0_CR0_SWAP_Msk)

/**
  * @brief  TX and RX Pin Swap Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxRxPinSwap_Dis(__UART__)                 CLEAR_BIT((__UART__)->CR0, UART0_CR0_SWAP_Msk)

/**
  * @brief  One Wire Enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_OneWire_En(__UART__)                      SET_BIT((__UART__)->CR0, UART0_CR0_OWE_Msk)

/**
  * @brief  One Wire Disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_OneWire_Dis(__UART__)                     CLEAR_BIT((__UART__)->CR0, UART0_CR0_OWE_Msk)

/**
  * @brief  TX DMA Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxDMA_En(__UART__)                        SET_BIT((__UART__)->CR0, UART0_CR0_DTE_Msk)

/**
  * @brief  TX DMA Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxDMA_Dis(__UART__)                       CLEAR_BIT((__UART__)->CR0, UART0_CR0_DTE_Msk)

/**
  * @brief  RX DMA Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxDMA_En(__UART__)                        SET_BIT((__UART__)->CR0, UART0_CR0_DRE_Msk)

/**
  * @brief  RX DMA Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxDMA_Dis(__UART__)                       CLEAR_BIT((__UART__)->CR0, UART0_CR0_DRE_Msk)

/**
  * @brief  TX FIFO Reset
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxFIFO_Reset(__UART__)                    SET_BIT((__UART__)->CR0, UART0_CR0_TFR_Msk)

/**
  * @brief  TX RIFO Reset
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxFIFO_Reset(__UART__)                    SET_BIT((__UART__)->CR0, UART0_CR0_RFR_Msk)

/**
  * @brief  TX Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Tx_En(__UART__)                           SET_BIT((__UART__)->CR0, UART0_CR0_TE_Msk)

/**
  * @brief  TX Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Tx_Dis(__UART__)                          CLEAR_BIT((__UART__)->CR0, UART0_CR0_TE_Msk)

/**
  * @brief  RX Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Rx_En(__UART__)                           SET_BIT((__UART__)->CR0, UART0_CR0_RE_Msk)

/**
  * @brief  RX Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Rx_Dis(__UART__)                          CLEAR_BIT((__UART__)->CR0, UART0_CR0_RE_Msk)

/**
  * @brief  UART Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_En(__UART__)                              SET_BIT((__UART__)->CR0, UART0_CR0_UE_Msk)

/**
  * @brief  UART Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Dis(__UART__)                             CLEAR_BIT((__UART__)->CR0, UART0_CR0_UE_Msk)

/**
  * @brief  Judge is UART Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 UART is Disable
  * @retval 1 UART is Enable
  */
#define __LL_UART_IsEn(__UART__)                            READ_BIT_SHIFT((__UART__)->CR0, UART0_CR0_UE_Msk, UART0_CR0_UE_Pos)


/**
  * @brief  Auto Baud Rate Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AutoBaudRate_En(__UART__)                 SET_BIT((__UART__)->CR1, UART0_CR1_ABR_Msk)

/**
  * @brief  Auto Baud Rate Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AutoBaudRate_Dis(__UART__)                CLEAR_BIT((__UART__)->CR1, UART0_CR1_ABR_Msk)

/**
  * @brief  Judge is Auto Baud Rate Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_IsAutoBaudRateEn(__UART__)                READ_BIT_SHIFT((__UART__)->CR1, UART0_CR1_ABR_Msk, UART0_CR1_ABR_Pos)

/**
  * @brief  Tx Idle Frame Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxIdleFrame_En(__UART__)                  SET_BIT((__UART__)->CR1, UART0_CR1_IDR_Msk)

/**
  * @brief  Tx Idle Frame Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxIdleFrame_Dis(__UART__)                 CLEAR_BIT((__UART__)->CR1, UART0_CR1_IDR_Msk)

/**
  * @brief  Tx Break Frame Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxBreakFrame_En(__UART__)                 SET_BIT((__UART__)->CR1, UART0_CR1_BKR_Msk)

/**
  * @brief  Tx Break Frame Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxBreakFrame_Dis(__UART__)                CLEAR_BIT((__UART__)->CR1, UART0_CR1_BKR_Msk)

/**
  * @brief  TX Extend-Mode Set
  * @param  __UART__ Specifies UART peripheral
  * @param  mode TX Extend-Mode
  * @return None
  */
#define __LL_UART_TxExtMode_Set(__UART__, mode)             \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_TEM_Msk, (((mode) & 1UL) << UART0_CR1_TEM_Pos))

/**
  * @brief  Judge is TX Extend Address Match mode or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 is TX Extend Normal Mode
  * @retval 1 is TX Extend Address Match Mode
  */
#define __LL_UART_IsTxExtAddrMatchMode(__UART__)            READ_BIT_SHIFT((__UART__)->CR1, UART0_CR1_TEM_Msk, UART0_CR1_TEM_Pos)

/**
  * @brief  RX Extend-Mode set
  * @param  __UART__ Specifies UART peripheral
  * @param  mode RX Extend-Mode
  * @return None
  */
#define __LL_UART_RxExtMode_Set(__UART__, mode)             \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_REM_Msk, (((mode) & 1UL) << UART0_CR1_REM_Pos))

/**
  * @brief  Judge is RX Extend Address Match mode or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 is RX Extend Normal Mode
  * @retval 1 is RX Extend Address Match Mode
  */
#define __LL_UART_IsRxExtAddrMatchMode(__UART__)            READ_BIT_SHIFT((__UART__)->CR1, UART0_CR1_REM_Msk, UART0_CR1_REM_Pos)

/**
  * @brief  Extend-Bit Enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ExtBit_En(__UART__)                       SET_BIT((__UART__)->CR1, UART0_CR1_EBE_Msk)

/**
  * @brief  Extend-Bit Disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ExtBit_Dis(__UART__)                      CLEAR_BIT((__UART__)->CR1, UART0_CR1_EBE_Msk)

/**
  * @brief  Judge is Extend-Bit Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Extend-Bit is Disable
  * @retval 1 Extend-Bit is Enable
  */
#define __LL_UART_IsExtBitEn(__UART__)                      READ_BIT_SHIFT((__UART__)->CR1, UART0_CR1_EBE_Msk, UART0_CR1_EBE_Pos)

/**
  * @brief  DE Signal Polarity Set
  * @param  __UART__ Specifies UART peripheral
  * @param  pol DE Signal Polarity
  * @return None
  */
#define __LL_UART_DE_Pol_Set(__UART__, pol)                 \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_DEP_Msk, (((pol) & 0x1UL) << UART0_CR1_DEP_Pos))

/**
  * @brief  RE Signal Polarity Set
  * @param  __UART__ Specifies UART peripheral
  * @param  pol RE Signal Polarity
  * @return None
  */
#define __LL_UART_RE_Pol_Set(__UART__, pol)                 \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_REP_Msk, (((pol) & 0x1UL) << UART0_CR1_REP_Pos))

/**
  * @brief  RS485 enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RS485_En(__UART__)                        SET_BIT((__UART__)->CR1, UART0_CR1_RS485E_Msk)

/**
  * @brief  RS485 disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RS485_Dis(__UART__)                       CLEAR_BIT((__UART__)->CR1, UART0_CR1_RS485E_Msk)

/**
  * @brief  Bit Order Set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  order Bit Order
  * @return None
  */
#define __LL_UART_BitOrder_Set(__UART__, order)             \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_MSB_Msk, (((order) & 1UL) << UART0_CR1_MSB_Pos))

/**
  * @brief  Stick parity Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_StickParity_En(__UART__)                  SET_BIT((__UART__)->CR1, UART0_CR1_SPE_Msk)

/**
  * @brief  Stick parity Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_StickParity_Dis(__UART__)                 CLEAR_BIT((__UART__)->CR1, UART0_CR1_SPE_Msk)

/**
  * @brief  Parity set
  * @param  __UART__ Specifies UART peripheral
  * @param  parity Parity
  * @return None
  */
#define __LL_UART_Parity_Set(__UART__, parity)              \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_PSEL_Msk, (((parity) & 0x1UL) << UART0_CR1_PSEL_Pos))

/**
  * @brief  Parity enable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Parity_En(__UART__)                       SET_BIT((__UART__)->CR1, UART0_CR1_PEN_Msk)

/**
  * @brief  Parity disable
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_Parity_Dis(__UART__)                      CLEAR_BIT((__UART__)->CR1, UART0_CR1_PEN_Msk)

/**
  * @brief  Judge parity is enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Parity is Disable
  * @retval 1 Parity is Enable
  */
#define __LL_UART_IsParityEn(__UART__)                      READ_BIT_SHIFT((__UART__)->CR1, UART0_CR1_PEN_Msk, UART0_CR1_PEN_Pos)

/**
  * @brief  Stop Length Set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  len Stop Length
  * @return None
  */
#define __LL_UART_StopLen_Set(__UART__, len)                \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_STP_Msk, (((len) & 0x1UL) << UART0_CR1_STP_Pos))

/**
  * @brief  Data length Set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  len Data length
  * @return None
  */
#define __LL_UART_DatLen_Set(__UART__, len)                 \
        MODIFY_REG((__UART__)->CR1, UART0_CR1_LEN_Msk, (((len) & 0x3UL) << UART0_CR1_LEN_Pos))

/**
  * @brief  Data length Get
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Data length is 5bits
  * @retval 1 Data length is 6bits
  * @retval 2 Data length is 7bits
  * @retval 3 Data length is 8bits
  */
#define __LL_UART_DatLen_Get(__UART__)                      READ_BIT_SHIFT((__UART__)->CR1, UART0_CR1_LEN_Msk, UART0_CR1_LEN_Pos)


/**
  * @brief  Baudrate Value Set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  val Baudrate Value
  * @return None
  */
#define __LL_UART_Baudrate_Set(__UART__, val)               \
        MODIFY_REG((__UART__)->BAUD, UART0_BAUD_BAUD_Msk, (((val) & 0xffffUL) << UART0_BAUD_BAUD_Pos))

/**
  * @brief  Baudrate Value Read
  * @param  __UART__ Specifies UART peripheral
  * @return Baudrate Value
  */
#define __LL_UART_Baudrate_Read(__UART__)                    \
        READ_BIT_SHIFT((__UART__)->BAUD, UART0_BAUD_BAUD_Msk, UART0_BAUD_BAUD_Pos)


/**
  * @brief  RX FIFO Full Threshold Set
  * @param  __UART__ Specifies UART peripheral
  * @param  thres RxFIFO Full Threshold
  * @return None
  */
#define __LL_UART_RxFIFOFullThres_Set(__UART__, thres)      \
        MODIFY_REG((__UART__)->FIFOCTRL, UART0_FIFOCTRL_RXFT_Msk, (((thres-1) & 0xfUL) << UART0_FIFOCTRL_RXFT_Pos))

/**
  * @brief  RX FIFO Full Threshold Get
  * @param  __UART__ Specifies UART peripheral
  * @return RxFIFO Full Threshold
  */
#define __LL_UART_RxFIFOFullThres_Get(__UART__)             \
        (READ_BIT_SHIFT((__UART__)->FIFOCTRL, UART0_FIFOCTRL_RXFT_Msk, UART0_FIFOCTRL_RXFT_Pos) + 1)

/**
  * @brief  TX FIFO Empty Threshold Set
  * @param  __UART__ Specifies UART peripheral
  * @param  thres TxFIFO Empty Threshold
  * @return None
  */
#define __LL_UART_TxFIFOEmptyThres_Set(__UART__, thres)     \
        MODIFY_REG((__UART__)->FIFOCTRL, UART0_FIFOCTRL_TXFT_Msk, (((thres) & 0xfUL) << UART0_FIFOCTRL_TXFT_Pos))

/**
  * @brief  TX FIFO Empty Threshold Get
  * @param  __UART__ Specifies UART peripheral
  * @return TxFIFO Empty Threshold
  */
#define __LL_UART_TxFIFOEmptyThres_Get(__UART__)            \
        READ_BIT_SHIFT((__UART__)->FIFOCTRL, UART0_FIFOCTRL_TXFT_Msk, UART0_FIFOCTRL_TXFT_Pos)


/**
  * @brief  RS485 DE deassertion time set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DE_DeAssertTime_Set(__UART__, val)        \
        MODIFY_REG((__UART__)->TIMING0, UART0_TIMING0_DEDT_Msk, (((val) & 0xffffUL) << UART0_TIMING0_DEDT_Pos))

/**
  * @brief  RS485 DE assertion time set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DE_AssertTime_Set(__UART__, val)          \
        MODIFY_REG((__UART__)->TIMING0, UART0_TIMING0_DEAT_Msk, (((val) & 0xffffUL) << UART0_TIMING0_DEAT_Pos))


/**
  * @brief  RS485 RE to DE turn around time set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_REtoDE_TurnAroundTime_Set(__UART__, val)  \
        MODIFY_REG((__UART__)->TIMING1, UART0_TIMING1_RDET_Msk, (((val) & 0xffffUL) << UART0_TIMING1_RDET_Pos))

/**
  * @brief  RS485 DE to RE turn around time set
  * @note   Can only be config in UART Disable state
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_DEtoRE_TurnAroundTime_Set(__UART__, val)  \
        MODIFY_REG((__UART__)->TIMING1, UART0_TIMING1_DRET_Msk, (((val) & 0xffffUL) << UART0_TIMING1_DRET_Pos))


/**
  * @brief  TX data 8bits write
  * @param  __UART__ Specifies UART peripheral
  * @param  dat 8bits write data
  * @return None
  */
#define __LL_UART_TxDat8bits_Write(__UART__, dat)           WRITE_REG((__UART__)->TDR, ((dat) & 0xffUL))

/**
  * @brief  TX data 9bits write
  * @param  __UART__ Specifies UART peripheral
  * @param  dat 9bits write data
  * @return None
  */
#define __LL_UART_TxDat9bits_Write(__UART__, dat)           WRITE_REG((__UART__)->TDR, ((dat) & 0x1ffUL))


/**
  * @brief  RX Over Data set
  * @param  __UART__ Specifies UART peripheral
  * @param  val set value
  * @return None
  */
#define __LL_UART_OverDat_Set(__UART__, val)                \
        MODIFY_REG((__UART__)->RDR, UART0_RDR_OVDA_Msk, (((val) & 0x7ffUL) << UART0_RDR_OVDA_Pos))

/**
  * @brief  RX Over Data Get
  * @param  __UART__ Specifies UART peripheral
  * @return RX Over Data
  */
#define __LL_UART_OverDat_Get(__UART__)                     \
        READ_BIT_SHIFT((__UART__)->RDR, UART0_RDR_OVDA_Msk, UART0_RDR_OVDA_Pos)

/**
  * @brief  Judge is Rx Frame Status correct or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Rx Frame Status is error
  * @retval 1 Rx Frame Status is correct
  */
#define __LL_UART_IsRxFrameStaCorrect(__UART__)             \
        (!(READ_BIT_SHIFT((__UART__)->RDR, UART0_RDR_FMST_Msk, UART0_RDR_FMST_Pos)))

/**
  * @brief  Judge is Rx Parity Status correct or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Rx Parity Status is error
  * @retval 1 Rx Parity Status is correct
  */
#define __LL_UART_IsRxParityStaCorrect(__UART__)            \
        (!(READ_BIT_SHIFT((__UART__)->RDR, UART0_RDR_PRST_Msk, UART0_RDR_PRST_Pos)))

/**
  * @brief  RX data 8bits read
  * @param  __UART__ Specifies UART peripheral
  * @return 8bits read data
  */
#define __LL_UART_RxDat8bits_Read(__UART__)                 (READ_BIT((__UART__)->RDR, 0xffUL))

/**
  * @brief  RX data 9bits read
  * @param  __UART__ Specifies UART peripheral
  * @return 9bits read data
  */
#define __LL_UART_RxDat9bits_Read(__UART__)                 (READ_BIT((__UART__)->RDR, 0x1ffUL))

/**
  * @brief  RX data register read
  * @param  __UART__ Specifies UART peripheral
  * @return RX data register valule
  */
#define __LL_UART_RxDatReg_Read(__UART__)                   READ_REG((__UART__)->RDR)


/**
  * @brief  TX Extend Address set
  * @param  __UART__ Specifies UART peripheral
  * @param  addr TX Extend Address
  * @return None
  */
#define __LL_UART_TxExtAddr_Set(__UART__, addr)             \
        MODIFY_REG((__UART__)->TAR, UART0_TAR_TAR_Msk, (((addr) & 0xffUL) << UART0_TAR_TAR_Pos))


/**
  * @brief  RX Extend Address set
  * @param  __UART__ Specifies UART peripheral
  * @param  addr RX Extend Address
  * @return None
  */
#define __LL_UART_RxExtAddr_Set(__UART__, addr)             \
        MODIFY_REG((__UART__)->RAR, UART0_RAR_RAR_Msk, (((addr) & 0xffUL) << UART0_RAR_RAR_Pos))


/**
  * @brief  Rx Timeout Time set
  * @param  __UART__ Specifies UART peripheral
  * @param  time Rx Timeout Time
  * @return None
  */
#define __LL_UART_RxTimeoutTime_Set(__UART__, time)         \
        MODIFY_REG((__UART__)->RTO, UART0_RTO_RTO_Msk, (((time) & 0xffffUL) << UART0_RTO_RTO_Pos))


/**
  * @brief  Auto Baud Rate Error Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AutoBaudRateErr_INT_En(__UART__)          SET_BIT((__UART__)->INTEN, UART0_INTEN_ABRE_Msk)

/**
  * @brief  Auto Baud Rate Error Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AutoBaudRateErr_INT_Dis(__UART__)         CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_ABRE_Msk)

/**
  * @brief  Judge is Auto Baud Rate Error Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Auto Baud Rate Error Interrupt Enable
  * @retval 1 is Auto Baud Rate Error Interrupt Enable
  */
#define __LL_UART_IsAutoBaudRateErrIntEn(__UART__)                \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_ABRE_Msk, UART0_INTEN_ABRE_Pos)

/**
  * @brief  RX Address Match Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxAddrMatch_INT_En(__UART__)              SET_BIT((__UART__)->INTEN, UART0_INTEN_AMIE_Msk)

/**
  * @brief  RX Address Match Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxAddrMatch_INT_Dis(__UART__)             CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_AMIE_Msk)

/**
  * @brief  TX Idle Done Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxIdleDone_INT_En(__UART__)               SET_BIT((__UART__)->INTEN, UART0_INTEN_IDLE_Msk)

/**
  * @brief  TX Idle Done Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxIdleDone_INT_Dis(__UART__)              CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_IDLE_Msk)

/**
  * @brief  TX Break Done Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxBreakDone_INT_En(__UART__)              SET_BIT((__UART__)->INTEN, UART0_INTEN_TBIE_Msk)

/**
  * @brief  TX Break Done Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxBreakDone_INT_Dis(__UART__)             CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_TBIE_Msk)

/**
  * @brief  TXDone Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxDone_INT_En(__UART__)                   SET_BIT((__UART__)->INTEN, UART0_INTEN_TDIE_Msk)

/**
  * @brief  TXDone Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxDone_INT_Dis(__UART__)                  CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_TDIE_Msk)

/**
  * @brief  Judge is UART TXDone Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TXDone Interrupt Enable
  * @retval 1 is TXDone Interrupt Enable
  */
#define __LL_UART_IsTxDoneIntEn(__UART__)                   \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_TDIE_Msk, UART0_INTEN_TDIE_Pos)

/**
  * @brief  RX Timeout Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxTimeout_INT_En(__UART__)                SET_BIT((__UART__)->INTEN, UART0_INTEN_RTIE_Msk)

/**
  * @brief  RX Timeout Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxTimeout_INT_Dis(__UART__)               CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_RTIE_Msk)

/**
  * @brief  Judge is UART RX Timeout Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RX Timeout Interrupt Enable
  * @retval 1 is RX Timeout Interrupt Enable
  */
#define __LL_UART_IsRxTimeoutIntEn(__UART__)                \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_RTIE_Msk, UART0_INTEN_RTIE_Pos)

/**
  * @brief  RX Break Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxBreak_INT_En(__UART__)                  SET_BIT((__UART__)->INTEN, UART0_INTEN_BKIE_Msk)

/**
  * @brief  RX Break Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxBreak_INT_Dis(__UART__)                 CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_BKIE_Msk)

/**
  * @brief  Frame Error Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_FrameErr_INT_En(__UART__)                 SET_BIT((__UART__)->INTEN, UART0_INTEN_FEIE_Msk)

/**
  * @brief  Frame Error Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_FrameErr_INT_Dis(__UART__)                CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_FEIE_Msk)

/**
  * @brief  Judge is UART FrameError Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't FrameError Interrupt Enable
  * @retval 1 is FrameError Interrupt Enable
  */
#define __LL_UART_IsFrameErrIntEn(__UART__)                 \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_FEIE_Msk, UART0_INTEN_FEIE_Pos)

/**
  * @brief  Parity Error Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ParityErr_INT_En(__UART__)                SET_BIT((__UART__)->INTEN, UART0_INTEN_PEIE_Msk)

/**
  * @brief  Parity Error Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ParityErr_INT_Dis(__UART__)               CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_PEIE_Msk)

/**
  * @brief  Judge is UART ParityError Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't ParityError Interrupt Enable
  * @retval 1 is ParityError Interrupt Enable
  */
#define __LL_UART_IsParityErrIntEn(__UART__)                \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_PEIE_Msk, UART0_INTEN_PEIE_Pos)

/**
  * @brief  Noise Detection Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_NoiseDetect_INT_En(__UART__)              SET_BIT((__UART__)->INTEN, UART0_INTEN_NOIE_Msk)

/**
  * @brief  Noise Detection Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_NoiseDetect_INT_Dis(__UART__)             CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_NOIE_Msk)

/**
  * @brief  Judge is Noise Detection Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Noise Detection Interrupt Enable
  * @retval 1 is Noise Detection Interrupt Enable
  */
#define __LL_UART_IsNoiseDetectIntEn(__UART__)              \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_NOIE_Msk, UART0_INTEN_NOIE_Pos)

/**
  * @brief  Idle Detection Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxIdleDetect_INT_En(__UART__)             SET_BIT((__UART__)->INTEN, UART0_INTEN_IDIE_Msk)

/**
  * @brief  Idle Detection Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxIdleDetect_INT_Dis(__UART__)            CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_IDIE_Msk)

/**
  * @brief  Judge is Idle Detection Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Idle Detection Interrupt Enable
  * @retval 1 is Idle Detection Interrupt Enable
  */
#define __LL_UART_IsRxIdleDetectIntEn(__UART__)             \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_IDIE_Msk, UART0_INTEN_IDIE_Pos)

/**
  * @brief  TX FIFO OverFlow Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxOverFlow_INT_En(__UART__)               SET_BIT((__UART__)->INTEN, UART0_INTEN_TOIE_Msk)

/**
  * @brief  TX FIFO OverFlow Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxOverFlow_INT_Dis(__UART__)              CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_TOIE_Msk)

/**
  * @brief  Judge is TX FIFO OverFlow Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TX FIFO OverFlow Interrupt Enable
  * @retval 1 is TX FIFO OverFlow Interrupt Enable
  */
#define __LL_UART_IsTxOverFlowIntEn(__UART__)               \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_TOIE_Msk, UART0_INTEN_TOIE_Pos)

/**
  * @brief  RX FIFO UnderFlow Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxUnderFlow_INT_En(__UART__)              SET_BIT((__UART__)->INTEN, UART0_INTEN_RUIE_Msk)

/**
  * @brief  RX FIFO UnderFlow Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxUnderFlow_INT_Dis(__UART__)             CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_RUIE_Msk)

/**
  * @brief  Judge is RX FIFO UnderFlow Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RX FIFO UnderFlow Interrupt Enable
  * @retval 1 is RX FIFO UnderFlow Interrupt Enable
  */
#define __LL_UART_IsRxUnderFlowIntEn(__UART__)              \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_RUIE_Msk, UART0_INTEN_RUIE_Pos)

/**
  * @brief  RX FIFO OverFlow Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxOverFlow_INT_En(__UART__)               SET_BIT((__UART__)->INTEN, UART0_INTEN_ROIE_Msk)

/**
  * @brief  RX FIFO OverFlow Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxOverFlow_INT_Dis(__UART__)              CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_ROIE_Msk)

/**
  * @brief  Judge is RX FIFO OverFlow Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RX FIFO OverFlow Interrupt Enable
  * @retval 1 is RX FIFO OverFlow Interrupt Enable
  */
#define __LL_UART_IsRxOverFlowIntEn(__UART__)               \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_ROIE_Msk, UART0_INTEN_ROIE_Pos)

/**
  * @brief  TX FIFO empty Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxEmpty_INT_En(__UART__)                  SET_BIT((__UART__)->INTEN, UART0_INTEN_TEIE_Msk)

/**
  * @brief  TX FIFO empty Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxEmpty_INT_Dis(__UART__)                 CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_TEIE_Msk)

/**
  * @brief  Judge is TxEmpty Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TxEmpty Interrupt Enable
  * @retval 1 is TxEmpty Interrupt Enable
  */
#define __LL_UART_IsTxEmptyIntEn(__UART__)                  \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_TEIE_Msk, UART0_INTEN_TEIE_Pos)

/**
  * @brief  RX FIFO full Interrupt Enable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxFull_INT_En(__UART__)                   SET_BIT((__UART__)->INTEN, UART0_INTEN_RFIE_Msk)

/**
  * @brief  RX FIFO full Interrupt Disable
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxFull_INT_Dis(__UART__)                  CLEAR_BIT((__UART__)->INTEN, UART0_INTEN_RFIE_Msk)

/**
  * @brief  Judge is RX FIFO full Interrupt Enable or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RxFull Interrupt Enable
  * @retval 1 is RxFull Interrupt Enable
  */
#define __LL_UART_IsRxFullIntEn(__UART__)                   \
        READ_BIT_SHIFT((__UART__)->INTEN, UART0_INTEN_RFIE_Msk, UART0_INTEN_RFIE_Pos)

/**
  * @brief  All Interrupt Enable Status Get
  * @param  __UART__ Specifies UART peripheral
  * @return All Interrupt Enable Status
  */
#define __LL_UART_AllIntEn_Get(__UART__)                    READ_REG((__UART__)->INTEN)


/**
  * @brief  Judge is Auto Baud Rate Error Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Auto Baud Rate Error Interrupt Pending
  * @retval 1 is Auto Baud Rate Error Interrupt Pending
  */
#define __LL_UART_IsAutoBaudRateErrIntPnd(__UART__)         READ_BIT_SHIFT((__UART__)->INT, UART0_INT_ABRF_Msk, UART0_INT_ABRF_Pos)

/**
  * @brief  Auto Baud Rate Error Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AutoBaudRateErrIntPnd_Clr(__UART__)       WRITE_REG((__UART__)->INT, UART0_INT_ABRF_Msk)

/**
  * @brief  Judge is Rx Address Match Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Rx Address Match Interrupt Pending
  * @retval 1 is Rx Address Match Interrupt Pending
  */
#define __LL_UART_IsRxAddrMatchIntPnd(__UART__)             READ_BIT_SHIFT((__UART__)->INT, UART0_INT_AMIF_Msk, UART0_INT_AMIF_Pos)

/**
  * @brief  Rx Address Match Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxAddrMatchIntPnd_Clr(__UART__)           WRITE_REG((__UART__)->INT, UART0_INT_AMIF_Msk)

/**
  * @brief  Judge is TX Idle Done Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TX Idle Done Interrupt Pending
  * @retval 1 is TX Idle Done Interrupt Pending
  */
#define __LL_UART_IsTxIdleDoneIntPnd(__UART__)              READ_BIT_SHIFT((__UART__)->INT, UART0_INT_IDLF_Msk, UART0_INT_IDLF_Pos)

/**
  * @brief  TX Idle Done Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxIdleDoneIntPnd_Clr(__UART__)            WRITE_REG((__UART__)->INT, UART0_INT_IDLF_Msk)

/**
  * @brief  Judge is TX Break Done Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TX Break Done Interrupt Pending
  * @retval 1 is TX Break Done Interrupt Pending
  */
#define __LL_UART_IsTxBreakDoneIntPnd(__UART__)             READ_BIT_SHIFT((__UART__)->INT, UART0_INT_TBIF_Msk, UART0_INT_TBIF_Pos)

/**
  * @brief  TX Break Done Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxBreakDoneIntPnd_Clr(__UART__)           WRITE_REG((__UART__)->INT, UART0_INT_TBIF_Msk)

/**
  * @brief  Judge is TX Done Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TX Done Interrupt Pending
  * @retval 1 is TX Done Interrupt Pending
  */
#define __LL_UART_IsTxDoneIntPnd(__UART__)                  READ_BIT_SHIFT((__UART__)->INT, UART0_INT_TDIF_Msk, UART0_INT_TDIF_Pos)

/**
  * @brief  TX Done Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxDoneIntPnd_Clr(__UART__)                WRITE_REG((__UART__)->INT, UART0_INT_TDIF_Msk)

/**
  * @brief  Judge is RX Timeout Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Rx Timeout Interrupt Pending
  * @retval 1 is Rx Timeout Interrupt Pending
  */
#define __LL_UART_IsRxTimeoutIntPnd(__UART__)               READ_BIT_SHIFT((__UART__)->INT, UART0_INT_RTOI_Msk, UART0_INT_RTOI_Pos)

/**
  * @brief  RX Timeout Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxTimeoutIntPnd_Clr(__UART__)             WRITE_REG((__UART__)->INT, UART0_INT_RTOI_Msk)

/**
  * @brief  Judge is RX Break Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RX Break Interrupt Pending
  * @retval 1 is RX Break Interrupt Pending
  */
#define __LL_UART_IsRxBreakIntPnd(__UART__)                 READ_BIT_SHIFT((__UART__)->INT, UART0_INT_BKIF_Msk, UART0_INT_BKIF_Pos)

/**
  * @brief  RX Break Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxBreakIntPnd_Clr(__UART__)               WRITE_REG((__UART__)->INT, UART0_INT_BKIF_Msk)

/**
  * @brief  Judge is frame error Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't frame error Pending
  * @retval 1 is frame error Pending
  */
#define __LL_UART_IsFrameErrIntPnd(__UART__)                READ_BIT_SHIFT((__UART__)->INT, UART0_INT_FEIF_Msk, UART0_INT_FEIF_Pos)

/**
  * @brief  frame error Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_FrameErrIntPnd_Clr(__UART__)              WRITE_REG((__UART__)->INT, UART0_INT_FEIF_Msk)

/**
  * @brief  Judge is parity error Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't parity error Pending
  * @retval 1 is parity error Pending
  */
#define __LL_UART_IsParityErrIntPnd(__UART__)               READ_BIT_SHIFT((__UART__)->INT, UART0_INT_PEIF_Msk, UART0_INT_PEIF_Pos)

/**
  * @brief  parity error Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_ParityErrIntPnd_Clr(__UART__)             WRITE_REG((__UART__)->INT, UART0_INT_PEIF_Msk)

/**
  * @brief  Judge is RXFIFO error Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RXFIFO error Pending
  * @retval 1 is RXFIFO error Pending
  */
#define __LL_UART_IsRxFIFOErr(__UART__)                     \
        (!!READ_BIT_SHIFT((__UART__)->INT, UART0_INT_PEIF_Msk | UART0_INT_FEIF_Msk | UART0_INT_BKIF_Msk, UART0_INT_PEIF_Pos))

/**
  * @brief  RXFIFO error Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxFIFOErrIntPnd_Clr(__UART__)             \
        WRITE_REG((__UART__)->INT, UART0_INT_PEIF_Msk | UART0_INT_FEIF_Msk | UART0_INT_BKIF_Msk)

/**
  * @brief  Judge is Noise Detection Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Noise Detection Interrupt Pending
  * @retval 1 is Noise Detection Interrupt Pending
  */
#define __LL_UART_IsNoiseDetectIntPnd(__UART__)             READ_BIT_SHIFT((__UART__)->INT, UART0_INT_NOIF_Msk, UART0_INT_NOIF_Pos)

/**
  * @brief  Noise Detection Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_NoiseDetectIntPnd_Clr(__UART__)           WRITE_REG((__UART__)->INT, UART0_INT_NOIF_Msk)

/**
  * @brief  Judge is Idle Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't Idle Interrupt Pending
  * @retval 1 is Idle Interrupt Pending
  */
#define __LL_UART_IsRxIdleIntPnd(__UART__)                  READ_BIT_SHIFT((__UART__)->INT, UART0_INT_IDIF_Msk, UART0_INT_IDIF_Pos)

/**
  * @brief  Idle Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxIdleIntPnd_Clr(__UART__)                WRITE_REG((__UART__)->INT, UART0_INT_IDIF_Msk)

/**
  * @brief  Judge is TXFIFO OverFlow Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 TXFIFO isn't OverFlow Pending
  * @retval 1 TXFIFO is OverFlow Pending
  */
#define __LL_UART_IsTxFIFOOverFlowIntPnd(__UART__)          READ_BIT_SHIFT((__UART__)->INT, UART0_INT_TOIF_Msk, UART0_INT_TOIF_Pos)

/**
  * @brief  TXFIFO OverFlow Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_TxFIFOOverFlowIntPnd_Clr(__UART__)        WRITE_REG((__UART__)->INT, UART0_INT_TOIF_Msk)

/**
  * @brief  Judge is RXFIFO UnderFlow Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 RXFIFO isn't UnderFlow Pending
  * @retval 1 RXFIFO is UnderFlow Pending
  */
#define __LL_UART_IsRxFIFOUnderFlowIntPnd(__UART__)         READ_BIT_SHIFT((__UART__)->INT, UART0_INT_RUIF_Msk, UART0_INT_RUIF_Pos)

/**
  * @brief  RXFIFO UnderFlow Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxFIFOUnderFlowIntPnd_Clr(__UART__)       WRITE_REG((__UART__)->INT, UART0_INT_RUIF_Msk)

/**
  * @brief  Judge is RXFIFO OverFlow Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 RXFIFO isn't OverFlow Pending
  * @retval 1 RXFIFO is OverFlow Pending
  */
#define __LL_UART_IsRxFIFOOverFlowIntPnd(__UART__)          READ_BIT_SHIFT((__UART__)->INT, UART0_INT_ROIF_Msk, UART0_INT_ROIF_Pos)

/**
  * @brief  RXFIFO OverFlow Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_RxFIFOOverFlowIntPnd_Clr(__UART__)        WRITE_REG((__UART__)->INT, UART0_INT_ROIF_Msk)

/**
  * @brief  Judge is TXFIFO empty Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't TXFIFO empty Interrupt Pending
  * @retval 1 is TXFIFO empty Interrupt Pending
  */
#define __LL_UART_IsTxFIFOEmptyIntPnd(__UART__)             READ_BIT_SHIFT((__UART__)->INT, UART0_INT_TXEI_Msk, UART0_INT_TXEI_Pos)

/**
  * @brief  Judge is RXFIFO full Interrupt Pending or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 isn't RXFIFO full Interrupt Pending
  * @retval 1 is RXFIFO full Interrupt Pending
  */
#define __LL_UART_IsRxFIFOFullIntPnd(__UART__)              READ_BIT_SHIFT((__UART__)->INT, UART0_INT_RXFI_Msk, UART0_INT_RXFI_Pos)

/**
  * @brief  All Interrupt Pending Get
  * @param  __UART__ Specifies UART peripheral
  * @return All Interrupt Pending
  */
#define __LL_UART_AllIntPnd_Get(__UART__)                   READ_REG((__UART__)->INT)

/**
  * @brief  All Interrupt Pending Clear
  * @param  __UART__ Specifies UART peripheral
  * @return None
  */
#define __LL_UART_AllIntPnd_Clr(__UART__)                   WRITE_REG((__UART__)->INT, 0xffffffffUL)


/**
  * @brief  RX-Start error get
  * @param  __UART__ Specifies UART peripheral
  * @return RX-Start error 
  */
#define __LL_UART_RxStartErr_Get(__UART__)      READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_RSE_Msk, UART0_STATUS_RSE_Pos)

/**
  * @brief  RXFIFO level get
  * @param  __UART__ Specifies UART peripheral
  * @return RXFIFO level
  */
#define __LL_UART_RxFIFOLvl_Get(__UART__)       READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_RFL_Msk, UART0_STATUS_RFL_Pos)

/**
  * @brief  Judge is RXFIFO Full or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 RXFIFO isn't Full
  * @retval 1 RXFIFO is Full
  */
#define __LL_UART_IsRxFIFOFull(__UART__)        READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_RFF_Msk, UART0_STATUS_RFF_Pos)

/**
  * @brief  Judge is RXFIFO Empty or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 RXFIFO isn't Empty
  * @retval 1 RXFIFO is Empty
  */
#define __LL_UART_IsRxFIFOEmpty(__UART__)       READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_RFE_Msk, UART0_STATUS_RFE_Pos)

/**
  * @brief  Judge is Rx Busy or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Rx is Idle
  * @retval 1 Rx is Busy
  */
#define __LL_UART_IsRxBusy(__UART__)            READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_RBSY_Msk, UART0_STATUS_RBSY_Pos)

/**
  * @brief  TXFIFO level get
  * @param  __UART__ Specifies UART peripheral
  * @return TXFIFO level
  */
#define __LL_UART_TxFIFOLvl_Get(__UART__)       READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_TFL_Msk, UART0_STATUS_TFL_Pos)

/**
  * @brief  Judge is TXFIFO Full or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 TXFIFO isn't Full
  * @retval 1 TXFIFO is Full
  */
#define __LL_UART_IsTxFIFOFull(__UART__)        READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_TFF_Msk, UART0_STATUS_TFF_Pos)

/**
  * @brief  Judge is TXFIFO Empty or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 TXFIFO isn't Empty
  * @retval 1 TXFIFO is Empty
  */
#define __LL_UART_IsTxFIFOEmpty(__UART__)       READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_TFE_Msk, UART0_STATUS_TFE_Pos)

/**
  * @brief  Judge is Tx Busy or not
  * @param  __UART__ Specifies UART peripheral
  * @retval 0 Tx is Idle
  * @retval 1 Tx is Busy
  */
#define __LL_UART_IsTxBusy(__UART__)            READ_BIT_SHIFT((__UART__)->STATUS, UART0_STATUS_TBSY_Msk, UART0_STATUS_TBSY_Pos)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Types UART LL Exported Types
  * @brief    UART LL Exported Types
  * @{
  */

/**
  * @brief UART Uer callback function type definition
  */
typedef void (*UART_UserCallback)(void);

/**
  * @brief UART Instance definition
  */
typedef enum {
    UART_INSTANCE_0 = 0,            /*!< UART Instance 0        */
    UART_INSTANCE_1,                /*!< UART Instance 1        */
    UART_INSTANCE_2,                /*!< UART Instance 2        */
    UART_INSTANCE_3,                /*!< UART Instance 3        */
    UART_INSTANCE_4,                /*!< UART Instance 4        */
    UART_INSTANCE_NUMS,             /*!< UART Instance Numbers  */
} UART_InstanceETypeDef;

/**
  * @brief UART State definition
  */
typedef enum {
    UART_STATE_RESET,               /*!< Peripheral not Initialized                 */
    UART_STATE_READY,               /*!< Peripheral Initialized and ready for use   */
    UART_STATE_BUSY,                /*!< an internal process is ongoing             */
    UART_STATE_BUSY_TX,             /*!< Data Tx process is ongoing                 */
    UART_STATE_BUSY_RX,             /*!< Data Rx process is ongoing                 */
    UART_STATE_ERROR,               /*!< UART error state                           */
} UART_StateETypeDef;


/**
  * @brief UART data length type definition
  */
typedef enum {
    UART_DAT_LEN_5b = 0,            /*!< Data length 5bits  */
    UART_DAT_LEN_6b,                /*!< Data length 6bits  */
    UART_DAT_LEN_7b,                /*!< Data length 7bits  */
    UART_DAT_LEN_8b,                /*!< Data length 8bits  */
} UART_DatLenETypeDef;

/**
  * @brief UART stop length type definition
  */
typedef enum {
    UART_STOP_LEN_1b = 0,           /*!< Stop length 1bit   */
    UART_STOP_LEN_2b,               /*!< Stop length 2bits  */
} UART_StopLenETypeDef;

/**
  * @brief UART parity type definition
  */
typedef enum {
    UART_PARITY_NO = -1,            /*!< Parity no          */
    UART_PARITY_EVEN,               /*!< Parity even        */
    UART_PARITY_ODD,                /*!< Parity odd         */
} UART_ParityETypeDef;

/**
  * @brief UART Pin Polarity definition
  */
typedef enum {
    UART_PIN_POL_INACT_HIGH = 0,    /*!< UART Pin Polarity Inactive High    */
    UART_PIN_POL_INACT_LOW,         /*!< UART Pin Polarity Inactive Low     */
} UART_PinPolETypeDef;

/**
  * @brief UART Bit order definition
  */
typedef enum {
    UART_BIT_ORDER_LSB = 0,         /*!< UART Bit Order LSB */
    UART_BIT_ORDER_MSB,             /*!< UART Bit Order MSB */
} UART_BitOrderETypeDef;

/**
  * @brief UART Oversample Mode definition
  */
typedef enum {
    UART_OVER_SAMP_16X = 0,         /*!< UART Oversample Mode 16X   */
    UART_OVER_SAMP_8X,              /*!< UART Oversample Mode 8X    */
} UART_OverSampETypeDef;

/**
  * @brief UART RS485 DE/RE polarity type definition
  */
typedef enum {
    UART_RS485_POL_ACT_LOW = 0,     /*!< RS485 DE/RE polarity active low    */
    UART_RS485_POL_ACT_HIGH,        /*!< RS485 DE/RE polarity active high   */
} UART_RS485PolETypeDef;

/**
  * @brief UART Extend Mode definition
  */
typedef enum {
    UART_EXT_MODE_NORMAL = 0,       /*!< UART Extend Mode Normal        */
    UART_EXT_MODE_ADDR_MATCH,       /*!< UART Extend Mode Address Match */
} UART_ExtModeETypeDef;

/**
  * @brief UART Auto Baud Rate Mode definition
  */
typedef enum {
    UART_AUTO_BAUD_RATE_MODE_0 = 0,       /*!< UART Auto Baud Rate Mode character starting bit0 is 1            */
    UART_AUTO_BAUD_RATE_MODE_1,           /*!< UART Auto Baud Rate Mode character starting bit0 is 0, bit1 is 1 */
    UART_AUTO_BAUD_RATE_MODE_2,           /*!< UART Auto Baud Rate Mode begin with the character 0x7F in LSB    */
    UART_AUTO_BAUD_RATE_MODE_3,           /*!< UART Auto Baud Rate Mode begin with the character 0x55 in LSB    */
} UART_AutoBaudRateModeETypeDef;

/**
  * @brief UART RTO Mode definition
  */
typedef enum {
    UART_RTO_MODE_FNE_RXIDEL  = 0,    /*!< UART RTO Mode Rx FIFO not empty and Rx Idel */
    UART_RTO_MODE_RXIDEL      = 1,    /*!< UART RTO Mode Rx Idel */
} UART_RTOModeETypeDef;

/**
 * @brief UART IRQ Callback ID definition
 */
typedef enum {
    UART_TX_CPLT_CB_ID,                      /*!< UART Tx Completed callback ID       */
    UART_RX_CPLT_CB_ID,                      /*!< UART Rx Completed callback ID       */
    UART_TX_HALF_CPLT_CB_ID,                 /*!< UART Tx Half Completed callback ID  */
    UART_RX_HALF_CPLT_CB_ID,                 /*!< UART Rx Half Completed callback ID  */
    UART_ERROR_CB_ID,                        /*!< UART Error callback ID              */
} UART_UserCallbackIdETypeDef;


/**
  * @brief UART IRQ Callback structure definition
  */
typedef struct __UART_UserCallbackTypeDef {
    UART_UserCallback TxCpltCallback;       /*!< UART Tx Completed callback         */
    UART_UserCallback RxCpltCallback;       /*!< UART Rx Completed callback         */
    UART_UserCallback TxHalfCpltCallback;   /*!< UART Tx Half Completed callback    */
    UART_UserCallback RxHalfCpltCallback;   /*!< UART Rx Half Completed callback    */
    UART_UserCallback ErrorCallback;        /*!< UART Error callback                */
} UART_UserCallbackTypeDef;

/**
  * @brief UART LL Config Type Definition
  */
typedef struct __UART_LLCfgTypeDef {
    bool tx_rx_swap_en;                     /*!< Tx/Rx Pin Swap Enable      */
    bool rx_timeout_en;                     /*!< Rx Timeout Enable          */
    bool one_wire_en;                       /*!< One Wire Enable            */
    UART_PinPolETypeDef   tx_pol;           /*!< Tx Pin Polarity            */
    UART_PinPolETypeDef   rx_pol;           /*!< Rx Pin Polarity            */
    UART_BitOrderETypeDef bit_order;        /*!< UART Bit Order             */
    uint8_t  tx_fifo_empty_thres;           /*!< TxFIFO Empty Threshold     */
    uint8_t  rx_fifo_full_thres;            /*!< RxFIFO Full Threshold      */
    uint16_t rx_timeout;                    /*!< Rx Timeout Time            */
    UART_RTOModeETypeDef  rx_timeout_mode;  /*!< RTO Mode                   */
} UART_LLCfgTypeDef;

/**
  * @brief UART Init Structure definition
  */
typedef struct __UART_InitTypeDef {
    //Common Config
    uint32_t baudrate;                      /*!< baudrate                   */
    UART_OverSampETypeDef over_samp;        /*!< Oversample Mode            */
    UART_DatLenETypeDef   dat_len;          /*!< data length                */
    UART_StopLenETypeDef  stop_len;         /*!< stop length                */
    UART_ParityETypeDef   parity;           /*!< parity                     */
    UART_LLCfgTypeDef     *ll_cfg;          /*!< Optional LL Config Pointer */

    //Extend Mode Config
    bool ext_bit_en;                        /*!< Extend Bit(Mode) Enable    */
    uint8_t rx_addr_ext;                    /*!< Extend mode Rx address     */
    UART_ExtModeETypeDef rx_ext_mode;       /*!< Rx Extend mode             */

    //User Callback
    UART_UserCallbackTypeDef user_callback; /*!< User Callback              */
} UART_InitTypeDef;

/**
  * @brief UART RS485 Mode Config Structure definition
  */
typedef struct __UART_Rs485CfgTypeDef {
    bool     enable;                        /*!< RS485 Enable           */
    uint16_t de_assert_time;                /*!< DE assertion time      */
    uint16_t de_deassert_time;              /*!< DE de-assertion time   */
    uint16_t de2re_turn_ard_time;           /*!< DE-Re Turn Around time */
    uint16_t re2de_turn_ard_time;           /*!< RE-De Turn Around time */
    UART_RS485PolETypeDef  de_pol;          /*!< DE Singal Polarity     */
    UART_RS485PolETypeDef  re_pol;          /*!< RE Singal Polarity     */
} UART_Rs485CfgTypeDef;

/**
  * @brief UART Auto Baud Rate Mode Config Structure definition
  */
typedef struct __UART_AutoBaudCfgTypeDef {
    bool     detect_at_once;                /*!< Auto Baud Rate at once */
    uint32_t default_baud;                  /*!< Default Baud Rate      */
    UART_AutoBaudRateModeETypeDef mode;     /*!< Auto Baud Rate Mode    */
    bool over_samp_refresh;                 /*!< Refresh Oversample     */
    UART_OverSampETypeDef over_samp_reload; /*!< Oversample Mode Reload */
} UART_AutoBaudCfgTypeDef;

/**
  * @brief UART IRQ callback function type definition
  */
typedef void (*UART_LLIRQCallback)(UART_TypeDef *Instance);

/**
  * @brief UART Transmission definition
  */
typedef struct __Uart_TransTypeDef {
    uint8_t *buf;                   /*!< Uart Transmission Buffer Pointer   */
    uint16_t size;                  /*!< Uart Transmission Buffer Size      */
    uint16_t cnt;                   /*!< Uart Transmission Counter          */
    UART_LLIRQCallback isr;         /*!< Interrupt Service Routine          */
    UART_StateETypeDef state;       /*!< UART Transmission State            */
#ifdef LL_DMA_MODULE_ENABLED
    DMA_ChannelETypeDef dma_ch;     /*!< Uart Transmission DMA Channel      */
#endif
} UART_TransTypeDef;

/**
  * @brief UART handle Structure definition
  */
typedef struct __UART_HandleTypeDef {
    volatile UART_TransTypeDef tx_ctrl;     /*!< UART Transmission Tx Control   */
    volatile UART_TransTypeDef rx_ctrl;     /*!< UART Transmission Rx Control   */

    UART_UserCallbackTypeDef user_callback; /*!< User Callback                  */
} UART_HandleTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup UART_LL_Exported_Functions
  * @{
  */

/** @addtogroup UART_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_UART_Init(UART_TypeDef *Instance, UART_InitTypeDef *init);
LL_StatusETypeDef LL_UART_DeInit(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_Reset(UART_TypeDef *Instance);
void LL_UART_MspInit(UART_TypeDef *Instance);
void LL_UART_MspDeInit(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_RegisterCallback(UART_TypeDef *Instance, UART_UserCallbackIdETypeDef CallbackID, UART_UserCallback pCallback);
LL_StatusETypeDef LL_UART_UnRegisterCallback(UART_TypeDef *Instance, UART_UserCallbackIdETypeDef CallbackID);
/**
  * @}
  */


/** @addtogroup UART_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_UART_Transmit_CPU(UART_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout);
LL_StatusETypeDef LL_UART_Receive_CPU(UART_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout);

LL_StatusETypeDef LL_UART_Transmit_IT(UART_TypeDef *Instance, uint8_t *buf, uint16_t size);
LL_StatusETypeDef LL_UART_Receive_IT(UART_TypeDef *Instance, uint8_t *buf, uint16_t size);

#ifdef LL_DMA_MODULE_ENABLED
LL_StatusETypeDef LL_UART_Transmit_DMA(UART_TypeDef *Instance, uint8_t *buf, uint16_t size);
LL_StatusETypeDef LL_UART_Receive_DMA(UART_TypeDef *Instance, uint8_t *buf, uint16_t size);
#endif
/**
  * @}
  */


/** @addtogroup UART_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_UART_AbortTransmit_CPU(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_AbortReceive_CPU(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_AbortTransmit_IT(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_AbortReceive_IT(UART_TypeDef *Instance);

LL_StatusETypeDef LL_Uart_TxExtAddrCfg(UART_TypeDef *Instance, uint8_t tx_addr_ext);
LL_StatusETypeDef LL_UART_RS485Cfg(UART_TypeDef *Instance, UART_Rs485CfgTypeDef *cfg);
LL_StatusETypeDef LL_UART_ReceiverTimeout_Config(UART_TypeDef *Instance, uint16_t TimeoutValue);
LL_StatusETypeDef LL_UART_EnableReceiverTimeout(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_DisableReceiverTimeout(UART_TypeDef *Instance);
LL_StatusETypeDef LL_UART_AutoBaudRateCfg(UART_TypeDef *Instance, UART_AutoBaudCfgTypeDef *cfg, uint32_t timeout);

UART_HandleTypeDef *LL_UART_Handle_Get(UART_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup UART_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_UART_IRQHandler(UART_TypeDef *Instance);

void LL_UART_AutoBaudRateErrCallback(UART_TypeDef *Instance);
void LL_UART_RxAddrMatchCallback(UART_TypeDef *Instance);
void LL_UART_TxIdleDoneCallback(UART_TypeDef *Instance);
void LL_UART_TxBreakDoneCallback(UART_TypeDef *Instance);
void LL_UART_TxDoneCallback(UART_TypeDef *Instance);
void LL_UART_RxTimeoutCallback(UART_TypeDef *Instance);
void LL_UART_RxBreakCallback(UART_TypeDef *Instance);
void LL_UART_FrameErrCallback(UART_TypeDef *Instance);
void LL_UART_ParityErrCallback(UART_TypeDef *Instance);
void LL_UART_NoiseDetectCallback(UART_TypeDef *Instance);
void LL_UART_RxIdleDoneCallback(UART_TypeDef *Instance);
void LL_UART_TxFIFOOverFlowCallback(UART_TypeDef *Instance);
void LL_UART_RxFIFOUnderFlowCallback(UART_TypeDef *Instance);
void LL_UART_RxFIFOOverFlowCallback(UART_TypeDef *Instance);
void LL_UART_TxFIFOEmptyCallback(UART_TypeDef *Instance);
void LL_UART_RxFIFOFullCallback(UART_TypeDef *Instance);

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

#endif /* _TAE32G58XX_LL_UART_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

