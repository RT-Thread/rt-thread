#ifndef __modem_device_h__
#define __modem_device_h__

#include <rtthread.h>
#include <rtdevice.h>
#include <ppp/ppp.h>
#include <ppp/pppos.h>

struct rt_modem
{
    struct netif pppif;
    ppp_pcb *ppp;
    struct rt_completion comp;

    struct rt_serial_device *serial;
    rt_err_t (*prepare)(struct rt_modem *modem);
};

struct rt_serial_device* rt_modem_open_serial(const char *device_name);
void rt_modem_attach(struct rt_modem *modem);

#endif
