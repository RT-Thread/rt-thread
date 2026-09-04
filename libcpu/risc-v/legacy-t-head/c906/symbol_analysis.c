/*
 * Copyright lizhirui
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     lizhirui     the first version
 * 2021-05-20     lizhirui     add os debug support
 */

#include <rtthread.h>
#include "symbol_analysis.h"

#define MEMORY_BASE 0x40000000
#define MEMORY_SIZE (128 * 0x100000)

extern rt_size_t _osdebug_start;

static os_symtab_header *symtab_header = (os_symtab_header *)&_osdebug_start;

//该函数用于在指定的表中查找某个地址对应的符号的描述结构体指针，返回值的符号遵循规则详见文档
os_symtab_item *find_symbol_table(rt_size_t symbol_table_addr,rt_size_t symbol_num,rt_size_t address)
{
    rt_size_t left = 0;
    rt_size_t right = symbol_num;
    os_symtab_item *sym_table = (os_symtab_item *)((rt_size_t)&_osdebug_start + symbol_table_addr);

    while(left < right)
    {
        rt_size_t mid = (left + right) >> 1;
        //rt_kprintf("left = %d,right = %d,mid = %d\n",left,right,mid);

        if(address < sym_table[mid].address)
        {
            right = mid;

            while((right < symbol_num) && ((right - 1) >= 0) && (sym_table[right].address == sym_table[right - 1].address))
            {
                right--;
            }
        }
        else if(address == sym_table[mid].address)
        {
            left = mid + 1;
            break;
        }
        else
        {
            left = mid;

            while((left >= 0) && ((left + 1) < symbol_num) && (sym_table[left].address == sym_table[left + 1].address))
            {
                left++;
            }

            left++;
        }
    }

    left--;

    if(left == ((rt_size_t)-1))
    {
        return RT_NULL;
    }

    while((left < symbol_num) && ((left - 1) >= 0) && (sym_table[left].address == sym_table[left - 1].address))
    {
        left--;
    }

    return &sym_table[left];
}

//该函数用于根据给定的符号指针从字符串表中找到对应的符号名指针并返回
const char *get_symbol_name(os_symtab_item *symbol)
{
    return (const char *)((rt_size_t)&_osdebug_start + symtab_header -> string_table_offset + symbol -> name_offset);
}

//该函数可以根据给定的符号和地址向中断打印出标准格式的符号信息
void print_symbol(os_symtab_item *symbol,rt_size_t address)
{
    rt_kprintf("<%s(0x%p)",get_symbol_name(symbol),symbol -> address);

    if(symbol -> size)
    {
        rt_kprintf(" : 0x%x>",symbol -> size);
    }
    else
    {
        rt_kprintf(">");
    }

    if(address > symbol -> address)
    {
        rt_kprintf(" + 0x%x",address - symbol -> address);
    }
}

//该函数用于打印出一个地址关联的全部符号信息
void print_symbol_info(rt_size_t address,rt_bool_t function)
{
    os_symtab_item *function_symbol = find_symbol_table(symtab_header -> function_table_offset,symtab_header -> function_table_num,address);
    os_symtab_item *object_symbol = find_symbol_table(symtab_header -> object_table_offset,symtab_header -> object_table_num,address);
    os_symtab_item *general_symbol = find_symbol_table(symtab_header -> general_symbol_table_offset,symtab_header -> general_symbol_table_num,address);
    const char *dot = "";
    rt_bool_t valid = RT_FALSE;

    if(function)
    {
        while(function_symbol != RT_NULL)
        {
            if((function_symbol -> address + function_symbol -> size) > address)
            {
                rt_kprintf(dot);
                print_symbol(function_symbol,address);
                dot = ",";
                valid = RT_TRUE;
            }

            if(((rt_size_t)(function_symbol + 1)) >= (((rt_size_t)&_osdebug_start) + symtab_header -> function_table_offset + symtab_header -> function_table_num * sizeof(os_symtab_item)))
            {
                break;
            }

            if(function_symbol[0].address == function_symbol[1].address)
            {
                function_symbol++;
            }

            break;
        }

        if(!valid)
        {
            while(general_symbol != RT_NULL)
            {
                rt_kprintf(dot);
                print_symbol(general_symbol,address);
                dot = ",";
                valid = RT_TRUE;

                if(((rt_size_t)(general_symbol + 1)) >= (((rt_size_t)&_osdebug_start) + symtab_header -> general_symbol_table_offset + symtab_header -> general_symbol_table_num * sizeof(os_symtab_item)))
                {
                    break;
                }

                if(general_symbol[0].address == general_symbol[1].address)
                {
                    general_symbol++;
                }

                break;
            }

            while(object_symbol != RT_NULL)
            {
                if((object_symbol -> address + object_symbol -> size) > address)
                {
                    rt_kprintf(dot);
                    print_symbol(object_symbol,address);
                    dot = ",";
                    valid = RT_TRUE;
                }

                if(((rt_size_t)(object_symbol + 1)) >= (((rt_size_t)&_osdebug_start) + symtab_header -> object_table_offset + symtab_header -> object_table_num * sizeof(os_symtab_item)))
                {
                    break;
                }

                if(object_symbol[0].address == object_symbol[1].address)
                {
                    object_symbol++;
                }

                break;
            }
        }
    }
    else
    {
        while(object_symbol != RT_NULL)
        {
            if((object_symbol -> address + object_symbol -> size) > address)
            {
                rt_kprintf(dot);
                print_symbol(object_symbol,address);
                dot = ",";
                valid = RT_TRUE;
            }

            if(((rt_size_t)(object_symbol + 1)) >= (((rt_size_t)&_osdebug_start) + symtab_header -> object_table_offset + symtab_header -> object_table_num * sizeof(os_symtab_item)))
            {
                break;
            }

            if(object_symbol[0].address == object_symbol[1].address)
            {
                object_symbol++;
            }

            break;
        }

        if(!valid)
        {
            while(general_symbol != RT_NULL)
            {
                rt_kprintf(dot);
                print_symbol(general_symbol,address);
                dot = ",";
                valid = RT_TRUE;

                if(((rt_size_t)(general_symbol + 1)) >= (((rt_size_t)&_osdebug_start) + symtab_header -> general_symbol_table_offset + symtab_header -> general_symbol_table_num * sizeof(os_symtab_item)))
                {
                    break;
                }

                if(general_symbol[0].address == general_symbol[1].address)
                {
                    general_symbol++;
                }

                break;
            }

            while(function_symbol != RT_NULL)
            {
                if((function_symbol -> address + function_symbol -> size) > address)
                {
                    rt_kprintf(dot);
                    print_symbol(function_symbol,address);
                    dot = ",";
                    valid = RT_TRUE;
                }

                if(((rt_size_t)(function_symbol + 1)) >= (((rt_size_t)&_osdebug_start) + symtab_header -> function_table_offset + symtab_header -> function_table_num * sizeof(os_symtab_item)))
                {
                    break;
                }

                if(function_symbol[0].address == function_symbol[1].address)
                {
                    function_symbol++;
                }

                break;
            }
        }
    }

    if(dot == "")
    {
        rt_kprintf("<Unknown Symbol>");
    }
}

//该函数用于在出错时打印出栈跟踪信息
void print_stacktrace(rt_size_t epc,rt_size_t fp)
{
    rt_kprintf("-----------------------------Dump Stacktrace----------------------------\n\n");
    rt_size_t sp = fp;
    rt_size_t i = 0;

    rt_kprintf("address 0x%p(",epc);
    print_symbol_info(epc,RT_TRUE);
    rt_kprintf(")\n\n");

    while(1)
    {
        if((sp >= MEMORY_BASE) && (sp < (MEMORY_BASE + MEMORY_SIZE)))
        {
            //rt_kprintf("%d: 0x%p\n",i,sp);
            rt_size_t *stack = (rt_size_t *)(sp - sizeof(rt_size_t) * 2);
            rt_size_t ra = stack[1];

            if(!ra)
            {
                break;
            }

            rt_kprintf("return to 0x%p(",ra);
            print_symbol_info(ra,RT_TRUE);
            rt_kprintf(")\n\n");
            //rt_kprintf("ra = 0x%p,fp = 0x%p\n",stack[1],stack[0]);
            sp = stack[0];
            i++;
        }
        else
        {
            break;
        }
    }

    rt_kprintf("---------------------------------Dump OK--------------------------------\n");
}
