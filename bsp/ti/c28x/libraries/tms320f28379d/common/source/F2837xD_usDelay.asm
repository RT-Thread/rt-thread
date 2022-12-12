;//###########################################################################
;//
;// FILE: F2837xD_usDelay.asm
;//
;// TITLE: Simple delay function
;//
;// DESCRIPTION:
;// This is a simple delay function that can be used to insert a specified
;// delay into code.
;// This function is only accurate if executed from internal zero-waitstate
;// SARAM. If it is executed from waitstate memory then the delay will be
;// longer then specified.
;// To use this function:
;//  1 - update the CPU clock speed in the F2837xD_Examples.h
;//    file. For example:
;//    #define CPU_RATE 6.667L // for a 150MHz CPU clock speed
;//  2 - Call this function by using the DELAY_US(A) macro
;//    that is defined in the F2837xD_Device.h file.  This macro
;//    will convert the number of microseconds specified
;//    into a loop count for use with this function.
;//    This count will be based on the CPU frequency you specify.
;//  3 - For the most accurate delay
;//    - Execute this function in 0 waitstate RAM.
;//    - Disable interrupts before calling the function
;//      If you do not disable interrupts, then think of
;//      this as an "at least" delay function as the actual
;//      delay may be longer.
;//  The C assembly call from the DELAY_US(time) macro will
;//  look as follows:
;//  extern void Delay(long LoopCount);
;//        MOV   AL,#LowLoopCount
;//        MOV   AH,#HighLoopCount
;//        LCR   _Delay
;//  Or as follows (if count is less then 16-bits):
;//        MOV   ACC,#LoopCount
;//        LCR   _Delay
;//
;//###########################################################################
;// $TI Release: F2837xD Support Library v3.05.00.00 $
;// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
;// $Copyright:
;// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;//###########################################################################

       .cdecls LIST ;;Used to populate __TI_COMPILER_VERSION__ macro
       %{
           #ifdef __TI_EABI__
           #define __EABI__ 1
           #else
           #define __EABI__ 0
           #endif
       %}

       .if __EABI__
       .def F28x_usDelay
       .else
       .def _F28x_usDelay
       .endif

       .if __TI_COMPILER_VERSION__
       .if __TI_COMPILER_VERSION__ >= 15009000
       .sect ".TI.ramfunc"      ;;Used with compiler v15.9.0 and newer
       .else
       .sect "ramfuncs"         ;;Used with compilers older than v15.9.0
       .endif
       .endif

        .global  __F28x_usDelay

       .if __EABI__
F28x_usDelay:
       .else
_F28x_usDelay:
       .endif

        SUB    ACC,#1
       .if __EABI__
        BF     F28x_usDelay,GEQ    ;; Loop if ACC >= 0
       .else
        BF     _F28x_usDelay,GEQ    ;; Loop if ACC >= 0
       .endif

        LRETR

;There is a 9/10 cycle overhead and each loop
;takes five cycles. The LoopCount is given by
;the following formula:
;  DELAY_CPU_CYCLES = 9 + 5*LoopCount
; LoopCount = (DELAY_CPU_CYCLES - 9) / 5
; The macro DELAY_US(A) performs this calculation for you
;
;

;//
;// End of file
;//
