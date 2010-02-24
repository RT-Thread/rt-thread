#ifndef __NET_BUF_H__
#define __NET_BUF_H__

#include <rtthread.h>
#include "board.h"

/* SRAM buffer pool routine */
rt_size_t sbuf_get_size(void);
void* sbuf_alloc(void);
void sbuf_release(void* ptr);

#if STM32_EXT_SRAM
/* net buffer routine */
void net_buf_init(rt_size_t size);

rt_size_t net_buf_read(rt_uint8_t* buffer, rt_size_t length);

int net_buf_start_job(rt_size_t (*fetch)(rt_uint8_t* ptr, rt_size_t len, void* parameter),
	void (*close)(void* parameter),
	void* parameter);
void net_buf_stop_job(void);

#endif

#endif
