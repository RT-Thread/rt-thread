#ifndef DRV_AMP_MAILBOX_H__
#define DRV_AMP_MAILBOX_H__

#include <stdint.h>

int amp_mailbox_init(int is_e907);
int amp_mailbox_send(uint32_t data);
int amp_mailbox_recv(uint32_t *data, uint32_t timeout_loops);
int amp_mailbox_ack(uint32_t data);
uint32_t amp_mailbox_msgbox_probe(void);

#endif
