/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-09-21     rcitach           INITIAL VERSION
 */


#ifndef __RA6W1_PIN_EXT_H__
#define __RA6W1_PIN_EXT_H__

#ifdef EXTRA_IO_INCLUDE
#define RA6W1_PIN_INCLUDE_FILE_(name) <name>
#define RA6W1_PIN_INCLUDE_FILE(name)  RA6W1_PIN_INCLUDE_FILE_(name)
#include RA6W1_PIN_INCLUDE_FILE(EXTRA_IO_INCLUDE)
#undef RA6W1_PIN_INCLUDE_FILE
#undef RA6W1_PIN_INCLUDE_FILE_
#endif

#ifndef RA6W1_PIN_CFG_EXTRA
#define RA6W1_PIN_CFG_EXTRA
#endif

#ifndef RA6W1_PIN_NAME_EXTRA
#define RA6W1_PIN_NAME_EXTRA
#endif

#ifndef RA6W1_PIN_COUNT_EXTRA
#define RA6W1_PIN_COUNT_EXTRA 0
#endif

#endif /* __RA6W1_PIN_EXT_H__ */
