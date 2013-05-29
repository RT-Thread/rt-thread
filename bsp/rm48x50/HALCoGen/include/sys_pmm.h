/** @file sys_pmm.h
*   @brief PMM Driver Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __SYS_PMM_H__
#define __SYS_PMM_H__

#include "reg_pmm.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Bit Masks */
#define PMM_LOGICPDPWRCTRL0_LOGICPDON0      (0xFU << 24U)		/*PD2*/
#define PMM_LOGICPDPWRCTRL0_LOGICPDON1      (0xFU << 16U)		/*PD3*/
#define PMM_LOGICPDPWRCTRL0_LOGICPDON2      (0xFU << 8U)		/*PD4*/
#define PMM_LOGICPDPWRCTRL0_LOGICPDON3      (0xFU << 0U)		/*PD5*/

#define PMM_MEMPDPWRCTRL0_MEMPDON0          (0xFU << 24U)		/*RAM_PD1*/
#define PMM_MEMPDPWRCTRL0_MEMPDON1          (0xFU << 16U)		/*RAM_PD2*/
#define PMM_MEMPDPWRCTRL0_MEMPDON2          (0xFU << 8U)		/*RAM_PD3*/

#define PMM_LOGICPDPWRSTAT_DOMAINON	        (1U << 8U)
#define PMM_LOGICPDPWRSTAT_LOGICPDPWRSTAT	(0x3U << 0U)
#define PMM_MEMPDPWRSTAT_DOMAINON	        (1U << 8U)
#define PMM_MEMPDPWRSTAT_MEMPDPWRSTAT    	(0x3U << 0U)
#define PMM_GLOBALCTRL1_AUTOCLKWAKEENA	    (1U << 0U)

/* Configuration registers initial value */
#define PMM_LOGICPDPWRCTRL0_CONFIGVALUE   (((1U)?0x5U:0xAU) << 24U) \
										| (((1U)?0x5U:0xAU) << 16U) \
										| (((0U)?0x5U:0xAU) << 8U)  \
										| (((1U)?0x5U:0xAU) << 0U)

#define PMM_MEMPDPWRCTRL0_CONFIGVALUE 	  (((1U)?0x5U:0xAU) << 24U) \
										| (((1U)?0x5U:0xAU) << 16U) \
										| (((1U)?0x5U:0xAU) << 8U)

#define PMM_PDCLKDISREG_CONFIGVALUE		  ((!1U) << 0U)\
										| ((!1U) << 1U)\
										| ((!0U) << 2U)\
										| ((!1U) << 3U)

#define PMM_GLOBALCTRL1_CONFIGVALUE		(0U << 8U) | (0U << 0U)


/** @enum pmmLogicPDTag
*   @brief PMM Logic Power Domain 
*
*   Used to define PMM Logic Power Domain
*/
typedef enum pmmLogicPDTag
{
	PMM_LOGICPD1	= 4U,	/*-- NOT USED*/
	PMM_LOGICPD2	= 0U,
	PMM_LOGICPD3	= 1U,
	PMM_LOGICPD4	= 2U,
	PMM_LOGICPD5	= 3U
}pmm_LogicPD_t;


/** @enum pmmMemPDTag
*   @brief PMM Memory-Only Power Domain 
*
*   Used to define PMM Memory-Only Power Domain
*/
typedef enum pmmMemPDTag
{
	PMM_MEMPD1 = 0U,
	PMM_MEMPD2 = 1U,
	PMM_MEMPD3 = 2U
}pmm_MemPD_t;


/** @enum pmmModeTag
*   @brief PSCON operating mode 
*
*   Used to define the operating mode of PSCON Compare Block
*/
typedef enum pmmModeTag
{
	LockStep				= 0x0U,
	SelfTest				= 0x6U,
	ErrorForcing			= 0x9U,
	SelfTestErrorForcing	= 0xFU
}pmm_Mode_t;

/*Pmm Configuration Registers*/
typedef struct pmm_config_reg
{
	uint32 CONFIG_LOGICPDPWRCTRL0;
	uint32 CONFIG_MEMPDPWRCTRL0;
	uint32 CONFIG_PDCLKDISREG;
	uint32 CONFIG_GLOBALCTRL1;
}pmm_config_reg_t;

/**
 * @defgroup PMM PMM
 * @brief Power Management Module
 *
 * The PMM provides memory-mapped registers that control the states of the supported power domains. 
 * The PMM includes interfaces to the Power Mode Controller (PMC) and the Power State Controller (PSCON). 
 * The PMC and PSCON control the power up/down sequence of each power domain.
 *
 * Related files:
 * - reg_pmm.h
 * - sys_pmm.h
 * - sys_pmm.c
 *
 * @addtogroup PMM
 * @{
 */
 
/* Pmm Interface Functions */
void pmmInit(void);
void pmmTurnONLogicPowerDomain(pmm_LogicPD_t logicPD);
void pmmTurnONMemPowerDomain(pmm_MemPD_t memPD);
void pmmTurnOFFLogicPowerDomain(pmm_LogicPD_t logicPD);
void pmmTurnOFFMemPowerDomain(pmm_MemPD_t memPD);
boolean pmmIsLogicPowerDomainActive(pmm_LogicPD_t logicPD);
boolean pmmIsMemPowerDomainActive(pmm_MemPD_t memPD);
void pmmGetConfigValue(pmm_config_reg_t *config_reg, config_value_type_t type);
void pmmSetMode(pmm_Mode_t mode);
boolean pmmPerformSelfTest(void);

/**@}*/
/* USER CODE BEGIN (1) */
/* USER CODE END */

#endif

