/*
 * Copyright (C) 2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
*/

/*!
 * @file plat_startup.inc
 * @brief This file contains start-up DCD.
 *
 * @ingroup diag_init
 */
 /* *INDENT-OFF* */
#ifndef _PLAT_STARTUP_H_
#define _PLAT_STARTUP_H_

#include "soc_memory_map.h"
#define IMAGE_ENTRY_ADDR        0x80000000
#define IMAGE_SIZE              4*1024*1024

#define L2CC_REG1_CTRL          0x00A02100
#define L2CC_INV_REG            0x00A0277C
#define L2CC_TAG_RAM_CTRL       0x00A02108
#define L2CC_DAT_RAM_CTRL       0x00A0210C
#define L2CC_PREFETCH_CTRL      0x00A02F60

#define ROM_API_TABLE_BASE_ADDR     (0x00000180)
#define ROM_API_HWCNFG_SETUP_OFFSET   (0x08)

#define PLATFORM_INIT           plat_dcd_startup

#define ASM_REG32_WR(i, addr, val) \
    ldr r0, =addr;              \
    ldr r1, =val;               \
    str r1, [r0];

// image starts at 0x00907000
//flash header & DCD @ 0x400
.macro plat_dcd_startup
    b startup
    .org 0x400
/* First IVT to copy the plugin that initializes the system into OCRAM */
ivt_header:             .long 0x402000D1    //Tag=0xD1, Len=0x0020, Ver=0x40
app_code_jump_v:        .long 0x00907458    // Plugin entry point, address after the second IVT table
reserv1:                .long 0x0
dcd_ptr:                .long 0x0
boot_data_ptr:          .long 0x00907420
self_ptr:               .long 0x00907400
app_code_csf:           .long 0x0 // reserve 4K for csf
reserv2:                .long 0x0
boot_data:              .long 0x00907000
image_len:              .long 16*1024  
plugin:                 .long 0x1  // Enable plugin flag

/* Second IVT to give entry point into the bootloader copied to DDR */
ivt2_header:            .long 0x402000D1    //Tag=0xD1, Len=0x0020, Ver=0x40
app2_code_jump_v:       .long startup       // Entry point for the bootloader
reserv3:                .long 0x0
dcd2_ptr:               .long 0x0
boot_data2_ptr:         .long boot_data2
self_ptr2:              .long ivt2_header
app_code_csf2:          .long 0x0 // reserve 4K for csf
reserv4:                .long 0x0
boot_data2:             .long IMAGE_ENTRY_ADDR
image_len2:             .long IMAGE_SIZE
plugin2:                .long 0x0

// Here starts the plugin code
plugin_start:
// Save the return address and the function arguments
    push    {r0-r4, lr}

#if defined(EVB) || defined(SABRE_LITE)
ASM_REG32_WR(0, 0x020bc000, 0x30)


ASM_REG32_WR(0, 0x020c4068, 0xffffffff)
ASM_REG32_WR(0, 0x020c406c, 0xffffffff)
ASM_REG32_WR(0, 0x020c4070, 0xffffffff)
ASM_REG32_WR(0, 0x020c4074, 0xffffffff)
ASM_REG32_WR(0, 0x020c4078, 0xffffffff)
ASM_REG32_WR(0, 0x020c407c, 0xffffffff)
ASM_REG32_WR(0, 0x020c4080, 0xffffffff)
ASM_REG32_WR(0, 0x020c4084, 0xffffffff)

ASM_REG32_WR(0, 0x020E04B4, 0x000C0000)
ASM_REG32_WR(0, 0x020E04AC, 0x00000000)
ASM_REG32_WR(0, 0x020E027C, 0x00000030)
ASM_REG32_WR(0, 0x020E0250, 0x00000030)
ASM_REG32_WR(0, 0x020E024C, 0x00000030)
ASM_REG32_WR(0, 0x020E0490, 0x00000030)
ASM_REG32_WR(0, 0x020E0288, 0x00000030)
ASM_REG32_WR(0, 0x020E0270, 0x00000000)
ASM_REG32_WR(0, 0x020E0260, 0x00000030)
ASM_REG32_WR(0, 0x020E0264, 0x00000030)
ASM_REG32_WR(0, 0x020E04A0, 0x00000030)
ASM_REG32_WR(0, 0x020E0494, 0x00020000)
ASM_REG32_WR(0, 0x020E0280, 0x00000030)
ASM_REG32_WR(0, 0x020E0284, 0x00000030)
ASM_REG32_WR(0, 0x020E04B0, 0x00020000)
ASM_REG32_WR(0, 0x020E0498, 0x00000030)
ASM_REG32_WR(0, 0x020E04A4, 0x00000030)
ASM_REG32_WR(0, 0x020E0244, 0x00000030)
ASM_REG32_WR(0, 0x020E0248, 0x00000030)
ASM_REG32_WR(0, 0x021B001C, 0x00008000)
ASM_REG32_WR(0, 0x021B0800, 0xA1390003)
ASM_REG32_WR(0, 0x021B080C, 0x001b001E)
ASM_REG32_WR(0, 0x021B083C, 0x42400240)
ASM_REG32_WR(0, 0x021B0848, 0x00003A3E)
ASM_REG32_WR(0, 0x021B0850, 0x00003230)
ASM_REG32_WR(0, 0x021B081C, 0x33333333)
ASM_REG32_WR(0, 0x021B0820, 0x33333333)
ASM_REG32_WR(0, 0x021B082C, 0xf3333333)
ASM_REG32_WR(0, 0x021B0830, 0xf3333333)
ASM_REG32_WR(0, 0x021B08C0, 0x00922012)
ASM_REG32_WR(0, 0x021B08b8, 0x00000800)
ASM_REG32_WR(0, 0x021B0004, 0x0002002D)
ASM_REG32_WR(0, 0x021B0008, 0x1B333000)
ASM_REG32_WR(0, 0x021B000C, 0x676B54B3)
ASM_REG32_WR(0, 0x021B0010, 0xB68E0A83)
ASM_REG32_WR(0, 0x021B0014, 0x01FF00DB)
ASM_REG32_WR(0, 0x021B0018, 0x00211740)
ASM_REG32_WR(0, 0x021B001C, 0x00008000)
ASM_REG32_WR(0, 0x021B002C, 0x000026D2)
ASM_REG32_WR(0, 0x021B0030, 0x006C1023)
ASM_REG32_WR(0, 0x021B0040, 0x0000005F)
ASM_REG32_WR(0, 0x021B0000, 0x85180000)
ASM_REG32_WR(0, 0x021B001C, 0x02008032)
ASM_REG32_WR(0, 0x021B001C, 0x00008033)
ASM_REG32_WR(0, 0x021B001C, 0x00048031)
ASM_REG32_WR(0, 0x021B001C, 0x15208030)
ASM_REG32_WR(0, 0x021B001C, 0x04008040)
ASM_REG32_WR(0, 0x021B0020, 0x00000800)
ASM_REG32_WR(0, 0x021B0818, 0x00000227)
ASM_REG32_WR(0, 0x021B0004, 0x0002552D)
ASM_REG32_WR(0, 0x021B0404, 0x00011006)
ASM_REG32_WR(0, 0x021B001C, 0x00000000)


#else
	#error "Please add the DDR initialization code for this board, unless you can make sure the existing code can be shared."
#endif

read_obds:
/********************
    The following is to fill in those arguments for this ROM function
    pu_irom_hwcnfg_setup(void **start, size_t *bytes, const void *boot_data)

    This function is used to copy data from the storage media into DDR.

    start - Initial (possibly partial) image load address on entry.  Final image load address on exit.
    bytes - Initial (possibly partial) image size on entry.  Final image size on exit.
    boot_data - Initial @ref ivt Boot Data load address.
*/

    adr r0, DDR_DEST_ADDR
    adr r1, COPY_SIZE
    adr r2, BOOT_DATA

/*
 * check the _pu_irom_api_table for the address
 */
before_calling_rom___pu_irom_hwcnfg_setup:
    //mov r4, #0x2000
    //add r4, r4, #0xed
    //blx r4    // This address might change in future ROM versions.
    ldr r3, =ROM_API_TABLE_BASE_ADDR         /* Address of rom_api_table is 0xc0 */
    ldr r4, [r3, #ROM_API_HWCNFG_SETUP_OFFSET] /* hwcnfg setup function address is 3rd entry in the api table address 0xc8 */
    blx r4  /* call into ROM function */
after_calling_rom___pu_irom_hwcnfg_setup:

	/* SDRAM has been setup, binary image has been copied to SDRAM */
	b	startup // Jump to our code directly

DDR_DEST_ADDR:    .word   IMAGE_ENTRY_ADDR
COPY_SIZE:        .word   IMAGE_SIZE
BOOT_DATA:        .word   IMAGE_ENTRY_ADDR
                  .word   IMAGE_SIZE  //real data to be copied by the pu_irom_hwcnfg_setup()
                  .word   0

.endm   //plat_dcd_startup

// #define PLATFORM_ASM_STARTUP           platform_asm_startup
.macro platform_asm_startup

config_L2_cache:
    disable_L2_cache

init_aips_start:
    init_aips

init_reloc_start:
    /* Check if need to copy image to Redboot ROM space */
    ldr r0, =0xFFFFF000
    and r0, r0, pc
    ldr r1, =IMAGE_ENTRY_ADDR
    cmp r0, r1
    beq skip_SDRAM_copy

    add r2, r0, #IMAGE_SIZE

1:  ldmia r0!, {r3-r10}
    stmia r1!, {r3-r10}
    cmp r0, r2
    ble 1b
    /* Jump to SDRAM */
    ldr r1, =0xFFFF
    and r0, pc, r1         /* offset of pc */
    ldr r1, =(IMAGE_ENTRY_ADDR + 0x8)
    add pc, r0, r1
    nop
    nop
    nop
    nop

skip_SDRAM_copy:
.endm   //platform_asm_startup

/* AIPS setup - Only setup MPROTx registers. The PACR default values are good.*/
.macro init_aips
    /*
     * Set all MPROTx to be non-bufferable, trusted for R/W,
     * not forced to user-mode.
     */
    ldr r0, =AIPS_TZ1_BASE_ADDR
    ldr r1, =0x77777777
    str r1, [r0, #0x00]
    str r1, [r0, #0x04]

    ldr r0, =AIPS_TZ2_BASE_ADDR
    str r1, [r0, #0x00]
    str r1, [r0, #0x04]

.endm /* init_aips */

.macro clean_L1_DCache
	mov r0, #0
	mcr p15, 2, r0, c0, c0, 0 // select DCache
	mrc p15, 1, r0, c0, c0, 0 // read CCSIDR
	mov r0, r0, ASR #13
	ldr	r3, =0x3FFF
	and r0, r0, r3
	cmp r0, #0x7F
	moveq r6, #0x1000 // 4KB * 4way = 16KB
	beq	clean_and_invalidate_L1_dcache
	cmp r0, #0xFF
	moveq r6, #0x2000 // 32KB
	beq clean_and_invalidate_L1_dcache
	movne r6, #0x4000 // 64KB

clean_and_invalidate_L1_dcache:
	mov r2, #0x00000000
	mov r3, #0x40000000
	mov r4, #0x80000000
	mov r5, #0xC0000000

clean_and_invalidate_L1_dcache_byset:
	mcr p15, 0, r2, c7, c14, 2 //clean and invalidate dcache on way 0
	mcr p15, 0, r3, c7, c14, 2 //clean and invalidate dcache on way 1
	mcr p15, 0, r4, c7, c14, 2 //clean and invalidate dcache on way 2
	mcr p15, 0, r5, c7, c14, 2 //clean and invalidate dcache on way 3
	add r2, r2, #0x20
	add r3, r3, #0x20
	add r4, r4, #0x20
	add r5, r5, #0x20
	
	cmp r2, r6
	bne clean_and_invalidate_L1_dcache_byset
	
.endm

.macro enable_L1_cache
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 6 // invalidate BTAC
    mcr p15, 0, r0, c7, c5, 0 // invalidate icache
    
    mov r0, #0
    mcr p15, 2, r0, c0, c0, 0 // select DCache
    mrc p15, 1, r0, c0, c0, 0 // read CCSIDR
    mov r0, r0, ASR #13
    ldr r3, =0x3FFF
    and r0, r0, r3
    cmp r0, #0x7F
    moveq r6, #0x1000 // 4KB * 4way = 16KB
    beq invalidate_dcache
    cmp r0, #0xFF
    moveq r6, #0x2000 // 32KB
    beq invalidate_dcache
    movne r6, #0x4000 // 64KB

invalidate_dcache:
    mov r2, #0x00000000
    mov r3, #0x40000000
    mov r4, #0x80000000
    mov r5, #0xC0000000

invalidate_dcache_byset:
    mcr p15, 0, r2, c7, c6, 2 //invalidate dcache on way 0
    mcr p15, 0, r3, c7, c6, 2 //invalidate dcache on way 1
    mcr p15, 0, r4, c7, c6, 2 //invalidate dcache on way 2
    mcr p15, 0, r5, c7, c6, 2 //invalidate dcache on way 3
    add r2, r2, #0x20
    add r3, r3, #0x20
    add r4, r4, #0x20
    add r5, r5, #0x20
    
    cmp r2, r6
    bne invalidate_dcache_byset
    
    ldr r0, =0x00930000 //where to store the TLB page table
    mcr p15, 0, r0, c2, c0, 0
    ldr r0, =0x55555555
    mcr p15, 0, r0, c3, c0, 0
    
    mrc p15, 0, r0, c1, c0, 0 // read CP15 register 1 into r0
    orr r0, r0, #(0x1<<12)    // enable I Cache
    orr r0, r0, #(0x1<<11)    // turn on BP
    orr r0, r0, #(0x1<<2)     // enable D Cache
    /*Attention: If you want to enable MMU, must set up the TLB tables first!!*/
    bic r0, r0, #(0x1<<0)     // disable MMU
    mcr p15, 0, r0, c1, c0, 0 // write CP15 register 1
.endm

.macro disable_L1_cache
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(0x1<<12) 
    bic r0, r0, #(0x1<<11) 
    bic r0, r0, #(0x1<<2) 
    bic r0, r0, #(0x1<<0) 
    mcr p15, 0, r0, c1, c0, 0
.endm

.macro disable_L1_DCache
	mrc		p15, 0, r0, c1, c0, 0
	ands	r0, r0, #(0x1<<11)	//check if L1 DCache has been disabled
	beq		disable_L1_DCache_done
	bic r0, r0, #(0x1<<11) 
	bic r0, r0, #(0x1<<0) //disable MMU 
	mcr p15, 0, r0, c1, c0, 0
	clean_L1_DCache
disable_L1_DCache_done:
.endm

.macro enable_L2_cache
    /* set latency: 4x cycles read, 2x cycles write, (3x cycles setup)*/
    ldr     r1,= L2CC_TAG_RAM_CTRL
    ldr     r0,=0x0132
    str     r0,[r1]
    ldr     r1, =L2CC_DAT_RAM_CTRL
    ldr     r0,=0x0132
    str     r0,[r1]
    
    /* invalidate L2Cache by way */
    ldr     r1, =L2CC_INV_REG
    ldr     r0, =0xffff
    str     r0,[r1]
l2cc_inv_done:
    ldr     r2,[r1]
    mov     r0,#0x0
    cmp     r2,r0
    bne     l2cc_inv_done
    
    /* turn on l2 cache */
    ldr     r1, =L2CC_REG1_CTRL
    mov     r0,#1
    str     r0,[r1]
.endm

.macro disable_L2_cache
    ldr     r1, =L2CC_REG1_CTRL
    mov     r0,#0
    str     r0,[r1]
.endm

#endif //_PLAT_STARTUP_H_
