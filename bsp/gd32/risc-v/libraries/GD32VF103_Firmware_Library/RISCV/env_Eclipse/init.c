//See LICENSE for license details.
#include <gd32vf103.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "riscv_encoding.h"
#include "n200_func.h"

extern uint32_t disable_mcycle_minstret();
void _init()
{
    SystemInit();

    //ECLIC init
    eclic_init(ECLIC_NUM_INTERRUPTS);
    eclic_mode_enable();

    //printf("After ECLIC mode enabled, the mtvec value is %x \n\n\r", read_csr(mtvec));

    // // It must be NOTED:
    //  //    * In the RISC-V arch, if user mode and PMP supported, then by default if PMP is not configured
    //  //      with valid entries, then user mode cannot access any memory, and cannot execute any instructions.
    //  //    * So if switch to user-mode and still want to continue, then you must configure PMP first
    //pmp_open_all_space();
    //switch_m2u_mode();

    /* Before enter into main, add the cycle/instret disable by default to save power,
    only use them when needed to measure the cycle/instret */
    disable_mcycle_minstret();
}

void _fini()
{
}
