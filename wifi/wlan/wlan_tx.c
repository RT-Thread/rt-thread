/** @file wlan_tx.c
  * @brief This file contains the handling of TX in wlan
  * driver.
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
  */
/********************************************************
Change log:
	09/28/05: Add Doxygen format comments
	12/13/05: Add Proprietary periodic sleep support
	01/05/06: Add kernel 2.6.x support	
	04/06/06: Add TSPEC, queue metrics, and MSDU expiry support
********************************************************/

#include	"include.h"
#include <netif/ethernetif.h>
#define TX_QUEUED_PACKET_LOWER_LIMIT   40
#define TX_QUEUED_PACKET_UPPER_LIMIT   50
/********************************************************
		Local Variables
********************************************************/

/********************************************************
		Global Variables
********************************************************/
extern struct rt_event wlan_tx_event;
/********************************************************
		Local Functions
********************************************************/

/** 
 *  @brief This function processes a single packet and sends
 *  to IF layer
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param skb     A pointer to skb which includes TX packet
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
SendSinglePacket(wlan_private * priv, struct sk_buff *skb)
{
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    TxPD LocalTxPD;
    TxPD *pLocalTxPD = &LocalTxPD;
    u8 *ptr = Adapter->TmpTxBuf;
   struct pbuf *phead;
   int curlen;
   rt_base_t level;
    ENTER();

    if (!skb->len || (skb->len > MRVDRV_ETH_TX_PACKET_BUFFER_SIZE)) {
        wlan_debug1( "Tx Error: Bad skb length %d : %d\n",
               skb->len, MRVDRV_ETH_TX_PACKET_BUFFER_SIZE);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    memset(pLocalTxPD, 0, sizeof(TxPD));

    pLocalTxPD->TxPacketLength = skb->len;

    if (Adapter->PSState != PS_STATE_FULL_POWER) {
        if (TRUE == CheckLastPacketIndication(priv)) {
            Adapter->TxLockFlag = TRUE;
            pLocalTxPD->Flags = MRVDRV_TxPD_POWER_MGMT_LAST_PACKET;
        }
    }

    /* offset of actual data */
    pLocalTxPD->TxPacketLocation = sizeof(TxPD);

    if (pLocalTxPD->TxControl == 0) {
        /* TxCtrl set by user or default */
        pLocalTxPD->TxControl = Adapter->PktTxCtrl;
    }

    endian_convert_TxPD(pLocalTxPD);

    memcpy(pLocalTxPD->TxDestAddrHigh, skb->data, MRVDRV_ETH_ADDR_LEN);

    memcpy(ptr, pLocalTxPD, sizeof(TxPD));

    ptr += sizeof(TxPD);
    phead=(struct pbuf*)skb->head;
    curlen=0;
    if(phead ->tot_len>=2048)
    {
    	wlan_debug1("tx too long\r\n");
    	goto done;
    }
    while(phead!=RT_NULL&&curlen<phead ->tot_len)
    {
		rt_memcpy(ptr+curlen, phead->payload,phead->len);
		curlen+=phead->len;
		phead=phead->next;
     }

  //  memcpy(ptr, skb->data, skb->len);

    ret = sbi_host_to_card(priv, MVMS_DAT, Adapter->TmpTxBuf,
                           skb->len + sizeof(TxPD));
    if (ret) {
     wlan_debug1("SendSinglePacket Error: sbi_host_to_card failed: 0x%X\n",
              ret);
        Adapter->dbg.num_tx_host_to_card_failure++;
        goto done;
    }
   
    wlan_debug3("Data => FW\n");
    //wmm_process_fw_iface_tx_xfer_start(priv);
    if (--Adapter->wmm.packetsQueued < TX_QUEUED_PACKET_LOWER_LIMIT) {
        wlan_debug2( "WMM: FW OS+: %d\n", Adapter->wmm.packetsQueued);
	  if(Adapter->wmm.downlinkblock==TRUE)
    	 {
    	 	level = rt_hw_interrupt_disable();
    	 	Adapter->wmm.downlinkblock=FALSE;
	       rt_hw_interrupt_enable(level);
		rt_sem_release(&Adapter->wmm.flowcrsem);
         }
    }
	
  done:
    if (!ret) {
        priv->stats.tx_packets++;
        priv->stats.tx_bytes += skb->len;
    } else {
        priv->stats.tx_dropped++;
        priv->stats.tx_errors++;
    }

    /* need to be freed in all cases */
 //   if(skb->head!=NULL)
    {
    	//rt_free(skb->head);
    	rt_free(skb);
     }
    level = rt_hw_interrupt_disable();
    priv->adapter->CurrentTxSkb = NULL;
     rt_hw_interrupt_enable(level);
   rt_event_send(&wlan_tx_event, 0x01);

    LEAVE();
    return ret;
}

/********************************************************
		Global functions
********************************************************/

/** 
 *  @brief This function checks the conditions and sends packet to IF
 *  layer if everything is ok.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   n/a
 */
extern struct rt_semaphore driver_sem;
void wlan_process_tx(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    if (priv->wlan_dev.dnld_sent) {
        wlan_debug1 ("TX Error: dnld_sent = %d, not sending\n",priv->wlan_dev.dnld_sent);
        goto done;
    }

    SendSinglePacket(priv, Adapter->CurrentTxSkb);
    rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
    priv->adapter->HisRegCpy &= ~HIS_TxDnLdRdy;
    rt_sem_release(&driver_sem);

  done:
    LEAVE();
}

/** 
 *  @brief This function queues the packet received from
 *  kernel/upper layer and wake up the main thread to handle it.
 *  
 *  @param priv    A pointer to wlan_private structure
  * @param skb     A pointer to skb which includes TX packet
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */

int wlan_tx_packet(wlan_private * priv, struct pbuf *packet)
{
    u32 flags;
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    rt_base_t level;
    struct sk_buff *skb=RT_NULL;
    struct pbuf* p;
    int datalen=0;
    rt_uint32_t e;
    ENTER();

   skb=rt_malloc(sizeof(struct sk_buff));
   if(skb==RT_NULL)
   {
	wlan_debug1("tx skb malloc failed\r\n");
	return WLAN_STATUS_FAILURE;
   }
  skb->head = (char*)packet;
   wlan_debug3("tx buf %d,%x\n",packet->tot_len, skb->head);
   if (!(skb->head )) {
            wlan_debug1("No free skb data buf\n");
            
            ret = WLAN_STATUS_FAILURE;
	     rt_free(skb);
            return ret;
        }
    skb->data=(char *)packet->payload;
/*    p=packet;
    while(p!=RT_NULL&&datalen< packet->tot_len)
    {
		rt_memcpy(skb->data+datalen, p->payload,p->len);
		datalen+=p->len;
		p=p->next;
     }
 */
    skb->len=packet->tot_len;
     level = rt_hw_interrupt_disable();
    list_add_tail((struct list_head *) skb,
                  (struct list_head *) &Adapter->wmm.txSkbQ);
    Adapter->wmm.packetsQueued++;
    if (!priv->wlan_dev.dnld_sent
        || (Adapter->wmm.packetsQueued >= TX_QUEUED_PACKET_UPPER_LIMIT)) {
        wlan_debug1( "WMM: APP OS-: %d\n", Adapter->wmm.packetsQueued);
       
        Adapter->wmm.downlinkblock=TRUE;
    }
    rt_hw_interrupt_enable(level);
   
    rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);
    if(Adapter->wmm.downlinkblock==TRUE)
    {
		rt_sem_take(&Adapter->wmm.flowcrsem, RT_WAITING_FOREVER);
    }
    rt_event_recv(&wlan_tx_event,0x1,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&e);
    LEAVE();

    return ret;
}

/** 
 *  @brief This function tells firmware to send a NULL data packet.
 *  
 *  @param priv     A pointer to wlan_private structure
 *  @param flags    Trasnit Pkt Flags
 *  @return 	    n/a
 */
int
SendNullPacket(wlan_private * priv, u8 flags)
{
    wlan_adapter *Adapter = priv->adapter;
    TxPD txpd;
    int ret = WLAN_STATUS_SUCCESS;
    u8 *ptr = Adapter->TmpTxBuf;

    ENTER();

    if (Adapter->SurpriseRemoved == TRUE) {
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    if (Adapter->MediaConnectStatus == WlanMediaStateDisconnected) {
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    memset(&txpd, 0, sizeof(TxPD));

    txpd.TxControl = Adapter->PktTxCtrl;
    txpd.Flags = flags;
    txpd.Priority = WMM_HIGHEST_PRIORITY;
    txpd.TxPacketLocation = sizeof(TxPD);

    endian_convert_TxPD(&txpd);

    memcpy(ptr, &txpd, sizeof(TxPD));

   ret = sbi_host_to_card(priv, MVMS_DAT, Adapter->TmpTxBuf, sizeof(TxPD));

    if (ret != 0) {
        wlan_debug1( "TX Error: SendNullPacket failed!\n");
        Adapter->dbg.num_tx_host_to_card_failure++;
        goto done;
    }
    wlan_debug3("Null data => FW\n");


  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function check if we need send last packet indication.
 *  
 *  @param priv     A pointer to wlan_private structure
 *
 *  @return 	   TRUE or FALSE
 */
BOOLEAN
CheckLastPacketIndication(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    BOOLEAN ret = FALSE;
    BOOLEAN prop_ps = TRUE;

    ENTER();

    if (Adapter->sleep_period.period == 0 || Adapter->gen_null_pkg == FALSE     /* for UPSD certification tests */
        ) {
        LEAVE();
        return ret;
    }

    if (wmm_lists_empty(priv)) {
 //       if (((Adapter->CurBssParams.wmm_uapsd_enabled == TRUE)
 //            && (Adapter->wmm.qosinfo != 0)) || prop_ps) {
            ret = TRUE;
 //       }
    }

    LEAVE();
    return ret;
}
