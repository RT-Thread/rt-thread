////////////////////////////////////////////////////////////////////////////////
/// @file     SYSTEM_MM32.C
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _SYSTEM_MM32_C_

// Files includes

/// @addtogroup CMSIS
/// @{

#include "mm32_device.h"


/// @}



/// @}


/// Uncomment the line corresponding to the desired System clock (SYSCLK)
/// frequency (after reset the HSI is used as SYSCLK source)
///
/// IMPORTANT NOTE:
/// ==============
/// 1. After each device reset the HSI is used as System clock source.
///
/// 2. Please make sure that the selected System clock doesn't exceed your device's
/// maximum frequency.
///
/// 3. If none of the define below is enabled, the HSI is used as System clock
/// source.
///
/// 4. The System clock configuration functions provided within this file assume that:
/// - For Low, Medium and High density Value line devices an external 8MHz
/// crystal is used to drive the System clock.
/// - For Low, Medium and High density devices an external 8MHz crystal is
/// used to drive the System clock.
/// - For Connectivity line devices an external 25MHz crystal is used to drive
/// the System clock.
/// If you are using different crystal you have to adapt those functions accordingly.

//#define SYSCLK_FREQ_HSE    HSE_VALUE          //HSE_VALUE is define in reg_common.h
//#define SYSCLK_FREQ_24MHz  (HSE_VALUE*3)      //24000000 based HSE_VALUE = 8000000
//#define SYSCLK_FREQ_36MHz  (HSE_VALUE*9/2)    //36000000 based HSE_VALUE = 8000000
//#define SYSCLK_FREQ_48MHz  (HSE_VALUE*6)      //48000000 based HSE_VALUE = 8000000
//#define SYSCLK_FREQ_XXMHz  (HSE_VALUE*6)      //48000000 based HSE_VALUE = 8000000
//#define SYSCLK_FREQ_XXMHz  (HSE_VALUE*9)      //72000000 based HSE_VALUE = 8000000
//#define SYSCLK_FREQ_XXMHz  (HSE_VALUE*12)      //96000000 based HSE_VALUE = 8000000
#define SYSCLK_FREQ_XXMHz (HSE_VALUE*15)       //120000000 based HSE_VALUE = 8000000

#if defined(SYSCLK_FREQ_HSE) || defined(SYSCLK_FREQ_24MHz) || defined(SYSCLK_FREQ_36MHz) || defined(SYSCLK_FREQ_48MHz) || defined(SYSCLK_FREQ_XXMHz)

#if defined(HSE_VALUE) && (!(HSE_VALUE == 8000000))
#warning redefine HSE_VALUE in reg_common.h Line 48 and ignore this warning
#endif

#endif


//#define SYSCLK_HSI_24MHz  24000000
//#define SYSCLK_HSI_36MHz  36000000
//#define SYSCLK_HSI_48MHz  48000000
//#define SYSCLK_HSI_XXMHz  48000000
//#define SYSCLK_HSI_XXMHz  72000000
//#define SYSCLK_HSI_XXMHz  96000000
#define SYSCLK_HSI_XXMHz  120000000
/// Uncomment the following line if you need to relocate your vector Table in
/// Internal SRAM.
///#define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0
/// Vector Table base offset field.
/// This value must be a multiple of 0x200.


/// @}




///////////////////////////////////////////////////////////////
///Clock Definitions
///////////////////////////////////////////////////////////////
#if defined SYSCLK_FREQ_HSE
u32 SystemCoreClock         = SYSCLK_FREQ_HSE;
#elif defined SYSCLK_FREQ_24MHz
u32 SystemCoreClock         = SYSCLK_FREQ_24MHz;
#elif defined SYSCLK_FREQ_36MHz
u32 SystemCoreClock         = SYSCLK_FREQ_36MHz;
#elif defined SYSCLK_FREQ_48MHz
u32 SystemCoreClock         = SYSCLK_FREQ_48MHz;
#elif defined SYSCLK_FREQ_XXMHz
u32 SystemCoreClock         = SYSCLK_FREQ_XXMHz;


#elif defined SYSCLK_HSI_24MHz
u32 SystemCoreClock         = SYSCLK_HSI_24MHz;
#elif defined SYSCLK_HSI_36MHz
u32 SystemCoreClock         = SYSCLK_HSI_36MHz;
#elif defined SYSCLK_HSI_48MHz
u32 SystemCoreClock         = SYSCLK_HSI_48MHz;
#elif defined SYSCLK_HSI_XXMHz
u32 SystemCoreClock         = SYSCLK_HSI_XXMHz;
#else //HSI Selected as System Clock source 
u32 SystemCoreClock         = HSI_VALUE;
#endif

__I u8 AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/// @}


static void SetSysClock(void);

#if defined SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_24MHz
static void SetSysClockTo24(void);
#elif defined SYSCLK_FREQ_36MHz
static void SetSysClockTo36(void);
#elif defined SYSCLK_FREQ_48MHz
static void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_XXMHz
static void SetSysClockToXX(void);

#elif defined SYSCLK_HSI_24MHz
static void SetSysClockTo24_HSI(void);
#elif defined SYSCLK_HSI_36MHz
static void SetSysClockTo36_HSI(void);
#elif defined SYSCLK_HSI_48MHz
static void SetSysClockTo48_HSI(void);
#elif defined SYSCLK_HSI_XXMHz
static void SetSysClockToXX_HSI(void);
#endif

#ifdef DATA_IN_ExtSRAM
static void SystemInit_ExtMemCtl(void);
#endif //DATA_IN_ExtSRAM 


/// @}



/// @brief  Setup the microcontroller system
///         Initialize the Embedded Flash Interface, the PLL and update the
///         SystemCoreClock variable.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None

void SystemInit (void)
{
    //Reset the RCC clock configuration to the default reset state(for debug purpose)
    //Set HSION bit
    RCC->CR |= (u32)0x00000001;

    //Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
    RCC->CFGR &= (u32)0xF8FFC00C;

    //Reset HSEON, CSSON and PLLON bits
    RCC->CR &= (u32)0xFEF6FFFF;

    //Reset HSEBYP bit
    RCC->CR &= (u32)0xFFFBFFFF;

    //Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
    RCC->CFGR &= (u32)0xFF3CFFFF;
    RCC->CR &= (u32)0x008FFFFF;

    //Disable all interrupts and clear pending bits
    RCC->CIR = 0x009F0000;
    //Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
    //Configure the Flash Latency cycles and enable prefetch buffer
    SetSysClock();
}


/// @brief  use to return the pllm&plln.
/// @param  pllclkSourceFrq : PLL source clock frquency;
///         pllclkFrq : Target PLL clock frquency;
///         plln : PLL factor PLLN
///         pllm : PLL factor PLLM
/// @retval amount of error
u32 AutoCalPllFactor(u32 pllclkSourceFrq, u32 pllclkFrq, u8* plln, u8* pllm)
{
    u32 n, m;
    u32 tempFrq;
    u32 minDiff = pllclkFrq;
    u8  flag = 0;
    for(m = 0; m < 4 ; m++) {
        for(n = 0; n < 64 ; n++) {
            tempFrq =  pllclkSourceFrq * (n + 1) / (m + 1);
            tempFrq = (tempFrq >  pllclkFrq) ? (tempFrq - pllclkFrq) : (pllclkFrq - tempFrq) ;

            if(minDiff > tempFrq) {
                minDiff =  tempFrq;
                *plln = n;
                *pllm = m;
            }
            if(minDiff == 0) {
                flag = 1;
                break;
            }
        }
        if(flag != 0) {
            break;
        }
    }
    return  minDiff;
}
static void DELAY_xUs(u32 count)
{
    u32 temp;
    SysTick->CTRL = 0x0;                                                        //disable systick function
    SysTick->LOAD = count * 8;                                                    //time count for 1us with HSI as SYSCLK
    SysTick->VAL = 0x00;                                                        //clear counter
    SysTick->CTRL = 0x5;                                                        //start discrease with Polling
    do {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));                              //wait time count done
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                                  //Close Counter
    SysTick->VAL = 0X00;                                                        //clear counter
}
/// @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
/// @param  None
/// @retval None

static void SetSysClock(void)
{
    CACHE->CCR &= ~(0x3 << 3);
    CACHE->CCR |= 1;
    while((CACHE->SR & 0x3) != 2);
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
    SetSysClockTo24();
#elif defined SYSCLK_FREQ_36MHz
    SetSysClockTo36();
#elif defined SYSCLK_FREQ_48MHz
    SetSysClockTo48();
#elif defined SYSCLK_FREQ_XXMHz
    SetSysClockToXX();

#elif defined SYSCLK_HSI_24MHz
    SetSysClockTo24_HSI();
#elif defined SYSCLK_HSI_36MHz
    SetSysClockTo36_HSI();
#elif defined SYSCLK_HSI_48MHz
    SetSysClockTo48_HSI();
#elif defined SYSCLK_HSI_XXMHz
    SetSysClockToXX_HSI();
#endif

    //If none of the define above is enabled, the HSI is used as System clock
    //source (default after reset)
}

#ifdef SYSCLK_FREQ_HSE

/// @brief  Selects HSE as System clock source and configure HCLK, PCLK2
///         and PCLK1 prescalers.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None

static void SetSysClockToHSE(void)
{
    __IO u32 StartUpCounter = 0, HSEStatus = 0;
    s32 i;

    //SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    //Enable HSE
    RCC->CR |= ((u32)RCC_CR_HSEON);

    //Wait till HSE is ready and if Time out is reached exit
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (u32)0x01;
        i = 2000;
        while(i--);
    }
    else {
        HSEStatus = (u32)0x00;
    }

    if (HSEStatus == (u32)0x01) {
        //Enable Prefetch Buffer
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        //Flash 0 wait state ,bit0~2
        FLASH->ACR &= ~0x07;
        //HCLK = SYSCLK
        RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV1;

        //PCLK2 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE2_DIV1;

        //PCLK1 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV1;

        //Select HSE as system clock source
        RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
        RCC->CFGR |= (u32)RCC_CFGR_SW_HSE;

        //Wait till HSE is used as system clock source
        while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)0x04) {
        }
    }
    else {
        //If HSE fails to start-up, the application will have wrong clock
        //configuration. User can add here some code to deal with this error
    }
}
#elif defined SYSCLK_FREQ_24MHz

/// @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2
///         and PCLK1 prescalers.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None

static void SetSysClockTo24(void)
{
    __IO u32 StartUpCounter = 0, HSEStatus = 0;
    s32 i;

    //SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    //Enable HSE
    RCC->CR |= ((u32)RCC_CR_HSEON);

    //Wait till HSE is ready and if Time out is reached exit
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (u32)0x01;
        i = 2000;
        while(i--);
    }
    else {
        HSEStatus = (u32)0x00;
    }

    if (HSEStatus == (u32)0x01) {
        //Enable Prefetch Buffer
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        //Flash 0 wait state ,bit0~2
        FLASH->ACR &= ~0x07;
        FLASH->ACR |= 0x01;
        //HCLK = SYSCLK
        RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV1;

        //PCLK2 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE2_DIV1;

        //PCLK1 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV1;

        // PLL configuration:  = (HSE ) * (2+1) = 24 MHz
        RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
        RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

        RCC->APB1ENR |= RCC_APB1ENR_PWR;
        RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
        RCC->PLLCFGR |= ((0 << RCC_PLLCFGR_PLL_DN_Pos) | (2 << RCC_PLLCFGR_PLL_DP_Pos));
        //Enable PLL
        RCC->CR |= RCC_CR_PLLON;

        //Wait till PLL is ready
        while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

        //Select PLL as system clock source
        RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
        RCC->CFGR |= (u32)RCC_CFGR_SW_PLL;

        //Wait till PLL is used as system clock source
        while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)0x08) {
        }
    }
    else {
        //If HSE fails to start-up, the application will have wrong clock
        //configuration. User can add here some code to deal with this error
    }
}
#elif defined SYSCLK_FREQ_36MHz

/// @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2
///         and PCLK1 prescalers.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None

static void SetSysClockTo36(void)
{
    s32 i;
    __IO u32 StartUpCounter = 0, HSEStatus = 0;

    //SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    //Enable HSE
    RCC->CR |= ((u32)RCC_CR_HSEON);

    //Wait till HSE is ready and if Time out is reached exit
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (u32)0x01;
        i = 2000;
        while(i--);
    }
    else {
        HSEStatus = (u32)0x00;
    }

    if (HSEStatus == (u32)0x01) {
        //Enable Prefetch Buffer
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        //Flash 0 wait state ,bit0~2
        FLASH->ACR &= ~0x07;
        FLASH->ACR |= 0x01;
        //HCLK = SYSCLK
        RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV1;

        //PCLK2 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE2_DIV1;

        //PCLK1 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV1;
        RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
        RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

        RCC->APB1ENR |= RCC_APB1ENR_PWR;
        RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
        RCC->PLLCFGR |= ((1 << RCC_PLLCFGR_PLL_DN_Pos) | (8 << RCC_PLLCFGR_PLL_DP_Pos));
        //Enable PLL
        RCC->CR |= RCC_CR_PLLON;

        //Wait till PLL is ready
        while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

        //Select PLL as system clock source
        RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
        RCC->CFGR |= (u32)RCC_CFGR_SW_PLL;

        //Wait till PLL is used as system clock source
        while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)0x08) {
        }
    }
    else {
        //If HSE fails to start-up, the application will have wrong clock
        //configuration. User can add here some code to deal with this error
    }
}
#elif defined SYSCLK_FREQ_48MHz

/// @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
///         and PCLK1 prescalers.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None

static void SetSysClockTo48(void)
{
    __IO u32 StartUpCounter = 0, HSEStatus = 0;
    s32 i;
    //SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    //Enable HSE
    RCC->CR |= ((u32)RCC_CR_HSEON);

    //Wait till HSE is ready and if Time out is reached exit
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (u32)0x01;
        i = 2000;
        while(i--);
    }
    else {
        HSEStatus = (u32)0x00;
    }

    if (HSEStatus == (u32)0x01) {
        //Enable Prefetch Buffer
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        //Flash 0 wait state ,bit0~2
        FLASH->ACR &= ~0x07;
        FLASH->ACR |= 0x02;
        //HCLK = SYSCLK
        RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV1;

        //PCLK2 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE2_DIV1;

        //PCLK1 = HCLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV2;

        // PLL configuration:  = (HSE ) * (5+1) = 48MHz
        RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
        RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

        RCC->APB1ENR |= RCC_APB1ENR_PWR;
        RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
        RCC->PLLCFGR |= ((0 << RCC_PLLCFGR_PLL_DN_Pos) | (5 << RCC_PLLCFGR_PLL_DP_Pos));
        //Enable PLL
        RCC->CR |= RCC_CR_PLLON;

        //Wait till PLL is ready
        while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

        //Select PLL as system clock source
        RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
        RCC->CFGR |= (u32)RCC_CFGR_SW_PLL;

        //Wait till PLL is used as system clock source
        while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)0x08) {
        }
    }
    else {
        //If HSE fails to start-up, the application will have wrong clock
        //configuration. User can add here some code to deal with this error
    }
}
#elif defined SYSCLK_FREQ_XXMHz

/// @brief  Sets System clock frequency to XXMHz and configure HCLK, PCLK2
///         and PCLK1 prescalers.
/// @note   This function should be used only after reset.
/// @param  None
/// @retval None

static void SetSysClockToXX(void)
{
    __IO u32 temp, tn, tm;//j,
    __IO u32 StartUpCounter = 0, HSEStatus = 0;

    u8 plln, pllm;

    RCC->CR |= RCC_CR_HSION;
    while(!(RCC->CR & RCC_CR_HSIRDY));
    //PLL SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    //Enable HSE
    RCC->CR |= ((u32)RCC_CR_HSEON);

    DELAY_xUs(5);

    if(SystemCoreClock > 96000000) {
        RCC->APB1ENR |= RCC_APB1ENR_PWR;
        PWR->CR &= ~(3 << 14);
        PWR->CR |= 3 << 14;
    }
    //Wait till HSE is ready and if Time out is reached exit
    while(1) {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        if(HSEStatus != 0)
            break;
        StartUpCounter++;
        if(StartUpCounter >= (10 * HSE_STARTUP_TIMEOUT))
            return;
    }

    if ((RCC->CR & RCC_CR_HSERDY) == RESET) {
        //If HSE fails to start-up, the application will have wrong clock
        //configuration. User can add here some code to deal with this error
        HSEStatus = (u32)0x00;
        return;
    }

    HSEStatus = (u32)0x01;
    DELAY_xUs(5);

    SystemCoreClock         = SYSCLK_FREQ_XXMHz;
    //Enable Prefetch Buffer
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    //Flash 0 wait state ,bit0~2
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    temp = (SystemCoreClock - 1) / 24000000;
    FLASH->ACR |= (temp & FLASH_ACR_LATENCY);
    RCC->CFGR &= (~RCC_CFGR_HPRE) & ( ~RCC_CFGR_PPRE1) & (~RCC_CFGR_PPRE2);

    //HCLK = AHB = FCLK = SYSCLK divided by 4
    RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV4;

    //PCLK2 = APB2 = HCLK divided by 1, APB2 is high APB CLK
    RCC->CFGR |= (u32)RCC_CFGR_PPRE2_DIV1;

    if(SystemCoreClock > 72000000) {
        //PCLK1 = APB1 = HCLK divided by 4, APB1 is low APB CLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV4;
    }
    else if(SystemCoreClock > 36000000) {
        //PCLK1 = APB1 = HCLK divided by 2, APB1 is low APB CLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV2;
    }

    AutoCalPllFactor(HSE_VALUE, SystemCoreClock, &plln, &pllm);

    RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
    RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

    tm = (((u32)pllm) & 0x07);
    tn = (((u32)plln) & 0x7F);

    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
    RCC->PLLCFGR |= ((tn << RCC_PLLCFGR_PLL_DN_Pos) | (tm << RCC_PLLCFGR_PLL_DP_Pos));
    //Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    //Wait till PLL is ready
    while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        __ASM ("nop") ;//__NOP();
    }
    //Select PLL as system clock source
    RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
    RCC->CFGR |= (u32)RCC_CFGR_SW_PLL;

    //Wait till PLL is used as system clock source
    while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)RCC_CFGR_SWS_PLL) {
        __ASM ("nop") ;//__NOP();
    }

    DELAY_xUs(1);
    // set HCLK = AHB = FCLK = SYSCLK divided by 2
    RCC->CFGR &= (~(RCC_CFGR_PPRE_0));
    DELAY_xUs(1);

    // set HCLK = AHB = FCLK = SYSCLK divided by 1
    RCC->CFGR &= (~(RCC_CFGR_PPRE_3));

    DELAY_xUs(1);

}
#elif defined SYSCLK_HSI_24MHz
void SetSysClockTo24_HSI(void)
{
    u8 temp = 0;

    RCC->CR |= RCC_CR_HSION;

    while(!(RCC->CR & RCC_CR_HSIRDY));
    FLASH->ACR = FLASH_ACR_PRFTBE;

    RCC->CFGR = RCC_CFGR_PPRE1_2;
    // PLL configuration:  = (HSI = 8M ) * (2+1)/(0+1) = 24 MHz
    RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
    RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
    RCC->PLLCFGR |= ((0 << RCC_PLLCFGR_PLL_DN_Pos) | (2 << RCC_PLLCFGR_PLL_DP_Pos));


    RCC->CR |= RCC_CR_PLLON;

    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= ~RCC_CFGR_SW;

    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while(temp != 0x02) {
        temp = RCC->CFGR >> 2;
        temp &= 0x03;
    }
}

#elif defined SYSCLK_HSI_36MHz
void SetSysClockTo36_HSI(void)
{
    u8 temp = 0;

    RCC->CR |= RCC_CR_HSION;

    while(!(RCC->CR & RCC_CR_HSIRDY));
    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_PRFTBE;
    RCC->CFGR = RCC_CFGR_PPRE1_2;
    // PLL configuration:  = (HSI = 8M ) * (8+1)/(1+1) = 36 MHz
    RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
    RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
    RCC->PLLCFGR |= ((1 << RCC_PLLCFGR_PLL_DN_Pos) | (8 << RCC_PLLCFGR_PLL_DP_Pos));

    RCC->CR |= RCC_CR_PLLON;

    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= ~ RCC_CFGR_SW;

    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while(temp != 0x02) {
        temp = RCC->CFGR >> 2;
        temp &= 0x03;
    }
}

#elif defined SYSCLK_HSI_48MHz
void SetSysClockTo48_HSI(void)
{
    u8 temp = 0;

    RCC->CR |= RCC_CR_HSION;

    while(!(RCC->CR & RCC_CR_HSIRDY));
    FLASH->ACR = FLASH_ACR_LATENCY_1 | FLASH_ACR_PRFTBE;
    RCC->CFGR = RCC_CFGR_PPRE1_2;





    // PLL configuration:  = (HSI = 8M ) * (5+1)/(0+1) = 36 MHz
    RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
    RCC->PLLCFGR |= (u32 ) RCC_PLLCFGR_PLLSRC  ;

    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
    RCC->PLLCFGR |= ((0 << RCC_PLLCFGR_PLL_DN_Pos) | (5 << RCC_PLLCFGR_PLL_DP_Pos));

    RCC->CR |= RCC_CR_PLLON;

    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= ~RCC_CFGR_SW;

    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while(temp != 0x02) {
        temp = RCC->CFGR >> 2;
        temp &= 0x03;
    }
}
#elif defined SYSCLK_HSI_XXMHz


static void SetSysClockToXX_HSI(void)
{
    __IO u32 temp, tn, tm;
    u8 plln, pllm;

    RCC->CR |= RCC_CR_HSION;
    while(!(RCC->CR & RCC_CR_HSIRDY));

    if(SystemCoreClock > 96000000) {
        RCC->APB1ENR |= RCC_APB1ENR_PWR;
        PWR->CR &= ~(3 << 14);
        PWR->CR |= 3 << 14;
    }



    SystemCoreClock         = SYSCLK_HSI_XXMHz;
    //Enable Prefetch Buffer
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    //Flash 0 wait state ,bit0~2
    FLASH->ACR &= ~FLASH_ACR_LATENCY;

    temp = (SystemCoreClock - 1) / 24000000;

    FLASH->ACR |= (temp & FLASH_ACR_LATENCY);


    RCC->CFGR &= (~RCC_CFGR_HPRE) & ( ~RCC_CFGR_PPRE1) & (~RCC_CFGR_PPRE2);
    //HCLK = AHB = FCLK = SYSCLK divided by 4
    RCC->CFGR |= (u32)RCC_CFGR_HPRE_DIV4;

    //PCLK2 = APB2 = HCLK divided by 1, APB2 is high APB CLK
    RCC->CFGR |= (u32)RCC_CFGR_PPRE2_DIV1;

    if(SystemCoreClock > 72000000) {
        //PCLK1 = APB1 = HCLK divided by 4, APB1 is low APB CLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV4;
    }
    else if(SystemCoreClock > 36000000) {
        //PCLK1 = APB1 = HCLK divided by 2, APB1 is low APB CLK
        RCC->CFGR |= (u32)RCC_CFGR_PPRE1_DIV2;
    }



    AutoCalPllFactor(HSI_VALUE_PLL_ON, SystemCoreClock, &plln, &pllm);

    RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLXTPRE) ;
    RCC->PLLCFGR &= ~((u32 ) RCC_PLLCFGR_PLLSRC);

    tm = (((u32)pllm) & 0x07);
    tn = (((u32)plln) & 0x7F);

    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    RCC->PLLCFGR &= (u32)((~RCC_PLLCFGR_PLL_DN) & (~RCC_PLLCFGR_PLL_DP));
    RCC->PLLCFGR |= ((tn << RCC_PLLCFGR_PLL_DN_Pos) | (tm << RCC_PLLCFGR_PLL_DP_Pos));
    //Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    //Wait till PLL is ready
    while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        __ASM ("nop") ;//__NOP();
    }
    //Select PLL as system clock source
    RCC->CFGR &= (u32)((u32)~(RCC_CFGR_SW));
    RCC->CFGR |= (u32)RCC_CFGR_SW_PLL;

    //Wait till PLL is used as system clock source
    while ((RCC->CFGR & (u32)RCC_CFGR_SWS) != (u32)RCC_CFGR_SWS_PLL) {
        __ASM ("nop") ;//__NOP();
    }

    DELAY_xUs(1);
    // set HCLK = AHB = FCLK = SYSCLK divided by 2
    RCC->CFGR &= (~(RCC_CFGR_PPRE_0));
    DELAY_xUs(1);

    // set HCLK = AHB = FCLK = SYSCLK divided by 1
    RCC->CFGR &= (~(RCC_CFGR_PPRE_3));

    DELAY_xUs(1);

}

#endif



/// @}



/// @}



/// @}



