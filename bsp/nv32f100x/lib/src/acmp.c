
/******************************************************************************
*
* @brief providing APIs for configuring ACMP. 
*
*******************************************************************************
*
* provide APIs for configuring ACMP
******************************************************************************/
#include "common.h"
#include "acmp.h"
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/

ACMP_CallbackPtr ACMP_Callback[2] = {(ACMP_CallbackPtr)NULL};

/******************************************************************************
* Local functions
******************************************************************************/
/******************************************************************************
* Global functions
******************************************************************************/
void ACMP0_Isr(void);
void ACMP1_Isr(void);

/******************************************************************************
* ACMP api list.
*
*//*! @addtogroup acmp_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief initialize ACMP as per control field.
*        
* @param   pACMPx         pointer to an ACMP register base.
* @param   pConfig        control parameters.  
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see   ACMP_DeInit.  
*
*****************************************************************************/
void ACMP_Init(ACMP_Type *pACMPx, ACMP_ConfigType *pConfig) 
{
    if(ACMP0 == pACMPx)
    {    
        /* enable clock to ACMP */
        SIM->SCGC |= SIM_SCGC_ACMP0_MASK;
 
        /* enable ACMP interrupt */
        if(pConfig->sCtrlStatus.bits.bIntEn)
            NVIC_EnableIRQ(ACMP0_IRQn);
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_ACMP1_MASK;
        if(pConfig->sCtrlStatus.bits.bIntEn)
            NVIC_EnableIRQ(ACMP1_IRQn);            
    }
    /* neg and pos pin are not equal */
    pACMPx->C0 = pConfig->sPinSelect.byte;
    ACMP_ConfigDAC(pACMPx, &pConfig->sDacSet );
    //pACMPx->C1 = pConfig->sDacSet.byte;
    pACMPx->C2 = pConfig->sPinEnable.byte;
    pACMPx->CS = pConfig->sCtrlStatus.byte;
}


/*****************************************************************************//*!
*
* @brief write ACMP register bits.
*        
* @param   pACMPx      pointer to an ACMP register base.
* @param   pDACConfig   pointer to an ACMP DAC control structure.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void ACMP_ConfigDAC(ACMP_Type *pACMPx, ACMP_DACType *pDACConfig) 
{
    pACMPx->C1 = pDACConfig->byte;  
}

/*****************************************************************************//*!
*
* @brief deinit ACMP module.
*        
* @param   pACMPx      pointer to an ACMP register base.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see   ACMP_Init.  
*
*****************************************************************************/
void ACMP_DeInit(ACMP_Type *pACMPx) 
{
    if(ACMP0 == pACMPx)
    {    
        if(pACMPx->CS & ACMP_CS_ACIE_MASK)
            NVIC_DisableIRQ(ACMP0_IRQn);
    }
    else
    {
        if(pACMPx->CS & ACMP_CS_ACIE_MASK)
            NVIC_DisableIRQ(ACMP1_IRQn);            
    }
    
    pACMPx->CS = 0;
    pACMPx->C0 = 0;
    pACMPx->C1 = 0;
    pACMPx->C2 = 0;
    
    if(ACMP0 == pACMPx)
    {    
        SIM->SCGC &= ~SIM_SCGC_ACMP0_MASK;
    }
    else
    {
        SIM->SCGC &= ~SIM_SCGC_ACMP1_MASK;           
    } 
}

/*****************************************************************************//*!
*
* @brief  set up ACMP callback routines to be called by interrupt service routine.
*        
* @param  pACMPx       pointer to an ACMP register base. 
* @param   pfnCallback  callback routine.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void ACMP_SetCallback(ACMP_Type *pACMPx, ACMP_CallbackPtr pfnCallback)
{
    if(ACMP0 == pACMPx)
    {
        ACMP_Callback[0] = pfnCallback;
    }
    else
    {
        ACMP_Callback[1] = pfnCallback;
    }
}

/*! @} End of acmp_api_list                                                  */


/*****************************************************************************//*!
*
* @brief  ACMP0 interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void ACMP0_Isr(void)
{

    if(ACMP_Callback[0])
    {
        ACMP_Callback[0]();             /* call callback routine */
    }
}

/*****************************************************************************//*!
*
* @brief  ACMP1 interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void ACMP1_Isr(void)
{

    if(ACMP_Callback[1])
    {
        ACMP_Callback[1]();             /* call callback routine */
    }
}


