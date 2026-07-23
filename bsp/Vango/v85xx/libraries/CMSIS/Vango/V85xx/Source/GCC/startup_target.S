;/**
;* @file    startup_target.s
;* @author  Application Team
;* @version V1.1.0
;* @date    2019-10-28
;* @brief   Target Devices vector table.
;******************************************************************************/

  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.equ __CHIPINITIAL, 1

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

/*************************************************************************
* Chip init.
*      1. Load flash configuration
*      2. Load ANA_REG(B/C/D/E) information
*      3. Load ANA_REG10 information

**************************************************************************/
.if (__CHIPINITIAL != 0)
  .section .chipinit_section.__CHIP_INIT
__CHIP_INIT:
CONFIG1_START:
        /*-------------------------------*/
        /* 1. Load flash configuration */
        /* Unlock flash */
        LDR     R0, =0x000FFFE0
        LDR     R1, =0x55AAAA55
        STR     R1, [R0]
        /* Load configure word 0 to 7
           Compare bit[7:0] */
        LDR     R0, =0x00080E00
        LDR     R1, =0x20
        LDR     R2, =0x000FFFE8
        LDR     R3, =0x000FFFF0
        LDR     R4, =0x0
        LDR     R7, =0x0FF
FLASH_CONF_START_1:
        LDR     R5, [R0]
        STR     R4, [R2]
        STR     R5, [R3]
        LDR     R6, [R3]
        ANDS    R5, R7
        ANDS    R6, R7
        CMP     R5, R6
        BNE     FLASH_CONF_AGAIN_1
        ADDS    R4, #4
        ADDS    R0, #4
        CMP     R1, R4
        BEQ     FLASH_CONF_END_1
        B       FLASH_CONF_START_1
FLASH_CONF_AGAIN_1:
        LDR     R5, [R0]
        STR     R4, [R2]
        STR     R5, [R3]
        LDR     R6, [R3]
        ANDS    R5, R7
        ANDS    R6, R7
        CMP     R5, R6
FLASH_CONF_WHILELOOP_1:
        BNE     FLASH_CONF_WHILELOOP_1
        ADDS    R4, #4
        ADDS    R0, #4
        CMP     R1, R4
        BEQ     FLASH_CONF_END_1
        B       FLASH_CONF_START_1
FLASH_CONF_END_1:
        /* Load configure word 8 to 11
           Compare bit 31,24,23:16,8,7:0 */
        LDR     R1, =0x30
        LDR     R7, =0x81FF81FF
FLASH_CONF_START_2:
        LDR     R5, [R0]
        STR     R4, [R2]
        STR     R5, [R3]
        LDR     R6, [R3]
        ANDS    R5, R7
        ANDS    R6, R7
        CMP     R5, R6
        BNE     FLASH_CONF_AGAIN_1
        ADDS    R4, #4
        ADDS    R0, #4
        CMP     R1, R4
        BEQ     FLASH_CONF_END_2
        B       FLASH_CONF_START_2
FLASH_CONF_AGAIN_2:
        LDR     R5, [R0]
        STR     R4, [R2]
        STR     R5, [R3]
        LDR     R6, [R3]
        ANDS    R5, R7
        ANDS    R6, R7
        CMP     R5, R6
FLASH_CONF_WHILELOOP_2:
        BNE     FLASH_CONF_WHILELOOP_2
        ADDS    R4, #4
        ADDS    R0, #4
        CMP     R1, R4
        BEQ     FLASH_CONF_END_2
        B       FLASH_CONF_START_2
FLASH_CONF_END_2:
        /* Lock flash */
        LDR     R0, =0x000FFFE0
        LDR     R1, =0x0
        STR     R1, [R0]
        /*-------------------------------*/
        /* 2. Load ANA_REG(B/C/D/E) information */
CONFIG2_START:
        LDR     R4, =0x4001422C
        LDR     R5, =0x40014230
        LDR     R6, =0x40014234
        LDR     R7, =0x40014238
        LDR     R0, =0x80DC0
        LDR     R0, [R0]
        LDR     R1, =0x80DC4
        LDR     R1, [R1]
        ADDS    R2, R0, R1
        ADDS    R2, #0x0FFFFFFFF
        MVNS    R2, R2
        LDR     R3, =0x80DCC
        LDR     R3, [R3]
        CMP     R3, R2
        BEQ     ANADAT_CHECKSUM1_OK
        B       ANADAT_CHECKSUM1_ERR
ANADAT_CHECKSUM1_OK:
        /* ANA_REGB */
        LDR     R1, =0x0FF
        ANDS    R1, R0
        STR     R1, [R4]
        /* ANA_REGC */
        LDR     R1, =0x0FF00
        ANDS    R1, R0
        LSRS    R1, R1, #8
        STR     R1, [R5]
        /* ANA_REGD */
        LDR     R1, =0x0FF0000
        ANDS    R1, R0
        LSRS    R1, R1, #16
        STR     R1, [R6]
        /* ANA_REGE */
        LDR     R1, =0x0FF000000
        ANDS    R1, R0
        LSRS    R1, R1, #24
        STR     R1, [R7]
        B       CONFIG3_START
ANADAT_CHECKSUM1_ERR:
        LDR     R0, =0x80DD0
        LDR     R0, [R0]
        LDR     R1, =0x80DD4
        LDR     R1, [R1]
        ADDS    R2, R0, R1
        ADDS    R2, #0x0FFFFFFFF
        MVNS    R2, R2
        LDR     R3, =0x80DDC
        LDR     R3, [R3]
        CMP     R3, R2
        BEQ     ANADAT_CHECKSUM2_OK
        B       ANADAT_CHECKSUM2_ERR
ANADAT_CHECKSUM2_OK:
        /* ANA_REGB */
        LDR     R1, =0x0FF
        ANDS    R1, R0
        STR     R1, [R4]
        /* ANA_REGC */
        LDR     R1, =0x0FF00
        ANDS    R1, R0
        LSRS    R1, R1, #8
        STR     R1, [R5]
        /* ANA_REGD */
        LDR     R1, =0x0FF0000
        ANDS    R1, R0
        LSRS    R1, R1, #16
        STR     R1, [R6]
        /* ANA_REGE */
        LDR     R1, =0x0FF000000
        ANDS    R1, R0
        LSRS    R1, R1, #24
        STR     R1, [R7]
        B       CONFIG3_START
ANADAT_CHECKSUM2_ERR:
        B       ANADAT_CHECKSUM2_ERR
        /*-------------------------------*/
        /* 3. Load ANA_REG10 information */
CONFIG3_START:
        LDR     R7, =0x40014240
        LDR     R0, =0x80DE0
        LDR     R0, [R0]
        LDR     R1, =0x80DE4
        LDR     R1, [R1]
        MVNS    R1, R1
        CMP     R1, R0
        BEQ     ANADAT10_CHECKSUM1_OK
        B       ANADAT10_CHECKSUM1_ERR
ANADAT10_CHECKSUM1_OK:
        /* ANA_REG10 */
        LDR     R1, =0x0FF
        ANDS    R1, R0
        STR     R1, [R7]
        BX      LR
ANADAT10_CHECKSUM1_ERR:
        LDR     R0, =0x80DE8
        LDR     R0, [R0]
        LDR     R1, =0x80DEC
        LDR     R1, [R1]
        MVNS    R1, R1
        CMP     R1, R0
        BEQ     ANADAT10_CHECKSUM2_OK
        B       ANADAT10_CHECKSUM2_ERR
ANADAT10_CHECKSUM2_OK:
        /* ANA_REG10 */
        LDR     R1, =0x0FF
        ANDS    R1, R0
        STR     R1, [R7]
        BX      LR
ANADAT10_CHECKSUM2_ERR:
        B       ANADAT10_CHECKSUM2_ERR
.size __CHIP_INIT, .-__CHIP_INIT
.endif


.if (__CHIPINITIAL != 0)
  .global __CHIP_INIT
  .section .chipinit_section.Reset_Handler
.else
  .section .text.Reset_Handler
.endif
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:

.if (__CHIPINITIAL != 0)
/* Chip Initiliazation */  
  bl    __CHIP_INIT
/* System Initiliazation */
  bl SystemInit
.endif

/* set stack pointer */
  ldr   r0, =_estack
  mov   sp, r0

/* Copy the data segment initializers from flash to SRAM */
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs r3, #0
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever

.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler

  /* External Interrupts */
  .word  PMU_IRQHandler                    /*  0: PMU       */
  .word  RTC_IRQHandler                    /*  1: RTC       */
  .word  U32K0_IRQHandler                  /*  2: U32K0     */
  .word  U32K1_IRQHandler                  /*  3: U32K1     */
  .word  I2C_IRQHandler                    /*  4: I2C       */
  .word  SPI1_IRQHandler                   /*  5: SPI1      */
  .word  UART0_IRQHandler                  /*  6: UART0     */
  .word  UART1_IRQHandler                  /*  7: UART1     */
  .word  UART2_IRQHandler                  /*  8: UART2     */
  .word  UART3_IRQHandler                  /*  9: UART3     */
  .word  UART4_IRQHandler                  /* 10: UART4     */
  .word  UART5_IRQHandler                  /* 11: UART5     */
  .word  ISO78160_IRQHandler               /* 12: ISO78160  */
  .word  ISO78161_IRQHandler               /* 13: ISO78161  */
  .word  TMR0_IRQHandler                   /* 14: TMR0      */
  .word  TMR1_IRQHandler                   /* 15: TMR1      */
  .word  TMR2_IRQHandler                   /* 16: TMR2      */
  .word  TMR3_IRQHandler                   /* 17: TMR3      */
  .word  PWM0_IRQHandler                   /* 18: PWM0      */
  .word  PWM1_IRQHandler                   /* 19: PWM1      */
  .word  PWM2_IRQHandler                   /* 20: PWM2      */
  .word  PWM3_IRQHandler                   /* 21: PWM3      */
  .word  DMA_IRQHandler                    /* 22: DMA       */
  .word  FLASH_IRQHandler                  /* 23: FLASH     */
  .word  ANA_IRQHandler                    /* 24: ANA       */
  .word  0                                 /* 25: Reserved  */
  .word  0                                 /* 26: Reserved  */
  .word  SPI2_IRQHandler                   /* 27: SPI2      */
  .word  SPI3_IRQHandler                   /* 28: SPI3      */
  .word  0                                 /* 29: Reserved  */
  .word  0                                 /* 30: Reserved  */
  .word  0                                 /* 31: Reserved  */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      PMU_IRQHandler
  .thumb_set PMU_IRQHandler,Default_Handler

  .weak      RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak      U32K0_IRQHandler
  .thumb_set U32K0_IRQHandler,Default_Handler

  .weak      U32K1_IRQHandler
  .thumb_set U32K1_IRQHandler,Default_Handler

  .weak      I2C_IRQHandler
  .thumb_set I2C_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak      UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Default_Handler

  .weak      UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak      UART2_IRQHandler
  .thumb_set UART2_IRQHandler,Default_Handler

  .weak      UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak      UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Default_Handler

  .weak      UART5_IRQHandler
  .thumb_set UART5_IRQHandler,Default_Handler

  .weak      ISO78160_IRQHandler
  .thumb_set ISO78160_IRQHandler,Default_Handler

  .weak      ISO78161_IRQHandler
  .thumb_set ISO78161_IRQHandler,Default_Handler

  .weak      TMR0_IRQHandler
  .thumb_set TMR0_IRQHandler,Default_Handler

  .weak      TMR1_IRQHandler
  .thumb_set TMR1_IRQHandler,Default_Handler

  .weak      TMR2_IRQHandler
  .thumb_set TMR2_IRQHandler,Default_Handler

  .weak      TMR3_IRQHandler
  .thumb_set TMR3_IRQHandler,Default_Handler

  .weak      PWM0_IRQHandler
  .thumb_set PWM0_IRQHandler,Default_Handler

  .weak      PWM1_IRQHandler
  .thumb_set PWM1_IRQHandler,Default_Handler

  .weak      PWM2_IRQHandler
  .thumb_set PWM2_IRQHandler,Default_Handler

  .weak      PWM3_IRQHandler
  .thumb_set PWM3_IRQHandler,Default_Handler

  .weak      DMA_IRQHandler
  .thumb_set DMA_IRQHandler,Default_Handler

  .weak      FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler

  .weak      ANA_IRQHandler
  .thumb_set ANA_IRQHandler,Default_Handler

  .weak      SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak      SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Default_Handler
