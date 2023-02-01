/*
 * Copyright (C) 2016-2020 Bouffalo Lab
 */

_start:
    .section      .text.startup
    .align  2
    .globl  risc_e906_start
    .type   risc_e906_start, %function
risc_e906_start:
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      a0, IRQ_Handler
    ori     a0, a0, 3
    csrw    mtvec, a0 
#1:
#    j       1b

    la      a0, __Vectors
    csrw    mtvt, a0

    .weak __StackTop
    la      sp, __StackTop
    csrw    mscratch, sp

#ifndef RUN_IN_RAM
	/* Load boot2 partition address */
	la a0, __boot2_pt_addr_src
	la a1, __boot2_pt_addr_start
	la a2, __boot2_pt_addr_end
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:


	/* Load boot2 flashCfg address */
	la a0, hal_boot2_get_flash_addr
	jalr a0
	la a1, __boot2_flashCfg_start
	la a2, __boot2_flashCfg_end
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:
#endif

    /* Load data section removed */
    
    /* start load code to itcm like. */
    la a0,  start_load
    jalr    a0
 
    /* Clear bss section removed */

#ifndef __NO_SYSTEM_INIT
    la a0,  system_init_bl606p
    jalr    a0
#endif

#ifndef __NO_BOARD_INIT
    la a0,  board_init
    jalr    a0
#endif
   
	//la a0,  bfl_main
	la a0,  entry
    jalr    a0

    .size   risc_e906_start, . - risc_e906_start

__exit:
    j      __exit

