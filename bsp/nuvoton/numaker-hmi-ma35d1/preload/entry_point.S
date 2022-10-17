.section ".text.entrypoint"
.globl system_vectors

ma35d1_start:
    .word    0x10000014
    .word    0x9100029f
    .word    0xd539f220
    .word    0xb27a0000
    .word    0xd519f220
    .word    0xd53800a1
    .word    0x92400421
    .word    0xb4000141
    .word    0xd503205f
    .word    0xd2800900
    .word    0xf2a808c0
    .word    0xf9400001
    .word    0xf100003f
    .word    0x54ffff60
    .word    0x91001000
    .word    0xb9000001
    .word    0x14000012
    .word    0xd2800980
    .word    0xf2a808c0
    .word    0xaa1f03e1
    .word    0xb9000001
    .word    0xd282000a
    .word    0xd100054a
    .word    0xf100015f
    .word    0x54000140
    .word    0xd2800900
    .word    0xf2a808c0
    .word    0xaa1403e1
    .word    0xb9000001
    .word    0xd503209f
    .word    0x91001000
    .word    0xb9400002
    .word    0xeb02003f
    .word    0x54fffea1
    .word    0xd2836000
    .word    0xf2a016e0
    .word    0xd51be000
    .word    0xd2820000
    .word    0xf2aa1000
    .word    0x52800069
    .word    0xb9000009
    .word    0xb9400409
    .word    0x1200112a
    .word    0x340001aa
    .word    0x9102000b
    .word    0x52800009
    .word    0xb8004569
    .word    0xb8004569
    .word    0x5100054a
    .word    0x35ffffca
    .word    0xd2840001
    .word    0xf2aa1001
    .word    0x52800060
    .word    0xb9000020
    .word    0x52801000
    .word    0xb9000420
    .word    0xd2820000
    .word    0xf2aa1000
    .word    0xd2840001
    .word    0xf2aa1001
    .word    0x52800009
    .word    0xb9008009
    .word    0x52800029
    .word    0xb9010009
    .word    0x52803ce9
    .word    0xb9000029
    .word    0x52801009
    .word    0xb9000429
    .word    0xd2a00600
    .word    0xd5181040
    .word    0xaa1f03e0
    .word    0xb2630000
    .word    0xb2640000
    .word    0xb2690000
    .word    0xb26a0000
    .word    0xb26c0000
    .word    0xb2750000
    .word    0xd5181000
    .word    0xaa1f03e0
    .word    0xb2770000
    .word    0xb2780000
    .word    0xb2790000
    .word    0xb27b0000
    .word    0xb27c0000
    .word    0xd51e1100
    .word    0xaa1f03e0
    .word    0xd2800060
    .word    0xb2780000
    .word    0xb2790000
    .word    0xb27a0000
    .word    0xb27c0000
    .word    0xd51e4000
    .word    0x10000060
    .word    0xd51e4020
    .word    0xd69f03e0

.L__aarch32_code:

    nop
    nop
    nop
    nop
    ldr     r0, =ma35d1_start
    mov     sp, r0
    ldr     pc, =system_vectors
