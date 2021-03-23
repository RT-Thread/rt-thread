/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef RTCONFIG_PROJECT_H__
#define RTCONFIG_PROJECT_H__

#define RT_HEAP_SIZE   (1024*1024*8)

#if defined(_MSC_VER)
#define NORESOURCE  //RT_VESRION in winuser.h
#define _CRT_ERRNO_DEFINED  //errno macro redefinition
#define _INC_WTIME_INL//dfs_elm.c time.h conflicts with wtime.inl
#define _INC_TIME_INL //dfs_elm.c time.h conflicts with wtime.inl

/* disable some warning in MSC */
#pragma warning(disable:4273)   /* to ignore: warning C4273: inconsistent dll linkage */
#pragma warning(disable:4312)   /* to ignore: warning C4312: 'type cast' : conversion from 'rt_uint32_t' to 'rt_uint32_t *' */
#pragma warning(disable:4311)   /* to ignore: warning C4311: 'type cast' : pointer truncation from 'short *__w64 ' to 'long' */
#pragma warning(disable:4996)   /* to ignore: warning C4996: The POSIX name for this item is deprecated. */
#pragma warning(disable:4267)   /* to ignore: warning C4267: conversion from 'size_t' to 'rt_size_t', possible loss of data */
#pragma warning(disable:4244)   /* to ignore: warning C4244: '=' : conversion from '__w64 int' to 'rt_size_t', possible loss of data */

#endif /* end of _MSC_VER */

#endif
