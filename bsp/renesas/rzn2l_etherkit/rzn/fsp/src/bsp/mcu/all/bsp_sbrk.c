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
#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
#include <sys/types.h>
#include <errno.h>
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
caddr_t _sbrk(int incr);

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * FSP implementation of the standard library _sbrk() function.
 * @param[in]   inc  The number of bytes being asked for by malloc().
 *
 * @note This function overrides the _sbrk version that exists in the newlib library that is linked with.
 *       That version improperly relies on the SP as part of it's allocation strategy. This is bad in general and
 *       worse in an RTOS environment. This version insures that we allocate the byte pool requested by malloc()
 *       only from our allocated HEAP area. Also note that newlib is pre-built and forces the pagesize used by
 *       malloc() to be 4096. That requires that we have a HEAP of at least 4096 if we are to support malloc().
 * @retval        Address of allocated area if successful, -1 otherwise.
 **********************************************************************************************************************/
caddr_t _sbrk (int incr)
{
    extern char _Heap_Begin __asm("__HeapBase");  ///< Defined by the linker.

    extern char _Heap_Limit __asm("__HeapLimit"); ///< Defined by the linker.

    uint32_t      bytes            = (uint32_t) incr;
    static char * current_heap_end = 0;
    char        * current_block_address;

    if (current_heap_end == 0)
    {
        current_heap_end = &_Heap_Begin;
    }

    current_block_address = current_heap_end;

    /* The returned address must be aligned to a word boundary to prevent hard faults on cores that do not support
     * unaligned access. We assume the heap starts on a word boundary and make sure all allocations are a multiple
     * of 4. */
    bytes = (bytes + 3U) & (~3U);
    if (current_heap_end + bytes > &_Heap_Limit)
    {
        /** Heap has overflowed */
        errno = ENOMEM;

        return (caddr_t) -1;
    }

    current_heap_end += bytes;

    return (caddr_t) current_block_address;
}

#endif

/******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU)
 *********************************************************************************************************************/
