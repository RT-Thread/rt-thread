/*!
*******************************************************************************
**
** \file      gh_vic.h
**
** \brief     VIC.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_VIC_H
#define _GH_VIC_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_VIC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VIC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VIC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VIC_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VIC_IRQSTS                                      FIO_ADDRESS(VIC,0x90003030) /* read */
#define REG_VIC_FIQSTS                                      FIO_ADDRESS(VIC,0x90003034) /* read */
#define REG_VIC_RAWSTS                                      FIO_ADDRESS(VIC,0x90003018) /* read */
#define REG_VIC_SELECT                                      FIO_ADDRESS(VIC,0x9000300C) /* read/write */
#define REG_VIC_ENABLE                                      FIO_ADDRESS(VIC,0x90003010) /* read/write */
#define REG_VIC_ENCLR                                       FIO_ADDRESS(VIC,0x90003014) /* write */
#define REG_VIC_SOFTINT                                     FIO_ADDRESS(VIC,0x9000301C) /* read/write */
#define REG_VIC_SOFTINTRCLR                                 FIO_ADDRESS(VIC,0x90003020) /* write */
#define REG_VIC_PROTECT                                     FIO_ADDRESS(VIC,0x90003024) /* read/write */
#define REG_VIC_SENSE                                       FIO_ADDRESS(VIC,0x90003000) /* read/write */
#define REG_VIC_BOTHEDGE                                    FIO_ADDRESS(VIC,0x90003008) /* read/write */
#define REG_VIC_EVENT                                       FIO_ADDRESS(VIC,0x90003004) /* read/write */
#define REG_VIC_EDGECLR                                     FIO_ADDRESS(VIC,0x90003038) /* write */

/*!
*******************************************************************************
**
** \brief Interrupt vectors
**
** The list below describes all available interrupt sources,
** a table containing the real interrupt service routines.
** All other interrupts are maskable and the priority can be set
** either to medium (1) or low (2).
**
******************************************************************************/
enum
{
    GH_INT_SSI_SLAVE_IRQ        = 0,  //!<
    GH_INT_ETH_IRQ              = 1,  //!< level, Ethernet 1
    GH_INT_IDSP_ERROR_IRQ       = 2,  //!< edge, iDSP error
    GH_INT_RESERVED1_03_IRQ     = 3,  //!<
    GH_INT_RESERVED1_04_IRQ     = 4,  //!<
    GH_INT_RESERVED1_05_IRQ     = 5,  //!<
    GH_INT_RESERVED1_06_IRQ     = 6,  //!<
    GH_INT_CODING_ORC_VOUT1_IRQ = 7,  //!<
    GH_INT_SD_CONTROLLER_IRQ    = 8,  //!< level, SD controller
    GH_INT_IDC_IRQ              = 9,  //!< level, i2c read/write, I2C0
    GH_INT_SSI_SPI_IRQ          = 10,  //!< level, Synchronous Serial Interface (SSI, SPI)
    GH_INT_WDT_IRQ              = 11,  //!< edge, Watchdog (WDT)
    GH_INT_IRIF_IRQ             = 12,  //!<
    GH_INT_RESERVED1_13_IRQ     = 13,  //!<
    GH_INT_SD_CARD_DETECT_IRQ   = 14,  //!< Both edges, SD card detect (state of SMIO5 pin)
    GH_INT_UART1_IRQ            = 15,  //!< level, uart read/write, UART1
    GH_INT_GPIO0_IRQ            = 16,  //!< level, GPIO0
    GH_INT_UART2_IRQ            = 17,  //!< level, uart read/write, UART1
    GH_INT_TIMER1_IRQ           = 18,  //!< edge, timer#1
    GH_INT_TIMER2_IRQ           = 19,  //!< edge, timer#2
    GH_INT_TIMER3_IRQ           = 20,  //!< edge, timer#3
    GH_INT_DMA_IRQ              = 21,  //!< level, DMA
    GH_INT_RESERVED1_22_IRQ     = 22,  //!<
    GH_INT_RESERVED1_23_IRQ     = 23,  //!<
    GH_INT_CODING_ORC_VIN_IRQ   = 24,  //!< edge, Coding Orc VIN
    GH_INT_CORDING_ORC_VDSP_IRQ = 25,  //!<
    GH_INT_USB_IRQ              = 26,  //!< level, USB
    GH_INT_RESERVED1_27_IRQ     = 27,  //!<
    GH_INT_XIU_TIMEOUT_IRQ      = 28,  //!<
    GH_INT_AUDIO_I2S_TX_IRQ     = 29,  //!< level, Audio (I2S) TX
    GH_INT_AUDIO_I2S_RX_IRQ     = 30,  //!< level, Audio (I2S) RX
    GH_INT_UART_IRQ             = 31,  //!< level, GPIO0
    GH_INT_RESERVED2_00_IRQ     = ( 0 + 32),  //!<
    GH_INT_RESERVED2_01_IRQ     = ( 1 + 32),  //!<
    GH_INT_RESERVED2_02_IRQ     = ( 2 + 32),  //!<
    GH_INT_RESERVED2_03_IRQ     = ( 3 + 32),  //!<
    GH_INT_RESERVED2_04_IRQ     = ( 4 + 32),  //!<
    GH_INT_RESERVED2_05_IRQ     = ( 5 + 32),  //!<
    GH_INT_RESERVED2_06_IRQ     = ( 6 + 32),  //!<
    GH_INT_RESERVED2_07_IRQ     = ( 7 + 32),  //!<
    GH_INT_AUDIO_PHY_RX_IRQ     = ( 8 + 32),  //!<
    GH_INT_AUDIO_PHY_TX_IRQ     = ( 9 + 32),  //!<
    GH_INT_RESERVED2_10_IRQ     = ( 10 + 32),  //!<
    GH_INT_RESERVED2_11_IRQ     = ( 11 + 32),  //!<
    GH_INT_RESERVED2_12_IRQ     = ( 12 + 32),  //!<
    GH_INT_RESERVED2_13_IRQ     = ( 13 + 32),  //!<
    GH_INT_RESERVED2_14_IRQ     = ( 14 + 32),  //!<
    GH_INT_RESERVED2_15_IRQ     = ( 15 + 32),  //!<
    GH_INT_RESERVED2_16_IRQ     = ( 16 + 32),  //!< edge, iDSP Vsync (VIN on master mode)
    GH_INT_RESERVED2_17_IRQ     = ( 17 + 32),  //!<
    GH_INT_CODING_ORC_VOUT0_IRQ = ( 18 + 32),  //!<
    GH_INT_AES_OUTPUT_READY_IRQ = ( 19 + 32),  //!< edge, AES output ready from Crypt block
    GH_INT_DES_OUTPUT_READY_IRQ = ( 20 + 32),  //!< edge, DES output ready from Crypt block
    GH_INT_RESERVED2_21_IRQ     = ( 21 + 32),  //!<
    GH_INT_GDMA_COMPLETION_IRQ  = ( 22 + 32),  //!<
    GH_INT_MOTOR_INTERRUPT_IRQ  = ( 23 + 32),  //!<
    GH_INT_ADC_LEVEL_CHANGE_IRQ = ( 24 + 32),  //!< level, ADC level change
    GH_INT_RESERVED2_25_IRQ     = ( 25 + 32),  //!<
    GH_INT_IDC2_IRQ             = ( 26 + 32),  //!< level, IDC2
    GH_INT_IDSP_LAST_PIXEL_IRQ  = ( 27 + 32),  //!< edge, iDSP last pixel
    GH_INT_IDSP_VSYNC_IRQ       = ( 28 + 32),  //!< edge, iDSP Vsync (VIN on master mode)
    GH_INT_IDSP_SENSOR_VSYNC_IRQ= ( 29 + 32),  //!< edge, iDSP sensor Vsync (VIN on slave mode)
    GH_INT_PMU_IRQ              = ( 30 + 32),  //!< level, PMU
    GH_INT_SSI2_IRQ             = ( 31 + 32),  //!< level, SSI2
};
/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VIC_Protect */
    U32 all;
    struct {
        U32 protect                     : 1;
        U32                             : 31;
    } bitc;
} GH_VIC_PROTECT_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U32                                     m_vic_enclr[2];
extern U32                                     m_vic_softintrclr[2];
extern U32                                     m_vic_edgeclr[2];

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VIC_IRQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIC_IRQSts'. */
U32  GH_VIC_get_IRQSts(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_FIQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIC_FIQSts'. */
U32  GH_VIC_get_FIQSts(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_RawSts (read)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIC_RawSts'. */
U32  GH_VIC_get_RawSts(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_Select (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_Select'. */
void GH_VIC_set_Select(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Select'. */
U32  GH_VIC_get_Select(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_Enable'. */
void GH_VIC_set_Enable(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Enable'. */
U32  GH_VIC_get_Enable(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_EnClr (write)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_EnClr'. */
void GH_VIC_set_EnClr(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VIC_EnClr'. */
U32  GH_VIC_getm_EnClr(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_SoftInt (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_SoftInt'. */
void GH_VIC_set_SoftInt(U8 index, U32 data);
/*! \brief Reads the register 'VIC_SoftInt'. */
U32  GH_VIC_get_SoftInt(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_SoftIntrClr (write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_SoftIntrClr'. */
void GH_VIC_set_SoftIntrClr(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VIC_SoftIntrClr'. */
U32  GH_VIC_getm_SoftIntrClr(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_Protect (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_Protect'. */
void GH_VIC_set_Protect(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Protect'. */
U32  GH_VIC_get_Protect(U8 index);
/*! \brief Writes the bit group 'Protect' of register 'VIC_Protect'. */
void GH_VIC_set_Protect_Protect(U8 index, U8 data);
/*! \brief Reads the bit group 'Protect' of register 'VIC_Protect'. */
U8   GH_VIC_get_Protect_Protect(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_Sense (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_Sense'. */
void GH_VIC_set_Sense(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Sense'. */
U32  GH_VIC_get_Sense(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_BothEdge (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_BothEdge'. */
void GH_VIC_set_BothEdge(U8 index, U32 data);
/*! \brief Reads the register 'VIC_BothEdge'. */
U32  GH_VIC_get_BothEdge(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_Event (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_Event'. */
void GH_VIC_set_Event(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Event'. */
U32  GH_VIC_get_Event(U8 index);

/*----------------------------------------------------------------------------*/
/* register VIC_EdgeClr (write)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIC_EdgeClr'. */
void GH_VIC_set_EdgeClr(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VIC_EdgeClr'. */
U32  GH_VIC_getm_EdgeClr(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VIC_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vic.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VIC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

