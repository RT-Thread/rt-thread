#ifndef __MESSAGEBOX__H__
#define __MESSAGEBOX__H__

#include <stdint.h>

enum cpu_type {
    ARM_MSG_CORE,
    RISC_V_MSG_CORE,
    MIPS_MSG_CORE,
    OPENRISC_MSG_CORE,
    DSP0_MSG_CORE,
    DSP1_MSG_CORE,
};

struct msg_endpoint {
    uint32_t local_amp;
    uint32_t remote_amp;
    uint32_t write_ch;
    uint32_t read_ch;
    struct msg_endpoint *next;
    void *data;
    void (*rec)(uint32_t l, void *d);
    void (*tx_done)(void *d);
    /* use in driver */
    void *private;
};

uint32_t hal_msgbox_init(void);

uint32_t hal_msgbox_alloc_channel(struct msg_endpoint *edp, uint32_t remote,
                  uint32_t read, uint32_t write);

uint32_t hal_msgbox_channel_send(struct msg_endpoint *edp, uint8_t *bf,
                 uint32_t len);

void hal_msgbox_free_channel(struct msg_endpoint *edp);

#endif /* __MESSAGEBOX__H__ */

