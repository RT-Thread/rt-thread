/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ENET_PHY_COMMON_H
#define HPM_ENET_PHY_COMMON_H

#if defined(__USE_DP83867) && __USE_DP83867
    #include "hpm_dp83867.h"
    #include "hpm_dp83867_regs.h"
#elif defined(__USE_RTL8211) && __USE_RTL8211
    #include "hpm_rtl8211.h"
    #include "hpm_rtl8211_regs.h"
#elif defined(__USE_DP83848) && __USE_DP83848
    #include "hpm_dp83848.h"
    #include "hpm_dp83848_regs.h"
#elif defined(__USE_RTL8201) && __USE_RTL8201
    #include "hpm_rtl8201.h"
    #include "hpm_rtl8201_regs.h"
#else
    #error no specified Ethernet PHY !!!
#endif

#endif /* HPM_ENET_PHY_H */
