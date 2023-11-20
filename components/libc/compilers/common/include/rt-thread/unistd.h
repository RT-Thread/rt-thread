/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/08     Bernard      Add macro definition for `#pragma once`
 */

#ifndef UNISTD_H__
#define UNISTD_H__

#include "sys/unistd.h"

#ifndef F_OK
#define	F_OK	0
#endif

#ifndef R_OK
#define	R_OK	4
#endif

#ifndef W_OK
#define	W_OK	2
#endif

#ifndef X_OK
#define	X_OK	1
#endif

#endif /* UNISTD_H__ */
