/*
 * @brief LPC8xx Pin Interrupt and Pattern Match Registers and driver
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

#ifndef __PININT_8XX_H_
#define __PININT_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PININT_8XX CHIP: LPC8xx Pin Interrupt and Pattern Match driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief LPC8xx Pin Interrupt and Pattern Match register block structure
 */
typedef struct {			/*!< (@ 0xA0004000) PIN_INT Structure */
	__IO uint32_t ISEL;		/*!< (@ 0xA0004000) Pin Interrupt Mode register */
	__IO uint32_t IENR;		/*!< (@ 0xA0004004) Pin Interrupt Enable (Rising) register */
	__IO uint32_t SIENR;	/*!< (@ 0xA0004008) Set Pin Interrupt Enable (Rising) register */
	__IO uint32_t CIENR;	/*!< (@ 0xA000400C) Clear Pin Interrupt Enable (Rising) register */
	__IO uint32_t IENF;		/*!< (@ 0xA0004010) Pin Interrupt Enable Falling Edge / Active Level register */
	__IO uint32_t SIENF;	/*!< (@ 0xA0004014) Set Pin Interrupt Enable Falling Edge / Active Level register */
	__IO uint32_t CIENF;	/*!< (@ 0xA0004018) Clear Pin Interrupt Enable Falling Edge / Active Level address */
	__IO uint32_t RISE;		/*!< (@ 0xA000401C) Pin Interrupt Rising Edge register */
	__IO uint32_t FALL;		/*!< (@ 0xA0004020) Pin Interrupt Falling Edge register */
	__IO uint32_t IST;		/*!< (@ 0xA0004024) Pin Interrupt Status register */
	__IO uint32_t PMCTRL;	/*!< (@ 0xA0004028) GPIO pattern match interrupt control register          */
	__IO uint32_t PMSRC;	/*!< (@ 0xA000402C) GPIO pattern match interrupt bit-slice source register */
	__IO uint32_t PMCFG;	/*!< (@ 0xA0004030) GPIO pattern match interrupt bit slice configuration register */
} LPC_PININT_T;

/* Reserved bits masks for registers */
#define PININT_ISEL_RESERVED    (~0xff)
#define PININT_IENR_RESERVED    (~0xff)
#define PININT_SIENR_RESERVED   (~0xff)
#define PININT_CIENR_RESERVED   (~0xff)
#define PININT_IENF_RESERVED    (~0xff)
#define PININT_SIENF_RESERVED   (~0xff)
#define PININT_CIENF_RESERVED   (~0xff)
#define PININT_RISE_RESERVED    (~0xff)
#define PININT_FALL_RESERVED    (~0xff)
#define PININT_IST_RESERVED     (~0xff)
#define PININT_PMCTRL_RESERVED  (~0xff000003)
#define PININT_PMSRC_RESERVED   0xff
#define PININT_PMCFG_RESERVED   (1<<7)

/**
 * LPC8xx Pin Interrupt and Pattern match engine register
 * bit fields and macros
 */
/* PININT interrupt control register */
#define PININT_PMCTRL_PMATCH_SEL (1 << 0) 
#define PININT_PMCTRL_RXEV_ENA   (1 << 1) 

/* PININT Bit slice source register bits */
#define PININT_SRC_BITSOURCE_START  8
#define PININT_SRC_BITSOURCE_MASK   7

/* PININT Bit slice configuration register bits */
#define PININT_SRC_BITCFG_START  8
#define PININT_SRC_BITCFG_MASK   7

/**
 * LPC8xx Pin Interrupt channel values
 */
#define PININTCH0         (1 << 0)
#define PININTCH1         (1 << 1)
#define PININTCH2         (1 << 2)
#define PININTCH3         (1 << 3)
#define PININTCH4         (1 << 4)
#define PININTCH5         (1 << 5)
#define PININTCH6         (1 << 6)
#define PININTCH7         (1 << 7)
#define PININTCH(ch)      (1 << (ch))

/**
 * LPC8xx Pin Matching Interrupt bit slice enum values
 */
typedef enum Chip_PININT_BITSLICE {
	PININTBITSLICE0 = 0,	/*!< PININT Bit slice 0 */
	PININTBITSLICE1 = 1,	/*!< PININT Bit slice 1 */
	PININTBITSLICE2 = 2,	/*!< PININT Bit slice 2 */
	PININTBITSLICE3 = 3,	/*!< PININT Bit slice 3 */
	PININTBITSLICE4 = 4,	/*!< PININT Bit slice 4 */
	PININTBITSLICE5 = 5,	/*!< PININT Bit slice 5 */
	PININTBITSLICE6 = 6,	/*!< PININT Bit slice 6 */
	PININTBITSLICE7 = 7	/*!< PININT Bit slice 7 */
} Chip_PININT_BITSLICE_T;

/**
 * LPC8xx Pin Matching Interrupt bit slice configuration enum values
 */
typedef enum Chip_PININT_BITSLICE_CFG {
    PININT_PATTERNCONST1           = 0x0,	/*!< Contributes to product term match */
    PININT_PATTERNRISING           = 0x1,	/*!< Rising edge */    
    PININT_PATTERNFALLING          = 0x2,	/*!< Falling edge */    
    PININT_PATTERNRISINGRFALLING   = 0x3,	/*!< Rising or Falling edge */    
    PININT_PATTERNHIGH             = 0x4,	/*!< High level */    
    PININT_PATTERNLOW              = 0x5,	/*!< Low level */    
    PININT_PATTERCONST0            = 0x6,	/*!< Never contributes for match */    
    PININT_PATTEREVENT             = 0x7	/*!< Match occurs on event */    
} Chip_PININT_BITSLICE_CFG_T;

/**
 * @brief	Initialize Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block
 * @return	Nothing
 * @note	This function should be used after the Chip_GPIO_Init() function.
 */
STATIC INLINE void Chip_PININT_Init(LPC_PININT_T *pPININT) {}

/**
 * @brief	De-Initialize Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DeInit(LPC_PININT_T *pPININT) {}

/**
 * @brief	Configure the pins as edge sensitive in Pin interrupt block 
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_SetPinModeEdge(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->ISEL &= ~(pins | PININT_ISEL_RESERVED);
}

/**
 * @brief	Configure the pins as level sensitive in Pin interrupt block 
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_SetPinModeLevel(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->ISEL = pins | (pPININT->ISEL & ~PININT_ISEL_RESERVED);
    pPININT->SIENR = pins;
}

/**
 * @brief	Return current PININT rising edge or high level interrupt enable state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	A bifield containing the high edge/level interrupt enables for each
 * interrupt. Bit 0 = PININT0, 1 = PININT1, etc.
 * For each bit, a 0 means the high edge/level interrupt is disabled, while a 1
 * means it's enabled.
 */
STATIC INLINE uint32_t Chip_PININT_GetHighEnabled(LPC_PININT_T *pPININT)
{
    return pPININT->IENR & ~PININT_IENR_RESERVED;
}

/**
 * @brief	Enable high edge/level PININT interrupts for pins
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to enable (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_EnableIntHigh(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->SIENR = pins;
}

/**
 * @brief	Select high/low level for level sensitive  PININT interrupts
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to enable (ORed value of PININTCH*)
 * @return	Nothing
*/
STATIC INLINE void Chip_PININT_SelectLevel(LPC_PININT_T *pPININT, uint32_t pins, bool isHigh)
{
	if (isHigh)
    	pPININT->SIENF = pins;
    else
    	pPININT->CIENF = pins;
}


/**
 * @brief	Disable high edge/level PININT interrupts for pins
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to disable (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DisableIntHigh(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->CIENR = pins;
}

/**
 * @brief	Return current PININT falling edge or low level interrupt enable state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	A bifield containing the low edge/level interrupt enables for each
 * interrupt. Bit 0 = PININT0, 1 = PININT1, etc.
 * For each bit, a 0 means the low edge/level interrupt is disabled, while a 1
 * means it's enabled.
 */
STATIC INLINE uint32_t Chip_PININT_GetLowEnabled(LPC_PININT_T *pPININT)
{
    return pPININT->IENF & ~PININT_IENF_RESERVED;
}

/**
 * @brief	Enable low edge/level PININT interrupts for pins
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to enable (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_EnableIntLow(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->SIENF = pins;
}

/**
 * @brief	Disable low edge/level PININT interrupts for pins
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins to disable (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DisableIntLow(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->CIENF = pins;
}

/**
 * @brief	Return pin states that have a detected latched high edge (RISE) state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	PININT states (bit n = high) with a latched rise state detected
 */
STATIC INLINE uint32_t Chip_PININT_GetRiseStates(LPC_PININT_T *pPININT)
{
    return pPININT->RISE & ~PININT_RISE_RESERVED;
}

/**
 * @brief	Clears pin states that had a latched high edge (RISE) state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins with latched states to clear
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_ClearRiseStates(LPC_PININT_T *pPININT, uint32_t pins)
{
		pPININT->RISE = pins;
}

/**
 * @brief	Return pin states that have a detected latched falling edge (FALL) state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	PININT states (bit n = high) with a latched rise state detected
 */
STATIC INLINE uint32_t Chip_PININT_GetFallStates(LPC_PININT_T *pPININT)
{
    return pPININT->FALL & ~PININT_FALL_RESERVED;
}

/**
 * @brief	Clears pin states that had a latched falling edge (FALL) state
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pins with latched states to clear
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_ClearFallStates(LPC_PININT_T *pPININT, uint32_t pins)
{
		pPININT->FALL = pins;
}

/**
 * @brief	Get interrupt status from Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	Interrupt status (bit n for PININTn = high means interrupt ie pending)
 */
STATIC INLINE uint32_t Chip_PININT_GetIntStatus(LPC_PININT_T *pPININT)
{
    return pPININT->IST& ~PININT_IST_RESERVED;
}

/**
 * @brief	Clear interrupt status in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	pins	: Pin interrupts to clear (ORed value of PININTCH*)
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_ClearIntStatus(LPC_PININT_T *pPININT, uint32_t pins)
{
    pPININT->IST = pins;
}

/**
 * @brief	Set source for pattern match in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @param	chan	: PININT channel number (From 0 to 7)
 * @param	slice	: PININT slice number
 * @return	Nothing
 */
void Chip_PININT_SetPatternMatchSrc(LPC_PININT_T *pPININT, uint8_t chan, Chip_PININT_BITSLICE_T slice);

/**
 * @brief	Configure the pattern matcch in Pin interrupt block
 * @param	pPININT		: The base address of Pin interrupt block 
 * @param	slice		: PININT slice number
 * @param	slice_cfg	: PININT slice configuration value (enum Chip_PININT_BITSLICE_CFG_T)
 * @param	end_point	: If true, current slice is final component
 * @return	Nothing
 */
void Chip_PININT_SetPatternMatchConfig(LPC_PININT_T *pPININT, Chip_PININT_BITSLICE_T slice, 
        Chip_PININT_BITSLICE_CFG_T slice_cfg, bool end_point);

/**
 * @brief	Enable pattern match interrupts in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_EnablePatternMatch(LPC_PININT_T *pPININT)
{
    pPININT->PMCTRL = PININT_PMCTRL_PMATCH_SEL | (pPININT->PMCTRL & ~PININT_PMCTRL_RESERVED);
}

/**
 * @brief	Disable pattern match interrupts in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DisablePatternMatch(LPC_PININT_T *pPININT)
{
    pPININT->PMCTRL &= ~(PININT_PMCTRL_PMATCH_SEL | PININT_PMCTRL_RESERVED);
}

/**
 * @brief	Enable RXEV output in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_EnablePatternMatchRxEv(LPC_PININT_T *pPININT)
{
    pPININT->PMCTRL = PININT_PMCTRL_RXEV_ENA | (pPININT->PMCTRL & ~PININT_PMCTRL_RESERVED);
}

/**
 * @brief	Disable RXEV output in Pin interrupt block
 * @param	pPININT	: The base address of Pin interrupt block 
 * @return	Nothing
 */
STATIC INLINE void Chip_PININT_DisablePatternMatchRxEv(LPC_PININT_T *pPININT)
{
    pPININT->PMCTRL &= ~(PININT_PMCTRL_RXEV_ENA | PININT_PMCTRL_RESERVED);
}
    
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __PININT_8XX_H_ */
