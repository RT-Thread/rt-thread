////////////////////////////////////////////////////////////////////////////////
/// @file     hal_eth_conf.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE hal_eth_conf.h EXAMPLES.
/// ////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT  MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAL_ETH_CONF_H
#define __HAL_ETH_CONF_H
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ETH_HAL
/// @brief ETH HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ETH_Exported_Types
/// @{


// #define USE_ENHANCED_DMA_DESCRIPTORS
// #define CUSTOM_DRIVER_BUFFERS_CONFIG
#define DP83848

#ifdef CUSTOM_DRIVER_BUFFERS_CONFIG
#define ETH_RX_BUF_SIZE     ETH_MAX_PACKET_SIZE
#define ETH_TX_BUF_SIZE     ETH_MAX_PACKET_SIZE
#define ETH_RX_BUF_NUM      4
#define ETH_TX_BUF_NUM      4
#endif

////////////////////////////////////////////////////////////////////////////////
#if defined(DP83848)
#define PHY_SR                  ((u16)0x10)
#define PHY_SR_LINKSTATUS       ((u16)0x0001)
#define PHY_SPEED_STATUS        ((u16)0x0002)
#define PHY_DUPLEX_STATUS       ((u16)0x0004)

#define PHY_MICR                ((u16)0x11)
#define PHY_MICR_INT_EN         ((u16)0x0002)
#define PHY_MICR_INT_OE         ((u16)0x0001)

#define PHY_MISR                ((u16)0x12)
#define PHY_MISR_LINK_INT_EN    ((u16)0x0020)
#define PHY_LINK_STATUS         ((u16)0x2000)
#endif

/// @}

/// @}

/// @}
////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_ETH_CONF_H
////////////////////////////////////////////////////////////////////////////////
