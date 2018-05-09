#include "nds32.h"

	.set	regno, 0
#ifdef __TARGET_IFC_EXT
	.set	regno, regno+1
#endif
#ifdef __TARGET_ZOL_EXT
	.set	regno, regno+3
#endif

	/* Descend PSW.INTL and enable PSW.AEN */
	.macro IntlDescend
		mfsr	$r1, $PSW
#ifdef __TARGET_ZOL_EXT
		/* Also enable ZOL (PSW.AEN) */
		xori	$r1, $r1, #((1 << 13) | (1 << 1))
#else
		addi	$r1, $r1, #-2
#endif
		mtsr	$r1, $PSW
	.endm

	/* FPU registers */
	.macro SAVE_FPU_REGS_00
		fsdi.bi $fd3, [$sp], -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro SAVE_FPU_REGS_01
		fsdi.bi $fd7, [$sp], -8
		fsdi.bi $fd6, [$sp], -8
		fsdi.bi $fd5, [$sp], -8
		fsdi.bi $fd4, [$sp], -8
		SAVE_FPU_REGS_00
	.endm

	.macro SAVE_FPU_REGS_02
		fsdi.bi $fd15, [$sp], -8
		fsdi.bi $fd14, [$sp], -8
		fsdi.bi $fd13, [$sp], -8
		fsdi.bi $fd12, [$sp], -8
		fsdi.bi $fd11, [$sp], -8
		fsdi.bi $fd10, [$sp], -8
		fsdi.bi $fd9, [$sp], -8
		fsdi.bi $fd8, [$sp], -8
		SAVE_FPU_REGS_01
	.endm

	.macro SAVE_FPU_REGS_03
		fsdi.bi $fd31, [$sp], -8
		fsdi.bi $fd30, [$sp], -8
		fsdi.bi $fd29, [$sp], -8
		fsdi.bi $fd28, [$sp], -8
		fsdi.bi $fd27, [$sp], -8
		fsdi.bi $fd26, [$sp], -8
		fsdi.bi $fd25, [$sp], -8
		fsdi.bi $fd24, [$sp], -8
		fsdi.bi $fd23, [$sp], -8
		fsdi.bi $fd22, [$sp], -8
		fsdi.bi $fd21, [$sp], -8
		fsdi.bi $fd20, [$sp], -8
		fsdi.bi $fd19, [$sp], -8
		fsdi.bi $fd18, [$sp], -8
		fsdi.bi $fd17, [$sp], -8
		fsdi.bi $fd16, [$sp], -8
		SAVE_FPU_REGS_02
	.endm

	.macro push_fpu
#if defined(__NDS32_EXT_FPU_CONFIG_0__)
		addi    $sp, $sp, -8
		SAVE_FPU_REGS_00
#elif defined(__NDS32_EXT_FPU_CONFIG_1__)
		addi    $sp, $sp, -8
		SAVE_FPU_REGS_01
#elif defined(__NDS32_EXT_FPU_CONFIG_2__)
		addi    $sp, $sp, -8
		SAVE_FPU_REGS_02
#elif defined(__NDS32_EXT_FPU_CONFIG_3__)
		addi    $sp, $sp, -8
		SAVE_FPU_REGS_03
#else
#endif
	.endm

	.macro RESTORE_FPU_REGS_00
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
		fldi.bi $fd3, [$sp], 8
	.endm

	.macro RESTORE_FPU_REGS_01
		RESTORE_FPU_REGS_00
		fldi.bi $fd4, [$sp], 8
		fldi.bi $fd5, [$sp], 8
		fldi.bi $fd6, [$sp], 8
		fldi.bi $fd7, [$sp], 8
	.endm

	.macro RESTORE_FPU_REGS_02
		RESTORE_FPU_REGS_01
		fldi.bi $fd8, [$sp], 8
		fldi.bi $fd9, [$sp], 8
		fldi.bi $fd10, [$sp], 8
		fldi.bi $fd11, [$sp], 8
		fldi.bi $fd12, [$sp], 8
		fldi.bi $fd13, [$sp], 8
		fldi.bi $fd14, [$sp], 8
		fldi.bi $fd15, [$sp], 8
	.endm

	.macro RESTORE_FPU_REGS_03
		RESTORE_FPU_REGS_02
		fldi.bi $fd16, [$sp], 8
		fldi.bi $fd17, [$sp], 8
		fldi.bi $fd18, [$sp], 8
		fldi.bi $fd19, [$sp], 8
		fldi.bi $fd20, [$sp], 8
		fldi.bi $fd21, [$sp], 8
		fldi.bi $fd22, [$sp], 8
		fldi.bi $fd23, [$sp], 8
		fldi.bi $fd24, [$sp], 8
		fldi.bi $fd25, [$sp], 8
		fldi.bi $fd26, [$sp], 8
		fldi.bi $fd27, [$sp], 8
		fldi.bi $fd28, [$sp], 8
		fldi.bi $fd29, [$sp], 8
		fldi.bi $fd30, [$sp], 8
		fldi.bi $fd31, [$sp], 8
	.endm

	.macro pop_fpu
#if defined(__NDS32_EXT_FPU_CONFIG_0__)
		RESTORE_FPU_REGS_00
#elif defined(__NDS32_EXT_FPU_CONFIG_1__)
		RESTORE_FPU_REGS_01
#elif defined(__NDS32_EXT_FPU_CONFIG_2__)
		RESTORE_FPU_REGS_02
#elif defined(__NDS32_EXT_FPU_CONFIG_3__)
		RESTORE_FPU_REGS_03
#else
#endif
	.endm

	/* FPU Caller registers */
	.macro SAVE_FPU_CALLER_REGS_00
		addi    $sp, $sp, -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro SAVE_FPU_CALLER_REGS_01
		SAVE_FPU_CALLER_REGS_00
	.endm

	.macro SAVE_FPU_CALLER_REGS_02
		addi    $sp, $sp, -8
		fsdi.bi $fd15, [$sp], -8
		fsdi.bi $fd14, [$sp], -8
		fsdi.bi $fd13, [$sp], -8
		fsdi.bi $fd12, [$sp], -8
		fsdi.bi $fd11, [$sp], -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro SAVE_FPU_CALLER_REGS_03
		addi    $sp, $sp, -8
		fsdi.bi $fd23, [$sp], -8
		fsdi.bi $fd22, [$sp], -8
		fsdi.bi $fd21, [$sp], -8
		fsdi.bi $fd20, [$sp], -8
		fsdi.bi $fd19, [$sp], -8
		fsdi.bi $fd18, [$sp], -8
		fsdi.bi $fd17, [$sp], -8
		fsdi.bi $fd16, [$sp], -8
		fsdi.bi $fd15, [$sp], -8
		fsdi.bi $fd14, [$sp], -8
		fsdi.bi $fd13, [$sp], -8
		fsdi.bi $fd12, [$sp], -8
		fsdi.bi $fd11, [$sp], -8
		fsdi.bi $fd2, [$sp], -8
		fsdi.bi $fd1, [$sp], -8
		fsdi    $fd0, [$sp+0]
	.endm

	.macro push_fpu_caller
#if defined(__NDS32_EXT_FPU_CONFIG_0__)
		SAVE_FPU_CALLER_REGS_00
#elif defined(__NDS32_EXT_FPU_CONFIG_1__)
		SAVE_FPU_CALLER_REGS_01
#elif defined(__NDS32_EXT_FPU_CONFIG_2__)
		SAVE_FPU_CALLER_REGS_02
#elif defined(__NDS32_EXT_FPU_CONFIG_3__)
		SAVE_FPU_CALLER_REGS_03
#else
#endif
	.endm

	.macro RESTORE_FPU_CALLER_REGS_00
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
	.endm

	.macro RESTORE_FPU_CALLER_REGS_01
		RESTORE_FPU_CALLER_REGS_00
	.endm

	.macro RESTORE_FPU_CALLER_REGS_02
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
		fldi.bi $fd11, [$sp], 8
		fldi.bi $fd12, [$sp], 8
		fldi.bi $fd13, [$sp], 8
		fldi.bi $fd14, [$sp], 8
		fldi.bi $fd15, [$sp], 8
	.endm

	.macro RESTORE_FPU_CALLER_REGS_03
		fldi.bi $fd0, [$sp], 8
		fldi.bi $fd1, [$sp], 8
		fldi.bi $fd2, [$sp], 8
		fldi.bi $fd11, [$sp], 8
		fldi.bi $fd12, [$sp], 8
		fldi.bi $fd13, [$sp], 8
		fldi.bi $fd14, [$sp], 8
		fldi.bi $fd15, [$sp], 8
		fldi.bi $fd16, [$sp], 8
		fldi.bi $fd17, [$sp], 8
		fldi.bi $fd18, [$sp], 8
		fldi.bi $fd19, [$sp], 8
		fldi.bi $fd20, [$sp], 8
		fldi.bi $fd21, [$sp], 8
		fldi.bi $fd22, [$sp], 8
		fldi.bi $fd23, [$sp], 8
	.endm

	.macro pop_fpu_caller
#if defined(__NDS32_EXT_FPU_CONFIG_0__)
		RESTORE_FPU_CALLER_REGS_00
#elif defined(__NDS32_EXT_FPU_CONFIG_1__)
		RESTORE_FPU_CALLER_REGS_01
#elif defined(__NDS32_EXT_FPU_CONFIG_2__)
		RESTORE_FPU_CALLER_REGS_02
#elif defined(__NDS32_EXT_FPU_CONFIG_3__)
		RESTORE_FPU_CALLER_REGS_03
#else
#endif
	.endm

	/* IFC system register */
	.macro MFUSR_IFC R0="$r1"
		mfusr	\R0, $IFC_LP
	.endm

	.macro MTUSR_IFC R0="$r1"
		mtusr	\R0, $IFC_LP
	.endm

	/* ZOL system registers */
	.macro MFUSR_ZOL R0="$r1", R1="$r2", R2="$r3"
		mfusr	\R0, $LB
		mfusr	\R1, $LE
		mfusr	\R2, $LC
	.endm

	.macro MTUSR_ZOL R0="$r1", R1="$r2", R2="$r3"
		mtusr	\R0, $LB
		mtusr	\R1, $LE
		mtusr	\R2, $LC
	.endm

	/* Context-switch save and restore routines */
	.macro SAVE_ALL
		pushm	$r6, $r30

		mfsr	$r1, $IPC
		mfsr	$r2, $IPSW

		.if (regno == 4)
		MFUSR_ZOL "$r3","$r4","$r5"
		MFUSR_IFC "$r6"
		pushm	$r0, $r6		/* $0 is dummy */
		.else
		.if (regno == 3)
		MFUSR_ZOL "$r3","$r4","$r5"
		pushm	$r1, $r5
		.else
		.if (regno == 1)
		MFUSR_IFC "$r3"
		pushm	$r1, $r3
		.else
		pushm	$r1, $r2
		.endif
		.endif
		.endif

		push_fpu
	.endm

	.macro RESTORE_ALL
		pop_fpu
		setgie.d
		dsb

		.if (regno == 4)
		popm	$r0, $r6		/* $0 is dummy */
		MTUSR_ZOL "$r3","$r4","$r5"
		MTUSR_IFC "$r6"
		.else
		.if (regno == 3)
		popm	$r1, $r5
		MTUSR_ZOL "$r3","$r4","$r5"
		.else
		.if (regno == 1)
		popm	$r1, $r3
		MTUSR_IFC "$r3"
		.else
		popm	$r1, $r2
		.endif
		.endif
		.endif

		mtsr	$r1, $IPC
		mtsr	$r2, $IPSW

		popm	$r6, $r30
		popm	$r0, $r5
	.endm

	/* Nested IRQ save and restore routines*/
	.macro SAVE_CALLER
		pushm	$r15,$r30		/* full: 16 gpr, reduce: 4 gpr */

		.if (regno == 4)
		MFUSR_ZOL "$r1","$r2","$r3"
		MFUSR_IFC "$r4"
		pushm	$r1, $r4

		mfsr	$r1, $IPC
		mfsr	$r2, $IPSW
		pushm	$r1, $r2
		.else
		mfsr	$r1, $IPC
                mfsr	$r2, $IPSW
		.if (regno == 3)
		MFUSR_ZOL "$r3","$r4","$r5"
		pushm	$r0, $r5		/* $0 is dummy */
		.else
		.if (regno == 1)
		MFUSR_IFC "$r3"
		pushm	$r0, $r3		/* $r0 is dummy */
		.else
		pushm	$r1, $r2
		.endif
		.endif
		.endif

		push_fpu_caller
	.endm

	.macro RESTORE_CALLER
		pop_fpu_caller
		setgie.d
		dsb

		.if (regno == 4)
		popm $r1, $r2
		mtsr	$r1, $IPC
		mtsr	$r2, $IPSW

		popm	$r1, $r4
		MTUSR_ZOL "$r1","$r2","$r3"
                MTUSR_IFC "$r4"
		.else
		.if (regno == 3)
		popm	$r0, $r5		/* $0 is dummy */
		MTUSR_ZOL "$r3","$r4","$r5"
		.else
		.if (regno == 1)
		popm	$r0, $r3		/* $0 is dummy */
		MTUSR_IFC "$r3"
		.else
		popm	$r1, $r2
		.endif
		.endif
		mtsr	$r1, $IPC
		mtsr	$r2, $IPSW
		.endif

		popm	$r15,$r30		/* full: 16 gpr, reduce: 4 gpr*/
		popm	$r0, $r5
	.endm

	/* Non-Nested IRQ save and restore routines */
	.macro SAVE_CALLER_UNNESTED
		pushm	$r15,$r30		/* full: 16 gpr, reduce: 4 gpr */

		.if (regno == 1)
		MFUSR_IFC "$r1"
		pushm	$r0, $r1		/* $r0 is dummy */
		.endif

		push_fpu_caller
	.endm

	.macro RESTORE_CALLER_UNNESTED
		pop_fpu_caller

		.if (regno == 1)
		setgie.d
		dsb
		popm	$r0, $r1		/* $0 is dummy */
		MTUSR_IFC "$r1"
		.endif

		popm	$r15,$r30		/* full: 16 gpr, reduce: 4 gpr*/
		popm	$r0, $r5
	.endm
