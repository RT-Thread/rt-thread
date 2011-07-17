/** @file wlan_wmm.c
 * @brief This file contains functions for WMM.
 * 
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/********************************************************
Change log:
    10/04/05: Add Doxygen format comments
    11/11/05: Add support for WMM Status change event
    01/05/06: Add kernel 2.6.x support  
    01/11/06: Conditionalize new scan/join code modifications.
    04/06/06: Add TSPEC, queue metrics, and MSDU expiry support
********************************************************/
#include    "include.h"
#include	"wlan_defs.h"
/********************************************************
        Local Variables
********************************************************/

/** Maximum value FW can accept for driver delay in packet transmission */
#define DRV_PKT_DELAY_TO_FW_MAX   512

/** Set limit of driver packet delay for use in MSDU lifetime expiry and
 *   traffic stream metrics.
 *
 *   - Set to 0 to disable driver delay in firmware
 *   - Set to DRV_PKT_DELAY_TO_FW_MAX to enable all possible values
 */
#define DRV_PKT_DELAY_TO_FW_LIMIT  0

/** Upper and Lower threshold for packet queuing in the driver
 *
 *    - When the number of packets queued reaches the upper limit,
 *      the driver will stop the net queue in the app/kernel space.
 *
 *    - When the number of packets drops beneath the lower limit after
 *      having reached the upper limit, the driver will restart the net
 *      queue.
 */
#define WMM_QUEUED_PACKET_LOWER_LIMIT   40
#define WMM_QUEUED_PACKET_UPPER_LIMIT   50

#define IPTOS_OFFSET 5

static const u8 wmm_info_ie[] = { WMM_IE, 0x07,
    0x00, 0x50, 0xf2, 0x02,
    0x00, 0x01, 0x00
};

/********************************************************
        Local Functions
********************************************************/
#ifdef DEBUG_LEVEL2
/** 
 *  @brief Debug print function to display the priority parameters for a WMM AC
 *
 *  @param acStr    String pointer giving the AC enumeration (BK, BE, VI, VO)
 *  @param pACParam Pointer to the AC paramters to display
 *
 *  @return         void
 */
static void
wmm_debugPrintAC(wlan_wmm_ac_e acVal,
                 const IEEEtypes_WmmAcParameters_t * pACParam)
{
    const char *acStr[] = { "BK", "BE", "VI", "VO" };

    PRINTM(INFO, "WMM AC_%s: ACI=%d, ACM=%d, Aifsn=%d, "
           "EcwMin=%d, EcwMax=%d, TxopLimit=%d\n",
           acStr[acVal], pACParam->AciAifsn.Aci, pACParam->AciAifsn.Acm,
           pACParam->AciAifsn.Aifsn, pACParam->Ecw.EcwMin,
           pACParam->Ecw.EcwMax, wlan_le16_to_cpu(pACParam->TxopLimit));
}

#define PRINTM_AC(acStr, pACParam) wmm_debugPrintAC(acStr, pACParam)
#else
#define PRINTM_AC(acStr, pACParam)
#endif
#if 0
/**
 *  @brief Compute the difference between two timestamps.
 *
 *  @param pTv1 Pointer to timestamp1
 *  @param pTv2 Pointer to timestamp2
 *
 *  @return Time difference in ms between pTv1 and pTv2 (pTv1 - pTv2)
 */
static int
timeval_diff_in_ms(const struct timeval *pTv1, const struct timeval *pTv2)
{
 /*   int diff_ms;

    diff_ms = (pTv1->tv_sec - pTv2->tv_sec) * 1000;
    diff_ms += (pTv1->tv_usec - pTv2->tv_usec) / 1000;

    return diff_ms;
*/
}
#endif
#if 0
/** 
 *  @brief Set the WMM queue priorities to their default values
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         void
 */
static void
wmm_default_queue_priorities(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    /* default queue priorities: VO->VI->BE->BK */
 //   Adapter->wmm.queuePriority[0] = WMM_AC_VO;
 //   Adapter->wmm.queuePriority[1] = WMM_AC_VI;
 //   Adapter->wmm.queuePriority[2] = WMM_AC_BE;
 //   Adapter->wmm.queuePriority[3] = WMM_AC_BK;
}
#endif
/** 
 *  @brief Initialize WMM priority queues
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         void
 */
static void
wmm_setup_queue_priorities(wlan_private * priv)
{
#if 0
    wlan_adapter *Adapter = priv->adapter;
    IEEEtypes_WmmParameter_t *pWmmIe;
    wlan_wmm_ac_e acVal;
    u16 cwmax, cwmin, avg_back_off, tmp[4];
    int i, j, n;

    if (Adapter->wmm.enabled == FALSE) {
        /* WMM is not enabled, just set the defaults and return */
        wmm_default_queue_priorities(priv);
        return;
    }

    n = 0;
    pWmmIe = &Adapter->CurBssParams.BSSDescriptor.wmmIE;

//    HEXDUMP("WMM: setup_queue_priorities: param IE",
//            (u8 *) pWmmIe, sizeof(IEEEtypes_WmmParameter_t));

    PRINTM(INFO, "WMM Parameter IE: version=%d, "
           "QoSInfo Parameter Set Count=%d, Reserved=%#x\n",
           pWmmIe->VendHdr.Version, pWmmIe->QoSInfo.ParaSetCount,
           pWmmIe->Reserved);

    for (acVal = WMM_AC_BK; acVal <= WMM_AC_VO; acVal++) {
        cwmax = (1 << pWmmIe->AcParams[acVal].Ecw.EcwMax) - 1;
        cwmin = (1 << pWmmIe->AcParams[acVal].Ecw.EcwMin) - 1;
        avg_back_off = (cwmin >> 1) + pWmmIe->AcParams[acVal].AciAifsn.Aifsn;
        Adapter->wmm.queuePriority[n] = acVal;
        tmp[n++] = avg_back_off;

        PRINTM(INFO, "WMM: CWmax=%d CWmin=%d Avg Back-off=%d\n",
               cwmax, cwmin, avg_back_off);
        PRINTM_AC(acVal, &pWmmIe->AcParams[acVal]);
    }

//    HEXDUMP("WMM: avg_back_off", (u8 *) tmp, sizeof(tmp));
//    HEXDUMP("WMM: queuePriority", Adapter->wmm.queuePriority,
//            sizeof(Adapter->wmm.queuePriority));

    /* bubble sort */
    for (i = 0; i < n; i++) {
        for (j = 1; j < n - i; j++) {
            if (tmp[j - 1] > tmp[j]) {
                SWAP_U16(tmp[j - 1], tmp[j]);
                SWAP_U8(Adapter->wmm.queuePriority[j - 1],
                        Adapter->wmm.queuePriority[j]);
            } else if (tmp[j - 1] == tmp[j]) {
                if (Adapter->wmm.queuePriority[j - 1]
                    < Adapter->wmm.queuePriority[j]) {
                    SWAP_U8(Adapter->wmm.queuePriority[j - 1],
                            Adapter->wmm.queuePriority[j]);
                }
            }
        }
    }

//    HEXDUMP("WMM: avg_back_off, sort", (u8 *) tmp, sizeof(tmp));
//    HEXDUMP("WMM: queuePriority, sort", Adapter->wmm.queuePriority,
//            sizeof(Adapter->wmm.queuePriority));
#endif
}
#if 0
/** 
 *  @brief pop up the highest skb from wmm queue
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         void
 */
static void
wmm_pop_highest_prio_skb(wlan_private * priv)
{
 /*   wlan_adapter *Adapter = priv->adapter;
    int i;
    u8 ac;

    ENTER();

    for (i = 0; i < MAX_AC_QUEUES; i++) {
        ac = Adapter->wmm.queuePriority[i];
        if (!list_empty((struct list_head *) &Adapter->wmm.txSkbQ[ac])) {
            PRINTM(DATA, "WMM: Highest prio pkt in AC Queue %d\n", i);
            Adapter->CurrentTxSkb = Adapter->wmm.txSkbQ[ac].next;
            Adapter->wmm.packetsOut[ac]++;
            list_del((struct list_head *) Adapter->wmm.txSkbQ[ac].next);
            break;
        }
    }

    LEAVE();
*/
}
#endif
#if 0
/** 
 *  @brief Evaluate whether or not an AC is to be downgraded
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *  @param evalAC   AC to evaluate for downgrading
 *
 *  @return WMM AC the evalAC traffic is to be sent on.  
 */
static wlan_wmm_ac_e
wmm_eval_downgrade_ac(wlan_private * priv, wlan_wmm_ac_e evalAC)
{
#if 0
    wlan_wmm_ac_e downAC;
    wlan_wmm_ac_e retAC;
    WmmAcStatus_t *pACStatus;

    pACStatus = &priv->adapter->wmm.acStatus[evalAC];

    if (pACStatus->Disabled == FALSE) {
        /* Okay to use this AC, its enabled */
        return evalAC;
    }

    /* Setup a default return value of the lowest priority */
    retAC = WMM_AC_BK;

    /*
     *  Find the highest AC that is enabled and does not require admission
     *    control.  The spec disallows downgarding to an AC which is enabled
     *    due to a completed admission control.  Unadmitted traffic is not 
     *    to be sent on an AC with admitted traffic.
     */
    for (downAC = WMM_AC_BK; downAC < evalAC; downAC++) {
        pACStatus = &priv->adapter->wmm.acStatus[downAC];

        if ((pACStatus->Disabled == FALSE)
            && (pACStatus->FlowRequired == FALSE)) {
            /* AC is enabled and does not require admission control */
            retAC = downAC;
        }
    }

    return retAC;
#endif
}
#endif
/** 
 *  @brief Downgrade WMM priority queue
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         void
 */
static void
wmm_setup_ac_downgrade(wlan_private * priv)
{
#if 0
    wlan_adapter *Adapter = priv->adapter;
    wlan_wmm_ac_e acVal;

    PRINTM(INFO, "WMM: AC Priorities: BK(0), BE(1), VI(2), VO(3)\n");

    if (Adapter->wmm.enabled == FALSE) {
        /* WMM is not enabled, default priorities */
        for (acVal = WMM_AC_BK; acVal <= WMM_AC_VO; acVal++) {
            for (acVal = WMM_AC_BK; acVal <= WMM_AC_VO; acVal++) {
                Adapter->wmm.acDowngradedVals[acVal] = acVal;
            }
        }
    } else {
        for (acVal = WMM_AC_BK; acVal <= WMM_AC_VO; acVal++) {
            Adapter->wmm.acDowngradedVals[acVal]
                = wmm_eval_downgrade_ac(priv, acVal);
            PRINTM(INFO, "WMM: AC PRIO %d maps to %d\n",
                   acVal, Adapter->wmm.acDowngradedVals[acVal]);
        }
    }
#endif
}

/** 
 *  @brief Convert the IP TOS field to an WMM AC Queue assignment
 *
 *  @param tos  IP TOS field
 *
 *  @return     WMM AC Queue mapping of the IP TOS field
 */
wlan_wmm_ac_e
wmm_convert_tos_to_ac(int tos)
{
    u8 tosIdx;

    /* Map of TOS UP values to WMM AC */
    const wlan_wmm_ac_e tos_to_ac[] = { WMM_AC_BE,
        WMM_AC_BK,
        WMM_AC_BK,
        WMM_AC_BE,
        WMM_AC_VI,
        WMM_AC_VI,
        WMM_AC_VO,
        WMM_AC_VO
    };

    tosIdx = tos >> IPTOS_OFFSET;

    if (tosIdx >= NELEMENTS(tos_to_ac)) {
        return WMM_AC_BE;
    }

    return tos_to_ac[tosIdx];
}

/** 
 *  @brief  Evaluate a given AC and downgrade it to a lower AC if the
 *          WMM Parameter IE received from the AP indicates that the AP
 *          is disabled (due to call admission control (ACM bit)
 *
 *  @param priv   Pointer to the wlan_private driver data struct
 *  @param acVal  AC to evaulate for downgrading
 *
 *  @return       Same AC as input if downgrading not required or
 *                the AC the traffic for the given AC should be downgraded to 
 */
wlan_wmm_ac_e
wmm_downgrade_ac(wlan_private * priv, wlan_wmm_ac_e acVal)
{
    wlan_adapter *Adapter = priv->adapter;
#if 0
    return (Adapter->wmm.acDowngradedVals[acVal]);
#endif
}
#if 0
/** 
 *  @brief  Map the IP TOS field to a user priority value
 *
 *  @param tos  IP TOS field
 *
 *  @return     User priority tos input parameter maps to
 */
static u8
wmm_tos_to_priority(u8 tos)
{
    u8 tosIdx;
    const u8 tos_to_priority[] = {
        /* Priority   DSCP_P2   DSCP_P1  DSCP_P0   WMM_AC   */
        0x00,                   /*    0         0        0       AC_BE   */
        0x01,                   /*    0         0        1       AC_BK   */
        0x02,                   /*    0         1        0       AC_BK   */
        0x03,                   /*    0         1        1       AC_BE   */
        0x04,                   /*    1         0        0       AC_VI   */
        0x05,                   /*    1         0        1       AC_VI   */
        0x06,                   /*    1         1        0       AC_VO   */
        0x07                    /*    1         1        1       AC_VO   */
    };

    tosIdx = tos >> IPTOS_OFFSET;

    if (tosIdx >= NELEMENTS(tos_to_priority)) {
        return WMM_AC_BE;
    }

    return tos_to_priority[tosIdx];
}
#endif
/**
 *  @brief  Process a transfer of a data packet to the firmware from the 
 *          driver queue in order to manipulate flow control in the driver.
 *
 *  @param priv  Pointer to the wlan_private driver data struct
 *
 *  @return      void
 */
void
wmm_process_fw_iface_tx_xfer_start(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    if (--Adapter->wmm.packetsQueued < WMM_QUEUED_PACKET_LOWER_LIMIT) {
        wlan_debug3("WMM: FW OS+: %d\n", Adapter->wmm.packetsQueued);

    }
}

/**
 *  @brief  Process the completion of a data packet transfer to the firmware 
 *          from the driver queue in order to manipulate flow control in the
 *          driver.
 *
 *  @param priv  Pointer to the wlan_private driver data struct
 *
 *  @return      void
 *
 */
void
wmm_process_fw_iface_tx_xfer_end(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    if (Adapter->wmm.packetsQueued) {
        wlan_debug3( "WMM: FW OS-: %d\n", Adapter->wmm.packetsQueued);

    }
}

/**
 *  @brief  Process a transfer of a data packet from the OS to the driver
 *          queue in order to manipulate flow control in the driver.
 *
 *  @param priv  Pointer to the wlan_private driver data struct
 *
 *  @return      void
 */
void
wmm_process_app_iface_tx(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    Adapter->wmm.packetsQueued++;

    if (!priv->wlan_dev.dnld_sent
        || (Adapter->wmm.packetsQueued >= WMM_QUEUED_PACKET_UPPER_LIMIT)) {
        wlan_debug1 ("WMM: APP OS-: %d\n", Adapter->wmm.packetsQueued);

    }
}

/**
 *  @brief  Stop the WMM data queues.  Traffic is still accepted from the
 *          OS until the buffer limits are reached.
 *
 *  @param priv  Pointer to the wlan_private driver data struct
 *
 *  @return      void
 */
void
wmm_stop_queue(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    wlan_debug2("WMM: Q-: %d\n", Adapter->wmm.packetsQueued);
    Adapter->wmm.queueStopped = TRUE;
}

/**
 *  @brief  Start/re-start the WMM data queues and indicate to the OS layer 
 *          that data is being accepted again.
 *
 *  @param priv  Pointer to the wlan_private driver data struct
 *
 *  @return      void
 */
void
wmm_start_queue(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    wlan_debug3("WMM: Q+: %d\n", Adapter->wmm.packetsQueued);
    Adapter->wmm.queueStopped = FALSE;
   if (Adapter->wmm.packetsQueued) {
       rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);
   }
 

}

/** 
 *  @brief  Query the status of the WMM queues.  Determine if the driver data
 *          path is active or not.
 *
 *  @param priv  Pointer to the wlan_private driver data struct
 *
 *  @return      TRUE if WMM queues have been stopped, FALSE if still active
 */
int
wmm_is_queue_stopped(wlan_private * priv)
{
    return (priv->adapter->wmm.queueStopped == TRUE);
}

/** 
 *  @brief Initialize the WMM state information and the WMM data path queues.
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         void
 */
void
wmm_init(wlan_private * priv)
{
 /*   wlan_adapter *Adapter = priv->adapter;
    int i;
    memset(&Adapter->wmm, 0x00, sizeof(Adapter->wmm));

    for (i = 0; i < MAX_AC_QUEUES; i++) {
        INIT_LIST_HEAD((struct list_head *) &Adapter->wmm.txSkbQ[i]);
    }

    Adapter->wmm.required = FALSE;
 */
 //   Adapter->gen_null_pkg = TRUE;       /*Enable NULL Pkg generation */
  wlan_adapter *Adapter = priv->adapter;
 INIT_LIST_HEAD((struct list_head *) &Adapter->wmm.txSkbQ);
}

/** 
 *  @brief Setup the queue priorities and downgrade any queues as required
 *         by the WMM info.  Setups default values if WMM is not active
 *         for this association.
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         void
 */
void
wmm_setup_queues(wlan_private * priv)
{
    wmm_setup_queue_priorities(priv);
    wmm_setup_ac_downgrade(priv);
}

/** 
 *  @brief implement WMM enable command
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *  @param wrq      Pointer to user data
 *
 *  @return         WLAN_STATUS_SUCCESS if success; otherwise <0
 */
//int wlan_wmm_enable_ioctl(wlan_private * priv, struct iwreq *wrq)
//{
/*    wlan_adapter *Adapter = priv->adapter;
    ulong flags;
    int data, data1;
    int *val;
	rt_base_t level;
    ENTER();

    data = *((int *) (wrq->u.name + SUBCMD_OFFSET));
    switch (data) {
*/
 //   case CMD_DISABLED:         /* disable */
/*        if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
            return -EPERM;
        }

        spin_lock_irqsave(&Adapter->CurrentTxLock, flags);
		level = rt_hw_interrupt_disable();
        Adapter->wmm.required = FALSE;
        if (!Adapter->wmm.enabled) {
            spin_unlock_irqrestore(&Adapter->CurrentTxLock, flags);
			rt_hw_interrupt_enable(level);
            data1 = Adapter->wmm.required;
            val = (int *) wrq->u.name;
            *val = data;
            return WLAN_STATUS_SUCCESS;
        } else {
            Adapter->wmm.enabled = 0;
        }

        if (Adapter->CurrentTxSkb) {
//            kfree_skb(Adapter->CurrentTxSkb);
            OS_INT_DISABLE;
            Adapter->CurrentTxSkb = NULL;
            OS_INT_RESTORE;
            priv->stats.tx_dropped++;
        }
		rt_hw_interrupt_enable(level);
        //spin_unlock_irqrestore(&Adapter->CurrentTxLock, flags);
        break;
 */
 //   case CMD_ENABLED:          /* enable */
 /*       if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
            return -EPERM;
        }
		level = rt_hw_interrupt_disable();
        spin_lock_irqsave(&Adapter->CurrentTxLock, flags);
        Adapter->wmm.required = TRUE;
        spin_unlock_irqrestore(&Adapter->CurrentTxLock, flags);
		rt_hw_interrupt_enable(level);
        break;

    case CMD_GET:
        break;
    default:
        PRINTM(INFO, "Invalid option\n");
        return -EINVAL;
    }

    data = Adapter->wmm.required;
    val = (int *) wrq->u.name;
    *val = data;
   */
//    return WLAN_STATUS_SUCCESS;
//}

/** 
 *  @brief Implement cmd HostCmd_CMD_WMM_GET_STATUS
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *  @param cmd      Pointer to CMD buffer 
 *  @param InfoBuf  Pointer to cmd data
 *
 *  @return         WLAN_STATUS_SUCCESS
 */
int
wlan_cmd_wmm_get_status(wlan_private * priv,
                        HostCmd_DS_COMMAND * cmd, void *InfoBuf)
{
    wlan_debug3("WMM: WMM_GET_STATUS cmd sent\n");
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_WMM_GET_STATUS);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_WMM_GET_STATUS) + S_DS_GEN);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief  Send a command to firmware to retrieve the current WMM status
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         WLAN_STATUS_SUCCESS; WLAN_STATUS_FAILURE
 */
int
sendWMMStatusChangeCmd(wlan_private * priv)
{
    return PrepareAndSendCommand(priv, HostCmd_CMD_WMM_GET_STATUS,
                                 0, 0, 0, NULL);
}

/** 
 *  @brief Check if wmm TX queue is empty
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *
 *  @return         FALSE if not empty; TRUE if empty
 */
int wmm_lists_empty(wlan_private * priv)
{
    if (!list_empty((struct list_head *) &priv->adapter->wmm.txSkbQ)) {
            return FALSE;
 	}
    return TRUE;

}

/**
 *  @brief Process the GET_WMM_STATUS command response from firmware
 *
 *  The GET_WMM_STATUS command returns multiple TLVs for:
 *      - Each AC Queue status
 *      - Current WMM Parameter IE
 *
 *  This function parses the TLVs and then calls further functions
 *   to process any changes in the queue prioritization or state.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param resp    Pointer to the command response buffer including TLVs
 *                 TLVs for each queue and the WMM Parameter IE.
 * 
 *  @return WLAN_STATUS_SUCCESS
 */
int
wlan_cmdresp_wmm_get_status(wlan_private * priv,
                            const HostCmd_DS_COMMAND * resp)
{
    wlan_adapter *Adapter = priv->adapter;
    u8 *pCurrent = (u8 *) & resp->params.getWmmStatus;
    u32 respLen = resp->Size;
    int valid = TRUE;
    int enableData = TRUE;

    MrvlIEtypes_Data_t *pTlvHdr;
    MrvlIEtypes_WmmQueueStatus_t *pTlvWmmQStatus;
    IEEEtypes_WmmParameter_t *pWmmParamIe;
    WmmAcStatus_t *pACStatus;

    wlan_debug3("WMM: WMM_GET_STATUS cmdresp received: %d\n", respLen);


    while ((respLen >= sizeof(pTlvHdr->Header)) && valid) {
        pTlvHdr = (MrvlIEtypes_Data_t *) pCurrent;
        pTlvHdr->Header.Len = wlan_le16_to_cpu(pTlvHdr->Header.Len);

        switch (wlan_le16_to_cpu(pTlvHdr->Header.Type)) {
        case TLV_TYPE_WMMQSTATUS:
            pTlvWmmQStatus = (MrvlIEtypes_WmmQueueStatus_t *) pTlvHdr;
            wlan_debug3(
                   "CMD_RESP: WMM_GET_STATUS: QSTATUS TLV: %d, %d, %d\n",
                   pTlvWmmQStatus->QueueIndex, pTlvWmmQStatus->FlowRequired,
                   pTlvWmmQStatus->Disabled);

//            pACStatus = &Adapter->wmm.acStatus[pTlvWmmQStatus->QueueIndex];
//            pACStatus->Disabled = pTlvWmmQStatus->Disabled;
//            pACStatus->FlowRequired = pTlvWmmQStatus->FlowRequired;
//            pACStatus->FlowCreated = pTlvWmmQStatus->FlowCreated;
            break;

        case WMM_IE:
            /*
             * Point the regular IEEE IE 2 bytes into the Marvell IE
             *   and setup the IEEE IE type and length byte fields
             */

            pWmmParamIe = (IEEEtypes_WmmParameter_t *) (pCurrent + 2);
            pWmmParamIe->VendHdr.Len = pTlvHdr->Header.Len;
            pWmmParamIe->VendHdr.ElementId = WMM_IE;

            wlan_debug3( "CMD_RESP: WMM_GET_STATUS: WMM Parameter Set: %d\n",
                   pWmmParamIe->QoSInfo.ParaSetCount);

            memcpy((u8 *) & Adapter->CurBssParams.BSSDescriptor.wmmIE,
                   pWmmParamIe, pWmmParamIe->VendHdr.Len + 2);

            break;

        default:
            valid = FALSE;
            break;
        }

        pCurrent += (pTlvHdr->Header.Len + sizeof(pTlvHdr->Header));
        respLen -= (pTlvHdr->Header.Len + sizeof(pTlvHdr->Header));
    }

    wmm_setup_queue_priorities(priv);
    wmm_setup_ac_downgrade(priv);

    if (enableData) {
        wmm_start_queue(priv);
    }

   // send_iwevcustom_event(priv, WMM_CONFIG_CHANGE_INDICATION);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Call back from the command module to allow insertion of a WMM TLV
 *   
 *  If the BSS we are associating to supports WMM, add the required WMM
 *    Information IE to the association request command buffer in the form
 *    of a Marvell extended IEEE IE.
 *     
 *  @param priv        Pointer to the wlan_private driver data struct
 *  @param ppAssocBuf  Output parameter: Pointer to the TLV output buffer,
 *                     modified on return to point after the appended WMM TLV
 *  @param pWmmIE      Pointer to the WMM IE for the BSS we are joining
 * 
 *  @return Length of data appended to the association tlv buffer
 */
u32
wlan_wmm_process_association_req(wlan_private * priv,
                                 u8 ** ppAssocBuf,
                                 IEEEtypes_WmmParameter_t * pWmmIE)
{
    wlan_adapter *Adapter = priv->adapter;
    MrvlIEtypes_WmmParamSet_t *pWmmTlv;
    u32 retLen = 0;

    /* Null checks */
    if (ppAssocBuf == 0)
        return 0;
    if (*ppAssocBuf == 0)
        return 0;
    if (pWmmIE == 0)
        return 0;

    wlan_debug3( "WMM: process assoc req: bss->wmmIe=%x\n",
           pWmmIE->VendHdr.ElementId);
    //in current design, WMM unsupported.//
    if (Adapter->wmm.required && pWmmIE->VendHdr.ElementId == WMM_IE) {
        pWmmTlv = (MrvlIEtypes_WmmParamSet_t *) * ppAssocBuf;
        pWmmTlv->Header.Type = (u16) wmm_info_ie[0];
        pWmmTlv->Header.Type = wlan_cpu_to_le16(pWmmTlv->Header.Type);
        pWmmTlv->Header.Len = (u16) wmm_info_ie[1];
        pWmmTlv->Header.Len = wlan_cpu_to_le16(pWmmTlv->Header.Len);

        memcpy(pWmmTlv->WmmIE, &wmm_info_ie[2], pWmmTlv->Header.Len);
#define QOS_INFO_PARA_MASK 0x0f
/*  
        if (pWmmIE->QoSInfo.QosUAPSD
            && ((Adapter->wmm.qosinfo & QOS_INFO_PARA_MASK) != 0)) {
            memcpy((u8 *) (pWmmTlv->WmmIE + pWmmTlv->Header.Len
                           - sizeof(Adapter->wmm.qosinfo)),
                   &Adapter->wmm.qosinfo, sizeof(Adapter->wmm.qosinfo));
        }
*/
        retLen = sizeof(pWmmTlv->Header) + pWmmTlv->Header.Len;

       wlan_debug3("ASSOC_CMD: WMM IE %d,%d", (u8 *) pWmmTlv, retLen);
        *ppAssocBuf += retLen;
    }

    return retLen;
}

/**
 *   @brief Compute the time delay in the driver queues for a given skb.
 *
 *   When the skb is received at the OS/Driver interface, the current 
 *     time is set in the skb structure.  The difference between the present
 *     time and that received time is computed in this function and limited
 *     based on pre-compiled limits in the driver.
 *
 *   @param skb  Pointer to a sk_buff which has been previously timestamped
 *
 *   @return Time delay of the packet in 2ms units after having limit applied
 */
u8
wmm_compute_driver_packet_delay(const struct sk_buff * skb)
{
    u8 retVal;
 //   struct timeval in_tv;
 //   struct timeval out_tv;
    
    int queue_delay;

    retVal = 0;

//#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,14)
 //   skb_get_timestamp(skb, &in_tv);
//#else
 //   memcpy(&in_tv, &skb->stamp, sizeof(in_tv));
//#endif
   // do_gettimeofday(&out_tv);

   // queue_delay = timeval_diff_in_ms(&out_tv, &in_tv);

    /* Queue delay is passed as a uint8 in units of 2ms (ms shifted
     *  by 1). Min value (other than 0) is therefore 2ms, max is 510ms.
     *
     * Pass max value if queue_delay is beyond the uint8 range 
     */
    retVal = MIN(queue_delay, DRV_PKT_DELAY_TO_FW_LIMIT) >> 1;

    wlan_debug3("WMM: Pkt Delay: %d ms, %d ms sent to FW\n",
           queue_delay, retVal);

    return retVal;
}

/** 
 *  @brief Transmit the highest priority packet awaiting in the WMM Queues
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *
 *  @return        void
 */
void
wmm_process_tx(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    
    rt_base_t level;

    ENTER();

    if ((Adapter->PSState == PS_STATE_SLEEP)
        || (Adapter->PSState == PS_STATE_PRE_SLEEP)) {
        wlan_debug3( "In PS State %d"
               " - Not sending the packet\n", Adapter->PSState);
        LEAVE();

        return;
    }

	level = rt_hw_interrupt_disable();

    if (priv->wlan_dev.dnld_sent) {

	 rt_hw_interrupt_enable(level);
        LEAVE();

        return;
    }
   
   if (!list_empty((struct list_head *) &Adapter->wmm.txSkbQ)) {
            wlan_debug3( "get a packet for tx list\n");
            Adapter->CurrentTxSkb = Adapter->wmm.txSkbQ.next;
            list_del((struct list_head *) Adapter->wmm.txSkbQ.next);
        }
  
   rt_hw_interrupt_enable(level);
    if (Adapter->CurrentTxSkb) {
        wlan_process_tx(priv);
    }

    LEAVE();
}

/**
 *  @brief Private IOCTL entry to get the status of the WMM queues
 *
 *  Return the following information for each WMM AC:
 *        - WMM IE Acm Required
 *        - Firmware Flow Required 
 *        - Firmware Flow Established
 *        - Firmware Queue Enabled
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param wrq     A pointer to iwreq structure containing the
 *                 wlan_ioctl_wmm_queue_status_t struct for request
 *
 *  @return        0 if successful; IOCTL error code otherwise
 */
//int wlan_wmm_queue_status_ioctl(wlan_private * priv, struct iwreq *wrq)
//{
/*    wlan_adapter *Adapter = priv->adapter;
    wlan_ioctl_wmm_queue_status_t qstatus;
    wlan_wmm_ac_e acVal;
    WmmAcStatus_t *pACStatus;
    IEEEtypes_WmmAcParameters_t *pWmmIeAC;

    for (acVal = WMM_AC_BK; acVal <= WMM_AC_VO; acVal++) {
        pACStatus = &Adapter->wmm.acStatus[acVal];
        pWmmIeAC = &Adapter->CurBssParams.BSSDescriptor.wmmIE.AcParams[acVal];

  */      /* Acm bit */
  /*      qstatus.acStatus[acVal].wmmAcm = pWmmIeAC->AciAifsn.Acm;

  */      /* Firmware status */
  /*      qstatus.acStatus[acVal].flowRequired = pACStatus->FlowRequired;
        qstatus.acStatus[acVal].flowCreated = pACStatus->FlowCreated;
        qstatus.acStatus[acVal].disabled = pACStatus->Disabled;
    }

    if (memcpy(wrq->u.data.pointer, &qstatus, sizeof(qstatus))) {
        PRINTM(INFO, "Copy to user failed\n");
        return -EFAULT;
    }

    return WLAN_STATUS_SUCCESS;*/
//}

/**
 *  @brief Private IOCTL entry to send an ADDTS TSPEC
 *
 *  Receive a ADDTS command from the application.  The command structure
 *    contains a TSPEC and timeout in milliseconds.  The timeout is performed
 *    in the firmware after the ADDTS command frame is sent.  
 *
 *  The TSPEC is received in the API as an opaque block whose length is 
 *    calculated from the IOCTL data length.  The firmware will send the 
 *    entire data block, including the bytes after the TSPEC.  This is done
 *    to allow extra IEs to be packaged with the TSPEC in the ADDTS action
 *    frame.
 *
 *  The IOCTL structure contains two return fields: 
 *    - The firmware command result which indicates failure and timeouts
 *    - The IEEE Status code which contains the corresponding value from
 *      any ADDTS response frame received.
 *
 *  In addition, the opaque TSPEC data block passed in is replaced with the 
 *    TSPEC recieved in the ADDTS response frame.  In case of failure, the
 *    AP may modify the TSPEC on return and in the case of success, the 
 *    medium time is returned as calculated by the AP.  Along with the TSPEC,
 *    any IEs that are sent in the ADDTS response are also returned and can be
 *    parsed using the IOCTL length as an indicator of extra elements.
 *
 *  The return value to the application layer indicates a driver execution
 *    success or failure.  A successful return could still indicate a firmware
 *    failure or AP negotiation failure via the commandResult field copied
 *    back to the application.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param wrq     A pointer to iwreq structure containing the
 *                 wlan_ioctl_wmm_addts_req_t struct for this ADDTS request
 *
 *  @return        0 if successful; IOCTL error code otherwise
 */
//int wlan_wmm_addts_req_ioctl(wlan_private * priv, struct iwreq *wrq)
//{
/*    static int dialogTok = 0;
    wlan_ioctl_wmm_addts_req_t addtsIoctl;
    wlan_cmd_wmm_addts_req_t addtsCmd;
    int retcode;

    if (memcpy(&addtsIoctl,
                       wrq->u.data.pointer,
                       MIN(wrq->u.data.length, sizeof(addtsIoctl))) != 0) {
  */      /* copy_from_user failed  */
 /*       PRINTM(INFO, "TSPEC: ADDTS copy from user failed\n");
        retcode = -EFAULT;

    } else {
        memset(&addtsCmd, 0x00, sizeof(addtsCmd));
        addtsCmd.dialogToken = ++dialogTok;
        addtsCmd.timeout_ms = addtsIoctl.timeout_ms;
        addtsCmd.tspecDataLen = (wrq->u.data.length
                                 - sizeof(addtsCmd.timeout_ms)
                                 - sizeof(addtsCmd.commandResult)
                                 - sizeof(addtsCmd.ieeeStatusCode));
        memcpy(addtsCmd.tspecData,
               addtsIoctl.tspecData, addtsCmd.tspecDataLen);

        retcode = PrepareAndSendCommand(priv,
                                        HostCmd_CMD_WMM_ADDTS_REQ, 0,
                                        HostCmd_OPTION_WAITFORRSP, 0,
                                        &addtsCmd);

        wrq->u.data.length = (sizeof(addtsIoctl.timeout_ms)
                              + sizeof(addtsIoctl.commandResult)
                              + sizeof(addtsIoctl.ieeeStatusCode)
                              + addtsCmd.tspecDataLen);

        addtsIoctl.commandResult = addtsCmd.commandResult;
        addtsIoctl.ieeeStatusCode = addtsCmd.ieeeStatusCode;
        memcpy(addtsIoctl.tspecData,
               addtsCmd.tspecData, addtsCmd.tspecDataLen);

        if (memcpy(wrq->u.data.pointer,
                         &addtsIoctl, sizeof(addtsIoctl))) {
            PRINTM(INFO, "Copy to user failed\n");
            return -EFAULT;
        }

        if (retcode) {
            return -EFAULT;
        }
    }

    return retcode;*/
//}

/**
 *  @brief Private IOCTL entry to send a DELTS TSPEC
 *
 *  Receive a DELTS command from the application.  The command structure
 *    contains a TSPEC and reason code along with space for a command result
 *    to be returned.  The information is packaged is sent to the wlan_cmd.c
 *    firmware command prep and send routines for execution in the firmware.
 *
 *  The reason code is not used for WMM implementations but is indicated in
 *    the 802.11e specification.
 *
 *  The return value to the application layer indicates a driver execution
 *    success or failure.  A successful return could still indicate a firmware
 *    failure via the commandResult field copied back to the application.
 *  
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param wrq     A pointer to iwreq structure containing the
 *                 wlan_ioctl_wmm_delts_req_t struct for this DELTS request
 *
 *  @return        0 if successful; IOCTL error code otherwise
 */
//int wlan_wmm_delts_req_ioctl(wlan_private * priv, struct iwreq *wrq)
//{
/*    wlan_ioctl_wmm_delts_req_t deltsIoctl;
    wlan_cmd_wmm_delts_req_t deltsCmd;
    int retcode;

    if (copy_from_user(&deltsIoctl,
                       wrq->u.data.pointer,
                       MIN(wrq->u.data.length, sizeof(deltsIoctl))) != 0) {
 */       /* copy_from_user failed  */
 /*       PRINTM(INFO, "TSPEC: DELTS copy from user failed\n");
        retcode = -EFAULT;

    } else {
        memset(&deltsCmd, 0x00, sizeof(deltsCmd));

 */       /* Dialog token unused for WMM implementations */
  /*      deltsCmd.dialogToken = 0;

        deltsCmd.ieeeReasonCode = deltsIoctl.ieeeReasonCode;

  */      /* Calculate the length of the TSPEC and any other IEs */
  /*      deltsCmd.tspecDataLen = (wrq->u.data.length
                                 - sizeof(deltsCmd.commandResult)
                                 - sizeof(deltsCmd.ieeeReasonCode));
        memcpy(deltsCmd.tspecData,
               deltsIoctl.tspecData, deltsCmd.tspecDataLen);

  */      /* Send the DELTS request to firmware, wait for a response */
  /*      retcode = PrepareAndSendCommand(priv,
                                        HostCmd_CMD_WMM_DELTS_REQ, 0,
                                        HostCmd_OPTION_WAITFORRSP, 0,
                                        &deltsCmd);

  
  */      /* Return the firmware command result back to the application layer */
  /*      deltsIoctl.commandResult = deltsCmd.commandResult;

        if (copy_to_user(wrq->u.data.pointer,
                         &deltsCmd,
                         MIN(wrq->u.data.length, sizeof(deltsIoctl)))) {
            PRINTM(INFO, "Copy to user failed\n");
            return -EFAULT;
        }

        if (retcode) {
            retcode = -EFAULT;
        }
    }

    return retcode;
*/
//}

/**
 *  @brief Process the ADDTS_REQ command response from firmware
 *
 *  Return the ADDTS firmware response to the calling thread that sent 
 *    the command.  The result is then relayed back the app layer.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param resp    Pointer to the command response buffer including the 
 *                 command result and any returned ADDTS response TSPEC
 *                 elements 
 * 
 *  @return WLAN_STATUS_SUCCESS
 *
 *  @sa wlan_wmm_addts_req_ioctl
 */
int wlan_cmdresp_wmm_addts_req(wlan_private * priv,
                           const HostCmd_DS_COMMAND * resp)
{
    wlan_cmd_wmm_addts_req_t *pAddTsCmd;
    const HostCmd_DS_WMM_ADDTS_REQ *pCmdResp;

    /* Cast the NULL pointer of the buffer the IOCTL sent in the command req */
    pAddTsCmd = (wlan_cmd_wmm_addts_req_t *) priv->adapter->CurCmd->pdata_buf;

    /* Convenience variable for the ADDTS response from the firmware */
    pCmdResp = &resp->params.addTsReq;

    /* Assign return data */
    pAddTsCmd->dialogToken = pCmdResp->dialogToken;
    pAddTsCmd->commandResult = pCmdResp->commandResult;
    pAddTsCmd->ieeeStatusCode = pCmdResp->ieeeStatusCode;

    /* The tspecData field is potentially variable in size due to extra IEs
     *   that may have been in the ADDTS response action frame.  Calculate
     *   the data length from the firmware command response.
     */
    pAddTsCmd->tspecDataLen = (resp->Size - sizeof(pCmdResp->commandResult)
                               - sizeof(pCmdResp->timeout_ms)
                               - sizeof(pCmdResp->dialogToken)
                               - sizeof(pCmdResp->ieeeStatusCode)
                               - S_DS_GEN);

    /* Copy back the TSPEC data including any extra IEs after the TSPEC */
    memcpy(pAddTsCmd->tspecData,
           pCmdResp->tspecData,
           MAX(pAddTsCmd->tspecDataLen, sizeof(pAddTsCmd->tspecData)
               + sizeof(pAddTsCmd->addtsExtraIEBuf)));

    wlan_debug3("TSPEC: ADDTS ret = %d,%d sz=%d\n",
           pAddTsCmd->commandResult, pAddTsCmd->ieeeStatusCode,
           pAddTsCmd->tspecDataLen);


    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Process the DELTS_REQ command response from firmware
 *
 *  Return the DELTS firmware response to the calling thread that sent 
 *    the command.  The result is then relayed back the app layer.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param resp    Pointer to the command response buffer with the command
 *                 result.  No other response information is passed back 
 *                 to the driver.
 * 
 *  @return WLAN_STATUS_SUCCESS
 *
 *  @sa wlan_wmm_delts_req_ioctl
 */
int wlan_cmdresp_wmm_delts_req(wlan_private * priv,
                           const HostCmd_DS_COMMAND * resp)
{
    wlan_cmd_wmm_delts_req_t *pDelTsCmd;

    /* Cast the NULL pointer of the buffer the IOCTL sent in the command req */
    pDelTsCmd = (wlan_cmd_wmm_delts_req_t *) priv->adapter->CurCmd->pdata_buf;

    pDelTsCmd->commandResult =
        wlan_le16_to_cpu(resp->params.delTsReq.commandResult);

    wlan_debug3("TSPEC: DELTS result = %d\n", pDelTsCmd->commandResult);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Implement cmd HostCmd_DS_WMM_ADDTS_REQ
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param cmd     Pointer to CMD buffer 
 *  @param InfoBuf Pointer to cmd data
 *
 *  @return        WLAN_STATUS_SUCCESS
 *
 *  @sa wlan_wmm_addts_req_ioctl
 */
int wlan_cmd_wmm_addts_req(wlan_private * priv,
                       HostCmd_DS_COMMAND * cmd, void *InfoBuf)
{
    wlan_cmd_wmm_addts_req_t *pAddTsCmd;
    int tspecCopySize;

    pAddTsCmd = (wlan_cmd_wmm_addts_req_t *) InfoBuf;

    cmd->params.addTsReq.timeout_ms = pAddTsCmd->timeout_ms;
    cmd->params.addTsReq.dialogToken = pAddTsCmd->dialogToken;

    tspecCopySize = MIN(pAddTsCmd->tspecDataLen,
                        sizeof(cmd->params.addTsReq.tspecData));
    memcpy(&cmd->params.addTsReq.tspecData,
           pAddTsCmd->tspecData, tspecCopySize);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_WMM_ADDTS_REQ);
    cmd->Size = wlan_cpu_to_le16(sizeof(cmd->params.addTsReq.dialogToken)
                                 + sizeof(cmd->params.addTsReq.timeout_ms)
                                 + sizeof(cmd->params.addTsReq.commandResult)
                                 + sizeof(cmd->params.addTsReq.ieeeStatusCode)
                                 + tspecCopySize + S_DS_GEN);

    cmd->params.addTsReq.timeout_ms
        = wlan_cpu_to_le32(cmd->params.addTsReq.timeout_ms);

    wlan_debug3("WMM: ADDTS Cmd: Data Len = %d\n", pAddTsCmd->tspecDataLen);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Implement cmd HostCmd_DS_WMM_DELTS_REQ
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *  @param cmd      Pointer to CMD buffer 
 *  @param InfoBuf  Void pointer cast of a wlan_cmd_wmm_delts_req_t struct
 *
 *  @return         WLAN_STATUS_SUCCESS
 *
 *  @sa wlan_wmm_delts_req_ioctl
 */
int wlan_cmd_wmm_delts_req(wlan_private * priv,
                       HostCmd_DS_COMMAND * cmd, void *InfoBuf)
{
    wlan_cmd_wmm_delts_req_t *pDelTsCmd;
    int tspecCopySize;

    pDelTsCmd = (wlan_cmd_wmm_delts_req_t *) InfoBuf;

    cmd->params.delTsReq.dialogToken = pDelTsCmd->dialogToken;
    cmd->params.delTsReq.ieeeReasonCode = pDelTsCmd->ieeeReasonCode;

    tspecCopySize = MIN(pDelTsCmd->tspecDataLen,
                        sizeof(cmd->params.delTsReq.tspecData));
    memcpy(&cmd->params.delTsReq.tspecData,
           pDelTsCmd->tspecData, tspecCopySize);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_WMM_DELTS_REQ);
    cmd->Size = wlan_cpu_to_le16(sizeof(cmd->params.delTsReq.dialogToken)
                                 + sizeof(cmd->params.delTsReq.commandResult)
                                 + sizeof(cmd->params.delTsReq.ieeeReasonCode)
                                 + tspecCopySize + S_DS_GEN);

    wlan_debug3( "WMM: DELTS Cmd prepared\n");

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Prepare the firmware command buffer for the WMM_QUEUE_CONFIG command
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *  @param cmd      Pointer to CMD buffer 
 *  @param InfoBuf  Void pointer cast of a wlan_cmd_wmm_queue_config_t struct
 *
 *  @return         WLAN_STATUS_SUCCESS
 */
int wlan_cmd_wmm_queue_config(wlan_private * priv,
                          HostCmd_DS_COMMAND * cmd, void *InfoBuf)
{
    wlan_cmd_wmm_queue_config_t *pQConfigCmd;
    int tlvCopySize;

    pQConfigCmd = (wlan_cmd_wmm_queue_config_t *) InfoBuf;

    cmd->params.queueConfig.action = pQConfigCmd->action;
    cmd->params.queueConfig.accessCategory = pQConfigCmd->accessCategory;
    cmd->params.queueConfig.msduLifetimeExpiry
        = wlan_cpu_to_le16(pQConfigCmd->msduLifetimeExpiry);

    tlvCopySize = MIN(pQConfigCmd->tlvBufLen,
                      sizeof(cmd->params.queueConfig.tlvBuffer));
    memcpy(&cmd->params.queueConfig.tlvBuffer,
           pQConfigCmd->tlvBuffer, tlvCopySize);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_WMM_QUEUE_CONFIG);
    cmd->Size = wlan_cpu_to_le16(sizeof(cmd->params.queueConfig.action)
                                 +
                                 sizeof(cmd->params.queueConfig.
                                        accessCategory)
                                 +
                                 sizeof(cmd->params.queueConfig.
                                        msduLifetimeExpiry)
                                 + tlvCopySize + S_DS_GEN);

    wlan_debug3("WMM: QUEUE CONFIG Cmd prepared\n");

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Process the WMM_QUEUE_CONFIG command response from firmware
 *
 *  Return the firmware command response to the blocked IOCTL caller function.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param resp    Pointer to the command response buffer with:
 *                      - action code
 *                      - access category
 *                      - collected statistics if requested 
 *
 *  @return WLAN_STATUS_SUCCESS
 *
 *  @sa wlan_wmm_queue_config_ioctl
 */
int wlan_cmdresp_wmm_queue_config(wlan_private * priv,
                              const HostCmd_DS_COMMAND * resp)
{
    wlan_cmd_wmm_queue_config_t *pQConfigCmd;
    const HostCmd_DS_WMM_QUEUE_CONFIG *pCmdResp;

    pQConfigCmd =
        (wlan_cmd_wmm_queue_config_t *) (priv->adapter->CurCmd->pdata_buf);
    pCmdResp = &resp->params.queueConfig;

    pQConfigCmd->action = pCmdResp->action;
    pQConfigCmd->accessCategory = pCmdResp->accessCategory;
    pQConfigCmd->msduLifetimeExpiry
        = wlan_le16_to_cpu(pCmdResp->msduLifetimeExpiry);

    pQConfigCmd->tlvBufLen = (resp->Size - sizeof(pCmdResp->action)
                              - sizeof(pCmdResp->accessCategory)
                              - sizeof(pCmdResp->msduLifetimeExpiry)
                              - S_DS_GEN);

    memcpy(pQConfigCmd->tlvBuffer,
           pCmdResp->tlvBuffer, pQConfigCmd->tlvBufLen);

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Private IOCTL entry to get/set a specified AC Queue's parameters
 *
 *  Receive a AC Queue configuration command which is used to get, set, or 
 *    default the parameters associated with a specific WMM AC Queue.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param wrq     A pointer to iwreq structure containing the
 *                 wlan_ioctl_wmm_queue_config_t struct
 *
 *  @return        0 if successful; IOCTL error code otherwise
 */
//int wlan_wmm_queue_config_ioctl(wlan_private * priv, struct iwreq *wrq)
//{
/*    wlan_ioctl_wmm_queue_config_t queueConfigIoctl;
    wlan_cmd_wmm_queue_config_t queueConfigCmd;
    int retcode;

    PRINTM(INFO, "WMM: Queue Config IOCTL Enter\n");

    if (copy_from_user(&queueConfigIoctl,
                       wrq->u.data.pointer,
                       MIN(wrq->u.data.length,
                           sizeof(queueConfigIoctl))) != 0) {
 */       /* copy_from_user failed  */
 /*       PRINTM(INFO, "WMM: Queue Config: copy from user failed\n");
        retcode = -EFAULT;

    } else {
        memset(&queueConfigCmd, 0x00, sizeof(queueConfigCmd));

        queueConfigCmd.action = queueConfigIoctl.action;
        queueConfigCmd.accessCategory = queueConfigIoctl.accessCategory;
        queueConfigCmd.msduLifetimeExpiry
            = queueConfigIoctl.msduLifetimeExpiry;

  */      /* Create a rates TLV from the supportedRates[] ioctl field */
 /*       queueConfigCmd.tlvBufLen = 0;

        retcode = PrepareAndSendCommand(priv,
                                        HostCmd_CMD_WMM_QUEUE_CONFIG, 0,
                                        HostCmd_OPTION_WAITFORRSP, 0,
                                        &queueConfigCmd);
        if (retcode) {
            retcode = -EFAULT;
        } else {
            memset(&queueConfigIoctl, 0x00, sizeof(queueConfigIoctl));

            queueConfigIoctl.action = queueConfigCmd.action;
            queueConfigIoctl.accessCategory = queueConfigCmd.accessCategory;
            queueConfigIoctl.msduLifetimeExpiry
                = queueConfigCmd.msduLifetimeExpiry;

            wrq->u.data.length = sizeof(queueConfigIoctl);

            if (copy_to_user(wrq->u.data.pointer,
                             &queueConfigIoctl, sizeof(queueConfigIoctl))) {
                PRINTM(INFO, "Copy to user failed\n");
                retcode = -EFAULT;
            }
        }
    }

    return retcode;*/
//}

/** 
 *  @brief Prepare the firmware command buffer for the WMM_QUEUE_STATS command
 *
 *  @param priv     Pointer to the wlan_private driver data struct
 *  @param cmd      pointer to CMD buffer 
 *  @param InfoBuf  void pointer cast of a HostCmd_CMD_WMM_QUEUE_STATS struct
 *
 *  @return         WLAN_STATUS_SUCCESS
 */
int wlan_cmd_wmm_queue_stats(wlan_private * priv,
                         HostCmd_DS_COMMAND * cmd, void *InfoBuf)
{
    memcpy(&cmd->params.queueStats, InfoBuf, sizeof(cmd->params.queueStats));

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_WMM_QUEUE_STATS);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_WMM_QUEUE_STATS)
                                 + S_DS_GEN);

    wlan_debug3("WMM: QUEUE STATS Cmd prepared\n");

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Process the WMM_QUEUE_STATS command response from firmware
 *
 *  Return the firmware command response to the blocked IOCTL caller function.
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param resp    Pointer to the command response buffer with:
 *                      - action code
 *                      - access category
 *                      - collected statistics if requested 
 *
 *  @return WLAN_STATUS_SUCCESS
 *
 *  @sa wlan_wmm_queue_stats_ioctl
 */
int wlan_cmdresp_wmm_queue_stats(wlan_private * priv,const HostCmd_DS_COMMAND * resp)
{
    HostCmd_DS_WMM_QUEUE_STATS *pQueueStats =
        (HostCmd_DS_WMM_QUEUE_STATS *) priv->adapter->CurCmd->pdata_buf;

    memcpy(pQueueStats, &resp->params.queueStats, (resp->Size - S_DS_GEN));

    pQueueStats->pktCount = wlan_le16_to_cpu(pQueueStats->pktCount);
    pQueueStats->pktLoss = wlan_le16_to_cpu(pQueueStats->pktLoss);
    pQueueStats->avgQueueDelay = wlan_le32_to_cpu(pQueueStats->avgQueueDelay);
    pQueueStats->avgTxDelay = wlan_le32_to_cpu(pQueueStats->avgTxDelay);
    pQueueStats->usedTime = wlan_le32_to_cpu(pQueueStats->usedTime);

    wlan_debug3("WMM: Queue Stats response: %d\n", resp->Size - S_DS_GEN);

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Private IOCTL entry to get and start/stop queue stats on a WMM AC
 *
 *  Receive a AC Queue statistics command from the application for a specific
 *    WMM AC.  The command can:
 *         - Turn stats on
 *         - Turn stats off
 *         - Collect and clear the stats 
 *
 *  @param priv    Pointer to the wlan_private driver data struct
 *  @param wrq     A pointer to iwreq structure containing the
 *                 wlan_ioctl_wmm_queue_stats_t struct
 *
 *  @return        0 if successful; IOCTL error code otherwise
 */
//int wlan_wmm_queue_stats_ioctl(wlan_private * priv, struct iwreq *wrq)
//{
 /*   wlan_ioctl_wmm_queue_stats_t queueStatsIoctl;
    HostCmd_DS_WMM_QUEUE_STATS queueStatsCmd;
    int retcode;

    if (copy_from_user(&queueStatsIoctl,
                       wrq->u.data.pointer,
                       MIN(wrq->u.data.length,
                           sizeof(queueStatsIoctl))) != 0) {
 */       /* copy_from_user failed  */
 /*       PRINTM(INFO, "WMM: Queue Stats: copy from user failed\n");
        retcode = -EFAULT;

    } else {
        memcpy(&queueStatsCmd, &queueStatsIoctl, sizeof(queueStatsCmd));

        PRINTM(INFO, "WMM: QUEUE STATS Ioctl: %d, %d\n",
               queueStatsCmd.action, queueStatsCmd.accessCategory);

        retcode = PrepareAndSendCommand(priv,
                                        HostCmd_CMD_WMM_QUEUE_STATS, 0,
                                        HostCmd_OPTION_WAITFORRSP, 0,
                                        &queueStatsCmd);
        if (retcode) {
            retcode = -EFAULT;
        } else {
            if (copy_to_user(wrq->u.data.pointer,
                             &queueStatsCmd,
                             MIN(wrq->u.data.length,
                                 sizeof(queueStatsCmd)))) {
                PRINTM(INFO, "Copy to user failed\n");
                retcode = -EFAULT;
            }
        }
    }

    if (retcode != WLAN_STATUS_SUCCESS) {
        PRINTM(INFO, "WMM: QUEUE STATS Ioctl FAILED: %d, %d\n",
               queueStatsIoctl.action, queueStatsIoctl.accessCategory);
    }

    return retcode;
*/
//}
