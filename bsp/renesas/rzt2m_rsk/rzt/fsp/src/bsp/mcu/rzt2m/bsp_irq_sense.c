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

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RZT2M
 * @{
 **********************************************************************************************************************/

/** Array of GICD_ICFGR initialization value. */
const uint32_t BSP_GICD_ICFGR_INIT[BSP_NON_SELECTABLE_ICFGR_MAX] =
{
    0xAAAAAAAAUL,                      /* Event No. 0 to 15    */
    0x000000AAUL,                      /* Event No. 16 to 31   */
    0x00000000UL,                      /* Event No. 32 to 47   */
    0xAAAAA800UL,                      /* Event No. 48 to 63   */
    0xAAAAAAAAUL,                      /* Event No. 64 to 79   */
    0xAAAAAAAAUL,                      /* Event No. 80 to 95   */
    0xAAAAAAAAUL,                      /* Event No. 96 to 111  */
    0xAAAAAA00UL,                      /* Event No. 112 to 127 */
    0xAAAAAAAAUL,                      /* Event No. 128 to 143 */
    0xAAAAAAAAUL,                      /* Event No. 144 to 159 */
    0xAAAAAAAAUL,                      /* Event No. 160 to 175 */
    0xAAAAAAAAUL,                      /* Event No. 176 to 191 */
    0xAAAAAAAAUL,                      /* Event No. 192 to 207 */
    0xAAAAAAAAUL,                      /* Event No. 208 to 223 */
    0xAAAAAAAAUL,                      /* Event No. 224 to 239 */
    0x0000000AUL,                      /* Event No. 240 to 255 */
    0xA8000000UL,                      /* Event No. 256 to 271 */
    0xA82A2AAAUL,                      /* Event No. 272 to 287 */
    0x28282828UL,                      /* Event No. 288 to 303 */
    0x00282828UL,                      /* Event No. 304 to 319 */
    0xA82A0A00UL,                      /* Event No. 320 to 335 */
    0xA0AA8020UL,                      /* Event No. 336 to 351 */
    0x00000002UL,                      /* Event No. 352 to 367 */
    0x00000000UL,                      /* Event No. 368 to 383 */
    0xAAAA0AAAUL,                      /* Event No. 384 to 399 */
    0xAAAAAAAAUL,                      /* Event No. 400 to 415 */
    0x00AAAAAAUL,                      /* Event No. 416 to 431 */
    0x828A0A2AUL,                      /* Event No. 432 to 447 */
};

const uint32_t BSP_GICR_SGI_PPI_ICFGR_INIT[BSP_EVENT_SGI_PPI_ARRAY_NUM] =
{
    0xAAAAAAAAUL,                      /* event SGI */
    0x00020000UL,                      /* event PPI */
};

/** @} (end addtogroup BSP_MCU_RZT2M) */

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
