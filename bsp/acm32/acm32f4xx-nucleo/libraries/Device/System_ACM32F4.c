/*
  ******************************************************************************
  * @file    System_ACM32F4.c
  * @version V1.0.0
  * @date    2021 
  * @brief   System Source File, includes clock management, reset management 
  *          and IO configuration, ...   
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

uint32_t gu32_SystemClock;
uint32_t gu32_APBClock;        

/* System count in SysTick_Handler */
volatile uint32_t gu32_SystemCount;

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0U /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */
/******************************************************************************/

/*********************************************************************************
* Function    : HardFault_Handler
* Description : Hard Fault handle, while(1) loop, wait for debug 
* Input       : none 
* Output      : none   
* Author      : xwl                           
**********************************************************************************/  
//void HardFault_Handler(void)	//implemented in context_rvds.S
//{
//    while(1);   
//} 

/*********************************************************************************
* Function    : SysTick_Handler
* Description : System tick handler
* Input       : none 
* Output      : none 
* Author      : Chris_Kyle                         
**********************************************************************************/
//void SysTick_Handler(void)	//implemented in board.c
//{
//    gu32_SystemCount++;
//}

/*********************************************************************************
* Function    : System_SysTick_Init
* Description : System Tick Init. Period is 1 ms
* Input       : none 
* Output      : none 
* Author      : Chris_Kyle                         
**********************************************************************************/
//void System_SysTick_Init(void)	//implemented in board.c/rt_hw_board_init()
//{
//    gu32_SystemCount = 0;   
//    SysTick_Config(gu32_SystemClock / 1000);  //1ms/tick  
//}

/*********************************************************************************
* Function    : System_SysTick_Off
* Description : Turn off System Tick  
* Input       : none 
* Output      : none 
* Author      : xwl                         
**********************************************************************************/
//void System_SysTick_Off(void)  
//{
//    SysTick->CTRL = 0;   
//}
/*********************************************************************************
* Function    : System_Init
* Description : Initialize the system clock, accelerate function and system tick.   
* Input       : none 
* Output      : none 
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Init(void)
{
    SCU->RCR |= SCU_RCR_REMAP_EN;   // always remap enabled  
    System_Set_Buzzer_Divider(80, FUNC_DISABLE); // disable clock out   
    /* 3 bits for pre-emption priority, 0 bits for subpriority */ 
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_3);    

    /* Initialize the system clock */
    if (false == System_Clock_Init(DEFAULT_SYSTEM_CLOCK))
    {
        while(1);  
    }
    
#if (__ACCELERATE_PRESENT == 1)
    System_EnableIAccelerate();
#endif
    
#if (__ACCELERATE_EH_PRESENT == 1)   
    System_EnableDAccelerate();
#endif  

#ifdef HAL_SYSTICK_ENABLED  // To activate macro in ACM32Fxx_HAL.h      
    //System_SysTick_Init();
#endif
}

/*********************************************************************************
* Function    : System_Core_Config
* Description : configure FPU and vector table address  
* Input       : none  
* Output      : none   
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Core_Config(void)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    /* set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
#endif

    /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;    /* Vector Table Relocation in Internal SRAM */
#else
    SCB->VTOR = EFLASH_BASE | VECT_TAB_OFFSET;  /* Vector Table Relocation in Internal FLASH */
#endif
}


/*********************************************************************************
* Function    : System_Clock_Init
* Description : Clock init
* Input       : fu32_Clock: System core clock frequency, measured as Hz   
* Output      : 0: success, other value: fail reason  
* Author      : xwl                         
**********************************************************************************/
bool System_Clock_Init(uint32_t fu32_Clock)
{
    volatile uint32_t lu32_sysdiv, lu32_pclkdiv, lu32_timeout, lu32_pll_src, lu32_pclk_div_para, lu32_result;     
          
    SET_EFC_RD_WAIT(RD_WAIT_ENSURE_OK)    
    lu32_result = 0;  
    lu32_pll_src = PLL_SOURCE_FROM;   
       
    if(0 == (SCU->RCHCR & SCU_RCHCR_RCHRDY))  
    {
       SCU->RCHCR |=  SCU_RCHCR_RCH_EN;   
       while(0 == (SCU->RCHCR & SCU_RCHCR_RCHRDY));  // wait RCH ready         
    }
    SCU->CCR1 = 0;  // select RC64M as default  

    if (fu32_Clock <= 64000000)  
    {
        if ((SCU->RCHCR) & SCU_RCHCR_RCH_DIV)
        {
            SCU->RCHCR &= (~SCU_RCHCR_RCH_DIV);   
            while(0 == (SCU->RCHCR & SCU_RCHCR_RCHRDY));    
        }
        
        if (fu32_Clock == 32000000)
        {
            gu32_SystemClock = fu32_Clock;
            lu32_sysdiv = 2;  
            lu32_pclkdiv = 1;  // pclk = hclk 
        }
        else
        {
            gu32_SystemClock = 64000000;
            lu32_sysdiv = 1;  
            lu32_pclkdiv = 1;   
        }
              
        gu32_APBClock = gu32_SystemClock/lu32_pclkdiv;     
    }
    // select pll as system clock 
    else
    {
        if (PLLCLK_SRC_RC4M == lu32_pll_src)
        {
            SCU->RCHCR |= SCU_RCHCR_RCH_DIV;   
            while(!(SCU->RCHCR & SCU_RCHCR_RCHRDY));

            SCU->PLLCR |=  SCU_PLLCR_PLL_EN;
            SCU->PLLCR &= ~(SCU_PLLCR_PLL_SLEEP);
            while(!(SCU->PLLCR & SCU_PLLCR_PLL_FREE_RUN));

            switch(fu32_Clock)
            {
                case 180000000:  // 180M 
                {
                    SCU->PLLCR  = (SCU->PLLCR & ~(0xFFFF8)) | (33 << 3);
                    SCU->PLLCR |= SCU_PLLCR_PLL_UPDATE_EN;  
                    while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) ) );       

                    lu32_sysdiv = 1;  
                    lu32_pclkdiv = 2; // pclk = hclk/2 
                }break;

                case 120000000:  // 120M
                {
                    SCU->PLLCR  = (SCU->PLLCR & ~(0xFFFF8)) | (18U << 3);      
                    SCU->PLLCR |= SCU_PLLCR_PLL_UPDATE_EN;  
                    while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) ) );    

                    lu32_sysdiv = 1;  
                    lu32_pclkdiv = 2; // pclk = hclk/2
                }break;
                
                default: lu32_result = 1; break; 
            }
            gu32_SystemClock = fu32_Clock;  
            gu32_APBClock = gu32_SystemClock/lu32_pclkdiv;        
            SCU->CCR1 = SCU_CCR1_SYS_PLL;  // configure system clock as PLL clock     
        }
        else if (SCU_XTHCR_XTH_EN == lu32_pll_src)   
        {
            lu32_timeout = 0;  
        
            SCU->XTHCR = SCU_XTHCR_XTH_EN | SCU_XTHCR_READYTIME_32768;
            while (0 == (SCU->XTHCR & SCU_XTHCR_XTHRDY))
            {     
                if (lu32_timeout == SYSTEM_TIMEOUT)
                {
                    lu32_result = 2;  
                    break;     
                }  
                lu32_timeout++;    
            } 
            
            if  (0 == lu32_result)
            {
                SCU->PLLCR |=  SCU_PLLCR_PLL_EN;  
                SCU->PLLCR &= ~(SCU_PLLCR_PLL_SLEEP);   
                while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) ));     
            
                switch(fu32_Clock) 
                {
                    case 180000000:  // 180M 
                    {
                        SCU->PLLCR = (SCU->PLLCR &(~(0x1FFFFU << 3))) | (18U << 3) | (1U << 12) | (0U << 16);   
                        SCU->PLLCR = (SCU->PLLCR & (~(0x3U << 1)) ) | (3 << 1);   
                        SCU->PLLCR |= SCU_PLLCR_PLL_UPDATE_EN;   
                        while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) ) );     
                   
                        lu32_sysdiv = 1;  
                        lu32_pclkdiv = 2; // pclk = hclk/2  
                    }break;

                    case 120000000:  // 120M 
                    {
                        SCU->PLLCR = (SCU->PLLCR &(~(0x1FFFFU << 3))) | (18U << 3) | (2U << 12) | (0U << 16);   
                        SCU->PLLCR = (SCU->PLLCR & (~(0x3U << 1)) ) | (3 << 1); // select XTH  
                        SCU->PLLCR |= SCU_PLLCR_PLL_UPDATE_EN;   
                        while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) ) );     
                   
                        lu32_sysdiv = 1;  
                        lu32_pclkdiv = 2; // pclk = hclk/2  
                    }break;
               
                    default: lu32_result = 1; break;  
                }
            }
            gu32_SystemClock = fu32_Clock;  
            gu32_APBClock = gu32_SystemClock/lu32_pclkdiv;        
            SCU->CCR1 = SCU_CCR1_SYS_PLL;  // configure system clock as PLL clock   
        }  
        else
        {
            lu32_result = 3;    
        }
    }
    
    if (0 == lu32_result)
    {
        if (1 == lu32_pclkdiv)
        {
            lu32_pclk_div_para = 0;    
        }
        else if (2 == lu32_pclkdiv)
        {
            lu32_pclk_div_para = 4;    // pclk = hclk/2   
        } 
        else
        {
            lu32_pclk_div_para = 5;    // pclk = hclk/4       
        }
    }
    else
    {
        lu32_sysdiv = 1;   
        lu32_pclk_div_para = 0;  
    }
  
    SCU->CCR2 = (SCU->CCR2 & (~0x7FFU)) | (lu32_sysdiv-1) | (lu32_pclk_div_para << 8);   
    while((SCU->CCR2 & SCU_CCR2_DIVDONE) == 0x00);  // wait divide done   

    HAL_EFlash_Init(gu32_SystemClock);    
    
    return (lu32_result == 0);    
}

/*********************************************************************************
* Function    : System_Get_SystemClock
* Description : get AHB clock frequency   
* Input       : none 
* Output      : frequency, measured as Hz    
* Author      : Chris_Kyle                         
**********************************************************************************/
uint32_t System_Get_SystemClock(void)
{
    return gu32_SystemClock;
}

/*********************************************************************************
* Function    : System_Get_APBClock
* Description : get APB clock frequency   
* Input       : none 
* Output      : frequency, measured as Hz  
* Author      : Chris_Kyle                         
**********************************************************************************/
uint32_t System_Get_APBClock(void)
{
    return gu32_APBClock;
}

/*********************************************************************************
* Function    : System_Module_Reset
* Description : reset module 
* Input       : module id 
* Output      : none 
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Module_Reset(enum_RST_ID_t fe_ID_Index)
{
    if (fe_ID_Index > 31) 
    {
        SCU->IPRST2 &= ~(1 << (fe_ID_Index - 32));         
        System_Delay(5);
        SCU->IPRST2 |= 1 << (fe_ID_Index - 32);   
    }
    else 
    {
        SCU->IPRST1 &= ~(1 << fe_ID_Index);       
        System_Delay(5);  
        SCU->IPRST1 |= 1 << fe_ID_Index;       
    }
}

/*********************************************************************************
* Function    : System_Module_Enable
* Description : enable module clock  
* Input       : module id     
* Output      : none 
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Module_Enable(enum_Enable_ID_t fe_ID_Index)
{
    if (fe_ID_Index > 13) 
    {
        SCU->IPCKENR1 |= 1 << (fe_ID_Index - 14);
    }
    else 
    {
        SCU->IPCKENR2 |= 1 << fe_ID_Index;
    }
    
    System_Delay(2);   
}

/*********************************************************************************
* Function    : System_Module_Disable
* Description : disable module clock 
* Input       : module id  
* Output      : none 
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Module_Disable(enum_Enable_ID_t fe_ID_Index)
{
    if (fe_ID_Index > 13) 
    {
        SCU->IPCKENR1 &= ~(1 << (fe_ID_Index - 14));
    }
    else 
    {
        SCU->IPCKENR2 &= ~(1 << fe_ID_Index);
    }
}

/*********************************************************************************
* Function    : System_Delay
* Description : NOP delay
* Input       : count 
* Output      : none  
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Delay(volatile uint32_t fu32_Delay)
{
    while (fu32_Delay--);
}

/*********************************************************************************
* Function    : System_Delay_MS
* Description : ms delay. Use this Function must call System_SysTick_Init()
* Input       : delay period, measured as ms  
* Output      : none  
* Author      : Chris_Kyle                         
**********************************************************************************/
void System_Delay_MS(volatile uint32_t fu32_Delay)
{
    uint32_t lu32_SystemCountBackup;
    
    lu32_SystemCountBackup = gu32_SystemCount;
    
    while ( (gu32_SystemCount - lu32_SystemCountBackup) < fu32_Delay);  
}

/*********************************************************************************
* Function    : System_Enable_RC32K
* Description : Enable RC32K, make sure RTC Domain Access is allowed    
* Input       : none 
* Output      : none 
* Author      : CWT                         
**********************************************************************************/
void System_Enable_RC32K(void)
{
    PMU->ANACR |= (1 << 8); 
    while(0 == ((PMU->ANACR) & (1U << 9)));
}

/*********************************************************************************
* Function    : System_Disable_RC32K
* Description : Disable RC32K
* Input       : none  
* Output      : none 
* Author      : CWT                        
**********************************************************************************/
void System_Disable_RC32K(void)
{
    PMU->ANACR &= (~(1 << 8));
}

/*********************************************************************************
* Function    : System_Enable_XTAL
* Description : Enable XTAL, make sure RTC Domain Access is allowed 
* Input       : none 
* Output      : none  
* Author      : CWT                         
**********************************************************************************/
void System_Enable_XTAL(void)
{
    PMU->ANACR = (PMU->ANACR & ~RPMU_ANACR_XTLDRV) | (RPMU_ANACR_XTLDRV_1 | RPMU_ANACR_XTLDRV_0);
    PMU->ANACR |= RPMU_ANACR_XTLEN;
    while(!(PMU->ANACR & RPMU_ANACR_XTLRDY));
    PMU->CR1 |= RTC_CLOCK_XTL;
}

/*********************************************************************************
* Function    : System_Disable_XTAL
* Description : Disable XTAL
* Input       : none 
* Output      : none 
* Author      : CWT                       
**********************************************************************************/
void System_Disable_XTAL(void)
{
    PMU->ANACR &= (~(RPMU_ANACR_XTLEN));   
}

/*********************************************************************************
* Function    : System_Enable_Disable_RTC_Domain_Access
* Description : Enable or Disable  RTC Domain Access.
* Input       : enable or  disable  
* Output      : none   
* Author      : CWT                         
**********************************************************************************/
void System_Enable_Disable_RTC_Domain_Access(FUNC_DISABLE_ENABLE enable_disable)  
{
    if (FUNC_DISABLE == enable_disable)
    {
        SCU->STOPCFG &= (~SCU_STOPCFG_RTC_WE);
    }
    else
    {
        SCU->STOPCFG |= SCU_STOPCFG_RTC_WE;  
        System_Delay(1);     
        RTC->WP = 0xCA53CA53U;  
    }
}

/*********************************************************************************
* Function    : System_Enable_Disable_Reset
* Description : Enable or Disable  System Reset source.
* Input       : none 
* Output      : none 
* Author      : CWT                         
**********************************************************************************/
void System_Enable_Disable_Reset(RESET_ENABLE_SOURCE source, FUNC_DISABLE_ENABLE enable_disable)  
{
    switch(source)
    {
        /* reset source: from bit0 to bit3  */  
        case RESET_ENABLE_SOURCE_LVD:
        case RESET_ENABLE_SOURCE_WDT:
        case RESET_ENABLE_SOURCE_IWDT:
        case RESET_ENABLE_SOURCE_LOCKUP:   

        if (FUNC_DISABLE == enable_disable)
        {
            SCU->RCR &= (~(1U << source));  
        }
        else
        {
            SCU->RCR |= (1U << source);    
        }	
        break; 

        default: break;  
    }
}

/*********************************************************************************
* Function    : System_Reset_MCU
* Description : reset mcu  
* Input       : reset source  
* Output      : none 
* Author      : xwl                          
**********************************************************************************/
void System_Reset_MCU(RESET_SOURCE source)  
{
    switch(source)
    {
        case RESET_SOURCE_EFC:
        {
            SCU->RCR &= (~BIT29);     
            while(1);
        }break;
        
        case RESET_SOURCE_NVIC_RESET:
        {
            NVIC_SystemReset();
            while(1);  
        }break;
        
        case RESET_SOFT_RESET:
        {
            SCU->RCR &= (~BIT30);               
            while(1);
        }break;

        default: break;
    }
}

/*********************************************************************************
* Function    : System_Enter_Standby_Mode   
* Description : try to enter standby mode
* Input       : none         
* Output      : none
* Author      : xwl                         Date : 2021  
**********************************************************************************/
void System_Enter_Standby_Mode(void)
{
    __set_PRIMASK(1);    // disable interrupt 
    SysTick->CTRL = 0;   // disable systick   
    SCU->STOPCFG |= BIT11;  // set PDDS=1  
    
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); 
    __WFI();     
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));      
    System_Delay(100);  
    
    printfS("Enter Standby Mode Failed! \n");   // should not go here   
}

/*********************************************************************************
* Function    : System_Clear_Stop_Wakeup
* Description : clear all stop setting and status 
* Input       : none
* Output      : none 
* Author      : CWT                         Date : 2021年4月
**********************************************************************************/
void System_Clear_Stop_Wakeup(void) 
{
    EXTI->IENR = 0;  
    EXTI->RTENR = 0;  
    EXTI->FTENR = 0;  
    EXTI->SWIER = 0;  
    EXTI->PDR = 0x7FFFFFU;
}

/*********************************************************************************
* Function    : System_Enter_Stop_Mode
* Description : try to enter stop mode
* Input       : STOPEntry: STOPENTRY_WFI or STOPENTRY_WFE             
* Output      : none  
* Author      : CWT                         Date : 2021  
**********************************************************************************/
void System_Enter_Stop_Mode(uint8_t STOPEntry)
{
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); 
    
    SCU->STOPCFG &= (~BIT11);  // PDDS=0     
    
    //System_SysTick_Off();  
    /* Select Stop mode entry */
    if(STOPEntry == STOPENTRY_WFI)
    {
        /* Wait For Interrupt */   
        __WFI();
    }
    else
    {
        __SEV();   
        __WFE();
        __WFE();    /* Wait For Event */  
    }
    
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));  
    
#ifdef HAL_SYSTICK_ENABLED  // To activate macro in ACM32Fxx_HAL.h      
    //System_SysTick_Init();
#endif  
}

/*********************************************************************************
* Function    : System_Enter_Sleep_Mode
* Description : try to enter sleep mode
* Input       : SleepEntry: SLEEPENTRY_WFI or SLEEPENTRY_WFE                     
* Output      : none  
* Author      : CWT                         Date : 2021  
**********************************************************************************/
void System_Enter_Sleep_Mode(uint8_t SleepEntry)
{
    /* clear SLEEPDEEP bit of Cortex System Control Register */
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));         

    /* Select Stop mode entry */
    if(SleepEntry == SLEEPENTRY_WFI)       
    {
        /* Wait For Interrupt */
        __WFI();
    }
    else
    {
        
        __SEV();      
        __WFE();
        __WFE(); /*Wait For Event */     
    }
        
}


 /*********************************************************************************
* Function    : System_Return_Last_Reset_Reason
* Description : Get System Last Reset Reason
* Input       : none 
* Output      : RESET_REASON
* Author      : CWT                         Date : 2021年4月
**********************************************************************************/
RESET_REASON System_Return_Last_Reset_Reason(void)
{
    RESET_REASON Reset_Reason_Save;   
    RESET_REASON i = RESET_REASON_POR;    
    
    for(i = RESET_REASON_POR; i >= RESET_REASON_POR12; i--)       
    {
        if ((SCU->RSR) & (1U << i))  
        {
            SCU->RSR |= SCU_RSR_RSTFLAG_CLR; // clear reset reason flags  
            Reset_Reason_Save = i;  
            return i;  
        }
    } 
    
    for(i = RESET_REASON_LOW_VOLTAGE; i <= RESET_REASON_SOFT; i++)    
    {
        if ((SCU->RSR) & (1U << i))    
        {
            SCU->RSR |= SCU_RSR_RSTFLAG_CLR; // clear reset reason flags  
            Reset_Reason_Save = i;  
            return i;  
        }
    }  

    return RESET_REASON_INVALID;  // this should not happen 
}

/*********************************************************************************
* Function    : System_Set_Buzzer_Divider
* Description : set buzzer divide factor 
* Input       : 
              div: div factor, if div = 80 then output buzzer freq=HCLK/80   
              enable: FUNC_DISABLE and FUNC_ENABLE      
* Output      : none
* Author      : xwl                         Date : 2021年4月
**********************************************************************************/
void System_Set_Buzzer_Divider(uint32_t div, FUNC_DISABLE_ENABLE enable)  
{      
    if (FUNC_ENABLE == enable)
    {
        SCU->CLKOCR = (SCU->CLKOCR & (~(0x1FFFFU << 5) ) ) | (div << 5);      
        SCU->CLKOCR |= BIT23;  
    }
    else
    {
        SCU->CLKOCR &= (~BIT23);   
    }
}

/*********************************************************************************
* Function    : System_USB_PHY_Config
* Description : Configure USB PHY, such as clock select, pll...
* Input       : none  
* Output      : 0: fail, 1:success 
* Author      : xwl                         Date : 2021年4月
**********************************************************************************/
uint32_t System_USB_PHY_Config(void) 
{
    volatile uint32_t delay_count; 
       
    SCU->PHYCR &= (~BIT2); // exit power down, auto select clock source 
    
    delay_count = SYSTEM_TIMEOUT;  
    while(delay_count--)
    {
        if (SCU->PHYCR & (BIT19)) // clksel_end flag = 1  
        {
            break;  
        }
    }  

    if (delay_count) 
    {
        return HAL_OK;   
    }
    else
    {
        return HAL_TIMEOUT;     
    }
}

