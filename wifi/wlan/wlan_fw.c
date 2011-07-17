/** @file wlan_fw.c
  * @brief This file contains the initialization for FW
  * and HW 
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
  */
/********************************************************
Change log:
	09/28/05: Add Doxygen format comments
	01/05/06: Add kernel 2.6.x support	
	01/11/06: Conditionalize new scan/join functions.
	          Cleanup association response handler initialization.
	01/06/05: Add FW file read
	05/08/06: Remove the 2nd GET_HW_SPEC command and TempAddr/PermanentAddr
	06/30/06: replaced MODULE_PARM(name, type) with module_param(name, type, perm)

********************************************************/

#include	"include.h"
#include	"gspibin.h"
#include	"helper_gspi.h"
#include	"wlan_debug.h"
//#include <linux/vmalloc.h>

/********************************************************
		Local Variables
********************************************************/

char *helper_name = NULL;
char *fw_name = NULL;

/********************************************************
		Global Variables
********************************************************/

/********************************************************
		Local Functions
********************************************************/

/** 
 *  @brief This function downloads firmware image, gets
 *  HW spec from firmware and set basic parameters to
 *  firmware.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_download_firmware(wlan_private * priv)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_adapter *adapter = priv->adapter;
    u8 *ptr = NULL;	
    u8* temp1;
    u32 len = 0;

    HostCmd_DS_CMD_GSPI_BUS_CONFIG bus_config;

    ENTER();

    sbi_disable_host_int(priv);

    adapter->fmimage = NULL;
    adapter->fmimage_len = 0;
    adapter->helper = NULL;
    adapter->helper_len = 0;
    ptr=(u8*)helpgspibin;
    len=sizeof(helpgspibin);


    adapter->helper = ptr;
    adapter->helper_len = len;
    wlan_debug2("helper read success, len=%x\n", len);
 
    ptr=(u8*)gspi8686bin;
    len=sizeof(gspi8686bin);


    adapter->fmimage = ptr;
    adapter->fmimage_len = len;


    /* Download the helper */
    ret = sbi_prog_helper(priv);

    if (ret) {
        wlan_debug1("down load helper failed!\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }
    /* Download firmware */
   if (sbi_prog_firmware_w_helper(priv)) {
       wlan_debug1("down load firmware unsuccessful\n");
       ret = WLAN_STATUS_FAILURE;
       goto done;
    }

    /* check if the fimware is downloaded successfully or not */
    if (sbi_verify_fw_download(priv)) {
        wlan_debug1( "FW failed to be active in time!\n");
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }
    wlan_debug3(" fw has been load to board\n ");
#define RF_REG_OFFSET 0x07
#define RF_REG_VALUE  0xc8

    sbi_enable_host_int(priv);

#define 	SPI_BMR_DELAY_METHOD		B_BIT_2
#define		SPI_BMR_BUSMODE_16_16		0x02    //16bit address and 16bit data
         g_bus_mode_reg = SPI_BMR_BUSMODE_16_16 | SPI_BMR_DELAY_METHOD;
         g_dummy_clk_ioport = 1;
         g_dummy_clk_reg = 1;
         bus_config.BusDelayMode = g_bus_mode_reg;
         bus_config.HostTimeDelayToReadPort = g_dummy_clk_ioport * 16;
         bus_config.HostTimeDelayToReadregister = g_dummy_clk_reg * 16;
        wlan_debug3 ("Setting for %d %d\n", g_dummy_clk_ioport,
               g_dummy_clk_reg);
        ret =PrepareAndSendCommand(priv, HostCmd_CMD_GSPI_BUS_CONFIG,
                                  HostCmd_ACT_GEN_SET,
                                  HostCmd_OPTION_WAITFORRSP, 0, &bus_config);
        if (ret) {
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
	wlan_debug3("Hostcmd_CMD_GSPI_BUS_CONFIG OK\n ");

        /*
         * Read MAC address from HW
         */
        memset(adapter->CurrentAddr, 0xff, MRVDRV_ETH_ADDR_LEN);

        ret = PrepareAndSendCommand(priv, HostCmd_CMD_GET_HW_SPEC,
                                    0, HostCmd_OPTION_WAITFORRSP, 0, NULL);

        if (ret) {
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }

	temp1=adapter->CurrentAddr;
	wlan_debug3 ("Hostcmd_CMD_GET_HW_SPEC OK:%x,%x,%x,%x,%x,%x,%x,%x\n",
	temp1[0],temp1[1],temp1[2],temp1[3],temp1[4],temp1[5],temp1[6],temp1[7]);

       ret = PrepareAndSendCommand(priv,
                                    HostCmd_CMD_MAC_CONTROL,
                                    0, HostCmd_OPTION_WAITFORRSP, 0,
                                    &adapter->CurrentPacketFilter);

        if (ret) {
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
		wlan_debug2("Hostcmd_CMD_MAC_CONTROL OK\n");

        ret = PrepareAndSendCommand(priv,
                                    HostCmd_CMD_802_11_FW_WAKE_METHOD,
                                    HostCmd_ACT_GET,
                                    HostCmd_OPTION_WAITFORRSP, 0,
                                    &priv->adapter->fwWakeupMethod);

        if (ret) {
            ret = WLAN_STATUS_FAILURE;
            goto done;

        }
        ret = PrepareAndSendCommand(priv,
                                    HostCmd_CMD_802_11_RATE_ADAPT_RATESET,
                                    HostCmd_ACT_GEN_GET,
                                    HostCmd_OPTION_WAITFORRSP, 0, NULL);
        if (ret) {
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
	
        priv->adapter->DataRate = 0;
        ret = PrepareAndSendCommand(priv,
                                    HostCmd_CMD_802_11_RF_TX_POWER,
                                    HostCmd_ACT_GEN_GET,
                                    HostCmd_OPTION_WAITFORRSP, 0, NULL);

        if (ret) {
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
	wlan_debug3("Hostcmd_CMD_802_11_RF_TX_POWER OK\n ");

    ret = WLAN_STATUS_SUCCESS;
  done:
    LEAVE();

    return (ret);
}

/** 
 *  @brief This function initializes timers.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   n/a
 */
static void init_sync_objects(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    InitializeTimer(&Adapter->MrvDrvCommandTimer,
                    MrvDrvCommandTimerFunction, priv,"cmdtimer");
    Adapter->CommandTimerIsSet = FALSE;


    return;
}

/** 
 *  @brief This function allocates buffer for the member of adapter
 *  structure like command buffer and BSSID list.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
wlan_allocate_adapter(wlan_private * priv)
{
    u32 ulBufSize;
    wlan_adapter *Adapter = priv->adapter;

    BSSDescriptor_t *pTempScanTable;

    /* Allocate buffer to store the BSSID list */
    ulBufSize = sizeof(BSSDescriptor_t) * MRVDRV_MAX_BSSID_LIST;
	pTempScanTable = (BSSDescriptor_t *)rt_malloc(ulBufSize);
    if (!pTempScanTable) {
        return WLAN_STATUS_FAILURE;
    }

    Adapter->ScanTable = pTempScanTable;
    memset(Adapter->ScanTable, 0, ulBufSize);
	Adapter->bgScanConfig =(HostCmd_DS_802_11_BG_SCAN_CONFIG *)rt_malloc(sizeof(HostCmd_DS_802_11_BG_SCAN_CONFIG));
    if (!Adapter->bgScanConfig) {
        return WLAN_STATUS_FAILURE;
    }
    Adapter->bgScanConfigSize = sizeof(HostCmd_DS_802_11_BG_SCAN_CONFIG);
    memset(Adapter->bgScanConfig, 0, Adapter->bgScanConfigSize);

    /* Allocate the command buffers */
    if (AllocateCmdBuffer(priv) != WLAN_STATUS_SUCCESS) {
        return WLAN_STATUS_FAILURE;
    }

    memset(&Adapter->PSConfirmSleep, 0, sizeof(PS_CMD_ConfirmSleep));
    Adapter->PSConfirmSleep.SeqNum = (++Adapter->SeqNum);
    Adapter->PSConfirmSleep.Command =(HostCmd_CMD_802_11_PS_MODE);
    Adapter->PSConfirmSleep.Size =(sizeof(PS_CMD_ConfirmSleep));
    Adapter->PSConfirmSleep.Result = 0;
    Adapter->PSConfirmSleep.Action =(HostCmd_SubCmd_Sleep_Confirmed);

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function initializes the adapter structure
 *  and set default value to the member of adapter.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   n/a
 */
static void
wlan_init_adapter(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    int i;

    Adapter->ScanProbes = 0;

    Adapter->bcn_avg_factor = DEFAULT_BCN_AVG_FACTOR;
    Adapter->data_avg_factor = DEFAULT_DATA_AVG_FACTOR;

    /* ATIM params */
    Adapter->AtimWindow = 0;
    Adapter->ATIMEnabled = FALSE;

    Adapter->MediaConnectStatus = WlanMediaStateDisconnected;
    memset(Adapter->CurrentAddr, 0xff, MRVDRV_ETH_ADDR_LEN);

    /* Status variables */
    Adapter->HardwareStatus = WlanHardwareStatusInitializing;

    /* scan type */
    Adapter->ScanType = HostCmd_SCAN_TYPE_ACTIVE;

    /* scan mode */
    Adapter->ScanMode = HostCmd_BSS_TYPE_ANY;

    /* scan time */
    Adapter->SpecificScanTime = MRVDRV_SPECIFIC_SCAN_CHAN_TIME;
    Adapter->ActiveScanTime = MRVDRV_ACTIVE_SCAN_CHAN_TIME;
    Adapter->PassiveScanTime = MRVDRV_PASSIVE_SCAN_CHAN_TIME;

    /* 802.11 specific */
    Adapter->SecInfo.WEPStatus = Wlan802_11WEPDisabled;
    for (i = 0; i < sizeof(Adapter->WepKey) / sizeof(Adapter->WepKey[0]); i++)
        memset(&Adapter->WepKey[i], 0, sizeof(MRVL_WEP_KEY));
    Adapter->CurrentWepKeyIndex = 0;
    Adapter->SecInfo.AuthenticationMode = Wlan802_11AuthModeOpen;
    Adapter->SecInfo.EncryptionMode = CIPHER_NONE;

    ///////ADD FOR WEP TEST//////////
    Adapter->SecInfo.WPAEnabled = FALSE;
    Adapter->SecInfo.WPA2Enabled= FALSE;
    Adapter->mrvlAssocTlvBufferLen=0;
    ///////ADD FOR WEP TEST//////////

    Adapter->AdhocAESEnabled = FALSE;
    Adapter->InfrastructureMode = Wlan802_11Infrastructure;

    Adapter->NumInScanTable = 0;
    Adapter->pAttemptedBSSDesc = NULL;
    Adapter->pBeaconBufEnd = Adapter->beaconBuffer;

    Adapter->HisRegCpy |= HIS_TxDnLdRdy;

    memset(&Adapter->CurBssParams, 0, sizeof(Adapter->CurBssParams));

    /* PnP and power profile */
    Adapter->SurpriseRemoved = FALSE;

    Adapter->CurrentPacketFilter =
        HostCmd_ACT_MAC_RX_ON | HostCmd_ACT_MAC_TX_ON;

    Adapter->RadioOn = RADIO_ON;
    Adapter->TxAntenna = RF_ANTENNA_2;
    Adapter->RxAntenna = RF_ANTENNA_AUTO;

    Adapter->HWRateDropMode = HW_TABLE_RATE_DROP;
    Adapter->Is_DataRate_Auto = TRUE;
    Adapter->BeaconPeriod = MRVDRV_BEACON_INTERVAL;

    Adapter->AdhocChannel = DEFAULT_AD_HOC_CHANNEL;

    Adapter->PSMode = Wlan802_11PowerModeCAM;
    Adapter->MultipleDtim = MRVDRV_DEFAULT_MULTIPLE_DTIM;

    Adapter->ListenInterval = MRVDRV_DEFAULT_LISTEN_INTERVAL;

    Adapter->PSState = PS_STATE_FULL_POWER;
    Adapter->NeedToWakeup = FALSE;
    Adapter->LocalListenInterval = 0;   /* default value in firmware will be used */
    Adapter->fwWakeupMethod = WAKEUP_FW_UNCHANGED;

    Adapter->IsDeepSleep = FALSE;

    Adapter->bWakeupDevRequired = FALSE;
    Adapter->WakeupTries = 0;
    Adapter->bHostSleepConfigured = FALSE;
    Adapter->HSCfg.conditions = HOST_SLEEP_CFG_CANCEL;
    Adapter->HSCfg.gpio = 0;
    Adapter->HSCfg.gap = 0;

    Adapter->DataRate = 0;      // Initially indicate the rate as auto 

    Adapter->adhoc_grate_enabled = FALSE;

    Adapter->IntCounter = Adapter->IntCounterSaved = 0;

    INIT_LIST_HEAD((struct list_head *) &Adapter->RxSkbQ);

    Adapter->gen_null_pkg = TRUE;       /*Enable NULL Pkg generation */


    rt_event_init(&Adapter->cmd_EncKey, "EncKeyevt", RT_IPC_FLAG_FIFO);	  //which thread wait on this queue


    Adapter->CurrentTxSkb = NULL;
    Adapter->PktTxCtrl = 0;

    return;
}

/********************************************************
		Global Functions
********************************************************/

/** 
 *  @brief This function initializes firmware
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
wlan_init_fw(wlan_private * priv)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    /* Allocate adapter structure */
    if ((ret = wlan_allocate_adapter(priv)) != WLAN_STATUS_SUCCESS) {
        goto done;
    }

    /* init adapter structure */
    wlan_init_adapter(priv);

    /* init timer etc. */
    init_sync_objects(priv);

    /* download fimrware etc. */
    if ((ret = wlan_download_firmware(priv)) != WLAN_STATUS_SUCCESS) {
        Adapter->HardwareStatus = WlanHardwareStatusNotReady;
        ret = WLAN_STATUS_FAILURE;
        goto done;
    }
    /* init 802.11d */
    wlan_init_11d(priv);

    Adapter->HardwareStatus = WlanHardwareStatusReady;
    ret = WLAN_STATUS_SUCCESS;
  done:
    LEAVE();
    return ret;
}

/** 
 *  @brief This function frees the structure of adapter
 *    
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   n/a
 */
void
wlan_free_adapter(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    if (!Adapter) {
        wlan_debug1( "Why double free adapter?:)\n");
        return;
    }

    wlan_debug3("Free Command buffer\n");
    FreeCmdBuffer(priv);

    wlan_debug2("Free CommandTimer\n");
    if (Adapter->CommandTimerIsSet) {
        CancelTimer(&Adapter->MrvDrvCommandTimer);
        Adapter->CommandTimerIsSet = FALSE;
    }
    FreeTimer(&Adapter->MrvDrvCommandTimer);

    if (Adapter->bgScanConfig) {
        rt_free(Adapter->bgScanConfig);
        Adapter->bgScanConfig = NULL;
    }



    wlan_debug3("Free ScanTable\n");
    if (Adapter->ScanTable) {
        rt_free(Adapter->ScanTable);
        Adapter->ScanTable = NULL;
    }

    wlan_debug3("Free Adapter\n");

    /* Free the adapter object itself */
    rt_free(Adapter);
    priv->adapter = NULL;
    LEAVE();
}
