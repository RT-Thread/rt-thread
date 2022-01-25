/**************************************************************************//**
 * @file     system_fm33lc0xx.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File for
 *           Device FM33LC0XX
 * @version  V2.00
 * @date     15. March 2021
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#include "system_fm33lc0xx.h"
/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies             */

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit()    */
uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
static uint32_t SystemPLLClockUpdate(void)
{
    uint32_t clock = 0;
    
    // 时钟源
    switch ((RCC->PLLCR >> 1) & 0x1)
    {
        case 0:
            switch ((RCC->RCHFCR >> 16) & 0xf)
            {
                case 1: // 16M
                    clock = 16000000;
                    break;
                
                case 2: // 24M
                    clock = 24000000;
                    break;
                
                case 0: // 8M
                default:
                    clock = 8000000;
                    break;
            }
            break;
        
        case 1:
            clock = XTHF_VALUE;
            break;
    }
    
    // 分频
    switch ((RCC->PLLCR >> 0x4) & 0x7)
    {
        case 0: // 不分频
            clock /= 1;
            break;
        
        case 1: // 2分频
            clock /= 2; 
            break;
        
        case 2: // 4分频
            clock /= 4;
            break;
        
        case 3: // 8分频
            clock /= 8;
            break;
        
        case 4: // 12分频
            clock /= 12;
            break;
        
        case 5: // 16分频
            clock /= 16;
            break;
        
        case 6: // 24分频
            clock /= 24;
            break;
        
        case 7: // 32分频
            clock /= 32;
            break;
    }
    
    // 倍频比
    clock = clock * (((RCC->PLLCR >> 16) & 0x7f) + 1);
    
    // 输出选择
    if ((RCC->PLLCR >> 3) & 0x1)
    {
        clock *= 2;
    }
        
    return clock;
}
 
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
    switch ((RCC->SYSCLKCR >> 0) & 0x7)
    {        
        case 1: // XTHF
            SystemCoreClock = XTHF_VALUE;
            break;
        
        case 2: // PLL
            SystemCoreClock = SystemPLLClockUpdate();
            break;
        
        case 4: // RCMF
            switch ((RCC->RCMFCR >> 16) & 0x3)
            {
                case 0: // 不分频
                    SystemCoreClock = 4000000;
                    break;
                
                case 1: // 4分频
                    SystemCoreClock = 1000000;
                    break;
                
                case 2: // 8分频
                    SystemCoreClock = 500000;
                    break;
                
                case 3: // 16分频
                    SystemCoreClock = 250000;
                    break;
            }
            break;
        
        case 5: // LSCLK
        case 6: // LPOSC
            SystemCoreClock = 32768;
            break;
        
        case 7: // USBBCK
            switch ((RCC->SYSCLKCR >> 3) & 0x1)
            {
                case 0: // USBBCK 48M
                    SystemCoreClock = 48000000;
                    break;
                
                case 1: // USBBCK 120M 2分频
                    SystemCoreClock = 60000000;
                    break;
            }
            break;
        
        default:
            switch ((RCC->RCHFCR >> 16) & 0xf)
            {
                case 1: // 16M
                    SystemCoreClock = 16000000;
                    break;
                
                case 2: // 24M
                    SystemCoreClock = 24000000;
                    break;
                
                case 0: // 8M
                default:
                    SystemCoreClock = 8000000;
                    break;
            }
            break;
    }
}

/**
  * @brief	NVIC_Init config NVIC
  *
  * @param 	NVIC_configStruct configParams
  *
  * @param 	IRQn Interrupt number
  *
  * @retval	None
  */
void NVIC_Init(NVIC_ConfigTypeDef  *NVIC_configStruct,IRQn_Type IRQn)
{
    /* Params Check */
    if(NVIC_configStruct->preemptPriority>3)
    {
        NVIC_configStruct->preemptPriority = 3;
    }
    
	NVIC_DisableIRQ(IRQn);
	NVIC_SetPriority(IRQn,NVIC_configStruct->preemptPriority);
	NVIC_EnableIRQ(IRQn);
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
    uint32_t temp;
    
    /*  */
    RCC->PLLCR = (uint32_t)0x00000000U;
    RCC->SYSCLKCR = (uint32_t)0x0A000000U;
     /* PAD RCC*/
    RCC->PCLKCR1 |=  (0x1U << 7U);
    #ifdef USE_LSCLK_CLOCK_SRC_XTLF           
        GPIOD->FCR |= 0x3C0000; 
        /* XTLF*/
        RCC->XTLFCR  = (uint32_t)(0x00000000U);
        /* XTLF*/
        RCC->XTLFCR  |= (uint32_t)(0x00000005U<<8);
        for(temp = 2000;temp>0;temp--);
        /* LSCLKXTLF*/
        RCC->LSCLKSEL = 0xAA;
        /* LSCXTLF*/
        RCC->SYSCLKCR |= 0x8000000U;
    #else
        RCC->SYSCLKCR &= 0x7FFFFFFU;
        RCC->LSCLKSEL = 0x55;
    #endif
    /*PDR*/
    RMU->PDRCR |=0x01;
    /*BOR*/
    RMU->BORCR &=0xFE;
    
    /* DEBUG IWDT WWDT */
    DBG->CR =0x03;
    
    RCC->RCHFTR = RCHF24M_TRIM;
    RCC->RCMFTR = RCMF4M_TRIM;
    RCC->LPOSCTR = LPOSC_TRIM;
    
    GPIOD->PUEN |= 0x3 << 7;
    
    /* DMA Flash Channel: Flash->RAM */
    RCC->PCLKCR2 |= 0x1 << 4;
    DMA->CH7CR |= 0x1 << 10;
    RCC->PCLKCR2 &= ~(0x1 << 4);
} 



