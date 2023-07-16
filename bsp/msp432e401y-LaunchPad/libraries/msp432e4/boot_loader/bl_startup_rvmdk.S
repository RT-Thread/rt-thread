;******************************************************************************
;
; bl_startup_rvmdk.S - Startup code for RV-MDK.
;
; Copyright (c) 2007-2017 Texas Instruments Incorporated.  All rights reserved.
; Software License Agreement
;
; Texas Instruments (TI) is supplying this software for use solely and
; exclusively on TI's microcontroller products. The software is owned by
; TI and/or its suppliers, and is protected under applicable copyright
; laws. You may not combine this software with "viral" open-source
; software in order to form a larger program.
;
; THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
; NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
; NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
; CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
; DAMAGES, FOR ANY REASON WHATSOEVER.
;
;******************************************************************************

    include bl_config.inc

;******************************************************************************
;
; A couple of defines that would normally be obtained from the appropriate C
; header file, but must be manually provided here since the Keil compiler does
; not have a mechanism for passing assembly source through the C preprocessor.
;
;******************************************************************************
SYSCTL_RESC                     equ     0x400fe05c
SYSCTL_RESC_MOSCFAIL            equ     0x00010000
NVIC_VTABLE                     equ     0xe000ed08

;******************************************************************************
;
; Put the assembler into the correct configuration.
;
;******************************************************************************
    thumb
    require8
    preserve8

;******************************************************************************
;
; The stack gets placed into the zero-init section.
;
;******************************************************************************
    area    ||.bss||, noinit, align=2

;******************************************************************************
;
; Allocate storage for the stack.
;
;******************************************************************************
g_pulStack
    space   _STACK_SIZE * 4

;******************************************************************************
;
; This portion of the file goes into the reset section.
;
;******************************************************************************
    area    RESET, code, readonly, align=3

;******************************************************************************
;
; The minimal vector table for a Cortex-M3 processor.
;
;******************************************************************************
    export  __Vectors
__Vectors
    dcd     g_pulStack + (_STACK_SIZE * 4)  ; Offset 00: Initial stack pointer
    dcd     Reset_Handler                   ; Offset 04: Reset handler
    dcd     NmiSR                           ; Offset 08: NMI handler
    dcd     FaultISR                        ; Offset 0C: Hard fault handler
    dcd     IntDefaultHandler               ; Offset 10: MPU fault handler
    dcd     IntDefaultHandler               ; Offset 14: Bus fault handler
    dcd     IntDefaultHandler               ; Offset 18: Usage fault handler
    dcd     0                               ; Offset 1C: Reserved
    dcd     0                               ; Offset 20: Reserved
    dcd     0                               ; Offset 24: Reserved
    dcd     0                               ; Offset 28: Reserved
    dcd     UpdateHandler                   ; Offset 2C: SVCall handler
    dcd     IntDefaultHandler               ; Offset 30: Debug monitor handler
    dcd     0                               ; Offset 34: Reserved
    dcd     IntDefaultHandler               ; Offset 38: PendSV handler
    if      :def:_ENET_ENABLE_UPDATE
    import  SysTickIntHandler
    dcd     SysTickIntHandler               ; Offset 3C: SysTick handler
    else
    dcd     IntDefaultHandler               ; Offset 3C: SysTick handler
    endif
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 0)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 040: GPIO port A handler
    else
    dcd     IntDefaultHandler               ; Offset 040: GPIO port A handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 040: GPIO port A handler
    endif
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 1)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 044: GPIO port B handler
    else
    dcd     IntDefaultHandler               ; Offset 044: GPIO port B handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 044: GPIO port B handler
    endif
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 2)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 048: GPIO port C handler
    else
    dcd     IntDefaultHandler               ; Offset 048: GPIO port C handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 048: GPIO port C handler
    endif
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 3)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 04C: GPIO port D handler
    else
    dcd     IntDefaultHandler               ; Offset 04C: GPIO port D handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 04C: GPIO port D handler
    endif
    dcd     IntDefaultHandler               ; Offset 050: GPIO Port E
    dcd     IntDefaultHandler               ; Offset 054: UART0 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 058: UART1 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 05C: SSI0 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 060: I2C0 Master and Slave
    dcd     IntDefaultHandler               ; Offset 064: PWM Fault
    dcd     IntDefaultHandler               ; Offset 068: PWM Generator 0
    dcd     IntDefaultHandler               ; Offset 06C: PWM Generator 1
    dcd     IntDefaultHandler               ; Offset 070: PWM Generator 2
    dcd     IntDefaultHandler               ; Offset 074: Quadrature Encoder 0
    dcd     IntDefaultHandler               ; Offset 078: ADC Sequence 0
    dcd     IntDefaultHandler               ; Offset 07C: ADC Sequence 1
    dcd     IntDefaultHandler               ; Offset 080: ADC Sequence 2
    dcd     IntDefaultHandler               ; Offset 084: ADC Sequence 3
    dcd     IntDefaultHandler               ; Offset 088: Watchdog timer
    dcd     IntDefaultHandler               ; Offset 08C: Timer 0 subtimer A
    dcd     IntDefaultHandler               ; Offset 090: Timer 0 subtimer B
    dcd     IntDefaultHandler               ; Offset 094: Timer 1 subtimer A
    dcd     IntDefaultHandler               ; Offset 098: Timer 1 subtimer B
    dcd     IntDefaultHandler               ; Offset 09C: Timer 2 subtimer A
    dcd     IntDefaultHandler               ; Offset 0A0: Timer 2 subtimer B
    dcd     IntDefaultHandler               ; Offset 0A4: Analog Comparator 0
    dcd     IntDefaultHandler               ; Offset 0A8: Analog Comparator 1
    dcd     IntDefaultHandler               ; Offset 0AC: Analog Comparator 2
    dcd     IntDefaultHandler               ; Offset 0B0: System Control
    dcd     IntDefaultHandler               ; Offset 0B4: FLASH Control
    dcd     IntDefaultHandler               ; Offset 0B8: GPIO Port F
    dcd     IntDefaultHandler               ; Offset 0BC: GPIO Port G
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 7)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 0C0: GPIO port H handler
    else
    dcd     IntDefaultHandler               ; Offset 0C0: GPIO port H handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 0C0: GPIO port H handler
    endif
    dcd     IntDefaultHandler               ; Offset 0C4: UART2 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 0C8: SSI1 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 0CC: Timer 3 subtimer A
    dcd     IntDefaultHandler               ; Offset 0D0: Timer 3 subtimer B
    dcd     IntDefaultHandler               ; Offset 0D4: I2C1 Master and Slave
    dcd     IntDefaultHandler               ; Offset 0D8: CAN0
    dcd     IntDefaultHandler               ; Offset 0DC: CAN1
    dcd     IntDefaultHandler               ; Offset 0E0: Ethernet
    dcd     IntDefaultHandler               ; Offset 0E4: Hibernation module
    if      :def:_USB_ENABLE_UPDATE
    import  USB0DeviceIntHandler
    dcd     USB0DeviceIntHandler            ; Offset 0E8: USB 0 Controller
    else
    dcd     IntDefaultHandler               ; Offset 0E8: USB 0 Controller
    endif
    dcd     IntDefaultHandler               ; Offset 0EC: PWM Generator 3
    dcd     IntDefaultHandler               ; Offset 0F0: uDMA 0 Software
    dcd     IntDefaultHandler               ; Offset 0F4: uDMA 0 Error
    dcd     IntDefaultHandler               ; Offset 0F8: ADC 1 Sequence 0
    dcd     IntDefaultHandler               ; Offset 0FC: ADC 1 Sequence 1
    dcd     IntDefaultHandler               ; Offset 100: ADC 1 Sequence 2
    dcd     IntDefaultHandler               ; Offset 104: ADC 1 Sequence 3
    dcd     IntDefaultHandler               ; Offset 108: EPI 0
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 8)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 10C: GPIO port J handler
    else
    dcd     IntDefaultHandler               ; Offset 10C: GPIO port J handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 10C: GPIO port J handler
    endif
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 9)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 110: GPIO port K handler
    else
    dcd     IntDefaultHandler               ; Offset 110: GPIO port K handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 110: GPIO port K handler
    endif
    dcd     IntDefaultHandler               ; Offset 114: GPIO Port L
    dcd     IntDefaultHandler               ; Offset 118: SSI2 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 11C: SSI3 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 120: UART3 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 124: UART4 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 128: UART5 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 12C: UART6 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 130: UART7 Rx and Tx
    dcd     IntDefaultHandler               ; Offset 134: I2C2 Master and Slave
    dcd     IntDefaultHandler               ; Offset 138: I2C3 Master and Slave
    dcd     IntDefaultHandler               ; Offset 13C: Timer 4 subtimer A
    dcd     IntDefaultHandler               ; Offset 140: Timer 4 subtimer B
    dcd     IntDefaultHandler               ; Offset 144: Timer 5 subtimer A
    dcd     IntDefaultHandler               ; Offset 148: Timer 5 subtimer B
    dcd     IntDefaultHandler               ; Offset 14C: FPU Exception
    dcd     IntDefaultHandler               ; Offset 150: Reserved
    dcd     IntDefaultHandler               ; Offset 154: Reserved
    dcd     IntDefaultHandler               ; Offset 158: I2C4 Master and Slave
    dcd     IntDefaultHandler               ; Offset 15C: I2C5 Master and Slave
    dcd     IntDefaultHandler               ; Offset 160: GPIO Port M
    dcd     IntDefaultHandler               ; Offset 164: GPIO Port N
    dcd     IntDefaultHandler               ; Offset 168: Reserved
    dcd     IntDefaultHandler               ; Offset 16C: Tamper
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 13)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 170: GPIO port P handler
    else
    dcd     IntDefaultHandler               ; Offset 170: GPIO port P handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 170: GPIO port P handler
    endif
    dcd     IntDefaultHandler               ; Offset 174: GPIO Port P1
    dcd     IntDefaultHandler               ; Offset 178: GPIO Port P2
    dcd     IntDefaultHandler               ; Offset 17C: GPIO Port P3
    dcd     IntDefaultHandler               ; Offset 180: GPIO Port P4
    dcd     IntDefaultHandler               ; Offset 184: GPIO Port P5
    dcd     IntDefaultHandler               ; Offset 188: GPIO Port P6
    dcd     IntDefaultHandler               ; Offset 18C: GPIO Port P7
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 14)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 190: GPIO port Q handler
    else
    dcd     IntDefaultHandler               ; Offset 190: GPIO port Q handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 190: GPIO port Q handler
    endif
    dcd     IntDefaultHandler               ; Offset 194: GPIO Port Q1
    dcd     IntDefaultHandler               ; Offset 198: GPIO Port Q2
    dcd     IntDefaultHandler               ; Offset 19C: GPIO Port Q3
    dcd     IntDefaultHandler               ; Offset 1A0: GPIO Port Q4
    dcd     IntDefaultHandler               ; Offset 1A4: GPIO Port Q5
    dcd     IntDefaultHandler               ; Offset 1A8: GPIO Port Q6
    dcd     IntDefaultHandler               ; Offset 1AC: GPIO Port Q7
    if      :def: _UART_ENABLE_UPDATE :land: :def:_UART_AUTOBAUD
    if      (_UART_AUTOBAUD== 15)
    import  GPIOIntHandler
    dcd     GPIOIntHandler                  ; Offset 1B0: GPIO port R handler
    else
    dcd     IntDefaultHandler               ; Offset 1B0: GPIO port R handler
    endif
    else
    dcd     IntDefaultHandler               ; Offset 1B0: GPIO port R handler
    endif
    dcd     IntDefaultHandler               ; Offset 1B4: GPIO Port S
    dcd     IntDefaultHandler               ; Offset 1B8: SHA/MD5
    dcd     IntDefaultHandler               ; Offset 1BC: AES

;******************************************************************************
;
; Initialize the processor by copying the boot loader from flash to SRAM, zero
; filling the .bss section, and moving the vector table to the beginning of
; SRAM.  The return address is modified to point to the SRAM copy of the boot
; loader instead of the flash copy, resulting in a branch to the copy now in
; SRAM.
;
;******************************************************************************
    export  ProcessorInit
ProcessorInit
    ;
    ; Copy the code image from flash to SRAM.
    ;
    movs    r0, #0x0000
    movs    r1, #0x0000
    movt    r1, #0x2000
    import  ||Image$$SRAM$$ZI$$Base||
    ldr     r2, =||Image$$SRAM$$ZI$$Base||
copy_loop
        ldr     r3, [r0], #4
        str     r3, [r1], #4
        cmp     r1, r2
        blt     copy_loop

    ;
    ; Zero fill the .bss section.
    ;
    movs    r0, #0x0000
    import  ||Image$$SRAM$$ZI$$Limit||
    ldr     r2, =||Image$$SRAM$$ZI$$Limit||
zero_loop
        str     r0, [r1], #4
        cmp     r1, r2
        blt     zero_loop

    ;
    ; Set the vector table pointer to the beginning of SRAM.
    ;
    movw    r0, #(NVIC_VTABLE & 0xffff)
    movt    r0, #(NVIC_VTABLE >> 16)
    movs    r1, #0x0000
    movt    r1, #0x2000
    str     r1, [r0]

    ;
    ; Return to the caller.
    ;
    bx      lr

;******************************************************************************
;
; The reset handler, which gets called when the processor starts.
;
;******************************************************************************
    export  Reset_Handler
Reset_Handler

    ;
    ; Enable the floating-point unit.  This must be done here in case any
    ; later C functions use floating point.  Note that some toolchains will
    ; use the FPU registers for general workspace even if no explicit floating
    ; point data types are in use.
    ;
    movw    r0, #0xED88
    movt    r0, #0xE000
    ldr     r1, [r0]
    orr     r1, #0x00F00000
    str     r1, [r0]

    ;
    ; Initialize the processor.
    ;
    bl      ProcessorInit

    ;
    ; Branch to the SRAM copy of the reset handler.
    ;
    ldr     pc, =Reset_Handler_In_SRAM

;******************************************************************************
;
; The NMI handler.
;
;******************************************************************************
NmiSR
    if      :def:_ENABLE_MOSCFAIL_HANDLER
    ;
    ; Grab the fault frame from the stack (the stack will be cleared by the
    ; processor initialization that follows).
    ;
    ldm     sp, {r4-r11}
    mov     r12, lr

    ;
    ; Initialize the processor.
    ;
    bl      ProcessorInit

    ;
    ; Branch to the SRAM copy of the NMI handler.
    ;
    ldr     pc, =NmiSR_In_SRAM
    else
    ;
    ; Loop forever since there is nothing that we can do about a NMI.
    ;
    b       .
    endif

;******************************************************************************
;
; The hard fault handler.
;
;******************************************************************************
FaultISR
    ;
    ; Loop forever since there is nothing that we can do about a hard fault.
    ;
    b       .

;******************************************************************************
;
; The update handler, which gets called when the application would like to
; start an update.
;
;******************************************************************************
UpdateHandler
    ;
    ; Initialize the processor.
    ;
    bl      ProcessorInit

    ;
    ; Branch to the SRAM copy of the update handler.
    ;
    ldr     pc, =UpdateHandler_In_SRAM

;******************************************************************************
;
; This portion of the file goes into the text section.
;
;******************************************************************************
    align   4
    area    ||.text||, code, readonly, align=2

Reset_Handler_In_SRAM
    ;
    ; Call the user-supplied low level hardware initialization function
    ; if provided.
    ;
    if      :def:_BL_HW_INIT_FN_HOOK
    import  $_BL_HW_INIT_FN_HOOK
    bl      $_BL_HW_INIT_FN_HOOK
    endif

    ;
    ; See if an update should be performed.
    ;
    import  CheckForceUpdate
    bl      CheckForceUpdate
    cbz     r0, CallApplication

    ;
    ; Configure the microcontroller.
    ;
EnterBootLoader
    if      :def:_ENET_ENABLE_UPDATE
    import  ConfigureEnet
    bl      ConfigureEnet
    elif    :def:_CAN_ENABLE_UPDATE
    import  ConfigureCAN
    bl      ConfigureCAN
    elif    :def:_USB_ENABLE_UPDATE
    import  ConfigureUSB
    bl      ConfigureUSB
    else
    import  ConfigureDevice
    bl      ConfigureDevice
    endif

    ;
    ; Call the user-supplied initialization function if provided.
    ;
    if      :def:_BL_INIT_FN_HOOK
    import  $_BL_INIT_FN_HOOK
    bl      $_BL_INIT_FN_HOOK
    endif

    ;
    ; Branch to the update handler.
    ;
    if      :def:_ENET_ENABLE_UPDATE
    import  UpdateBOOTP
    b       UpdateBOOTP
    elif    :def:_CAN_ENABLE_UPDATE
    import  UpdaterCAN
    b       UpdaterCAN
    elif    :def:_USB_ENABLE_UPDATE
    import  UpdaterUSB
    b       UpdaterUSB
    else
    import  Updater
    b       Updater
    endif

    ;
    ; This is a second symbol to allow starting the application from the boot
    ; loader the linker may not like the perceived jump.
    ;
    export StartApplication
StartApplication
    ;
    ; Call the application via the reset handler in its vector table.  Load the
    ; address of the application vector table.
    ;
CallApplication
    ;
    ; Copy the application's vector table to the target address if necessary.
    ; Note that incorrect boot loader configuration could cause this to
    ; corrupt the code!  Setting VTABLE_START_ADDRESS to 0x20000000 (the start
    ; of SRAM) is safe since this will use the same memory that the boot loader
    ; already uses for its vector table.  Great care will have to be taken if
    ; other addresses are to be used.
    ;
    if (_APP_START_ADDRESS != _VTABLE_START_ADDRESS)
    movw    r0, #(_VTABLE_START_ADDRESS & 0xffff)
    if (_VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(_VTABLE_START_ADDRESS >> 16)
    endif
    movw    r1, #(_APP_START_ADDRESS & 0xffff)
    if (_APP_START_ADDRESS > 0xffff)
    movt    r1, #(_APP_START_ADDRESS >> 16)
    endif

    ;
    ; Calculate the end address of the vector table assuming that it has the
    ; maximum possible number of vectors.  We don't know how many the app has
    ; populated so this is the safest approach though it may copy some non
    ; vector data if the app table is smaller than the maximum.
    ;
    movw    r2, #(70 * 4)
    adds    r2, r2, r0
VectorCopyLoop
        ldr     r3, [r1], #4
        str     r3, [r0], #4
        cmp     r0, r2
        blt     VectorCopyLoop
    endif

    ;
    ; Set the vector table address to the beginning of the application.
    ;
    movw    r0, #(_VTABLE_START_ADDRESS & 0xffff)
    if (_VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(_VTABLE_START_ADDRESS >> 16)
    endif
    movw    r1, #(NVIC_VTABLE & 0xffff)
    movt    r1, #(NVIC_VTABLE >> 16)
    str     r0, [r1]

    ;
    ; Load the stack pointer from the application's vector table.
    ;
    if (_APP_START_ADDRESS != _VTABLE_START_ADDRESS)
    movw    r0, #(_APP_START_ADDRESS & 0xffff)
    if (_APP_START_ADDRESS > 0xffff)
    movt    r0, #(_APP_START_ADDRESS >> 16)
    endif
    endif
    ldr     sp, [r0]

    ;
    ; Load the initial PC from the application's vector table and branch to
    ; the application's entry point.
    ;
    ldr     r0, [r0, #4]
    bx      r0

;******************************************************************************
;
; The update handler, which gets called when the application would like to
; start an update.
;
;******************************************************************************
UpdateHandler_In_SRAM
    ;
    ; Load the stack pointer from the vector table.
    ;
    movs    r0, #0x0000
    ldr     sp, [r0]

    ;
    ; Call the user-supplied low level hardware initialization function
    ; if provided.
    ;
    if      :def:_BL_HW_INIT_FN_HOOK
    bl      $_BL_HW_INIT_FN_HOOK
    endif

    ;
    ; Call the user-supplied re-initialization function if provided.
    ;
    if      :def:_BL_REINIT_FN_HOOK
    import  $_BL_REINIT_FN_HOOK
    bl      $_BL_REINIT_FN_HOOK
    endif

    ;
    ; Branch to the update handler.
    ;
    if      :def:_ENET_ENABLE_UPDATE
    b       UpdateBOOTP
    elif    :def:_CAN_ENABLE_UPDATE
    import  AppUpdaterCAN
    b       AppUpdaterCAN
    elif    :def:_USB_ENABLE_UPDATE
    import  AppUpdaterUSB
    b       AppUpdaterUSB
    else
    b       Updater
    endif

;******************************************************************************
;
; The NMI handler.
;
;******************************************************************************
    if      :def:_ENABLE_MOSCFAIL_HANDLER
NmiSR_In_SRAM
    ;
    ; Restore the stack frame.
    ;
    mov     lr, r12
    stm     sp, {r4-r11}

    ;
    ; Save the link register.
    ;
    mov     r9, lr

    ;
    ; Call the user-supplied low level hardware initialization function
    ; if provided.
    ;
    if      :def:_BL_HW_INIT_FN_HOOK
    bl      _BL_HW_INIT_FN_HOOK
    endif

    ;
    ; See if an update should be performed.
    ;
    bl      CheckForceUpdate
    cbz     r0, EnterApplication

        ;
        ; Clear the MOSCFAIL bit in RESC.
        ;
        movw    r0, #(SYSCTL_RESC & 0xffff)
        movt    r0, #(SYSCTL_RESC >> 16)
        ldr     r1, [r0]
        bic     r1, r1, #SYSCTL_RESC_MOSCFAIL
        str     r1, [r0]

        ;
        ; Fix up the PC on the stack so that the boot pin check is bypassed
        ; (since it has already been performed).
        ;
        ldr     r0, =EnterBootLoader
        bic     r0, #0x00000001
        str     r0, [sp, #0x18]

        ;
        ; Return from the NMI handler.  This will then start execution of the
        ; boot loader.
        ;
        bx      r9

    ;
    ; Restore the link register.
    ;
EnterApplication
    mov     lr, r9

    ;
    ; Copy the application's vector table to the target address if necessary.
    ; Note that incorrect boot loader configuration could cause this to
    ; corrupt the code!  Setting VTABLE_START_ADDRESS to 0x20000000 (the start
    ; of SRAM) is safe since this will use the same memory that the boot loader
    ; already uses for its vector table.  Great care will have to be taken if
    ; other addresses are to be used.
    ;
    if (_APP_START_ADDRESS != _VTABLE_START_ADDRESS)
    movw    r0, #(_VTABLE_START_ADDRESS & 0xffff)
    if (_VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(_VTABLE_START_ADDRESS >> 16)
    endif
    movw    r1, #(_APP_START_ADDRESS & 0xffff)
    if (_APP_START_ADDRESS > 0xffff)
    movt    r1, #(_APP_START_ADDRESS >> 16)
    endif

    ;
    ; Calculate the end address of the vector table assuming that it has the
    ; maximum possible number of vectors.  We don't know how many the app has
    ; populated so this is the safest approach though it may copy some non
    ; vector data if the app table is smaller than the maximum.
    ;
    movw    r2, #(70 * 4)
    adds    r2, r2, r0
VectorCopyLoop2
        ldr     r3, [r1], #4
        str     r3, [r0], #4
        cmp     r0, r2
        blt     VectorCopyLoop2
    endif

    ;
    ; Set the application's vector table start address.  Typically this is the
    ; application start address but in some cases an application may relocate
    ; this so we can't assume that these two addresses are equal.
    ;
    movw    r0, #(_VTABLE_START_ADDRESS & 0xffff)
    if (_VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(_VTABLE_START_ADDRESS >> 16)
    endif
    movw    r1, #(NVIC_VTABLE & 0xffff)
    movt    r1, #(NVIC_VTABLE >> 16)
    str     r0, [r1]

    ;
    ; Remove the NMI stack frame from the boot loader's stack.
    ;
    ldmia   sp, {r4-r11}

    ;
    ; Get the application's stack pointer.
    ;
    if (_APP_START_ADDRESS != _VTABLE_START_ADDRESS)
    movw    r0, #(_APP_START_ADDRESS & 0xffff)
    if (_APP_START_ADDRESS > 0xffff)
    movt    r0, #(_APP_START_ADDRESS >> 16)
    endif
    endif
    ldr     sp, [r0, #0x00]

    ;
    ; Fix up the NMI stack frame's return address to be the reset handler of
    ; the application.
    ;
    ldr     r10, [r0, #0x04]
    bic     r10, #0x00000001

    ;
    ; Store the NMI stack frame onto the application's stack.
    ;
    stmdb   sp!, {r4-r11}

    ;
    ; Branch to the application's NMI handler.
    ;
    ldr     r0, [r0, #0x08]
    bx      r0
    endif

;******************************************************************************
;
; The default interrupt handler.
;
;******************************************************************************
IntDefaultHandler
    ;
    ; Loop forever since there is nothing that we can do about an unexpected
    ; interrupt.
    ;
    b       .

;******************************************************************************
;
; Provides a small delay.  The loop below takes 3 cycles/loop.
;
;******************************************************************************
    export  Delay
Delay
    subs    r0, #1
    bne     Delay
    bx      lr

;******************************************************************************
;
; This is the end of the file.
;
;******************************************************************************
    align   4
    end
