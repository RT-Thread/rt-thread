/*!
 * @file        apm32f0xx_usart.h
 *
 * @brief       This file contains all the functions prototypes for the USART firmware library
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __APM32F0XX_USART_H
#define __APM32F0XX_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup USART_Driver USART Driver
  @{
*/

/** @defgroup USART_Macros Macros
  @{
*/

/** Macros description */
#define USART_MACROS      1

/**@} end of group USART_Macros*/

/** @defgroup USART_Enumerations Enumerations
  @{
*/

/**
 * @brief   USART Word Length define
 */
typedef enum
{
    USART_WORD_LEN_8B = 0,            /*!< 8-bit data length */
    USART_WORD_LEN_9B = BIT12,        /*!< 9-bit data length */
    USART_WORD_LEN_7B = BIT12 | BIT28 /*!< only available for APM32F072 and APM32F030 devices */
} USART_WORD_LEN_T;

/**
 * @brief   USART Stop bits define
 */
typedef enum
{
    USART_STOP_BIT_1    = 0,             /*!< 1-bit stop bit */
    USART_STOP_BIT_2    = BIT13,         /*!< 2-bit stop bit */
    USART_STOP_BIT_1_5  = BIT12 | BIT13  /*!< 1.5-bit stop bit */
} USART_STOP_BITS_T;

/**
 * @brief   USART Parity define
 */
typedef enum
{
    USART_PARITY_NONE   = 0,            /*!< Disable parity control */
    USART_PARITY_EVEN   = BIT10,        /*!< Enable even parity control */
    USART_PARITY_ODD    = BIT10 | BIT9  /*!< Enable odd parity control*/
} USART_PARITY_T;

/**
 * @brief   USART mode define
 */
typedef enum
{
    USART_MODE_RX       = BIT2,        /*!< Enable USART Receive mode */
    USART_MODE_TX       = BIT3,        /*!< Enable USART transmit mode */
    USART_MODE_TX_RX    = BIT2 | BIT3  /*!< Enable USART receive and transmit mode */
} USART_MODE_T;

/**
 * @brief   USART hardware flow control define
 */
typedef enum
{
    USART_FLOW_CTRL_NONE    = 0,           /*!< Disable hardware flow control */
    USART_FLOW_CTRL_RTS     = BIT8,        /*!< Enable RTS hardware flow control */
    USART_FLOW_CTRL_CTS     = BIT9,        /*!< Enable CTS hardware flow control */
    USART_FLOW_CTRL_RTS_CTS = BIT8 | BIT9  /*!< Enable RTS and CTS hardware flow control */
} USART_HARDWARE_FLOW_CTRL_T;

/**
 * @brief    USART synchronization clock enable/disable
 */
typedef enum
{
    USART_CLKEN_DISABLE     = ((uint8_t)0),   /*!< Disable usart clock */
    USART_CLKEN_ENABLE      = ((uint8_t)1)    /*!< Enable usart clock */
} USART_CLKEN_T;

/**
 * @brief    USART Clock polarity define
 */
typedef enum
{
    USART_CLKPOL_LOW        = ((uint8_t)0),  /*!< Set clock polarity to low */
    USART_CLKPOL_HIGH       = ((uint8_t)1)   /*!< Set clock polarity to high */
} USART_CLKPOL_T;

/**
 * @brief    USART Clock phase define
 */
typedef enum
{
    USART_CLKPHA_1EDGE      = ((uint8_t)0),  /*!< Set usart to sample at the edge of the first clock */
    USART_CLKPHA_2EDGE      = ((uint8_t)1)   /*!< Set usart to sample at the edge of the second clock */
} USART_CLKPHA_T;

/**
 * @brief    USART Last bit clock pulse enable
 */
typedef enum
{
    USART_LBCP_DISABLE      = ((uint8_t)0),  /*!< Disable output last bit clock pulse */
    USART_LBCP_ENABLE       = ((uint8_t)1)   /*!< Enable output last bit clock pulse */
} USART_LBCP_T;

/**
 * @brief   USART DMA requests
 */
typedef enum
{
    USART_DMA_REQUEST_RX    = BIT6,  /*!< USART DMA receive request */
    USART_DMA_REQUEST_TX    = BIT7   /*!< USART DMA transmit request */
} USART_DMA_REQUEST_T;

/**
 * @brief   USART DMA reception error
 */
typedef enum
{
    USART_DMA_RXERR_ENABLE  = ((uint8_t)0),  /*!< USART DMA reception error enable */
    USART_DMA_RXERR_DISABLE = ((uint8_t)1)   /*!< USART DMA reception error disable */
} USART_DMA_RXERR_T;

/**
 * @brief    USART wakeup method
 */
typedef enum
{
    USART_WAKEUP_IDLE_LINE      = ((uint8_t)0),  /*!< WakeUp by an idle line detection */
    USART_WAKEUP_ADDRESS_MARK   = ((uint8_t)1)   /*!< WakeUp by an address mark */
} USART_WAKEUP_T;

/**
 * @brief    USART LIN break detection length
 */
typedef enum
{
    USART_BREAK_LENGTH_10B   = ((uint8_t)0),  /*!< 10-bit break detection */
    USART_BREAK_LENGTH_11B   = ((uint8_t)1)   /*!< 11-bit break detection */
} USART_BREAK_LENGTH_T;

/**
 * @brief    USART address mode
 */
typedef enum
{
    USART_ADDRESS_MODE_4B   = ((uint8_t)0),  /*!< 4-bit address detection */
    USART_ADDRESS_MODE_7B   = ((uint8_t)1)   /*!< 7-bit address detection */
} USART_ADDRESS_MODE_T;

/**
 * @brief    USART address mode, only available for APM32F072 devices
 */
typedef enum
{
    USART_WAKEUP_SOURCE_ADDRESS = ((uint8_t)0),  /*!< usart wakeup by address */
    USART_WAKEUP_SOURCE_START   = ((uint8_t)2),  /*!< usart wakeup by start bit */
    USART_WAKEUP_SOURCE_RXNE    = ((uint8_t)3)   /*!< usart wakeup by RXNE */
} USART_WAKEUP_SOURCE_T;

/**
 * @brief    USART driver enable polarity select
 */
typedef enum
{
    USART_DE_POL_HIGH       = ((uint8_t)0),  /*!< driver enable polarity is high */
    USART_DE_POL_LOW        = ((uint8_t)1)   /*!< driver enable polarity is low */
} USART_DE_POL_T;

/**
 * @brief    USART inversion Pins
 */
typedef enum
{
    USART_INVERSION_RX       = BIT16,       /*!< usart RX Pins active level inversion */
    USART_INVERSION_TX       = BIT17,       /*!< usart TX Pins active level inversion */
    USART_INVERSION_TX_RX    = BIT16 | BIT17 /*!< usart RX TX Pins active level inversion */
} USART_INVERSION_T;

/**
 * @brief    USART IrDA Low Power
 */
typedef enum
{
    USART_IRDA_MODE_NORMAL     = ((uint8_t)0),  /*!< usart irda works in normal mode */
    USART_IRDA_MODE_LOWPOWER   = ((uint8_t)1)   /*!< usart irda works in low-power mode */
} USART_IRDA_MODE_T;

/**
 * @brief    USART auto baud rate mode
 */
typedef enum
{
    USART_AUTO_BAUD_RATE_STARTBIT     = ((uint8_t)0x00),  /*!< auto-baud measure start bit */
    USART_AUTO_BAUD_RATE_FALLINGEDGE  = ((uint8_t)0x01)   /*!< auto-baud measure falling edge */
} USART_AUTO_BAUD_RATE_T;

/**
 * @brief    USART  over detection  disable
 */
typedef enum
{
    USART_OVER_DETECTION_ENABLE     = ((uint8_t)0),  /*!< enable overrun detection */
    USART_OVER_DETECTION_DISABLE    = ((uint8_t)1)   /*!< disable overrun detection */
} USART_OVER_DETECTION_T;

/**
 * @brief   USART request
 */
typedef enum
{
    USART_REQUEST_ABRQ     = ((uint8_t)0x01),         /*!< Auto Baud Rate Request */
    USART_REQUEST_SBQ      = ((uint8_t)0x02),         /*!< Send Break Request */
    USART_REQUEST_MMQ      = ((uint8_t)0x04),         /*!< Mute Mode Request */
    USART_REQUEST_RDFQ     = ((uint8_t)0x08),         /*!< Receive data flush Request */
    USART_REQUEST_TDFQ     = ((uint8_t)0x10)          /*!< Transmit data flush Request */
} USART_REQUEST_T;

/**
 * @brief    USART flag definition
 */
typedef enum
{
    USART_FLAG_RXENACKF    = ((uint32_t)0x00400000),  /*!< Receive Enable Acknowledge Flag */
    USART_FLAG_TXENACKF    = ((uint32_t)0x00200000),  /*!< Transmit Enable Acknowledge Flag */
    USART_FLAG_WAKEUP      = ((uint32_t)0x00100000),  /*!< Wake Up from stop mode Flag (Not for APM32F030 devices) */
    USART_FLAG_RWF         = ((uint32_t)0x00080000),  /*!< Send Break flag (Not for APM32F030 devices) */
    USART_FLAG_SBF         = ((uint32_t)0x00040000),  /*!< Send Break flag */
    USART_FLAG_CMF         = ((uint32_t)0X00020000),  /*!< Character match flag */
    USART_FLAG_BUSY        = ((uint32_t)0X00010000),  /*!< Busy flag */
    USART_FLAG_ABRTF       = ((uint32_t)0X00008000),  /*!< Auto baud rate flag */
    USART_FLAG_ABRTE       = ((uint32_t)0X00004000),  /*!< Auto baud rate error flag */
    USART_FLAG_EOBF        = ((uint32_t)0X00001000),  /*!< End of block flag (Not for APM32F030 devices) */
    USART_FLAG_RXTOF       = ((uint32_t)0X00000800),  /*!< Receive time out flag */
    USART_FLAG_CTSF        = ((uint32_t)0X00000400),  /*!< CTS Change flag */
    USART_FLAG_CTSIF       = ((uint32_t)0X00000200),  /*!< CTS interrupt flag */
    USART_FLAG_LBDF        = ((uint32_t)0x00000100),  /*!< LIN Break Detection Flag (Not for APM32F030 devices) */
    USART_FLAG_TXBE        = ((uint32_t)0X00000080),  /*!< Transmit data register empty flag */
    USART_FLAG_TXC         = ((uint32_t)0X00000040),  /*!< Transmission Complete flag */
    USART_FLAG_RXBNE       = ((uint32_t)0X00000020),  /*!< Receive data buffer not empty flag */
    USART_FLAG_IDLEF       = ((uint32_t)0X00000010),  /*!< Idle Line detection flag */
    USART_FLAG_OVRE        = ((uint32_t)0X00000008),  /*!< OverRun Error flag */
    USART_FLAG_NEF         = ((uint32_t)0X00000004),  /*!< Noise Error flag */
    USART_FLAG_FEF         = ((uint32_t)0X00000002),  /*!< Framing Error flag */
    USART_FLAG_PEF         = ((uint32_t)0X00000001),  /*!< Parity Error flag */
} USART_FLAG_T;

/**
 * @brief   USART interrupts source
 */
typedef enum
{
    USART_INT_WAKEUP       = ((uint32_t)0x00400000),  /*!< Wake up interrupt (Not for APM32F030 devices) */
    USART_INT_CMIE         = ((uint32_t)0x00004000),  /*!< Character match interrupt */
    USART_INT_EOBIE        = ((uint32_t)0x08000000),  /*!< End of Block interrupt (Not for APM32F030 devices) */
    USART_INT_RXTOIE       = ((uint32_t)0x04000000),  /*!< Receive time out interrupt */
    USART_INT_CTSIE        = ((uint32_t)0x00000400),  /*!< CTS change interrupt */
    USART_INT_LBDIE        = ((uint32_t)0X00000040),  /*!< LIN Break detection interrupt (Not for APM32F030 devices) */
    USART_INT_TXBEIE       = ((uint32_t)0x00000080),  /*!< Tansmit Data Register empty interrupt */
    USART_INT_TXCIE        = ((uint32_t)0x40000040),  /*!< Transmission complete interrupt */
    USART_INT_RXBNEIE      = ((uint32_t)0x00000020),  /*!< Receive Data buffer not empty interrupt */
    USART_INT_IDLEIE       = ((uint32_t)0x00000010),  /*!< Idle line detection interrupt */
    USART_INT_PEIE         = ((uint32_t)0x00000100),  /*!< Parity Error interrupt */
    USART_INT_ERRIE        = ((uint32_t)0x00000001),  /*!< Error interrupt */
} USART_INT_T;

/**
 * @brief   USART Interrupt flag definition
 */
typedef enum
{
    USART_INT_FLAG_WAKEUP  = ((uint32_t)0X00100000),  /*!< Wake up flag (Not for APM32F030 devices) */
    USART_INT_FLAG_CMF     = ((uint32_t)0X00020000),  /*!< Character match flag */
    USART_INT_FLAG_EOBF    = ((uint32_t)0X00001000),  /*!< End of block flag (Not for APM32F030 devices) */
    USART_INT_FLAG_RXTOF   = ((uint32_t)0X00000800),  /*!< Receive time out flag */
    USART_INT_FLAG_CTSIF   = ((uint32_t)0X00000200),  /*!< CTS interrupt flag */
    USART_INT_FLAG_LBDF    = ((uint32_t)0X00000100),  /*!< LIN Break detection flag (Not for APM32F030 devices) */
    USART_INT_FLAG_TXBE    = ((uint32_t)0X00000080),  /*!< Transmit data register empty flag */
    USART_INT_FLAG_TXC     = ((uint32_t)0X00000040),  /*!< Transmission Complete flag */
    USART_INT_FLAG_RXBNE   = ((uint32_t)0X00000020),  /*!< Receive data buffer not empty flag */
    USART_INT_FLAG_IDLE    = ((uint32_t)0X00000010),  /*!< Idle Line detection flag */
    USART_INT_FLAG_OVRE    = ((uint32_t)0X00000008),  /*!< OverRun Error flag */
    USART_INT_FLAG_NE      = ((uint32_t)0X00000004),  /*!< Noise Error flag */
    USART_INT_FLAG_FE      = ((uint32_t)0X00000002),  /*!< Framing Error flag */
    USART_INT_FLAG_PE      = ((uint32_t)0X00000001),  /*!< Parity Error flag */
} USART_INT_FLAG_T;

/**@} end of group USART_Enumerations*/

/** @defgroup USART_Structures Structures
  @{
*/

/**
 * @brief   USART Config struct definition
 */
typedef struct
{
    uint32_t                    baudRate;       /*!< Specifies the baud rate */
    USART_WORD_LEN_T            wordLength;     /*!< Specifies the word length */
    USART_STOP_BITS_T           stopBits;       /*!< Specifies the stop bits */
    USART_PARITY_T              parity;         /*!< Specifies the parity */
    USART_MODE_T                mode;           /*!< Specifies the mode */
    USART_HARDWARE_FLOW_CTRL_T  hardwareFlowCtrl;
} USART_Config_T;

/**
 * @brief   USART synchronous communication clock config struct definition
 */
typedef struct
{
    USART_CLKEN_T               enable;          /*!< Enable or Disable Clock */
    USART_CLKPOL_T              polarity;        /*!< Specifies the clock polarity */
    USART_CLKPHA_T              phase;           /*!< Specifies the clock phase */
    USART_LBCP_T                lastBitClock;    /*!< Enable or Disable last bit clock */
} USART_SyncClockConfig_T;

/**@} end of group USART_Structures*/

/** @defgroup USART_Variables Variables
  @{
  */

/**@} end of group USART_Variables */

/** @addtogroup USART_Functions Functions
  @{
*/

/* USART peripheral Reset and Configuration */
void USART_Reset(USART_T* usart);
void USART_Config(USART_T* uart, USART_Config_T* configStruct);
void USART_ConfigStructInit(USART_Config_T* configStruct);
void USART_ConfigSyncClock(USART_T* usart, USART_SyncClockConfig_T* SyncClockConfig);
void USART_ConfigSyncClockStructInit(USART_SyncClockConfig_T* SyncClockConfig);
void USART_Enable(USART_T* usart);
void USART_Disable(USART_T* usart);
void USART_EnableDirectionMode(USART_T* usart, USART_MODE_T mode);
void USART_DisableDirectionMode(USART_T* usart, USART_MODE_T mode);
void USART_ConfigDivider(USART_T* usart, uint8_t divider);  /*!< Not for APM32F030 devices */
void USART_EnableOverSampling8(USART_T* usart);
void USART_DisableOverSampling8(USART_T* usart);
void USART_EnableMSBFirst(USART_T* usart);
void USART_DisableMSBFirst(USART_T* usart);
void USART_EnableOneBitMethod(USART_T* usart);
void USART_DisableOneBitMethod(USART_T* usart);
void USART_EnableDataInv(USART_T* usart);
void USART_DisableDataInv(USART_T* usart);
void USART_EnableInvPin(USART_T* usart, USART_INVERSION_T invPin);
void USART_DisableInvPin(USART_T* usart, USART_INVERSION_T invPin);
void USART_EnableSWAPPin(USART_T* usart);
void USART_DisableSWAPPin(USART_T* usart);
void USART_EnableReceiverTimeOut(USART_T* usart);
void USART_DisableReceiverTimeOut(USART_T* usart);
void USART_ReceiverTimeOutValue(USART_T* usart, uint32_t timeOut);
void USART_EnableAutoBaudRate(USART_T* usart);
void USART_DisableAutoBaudRate(USART_T* usart);
void USART_ConfigAutoBaudRate(USART_T* usart, USART_AUTO_BAUD_RATE_T mode);
void USART_ConfigOverrunDetection(USART_T* usart, USART_OVER_DETECTION_T overDetection);

/* Stop mode */
void USART_EnableStopMode(USART_T* usart);
void USART_DisableStopMode(USART_T* usart);
void USART_ConfigStopModeWakeUpSource(USART_T* usart, USART_WAKEUP_SOURCE_T source);  /*!< Not for APM32F030 devices */

/* Address */
void USART_Address(USART_T* usart, uint8_t address);
void USART_ConfigAddressDetection(USART_T* usart, USART_ADDRESS_MODE_T address);

/* Transmit and receive */
void USART_TxData(USART_T* usart, uint16_t data);
uint16_t USART_RxData(USART_T* usart);

/* Mute mode */
void USART_EnableMuteMode(USART_T* usart);
void USART_DisableMuteMode(USART_T* usart);
void USART_ConfigMuteModeWakeUp(USART_T* usart, USART_WAKEUP_T wakeup);

/* LIN mode */
void USART_EnableLINmode(USART_T* usart);   /*!< Not for APM32F030 devices */
void USART_DisableLINmode(USART_T* usart);  /*!< Not for APM32F030 devices */
void USART_ConfigLINbreakDetectLength(USART_T* usart, USART_BREAK_LENGTH_T length);   /*!< Not for APM32F030 devices */

/* Half-duplex mode  */
void USART_EnableHalfDuplex(USART_T* usart);
void USART_DisableHalfDuplex(USART_T* usart);

/* Smartcard mode */
void USART_EnableSmartCard(USART_T* usart);   /*!< Not for APM32F030 devices */
void USART_DisableSmartCard(USART_T* usart);  /*!< Not for APM32F030 devices */
void USART_EnableSmartCardNACK(USART_T* usart);   /*!< Not for APM32F030 devices */
void USART_DisableSmartCardNACK(USART_T* usart);  /*!< Not for APM32F030 devices */
void USART_ConfigGuardTime(USART_T* usart, uint8_t guardTime);  /*!< Not for APM32F030 devices */
void USART_ConfigAutoCount(USART_T* usart, uint8_t autoCount);  /*!< Not for APM32F030 devices */
void USART_ConfigBlockSize(USART_T* usart, uint8_t blockSize);  /*!< Not for APM32F030 devices */

/* IrDA mode */
void USART_EnableIrDA(USART_T* usart);   /*!< Not for APM32F030 devices */
void USART_DisableIrDA(USART_T* usart);  /*!< Not for APM32F030 devices */
void USART_ConfigIrDAMode(USART_T* usart, USART_IRDA_MODE_T IrDAMode);  /*!< Not for APM32F030 devices */

/* Driver enable Configuration */
void USART_EnableDE(USART_T* usart);
void USART_DisableDE(USART_T* usart);
void USART_ConfigDEPolarity(USART_T* usart, USART_DE_POL_T polarity);
void USART_DEAssertionTimeValue(USART_T* usart, uint8_t value);
void USART_DEDeassertionTimeValue(USART_T* usart, uint8_t value);

/* DMA */
void USART_EnableDMA(USART_T* usart, uint32_t dmaReq);
void USART_DisableDMA(USART_T* usart, uint32_t dmaReq);
void USART_ConfigDMAReceptionError(USART_T* usart, USART_DMA_RXERR_T error);

/* Request */
void USART_EnableRequest(USART_T* usart, USART_REQUEST_T request);
void USART_DisableRequest(USART_T* usart, USART_REQUEST_T request);

/* Interrupt */
void USART_EnableInterrupt(USART_T* usart, USART_INT_T interrupt);
void USART_DisableInterrupt(USART_T* usart, USART_INT_T interrupt);
uint8_t USART_ReadIntFlag(USART_T* usart, USART_INT_FLAG_T flag);
void USART_ClearIntFlag(USART_T* usart, uint32_t flag);

/* Flag */
uint8_t USART_ReadStatusFlag(USART_T* usart, USART_FLAG_T flag);
void USART_ClearStatusFlag(USART_T* usart, uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_USART_H */

/**@} end of group USART_Functions */
/**@} end of group USART_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
