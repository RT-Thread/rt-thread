/** @file wlan_cmd.c
  *  
  * @brief This file contains the handling of command.
  * it prepares command and sends it to firmware when
  * it is ready.
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
  * 
  */
/********************************************************
Change log:
    10/04/05: Add Doxygen format comments
    01/05/06: Add kernel 2.6.x support  
    01/11/06: Conditionalize new scan/join structures
    01/31/06: Add support to selectively enabe the FW Scan channel filter
    02/16/06: Clear scan in progress flag when scan command failed and dropped
    04/06/06: Add TSPEC, queue metrics, and MSDU expiry support
    04/18/06: Remove old Subscrive Event and add new Subscribe Event
              implementation through generic hostcmd API
    05/04/06: Add IBSS coalescing related new hostcmd handling	      
    08/29/06: Add ledgpio private command
********************************************************/

#include	"include.h"
#include	"wlan_defs.h"
int sbi_host_to_card(wlan_private * priv, u8 type, u8 * payload, u16 nb);
extern struct rt_semaphore driver_sem;
/********************************************************
		Local Variables
********************************************************/

static u16 Commands_Allowed_In_PS[] = {
    HostCmd_CMD_802_11_RSSI,
    HostCmd_CMD_802_11_HOST_SLEEP_CFG,
    HostCmd_CMD_802_11_WAKEUP_CONFIRM,
};

/********************************************************
		Global Variables
********************************************************/

/********************************************************
		Local Functions
********************************************************/

/** 
 *  @brief This function checks if the commans is allowed
 *  in PS mode not.
 *  
 *  @param Command the command ID
 *  @return 	   TRUE or FALSE
 */
static BOOLEAN
Is_Command_Allowed_In_PS(u16 Command)
{
    int count = sizeof(Commands_Allowed_In_PS)
        / sizeof(Commands_Allowed_In_PS[0]);
    int i;

    for (i = 0; i < count; i++) {
        if (Command == wlan_cpu_to_le16(Commands_Allowed_In_PS[i]))
            return TRUE;
    }

    return FALSE;
}

/** 
 *  @brief This function prepares command of get_hw_spec.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param cmd	   A pointer to HostCmd_DS_COMMAND structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_hw_spec(wlan_private * priv, HostCmd_DS_COMMAND * cmd)
{
    HostCmd_DS_GET_HW_SPEC *hwspec = &cmd->params.hwspec;

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_GET_HW_SPEC);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_GET_HW_SPEC) + S_DS_GEN);
    memcpy(hwspec->PermanentAddr, priv->adapter->CurrentAddr, ETH_ALEN);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of ps_mode.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action 	the action: GET or SET
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_ps_mode(wlan_private * priv,
                        HostCmd_DS_COMMAND * cmd, u16 cmd_action)
{
    HostCmd_DS_802_11_PS_MODE *psm = &cmd->params.psmode;
    u16 Action = cmd_action;
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_PS_MODE);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_PS_MODE) + S_DS_GEN);
    psm->Action = wlan_cpu_to_le16(cmd_action);
    psm->MultipleDtim = 0;
    switch (Action) {
    case HostCmd_SubCmd_Enter_PS:
        psm->LocalListenInterval =
            wlan_cpu_to_le16(Adapter->LocalListenInterval);
        psm->NullPktInterval = wlan_cpu_to_le16(Adapter->NullPktInterval);
        psm->MultipleDtim = wlan_cpu_to_le16(priv->adapter->MultipleDtim);
        psm->BCNMissTimeOut = wlan_cpu_to_le16(priv->adapter->BCNMissTimeOut);
        if (priv->adapter->InfrastructureMode == Wlan802_11IBSS)
            psm->AdhocAwakePeriod =
                wlan_cpu_to_le16(priv->adapter->AdhocAwakePeriod);
        break;

    case HostCmd_SubCmd_Exit_PS:
        wlan_debug3("PS Command:" "SubCode- Exit PS\n");
        break;

    case HostCmd_SubCmd_Sleep_Confirmed:
        wlan_debug3("PS Command: SubCode- sleep confirm\n");
        break;

    default:
        break;
    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of fw_wakeup_method.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action 	the action: GET or SET
 *  @param pdata_buf 	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_fw_wakeup_method(wlan_private * priv,
                                 HostCmd_DS_COMMAND * cmd,
                                 int cmd_action, void *pdata_buf)
{
    HostCmd_DS_802_11_FW_WAKEUP_METHOD *fwwm = &cmd->params.fwwakeupmethod;
    u16 action = (u16) cmd_action;
    u16 method = *((u16 *) pdata_buf);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_FW_WAKE_METHOD);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_FW_WAKEUP_METHOD) +
                         S_DS_GEN);
    fwwm->Action = wlan_cpu_to_le16(action);
    switch (action) {
    case HostCmd_ACT_SET:
        fwwm->Method = wlan_cpu_to_le16(method);
        break;
    case HostCmd_ACT_GET:
    default:
        fwwm->Method = 0;
        break;
    }

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function sends the HS_Activated event to the application
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_host_sleep_activated_event(wlan_private * priv)
{
    ENTER();
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of host_sleep_cfg.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param pdata_buf 	A pointer to HostCmd_DS_802_11_HOST_SLEEP_CFG structure
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_host_sleep_cfg(wlan_private * priv,
                               HostCmd_DS_COMMAND * cmd,
                               HostCmd_DS_802_11_HOST_SLEEP_CFG * pdata_buf)
{
    HostCmd_DS_802_11_HOST_SLEEP_CFG *phwuc = &cmd->params.hostsleepcfg;

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_HOST_SLEEP_CFG);
    if ((pdata_buf->conditions != HOST_SLEEP_CFG_CANCEL)
        && (priv->adapter->ArpFilterSize > 0)) {
        wlan_debug3("Attach %d bytes ArpFilter to HSCfg cmd\n",
              priv->adapter->ArpFilterSize);
        memcpy(((u8 *) phwuc) + sizeof(HostCmd_DS_802_11_HOST_SLEEP_CFG),
               priv->adapter->ArpFilter, priv->adapter->ArpFilterSize);
        cmd->Size =
            wlan_cpu_to_le16(priv->adapter->ArpFilterSize +
                             sizeof(HostCmd_DS_802_11_HOST_SLEEP_CFG) +
                             S_DS_GEN);
    } else
        cmd->Size =
            wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_HOST_SLEEP_CFG) +
                             S_DS_GEN);
    phwuc->conditions = wlan_cpu_to_le32(pdata_buf->conditions);
    phwuc->gpio = pdata_buf->gpio;
    phwuc->gap = pdata_buf->gap;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of inactivity_timeout.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   Action: GET SET
 *  @param pdata_buf 	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_inactivity_timeout(wlan_private * priv,
                                   HostCmd_DS_COMMAND * cmd,
                                   u16 cmd_action, void *pdata_buf)
{
    u16 *timeout = (u16 *) pdata_buf;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_INACTIVITY_TIMEOUT);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_INACTIVITY_TIMEOUT) +
                         S_DS_GEN);

    cmd->params.inactivity_timeout.Action = wlan_cpu_to_le16(cmd_action);

    if (cmd_action)
        cmd->params.inactivity_timeout.Timeout = wlan_cpu_to_le16(*timeout);
    else
        cmd->params.inactivity_timeout.Timeout = 0;

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of sleep_period.
 *  
 *  @param priv    		A pointer to wlan_private structure
 *  @param cmd	   		A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action 		the action: GET or SET
 *  @param pdata_buf		A pointer to data buffer
 *  @return 	   		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_sleep_period(wlan_private * priv,
                             HostCmd_DS_COMMAND * cmd,
                             u16 cmd_action, void *pdata_buf)
{
    HostCmd_DS_802_11_SLEEP_PERIOD *pSleepPeriod = &cmd->params.ps_sleeppd;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SLEEP_PERIOD);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_SLEEP_PERIOD) +
                                 S_DS_GEN);
    memmove(pSleepPeriod, pdata_buf, sizeof(HostCmd_DS_802_11_SLEEP_PERIOD));
    pSleepPeriod->Action = wlan_cpu_to_le16(pSleepPeriod->Action);
    pSleepPeriod->Period = wlan_cpu_to_le16(pSleepPeriod->Period);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of wlan_cmd_802_11_crypto
 *    
 *  @param priv    		A pointer to wlan_private structure
 *  @param cmd	   		A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action 		the action: GET or SET
 *  @param pdata_buf		A pointer to data buffer
 *  @return 	   		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_crypto(wlan_private * priv,
                       HostCmd_DS_COMMAND * cmd,
                       u16 cmd_action, void *pdata_buf)
{

    HostCmd_DS_802_11_CRYPTO *crypto = (HostCmd_DS_802_11_CRYPTO *) pdata_buf;
    MrvlIEtypes_Data_t *data =
        (MrvlIEtypes_Data_t *) ((u8 *) pdata_buf +
                                sizeof(HostCmd_DS_802_11_CRYPTO));
    int len;

    if (data->Header.Type != TLV_TYPE_CRYPTO_DATA)
        return WLAN_STATUS_FAILURE;
    switch (crypto->Algorithm) {
    case CIPHER_TEST_RC4:
        if (((crypto->KeyIVLength + crypto->KeyLength) > 256) ||
            ((crypto->KeyIVLength + crypto->KeyLength) == 0))
            return WLAN_STATUS_FAILURE;
        break;
    case CIPHER_TEST_AES:
        if ((crypto->KeyLength != 16) && (crypto->KeyLength != 24) &&
            (crypto->KeyLength != 32))
            return WLAN_STATUS_FAILURE;
        break;
    case CIPHER_TEST_AES_KEY_WRAP:
        if (crypto->KeyIVLength != 8)
            return FALSE;
        if ((crypto->KeyLength != 16) && (crypto->KeyLength != 24) &&
            (crypto->KeyLength != 32))
            return WLAN_STATUS_FAILURE;
        if (data->Header.Len % 8)
            return WLAN_STATUS_FAILURE;
        break;
    default:
        return WLAN_STATUS_FAILURE;

    }
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_CRYPTO);

    len = data->Header.Len;
    data->Header.Type = wlan_cpu_to_le16(data->Header.Type);
    data->Header.Len = wlan_cpu_to_le16(data->Header.Len);

    crypto->EncDec = wlan_cpu_to_le16(crypto->EncDec);
    crypto->Algorithm = wlan_cpu_to_le16(crypto->Algorithm);
    crypto->KeyIVLength = wlan_cpu_to_le16(crypto->KeyIVLength);
    crypto->KeyLength = wlan_cpu_to_le16(crypto->KeyLength);

    memmove(&cmd->params.crypto, pdata_buf, sizeof(HostCmd_DS_802_11_CRYPTO) +
            len + sizeof(MrvlIEtypesHeader_t));

    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_CRYPTO) + S_DS_GEN +
                                 len + sizeof(MrvlIEtypesHeader_t));
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of sleep_params.
 *  
 *  @param priv    		A pointer to wlan_private structure
 *  @param cmd	   		A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action 		the action: GET or SET
 *  @return 	   		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_sleep_params(wlan_private * priv,
                             HostCmd_DS_COMMAND * cmd, u16 cmd_action)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_SLEEP_PARAMS *sp = &cmd->params.sleep_params;

    ENTER();

    cmd->Size = wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_SLEEP_PARAMS)) +
                                 S_DS_GEN);
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SLEEP_PARAMS);

    if (cmd_action == HostCmd_ACT_GEN_GET) {
        memset(&Adapter->sp, 0, sizeof(SleepParams));
        memset(sp, 0, sizeof(HostCmd_DS_802_11_SLEEP_PARAMS));
        sp->Action = wlan_cpu_to_le16(cmd_action);
    } else if (cmd_action == HostCmd_ACT_GEN_SET) {
        sp->Action = wlan_cpu_to_le16(cmd_action);
        sp->Error = wlan_cpu_to_le16(Adapter->sp.sp_error);
        sp->Offset = wlan_cpu_to_le16(Adapter->sp.sp_offset);
        sp->StableTime = wlan_cpu_to_le16(Adapter->sp.sp_stabletime);
        sp->CalControl = (u8) Adapter->sp.sp_calcontrol;
        sp->ExternalSleepClk = (u8) Adapter->sp.sp_extsleepclk;
        sp->Reserved = wlan_cpu_to_le16(Adapter->sp.sp_reserved);
    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

#define WEP_40_BIT_LEN	5
#define WEP_104_BIT_LEN	13

/** 
 *  @brief This function prepares command of set_wep.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_oid   OID: ADD_WEP KEY or REMOVE_WEP KEY
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_set_wep(wlan_private * priv,
                        HostCmd_DS_COMMAND * cmd, u32 cmd_oid)
{
    HostCmd_DS_802_11_SET_WEP *wep = &cmd->params.wep;
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;

    ENTER();

    if (cmd_oid == OID_802_11_ADD_WEP) {
        cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SET_WEP);
        cmd->Size =
            wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_SET_WEP)) + S_DS_GEN);
        wep->Action = wlan_cpu_to_le16(HostCmd_ACT_ADD);

        /* default tx key index */
        wep->KeyIndex = wlan_cpu_to_le16(Adapter->CurrentWepKeyIndex &
                                         HostCmd_WEP_KEY_INDEX_MASK);

        wlan_debug3("Tx Key Index: %u\n", wep->KeyIndex);

        switch (Adapter->WepKey[0].KeyLength) {
        case WEP_40_BIT_LEN:
            wep->WEPTypeForKey1 = HostCmd_TYPE_WEP_40_BIT;
            memmove(wep->WEP1, Adapter->WepKey[0].KeyMaterial,
                    Adapter->WepKey[0].KeyLength);
            break;
        case WEP_104_BIT_LEN:
            wep->WEPTypeForKey1 = HostCmd_TYPE_WEP_104_BIT;
            memmove(wep->WEP1, Adapter->WepKey[0].KeyMaterial,
                    Adapter->WepKey[0].KeyLength);
            break;
        case 0:
            break;
        default:
            wlan_debug3( "Key1 Length = %d \n",
                   Adapter->WepKey[0].KeyLength);
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }

        switch (Adapter->WepKey[1].KeyLength) {
        case WEP_40_BIT_LEN:
            wep->WEPTypeForKey2 = HostCmd_TYPE_WEP_40_BIT;
            memmove(wep->WEP2, Adapter->WepKey[1].KeyMaterial,
                    Adapter->WepKey[1].KeyLength);
            break;
        case WEP_104_BIT_LEN:
            wep->WEPTypeForKey2 = HostCmd_TYPE_WEP_104_BIT;
            memmove(wep->WEP2, Adapter->WepKey[1].KeyMaterial,
                    Adapter->WepKey[1].KeyLength);
            break;
        case 0:
            break;
        default:
            wlan_debug3("Key2 Length = %d \n",
                   Adapter->WepKey[1].KeyLength);
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }

        switch (Adapter->WepKey[2].KeyLength) {
        case WEP_40_BIT_LEN:
            wep->WEPTypeForKey3 = HostCmd_TYPE_WEP_40_BIT;
            memmove(wep->WEP3, Adapter->WepKey[2].KeyMaterial,
                    Adapter->WepKey[2].KeyLength);
            break;
        case WEP_104_BIT_LEN:
            wep->WEPTypeForKey3 = HostCmd_TYPE_WEP_104_BIT;
            memmove(wep->WEP3, Adapter->WepKey[2].KeyMaterial,
                    Adapter->WepKey[2].KeyLength);
            break;
        case 0:
            break;
        default:
            wlan_debug3( "Key3 Length = %d \n",
                   Adapter->WepKey[2].KeyLength);
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }

        switch (Adapter->WepKey[3].KeyLength) {
        case WEP_40_BIT_LEN:
            wep->WEPTypeForKey4 = HostCmd_TYPE_WEP_40_BIT;
            memmove(wep->WEP4, Adapter->WepKey[3].KeyMaterial,
                    Adapter->WepKey[3].KeyLength);
            break;
        case WEP_104_BIT_LEN:
            wep->WEPTypeForKey4 = HostCmd_TYPE_WEP_104_BIT;
            memmove(wep->WEP4, Adapter->WepKey[3].KeyMaterial,
                    Adapter->WepKey[3].KeyLength);
            break;
        case 0:
            break;
        default:
            wlan_debug3( "Key4 Length = %d \n",
                   Adapter->WepKey[3].KeyLength);
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
    } else if (cmd_oid == OID_802_11_REMOVE_WEP) {
        cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_SET_WEP);
        cmd->Size =
            wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_SET_WEP)) + S_DS_GEN);
        wep->Action = wlan_cpu_to_le16(HostCmd_ACT_REMOVE);

        /* default tx key index */
        wep->KeyIndex = wlan_cpu_to_le16((u16) (Adapter->CurrentWepKeyIndex &
                                                (u32)
                                                HostCmd_WEP_KEY_INDEX_MASK));
    }

    ret = WLAN_STATUS_SUCCESS;
  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function prepares command of key_material.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action 	the action: GET or SET
 *  @param cmd_oid	OID: ENABLE or DISABLE
 *  @param pdata_buf    A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_key_material(wlan_private * priv,
                             HostCmd_DS_COMMAND * cmd,
                             u16 cmd_action,
                             WLAN_OID cmd_oid, void *pdata_buf)
{
    HostCmd_DS_802_11_KEY_MATERIAL *pKeyMaterial = &cmd->params.keymaterial;
    WLAN_802_11_KEY *pKey = (WLAN_802_11_KEY *) pdata_buf;
    u16 KeyParamSet_len;
    int ret = WLAN_STATUS_SUCCESS;

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_KEY_MATERIAL);
    pKeyMaterial->Action = wlan_cpu_to_le16(cmd_action);

    if (cmd_action == HostCmd_ACT_GET) {
        cmd->Size = wlan_cpu_to_le16(2 + S_DS_GEN);
        ret = WLAN_STATUS_SUCCESS;
        goto done;
    }

    memset(&pKeyMaterial->KeyParamSet, 0, sizeof(MrvlIEtype_KeyParamSet_t));

    if (pKey->KeyLength == WPA_AES_KEY_LEN) {
       wlan_debug3( "WPA_AES\n");
        pKeyMaterial->KeyParamSet.KeyTypeId =
            wlan_cpu_to_le16(KEY_TYPE_ID_AES);

        if (cmd_oid == (WLAN_OID) KEY_INFO_ENABLED)
            pKeyMaterial->KeyParamSet.KeyInfo =
                wlan_cpu_to_le16(KEY_INFO_AES_ENABLED);
        else
            pKeyMaterial->KeyParamSet.KeyInfo =
                !(wlan_cpu_to_le16(KEY_INFO_AES_ENABLED));

        if (pKey->KeyIndex & 0x40000000)        //AES pairwise key: unicast
            pKeyMaterial->KeyParamSet.KeyInfo |=
                wlan_cpu_to_le16(KEY_INFO_AES_UNICAST);
        else                    //AES group key: multicast
            pKeyMaterial->KeyParamSet.KeyInfo |=
                wlan_cpu_to_le16(KEY_INFO_AES_MCAST);
    } else if (pKey->KeyLength == WPA_TKIP_KEY_LEN) {
  //      PRINTM(INFO, "WPA_TKIP\n");
        pKeyMaterial->KeyParamSet.KeyTypeId =
            wlan_cpu_to_le16(KEY_TYPE_ID_TKIP);
        pKeyMaterial->KeyParamSet.KeyInfo =
            wlan_cpu_to_le16(KEY_INFO_TKIP_ENABLED);

        if (pKey->KeyIndex & 0x40000000)        //TKIP pairwise key: unicast
            pKeyMaterial->KeyParamSet.KeyInfo |=
                wlan_cpu_to_le16(KEY_INFO_TKIP_UNICAST);
        else                    //TKIP group key: multicast
            pKeyMaterial->KeyParamSet.KeyInfo |=
                wlan_cpu_to_le16(KEY_INFO_TKIP_MCAST);
    }

    if (pKeyMaterial->KeyParamSet.KeyTypeId) {
        pKeyMaterial->KeyParamSet.Type =
            wlan_cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
        pKeyMaterial->KeyParamSet.KeyLen = wlan_cpu_to_le16(pKey->KeyLength);
        memcpy(pKeyMaterial->KeyParamSet.Key,
               pKey->KeyMaterial, pKey->KeyLength);
        pKeyMaterial->KeyParamSet.Length =
            wlan_cpu_to_le16(pKey->KeyLength + 6);

#define TYPE_LEN_FIELDS_LEN 4
        KeyParamSet_len = (pKey->KeyLength + 6) + TYPE_LEN_FIELDS_LEN;
#define ACTION_FIELD_LEN 2
        cmd->Size =
            wlan_cpu_to_le16(KeyParamSet_len + ACTION_FIELD_LEN + S_DS_GEN);
    }

    ret = WLAN_STATUS_SUCCESS;
  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function prepares command of get_log.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_get_log(wlan_private * priv, HostCmd_DS_COMMAND * cmd)
{
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_GET_LOG);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_GET_LOG) + S_DS_GEN);

    return WLAN_STATUS_SUCCESS;
}


/** 
 *  @brief This function prepares command of radio_control.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_radio_control(wlan_private * priv,
                              HostCmd_DS_COMMAND * cmd, int cmd_action)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_RADIO_CONTROL *pRadioControl = &cmd->params.radio;

    ENTER();

    cmd->Size = wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_RADIO_CONTROL))
                                 + S_DS_GEN);
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RADIO_CONTROL);

    pRadioControl->Action = wlan_cpu_to_le16(cmd_action);
    pRadioControl->Control = wlan_cpu_to_le16(Adapter->RadioOn);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of bca_timeshare.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param user_bca_ts	A pointer to HostCmd_DS_802_11_BCA_TIMESHARE structure
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_bca_timeshare(wlan_private * priv,
                              HostCmd_DS_COMMAND * cmd,
                              u16 cmd_action,
                              HostCmd_DS_802_11_BCA_TIMESHARE * user_bca_ts)
{
    wlan_adapter *Adapter = priv->adapter;
    HostCmd_DS_802_11_BCA_TIMESHARE *bca_ts = &cmd->params.bca_timeshare;

    ENTER();

    cmd->Size = wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_BCA_TIMESHARE)) +
                                 S_DS_GEN);
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_BCA_CONFIG_TIMESHARE);

    if (cmd_action == HostCmd_ACT_GEN_GET) {
        memset(&Adapter->bca_ts, 0, sizeof(bca_ts));
        memset(bca_ts, 0, sizeof(HostCmd_DS_802_11_BCA_TIMESHARE));
        bca_ts->Action = wlan_cpu_to_le16(cmd_action);
        bca_ts->TrafficType = wlan_cpu_to_le16(user_bca_ts->TrafficType);
    } else if (cmd_action == HostCmd_ACT_GEN_SET) {
        bca_ts->Action = wlan_cpu_to_le16(cmd_action);
        bca_ts->TrafficType = wlan_cpu_to_le16(user_bca_ts->TrafficType);
        bca_ts->TimeShareInterval =
            wlan_cpu_to_le32(user_bca_ts->TimeShareInterval);
        bca_ts->BTTime = wlan_cpu_to_le32(user_bca_ts->BTTime);
    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of rf_tx_power.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_rf_tx_power(wlan_private * priv,
                            HostCmd_DS_COMMAND * cmd,
                            u16 cmd_action, void *pdata_buf)
{

    HostCmd_DS_802_11_RF_TX_POWER *pRTP = &cmd->params.txp;

    ENTER();

    cmd->Size =
        wlan_cpu_to_le16((sizeof(HostCmd_DS_802_11_RF_TX_POWER)) + S_DS_GEN);
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RF_TX_POWER);
    pRTP->Action = cmd_action;

    wlan_debug3 ("RF_TX_POWER_CMD: Size:%d Cmd:0x%x Act:%d\n", cmd->Size,
           cmd->Command, pRTP->Action);

    switch (cmd_action) {
    case HostCmd_ACT_GEN_GET:
        pRTP->Action = wlan_cpu_to_le16(HostCmd_ACT_GEN_GET);
        pRTP->CurrentLevel = 0;
        break;

    case HostCmd_ACT_GEN_SET:
        pRTP->Action = wlan_cpu_to_le16(HostCmd_ACT_GEN_SET);
        pRTP->CurrentLevel = wlan_cpu_to_le16(*((u16 *) pdata_buf));
        break;
    }
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of rf_antenna.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_rf_antenna(wlan_private * priv,
                           HostCmd_DS_COMMAND * cmd,
                           u16 cmd_action, void *pdata_buf)
{
    HostCmd_DS_802_11_RF_ANTENNA *rant = &cmd->params.rant;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RF_ANTENNA);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_RF_ANTENNA) + S_DS_GEN);

    rant->Action = wlan_cpu_to_le16(cmd_action);
    if ((cmd_action == HostCmd_ACT_SET_RX) ||
        (cmd_action == HostCmd_ACT_SET_TX)) {
        rant->AntennaMode =
            wlan_cpu_to_le16((u16) (*(WLAN_802_11_ANTENNA *) pdata_buf));
    }

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of rate_adapt_rateset.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_rate_adapt_rateset(wlan_private * priv,
                                   HostCmd_DS_COMMAND * cmd, u16 cmd_action)
{
    HostCmd_DS_802_11_RATE_ADAPT_RATESET * rateadapt = &cmd->params.rateset;
    wlan_adapter *Adapter = priv->adapter;

    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_RATE_ADAPT_RATESET) +
                         S_DS_GEN);
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RATE_ADAPT_RATESET);

    ENTER();

    rateadapt->Action = wlan_cpu_to_le16(cmd_action);
    rateadapt->HWRateDropMode = wlan_cpu_to_le16(Adapter->HWRateDropMode);
    rateadapt->Threshold = wlan_cpu_to_le16(Adapter->Threshold);
    rateadapt->FinalRate = wlan_cpu_to_le16(Adapter->FinalRate);
    rateadapt->Bitmap = wlan_cpu_to_le16(Adapter->RateBitmap);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of mac_multicast_adr.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_mac_multicast_adr(wlan_private * priv,
                           HostCmd_DS_COMMAND * cmd, u16 cmd_action)
{
    HostCmd_DS_MAC_MULTICAST_ADR *pMCastAdr = &cmd->params.madr;
    wlan_adapter *Adapter = priv->adapter;

    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_MAC_MULTICAST_ADR) + S_DS_GEN);
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_MAC_MULTICAST_ADR);

    pMCastAdr->Action = wlan_cpu_to_le16(cmd_action);
    pMCastAdr->NumOfAdrs =
        wlan_cpu_to_le16((u16) Adapter->NumOfMulticastMACAddr);
    memcpy(pMCastAdr->MACList, Adapter->MulticastList,
           Adapter->NumOfMulticastMACAddr * ETH_ALEN);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of rf_channel.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_rf_channel(wlan_private * priv,
                           HostCmd_DS_COMMAND * cmd,
                           int option, void *pdata_buf)
{
    HostCmd_DS_802_11_RF_CHANNEL *rfchan = &cmd->params.rfchannel;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RF_CHANNEL);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_RF_CHANNEL)
                                 + S_DS_GEN);

    if (option == HostCmd_OPT_802_11_RF_CHANNEL_SET) {
        rfchan->CurrentChannel = wlan_cpu_to_le16(*((u16 *) pdata_buf));
    }

    rfchan->Action = wlan_cpu_to_le16(option);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of rssi.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_rssi(wlan_private * priv, HostCmd_DS_COMMAND * cmd)
{
    wlan_adapter *Adapter = priv->adapter;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_RSSI);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_RSSI) + S_DS_GEN);
    cmd->params.rssi.N = wlan_cpu_to_le16(Adapter->bcn_avg_factor);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of reg_access.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_reg_access(wlan_private * priv,
                    HostCmd_DS_COMMAND * CmdPtr,
                    u8 cmd_action, void *pdata_buf)
{
    wlan_offset_value *offval;

    ENTER();

    offval = (wlan_offset_value *) pdata_buf;

    switch (CmdPtr->Command) {
    case HostCmd_CMD_MAC_REG_ACCESS:
        {
            HostCmd_DS_MAC_REG_ACCESS *macreg;

            CmdPtr->Size =
                wlan_cpu_to_le16(sizeof(HostCmd_DS_MAC_REG_ACCESS) +
                                 S_DS_GEN);
            macreg = (HostCmd_DS_MAC_REG_ACCESS *) & CmdPtr->params.macreg;

            macreg->Action = wlan_cpu_to_le16(cmd_action);
            macreg->Offset = wlan_cpu_to_le16((u16) offval->offset);
            macreg->Value = wlan_cpu_to_le32(offval->value);

            break;
        }

    case HostCmd_CMD_BBP_REG_ACCESS:
        {
            HostCmd_DS_BBP_REG_ACCESS *bbpreg;

            CmdPtr->Size =
                wlan_cpu_to_le16(sizeof(HostCmd_DS_BBP_REG_ACCESS) +
                                 S_DS_GEN);
            bbpreg = (HostCmd_DS_BBP_REG_ACCESS *) & CmdPtr->params.bbpreg;

            bbpreg->Action = wlan_cpu_to_le16(cmd_action);
            bbpreg->Offset = wlan_cpu_to_le16((u16) offval->offset);
            bbpreg->Value = (u8) offval->value;

            break;
        }

    case HostCmd_CMD_RF_REG_ACCESS:
        {
            HostCmd_DS_RF_REG_ACCESS *rfreg;

            CmdPtr->Size =
                wlan_cpu_to_le16(sizeof(HostCmd_DS_RF_REG_ACCESS) + S_DS_GEN);
            rfreg = (HostCmd_DS_RF_REG_ACCESS *) & CmdPtr->params.rfreg;

            rfreg->Action = wlan_cpu_to_le16(cmd_action);
            rfreg->Offset = wlan_cpu_to_le16((u16) offval->offset);
            rfreg->Value = (u8) offval->value;

            break;
        }

    default:
        break;
    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of mac_address.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_mac_address(wlan_private * priv,
                            HostCmd_DS_COMMAND * cmd, u16 cmd_action)
{
    wlan_adapter *Adapter = priv->adapter;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_MAC_ADDRESS);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_MAC_ADDRESS) +
                                 S_DS_GEN);
    cmd->Result = 0;

    cmd->params.macadd.Action = wlan_cpu_to_le16(cmd_action);

    if (cmd_action == HostCmd_ACT_SET) {
        memcpy(cmd->params.macadd.MacAdd, Adapter->CurrentAddr, ETH_ALEN);
//        HEXDUMP("SET_CMD: MAC ADDRESS-", Adapter->CurrentAddr, 6);
    }

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of cal_data_ext.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param pdata_buf	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_cal_data_ext(wlan_private * priv,
                             HostCmd_DS_COMMAND * cmd, void *pdata_buf)
{
    HostCmd_DS_802_11_CAL_DATA_EXT *PCalDataext = pdata_buf;

    HostCmd_DS_802_11_CAL_DATA_EXT *pCmdCalData =
        (HostCmd_DS_802_11_CAL_DATA_EXT *) & cmd->params.caldataext;

    ENTER();
    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_CAL_DATA_EXT);

wlan_debug3("CalDataLen = %d(d)\n", PCalDataext->CalDataLen);

#define MAX_ALLOWED_LEN	1024
    if (PCalDataext->CalDataLen > MAX_ALLOWED_LEN) {
        wlan_debug2("CAL_DATA_EXT: Cal data lenght too large!\n");
        return WLAN_STATUS_FAILURE;
    }
#define ACTION_REV_CALDATA_LEN_FIELDS_LEN 6
    memcpy(pCmdCalData, PCalDataext,
           PCalDataext->CalDataLen + ACTION_REV_CALDATA_LEN_FIELDS_LEN);

    pCmdCalData->Action = wlan_cpu_to_le16(pCmdCalData->Action);
    pCmdCalData->Revision = wlan_cpu_to_le16(pCmdCalData->Revision);
    pCmdCalData->CalDataLen = wlan_cpu_to_le16(pCmdCalData->CalDataLen);

    cmd->Size = wlan_cpu_to_le16(PCalDataext->CalDataLen +
                                 ACTION_REV_CALDATA_LEN_FIELDS_LEN +
                                 S_DS_GEN);

    wlan_debug3("CAL_DATA_EXT: cmd->Size = %d(d)\n", cmd->Size);

    cmd->Result = 0;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of eeprom_access.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @param pdata_buf	A pointer to data buffer
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_802_11_eeprom_access(wlan_private * priv,
                              HostCmd_DS_COMMAND * cmd,
                              int cmd_action, void *pdata_buf)
{
    wlan_ioctl_regrdwr *ea = pdata_buf;

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_EEPROM_ACCESS);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_EEPROM_ACCESS) + S_DS_GEN);
    cmd->Result = 0;

    cmd->params.rdeeprom.Action = wlan_cpu_to_le16(ea->Action);
    cmd->params.rdeeprom.Offset = wlan_cpu_to_le16(ea->Offset);
    cmd->params.rdeeprom.ByteCount = wlan_cpu_to_le16(ea->NOB);
    cmd->params.rdeeprom.Value = 0;

    return WLAN_STATUS_SUCCESS;
}

static int
wlan_cmd_802_11_IBSS_Coalesced_Status(wlan_private * priv,
                                      HostCmd_DS_COMMAND * cmd,
                                      int cmd_action, void *pdata_buf)
{
    HostCmd_DS_802_11_IBSS_Status *pIBSSReq = &(cmd->params.ibssCoalescing);
    u16 *enable = pdata_buf;

    wlan_debug3("HostCmd_CMD_802_11_BSSID_QUERY request");

    cmd->Command =
        wlan_cpu_to_le16(HostCmd_CMD_802_11_IBSS_COALESCING_STATUS);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_IBSS_Status) + S_DS_GEN);
    cmd->Result = 0;
    pIBSSReq->Action = wlan_cpu_to_le16(cmd_action);

    switch (cmd_action) {
    case HostCmd_ACT_SET:
        pIBSSReq->Enable = wlan_cpu_to_le16(*enable);
        break;

        /* In other case.. Noting to do */
    case HostCmd_ACT_GET:
    default:
        break;
    }
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function prepares command of eeprom_access.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd	   	A pointer to HostCmd_DS_COMMAND structure
 *  @param cmd_action   the action: GET or SET
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_gspi_bus_config(wlan_private * priv,
                         HostCmd_DS_COMMAND * cmd,
                         u16 cmd_action, void *pdata_buf)
{
    HostCmd_DS_CMD_GSPI_BUS_CONFIG *pCmdGspiConfig =
        (HostCmd_DS_CMD_GSPI_BUS_CONFIG *) & cmd->params.gspicfg;
    HostCmd_DS_CMD_GSPI_BUS_CONFIG *pbus_config =
        (HostCmd_DS_CMD_GSPI_BUS_CONFIG *) pdata_buf;

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_GSPI_BUS_CONFIG);
    cmd->Size =
        wlan_cpu_to_le16(sizeof(HostCmd_DS_CMD_GSPI_BUS_CONFIG) + S_DS_GEN);
    cmd->Result = 0;

    pCmdGspiConfig->Action = wlan_cpu_to_le16(cmd_action);
    pCmdGspiConfig->BusDelayMode =
        wlan_cpu_to_le16(pbus_config->BusDelayMode);
    pCmdGspiConfig->HostTimeDelayToReadPort =
        wlan_cpu_to_le16(pbus_config->HostTimeDelayToReadPort);
    pCmdGspiConfig->HostTimeDelayToReadregister =
        wlan_cpu_to_le16(pbus_config->HostTimeDelayToReadregister);

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function queues the command to cmd list.
 *  
 *  @param Adapter	A pointer to wlan_adapter structure
 *  @param CmdNode   	A pointer to CmdCtrlNode structure
 *  @param addtail	specify if the cmd needs to be queued in the header or tail
 *  @return 	   	n/a
 */
void
QueueCmd(wlan_adapter * Adapter, CmdCtrlNode * CmdNode, BOOLEAN addtail)
{
 
    HostCmd_DS_COMMAND *CmdPtr;
    u16 command;
	rt_base_t level;
    ENTER();

    if (!CmdNode) {
		wlan_debug1("QUEUE_CMD: CmdNode is NULL\n");
        goto done;
    }

    CmdPtr = (HostCmd_DS_COMMAND *) CmdNode->BufVirtualAddr;
    if (!CmdPtr) {
		wlan_debug1("QUEUE_CMD: CmdPtr is NULL\n");
        goto done;
    }

    command = wlan_le16_to_cpu(CmdPtr->Command);

    /* Exit_PS command needs to be queued in the header always. */
    if (command == HostCmd_CMD_802_11_PS_MODE) {
        HostCmd_DS_802_11_PS_MODE *psm = &CmdPtr->params.psmode;
        if (wlan_le16_to_cpu(psm->Action) == HostCmd_SubCmd_Exit_PS) {
            if (Adapter->PSState != PS_STATE_FULL_POWER)
                addtail = FALSE;
        }
    }

    if ((command == HostCmd_CMD_802_11_WAKEUP_CONFIRM)) {
        addtail = FALSE;
    }


	
	/* disable interrupt */
	level = rt_hw_interrupt_disable();

    if (addtail)
        list_add_tail((struct list_head *) CmdNode, &Adapter->CmdPendingQ);
    else
        list_add((struct list_head *) CmdNode, &Adapter->CmdPendingQ);
	rt_hw_interrupt_enable(level);
    wlan_debug3("QUEUE_CMD: cmd=0x%x is queued\n", command);

  done:
    LEAVE();
    return;
}

#ifdef MFG_CMD_SUPPORT
/** 
 *  @brief This function sends general command to firmware.
 *  
 *  @param priv     	A pointer to wlan_private structure
 *  @param cmd      	A pointer to HostCmd_DS_COMMAND structure
 *  @param pdata_buf	A pointer to data buffer
 *  @return         	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_mfg_cmd(wlan_private * priv,
                 HostCmd_DS_COMMAND * cmd, void *pdata_buf)
{
    HostCmd_DS_GEN *pCmdPtr;

    ENTER();

    pCmdPtr = (HostCmd_DS_GEN *) pdata_buf;

    /* copy the MFG command to command buffer */
    memcpy((void *) cmd, pdata_buf, pCmdPtr->Size);

    wlan_debug3( "MFG command size = %d\n", pCmdPtr->Size);

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_MFG_COMMAND);
    cmd->Size = wlan_cpu_to_le16(cmd->Size);
    cmd->Result = 0;

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}
#endif

/** 
 *  @brief This function downloads the command to firmware.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param CmdNode   	A pointer to CmdCtrlNode structure
 *  @return 	   	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
DownloadCommandToStation(wlan_private * priv, CmdCtrlNode * CmdNode)
{

    HostCmd_DS_COMMAND *CmdPtr;
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    u16 CmdSize;
    u16 Command;
	rt_base_t level;

    ENTER();

    if (!Adapter || !CmdNode) {
        wlan_debug1 ("DNLD_CMD: Adapter = %#x, CmdNode = %#x\n",(int) Adapter, (int) CmdNode);
        if (CmdNode)
            CleanupAndInsertCmd(priv, CmdNode);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    CmdPtr = (HostCmd_DS_COMMAND *) CmdNode->BufVirtualAddr;

    if (!CmdPtr || !CmdPtr->Size) {
        wlan_debug1("DNLD_CMD: CmdPtr is Null or Cmd Size is Zero, "
               "Not sending\n");
        CleanupAndInsertCmd(priv, CmdNode);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }


    level = rt_hw_interrupt_disable();
    Adapter->CurCmd = CmdNode;
    rt_hw_interrupt_enable(level);

    Adapter->CurCmdRetCode = 0;

    Command = wlan_cpu_to_le16(CmdPtr->Command);
    CmdSize = wlan_cpu_to_le16(CmdPtr->Size);

    ret = sbi_host_to_card(priv, MVMS_CMD, (u8 *) CmdPtr, CmdSize);

    /* clear TxDone interrupt bit */
    rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
    Adapter->HisRegCpy &= ~HIS_TxDnLdRdy;
     rt_sem_release(&driver_sem);

    if (ret != 0) {
        wlan_debug1("DNLD_CMD: Host to Card Failed\n");
        /* set error code that will be transferred back to PrepareAndSendCommand() */
        Adapter->CurCmdRetCode = WLAN_STATUS_FAILURE;
        CleanupAndInsertCmd(priv, Adapter->CurCmd);

	level = rt_hw_interrupt_disable();
       Adapter->CurCmd = NULL;
	rt_hw_interrupt_enable(level);

        Adapter->dbg.num_cmd_host_to_card_failure++;
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    Adapter->dbg.LastCmdId = Command;

    if (Command == HostCmd_CMD_802_11_PS_MODE) {
        HostCmd_DS_802_11_PS_MODE *psmode = &CmdPtr->params.psmode;
        wlan_debug3("DNLD_CMD: 0x%x, act 0x%x, len %d, seqno %d\n",
              Command, wlan_cpu_to_le16(psmode->Action), CmdSize,
              wlan_le16_to_cpu(CmdPtr->SeqNum));
    } else {
        wlan_debug3("DNLD_CMD: 0x%x, len %d, seqno %d\n",
               Command, CmdSize, wlan_le16_to_cpu(CmdPtr->SeqNum));
    }
    wlan_debug3("DNLD_CMD", CmdNode->BufVirtualAddr, CmdSize);

    /* Setup the timer after transmit command */
    if (Command == HostCmd_CMD_802_11_SCAN
        || Command == HostCmd_CMD_802_11_DEAUTHENTICATE
        || Command == HostCmd_CMD_802_11_ASSOCIATE
        || Command == HostCmd_CMD_WMM_ADDTS_REQ) {
        ModTimer(&Adapter->MrvDrvCommandTimer, MRVDRV_TIMER_10S);
    } else {
        ModTimer(&Adapter->MrvDrvCommandTimer, MRVDRV_TIMER_5S);
    }

    Adapter->CommandTimerIsSet = TRUE;

    if (Command == HostCmd_CMD_802_11_DEEP_SLEEP) {
        if (Adapter->IntCounter || Adapter->CurrentTxSkb)
           wlan_debug2("DNLD_CMD: DS- IntCnt=%d CurTxSkb=%s\n",
                   Adapter->IntCounter, (Adapter->CurrentTxSkb) ? "Y" : "N");

        if (Adapter->IntCounter) {
            rt_sem_take(&driver_sem, RT_WAITING_FOREVER);
            Adapter->IntCounterSaved = Adapter->IntCounter;
            Adapter->IntCounter = 0;
            rt_sem_release(&driver_sem);
        }
        if (Adapter->CurrentTxSkb) {

            rt_sem_release(&driver_sem);
            Adapter->CurrentTxSkb = NULL;
            rt_sem_release(&driver_sem);
            priv->stats.tx_dropped++;
        }
        /* 1. change the PS state to DEEP_SLEEP
         * 2. since there is no response for this command, so 
         *    delete the command timer and free the Node. */

        Adapter->IsDeepSleep = TRUE;

        CleanupAndInsertCmd(priv, CmdNode);
	 level = rt_hw_interrupt_disable();
        Adapter->CurCmd = NULL;
	 rt_hw_interrupt_enable(level);

        if (Adapter->CommandTimerIsSet) {
            CancelTimer(&Adapter->MrvDrvCommandTimer);
            Adapter->CommandTimerIsSet = FALSE;
        }

        if (Adapter->bHostSleepConfigured) {
            Adapter->bWakeupDevRequired = TRUE;
            wlan_host_sleep_activated_event(priv);
        }

    }

    ret = WLAN_STATUS_SUCCESS;

  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function prepares command of mac_control.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd		A pointer to HostCmd_DS_COMMAND structure
 *  @return 		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_cmd_mac_control(wlan_private * priv,
                     HostCmd_DS_COMMAND * cmd, void *InfoBuf)
{
    HostCmd_DS_MAC_CONTROL *mac = &cmd->params.macctrl;
    u16 Action = *((u16 *) InfoBuf);

    ENTER();

    cmd->Command = wlan_cpu_to_le16(HostCmd_CMD_MAC_CONTROL);
    cmd->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_MAC_CONTROL) + S_DS_GEN);
    mac->Action = wlan_cpu_to_le16(Action);

    wlan_debug3("wlan_cmd_mac_control(): Action=0x%X Size=%d\n",
           mac->Action, cmd->Size);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/********************************************************
		Global Functions
********************************************************/

/** 
 *  @brief This function inserts command node to CmdFreeQ
 *  after cleans it.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param pTempCmd	A pointer to CmdCtrlNode structure
 *  @return 		n/a
 */
void
CleanupAndInsertCmd(wlan_private * priv, CmdCtrlNode * pTempCmd)
{
   
    wlan_adapter *Adapter = priv->adapter;
	rt_base_t level;
    ENTER();

    if (!pTempCmd)
        goto done;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();
    CleanUpCmdCtrlNode(pTempCmd);
    list_add_tail((struct list_head *) pTempCmd, &Adapter->CmdFreeQ);
	rt_hw_interrupt_enable(level);

  done:
    LEAVE();
}
void CleanUpCmdCtrlNodeNoSetEvent(CmdCtrlNode * pTempNode);
void
CleanupAndInsertCmdNoSetEvent(wlan_private * priv, CmdCtrlNode * pTempCmd)
{
  
    wlan_adapter *Adapter = priv->adapter;
	rt_base_t level;
    ENTER();

    if (!pTempCmd)
        goto done;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();
  //  CleanUpCmdCtrlNode(pTempCmd);
    list_add_tail((struct list_head *) pTempCmd, &Adapter->CmdFreeQ);
	rt_hw_interrupt_enable(level);
	CleanUpCmdCtrlNodeNoSetEvent(pTempCmd);
		 
  done:
    LEAVE();
}
/** 
 *  @brief This function prepare the command before send to firmware.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param cmd_no	command number
 *  @param cmd_action	command action: GET or SET
 *  @param wait_option	wait option: wait response or not
 *  @param cmd_oid	cmd oid: treated as sub command
 *  @param pdata_buf	A pointer to informaion buffer
 *  @return 		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
PrepareAndSendCommand(wlan_private * priv,
                      u16 cmd_no,
                      u16 cmd_action,
                      u16 wait_option, WLAN_OID cmd_oid, void *pdata_buf)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_adapter *Adapter = priv->adapter;
    CmdCtrlNode *CmdNode;
    HostCmd_DS_COMMAND *CmdPtr;
	rt_uint32_t e;
    ENTER();

    if (!Adapter) {
        wlan_debug1 ( "PREP_CMD: Adapter is Null\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    if (Adapter->SurpriseRemoved) {
        wlan_debug1 ("PREP_CMD: Card is Removed\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    CmdNode = GetFreeCmdCtrlNode(priv);

    if (CmdNode == NULL) {
        wlan_debug2 ("PREP_CMD: No free CmdNode\n");

        /* Wake up main thread to execute next command */
		rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    SetCmdCtrlNode(priv, CmdNode, cmd_oid, wait_option, pdata_buf);

    CmdPtr = (HostCmd_DS_COMMAND *) CmdNode->BufVirtualAddr;

    if (!CmdPtr) {
        wlan_debug2 ( "PREP_CMD: BufVirtualAddr of CmdNode is NULL\n");
        CleanupAndInsertCmd(priv, CmdNode);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    /* Set sequence number, command and INT option */
    Adapter->SeqNum++;
    CmdPtr->SeqNum = wlan_cpu_to_le16(Adapter->SeqNum);

    CmdPtr->Command = cmd_no;
    CmdPtr->Result = 0;

   // TX_EVENT_FLAGS_SET(&CmdNode->cmdwait_q, 0, TX_AND);	  no valid
    switch (cmd_no) {
    case HostCmd_CMD_GET_HW_SPEC:
        ret = wlan_cmd_hw_spec(priv, CmdPtr);
        break;
    case HostCmd_CMD_802_11_PS_MODE:
        ret = wlan_cmd_802_11_ps_mode(priv, CmdPtr, cmd_action);
        break;

    case HostCmd_CMD_802_11_SCAN:
        ret = wlan_cmd_802_11_scan(priv, CmdPtr, pdata_buf);
        break;

    case HostCmd_CMD_MAC_CONTROL:
        ret = wlan_cmd_mac_control(priv, CmdPtr, pdata_buf);
        break;

    case HostCmd_CMD_802_11_ASSOCIATE:
        ret = wlan_cmd_802_11_associate(priv, CmdPtr, pdata_buf);
        break;

    case HostCmd_CMD_802_11_DEAUTHENTICATE:
        ret = wlan_cmd_802_11_deauthenticate(priv, CmdPtr);
        break;

    case HostCmd_CMD_802_11_SET_WEP:
        ret = wlan_cmd_802_11_set_wep(priv, CmdPtr, cmd_oid);
        break;

    case HostCmd_CMD_802_11_RESET:
        CmdPtr->Command = wlan_cpu_to_le16(cmd_no);
        CmdPtr->Size = wlan_cpu_to_le16(S_DS_GEN);
        break;

    case HostCmd_CMD_802_11_GET_LOG:
        ret = wlan_cmd_802_11_get_log(priv, CmdPtr);
        break;

    case HostCmd_CMD_MAC_REG_ACCESS:
    case HostCmd_CMD_BBP_REG_ACCESS:
    case HostCmd_CMD_RF_REG_ACCESS:
        ret = wlan_cmd_reg_access(priv, CmdPtr, cmd_action, pdata_buf);
        break;

    case HostCmd_CMD_802_11_RF_CHANNEL:
        ret = wlan_cmd_802_11_rf_channel(priv, CmdPtr, cmd_action, pdata_buf);
        break;

    case HostCmd_CMD_802_11_RF_TX_POWER:
        ret = wlan_cmd_802_11_rf_tx_power(priv, CmdPtr,
                                          cmd_action, pdata_buf);
        break;

    case HostCmd_CMD_802_11_RADIO_CONTROL:
        ret = wlan_cmd_802_11_radio_control(priv, CmdPtr, cmd_action);
        break;

    case HostCmd_CMD_802_11_RF_ANTENNA:
        ret = wlan_cmd_802_11_rf_antenna(priv, CmdPtr, cmd_action, pdata_buf);
        break;

    case HostCmd_CMD_802_11_RATE_ADAPT_RATESET:
        ret = wlan_cmd_802_11_rate_adapt_rateset(priv, CmdPtr, cmd_action);
        break;

    case HostCmd_CMD_MAC_MULTICAST_ADR:
        ret = wlan_cmd_mac_multicast_adr(priv, CmdPtr, cmd_action);
        break;

    case HostCmd_CMD_802_11_RSSI:
        ret = wlan_cmd_802_11_rssi(priv, CmdPtr);
        break;

    case HostCmd_CMD_802_11_KEY_MATERIAL:
        ret = wlan_cmd_802_11_key_material(priv, CmdPtr,
                                           cmd_action, cmd_oid, pdata_buf);
        break;

    case HostCmd_CMD_802_11_MAC_ADDRESS:
        ret = wlan_cmd_802_11_mac_address(priv, CmdPtr, cmd_action);
        break;
    case HostCmd_CMD_802_11_CAL_DATA_EXT:
        ret = wlan_cmd_802_11_cal_data_ext(priv, CmdPtr, pdata_buf);
        break;

    case HostCmd_CMD_802_11_DEEP_SLEEP:
        CmdPtr->Command = wlan_cpu_to_le16(cmd_no);
        CmdPtr->Size = wlan_cpu_to_le16((u16)
                                        (sizeof
                                         (HostCmd_DS_802_11_DEEP_SLEEP)));
        break;

    case HostCmd_CMD_802_11_HOST_SLEEP_CFG:
        ret = wlan_cmd_802_11_host_sleep_cfg(priv, CmdPtr, pdata_buf);
        break;
    case HostCmd_CMD_802_11_WAKEUP_CONFIRM:
        CmdPtr->Command = wlan_cpu_to_le16(cmd_no);
        CmdPtr->Size = wlan_cpu_to_le16(S_DS_GEN);
        break;

    case HostCmd_CMD_802_11_EEPROM_ACCESS:
        ret = wlan_cmd_802_11_eeprom_access(priv, CmdPtr,
                                            cmd_action, pdata_buf);
        break;
    case HostCmd_CMD_GSPI_BUS_CONFIG:
        ret = wlan_cmd_gspi_bus_config(priv, CmdPtr, cmd_action, pdata_buf);
        break;

#ifdef MFG_CMD_SUPPORT
    case HostCmd_CMD_MFG_COMMAND:
        ret = wlan_cmd_mfg_cmd(priv, CmdPtr, pdata_buf);
        break;
#endif

    case HostCmd_CMD_802_11D_DOMAIN_INFO:
        ret = wlan_cmd_802_11d_domain_info(priv, CmdPtr, cmd_no, cmd_action);
        break;

    case HostCmd_CMD_802_11_SLEEP_PARAMS:
        ret = wlan_cmd_802_11_sleep_params(priv, CmdPtr, cmd_action);
        break;
    case HostCmd_CMD_802_11_BCA_CONFIG_TIMESHARE:
        ret = wlan_cmd_802_11_bca_timeshare(priv, CmdPtr,
                                            cmd_action, pdata_buf);
        break;
    case HostCmd_CMD_802_11_INACTIVITY_TIMEOUT:
        ret = wlan_cmd_802_11_inactivity_timeout(priv, CmdPtr,
                                                 cmd_action, pdata_buf);
        break;
    case HostCmd_CMD_802_11_BG_SCAN_CONFIG:
        ret = wlan_cmd_802_11_bg_scan_config(priv, CmdPtr,
                                             cmd_action, pdata_buf);
        break;

    case HostCmd_CMD_802_11_BG_SCAN_QUERY:
        ret = wlan_cmd_802_11_bg_scan_query(priv, CmdPtr);
        break;

    case HostCmd_CMD_802_11_FW_WAKE_METHOD:
        ret = wlan_cmd_802_11_fw_wakeup_method(priv, CmdPtr,
                                               cmd_action, pdata_buf);
        break;

    case HostCmd_CMD_WMM_GET_STATUS:
        ret = wlan_cmd_wmm_get_status(priv, CmdPtr, pdata_buf);
        break;

    case HostCmd_CMD_WMM_ADDTS_REQ:
        ret = wlan_cmd_wmm_addts_req(priv, CmdPtr, pdata_buf);
        break;
    case HostCmd_CMD_WMM_DELTS_REQ:
        ret = wlan_cmd_wmm_delts_req(priv, CmdPtr, pdata_buf);
        break;
    case HostCmd_CMD_WMM_QUEUE_CONFIG:
        ret = wlan_cmd_wmm_queue_config(priv, CmdPtr, pdata_buf);
        break;
    case HostCmd_CMD_WMM_QUEUE_STATS:
        ret = wlan_cmd_wmm_queue_stats(priv, CmdPtr, pdata_buf);
        break;
    case HostCmd_CMD_TX_PKT_STATS:
        CmdPtr->Command = wlan_cpu_to_le16(HostCmd_CMD_TX_PKT_STATS);
        CmdPtr->Size = wlan_cpu_to_le16(S_DS_GEN);
        ret = WLAN_STATUS_SUCCESS;
        break;
    case HostCmd_CMD_802_11_TPC_CFG:
        CmdPtr->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_TPC_CFG);
        CmdPtr->Size =
            wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_TPC_CFG) + S_DS_GEN);

        memmove(&CmdPtr->params.tpccfg,
                pdata_buf, sizeof(HostCmd_DS_802_11_TPC_CFG));
        CmdPtr->params.tpccfg.Action =
            wlan_cpu_to_le16(CmdPtr->params.tpccfg.Action);

        ret = WLAN_STATUS_SUCCESS;
        break;
    case HostCmd_CMD_802_11_LED_CONTROL:
        {
            HostCmd_DS_802_11_LED_CTRL *pLedCtrl = &CmdPtr->params.ledgpio;
            MrvlIEtypes_LedGpio_t *gpio = &pLedCtrl->LedGpio;
            MrvlIEtypes_LedBehavior_t *pLedBehavior = pLedCtrl->LedBehavior;

            memmove(&CmdPtr->params.ledgpio,
                    pdata_buf, sizeof(HostCmd_DS_802_11_LED_CTRL));

            CmdPtr->Command =
                wlan_cpu_to_le16(HostCmd_CMD_802_11_LED_CONTROL);

#define ACTION_NUMLED_TLVTYPE_LEN_FIELDS_LEN 8
            CmdPtr->Size = wlan_cpu_to_le16(gpio->Header.Len + S_DS_GEN
                                            +
                                            ACTION_NUMLED_TLVTYPE_LEN_FIELDS_LEN);

            pLedCtrl->Action = wlan_cpu_to_le16(pLedCtrl->Action);
            pLedCtrl->LedNums = wlan_cpu_to_le16(pLedCtrl->LedNums);

            gpio->Header.Type = wlan_cpu_to_le16(gpio->Header.Type);
            gpio->Header.Len = wlan_cpu_to_le16(gpio->Header.Len);

            pLedBehavior->Header.Type =
                wlan_cpu_to_le16(pLedBehavior->Header.Type);
            pLedBehavior->Header.Len =
                wlan_cpu_to_le16(pLedBehavior->Header.Len);

            ret = WLAN_STATUS_SUCCESS;
            break;
        }
    case HostCmd_CMD_802_11_SLEEP_PERIOD:
        ret = wlan_cmd_802_11_sleep_period(priv, CmdPtr,
                                           cmd_action, pdata_buf);
        break;
    case HostCmd_CMD_802_11_CRYPTO:
        ret = wlan_cmd_802_11_crypto(priv, CmdPtr, cmd_action, pdata_buf);
        break;
    case HostCmd_CMD_GET_TSF:
        CmdPtr->Command = wlan_cpu_to_le16(HostCmd_CMD_GET_TSF);
        CmdPtr->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_GET_TSF)
                                        + S_DS_GEN);
        ret = WLAN_STATUS_SUCCESS;
        break;
    case HostCmd_CMD_802_11_TX_RATE_QUERY:
        CmdPtr->Command = wlan_cpu_to_le16(HostCmd_CMD_802_11_TX_RATE_QUERY);
        CmdPtr->Size =
            wlan_cpu_to_le16(sizeof(HostCmd_TX_RATE_QUERY) + S_DS_GEN);
        Adapter->TxRate = 0;
        ret = WLAN_STATUS_SUCCESS;
        break;
    case HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
        ret =
            wlan_cmd_802_11_IBSS_Coalesced_Status(priv, CmdPtr, cmd_action,
                                                  pdata_buf);
        break;

    case HostCmd_CMD_802_11_LDO_CONFIG:
        CmdPtr->Command = wlan_cpu_to_le16(cmd_no);
        CmdPtr->Size =
            wlan_cpu_to_le16(sizeof(HostCmd_DS_802_11_LDO_CONFIG) + S_DS_GEN);
        memcpy(&CmdPtr->params.ldocfg, pdata_buf,
               sizeof(HostCmd_DS_802_11_LDO_CONFIG));
        CmdPtr->params.ldocfg.Action =
            wlan_cpu_to_le16(CmdPtr->params.ldocfg.Action);
        CmdPtr->params.ldocfg.PMSource =
            wlan_cpu_to_le16(CmdPtr->params.ldocfg.PMSource);
        break;

    case HostCmd_CMD_VERSION_EXT:
        CmdPtr->Command = wlan_cpu_to_le16(cmd_no);
        memcpy(&CmdPtr->params, pdata_buf, sizeof(HostCmd_DS_VERSION_EXT));
        CmdPtr->Size = wlan_cpu_to_le16(sizeof(HostCmd_DS_VERSION_EXT)
                                        + S_DS_GEN);
        break;

    default:
        wlan_debug2 ("PREP_CMD: unknown command- %#x\n", cmd_no);
        ret = WLAN_STATUS_FAILURE;
        break;
    }

    /* return error, since the command preparation failed */
    if (ret != WLAN_STATUS_SUCCESS) {
        wlan_debug2("PREP_CMD: Command 0x%x preparation failed\n", cmd_no);
        CleanupAndInsertCmd(priv, CmdNode);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    wlan_debug3("PREP_CMD: 0x%x\n", cmd_no);


    QueueCmd(Adapter, CmdNode, TRUE);
    rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);

    if (wait_option & HostCmd_OPTION_WAITFORRSP) {
        wlan_debug2("PREP_CMD: Wait for CMD response...\n");

	rt_event_recv(&CmdNode->cmdwait,CmdWaitQWoken,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER, &e);
       if (Adapter->CurCmdRetCode) {
       wlan_debug2("PREP_CMD: Command failed with return code=%d\n",
                   Adapter->CurCmdRetCode);
            Adapter->CurCmdRetCode = 0;
            ret = WLAN_STATUS_FAILURE;
        }
    }

  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function allocates the command buffer and link
 *  it to command free queue.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @return 		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
AllocateCmdBuffer(wlan_private * priv)
{
    int ret = WLAN_STATUS_SUCCESS;
    u32 ulBufSize;
    u32 i;
    CmdCtrlNode *TempCmdArray=RT_NULL;
    u8 *pTempVirtualAddr;
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    /* Allocate and initialize CmdCtrlNode */
    ulBufSize = sizeof(CmdCtrlNode) * MRVDRV_NUM_OF_CMD_BUFFER;
	TempCmdArray =(CmdCtrlNode *) rt_malloc(ulBufSize);
    if (!(TempCmdArray)) {
        wlan_debug1("ALLOC_CMD_BUF: Failed to allocate TempCmdArray\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    Adapter->CmdArray = TempCmdArray;
    memset(Adapter->CmdArray, 0, ulBufSize);

    /* Allocate and initialize command buffers */
    ulBufSize = MRVDRV_SIZE_OF_CMD_BUFFER;
    for (i = 0; i < MRVDRV_NUM_OF_CMD_BUFFER; i++) {
		pTempVirtualAddr =(u8 *) rt_malloc(ulBufSize);
        if (!pTempVirtualAddr) {
            rt_kprintf("ALLOC_CMD_BUF: pTempVirtualAddr: out of memory\n");
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }

        memset(pTempVirtualAddr, 0, ulBufSize);

        /* Update command buffer virtual */
        TempCmdArray[i].BufVirtualAddr = pTempVirtualAddr;
    }

    for (i = 0; i < MRVDRV_NUM_OF_CMD_BUFFER; i++) {
        //init_waitqueue_head(&TempCmdArray[i].cmdwait_q);
		rt_event_init(&TempCmdArray[i].cmdwait, "cmdwaitevent", RT_IPC_FLAG_FIFO);
        //CleanupAndInsertCmd(priv, &TempCmdArray[i]);
		CleanupAndInsertCmdNoSetEvent(priv, &TempCmdArray[i]);
    }

    ret = WLAN_STATUS_SUCCESS;
  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function frees the command buffer.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @return 		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
FreeCmdBuffer(wlan_private * priv)
{

    unsigned int i;
    CmdCtrlNode *TempCmdArray;
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    /* need to check if cmd array is allocated or not */
    if (Adapter->CmdArray == NULL) {
        wlan_debug2("FREE_CMD_BUF: CmdArray is Null\n");
        goto done;
    }

    TempCmdArray = Adapter->CmdArray;

    /* Release shared memory buffers */

    for (i = 0; i < MRVDRV_NUM_OF_CMD_BUFFER; i++) {
        if (TempCmdArray[i].BufVirtualAddr) {
            wlan_debug3("Free all the array\n");
            rt_free(TempCmdArray[i].BufVirtualAddr);
            TempCmdArray[i].BufVirtualAddr = NULL;
        }
    }

    /* Release CmdCtrlNode */
    if (Adapter->CmdArray) {
        wlan_debug3("Free CmdArray\n");
        rt_free(Adapter->CmdArray);
        Adapter->CmdArray = NULL;
    }

  done:
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}
void CleanUpCmdCtrlNodeNoSetEvent(CmdCtrlNode * pTempNode);
/** 
 *  @brief This function gets a free command node if available in
 *  command free queue.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @return CmdCtrlNode A pointer to CmdCtrlNode structure or NULL
 */
CmdCtrlNode *
GetFreeCmdCtrlNode(wlan_private * priv)
{
    CmdCtrlNode *TempNode;
    wlan_adapter *Adapter = priv->adapter;

	rt_base_t level;
    ENTER();

    if (!Adapter)
        return NULL;

	level = rt_hw_interrupt_disable();

    if (!list_empty(&Adapter->CmdFreeQ)) {
        TempNode = (CmdCtrlNode *) Adapter->CmdFreeQ.next;
        list_del((struct list_head *) TempNode);
    } else {
        wlan_debug3("GET_CMD_NODE: CmdCtrlNode is not available\n");
        TempNode = NULL;
    }


   rt_hw_interrupt_enable(level);

    if (TempNode) {
	CleanUpCmdCtrlNodeNoSetEvent(TempNode);	  //modified by dennis
    }

    LEAVE();
    return TempNode;
}

/** 
 *  @brief This function cleans command node.
 *  
 *  @param pTempNode	A pointer to CmdCtrlNode structure
 *  @return 		n/a
 */
void
CleanUpCmdCtrlNode(CmdCtrlNode * pTempNode)
{
    ENTER();

    if (!pTempNode)
        return;
//    pTempNode->CmdWaitQWoken = TRUE;
//    wake_up_interruptible(&pTempNode->cmdwait_q);
	/*here there is a query: when get a free cmd node  this function will also be invoked,
	but it is not reasionable to set a flag to cmdwait events*/
	rt_event_send(&pTempNode->cmdwait, CmdWaitQWoken);

    pTempNode->Status = 0;									   
    pTempNode->cmd_oid = (WLAN_OID) 0;
    pTempNode->wait_option = 0;
    pTempNode->CmdFlags = 0;
    pTempNode->pdata_buf = NULL;

    if (pTempNode->BufVirtualAddr != NULL)
        memset(pTempNode->BufVirtualAddr, 0, MRVDRV_SIZE_OF_CMD_BUFFER);

    LEAVE();
    return;
}
void CleanUpCmdCtrlNodeNoSetEvent(CmdCtrlNode * pTempNode)
{
    ENTER();

    if (!pTempNode)
        return;

	/*here there is a query: when get a free cmd node  this function will also be invoked,
	but it is not reasionable to set a flag to cmdwait events*/
//	rt_event_send(&pTempNode->cmdwait, CmdWaitQWoken);

    pTempNode->Status = 0;									   
    pTempNode->cmd_oid = (WLAN_OID) 0;
    pTempNode->wait_option = 0;
    pTempNode->CmdFlags = 0;
    pTempNode->pdata_buf = NULL;

    if (pTempNode->BufVirtualAddr != NULL)
        memset(pTempNode->BufVirtualAddr, 0, MRVDRV_SIZE_OF_CMD_BUFFER);

    LEAVE();
    return;
}
/** 
 *  @brief This function initializes the command node.
 *  
 *  @param priv		A pointer to wlan_private structure
 *  @param pTempNode	A pointer to CmdCtrlNode structure
 *  @param cmd_oid	cmd oid: treated as sub command
 *  @param wait_option	wait option: wait response or not
 *  @param pdata_buf	A pointer to informaion buffer
 *  @return 		WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
void
SetCmdCtrlNode(wlan_private * priv,
               CmdCtrlNode * pTempNode,
               WLAN_OID cmd_oid, u16 wait_option, void *pdata_buf)
{
    ENTER();

    if (!pTempNode)
        return;

    pTempNode->cmd_oid = cmd_oid;
    pTempNode->wait_option = wait_option;
    pTempNode->pdata_buf = pdata_buf;

    LEAVE();
}

/** 
 *  @brief This function executes next command in command
 *  pending queue. It will put fimware back to PS mode
 *  if applicable.
 *  
 *  @param priv     A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
ExecuteNextCommand(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    CmdCtrlNode *CmdNode = NULL;
    HostCmd_DS_COMMAND *CmdPtr;
  
    int ret = WLAN_STATUS_SUCCESS;
	rt_base_t level;
    ENTER();

    if (!Adapter) {
        wlan_debug1 ("EXEC_NEXT_CMD: Adapter is NULL\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

	level = rt_hw_interrupt_disable();

    if (Adapter->CurCmd) {
        wlan_debug1 ("EXEC_NEXT_CMD: there is command in processing!\n");
        rt_hw_interrupt_enable(level);
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }

    if (!list_empty(&Adapter->CmdPendingQ)) {
        CmdNode = (CmdCtrlNode *)
            Adapter->CmdPendingQ.next;
    }

	rt_hw_interrupt_enable(level);

    if (CmdNode) {
        CmdPtr = (HostCmd_DS_COMMAND *) CmdNode->BufVirtualAddr;

        if (Is_Command_Allowed_In_PS(CmdPtr->Command)) {
            if ((Adapter->PSState == PS_STATE_SLEEP)
                || (Adapter->PSState == PS_STATE_PRE_SLEEP)
                ) {
                wlan_debug2("EXEC_NEXT_CMD: Cannot send cmd 0x%x in PSState %d\n",
                       CmdPtr->Command, Adapter->PSState);
                ret = WLAN_STATUS_FAILURE;
                goto done;
            }
            wlan_debug3("EXEC_NEXT_CMD: OK to send command "
                   "0x%x in PSState %d\n", CmdPtr->Command, Adapter->PSState);
        } else if (Adapter->PSState != PS_STATE_FULL_POWER) {
            /*
             * 1. Non-PS command: 
             * Queue it. set NeedToWakeup to TRUE if current state 
             * is SLEEP, otherwise call PSWakeup to send Exit_PS.
             * 2. PS command but not Exit_PS: 
             * Ignore it.
             * 3. PS command Exit_PS:
             * Set NeedToWakeup to TRUE if current state is SLEEP, 
             * otherwise send this command down to firmware
             * immediately.
             */
            if (CmdPtr->Command !=
                wlan_cpu_to_le16(HostCmd_CMD_802_11_PS_MODE)) {
                /*  Prepare to send Exit PS,
                 *  this non PS command will be sent later */
                if ((Adapter->PSState == PS_STATE_SLEEP)
                    || (Adapter->PSState == PS_STATE_PRE_SLEEP)
                    ) {
                    /* w/ new scheme, it will not reach here.
                       since it is blocked in main_thread. */
                    Adapter->NeedToWakeup = TRUE;
                } else
                    PSWakeup(priv, 0);

                ret = WLAN_STATUS_SUCCESS;
                goto done;
            } else {
                /*
                 * PS command. Ignore it if it is not Exit_PS. 
                 * otherwise send it down immediately.
                 */
                HostCmd_DS_802_11_PS_MODE *psm = &CmdPtr->params.psmode;

                wlan_debug3("EXEC_NEXT_CMD: PS cmd- Action=0x%x\n",
                       psm->Action);
                if (psm->Action != wlan_cpu_to_le16(HostCmd_SubCmd_Exit_PS)) {
                    wlan_debug1 ("EXEC_NEXT_CMD: Ignore Enter PS cmd\n");
                    list_del((struct list_head *) CmdNode);
                    CleanupAndInsertCmd(priv, CmdNode);

                    ret = WLAN_STATUS_SUCCESS;
                    goto done;
                }

                if ((Adapter->PSState == PS_STATE_SLEEP)
                    || (Adapter->PSState == PS_STATE_PRE_SLEEP)
                    ) {
                    wlan_debug1 ("EXEC_NEXT_CMD: Ignore ExitPS cmd in sleep\n");
                    list_del((struct list_head *) CmdNode);
                    CleanupAndInsertCmd(priv, CmdNode);
                    Adapter->NeedToWakeup = TRUE;

                    ret = WLAN_STATUS_SUCCESS;
                    goto done;
                }

                wlan_debug3("EXEC_NEXT_CMD: Sending Exit_PS down...\n");
            }
        }
        list_del((struct list_head *) CmdNode);
        DownloadCommandToStation(priv, CmdNode);
    } else {
        if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
            /*
             * check if in power save mode, if yes, put the device back
             * to PS mode
             */
            if ((Adapter->PSMode != Wlan802_11PowerModeCAM) &&
                (Adapter->PSState == PS_STATE_FULL_POWER) &&
                (Adapter->MediaConnectStatus == WlanMediaStateConnected)) {
                if (Adapter->SecInfo.WPAEnabled
                    || Adapter->SecInfo.WPA2Enabled) {
                    if (Adapter->IsGTK_SET) {
                        wlan_debug3("EXEC_NEXT_CMD: WPA enabled and GTK_SET"
                               " go back to PS_SLEEP");
                        PSSleep(priv, 0);
                    }
                } else {
                    {
                        wlan_debug3("EXEC_NEXT_CMD: Command PendQ is empty,"
                               " go back to PS_SLEEP");
                        PSSleep(priv, 0);
                    }
                }
            }
        }
    }

    ret = WLAN_STATUS_SUCCESS;
  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function handles the timeout of command sending.
 *  It will re-send the same command again.
 *  
 *  @param FunctionContext    A pointer to FunctionContext
 *  @return 	   n/a
 */
void
MrvDrvCommandTimerFunction(void *FunctionContext)
{
    wlan_private *priv = (wlan_private *) FunctionContext;
    wlan_adapter *Adapter = priv->adapter;
    CmdCtrlNode *pTempNode;
    HostCmd_DS_COMMAND *CmdPtr;

    ENTER();

    wlan_debug3("Command timeout.\n");

    Adapter->CommandTimerIsSet = FALSE;

    if (!Adapter->num_cmd_timeout)
        Adapter->dbg.num_cmd_timeout++;

    pTempNode = Adapter->CurCmd;

    if (pTempNode == NULL) {
        wlan_debug1("CurCmd Empty\n");
        goto exit;
    }

    CmdPtr = (HostCmd_DS_COMMAND *) pTempNode->BufVirtualAddr;
    if (CmdPtr == NULL) {
        goto exit;
    }

    if (CmdPtr->Size) {
        Adapter->dbg.TimeoutCmdId = wlan_cpu_to_le16(CmdPtr->Command);
        Adapter->dbg.TimeoutCmdAct =
            wlan_cpu_to_le16(*(u16 *) ((u8 *) CmdPtr + S_DS_GEN));
        wlan_debug2("Timeout cmd = 0x%x, act = 0x%x\n",
               Adapter->dbg.TimeoutCmdId, Adapter->dbg.TimeoutCmdAct);
    }
#define MAX_CMD_TIMEOUT_COUNT	5
    Adapter->num_cmd_timeout++;
    if (Adapter->num_cmd_timeout > MAX_CMD_TIMEOUT_COUNT) {
        wlan_debug1("num_cmd_timeout=%d\n", Adapter->num_cmd_timeout);
        goto exit;
    }

    /* Restart the timer to trace command response again */
    ModTimer(&Adapter->MrvDrvCommandTimer, MRVDRV_TIMER_1S);
    Adapter->CommandTimerIsSet = TRUE;

    /* Wake up main thread to read int status register */
    Adapter->IntCounter++;
    rt_event_send(&priv->MainThread.waitQ, WakeUpMainThread);

  exit:
    LEAVE();
    return;
}

/** 
 *  @brief This function sends sleep confirm command to firmware.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param cmdptr  A pointer to the command
 *  @param size	   the size of command
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
SendConfirmSleep(wlan_private * priv, u8 * CmdPtr, u16 size)
{
    wlan_adapter *Adapter = priv->adapter;
    int ret = WLAN_STATUS_SUCCESS;
    static u32 i = 0;

    ENTER();

    wlan_debug3 ("SLEEP_CFM", CmdPtr, size);

    ret = sbi_host_to_card(priv, MVMS_CMD, CmdPtr, size);
    priv->wlan_dev.dnld_sent = DNLD_RES_RECEIVED;

    if (ret) {
        wlan_debug2("SLEEP_CFM: sbi_host_to_card() failed\n");
        Adapter->dbg.num_cmd_sleep_cfm_host_to_card_failure++;
    } else {
        Adapter->PSState = PS_STATE_SLEEP;
        if (Adapter->bHostSleepConfigured &&
            (Adapter->sleep_period.period == 0)) {
            Adapter->bWakeupDevRequired = TRUE;
            wlan_host_sleep_activated_event(priv);
        }
#define NUM_SC_PER_LINE		16
        if (++i % NUM_SC_PER_LINE == 0) {
            wlan_debug2("+\n");
        } else {
            wlan_debug2("+");
        }

        /* check if interrupt is received after sleep confirm */
        if (Adapter->IntCounter) {
            wlan_debug2("SLEEP_CFM: After sent, IntCnt=%d\n",
                   Adapter->IntCounter);
            Adapter->PSState = PS_STATE_AWAKE;
        }
    }

    LEAVE();
    return ret;
}

/** 
 *  @brief This function sends Enter_PS command to firmware.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param wait_option	wait response or not
 *  @return 	   	n/a 
 */
void
PSSleep(wlan_private * priv, int wait_option)
{

    ENTER();

    PrepareAndSendCommand(priv, HostCmd_CMD_802_11_PS_MODE,
                          HostCmd_SubCmd_Enter_PS, wait_option, 0, NULL);

    LEAVE();
    return;
}

/** 
 *  @brief This function sends Eixt_PS command to firmware.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param wait_option	wait response or not
 *  @return 	   	n/a 
 */
void
PSWakeup(wlan_private * priv, int wait_option)
{
    WLAN_802_11_POWER_MODE LocalPSMode;

    ENTER();

    LocalPSMode = Wlan802_11PowerModeCAM;

    PrepareAndSendCommand(priv, HostCmd_CMD_802_11_PS_MODE,
                          HostCmd_SubCmd_Exit_PS,
                          wait_option, 0, &LocalPSMode);

    LEAVE();
    return;
}

/** 
 *  @brief This function checks condition and prepares to
 *  send sleep confirm command to firmware if ok.
 *  
 *  @param priv    	A pointer to wlan_private structure
 *  @param PSMode  	Power Saving mode
 *  @return 	   	n/a 
 */
void
PSConfirmSleep(wlan_private * priv, u16 PSMode)
{
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    if (!priv->wlan_dev.dnld_sent && !Adapter->CurCmd && !Adapter->IntCounter) {
        SendConfirmSleep(priv, (u8 *) & Adapter->PSConfirmSleep,
                         sizeof(PS_CMD_ConfirmSleep));
    } else {
        wlan_debug2 ("Delay Sleep Confirm (%s%s%s)\n",
               (priv->wlan_dev.dnld_sent) ? "D" : "",
               (Adapter->CurCmd) ? "C" : "",
               (Adapter->IntCounter) ? "I" : "");
    }

    LEAVE();
}
