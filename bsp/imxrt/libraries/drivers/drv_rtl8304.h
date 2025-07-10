/*
*  Copyright (c) 2006-2020, Chukie
*
*  SPDX-License-Identifier: Apache-2.0
*
*  @file     : drv_rtl8304.h
*
*  @brief    : Realtek RTL8304 driver
*
*
*  Change Logs:
*  Date           Author          Notes
*  2022-07-16     weiyf           created
*/
/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __DRV_RTL8304_H__
#define __DRV_RTL8304_H__
/* Includes -----------------------------------------------------------------*/
#include "rtthread.h"


#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/
/* Exported types -----------------------------------------------------------*/

#define CPU_TAG_ENABLE    1
#define CPU_TAG_LEN       4
#define CPU_TAG_OFFSET    12
#define CPU_TAG_PORT_MAP(port)    (1 << (port))
#define CPU_TAG_ETHER_TYPE        (0x9988) //Realtek proprietary number

/**
 * @brief RTL8309 & RTL8304 share the same PHY register
 * 
 */
typedef enum
{
    RTL_PHY_0 = 0,
    RTL_PHY_1,
    RTL_PHY_2,
    RTL_PHY_3,
    RTL_PHY_4,
    RTL_PHY_5,
    RTL_PHY_6,
    RTL_PHY_7,
    RTL_PHY_8,
} rtl_phy_t;

/**
 * @brief RTL8304 switch & RMII port mapping to RTL8309 port
 * 
 */
typedef enum
{
    /* switch port 0 */
    RTL_PORT_0 = 0,
    /* switch port 1 */
    RTL_PORT_1 = 3,
    /* switch port 2 */
    RTL_PORT_2 = 4,
    /* RMII port */
    RTL_PORT_3 = 8,
} rtl_port_t;

/**
 * @brief RTL8309 & RTL8304 register
 * 
 */
typedef enum
{
    RTL_REG_0 = 0,
    RTL_REG_1,
    RTL_REG_2,
    RTL_REG_3,
    RTL_REG_4,
    RTL_REG_5,
    RTL_REG_6,
    RTL_REG_7,
    RTL_REG_8,
    RTL_REG_9,
    RTL_REG_10,
    RTL_REG_11,
    RTL_REG_12,
    RTL_REG_13,
    RTL_REG_14,
    RTL_REG_15,
    RTL_REG_16,
    RTL_REG_17,
    RTL_REG_18,
    RTL_REG_19,
    RTL_REG_20,
    RTL_REG_21,
    RTL_REG_22,
    RTL_REG_23,
    RTL_REG_24,
    RTL_REG_25,
    RTL_REG_26,
    RTL_REG_27,
    RTL_REG_28,
    RTL_REG_29,
    RTL_REG_30,
    RTL_REG_31,
} rtl_reg_t;

/**
 * @brief RTL8309 & RTL8304 page
 * 
 */
typedef enum
{
    RTL_PAGE_0 = 0,
    RTL_PAGE_1,
    RTL_PAGE_2,
    RTL_PAGE_3,
    RTL_PAGE_4,
    RTL_PAGE_5,
    RTL_PAGE_6,
    RTL_PAGE_7,
    RTL_PAGE_8,
    RTL_PAGE_9,
    RTL_PAGE_10,
    RTL_PAGE_11,
    RTL_PAGE_12,
    RTL_PAGE_13,
    RTL_PAGE_14,
    RTL_PAGE_15,
    RTL_PAGE_16,
    RTL_PAGE_17,
} rtl_page_t;

/**
 * @brief RTL8309 & RTL8304 port link status
 * 
 */
typedef enum
{
    RTL_LINK_DOWN = 0,
    RTL_LINK_UP,
} rtl_link_t;

/**
 * @brief RTL8309 & RTL8304 port speed status
 * 
 */
typedef enum
{
    RTL_SPEED_10M = 0,
    RTL_SPEED_100M,
} rtl_speed_t;

/**
 * @brief RTL8309 & RTL8304 port duplex status
 * 
 */
typedef enum
{
    RTL_DUPLEX_HALF = 0,
    RTL_DUPLEX_FULL,
} rtl_duplex_t;

typedef enum
{
    RTL_LED_LINK_ACT_SPEED  = 0,
    RTL_LED_LINK_ACT_DUPLEX,
    RTL_LED_LINK_ACT_DUPLEX_COLLISION,
    RTL_LED_LINK_SPEEDLINK_ACT,
    RTL_LED_LINK_DUPLEXLINK_ACT,
    RTL_LED_LINK_DUPLEX_COLLISIONLINK_ACT,
    RTL_LED_LINK_SPEED100_ACTSPEED10,
} rtl_led_t;

enum RTL_ENABLE_STATUS
{
	RTL_DISABLED = 0,
	RTL_ENABLED,
	RTL_ENABLE_END
};

typedef enum
{
    PORT0 = RTL_PORT_0,
    PORT1 = RTL_PORT_1,
    PORT2 = RTL_PORT_2,
    PORT3 = RTL_PORT_3,
} switch_port_t;

struct switch_cpu_tag {
    rt_uint16_t ether_type;
    rt_uint8_t  protocol;
    rt_uint8_t  port_map;
};

typedef enum {
    ETH_SWITCH,
    ETH_SEPARATE,    
}eEthMode;



/* Exported constants -------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
rtl_link_t rtl_get_link_status(rtl_port_t port);
rtl_speed_t rtl_get_speed_status(rtl_port_t port);
rtl_duplex_t rtl_get_duplex_status(rtl_port_t port);
void rtl_set_storm_filter(rtl_port_t port);
void rtl_set_led_status(rtl_led_t status);
int rtl_set_egr_rate(rtl_port_t port, rt_uint32_t rate);
rt_uint16_t rtl_get_id1(rtl_phy_t phy);
rt_uint16_t rtl_get_id2(rtl_phy_t phy);
int rtl_init(eEthMode eth_mode);
void rtl_external_port_isolation_set(uint32_t enabled);
void rtl_external_cpu_tag_insert_en(uint32_t enabled);
void rtl_external_cpu_tag_remove_en(uint32_t enabled);
rtl_link_t rtl_get_link_status(rtl_port_t port);


#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*__DRV_RTL8304_H__*/
/* End of file****************************************************************/
