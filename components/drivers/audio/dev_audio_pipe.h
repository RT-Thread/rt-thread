/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-03-04     wumingzi     add doxygen comments.
 */
#ifndef __DEV_AUDIO_PIPE_H__
#define __DEV_AUDIO_PIPE_H__

/**
 * Pipe Device
 */
#include <rtdevice.h>

#ifndef RT_PIPE_BUFSZ
#define PIPE_BUFSZ    512
#else
#define PIPE_BUFSZ    RT_PIPE_BUFSZ
#endif

/**
 * @brief Portal device
 */
struct rt_audio_portal_device
{
    struct rt_device parent;
    struct rt_device *write_dev;
    struct rt_device *read_dev;
};

/**
 * @brief Aduio pipe flags
 */
enum rt_audio_pipe_flag
{

    RT_PIPE_FLAG_NONBLOCK_RDWR = 0x00, /**< both read and write won't block */
    RT_PIPE_FLAG_BLOCK_RD = 0x01, /**< read would block */
    RT_PIPE_FLAG_BLOCK_WR = 0x02, /**< write would block */
    RT_PIPE_FLAG_FORCE_WR = 0x04, /**< write to this pipe will discard some data when the pipe is full.
                                    * When this flag is set, RT_PIPE_FLAG_BLOCK_WR will be ignored since write
                                    * operation will always be success. */
};

/**
 * @brief Audio buffer info
 *
 * The preferred number and size of audio pipeline buffer for the audio device, it
 * will be used in rt_audio_replay struct.
 *
 */
struct rt_audio_pipe
{
    struct rt_device parent;

    struct rt_ringbuffer ringbuffer; /**< ring buffer in pipe device */

    rt_int32_t flag;

    rt_list_t suspended_read_list; /**< suspended thread list for reading */
    rt_list_t suspended_write_list; /**< suspended thread list for writing  */

    struct rt_audio_portal_device *write_portal;
    struct rt_audio_portal_device *read_portal;
};

#define PIPE_CTRL_GET_SPACE          0x14 /**< get the remaining size of a pipe device */

rt_err_t rt_audio_pipe_init(struct rt_audio_pipe *pipe,
                      const char *name,
                      rt_int32_t flag,
                      rt_uint8_t *buf,
                      rt_size_t size);
rt_err_t rt_audio_pipe_detach(struct rt_audio_pipe *pipe);
#ifdef RT_USING_HEAP
rt_err_t rt_audio_pipe_create(const char *name, rt_int32_t flag, rt_size_t size);
void rt_audio_pipe_destroy(struct rt_audio_pipe *pipe);
#endif /* RT_USING_HEAP */

#endif /* __DEV_AUDIO_PIPE_H__ */