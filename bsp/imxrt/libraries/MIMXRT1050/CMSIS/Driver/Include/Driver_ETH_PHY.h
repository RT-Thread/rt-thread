/*
 * Copyright (c) 2013-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Date:        2. Feb 2017
 * $Revision:    V2.1
 *
 * Project:      Ethernet PHY (Physical Transceiver) Driver definitions
 */

/* History:
 *  Version 2.1
 *    ARM_ETH_LINK_INFO made volatile
 *  Version 2.0
 *    changed parameter "mode" in function ARM_ETH_PHY_SetMode
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *    Changed return values of some functions to int32_t
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_ETH_PHY_H_
#define DRIVER_ETH_PHY_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_ETH.h"

#define ARM_ETH_PHY_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,1)  /* API version */


#define _ARM_Driver_ETH_PHY_(n)      Driver_ETH_PHY##n
#define  ARM_Driver_ETH_PHY_(n) _ARM_Driver_ETH_PHY_(n)


/****** Ethernet PHY Mode *****/
#define ARM_ETH_PHY_SPEED_Pos            0
#define ARM_ETH_PHY_SPEED_Msk           (3UL                 << ARM_ETH_PHY_SPEED_Pos)
#define ARM_ETH_PHY_SPEED_10M           (ARM_ETH_SPEED_10M   << ARM_ETH_PHY_SPEED_Pos)  ///< 10 Mbps link speed
#define ARM_ETH_PHY_SPEED_100M          (ARM_ETH_SPEED_100M  << ARM_ETH_PHY_SPEED_Pos)  ///< 100 Mbps link speed
#define ARM_ETH_PHY_SPEED_1G            (ARM_ETH_SPEED_1G    << ARM_ETH_PHY_SPEED_Pos)  ///< 1 Gpbs link speed
#define ARM_ETH_PHY_DUPLEX_Pos           2
#define ARM_ETH_PHY_DUPLEX_Msk          (1UL                 << ARM_ETH_PHY_DUPLEX_Pos)
#define ARM_ETH_PHY_DUPLEX_HALF         (ARM_ETH_DUPLEX_HALF << ARM_ETH_PHY_DUPLEX_Pos) ///< Half duplex link
#define ARM_ETH_PHY_DUPLEX_FULL         (ARM_ETH_DUPLEX_FULL << ARM_ETH_PHY_DUPLEX_Pos) ///< Full duplex link
#define ARM_ETH_PHY_AUTO_NEGOTIATE      (1UL << 3)                                      ///< Auto Negotiation mode
#define ARM_ETH_PHY_LOOPBACK            (1UL << 4)                                      ///< Loop-back test mode
#define ARM_ETH_PHY_ISOLATE             (1UL << 5)                                      ///< Isolate PHY from MII/RMII interface


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_ETH_PHY_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
/**
  \fn          int32_t ARM_ETH_PHY_Initialize (ARM_ETH_PHY_Read_t  fn_read,
                                               ARM_ETH_PHY_Write_t fn_write)
  \brief       Initialize Ethernet PHY Device.
  \param[in]   fn_read   Pointer to \ref ARM_ETH_MAC_PHY_Read
  \param[in]   fn_write  Pointer to \ref ARM_ETH_MAC_PHY_Write
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_PHY_Uninitialize (void)
  \brief       De-initialize Ethernet PHY Device.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_PHY_PowerControl (ARM_POWER_STATE state)
  \brief       Control Ethernet PHY Device Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_PHY_SetInterface (uint32_t interface)
  \brief       Set Ethernet Media Interface.
  \param[in]   interface  Media Interface type
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_PHY_SetMode (uint32_t mode)
  \brief       Set Ethernet PHY Device Operation mode.
  \param[in]   mode  Operation Mode
  \return      \ref execution_status
*/
/**
  \fn          ARM_ETH_LINK_STATE ARM_ETH_PHY_GetLinkState (void)
  \brief       Get Ethernet PHY Device Link state.
  \return      current link status \ref ARM_ETH_LINK_STATE
*/
/**
  \fn          ARM_ETH_LINK_INFO ARM_ETH_PHY_GetLinkInfo (void)
  \brief       Get Ethernet PHY Device Link information.
  \return      current link parameters \ref ARM_ETH_LINK_INFO
*/


typedef int32_t (*ARM_ETH_PHY_Read_t)  (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data); ///< Pointer to \ref ARM_ETH_MAC_PHY_Read : Read Ethernet PHY Register.
typedef int32_t (*ARM_ETH_PHY_Write_t) (uint8_t phy_addr, uint8_t reg_addr, uint16_t  data); ///< Pointer to \ref ARM_ETH_MAC_PHY_Write : Write Ethernet PHY Register.


/**
\brief Access structure of the Ethernet PHY Driver
*/
typedef struct _ARM_DRIVER_ETH_PHY {
  ARM_DRIVER_VERSION (*GetVersion)   (void);                          ///< Pointer to \ref ARM_ETH_PHY_GetVersion : Get driver version.
  int32_t            (*Initialize)   (ARM_ETH_PHY_Read_t  fn_read,
                                      ARM_ETH_PHY_Write_t fn_write);  ///< Pointer to \ref ARM_ETH_PHY_Initialize : Initialize PHY Device.
  int32_t            (*Uninitialize) (void);                          ///< Pointer to \ref ARM_ETH_PHY_Uninitialize : De-initialize PHY Device.
  int32_t            (*PowerControl) (ARM_POWER_STATE state);         ///< Pointer to \ref ARM_ETH_PHY_PowerControl : Control PHY Device Power.
  int32_t            (*SetInterface) (uint32_t interface);            ///< Pointer to \ref ARM_ETH_PHY_SetInterface : Set Ethernet Media Interface.
  int32_t            (*SetMode)      (uint32_t mode);                 ///< Pointer to \ref ARM_ETH_PHY_SetMode : Set Ethernet PHY Device Operation mode.
  ARM_ETH_LINK_STATE (*GetLinkState) (void);                          ///< Pointer to \ref ARM_ETH_PHY_GetLinkState : Get Ethernet PHY Device Link state.
  ARM_ETH_LINK_INFO  (*GetLinkInfo)  (void);                          ///< Pointer to \ref ARM_ETH_PHY_GetLinkInfo : Get Ethernet PHY Device Link information.
} const ARM_DRIVER_ETH_PHY;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_ETH_PHY_H_ */
