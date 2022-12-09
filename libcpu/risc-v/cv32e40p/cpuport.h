/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

/* bytes of register width  */
#ifdef ARCH_CPU_64BIT
#define STORE                   sd
#define LOAD                    ld
#define REGBYTES                8
#else
<<<<<<< HEAD
#define STORE                     sw
#define LOAD                         lw
=======
#define STORE                   sw
#define LOAD                    lw
>>>>>>> 1185482745fa76c9094f8cf9227f85d55ed8e2bd
#define REGBYTES                4
#endif

#endif
