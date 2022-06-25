# /* Peripheral and SRAM base address in the alias region */
set PERIPH_BB_BASE        0x42000000
set SRAM_BB_BASE          0x22000000

# /*Peripheral and SRAM base address in the bit-band region */
set SRAM_BASE             0x20000000
set PERIPH_BASE           0x40000000

# /*FSMC registers base address */
set FSMC_R_BASE           0xA0000000

# /*Peripheral memory map */
set APB1PERIPH_BASE       [set PERIPH_BASE]
set APB2PERIPH_BASE       [expr $PERIPH_BASE + 0x10000]
set AHBPERIPH_BASE        [expr $PERIPH_BASE + 0x20000]

set TIM2_BASE             [expr $APB1PERIPH_BASE + 0x0000]
set TIM3_BASE             [expr $APB1PERIPH_BASE + 0x0400]
set TIM4_BASE             [expr $APB1PERIPH_BASE + 0x0800]
set TIM5_BASE             [expr $APB1PERIPH_BASE + 0x0C00]
set TIM6_BASE             [expr $APB1PERIPH_BASE + 0x1000]
set TIM7_BASE             [expr $APB1PERIPH_BASE + 0x1400]
set RTC_BASE              [expr $APB1PERIPH_BASE + 0x2800]
set WWDG_BASE             [expr $APB1PERIPH_BASE + 0x2C00]
set IWDG_BASE             [expr $APB1PERIPH_BASE + 0x3000]
set SPI2_BASE             [expr $APB1PERIPH_BASE + 0x3800]
set SPI3_BASE             [expr $APB1PERIPH_BASE + 0x3C00]
set USART2_BASE           [expr $APB1PERIPH_BASE + 0x4400]
set USART3_BASE           [expr $APB1PERIPH_BASE + 0x4800]
set UART4_BASE            [expr $APB1PERIPH_BASE + 0x4C00]
set UART5_BASE            [expr $APB1PERIPH_BASE + 0x5000]
set I2C1_BASE             [expr $APB1PERIPH_BASE + 0x5400]
set I2C2_BASE             [expr $APB1PERIPH_BASE + 0x5800]
set CAN_BASE              [expr $APB1PERIPH_BASE + 0x6400]
set BKP_BASE              [expr $APB1PERIPH_BASE + 0x6C00]
set PWR_BASE              [expr $APB1PERIPH_BASE + 0x7000]
set DAC_BASE              [expr $APB1PERIPH_BASE + 0x7400]

set AFIO_BASE             [expr $APB2PERIPH_BASE + 0x0000]
set EXTI_BASE             [expr $APB2PERIPH_BASE + 0x0400]
set GPIOA_BASE            [expr $APB2PERIPH_BASE + 0x0800]
set GPIOB_BASE            [expr $APB2PERIPH_BASE + 0x0C00]
set GPIOC_BASE            [expr $APB2PERIPH_BASE + 0x1000]
set GPIOD_BASE            [expr $APB2PERIPH_BASE + 0x1400]
set GPIOE_BASE            [expr $APB2PERIPH_BASE + 0x1800]
set GPIOF_BASE            [expr $APB2PERIPH_BASE + 0x1C00]
set GPIOG_BASE            [expr $APB2PERIPH_BASE + 0x2000]
set ADC1_BASE             [expr $APB2PERIPH_BASE + 0x2400]
set ADC2_BASE             [expr $APB2PERIPH_BASE + 0x2800]
set TIM1_BASE             [expr $APB2PERIPH_BASE + 0x2C00]
set SPI1_BASE             [expr $APB2PERIPH_BASE + 0x3000]
set TIM8_BASE             [expr $APB2PERIPH_BASE + 0x3400]
set USART1_BASE           [expr $APB2PERIPH_BASE + 0x3800]
set ADC3_BASE             [expr $APB2PERIPH_BASE + 0x3C00]

set SDIO_BASE             [expr $PERIPH_BASE + 0x18000]

set DMA1_BASE             [expr $AHBPERIPH_BASE + 0x0000]
set DMA1_Channel1_BASE    [expr $AHBPERIPH_BASE + 0x0008]
set DMA1_Channel2_BASE    [expr $AHBPERIPH_BASE + 0x001C]
set DMA1_Channel3_BASE    [expr $AHBPERIPH_BASE + 0x0030]
set DMA1_Channel4_BASE    [expr $AHBPERIPH_BASE + 0x0044]
set DMA1_Channel5_BASE    [expr $AHBPERIPH_BASE + 0x0058]
set DMA1_Channel6_BASE    [expr $AHBPERIPH_BASE + 0x006C]
set DMA1_Channel7_BASE    [expr $AHBPERIPH_BASE + 0x0080]
set DMA2_BASE             [expr $AHBPERIPH_BASE + 0x0400]
set DMA2_Channel1_BASE    [expr $AHBPERIPH_BASE + 0x0408]
set DMA2_Channel2_BASE    [expr $AHBPERIPH_BASE + 0x041C]
set DMA2_Channel3_BASE    [expr $AHBPERIPH_BASE + 0x0430]
set DMA2_Channel4_BASE    [expr $AHBPERIPH_BASE + 0x0444]
set DMA2_Channel5_BASE    [expr $AHBPERIPH_BASE + 0x0458]
set RCC_BASE              [expr $AHBPERIPH_BASE + 0x1000]
set CRC_BASE              [expr $AHBPERIPH_BASE + 0x3000]

# /*Flash registers base address */
set FLASH_R_BASE          [expr $AHBPERIPH_BASE + 0x2000]
# /*Flash Option Bytes base address */
set OB_BASE               0x1FFFF800

# /*FSMC Bankx registers base address */
set FSMC_Bank1_R_BASE     [expr $FSMC_R_BASE + 0x0000]
set FSMC_Bank1E_R_BASE    [expr $FSMC_R_BASE + 0x0104]
set FSMC_Bank2_R_BASE     [expr $FSMC_R_BASE + 0x0060]
set FSMC_Bank3_R_BASE     [expr $FSMC_R_BASE + 0x0080]
set FSMC_Bank4_R_BASE     [expr $FSMC_R_BASE + 0x00A0]

# /*Debug MCU registers base address */
set DBGMCU_BASE           0xE0042000

# /*System Control Space memory map */
set SCS_BASE              0xE000E000

set SysTick_BASE          [expr $SCS_BASE + 0x0010]
set NVIC_BASE             [expr $SCS_BASE + 0x0100]
set SCB_BASE              [expr $SCS_BASE + 0x0D00]
