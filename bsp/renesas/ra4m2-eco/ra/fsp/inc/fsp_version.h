/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef FSP_VERSION_H
 #define FSP_VERSION_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
 #include "bsp_api.h"

/*******************************************************************************************************************//**
 * @addtogroup RENESAS_COMMON
 * @{
 **********************************************************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** FSP pack major version. */
 #define FSP_VERSION_MAJOR (4U)

/** FSP pack minor version. */
 #define FSP_VERSION_MINOR (2U)

/** FSP pack patch version. */
 #define FSP_VERSION_PATCH (0U)

/** FSP pack version build number (currently unused). */
 #define FSP_VERSION_BUILD           (0U)

/** Public FSP version name. */
 #define FSP_VERSION_STRING          ("4.2.0")

/** Unique FSP version ID. */
 #define FSP_VERSION_BUILD_STRING    ("Built with Renesas Advanced Flexible Software Package version 4.2.0")

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** FSP Pack version structure */
typedef union st_fsp_pack_version
{
    /** Version id */
    uint32_t version_id;

    /**
     * Code version parameters, little endian order.
     */
    struct version_id_b_s
    {
        uint8_t build;                 ///< Build version of FSP Pack
        uint8_t patch;                 ///< Patch version of FSP Pack
        uint8_t minor;                 ///< Minor version of FSP Pack
        uint8_t major;                 ///< Major version of FSP Pack
    } version_id_b;
} fsp_pack_version_t;

/** @} */

 #ifdef __cplusplus
}
 #endif

#endif
