/***************************************************************************//**
* \file UART0.h
* \version 2.0
*
*  This file provides constants and parameter values for the UART component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(UART0_CY_SCB_UART_PDL_H)
#define UART0_CY_SCB_UART_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define UART0_DIRECTION  (3U)
#define UART0_ENABLE_RTS (0U)
#define UART0_ENABLE_CTS (0U)

/* UART direction enum */
#define UART0_RX    (0x1U)
#define UART0_TX    (0x2U)

#define UART0_ENABLE_RX  (0UL != (UART0_DIRECTION & UART0_RX))
#define UART0_ENABLE_TX  (0UL != (UART0_DIRECTION & UART0_TX))


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component specific functions. */
void UART0_Start(void);

/* Basic functions */
__STATIC_INLINE cy_en_scb_uart_status_t UART0_Init(cy_stc_scb_uart_config_t const *config);
__STATIC_INLINE void UART0_DeInit(void);
__STATIC_INLINE void UART0_Enable(void);
__STATIC_INLINE void UART0_Disable(void);

/* Register callback. */
__STATIC_INLINE void UART0_RegisterCallback(cy_cb_scb_uart_handle_events_t callback);

/* Configuration change. */
#if (UART0_ENABLE_CTS)
__STATIC_INLINE void UART0_EnableCts(void);
__STATIC_INLINE void UART0_DisableCts(void);
#endif /* (UART0_ENABLE_CTS) */

#if (UART0_ENABLE_RTS)
__STATIC_INLINE void     UART0_SetRtsFifoLevel(uint32_t level);
__STATIC_INLINE uint32_t UART0_GetRtsFifoLevel(void);
#endif /* (UART0_ENABLE_RTS) */

__STATIC_INLINE void UART0_EnableSkipStart(void);
__STATIC_INLINE void UART0_DisableSkipStart(void);

#if (UART0_ENABLE_RX)
/* Low level: Receive direction. */
__STATIC_INLINE uint32_t UART0_Get(void);
__STATIC_INLINE uint32_t UART0_GetArray(void *buffer, uint32_t size);
__STATIC_INLINE void     UART0_GetArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t UART0_GetRxFifoStatus(void);
__STATIC_INLINE void     UART0_ClearRxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t UART0_GetNumInRxFifo(void);
__STATIC_INLINE void     UART0_ClearRxFifo(void);
#endif /* (UART0_ENABLE_RX) */

#if (UART0_ENABLE_TX)
/* Low level: Transmit direction. */
__STATIC_INLINE uint32_t UART0_Put(uint32_t data);
__STATIC_INLINE uint32_t UART0_PutArray(void *buffer, uint32_t size);
__STATIC_INLINE void     UART0_PutArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE void     UART0_PutString(char_t const string[]);
__STATIC_INLINE void     UART0_SendBreakBlocking(uint32_t breakWidth);
__STATIC_INLINE uint32_t UART0_GetTxFifoStatus(void);
__STATIC_INLINE void     UART0_ClearTxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t UART0_GetNumInTxFifo(void);
__STATIC_INLINE bool     UART0_IsTxComplete(void);
__STATIC_INLINE void     UART0_ClearTxFifo(void);
#endif /* (UART0_ENABLE_TX) */

#if (UART0_ENABLE_RX)
/* High level: Ring buffer functions. */
__STATIC_INLINE void     UART0_StartRingBuffer(void *buffer, uint32_t size);
__STATIC_INLINE void     UART0_StopRingBuffer(void);
__STATIC_INLINE void     UART0_ClearRingBuffer(void);
__STATIC_INLINE uint32_t UART0_GetNumInRingBuffer(void);

/* High level: Receive direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t UART0_Receive(void *buffer, uint32_t size);
__STATIC_INLINE void     UART0_AbortReceive(void);
__STATIC_INLINE uint32_t UART0_GetReceiveStatus(void);
__STATIC_INLINE uint32_t UART0_GetNumReceived(void);
#endif /* (UART0_ENABLE_RX) */

#if (UART0_ENABLE_TX)
/* High level: Transmit direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t UART0_Transmit(void *buffer, uint32_t size);
__STATIC_INLINE void     UART0_AbortTransmit(void);
__STATIC_INLINE uint32_t UART0_GetTransmitStatus(void);
__STATIC_INLINE uint32_t UART0_GetNumLeftToTransmit(void);
#endif /* (UART0_ENABLE_TX) */

/* Interrupt handler */
__STATIC_INLINE void UART0_Interrupt(void);
/** @} group_general */


/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t UART0_initVar;
extern cy_stc_scb_uart_config_t const UART0_config;
extern cy_stc_scb_uart_context_t UART0_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the hardware */
#define UART0_HW     ((CySCB_Type *) UART0_SCB__HW)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: UART0_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART0_Init(cy_stc_scb_uart_config_t const *config)
{
   return Cy_SCB_UART_Init(UART0_HW, config, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_DeInit(void)
{
    Cy_SCB_UART_DeInit(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_Enable(void)
{
    Cy_SCB_UART_Enable(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_Disable(void)
{
    Cy_SCB_UART_Disable(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_RegisterCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_RegisterCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_RegisterCallback(cy_cb_scb_uart_handle_events_t callback)
{
    Cy_SCB_UART_RegisterCallback(UART0_HW, callback, &UART0_context);
}


#if (UART0_ENABLE_CTS)
/*******************************************************************************
* Function Name: UART0_EnableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_EnableCts(void)
{
    Cy_SCB_UART_EnableCts(UART0_HW);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_DisableCts(void)
{
    Cy_SCB_UART_DisableCts(UART0_HW);
}
#endif /* (UART0_ENABLE_CTS) */


#if (UART0_ENABLE_RTS)
/*******************************************************************************
* Function Name: UART0_SetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_SetRtsFifoLevel(uint32_t level)
{
    Cy_SCB_UART_SetRtsFifoLevel(UART0_HW, level);
}


/*******************************************************************************
* Function Name: UART0_GetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetRtsFifoLevel(void)
{
    return Cy_SCB_UART_GetRtsFifoLevel(UART0_HW);
}
#endif /* (UART0_ENABLE_RTS) */


/*******************************************************************************
* Function Name: UART0_EnableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_EnableSkipStart(void)
{
    Cy_SCB_UART_EnableSkipStart(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_DisableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_DisableSkipStart(void)
{
    Cy_SCB_UART_DisableSkipStart(UART0_HW);
}


#if (UART0_ENABLE_RX)
/*******************************************************************************
* Function Name: UART0_Get
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Get() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_Get(void)
{
    return Cy_SCB_UART_Get(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_GetArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_GetArray(UART0_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART0_GetArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_GetArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_GetArrayBlocking(UART0_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART0_GetRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetRxFifoStatus(void)
{
    return Cy_SCB_UART_GetRxFifoStatus(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_ClearRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_ClearRxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearRxFifoStatus(UART0_HW, clearMask);
}


/*******************************************************************************
* Function Name: UART0_GetNumInRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetNumInRxFifo(void)
{
    return Cy_SCB_UART_GetNumInRxFifo(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_ClearRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_ClearRxFifo(void)
{
    Cy_SCB_UART_ClearRxFifo(UART0_HW);
}
#endif /* (UART0_ENABLE_RX) */


#if (UART0_ENABLE_TX)
/*******************************************************************************
* Function Name: UART0_Put
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Put() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_Put(uint32_t data)
{
    return Cy_SCB_UART_Put(UART0_HW,data);
}


/*******************************************************************************
* Function Name: UART0_PutArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_PutArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_PutArray(UART0_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART0_PutArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_PutArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_PutArrayBlocking(UART0_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART0_PutString
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutString() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_PutString(char_t const string[])
{
    Cy_SCB_UART_PutString(UART0_HW, string);
}


/*******************************************************************************
* Function Name: UART0_SendBreakBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SendBreakBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_SendBreakBlocking(uint32_t breakWidth)
{
    Cy_SCB_UART_SendBreakBlocking(UART0_HW, breakWidth);
}


/*******************************************************************************
* Function Name: UART0_GetTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetTxFifoStatus(void)
{
    return Cy_SCB_UART_GetTxFifoStatus(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_ClearTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_ClearTxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearTxFifoStatus(UART0_HW, clearMask);
}


/*******************************************************************************
* Function Name: UART0_GetNumInTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetNumInTxFifo(void)
{
    return Cy_SCB_UART_GetNumInTxFifo(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_IsTxComplete
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_IsTxComplete() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool UART0_IsTxComplete(void)
{
    return Cy_SCB_UART_IsTxComplete(UART0_HW);
}


/*******************************************************************************
* Function Name: UART0_ClearTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_ClearTxFifo(void)
{
    Cy_SCB_UART_ClearTxFifo(UART0_HW);
}
#endif /* (UART0_ENABLE_TX) */


#if (UART0_ENABLE_RX)
/*******************************************************************************
* Function Name: UART0_StartRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StartRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_StartRingBuffer(void *buffer, uint32_t size)
{
    Cy_SCB_UART_StartRingBuffer(UART0_HW, buffer, size, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_StopRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StopRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_StopRingBuffer(void)
{
    Cy_SCB_UART_StopRingBuffer(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_ClearRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_ClearRingBuffer(void)
{
    Cy_SCB_UART_ClearRingBuffer(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_GetNumInRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetNumInRingBuffer(void)
{
    return Cy_SCB_UART_GetNumInRingBuffer(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_Receive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Receive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART0_Receive(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Receive(UART0_HW, buffer, size, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_GetReceiveStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetReceiveStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetReceiveStatus(void)
{
    return Cy_SCB_UART_GetReceiveStatus(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_AbortReceive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortReceive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_AbortReceive(void)
{
    Cy_SCB_UART_AbortReceive(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_GetNumReceived
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumReceived() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetNumReceived(void)
{
    return Cy_SCB_UART_GetNumReceived(UART0_HW, &UART0_context);
}
#endif /* (UART0_ENABLE_RX) */


#if (UART0_ENABLE_TX)
/*******************************************************************************
* Function Name: UART0_Transmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Transmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART0_Transmit(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Transmit(UART0_HW, buffer, size, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_GetTransmitStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTransmitStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetTransmitStatus(void)
{
    return Cy_SCB_UART_GetTransmitStatus(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_AbortTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_AbortTransmit(void)
{
    Cy_SCB_UART_AbortTransmit(UART0_HW, &UART0_context);
}


/*******************************************************************************
* Function Name: UART0_GetNumLeftToTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumLeftToTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART0_GetNumLeftToTransmit(void)
{
    return Cy_SCB_UART_GetNumLeftToTransmit(UART0_HW, &UART0_context);
}
#endif /* (UART0_ENABLE_TX) */


/*******************************************************************************
* Function Name: UART0_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART0_Interrupt(void)
{
    Cy_SCB_UART_Interrupt(UART0_HW, &UART0_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* UART0_CY_SCB_UART_PDL_H */


/* [] END OF FILE */
