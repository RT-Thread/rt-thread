/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2014
 *                         All Rights Reserved.
 *
 ****************************************************************************/

#ifndef __AE210P_H__
#define __AE210P_H__

#ifndef __ASSEMBLER__
#include <inttypes.h>
#include <nds32_intrinsic.h>
#endif

/*****************************************************************************
 * System clock
 ****************************************************************************/
#define KHz                     1000
#define MHz                     1000000

#define MB_OSCCLK               (20 * MHz)
#define MB_CPUCLK               (40 * MHz)
#define MB_HCLK                 (MB_CPUCLK)
#define MB_PCLK                 (MB_CPUCLK)
#define MB_UCLK                 (MB_OSCCLK)

/*****************************************************************************
 * IRQ Vector
 ****************************************************************************/
#define IRQ_RTCPERIOD_VECTOR    0
#define IRQ_RTCALARM_VECTOR     1
#define IRQ_PIT_VECTOR          2
#define IRQ_SPI1_VECTOR         3
#define IRQ_SPI2_VECTOR         4
#define IRQ_I2C_VECTOR          5
#define IRQ_GPIO_VECTOR         6
#define IRQ_UART1_VECTOR        7
#define IRQ_UATR2_VECTOR        8
#define IRQ_DMA_VECTOR          9
#define IRQ_BMC_VECTOR          10
#define IRQ_SWI_VECTOR          11

/* EXT_INT_0~19 are reserved for vendor IPs */
#define IRQ_EXTINT0_VECTOR      12
#define IRQ_EXTINT1_VECTOR      13
#define IRQ_EXTINT2_VECTOR      14
#define IRQ_EXTINT3_VECTOR      15
#define IRQ_EXTINT4_VECTOR      16
#define IRQ_EXTINT5_VECTOR      17
#define IRQ_EXTINT6_VECTOR      18
#define IRQ_EXTINT7_VECTOR      19
#define IRQ_EXTINT8_VECTOR      20
#define IRQ_EXTINT9_VECTOR      21
#define IRQ_EXTINT10_VECTOR     22
#define IRQ_EXTINT11_VECTOR     23
#define IRQ_EXTINT12_VECTOR     24
#define IRQ_EXTINT13_VECTOR     25
#define IRQ_EXTINT14_VECTOR     26
#define IRQ_EXTINT15_VECTOR     27
#define IRQ_EXTINT16_VECTOR     28
#define IRQ_EXTINT17_VECTOR     29
#define IRQ_EXTINT18_VECTOR     30
#define IRQ_EXTINT19_VECTOR     31

/* The system tick IRQ for OS */
#define IRQ_SYS_TICK_VECTOR     IRQ_PIT_VECTOR
#define IRQ_SYS_TICK2_VECTOR    IRQ_PIT_VECTOR

/* Include ae210p memory mapping and register definition */
#include "ae210p_defs.h"
#include "ae210p_regs.h"

#endif	/* __AE210P_H__ */
