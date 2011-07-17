/* @file wlan_main.c
  *  
  * @brief This file contains the major functions in WLAN
  * driver. It includes init, exit, open, close and main
  * thread etc..
  * 
  */
/**
  * @mainpage M-WLAN Linux Driver
  *
  * @section overview_sec Overview
  *
  * The M-WLAN is a Linux reference driver for Marvell
  * 802.11 (a/b/g) WLAN chipset.
  * 
  * @section copyright_sec Copyright
  *
  * Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
  *
  */
/********************************************************
Change log:
    09/30/05: Add Doxygen format comments
    12/09/05: Add TX_QUEUE support  
    01/05/06: Add kernel 2.6.x support  
    01/11/06: Conditionalize new scan/join functions.
    01/12/06: Add TxLockFlag for UAPSD power save mode 
              and Proprietary Periodic sleep support
********************************************************/

#include    "include.h"
#include	"wlan_debug.h"
#include <netif/ethernetif.h>
#include <rtdef.h>
/********************************************************
        Local Variables
********************************************************/
static struct rt_semaphore  tx_sem_lock;
struct rt_event wlan_tx_event;
u32 driver_flags;

#define WLAN_TX_PWR_DEFAULT     20      /*100mW */
#define WLAN_TX_PWR_US_DEFAULT      20  /*100mW */
#define WLAN_TX_PWR_JP_DEFAULT      16  /*50mW */
#define WLAN_TX_PWR_FR_100MW        20  /*100mW */
#define WLAN_TX_PWR_EMEA_DEFAULT    20  /*100mW */

/* Format { Channel, Frequency (MHz), MaxTxPower } */
/* Band: 'B/G', Region: USA FCC/Canada IC */
static CHANNEL_FREQ_POWER channel_freq_power_US_BG[] = {
    {1, 2412, WLAN_TX_PWR_US_DEFAULT},
    {2, 2417, WLAN_TX_PWR_US_DEFAULT},
    {3, 2422, WLAN_TX_PWR_US_DEFAULT},
    {4, 2427, WLAN_TX_PWR_US_DEFAULT},
    {5, 2432, WLAN_TX_PWR_US_DEFAULT},
    {6, 2437, WLAN_TX_PWR_US_DEFAULT},
    {7, 2442, WLAN_TX_PWR_US_DEFAULT},
    {8, 2447, WLAN_TX_PWR_US_DEFAULT},
    {9, 2452, WLAN_TX_PWR_US_DEFAULT},
    {10, 2457, WLAN_TX_PWR_US_DEFAULT},
    {11, 2462, WLAN_TX_PWR_US_DEFAULT}
};

/* Band: 'B/G', Region: Europe ETSI */
static CHANNEL_FREQ_POWER channel_freq_power_EU_BG[] = {
    {1, 2412, WLAN_TX_PWR_EMEA_DEFAULT},
    {2, 2417, WLAN_TX_PWR_EMEA_DEFAULT},
    {3, 2422, WLAN_TX_PWR_EMEA_DEFAULT},
    {4, 2427, WLAN_TX_PWR_EMEA_DEFAULT},
    {5, 2432, WLAN_TX_PWR_EMEA_DEFAULT},
    {6, 2437, WLAN_TX_PWR_EMEA_DEFAULT},
    {7, 2442, WLAN_TX_PWR_EMEA_DEFAULT},
    {8, 2447, WLAN_TX_PWR_EMEA_DEFAULT},
    {9, 2452, WLAN_TX_PWR_EMEA_DEFAULT},
    {10, 2457, WLAN_TX_PWR_EMEA_DEFAULT},
    {11, 2462, WLAN_TX_PWR_EMEA_DEFAULT},
    {12, 2467, WLAN_TX_PWR_EMEA_DEFAULT},
    {13, 2472, WLAN_TX_PWR_EMEA_DEFAULT}
};

/* Band: 'B/G', Region: Spain */
static CHANNEL_FREQ_POWER channel_freq_power_SPN_BG[] = {
    {10, 2457, WLAN_TX_PWR_DEFAULT},
    {11, 2462, WLAN_TX_PWR_DEFAULT}
};

/* Band: 'B/G', Region: France */
static CHANNEL_FREQ_POWER channel_freq_power_FR_BG[] = {
    {10, 2457, WLAN_TX_PWR_FR_100MW},
    {11, 2462, WLAN_TX_PWR_FR_100MW},
    {12, 2467, WLAN_TX_PWR_FR_100MW},
    {13, 2472, WLAN_TX_PWR_FR_100MW}
};

/* Band: 'B/G', Region: Japan */
static CHANNEL_FREQ_POWER channel_freq_power_JPN41_BG[] = {
    {1, 2412, WLAN_TX_PWR_JP_DEFAULT},
    {2, 2417, WLAN_TX_PWR_JP_DEFAULT},
    {3, 2422, WLAN_TX_PWR_JP_DEFAULT},
    {4, 2427, WLAN_TX_PWR_JP_DEFAULT},
    {5, 2432, WLAN_TX_PWR_JP_DEFAULT},
    {6, 2437, WLAN_TX_PWR_JP_DEFAULT},
    {7, 2442, WLAN_TX_PWR_JP_DEFAULT},
    {8, 2447, WLAN_TX_PWR_JP_DEFAULT},
    {9, 2452, WLAN_TX_PWR_JP_DEFAULT},
    {10, 2457, WLAN_TX_PWR_JP_DEFAULT},
    {11, 2462, WLAN_TX_PWR_JP_DEFAULT},
    {12, 2467, WLAN_TX_PWR_JP_DEFAULT},
    {13, 2472, WLAN_TX_PWR_JP_DEFAULT}
};

/* Band: 'B/G', Region: Japan */
static CHANNEL_FREQ_POWER channel_freq_power_JPN40_BG[] = {
    {14, 2484, WLAN_TX_PWR_JP_DEFAULT}
};

/********************************************************
        Global Variables
********************************************************/
struct rt_wlan_dev *wlan_eth = NULL;
struct rt_semaphore driver_sem;
/**
 * the structure for channel, frequency and power
 */
typedef struct _region_cfp_table
{
    u8 region;
    CHANNEL_FREQ_POWER *cfp_BG;
    int cfp_no_BG;
} region_cfp_table_t;

/**
 * the structure for the mapping between region and CFP
 */
region_cfp_table_t region_cfp_table[] = {
    {0x10,                      /*US FCC */
     channel_freq_power_US_BG,
     sizeof(channel_freq_power_US_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
    {0x20,                      /*CANADA IC */
     channel_freq_power_US_BG,
     sizeof(channel_freq_power_US_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
    {0x30, /*EU*/ channel_freq_power_EU_BG,
     sizeof(channel_freq_power_EU_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
    {0x31, /*SPAIN*/ channel_freq_power_SPN_BG,
     sizeof(channel_freq_power_SPN_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
    {0x32, /*FRANCE*/ channel_freq_power_FR_BG,
     sizeof(channel_freq_power_FR_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
    {0x40, /*JAPAN*/ channel_freq_power_JPN40_BG,
     sizeof(channel_freq_power_JPN40_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
    {0x41, /*JAPAN*/ channel_freq_power_JPN41_BG,
     sizeof(channel_freq_power_JPN41_BG) / sizeof(CHANNEL_FREQ_POWER),
     }
    ,
/*Add new region here */
};

/**
 * the rates supported by the card
 */
u8 WlanDataRates[WLAN_SUPPORTED_RATES] =
    { 0x02, 0x04, 0x0B, 0x16, 0x00, 0x0C, 0x12,
    0x18, 0x24, 0x30, 0x48, 0x60, 0x6C, 0x00
};

/**
 * the rates supported
 */
u8 SupportedRates[G_SUPPORTED_RATES] =
    { 0x82, 0x84, 0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24, 0x30, 0x48,
    0x60, 0x6c, 0
};
/**
 * the global variable of a pointer to wlan_private
 * structure variable
 */
wlan_private *wlanpriv = NULL;

u32 DSFreqList[15] = {
    0, 2412000, 2417000, 2422000, 2427000, 2432000, 2437000, 2442000,
    2447000, 2452000, 2457000, 2462000, 2467000, 2472000, 2484000
};

/**
 * the table to keep region code
 */
u16 RegionCodeToIndex[MRVDRV_MAX_REGION_CODE] =
    { 0x10, 0x20, 0x30, 0x31, 0x32, 0x40, 0x41 };
char main_thread_stack[2048];
char assciation_thread_stack[2048];

/********************************************************
        Local Functions
********************************************************/

/** 
 *  @brief This function opens the network device
 *  
 *  @param dev     A pointer to net_device structure
 *  @return        WLAN_STATUS_SUCCESS
 */
static int
wlan_open(struct rt_wlan_dev *dev)
{
    wlan_private *priv = (wlan_private *) dev->priv;
    wlan_adapter *adapter = priv->adapter;

    ENTER();
    priv->open = TRUE;


    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function closes the network device
 *  
 *  @param dev     A pointer to net_device structure
 *  @return        WLAN_STATUS_SUCCESS
 */
static int
wlan_close(struct rt_wlan_dev *dev)
{
    wlan_private *priv = dev->priv;

    ENTER();

    wlan_clean_txrx(priv);

    priv->open = FALSE;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}


/** 
 *  @brief This function handles packet transmission
 *  
 *  @param skb     A pointer to sk_buff structure
 *  @param dev     A pointer to net_device structure
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
rt_err_t rt_wlan_dev_tx( rt_device_t dev, struct pbuf* packet)
{
    int ret;
    struct rt_wlan_dev *wlandev=dev->user_data;
    wlan_private *priv = wlandev->priv;
    
    ret = RT_EOK;

    ENTER();

    wlan_debug3( "Data <= kernel\n");
    
    rt_sem_take(&tx_sem_lock, RT_WAITING_FOREVER);
    if (wlan_tx_packet(priv, packet)) {
	rt_sem_release(&tx_sem_lock);
        /* Transmit failed */
        ret = RT_ERROR;
    }
    rt_sem_release(&tx_sem_lock);
    LEAVE();
    return ret;
}

/** 
 *  @brief This function handles the timeout of packet
 *  transmission
 *  
 *  @param dev     A pointer to net_device structure
 *  @return        n/a
 */
static void
wlan_tx_timeout(struct rt_wlan_dev *dev)
{
    wlan_private *priv = (wlan_private *) dev->priv;

    ENTER();

    wlan_debug2("wlan_tx timeout\n");
    priv->adapter->dbg.num_tx_timeout++;

    priv->adapter->IntCounter++;
	rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);

    LEAVE();
}

/** 
 *  @brief This function returns the network statistics
 *  
 *  @param dev     A pointer to wlan_private structure
 *  @return        A pointer to net_device_stats structure
 */
static struct net_device_stats *
wlan_get_stats(struct rt_wlan_dev *dev)
{
    wlan_private *priv = (wlan_private *) dev->priv;

    return &priv->stats;
}

/** 
 *  @brief This function sets the MAC address to firmware.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param pRxPD   A pointer to RxPD structure of received packet
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_set_mac_address(struct rt_wlan_dev *dev, char *addr)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_private *priv = (wlan_private *) dev->priv;
    wlan_adapter *Adapter = priv->adapter;
   
    ENTER();

    memset(Adapter->CurrentAddr, 0, MRVDRV_ETH_ADDR_LEN);

    /* dev->dev_addr is 8 bytes */
    rt_memcpy(Adapter->CurrentAddr, addr, ETH_ALEN);

    ret = PrepareAndSendCommand(priv, HostCmd_CMD_802_11_MAC_ADDRESS,
                                HostCmd_ACT_SET,
                                HostCmd_OPTION_WAITFORRSP, 0, NULL);

    if (ret) {
        wlan_debug1("set mac address failed.\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }
    rt_memcpy(dev->dev_addr, Adapter->CurrentAddr, ETH_ALEN);

  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function sets multicast addresses to firmware
 *  
 *  @param dev     A pointer to net_device structure
 *  @return        n/a
 */
static void
wlan_set_multicast_list(struct rt_wlan_dev *dev)
{
    wlan_private *priv = dev->priv;
    wlan_adapter *Adapter = priv->adapter;
    int OldPacketFilter;

    ENTER();

    OldPacketFilter = Adapter->CurrentPacketFilter;
#if 0
    if (dev->flags & IFF_PROMISC) {
        wlan_debug3("Enable Promiscuous mode\n");
        Adapter->CurrentPacketFilter |= HostCmd_ACT_MAC_PROMISCUOUS_ENABLE;
        Adapter->CurrentPacketFilter &= ~HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE;
    } else {
        /* Multicast */
        Adapter->CurrentPacketFilter &= ~HostCmd_ACT_MAC_PROMISCUOUS_ENABLE;

        if (dev->flags & IFF_ALLMULTI || dev->mc_count >
            MRVDRV_MAX_MULTICAST_LIST_SIZE) {
            wlan_debug3("Enabling All Multicast!\n");
            Adapter->CurrentPacketFilter |=
                HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE;
        } else {
            Adapter->CurrentPacketFilter &=
                ~HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE;

            if (!dev->mc_count) {
                wlan_debug3("No multicast addresses - "
                       "disabling multicast!\n");

            } else {
                int i;

                Adapter->NumOfMulticastMACAddr =
                    CopyMulticastAddrs(Adapter, dev);

                PRINTM(INFO, "Multicast addresses: %d\n", dev->mc_count);

                for (i = 0; i < dev->mc_count; i++) {
                    wlan_debug3("Multicast address %d:"
                           "%x %x %x %x %x %x\n", i,
                           Adapter->MulticastList[i][0],
                           Adapter->MulticastList[i][1],
                           Adapter->MulticastList[i][2],
                           Adapter->MulticastList[i][3],
                           Adapter->MulticastList[i][4],
                           Adapter->MulticastList[i][5]);
                }
                /* set multicast addresses to firmware */
                PrepareAndSendCommand(priv, HostCmd_CMD_MAC_MULTICAST_ADR,
                                      HostCmd_ACT_GEN_SET, 0, 0, NULL);
            }
        }
    }

    if (Adapter->CurrentPacketFilter != OldPacketFilter) {
        PrepareAndSendCommand(priv,
                              HostCmd_CMD_MAC_CONTROL,
                              0, 0, 0, &Adapter->CurrentPacketFilter);
    }
 #endif
    LEAVE();
}

/** 
 *  @brief This function pops rx_skb from the rx queue.
 *  
 *  @param RxSkbQ  A pointer to rx_skb queue
 *  @return        A pointer to skb
 */
static struct sk_buff * wlan_pop_rx_skb(struct sk_buff *RxSkbQ)
{
    struct sk_buff *skb_data = NULL;

    if (!list_empty((struct list_head *) RxSkbQ)) {
        skb_data = RxSkbQ->next;
        list_del((struct list_head *) RxSkbQ->next);
    }

    return skb_data;
}

/** 
 *  @brief This function hanldes the major job in WLAN driver.
 *  it handles the event generated by firmware, rx data received
 *  from firmware and tx data sent from kernel.
 *  
 *  @param data    A pointer to wlan_thread structure
 *  @return        WLAN_STATUS_SUCCESS
 */
static void wlan_service_main_thread(void *data)
{
    wlan_thread *thread = data;
    wlan_private *priv = thread->priv;
    wlan_adapter *Adapter = priv->adapter;
    u8 ireg = 0;
	rt_uint32_t e;


       ENTER();
	if (rt_sem_init(&driver_sem, "wlansem", 1, RT_IPC_FLAG_FIFO)!=RT_EOK)
	{
		wlan_debug2("init driver_sem failed/r/n");
		return ;
	}
    	wlan_activate_thread(thread);

    	wmm_init(priv);

    	for (;;) {
    
   	if ((Adapter->WakeupTries) ||
            (Adapter->PSState == PS_STATE_SLEEP
             && !Adapter->bWakeupDevRequired) ||
            (!Adapter->IntCounter &&
             Adapter->PSState == PS_STATE_PRE_SLEEP) ||
            (!Adapter->IntCounter
             && (priv->wlan_dev.dnld_sent || Adapter->TxLockFlag
                 || wmm_lists_empty(priv) || wmm_is_queue_stopped(priv))
             && (priv->wlan_dev.dnld_sent || !Adapter->CurrentTxSkb)
             && (priv->wlan_dev.dnld_sent || Adapter->CurCmd ||
                 list_empty(&Adapter->CmdPendingQ))
            )
            ) {
           wlan_debug2 ("main-thread sleeping... "
                   "WakeupReq=%s Conn=%s PS_Mode=%d PS_State=%d\n\r",
                   (Adapter->bWakeupDevRequired) ? "Y" : "N",
                   (Adapter->MediaConnectStatus) ? "Y" : "N",
                   Adapter->PSMode, Adapter->PSState);
    	   rt_event_recv(&thread->waitQ,WakeUpMainThread,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&e);
         
           wlan_debug2 ("main-thread waking up: IntCnt=%d ""CurCmd=%s CmdPending=%s\n\r"
                   "Connect=%s "
                   "CurTxSkb=%s dnld_sent=%d\n\r",
                   Adapter->IntCounter,
                   (Adapter->CurCmd) ? "Y" : "N",
                   list_empty(&Adapter->CmdPendingQ) ? "N" : "Y",
                   (Adapter->MediaConnectStatus) ? "Y" : "N",
                   (Adapter->CurrentTxSkb) ? "Y" : "N",
                   priv->wlan_dev.dnld_sent); 
        } else {
           
        }

        if (Adapter->IntCounter) {
            rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
            Adapter->IntCounter = 0;
            rt_sem_release(&driver_sem);

           if (sbi_get_int_status(priv, &ireg)) {
                wlan_debug1("main-thread: reading HOST_INT_STATUS_REG failed\n");
		        wlan_debug1("sbi_get_int_status return  \n"); 
           }
            rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
            Adapter->HisRegCpy |= ireg;
            rt_sem_release(&driver_sem);
            wlan_debug1("INT: status = 0x%x\n", Adapter->HisRegCpy);
        } else if (Adapter->bWakeupDevRequired
                   && ((Adapter->PSState == PS_STATE_SLEEP)
                   )
            ) {
           Adapter->WakeupTries++;
           wlan_debug3("Wakeup device... WakeupReq=%s Conn=%s PS_Mode=%d PS_State=%d\n",
                   (Adapter->bWakeupDevRequired) ? "Y" : "N",
                   (priv->adapter->MediaConnectStatus) ? "Y" : "N",
                   priv->adapter->PSMode, priv->adapter->PSState);

            /* Wake up device */
            if (sbi_exit_deep_sleep(priv))
                wlan_debug3("main-thread: wakeup dev failed\n");
            continue;
       }

        /* Command response? */
        if (Adapter->HisRegCpy & HIS_CmdUpLdRdy) {
            rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
            Adapter->HisRegCpy &= ~HIS_CmdUpLdRdy;
            rt_sem_release(&driver_sem);

            wlan_process_rx_command(priv);
        }

        /* Any received data? */
        if (Adapter->HisRegCpy & HIS_RxUpLdRdy) {
            rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
            Adapter->HisRegCpy &= ~HIS_RxUpLdRdy;
            rt_sem_release(&driver_sem);

            wlan_send_rxskbQ(priv);
        }

        /* Any Card Event */
        if (Adapter->HisRegCpy & HIS_CardEvent) {
            rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
            Adapter->HisRegCpy &= ~HIS_CardEvent;
            rt_sem_release(&driver_sem);

            if (sbi_read_event_cause(priv)) {
                wlan_debug1("main-thread: sbi_read_event_cause failed.\n");
                continue;
            }
            wlan_process_event(priv);
        }

        /* Check if we need to confirm Sleep Request received previously */
        if (Adapter->PSState == PS_STATE_PRE_SLEEP) {
            if (!priv->wlan_dev.dnld_sent && !Adapter->CurCmd) {
                wlan_debug1("Adapter->MediaConnectStatus ==WlanMediaStateConnected");
                PSConfirmSleep(priv, (u16) Adapter->PSMode);
            }
        }

        /* The PS state is changed during processing of 
         * Sleep Request event above 
         */
        if ((Adapter->PSState == PS_STATE_SLEEP)
            || (Adapter->PSState == PS_STATE_PRE_SLEEP)) {
            continue;
        }

        /* Execute the next command */
        if (!priv->wlan_dev.dnld_sent && !Adapter->CurCmd) {
            ExecuteNextCommand(priv);
        }

        if (!priv->wlan_dev.dnld_sent
            && !wmm_lists_empty(priv) && !wmm_is_queue_stopped(priv)) {
            if ((Adapter->PSState == PS_STATE_FULL_POWER)
                || (Adapter->sleep_period.period == 0)
                || (Adapter->TxLockFlag == FALSE)) {
                wmm_process_tx(priv);
            }
        }

    }
    LEAVE();
    return ;
}

/**
 * @brief This function adds the card. it will probe the
 * card, allocate the wlan_priv and initialize the device. 
 *  
 *  @param card    A pointer to card
 *  @return        A pointer to wlan_private structure
 */
static wlan_private * wlan_FW_thread_init(struct rt_wlan_dev *wlandev)
{
	struct rt_wlan_dev *dev = NULL;
  	wlan_private *priv = NULL;
   	if(wlandev==NULL){
		wlan_debug1( "wlan add card input error\n");
		return NULL;
   	}
   	dev=wlandev;
	priv = (wlan_private*)rt_malloc(sizeof(wlan_private));
 	if(!priv ) {
       	wlan_debug1( "Init ethernet device private failed!\n");
       	 return NULL;
    	}
	rt_memset(priv,0x00,sizeof(wlan_private));
	dev->priv=priv;
	wlanpriv= priv;
	wlan_eth=dev;
	priv->adapter =(wlan_adapter*) rt_malloc(sizeof(wlan_adapter));
 	if(!priv->adapter) {
        wlan_debug1("Allocate buffer for wlan_adapter failed!\n");
        goto err_malloc;
    	}
 	rt_memset(priv->adapter, 0, sizeof(wlan_adapter));
	rt_sem_init(&priv->adapter->wmm.flowcrsem, "tx_flowcr", 0, RT_IPC_FLAG_FIFO);
	priv->wlan_dev.netdev = dev;
	rt_event_init(&priv->adapter->ds_awake_q, "deepsleep", RT_IPC_FLAG_FIFO);
	INIT_LIST_HEAD(&priv->adapter->CmdFreeQ);
       INIT_LIST_HEAD(&priv->adapter->CmdPendingQ);
	priv->MainThread.priv = priv;
	rt_thread_init(&priv->MainThread.task,
				   "wlan_men_thread",
                   wlan_service_main_thread,
                   &priv->MainThread,
                   &main_thread_stack[0],
                   sizeof(main_thread_stack), 121, 100);
       rt_thread_startup(&priv->MainThread.task);
	rt_sem_init(&tx_sem_lock, "wlan_tx_lock", 1, RT_IPC_FLAG_FIFO);

	if (spi_register_dev(priv) < 0) {
        wlan_debug1("Failed to register wlan device!\n");
        goto err_registerdev;
        }
	wlan_debug2("%s: Marvell Wlan 802.11 Adapter "
           "revision 0x%02X at IRQ %i\n", dev->name,
           priv->adapter->chip_rev, dev->irq);
	/* init FW and HW */
    if (wlan_init_fw(priv)) {
        wlan_debug1("Firmware Init Failed\n");
        goto err_init_fw;
    }
	 return priv;
err_init_fw:
err_registerdev:
err_malloc:
    rt_free(priv);
    wlanpriv = NULL;
    return NULL;
}
/** 
 *  @brief This function removes the card.
 *  
 *  @param priv    A pointer to card
 *  @return        WLAN_STATUS_SUCCESS
 */
static int
wlan_remove_card(void *card)
{
    wlan_private *priv = wlanpriv;
    wlan_adapter *Adapter;
    struct rt_wlan_dev *dev;
    ENTER();

    if (!priv) {
        LEAVE();
        return WLAN_STATUS_SUCCESS;
    }

    Adapter = priv->adapter;

    if (!Adapter) {
        LEAVE();
        return WLAN_STATUS_SUCCESS;
    }

    dev = priv->wlan_dev.netdev;


	rt_event_send(&Adapter->ds_awake_q, 0x01);

    if (Adapter->CurCmd) {
        rt_kprintf("Wake up current cmdwait_q\n");

		  rt_event_send(&Adapter->CurCmd->cmdwait, CmdWaitQWoken);

    }

    Adapter->CurCmd = NULL;

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        wlan_clean_txrx(priv);
        Adapter->MediaConnectStatus = WlanMediaStateDisconnected;
    }

    if (Adapter->PSMode == Wlan802_11PowerModeMAX_PSP) {
        Adapter->PSMode = Wlan802_11PowerModeCAM;
        PSWakeup(priv, HostCmd_OPTION_WAITFORRSP);
    }
    if (Adapter->IsDeepSleep == TRUE) {
        Adapter->IsDeepSleep = FALSE;
    }

    PrepareAndSendCommand(priv, HostCmd_CMD_802_11_RESET, 0, 0, 0, NULL);



    wlan_clean_txrx(priv);

    Adapter->SurpriseRemoved = TRUE;

    /* Stop the thread servicing the interrupts */

    rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);
    wlan_free_adapter(priv);

    /* Last reference is our one */
    wlan_debug3("Unregister finish\n");

    priv->wlan_dev.netdev = NULL;

    wlanpriv = NULL;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/********************************************************
        Global Functions
********************************************************/

/**
 * @brief This function sends the rx packets to the os from the skb queue
 *
 * @param priv  A pointer to wlan_private structure
 * @return  n/a
 */
void
wlan_send_rxskbQ(wlan_private * priv)
{
    struct rt_wlan_dev* netdev=priv->wlan_dev.netdev;
    rt_err_t result;
    ENTER();
  
    result = eth_device_ready(&(netdev->parent));
	if(result!=RT_EOK)
	wlan_debug1("wlan_send_rxskbQ %d",result);
    RT_ASSERT(result == RT_EOK);
    
    LEAVE();
}
/* reception packet. */
struct pbuf *rt_wlan_dev_rx(rt_device_t dev)
{
	struct rt_wlan_dev*netdev=(struct rt_wlan_dev*)(dev->user_data);
	wlan_private * priv=netdev->priv;
	struct pbuf* p=	RT_NULL;
	struct sk_buff *skb=RT_NULL;
	rt_err_t result;
   	if (priv->adapter) {
       	skb = wlan_pop_rx_skb(&priv->adapter->RxSkbQ);
		if(skb==RT_NULL)
		{
		return RT_NULL;
		}
	
    	p=ProcessRxedPacket(priv, skb);
       wlan_debug3("free skb %x,data %x",(u32)skb,(u32)skb->data);
    	if(skb!=RT_NULL)
    	{
    		if(skb->head!=RT_NULL)
    		rt_free(skb->head);
    		rt_free(skb);
    	}
    	if (!list_empty((struct list_head *) (&priv->adapter->RxSkbQ))) {
      		result = eth_device_ready(&(priv->wlan_dev.netdev->parent));
		if(result!=RT_EOK)
		wlan_debug1("rt_wlan_dev_rx %d",result);
   	 	RT_ASSERT(result == RT_EOK);
    	}
	}
    return p;
}

/** 
 *  @brief This function finds the CFP in 
 *  region_cfp_table based on region and band parameter.
 *  
 *  @param region  The region code
 *  @param band    The band
 *  @param cfp_no  A pointer to CFP number
 *  @return        A pointer to CFP
 */
CHANNEL_FREQ_POWER *
wlan_get_region_cfp_table(u8 region, u8 band, int *cfp_no)
{
    int i;

    ENTER();

    for (i = 0; i < sizeof(region_cfp_table) / sizeof(region_cfp_table_t);
         i++) {
        wlan_debug3( "region_cfp_table[i].region=%d\n",
               region_cfp_table[i].region);
        if (region_cfp_table[i].region == region) {
            {
                *cfp_no = region_cfp_table[i].cfp_no_BG;
                LEAVE();
                return region_cfp_table[i].cfp_BG;
            }
        }
    }

    LEAVE();
    return NULL;
}

/** 
 *  @brief This function sets region table. 
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param region  The region code
 *  @param band    The band
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_set_regiontable(wlan_private * priv, u8 region, u8 band)
{
    wlan_adapter *Adapter = priv->adapter;
    int i = 0;

    CHANNEL_FREQ_POWER *cfp;
    int cfp_no;
    ENTER();
    memset(Adapter->region_channel, 0, sizeof(Adapter->region_channel));

    {
        cfp = wlan_get_region_cfp_table(region, band, &cfp_no);
        if (cfp != NULL) {
            Adapter->region_channel[i].NrCFP = cfp_no;
            Adapter->region_channel[i].CFP = cfp;
        } else {
            wlan_debug3("wrong region code %#x in Band B-G\n", region);
            return WLAN_STATUS_FAILURE;
        }
        Adapter->region_channel[i].Valid = TRUE;
        Adapter->region_channel[i].Region = region;
        Adapter->region_channel[i].Band = band;
        i++;
    }
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function handles the interrupt. it will change PS
 *  state if applicable. it will wake up main_thread to handle
 *  the interrupt event as well.
 *  
 */
void
wlan_interrupt(struct rt_wlan_dev *dev)
{
  
    wlan_private *priv=wlanpriv;
    priv->adapter->IntCounter++;

    wlan_debug3 ("*\n");

    priv->adapter->WakeupTries = 0;

    if (priv->adapter->PSState == PS_STATE_SLEEP) {
        priv->adapter->PSState = PS_STATE_AWAKE;
    }
					  
    rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);
}

/** 
 *  @brief This function initializes module.
 *  
 *  @param     n/a    A pointer to rt_wlan_dev structure
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int wlan_init_module(struct rt_wlan_dev * wlan_dev)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_private * prv=RT_NULL;
    wlan_debug3("start wlan device init..... \r\n");
    if(wlan_dev==NULL)
    {
	 	ret = WLAN_STATUS_FAILURE;
        goto done;
    }
    
    rt_event_init(&wlan_tx_event, "wlantx", RT_IPC_FLAG_FIFO);
    prv=wlan_FW_thread_init(wlan_dev); 
    if(prv==NULL){
		ret = WLAN_STATUS_FAILURE;
        	goto done;
    }

done:
   
    return ret;
}
