/**
  **************************************************************************
  * @file     system_at32f425.c
  * @brief    contains all the functions for cmsis cortex-m4 system source file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F425_system
  * @{
  */

#include "at32f425.h"

/** @addtogroup AT32F425_system_private_defines
  * @{
  */
#define VECT_TAB_OFFSET                  0x0 /*!< vector table base offset field. this value must be a multiple of 0x200. */
/**
  * @}
  */

/** @addtogroup AT32F425_system_private_variables
  * @{
  */
unsigned int system_core_clock           = HICK_VALUE; /*!< system clock frequency (core clock) */
/**
  * @}
  */

/** @addtogroup AT32F425_system_private_functions
  * @{
  */

/**
  * @brief  setup the microcontroller system
  *         initialize the flash interface.
  * @note   this function should be used only after reset.
  * @param  none
  * @retval none
  */
void SystemInit (void)
{
  /* reset the crm clock configuration to the default reset state(for debug purpose) */
  /* set hicken bit */
  CRM->ctrl_bit.hicken = TRUE;

  /* wait hick stable */
  while(CRM->ctrl_bit.hickstbl != SET);

  /* hick used as system clock */
  CRM->cfg_bit.sclksel = CRM_SCLK_HICK;

  /* wait sclk switch status */
  while(CRM->cfg_bit.sclksts != CRM_SCLK_HICK);

  /* reset hexten, hextbyps, cfden and pllen bits */
  CRM->ctrl &= ~(0x010D0000U);

  /* reset cfg register, include sclk switch, ahbdiv, apb1div, apb2div, adcdiv,
     clkout pllrcs, pllhextdiv, pllmult, usbdiv and pllrange bits */
  CRM->cfg = 0;

  /* reset pllfr, pllms, pllns and pllfref bits */
  CRM->pll = (0x00001F10U);

  /* reset clkout[3], usbbufs, hickdiv, clkoutdiv */
  CRM->misc1 = 0x00100000;

  /* disable all interrupts enable and clear pending bits  */
  CRM->clkint = 0x009F0000;

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE  | VECT_TAB_OFFSET;  /* vector table relocation in internal sram. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;  /* vector table relocation in internal flash. */
#endif
}

/**
  * @brief  update system_core_clock variable according to clock register values.
  *         the system_core_clock variable contains the core clock (hclk), it can
  *         be used by the user application to setup the systick timer or configure
  *         other parameters.
  * @param  none
  * @retval none
  */
void system_core_clock_update(void)
{
  uint32_t pll_mult = 0, pll_mult_h = 0, pll_clock_source = 0, temp = 0, div_value = 0;
  uint32_t pllrcsfreq = 0, pll_ms = 0, pll_ns = 0, pll_fr = 0;
  crm_sclk_type sclk_source;

  static const uint8_t sys_ahb_div_table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

  /* get sclk source */
  sclk_source = crm_sysclk_switch_status_get();

  switch(sclk_source)
  {
    case CRM_SCLK_HICK:
      if(((CRM->misc2_bit.hick_to_sclk) != RESET) && ((CRM->misc1_bit.hickdiv) != RESET))
        system_core_clock = HICK_VALUE * 6;
      else
        system_core_clock = HICK_VALUE;
      break;
    case CRM_SCLK_HEXT:
      system_core_clock = HEXT_VALUE;
      break;
    case CRM_SCLK_PLL:
      pll_clock_source = CRM->cfg_bit.pllrcs;
      if(CRM->pll_bit.pllcfgen == FALSE)
      {
        /* get multiplication factor */
        pll_mult = CRM->cfg_bit.pllmult_l;
        pll_mult_h = CRM->cfg_bit.pllmult_h;
        /* process high bits */
        if((pll_mult_h != 0U) || (pll_mult == 15U)){
            pll_mult += ((16U * pll_mult_h) + 1U);
        }
        else
        {
            pll_mult += 2U;
        }

        if (pll_clock_source == 0x00)
        {
          /* hick divided by 2 selected as pll clock entry */
          system_core_clock = (HICK_VALUE >> 1) * pll_mult;
        }
        else
        {
          /* hext selected as pll clock entry */
          if (CRM->cfg_bit.pllhextdiv != RESET)
          {
            /* hext clock divided by 2 */
            system_core_clock = (HEXT_VALUE / 2) * pll_mult;
          }
          else
          {
            system_core_clock = HEXT_VALUE * pll_mult;
          }
        }
      }
      else
      {
        pll_ms = CRM->pll_bit.pllms;
        pll_ns = CRM->pll_bit.pllns;
        pll_fr = CRM->pll_bit.pllfr;

        if (pll_clock_source == 0x00)
        {
          /* hick divided by 2 selected as pll clock entry */
          pllrcsfreq = (HICK_VALUE >> 1);
        }
        else
        {
          /* hext selected as pll clock entry */
          if (CRM->cfg_bit.pllhextdiv != RESET)
          {
            /* hext clock divided by 2 */
            pllrcsfreq = (HEXT_VALUE / 2);
          }
          else
          {
            pllrcsfreq = HEXT_VALUE;
          }
        }
        system_core_clock = (uint32_t)(((uint64_t)pllrcsfreq * pll_ns) / (pll_ms * (0x1 << pll_fr)));
      }
      break;
    default:
      system_core_clock = HICK_VALUE;
      break;
  }

  /* compute sclk, ahbclk frequency */
  /* get ahb division */
  temp = CRM->cfg_bit.ahbdiv;
  div_value = sys_ahb_div_table[temp];
  /* ahbclk frequency */
  system_core_clock = system_core_clock >> div_value;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

