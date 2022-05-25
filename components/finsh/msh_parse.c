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

#define forstrloop(str) for (; '\0' != *(str); (str)++)

/**
 * This function will tolower.
 *
 * @param c char
 *
 * @return tolower char
 */
int msh_tolower(int c)
{
    int temp = 'a' - 'A';

    if ((c < 'A') || (c > 'Z'))
    {
        return c;
    }
    return (c + temp);
}

/**
 * This function will check digit.
 *
 * @param c char
 *
 * @return true or false
 */
rt_bool_t msh_isdigit(int ch)
{
    if ((ch >= '0') && (ch <= '9'))
    {
        return RT_TRUE;
    }
    return RT_FALSE;
}

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
        if (!msh_isdigit(*strvalue))
        {
            return RT_FALSE;
        }
    }
    return RT_TRUE;
}

/**
 * This function will transform for string to integer.
 *
 * @param strvalue string
 *
 * @return true or false
 */
int msh_strtoint(char *strvalue)
{
    int value = 0;
    int sign = 1;
    if ('-' == *strvalue)
    {
        sign = -1;
        strvalue++;
    }
    else if ('+' == *strvalue)
    {
        strvalue++;
    }

    forstrloop(strvalue)
    {
        value *= 10;
        value += *strvalue - '0';
    }
    return value * sign;
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
    char c;
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
        c = msh_tolower(*strvalue);
        if (!msh_isdigit(c) && ((c < 'a') || (c > 'f')))
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
        c = msh_tolower(*strvalue);
        value += msh_isdigit(c) ? c - '0' : c - 'a' + 10;
    }
    return value;
}
