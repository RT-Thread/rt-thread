 /**
******************************************************************************
* @file    system_MM32L3xx.c
* @author  AE Team
* @version V1.0.0
* @date    28/7/2017
* @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
* 
* 1.  This file provides two functions and one global variable to be called from 
*     user application:
*      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
*                      factors, AHB/APBx prescalers and Flash settings). 
*                      This function is called at startup just after reset and 
*                      before branch to main program. This call is made inside
*                      the "startup_MM32L3xx.s" file.
*
*      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
*                                  by the user application to setup the SysTick 
*                                  timer or configure other parameters.
*                                     
*      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
*                                 be called whenever the core clock is changed
*                                 during program execution.
*
* 2. After each device reset the HSI (8 MHz) is used as system clock source.
*    Then SystemInit() function is called, in "startup_MM32L3xx.s" file, to
*    configure the system clock before to branch to main program.
*
* 3. If the system clock source selected by user fails to startup, the SystemInit()
*    function will do nothing and HSI still used as system clock source. User can 
*    add some code to deal with this issue inside the SetSysClock() function.
*
* 4. The default value of HSE crystal is set to 8 MHz (or 25 MHz, depedning on
*    the product used), refer to "HSE_VALUE" define in "MM32L3xx.h" file. 
*    When HSE is used as system clock source, directly or through PLL, and you
*    are using different crystal you have to adapt the HSE value to your own
*    configuration.
*        
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MINDMOTION SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
******************************************************************************
*/

/** @addtogroup CMSIS
* @{
*/
#include "HAL_device.h"


/**
* @}
*/

/**
* @}
*/

/*!< Uncomment the line corresponding to the desired System clock (SYSCLK)
frequency (after reset the HSI is used as SYSCLK source)

IMPORTANT NOTE:
============== 
1. After each device reset the HSI is used as System clock source.

2. Please make sure that the selected System clock doesn't exceed your device's
maximum frequency.

3. If none of the define below is enabled, the HSI is used as System clock
source.

4. The System clock configuration functions provided within this file assume that:
- For Low, Medium and High density Value line devices an external 8MHz 
crystal is used to drive the System clock.
- For Low, Medium and High density devices an external 8MHz crystal is
used to drive the System clock.
- For Connectivity line devices an external 25MHz crystal is used to drive
the System clock.
If you are using different crystal you have to adapt those functions accordingly.
*/

//#define SYSCLK_FREQ_HSE    HSE_VALUE 
//#define SYSCLK_FREQ_24MHz  24000000  
//#define SYSCLK_FREQ_36MHz  36000000 
//#define SYSCLK_FREQ_48MHz  48000000 
//#define SYSCLK_FREQ_56MHz  56000000 
//#define SYSCLK_FREQ_72MHz  72000000
//#define SYSCLK_FREQ_96MHz  96000000

//#define SYSCLK_HSI_48MHz  48000000
//#define SYSCLK_HSI_72MHz  72000000
#define SYSCLK_HSI_96MHz  96000000

/*!< Uncomment the following line if you need to relocate your vector Table in
Internal SRAM. */ 
//#define VECT_TAB_SRAM 
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. 
This value must be a multiple of 0x200. */

/**
* @}
*/

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_24MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_24MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_36MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_36MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_48MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_56MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_56MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_72MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_96MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_96MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_HSI_48MHz
uint32_t SystemCoreClock         = SYSCLK_HSI_48MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_HSI_72MHz
uint32_t SystemCoreClock         = SYSCLK_HSI_72MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_HSI_96MHz
uint32_t SystemCoreClock         = SYSCLK_HSI_96MHz;        /*!< System Clock Frequency (Core Clock) */
#else /*!< HSI Selected as System Clock source */
uint32_t SystemCoreClock         = HSI_VALUE_PLL_OFF;        /*!< System Clock Frequency (Core Clock) */
#endif

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
/**
* @}
*/

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_24MHz
static void SetSysClockTo24(void);
#elif defined SYSCLK_FREQ_36MHz
static void SetSysClockTo36(void);
#elif defined SYSCLK_FREQ_48MHz
static void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_56MHz
static void SetSysClockTo56(void);  
#elif defined SYSCLK_FREQ_72MHz
static void SetSysClockTo72(void);
#elif defined SYSCLK_FREQ_96MHz
static void SetSysClockTo96(void);

#elif defined SYSCLK_HSI_48MHz
static void SetSysClockTo48_HSI(void);
#elif defined SYSCLK_HSI_72MHz
static void SetSysClockTo72_HSI(void);
#elif defined SYSCLK_HSI_96MHz
static void SetSysClockTo96_HSI(void);
#endif

#ifdef DATA_IN_ExtSRAM
static void SystemInit_ExtMemCtl(void); 
#endif /* DATA_IN_ExtSRAM */

/**
* @}
*/

/**
* @brief  Setup the microcontroller system
*         Initialize the Embedded Flash Interface, the PLL and update the 
*         SystemCoreClock variable.
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
void SystemInit (void)
{
    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;
    
    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= (uint32_t)0xF8FF000C;    
    
    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;
    
    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;
    
    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;
    RCC->CR &= (uint32_t)0x000FFFFF;
    
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
    
    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();
    
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}

/**
* @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
* @param  None
* @retval None
*/
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
    SetSysClockTo24();
#elif defined SYSCLK_FREQ_36MHz
    SetSysClockTo36();
#elif defined SYSCLK_FREQ_48MHz
    SetSysClockTo48();
#elif defined SYSCLK_FREQ_56MHz
    SetSysClockTo56();  
#elif defined SYSCLK_FREQ_72MHz
    SetSysClockTo72();
#elif defined SYSCLK_FREQ_96MHz
    SetSysClockTo96();
    
#elif defined SYSCLK_HSI_48MHz
    SetSysClockTo48_HSI();
#elif defined SYSCLK_HSI_72MHz
    SetSysClockTo72_HSI();
#elif defined SYSCLK_HSI_96MHz
    SetSysClockTo96_HSI();
#endif
    
    /* If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}

#ifdef SYSCLK_FREQ_HSE
/**
* @brief  Selects HSE as System clock source and configure HCLK, PCLK2
*          and PCLK1 prescalers.
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	u16 i = 0;
	int nTime = 2;
    
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 750;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        
        /* Select HSE as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;    
        
        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }  
}
#elif defined SYSCLK_FREQ_24MHz
/**
* @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2 
*          and PCLK1 prescalers.
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockTo24(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	u16 i = 0;
	int nTime = 2;
    
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 750;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
        
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        FLASH->ACR |= 0x01;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        
        /*  PLL configuration:  = (HSE ) * (2+1) = 24 MHz */
        RCC->CFGR &= (uint32_t)0xFFFCFFFF;
        RCC->CR &= (uint32_t)0x000FFFFF;  
        
        RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC ;
        RCC->CR |= 0x08000000;//pll=3/1
        //RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        //RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        
        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
        
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    } 
}
#elif defined SYSCLK_FREQ_36MHz
/**
* @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2 
*          and PCLK1 prescalers. 
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockTo36(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	u16 i = 0;
	int nTime = 2;
    
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 750;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        FLASH->ACR |= 0x01;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
        
        /*  PLL configuration:  = (HSE ) * (8+1)/(1+1) = 36 MHz */
        RCC->CFGR &= (uint32_t)0xFFFCFFFF;
        RCC->CR &= (uint32_t)0x000FFFFF;  
        
        RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC ;
        RCC->CR |= 0x20100000;//pll = 9/2
        //RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        //RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        
        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
        
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }  
}
#elif defined SYSCLK_FREQ_48MHz
/**
* @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2 
*          and PCLK1 prescalers. 
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockTo48(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	u16 i = 0;
	int nTime = 2;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 750;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        FLASH->ACR |= 0x01;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        
        /*  PLL configuration:  = (HSE ) * (5+1) = 48MHz */
        RCC->CFGR &= (uint32_t)0xFFFCFFFF;
        RCC->CR &= (uint32_t)0x000FFFFF;  
        
        RCC->CFGR |= (uint32_t ) RCC_CFGR_PLLSRC ;
        RCC->CR |= 0x14000000;//pll = 6/1
        //RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        //RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        
        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
        
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_FREQ_56MHz
/**
* @brief  Sets System clock frequency to 56MHz and configure HCLK, PCLK2 
*          and PCLK1 prescalers. 
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockTo56(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	u16 i = 0;
	int nTime = 2;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 750;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        FLASH->ACR |=0x02;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        
        /*  PLL configuration:  = (HSE ) * (6+1) = 56 MHz */
        RCC->CFGR &= (uint32_t)0xFFFCFFFF;
        RCC->CR &= (uint32_t)0x000FFFFF;  
        
        RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC ;
        RCC->CR |= 0x18000000;//pll = 7/1
        //RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        //RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        
        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
        
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_FREQ_72MHz
/**
* @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
*          and PCLK1 prescalers. 
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockTo72(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	u16 i = 0;
	int nTime = 2;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 750;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        FLASH->ACR |=0x03;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        
        /*  PLL configuration:  = (HSE ) * (8+1) = 72 MHz */
        RCC->CFGR &= (uint32_t)0xFFFCFFFF;
        RCC->CR &= (uint32_t)0x000FFFFF;  
        
        RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC ;
        //    RCC->CR |= 0x20000000;//pll = 9/1
        RCC->CR |= (1<<20)|(17<<26);//pll = 9/1
        //RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        //RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        
        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
        
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_FREQ_96MHz
/**
* @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
*          and PCLK1 prescalers. 
* @note   This function should be used only after reset.
* @param  None
* @retval None
*/
static void SetSysClockTo96(void)
{
    int i = 100000;
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	int nTime = 2;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    
	/*delay more than 2ms*/
	while(nTime--){
		i = 1500;
		while(i--);
	}
	
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  
    i = 10000;while(i--);
    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state ,bit0~2*/
        FLASH->ACR &= ~0x07;
        FLASH->ACR |=0x03;
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
        
        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
        
        /*  PLL configuration:  = (HSE ) * (11+1) = 96 MHz */
        RCC->CFGR &= (uint32_t)0xFFFCFFFF;
        RCC->CR &= (uint32_t)0x000FFFFF;  
        
        RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC ;
        RCC->CR |= 0x2C000000;//pll = 12/1
        //RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        //RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_Div2 | RCC_CFGR_PLLMULL6);
        
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        
        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    
        
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
        configuration. User can add here some code to deal with this error */
    }
}



#elif defined SYSCLK_HSI_48MHz
void SetSysClockTo48_HSI()
{
    unsigned char temp=0;   
    
    RCC->CR|=RCC_CR_HSION;  
    while(!(RCC->CR&RCC_CR_HSIRDY));
    RCC->CFGR=RCC_CFGR_PPRE1_2; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
    
    RCC->CFGR&=~RCC_CFGR_PLLSRC;	  //PLLSRC ON 
    
    RCC->CR &=~(RCC_CR_PLLON);		//清PLL//	RCC->CR &=~(7<<20);		//清PLL
    
    RCC->CR &=~(0x1f<<26);	
    RCC->CR|=(4 - 1) << 26;   //设置PLL值 2~16
    
    FLASH->ACR=FLASH_ACR_LATENCY_1|FLASH_ACR_PRFTBE;	  //FLASH 2个延时周期
    
    RCC->CR|=RCC_CR_PLLON;  //PLLON
    while(!(RCC->CR&RCC_CR_PLLRDY));//等待PLL锁定
    RCC->CFGR&=~RCC_CFGR_SW;
    RCC->CFGR|=RCC_CFGR_SW_PLL;//PLL作为系统时钟	 
    while(temp!=0x02)     //等待PLL作为系统时钟设置成功
    {    
        temp=RCC->CFGR>>2;
        temp&=0x03;
    } 
}	
#elif defined SYSCLK_HSI_72MHz
void SetSysClockTo72_HSI()
{
    unsigned char temp=0;   
    RCC->CR|=RCC_CR_HSION;  
    while(!(RCC->CR&RCC_CR_HSIRDY));
    RCC->CFGR=RCC_CFGR_PPRE1_2; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
    
    RCC->CFGR&=~RCC_CFGR_PLLSRC;	  //PLLSRC ON 
    
    RCC->CR &=~(RCC_CR_PLLON);		//清PLL//	RCC->CR &=~(7<<20);		//清PLL
    
    RCC->CR &=~(0x1f<<26);	
    RCC->CR|=(6 - 1) << 26;   //设置PLL值 2~16
    
    FLASH->ACR=FLASH_ACR_LATENCY_1|FLASH_ACR_PRFTBE;	  //FLASH 2个延时周期
    
    RCC->CR|=RCC_CR_PLLON;  //PLLON
    while(!(RCC->CR&RCC_CR_PLLRDY));//等待PLL锁定
    RCC->CFGR&=~RCC_CFGR_SW;
    RCC->CFGR|=RCC_CFGR_SW_PLL;//PLL作为系统时钟	 
    while(temp!=0x02)     //等待PLL作为系统时钟设置成功
    {    
        temp=RCC->CFGR>>2;
        temp&=0x03;
    } 
}	
#elif defined SYSCLK_HSI_96MHz
void SetSysClockTo96_HSI()
{
    unsigned char temp=0;   
    RCC->CR|=RCC_CR_HSION;  
    while(!(RCC->CR&RCC_CR_HSIRDY));
    RCC->CFGR=RCC_CFGR_PPRE1_2; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
    
    RCC->CFGR&=~RCC_CFGR_PLLSRC;	  //PLLSRC ON 
    
    RCC->CR &=~(RCC_CR_PLLON);		//清PLL//	RCC->CR &=~(7<<20);		//清PLL
    
    RCC->CR &=~(0x1f<<26);	
    RCC->CR|=(8 - 1) << 26;   //设置PLL值 2~16
    
    FLASH->ACR=FLASH_ACR_LATENCY_1|FLASH_ACR_LATENCY_0|FLASH_ACR_PRFTBE;	  //FLASH 2个延时周期
    
    RCC->CR|=RCC_CR_PLLON;  //PLLON
    while(!(RCC->CR&RCC_CR_PLLRDY));//等待PLL锁定
    RCC->CFGR&=~RCC_CFGR_SW;
    RCC->CFGR|=RCC_CFGR_SW_PLL;//PLL作为系统时钟	 
    while(temp!=0x02)     //等待PLL作为系统时钟设置成功
    {    
        temp=RCC->CFGR>>2;
        temp&=0x03;
    } 
}	
#endif

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/    
/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
