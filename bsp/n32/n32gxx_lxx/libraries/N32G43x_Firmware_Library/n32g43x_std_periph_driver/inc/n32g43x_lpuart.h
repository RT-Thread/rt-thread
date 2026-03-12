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
 * @file n32g43x_lpuart.h
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G43x_LPUART_H__
#define __N32G43x_LPUART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g43x.h"

/** @addtogroup N32G43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup LPUART
 * @{
 */

/** @addtogroup LPUART_Exported_Types
 * @{
 */

/**
 * @brief  LPUART Init Structure definition
 */

typedef struct
{
    uint32_t BaudRate; /*!< This member configures the LPUART communication baud rate.
                                  The baud rate is computed using the following formula:
                                   - IntegerDivider = ((CLK) / (LPUART_InitStruct->BaudRate)))
                                   - FractionalDivider */

    uint16_t Parity; /*!< Specifies the parity mode.
                                This parameter can be a value of @ref Parity
                                @note When parity is enabled, the computed parity is inserted
                                      at the MSB position of the transmitted data (only support
                                      8 data bits). */

    uint16_t Mode; /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                              This parameter can be a value of @ref Mode */

    uint16_t RtsThreshold; /* Specifies RTS Threshold.
                                    This parameter can be a value of @ref RtsThreshold */

    uint16_t HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                             or disabled.
                                             This parameter can be a value of @ref LPUART_Hardware_Flow_Control */
} LPUART_InitType;

/**
 * @}
 */

/** @addtogroup LPUART_Exported_Constants
 * @{
 */

/** @addtogroup Parity
 * @{
 */

#define LPUART_PE_NO             ((uint16_t)0x0008)
#define LPUART_PE_EVEN           ((uint16_t)0x0000)
#define LPUART_PE_ODD            ((uint16_t)0x0001)
#define IS_LPUART_PARITY(PARITY) (((PARITY) == LPUART_PE_NO) || ((PARITY) == LPUART_PE_EVEN) || ((PARITY) == LPUART_PE_ODD))
/**
 * @}
 */

/** @addtogroup Mode
 * @{
 */

#define LPUART_MODE_RX       ((uint16_t)0x0000)
#define LPUART_MODE_TX       ((uint16_t)0x0002)
#define IS_LPUART_MODE(MODE) (((MODE) == LPUART_MODE_RX) || ((MODE) == LPUART_MODE_TX))
/**
 * @}
 */

/** @addtogroup RtsThreshold
 * @{
 */

#define LPUART_RTSTH_FIFOHF       ((uint16_t)0x0000)
#define LPUART_RTSTH_FIFO3QF      ((uint16_t)0x0100)
#define LPUART_RTSTH_FIFOFU       ((uint16_t)0x0200)
#define IS_LPUART_RTSTHRESHOLD(RTSTHRESHOLD)                                                                                \
    (((RTSTHRESHOLD) == LPUART_RTSTH_FIFOHF) || ((RTSTHRESHOLD) == LPUART_RTSTH_FIFO3QF) || ((RTSTHRESHOLD) == LPUART_RTSTH_FIFOFU))
/**
 * @}
 */

/** @addtogroup Hardware_Flow_Control
 * @{
 */
#define LPUART_HFCTRL_NONE    ((uint16_t)0x0000)
#define LPUART_HFCTRL_CTS     ((uint16_t)0x0400)
#define LPUART_HFCTRL_RTS     ((uint16_t)0x0800)
#define LPUART_HFCTRL_RTS_CTS ((uint16_t)0x0C00)
#define IS_LPUART_HARDWARE_FLOW_CONTROL(CONTROL)                                                                        \
    (((CONTROL) == LPUART_HFCTRL_NONE) || ((CONTROL) == LPUART_HFCTRL_RTS) || ((CONTROL) == LPUART_HFCTRL_CTS)          \
     || ((CONTROL) == LPUART_HFCTRL_RTS_CTS))
/**
 * @}
 */

/** @addtogroup LPUART_Interrupt_definition
 * @{
 */

#define LPUART_INT_PE      ((uint16_t)0x0001)
#define LPUART_INT_TXC     ((uint16_t)0x0102)
#define LPUART_INT_FIFO_OV ((uint16_t)0x0204)
#define LPUART_INT_FIFO_FU ((uint16_t)0x0308)
#define LPUART_INT_FIFO_HF ((uint16_t)0x0410)
#define LPUART_INT_FIFO_NE ((uint16_t)0x0520)
#define LPUART_INT_WUF     ((uint16_t)0x0640)
#define IS_LPUART_CFG_INT(IT)                                                                                           \
    (((IT) == LPUART_INT_PE) || ((IT) == LPUART_INT_TXC) || ((IT) == LPUART_INT_FIFO_OV) || ((IT) == LPUART_INT_FIFO_FU)       \
     || ((IT) == LPUART_INT_FIFO_HF) || ((IT) == LPUART_INT_FIFO_NE) || ((IT) == LPUART_INT_WUF))
#define IS_LPUART_GET_INT(IT)                                                                                           \
    (((IT) == LPUART_INT_PE) || ((IT) == LPUART_INT_TXC) || ((IT) == LPUART_INT_FIFO_OV) || ((IT) == LPUART_INT_FIFO_FU)       \
     || ((IT) == LPUART_INT_FIFO_HF) || ((IT) == LPUART_INT_FIFO_NE) || ((IT) == LPUART_INT_WUF))
#define IS_LPUART_CLR_INT(IT)                                                                                           \
    (((IT) == LPUART_INT_PE) || ((IT) == LPUART_INT_TXC) || ((IT) == LPUART_INT_FIFO_OV) || ((IT) == LPUART_INT_FIFO_FU)      \
     || ((IT) == LPUART_INT_FIFO_HF) || ((IT) == LPUART_INT_FIFO_NE) || ((IT) == LPUART_INT_WUF))
/**
 * @}
 */

/** @addtogroup LPUART_DMA_Requests
 * @{
 */

#define LPUART_DMAREQ_TX         ((uint16_t)0x0020)
#define LPUART_DMAREQ_RX         ((uint16_t)0x0040)
#define IS_LPUART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFF9F) == (uint16_t)0x00) && ((DMAREQ) != (uint16_t)0x00))

/**
 * @}
 */

/** @addtogroup LPUART_WakeUp_methods
 * @{
 */

#define LPUART_WUSTP_STARTBIT    ((uint16_t)0x0000)
#define LPUART_WUSTP_RXNE        ((uint16_t)0x1000)
#define LPUART_WUSTP_BYTE        ((uint16_t)0x2000)
#define LPUART_WUSTP_FRAME       ((uint16_t)0x3000)
#define IS_LPUART_WAKEUP(WAKEUP)  \
    (((WAKEUP) == LPUART_WUSTP_STARTBIT) || ((WAKEUP) == LPUART_WUSTP_RXNE) || ((WAKEUP) == LPUART_WUSTP_BYTE) || ((WAKEUP) == LPUART_WUSTP_FRAME))
/**
 * @}
 */

/** @addtogroup LPUART_Sampling_methods
 * @{
 */

#define LPUART_SMPCNT_3B    ((uint16_t)0x0000)
#define LPUART_SMPCNT_1B    ((uint16_t)0x4000)
#define IS_LPUART_SAMPLING(SAMPLING) (((SAMPLING) == LPUART_SMPCNT_1B) || ((SAMPLING) == LPUART_SMPCNT_3B))
/**
 * @}
 */

/** @addtogroup LPUART_Flags
 * @{
 */

#define LPUART_FLAG_PEF      ((uint16_t)0x0001)
#define LPUART_FLAG_TXC      ((uint16_t)0x0002)
#define LPUART_FLAG_FIFO_OV  ((uint16_t)0x0004)
#define LPUART_FLAG_FIFO_FU  ((uint16_t)0x0008)
#define LPUART_FLAG_FIFO_HF  ((uint16_t)0x0010)
#define LPUART_FLAG_FIFO_NE  ((uint16_t)0x0020)
#define LPUART_FLAG_CTS      ((uint16_t)0x0040)
#define LPUART_FLAG_WUF      ((uint16_t)0x0080)
#define LPUART_FLAG_NF       ((uint16_t)0x0100)
#define IS_LPUART_FLAG(FLAG)                                                                                            \
    (((FLAG) == LPUART_FLAG_PEF) || ((FLAG) == LPUART_FLAG_TXC) || ((FLAG) == LPUART_FLAG_FIFO_OV)                           \
     || ((FLAG) == LPUART_FLAG_FIFO_FU) || ((FLAG) == LPUART_FLAG_FIFO_HF) || ((FLAG) == LPUART_FLAG_FIFO_NE)                   \
     || ((FLAG) == LPUART_FLAG_CTS) || ((FLAG) == LPUART_FLAG_WUF) || ((FLAG) == LPUART_FLAG_NF))

#define IS_LPUART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFE40) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_LPUART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x010000))

#define IS_LPUART_DATA(DATA)         ((DATA) <= 0xFF)

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup LPUART_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup LPUART_Exported_Functions
 * @{
 */

void LPUART_DeInit(void);
void LPUART_Init(LPUART_InitType* LPUART_InitStruct);
void LPUART_StructInit(LPUART_InitType* LPUART_InitStruct);
void LPUART_FlushRxFifo(void);
void LPUART_ConfigInt(uint16_t LPUART_INT, FunctionalState Cmd);
void LPUART_EnableDMA(uint16_t LPUART_DMAReq, FunctionalState Cmd);
void LPUART_ConfigWakeUpMethod(uint16_t LPUART_WakeUpMethod);
void LPUART_EnableWakeUpStop(FunctionalState Cmd);
void LPUART_ConfigSamplingMethod(uint16_t LPUART_SamplingMethod);
void LPUART_EnableLoopBack(FunctionalState Cmd);
void LPUART_SendData(uint8_t Data);
uint8_t LPUART_ReceiveData(void);
void LPUART_ConfigWakeUpData(uint32_t LPUART_WakeUpData);
FlagStatus LPUART_GetFlagStatus(uint16_t LPUART_FLAG);
void LPUART_ClrFlag(uint16_t LPUART_FLAG);
INTStatus LPUART_GetIntStatus(uint16_t LPUART_INT);
void LPUART_ClrIntPendingBit(uint16_t LPART_INT);

#ifdef __cplusplus
}
#endif

#endif /* __N32G43x_LPUART_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
