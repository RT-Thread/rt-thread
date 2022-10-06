/**
 *  \file   clock.c
 *
 *  \brief  AM335X clock management APIs.
 *
 *   This file contains routines for managing AM335x clock.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "clock.h"

/*******************************************************************************
*                       EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
extern ModuleClock *ModuleClockList[];
extern ClockDomain *clockDomainList[];

/*******************************************************************************
*                       LOCAL API DECLARATIONS
*******************************************************************************/

/*	CM Internal API's*/
static void enableClock(Clock *clkPtr);

static void disableClock(Clock *clkPtr);

static void configClkDiv(ClockDivider *clkDDiv, unsigned int OPPSupported);

//static unsigned int getActiveChildCount(Clock *clk);

//static unsigned int getActiveClockCount(ClockDomain *clkDm);


/*	PLL Internal API's*/
static void configADPLLAutoIdleCtrl(ADPLL *adpllPtr);

static void setBypassClockSource(ADPLL *adpllPtr);

static void setClkMultDiv(ADPLL *adpllPtr, unsigned int OPPSupported);

static void setRelockRampCtrl(ADPLL *adpllPtr);

static void setDividerAutoGateCtrl(ClockDivider *clkDDiv);

static void setDividerAutoPDCtrl(ClockDivider *clkDDiv);

static void updateClockDivider(ClockDivider *clkDDiv, unsigned int OPPSupported);


/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief   This API will set the Auto gate control of the divider.
 *
 * \param   *clkDDiv	Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
static void setDividerAutoGateCtrl(ClockDivider *clkDDiv)
{
	HWREG(clkDDiv->dividerConfigReg) = 
		(HWREG(clkDDiv->dividerConfigReg) & (~clkDDiv->clkoutAutoGateCtrlMask)) |
													clkDDiv->clkoutAutoGateCtrl;
}


/**
 * \brief   This API will set the Auto power down control of the divider.
 *
 * \param   *clkDDiv	Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
static void setDividerAutoPDCtrl(ClockDivider *clkDDiv)
{
	if(true == clkDDiv->isPdCtrlValid)
	{
		HWREG(clkDDiv->dividerConfigReg) = 
			(HWREG(clkDDiv->dividerConfigReg) & (~clkDDiv->clkAutoPDCtrlMask)) |
														clkDDiv->clkAutoPDCtrl;
	}
}


/**
 * \brief   This API will update the clock divider
 *
 * \param   *clkDDiv	Pointer to clock divider structure
 * \param   OPPSupported	OPP supported
 *
 * \return  None.
 *
 **/
static void updateClockDivider(ClockDivider *clkDDiv, unsigned int OPPSupported)
{
	//unsigned int dividerUpdate = 0;
	
	/*	read the divider update status bit before updating the divider	*/
	//dividerUpdate = (HWREG(clkDDiv->dividerConfigReg) & clkDDiv->clkDivUpdatedStatusMask) >>
	//						clkDDiv->clkDivUpdatedStatusShift;

	/*	Configure divider value	*/
	HWREG(clkDDiv->dividerConfigReg) = 
		(HWREG(clkDDiv->dividerConfigReg) & (~clkDDiv->clkDividerMask)) |
										clkDDiv->clkDividerValue[OPPSupported];
	
	/*	Wait till the new divider value is updated	*/
	/*while(dividerUpdate == ((HWREG(clkDDiv->dividerConfigReg) & 
		clkDDiv->clkDivUpdatedStatusMask) >> clkDDiv->clkDivUpdatedStatusShift));*/ 	/*	TBD - Status not getting updated	*/
}


/**
 * \brief   This API will configure the different settings of the divider.
 *				- Clock divider
 *				- Auto gate control
 *				- Auto Power down control
 *
 * \param   *clkDDiv		Pointer to clock divider structure
 * \param   OPPSupported	OPP supported by the device
 *
 * \return  None.
 *
 **/
static void configClkDiv(ClockDivider *clkDDiv, unsigned int OPPSupported)
{
	/*	update clock divider	*/
	updateClockDivider(clkDDiv, OPPSupported);
	
	/*	Configure auto-gating control	*/
	setDividerAutoGateCtrl(clkDDiv);
	
	/*	Configure auto-power down control	*/
	setDividerAutoPDCtrl(clkDDiv);
}


/**
 * \brief   This API will configure PLL auto idle control
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
static void configADPLLAutoIdleCtrl(ADPLL *adpllPtr)
{
	HWREG(adpllPtr->autoIdleCtrlReg) = adpllPtr->autoIdleCtrlVal;
}


/**
 * \brief   This API will configure the bypass clock source selection
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
static void setBypassClockSource(ADPLL *adpllPtr)
{
	HWREG(adpllPtr->adpllConfigReg) = 
		(HWREG(adpllPtr->adpllConfigReg) & (~adpllPtr->adpllBypassClkMask)) |
												adpllPtr->adpllBypassClkSource;
}


/**
 * \brief   This API will configure multiplier, divider, and sigma-delta 
 *			divider of the PLL
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 * \param   OPPSupported	OPP supported by the device
 *
 * \return  None.
 *
 **/
static void setClkMultDiv(ADPLL *adpllPtr, unsigned int OPPSupported)
{
	/*	Configure multiplier	*/
	HWREG(adpllPtr->adpllConfigReg) = 
		(HWREG(adpllPtr->adpllConfigReg) & (~adpllPtr->adpllMultiplierMask)) |
									adpllPtr->adpllMultiplier[OPPSupported];
	
	/*	Configure divider	*/
	HWREG(adpllPtr->adpllConfigReg) = 
		(HWREG(adpllPtr->adpllConfigReg) & (~adpllPtr->adpllDividerMask)) |
									adpllPtr->adpllDivider[OPPSupported];
										
	/*	Configure sigma delta divider	*/
	HWREG(adpllPtr->adpllConfigReg) = 
		(HWREG(adpllPtr->adpllConfigReg) & (~adpllPtr->adpllSigmaDeltaDividerMask)) |
									adpllPtr->adpllSigmaDeltaDivider[OPPSupported];
}


/**
 * \brief   This API will configure the low power bypass mode
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
void setLPBypassMode(ADPLL *adpllPtr, unsigned int isNormalByp)
{
	if(CLK_LP_MODE_NORMAL == isNormalByp)
	{
		HWREG(adpllPtr->adpllModeReg) = 
			(HWREG(adpllPtr->adpllModeReg) & (~(adpllPtr->adpllLowPowerMask))) |
											adpllPtr->adpllLowPowerNormalVal;
		/*	Wait till the PLL is LOCKED	*/
		while(((HWREG(adpllPtr->idleStatusReg) & adpllPtr->adpllClkStatusMask) >> adpllPtr->adpllClkStatusShift) != 0x1);		
	}

	if(CLK_LP_MODE_BYPASS == isNormalByp)
	{
		HWREG(adpllPtr->adpllModeReg) = 
			(HWREG(adpllPtr->adpllModeReg) & (~(adpllPtr->adpllLowPowerMask))) |
											adpllPtr->adpllLowPowerBypassVal;
											
		/*	Wait till the PLL is in bypass	*/
		while(((HWREG(adpllPtr->idleStatusReg) & adpllPtr->adpllClkStatusMask) >> adpllPtr->adpllClkStatusShift) != 0x0);		
	}
}


/**
 * \brief   This API will configure the relock ramp setting of the PLL
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
static void setRelockRampCtrl(ADPLL *adpllPtr)
{
	HWREG(adpllPtr->adpllModeReg) = 
		(HWREG(adpllPtr->adpllModeReg) & (~adpllPtr->adpllRelockRampMask)) |
											adpllPtr->adpllRelockRampVal;
}


/**
 * \brief   This API will configure the different settings of the PLL
 *				- auto idle control
 *				- bypass clock source
 *				- Multiplier
 *				- Divider
 *				- sigma-delta divider
 *				- Low power bypass mode
 *				- relock ramp value
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 * \param   OPPSupported	OPP supported by the device
 *
 * \return  None.
 *
 **/
void configADPLL(ADPLL *adpllPtr, unsigned int OPPSupported)
{
	/*	Configure the PLL if it is not configured already	*/
	if(!adpllPtr->isPLLConfigured)
	{
		/*	Low power mode control setting	*/	
		setLPBypassMode(adpllPtr, CLK_LP_MODE_BYPASS);
		
		/*	Wait till the PLL is LOCKED	*/
		while(((HWREG(adpllPtr->idleStatusReg) & adpllPtr->adpllClkStatusMask) >> adpllPtr->adpllClkStatusShift) != 0x0);		

		/*	Configure the auto idle control	*/
		configADPLLAutoIdleCtrl(adpllPtr);
		
		/*	Configure the bypass clock source	*/
		setBypassClockSource(adpllPtr);

		/*	Configure multiplier, divider, sigma-delta divider	*/
		setClkMultDiv(adpllPtr, OPPSupported);

		/*	Relock ramp control setting	*/
		setRelockRampCtrl(adpllPtr);
		
		/*	Low power mode control setting	*/	
		setLPBypassMode(adpllPtr, CLK_LP_MODE_NORMAL);
		
		/*	Wait till the PLL is LOCKED	*/
		while(((HWREG(adpllPtr->idleStatusReg) & adpllPtr->adpllClkStatusMask) >> adpllPtr->adpllClkStatusShift) != 0x1);		

		adpllPtr->isPLLConfigured = true;
	}
}


/**
 * \brief   This API will enable the low power bypass mode of the PLL
 *
 * \param   *adpllPtr		Pointer to clock divider structure
 *
 * \return  None.
 *
 **/
//#if 0
void enableADPLLLowPowerMode(ADPLL *adpllPtr)
{
	/*	Low power mode control setting	*/	
	if((NULL != adpllPtr) && (NULL != adpllPtr->adpllModeReg))
	{
		setLPBypassMode(adpllPtr, CLK_LP_MODE_BYPASS);
	}
}
//#endif


/**
 * \brief   This API will configure the sleep transition mode of the clock domain
 *			and it increments the active clock count
 *
 * \param   *clkDomainptr	Pointer to the clock domain structure
 *
 * \return  None.
 *
 **/
void initClockDomain(ClockDomain *clkDomainptr)
{
	/*	Check if the clock domain is initialized	*/
	if((!(clkDomainptr->isCDInitialized)) && (NULL != clkDomainptr->clkStateTransCtrlReg))
	{
		HWREG(clkDomainptr->clkStateTransCtrlReg) = clkDomainptr->clkStateTransValue;
		clkDomainptr->isCDInitialized = true;
	}
	clkDomainptr->activeClockCount++;
}


/**
 * \brief   This API will configure the differnt settings of the clock
 *			-	if the clock is not leaf clock increment the active child count
 *			-	enable the parent clock
 *			-	initialize the clock domain
 *			-	enable module clock
 *			-	Configure the PLL
 *			-	Configure the clock divider
 *			-	Configure the multiplexer
 *
 * \param   *clkPtr	Pointer to the clock structure
 *
 * \return  None.
 *
 **/
static void enableClock(Clock *clkPtr)
{
	/*	if this is not leaf node increase the active child count	*/
	if(!clkPtr->isLeafClock)
	{
		if(clkPtr->activeChildCount > 0)
		{
			/*	This clock is already initialized	*/
			clkPtr->activeChildCount++;
			return;
		}
		else /* <= 0 */
		{
			/*	This clock is NOT initialized	*/
			clkPtr->activeChildCount++;
		}
	}

	/*	Enable the parent clock if any	*/
	if(NULL != clkPtr->parentClock)
	{
		enableClock(clkPtr->parentClock);
	}
	
	/*	Initialize the clock domain if this clock node is direatly associated to a clock domain	*/
	if(NULL != clkPtr->clkDomainPtr)
	{
		initClockDomain(clkPtr->clkDomainPtr);
	}
	
	/*	Configure PLL, if this clock node is a PLL	*/
	if(NULL != clkPtr->adpllPtr)
	{
		configADPLL(clkPtr->adpllPtr, clkPtr->OPPSupported);
	}
	
	/*	Configure clock divider	*/
	if(NULL != clkPtr->clkDivider)
	{
		configClkDiv(clkPtr->clkDivider, clkPtr->OPPSupported);
	}
	
	/*	Select inputs for Multiplexer	*/
	if(NULL != clkPtr->muxInputSelReg)
	{
		HWREG(clkPtr->muxInputSelReg) = 
				(HWREG(clkPtr->muxInputSelReg) & (~clkPtr->muxInputSelMask)) | 
													clkPtr->muxInputSelVal;
	}
	
}


/**
 * \brief   This API will enable the module
 *
 * \param   moduleId	module id of the module to be enabled
 *
 * \return  None.
 *
 **/
void enableModule(unsigned int moduleId)
{
	/*	with clock id get reference to corresponding module clock	*/
	ModuleClock *moduleClk = ModuleClockList[moduleId];
	
	/*	Enable the module by configuring the control register	*/
	if(NULL != moduleClk->clockCtrlReg)
	{
		HWREG(moduleClk->clockCtrlReg) |= moduleClk->enableValue;
	}

	/*	Wait till the module is fully functional	*/
    while(((moduleClk->idleStatusMask) & (~moduleClk->idleStatusMask))!=
          (HWREG(moduleClk->clockCtrlReg) & (moduleClk->idleStatusMask)));
}


/**
 * \brief   This API will enable the module
 *
 * \param   moduleId	module id of the module to be disabled
 *
 * \return  None.
 *
 **/
void disableModule(unsigned int moduleId)
{
	/*	with clock id get reference to corresponding module clock	*/
	ModuleClock *moduleClk = ModuleClockList[moduleId];
	
	/*	Disable the module by configuring the control register	*/
	if(NULL != moduleClk->clockCtrlReg)
	{
		HWREG(moduleClk->clockCtrlReg) &= moduleClk->disableValue;
	}
}


/**
 * \brief   This API will enable all the clocks required for a module. It enables
 *				-	Interface clock
 *				-	Functional clock
 *				-	Optional clock
 *				-	enable clock signal
 *
 * \param   moduleId	Module id of the module
 *
 * \return  None
 *
 **/
void enableModuleClock(unsigned int moduleId)
{
	unsigned int index = 0;
	
	/*	with clock id get reference to corresponding module clock	*/
	ModuleClock *moduleClk = ModuleClockList[moduleId];
	
	//enableModule(moduleId);
	
	/*	Initialize all Interface clocks		*/
	while(moduleClk->iClk[index])
	{
		enableClock(moduleClk->iClk[index++]);
	}
	
	/*	Initialize all Functional clocks	*/
	index = 0;
	while(moduleClk->fClk[index])
	{
		enableClock(moduleClk->fClk[index++]);
	}
	
	/*	Initialize all Optional clocks		*/
	index = 0;
	while(moduleClk->optClk[index])
	{
		enableClock(moduleClk->optClk[index++]);
	}	
	
	/*	Initialize all Clock enalbe	signals		*/
	index = 0;
	while(moduleClk->clkEnable[index])
	{
		enableClock(moduleClk->clkEnable[index++]);
	}
	
	enableModule(moduleId);
}


/**
 * \brief   This API tries to disable the clock domain. It will be disabled only
 *			if all the clocks under the clock domain are gated.
 *
 * \param   clkDomainptr	pointer to the clock domain
 *
 * \return  result	Indicates whether the clock domain is disabled or not. 
 *					Possible values are
 *						-	FAIL
 *						-	SUCCESS
 **/
result disableClockDomain(ClockDomain *clkDomainptr)
{
	if(NULL != clkDomainptr)
	{
		/*	If the active child count is zero, the clock domain is already disabled	*/
		if(0 == clkDomainptr->activeClockCount)
		{
			return SUCCESS;		
		}

		/*	decrement active child count	*/
		clkDomainptr->activeClockCount--;
			
		/*	if active child count is 0 go to sleep mode (update variable & register)	*/
		if(0 == clkDomainptr->activeClockCount)
		{
			clkDomainptr->clkStateTransValue = (CM_CLKSTCTRL_CLKTRCTRL_SW_SLEEP <<
												CM_CLKSTCTRL_CLKTRCTRL_SHIFT);
												
			HWREG(clkDomainptr->clkStateTransCtrlReg) |= clkDomainptr->clkStateTransValue;

			clkDomainptr->isCDInitialized = false;
			
			return SUCCESS;
		}
	}

	return FAIL;
}


/**
 * \brief   This API disables the clock. 
 *
 * \param   clkPtr	pointer to the clock
 *
 * \return  None
 **/
static void disableClock(Clock *clkPtr)
{
	/*	Disable clock only if the active child count is 0	*/
	if(0 == clkPtr->activeChildCount)
	{
		/*	disable clock domain	*/
		//disableClockDomain(clkPtr->clkDomainPtr);
				
		/*	Configure DPLL in low power mode	*/
		//enableADPLLLowPowerMode(clkPtr->adpllPtr);
		
		/*	Decrement the parent clock's active child count	*/
		if(NULL != clkPtr->parentClock)
		{
			clkPtr->parentClock->activeChildCount--;
			disableClock(clkPtr->parentClock);
		}
	}
}


/**
 * \brief   This API disables the module clock. The following actions are performed
 *			-	Check whether the module is idle 
				-	return with error status if not idle or wait if isBlockingCall is true
			-	If the module is idle, disable the module
			-	Check whether the module is disabled
				-	return with error status if not disabled or wait if isBlockingCall is true
			-	If the module is disabled, gate (disable) the clocks
			-	Check whether all the clocks are gated
 *
 * \param   moduleId		Module id of the module
 * \param   isBlockingCall	Variable indicating whether this is a blocking call or not
 *
 * \return  result	Indicates whether the module clock is disabled or not. 
 *					Possible values are
 *						-	MODULE_NOT_DISABLED
 *						-	MODULE_NOT_IDLE
 *						-	MODULE_AND_CLOCK_DISABLED
 *						-	MODULE_AND_CLOCK_NOT_DISABLED
 **/
unsigned int disableModuleClock(unsigned int moduleId, tBoolean isBlockingCall)
{
	unsigned int index = 0;
	
	/*	with clock id get reference to corresponding module clock	*/
	ModuleClock *moduleClk = ModuleClockList[moduleId];
	
	/*	Check module idle status	*/
	/*while(MODULE_IDLE != getModuleState(moduleId))
	{
		if(!isBlockingCall)
		{
			return MODULE_NOT_IDLE;
		}
	}*/
	
	/*	Disable Module	*/
	disableModule(moduleId);
	//asm("	DSB");
	/*	Check module disabled status	*/
	while(MODULE_DISABLED != getModuleState(moduleId))
	{
		if(!isBlockingCall)
		{
			return MODULE_NOT_DISABLED;
		}
	}
	
	/*	Disable clock - clock domain	*/
	/*	disable all Interface clocks		*/
	index = 0;
	while(moduleClk->iClk[index])
	{
		disableClock(moduleClk->iClk[index++]);
	}
	
	/*	disable all Functional clocks	*/
	index = 0;
	while(moduleClk->fClk[index])
	{
		disableClock(moduleClk->fClk[index++]);
	}
	
	/*	disable all Optional clocks		*/
	index = 0;
	while(moduleClk->optClk[index])
	{
		disableClock(moduleClk->optClk[index++]);
	}	
	
	/*	disable all Clock enable signals		*/
	index = 0;
	while(moduleClk->clkEnable[index])
	{
		disableClock(moduleClk->clkEnable[index++]);
	}
	
	return	MODULE_AND_CLOCK_DISABLED;
}


/**
 * \brief   This API gets the state of the module.
 *
 * \param   moduleId	Module id of the module
 *
 * \return  status	Indicates the status of the module
 *						- Module functional
 *						- Module in-transition
 *						- Module is idle
 *						- Module disabled
 *
 **/
unsigned int getModuleState(unsigned int moduleId)
{
	ModuleClock *moduleClk = ModuleClockList[moduleId];
	
	return ((HWREG(moduleClk->moduleStatusReg) & 
				moduleClk->idleStatusMask) >> 
				moduleClk->idleStatusShift);		
}


/**
 * \brief   This API gets the clock state of the Gclock
 *
 * \param   clk		Pointer to clock instance
 *
 * \return  status	Indicates the state of Gclock
 *
 **/
int getGclockGateState(Clock *clkPtr)
{
	if(NULL != clkPtr->clkGateStatusReg)
	{
		return ((HWREG(clkPtr->clkGateStatusReg) & 
				clkPtr->clockGateStatusMask) >> clkPtr->clockGateStatusShift);	
	}
	else
	{
		return CLK_INVALID_GCLK;
	}
}


/**
 * \brief   This API gets the idle status of the PLL
 *
 * \param   adpllPtr	Pointer to PLL instance
 *
 * \return  status	Indicates the idle status of the PLL
 *
 **/
unsigned int getADPLLIdleStatus(ADPLL *adpllPtr)
{
	if(NULL != (adpllPtr->idleStatusReg))
	{
		return ((HWREG(adpllPtr->idleStatusReg) & 
				adpllPtr->adpllClkStatusMask) >> adpllPtr->adpllClkStatusShift);
	}
	else
	{
		return ADPLL_INVALID;
	}
}


/**
 * \brief   This API gets the clock divider gate status
 *
 * \param   clkPtr	Pointer to clock instance
 *
 * \return  status	Indicates the clock divider gate status
 *
 **/
unsigned int getDividerClkGateStatus(Clock *clkPtr)
{
	if(NULL != clkPtr->clkDivider->dividerConfigReg)
	{
		return ((HWREG(clkPtr->clkDivider->dividerConfigReg) & 
		clkPtr->clkDivider->clkoutGateStatusMask) >> 
			clkPtr->clkDivider->clkoutGateStatusShift);			
	}
	else
	{
		return CLK_INVALID_DIVIDER;
	}
}


/**
 * \brief   This API gets number of active child count under this clock
 *
 * \param   clkPtr	Pointer to clock instance
 *
 * \return  Count	Active child count
 *
 **/
//static unsigned int getActiveChildCount(Clock *clk)
//{
	//return	clk->activeChildCount;
//}


/**
 * \brief   This API gets number of active child count under this clock domain
 *
 * \param   clkPtr	Pointer to clock domain instance
 *
 * \return  Count	Active clock count
 *
 **/
//static unsigned int getActiveClockCount(ClockDomain *clkDm)
//{
	//return clkDm->activeClockCount;
//}


/**
 * \brief   This API disables all the modules in the device
 *
 * \param   moduleDisableList[]	List of modules to be disabled
 *
 * \return  result	result of module disable. Possible values are
 *						-	SUCCESS
 *						-	FAIL
 *
 **/
result deviceClockDisable(unsigned int moduleDisableList[], unsigned noOfElements)
{
	unsigned int index = 0;
	result status = SUCCESS;
	
	for(index = 0; index < noOfElements; index++)
	{
		if(MODULE_AND_CLOCK_DISABLED == disableModuleClock(moduleDisableList[index], true))
		{
			status &= SUCCESS;
		}
		else
		{
			status &= FAIL;
		}
	}
	return status;
}

/**
 * \brief   This API disables selected modules from the list
 *
 * \param   moduleDisableList[] List of modules to be disabled
 * \param   noOfElements        No of entries in list
 *
 * \return  result    result of module disable. Possible values are
 *                     - SUCCESS
 *                     - FAIL
 *
 **/
result disableSelModuleClock(tMapModule moduleDisableList[],
                             unsigned noOfElements)
{
    unsigned int index = 0;
    result status = SUCCESS;

    for(index = 0; index < noOfElements; index++)
    {
        if((true == moduleDisableList[index].select) &&
           (MODULE_AND_CLOCK_DISABLED !=
                    disableModuleClock(moduleDisableList[index].module, true)))
        {
            status = FAIL;
        }
    }

    return status;
}

/**
 * \brief   This API gets the status of the clock domain
 *
 * \param   clkDomainId		Id of the clock domain
 *
 * \return  result	State of the clock domain gate. Possible values are
 *						-	SUCCESS
 *						-	FAIL
 *
 **/
result clkdomainGateStatus(unsigned int clkDomainId)
{
	ClockDomain *clkDomainPtr = clockDomainList[clkDomainId];
	
	if(0 == (HWREG(clkDomainPtr->clkStateTransCtrlReg) & clkDomainPtr->clkGateStatusMask))
	{
		return SUCCESS;
	}
	
	return FAIL;	
}


/**
 * \brief   This API will check whether all the clocks of the given 
 *			clock domain list are gated
 *
 * \param   clockDomainStatusList - List of clock domains to be checked
 *
 * \return  result	result of clock gate status. Possible values are
 *						-	SUCCESS
 *						-	FAIL
 **/
result deviceClockGateStatus(unsigned int clockDomainStatusList[], unsigned noOfElements)
{
	unsigned int index = 0;
	result status = SUCCESS;
	
	for(index = 0; index < noOfElements; index++)
	{
		if(CLK_DOMAIN_CLOCK_GATED == clkdomainGateStatus(clockDomainStatusList[index]))
		{
			status &= SUCCESS;
		}
		else
		{
			status &= FAIL;
		}
	}
	
	return status;
}


/**
 * \brief   This API enables all the modules in the device
 *
 * \param   enableList[]	List of modules to be enabled
 *
 * \return  None
 **/
void deviceClockEnable(unsigned int enableList[], unsigned noOfElements)
{
	unsigned int index = 0;
	
	for(index = 0; index < noOfElements; index++)
	{
		enableModuleClock(enableList[index]);
	}
}

/**
 * \brief   This API enables selected modules from the list
 *
 * \param   enableList[]    List of modules to be enabled
 * \param   noOfElements    No of entries in list
 *
 * \return  None
 *
 * Note: List is traversed in reverse order
 *
 **/
void enableSelModuleClock(tMapModule enableList[], unsigned int noOfElements)
{
    unsigned int index = 0;

    for(index = 0; index < noOfElements; index++)
    {
        if(true == enableList[noOfElements - index -1].select)
        {
            enableModuleClock(enableList[noOfElements - index - 1].module);
        }
    }
}
