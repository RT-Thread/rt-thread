/*******************************************************************************
* File Name: MCWDT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the MCWDT
*  component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MCWDT_PDL.h"


/** MCWDT_initVar indicates whether the MCWDT  component
*  has been initialized. The variable is initialized to 0 and set to 1 the first
*  time MCWDT_Start() is called.
*  This allows the component to restart without reinitialization after the first 
*  call to the MCWDT_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  MCWDT_Init() function can be called before the 
*  MCWDT_Start() or MCWDT_Enable() function.
*/
uint8 MCWDT_initVar = 0u;

/** The instance-specific configuration structure. This should be used in the 
*  associated MCWDT_Init() function.
*/ 
const cy_stc_mcwdt_config_t MCWDT_config =
{
    .c0Match     = MCWDT_C0_MATCH,
    .c1Match     = MCWDT_C1_MATCH,
    .c0Mode      = MCWDT_C0_MODE,
    .c1Mode      = MCWDT_C1_MODE,
    .c2ToggleBit = MCWDT_C2_PERIOD,
    .c2Mode      = MCWDT_C2_MODE,
    .c0ClearOnMatch = (bool)MCWDT_C0_CLEAR_ON_MATCH,
    .c1ClearOnMatch = (bool)MCWDT_C1_CLEAR_ON_MATCH,
    .c0c1Cascade = (bool)MCWDT_CASCADE_C0C1,
    .c1c2Cascade = (bool)MCWDT_CASCADE_C1C2
};


/*******************************************************************************
* Function Name: MCWDT_Start
****************************************************************************//**
*
*  Sets the initVar variable, calls the Init() function, unmasks the 
*  corresponding counter interrupts and then calls the Enable() function 
*  to enable the counters.
*
* \globalvars
*  \ref MCWDT_initVar
*
*  \note
*  When this API is called, the counter starts counting after two lf_clk cycles 
*  pass. It is the user's responsibility to check whether the selected counters
*  were enabled immediately after the function call. This can be done by the 
*  MCWDT_GetEnabledStatus() API.
*
*******************************************************************************/
void MCWDT_Start(void)
{
    if (0u == MCWDT_initVar)
    {
        (void)MCWDT_Init(&MCWDT_config);
        MCWDT_initVar = 1u; /* Component was initialized */
    }

	/* Set interrupt masks for the counters */
	MCWDT_SetInterruptMask(MCWDT_CTRS_INT_MASK);

	/* Enable the counters that are enabled in the customizer */
    MCWDT_Enable(MCWDT_ENABLED_CTRS_MASK, 0u);
}


/*******************************************************************************
* Function Name: MCWDT_Stop
****************************************************************************//**
*
*  Calls the Disable() function to disable all counters.
*
*******************************************************************************/
void MCWDT_Stop(void)
{
    MCWDT_Disable(CY_MCWDT_CTR_Msk, MCWDT_TWO_LF_CLK_CYCLES_DELAY);
    MCWDT_DeInit();
}


/* [] END OF FILE */
