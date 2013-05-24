/** @file sys_pmm.c
*   @brief PCR Driver Implementation File
*   @date 23.May.2013
*   @version 03.05.01
*
*/
/* (c) Texas Instruments 2009-2013, All rights reserved. */

#include "sys_pmm.h"

/** @fn void pmmInit(void)
*   @brief Initializes the PMM Driver
*
*   This function initializes the PMM module.
*/
void pmmInit(void)
{
	/*Disable clocks to all logic domains*/
	pmmREG->PDCLKDISREG = 0xFU;
	/*Enable or disable clock to pmctrl_wakeup block and automatic clock wake up*/
	pmmREG->GLOBALCTRL1 = (0U << 8U) | (0U << 0U); /*from GUI*/
	/*Power on the logic power domains*/
	pmmREG->LOGICPDPWRCTRL0 = PMM_LOGICPDPWRCTRL0_CONFIGVALUE;
	/*Power on the memory-only power domains*/
	pmmREG->MEMPDPWRCTRL0 = PMM_MEMPDPWRCTRL0_CONFIGVALUE;

	/*wait till Logic Power Domain PD2 turns ON*/
		while((pmmREG->LOGICPDPWRSTAT[PMM_LOGICPD2] & PMM_LOGICPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
		/*wait till Logic Power Domain PD3 turns ON*/
		while((pmmREG->LOGICPDPWRSTAT[PMM_LOGICPD3] & PMM_LOGICPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
		/*wait till Logic Power Domain PD4 turns OFF*/
		while((pmmREG->LOGICPDPWRSTAT[PMM_LOGICPD4] & PMM_LOGICPDPWRSTAT_LOGICPDPWRSTAT) != 0U)
		{ 
		}/* Wait */  
		/*wait till Logic Power Domain PD5 turns ON*/
		while((pmmREG->LOGICPDPWRSTAT[PMM_LOGICPD5] & PMM_LOGICPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  

		/*wait till Memory Only Power Domain RAM_PD1 turns ON*/
		while((pmmREG->MEMPDPWRSTAT[PMM_MEMPD1] & PMM_MEMPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
		/*wait till Memory Only Power Domain RAM_PD2 turns ON*/
		while((pmmREG->MEMPDPWRSTAT[PMM_MEMPD2] & PMM_MEMPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
		/*wait till Memory Only Power Domain RAM_PD3 turns ON*/
		while((pmmREG->MEMPDPWRSTAT[PMM_MEMPD3] & PMM_MEMPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
	if ((pmmREG->GLOBALCTRL1 & PMM_GLOBALCTRL1_AUTOCLKWAKEENA) == 0U)
	{
		/* Enable clocks for the selected logic domain */
		pmmREG->PDCLKDISREG = PMM_PDCLKDISREG_CONFIGVALUE;
	}

}


/** @fn void pmmTurnONLogicPowerDomain(pmm_LogicPD_t logicPD)
*   @brief Turns on Logic Power Domain
*   @param[in] logicPD - Power Domain to be turned on
*              - PMM_LOGICPD2: Power domain PD2 will be turned on
*              - PMM_LOGICPD3: Power domain PD3 will be turned on
*              - PMM_LOGICPD4: Power domain PD4 will be turned on
*              - PMM_LOGICPD5: Power domain PD5 will be turned on
*
*   This function turns on the selected Logic Power Domain
*
*/
void pmmTurnONLogicPowerDomain(pmm_LogicPD_t logicPD)
{
	if (logicPD != PMM_LOGICPD1)
	{
		/* Power on the domain */
		if (logicPD == PMM_LOGICPD2)
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xF0FFFFFFU) | (0x5U << 24U);
		}
		else if (logicPD == PMM_LOGICPD3)
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xFFF0FFFFU) | (0x5U << 16U);
		}
		else if (logicPD == PMM_LOGICPD4)
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xFFFFF0FFU) | (0x5U << 8U);
		}
		else
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xFFFFFFF0U) | (0x5U << 0U);
		}
		/* Wait until the power domain turns on */
		while((pmmREG->LOGICPDPWRSTAT[logicPD] & PMM_LOGICPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
		if ((pmmREG->GLOBALCTRL1 & PMM_GLOBALCTRL1_AUTOCLKWAKEENA) == 0U)
		{
			/* Enable clocks to the power domain */
			pmmREG->PDCLKDISCLRREG = 1U << (uint32)logicPD;
		}
	}
}

/** @fn void pmmTurnONMemPowerDomain(pmm_MemPD_t memPD)
*   @brief Turns on Memory Power Domain
*   @param[in] memPD - Power Domain to be tured on
*              - PMM_MEMPD1: Power domain RAM_PD1 will be turned on
*              - PMM_MEMPD2: Power domain RAM_PD2 will be turned on
*              - PMM_MEMPD3: Power domain RAM_PD3 will be turned on
*
*   This function turns on the selected Memory Power Domain
*
*/
void pmmTurnONMemPowerDomain(pmm_MemPD_t memPD)
{
	/* Power on the domain */
	if (memPD == PMM_MEMPD1)
	{
		pmmREG->MEMPDPWRCTRL0 = (pmmREG->MEMPDPWRCTRL0 & 0xF0FFFFFFU) | (0x5U << 24U);
	}
	else if (memPD == PMM_MEMPD2)
	{
		pmmREG->MEMPDPWRCTRL0 = (pmmREG->MEMPDPWRCTRL0 & 0xFFF0FFFFU) | (0x5U << 16U);
	}
	else
	{
		pmmREG->MEMPDPWRCTRL0 = (pmmREG->MEMPDPWRCTRL0 & 0xFFFFF0FFU) | (0x5U << 8U);
	}
	/*Wait until the power domain turns on*/
	while((pmmREG->MEMPDPWRSTAT[memPD] & PMM_MEMPDPWRSTAT_DOMAINON) == 0U)
		{ 
		}/* Wait */  
}

/** @fn void pmmTurnOFFLogicPowerDomain(pmm_LogicPD_t logicPD)
*   @brief Turns off Logic Power Domain
*	@param[in] logicPD - Power Domain to be tured off
*              - PMM_LOGICPD2: Power domain PD2 will be turned off
*              - PMM_LOGICPD3: Power domain PD3 will be turned off
*              - PMM_LOGICPD4: Power domain PD4 will be turned off
*              - PMM_LOGICPD5: Power doamin PD5 will be turned off
*
*   This function turns off the selected Logic Power Domain
*
*/
void pmmTurnOFFLogicPowerDomain(pmm_LogicPD_t logicPD)
{
	if (logicPD != PMM_LOGICPD1)
	{
		/* Disable all clocks to the power domain */
		pmmREG->PDCLKDISSETREG = 1U << (uint32)logicPD;
		
		/* Power down the domain */
		if (logicPD == PMM_LOGICPD2)
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xF0FFFFFFU) | (0xAU << 24U);
		}
		else if (logicPD == PMM_LOGICPD3)
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xFFF0FFFFU) | (0xAU << 16U);
		}
		else if (logicPD == PMM_LOGICPD4)
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xFFFFF0FFU) | (0xAU << 8U);
		}
		else
		{
			pmmREG->LOGICPDPWRCTRL0 = (pmmREG->LOGICPDPWRCTRL0 & 0xFFFFFFF0U) | (0xAU << 0U);
		}
		/* Wait until the power domain turns off */
		while((pmmREG->LOGICPDPWRSTAT[logicPD] & PMM_LOGICPDPWRSTAT_LOGICPDPWRSTAT) != 0U)
		{ 
		}/* Wait */  
	}
}

/** @fn void pmmTurnOFFMemPowerDomain(pmm_MemPD_t memPD)
*   @brief Turns off Memory Power Domain
*   @param[in] memPD - Power Domain to be tured off
*              - PMM_MEMPD1: Power domain RAM_PD1 will be turned off
*              - PMM_MEMPD2: Power domain RAM_PD2 will be turned off
*              - PMM_MEMPD3: Power domain RAM_PD3 will be turned off
*
*   This function turns off the selected Memory Power Domain
*
*/
void pmmTurnOFFMemPowerDomain(pmm_MemPD_t memPD)
{
	/* Power down the domain */
	if (memPD == PMM_MEMPD1)
	{
		pmmREG->MEMPDPWRCTRL0 = (pmmREG->MEMPDPWRCTRL0 & 0xF0FFFFFFU) | (0xAU << 24U);
	}
	else if (memPD == PMM_MEMPD2)
	{
		pmmREG->MEMPDPWRCTRL0 = (pmmREG->MEMPDPWRCTRL0 & 0xFFF0FFFFU) | (0xAU << 16U);
	}
	else
	{
		pmmREG->MEMPDPWRCTRL0 = (pmmREG->MEMPDPWRCTRL0 & 0xFFFFF0FFU) | (0xAU << 8U);
	}
	/*Wait until the power domain turns off*/
	while((pmmREG->MEMPDPWRSTAT[memPD] & PMM_MEMPDPWRSTAT_MEMPDPWRSTAT) != 0U)
		{ 
		}/* Wait */  
}

/** @fn boolean pmmIsLogicPowerDomainActive(pmm_LogicPD_t logicPD)
*   @brief Check if the power domain is active or not
*	@param[in] logicPD - Power Domain to be be checked
*              - PMM_LOGICPD2: Checks whether Power domain PD2 is active or not
*              - PMM_LOGICPD3: Checks whether Power domain PD3 is active or not
*              - PMM_LOGICPD4: Checks whether Power domain PD4 is active or not
*              - PMM_LOGICPD5: Checks whether Power domain PD5 is active or not
*	@return The function will return:
*              - TRUE : When the selected power domain is in Active state.
*              - FALSE: When the selected power domain is in OFF state.
*
*   This function checks whether the selected power domain is active or not.
*
*/
boolean pmmIsLogicPowerDomainActive(pmm_LogicPD_t logicPD)
{
	boolean status;
	if ((pmmREG->LOGICPDPWRSTAT[logicPD] & PMM_LOGICPDPWRSTAT_DOMAINON) == 0U)
	{
		status = FALSE;
	}
	else
	{
		status = TRUE;
	}
	return status;
}

/** @fn boolean pmmIsMemPowerDomainActive(pmm_MemPD_t memPD)
*   @brief Check if the power domain is active or not
*	@param[in] memPD - Power Domain to be tured off
*              - PMM_MEMPD1: Checks whether Power domain RAM_PD1 is active or not
*              - PMM_MEMPD2: Checks whether Power domain RAM_PD2 is active or not
*              - PMM_MEMPD3: Checks whether Power domain RAM_PD3 is active or not
*	@return The function will return:
*              - TRUE : When the selected power domain is in Active state.
*              - FALSE: When the selected power domain is in OFF state.
*
*   This function checks whether the selected power domain is active or not.
*
*/
boolean pmmIsMemPowerDomainActive(pmm_MemPD_t memPD)
{
	boolean status;
	if ((pmmREG->MEMPDPWRSTAT[memPD] & PMM_MEMPDPWRSTAT_DOMAINON) == 0U)
	{
		status = FALSE;
	}
	else
	{
		status = TRUE;
	}
	return status;
}

/** @fn void pmmGetConfigValue(pmm_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration register
*	@param[in] *config_reg - pointer to the struct to which the initial or current value of the configuration registers need to be stored
*	@param[in] type  - 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*/
void pmmGetConfigValue(pmm_config_reg_t *config_reg, config_value_type_t type)
{
	if (type == InitialValue)
	{
		config_reg->CONFIG_LOGICPDPWRCTRL0 = PMM_LOGICPDPWRCTRL0_CONFIGVALUE;
		config_reg->CONFIG_MEMPDPWRCTRL0 = PMM_MEMPDPWRCTRL0_CONFIGVALUE;
		config_reg->CONFIG_PDCLKDISREG = PMM_PDCLKDISREG_CONFIGVALUE;
		config_reg->CONFIG_GLOBALCTRL1 = PMM_GLOBALCTRL1_CONFIGVALUE;
	}
	else
	{
		config_reg->CONFIG_LOGICPDPWRCTRL0 = pmmREG->LOGICPDPWRCTRL0;
		config_reg->CONFIG_MEMPDPWRCTRL0 = pmmREG->MEMPDPWRCTRL0;
		config_reg->CONFIG_PDCLKDISREG = pmmREG->PDCLKDISREG;
		config_reg->CONFIG_GLOBALCTRL1 = pmmREG->GLOBALCTRL1;
	}
}

/** @fn void pmmSetMode(pmm_Mode_t mode)
*   @brief Set PSCON Compare Block Mode
*	@param[in] mode - PSCON Compare Block mode
*				- LockStep				: PSCON compare block is set to Lock-Step mode
*				- SelfTest				: PSCON compare block is set to Self-Test mode
*				- ErrorForcing			: PSCON compare block is set to Error-Forcing mode
*				- SelfTestErrorForcing	: PSCON compare block is set to Self-Test-Error-Forcing mode
*
*   This function sets the PSCON Compare block to the selected mode
*
*/
void pmmSetMode(pmm_Mode_t mode)
{
	/* Set PSCON Compare Block Mode */
	pmmREG->PRCKEYREG = mode;
}

/** @fn boolean pmmPerformSelfTest(void)
*   @brief Perform self test and return the result
*
*	@return The function will return
*			- TRUE if PSCON compare block passed self-test
*			- FALSE if PSCON compare block failed in self-test
*
*   This function checks whether PSCON compare block passed the self-test or not.
*
*/
boolean pmmPerformSelfTest(void)
{
	boolean status = TRUE;
	/*Enter self-test mode*/
	pmmREG->PRCKEYREG = SelfTest;
	/*Wait till self test is completed*/
	while ((pmmREG->LPDDCSTAT1 & 0xFU) != 0xFU)
	{ 
	}/* Wait */ 				
	
	while ((pmmREG->MPDDCSTAT1 & 0x7U) != 0x7U)
	{ 
	}/* Wait */ 				

	/*Check whether self-test passed or not*/
	if ((pmmREG->LPDDCSTAT2 & 0xFU) != 0U)
	{
		status = FALSE;
	}
	if ((pmmREG->MPDDCSTAT2 & 0x7U) != 0U)
	{
		status = FALSE;
	}
	/*Enter lock-step mode*/
	pmmREG->PRCKEYREG = LockStep;

	return status;
}
