/** @file dcc.h
*   @brief DCC Driver Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __DCC_H__
#define __DCC_H__

#include "reg_dcc.h"



/* DCC General Definitions */

/** @def dcc1CNT0_CLKSRC_HFLPO
*   @brief Alias name for DCC1 Counter 0 Clock Source HFLPO
*
*   This is an alias name for the Clock Source HFLPO for DCC1 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc1CNT0_CLKSRC_HFLPO 0x00000005U

/** @def dcc1CNT0_CLKSRC_TCK
*   @brief Alias name for DCC1 Counter 0 Clock Source TCK
*
*   This is an alias name for the Clock Source TCK for DCC1 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc1CNT0_CLKSRC_TCK 0x0000000AU

/** @def dcc1CNT0_CLKSRC_OSCIN
*   @brief Alias name for DCC1 Counter 0 Clock Source OSCIN
*
*   This is an alias name for the Clock Source OSCIN for DCC1 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc1CNT0_CLKSRC_OSCIN 0x0000000FU

/** @def dcc1CNT1_CLKSRC_PLL1
*   @brief Alias name for DCC1 Counter 1 Clock Source PLL1
*
*   This is an alias name for the Clock Source PLL for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_PLL1 0x0000A0000U

/** @def dcc1CNT1_CLKSRC_PLL2
*   @brief Alias name for DCC1 Counter 1 Clock Source PLL2
*
*   This is an alias name for the Clock Source OSCIN for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_PLL2 0x0000A0001U

/** @def dcc1CNT1_CLKSRC_LFLPO
*   @brief Alias name for DCC1 Counter 1 Clock Source LFLPO
*
*   This is an alias name for the Clock Source LFLPO for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_LFLPO 0x0000A0002U

/** @def dcc1CNT1_CLKSRC_HFLPO
*   @brief Alias name for DCC1 Counter 1 Clock Source HFLPO
*
*   This is an alias name for the Clock Source HFLPO for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_HFLPO 0x0000A0003U

/** @def dcc1CNT1_CLKSRC_EXTCLKIN1
*   @brief Alias name for DCC1 Counter 1 Clock Source EXTCLKIN1
*
*   This is an alias name for the Clock Source EXTCLKIN1 for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_EXTCLKIN1 0x0000A0005U

/** @def dcc1CNT1_CLKSRC_EXTCLKIN2
*   @brief Alias name for DCC1 Counter 1 Clock Source EXTCLKIN2
*
*   This is an alias name for the Clock Source EXTCLKIN2 for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_EXTCLKIN2 0x0000A0006U

/** @def dcc1CNT1_CLKSRC_VCLK
*   @brief Alias name for DCC1 Counter 1 Clock Source VCLK
*
*   This is an alias name for the Clock Source VCLK for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_VCLK 0x0000A0008U

/** @def dcc1CNT1_CLKSRC_N2HET1_31
*   @brief Alias name for DCC1 Counter 1 Clock Source N2HET1_31
*
*   This is an alias name for the Clock Source N2HET1_31 for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_N2HET1_31 0x00005000FU

/** @def dcc2CNT0_CLKSRC_TCK
*   @brief Alias name for DCC2 Counter 0 Clock Source TCK
*
*   This is an alias name for the Clock Source TCK for DCC2 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc2CNT0_CLKSRC_TCK 0x0000000AU

/** @def dcc1CNT0_CLKSRC_OSCIN
*   @brief Alias name for DCC1 Counter 0 Clock Source OSCIN
*
*   This is an alias name for the Clock Source OSCIN for DCC2 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc2CNT0_CLKSRC_OSCIN 0x0000000FU

/** @def dcc2CNT1_CLKSRC_VCLK
*   @brief Alias name for DCC2 Counter 1 Clock Source VCLK
*
*   This is an alias name for the Clock Source VCLK for DCC2 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc2CNT1_CLKSRC_VCLK 0x0000A0008U

/** @def dcc2CNT1_CLKSRC_N2HET1_0
*   @brief Alias name for DCC2 Counter 1 Clock Source N2HET2_0
*
*   This is an alias name for the Clock Source N2HET2_0 for DCC2 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc2CNT1_CLKSRC_N2HET1_0 0x00005000FU

/** @def dccNOTIFICATION_DONE
*   @brief Alias name for DCC Done notification
*
*   This is an alias name for the DCC Done notification.
*
*   @note This value should be used for API argument @a notification
*/
#define dccNOTIFICATION_DONE 0x0000A000U

/** @def dccNOTIFICATION_ERROR
*   @brief Alias name for DCC Error notification
*
*   This is an alias name for the DCC Error notification.
*
*   @note This value should be used for API argument @a notification
*/
#define dccNOTIFICATION_ERROR 0x000000A0U


/** @enum dcc1clocksource
*   @brief Alias names for dcc clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*/
enum dcc1clocksource
{
    DCC1_CNT0_HF_LPO	= 0x5U,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 0*/
	DCC1_CNT0_TCK		= 0xAU,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 1*/
	DCC1_CNT0_OSCIN		= 0xFU,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 2*/

    DCC1_CNT1_PLL1		= 0x0U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 0*/
    DCC1_CNT1_PLL2		= 0x1U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 1*/
	DCC1_CNT1_LF_LPO	= 0x2U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 2*/
	DCC1_CNT1_HF_LPO	= 0x3U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 3*/
	DCC1_CNT1_EXTCLKIN1 = 0x5U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 4*/
	DCC1_CNT1_EXTCLKIN2 = 0x6U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 6*/
	DCC1_CNT1_VCLK		= 0x8U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 8*/
	DCC1_CNT1_N2HET1_31	= 0xAU	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 9*/
};

/** @enum dcc2clocksource
*   @brief Alias names for dcc clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*/
enum dcc2clocksource
{
    DCC2_CNT0_OSCIN		= 0xFU,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 0*/
    DCC2_CNT0_TCK		= 0xAU,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 2*/

   	DCC2_CNT1_VCLK		= 0x8U,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 8*/
	DCC2_CNT1_N2HET2_0	= 0xAU	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 9*/
};

/* Configuration registers */
typedef struct dcc_config_reg
{
    uint32 CONFIG_GCTRL;
    uint32 CONFIG_CNT0SEED;
    uint32 CONFIG_VALID0SEED;
    uint32 CONFIG_CNT1SEED;
    uint32 CONFIG_CLKSRC1;
    uint32 CONFIG_CLKSRC0;
} dcc_config_reg_t;

/* Configuration registers initial value */
#define DCC1_GCTRL_CONFIGVALUE		0xAU | (0xAU << 4U) | (0x5U << 8U) | (0xAU << 12U)
#define DCC1_CNT0SEED_CONFIGVALUE	39204U
#define DCC1_VALID0SEED_CONFIGVALUE	792U
#define DCC1_CNT1SEED_CONFIGVALUE	495000U
#define DCC1_CLKSRC1_CONFIGVALUE	(10U << 12U) | DCC1_CNT1_PLL1
/*SAFETYMCUSW 79 S MR:19.4 <REVIEWED> "Macro filled using GUI parameter cannot be avoided" */
#define DCC1_CLKSRC0_CONFIGVALUE	DCC1_CNT0_OSCIN

#define DCC2_GCTRL_CONFIGVALUE		0xAU | (0xAU << 4U) | (0x5U << 8U) | (0xAU << 12U)
#define DCC2_CNT0SEED_CONFIGVALUE	0U
#define DCC2_VALID0SEED_CONFIGVALUE	0U
#define DCC2_CNT1SEED_CONFIGVALUE	0U
#define DCC2_CLKSRC1_CONFIGVALUE	(0x5U << 12U) | DCC2_CNT1_VCLK
/*SAFETYMCUSW 79 S MR:19.4 <REVIEWED> "Macro filled using GUI parameter cannot be avoided" */
#define DCC2_CLKSRC0_CONFIGVALUE		DCC2_CNT0_OSCIN

/**
 *  @defgroup DCC DCC
 *  @brief Dual-Clock Comparator Module
 *
 *  The primary purpose of a DCC module is to measure the frequency of a clock signal using a second
 *  known clock signal as a reference. This capability can be used to ensure the correct frequency range for
 *  several different device clock sources, thereby enhancing the system safety metrics.
 *
 *	Related Files
 *   - reg_dcc.h
 *   - dcc.h
 *   - dcc.c
 *  @addtogroup DCC
 *  @{
 */

/* DCC Interface Functions */
void dccInit(void);
void dccSetCounter0Seed(dccBASE_t  *dcc, uint32 cnt0seed);
void dccSetTolerance(dccBASE_t  *dcc, uint32 valid0seed);
void dccSetCounter1Seed(dccBASE_t  *dcc, uint32 cnt1seed);
void dccSetSeed(dccBASE_t  *dcc, uint32 cnt0seed, uint32 valid0seed, uint32 cnt1seed);
void dccSelectClockSource(dccBASE_t  *dcc, uint32 cnt0_Clock_Source, uint32 cnt1_Clock_Source);
void dccEnable(dccBASE_t  *dcc);
void dccDisable(dccBASE_t  *dcc);
uint32 dccGetErrStatus(dccBASE_t  *dcc);

void dccEnableNotification(dccBASE_t  *dcc, uint32 notification);
void dccDisableNotification(dccBASE_t  *dcc, uint32 notification);
void dcc1GetConfigValue(dcc_config_reg_t *config_reg, config_value_type_t type);
void dcc2GetConfigValue(dcc_config_reg_t *config_reg, config_value_type_t type);
/** @fn void dccNotification(dccBASE_t  *dcc,uint32 flags)
*   @brief Interrupt callback
*   @param[in] dcc   - dcc module base address
*   @param[in] flags - status flags
*
* This is a callback function provided by the application.  It is call when
* a dcc is complete or detected error.
*/
void dccNotification(dccBASE_t  *dcc,uint32 flags);

/**@}*/
#endif
