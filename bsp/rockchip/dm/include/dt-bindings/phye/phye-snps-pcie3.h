/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_PHYE_SNPS_PCIE3_H__
#define __DT_BINDINGS_PHYE_SNPS_PCIE3_H__

/*
 * pcie30_phy_mode[2:0]
 * bit2: aggregation
 * bit1: bifurcation for port 1
 * bit0: bifurcation for port 0
 */
#define PHYE_MODE_PCIE_AGGREGATION 	4   /* PCIe3x4 */
#define PHYE_MODE_PCIE_NANBNB      	0   /* P1:PCIe3x2  +  P0:PCIe3x2 */
#define PHYE_MODE_PCIE_NANBBI      	1   /* P1:PCIe3x2  +  P0:PCIe3x1*2 */
#define PHYE_MODE_PCIE_NABINB      	2   /* P1:PCIe3x1*2 + P0:PCIe3x2 */
#define PHYE_MODE_PCIE_NABIBI      	3   /* P1:PCIe3x1*2 + P0:PCIe3x1*2 */

#endif /* __DT_BINDINGS_PHYE_SNPS_PCIE3_H__ */
