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

#ifndef BSP_SEMAPHORE_H
#define BSP_SEMAPHORE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/** The semaphore resource state shared by CPU0 and CPU1 */
typedef enum e_bsp_resource_state
{
    BSP_RESOURCE_STATE_BEING_USED     = 0, ///< Semaphore resource being used.
    BSP_RESOURCE_STATE_NOT_BEING_USED = 1, ///< Semaphore resource not being used.
} bsp_resource_state_t;

/** The semaphore resource number shared by CPU0 and CPU1 */
typedef enum e_bsp_resource_num
{
    BSP_RESOURCE_NUM_0 = 0,            ///< Semaphore resource number 0
    BSP_RESOURCE_NUM_1 = 1,            ///< Semaphore resource number 1
    BSP_RESOURCE_NUM_2 = 2,            ///< Semaphore resource number 2
    BSP_RESOURCE_NUM_3 = 3,            ///< Semaphore resource number 3
    BSP_RESOURCE_NUM_4 = 4,            ///< Semaphore resource number 4
    BSP_RESOURCE_NUM_5 = 5,            ///< Semaphore resource number 5
    BSP_RESOURCE_NUM_6 = 6,            ///< Semaphore resource number 6
    BSP_RESOURCE_NUM_7 = 7,            ///< Semaphore resource number 7
} bsp_resource_num_t;

#if BSP_FEATURE_SEM_SUPPORTED

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Inline Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Read semaphore resource status. When SYTSEMFEN = 1, reading this status clear the resource status.
 *
 * @param[in]  sem_num Semaphore number to read resource status.
 *
 * @retval     Resource status.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_SemaphoreStateRead (bsp_resource_num_t sem_num)
{
    return R_SEM->SYTSEMF[sem_num];
}

#endif

/** @} (end addtogroup BSP_MCU) */

/* Public functions defined in bsp.h */
void bsp_semaphore_init(void);         // Used internally by BSP

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
