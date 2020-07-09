/*
 * @brief LPC8xx Analog comparator driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
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

#ifndef __ACMP_8XX_H_
#define __ACMP_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ACMP_8XX CHIP: LPC8xx Analog Comparator driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief Analog Comparator register block structure
 */
typedef struct {			/*!< ACMP Structure */
	__IO uint32_t  CTRL;	/*!< Comparator control register */
	__IO uint32_t  LAD;		/*!< Voltage ladder register */
} LPC_CMP_T;

/* Reserved bits masks for registers */
#define ACMP_CTRL_RESERVED   (7|(1<<5)|(1<<7)|(0x3f<<14)|(1<<22)|(1<<24)|(0x1fu<<27))
#define ACMP_LAD_RESERVED    (~0x7f)

#define ACMP_COMPSA_BIT      (1 << 6)	/* Comparator output control bit */
#define ACMP_COMPSTAT_BIT    (1 << 21)	/* Comparator status, reflects the state of the comparator output */
#define ACMP_COMPEDGE_BIT    (1 << 23)	/* Comparator edge-detect status */
#define ACMP_LADENAB_BIT     (1 << 0)	/* Voltage ladder enable bit */

/* EDGECLR interrupt clear bit, write 1, then 0 */
#define ACMP_EDGECLR_BIT     (1 << 20)
#define ACMP_EDGESEL_MASK    (0x3 << 3)
#define ACMP_COMPVPSEL_MASK  (0x7 << 8)
#define ACMP_COMPVMSEL_MASK  (0x7 << 11)
#define ACMP_HYSTERESIS_MASK (0x3 << 25)
#define ACMP_LADSEL_MASK     (0x1F << 1)
#define ACMP_LADREF_MASK     (0x1 << 6)

/** Edge selection for comparator */
typedef enum {
	ACMP_EDGESEL_FALLING = (0 << 3),	/* Set the COMPEDGE bit on falling edge */
	ACMP_EDGESEL_RISING  = (1 << 3),	/* Set the COMPEDGE bit on rising edge */
	ACMP_EDGESEL_BOTH    = (2 << 3)		/* Set the COMPEDGE bit on falling and rising edges */
} ACMP_EDGESEL_T;

/** Hysteresis selection for comparator */
typedef enum {
	ACMP_HYS_NONE = (0 << 25),	/* No hysteresis (the output will switch as the voltages cross) */
	ACMP_HYS_5MV  = (1 << 25),	/* 5mV hysteresis */
	ACMP_HYS_10MV = (2 << 25),	/* 10mV hysteresis */
	ACMP_HYS_20MV = (3 << 25)	/* 20mV hysteresis */
} ACMP_HYS_T;

/**
 * Analog Comparator positive input values
 */
typedef enum CHIP_ACMP_POS_INPUT {
	ACMP_POSIN_VLO      = (0 << 8),	/*!< Voltage ladder output */
	ACMP_POSIN_ACMP_I1  = (1 << 8),	/*!< ACMP_I1 pin */
	ACMP_POSIN_ACMP_I2  = (2 << 8),	/*!< ACMP_I2 pin */
	ACMP_POSIN_ACMP_I3  = (3 << 8),	/*!< ACMP_I3 pin */
	ACMP_POSIN_ACMP_I4  = (4 << 8),	/*!< ACMP_I4 pin */
#if defined(CHIP_LPC82X)
	ACMP_POSIN_INT_REF  = (5 << 8),	/*!< Internal reference voltage */
	ACMP_POSIN_ADC_0    = (6 << 8),	/*!< ADC_0 Input */
#else
	ACMP_POSIN_INT_REF  = (6 << 8),	/*!< Internal reference voltage */
#endif
} ACMP_POS_INPUT_T;

/**
 * Analog Comparator negative input values
 */
typedef enum CHIP_ACMP_NEG_INPUT {
	ACMP_NEGIN_VLO     = (0 << 11),	/*!< Voltage ladder output */
	ACMP_NEGIN_ACMP_I1 = (1 << 11),	/*!< ACMP_I1 pin */
	ACMP_NEGIN_ACMP_I2 = (2 << 11),	/*!< ACMP_I2 pin */
	ACMP_NEGIN_ACMP_I3 = (3 << 11),	/*!< ACMP_I3 pin */
	ACMP_NEGIN_ACMP_I4 = (4 << 11),	/*!< ACMP_I4 pin */
#if defined(CHIP_LPC82X)
	ACMP_NEGIN_INT_REF = (5 << 11),	/*!< Internal reference voltage */
	ACMP_NEGIN_ADC_0   = (6 << 11),	/*!< ADC_0 Input */
#else
	ACMP_NEGIN_INT_REF = (6 << 11)	/*!< Internal reference voltage */
#endif
} ACMP_NEG_INPUT_T;

/**
 * @brief	Initializes the ACMP
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
void Chip_ACMP_Init(LPC_CMP_T *pACMP);

/**
 * @brief	Deinitializes the ACMP
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
void Chip_ACMP_Deinit(LPC_CMP_T *pACMP);

/**
 * @brief	Returns the current comparator status
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Status is an Or'ed value of ACMP_COMPSTAT_BIT or ACMP_COMPEDGE_BIT
 */
STATIC INLINE uint32_t Chip_ACMP_GetCompStatus(LPC_CMP_T *pACMP)
{
	return pACMP->CTRL & (ACMP_COMPSTAT_BIT | ACMP_COMPEDGE_BIT);
}

/**
 * @brief	Clears the ACMP interrupt (EDGECLR bit)
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
void Chip_ACMP_EdgeClear(LPC_CMP_T *pACMP);

/**
 * @brief	Sets up ACMP edge selection
 * @param	pACMP	: Pointer to Analog Comparator block
 * @param	edgeSel	: Edge selection value
 * @return	Nothing
 */
void Chip_ACMP_SetEdgeSelection(LPC_CMP_T *pACMP, ACMP_EDGESEL_T edgeSel);

/**
 * @brief	Synchronizes Comparator output to bus clock
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
STATIC INLINE void Chip_ACMP_EnableSyncCompOut(LPC_CMP_T *pACMP)
{
	pACMP->CTRL = ACMP_COMPSA_BIT | (pACMP->CTRL & ~ACMP_CTRL_RESERVED);
}

/**
 * @brief	Sets comparator output to be used directly (no sync)
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
STATIC INLINE void Chip_ACMP_DisableSyncCompOut(LPC_CMP_T *pACMP)
{
	pACMP->CTRL &= ~(ACMP_COMPSA_BIT | ACMP_CTRL_RESERVED);
}

/**
 * @brief	Selects positive voltage input
 * @param	pACMP		: Pointer to Analog Comparator block
 * @param	Posinput	: one of the positive input voltage sources
 * @return	Nothing
 */
void Chip_ACMP_SetPosVoltRef(LPC_CMP_T *pACMP, ACMP_POS_INPUT_T Posinput);

/**
 * @brief	Selects negative voltage input
 * @param	pACMP		: Pointer to Analog Comparator block
 * @param	Neginput	: one of the negative input voltage sources
 * @return	Nothing
 */
void Chip_ACMP_SetNegVoltRef(LPC_CMP_T *pACMP, ACMP_NEG_INPUT_T Neginput);

/**
 * @brief	Selects hysteresis level
 * @param	pACMP	: Pointer to Analog Comparator block
 * @param   hys     : Selected Hysteresis level
 * @return	Nothing
 */
void Chip_ACMP_SetHysteresis(LPC_CMP_T *pACMP, ACMP_HYS_T hys);

/**
 * @brief	Helper function for setting up ACMP control
 * @param	pACMP		: Pointer to Analog Comparator block
 * @param	edgeSel		: Edge selection value
 * @param	Posinput	: one of the positive input voltage sources
 * @param	Neginput	: one of the negative input voltage sources
 * @param	hys			: Selected Hysteresis level
 * @return	Nothing
 */
void Chip_ACMP_SetupAMCPRefs(LPC_CMP_T *pACMP, ACMP_EDGESEL_T edgeSel,
							 ACMP_POS_INPUT_T Posinput, ACMP_NEG_INPUT_T Neginput,
							 ACMP_HYS_T hys);

/**
 * @brief	Sets up voltage ladder
 * @param	pACMP			: Pointer to Analog Comparator block
 * @param	ladsel			: Voltage ladder value (0 .. 31)
 * @param	ladrefVDDCMP	: Selects the reference voltage Vref for the voltage ladder
 *							: false for VDD, true for VDDCMP pin
 * @return	Nothing
 */
void Chip_ACMP_SetupVoltLadder(LPC_CMP_T *pACMP, uint32_t ladsel, bool ladrefVDDCMP);

/**
 * @brief	Enables voltage ladder
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
STATIC INLINE void Chip_ACMP_EnableVoltLadder(LPC_CMP_T *pACMP)
{
	pACMP->LAD = ACMP_LADENAB_BIT | (pACMP->LAD & ~ACMP_LAD_RESERVED);
}

/**
 * @brief	Disables voltage ladder
 * @param	pACMP	: Pointer to Analog Comparator block
 * @return	Nothing
 */
STATIC INLINE void Chip_ACMP_DisableVoltLadder(LPC_CMP_T *pACMP)
{
	pACMP->LAD &= ~(ACMP_LADENAB_BIT | ACMP_LAD_RESERVED);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ACMP_8XX_H_ */
