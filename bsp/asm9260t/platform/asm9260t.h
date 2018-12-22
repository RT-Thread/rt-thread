#ifndef __ASM9260T_REGS_H__
#define __ASM9260T_REGS_H__
////////////////////////////////////////////////////////////////////////////////

typedef volatile unsigned char *VP8;
typedef volatile unsigned short *VP16;
typedef volatile unsigned long *VP32;

#define __I  volatile const   /*!< Defines 'read only' permissions    */
#define __O  volatile         /*!< Defines 'write only' permissions   */
#define __IO volatile         /*!< Defines 'read / write' permissions */

#define outb(v, r)      do{*((VP8)(r))=(v);}while(0)
#define outw(v, r)      do{*((VP16)(r))=(v);}while(0)
#define outl(v, r)      do{*((VP32)(r))=(v);}while(0)

#define inb(r)          (*((VP8)(r)))
#define inw(r)          (*((VP16)(r)))
#define inl(r)          (*((VP32)(r)))

#define REG_VAL(r)      (((unsigned long)(r))+0x00)
#define REG_SET(r)      (((unsigned long)(r))+0x04)
#define REG_CLR(r)      (((unsigned long)(r))+0x08)
#define REG_TOG(r)      (((unsigned long)(r))+0x0C)

////////////////////////////////////////////////////////////////////////////////
// SYSTEM CONFIG
#define HW_PRESETCTRL0        0x80040000
#define HW_PRESETCTRL1        0x80040010
#define HW_AHBCLKCTRL0        0x80040020
#define HW_AHBCLKCTRL1        0x80040030
#define HW_SYSTCKCAL          0x80040040
#define HW_SYSPLLCTRL         0x80040100
#define HW_SYSPLLSTAT         0x80040104
#define HW_SYSRSTSTAT         0x80040110
#define HW_MAINCLKSEL         0x80040120
#define HW_MAINCLKUEN         0x80040124
#define HW_UARTCLKSEL         0x80040128
#define HW_UARTCLKUEN         0x8004012C
#define HW_I2S0CLKSEL         0x80040130
#define HW_I2S0CLKUEN         0x80040134
#define HW_I2S1CLKSEL         0x80040138
#define HW_I2S1CLKUEN         0x8004013C
#define HW_USBCLKSEL          0x80040140
#define HW_USBCLKUEN          0x80040144
#define HW_WDTCLKSEL          0x80040160
#define HW_WDTCLKUEN          0x80040164
#define HW_OUTCLKSEL          0x80040170
#define HW_OUTCLKUEN          0x80040174
#define HW_CPUCLKDIV          0x8004017C
#define HW_SYSAHBCLKDIV       0x80040180
#define HW_I2S1_MCLKDIV       0x80040188
#define HW_I2S1_SCLKDIV       0x8004018C
#define HW_I2S0_MCLKDIV       0x80040190
#define HW_I2S0_SCLKDIV       0x80040194
#define HW_UART0CLKDIV        0x80040198
#define HW_UART1CLKDIV        0x8004019C
#define HW_UART2CLKDIV        0x800401A0
#define HW_UART3CLKDIV        0x800401A4
#define HW_UART4CLKDIV        0x800401A8
#define HW_UART5CLKDIV        0x800401AC
#define HW_UART6CLKDIV        0x800401B0
#define HW_UART7CLKDIV        0x800401B4
#define HW_UART8CLKDIV        0x800401B8
#define HW_UART9CLKDIV        0x800401BC
#define HW_SPI0CLKDIV         0x800401C0
#define HW_SPI1CLKDIV         0x800401C4
#define HW_QUADSPI0CLKDIV     0x800401C8
#define HW_SSP0CLKDIV         0x800401D0
#define HW_NANDCLKDIV         0x800401D4
#define HW_TRACECLKDIV        0x800401E0
#define HW_CAMMCLKDIV         0x800401E8
#define HW_WDTCLKDIV          0x800401EC
#define HW_USBCLKDIV          0x800401F0
#define HW_OUTCLKDIV          0x800401F4
#define HW_MACCLKDIV          0x800401F8
#define HW_LCDCLKDIV          0x800401FC
#define HW_ADCCLKDIV          0x80040200
#define HW_PDRUNCFG           0x80040238
#define HW_MATRIXPRI0         0x80040300
#define HW_MATRIXPRI1         0x80040304
#define HW_MATRIXPRI2         0x80040308
#define HW_MATRIXPRI3         0x8004030C
#define HW_MATRIXPRI4         0x80040310
#define HW_MATRIXPRI5         0x80040314
#define HW_MATRIXPRI6         0x80040318
#define HW_MATRIXPRI7         0x8004031C
#define HW_MATRIXPRI8         0x80040320
#define HW_MATRIXPRI9         0x80040324
#define HW_MATRIXPRI10        0x80040328
#define HW_MATRIXPRI11        0x8004032C
#define HW_MATRIXPRI12        0x80040330
#define HW_MATRIXPRI13        0x80040334
#define HW_MATRIXPRI14        0x80040338
#define HW_MATRIXPRI15        0x8004033C
#define HW_EMI_CTRL           0x8004034C
#define HW_RISC_CTRL          0x80040350
#define HW_DMA_CTRL           0x80040354
#define HW_MACPHY_SEL         0x80040360
#define HW_USB_CTRL           0x80040368
#define HW_ANA_CTRL           0x80040370
#define HW_USB0_TEST          0x80040380
#define HW_USB1_TEST          0x80040390
#define HW_USB0_RSTPARA       0x800403A0
#define HW_USB1_RSTPARA       0x800403B0
#define HW_DEVICEID           0x80040400
#define HW_PCON_ADDR          0x80040500

////////////////////////////////////////////////////////////////////////////////
// EMI
#define HW_EMI_SCONR          0x80700000    
#define HW_EMI_STMG0R         0x80700004
#define HW_EMI_STMG1R         0x80700008
#define HW_EMI_SCTLR          0x8070000C
#define HW_EMI_SREFR          0x80700010
#define HW_EMI_SCSLR0_LOW     0x80700014
#define HW_EMI_SCSLR1_LOW     0x80700018
#define HW_EMI_SCSLR2_LOW     0x8070001c
#define HW_EMI_SCSLR3_LOW     0x80700020
#define HW_EMI_SCSLR4_LOW     0x80700024
#define HW_EMI_SCSLR5_LOW     0x80700028
#define HW_EMI_SCSLR6_LOW     0x8070002c
#define HW_EMI_SCSLR7_LOW     0x80700030

#define HW_EMI_SMSKR0         0x80700054
#define HW_EMI_SMSKR1         0x80700058
#define HW_EMI_SMSKR2         0x8070005c
#define HW_EMI_SMSKR3         0x80700060
#define HW_EMI_SMSKR4         0x80700064
#define HW_EMI_SMSKR5         0x80700068
#define HW_EMI_SMSKR6         0x8070006c
#define HW_EMI_SMSKR7         0x80700070

#define HW_EMI_CSALIAS0_LOW   0x80700074
#define HW_EMI_CSALIAS1_LOW   0x80700078

#define HW_EMI_CSREMAP0_LOW   0x80700084
#define HW_EMI_CSREMAP1_LOW   0x80700088

#define HW_EMI_SMTMGR_SET0    0x80700094
#define HW_EMI_SMTMGR_SET1    0x80700098
#define HW_EMI_SMTMGR_SET2    0x8070009c

#define HW_EMI_FLASH_TRPDR    0x807000a0
#define HW_EMI_SMCTLR         0x807000a4
#define HW_EMI_EXN_MODE_REG   0x807000ac

////////////////////////////////////////////////////////////////////////////////
// IOCON
#define HW_IOCON_PIO_BASE     0x80044000
#define HW_IOCON_SCKLOC       0x800442c0
#define HW_IOCON(port,pin)    (HW_IOCON_PIO_BASE|(((port)<<5)|((pin)<<2)))

////////////////////////////////////////////////////////////////////////////////
// GPIO
#define HW_GPIO_DATA_BASE     0x50000000

#define HW_GPIO_DMA_CTRL      0x50000010
#define HW_GPIO_DMA_DATA      0x50000020
#define HW_GPIO_DMA_PADCTRL0  0x50000030
#define HW_GPIO_DMA_PADCTRL1  0x50000040
#define HW_GPIO_DMA_PADCTRL2  0x50000050
#define HW_GPIO_DMA_PADCTRL3  0x50000060
#define HW_GPIO_DMA_CTRL1     0x50000070
#define HW_GPIO_DMA_CTRL2     0x50000080
#define HW_GPIO_DMA_CTRL3     0x50000090
#define HW_GPIO_DMA_CTRL4     0x500000a0

#define HW_GPIO_DATA0         0x50000000
#define HW_GPIO_DATA1         0x50010000
#define HW_GPIO_DATA2         0x50020000
#define HW_GPIO_DATA3         0x50030000
#define HW_GPIO_DATA4         0x50040000

#define HW_GPIO_DIR0          0x50008000
#define HW_GPIO_DIR1          0x50018000
#define HW_GPIO_DIR2          0x50028000
#define HW_GPIO_DIR3          0x50038000
#define HW_GPIO_DIR4          0x50048000

#define HW_GPIO_IS0           0x50008010
#define HW_GPIO_IS1           0x50018010
#define HW_GPIO_IS2           0x50028010
#define HW_GPIO_IS3           0x50038010
#define HW_GPIO_IS4           0x50048010

#define HW_GPIO_IBE0          0x50008020
#define HW_GPIO_IBE1          0x50018020
#define HW_GPIO_IBE2          0x50028020
#define HW_GPIO_IBE3          0x50038020
#define HW_GPIO_IBE4          0x50048020

#define HW_GPIO_IEV0          0x50008030
#define HW_GPIO_IEV1          0x50018030
#define HW_GPIO_IEV2          0x50028030
#define HW_GPIO_IEV3          0x50038030
#define HW_GPIO_IEV4          0x50048030

#define HW_GPIO_IE0           0x50008040
#define HW_GPIO_IE1           0x50018040
#define HW_GPIO_IE2           0x50028040
#define HW_GPIO_IE3           0x50038040
#define HW_GPIO_IE4           0x50048040

#define HW_GPIO_RIS0          0x50008050
#define HW_GPIO_RIS1          0x50018050
#define HW_GPIO_RIS2          0x50028050
#define HW_GPIO_RIS3          0x50038050
#define HW_GPIO_RIS4          0x50048050

#define HW_GPIO_MIS0          0x50008060
#define HW_GPIO_MIS1          0x50018060
#define HW_GPIO_MIS2          0x50028060
#define HW_GPIO_MIS3          0x50038060
#define HW_GPIO_MIS4          0x50048060

#define HW_GPIO_IC0           0x50008070
#define HW_GPIO_IC1           0x50018070
#define HW_GPIO_IC2           0x50028070
#define HW_GPIO_IC3           0x50038070
#define HW_GPIO_IC4           0x50048070 

#define HW_GPIO_DATAMASK0     0x50008080
#define HW_GPIO_DATAMASK1     0x50018080
#define HW_GPIO_DATAMASK2     0x50028080
#define HW_GPIO_DATAMASK3     0x50038080
#define HW_GPIO_DATAMASK4     0x50048080 

////////////////////////////////////////////////////////////////////////////////
// Quad-SPI0
#define QSPI0_BASE_ADDRESS    0x80068000
#define HW_QSPI0_CTRL0        0x80068000
#define HW_QSPI0_CTRL1        0x80068010
#define HW_QSPI0_CMD          0x80068020
#define HW_QSPI0_TIMING       0x80068030
#define HW_QSPI0_DATA         0x80068040
#define HW_QSPI0_STATUS       0x80068050
#define HW_QSPI0_DEBUG0       0x80068060
#define HW_QSPI0_XFER         0x80068070

/////////////////////////////////////////////////////////
//DMA0
#define HW_DMA0_SAR0           0x80100000
#define HW_DMA0_DAR0           0x80100008
#define HW_DMA0_LLP0           0x80100010
#define HW_DMA0_CTL0           0x80100018
#define HW_DMA0_SSTAT0         0x80100020
#define HW_DMA0_DSTAT0         0x80100028
#define HW_DMA0_SSTATAR0       0x80100030      
#define HW_DMA0_DSTATAR0       0x80100038 
#define HW_DMA0_CFG0           0x80100040
#define HW_DMA0_SGR0           0x80100048
#define HW_DMA0_DSR0           0x80100050

#define HW_DMA0_SAR1           0x80100058
#define HW_DMA0_DAR1           0x80100060
#define HW_DMA0_LLP1           0x80100068
#define HW_DMA0_CTL1           0x80100070
#define HW_DMA0_SSTAT1         0x80100078
#define HW_DMA0_DSTAT1         0x80100080
#define HW_DMA0_SSTATAR1       0x80100088      
#define HW_DMA0_DSTATAR1       0x80100090 
#define HW_DMA0_CFG1           0x80100098
#define HW_DMA0_SGR1           0x801000a0
#define HW_DMA0_DSR1           0x801000a8

#define HW_DMA0_SAR2           0x801000b0
#define HW_DMA0_DAR2           0x801000b8
#define HW_DMA0_LLP2           0x801000c0
#define HW_DMA0_CTL2           0x801000c8
#define HW_DMA0_SSTAT2         0x801000d0
#define HW_DMA0_DSTAT2         0x801000d8
#define HW_DMA0_SSTATAR2       0x801000e0      
#define HW_DMA0_DSTATAR2       0x801000e8 
#define HW_DMA0_CFG2           0x801000f0
#define HW_DMA0_SGR2           0x801000f8
#define HW_DMA0_DSR2           0x80100100

#define HW_DMA0_SAR3           0x80100108
#define HW_DMA0_DAR3           0x80100110
#define HW_DMA0_LLP3           0x80100118
#define HW_DMA0_CTL3           0x80100120
#define HW_DMA0_SSTAT3         0x80100128
#define HW_DMA0_DSTAT3         0x80100130
#define HW_DMA0_SSTATAR3       0x80100138      
#define HW_DMA0_DSTATAR3       0x80100140 
#define HW_DMA0_CFG3           0x80100148
#define HW_DMA0_SGR3           0x80100150
#define HW_DMA0_DSR3           0x80100158

#define HW_DMA0_SAR4           0x80100160
#define HW_DMA0_DAR4           0x80100168
#define HW_DMA0_LLP4           0x80100170
#define HW_DMA0_CTL4           0x80100178
#define HW_DMA0_SSTAT4         0x80100180
#define HW_DMA0_DSTAT4         0x80100188
#define HW_DMA0_SSTATAR4       0x80100190      
#define HW_DMA0_DSTATAR4       0x80100198 
#define HW_DMA0_CFG4           0x801001a0
#define HW_DMA0_SGR4           0x801001a8
#define HW_DMA0_DSR4           0x801001b0

#define HW_DMA0_SAR5           0x801001b8
#define HW_DMA0_DAR5           0x801001c0
#define HW_DMA0_LLP5           0x801001c8
#define HW_DMA0_CTL5           0x801001d0
#define HW_DMA0_SSTAT5         0x801001d8
#define HW_DMA0_DSTAT5         0x801001e0
#define HW_DMA0_SSTATAR5       0x801001e8      
#define HW_DMA0_DSTATAR5       0x801001f0 
#define HW_DMA0_CFG5           0x801001f8
#define HW_DMA0_SGR5           0x80100200
#define HW_DMA0_DSR5           0x80100208

#define HW_DMA0_SAR6           0x80100210
#define HW_DMA0_DAR6           0x80100218
#define HW_DMA0_LLP6           0x80100220
#define HW_DMA0_CTL6           0x80100228
#define HW_DMA0_SSTAT6         0x80100230
#define HW_DMA0_DSTAT6         0x80100238
#define HW_DMA0_SSTATAR6       0x80100240      
#define HW_DMA0_DSTATAR6       0x80100248 
#define HW_DMA0_CFG6           0x80100250
#define HW_DMA0_SGR6           0x80100258
#define HW_DMA0_DSR6           0x80100260

#define HW_DMA0_SAR7           0x80100268
#define HW_DMA0_DAR7           0x80100270
#define HW_DMA0_LLP7           0x80100278
#define HW_DMA0_CTL7           0x80100280
#define HW_DMA0_SSTAT7         0x80100288
#define HW_DMA0_DSTAT7         0x80100290
#define HW_DMA0_SSTATAR7       0x80100298      
#define HW_DMA0_DSTATAR7       0x801002a0 
#define HW_DMA0_CFG7           0x801002a8
#define HW_DMA0_SGR7           0x801002b0
#define HW_DMA0_DSR7           0x801002b8

#define HW_DMA0_RawTFR         0x801002c0
#define HW_DMA0_RawBLOCK       0x801002c8
#define HW_DMA0_RawSRCTRAN     0x801002d0
#define HW_DMA0_RawDSTTRAN     0x801002d8
#define HW_DMA0_RawERR         0x801002e0

#define HW_DMA0_StatusTFR      0x801002e8
#define HW_DMA0_StatusBLOCK    0x801002f0
#define HW_DMA0_StatusSRCTRAN  0x801002f8
#define HW_DMA0_StatusDSTTRAN  0x80100300
#define HW_DMA0_StatusERR      0x80100308

#define HW_DMA0_MaskTFR        0x80100310
#define HW_DMA0_MaskBLOCK      0x80100318
#define HW_DMA0_MaskSRCTRAN    0x80100320
#define HW_DMA0_MaskDSTTRAN    0x80100328
#define HW_DMA0_MaskERR        0x80100330

#define HW_DMA0_ClearTFR       0x80100338
#define HW_DMA0_ClearBLOCK     0x80100340
#define HW_DMA0_ClearSRCTRAN   0x80100348
#define HW_DMA0_ClearDSTTRAN   0x80100350
#define HW_DMA0_ClearERR       0x80100358

#define HW_DMA0_STATUSINT      0x80100360

#define HW_DMA0_ReqSrcReg      0x80100368
#define HW_DMA0_ReqDstReg      0x80100370
#define HW_DMA0_SglReqSrcReg   0x80100378
#define HW_DMA0_SglReqDstReg   0x80100380
#define HW_DMA0_LstSrcReg      0x80100388
#define HW_DMA0_LstDstReg      0x80100390

#define HW_DMA0_DMACFGREG      0x80100398
#define HW_DMA0_CHENREG        0x801003a0

////////////////////////////////////////////////////////////////////////////////
// DMA1
#define HW_DMA1_SAR0          0x80200000
#define HW_DMA1_DAR0          0x80200008
#define HW_DMA1_LLP0          0x80200010
#define HW_DMA1_CTL0          0x80200018
#define HW_DMA1_SSTAT0        0x80200020
#define HW_DMA1_DSTAT0        0x80200028
#define HW_DMA1_SSTATAR0      0x80200030
#define HW_DMA1_DSTATAR0      0x80200038
#define HW_DMA1_CFG0          0x80200040
#define HW_DMA1_SGR0          0x80200048
#define HW_DMA1_DSR0          0x80200050

#define HW_DMA1_SAR1          0x80200058
#define HW_DMA1_DAR1          0x80200060
#define HW_DMA1_LLP1          0x80200068
#define HW_DMA1_CTL1          0x80200070
#define HW_DMA1_SSTAT1        0x80200078
#define HW_DMA1_DSTAT1        0x80200080
#define HW_DMA1_SSTATAR1      0x80200088
#define HW_DMA1_DSTATAR1      0x80200090
#define HW_DMA1_CFG1          0x80200098
#define HW_DMA1_SGR1          0x802000a0
#define HW_DMA1_DSR1          0x802000a8

#define HW_DMA1_SAR2          0x802000b0
#define HW_DMA1_DAR2          0x802000b8
#define HW_DMA1_LLP2          0x802000c0
#define HW_DMA1_CTL2          0x802000c8
#define HW_DMA1_SSTAT2        0x802000d0
#define HW_DMA1_DSTAT2        0x802000d8
#define HW_DMA1_SSTATAR2      0x802000e0
#define HW_DMA1_DSTATAR2      0x802000e8
#define HW_DMA1_CFG2          0x802000f0
#define HW_DMA1_SGR2          0x802000f8
#define HW_DMA1_DSR2          0x80200100

#define HW_DMA1_SAR3          0x80200108
#define HW_DMA1_DAR3          0x80200110
#define HW_DMA1_LLP3          0x80200118
#define HW_DMA1_CTL3          0x80200120
#define HW_DMA1_SSTAT3        0x80200128
#define HW_DMA1_DSTAT3        0x80200130
#define HW_DMA1_SSTATAR3      0x80200138
#define HW_DMA1_DSTATAR3      0x80200140
#define HW_DMA1_CFG3          0x80200148
#define HW_DMA1_SGR3          0x80200150
#define HW_DMA1_DSR3          0x80200158

#define HW_DMA1_SAR4          0x80200160
#define HW_DMA1_DAR4          0x80200168
#define HW_DMA1_LLP4          0x80200170
#define HW_DMA1_CTL4          0x80200178
#define HW_DMA1_SSTAT4        0x80200180
#define HW_DMA1_DSTAT4        0x80200188
#define HW_DMA1_SSTATAR4      0x80200190
#define HW_DMA1_DSTATAR4      0x80200198
#define HW_DMA1_CFG4          0x802001a0
#define HW_DMA1_SGR4          0x802001a8
#define HW_DMA1_DSR4          0x802001b0

#define HW_DMA1_SAR5          0x802001b8
#define HW_DMA1_DAR5          0x802001c0
#define HW_DMA1_LLP5          0x802001c8
#define HW_DMA1_CTL5          0x802001d0
#define HW_DMA1_SSTAT5        0x802001d8
#define HW_DMA1_DSTAT5        0x802001e0
#define HW_DMA1_SSTATAR5      0x802001e8
#define HW_DMA1_DSTATAR5      0x802001f0
#define HW_DMA1_CFG5          0x802001f8
#define HW_DMA1_SGR5          0x80200200
#define HW_DMA1_DSR5          0x80200208

#define HW_DMA1_SAR6          0x80200210
#define HW_DMA1_DAR6          0x80200218
#define HW_DMA1_LLP6          0x80200220
#define HW_DMA1_CTL6          0x80200228
#define HW_DMA1_SSTAT6        0x80200230
#define HW_DMA1_DSTAT6        0x80200238
#define HW_DMA1_SSTATAR6      0x80200240
#define HW_DMA1_DSTATAR6      0x80200248
#define HW_DMA1_CFG6          0x80200250
#define HW_DMA1_SGR6          0x80200258
#define HW_DMA1_DSR6          0x80200260

#define HW_DMA1_SAR7          0x80200268
#define HW_DMA1_DAR7          0x80200270
#define HW_DMA1_LLP7          0x80200278
#define HW_DMA1_CTL7          0x80200280
#define HW_DMA1_SSTAT7        0x80200288
#define HW_DMA1_DSTAT7        0x80200290
#define HW_DMA1_SSTATAR7      0x80200298
#define HW_DMA1_DSTATAR7      0x802002a0
#define HW_DMA1_CFG7          0x802002a8
#define HW_DMA1_SGR7          0x802002b0
#define HW_DMA1_DSR7          0x802002b8

#define HW_DMA1_RawTFR        0x802002c0
#define HW_DMA1_RawBLOCK      0x802002c8
#define HW_DMA1_RawSRCTRAN    0x802002d0
#define HW_DMA1_RawDSTTRAN    0x802002d8
#define HW_DMA1_RawERR        0x802002e0

#define HW_DMA1_StatusTFR     0x802002e8
#define HW_DMA1_StatusBLOCK   0x802002f0
#define HW_DMA1_StatusSRCTRAN 0x802002f8
#define HW_DMA1_StatusDSTTRAN 0x80200300
#define HW_DMA1_StatusERR     0x80200308

#define HW_DMA1_MaskTFR       0x80200310
#define HW_DMA1_MaskBLOCK     0x80200318
#define HW_DMA1_MaskSRCTRAN   0x80200320
#define HW_DMA1_MaskDSTTRAN   0x80200328
#define HW_DMA1_MaskERR       0x80200330

#define HW_DMA1_ClearTFR      0x80200338
#define HW_DMA1_ClearBLOCK    0x80200340
#define HW_DMA1_ClearSRCTRAN  0x80200348
#define HW_DMA1_ClearDSTTRAN  0x80200350
#define HW_DMA1_ClearERR      0x80200358

#define HW_DMA1_STATUSINT     0x80200360

#define HW_DMA1_ReqSrcReg     0x80200368
#define HW_DMA1_ReqDstReg     0x80200370
#define HW_DMA1_SglReqSrcReg  0x80200378
#define HW_DMA1_SglReqDstReg  0x80200380
#define HW_DMA1_LstSrcReg     0x80200388
#define HW_DMA1_LstDstReg     0x80200390

#define HW_DMA1_DMACFGREG     0x80200398
#define HW_DMA1_CHENREG       0x802003a0

////////////////////////////////////////////////////////////////////////////////
// ICOLL
#define HW_ICOLL_VECTOR       0x80054000
#define HW_ICOLL_LEVELACK     0x80054010
#define HW_ICOLL_CTRL         0x80054020
#define HW_ICOLL_STAT         0x80054030
#define HW_ICOLL_RAW0         0x80054040
#define HW_ICOLL_RAW1         0x80054050
#define HW_ICOLL_PRIORITY0    0x80054060
#define HW_ICOLL_PRIORITY1    0x80054070
#define HW_ICOLL_PRIORITY2    0x80054080
#define HW_ICOLL_PRIORITY3    0x80054090
#define HW_ICOLL_PRIORITY4    0x800540A0
#define HW_ICOLL_PRIORITY5    0x800540B0
#define HW_ICOLL_PRIORITY6    0x800540C0
#define HW_ICOLL_PRIORITY7    0x800540D0
#define HW_ICOLL_PRIORITY8    0x800540E0
#define HW_ICOLL_PRIORITY9    0x800540F0
#define HW_ICOLL_PRIORITY10   0x80054100
#define HW_ICOLL_PRIORITY11   0x80054110
#define HW_ICOLL_PRIORITY12   0x80054120
#define HW_ICOLL_PRIORITY13   0x80054130
#define HW_ICOLL_PRIORITY14   0x80054140
#define HW_ICOLL_PRIORITY15   0x80054150
#define HW_ICOLL_VBASE        0x80054160
#define HW_ICOLL_DEBUG        0x80054170
#define HW_ICOLL_DBGREAD0     0x80054180
#define HW_ICOLL_DBGREAD1     0x80054190
#define HW_ICOLL_DBGFLAG      0x800541A0
#define HW_ICOLL_DBGREQUEST0  0x800541B0
#define HW_ICOLL_DBGREQUEST1  0x800541C0
#define HW_ICOLL_CLEAR0       0x800541D0
#define HW_ICOLL_CLEAR1       0x800541E0
#define HW_ICOLL_UNDEF_VECTOR 0x800541F0

////////////////////////////////////////////////////////////////////////////////
// TIMER0
#define HW_TIMER0_IR          0x80088000
#define HW_TIMER0_TCR         0x80088010
#define HW_TIMER0_DIR         0x80088020
#define HW_TIMER0_TC0         0x80088030
#define HW_TIMER0_TC1         0x80088040
#define HW_TIMER0_TC2         0x80088050
#define HW_TIMER0_TC3         0x80088060
#define HW_TIMER0_PR          0x80088070
#define HW_TIMER0_PC          0x80088080
#define HW_TIMER0_MCR         0x80088090
#define HW_TIMER0_MR0         0x800880a0
#define HW_TIMER0_MR1         0x800880b0
#define HW_TIMER0_MR2         0x800880C0
#define HW_TIMER0_MR3         0x800880D0
#define HW_TIMER0_CCR         0x800880E0
#define HW_TIMER0_CR0         0x800880F0
#define HW_TIMER0_CR1         0x80088100
#define HW_TIMER0_CR2         0x80088110
#define HW_TIMER0_CR3         0x80088120
#define HW_TIMER0_EMR         0x80088130
#define HW_TIMER0_PWMTH0      0x80088140
#define HW_TIMER0_PWMTH1      0x80088150
#define HW_TIMER0_PWMTH2      0x80088160
#define HW_TIMER0_PWMTH3      0x80088170
#define HW_TIMER0_CTCR        0x80088180
#define HW_TIMER0_PWMC        0x80088190

////////////////////////////////////////////////////////////////////////////////
// USART

typedef struct {
  __IO unsigned long CTRL0[4];
  __IO unsigned long CTRL1[4];
  __IO unsigned long CTRL2[4];
  __IO unsigned long LINECTRL[4];
  __IO unsigned long INTR[4];
  __IO unsigned long DATA[4];
  __IO unsigned long STAT[4];
  __I  unsigned long DEBUG[4];
  __IO unsigned long ILPR[4];
  __IO unsigned long RS485CTRL[4];
  __IO unsigned long RS485ADRMATCH[4];
  __IO unsigned long RS485DLY[4];
  __IO unsigned long AUTOBAUD[4];
  __IO unsigned long CTRL3[4];
} ASM_USART_TypeDef;

#define UART0_BASE            0x80000000
#define UART1_BASE            0x80004000
#define UART2_BASE            0x80008000
#define UART3_BASE            0x8000C000
#define UART4_BASE            0x80010000
#define UART5_BASE            0x80014000
#define UART6_BASE            0x80018000
#define UART7_BASE            0x8001C000
#define UART8_BASE            0x80020000
#define UART9_BASE            0x80024000

////////////////////////////////////////////////////////////////////////////////
// MAC
#define HW_ETH_BASE_ADDR      0x80500000
#define HW_ETH_MACCR          (HW_ETH_BASE_ADDR + 0x0000)
#define HW_ETH_MACFFR         (HW_ETH_BASE_ADDR + 0x0004)
#define HW_ETH_MACHTHR        (HW_ETH_BASE_ADDR + 0x0008)
#define HW_ETH_MACHTLR        (HW_ETH_BASE_ADDR + 0x000C)
#define HW_ETH_MACMIIAR       (HW_ETH_BASE_ADDR + 0x0010)
#define HW_ETH_MACMIIDR       (HW_ETH_BASE_ADDR + 0x0014)
#define HW_ETH_MACFCR         (HW_ETH_BASE_ADDR + 0x0018)
#define HW_ETH_MACVLANTR      (HW_ETH_BASE_ADDR + 0x001C)
#define HW_ETH_MACVR          (HW_ETH_BASE_ADDR + 0x0020)
#define HW_ETH_MACRWUFFR      (HW_ETH_BASE_ADDR + 0x0028)
#define HW_ETH_MACPMTCSR      (HW_ETH_BASE_ADDR + 0x002C)
#define HW_ETH_MACDBGR        (HW_ETH_BASE_ADDR + 0x0034)
#define HW_ETH_MACISR         (HW_ETH_BASE_ADDR + 0x0038)
#define HW_ETH_MACIMR         (HW_ETH_BASE_ADDR + 0x003C)
#define HW_ETH_MACA0HR        (HW_ETH_BASE_ADDR + 0x0040)
#define HW_ETH_MACA0LR        (HW_ETH_BASE_ADDR + 0x0044)
#define HW_ETH_MACA1HR        (HW_ETH_BASE_ADDR + 0x0048)
#define HW_ETH_MACA1LR        (HW_ETH_BASE_ADDR + 0x004C)
#define HW_ETH_MACA2HR        (HW_ETH_BASE_ADDR + 0x0050)
#define HW_ETH_MACA2LR        (HW_ETH_BASE_ADDR + 0x0054)
#define HW_ETH_MACA3HR        (HW_ETH_BASE_ADDR + 0x0058)
#define HW_ETH_MACA3LR        (HW_ETH_BASE_ADDR + 0x005C)
#define HW_ETH_MACA4HR        (HW_ETH_BASE_ADDR + 0x0060)
#define HW_ETH_MACA4LR        (HW_ETH_BASE_ADDR + 0x0064)
#define HW_ETH_MMCCR          (HW_ETH_BASE_ADDR + 0x0100)
#define HW_ETH_MMCRIR         (HW_ETH_BASE_ADDR + 0x0104)
#define HW_ETH_MMCTIR         (HW_ETH_BASE_ADDR + 0x0108)
#define HW_ETH_MMCRIMR        (HW_ETH_BASE_ADDR + 0x010C)
#define HW_ETH_MMCTIMR        (HW_ETH_BASE_ADDR + 0x0110)
#define HW_ETH_MMCTGFSCCR     (HW_ETH_BASE_ADDR + 0x014C)
#define HW_ETH_MMCTGFMSCCR    (HW_ETH_BASE_ADDR + 0x0150)
#define HW_ETH_MMCTGFCR       (HW_ETH_BASE_ADDR + 0x0168)
#define HW_ETH_MMCRFCECR      (HW_ETH_BASE_ADDR + 0x0194)
#define HW_ETH_MMCRFAECR      (HW_ETH_BASE_ADDR + 0x0198)
#define HW_ETH_MMCRGUFCR      (HW_ETH_BASE_ADDR + 0x01C4)
#define HW_ETH_PTPTSCR        (HW_ETH_BASE_ADDR + 0x0700)
#define HW_ETH_PTPSSIR        (HW_ETH_BASE_ADDR + 0x0704)
#define HW_ETH_PTPTSHR        (HW_ETH_BASE_ADDR + 0x0708)
#define HW_ETH_PTPTSLR        (HW_ETH_BASE_ADDR + 0x070C)
#define HW_ETH_PTPTSHUR       (HW_ETH_BASE_ADDR + 0x0710)
#define HW_ETH_PTPTSLUR       (HW_ETH_BASE_ADDR + 0x0714)
#define HW_ETH_PTPTSAR        (HW_ETH_BASE_ADDR + 0x0718)
#define HW_ETH_PTPTTHR        (HW_ETH_BASE_ADDR + 0x071C)
#define HW_ETH_PTPTTLR        (HW_ETH_BASE_ADDR + 0x0720)
#define HW_ETH_PTPTSSR        (HW_ETH_BASE_ADDR + 0x0728)
#define HW_ETH_PTPPPSCR       (HW_ETH_BASE_ADDR + 0x072C)
#define HW_ETH_DMABMR         (HW_ETH_BASE_ADDR + 0x1000)
#define HW_ETH_DMATPDR        (HW_ETH_BASE_ADDR + 0x1004)
#define HW_ETH_DMARPDR        (HW_ETH_BASE_ADDR + 0x1008)
#define HW_ETH_DMARDLAR       (HW_ETH_BASE_ADDR + 0x100C)
#define HW_ETH_DMATDLAR       (HW_ETH_BASE_ADDR + 0x1010)
#define HW_ETH_DMASR          (HW_ETH_BASE_ADDR + 0x1014)
#define HW_ETH_DMAOMR         (HW_ETH_BASE_ADDR + 0x1018)
#define HW_ETH_DMAIER         (HW_ETH_BASE_ADDR + 0x101C)
#define HW_ETH_DMAMFBOCR      (HW_ETH_BASE_ADDR + 0x1020)
#define HW_ETH_DMARSWTR       (HW_ETH_BASE_ADDR + 0x1024)
#define HW_ETH_DMACHTDR       (HW_ETH_BASE_ADDR + 0x1048)
#define HW_ETH_DMACHRDR       (HW_ETH_BASE_ADDR + 0x104C)
#define HW_ETH_DMACHTBAR      (HW_ETH_BASE_ADDR + 0x1050)
#define HW_ETH_DMACHRBAR      (HW_ETH_BASE_ADDR + 0x1054)

////////////////////////////////////////////////////////////////////////////////
#endif /* __ASM9260T_REGS_H__ */

