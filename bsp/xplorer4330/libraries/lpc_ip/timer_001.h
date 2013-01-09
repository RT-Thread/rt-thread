/*
 * @brief 32-bit Timer/PWM registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __TIMER_001_H_
#define __TIMER_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_TIMER_001 IP: Timer register block and driver
 * @ingroup IP_Drivers
 * @{
 */

/**
 * @brief 32-bit Standard timer register block structure
 */
typedef struct {					/*!< TIMERn Structure       */
	__IO uint32_t IR;				/*!< Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
	__IO uint32_t TCR;				/*!< Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
	__IO uint32_t TC;				/*!< Timer Counter. The 32 bit TC is incremented every PR+1 cycles of PCLK. The TC is controlled through the TCR. */
	__IO uint32_t PR;				/*!< Prescale Register. The Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC. */
	__IO uint32_t PC;				/*!< Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
	__IO uint32_t MCR;				/*!< Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
	__IO uint32_t MR[4];			/*!< Match Register. MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
	__IO uint32_t CCR;				/*!< Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
	__IO uint32_t CR[4];			/*!< Capture Register. CR is loaded with the value of TC when there is an event on the CAPn.0 input. */
	__IO uint32_t EMR;				/*!< External Match Register. The EMR controls the external match pins MATn.0-3 (MAT0.0-3 and MAT1.0-3 respectively). */
	__I  uint32_t RESERVED0[12];
	__IO uint32_t CTCR;				/*!< Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
} IP_TIMER_001_Type;

/** Macro to clear interrupt pending */
#define TIMER_IR_CLR(n)         _BIT(n)

/** Macro for getting a timer match interrupt bit */
#define TIMER_MATCH_INT(n)      (_BIT((n) & 0x0F))
/** Macro for getting a capture event interrupt bit */
#define TIMER_CAP_INT(n)        (_BIT((((n) & 0x0F) + 4)))

/** Timer/counter enable bit */
#define TIMER_ENABLE            ((uint32_t) (1 << 0))
/** Timer/counter reset bit */
#define TIMER_RESET             ((uint32_t) (1 << 1))

/** Bit location for interrupt on MRx match, n = 0 to 3 */
#define TIMER_INT_ON_MATCH(n)   (_BIT(((n) * 3)))
/** Bit location for reset on MRx match, n = 0 to 3 */
#define TIMER_RESET_ON_MATCH(n) (_BIT((((n) * 3) + 1)))
/** Bit location for stop on MRx match, n = 0 to 3 */
#define TIMER_STOP_ON_MATCH(n)  (_BIT((((n) * 3) + 2)))

/** Bit location for CAP.n on CRx rising edge, n = 0 to 3 */
#define TIMER_CAP_RISING(n)     (_BIT(((n) * 3)))
/** Bit location for CAP.n on CRx falling edge, n = 0 to 3 */
#define TIMER_CAP_FALLING(n)    (_BIT((((n) * 3) + 1)))
/** Bit location for CAP.n on CRx interrupt enable, n = 0 to 3 */
#define TIMER_INT_ON_CAP(n)     (_BIT((((n) * 3) + 2)))

/**
 * @brief	Determine if a match interrupt is pending
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match interrupt number to check
 * @return	false if the interrupt is not pending, otherwise true
 * Determine if the match interrupt for the passed timer and match
 * counter is pending.
 */
STATIC INLINE bool IP_TIMER_MatchPending(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	return (bool) ((timer->IR & TIMER_MATCH_INT(matchnum)) != 0);
}

/**
 * @brief	Determine if a capture interrupt is pending
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture interrupt number to check
 * @return	false if the interrupt is not pending, otherwise true
 * Determine if the capture interrupt for the passed capture pin is
 * pending.
 */
STATIC INLINE bool IP_TIMER_CapturePending(IP_TIMER_001_Type *timer, int8_t capnum)
{
	return (bool) ((timer->IR & TIMER_CAP_INT(capnum)) != 0);
}

/**
 * @brief	Clears a (pending) match interrupt
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match interrupt number to clear
 * @return	Nothing
 * Clears a pending timer match interrupt.
 */
STATIC INLINE void IP_TIMER_ClearMatch(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->IR = TIMER_IR_CLR(matchnum);
}

/**
 * @brief	Clears a (pending) capture interrupt
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture interrupt number to clear
 * @return	Nothing
 * Clears a pending timer capture interrupt.
 */
STATIC INLINE void IP_TIMER_ClearCapture(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->IR = (0x10 << capnum);
}

/**
 * @brief	Enables the timer (starts count)
 * @param	timer	: Pointer to timer IP register address
 * @return	Nothing
 * Enables the timer to start counting.
 */
STATIC INLINE void IP_TIMER_Enable(IP_TIMER_001_Type *timer)
{
	timer->TCR |= TIMER_ENABLE;
}

/**
 * @brief	Disables the timer (stops count)
 * @param	timer	: Pointer to timer IP register address
 * @return	Nothing
 * Disables the timer to stop counting.
 */
STATIC INLINE void IP_TIMER_Disable(IP_TIMER_001_Type *timer)
{
	timer->TCR &= ~TIMER_ENABLE;
}

/**
 * @brief	Returns the current timer count
 * @param	timer	: Pointer to timer IP register address
 * @return	Current timer terminal count value
 * Returns the current timer terminal count.
 */
STATIC INLINE uint32_t IP_TIMER_ReadCount(IP_TIMER_001_Type *timer)
{
	return timer->TC;
}

/**
 * @brief  Returns the current prescale count
 * @param	timer		: Pointer to timer IP register address
 * @return Current timer prescale count value
 * Returns the current prescale count.
 */
STATIC INLINE uint32_t IP_TIMER_ReadPrescale(IP_TIMER_001_Type *timer)
{
	return timer->PC;
}

/**
 * @brief	Sets the prescaler value
 * @param	timer		: Pointer to timer IP register address
 * @param	prescale	: Prescale value to set the prescale register to
 * @return	Nothing
 * Sets the prescale count value.
 */
STATIC INLINE void IP_TIMER_PrescaleSet(IP_TIMER_001_Type *timer, uint32_t prescale)
{
	timer->PR = prescale;
}

/**
 * @brief	Sets a timer match value
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer to set match count for
 * @param	matchval	: Match value for the selected match count
 * @return	Nothing
 * Sets ones of the timer match values.
 */
STATIC INLINE void IP_TIMER_SetMatch(IP_TIMER_001_Type *timer, int8_t matchnum, uint32_t matchval)
{
	timer->MR[matchnum] = matchval;
}

/**
 * @brief	Reads a capture register
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture register to read
 * @return	The selected capture register value
 * Returns the selected capture register value.
 */
STATIC INLINE uint32_t IP_TIMER_ReadCapture(IP_TIMER_001_Type *timer, int8_t capnum)
{
	return timer->CR[capnum];
}

/**
 * @brief	Resets the timer terminal and prescale counts to 0
 * @param	timer	: Pointer to timer IP register address
 * @return	Nothing
 */
void IP_TIMER_Reset(IP_TIMER_001_Type *timer);

/**
 * @brief	Enables a match interrupt that fires when the terminal count
 *			matches the match counter value.
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer, 0 to 3
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_MatchEnableInt(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->MCR |= TIMER_INT_ON_MATCH(matchnum);
}

/**
 * @brief	Disables a match interrupt for a match counter.
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer, 0 to 3
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_MatchDisableInt(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->MCR &= ~TIMER_INT_ON_MATCH(matchnum);
}

/**
 * @brief	For the specific match counter, enables reset of the terminal count register when a match occurs
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer, 0 to 3
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_ResetOnMatchEnable(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->MCR |= TIMER_RESET_ON_MATCH(matchnum);
}

/**
 * @brief	For the specific match counter, disables reset of the terminal count register when a match occurs
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer, 0 to 3
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_ResetOnMatchDisable(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->MCR &= ~TIMER_RESET_ON_MATCH(matchnum);
}

/**
 * @brief	Enable a match timer to stop the terminal count when a
 *			match count equals the terminal count.
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer, 0 to 3
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_StopOnMatchEnable(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->MCR |= TIMER_STOP_ON_MATCH(matchnum);
}

/**
 * @brief	Disable stop on match for a match timer. Disables a match timer
 *			to stop the terminal count when a match count equals the terminal count.
 * @param	timer		: Pointer to timer IP register address
 * @param	matchnum	: Match timer, 0 to 3
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_StopOnMatchDisable(IP_TIMER_001_Type *timer, int8_t matchnum)
{
	timer->MCR &= ~TIMER_STOP_ON_MATCH(matchnum);
}

/**
 * @brief	Enables capture on on rising edge of selected CAP signal for the
 *			selected capture register, enables the selected CAPn.capnum signal to load
 *			the capture register with the terminal coount on a rising edge.
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture signal/register to use
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_CaptureRisingEdgeEnable(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->CCR |= TIMER_CAP_RISING(capnum);
}

/**
 * @brief	Disables capture on on rising edge of selected CAP signal. For the
 *			selected capture register, disables the selected CAPn.capnum signal to load
 *			the capture register with the terminal coount on a rising edge.
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture signal/register to use
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_CaptureRisingEdgeDisable(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->CCR &= ~TIMER_CAP_RISING(capnum);
}

/**
 * @brief	Enables capture on on falling edge of selected CAP signal. For the
 *			selected capture register, enables the selected CAPn.capnum signal to load
 *			the capture register with the terminal coount on a falling edge.
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture signal/register to use
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_CaptureFallingEdgeEnable(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->CCR |= TIMER_CAP_FALLING(capnum);
}

/**
 * @brief	Disables capture on on falling edge of selected CAP signal. For the
 *			selected capture register, disables the selected CAPn.capnum signal to load
 *			the capture register with the terminal coount on a falling edge.
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture signal/register to use
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_CaptureFallingEdgeDisable(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->CCR &= ~TIMER_CAP_FALLING(capnum);
}

/**
 * @brief	Enables interrupt on capture of selected CAP signal. For the
 *			selected capture register, an interrupt will be generated when the enabled
 *			rising or falling edge on CAPn.capnum is detected.
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture signal/register to use
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_CaptureEnableInt(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->CCR |= TIMER_INT_ON_CAP(capnum);
}

/**
 * @brief	Disables interrupt on capture of selected CAP signal
 * @param	timer	: Pointer to timer IP register address
 * @param	capnum	: Capture signal/register to use
 * @return	Nothing
 */
STATIC INLINE void IP_TIMER_CaptureDisableInt(IP_TIMER_001_Type *timer, int8_t capnum)
{
	timer->CCR &= ~TIMER_INT_ON_CAP(capnum);
}

/**
 * @brief Standard timer initial match pin state and change state
 */
typedef enum {
	TIMER_EXTMATCH_DO_NOTHING = 0,	/*!< Timer match state does nothing on match pin */
	TIMER_EXTMATCH_CLEAR      = 1,	/*!< Timer match state sets match pin low */
	TIMER_EXTMATCH_SET        = 2,	/*!< Timer match state sets match pin high */
	TIMER_EXTMATCH_TOGGLE     = 3	/*!< Timer match state toggles match pin */
} IP_TIMER_PIN_MATCH_STATE_Type;

/**
 * @brief	Sets external match control (MATn.matchnum) pin control
 * @param	timer			: Pointer to timer IP register address
 * @param	initial_state	: Initial state of the pin, high(1) or low(0)
 * @param	matchState		: Selects the match state for the pin
 * @param	matchnum		: MATn.matchnum signal to use
 * @return	Nothing
 * For the pin selected with matchnum, sets the function of the pin that occurs on
 * a terminal count match for the match count.
 */
void IP_TIMER_ExtMatchControlSet(IP_TIMER_001_Type *timer, int8_t initial_state,
								 IP_TIMER_PIN_MATCH_STATE_Type matchState, int8_t matchnum);

/**
 * @brief Standard timer clock and edge for count source
 */
typedef enum {
	TIMER_CAPSRC_RISING_PCLK  = 0,	/*!< Timer ticks on PCLK rising edge */
	TIMER_CAPSRC_RISING_CAPN  = 1,	/*!< Timer ticks on CAPn.x rising edge */
	TIMER_CAPSRC_FALLING_CAPN = 2,	/*!< Timer ticks on CAPn.x falling edge */
	TIMER_CAPSRC_BOTH_CAPN    = 3	/*!< Timer ticks on CAPn.x both edges */
} IP_TIMER_CAP_SRC_STATE_Type;

/**
 * @brief	Sets timer count source and edge with the selected passed from CapSrc
 * @param	timer	: Pointer to timer IP register address
 * @param	capSrc	: timer clock source and edge
 * @param	capnum	: CAPn.capnum pin to use (if used)
 * @return	Nothing
 * If CapSrc selected a CAPn pin, select the specific CAPn pin with the capnum value.
 */
void IP_TIMER_SetCountClockSrc(IP_TIMER_001_Type *timer,
							   IP_TIMER_CAP_SRC_STATE_Type capSrc, int8_t capnum);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_001_H_ */
