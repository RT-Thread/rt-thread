/*
 * COPYRIGHT (C) 2018, Real-Thread Information Technology Ltd
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-06-09     Grissiom     version 2.0.2; add comment
 * 2015-01-06     Grissiom     version 2.0.3; API change, no functional changes
 */
#ifndef __VBUS_H__
#define __VBUS_H__

#include <vbus_api.h>

int rt_vbus_init(void *outr, void *inr);

void rt_vbus_resume_out_thread(void);

/** Post data on channel.
 *
 * @param chnr the channel number
 * @param prio the priority of the data
 * @param datap pointer to the actual data
 * @param size number of byte of the data
 * @param timeout the value used in the blocking API
 *
 * Note: rt_vbus_post is an asynchronous function that when it returns, the
 * @datap and @size is recorded in the post queue at least but there is no
 * guarantee that the data is copied into the ring buffer. To avoid data
 * corruption, you need to wait on the RT_VBUS_EVENT_ID_TX event.
 *
 * However, if you just post static data such as static string, there is no
 * need to wait.
 *
 * @sa rt_vbus_register_listener .
 */
rt_err_t rt_vbus_post(rt_uint8_t chnr,
                      rt_uint8_t prio,
                      const void *datap,
                      rt_size_t size,
                      rt_int32_t timeout);

struct rt_vbus_data {
    /* Number of bytes in current data package. */
    unsigned char size;
    /* Used internally in VBus. Don't modify this field as it may corrupt the
     * receive queue. */
    struct rt_vbus_data *next;
    /* Data follows the struct */
};

struct rt_vbus_wm_cfg {
	unsigned int low, high;
};

struct rt_vbus_request {
	unsigned char prio;
	const char *name;
	int is_server;
	struct rt_vbus_wm_cfg recv_wm, post_wm;
};

/** Request a channel.
 *
 * @return channel number. Negative if error happened.
 */
int rt_vbus_request_chn(struct rt_vbus_request *req, int timeout);

/** Close channel @chnr */
void rt_vbus_close_chn(unsigned char chnr);

/** Set the water mark level for posting into the channel @chnr. */
void rt_vbus_set_post_wm(unsigned char chnr, unsigned int low, unsigned int high);
/** Set the water mark level for receiving from the channel @chnr. */
void rt_vbus_set_recv_wm(unsigned char chnr, unsigned int low, unsigned int high);

typedef void (*rt_vbus_event_listener)(void *ctx);

enum rt_vbus_event_id {
    /* On a packet received in channel. */
    RT_VBUS_EVENT_ID_RX,
    /* On the data of rt_vbus_post has been written to the ring buffer. */
    RT_VBUS_EVENT_ID_TX,
    /* On the channel has been closed. */
    RT_VBUS_EVENT_ID_DISCONN,
    RT_VBUS_EVENT_ID_MAX,
};

/** Register callback @indi on the event @eve on the @chnr.
 *
 * @ctx will passed to @indi on calling the @indi.
 */
void rt_vbus_register_listener(unsigned char chnr,
                               enum rt_vbus_event_id eve,
                               rt_vbus_event_listener indi,
                               void *ctx);

/** Listen on any events happen on the @chnr for @timeout ticks.
 *
 * This function blocks until events occur or timeout happened.
 */
rt_err_t rt_vbus_listen_on(rt_uint8_t chnr,
                           rt_int32_t timeout);

/** Push a data package into the receive queue of the channel @chnr. */
void rt_vbus_data_push(unsigned int chnr,
                       struct rt_vbus_data *data);
/** Pop a data package from the receive queue of the channel @chnr.
 *
 * The actual data is following the struct rt_vbus_data. After using it, it
 * should be freed by rt_free.
 */
struct rt_vbus_data* rt_vbus_data_pop(unsigned int chnr);

struct rt_vbus_dev
{
    /* Runtime infomations. */
    rt_uint8_t chnr;
    struct rt_vbus_data *act;
    rt_size_t pos;

    /* There will be a request for each channel. So no need to seperate them so
     * clearly. */
    struct rt_vbus_request req;
};

rt_err_t rt_vbus_chnx_init(void);
/** Get the corresponding channel number from the VBus device @dev. */
rt_uint8_t rt_vbus_get_chnnr(rt_device_t dev);
/** Register a call back on the other side disconnect the channel.
 *
 * @sa rt_vbus_register_listener .
 */
void rt_vbus_chnx_register_disconn(rt_device_t dev,
                                   rt_vbus_event_listener indi,
                                   void *ctx);

/* Commands for the device control interface. */
#define VBUS_IOCRECV_WM      0xD1
#define VBUS_IOCPOST_WM      0xD2
/** Configure event listener */
#define VBUS_IOC_LISCFG      0xD3

struct rt_vbus_dev_liscfg
{
    enum rt_vbus_event_id event;
    rt_vbus_event_listener listener;
    void *ctx;
};

int rt_vbus_shell_start(void);
#ifdef RT_USING_VBUS_RFS
int dfs_rfs_init(void);
#endif

/** VBus hardware init function.
 *
 * BSP should implement this function to initialize the interrupts etc.
 */
int rt_vbus_hw_init(void);

/** VBus ISR function.
 *
 * BSP should call this function when the interrupt from other core is
 * triggered. @param is not used by VBus and will pass to rt_vbus_hw_eoi.
 */
void rt_vbus_isr(int irqnr, void *param);

/** VBus End Of Interrupt function.
 *
 * This function will be called when VBus finished the ISR handling. BSP should
 * define this function to clear the interrupt flag etc.
 */
int rt_vbus_hw_eoi(int irqnr, void *param);

#endif /* end of include guard: __VBUS_H__ */
