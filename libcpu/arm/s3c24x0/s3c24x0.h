/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-12-11     Bernard      first version
 */

#ifndef __S3C24X0_H__
#define __S3C24X0_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

/**
 * @addtogroup S3C24X0
 */
/*@{*/

// Memory control 
#define BWSCON    (*(volatile unsigned *)0x48000000) //Bus width & wait status
#define BANKCON0  (*(volatile unsigned *)0x48000004) //Boot ROM control
#define BANKCON1  (*(volatile unsigned *)0x48000008) //BANK1 control
#define BANKCON2  (*(volatile unsigned *)0x4800000c) //BANK2 cControl
#define BANKCON3  (*(volatile unsigned *)0x48000010) //BANK3 control
#define BANKCON4  (*(volatile unsigned *)0x48000014) //BANK4 control
#define BANKCON5  (*(volatile unsigned *)0x48000018) //BANK5 control
#define BANKCON6  (*(volatile unsigned *)0x4800001c) //BANK6 control
#define BANKCON7  (*(volatile unsigned *)0x48000020) //BANK7 control
#define REFRESH   (*(volatile unsigned *)0x48000024) //DRAM/SDRAM efresh
#define BANKSIZE  (*(volatile unsigned *)0x48000028) //Flexible Bank Size
#define MRSRB6    (*(volatile unsigned *)0x4800002c) //Mode egister set for SDRAM
#define MRSRB7    (*(volatile unsigned *)0x48000030) //Mode egister set for SDRAM


// USB Host


// INTERRUPT
#define SRCPND     (*(volatile unsigned *)0x4a000000) //Interrupt request status
#define INTMOD     (*(volatile unsigned *)0x4a000004) //Interrupt mode control
#define INTMSK     (*(volatile unsigned *)0x4a000008) //Interrupt mask control
#define PRIORITY   (*(volatile unsigned *)0x4a00000c) //IRQ priority control
#define INTPND     (*(volatile unsigned *)0x4a000010) //Interrupt request status
#define INTOFFSET  (*(volatile unsigned *)0x4a000014) //Interruot request source offset
#define SUBSRCPND  (*(volatile unsigned *)0x4a000018) //Sub source pending
#define INTSUBMSK  (*(volatile unsigned *)0x4a00001c) //Interrupt sub mask


// DMA
#define DISRC0     (*(volatile unsigned *)0x4b000000) //DMA 0 Initial source
#define DISRCC0    (*(volatile unsigned *)0x4b000004) //DMA 0 Initial source control
#define DIDST0     (*(volatile unsigned *)0x4b000008) //DMA 0 Initial Destination
#define DIDSTC0    (*(volatile unsigned *)0x4b00000c) //DMA 0 Initial Destination control
#define DCON0      (*(volatile unsigned *)0x4b000010) //DMA 0 Control
#define DSTAT0     (*(volatile unsigned *)0x4b000014) //DMA 0 Status
#define DCSRC0     (*(volatile unsigned *)0x4b000018) //DMA 0 Current source
#define DCDST0     (*(volatile unsigned *)0x4b00001c) //DMA 0 Current destination
#define DMASKTRIG0 (*(volatile unsigned *)0x4b000020) //DMA 0 Mask trigger

#define DISRC1     (*(volatile unsigned *)0x4b000040) //DMA 1 Initial source
#define DISRCC1    (*(volatile unsigned *)0x4b000044) //DMA 1 Initial source control
#define DIDST1     (*(volatile unsigned *)0x4b000048) //DMA 1 Initial Destination
#define DIDSTC1    (*(volatile unsigned *)0x4b00004c) //DMA 1 Initial Destination control
#define DCON1      (*(volatile unsigned *)0x4b000050) //DMA 1 Control
#define DSTAT1     (*(volatile unsigned *)0x4b000054) //DMA 1 Status
#define DCSRC1     (*(volatile unsigned *)0x4b000058) //DMA 1 Current source
#define DCDST1     (*(volatile unsigned *)0x4b00005c) //DMA 1 Current destination
#define DMASKTRIG1 (*(volatile unsigned *)0x4b000060) //DMA 1 Mask trigger

#define DISRC2     (*(volatile unsigned *)0x4b000080) //DMA 2 Initial source
#define DISRCC2    (*(volatile unsigned *)0x4b000084) //DMA 2 Initial source control
#define DIDST2     (*(volatile unsigned *)0x4b000088) //DMA 2 Initial Destination
#define DIDSTC2    (*(volatile unsigned *)0x4b00008c) //DMA 2 Initial Destination control
#define DCON2      (*(volatile unsigned *)0x4b000090) //DMA 2 Control
#define DSTAT2     (*(volatile unsigned *)0x4b000094) //DMA 2 Status
#define DCSRC2     (*(volatile unsigned *)0x4b000098) //DMA 2 Current source
#define DCDST2     (*(volatile unsigned *)0x4b00009c) //DMA 2 Current destination
#define DMASKTRIG2 (*(volatile unsigned *)0x4b0000a0) //DMA 2 Mask trigger

#define DISRC3     (*(volatile unsigned *)0x4b0000c0) //DMA 3 Initial source
#define DISRCC3    (*(volatile unsigned *)0x4b0000c4) //DMA 3 Initial source control
#define DIDST3     (*(volatile unsigned *)0x4b0000c8) //DMA 3 Initial Destination
#define DIDSTC3    (*(volatile unsigned *)0x4b0000cc) //DMA 3 Initial Destination control
#define DCON3      (*(volatile unsigned *)0x4b0000d0) //DMA 3 Control
#define DSTAT3     (*(volatile unsigned *)0x4b0000d4) //DMA 3 Status
#define DCSRC3     (*(volatile unsigned *)0x4b0000d8) //DMA 3 Current source
#define DCDST3     (*(volatile unsigned *)0x4b0000dc) //DMA 3 Current destination
#define DMASKTRIG3 (*(volatile unsigned *)0x4b0000e0) //DMA 3 Mask trigger


// CLOCK & POWER MANAGEMENT
#define LOCKTIME   (*(volatile unsigned *)0x4c000000) //PLL lock time counter
#define MPLLCON    (*(volatile unsigned *)0x4c000004) //MPLL Control
#define UPLLCON    (*(volatile unsigned *)0x4c000008) //UPLL Control
#define CLKCON     (*(volatile unsigned *)0x4c00000c) //Clock generator control
#define CLKSLOW    (*(volatile unsigned *)0x4c000010) //Slow clock control
#define CLKDIVN    (*(volatile unsigned *)0x4c000014) //Clock divider control
#define CAMDIVN    (*(volatile unsigned *)0x4c000018)	//USB, CAM Clock divider control


// LCD CONTROLLER
#define LCDCON1    (*(volatile unsigned *)0x4d000000) //LCD control 1
#define LCDCON2    (*(volatile unsigned *)0x4d000004) //LCD control 2
#define LCDCON3    (*(volatile unsigned *)0x4d000008) //LCD control 3
#define LCDCON4    (*(volatile unsigned *)0x4d00000c) //LCD control 4
#define LCDCON5    (*(volatile unsigned *)0x4d000010) //LCD control 5
#define LCDSADDR1  (*(volatile unsigned *)0x4d000014) //STN/TFT Frame buffer start address 1
#define LCDSADDR2  (*(volatile unsigned *)0x4d000018) //STN/TFT Frame buffer start address 2
#define LCDSADDR3  (*(volatile unsigned *)0x4d00001c) //STN/TFT Virtual screen address set
#define REDLUT     (*(volatile unsigned *)0x4d000020) //STN Red lookup table
#define GREENLUT   (*(volatile unsigned *)0x4d000024) //STN Green lookup table 
#define BLUELUT    (*(volatile unsigned *)0x4d000028) //STN Blue lookup table
#define DITHMODE   (*(volatile unsigned *)0x4d00004c) //STN Dithering mode
#define TPAL       (*(volatile unsigned *)0x4d000050) //TFT Temporary palette
#define LCDINTPND  (*(volatile unsigned *)0x4d000054) //LCD Interrupt pending
#define LCDSRCPND  (*(volatile unsigned *)0x4d000058) //LCD Interrupt source
#define LCDINTMSK  (*(volatile unsigned *)0x4d00005c) //LCD Interrupt mask
#define LPCSEL     (*(volatile unsigned *)0x4d000060) //LPC3600 Control
#define PALETTE     0x4d000400                         //Palette start address


// NAND flash
#define NFCONF     (*(volatile unsigned *)0x4e000000)      //NAND Flash configuration
#define NFCMD      (*(volatile unsigned *)0x4e000004)            //NADD Flash command
#define NFADDR     (*(volatile unsigned *)0x4e000008)            //NAND Flash address
#define NFDATA     (*(volatile unsigned *)0x4e00000c)            //NAND Flash data
#define NFSTAT     (*(volatile unsigned *)0x4e000010)      //NAND Flash operation status
#define NFECC      (*(volatile unsigned *)0x4e000014)      //NAND Flash ECC
#define NFECC0     (*(volatile unsigned *)0x4e000014)
#define NFECC1     (*(volatile unsigned *)0x4e000015)
#define NFECC2     (*(volatile unsigned *)0x4e000016)

// UART
#define U0BASE     (*(volatile unsigned *)0x50000000) //UART 0 Line control
#define ULCON0     (*(volatile unsigned *)0x50000000) //UART 0 Line control
#define UCON0      (*(volatile unsigned *)0x50000004) //UART 0 Control
#define UFCON0     (*(volatile unsigned *)0x50000008) //UART 0 FIFO control
#define UMCON0     (*(volatile unsigned *)0x5000000c) //UART 0 Modem control
#define USTAT0   (*(volatile unsigned *)0x50000010) //UART 0 Tx/Rx status
#define URXB0   (*(volatile unsigned *)0x50000014) //UART 0 Rx error status
#define UFSTAT0    (*(volatile unsigned *)0x50000018) //UART 0 FIFO status
#define UMSTAT0    (*(volatile unsigned *)0x5000001c) //UART 0 Modem status
#define UBRD0    (*(volatile unsigned *)0x50000028) //UART 0 Baud ate divisor

#define U1BASE     (*(volatile unsigned *)0x50004000) //UART 1 Line control
#define ULCON1     (*(volatile unsigned *)0x50004000) //UART 1 Line control
#define UCON1      (*(volatile unsigned *)0x50004004) //UART 1 Control
#define UFCON1     (*(volatile unsigned *)0x50004008) //UART 1 FIFO control
#define UMCON1     (*(volatile unsigned *)0x5000400c) //UART 1 Modem control
#define USTAT1   (*(volatile unsigned *)0x50004010) //UART 1 Tx/Rx status
#define URXB1   (*(volatile unsigned *)0x50004014) //UART 1 Rx error status
#define UFSTAT1    (*(volatile unsigned *)0x50004018) //UART 1 FIFO status
#define UMSTAT1    (*(volatile unsigned *)0x5000401c) //UART 1 Modem status
#define UBRD1    (*(volatile unsigned *)0x50004028) //UART 1 Baud ate divisor

#define U2BASE     *(volatile unsigned *)0x50008000 //UART 2 Line control
#define ULCON2     (*(volatile unsigned *)0x50008000) //UART 2 Line control
#define UCON2      (*(volatile unsigned *)0x50008004) //UART 2 Control
#define UFCON2     (*(volatile unsigned *)0x50008008) //UART 2 FIFO control
#define UMCON2     (*(volatile unsigned *)0x5000800c) //UART 2 Modem control
#define USTAT2   (*(volatile unsigned *)0x50008010) //UART 2 Tx/Rx status
#define URXB2   (*(volatile unsigned *)0x50008014) //UART 2 Rx error status
#define UFSTAT2    (*(volatile unsigned *)0x50008018) //UART 2 FIFO status
#define UMSTAT2    (*(volatile unsigned *)0x5000801c) //UART 2 Modem status
#define UBRD2    (*(volatile unsigned *)0x50008028) //UART 2 Baud ate divisor

#ifdef __BIG_ENDIAN
#define UTXH0      (*(volatile unsigned char *)0x50000023) //UART 0 Transmission Hold
#define URXH0      (*(volatile unsigned char *)0x50000027) //UART 0 Receive buffer
#define UTXH1      (*(volatile unsigned char *)0x50004023) //UART 1 Transmission Hold
#define URXH1      (*(volatile unsigned char *)0x50004027) //UART 1 Receive buffer
#define UTXH2      (*(volatile unsigned char *)0x50008023) //UART 2 Transmission Hold
#define URXH2      (*(volatile unsigned char *)0x50008027) //UART 2 Receive buffer

#define WrUTXH0(ch) (*(volatile unsigned char *)0x50000023)=(unsigned char)(ch)
#define RdURXH0()   (*(volatile unsigned char *)0x50000027)
#define WrUTXH1(ch) (*(volatile unsigned char *)0x50004023)=(unsigned char)(ch)
#define RdURXH1()   (*(volatile unsigned char *)0x50004027)
#define WrUTXH2(ch) (*(volatile unsigned char *)0x50008023)=(unsigned char)(ch)
#define RdURXH2()   (*(volatile unsigned char *)0x50008027)

#else //Little Endian
#define UTXH0 (*(volatile unsigned char *)0x50000020) //UART 0 Transmission Hold
#define URXH0 (*(volatile unsigned char *)0x50000024) //UART 0 Receive buffer
#define UTXH1 (*(volatile unsigned char *)0x50004020) //UART 1 Transmission Hold
#define URXH1 (*(volatile unsigned char *)0x50004024) //UART 1 Receive buffer
#define UTXH2 (*(volatile unsigned char *)0x50008020) //UART 2 Transmission Hold
#define URXH2 (*(volatile unsigned char *)0x50008024) //UART 2 Receive buffer

#define WrUTXH0(ch) (*(volatile unsigned char *)0x50000020)=(unsigned char)(ch)
#define RdURXH0()   (*(volatile unsigned char *)0x50000024)
#define WrUTXH1(ch) (*(volatile unsigned char *)0x50004020)=(unsigned char)(ch)
#define RdURXH1()   (*(volatile unsigned char *)0x50004024)
#define WrUTXH2(ch) (*(volatile unsigned char *)0x50008020)=(unsigned char)(ch)
#define RdURXH2()   (*(volatile unsigned char *)0x50008024)

#endif


// PWM TIMER
#define TCFG0  (*(volatile unsigned *)0x51000000) //Timer 0 configuration
#define TCFG1  (*(volatile unsigned *)0x51000004) //Timer 1 configuration
#define TCON   (*(volatile unsigned *)0x51000008) //Timer control
#define TCNTB0 (*(volatile unsigned *)0x5100000c) //Timer count buffer 0
#define TCMPB0 (*(volatile unsigned *)0x51000010) //Timer compare buffer 0
#define TCNTO0 (*(volatile unsigned *)0x51000014) //Timer count observation 0
#define TCNTB1 (*(volatile unsigned *)0x51000018) //Timer count buffer 1
#define TCMPB1 (*(volatile unsigned *)0x5100001c) //Timer compare buffer 1
#define TCNTO1 (*(volatile unsigned *)0x51000020) //Timer count observation 1
#define TCNTB2 (*(volatile unsigned *)0x51000024) //Timer count buffer 2
#define TCMPB2 (*(volatile unsigned *)0x51000028) //Timer compare buffer 2
#define TCNTO2 (*(volatile unsigned *)0x5100002c) //Timer count observation 2
#define TCNTB3 (*(volatile unsigned *)0x51000030) //Timer count buffer 3
#define TCMPB3 (*(volatile unsigned *)0x51000034) //Timer compare buffer 3
#define TCNTO3 (*(volatile unsigned *)0x51000038) //Timer count observation 3
#define TCNTB4 (*(volatile unsigned *)0x5100003c) //Timer count buffer 4
#define TCNTO4 (*(volatile unsigned *)0x51000040) //Timer count observation 4

// Added for 2440
#define FLTOUT		(*(volatile unsigned *)0x560000c0)	// Filter output(Read only)
#define DSC0			(*(volatile unsigned *)0x560000c4)	// Strength control register 0
#define DSC1			(*(volatile unsigned *)0x560000c8)	// Strength control register 1
#define MSLCON		(*(volatile unsigned *)0x560000cc)	// Memory sleep control register


// USB DEVICE
#ifdef __BIG_ENDIAN
#define FUNC_ADDR_REG     (*(volatile unsigned char *)0x52000143) //Function address
#define PWR_REG           (*(volatile unsigned char *)0x52000147) //Power management
#define EP_INT_REG        (*(volatile unsigned char *)0x5200014b) //EP Interrupt pending and clear
#define USB_INT_REG       (*(volatile unsigned char *)0x5200015b) //USB Interrupt pending and clear
#define EP_INT_EN_REG     (*(volatile unsigned char *)0x5200015f) //Interrupt enable
#define USB_INT_EN_REG    (*(volatile unsigned char *)0x5200016f)
#define FRAME_NUM1_REG    (*(volatile unsigned char *)0x52000173) //Frame number lower byte
#define FRAME_NUM2_REG    (*(volatile unsigned char *)0x52000177) //Frame number higher byte
#define INDEX_REG         (*(volatile unsigned char *)0x5200017b) //Register index
#define MAXP_REG          (*(volatile unsigned char *)0x52000183) //Endpoint max packet
#define EP0_CSR           (*(volatile unsigned char *)0x52000187) //Endpoint 0 status
#define IN_CSR1_REG       (*(volatile unsigned char *)0x52000187) //In endpoint control status
#define IN_CSR2_REG       (*(volatile unsigned char *)0x5200018b)
#define OUT_CSR1_REG      (*(volatile unsigned char *)0x52000193) //Out endpoint control status
#define OUT_CSR2_REG      (*(volatile unsigned char *)0x52000197)
#define OUT_FIFO_CNT1_REG (*(volatile unsigned char *)0x5200019b) //Endpoint out write count
#define OUT_FIFO_CNT2_REG (*(volatile unsigned char *)0x5200019f)
#define EP0_FIFO          (*(volatile unsigned char *)0x520001c3) //Endpoint 0 FIFO
#define EP1_FIFO          (*(volatile unsigned char *)0x520001c7) //Endpoint 1 FIFO
#define EP2_FIFO          (*(volatile unsigned char *)0x520001cb) //Endpoint 2 FIFO
#define EP3_FIFO          (*(volatile unsigned char *)0x520001cf) //Endpoint 3 FIFO
#define EP4_FIFO          (*(volatile unsigned char *)0x520001d3) //Endpoint 4 FIFO
#define EP1_DMA_CON       (*(volatile unsigned char *)0x52000203) //EP1 DMA interface control
#define EP1_DMA_UNIT      (*(volatile unsigned char *)0x52000207) //EP1 DMA Tx unit counter
#define EP1_DMA_FIFO      (*(volatile unsigned char *)0x5200020b) //EP1 DMA Tx FIFO counter
#define EP1_DMA_TTC_L     (*(volatile unsigned char *)0x5200020f) //EP1 DMA total Tx counter
#define EP1_DMA_TTC_M     (*(volatile unsigned char *)0x52000213)
#define EP1_DMA_TTC_H     (*(volatile unsigned char *)0x52000217)
#define EP2_DMA_CON       (*(volatile unsigned char *)0x5200021b) //EP2 DMA interface control
#define EP2_DMA_UNIT      (*(volatile unsigned char *)0x5200021f) //EP2 DMA Tx unit counter
#define EP2_DMA_FIFO      (*(volatile unsigned char *)0x52000223) //EP2 DMA Tx FIFO counter
#define EP2_DMA_TTC_L     (*(volatile unsigned char *)0x52000227) //EP2 DMA total Tx counter
#define EP2_DMA_TTC_M     (*(volatile unsigned char *)0x5200022b)
#define EP2_DMA_TTC_H     (*(volatile unsigned char *)0x5200022f)
#define EP3_DMA_CON       (*(volatile unsigned char *)0x52000243) //EP3 DMA interface control
#define EP3_DMA_UNIT      (*(volatile unsigned char *)0x52000247) //EP3 DMA Tx unit counter
#define EP3_DMA_FIFO      (*(volatile unsigned char *)0x5200024b) //EP3 DMA Tx FIFO counter
#define EP3_DMA_TTC_L     (*(volatile unsigned char *)0x5200024f) //EP3 DMA total Tx counter
#define EP3_DMA_TTC_M     (*(volatile unsigned char *)0x52000253)
#define EP3_DMA_TTC_H     (*(volatile unsigned char *)0x52000257)
#define EP4_DMA_CON       (*(volatile unsigned char *)0x5200025b) //EP4 DMA interface control
#define EP4_DMA_UNIT      (*(volatile unsigned char *)0x5200025f) //EP4 DMA Tx unit counter
#define EP4_DMA_FIFO      (*(volatile unsigned char *)0x52000263) //EP4 DMA Tx FIFO counter
#define EP4_DMA_TTC_L     (*(volatile unsigned char *)0x52000267) //EP4 DMA total Tx counter
#define EP4_DMA_TTC_M     (*(volatile unsigned char *)0x5200026b)
#define EP4_DMA_TTC_H     (*(volatile unsigned char *)0x5200026f)

#else  // Little Endian
#define FUNC_ADDR_REG     (*(volatile unsigned char *)0x52000140) //Function address
#define PWR_REG           (*(volatile unsigned char *)0x52000144) //Power management
#define EP_INT_REG        (*(volatile unsigned char *)0x52000148) //EP Interrupt pending and clear
#define USB_INT_REG       (*(volatile unsigned char *)0x52000158) //USB Interrupt pending and clear
#define EP_INT_EN_REG     (*(volatile unsigned char *)0x5200015c) //Interrupt enable
#define USB_INT_EN_REG    (*(volatile unsigned char *)0x5200016c)
#define FRAME_NUM1_REG    (*(volatile unsigned char *)0x52000170) //Frame number lower byte
#define FRAME_NUM2_REG    (*(volatile unsigned char *)0x52000174) //Frame number higher byte
#define INDEX_REG         (*(volatile unsigned char *)0x52000178) //Register index
#define MAXP_REG          (*(volatile unsigned char *)0x52000180) //Endpoint max packet
#define EP0_CSR           (*(volatile unsigned char *)0x52000184) //Endpoint 0 status
#define IN_CSR1_REG       (*(volatile unsigned char *)0x52000184) //In endpoint control status
#define IN_CSR2_REG       (*(volatile unsigned char *)0x52000188)
#define OUT_CSR1_REG      (*(volatile unsigned char *)0x52000190) //Out endpoint control status
#define OUT_CSR2_REG      (*(volatile unsigned char *)0x52000194)
#define OUT_FIFO_CNT1_REG (*(volatile unsigned char *)0x52000198) //Endpoint out write count
#define OUT_FIFO_CNT2_REG (*(volatile unsigned char *)0x5200019c)
#define EP0_FIFO          (*(volatile unsigned char *)0x520001c0) //Endpoint 0 FIFO
#define EP1_FIFO          (*(volatile unsigned char *)0x520001c4) //Endpoint 1 FIFO
#define EP2_FIFO          (*(volatile unsigned char *)0x520001c8) //Endpoint 2 FIFO
#define EP3_FIFO          (*(volatile unsigned char *)0x520001cc) //Endpoint 3 FIFO
#define EP4_FIFO          (*(volatile unsigned char *)0x520001d0) //Endpoint 4 FIFO
#define EP1_DMA_CON       (*(volatile unsigned char *)0x52000200) //EP1 DMA interface control
#define EP1_DMA_UNIT      (*(volatile unsigned char *)0x52000204) //EP1 DMA Tx unit counter
#define EP1_DMA_FIFO      (*(volatile unsigned char *)0x52000208) //EP1 DMA Tx FIFO counter
#define EP1_DMA_TTC_L     (*(volatile unsigned char *)0x5200020c) //EP1 DMA total Tx counter
#define EP1_DMA_TTC_M     (*(volatile unsigned char *)0x52000210)
#define EP1_DMA_TTC_H     (*(volatile unsigned char *)0x52000214)
#define EP2_DMA_CON       (*(volatile unsigned char *)0x52000218) //EP2 DMA interface control
#define EP2_DMA_UNIT      (*(volatile unsigned char *)0x5200021c) //EP2 DMA Tx unit counter
#define EP2_DMA_FIFO      (*(volatile unsigned char *)0x52000220) //EP2 DMA Tx FIFO counter
#define EP2_DMA_TTC_L     (*(volatile unsigned char *)0x52000224) //EP2 DMA total Tx counter
#define EP2_DMA_TTC_M     (*(volatile unsigned char *)0x52000228)
#define EP2_DMA_TTC_H     (*(volatile unsigned char *)0x5200022c)
#define EP3_DMA_CON       (*(volatile unsigned char *)0x52000240) //EP3 DMA interface control
#define EP3_DMA_UNIT      (*(volatile unsigned char *)0x52000244) //EP3 DMA Tx unit counter
#define EP3_DMA_FIFO      (*(volatile unsigned char *)0x52000248) //EP3 DMA Tx FIFO counter
#define EP3_DMA_TTC_L     (*(volatile unsigned char *)0x5200024c) //EP3 DMA total Tx counter
#define EP3_DMA_TTC_M     (*(volatile unsigned char *)0x52000250)
#define EP3_DMA_TTC_H     (*(volatile unsigned char *)0x52000254)
#define EP4_DMA_CON       (*(volatile unsigned char *)0x52000258) //EP4 DMA interface control
#define EP4_DMA_UNIT      (*(volatile unsigned char *)0x5200025c) //EP4 DMA Tx unit counter
#define EP4_DMA_FIFO      (*(volatile unsigned char *)0x52000260) //EP4 DMA Tx FIFO counter
#define EP4_DMA_TTC_L     (*(volatile unsigned char *)0x52000264) //EP4 DMA total Tx counter
#define EP4_DMA_TTC_M     (*(volatile unsigned char *)0x52000268)
#define EP4_DMA_TTC_H     (*(volatile unsigned char *)0x5200026c)
#endif   // __BIG_ENDIAN


// WATCH DOG TIMER
#define WTCON   (*(volatile unsigned *)0x53000000) //Watch-dog timer mode
#define WTDAT   (*(volatile unsigned *)0x53000004) //Watch-dog timer data
#define WTCNT   (*(volatile unsigned *)0x53000008) //Eatch-dog timer count


// IIC
#define IICCON  (*(volatile unsigned *)0x54000000) //IIC control
#define IICSTAT (*(volatile unsigned *)0x54000004) //IIC status
#define IICADD  (*(volatile unsigned *)0x54000008) //IIC address
#define IICDS   (*(volatile unsigned *)0x5400000c) //IIC data shift


// IIS
#define IISCON  (*(volatile unsigned *)0x55000000) //IIS Control
#define IISMOD  (*(volatile unsigned *)0x55000004) //IIS Mode
#define IISPSR  (*(volatile unsigned *)0x55000008) //IIS Prescaler
#define IISFCON (*(volatile unsigned *)0x5500000c) //IIS FIFO control

#ifdef __BIG_ENDIAN
#define IISFIFO  ((volatile unsigned short *)0x55000012) //IIS FIFO entry

#else //Little Endian
#define IISFIFO  ((volatile unsigned short *)0x55000010) //IIS FIFO entry

#endif


// I/O PORT
#define GPACON    (*(volatile unsigned *)0x56000000) //Port A control
#define GPADAT    (*(volatile unsigned *)0x56000004) //Port A data

#define GPBCON    (*(volatile unsigned *)0x56000010) //Port B control
#define GPBDAT    (*(volatile unsigned *)0x56000014) //Port B data
#define GPBUP     (*(volatile unsigned *)0x56000018) //Pull-up control B

#define GPCCON    (*(volatile unsigned *)0x56000020) //Port C control
#define GPCDAT    (*(volatile unsigned *)0x56000024) //Port C data
#define GPCUP     (*(volatile unsigned *)0x56000028) //Pull-up control C

#define GPDCON    (*(volatile unsigned *)0x56000030) //Port D control
#define GPDDAT    (*(volatile unsigned *)0x56000034) //Port D data
#define GPDUP     (*(volatile unsigned *)0x56000038) //Pull-up control D

#define GPECON    (*(volatile unsigned *)0x56000040) //Port E control
#define GPEDAT    (*(volatile unsigned *)0x56000044) //Port E data
#define GPEUP     (*(volatile unsigned *)0x56000048) //Pull-up control E

#define GPFCON    (*(volatile unsigned *)0x56000050) //Port F control
#define GPFDAT    (*(volatile unsigned *)0x56000054) //Port F data
#define GPFUP     (*(volatile unsigned *)0x56000058) //Pull-up control F

#define GPGCON    (*(volatile unsigned *)0x56000060) //Port G control
#define GPGDAT    (*(volatile unsigned *)0x56000064) //Port G data
#define GPGUP     (*(volatile unsigned *)0x56000068) //Pull-up control G

#define GPHCON    (*(volatile unsigned *)0x56000070) //Port H control
#define GPHDAT    (*(volatile unsigned *)0x56000074) //Port H data
#define GPHUP     (*(volatile unsigned *)0x56000078) //Pull-up control H

#define GPJCON    (*(volatile unsigned *)0x560000d0)	//Port J control
#define GPJDAT    (*(volatile unsigned *)0x560000d4)	//Port J data
#define GPJUP     (*(volatile unsigned *)0x560000d8)	//Pull-up control J

#define MISCCR    (*(volatile unsigned *)0x56000080) //Miscellaneous control
#define DCLKCON   (*(volatile unsigned *)0x56000084) //DCLK0/1 control
#define EXTINT0   (*(volatile unsigned *)0x56000088) //External interrupt control egister 0
#define EXTINT1   (*(volatile unsigned *)0x5600008c) //External interrupt control egister 1
#define EXTINT2   (*(volatile unsigned *)0x56000090) //External interrupt control egister 2
#define EINTFLT0  (*(volatile unsigned *)0x56000094) //Reserved
#define EINTFLT1  (*(volatile unsigned *)0x56000098) //Reserved
#define EINTFLT2  (*(volatile unsigned *)0x5600009c) //External interrupt filter control egister 2
#define EINTFLT3  (*(volatile unsigned *)0x560000a0) //External interrupt filter control egister 3
#define EINTMASK  (*(volatile unsigned *)0x560000a4) //External interrupt mask
#define EINTPEND  (*(volatile unsigned *)0x560000a8) //External interrupt pending
#define GSTATUS0  (*(volatile unsigned *)0x560000ac) //External pin status
#define GSTATUS1  (*(volatile unsigned *)0x560000b0) //Chip ID(0x32410000)
#define GSTATUS2  (*(volatile unsigned *)0x560000b4) //Reset type
#define GSTATUS3  (*(volatile unsigned *)0x560000b8) //Saved data0(32-bit) before entering POWER_OFF mode
#define GSTATUS4  (*(volatile unsigned *)0x560000bc) //Saved data0(32-bit) before entering POWER_OFF mode


// RTC
#ifdef __BIG_ENDIAN
#define RTCCON    (*(volatile unsigned char *)0x57000043) //RTC control
#define TICNT     (*(volatile unsigned char *)0x57000047) //Tick time count
#define RTCALM    (*(volatile unsigned char *)0x57000053) //RTC alarm control
#define ALMSEC    (*(volatile unsigned char *)0x57000057) //Alarm second
#define ALMMIN    (*(volatile unsigned char *)0x5700005b) //Alarm minute
#define ALMHOUR   (*(volatile unsigned char *)0x5700005f) //Alarm Hour
#define ALMDATE   (*(volatile unsigned char *)0x57000063) //Alarm day     <-- May 06, 2002 SOP
#define ALMMON    (*(volatile unsigned char *)0x57000067) //Alarm month
#define ALMYEAR   (*(volatile unsigned char *)0x5700006b) //Alarm year
#define RTCRST    (*(volatile unsigned char *)0x5700006f) //RTC ound eset
#define BCDSEC    (*(volatile unsigned char *)0x57000073) //BCD second
#define BCDMIN    (*(volatile unsigned char *)0x57000077) //BCD minute
#define BCDHOUR   (*(volatile unsigned char *)0x5700007b) //BCD hour
#define BCDDATE   (*(volatile unsigned char *)0x5700007f) //BCD day       <-- May 06, 2002 SOP
#define BCDDAY    (*(volatile unsigned char *)0x57000083) //BCD date      <-- May 06, 2002 SOP
#define BCDMON    (*(volatile unsigned char *)0x57000087) //BCD month
#define BCDYEAR   (*(volatile unsigned char *)0x5700008b) //BCD year

#else //Little Endian
#define RTCCON    (*(volatile unsigned char *)0x57000040) //RTC control
#define TICNT     (*(volatile unsigned char *)0x57000044) //Tick time count
#define RTCALM    (*(volatile unsigned char *)0x57000050) //RTC alarm control
#define ALMSEC    (*(volatile unsigned char *)0x57000054) //Alarm second
#define ALMMIN    (*(volatile unsigned char *)0x57000058) //Alarm minute
#define ALMHOUR   (*(volatile unsigned char *)0x5700005c) //Alarm Hour
#define ALMDATE   (*(volatile unsigned char *)0x57000060) //Alarm day      <-- May 06, 2002 SOP
#define ALMMON    (*(volatile unsigned char *)0x57000064) //Alarm month
#define ALMYEAR   (*(volatile unsigned char *)0x57000068) //Alarm year
#define RTCRST    (*(volatile unsigned char *)0x5700006c) //RTC ound eset
#define BCDSEC    (*(volatile unsigned char *)0x57000070) //BCD second
#define BCDMIN    (*(volatile unsigned char *)0x57000074) //BCD minute
#define BCDHOUR   (*(volatile unsigned char *)0x57000078) //BCD hour
#define BCDDATE   (*(volatile unsigned char *)0x5700007c) //BCD day        <-- May 06, 2002 SOP
#define BCDDAY    (*(volatile unsigned char *)0x57000080) //BCD date       <-- May 06, 2002 SOP
#define BCDMON    (*(volatile unsigned char *)0x57000084) //BCD month
#define BCDYEAR   (*(volatile unsigned char *)0x57000088) //BCD year
#endif  //RTC


// ADC
#define ADCCON    (*(volatile unsigned *)0x58000000) //ADC control
#define ADCTSC    (*(volatile unsigned *)0x58000004) //ADC touch screen control
#define ADCDLY    (*(volatile unsigned *)0x58000008) //ADC start or Interval Delay
#define ADCDAT0   (*(volatile unsigned *)0x5800000c) //ADC conversion data 0
#define ADCDAT1   (*(volatile unsigned *)0x58000010) //ADC conversion data 1

// SPI
#define SPCON0    (*(volatile unsigned *)0x59000000) //SPI0 control
#define SPSTA0    (*(volatile unsigned *)0x59000004) //SPI0 status
#define SPPIN0    (*(volatile unsigned *)0x59000008) //SPI0 pin control
#define SPPRE0    (*(volatile unsigned *)0x5900000c) //SPI0 baud ate prescaler
#define SPTDAT0   (*(volatile unsigned *)0x59000010) //SPI0 Tx data
#define SPRDAT0   (*(volatile unsigned *)0x59000014) //SPI0 Rx data

#define SPCON1    (*(volatile unsigned *)0x59000020) //SPI1 control
#define SPSTA1    (*(volatile unsigned *)0x59000024) //SPI1 status
#define SPPIN1    (*(volatile unsigned *)0x59000028) //SPI1 pin control
#define SPPRE1    (*(volatile unsigned *)0x5900002c) //SPI1 baud ate prescaler
#define SPTDAT1   (*(volatile unsigned *)0x59000030) //SPI1 Tx data
#define SPRDAT1   (*(volatile unsigned *)0x59000034) //SPI1 Rx data


// SD Interface
#define SDICON     (*(volatile unsigned *)0x5a000000) //SDI control
#define SDIPRE     (*(volatile unsigned *)0x5a000004) //SDI baud ate prescaler
#define SDICARG    (*(volatile unsigned *)0x5a000008) //SDI command argument
#define SDICCON    (*(volatile unsigned *)0x5a00000c) //SDI command control
#define SDICSTA    (*(volatile unsigned *)0x5a000010) //SDI command status
#define SDIRSP0    (*(volatile unsigned *)0x5a000014) //SDI esponse 0
#define SDIRSP1    (*(volatile unsigned *)0x5a000018) //SDI esponse 1
#define SDIRSP2    (*(volatile unsigned *)0x5a00001c) //SDI esponse 2
#define SDIRSP3    (*(volatile unsigned *)0x5a000020) //SDI esponse 3
#define SDIDTIMER  (*(volatile unsigned *)0x5a000024) //SDI data/busy timer
#define SDIBSIZE   (*(volatile unsigned *)0x5a000028) //SDI block size
#define SDIDCON    (*(volatile unsigned *)0x5a00002c) //SDI data control
#define SDIDCNT    (*(volatile unsigned *)0x5a000030) //SDI data emain counter
#define SDIDSTA    (*(volatile unsigned *)0x5a000034) //SDI data status
#define SDIFSTA    (*(volatile unsigned *)0x5a000038) //SDI FIFO status
#define SDIIMSK    (*(volatile unsigned *)0x5a000040) //SDI interrupt mask

#ifdef __BIG_ENDIAN  /* edited for 2440A */
#define SDIDAT     (*(volatile unsigned *)0x5a00004c)
#else  // Little Endian
#define SDIDAT     (*(volatile unsigned *)0x5a000040)  
#endif   //SD Interface

// PENDING BIT
#define INTEINT0      (0)
#define INTEINT1      (1)
#define INTEINT2      (2)
#define INTEINT3      (3)
#define INTEINT4_7    (4)
#define INTEINT8_23   (5)
#define INTNOTUSED6   (6)
#define INTBAT_FLT    (7)
#define INTTICK       (8)
#define INTWDT        (9)
#define INTTIMER0     (10)
#define INTTIMER1     (11)
#define INTTIMER2     (12)
#define INTTIMER3     (13)
#define INTTIMER4     (14)
#define INTUART2      (15)
#define INTLCD        (16)
#define INTDMA0       (17)
#define INTDMA1       (18)
#define INTDMA2       (19)
#define INTDMA3       (20)
#define INTSDI        (21)
#define INTSPI0       (22)
#define INTUART1      (23)
//#define INTNOTUSED24  (24)
#define INTNIC  (24)
#define INTUSBD       (25)
#define INTUSBH       (26)
#define INTIIC        (27)
#define INTUART0      (28)
#define INTSPI1       (29)
#define INTRTC        (30)
#define INTADC        (31)
#define BIT_ALLMSK     (0xffffffff)

#define BIT_SUB_ALLMSK (0x7ff)
#define INTSUB_ADC    (10)
#define INTSUB_TC     (9)
#define INTSUB_ERR2   (8)
#define INTSUB_TXD2   (7)
#define INTSUB_RXD2   (6)
#define INTSUB_ERR1   (5)
#define INTSUB_TXD1   (4)
#define INTSUB_RXD1   (3)
#define INTSUB_ERR0   (2)
#define INTSUB_TXD0   (1)
#define INTSUB_RXD0   (0)

#define BIT_SUB_ADC    (0x1<<10)
#define BIT_SUB_TC     (0x1<<9)
#define BIT_SUB_ERR2   (0x1<<8)
#define BIT_SUB_TXD2   (0x1<<7)
#define BIT_SUB_RXD2   (0x1<<6)
#define BIT_SUB_ERR1   (0x1<<5)
#define BIT_SUB_TXD1   (0x1<<4)
#define BIT_SUB_RXD1   (0x1<<3)
#define BIT_SUB_ERR0   (0x1<<2)
#define BIT_SUB_TXD0   (0x1<<1)
#define BIT_SUB_RXD0   (0x1<<0)

#define ClearPending(bit) {SRCPND = bit;INTPND = bit;INTPND;}
//Wait until INTPND is changed for the case that the ISR is very short.

#define INTGLOBAL		32

/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE		0x10
#define FIQMODE			0x11
#define IRQMODE			0x12
#define SVCMODE			0x13
#define ABORTMODE		0x17
#define UNDEFMODE		0x1b
#define MODEMASK		0x1f
#define NOINT			0xc0

struct rt_hw_register
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r4;
	rt_uint32_t r5;
	rt_uint32_t r6;
	rt_uint32_t r7;
	rt_uint32_t r8;
	rt_uint32_t r9;
	rt_uint32_t r10;
	rt_uint32_t fp;
	rt_uint32_t ip;
	rt_uint32_t sp;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t cpsr;
	rt_uint32_t ORIG_r0;
};

#ifdef __cplusplus
}
#endif

/*@}*/

#endif
