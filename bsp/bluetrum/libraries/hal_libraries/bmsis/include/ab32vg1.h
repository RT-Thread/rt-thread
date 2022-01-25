/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_H__
#define AB32VG1_H__

#ifndef __ASSEMBLER__
#include <stdint.h>
#include "system_ab32vgx.h"

/*!< Interrupt Number Definition */
typedef enum
{
    IRQ_SW_VECTOR                   = 2,
    IRQ_TMR0_VECTOR                 = 3,
    IRQ_TMR1_VECTOR                 = 4,
    IRQ_TMR2_4_5_VECTOR             = 5,    /*!< Timer 2, 4 and 5 Interrupt         */
    IRQ_IRRX_VECTOR                 = 6,    /*!< Timer 3 and IR receiver Interrupt  */
    IRQ_USB_VECTOR                  = 7,
    IRQ_SD_VECTOR                   = 8,
    IRQ_AUBUF0_1_VECTOR             = 9,    /*!< Audio buffer 0 and 1 Interrupt     */
    IRQ_SDADC_VECTOR                = 10,
    IRQ_AUDEC_VECTOR                = 11,   /*!< Audio codec, SBC encode and AEC FFT Interrupt */
    IRQ_SRC_VECTOR                  = 12,   /*!< SRC, PLC and CVSD Interrupt        */
    IRQ_FM_SPDIF_VECTOR             = 13,   /*!< FM TX, RX and SPDIF RX Interrupt   */
    IRQ_UART0_2_VECTOR              = 14,   /*!< UART 0 to 2 Interrupt              */
    IRQ_HSUART_VECTOR               = 15,
    IRQ_RTC_VECTOR                  = 16,   /*!< RTC, LVD and WDT Interrupt         */
    IRQ_I2S_VECTOR                  = 17,
    IRQ_TOTAL_NUM                   = 23,
} irq_type;
#endif // __ASSEMBLER__

#ifndef __ASSEMBLER__
#define SFR_RO *(volatile unsigned long const *)
#define SFR_WO *(volatile unsigned long*)
#define SFR_RW *(volatile unsigned long*)
#define SWINT() asm(".long 0xb0030057")
#define EEBREAKINT() asm(".long 0xb0040057")
#else
#define SFR_RO
#define SFR_WO
#define SFR_RW
#define SWINT      .long 0xb0030057
#define EEBREAKINT .long 0xb0040057
#endif

#define SFR_BASE   0x00000000
#define SFR0_BASE  (0x00000000 + 0x000)
#define SFR1_BASE  (0x00000000 + 0x100)
#define SFR2_BASE  (0x00000000 + 0x200)
#define SFR3_BASE  (0x00000000 + 0x300)
#define SFR4_BASE  (0x00000000 + 0x400)
#define SFR5_BASE  (0x00000000 + 0x500)
#define SFR6_BASE  (0x00000000 + 0x600)
#define SFR7_BASE  (0x00000000 + 0x700)
#define SFR8_BASE  (0x00000000 + 0x800)
#define SFR9_BASE  (0x00000000 + 0x900)
#define SFR10_BASE (0x00000000 + 0xa00)
#define SFR11_BASE (0x00000000 + 0xb00)
#define SFR12_BASE (0x00000000 + 0xc00)
#define SFR13_BASE (0x00000000 + 0xd00)
#define SFR14_BASE (0x00000000 + 0xe00)
#define SFR15_BASE (0x00000000 + 0xf00)

#define RTC_WR          0x200
#define RTC_RD          0x100

#define RTCCNT_CMD      0x01
#define RTCALM_CMD      0x02
#define RTCRAM_CMD      0x03
#define RTCCON0_CMD     0x04
#define RTCCON1_CMD     0x05
#define RTCCON2_CMD     0x06
#define RTCCON3_CMD     0x07
#define RTCCON4_CMD     0x08
#define RTCCON5_CMD     0x09
#define RTCCON6_CMD     0x0a
#define RTCCON7_CMD     0x0b
#define RTCCON8_CMD     0x0c
#define RTCCON9_CMD     0x0d
#define RTCCON10_CMD    0x0e

#define FUNCMCON0         SFR_RW (SFR0_BASE + 0x07*4)
#define FUNCMCON1         SFR_RW (SFR0_BASE + 0x08*4)
#define FUNCMCON2         SFR_RW (SFR0_BASE + 0x09*4)

#define UART0CON          SFR_RW (SFR0_BASE + 0x10*4)
#define UART0CPND         SFR_WO (SFR0_BASE + 0x11*4)
#define UART0BAUD         SFR_RW (SFR0_BASE + 0x12*4)
#define UART0DATA         SFR_RW (SFR0_BASE + 0x13*4)
#define TMR0CON           SFR_RW (SFR0_BASE + 0x14*4)
#define TMR0CPND          SFR_RW (SFR0_BASE + 0x15*4)
#define TMR0CNT           SFR_RW (SFR0_BASE + 0x16*4)
#define TMR0PR            SFR_RW (SFR0_BASE + 0x17*4)
#define CLKCON0           SFR_RW (SFR0_BASE + 0x19*4)
#define WDTCON            SFR_RW (SFR0_BASE + 0x1a*4)
#define RTCCON            SFR_RW (SFR0_BASE + 0x1b*4)
#define RTCDAT            SFR_RW (SFR0_BASE + 0x1c*4)
#define CLKCON1           SFR_RW (SFR0_BASE + 0x1d*4)
#define RTCCPND           SFR_WO (SFR0_BASE + 0x1e*4)

#define SD0CON            SFR_RW (SFR0_BASE + 0x20*4)
#define SD0CPND           SFR_WO (SFR0_BASE + 0x21*4)
#define SD0BAUD           SFR_RW (SFR0_BASE + 0x22*4)
#define SD0CMD            SFR_RW (SFR0_BASE + 0x23*4)
#define SD0ARG3           SFR_RW (SFR0_BASE + 0x24*4)
#define SD0ARG2           SFR_RW (SFR0_BASE + 0x25*4)
#define SD0ARG1           SFR_RW (SFR0_BASE + 0x26*4)
#define SD0ARG0           SFR_RW (SFR0_BASE + 0x27*4)
#define SD0DMAADR         SFR_RW (SFR0_BASE + 0x28*4)
#define SD0DMACNT         SFR_RW (SFR0_BASE + 0x29*4)
#define SPI0CON           SFR_RW (SFR0_BASE + 0x2a*4)
#define SPI0BUF           SFR_RW (SFR0_BASE + 0x2b*4)
#define SPI0BAUD          SFR_RW (SFR0_BASE + 0x2c*4)
#define SPI0CPND          SFR_RW (SFR0_BASE + 0x2d*4)
#define SPI0DMACNT        SFR_RW (SFR0_BASE + 0x2e*4)
#define SPI0DMAADR        SFR_RW (SFR0_BASE + 0x2f*4)

#define UART1CON          SFR_RW (SFR0_BASE + 0x30*4)
#define UART1CPND         SFR_WO (SFR0_BASE + 0x31*4)
#define UART1BAUD         SFR_RW (SFR0_BASE + 0x32*4)
#define UART1DATA         SFR_RW (SFR0_BASE + 0x33*4)
#define TMR1CON           SFR_RW (SFR0_BASE + 0x35*4)
#define TMR1CPND          SFR_RW (SFR0_BASE + 0x36*4)
#define TMR1CNT           SFR_RW (SFR0_BASE + 0x37*4)
#define TMR1PR            SFR_RW (SFR0_BASE + 0x38*4)
#define TMR2CON           SFR_RW (SFR0_BASE + 0x3a*4)
#define TMR2CPND          SFR_RW (SFR0_BASE + 0x3b*4)
#define TMR2CNT           SFR_RW (SFR0_BASE + 0x3c*4)
#define TMR2PR            SFR_RW (SFR0_BASE + 0x3d*4)

//------------------------- SFR Group1 ---------------------------------------//
#define AUBUFDATA       SFR_RW (SFR1_BASE + 0x01*4)
#define AUBUFCON        SFR_RW (SFR1_BASE + 0x02*4)
#define AUBUFSTARTADDR  SFR_RW (SFR1_BASE + 0x03*4)
#define AUBUFSIZE       SFR_RW (SFR1_BASE + 0x04*4)
#define AUBUFFIFOCNT    SFR_RW (SFR1_BASE + 0x05*4)
#define AUBUF1DATA      SFR_RW (SFR1_BASE + 0x06*4)
#define AUBUF1CON       SFR_RW (SFR1_BASE + 0x07*4)
#define AUBUF1STARTADDR SFR_RW (SFR1_BASE + 0x08*4)
#define AUBUF1SIZE      SFR_RW (SFR1_BASE + 0x09*4)
#define AUBUF1FIFOCNT   SFR_RW (SFR1_BASE + 0x0a*4)

#define DACDIGCON0      SFR_RW (SFR1_BASE + 0x10*4)
#define DACVOLCON       SFR_RW (SFR1_BASE + 0x11*4)
#define AU0LMIXCOEF     SFR_RW (SFR1_BASE + 0x12*4)
#define AU0RMIXCOEF     SFR_RW (SFR1_BASE + 0x13*4)
#define AU1LMIXCOEF     SFR_RW (SFR1_BASE + 0x14*4)
#define AU1RMIXCOEF     SFR_RW (SFR1_BASE + 0x15*4)

#define AUANGCON0       SFR_RW (SFR1_BASE + 0x3c*4)
#define AUANGCON1       SFR_RW (SFR1_BASE + 0x3d*4)
#define AUANGCON2       SFR_RW (SFR1_BASE + 0x3e*4)
#define AUANGCON3       SFR_RW (SFR1_BASE + 0x3f*4)

#define USBCON0         SFR_RW (SFR3_BASE + 0x00*4)
#define USBCON1         SFR_RW (SFR3_BASE + 0x01*4)
#define USBCON2         SFR_RW (SFR3_BASE + 0x02*4)

#define PWRCON0         SFR_RW (SFR3_BASE + 0x1d*4)
#define LVDCON          SFR_RW (SFR3_BASE + 0x1e*4)
#define CHAGCON         SFR_RW (SFR3_BASE + 0x1f*4)

#define PLL0DIV         SFR_RW (SFR3_BASE + 0x23*4)
#define PLL1DIV         SFR_RW (SFR3_BASE + 0x24*4)
#define PLL0CON         SFR_RW (SFR3_BASE + 0x26*4)
#define PLL1CON         SFR_RW (SFR3_BASE + 0x27*4)
#define PLL2CON         SFR_RW (SFR3_BASE + 0x28*4)
#define XO26MCON        SFR_RW (SFR3_BASE + 0x29*4)
#define CLKCON2         SFR_RW (SFR3_BASE + 0x2a*4)
#define CLKGAT0         SFR_RW (SFR3_BASE + 0x2c*4)
#define LPMCON          SFR_RW (SFR3_BASE + 0x2d*4)
#define MEMCON          SFR_RW (SFR3_BASE + 0x2e*4)
#define CLKCON3         SFR_RW (SFR3_BASE + 0x2f*4)
#define CLKGAT1         SFR_RW (SFR3_BASE + 0x3f*4)

#define PWMCON          SFR_RW (SFR4_BASE + 0x20*4)
#define PWMPRCON        SFR_RW (SFR4_BASE + 0x21*4)
#define PWM01DUTY       SFR_RW (SFR4_BASE + 0x22*4)
#define PWM23DUTY       SFR_RW (SFR4_BASE + 0x23*4)
#define PWMCYCNUM       SFR_RW (SFR4_BASE + 0x24*4)
#define PWMSTEP         SFR_RW (SFR4_BASE + 0x25*4)

//0x00~0x1f reserve for CPU
#define PICCONCLR       SFR_WO (SFR5_BASE + 0x0c*4)
#define PICCONSET       SFR_WO (SFR5_BASE + 0x0d*4)
#define PICENCLR        SFR_WO (SFR5_BASE + 0x0e*4)
#define PICENSET        SFR_WO (SFR5_BASE + 0x0f*4)

#define PICCON          SFR_RW (SFR5_BASE + 0x10*4)
#define PICEN           SFR_RW (SFR5_BASE + 0x11*4)
#define PICPR           SFR_RW (SFR5_BASE + 0x12*4)
#define PICADR          SFR_RW (SFR5_BASE + 0x13*4)
#define PICPND          SFR_RW (SFR5_BASE + 0x14*4)
#define EPICCON         SFR_RW (SFR5_BASE + 0x1e*4)
#define EPC             SFR_RW (SFR5_BASE + 0x1f*4)

#define SADCDAT0        SFR_RO (SFR5_BASE + 0x20*4)
#define SADCDAT1        SFR_RO (SFR5_BASE + 0x21*4)
#define SADCDAT2        SFR_RO (SFR5_BASE + 0x22*4)
#define SADCDAT3        SFR_RO (SFR5_BASE + 0x23*4)
#define SADCDAT4        SFR_RO (SFR5_BASE + 0x24*4)
#define SADCDAT5        SFR_RO (SFR5_BASE + 0x25*4)
#define SADCDAT6        SFR_RO (SFR5_BASE + 0x26*4)
#define SADCDAT7        SFR_RO (SFR5_BASE + 0x27*4)
#define SADCDAT8        SFR_RO (SFR5_BASE + 0x28*4)
#define SADCDAT9        SFR_RO (SFR5_BASE + 0x29*4)
#define SADCDAT10       SFR_RO (SFR5_BASE + 0x2a*4)
#define SADCDAT11       SFR_RO (SFR5_BASE + 0x2b*4)
#define SADCDAT12       SFR_RO (SFR5_BASE + 0x2c*4)
#define SADCDAT13       SFR_RO (SFR5_BASE + 0x2d*4)
#define SADCDAT14       SFR_RO (SFR5_BASE + 0x2e*4)
#define SADCDAT15       SFR_RO (SFR5_BASE + 0x2f*4)

#define AUANGCON1       SFR_RW (SFR1_BASE + 0x3d*4)

#define WKUPCON         SFR_WO (SFR5_BASE + 0x39*4)
#define WKUPEDG         SFR_WO (SFR5_BASE + 0x3a*4)
#define WKUPCPND        SFR_WO (SFR5_BASE + 0x3b*4)

//------------------------- SFR Group6 ---------------------------------------//
#define GPIOASET        SFR_RW (SFR6_BASE + 0x00*4)
#define GPIOACLR        SFR_RW (SFR6_BASE + 0x01*4)
#define GPIOA           SFR_RW (SFR6_BASE + 0x02*4)
#define GPIOADIR        SFR_RW (SFR6_BASE + 0x03*4)
#define GPIOADE         SFR_RW (SFR6_BASE + 0x04*4)
#define GPIOAFEN        SFR_RW (SFR6_BASE + 0x05*4)
#define GPIOADRV        SFR_RW (SFR6_BASE + 0x06*4)
#define GPIOAPU         SFR_RW (SFR6_BASE + 0x07*4)
#define GPIOAPD         SFR_RW (SFR6_BASE + 0x08*4)
#define GPIOAPU200K     SFR_RW (SFR6_BASE + 0x09*4)
#define GPIOAPD200K     SFR_RW (SFR6_BASE + 0x0a*4)
#define GPIOAPU300      SFR_RW (SFR6_BASE + 0x0b*4)
#define GPIOAPD300      SFR_RW (SFR6_BASE + 0x0c*4)

#define GPIOBSET        SFR_RW (SFR6_BASE + 0x10*4)
#define GPIOBCLR        SFR_RW (SFR6_BASE + 0x11*4)
#define GPIOB           SFR_RW (SFR6_BASE + 0x12*4)
#define GPIOBDIR        SFR_RW (SFR6_BASE + 0x13*4)
#define GPIOBDE         SFR_RW (SFR6_BASE + 0x14*4)
#define GPIOBFEN        SFR_RW (SFR6_BASE + 0x15*4)
#define GPIOBDRV        SFR_RW (SFR6_BASE + 0x16*4)
#define GPIOBPU         SFR_RW (SFR6_BASE + 0x17*4)
#define GPIOBPD         SFR_RW (SFR6_BASE + 0x18*4)
#define GPIOBPU200K     SFR_RW (SFR6_BASE + 0x19*4)
#define GPIOBPD200K     SFR_RW (SFR6_BASE + 0x1a*4)
#define GPIOBPU300      SFR_RW (SFR6_BASE + 0x1b*4)
#define GPIOBPD300      SFR_RW (SFR6_BASE + 0x1c*4)

#define GPIOESET        SFR_RW (SFR6_BASE + 0x20*4)
#define GPIOECLR        SFR_RW (SFR6_BASE + 0x21*4)
#define GPIOE           SFR_RW (SFR6_BASE + 0x22*4)
#define GPIOEDIR        SFR_RW (SFR6_BASE + 0x23*4)
#define GPIOEDE         SFR_RW (SFR6_BASE + 0x24*4)
#define GPIOEFEN        SFR_RW (SFR6_BASE + 0x25*4)
#define GPIOEDRV        SFR_RW (SFR6_BASE + 0x26*4)
#define GPIOEPU         SFR_RW (SFR6_BASE + 0x27*4)
#define GPIOEPD         SFR_RW (SFR6_BASE + 0x28*4)
#define GPIOEPU200K     SFR_RW (SFR6_BASE + 0x29*4)
#define GPIOEPD200K     SFR_RW (SFR6_BASE + 0x2a*4)
#define GPIOEPU300      SFR_RW (SFR6_BASE + 0x2b*4)
#define GPIOEPD300      SFR_RW (SFR6_BASE + 0x2c*4)

#define GPIOFSET        SFR_RW (SFR6_BASE + 0x30*4)
#define GPIOFCLR        SFR_RW (SFR6_BASE + 0x31*4)
#define GPIOF           SFR_RW (SFR6_BASE + 0x32*4)
#define GPIOFDIR        SFR_RW (SFR6_BASE + 0x33*4)
#define GPIOFDE         SFR_RW (SFR6_BASE + 0x34*4)
#define GPIOFFEN        SFR_RW (SFR6_BASE + 0x35*4)
#define GPIOFDRV        SFR_RW (SFR6_BASE + 0x36*4)
#define GPIOFPU         SFR_RW (SFR6_BASE + 0x37*4)
#define GPIOFPD         SFR_RW (SFR6_BASE + 0x38*4)
#define GPIOFPU200K     SFR_RW (SFR6_BASE + 0x39*4)
#define GPIOFPD200K     SFR_RW (SFR6_BASE + 0x3a*4)
#define GPIOFPU300      SFR_RW (SFR6_BASE + 0x3b*4)
#define GPIOFPD300      SFR_RW (SFR6_BASE + 0x3c*4)

#define GPIOGSET        SFR_RW (SFR7_BASE + 0x00*4)
#define GPIOGCLR        SFR_RW (SFR7_BASE + 0x01*4)
#define GPIOG           SFR_RW (SFR7_BASE + 0x02*4)
#define GPIOGDIR        SFR_RW (SFR7_BASE + 0x03*4)
#define GPIOGDE         SFR_RW (SFR7_BASE + 0x04*4)
#define GPIOGFEN        SFR_RW (SFR7_BASE + 0x05*4)
#define GPIOGDRV        SFR_RW (SFR7_BASE + 0x06*4)
#define GPIOGPU         SFR_RW (SFR7_BASE + 0x07*4)
#define GPIOGPD         SFR_RW (SFR7_BASE + 0x08*4)
#define GPIOGPU200K     SFR_RW (SFR7_BASE + 0x09*4)
#define GPIOGPD200K     SFR_RW (SFR7_BASE + 0x0a*4)
#define GPIOGPU300      SFR_RW (SFR7_BASE + 0x0b*4)
#define GPIOGPD300      SFR_RW (SFR7_BASE + 0x0c*4)

#define IRRXCON         SFR_RW (SFR8_BASE + 0x1b*4)
#define IRRXDAT         SFR_RW (SFR8_BASE + 0x1c*4)
#define IRRXCPND        SFR_WO (SFR8_BASE + 0x1d*4)
#define IRRXERR0        SFR_WO (SFR8_BASE + 0x1e*4)
#define IRRXERR1        SFR_WO (SFR8_BASE + 0x1f*4)

#define USERKEY         SFR_RW (SFR8_BASE + 0x20*4)
#define PROTCON1        SFR_RW (SFR8_BASE + 0x21*4)
#define FMAMFDTCON      SFR_WO (SFR8_BASE + 0x29*4)

#define TMR3CON         SFR_RW (SFR9_BASE + 0x00*4)
#define TMR3CPND        SFR_WO (SFR9_BASE + 0x01*4)
#define TMR3CNT         SFR_RW (SFR9_BASE + 0x02*4)
#define TMR3PR          SFR_RW (SFR9_BASE + 0x03*4)
#define TMR3CPT         SFR_RO (SFR9_BASE + 0x04*4)
#define TMR3DUTY0       SFR_WO (SFR9_BASE + 0x05*4)
#define TMR3DUTY1       SFR_WO (SFR9_BASE + 0x06*4)
#define TMR3DUTY2       SFR_WO (SFR9_BASE + 0x07*4)
#define TMR4CON         SFR_RW (SFR9_BASE + 0x08*4)
#define TMR4CPND        SFR_WO (SFR9_BASE + 0x09*4)
#define TMR4CNT         SFR_RW (SFR9_BASE + 0x0a*4)
#define TMR4PR          SFR_RW (SFR9_BASE + 0x0b*4)
#define TMR4CPT         SFR_RO (SFR9_BASE + 0x0c*4)
#define TMR4DUTY0       SFR_WO (SFR9_BASE + 0x0d*4)
#define TMR4DUTY1       SFR_WO (SFR9_BASE + 0x0e*4)
#define TMR4DUTY2       SFR_WO (SFR9_BASE + 0x0f*4)

#define TMR5CON         SFR_RW (SFR9_BASE + 0x10*4)
#define TMR5CPND        SFR_WO (SFR9_BASE + 0x11*4)
#define TMR5CNT         SFR_RW (SFR9_BASE + 0x12*4)
#define TMR5PR          SFR_RW (SFR9_BASE + 0x13*4)
#define TMR5CPT         SFR_RO (SFR9_BASE + 0x14*4)
#define TMR5DUTY0       SFR_WO (SFR9_BASE + 0x15*4)
#define TMR5DUTY1       SFR_WO (SFR9_BASE + 0x16*4)
#define TMR5DUTY2       SFR_WO (SFR9_BASE + 0x17*4)
#define UART2CON        SFR_RW (SFR9_BASE + 0x18*4)
#define UART2CPND       SFR_WO (SFR9_BASE + 0x19*4)
#define UART2BAUD       SFR_RW (SFR9_BASE + 0x1a*4)
#define UART2DATA       SFR_RW (SFR9_BASE + 0x1b*4)
#define PORTINTEDG      SFR_RW (SFR9_BASE + 0x1e*4)
#define PORTINTEN       SFR_RW (SFR9_BASE + 0x1f*4)

#define SPI1CON         SFR_RW (SFR9_BASE + 0x20*4)
#define SPI1BUF         SFR_RW (SFR9_BASE + 0x21*4)
#define SPI1BAUD        SFR_RW (SFR9_BASE + 0x22*4)
#define SPI1CPND        SFR_RW (SFR9_BASE + 0x23*4)
#define SPI1DMACNT      SFR_RW (SFR9_BASE + 0x24*4)
#define SPI1DMAADR      SFR_RW (SFR9_BASE + 0x25*4)

#endif
