/** @file wlan_wmm.h
 * @brief This file contains related macros, enum, and struct
 * of wmm functionalities
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/****************************************************
Change log:
    09/26/05: add Doxygen format comments 
    04/06/06: Add TSPEC, queue metrics, and MSDU expiry support
****************************************************/

#ifndef __WLAN_WMM_H
#define __WLAN_WMM_H
#include "wlan_types.h"
#include "wlan_defs.h"
/** Custom indiciation message sent to the application layer for WMM changes */
#define WMM_CONFIG_CHANGE_INDICATION  "WMM_CONFIG_CHANGE.indication"

/** Highest priority setting for a packet (uses voice AC) */
#define WMM_HIGHEST_PRIORITY  7


/** struct of WMM DESC */
struct sk_buff {
	/* These two members must be first. */
	struct sk_buff		*next;
	struct sk_buff		*prev;
	unsigned int		len;
	unsigned char		*head,*data;
};
typedef struct
{
    u8 required;
    u8 enabled;
    u8 packetsQueued;
    u8 queueStopped;
    u8 downlinkblock;
    struct rt_semaphore flowcrsem;
    struct sk_buff txSkbQ;
   // WmmAcStatus_t acStatus[MAX_AC_QUEUES];
   // wlan_wmm_ac_e acDowngradedVals[MAX_AC_QUEUES];

    /** wmm queue priority table*/
    //u8 queuePriority[MAX_AC_QUEUES];

   // u8 qosinfo;
} __ATTRIB_PACK__ WMM_DESC;
#ifdef __KERNEL__

extern u8 wmm_compute_driver_packet_delay(const struct sk_buff *skb);
#endif

extern int sendWMMStatusChangeCmd(wlan_private * priv);
extern int wmm_lists_empty(wlan_private * priv);
extern void wmm_process_tx(wlan_private * priv);

extern void wmm_init(wlan_private * priv);
extern void wmm_setup_queues(wlan_private * priv);
extern void wmm_start_queue(wlan_private * priv);
extern void wmm_stop_queue(wlan_private * priv);
extern int wmm_is_queue_stopped(wlan_private * priv);

extern void wmm_process_fw_iface_tx_xfer_start(wlan_private * priv);
extern void wmm_process_fw_iface_tx_xfer_end(wlan_private * priv);
extern void wmm_process_app_iface_tx(wlan_private * priv);
extern wlan_wmm_ac_e wmm_convert_tos_to_ac(int tos);
extern wlan_wmm_ac_e wmm_downgrade_ac(wlan_private * priv,wlan_wmm_ac_e acVal);

extern u32 wlan_wmm_process_association_req(wlan_private * priv,
                                            u8 ** ppAssocBuf,
                                            IEEEtypes_WmmParameter_t *
                                            pWmmIE);

/* 
 *  Functions used in the cmd handling routine
 */
extern int wlan_cmd_wmm_get_status(wlan_private * priv,
                                   HostCmd_DS_COMMAND * cmd, void *InfoBuf);
extern int wlan_cmd_wmm_addts_req(wlan_private * priv,
                                  HostCmd_DS_COMMAND * cmd, void *InfoBuf);
extern int wlan_cmd_wmm_delts_req(wlan_private * priv,
                                  HostCmd_DS_COMMAND * cmd, void *InfoBuf);
extern int wlan_cmd_wmm_queue_config(wlan_private * priv,
                                     HostCmd_DS_COMMAND * cmd, void *InfoBuf);
extern int wlan_cmd_wmm_queue_stats(wlan_private * priv,
                                    HostCmd_DS_COMMAND * cmd, void *InfoBuf);

/* 
 *  Functions used in the cmdresp handling routine
 */
extern int wlan_cmdresp_wmm_get_status(wlan_private * priv,
                                       const HostCmd_DS_COMMAND * resp);
extern int wlan_cmdresp_wmm_addts_req(wlan_private * priv,
                                      const HostCmd_DS_COMMAND * resp);
extern int wlan_cmdresp_wmm_delts_req(wlan_private * priv,
                                      const HostCmd_DS_COMMAND * resp);
extern int wlan_cmdresp_wmm_queue_config(wlan_private * priv,
                                         const HostCmd_DS_COMMAND * resp);
extern int wlan_cmdresp_wmm_queue_stats(wlan_private * priv,
                                        const HostCmd_DS_COMMAND * resp);

/* 
 * IOCTLs 
 */
//extern int wlan_wmm_enable_ioctl(wlan_private * priv, struct iwreq *wrq);
//extern int wlan_wmm_queue_status_ioctl(wlan_private * priv,struct iwreq *wrq);

//extern int wlan_wmm_addts_req_ioctl(wlan_private * priv, struct iwreq *wrq);
//extern int wlan_wmm_delts_req_ioctl(wlan_private * priv, struct iwreq *wrq);
//extern int wlan_wmm_queue_config_ioctl(wlan_private * priv,struct iwreq *wrq);
//extern int wlan_wmm_queue_stats_ioctl(wlan_private * priv, struct iwreq *wrq);
#endif /* __WLAN_WMM_H */
