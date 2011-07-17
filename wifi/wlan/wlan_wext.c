/** @file  wlan_wext.c 
  * @brief This file contains ioctl functions
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
  */
/********************************************************
Change log:
	10/10/05: Add Doxygen format comments
	12/23/05: Modify FindBSSIDInList to search entire table for
	          duplicate BSSIDs when earlier matches are not compatible
	12/26/05: Remove errant memcpy in wlanidle_off; overwriting stack space
	01/05/06: Add kernel 2.6.x support	
	01/11/06: Conditionalize new scan/join functions.
	          Update statics/externs.  Move forward decl. from wlan_decl.h
	04/06/06: Add TSPEC, queue metrics, and MSDU expiry support
	04/10/06: Add hostcmd generic API
	04/18/06: Remove old Subscrive Event and add new Subscribe Event
	          implementation through generic hostcmd API
	05/04/06: Add IBSS coalescing related new iwpriv command
	08/29/06: Add ledgpio private command
	10/23/06: Validate setbcnavg/setdataavg command parameters and
	          return error if out of range
********************************************************/

#include	"include.h"

#include	"wlan_version.h"
#include     "wlan_dev.h"
#include	"wlan_debug.h"
#include "wlan_wext.h"
extern struct rt_wlan_dev *wlan_eth ;
extern wlan_private *wlanpriv;

/** 
 *  @brief Find the channel frequency power info with specific channel
 *   
 *  @param adapter 	A pointer to wlan_adapter structure
 *  @param band		it can be BAND_A, BAND_G or BAND_B
 *  @param channel      the channel for looking	
 *  @return 	   	A pointer to CHANNEL_FREQ_POWER structure or NULL if not find.
 */
CHANNEL_FREQ_POWER *
find_cfp_by_band_and_channel(wlan_adapter * adapter, u8 band, u16 channel)
{
    CHANNEL_FREQ_POWER *cfp = NULL;
    REGION_CHANNEL *rc;
    int count = sizeof(adapter->region_channel) /
        sizeof(adapter->region_channel[0]);
    int i, j;

    for (j = 0; !cfp && (j < count); j++) {
        rc = &adapter->region_channel[j];

        if (adapter->State11D.Enable11D == ENABLE_11D) {
            rc = &adapter->universal_channel[j];
        }
        if (!rc->Valid || !rc->CFP)
            continue;
        if (rc->Band != band)
            continue;
        for (i = 0; i < rc->NrCFP; i++) {
            if (rc->CFP[i].Channel == channel) {
                cfp = &rc->CFP[i];
                break;
            }
        }
    }

    if (!cfp && channel)
        wlan_debug1("find_cfp_by_band_and_channel(): cannot find "
               "cfp by band %d & channel %d\n", band, channel);

    return cfp;
}
int wlan_scan_network_for_AP(void)
{
   if(wlan_eth==NULL)
   return -1;
   if(wlan_set_scan(wlan_eth, NULL,NULL,NULL)!=0)
   wlan_debug1("wlan_set_scan sucess\n");
   return 0;
}
int wlan_associate_AP(char *dstbssid,int len)
{
	 char * ssid[6];
	 if(dstbssid==RT_NULL)
	 rt_memset(ssid,0xff,6);
	 else{
	 rt_memcpy(ssid,dstbssid,6);
	 } 
	 wlan_set_wap (wlan_eth, ssid,6);
}
static _wep_key_set_arg keyset;
int set_wlan_wep_key_char(char *key,int len)
{
	
	int keylen=len;
	wlan_debug1( "set wep key %s\n",key);
	rt_memset((u8*)&keyset,0x00,sizeof(Wep_Key_Set_Arg));
	rt_memcpy((u8*)(&keyset.Key_value[0]),key,len);
	keyset.KeyLength[0]=len;
	keyset.defaut_key_index=0;
	keyset.wepkeyaction=SETWEPKEY;
	wlan_set_wep_key(&keyset);

}
 int wlan_set_wep_key(Wep_Key_Set_Arg key_set_arg)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_private *priv = wlan_eth->priv;
    wlan_adapter *Adapter = priv->adapter;
    MRVL_WEP_KEY *pWep;
    int index, PrevAuthMode,i=0;

    ENTER();

    if (!Is_Command_Allowed(priv)) {
        wlan_debug1( "%s: not allowed\n", __FUNCTION__);
        return -EBUSY;
    }
    if(key_set_arg->defaut_key_index>=MRVL_NUM_WEP_KEY)
    { 	return -WLANEPARAMETER;}
    else{index=key_set_arg->defaut_key_index;}
	
    if(key_set_arg->KeyLength[index]==0||key_set_arg->KeyLength[index]>MAX_WEP_KEY_SIZE)
    return -WLANEPARAMETER;
  
   
    
    if(key_set_arg->wepkeyaction==SETWEPKEY)
    {
		Adapter->CurrentWepKeyIndex = index;
	 	for(i=0;i<MRVL_NUM_WEP_KEY;i++)
    		{
			pWep = &Adapter->WepKey[i];
			if((key_set_arg->KeyLength[i]!=0)&&(key_set_arg->KeyLength[i]<=MAX_WEP_KEY_SIZE))
			{
				
				rt_memcpy(pWep->KeyMaterial,&key_set_arg->Key_value[i][0],key_set_arg->KeyLength[i]);
				if (key_set_arg->KeyLength[i]>MIN_WEP_KEY_SIZE) {
               	 		pWep->KeyLength = MAX_WEP_KEY_SIZE;
            			} else {
               			if (key_set_arg->KeyLength[i] > 0) {
                   			 pWep->KeyLength = MIN_WEP_KEY_SIZE;
               			 } 
                		}
            		}else{
				pWep->KeyLength = 0;
				rt_memset(pWep->KeyMaterial,0x00,MAX_WEP_KEY_SIZE);
			}
      		}
		Adapter->SecInfo.WEPStatus = Wlan802_11WEPEnabled;
		ret = PrepareAndSendCommand(priv,
                                    HostCmd_CMD_802_11_SET_WEP,
                                    0, HostCmd_OPTION_WAITFORRSP,
                                    OID_802_11_ADD_WEP, NULL);

        	if (ret) {
           	LEAVE();
           	return ret;
		
        	}
    }else if(key_set_arg->wepkeyaction==NOWEPKEY)
    {
	
	 Adapter->SecInfo.WEPStatus = Wlan802_11WEPDisabled;
    }
    wlan_debug3("act %d, Length=%d Index=%d CurrentWepKeyIndex=%d\n",
           		key_set_arg->wepkeyaction, key_set_arg->KeyLength[index], Adapter->CurrentWepKeyIndex);
    if (Adapter->SecInfo.WEPStatus == Wlan802_11WEPEnabled) {
        Adapter->CurrentPacketFilter |= HostCmd_ACT_MAC_WEP_ENABLE;
    } else {
        Adapter->CurrentPacketFilter &= ~HostCmd_ACT_MAC_WEP_ENABLE;
    }
   ret = PrepareAndSendCommand(priv,
                                HostCmd_CMD_MAC_CONTROL,
                                0, HostCmd_OPTION_WAITFORRSP,
                                0, &Adapter->CurrentPacketFilter);
    LEAVE();
    return WLAN_STATUS_SUCCESS;
 
 }
 
int wlan_set_wpa_psk(WLAN_802_11_KEY* wpa_psk_arg)
{
    int ret = WLAN_STATUS_SUCCESS;
    wlan_private *priv = wlan_eth->priv;
    WLAN_802_11_KEY *pKey;

    ENTER();

    if (!Is_Command_Allowed(priv)) {
        wlan_debug1("%s: not allowed\n", __FUNCTION__);
        return -EBUSY;
    }

    pKey = wpa_psk_arg;

    wlan_debug3("Key buffer: %s", pKey->KeyMaterial);

    // current driver only supports key length of up to 32 bytes
    if (pKey->KeyLength > MRVL_MAX_WPA_KEY_LENGTH) {
        wlan_debug1( " Error in key length \n");
        return WLAN_STATUS_FAILURE;
    }

    ret = PrepareAndSendCommand(priv,
                                HostCmd_CMD_802_11_KEY_MATERIAL,
                                HostCmd_ACT_SET,
                                HostCmd_OPTION_WAITFORRSP,
                                KEY_INFO_ENABLED, pKey);

    if (ret) {
        LEAVE();
        return ret;
    }

    LEAVE();
    return ret;
}

