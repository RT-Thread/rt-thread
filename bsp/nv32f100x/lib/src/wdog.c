
/******************************************************************************
*
* @brief Provide common watchdog module routines. 
*
* @history:
* 	Jun. 25, 2013	modified the watch dog unlock sequence and disable sequence
******************************************************************************/
#include "common.h"
#include "wdog.h"
 
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

/******************************************************************************
* Local functions
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* define watchdog API list
*
*//*! @addtogroup wdog_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief Watchdog ETMer disable routine.
*        
* @param  none 
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see WDOG_Enable
*****************************************************************************/

void WDOG_Disable(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1       &= ~WDOG_CS1_EN_MASK;

	/* First unlock the watchdog so that we can write to registers */
    WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;
}


/*****************************************************************************//*!
*
* @brief Watchdog ETMer disable routine with update enabled.
*        
*   Disable watchdog but the watchdog can be enabled and updated later.
*
* @param  none 
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see WDOG_Enable
*****************************************************************************/

void WDOG_DisableWDOGEnableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1       &= ~WDOG_CS1_EN_MASK;
    u8Cs1       |= WDOG_CS1_UPDATE_MASK;

	/* First unlock the watchdog so that we can write to registers */
    //WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;
}

/*****************************************************************************//*!
*
* @brief Watchdog ETMer enable routine.
*        
* @param  none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @see  WDOG_Disable
*****************************************************************************/

void WDOG_Enable(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;
    
    u8Cs1       |= WDOG_CS1_EN_MASK;

	/* First unlock the watchdog so that we can write to registers */
    WDOG_Unlock();
    WDOG->CS1    = u8Cs1;
}


/*****************************************************************************//*!
*
* @brief initialize watchdog.
*        
* @param[in]   pConfig  poiner to watchdog configuration strcture.
*
* @return none
*
* @ Pass/ Fail criteria: none
* 
* @warning make sure that WDOG is not initialized after reset or WDOG update is enabled 
* after reset by calling WDOG_EnableUpdate / WDOG_DisableWDOGEnableUpdate.
*
* @see WDOG_EnableUpdate, WDOG_DisableWDOGEnableUpdate
*
*****************************************************************************/

void WDOG_Init(WDOG_ConfigPtr pConfig)
{
    uint8_t     u8Cs1;
    uint8_t     u8Cs2;
    uint16_t    u16Toval;
    uint16_t    u16Win;
    
    u8Cs1       = 0x80;                                   /* default CS1 register value */
    u8Cs2       = 0;
    u16Toval    = pConfig->u16ETMeOut;
    u16Win      = pConfig->u16WinETMe;
        
    if(pConfig->sBits.bDisable)
    {
        u8Cs1 &= ~WDOG_CS1_EN_MASK;
    }
    if(pConfig->sBits.bIntEnable)
    {
        u8Cs1 |= WDOG_CS1_INT_MASK;
    }
    if(pConfig->sBits.bStopEnable)
    {
        u8Cs1 |= WDOG_CS1_STOP_MASK;
    }
    if(pConfig->sBits.bDbgEnable)
    {
        u8Cs1 |= WDOG_CS1_DBG_MASK;
    }
    if(pConfig->sBits.bWaitEnable)
    {
        u8Cs1 |= WDOG_CS1_WAIT_MASK;
    }
    if(pConfig->sBits.bUpdateEnable)
    {
        u8Cs1 |= WDOG_CS1_UPDATE_MASK;
    }
    if(pConfig->sBits.bWinEnable)
    {
        u8Cs2 |= WDOG_CS2_WIN_MASK;
    }
    if(pConfig->sBits.bPrescaler)
    {
        u8Cs2 |= WDOG_CS2_PRES_MASK;
    }
    u8Cs2   |= (pConfig->sBits.bClkSrc & 0x03);
    
    /* write regisers */
    WDOG_Unlock();              /* unlock watchdog first */
    WDOG->CS2   = u8Cs2;

    WDOG->TOVAL8B.TOVALL  = u16Toval;
    WDOG->TOVAL8B.TOVALH  = u16Toval >> 8;
    
    WDOG->WIN8B.WINL  = u16Win;
    WDOG->WIN8B.WINH  = u16Win >> 8;
    
    WDOG->CS1   = u8Cs1;                            
}


/*****************************************************************************//*!
*
* @brief initialize watchdog to the default state.
*        
* @param   none 
*
* @return none
*
* @ Pass/ Fail criteria: none
* @warning make sure that WDOG update is enabled after reset by calling WDOG_EnableUpdate.
* or by calling WDOG_DisableWDOGEnableUpdate.
*
* @see WDOG_DisableWDOGEnableUpdate, WDOG_EnableUpdate
*
*****************************************************************************/

void WDOG_DeInit(void)
{
    WDOG_Unlock();
    
    WDOG->CS2    =  WDOG_CS2_DEFAULT_VALUE;
    WDOG->TOVAL  =  WDOG_TOVAL_DEFAULT_VALUE;
    WDOG->WIN    =  WDOG_WIN_DEFAULT_VALUE;    
    WDOG->CS1    =  WDOG_CS1_DEFAULT_VALUE;
}

/*****************************************************************************//*!
*
* @brief feed/refresh watchdog.
*        
* @param   none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

void WDOG_Feed(void)
{
    DisableInterrupts;
    WDOG->CNT = 0x02A6;
    WDOG->CNT = 0x80B4;
    EnableInterrupts;
}



/*****************************************************************************//*!
*
* @brief enable update of WDOG. 
*        
* @param  none
*
* @return none
*
* @ Pass/ Fail criteria: none
* @warning  this must be the last step of writing control bits sequence.
*****************************************************************************/

void WDOG_EnableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1 |= WDOG_CS1_UPDATE_MASK;

	/* First unlock the watchdog so that we can write to registers */
    WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;  
}


/*****************************************************************************//*!
*
* @brief disable update of WDOG. 
*        
* @param  none 
*
* @return none
*
* @ Pass/ Fail criteria: none
* @warning  this must be the last step of writing control bits sequence.
*****************************************************************************/

void WDOG_DisableUpdate(void)
{
    uint8_t u8Cs1 =  WDOG->CS1;  
    uint8_t u8Cs2 =  WDOG->CS2;  
    uint16_t u16TOVAL =  WDOG->TOVAL;  
    uint16_t u16WIN =  WDOG->WIN;  

    u8Cs1 &= ~WDOG_CS1_UPDATE_MASK;

	/* First unlock the watchdog so that we can write to registers */
    WDOG_Unlock(); 
    WDOG->CS2    =  u8Cs2;
    WDOG->TOVAL  =  u16TOVAL;
    WDOG->WIN    =  u16WIN;
    WDOG->CS1    =  u8Cs1;  
    
}


/********************************************************************/

/*! @} End of wdog_api_list                                                    					*/




