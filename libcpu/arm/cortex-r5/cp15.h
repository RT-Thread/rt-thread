/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#ifndef __CP15_H__
#define __CP15_H__

int rt_hw_cpu_id(void);
void rt_cpu_vector_set_base(unsigned int addr);

#endif
