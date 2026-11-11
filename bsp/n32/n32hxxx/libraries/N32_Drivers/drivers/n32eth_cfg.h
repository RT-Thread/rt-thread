/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-16     ox-horse     first version
 */

#ifndef __N32ETH_CFG_H__
#define __N32ETH_CFG_H__

/*
 * The N32H7xx and N32H49x standard peripheral libraries ship an <soc>_eth.h
 * whose first statement is `#include "n32eth_cfg.h"`, but neither the driver
 * packages nor this repository carry that file - the vendor only ships it
 * inside their Ethernet demo projects.  The N32H47x_48x library is
 * self-contained (its eth.h pulls the device headers in directly), which is
 * why only the H7xx/H49x builds fail with
 * "n32eth_cfg.h: No such file or directory".
 *
 * Reproduce the baseline the SDK headers expect: the device definitions plus
 * the RCC/GPIO headers.  Exactly one series' headers are on the include path
 * in any given build, so probe for them instead of keying off SOC_SERIES_* -
 * the SDK's own <soc>_eth.c includes this header before rtconfig.h has had a
 * chance to define that macro.
 *
 * __has_include settles the probe under GCC and armclang, but ARM Compiler 5
 * does not have it - and every Keil project in this BSP is AC5 (<uAC6>0 in
 * all three).  There the whole block would be skipped and the includes
 * silently dropped, which is the very failure this file exists to prevent.
 * So fall back on the part macro: it is a compiler define rather than a
 * header, set before any file is read, and every board here passes its own -
 * N32H76x on h760, N32H49x on h497, N32H488 on h487 - from both its
 * SConscript and its uvprojx.  The lists are the family sets the SDK device
 * headers select on.
 */
#if defined(__has_include)
#if __has_include("n32h7xx.h")
#define N32ETH_CFG_SERIES_H7XX
#elif __has_include("n32h49x.h")
#define N32ETH_CFG_SERIES_H49X
#elif __has_include("n32h47x_48x.h")
#define N32ETH_CFG_SERIES_H47X_48X
#endif
#elif defined(N32H73x) || defined(N32H76x) || defined(N32H73x_76x) || defined(N32H78x)
#define N32ETH_CFG_SERIES_H7XX
#elif defined(N32H49x)
#define N32ETH_CFG_SERIES_H49X
#elif defined(N32H473) || defined(N32H474) || defined(N32H475) || defined(N32H480) || \
    defined(N32H481) || defined(N32H482) || defined(N32H487) || defined(N32H488)
#define N32ETH_CFG_SERIES_H47X_48X
#endif

#if defined(N32ETH_CFG_SERIES_H7XX)
#include "n32h7xx.h"
#include "n32h7xx_rcc.h"
#include "n32h7xx_gpio.h"
#elif defined(N32ETH_CFG_SERIES_H49X)
#include "n32h49x.h"
#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"
#elif defined(N32ETH_CFG_SERIES_H47X_48X)
#include "n32h47x_48x.h"
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_gpio.h"
#endif

#endif /* __N32ETH_CFG_H__ */
