// See LICENSE file for license details

#ifndef _FE300PRCI_DRIVER_H_
#define _FE300PRCI_DRIVER_H_

//__BEGIN_DECLS

#include <unistd.h>

typedef enum prci_freq_target {
  
  PRCI_FREQ_OVERSHOOT,
  PRCI_FREQ_CLOSEST,
  PRCI_FREQ_UNDERSHOOT

} PRCI_freq_target;

/* Measure and return the approximate frequency of the 
 * CPU, as given by measuring the mcycle counter against 
 * the mtime ticks.
 */
uint32_t PRCI_measure_mcycle_freq(uint32_t mtime_ticks, uint32_t mtime_freq);

/* Safely switch over to the HFROSC using the given div
 * and trim settings.
 */
void PRCI_use_hfrosc(int div, int trim);

/* Safely switch over to the 16MHz HFXOSC,
 * applying the finaldiv clock divider (1 is the lowest
 * legal value).
 */
void PRCI_use_hfxosc(uint32_t finaldiv);

/* Safely switch over to the PLL using the given
 * settings.
 * 
 * Note that not all combinations of the inputs are actually
 * legal, and this function does not check for their
 * legality ("safely" means that this function won't turn off
 * or glitch the clock the CPU is actually running off, but
 * doesn't protect against you making it too fast or slow.)
 */

void PRCI_use_pll(int refsel, int bypass,
			 int r, int f, int q, int finaldiv,
			 int hfroscdiv, int hfrosctrim);

/* Use the default clocks configured at reset.
 * This is ~16Mhz HFROSC and turns off the LFROSC
 * (on the current FE310 Dev Platforms, an external LFROSC is 
 * used as it is more power efficient).
 */
void PRCI_use_default_clocks();

/* This routine will adjust the HFROSC trim
 * while using HFROSC as the clock source, 
 * measure the resulting frequency, then
 * use it as the PLL clock source, 
 * in an attempt to get over, under, or close to the 
 * requested frequency. It returns the actual measured 
 * frequency. 
 *
 * Note that the requested frequency must be within the 
 * range supported by the PLL so not all values are 
 * achievable with this function, and not all 
 * are guaranteed to actually work. The PLL
 * is rated higher than the hardware.
 * 
 * There is no check on the desired f_cpu frequency, it
 * is up to the user to specify something reasonable.
 */

uint32_t PRCI_set_hfrosctrim_for_f_cpu(uint32_t f_cpu, PRCI_freq_target target);

//__END_DECLS

#endif
  
