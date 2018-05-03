/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. 

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************/

/* Start-up code for M16C targets only */

.text
	.global	_start
	.type	_start, @function
	
_start:
	ldc	#_istack, isp	/* set interrupt stack pointer */

#ifndef EXT_RAM
 
        mov.b	#0x02,0x0a	 	/* write enable in protect register */
	mov.b	#0x00,0x04		/* set processer mode  :single chip mode */
					/* 0x04 is the address of processor mode register 0 */
	mov.b	#0x00,0x0a		/* write disable in protect register */
#endif

#if EXT_RAM 
        mov.w #0x000a,a0		  /* Write enable in protect register */
        mov.b #0xff,[a0]		 
        
        mov.w #0x04,a0			  /* Memory expansion mode, WRH/WRL/RD signals */
        mov.b #0x05,[a0]

        mov.w #0x05,a0			  /* Insert wait, no limit in on-chip memory */
        mov.b #0x88,[a0]		  

        mov.w #0x08,a0			  /* Enable all the CS signals with wait */
        mov.b #0x0F,[a0]

        mov.w #0x0a,a0			 /* write disable in protect register */
        mov.b #0x00,[a0]
#endif

;	ldc	#0x0080,flg		/* select USER STACK POINTER (BIT7=1,USP) (BIT7=0,ISP) */
;	ldc	#_ustack,sp		/* set user stack pointer */
	
	/* INTERRUPT VECTOR ADDRESS  definition	*/
	ldc 	#0xF, intbh	/* load upper 4 bits of variable vector address in intbh */
	ldc 	#0xA000, intbl	/* load lower 16 bits of variable vector address in intbl */

	fset	I			/* ADD THIS TO ENABLE INTERRUPTS */
		
	/* call the hardware initialiser */
;	jsr.a	 _hw_initialise
	


/* load data section from ROM to RAM */
         
 	mov.b	#%hi8(_mdata),r1h	/* move upper 4 bits of the 20 bit address (_mdata) to, r1h */
	mov.w	#%lo16(_mdata),a0	/* move lower 16 bits of the 20 bit address (_mdata) to,a0 */	
	mov.w	#_data,a1		/* store the start address of data section in, A1 */
	mov.w	#_edata,r3		/* store the end address of data section in R3 */
	sub.w	a1,r3			/* R3=R3-A1. Store size of data section in R3 */
	mov.w	r3,r2			/* Store size of data section in R2 */
	smovf.b

/* bss initialisation : zero out bss */

	mov.b	#0x00,R0L  		/* load R0L reg with 0x0 (value at which bss section will be initialised) */
	mov.w	#_bss, a1  		/* store the start address of bss in A1 */
	mov.w	#_ebss, a0 		/* store the end address of bss in A0 */
	sub.w   a1,a0	   		/* (A0 = A0-A1) */
	mov.w   a0,r3	   		/* Store size of bss section in reg R3 */
	sstr.b

#if EXT_RAM
/* load fdata section from ROM to External RAM only if EXT_RAM is defined */

        pushc   sp                	/*store stack pointer in stack */
        popc    fb                	/*copy the stack pointer in frame base register */

	push.w  #%hi16(_mdata)    	/* offset of -2 from fb: store higher 16 bits of _mdata */
	push.w  #%lo16(_mdata)    	/* offset of -4 from fb: store lower 16 bits of _mdata */
        
	mov.w	#_edata,r0        	/* end address of data section */
	mov.w	#_data,r1         	/* start address of data section */
	sub.w	r1,r0             	/* size of data section in r0 */

	add.w	r0,-4[fb]         	/* store the lower 16 bits of source address on stack */
	adc.w   #0,-2[fb]         	/* store the higher 4 bits of source address on stack */

        push.w  #%hi16(_fdata)    	/* offset -6 from fp: store the higher 4 bits of destination address on stack */
        push.w  #%lo16(_fdata)     	/* offset -8 from fp: store the lower 16 bits of destination address on stack */
        
                
        push.w	#%hi16(_efdata)   	/* offset -10 from fp: higher 16 bits of _efdata */
	push.w	#%lo16(_efdata)   	/* offset -12 from fp: lower 16 bits of _efdata */
	
label1:	
        cmp.w   -6[fb],-10[fb]    	/* Compare higher 16 bits of _fdata and _efdata */
        jnz     label2
        cmp.w   -8[fb],-12[fb]    	/* Compare lower 16 bits of _fdata and _efdata */
        jeq	init_fdata_end
        
        
label2:
	mov.w   -2[fb],a1	 	/* Copy higher 16 bits of source in A1 */
        mov.w   -4[fb],a0	 	/* Copy lower 16 bits of source in A1 */
        lde.b	[a1a0],r0l	 	/* Copy contents of a1a0 in r0l */
        mov.w   -6[fb],a1	 	/* Copy higher 16 bits of destination in A1 */
        mov.w   -8[fb],a0	 	/* Copy lower 16 bits of destination in A0 */
        ste.b 	r0l,[a1a0]	 	/* store r0l contents at [a1a0] */
               
        add.w	#0x01,-4[fb]	 	/* increment lower 16 bits of source */
        adcf.w	-2[fb]   	 	/* add carry to higher 16 bits of source */
        add.w	#0x01,-8[fb]	 	/* increment lower 16 bits of destination */
        adcf.w	-6[fb]           	/* add carry to higher 16 bits of destination */
        
        jmp.b	label1
        
init_fdata_end:
        pop.w  r0			/* clean stack */
        pop.w  r0
        pop.w  r0
        pop.w  r0
        pop.w  r0
        pop.w  r0 

/* Zero out fbss section */
   
        push.w  #%hi16(_fbss)    	/* offset of -2 from fb: higher 16 bits of _fbss */
        push.w  #%lo16(_fbss)    	/* offset of -4 from fb: lower 16 bits of _fbss */
	push.w  #%hi16(_efbss)   	/* offset of -6 from fb: higer 16 bits of _efbss */
        push.w  #%lo16(_efbss)   	/* offset of -8 from fb: lower 16 bits of _efbss */
        mov.b   #0x00,r0l
label3:
        cmp.w   -2[fb],-6[fb]    	/* Compare higher 16 bits of _fdata and _efdata */
        jnz     label4
        cmp.w   -4[fb],-8[fb]    	/* Compare lower 16 bits of _fdata and _efdata */
        jeq     init_fbss_end

label4:
        mov.w   -2[fb],a1        	/* Copy higher 16 bits of source in A1 */
        mov.w   -4[fb],a0        	/* Copy lower 16 bits of source in A1 */
        ste.b   r0l,[a1a0]       	/* store r0l contents at [a1a0] */

        add.w   #0x01,-4[fb]     	/* increment lower 16 bits of _fbss */
        adcf.w  -2[fb]           	/* add carry to higher 16 bits of _fbss */

        jmp.b   label3

init_fbss_end:
	pop.w   r0			/* clean stack */
        pop.w   r0
        pop.w   r0
        pop.w   r0
#endif

/* start user program */
	jsr.a	_main		
	
	.end

