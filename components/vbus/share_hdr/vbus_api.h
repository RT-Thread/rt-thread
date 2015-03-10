#ifndef __VBUS_API_H__
#define __VBUS_API_H__

#include "vbus_conf.h"

#define RT_VBUS_CHANNEL_NR   32

#define RT_VBUS_BLK_HEAD_SZ  4
#define RT_VBUS_MAX_PKT_SZ   (256 - RT_VBUS_BLK_HEAD_SZ)

#ifndef __ASSEMBLY__
#include <stddef.h> /* For size_t */

struct rt_vbus_blk
{
    unsigned char id;
    unsigned char qos;
    unsigned char len;
    unsigned char reserved;
    unsigned char data[60];
} __attribute__((packed));

struct rt_vbus_ring
{
    volatile size_t put_idx;
    volatile size_t get_idx;
    /* whether the writer is blocked on this ring. For RTT, it means the
     * central writer thread is waiting. For Linux, it means there are some
     * threads waiting for space to write.
     *
     * Note that we don't record whether there are reading thread blocked. When
     * there is new data, the other side will always be waked up. */
    volatile unsigned int blocked;
    struct rt_vbus_blk blks[RT_VMM_RB_BLK_NR];
};

enum
{
    RT_VBUS_CHN0_CMD_ENABLE,
    RT_VBUS_CHN0_CMD_DISABLE,
    RT_VBUS_CHN0_CMD_SET,
    RT_VBUS_CHN0_CMD_ACK,
    RT_VBUS_CHN0_CMD_NAK,
    /* If the recieving side reached high water mark. It has the right to
     * suspend the channel. All the server/client should know about this
     * command but the one that does not implement flow control could ignore
     * this command. */
    RT_VBUS_CHN0_CMD_SUSPEND,
    RT_VBUS_CHN0_CMD_RESUME,
    RT_VBUS_CHN0_CMD_MAX,
};

enum rt_vbus_chn_status
{
    /* initial state, available for reuse */
    RT_VBUS_CHN_ST_AVAILABLE,
    /* ACK DISABLE send(CS) or received(CS), but not ready for reuse.(the
     * channel is not closed by this end) */
    RT_VBUS_CHN_ST_CLOSED,
    /* ENABLE send(client) or received(server) */
    RT_VBUS_CHN_ST_ESTABLISHING,
    /* ACK SET send(C) or received(S) */
    RT_VBUS_CHN_ST_ESTABLISHED,
    /* Channel suspended by flow control. */
    RT_VBUS_CHN_ST_SUSPEND,
    /* DISABLE received(CS) */
    RT_VBUS_CHN_ST_CLOSING,
};
#endif

#undef BUILD_ASSERT
/* borrowed from http://lxr.linux.no/linux+v2.6.26.5/include/linux/kernel.h#L494 */
#define BUILD_ASSERT(condition) ((void)sizeof(char[1 - 2*!(condition)]))

/* max length of a channel name, including the \0 */
#define RT_VBUS_CHN_NAME_MAX   16

#endif /* end of include guard: __VBUS_API_H__ */

