/*******************************************************************************
* Copyright (C) 2013 Spansion LLC. All Rights Reserved. 
*
* This software is owned and published by: 
* Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with Spansion 
* components. This software is licensed by Spansion to be adapted only 
* for use in systems utilizing Spansion components. Spansion shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein.  Spansion is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.  
*/
/**
 ******************************************************************************
 ** \file system_mb9abxxx.c
 **
 ** FM3 system initialization functions
 ** All adjustments can be done in belonging header file.
 **
 ** History:
 ** 2013-01-21  0.1  MWi  AI: Unification to be done
 ** 2013-01-23  0.2  MWi  mcu.h inclusion changed to pdl.h
 ** 2013-06-28  0.3  EH   Added Trace Buffer enable
 ******************************************************************************/

#include "mcu.h"

/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
uint32_t SystemCoreClock = __HCLK;

/**
 ******************************************************************************
 ** \brief  Update the System Core Clock with current core Clock retrieved from
 ** cpu registers.
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemCoreClockUpdate (void) {
  uint32_t masterClk;
  uint32_t u32RegisterRead; // Workaround variable for MISRA C rule conformance

  switch ((FM4_CRG->SCM_CTL >> 5U) & 0x07U) {
    case 0u:                                 /* internal High-speed Cr osc.    */
      masterClk = __CLKHC;
      break;

    case 1u:                                 /* external main osc.             */
      masterClk = __CLKMO;
      break;

    case 2u:                                 /* PLL clock                      */
  // Workaround for preventing MISRA C:1998 Rule 46 (MISRA C:2004 Rule 12.2)
  // violation:
  //   "Unordered accesses to a volatile location"
      u32RegisterRead = (__CLKMO  * (((uint32_t)(FM4_CRG->PLL_CTL2) & 0x3Fu) + 1u));
      masterClk = (u32RegisterRead / ((((uint32_t)(FM4_CRG->PLL_CTL1) >> 4ul) & 0x0Fu) + 1u));
      break;

    case 4u:                                 /* internal Low-speed CR osc.     */
      masterClk = __CLKLC;
      break;

    case 5u:                                 /* external Sub osc.              */
      masterClk = __CLKSO;
      break;

    default:
      masterClk = 0ul;
      break;
  }

  switch (FM4_CRG->BSC_PSR & 0x07u) {
    case 0u:
      SystemCoreClock = masterClk;
      break;

    case 1u:
      SystemCoreClock = masterClk / 2u;
      break;

    case 2u:
      SystemCoreClock = masterClk / 3u;
      break;

    case 3u:
      SystemCoreClock = masterClk / 4u;
      break;

    case 4u:
      SystemCoreClock = masterClk / 6u;
      break;

    case 5u:
      SystemCoreClock = masterClk /8u;
      break;

    case 6u:
      SystemCoreClock = masterClk /16u;
      break;

    default:
      SystemCoreClock = 0ul;
      break;
  }

}

/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit (void) {

  static uint8_t u8IoRegisterRead;  // Workaround variable for MISRA C rule conformance
  
#if (HWWD_DISABLE)                                 /* HW Watchdog Disable */
  FM4_HWWDT->WDG_LCK = 0x1ACCE551u;                /* HW Watchdog Unlock */
  FM4_HWWDT->WDG_LCK = 0xE5331AAEu;
  FM4_HWWDT->WDG_CTL = 0u;                         /* HW Watchdog stop */
#endif

#if (TRACE_BUFFER_ENABLE)
  FM4_FLASH_IF->FBFCR = 0x01;                      /* Trace Buffer enable */
#endif

#if (CLOCK_SETUP)                                  /* Clock Setup */
  FM4_CRG->BSC_PSR   = (uint8_t)BSC_PSR_Val;                 /* set System Clock presacaler */
  FM4_CRG->APBC0_PSR = (uint8_t)APBC0_PSR_Val;               /* set APB0 presacaler */
  FM4_CRG->APBC1_PSR = (uint8_t)APBC1_PSR_Val;               /* set APB1 presacaler */
  FM4_CRG->APBC2_PSR = (uint8_t)APBC2_PSR_Val;               /* set APB2 presacaler */
  FM4_CRG->SWC_PSR   = (uint8_t)(SWC_PSR_Val | (1ul << 7u)); /* set SW Watchdog presacaler */
  FM4_CRG->TTC_PSR   = (uint8_t)TTC_PSR_Val;                 /* set Trace Clock presacaler */

  FM4_CRG->CSW_TMR   = (uint8_t)CSW_TMR_Val;                 /* set oscillation stabilization wait time */
  
  if (SCM_CTL_Val & (1ul << 1u)) {                 /* Main clock oscillator enabled ? */
    FM4_CRG->SCM_CTL |= (uint8_t)(1ul << 1u);            /* enable main oscillator */ 
    
    while (!((FM4_CRG->SCM_STR) & (uint8_t)(1ul << 1u))) /* wait for Main clock oscillation stable */ 
    {}
  }
  
  if (SCM_CTL_Val & (1UL << 3)) {                    /* Sub clock oscillator enabled ? */
    // Initialize VBAT (Temporary process)
    FM4_RTC->VDET = 0x00;
    FM4_RTC->VBPFR = 0x1C;
    FM4_RTC->CCB = 0x10;
    FM4_RTC->CCS = 0x08;

    // VB_CLK is less or equal to 1MHz (Temporary process)
    FM4_RTC->VB_CLKDIV = 0x4E;
    FM4_RTC->BOOST = 0x03;

    // Enable SUB CLK oscilation (Temporary process)
    FM4_RTC->WTOSCCNT_f.SOSCEX  = 0;
    FM4_RTC->WTOSCCNT_f.SOSCNTL = 1;

    // Transmit to VBAT domain (Temporary process)
    FM4_RTC->WTCR20_f.PWRITE = 1;

    // Wait to complete transmission
    while(0 != FM4_RTC->WTCR10_f.TRANS)

    FM4_CRG->SCM_CTL |= (1UL << 3);                /* enable sub oscillator */ 
    while (!(FM4_CRG->SCM_STR & (1UL << 3)));      /* wait for Sub clock oscillation stable */
  }

  FM4_CRG->PSW_TMR   =  (uint8_t)PSW_TMR_Val;                /* set PLL stabilization wait time */
  FM4_CRG->PLL_CTL1  = (uint8_t) PLL_CTL1_Val;               /* set PLLM and PLLK */
  FM4_CRG->PLL_CTL2  =  (uint8_t)PLL_CTL2_Val;               /* set PLLN          */
  
  if (SCM_CTL_Val &  (uint8_t)(1ul << 4u)) {                    /* PLL enabled ? */
    FM4_CRG->SCM_CTL  |=  (uint8_t)(1ul << 4u);               /* enable PLL */ 
    while (!(FM4_CRG->SCM_STR &  (uint8_t)(1ul << 4u)))      /* wait for PLL stable */
    {}
  }

  FM4_CRG->SCM_CTL  |=  (uint8_t)(SCM_CTL_Val & 0xE0u);       /* Set Master Clock switch */ 
  
  // Workaround for preventing MISRA C:1998 Rule 46 (MISRA C:2004 Rule 12.2)
  // violations:
  //   "Unordered reads and writes to or from same location" and
  //   "Unordered accesses to a volatile location"
  do                                              
  {                                               
    u8IoRegisterRead = (FM4_CRG->SCM_CTL & 0xE0u); 
  }while ((FM4_CRG->SCM_STR & 0xE0u) != u8IoRegisterRead);
#endif // (CLOCK_SETUP)
  
#if (CR_TRIM_SETUP)
  /* CR Trimming Data  */
  if( 0x000003FFu != (FM4_FLASH_IF->CRTRMM & 0x000003FFu) )
  {
    /* UnLock (MCR_FTRM) */
    FM4_CRTRIM->MCR_RLR =  (uint32_t)0x1ACCE554u;
    /* Set MCR_FTRM */
    FM4_CRTRIM->MCR_FTRM = (uint16_t)FM4_FLASH_IF->CRTRMM;
    /* Lock (MCR_FTRM) */
    FM4_CRTRIM->MCR_RLR =  (uint32_t)0x00000000u;
  }
#endif // (CR_TRIM_SETUP)
}



