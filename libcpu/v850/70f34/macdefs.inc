; 
;       These are the macros used by the v850 port of the uCOS/II. 
; 
 
 
 
 
 
;******************************************************************** 
;	function: 
;	description: 
;	--- Modifies ---------------------------------------------- 
;		   IO : 
;		   Mem: 
;		   CPU: 
;	--- Uses -------------------------------------------------- 
;		   IO : 
;		   Mem: 
;	--- Input ------------------------------------------------- 
;	--- Output ------------------------------------------------ 
;	--- Notes ------------------------------------------------- 
;==================================================================== 
 
SAVE_CPU_CTX MACRO 
	;Save all registers on entry (r3 is the stack pointer) 
	prepare {r23,r24,r25,r26,r27,r28,r29,r30,r31},(8+(4*14))	 ;Add 8 bytes for 2 more registers 
	mov sp, ep 
        sst.w r1, 0[ep] 
	sst.w r2, 4[ep] 
	sst.w r5, 8[ep] 
	sst.w r6, 12[ep] 
	sst.w r7, 16[ep] 
	sst.w r8, 20[ep] 
	sst.w r9, 24[ep] 
	sst.w r10, 28[ep] 
	sst.w r11, 32[ep] 
	sst.w r12, 36[ep] 
	sst.w r13, 40[ep] 
	sst.w r14, 44[ep] 
	sst.w r15, 48[ep] 
	sst.w r16, 52[ep] 
	;Save caller's PC 
	stsr EIPC, r1 
	sst.w r1, 56[ep] 
	;Save caller's PSW 
	stsr EIPSW, r1 
	sst.w r1, 60[ep] 
 
        ENDMAC 
 
 
 
 
 
;******************************************************************** 
;	function: 
;	description: 
;	--- Modifies ---------------------------------------------- 
;		   IO : 
;		   Mem: 
;		   CPU: 
;	--- Uses -------------------------------------------------- 
;		   IO : 
;		   Mem: 
;	--- Input ------------------------------------------------- 
;	--- Output ------------------------------------------------ 
;	--- Notes ------------------------------------------------- 
;==================================================================== 
SAVE_SP MACRO 
	;Save stack pointer on OSTCBCur->OSTCBStkPtr (OSTCBStkPtr=0) 
	mov OSTCBCur, r21 
	ld.w 0[r21], r21 
	st.w sp, 0[r21] 
        ENDMAC 
 
 
 
;******************************************************************** 
;	function: 
;	description: 
;	--- Modifies ---------------------------------------------- 
;		   IO : 
;		   Mem: 
;		   CPU: 
;	--- Uses -------------------------------------------------- 
;		   IO : 
;		   Mem: 
;	--- Input ------------------------------------------------- 
;	--- Output ------------------------------------------------ 
;	--- Notes ------------------------------------------------- 
;==================================================================== 
ISR_ENTRY  MACRO 
        LOCAL _DontSaveSP 
 
        ;Save all CPU registers according to the standard stack frame 
        SAVE_CPU_CTX 
 
	mov OSIntNesting, r1                   ;Increment OSNesting by one 
	LD.BU	0[r1],r2 
        add 1, r2 
	ST.B  r2, 0[r1] 
        cmp 1, r2                              ;If OSNesting==1 save SP in current TCB 
        bne _DontSaveSP 
        SAVE_SP 
_DontSaveSP: 
        ENDMAC 
 
;******************************************************************** 
;	function: 
;	description: 
;	--- Modifies ---------------------------------------------- 
;		   IO : 
;		   Mem: 
;		   CPU: 
;	--- Uses -------------------------------------------------- 
;		   IO : 
;		   Mem: 
;	--- Input ------------------------------------------------- 
;	--- Output ------------------------------------------------ 
;	--- Notes ------------------------------------------------- 
;==================================================================== 
ISR_EXIT MACRO 
        jarl OSIntExit, lp                      ;Call OSIntExit() 
	jr OS_Restore_CPU_Context               ;Restore processors registers and execute RETI 
        ENDMAC 
