/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_IRQ_H__
#define __BL_IRQ_H__
void bl_irq_enable(unsigned int source);
void bl_irq_disable(unsigned int source);
typedef enum {
    BL_IRQ_EXCEPTION_TYPE_LOAD_MISALIGN,
    BL_IRQ_EXCEPTION_TYPE_STORE_MISALIGN,
    BL_IRQ_EXCEPTION_TYPE_ACCESS_ILLEGAL,
    BL_IRQ_EXCEPTION_TYPE_ILLEGAL_INSTRUCTION,
} BL_IRQ_EXCEPTION_TYPE_T;

struct irq_ctx {
    char *name;
    int irqnum;
    uint64_t irq_run_time;
};

struct irq_ctx **bl_irq_ctx_list(int *num);
void bl_irq_exception_trigger(BL_IRQ_EXCEPTION_TYPE_T type, void *ptr);

void bl_irq_init(void);
/*The following section define the IRQ handler for other files*/
void bl_sec_aes_IRQHandler(void);
void bl_sec_sha_IRQHandler(void);
void bl_sec_pka_IRQHandler(void);
void bl_dma_IRQHandler(void);
void intc_irq(void);//MAC IRQ
void bl_irq_handler(void);//IPC host IRQ
void bl_irq_register_with_ctx(int irqnum, void *handler, void *ctx);
void bl_irq_register(int irqnum, void *handler);
void bl_irq_unregister(int irqnum, void *handler);
void bl_irq_ctx_get(int irqnum, void **ctx);


int bl_irq_save(void);
void bl_irq_restore(int flags);
void __attribute__((noreturn)) bl_sys_abort(const char *details);

#define GLOBAL_IRQ_SAVE()  if (1) { \
  int ____global_prev_mie_irq____ = bl_irq_save();

#define GLOBAL_IRQ_RESTORE() \
  bl_irq_restore(____global_prev_mie_irq____ ); \
}
#endif
