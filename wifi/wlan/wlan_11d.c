/** @file wlan_11d.c
  * @brief This file contains functions for 802.11D.
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
  */
/********************************************************
Change log:
	10/04/05: Add Doxygen format comments
	
********************************************************/
#include	"include.h"

/********************************************************
		Local Variables
********************************************************/
#define TX_PWR_DEFAULT	10

static region_code_mapping_t region_code_mapping[] = {
    {"US ", 0x10},              /* US FCC      */
    {"CA ", 0x20},              /* IC Canada   */
    {"SG ", 0x10},              /* Singapore   */
    {"EU ", 0x30},              /* ETSI        */
    {"AU ", 0x30},              /* Australia   */
    {"KR ", 0x30},              /* Republic Of Korea */
    {"ES ", 0x31},              /* Spain       */
    {"FR ", 0x32},              /* France      */
    {"JP ", 0x40},              /* Japan       */
    {"JP ", 0x41},              /* Japan       */
};

/********************************************************
		Global Variables
********************************************************/
/* Following 2 structure defines the supported channels */
CHANNEL_FREQ_POWER channel_freq_power_UN_BG[] = {
    {1, 2412, TX_PWR_DEFAULT},
    {2, 2417, TX_PWR_DEFAULT},
    {3, 2422, TX_PWR_DEFAULT},
    {4, 2427, TX_PWR_DEFAULT},
    {5, 2432, TX_PWR_DEFAULT},
    {6, 2437, TX_PWR_DEFAULT},
    {7, 2442, TX_PWR_DEFAULT},
    {8, 2447, TX_PWR_DEFAULT},
    {9, 2452, TX_PWR_DEFAULT},
    {10, 2457, TX_PWR_DEFAULT},
    {11, 2462, TX_PWR_DEFAULT},
    {12, 2467, TX_PWR_DEFAULT},
    {13, 2472, TX_PWR_DEFAULT},
    {14, 2484, TX_PWR_DEFAULT}
};

CHANNEL_FREQ_POWER channel_freq_power_UN_AJ[] = {
    {8, 5040, TX_PWR_DEFAULT},
    {12, 5060, TX_PWR_DEFAULT},
    {16, 5080, TX_PWR_DEFAULT},
    {34, 5170, TX_PWR_DEFAULT},
    {38, 5190, TX_PWR_DEFAULT},
    {42, 5210, TX_PWR_DEFAULT},
    {46, 5230, TX_PWR_DEFAULT},
    {36, 5180, TX_PWR_DEFAULT},
    {40, 5200, TX_PWR_DEFAULT},
    {44, 5220, TX_PWR_DEFAULT},
    {48, 5240, TX_PWR_DEFAULT},
    {52, 5260, TX_PWR_DEFAULT},
    {56, 5280, TX_PWR_DEFAULT},
    {60, 5300, TX_PWR_DEFAULT},
    {64, 5320, TX_PWR_DEFAULT},
    {100, 5500, TX_PWR_DEFAULT},
    {104, 5520, TX_PWR_DEFAULT},
    {108, 5540, TX_PWR_DEFAULT},
    {112, 5560, TX_PWR_DEFAULT},
    {116, 5580, TX_PWR_DEFAULT},
    {120, 5600, TX_PWR_DEFAULT},
    {124, 5620, TX_PWR_DEFAULT},
    {128, 5640, TX_PWR_DEFAULT},
    {132, 5660, TX_PWR_DEFAULT},
    {136, 5680, TX_PWR_DEFAULT},
    {140, 5700, TX_PWR_DEFAULT},
    {149, 5745, TX_PWR_DEFAULT},
    {153, 5765, TX_PWR_DEFAULT},
    {157, 5785, TX_PWR_DEFAULT},
    {161, 5805, TX_PWR_DEFAULT},
    {165, 5825, TX_PWR_DEFAULT},
/*	{240, 4920, TX_PWR_DEFAULT}, 
	{244, 4940, TX_PWR_DEFAULT}, 
	{248, 4960, TX_PWR_DEFAULT}, 
	{252, 4980, TX_PWR_DEFAULT}, 
channels for 11J JP 10M channel gap */
};

extern CHANNEL_FREQ_POWER *wlan_get_region_cfp_table(u8 region,
                                                     u8 band, int *cfp_no);

/********************************************************
		Local Functions
********************************************************/
/** 
 *  @brief This function convert Region string to code integer
 *  @param region     region string
 *  @return 	      region id
*/
static u8
wlan_region_2_code(s8 * region)
{
    u8 i;
    u8 size = sizeof(region_code_mapping) / sizeof(region_code_mapping_t);

    for (i = 0; region[i] && i < COUNTRY_CODE_LEN; i++)
        region[i] = toupper(region[i]);

    for (i = 0; i < size; i++) {
        if (!memcmp(region, region_code_mapping[i].region, COUNTRY_CODE_LEN))
            return (region_code_mapping[i].code);
    }

    /* default is US */
    return (region_code_mapping[0].code);
}

/** 
 *  @brief This function converts interger code to region string
 *  @param code       region code
 *  @return 	      region string
*/
static u8 *
wlan_code_2_region(u8 code)
{
    u8 i;
    u8 size = sizeof(region_code_mapping) / sizeof(region_code_mapping_t);
    for (i = 0; i < size; i++) {
        if (region_code_mapping[i].code == code)
            return (region_code_mapping[i].region);
    }
    /* default is US */
    return (region_code_mapping[0].region);
}

/** 
 *  @brief This function finds the NoOfChan-th chan after the firstChan
 *  @param band       band
 *  @param firstChan  first channel number
 *  @param NoOfChan   number of channels
 *  @return 	      the NoOfChan-th chan number
*/
static BOOLEAN
wlan_get_chan_11d(u8 band, u8 firstChan, u8 NoOfChan, u8 * chan)
/*find the NoOfChan-th chan after the firstChan*/
{
    u8 i;
    CHANNEL_FREQ_POWER *cfp;
    u8 cfp_no;

//	 ENTER();

    {
        cfp = channel_freq_power_UN_BG;
        cfp_no = sizeof(channel_freq_power_UN_BG) /
            sizeof(CHANNEL_FREQ_POWER);
    }

    for (i = 0; i < cfp_no; i++) {
        if ((cfp + i)->Channel == firstChan) {
            rt_kprintf("firstChan found\n");
            break;
        }
    }

    if (i < cfp_no) {
        /*if beyond the boundary */
        if (i + NoOfChan < cfp_no) {
            *chan = (cfp + i + NoOfChan)->Channel;
            return TRUE;
        }
    }

//   LEAVE();
    return FALSE;
}

/** 
 *  @brief This function Checks if chan txpwr is learned from AP/IBSS
 *  @param chan                 chan number
 *  @param parsed_region_chan   pointer to parsed_region_chan_11d_t     
 *  @return 	                TRUE; FALSE
*/
BOOLEAN
wlan_channel_known_11d(u8 chan, parsed_region_chan_11d_t * parsed_region_chan)
{
    chan_power_11d_t *chanPwr = parsed_region_chan->chanPwr;
    u8 NoOfChan = parsed_region_chan->NoOfChan;
    u8 i = 0;

    ENTER();
 
    for (i = 0; i < NoOfChan; i++) {
        if (chan == chanPwr[i].chan) {
        wlan_debug3( "11D: Found Chan:%d\n", chan);
            LEAVE();
            return TRUE;
        }
    }
    LEAVE();
    return FALSE;
}

/********************************************************
		Global Functions
********************************************************/

/** 
 *  @brief This function Converts chan to frequency
 *  @param chan                 channel number
 *  @param band                 band
 *  @return 	                channel frequency
*/
u32
chan_2_freq(u8 chan, u8 band)
{
    CHANNEL_FREQ_POWER *cf;
    u16 cnt;
    u16 i;
    u32 freq = 0;

//    ENTER();

    {
        cf = channel_freq_power_UN_BG;
        cnt = sizeof(channel_freq_power_UN_BG) / sizeof(CHANNEL_FREQ_POWER);
    }

    for (i = 0; i < cnt; i++) {
        if (chan == cf[i].Channel)
            freq = cf[i].Freq;
    }

//    LEAVE();
    return freq;
}

/** 
 *  @brief This function generates domaininfo from parsed_region_chan
 *  @param parsed_region_chan   pointer to parsed_region_chan_11d_t
 *  @param domaininfo           pointer to wlan_802_11d_domain_reg_t
 *  @return 	                WLAN_STATUS_SUCCESS
*/
int
wlan_generate_domain_info_11d(parsed_region_chan_11d_t * parsed_region_chan,
                              wlan_802_11d_domain_reg_t * domaininfo)
{
    u8 NoOfSubband = 0;

    u8 NoOfChan = parsed_region_chan->NoOfChan;
    u8 NoOfParsedChan = 0;

    u8 firstChan = 0, nextChan = 0, maxPwr = 0;

    u8 i, flag = 0;

    ENTER();

    memcpy(domaininfo->CountryCode, parsed_region_chan->CountryCode,COUNTRY_CODE_LEN);

    wlan_debug3("11D:NoOfChan=%d\n", NoOfChan);
 //   HEXDUMP("11D:parsed_region_chan:", (char *) parsed_region_chan,sizeof(parsed_region_chan_11d_t));

    for (i = 0; i < NoOfChan; i++) {
        if (!flag) {
            flag = 1;
            nextChan = firstChan = parsed_region_chan->chanPwr[i].chan;
            maxPwr = parsed_region_chan->chanPwr[i].pwr;
            NoOfParsedChan = 1;
            continue;
        }

        if (parsed_region_chan->chanPwr[i].chan == nextChan + 1 &&
            parsed_region_chan->chanPwr[i].pwr == maxPwr) {
            nextChan++;
            NoOfParsedChan++;
        } else {
            domaininfo->Subband[NoOfSubband].FirstChan = firstChan;
            domaininfo->Subband[NoOfSubband].NoOfChan = NoOfParsedChan;
            domaininfo->Subband[NoOfSubband].MaxTxPwr = maxPwr;
            NoOfSubband++;
            NoOfParsedChan = 1;
            nextChan = firstChan = parsed_region_chan->chanPwr[i].chan;
            maxPwr = parsed_region_chan->chanPwr[i].pwr;
        }
    }

    if (flag) {
        domaininfo->Subband[NoOfSubband].FirstChan = firstChan;
        domaininfo->Subband[NoOfSubband].NoOfChan = NoOfParsedChan;
        domaininfo->Subband[NoOfSubband].MaxTxPwr = maxPwr;
        NoOfSubband++;
    }
    domaininfo->NoOfSubband = NoOfSubband;

 wlan_debug3("NoOfSubband=%x\n", domaininfo->NoOfSubband);
 //   HEXDUMP("11D:domaininfo:", (char *) domaininfo,
 //           COUNTRY_CODE_LEN + 1 +
 //           sizeof(IEEEtypes_SubbandSet_t) * NoOfSubband);
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function generates parsed_region_chan from Domain Info learned from AP/IBSS
 *  @param region_chan          pointer to REGION_CHANNEL
 *  @param *parsed_region_chan  pointer to parsed_region_chan_11d_t
 *  @return 	                N/A
*/
void wlan_generate_parsed_region_chan_11d(REGION_CHANNEL * region_chan,
                                     parsed_region_chan_11d_t *
                                     parsed_region_chan)
{
    u8 i;
    CHANNEL_FREQ_POWER *cfp;

    ENTER();

    if (region_chan == NULL) {
        wlan_debug3("11D: region_chan is NULL\n");
        return;
    }

    cfp = region_chan->CFP;
    if (cfp == NULL) {
        wlan_debug3( "11D: cfp equal NULL \n");
        return;
    }

    parsed_region_chan->band = region_chan->Band;
    parsed_region_chan->region = region_chan->Region;
    memcpy(parsed_region_chan->CountryCode,
           wlan_code_2_region(region_chan->Region), COUNTRY_CODE_LEN);

    wlan_debug3("11D: region[0x%x] band[%d]\n", parsed_region_chan->region,
           parsed_region_chan->band);

    for (i = 0; i < region_chan->NrCFP; i++, cfp++) {
        parsed_region_chan->chanPwr[i].chan = cfp->Channel;
        parsed_region_chan->chanPwr[i].pwr = cfp->MaxTxPower;
        wlan_debug3("11D: Chan[%d] Pwr[%d]\n",
               parsed_region_chan->chanPwr[i].chan,
               parsed_region_chan->chanPwr[i].pwr);
    }
    parsed_region_chan->NoOfChan = region_chan->NrCFP;

    wlan_debug3("11D: NoOfChan[%d]\n", parsed_region_chan->NoOfChan);

    LEAVE();
    return;
}

/** 
 *  @brief generate parsed_region_chan from Domain Info learned from AP/IBSS
 *  @param region               region ID
 *  @param band                 band
 *  @param chan                 chan
 *  @return 	                TRUE;FALSE
*/
BOOLEAN
wlan_region_chan_supported_11d(u8 region, u8 band, u8 chan)
{
    CHANNEL_FREQ_POWER *cfp;
    int cfp_no;
    u8 idx;

    ENTER();

    if ((cfp = wlan_get_region_cfp_table(region, band, &cfp_no)) == NULL) {
        return FALSE;
    }

    for (idx = 0; idx < cfp_no; idx++) {
        if (chan == (cfp + idx)->Channel) {
            /* If Mrvl Chip Supported? */
            if ((cfp + idx)->Unsupported) {
                return FALSE;
            } else {
                return TRUE;
            }
        }
    }

    /*chan is not in the region table */
    LEAVE();
    return FALSE;
}

/** 
 *  @brief This function checks if chan txpwr is learned from AP/IBSS
 *  @param chan                 chan number
 *  @param parsed_region_chan   pointer to parsed_region_chan_11d_t     
 *  @return 	                WLAN_STATUS_SUCCESS       
*/
int
wlan_parse_domain_info_11d(IEEEtypes_CountryInfoFullSet_t * CountryInfo,
                           u8 band,
                           parsed_region_chan_11d_t * parsed_region_chan)
{
    u8 NoOfSubband, NoOfChan;
    u8 lastChan, firstChan, curChan;
    u8 region;

    u8 idx = 0;                 /*chan index in parsed_region_chan */

    u8 j, i;

    ENTER();

    /*Validation Rules:
       1. Valid Region Code
       2. First Chan increment
       3. Channel range no overlap
       4. Channel is valid?
       5. Channel is supported by Region?
       6. Others
     */

  //  HEXDUMP("CountryInfo:", (s8 *) CountryInfo, 30);

    if ((*(CountryInfo->CountryCode)) == 0 ||
        (CountryInfo->Len <= COUNTRY_CODE_LEN)) {
        /* No region Info or Wrong region info: treat as No 11D info */
        LEAVE();
        return WLAN_STATUS_SUCCESS;
    }

    /*Step1: check region_code */
    parsed_region_chan->region = region =
        wlan_region_2_code(CountryInfo->CountryCode);

    wlan_debug3( "regioncode=%x\n", (u8) parsed_region_chan->region);

    parsed_region_chan->band = band;

    memcpy(parsed_region_chan->CountryCode, CountryInfo->CountryCode,
           COUNTRY_CODE_LEN);

    NoOfSubband = (CountryInfo->Len - COUNTRY_CODE_LEN) /
        sizeof(IEEEtypes_SubbandSet_t);

    for (j = 0, lastChan = 0; j < NoOfSubband; j++) {

        if (CountryInfo->Subband[j].FirstChan <= lastChan) {
            /*Step2&3. Check First Chan Num increment and no overlap */
            wlan_debug3("11D: Chan[%d>%d] Overlap\n",
                   CountryInfo->Subband[j].FirstChan, lastChan);
            continue;
        }

        firstChan = CountryInfo->Subband[j].FirstChan;
        NoOfChan = CountryInfo->Subband[j].NoOfChan;

        for (i = 0; idx < MAX_NO_OF_CHAN && i < NoOfChan; i++) {
            /*step4: channel is supported? */

            if (wlan_get_chan_11d(band, firstChan, i, &curChan)
                == FALSE) {
                /* Chan is not found in UN table */
                wlan_debug3("chan is not supported: %d \n", i);
                break;
            }

            lastChan = curChan;

            /*step5: We don't need to Check if curChan is supported by mrvl in region */
            parsed_region_chan->chanPwr[idx].chan = curChan;
            parsed_region_chan->chanPwr[idx].pwr =
                CountryInfo->Subband[j].MaxTxPwr;
            idx++;
        }

        /*Step6: Add other checking if any */

    }

    parsed_region_chan->NoOfChan = idx;

    wlan_debug3("NoOfChan=%x\n", parsed_region_chan->NoOfChan);
 //   HEXDUMP("11D:parsed_region_chan:", (s8 *) parsed_region_chan,
//            2 + COUNTRY_CODE_LEN + sizeof(parsed_region_chan_11d_t) * idx);

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function calculates the scan type for channels
 *  @param chan                 chan number
 *  @param parsed_region_chan   pointer to parsed_region_chan_11d_t     
 *  @return 	                PASSIVE if chan is unknown; ACTIVE if chan is known
*/
u8
wlan_get_scan_type_11d(u8 chan, parsed_region_chan_11d_t * parsed_region_chan)
{
    u8 scan_type = HostCmd_SCAN_TYPE_PASSIVE;

    ENTER();

    if (wlan_channel_known_11d(chan, parsed_region_chan)) {
        wlan_debug3( "11D: Found and do Active Scan\n");
        scan_type = HostCmd_SCAN_TYPE_ACTIVE;
    } else {
        wlan_debug3( "11D: Not Find and do Passive Scan\n");
    }

    LEAVE();
    return scan_type;

}

/** 
 *  @brief This function gets if 11D is enabled
 *  @param priv       pointer to wlan_private
 *  @return 	      ENABLE_11D;DISABLE_11D
*/
state_11d_t
wlan_get_state_11d(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    wlan_802_11d_state_t *state = &Adapter->State11D;
    return (state->Enable11D);
}

/** 
 *  @brief initialize internal variable for 11D
 *  @param priv       pointer to wlan_private
 *  @return 	      N/A
*/
void
wlan_init_11d(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    wlan_802_11d_state_t *state = &Adapter->State11D;

    state->Enable11D = DISABLE_11D;

    memset(&(priv->adapter->parsed_region_chan), 0,
           sizeof(parsed_region_chan_11d_t));

    return;
}

/** 
 *  @brief This function enable/disable 11D
 *  @param priv       pointer to wlan_private
 *  @param flag       enable/disable flag
 *  @return 	      WLAN_STATUS_SUCCESS; WLAN_STATUS_FAILURE
*/
int
wlan_enable_11d(wlan_private * priv, state_11d_t flag)
{
    wlan_adapter *Adapter = priv->adapter;
    wlan_802_11d_state_t *state = &Adapter->State11D;
    int ret;
    state_11d_t enable = flag;

    ENTER();

    state->Enable11D = flag;

    /* send cmd to FW to enable/disable 11D fucntion in FW */
    ret = PrepareAndSendCommand(priv,
                                HostCmd_CMD_802_11_SNMP_MIB,
                                HostCmd_ACT_SET,
                                HostCmd_OPTION_WAITFORRSP,
                                OID_802_11D_ENABLE, &enable);
    if (ret) {
        wlan_debug3( "11D: Fail to enable 11D \n");
    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function sets DOMAIN INFO to FW
 *  @param priv       pointer to wlan_private
 *  @return 	      WLAN_STATUS_SUCCESS; WLAN_STATUS_FAILURE
*/
int
wlan_set_domain_info_11d(wlan_private * priv)
{
    int ret;

    if (!wlan_get_state_11d(priv)) {
        wlan_debug3( "11D: dnld domain Info with 11d disabled\n");
        return WLAN_STATUS_SUCCESS;
    }

    ret = PrepareAndSendCommand(priv, HostCmd_CMD_802_11D_DOMAIN_INFO,
                                HostCmd_ACT_GEN_SET,
                                HostCmd_OPTION_WAITFORRSP, 0, NULL);
    if (ret) {
        wlan_debug3( "11D: Fail to dnld domain Info\n");
    }

    LEAVE();
    return ret;
}

/** 
 *  @brief This function setups scan channels
 *  @param priv       pointer to wlan_private
 *  @param band       band
 *  @return 	      WLAN_STATUS_SUCCESS
*/
int
wlan_set_universaltable(wlan_private * priv, u8 band)
{
    wlan_adapter *Adapter = priv->adapter;
    u16 size = sizeof(CHANNEL_FREQ_POWER);
    u16 i = 0;

    ENTER();

    memset(Adapter->universal_channel, 0, sizeof(Adapter->universal_channel));

    {
        Adapter->universal_channel[i].NrCFP =
            sizeof(channel_freq_power_UN_BG) / size;
        wlan_debug3("11D: BG-band NrCFP=%d\n",
               Adapter->universal_channel[i].NrCFP);

        Adapter->universal_channel[i].CFP = channel_freq_power_UN_BG;
        Adapter->universal_channel[i].Valid = TRUE;
        Adapter->universal_channel[i].Region = UNIVERSAL_REGION_CODE;
        Adapter->universal_channel[i].Band = band;
        i++;
    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function implements command CMD_802_11D_DOMAIN_INFO
 *  @param priv       pointer to wlan_private
 *  @param cmd        pointer to cmd buffer
 *  @param cmdno      cmd ID
 *  @param CmdOption  cmd action 
 *  @return 	      WLAN_STATUS_SUCCESS
*/
int wlan_cmd_802_11d_domain_info(wlan_private * priv,HostCmd_DS_COMMAND * cmd, u16 cmdno,u16 CmdOption)
{
    HostCmd_DS_802_11D_DOMAIN_INFO *pDomainInfo = &cmd->params.domaininfo;
    MrvlIEtypes_DomainParamSet_t *domain = &pDomainInfo->Domain;
    wlan_adapter *Adapter = priv->adapter;
    u8 NoOfSubband = Adapter->DomainReg.NoOfSubband;

    ENTER();

    wlan_debug3("NoOfSubband=%x\n", NoOfSubband);

    cmd->Command = wlan_cpu_to_le16(cmdno);
    pDomainInfo->Action = wlan_cpu_to_le16(CmdOption);
    if (CmdOption == HostCmd_ACT_GET) {
        cmd->Size = wlan_cpu_to_le16(sizeof(pDomainInfo->Action) + S_DS_GEN);
   //     HEXDUMP("11D: 802_11D_DOMAIN_INFO:", (u8 *) cmd, (int) (cmd->Size));
        LEAVE();
        return WLAN_STATUS_SUCCESS;
    }

    domain->Header.Type = wlan_cpu_to_le16(TLV_TYPE_DOMAIN);
    memcpy(domain->CountryCode, Adapter->DomainReg.CountryCode,
           sizeof(domain->CountryCode));

    domain->Header.Len =
        wlan_cpu_to_le16(NoOfSubband * sizeof(IEEEtypes_SubbandSet_t) +
                         sizeof(domain->CountryCode));

    if (NoOfSubband) {
        memcpy(domain->Subband, Adapter->DomainReg.Subband,
               NoOfSubband * sizeof(IEEEtypes_SubbandSet_t));

        cmd->Size = wlan_cpu_to_le16(sizeof(pDomainInfo->Action) +
                                     domain->Header.Len +
                                     sizeof(MrvlIEtypesHeader_t) + S_DS_GEN);
    } else {
        cmd->Size = wlan_cpu_to_le16(sizeof(pDomainInfo->Action) + S_DS_GEN);
    }

 //   HEXDUMP("11D:802_11D_DOMAIN_INFO:", (u8 *) cmd, (int) (cmd->Size));

    LEAVE();

    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function implements private cmd: enable/disable 11D
 *  @param priv    pointer to wlan_private
 *  @param wrq     pointer to user data 
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int wlan_cmd_enable_11d(wlan_private * priv, void*wrq)
{
#if 0 
    int data = 0;
    int *val;
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    data = *((int *) (wrq->u.name + SUBCMD_OFFSET));

    wlan_debug3("Enable 11D: %s\n",
           (data == CMD_ENABLED) ? "Enable" : "Disable");
    switch (data) {
    case CMD_ENABLED:
        wlan_enable_11d(priv, ENABLE_11D);
        break;
    case CMD_DISABLED:
        wlan_enable_11d(priv, DISABLE_11D);
        break;
    default:
        break;
    }

    data =
        (Adapter->State11D.Enable11D ==
         ENABLE_11D) ? CMD_ENABLED : CMD_DISABLED;
    val = (int *) wrq->u.name;
    *val = data;
 #endif
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function parses countryinfo from AP and download country info to FW
 *  @param priv    pointer to wlan_private
 *  @param resp    pointer to command response buffer
 *  @return 	   WLAN_STATUS_SUCCESS; WLAN_STATUS_FAILURE
 */
int wlan_ret_802_11d_domain_info(wlan_private * priv, HostCmd_DS_COMMAND * resp)
{
    HostCmd_DS_802_11D_DOMAIN_INFO_RSP
        * domaininfo = &resp->params.domaininforesp;
    MrvlIEtypes_DomainParamSet_t * domain = &domaininfo->Domain;
    u16 Action = wlan_le16_to_cpu(domaininfo->Action);
    s16 ret = WLAN_STATUS_SUCCESS;
    u8 NoOfSubband = 0;

    ENTER();

  //  HEXDUMP("11D DOMAIN Info Rsp Data:", (u8 *) resp, resp->Size);

    NoOfSubband =
        (wlan_le16_to_cpu(domain->Header.Len) -
         3) / sizeof(IEEEtypes_SubbandSet_t);
    /* countrycode 3 bytes */

    wlan_debug3( "11D Domain Info Resp: NoOfSubband=%d\n", NoOfSubband);

    if (NoOfSubband > MRVDRV_MAX_SUBBAND_802_11D) {
        wlan_debug3("Invalid Numrer of Subband returned!!\n");
        return WLAN_STATUS_FAILURE;
    }

    switch (Action) {
    case HostCmd_ACT_SET:      /*Proc Set Action */
        break;

    case HostCmd_ACT_GET:
        break;
    default:
        wlan_debug3("Invalid Action:%d\n", domaininfo->Action);
        ret = WLAN_STATUS_FAILURE;
        break;
    }

    LEAVE();
    return ret;
}

/** 
 *  @brief This function parses countryinfo from AP and download country info to FW
 *  @param priv    pointer to wlan_private
 *  @return 	   WLAN_STATUS_SUCCESS; WLAN_STATUS_FAILURE
 */
int
wlan_parse_dnld_countryinfo_11d(wlan_private * priv)
{
    int ret;
    wlan_adapter *Adapter = priv->adapter;

    ENTER();

    if (Adapter->MediaConnectStatus == WlanMediaStateConnected) {
        /* Skip new 11d download when roaming */
        return WLAN_STATUS_SUCCESS;
    }

    if (wlan_get_state_11d(priv) == ENABLE_11D) {

        memset(&Adapter->parsed_region_chan, 0,
               sizeof(parsed_region_chan_11d_t));

        ret =
            wlan_parse_domain_info_11d(&Adapter->pAttemptedBSSDesc->
                                       CountryInfo, 0,
                                       &Adapter->parsed_region_chan);

        if (ret == WLAN_STATUS_FAILURE) {
            wlan_debug3( "11D: Err Parse domain_info from AP..\n");
            LEAVE();
            return ret;
        }

        memset(&Adapter->DomainReg, 0, sizeof(wlan_802_11d_domain_reg_t));
        wlan_generate_domain_info_11d(&Adapter->parsed_region_chan,
                                      &Adapter->DomainReg);

        ret = wlan_set_domain_info_11d(priv);

        if (ret) {
            wlan_debug3( "11D: Err set domainInfo to FW\n");
            LEAVE();
            return ret;
        }
    }
    LEAVE();
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function generates 11D info from user specified regioncode and download to FW
 *  @param priv    pointer to wlan_private
 *  @return 	   WLAN_STATUS_SUCCESS; WLAN_STATUS_FAILURE
 */
int
wlan_create_dnld_countryinfo_11d(wlan_private * priv)
{
    int ret;
    wlan_adapter *Adapter = priv->adapter;
    REGION_CHANNEL *region_chan;
    u8 j;

    ENTER();
    wlan_debug3("11D:CurBssParams.Band[%d]\n", Adapter->CurBssParams.band);

    if (wlan_get_state_11d(priv) == ENABLE_11D) {
        /* update parsed_region_chan_11; dnld domaininf to FW */

        for (j = 0; j < sizeof(Adapter->region_channel) /
             sizeof(Adapter->region_channel[0]); j++) {
            region_chan = &Adapter->region_channel[j];

            wlan_debug3( "11D:[%d] region_chan->Band[%d]\n", j,
                   region_chan->Band);

            if (!region_chan || !region_chan->Valid || !region_chan->CFP)
                continue;
            if (region_chan->Band != Adapter->CurBssParams.band)
                continue;
            break;
        }

        if (j >= sizeof(Adapter->region_channel) /
            sizeof(Adapter->region_channel[0])) {
            wlan_debug3("11D:region_chan not found. Band[%d]\n",
                   Adapter->CurBssParams.band);
            LEAVE();
            return WLAN_STATUS_FAILURE;
        }

        memset(&Adapter->parsed_region_chan, 0,
               sizeof(parsed_region_chan_11d_t));
        wlan_generate_parsed_region_chan_11d(region_chan,
                                             &Adapter->parsed_region_chan);

        memset(&Adapter->DomainReg, 0, sizeof(wlan_802_11d_domain_reg_t));
        wlan_generate_domain_info_11d(&Adapter->parsed_region_chan,
                                      &Adapter->DomainReg);

        ret = wlan_set_domain_info_11d(priv);

        if (ret) {
            wlan_debug3("11D: Err set domainInfo to FW\n");
            LEAVE();
            return ret;
        }

    }

    LEAVE();
    return WLAN_STATUS_SUCCESS;
}
