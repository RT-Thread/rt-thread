#ifndef __CORE_V5_H__
#define __CORE_V5_H__

#define MSTATUS_UIE         	0x00000001
#define MSTATUS_SIE         	0x00000002
#define MSTATUS_HIE         	0x00000004
#define MSTATUS_MIE         	0x00000008
#define MSTATUS_UPIE        	0x00000010
#define MSTATUS_SPIE        	0x00000020
#define MSTATUS_HPIE        	0x00000040
#define MSTATUS_MPIE        	0x00000080
#define MSTATUS_SPP         	0x00000100
#define MSTATUS_HPP         	0x00000600
#define MSTATUS_MPP         	0x00001800
#define MSTATUS_FS          	0x00006000
#define MSTATUS_XS          	0x00018000
#define MSTATUS_MPRV        	0x00020000
#define MSTATUS_PUM         	0x00040000
#define MSTATUS_MXR				0x00080000
#define MSTATUS_VM          	0x1F000000
#define MSTATUS32_SD        	0x80000000
#define MSTATUS64_SD        	0x8000000000000000

#if __riscv_xlen == 64
#define MCAUSE_INT          	0x8000000000000000UL
#define MCAUSE_CAUSE        	0x7FFFFFFFFFFFFFFFUL
#else
#define MCAUSE_INT          	0x80000000UL
#define MCAUSE_CAUSE        	0x7FFFFFFFUL
#endif

#define IRQ_S_SOFT          	1
#define IRQ_H_SOFT          	2
#define IRQ_M_SOFT          	3
#define IRQ_S_TIMER         	5
#define IRQ_H_TIMER         	6
#define IRQ_M_TIMER         	7
#define IRQ_S_EXT           	9
#define IRQ_H_EXT           	10
#define IRQ_M_EXT           	11
#define IRQ_COP             	12
#define IRQ_HOST            	13

/* Machine mode MCAUSE */
#define TRAP_M_I_ACC_FAULT    	1   /* Instruction access fault */
#define TRAP_M_L_ACC_FAULT   	5   /* Data load access fault */
#define TRAP_M_S_ACC_FAULT   	7   /* Data store access fault */
#define TRAP_U_ECALL        	8
#define TRAP_S_ECALL        	9
#define TRAP_H_ECALL        	10
#define TRAP_M_ECALL        	11
#define TRAP_M_I_PAGE_FAULT	12  /* Instruction page fault */
#define TRAP_M_L_PAGE_FAULT	13  /* Data load page fault */
#define TRAP_M_S_PAGE_FAULT	15  /* Data store page fault */
#define TRAP_M_STACKOVF     	32
#define TRAP_M_STACKUDF     	33

/* Supervisor mode SCAUSE */
#define TRAP_S_I_ACC_FAULT    	1   /* Instruction access fault */
#define TRAP_S_L_ACC_FAULT   	5   /* Data load access fault */
#define TRAP_S_S_ACC_FAULT   	7   /* Data store access fault */
#define TRAP_S_I_PAGE_FAULT	12  /* Instruction page fault */
#define TRAP_S_L_PAGE_FAULT	13  /* Data load page fault */
#define TRAP_S_S_PAGE_FAULT	15  /* Data store page fault */

#define MIP_SSIP            	(1 << IRQ_S_SOFT)
#define MIP_HSIP            	(1 << IRQ_H_SOFT)
#define MIP_MSIP            	(1 << IRQ_M_SOFT)
#define MIP_STIP            	(1 << IRQ_S_TIMER)
#define MIP_HTIP            	(1 << IRQ_H_TIMER)
#define MIP_MTIP            	(1 << IRQ_M_TIMER)
#define MIP_SEIP            	(1 << IRQ_S_EXT)
#define MIP_HEIP            	(1 << IRQ_H_EXT)
#define MIP_MEIP            	(1 << IRQ_M_EXT)

/* MILMB and MDLMB */
#define	MILMB_IEN		(0x1UL)
#define	MDLMB_DEN		(0x1UL)

#if __riscv_xlen == 64
# define SLL32    		sllw
# define STORE    		sd
# define LOAD     		ld
# define LWU      		lwu
# define LOG_REGBYTES 		3
#else
# define SLL32    		sll
# define STORE    		sw
# define LOAD     		lw
# define LWU      		lw
# define LOG_REGBYTES		2
#endif
#define REGBYTES		(1 << LOG_REGBYTES)

#if __riscv_flen == 64
# define FPSTORE		fsd
# define FPLOAD			fld
# define LOG_FPREGBYTES		3
#else
# define FPSTORE		fsw
# define FPLOAD			flw
# define LOG_FPREGBYTES		2
#endif
#define FPREGBYTES              (1 << LOG_FPREGBYTES)

#define STR(S)			#S
#define XSTR(S)			STR(S)

#define PUSH			XSTR(STORE)
#define POP			XSTR(LOAD)
#define REGSIZE			XSTR(REGBYTES)
#define FPPUSH			XSTR(FPSTORE)
#define FPPOP			XSTR(FPLOAD)
#define FPREGSIZE		XSTR(FPREGBYTES)

#ifndef __ASSEMBLER__


#define read_csr(reg)		__nds__csrr(reg)
#define write_csr(reg, val)	__nds__csrw(val, reg)
#define swap_csr(reg, val)	__nds__csrrw(val, reg)
#define set_csr(reg, bit)	__nds__csrrs(bit, reg)
#define clear_csr(reg, bit)	__nds__csrrc(bit, reg)

#endif

#endif	// __CORE_V5_H__
