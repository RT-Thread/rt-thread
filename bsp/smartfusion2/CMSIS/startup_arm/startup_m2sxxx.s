;*******************************************************************************
; (c) Copyright 2015 Microsemi SoC Products Group. All rights reserved.
;  SmartFusion2  startup code for Keil-MDK.
; 
;  SmartFusion2 vector table and startup code for ARM tool chain.
; 
;  SVN $Revision: 7419 $
;  SVN $Date: 2015-05-15 16:50:21 +0100 (Fri, 15 May 2015) $
;

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
stack_start
Stack_Mem       SPACE   Stack_Size
__initial_sp
stack_end


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


;===============================================================================
; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WdogWakeup_IRQHandler
                DCD     RTC_Wakeup_IRQHandler
                DCD     SPI0_IRQHandler
                DCD     SPI1_IRQHandler
                DCD     I2C0_IRQHandler
                DCD     I2C0_SMBAlert_IRQHandler
                DCD     I2C0_SMBus_IRQHandler
                DCD     I2C1_IRQHandler
                DCD     I2C1_SMBAlert_IRQHandler
                DCD     I2C1_SMBus_IRQHandler
                DCD     UART0_IRQHandler
                DCD     UART1_IRQHandler
                DCD     EthernetMAC_IRQHandler
                DCD     DMA_IRQHandler
                DCD     Timer1_IRQHandler
                DCD     Timer2_IRQHandler
                DCD     CAN_IRQHandler
                DCD     ENVM0_IRQHandler
                DCD     ENVM1_IRQHandler
                DCD     ComBlk_IRQHandler
                DCD     USB_IRQHandler
                DCD     USB_DMA_IRQHandler
                DCD     PLL_Lock_IRQHandler
                DCD     PLL_LockLost_IRQHandler
                DCD     CommSwitchError_IRQHandler
                DCD     CacheError_IRQHandler
                DCD     DDR_IRQHandler
                DCD     HPDMA_Complete_IRQHandler
                DCD     HPDMA_Error_IRQHandler
                DCD     ECC_Error_IRQHandler
                DCD     MDDR_IOCalib_IRQHandler
                DCD     FAB_PLL_Lock_IRQHandler
                DCD     FAB_PLL_LockLost_IRQHandler
                DCD     FIC64_IRQHandler
                DCD     FabricIrq0_IRQHandler
                DCD     FabricIrq1_IRQHandler
                DCD     FabricIrq2_IRQHandler
                DCD     FabricIrq3_IRQHandler
                DCD     FabricIrq4_IRQHandler
                DCD     FabricIrq5_IRQHandler
                DCD     FabricIrq6_IRQHandler
                DCD     FabricIrq7_IRQHandler
                DCD     FabricIrq8_IRQHandler
                DCD     FabricIrq9_IRQHandler
                DCD     FabricIrq10_IRQHandler
                DCD     FabricIrq11_IRQHandler
                DCD     FabricIrq12_IRQHandler
                DCD     FabricIrq13_IRQHandler
                DCD     FabricIrq14_IRQHandler
                DCD     FabricIrq15_IRQHandler                
                DCD     GPIO0_IRQHandler
                DCD     GPIO1_IRQHandler
                DCD     GPIO2_IRQHandler
                DCD     GPIO3_IRQHandler
                DCD     GPIO4_IRQHandler
                DCD     GPIO5_IRQHandler
                DCD     GPIO6_IRQHandler
                DCD     GPIO7_IRQHandler
                DCD     GPIO8_IRQHandler
                DCD     GPIO9_IRQHandler
                DCD     GPIO10_IRQHandler
                DCD     GPIO11_IRQHandler
                DCD     GPIO12_IRQHandler
                DCD     GPIO13_IRQHandler
                DCD     GPIO14_IRQHandler
                DCD     GPIO15_IRQHandler
                DCD     GPIO16_IRQHandler
                DCD     GPIO17_IRQHandler
                DCD     GPIO18_IRQHandler
                DCD     GPIO19_IRQHandler
                DCD     GPIO20_IRQHandler
                DCD     GPIO21_IRQHandler
                DCD     GPIO22_IRQHandler
                DCD     GPIO23_IRQHandler
                DCD     GPIO24_IRQHandler
                DCD     GPIO25_IRQHandler
                DCD     GPIO26_IRQHandler
                DCD     GPIO27_IRQHandler
                DCD     GPIO28_IRQHandler
                DCD     GPIO29_IRQHandler
                DCD     GPIO30_IRQHandler
                DCD     GPIO31_IRQHandler

__Vectors_End

__Vectors_Size 	EQU 	__Vectors_End - __Vectors

;===============================================================================
; Reset Handler
;
                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
 ;               IMPORT  low_level_init
                IMPORT  __main
                
                ;---------------------------------------------------------------
                ; Initialize stack RAM content to initialize the error detection
                ; and correction (EDAC). This is done if EDAC is enabled for the
                ; eSRAM blocks or the ECC/SECDED is enabled for the MDDR.
                ; Register R11 is used to keep track of the RAM intialization
                ; decision outcome for later use for heap RAM initialization at
                ; the end of the startup code.
                ; Please note that the stack has to be located in eSRAM at this
                ; point and cannot be located in MDDR since MDDR is not available
                ; at this point.
                ; The bits of the content of register R11 have the foolwing
                ; meaning:
                ;  reg11[0]: eSRAM EDAC enabled
                ;  reg11[1]: MDDR ECC/SECDED enabled
                ;
                MOV R11, #0
				LDR R0, SF2_MDDR_MODE_CR
                LDR R0, [R0]
                LDR R1, SF2_EDAC_CR
                LDR R1, [R1]
                AND R1, R1, #3
                AND R0, R0, #0x1C
                CMP R0, #0x14
                BNE check_esram_edac
                ORR R11, R11, #2
check_esram_edac
                CMP R1, #0
                BEQ check_stack_init
                ORR R11, R11, #1
check_stack_init
                CMP R11, #0
                BEQ call_system_init
clear_stack
                LDR R0, =stack_start
                LDR R1, =stack_end
                LDR R2, RAM_INIT_PATTERN
                BL  fill_memory                       ; fill_memory takes r0 - r2 as arguments uses r4, r5, r6, r7, r8, r9, and does not preserve contents */
        
                ;---------------------------------------------------------------
                ; Call SystemInit() to perform Libero specified configuration.
                ;
call_system_init
                LDR     R0, =SystemInit
                BLX     R0
   ;             LDR     R0, =low_level_init
   ;             BLX     R0
                
                ;---------------------------------------------------------------
                ; Modify MDDR configuration if ECC/SECDED is enabled for MDDR.
                ; Enable write combining on MDDR bridge, disable non-bufferable
                ; regions.
                ;
adjust_mddr_cfg
                AND R10, R11, #0x2
                CMP R10, #0
                BEQ branch_to_main
                LDR R0, SF2_DDRB_NB_SIZE
                LDR R1, SF2_DDRB_CR
                LDR R2, [R0]
                LDR R3, [R1]
                push {R0, R1, R2, R3}
                MOV R2, #0
                MOV R3, #0xFF
                STR R2, [R0]
                STR R3, [R1]

                ; --------------------------------------------------------------
                ; Initialize heap RAM content to initialize the error detection
                ; and correction (EDAC). We use the decision made earlier in the
                ; startup code of whether or not the stack RAM should be
                ; initialized. This decision is held in register R11. A non-zero
                ; value indicates that the RAM content should be initialized.
                ;
clear_heap
                CMP R11, #0
                BEQ branch_to_main
                LDR R0, =__heap_base
                LDR R1, =__heap_limit
                LDR R2, HEAP_INIT_PATTERN
                BL  fill_memory                       ; fill_memory takes r0 - r2 as arguments uses r4, r5, r6, r7, r8, r9, and does not preserve contents */
                
                ;---------------------------------------------------------------
                ; Branch to __main
                ;
branch_to_main
                LDR     R0, =__main
                BX      R0
                ENDP
					
SF2_EDAC_CR         DCD     0x40038038
SF2_DDRB_NB_SIZE    DCD     0x40038030
SF2_DDRB_CR         DCD     0x40038034
SF2_MDDR_MODE_CR    DCD     0x40020818
RAM_INIT_PATTERN    DCD     0x00000000
HEAP_INIT_PATTERN   DCD     0x00000000
                
;------------------------------------------------------------------------------
; * fill_memory.
; * @brief Fills memory with Pattern contained in r2
; * This routine uses the stmne instruction to copy 4 words at a time which is very efficient
; * The instruction can only write to word aligned memory, hence the code at the start and end of this routine
; * to handle possible unaligned bytes at start and end.
; *
; * @param param1 r0: start address
; * @param param2 r1: end address
; * @param param3 r2: FILL PATTETN
; *
; * @note note: Most efficient if memory aligned. Linker ALIGN(4) command
; * should be used as per example linker scripts
; * Stack is not used in this routine
; * register contents r4, r5, r6, r7, r8, r9, will are used and will be returned undefined 
; * @return none - Used Registers are not preserved
; */

fill_memory	PROC
     ;push {r4, r5, r6, r7, r8, r9, lr}	 We will not use stack as may be not available */
    cmp r0, r1
    beq fill_memory_exit         ; Exit early if source and destination the same */
 ; copy non-aligned bytes at the start */
    and.w  r6, r0, #3			 ; see if non-alaigned bytes at the start 	*/
    cmp r6, #0
    beq fill_memory_end_start    ; no spare bytes at start, continue 	*/
    mov    r5, #4
    sub.w  r4, r5, r6			 ; now have number of non-aligned bytes in r4 */
    mov  r7, #8
    mul  r8, r7, r6				 ; calculate number of shifts required to initalise pattern for non-aligned bytes */
    mov  r9, r2					 ; copy pattern */
    ror  r9, r9, r8              ; Rotate right to keep pattern consistent */
fill_memory_spare_bytes_start   ; From above, R0 contains source address, R1 contains destination address */
    cmp r4, #0					 ; no spare bytes at end- end now 	*/
    beq fill_memory_end_start
    strb r9, [r0]				 ; fill byte */
    ror.w  r9, r9, r7            ; Rotate right by one byte for the next time, to keep pattern consistent */
    add r0, r0, #1				 ; add one to address */
    subs r4, r4, #1				 ; subtract one from byte count 1	*/
    b fill_memory_spare_bytes_start
fill_memory_end_start
    mov  r6, #0
    mov  r7, r1					  ; save end address */
    subs r1, r1, r0               ; Calculate number of bytes to fill */
    mov  r8,r1                    ; Save copy of byte count */
    asrs r1,r1, #4                ; Div by 16 to get number of chunks to move */
    mov  r9, r2					  ; copy pattern */
    mov  r4, r2					  ; copy pattern */
    mov  r5, r2					  ; copy pattern */
    cmp r1, r6					  ; compare to see if all chunks copied */
    beq fill_memory_spare_bytes_end
fill_memory_loop
    it ne
    stmne r0!, {r2, r4, r5, r9}   ; copy pattern- note: stmne instruction must me word aligned (address in r0) */
    add.w r6, r6, #1			  ; use Thumb2- make sure condition code reg. not updated */
    cmp r1, r6					  ; compare to see if all chunks copied */
    bne fill_memory_loop
fill_memory_spare_bytes_end	  	; copy spare bytes at the end if any */
    and.w r8, r8, #15			; get spare bytes  --check can you do an ands? 	*/
fill_memory_spare_end_loop       ; From above, R0 contains source address, R1 contains destination address */
    cmp r8, #0					  ; no spare bytes at end- end now 	*/
    beq fill_memory_exit
    strb r2, [r0]
    ror.w  r2, r2, #8             ; Rotate right by one byte for the next time, to keep pattern consistent */
    add r0, r0, #1				  ; add one to address */
    subs r8, r8, #1				  ; subtract one from byte count 1	*/
    b fill_memory_spare_end_loop
fill_memory_exit
    bx	lr						  ; We will not use pop as stack may be not available */
    ENDP



;===============================================================================
; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WdogWakeup_IRQHandler           [WEAK]
                EXPORT  RTC_Wakeup_IRQHandler           [WEAK]
                EXPORT  SPI0_IRQHandler                 [WEAK]
                EXPORT  SPI1_IRQHandler                 [WEAK]
                EXPORT  I2C0_IRQHandler                 [WEAK]
                EXPORT  I2C0_SMBAlert_IRQHandler        [WEAK]
                EXPORT  I2C0_SMBus_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler                 [WEAK]
                EXPORT  I2C1_SMBAlert_IRQHandler        [WEAK]
                EXPORT  I2C1_SMBus_IRQHandler           [WEAK]
                EXPORT  UART0_IRQHandler                [WEAK]
                EXPORT  UART1_IRQHandler                [WEAK]
                EXPORT  EthernetMAC_IRQHandler          [WEAK]
                EXPORT  DMA_IRQHandler                  [WEAK]
                EXPORT  Timer1_IRQHandler               [WEAK]
                EXPORT  Timer2_IRQHandler               [WEAK]
                EXPORT  CAN_IRQHandler                  [WEAK]
                EXPORT  ENVM0_IRQHandler                [WEAK]
                EXPORT  ENVM1_IRQHandler                [WEAK]
                EXPORT  ComBlk_IRQHandler               [WEAK]
                EXPORT  USB_IRQHandler                  [WEAK]
                EXPORT  USB_DMA_IRQHandler              [WEAK]
                EXPORT  PLL_Lock_IRQHandler             [WEAK]
                EXPORT  PLL_LockLost_IRQHandler         [WEAK]
                EXPORT  CommSwitchError_IRQHandler      [WEAK]
                EXPORT  CacheError_IRQHandler           [WEAK]
                EXPORT  DDR_IRQHandler                  [WEAK]
                EXPORT  HPDMA_Complete_IRQHandler       [WEAK]
                EXPORT  HPDMA_Error_IRQHandler          [WEAK]
                EXPORT  ECC_Error_IRQHandler            [WEAK]
                EXPORT  MDDR_IOCalib_IRQHandler         [WEAK]
                EXPORT  FAB_PLL_Lock_IRQHandler         [WEAK]
                EXPORT  FAB_PLL_LockLost_IRQHandler     [WEAK]
                EXPORT  FIC64_IRQHandler                [WEAK]
                EXPORT  FabricIrq0_IRQHandler           [WEAK]
                EXPORT  FabricIrq1_IRQHandler           [WEAK]
                EXPORT  FabricIrq2_IRQHandler           [WEAK]
                EXPORT  FabricIrq3_IRQHandler           [WEAK]
                EXPORT  FabricIrq4_IRQHandler           [WEAK]
                EXPORT  FabricIrq5_IRQHandler           [WEAK]
                EXPORT  FabricIrq6_IRQHandler           [WEAK]
                EXPORT  FabricIrq7_IRQHandler           [WEAK]
                EXPORT  FabricIrq8_IRQHandler           [WEAK]
                EXPORT  FabricIrq9_IRQHandler           [WEAK]
                EXPORT  FabricIrq10_IRQHandler          [WEAK]
                EXPORT  FabricIrq11_IRQHandler          [WEAK]
                EXPORT  FabricIrq12_IRQHandler          [WEAK]
                EXPORT  FabricIrq13_IRQHandler          [WEAK]
                EXPORT  FabricIrq14_IRQHandler          [WEAK]
                EXPORT  FabricIrq15_IRQHandler          [WEAK]                
                EXPORT  GPIO0_IRQHandler                [WEAK]
                EXPORT  GPIO1_IRQHandler                [WEAK]
                EXPORT  GPIO2_IRQHandler                [WEAK]
                EXPORT  GPIO3_IRQHandler                [WEAK]
                EXPORT  GPIO4_IRQHandler                [WEAK]
                EXPORT  GPIO5_IRQHandler                [WEAK]
                EXPORT  GPIO6_IRQHandler                [WEAK]
                EXPORT  GPIO7_IRQHandler                [WEAK]
                EXPORT  GPIO8_IRQHandler                [WEAK]
                EXPORT  GPIO9_IRQHandler                [WEAK]
                EXPORT  GPIO10_IRQHandler               [WEAK]
                EXPORT  GPIO11_IRQHandler               [WEAK]
                EXPORT  GPIO12_IRQHandler               [WEAK]
                EXPORT  GPIO13_IRQHandler               [WEAK]
                EXPORT  GPIO14_IRQHandler               [WEAK]
                EXPORT  GPIO15_IRQHandler               [WEAK]
                EXPORT  GPIO16_IRQHandler               [WEAK]
                EXPORT  GPIO17_IRQHandler               [WEAK]
                EXPORT  GPIO18_IRQHandler               [WEAK]
                EXPORT  GPIO19_IRQHandler               [WEAK]
                EXPORT  GPIO20_IRQHandler               [WEAK]
                EXPORT  GPIO21_IRQHandler               [WEAK]
                EXPORT  GPIO22_IRQHandler               [WEAK]
                EXPORT  GPIO23_IRQHandler               [WEAK]
                EXPORT  GPIO24_IRQHandler               [WEAK]
                EXPORT  GPIO25_IRQHandler               [WEAK]
                EXPORT  GPIO26_IRQHandler               [WEAK]
                EXPORT  GPIO27_IRQHandler               [WEAK]
                EXPORT  GPIO28_IRQHandler               [WEAK]
                EXPORT  GPIO29_IRQHandler               [WEAK]
                EXPORT  GPIO30_IRQHandler               [WEAK]
                EXPORT  GPIO31_IRQHandler               [WEAK]


WdogWakeup_IRQHandler
RTC_Wakeup_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2C0_IRQHandler
I2C0_SMBAlert_IRQHandler
I2C0_SMBus_IRQHandler
I2C1_IRQHandler
I2C1_SMBAlert_IRQHandler
I2C1_SMBus_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
EthernetMAC_IRQHandler
DMA_IRQHandler
Timer1_IRQHandler
Timer2_IRQHandler
CAN_IRQHandler
ENVM0_IRQHandler
ENVM1_IRQHandler
ComBlk_IRQHandler
USB_IRQHandler
USB_DMA_IRQHandler
PLL_Lock_IRQHandler
PLL_LockLost_IRQHandler
CommSwitchError_IRQHandler
CacheError_IRQHandler
DDR_IRQHandler
HPDMA_Complete_IRQHandler
HPDMA_Error_IRQHandler
ECC_Error_IRQHandler
MDDR_IOCalib_IRQHandler
FAB_PLL_Lock_IRQHandler
FAB_PLL_LockLost_IRQHandler
FIC64_IRQHandler
FabricIrq0_IRQHandler
FabricIrq1_IRQHandler
FabricIrq2_IRQHandler
FabricIrq3_IRQHandler
FabricIrq4_IRQHandler
FabricIrq5_IRQHandler
FabricIrq6_IRQHandler
FabricIrq7_IRQHandler
FabricIrq8_IRQHandler 
FabricIrq9_IRQHandler 
FabricIrq10_IRQHandler
FabricIrq11_IRQHandler
FabricIrq12_IRQHandler
FabricIrq13_IRQHandler
FabricIrq14_IRQHandler
FabricIrq15_IRQHandler
GPIO0_IRQHandler
GPIO1_IRQHandler
GPIO2_IRQHandler
GPIO3_IRQHandler
GPIO4_IRQHandler
GPIO5_IRQHandler
GPIO6_IRQHandler
GPIO7_IRQHandler
GPIO8_IRQHandler
GPIO9_IRQHandler
GPIO10_IRQHandler
GPIO11_IRQHandler
GPIO12_IRQHandler
GPIO13_IRQHandler
GPIO14_IRQHandler
GPIO15_IRQHandler
GPIO16_IRQHandler
GPIO17_IRQHandler
GPIO18_IRQHandler
GPIO19_IRQHandler
GPIO20_IRQHandler
GPIO21_IRQHandler
GPIO22_IRQHandler
GPIO23_IRQHandler
GPIO24_IRQHandler
GPIO25_IRQHandler
GPIO26_IRQHandler
GPIO27_IRQHandler
GPIO28_IRQHandler
GPIO29_IRQHandler
GPIO30_IRQHandler
GPIO31_IRQHandler
                B       .

                ENDP

mscc_post_hw_cfg_init PROC
                EXPORT  mscc_post_hw_cfg_init           [WEAK]
                BX LR
                ENDP
                
                ALIGN


;===============================================================================
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
