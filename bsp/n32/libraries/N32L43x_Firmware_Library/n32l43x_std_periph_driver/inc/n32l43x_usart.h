/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l43x_usart.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32L43X_USART_H__
#define __N32L43X_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l43x.h"

/** @addtogroup n32l43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup USART
 * @{
 */

/** @addtogroup USART_Exported_Types
 * @{
 */

/**
 * @brief  USART Init Structure definition
 */

typedef struct
{
    uint32_t BaudRate; /*!< This member configures the USART communication baud rate.
                                  The baud rate is computed using the following formula:
                                   - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->BaudRate)))
                                   - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint16_t WordLength; /*!< Specifies the number of data bits transmitted or received in a frame.
                                    This parameter can be a value of @ref USART_Word_Length */

    uint16_t StopBits; /*!< Specifies the number of stop bits transmitted.
                                  This parameter can be a value of @ref USART_Stop_Bits */

    uint16_t Parity; /*!< Specifies the parity mode.
                                This parameter can be a value of @ref Parity
                                @note When parity is enabled, the computed parity is inserted
                                      at the MSB position of the transmitted data (9th bit when
                                      the word length is set to 9 data bits; 8th bit when the
                                      word length is set to 8 data bits). */

    uint16_t Mode; /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                              This parameter can be a value of @ref Mode */

    uint16_t HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                             or disabled.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitType;

/**
 * @brief  USART Clock Init Structure definition
 */

typedef struct
{
    uint16_t Clock; /*!< Specifies whether the USART clock is enabled or disabled.
                               This parameter can be a value of @ref Clock */

    uint16_t Polarity; /*!< Specifies the steady state value of the serial clock.
                              This parameter can be a value of @ref USART_Clock_Polarity */

    uint16_t Phase; /*!< Specifies the clock transition on which the bit capture is made.
                              This parameter can be a value of @ref USART_Clock_Phase */

    uint16_t LastBit; /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                 data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                 This parameter can be a value of @ref USART_Last_Bit */
} USART_ClockInitType;

/**
 * @}
 */

/** @addtogroup USART_Exported_Constants
 * @{
 */

#define IS_USART_ALL_PERIPH(PERIPH)                                                                                    \
    (((PERIPH) == USART1) || ((PERIPH) == USART2) || ((PERIPH) == USART3) || ((PERIPH) == UART4) || ((PERIPH) == UART5))

#define IS_USART_123_PERIPH(PERIPH) (((PERIPH) == USART1) || ((PERIPH) == USART2) || ((PERIPH) == USART3))

#define IS_USART_1234_PERIPH(PERIPH)                                                                                   \
    (((PERIPH) == USART1) || ((PERIPH) == USART2) || ((PERIPH) == USART3) || ((PERIPH) == UART4))
/** @addtogroup USART_Word_Length
 * @{
 */

#define USART_WL_8B ((uint16_t)0x0000)
#define USART_WL_9B ((uint16_t)0x1000)

#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WL_8B) || ((LENGTH) == USART_WL_9B))
/**
 * @}
 */

/** @addtogroup USART_Stop_Bits
 * @{
 */

#define USART_STPB_1   ((uint16_t)0x0000)
#define USART_STPB_0_5 ((uint16_t)0x1000)
#define USART_STPB_2   ((uint16_t)0x2000)
#define USART_STPB_1_5 ((uint16_t)0x3000)
#define IS_USART_STOPBITS(STOPBITS)                                                                                    \
    (((STOPBITS) == USART_STPB_1) || ((STOPBITS) == USART_STPB_0_5) || ((STOPBITS) == USART_STPB_2)                    \
     || ((STOPBITS) == USART_STPB_1_5))
/**
 * @}
 */

/** @addtogroup Parity
 * @{
 */

#define USART_PE_NO             ((uint16_t)0x0000)
#define USART_PE_EVEN           ((uint16_t)0x0400)
#define USART_PE_ODD            ((uint16_t)0x0600)
#define IS_USART_PARITY(PARITY) (((PARITY) == USART_PE_NO) || ((PARITY) == USART_PE_EVEN) || ((PARITY) == USART_PE_ODD))
/**
 * @}
 */

/** @addtogroup Mode
 * @{
 */

#define USART_MODE_RX       ((uint16_t)0x0004)
#define USART_MODE_TX       ((uint16_t)0x0008)
#define IS_USART_MODE(MODE) ((((MODE) & (uint16_t)0xFFF3) == 0x00) && ((MODE) != (uint16_t)0x00))
/**
 * @}
 */

/** @addtogroup USART_Hardware_Flow_Control
 * @{
 */
#define USART_HFCTRL_NONE    ((uint16_t)0x0000)
#define USART_HFCTRL_RTS     ((uint16_t)0x0100)
#define USART_HFCTRL_CTS     ((uint16_t)0x0200)
#define USART_HFCTRL_RTS_CTS ((uint16_t)0x0300)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)                                                                        \
    (((CONTROL) == USART_HFCTRL_NONE) || ((CONTROL) == USART_HFCTRL_RTS) || ((CONTROL) == USART_HFCTRL_CTS)            \
     || ((CONTROL) == USART_HFCTRL_RTS_CTS))
/**
 * @}
 */

/** @addtogroup Clock
 * @{
 */
#define USART_CLK_DISABLE     ((uint16_t)0x0000)
#define USART_CLK_ENABLE      ((uint16_t)0x0800)
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_CLK_DISABLE) || ((CLOCK) == USART_CLK_ENABLE))
/**
 * @}
 */

/** @addtogroup USART_Clock_Polarity
 * @{
 */

#define USART_CLKPOL_LOW    ((uint16_t)0x0000)
#define USART_CLKPOL_HIGH   ((uint16_t)0x0400)
#define IS_USART_CPOL(CPOL) (((CPOL) == USART_CLKPOL_LOW) || ((CPOL) == USART_CLKPOL_HIGH))

/**
 * @}
 */

/** @addtogroup USART_Clock_Phase
 * @{
 */

#define USART_CLKPHA_1EDGE  ((uint16_t)0x0000)
#define USART_CLKPHA_2EDGE  ((uint16_t)0x0200)
#define IS_USART_CPHA(CPHA) (((CPHA) == USART_CLKPHA_1EDGE) || ((CPHA) == USART_CLKPHA_2EDGE))

/**
 * @}
 */

/** @addtogroup USART_Last_Bit
 * @{
 */

#define USART_CLKLB_DISABLE       ((uint16_t)0x0000)
#define USART_CLKLB_ENABLE        ((uint16_t)0x0100)
#define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_CLKLB_DISABLE) || ((LASTBIT) == USART_CLKLB_ENABLE))
/**
 * @}
 */

/** @addtogroup USART_Interrupt_definition
 * @{
 */

#define USART_INT_PEF   ((uint16_t)0x0028)
#define USART_INT_TXDE  ((uint16_t)0x0727)
#define USART_INT_TXC   ((uint16_t)0x0626)
#define USART_INT_RXDNE ((uint16_t)0x0525)
#define USART_INT_IDLEF ((uint16_t)0x0424)
#define USART_INT_LINBD ((uint16_t)0x0846)
#define USART_INT_CTSF  ((uint16_t)0x096A)
#define USART_INT_ERRF  ((uint16_t)0x0060)
#define USART_INT_OREF  ((uint16_t)0x0360)
#define USART_INT_NEF   ((uint16_t)0x0260)
#define USART_INT_FEF   ((uint16_t)0x0160)
#define IS_USART_CFG_INT(IT)                                                                                           \
    (((IT) == USART_INT_PEF) || ((IT) == USART_INT_TXDE) || ((IT) == USART_INT_TXC) || ((IT) == USART_INT_RXDNE)       \
     || ((IT) == USART_INT_IDLEF) || ((IT) == USART_INT_LINBD) || ((IT) == USART_INT_CTSF)                             \
     || ((IT) == USART_INT_ERRF))
#define IS_USART_GET_INT(IT)                                                                                           \
    (((IT) == USART_INT_PEF) || ((IT) == USART_INT_TXDE) || ((IT) == USART_INT_TXC) || ((IT) == USART_INT_RXDNE)       \
     || ((IT) == USART_INT_IDLEF) || ((IT) == USART_INT_LINBD) || ((IT) == USART_INT_CTSF) || ((IT) == USART_INT_OREF) \
     || ((IT) == USART_INT_NEF) || ((IT) == USART_INT_FEF))
#define IS_USART_CLR_INT(IT)                                                                                           \
    (((IT) == USART_INT_TXC) || ((IT) == USART_INT_RXDNE) || ((IT) == USART_INT_LINBD) || ((IT) == USART_INT_CTSF))
/**
 * @}
 */

/** @addtogroup USART_DMA_Requests
 * @{
 */

#define USART_DMAREQ_TX         ((uint16_t)0x0080)
#define USART_DMAREQ_RX         ((uint16_t)0x0040)
#define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFF3F) == 0x00) && ((DMAREQ) != (uint16_t)0x00))

/**
 * @}
 */

/** @addtogroup USART_WakeUp_methods
 * @{
 */

#define USART_WUM_IDLELINE      ((uint16_t)0x0000)
#define USART_WUM_ADDRMASK      ((uint16_t)0x0800)
#define IS_USART_WAKEUP(WAKEUP) (((WAKEUP) == USART_WUM_IDLELINE) || ((WAKEUP) == USART_WUM_ADDRMASK))
/**
 * @}
 */

/** @addtogroup USART_LIN_Break_Detection_Length
 * @{
 */

#define USART_LINBDL_10B                         ((uint16_t)0x0000)
#define USART_LINBDL_11B                         ((uint16_t)0x0020)
#define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) (((LENGTH) == USART_LINBDL_10B) || ((LENGTH) == USART_LINBDL_11B))
/**
 * @}
 */

/** @addtogroup USART_IrDA_Low_Power
 * @{
 */

#define USART_IRDAMODE_LOWPPWER  ((uint16_t)0x0004)
#define USART_IRDAMODE_NORMAL    ((uint16_t)0x0000)
#define IS_USART_IRDA_MODE(MODE) (((MODE) == USART_IRDAMODE_LOWPPWER) || ((MODE) == USART_IRDAMODE_NORMAL))
/**
 * @}
 */

/** @addtogroup USART_Flags
 * @{
 */

#define USART_FLAG_CTSF  ((uint16_t)0x0200)
#define USART_FLAG_LINBD ((uint16_t)0x0100)
#define USART_FLAG_TXDE  ((uint16_t)0x0080)
#define USART_FLAG_TXC   ((uint16_t)0x0040)
#define USART_FLAG_RXDNE ((uint16_t)0x0020)
#define USART_FLAG_IDLEF ((uint16_t)0x0010)
#define USART_FLAG_OREF  ((uint16_t)0x0008)
#define USART_FLAG_NEF   ((uint16_t)0x0004)
#define USART_FLAG_FEF   ((uint16_t)0x0002)
#define USART_FLAG_PEF   ((uint16_t)0x0001)
#define IS_USART_FLAG(FLAG)                                                                                            \
    (((FLAG) == USART_FLAG_PEF) || ((FLAG) == USART_FLAG_TXDE) || ((FLAG) == USART_FLAG_TXC)                           \
     || ((FLAG) == USART_FLAG_RXDNE) || ((FLAG) == USART_FLAG_IDLEF) || ((FLAG) == USART_FLAG_LINBD)                   \
     || ((FLAG) == USART_FLAG_CTSF) || ((FLAG) == USART_FLAG_OREF) || ((FLAG) == USART_FLAG_NEF)                       \
     || ((FLAG) == USART_FLAG_FEF))

#define IS_USART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFC9F) == 0x00) && ((FLAG) != (uint16_t)0x00))
#define IS_USART_PERIPH_FLAG(PERIPH, USART_FLAG)                                                                       \
    ((((*(uint32_t*)&(PERIPH)) != UART4_BASE) && ((*(uint32_t*)&(PERIPH)) != UART5_BASE))                              \
     || ((USART_FLAG) != USART_FLAG_CTSF))
#define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x00337F99))
#define IS_USART_ADDRESS(ADDRESS)   ((ADDRESS) <= 0xF)
#define IS_USART_DATA(DATA)         ((DATA) <= 0x1FF)

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup USART_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup USART_Exported_Functions
 * @{
 */

void USART_DeInit(USART_Module* USARTx);
void USART_Init(USART_Module* USARTx, USART_InitType* USART_InitStruct);
void USART_StructInit(USART_InitType* USART_InitStruct);
void USART_ClockInit(USART_Module* USARTx, USART_ClockInitType* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitType* USART_ClockInitStruct);
void USART_Enable(USART_Module* USARTx, FunctionalState Cmd);
void USART_ConfigInt(USART_Module* USARTx, uint16_t USART_INT, FunctionalState Cmd);
void USART_EnableDMA(USART_Module* USARTx, uint16_t USART_DMAReq, FunctionalState Cmd);
void USART_SetAddr(USART_Module* USARTx, uint8_t USART_Addr);
void USART_ConfigWakeUpMode(USART_Module* USARTx, uint16_t USART_WakeUpMode);
void USART_EnableRcvWakeUp(USART_Module* USARTx, FunctionalState Cmd);
void USART_ConfigLINBreakDetectLength(USART_Module* USARTx, uint16_t USART_LINBreakDetectLength);
void USART_EnableLIN(USART_Module* USARTx, FunctionalState Cmd);
void USART_SendData(USART_Module* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_Module* USARTx);
void USART_SendBreak(USART_Module* USARTx);
void USART_SetGuardTime(USART_Module* USARTx, uint8_t USART_GuardTime);
void USART_SetPrescaler(USART_Module* USARTx, uint8_t USART_Prescaler);
void USART_EnableSmartCard(USART_Module* USARTx, FunctionalState Cmd);
void USART_SetSmartCardNACK(USART_Module* USARTx, FunctionalState Cmd);
void USART_EnableHalfDuplex(USART_Module* USARTx, FunctionalState Cmd);
void USART_ConfigIrDAMode(USART_Module* USARTx, uint16_t USART_IrDAMode);
void USART_EnableIrDA(USART_Module* USARTx, FunctionalState Cmd);
FlagStatus USART_GetFlagStatus(USART_Module* USARTx, uint16_t USART_FLAG);
void USART_ClrFlag(USART_Module* USARTx, uint16_t USART_FLAG);
INTStatus USART_GetIntStatus(USART_Module* USARTx, uint16_t USART_INT);
void USART_ClrIntPendingBit(USART_Module* USARTx, uint16_t USART_INT);

#ifdef __cplusplus
}
#endif

#endif /* __N32L43X_USART_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
