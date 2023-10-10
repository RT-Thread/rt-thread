/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <dfs_seq_file.h>
#include <dfs_dentry.h>

#define DBG_TAG "DFS.seq"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

static void dfs_seq_overflow(struct dfs_seq_file *seq)
{
    seq->count = seq->size;
}

static void *dfs_seq_alloc(unsigned long size)
{
    return rt_calloc(1, size);
}

int dfs_seq_open(struct dfs_file *file, const struct dfs_seq_ops *ops)
{
    struct dfs_seq_file *seq;

    if (!ops)
    {
        LOG_E("dfs_seq_open: ops = null, pathname: %s\n", file->dentry->pathname);
        return -EINVAL;
    }

    if (file->data)
    {
        LOG_W("dfs_seq_open: file->data != null\n");
    }

    seq = rt_calloc(1, sizeof(struct dfs_seq_file));
    if (!seq)
        return -ENOMEM;

    file->data = seq;

    rt_mutex_init(&seq->lock, "dfs_seq", RT_IPC_FLAG_PRIO);

    seq->ops = ops;
    seq->file = file;

    return 0;
}

static int dfs_seq_traverse(struct dfs_seq_file *seq, off_t offset)
{
    off_t pos = 0;
    int error = 0;
    void *p;

    seq->index = 0;
    seq->count = seq->from = 0;
    if (!offset)
        return 0;

    if (!seq->buf)
    {
        seq->buf = dfs_seq_alloc(seq->size = PAGE_SIZE);
        if (!seq->buf)
            return -ENOMEM;
    }
    p = seq->ops->start(seq, &seq->index);
    while (p)
    {
        error = seq->ops->show(seq, p);
        if (error < 0)
            break;
        if (error)
        {
            error = 0;
            seq->count = 0;
        }
        if (dfs_seq_is_full(seq))
            goto Eoverflow;

        p = seq->ops->next(seq, p, &seq->index);
        if (pos + seq->count > offset)
        {
            seq->from = offset - pos;
            seq->count -= seq->from;
            break;
        }
        pos += seq->count;
        seq->count = 0;
        if (pos == offset)
            break;
    }
    seq->ops->stop(seq, p);
    return error;

Eoverflow:
    seq->ops->stop(seq, p);
    rt_free(seq->buf);
    seq->count = 0;
    seq->buf = dfs_seq_alloc(seq->size <<= 1);
    return !seq->buf ? -ENOMEM : -EAGAIN;
}

ssize_t dfs_seq_read(struct dfs_file *file, void *buf, size_t size, off_t *pos)
{
    struct dfs_seq_file *seq = file->data;
    size_t copied = 0;
    size_t n;
    void *p;
    int err = 0;

    if (!size)
        return 0;

    rt_mutex_take(&seq->lock, RT_WAITING_FOREVER);

    /*
     * if request is to read from zero offset, reset iterator to first
     * record as it might have been already advanced by previous requests
     */
    if (*pos == 0)
    {
        seq->index = 0;
        seq->count = 0;
    }

    /* Don't assume ki_pos is where we left it */
    if (*pos != seq->read_pos)
    {
        while ((err = dfs_seq_traverse(seq, *pos)) == -EAGAIN)
            ;
        if (err)
        {
            /* With prejudice... */
            seq->read_pos = 0;
            seq->index = 0;
            seq->count = 0;
            goto Done;
        }
        else
        {
            seq->read_pos = *pos;
        }
    }

    /* grab buffer if we didn't have one */
    if (!seq->buf)
    {
        seq->buf = dfs_seq_alloc(seq->size = PAGE_SIZE);
        if (!seq->buf)
            goto Enomem;
    }
    // something left in the buffer - copy it out first
    if (seq->count)
    {
        n = seq->count > size ? size : seq->count;
        rt_memcpy((char *)buf + copied, seq->buf + seq->from, n);
        size -= n;
        seq->count -= n;
        seq->from += n;
        copied += n;
        if (seq->count) // hadn't managed to copy everything
            goto Done;
    }
    // get a non-empty record in the buffer
    seq->from = 0;
    p = seq->ops->start(seq, &seq->index);
    while (p)
    {
        err = seq->ops->show(seq, p);
        if (err < 0) // hard error
            break;
        if (err) // ->show() says "skip it"
            seq->count = 0;
        if (!seq->count)
        { // empty record
            p = seq->ops->next(seq, p, &seq->index);
            continue;
        }
        if (!dfs_seq_is_full(seq)) // got it
            goto Fill;
        // need a bigger buffer
        seq->ops->stop(seq, p);
        rt_free(seq->buf);
        seq->count = 0;
        seq->buf = dfs_seq_alloc(seq->size <<= 1);
        if (!seq->buf)
            goto Enomem;
        p = seq->ops->start(seq, &seq->index);
    }
    // EOF or an error
    seq->ops->stop(seq, p);
    seq->count = 0;
    goto Done;
Fill:
    // one non-empty record is in the buffer; if they want more,
    // try to fit more in, but in any case we need to advance
    // the iterator once for every record shown.
    while (1)
    {
        size_t offs = seq->count;
        off_t pos = seq->index;

        p = seq->ops->next(seq, p, &seq->index);
        if (pos == seq->index)
        {
            LOG_W(".next function %p did not update position index\n", seq->ops->next);
            seq->index++;
        }
        if (!p) // no next record for us
            break;
        if (seq->count >= size)
            break;
        err = seq->ops->show(seq, p);
        if (err > 0)
        { // ->show() says "skip it"
            seq->count = offs;
        }
        else if (err || dfs_seq_is_full(seq))
        {
            seq->count = offs;
            break;
        }
    }
    seq->ops->stop(seq, p);
    n = seq->count > size ? size : seq->count;
    rt_memcpy((char *)buf + copied, seq->buf, n);
    size -= n;
    copied += n;
    seq->count -= n;
    seq->from = n;
Done:
    if (!copied)
    {
        copied = seq->count ? -EFAULT : err;
    }
    else
    {
        *pos += copied;
        seq->read_pos += copied;
    }
    rt_mutex_release(&seq->lock);
    return copied;
Enomem:
    err = -ENOMEM;
    goto Done;
}

ssize_t dfs_seq_lseek(struct dfs_file *file, off_t offset, int whence)
{
    struct dfs_seq_file *seq = file->data;
    off_t retval = -EINVAL;

    rt_mutex_take(&seq->lock, RT_WAITING_FOREVER);

    switch (whence)
    {
    case SEEK_CUR:
        offset += file->fpos;
    case SEEK_SET:
        if (offset < 0)
            break;
        retval = offset;
        if (offset != seq->read_pos)
        {
            while ((retval = dfs_seq_traverse(seq, offset)) == -EAGAIN);
            if (retval)
            {
                /* with extreme prejudice... */
                retval = 0;
                seq->read_pos = 0;
                seq->index = 0;
                seq->count = 0;
            }
            else
            {
                seq->read_pos = offset;
                retval = offset;
            }
        }
    }

    rt_mutex_release(&seq->lock);

    return retval;
}

int dfs_seq_release(struct dfs_file *file)
{
    struct dfs_seq_file *seq = file->data;

    if (seq)
    {
        rt_mutex_detach(&seq->lock);
        if (seq->buf)
        {
            rt_free(seq->buf);
        }
        rt_free(seq);
    }

    return 0;
}

void dfs_seq_vprintf(struct dfs_seq_file *seq, const char *f, va_list args)
{
    int len;

    if (seq->count < seq->size)
    {
        len = vsnprintf(seq->buf + seq->count, seq->size - seq->count, f, args);
        if (seq->count + len < seq->size)
        {
            seq->count += len;
            return;
        }
    }
    dfs_seq_overflow(seq);
}

void dfs_seq_printf(struct dfs_seq_file *seq, const char *f, ...)
{
    va_list args;

    va_start(args, f);
    dfs_seq_vprintf(seq, f, args);
    va_end(args);
}

/**
 * write char to buffer
 */
void dfs_seq_putc(struct dfs_seq_file *seq, char c)
{
    if (seq->count < seq->size)
    {
        seq->buf[seq->count++] = c;
    }
}

/**
 * write string to buffer
 */
void dfs_seq_puts(struct dfs_seq_file *seq, const char *s)
{
    int len = strlen(s);

    if (seq->count + len >= seq->size)
    {
        dfs_seq_overflow(seq);
        return;
    }
    rt_memcpy(seq->buf + seq->count, s, len);
    seq->count += len;
}

/**
 * write arbitrary data to buffer
 */
int dfs_seq_write(struct dfs_seq_file *seq, const void *data, size_t len)
{
    if (seq->count + len < seq->size)
    {
        rt_memcpy(seq->buf + seq->count, data, len);
        seq->count += len;
        return 0;
    }
    dfs_seq_overflow(seq);
    return -1;
}

/**
 * write padding spaces to buffer
 */
void dfs_seq_pad(struct dfs_seq_file *seq, char c)
{
    int size = seq->pad_until - seq->count;

    if (size > 0)
    {
        if (size + seq->count > seq->size)
        {
            dfs_seq_overflow(seq);
            return;
        }
        rt_memset(seq->buf + seq->count, ' ', size);
        seq->count += size;
    }

    if (c)
    {
        dfs_seq_putc(seq, c);
    }
}

#if 1
/* test demo */

static char *txt[4] = {
    "text1",
    "text2",
    "text3",
    "text4",
};

static void *seq_test_start(struct dfs_seq_file *seq, off_t *index)
{
    off_t i = *index; // seq->index

    if (i >= 0 && i < 4)
    {
        return txt[i];
    }

    return RT_NULL;
}

static void seq_test_stop(struct dfs_seq_file *seq, void *data)
{
}

static void *seq_test_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    off_t i = *index + 1; // seq->index

    *index = i;

    if (i >= 0 && i < 4)
    {
        return txt[i];
    }

    return RT_NULL;
}

static int seq_test_show(struct dfs_seq_file *seq, void *data)
{
    const char *text = (const char *)data;

    dfs_seq_setwidth(seq, 20);
    dfs_seq_puts(seq, "puts ");
    dfs_seq_putc(seq, 'c');
    dfs_seq_write(seq, " write", 6);
    dfs_seq_printf(seq, " %s", text);
    dfs_seq_pad(seq, 0);

    return 0;
}

static const struct dfs_seq_ops _test_ops = {
    .start  = seq_test_start,
    .stop   = seq_test_stop,
    .next   = seq_test_next,
    .show   = seq_test_show,
};

static int dfs_seq_test(int argc, char **argv)
{
    struct dfs_file file = {0};
    int ret = dfs_seq_open(&file, &_test_ops);

    if (ret == 0)
    {
        char buf[256] = {0};
        off_t pos = (argc > 1) ? atoi(argv[1]) : 0;
        ssize_t len = (argc > 2) ? atoi(argv[2]) : 255;

        if (len > 255)
        {
            len = 255;
            rt_kprintf("buf len is %d, max read is 255\n", 256, len);
        }

        len = dfs_seq_read(&file, buf, len, &pos);
        buf[len] = '\0';

        rt_kprintf("show: \"%s\" len: %d\n", buf, len);
        dfs_seq_release(&file);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(dfs_seq_test, seq_test, seq_test[pos][read_len]);
#endif
