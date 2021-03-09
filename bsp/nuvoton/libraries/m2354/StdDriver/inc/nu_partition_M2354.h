/**************************************************************************//**
 * @file     nu_partition_M2354.h
 * @version  V3.00
 * @brief    TrustZone partition file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#ifndef PARTITION_M2354
#define PARTITION_M2354

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)

/*
   Default M2354 pritition configuration file is for non-TrustZone sample code only.
   If user wants to use TrurstZone, they should have their partition_m2354.h.
   For TrustZone projects, path of local partition_m2354.h should be in the
   front of the include path list to make sure local partition_m2354.h is used.

   It also apply to non-secure project of the TrustZone projects.

*/
# error "Link to default nu_partition_M2354.h in secure mode. Please check your include path."

#endif

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/


/*
    SRAMNSSET
*/
/*
// Bit 0..18
// <o.0..18> Secure SRAM Size              <0=> 0 KB
//                                         <0x4000=> 16KB
//                                         <0x8000=> 32KB
//                                         <0xc000=> 48KB
//                                         <0x10000=> 64KB
//                                         <0x14000=> 80KB
//                                         <0x18000=> 96KB
//                                         <0x1C000=> 112KB
//                                         <0x20000=> 128KB
//                                         <0x24000=> 144KB
//                                         <0x28000=> 160KB
//                                         <0x2C000=> 176KB
//                                         <0x30000=> 192KB
//                                         <0x34000=> 208KB
//                                         <0x38000=> 224KB
//                                         <0x3C000=> 240KB
//                                         <0x40000=> 256KB
*/
#define SCU_SECURE_SRAM_SIZE      0x18000
#define NON_SECURE_SRAM_BASE    (0x30000000 + SCU_SECURE_SRAM_SIZE)



/*--------------------------------------------------------------------------------------------------------*/

/*
    NSBA
*/
#define FMC_INIT_NSBA          1
/*
//     <o>Secure Flash ROM Size <0x800-0x80000:0x800>
*/

#define FMC_SECURE_ROM_SIZE      0x80000

#define FMC_NON_SECURE_BASE     (0x10000000 + FMC_SECURE_ROM_SIZE)

/*--------------------------------------------------------------------------------------------------------*/


/*
// <h> Peripheral Secure Attribution Configuration
*/

/*
    PNSSET0
*/
/*
// Module 0..31
//   <o.9>  USBH       <0=> Secure <1=> Non-Secure
//   <o.13>  SD0   <0=> Secure <1=> Non-Secure
//   <o.16>  EBI    <0=> Secure <1=> Non-Secure
//   <o.24>  PDMA1      <0=> Secure <1=> Non-Secure
*/
#define SCU_INIT_PNSSET0_VAL      0x0
/*
    PNSSET1
*/
/*
// Module 0..31
//   <o.17>  CRC       <0=> Secure <1=> Non-Secure
//   <o.18>  CRPT   <0=> Secure <1=> Non-Secure
*/
#define SCU_INIT_PNSSET1_VAL      0x00000
/*
    PNSSET2
*/
/*
// Module 0..31
//   <o.2>  EWDT        <0=> Secure <1=> Non-Secure
//   <o.3>  EADC        <0=> Secure <1=> Non-Secure
//   <o.5>  ACMP01      <0=> Secure <1=> Non-Secure
//
//   <o.7>  DAC         <0=> Secure <1=> Non-Secure
//   <o.8>  I2S0        <0=> Secure <1=> Non-Secure
//   <o.13>  OTG        <0=> Secure <1=> Non-Secure
//   <h> TIMER
//   <o.17>  TMR23      <0=> Secure <1=> Non-Secure
//   <o.18>  TMR45      <0=> Secure <1=> Non-Secure
//   <h> EPWM
//   <o.24>  EPWM0      <0=> Secure <1=> Non-Secure
//   <o.25>  EPWM1      <0=> Secure <1=> Non-Secure
//   </h>
//   <h> BPWM
//   <o.26>  BPWM0      <0=> Secure <1=> Non-Secure
//   <o.27>  BPWM1      <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_PNSSET2_VAL      0x0
/*
    PNSSET3
*/
/*
// Module 0..31
//   <h>  SPI
//   <o.0>  QSPI0       <0=> Secure <1=> Non-Secure
//   <o.1>  SPI0   <0=> Secure <1=> Non-Secure
//   <o.2>  SPI1      <0=> Secure <1=> Non-Secure
//   <o.3>  SPI2    <0=> Secure <1=> Non-Secure
//   <o.4>  SPI3      <0=> Secure <1=> Non-Secure
//   </h>
//   <h> UART
//   <o.16>  UART0      <0=> Secure <1=> Non-Secure
//   <o.17>  UART1      <0=> Secure <1=> Non-Secure
//   <o.18>  UART2      <0=> Secure <1=> Non-Secure
//   <o.19>  UART3      <0=> Secure <1=> Non-Secure
//   <o.20>  UART4      <0=> Secure <1=> Non-Secure
//   <o.21>  UART5      <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_PNSSET3_VAL      0x00000
/*
    PNSSET4
*/
/*
// Module 0..31
//   <h> I2C
//   <o.0>  I2C0       <0=> Secure <1=> Non-Secure
//   <o.1>  I2C1   <0=> Secure <1=> Non-Secure
//   <o.2>  I2C2      <0=> Secure <1=> Non-Secure
//   </h>
//   <h> Smart Card
//   <o.16>  SC0      <0=> Secure <1=> Non-Secure
//   <o.17>  SC1      <0=> Secure <1=> Non-Secure
//   <o.18>  SC2      <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_PNSSET4_VAL      0x0
/*
    PNSSET5
*/
/*
// Module 0..31
//   <o.0>  CAN0        <0=> Secure <1=> Non-Secure
//   <h> QEI
//   <o.16>  QEI0       <0=> Secure <1=> Non-Secure
//   <o.17>  QEI1       <0=> Secure <1=> Non-Secure
//   </h>
//   <h> ECAP
//   <o.20>  ECAP0      <0=> Secure <1=> Non-Secure
//   <o.21>  ECAP1      <0=> Secure <1=> Non-Secure
//   </h>
//   <o.25>  TRNG       <0=> Secure <1=> Non-Secure
//   <o.27>  LCD        <0=> Secure <1=> Non-Secure
*/
#define SCU_INIT_PNSSET5_VAL      0x0
/*
    PNSSET6
*/
/*
// Module 0..31
//   <o.0>  USBD       <0=> Secure <1=> Non-Secure
//   <h> USCI
//   <o.16>  USCI0   <0=> Secure <1=> Non-Secure
//   <o.17>  USCI1      <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_PNSSET6_VAL      0x0
/*
// </h>
*/


/*
// <h> GPIO Secure Attribution Configuration
*/

/*
    IONSSET
*/

/*
// Bit 0..31
//   <h> PA
//   <o.0>  PA0       <0=> Secure <1=> Non-Secure
//   <o.1>  PA1       <0=> Secure <1=> Non-Secure
//   <o.2>  PA2       <0=> Secure <1=> Non-Secure
//   <o.3>  PA3       <0=> Secure <1=> Non-Secure
//   <o.4>  PA4       <0=> Secure <1=> Non-Secure
//   <o.5>  PA5       <0=> Secure <1=> Non-Secure
//   <o.6>  PA6       <0=> Secure <1=> Non-Secure
//   <o.7>  PA7       <0=> Secure <1=> Non-Secure
//   <o.8>  PA8       <0=> Secure <1=> Non-Secure
//   <o.7>  PA9       <0=> Secure <1=> Non-Secure
//   <o.10>  PA10       <0=> Secure <1=> Non-Secure
//   <o.11>  PA11       <0=> Secure <1=> Non-Secure
//   <o.12>  PA12       <0=> Secure <1=> Non-Secure
//   <o.13>  PA13       <0=> Secure <1=> Non-Secure
//   <o.14>  PA14       <0=> Secure <1=> Non-Secure
//   <o.15>  PA15      <0=> Secure <1=> Non-Secure
//   </h>

*/
#define SCU_INIT_IONSSET0_VAL      0x00000000

/*
// Bit 0..31
//   <h> PB
//   <o.0>  PB0       <0=> Secure <1=> Non-Secure
//   <o.1>  PB1       <0=> Secure <1=> Non-Secure
//   <o.2>  PB2       <0=> Secure <1=> Non-Secure
//   <o.3>  PB3       <0=> Secure <1=> Non-Secure
//   <o.4>  PB4       <0=> Secure <1=> Non-Secure
//   <o.5>  PB5       <0=> Secure <1=> Non-Secure
//   <o.6>  PB6       <0=> Secure <1=> Non-Secure
//   <o.7>  PB7       <0=> Secure <1=> Non-Secure
//   <o.8>  PB8       <0=> Secure <1=> Non-Secure
//   <o.9>  PB9       <0=> Secure <1=> Non-Secure
//   <o.10>  PB10       <0=> Secure <1=> Non-Secure
//   <o.11>  PB11       <0=> Secure <1=> Non-Secure
//   <o.12>  PB12       <0=> Secure <1=> Non-Secure
//   <o.13>  PB13       <0=> Secure <1=> Non-Secure
//   <o.14>  PB14       <0=> Secure <1=> Non-Secure
//   <o.15>  PB15       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET1_VAL      0x00000000


/*
// Bit 0..31
//   <h> PC
//   <o.0>  PC0       <0=> Secure <1=> Non-Secure
//   <o.1>  PC1       <0=> Secure <1=> Non-Secure
//   <o.2>  PC2       <0=> Secure <1=> Non-Secure
//   <o.3>  PC3       <0=> Secure <1=> Non-Secure
//   <o.4>  PC4       <0=> Secure <1=> Non-Secure
//   <o.5>  PC5       <0=> Secure <1=> Non-Secure
//   <o.6>  PC6       <0=> Secure <1=> Non-Secure
//   <o.7>  PC7       <0=> Secure <1=> Non-Secure
//   <o.8>  PC8       <0=> Secure <1=> Non-Secure
//   <o.9>  PC9       <0=> Secure <1=> Non-Secure
//   <o.10>  PC10       <0=> Secure <1=> Non-Secure
//   <o.11>  PC11       <0=> Secure <1=> Non-Secure
//   <o.12>  PC12       <0=> Secure <1=> Non-Secure
//   <o.13>  PC13       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET2_VAL      0x00000000

/*
// Bit 0..31
//   <h> PD
//   <o.0>  PD0       <0=> Secure <1=> Non-Secure
//   <o.1>  PD1       <0=> Secure <1=> Non-Secure
//   <o.2>  PD2       <0=> Secure <1=> Non-Secure
//   <o.3>  PD3       <0=> Secure <1=> Non-Secure
//   <o.4>  PD4       <0=> Secure <1=> Non-Secure
//   <o.5>  PD5       <0=> Secure <1=> Non-Secure
//   <o.6>  PD6       <0=> Secure <1=> Non-Secure
//   <o.7>  PD7       <0=> Secure <1=> Non-Secure
//   <o.8>  PD8       <0=> Secure <1=> Non-Secure
//   <o.9>  PD9       <0=> Secure <1=> Non-Secure
//   <o.10>  PD10       <0=> Secure <1=> Non-Secure
//   <o.11>  PD11       <0=> Secure <1=> Non-Secure
//   <o.12>  PD12       <0=> Secure <1=> Non-Secure
//   <o.14>  PD14       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET3_VAL      0x00000000


/*
// Bit 0..31
//   <h> PE
//   <o.0>  PE0       <0=> Secure <1=> Non-Secure
//   <o.1>  PE1       <0=> Secure <1=> Non-Secure
//   <o.2>  PE2       <0=> Secure <1=> Non-Secure
//   <o.3>  PE3       <0=> Secure <1=> Non-Secure
//   <o.4>  PE4       <0=> Secure <1=> Non-Secure
//   <o.5>  PE5       <0=> Secure <1=> Non-Secure
//   <o.6>  PE6       <0=> Secure <1=> Non-Secure
//   <o.7>  PE7       <0=> Secure <1=> Non-Secure
//   <o.8>  PE8       <0=> Secure <1=> Non-Secure
//   <o.9>  PE9       <0=> Secure <1=> Non-Secure
//   <o.10>  PE10       <0=> Secure <1=> Non-Secure
//   <o.11>  PE11       <0=> Secure <1=> Non-Secure
//   <o.12>  PE12       <0=> Secure <1=> Non-Secure
//   <o.13>  PE13       <0=> Secure <1=> Non-Secure
//   <o.14>  PE14       <0=> Secure <1=> Non-Secure
//   <o.15>  PE15       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET4_VAL      0x00000000


/*
// Bit 0..31
//   <h> PF
//   <o.0>  PF0       <0=> Secure <1=> Non-Secure
//   <o.1>  PF1       <0=> Secure <1=> Non-Secure
//   <o.2>  PF2       <0=> Secure <1=> Non-Secure
//   <o.3>  PF3       <0=> Secure <1=> Non-Secure
//   <o.4>  PF4       <0=> Secure <1=> Non-Secure
//   <o.5>  PF5       <0=> Secure <1=> Non-Secure
//   <o.6>  PF6       <0=> Secure <1=> Non-Secure
//   <o.7>  PF7       <0=> Secure <1=> Non-Secure
//   <o.8>  PF8       <0=> Secure <1=> Non-Secure
//   <o.9>  PF9       <0=> Secure <1=> Non-Secure
//   <o.10>  PF10       <0=> Secure <1=> Non-Secure
//   <o.11>  PF11       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET5_VAL      0x00000000


/*
// Bit 0..31
//   <h> PG
//   <o.2>  PG2       <0=> Secure <1=> Non-Secure
//   <o.3>  PG3       <0=> Secure <1=> Non-Secure
//   <o.4>  PG4       <0=> Secure <1=> Non-Secure
//   <o.9>  PG9       <0=> Secure <1=> Non-Secure
//   <o.10>  PG10       <0=> Secure <1=> Non-Secure
//   <o.11>  PG11       <0=> Secure <1=> Non-Secure
//   <o.12>  PG12       <0=> Secure <1=> Non-Secure
//   <o.13>  PG13       <0=> Secure <1=> Non-Secure
//   <o.14>  PG14       <0=> Secure <1=> Non-Secure
//   <o.15>  PG15       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET6_VAL      0x00000000

/*
// Bit 0..31
//   <h> PH
//   <o.4>  PH4       <0=> Secure <1=> Non-Secure
//   <o.5>  PH5       <0=> Secure <1=> Non-Secure
//   <o.6>  PH6       <0=> Secure <1=> Non-Secure
//   <o.7>  PH7       <0=> Secure <1=> Non-Secure
//   <o.8>  PH8       <0=> Secure <1=> Non-Secure
//   <o.9>  PH9       <0=> Secure <1=> Non-Secure
//   <o.10>  PH10       <0=> Secure <1=> Non-Secure
//   <o.11>  PH11       <0=> Secure <1=> Non-Secure
//   </h>
*/
#define SCU_INIT_IONSSET7_VAL      0x00000000

/*
// </h>
*/



/*
// <h>Assign GPIO Interrupt to Secure or Non-secure Vector
*/


/*
    Initialize GPIO ITNS (Interrupts 0..31)
*/

/*
// Bit 0..31
//   <o.0>  GPA         <0=> Secure <1=> Non-Secure
//   <o.1>  GPB         <0=> Secure <1=> Non-Secure
//   <o.2>  GPC         <0=> Secure <1=> Non-Secure
//   <o.3>  GPD         <0=> Secure <1=> Non-Secure
//   <o.4>  GPE         <0=> Secure <1=> Non-Secure
//   <o.5>  GPF         <0=> Secure <1=> Non-Secure
//   <o.6>  GPG         <0=> Secure <1=> Non-Secure
//   <o.7>  GPH         <0=> Secure <1=> Non-Secure
//   <o.8>  EINT0         <0=> Secure <1=> Non-Secure
//   <o.9>  EINT1         <0=> Secure <1=> Non-Secure
//   <o.10>  EINT2         <0=> Secure <1=> Non-Secure
//   <o.11>  EINT3         <0=> Secure <1=> Non-Secure
//   <o.12>  EINT4         <0=> Secure <1=> Non-Secure
//   <o.13>  EINT5         <0=> Secure <1=> Non-Secure
//   <o.14>  EINT6         <0=> Secure <1=> Non-Secure
//   <o.15>  EINT7         <0=> Secure <1=> Non-Secure
*/
#define SCU_INIT_IONSSET_VAL      0x0000
/*
// </h>
*/



/* ---------------------------------------------------------------------------------------------------- */

/*
// <e>Secure Attribute Unit (SAU) Control
*/
#define SAU_INIT_CTRL 0

/*
//   <q> Enable SAU
//   <i> To enable Secure Attribute Unit (SAU).
*/
#define SAU_INIT_CTRL_ENABLE 1

/*
//   <o> All Memory Attribute When SAU is disabled
//     <0=> All Memory is Secure
//     <1=> All Memory is Non-Secure
//   <i> To set the ALLNS bit in SAU CTRL.
//   <i> When all Memory is Non-Secure (ALLNS is 1), IDAU can override memory map configuration.
*/
#define SAU_INIT_CTRL_ALLNS  0

/*
// </e>
*/


/*
// <h>Enable and Set Secure/Non-Secure region
*/
#define SAU_REGIONS_MAX   8                 /* Max. number of SAU regions */

/*
//   <e>SAU Region 0
//   <i> Setup SAU Region 0
*/
#define SAU_INIT_REGION0    0
/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0     0x0003F000      /* start address of SAU region 0 */
/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x0003FFFF      /* end address of SAU region 0 */
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
//   <e>SAU Region 1
//   <i> Setup SAU Region 1
*/
#define SAU_INIT_REGION1    0
/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START1     0x10040000
/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x1007FFFF
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
//   <e>SAU Region 2
//   <i> Setup SAU Region 2
*/
#define SAU_INIT_REGION2    0
/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START2     0x2000F000
/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0x2000FFFF
/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC2       1
/*
//   </e>
*/

/*
//   <e>SAU Region 3
//   <i> Setup SAU Region 3
*/
#define SAU_INIT_REGION3    0
/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START3     0x3f000
/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0x3f7ff
/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC3       1
/*
//   </e>
*/

/*
   <e>SAU Region 4
   <i> Setup SAU Region 4
*/
#define SAU_INIT_REGION4    1
/*
     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START4     FMC_NON_SECURE_BASE      /* start address of SAU region 4 */

/*
     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END4       0x1007FFFF      /* end address of SAU region 4 */

/*
     <o>Region is
         <0=>Non-Secure
         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC4       0
/*
   </e>
*/

/*
   <e>SAU Region 5
   <i> Setup SAU Region 5
*/
#define SAU_INIT_REGION5    1

/*
     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START5     0x00807E00

/*
     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END5       0x00807FFF

/*
     <o>Region is
         <0=>Non-Secure
         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC5       1
/*
   </e>
*/

/*
   <e>SAU Region 6
   <i> Setup SAU Region 6
*/
#define SAU_INIT_REGION6    1

/*
     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START6     NON_SECURE_SRAM_BASE

/*
     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END6       0x30017FFF

/*
     <o>Region is
         <0=>Non-Secure
         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC6       0
/*
   </e>
*/

/*
   <e>SAU Region 7
   <i> Setup SAU Region 7
*/
#define SAU_INIT_REGION7    1

/*
     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START7     0x50000000

/*
     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END7       0x5FFFFFFF

/*
     <o>Region is
         <0=>Non-Secure
         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC7       0
/*
   </e>
*/

/*
// </h>
*/

/*
// <e>Setup behavior of Sleep and Exception Handling
*/
#define SCB_CSR_AIRCR_INIT  1

/*
//   <o> Deep Sleep can be enabled by
//     <0=>Secure and Non-Secure state
//     <1=>Secure state only
//   <i> Value for SCB->CSR register bit DEEPSLEEPS
*/
#define SCB_CSR_DEEPSLEEPS_VAL  0

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
//     <1=> Lowered to 0x80-0xFF
//   <i> Value for SCB->AIRCR register bit PRIS
*/
#define SCB_AIRCR_PRIS_VAL      0

/* Assign HardFault to be always secure for safe */
#define SCB_AIRCR_BFHFNMINS_VAL 0

/*
// </e>
*/

/*
    max 128 SAU regions.
    SAU regions are defined in partition.h
 */

#define SAU_INIT_REGION(n) \
    SAU->RNR  =  (n                                     & SAU_RNR_REGION_Msk); \
    SAU->RBAR =  (SAU_INIT_START##n                     & SAU_RBAR_BADDR_Msk); \
    SAU->RLAR =  (SAU_INIT_END##n                       & SAU_RLAR_LADDR_Msk) | \
                ((SAU_INIT_NSC##n << SAU_RLAR_NSC_Pos)  & SAU_RLAR_NSC_Msk)   | 1U


#endif  /* PARTITION_M2354 */

