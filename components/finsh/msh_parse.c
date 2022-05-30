/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-25     WangQiang    the first verion for msh parse
 */

#include <rtthread.h>
#include <ctype.h>

#define forstrloop(str) for (; '\0' != *(str); (str)++)

/**
 * This function will check integer.
 *
 * @param strvalue string
 *
 * @return true or false
 */
rt_bool_t msh_isint(char *strvalue)
{
    if ((RT_NULL == strvalue) || ('\0' == strvalue[0]))
    {
        return RT_FALSE;
    }
    if (('+' == *strvalue) || ('-' == *strvalue))
    {
        strvalue++;
    }
    forstrloop(strvalue)
    {
        if (!isdigit((int)(*strvalue)))
        {
            return RT_FALSE;
        }
    }
    return RT_TRUE;
}

/**
 * This function will check hex.
 *
 * @param strvalue string
 *
 * @return true or false
 */
rt_bool_t msh_ishex(char *strvalue)
{
    int c;
    if ((RT_NULL == strvalue) || ('\0' == strvalue[0]))
    {
        return RT_FALSE;
    }
    if ('0' != *(strvalue++))
    {
        return RT_FALSE;
    }
    if ('x' != *(strvalue++))
    {
        return RT_FALSE;
    }

    forstrloop(strvalue)
    {
        c = tolower(*strvalue);
        if (!isxdigit(c))
        {
            return RT_FALSE;
        }
    }
    return RT_TRUE;
}

/**
 * This function will transform for string to hex.
 *
 * @param strvalue string
 *
 * @return true or false
 */
int msh_strtohex(char *strvalue)
{
    char c = 0;
    int value = 0;
    strvalue += 2;
    forstrloop(strvalue)
    {
        value *= 16;
        c = tolower(*strvalue);
        value += isdigit(c) ? c - '0' : c - 'a' + 10;
    }
    return value;
}
