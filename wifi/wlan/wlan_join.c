/** @file wlan_join.c
 *
 *  @brief Functions implementing wlan infrastructure and adhoc join routines
 *
 *  IOCTL handlers as well as command preperation and response routines
 *   for sending adhoc start, adhoc join, and association commands
 *   to the firmware.
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 *
 *  @sa wlan_join.h
 */
/*************************************************************
Change Log:
    01/11/06: Initial revision. Match new scan code, relocate related functions
    01/19/06: Fix failure to save adhoc ssid as current after adhoc start
    03/16/06: Add a semaphore to protect reassociation thread

************************************************************/

#include    "include.h"
#include "rt_wlan_dev.h"
#define EBUSY  1000
#define ENOTSUPP 1001
BOOLEAN
Is_Command_Allowed(wlan_private * priv)
{
    BOOLEAN ret = TRUE;

    {
        if ((priv->adapter->IsDeepSleep == TRUE)) {
            wlan_debug3("IOCTLS called when station is in DeepSleep\n");
            ret = FALSE;
        }
    }

    return ret;
}
/**
 *  @brief This function finds out the common rates between rate1 and rate2.
 *
 * It will fill common rates in rate1 as output if found.
 *
 * NOTE: Setting the MSB of the basic rates need to be taken
 *   care, either before or after calling this function
 *
 *  @param Adapter     A pointer to wlan_adapter structure
 *  @param rate1       the buffer which keeps input and output
 *  @param rate1_size  the size of rate1 buffer
 *  @param rate2       the buffer which keeps rate2
 *  @param rate2_size  the size of rate2 buffer.
 *
 *  @return            WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
get_common_rates(wlan_adapter * Adapter, u8 * rate1,
                 int rate1_size, u8 * rate2, int rate2_size)
{
    u8 *ptr = rate1;
    int ret = WLAN_STATUS_SUCCESS;
    u8 *tmp = NULL;
    int i, j;

    if (!(tmp = (u8*)malloc(rate1_size))) {
        wlan_debug3("Allocate buffer for common rates failed\n");
        return -ENOMEM;
    }

    memcpy(tmp, rate1, rate1_size);
    memset(rate1, 0, rate1_size);

    for (i = 0; rate2[i] && i < rate2_size; i++) {
        for (j = 0; tmp[j] && j < rate1_size; j++) {
            /* Check common rate, excluding the bit for basic rate */
            if ((rate2[i] & 0x7F) == (tmp[j] & 0x7F)) {
                *rate1++ = tmp[j];
                break;
            }
        }
    }
    if (!Adapter->Is_DataRate_Auto) {
        while (*ptr) {
            if ((*ptr & 0x7f) == Adapter->DataRate) {
                ret = WLAN_STATUS_SUCCESS;
                goto done;
            }
            ptr++;
        }
        wlan_debug3("Previously set fixed data rate %#x isn't "
               "compatible with the network.\n", Adapter->DataRate);

        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    ret = WLAN_STATUS_SUCCESS;
  done:
    free(tmp);
    return ret;
}

/**
 *  @brief Create the intersection of the rates supported by a target BSS and
 *         our Adapter settings for use in an assoc/join command.
 *
 *  @param Adapter       A pointer to wlan_adapter structure
 *  @param pBSSDesc      BSS Descriptor whose rates are used in the setup
 *  @param pOutRates     Output: Octet array of rates common between the BSS
 *                       and the Adapter supported rates settings
 *  @param pOutRatesSize Output: Number of rates/octets set in pOutRates
 *
 *  @return              WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 *
 */
static int
setup_rates_from_bssdesc(wlan_adapter * Adapter,
                         BSSDescriptor_t * pBSSDesc,
                         u8 * pOutRates, int *pOutRatesSize)
{
    u8 *card_rates;
    int card_rates_size;

    ENTER();

    memcpy(pOutRates, pBSSDesc->SupportedRates, WLAN_SUPPORTED_RATES);

    card_rates = SupportedRates;
    card_rates_size = sizeof(SupportedRates);

    if (get_common_rates(Adapter, pOutRates, WLAN_SUPPORTED_RATES,
                         card_rates, card_rates_size)) {
        *pOutRatesSize = 0;
        wlan_debug2( "get_common_rates failed\n");
        LEAVE();
        return WLAN_STATUS_FAILURE;
    }

    *pOutRatesSize = MIN(strlen(pOutRates), WLAN_SUPPORTED_RATES);

    LEAVE();

    return WLAN_STATUS_SUCCESS;
}
/**
 *  @brief Connect to the AP or Ad-hoc Network with specific bssid
 *
 * NOTE: Scan should be issued by application before this function is called
 *
 *  @param dev          A pointer to net_device structure
 *  @param info         A pointer to iw_request_info structure
 *  @param awrq         A pointer to iw_param structure
 *  @param extra        A pointer to extra data buf
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
int wlan_set_wap (struct rt_wlan_dev *dev, char * dstbssid,int len)
{
 
    wlan_private *priv = dev->priv;
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    const u8 bcast[ETH_ALEN] = { 255, 255, 255, 255, 255, 255 };
    u8 reqBSSID[ETH_ALEN];
    int i;

    ENTER();
    if(len!=ETH_ALEN)
    return -WLANEPARAMETER;
    if (!Is_Command_Allowed(priv)) {
        wlan_debug1( "%s: not allowed\n", __FUNCTION__);
        return -EBUSY;
    }

    /* Clear any past association response stored for application retrieval */
    Adapter->assocRspSize = 0;

    wlan_debug3("ASSOC: WAP: sa_data: %02x:%02x:%02x:%02x:%02x:%02x\n",
           (u8) dstbssid[0], (u8) dstbssid[1],
           (u8) dstbssid[2], (u8) dstbssid[3],
           (u8) dstbssid[4], (u8) dstbssid[5]);

#ifdef REASSOCIATION
    // cancel re-association timer if there's one
    if (Adapter->ReassocTimerIsSet == TRUE) {
        CancelTimer(&Adapter->MrvDrvTimer);
        Adapter->ReassocTimerIsSet = FALSE;
    }
#endif /* REASSOCIATION */

    if (!memcmp(bcast, dstbssid, ETH_ALEN)) {
        i = FindBestSSIDInList(Adapter);
    } else {
        memcpy(reqBSSID, dstbssid, ETH_ALEN);

        wlan_debug3( "ASSOC: WAP: Bssid = %02x:%02x:%02x:%02x:%02x:%02x\n",
              dstbssid[0], dstbssid[1], dstbssid[2],
               dstbssid[3], dstbssid[4], dstbssid[5]);

        /* Search for index position in list for requested MAC */
        i = FindBSSIDInList(Adapter, reqBSSID, Adapter->InfrastructureMode);
    }

    if (i < 0) {
        wlan_debug1( "ASSOC: WAP: MAC address not found in BSSID List\n");
        return -ENETUNREACH;
    }

    if (Adapter->InfrastructureMode == Wlan802_11Infrastructure) {

        ret = wlan_associate(priv, &Adapter->ScanTable[i]);

        if (ret) {
            LEAVE();
            return ret;
        }
    } 

    /* Check to see if we successfully connected */
    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        ret = WLAN_STATUS_SUCCESS;
    } else {
        ret = -ENETDOWN;
    }

    LEAVE();
    return ret;
}

/**
 *  @brief Associated to a specific BSS discovered in a scan
 *
 *  @param priv      A pointer to wlan_private structure
 *  @param pBSSDesc  Pointer to the BSS descriptor to associate with.
 *
 *  @return          WLAN_STATUS_SUCCESS-success, otherwise fail
 */
int
wlan_associate(wlan_private * priv, BSSDescriptor_t * pBSSDesc)
{
    wlan_adapter *Adapter = priv->adapter;
    int enableData = TRUE;
//    union iwreq_data wrqu;
    int ret;
    IEEEtypes_AssocRsp_t *pAssocRsp;
    u8 currentBSSID[MRVDRV_ETH_ADDR_LEN];
    int reassocAttempt = FALSE;

    ENTER();

    /* Return error if the Adapter or table entry is not marked as infra */
    if ((Adapter->InfrastructureMode != Wlan802_11Infrastructure)
        || (pBSSDesc->InfrastructureMode != Wlan802_11Infrastructure)) {
        LEAVE();
        return -EINVAL;
    }

    memcpy(&currentBSSID,
           &Adapter->CurBssParams.BSSDescriptor.MacAddress,
           sizeof(currentBSSID));

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        reassocAttempt = TRUE;
        wlan_debug3( "Attempting reassociation, stopping wmm queues\n");
        wmm_stop_queue(priv);
    }

    /* Clear any past association response stored for application retrieval */
    Adapter->assocRspSize = 0;

    ret = PrepareAndSendCommand(priv, HostCmd_CMD_802_11_ASSOCIATE,
                                0, HostCmd_OPTION_WAITFORRSP, 0, pBSSDesc);

    if (Adapter->wmm.enabled) {
        /* Don't re-enable carrier until we get the WMM_GET_STATUS event */
        enableData = FALSE;
    } else {
        /* Since WMM is not enabled, setup the queues with the defaults */
        wmm_setup_queues(priv);
    }

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {

        if (reassocAttempt
            && (memcmp(&currentBSSID,
                       &Adapter->CurBssParams.BSSDescriptor.MacAddress,
                       sizeof(currentBSSID)) == 0)) {

            /* Reassociation attempt failed, still associated to old AP,
             **   no need to wait for WMM notification to restart data
             */
            enableData = TRUE;
        }
        if (enableData) {
            wlan_debug2( "Post association, re-enabling data flow\n");
            wmm_start_queue(priv);

        }
    } else {
        wlan_debug2( "Post association, stopping data flow\n");

    }

 //   memcpy(wrqu.ap_addr.sa_data,
 //          &Adapter->CurBssParams.BSSDescriptor.MacAddress, ETH_ALEN);
 //   wrqu.ap_addr.sa_family = ARPHRD_ETHER;
 //   wireless_send_event(priv->wlan_dev.netdev, SIOCGIWAP, &wrqu, NULL);

    pAssocRsp = (IEEEtypes_AssocRsp_t *) Adapter->assocRspBuffer;

    if (ret || pAssocRsp->StatusCode) {
        ret = -ENETUNREACH;
    }

    LEAVE();
    return ret;
}

/**
 *  @brief Associated to a specific indexed entry in the ScanTable
 *
 *  @param priv      A pointer to wlan_private structure
 *  @param tableIdx  Index into the ScanTable to associate to, index parameter
 *                   base value is 1.  No scanning is done before the 
 *                   association attempt.
 *
 *  @return          WLAN_STATUS_SUCCESS-success, otherwise fail
 */
int
wlan_associate_to_table_idx(wlan_private * priv, int tableIdx)
{
    wlan_adapter *Adapter = priv->adapter;
    int ret;

    ENTER();

    wlan_debug3("ASSOC: iwpriv: Index = %d, NumInScanTable = %d\n",
           tableIdx, Adapter->NumInScanTable);

    /* Check index in table, subtract 1 if within range and call association
     *   sub-function.  ScanTable[] is 0 based, parameter is 1 based to
     *   conform with IW_ENCODE_INDEX flag parameter passing in iwconfig/iwlist
     */
    if (tableIdx && (tableIdx <= Adapter->NumInScanTable)) {
        ret = wlan_associate(priv, &Adapter->ScanTable[tableIdx - 1]);
    } else {
        ret = -EINVAL;
    }
    LEAVE();

    return ret;
}

/**
 *  @brief Send Deauthentication Request
 *
 *  @param priv      A pointer to wlan_private structure
 *  @return          WLAN_STATUS_SUCCESS--success, WLAN_STATUS_FAILURE--fail
 */
int
SendDeauthentication(wlan_private * priv)
{
    return PrepareAndSendCommand(priv, HostCmd_CMD_802_11_DEAUTHENTICATE,
                                 0, HostCmd_OPTION_WAITFORRSP, 0, NULL);
}

/**
 *  @brief Append a generic IE as a passthrough TLV to a TLV buffer.
 *
 *  This function is called from the network join command prep. routine. 
 *    If the IE buffer has been setup by the application, this routine appends
 *    the buffer as a passthrough TLV type to the request.
 *
 *  @param priv     A pointer to wlan_private structure
 *  @param ppBuffer pointer to command buffer pointer
 *
 *  @return         bytes added to the buffer
 */
static int
wlan_cmd_append_generic_ie(wlan_private * priv, u8 ** ppBuffer)
{
    wlan_adapter *Adapter = priv->adapter;
    int retLen = 0;
    MrvlIEtypesHeader_t ieHeader;

    /* Null Checks */
    if (ppBuffer == 0)
        return 0;
    if (*ppBuffer == 0)
        return 0;

    /*
     * If there is a generic ie buffer setup, append it to the return
     *   parameter buffer pointer.
     */
    if (Adapter->genIeBufferLen) {
        wlan_debug3("append generic %d to %p\n", Adapter->genIeBufferLen,
               *ppBuffer);

        /* Wrap the generic IE buffer with a passthrough TLV type */
        ieHeader.Type = wlan_cpu_to_le16(TLV_TYPE_PASSTHROUGH);
        ieHeader.Len = wlan_cpu_to_le16(Adapter->genIeBufferLen);
        memcpy(*ppBuffer, &ieHeader, sizeof(ieHeader));

        /* Increment the return size and the return buffer pointer param */
        *ppBuffer += sizeof(ieHeader);
        retLen += sizeof(ieHeader);

        /* Copy the generic IE buffer to the output buffer, advance pointer */
        memcpy(*ppBuffer, Adapter->genIeBuffer, Adapter->genIeBufferLen);

        /* Increment the return size and the return buffer pointer param */
        *ppBuffer += Adapter->genIeBufferLen;
        retLen += Adapter->genIeBufferLen;

        /* Reset the generic IE buffer */
        Adapter->genIeBufferLen = 0;
    }

    /* return the length appended to the buffer */
    return retLen;
}

/**
 *  @brief Append any application provided Marvell TLVs to a TLV buffer.
 *
 *  This function is called from the network join command prep. routine. 
 *    If the Marvell TLV buffer has been setup by the application, this routine
 *    appends the buffer to the request.
 *
 *  @param priv     A pointer to wlan_private structure
 *  @param ppBuffer pointer to command buffer pointer
 *
 *  @return         bytes added to the buffer
 */
static int
wlan_cmd_append_marvell_tlv(wlan_private * priv, u8 ** ppBuffer)
{
    wlan_adapter *Adapter = priv->adapter;
    int retLen = 0;

    /* Null Checks */
    if (ppBuffer == 0)
        return 0;
    if (*ppBuffer == 0)
        return 0;

    /*
     * If there is a Marvell TLV buffer setup, append it to the return
     *   parameter buffer pointer.
     */
    if (Adapter->mrvlAssocTlvBufferLen) {
        wlan_debug3("append tlv %d to %p\n",
               Adapter->mrvlAssocTlvBufferLen, *ppBuffer);

        /* Copy the TLV buffer to the output buffer, advance pointer */
        memcpy(*ppBuffer,
               Adapter->mrvlAssocTlvBuffer, Adapter->mrvlAssocTlvBufferLen);

        /* Increment the return size and the return buffer pointer param */
        *ppBuffer += Adapter->mrvlAssocTlvBufferLen;
        retLen += Adapter->mrvlAssocTlvBufferLen;

        /* Reset the Marvell TLV buffer */
        Adapter->mrvlAssocTlvBufferLen = 0;
    }

    /* return the length appended to the buffer */
    return retLen;
}

/**
 *  @brief Append TSF tracking info from the scan table for the target AP
 *
 *  This function is called from the network join command prep. routine. 
 *    The TSF table TSF sent to the firmware contians two TSF values:
 *      - the TSF of the target AP from its previous beacon/probe response
 *      - the TSF timestamp of our local MAC at the time we observed the
 *        beacon/probe response.
 *
 *    The firmware uses the timestamp values to set an initial TSF value
 *      in the MAC for the new association after a reassociation attempt.
 *
 *  @param priv     A pointer to wlan_private structure
 *  @param ppBuffer A pointer to command buffer pointer
 *  @param pBSSDesc A pointer to the BSS Descriptor from the scan table of
 *                  the AP we are trying to join
 *
 *  @return         bytes added to the buffer
 */
static int
wlan_cmd_append_tsf_tlv(wlan_private * priv, u8 ** ppBuffer,
                        BSSDescriptor_t * pBSSDesc)
{
    MrvlIEtypes_TsfTimestamp_t tsfTlv;
    u64 tsfVal;

    /* Null Checks */
    if (ppBuffer == 0)
        return 0;
    if (*ppBuffer == 0)
        return 0;

    tsfTlv.Header.Type = wlan_cpu_to_le16(TLV_TYPE_TSFTIMESTAMP);
    tsfTlv.Header.Len = wlan_cpu_to_le16(2 * sizeof(tsfVal));

    memcpy(*ppBuffer, &tsfTlv, sizeof(tsfTlv.Header));
    *ppBuffer += sizeof(tsfTlv.Header);

    /* TSF timestamp from the firmware TSF when the bcn/prb rsp was received */
    tsfVal = wlan_cpu_to_le64(pBSSDesc->networkTSF);
    memcpy(*ppBuffer, &tsfVal, sizeof(tsfVal));
    *ppBuffer += sizeof(tsfVal);

    memcpy(&tsfVal, pBSSDesc->TimeStamp, sizeof(tsfVal));

    wlan_debug3( "ASSOC: TSF offset calc: %016llx - %016llx\n",
           tsfVal, pBSSDesc->networkTSF);

    tsfVal = wlan_cpu_to_le64(tsfVal);
    memcpy(*ppBuffer, &tsfVal, sizeof(tsfVal));
    *ppBuffer += sizeof(tsfVal);

    return (sizeof(tsfTlv.Header) + (2 * sizeof(tsfVal)));
}

/**
 *  @brief This function prepares command of deauthenticate.
 *
 *  @param priv     A pointer to wlan_private structure
 *  @param cmd      A pointer to HostCmd_DS_COMMAND structure
 *  @return         WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_cmd_802_11_deauthenticate(wlan_private * priv, HostCmd_DS_COMMAND * cmd)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_DEAUTHENTICATE *dauth = &cmd->params.deauth;

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_DEAUTHENTICATE);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_DEAUTHENTICATE) + S_DS_GEN);

    /* set AP MAC address */
    memcpy(dauth->MacAddr,
           &Adapter->CurBssParams.BSSDescriptor.MacAddress, ETH_ALEN);

    /* Reason code 3 = Station is leaving */
#define REASON_CODE_STA_LEAVING 3
    dauth->ReasonCode = wlan_cpu_to_le16(REASON_CODE_STA_LEAVING);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of association.
 *
 *  @param priv      A pointer to wlan_private structure
 *  @param cmd       A pointer to HostCmd_DS_COMMAND structure
 *  @param pdata_buf Void cast of BSSDescriptor_t from the scan table to assoc
 *  @return          WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static char parabuf[256];
int
wlan_cmd_802_11_associate(wlan_private * priv,
                          HostCmd_DS_COMMAND * cmd, void *pdata_buf)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_ASSOCIATE *pAsso = &cmd->params.associate;
    int ret = WLAN_STATUS_SUCCESS;
    BSSDescriptor_t *pBSSDesc;
    WLAN_802_11_RATES rates;
    int ratesSize;
    u8 *pos;
    u16 TmpCap;
    u8* tempuf;
    u32 temlen=0;
    MrvlIEtypes_SsIdParamSet_t *pSsidTlv;
    MrvlIEtypes_PhyParamSet_t *pPhyTlv;
    MrvlIEtypes_SsParamSet_t *pSsTlv;
    MrvlIEtypes_RatesParamSet_t *pRatesTlv;
    MrvlIEtypes_AuthType_t *pAuthTlv;
    MrvlIEtypes_RsnParamSet_t *pRsnTlv;

    ENTER();
    tempuf=rt_malloc(256);
    if(tempuf==RT_NULL)
    {
	 wlan_debug1("wlan_cmd_802_11_associate fail to  get  mem\r\n ");
	 goto done;
    }
    rt_memset(tempuf,0x00,256);
    pBSSDesc = (BSSDescriptor_t *) pdata_buf;
    pos = (u8 *) pAsso;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_ASSOCIATE);

    /* Save so we know which BSS Desc to use in the response handler */
    Adapter->pAttemptedBSSDesc = pBSSDesc;
    
    rt_memcpy(pAsso->PeerStaAddr,
           pBSSDesc->MacAddress, sizeof(pAsso->PeerStaAddr));
    pos += sizeof(pAsso->PeerStaAddr);

    /* set the listen interval */
    pAsso->ListenInterval = wlan_cpu_to_le16(Adapter->ListenInterval);

    pos += sizeof(pAsso->CapInfo);
    pos += sizeof(pAsso->ListenInterval);
    pos += sizeof(pAsso->Reserved1);

    pSsidTlv=(MrvlIEtypes_SsIdParamSet_t *)tempuf;
    //pSsidTlv = (MrvlIEtypes_SsIdParamSet_t *) pos;
    pSsidTlv->Header.Type = wlan_cpu_to_le16(TLV_TYPE_SSID);
    pSsidTlv->Header.Len = pBSSDesc->Ssid.SsidLength;
    rt_memcpy(pSsidTlv->SsId, pBSSDesc->Ssid.Ssid, pSsidTlv->Header.Len);
    temlen+=sizeof(pSsidTlv->Header) + pSsidTlv->Header.Len;
    rt_memcpy(pos, (u8*)pSsidTlv, temlen);
    pos += sizeof(pSsidTlv->Header) + pSsidTlv->Header.Len;

    rt_memset(tempuf,0x00,256);
    temlen=0;
    pPhyTlv=(MrvlIEtypes_PhyParamSet_t *)tempuf;
   // pPhyTlv = (MrvlIEtypes_PhyParamSet_t *) pos;
    pPhyTlv->Header.Type = wlan_cpu_to_le16(TLV_TYPE_PHY_DS);
    pPhyTlv->Header.Len = sizeof(pPhyTlv->fh_ds.DsParamSet);
    rt_memcpy(&pPhyTlv->fh_ds.DsParamSet,
           &pBSSDesc->PhyParamSet.DsParamSet.CurrentChan,
           sizeof(pPhyTlv->fh_ds.DsParamSet));
    temlen=sizeof(pPhyTlv->Header) + pPhyTlv->Header.Len;
    rt_memcpy(pos, (u8*)pPhyTlv, temlen);
    pos += sizeof(pPhyTlv->Header) + pPhyTlv->Header.Len;
   // pPhyTlv->Header.Len = wlan_cpu_to_le16(pPhyTlv->Header.Len);

    rt_memset(tempuf,0x00,256);
    temlen=0;
    pSsTlv=(MrvlIEtypes_SsParamSet_t *)tempuf;
   // pSsTlv = (MrvlIEtypes_SsParamSet_t *) pos;
    pSsTlv->Header.Type = wlan_cpu_to_le16(TLV_TYPE_CF);
    pSsTlv->Header.Len = sizeof(pSsTlv->cf_ibss.CfParamSet);

    temlen=sizeof(pSsTlv->Header) + pSsTlv->Header.Len;
    rt_memcpy(pos, (u8*)pSsTlv, temlen);
    pos += sizeof(pSsTlv->Header) + pSsTlv->Header.Len;
   // pSsTlv->Header.Len = wlan_cpu_to_le16(pSsTlv->Header.Len);

    /* Get the common rates supported between the driver and the BSS Desc */
    if (setup_rates_from_bssdesc(Adapter, pBSSDesc, rates, &ratesSize)) {
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    /* Setup the Rates TLV in the association command */
    rt_memset(tempuf,0x00,256);
    temlen=0;
    pRatesTlv=(MrvlIEtypes_RatesParamSet_t *)tempuf;
    //pRatesTlv = (MrvlIEtypes_RatesParamSet_t *) pos;
    pRatesTlv->Header.Type = wlan_cpu_to_le16(TLV_TYPE_RATES);
    pRatesTlv->Header.Len = wlan_cpu_to_le16(ratesSize);
    rt_memcpy(pRatesTlv->Rates, rates, ratesSize);
    temlen=sizeof(pRatesTlv->Header) + ratesSize;
    rt_memcpy(pos, (u8*)pRatesTlv, temlen);
    pos += sizeof(pRatesTlv->Header) + ratesSize;
    wlan_debug3( "ASSOC_CMD: Rates size = %d\n", ratesSize);

    /* Add the Authentication type to be used for Auth frames if needed */
    rt_memset(tempuf,0x00,256);
    temlen=0;
    pAuthTlv=(MrvlIEtypes_AuthType_t *)tempuf;
   // pAuthTlv = (MrvlIEtypes_AuthType_t *) pos;
    pAuthTlv->Header.Type = wlan_cpu_to_le16(TLV_TYPE_AUTH_TYPE);
    pAuthTlv->Header.Len = sizeof(pAuthTlv->AuthType);
    pAuthTlv->AuthType = Adapter->SecInfo.AuthenticationMode;
    temlen=sizeof(pAuthTlv->Header) + pAuthTlv->Header.Len;
    rt_memcpy(pos, (u8*)pAuthTlv, temlen);
    pos += sizeof(pAuthTlv->Header) + pAuthTlv->Header.Len;
   // pAuthTlv->Header.Len = wlan_cpu_to_le16(pAuthTlv->Header.Len);
    rt_memset(tempuf,0x00,256);
    temlen=0;
    if (!Adapter->wps.SessionEnable) {
        if (Adapter->SecInfo.WPAEnabled || Adapter->SecInfo.WPA2Enabled) {
	     pRsnTlv=(MrvlIEtypes_RsnParamSet_t *)tempuf;	
           // pRsnTlv = (MrvlIEtypes_RsnParamSet_t *) pos;
            pRsnTlv->Header.Type = (u16) Adapter->Wpa_ie[0];    /* WPA_IE or WPA2_IE */
            pRsnTlv->Header.Type = pRsnTlv->Header.Type & 0x00FF;
            pRsnTlv->Header.Type = wlan_cpu_to_le16(pRsnTlv->Header.Type);
            pRsnTlv->Header.Len = (u16) Adapter->Wpa_ie[1];
            pRsnTlv->Header.Len = pRsnTlv->Header.Len & 0x00FF;
            rt_memcpy(pRsnTlv->RsnIE, &Adapter->Wpa_ie[2], pRsnTlv->Header.Len);
	     temlen+=sizeof(pRsnTlv->Header) + pRsnTlv->Header.Len;
	     rt_memcpy(pos, (u8*)pRsnTlv, temlen);
//            HEXDUMP("ASSOC_CMD: RSN IE", (u8 *) pRsnTlv,
//                    sizeof(pRsnTlv->Header) + pRsnTlv->Header.Len);
            pos += sizeof(pRsnTlv->Header) + pRsnTlv->Header.Len;
           // pRsnTlv->Header.Len = wlan_cpu_to_le16(pRsnTlv->Header.Len);
        }
    }
    rt_free(tempuf);
    wlan_wmm_process_association_req(priv, &pos, &pBSSDesc->wmmIE);

    wlan_cmd_append_generic_ie(priv, &pos);

    wlan_cmd_append_marvell_tlv(priv, &pos);

    wlan_cmd_append_tsf_tlv(priv, &pos, pBSSDesc);

    if (wlan_parse_dnld_countryinfo_11d(priv)) {
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    cmd->Size = wlan_cpu_to_le16((u16) (pos - (u8 *) pAsso) + S_DS_GEN);

    /* set the Capability info at last */
    rt_memcpy(&TmpCap, &pBSSDesc->Cap, sizeof(pAsso->CapInfo));
    TmpCap &= CAPINFO_MASK;
    wlan_debug3( "ASSOC_CMD: TmpCap=%4X CAPINFO_MASK=%4X\n",
           TmpCap, CAPINFO_MASK);
    TmpCap = wlan_cpu_to_le16(TmpCap);
    rt_memcpy(&pAsso->CapInfo, &TmpCap, sizeof(pAsso->CapInfo));

  done:
    LEAVE();
    return ret;
}

/**
 *  @brief Association firmware command response handler
 *
 *   The response buffer for the association command has the following
 *      memory layout.
 *
 *   For cases where an association response was not received (indicated
 *      by the CapInfo and AId field):
 *
 *     .------------------------------------------------------------.
 *     |  Header(4 * sizeof(u16)):  Standard command response hdr   |
 *     .------------------------------------------------------------.
 *     |  CapInfo/Error Return(u16):                                |
 *     |           0xFFFF(-1): Internal error                       |
 *     |           0xFFFE(-2): Authentication unhandled message     |
 *     |           0xFFFD(-3): Authentication refused               |
 *     .------------------------------------------------------------.
 *     |  StatusCode(u16):                                          |
 *     |        If CapInfo is -1:                                   |
 *     |           (1) Internal processing failure                  |
 *     |           (2) Timeout waiting for AP response              |
 *     |                                                            |
 *     |        If CapInfo is -2:                                   |
 *     |           An authentication frame was received but was     |
 *     |           not handled by the firmware.  IEEE Status        |
 *     |           code for the failure is returned.                |
 *     |                                                            |
 *     |        If CapInfo is -3:                                   |
 *     |           An authentication frame was received and the     |
 *     |           StatusCode is the IEEE Status reported in the    |
 *     |           response.                                        |
 *     .------------------------------------------------------------.
 *     |  AId(u16): 0xFFFF                                          |
 *     .------------------------------------------------------------.
 *
 *
 *   For cases where an association response was received, the IEEE 
 *     standard association response frame is returned:
 *
 *     .------------------------------------------------------------.
 *     |  Header(4 * sizeof(u16)):  Standard command response hdr   |
 *     .------------------------------------------------------------.
 *     |  CapInfo(u16): IEEE Capability                             |
 *     .------------------------------------------------------------.
 *     |  StatusCode(u16): IEEE Status Code                         |
 *     .------------------------------------------------------------.
 *     |  AId(u16): IEEE Association ID                             |
 *     .------------------------------------------------------------.
 *     |  IEEE IEs(variable): Any received IEs comprising the       |
 *     |                      remaining portion of a received       |
 *     |                      association response frame.           |
 *     .------------------------------------------------------------.
 *
 *  For simplistic handling, the StatusCode field can be used to determine
 *    an association success (0) or failure (non-zero).
 *
 *  @param priv    A pointer to wlan_private structure
 *  @param resp    A pointer to HostCmd_DS_COMMAND
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_ret_802_11_associate(wlan_private * priv, HostCmd_DS_COMMAND * resp)
{
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    IEEEtypes_AssocRsp_t *pAssocRsp;
    BSSDescriptor_t *pBSSDesc;
    WLAN_802_11_RATES rates;
    int ratesSize;

    ENTER();

    pAssocRsp = (IEEEtypes_AssocRsp_t *) & resp->params;

//    HEXDUMP("ASSOC_RESP:", (void *) &resp->params,
//            wlan_le16_to_cpu(resp->Size) - S_DS_GEN);

    Adapter->assocRspSize = MIN(wlan_le16_to_cpu(resp->Size) - S_DS_GEN,
                                sizeof(Adapter->assocRspBuffer));

    memcpy(Adapter->assocRspBuffer, &resp->params, Adapter->assocRspSize);

    if (pAssocRsp->StatusCode) {
        priv->adapter->dbg.num_cmd_assoc_failure++;
        wlan_debug3("ASSOC_RESP: Association Failed, status code = %d\n",
               pAssocRsp->StatusCode);

        ret = WLAN_STATUS_FAILURE;

        goto done;
    }

    /* Send a Media Connected event, according to the Spec */
    Adapter->MediaConnectStatus = WlanMediaStateConnected;

    /* Set the attempted BSSID Index to current */
    pBSSDesc = Adapter->pAttemptedBSSDesc;

    wlan_debug3("ASSOC_RESP: %s\n", pBSSDesc->Ssid.Ssid);

    /* Make a copy of current BSSID descriptor */
    memcpy(&Adapter->CurBssParams.BSSDescriptor,
           pBSSDesc, sizeof(BSSDescriptor_t));

    /* update CurBssParams */
    Adapter->CurBssParams.BSSDescriptor.Channel
        = pBSSDesc->PhyParamSet.DsParamSet.CurrentChan;

    if (setup_rates_from_bssdesc(Adapter, pBSSDesc, rates, &ratesSize)) {
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    /* Copy the infra. association rates into Current BSS state structure */
    Adapter->CurBssParams.NumOfRates = ratesSize;
    memcpy(&Adapter->CurBssParams.DataRates, rates, ratesSize);

    /* Adjust the timestamps in the scan table to be relative to the newly
     *   associated AP's TSF
     */
    wlan_scan_update_tsf_timestamps(priv, pBSSDesc);

    if (pBSSDesc->wmmIE.VendHdr.ElementId == WMM_IE) {
        Adapter->CurBssParams.wmm_enabled = TRUE;
    } else {
        Adapter->CurBssParams.wmm_enabled = FALSE;
    }

    if (Adapter->wmm.required && Adapter->CurBssParams.wmm_enabled) {
        Adapter->wmm.enabled = TRUE;
    } else {
        Adapter->wmm.enabled = FALSE;
    }

    Adapter->CurBssParams.wmm_uapsd_enabled = FALSE;

    if (Adapter->wmm.enabled == TRUE) {
        Adapter->CurBssParams.wmm_uapsd_enabled
            = pBSSDesc->wmmIE.QoSInfo.QosUAPSD;
    }

    wlan_debug3("ASSOC_RESP: CurrentPacketFilter is %x\n",
           Adapter->CurrentPacketFilter);

    if (Adapter->SecInfo.WPAEnabled || Adapter->SecInfo.WPA2Enabled)
        Adapter->IsGTK_SET = FALSE;

    Adapter->SNR[TYPE_RXPD][TYPE_AVG] = 0;
    Adapter->NF[TYPE_RXPD][TYPE_AVG] = 0;

    memset(Adapter->rawSNR, 0x00, sizeof(Adapter->rawSNR));
    memset(Adapter->rawNF, 0x00, sizeof(Adapter->rawNF));
    Adapter->nextSNRNF = 0;
    Adapter->numSNRNF = 0;

    priv->adapter->dbg.num_cmd_assoc_success++;
    wlan_debug3("ASSOC_RESP: Associated \n");

  done:
    LEAVE();
    return ret;
}

/**
 *  @brief This function handles the command response of disassociate
 *
 *  @param priv    A pointer to wlan_private structure
 *  @param resp    A pointer to HostCmd_DS_COMMAND
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_ret_802_11_disassociate(wlan_private * priv, HostCmd_DS_COMMAND * resp)
{
    ENTER();

    priv->adapter->dbg.num_cmd_deauth++;
    MacEventDisconnected(priv);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function handles the command response of ad_hoc_start and
 *  ad_hoc_join
 *
 *  @param priv    A pointer to wlan_private structure
 *  @param resp    A pointer to HostCmd_DS_COMMAND
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */


#ifdef REASSOCIATION
/** 
 *  @brief This function triggers re-association by waking up
 *  re-assoc thread.
 *  
 *  @param FunctionContext    A pointer to FunctionContext
 *  @return 	   n/a
 */
void
MrvDrvReassocTimerFunction(void *FunctionContext)
{
    wlan_private *priv = (wlan_private *) FunctionContext;
    wlan_adapter *Adapter = priv->adapter;
 
    ENTER();

    PRINTM(INFO, "MrvDrvReassocTimer fired.\n");
    Adapter->ReassocTimerIsSet = FALSE;
    if (Adapter->PSState != PS_STATE_FULL_POWER) {
        /* wait until Exit_PS command returns */
        Adapter->ReassocTimerIsSet = TRUE;
        ModTimer(&Adapter->MrvDrvTimer, MRVDRV_TIMER_1S);
        PRINTM(INFO, "MrvDrvTimerFunction(PSState=%d) waiting"
               "for Exit_PS done\n", Adapter->PSState);
        LEAVE();
        return;
    }

    PRINTM(INFO, "Waking Up the Reassoc Thread\n");

//    wake_up_interruptible(&priv->ReassocThread.waitQ);
	rt_event_send(&priv->ReassocThread.waitQ, WakeUpReassociationThread);
    LEAVE();
    return;
}
#endif /* REASSOCIATION */
