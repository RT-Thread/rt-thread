/*
  ******************************************************************************
  * @file    System_ACM32F0x0.c
  * @version V1.0.0
  * @date    2021
  * @brief   System Source File, includes clock management, reset management
  *          and IO configuration, ...
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

uint32_t gu32_SystemClock;
uint32_t gu32_APBClock;

RESET_REASON Reset_Reason_Save;

/* System count in SysTick_Handler */
volatile uint32_t gu32_SystemCount;

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0U /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */
/******************************************************************************/
#if 0
/*********************************************************************************
* Function    : HardFault_Handler
* Description : Hard Fault handle, while(1) loop, wait for debug
* Input       : none
* Output      : none
* Author      : xwl
**********************************************************************************/
void HardFault_Handler(void)
{
    while(1);
}

/*********************************************************************************
* Function    : SysTick_Handler
* Description : System tick handler
* Input       : none
* Output      : none
* Author      : Chris_Kyle
**********************************************************************************/
void SysTick_Handler(void)
{
    gu32_SystemCount++;
}

/*********************************************************************************
* Function    : System_SysTick_Init
* Description : System Tick Init. Period is 1 ms
* Input       : none
* Output      : none
* Author      : Chris_Kyle
**********************************************************************************/
void System_SysTick_Init(void)
{
    gu32_SystemCount = 0;
    SysTick_Config(gu32_SystemClock / 1000);  //1ms/tick
}
#endif
/*********************************************************************************
* Function    : System_SysTick_Off
* Description : Turn off System Tick
* Input       : none
* Output      : none
* Author      : xwl
**********************************************************************************/
void System_SysTick_Off(void)
{
    SysTick->CTRL = 0;
}
/*********************************************************************************
* Function    : System_Init
* Description : Initialize the system clock
* Input       : none
* Outpu       : none
* Author      : Chris_Kyle                         Date : 2021
**********************************************************************************/
void System_Init(void)
{
    SCU->RCR |= SCU_RCR_REMAP_EN;
    System_Set_Buzzer_Divider(80, FUNC_DISABLE); // disable clock out
    /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
    /* Vector Table Relocation in Internal SRAM */
    SCU->VECTOROFFSET = SRAM_BASE | VECT_TAB_OFFSET | SCU_VECTOROFFSET_VOFFSETEN;
#else
    /* Vector Table Relocation in Internal FLASH */
    SCU->VECTOROFFSET = EFLASH_BASE | VECT_TAB_OFFSET | SCU_VECTOROFFSET_VOFFSETEN;
#endif

    /* Initialize the system clock */
    if (false == System_Clock_Init(DEFAULT_SYSTEM_CLOCK))
    {
        while(1);
    }

#ifdef HAL_SYSTICK_ENABLED  // To activate macro in ACM32Fxx_HAL.h
    System_SysTick_Init();
#endif
}

/*********************************************************************************
* Function    : System_Clock_Init
* Description : Clock init
* Input       : fu32_Clock: System core clock
* Outpu       : 0: success, other value: fail reason
* Author      : xwl                         Date : 2021
**********************************************************************************/
bool System_Clock_Init(uint32_t fu32_Clock)
{
    uint32_t lu32_DIV, lu32_system_clk_source, lu32_result, lu32_timeout;

    lu32_system_clk_source = CLK_SRC_RC64M;

    SET_EFC_RD_WAIT(RD_WAIT_SET_DEFAULT)

    switch (fu32_Clock)
    {
        /* 64MHz */
        case 64000000: lu32_DIV = 1; break;

        /* 32MHz */
        case 32000000: lu32_DIV = 2; break;

        /* 16MHz */
        case 16000000: lu32_DIV = 4; break;

        /* 8MHz */
        case 8000000:  lu32_DIV = 8; break;

        default: return false;
    }

    lu32_result = 0;

    if (lu32_system_clk_source == CLK_SRC_XTH_PLL)
    {
        lu32_timeout = 0;

        SCU->XTHCR = SCU_XTHCR_XTH_EN | SCU_XTHCR_READYTIME_32768;
        while (0 == (SCU->XTHCR & SCU_XTHCR_XTHRDY))
        {
            if (lu32_timeout == SYSTEM_TIMEOUT)
            {
                lu32_result = 1;
                break;
            }
            lu32_timeout++;
        }

        if (0 == lu32_result)
        {
            SCU->PLLCR |=  SCU_PLLCR_PLL_EN;
            SCU->PLLCR &= ~(SCU_PLLCR_PLL_SLEEP);
            while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) )) {}

#ifdef XTH_8M_CRYSTAL
            SCU->PLLCR = (SCU->PLLCR &(~(0x1FFFFU << 3))) | (15U << 3) | (1U << 12) | (0U << 16);
#endif

#ifdef XTH_12M_CRYSTAL
            SCU->PLLCR = (SCU->PLLCR &(~(0x1FFFFU << 3))) | (15U << 3) | (2U << 12) | (0U << 16);
#endif

            SCU->PLLCR = (SCU->PLLCR & (~(0x3U << 1)) ) | (3 << 1);
            SCU->PLLCR |= SCU_PLLCR_PLL_UPDATE_EN;
            while(!(SCU->PLLCR & (SCU_PLLCR_PLL_FREE_RUN) ) );

            /* Division Config */
            SCU->CCR2 = (SCU->CCR2 & (~0xFF)) | APB_CLK_DIV_0 | (lu32_DIV - 1);
            while((SCU->CCR2 & (1UL << 31)) == 0x00);

            /* Clock Select PLL */
            SCU->CCR1 = SYS_CLK_SRC_PLLCLK;
        }
        else
        {
            SCU->XTHCR &= (~SCU_XTHCR_XTH_EN);
        }
    }

    if ( (lu32_system_clk_source == CLK_SRC_RC64M) || (0 != lu32_result) )
    {
        /* Division Config */
        SCU->CCR2 = (SCU->CCR2 & (~0xFF)) | APB_CLK_DIV_0 | (lu32_DIV - 1);
        while((SCU->CCR2 & (1UL << 31)) == 0x00);

        /* Clock Select RCH */
        SCU->CCR1 = SYS_CLK_SRC_RCH;
    }

    gu32_SystemClock = fu32_Clock;
    gu32_APBClock    = fu32_Clock;

    /* Eflash Config */
    //HAL_EFlash_Init(gu32_SystemClock);

    return true;
}

/*********************************************************************************
* Function    : System_Get_SystemClock
* Description : get AHB clock frequency
* Input       : none
* Outpu       : frequency, measured as Hz
* Author      : Chris_Kyle                         Date : 2020
**********************************************************************************/
uint32_t System_Get_SystemClock(void)
{
    return gu32_SystemClock;
}

/*********************************************************************************
* Function    : System_Get_APBClock
* Description : get APB clock frequency
* Input       : none
* Outpu       : frequency, measured as Hz
* Author      : Chris_Kyle                         Date : 2021
**********************************************************************************/
uint32_t System_Get_APBClock(void)
{
    return gu32_APBClock;
}

/*********************************************************************************
* Function    : System_Module_Reset
* Description : reset module
* Input       : module id
* Outpu       : none
* Author      : Chris_Kyle                         Date : 2021
**********************************************************************************/
void System_Module_Reset(enum_RST_ID_t fe_ID_Index)
{
    SCU->IPRST &= (~(1 << fe_ID_Index));
    System_Delay(2);
    SCU->IPRST |= (1 << fe_ID_Index);
}

/*********************************************************************************
* Function    : System_Module_Enable
* Description : enable module clock
* Input       : module id
* Outpu       : none
* Author      : Chris_Kyle                         Date : 2021
**********************************************************************************/
void System_Module_Enable(enum_Enable_ID_t fe_ID_Index)
{
    if (fe_ID_Index > 6)
    {
        SCU->IPCKENR1 |= (1U << (fe_ID_Index - 7) );
    }
    else
    {
        SCU->IPCKENR2 |= (1U << fe_ID_Index);
    }

    System_Delay(2);
}

/*********************************************************************************
* Function    : System_Module_Disable
* Description : disable module clock
* Input       : module id
* Outpu       : none
* Author      : Chris_Kyle                         Date : 2021
**********************************************************************************/
void System_Module_Disable(enum_Enable_ID_t fe_ID_Index)
{
    if (fe_ID_Index > 6)
    {
        SCU->IPCKENR1 &= ~(1U << (fe_ID_Index - 7));
    }
    else
    {
        SCU->IPCKENR2 &= ~(1U << fe_ID_Index);
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
* Outpu       : none
* Author      : Chris_Kyle                         Date : 2021
**********************************************************************************/
void System_Enable_RC32K(void)
{
    PMU->ANACR |= RPMU_ANACR_RC32K_EN;
    while(!(PMU->ANACR & RPMU_ANACR_RC32K_RDY));
}

/*********************************************************************************
* Function    : System_Disable_RC32K
* Description : Disable RC32K
* Input       : none
* Outpu       : none
* Author      : CWT                         Date : 2021
**********************************************************************************/
void System_Disable_RC32K(void)
{
    PMU->ANACR &= (~RPMU_ANACR_RC32K_EN);
}

/*********************************************************************************
* Function    : System_Enable_XTAL
* Description : Enable XTAL, make sure RTC Domain Access is allowed
* Input       : none
* Outpu       : none
* Author      : Chris_Kyle                         Date : 2021
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
        }

        case RESET_SOURCE_NVIC_RESET:
        {
            NVIC_SystemReset();
            while(1);
        }

        case RESET_SOFT_RESET:
        {
            SCU->RCR &= (~BIT30);
            while(1);
        }

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
* Author      : CWT                         Date : 2021
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

    System_SysTick_Off();
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
    System_SysTick_Init();
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
* Author      : CWT                         Date : 2021
**********************************************************************************/
RESET_REASON System_Return_Last_Reset_Reason(void)
{
    RESET_REASON i = RESET_REASON_POR;
    Reset_Reason_Save = RESET_REASON_POR;

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
* Function    : System_Return_Saved_Reset_Reason
* Description : Get saved Reset Reason
* Input       : none
* Output      : RESET_REASON
* Author      : CWT                         Date : 2021
**********************************************************************************/
RESET_REASON System_Return_Saved_Reset_Reason(void)
{
    return Reset_Reason_Save;
}
 /*********************************************************************************
* Function    : System_Set_Buzzer_Divider
* Description : set buzzer divide factor
* Input       :
              div: div factor, if div = 80 then output buzzer freq=HCLK/80
              enable: FUNC_DISABLE and FUNC_ENABLE
* Output      : none
* Author      : xwl                         Date : 2021
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

