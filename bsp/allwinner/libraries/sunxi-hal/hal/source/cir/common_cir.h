/*
 * ===========================================================================================
 *
 *       Filename:  common_cir.h
 *
 *    Description:  IR HAL definition.
 *
 *        Version:  Melis3.0
 *         Create:  2021-01-15 11:11:56
 *       Revision:  none
 *       Compiler:  GCC:version 9.2.1
 *
 *         Author:  luruixiang@allwinnertech.com
 *   Organization:  SWC-BPD
 *  Last Modified:  2021-01-15 16:02:11
 *
 * ===========================================================================================
 */

#ifndef _CIRCOMMON_H_
#define _CIRCOMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Registers */
#define CIR_CTRL        (0x00)  /* IR Control */
#define CIR_RXCTRL      (0x10)  /* Rx Config */
#define CIR_RXFIFO      (0x20)  /* Rx Data */
#define CIR_RXINT       (0x2C)  /* Rx Interrupt Enable */
#define CIR_RXSTA       (0x30)  /* Rx Interrupt Status */
#define CIR_CONFIG      (0x34)  /* IR Sample Config */

/*CIR_CTRL*/
#define GEN_OFFSET      0
#define RXEN_OFFSET     1
#define CIR_ENABLE_OFFSET   4
#define CIR_MODE_OFFSET     6
/*global enable*/
#define GEN         (0x01 << GEN_OFFSET)
/*receiver block enable*/
#define RXEN            (0x01 << RXEN_OFFSET)
/*cir enable*/
#define CIR_ENABLE      (0x03 << CIR_ENABLE_OFFSET)
/*active pulse accept mode*/
#define CIR_MODE        (0x03 << CIR_MODE_OFFSET)

/*CIR_RXCTRL*/
#define RPPI_OFFSET     2
#define RPPI            (0x01 << RPPI_OFFSET)   /*receiver pulse polarity invert*/

/*CIR_RXINT*/
#define ROI_EN_OFFSET       0
#define PREI_EN_OFFSET      1
#define RAI_EN_OFFSET       4
#define DRQ_EN_OFFSET       5
#define RAL_OFFSET      8
/*receiver fifo overrun interrupt enable*/
#define ROI_EN          (0x01 << ROI_EN_OFFSET)
/*receiver packet end interrupt enable*/
#define PREI_EN         (0x01 << PREI_EN_OFFSET)
/*rx fifo available interrupt enable*/
#define RAI_EN          (0x01 << RAI_EN_OFFSET)
/*rx fifo dma enable*/
#define DRQ_EN          (0x01 << DRQ_EN_OFFSET)
/*rx fifo available received byte level*/
#define RAL         (0x3f << RAL_OFFSET)
#define IRQ_MASK        (0x3f)

/*CIR_RXSTA*/
#define ROI_OFFSET      0
#define RPE_OFFSET      1
#define RA_OFFSET       4
#define STAT_OFFSET     7
#define RAC_OFFSET      8
#define ROI         (0x01 << ROI_OFFSET)    /*receiver fifo overrun*/
#define RPE         (0x01 << RPE_OFFSET)    /*receiver packet end reg*/
#define RA          (0x01 << RA_OFFSET) /*rx fifo available*/
#define STAT            (0x01 << STAT_OFFSET)   /*status of cir, 0:idle, 1:busy*/
#define RAC         (0x7f << RAC_OFFSET)    /*rx fifo available counter*/

/*CIR_CONFIG*/
#define SCS_OFFSET      0
#define NTHR_OFFSET     2
#define ITHR_OFFSET     8
#define ATHR_OFFSET     16
#define ATHC_OFFSET     23
#define SCS2_OFFSET     24
#define SCS         (0x03 << SCS_OFFSET)    /*sample clk select for cir*/
#define NTHR            (0x3f << NTHR_OFFSET)   /*noise threshold for cir*/
#define ITHR            (0xff << ITHR_OFFSET)   /*idle threshold for cir*/
#define ATHR            (0x7f << ATHR_OFFSET)   /*active threshold for cir*/
#define ATHC            (0x01 << ATHC_OFFSET)   /*active threshold control for cir*/
#define SCS2            (0x01 << SCS2_OFFSET)   /*bit2 of sample clock select for cir*/

#define CIR_NOISE_THR_NEC   32
#define CIR_NOISE_THR_RC5   22

#ifdef __cplusplus
}
#endif

#endif
