/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-01-20 10:07:04
 * @LastEditTime: 2021-05-24 14:36:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \project_freertos\devices\ft2004\gcc\asmArm.h
 */
#ifndef ASMARM_H
#define ASMARM_H

#define FUNC_LABEL(func) \
    func:

#if (defined __GNUC__)
#define FUNC_BEGIN(func) \
    .thumb;              \
    .thumb_func;         \
    .balign 4;           \
    FUNC_LABEL(func)
#else /* !__GNUC__ */
#define FUNC_BEGIN(func) \
    .thumb;              \
    .balign 4;           \
    FUNC_LABEL(func)
#endif /* __GNUC__ */

#define FUNC(sym) sym
#define FUNC_END(func) .size FUNC(func), .- FUNC(func)

#define Swap64(var64) var64
#define Swap32(var32) var32

#endif // !ASMARM_H
