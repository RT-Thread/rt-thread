;/****************************************************************
;KPIT Cummins Infosystems Ltd, Pune, India. 17-June-2005.
;
;This program is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
;
;*****************************************************************/

; Fixed Vector Table

	.section	.vects,"a",@progbits
	.type	_HardwareVectors, @object
	.size	_HardwareVectors, 36

_HardwareVectors:
	.long	0	;(Undefined Instruction) Interrupt on UND instruction 
	.long	0	;(Overflow) Interrupt on INTO instruction 
	.long	0	;(BRK) If the vector contains FF16, program execution starts from the address shown by the vector in the variable vector table
	.long	0	;(Address match)There is an address-matching interrupt enable bit
	.long	0	;Single step (debugger)
	.long	0	;Watchdog timer
	.long	0	;DBC (debugger)
	.long	0	;(NMI)External interrupt by input to NMI pin
	.long	(_start + 0xFF000000)	; Reset


; Variable Vector Table

;	.global	_rt_hw_uart0_receive_handler
;	.global	_rt_hw_timer_handler

	.global	_VariableVectors
	.section	.var_vects,"a",@progbits
	.type	_VariableVectors, @object
	.size	_VariableVectors, 128
_VariableVectors:
    .long    _os_context_switch           ; Vector  0: BRK
    .long    0                           ; Vector  1: Reserved
    .long    0                           ; Vector  2: Reserved
    .long    0                           ; Vector  3: Reserved
    .long    0                           ; Vector  4: INT3
    .long    0                           ; Vector  5: Timer B5
    .long    0                           ; Vector  6: Timer B4, UART1 Bus Collision Detect
    .long    0                           ; Vector  7: Timer B3, UART0 Bus Collision Detect
    .long    0                           ; Vector  8: SI/O4, INT5
    .long    0                           ; Vector  9: SI/O3, INT4
    .long    0                           ; Vector 10: UART2 Bus Collision Detect
    .long    0                           ; Vector 11: DMA0
    .long    0                           ; Vector 12: DMA1
    .long    0                           ; Vector 13: Key Input Interrupt
    .long    0                           ; Vector 14: A/D
    .long    0                           ; Vector 15: UART2 Transmit, NACK2
    .long    0                           ; Vector 16: UART2 Receive,   ACK2
    .long    0                           ; Vector 17: UART0 Transmit, NACK0
    .long    _rt_hw_uart0_receive_handler ; Vector 18: UART0 Receive,   ACK0
    .long    0                           ; Vector 19: UART1 Transmit, NACK1
    .long    0                           ; Vector 20: UART1 Receive,   ACK1
    .long    0                           ; Vector 21: Timer A0
    .long    0                           ; Vector 22: Timer A1
    .long    0                           ; Vector 23: Timer A2
    .long    0                           ; Vector 24: Timer A3
    .long    0                           ; Vector 25: Timer A4
    .long    _rt_hw_timer_handler         ; Vector 26: Timer B0
    .long    0                           ; Vector 27: Timer B1
    .long    0                           ; Vector 28: Timer B2
    .long    0                           ; Vector 29:
    .long    0                           ; Vector 30:
    .long    0                           ; Vector 31:

	.end 
