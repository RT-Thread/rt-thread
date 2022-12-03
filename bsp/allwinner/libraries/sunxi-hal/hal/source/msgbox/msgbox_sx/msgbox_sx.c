#include "hal_msgbox.h"
#include "bitops.h"
#include "msgbox_sx.h"
#include "compiler_attributes.h"


#define MSGBOX_CTRL_REG_OFFSET    0x00
#define MSGBOX_VER_REG_OFFSET     0x10
#define MSGBOX_IRQ_EN_REG_OFFSET  0x40
#define MSGBOX_IRQ_STATUS_OFFSET  0x50
#define MSGBOX_FIFO_STATUS_OFFSET 0x100
#define MSGBOX_FIFO_STATUS_MASK   BIT(0)
#define MSGBOX_MSG_STATUS_OFFSET  0x140
#define MSGBOX_MSG_STATUS_MASK    0x0f
#define MSGBOX_MSG_QUEUE_OFFSET   0x180

static int msg_queue_t_set(struct messagebox *mb, int queue)
{
    int user = mb->this_user;
    int offset_reg = (queue / 4 ) * 4 + MSGBOX_CTRL_REG_OFFSET;
    int offset_bit_t = 4 + ((queue % 4) * 8 );
    int offset_bit_r = ((queue % 4) * 8 );
    unsigned long *reg = (unsigned long *)(mb->base + offset_reg);
    unsigned long data;

    if (queue >= MSGBOX_MAX_QUEUE || user >= MSGBOX_MAX_USER)
        return -EINVAL;

    data = *reg;
    data &= ~(BIT(offset_bit_r) | BIT(offset_bit_t));

    if (user)
        *reg = data | BIT(offset_bit_t);
    else
        *reg = data | BIT(offset_bit_r);

    return 0;
}

static int msg_queue_r_set(struct messagebox *mb, int queue)
{
    int user = mb->this_user;
    int offset_reg = (queue / 4 ) * 4 + MSGBOX_CTRL_REG_OFFSET;
    int offset_bit_t = 4 + ((queue % 4) * 8 );
    int offset_bit_r = ((queue % 4) * 8 );
    unsigned long *reg = (unsigned long *)(mb->base + offset_reg);
    unsigned long data;

    if (queue >= MSGBOX_MAX_QUEUE || user >= MSGBOX_MAX_USER)
        return -EINVAL;

    data = *reg;
    data &= ~(BIT(offset_bit_r) | BIT(offset_bit_t));

    if (user)
        *reg = data | BIT(offset_bit_r);
    else
        *reg = data | BIT(offset_bit_t);

    return 0;
}

static int msg_queue_irq_t(struct messagebox *mb, int queue, int en)
{
    int user = mb->this_user;
    long *reg = (long *)(mb->base + MSGBOX_IRQ_EN_REG_OFFSET + user * 0x20);
    int offset_bit = 1 + (queue << 1);

    if (queue >= MSGBOX_MAX_QUEUE || user >= MSGBOX_MAX_USER)
        return -EINVAL;

    if (en)
        *reg = SET_BIT(*reg, offset_bit);
    else
        *reg = CLR_BIT(*reg, offset_bit);

    return 0;
}

static int msg_queue_irq_r(struct messagebox *mb, int queue, int en)
{
    int user = mb->this_user;
    long *reg = (long *)(mb->base + MSGBOX_IRQ_EN_REG_OFFSET + user * 0x20);
    int offset_bit = (queue << 1);

    if (queue >= MSGBOX_MAX_QUEUE || user >= MSGBOX_MAX_USER)
        return -EINVAL;

    if (en)
        *reg = SET_BIT(*reg, offset_bit);
    else
        *reg = CLR_BIT(*reg, offset_bit);

    return 0;
}

/*
 * static int msg_queue_status_pending(struct messagebox *mb, int queue)
 * {
 *         int user = mb->this_user;
 *
 *         if (queue >= MSGBOX_MAX_QUEUE || user >= MSGBOX_MAX_USER)
 *                 return -EINVAL;
 *
 *         return 0;
 * }
 */

static __maybe_unused int msg_queue_is_full(struct messagebox *mb, int queue)
{
    long *reg = (long *)(mb->base + MSGBOX_FIFO_STATUS_OFFSET + queue * 4);

    if (queue >= MSGBOX_MAX_QUEUE)
        return -EINVAL;

    if (*reg & MSGBOX_FIFO_STATUS_MASK)
        return 1;

    return 0;
}

static int msg_queue_msg_cnt_sx(struct messagebox *mb, int queue)
{
    long *reg = (long *)(mb->base + MSGBOX_MSG_STATUS_OFFSET + 4 * queue);

    if (queue >= MSGBOX_MAX_QUEUE)
        return -EINVAL;

    return *reg & MSGBOX_MSG_STATUS_MASK;
}

static int msg_queue_read_sx(struct messagebox *mb, int queue, unsigned long *read)
{
    long *reg = (long *)(mb->base + MSGBOX_MSG_QUEUE_OFFSET + 4 * queue);

    *read = *reg;

    return 0;
}

static int msg_queue_write_sx(struct messagebox *mb, int queue,
               unsigned long write)
{
    long *reg = (long *)(mb->base + MSGBOX_MSG_QUEUE_OFFSET + 4 * queue);

    *reg = write;

    return 0;
}

static inline unsigned long msg_irq_enable_get(struct messagebox *mb)
{
    int user = mb->this_user;
    long *reg = (long *)(mb->base + MSGBOX_IRQ_EN_REG_OFFSET + user * 0x20);

    return *reg;
}

static inline unsigned long msg_irq_status(struct messagebox *mb)
{
    int user = mb->this_user;
    long *reg = (long *)(mb->base + MSGBOX_IRQ_STATUS_OFFSET + 0x20 * user);

    if (user >= MSGBOX_MAX_USER)
        return -EINVAL;

    return *reg;
}

static inline int msg_irq_clear(struct messagebox *mb, unsigned long clr)
{
    int user = mb->this_user;
    long *reg = (long *)(mb->base + MSGBOX_IRQ_STATUS_OFFSET + 0x20 * user);

    if (user >= MSGBOX_MAX_USER)
        return -EINVAL;

    *reg = clr;

    return 0;
}

int msg_irq_handler_sx(int i, void *d)
{
    int channel;
    struct messagebox *mb = d;
    unsigned long status = msg_irq_status(mb);
    unsigned long enable = msg_irq_enable_get(mb);


    for (channel = 0; channel < MSGBOX_MAX_QUEUE; channel++) {
        unsigned long tbit = channel << 1;
        struct msg_channel *h = &mb->msg_handler[channel];

        tbit = (1 << tbit) | (1 << (tbit + 1));
        if ((tbit & status & enable) && h->cb_of_msg_queue) {
            h->cb_of_msg_queue(channel, h);
        }
    }

    msg_irq_clear(mb, status & enable);

    return 0;
}

static inline int
msg_channel_set_direction_sx(struct messagebox *mb, int channel,
                 enum msgbox_channel_direction dir)
{
    if (dir == MSGBOX_CHANNEL_SEND)
        return msg_queue_t_set(mb, channel);
    else
        return msg_queue_r_set(mb, channel);
}

static inline int msg_channel_irq_set_sx(struct messagebox *mb, int channel,
                     int enable)
{
    struct msg_channel *ch;

    if (channel >= MSGBOX_MAX_QUEUE)
        return -EINVAL;

    ch = &mb->msg_handler[channel];
    if (ch->dir == MSGBOX_CHANNEL_SEND)
        return msg_queue_irq_t(mb, channel, enable);
    else
        return msg_queue_irq_r(mb, channel, enable);
}

int msg_ops_init_sx(struct messagebox *mb)
{

    mb->channel_set_direction = msg_channel_set_direction_sx;
    mb->channel_irq_set = msg_channel_irq_set_sx;
    mb->channel_fifo_len = msg_queue_msg_cnt_sx;
    mb->channel_read = msg_queue_read_sx;
    mb->channel_write = msg_queue_write_sx;

    return 0;
}

