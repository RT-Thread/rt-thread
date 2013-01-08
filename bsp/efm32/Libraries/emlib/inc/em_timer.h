/***************************************************************************//**
 * @file
 * @brief Timer/counter (TIMER) peripheral API
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
#ifndef __EM_TIMER_H
#define __EM_TIMER_H

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
 * @addtogroup TIMER
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Timer compare/capture mode. */
typedef enum
{
  timerCCModeOff     = _TIMER_CC_CTRL_MODE_OFF,           /**< Channel turned off. */
  timerCCModeCapture = _TIMER_CC_CTRL_MODE_INPUTCAPTURE,  /**< Input capture. */
  timerCCModeCompare = _TIMER_CC_CTRL_MODE_OUTPUTCOMPARE, /**< Output compare. */
  timerCCModePWM     = _TIMER_CC_CTRL_MODE_PWM            /**< Pulse-Width modulation. */
} TIMER_CCMode_TypeDef;


/** Clock select. */
typedef enum
{
  /** Prescaled HFPER clock. */
  timerClkSelHFPerClk = _TIMER_CTRL_CLKSEL_PRESCHFPERCLK,

  /** Prescaled HFPER clock. */
  timerClkSelCC1      = _TIMER_CTRL_CLKSEL_CC1,

  /**
   * Cascaded, clocked by underflow (down-counting) or overflow (up-counting)
   * by lower numbered timer.
   */
  timerClkSelCascade  = _TIMER_CTRL_CLKSEL_TIMEROUF
} TIMER_ClkSel_TypeDef;


/** Input capture edge select. */
typedef enum
{
  /** Rising edges detected. */
  timerEdgeRising  = _TIMER_CC_CTRL_ICEDGE_RISING,

  /** Falling edges detected. */
  timerEdgeFalling = _TIMER_CC_CTRL_ICEDGE_FALLING,

  /** Both edges detected. */
  timerEdgeBoth    = _TIMER_CC_CTRL_ICEDGE_BOTH,

  /** No edge detection, leave signal as is. */
  timerEdgeNone    = _TIMER_CC_CTRL_ICEDGE_NONE
} TIMER_Edge_TypeDef;


/** Input capture event control. */
typedef enum
{
  /** PRS output pulse, interrupt flag and DMA request set on every capture. */
  timerEventEveryEdge    = _TIMER_CC_CTRL_ICEVCTRL_EVERYEDGE,
  /** PRS output pulse, interrupt flag and DMA request set on every second capture. */
  timerEventEvery2ndEdge = _TIMER_CC_CTRL_ICEVCTRL_EVERYSECONDEDGE,
  /**
   * PRS output pulse, interrupt flag and DMA request set on rising edge (if
   * input capture edge = BOTH).
   */
  timerEventRising       = _TIMER_CC_CTRL_ICEVCTRL_RISING,
  /**
   * PRS output pulse, interrupt flag and DMA request set on falling edge (if
   * input capture edge = BOTH).
   */
  timerEventFalling      = _TIMER_CC_CTRL_ICEVCTRL_FALLING
} TIMER_Event_TypeDef;


/** Input edge action. */
typedef enum
{
  /** No action taken. */
  timerInputActionNone        = _TIMER_CTRL_FALLA_NONE,

  /** Start counter without reload. */
  timerInputActionStart       = _TIMER_CTRL_FALLA_START,

  /** Stop counter without reload. */
  timerInputActionStop        = _TIMER_CTRL_FALLA_STOP,

  /** Reload and start counter. */
  timerInputActionReloadStart = _TIMER_CTRL_FALLA_RELOADSTART
} TIMER_InputAction_TypeDef;


/** Timer mode. */
typedef enum
{
  timerModeUp     = _TIMER_CTRL_MODE_UP,     /**< Up-counting. */
  timerModeDown   = _TIMER_CTRL_MODE_DOWN,   /**< Down-counting. */
  timerModeUpDown = _TIMER_CTRL_MODE_UPDOWN, /**< Up/down-counting. */
  timerModeQDec   = _TIMER_CTRL_MODE_QDEC    /**< Quadrature decoder. */
} TIMER_Mode_TypeDef;


/** Compare/capture output action. */
typedef enum
{
  /** No action. */
  timerOutputActionNone   = _TIMER_CC_CTRL_CUFOA_NONE,

  /** Toggle on event. */
  timerOutputActionToggle = _TIMER_CC_CTRL_CUFOA_TOGGLE,

  /** Clear on event. */
  timerOutputActionClear  = _TIMER_CC_CTRL_CUFOA_CLEAR,

  /** Set on event. */
  timerOutputActionSet    = _TIMER_CC_CTRL_CUFOA_SET
} TIMER_OutputAction_TypeDef;


/** Prescaler. */
typedef enum
{
  timerPrescale1    = _TIMER_CTRL_PRESC_DIV1,     /**< Divide by 1. */
  timerPrescale2    = _TIMER_CTRL_PRESC_DIV2,     /**< Divide by 2. */
  timerPrescale4    = _TIMER_CTRL_PRESC_DIV4,     /**< Divide by 4. */
  timerPrescale8    = _TIMER_CTRL_PRESC_DIV8,     /**< Divide by 8. */
  timerPrescale16   = _TIMER_CTRL_PRESC_DIV16,    /**< Divide by 16. */
  timerPrescale32   = _TIMER_CTRL_PRESC_DIV32,    /**< Divide by 32. */
  timerPrescale64   = _TIMER_CTRL_PRESC_DIV64,    /**< Divide by 64. */
  timerPrescale128  = _TIMER_CTRL_PRESC_DIV128,   /**< Divide by 128. */
  timerPrescale256  = _TIMER_CTRL_PRESC_DIV256,   /**< Divide by 256. */
  timerPrescale512  = _TIMER_CTRL_PRESC_DIV512,   /**< Divide by 512. */
  timerPrescale1024 = _TIMER_CTRL_PRESC_DIV1024   /**< Divide by 1024. */
} TIMER_Prescale_TypeDef;


/** Peripheral Reflex System signal. */
typedef enum
{
  timerPRSSELCh0 = _ADC_SINGLECTRL_PRSSEL_PRSCH0, /**< PRS channel 0. */
  timerPRSSELCh1 = _ADC_SINGLECTRL_PRSSEL_PRSCH1, /**< PRS channel 1. */
  timerPRSSELCh2 = _ADC_SINGLECTRL_PRSSEL_PRSCH2, /**< PRS channel 2. */
  timerPRSSELCh3 = _ADC_SINGLECTRL_PRSSEL_PRSCH3, /**< PRS channel 3. */
  timerPRSSELCh4 = _ADC_SINGLECTRL_PRSSEL_PRSCH4, /**< PRS channel 4. */
  timerPRSSELCh5 = _ADC_SINGLECTRL_PRSSEL_PRSCH5, /**< PRS channel 5. */
  timerPRSSELCh6 = _ADC_SINGLECTRL_PRSSEL_PRSCH6, /**< PRS channel 6. */
  timerPRSSELCh7 = _ADC_SINGLECTRL_PRSSEL_PRSCH7  /**< PRS channel 7. */
} TIMER_PRSSEL_TypeDef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** TIMER initialization structure. */
typedef struct
{
  /** Start counting when init completed. */
  bool                      enable;

  /** Counter shall keep running during debug halt. */
  bool                      debugRun;

  /** Prescaling factor, if HFPER clock used. */
  TIMER_Prescale_TypeDef    prescale;

  /** Clock selection. */
  TIMER_ClkSel_TypeDef      clkSel;

#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
  /** 2x Count mode, counter increments/decrements by 2, meant for PWN mode. */
  bool                      count2x;

  /** ATI (Always Track Inputs) makes CCPOL always track
   * the polarity of the inputs. */
  bool                      ati;
#endif

  /** Action on falling input edge. */
  TIMER_InputAction_TypeDef fallAction;

  /** Action on rising input edge. */
  TIMER_InputAction_TypeDef riseAction;

  /** Counting mode. */
  TIMER_Mode_TypeDef        mode;

  /** DMA request clear on active. */
  bool                      dmaClrAct;

  /** Select X2 or X4 quadrature decode mode (if used). */
  bool                      quadModeX4;

  /** Determines if only counting up or down once. */
  bool                      oneShot;

  /** Timer start/stop/reload by other timers. */
  bool                      sync;
} TIMER_Init_TypeDef;

/** Default config for TIMER init structure. */
#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
#define TIMER_INIT_DEFAULT                                                              \
  { true,                   /* Enable timer when init complete. */                      \
    false,                  /* Stop counter during debug halt. */                       \
    timerPrescale1,         /* No prescaling. */                                        \
    timerClkSelHFPerClk,    /* Select HFPER clock. */                                   \
    false,                  /* Not 2x count mode. */                                    \
    false,                  /* No ATI. */                                               \
    timerInputActionNone,   /* No action on falling input edge. */                      \
    timerInputActionNone,   /* No action on rising input edge. */                       \
    timerModeUp,            /* Up-counting. */                                          \
    false,                  /* Do not clear DMA requests when DMA channel is active. */ \
    false,                  /* Select X2 quadrature decode mode (if used). */           \
    false,                  /* Disable one shot. */                                     \
    false                   /* Not started/stopped/reloaded by other timers. */         \
  }
#else
#define TIMER_INIT_DEFAULT                                                              \
  { true,                   /* Enable timer when init complete. */                      \
    false,                  /* Stop counter during debug halt. */                       \
    timerPrescale1,         /* No prescaling. */                                        \
    timerClkSelHFPerClk,    /* Select HFPER clock. */                                   \
    timerInputActionNone,   /* No action on falling input edge. */                      \
    timerInputActionNone,   /* No action on rising input edge. */                       \
    timerModeUp,            /* Up-counting. */                                          \
    false,                  /* Do not clear DMA requests when DMA channel is active. */ \
    false,                  /* Select X2 quadrature decode mode (if used). */           \
    false,                  /* Disable one shot. */                                     \
    false                   /* Not started/stopped/reloaded by other timers. */         \
  }
#endif

/** TIMER compare/capture initialization structure. */
typedef struct
{
  /** Input capture event control. */
  TIMER_Event_TypeDef        eventCtrl;

  /** Input capture edge select. */
  TIMER_Edge_TypeDef         edge;

  /**
   * Peripheral reflex system trigger selection. Only applicable if @p prsInput
   * is enabled.
   */
  TIMER_PRSSEL_TypeDef       prsSel;

  /** Counter underflow output action. */
  TIMER_OutputAction_TypeDef cufoa;

  /** Counter overflow output action. */
  TIMER_OutputAction_TypeDef cofoa;

  /** Counter match output action. */
  TIMER_OutputAction_TypeDef cmoa;

  /** Compare/capture channel mode. */
  TIMER_CCMode_TypeDef       mode;

  /** Enable digital filter. */
  bool                       filter;

  /** Select TIMERnCCx (false) or PRS input (true). */
  bool                       prsInput;

  /**
   * Compare output initial state. Only used in Output Compare and PWM mode.
   * When true, the compare/PWM output is set high when the counter is
   * disabled. When counting resumes, this value will represent the initial
   * value for the compare/PWM output. If the bit is cleared, the output
   * will be cleared when the counter is disabled.
   */
  bool                       coist;

  /** Invert output from compare/capture channel. */
  bool                       outInvert;
} TIMER_InitCC_TypeDef;

/** Default config for TIMER compare/capture init structure. */
#define TIMER_INITCC_DEFAULT                                                   \
  { timerEventEveryEdge,      /* Event on every capture. */                    \
    timerEdgeRising,          /* Input capture edge on rising edge. */         \
    timerPRSSELCh0,           /* Not used by default, select PRS channel 0. */ \
    timerOutputActionNone,    /* No action on underflow. */                    \
    timerOutputActionNone,    /* No action on overflow. */                     \
    timerOutputActionNone,    /* No action on match. */                        \
    timerCCModeOff,           /* Disable compare/capture channel. */           \
    false,                    /* Disable filter. */                            \
    false,                    /* Select TIMERnCCx input. */                    \
    false,                    /* Clear output when countre disabled. */        \
    false                     /* Do not invert output. */                      \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get capture value for compare/capture channel when operating in capture
 *   mode.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] ch
 *   Compare/capture channel to access.
 *
 * @return
 *   Current capture value.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_CaptureGet(TIMER_TypeDef *timer, unsigned int ch)
{
  return(timer->CC[ch].CCV);
}


/***************************************************************************//**
 * @brief
 *   Set compare value buffer for compare/capture channel when operating in
 *   compare or PWM mode.
 *
 * @details
 *   The compare value buffer holds the value which will be written to
 *   TIMERn_CCx_CCV on an update event if the buffer has been updated since
 *   the last event.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] ch
 *   Compare/capture channel to access.
 *
 * @param[in] val
 *   Value to set in compare value buffer register.
 ******************************************************************************/
__STATIC_INLINE void TIMER_CompareBufSet(TIMER_TypeDef *timer,
                                         unsigned int ch,
                                         uint32_t val)
{
  timer->CC[ch].CCVB = val;
}


/***************************************************************************//**
 * @brief
 *   Set compare value for compare/capture channel when operating in compare
 *   or PWM mode.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] ch
 *   Compare/capture channel to access.
 *
 * @param[in] val
 *   Value to set in compare value register.
 ******************************************************************************/
__STATIC_INLINE void TIMER_CompareSet(TIMER_TypeDef *timer,
                                      unsigned int ch,
                                      uint32_t val)
{
  timer->CC[ch].CCV = val;
}


/***************************************************************************//**
 * @brief
 *   Get TIMER counter value.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @return
 *   Current TIMER counter value.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_CounterGet(TIMER_TypeDef *timer)
{
  return(timer->CNT);
}


/***************************************************************************//**
 * @brief
 *   Set TIMER counter value.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] val
 *   Value to set counter to.
 ******************************************************************************/
__STATIC_INLINE void TIMER_CounterSet(TIMER_TypeDef *timer, uint32_t val)
{
  timer->CNT = val;
}


void TIMER_Enable(TIMER_TypeDef *timer, bool enable);
void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init);
void TIMER_InitCC(TIMER_TypeDef *timer,
                  unsigned int ch,
                  const TIMER_InitCC_TypeDef *init);


/***************************************************************************//**
 * @brief
 *   Clear one or more pending TIMER interrupts.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] flags
 *   Pending TIMER interrupt source(s) to clear. Use one or more valid
 *   interrupt flags for the TIMER module (TIMER_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void TIMER_IntClear(TIMER_TypeDef *timer, uint32_t flags)
{
  timer->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more TIMER interrupts.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] flags
 *   TIMER interrupt source(s) to disable. Use one or more valid
 *   interrupt flags for the TIMER module (TIMER_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void TIMER_IntDisable(TIMER_TypeDef *timer, uint32_t flags)
{
  timer->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more TIMER interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using TIMER_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] flags
 *   TIMER interrupt source(s) to enable. Use one or more valid
 *   interrupt flags for the TIMER module (TIMER_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void TIMER_IntEnable(TIMER_TypeDef *timer, uint32_t flags)
{
  timer->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending TIMER interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @return
 *   TIMER interrupt source(s) pending. Returns one or more valid
 *   interrupt flags for the TIMER module (TIMER_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_IntGet(TIMER_TypeDef *timer)
{
  return(timer->IF);
}


/***************************************************************************//**
 * @brief
 *   Get enabled and pending TIMER interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled TIMER interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in TIMERx_IEN_nnn
 *     register (TIMERx_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the TIMER module
 *     (TIMERx_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_IntGetEnabled(TIMER_TypeDef *timer)
{
  uint32_t tmp;

  /* Store TIMER->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = timer->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return timer->IF & tmp;
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending TIMER interrupts from SW.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] flags
 *   TIMER interrupt source(s) to set to pending. Use one or more valid
 *   interrupt flags for the TIMER module (TIMER_IF_nnn) OR'ed together.
 ******************************************************************************/
__STATIC_INLINE void TIMER_IntSet(TIMER_TypeDef *timer, uint32_t flags)
{
  timer->IFS = flags;
}

#ifdef TIMER_DTLOCK_LOCKKEY_LOCK
void TIMER_Lock(TIMER_TypeDef *timer);
#endif

void TIMER_Reset(TIMER_TypeDef *timer);

/***************************************************************************//**
 * @brief
 *   Set top value buffer for timer.
 *
 * @details
 *   When the top value buffer register is updated, the value is loaded into
 *   the top value register at the next wrap around. This feature is useful
 *   in order to update the top value safely when the timer is running.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] val
 *   Value to set in top value buffer register.
 ******************************************************************************/
__STATIC_INLINE void TIMER_TopBufSet(TIMER_TypeDef *timer, uint32_t val)
{
  timer->TOPB = val;
}


/***************************************************************************//**
 * @brief
 *   Get top value setting for timer.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @return
 *   Current top value.
 ******************************************************************************/
__STATIC_INLINE uint32_t TIMER_TopGet(TIMER_TypeDef *timer)
{
  return(timer->TOP);
}


/***************************************************************************//**
 * @brief
 *   Set top value for timer.
 *
 * @param[in] timer
 *   Pointer to TIMER peripheral register block.
 *
 * @param[in] val
 *   Value to set in top value register.
 ******************************************************************************/
__STATIC_INLINE void TIMER_TopSet(TIMER_TypeDef *timer, uint32_t val)
{
  timer->TOP = val;
}

#ifdef TIMER_DTLOCK_LOCKKEY_UNLOCK
void TIMER_Unlock(TIMER_TypeDef *timer);
#endif


/** @} (end addtogroup TIMER) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_TIMER_H */
