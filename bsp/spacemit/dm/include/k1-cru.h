/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __K1_CLK_RST_H__
#define __K1_CLK_RST_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

/* APBS register offset */
/* PLL1 */
#define APB_SPARE1_REG                  0x100
#define APB_SPARE2_REG                  0x104
#define APB_SPARE3_REG                  0x108
/* PLL2 */
#define APB_SPARE7_REG                  0x118
#define APB_SPARE8_REG                  0x11c
#define APB_SPARE9_REG                  0x120
/* PLL3 */
#define APB_SPARE10_REG                 0x124
#define APB_SPARE11_REG                 0x128
#define APB_SPARE12_REG                 0x12c
/* end of APBS register offset */

/* APBC register offset */
#define APBC_UART1_CLK_RST              0x0
#define APBC_UART2_CLK_RST              0x4
#define APBC_GPIO_CLK_RST               0x8
#define APBC_PWM0_CLK_RST               0xc
#define APBC_PWM1_CLK_RST               0x10
#define APBC_PWM2_CLK_RST               0x14
#define APBC_PWM3_CLK_RST               0x18
#define APBC_TWSI8_CLK_RST              0x20
#define APBC_UART3_CLK_RST              0x24
#define APBC_RTC_CLK_RST                0x28
#define APBC_TWSI0_CLK_RST              0x2c
#define APBC_TWSI1_CLK_RST              0x30
#define APBC_TIMERS1_CLK_RST            0x34
#define APBC_TWSI2_CLK_RST              0x38
#define APBC_AIB_CLK_RST                0x3c
#define APBC_TWSI4_CLK_RST              0x40
#define APBC_TIMERS2_CLK_RST            0x44
#define APBC_ONEWIRE_CLK_RST            0x48
#define APBC_TWSI5_CLK_RST              0x4c
#define APBC_DRO_CLK_RST                0x58
#define APBC_IR_CLK_RST                 0x5c
#define APBC_TWSI6_CLK_RST              0x60
#define APBC_COUNTER_CLK_SEL            0x64
#define APBC_TWSI7_CLK_RST              0x68
#define APBC_TSEN_CLK_RST               0x6c

#define APBC_UART4_CLK_RST              0x70
#define APBC_UART5_CLK_RST              0x74
#define APBC_UART6_CLK_RST              0x78
#define APBC_SSP3_CLK_RST               0x7c

#define APBC_SSPA0_CLK_RST              0x80
#define APBC_SSPA1_CLK_RST              0x84

#define APBC_IPC_AP2AUD_CLK_RST         0x90
#define APBC_UART7_CLK_RST              0x94
#define APBC_UART8_CLK_RST              0x98
#define APBC_UART9_CLK_RST              0x9c

#define APBC_CAN0_CLK_RST               0xa0
#define APBC_PWM4_CLK_RST               0xa8
#define APBC_PWM5_CLK_RST               0xac
#define APBC_PWM6_CLK_RST               0xb0
#define APBC_PWM7_CLK_RST               0xb4
#define APBC_PWM8_CLK_RST               0xb8
#define APBC_PWM9_CLK_RST               0xbc
#define APBC_PWM10_CLK_RST              0xc0
#define APBC_PWM11_CLK_RST              0xc4
#define APBC_PWM12_CLK_RST              0xc8
#define APBC_PWM13_CLK_RST              0xcc
#define APBC_PWM14_CLK_RST              0xd0
#define APBC_PWM15_CLK_RST              0xd4
#define APBC_PWM16_CLK_RST              0xd8
#define APBC_PWM17_CLK_RST              0xdc
#define APBC_PWM18_CLK_RST              0xe0
#define APBC_PWM19_CLK_RST              0xe4
/* End of APBC register offset */

/* MPMU register offset */
#define MPMU_POSR                       0x10
#define POSR_PLL1_LOCK                  RT_BIT(27)
#define POSR_PLL2_LOCK                  RT_BIT(28)
#define POSR_PLL3_LOCK                  RT_BIT(29)

#define MPMU_VRCR                       0x18
#define MPMU_VRCR_REQ_EN0               RT_BIT(0)
#define MPMU_VRCR_REQ_EN2               RT_BIT(2)
#define MPMU_VRCR_REQ_POL2              RT_BIT(6)
#define MPMU_VRCR_VCXO_OUT_REQ_EN2      RT_BIT(14)

#define MPMU_WDTPCR                     0x200
#define MPMU_RIPCCR                     0x210
#define MPMU_ACGR                       0x1024
#define MPMU_SUCCR                      0x14
#define MPMU_ISCCR                      0x44
#define MPMU_SUCCR_1                    0x10b0
#define MPMU_APBCSCR                    0x1050

#define MPMU_PM_MN                      0x10a4
#define MPMU_PM_MN_GPCR2                0x48
#define MPMU_PM_MN_GPCR                 0x30
/* End of MPMU register offset */

/* APMU register offset */
#define APMU_JPG_CLK_RES_CTRL           0x20
#define APMU_CSI_CCIC2_CLK_RES_CTRL     0x24
#define APMU_ISP_CLK_RES_CTRL           0x38
#define APMU_LCD_CLK_RES_CTRL1          0x44
#define APMU_LCD_SPI_CLK_RES_CTRL       0x48
#define APMU_LCD_CLK_RES_CTRL2          0x4c
#define APMU_CCIC_CLK_RES_CTRL          0x50
#define APMU_SDH0_CLK_RES_CTRL          0x54
#define APMU_SDH1_CLK_RES_CTRL          0x58
#define APMU_USB_CLK_RES_CTRL           0x5c
#define APMU_QSPI_CLK_RES_CTRL          0x60
#define APMU_USB_CLK_RES_CTRL           0x5c
#define APMU_DMA_CLK_RES_CTRL           0x64
#define APMU_AES_CLK_RES_CTRL           0x68
#define APMU_VPU_CLK_RES_CTRL           0xa4
#define APMU_GPU_CLK_RES_CTRL           0xcc
#define APMU_SDH2_CLK_RES_CTRL          0xe0
#define APMU_PMUA_MC_CTRL               0xe8
#define APMU_PMU_CC2_AP                 0x100
#define APMU_PMUA_EM_CLK_RES_CTRL       0x104

#define APMU_AUDIO_CLK_RES_CTRL         0x14c
#define APMU_HDMI_CLK_RES_CTRL          0x1b8
#define APMU_CCI550_CLK_CTRL            0x300
#define APMU_ACLK_CLK_CTRL              0x388
#define APMU_CPU_C0_CLK_CTRL            0x38c
#define APMU_CPU_C1_CLK_CTRL            0x390

#define APMU_PCIE_CLK_RES_CTRL_0        0x3cc
#define APMU_PCIE_CLK_RES_CTRL_1        0x3d4
#define APMU_PCIE_CLK_RES_CTRL_2        0x3dc

#define APMU_EMAC0_CLK_RES_CTRL         0x3e4
#define APMU_EMAC1_CLK_RES_CTRL         0x3ec

#define APMU_DFC_AP                     0x180
#define APMU_DFC_STATUS                 0x188

#define APMU_DFC_LEVEL0                 0x190
#define APMU_DFC_LEVEL1                 0x194
#define APMU_DFC_LEVEL2                 0x198
#define APMU_DFC_LEVEL3                 0x19c
#define APMU_DFC_LEVEL4                 0x1a0
#define APMU_DFC_LEVEL5                 0x1a4
#define APMU_DFC_LEVEL6                 0x1a8
#define APMU_DFC_LEVEL7                 0x1ac

#define APMU_DPLL1_CLK_CTRL1            0x39c
#define APMU_DPLL1_CLK_CTRL2            0x3a0
#define APMU_DPLL2_CLK_CTRL1            0x3a8
#define APMU_DPLL2_CLK_CTRL2            0x3ac
/* End of APMU register offset */

/* APBC2 register offset */
#define APBC2_UART1_CLK_RST             0x00
#define APBC2_SSP2_CLK_RST              0x04
#define APBC2_TWSI3_CLK_RST             0x08
#define APBC2_RTC_CLK_RST               0x0c
#define APBC2_TIMERS0_CLK_RST           0x10
#define APBC2_KPC_CLK_RST               0x14
#define APBC2_GPIO_CLK_RST              0x1c
/* End of APBC2 register offset */

/* RCPU register offset */
#define RCPU_HDMI_CLK_RST               0x2044
#define RCPU_CAN_CLK_RST                0x4c
#define RCPU_I2C0_CLK_RST               0x30

#define RCPU_SSP0_CLK_RST               0x28
#define RCPU_IR_CLK_RST                 0x48
#define RCPU_UART0_CLK_RST              0xd8
#define RCPU_UART1_CLK_RST              0x3c
/* End of RCPU register offset */

/* RCPU2 register offset */
#define RCPU2_PWM0_CLK_RST              0x00
#define RCPU2_PWM1_CLK_RST              0x04
#define RCPU2_PWM2_CLK_RST              0x08
#define RCPU2_PWM3_CLK_RST              0x0c
#define RCPU2_PWM4_CLK_RST              0x10
#define RCPU2_PWM5_CLK_RST              0x14
#define RCPU2_PWM6_CLK_RST              0x18
#define RCPU2_PWM7_CLK_RST              0x1c
#define RCPU2_PWM8_CLK_RST              0x20
#define RCPU2_PWM9_CLK_RST              0x24
/* End of RCPU2 register offset */

/* AUDPMU register offset */
#define AUDPMU_AUDIO_BUS_CLK_CTRL       0x38
/* end of AUDPMU register offset */

enum cru_type
{
    CRU_BASE_TYPE_MPMU = 0,
    CRU_BASE_TYPE_APMU,
    CRU_BASE_TYPE_APBC,
    CRU_BASE_TYPE_APBS,
    CRU_BASE_TYPE_CIU,
    CRU_BASE_TYPE_DCIU,
    CRU_BASE_TYPE_DDRC,
    CRU_BASE_TYPE_APBC2,
    CRU_BASE_TYPE_RCPU,
    CRU_BASE_TYPE_RCPU2,
    CRU_BASE_TYPE_AUDPMU,
    CRU_BASE_TYPE_AUDC,
    CRU_BASE_TYPE_MAX,
};

#ifdef __CCU_H__
RT_DEFINE_SPINLOCK(k1_cru_lock);
#else
extern struct rt_spinlock k1_cru_lock;
#endif

#endif /* __K1_CLK_RST_H__ */
