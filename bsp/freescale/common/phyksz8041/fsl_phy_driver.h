/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_PHY_DRIVER_H__
#define __FSL_PHY_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_enet_hal.h"

/*! 
 * @addtogroup phy_driver
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the maximum PHY address.*/ 
#define ENET_PHY_MAX_ADDRESS     0x1FU

/*! @brief Defines the PHY register.*/
typedef enum _enet_phy_register
{
    kEnetPhyCR = 0U, /*!< PHY control register */
    kEnetPhySR = 1U, /*!< PHY status register*/
    kEnetPhyId1 = 2U, /*!< PHY identification register 1*/
    kEnetPhyId2 = 3U, /*!< PHY identification register 2*/
    kEnetPhyCt1 = 0x1eU, /*!< PHY control1 register*/
    kEnetPhyCt2 = 0x1fU, /*!< PHY control2 register*/
} enet_phy_register_t;

/*! @brief Defines the control flag in control register.*/
typedef enum _enet_phy_controlreg
{
    kEnetPhyAutoNeg = 0x1000U,/*!< ENET PHY auto negotiation control*/
    kEnetPhySpeed = 0x2000U, /*! ENET PHY speed control*/
    kEnetPhyLoop = 0x4000U, /*!< ENET PHY loop control*/
    kEnetPhyReset = 0x8000U, /*!< ENET PHY reset control*/
    kEnetPhy10HalfDuplex = 0x04U, /*!< ENET PHY 10M half duplex*/
    kEnetPhy100HalfDuplex = 0x08U,/*!< ENET PHY 100M half duplex*/
    kEnetPhy10FullDuplex = 0x14U,/*!< ENET PHY 10M full duplex*/
    kEnetPhy100FullDuplex = 0x18U/*!< ENET PHY 100M full duplex*/
} enet_phy_controlreg_t;

/*! @brief Defines the control flag in status register.*/
typedef enum _enet_phy_statusreg
{
    kEnetPhyLinkStatus = 0x04U,  /*!< ENET PHY link status bit*/
    kEnetPhyAutoNegAble = 0x08U, /*!< ENET PHY auto negotiation ability*/
    kEnetPhySpeedDulpexMask = 0x1cU, /*!< ENET PHY speed mask on status register 2*/
    kEnetPhyAutoNegComplete = 0x20U /*!< ENET PHY auto negotiation complete*/
} enet_phy_statusreg_t;

/*! @brief Define PHY's link status*/
typedef enum _enet_phy_link_status
{
    kPhyLinkSpeed = 0x1U,       /*!< PHY Link speed */
    kPhyLinkon    = 0x2U       /*!< PHY link status*/
}enet_phy_link_status_t;

/*! @brief Defines the PHY link speed. */
typedef enum _enet_phy_speed
{
    kEnetSpeed10M = 0U,   /*!< ENET PHY 10 M speed*/
    kEnetSpeed100M = 1U  /*!< ENET PHY 100 M speed*/
} enet_phy_speed_t;

/*! @brief Defines the PHY link duplex.*/
typedef enum _enet_phy_duplex
{
    kEnetHalfDuplex = 0U, /*!< ENET PHY half duplex*/
    kEnetFullDuplex = 1U  /*!< ENET PHY full duplex*/
} enet_phy_duplex_t;

/*! @brief Defines the basic configuration for PHY.*/
typedef struct ENETPhyConfig
{
    bool isAutodiscoverEnabled;  /*!< PHY address auto discover*/
    uint8_t phyAddr;    /*!< PHY address*/
    bool isLoopEnabled; /*!< Switcher to enable the HY loop mode*/
} enet_phy_config_t;

/*******************************************************************************
 * Global variables
 ******************************************************************************/

/*******************************************************************************
 * API 
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
  * @name PHY Driver
  * @{
  */
  
/*!
 * @brief PHY Write function.
 *
 * This interface write data over the SMI to the specified PHY register.   
 * This function is called by all PHY interfaces.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param data The data written to the phy register.
 * @return The execution status.
 */
enet_status_t PHY_DRV_Write(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t data);
/*!
 * @brief PHY Read function.
 *
 * This interface read data over the SMI from the specified PHY register.   
 * This function is called by all PHY interfaces.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param dataPtr The address to store the data read from the phy register.
 * @return The execution status.
 */
enet_status_t PHY_DRV_Read(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr);

/*!
 * @brief Initializes PHY.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param isLoopEnabled The flag to enable or disable phy internal loopback.
 * @return The execution status.
 */
enet_status_t PHY_DRV_Init(uint32_t instance, uint32_t phyAddr, bool isLoopEnabled);

/*!
 * @brief PHY address auto discover.
 *
 *
 * This function provides a interface to get phy address using phy address auto 
 * discovering, this interface is used when the phy address is unknown.
 *
 * @param instance The ENET instance structure.
 * @param phyAddr The address of discovered PHY address.
 * @return The execution status.
 */
enet_status_t PHY_DRV_Autodiscover(uint32_t instance, uint32_t *phyAddr);

/*!
 * @brief Gets the PHY link speed.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param speed The address of PHY link speed.
 * @return The execution status.
 */
enet_status_t PHY_DRV_GetLinkSpeed(uint32_t instance, uint32_t phyAddr, enet_phy_speed_t *speed);

/*!
 * @brief Gets the PHY link status.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param status The link on or down status of the PHY.
 *         - True the link is on.
 *         - False the link is down.
 * @return The execution status.
 */
enet_status_t PHY_DRV_GetLinkStatus(uint32_t instance, uint32_t phyAddr, bool *status);

/*!
 * @brief Gets the PHY link duplex.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param status The link duplex of PHY.
 * @return The execution status.
 */
enet_status_t PHY_DRV_GetLinkDuplex(uint32_t instance, uint32_t phyAddr, enet_phy_duplex_t *status);

/*!
 * @brief Upate PHY link speed.
 *
 * This function provides a interface to moniter the change of the link speed.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param status The link speed of PHY.
 * @return The PHY link speed change flag.
 *         - True PHY link speed changed effectively.
 *         - False PHY link speed not changed effectively.
 */
bool PHY_DRV_UpdateSpeed(uint32_t instance, uint32_t phyAddr, enet_phy_speed_t *status);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_PHY_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

