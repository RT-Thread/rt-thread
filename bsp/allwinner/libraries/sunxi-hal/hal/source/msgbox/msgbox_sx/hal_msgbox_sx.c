#include "FreeRTOS.h"
#include "hal_msgbox.h"
#include "msgbox_sx.h"
#include "../platform-msgbox.h"
#include "hal_interrupt.h"
#include "hal_log.h"
#include "string.h"
#include "hal_clk.h"

struct messagebox *msgbox_dsp;
struct messagebox *msgbox_cpu;

int msgbox_sx_init_ccmu(void)
{
    if (hal_clock_enable(HAL_CLK_PERIPH_MSGBOX0) < 0) {
        hal_log_err("enable msgbox0 clk err!\n");
        return -1;
    }

    if (hal_clock_enable(HAL_CLK_PERIPH_MSGBOX1) < 0) {
        hal_log_err("enable msgbox1 clk err!\n");
        return -1;
    }

    if (hal_clock_enable(HAL_CLK_PERIPH_MSGBOXR) < 0) {
        hal_log_err("enable r_msgbox clk err!\n");
        return -1;
    }

    return 0;
}

struct messagebox *msgbox_init_sx(enum msgbox_direction dir)
{
    struct messagebox *mb = pvPortMalloc(sizeof(struct messagebox) +
                         sizeof(struct msg_channel) *
                             MSGBOX_MAX_QUEUE);

    if (!mb)
        return 0;

    /* for reset and gating */

    memset(mb, 0,
           sizeof(struct messagebox) +
               sizeof(struct msg_channel) * MSGBOX_MAX_QUEUE);
    if (dir == MSGBOX_DIRECTION_DSP) {
        mb->base = MSGBOX_DSP_DSP;
        mb->this_user = MSGBOX_DSP_DSP_USER;
    } else {
        mb->base = MSGBOX_CPU_DSP;
        mb->this_user = MSGBOX_CPU_DSP_USER;
    }

    msg_ops_init_sx(mb);

    if (dir == MSGBOX_DIRECTION_CPU) {
        irq_request(SUNXI_DSP_IRQ_MSGBOX0_DSP, msg_irq_handler_sx, mb);
        irq_enable(SUNXI_DSP_IRQ_MSGBOX0_DSP);
    } else {
        irq_request(SUNXI_DSP_IRQ_R_MSGBOX_DSP, msg_irq_handler_sx, mb);
        irq_enable(SUNXI_DSP_IRQ_R_MSGBOX_DSP);
    }

    return mb;
}

void msgbox_uninit_sx(struct messagebox *mb)
{
    irq_free(SUNXI_DSP_IRQ_MSGBOX0_DSP);
    vPortFree(mb);
}

/*
 * msgbox_rev_handler - rev interrupt handler function
 */
static int msgbox_rev_handler(int channel, void *c)
{
    struct msg_channel *ch = c;
    struct messagebox *mb = ch->mb;
    unsigned long data;

    while (mb->channel_fifo_len(mb, channel) > 0) {
        mb->channel_read(mb, channel, &data);
        if (ch->cb_rx)
            ch->cb_rx(data, ch->data);
    }
    return 0;
}

/*
 * msgbox_send_handler - send interrutp handler function
 */
static int msgbox_send_handler(int channel, void *c)
{
    struct msg_channel *ch = c;
    struct messagebox *mb = ch->mb;

    while (mb->channel_fifo_len(mb, channel) < MSGBOX_CHANNEL_DEPTH) {
        unsigned long i;
        unsigned long data = 0;

        if (ch->idx >= ch->len) {
            goto finish;
        }

        for (i = 0; i < sizeof(long); i++) {
            if (ch->idx < ch->len)
                data |= ch->send[ch->idx++] << (i << 3);
        }

        mb->channel_write(mb, channel, data);

    }

    return 0;

finish:
    mb->channel_irq_set(mb, channel, false);
    if (ch->cb_tx_done)
        ch->cb_tx_done(ch->idx, ch->data);

    return 0;
}


/**
 * msgbox_alloc_channel - alloc channel from msgbox
 * @func when function as send, it act as tx_done
 *       when function as rev, it act as word reveive.
 */
struct msg_channel *msgbox_alloc_channel_sx(struct messagebox *mb, int channel,
                     enum msgbox_channel_direction dir,
                     int (*func)(unsigned long, void *),
                     void *data)
{
    struct msg_channel *ch;

    if (!mb || channel >= MSGBOX_MAX_QUEUE)
        return 0;

    ch = &mb->msg_handler[channel];

    ch->mb = mb;
    ch->channel = channel;
    ch->data = data;
    ch->dir = dir;

    if (mb->channel_set_direction(mb, channel, dir))
        return 0;

    if (ch->dir == MSGBOX_CHANNEL_SEND) {
        ch->cb_of_msg_queue = msgbox_send_handler;
        ch->cb_tx_done = func;
    }
    else {
        ch->cb_of_msg_queue = msgbox_rev_handler;
        ch->cb_rx = func;

        mb->channel_irq_set(mb, channel, true);
    }

    return ch;
}

void msgbox_free_channel_sx(struct messagebox *mb, struct msg_channel *ch)
{
    if (!mb || ch->channel >= MSGBOX_MAX_QUEUE)
        return;

    mb->channel_irq_set(mb, ch->channel, false);

    ch->data = NULL;
    ch->cb_of_msg_queue = NULL;
    ch->cb_tx_done = NULL;
    ch->cb_rx = NULL;
}

int msgbox_channel_send_data_sx(struct msg_channel *ch, unsigned char *d,
                 size_t len)
{
    struct messagebox *mb = ch->mb;

    ch->send = d;
    ch->len = len;
    ch->idx = 0;

    mb->channel_irq_set(mb, ch->channel, true);

    return 0;
}

int messagebox_init_sx(void)
{
    msgbox_sx_init_ccmu();
    msgbox_dsp = msgbox_init_sx(MSGBOX_DIRECTION_DSP);
    msgbox_cpu = msgbox_init_sx(MSGBOX_DIRECTION_CPU);

    return 0;
}

