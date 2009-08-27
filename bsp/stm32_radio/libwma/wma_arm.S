	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8

MULT32	PROC
	EXPORT MULT32
	MOV      r2,r0
	SMULL    r1,r0,r2,r1
	BX		 lr
	ENDP

MULT31	PROC
	EXPORT MULT31
	SMULL    r2,r1,r0,r1
	LSL      r0,r1,#1
	BX       lr
	ENDP

MULT31_SHIFT15	PROC
	EXPORT MULT31_SHIFT15

	SMULL    r2,r1,r0,r1
	LSRS     r0,r2,#15
	ADC      r0,r0,r1,LSL #17
	BX       lr

	ENDP

XPROD32 PROC
	EXPORT XPROD32

	PUSH     {r4,r5,lr}
	SMULL    lr,r12,r0,r2
	SMLAL    lr,r12,r1,r3
	RSB      lr,r0,#0
	SMULL    r2,r0,r1,r2
	SMLAL    r2,r0,lr,r3
	LDR      r4,[sp,#0xc]
	LDR      r5,[sp,#0x10]
	STR      r12,[r4,#0]
	STR      r0,[r5,#0]
	POP      {r4,r5,pc}

	ENDP

XPROD31 PROC
	EXPORT XPROD31

	PUSH     {r4,r5,lr}
	SMULL    lr,r12,r0,r2
	SMLAL    lr,r12,r1,r3
	RSB      lr,r0,#0
	SMULL    r2,r0,r1,r2
	SMLAL    r2,r0,lr,r3
	LDR      r4,[sp,#0xc]
	LDR      r5,[sp,#0x10]
	LSL      r1,r12,#1
	LSL      r0,r0,#1
	STR      r1,[r4,#0]
	STR      r0,[r5,#0]
	POP      {r4,r5,pc}

	ENDP

XNPROD31	PROC
	EXPORT XNPROD31

	PUSH     {r4-r6,lr}
	SMULL    r4,r12,r0,r2
	RSB      lr,r1,#0
	SMLAL    r4,r12,lr,r3
	SMULL    lr,r2,r1,r2
	SMLAL    lr,r2,r0,r3
	LDR      r5,[sp,#0x10]
	LDR      r6,[sp,#0x14]
	LSL      r0,r12,#1
	STR      r0,[r5,#0]
	LSL      r0,r2,#1
	STR      r0,[r6,#0]
	POP      {r4-r6,pc}

	ENDP

CLIP_TO_15	PROC
	EXPORT CLIP_TO_15

	SUBS     r1, r0, #0x8000
	MOVPL    r0, #0x7f00
	ORRPL    r0, r0, #0xff
	ADDS     r1, r0, #0x8000
	MOVMI    r0,#0x8000
	BX 		 lr
	ENDP

	END
