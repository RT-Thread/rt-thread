/***************************************************************************//**
 * @file
 * @brief Universal synchronous/asynchronous receiver/transmitter (USART/UART)
 *   peripheral API for EFM32.
 * @author Energy Micro AS
 * @version 1.3.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
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
#ifndef __EFM32_USART_H
#define __EFM32_USART_H

#include <stdbool.h>
#include "efm32.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup USART
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Databit selection. */
typedef enum
{
  usartDatabits4  = USART_FRAME_DATABITS_FOUR,     /**< 4 databits (not available for UART). */
  usartDatabits5  = USART_FRAME_DATABITS_FIVE,     /**< 5 databits (not available for UART). */
  usartDatabits6  = USART_FRAME_DATABITS_SIX,      /**< 6 databits (not available for UART). */
  usartDatabits7  = USART_FRAME_DATABITS_SEVEN,    /**< 7 databits (not available for UART). */
  usartDatabits8  = USART_FRAME_DATABITS_EIGHT,    /**< 8 databits. */
  usartDatabits9  = USART_FRAME_DATABITS_NINE,     /**< 9 databits. */
  usartDatabits10 = USART_FRAME_DATABITS_TEN,      /**< 10 databits (not available for UART). */
  usartDatabits11 = USART_FRAME_DATABITS_ELEVEN,   /**< 11 databits (not available for UART). */
  usartDatabits12 = USART_FRAME_DATABITS_TWELVE,   /**< 12 databits (not available for UART). */
  usartDatabits13 = USART_FRAME_DATABITS_THIRTEEN, /**< 13 databits (not available for UART). */
  usartDatabits14 = USART_FRAME_DATABITS_FOURTEEN, /**< 14 databits (not available for UART). */
  usartDatabits15 = USART_FRAME_DATABITS_FIFTEEN,  /**< 15 databits (not available for UART). */
  usartDatabits16 = USART_FRAME_DATABITS_SIXTEEN   /**< 16 databits (not available for UART). */
} USART_Databits_TypeDef;


/** Enable selection. */
typedef enum
{
  /** Disable both receiver and transmitter. */
  usartDisable  = 0x0,

  /** Enable receiver only, transmitter disabled. */
  usartEnableRx = USART_CMD_RXEN,

  /** Enable transmitter only, receiver disabled. */
  usartEnableTx = USART_CMD_TXEN,

  /** Enable both receiver and transmitter. */
  usartEnable   = (USART_CMD_RXEN | USART_CMD_TXEN)
} USART_Enable_TypeDef;


/** Oversampling selection, used for asynchronous operation. */
typedef enum
{
  usartOVS16 = USART_CTRL_OVS_X16,     /**< 16x oversampling (normal). */
  usartOVS8  = USART_CTRL_OVS_X8,      /**< 8x oversampling. */
  usartOVS6  = USART_CTRL_OVS_X6,      /**< 6x oversampling. */
  usartOVS4  = USART_CTRL_OVS_X4       /**< 4x oversampling. */
} USART_OVS_TypeDef;


/** Parity selection, mainly used for asynchronous operation. */
typedef enum
{
  usartNoParity   = USART_FRAME_PARITY_NONE,    /**< No parity. */
  usartEvenParity = USART_FRAME_PARITY_EVEN,    /**< Even parity. */
  usartOddParity  = USART_FRAME_PARITY_ODD      /**< Odd parity. */
} USART_Parity_TypeDef;


/** Stopbits selection, used for asynchronous operation. */
typedef enum
{
  usartStopbits0p5 = USART_FRAME_STOPBITS_HALF,        /**< 0.5 stopbits. */
  usartStopbits1   = USART_FRAME_STOPBITS_ONE,         /**< 1 stopbits. */
  usartStopbits1p5 = USART_FRAME_STOPBITS_ONEANDAHALF, /**< 1.5 stopbits. */
  usartStopbits2   = USART_FRAME_STOPBITS_TWO          /**< 2 stopbits. */
} USART_Stopbits_TypeDef;


/** Clock polarity/phase mode. */
typedef enum
{
  /** Clock idle low, sample on rising edge. */
  usartClockMode0 = USART_CTRL_CLKPOL_IDLELOW | USART_CTRL_CLKPHA_SAMPLELEADING,

  /** Clock idle low, sample on falling edge. */
  usartClockMode1 = USART_CTRL_CLKPOL_IDLELOW | USART_CTRL_CLKPHA_SAMPLETRAILING,

  /** Clock idle high, sample on falling edge. */
  usartClockMode2 = USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_CLKPHA_SAMPLELEADING,

  /** Clock idle high, sample on rising edge. */
  usartClockMode3 = USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_CLKPHA_SAMPLETRAILING
} USART_ClockMode_TypeDef;


/** Pulse width selection for IrDA mode. */
typedef enum
{
  /** IrDA pulse width is 1/16 for OVS=0 and 1/8 for OVS=1 */
  usartIrDAPwONE   = USART_IRCTRL_IRPW_ONE,

  /** IrDA pulse width is 2/16 for OVS=0 and 2/8 for OVS=1 */
  usartIrDAPwTWO   = USART_IRCTRL_IRPW_TWO,

  /** IrDA pulse width is 3/16 for OVS=0 and 3/8 for OVS=1 */
  usartIrDAPwTHREE = USART_IRCTRL_IRPW_THREE,

  /** IrDA pulse width is 4/16 for OVS=0 and 4/8 for OVS=1 */
  usartIrDAPwFOUR  = USART_IRCTRL_IRPW_FOUR
} USART_IrDAPw_Typedef;


/** PRS channel selection for IrDA mode. */
typedef enum
{
  usartIrDAPrsCh0 = USART_IRCTRL_IRPRSSEL_PRSCH0, /**< PRS channel 0 */
  usartIrDAPrsCh1 = USART_IRCTRL_IRPRSSEL_PRSCH1, /**< PRS channel 1 */
  usartIrDAPrsCh2 = USART_IRCTRL_IRPRSSEL_PRSCH2, /**< PRS channel 2 */
  usartIrDAPrsCh3 = USART_IRCTRL_IRPRSSEL_PRSCH3, /**< PRS channel 3 */
  usartIrDAPrsCh4 = USART_IRCTRL_IRPRSSEL_PRSCH4, /**< PRS channel 4 */
  usartIrDAPrsCh5 = USART_IRCTRL_IRPRSSEL_PRSCH5, /**< PRS channel 5 */
  usartIrDAPrsCh6 = USART_IRCTRL_IRPRSSEL_PRSCH6, /**< PRS channel 6 */
  usartIrDAPrsCh7 = USART_IRCTRL_IRPRSSEL_PRSCH7  /**< PRS channel 7 */
} USART_IrDAPrsSel_Typedef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Asynchronous mode init structure. */
typedef struct
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  USART_Enable_TypeDef enable;

  /**
   * USART/UART reference clock assumed when configuring baudrate setup. Set
   * it to 0 if currently configurated reference clock shall be used.
   */
  uint32_t          refFreq;

  /** Desired baudrate. */
  uint32_t          baudrate;

  /** Oversampling used. */
  USART_OVS_TypeDef oversampling;

  /** Number of databits in frame. Notice that UART modules only support 8 or
   * 9 databits. */
  USART_Databits_TypeDef databits;

  /** Parity mode to use. */
  USART_Parity_TypeDef   parity;

  /** Number of stopbits to use. */
  USART_Stopbits_TypeDef stopbits;
} USART_InitAsync_TypeDef;

/** Default config for USART async init structure. */
#define USART_INITASYNC_DEFAULT                                                              \
  { usartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                /* Use current configured reference clock for configuring baudrate. */ \
    115200,           /* 115200 bits/s. */                                                   \
    usartOVS16,       /* 16x oversampling. */                                                \
    usartDatabits8,   /* 8 databits. */                                                      \
    usartNoParity,    /* No parity. */                                                       \
    usartStopbits1    /* 1 stopbit. */                                                       \
  }


/** Synchronous mode init structure. */
typedef struct
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  USART_Enable_TypeDef enable;

  /**
   * USART/UART reference clock assumed when configuring baudrate setup. Set
   * it to 0 if currently configurated reference clock shall be used.
   */
  uint32_t                refFreq;

  /** Desired baudrate. */
  uint32_t                baudrate;

  /** Number of databits in frame. */
  USART_Databits_TypeDef  databits;

  /** Select if to operate in master or slave mode. */
  bool                    master;

  /** Select if to send most or least significant bit first. */
  bool                    msbf;

  /** Clock polarity/phase mode. */
  USART_ClockMode_TypeDef clockMode;
} USART_InitSync_TypeDef;

/** Default config for USART sync init structure. */
#define USART_INITSYNC_DEFAULT                                                                \
  { usartEnable,       /* Enable RX/TX when init completed. */                                \
    0,                 /* Use current configured reference clock for configuring baudrate. */ \
    1000000,           /* 1 Mbits/s. */                                                       \
    usartDatabits8,    /* 8 databits. */                                                      \
    true,              /* Master mode. */                                                     \
    false,             /* Send least significant bit first. */                                \
    usartClockMode0    /* Clock idle low, sample on rising edge. */                           \
  }


/** IrDA mode init structure. Inherited from asynchronous mode init structure */
typedef struct
{
  /** General Async initialization structure. */
  USART_InitAsync_TypeDef async;

  /** Set to invert Rx signal before IrDA demodulator. */
  bool                    irRxInv;

  /** Set to enable filter on IrDA demodulator. */
  bool                    irFilt;

  /** Configure the pulse width generated by the IrDA modulator as a fraction
   *  of the configured USART bit period. */
  USART_IrDAPw_Typedef irPw;

  /** Enable the PRS channel selected by irPrsSel as input to IrDA module
   *  instead of TX. */
  bool irPrsEn;

  /** A PRS can be used as input to the pulse modulator instead of TX.
   *  This value selects the channel to use. */
  USART_IrDAPrsSel_Typedef irPrsSel;
} USART_InitIrDA_TypeDef;


/** Default config for IrDA mode init structure. */
#define USART_INITIRDA_DEFAULT                                                                \
  {                                                                                           \
    { usartEnable,     /* Enable RX/TX when init completed. */                                \
      0,               /* Use current configured reference clock for configuring baudrate. */ \
      115200,          /* 115200 bits/s. */                                                   \
      usartOVS16,      /* 16x oversampling. */                                                \
      usartDatabits8,  /* 8 databits. */                                                      \
      usartEvenParity, /* Even parity. */                                                     \
      usartStopbits1   /* 1 stopbit. */                                                       \
    },                                                                                        \
    false,             /* Rx invert disabled. */                                              \
    false,             /* Filtering disabled. */                                              \
    usartIrDAPwTHREE,  /* Pulse width is set to ONE. */                                       \
    false,             /* Routing to PRS is disabled. */                                      \
    usartIrDAPrsCh0    /* PRS channel 0. */                                                   \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void USART_BaudrateAsyncSet(USART_TypeDef *usart,
                            uint32_t refFreq,
                            uint32_t baudrate,
                            USART_OVS_TypeDef ovs);
uint32_t USART_BaudrateCalc(uint32_t refFreq,
                            uint32_t clkdiv,
                            bool syncmode,
                            USART_OVS_TypeDef ovs);
uint32_t USART_BaudrateGet(USART_TypeDef *usart);
void USART_BaudrateSyncSet(USART_TypeDef *usart,
                           uint32_t refFreq,
                           uint32_t baudrate);
void USART_Enable(USART_TypeDef *usart, USART_Enable_TypeDef enable);
void USART_InitAsync(USART_TypeDef *usart, USART_InitAsync_TypeDef *init);
void USART_InitSync(USART_TypeDef *usart, USART_InitSync_TypeDef *init);
void USART_InitIrDA(USART_InitIrDA_TypeDef *init);


/***************************************************************************//**
 * @brief
 *   Clear one or more pending USART interrupts.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @param[in] flags
 *   Pending USART/UART interrupt source to clear. Use a logical OR combination
 *   of valid interrupt flags for the USART module (USART_IF_nnn).
 ******************************************************************************/
static __INLINE void USART_IntClear(USART_TypeDef *usart, uint32_t flags)
{
  usart->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more USART interrupts.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @param[in] flags
 *   USART/UART interrupt sources to disable. Use a logical OR combination of
 *   valid interrupt flags for the USART module (USART_IF_nnn).
 ******************************************************************************/
static __INLINE void USART_IntDisable(USART_TypeDef *usart, uint32_t flags)
{
  usart->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more USART interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using USART_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @param[in] flags
 *   USART/UART interrupt sources to enable. Use a logical OR combination of
 *   valid interrupt flags for the USART module (USART_IF_nnn).
 ******************************************************************************/
static __INLINE void USART_IntEnable(USART_TypeDef *usart, uint32_t flags)
{
  usart->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending USART interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @return
 *   USART/UART interrupt sources pending. A logical OR combination of valid
 *   interrupt flags for the USART module (USART_IF_nnn).
 ******************************************************************************/
static __INLINE uint32_t USART_IntGet(USART_TypeDef *usart)
{
  return usart->IF;
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending USART interrupts from SW.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @param[in] flags
 *   USART/UART interrupt sources to set to pending. Use a logical OR combination
 *   of valid interrupt flags for the USART module (USART_IF_nnn).
 ******************************************************************************/
static __INLINE void USART_IntSet(USART_TypeDef *usart, uint32_t flags)
{
  usart->IFS = flags;
}

void USART_Reset(USART_TypeDef *usart);
uint8_t USART_Rx(USART_TypeDef *usart);
uint16_t USART_RxDouble(USART_TypeDef *usart);
uint32_t USART_RxDoubleExt(USART_TypeDef *usart);
uint16_t USART_RxExt(USART_TypeDef *usart);
void USART_Tx(USART_TypeDef *usart, uint8_t data);
void USART_TxDouble(USART_TypeDef *usart, uint16_t data);
void USART_TxDoubleExt(USART_TypeDef *usart, uint32_t data);
void USART_TxExt(USART_TypeDef *usart, uint16_t data);


/** @} (end addtogroup USART) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_USART_H */
