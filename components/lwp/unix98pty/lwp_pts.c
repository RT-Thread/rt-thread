/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lwp_pty.h"

rt_inline struct rt_wqueue *pts_get_wq(struct rt_lwp *lwp)
{
    return &lwp->wait_queue;
}

static int pts_file_open(struct dfs_fd *fd)
{
    int ret = 0;
    struct rt_device *device = RT_NULL;
    rt_base_t level = 0;

    level = rt_hw_interrupt_disable();
    device = (struct rt_device *)fd->fnode->data; 
    RT_ASSERT(device != RT_NULL);

    if (fd->fnode->ref_count == 1)
    {
        ret = rt_device_open(device, fd->flags);
    }
    rt_hw_interrupt_enable(level);
    return ret;
}

static int pts_file_close(struct dfs_fd *fd)
{
    int ret = 0;
    struct rt_device *device = RT_NULL;
    struct rt_pts_device *pts = LWP_PTY_GET_PTS(fd); 
    rt_base_t level = 0;

    level = rt_hw_interrupt_disable();

    device = (struct rt_device *)fd->fnode->data;
    RT_ASSERT(device != RT_NULL);

    if (fd->fnode->ref_count == 1)
    {
        ret = rt_device_close(device);
        lwp_pts_unregister(pts); 
    }

    rt_hw_interrupt_enable(level);
    
    return ret;
}

static int pts_file_read(struct dfs_fd *fd, void *buf, size_t count)
{
    rt_base_t level = 0;
    size_t size = 0;
    struct rt_pts_device *pts = LWP_PTY_GET_PTS(fd); 
    struct rt_lwp *lwp = RT_NULL;
    struct rt_wqueue *wq = RT_NULL;
    int wait_ret = 0;

    level = rt_hw_interrupt_disable();

    lwp = (struct rt_lwp *)(rt_thread_self()->lwp);
    wq = pts_get_wq(lwp);

    while(count)
    {
        size = rt_device_read(&pts->parent, -1, buf, count);
        if (size > 0)
        {
            break;
        }

        if (fd->flags & O_NONBLOCK)
        {
            break;
        }

        /* 当直接读的时候，没有数据就挂起，等待 ptmx 写入数据后唤醒 */ 
        pts->mwq = wq; /* 将当前lwp的等待队列设置到 pts 中，用于 ptmx 写数据后唤醒 lwp 读数据 */  
        wait_ret = rt_wqueue_wait_interruptible(wq, 0, RT_WAITING_FOREVER);
        pts->mwq = RT_NULL; /* 清空 */ 
        if (wait_ret != 0)
        {
            break;
        }
    }

    rt_hw_interrupt_enable(level);

    if (size < 0)
    {
        size = 0;
    }

    return size; 
}

static int pts_file_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    int size = 0;
    rt_base_t level = 0;

    level = rt_hw_interrupt_disable();
    
    struct rt_pts_device *pts = LWP_PTY_GET_PTS(fd); 
    RT_ASSERT(pts != RT_NULL);
    size = rt_device_write((struct rt_device *)pts, -1, buf, count);

    rt_hw_interrupt_enable(level);

    return size;
}

static int pts_file_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    rt_base_t level = 0;
    struct rt_pts_device *pts = LWP_PTY_GET_PTS(fd); 

    level = rt_hw_interrupt_disable();

    switch (cmd) {
    case TIOCSWINSZ:
        rt_memcpy(&pts->winsize, args, sizeof(struct winsize)); 
        LOG_D("set /dev/pts/%d winsize: %d %d %d %d", 
            pts->pts_index, 
            pts->winsize.ws_row, pts->winsize.ws_col, 
            pts->winsize.ws_xpixel, pts->winsize.ws_ypixel); 
        rt_hw_interrupt_enable(level);
        return 0; 
    case TIOCGWINSZ:
        rt_memcpy(args, &pts->winsize, sizeof(struct winsize)); 
        rt_hw_interrupt_enable(level);
        return 0; 

    case TIOCSCTTY: 
        LOG_D("TODO PTS TIOCSCTTY CMD");
        rt_hw_interrupt_enable(level); 
        return 0; 

#if defined(RT_USING_POSIX_TERMIOS) 
    case TCSETS:
        rt_memcpy(&pts->tio, args, sizeof(struct termios)); 
        rt_hw_interrupt_enable(level);
        return 0; 
    case TCGETS:
        rt_memcpy(args, &pts->tio, sizeof(struct termios)); 
        rt_hw_interrupt_enable(level);
        return 0; 
#endif /* RT_USING_POSIX_TERMIOS */ 
    }

    rt_hw_interrupt_enable(level);
    return -EINVAL;
}

static int pts_file_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    rt_base_t level = 0;
    int mask = POLLOUT; 
    rt_size_t len;
    struct rt_pts_device *pts = LWP_PTY_GET_PTS(fd); 
    struct rt_wqueue *wq = RT_NULL;
    struct rt_lwp *lwp = RT_NULL;

    level = rt_hw_interrupt_disable();

    lwp = (struct rt_lwp *)(rt_thread_self()->lwp);
    wq = pts_get_wq(lwp);
    rt_poll_add(wq, req);
    pts->mwq = wq; 

    /* 判断是否有数据可以 read 设备 */ 
    len = rt_ringbuffer_data_len(pts->mrb);
    if(len)
    {
        mask |= POLLIN;
    }

    rt_hw_interrupt_enable(level);

    return mask; 
}

static rt_err_t pts_device_init(struct rt_device *dev)
{
    return RT_EOK; 
}

static rt_err_t pts_device_open(struct rt_device *dev, rt_uint16_t oflag)
{
    // TODO: oflag = O_NOCTTY 
    return RT_EOK; 
}

static rt_err_t pts_device_close(struct rt_device *dev)
{
    return RT_EOK; 
}

static rt_size_t pts_device_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_base_t level = 0;
    rt_size_t len = 0;
    struct rt_pts_device *pts = (struct rt_pts_device *)dev;

    level = rt_hw_interrupt_disable();
    if (size)
    {
        len = rt_ringbuffer_data_len(pts->mrb); 
        if (len > size)
        {
            len = size;
        }
        if (len)
        {
            len = rt_ringbuffer_get(pts->mrb, buffer, len);
        }
    }
    rt_hw_interrupt_enable(level); 

    return len; 
}

static rt_size_t pts_device_write(struct rt_device *dev, rt_off_t pos, const void *buffer, rt_size_t count)
{
    rt_base_t level = 0;
    rt_size_t size = 0;
    struct rt_pts_device *pts = RT_NULL; 

    level = rt_hw_interrupt_disable(); 
    pts = (struct rt_pts_device *)dev; 
    size = lwp_pts_push_srb(pts, (void *)buffer, count); 
    rt_hw_interrupt_enable(level);

    return size; 
}

static rt_err_t pts_device_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK; 
}

#ifdef RT_USING_POSIX
const static struct dfs_file_ops pts_file_ops =
{
    pts_file_open,
    pts_file_close,
    pts_file_ioctl,
    pts_file_read,
    pts_file_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    pts_file_poll, 
};
#endif /* RT_USING_POSIX */ 

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pts_device_ops =
{
    pts_device_init,
    pts_device_open,
    pts_device_close,
    pts_device_read,
    pts_device_write,
    pts_device_control,
};
#endif /* RT_USING_DEVICE_OPS */ 

int lwp_pts_isbusy(struct rt_pts_device *pts)
{
    RT_ASSERT(pts != RT_NULL); 
    return (pts->parent.ref_count > 0) ? 1 : 0;  
}

static rt_size_t dispose_char(struct rt_pts_device *pts, char ch)
{
    rt_uint8_t is_lfcr = 0; 

    if (ch < 0)
    {
        return 0; 
    }

    /* 判断输入是否超过了缓存, 截断超出部分 */ 
    if (pts->line_position >= LWP_PTY_INPUT_BFSZ && ch != '\r' && ch != '\n')
    {
        return 0; 
    }

    /* handle control key: 
     * up key  : 0x1b 0x5b 0x41
     * down key: 0x1b 0x5b 0x42
     * right key:0x1b 0x5b 0x43
     * left key: 0x1b 0x5b 0x44
     */
    if(ch == 0x1b)
    {
        pts->stat = LWP_PTS_INPUT_WAIT_SPEC_KEY; 
        return 0; 
    }
    else if (pts->stat == LWP_PTS_INPUT_WAIT_SPEC_KEY)
    {
        if(ch == 0x5b)
        {
            pts->stat = LWP_PTS_INPUT_WAIT_FUNC_KEY;
            return 0; 
        }

        pts->stat = LWP_PTS_INPUT_WAIT_NORMAL; 
    }
    else if (pts->stat == LWP_PTS_INPUT_WAIT_FUNC_KEY)
    {
        pts->stat = LWP_PTS_INPUT_WAIT_NORMAL; 

        if (ch == 0x41) /* up key */
        {
            LOG_D("find input UP key"); 
            char buff[] = "^[[A"; 
            rt_ringbuffer_put_force(pts->srb, (void *)buff, rt_strlen(buff)); /* 回显 */ 
            return 0; 
        }
        else if (ch == 0x42) /* down key */
        {
            LOG_D("find input DOWN key"); 
            char buff[] = "^[[B"; 
            rt_ringbuffer_put_force(pts->srb, (void *)buff, rt_strlen(buff)); /* 回显 */ 
            return 0; 
        }
        else if (ch == 0x44) /* left key */
        {
            LOG_D("find input RIGHT key"); 
            char buff[] = "^[[C"; 
            rt_ringbuffer_put_force(pts->srb, (void *)buff, rt_strlen(buff)); /* 回显 */ 
            return 0; 
        }
        else if (ch == 0x43) /* right key */
        {
            LOG_D("find input LEFT key"); 
            char buff[] = "^[[D"; 
            rt_ringbuffer_put_force(pts->srb, (void *)buff, rt_strlen(buff)); /* 回显 */ 
            return 0; 
        }
    }

    /* received null or error */
    if (ch == '\0' || ch == 0xFF) return 0; 
    else if (ch == '\t') 
    {
        /* 补全不回显, 但是由会传递给 sh 处理 */ 
        pts->line[pts->line_position] = ch; 
        pts->line_position++; 
        return 0; 
    }
    else if (ch == 0x7f || ch == 0x08) /* handle backspace key */
    {
        LOG_D("find input backspace key"); 

        char buff[] = "\b \b"; 
        rt_ringbuffer_put_force(pts->srb, (void *)buff, rt_strlen(buff)); /* 回显 */ 
        pts->line_position--; 
        return 0; 
    }

    /* handle end of line, break */
    else if (ch == '\r' || ch == '\n')
    {
        is_lfcr = 1; 
    }

    rt_ringbuffer_put_force(pts->srb, (void *)&ch, 1); /* 回显 */ 

    /* 将没有回车的一行输入缓存到 line 中, 当发现回车换行后再统一输出到 ptmx 处理 */
    // LOG_D("%d", ch); 
    pts->line[pts->line_position] = ch; 
    pts->line_position++; 

    return is_lfcr; 
}

rt_size_t lwp_pts_push_mrb(struct rt_pts_device *pts, void *buffer, rt_size_t size)
{
    rt_size_t len = 0;
    rt_uint8_t is_lfcr = 0; 
    RT_ASSERT(pts != RT_NULL); 

    if(pts->echo)
    {
        /* 按照字符处理 */ 
        for(int index = 0; index < size; index++)
        {
            char *ptr = (char *)buffer; 
            is_lfcr = dispose_char(pts, *(ptr + index)); 
        }

        /* 判断是否发现回车换行了 */
        if(is_lfcr)
        {
            // LOG_D("pts->line_position = %d", pts->line_position); 
            rt_ringbuffer_put_force(pts->mrb, (void *)pts->line, pts->line_position);  
            pts->line_position = 0; 
            rt_memset(pts->line, 0x00, LWP_PTY_INPUT_BFSZ+1); 
        }
    }
    else /* 不处理直接传递给 sh 处理回显和字符 */ 
    {
        rt_ringbuffer_put_force(pts->mrb, buffer, size); 
    }

    len = rt_ringbuffer_data_len(pts->mrb); 
    if(len && pts->mwq) 
    {
        // 先读阻塞，用于唤醒阻塞的 lwp 进程
        rt_wqueue_wakeup(pts->mwq, (void*)POLLIN); 
    } 

    return len; 
}

rt_size_t lwp_pts_push_srb(struct rt_pts_device *pts, void *buffer, rt_size_t size)
{
    rt_size_t len = 0;
    RT_ASSERT(pts != RT_NULL); 
    rt_ringbuffer_put_force(pts->srb, buffer, size); 
    len = rt_ringbuffer_data_len(pts->srb); 

    if(len && pts->swq) 
    {
        // 先读阻塞，用于唤醒阻塞的 lwp 进程
        rt_wqueue_wakeup(pts->swq, (void*)POLLIN); 
    } 
    return len; 
}

int lwp_pts_unregister(struct rt_pts_device *pts)
{
    rt_err_t ret = RT_EOK; 
    rt_base_t level = 0;

    level = rt_hw_interrupt_disable(); 
    if(pts->parent.ref_count > 0)
    {
        ret = (-RT_EBUSY);
        goto _exit;  
    }

    rt_ringbuffer_destroy(pts->mrb); 
    rt_ringbuffer_destroy(pts->srb); 

    pts->mrb = RT_NULL;
    pts->srb = RT_NULL;
    
    rt_memset(&pts->winsize, 0x00, sizeof(struct winsize)); 
    pts->pts_lock = 0; 
    pts->ptmx_fd = 0; 
    pts->pts_index = 0; 
    pts->flags = PTY_INIT_FLAG_NONE; 
    ret = rt_device_unregister(&(pts->parent)); 
    
_exit: 
    rt_hw_interrupt_enable(level); 

    return ret; 
}

int lwp_pts_register(struct rt_pts_device *pts, int ptmx_fd, int pts_index) 
{
    rt_err_t ret = RT_EOK;
    rt_base_t level = 0;
    struct rt_device *device = RT_NULL; 
    char name[20];

    level = rt_hw_interrupt_disable(); 

    if(pts->flags != PTY_INIT_FLAG_NONE)
    {
        LOG_E("pts%d has been registered", pts_index); 
        ret = (-RT_EBUSY); 
        goto _exit; 
    }

    device = &(pts->parent); 
    device->type    = RT_Device_Class_Char; 
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &pts_device_ops;
#else
    device->init    = pts_device_init;
    device->open    = pts_device_open;
    device->close   = pts_device_close;
    device->read    = pts_device_read;
    device->write   = pts_device_write;
    device->control = pts_device_control;
#endif /* RT_USING_DEVICE_OPS */ 

    rt_snprintf(name, sizeof(name), "pts%d", pts_index);
    ret = rt_device_register(device, name, RT_DEVICE_FLAG_RDWR); 
    if (ret != RT_EOK)
    {
        LOG_E("pts%d register failed", pts_index); 
        ret = -RT_EIO;
        goto _exit;
    }

#ifdef RT_USING_POSIX
    /* set fops */
    device->fops = &pts_file_ops; 
#endif

    pts->mrb = rt_ringbuffer_create(LWP_PTY_INPUT_BFSZ);
    pts->srb = rt_ringbuffer_create(LWP_PTY_INPUT_BFSZ);

    RT_ASSERT(pts->mrb != RT_NULL); 
    RT_ASSERT(pts->srb != RT_NULL); 

    pts->echo = 1; 
    pts->stat = LWP_PTS_INPUT_WAIT_NORMAL;
    pts->line_position = 0; 
    rt_memset(pts->line, 0x00, sizeof(pts->line)); 

    rt_mutex_init(&pts->mutex, name, RT_IPC_FLAG_FIFO); 
    pts->mwq = RT_NULL;
    rt_memset(&pts->winsize, 0x00, sizeof(struct winsize)); 
    pts->pts_lock = 1; 
    pts->ptmx_fd = ptmx_fd; 
    pts->pts_index = pts_index; 
    pts->flags = PTY_INIT_FLAG_REGED; 

_exit: 
    rt_hw_interrupt_enable(level); 

    return ret; 
}

#include <rtthread.h>
#include <rtdevice.h>
int pts_dump(int argc, char *argv[])
{
    struct rt_pts_device *pts = RT_NULL; 
    int mrblen = 0, srblen = 0; 
    rt_device_t dev = rt_device_find(argv[1]); 
    
    pts = (struct rt_pts_device *)dev; 
    mrblen = rt_ringbuffer_data_len(pts->mrb);
    srblen = rt_ringbuffer_data_len(pts->srb);

    LOG_I("dev %s mrblen = %d srblen = %d", argv[1], mrblen, srblen); 
    return 0; 
}
MSH_CMD_EXPORT(pts_dump, dump /dev/pts/%d device ringbuffer info.);
