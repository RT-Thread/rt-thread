/*
 * @brief ADC ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef  _HW_ADC_H
#define  _HW_ADC_H

/*******************
 * INCLUDE FILES    *
 ********************/
#include <stdint.h>

#if defined( __CC_ARM   )
  #pragma anon_unions
#endif

/*******************
 * EXPORTED MACROS  *
 ********************/

/*********************
 * EXPORTED TYPEDEFS  *
 **********************/
// ------------------------------------------------------------------------------------------------
// -----                                          ADC                                         -----
// ------------------------------------------------------------------------------------------------

/**
 * @brief Product name title=UM10462 Chapter title=LPC11U1x ADC Modification date=3/16/2011 Major revision=0 Minor revision=3  (ADC)
 */

typedef struct {						/*!< (@ 0x40000000) ADC Structure          */
	volatile uint32_t CTRL;						/*!< (@ 0x40000000) A/D Control Register */
	volatile uint32_t INPUTSEL;					/*!< (@ 0x40000004) A/D Input Control Register */
	union {
		volatile uint32_t SEQ_CTRL[2];
		struct {
			volatile uint32_t SEQA_CTRL;			/*!< (@ 0x40000008) A/D SEQA Ctrl Register */
			volatile uint32_t SEQB_CTRL;			/*!< (@ 0x4000000C) A/D SEQB Ctrl Register */
		};

	};

	union {
		const volatile uint32_t SEQ_GDAT[2];
		struct {
			const volatile uint32_t SEQA_GDAT;					/*!< (@ 0x40000010) A/D SEQA Global Data Register */
			const volatile uint32_t SEQB_GDAT;					/*!< (@ 0x40000014) A/D SEQB Global Data Register */
		};

	};

	uint32_t Reserved[2];
	union {
		const volatile uint32_t DAT[12];				/*!< (@ 0x40000020) A/D Channel Data Register*/
		struct {
			const volatile uint32_t DAT0;					/*!< (@ 0x40000020) A/D Channel Data Register 0*/
			const volatile uint32_t DAT1;					/*!< (@ 0x40000024) A/D Channel Data Register 1*/
			const volatile uint32_t DAT2;					/*!< (@ 0x40000028) A/D Channel Data Register 2*/
			const volatile uint32_t DAT3;					/*!< (@ 0x4000002C) A/D Channel Data Register 3*/
			const volatile uint32_t DAT4;					/*!< (@ 0x40000030) A/D Channel Data Register 4*/
			const volatile uint32_t DAT5;					/*!< (@ 0x40000034) A/D Channel Data Register 5*/
			const volatile uint32_t DAT6;					/*!< (@ 0x40000038) A/D Channel Data Register 6*/
			const volatile uint32_t DAT7;					/*!< (@ 0x4000003C) A/D Channel Data Register 7*/
			const volatile uint32_t DAT8;					/*!< (@ 0x40000040) A/D Channel Data Register 8*/
			const volatile uint32_t DAT9;					/*!< (@ 0x40000044) A/D Channel Data Register 9*/
			const volatile uint32_t DAT10;					/*!< (@ 0x40000048) A/D Channel Data Register 10*/
			const volatile uint32_t DAT11;					/*!< (@ 0x4000004C) A/D Channel Data Register 11*/
		};

	};

	union {
		volatile uint32_t THR_LOW[2];
		struct {
			volatile uint32_t THR0_LOW;				/*!< (@ 0x40000050) A/D Low Threhold Register 0. */
			volatile uint32_t THR1_LOW;				/*!< (@ 0x40000054) A/D Low Threhold Register 1. */
		};

	};

	union {
		volatile uint32_t THR_HIGH[2];
		struct {
			volatile uint32_t THR0_HIGH;			/*!< (@ 0x40000058) A/D High Threhold Register 0. */
			volatile uint32_t THR1_HIGH;			/*!< (@ 0x4000005C) A/D High Threhold Register 1. */
		};

	};

	volatile uint32_t CHAN_THRSEL;				/*!< (@ 0x40000060) A/D Channel Threhold Select Register. */
	volatile uint32_t INTEN;					/*!< (@ 0x40000064) A/D Interrupt Enable Register. */
	volatile uint32_t FLAGS;					/*!< (@ 0x40000068) A/D Interrupt Request Flags Register. */
	volatile uint32_t STARTUP;					/*!< (@ 0x4000006C) A/D Startup Register. */
	volatile uint32_t CALIBR;					/*!< (@ 0x40000070) A/D Calibration Register. */
} ADC_REGS_T;

/** Maximum sample rate in Hz (12-bit conversions) */
#define ADC_MAX_CHANNEL_NUM         12

/**
 * @brief ADC register support bitfields and mask
 */
/** ADC Control register bit fields */
#define ADC_CR_CLKDIV_MASK      (0xFF << 0)				/*!< Mask for Clock divider value */
#define ADC_CR_CLKDIV_BITPOS    (0)							/*!< Bit position for Clock divider value */
#define ADC_CR_ASYNC_MODE       (1 << 8)
#define ADC_CR_RESOL_MASK       (0x3 << 9)				/*!< Two-bit mask for resolution */
#define ADC_CR_RESOL(n)         ((n) << 9)				/*!< 2-bits, 6(0x0),8(0x1),10(0x2),12(0x3)-bit mode enable bit */
#define ADC_CR_RESOL_BITPOS     (9)
#define ADC_CR_BYPASS           (1 << 11)					/*!< Bypass mode */
#define ADC_CR_TSAMP_MASK       (0x7 << 12)				/*!< Three-bit mask for Sample time */

/**
 * @brief ADC resolution bits 9 and 10
 */
typedef enum _ADC_RESOL_T {
	ADC_RESOL_6BIT = 0,
	ADC_RESOL_8BIT,
	ADC_RESOL_10BIT,
	ADC_RESOL_12BIT,
} ADC_RESOL_T;

/* ADC input Select register */
#define ADC_INPUTSEL_PIN            (0x0 << 0)
#define ADC_INPUTSEL_CORE_VOL       (0x1 << 0)
#define ADC_INPUTSEL_INTERNAL_VOL   (0x2 << 0)
#define ADC_INPUTSEL_TEMP_VOL       (0x3 << 0)

/** ADC Sequence Control register bit fields */
#define ADC_SEQ_CTRL_CHANSEL(n)             (1 << (n))		/*!< Channel select macro */
#define ADC_SEQ_CTRL_CHANSEL_BITPOS(n)      ((n) << 0)				/*!< Channel select macro */
#define ADC_SEQ_CTRL_CHANSEL_MASK           (0xFFF)				/*!< Channel select mask */

/** SEQ_CTRL register bit fields */
#define ADC_SEQ_CTRL_TRIGGER(n)          ((n) << 12)
#define ADC_SEQ_CTRL_TRIGGER_MASK        (0x1F << 12)
#define ADC_SEQ_CTRL_HWTRIG_POLPOS       (1 << 18)		/*!< HW trigger polarity - positive edge */
#define ADC_SEQ_CTRL_HWTRIG_SYNCBYPASS   (1 << 19)		/*!< HW trigger bypass synchronisation */
#define ADC_SEQ_CTRL_START               (1 << 26)		/*!< Start conversion enable bit */
#define ADC_SEQ_CTRL_BURST               (1 << 27)		/*!< Repeated conversion enable bit */
#define ADC_SEQ_CTRL_SINGLESTEP          (1 << 28)		/*!< Single step enable bit */
#define ADC_SEQ_CTRL_LOWPRIO             (1 << 29)		/*!< High priority enable bit (regardless of name) */
#define ADC_SEQ_CTRL_MODE_EOS            (1 << 30)		/*!< Mode End of sequence enable bit */
#define ADC_SEQ_CTRL_SEQ_ENA             (1UL << 31)	/*!< Sequence enable bit */

/** ADC global data register bit fields */
#define ADC_SEQ_GDAT_RESULT_MASK         (0xFFF << 4)	/*!< Result value mask */
#define ADC_SEQ_GDAT_RESULT_BITPOS       (4)			/*!< Result start bit position */
#define ADC_SEQ_GDAT_THCMPRANGE_MASK     (0x3 << 16)	/*!< Comparion range mask */
#define ADC_SEQ_GDAT_THCMPRANGE_BITPOS   (16)			/*!< Comparison range bit position */
#define ADC_SEQ_GDAT_THCMPCROSS_MASK     (0x3 << 18)	/*!< Comparion cross mask */
#define ADC_SEQ_GDAT_THCMPCROSS_BITPOS   (18)			/*!< Comparison cross bit position */
#define ADC_SEQ_GDAT_CHAN_MASK           (0xF << 26)	/*!< Channel number mask */
#define ADC_SEQ_GDAT_CHAN_BITPOS         (26)			/*!< Channel number bit position */
#define ADC_SEQ_GDAT_OVERRUN             (1 << 30)		/*!< Overrun bit */
#define ADC_SEQ_GDAT_DATAVALID           (1UL << 31)	/*!< Data valid bit */

/** ADC Data register bit fields */
#define ADC_DR_RESULT(n)           ((((n) >> 4) & 0xFFF))	/*!< Macro for getting the ADC data value */
#define ADC_DRTHR_RESULT(n)        ((((n) >> 4) & 0xFFFF))	/*!< Macro for getting the ADC data value along with Threshold */
#define ADC_DR_THCMPRANGE_MASK     (0x3 << 16)			/*!< Comparion range mask */
#define ADC_DR_THCMPRANGE_BITPOS   (16)					/*!< Comparison range bit position */
#define ADC_DR_THCMPRANGE(n)       (((n) >> ADC_DR_THCMPRANGE_BITPOS) & 0x3)
#define ADC_DR_THCMPCROSS_MASK     (0x3 << 18)			/*!< Comparion cross mask */
#define ADC_DR_THCMPCROSS_BITPOS   (18)					/*!< Comparison cross bit position */
#define ADC_DR_THCMPCROSS(n)       (((n) >> ADC_DR_THCMPCROSS_BITPOS) & 0x3)
#define ADC_DR_CHAN_MASK           (0xF << 26)			/*!< Channel number mask */
#define ADC_DR_CHAN_BITPOS         (26)					/*!< Channel number bit position */
#define ADC_DR_CHANNEL(n)          (((n) >> ADC_DR_CHAN_BITPOS) & 0xF)	/*!< Channel number bit position */
#define ADC_DR_OVERRUN             (1 << 30)			/*!< Overrun bit */
#define ADC_DR_DATAVALID           (1UL << 31)			/*!< Data valid bit */
#define ADC_DR_DONE(n)             (((n) >> 31))

/** ADC low/high Threshold register bit fields */
#define ADC_THR_VAL_MASK            (0xFFF << 4)		/*!< Threshold value bit mask */
#define ADC_THR_VAL_POS             (4)					/*!< Threshold value bit position */

/** ADC Threshold select register bit fields */
#define ADC_THRSEL_CHAN_SEL_THR1(n) (1 << (n))			/*!< Select THR1 register for channel n */

/** ADC Interrupt Enable register bit fields */
#define ADC_INTEN_SEQA_ENABLE       (1 << 0)			/*!< Sequence A Interrupt enable bit */
#define ADC_INTEN_SEQB_ENABLE       (1 << 1)			/*!< Sequence B Interrupt enable bit */
#define ADC_INTEN_SEQN_ENABLE(seq)  (1 << (seq))		/*!< Sequence A/B Interrupt enable bit */
#define ADC_INTEN_OVRRUN_ENABLE     (1 << 2)			/*!< Overrun Interrupt enable bit */
#define ADC_INTEN_CMP_DISBALE       (0)					/*!< Disable comparison interrupt value */
#define ADC_INTEN_CMP_OUTSIDETH     (1)					/*!< Outside threshold interrupt value */
#define ADC_INTEN_CMP_CROSSTH       (2)					/*!< Crossing threshold interrupt value */
#define ADC_INTEN_CMP_MASK          (3)					/*!< Comparison interrupt value mask */
#define ADC_INTEN_CMP_ENABLE(isel, ch) (((isel) & ADC_INTEN_CMP_MASK) << ((2 * (ch)) + 3))	/*!< Interrupt selection for channel */

/** ADC Flags register bit fields */
#define ADC_FLAGS_THCMP_MASK(ch)    (1 << (ch))		/*!< Threshold comparison status for channel */
#define ADC_FLAGS_OVRRUN_MASK(ch)   (1 << (12 + (ch)))	/*!< Overrun status for channel */
#define ADC_FLAGS_SEQA_OVRRUN_MASK  (1 << 24)			/*!< Seq A Overrun status */
#define ADC_FLAGS_SEQB_OVRRUN_MASK  (1 << 25)			/*!< Seq B Overrun status */
#define ADC_FLAGS_SEQN_OVRRUN_MASK(seq) (1 << (24 + (seq)))	/*!< Seq A/B Overrun status */
#define ADC_FLAGS_SEQA_INT_MASK     (1 << 28)			/*!< Seq A Interrupt status */
#define ADC_FLAGS_SEQB_INT_MASK     (1 << 29)			/*!< Seq B Interrupt status */
#define ADC_FLAGS_SEQN_INT_MASK(seq) (1 << (28 + (seq)))/*!< Seq A/B Interrupt status */
#define ADC_FLAGS_THCMP_INT_MASK    (1 << 30)			/*!< Threshold comparison Interrupt status */
#define ADC_FLAGS_OVRRUN_INT_MASK   (1UL << 31)			/*!< Overrun Interrupt status */

/** ADC Startup register bit fields */
#define ADC_STARTUP_ENABLE       (0x1 << 0)
#define ADC_STARTUP_INIT         (0x1 << 1)

/* ADC Calibration register definition */
#define ADC_CALIB                       (0x1 << 0)
#define ADC_CALREQD                     (0x1 << 1)

/* Depending on the mode you are running: the slowest case is using interrupt and end of conversion while BURST mode is enabled.
   For interrupt and end of sequence, the clock can be set faster. */

#endif /* _HW_ADCD_H      Do not add any thing below this line */
