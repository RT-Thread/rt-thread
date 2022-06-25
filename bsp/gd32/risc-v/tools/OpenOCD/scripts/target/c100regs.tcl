# Note that I basically converted
# u-boot/include/asm-arm/arch/comcerto_100.h
# defines

# this is a work-around for 'global' not working under Linux
# access registers by calling this routine.
# For example:
# set EX_CS_TMG1_REG [regs EX_CS0_TMG1_REG]
proc regs {reg} {
    return [dict get [regsC100] $reg ]
}

proc showreg {reg} {
    echo [format "0x%x" [dict get [regsC100] $reg ]]
}

proc regsC100 {} {
#/* memcore */
#/* device memory base addresses */
#// device memory sizes
#/* ARAM SIZE=64K */
dict set regsC100 ARAM_SIZE		0x00010000
dict set regsC100 ARAM_BASEADDR	0x0A000000

#/* Hardware Interface Units */
dict set regsC100 APB_BASEADDR	0x10000000
#/* APB_SIZE=16M address range */
dict set regsC100 APB_SIZE		0x01000000

dict set regsC100 EXP_CS0_BASEADDR       0x20000000
dict set regsC100 EXP_CS1_BASEADDR       0x24000000
dict set regsC100 EXP_CS2_BASEADDR       0x28000000
dict set regsC100 EXP_CS3_BASEADDR       0x2C000000
dict set regsC100 EXP_CS4_BASEADDR       0x30000000

dict set regsC100 DDR_BASEADDR           0x80000000

dict set regsC100 TDM_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x000000]
dict set regsC100 PHI_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x010000]
dict set regsC100 TDMA_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x020000]
dict set regsC100 ASA_DDR_BASEADDR	        [expr [dict get $regsC100 APB_BASEADDR ] + 0x040000]
dict set regsC100 ASA_ARAM_BASEADDR	        [expr [dict get $regsC100 APB_BASEADDR ] + 0x048000]
dict set regsC100 TIMER_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x050000]
dict set regsC100 ASD_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x060000]
dict set regsC100 GPIO_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x070000]
dict set regsC100 UART0_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x090000]
dict set regsC100 UART1_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x094000]
dict set regsC100 SPI_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x098000]
dict set regsC100 I2C_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x09C000]
dict set regsC100 INTC_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x0A0000]
dict set regsC100 CLKCORE_BASEADDR	        [expr [dict get $regsC100 APB_BASEADDR ] + 0x0B0000]
dict set regsC100 PUI_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x0B0000]
dict set regsC100 GEMAC_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x0D0000]
dict set regsC100 IDMA_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x0E0000]
dict set regsC100 MEMCORE_BASEADDR	        [expr [dict get $regsC100 APB_BASEADDR ] + 0x0F0000]
dict set regsC100 ASA_EBUS_BASEADDR	        [expr [dict get $regsC100 APB_BASEADDR ] + 0x100000]
dict set regsC100 ASA_AAB_BASEADDR	        [expr [dict get $regsC100 APB_BASEADDR ] + 0x108000]
dict set regsC100 GEMAC1_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x190000]
dict set regsC100 EBUS_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x1A0000]
dict set regsC100 MDMA_BASEADDR		[expr [dict get $regsC100 APB_BASEADDR ] + 0x1E0000]


#////////////////////////////////////////////////////////////
#//	AHB block											    //
#////////////////////////////////////////////////////////////
dict set regsC100 ASA_ARAM_PRI_REG	[expr [dict get $regsC100 ASA_ARAM_BASEADDR ] + 0x00]
dict set regsC100 ASA_ARAM_TC_REG	[expr [dict get $regsC100 ASA_ARAM_BASEADDR ] + 0x04]
dict set regsC100 ASA_ARAM_TC_CR_REG	[expr [dict get $regsC100 ASA_ARAM_BASEADDR ] + 0x08]
dict set regsC100 ASA_ARAM_STAT_REG	[expr [dict get $regsC100 ASA_ARAM_BASEADDR ] + 0x0C]

dict set regsC100 ASA_EBUS_PRI_REG	[expr [dict get $regsC100 ASA_EBUS_BASEADDR ] + 0x00]
dict set regsC100 ASA_EBUS_TC_REG	[expr [dict get $regsC100 ASA_EBUS_BASEADDR ] + 0x04]
dict set regsC100 ASA_EBUS_TC_CR_REG	[expr [dict get $regsC100 ASA_EBUS_BASEADDR ] + 0x08]
dict set regsC100 ASA_EBUS_STAT_REG	[expr [dict get $regsC100 ASA_EBUS_BASEADDR ] + 0x0C]

dict set regsC100 IDMA_MASTER		0
dict set regsC100 TDMA_MASTER		1
dict set regsC100 USBIPSEC_MASTER	2
dict set regsC100 ARM0_MASTER		3
dict set regsC100 ARM1_MASTER		4
dict set regsC100 MDMA_MASTER		5

#define IDMA_PRIORITY(level) (level)
#define TDM_PRIORITY(level) (level << 4)
#define USBIPSEC_PRIORITY(level) (level << 8)
#define ARM0_PRIORITY(level) (level << 12)
#define ARM1_PRIORITY(level) (level << 16)
#define MDMA_PRIORITY(level) (level << 20)

dict set regsC100 ASA_TC_REQIDMAEN	 [expr 1<<18]
dict set regsC100 ASA_TC_REQTDMEN	 [expr 1<<19]
dict set regsC100 ASA_TC_REQIPSECUSBEN [expr 1<<20]
dict set regsC100 ASA_TC_REQARM0EN	 [expr 1<<21]
dict set regsC100 ASA_TC_REQARM1EN	 [expr 1<<22]
dict set regsC100 ASA_TC_REQMDMAEN	 [expr 1<<23]

dict set regsC100 MEMORY_BASE_ADDR	0x80000000
dict set regsC100 MEMORY_MAX_ADDR	[expr [dict get $regsC100 ASD_BASEADDR ] + 0x10]
dict set regsC100 MEMORY_CR 		[expr [dict get $regsC100 ASD_BASEADDR ] + 0x14]
dict set regsC100 ROM_REMAP_EN	0x1

#define HAL_asb_priority(level) \
#*(volatile unsigned *)ASA_PRI_REG = level

#define HAL_aram_priority(level) \
#*(volatile unsigned *)ASA_ARAM_PRI_REG = level

#define HAL_aram_arbitration(arbitration_mask) \
#*(volatile unsigned *)ASA_ARAM_TC_CR_REG |= arbitration_mask

#define HAL_aram_defmaster(mask) \
#*(volatile unsigned *)ASA_ARAM_TC_CR_REG = (*(volatile unsigned *)ASA_TC_CR_REG & 0xFFFF) | (mask << 24)

#////////////////////////////////////////////////////////////
#// INTC block						  //
#////////////////////////////////////////////////////////////

dict set regsC100 INTC_ARM1_CONTROL_REG	[expr [dict get $regsC100 INTC_BASEADDR ] + 0x18]

#////////////////////////////////////////////////////////////
#// TIMER block						  //
#////////////////////////////////////////////////////////////

dict set regsC100 TIMER0_CNTR_REG	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x00]
dict set regsC100 TIMER0_CURR_COUNT	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x04]
dict set regsC100 TIMER1_CNTR_REG	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x08]
dict set regsC100 TIMER1_CURR_COUNT	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x0C]

dict set regsC100 TIMER2_CNTR_REG	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x18]
dict set regsC100 TIMER2_LBOUND_REG	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x10]
dict set regsC100 TIMER2_HBOUND_REG	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x14]
dict set regsC100 TIMER2_CURR_COUNT	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x1C]

dict set regsC100 TIMER3_LOBND	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x20]
dict set regsC100 TIMER3_HIBND	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x24]
dict set regsC100 TIMER3_CTRL		[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x28]
dict set regsC100 TIMER3_CURR_COUNT	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x2C]

dict set regsC100 TIMER_MASK		[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x40]
dict set regsC100 TIMER_STATUS	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x50]
dict set regsC100 TIMER_ACK		[expr [dict get $regsC100 TIMER_BASEADDR ] + 0x50]
dict set regsC100 TIMER_WDT_HIGH_BOUND [expr [dict get $regsC100 TIMER_BASEADDR ] + 0xD0]
dict set regsC100 TIMER_WDT_CONTROL	[expr [dict get $regsC100 TIMER_BASEADDR ] + 0xD4]
dict set regsC100 TIMER_WDT_CURRENT_COUNT [expr [dict get $regsC100 TIMER_BASEADDR ] + 0xD8]



#////////////////////////////////////////////////////////////
#//  EBUS block
#////////////////////////////////////////////////////////////

dict set regsC100 EX_SWRST_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x00]
dict set regsC100 EX_CSEN_REG		        [expr [dict get $regsC100 EBUS_BASEADDR ] + 0x04]
dict set regsC100 EX_CS0_SEG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x08]
dict set regsC100 EX_CS1_SEG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x0C]
dict set regsC100 EX_CS2_SEG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x10]
dict set regsC100 EX_CS3_SEG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x14]
dict set regsC100 EX_CS4_SEG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x18]
dict set regsC100 EX_CS0_CFG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x1C]
dict set regsC100 EX_CS1_CFG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x20]
dict set regsC100 EX_CS2_CFG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x24]
dict set regsC100 EX_CS3_CFG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x28]
dict set regsC100 EX_CS4_CFG_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x2C]
dict set regsC100 EX_CS0_TMG1_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x30]
dict set regsC100 EX_CS1_TMG1_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x34]
dict set regsC100 EX_CS2_TMG1_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x38]
dict set regsC100 EX_CS3_TMG1_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x3C]
dict set regsC100 EX_CS4_TMG1_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x40]
dict set regsC100 EX_CS0_TMG2_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x44]
dict set regsC100 EX_CS1_TMG2_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x48]
dict set regsC100 EX_CS2_TMG2_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x4C]
dict set regsC100 EX_CS3_TMG2_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x50]
dict set regsC100 EX_CS4_TMG2_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x54]
dict set regsC100 EX_CS0_TMG3_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x58]
dict set regsC100 EX_CS1_TMG3_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x5C]
dict set regsC100 EX_CS2_TMG3_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x60]
dict set regsC100 EX_CS3_TMG3_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x64]
dict set regsC100 EX_CS4_TMG3_REG		[expr [dict get $regsC100 EBUS_BASEADDR ] + 0x68]
dict set regsC100 EX_CLOCK_DIV_REG	        [expr [dict get $regsC100 EBUS_BASEADDR ] + 0x6C]

dict set regsC100 EX_MFSM_REG		[expr [dict get $regsC100 EBUS_BASEADDR] + 0x100]
dict set regsC100 EX_MFSM_REG		[expr [dict get $regsC100 EBUS_BASEADDR] + 0x100]
dict set regsC100 EX_CSFSM_REG		[expr [dict get $regsC100 EBUS_BASEADDR] + 0x104]
dict set regsC100 EX_WRFSM_REG		[expr [dict get $regsC100 EBUS_BASEADDR] + 0x108]
dict set regsC100 EX_RDFSM_REG		[expr [dict get $regsC100 EBUS_BASEADDR] + 0x10C]


dict set regsC100 EX_CLK_EN		0x00000001
dict set regsC100 EX_CSBOOT_EN	0x00000002
dict set regsC100 EX_CS0_EN		0x00000002
dict set regsC100 EX_CS1_EN		0x00000004
dict set regsC100 EX_CS2_EN		0x00000008
dict set regsC100 EX_CS3_EN		0x00000010
dict set regsC100 EX_CS4_EN		0x00000020

dict set regsC100 EX_MEM_BUS_8	0x00000000
dict set regsC100 EX_MEM_BUS_16       0x00000002
dict set regsC100 EX_MEM_BUS_32	0x00000004
dict set regsC100 EX_CS_HIGH		0x00000008
dict set regsC100 EX_WE_HIGH		0x00000010
dict set regsC100 EX_RE_HIGH		0x00000020
dict set regsC100 EX_ALE_MODE		0x00000040
dict set regsC100 EX_STRB_MODE	0x00000080
dict set regsC100 EX_DM_MODE		0x00000100
dict set regsC100 EX_NAND_MODE	0x00000200
dict set regsC100 EX_RDY_EN		0x00000400
dict set regsC100 EX_RDY_EDGE		0x00000800

#////////////////////////////////////////////////////////////
#//  GPIO block
#////////////////////////////////////////////////////////////

# GPIO outputs register
dict set regsC100 GPIO_OUTPUT_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x00]
# GPIO Output Enable register
dict set regsC100 GPIO_OE_REG		        [expr [dict get $regsC100 GPIO_BASEADDR ] + 0x04]
dict set regsC100 GPIO_HI_INT_ENABLE_REG	[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x08]
dict set regsC100 GPIO_LO_INT_ENABLE_REG	[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x0C]
# GPIO input register
dict set regsC100 GPIO_INPUT_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x10]
dict set regsC100 APB_ACCESS_WS_REG	        [expr [dict get $regsC100 GPIO_BASEADDR ] + 0x14]
dict set regsC100 MUX_CONF_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x18]
dict set regsC100 SYSCONF_REG		        [expr [dict get $regsC100 GPIO_BASEADDR ] + 0x1C]
dict set regsC100 GPIO_ARM_ID_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x30]
dict set regsC100 GPIO_BOOTSTRAP_REG	        [expr [dict get $regsC100 GPIO_BASEADDR ] + 0x40]
dict set regsC100 GPIO_LOCK_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x38]
dict set regsC100 GPIO_IOCTRL_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x44]
dict set regsC100 GPIO_DEVID_REG		[expr [dict get $regsC100 GPIO_BASEADDR ] + 0x50]

dict set regsC100 GPIO_IOCTRL_A15A16	0x00000001
dict set regsC100 GPIO_IOCTRL_A17A18	0x00000002
dict set regsC100 GPIO_IOCTRL_A19A21	0x00000004
dict set regsC100 GPIO_IOCTRL_TMREVT0	0x00000008
dict set regsC100 GPIO_IOCTRL_TMREVT1	0x00000010
dict set regsC100 GPIO_IOCTRL_GPBT3	0x00000020
dict set regsC100 GPIO_IOCTRL_I2C	0x00000040
dict set regsC100 GPIO_IOCTRL_UART0	0x00000080
dict set regsC100 GPIO_IOCTRL_UART1	0x00000100
dict set regsC100 GPIO_IOCTRL_SPI	0x00000200
dict set regsC100 GPIO_IOCTRL_HBMODE	0x00000400

dict set regsC100 GPIO_IOCTRL_VAL	0x55555555

dict set regsC100 GPIO_0			0x01
dict set regsC100 GPIO_1			0x02
dict set regsC100 GPIO_2			0x04
dict set regsC100 GPIO_3			0x08
dict set regsC100 GPIO_4			0x10
dict set regsC100 GPIO_5			0x20
dict set regsC100 GPIO_6			0x40
dict set regsC100 GPIO_7			0x80

dict set regsC100 GPIO_RISING_EDGE	1
dict set regsC100 GPIO_FALLING_EDGE	2
dict set regsC100 GPIO_BOTH_EDGES	3

#////////////////////////////////////////////////////////////
#// UART
#////////////////////////////////////////////////////////////

dict set regsC100 UART0_RBR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x00]
dict set regsC100 UART0_THR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x00]
dict set regsC100 UART0_DLL		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x00]
dict set regsC100 UART0_IER		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x04]
dict set regsC100 UART0_DLH		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x04]
dict set regsC100 UART0_IIR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x08]
dict set regsC100 UART0_FCR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x08]
dict set regsC100 UART0_LCR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x0C]
dict set regsC100 UART0_MCR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x10]
dict set regsC100 UART0_LSR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x14]
dict set regsC100 UART0_MSR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x18]
dict set regsC100 UART0_SCR		[expr [dict get $regsC100 UART0_BASEADDR ] + 0x1C]

dict set regsC100 UART1_RBR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x00]
dict set regsC100 UART1_THR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x00]
dict set regsC100 UART1_DLL		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x00]
dict set regsC100 UART1_IER		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x04]
dict set regsC100 UART1_DLH		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x04]
dict set regsC100 UART1_IIR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x08]
dict set regsC100 UART1_FCR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x08]
dict set regsC100 UART1_LCR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x0C]
dict set regsC100 UART1_MCR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x10]
dict set regsC100 UART1_LSR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x14]
dict set regsC100 UART1_MSR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x18]
dict set regsC100 UART1_SCR		[expr [dict get $regsC100 UART1_BASEADDR ] + 0x1C]

# /* default */
dict set regsC100 LCR_CHAR_LEN_5		0x00
dict set regsC100 LCR_CHAR_LEN_6		0x01
dict set regsC100 LCR_CHAR_LEN_7		0x02
dict set regsC100 LCR_CHAR_LEN_8		0x03
#/* One stop bit! - default */
dict set regsC100 LCR_ONE_STOP		0x00
#/* Two stop bit! */
dict set regsC100 LCR_TWO_STOP		0x04
#/* Parity Enable */
dict set regsC100 LCR_PEN			0x08
dict set regsC100 LCR_PARITY_NONE		0x00
#/* Even Parity Select */
dict set regsC100 LCR_EPS			0x10
#/* Enable Parity  Stuff */
dict set regsC100 LCR_PS			0x20
#/* Start Break */
dict set regsC100 LCR_SBRK		        0x40
#/* Parity Stuff Bit */
dict set regsC100 LCR_PSB			0x80
#/* UART 16550 Divisor Latch Assess */
dict set regsC100 LCR_DLAB		        0x80

#/* FIFO Error Status */
dict set regsC100 LSR_FIFOE		[expr 1 << 7]
#/* Transmitter Empty */
dict set regsC100 LSR_TEMT		[expr 1 << 6]
#/* Transmit Data Request */
dict set regsC100 LSR_TDRQ		[expr 1 << 5]
#/* Break Interrupt */
dict set regsC100 LSR_BI			[expr 1 << 4]
#/* Framing Error */
dict set regsC100 LSR_FE			[expr 1 << 3]
#/* Parity Error */
dict set regsC100 LSR_PE			[expr 1 << 2]
#/* Overrun Error */
dict set regsC100 LSR_OE			[expr 1 << 1]
#/* Data Ready */
dict set regsC100 LSR_DR			[expr 1 << 0]

#/* DMA Requests Enable */
dict set regsC100 IER_DMAE		        [expr 1 << 7]
#/* UART Unit Enable */
dict set regsC100 IER_UUE			[expr 1 << 6]
#/* NRZ coding Enable */
dict set regsC100 IER_NRZE		        [expr 1 << 5]
#/* Receiver Time Out Interrupt Enable */
dict set regsC100 IER_RTIOE		        [expr 1 << 4]
#/* Modem Interrupt Enable */
dict set regsC100 IER_MIE			[expr 1 << 3]
#/* Receiver Line Status Interrupt Enable */
dict set regsC100 IER_RLSE		        [expr 1 << 2]
#/* Transmit Data request Interrupt Enable */
dict set regsC100 IER_TIE			[expr 1 << 1]
#/* Receiver Data Available Interrupt Enable */
dict set regsC100 IER_RAVIE		        [expr 1 << 0]

#/* FIFO Mode Enable Status */
dict set regsC100 IIR_FIFOES1		        [expr 1 << 7]
#/* FIFO Mode Enable Status */
dict set regsC100 IIR_FIFOES0		        [expr 1 << 6]
#/* Time Out Detected */
dict set regsC100 IIR_TOD			[expr 1 << 3]
#/* Interrupt Source Encoded */
dict set regsC100 IIR_IID2		        [expr 1 << 2]
#/* Interrupt Source Encoded */
dict set regsC100 IIR_IID1		        [expr 1 << 1]
#/* Interrupt Pending (active low) */
dict set regsC100 IIR_IP			[expr 1 << 0]

#/* UART 16550 FIFO Control Register */
dict set regsC100 FCR_FIFOEN		0x01
dict set regsC100 FCR_RCVRRES		0x02
dict set regsC100 FCR_XMITRES		0x04

#/* Interrupt Enable Register */
#// UART 16550
#// Enable Received Data Available Interrupt
dict set regsC100 IER_RXTH		0x01
#// Enable Transmitter Empty Interrupt
dict set regsC100 IER_TXTH		0x02



#////////////////////////////////////////////////////////////
#// CLK  + RESET block
#////////////////////////////////////////////////////////////

dict set regsC100 CLKCORE_ARM_CLK_CNTRL	[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x00]
dict set regsC100 CLKCORE_AHB_CLK_CNTRL	[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x04]
dict set regsC100 CLKCORE_PLL_STATUS	        [expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x08]
dict set regsC100 CLKCORE_CLKDIV_CNTRL	[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x0C]
dict set regsC100 CLKCORE_TDM_CLK_CNTRL	[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x10]
dict set regsC100 CLKCORE_FSYNC_CNTRL	        [expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x14]
dict set regsC100 CLKCORE_CLK_PWR_DWN	        [expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x18]
dict set regsC100 CLKCORE_RNG_CNTRL	        [expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x1C]
dict set regsC100 CLKCORE_RNG_STATUS	        [expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x20]
dict set regsC100 CLKCORE_ARM_CLK_CNTRL2	[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x24]
dict set regsC100 CLKCORE_TDM_REF_DIV_RST	[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x40]

dict set regsC100 ARM_PLL_BY_CTRL	0x80000000
dict set regsC100 ARM_AHB_BYP		0x04000000
dict set regsC100 PLL_DISABLE		0x02000000
dict set regsC100 PLL_CLK_BYPASS	0x01000000

dict set regsC100 AHB_PLL_BY_CTRL	0x80000000
dict set regsC100 DIV_BYPASS		0x40000000
dict set regsC100 SYNC_MODE		0x20000000

dict set regsC100 EPHY_CLKDIV_BYPASS	0x00200000
dict set regsC100 EPHY_CLKDIV_RATIO_SHIFT	16
dict set regsC100 PUI_CLKDIV_BYPASS	0x00004000
dict set regsC100 PUI_CLKDIV_SRCCLK	0x00002000
dict set regsC100 PUI_CLKDIV_RATIO_SHIFT	8
dict set regsC100 PCI_CLKDIV_BYPASS	0x00000020
dict set regsC100 PCI_CLKDIV_RATIO_SHIFT	0

dict set regsC100 ARM0_CLK_PD		0x00200000
dict set regsC100 ARM1_CLK_PD		0x00100000
dict set regsC100 EPHY_CLK_PD		0x00080000
dict set regsC100 TDM_CLK_PD		0x00040000
dict set regsC100 PUI_CLK_PD		0x00020000
dict set regsC100 PCI_CLK_PD		0x00010000
dict set regsC100 MDMA_AHBCLK_PD	0x00000400
dict set regsC100 I2CSPI_AHBCLK_PD	0x00000200
dict set regsC100 UART_AHBCLK_PD	0x00000100
dict set regsC100 IPSEC_AHBCLK_PD	0x00000080
dict set regsC100 TDM_AHBCLK_PD	0x00000040
dict set regsC100 USB1_AHBCLK_PD	0x00000020
dict set regsC100 USB0_AHBCLK_PD	0x00000010
dict set regsC100 GEMAC1_AHBCLK_PD	0x00000008
dict set regsC100 GEMAC0_AHBCLK_PD	0x00000004
dict set regsC100 PUI_AHBCLK_PD	0x00000002
dict set regsC100 HIF_AHBCLK_PD	0x00000001

dict set regsC100 ARM1_DIV_BP		0x00001000
dict set regsC100 ARM1_DIV_VAL_SHIFT	8
dict set regsC100 ARM0_DIV_BP		0x00000010
dict set regsC100 ARM0_DIV_VAL_SHIFT	0

dict set regsC100 AHBCLK_PLL_LOCK	0x00000002
dict set regsC100 FCLK_PLL_LOCK	0x00000001


#// reset block
dict set regsC100 BLOCK_RESET_REG		[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x100]
dict set regsC100 CSP_RESET_REG		[expr [dict get $regsC100 CLKCORE_BASEADDR ] + 0x104]

dict set regsC100 RNG_RST		0x1000
dict set regsC100 IPSEC_RST		0x0800
dict set regsC100 DDR_RST		0x0400
dict set regsC100 USB1_PHY_RST	0x0200
dict set regsC100 USB0_PHY_RST	0x0100
dict set regsC100 USB1_RST		0x0080
dict set regsC100 USB0_RST		0x0040
dict set regsC100 GEMAC1_RST		0x0020
dict set regsC100 GEMAC0_RST		0x0010
dict set regsC100 TDM_RST		0x0008
dict set regsC100 PUI_RST		0x0004
dict set regsC100 HIF_RST		0x0002
dict set regsC100 PCI_RST		0x0001

#////////////////////////////////////////////////////////////////
#//	DDR  CONTROLLER block
#////////////////////////////////////////////////////////////////

dict set regsC100 DDR_CONFIG_BASEADDR	0x0D000000
dict set regsC100 DENALI_CTL_00_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x00]
dict set regsC100 DENALI_CTL_01_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x08]
dict set regsC100 DENALI_CTL_02_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x10]
dict set regsC100 DENALI_CTL_03_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x18]
dict set regsC100 DENALI_CTL_04_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x20]
dict set regsC100 DENALI_CTL_05_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x28]
dict set regsC100 DENALI_CTL_06_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x30]
dict set regsC100 DENALI_CTL_07_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x38]
dict set regsC100 DENALI_CTL_08_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x40]
dict set regsC100 DENALI_CTL_09_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x48]
dict set regsC100 DENALI_CTL_10_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x50]
dict set regsC100 DENALI_CTL_11_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x58]
dict set regsC100 DENALI_CTL_12_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x60]
dict set regsC100 DENALI_CTL_13_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x68]
dict set regsC100 DENALI_CTL_14_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x70]
dict set regsC100 DENALI_CTL_15_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x78]
dict set regsC100 DENALI_CTL_16_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x80]
dict set regsC100 DENALI_CTL_17_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x88]
dict set regsC100 DENALI_CTL_18_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x90]
dict set regsC100 DENALI_CTL_19_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x98]
dict set regsC100 DENALI_CTL_20_DATA	[expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0xA0]

# 32-bit value
dict set regsC100 DENALI_READY_CHECK         [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x44]
# 8-bit
dict set regsC100 DENALI_WR_DQS              [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x5D]
# 8-bit
dict set regsC100 DENALI_DQS_OUT             [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x5A]
# 8-bit
dict set regsC100 DENALI_DQS_DELAY0          [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] + 0x4F]
# 8-bit
dict set regsC100 DENALI_DQS_DELAY1          [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] +0x50]
# 8-bit
dict set regsC100 DENALI_DQS_DELAY2          [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] +0x51]
# 8-bit
dict set regsC100 DENALI_DQS_DELAY3          [expr [dict get $regsC100 DDR_CONFIG_BASEADDR ] +0x52]


# end of proc regsC100
}
