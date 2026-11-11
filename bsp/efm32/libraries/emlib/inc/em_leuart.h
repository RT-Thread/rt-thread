/***************************************************************************//**
 * @file
 * @brief Low Energy Universal Asynchronous Receiver/Transmitter (LEUART)
 *   peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EM_LEUART_H
#define __EM_LEUART_H

#include <stdbool.h>
#include "em_part.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup LEUART
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Databit selection. */
typedef enum
{
  leuartDatabits8 = LEUART_CTRL_DATABITS_EIGHT,     /**< 8 databits. */
  leuartDatabits9 = LEUART_CTRL_DATABITS_NINE       /**< 9 databits. */
} LEUART_Databits_TypeDef;


/** Enable selection. */
typedef enum
{
  /** Disable both receiver and transmitter. */
  leuartDisable  = 0x0,

  /** Enable receiver only, transmitter disabled. */
  leuartEnableRx = LEUART_CMD_RXEN,

  /** Enable transmitter only, receiver disabled. */
  leuartEnableTx = LEUART_CMD_TXEN,

  /** Enable both receiver and transmitter. */
  leuartEnable   = (LEUART_CMD_RXEN | LEUART_CMD_TXEN)
} LEUART_Enable_TypeDef;


/** Parity selection. */
typedef enum
{
  leuartNoParity   = LEUART_CTRL_PARITY_NONE,    /**< No parity. */
  leuartEvenParity = LEUART_CTRL_PARITY_EVEN,    /**< Even parity. */
  leuartOddParity  = LEUART_CTRL_PARITY_ODD      /**< Odd parity. */
} LEUART_Parity_TypeDef;


/** Stopbits selection. */
typedef enum
{
  leuartStopbits1 = LEUART_CTRL_STOPBITS_ONE,           /**< 1 stopbits. */
  leuartStopbits2 = LEUART_CTRL_STOPBITS_TWO            /**< 2 stopbits. */
} LEUART_Stopbits_TypeDef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Init structure. */
typedef struct
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  LEUART_Enable_TypeDef   enable;

  /**
   * LEUART reference clock assumed when configuring baudrate setup. Set
   * it to 0 if currently configurated reference clock shall be used.
   */
  uint32_t                refFreq;

  /** Desired baudrate. */
  uint32_t                baudrate;

  /** Number of databits in frame. */
  LEUART_Databits_TypeDef databits;

  /** Parity mode to use. */
  LEUART_Parity_TypeDef   parity;

  /** Number of stopbits to use. */
  LEUART_Stopbits_TypeDef stopbits;
} LEUART_Init_TypeDef;

/** Default config for LEUART init structure. */
#define LEUART_INIT_DEFAULT                                                                   \
  { leuartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                 /* Use current configured reference clock for configuring baudrate. */ \
    9600,              /* 9600 bits/s. */                                                     \
    leuartDatabits8,   /* 8 databits. */                                                      \
    leuartNoParity,    /* No parity. */                                                       \
    leuartStopbits1    /* 1 stopbit. */                                                       \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

uint32_t LEUART_BaudrateCalc(uint32_t refFreq, uint32_t clkdiv);
uint32_t LEUART_BaudrateGet(LEUART_TypeDef *leuart);
void LEUART_BaudrateSet(LEUART_TypeDef *leuart,
                        uint32_t refFreq,
                        uint32_t baudrate);
void LEUART_Enable(LEUART_TypeDef *leuart, LEUART_Enable_TypeDef enable);
void LEUART_FreezeEnable(LEUART_TypeDef *leuart, bool enable);
void LEUART_Init(LEUART_TypeDef *leuart, LEUART_Init_TypeDef *init);


/***************************************************************************//**
 * @brief
 *   Clear one or more pending LEUART interrupts.
 *
 * @param[in] leuart
 *   Pointer to LEUART peripheral register block.
 *
 * @param[in] flags
 *   Pending LEUART interrupt source to clear. Use a bitwise logic OR
 *   combination of valid interrupt flags for the LEUART module (LEUART_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LEUART_IntClear(LEUART_TypeDef *leuart, uint32_t flags)
{
  leuart->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more LEUART interrupts.
 *
 * @param[in] leuart
 *   Pointer to LEUART peripheral register block.
 *
 * @param[in] flags
 *   LEUART interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the LEUART module (LEUART_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LEUART_IntDisable(LEUART_TypeDef *leuart, uint32_t flags)
{
  leuart->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more LEUART interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using LEUART_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] leuart
 *   Pointer to LEUART peripheral register block.
 *
 * @param[in] flags
 *   LEUART interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the LEUART module (LEUART_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LEUART_IntEnable(LEUART_TypeDef *leuart, uint32_t flags)
{
  leuart->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending LEUART interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] leuart
 *   Pointer to LEUART peripheral register block.
 *
 * @return
 *   LEUART interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the LEUART module (LEUART_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t LEUART_IntGet(LEUART_TypeDef *leuart)
{
  return(leuart->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending LEUART interrupts from SW.
 *
 * @param[in] leuart
 *   Pointer to LEUART peripheral register block.
 *
 * @param[in] flags
 *   LEUART interrupt sources to set to pending. Use a bitwise logic OR
 *   combination of valid interrupt flags for the LEUART module (LEUART_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LEUART_IntSet(LEUART_TypeDef *leuart, uint32_t flags)
{
  leuart->IFS = flags;
}

void LEUART_Reset(LEUART_TypeDef *leuart);
uint8_t LEUART_Rx(LEUART_TypeDef *leuart);
uint16_t LEUART_RxExt(LEUART_TypeDef *leuart);
void LEUART_Tx(LEUART_TypeDef *leuart, uint8_t data);
void LEUART_TxExt(LEUART_TypeDef *leuart, uint16_t data);


/** @} (end addtogroup LEUART) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_LEUART_H */
