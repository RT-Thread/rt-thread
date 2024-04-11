/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#if !(BSP_CFG_RAM_EXECUTION)
 #if (1 == _RZT_ORDINAL)

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
  #define BSP_LOADER_PARAM_MAX    (19)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* Parameter Information for the Loader. */
BSP_DONT_REMOVE const uint32_t g_bsp_loader_param[BSP_LOADER_PARAM_MAX] BSP_PLACE_IN_SECTION(BSP_SECTION_LOADER_PARAM) =
{
    BSP_CFG_CACHE_FLG,
    BSP_CFG_CS0BCR_V_WRAPCFG_V,
    BSP_CFG_CS0WCR_V_COMCFG_V,
    BSP_CFG_DUMMY0_BMCFG_V,
    BSP_CFG_BSC_FLG_xSPI_FLG,
    BSP_CFG_LDR_ADDR_NML,
    BSP_CFG_LDR_SIZE_NML,
    BSP_CFG_DEST_ADDR_NML,
    BSP_CFG_DUMMY1,
    BSP_CFG_DUMMY2,
    BSP_CFG_DUMMY3_CSSCTL_V,
    BSP_CFG_DUMMY4_LIOCFGCS0_V,
    BSP_CFG_DUMMY5,
    BSP_CFG_DUMMY6,
    BSP_CFG_DUMMY7,
    BSP_CFG_DUMMY8,
    BSP_CFG_DUMMY9,
    BSP_CFG_DUMMY10_ACCESS_SPEED,
    BSP_CFG_CHECK_SUM
};

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

 #endif
#endif
