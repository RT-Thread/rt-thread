// See LICENSE file for license details

#include "platform.h"

#ifdef PRCI_CTRL_ADDR
#include "fe300prci/fe300prci_driver.h"
#include <unistd.h>

#define rdmcycle(x)  {                     \
    uint32_t lo, hi, hi2;                  \
    __asm__ __volatile__ ("1:\n\t"             \
              "csrr %0, mcycleh\n\t"       \
              "csrr %1, mcycle\n\t"        \
              "csrr %2, mcycleh\n\t"        \
              "bne  %0, %2, 1b\n\t"         \
              : "=r" (hi), "=r" (lo), "=r" (hi2)) ; \
    *(x) = lo | ((uint64_t) hi << 32);              \
  }

uint32_t PRCI_measure_mcycle_freq(uint32_t mtime_ticks, uint32_t mtime_freq)
{

  uint32_t start_mtime = CLINT_REG(CLINT_MTIME);
  uint32_t end_mtime = start_mtime + mtime_ticks + 1;

  // Make sure we won't get rollover.
  while (end_mtime < start_mtime){
    start_mtime = CLINT_REG(CLINT_MTIME);
    end_mtime = start_mtime + mtime_ticks + 1;
  }

  // Don't start measuring until mtime edge.
  uint32_t tmp = start_mtime;
  do {
    start_mtime = CLINT_REG(CLINT_MTIME);
  } while (start_mtime == tmp);

  uint64_t start_mcycle;
  rdmcycle(&start_mcycle);

  while (CLINT_REG(CLINT_MTIME) < end_mtime) ;

  uint64_t end_mcycle;
  rdmcycle(&end_mcycle);
  uint32_t difference = (uint32_t) (end_mcycle - start_mcycle);

  uint64_t freq = ((uint64_t) difference * mtime_freq) / mtime_ticks;
  return (uint32_t) freq & 0xFFFFFFFF;

}


void PRCI_use_hfrosc(int div, int trim)
{
  // Make sure the HFROSC is running at its default setting
  // It is OK to change this even if we are running off of it.

  PRCI_REG(PRCI_HFROSCCFG) = (ROSC_DIV(div) | ROSC_TRIM(trim) | ROSC_EN(1));

  while ((PRCI_REG(PRCI_HFROSCCFG) & ROSC_RDY(1)) == 0);

  PRCI_REG(PRCI_PLLCFG) &= ~PLL_SEL(1);
}

void PRCI_use_pll(int refsel, int bypass,
             int r, int f, int q, int finaldiv,
             int hfroscdiv, int hfrosctrim)
{
  // Ensure that we aren't running off the PLL before we mess with it.
  if (PRCI_REG(PRCI_PLLCFG) & PLL_SEL(1)) {
    // Make sure the HFROSC is running at its default setting
    PRCI_use_hfrosc(4, 16);
  }

  // Set PLL Source to be HFXOSC if desired.
  uint32_t config_value = 0;

  config_value |= PLL_REFSEL(refsel);

  if (bypass) {
    // Bypass
    config_value |= PLL_BYPASS(1);

    PRCI_REG(PRCI_PLLCFG) = config_value;

    // If we don't have an HFXTAL, this doesn't really matter.
    // Set our Final output divide to divide-by-1:
    PRCI_REG(PRCI_PLLDIV) = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));
  } else {

    // To overclock, use the hfrosc
    if (hfrosctrim >= 0 && hfroscdiv >= 0) {
      PRCI_use_hfrosc(hfroscdiv, hfrosctrim);
    }

    // Set DIV Settings for PLL

    // (Legal values of f_REF are 6-48MHz)

    // Set DIVR to divide-by-2 to get 8MHz frequency
    // (legal values of f_R are 6-12 MHz)

    config_value |= PLL_BYPASS(1);
    config_value |= PLL_R(r);

    // Set DIVF to get 512Mhz frequncy
    // There is an implied multiply-by-2, 16Mhz.
    // So need to write 32-1
    // (legal values of f_F are 384-768 MHz)
    config_value |= PLL_F(f);

    // Set DIVQ to divide-by-2 to get 256 MHz frequency
    // (legal values of f_Q are 50-400Mhz)
    config_value |= PLL_Q(q);

    // Set our Final output divide to divide-by-1:
    if (finaldiv == 1){
      PRCI_REG(PRCI_PLLDIV) = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));
    } else {
      PRCI_REG(PRCI_PLLDIV) = (PLL_FINAL_DIV(finaldiv-1));
    }

    PRCI_REG(PRCI_PLLCFG) = config_value;

    // Un-Bypass the PLL.
    PRCI_REG(PRCI_PLLCFG) &= ~PLL_BYPASS(1);

    // Wait for PLL Lock
    // Note that the Lock signal can be glitchy.
    // Need to wait 100 us
    // RTC is running at 32kHz.
    // So wait 4 ticks of RTC.
    uint32_t now = CLINT_REG(CLINT_MTIME);
    while (CLINT_REG(CLINT_MTIME) - now < 4) ;

    // Now it is safe to check for PLL Lock
    while ((PRCI_REG(PRCI_PLLCFG) & PLL_LOCK(1)) == 0);

  }

  // Switch over to PLL Clock source
  PRCI_REG(PRCI_PLLCFG) |= PLL_SEL(1);

  // If we're running off HFXOSC, turn off the HFROSC to
  // save power.
  if (refsel) {
    PRCI_REG(PRCI_HFROSCCFG) &= ~ROSC_EN(1);
  }

}

void PRCI_use_default_clocks()
{
  // Turn off the LFROSC
  AON_REG(AON_LFROSC) &= ~ROSC_EN(1);

  // Use HFROSC
  PRCI_use_hfrosc(4, 16);
}

void PRCI_use_hfxosc(uint32_t finaldiv)
{

  PRCI_use_pll(1, // Use HFXTAL
           1, // Bypass = 1
           0, // PLL settings don't matter
           0, // PLL settings don't matter
           0, // PLL settings don't matter
           finaldiv,
           -1,
           -1);
}

// This is a generic function, which
// doesn't span the entire range of HFROSC settings.
// It only adjusts the trim, which can span a hundred MHz or so.
// This function does not check the legality of the PLL settings
// at all, and it is quite possible to configure invalid PLL settings
// this way.
// It returns the actual measured CPU frequency.

uint32_t PRCI_set_hfrosctrim_for_f_cpu(uint32_t f_cpu, PRCI_freq_target target )
{

  uint32_t hfrosctrim = 0;
  uint32_t hfroscdiv = 4;
  uint32_t prev_trim = 0;

  // In this function we use PLL settings which
  // will give us a 32x multiplier from the output
  // of the HFROSC source to the output of the
  // PLL. We first measure our HFROSC to get the
  // right trim, then finally use it as the PLL source.
  // We should really check here that the f_cpu
  // requested is something in the limit of the PLL. For
  // now that is up to the user.

  // This will undershoot for frequencies not divisible by 16.
  uint32_t desired_hfrosc_freq = (f_cpu/ 16);

  PRCI_use_hfrosc(hfroscdiv, hfrosctrim);

  // Ignore the first run (for icache reasons)
  uint32_t cpu_freq = PRCI_measure_mcycle_freq(3000, RTC_FREQ);

  cpu_freq = PRCI_measure_mcycle_freq(3000, RTC_FREQ);
  uint32_t prev_freq = cpu_freq;

  while ((cpu_freq < desired_hfrosc_freq) && (hfrosctrim < 0x1F)){
    prev_trim = hfrosctrim;
    prev_freq = cpu_freq;
    hfrosctrim ++;
    PRCI_use_hfrosc(hfroscdiv, hfrosctrim);
    cpu_freq = PRCI_measure_mcycle_freq(3000, RTC_FREQ);
  }

  // We couldn't go low enough
  if (prev_freq > desired_hfrosc_freq){
    PRCI_use_pll(0, 0, 1, 31, 1, 1, hfroscdiv, prev_trim);
    cpu_freq = PRCI_measure_mcycle_freq(1000, RTC_FREQ);
    return cpu_freq;
  }

  // We couldn't go high enough
  if (cpu_freq < desired_hfrosc_freq){
    PRCI_use_pll(0, 0, 1, 31, 1, 1, hfroscdiv, prev_trim);
    cpu_freq = PRCI_measure_mcycle_freq(1000, RTC_FREQ);
    return cpu_freq;
  }

  // Check for over/undershoot
  switch(target) {
  case(PRCI_FREQ_CLOSEST):
    if ((desired_hfrosc_freq - prev_freq) < (cpu_freq - desired_hfrosc_freq)) {
      PRCI_use_pll(0, 0, 1, 31, 1, 1, hfroscdiv, prev_trim);
    } else {
      PRCI_use_pll(0, 0, 1, 31, 1, 1, hfroscdiv, hfrosctrim);
    }
    break;
  case(PRCI_FREQ_UNDERSHOOT):
    PRCI_use_pll(0, 0, 1, 31, 1, 1, hfroscdiv, prev_trim);
    break;
  default:
    PRCI_use_pll(0, 0, 1, 31, 1, 1, hfroscdiv, hfrosctrim);
  }

  cpu_freq =  PRCI_measure_mcycle_freq(1000, RTC_FREQ);
  return cpu_freq;

}

#endif
