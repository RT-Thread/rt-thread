/************************************************************************/
/*               (C) Fujitsu Semiconductor Europe GmbH                  */
/*                                                                      */
/* The following software deliverable is intended for and must only be  */
/* used for reference and in an evaluation laboratory environment.      */
/* It is provided on an as-is basis without charge and is subject to    */
/* alterations.                                                         */
/* It is the user’s obligation to fully test the software in its        */
/* environment and to ensure proper functionality, qualification and    */
/* compliance with component specifications.                            */
/*                                                                      */
/* In the event the software deliverable includes the use of open       */
/* source components, the provisions of the governing open source       */
/* license agreement shall apply with respect to such software          */
/* deliverable.                                                         */
/* FSEU does not warrant that the deliverables do not infringe any      */
/* third party intellectual property right (IPR). In the event that     */
/* the deliverables infringe a third party IPR it is the sole           */
/* responsibility of the customer to obtain necessary licenses to       */
/* continue the usage of the deliverable.                               */
/*                                                                      */
/* To the maximum extent permitted by applicable law FSEU disclaims all */
/* warranties, whether express or implied, in particular, but not       */
/* limited to, warranties of merchantability and fitness for a          */
/* particular purpose for which the deliverable is not designated.      */
/*                                                                      */
/* To the maximum extent permitted by applicable law, FSEU's liability  */
/* is restricted to intention and gross negligence.                     */
/* FSEU is not liable for consequential damages.                        */
/*                                                                      */
/* (V1.4)                                                               */
/************************************************************************/

#include "mb9bf506r.h"

/* 
 *  80MHz : Master Clock
 */
const uint32_t SystemFrequency = 80000000UL;

uint32_t SysFreHCLK  = 80000000UL; /* HCLK = MasterClock / 1 */
uint32_t SysFrePCLK0 = 40000000UL; /* PCLK0 = HCLK / 2 */
uint32_t SysFrePCLK1 = 40000000UL; /* PCLK1 = HCLK / 2 */
uint32_t SysFrePCLK2 = 40000000UL; /* PCLK2 = HCLK / 2 */
uint32_t SysFreTPIU  = 0UL; /* TPIUCLK : Disable */

/*
 *  Prototype of internal function
 */
static void ClockInit(void);
static void HwwdtDisable(void);


/*
 *  Setup the microcontroller system
 */
void SystemInit (void)
{
    HwwdtDisable();   /* Disable Hardware Watchdog */
    ClockInit();     /* Initialize Clock */
}
/*
 *  Initialize Clock
 */
static void ClockInit(void)
{
    /*set Main clock stabilization
    wait time to 2ms*/
    FM3_CRG->CSW_TMR = 0x79;
    /*Enable Main Oscilator*/
    FM3_CRG->SCM_CTL |= 1<<1;
    /*Wait stabilization end*/
    while(!(FM3_CRG->SCM_STR & 0x02));

    /* sub CLK enable */
    //FM3_CRG->SCM_CTL |= 0x08;				
    //while(!(FM3_CRG->SCM_STR & 0x08));

    /*Set PLL stabilization 
    wait time to 512uS*/
    FM3_CRG->PSW_TMR |= 2;
    /*Set PLL to 80MHz*/
    FM3_CRG->PLL_CTL1 = 0; /*K = 1, M=1*/
    FM3_CRG->PLL_CTL2 = 19; /*N = 20*/
    /*Enable PLL*/
    FM3_CRG->SCM_CTL |= 0x10;
    /*Set bus prescalers*/
    FM3_CRG->BSC_PSR = 0;           /*Base clock Prescaler 1:1*/
    FM3_CRG->APBC0_PSR |= 1;        /*APB0 clock Prescaler 1:2*/
    FM3_CRG->APBC1_PSR |= 1;        /*APB1 clock Prescaler 1:2*/
    FM3_CRG->APBC2_PSR |= 1;        /*APB2 clock Prescaler 1:2*/
    /*Wait PLL stabilizatoin end*/
    while(!(FM3_CRG->SCM_STR & 0x10));
    /*Select PLL for main clock*/
    FM3_CRG->SCM_CTL |= 2<<5; 
    /*Wait PLL to be connected*/
    while((FM3_CRG->SCM_STR & 0xe0) != 0x40);

}
/*
 *  Stop HW Watchdog Timer
 */
static void HwwdtDisable(void)
{
    /* UnLock (except WDG_CTL) */
    FM3_HWWDT->WDG_LCK = 0x1ACCE551;
    /* UnLock (WDG_CTL) */
    FM3_HWWDT->WDG_LCK = 0xE5331AAE;
    /* Disable WDG */
    FM3_HWWDT->WDG_CTL = 0x00;  
}
