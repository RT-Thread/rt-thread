/***********************************************************************
 * Filename    : HAL_IWDT.c
 * Description : HAL IWDT driver source file
 * Author(s)   : CWT  
 * version     : V1.0
 * Modify date : 2020-04-17  
 ***********************************************************************/
#include  "ACM32Fxx_HAL.h" 


HAL_StatusTypeDef HAL_IWDT_Init(IWDT_HandleTypeDef * hidt)
{
    if (hidt == NULL)
    {
        return HAL_ERROR;
    }

    System_Module_Enable(EN_IWDT); 	    
    System_Delay(1);  

    System_Enable_Disable_RTC_Domain_Access(FUNC_ENABLE);  
    System_Enable_RC32K();      
    System_Enable_Disable_Reset(RESET_ENABLE_SOURCE_IWDT, FUNC_ENABLE);  
    /*Enable IWDT  */
    hidt->Instance->CMDR = IWDT_ENABLE_COMMAND;
    System_Delay(10);  	
    /*Enable Write  */
    hidt->Instance->CMDR = IWDT_WRITE_ENABLE_COMMAND;      
    System_Delay(10);          

    hidt->Instance->PR = hidt->Init.Prescaler;   
    hidt->Instance->RLR = hidt->Init.Reload;	
    hidt->Instance->WINR = hidt->Init.Window; 		
    hidt->Instance->WUTR = hidt->Init.Wakeup;    	
    System_Delay(1);    
    while(hidt->Instance->SR & (0x0F)){}; // wait for configuration done         

    if (hidt->Init.Reload > hidt->Init.Wakeup)	
    {
        /*Enable Wake up  */
        hidt->Instance->CMDR = IWDT_WAKEUP_ENABLE_COMMAND;  
    }

    hidt->Instance->CMDR = IWDT_RELOAD_COMMAND;
    System_Delay(1);	
    while(hidt->Instance->SR & (1 << 4)){};      

    return HAL_OK;  

}

HAL_StatusTypeDef HAL_IWDT_Kick_Watchdog_Wait_For_Done(IWDT_HandleTypeDef * hidt)  
{
    hidt->Instance->CMDR = IWDT_RELOAD_COMMAND;  
    System_Delay(1);   
    while(hidt->Instance->SR & (1 << 4)){};  //wait for kick watchdog done       

    return HAL_OK;  
}













