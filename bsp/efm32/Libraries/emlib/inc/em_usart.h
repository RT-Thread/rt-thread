/***************************************************************************//**
 * @file
 * @brief Universal synchronous/asynchronous receiver/transmitter (USART/UART)
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
#ifndef __EM_USART_H
#define __EM_USART_H

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
 * @addtogroup USART
 * @brief Universal Synchronous/Asynchronous Receiver/Transmitter (USART) peripheral API
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

#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
/** I2S format selection. */
typedef enum
{
  usartI2sFormatW32D32  = USART_I2SCTRL_FORMAT_W32D32,   /**< 32-bit word, 32-bit data */
  usartI2sFormatW32D24M = USART_I2SCTRL_FORMAT_W32D24M,  /**< 32-bit word, 32-bit data with 8 lsb masked */
  usartI2sFormatW32D24  = USART_I2SCTRL_FORMAT_W32D24,   /**< 32-bit word, 24-bit data */
  usartI2sFormatW32D16  = USART_I2SCTRL_FORMAT_W32D16,   /**< 32-bit word, 16-bit data */
  usartI2sFormatW32D8   = USART_I2SCTRL_FORMAT_W32D8,    /**< 32-bit word, 8-bit data  */
  usartI2sFormatW16D16  = USART_I2SCTRL_FORMAT_W16D16,   /**< 16-bit word, 16-bit data */
  usartI2sFormatW16D8   = USART_I2SCTRL_FORMAT_W16D8,    /**< 16-bit word, 8-bit data  */
  usartI2sFormatW8D8    = USART_I2SCTRL_FORMAT_W8D8      /**<  8-bit word, 8-bit data  */
} USART_I2sFormat_TypeDef;

/** I2S frame data justify. */
typedef enum
{
  usartI2sJustifyLeft  = USART_I2SCTRL_JUSTIFY_LEFT,  /**< Data is left-justified within the frame  */
  usartI2sJustifyRight = USART_I2SCTRL_JUSTIFY_RIGHT  /**< Data is right-justified within the frame */
} USART_I2sJustify_TypeDef;

/** USART Rx input PRS selection. */
typedef enum
{
  usartPrsRxCh0  = USART_INPUT_RXPRSSEL_PRSCH0,    /**< PRSCH0  selected as USART_INPUT */
  usartPrsRxCh1  = USART_INPUT_RXPRSSEL_PRSCH1,    /**< PRSCH1  selected as USART_INPUT */
  usartPrsRxCh2  = USART_INPUT_RXPRSSEL_PRSCH2,    /**< PRSCH2  selected as USART_INPUT */
  usartPrsRxCh3  = USART_INPUT_RXPRSSEL_PRSCH3,    /**< PRSCH3  selected as USART_INPUT */
  usartPrsRxCh4  = USART_INPUT_RXPRSSEL_PRSCH4,    /**< PRSCH4  selected as USART_INPUT */
  usartPrsRxCh5  = USART_INPUT_RXPRSSEL_PRSCH5,    /**< PRSCH5  selected as USART_INPUT */
  usartPrsRxCh6  = USART_INPUT_RXPRSSEL_PRSCH6,    /**< PRSCH6  selected as USART_INPUT */

#if defined(_EFM32_TINY_FAMILY)
  usartPrsRxCh7  = USART_INPUT_RXPRSSEL_PRSCH7     /**< PRSCH7  selected as USART_INPUT */

#elif defined(_EFM32_GIANT_FAMILY)
  usartPrsRxCh7  = USART_INPUT_RXPRSSEL_PRSCH7,    /**< PRSCH7  selected as USART_INPUT */
  usartPrsRxCh8  = USART_INPUT_RXPRSSEL_PRSCH8,    /**< PRSCH8  selected as USART_INPUT */
  usartPrsRxCh9  = USART_INPUT_RXPRSSEL_PRSCH9,    /**< PRSCH9  selected as USART_INPUT */
  usartPrsRxCh10 = USART_INPUT_RXPRSSEL_PRSCH10,   /**< PRSCH10 selected as USART_INPUT */
  usartPrsRxCh11 = USART_INPUT_RXPRSSEL_PRSCH11    /**< PRSCH11 selected as USART_INPUT */
#else
#error Unknown EFM32 family.
#endif
} USART_PrsRxCh_TypeDef;
#endif

#if defined (_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
/** USART PRS Transmit Trigger Channels */
typedef enum
{
  usartPrsTriggerCh0 = USART_TRIGCTRL_TSEL_PRSCH0, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh1 = USART_TRIGCTRL_TSEL_PRSCH1, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh2 = USART_TRIGCTRL_TSEL_PRSCH2, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh3 = USART_TRIGCTRL_TSEL_PRSCH3, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh4 = USART_TRIGCTRL_TSEL_PRSCH4, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh5 = USART_TRIGCTRL_TSEL_PRSCH5, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh6 = USART_TRIGCTRL_TSEL_PRSCH6, /**< PRSCH0 selected as USART Trigger */
  usartPrsTriggerCh7 = USART_TRIGCTRL_TSEL_PRSCH7, /**< PRSCH0 selected as USART Trigger */
} USART_PrsTriggerCh_TypeDef;
#endif

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Asynchronous mode init structure. */
typedef struct
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  USART_Enable_TypeDef   enable;

  /**
   * USART/UART reference clock assumed when configuring baudrate setup. Set
   * it to 0 if currently configurated reference clock shall be used.
   */
  uint32_t               refFreq;

  /** Desired baudrate. */
  uint32_t               baudrate;

  /** Oversampling used. */
  USART_OVS_TypeDef      oversampling;

  /** Number of databits in frame. Notice that UART modules only support 8 or
   * 9 databits. */
  USART_Databits_TypeDef databits;

  /** Parity mode to use. */
  USART_Parity_TypeDef   parity;

  /** Number of stopbits to use. */
  USART_Stopbits_TypeDef stopbits;

#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
  /** Majority Vote Disable for 16x, 8x and 6x oversampling modes. */
  bool                   mvdis;

  /** Enable USART Rx via PRS. */
  bool                   prsRxEnable;

  /** Select PRS channel for USART Rx. (Only valid if prsRxEnable is true). */
  USART_PrsRxCh_TypeDef  prsRxCh;
#endif
} USART_InitAsync_TypeDef;

#if defined(_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
/** USART PRS trigger enable */
typedef struct
{
#if defined(_EFM32_GIANT_FAMILY)
  /** Enable AUTOTX */
  bool autoTxTriggerEnable;
#endif
  /** Trigger receive via PRS channel */
  bool rxTriggerEnable;
  /** Trigger transmit via PRS channel */
  bool txTriggerEnable;
  /** PRS channel to be used to trigger auto transmission */
  USART_PrsTriggerCh_TypeDef prsTriggerChannel;
} USART_PrsTriggerInit_TypeDef;
#endif

/** Default config for USART async init structure. */
#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
#define USART_INITASYNC_DEFAULT                                                              \
  { usartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                /* Use current configured reference clock for configuring baudrate. */ \
    115200,           /* 115200 bits/s. */                                                   \
    usartOVS16,       /* 16x oversampling. */                                                \
    usartDatabits8,   /* 8 databits. */                                                      \
    usartNoParity,    /* No parity. */                                                       \
    usartStopbits1,   /* 1 stopbit. */                                                       \
    false,            /* Do not disable majority vote. */                                    \
    false,            /* Not USART PRS input mode. */                                        \
    usartPrsRxCh0     /* PRS channel 0. */                                                   \
  }
#else
#define USART_INITASYNC_DEFAULT                                                              \
  { usartEnable,      /* Enable RX/TX when init completed. */                                \
    0,                /* Use current configured reference clock for configuring baudrate. */ \
    115200,           /* 115200 bits/s. */                                                   \
    usartOVS16,       /* 16x oversampling. */                                                \
    usartDatabits8,   /* 8 databits. */                                                      \
    usartNoParity,    /* No parity. */                                                       \
    usartStopbits1    /* 1 stopbit. */                                                       \
  }
#endif

/** Synchronous mode init structure. */
typedef struct
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  USART_Enable_TypeDef    enable;

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

#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
  /** Enable USART Rx via PRS. */
  bool                    prsRxEnable;

  /** Select PRS channel for USART Rx. (Only valid if prsRxEnable is true). */
  USART_PrsRxCh_TypeDef   prsRxCh;

  /** Enable AUTOTX mode. Transmits as long as RX is not full.
   *  If TX is empty, underflows are generated. */
  bool                    autoTx;
#endif
} USART_InitSync_TypeDef;

/** Default config for USART sync init structure. */
#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
#define USART_INITSYNC_DEFAULT                                                                \
  { usartEnable,       /* Enable RX/TX when init completed. */                                \
    0,                 /* Use current configured reference clock for configuring baudrate. */ \
    1000000,           /* 1 Mbits/s. */                                                       \
    usartDatabits8,    /* 8 databits. */                                                      \
    true,              /* Master mode. */                                                     \
    false,             /* Send least significant bit first. */                                \
    usartClockMode0,   /* Clock idle low, sample on rising edge. */                           \
    false,             /* Not USART PRS input mode. */                                        \
    usartPrsRxCh0,     /* PRS channel 0. */                                                   \
    false              /* No AUTOTX mode. */                                                  \
  }
#else
#define USART_INITSYNC_DEFAULT                                                                \
  { usartEnable,       /* Enable RX/TX when init completed. */                                \
    0,                 /* Use current configured reference clock for configuring baudrate. */ \
    1000000,           /* 1 Mbits/s. */                                                       \
    usartDatabits8,    /* 8 databits. */                                                      \
    true,              /* Master mode. */                                                     \
    false,             /* Send least significant bit first. */                                \
    usartClockMode0    /* Clock idle low, sample on rising edge. */                           \
  }
#endif


/** IrDA mode init structure. Inherited from asynchronous mode init structure */
typedef struct
{
  /** General Async initialization structure. */
  USART_InitAsync_TypeDef  async;

  /** Set to invert Rx signal before IrDA demodulator. */
  bool                     irRxInv;

  /** Set to enable filter on IrDA demodulator. */
  bool                     irFilt;

  /** Configure the pulse width generated by the IrDA modulator as a fraction
   *  of the configured USART bit period. */
  USART_IrDAPw_Typedef     irPw;

  /** Enable the PRS channel selected by irPrsSel as input to IrDA module
   *  instead of TX. */
  bool                     irPrsEn;

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


#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
/** I2S mode init structure. Inherited from synchronous mode init structure */
typedef struct
{
  /** General Sync initialization structure. */
  USART_InitSync_TypeDef   sync;

  /** I2S mode. */
  USART_I2sFormat_TypeDef  format;

  /** Delay on I2S data. Set to add a one-cycle delay between a transition
   *  on the word-clock and the start of the I2S word.
   *  Should be set for standard I2S format. */
  bool                     delay;

  /** Separate DMA Request For Left/Right Data. */
  bool                     dmaSplit;

  /** Justification of I2S data within the frame */
  USART_I2sJustify_TypeDef justify;

  /** Stero or Mono, set to true for mono. */
  bool                     mono;
} USART_InitI2s_TypeDef;


/** Default config for I2S mode init structure. */
#define USART_INITI2S_DEFAULT                                                                    \
  {                                                                                              \
    { usartEnableTx,      /* Enable TX when init completed. */                                   \
      0,                  /* Use current configured reference clock for configuring baudrate. */ \
      1000000,            /* Baudrate 1M bits/s. */                                              \
      usartDatabits16,    /* 16 databits. */                                                     \
      true,               /* Operate as I2S master. */                                           \
      true,               /* Most significant bit first. */                                      \
      usartClockMode0,    /* Clock idle low, sample on rising edge. */                           \
      false,              /* Don't enable USARTRx via PRS. */                                    \
      usartPrsRxCh0,      /* PRS channel selection (dummy). */                                   \
      false               /* Disable AUTOTX mode. */                                             \
    },                                                                                           \
    usartI2sFormatW16D16, /* 16-bit word, 16-bit data */                                         \
    true,                 /* Delay on I2S data. */                                               \
    false,                /* No DMA split. */                                                    \
    usartI2sJustifyLeft,  /* Data is left-justified within the frame */                          \
    false                 /* Stereo mode. */                                                     \
  }
#endif

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

void USART_InitAsync(USART_TypeDef *usart, const USART_InitAsync_TypeDef *init);
void USART_InitSync(USART_TypeDef *usart, const USART_InitSync_TypeDef *init);
void USART_InitIrDA(const USART_InitIrDA_TypeDef *init);

#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
void USART_InitI2s(USART_TypeDef *usart, USART_InitI2s_TypeDef *init);
void USART_InitPrsTrigger(USART_TypeDef *usart, const USART_PrsTriggerInit_TypeDef *init);
#endif


/***************************************************************************//**
 * @brief
 *   Clear one or more pending USART interrupts.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @param[in] flags
 *   Pending USART/UART interrupt source(s) to clear. Use one or more valid
 *   interrupt flags for the USART module (USART_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void USART_IntClear(USART_TypeDef *usart, uint32_t flags)
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
 *   USART/UART interrupt source(s) to disable. Use one or more valid
 *   interrupt flags for the USART module (USART_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void USART_IntDisable(USART_TypeDef *usart, uint32_t flags)
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
 *   USART/UART interrupt source(s) to enable. Use one or more valid
 *   interrupt flags for the USART module (USART_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void USART_IntEnable(USART_TypeDef *usart, uint32_t flags)
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
 *   USART/UART interrupt source(s) pending. Returns one or more valid
 *   interrupt flags for the USART module (USART_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE uint32_t USART_IntGet(USART_TypeDef *usart)
{
  return usart->IF;
}


/***************************************************************************//**
 * @brief
 *   Get enabled and pending USART interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled USART interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in USARTx_IEN_nnn
 *     register (USARTx_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the USART module
 *     (USARTx_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t USART_IntGetEnabled(USART_TypeDef *usart)
{
  uint32_t tmp;

  /* Store USARTx->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = usart->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return usart->IF & tmp;
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending USART interrupts from SW.
 *
 * @param[in] usart
 *   Pointer to USART/UART peripheral register block.
 *
 * @param[in] flags
 *   USART/UART interrupt source(s) to set to pending. Use one or more valid
 *   interrupt flags for the USART module (USART_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void USART_IntSet(USART_TypeDef *usart, uint32_t flags)
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
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_USART_H */
