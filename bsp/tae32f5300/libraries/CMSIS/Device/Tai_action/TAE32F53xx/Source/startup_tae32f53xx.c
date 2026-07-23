/**
  ******************************************************************************
  * @file    startup_tae32f53xx.c
  * @author  MCD Application Team
  * @brief   CMSIS-Core(M) Device Startup File for a tae32f53xx(Cortex-M3) Device
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


/** @addtogroup TAE_CMSIS
  * @{
  */

/** @defgroup TAE32F53xx_Startup TAE32F53xx Startup
  * @brief    TAE32F53xx Startup
  * @{
  */


/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/** @defgroup TAE32F53xx_Startup_Private_Types TAE32F53xx Startup Private Types
  * @brief    TAE32F53xx Startup Private Types
  * @{
  */

/**
  * @brief Exception / Interrupt Handler Function Prototype
  */
typedef void(*VECTOR_TABLE_Type)(void);

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup TAE32F53xx_Startup_Private_Functions TAE32F53xx Startup Private Functions
  * @brief    TAE32F53xx Startup Private Functions
  * @{
  */

/**
  * @brief Default empty handler
  */
void __NO_RETURN Default_Handler(void);

/**
  * @brief Reset handler
  */
void __NO_RETURN Reset_Handler(void);

/**
  * @brief Enter PreMain (C library entry point)
  */
void __NO_RETURN __PROGRAM_START(void);

/**
  * @brief Cortex-M3 core exceptions handlers
  */
__WEAK_ALIAS_FUNC(NMI_Handler,           Default_Handler)
__WEAK_ALIAS_FUNC(HardFault_Handler,     Default_Handler)
__WEAK_ALIAS_FUNC(MemManage_Handler,     Default_Handler)
__WEAK_ALIAS_FUNC(BusFault_Handler,      Default_Handler)
__WEAK_ALIAS_FUNC(UsageFault_Handler,    Default_Handler)
__WEAK_ALIAS_FUNC(SVC_Handler,           Default_Handler)
__WEAK_ALIAS_FUNC(DebugMon_Handler,      Default_Handler)
__WEAK_ALIAS_FUNC(PendSV_Handler,        Default_Handler)
__WEAK_ALIAS_FUNC(SysTick_Handler,       Default_Handler)

/**
  * @brief Peripherals interrupt handlers
  */
__WEAK_ALIAS_FUNC(I2C0_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(I2C1_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(UART0_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(UART1_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(TMR0_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR1_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR2_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR3_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(LVD_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(TMR4_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR5_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR6_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR7_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(IWDG_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(WWDG_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(IIR0_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(IIR1_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(IIR2_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(IIR3_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(IIR4_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(ECU_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(DMA_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(CAN_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(GPIOA_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(GPIOB_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(GPIOC_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(GPIOD_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(FLASH_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(DFLASH_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_MSTR_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV0_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV1_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV2_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV3_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV4_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV5_IRQHandler, Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_FLT_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_NORM_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_HALF_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_FULL_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_SAMP_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_NORM_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_HALF_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_FULL_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_SAMP_IRQHandler,  Default_Handler)
__WEAK_ALIAS_FUNC(DAC_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(CMP_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(USB_STA_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(USB_DET_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(USB_LPM_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(USB_EP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(DALI_IRQHandler,       Default_Handler)

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup TAE32F53xx_Startup_Private_Variables TAE32F53xx Startup Private Variables
  * @brief    TAE32F53xx Startup Private Variables
  * @{
  */

/**
  * @brief Stack pointer statement
  */
extern uint32_t __INITIAL_SP;


#if defined (__GNUC__)          /*!< GCC Compiler */
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#endif

/**
  * @brief TAE32F53xx Vector Table Definition
  */
const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {

    (VECTOR_TABLE_Type) &__INITIAL_SP,  /*!<     Initial Stack Pointer          */

    /* Processor Exceptions */
    Reset_Handler,                      /*!<     Reset Handler                  */
    NMI_Handler,                        /*!< -14 NMI Handler                    */
    HardFault_Handler,                  /*!< -13 Hard Fault Handler             */
    MemManage_Handler,                  /*!< -12 MPU Fault Handler              */
    BusFault_Handler,                   /*!< -11 Bus Fault Handler              */
    UsageFault_Handler,                 /*!< -10 Usage Fault Handler            */
    0,                                  /*!<     Reserved                       */
    0,                                  /*!<     Reserved                       */
    0,                                  /*!<     Reserved                       */
    0,                                  /*!<     Reserved                       */
    SVC_Handler,                        /*!<  -5 SVCall Handler                 */
    DebugMon_Handler,                   /*!<  -4 Debug Monitor Handler          */
    0,                                  /*!<     Reserved                       */
    PendSV_Handler,                     /*!<  -2 PendSV Handler                 */
    SysTick_Handler,                    /*!<  -1 SysTick Handler                */

    /* Processor Interrupt */
    I2C0_IRQHandler,                    /*!<   0 I2C0 Interrupt Handler         */
    I2C1_IRQHandler,                    /*!<   1 I2C1 Interrupt Handler         */
    UART0_IRQHandler,                   /*!<   2 UART0 Interrupt Handler        */
    UART1_IRQHandler,                   /*!<   3 UART1 Interrupt Handler        */
    TMR0_IRQHandler,                    /*!<   4 TIMER0 Interrupt Handler       */
    TMR1_IRQHandler,                    /*!<   5 TIMER1 Interrupt Handler       */
    TMR2_IRQHandler,                    /*!<   6 TIMER2 Interrupt Handler       */
    TMR3_IRQHandler,                    /*!<   7 TIMER3 Interrupt Handler       */
    LVD_IRQHandler,                     /*!<   8 LVD Interrupt Handler          */
    TMR4_IRQHandler,                    /*!<   9 TIMER4 Interrupt Handler       */
    TMR5_IRQHandler,                    /*!<  10 TIMER5 Interrupt Handler       */
    TMR6_IRQHandler,                    /*!<  11 TIMER6 Interrupt Handler       */
    TMR7_IRQHandler,                    /*!<  12 TIMER7 Interrupt Handler       */
    IWDG_IRQHandler,                    /*!<  13 IWDG Interrupt Handler         */
    WWDG_IRQHandler,                    /*!<  14 WWDG Interrupt Handler         */
    IIR0_IRQHandler,                    /*!<  15 IIR0 Interrupt Handler         */
    IIR1_IRQHandler,                    /*!<  16 IIR1 Interrupt Handler         */
    IIR2_IRQHandler,                    /*!<  17 IIR2 Interrupt Handler         */
    IIR3_IRQHandler,                    /*!<  18 IIR3 Interrupt Handler         */
    IIR4_IRQHandler,                    /*!<  19 IIR4 Interrupt Handler         */
    ECU_IRQHandler,                     /*!<  20 ECU Interrupt Handler          */
    DMA_IRQHandler,                     /*!<  21 DMA Interrupt Handler          */
    CAN_IRQHandler,                     /*!<  22 CAN Interrupt Handler          */
    GPIOA_IRQHandler,                   /*!<  23 GPIOA Interrupt Handler        */
    GPIOB_IRQHandler,                   /*!<  24 GPIOB Interrupt Handler        */
    GPIOC_IRQHandler,                   /*!<  25 GPIOC Interrupt Handler        */
    GPIOD_IRQHandler,                   /*!<  26 GPIOD Interrupt Handler        */
    FLASH_IRQHandler,                   /*!<  27 FLASH Interrupt Handler        */
    DFLASH_IRQHandler,                  /*!<  28 DFLASH Interrupt Handler       */
    HRPWM_MSTR_IRQHandler,              /*!<  29 HRPWM Master Interrupt Handler */
    HRPWM_SLV0_IRQHandler,              /*!<  30 HRPWM Slave0 Interrupt Handler */
    HRPWM_SLV1_IRQHandler,              /*!<  31 HRPWM Slave1 Interrupt Handler */
    HRPWM_SLV2_IRQHandler,              /*!<  32 HRPWM Slave2 Interrupt Handler */
    HRPWM_SLV3_IRQHandler,              /*!<  33 HRPWM Slave3 Interrupt Handler */
    HRPWM_SLV4_IRQHandler,              /*!<  34 HRPWM Slave4 Interrupt Handler */
    HRPWM_SLV5_IRQHandler,              /*!<  35 HRPWM Slave5 Interrupt Handler */
    HRPWM_FLT_IRQHandler,               /*!<  36 HRPWM Fault Interrupt Handler  */
    ADC0_NORM_IRQHandler,               /*!<  37 ADC0 Normal Interrupt Handler  */
    ADC0_HALF_IRQHandler,               /*!<  38 ADC0 Half Interrupt Handler    */
    ADC0_FULL_IRQHandler,               /*!<  39 ADC0 Full Interrupt Handler    */
    ADC0_SAMP_IRQHandler,               /*!<  40 ADC0 Sample Interrupt Handler  */
    ADC1_NORM_IRQHandler,               /*!<  41 ADC1 Normal Interrupt Handler  */
    ADC1_HALF_IRQHandler,               /*!<  42 ADC1 Half Interrupt Handler    */
    ADC1_FULL_IRQHandler,               /*!<  43 ADC1 Full Interrupt Handler    */
    ADC1_SAMP_IRQHandler,               /*!<  44 ADC1 Sample Interrupt Handler  */
    DAC_IRQHandler,                     /*!<  45 DAC Interrupt Handler          */
    CMP_IRQHandler,                     /*!<  46 CMP Interrupt Handler          */
    USB_STA_IRQHandler,                 /*!<  47 USB Status Interrupt Handler   */
    USB_DET_IRQHandler,                 /*!<  48 USB Detect Interrupt Handler   */
    USB_LPM_IRQHandler,                 /*!<  49 USB LPM Interrupt Handler      */
    USB_EP_IRQHandler,                  /*!<  50 USB Endpoint Interrupt Handler */
    DALI_IRQHandler,                    /*!<  51 DALI Interrupt Handler         */
};

#if defined (__GNUC__)      /*!< GCC Compiler */
    #pragma GCC diagnostic pop
#endif

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup TAE32F53xx_Startup_Private_Functions TAE32F53xx Startup Private Functions
  * @brief    TAE32F53xx Startup Private Functions
  * @{
  */

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/**
  * @brief  Reset Handler called on controller reset
  * @param  None
  * @return None
  */
void Reset_Handler(void)
{
    SystemInit();           /* CMSIS System Initialization              */
    __PROGRAM_START();      /* Enter PreMain (C library entry point)    */
}

/**
  * @brief  Default Handler for Exceptions / Interrupts
  * @param  None
  * @return None
  */
void Default_Handler(void)
{
    while (1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
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

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

