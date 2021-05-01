/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LWP_PTY_H__
#define __LWP_PTY_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <lwp.h>
#include <lwp_user_mm.h>

#if defined(RT_USING_POSIX_TERMIOS)
#include <posix_termios.h> 
#endif 

#ifdef __cplusplus
extern "C" {
#endif

#define DBG_ENABLE
#if defined(LWP_PTY_USING_DEBUG) 
#define DBG_LEVEL DBG_LOG
#else
#define DBG_LEVEL DBG_INFO
#endif 
#define DBG_COLOR
#include <rtdbg.h>

#ifndef LWP_PTY_INPUT_BFSZ
#define LWP_PTY_INPUT_BFSZ 1024 
#endif /* LWP_PTY_INPUT_BFSZ */ 

#ifndef LWP_PTY_PTS_SIZE
#define LWP_PTY_PTS_SIZE 3 
#endif /* LWP_PTY_PTS_SIZE */ 

#ifndef LWP_PTY_HISTORY_LINE_SIZE
#define LWP_PTY_HISTORY_LINE_SIZE 5 
#endif /* LWP_PTY_HISTORY_LINE_SIZE */ 

#define LWP_PTY_GET_PTMX(fd) ((struct rt_ptmx_device *)(fd->fnode->data)) 
#define LWP_PTY_GET_PTS(fd)  ((struct rt_pts_device *)(fd->fnode->data)) 

enum lwp_pty_init_flag
{
    PTY_INIT_FLAG_NONE = 0,
    PTY_INIT_FLAG_REGED,
    PTY_INIT_FLAG_INITED,
}; 
typedef enum lwp_pty_init_flag lwp_pty_init_flag_t; 

enum lwp_pts_input_stat
{
    LWP_PTS_INPUT_WAIT_NORMAL = 0,
    LWP_PTS_INPUT_WAIT_SPEC_KEY,
    LWP_PTS_INPUT_WAIT_FUNC_KEY,
};
typedef enum lwp_pts_input_stat lwp_pts_input_stat_t; 

struct rt_pts_device
{
    struct rt_device parent;
    int flags; 
    int pts_lock; 
    int pts_index; /* index = /dev/pts/%d */ 
    struct rt_mutex mutex; 

    // ptmx
    struct rt_ptmx_device *ptmx; 
    int ptmx_fd;

    // win attribute
    struct winsize winsize; 
    
#if defined(RT_USING_POSIX_TERMIOS)
    struct termios tio; 
#endif /* RT_USING_POSIX_TERMIOS */ 

    /* console echo */
    lwp_pts_input_stat_t stat;
    rt_uint8_t echo;
    char line[LWP_PTY_INPUT_BFSZ+1];
    rt_uint16_t line_position;

    struct rt_wqueue *mwq; 
    struct rt_wqueue *swq; 
    struct rt_ringbuffer *mrb; // ptmx w(master) ==> pts r(slave)
    struct rt_ringbuffer *srb; // pts w(slave) ==> ptmx r(master)
};

struct rt_ptmx_device
{
    struct rt_device parent;
    int flags;
    struct rt_mutex mutex; 
    struct rt_wqueue wq;
    
    int pts_index; 
    struct rt_pts_device pts[LWP_PTY_PTS_SIZE]; 
};

/* pty */
extern int lwp_pts_isbusy(struct rt_pts_device *pts); 
extern rt_size_t lwp_pts_push_mrb(struct rt_pts_device *pts, void *buffer, rt_size_t size); 
extern rt_size_t lwp_pts_push_srb(struct rt_pts_device *pts, void *buffer, rt_size_t size); 
extern int lwp_pts_unregister(struct rt_pts_device *pts); 
extern int lwp_pts_register(struct rt_pts_device *pts, int ptmx_fd, int pts_index);   

#ifdef __cplusplus
}
#endif

#endif /* __LWP_PTY_H__ */ 
