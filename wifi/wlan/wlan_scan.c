/** @file wlan_scan.c
 *
 *  @brief Functions implementing wlan scan IOCTL and firmware command APIs
 *
 *  IOCTL handlers as well as command preperation and response routines
 *   for sending scan commands to the firmware.
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
 *
 *  @sa wlan_scan.h
 */
/********************************************************
Change Log:
    01/11/06: Initial revision. New scan code, relocate related functions
    01/19/06: Update specific scan routines to discard old results for adhoc
    01/31/06: Add support for selectively enabling the FW Scan channel filter

************************************************************/

#include    "include.h"

/********************************************************
    Local Constants
********************************************************/

//! Approximate amount of data needed to pass a scan result back to iwlist
#define MAX_SCAN_CELL_SIZE  (IW_EV_ADDR_LEN             \
                             + MRVDRV_MAX_SSID_LENGTH   \
                             + IW_EV_UINT_LEN           \
                             + IW_EV_FREQ_LEN           \
                             + IW_EV_QUAL_LEN           \
                             + MRVDRV_MAX_SSID_LENGTH   \
                             + IW_EV_PARAM_LEN          \
                             + 40)      /* 40 for WPAIE */

//! Memory needed to store a max sized Channel List TLV for a firmware scan
#define CHAN_TLV_MAX_SIZE  (sizeof(MrvlIEtypesHeader_t)         \
                            + (MRVDRV_MAX_CHANNELS_PER_SCAN     \
                               * sizeof(ChanScanParamSet_t)))

//! Memory needed to store a max number/size SSID TLV for a firmware scan
#define SSID_TLV_MAX_SIZE  (1 * sizeof(MrvlIEtypes_SsIdParamSet_t))

//! WPS TLV MAX size is MAX IE size plus 2 bytes for u16 MRVL TLV extension
#define WPS_TLV_MAX_SIZE   (sizeof(IEEEtypes_VendorSpecific_t) + 2)

//! Maximum memory needed for a wlan_scan_cmd_config with all TLVs at max
#define MAX_SCAN_CFG_ALLOC (sizeof(wlan_scan_cmd_config)        \
                            + sizeof(MrvlIEtypes_NumProbes_t)   \
                            + CHAN_TLV_MAX_SIZE                 \
                            + SSID_TLV_MAX_SIZE                 \
                            + WPS_TLV_MAX_SIZE)

//! The maximum number of channels the firmware can scan per command
#define MRVDRV_MAX_CHANNELS_PER_SCAN   14

/**
 * @brief Number of channels to scan per firmware scan command issuance.
 *
 *  Number restricted to prevent hitting the limit on the amount of scan data
 *  returned in a single firmware scan command.
 */
#define MRVDRV_CHANNELS_PER_SCAN_CMD   4

//! Macro to enable/disable SSID checking before storing a scan table
#ifdef DISCARD_BAD_SSID
#define CHECK_SSID_IS_VALID(x) ssid_valid(&bssidEntry.Ssid)
#else
#define CHECK_SSID_IS_VALID(x) TRUE
#endif

/********************************************************
    Local Variables and Types
********************************************************/

/**
 * @brief Interally used to send a configured scan cmd between driver routines
 */
typedef union
{
    wlan_scan_cmd_config config;        //!< Scan configuration (variable length)
    u8 configAllocBuf[MAX_SCAN_CFG_ALLOC];      //!< Max allocated block
} wlan_scan_cmd_config_tlv;

/**
 *  @brief Check if a scanned network compatible with the driver settings
 *
 *   WEP     WPA     WPA2    ad-hoc  encrypt                      Network
 * enabled enabled  enabled   AES     mode   Privacy  WPA  WPA2  Compatible
 *    0       0        0       0      NONE      0      0    0   yes No security
 *    0       1        0       0       x        1x     1    x   yes WPA
 *    0       0        1       0       x        1x     x    1   yes WPA2
 *    0       0        0       1      NONE      1      0    0   yes Ad-hoc AES
 *
 *    1       0        0       0      NONE      1      0    0   yes Static WEP
 *    0       0        0       0     !=NONE     1      0    0   yes Dynamic WEP
 *
 *
 *  @param Adapter A pointer to wlan_adapter
 *  @param index   Index in ScanTable to check against current driver settings
 *  @param mode    Network mode: Infrastructure or IBSS
 *
 *  @return        Index in ScanTable, or error code if negative
 */
static int
IsNetworkCompatible(wlan_adapter * Adapter, int index, int mode)
{
    BSSDescriptor_t *pBSSDesc;

    ENTER();

    pBSSDesc = &Adapter->ScanTable[index];

    /* Don't check for compatibility if roaming */
    if ((Adapter->MediaConnectStatus == WlanMediaStateConnected)
        && (Adapter->InfrastructureMode == Wlan802_11Infrastructure)
        && (pBSSDesc->InfrastructureMode == Wlan802_11Infrastructure)) {
        LEAVE();
        return index;
    }

    if (Adapter->wps.SessionEnable == TRUE) {
        wlan_debug3("Return success directly in WPS period\n");
        LEAVE();
        return index;
    }

    if (pBSSDesc->InfrastructureMode == mode) {
        if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPDisabled
            && !Adapter->SecInfo.WPAEnabled
            && !Adapter->SecInfo.WPA2Enabled
            && pBSSDesc->wpaIE.VendHdr.ElementId != WPA_IE
            && pBSSDesc->rsnIE.IeeeHdr.ElementId != RSN_IE
            && !Adapter->AdhocAESEnabled
            && Adapter->SecInfo.EncryptionMode == CIPHER_NONE
            && !pBSSDesc->Privacy) {
            /* no security */
            LEAVE();
            return index;
        } else if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPEnabled
                   && !Adapter->SecInfo.WPAEnabled
                   && !Adapter->SecInfo.WPA2Enabled
                   && !Adapter->AdhocAESEnabled && pBSSDesc->Privacy) {
            /* static WEP enabled */
            LEAVE();
            return index;
        } else if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPDisabled
                   && Adapter->SecInfo.WPAEnabled
                   && !Adapter->SecInfo.WPA2Enabled
                   && (pBSSDesc->wpaIE.VendHdr.ElementId == WPA_IE)
                   && !Adapter->AdhocAESEnabled
                   /* Privacy bit may NOT be set in some APs like LinkSys WRT54G
                      && pBSSDesc->Privacy */
            ) {
            /* WPA enabled */
            wlan_debug3("IsNetworkCompatible() WPA: index=%d wpa_ie=%#x "
                   "wpa2_ie=%#x WEP=%s WPA=%s WPA2=%s EncMode=%#x "
                   "privacy=%#x\n",
                   index,
                   pBSSDesc->wpaIE.VendHdr.ElementId,
                   pBSSDesc->rsnIE.IeeeHdr.ElementId,
                   (Adapter->SecInfo.WEPStatus ==
                    Wlan802_11WEPEnabled) ? "e" : "d",
                   (Adapter->SecInfo.WPAEnabled) ? "e" : "d",
                   (Adapter->SecInfo.WPA2Enabled) ? "e" : "d",
                   Adapter->SecInfo.EncryptionMode, pBSSDesc->Privacy);
            LEAVE();
            return index;
        } else if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPDisabled
                   && !Adapter->SecInfo.WPAEnabled
                   && Adapter->SecInfo.WPA2Enabled
                   && (pBSSDesc->rsnIE.IeeeHdr.ElementId == RSN_IE)
                   && !Adapter->AdhocAESEnabled
                   /* Privacy bit may NOT be set in some APs like LinkSys WRT54G
                      && pBSSDesc->Privacy */
            ) {
            /* WPA2 enabled */
            wlan_debug3("IsNetworkCompatible() WPA2: index=%d wpa_ie=%#x "
                   "wpa2_ie=%#x WEP=%s WPA=%s WPA2=%s EncMode=%#x "
                   "privacy=%#x\n",
                   index,
                   pBSSDesc->wpaIE.VendHdr.ElementId,
                   pBSSDesc->rsnIE.IeeeHdr.ElementId,
                   (Adapter->SecInfo.WEPStatus ==
                    Wlan802_11WEPEnabled) ? "e" : "d",
                   (Adapter->SecInfo.WPAEnabled) ? "e" : "d",
                   (Adapter->SecInfo.WPA2Enabled) ? "e" : "d",
                   Adapter->SecInfo.EncryptionMode, pBSSDesc->Privacy);
            LEAVE();
            return index;
        } else if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPDisabled
                   && !Adapter->SecInfo.WPAEnabled
                   && !Adapter->SecInfo.WPA2Enabled
                   && (pBSSDesc->wpaIE.VendHdr.ElementId != WPA_IE)
                   && (pBSSDesc->rsnIE.IeeeHdr.ElementId != RSN_IE)
                   && Adapter->AdhocAESEnabled
                   && Adapter->SecInfo.EncryptionMode == CIPHER_NONE
                   && pBSSDesc->Privacy) {
            /* Ad-hoc AES enabled */
            LEAVE();
            return index;
        } else if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPDisabled
                   && !Adapter->SecInfo.WPAEnabled
                   && !Adapter->SecInfo.WPA2Enabled
                   && (pBSSDesc->wpaIE.VendHdr.ElementId != WPA_IE)
                   && (pBSSDesc->rsnIE.IeeeHdr.ElementId != RSN_IE)
                   && !Adapter->AdhocAESEnabled
                   && Adapter->SecInfo.EncryptionMode != CIPHER_NONE
                   && pBSSDesc->Privacy) {
            /* dynamic WEP enabled */
            wlan_debug3("IsNetworkCompatible() dynamic WEP: index=%d "
                   "wpa_ie=%#x wpa2_ie=%#x EncMode=%#x privacy=%#x\n",
                   index,
                   pBSSDesc->wpaIE.VendHdr.ElementId,
                   pBSSDesc->rsnIE.IeeeHdr.ElementId,
                   Adapter->SecInfo.EncryptionMode, pBSSDesc->Privacy);
            LEAVE();
            return index;
        }

        /* security doesn't match */
        wlan_debug3( "IsNetworkCompatible() FAILED: index=%d wpa_ie=%#x "
               "wpa2_ie=%#x WEP=%s WPA=%s WPA2=%s EncMode=%#x privacy=%#x\n",
               index,
               pBSSDesc->wpaIE.VendHdr.ElementId,
               pBSSDesc->rsnIE.IeeeHdr.ElementId,
               (Adapter->SecInfo.WEPStatus ==
                Wlan802_11WEPEnabled) ? "e" : "d",
               (Adapter->SecInfo.WPAEnabled) ? "e" : "d",
               (Adapter->SecInfo.WPA2Enabled) ? "e" : "d",
               Adapter->SecInfo.EncryptionMode, pBSSDesc->Privacy);
        LEAVE();
        return -ECONNREFUSED;
    }

    /* mode doesn't match */
    LEAVE();
    return -ENETUNREACH;
}

/**
 *  @brief This function validates a SSID as being able to be printed
 *
 *  @param pSsid   SSID structure to validate
 *
 *  @return        TRUE or FALSE
 */
static BOOLEAN
ssid_valid(WLAN_802_11_SSID * pSsid)
{
    int ssidIdx;

    for (ssidIdx = 0; ssidIdx < pSsid->SsidLength; ssidIdx++) {
        if (!isprint(pSsid->Ssid[ssidIdx])) {
            return FALSE;
        }
    }

    return TRUE;
}

/**
 *  @brief Post process the scan table after a new scan command has completed
 *
 *  Inspect each entry of the scan table and try to find an entry that
 *    matches our current associated/joined network from the scan.  If
 *    one is found, update the stored copy of the BSSDescriptor for our
 *    current network.
 *
 *  Debug dump the current scan table contents if compiled accordingly.
 *
 *  @param priv   A pointer to wlan_private structure
 *
 *  @return       void
 */
static void
wlan_scan_process_results(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    int i;
    int foundCurrent;

    foundCurrent = FALSE;

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        Adapter->CurBssParams.BSSDescriptor.pBeaconBuf = NULL;
        Adapter->CurBssParams.BSSDescriptor.beaconBufSize = 0;
        Adapter->CurBssParams.BSSDescriptor.beaconBufSizeMax = 0;
        i = FindSSIDInList(Adapter,
                           &Adapter->CurBssParams.BSSDescriptor.Ssid,
                           Adapter->CurBssParams.BSSDescriptor.MacAddress,
                           Adapter->InfrastructureMode);

        if (i >= 0) {
            wlan_debug2 ( "Found current ssid/bssid in list @ index #%d\n", i);
            /* Make a copy of current BSSID descriptor */
            memcpy(&Adapter->CurBssParams.BSSDescriptor,
                   &Adapter->ScanTable[i],
                   sizeof(Adapter->CurBssParams.BSSDescriptor));
        }
    }

    for (i = 0; i < Adapter->NumInScanTable; i++) {
        wlan_debug2 ( "Scan:(%02d) %02x:%02x:%02x:%02x:%02x:%02x, "
               "RSSI[%03d], SSID[%s]\n",
               i,
               Adapter->ScanTable[i].MacAddress[0],
               Adapter->ScanTable[i].MacAddress[1],
               Adapter->ScanTable[i].MacAddress[2],
               Adapter->ScanTable[i].MacAddress[3],
               Adapter->ScanTable[i].MacAddress[4],
               Adapter->ScanTable[i].MacAddress[5],
               (s32) Adapter->ScanTable[i].Rssi,
               Adapter->ScanTable[i].Ssid.Ssid);
    }
}

/**
 *  @brief Create a channel list for the driver to scan based on region info
 *
 *  Use the driver region/band information to construct a comprehensive list
 *    of channels to scan.  This routine is used for any scan that is not
 *    provided a specific channel list to scan.
 *
 *  @param priv          A pointer to wlan_private structure
 *  @param scanChanList  Output parameter: Resulting channel list to scan
 *  @param filteredScan  Flag indicating whether or not a BSSID or SSID filter
 *                       is being sent in the command to firmware.  Used to 
 *                       increase the number of channels sent in a scan
 *                       command and to disable the firmware channel scan
 *                       filter.
 *
 *  @return              void
 */
static void
wlan_scan_create_channel_list(wlan_private * priv,
                              ChanScanParamSet_t * scanChanList,
                              BOOLEAN filteredScan)
{

    wlan_adapter *Adapter = priv->adapter;
    REGION_CHANNEL *scanRegion;
    CHANNEL_FREQ_POWER *cfp;
    int rgnIdx;
    int chanIdx;
    int nextChan;
    u8 scanType;

    chanIdx = 0;

    /* Set the default scan type to the user specified type, will later
     *   be changed to passive on a per channel basis if restricted by
     *   regulatory requirements (11d or 11h)
     */
    scanType = Adapter->ScanType;

    for (rgnIdx = 0; rgnIdx < NELEMENTS(Adapter->region_channel); rgnIdx++) {
        if (wlan_get_state_11d(priv) == ENABLE_11D &&
            Adapter->MediaConnectStatus != WlanMediaStateConnected) {
            /* Scan all the supported chan for the first scan */
            if (!Adapter->universal_channel[rgnIdx].Valid)
                continue;
            scanRegion = &Adapter->universal_channel[rgnIdx];

            /* clear the parsed_region_chan for the first scan */
            memset(&Adapter->parsed_region_chan, 0x00,
                   sizeof(Adapter->parsed_region_chan));
        } else {
            if (!Adapter->region_channel[rgnIdx].Valid)
                continue;
            scanRegion = &Adapter->region_channel[rgnIdx];
        }

        for (nextChan = 0;
             nextChan < scanRegion->NrCFP; nextChan++, chanIdx++) {

            cfp = scanRegion->CFP + nextChan;

            if (wlan_get_state_11d(priv) == ENABLE_11D) {
                scanType =
                    wlan_get_scan_type_11d(cfp->Channel,
                                           &Adapter->parsed_region_chan);
            }

            switch (scanRegion->Band) {
            case BAND_B:
            case BAND_G:
            default:
                scanChanList[chanIdx].RadioType = HostCmd_SCAN_RADIO_TYPE_BG;
                break;
            }

            if (scanType == HostCmd_SCAN_TYPE_PASSIVE) {
                scanChanList[chanIdx].MaxScanTime =
                    wlan_cpu_to_le16(Adapter->PassiveScanTime);
                scanChanList[chanIdx].ChanScanMode.PassiveScan = TRUE;
            } else {
                scanChanList[chanIdx].MaxScanTime =
                    wlan_cpu_to_le16(Adapter->ActiveScanTime);
                scanChanList[chanIdx].ChanScanMode.PassiveScan = FALSE;
            }

            scanChanList[chanIdx].ChanNumber = cfp->Channel;

            if (filteredScan) {
                scanChanList[chanIdx].MaxScanTime =
                    wlan_cpu_to_le16(Adapter->SpecificScanTime);
                scanChanList[chanIdx].ChanScanMode.DisableChanFilt = TRUE;
            }
        }
    }
}

static void
wlan_add_wps_probe_request_ie(wlan_private * priv, u8 ** ppTlvOut)
{
    wlan_adapter *Adapter = priv->adapter;
    MrvlIEtypesHeader_t *tlv;

    if (Adapter->wps.wpsIe.VendHdr.Len) {
        tlv = (MrvlIEtypesHeader_t *) * ppTlvOut;
        tlv->Type = wlan_cpu_to_le16(TLV_TYPE_WPS_ENROLLEE_PROBE_REQ_TLV);
        tlv->Len = wlan_cpu_to_le16(Adapter->wps.wpsIe.VendHdr.Len);
        *ppTlvOut += sizeof(MrvlIEtypesHeader_t);
        rt_memcpy(*ppTlvOut,
               Adapter->wps.wpsIe.VendHdr.Oui,
               Adapter->wps.wpsIe.VendHdr.Len);
        *ppTlvOut += (Adapter->wps.wpsIe.VendHdr.Len
                      + sizeof(MrvlIEtypesHeader_t));
    }
}

/**
 *  @brief Construct a wlan_scan_cmd_config structure to use in issue scan cmds
 *
 *  Application layer or other functions can invoke wlan_scan_networks
 *    with a scan configuration supplied in a wlan_ioctl_user_scan_cfg struct.
 *    This structure is used as the basis of one or many wlan_scan_cmd_config
 *    commands that are sent to the command processing module and sent to
 *    firmware.
 *
 *  Create a wlan_scan_cmd_config based on the following user supplied
 *    parameters (if present):
 *             - SSID filter
 *             - BSSID filter
 *             - Number of Probes to be sent
 *             - Channel list
 *
 *  If the SSID or BSSID filter is not present, disable/clear the filter.
 *  If the number of probes is not set, use the adapter default setting
 *  Qualify the channel
 *
 *  @param priv             A pointer to wlan_private structure
 *  @param pUserScanIn      NULL or pointer to scan configuration parameters
 *  @param pScanCfgOut      Output parameter: Resulting scan configuration
 *  @param ppChanTlvOut     Output parameter: Pointer to the start of the
 *                          channel TLV portion of the output scan config
 *  @param pScanChanList    Output parameter: Pointer to the resulting channel
 *                          list to scan
 *  @param pMaxChanPerScan  Output parameter: Number of channels to scan for
 *                          each issuance of the firmware scan command
 *  @param pFilteredScan    Output parameter: Flag indicating whether or not
 *                          a BSSID or SSID filter is being sent in the
 *                          command to firmware.  Used to increase the number
 *                          of channels sent in a scan command and to 
 *                          disable the firmware channel scan filter.
 *  @param pScanCurrentOnly Output parameter: Flag indicating whether or not
 *                          we are only scanning our current active channel
 *
 *  @return                 void
 */
static void
wlan_scan_setup_scan_config(wlan_private * priv,
                            const wlan_ioctl_user_scan_cfg * pUserScanIn,
                            wlan_scan_cmd_config * pScanCfgOut,
                            MrvlIEtypes_ChanListParamSet_t ** ppChanTlvOut,
                            ChanScanParamSet_t * pScanChanList,
                            int *pMaxChanPerScan,
                            BOOLEAN * pFilteredScan,
                            BOOLEAN * pScanCurrentOnly)
{
    wlan_adapter *Adapter = priv->adapter;
    const u8 zeroMac[ETH_ALEN] = { 0, 0, 0, 0, 0, 0 };
    MrvlIEtypes_NumProbes_t *pNumProbesTlv;
    u8 *pTlvPos;
    u16 numProbes;
    u16 ssidLen;
    int chanIdx;
    int scanType;
    int scanDur;
    int channel;
    int radioType;
    int ssidIdx;
    BOOLEAN ssidFilter;

    MrvlIEtypes_WildCardSsIdParamSet_t *pWildCardSsidTlv;

    /* The tlvBufferLen is calculated for each scan command.  The TLVs added
     *   in this routine will be preserved since the routine that sends
     *   the command will append channelTLVs at *ppChanTlvOut.  The difference
     *   between the *ppChanTlvOut and the tlvBuffer start will be used
     *   to calculate the size of anything we add in this routine.
     */
    pScanCfgOut->tlvBufferLen = 0;

    /* Running tlv pointer.  Assigned to ppChanTlvOut at end of function
     *  so later routines know where channels can be added to the command buf
     */
    pTlvPos = pScanCfgOut->tlvBuffer;

    /*
     * Set the initial scan paramters for progressive scanning.  If a specific
     *   BSSID or SSID is used, the number of channels in the scan command
     *   will be increased to the absolute maximum
     */
    *pMaxChanPerScan = MRVDRV_MAX_CHANNELS_PER_SCAN;

    /* Initialize the scan as un-filtered; the flag is later set to
     *   TRUE below if a SSID or BSSID filter is sent in the command
     */
    *pFilteredScan = FALSE;

    /* Initialize the scan as not being only on the current channel.  If
     *   the channel list is customized, only contains one channel, and
     *   is the active channel, this is set true and data flow is not halted.
     */
    *pScanCurrentOnly = FALSE;

    if (pUserScanIn) {

        /* Default the ssidFilter flag to TRUE, set false under certain 
         *   wildcard conditions and qualified by the existence of an SSID 
         *   list before marking the scan as filtered
         */
        ssidFilter = TRUE;

        /* Set the bss type scan filter, use Adapter setting if unset */
        pScanCfgOut->bssType = (pUserScanIn->bssType ? pUserScanIn->bssType :
                                Adapter->ScanMode);

        /* Set the number of probes to send, use Adapter setting if unset */
        numProbes = (pUserScanIn->numProbes ? pUserScanIn->numProbes :
                     Adapter->ScanProbes);

        /*
         * Set the BSSID filter to the incoming configuration,
         *   if non-zero.  If not set, it will remain disabled (all zeros).
         */
        memcpy(pScanCfgOut->specificBSSID,
               pUserScanIn->specificBSSID,
               sizeof(pScanCfgOut->specificBSSID));

        for (ssidIdx = 0; ((ssidIdx < NELEMENTS(pUserScanIn->ssidList))
                           && (*pUserScanIn->ssidList[ssidIdx].ssid
                               || pUserScanIn->ssidList[ssidIdx].maxLen));
             ssidIdx++) {

            ssidLen = strlen(pUserScanIn->ssidList[ssidIdx].ssid) + 1;

            pWildCardSsidTlv = (MrvlIEtypes_WildCardSsIdParamSet_t *) pTlvPos;
            pWildCardSsidTlv->Header.Type
                = wlan_cpu_to_le16(TLV_TYPE_WILDCARDSSID);
            pWildCardSsidTlv->Header.Len
                = ssidLen + sizeof(pWildCardSsidTlv->MaxSsidLength);
            pWildCardSsidTlv->MaxSsidLength
                = pUserScanIn->ssidList[ssidIdx].maxLen;

            memcpy(pWildCardSsidTlv->SsId,
                   pUserScanIn->ssidList[ssidIdx].ssid, ssidLen);

            pTlvPos += (sizeof(pWildCardSsidTlv->Header)
                        + pWildCardSsidTlv->Header.Len);

            pWildCardSsidTlv->Header.Len
                = wlan_cpu_to_le16(pWildCardSsidTlv->Header.Len);

            wlan_debug3( "Scan: ssidList[%d]: %s, %d\n",
                   ssidIdx,
                   pWildCardSsidTlv->SsId, pWildCardSsidTlv->MaxSsidLength);

            /* Empty wildcard ssid with a maxlen will match many or potentially
             *   all SSIDs (maxlen == 32), therefore do not treat the scan
             *   as filtered.
             */
            if ((ssidLen == 0) && pWildCardSsidTlv->MaxSsidLength) {
                ssidFilter = FALSE;
            }
        }

        /*
         *  The default number of channels sent in the command is low to
         *    ensure the response buffer from the firmware does not truncate
         *    scan results.  That is not an issue with an SSID or BSSID
         *    filter applied to the scan results in the firmware.
         */
        if ((ssidIdx && ssidFilter)
            || memcmp(pScanCfgOut->specificBSSID, &zeroMac, sizeof(zeroMac))) {
            *pFilteredScan = TRUE;
        }

    } else {
        pScanCfgOut->bssType = Adapter->ScanMode;
        numProbes = Adapter->ScanProbes;
    }
    wlan_debug3 ("Scan mode %d numProbes = %d\n", Adapter->ScanMode,numProbes);
    /* If the input config or adapter has the number of Probes set, add tlv */
    if (numProbes) {

        wlan_debug3("Scan: numProbes = %d\n", numProbes);

        pNumProbesTlv = (MrvlIEtypes_NumProbes_t *) pTlvPos;
        pNumProbesTlv->Header.Type = wlan_cpu_to_le16(TLV_TYPE_NUMPROBES);
        pNumProbesTlv->Header.Len = sizeof(pNumProbesTlv->NumProbes);
        pNumProbesTlv->NumProbes = wlan_cpu_to_le16(numProbes);

        pTlvPos += sizeof(pNumProbesTlv->Header) + pNumProbesTlv->Header.Len;

        pNumProbesTlv->Header.Len =
            wlan_cpu_to_le16(pNumProbesTlv->Header.Len);
    }

    wlan_add_wps_probe_request_ie(priv, &pTlvPos);

    /*
     * Set the output for the channel TLV to the address in the tlv buffer
     *   past any TLVs that were added in this fuction (SSID, numProbes).
     *   Channel TLVs will be added past this for each scan command, preserving
     *   the TLVs that were previously added.
     */
    *ppChanTlvOut = (MrvlIEtypes_ChanListParamSet_t *) pTlvPos;

    if (pUserScanIn && pUserScanIn->chanList[0].chanNumber) {

        wlan_debug3( "Scan: Using supplied channel list\n");

        for (chanIdx = 0;
             chanIdx < WLAN_IOCTL_USER_SCAN_CHAN_MAX
             && pUserScanIn->chanList[chanIdx].chanNumber; chanIdx++) {

            channel = pUserScanIn->chanList[chanIdx].chanNumber;
            (pScanChanList + chanIdx)->ChanNumber = channel;

            radioType = pUserScanIn->chanList[chanIdx].radioType;
            (pScanChanList + chanIdx)->RadioType = radioType;

            scanType = pUserScanIn->chanList[chanIdx].scanType;

            if (scanType == HostCmd_SCAN_TYPE_PASSIVE) {
                (pScanChanList + chanIdx)->ChanScanMode.PassiveScan = TRUE;
            } else {
                (pScanChanList + chanIdx)->ChanScanMode.PassiveScan = FALSE;
            }

            if (pUserScanIn->chanList[chanIdx].scanTime) {
                scanDur = pUserScanIn->chanList[chanIdx].scanTime;
            } else {
                if (scanType == HostCmd_SCAN_TYPE_PASSIVE) {
                    scanDur = Adapter->PassiveScanTime;
                } else if (*pFilteredScan) {
                    scanDur = Adapter->SpecificScanTime;
                } else {
                    scanDur = Adapter->ActiveScanTime;
                }
            }

            (pScanChanList + chanIdx)->MinScanTime =
                wlan_cpu_to_le16(scanDur);
            (pScanChanList + chanIdx)->MaxScanTime =
                wlan_cpu_to_le16(scanDur);
        }

        /* Check if we are only scanning the current channel */
        if ((chanIdx == 1)
            && (pUserScanIn->chanList[0].chanNumber
                == priv->adapter->CurBssParams.BSSDescriptor.Channel)) {
            *pScanCurrentOnly = TRUE;
            wlan_debug3("Scan: Scanning current channel only");
        }

    } else {
        wlan_debug3("Scan: Creating full region channel list\n");
        wlan_scan_create_channel_list(priv, pScanChanList, *pFilteredScan);
    }
}

/**
 *  @brief Construct and send multiple scan config commands to the firmware
 *
 *  Previous routines have created a wlan_scan_cmd_config with any requested
 *   TLVs.  This function splits the channel TLV into maxChanPerScan lists
 *   and sends the portion of the channel TLV along with the other TLVs
 *   to the wlan_cmd routines for execution in the firmware.
 *
 *  @param priv            A pointer to wlan_private structure
 *  @param maxChanPerScan  Maximum number channels to be included in each
 *                         scan command sent to firmware
 *  @param filteredScan    Flag indicating whether or not a BSSID or SSID
 *                         filter is being used for the firmware command
 *                         scan command sent to firmware
 *  @param pScanCfgOut     Scan configuration used for this scan.
 *  @param pChanTlvOut     Pointer in the pScanCfgOut where the channel TLV
 *                         should start.  This is past any other TLVs that
 *                         must be sent down in each firmware command.
 *  @param pScanChanList   List of channels to scan in maxChanPerScan segments
 *
 *  @return                WLAN_STATUS_SUCCESS or error return otherwise
 */
static int
wlan_scan_channel_list(wlan_private * priv,
                       int maxChanPerScan,
                       BOOLEAN filteredScan,
                       wlan_scan_cmd_config * pScanCfgOut,
                       MrvlIEtypes_ChanListParamSet_t * pChanTlvOut,
                       ChanScanParamSet_t * pScanChanList)
{
    ChanScanParamSet_t *pTmpChan;
    ChanScanParamSet_t *pStartChan;
    u8 scanBand;
    int doneEarly;
    int tlvIdx;
    int totalscantime;
    int ret;

    ENTER();

    if (pScanCfgOut == 0 || pChanTlvOut == 0 || pScanChanList == 0) {
        wlan_debug3( "Scan: Null detect: %p, %p, %p\n",
               pScanCfgOut, pChanTlvOut, pScanChanList);
        return WLAN_STATUS_FAILURE;
    }

    ret = WLAN_STATUS_SUCCESS;

    pChanTlvOut->Header.Type = wlan_cpu_to_le16(TLV_TYPE_CHANLIST);

    /* Set the temp channel struct pointer to the start of the desired list */
    pTmpChan = pScanChanList;

    /* Loop through the desired channel list, sending a new firmware scan
     *   commands for each maxChanPerScan channels (or for 1,6,11 individually
     *   if configured accordingly)
     */
    while (pTmpChan->ChanNumber) {

        tlvIdx = 0;
        totalscantime = 0;
        pChanTlvOut->Header.Len = 0;
        scanBand = pTmpChan->RadioType;
        pStartChan = pTmpChan;
        doneEarly = FALSE;

        /* Construct the Channel TLV for the scan command.  Continue to
         *  insert channel TLVs until:
         *    - the tlvIdx hits the maximum configured per scan command
         *    - the next channel to insert is 0 (end of desired channel list)
         *    - doneEarly is set (controlling individual scanning of 1,6,11)
         */
        while (tlvIdx < maxChanPerScan && pTmpChan->ChanNumber && !doneEarly) {

            wlan_debug3 ( "Scan: Chan(%3d), Radio(%d), Mode(%d,%d), Dur(%d)\n",
                   pTmpChan->ChanNumber,
                   pTmpChan->RadioType,
                   pTmpChan->ChanScanMode.PassiveScan,
                   pTmpChan->ChanScanMode.DisableChanFilt,
                   pTmpChan->MaxScanTime);

            /* Copy the current channel TLV to the command being prepared */
            memcpy(pChanTlvOut->ChanScanParam + tlvIdx,
                   pTmpChan, sizeof(pChanTlvOut->ChanScanParam));

            /* Increment the TLV header length by the size appended */
            pChanTlvOut->Header.Len += sizeof(pChanTlvOut->ChanScanParam);

            /*
             *  The tlv buffer length is set to the number of bytes of the
             *    between the channel tlv pointer and the start of the
             *    tlv buffer.  This compensates for any TLVs that were appended
             *    before the channel list.
             */
            pScanCfgOut->tlvBufferLen = ((u8 *) pChanTlvOut
                                         - pScanCfgOut->tlvBuffer);

            /*  Add the size of the channel tlv header and the data length */
            pScanCfgOut->tlvBufferLen += (sizeof(pChanTlvOut->Header)
                                          + pChanTlvOut->Header.Len);

            /* Increment the index to the channel tlv we are constructing */
            tlvIdx++;

            /* Count the total scan time per command */
            totalscantime += pTmpChan->MaxScanTime;

            doneEarly = FALSE;

            /* Stop the loop if the *current* channel is in the 1,6,11 set
             *   and we are not filtering on a BSSID or SSID.
             */
            if (!filteredScan && (pTmpChan->ChanNumber == 1
                                  || pTmpChan->ChanNumber == 6
                                  || pTmpChan->ChanNumber == 11)) {
                doneEarly = TRUE;
            }

            /* Increment the tmp pointer to the next channel to be scanned */
            pTmpChan++;

            /* Stop the loop if the *next* channel is in the 1,6,11 set.
             *  This will cause it to be the only channel scanned on the next
             *  interation
             */
            if (!filteredScan && (pTmpChan->ChanNumber == 1
                                  || pTmpChan->ChanNumber == 6
                                  || pTmpChan->ChanNumber == 11)) {
                doneEarly = TRUE;
            }
        }

        /* The total scan time should be less than scan command timeout value */
        if (totalscantime > MRVDRV_MAX_TOTAL_SCAN_TIME) {
            wlan_debug2 ( "Total scan time %d ms is over limit (%d ms), scan skipped\n",
                   totalscantime, MRVDRV_MAX_TOTAL_SCAN_TIME);
            ret = WLAN_STATUS_FAILURE;
            break;
        }

        pChanTlvOut->Header.Len = wlan_cpu_to_le16(pChanTlvOut->Header.Len);

        /* Send the scan command to the firmware with the specified cfg */
        ret = PrepareAndSendCommand(priv, HostCmd_CMD_802_11_SCAN, 0,
                                    HostCmd_OPTION_WAITFORRSP, 0,
                                    pScanCfgOut);
    }

    LEAVE();

    if (ret) {
        return WLAN_STATUS_FAILURE;
    }

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Internal function used to start a scan based on an input config
 *
 *  Use the input user scan configuration information when provided in
 *    order to send the appropriate scan commands to firmware to populate or
 *    update the internal driver scan table
 *
 *  @param priv          A pointer to wlan_private structure
 *  @param pUserScanIn   Pointer to the input configuration for the requested
 *                       scan.
 *
 *  @return              WLAN_STATUS_SUCCESS or < 0 if error
 */
static int
wlan_scan_networks(wlan_private * priv,
                   const wlan_ioctl_user_scan_cfg * pUserScanIn)
{
    wlan_adapter *Adapter = priv->adapter;
    MrvlIEtypes_ChanListParamSet_t *pChanTlvOut;

    ChanScanParamSet_t scanChanList[WLAN_IOCTL_USER_SCAN_CHAN_MAX];
    wlan_scan_cmd_config_tlv scanCfgOut;
    BOOLEAN keepPreviousScan;
    BOOLEAN filteredScan;
    BOOLEAN scanCurrentChanOnly;
    int maxChanPerScan;
    int ret;
    BOOLEAN bBgScan;

    ENTER();

    memset(scanChanList, 0x00, sizeof(scanChanList));
    memset(&scanCfgOut, 0x00, sizeof(scanCfgOut));

    keepPreviousScan = FALSE;

    wlan_scan_setup_scan_config(priv,
                                pUserScanIn,
                                &scanCfgOut.config,
                                &pChanTlvOut,
                                scanChanList,
                                &maxChanPerScan,
                                &filteredScan, &scanCurrentChanOnly);

    if (pUserScanIn) {
        keepPreviousScan = pUserScanIn->keepPreviousScan;
    }

    if (keepPreviousScan == FALSE) {
        memset(Adapter->ScanTable, 0x00,
               sizeof(BSSDescriptor_t) * MRVDRV_MAX_BSSID_LIST);
        Adapter->NumInScanTable = 0;
        Adapter->pBeaconBufEnd = Adapter->beaconBuffer;
    }

    /* Keep the data path active if we are only scanning our current channel */
    if (!scanCurrentChanOnly) {
        wlan_debug2 ( "Scan: WMM Queue stop\n");
      //  priv->wlan_dev.netdev->watchdog_timeo = MRVDRV_SCAN_WATCHDOG_TIMEOUT;
        /* If WMM queues are in use, only stop the internal data queues */
        wmm_stop_queue(priv);
    }

    bBgScan = priv->adapter->bgScanConfig->Enable;
    if (priv->adapter->bgScanConfig->Enable == TRUE) {
        wlan_bg_scan_enable(priv, FALSE);
    }

    ret = wlan_scan_channel_list(priv,
                                 maxChanPerScan,
                                 filteredScan,
                                 &scanCfgOut.config,
                                 pChanTlvOut, scanChanList);

    /*  Process the resulting scan table:
     *    - Remove any bad ssids
     *    - Update our current BSS information from scan data
     */
    wlan_scan_process_results(priv);

    if (bBgScan == TRUE) {
        wlan_bg_scan_enable(priv, TRUE);
    }

    wlan_debug2("Scan: WMM Queue start\n");

//    priv->wlan_dev.netdev->watchdog_timeo = MRVDRV_DEFAULT_WATCHDOG_TIMEOUT;

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        wmm_start_queue(priv);
    }
  
    LEAVE();
    return ret;
}

/**
 *  @brief Create a brief scan resp to relay basic BSS info to the app layer
 *
 *  When the beacon/probe response has not been buffered, use the saved BSS
 *    information available to provide a minimum response for the application
 *    ioctl retrieval routines.  Include:
 *        - Timestamp
 *        - Beacon Period
 *        - Capabilities (including WMM Element if available)
 *        - SSID
 *
 *  @param ppBuffer  Output parameter: Buffer used to create basic scan rsp
 *  @param pBSSDesc  Pointer to a BSS entry in the scan table to create
 *                   scan response from for delivery to the application layer
 *
 *  @return          void
 */
static void
wlan_scan_create_brief_table_entry(u8 ** ppBuffer, BSSDescriptor_t * pBSSDesc)
{
    u8 *pTmpBuf = *ppBuffer;
    u8 tmpSSIDHdr[2];
    u8 ieLen;

    if (memcpy(pTmpBuf, pBSSDesc->TimeStamp,
                     sizeof(pBSSDesc->TimeStamp))) {
        wlan_debug3("Copy to user failed\n");
        return;
    }
    pTmpBuf += sizeof(pBSSDesc->TimeStamp);

    if (memcpy(pTmpBuf, &pBSSDesc->BeaconPeriod,
                     sizeof(pBSSDesc->BeaconPeriod))) {
        wlan_debug3("Copy to user failed\n");
        return;
    }
    pTmpBuf += sizeof(pBSSDesc->BeaconPeriod);

    if (memcpy(pTmpBuf, &pBSSDesc->Cap, sizeof(pBSSDesc->Cap))) {
        wlan_debug3("Copy to user failed\n");
        return;
    }
    pTmpBuf += sizeof(pBSSDesc->Cap);

    tmpSSIDHdr[0] = 0;          /* Element ID for SSID is zero */
    tmpSSIDHdr[1] = pBSSDesc->Ssid.SsidLength;
    if (memcpy(pTmpBuf, tmpSSIDHdr, sizeof(tmpSSIDHdr))) {
        wlan_debug3("Copy to user failed\n");
        return;
    }
    pTmpBuf += sizeof(tmpSSIDHdr);

    if (memcpy(pTmpBuf, pBSSDesc->Ssid.Ssid, pBSSDesc->Ssid.SsidLength)) {
        wlan_debug3("Copy to user failed\n");
        return;
    }
    pTmpBuf += pBSSDesc->Ssid.SsidLength;

    if (pBSSDesc->wmmIE.VendHdr.ElementId == WMM_IE) {
        ieLen = sizeof(IEEEtypes_Header_t) + pBSSDesc->wmmIE.VendHdr.Len;
        if (memcpy(pTmpBuf, &pBSSDesc->wmmIE, ieLen)) {
            wlan_debug3("Copy to user failed\n");
            return;
        }

        pTmpBuf += ieLen;
    }

    if (pBSSDesc->wpaIE.VendHdr.ElementId == WPA_IE) {
        ieLen = sizeof(IEEEtypes_Header_t) + pBSSDesc->wpaIE.VendHdr.Len;
        if (memcpy(pTmpBuf, &pBSSDesc->wpaIE, ieLen)) {
            wlan_debug3("Copy to user failed\n");
            return;
        }

        pTmpBuf += ieLen;
    }

    if (pBSSDesc->rsnIE.IeeeHdr.ElementId == RSN_IE) {
        ieLen = sizeof(IEEEtypes_Header_t) + pBSSDesc->rsnIE.IeeeHdr.Len;
        if (memcpy(pTmpBuf, &pBSSDesc->rsnIE, ieLen)) {
            wlan_debug3("Copy to user failed\n");
            return;
        }

        pTmpBuf += ieLen;
    }

    *ppBuffer = pTmpBuf;
}

/**
 *  @brief Inspect the scan response buffer for pointers to expected TLVs
 *
 *  TLVs can be included at the end of the scan response BSS information.
 *    Parse the data in the buffer for pointers to TLVs that can potentially
 *    be passed back in the response
 *
 *  @param pTlv        Pointer to the start of the TLV buffer to parse
 *  @param tlvBufSize  Size of the TLV buffer
 *  @param pTsfTlv     Output parameter: Pointer to the TSF TLV if found
 *
 *  @return            void
 */
static void
wlan_ret_802_11_scan_get_tlv_ptrs(MrvlIEtypes_Data_t * pTlv,
                                  int tlvBufSize,
                                  MrvlIEtypes_TsfTimestamp_t ** pTsfTlv)
{
    MrvlIEtypes_Data_t *pCurrentTlv;
    int tlvBufLeft;
    u16 tlvType;
    u16 tlvLen;

    pCurrentTlv = pTlv;
    tlvBufLeft = tlvBufSize;
    *pTsfTlv = NULL;

    wlan_debug3("SCAN_RESP: tlvBufSize = %d\n", tlvBufSize);
    while (tlvBufLeft >= sizeof(MrvlIEtypesHeader_t)) {
        tlvType = wlan_le16_to_cpu(pCurrentTlv->Header.Type);
        tlvLen = wlan_le16_to_cpu(pCurrentTlv->Header.Len);

        switch (tlvType) {
        case TLV_TYPE_TSFTIMESTAMP:
            wlan_debug3("SCAN_RESP: TSF Timestamp TLV, len = %d\n", tlvLen);
            *pTsfTlv = (MrvlIEtypes_TsfTimestamp_t *) pCurrentTlv;
            break;

        default:
            wlan_debug3("SCAN_RESP: Unhandled TLV = %d\n", tlvType);
            /* Give up, this seems corrupted */
            return;
        }                       /* switch */

        tlvBufLeft -= (sizeof(pTlv->Header) + tlvLen);
        pCurrentTlv = (MrvlIEtypes_Data_t *) (pCurrentTlv->Data + tlvLen);
    }                           /* while */
}

/**
 *  @brief Interpret a BSS scan response returned from the firmware
 *
 *  Parse the various fixed fields and IEs passed back for a a BSS probe
 *   response or beacon from the scan command.  Record information as needed
 *   in the scan table BSSDescriptor_t for that entry.
 *
 *  @param pBSSIDEntry  Output parameter: Pointer to the BSS Entry
 *
 *  @return             WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
InterpretBSSDescriptionWithIE(BSSDescriptor_t * pBSSEntry,
                              u8 ** pBeaconInfo, int *bytesLeft)
{
    IEEEtypes_ElementId_e elemID;
    IEEEtypes_FhParamSet_t *pFH;
    IEEEtypes_DsParamSet_t *pDS;
    IEEEtypes_CfParamSet_t *pCF;
    IEEEtypes_IbssParamSet_t *pIbss;
    IEEEtypes_CapInfo_t *pCap;
    WLAN_802_11_FIXED_IEs fixedIE;
    u8 *pCurrentPtr;
    u8 *pRate;
    u8 elemLen;
    u16 totalIeLen;
    u8 bytesToCopy;
    u8 rateSize;
    u16 beaconSize;
    BOOLEAN foundDataRateIE;
    int bytesLeftForCurrentBeacon;
    IEEEtypes_ERPInfo_t *pERPInfo;

    IEEEtypes_VendorSpecific_t *pVendorIe;
    const u8 wpa_oui[4] = { 0x00, 0x50, 0xf2, 0x01 };
    const u8 wmm_oui[4] = { 0x00, 0x50, 0xf2, 0x02 };
    const u8 wps_oui[4] = { 0x00, 0x50, 0xf2, 0x04 };

    IEEEtypes_CountryInfoSet_t *pcountryinfo;

    ENTER();

    foundDataRateIE = FALSE;
    rateSize = 0;
    beaconSize = 0;

    if (*bytesLeft >= sizeof(beaconSize)) {
        /* Extract & convert beacon size from the command buffer */
        memcpy(&beaconSize, *pBeaconInfo, sizeof(beaconSize));
        beaconSize = wlan_le16_to_cpu(beaconSize);
        *bytesLeft -= sizeof(beaconSize);
        *pBeaconInfo += sizeof(beaconSize);
    }

    if (beaconSize == 0 || beaconSize > *bytesLeft) {

        *pBeaconInfo += *bytesLeft;
        *bytesLeft = 0;

        return WLAN_STATUS_FAILURE;
    }

    /* Initialize the current working beacon pointer for this BSS iteration */
    pCurrentPtr = *pBeaconInfo;

    /* Advance the return beacon pointer past the current beacon */
    *pBeaconInfo += beaconSize;
    *bytesLeft -= beaconSize;

    bytesLeftForCurrentBeacon = beaconSize;

    memcpy(pBSSEntry->MacAddress, pCurrentPtr, MRVDRV_ETH_ADDR_LEN);
    wlan_debug3("InterpretIE: AP MAC Addr-%02x:%02x:%02x:%02x:%02x:%02x\n",
           pBSSEntry->MacAddress[0], pBSSEntry->MacAddress[1],
           pBSSEntry->MacAddress[2], pBSSEntry->MacAddress[3],
           pBSSEntry->MacAddress[4], pBSSEntry->MacAddress[5]);

    pCurrentPtr += MRVDRV_ETH_ADDR_LEN;
    bytesLeftForCurrentBeacon -= MRVDRV_ETH_ADDR_LEN;

    if (bytesLeftForCurrentBeacon < 12) {
        wlan_debug3("InterpretIE: Not enough bytes left\n");
        return WLAN_STATUS_FAILURE;
    }

    /*
     * next 4 fields are RSSI, time stamp, beacon interval,
     *   and capability information
     */

    /* RSSI is 1 byte long */
    pBSSEntry->Rssi = wlan_le32_to_cpu((LONG) (*pCurrentPtr));
    wlan_debug3("InterpretIE: RSSI=%02X\n", *pCurrentPtr);
    pCurrentPtr += 1;
    bytesLeftForCurrentBeacon -= 1;

    /*
     *  The RSSI is not part of the beacon/probe response.  After we have
     *    advanced pCurrentPtr past the RSSI field, save the remaining
     *    data for use at the application layer
     */
    pBSSEntry->pBeaconBuf = pCurrentPtr;
    pBSSEntry->beaconBufSize = bytesLeftForCurrentBeacon;

    /* time stamp is 8 bytes long */
    memcpy(fixedIE.Timestamp, pCurrentPtr, 8);
    memcpy(pBSSEntry->TimeStamp, pCurrentPtr, 8);
    pCurrentPtr += 8;
    bytesLeftForCurrentBeacon -= 8;

    /* beacon interval is 2 bytes long */
    memcpy(&fixedIE.BeaconInterval, pCurrentPtr, 2);
    pBSSEntry->BeaconPeriod = wlan_le16_to_cpu(fixedIE.BeaconInterval);
    pCurrentPtr += 2;
    bytesLeftForCurrentBeacon -= 2;

    /* capability information is 2 bytes long */
    memcpy(&fixedIE.Capabilities, pCurrentPtr, 2);
    wlan_debug3("InterpretIE: fixedIE.Capabilities=0x%X\n",
           fixedIE.Capabilities);
    fixedIE.Capabilities = wlan_le16_to_cpu(fixedIE.Capabilities);
    pCap = (IEEEtypes_CapInfo_t *) & fixedIE.Capabilities;
    memcpy(&pBSSEntry->Cap, pCap, sizeof(IEEEtypes_CapInfo_t));
    pCurrentPtr += 2;
    bytesLeftForCurrentBeacon -= 2;

    /* rest of the current buffer are IE's */
    wlan_debug3("InterpretIE: IELength for this AP = %d\n",
           bytesLeftForCurrentBeacon);

    if (pCap->Privacy) {
        wlan_debug3("InterpretIE: AP WEP enabled\n");
        pBSSEntry->Privacy = Wlan802_11PrivFilter8021xWEP;
    } else {
        pBSSEntry->Privacy = Wlan802_11PrivFilterAcceptAll;
    }

    if (pCap->Ibss == 1) {
        pBSSEntry->InfrastructureMode = Wlan802_11IBSS;
    } else {
        pBSSEntry->InfrastructureMode = Wlan802_11Infrastructure;
    }

    /* process variable IE */
    while (bytesLeftForCurrentBeacon >= 2) {
        elemID = (IEEEtypes_ElementId_e) (*((u8 *) pCurrentPtr));
        elemLen = *((u8 *) pCurrentPtr + 1);
        totalIeLen = elemLen + sizeof(IEEEtypes_Header_t);

        if (bytesLeftForCurrentBeacon < elemLen) {
            wlan_debug3("InterpretIE: Error in processing IE, "
                   "bytes left < IE length\n");
            bytesLeftForCurrentBeacon = 0;
            continue;
        }

        switch (elemID) {

        case SSID:
            pBSSEntry->Ssid.SsidLength = elemLen;
            memcpy(pBSSEntry->Ssid.Ssid, (pCurrentPtr + 2), elemLen);
            wlan_debug3("InterpretIE: Ssid: %-32s\n", pBSSEntry->Ssid.Ssid);
            break;

        case SUPPORTED_RATES:
            memcpy(pBSSEntry->DataRates, pCurrentPtr + 2, elemLen);
            memcpy(pBSSEntry->SupportedRates, pCurrentPtr + 2, elemLen);

            rateSize = elemLen;
            foundDataRateIE = TRUE;
            break;

        case EXTRA_IE:
            wlan_debug3("InterpretIE: EXTRA_IE Found!\n");
            pBSSEntry->extra_ie = 1;
            break;

        case FH_PARAM_SET:
            pFH = (IEEEtypes_FhParamSet_t *) pCurrentPtr;
            pBSSEntry->NetworkTypeInUse = Wlan802_11FH;
            memcpy(&pBSSEntry->PhyParamSet.FhParamSet, pFH,
                   sizeof(IEEEtypes_FhParamSet_t));
            pBSSEntry->PhyParamSet.FhParamSet.DwellTime
                =
                wlan_le16_to_cpu(pBSSEntry->PhyParamSet.FhParamSet.DwellTime);
            break;

        case DS_PARAM_SET:
            pDS = (IEEEtypes_DsParamSet_t *) pCurrentPtr;

            pBSSEntry->NetworkTypeInUse = Wlan802_11DS;
            pBSSEntry->Channel = pDS->CurrentChan;

            memcpy(&pBSSEntry->PhyParamSet.DsParamSet, pDS,
                   sizeof(IEEEtypes_DsParamSet_t));
            break;

        case CF_PARAM_SET:
            pCF = (IEEEtypes_CfParamSet_t *) pCurrentPtr;
            memcpy(&pBSSEntry->SsParamSet.CfParamSet, pCF,
                   sizeof(IEEEtypes_CfParamSet_t));
            break;

        case IBSS_PARAM_SET:
            pIbss = (IEEEtypes_IbssParamSet_t *) pCurrentPtr;
            pBSSEntry->ATIMWindow = wlan_le32_to_cpu(pIbss->AtimWindow);
            memcpy(&pBSSEntry->SsParamSet.IbssParamSet, pIbss,
                   sizeof(IEEEtypes_IbssParamSet_t));
            break;

            /* Handle Country Info IE */
        case COUNTRY_INFO:
            pcountryinfo = (IEEEtypes_CountryInfoSet_t *) pCurrentPtr;

            if (pcountryinfo->Len < sizeof(pcountryinfo->CountryCode)
                || pcountryinfo->Len > 254) {
                wlan_debug3("InterpretIE: 11D- Err "
                       "CountryInfo len =%d min=%d max=254\n",
                       pcountryinfo->Len, sizeof(pcountryinfo->CountryCode));
                LEAVE();
                return WLAN_STATUS_FAILURE;
            }

            memcpy(&pBSSEntry->CountryInfo,
                   pcountryinfo, pcountryinfo->Len + 2);

            break;
        case ERP_INFO:
            pERPInfo = (IEEEtypes_ERPInfo_t *) pCurrentPtr;
            pBSSEntry->ERPFlags = pERPInfo->ERPFlags;
            break;
        case EXTENDED_SUPPORTED_RATES:
            /*
             * only process extended supported rate
             * if data rate is already found.
             * data rate IE should come before
             * extended supported rate IE
             */
            if (foundDataRateIE) {
                if ((elemLen + rateSize) > WLAN_SUPPORTED_RATES) {
                    bytesToCopy = (WLAN_SUPPORTED_RATES - rateSize);
                } else {
                    bytesToCopy = elemLen;
                }

                pRate = (u8 *) pBSSEntry->DataRates;
                pRate += rateSize;
                memcpy(pRate, pCurrentPtr + 2, bytesToCopy);

                pRate = (u8 *) pBSSEntry->SupportedRates;
                pRate += rateSize;
                memcpy(pRate, pCurrentPtr + 2, bytesToCopy);
            }

            break;

        case VENDOR_SPECIFIC_221:
            pVendorIe = (IEEEtypes_VendorSpecific_t *) pCurrentPtr;

            if (!memcmp(pVendorIe->VendHdr.Oui, wpa_oui, sizeof(wpa_oui))) {
                pBSSEntry->wpaIE.VendHdr.Len
                    = (MIN(totalIeLen, sizeof(pBSSEntry->wpaIE))
                       - sizeof(IEEEtypes_Header_t));

                memcpy(&pBSSEntry->wpaIE,
                       pCurrentPtr,
                       (pBSSEntry->wpaIE.VendHdr.Len
                        + sizeof(IEEEtypes_Header_t)));
            } else if (!memcmp(pVendorIe->VendHdr.Oui,
                               wmm_oui, sizeof(wmm_oui))) {
                if (totalIeLen == sizeof(IEEEtypes_WmmParameter_t)
                    || totalIeLen == sizeof(IEEEtypes_WmmInfo_t)) {

                    /* Only accept and copy the WMM IE if it matches
                     *  the size expected for the WMM Info IE or the
                     *  WMM Parameter IE.
                     */
                    memcpy((u8 *) & pBSSEntry->wmmIE, pCurrentPtr,
                           totalIeLen);

                }
            } else if (!memcmp(pVendorIe->VendHdr.Oui,
                               wps_oui, sizeof(wps_oui))) {
                memcpy((u8 *) & pBSSEntry->wpsIE, pCurrentPtr, totalIeLen);

            }
            break;
        case RSN_IE:
            pBSSEntry->rsnIE.IeeeHdr.Len
                = (MIN(totalIeLen, sizeof(pBSSEntry->rsnIE))
                   - sizeof(IEEEtypes_Header_t));

            memcpy(&pBSSEntry->rsnIE,
                   pCurrentPtr,
                   pBSSEntry->rsnIE.IeeeHdr.Len + sizeof(IEEEtypes_Header_t));


            break;
        }

        pCurrentPtr += elemLen + 2;

        /* need to account for IE ID and IE Len */
        bytesLeftForCurrentBeacon -= (elemLen + 2);

    }                           /* while (bytesLeftForCurrentBeacon > 2) */

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Compare two SSIDs
 *
 *  @param ssid1    A pointer to ssid to compare
 *  @param ssid2    A pointer to ssid to compare
 *
 *  @return         0--ssid is same, otherwise is different
 */
int
SSIDcmp(WLAN_802_11_SSID * ssid1, WLAN_802_11_SSID * ssid2)
{
    if (!ssid1 || !ssid2)
        return -1;

    if (ssid1->SsidLength != ssid2->SsidLength)
        return -1;

    return memcmp(ssid1->Ssid, ssid2->Ssid, ssid1->SsidLength);
}

/**
 *  @brief This function finds a specific compatible BSSID in the scan list
 *
 *  @param Adapter  A pointer to wlan_adapter
 *  @param bssid    BSSID to find in the scan list
 *  @param mode     Network mode: Infrastructure or IBSS
 *
 *  @return         index in BSSID list, or error return code (< 0)
 */
int
FindBSSIDInList(wlan_adapter * Adapter, u8 * bssid, int mode)
{
    int ret = -ENETUNREACH;
    int i;

    if (!bssid)
        return -EFAULT;

    wlan_debug3("FindBSSID: Num of BSSIDs = %d\n", Adapter->NumInScanTable);

    /* Look through the scan table for a compatible match. The ret return
     *   variable will be equal to the index in the scan table (greater
     *   than zero) if the network is compatible.  The loop will continue
     *   past a matched bssid that is not compatible in case there is an
     *   AP with multiple SSIDs assigned to the same BSSID
     */
    for (i = 0; ret < 0 && i < Adapter->NumInScanTable; i++) {
        if (!memcmp(Adapter->ScanTable[i].MacAddress, bssid, ETH_ALEN)) {
            switch (mode) {
            case Wlan802_11Infrastructure:
            case Wlan802_11IBSS:
                ret = IsNetworkCompatible(Adapter, i, mode);
                break;
            default:
                ret = i;
                break;
            }
        }
    }

    return ret;
}

/**
 *  @brief This function finds ssid in ssid list.
 *
 *  @param Adapter      A pointer to wlan_adapter
 *  @param ssid         SSID to find in the list
 *  @param bssid        BSSID to qualify the SSID selection (if provided)
 *  @param mode         Network mode: Infrastructure or IBSS
 *
 *  @return         index in BSSID list
 */
int
FindSSIDInList(wlan_adapter * Adapter, WLAN_802_11_SSID * ssid,
               u8 * bssid, int mode)
{
    int net = -ENETUNREACH;
    u8 bestrssi = 0;
    int i, j;

    wlan_debug3( "Num of Entries in Table = %d\n", Adapter->NumInScanTable);

    /* Loop through the table until the maximum is reached or until a match
     *   is found based on the bssid field comparison 
     */
    for (i = 0;
         i < Adapter->NumInScanTable && (bssid == NULL || (bssid && net < 0));
         i++) {

        if (!SSIDcmp(&Adapter->ScanTable[i].Ssid, ssid) && ((bssid == NULL)
                                                            ||
                                                            !memcmp(Adapter->
                                                                    ScanTable
                                                                    [i].
                                                                    MacAddress,
                                                                    bssid,
                                                                    ETH_ALEN)))
        {
            switch (mode) {
            case Wlan802_11Infrastructure:
            case Wlan802_11IBSS:
                j = IsNetworkCompatible(Adapter, i, mode);

                if (j >= 0) {
                    if (SCAN_RSSI(Adapter->ScanTable[i].Rssi) > bestrssi) {
                        bestrssi = SCAN_RSSI(Adapter->ScanTable[i].Rssi);
                        net = i;
                    }
                } else {
                    if (net == -ENETUNREACH) {
                        net = j;
                    }
                }
                break;
            case Wlan802_11AutoUnknown:
            default:
                /* Do not check compatibility if the mode requested is 
                 *   AutoUnknown.  Allows generic find to work without 
                 *   verifying against the Adapter security settings
                 */
                if (SCAN_RSSI(Adapter->ScanTable[i].Rssi) > bestrssi) {
                    bestrssi = SCAN_RSSI(Adapter->ScanTable[i].Rssi);
                    net = i;
                }
                break;
            }
        }
    }

    return net;
}

/**
 *  @brief This function finds the best SSID in the Scan List
 *
 *  Search the scan table for the best SSID that also matches the current
 *   adapter network preference (infrastructure or adhoc)
 *
 *  @param Adapter  A pointer to wlan_adapter
 *
 *  @return         index in BSSID list
 */
int
FindBestSSIDInList(wlan_adapter * Adapter)
{
    int mode = Adapter->InfrastructureMode;
    int bestnet = -ENETUNREACH;
    u8 bestrssi = 0;
    int i;

    ENTER();

    wlan_debug3("Num of BSSIDs = %d\n", Adapter->NumInScanTable);

    for (i = 0; i < Adapter->NumInScanTable; i++) {
        switch (mode) {
        case Wlan802_11Infrastructure:
        case Wlan802_11IBSS:
            if (IsNetworkCompatible(Adapter, i, mode) >= 0) {
                if (SCAN_RSSI(Adapter->ScanTable[i].Rssi) > bestrssi) {
                    bestrssi = SCAN_RSSI(Adapter->ScanTable[i].Rssi);
                    bestnet = i;
                }
            }
            break;
        case Wlan802_11AutoUnknown:
        default:
            if (SCAN_RSSI(Adapter->ScanTable[i].Rssi) > bestrssi) {
                bestrssi = SCAN_RSSI(Adapter->ScanTable[i].Rssi);
                bestnet = i;
            }
            break;
        }
    }

    LEAVE();
    return bestnet;
}

/**
 *  @brief Find the AP with specific ssid in the scan list
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param pSSID        A pointer to AP's ssid
 *
 *  @return             WLAN_STATUS_SUCCESS--success, otherwise--fail
 */
int
FindBestNetworkSsid(wlan_private * priv, WLAN_802_11_SSID * pSSID)
{
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    BSSDescriptor_t *pReqBSSID;
    int i;

    ENTER();

    memset(pSSID, 0, sizeof(WLAN_802_11_SSID));

    wlan_scan_networks(priv, NULL);

    i = FindBestSSIDInList(Adapter);

    if (i >= 0) {

        pReqBSSID = &Adapter->ScanTable[i];
        memcpy(pSSID, &pReqBSSID->Ssid, sizeof(WLAN_802_11_SSID));

        /* Make sure we are in the right mode */
        if (Adapter->InfrastructureMode == Wlan802_11AutoUnknown) {
            Adapter->InfrastructureMode = pReqBSSID->InfrastructureMode;

            ret = PrepareAndSendCommand(priv,
                                        HostCmd_CMD_802_11_SNMP_MIB,
                                        HostCmd_ACT_SET,
                                        HostCmd_OPTION_WAITFORRSP,
                                        OID_802_11_INFRASTRUCTURE_MODE, NULL);

            if (ret) {
                LEAVE();
                return ret;
            }
        }
    }

    if (!pSSID->SsidLength) {
        ret = WLAN_STATUS_FAILURE;
    }

    LEAVE();
    return ret;
}

/**
 *  @brief Delete a specific indexed entry from the scan table.
 *
 *  Delete the scan table entry indexed by tableIdx.  Compact the remaining
 *    entries and adjust any buffering of beacon/probe response data
 *    if needed.
 *
 *  @param priv       A pointer to wlan_private structure
 *  @param tableIdx   Scan table entry index to delete from the table
 *
 *  @return           void
 *
 *  @pre              tableIdx must be an index to a valid entry
 */
static void
wlan_scan_delete_table_entry(wlan_private * priv, int tableIdx)
{
    wlan_adapter *Adapter = priv->adapter;
    int delIdx;
    unsigned int beaconBufAdj;
    u8 *pBeaconBuf;

    /* Shift the saved beacon buffer data for the scan table back over the
     *   entry being removed.  Update the end of buffer pointer.  Save the 
     *   deleted buffer allocation size for pointer adjustments for entries
     *   compacted after the deleted index.
     */
    beaconBufAdj = Adapter->ScanTable[tableIdx].beaconBufSizeMax;

    wlan_debug3("Scan: Delete Entry %d, beacon buffer removal = %d bytes\n",
           tableIdx, beaconBufAdj);

    /* Check if the table entry had storage allocated for its beacon */
    if (beaconBufAdj) {
        pBeaconBuf = Adapter->ScanTable[tableIdx].pBeaconBuf;

        /* Remove the entry's buffer space, decrement the table end pointer
         *   by the amount we are removing 
         */
        Adapter->pBeaconBufEnd -= beaconBufAdj;

        wlan_debug3(
               "Scan: Delete Entry %d, compact data: %p <- %p (sz = %d)\n",
               tableIdx,
               pBeaconBuf,
               pBeaconBuf + beaconBufAdj,
               Adapter->pBeaconBufEnd - pBeaconBuf);

        /* Compact data storage.  Copy all data after the deleted entry's
         *   end address (pBeaconBuf + beaconBufAdj) back to the original
         *   start address (pBeaconBuf).
         *
         * Scan table entries affected by the move will have their entry
         *   pointer adjusted below.
         *
         * Use memmove since the dest/src memory regions overlap.
         */
        memmove(pBeaconBuf,
                pBeaconBuf + beaconBufAdj,
                Adapter->pBeaconBufEnd - pBeaconBuf);
    }

    wlan_debug3( "Scan: Delete Entry %d, NumInScanTable = %d\n",
           tableIdx, Adapter->NumInScanTable);

    /* Shift all of the entries after the tableIdx back by one, compacting
     *   the table and removing the requested entry
     */
    for (delIdx = tableIdx; (delIdx + 1) < Adapter->NumInScanTable; delIdx++) {
        /* Copy the next entry over this one */
        memcpy(Adapter->ScanTable + delIdx,
               Adapter->ScanTable + delIdx + 1, sizeof(BSSDescriptor_t));

        /* Adjust this entry's pointer to its beacon buffer based on the 
         *   removed/compacted entry from the deleted index.  Don't decrement
         *   if the buffer pointer is NULL (no data stored for this entry).
         */
        if (Adapter->ScanTable[delIdx].pBeaconBuf) {
            Adapter->ScanTable[delIdx].pBeaconBuf -= beaconBufAdj;
        }
    }

    /* The last entry is invalid now that it has been deleted or moved back */
    memset(Adapter->ScanTable + Adapter->NumInScanTable - 1,
           0x00, sizeof(BSSDescriptor_t));

    Adapter->NumInScanTable--;
}

/**
 *  @brief Delete all occurrences of a given SSID from the scan table
 *
 *  Iterate through the scan table and delete all entries that match a given
 *    SSID.  Compact the remaining scan table entries.
 *
 *  @param priv       A pointer to wlan_private structure
 *  @param pDelSSID   Pointer to an SSID struct to use in deleting all
 *                    matching SSIDs from the scan table
 *
 *  @return           WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 *
 */
static int
wlan_scan_delete_ssid_table_entry(wlan_private * priv,
                                  WLAN_802_11_SSID * pDelSSID)
{
    int tableIdx;
    int retval = WLAN_STATUS_FAILURE;

    ENTER();

    wlan_debug3("Scan: Delete Ssid Entry: %-32s\n", pDelSSID->Ssid);

    /* If the requested SSID is found in the table, delete it.  Then keep
     *   searching the table for multiple entires for the SSID until no
     *   more are found 
     */
    while ((tableIdx = FindSSIDInList(priv->adapter,
                                      pDelSSID,
                                      NULL, Wlan802_11AutoUnknown)) >= 0) {
        wlan_debug3("Scan: Delete Ssid Entry: Found Idx = %d\n", tableIdx);
        retval = WLAN_STATUS_SUCCESS;
        wlan_scan_delete_table_entry(priv, tableIdx);
    }

    LEAVE();

    return retval;
}

/**
 *  @brief Scan Network
 *
 *  @param dev          A pointer to net_device structure
 *  @param info         A pointer to iw_request_info structure
 *  @param vwrq         A pointer to iw_param structure
 *  @param extra        A pointer to extra data buf
 *
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
int
wlan_set_scan(struct rt_wlan_dev * dev, char *extra)
{
    wlan_private *priv = dev->priv;
    wlan_adapter *Adapter = priv->adapter;
  
    int debug=0;
    if (!Is_Command_Allowed(priv)) {
        wlan_debug1 ("%s: not allowed\n", __FUNCTION__);
        return -EBUSY;
    }

    if (!(debug=wlan_scan_networks(priv, NULL))) {
       // memset(&wrqu, 0, sizeof(union iwreq_data));
		wlan_debug1 ("wlan_scan_networks sucess %d\n",debug);
    }
    if (Adapter->SurpriseRemoved)
        return WLAN_STATUS_FAILURE;
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Send a scan command for all available channels filtered on a spec
 *
 *  @param priv             A pointer to wlan_private structure
 *  @param pRequestedSSID   A pointer to AP's ssid
 *
 *  @return                WLAN_STATUS_SUCCESS-success, otherwise fail
 */
int
SendSpecificSSIDScan(wlan_private * priv, WLAN_802_11_SSID * pRequestedSSID)
{
    wlan_adapter *Adapter = priv->adapter;
    wlan_ioctl_user_scan_cfg scanCfg;

    ENTER();

    if (pRequestedSSID == NULL) {
        return WLAN_STATUS_FAILURE;
    }

    wlan_scan_delete_ssid_table_entry(priv, pRequestedSSID);

    memset(&scanCfg, 0x00, sizeof(scanCfg));

    memcpy(scanCfg.ssidList[0].ssid,
           pRequestedSSID->Ssid, pRequestedSSID->SsidLength);
    scanCfg.keepPreviousScan = TRUE;

    wlan_scan_networks(priv, &scanCfg);

    if (Adapter->SurpriseRemoved)
        return WLAN_STATUS_FAILURE;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief scan an AP with specific BSSID
 *
 *  @param priv      A pointer to wlan_private structure
 *  @param bssid     A pointer to AP's bssid
 *
 *  @return          WLAN_STATUS_SUCCESS-success, otherwise fail
 */
int
SendSpecificBSSIDScan(wlan_private * priv, u8 * bssid)
{
    wlan_ioctl_user_scan_cfg scanCfg;

    ENTER();

    if (bssid == NULL) {
        return WLAN_STATUS_FAILURE;
    }

    memset(&scanCfg, 0x00, sizeof(scanCfg));
    memcpy(scanCfg.specificBSSID, bssid, sizeof(scanCfg.specificBSSID));
    scanCfg.keepPreviousScan = TRUE;

    wlan_scan_networks(priv, &scanCfg);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief  Retrieve the scan table entries via wireless tools IOCTL call
 *
 *  @param dev          A pointer to net_device structure
 *  @param info         A pointer to iw_request_info structure
 *  @param dwrq         A pointer to iw_point structure
 *  @param extra        A pointer to extra data buf
 *
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
int wlan_get_scan(struct rt_wlan_dev *dev,int *length, char *extra)
{
#if 0
    wlan_private *priv = dev->priv;
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    char *current_ev = extra;
    char *end_buf = extra + IW_SCAN_MAX_DATA;
    CHANNEL_FREQ_POWER *cfp;
    BSSDescriptor_t *pScanTable;
    char *current_val;          /* For rates */
    struct iw_scan_parameter_head iwe;        /* Temporary buffer */
    int i;
    int j;
    int rate;
	int headlen=0;
    u8 buf[16 + 256 * 2];
    u8 *ptr;
    u8 *pRawData;

	headlen=sizeof(struct iw_scan_parameter_head);
    if (!Is_Command_Allowed(priv)) {
        wlan_debug1( "%s: not allowed\n", __FUNCTION__);
        return -EBUSY;
    }

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        wlan_debug1("Current Ssid: %32s\n", Adapter->CurBssParams.BSSDescriptor.Ssid.Ssid);
    }

    wlan_debug2("Scan: Get: NumInScanTable = %d\n", Adapter->NumInScanTable);


    for (i = 0; i < Adapter->NumInScanTable; i++) {
       		if ((current_ev + MAX_SCAN_CELL_SIZE) >= end_buf) {
            wlan_debug2("i=%d break out: current_ev=%p end_buf=%p" "MAX_SCAN_CELL_SIZE=%d\n",
			               i, current_ev, end_buf, MAX_SCAN_CELL_SIZE);
            break;
      	}

        pScanTable = &Adapter->ScanTable[i];

        wlan_debug2("i=%d  Ssid: %-32s\n", i, pScanTable->Ssid.Ssid);

        cfp =find_cfp_by_band_and_channel(Adapter, 0,(u16) pScanTable->Channel);
        if (!cfp) {
            wlan_debug1("Invalid channel number %d\n", pScanTable->Channel);
            continue;
        }

        if (ssid_valid(&Adapter->ScanTable[i].Ssid) == FALSE) {
		 	wlan_debug1("Invalid channel number %d\n", pScanTable->Channel);
            continue;
        }

        /* AP MAC address */
        iwe.type = WLAN_MAC_ADDRESS;
		iwe.len = WLAN_MAC_ADDRESS_LEN+headlen;  //mac address 6*8 bytes
		rt_memcpy(current_ev,&iwe,headlen);
		current_ev+=headlen;
        rt_memcpy(current_ev,&Adapter->ScanTable[i].MacAddress, WLAN_MAC_ADDRESS_LEN);
		current_ev+=WLAN_MAC_ADDRESS_LEN;

        /* Add the ESSID*/
		iwe.type=WLAN_ESSID;
        iwe.len= Adapter->ScanTable[i].Ssid.SsidLength;

        if (iwe.len > 32) {
            iwe.len = 32;
        }
		iwe.len+=headlen;
      	rt_memcpy(current_ev,&iwe,headlen);
       	current_ev+=headlen;
		rt_memcpy(current_ev,Adapter->ScanTable[i].Ssid.Ssid,Adapter->ScanTable[i].Ssid.SsidLength);
       	current_ev+=Adapter->ScanTable[i].Ssid.SsidLength;
   
        /*network mode*/
        iwe.type = WLAN_NETWORK_MODE;
        iwe.len = (sizeof(char))+headlen;
		rt_memcpy(current_ev,&iwe,headlen);
       	current_ev+=headlen;
		((char *)current_ev)[0]=Adapter->ScanTable[i].InfrastructureMode + 1;
		current_ev+=1;
        /*frequency*/
        iwe.type = WLAN_FREQUENCY;
        iwe.len =sizeof(unsigned int)+headlen; (long) cfp->Freq * 100000;
        rt_memcpy(current_ev,&iwe,headlen);
       	current_ev+=headlen;
		*(unsigned int *)current_ev=(long) cfp->Freq * 100000;
        }
    *length = (current_ev - extra);
#endif
     return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Create a wlan_ioctl_get_scan_table_entry for a given BSS 
 *         Descriptor for inclusion in the ioctl response to the user space
 *         application.
 *
 *
 *  @param priv      A pointer to wlan_private structure
 *  @param pBSSDesc  Pointer to a BSS entry in the scan table to form
 *                   scan response from for delivery to the application layer
 *  @param ppBuffer  Output parameter: Buffer used to output scan return struct
 *  @param pSpaceLeft Output parameter: Number of bytes available in the 
 *                    response buffer.
 *
 *  @return WLAN_STATUS_SUCCESS, or < 0 with IOCTL error code
 */
static int
wlan_get_scan_table_ret_entry(wlan_private * priv,
                              BSSDescriptor_t * pBSSDesc,
                              u8 ** ppBuffer, int *pSpaceLeft)
{
    wlan_adapter *Adapter;
    wlan_ioctl_get_scan_table_entry *pRspEntry;
    wlan_ioctl_get_scan_table_entry tmpRspEntry;
    int spaceNeeded;
    u8 *pCurrent;
    int variableSize;

    const int fixedSize = (sizeof(tmpRspEntry.fixedFieldLength)
                           + sizeof(tmpRspEntry.fixedFields)
                           + sizeof(tmpRspEntry.bssInfoLength));

    ENTER();

    Adapter = priv->adapter;
    pCurrent = *ppBuffer;

    /* The variable size returned is the stored beacon size */
    variableSize = pBSSDesc->beaconBufSize;

    /* If we stored a beacon and its size was zero, set the variable
     *  size return value to the size of the brief scan response 
     *  wlan_scan_create_brief_table_entry creates.  Also used if 
     *  we are not configured to store beacons in the first place
     */
    if (variableSize == 0) {
        variableSize = pBSSDesc->Ssid.SsidLength + 2;
        variableSize += (sizeof(pBSSDesc->BeaconPeriod)
                         + sizeof(pBSSDesc->TimeStamp)
                         + sizeof(pBSSDesc->Cap));
        if (pBSSDesc->wmmIE.VendHdr.ElementId == WMM_IE) {
            variableSize += (sizeof(IEEEtypes_Header_t)
                             + pBSSDesc->wmmIE.VendHdr.Len);
        }

        if (pBSSDesc->wpaIE.VendHdr.ElementId == WPA_IE) {
            variableSize += (sizeof(IEEEtypes_Header_t)
                             + pBSSDesc->wpaIE.VendHdr.Len);
        }

        if (pBSSDesc->rsnIE.IeeeHdr.ElementId == RSN_IE) {
            variableSize += (sizeof(IEEEtypes_Header_t)
                             + pBSSDesc->rsnIE.IeeeHdr.Len);
        }
    }

    spaceNeeded = fixedSize + variableSize;

    wlan_debug3("GetScanTable: need(%d), left(%d)\n",
           spaceNeeded, *pSpaceLeft);

    if (spaceNeeded >= *pSpaceLeft) {
        *pSpaceLeft = 0;
        LEAVE();
        return -E2BIG;
    }

    *pSpaceLeft -= spaceNeeded;

    tmpRspEntry.fixedFieldLength = sizeof(pRspEntry->fixedFields);
/*
    memcpy(tmpRspEntry.fixedFields.bssid,
           pBSSDesc->MacAddress, sizeof(pRspEntry->fixedFields.bssid));

    tmpRspEntry.fixedFields.rssi = pBSSDesc->Rssi;
    tmpRspEntry.fixedFields.channel = pBSSDesc->Channel;
    tmpRspEntry.fixedFields.networkTSF = pBSSDesc->networkTSF;
    tmpRspEntry.bssInfoLength = variableSize;
 */
    /*
     *  Copy fixed fields to user space
     */
    if (memcpy(pCurrent, &tmpRspEntry, fixedSize)) {

    }
/*
    pCurrent += fixedSize;

    if (pBSSDesc->pBeaconBuf) {
 */       /*
         *  Copy variable length elements to user space
         */
 /*       if (memcpy(pCurrent, pBSSDesc->pBeaconBuf,
                         pBSSDesc->beaconBufSize)) {
            PRINTM(INFO, "Copy to user failed\n");
            LEAVE();
            return -EFAULT;
        }

        pCurrent += pBSSDesc->beaconBufSize;
    } else {
        wlan_scan_create_brief_table_entry(&pCurrent, pBSSDesc);
    }

    *ppBuffer = pCurrent;

    LEAVE();
   */
    return WLAN_STATUS_SUCCESS;	
}

/**
 *  @brief Retrieve the scan response/beacon table
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param wrq          A pointer to iwreq structure
 *
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
int
wlan_get_scan_table_ioctl(wlan_private * priv, void*wrq)
{
#if 0
    wlan_adapter *Adapter;
    BSSDescriptor_t *pBSSDesc;
    wlan_ioctl_get_scan_table_info *pRspInfo;
    int retcode;
    int retlen;
    int spaceLeft;
    u8 *pCurrent;
    u8 *pBufferEnd;
    u32 scanStart;
    u32 numScansDone;

    numScansDone = 0;
    retcode = WLAN_STATUS_SUCCESS;
    Adapter = priv->adapter;

    if (memcpy(&scanStart,
                       wrq->u.data.pointer, sizeof(scanStart)) != 0) {
        /* copy_from_user failed  */
        PRINTM(INFO, "GetScanTable: copy from user failed\n");
        return -EFAULT;
    }

    pRspInfo = (wlan_ioctl_get_scan_table_info *) wrq->u.data.pointer;
    pCurrent = pRspInfo->scan_table_entry_buffer;
//    pBufferEnd = wrq->u.data.pointer + wrq->u.data.length - 1;
    spaceLeft = pBufferEnd - pCurrent;

    PRINTM(INFO, "GetScanTable: scanStart req = %d\n", scanStart);
    PRINTM(INFO, "GetScanTable: length avail = %d\n", wrq->u.data.length);

    if (scanStart == 0) {
        PRINTM(INFO, "GetScanTable: get current BSS Descriptor\n");

        /* Use to get current association saved descriptor */
        pBSSDesc = &Adapter->CurBssParams.BSSDescriptor;

        retcode = wlan_get_scan_table_ret_entry(priv,
                                                pBSSDesc,
                                                &pCurrent, &spaceLeft);

        if (retcode == WLAN_STATUS_SUCCESS) {
            numScansDone = 1;
        }

    } else {
        scanStart--;

        while (spaceLeft
               && (scanStart + numScansDone < Adapter->NumInScanTable)
               && (retcode == WLAN_STATUS_SUCCESS)) {

            pBSSDesc = &Adapter->ScanTable[scanStart + numScansDone];

            PRINTM(INFO, "GetScanTable: get current BSS Descriptor [%d]\n",
                   scanStart + numScansDone);

            retcode = wlan_get_scan_table_ret_entry(priv,
                                                    pBSSDesc,
                                                    &pCurrent, &spaceLeft);

            if (retcode == WLAN_STATUS_SUCCESS) {
                numScansDone++;
            }
        }
    }

    pRspInfo->scanNumber = numScansDone;
    retlen = pCurrent - (u8 *) wrq->u.data.pointer;

    wrq->u.data.length = retlen;

    /* Return retcode (EFAULT or E2BIG) in the case where no scan results were
     *   successfully encoded.
     */
    return (numScansDone ? WLAN_STATUS_SUCCESS : retcode);
#endif
}

/**
 *  @brief Update the scan entry TSF timestamps to reflect a new association
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param pNewBssDesc  A pointer to the newly associated AP's scan table entry
 *
 *  @return             void
 */
void
wlan_scan_update_tsf_timestamps(wlan_private * priv,
                                BSSDescriptor_t * pNewBssDesc)
{
    wlan_adapter *Adapter = priv->adapter;
    int tableIdx;
    u64 newTsfBase;
    s64 tsfDelta;

    memcpy(&newTsfBase, pNewBssDesc->TimeStamp, sizeof(newTsfBase));

    tsfDelta = newTsfBase - pNewBssDesc->networkTSF;

    wlan_debug3("TSF: Update TSF timestamps, 0x%016llx -> 0x%016llx\n",
           pNewBssDesc->networkTSF, newTsfBase);

    for (tableIdx = 0; tableIdx < Adapter->NumInScanTable; tableIdx++) {
        Adapter->ScanTable[tableIdx].networkTSF += tsfDelta;
    }
}

/**
 *  @brief Private IOCTL entry to perform an app configured immediate scan
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param wrq          A pointer to iwreq structure containing the
 *                      wlan_ioctl_user_scan_cfg requesting this scan
 *
 *  @return             0 if successful; IOCTL error code otherwise
 */
int
wlan_set_user_scan_ioctl(wlan_private * priv, void *wrq)
{
#if 0
    wlan_ioctl_user_scan_cfg scanReq;
    int retcode;
    union iwreq_data wrqu;

    if (memcpy(&scanReq,
                       wrq->u.data.pointer,
                       MIN(wrq->u.data.length, sizeof(scanReq))) != 0) {
        /* copy_from_user failed  */
        PRINTM(INFO, "SetUserScan: copy from user failed\n");
        retcode = -EFAULT;

    } else {
        retcode = wlan_scan_networks(priv, &scanReq);

        memset(&wrqu, 0x00, sizeof(union iwreq_data));
    }

    return retcode;
#endif
}

/**
 *  @brief Prepare a scan command to be sent to the firmware
 *
 *  Use the wlan_scan_cmd_config sent to the command processing module in
 *   the PrepareAndSendCommand to configure a HostCmd_DS_802_11_SCAN command
 *   struct to send to firmware.
 *
 *  The fixed fields specifying the BSS type and BSSID filters as well as a
 *   variable number/length of TLVs are sent in the command to firmware.
 *
 *  @param priv       A pointer to wlan_private structure
 *  @param cmd        A pointer to HostCmd_DS_COMMAND structure to be sent to
 *                    firmware with the HostCmd_DS_801_11_SCAN structure
 *  @param pdata_buf  Void pointer cast of a wlan_scan_cmd_config struct used
 *                    to set the fields/TLVs for the command sent to firmware
 *
 *  @return           WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 *
 *  @sa wlan_scan_create_channel_list
 */
int
wlan_cmd_802_11_scan(wlan_private * priv,
                     HostCmd_DS_COMMAND * cmd, void *pdata_buf)
{
    HostCmd_DS_802_11_SCAN *pScan = &cmd->params.scan;
    wlan_scan_cmd_config *pScanCfg;

    ENTER();

    pScanCfg = (wlan_scan_cmd_config *) pdata_buf;

    /* Set fixed field variables in scan command */
    pScan->BSSType = pScanCfg->bssType;
    memcpy(pScan->BSSID, pScanCfg->specificBSSID, sizeof(pScan->BSSID));
    memcpy(pScan->TlvBuffer, pScanCfg->tlvBuffer, pScanCfg->tlvBufferLen);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SCAN);

    /* Size is equal to the sizeof(fixed portions) + the TLV len + header */
    cmd->Size = wlan_cpu_to_le16(sizeof(pScan->BSSType)
                                 + sizeof(pScan->BSSID)
                                 + pScanCfg->tlvBufferLen + S_DS_GEN);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief Store a beacon or probe response for a BSS returned in the scan
 *  
 *  Store a new scan response or an update for a previous scan response.  New
 *    entries need to verify that they do not exceed the total amount of 
 *    memory allocated for the table.

 *  Replacement entries need to take into consideration the amount of space 
 *    currently allocated for the beacon/probe response and adjust the entry
 *    as needed.  
 *
 *  A small amount of extra pad (SCAN_BEACON_ENTRY_PAD) is generally reserved
 *    for an entry in case it is a beacon since a probe response for the
 *    network will by larger per the standard.  This helps to reduce the 
 *    amount of memory copying to fit a new probe response into an entry 
 *    already occupied by a network's previously stored beacon.
 *
 *  @param priv       A pointer to wlan_private structure
 *  @param beaconIdx  Index in the scan table to store this entry; may be
 *                    replacing an older duplicate entry for this BSS
 *  @param numInTable Number of entries currently in the table
 *  @param pNewBeacon Pointer to the new beacon/probe response to save
 *
 *  @return           void
 */
void
wlan_ret_802_11_scan_store_beacon(wlan_private * priv,
                                  int beaconIdx,
                                  int numInTable,
                                  BSSDescriptor_t * pNewBeacon)
{
    wlan_adapter *Adapter = priv->adapter;
    u8 *pBcnStore;
    int newBcnSize;
    int oldBcnSize;
    int bcnSpace;
    int adjIdx;

    if (Adapter->ScanTable[beaconIdx].pBeaconBuf != NULL) {

        newBcnSize = pNewBeacon->beaconBufSize;
        oldBcnSize = Adapter->ScanTable[beaconIdx].beaconBufSize;
        bcnSpace = Adapter->ScanTable[beaconIdx].beaconBufSizeMax;
        pBcnStore = Adapter->ScanTable[beaconIdx].pBeaconBuf;

        /* Set the max to be the same as current entry unless changed below */
        pNewBeacon->beaconBufSizeMax = bcnSpace;

        if (newBcnSize == oldBcnSize) {
            /*
             * Beacon is the same size as the previous entry.
             *   Replace the previous contents with the scan result
             */
            memcpy(pBcnStore,
                   pNewBeacon->pBeaconBuf, pNewBeacon->beaconBufSize);

        } else if (newBcnSize <= bcnSpace) {
            /*
             * New beacon size will fit in the amount of space
             *   we have previously allocated for it
             */

            /* Copy the new beacon buffer entry over the old one */
            memcpy(pBcnStore, pNewBeacon->pBeaconBuf, newBcnSize);

            /* If the old beacon size was less than the maximum
             *  we had alloted for the entry, and the new entry
             *  is even smaller, reset the max size to the old beacon
             *  entry and compress the storage space (leaving a new
             *  pad space of (oldBcnSize - newBcnSize).
             */
            if (oldBcnSize < bcnSpace && newBcnSize != bcnSpace) {
                /*
                 * Old Beacon size is smaller than the alloted storage size.
                 *   Shrink the alloted storage space.
                 */
                wlan_debug3( "AppControl: Smaller Duplicate Beacon (%d), "
                       "old = %d, new = %d, space = %d, left = %d\n",
                       beaconIdx, oldBcnSize, newBcnSize, bcnSpace,
                       (sizeof(Adapter->beaconBuffer) -
                        (Adapter->pBeaconBufEnd - Adapter->beaconBuffer)));

                /* memmove (since the memory overlaps) the data
                 *  after the beacon we just stored to the end of
                 *  the current beacon.  This cleans up any unused
                 *  space the old larger beacon was using in the buffer
                 */
                memmove(pBcnStore + oldBcnSize,
                        pBcnStore + bcnSpace,
                        Adapter->pBeaconBufEnd - (pBcnStore + bcnSpace));

                /* Decrement the end pointer by the difference between
                 *  the old larger size and the new smaller size since
                 *  we are using less space due to the new beacon being
                 *  smaller
                 */
                Adapter->pBeaconBufEnd -= (bcnSpace - oldBcnSize);

                /* Set the maximum storage size to the old beacon size */
                pNewBeacon->beaconBufSizeMax = oldBcnSize;

                /* Adjust beacon buffer pointers that are past the current */
                for (adjIdx = 0; adjIdx < numInTable; adjIdx++) {
                    if (Adapter->ScanTable[adjIdx].pBeaconBuf > pBcnStore) {
                        Adapter->ScanTable[adjIdx].pBeaconBuf
                            -= (bcnSpace - oldBcnSize);
                    }
                }
            }
        } else if (Adapter->pBeaconBufEnd + (newBcnSize - bcnSpace)
                   < (Adapter->beaconBuffer + sizeof(Adapter->beaconBuffer))) {
            /*
             * Beacon is larger than space previously allocated (bcnSpace)
             *   and there is enough space left in the beaconBuffer to store
             *   the additional data
             */
            wlan_debug3( "AppControl: Larger Duplicate Beacon (%d), "
                   "old = %d, new = %d, space = %d, left = %d\n",
                   beaconIdx, oldBcnSize, newBcnSize, bcnSpace,
                   (sizeof(Adapter->beaconBuffer) -
                    (Adapter->pBeaconBufEnd - Adapter->beaconBuffer)));

            /* memmove (since the memory overlaps) the data
             *  after the beacon we just stored to the end of
             *  the current beacon.  This moves the data for
             *  the beacons after this further in memory to
             *  make space for the new larger beacon we are
             *  about to copy in.
             */
            memmove(pBcnStore + newBcnSize,
                    pBcnStore + bcnSpace,
                    Adapter->pBeaconBufEnd - (pBcnStore + bcnSpace));

            /* Copy the new beacon buffer entry over the old one */
            memcpy(pBcnStore, pNewBeacon->pBeaconBuf, newBcnSize);

            /* Move the beacon end pointer by the amount of new
             *  beacon data we are adding
             */
            Adapter->pBeaconBufEnd += (newBcnSize - bcnSpace);

            /* This entry is bigger than the alloted max space
             *  previously reserved.  Increase the max space to
             *  be equal to the new beacon size
             */
            pNewBeacon->beaconBufSizeMax = newBcnSize;

            /* Adjust beacon buffer pointers that are past the current */
            for (adjIdx = 0; adjIdx < numInTable; adjIdx++) {
                if (Adapter->ScanTable[adjIdx].pBeaconBuf > pBcnStore) {
                    Adapter->ScanTable[adjIdx].pBeaconBuf
                        += (newBcnSize - bcnSpace);
                }
            }
        } else {
            /*
             * Beacon is larger than the previously allocated space, but
             *   there is not enough free space to store the additional data
             */
            wlan_debug3(
                   "AppControl: Failed: Larger Duplicate Beacon (%d),"
                   " old = %d, new = %d, space = %d, left = %d\n",
                   beaconIdx, oldBcnSize, newBcnSize, bcnSpace,
                   (sizeof(Adapter->beaconBuffer) -
                    (Adapter->pBeaconBufEnd - Adapter->beaconBuffer)));

            /* Storage failure, keep old beacon intact */
            pNewBeacon->beaconBufSize = oldBcnSize;
        }

        /* Point the new entry to its permanent storage space */
        pNewBeacon->pBeaconBuf = pBcnStore;

    } else {
        /* No existing beacon data exists for this entry, check to see
         *   if we can fit it in the remaining space
         */
        if (Adapter->pBeaconBufEnd + pNewBeacon->beaconBufSize +
            SCAN_BEACON_ENTRY_PAD < (Adapter->beaconBuffer +
                                     sizeof(Adapter->beaconBuffer))) {

            /* Copy the beacon buffer data from the local entry to the
             *   adapter dev struct buffer space used to store the raw
             *   beacon data for each entry in the scan table
             */
            memcpy(Adapter->pBeaconBufEnd, pNewBeacon->pBeaconBuf,
                   pNewBeacon->beaconBufSize);

            /* Update the beacon ptr to point to the table save area */
            pNewBeacon->pBeaconBuf = Adapter->pBeaconBufEnd;
            pNewBeacon->beaconBufSizeMax = (pNewBeacon->beaconBufSize
                                            + SCAN_BEACON_ENTRY_PAD);

            /* Increment the end pointer by the size reserved */
            Adapter->pBeaconBufEnd += pNewBeacon->beaconBufSizeMax;

            wlan_debug3("AppControl: Beacon[%02d] sz=%03d,"
                   " used = %04d, left = %04d\n",
                   beaconIdx,
                   pNewBeacon->beaconBufSize,
                   (Adapter->pBeaconBufEnd - Adapter->beaconBuffer),
                   (sizeof(Adapter->beaconBuffer) -
                    (Adapter->pBeaconBufEnd - Adapter->beaconBuffer)));
        } else {
            /*
             * No space for new beacon
             */
            wlan_debug3("AppControl: No space beacon (%d): "
                   "%02x:%02x:%02x:%02x:%02x:%02x; sz=%03d, left=%03d\n",
                   beaconIdx,
                   pNewBeacon->MacAddress[0], pNewBeacon->MacAddress[1],
                   pNewBeacon->MacAddress[2], pNewBeacon->MacAddress[3],
                   pNewBeacon->MacAddress[4], pNewBeacon->MacAddress[5],
                   pNewBeacon->beaconBufSize,
                   (sizeof(Adapter->beaconBuffer) -
                    (Adapter->pBeaconBufEnd - Adapter->beaconBuffer)));

            /* Storage failure; clear storage records for this bcn */
            pNewBeacon->pBeaconBuf = NULL;
            pNewBeacon->beaconBufSize = 0;
            pNewBeacon->beaconBufSizeMax = 0;
        }
    }
}

/**
 *  @brief This function handles the command response of scan
 *
 *   The response buffer for the scan command has the following
 *      memory layout:
 *
 *     .-----------------------------------------------------------.
 *     |  Header (4 * sizeof(u16)):  Standard command response hdr |
 *     .-----------------------------------------------------------.
 *     |  BufSize (u16) : sizeof the BSS Description data          |
 *     .-----------------------------------------------------------.
 *     |  NumOfSet (u8) : Number of BSS Descs returned             |
 *     .-----------------------------------------------------------.
 *     |  BSSDescription data (variable, size given in BufSize)    |
 *     .-----------------------------------------------------------.
 *     |  TLV data (variable, size calculated using Header->Size,  |
 *     |            BufSize and sizeof the fixed fields above)     |
 *     .-----------------------------------------------------------.
 *
 *  @param priv    A pointer to wlan_private structure
 *  @param resp    A pointer to HostCmd_DS_COMMAND
 *
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_ret_802_11_scan(wlan_private * priv, HostCmd_DS_COMMAND * resp)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_SCAN_RSP *pScan;
    BSSDescriptor_t newBssEntry;
    MrvlIEtypes_Data_t *pTlv;
    MrvlIEtypes_TsfTimestamp_t *pTsfTlv;
    u8 *pBssInfo;
    u16 scanRespSize;
    int bytesLeft;
    int numInTable;
    int bssIdx;
    int idx;
    int tlvBufSize;
    u64 tsfVal;
    BOOLEAN bgScanResp;

    ENTER();

    bgScanResp = (resp->Command == HostCmd_RET_802_11_BG_SCAN_QUERY);
    if (bgScanResp) {
        pScan = &resp->params.bgscanqueryresp.scanresp;
    } else {
        pScan = &resp->params.scanresp;
    }

    if (pScan->NumberOfSets > MRVDRV_MAX_BSSID_LIST) {
        wlan_debug3( "SCAN_RESP: Invalid number of AP returned (%d)!!\n",
               pScan->NumberOfSets);
        LEAVE();
        return WLAN_STATUS_FAILURE;
    }

    bytesLeft = wlan_le16_to_cpu(pScan->BSSDescriptSize);
    wlan_debug3("SCAN_RESP: BSSDescriptSize %d\n", bytesLeft);

    scanRespSize = resp->Size;

    wlan_debug3("SCAN_RESP: returned %d APs before parsing\n",
           pScan->NumberOfSets);

    numInTable = Adapter->NumInScanTable;
    pBssInfo = pScan->BssDescAndTlvBuffer;

    /* The size of the TLV buffer is equal to the entire command response
     *   size (scanRespSize) minus the fixed fields (sizeof()'s), the
     *   BSS Descriptions (BSSDescriptSize as bytesLef) and the command
     *   response header (S_DS_GEN)
     */
    tlvBufSize = scanRespSize - (bytesLeft + sizeof(pScan->BSSDescriptSize)
                                 + sizeof(pScan->NumberOfSets)
                                 + S_DS_GEN);

    pTlv = (MrvlIEtypes_Data_t *) (pScan->BssDescAndTlvBuffer + bytesLeft);

    /* Search the TLV buffer space in the scan response for any valid TLVs */
    wlan_ret_802_11_scan_get_tlv_ptrs(pTlv, tlvBufSize, &pTsfTlv);

    /*
     *  Process each scan response returned (pScan->NumberOfSets).  Save
     *    the information in the newBssEntry and then insert into the
     *    driver scan table either as an update to an existing entry
     *    or as an addition at the end of the table
     */
    for (idx = 0; idx < pScan->NumberOfSets && bytesLeft; idx++) {
        /* Zero out the newBssEntry we are about to store info in */
        memset(&newBssEntry, 0x00, sizeof(newBssEntry));

        /* Process the data fields and IEs returned for this BSS */
        if ((InterpretBSSDescriptionWithIE(&newBssEntry,
                                           &pBssInfo,
                                           &bytesLeft) == WLAN_STATUS_SUCCESS)
            && CHECK_SSID_IS_VALID(&newBssEntry.Ssid)) {

            wlan_debug3("SCAN_RESP: BSSID = %02x:%02x:%02x:%02x:%02x:%02x\n",
                   newBssEntry.MacAddress[0], newBssEntry.MacAddress[1],
                   newBssEntry.MacAddress[2], newBssEntry.MacAddress[3],
                   newBssEntry.MacAddress[4], newBssEntry.MacAddress[5]);

            /*
             * Search the scan table for the same bssid
             */
            for (bssIdx = 0; bssIdx < numInTable; bssIdx++) {
                if (memcmp(newBssEntry.MacAddress,
                           Adapter->ScanTable[bssIdx].MacAddress,
                           sizeof(newBssEntry.MacAddress)) == 0) {
                    /*
                     * If the SSID matches as well, it is a duplicate of
                     *   this entry.  Keep the bssIdx set to this
                     *   entry so we replace the old contents in the table
                     */
                    if ((newBssEntry.Ssid.SsidLength ==
                         Adapter->ScanTable[bssIdx].Ssid.SsidLength)
                        && (memcmp(newBssEntry.Ssid.Ssid,
                                   Adapter->ScanTable[bssIdx].Ssid.Ssid,
                                   newBssEntry.Ssid.SsidLength) == 0)) {
                        wlan_debug3("SCAN_RESP: Duplicate of index: %d\n",
                               bssIdx);
                        break;
                    }
                }
            }
            /*
             * If the bssIdx is equal to the number of entries in the table,
             *   the new entry was not a duplicate; append it to the scan
             *   table
             */
            if (bssIdx == numInTable) {
                /* Range check the bssIdx, keep it limited to the last entry */
                if (bssIdx == MRVDRV_MAX_BSSID_LIST) {
                    bssIdx--;
                } else {
                    numInTable++;
                }
            }

            /*
             * Save the beacon/probe response returned for later application
             *   retrieval.  Duplicate beacon/probe responses are updated if
             *   possible
             */
            wlan_ret_802_11_scan_store_beacon(priv,
                                              bssIdx,
                                              numInTable, &newBssEntry);
            /*
             * If the TSF TLV was appended to the scan results, save the
             *   this entries TSF value in the networkTSF field.  The
             *   networkTSF is the firmware's TSF value at the time the
             *   beacon or probe response was received.
             */
            if (pTsfTlv) {
                memcpy(&tsfVal, &pTsfTlv->tsfTable[idx], sizeof(tsfVal));
                tsfVal = wlan_le64_to_cpu(tsfVal);

                memcpy(&newBssEntry.networkTSF,
                       &tsfVal, sizeof(newBssEntry.networkTSF));
            }

            /* Copy the locally created newBssEntry to the scan table */
            memcpy(&Adapter->ScanTable[bssIdx],
                   &newBssEntry, sizeof(Adapter->ScanTable[bssIdx]));

        } else {

            /* Error parsing/interpreting the scan response, skipped */
            wlan_debug3("SCAN_RESP: "
                   "InterpretBSSDescriptionWithIE returned ERROR\n");
        }
    }

    wlan_debug3( "SCAN_RESP: Scanned %2d APs, %d valid, %d total\n",
           pScan->NumberOfSets, numInTable - Adapter->NumInScanTable,
           numInTable);

    /* Update the total number of BSSIDs in the scan table */
    Adapter->NumInScanTable = numInTable;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief scan network with specific ssid
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param req          A pointer to ifreq structure
 *
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
int wlan_extscan_ioctl(wlan_private * priv, void*req)
{
#if 0
    wlan_adapter *Adapter = priv->adapter;
    WLAN_802_11_SSID Ext_Scan_SSID;
    wlan_ioctl_user_scan_cfg scanCfg;
    union iwreq_data wrqu;

    ENTER();

    if (memcpy(&Ext_Scan_SSID, req->ifr_ifru.ifru_data, sizeof(Ext_Scan_SSID))) {
        PRINTM(INFO, "copy of SSID for ext scan from user failed \n");
        LEAVE();
        return -EFAULT;
    }
    memset(&scanCfg, 0x00, sizeof(scanCfg));

    memcpy(scanCfg.ssidList[0].ssid, Ext_Scan_SSID.Ssid,
           Ext_Scan_SSID.SsidLength);

    wlan_scan_networks(priv, &scanCfg);

    memset(&wrqu, 0, sizeof(union iwreq_data));

    if (Adapter->SurpriseRemoved)
        return WLAN_STATUS_FAILURE;

    LEAVE();
#endif
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function sends BG_SCAN query command to firmware.
 *
 *  @param priv    A pointer to wlan_private structure
 *
 *  @return        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sendBgScanQueryCmd(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    /* Clear the previous scan result */
    memset(Adapter->ScanTable, 0x00,
           sizeof(BSSDescriptor_t) * MRVDRV_MAX_BSSID_LIST);
    Adapter->NumInScanTable = 0;
    Adapter->pBeaconBufEnd = Adapter->beaconBuffer;

    return PrepareAndSendCommand(priv, HostCmd_CMD_802_11_BG_SCAN_QUERY,
                                 0, 0, 0, NULL);
}

/**
 *  @brief Enable/Disable BG Scan
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param enable       TRUE-enable, FALSE-disable
 *
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
int
wlan_bg_scan_enable(wlan_private * priv, BOOLEAN enable)
{
    int ret;

    ret = PrepareAndSendCommand(priv,
                                HostCmd_CMD_802_11_BG_SCAN_CONFIG,
                                0, HostCmd_OPTION_WAITFORRSP, 0, &enable);
    return ret;
}

/**
 *  @brief config BGSCAN parameter

 *  @param priv         A pointer to wlan_private structure
 *  @param req          A pointer to ifreq structure
 *
 *  @return             WLAN_STATUS_SUCCESS --success, otherwise fail
 */
 #if 0
int
wlan_do_bg_scan_config_ioctl(wlan_private * priv, struct ifreq *req)
{
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    u8 action;
    u8 *buf;

    ENTER();

//    action = *((u8 *) req->ifr_data + SKIP_CMDNUM + SKIP_SIZE);
//    PRINTM(INFO, "Action = %d\n", action);

    switch (action) {
    case HostCmd_ACT_GEN_GET:
        buf = (u8*)rt_malloc(Adapter->bgScanConfigSize + SKIP_SIZE);
        if (!buf) {
            PRINTM(MSG, "kmalloc no memory !!\n");
            return -ENOMEM;
        }
        rt_memcpy(buf, &Adapter->bgScanConfigSize, SKIP_SIZE);
        rt_memcpy(buf + SKIP_TYPE_SIZE, Adapter->bgScanConfig,
               Adapter->bgScanConfigSize);

        if (rt_memcpy(req->ifr_ifru.ifru_data, buf,
                         Adapter->bgScanConfigSize + SKIP_SIZE)) {
            PRINTM(INFO, "Copy to user failed\n");
            rt_free(buf);
            return -EFAULT;
        }

        rt_free(buf);

        break;
    case HostCmd_ACT_GEN_SET:
//        Adapter->bgScanConfigSize = *(u16 *) (req->ifr_ifru.ifru_data + SKIP_CMDNUM);
        PRINTM(INFO, "bgscanConfigSize = %d\n", Adapter->bgScanConfigSize);

        if (Adapter->bgScanConfig)
            rt_free(Adapter->bgScanConfig);

        if (!(Adapter->bgScanConfig =
              (HostCmd_DS_802_11_BG_SCAN_CONFIG *)rt_malloc(Adapter->bgScanConfigSize))) {
            PRINTM(MSG, "kmalloc no memory !!\n");
            Adapter->bgScanConfigSize = 0;
            return -ENOMEM;
        }

//        HEXDUMP("treq", req->ifr_data + SKIP_CMDNUM + SKIP_SIZE,
//                Adapter->bgScanConfigSize);

/*        if (memcpy(Adapter->bgScanConfig, req->ifr_ifru.ifru_data +
                           SKIP_CMDNUM + SKIP_SIZE,
                           Adapter->bgScanConfigSize)) {
            PRINTM(INFO, "Copy from user failed\n");
            return -EFAULT;
        }*/

        break;
    }

    LEAVE();

    return ret;
}
#endif
/**
 *  @brief This function prepares command of bg_scan_config.
 *
 *  @param priv         A pointer to wlan_private structure
 *  @param cmd          A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf    A pointer to data buffer
 *
 *  @return             WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_cmd_802_11_bg_scan_config(wlan_private * priv,
                               HostCmd_DS_COMMAND * cmd,
                               int cmd_action, void *pdata_buf)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_BG_SCAN_CONFIG *bgcfg = &cmd->params.bgscancfg;
    BOOLEAN enable = *((BOOLEAN *) pdata_buf);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_BG_SCAN_CONFIG);
    cmd->Size =
        wlan_cpu_to_le16((priv->adapter->bgScanConfigSize) + S_DS_GEN);

    Adapter->bgScanConfig->Enable = enable;

    memcpy(bgcfg, Adapter->bgScanConfig, Adapter->bgScanConfigSize);

    bgcfg->Action = wlan_cpu_to_le16(bgcfg->Action);
    bgcfg->ScanInterval = wlan_cpu_to_le32(bgcfg->ScanInterval);
    bgcfg->StoreCondition = wlan_cpu_to_le32(bgcfg->StoreCondition);
    bgcfg->ReportConditions = wlan_cpu_to_le32(bgcfg->ReportConditions);

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function prepares command of bg_scan_query.
 *
 *  @param priv     A pointer to wlan_private structure
 *  @param cmd      A pointer to HostCmd_DS_COMMAND structure
 *
 *  @return         WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_cmd_802_11_bg_scan_query(wlan_private * priv, HostCmd_DS_COMMAND * cmd)
{
    HostCmd_DS_802_11_BG_SCAN_QUERY *bgquery = &cmd->params.bgscanquery;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_BG_SCAN_QUERY);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_BG_SCAN_QUERY) + S_DS_GEN);

    bgquery->Flush = 1;

    return WLAN_STATUS_SUCCESS;
}
