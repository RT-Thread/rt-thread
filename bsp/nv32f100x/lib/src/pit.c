/******************************************************************************
* @brief    Periodic Interrupt ETMer (PIT) source code. 
*
******************************************************************************/
#include "common.h"
#include "pit.h"

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
/*!
 * @brief global variable to store PIT callbacks.
 *
 */
PIT_CallbackType PIT_Callback[2] = {(PIT_CallbackType)NULL}; /*!< PIT initial callback */

/******************************************************************************
* Local functions
******************************************************************************/
void PIT_Ch0Isr(void);
void PIT_Ch1Isr(void);


/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* define PIT APIs
*
*//*! @addtogroup pit_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief initialize pit module.
*        
* @param[in]   u8Channel_No channel number
* @param[in]   pConfig point to configuration  
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_Init(uint8_t u8Channel_No, PIT_ConfigType *pConfig)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */
    
    if (pConfig->bFreeze)            
    {                                               
        PIT_SetDebugFreeze();            
    } 
    
    if (pConfig->bModuleDis == 0) 
    {                                              
        PIT_Enable();       /*!< enable pit module */                                                                                
    }  
    
    PIT_SetLoadVal(u8Channel_No, pConfig->u32LoadValue);  
    
    if (pConfig->bInterruptEn)            
    {                                   
        if (u8Channel_No)
        {        
             NVIC_EnableIRQ(PIT_CH1_IRQn);             
        }
        else
        {                  
            NVIC_EnableIRQ(PIT_CH0_IRQn);
        }
        PIT_ChannelEnableInt(u8Channel_No);
    }                   
    else                                     
    {                     
        NVIC_DisableIRQ(PIT_CH0_IRQn);       
    }

    if (pConfig->bChainMode)            
    {                                               
        PIT_ChannelEnableChain(u8Channel_No);            
    }
    
    if (pConfig->bETMerEn)            
    {                                               
        PIT_ChannelEnable(u8Channel_No);            
    }             

}


/*****************************************************************************//*!
*
* @brief initialize pit module.
*        
* @param[in]   u8Channel_No channel number
* @param[in]   u32loadvalue load value for pit register  
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_SetLoadVal(uint8_t u8Channel, uint32_t u32loadvalue)

{
    PIT->CHANNEL[u8Channel].LDVAL = u32loadvalue;   
}


/*****************************************************************************//*!
*
* @brief pit module set call back.
*        
* @param[in] u8Channel_No channel number.   
* @param[in] pfnCallback point to call back.   
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_SetCallback(uint8_t u8Channel_No, PIT_CallbackType pfnCallback)
{
  PIT_Callback[u8Channel_No] = pfnCallback;
}


/*****************************************************************************//*!
*
* @brief pit module de-initialize, reset pit register
*        
* @param none  
*
* @return none 
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_DeInit(void)
{
    NVIC_DisableIRQ(PIT_CH0_IRQn);
    NVIC_DisableIRQ(PIT_CH1_IRQn);    
    PIT_SetLoadVal(0,0);
    PIT_SetLoadVal(1,0);
    PIT_ChannelDisable(0);
    PIT_ChannelDisable(1);
    PIT_ChannelDisableInt(0);
    PIT_ChannelDisableInt(1);
    PIT_ChannelDisableChain(0);
    PIT_ChannelDisableChain(1);    
    PIT_ChannelClrFlags(0);
    PIT_ChannelClrFlags(1);    
    PIT_SetDebugOn();
    PIT_Disable();
    SIM->SCGC &= ~SIM_SCGC_PIT_MASK;
}
/*! @} End of pit_api_list                                                   */


/*****************************************************************************//*!
*
* @brief pit module channel 0 isr.
*        
* @param none
*
* @return none 
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_Ch0Isr(void) 
{   
   PIT_ChannelClrFlags(0);  
    
    if (PIT_Callback[0])
    {    
        PIT_Callback[0]();     
    }
}
    
/*****************************************************************************//*!
*
* @brief pit module channel 1 isr.
*        
* @param none
*
* @return none 
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_Ch1Isr(void) 
{   
    PIT_ChannelClrFlags(1);
    if (PIT_Callback[1])
    {    
        PIT_Callback[1]();     
    }
}    


