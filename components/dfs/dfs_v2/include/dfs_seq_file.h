/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DFS_SEQ_FILE_H__
#define __DFS_SEQ_FILE_H__

#include <dfs.h>
#include <dfs_fs.h>

struct dfs_seq_ops;

/**
 * Sequence file control structure
 */
struct dfs_seq_file
{
    char *buf;          /* Data buffer pointer */
    size_t size;        /* Total buffer size in bytes */
    size_t from;        /* Start offset of valid data in buffer */
    size_t count;       /* Length of valid data in buffer */
    size_t pad_until;   /* Padding target position for alignment */

    off_t index;        /* Current item index in sequence */
    off_t read_pos;     /* Current read position in file */

    struct rt_mutex lock; /* Mutex for thread safety */

    const struct dfs_seq_ops *ops; /* Operation function table */
    const struct dfs_file *file;  /* Associated file object */
    void *data;         /* Private data pointer */
};

/**
 * Sequence file operations structure
 */
struct dfs_seq_ops
{
    void *(*start)(struct dfs_seq_file *seq, off_t *index);  /* Start sequence traversal */
    void (*stop)(struct dfs_seq_file *seq, void *data);      /* Stop sequence traversal */
    void *(*next)(struct dfs_seq_file *seq, void *data, off_t *index); /* Get next item in sequence */
    int (*show)(struct dfs_seq_file *seq, void *data);  /* Show current item */
};

/**
 * check if the buffer is full
 */
static inline rt_bool_t dfs_seq_is_full(struct dfs_seq_file *seq)
{
    return seq->count == seq->size;
}

/**
 * set padding width size
 */
static inline void dfs_seq_setwidth(struct dfs_seq_file *seq, size_t size)
{
    seq->pad_until = seq->count + size;
}

int dfs_seq_open(struct dfs_file *file, const struct dfs_seq_ops *ops);
ssize_t dfs_seq_read(struct dfs_file *file, void *buf, size_t size, off_t *pos);
off_t dfs_seq_lseek(struct dfs_file *file, off_t offset, int whence);
int dfs_seq_release(struct dfs_file *file);
int dfs_seq_write(struct dfs_seq_file *seq, const void *data, size_t len);

void dfs_seq_vprintf(struct dfs_seq_file *seq, const char *fmt, va_list args);
void dfs_seq_printf(struct dfs_seq_file *seq, const char *fmt, ...);
void dfs_seq_putc(struct dfs_seq_file *seq, char c);
void dfs_seq_puts(struct dfs_seq_file *seq, const char *s);
void dfs_seq_pad(struct dfs_seq_file *seq, char c);

#endif