#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "platform.h"
#include "encoding.h"

extern int main(int argc, char** argv);
extern void SW_handler();

static unsigned long mtime_lo(void)
{
  return *(volatile unsigned long *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

#ifdef __riscv32

static uint32_t mtime_hi(void)
{
  return *(volatile uint32_t *)(CLINT_CTRL_ADDR + CLINT_MTIME + 4);
}

uint64_t get_timer_value()
{
  while (1) {
    uint32_t hi = mtime_hi();
    uint32_t lo = mtime_lo();
    if (hi == mtime_hi())
      return ((uint64_t)hi << 32) | lo;
  }
}

#else /* __riscv32 */

uint64_t get_timer_value()
{
  return mtime_lo();
}

#endif

unsigned long get_timer_freq()
{
  return 32768;
}

static void use_hfrosc(int div, int trim)
{
  // Make sure the HFROSC is running at its default setting
  PRCI_REG(PRCI_HFROSCCFG) = (ROSC_DIV(div) | ROSC_TRIM(trim) | ROSC_EN(1));
  while ((PRCI_REG(PRCI_HFROSCCFG) & ROSC_RDY(1)) == 0) ;
  PRCI_REG(PRCI_PLLCFG) &= ~PLL_SEL(1);
}

void use_pll(int refsel, int bypass, int r, int f, int q)
{
  // Ensure that we aren't running off the PLL before we mess with it.
  if (PRCI_REG(PRCI_PLLCFG) & PLL_SEL(1)) {
    // Make sure the HFROSC is running at its default setting
    use_hfrosc(4, 16);
  }

  // Set PLL Source to be HFXOSC if available.
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
    // In case we are executing from QSPI,
    // (which is quite likely) we need to
    // set the QSPI clock divider appropriately
    // before boosting the clock frequency.

    // Div = f_sck/2
    SPI0_REG(SPI_REG_SCKDIV) = 8;

    // Set DIV Settings for PLL
    // Both HFROSC and HFXOSC are modeled as ideal
    // 16MHz sources (assuming dividers are set properly for
    // HFROSC).
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
    PRCI_REG(PRCI_PLLDIV) = (PLL_FINAL_DIV_BY_1(1) | PLL_FINAL_DIV(0));

    PRCI_REG(PRCI_PLLCFG) = config_value;

    // Un-Bypass the PLL.
    PRCI_REG(PRCI_PLLCFG) &= ~PLL_BYPASS(1);

    // Wait for PLL Lock
    // Note that the Lock signal can be glitchy.
    // Need to wait 100 us
    // RTC is running at 32kHz.
    // So wait 4 ticks of RTC.
    uint32_t now = mtime_lo();
    while (mtime_lo() - now < 4) ;

    // Now it is safe to check for PLL Lock
    while ((PRCI_REG(PRCI_PLLCFG) & PLL_LOCK(1)) == 0) ;
  }

  // Switch over to PLL Clock source
  PRCI_REG(PRCI_PLLCFG) |= PLL_SEL(1);
}

void use_default_clocks()
{
  // Turn off the LFROSC
  AON_REG(AON_LFROSC) &= ~ROSC_EN(1);

  // Use HFROSC
  use_hfrosc(4, 16);
}

static unsigned long __attribute__((noinline)) measure_cpu_freq(size_t n)
{
  unsigned long start_mtime, delta_mtime;
  unsigned long mtime_freq = get_timer_freq();

  // Don't start measuruing until we see an mtime tick
  unsigned long tmp = mtime_lo();
  do {
    start_mtime = mtime_lo();
  } while (start_mtime == tmp);

  unsigned long start_mcycle = read_csr(mcycle);

  do {
    delta_mtime = mtime_lo() - start_mtime;
  } while (delta_mtime < n);

  unsigned long delta_mcycle = read_csr(mcycle) - start_mcycle;

  return (delta_mcycle / delta_mtime) * mtime_freq
         + ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;
}

unsigned long get_cpu_freq()
{
  static uint32_t cpu_freq;

  if (!cpu_freq) {
    // warm up I$
    measure_cpu_freq(1);
    // measure for real
    cpu_freq = measure_cpu_freq(10);
  }

  return cpu_freq;
}

static void uart_init(size_t baud_rate)
{
  GPIO_REG(GPIO_IOF_SEL) &= ~IOF0_UART0_MASK;
  GPIO_REG(GPIO_IOF_EN) |= IOF0_UART0_MASK;
  UART0_REG(UART_REG_DIV) = get_cpu_freq() / baud_rate - 1;
  UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
}



#ifdef USE_PLIC
extern void handle_m_ext_interrupt();
#endif

#ifdef USE_M_TIME
extern void handle_m_time_interrupt();
#endif

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
  if (0){
#ifdef USE_PLIC
    // External Machine-Level interrupt from PLIC
  } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_EXT)) {
    handle_m_ext_interrupt();
#endif
#ifdef USE_M_TIME
    // External Machine-Level interrupt from PLIC
  } else if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_TIMER)){
    handle_m_time_interrupt();
#endif
  }
  else {
    rt_kprintf("Unhandled Trap.\n");
  }
  return epc;
}

void _init()
{

  #ifndef NO_INIT
  use_default_clocks();
  use_pll(0, 0, 1, 31, 1);
  uart_init(115200);

  rt_kprintf("core freq at %ld Hz\n", get_cpu_freq());

  write_csr(mtvec, &SW_handler);
  if (read_csr(misa) & (1 << ('F' - 'A'))) { // if F extension is present
    write_csr(mstatus, MSTATUS_FS); // allow FPU instructions without trapping
    write_csr(fcsr, 0); // initialize rounding mode, undefined at reset
  }
  #endif

}

void _fini()
{
}
