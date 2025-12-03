/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_rmac_phy.h"
#include "r_ether_phy_api.h"
#include "r_layer3_switch.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
#ifndef ETHER_PHY_LSI_TYPE_KIT_COMPONENT
  #define ETHER_PHY_LSI_TYPE_KIT_COMPONENT ETHER_PHY_LSI_TYPE_DEFAULT
#endif

#ifndef rmac_phy_target_rtl8211_initialize
void rmac_phy_target_rtl8211_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
#endif

#ifndef rmac_phy_target_rtl8211_is_support_link_partner_ability
bool rmac_phy_target_rtl8211_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex);
#endif

/** ETHER_PHY on RMAC_PHY Instance. */
extern const ether_phy_instance_t g_rmac_phy1;

/** Access the Ethernet PHY instance using these structures when calling API functions directly (::p_api is not used). */
extern rmac_phy_instance_ctrl_t g_rmac_phy1_ctrl;
extern const ether_phy_cfg_t g_rmac_phy1_cfg;
extern const rmac_phy_extended_cfg_t g_rmac_phy1_extended_cfg;
#ifndef ETHER_PHY_LSI_TYPE_KIT_COMPONENT
  #define ETHER_PHY_LSI_TYPE_KIT_COMPONENT ETHER_PHY_LSI_TYPE_DEFAULT
#endif

#ifndef rmac_phy_target_rtl8211_initialize
void rmac_phy_target_rtl8211_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
#endif

#ifndef rmac_phy_target_rtl8211_is_support_link_partner_ability
bool rmac_phy_target_rtl8211_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex);
#endif

/** ETHER_PHY on RMAC_PHY Instance. */
extern const ether_phy_instance_t g_rmac_phy0;

/** Access the Ethernet PHY instance using these structures when calling API functions directly (::p_api is not used). */
extern rmac_phy_instance_ctrl_t g_rmac_phy0_ctrl;
extern const ether_phy_cfg_t g_rmac_phy0_cfg;
extern const rmac_phy_extended_cfg_t g_rmac_phy0_extended_cfg;
#ifndef NULL
void NULL(ether_switch_callback_args_t * p_args);
#endif
#ifndef NULL
void NULL(ether_switch_callback_args_t * p_args);
#endif
#ifndef NULL
void NULL(ether_switch_callback_args_t * p_args);
#endif

/** Ethernet Switch on Layer3 Switch Instance. */
extern const ether_switch_instance_t g_layer3_switch0;

/** Access the Layer3 Switch instance using these structures when calling API functions directly (::p_api is not used). */
extern layer3_switch_instance_ctrl_t g_layer3_switch0_ctrl;
extern const ether_switch_cfg_t g_layer3_switch0_cfg;
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
