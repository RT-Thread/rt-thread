/** @file wlan_11d.h
 *  @brief This header file contains data structures and 
 *  function declarations of 802.11d   
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/*************************************************************
Change log:
	09/26/05: add Doxygen format comments 
 ************************************************************/

#ifndef _WLAN_11D_
#define _WLAN_11D_

#define MAX_CHAN_NUM				255

#define UNIVERSAL_REGION_CODE			0xff

/** (Beaconsize(256)-5(IEId,len,contrystr(3))/3(FirstChan,NoOfChan,MaxPwr) 
 */
#define MAX_NO_OF_CHAN 				40
typedef struct _REGION_CHANNEL *PREGION_CHANNEL;

typedef enum
{
    DISABLE_11D = 0,
    ENABLE_11D = 1,
} state_11d_t;

/** domain regulatory information */
typedef struct _wlan_802_11d_domain_reg
{
        /** country Code*/
    u8 CountryCode[COUNTRY_CODE_LEN];
        /** No. of subband*/
    u8 NoOfSubband;
    IEEEtypes_SubbandSet_t Subband[MRVDRV_MAX_SUBBAND_802_11D];
} wlan_802_11d_domain_reg_t;

typedef struct _chan_power_11d
{
    u8 chan;
    u8 pwr;
} __ATTRIB_PACK__ chan_power_11d_t;

typedef struct _parsed_region_chan_11d
{
    u8 band;
    u8 region;
    s8 CountryCode[COUNTRY_CODE_LEN];
    chan_power_11d_t chanPwr[MAX_NO_OF_CHAN];
    u8 NoOfChan;
} __ATTRIB_PACK__ parsed_region_chan_11d_t;

/** Data for state machine */
typedef struct _wlan_802_11d_state
{
        /** True for Enabling  11D*/
    BOOLEAN Enable11D;
} wlan_802_11d_state_t;

typedef struct _region_code_mapping
{
    s8 region[COUNTRY_CODE_LEN];
    u8 code;
} region_code_mapping_t;

/* function prototypes*/
int wlan_generate_domain_info_11d(parsed_region_chan_11d_t *
                                  parsed_region_chan,
                                  wlan_802_11d_domain_reg_t * domaininfo);

int wlan_parse_domain_info_11d(IEEEtypes_CountryInfoFullSet_t * CountryInfo,
                               u8 band,
                               parsed_region_chan_11d_t * parsed_region_chan);

u8 wlan_get_scan_type_11d(u8 chan,
                          parsed_region_chan_11d_t * parsed_region_chan);

u32 chan_2_freq(u8 chan, u8 band);

int wlan_set_domain_info_11d(wlan_private * priv);

state_11d_t wlan_get_state_11d(wlan_private * priv);

void wlan_init_11d(wlan_private * priv);

int wlan_enable_11d(wlan_private * priv, state_11d_t flag);

int wlan_set_universaltable(wlan_private * priv, u8 band);

void wlan_generate_parsed_region_chan_11d(PREGION_CHANNEL region_chan,
                                          parsed_region_chan_11d_t *
                                          parsed_region_chan);

int wlan_cmd_802_11d_domain_info(wlan_private * priv,
                                 HostCmd_DS_COMMAND * cmd, u16 cmdno,
                                 u16 CmdOption);

//int wlan_cmd_enable_11d(wlan_private * priv, struct iwreq *wrq);

int wlan_ret_802_11d_domain_info(wlan_private * priv,
                                 HostCmd_DS_COMMAND * resp);

int wlan_parse_dnld_countryinfo_11d(wlan_private * priv);

int wlan_create_dnld_countryinfo_11d(wlan_private * priv);

#endif /* _WLAN_11D_ */
