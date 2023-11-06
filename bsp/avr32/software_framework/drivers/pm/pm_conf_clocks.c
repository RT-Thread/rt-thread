/*****************************************************************************
 *
 * \file
 *
 * \brief Power Manager clocks configuration helper.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 *****************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#include <string.h>
#include "compiler.h"
#include "pm.h"

extern void flashc_set_wait_state(unsigned int wait_state);
#if (defined AVR32_FLASHC_210_H_INCLUDED)
extern void flashc_issue_command(unsigned int command, int page_number);
#endif


#define PM_MAX_MUL                ((1 << AVR32_PM_PLL0_PLLMUL_SIZE) - 1)


int pm_configure_clocks(pm_freq_param_t *param)
{
  // Supported frequencies:
  // Fosc0 mul div PLL div2_en cpu_f pba_f   Comment
  //  12   15   1  192     1     12    12
  //  12    9   3   40     1     20    20    PLL out of spec
  //  12   15   1  192     1     24    12
  //  12    9   1  120     1     30    15
  //  12    9   3   40     0     40    20    PLL out of spec
  //  12   15   1  192     1     48    12
  //  12   15   1  192     1     48    24
  //  12    8   1  108     1     54    27
  //  12    9   1  120     1     60    15
  //  12    9   1  120     1     60    30
  //  12   10   1  132     1     66    16.5
  //
  unsigned long in_cpu_f  = param->cpu_f;
  unsigned long in_osc0_f = param->osc0_f;
  unsigned long mul, div, div2_en = 0, div2_cpu = 0, div2_pba = 0;
  unsigned long pll_freq, rest;
  bool b_div2_pba, b_div2_cpu;

  // Switch to external Oscillator 0
  pm_switch_to_osc0(&AVR32_PM, in_osc0_f, param->osc0_startup);

  // Start with CPU freq config
  if (in_cpu_f == in_osc0_f)
  {
    param->cpu_f = in_osc0_f;
    param->pba_f = in_osc0_f;
    return PM_FREQ_STATUS_OK;
  }
  else if (in_cpu_f < in_osc0_f)
  {
    // TBD
  }

  rest = in_cpu_f % in_osc0_f;

  for (div = 1; div < 32; div++)
  {
    if ((div * rest) % in_osc0_f == 0)
      break;
  }
  if (div == 32)
    return PM_FREQ_STATUS_FAIL;

  mul = (in_cpu_f * div) / in_osc0_f;

  if (mul > PM_MAX_MUL)
    return PM_FREQ_STATUS_FAIL;

  // export 2power from PLL div to div2_cpu
  while (!(div % 2))
  {
    div /= 2;
    div2_cpu++;
  }

  // Here we know the mul and div parameter of the PLL config.
  // . Check out if the PLL has a valid in_cpu_f.
  // . Try to have for the PLL frequency (VCO output) the highest possible value
  //   to reduce jitter.
  while (in_osc0_f * 2 * mul / div < AVR32_PM_PLL_VCO_RANGE0_MAX_FREQ)
  {
    if (2 * mul > PM_MAX_MUL)
      break;
    mul *= 2;
    div2_cpu++;
  }

  if (div2_cpu != 0)
  {
    div2_cpu--;
    div2_en = 1;
  }

  pll_freq = in_osc0_f * mul / (div * (1 << div2_en));

  // Update real CPU Frequency
  param->cpu_f = pll_freq / (1 << div2_cpu);
  mul--;

  pm_pll_setup(&AVR32_PM
  , 0   // pll
  , mul // mul
  , div // div
  , 0   // osc
  , 16  // lockcount
  );

  pm_pll_set_option(&AVR32_PM
  , 0 // pll
  // PLL clock is lower than 160MHz: need to set pllopt.
  , (pll_freq < AVR32_PM_PLL_VCO_RANGE0_MIN_FREQ) ? 1 : 0 // pll_freq
  , div2_en // pll_div2
  , 0 // pll_wbwdisable
  );

  rest = pll_freq;
  while (rest > AVR32_PM_PBA_MAX_FREQ ||
         rest != param->pba_f)
  {
    div2_pba++;
    rest = pll_freq / (1 << div2_pba);
    if (rest < param->pba_f)
      break;
  }

  // Update real PBA Frequency
  param->pba_f = pll_freq / (1 << div2_pba);

  // Enable PLL0
  pm_pll_enable(&AVR32_PM, 0);

  // Wait for PLL0 locked
  pm_wait_for_pll0_locked(&AVR32_PM);

  if (div2_cpu)
  {
    b_div2_cpu = true;
    div2_cpu--;
  }
  else
    b_div2_cpu = false;

  if (div2_pba)
  {
    b_div2_pba = true;
    div2_pba--;
  }
  else
    b_div2_pba = false;

  pm_cksel(&AVR32_PM
  , b_div2_pba, div2_pba // PBA
  , b_div2_cpu, div2_cpu // PBB
  , b_div2_cpu, div2_cpu // HSB
  );

  if (param->cpu_f > AVR32_FLASHC_FWS_0_MAX_FREQ)
  {
    flashc_set_wait_state(1);
#if (defined AVR32_FLASHC_210_H_INCLUDED)
    if (param->cpu_f > AVR32_FLASHC_HSEN_FWS_1_MAX_FREQ)
      flashc_issue_command(AVR32_FLASHC_FCMD_CMD_HSEN, -1);
    else
      flashc_issue_command(AVR32_FLASHC_FCMD_CMD_HSDIS, -1);
#endif
  }
  else
  {
    flashc_set_wait_state(0);
#if (defined AVR32_FLASHC_210_H_INCLUDED)
    if (param->cpu_f > AVR32_FLASHC_HSEN_FWS_0_MAX_FREQ)
      flashc_issue_command(AVR32_FLASHC_FCMD_CMD_HSEN, -1);
    else
      flashc_issue_command(AVR32_FLASHC_FCMD_CMD_HSDIS, -1);
#endif
  }

  pm_switch_to_clock(&AVR32_PM, AVR32_PM_MCCTRL_MCSEL_PLL0);

  return PM_FREQ_STATUS_OK;
}


void pm_configure_usb_clock(void)
{
#if UC3A3

  // Setup USB GCLK.
  pm_gc_setup(&AVR32_PM, AVR32_PM_GCLK_USBB, // gc
                  0,                  // osc_or_pll: use Osc (if 0) or PLL (if 1)
                  0,                  // pll_osc: select Osc0/PLL0 or Osc1/PLL1
                  0,                  // diven
                  0);                 // div

  // Enable USB GCLK.
  pm_gc_enable(&AVR32_PM, AVR32_PM_GCLK_USBB);
#else
  // Use 12MHz from OSC0 and generate 96 MHz
  pm_pll_setup(&AVR32_PM, 1,  // pll.
	  7,   // mul.
	  1,   // div.
	  0,   // osc.
	  16); // lockcount.

  pm_pll_set_option(&AVR32_PM, 1, // pll.
	  1,  // pll_freq: choose the range 80-180MHz.
	  1,  // pll_div2.
	  0); // pll_wbwdisable.

  // start PLL1 and wait forl lock
  pm_pll_enable(&AVR32_PM, 1);

  // Wait for PLL1 locked.
  pm_wait_for_pll1_locked(&AVR32_PM);

  pm_gc_setup(&AVR32_PM, AVR32_PM_GCLK_USBB,  // gc.
            1,  // osc_or_pll: use Osc (if 0) or PLL (if 1).
            1,  // pll_osc: select Osc0/PLL0 or Osc1/PLL1.
            0,  // diven.
            0); // div.
  pm_gc_enable(&AVR32_PM, AVR32_PM_GCLK_USBB);
#endif
}
