/*
 * @brief LPC8xx Self Wakeup Timer (WKT) chip driver
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

#ifndef __WKT_8XX_H_
#define __WKT_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup WKT_8XX CHIP: LPC8xx Self Wakeup Timer driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief Self wake-up timer register block structure
 */
typedef struct {
	__IO uint32_t  CTRL;	/*!< Offset: 0x000 Alarm/Wakeup Timer Control register */
	uint32_t  Reserved[2];
	__IO uint32_t  COUNT;	/*!< Offset: 0x000C Alarm/Wakeup Timer Counter register */
} LPC_WKT_T;

#define WKT_CTRL_RESERVED (~7)

/**
 * WKT Control register bit fields & masks
 */
#define WKT_CTRL_CLKSEL        ((uint32_t) (1 << 0))	/*!< Select the self wake-up timer clock source */
#define WKT_CTRL_ALARMFLAG     ((uint32_t) (1 << 1))	/*!< Wake-up or alarm timer flag */
#define WKT_CTRL_CLEARCTR      ((uint32_t) (1 << 2))	/*!< Clears the self wake-up timer */

/**
 * WKT Clock source values enum
 */
typedef enum  {
	WKT_CLKSRC_DIVIRC = 0,	/*!< Divided IRC clock - runs at 750kHz */
	WKT_CLKSRC_10KHZ = 1	/*!< Low power clock - runs at 10kHz */
} WKT_CLKSRC_T;

/**
 * @brief	Get clock source for WKT
 * @param	pWKT	: Pointer to WKT register block
 * @return	Clock source for the WKT
 */
STATIC INLINE WKT_CLKSRC_T Chip_WKT_GetClockSource(LPC_WKT_T *pWKT)
{
	return (WKT_CLKSRC_T) (pWKT->CTRL & WKT_CTRL_CLKSEL);
}

/**
 * @brief	Set clock source for WKT
 * @param	pWKT	: Pointer to WKT register block
 * @param	clkSrc	: Clock source for the WKT
 * @return	Nothing
 */
void Chip_WKT_SetClockSource(LPC_WKT_T *pWKT, WKT_CLKSRC_T clkSrc);

/**
 * @brief	Return approximate rate for the selected clock source
 * @param	pWKT	: Pointer to WKT register block
 * @return	Clock rate of the selected clock source for WKT
 */
uint32_t Chip_WKT_GetClockRate(LPC_WKT_T *pWKT);

/**
 * @brief	Get WKT interrupt pending status (ALARMFLAG)
 * @param	pWKT	: Pointer to WKT register block
 * @return	True if the interrupt is pending, otherwise false
 */
STATIC INLINE bool Chip_WKT_GetIntStatus(LPC_WKT_T *pWKT)
{
	return (bool) ((pWKT->CTRL & WKT_CTRL_ALARMFLAG) != 0);
}

/**
 * @brief	Clear WKT interrupt status (ALARMFLAG)
 * @param	pWKT	: Pointer to WKT register block
 * @return	Nothing
 */
STATIC INLINE void Chip_WKT_ClearIntStatus(LPC_WKT_T *pWKT)
{
	pWKT->CTRL = WKT_CTRL_ALARMFLAG | (pWKT->CTRL & ~WKT_CTRL_RESERVED);
}

/**
 * @brief	Clear and stop WKT counter
 * @param	pWKT	: Pointer to WKT register block
 * @return	Nothing
 */
STATIC INLINE void Chip_WKT_Stop(LPC_WKT_T *pWKT)
{
	pWKT->CTRL = WKT_CTRL_CLEARCTR | (pWKT->CTRL & ~WKT_CTRL_RESERVED);
}

/**
 * @brief	Load count register and start count-down sequence
 * @param	pWKT	: Pointer to WKT register block
 * @param	count	: Count to load in the WKT
 * @return	Nothing
 * @note	This function should not be called if the WKT is already counting.
 */
STATIC INLINE void Chip_WKT_LoadCount(LPC_WKT_T *pWKT, uint32_t count)
{
	pWKT->COUNT = count;
}

/**
 * @brief	Start wake-up timer interrupt, set clock source, set timer interval
 * @param	pWKT	: Pointer to WKT register block
 * @param	clkSrc	: Clock source
 * @param	cntVal	: Timer interval
 * @return	None
 * @note	This function should not be called if the WKT is already counting.
 */
void Chip_WKT_Start(LPC_WKT_T *pWKT, WKT_CLKSRC_T clkSrc, uint32_t cntVal);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __WKT_8XX_H_ */
