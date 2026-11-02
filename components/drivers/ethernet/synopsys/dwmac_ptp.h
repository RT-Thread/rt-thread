/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __DWMAC_PTP_H__
#define __DWMAC_PTP_H__

#include "dwmac.h"

#define DWMAC_PTP_OFFSET                0xb00

#define PTP_TCR                         0x00
#define PTP_SSIR                        0x04
#define PTP_STSR                        0x08
#define PTP_STNSR                       0x0c
#define PTP_STSUR                       0x10
#define PTP_STNSUR                      0x14
#define PTP_TAR                         0x18
#define PTP_ACR                         0x40

#define PTP_ACR_ATSFC                   RT_BIT(0)
#define PTP_ACR_ATSEN0                  RT_BIT(4)
#define PTP_ACR_ATSEN(i)                RT_BIT(4 + (i))

#define MAC_PPS_CONTROL                 0xb70
#define MAC_PPSx_TARGET_TIME_SEC(x)     (0xb80 + ((x) * 0x10))
#define MAC_PPSx_TARGET_TIME_NSEC(x)    (0xb84 + ((x) * 0x10))
#define MAC_PPSx_INTERVAL(x)            (0xb88 + ((x) * 0x10))
#define MAC_PPSx_WIDTH(x)               (0xb8c + ((x) * 0x10))

#define PPSEN0                          RT_BIT(4)
#define TRGTBUSY0                       RT_BIT(31)

#define PPS_MAXIDX(x)                   ((((x) + 1) * 8) - 1)
#define PPS_MINIDX(x)                   ((x) * 8)
#define PPSx_MASK(x)                    RT_GENMASK(PPS_MAXIDX(x), PPS_MINIDX(x))
#define PPSCMDx(x, val)                 (RT_GENMASK(PPS_MINIDX(x) + 3, PPS_MINIDX(x)) & \
                                         ((val) << PPS_MINIDX(x)))
#define TRGTMODSELx(x, val)             (RT_GENMASK(PPS_MAXIDX(x) - 1, PPS_MAXIDX(x) - 2) & \
                                         ((val) << (PPS_MAXIDX(x) - 2)))

#define dwmac_reg_readl(eth, reg)       HWREG32((rt_uint8_t *)(eth)->mac_base + (reg))
#define dwmac_reg_writel(eth, reg, val) HWREG32((rt_uint8_t *)(eth)->mac_base + (reg)) = (val)

#define GMAC_HW_FEATURE1                0x120
#define GMAC_HW_FEATURE2                0x124
#define GMAC_HW_FEAT_PPSOUTNUM_MASK     RT_GENMASK(26, 24)
#define GMAC_HW_FEAT_AUXSNAPNUM_MASK    RT_GENMASK(30, 28)

#define PTP_TCR_TSENA                   RT_BIT(0)
#define PTP_TCR_TSCFUPDT                RT_BIT(1)
#define PTP_TCR_TSINIT                  RT_BIT(2)
#define PTP_TCR_TSUPDT                  RT_BIT(3)
#define PTP_TCR_TSADDREG                RT_BIT(5)
#define PTP_TCR_TSCTRLSSR               RT_BIT(9)

#define PTP_STNSUR_ADDSUB_SHIFT         31
#define PTP_DIGITAL_ROLLOVER_MODE       0x3b9aca00
#define PTP_SSIR_SSINC_MAX              0xff
#define GMAC4_PTP_SSIR_SSINC_SHIFT      16

#define DWMAC_PTP_HWTS_ACTIVE           (PTP_TCR_TSENA | PTP_TCR_TSCFUPDT | PTP_TCR_TSCTRLSSR)

#define dwmac_ptp_readl(eth, reg)       HWREG32((rt_uint8_t *)(eth)->mac_base + DWMAC_PTP_OFFSET + (reg))
#define dwmac_ptp_writel(eth, reg, val) HWREG32((rt_uint8_t *)(eth)->mac_base + DWMAC_PTP_OFFSET + (reg)) = (val)

#ifdef RT_ETHERNET_DWMAC_PTP
#define raw_to_dwmac_ptp(raw)           rt_container_of(raw, struct dwmac_eth, ptp_parent)

rt_err_t dwmac_ptp_hw_init(struct dwmac_eth *eth);
rt_err_t dwmac_ptp_register(struct dwmac_eth *eth);
void dwmac_ptp_unregister(struct dwmac_eth *eth);
#endif /* RT_ETHERNET_DWMAC_PTP */

#endif /* __DWMAC_PTP_H__ */
