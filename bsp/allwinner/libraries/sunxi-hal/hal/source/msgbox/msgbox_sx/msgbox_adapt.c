#include "msgbox_sx.h"
#include "FreeRTOS.h"
#include "hal_msgbox.h"
#include "../platform-msgbox.h"

struct msgbox_adapt {
    struct messagebox *msgbox;
    struct msg_channel *msg_ch_send;
    struct msg_channel *msg_ch_rec;
    struct msg_endpoint *edp;
};

uint32_t hal_msgbox_init(void)
{
    return messagebox_init_sx();
}

static int func_cb_tx(unsigned long i, void *d)
{
    struct msgbox_adapt *adp = d;
    struct msg_endpoint *edp = adp->edp;

    if (edp->tx_done)
        edp->tx_done(edp->data);

    return 0;
}

static int func_cb_rec(unsigned long i, void *d)
{
    struct msgbox_adapt *adp = d;
    struct msg_endpoint *edp = adp->edp;

    if (edp->rec)
        edp->rec(i, edp->data);

    return 0;
}

uint32_t hal_msgbox_alloc_channel(struct msg_endpoint *edp, uint32_t remote,
                  uint32_t read, uint32_t write)
{
    struct msgbox_adapt *adp;
    struct messagebox *msg;
    struct msg_channel *chl;

    if (edp->remote_amp == ARM_MSG_CORE)
        msg = msgbox_cpu;
    else
        msg = msgbox_dsp;

    adp = pvPortMalloc(sizeof(struct msgbox_adapt));

    adp->msgbox = msg;
    adp->edp = edp;
    edp->private = adp;

    chl = msgbox_alloc_channel_sx(msg, read, MSGBOX_CHANNEL_RECEIVE,
                      func_cb_rec, adp);
    adp->msg_ch_rec = chl;

    chl = msgbox_alloc_channel_sx(msg, write, MSGBOX_CHANNEL_SEND,
                      func_cb_tx, adp);
    adp->msg_ch_send = chl;

    return 0;
}

uint32_t hal_msgbox_channel_send(struct msg_endpoint *edp, uint8_t *bf,
                 uint32_t len)
{
    struct msgbox_adapt *adp = edp->private;

    return msgbox_channel_send_data_sx(adp->msg_ch_send, bf, len);
}

void hal_msgbox_free_channel(struct msg_endpoint *edp)
{
    struct msgbox_adapt *adp = edp->private;

    msgbox_free_channel_sx(adp->msgbox, adp->msg_ch_rec);
    msgbox_free_channel_sx(adp->msgbox, adp->msg_ch_send);

    vPortFree(adp);
}


