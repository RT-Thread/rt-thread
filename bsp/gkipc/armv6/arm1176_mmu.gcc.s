@*******************************************************************************
@*******************************************************************************
@**
@** Filename...: src/arm1176_mmu.gcc.s
@** Source.....: src/arm1176_mmu.s
@** Generator..: asm2gas.pl
@** Note.......: DO NOT MODIFY THIS FILE BY HAND!
@**
@*******************************************************************************
@*******************************************************************************

@*******************************************************************************
@*******************************************************************************
@**
@** ARM1176 Startup, MMU initialization and data cache setup
@**
@** This module initialized the MMU in flat memory mode, all addresses are
@** directly mapped, vitual addresses are equal to physical addresses. The
@** MMU is required only to enable the cache mode of dedicated memory
@** regions.
@**
@** Version: $Id: arm1176_mmu.gcc.s 9143 2012-04-25 09:33:55Z jrende $
@**
@** (C) Copyright 2012-2013 by Goke Microelectronics Shanghai Branch**
@*******************************************************************************
@*******************************************************************************

    .text
    .section ".ARM1176INIT"
    .align 8

    .extern _start
    .extern _end_readonly
    .extern |_start|
    .extern |ARM1176_MMU_ttb0|
    .extern |ARM1176_MMU_ttb1|
	
    .equ ARM1176_PHYSICAL_TTB0_BASE,      arm1176_mmu_ttb0 
    .equ ARM1176_PHYSICAL_TTB1_BASE,      arm1176_mmu_ttb1 
    .equ ARM1176_TTB_ENTRIES,             4096 

    .if CPU_USE_GK710XS==1
    .equ ARM1176_PHYSICAL_PERI_BASE,       0x90000000 
    .else
    .equ ARM1176_PHYSICAL_PERI_BASE,       0x60000000 
    .endif
    .equ ARM1176_PHYSICAL_PERI_SIZE,       0x20000000 
    .equ ARM1176_REMAPPED_PERI_BASE,       ARM1176_PHYSICAL_PERI_BASE 

    .equ ARM1176_PHYSICAL_PPM_BASE,        DDR_MEMORY_PPM_BASE 
    .equ ARM1176_PHYSICAL_PPM_SIZE,        DDR_MEMORY_PPM_SIZE 
    .equ ARM1176_REMAPPED_PPM_BASE,        ARM1176_PHYSICAL_PPM_BASE
	
    .equ ARM1176_PHYSICAL_RTOS_BASE,       DDR_MEMORY_OS_BASE 
    .equ ARM1176_PHYSICAL_RTOS_SIZE,       DDR_MEMORY_OS_SIZE
    .equ ARM1176_REMAPPED_RTOS_BASE,       ARM1176_PHYSICAL_RTOS_BASE

@  use mmu map bsb address from 0xCxxxxxxx(DDR_MEMORY_BSB_BASE) to 0xD0000000|DDR_MEMORY_BSB_BASE
    .equ ARM1176_PHYSICAL_BSB_REAMP_BASE,   0xD0000000
    .equ ARM1176_PHYSICAL_BSB_BASE,        DDR_MEMORY_BSB_BASE
    .equ ARM1176_PHYSICAL_BSB_SIZE,        DDR_MEMORY_BSB_SIZE 
    .equ ARM1176_REMAPPED_BSB_BASE,        ARM1176_PHYSICAL_BSB_BASE|ARM1176_PHYSICAL_BSB_REAMP_BASE

@  use mmu remap bsb address 0xCxxxxxxx(DDR_MEMORY_BSB_BASE) to ARM1176_REMAPPED_BSB_BASE+DDR_MEMORY_BSB_SIZE, it resolve bsb data revert.
    .equ ARM1176_PHYSICAL_BSB_BASE,        DDR_MEMORY_BSB_BASE
    .equ ARM1176_PHYSICAL_BSB_SIZE,        DDR_MEMORY_BSB_SIZE 
    .equ ARM1176_REMAPPED_BSB_BASE_EXT,    ARM1176_REMAPPED_BSB_BASE+DDR_MEMORY_BSB_SIZE
	
	.equ ARM1176_PHYSICAL_DSP_BASE,        DDR_MEMORY_DSP_BASE 
    .equ ARM1176_PHYSICAL_DSP_SIZE,        DDR_MEMORY_DSP_SIZE 
    .equ ARM1176_REMAPPED_DSP_BASE,        ARM1176_PHYSICAL_DSP_BASE 
	
    .equ ARM1176_1MB_CACHE_NOBUFFER,      0x00000DEA  @ cachable/non-bufferable
    .equ ARM1176_1MB_CACHE_BUFFER,        0x00000DEE  @ cachable/bufferable
    .equ ARM1176_1MB_NOCACHE_NOBUFFER,    0x00000DE2  @ non-cachable/non-bufferable
    .equ ARM1176_1MB_NORMAL_NOCACHE,      0x00001DE2  @ Normal memory, non-cachable/non-bufferable
    .equ ARM1176_1MB_CACHE_BUFFER_RO,     0x000011EE  @ cachable/bufferable read-only
    .equ ARM1176_1MB_NOCACHE_NOBUFFER_RO, 0x000011E2  @ non-cachable/non-bufferable read-only

@*******************************************************************************
@** Initialise the MMU
@*******************************************************************************

    .global ARM1176_MmuInitialise

ARM1176_MmuInitialise:

@*******************************************************************************
@** save link register on r11 as we are using bl commands internally
@*******************************************************************************

    mov r11,lr

@*******************************************************************************
@** if MMU/MPU enabled - disable (useful for ARMulator tests)
@*******************************************************************************

    mrc p15,0,r0,c1,c0,0 @ read CP15 register 1 into r0
    bic r0,r0,#0x1000    @ disable I-cache
    bic r0,r0,#0x0004    @ disable D-cache
    bic r0,r0,#0x0001    @ disable MMU
    mcr p15,0,r0,c1,c0,0 @ write value back

@*******************************************************************************
@** MMU Configuration
@**
@** Configure system to use extended v6 format pagetables
@** Set translation table base
@** Specify v6 format pagetables with no subpages
@** set bit 23 [XP] in CP15 control register.
@** ARM1176 supports two translation tables
@** Configure translation table base (TTB) control register cp15,c2
@** to a value of all zeros, indicates we are using TTB register 0.
@*******************************************************************************

    mrc p15,0,r0,c1,c0,0 @ read CP15 register 1 into r0
    mov r1,#0x800000
    orr r0,r0,r1	 @ disable Subpage AP bits
    mcr p15,0,r0,c1,c0,0 @ write value back
    mov r0,#0x0
    mcr p15,0,r0,c2,c0,2 @ Write Translation Table Base Control Register to 0, use Register 0
    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    mcr p15,0,r0,c2,c0,0 @ Write Translation Table Base Register 0 to ARM1176_PHYSICAL_TTB0_BASE

@*******************************************************************************
@** PAGE TABLE generation
@**
@** Generate the page tables
@** Build a flat translation table for the whole address space.
@** ie: Create 4096 1MB sections from 0x000xxxxx to 0xFFFxxxxx
@**
@** |31................20|19..18|17|16| 15|14..12|11.10|9|8....5| 4|3.2|1.0|
@** |section base address| 0   0|nG| S|APX|   TEX|  AP |P|Domain|XN|C B|1 0|
@**
@** Bits[31:20] Top 12 bits of VA is pointer into table
@** nG[17]=0.   Non global, enables matching against ASID in the TLB when set.
@** S[16]=0.    Indicates normal memory is shared when set.
@** Access Permissions - configure for full read/write access in all modes
@** APX[15]=0 and AP[11:10]=11
@**
@** Set attributes to normal memory, non cacheable.
@** TEX[14:12]=001 and CB[3:2]= 00
@** P[9]=0.     ECC enabled memory (not supported on ARM1136).
@** Domain[5:8]=1111 = Set all pages to use domain 15
@** XN[4]:=0    Execute never disabled.
@** Bits[1:0]   Indicate entry is a 1MB section.
@**
@** r0 contains the address of the translation table base
@** r1 is loop counter
@** r2 is level1 descriptor (bits 19:0)
@**
@** use loop counter to create 4096 individual table entries
@** this writes from address 0x7FFC down to 0x4000 in word steps (4bytes).
@**
@** In this example we will set the cacheable attribute in the first descriptor
@**  only, so virtual memory from 0 to 1MB will be cacheable (write back mode).
@** TEX[14:12]=000 and CB[3:2]=11
@*******************************************************************************

@*******************************************************************************
@** create empty TTB entries to initialize entries 0..2047
@** r0 = TTB base address
@** r1 = unused
@** r2 = unused
@** r3 = virtual DDR address, upper 12 bits shifted 20 bits right (virt. index)
@** r4 = remap size upper 12 bits shifted 20 bits right (table max. index)
@** r5 = unused
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE       @ set the MMU table base address
    ldr r1,=0x00000000                      @ 0x00000000 == disable access
    ldr r2,=0x00000000                      @ remap addresses from 0x00000000..
    ldr r3,=0x00000000                      @                   to 0x00000000..
    ldr r4,=0x80000000                      @ fixed remap RAM size (2048MB)
    bl  arm1176_update_mmu_table            @ update mmu table entries

@*******************************************************************************
@** set the peri
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_NOCACHE_NOBUFFER
    ldr r2,=ARM1176_PHYSICAL_PERI_BASE
    ldr r3,=ARM1176_REMAPPED_PERI_BASE
    ldr r4,=ARM1176_PHYSICAL_PERI_SIZE
    bl  arm1176_update_mmu_table

@*******************************************************************************
@** set the ppm
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_NOCACHE_NOBUFFER
    ldr r2,=ARM1176_PHYSICAL_PPM_BASE
    ldr r3,=ARM1176_REMAPPED_PPM_BASE
    ldr r4,=ARM1176_PHYSICAL_PPM_SIZE
    bl  arm1176_update_mmu_table
	
@*******************************************************************************
@** set the rtos (nocache_section(1M)/code_heap(RTOSSIZE-1M))
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_NOCACHE_NOBUFFER
    ldr r2,=ARM1176_PHYSICAL_RTOS_BASE
    ldr r3,=ARM1176_REMAPPED_RTOS_BASE
    ldr r4,=0x200000
    bl  arm1176_update_mmu_table

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_CACHE_BUFFER
    ldr r2,=ARM1176_PHYSICAL_RTOS_BASE+0x100000
    ldr r3,=ARM1176_REMAPPED_RTOS_BASE+0x100000
    ldr r4,=ARM1176_PHYSICAL_RTOS_SIZE-0x100000
    bl  arm1176_update_mmu_table

@*******************************************************************************
@** set the bsb
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_CACHE_BUFFER
    ldr r2,=ARM1176_PHYSICAL_BSB_BASE
    ldr r3,=ARM1176_REMAPPED_BSB_BASE
    ldr r4,=ARM1176_PHYSICAL_BSB_SIZE
    bl  arm1176_update_mmu_table

@*******************************************************************************
@** set the bsb again for continues address for frame address
@*******************************************************************************
    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_CACHE_BUFFER
    ldr r2,=ARM1176_PHYSICAL_BSB_BASE
    ldr r3,=ARM1176_REMAPPED_BSB_BASE_EXT
    ldr r4,=ARM1176_PHYSICAL_BSB_SIZE
    bl  arm1176_update_mmu_table
	
@*******************************************************************************
@** set the dsp
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,=ARM1176_1MB_CACHE_BUFFER
    ldr r2,=ARM1176_PHYSICAL_DSP_BASE
    ldr r3,=ARM1176_REMAPPED_DSP_BASE
    ldr r4,=ARM1176_PHYSICAL_DSP_SIZE
    bl  arm1176_update_mmu_table
	
@*******************************************************************************
@** copy TTB0 into TTB1
@*******************************************************************************

    ldr r0,ARM1176_PHYSICAL_TTB0_BASE
    ldr r1,ARM1176_PHYSICAL_TTB1_BASE
    ldr r2,=ARM1176_TTB_ENTRIES
    bl arm1176_copy_mmu_table

@*******************************************************************************
@** Setup domain control register
@** Enable all domains to client mode
@*******************************************************************************

    mrc p15,0,r0,c3,c0,0 @ Read Domain Access Control Register
    ldr r0,=0x55555555   @ Initialise every domain entry to b01 (client)
    mcr p15,0,r0,c3,c0,0 @ Write Domain Access Control Register

@*******************************************************************************
@** Now the MMU is enabled, virtual to physical address translations will occur.
@** This will affect the next instruction fetch.
@**
@** The two instructions currently in the ARM pipeline will have been fetched
@** before the MMU was enabled. This property is useful because the next two
@** instructions are safe even if new instruction fetches fail - If this
@** routine was mapped out of the new virtual memory map, the branch to
@** arm1176_BootLoaderMain would still succeed.
@*******************************************************************************

    mov r0,#0             @ move 0 into r0
    mcr p15,0,r0,c7,c5,0  @ invalidate instruction cache
    mcr p15,0,r0,c7,c6,0  @ invalidate data cache
    mcr p15,0,r0,c7,c10,4 @ drain write barrier
    mcr p15,0,r0,c8,c5,0  @ reset intruction TLB entries
    mcr p15,0,r0,c8,c6,0  @ reset data TLB entries
    mcr p15,0,r0,c8,c7,0  @ reset unified TLB entries

    mrc p15,0,r0,c1,c0,0  @ read CP15 register c1 into r0
    orr r0,r0,#0x00001000 @ enable I-cache
    orr r0,r0,#0x00000004 @ enable D-cache
    orr r0,r0,#0x00000001 @ enable MMU
    orr r0,r0,#0x00400000 @ enable unaligned load/store
    orr r0,r0,#0x00000100 @ system bit enabled
    bic r0,r0,#0x00000200 @ rom bit disabled
    mcr p15,0,r0,c1,c0,0  @ write r0 back to CP15 register c1
    mov lr,r11            @ restore link register
    bx lr                 @ branch back to caller

@*******************************************************************************
@** create TTB entries to remap 1MB junks of memory
@** register arguments:
@**   r0 = TTB base address
@**   r1 = access mask, lower 20 bits only
@**   r2 = physical address, upper 12 bits shifted 20 bits right (phys. index)
@**   r3 = virtual address, upper 12 bits shifted 20 bits right (virt. index)
@**   r4 = remap size upper 12 bits shifted 20 bits right (table max. index)
@** internal used registers:
@**   r5 = temporary vector to be written into TTB entry
@*******************************************************************************

arm1176_update_mmu_table:
    lsr  r2,r2,#20	@ 1M
    lsr  r3,r3,#20	@ 1M
    lsr  r4,r4,#20	@ 1M
    cmp  r4,#0x0
    bxeq lr
    add  r4,r4,r3
arm1176_update_mmu_table_loop: @ update r4 times 1MB entries
    orr  r5,r1,r2,LSL#20      @ r5 now contains full L1 descriptor to write
    str  r5,[r0,r3,LSL#2]     @ store table entry at TTB base + loopcount*4
    add  r3,r3,#1             @ increment virtual address index
    add  r2,r2,#1             @ increment physical address index
    cmp  r3,r4                @ check for last entry
    bne  arm1176_update_mmu_table_loop
    bx lr

@*******************************************************************************
@** copy one TTB into another
@** register arguments:
@**   r0 = address of 1st TTB
@**   r1 = address of 2nd TTB
@**   r2 = table entry count
@** internal used registers:
@**   r3 = temporary register holding read/wrrite values
@*******************************************************************************

arm1176_copy_mmu_table:
    cmp  r2,#0x0
    bxeq lr
arm1176_copy_mmu_table_loop: @ load entry from 1st table
    ldr  r3,[r0]            @ store entry into 2nd table
    str  r3,[r1]            @ store table entry at TTB base + loopcount*4
    add  r0,r0,#4           @ increment 1st table address by 4 byte
    add  r1,r1,#4           @ increment 2nd table address  by 4 byte
    sub  r2,r2,#1           @ decrement entry counter by 1
    cmp  r2,#0x0
    bne  arm1176_copy_mmu_table_loop
    bx lr

@*******************************************************************************
@** local variables containing far addresses
@*******************************************************************************

    .ltorg

arm1176_image_ro_base:
    .long _start
arm1176_image_ro_limit:
    .long _end_readonly
arm1176_image_start:
    .long _start
arm1176_mmu_ttb0:
    .long ARM1176_MMU_ttb0
arm1176_mmu_ttb1:
    .long ARM1176_MMU_ttb1
arm1176_mmu_video_cached_ptr:
    .long arm1176_mmu_video_cached
arm1176_mmu_video_cached:
    .long 0x0

    .global arm1176_mmu_video_cached
    .weak arm1176_mmu_video_cached

@*******************************************************************************
@** End of file
@*******************************************************************************

    .end
