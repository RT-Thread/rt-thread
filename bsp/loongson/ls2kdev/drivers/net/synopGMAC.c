/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 * 2020-08-10     lizhirui     porting to ls2k
 */

#include <rtthread.h>
#include <rtdef.h>
//#include <lwip/pbuf.h>

#include "synopGMAC.h"
#include "mii.c"
#include "synopGMAC_debug.h"

#define RMII

#define PCI_BASE            (0xFE00001800)
#define Buffer_Size         2048
#define MAX_ADDR_LEN        6
#define NAMESIZE            16

#define LS1B_GMAC0_IRQ      34
#define BUS_SIZE_ALIGN(x) ((x+15)&~15)

#define DEFAULT_MAC_ADDRESS {0x00, 0x55, 0x7B, 0xB5, 0x7D, 0xF7}

u64 gmac_base = 0;
static u32 GMAC_Power_down;
extern void *plat_alloc_consistent_dmaable_memory(synopGMACdevice *pcidev, u32 size, u32 *addr) ;
extern s32 synopGMAC_check_phy_init(synopGMACPciNetworkAdapter *adapter) ;
extern int init_phy(synopGMACdevice *gmacdev);
dma_addr_t plat_dma_map_single(void *hwdev, void *ptr, u32 size);

void eth_rx_irq(int irqno, void *param);
static char Rx_Buffer[Buffer_Size];
static char Tx_Buffer[Buffer_Size];

struct pci_header
{
    uint16_t VendorID;
    uint16_t DeviceID;
    uint16_t Command;
    uint16_t Status;
    uint32_t RevisionID : 8;
    uint32_t ClassCode : 24;
    uint8_t CachelineSize;
    uint8_t LatencyTimer;
    uint8_t HeaderType;
    uint8_t BIST;
    uint32_t BaseAddressRegister[6];
    uint32_t CardbusCISPointer;
    uint16_t SubsystemVendorID;
    uint16_t SubsystemID;
    uint32_t ExpansionROMBaseAddress;
    uint32_t CapabilitiesPointer : 8;
    uint32_t resv1 : 24;
    uint32_t resv2;
    uint8_t InterruptLine;
    uint8_t InterruptPin;
    uint8_t Min_Gnt;
    uint8_t Max_Lat;
};

struct rt_eth_dev
{
    struct eth_device parent;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    char *name;
    int iobase;
    int state;
    int index;
    struct rt_timer link_timer;
    struct rt_timer rx_poll_timer;
    void *priv;
};
static struct rt_eth_dev eth_dev;
static struct rt_semaphore sem_ack, sem_lock;

/**
 * This sets up the transmit Descriptor queue in ring or chain mode.
 * This function is tightly coupled to the platform and operating system
 * Device is interested only after the descriptors are setup. Therefore this function
 * is not included in the device driver API. This function should be treated as an
 * example code to design the descriptor structures for ring mode or chain mode.
 * This function depends on the pcidev structure for allocation consistent dma-able memory in case
 * of linux.
 * This limitation is due to the fact that linux uses pci structure to allocate a dmable memory
 * - Allocates the memory for the descriptors.
 * - Initialize the Busy and Next descriptors indices to 0(Indicating first descriptor).
 * - Initialize the Busy and Next descriptors to first descriptor address.
 * - Initialize the last descriptor with the endof ring in case of ring mode.
 * - Initialize the descriptors in chain mode.
 * @param[in] pointer to synopGMACdevice.
 * @param[in] pointer to pci_device structure.
 * @param[in] number of descriptor expected in tx descriptor queue.
 * @param[in] whether descriptors to be created in RING mode or CHAIN mode.
 * \return 0 upon success. Error code upon failure.
 * \note This function fails if allocation fails for required number of descriptors in Ring mode,
 * but in chain mode
 * function returns -ESYNOPGMACNOMEM in the process of descriptor chain creation. once returned from
 * this function
 * user should for gmacdev->TxDescCount to see how many descriptors are there in the chain. Should
 * continue further
 * only if the number of descriptors in the chain meets the requirements
 */
s32 synopGMAC_setup_tx_desc_queue(synopGMACdevice *gmacdev, u32 no_of_desc, u32 desc_mode)
{
    s32 i;
    DmaDesc *bf1;

    DmaDesc *first_desc = NULL;

    dma_addr_t dma_addr;
    gmacdev->TxDescCount = 0;

    first_desc = (DmaDesc *)plat_alloc_consistent_dmaable_memory(gmacdev, sizeof(DmaDesc) * (no_of_desc), &dma_addr);

    if (first_desc == NULL)
    {
        rt_kprintf("Error in Tx Descriptors memory allocation\n");
        return -ESYNOPGMACNOMEM;
    }

    DEBUG_MES("tx_first_desc_addr = %p\n", first_desc);
    DEBUG_MES("dmaadr = %p\n", dma_addr);
    gmacdev->TxDescCount = no_of_desc;
    gmacdev->TxDesc      = first_desc;
    gmacdev->TxDescDma  = dma_addr;

    for (i = 0; i < gmacdev->TxDescCount; i++)
    {
        synopGMAC_tx_desc_init_ring(gmacdev->TxDesc + i, i == gmacdev->TxDescCount - 1);

#if SYNOP_TOP_DEBUG
        rt_kprintf("\n%02d %08x \n", i, (unsigned int)(gmacdev->TxDesc + i));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i))->status);
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->length));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->buffer1));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->buffer2));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->data1));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->data2));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->dummy1));
        rt_kprintf("%08x ", (unsigned int)((gmacdev->TxDesc + i)->dummy2));
#endif
    }

    gmacdev->TxNext = 0;
    gmacdev->TxBusy = 0;
    gmacdev->TxNextDesc = gmacdev->TxDesc;
    gmacdev->TxBusyDesc = gmacdev->TxDesc;
    gmacdev->BusyTxDesc  = 0;

    return -ESYNOPGMACNOERR;
}

/**
 * This sets up the receive Descriptor queue in ring or chain mode.
 * This function is tightly coupled to the platform and operating system
 * Device is interested only after the descriptors are setup. Therefore this function
 * is not included in the device driver API. This function should be treated as an
 * example code to design the descriptor structures in ring mode or chain mode.
 * This function depends on the pcidev structure for allocation of consistent dma-able memory in
 * case of linux.
 * This limitation is due to the fact that linux uses pci structure to allocate a dmable memory
 * - Allocates the memory for the descriptors.
 * - Initialize the Busy and Next descriptors indices to 0(Indicating first descriptor).
 * - Initialize the Busy and Next descriptors to first descriptor address.
 * - Initialize the last descriptor with the endof ring in case of ring mode.
 * - Initialize the descriptors in chain mode.
 * @param[in] pointer to synopGMACdevice.
 * @param[in] pointer to pci_device structure.
 * @param[in] number of descriptor expected in rx descriptor queue.
 * @param[in] whether descriptors to be created in RING mode or CHAIN mode.
 * \return 0 upon success. Error code upon failure.
 * \note This function fails if allocation fails for required number of descriptors in Ring mode,
 * but in chain mode
 * function returns -ESYNOPGMACNOMEM in the process of descriptor chain creation. once returned from
 * this function
 * user should for gmacdev->RxDescCount to see how many descriptors are there in the chain. Should
 * continue further
 * only if the number of descriptors in the chain meets the requirements
 */
s32 synopGMAC_setup_rx_desc_queue(synopGMACdevice *gmacdev, u32 no_of_desc, u32 desc_mode)
{
    s32 i;
    DmaDesc *bf1;
    DmaDesc *first_desc = NULL;

    dma_addr_t dma_addr;

    gmacdev->RxDescCount = 0;
    first_desc = (DmaDesc *)plat_alloc_consistent_dmaable_memory(gmacdev, sizeof(DmaDesc) * no_of_desc, &dma_addr);
    if (first_desc == NULL)
    {
        rt_kprintf("Error in Rx Descriptor Memory allocation in Ring mode\n");
        return -ESYNOPGMACNOMEM;
    }

    DEBUG_MES("rx_first_desc_addr = %p\n", first_desc);
    DEBUG_MES("dmaadr = %p\n", dma_addr);
    gmacdev->RxDescCount = no_of_desc;
    gmacdev->RxDesc      = (DmaDesc *)first_desc;
    gmacdev->RxDescDma   = dma_addr;

    for (i = 0; i < gmacdev->RxDescCount; i++)
    {
        synopGMAC_rx_desc_init_ring(gmacdev->RxDesc + i, i == gmacdev->RxDescCount - 1);
    }

    gmacdev->RxNext = 0;
    gmacdev->RxBusy = 0;
    gmacdev->RxNextDesc = gmacdev->RxDesc;
    gmacdev->RxBusyDesc = gmacdev->RxDesc;

    gmacdev->BusyRxDesc   = 0;

    return -ESYNOPGMACNOERR;
}

void synopGMAC_linux_cable_unplug_function(void *adaptr)
{
    s32 data;
    synopGMACPciNetworkAdapter *adapter = (synopGMACPciNetworkAdapter *)adaptr;
    synopGMACdevice            *gmacdev = adapter->synopGMACdev;
    struct ethtool_cmd cmd;

    if (!mii_link_ok(&adapter->mii))
    {
        if (gmacdev->LinkState)
            rt_kprintf("\r\nNo Link\r\n");
        gmacdev->DuplexMode = 0;
        gmacdev->Speed = 0;
        gmacdev->LoopBackMode = 0;
        gmacdev->LinkState = 0;
    }
    else
    {
        data = synopGMAC_check_phy_init(adapter);

        if (gmacdev->LinkState != data)
        {
            gmacdev->LinkState = data;
            synopGMAC_mac_init(gmacdev);
            rt_kprintf("Link is up in %s mode\n", (gmacdev->DuplexMode == FULLDUPLEX) ? "FULL DUPLEX" : "HALF DUPLEX");
            if (gmacdev->Speed == SPEED1000)
                rt_kprintf("Link is with 1000M Speed \r\n");
            if (gmacdev->Speed == SPEED100)
                rt_kprintf("Link is with 100M Speed \n");
            if (gmacdev->Speed == SPEED10)
                rt_kprintf("Link is with 10M Speed \n");
        }
    }
}

s32 synopGMAC_check_phy_init(synopGMACPciNetworkAdapter *adapter)
{
    struct ethtool_cmd cmd;
    synopGMACdevice            *gmacdev = adapter->synopGMACdev;

    if (!mii_link_ok(&adapter->mii))
    {
        gmacdev->DuplexMode = FULLDUPLEX;
        gmacdev->Speed      =   SPEED100;

        return 0;
    }
    else
    {
        mii_ethtool_gset(&adapter->mii, &cmd);

        gmacdev->DuplexMode = (cmd.duplex == DUPLEX_FULL)  ? FULLDUPLEX : HALFDUPLEX ;
        if (cmd.speed == SPEED_1000)
            gmacdev->Speed      =   SPEED1000;
        else if (cmd.speed == SPEED_100)
            gmacdev->Speed      =   SPEED100;
        else
            gmacdev->Speed      =   SPEED10;
    }

    return gmacdev->Speed | (gmacdev->DuplexMode << 4);
}

static int Mac_change_check(u8 *macaddr0, u8 *macaddr1)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        if (macaddr0[i] != macaddr1[i])
            return 1;
    }
    return 0;
}

static rt_err_t eth_init(rt_device_t device)
{
    struct eth_device *eth_device = (struct eth_device *)device;
    RT_ASSERT(eth_device != RT_NULL);

    s32 ijk;
    s32 status = 0;
    u64 dma_addr;
    u32 Mac_changed = 0;
    struct pbuf *pbuf;
    u8 macaddr[6] = DEFAULT_MAC_ADDRESS;
    struct rt_eth_dev *dev = &eth_dev;
    struct synopGMACNetworkAdapter *adapter = dev->priv;
    synopGMACdevice *gmacdev = (synopGMACdevice *)adapter->synopGMACdev;

    synopGMAC_reset(gmacdev);
    synopGMAC_attach(gmacdev, (gmac_base + MACBASE), (gmac_base + DMABASE), DEFAULT_PHY_BASE, macaddr);

    synopGMAC_read_version(gmacdev);

    synopGMAC_set_mdc_clk_div(gmacdev, GmiiCsrClk3);
    gmacdev->ClockDivMdc = synopGMAC_get_mdc_clk_div(gmacdev);

    init_phy(adapter->synopGMACdev);

    DEBUG_MES("tx desc_queue\n");
    synopGMAC_setup_tx_desc_queue(gmacdev, TRANSMIT_DESC_SIZE, RINGMODE);
    synopGMAC_init_tx_desc_base(gmacdev);

    DEBUG_MES("rx desc_queue\n");
    synopGMAC_setup_rx_desc_queue(gmacdev, RECEIVE_DESC_SIZE, RINGMODE);
    synopGMAC_init_rx_desc_base(gmacdev);
    DEBUG_MES("DmaRxBaseAddr = %08x\n", synopGMACReadReg(gmacdev->DmaBase, DmaRxBaseAddr));

//  u32 dmaRx_Base_addr = synopGMACReadReg(gmacdev->DmaBase,DmaRxBaseAddr);
//  rt_kprintf("first_desc_addr = 0x%x\n", dmaRx_Base_addr);

#ifdef ENH_DESC_8W
    synopGMAC_dma_bus_mode_init(gmacdev, DmaBurstLength32 | DmaDescriptorSkip2 | DmaDescriptor8Words);
#else
    synopGMAC_dma_bus_mode_init(gmacdev, DmaBurstLength4 | DmaDescriptorSkip1);
    //synopGMAC_dma_bus_mode_init(gmacdev, DmaBurstLength4 | DmaDescriptorSkip2);
#endif
    synopGMAC_dma_control_init(gmacdev, DmaStoreAndForward | DmaTxSecondFrame | DmaRxThreshCtrl128);

    status = synopGMAC_check_phy_init(adapter);
    synopGMAC_mac_init(gmacdev);

    synopGMAC_pause_control(gmacdev);

#ifdef IPC_OFFLOAD
    synopGMAC_enable_rx_chksum_offload(gmacdev);
    synopGMAC_rx_tcpip_chksum_drop_enable(gmacdev);
#endif

    u64 skb;
    do
    {
        skb = (u64)plat_alloc_memory(RX_BUF_SIZE);      //should skb aligned here?
        if (skb == RT_NULL)
        {
            rt_kprintf("ERROR in skb buffer allocation\n");
            break;
        }

        dma_addr = plat_dma_map_single(gmacdev, (void *)skb, RX_BUF_SIZE);  //获取 skb 的 dma 地址

        status = synopGMAC_set_rx_qptr(gmacdev, dma_addr, RX_BUF_SIZE, (u64)skb, 0, 0, 0);
        if (status < 0)
        {
            rt_kprintf("status < 0!!\n");
            plat_free_memory((void *)skb);
        }
    }
    while (status >= 0 && (status < (RECEIVE_DESC_SIZE - 1)));
    synopGMAC_clear_interrupt(gmacdev);

    synopGMAC_disable_mmc_tx_interrupt(gmacdev, 0xFFFFFFFF);
    synopGMAC_disable_mmc_rx_interrupt(gmacdev, 0xFFFFFFFF);
    synopGMAC_disable_mmc_ipc_rx_interrupt(gmacdev, 0xFFFFFFFF);

//  synopGMAC_disable_interrupt_all(gmacdev);
    synopGMAC_enable_interrupt(gmacdev, DmaIntEnable);
    synopGMAC_enable_dma_rx(gmacdev);
    synopGMAC_enable_dma_tx(gmacdev);

    plat_delay(DEFAULT_LOOP_VARIABLE);
    synopGMAC_check_phy_init(adapter);
    synopGMAC_mac_init(gmacdev);

    rt_timer_init(&dev->link_timer, "link_timer",
                  synopGMAC_linux_cable_unplug_function,
                  (void *)adapter,
                  RT_TICK_PER_SECOND,
                  RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(&dev->link_timer);
#ifdef RT_USING_GMAC_INT_MODE
    /* installl isr */
    DEBUG_MES("%s\n", __FUNCTION__);
    rt_hw_interrupt_install(LS1C_MAC_IRQ, eth_rx_irq, RT_NULL, "e0_isr");
    rt_hw_interrupt_umask(LS1C_MAC_IRQ);
#else
    rt_timer_init(&dev->rx_poll_timer, "rx_poll_timer",
                  eth_rx_irq,
                  (void *)adapter,
                  1,
                  RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(&dev->rx_poll_timer);
#endif  /*RT_USING_GMAC_INT_MODE*/

    return RT_EOK;
}

static rt_err_t eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_kprintf("eth_open!!\n");

    return RT_EOK;
}

static rt_err_t eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args) rt_memcpy(args, eth_dev.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }
    return RT_EOK;
}

rt_err_t rt_eth_tx(rt_device_t device, struct pbuf *p)
{
    /* lock eth device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    DEBUG_MES("in %s\n", __FUNCTION__);

    s32 status;
    u64 pbuf;
    u64 dma_addr;
    u32 offload_needed = 0;
    u32 index;
    DmaDesc *dpr;
    struct rt_eth_dev *dev = (struct rt_eth_dev *) device;
    struct synopGMACNetworkAdapter *adapter;
    synopGMACdevice *gmacdev;
    adapter = (struct synopGMACNetworkAdapter *) dev->priv;
    if (adapter == NULL)
        return -1;

    gmacdev = (synopGMACdevice *) adapter->synopGMACdev;
    if (gmacdev == NULL)
        return -1;

    if (!synopGMAC_is_desc_owned_by_dma(gmacdev->TxNextDesc))
    {

        pbuf = (u64)plat_alloc_memory(p->tot_len);
        //pbuf = (u32)pbuf_alloc(PBUF_LINK, p->len, PBUF_RAM);
        if (pbuf == 0)
        {
            rt_kprintf("===error in alloc bf1\n");
            return -1;
        }

        DEBUG_MES("p->len = %d\n", p->len);
        pbuf_copy_partial(p, (void *)pbuf, p->tot_len, 0);
        dma_addr = plat_dma_map_single(gmacdev, (void *)pbuf, p->tot_len);

        status = synopGMAC_set_tx_qptr(gmacdev, dma_addr, p->tot_len, pbuf, 0, 0, 0, offload_needed, &index, dpr);

        if (status < 0)
        {
            rt_kprintf("%s No More Free Tx Descriptors\n", __FUNCTION__);

            plat_free_memory((void *)pbuf);
            return -16;
        }
    }

    synopGMAC_resume_dma_tx(gmacdev);


    s32 desc_index;
    u64 data1, data2;
    u32 dma_addr1, dma_addr2;
    u32 length1, length2;
#ifdef ENH_DESC_8W
    u32 ext_status;
    u16 time_stamp_higher;
    u32 time_stamp_high;
    u32 time_stamp_low;
#endif
    do
    {
#ifdef ENH_DESC_8W
        desc_index = synopGMAC_get_tx_qptr(gmacdev, &status, &dma_addr1, &length1, &data1, &dma_addr2, &length2, &data2, &ext_status, &time_stamp_high, &time_stamp_low);
        synopGMAC_TS_read_timestamp_higher_val(gmacdev, &time_stamp_higher);
#else
        desc_index = synopGMAC_get_tx_qptr(gmacdev, &status, &dma_addr1, &length1, &data1, &dma_addr2, &length2, &data2);
#endif
        if (desc_index >= 0 && data1 != 0)
        {
#ifdef  IPC_OFFLOAD
            if (synopGMAC_is_tx_ipv4header_checksum_error(gmacdev, status))
            {
                rt_kprintf("Harware Failed to Insert IPV4 Header Checksum\n");
            }
            if (synopGMAC_is_tx_payload_checksum_error(gmacdev, status))
            {
                rt_kprintf("Harware Failed to Insert Payload Checksum\n");
            }
#endif

            plat_free_memory((void *)(data1));  //sw:   data1 = buffer1

            if (synopGMAC_is_desc_valid(status))
            {
                adapter->synopGMACNetStats.tx_bytes += length1;
                adapter->synopGMACNetStats.tx_packets++;
            }
            else
            {
                adapter->synopGMACNetStats.tx_errors++;
                adapter->synopGMACNetStats.tx_aborted_errors += synopGMAC_is_tx_aborted(status);
                adapter->synopGMACNetStats.tx_carrier_errors += synopGMAC_is_tx_carrier_error(status);
            }
        }

        adapter->synopGMACNetStats.collisions += synopGMAC_get_tx_collision_count(status);
    }
    while (desc_index >= 0);

    /* unlock eth device */
    rt_sem_release(&sem_lock);
//  rt_kprintf("output %d bytes\n", p->len);
    u32 test_data;
    test_data = synopGMACReadReg(gmacdev->DmaBase, DmaStatus);
    //rt_kprintf("dma_status = 0x%08x\n",test_data);

    return RT_EOK;
}

struct pbuf *rt_eth_rx(rt_device_t device)
{
    DEBUG_MES("%s : \n", __FUNCTION__);
    struct rt_eth_dev *dev = &eth_dev;
    struct synopGMACNetworkAdapter *adapter;
    synopGMACdevice *gmacdev;
//  struct PmonInet * pinetdev;
    s32 desc_index;
    int i;
    char *ptr;
    u32 bf1;
    u64 data1;
    u64 data2;
    u32 len;
    u32 status;
    u32 dma_addr1;
    u32 dma_addr2;
    struct pbuf *pbuf = RT_NULL;
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    adapter = (struct synopGMACNetworkAdapter *) dev->priv;
    if (adapter == NULL)
    {
        rt_kprintf("%S : Unknown Device !!\n", __FUNCTION__);
        return NULL;
    }

    gmacdev = (synopGMACdevice *) adapter->synopGMACdev;
    if (gmacdev == NULL)
    {
        rt_kprintf("%s : GMAC device structure is missing\n", __FUNCTION__);
        return NULL;
    }

    /*Handle the Receive Descriptors*/
    desc_index = synopGMAC_get_rx_qptr(gmacdev, &status, &dma_addr1, NULL, &data1, &dma_addr2, NULL, &data2);

    if (((u32)desc_index >= RECEIVE_DESC_SIZE) && (desc_index != -1))
    {
        rt_kprintf("host receive descriptor address pointer = 0x%08x\n", synopGMACReadReg(gmacdev->DmaBase, DmaRxCurrDesc));
        rt_kprintf("host receive buffer = 0x%08x\n", synopGMACReadReg(gmacdev->DmaBase, DmaRxCurrAddr));
        rt_kprintf("desc_index error!!!!,tick = %d\n", rt_tick_get());
        while (1);
    }

    if (desc_index >= 0 && data1 != 0)
    {
        DEBUG_MES("Received Data at Rx Descriptor %d for skb 0x%08x whose status is %08x\n", desc_index, dma_addr1, status);

        if (synopGMAC_is_rx_desc_valid(status) || SYNOP_PHY_LOOPBACK)
        {
            dma_addr1 =  plat_dma_map_single(gmacdev, (void *)data1, RX_BUF_SIZE);
            len =  synopGMAC_get_rx_desc_frame_length(status) - 4; //Not interested in Ethernet CRC bytes
            pbuf = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
            if (pbuf == 0) rt_kprintf("===error in pbuf_alloc\n");
            rt_memcpy(pbuf->payload, (char *)data1, len);
            DEBUG_MES("==get pkg len: %d\n", len);
        }
        else
        {
            rt_kprintf("s: %08x\n", status);
            adapter->synopGMACNetStats.rx_errors++;
            adapter->synopGMACNetStats.collisions       += synopGMAC_is_rx_frame_collision(status);
            adapter->synopGMACNetStats.rx_crc_errors    += synopGMAC_is_rx_crc(status);
            adapter->synopGMACNetStats.rx_frame_errors  += synopGMAC_is_frame_dribbling_errors(status);
            adapter->synopGMACNetStats.rx_length_errors += synopGMAC_is_rx_frame_length_errors(status);
        }
        desc_index = synopGMAC_set_rx_qptr(gmacdev, dma_addr1, RX_BUF_SIZE, (u64)data1, 0, 0, 0);
        if (desc_index < 0)
        {
#if SYNOP_RX_DEBUG
            rt_kprintf("Cannot set Rx Descriptor for data1 %08x\n", (u32)data1);
#endif

            plat_free_memory((void *)data1);
        }
    }
    rt_sem_release(&sem_lock);
    DEBUG_MES("%s : before return \n", __FUNCTION__);
    return pbuf;
}

static int rtl88e1111_config_init(synopGMACdevice *gmacdev)
{
    int retval, err;
    u16 data;

    DEBUG_MES("in %s\n", __FUNCTION__);
    synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x14, &data);
    data = data | 0x82;
    err = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x14, data);
    synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x00, &data);
    data = data | 0x8000;
    err = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x00, data);
#if SYNOP_PHY_LOOPBACK
    synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x14, &data);
    data = data | 0x70;
    data = data & 0xffdf;
    err = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x14, data);
    data = 0x8000;
    err = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x00, data);
    data = 0x5140;
    err = synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x00, data);
#endif
    if (err < 0)
        return err;
    return 0;
}

int init_phy(synopGMACdevice *gmacdev)
{
    u16 data;

    synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 2, &data);
    /*set 88e1111 clock phase delay*/
    if (data == 0x141)
        rtl88e1111_config_init(gmacdev);
#if defined (RMII)
    else if (data == 0x8201)
    {
        //RTL8201
        data = 0x400;    // set RMII mode
        synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x19, data);
        synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x19, &data);
        TR("phy reg25 is %0x \n", data);

        data = 0x3100;    //set  100M speed
        synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x0, data);
    }
    else if (data == 0x0180 || data == 0x0181)
    {
        //DM9161
        synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x10, &data);
        data |= (1 << 8);  //set RMII mode
        synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x10, data); //set RMII mode
        synopGMAC_read_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x10, &data);
        TR("phy reg16 is 0x%0x \n", data);

        //  synopGMAC_read_phy_reg(gmacdev->MacBase,gmacdev->PhyBase,0x0,&data);
        //  data &= ~(1<<10);
        data = 0x3100;  //set auto-
        //data = 0x0100;    //set  10M speed
        synopGMAC_write_phy_reg(gmacdev->MacBase, gmacdev->PhyBase, 0x0, data);
    }
#endif

    return 0;
}

u32 synopGMAC_wakeup_filter_config3[] =
{
    0x00000000,
    0x000000FF,
    0x00000000,
    0x00000000,
    0x00000100,
    0x00003200,
    0x7eED0000,
    0x00000000
};

static void synopGMAC_linux_powerdown_mac(synopGMACdevice *gmacdev)
{
    rt_kprintf("Put the GMAC to power down mode..\n");

    GMAC_Power_down = 1;

    synopGMAC_disable_dma_tx(gmacdev);
    plat_delay(10000);

    synopGMAC_tx_disable(gmacdev);
    synopGMAC_rx_disable(gmacdev);
    plat_delay(10000);

    synopGMAC_disable_dma_rx(gmacdev);

    synopGMAC_magic_packet_enable(gmacdev);
    synopGMAC_write_wakeup_frame_register(gmacdev, synopGMAC_wakeup_filter_config3);

    synopGMAC_wakeup_frame_enable(gmacdev);

    synopGMAC_rx_enable(gmacdev);

    synopGMAC_pmt_int_enable(gmacdev);

    synopGMAC_power_down_enable(gmacdev);
    return;
}

static void synopGMAC_linux_powerup_mac(synopGMACdevice *gmacdev)
{
    GMAC_Power_down = 0;
    if (synopGMAC_is_magic_packet_received(gmacdev))
        rt_kprintf("GMAC wokeup due to Magic Pkt Received\n");
    if (synopGMAC_is_wakeup_frame_received(gmacdev))
        rt_kprintf("GMAC wokeup due to Wakeup Frame Received\n");

    synopGMAC_pmt_int_disable(gmacdev);

    synopGMAC_rx_enable(gmacdev);
    synopGMAC_enable_dma_rx(gmacdev);

    synopGMAC_tx_enable(gmacdev);
    synopGMAC_enable_dma_tx(gmacdev);
    return;
}


static int mdio_read(synopGMACPciNetworkAdapter *adapter, int addr, int reg)
{
    synopGMACdevice *gmacdev;
    u16 data;
    gmacdev = adapter->synopGMACdev;

    synopGMAC_read_phy_reg(gmacdev->MacBase, addr, reg, &data);
    return data;
}

static void mdio_write(synopGMACPciNetworkAdapter *adapter, int addr, int reg, int data)
{
    synopGMACdevice *gmacdev;
    gmacdev = adapter->synopGMACdev;
    synopGMAC_write_phy_reg(gmacdev->MacBase, addr, reg, data);
}

void eth_rx_irq(int irqno, void *param)
{
    struct rt_eth_dev *dev = &eth_dev;
    struct synopGMACNetworkAdapter *adapter = dev->priv;
    //DEBUG_MES("in irq!!\n");
#ifdef RT_USING_GMAC_INT_MODE
    int i ;
    for (i = 0; i < 7200; i++)
        ;
#endif  /*RT_USING_GMAC_INT_MODE*/
    synopGMACdevice *gmacdev = (synopGMACdevice *)adapter->synopGMACdev;

    u32 interrupt, dma_status_reg;
    s32 status;
    u32 dma_addr;

    //rt_kprintf("irq i = %d\n", i++);
    dma_status_reg = synopGMACReadReg(gmacdev->DmaBase, DmaStatus);
    if (dma_status_reg == 0)
    {
        rt_kprintf("dma_status ==0 \n");
        return;
    }

    //rt_kprintf("dma_status_reg is 0x%x\n", dma_status_reg);
    u32 gmacstatus;
    synopGMAC_disable_interrupt_all(gmacdev);
    gmacstatus = synopGMACReadReg(gmacdev->MacBase, GmacStatus);

    if (dma_status_reg & GmacPmtIntr)
    {
        rt_kprintf("%s:: Interrupt due to PMT module\n", __FUNCTION__);
        //synopGMAC_linux_powerup_mac(gmacdev);
    }
    if (dma_status_reg & GmacMmcIntr)
    {
        rt_kprintf("%s:: Interrupt due to MMC module\n", __FUNCTION__);
        DEBUG_MES("%s:: synopGMAC_rx_int_status = %08x\n", __FUNCTION__, synopGMAC_read_mmc_rx_int_status(gmacdev));
        DEBUG_MES("%s:: synopGMAC_tx_int_status = %08x\n", __FUNCTION__, synopGMAC_read_mmc_tx_int_status(gmacdev));
    }

    if (dma_status_reg & GmacLineIntfIntr)
    {
        //rt_kprintf("%s:: Interrupt due to GMAC LINE module\n", __FUNCTION__);
    }

    interrupt = synopGMAC_get_interrupt_type(gmacdev);
    //rt_kprintf("%s:Interrupts to be handled: 0x%08x\n",__FUNCTION__,interrupt);
    if (interrupt & synopGMACDmaError)
    {
        u8 mac_addr0[6];
        rt_kprintf("%s::Fatal Bus Error Inetrrupt Seen\n", __FUNCTION__);

        memcpy(mac_addr0, dev->dev_addr, 6);
        synopGMAC_disable_dma_tx(gmacdev);
        synopGMAC_disable_dma_rx(gmacdev);

        synopGMAC_take_desc_ownership_tx(gmacdev);
        synopGMAC_take_desc_ownership_rx(gmacdev);

        synopGMAC_init_tx_rx_desc_queue(gmacdev);

        synopGMAC_reset(gmacdev);

        synopGMAC_set_mac_addr(gmacdev, GmacAddr0High, GmacAddr0Low, mac_addr0);
        synopGMAC_dma_bus_mode_init(gmacdev, DmaFixedBurstEnable | DmaBurstLength8 | DmaDescriptorSkip1);
        synopGMAC_dma_control_init(gmacdev, DmaStoreAndForward);
        synopGMAC_init_rx_desc_base(gmacdev);
        synopGMAC_init_tx_desc_base(gmacdev);
        synopGMAC_mac_init(gmacdev);
        synopGMAC_enable_dma_rx(gmacdev);
        synopGMAC_enable_dma_tx(gmacdev);

    }
    if (interrupt & synopGMACDmaRxNormal)
    {
        //DEBUG_MES("%s:: Rx Normal \n", __FUNCTION__);
        //synop_handle_received_data(netdev);
        eth_device_ready(&eth_dev.parent);
    }
    if (interrupt & synopGMACDmaRxAbnormal)
    {
        //rt_kprintf("%s::Abnormal Rx Interrupt Seen\n",__FUNCTION__);
        if (GMAC_Power_down == 0)
        {
            adapter->synopGMACNetStats.rx_over_errors++;
            synopGMACWriteReg(gmacdev->DmaBase, DmaStatus, 0x80);
            synopGMAC_resume_dma_rx(gmacdev);
        }
    }
    if (interrupt & synopGMACDmaRxStopped)
    {
        rt_kprintf("%s::Receiver stopped seeing Rx interrupts\n", __FUNCTION__); //Receiver gone in to stopped state
    }

    if (interrupt & synopGMACDmaTxNormal)
    {
        DEBUG_MES("%s::Finished Normal Transmission \n", __FUNCTION__);
        //          synop_handle_transmit_over(netdev);
    }

    if (interrupt & synopGMACDmaTxAbnormal)
    {
        rt_kprintf("%s::Abnormal Tx Interrupt Seen\n", __FUNCTION__);
    }
    if (interrupt & synopGMACDmaTxStopped)
    {
        TR("%s::Transmitter stopped sending the packets\n", __FUNCTION__);
        if (GMAC_Power_down == 0)    // If Mac is not in powerdown
        {
            synopGMAC_disable_dma_tx(gmacdev);
            synopGMAC_take_desc_ownership_tx(gmacdev);

            synopGMAC_enable_dma_tx(gmacdev);
            //      netif_wake_queue(netdev);
            TR("%s::Transmission Resumed\n", __FUNCTION__);
        }
    }
    /* Enable the interrrupt before returning from ISR*/
    synopGMAC_enable_interrupt(gmacdev, DmaIntEnable);

    return;
}

int rt_hw_eth_init(void)
{
    struct pci_header *p = (struct pci_header *)(0x9000000000000000 | PCI_BASE);
    gmac_base = (0x9000000000000000 | ((p->BaseAddressRegister[0]) & 0xffffff00));

    struct synopGMACNetworkAdapter *synopGMACadapter;
    static u8 mac_addr0[6] = DEFAULT_MAC_ADDRESS;
    int index;
    rt_sem_init(&sem_ack, "tx_ack", 1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

    memset(&eth_dev, 0, sizeof(eth_dev));
    synopGMACadapter = (struct synopGMACNetworkAdapter *)plat_alloc_memory(sizeof(struct synopGMACNetworkAdapter));
    if (!synopGMACadapter)
    {
        rt_kprintf("Error in Memory Allocataion, Founction : %s \n", __FUNCTION__);
    }
    memset((char *)synopGMACadapter, 0, sizeof(struct synopGMACNetworkAdapter));

    synopGMACadapter->synopGMACdev    = NULL;

    synopGMACadapter->synopGMACdev = (synopGMACdevice *) plat_alloc_memory(sizeof(synopGMACdevice));
    if (!synopGMACadapter->synopGMACdev)
    {
        rt_kprintf("Error in Memory Allocataion, Founction : %s \n", __FUNCTION__);
    }

    memset((char *)synopGMACadapter->synopGMACdev, 0, sizeof(synopGMACdevice));

    /*
     * Attach the device to MAC struct This will configure all the required base addresses
     * such as Mac base, configuration base, phy base address(out of 32 possible phys)
     * */
    synopGMAC_attach(synopGMACadapter->synopGMACdev, (gmac_base + MACBASE), gmac_base + DMABASE, DEFAULT_PHY_BASE, mac_addr0);

    init_phy(synopGMACadapter->synopGMACdev);
    synopGMAC_reset(synopGMACadapter->synopGMACdev);

    /* MII setup */
    synopGMACadapter->mii.phy_id_mask = 0x1F;
    synopGMACadapter->mii.reg_num_mask = 0x1F;
    synopGMACadapter->mii.dev = synopGMACadapter;
    synopGMACadapter->mii.mdio_read = mdio_read;
    synopGMACadapter->mii.mdio_write = mdio_write;
    synopGMACadapter->mii.phy_id = synopGMACadapter->synopGMACdev->PhyBase;
    synopGMACadapter->mii.supports_gmii = mii_check_gmii_support(&synopGMACadapter->mii);

    eth_dev.iobase = gmac_base;
    eth_dev.name = "e0";
    eth_dev.priv = synopGMACadapter;
    eth_dev.dev_addr[0] = mac_addr0[0];
    eth_dev.dev_addr[1] = mac_addr0[1];
    eth_dev.dev_addr[2] = mac_addr0[2];
    eth_dev.dev_addr[3] = mac_addr0[3];
    eth_dev.dev_addr[4] = mac_addr0[4];
    eth_dev.dev_addr[5] = mac_addr0[5];

    eth_dev.parent.parent.type          = RT_Device_Class_NetIf;
    eth_dev.parent.parent.init          = eth_init;
    eth_dev.parent.parent.open          = eth_open;
    eth_dev.parent.parent.close         = eth_close;
    eth_dev.parent.parent.read          = eth_read;
    eth_dev.parent.parent.write         = eth_write;
    eth_dev.parent.parent.control       = eth_control;
    eth_dev.parent.parent.user_data     = RT_NULL;

    eth_dev.parent.eth_tx            = rt_eth_tx;
    eth_dev.parent.eth_rx            = rt_eth_rx;

    eth_device_init(&(eth_dev.parent), "e0");
    eth_device_linkchange(&eth_dev.parent, RT_TRUE);   //linkup the e0 for lwip to check
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_eth_init);
