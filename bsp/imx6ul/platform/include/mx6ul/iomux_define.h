#ifndef _IOMUX_DEFINE_H_
#define _IOMUX_DEFINE_H_

#include "soc_memory_map.h"

// IOMUXC_SW_MUX_CTL_PAD_*
// SION
#define SION_DISABLED 0x0
#define SION_ENABLED  0x1
// MUX_MODE
#define ALT0 0x0
#define ALT1 0x1
#define ALT2 0x2
#define ALT3 0x3
#define ALT4 0x4
#define ALT5 0x5
#define ALT6 0x6
#define ALT7 0x7

// IOMUXC_SW_PAD_CTL_PAD_*
// IOMUXC_SW_PAD_CTL_GRP_*
// LVE
#define LVE_DISABLED 0x0
#define LVE_ENABLED  0x1
// HYS
#define HYS_DISABLED 0x0
#define HYS_ENABLED  0x1
// PUS
#define PUS_100KOHM_PD 0x0
#define PUS_47KOHM_PU  0x1
#define PUS_100KOHM_PU 0x2
#define PUS_22KOHM_PU  0x3
// PUE
#define PUE_KEEP 0x0
#define PUE_PULL 0x1
// PKE
#define PKE_DISABLED 0x0
#define PKE_ENABLED  0x1
// ODE
#define ODE_DISABLED 0x0
#define ODE_ENABLED  0x1
// SPEED
#define SPD_TBD    0x0
#define SPD_50MHZ  0x1
#define SPD_100MHZ 0x2
#define SPD_200MHZ 0x3
// DSE
#define DSE_DISABLED 0x0
#define DSE_240OHM   0x1
#define DSE_120OHM   0x2
#define DSE_80OHM    0x3
#define DSE_60OHM    0x4
#define DSE_48OHM    0x5
#define DSE_40OHM    0x6
#define DSE_34OHM    0x7
// SRE
#define SRE_SLOW 0x0
#define SRE_FAST 0x1
// ODT
#define ODT_OFF    0x0
#define ODT_120OHM 0x1
#define ODT_60OHM  0x2
#define ODT_40OHM  0x3
#define ODT_30OHM  0x4
#define ODT_RES5   0x5
#define ODT_20OHM  0x6
#define ODT_RES7   0x7
// DDR_INPUT
#define DDR_INPUT_CMOS 0x0
#define DDR_INPUT_DIFF 0x1
// DDR_SEL
#define DDR_SEL_LPDDR1_DDR3_DDR2_ODT 0x0
#define DDR_SEL_DDR2                 0x1
#define DDR_SEL_LPDDR2               0x2
#define DDR_SEL_RES0                 0x3
// DO_TRIM
#define DO_TRIM_RES0 0x0
#define DO_TRIM_RES1 0x1

#define MK_PAD(HYS, PUS, PUE, PKE, ODE, SPEED, DSE, SRE) ( \
		((HYS & 0x1) << 16) | \
		((PUS & 0x3) << 14) | \
		((PUE & 0x1) << 13) | \
		((PKE & 0x1) << 12) | \
		((ODE & 0x1) << 11) | \
		((SPEED & 0x3) << 6 ) | \
		((DSE & 0x7) << 3 ) | \
		((SRE & 0x1) << 0 ) )

#define PAD_ENET_INPUT	MK_PAD(1, 0, 0, 0, 0, 3, 5, 1)
#define PAD_ENET_OUTPUT	MK_PAD(0, 0, 0, 0, 0, 3, 5, 1)
#define PAD_ENET_CTRL	MK_PAD(0, 0, 0, 0, 0, 0, 3, 1)
#define PAD_GPIO_OUTPUT	MK_PAD(0, 0, 0, 0, 0, 0, 2, 0)
#define PAD_GPIO_INPUT	MK_PAD(0, 1, 1, 1, 0, 0, 2, 0)
#define PAD_UART_OUTPUT	MK_PAD(0, 0, 0, 0, 0, 0, 2, 0)
#define PAD_UART_INPUT	MK_PAD(0, 2, 0, 0, 0, 0, 2, 0)
#define PAD_I2C			MK_PAD(0, 2, 0, 0, 1, 0, 2, 0)
#define PAD_I2C4		MK_PAD(0, 2, 0, 0, 1, 0, 4, 0)
#define PAD_LCD_DATA	MK_PAD(0, 0, 0, 0, 0, 2, 3, 1)
#define PAD_AUDMUX		MK_PAD(0, 0, 0, 0, 0, 0, 5, 1)
#define PAD_CAN			MK_PAD(0, 0, 0, 0, 0, 0, 2, 0)
#define PAD_SDHC_DATA	MK_PAD(0, 1, 1, 1, 0, 2, 3, 1)
#define PAD_QSPI		MK_PAD(0, 0, 0, 0, 0, 3, 3, 1)
#define PAD_QSPI_PU		MK_PAD(0, 1, 1, 1, 0, 3, 3, 1)

#endif

