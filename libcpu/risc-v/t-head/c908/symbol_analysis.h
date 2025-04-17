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

#ifndef __SYMBOL_ANALYSIS_H__
#define __SYMBOL_ANALYSIS_H__

    #include <rtthread.h>

    //osdebug节区头描述结构体
    typedef struct os_symtab_header
    {
        rt_size_t function_table_offset;//函数表的偏移地址（相对于节区起始地址，下同）
        rt_size_t function_table_num;//函数表中的符号数量
        rt_size_t object_table_offset;//对象表的偏移地址
        rt_size_t object_table_num;//对象表中的符号数量
        rt_size_t general_symbol_table_offset;//一般符号（指代类型虽为NONE但带有GLOBAL的符号）表的偏移地址
        rt_size_t general_symbol_table_num;//一般符号表中的符号数量
        rt_size_t string_table_offset;//字符串表的偏移地址
        rt_size_t string_table_size;//字符串表的大小（字节为单位）
    }os_symtab_header;

    //符号描述结构体
    typedef struct os_symtab_item
    {
        rt_size_t name_offset;//符号名称在字符串表中的偏移地址
        rt_size_t address;//该符号所代表的地址
        rt_size_t size;//该符号所代表的大小
    }os_symtab_item;

    os_symtab_item *find_symbol_table(rt_size_t symbol_table_addr,rt_size_t symbol_num,rt_size_t address);
    const char *get_symbol_name(os_symtab_item *symbol);
    void print_symbol(os_symtab_item *symbol,rt_size_t address);
    void print_symbol_info(rt_size_t address,rt_bool_t function);
    void print_stacktrace(rt_size_t epc,rt_size_t fp);

#endif
