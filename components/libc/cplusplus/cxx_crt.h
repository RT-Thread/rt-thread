/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
* Change Logs:
* Date           Author       Notes
* 2015-03-07     Bernard      Add copyright header.
*/

#ifndef CRT_H_
#define CRT_H_

#include <inttypes.h>
#include <stdlib.h>

void *operator new(size_t size);
void *operator new[](size_t size);

void operator delete(void * ptr);
void operator delete[](void *ptr);

extern "C" void __cxa_pure_virtual(void);
extern "C" int  cplusplus_system_init(void);

#endif
