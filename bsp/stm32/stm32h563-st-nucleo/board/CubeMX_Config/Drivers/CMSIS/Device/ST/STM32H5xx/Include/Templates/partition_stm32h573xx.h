/**
  ******************************************************************************
  * @file    partition_stm32h573xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32H573xx Device Header File for Initial Setup for Secure /
  *          Non-Secure Zones for ARMCM33 based on CMSIS CORE partition_ARMCM33.h
  *          Template.
  *
  *          This file contains:
  *           - Initialize Security Attribution Unit (SAU) CTRL register
  *           - Setup behavior of Sleep and Exception Handling
  *           - Setup behavior of Floating Point Unit
  *           - Setup Interrupt Target
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
 */

#ifndef PARTITION_STM32H573XX_H
#define PARTITION_STM32H573XX_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/

/*
// <e>Initialize Security Attribution Unit (SAU) CTRL register
*/
#define SAU_INIT_CTRL          1

/*
//   <q> Enable SAU
//   <i> Value for SAU->CTRL register bit ENABLE
*/
#define SAU_INIT_CTRL_ENABLE   0

/*
//   <o> When SAU is disabled
//     <0=> All Memory is Secure
//     <1=> All Memory is Non-Secure
//   <i> Value for SAU->CTRL register bit ALLNS
//   <i> When all Memory is Non-Secure (ALLNS is 1), IDAU can override memory map configuration.
*/
#define SAU_INIT_CTRL_ALLNS    1

/*
// </e>
*/

/*
// <h>Initialize Security Attribution Unit (SAU) Address Regions
// <i>SAU configuration specifies regions to be one of:
// <i> - Secure and Non-Secure Callable
// <i> - Non-Secure
// <i>Note: All memory regions not configured by SAU are Secure
*/
#define SAU_REGIONS_MAX   8                 /* Max. number of SAU regions */

/*
//   <e>Initialize SAU Region 0
//   <i> Setup SAU Region 0 memory attributes
*/
#define SAU_INIT_REGION0    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0     0x0C0FE000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x0C0FFFFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC0       1
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 1
//   <i> Setup SAU Region 1 memory attributes
*/
#define SAU_INIT_REGION1    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START1     0x08100000      /* start address of SAU region 1 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x081FFFFF      /* end address of SAU region 1 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC1       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 2
//   <i> Setup SAU Region 2 memory attributes
*/
#define SAU_INIT_REGION2    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START2     0x20050000      /* start address of SAU region 2 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0x2009FFFF      /* end address of SAU region 2 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC2       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 3
//   <i> Setup SAU Region 3 memory attributes
*/
#define SAU_INIT_REGION3    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START3     0x40000000      /* start address of SAU region 3 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0x4FFFFFFF      /* end address of SAU region 3 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC3       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 4
//   <i> Setup SAU Region 4 memory attributes
*/
#define SAU_INIT_REGION4    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START4     0x60000000      /* start address of SAU region 4 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END4       0x9FFFFFFF      /* end address of SAU region 4 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC4       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 5
//   <i> Setup SAU Region 5 memory attributes
*/
#define SAU_INIT_REGION5    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START5     0x0BF90000      /* start address of SAU region 5 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END5       0x0BFA8FFF      /* end address of SAU region 5 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC5       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 6
//   <i> Setup SAU Region 6 memory attributes
*/
#define SAU_INIT_REGION6    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START6     0x00000000      /* start address of SAU region 6 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END6       0x00000000      /* end address of SAU region 6 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC6       0
/*
//   </e>
*/

/*
//   <e>Initialize SAU Region 7
//   <i> Setup SAU Region 7 memory attributes
*/
#define SAU_INIT_REGION7    0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START7     0x00000000      /* start address of SAU region 7 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END7       0x00000000      /* end address of SAU region 7 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC7       0
/*
//   </e>
*/

/*
// </h>
*/

/*
// <e>Setup behaviour of Sleep and Exception Handling
*/
#define SCB_CSR_AIRCR_INIT  0

/*
//   <o> Deep Sleep can be enabled by
//     <0=>Secure and Non-Secure state
//     <1=>Secure state only
//   <i> Value for SCB->CSR register bit DEEPSLEEPS
*/
#define SCB_CSR_DEEPSLEEPS_VAL      0

/*
//   <o>System reset request accessible from
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for SCB->AIRCR register bit SYSRESETREQS
*/
#define SCB_AIRCR_SYSRESETREQS_VAL  0

/*
//   <o>Priority of Non-Secure exceptions is
//     <0=> Not altered
//     <1=> Lowered to 0x04-0x07
//   <i> Value for SCB->AIRCR register bit PRIS
*/
#define SCB_AIRCR_PRIS_VAL          0

/*
//   <o>BusFault, HardFault, and NMI target
//     <0=> Secure state
//     <1=> Non-Secure state
//   <i> Value for SCB->AIRCR register bit BFHFNMINS
*/
#define SCB_AIRCR_BFHFNMINS_VAL     0

/*
// </e>
*/

/*
// <e>Setup behaviour of Floating Point Unit
*/
#define TZ_FPU_NS_USAGE 1

/*
// <o>Floating Point Unit usage
//     <0=> Secure state only
//     <3=> Secure and Non-Secure state
//   <i> Value for SCB->NSACR register bits CP10, CP11
*/
#define SCB_NSACR_CP10_11_VAL       3

/*
// <o>Treat floating-point registers as Secure
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit TS
*/
#define FPU_FPCCR_TS_VAL            0

/*
// <o>Clear on return (CLRONRET) accessibility
//     <0=> Secure and Non-Secure state
//     <1=> Secure state only
//   <i> Value for FPU->FPCCR register bit CLRONRETS
*/
#define FPU_FPCCR_CLRONRETS_VAL     0

/*
// <o>Clear floating-point caller saved registers on exception return
//     <0=> Disabled
//     <1=> Enabled
//   <i> Value for FPU->FPCCR register bit CLRONRET
*/
#define FPU_FPCCR_CLRONRET_VAL      1

/*
// </e>
*/

/*
// <h>Setup Interrupt Target
*/

/*
//   <e>Initialize ITNS 0 (Interrupts 0..31)
*/
#define NVIC_INIT_ITNS0    1

/*
// Interrupts 0..31
//   <o.0>  WWDG_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.1>  PVD_AVD_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.2>  RTC_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.3>  RTC_S_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.4>  TAMP_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.5>  RAMCFG_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.6>  FLASH_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.7>  FLASH_S_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.8>  GTZC_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.9>  RCC_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.10> RCC_S_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.11> EXTI0_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.12> EXTI1_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.13> EXTI2_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.14> EXTI3_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.15> EXTI4_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.16> EXTI5_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.17> EXTI6_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.18> EXTI7_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.19> EXTI8_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.20> EXTI9_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.21> EXTI10_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.22> EXTI11_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.23> EXTI12_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.24> EXTI13_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.25> EXTI14_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.26> EXTI15_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.27> GPDMA1_Channel0_IRQn   <0=> Secure state <1=> Non-Secure state
//   <o.28> GPDMA1_Channel1_IRQn   <0=> Secure state <1=> Non-Secure state
//   <o.29> GPDMA1_Channel2_IRQn   <0=> Secure state <1=> Non-Secure state
//   <o.30> GPDMA1_Channel3_IRQn   <0=> Secure state <1=> Non-Secure state
//   <o.31> GPDMA1_Channel4_IRQn   <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS0_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 1 (Interrupts 32..63)
*/
#define NVIC_INIT_ITNS1    1

/*
// Interrupts 32..63
//   <o.0>  GPDMA1_Channel5_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.1>  GPDMA1_Channel6_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.2>  GPDMA1_Channel7_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.3>  IWDG_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.4>  SAES_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.5>  ADC1_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.6>  DAC1_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.7>  FDCAN1_IT0_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.8>  FDCAN1_IT1_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.9>  TIM1_BRK_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.10> TIM1_UP_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.11> TIM1_TRG_COM_IRQn     <0=> Secure state <1=> Non-Secure state
//   <o.12> TIM1_CC_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.13> TIM2_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.14> TIM3_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.15> TIM4_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.16> TIM5_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.17> TIM6_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.18> TIM7_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.19> I2C1_EV_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.20> I2C1_ER_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.21> I2C2_EV_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.22> I2C2_ER_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.23> SPI1_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.24> SPI2_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.25> SPI3_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.26> USART1_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.27> USART2_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.28> USART3_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.29> UART4_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.30> UART5_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.31> LPUART1_IRQn          <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS1_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 2 (Interrupts 64..95)
*/
#define NVIC_INIT_ITNS2    1

/*
// Interrupts 64..95
//   <o.0>  LPTIM1_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.1>  TIM8_BRK_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.2>  TIM8_UP_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.3>  TIM8_TRG_COM_IRQn     <0=> Secure state <1=> Non-Secure state
//   <o.4>  TIM8_CC_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.5>  ADC2_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.6>  LPTIM2_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.7>  TIM15_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.8>  TIM16_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.9>  TIM17_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.10> USB_DRD_FS_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.11> CRS_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.12> UCPD1_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.13> FMC_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.14> OCTOSPI1_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.15> SDMMC1_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.16> I2C3_EV_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.17> I2C3_ER_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.18> SPI4_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.19> SPI5_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.20> SPI6_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.21> USART6_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.22> USART10_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.23> USART11_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.24> SAI1_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.25> SAI2_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.26> GPDMA2_Channel0_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.27> GPDMA2_Channel1_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.28> GPDMA2_Channel2_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.29> GPDMA2_Channel3_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.30> GPDMA2_Channel4_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.31> GPDMA2_Channel5_IRQn  <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS2_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 3 (Interrupts 96..127)
*/
#define NVIC_INIT_ITNS3    1

/*
// Interrupts 96..127
//   <o.0>  GPDMA2_Channel6_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.1>  GPDMA2_Channel7_IRQn  <0=> Secure state <1=> Non-Secure state
//   <o.2>  UART7_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.3>  UART8_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.4>  UART9_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.5>  UART12_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.6>  SDMMC2_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.7>  FPU_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.8>  ICACHE_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.9>  DCACHE_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.10> ETH_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.11> ETH_WKUP_IRQn         <0=> Secure state <1=> Non-Secure state
//   <o.12> DCMI_PSSI_IRQn        <0=> Secure state <1=> Non-Secure state
//   <o.13> FDCAN2_IT0_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.14> FDCAN2_IT1_IRQn       <0=> Secure state <1=> Non-Secure state
//   <o.15> CORDIC_IRQn           <0=> Secure state <1=> Non-Secure state
//   <o.16> FMAC_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.17> DTS_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.18> RNG_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.19> OTFDEC1_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.20> AES_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.21> HASH_IRQn             <0=> Secure state <1=> Non-Secure state
//   <o.22> PKA_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.23> CEC_IRQn              <0=> Secure state <1=> Non-Secure state
//   <o.24> TIM12_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.25> TIM13_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.26> TIM14_IRQn            <0=> Secure state <1=> Non-Secure state
//   <o.27> I3C1_EV_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.28> I3C1_ER_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.29> I2C4_EV_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.30> I2C4_ER_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.31> LPTIM3_IRQn           <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS3_VAL      0x00000000

/*
//   </e>
*/

/*
//   <e>Initialize ITNS 4 (Interrupts 128..130)
*/
#define NVIC_INIT_ITNS4    1

/*
// Interrupts 128..130
//   <o.0>  LPTIM4_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.1>  LPTIM5_IRQn          <0=> Secure state <1=> Non-Secure state
//   <o.2>  LPTIM6_IRQn          <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS4_VAL      0x00000000

/*
//   </e>
*/

/*
// </h>
*/

/*
    max 8 SAU regions.
    SAU regions are defined in partition.h
 */

#define SAU_INIT_REGION(n) \
    SAU->RNR  =  (n                                     & SAU_RNR_REGION_Msk); \
    SAU->RBAR =  (SAU_INIT_START##n                     & SAU_RBAR_BADDR_Msk); \
    SAU->RLAR =  (SAU_INIT_END##n                       & SAU_RLAR_LADDR_Msk) | \
                ((SAU_INIT_NSC##n << SAU_RLAR_NSC_Pos)  & SAU_RLAR_NSC_Msk)   | 1U

/**
  \brief   Setup a SAU Region
  \details Writes the region information contained in SAU_Region to the
           registers SAU_RNR, SAU_RBAR, and SAU_RLAR
 */
__STATIC_INLINE void TZ_SAU_Setup (void)
{

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)

  #if defined (SAU_INIT_REGION0) && (SAU_INIT_REGION0 == 1U)
    SAU_INIT_REGION(0);
  #endif

  #if defined (SAU_INIT_REGION1) && (SAU_INIT_REGION1 == 1U)
    SAU_INIT_REGION(1);
  #endif

  #if defined (SAU_INIT_REGION2) && (SAU_INIT_REGION2 == 1U)
    SAU_INIT_REGION(2);
  #endif

  #if defined (SAU_INIT_REGION3) && (SAU_INIT_REGION3 == 1U)
    SAU_INIT_REGION(3);
  #endif

  #if defined (SAU_INIT_REGION4) && (SAU_INIT_REGION4 == 1U)
    SAU_INIT_REGION(4);
  #endif

  #if defined (SAU_INIT_REGION5) && (SAU_INIT_REGION5 == 1U)
    SAU_INIT_REGION(5);
  #endif

  #if defined (SAU_INIT_REGION6) && (SAU_INIT_REGION6 == 1U)
    SAU_INIT_REGION(6);
  #endif

  #if defined (SAU_INIT_REGION7) && (SAU_INIT_REGION7 == 1U)
    SAU_INIT_REGION(7);
  #endif

  /* repeat this for all possible SAU regions */

#endif /* defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U) */


  #if defined (SAU_INIT_CTRL) && (SAU_INIT_CTRL == 1U)
    SAU->CTRL = ((SAU_INIT_CTRL_ENABLE << SAU_CTRL_ENABLE_Pos) & SAU_CTRL_ENABLE_Msk) |
                ((SAU_INIT_CTRL_ALLNS  << SAU_CTRL_ALLNS_Pos)  & SAU_CTRL_ALLNS_Msk)   ;
  #endif

  #if defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U)
    SCB->SCR   = (SCB->SCR   & ~(SCB_SCR_SLEEPDEEPS_Msk    )) |
                   ((SCB_CSR_DEEPSLEEPS_VAL     << SCB_SCR_SLEEPDEEPS_Pos)     & SCB_SCR_SLEEPDEEPS_Msk);

    SCB->AIRCR = (SCB->AIRCR & ~(SCB_AIRCR_VECTKEY_Msk   | SCB_AIRCR_SYSRESETREQS_Msk |
                                 SCB_AIRCR_BFHFNMINS_Msk | SCB_AIRCR_PRIS_Msk)        )                     |
                   ((0x05FAU                    << SCB_AIRCR_VECTKEY_Pos)      & SCB_AIRCR_VECTKEY_Msk)      |
                   ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                   ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk)         |
                   ((SCB_AIRCR_BFHFNMINS_VAL    << SCB_AIRCR_BFHFNMINS_Pos)    & SCB_AIRCR_BFHFNMINS_Msk);
  #endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */

  #if defined (__FPU_USED) && (__FPU_USED == 1U) && \
      defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)

    SCB->NSACR = (SCB->NSACR & ~(SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk)) |
                   ((SCB_NSACR_CP10_11_VAL << SCB_NSACR_CP10_Pos) & (SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk));

    FPU->FPCCR = (FPU->FPCCR & ~(FPU_FPCCR_TS_Msk | FPU_FPCCR_CLRONRETS_Msk | FPU_FPCCR_CLRONRET_Msk)) |
                   ((FPU_FPCCR_TS_VAL        << FPU_FPCCR_TS_Pos       ) & FPU_FPCCR_TS_Msk       ) |
                   ((FPU_FPCCR_CLRONRETS_VAL << FPU_FPCCR_CLRONRETS_Pos) & FPU_FPCCR_CLRONRETS_Msk) |
                   ((FPU_FPCCR_CLRONRET_VAL  << FPU_FPCCR_CLRONRET_Pos ) & FPU_FPCCR_CLRONRET_Msk );
  #endif

  #if defined (NVIC_INIT_ITNS0) && (NVIC_INIT_ITNS0 == 1U)
    NVIC->ITNS[0] = NVIC_INIT_ITNS0_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS1) && (NVIC_INIT_ITNS1 == 1U)
    NVIC->ITNS[1] = NVIC_INIT_ITNS1_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS2) && (NVIC_INIT_ITNS2 == 1U)
    NVIC->ITNS[2] = NVIC_INIT_ITNS2_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS3) && (NVIC_INIT_ITNS3 == 1U)
    NVIC->ITNS[3] = NVIC_INIT_ITNS3_VAL;
  #endif

  #if defined (NVIC_INIT_ITNS4) && (NVIC_INIT_ITNS4 == 1U)
    NVIC->ITNS[4] = NVIC_INIT_ITNS4_VAL;
  #endif

}

#endif  /* PARTITION_STM32H573XX_H */
