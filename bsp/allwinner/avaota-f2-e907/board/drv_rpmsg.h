#ifndef DRV_RPMSG_H__
#define DRV_RPMSG_H__

#include <stdint.h>

int rpmsg_lite_init(int is_e907);
int rpmsg_lite_send(uint32_t data);
int rpmsg_lite_recv(uint32_t *data, uint32_t timeout_loops);
int rpmsg_lite_ack(uint32_t data);
uint32_t rpmsg_lite_msgbox_probe(void);

#endif
