/***********************************************************************
 * Filename    : HAL_WDT.c
 * Description : HAL WDT driver source file
 * Author(s)   : CWT  
 * version     : V1.0
 * Modify date : 2020-04-17  
 ***********************************************************************/
#include  "ACM32Fxx_HAL.h"

/************************************************************************
 * function   : HAL_WDT_Feed
 * Description: WDT feed. 
 * input : 
 *         none 
 * return: none
 ************************************************************************/
void HAL_WDT_Feed(WDT_HandleTypeDef* hwdt)
{
    hwdt->Instance->FEED = 0xAA55A55A; 
}
/************************************************************************
 * function   : HAL_WDT_IRQHandler
 * Description: WDT interrupt service routine. 
 * input : 
 *         none 
 * return: none
 ************************************************************************/
void HAL_WDT_IRQHandler(WDT_HandleTypeDef* hwdt)
{
    volatile uint32_t wdt_ris = 0;
    wdt_ris = hwdt->Instance->RIS;
    HAL_WDT_Feed(hwdt);
    NVIC_ClearPendingIRQ(WDT_IRQn);  
}

/************************************************************************
 * function   : HAL_WDT_Init
 * Description: WDT initiation. 
 * input : 
 *         pinit initiation parameters 
 * return: none
 ************************************************************************/
void HAL_WDT_Init(WDT_HandleTypeDef* hwdt)
{
    System_Module_Enable(EN_WDT);    
    System_Delay(1);
    System_Enable_Disable_RTC_Domain_Access(FUNC_ENABLE);  
    System_Enable_Disable_Reset(RESET_ENABLE_SOURCE_WDT, FUNC_ENABLE);  
    
    hwdt->Instance->LOAD = hwdt->Init.WDTLoad;
    hwdt->Instance->CTRL = (hwdt->Instance->CTRL & ~0x47) | (hwdt->Init.WDTDivisor) | (hwdt->Init.WDTMode << 6);	 

    if (WDT_MODE_INT == hwdt->Init.WDTMode)
    {
        hwdt->Instance->INTCLRTIME = hwdt->Init.WDTINTCLRTIME; 
        HAL_WDT_Int_Enable(hwdt);   
    }
}

/************************************************************************
 * function   : HAL_WDT_Start
 * Description: WDT start
 * input : none
 *         
 * return: none
 ************************************************************************/
void HAL_WDT_Start(WDT_HandleTypeDef* hwdt)
{
    hwdt->Instance->CTRL |= WDT_ENABLE;
}

/************************************************************************
 * function   : WDT_Stop
 * Description: WDT stop
 * input : none
 *         
 * return: none
 ************************************************************************/
void HAL_WDT_Stop(WDT_HandleTypeDef* hwdt)
{
    hwdt->Instance->CTRL &= WDT_DISABLE;
}

/************************************************************************
 * function   : WDT_Int_Enable
 * Description: WDT int enable
 * input : none
 *         
 * return: none
 ************************************************************************/
void HAL_WDT_Int_Enable(WDT_HandleTypeDef* hwdt)
{
    hwdt->Instance->CTRL |= WDT_INT_ENABLE; 
    NVIC_ClearPendingIRQ(WDT_IRQn);  
    NVIC_EnableIRQ(WDT_IRQn);
}

/************************************************************************
 * function   : WDT_Int_Disable
 * Description: WDT int disable
 * input : none
 *         
 * return: none
 ************************************************************************/
void HAL_WDT_Int_Disable(WDT_HandleTypeDef* hwdt)
{
    hwdt->Instance->CTRL &= WDT_INT_DISABLE;
}


