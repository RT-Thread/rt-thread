#ifndef __DRV_MOUSE_H__
#define __DRV_MOUSE_H__

int rt_hw_mouse_init(void);

struct mouse_info
{
    uint32_t type;
    uint32_t button;
    uint32_t x;
    uint32_t y;
    uint32_t ts;
    uint32_t id;
};

#define CMD_MOUSE_SET_NOTIFY 0  /* arg is shmid, in the shm, a sem point is given */

#endif