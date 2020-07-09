
/******************************************************************************
* @brief providing APIs for configuring PMC. 
*
*******************************************************************************
*
* provide APIs for configuring PMC
******************************************************************************/
#include "common.h"
#include "pmc.h"

/******************************************************************************
* Constants
******************************************************************************/
/******************************************************************************
* Macros
******************************************************************************/
/******************************************************************************
* Types
******************************************************************************/
/******************************************************************************
* Global variables
******************************************************************************/
/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* PMC api list.
*
*//*! @addtogroup pmc_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief  configure PMC with given parameters.
* 
* @param[in]   pPMC_Config       PMC configuration structure.
* @param[in]   pPMC             pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_DeInit.
*
*****************************************************************************/
void PMC_Init(PMC_Type *pPMC, PMC_ConfigType *pPMC_Config)
{
    pPMC->SPMSC1 = pPMC_Config->sCtrlstatus.byte;
    pPMC->SPMSC2 = pPMC_Config->sDetectVoltSelect.byte;         
}


/*****************************************************************************//*!
*
* @brief  config the pmc register to the default mode.
* 
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see PMC_Init.
*
*****************************************************************************/
void PMC_DeInit(PMC_Type *pPMC)
{
    pPMC->SPMSC1 = 0x1C;
    pPMC->SPMSC2 = 0;         
}


/*****************************************************************************//*!
*
* @brief  config the pmc mode among run, wait and stop modes.
* 
* @param[in]  u8PmcMode         PMC mode select.
* @param[in]  pPMC              pointer to the PMC module.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void PMC_SetMode(PMC_Type *pPMC,uint8_t u8PmcMode)
{
    switch(u8PmcMode & 0x3) 
    {
        case PmcModeRun:    
            break;
        case PmcModeWait:
            wait();
            break;
        case PmcModeStop4:
            /* enable LVD in stop mode */
            pPMC->SPMSC1 |= (PMC_SPMSC1_LVDE_MASK | PMC_SPMSC1_LVDSE_MASK);	
            stop();   
            break;
        case PmcModeStop3: 
            /* disable LVD in stop mode */
            pPMC->SPMSC1 &= ~(PMC_SPMSC1_LVDE_MASK | PMC_SPMSC1_LVDRE_MASK | PMC_SPMSC1_LVDSE_MASK);	
            stop();  
            break;
        default: 
            break;
    }
 
}

/*! @} End of pmc_api_list                                                    */

