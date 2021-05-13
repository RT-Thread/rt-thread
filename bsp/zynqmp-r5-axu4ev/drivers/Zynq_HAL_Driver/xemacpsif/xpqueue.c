/*
 * Copyright (C) 2007 - 2019 Xilinx, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 */

#include <stdlib.h>

#include "netif/xpqueue.h"
#include "xil_printf.h"

#define NUM_QUEUES	2

pq_queue_t pq_queue[NUM_QUEUES];

pq_queue_t *
pq_create_queue()
{
	static int i;
	pq_queue_t *q = NULL;

	if (i >= NUM_QUEUES) {
		xil_printf("ERR: Max Queues allocated\n\r");
		return q;
	}

	q = &pq_queue[i++];

	if (!q)
		return q;

	q->head = q->tail = q->len = 0;

	return q;
}

int
pq_enqueue(pq_queue_t *q, void *p)
{
	if (q->len == PQ_QUEUE_SIZE)
		return -1;

	q->data[q->head] = p;
	q->head = (q->head + 1)%PQ_QUEUE_SIZE;
	q->len++;

	return 0;
}

void*
pq_dequeue(pq_queue_t *q)
{
	int ptail;

	if (q->len == 0)
		return NULL;

	ptail = q->tail;
	q->tail = (q->tail + 1)%PQ_QUEUE_SIZE;
	q->len--;

	return q->data[ptail];
}

int
pq_qlength(pq_queue_t *q)
{
	return q->len;
}
