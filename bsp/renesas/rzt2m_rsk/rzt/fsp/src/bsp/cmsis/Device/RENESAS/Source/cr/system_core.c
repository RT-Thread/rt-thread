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
#include <string.h>
#include "bsp_api.h"

#include "../../../../../mcu/all/bsp_clocks.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_CPCAR_CP_ENABLE             (0x00F00000)
#define BSP_FPEXC_EN_ENABLE             (0x40000000)
#define BSP_TCM_ALL_ACCESS_ENABLE       (0x00000003)

#define BSP_PRIORITY_MASK               BSP_FEATURE_BSP_IRQ_PRIORITY_MASK /* Priority mask value for GIC */
#define BSP_ENABLE_GROUP_INT            (0x00000001)                      /* Enable Group1 interrupt value */
#define BSP_ICC_CTLR                    (0x00000001)                      /* ICC_BPR0 is used for Group1 interrupt */

#define BSP_BG_REGION_ENABLE            (0x00020000)                      /* Enable EL1 background region */
#define BSP_BG_REGION_DISABLE           (0x00000000)                      /* Disable EL1 background region */
#define BSP_SCTLR_BR_BIT                (BSP_CFG_SCTLR_BR_BIT)            /* Enable EL1 background region */

#define BSP_ICACHE_ENABLE               (0x00001000)
#define BSP_ICACHE_DISABLE              (0x00000000)

#define BSP_DATACACHE_ENABLE            (0x00000004)
#define BSP_DATACACHE_DISABLE           (0x00000000)

#define BSP_WRITE_THROUGH_TRANSIENT     (0x0003) /* Normal-Memory: Write-Through transient */
#define BSP_NON_CACHEABLE               (0x0004) /* Normal-Memory: Non-Cacheable */
#define BSP_WRITE_BACK_TRANSIENT        (0x0007) /* Normal-Memory: Write-Back transient */
#define BSP_WRITE_NON_THROUGH           (0x000B) /* Normal-Memory: Write-Through non-transient. */
#define BSP_WRITE_BACK_NON_TRANSIENT    (0x000F) /* Normal-Memory: Write-Back non-transient. */

#define BSP_TYPE_NORMAL_MEMORY          (0)
#define BSP_TYPE_DEVICE_MEMORY          (1)

#define BSP_READ_ALLOCATE               (0xFFFF) /* Read allocate (bit1=1, "1" mask except bit1) */
#define BSP_READ_NOT_ALLOCATE           (0xFFFD) /* Read not allocate (bit1=0, "1" mask except bit1) */
#define BSP_WRITE_ALLOCATE              (0xFFFF) /* Write allocate (bit0=1, "1" mask except bit0) */
#define BSP_WRITE_NOT_ALLOCATE          (0xFFFE) /* Write not allocate (bit0=0, "1" mask except bit0) */

#define BSP_DEVICE_NGNRNE               (0x0000) /* Device-nGnRnE memory */
#define BSP_DEVICE_NGNRE                (0x0004) /* Device-nGnRE memory */
#define BSP_DEVICE_NGRE                 (0x0008) /* Device-nGRE memory */
#define BSP_DEVICE_GRE                  (0x000C) /* Device-GRE memory */

#define BSP_OFFSET_ATTR0_INNER          (0)
#define BSP_OFFSET_ATTR0_OUTER          (4)
#define BSP_OFFSET_ATTR0_DEVICE         (0)
#define BSP_OFFSET_ATTR1_INNER          (8)
#define BSP_OFFSET_ATTR1_OUTER          (12)
#define BSP_OFFSET_ATTR1_DEVICE         (8)

#define BSP_OFFSET_ATTR2_INNER          (16)
#define BSP_OFFSET_ATTR2_OUTER          (20)
#define BSP_OFFSET_ATTR2_DEVICE         (16)
#define BSP_OFFSET_ATTR3_INNER          (24)
#define BSP_OFFSET_ATTR3_OUTER          (28)
#define BSP_OFFSET_ATTR3_DEVICE         (24)

#define BSP_OFFSET_ATTR4_INNER          (0)
#define BSP_OFFSET_ATTR4_OUTER          (4)
#define BSP_OFFSET_ATTR4_DEVICE         (0)
#define BSP_OFFSET_ATTR5_INNER          (8)
#define BSP_OFFSET_ATTR5_OUTER          (12)
#define BSP_OFFSET_ATTR5_DEVICE         (8)

#define BSP_OFFSET_ATTR6_INNER          (16)
#define BSP_OFFSET_ATTR6_OUTER          (20)
#define BSP_OFFSET_ATTR6_DEVICE         (16)
#define BSP_OFFSET_ATTR7_INNER          (24)
#define BSP_OFFSET_ATTR7_OUTER          (28)
#define BSP_OFFSET_ATTR7_DEVICE         (24)

#define BSP_NON_SHAREABLE               (0 << 3)
#define BSP_OUTER_SHAREABLE             (2 << 3)
#define BSP_INNER_SHAREABLE             (3 << 3)
#define BSP_EL1RW_EL0NO                 (0 << 1)
#define BSP_EL1RW_EL0RW                 (1 << 1)
#define BSP_EL1RO_EL0NO                 (2 << 1)
#define BSP_EL1RO_EL0RO                 (3 << 1)
#define BSP_EXECUTE_ENABLE              (0)
#define BSP_EXECUTE_NEVER               (1)
#define BSP_REGION_DISABLE              (0)
#define BSP_REGION_ENABLE               (1)
#define BSP_ATTRINDEX0                  (0 << 1)
#define BSP_ATTRINDEX1                  (1 << 1)
#define BSP_ATTRINDEX2                  (2 << 1)
#define BSP_ATTRINDEX3                  (3 << 1)
#define BSP_ATTRINDEX4                  (4 << 1)
#define BSP_ATTRINDEX5                  (5 << 1)
#define BSP_ATTRINDEX6                  (6 << 1)
#define BSP_ATTRINDEX7                  (7 << 1)

/* Attr0 */
#if BSP_CFG_CPU_MPU_ATTR0_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR0          (BSP_CFG_CPU_MPU_ATTR0_DEVICE_TYPE << BSP_OFFSET_ATTR0_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR0          (((BSP_CFG_CPU_MPU_ATTR0_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR0_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR0_INNER_WRITE)) << BSP_OFFSET_ATTR0_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR0_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR0_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR0_OUTER_WRITE)) << BSP_OFFSET_ATTR0_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR0_TYPE */

/* Attr1 */
#if BSP_CFG_CPU_MPU_ATTR1_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR1          (BSP_CFG_CPU_MPU_ATTR1_DEVICE_TYPE << BSP_OFFSET_ATTR1_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR1          (((BSP_CFG_CPU_MPU_ATTR1_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR1_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR1_INNER_WRITE)) << BSP_OFFSET_ATTR1_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR1_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR1_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR1_OUTER_WRITE)) << BSP_OFFSET_ATTR1_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR1_TYPE */

/* Attr2 */
#if BSP_CFG_CPU_MPU_ATTR2_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR2          (BSP_CFG_CPU_MPU_ATTR2_DEVICE_TYPE << BSP_OFFSET_ATTR2_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR2          (((BSP_CFG_CPU_MPU_ATTR2_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR2_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR2_INNER_WRITE)) << BSP_OFFSET_ATTR2_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR2_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR2_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR2_OUTER_WRITE)) << BSP_OFFSET_ATTR2_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR2_TYPE */

/* Attr3 */
#if BSP_CFG_CPU_MPU_ATTR3_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR3          (BSP_CFG_CPU_MPU_ATTR3_DEVICE_TYPE << BSP_OFFSET_ATTR3_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR3          (((BSP_CFG_CPU_MPU_ATTR3_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR3_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR3_INNER_WRITE)) << BSP_OFFSET_ATTR3_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR3_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR3_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR3_OUTER_WRITE)) << BSP_OFFSET_ATTR3_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR3_TYPE */

/* Attr4 */
#if BSP_CFG_CPU_MPU_ATTR4_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR4          (BSP_CFG_CPU_MPU_ATTR4_DEVICE_TYPE << BSP_OFFSET_ATTR4_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR4          (((BSP_CFG_CPU_MPU_ATTR4_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR4_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR4_INNER_WRITE)) << BSP_OFFSET_ATTR4_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR4_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR4_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR4_OUTER_WRITE)) << BSP_OFFSET_ATTR4_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR4_TYPE */

/* Attr5 */
#if BSP_CFG_CPU_MPU_ATTR5_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR5          (BSP_CFG_CPU_MPU_ATTR5_DEVICE_TYPE << BSP_OFFSET_ATTR5_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR5          (((BSP_CFG_CPU_MPU_ATTR5_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR5_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR5_INNER_WRITE)) << BSP_OFFSET_ATTR5_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR5_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR5_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR5_OUTER_WRITE)) << BSP_OFFSET_ATTR5_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR5_TYPE */

/* Attr6 */
#if BSP_CFG_CPU_MPU_ATTR6_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR6          (BSP_CFG_CPU_MPU_ATTR6_DEVICE_TYPE << BSP_OFFSET_ATTR6_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR6          (((BSP_CFG_CPU_MPU_ATTR6_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR6_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR6_INNER_WRITE)) << BSP_OFFSET_ATTR6_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR6_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR6_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR6_OUTER_WRITE)) << BSP_OFFSET_ATTR6_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR6_TYPE */

/* Attr7 */
#if BSP_CFG_CPU_MPU_ATTR7_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR7          (BSP_CFG_CPU_MPU_ATTR7_DEVICE_TYPE << BSP_OFFSET_ATTR7_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR7          (((BSP_CFG_CPU_MPU_ATTR7_INNER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR7_INNER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR7_INNER_WRITE)) << BSP_OFFSET_ATTR7_INNER) | \
                                         ((BSP_CFG_CPU_MPU_ATTR7_OUTER &                                     \
                                           (BSP_CFG_CPU_MPU_ATTR7_OUTER_READ) &                              \
                                           (BSP_CFG_CPU_MPU_ATTR7_OUTER_WRITE)) << BSP_OFFSET_ATTR7_OUTER))
#endif                                 /* BSP_CFG_CPU_MPU_ATTR7_TYPE */

#define ATTR_3_2_1_0                    (BSP_CFG_CPU_MPU_ATTR3 | BSP_CFG_CPU_MPU_ATTR2 | BSP_CFG_CPU_MPU_ATTR1 | \
                                         BSP_CFG_CPU_MPU_ATTR0)
#define ATTR_7_6_5_4                    (BSP_CFG_CPU_MPU_ATTR7 | BSP_CFG_CPU_MPU_ATTR6 | BSP_CFG_CPU_MPU_ATTR5 | \
                                         BSP_CFG_CPU_MPU_ATTR4)

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR0_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR0_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR0_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR0_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR0_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR0_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR0_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR1_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR1_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR1_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR1_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR1_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR1_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR1_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR2_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR2_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR2_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR2_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR2_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR2_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR2_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR3_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR3_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR3_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR3_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR3_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR3_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR3_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR4_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR4_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR4_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR4_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR4_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR4_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR4_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR5_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR5_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR5_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR5_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR5_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR5_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR5_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR6_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR6_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR6_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR6_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR6_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR6_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR6_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

#if (BSP_TYPE_NORMAL_MEMORY == BSP_CFG_CPU_MPU_ATTR7_TYPE)
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR7_INNER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR7_INNER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR7_INNER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
 #if ((BSP_WRITE_THROUGH_TRANSIENT == BSP_CFG_CPU_MPU_ATTR7_OUTER) && \
    (BSP_READ_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR7_OUTER_READ) &&    \
    (BSP_WRITE_NOT_ALLOCATE == BSP_CFG_CPU_MPU_ATTR7_OUTER_WRITE))
  #error "If you select Write-Through transient, set either Read or Write to allocate."
 #endif
#endif

/* Region template */
#define EL1_MPU_REGION_COUNT    (24)

#define EL1_MPU_REGIONXX_BASE(n)     ((BSP_CFG_EL1_MPU_REGION ## n ## _BASE & 0xFFFFFFC0) | \
                                      BSP_CFG_EL1_MPU_REGION ## n ## _SH |                  \
                                      BSP_CFG_EL1_MPU_REGION ## n ## _AP |                  \
                                      BSP_CFG_EL1_MPU_REGION ## n ## _XN)

#define EL1_MPU_REGIONXX_LIMIT(n)    ((BSP_CFG_EL1_MPU_REGION ## n ## _LIMIT & 0xFFFFFFC0) | \
                                      BSP_CFG_EL1_MPU_REGION ## n ## _ATTRINDEX |            \
                                      BSP_CFG_EL1_MPU_REGION ## n ## _ENABLE)

/* region 0 */
#define EL1_MPU_REGION00_BASE     EL1_MPU_REGIONXX_BASE(00)
#define EL1_MPU_REGION00_LIMIT    EL1_MPU_REGIONXX_LIMIT(00)

/* region 1 */
#define EL1_MPU_REGION01_BASE     EL1_MPU_REGIONXX_BASE(01)
#define EL1_MPU_REGION01_LIMIT    EL1_MPU_REGIONXX_LIMIT(01)

/* region 2 */
#define EL1_MPU_REGION02_BASE     EL1_MPU_REGIONXX_BASE(02)
#define EL1_MPU_REGION02_LIMIT    EL1_MPU_REGIONXX_LIMIT(02)

/* region 3 */
#define EL1_MPU_REGION03_BASE     EL1_MPU_REGIONXX_BASE(03)
#define EL1_MPU_REGION03_LIMIT    EL1_MPU_REGIONXX_LIMIT(03)

/* region 4 */
#define EL1_MPU_REGION04_BASE     EL1_MPU_REGIONXX_BASE(04)
#define EL1_MPU_REGION04_LIMIT    EL1_MPU_REGIONXX_LIMIT(04)

/* region 5 */
#define EL1_MPU_REGION05_BASE     EL1_MPU_REGIONXX_BASE(05)
#define EL1_MPU_REGION05_LIMIT    EL1_MPU_REGIONXX_LIMIT(05)

/* region 6 */
#define EL1_MPU_REGION06_BASE     EL1_MPU_REGIONXX_BASE(06)
#define EL1_MPU_REGION06_LIMIT    EL1_MPU_REGIONXX_LIMIT(06)

/* region 7 */
#define EL1_MPU_REGION07_BASE     EL1_MPU_REGIONXX_BASE(07)
#define EL1_MPU_REGION07_LIMIT    EL1_MPU_REGIONXX_LIMIT(07)

/* region 8 */
#define EL1_MPU_REGION08_BASE     EL1_MPU_REGIONXX_BASE(08)
#define EL1_MPU_REGION08_LIMIT    EL1_MPU_REGIONXX_LIMIT(08)

/* region 9 */
#define EL1_MPU_REGION09_BASE     EL1_MPU_REGIONXX_BASE(09)
#define EL1_MPU_REGION09_LIMIT    EL1_MPU_REGIONXX_LIMIT(09)

/* region 10 */
#define EL1_MPU_REGION10_BASE     EL1_MPU_REGIONXX_BASE(10)
#define EL1_MPU_REGION10_LIMIT    EL1_MPU_REGIONXX_LIMIT(10)

/* region 11 */
#define EL1_MPU_REGION11_BASE     EL1_MPU_REGIONXX_BASE(11)
#define EL1_MPU_REGION11_LIMIT    EL1_MPU_REGIONXX_LIMIT(11)

/* region 12 */
#define EL1_MPU_REGION12_BASE     EL1_MPU_REGIONXX_BASE(12)
#define EL1_MPU_REGION12_LIMIT    EL1_MPU_REGIONXX_LIMIT(12)

/* region 13 */
#define EL1_MPU_REGION13_BASE     EL1_MPU_REGIONXX_BASE(13)
#define EL1_MPU_REGION13_LIMIT    EL1_MPU_REGIONXX_LIMIT(13)

/* region 14 */
#define EL1_MPU_REGION14_BASE     EL1_MPU_REGIONXX_BASE(14)
#define EL1_MPU_REGION14_LIMIT    EL1_MPU_REGIONXX_LIMIT(14)

/* region 15 */
#define EL1_MPU_REGION15_BASE     EL1_MPU_REGIONXX_BASE(15)
#define EL1_MPU_REGION15_LIMIT    EL1_MPU_REGIONXX_LIMIT(15)

/* region 16 */
#define EL1_MPU_REGION16_BASE     EL1_MPU_REGIONXX_BASE(16)
#define EL1_MPU_REGION16_LIMIT    EL1_MPU_REGIONXX_LIMIT(16)

/* region 17 */
#define EL1_MPU_REGION17_BASE     EL1_MPU_REGIONXX_BASE(17)
#define EL1_MPU_REGION17_LIMIT    EL1_MPU_REGIONXX_LIMIT(17)

/* region 18 */
#define EL1_MPU_REGION18_BASE     EL1_MPU_REGIONXX_BASE(18)
#define EL1_MPU_REGION18_LIMIT    EL1_MPU_REGIONXX_LIMIT(18)

/* region 19 */
#define EL1_MPU_REGION19_BASE     EL1_MPU_REGIONXX_BASE(19)
#define EL1_MPU_REGION19_LIMIT    EL1_MPU_REGIONXX_LIMIT(19)

/* region 20 */
#define EL1_MPU_REGION20_BASE     EL1_MPU_REGIONXX_BASE(20)
#define EL1_MPU_REGION20_LIMIT    EL1_MPU_REGIONXX_LIMIT(20)

/* region 21 */
#define EL1_MPU_REGION21_BASE     EL1_MPU_REGIONXX_BASE(21)
#define EL1_MPU_REGION21_LIMIT    EL1_MPU_REGIONXX_LIMIT(21)

/* region 22 */
#define EL1_MPU_REGION22_BASE     EL1_MPU_REGIONXX_BASE(22)
#define EL1_MPU_REGION22_LIMIT    EL1_MPU_REGIONXX_LIMIT(22)

/* region 23 */
#define EL1_MPU_REGION23_BASE     EL1_MPU_REGIONXX_BASE(23)
#define EL1_MPU_REGION23_LIMIT    EL1_MPU_REGIONXX_LIMIT(23)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_bsp_mpu_config
{
    uint32_t base;
    uint32_t limit;
} bsp_mpu_config_t;

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static const bsp_mpu_config_t g_bsp_el1_mpu[EL1_MPU_REGION_COUNT] =
{
    {EL1_MPU_REGION00_BASE, EL1_MPU_REGION00_LIMIT},
    {EL1_MPU_REGION01_BASE, EL1_MPU_REGION01_LIMIT},
    {EL1_MPU_REGION02_BASE, EL1_MPU_REGION02_LIMIT},
    {EL1_MPU_REGION03_BASE, EL1_MPU_REGION03_LIMIT},
    {EL1_MPU_REGION04_BASE, EL1_MPU_REGION04_LIMIT},
    {EL1_MPU_REGION05_BASE, EL1_MPU_REGION05_LIMIT},
    {EL1_MPU_REGION06_BASE, EL1_MPU_REGION06_LIMIT},
    {EL1_MPU_REGION07_BASE, EL1_MPU_REGION07_LIMIT},
    {EL1_MPU_REGION08_BASE, EL1_MPU_REGION08_LIMIT},
    {EL1_MPU_REGION09_BASE, EL1_MPU_REGION09_LIMIT},
    {EL1_MPU_REGION10_BASE, EL1_MPU_REGION10_LIMIT},
    {EL1_MPU_REGION11_BASE, EL1_MPU_REGION11_LIMIT},
    {EL1_MPU_REGION12_BASE, EL1_MPU_REGION12_LIMIT},
    {EL1_MPU_REGION13_BASE, EL1_MPU_REGION13_LIMIT},
    {EL1_MPU_REGION14_BASE, EL1_MPU_REGION14_LIMIT},
    {EL1_MPU_REGION15_BASE, EL1_MPU_REGION15_LIMIT},
    {EL1_MPU_REGION16_BASE, EL1_MPU_REGION16_LIMIT},
    {EL1_MPU_REGION17_BASE, EL1_MPU_REGION17_LIMIT},
    {EL1_MPU_REGION18_BASE, EL1_MPU_REGION18_LIMIT},
    {EL1_MPU_REGION19_BASE, EL1_MPU_REGION19_LIMIT},
    {EL1_MPU_REGION20_BASE, EL1_MPU_REGION20_LIMIT},
    {EL1_MPU_REGION21_BASE, EL1_MPU_REGION21_LIMIT},
    {EL1_MPU_REGION22_BASE, EL1_MPU_REGION22_LIMIT},
    {EL1_MPU_REGION23_BASE, EL1_MPU_REGION23_LIMIT},
};

#if __FPU_USED
void bsp_fpu_advancedsimd_init(void);

#endif

#if (0 == BSP_CFG_CORE_CR52)
void bsp_slavetcm_enable(void);

#endif

void bsp_memory_protect_setting(void);
void bsp_mpu_init(uint32_t region, uint32_t base, uint32_t limit);
void bsp_irq_cfg_common(void);

#if __FPU_USED

/*******************************************************************************************************************//**
 * Initialize FPU and Advanced SIMD setting.
 **********************************************************************************************************************/
void bsp_fpu_advancedsimd_init (void)
{
    uint32_t apacr;
    uint32_t fpexc;

    /* Enables cp10 and cp11 accessing */
    apacr  = __get_CPACR();
    apacr |= BSP_CPCAR_CP_ENABLE;
    __set_CPACR(apacr);
    __ISB();

    /* Enables the FPU */
    fpexc  = __get_FPEXC();
    fpexc |= BSP_FPEXC_EN_ENABLE;
    __set_FPEXC(fpexc);
    __ISB();
}

#endif

#if (0 == BSP_CFG_CORE_CR52)

/*******************************************************************************************************************//**
 * Settings the privilege level required for the AXIS to access the TCM.
 **********************************************************************************************************************/
void bsp_slavetcm_enable (void)
{
    uint32_t imp_slavepctlr;

    /* Enable TCM access privilege and non privilege */
    imp_slavepctlr  = __get_IMP_SLAVEPCTLR();
    imp_slavepctlr |= BSP_TCM_ALL_ACCESS_ENABLE;
    __DSB();

    __set_IMP_SLAVEPCTLR(imp_slavepctlr);
    __ISB();
}

#endif

/*******************************************************************************************************************//**
 * Initialize memory protection settings.
 **********************************************************************************************************************/
void bsp_memory_protect_setting (void)
{
    uint32_t sctlr;
    uint32_t mair0;
    uint32_t mair1;
    uint32_t region;

    /* Adopt EL1 default memory map as background map */
    sctlr  = __get_SCTLR();
    sctlr |= BSP_SCTLR_BR_BIT;
    __DSB();
    __set_SCTLR(sctlr);
    __ISB();

    /* Configure Memory Attribute Indirection Registers */
    mair0 = ATTR_3_2_1_0;
    mair1 = ATTR_7_6_5_4;
    __set_MAIR0(mair0);
    __set_MAIR1(mair1);
    __DSB();

    /* Setup region. */
    for (region = 0; region < EL1_MPU_REGION_COUNT; region++)
    {
        bsp_mpu_init(region, g_bsp_el1_mpu[region].base, g_bsp_el1_mpu[region].limit);
    }

    R_BSP_CacheInvalidateAll();

    R_BSP_CacheEnableMemoryProtect();

#if (BSP_ICACHE_ENABLE == BSP_CFG_SCTLR_I_BIT)
    R_BSP_CacheEnableInst();
#else
    R_BSP_CacheDisableInst();
#endif

#if (BSP_DATACACHE_ENABLE == BSP_CFG_SCTLR_C_BIT)
    R_BSP_CacheEnableData();
#else
    R_BSP_CacheDisableData();
#endif
}

/*******************************************************************************************************************//**
 * Core MPU initialization block.
 **********************************************************************************************************************/
void bsp_mpu_init (uint32_t region, uint32_t base, uint32_t limit)
{
    /* Selects the current EL1-controlled MPU region registers, PRBAR, and PRLAR */
    __set_PRSELR(region);
    __DSB();

    /* Set the base address and attributes of the MPU region controlled by EL1 */
    __set_PRBAR(base);
    __DSB();

    /* Set the limit address and attributes of the MPU region controlled by EL1 */
    __set_PRLAR(limit);
    __DSB();
}

/*******************************************************************************************************************//**
 * Initialize common configuration settings for interrupts
 **********************************************************************************************************************/
void bsp_irq_cfg_common (void)
{
    uint32_t icc_pmr;
    uint32_t icc_igrpen1;
    uint32_t icc_ctlr;

    /* Set priority mask level for CPU interface */
    icc_pmr = BSP_PRIORITY_MASK;
    __set_ICC_PMR(icc_pmr);

    /* Enable group 1 interrupts */
    icc_igrpen1 = BSP_ENABLE_GROUP_INT;
    __set_ICC_IGRPEN1(icc_igrpen1);

    /* Use ICC_BPR0 for interrupt preemption for both group 0 and group 1 interrupts */
    icc_ctlr  = __get_ICC_CTLR();
    icc_ctlr |= BSP_ICC_CTLR;
    __set_ICC_CTLR(icc_ctlr);

    __ISB();
}
