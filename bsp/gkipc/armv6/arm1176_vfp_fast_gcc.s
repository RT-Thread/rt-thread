@*******************************************************************************
@*******************************************************************************
@**
@** ARM1176 Startup, VFP initialization for fast mode
@**
@** This module initializes the VFP co-processor unit in fast mode
@**
@** Version: $Id: arm1176_vfp_fast.s 5280 2011-02-21 16:39:28Z wlaris $
@**
@** (C) Copyright 2006-2010 by Fujitsu Microelectronics Europe GmbH;**
@** (C) Copyright 2010-2011 by Fujitsu Semiconductor Europe GmbH
@*******************************************************************************
@*******************************************************************************
#if ARM1176_USE_VFP == 1
    .text
    .section ".ARM1176INIT"
    .code 32

@*******************************************************************************
@** Bit pattern to enable RunFast mode
@** - FPSCR [24] - Flush to Zero mode
@** - FPSCR [25] - Default NaN mode
@*******************************************************************************

    .equ ARM1176_VFP_ENABLE,   0x40000000 @
    .equ ARM1176_VFP_FASTMODE, 0x03000000 @ 2_11:SHL:24

@*******************************************************************************
@** enable the fast-mode of the VFP block
@*******************************************************************************

    .global ARM1176_VfpSetFastmode

ARM1176_VfpSetFastmode:
    mov r0,#ARM1176_VFP_FASTMODE
    fmxr fpscr,r0
    bx lr

@*******************************************************************************
@** enable the the VFP block
@*******************************************************************************

    .global ARM1176_VfpInitialise

ARM1176_VfpInitialise:
    mrc p15,0,r1,c1,c0,2  @ r1 = Access Control Register
    orr r1,r1,#(0xf<<20)  @ enable full access for p10,11
    mcr p15,0,r1,c1,c0,2  @ Access Control Register = r1
    mov r1,#0             @
    mcr p15,0,r1,c7,c5,4  @ flush prefetch buffer because of FMXR below and
                          @ CP 10 & 11 were only just enabled
    @ Enable VFP itself
    mov  r0,#ARM1176_VFP_ENABLE
    fmxr fpexc,r0
    bx   lr

@*******************************************************************************
@** End of file
@*******************************************************************************

    .end
#endif
