/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _EMBARC_BSP_CONFIG_H_
#define _EMBARC_BSP_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BOARD_EMSK
/****************************************************************************
 * BSP Definitions
 ****************************************************************************/
/**
 *  Toolchain Definition for MetaWare or GNU
 */
//#define __MW__
#define __GNU__

/**
 *  Must be set.
 *  If changed, modify .lcf file for
 *  .stack ALIGN(4) SIZE(524288): {}
 *  .heap? ALIGN(4) SIZE(524288): {}
 */
#define _STACKSIZE      (4 * 1024)
#define _HEAPSZ         (32 * 1024)



#ifdef __cplusplus
}
#endif

#endif /* _EMBARC_CONFIG_BSP_H_ */
