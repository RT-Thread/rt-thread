/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef ACW_H_
#define ACW_H_
#include <rtthread.h>
#include <rtdevice.h>
#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif
#include <rthw.h>
#define ACW_CAP_DMA_CHAN 2
#define ACW_PLY_DMA_CHAN 3
typedef unsigned long long dma_addr_t;
struct scatterlist {
#ifdef CONFIG_DEBUG_SG
	unsigned long	sg_magic;
#endif
	unsigned long	page_link;
	unsigned int	offset;
	unsigned int	length;
	dma_addr_t	dma_address;
#ifdef CONFIG_NEED_SG_DMA_LENGTH
	unsigned int	dma_length;
#endif
};
#define readl(a)          (*(volatile rt_uint32_t   *)(a))
#define rkqueue_struct		rt_workqueue
#define work_struct				rt_work
#define INIT_WORK(work,func)	rt_work_init(work,func,RT_NULL);
#define queue_work				rt_workqueue_dowork


//timer
#define timer_list				rt_timer
#define wait_queue_head_t				struct rt_event
#define init_waitqueue_head(event_t) 		rt_event_init(event_t, "audio_event", RT_IPC_FLAG_FIFO)
typedef enum{
	AC_SR_8K   = 8000,
	AC_SR_16K  = 16000,
	AC_SR_32K  = 32000,
	AC_SR_441K = 44100,
	AC_SR_48K  = 48000,
} FH_AC_SAMPLE_RATE_E;

typedef enum{
	AC_BW_8  = 8,
	AC_BW_16 = 16,
	AC_BW_24 = 24,
} FH_AC_BIT_WIDTH_E;

enum io_select{
	mic_in = 0,
	line_in = 1,
	speaker_out = 2,
	line_out = 3,
};

struct fh_audio_cfg_arg{
	enum io_select io_type;
	int volume;
	int rate;
	int frame_bit;
	int channels;
	int buffer_size;
	int period_size;
};
typedef struct{
	unsigned int len;
	unsigned char *data;
}FH_AC_FRAME_S;

typedef enum{
	FH_AC_MIC_IN = 0,
	FH_AC_LINE_IN = 1,
	FH_AC_SPK_OUT = 2,
	FH_AC_LINE_OUT = 3
}FH_AC_IO_TYPE_E;


typedef struct {
	FH_AC_IO_TYPE_E io_type;
	FH_AC_SAMPLE_RATE_E sample_rate;
	FH_AC_BIT_WIDTH_E bit_width;
	unsigned int channels;
	unsigned int period_size;
	unsigned int volume;
} FH_AC_CONFIG;

struct device_dma_parameters {
	/*
	 * a low level driver may set these to teach IOMMU code about
	 * sg limitations.
	 */
	unsigned int max_segment_size;
	unsigned long segment_boundary_mask;
};

struct list_head {
    struct list_head *next;
    struct list_head *prev;
};
struct dma_coherent_mem {
	void		*virt_base;
	dma_addr_t	device_base;
	int		size;
	int		flags;
	unsigned long	*bitmap;
};
struct device_acw{
	unsigned long long		*dma_mask;	/* dma mask (if dma'able device) */
	unsigned long long		coherent_dma_mask;/* Like dma_mask, but for
					     alloc_coherent mappings as
					     not all hardware supports
					     64 bit addresses for consistent
					     allocations such descriptors. */
	struct device_dma_parameters *dma_parms;

	struct list_head	dma_pools;

	struct dma_coherent_mem	*dma_mem;
};
#define false 0
#define true  1



#define	AC_INIT_CAPTURE_MEM    	    0x10
#define	AC_INIT_PLAYBACK_MEM        0x11


#define AC_SET_VOL                  0x12
#define AC_SET_INPUT_MODE           0x13
#define AC_SET_OUTPUT_MODE          0x14


#define AC_AI_EN                    0x15
#define AC_AO_EN                    0x16
#define AC_AI_DISABLE               0x17
#define AC_AO_DISABLE       		0x18
#define AC_AI_PAUSE               	0x19
#define AC_AI_RESUME          		0x1a
#define AC_AO_PAUSE              	0x1b
#define AC_AO_RESUME          		0x1c
#define AC_MIC_BOOST          		0x1d

#define POLLIN		0x001		/* There is data to read.  */
#define POLLPRI		0x002		/* There is urgent data to read.  */
#define POLLOUT		0x004		/* Writing now will not block.  */


/* These values are defined in XPG4.2.  */
# define POLLRDNORM	0x040		/* Normal data may be read.  */
# define POLLRDBAND	0x080		/* Priority data may be read.  */
# define POLLWRNORM	0x100		/* Writing now will not block.  */
# define POLLWRBAND	0x200		/* Priority data may be written.  */



/* These are extensions for Linux.  */
# define POLLMSG	0x400
# define POLLREMOVE	0x1000
# define POLLRDHUP	0x2000


/* Event types always implicitly polled for.  These bits need not be set in
   `events', but they will appear in `revents' to indicate the status of
   the file descriptor.  */
#define POLLERR		0x008		/* Error condition.  */
#define POLLHUP		0x010		/* Hung up.  */
#define POLLNVAL	0x020		/* Invalid polling request.  */

#define	EPERM		 1	/* Operation not permitted */
#define	ENOENT		 2	/* No such file or directory */
#define	ESRCH		 3	/* No such process */
#define	EINTR		 4	/* Interrupted system call */
#define	EIO		 5	/* I/O error */
#define	ENXIO		 6	/* No such device or address */
#define	E2BIG		 7	/* Argument list too long */
#define	ENOEXEC		 8	/* Exec format error */
#define	EBADF		 9	/* Bad file number */
#define	ECHILD		10	/* No child processes */
#define	EAGAIN		11	/* Try again */
#define	ENOMEM		12	/* Out of memory */
#define	EACCES		13	/* Permission denied */
#define	EFAULT		14	/* Bad address */
#define	ENOTBLK		15	/* Block device required */
#define	EBUSY		16	/* Device or resource busy */
#define	EEXIST		17	/* File exists */
#define	EXDEV		18	/* Cross-device link */
#define	ENODEV		19	/* No such device */
#define	ENOTDIR		20	/* Not a directory */
#define	EISDIR		21	/* Is a directory */
#define	EINVAL		22	/* Invalid argument */
#define	ENFILE		23	/* File table overflow */
#define	EMFILE		24	/* Too many open files */
#define	ENOTTY		25	/* Not a typewriter */
#define	ETXTBSY		26	/* Text file busy */
#define	EFBIG		27	/* File too large */
#define	ENOSPC		28	/* No space left on device */
#define	ESPIPE		29	/* Illegal seek */
#define	EROFS		30	/* Read-only file system */
#define	EMLINK		31	/* Too many links */
#define	EPIPE		32	/* Broken pipe */
#define	EDOM		33	/* Math argument out of domain of func */
#define	ERANGE		34	/* Math result not representable */
extern void  fh_audio_init(void);
extern void fh_acw_test();
#endif
