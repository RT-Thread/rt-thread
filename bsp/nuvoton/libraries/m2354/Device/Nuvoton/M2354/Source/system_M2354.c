/**************************************************************************//**
 * @file     system_M2354.c
 * @version  V2.00
 * @brief    System Setting Source File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
#include <arm_cmse.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include "NuMicro.h"

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
#include "nu_partition_M2354.h"
#endif
extern void *g_pfnVectors;                   /* see startup file */


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock  = __HSI;              /*!< System Clock Frequency (Core Clock) */
uint32_t CyclesPerUs      = (__HSI / 1000000UL);/*!< Cycles per micro second             */
uint32_t PllClock         = __HSI;              /*!< PLL Output Clock Frequency          */

void FMC_NSBA_Setup(void);
void SCU_Setup(void);
void NSC_Init(void);
void TZ_SAU_Setup(void);


#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
extern void SCU_IRQHandler(void);
#else
extern void SCU_IRQHandler(void)__attribute__((noreturn));
#endif


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
 * @brief    Setup Non-secure boundary
 *
 * @details  This function is used to set Non-secure boundary according to
 *           the configuration of partition header file
 */
void FMC_NSBA_Setup(void)
{
    /* Skip NSBA Setupt according config */
    if(FMC_INIT_NSBA == 0)
        return;

    /* Check if NSBA value with current active NSBA */
    if(SCU->FNSADDR != FMC_SECURE_ROM_SIZE)
    {
        /* Unlock Protected Register */
        SYS_UnlockReg();

        /* Enable ISP and config update */
        FMC->ISPCTL = FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_CFGUEN_Msk;

        /* Config Base of NSBA */
        FMC->ISPADDR = FMC_NSCBA_BASE ;

        /* Read Non-secure base address config */
        FMC->ISPCMD = FMC_ISPCMD_READ;
        FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
        while(FMC->ISPTRG);

        //while(PA0);

        /* Setting NSBA when it is empty */
        if(FMC->ISPDAT != 0xfffffffful)
        {
            /* Erase old setting */
            FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE;
            FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
            while(FMC->ISPTRG);
        }

        /* Set new base */
        FMC->ISPDAT = FMC_SECURE_ROM_SIZE;
        FMC->ISPCMD = FMC_ISPCMD_PROGRAM;
        FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
        while(FMC->ISPTRG);

        /* Force Chip Reset to valid new setting */
        SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;


    }

}


/**
  \brief   Setup SCU Configuration Unit
  \details

 */
void SCU_Setup(void)
{
    int32_t i;

    SCU->PNSSET[0] = SCU_INIT_PNSSET0_VAL;
    SCU->PNSSET[1] = SCU_INIT_PNSSET1_VAL;
    SCU->PNSSET[2] = SCU_INIT_PNSSET2_VAL;
    SCU->PNSSET[3] = SCU_INIT_PNSSET3_VAL;
    SCU->PNSSET[4] = SCU_INIT_PNSSET4_VAL;
    SCU->PNSSET[5] = SCU_INIT_PNSSET5_VAL;
    SCU->PNSSET[6] = SCU_INIT_PNSSET6_VAL;


    SCU->IONSSET[0] = SCU_INIT_IONSSET0_VAL;
    SCU->IONSSET[1] = SCU_INIT_IONSSET1_VAL;
    SCU->IONSSET[2] = SCU_INIT_IONSSET2_VAL;
    SCU->IONSSET[3] = SCU_INIT_IONSSET3_VAL;
    SCU->IONSSET[4] = SCU_INIT_IONSSET4_VAL;
    SCU->IONSSET[5] = SCU_INIT_IONSSET5_VAL;
    SCU->IONSSET[6] = SCU_INIT_IONSSET6_VAL;
    SCU->IONSSET[7] = SCU_INIT_IONSSET7_VAL;

    /* Set Non-secure SRAM */
    for(i = 15; i >= SCU_SECURE_SRAM_SIZE / 16384; i--)
    {
        SCU->SRAMNSSET |= (1U << i);
    }

    /* Set interrupt to non-secure according to PNNSET settings */
    if(SCU_INIT_PNSSET0_VAL & BIT9) NVIC->ITNS[1] |= BIT22;  /* Int of USBH_INT     */
    if(SCU_INIT_PNSSET0_VAL & BIT13) NVIC->ITNS[2] |= BIT0 ; /* Int of SDHOST0_INT  */
    if(SCU_INIT_PNSSET0_VAL & BIT24) NVIC->ITNS[3] |= BIT2 ; /* Int of PDMA1_INT    */
    if(SCU_INIT_PNSSET1_VAL & BIT18) NVIC->ITNS[2] |= BIT7 ; /* Int of CRYPTO       */
    if(SCU_INIT_PNSSET2_VAL & BIT2) NVIC->ITNS[3] |= BIT15;  /* Int of EWDT_INT     */
    if(SCU_INIT_PNSSET2_VAL & BIT2) NVIC->ITNS[3] |= BIT16;  /* Int of EWWDT_INT    */
    if(SCU_INIT_PNSSET2_VAL & BIT3) NVIC->ITNS[1] |= BIT10;  /* Int of EADC0_INT    */
    if(SCU_INIT_PNSSET2_VAL & BIT3) NVIC->ITNS[1] |= BIT11;  /* Int of EADC1_INT    */
    if(SCU_INIT_PNSSET2_VAL & BIT3) NVIC->ITNS[1] |= BIT14;  /* Int of EADC2_INT    */
    if(SCU_INIT_PNSSET2_VAL & BIT3) NVIC->ITNS[1] |= BIT15;  /* Int of EADC3_INT    */
    if(SCU_INIT_PNSSET2_VAL & BIT5) NVIC->ITNS[1] |= BIT12;  /* Int of ACMP01_INT   */
    if(SCU_INIT_PNSSET2_VAL & BIT7) NVIC->ITNS[1] |= BIT9 ;  /* Int of DAC_INT      */
    if(SCU_INIT_PNSSET2_VAL & BIT8) NVIC->ITNS[2] |= BIT4 ;  /* Int of I2S0_INT     */
    if(SCU_INIT_PNSSET2_VAL & BIT13) NVIC->ITNS[1] |= BIT23; /* Int of USBOTG_INT   */
    if(SCU_INIT_PNSSET2_VAL & BIT17) NVIC->ITNS[1] |= BIT2 ; /* Int of TMR2_INT     */
    if(SCU_INIT_PNSSET2_VAL & BIT17) NVIC->ITNS[1] |= BIT3 ; /* Int of TMR3_INT     */
    if(SCU_INIT_PNSSET2_VAL & BIT18) NVIC->ITNS[3] |= BIT18; /* Int of TMR4_INT     */
    if(SCU_INIT_PNSSET2_VAL & BIT18) NVIC->ITNS[3] |= BIT19; /* Int of TMR5_INT     */
    if(SCU_INIT_PNSSET2_VAL & BIT24) NVIC->ITNS[0] |= BIT25; /* Int of EPWM0_P0_INT */
    if(SCU_INIT_PNSSET2_VAL & BIT24) NVIC->ITNS[0] |= BIT26; /* Int of EPWM0_P1_INT */
    if(SCU_INIT_PNSSET2_VAL & BIT24) NVIC->ITNS[0] |= BIT27; /* Int of EPWM0_P2_INT */
    if(SCU_INIT_PNSSET2_VAL & BIT25) NVIC->ITNS[0] |= BIT29; /* Int of EPWM1_P0_INT */
    if(SCU_INIT_PNSSET2_VAL & BIT25) NVIC->ITNS[0] |= BIT30; /* Int of EPWM1_P1_INT */
    if(SCU_INIT_PNSSET2_VAL & BIT25) NVIC->ITNS[0] |= BIT31; /* Int of EPWM1_P2_INT */
    if(SCU_INIT_PNSSET2_VAL & BIT26) NVIC->ITNS[2] |= BIT14; /* Int of BPWM0_INT    */
    if(SCU_INIT_PNSSET2_VAL & BIT27) NVIC->ITNS[2] |= BIT15; /* Int of BPWM1_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT0) NVIC->ITNS[0] |= BIT22;  /* Int of QSPI0_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT1) NVIC->ITNS[0] |= BIT23;  /* Int of SPI0_INT     */
    if(SCU_INIT_PNSSET3_VAL & BIT2) NVIC->ITNS[1] |= BIT19;  /* Int of SPI1_INT     */
    if(SCU_INIT_PNSSET3_VAL & BIT3) NVIC->ITNS[1] |= BIT20;  /* Int of SPI2_INT     */
    if(SCU_INIT_PNSSET3_VAL & BIT4) NVIC->ITNS[1] |= BIT30;  /* Int of SPI3_INT     */
    if(SCU_INIT_PNSSET3_VAL & BIT16) NVIC->ITNS[1] |= BIT4 ; /* Int of UART0_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT17) NVIC->ITNS[1] |= BIT5 ; /* Int of UART1_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT18) NVIC->ITNS[1] |= BIT16; /* Int of UART2_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT19) NVIC->ITNS[1] |= BIT17; /* Int of UART3_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT20) NVIC->ITNS[2] |= BIT10; /* Int of UART4_INT    */
    if(SCU_INIT_PNSSET3_VAL & BIT21) NVIC->ITNS[2] |= BIT11; /* Int of UART5_INT    */
    if(SCU_INIT_PNSSET4_VAL & BIT0) NVIC->ITNS[1] |= BIT6 ;  /* Int of I2C0_INT     */
    if(SCU_INIT_PNSSET4_VAL & BIT1) NVIC->ITNS[1] |= BIT7 ;  /* Int of I2C1_INT     */
    if(SCU_INIT_PNSSET4_VAL & BIT2) NVIC->ITNS[2] |= BIT18;  /* Int of I2C2_INT     */
    if(SCU_INIT_PNSSET4_VAL & BIT16) NVIC->ITNS[1] |= BIT26; /* Int of SC0_INT      */
    if(SCU_INIT_PNSSET4_VAL & BIT17) NVIC->ITNS[1] |= BIT27; /* Int of SC1_INT      */
    if(SCU_INIT_PNSSET4_VAL & BIT18) NVIC->ITNS[1] |= BIT28; /* Int of SC2_INT      */
    if(SCU_INIT_PNSSET5_VAL & BIT0) NVIC->ITNS[1] |= BIT24;  /* Int of CAN0_INT     */
    if(SCU_INIT_PNSSET5_VAL & BIT16) NVIC->ITNS[2] |= BIT20; /* Int of QEI0_INT     */
    if(SCU_INIT_PNSSET5_VAL & BIT17) NVIC->ITNS[2] |= BIT21; /* Int of QEI1_INT     */
    if(SCU_INIT_PNSSET5_VAL & BIT20) NVIC->ITNS[2] |= BIT22; /* Int of ECAP0_INT    */
    if(SCU_INIT_PNSSET5_VAL & BIT21) NVIC->ITNS[2] |= BIT23; /* Int of ECAP1_INT    */
    if(SCU_INIT_PNSSET5_VAL & BIT25) NVIC->ITNS[3] |= BIT5 ; /* Int of TRNG_INT     */
    if(SCU_INIT_PNSSET5_VAL & BIT27) NVIC->ITNS[3] |= BIT4 ; /* Int of LCD_INT      */
    if(SCU_INIT_PNSSET6_VAL & BIT0) NVIC->ITNS[1] |= BIT21;  /* Int of USBD_INT     */
    if(SCU_INIT_PNSSET6_VAL & BIT16) NVIC->ITNS[2] |= BIT12; /* Int of USCI0_INT    */
    if(SCU_INIT_PNSSET6_VAL & BIT17) NVIC->ITNS[2] |= BIT13; /* Int of USCI1_INT    */
    if(SCU_INIT_IONSSET_VAL & BIT0) NVIC->ITNS[0] |= BIT16;  /* Int of PA           */
    if(SCU_INIT_IONSSET_VAL & BIT1) NVIC->ITNS[0] |= BIT17;  /* Int of PB           */
    if(SCU_INIT_IONSSET_VAL & BIT2) NVIC->ITNS[0] |= BIT18;  /* Int of PC           */
    if(SCU_INIT_IONSSET_VAL & BIT3) NVIC->ITNS[0] |= BIT19;  /* Int of PD           */
    if(SCU_INIT_IONSSET_VAL & BIT4) NVIC->ITNS[0] |= BIT20;  /* Int of PE           */
    if(SCU_INIT_IONSSET_VAL & BIT5) NVIC->ITNS[0] |= BIT21;  /* Int of PF           */
    if(SCU_INIT_IONSSET_VAL & BIT6) NVIC->ITNS[2] |= BIT8 ;  /* Int of PG           */
    if(SCU_INIT_IONSSET_VAL & BIT7) NVIC->ITNS[2] |= BIT24;  /* Int of PH           */
    if(SCU_INIT_IONSSET_VAL & BIT8) NVIC->ITNS[0] |= BIT10;  /* Int of EINT0        */
    if(SCU_INIT_IONSSET_VAL & BIT9) NVIC->ITNS[0] |= BIT11;  /* Int of EINT1        */
    if(SCU_INIT_IONSSET_VAL & BIT10) NVIC->ITNS[0] |= BIT12; /* Int of EINT2        */
    if(SCU_INIT_IONSSET_VAL & BIT11) NVIC->ITNS[0] |= BIT13; /* Int of EINT3        */
    if(SCU_INIT_IONSSET_VAL & BIT12) NVIC->ITNS[0] |= BIT14; /* Int of EINT4        */
    if(SCU_INIT_IONSSET_VAL & BIT13) NVIC->ITNS[0] |= BIT15; /* Int of EINT5        */
    if(SCU_INIT_IONSSET_VAL & BIT14) NVIC->ITNS[2] |= BIT9;  /* Int of EINT6        */
    if(SCU_INIT_IONSSET_VAL & BIT15) NVIC->ITNS[2] |= BIT25; /* Int of EINT7        */

    /* Enable SCU Int status */
    SCU->SVIOIEN = (uint32_t)(-1);
    SCU->PVIOIEN = (uint32_t)(-1);
    NVIC_EnableIRQ(SCU_IRQn);

}


#if defined( __ICCARM__ )
__WEAK
#else
__attribute__((weak))
#endif
void SCU_IRQHandler(void)
{
    char const *master[] = {"CPU", 0, 0, "PDMA0", "SDH0", "CRPT", "USBH", 0, 0, 0, 0, "PDMA1"};
    char const *ipname[] = {"APB0", "APB1", 0, 0, "GPIO", "EBI", "USBH", "CRC", "SDH0", 0, "PDMA0", "PDMA1"
                            , "SRAM0", "SRAM1", "FMC", "FLASH", "SCU", "SYS", "CRPT", "KS", "SIORAM"
                           };
    const uint8_t info[] = {0x34, 0x3C, 0, 0, 0x44, 0x4C, 0x54, 0x5C, 0x64, 0, 0x74, 0x7C, 0x84, 0x8C, 0x94, 0x9C, 0xA4, 0xAC, 0xB4, 0xBC, 0xC4};
    uint32_t u32Reg, u32Addr;
    uint32_t i;

    /* TrustZone access policy */
    u32Reg = SCU->SVINTSTS;
    if(u32Reg)
    {

        /* Get violation address and source */
        for(i = 0; i < sizeof(ipname); i++)
        {
            if(u32Reg & (1 << i))
            {
                u32Addr = M32(SCU_BASE + info[i] + 4);
                printf("  %s(0x%08x) Alarm! illegal access by %s\n", ipname[i], u32Addr, master[M32(SCU_BASE + info[i])]);
                SCU->SVINTSTS = (1 << i);
                break;
            }

        }
    }

    /* Privilege */
    u32Reg = SCU->PVINTSTS;
    if(u32Reg)
    {
        /* Get violation address and source */
        for(i = 0; i < sizeof(ipname); i++)
        {
            if(u32Reg & (1 << i))
            {
                printf("\n%s Alarm! Caused by unprivilege access\n\n", ipname[i]);
                SCU->PVINTSTS = (1 << i);
                break;
            }
        }
    }

}


/**
  \brief   Setup a Nonsecure callable Region
  \details The base and limit of Nonsecure callable region is dependent on the
           application code size.
 */
void NSC_Init(void)
{
    uint32_t u32Region;
    uint32_t u32Base, u32Limit;

#if defined (__ICCARM__)
# pragma section = "NSC"
    u32Base = (uint32_t)__section_begin("NSC");
    u32Limit = (uint32_t)__section_end("NSC");
#elif defined(__ARMCC_VERSION)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
    extern uint32_t Image$$NSC_ROM$$XO$$Base[];
    extern uint32_t Image$$NSC_ROM$$XO$$Limit[];
    u32Base = (uint32_t)Image$$NSC_ROM$$XO$$Base;
    u32Limit = (uint32_t)Image$$NSC_ROM$$XO$$Limit;
#pragma clang diagnostic pop
#else
    extern uint32_t __start_NSC[];
    extern uint32_t __end_NSC[];
    u32Base = (uint32_t)__start_NSC;
    u32Limit = (uint32_t)__end_NSC;
#endif

    /* SAU region 3 is dedicated for NSC */
    u32Region = 3;
    SAU->RNR  = (u32Region & SAU_RNR_REGION_Msk);
    SAU->RBAR = (u32Base & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = (u32Limit & SAU_RLAR_LADDR_Msk) |
                ((1ul << SAU_RLAR_NSC_Pos)  & SAU_RLAR_NSC_Msk) | 1ul;

}

/**
  \brief   Setup a SAU Region
  \details Writes the region information contained in SAU_Region to the
           registers SAU_RNR, SAU_RBAR, and SAU_RLAR
 */
void TZ_SAU_Setup(void)
{

#if defined (__SAU_PRESENT) && (__SAU_PRESENT == 1U)

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


#if defined (SAU_INIT_CTRL) && (SAU_INIT_CTRL == 1U)
    SAU->CTRL = ((SAU_INIT_CTRL_ENABLE << SAU_CTRL_ENABLE_Pos) & SAU_CTRL_ENABLE_Msk) |
                ((SAU_INIT_CTRL_ALLNS  << SAU_CTRL_ALLNS_Pos)  & SAU_CTRL_ALLNS_Msk)   ;
#endif

#endif /* defined (__SAU_PRESENT) && (__SAU_PRESENT == 1U) */

#if defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U)
    SCB->SCR   = (SCB->SCR   & ~(SCB_SCR_SLEEPDEEPS_Msk)) |
                 ((SCB_CSR_DEEPSLEEPS_VAL     << SCB_SCR_SLEEPDEEPS_Pos)     & SCB_SCR_SLEEPDEEPS_Msk);

    SCB->AIRCR = (0x05FA << 16) |
                 ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                 ((SCB_AIRCR_BFHFNMINS_VAL    << SCB_AIRCR_BFHFNMINS_Pos)    & SCB_AIRCR_BFHFNMINS_Msk)    |
                 ((SCB_AIRCR_PRIS_VAL         << SCB_AIRCR_PRIS_Pos)         & SCB_AIRCR_PRIS_Msk);



#endif /* defined (SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U) */

#if defined (SCB_ICSR_INIT) && (SCB_ICSR_INIT == 1U)
    SCB->ICSR  = (SCB->ICSR  & ~(SCB_ICSR_STTNS_Msk)) |
                 ((SCB_ICSR_STTNS_VAL         << SCB_ICSR_STTNS_Pos)         & SCB_ICSR_STTNS_Msk);
#endif /* defined (SCB_ICSR_INIT) && (SCB_ICSR_INIT == 1U) */

    /* repeat this for all possible ITNS elements */

    /* Initial Nonsecure callable region */
    NSC_Init();
}
#else
#if defined( __ICCARM__ )
__WEAK
#else
__attribute__((weak))
#endif
void SCU_IRQHandler(void)
{
    while(1);
}
#endif


/**
 * @brief    Update the Variable SystemCoreClock
 *
 * @details  This function is used to update the variable SystemCoreClock
 *           and must be called whenever the core clock is changed.
 */
void SystemCoreClockUpdate(void)
{
    /* Update PLL Clock */
    PllClock = CLK_GetPLLClockFreq();

    /* Update System Core Clock */
    SystemCoreClock = CLK_GetCPUFreq();

    /* Update Cycles per micro second */
    CyclesPerUs = (SystemCoreClock + 500000UL) / 1000000UL;
}



/**
 * @brief    System Initialization
 *
 * @details  The necessary initialization of system. Global variables are forbidden here.
 */
void SystemInit(void)
{
#if 0
/* Move the scope into Reset_Handler to avoid invalid memory access. */
/* When push LR to RAM region is not enabled, it will get hardware after exit SystemInit.*/
    if((__PC() & NS_OFFSET) == 0)
    {
        /* Unlock protected registers */
        do
        {
            SYS->REGLCTL = 0x59;
            SYS->REGLCTL = 0x16;
            SYS->REGLCTL = 0x88;
        }
        while(!SYS->REGLCTL);

        /* Enable Crypto power switch */
        SYS->PSWCTL = SYS_PSWCTL_CRPTPWREN_Msk;

        /* Enable all GPIO, SRAM and Trace clock */
        CLK->AHBCLK |= (0xffful << 20) | (1ul << 14);
    }
#endif

#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#endif

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
    TZ_SAU_Setup();
    SCU_Setup();
    FMC_NSBA_Setup();
#endif

#ifdef INIT_SYSCLK_AT_BOOTING

#endif

}


#if USE_ASSERT

/**
 * @brief      Assert Error Message
 *
 * @param[in]  file  the source file name
 * @param[in]  line  line number
 *
 * @details    The function prints the source file name and line number where
 *             the ASSERT_PARAM() error occurs, and then stops in an infinite loop.
 */
void AssertError(uint8_t * file, uint32_t line)
{

    printf("[%s] line %d : wrong parameters.\r\n", file, line);

    /* Infinite loop */
    while(1) ;
}
#endif


#if (defined(__ICCARM__) && (__VER__ >= 7080000) && (__VER__ < 8020000))

#if  (__ARM_FEATURE_CMSE == 3U)
/**
  \brief   Get Process Stack Pointer (non-secure)
  \details Returns the current value of the non-secure Process Stack Pointer (PSP) when in secure state.
  \return               PSP Register value
 */
uint32_t __TZ_get_PSP_NS(void)
{
    register uint32_t result;

    __ASM volatile("MRS %0, psp_ns"  : "=r"(result));
    return(result);
}


/**
  \brief   Set Process Stack Pointer (non-secure)
  \details Assigns the given value to the non-secure Process Stack Pointer (PSP) when in secure state.
  \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
void __TZ_set_PSP_NS(uint32_t topOfProcStack)
{
    __ASM volatile("MSR psp_ns, %0" : : "r"(topOfProcStack));
}



/**
  \brief   Get Main Stack Pointer (non-secure)
  \details Returns the current value of the non-secure Main Stack Pointer (MSP) when in secure state.
  \return               MSP Register value
 */
int32_t __TZ_get_MSP_NS(void)
{
    register uint32_t result;

    __ASM volatile("MRS %0, msp_ns" : "=r"(result));
    return(result);
}



/**
  \brief   Set Main Stack Pointer (non-secure)
  \details Assigns the given value to the non-secure Main Stack Pointer (MSP) when in secure state.
  \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
void __TZ_set_MSP_NS(uint32_t topOfMainStack)
{
    __ASM volatile("MSR msp_ns, %0" : : "r"(topOfMainStack));
}



/**
  \brief   Get Priority Mask (non-secure)
  \details Returns the current state of the non-secure priority mask bit from the Priority Mask Register when in secure state.
  \return               Priority Mask value
 */
uint32_t __TZ_get_PRIMASK_NS(void)
{
    uint32_t result;

    __ASM volatile("MRS %0, primask_ns" : "=r"(result));
    return(result);
}



/**
  \brief   Set Priority Mask (non-secure)
  \details Assigns the given value to the non-secure Priority Mask Register when in secure state.
  \param [in]    priMask  Priority Mask
 */
void __TZ_set_PRIMASK_NS(uint32_t priMask)
{
    __ASM volatile("MSR primask_ns, %0" : : "r"(priMask) : "memory");
}


#endif


#endif



