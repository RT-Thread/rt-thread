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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

#ifndef BSP_COMPILER_SUPPORT_H
#define BSP_COMPILER_SUPPORT_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3))
 #include <arm_cmse.h>
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION)           /* AC6 compiler */

/* The AC6 linker requires uninitialized code to be placed in a section that starts with ".bss." Without this, load
 * memory (ROM) is reserved unnecessarily. */
 #define BSP_UNINIT_SECTION_PREFIX         ".bss"
 #define BSP_SECTION_HEAP                  BSP_UNINIT_SECTION_PREFIX ".heap"
 #define BSP_DONT_REMOVE
 #define BSP_ATTRIBUTE_STACKLESS           __attribute__((naked))
 #define BSP_FORCE_INLINE                  __attribute__((always_inline))
 #define BSP_TARGET_ARM                    #pragma arm
#elif   defined(__GNUC__)              /* GCC compiler */
 #define BSP_UNINIT_SECTION_PREFIX
 #define BSP_SECTION_HEAP                  ".heap"
 #define BSP_DONT_REMOVE
 #define BSP_ATTRIBUTE_STACKLESS           __attribute__((naked))
 #define BSP_FORCE_INLINE                  __attribute__((always_inline))
 #define BSP_TARGET_ARM                    __attribute__((target("arm")))
#elif defined(__ICCARM__)              /* IAR compiler */
 #define BSP_UNINIT_SECTION_PREFIX
 #define BSP_SECTION_HEAP                  "HEAP"
 #define BSP_DONT_REMOVE                   __root
 #define BSP_ATTRIBUTE_STACKLESS           __stackless
 #define BSP_FORCE_INLINE                  _Pragma("inline=forced")
 #define BSP_TARGET_ARM                    __arm
#endif

#define BSP_SECTION_FIQ_STACK              BSP_UNINIT_SECTION_PREFIX ".fiq_stack"
#define BSP_SECTION_IRQ_STACK              BSP_UNINIT_SECTION_PREFIX ".irq_stack"
#define BSP_SECTION_ABT_STACK              BSP_UNINIT_SECTION_PREFIX ".abt_stack"
#define BSP_SECTION_UND_STACK              BSP_UNINIT_SECTION_PREFIX ".und_stack"
#define BSP_SECTION_SYS_STACK              BSP_UNINIT_SECTION_PREFIX ".sys_stack"
#define BSP_SECTION_SVC_STACK              BSP_UNINIT_SECTION_PREFIX ".svc_stack"
#define BSP_SECTION_NOINIT                 BSP_UNINIT_SECTION_PREFIX ".noinit"
#define BSP_SECTION_FIXED_VECTORS          ".fixed_vectors"
#define BSP_SECTION_APPLICATION_VECTORS    ".application_vectors"
#define BSP_SECTION_ROM_REGISTERS          ".rom_registers"
#define BSP_SECTION_ID_CODE                ".id_code"
#define BSP_SECTION_LOADER_PARAM           ".loader_param"

/* Compiler neutral macros. */
#define BSP_PLACE_IN_SECTION(x)    __attribute__((section(x))) __attribute__((__used__))

#define BSP_ALIGN_VARIABLE(x)      __attribute__((aligned(x)))

#define BSP_PACKED             __attribute__((aligned(1)))

#define BSP_WEAK_REFERENCE     __attribute__((weak))

/** Stacks (and heap) must be sized and aligned to an integer multiple of this number. */
#define BSP_STACK_ALIGNMENT    (8)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/** @} (end of addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
