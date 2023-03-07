/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-23     WangXiaoyao  the first version
 */
#ifndef __MM_FLAG_H__
#define __MM_FLAG_H__

/**
 * @brief mm_flag_t
 * |max ------- 7|6 ----- 0|
 * |   control   |  align  |
 *
 * there should be no more than 25 flags
 */
typedef unsigned long mm_flag_t;

#define _MMF_CNTL_SHIFT  7
#define _MMF_ALIGN_MASK  0x7f
#define _MMF_CNTL_MASK   (~((1 << _MMF_CNTL_SHIFT) - 1))
#define _DEF_FLAG(index) (1 << (_MMF_CNTL_SHIFT + (index)))

enum mm_flag_cntl
{
    /**
     * @brief Indicate a possible COW mapping
     */
    MMF_MAP_PRIVATE = _DEF_FLAG(0),
    MMF_COW = _DEF_FLAG(1),

    /**
     * @brief [POSIX MAP_FIXED] When MAP_FIXED is set in the flags argument, the
     * implementation is informed that the value of pa shall be addr, exactly.
     * If a MAP_FIXED request is successful, the mapping established
     * by mmap() replaces any previous mappings for the pages in the range
     * [pa,pa+len) of the process.
     */
    MMF_MAP_FIXED = _DEF_FLAG(2),

    /**
     * @brief The backup page frame is allocated and setted only until it is
     * truly necessary by the user
     */
    MMF_PREFETCH = _DEF_FLAG(3),

    MMF_HUGEPAGE = _DEF_FLAG(4),

    MMF_TEXT = _DEF_FLAG(5),

    MMF_STATIC_ALLOC = _DEF_FLAG(6),

    /**
     * @brief a non-locked memory can be swapped out when required, this is
     * reserved for future
     */
    MMF_NONLOCKED = _DEF_FLAG(20),

    /**
     * @brief An alignment is specified in flags that the mapping must admit
     */
    MMF_REQUEST_ALIGN = _DEF_FLAG(21),
};

#define MMF_GET_ALIGN(src) ((src & _MMF_ALIGN_MASK))
#define MMF_SET_ALIGN(src, align)                                              \
    ((src & ~_MMF_ALIGN_MASK) | (__builtin_ffsl(align) - 1))

#define MMF_GET_CNTL(src)         (src & _MMF_CNTL_MASK)
#define MMF_TEST_CNTL(src, flag)  (src & flag)
#define MMF_SET_CNTL(src, flag)   ((src) | (flag))
#define MMF_CLEAR_CNTL(src, flag) ((src) & ~(flag))

/**
 * @brief Create Flags
 *
 * example: MMF_CREATE(0, 0)
 *          MMF_CREATE(MM_MAP_FIXED, 0x2000)
 *
 * Direct use of flag is also acceptable: (MMF_MAP_FIXED | MMF_PREFETCH)
 */
#define MMF_CREATE(cntl, align)                                                \
    (align ? (MMF_SET_CNTL((mm_flag_t)0, (cntl) | MMF_REQUEST_ALIGN) |         \
              MMF_SET_ALIGN((mm_flag_t)0, align))                              \
           : (MMF_SET_CNTL((mm_flag_t)0, (cntl) & ~MMF_REQUEST_ALIGN)))

#undef _DEF_FLAG
#endif /* __MM_FLAG_H__ */
