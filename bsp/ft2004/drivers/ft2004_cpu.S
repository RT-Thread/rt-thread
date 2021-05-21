
#include "rtconfig.h"

.globl rt_hw_cpu_id 
rt_hw_cpu_id:
    push	{fp}		
    add	fp, sp, #0
    sub	sp, sp, #12
    mrc	p15, 0, r3, c0, c0, 5
    str	r3, [fp, #-8]
    ldr	r3, [fp, #-8]
    ubfx	r3, r3, #0, #12
    movw	r2, #257	
    cmp	r3, r2
    beq	core3 
    movw	r2, #257	
    cmp	r3, r2
    bgt	default 
    cmp	r3, #1
    beq	core1 
    cmp	r3, #256	
    beq	core2 
    b	default 
core1:	
    mov	r3, #1
    b	return 
core2:	
    mov	r3, #2
    b	return 
core3:	
    mov	r3, #3
    b	return 
default:	
    ldr	r3, [fp, #-8]
    and	r3, r3, #15
return:	
    mov	r0, r3
    add	sp, fp, #0
    pop	{fp}		 
    bx	lr 
