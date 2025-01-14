;/**
; ******************************************************************************
;  @file  startup_hc32f4a0.s
;  @brief Startup for MDK.
; verbatim
;  Change Logs:
;  Date             Author          Notes
;  2022-03-31       CDT             First version
; endverbatim
; *****************************************************************************
; * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
; *
; * This software component is licensed by XHSC under BSD 3-Clause license
; * (the "License"); You may not use this file except in compliance with the
; * License. You may obtain a copy of the License at:
; *                    opensource.org/licenses/BSD-3-Clause
; *
; ******************************************************************************
; */

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00002000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00002000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; Peripheral Interrupts
                DCD     IRQ000_Handler
                DCD     IRQ001_Handler
                DCD     IRQ002_Handler
                DCD     IRQ003_Handler
                DCD     IRQ004_Handler
                DCD     IRQ005_Handler
                DCD     IRQ006_Handler
                DCD     IRQ007_Handler
                DCD     IRQ008_Handler
                DCD     IRQ009_Handler
                DCD     IRQ010_Handler
                DCD     IRQ011_Handler
                DCD     IRQ012_Handler
                DCD     IRQ013_Handler
                DCD     IRQ014_Handler
                DCD     IRQ015_Handler
                DCD     IRQ016_Handler
                DCD     IRQ017_Handler
                DCD     IRQ018_Handler
                DCD     IRQ019_Handler
                DCD     IRQ020_Handler
                DCD     IRQ021_Handler
                DCD     IRQ022_Handler
                DCD     IRQ023_Handler
                DCD     IRQ024_Handler
                DCD     IRQ025_Handler
                DCD     IRQ026_Handler
                DCD     IRQ027_Handler
                DCD     IRQ028_Handler
                DCD     IRQ029_Handler
                DCD     IRQ030_Handler
                DCD     IRQ031_Handler
                DCD     IRQ032_Handler
                DCD     IRQ033_Handler
                DCD     IRQ034_Handler
                DCD     IRQ035_Handler
                DCD     IRQ036_Handler
                DCD     IRQ037_Handler
                DCD     IRQ038_Handler
                DCD     IRQ039_Handler
                DCD     IRQ040_Handler
                DCD     IRQ041_Handler
                DCD     IRQ042_Handler
                DCD     IRQ043_Handler
                DCD     IRQ044_Handler
                DCD     IRQ045_Handler
                DCD     IRQ046_Handler
                DCD     IRQ047_Handler
                DCD     IRQ048_Handler
                DCD     IRQ049_Handler
                DCD     IRQ050_Handler
                DCD     IRQ051_Handler
                DCD     IRQ052_Handler
                DCD     IRQ053_Handler
                DCD     IRQ054_Handler
                DCD     IRQ055_Handler
                DCD     IRQ056_Handler
                DCD     IRQ057_Handler
                DCD     IRQ058_Handler
                DCD     IRQ059_Handler
                DCD     IRQ060_Handler
                DCD     IRQ061_Handler
                DCD     IRQ062_Handler
                DCD     IRQ063_Handler
                DCD     IRQ064_Handler
                DCD     IRQ065_Handler
                DCD     IRQ066_Handler
                DCD     IRQ067_Handler
                DCD     IRQ068_Handler
                DCD     IRQ069_Handler
                DCD     IRQ070_Handler
                DCD     IRQ071_Handler
                DCD     IRQ072_Handler
                DCD     IRQ073_Handler
                DCD     IRQ074_Handler
                DCD     IRQ075_Handler
                DCD     IRQ076_Handler
                DCD     IRQ077_Handler
                DCD     IRQ078_Handler
                DCD     IRQ079_Handler
                DCD     IRQ080_Handler
                DCD     IRQ081_Handler
                DCD     IRQ082_Handler
                DCD     IRQ083_Handler
                DCD     IRQ084_Handler
                DCD     IRQ085_Handler
                DCD     IRQ086_Handler
                DCD     IRQ087_Handler
                DCD     IRQ088_Handler
                DCD     IRQ089_Handler
                DCD     IRQ090_Handler
                DCD     IRQ091_Handler
                DCD     IRQ092_Handler
                DCD     IRQ093_Handler
                DCD     IRQ094_Handler
                DCD     IRQ095_Handler
                DCD     IRQ096_Handler
                DCD     IRQ097_Handler
                DCD     IRQ098_Handler
                DCD     IRQ099_Handler
                DCD     IRQ100_Handler
                DCD     IRQ101_Handler
                DCD     IRQ102_Handler
                DCD     IRQ103_Handler
                DCD     IRQ104_Handler
                DCD     IRQ105_Handler
                DCD     IRQ106_Handler
                DCD     IRQ107_Handler
                DCD     IRQ108_Handler
                DCD     IRQ109_Handler
                DCD     IRQ110_Handler
                DCD     IRQ111_Handler
                DCD     IRQ112_Handler
                DCD     IRQ113_Handler
                DCD     IRQ114_Handler
                DCD     IRQ115_Handler
                DCD     IRQ116_Handler
                DCD     IRQ117_Handler
                DCD     IRQ118_Handler
                DCD     IRQ119_Handler
                DCD     IRQ120_Handler
                DCD     IRQ121_Handler
                DCD     IRQ122_Handler
                DCD     IRQ123_Handler
                DCD     IRQ124_Handler
                DCD     IRQ125_Handler
                DCD     IRQ126_Handler
                DCD     IRQ127_Handler
                DCD     IRQ128_Handler
                DCD     IRQ129_Handler
                DCD     IRQ130_Handler
                DCD     IRQ131_Handler
                DCD     IRQ132_Handler
                DCD     IRQ133_Handler
                DCD     IRQ134_Handler
                DCD     IRQ135_Handler
                DCD     IRQ136_Handler
                DCD     IRQ137_Handler
                DCD     IRQ138_Handler
                DCD     IRQ139_Handler
                DCD     IRQ140_Handler
                DCD     IRQ141_Handler
                DCD     IRQ142_Handler
                DCD     IRQ143_Handler

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  IRQ000_Handler            [WEAK]
                EXPORT  IRQ001_Handler            [WEAK]
                EXPORT  IRQ002_Handler            [WEAK]
                EXPORT  IRQ003_Handler            [WEAK]
                EXPORT  IRQ004_Handler            [WEAK]
                EXPORT  IRQ005_Handler            [WEAK]
                EXPORT  IRQ006_Handler            [WEAK]
                EXPORT  IRQ007_Handler            [WEAK]
                EXPORT  IRQ008_Handler            [WEAK]
                EXPORT  IRQ009_Handler            [WEAK]
                EXPORT  IRQ010_Handler            [WEAK]
                EXPORT  IRQ011_Handler            [WEAK]
                EXPORT  IRQ012_Handler            [WEAK]
                EXPORT  IRQ013_Handler            [WEAK]
                EXPORT  IRQ014_Handler            [WEAK]
                EXPORT  IRQ015_Handler            [WEAK]
                EXPORT  IRQ016_Handler            [WEAK]
                EXPORT  IRQ017_Handler            [WEAK]
                EXPORT  IRQ018_Handler            [WEAK]
                EXPORT  IRQ019_Handler            [WEAK]
                EXPORT  IRQ020_Handler            [WEAK]
                EXPORT  IRQ021_Handler            [WEAK]
                EXPORT  IRQ022_Handler            [WEAK]
                EXPORT  IRQ023_Handler            [WEAK]
                EXPORT  IRQ024_Handler            [WEAK]
                EXPORT  IRQ025_Handler            [WEAK]
                EXPORT  IRQ026_Handler            [WEAK]
                EXPORT  IRQ027_Handler            [WEAK]
                EXPORT  IRQ028_Handler            [WEAK]
                EXPORT  IRQ029_Handler            [WEAK]
                EXPORT  IRQ030_Handler            [WEAK]
                EXPORT  IRQ031_Handler            [WEAK]
                EXPORT  IRQ032_Handler            [WEAK]
                EXPORT  IRQ033_Handler            [WEAK]
                EXPORT  IRQ034_Handler            [WEAK]
                EXPORT  IRQ035_Handler            [WEAK]
                EXPORT  IRQ036_Handler            [WEAK]
                EXPORT  IRQ037_Handler            [WEAK]
                EXPORT  IRQ038_Handler            [WEAK]
                EXPORT  IRQ039_Handler            [WEAK]
                EXPORT  IRQ040_Handler            [WEAK]
                EXPORT  IRQ041_Handler            [WEAK]
                EXPORT  IRQ042_Handler            [WEAK]
                EXPORT  IRQ043_Handler            [WEAK]
                EXPORT  IRQ044_Handler            [WEAK]
                EXPORT  IRQ045_Handler            [WEAK]
                EXPORT  IRQ046_Handler            [WEAK]
                EXPORT  IRQ047_Handler            [WEAK]
                EXPORT  IRQ048_Handler            [WEAK]
                EXPORT  IRQ049_Handler            [WEAK]
                EXPORT  IRQ050_Handler            [WEAK]
                EXPORT  IRQ051_Handler            [WEAK]
                EXPORT  IRQ052_Handler            [WEAK]
                EXPORT  IRQ053_Handler            [WEAK]
                EXPORT  IRQ054_Handler            [WEAK]
                EXPORT  IRQ055_Handler            [WEAK]
                EXPORT  IRQ056_Handler            [WEAK]
                EXPORT  IRQ057_Handler            [WEAK]
                EXPORT  IRQ058_Handler            [WEAK]
                EXPORT  IRQ059_Handler            [WEAK]
                EXPORT  IRQ060_Handler            [WEAK]
                EXPORT  IRQ061_Handler            [WEAK]
                EXPORT  IRQ062_Handler            [WEAK]
                EXPORT  IRQ063_Handler            [WEAK]
                EXPORT  IRQ064_Handler            [WEAK]
                EXPORT  IRQ065_Handler            [WEAK]
                EXPORT  IRQ066_Handler            [WEAK]
                EXPORT  IRQ067_Handler            [WEAK]
                EXPORT  IRQ068_Handler            [WEAK]
                EXPORT  IRQ069_Handler            [WEAK]
                EXPORT  IRQ070_Handler            [WEAK]
                EXPORT  IRQ071_Handler            [WEAK]
                EXPORT  IRQ072_Handler            [WEAK]
                EXPORT  IRQ073_Handler            [WEAK]
                EXPORT  IRQ074_Handler            [WEAK]
                EXPORT  IRQ075_Handler            [WEAK]
                EXPORT  IRQ076_Handler            [WEAK]
                EXPORT  IRQ077_Handler            [WEAK]
                EXPORT  IRQ078_Handler            [WEAK]
                EXPORT  IRQ079_Handler            [WEAK]
                EXPORT  IRQ080_Handler            [WEAK]
                EXPORT  IRQ081_Handler            [WEAK]
                EXPORT  IRQ082_Handler            [WEAK]
                EXPORT  IRQ083_Handler            [WEAK]
                EXPORT  IRQ084_Handler            [WEAK]
                EXPORT  IRQ085_Handler            [WEAK]
                EXPORT  IRQ086_Handler            [WEAK]
                EXPORT  IRQ087_Handler            [WEAK]
                EXPORT  IRQ088_Handler            [WEAK]
                EXPORT  IRQ089_Handler            [WEAK]
                EXPORT  IRQ090_Handler            [WEAK]
                EXPORT  IRQ091_Handler            [WEAK]
                EXPORT  IRQ092_Handler            [WEAK]
                EXPORT  IRQ093_Handler            [WEAK]
                EXPORT  IRQ094_Handler            [WEAK]
                EXPORT  IRQ095_Handler            [WEAK]
                EXPORT  IRQ096_Handler            [WEAK]
                EXPORT  IRQ097_Handler            [WEAK]
                EXPORT  IRQ098_Handler            [WEAK]
                EXPORT  IRQ099_Handler            [WEAK]
                EXPORT  IRQ100_Handler            [WEAK]
                EXPORT  IRQ101_Handler            [WEAK]
                EXPORT  IRQ102_Handler            [WEAK]
                EXPORT  IRQ103_Handler            [WEAK]
                EXPORT  IRQ104_Handler            [WEAK]
                EXPORT  IRQ105_Handler            [WEAK]
                EXPORT  IRQ106_Handler            [WEAK]
                EXPORT  IRQ107_Handler            [WEAK]
                EXPORT  IRQ108_Handler            [WEAK]
                EXPORT  IRQ109_Handler            [WEAK]
                EXPORT  IRQ110_Handler            [WEAK]
                EXPORT  IRQ111_Handler            [WEAK]
                EXPORT  IRQ112_Handler            [WEAK]
                EXPORT  IRQ113_Handler            [WEAK]
                EXPORT  IRQ114_Handler            [WEAK]
                EXPORT  IRQ115_Handler            [WEAK]
                EXPORT  IRQ116_Handler            [WEAK]
                EXPORT  IRQ117_Handler            [WEAK]
                EXPORT  IRQ118_Handler            [WEAK]
                EXPORT  IRQ119_Handler            [WEAK]
                EXPORT  IRQ120_Handler            [WEAK]
                EXPORT  IRQ121_Handler            [WEAK]
                EXPORT  IRQ122_Handler            [WEAK]
                EXPORT  IRQ123_Handler            [WEAK]
                EXPORT  IRQ124_Handler            [WEAK]
                EXPORT  IRQ125_Handler            [WEAK]
                EXPORT  IRQ126_Handler            [WEAK]
                EXPORT  IRQ127_Handler            [WEAK]
                EXPORT  IRQ128_Handler            [WEAK]
                EXPORT  IRQ129_Handler            [WEAK]
                EXPORT  IRQ130_Handler            [WEAK]
                EXPORT  IRQ131_Handler            [WEAK]
                EXPORT  IRQ132_Handler            [WEAK]
                EXPORT  IRQ133_Handler            [WEAK]
                EXPORT  IRQ134_Handler            [WEAK]
                EXPORT  IRQ135_Handler            [WEAK]
                EXPORT  IRQ136_Handler            [WEAK]
                EXPORT  IRQ137_Handler            [WEAK]
                EXPORT  IRQ138_Handler            [WEAK]
                EXPORT  IRQ139_Handler            [WEAK]
                EXPORT  IRQ140_Handler            [WEAK]
                EXPORT  IRQ141_Handler            [WEAK]
                EXPORT  IRQ142_Handler            [WEAK]
                EXPORT  IRQ143_Handler            [WEAK]

IRQ000_Handler
IRQ001_Handler
IRQ002_Handler
IRQ003_Handler
IRQ004_Handler
IRQ005_Handler
IRQ006_Handler
IRQ007_Handler
IRQ008_Handler
IRQ009_Handler
IRQ010_Handler
IRQ011_Handler
IRQ012_Handler
IRQ013_Handler
IRQ014_Handler
IRQ015_Handler
IRQ016_Handler
IRQ017_Handler
IRQ018_Handler
IRQ019_Handler
IRQ020_Handler
IRQ021_Handler
IRQ022_Handler
IRQ023_Handler
IRQ024_Handler
IRQ025_Handler
IRQ026_Handler
IRQ027_Handler
IRQ028_Handler
IRQ029_Handler
IRQ030_Handler
IRQ031_Handler
IRQ032_Handler
IRQ033_Handler
IRQ034_Handler
IRQ035_Handler
IRQ036_Handler
IRQ037_Handler
IRQ038_Handler
IRQ039_Handler
IRQ040_Handler
IRQ041_Handler
IRQ042_Handler
IRQ043_Handler
IRQ044_Handler
IRQ045_Handler
IRQ046_Handler
IRQ047_Handler
IRQ048_Handler
IRQ049_Handler
IRQ050_Handler
IRQ051_Handler
IRQ052_Handler
IRQ053_Handler
IRQ054_Handler
IRQ055_Handler
IRQ056_Handler
IRQ057_Handler
IRQ058_Handler
IRQ059_Handler
IRQ060_Handler
IRQ061_Handler
IRQ062_Handler
IRQ063_Handler
IRQ064_Handler
IRQ065_Handler
IRQ066_Handler
IRQ067_Handler
IRQ068_Handler
IRQ069_Handler
IRQ070_Handler
IRQ071_Handler
IRQ072_Handler
IRQ073_Handler
IRQ074_Handler
IRQ075_Handler
IRQ076_Handler
IRQ077_Handler
IRQ078_Handler
IRQ079_Handler
IRQ080_Handler
IRQ081_Handler
IRQ082_Handler
IRQ083_Handler
IRQ084_Handler
IRQ085_Handler
IRQ086_Handler
IRQ087_Handler
IRQ088_Handler
IRQ089_Handler
IRQ090_Handler
IRQ091_Handler
IRQ092_Handler
IRQ093_Handler
IRQ094_Handler
IRQ095_Handler
IRQ096_Handler
IRQ097_Handler
IRQ098_Handler
IRQ099_Handler
IRQ100_Handler
IRQ101_Handler
IRQ102_Handler
IRQ103_Handler
IRQ104_Handler
IRQ105_Handler
IRQ106_Handler
IRQ107_Handler
IRQ108_Handler
IRQ109_Handler
IRQ110_Handler
IRQ111_Handler
IRQ112_Handler
IRQ113_Handler
IRQ114_Handler
IRQ115_Handler
IRQ116_Handler
IRQ117_Handler
IRQ118_Handler
IRQ119_Handler
IRQ120_Handler
IRQ121_Handler
IRQ122_Handler
IRQ123_Handler
IRQ124_Handler
IRQ125_Handler
IRQ126_Handler
IRQ127_Handler
IRQ128_Handler
IRQ129_Handler
IRQ130_Handler
IRQ131_Handler
IRQ132_Handler
IRQ133_Handler
IRQ134_Handler
IRQ135_Handler
IRQ136_Handler
IRQ137_Handler
IRQ138_Handler
IRQ139_Handler
IRQ140_Handler
IRQ141_Handler
IRQ142_Handler
IRQ143_Handler
                B       .
                ENDP

                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
