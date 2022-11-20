/**************************************************************************//**
 * @file     plm_reg.h
 * @brief    PLM register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PLM_REG_H__
#define __PLM_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Product Life-cycle Manager -------------------------*/
/**
    @addtogroup PLM Product Life-cycle Manager(PLM)
    Memory Mapped Structure for PLM Controller
@{ */

typedef struct
{


    /**
     * @var PLM_T::STS
     * Offset: 0x04  Product Life-cycle Status Register (TZNS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |STAGE     |Current Product Lifecycle Stage (Read Only)
     * |        |          |0x1 = Develop Stage.
     * |        |          |0x3 = Deployed Stage.
     * |        |          |0x7 = RMA Stage.
     * |        |          |0x5 = RMA Stage.
     * |        |          |Others = Error stage.
     * |[31:24] |RVCODE    |Read Verify Code (Read Only)
     * |        |          |Read Verify Code should be 0xA5
     */
    __I  uint32_t RESERVE0[1];
    __I  uint32_t STS;                   /*!< [0x0004] Product Life-cycle Status Register (TZNS)                        */

} PLM_T;

/**
    @addtogroup PLM_CONST PLM Bit Field Definition
    Constant Definitions for PLM Controller
@{ */

#define PLM_STS_STAGE_Pos                (0)                                               /*!< PLM_T::STS: STAGE Position             */
#define PLM_STS_STAGE_Msk                (0x7ul << PLM_STS_STAGE_Pos)                      /*!< PLM_T::STS: STAGE Mask                 */

#define PLM_STS_RVCODE_Pos               (24)                                              /*!< PLM_T::STS: RVCODE Position            */
#define PLM_STS_RVCODE_Msk               (0xfful << PLM_STS_RVCODE_Pos)                    /*!< PLM_T::STS: RVCODE Mask                */

/**@}*/ /* PLM_CONST */
/**@}*/ /* end of PLM register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __PLM_REG_H__ */
