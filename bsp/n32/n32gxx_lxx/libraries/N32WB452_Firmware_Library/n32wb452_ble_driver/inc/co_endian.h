/**
 ****************************************************************************************
 *
 * @file co_endian.h
 *
 * @brief Common endianness conversion functions
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _CO_ENDIAN_H_
#define _CO_ENDIAN_H_

#include <stdint.h>              // standard integer definitions
#include "rwip_config.h"         // stack configuration
#include "ble_arch.h"

/**
 ****************************************************************************************
 * @defgroup CO_ENDIAN Endianness
 * @ingroup COMMON
 * @brief  Endianness conversion functions.
 *
 * This set of functions converts values between the local system
 * and a external one. It is inspired from the <tt>htonl</tt>-like functions
 * from the standard C library.
 *
 * Example:
 * @code
 *  struct eth_header   *header = get_header();  // get pointer on Eth II packet header
 *  uint16_t            eth_id;                  // will contain the type of the packet
 *  eth_id = co_ntohs(header->eth_id);           // retrieve the type with correct endianness
 * @endcode
 *
 * @{
 * ****************************************************************************************
 * */


/**
 ****************************************************************************************
 * @brief Swap bytes of a 32 bits value.
 * The swap is done in every case. Should not be called directly.
 * @param[in] val32 The 32 bits value to swap.
 * @return The 32 bit swapped value.
 ****************************************************************************************
 */
__INLINE uint32_t co_bswap32(uint32_t val32)
{
    return (val32<<24) | ((val32<<8)&0xFF0000) | ((val32>>8)&0xFF00) | ((val32>>24)&0xFF);
}

/**
 ****************************************************************************************
 * @brief Swap bytes of a 16 bits value.
 * The swap is done in every case. Should not be called directly.
 * @param[in] val16 The 16 bit value to swap.
 * @return The 16 bit swapped value.
 ****************************************************************************************
 */
__INLINE uint16_t co_bswap16(uint16_t val16)
{
    return ((val16<<8)&0xFF00) | ((val16>>8)&0xFF);
}
/// @} CO_ENDIAN




/**
 * ****************************************************************************************
 * @defgroup CO_ENDIAN_NET Endianness (Network)
 * @ingroup CO_ENDIAN
 * @brief Endianness conversion functions for Network data
 *
 *  Converts values between the local system and big-endian network data
 *  (e.g. IP, Ethernet, but NOT WLAN).
 *
 *  The \b host term in the descriptions of these functions refers
 *  to the local system, i.e. \b application or \b embedded system.
 *  Therefore, these functions will behave differently depending on which
 *  side they are used. The reason of this terminology is to keep the
 *  same name than the standard C function.
 *
 *  Behavior will depends on the endianness of the host:
 *  - little endian: swap bytes;
 *  - big endian: identity function.
 *
 *  @{
 * ****************************************************************************************
 *  */

/**
 ****************************************************************************************
 * @brief Convert host to network long word.
 *
 * @param[in] hostlong    Long word value to convert.
 *
 * @return The converted long word.
 ****************************************************************************************
 */
__INLINE uint32_t co_htonl(uint32_t hostlong)
{
    #if (!CPU_LE)
        return hostlong;
    #else
        return co_bswap32(hostlong);
    #endif // CPU_LE
}

/**
 ****************************************************************************************
 * @brief Convert host to network short word.
 *
 * @param[in] hostshort Short word value to convert.
 *
 * @return The converted short word.
 ****************************************************************************************
 */
__INLINE uint16_t co_htons(uint16_t hostshort)
{
    #if (!CPU_LE)
        return hostshort;
    #else
        return co_bswap16(hostshort);
    #endif // CPU_LE
}

/**
 ****************************************************************************************
 * @brief Convert network to host long word.
 *
 * @param[in] netlong Long word value to convert.
 *
 * @return The converted long word.
 ****************************************************************************************
 */
__INLINE uint32_t co_ntohl(uint32_t netlong)
{
    return co_htonl(netlong);
}

/**
 ****************************************************************************************
 * @brief Convert network to host short word.
 *
 * @param[in] netshort Short word value to convert.
 *
 * @return The converted short word.
 ****************************************************************************************
 */
__INLINE uint16_t co_ntohs(uint16_t netshort)
{
    return co_htons(netshort);
}
/// @} CO_ENDIAN_NET

/**
 * ****************************************************************************************
 * @defgroup CO_ENDIAN_BT Endianness (BT)
 *  @ingroup CO_ENDIAN
 *  @brief Endianness conversion functions for Bluetooth data (HCI and protocol)
 *
 *  Converts values between the local system and little-endian Bluetooth data.
 *
 *  The \b host term in the descriptions of these functions refers
 *  to the local system (check \ref CO_ENDIAN_NET "this comment").
 *
 *  Behavior will depends on the endianness of the host:
 *  - little endian: identity function;
 *  - big endian: swap bytes.
 *
 *  @addtogroup CO_ENDIAN_BT
 *  @{
 *  ****************************************************************************************
 *  */

/**
 ****************************************************************************************
 * @brief Convert host to Bluetooth long word.
 *
 * @param[in] hostlong Long word value to convert.
 *
 * @return The converted long word.
 ****************************************************************************************
 */
__INLINE uint32_t co_htobl(uint32_t hostlong)
{
    #if (CPU_LE)
        return hostlong;
    #else
        return co_bswap32(hostlong);
    #endif // CPU_LE
}

/**
 ****************************************************************************************
 * @brief Convert host to Bluetooth short word.
 *
 * @param[in] hostshort Short word value to convert.
 *
 * @return The converted short word.
 ****************************************************************************************
 */
__INLINE uint16_t co_htobs(uint16_t hostshort)
{
    #if (CPU_LE)
        return hostshort;
    #else
        return co_bswap16(hostshort);
    #endif // CPU_LE
}


/**
 ****************************************************************************************
 * @brief Convert Bluetooth to host long word.
 *
 * @param[in] btlong Long word value to convert.
 *
 * @return The converted long word.
 ****************************************************************************************
 */
__INLINE uint32_t co_btohl(uint32_t btlong)
{
    return co_htobl(btlong);
}


/**
 ****************************************************************************************
 * @brief Convert Bluetooth to host short word.
 *
 * @param[in] btshort Short word value to convert.
 *
 * @return The converted short word.
 ****************************************************************************************
 */
__INLINE uint16_t co_btohs(uint16_t btshort)
{
    return co_htobs(btshort);
}
/// @} CO_ENDIAN

#endif // _CO_ENDIAN_H_
