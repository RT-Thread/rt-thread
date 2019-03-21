.data
#define DEVICE_MEM  0x10c06
#define NORMAL_MEM  0x11c0e
.align 14
mtbl:
	//vaddr: 0x00000000
	.equ mmu_tbl_map_paddr, 0x00000000
	.rept 0x800
	.word mmu_tbl_map_paddr | DEVICE_MEM
	.equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
	.endr

	//vaddr: 0x80000000
	.equ mmu_tbl_map_paddr, 0x80000000
	.rept 0x800
	.word mmu_tbl_map_paddr | NORMAL_MEM
	.equ mmu_tbl_map_paddr, mmu_tbl_map_paddr + 0x100000
	.endr

