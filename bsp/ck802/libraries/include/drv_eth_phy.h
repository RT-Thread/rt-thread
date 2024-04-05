/**
 * Copyright (C) 2016 CSI Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _CSI_ETH_PHY_H_
#define _CSI_ETH_PHY_H_

#include "drv_eth.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *eth_phy_handle_t;

#define CSI_ETH_PHY_API_VERSION CSI_ETH_VERSION_MAJOR_MINOR(2,1)  /* API version */


#define _CSI_Driver_ETH_PHY_(n)      Driver_ETH_PHY##n
#define  CSI_Driver_ETH_PHY_(n) _CSI_Driver_ETH_PHY_(n)


/****** Ethernet PHY Mode *****/
#define CSI_ETH_PHY_SPEED_Pos            0
#define CSI_ETH_PHY_SPEED_Msk           (3UL                 << CSI_ETH_PHY_SPEED_Pos)
#define CSI_ETH_PHY_SPEED_10M           (CSI_ETH_SPEED_10M   << CSI_ETH_PHY_SPEED_Pos)  ///< 10 Mbps link speed
#define CSI_ETH_PHY_SPEED_100M          (CSI_ETH_SPEED_100M  << CSI_ETH_PHY_SPEED_Pos)  ///< 100 Mbps link speed
#define CSI_ETH_PHY_SPEED_1G            (CSI_ETH_SPEED_1G    << CSI_ETH_PHY_SPEED_Pos)  ///< 1 Gpbs link speed
#define CSI_ETH_PHY_DUPLEX_Pos           2
#define CSI_ETH_PHY_DUPLEX_Msk          (1UL                 << CSI_ETH_PHY_DUPLEX_Pos)
#define CSI_ETH_PHY_DUPLEX_HALF         (CSI_ETH_DUPLEX_HALF << CSI_ETH_PHY_DUPLEX_Pos) ///< Half duplex link
#define CSI_ETH_PHY_DUPLEX_FULL         (CSI_ETH_DUPLEX_FULL << CSI_ETH_PHY_DUPLEX_Pos) ///< Full duplex link
#define CSI_ETH_PHY_AUTO_NEGOTIATE      (1UL << 3)                                      ///< Auto Negotiation mode
#define CSI_ETH_PHY_LOOPBACK            (1UL << 4)                                      ///< Loop-back test mode
#define CSI_ETH_PHY_ISOLATE             (1UL << 5)                                      ///< Isolate PHY from MII/RMII interface

typedef int32_t (*csi_eth_phy_read_t)  (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data); ///< Read Ethernet PHY Register.
typedef int32_t (*csi_eth_phy_write_t) (uint8_t phy_addr, uint8_t reg_addr, uint16_t  data); ///< Write Ethernet PHY Register.

typedef struct {
    csi_eth_phy_read_t  phy_read;
    csi_eth_phy_write_t phy_write;
    eth_link_info_t     link_info;
}eth_phy_priv_t;

// Function documentation
/**
  \brief       Get driver version.
  \param[in]   handle  ethernet phy handle
  \return      driver version
*/
csi_drv_version_t csi_eth_phy_get_version(eth_phy_handle_t handle);

/**
  \brief       Initialize Ethernet PHY Device.
  \param[in]   fn_read
  \param[in]   fn_write
  \return      ethernet phy handle
*/
eth_phy_handle_t csi_eth_phy_initialize(csi_eth_phy_read_t fn_read, csi_eth_phy_write_t fn_write);

/**
  \brief       De-initialize Ethernet PHY Device.
  \param[in]   handle  ethernet phy handle
  \return      error code
*/
int32_t csi_eth_phy_uninitialize(eth_phy_handle_t handle);

/**
  \brief       Control Ethernet PHY Device Power.
  \param[in]   handle  ethernet phy handle
  \param[in]   state  Power state
  \return      error code
*/
int32_t csi_eth_phy_power_control(eth_phy_handle_t handle, eth_power_state_t state);

/**
  \brief       Set Ethernet Media Interface.
  \param[in]   handle  ethernet phy handle
  \param[in]   interface  Media Interface type
  \return      error code
*/
int32_t csi_eth_phy_set_interface(eth_phy_handle_t handle, uint32_t interface);

/**
  \brief       Set Ethernet PHY Device Operation mode.
  \param[in]   handle  ethernet phy handle
  \param[in]   mode  Operation Mode
  \return      error code
*/
int32_t csi_eth_phy_set_mode(eth_phy_handle_t handle, uint32_t mode);

/**
  \brief       Get Ethernet PHY Device Link state.
  \param[in]   handle  ethernet phy handle
  \return      current link status \ref eth_link_state_t
*/
eth_link_state_t csi_eth_phy_get_linkstate(eth_phy_handle_t handle);

/**
  \brief       Get Ethernet PHY Device Link information.
  \param[in]   handle  ethernet phy handle
  \return      current link parameters \ref eth_link_info_t
*/
eth_link_info_t csi_eth_phy_get_linkinfo(eth_phy_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif

