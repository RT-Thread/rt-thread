/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-18 13:43:19
 * @Description:  This files is for assert function
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef Ft_assert_H
#define Ft_assert_H

#include "ft_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define Fassert_NONE 0U
#define Fassert_OCCURRED 1U

    extern u32 Ft_assertStatus;
    extern s32 Ft_assertWait;
    extern void Ft_assert(FT_IN char *File, s32 Line);

    typedef void (*Ft_assertCallback)(FT_IN char *File, s32 Line);

/**
 * @name: Ft_assertVoid
 * @msg:  断言函数不带返回值
 * @param {*}
 * @return {*}
 */
#define Ft_assertVoid(Expression)               \
    {                                           \
        if (Expression)                         \
        {                                       \
            Ft_assertStatus = Fassert_NONE;     \
        }                                       \
        else                                    \
        {                                       \
            Ft_assert(__FILE__, __LINE__);      \
            Ft_assertStatus = Fassert_OCCURRED; \
            return;                             \
        }                                       \
    }

/**
 * @name:
 * @msg:
 * @in param:
 * @inout param:
 * @out param:
 * @return {*}
 */
#define Ft_assertBool(Expression)               \
    {                                           \
        if (Expression)                         \
        {                                       \
            Ft_assertStatus = Fassert_NONE;     \
        }                                       \
        else                                    \
        {                                       \
            Ft_assert(__FILE__, __LINE__);      \
            Ft_assertStatus = Fassert_OCCURRED; \
            return FALSE;                       \
        }                                       \
    }

/**
 * @name: Ft_assertZeroNum
 * @msg:  断言函数带返回值0
 * @param {*}
 * @return {*}
 */
#define Ft_assertZeroNum(Expression)            \
    {                                           \
        if (Expression)                         \
        {                                       \
            Ft_assertStatus = Fassert_NONE;     \
        }                                       \
        else                                    \
        {                                       \
            Ft_assert(__FILE__, __LINE__);      \
            Ft_assertStatus = Fassert_OCCURRED; \
            return FST_ASSERT_RETURN;           \
        }                                       \
    }

/**
 * @name: Ft_assertNonvoid
 * @msg:  断言函数带返回值FST_ASSERT_RETURN
 * @param {*}
 * @return {*}
 */
#define Ft_assertNonvoid(Expression)            \
    {                                           \
        if (Expression)                         \
        {                                       \
            Ft_assertStatus = Fassert_NONE;     \
        }                                       \
        else                                    \
        {                                       \
            Ft_assert(__FILE__, __LINE__);      \
            Ft_assertStatus = Fassert_OCCURRED; \
            return FST_ASSERT_RETURN;           \
        }                                       \
    }

/**
 * @name: Ft_assertNoneReturn
 * @msg:  断言函数不返回
 * @param {*}
 * @return {*}
 */
#define Ft_assertNoneReturn(Expression)         \
    {                                           \
        if (Expression)                         \
        {                                       \
            Ft_assertStatus = Fassert_NONE;     \
        }                                       \
        else                                    \
        {                                       \
            Ft_assert(__FILE__, __LINE__);      \
            Ft_assertStatus = Fassert_OCCURRED; \
        }                                       \
    }

#define Ft_assertVoidAlways()               \
    {                                       \
        Ft_assert(__FILE__, __LINE__);      \
        Ft_assertStatus = Fassert_OCCURRED; \
        return;                             \
    }

#define Ft_assertNonvoidAlways()            \
    {                                       \
        Ft_assert(__FILE__, __LINE__);      \
        Ft_assertStatus = Fassert_OCCURRED; \
        return FST_ASSERT_RETURN;           \
    }

    void Ft_assertSetCallBack(Ft_assertCallback routine);
#ifdef __cplusplus
}
#endif

#endif // !
