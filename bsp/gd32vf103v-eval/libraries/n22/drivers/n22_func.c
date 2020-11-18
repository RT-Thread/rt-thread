// See LICENSE for license details.
#include <gd32vf103.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "riscv_encoding.h"
#include "n22_func.h"

void switch_m2u_mode() {
    clear_csr(mstatus, MSTATUS_MPP);
    //printf("\nIn the m2u function, the mstatus is 0x%x\n", read_csr(mstatus));
    //printf("\nIn the m2u function, the mepc is 0x%x\n", read_csr(mepc));
    asm volatile ("la x6, 1f    ":::"x6");
    asm volatile ("csrw mepc, x6":::);
    asm volatile ("mret":::);
    asm volatile ("1:":::);
}

uint32_t mtime_lo(void) {
    return *(volatile uint32_t *) (TMR_CTRL_ADDR + TMR_MTIME);
}

uint32_t mtime_hi(void) {
    return *(volatile uint32_t *) (TMR_CTRL_ADDR + TMR_MTIME + 4);
}

void enable_timer_interrupt(void) {
    *(volatile uint32_t *) (TMR_CTRL_ADDR + TMR_MTIME + 0xffc) = 1;
}

void clear_timer_interrupt(void) {
    *(volatile uint32_t *) (TMR_CTRL_ADDR + TMR_MTIME + 0xffc) = 0;
}

void close_timer(void) {
    *(volatile uint32_t *) (TMR_CTRL_ADDR + TMR_MTIME + 0xff8) = 1;
}

void open_timer(void) {
    *(volatile uint32_t *) (TMR_CTRL_ADDR + TMR_MTIME + 0xff8) = 0;
}

uint64_t get_timer_value() {
    while (1) {
        uint32_t hi = mtime_hi();
        uint32_t lo = mtime_lo();

        if (hi == mtime_hi())
            return ((uint64_t) hi << 32) | lo;
    }
}

uint32_t get_timer_freq() {
    return TMR_FREQ;
}

uint64_t get_instret_value() {
    while (1) {
        uint32_t hi = read_csr(minstreth);
        uint32_t lo = read_csr(minstret);
        if (hi == read_csr(minstreth))
            return ((uint64_t) hi << 32) | lo;
    }
}

uint64_t get_cycle_value() {
    while (1) {
        uint32_t hi = read_csr(mcycleh);
        uint32_t lo = read_csr(mcycle);
        if (hi == read_csr(mcycleh))
            return ((uint64_t) hi << 32) | lo;
    }
}
// Note that there are no assertions or bounds checking on these
// parameter values.

void eclic_init(uint32_t num_irq) {
    typedef volatile uint32_t vuint32_t;

    //clear cfg register 
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_CFG_OFFSET) = 0;

    //clear minthresh register 
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_MTH_OFFSET) = 0;

    //clear all IP/IE/ATTR/CTRL bits for all interrupt sources
    vuint32_t * ptr;

    vuint32_t * base = (vuint32_t*) (ECLIC_ADDR_BASE + ECLIC_INT_IP_OFFSET);
    vuint32_t * upper = (vuint32_t*) (base + num_irq * 4);

    for (ptr = base; ptr < upper; ptr = ptr + 4) {
        *ptr = 0;
    }
    eclic_set_nlbits(ECLIC_GROUP_LEVEL2_PRIO2);
}

void eclic_enable_interrupt(uint32_t source) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_IE_OFFSET + source * 4) =
            1;
}

void eclic_disable_interrupt(uint32_t source) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_IE_OFFSET + source * 4) =
            0;
}

void eclic_set_pending(uint32_t source) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_IP_OFFSET + source * 4) =
            1;
}

void eclic_clear_pending(uint32_t source) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_IP_OFFSET + source * 4) =
            0;
}

void eclic_set_intctrl(uint32_t source, uint8_t intctrl) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_CTRL_OFFSET + source * 4) =
            intctrl;
}

uint8_t eclic_get_intctrl(uint32_t source) {
    return *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_CTRL_OFFSET
            + source * 4);
}

void eclic_set_intattr(uint32_t source, uint8_t intattr) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_ATTR_OFFSET + source * 4) =
            intattr;
}

uint8_t eclic_get_intattr(uint32_t source) {
    return *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_INT_ATTR_OFFSET
            + source * 4);
}

void eclic_set_ecliccfg(uint8_t ecliccfg) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_CFG_OFFSET) = ecliccfg;
}

uint8_t eclic_get_ecliccfg() {
    return *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_CFG_OFFSET);
}

void eclic_set_mth(uint8_t mth) {
    *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_MTH_OFFSET) = mth;
}

uint8_t eclic_get_mth() {
    return *(volatile uint8_t*) (ECLIC_ADDR_BASE + ECLIC_MTH_OFFSET);
}

void eclic_set_nlbits(uint8_t nlbits) {
    //shift nlbits to correct position
    uint8_t nlbits_shifted = nlbits << ECLIC_CFG_NLBITS_LSB;

    //read the current ecliccfg
    uint8_t old_ecliccfg = eclic_get_ecliccfg();
    uint8_t new_ecliccfg = (old_ecliccfg & (~ECLIC_CFG_NLBITS_MASK))
            | (ECLIC_CFG_NLBITS_MASK & nlbits_shifted);

    eclic_set_ecliccfg(new_ecliccfg);
}

uint8_t eclic_get_nlbits(void) {
    //extract nlbits
    uint8_t nlbits = eclic_get_ecliccfg();
    nlbits = (nlbits & ECLIC_CFG_NLBITS_MASK) >> ECLIC_CFG_NLBITS_LSB;
    return nlbits;
}

//sets an interrupt level based encoding of nlbits and ECLICINTCTLBITS
uint8_t eclic_set_int_level(uint32_t source, uint8_t level) {
    //extract nlbits
    uint8_t nlbits = eclic_get_nlbits();
    if (nlbits > ECLICINTCTLBITS) {
        nlbits = ECLICINTCTLBITS;
    }

    //shift level into correct bit position
    level = level << (8 - nlbits);

    //write to eclicintctrl
    uint8_t current_intctrl = eclic_get_intctrl(source);
    //shift intctrl left to mask off unused bits
    current_intctrl = current_intctrl << nlbits;
    //shift intctrl into correct bit position
    current_intctrl = current_intctrl >> nlbits;

    eclic_set_intctrl(source, (current_intctrl | level));

    return level;
}

//gets an interrupt level based encoding of nlbits
uint8_t eclic_get_int_level(uint32_t source) {
    //extract nlbits
    uint8_t nlbits = eclic_get_nlbits();
    if (nlbits > ECLICINTCTLBITS) {
        nlbits = ECLICINTCTLBITS;
    }

    uint8_t intctrl = eclic_get_intctrl(source);

    //shift intctrl
    intctrl = intctrl >> (8 - nlbits);
    //shift intctrl
    uint8_t level = intctrl << (8 - nlbits);

    return level;
}

//sets an interrupt priority based encoding of nlbits and ECLICINTCTLBITS
uint8_t eclic_set_int_priority(uint32_t source, uint8_t priority) {
    //extract nlbits
    uint8_t nlbits = eclic_get_nlbits();
    if (nlbits >= ECLICINTCTLBITS) {
        nlbits = ECLICINTCTLBITS;
        return 0;
    }

    //shift priority into correct bit position
    priority = priority << (8 - ECLICINTCTLBITS);

    //write to eclicintctrl
    uint8_t current_intctrl = eclic_get_intctrl(source);
    //shift intctrl right to mask off unused bits
    current_intctrl = current_intctrl >> (8 - nlbits);
    //shift intctrl into correct bit position
    current_intctrl = current_intctrl << (8 - nlbits);

    eclic_set_intctrl(source, (current_intctrl | priority));

    return priority;
}

//gets an interrupt priority based encoding of nlbits
uint8_t eclic_get_int_priority(uint32_t source) {
    //extract nlbits
    uint8_t nlbits = eclic_get_nlbits();
    if (nlbits > ECLICINTCTLBITS) {
        nlbits = ECLICINTCTLBITS;
    }

    uint8_t intctrl = eclic_get_intctrl(source);

    //shift intctrl
    intctrl = intctrl << nlbits;
    //shift intctrl
    uint8_t priority = intctrl >> (nlbits + (8 - ECLICINTCTLBITS));

    return priority;
}

void eclic_mode_enable() {
    uint32_t mtvec_value = read_csr(mtvec);
    mtvec_value = mtvec_value & 0xFFFFFFC0;
    mtvec_value = mtvec_value | 0x00000003;
    write_csr(mtvec, mtvec_value);
}

void eclic_set_shv(uint32_t source, uint8_t shv) {
    uint8_t attr = eclic_get_intattr(source);
    if (shv) {
        attr |= 0x01;
        eclic_set_intattr(source, attr);
    }
}

void eclic_set_trig(uint32_t source, uint8_t trig) {
    uint8_t attr = eclic_get_intattr(source);
    if ((trig & 0x1)) {
        attr |= (trig << 1);
        eclic_set_intattr(source, attr);
    }
}
