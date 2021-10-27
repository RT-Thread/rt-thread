/*
  ******************************************************************************
  * @file    HAL_EFlash.c
  * @version V1.0.0
  * @date    2020
  * @brief   EFlash HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the internal FLASH memory:
  *           @ Program operations functions
  *           @ Erase   operations functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_EFlash_Init
* Description : Configure eflash parameter as system clock 
* Input       : system clock frequency 
* Output      : None
* Author      : Chris_Kyle                      
**********************************************************************************/
void HAL_EFlash_Init(uint32_t fu32_freq)
{
    HAL_EFlash_Init_Para(fu32_freq);     
} 

#if (__ACCELERATE_EH_PRESENT == 0)    
/*********************************************************************************
* Function    : HAL_EFlash_Erase_Page
* Description : Erase a Page, TERASE has been configured in System_Clock_Init()
* Input       : 
* Output      : false: FAIL
                true:  SUCCESS
* Author      : Chris_Kyle                         
**********************************************************************************/
bool HAL_EFlash_ErasePage(uint32_t fu32_Addr)
{
    EFC->CTRL |= EFC_CTRL_PAGE_ERASE_MODE;
    
    EFC->SEC = 0x55AAAA55;

    *((volatile uint32_t *)fu32_Addr) = 0;
    
    while (!(EFC->STATUS & EFC_STATUS_EFLASH_RDY));
    
    EFC->CTRL &= ~EFC_CTRL_PAGE_ERASE_MODE;

    return true;
}

/*********************************************************************************
* Function    : HAL_EFlash_Programe
* Description : Program a word, TPROG has been configured in System_Clock_Init()
* Input       : 
* Output      : false: FAIL
                true:  SUCCESS
* Author      : Chris_Kyle                         
**********************************************************************************/
bool HAL_EFlash_Program_Word(uint32_t fu32_Addr, uint32_t fu32_Data)
{
    if (fu32_Addr % 4)
    {
        return false; 
    }

    EFC->CTRL |= EFC_CTRL_PROGRAM_MODE;

    EFC->SEC = 0x55AAAA55;

    *((volatile uint32_t *)fu32_Addr) = fu32_Data;

    while (!(EFC->STATUS & EFC_STATUS_EFLASH_RDY));

    EFC->CTRL &= ~EFC_CTRL_PROGRAM_MODE;
    
    return true;
}
#else
/*********************************************************************************
* Function    : HAL_EFlash_Erase_Page
* Description : Erase a Page, TERASE has been configured in System_Clock_Init()
* Input       : 
* Output      : false: FAIL
                true:  SUCCESS
* Author      : Chris_Kyle                         
**********************************************************************************/
bool HAL_EFlash_ErasePage(uint32_t fu32_Addr)
{
    HAL_EFlash_ErasePage_EX(fu32_Addr);    

    return true;
}

/*********************************************************************************
* Function    : HAL_EFlash_Programe
* Description : Program a word, TPROG has been configured in System_Clock_Init()
* Input       : 
* Output      : false: FAIL
                true:  SUCCESS
* Author      : Chris_Kyle                         
**********************************************************************************/
bool HAL_EFlash_Program_Word(uint32_t fu32_Addr, uint32_t fu32_Data)
{
    if (fu32_Addr % 4)
    {
        return false; 
    }

    HAL_EFlash_Program_Word_EX(fu32_Addr, fu32_Data);     
    
    return true;
} 

#endif
