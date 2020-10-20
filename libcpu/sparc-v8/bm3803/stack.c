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

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    rt_uint32_t *stk;
    int window_index;
    int register_index;

    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk      = (rt_uint32_t *)stack_addr;

    stk -= 24;
    stk -= 8;

    for (register_index = 0; register_index != 8; register_index++)
        stk[register_index] = 0xdeadbeef;

    for (window_index = 0; window_index != 8; window_index++)
    {
        stk -= 16;
        for (register_index = 0; register_index != 16; register_index++)
            stk[register_index] = 0xdeadbeef;
        if (window_index == 0)
        {
            stk[8] = (rt_uint32_t)parameter;
            stk[15] = (rt_uint32_t)texit - 8;
        }
    }

    stk -= 34;
    for (register_index = 0; register_index != 34; register_index++)
        stk[register_index] = 0;

    stk -= 4;
    stk[0] = (rt_uint32_t)tentry; //pc
    stk[1] = (rt_uint32_t)tentry + 4; //npc
    stk[2] = 0x10C7; //psr
    stk[3] = 0x2; //wim

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}
