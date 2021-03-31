/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include "finsh_error.h"

uint8_t global_errno;

static const char * finsh_error_string_table[] =
{
    "No error",
    "Invalid token",
    "Expect a type",
    "Unknown type",
    "Variable exist",
    "Expect a operater",
    "Memory full",
    "Unknown operator",
    "Unknown node",
    "Expect a character",
    "Unexpect end",
    "Unknown token",
    "Float not supported",
    "Unknown symbol",
    "Null node"
};

int finsh_error_init()
{
    global_errno = FINSH_ERROR_OK;

    return 0;
}

int finsh_error_set(uint8_t type)
{
    global_errno = type;

    return 0;
}

uint8_t finsh_errno()
{
    return global_errno;
}

const char* finsh_error_string(uint8_t type)
{
    return finsh_error_string_table[type];
}
