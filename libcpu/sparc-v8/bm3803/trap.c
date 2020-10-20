/*
Copyright 2020 Shenzhen Academy of Aerospace Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Change Logs:
Date           Author       Notes
2020-10-16     Dystopia     the first version
*/

#include <rtthread.h>
#include <rthw.h>

extern struct rt_irq_desc isr_table[];

void rt_hw_trap(int tt, unsigned int *sp)
{
    void *param;
    rt_isr_handler_t isr_func;

    /* get interrupt service routine */
    isr_func = isr_table[tt].handler;
    param = isr_table[tt].param;

    /* turn to interrupt service routine */
    if (isr_func != RT_NULL)
        isr_func(tt, param);
}
