.data
#define DEVICE_MEM  0x10c06
#define NORMAL_MEM  0x11c0e
.align 14
mtbl:

    //vaddr: 0x00000000
    .rept 0x100
    .word 0x0
    .endr

    //vaddr: 0x10000000
    .equ mmu_tbl_map_paddr, 0x10000000
    .rept 0x400
    .word mmu_tbl_map_paddr | DEVICE_MEM
    .equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
    .endr

    //vaddr: 0x50000000
    .rept 0x100
    .word 0x0
    .endr

    //vaddr: 0x60000000
    .equ mmu_tbl_map_paddr, 0x60000000
    .rept 0x800
    .word mmu_tbl_map_paddr | NORMAL_MEM
    .equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
    .endr

    //vaddr: 0xe0000000
    .rept 0x200
    .word 0x0
    .endr
