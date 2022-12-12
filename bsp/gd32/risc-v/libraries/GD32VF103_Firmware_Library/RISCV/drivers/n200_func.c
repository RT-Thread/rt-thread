/* See LICENSE for license details. */
#include <gd32vf103.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if   defined (__ICCRISCV__)
    #include "compiler.h"
#elif defined ( __GNUC__ )
    #include <unistd.h>
#endif

#include "riscv_encoding.h"
#include "n200_func.h"

/* Configure PMP to make all the address space accesable and executable */
void pmp_open_all_space(void){
    /* Config entry0 addr to all 1s to make the range cover all space */
    asm volatile ("li x6, 0xffffffff":::"x6");
    asm volatile ("csrw pmpaddr0, x6":::);
    /* Config entry0 cfg to make it NAPOT address mode, and R/W/X okay */
    asm volatile ("li x6, 0x7f":::"x6");
    asm volatile ("csrw pmpcfg0, x6":::);
}

void switch_m2u_mode(void){
#if   defined (__ICCRISCV__)
    clear_csr (CSR_MSTATUS,MSTATUS_MPP);
#elif defined ( __GNUC__ )
    clear_csr (mstatus,MSTATUS_MPP);
#endif
    /* printf("\nIn the m2u function, the mstatus is 0x%x\n", read_csr(mstatus)); */
    /* printf("\nIn the m2u function, the mepc is 0x%x\n", read_csr(mepc)); */
#if defined ( __GNUC__ )
    asm volatile ("la x6, 1f    ":::"x6");
#endif
    asm volatile ("csrw mepc, x6":::);
    asm volatile ("mret":::);
    asm volatile ("1:":::);
}

uint32_t mtime_lo(void)
{
  return *(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME);
}


uint32_t mtime_hi(void)
{
  return *(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME + 4);
}

uint64_t get_timer_value(void)
{
  while (1) {
    uint32_t hi = mtime_hi();
    uint32_t lo = mtime_lo();
    if (hi == mtime_hi())
      return ((uint64_t)hi << 32) | lo;
  }
}

uint32_t get_timer_freq(void)
{
  return TIMER_FREQ;
}

uint64_t get_instret_value(void)
{
  while (1) {
#if   defined (__ICCRISCV__)
    uint32_t hi = read_csr(CSR_MINSTRETH);
    uint32_t lo = read_csr(CSR_MINSTRETH);
    if (hi == read_csr(CSR_MINSTRETH))
#elif defined ( __GNUC__ )
    uint32_t hi = read_csr(minstreth);
    uint32_t lo = read_csr(minstret);
    if (hi == read_csr(minstreth))
#endif

      return ((uint64_t)hi << 32) | lo;
  }
}

uint64_t get_cycle_value(void)
{
  while (1) {
#if   defined (__ICCRISCV__)
    uint32_t hi = read_csr(CSR_MCYCLEH);
    uint32_t lo = read_csr(CSR_MCYCLE);
    if (hi == read_csr(CSR_MCYCLEH))
#elif defined ( __GNUC__ )
    uint32_t hi = read_csr(mcycleh);
    uint32_t lo = read_csr(mcycle);
    if (hi == read_csr(mcycleh))
#endif

      return ((uint64_t)hi << 32) | lo;
  }
}

uint32_t __attribute__((noinline)) measure_cpu_freq(size_t n)
{
  uint32_t start_mtime, delta_mtime;
  uint32_t mtime_freq = get_timer_freq();

  /* Don't start measuruing until we see an mtime tick */
  uint32_t tmp = mtime_lo();
  do {
    start_mtime = mtime_lo();
  } while (start_mtime == tmp);

#if   defined (__ICCRISCV__)
  uint32_t start_mcycle = read_csr(CSR_MCYCLE);
#elif defined ( __GNUC__ )
  uint32_t start_mcycle = read_csr(mcycle);
#endif

  do {
    delta_mtime = mtime_lo() - start_mtime;
  } while (delta_mtime < n);

#if   defined (__ICCRISCV__)
  uint32_t delta_mcycle = read_csr(CSR_MCYCLE) - start_mcycle;
#elif defined ( __GNUC__ )
  uint32_t delta_mcycle = read_csr(mcycle) - start_mcycle;
#endif

  return (delta_mcycle / delta_mtime) * mtime_freq
         + ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;
}

uint32_t get_cpu_freq(void)
{
  uint32_t cpu_freq;

  /* warm up */
  measure_cpu_freq(1);
  /* measure for real */
  cpu_freq = measure_cpu_freq(100);

  return cpu_freq;
}

/* Note that there are no assertions or bounds checking on these */
/* parameter values. */
void eclic_init ( uint32_t num_irq )
{

  typedef volatile uint32_t vuint32_t;

  /* clear cfg register */
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_CFG_OFFSET)=0;

  /* clear minthresh register */
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_MTH_OFFSET)=0;

  /* clear all IP/IE/ATTR/CTRL bits for all interrupt sources */
  vuint32_t * ptr;

  vuint32_t * base = (vuint32_t*)(ECLIC_ADDR_BASE + ECLIC_INT_IP_OFFSET);
  vuint32_t * upper = (vuint32_t*)(base + num_irq*4);

  for (ptr = base; ptr < upper; ptr=ptr+4){
    *ptr = 0;
  }
}

void eclic_enable_interrupt (uint32_t source) {
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IE_OFFSET+source*4) = 1;
}

void eclic_disable_interrupt (uint32_t source){
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IE_OFFSET+source*4) = 0;
}

void eclic_set_pending(uint32_t source){
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IP_OFFSET+source*4) = 1;
}

void eclic_clear_pending(uint32_t source){
    *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IP_OFFSET+source*4) = 0;
}

void eclic_set_intctrl (uint32_t source, uint8_t intctrl){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTRL_OFFSET+source*4) = intctrl;
}

uint8_t eclic_get_intctrl  (uint32_t source){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTRL_OFFSET+source*4);
}

void eclic_set_intattr (uint32_t source, uint8_t intattr){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_ATTR_OFFSET+source*4) = intattr;
}

uint8_t eclic_get_intattr  (uint32_t source){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_ATTR_OFFSET+source*4);
}

void eclic_set_cliccfg (uint8_t cliccfg){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_CFG_OFFSET) = cliccfg;
}

uint8_t eclic_get_cliccfg (void){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_CFG_OFFSET);
}

void eclic_set_mth (uint8_t mth){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_MTH_OFFSET) = mth;
}

uint8_t eclic_get_mth (void){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_MTH_OFFSET);
}

/* sets nlbits */
void eclic_set_nlbits(uint8_t nlbits) {
  /* shift nlbits to correct position */
  uint8_t nlbits_shifted = nlbits << ECLIC_CFG_NLBITS_LSB;

  /* read the current cliccfg */
  uint8_t old_cliccfg = eclic_get_cliccfg();
  uint8_t new_cliccfg = (old_cliccfg & (~ECLIC_CFG_NLBITS_MASK)) | (ECLIC_CFG_NLBITS_MASK & nlbits_shifted);

  eclic_set_cliccfg(new_cliccfg);
}

/* get nlbits */
uint8_t eclic_get_nlbits(void) {
  /* extract nlbits */
  uint8_t nlbits = eclic_get_cliccfg();
  nlbits = (nlbits & ECLIC_CFG_NLBITS_MASK) >> ECLIC_CFG_NLBITS_LSB;
  return nlbits;
}

/* sets an interrupt level based encoding of nlbits and ECLICINTCTLBITS */
void eclic_set_irq_lvl(uint32_t source, uint8_t lvl) {
  /* extract nlbits */
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  /* shift lvl right to mask off unused bits */
  lvl = lvl >> (8-nlbits);
  /* shift lvl into correct bit position */
  lvl = lvl << (8-nlbits);

  /* write to clicintctrl */
  uint8_t current_intctrl = eclic_get_intctrl(source);
  /* shift intctrl left to mask off unused bits */
  current_intctrl = current_intctrl << nlbits;
  /* shift intctrl into correct bit position */
  current_intctrl = current_intctrl >> nlbits;

  eclic_set_intctrl(source, (current_intctrl | lvl));
}

/* gets an interrupt level based encoding of nlbits */
uint8_t eclic_get_irq_lvl(uint32_t source) {
  /* extract nlbits */
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  uint8_t intctrl = eclic_get_intctrl(source);

  /* shift intctrl */
  intctrl = intctrl >> (8-nlbits);
  /* shift intctrl */
  uint8_t lvl = intctrl << (8-nlbits);

  return lvl;
}

void eclic_set_irq_lvl_abs(uint32_t source, uint8_t lvl_abs) {
  /* extract nlbits */
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  /* shift lvl_abs into correct bit position */
  uint8_t lvl = lvl_abs << (8-nlbits);

  /* write to clicintctrl */
  uint8_t current_intctrl = eclic_get_intctrl(source);
  /* shift intctrl left to mask off unused bits */
  current_intctrl = current_intctrl << nlbits;
  /* shift intctrl into correct bit position */
  current_intctrl = current_intctrl >> nlbits;

  eclic_set_intctrl(source, (current_intctrl | lvl));
}

uint8_t eclic_get_irq_lvl_abs(uint32_t source) {
  /* extract nlbits */
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  uint8_t intctrl = eclic_get_intctrl(source);

  /* shift intctrl */
  intctrl = intctrl >> (8-nlbits);
  /* shift intctrl */
  uint8_t lvl_abs = intctrl;

  return lvl_abs;
}

/* sets an interrupt priority based encoding of nlbits and ECLICINTCTLBITS */
uint8_t eclic_set_irq_priority(uint32_t source, uint8_t priority) {
    /* extract nlbits */
    uint8_t nlbits = eclic_get_nlbits();
    if (nlbits >= ECLICINTCTLBITS) {
        nlbits = ECLICINTCTLBITS;
        return 0;
    }

    /* shift priority into correct bit position */
    priority = priority << (8 - ECLICINTCTLBITS);

    /* write to eclicintctrl */
    uint8_t current_intctrl = eclic_get_intctrl(source);
    /* shift intctrl right to mask off unused bits */
    current_intctrl = current_intctrl >> (8-nlbits);
    /* shift intctrl into correct bit position */
    current_intctrl = current_intctrl << (8-nlbits);

    eclic_set_intctrl(source, (current_intctrl | priority));

    return priority;
}

/* gets an interrupt priority based encoding of nlbits */
uint8_t eclic_get_irq_priority(uint32_t source) {
    /* extract nlbits */
    uint8_t nlbits = eclic_get_nlbits();
    if (nlbits > ECLICINTCTLBITS) {
          nlbits = ECLICINTCTLBITS;
    }

    uint8_t intctrl = eclic_get_intctrl(source);

    /* shift intctrl */
    intctrl = intctrl << nlbits;
    /* shift intctrl */
    uint8_t priority = intctrl >> (nlbits+(8 - ECLICINTCTLBITS));

    return priority;
}

void eclic_mode_enable() {
#if   defined (__ICCRISCV__)
  uint32_t mtvec_value = read_csr(CSR_MTVEC);
  mtvec_value = mtvec_value & 0xFFFFFFC0;
  mtvec_value = mtvec_value | 0x00000003;
  write_csr(CSR_MTVEC,mtvec_value);
#elif defined ( __GNUC__ )
  uint32_t mtvec_value = read_csr(mtvec);
  mtvec_value = mtvec_value & 0xFFFFFFC0;
  mtvec_value = mtvec_value | 0x00000003;
  write_csr(mtvec,mtvec_value);
#endif

}

/* sets vector-mode or non-vector mode */
void eclic_set_vmode(uint32_t source) {
  /* read the current attr */
  uint8_t old_intattr = eclic_get_intattr(source);
      /*  Keep other bits unchanged and only set the LSB bit */
  uint8_t new_intattr = (old_intattr | 0x1);

  eclic_set_intattr(source,new_intattr);
}

void eclic_set_nonvmode(uint32_t source) {
  /* read the current attr */
  uint8_t old_intattr = eclic_get_intattr(source);
      /* Keep other bits unchanged and only clear the LSB bit*/
  uint8_t new_intattr = (old_intattr & (~0x1));

  eclic_set_intattr(source,new_intattr);
}

/* sets interrupt as level sensitive
Bit 1, trig[0], is defined as "edge-triggered" (0: level-triggered, 1: edge-triggered);
Bit 2, trig[1], is defined as "negative-edge" (0: positive-edge, 1: negative-edge).*/

void eclic_set_level_trig(uint32_t source) {
  /* read the current attr */
  uint8_t old_intattr = eclic_get_intattr(source);
      /* Keep other bits unchanged and only clear the bit 1 */
  uint8_t new_intattr = (old_intattr & (~0x2));

  eclic_set_intattr(source,new_intattr);
}

void eclic_set_posedge_trig(uint32_t source) {
  /* read the current attr */
  uint8_t old_intattr = eclic_get_intattr(source);
      /* Keep other bits unchanged and only set the bit 1 */
  uint8_t new_intattr = (old_intattr | 0x2);
      /* Keep other bits unchanged and only clear the bit 2 */
  new_intattr = (old_intattr & (~0x4));

  eclic_set_intattr(source,new_intattr);
}

void eclic_set_negedge_trig(uint32_t source) {
  /*read the current attr */
  uint8_t old_intattr = eclic_get_intattr(source);
      /* Keep other bits unchanged and only set the bit 1*/
  uint8_t new_intattr = (old_intattr | 0x2);
      /* Keep other bits unchanged and only set the bit 2*/
  new_intattr = (old_intattr | 0x4);

  eclic_set_intattr(source,new_intattr);
}
