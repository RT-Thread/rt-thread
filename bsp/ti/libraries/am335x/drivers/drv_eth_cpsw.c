#include <netif/ethernetif.h>
#include <lwipopts.h>
#include <interrupt.h>
#include <am33xx.h>
#include "armv7a/am335x/evmAM335x.h"

/*
** CPSW-specific lwIP interface/porting layer code.
*/
#include "ports/cpsw/include/netif/cpswif.h"

#define DBG_TAG "drv.cpsw"
#include <rtdbg.h>

/*
** The lwIP network interface structure for CPSW ports.
*/
#ifdef CPSW_DUAL_MAC_MODE
static struct netif *cpswNetIF[MAX_CPSW_INST * MAX_SLAVEPORT_PER_INST];
#else
static struct netif *cpswNetIF[MAX_CPSW_INST];
#endif

/*
** Helper to identify ports
*/
static struct cpswportif cpswPortIf[MAX_CPSW_INST * MAX_SLAVEPORT_PER_INST];

static struct eth_device eth0;

static void CPSWCore0RxIsr(int vector, void *param)
{
    struct eth_device *ethif = param;
    struct cpswportif *cpswif = ethif->parent.user_data;

    //eth_device_ready(ethif);
    cpswif_rx_inthandler(cpswif->inst_num, cpswNetIF);
}

static void CPSWCore0TxIsr(int vector, void *param)
{
    struct eth_device *ethif = param;
    struct cpswportif *cpswif = ethif->parent.user_data;

    cpswif_tx_inthandler(cpswif->inst_num);
}

/*
** Set up the ARM Interrupt Controller for generating interrupt
*/
static void AintcCPSWIntrSetUp(void)
{
    rt_hw_interrupt_install(CPSW_RX_INT0, CPSWCore0RxIsr, &eth0, "cpsw_rx");
    rt_hw_interrupt_control(CPSW_RX_INT0, 0, 0);
    rt_hw_interrupt_umask(CPSW_RX_INT0);

    rt_hw_interrupt_install(CPSW_TX_INT0, CPSWCore0TxIsr, &eth0, "cpsw_tx");
    rt_hw_interrupt_control(CPSW_TX_INT0, 0, 0);
    rt_hw_interrupt_umask(CPSW_TX_INT0);
}

/* cpsw initialization function */
static rt_err_t rt_cpsw_eth_init(rt_device_t dev)
{
    struct eth_device *ethif = rt_container_of(dev, struct eth_device, parent);
    struct cpswportif *cpswif = ethif->parent.user_data;
    u32_t if_num;

    if_num = (cpswif->inst_num * MAX_SLAVEPORT_PER_INST) + cpswif->port_num - 1;
    cpswNetIF[if_num] = ethif->netif;

    cpswif_init(ethif->netif);
    eth_device_linkchange(ethif, RT_TRUE);

    return RT_EOK;
}

static rt_err_t rt_cpsw_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("cpsw open");
    return RT_EOK;
}

static rt_err_t rt_cpsw_eth_close(rt_device_t dev)
{
    LOG_D("cpsw close");
    return RT_EOK;
}

static rt_size_t rt_cpsw_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("cpsw read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_cpsw_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("cpsw write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_cpsw_eth_control(rt_device_t dev, int cmd, void *args)
{
    struct eth_device *ethif = rt_container_of(dev, struct eth_device, parent);
    struct cpswportif *cpswif = ethif->parent.user_data;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, cpswif->eth_addr, sizeof(cpswif->eth_addr));
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit data*/
rt_err_t rt_cpsw_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct eth_device *ethif = rt_container_of(dev, struct eth_device, parent);

    return cpswif_output(ethif->netif, p);
}

/* receive data*/
struct pbuf *rt_cpsw_eth_rx(rt_device_t dev)
{
    //struct eth_device *ethif = rt_container_of(dev, struct eth_device, parent);
    //struct cpswportif *cpswif = ethif->parent.user_data;

    //cpswif_rx_inthandler(cpswif->inst_num, cpswNetIF);

    // yzq: alread inputted
    return RT_NULL;
}

/* Register the cpsw device */
static int rt_hw_cpsw_eth_init(void)
{
    rt_err_t state = RT_EOK;

    CPSWPinMuxSetup();
    CPSWClkEnable();

    /* Chip configuration RGMII selection */
    EVMPortRGMIIModeSelect();

    /* Get the MAC address */
    EVMMACAddrGet(0, cpswPortIf[0].eth_addr);
    EVMMACAddrGet(1, cpswPortIf[1].eth_addr);

    AintcCPSWIntrSetUp();

    cpswPortIf[0].inst_num = 0;
    cpswPortIf[0].port_num = 1;

#ifdef RT_USING_CPSW0_PORT2
    cpswPortIf[1].inst_num = 0;
    cpswPortIf[1].port_num = 2;
#endif

    eth0.parent.init       = rt_cpsw_eth_init;
    eth0.parent.open       = rt_cpsw_eth_open;
    eth0.parent.close      = rt_cpsw_eth_close;
    eth0.parent.read       = rt_cpsw_eth_read;
    eth0.parent.write      = rt_cpsw_eth_write;
    eth0.parent.control    = rt_cpsw_eth_control;
    eth0.parent.user_data  = &cpswPortIf[0];

    eth0.eth_rx     = rt_cpsw_eth_rx;
    eth0.eth_tx     = rt_cpsw_eth_tx;

    /* register eth device */
    state = eth_device_init(&eth0, "e0");
    if (RT_EOK == state)
    {
        LOG_D("cpsw device init success");
    }
    else
    {
        LOG_E("cpsw device init faild: %d", state);
        state = -RT_ERROR;
        goto __exit;
    }

__exit:

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_cpsw_eth_init);

