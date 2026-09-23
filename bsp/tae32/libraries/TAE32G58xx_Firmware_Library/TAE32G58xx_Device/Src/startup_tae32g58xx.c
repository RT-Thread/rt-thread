/**
  ******************************************************************************
  * @file    startup_tae32g58xx.c
  * @author  MCD Application Team
  * @brief   CMSIS-Core(M) Device Startup File for a tae32g58xx(Cortex-M4) Device
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
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE_CMSIS
  * @{
  */

/** @defgroup TAE32G58xx_Startup TAE32G58xx Startup
  * @brief    TAE32G58xx Startup
  * @{
  */


/* Private Constants ---------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup TAE32G58xx_Startup_Private_Types TAE32G58xx Startup Private Types
  * @brief    TAE32G58xx Startup Private Types
  * @{
  */

/**
  * @brief Exception / Interrupt Handler Function Prototype
  */
typedef void (*VECTOR_TABLE_Type)(void);

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup TAE32G58xx_Startup_Private_Functions TAE32G58xx Startup Private Functions
  * @brief    TAE32G58xx Startup Private Functions
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

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	//...
#elif defined (__GNUC__) /*!< GCC Compiler */
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmissing-attributes"
#endif

/**
  * @brief Cortex-M4 core exceptions handlers
  */
__WEAK_ALIAS_FUNC(NMI_Handler,              Default_Handler)
__WEAK_ALIAS_FUNC(HardFault_Handler,        Default_Handler)
__WEAK_ALIAS_FUNC(MemManage_Handler,        Default_Handler)
__WEAK_ALIAS_FUNC(BusFault_Handler,         Default_Handler)
__WEAK_ALIAS_FUNC(UsageFault_Handler,       Default_Handler)
__WEAK_ALIAS_FUNC(SVC_Handler,              Default_Handler)
__WEAK_ALIAS_FUNC(DebugMon_Handler,         Default_Handler)
__WEAK_ALIAS_FUNC(PendSV_Handler,           Default_Handler)
__WEAK_ALIAS_FUNC(SysTick_Handler,          Default_Handler)

/**
  * @brief Peripherals interrupt handlers
  */
__WEAK_ALIAS_FUNC(I2C0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(I2C1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(I2C2_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(UART0_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART1_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART2_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART3_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(UART4_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(SPI0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(SPI1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(CAN0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(CAN1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(PDM0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(PDM1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(PDM2_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(PDM3_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(QEI0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(QEI1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(QEI2_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH0_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH1_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH2_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH3_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH4_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(DMA_CH5_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR7_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR8_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR0_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR1_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR2_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR3_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR4_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(TMR9_BRK_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(TMR9_UPD_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(TMR9_TRG_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(TMR9_CC_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(TMR10_BRK_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(TMR10_UPD_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(TMR10_TRG_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(TMR10_CC_IRQHandler,      Default_Handler)
__WEAK_ALIAS_FUNC(IWDG_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(WWDG_IRQHandler,          Default_Handler)
__WEAK_ALIAS_FUNC(GPIOA_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOB_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOC_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOD_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOE_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(GPIOF_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(EFLASH_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(IIR_IRQHandler,           Default_Handler)
__WEAK_ALIAS_FUNC(CORDIC_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(CMPG0_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(CMPG1_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(CMPG2_IRQHandler,         Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_MST_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV0_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV1_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV2_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV3_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV4_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV5_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV6_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_SLV7_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(HRPWM_COMM_IRQHandler,    Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_NORM_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_SAMP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_HALF_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC0_FULL_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_NORM_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_SAMP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_HALF_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC1_FULL_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC2_NORM_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC2_SAMP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC2_HALF_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC2_FULL_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC3_NORM_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC3_SAMP_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC3_HALF_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(ADC3_FULL_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(PMU_IRQHandler,           Default_Handler)
__WEAK_ALIAS_FUNC(USB_PWR_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(USB_DET_IRQHandler,       Default_Handler)
__WEAK_ALIAS_FUNC(USB_EP_IRQHandler,        Default_Handler)
__WEAK_ALIAS_FUNC(XIF_IRQHandler,           Default_Handler)
__WEAK_ALIAS_FUNC(CAN0_INT1_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(CAN1_INT1_IRQHandler,     Default_Handler)
__WEAK_ALIAS_FUNC(TMR6_IRQHandler,          Default_Handler)

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	//...
#elif defined (__GNUC__) /*!< GCC Compiler */
    #pragma GCC diagnostic pop
#endif

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup TAE32G58xx_Startup_Private_Variables TAE32G58xx Startup Private Variables
  * @brief    TAE32G58xx Startup Private Variables
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
  * @brief TAE32G58xx Vector Table Definition
  */
const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {

    (VECTOR_TABLE_Type) &__INITIAL_SP,  /*!<     Initial Stack Pointer          */

    /* Processor Exceptions */
    Reset_Handler,                      /*!< -15 Reset Handler                  */
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
    I2C0_IRQHandler,                    /*!<  0  I2C0 Interrupt Handler         */
    I2C1_IRQHandler,                    /*!<  1  I2C1 Interrupt Handler         */
    I2C2_IRQHandler,                    /*!<  2  I2C2 Interrupt Handler         */
    UART0_IRQHandler,                   /*!<  3  UART0 Interrupt Handler        */
    UART1_IRQHandler,                   /*!<  4  UART1 Interrupt Handler        */
    UART2_IRQHandler,                   /*!<  5  UART2 Interrupt Handler        */
    UART3_IRQHandler,                   /*!<  6  UART3 Interrupt Handler        */
    UART4_IRQHandler,                   /*!<  7  UART4 Interrupt Handler        */
    SPI0_IRQHandler,                    /*!<  8  SPI0 Interrupt Handler         */
    SPI1_IRQHandler,                    /*!<  9  SPI1 Interrupt Handler         */
    CAN0_IRQHandler,                    /*!< 10  CAN0 Interrupt Handler         */
    CAN1_IRQHandler,                    /*!< 11  CAN1 Interrupt Handler         */
    PDM0_IRQHandler,                    /*!< 12  PDM0 Interrupt Handler         */
    PDM1_IRQHandler,                    /*!< 13  PDM1 Interrupt Handler         */
    PDM2_IRQHandler,                    /*!< 14  PDM2 Interrupt Handler         */
    PDM3_IRQHandler,                    /*!< 15  PDM3 Interrupt Handler         */
    QEI0_IRQHandler,                    /*!< 16  QEI0 Interrupt Handler         */
    QEI1_IRQHandler,                    /*!< 17  QEI1 Interrupt Handler         */
    QEI2_IRQHandler,                    /*!< 18  QEI2 Interrupt Handler         */
    DMA_CH0_IRQHandler,                 /*!< 19  DMA_CH0 Interrupt Handler      */
    DMA_CH1_IRQHandler,                 /*!< 20  DMA_CH1 Interrupt Handler      */
    DMA_CH2_IRQHandler,                 /*!< 21  DMA_CH2 Interrupt Handler      */
    DMA_CH3_IRQHandler,                 /*!< 22  DMA_CH3 Interrupt Handler      */
    DMA_CH4_IRQHandler,                 /*!< 23  DMA_CH4 Interrupt Handler      */
    DMA_CH5_IRQHandler,                 /*!< 24  DMA_CH5 Interrupt Handler      */
    TMR7_IRQHandler,                    /*!< 25  TMR7 Interrupt Handler         */
    TMR8_IRQHandler,                    /*!< 26  TMR8 Interrupt Handler         */
    TMR0_IRQHandler,                    /*!< 27  TMR0 Interrupt Handler         */
    TMR1_IRQHandler,                    /*!< 28  TMR1 Interrupt Handler         */
    TMR2_IRQHandler,                    /*!< 29  TMR2 Interrupt Handler         */
    TMR3_IRQHandler,                    /*!< 30  TMR3 Interrupt Handler         */
    TMR4_IRQHandler,                    /*!< 31  TMR4 Interrupt Handler         */
    TMR9_BRK_IRQHandler,                /*!< 32  TMR9 Break Interrupt Handler   */
    TMR9_UPD_IRQHandler,                /*!< 33  TMR9 Update Interrupt Handler  */
    TMR9_TRG_IRQHandler,                /*!< 34  TMR9 Trigger Interrupt Handler */
    TMR9_CC_IRQHandler,                 /*!< 35  TMR9 Cap/Cmp Interrupt Handler */
    TMR10_BRK_IRQHandler,               /*!< 36  TMR10 Break Interrupt Handler  */
    TMR10_UPD_IRQHandler,               /*!< 37  TMR10 Update Interrupt Handler */
    TMR10_TRG_IRQHandler,               /*!< 38  TMR10 Trigger Interrupt Handler*/
    TMR10_CC_IRQHandler,                /*!< 39  TMR10 Cap/Cmp Interrupt Handler*/
    IWDG_IRQHandler,                    /*!< 40  IWDG Interrupt Handler         */
    WWDG_IRQHandler,                    /*!< 41  WWDG Interrupt Handler         */
    GPIOA_IRQHandler,                   /*!< 42  GPIOA Interrupt Handler        */
    GPIOB_IRQHandler,                   /*!< 43  GPIOB Interrupt Handler        */
    GPIOC_IRQHandler,                   /*!< 44  GPIOC Interrupt Handler        */
    GPIOD_IRQHandler,                   /*!< 45  GPIOD Interrupt Handler        */
    GPIOE_IRQHandler,                   /*!< 46  GPIOE Interrupt Handler        */
    GPIOF_IRQHandler,                   /*!< 47  GPIOF Interrupt Handler        */
    EFLASH_IRQHandler,                  /*!< 48  EFLASH Interrupt Handler       */
    IIR_IRQHandler,                     /*!< 49  IIR Interrupt Handler          */
    CORDIC_IRQHandler,                  /*!< 50  CORDIC Interrupt Handler       */
    CMPG0_IRQHandler,                   /*!< 51  CMPG0 Interrupt Handler        */
    CMPG1_IRQHandler,                   /*!< 52  CMPG1 Interrupt Handler        */
    CMPG2_IRQHandler,                   /*!< 53  CMPG2 Interrupt Handler        */
    HRPWM_MST_IRQHandler,               /*!< 54  HRPWM_MST Interrupt Handler    */
    HRPWM_SLV0_IRQHandler,              /*!< 55  HRPWM_SLV0 Interrupt Handler   */
    HRPWM_SLV1_IRQHandler,              /*!< 56  HRPWM_SLV1 Interrupt Handler   */
    HRPWM_SLV2_IRQHandler,              /*!< 57  HRPWM_SLV2 Interrupt Handler   */
    HRPWM_SLV3_IRQHandler,              /*!< 58  HRPWM_SLV3 Interrupt Handler   */
    HRPWM_SLV4_IRQHandler,              /*!< 59  HRPWM_SLV4 Interrupt Handler   */
    HRPWM_SLV5_IRQHandler,              /*!< 60  HRPWM_SLV5 Interrupt Handler   */
    HRPWM_SLV6_IRQHandler,              /*!< 61  HRPWM_SLV6 Interrupt Handler   */
    HRPWM_SLV7_IRQHandler,              /*!< 62  HRPWM_SLV7 Interrupt Handler   */
    HRPWM_COMM_IRQHandler,              /*!< 63  HRPWM_COMM Interrupt Handler   */
    ADC0_NORM_IRQHandler,               /*!< 64  ADC0_NORM Interrupt Handler    */
    ADC0_SAMP_IRQHandler,               /*!< 65  ADC0_SAMP Interrupt Handler    */
    ADC0_HALF_IRQHandler,               /*!< 66  ADC0_HALF Interrupt Handler    */
    ADC0_FULL_IRQHandler,               /*!< 67  ADC0_FULL Interrupt Handler    */
    ADC1_NORM_IRQHandler,               /*!< 68  ADC1_NORM Interrupt Handler    */
    ADC1_SAMP_IRQHandler,               /*!< 69  ADC1_SAMP Interrupt Handler    */
    ADC1_HALF_IRQHandler,               /*!< 70  ADC1_HALF Interrupt Handler    */
    ADC1_FULL_IRQHandler,               /*!< 71  ADC1_FULL Interrupt Handler    */
    ADC2_NORM_IRQHandler,               /*!< 72  ADC2_NORM Interrupt Handler    */
    ADC2_SAMP_IRQHandler,               /*!< 73  ADC2_SAMP Interrupt Handler    */
    ADC2_HALF_IRQHandler,               /*!< 74  ADC2_HALF Interrupt Handler    */
    ADC2_FULL_IRQHandler,               /*!< 75  ADC2_FULL Interrupt Handler    */
    ADC3_NORM_IRQHandler,               /*!< 76  ADC3_NORM Interrupt Handler    */
    ADC3_SAMP_IRQHandler,               /*!< 77  ADC3_SAMP Interrupt Handler    */
    ADC3_HALF_IRQHandler,               /*!< 78  ADC3_HALF Interrupt Handler    */
    ADC3_FULL_IRQHandler,               /*!< 79  ADC3_FULL Interrupt Handler    */
    PMU_IRQHandler,                     /*!< 80  PMU Interrupt Handler          */
    USB_PWR_IRQHandler,                 /*!< 81  USB_POWER Interrupt Handler    */
    USB_DET_IRQHandler,                 /*!< 82  USB_DET Interrupt Handler      */
    USB_EP_IRQHandler,                  /*!< 83  USB_EP Interrupt Handler       */
    XIF_IRQHandler,                     /*!< 84  XIF Interrupt Handler          */
    CAN0_INT1_IRQHandler,               /*!< 85  CAN0 Interrupt Line1  Handler  */
    CAN1_INT1_IRQHandler,               /*!< 86  CAN1 Interrupt Line1  Handler  */
    TMR6_IRQHandler,                    /*!< 87  TMR6 Interrupt Handler         */
};

#if defined (__GNUC__)      /*!< GCC Compiler */
#pragma GCC diagnostic pop

void _start(void)
{
    int main(void);
    main();

    while (1) {
    }
}
#endif

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/** @defgroup TAE32G58xx_Startup_Private_Functions TAE32G58xx Startup Private Functions
  * @brief    TAE32G58xx Startup Private Functions
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

