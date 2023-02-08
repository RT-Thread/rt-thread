#include <rtthread.h>
#include <dfs_fs.h>

#include "sd.h"

#include <AT91SAM7X.h>

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM7X256
// *****************************************************************************
#define AT91C_PIO_PA0        ((unsigned int) 1 <<  0) // Pin Controlled by PA0
#define AT91C_PA0_RXD0     ((unsigned int) AT91C_PIO_PA0) //  USART 0 Receive Data
#define AT91C_PIO_PA1        ((unsigned int) 1 <<  1) // Pin Controlled by PA1
#define AT91C_PA1_TXD0     ((unsigned int) AT91C_PIO_PA1) //  USART 0 Transmit Data
#define AT91C_PIO_PA10       ((unsigned int) 1 << 10) // Pin Controlled by PA10
#define AT91C_PA10_TWD      ((unsigned int) AT91C_PIO_PA10) //  TWI Two-wire Serial Data
#define AT91C_PIO_PA11       ((unsigned int) 1 << 11) // Pin Controlled by PA11
#define AT91C_PA11_TWCK     ((unsigned int) AT91C_PIO_PA11) //  TWI Two-wire Serial Clock
#define AT91C_PIO_PA12       ((unsigned int) 1 << 12) // Pin Controlled by PA12
#define AT91C_PA12_SPI0_NPCS0 ((unsigned int) AT91C_PIO_PA12) //  SPI 0 Peripheral Chip Select 0
#define AT91C_PIO_PA13       ((unsigned int) 1 << 13) // Pin Controlled by PA13
#define AT91C_PA13_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA13) //  SPI 0 Peripheral Chip Select 1
#define AT91C_PA13_PCK1     ((unsigned int) AT91C_PIO_PA13) //  PMC Programmable Clock Output 1
#define AT91C_PIO_PA14       ((unsigned int) 1 << 14) // Pin Controlled by PA14
#define AT91C_PA14_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PA14) //  SPI 0 Peripheral Chip Select 2
#define AT91C_PA14_IRQ1     ((unsigned int) AT91C_PIO_PA14) //  External Interrupt 1
#define AT91C_PIO_PA15       ((unsigned int) 1 << 15) // Pin Controlled by PA15
#define AT91C_PA15_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PA15) //  SPI 0 Peripheral Chip Select 3
#define AT91C_PA15_TCLK2    ((unsigned int) AT91C_PIO_PA15) //  Timer Counter 2 external clock input
#define AT91C_PIO_PA16       ((unsigned int) 1 << 16) // Pin Controlled by PA16
#define AT91C_PA16_SPI0_MISO ((unsigned int) AT91C_PIO_PA16) //  SPI 0 Master In Slave
#define AT91C_PIO_PA17       ((unsigned int) 1 << 17) // Pin Controlled by PA17
#define AT91C_PA17_SPI0_MOSI ((unsigned int) AT91C_PIO_PA17) //  SPI 0 Master Out Slave
#define AT91C_PIO_PA18       ((unsigned int) 1 << 18) // Pin Controlled by PA18
#define AT91C_PA18_SPI0_SPCK ((unsigned int) AT91C_PIO_PA18) //  SPI 0 Serial Clock
#define AT91C_PIO_PA19       ((unsigned int) 1 << 19) // Pin Controlled by PA19
#define AT91C_PA19_CANRX    ((unsigned int) AT91C_PIO_PA19) //  CAN Receive
#define AT91C_PIO_PA2        ((unsigned int) 1 <<  2) // Pin Controlled by PA2
#define AT91C_PA2_SCK0     ((unsigned int) AT91C_PIO_PA2) //  USART 0 Serial Clock
#define AT91C_PA2_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PA2) //  SPI 1 Peripheral Chip Select 1
#define AT91C_PIO_PA20       ((unsigned int) 1 << 20) // Pin Controlled by PA20
#define AT91C_PA20_CANTX    ((unsigned int) AT91C_PIO_PA20) //  CAN Transmit
#define AT91C_PIO_PA21       ((unsigned int) 1 << 21) // Pin Controlled by PA21
#define AT91C_PA21_TF       ((unsigned int) AT91C_PIO_PA21) //  SSC Transmit Frame Sync
#define AT91C_PA21_SPI1_NPCS0 ((unsigned int) AT91C_PIO_PA21) //  SPI 1 Peripheral Chip Select 0
#define AT91C_PIO_PA22       ((unsigned int) 1 << 22) // Pin Controlled by PA22
#define AT91C_PA22_TK       ((unsigned int) AT91C_PIO_PA22) //  SSC Transmit Clock
#define AT91C_PA22_SPI1_SPCK ((unsigned int) AT91C_PIO_PA22) //  SPI 1 Serial Clock
#define AT91C_PIO_PA23       ((unsigned int) 1 << 23) // Pin Controlled by PA23
#define AT91C_PA23_TD       ((unsigned int) AT91C_PIO_PA23) //  SSC Transmit data
#define AT91C_PA23_SPI1_MOSI ((unsigned int) AT91C_PIO_PA23) //  SPI 1 Master Out Slave
#define AT91C_PIO_PA24       ((unsigned int) 1 << 24) // Pin Controlled by PA24
#define AT91C_PA24_RD       ((unsigned int) AT91C_PIO_PA24) //  SSC Receive Data
#define AT91C_PA24_SPI1_MISO ((unsigned int) AT91C_PIO_PA24) //  SPI 1 Master In Slave
#define AT91C_PIO_PA25       ((unsigned int) 1 << 25) // Pin Controlled by PA25
#define AT91C_PA25_RK       ((unsigned int) AT91C_PIO_PA25) //  SSC Receive Clock
#define AT91C_PA25_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PA25) //  SPI 1 Peripheral Chip Select 1
#define AT91C_PIO_PA26       ((unsigned int) 1 << 26) // Pin Controlled by PA26
#define AT91C_PA26_RF       ((unsigned int) AT91C_PIO_PA26) //  SSC Receive Frame Sync
#define AT91C_PA26_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PA26) //  SPI 1 Peripheral Chip Select 2
#define AT91C_PIO_PA27       ((unsigned int) 1 << 27) // Pin Controlled by PA27
#define AT91C_PA27_DRXD     ((unsigned int) AT91C_PIO_PA27) //  DBGU Debug Receive Data
#define AT91C_PA27_PCK3     ((unsigned int) AT91C_PIO_PA27) //  PMC Programmable Clock Output 3
#define AT91C_PIO_PA28       ((unsigned int) 1 << 28) // Pin Controlled by PA28
#define AT91C_PA28_DTXD     ((unsigned int) AT91C_PIO_PA28) //  DBGU Debug Transmit Data
#define AT91C_PIO_PA29       ((unsigned int) 1 << 29) // Pin Controlled by PA29
#define AT91C_PA29_FIQ      ((unsigned int) AT91C_PIO_PA29) //  AIC Fast Interrupt Input
#define AT91C_PA29_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PA29) //  SPI 1 Peripheral Chip Select 3
#define AT91C_PIO_PA3        ((unsigned int) 1 <<  3) // Pin Controlled by PA3
#define AT91C_PA3_RTS0     ((unsigned int) AT91C_PIO_PA3) //  USART 0 Ready To Send
#define AT91C_PA3_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PA3) //  SPI 1 Peripheral Chip Select 2
#define AT91C_PIO_PA30       ((unsigned int) 1 << 30) // Pin Controlled by PA30
#define AT91C_PA30_IRQ0     ((unsigned int) AT91C_PIO_PA30) //  External Interrupt 0
#define AT91C_PA30_PCK2     ((unsigned int) AT91C_PIO_PA30) //  PMC Programmable Clock Output 2
#define AT91C_PIO_PA4        ((unsigned int) 1 <<  4) // Pin Controlled by PA4
#define AT91C_PA4_CTS0     ((unsigned int) AT91C_PIO_PA4) //  USART 0 Clear To Send
#define AT91C_PA4_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PA4) //  SPI 1 Peripheral Chip Select 3
#define AT91C_PIO_PA5        ((unsigned int) 1 <<  5) // Pin Controlled by PA5
#define AT91C_PA5_RXD1     ((unsigned int) AT91C_PIO_PA5) //  USART 1 Receive Data
#define AT91C_PIO_PA6        ((unsigned int) 1 <<  6) // Pin Controlled by PA6
#define AT91C_PA6_TXD1     ((unsigned int) AT91C_PIO_PA6) //  USART 1 Transmit Data
#define AT91C_PIO_PA7        ((unsigned int) 1 <<  7) // Pin Controlled by PA7
#define AT91C_PA7_SCK1     ((unsigned int) AT91C_PIO_PA7) //  USART 1 Serial Clock
#define AT91C_PA7_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA7) //  SPI 0 Peripheral Chip Select 1
#define AT91C_PIO_PA8        ((unsigned int) 1 <<  8) // Pin Controlled by PA8
#define AT91C_PA8_RTS1     ((unsigned int) AT91C_PIO_PA8) //  USART 1 Ready To Send
#define AT91C_PA8_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PA8) //  SPI 0 Peripheral Chip Select 2
#define AT91C_PIO_PA9        ((unsigned int) 1 <<  9) // Pin Controlled by PA9
#define AT91C_PA9_CTS1     ((unsigned int) AT91C_PIO_PA9) //  USART 1 Clear To Send
#define AT91C_PA9_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PA9) //  SPI 0 Peripheral Chip Select 3
#define AT91C_PIO_PB0        ((unsigned int) 1 <<  0) // Pin Controlled by PB0
#define AT91C_PB0_ETXCK_EREFCK ((unsigned int) AT91C_PIO_PB0) //  Ethernet MAC Transmit Clock/Reference Clock
#define AT91C_PB0_PCK0     ((unsigned int) AT91C_PIO_PB0) //  PMC Programmable Clock Output 0
#define AT91C_PIO_PB1        ((unsigned int) 1 <<  1) // Pin Controlled by PB1
#define AT91C_PB1_ETXEN    ((unsigned int) AT91C_PIO_PB1) //  Ethernet MAC Transmit Enable
#define AT91C_PIO_PB10       ((unsigned int) 1 << 10) // Pin Controlled by PB10
#define AT91C_PB10_ETX2     ((unsigned int) AT91C_PIO_PB10) //  Ethernet MAC Transmit Data 2
#define AT91C_PB10_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PB10) //  SPI 1 Peripheral Chip Select 1
#define AT91C_PIO_PB11       ((unsigned int) 1 << 11) // Pin Controlled by PB11
#define AT91C_PB11_ETX3     ((unsigned int) AT91C_PIO_PB11) //  Ethernet MAC Transmit Data 3
#define AT91C_PB11_SPI1_NPCS2 ((unsigned int) AT91C_PIO_PB11) //  SPI 1 Peripheral Chip Select 2
#define AT91C_PIO_PB12       ((unsigned int) 1 << 12) // Pin Controlled by PB12
#define AT91C_PB12_ETXER    ((unsigned int) AT91C_PIO_PB12) //  Ethernet MAC Transmikt Coding Error
#define AT91C_PB12_TCLK0    ((unsigned int) AT91C_PIO_PB12) //  Timer Counter 0 external clock input
#define AT91C_PIO_PB13       ((unsigned int) 1 << 13) // Pin Controlled by PB13
#define AT91C_PB13_ERX2     ((unsigned int) AT91C_PIO_PB13) //  Ethernet MAC Receive Data 2
#define AT91C_PB13_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PB13) //  SPI 0 Peripheral Chip Select 1
#define AT91C_PIO_PB14       ((unsigned int) 1 << 14) // Pin Controlled by PB14
#define AT91C_PB14_ERX3     ((unsigned int) AT91C_PIO_PB14) //  Ethernet MAC Receive Data 3
#define AT91C_PB14_SPI0_NPCS2 ((unsigned int) AT91C_PIO_PB14) //  SPI 0 Peripheral Chip Select 2
#define AT91C_PIO_PB15       ((unsigned int) 1 << 15) // Pin Controlled by PB15
#define AT91C_PB15_ERXDV_ECRSDV ((unsigned int) AT91C_PIO_PB15) //  Ethernet MAC Receive Data Valid
#define AT91C_PIO_PB16       ((unsigned int) 1 << 16) // Pin Controlled by PB16
#define AT91C_PB16_ECOL     ((unsigned int) AT91C_PIO_PB16) //  Ethernet MAC Collision Detected
#define AT91C_PB16_SPI1_NPCS3 ((unsigned int) AT91C_PIO_PB16) //  SPI 1 Peripheral Chip Select 3
#define AT91C_PIO_PB17       ((unsigned int) 1 << 17) // Pin Controlled by PB17
#define AT91C_PB17_ERXCK    ((unsigned int) AT91C_PIO_PB17) //  Ethernet MAC Receive Clock
#define AT91C_PB17_SPI0_NPCS3 ((unsigned int) AT91C_PIO_PB17) //  SPI 0 Peripheral Chip Select 3
#define AT91C_PIO_PB18       ((unsigned int) 1 << 18) // Pin Controlled by PB18
#define AT91C_PB18_EF100    ((unsigned int) AT91C_PIO_PB18) //  Ethernet MAC Force 100 Mbits/sec
#define AT91C_PB18_ADTRG    ((unsigned int) AT91C_PIO_PB18) //  ADC External Trigger
#define AT91C_PIO_PB19       ((unsigned int) 1 << 19) // Pin Controlled by PB19
#define AT91C_PB19_PWM0     ((unsigned int) AT91C_PIO_PB19) //  PWM Channel 0
#define AT91C_PB19_TCLK1    ((unsigned int) AT91C_PIO_PB19) //  Timer Counter 1 external clock input
#define AT91C_PIO_PB2        ((unsigned int) 1 <<  2) // Pin Controlled by PB2
#define AT91C_PB2_ETX0     ((unsigned int) AT91C_PIO_PB2) //  Ethernet MAC Transmit Data 0
#define AT91C_PIO_PB20       ((unsigned int) 1 << 20) // Pin Controlled by PB20
#define AT91C_PB20_PWM1     ((unsigned int) AT91C_PIO_PB20) //  PWM Channel 1
#define AT91C_PB20_PCK0     ((unsigned int) AT91C_PIO_PB20) //  PMC Programmable Clock Output 0
#define AT91C_PIO_PB21       ((unsigned int) 1 << 21) // Pin Controlled by PB21
#define AT91C_PB21_PWM2     ((unsigned int) AT91C_PIO_PB21) //  PWM Channel 2
#define AT91C_PB21_PCK1     ((unsigned int) AT91C_PIO_PB21) //  PMC Programmable Clock Output 1
#define AT91C_PIO_PB22       ((unsigned int) 1 << 22) // Pin Controlled by PB22
#define AT91C_PB22_PWM3     ((unsigned int) AT91C_PIO_PB22) //  PWM Channel 3
#define AT91C_PB22_PCK2     ((unsigned int) AT91C_PIO_PB22) //  PMC Programmable Clock Output 2
#define AT91C_PIO_PB23       ((unsigned int) 1 << 23) // Pin Controlled by PB23
#define AT91C_PB23_TIOA0    ((unsigned int) AT91C_PIO_PB23) //  Timer Counter 0 Multipurpose Timer I/O Pin A
#define AT91C_PB23_DCD1     ((unsigned int) AT91C_PIO_PB23) //  USART 1 Data Carrier Detect
#define AT91C_PIO_PB24       ((unsigned int) 1 << 24) // Pin Controlled by PB24
#define AT91C_PB24_TIOB0    ((unsigned int) AT91C_PIO_PB24) //  Timer Counter 0 Multipurpose Timer I/O Pin B
#define AT91C_PB24_DSR1     ((unsigned int) AT91C_PIO_PB24) //  USART 1 Data Set ready
#define AT91C_PIO_PB25       ((unsigned int) 1 << 25) // Pin Controlled by PB25
#define AT91C_PB25_TIOA1    ((unsigned int) AT91C_PIO_PB25) //  Timer Counter 1 Multipurpose Timer I/O Pin A
#define AT91C_PB25_DTR1     ((unsigned int) AT91C_PIO_PB25) //  USART 1 Data Terminal ready
#define AT91C_PIO_PB26       ((unsigned int) 1 << 26) // Pin Controlled by PB26
#define AT91C_PB26_TIOB1    ((unsigned int) AT91C_PIO_PB26) //  Timer Counter 1 Multipurpose Timer I/O Pin B
#define AT91C_PB26_RI1      ((unsigned int) AT91C_PIO_PB26) //  USART 1 Ring Indicator
#define AT91C_PIO_PB27       ((unsigned int) 1 << 27) // Pin Controlled by PB27
#define AT91C_PB27_TIOA2    ((unsigned int) AT91C_PIO_PB27) //  Timer Counter 2 Multipurpose Timer I/O Pin A
#define AT91C_PB27_PWM0     ((unsigned int) AT91C_PIO_PB27) //  PWM Channel 0
#define AT91C_PIO_PB28       ((unsigned int) 1 << 28) // Pin Controlled by PB28
#define AT91C_PB28_TIOB2    ((unsigned int) AT91C_PIO_PB28) //  Timer Counter 2 Multipurpose Timer I/O Pin B
#define AT91C_PB28_PWM1     ((unsigned int) AT91C_PIO_PB28) //  PWM Channel 1
#define AT91C_PIO_PB29       ((unsigned int) 1 << 29) // Pin Controlled by PB29
#define AT91C_PB29_PCK1     ((unsigned int) AT91C_PIO_PB29) //  PMC Programmable Clock Output 1
#define AT91C_PB29_PWM2     ((unsigned int) AT91C_PIO_PB29) //  PWM Channel 2
#define AT91C_PIO_PB3        ((unsigned int) 1 <<  3) // Pin Controlled by PB3
#define AT91C_PB3_ETX1     ((unsigned int) AT91C_PIO_PB3) //  Ethernet MAC Transmit Data 1
#define AT91C_PIO_PB30       ((unsigned int) 1 << 30) // Pin Controlled by PB30
#define AT91C_PB30_PCK2     ((unsigned int) AT91C_PIO_PB30) //  PMC Programmable Clock Output 2
#define AT91C_PB30_PWM3     ((unsigned int) AT91C_PIO_PB30) //  PWM Channel 3
#define AT91C_PIO_PB4        ((unsigned int) 1 <<  4) // Pin Controlled by PB4
#define AT91C_PB4_ECRS     ((unsigned int) AT91C_PIO_PB4) //  Ethernet MAC Carrier Sense/Carrier Sense and Data Valid
#define AT91C_PIO_PB5        ((unsigned int) 1 <<  5) // Pin Controlled by PB5
#define AT91C_PB5_ERX0     ((unsigned int) AT91C_PIO_PB5) //  Ethernet MAC Receive Data 0
#define AT91C_PIO_PB6        ((unsigned int) 1 <<  6) // Pin Controlled by PB6
#define AT91C_PB6_ERX1     ((unsigned int) AT91C_PIO_PB6) //  Ethernet MAC Receive Data 1
#define AT91C_PIO_PB7        ((unsigned int) 1 <<  7) // Pin Controlled by PB7
#define AT91C_PB7_ERXER    ((unsigned int) AT91C_PIO_PB7) //  Ethernet MAC Receive Error
#define AT91C_PIO_PB8        ((unsigned int) 1 <<  8) // Pin Controlled by PB8
#define AT91C_PB8_EMDC     ((unsigned int) AT91C_PIO_PB8) //  Ethernet MAC Management Data Clock
#define AT91C_PIO_PB9        ((unsigned int) 1 <<  9) // Pin Controlled by PB9
#define AT91C_PB9_EMDIO    ((unsigned int) AT91C_PIO_PB9) //  Ethernet MAC Management Data Input/Output

#define CARD_WP_PIN      AT91C_PIO_PA16
#define CARD_INS_PIN     AT91C_PIO_PA15
#define CARD_PWR_PIN     AT91C_PIO_PA12

typedef volatile unsigned int AT91S_REG;// Hardware register definition
// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
// *****************************************************************************
typedef struct _AT91S_SPI {
	AT91S_REG	 SPI_CR; 	// Control Register
	AT91S_REG	 SPI_MR; 	// Mode Register
	AT91S_REG	 SPI_RDR; 	// Receive Data Register
	AT91S_REG	 SPI_TDR; 	// Transmit Data Register
	AT91S_REG	 SPI_SR; 	// Status Register
	AT91S_REG	 SPI_IER; 	// Interrupt Enable Register
	AT91S_REG	 SPI_IDR; 	// Interrupt Disable Register
	AT91S_REG	 SPI_IMR; 	// Interrupt Mask Register
	AT91S_REG	 Reserved0[4]; 	// 
	AT91S_REG	 SPI_CSR[4]; 	// Chip Select Register
	AT91S_REG	 Reserved1[48]; 	// 
	AT91S_REG	 SPI_RPR; 	// Receive Pointer Register
	AT91S_REG	 SPI_RCR; 	// Receive Counter Register
	AT91S_REG	 SPI_TPR; 	// Transmit Pointer Register
	AT91S_REG	 SPI_TCR; 	// Transmit Counter Register
	AT91S_REG	 SPI_RNPR; 	// Receive Next Pointer Register
	AT91S_REG	 SPI_RNCR; 	// Receive Next Counter Register
	AT91S_REG	 SPI_TNPR; 	// Transmit Next Pointer Register
	AT91S_REG	 SPI_TNCR; 	// Transmit Next Counter Register
	AT91S_REG	 SPI_PTCR; 	// PDC Transfer Control Register
	AT91S_REG	 SPI_PTSR; 	// PDC Transfer Status Register
} AT91S_SPI, *AT91PS_SPI;
static AT91PS_SPI pSPI  = ((AT91PS_SPI) 0xFFFE0000);

// -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
#define AT91C_SPI_SPIEN       ((unsigned int) 0x1 <<  0) // (SPI) SPI Enable
#define AT91C_SPI_SPIDIS      ((unsigned int) 0x1 <<  1) // (SPI) SPI Disable
#define AT91C_SPI_SWRST       ((unsigned int) 0x1 <<  7) // (SPI) SPI Software reset
#define AT91C_SPI_LASTXFER    ((unsigned int) 0x1 << 24) // (SPI) SPI Last Transfer
// -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
#define AT91C_SPI_MSTR        ((unsigned int) 0x1 <<  0) // (SPI) Master/Slave Mode
#define AT91C_SPI_PS          ((unsigned int) 0x1 <<  1) // (SPI) Peripheral Select
#define 	AT91C_SPI_PS_FIXED                ((unsigned int) 0x0 <<  1) // (SPI) Fixed Peripheral Select
#define 	AT91C_SPI_PS_VARIABLE             ((unsigned int) 0x1 <<  1) // (SPI) Variable Peripheral Select
#define AT91C_SPI_PCSDEC      ((unsigned int) 0x1 <<  2) // (SPI) Chip Select Decode
#define AT91C_SPI_FDIV        ((unsigned int) 0x1 <<  3) // (SPI) Clock Selection
#define AT91C_SPI_MODFDIS     ((unsigned int) 0x1 <<  4) // (SPI) Mode Fault Detection
#define AT91C_SPI_LLB         ((unsigned int) 0x1 <<  7) // (SPI) Clock Selection
#define AT91C_SPI_PCS         ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select
#define AT91C_SPI_DLYBCS      ((unsigned int) 0xFF << 24) // (SPI) Delay Between Chip Selects
// -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
#define AT91C_SPI_RD          ((unsigned int) 0xFFFF <<  0) // (SPI) Receive Data
#define AT91C_SPI_RPCS        ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
#define AT91C_SPI_TD          ((unsigned int) 0xFFFF <<  0) // (SPI) Transmit Data
#define AT91C_SPI_TPCS        ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
#define AT91C_SPI_RDRF        ((unsigned int) 0x1 <<  0) // (SPI) Receive Data Register Full
#define AT91C_SPI_TDRE        ((unsigned int) 0x1 <<  1) // (SPI) Transmit Data Register Empty
#define AT91C_SPI_MODF        ((unsigned int) 0x1 <<  2) // (SPI) Mode Fault Error
#define AT91C_SPI_OVRES       ((unsigned int) 0x1 <<  3) // (SPI) Overrun Error Status
#define AT91C_SPI_ENDRX       ((unsigned int) 0x1 <<  4) // (SPI) End of Receiver Transfer
#define AT91C_SPI_ENDTX       ((unsigned int) 0x1 <<  5) // (SPI) End of Receiver Transfer
#define AT91C_SPI_RXBUFF      ((unsigned int) 0x1 <<  6) // (SPI) RXBUFF Interrupt
#define AT91C_SPI_TXBUFE      ((unsigned int) 0x1 <<  7) // (SPI) TXBUFE Interrupt
#define AT91C_SPI_NSSR        ((unsigned int) 0x1 <<  8) // (SPI) NSSR Interrupt
#define AT91C_SPI_TXEMPTY     ((unsigned int) 0x1 <<  9) // (SPI) TXEMPTY Interrupt
#define AT91C_SPI_SPIENS      ((unsigned int) 0x1 << 16) // (SPI) Enable Status
// -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
// -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
// -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
// -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
#define AT91C_SPI_CPOL        ((unsigned int) 0x1 <<  0) // (SPI) Clock Polarity
#define AT91C_SPI_NCPHA       ((unsigned int) 0x1 <<  1) // (SPI) Clock Phase
#define AT91C_SPI_CSAAT       ((unsigned int) 0x1 <<  3) // (SPI) Chip Select Active After Transfer
#define AT91C_SPI_BITS        ((unsigned int) 0xF <<  4) // (SPI) Bits Per Transfer
#define 	AT91C_SPI_BITS_8                    ((unsigned int) 0x0 <<  4) // (SPI) 8 Bits Per transfer
#define 	AT91C_SPI_BITS_9                    ((unsigned int) 0x1 <<  4) // (SPI) 9 Bits Per transfer
#define 	AT91C_SPI_BITS_10                   ((unsigned int) 0x2 <<  4) // (SPI) 10 Bits Per transfer
#define 	AT91C_SPI_BITS_11                   ((unsigned int) 0x3 <<  4) // (SPI) 11 Bits Per transfer
#define 	AT91C_SPI_BITS_12                   ((unsigned int) 0x4 <<  4) // (SPI) 12 Bits Per transfer
#define 	AT91C_SPI_BITS_13                   ((unsigned int) 0x5 <<  4) // (SPI) 13 Bits Per transfer
#define 	AT91C_SPI_BITS_14                   ((unsigned int) 0x6 <<  4) // (SPI) 14 Bits Per transfer
#define 	AT91C_SPI_BITS_15                   ((unsigned int) 0x7 <<  4) // (SPI) 15 Bits Per transfer
#define 	AT91C_SPI_BITS_16                   ((unsigned int) 0x8 <<  4) // (SPI) 16 Bits Per transfer
#define AT91C_SPI_SCBR        ((unsigned int) 0xFF <<  8) // (SPI) Serial Clock Baud Rate
#define AT91C_SPI_DLYBS       ((unsigned int) 0xFF << 16) // (SPI) Delay Before SPCK
#define AT91C_SPI_DLYBCT      ((unsigned int) 0xFF << 24) // (SPI) Delay Between Consecutive Transfers

#define CARD_SELECT_PIN  AT91C_PA13_SPI0_NPCS1
#define SPI_CSR_NUM      0

#define SPI_SCBR_MIN     2

/* MMC/SD command (in SPI) */
#define CMD0    (0x40+0)    /* GO_IDLE_STATE */
#define CMD1    (0x40+1)    /* SEND_OP_COND */
#define CMD9    (0x40+9)    /* SEND_CSD */
#define CMD10   (0x40+10)   /* SEND_CID */
#define CMD12   (0x40+12)   /* STOP_TRANSMISSION */
#define CMD17   (0x40+17)   /* READ_SINGLE_BLOCK */
#define CMD18   (0x40+18)   /* READ_MULTIPLE_BLOCK */
#define CMD24   (0x40+24)   /* WRITE_BLOCK */
#define CMD25   (0x40+25)   /* WRITE_MULTIPLE_BLOCK */
#define CMD58   (0x40+58)   /* READ_OCR */

/* Control signals (Platform dependent) */
#define SELECT()        (AT91C_PIOA_CODR = CARD_SELECT_PIN) /* MMC CS = L */
#define DESELECT()      (AT91C_PIOA_SODR = CARD_SELECT_PIN) /* MMC CS = H */

#define SOCKWP          CARD_WP_PIN         /* Write protect switch (PB5) */
#define SOCKINS         CARD_INS_PIN        /* Card detect switch (PB4) */

#define POWER_ON()      (AT91C_PIOA_CODR = CARD_PWR_PIN)
#define POWER_OFF()     (AT91C_PIOA_SODR = CARD_PWR_PIN)

static struct rt_device sd;
static struct dfs_partition part;

static void AT91_spiSetSpeed(rt_uint8_t speed)
{
	rt_uint32_t reg;

	if ( speed < SPI_SCBR_MIN ) speed = SPI_SCBR_MIN;
	if ( speed > 1 ) speed &= 0xFE;

	reg = pSPI->SPI_CSR[SPI_CSR_NUM];
	reg = ( reg & ~(AT91C_SPI_SCBR) ) | ( (rt_uint32_t)speed << 8 );
	pSPI->SPI_CSR[SPI_CSR_NUM] = reg;
}

static rt_uint8_t AT91_spi(rt_uint8_t outgoing)
{
	rt_uint8_t incoming;

	while( !( pSPI->SPI_SR & AT91C_SPI_TDRE ) ); // transfer compl. wait
	pSPI->SPI_TDR = (rt_uint16_t)( outgoing );

	while( !( pSPI->SPI_SR & AT91C_SPI_RDRF ) ); // wait for char
	incoming = (rt_uint8_t)( pSPI->SPI_RDR );

	return incoming;
}

/*--------------------------------*/
/* Transmit a rt_uint8_t to MMC via SPI */
/* (Platform dependent)           */
rt_inline void xmit_spi(rt_uint8_t dat)
{
	AT91_spi(dat);
}

/*---------------------------------*/
/* Receive a rt_uint8_t from MMC via SPI */
/* (Platform dependent)            */
rt_inline rt_uint8_t rcvr_spi(void)
{
	return AT91_spi(0xff);
}

/* Alternative "macro" (not at AT91 so far) to receive data fast */
static void rcvr_spi_m(rt_uint8_t *dst)
{
	*dst = rcvr_spi();
}

/*---------------------*/
/* Wait for card ready */
static rt_uint8_t wait_ready ()
{
	rt_uint8_t res;

	rcvr_spi();
	do
	{
		res = rcvr_spi();
	} while ((res != 0xFF));

	return res;
}

/*--------------------------------*/
/* Receive a data packet from MMC */

rt_bool_t rcvr_datablock (rt_uint8_t *buff, rt_uint8_t wc)
{
	rt_uint8_t token;

	{
	    /* Wait for data packet in timeout of 100ms */
		token = rcvr_spi();
	}while ((token == 0xFF));

	if(token != 0xFE) return RT_FALSE;   /* If not valid data token, retutn with error */

	do
	{
	    /* Receive the data block into buffer */
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
	} while (--wc);

	rcvr_spi();                  /* Discard CRC */
	rcvr_spi();

	return RT_TRUE;               /* Return with success */
}

/*---------------------------*/
/* Send a data packet to MMC */
static rt_bool_t xmit_datablock(const rt_uint8_t *buff, rt_uint8_t token)
{
	rt_uint8_t resp, wc = 0;

	if (wait_ready() != 0xFF) return RT_FALSE;

	xmit_spi(token);                    /* Xmit data token */
	if (token != 0xFD)
	{   /* Is data token */
		do
		{
		    /* Xmit the 512 rt_uint8_t data block to MMC */
			xmit_spi(*buff++);
			xmit_spi(*buff++);
		} while (--wc);

		xmit_spi(0xFF);                 /* CRC (Dummy) */
		xmit_spi(0xFF);
		resp = rcvr_spi();              /* Reveive data response */

		if ((resp & 0x1F) != 0x05)      /* If not accepted, return with error */
			return RT_FALSE;
	}

	return RT_TRUE;
}

/*------------------------------*/
/* Send a command packet to MMC */
rt_uint8_t send_cmd (rt_uint8_t cmd, rt_uint32_t arg)
{
	rt_uint8_t n, res;

	if (wait_ready() != 0xFF) return 0xFF;

	/* Send command packet */
	xmit_spi(cmd);                      /* Command */
	xmit_spi((rt_uint8_t)(arg >> 24));  /* Argument[31..24] */
	xmit_spi((rt_uint8_t)(arg >> 16));  /* Argument[23..16] */
	xmit_spi((rt_uint8_t)(arg >> 8));   /* Argument[15..8] */
	xmit_spi((rt_uint8_t)arg);          /* Argument[7..0] */
	xmit_spi(0x95);                     /* CRC (valid for only CMD0) */

	/* Receive command response */
	if (cmd == CMD12) rcvr_spi();       /* Skip a stuff rt_uint8_t when stop reading */
	n = 10;                             /* Wait for a valid response in timeout of 10 attempts */
	do
	{
		res = rcvr_spi();
	}
	while ((res & 0x80) && --n);

	return res;         /* Return with the response value */
}

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t count;

	count  = size / 512;

	/* CS = L */
	SELECT();
	
	/* append partition offset */
	pos += part.offset * 512;

	if (count == 1)
	{   /* Single block read */
		if ((send_cmd(CMD17, pos) == 0)   /* READ_SINGLE_BLOCK */
				&& rcvr_datablock(buffer, (rt_uint8_t)(512/2)))
			count = 0;
		else
			count = 1;
	}
	else
	{            /* Multiple block read */
		if (send_cmd(CMD18, pos) == 0)
		{
			rt_uint8_t* ptr;
			
			ptr = buffer;
			do
			{
				if (!rcvr_datablock(ptr, (rt_uint8_t)(512/2))) break;
				ptr += 512;
			} while (--count);

			send_cmd(CMD12, 0);            /* STOP_TRANSMISSION */
		}
	}

	DESELECT();         /* CS = H */
	rcvr_spi();         /* Idle (Release DO) */

	if (count)
	{
		// rt_set_errno(-RT_ERROR);
		return 0;
	}
	
	return size / 512;
}

static rt_ssize_t rt_sdcard_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t count;

	count = size / 512;

	/* CS = L */
	SELECT();

	/* append partition offset */
	pos += part.offset * 512;

	if (count == 1)
	{
	    /* Single block write */
		if ((send_cmd(CMD24, pos) == 0)   /* WRITE_BLOCK */
				&& xmit_datablock(buffer, 0xFE))
			count = 0;
		else
			count = 1;
	}
	else
	{
	    /* Multiple block write */
		if (send_cmd(CMD25, pos) == 0)
		{
			rt_uint8_t *ptr;
			
			ptr = (rt_uint8_t *)buffer;
			do
			{
				if (!xmit_datablock(ptr, 0xFC)) break;
				ptr += 512;
			} while (--count);

			if (!xmit_datablock(0, 0xFD))   /* STOP_TRAN token */
				count = 1;
		}
	}

	DESELECT();         /* CS = H */
	rcvr_spi();         /* Idle (Release DO) */

	if (count)
	{
		rt_set_errno(-RT_ERROR);
		return 0;
	}

	return size;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

void rt_hw_sdcard_init()
{
	rt_uint32_t n;
	rt_uint8_t* sector;
	
	sd.type     = RT_Device_Class_Block;
	sd.init 	= rt_sdcard_init;
	sd.open 	= rt_sdcard_open;
	sd.close    = rt_sdcard_close;
	sd.read 	= rt_sdcard_read;
	sd.write    = rt_sdcard_write;
	sd.control  = rt_sdcard_control;
	sd.user_data = RT_NULL;

	AT91C_PIOA_PER  = CARD_PWR_PIN; // enable GPIO of CS-pin
	AT91C_PIOA_CODR = CARD_PWR_PIN; // set high
	AT91C_PIOA_OER  = CARD_PWR_PIN; // output enable

	for (n = 0; n < 3000; n ++) ;

	// disable PIO from controlling MOSI, MISO, SCK (=hand over to SPI)
	// keep CS untouched - used as GPIO pin during init
	AT91C_PIOA_PDR = AT91C_PA16_SPI0_MISO | AT91C_PA17_SPI0_MOSI | AT91C_PA18_SPI0_SPCK; //  | NCPS_PDR_BIT;
	// set pin-functions in PIO Controller
	AT91C_PIOA_ASR = AT91C_PA16_SPI0_MISO | AT91C_PA17_SPI0_MOSI | AT91C_PA18_SPI0_SPCK; /// not here: | NCPS_ASR_BIT;

	// set chip-select as output high (unselect card)
	AT91C_PIOA_PER  = CARD_SELECT_PIN; // enable GPIO of CS-pin
	AT91C_PIOA_SODR = CARD_SELECT_PIN; // set high
	AT91C_PIOA_OER  = CARD_SELECT_PIN; // output enable

	// enable peripheral clock for SPI ( PID Bit 5 )
	AT91C_PMC_PCER = ( (rt_uint32_t) 1 << AT91C_ID_SPI0 ); // n.b. IDs are just bit-numbers

	// SPI enable and reset
	pSPI->SPI_CR = AT91C_SPI_SPIEN | AT91C_SPI_SWRST;

	// SPI mode: master, FDIV=0, fault detection disabled
	pSPI->SPI_MR  = AT91C_SPI_MSTR | AT91C_SPI_MODFDIS;

	// set chip-select-register
	// 8 bits per transfer, CPOL=1, ClockPhase=0, DLYBCT = 0
	pSPI->SPI_CSR[SPI_CSR_NUM] = AT91C_SPI_CPOL | AT91C_SPI_BITS_8;

	// slow during init
	AT91_spiSetSpeed(0xFE);

	// enable
	pSPI->SPI_CR = AT91C_SPI_SPIEN;

	n = 10;                  /* Dummy clock */
	do
	{
		rcvr_spi();
	} while (--n);

	SELECT();         /* CS = L */
	if (send_cmd(CMD0, 0) == 1)
	{
		/* Enter Idle state */
		while (send_cmd(CMD1, 0));
	}

	DESELECT();         /* CS = H */
	rcvr_spi();         /* Idle (Release DO) */

	AT91_spiSetSpeed(SPI_SCBR_MIN);

	/* get the first sector to read partition table */
	sector = (rt_uint8_t*) rt_malloc (512);
	if (sector == RT_NULL)
	{
		rt_kprintf("allocate partition sector buffer failed\n");
		return;
	}

	n = rt_sdcard_read((rt_device_t)&sd, 0, sector, 512);
	if (n == 512)
	{
		rt_err_t status;
		
		/* get the first partition */
		status = dfs_filesystem_get_partition(&part, sector, 0);
		if (status != RT_EOK)
		{
			/* there is no partition table */
			part.offset = 0;
			part.size   = 0;
		}
	}
	else
	{
		/* there is no partition table */
		part.offset = 0;
		part.size   = 0;
	}

	/* release sector buffer */
	rt_free(sector);

	/* register sd device */
	rt_device_register(&sd, "sd", RT_DEVICE_FLAG_RDWR);
}
