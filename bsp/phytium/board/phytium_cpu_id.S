#include "fparameters.h"
#include "sdkconfig.h"

#ifndef __aarch64__
.globl cpu_id_mapping
cpu_id_mapping:
#if defined(CONFIG_TARGET_E2000Q)
cmp r0, #0 // compare cpu_id with 0
beq map_cpu_id_0
cmp r0, #1 // compare cpu_id with 1
beq map_cpu_id_1
cmp r0, #2 // compare cpu_id with 2
beq map_cpu_id_2
cmp r0, #3 // compare cpu_id with 3
beq map_cpu_id_3
mov pc, lr // no mapping needed
#endif
mov pc, lr // no mapping needed

// Mapping for E2000Q
map_cpu_id_0:
mov r0, #2
mov pc, lr

map_cpu_id_1:
mov r0, #3
mov pc, lr

map_cpu_id_2:
mov r0, #0
mov pc, lr

map_cpu_id_3:
mov r0, #1
mov pc, lr

.globl rt_asm_cpu_id 
rt_asm_cpu_id:
// read MPIDR
    mov r9, lr
    mrc p15, 0, r0, c0, c0, 5 
    ubfx r0, r0, #0, #12
    ldr r1,= CORE0_AFF
    cmp r0, r1
    beq core0

#if defined(CORE1_AFF)
    ldr r1,= CORE1_AFF
    cmp r0, r1
    beq core1
#endif

#if defined(CORE2_AFF)
    ldr r1,= CORE2_AFF
    cmp r0, r1
    beq core2
#endif

#if defined(CORE3_AFF)
    ldr r1,= CORE3_AFF
    cmp r0, r1
    beq core3
#endif

    b default

core0:
    mov r0, #0
    b return 

core1: 
    mov r0, #1
    b return 

core2: 
    mov r0, #2
    b return 

core3: 
    mov r0, #3
    b return 

core4: 
    mov r0, #4
    b return 

core5: 
    mov r0, #5
    b return 

core6: 
    mov r0, #6
    b return 

core8: 
    mov r0, #8
    b return 

default: 
    and r0, r0, #15

return: 

    bl cpu_id_mapping

    mov pc, r9

#else

.globl cpu_id_mapping
cpu_id_mapping:
#if defined(CONFIG_TARGET_E2000Q)
cmp x0, #0 // compare cpu_id with 0
beq map_cpu_id_0
cmp x0, #1 // compare cpu_id with 1
beq map_cpu_id_1
cmp x0, #2 // compare cpu_id with 2
beq map_cpu_id_2
cmp x0, #3 // compare cpu_id with 3
beq map_cpu_id_3
RET // no mapping needed
#endif
RET // no mapping needed

// Mapping for E2000Q
map_cpu_id_0:
mov x0, #2
RET

map_cpu_id_1:
mov x0, #3
RET

map_cpu_id_2:
mov x0, #0
RET

map_cpu_id_3:
mov x0, #1
RET


.globl rt_hw_cpu_id_set 
rt_hw_cpu_id_set:
    mov x9, lr 
    mrs x0,MPIDR_EL1
    and x1, x0, #15
    msr tpidr_el1, x1

    ubfx x0, x0, #0, #12
    ldr x1,= CORE0_AFF
    cmp x0, x1
    beq core0

#if defined(CORE1_AFF)
    ldr x1,= CORE1_AFF
    cmp x0, x1
    beq core1
#endif

#if defined(CORE2_AFF)
    ldr x1,= CORE2_AFF
    cmp x0, x1
    beq core2
#endif

#if defined(CORE3_AFF)
    ldr x1,= CORE3_AFF
    cmp x0, x1
    beq core3
#endif

    b default

core0:
    mov x0, #0
    b return 

core1: 
    mov x0, #1
    b return 

core2: 
    mov x0, #2
    b return 

core3: 
    mov x0, #3
    b return 

core4: 
    mov x0, #4
    b return 

core5: 
    mov x0, #5
    b return 

core6: 
    mov x0, #6
    b return 

core8: 
    mov x0, #8
    b return 

default: 
    and x0, x0, #15

return: 

    //bl cpu_id_mapping
    mov lr, x9
    RET


#endif

