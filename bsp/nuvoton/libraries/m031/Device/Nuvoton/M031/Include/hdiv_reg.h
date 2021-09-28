/**************************************************************************//**
 * @file     hdiv_reg.h
 * @version  V1.00
 * @brief    HDIV register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HDIV_REG_H__
#define __HDIV_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup HDIV Hardware Divider (HDIV)
    Memory Mapped Structure for HDIV Controller
@{ */

typedef struct
{


    /**
     * DIVIDEND
     * ===================================================================================================
     * Offset: 0x00  Dividend Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DIVIDEND  |Dividend Source
     * |        |          |This register is given the dividend of divider before calculation starting.
    */
    __IO uint32_t DIVIDEND;

    /**
     * DIVISOR
     * ===================================================================================================
     * Offset: 0x04  Divisor Source Resister
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |DIVISOR   |Divisor Source
     * |        |          |This register is given the divisor of divider before calculation starts.
     * |        |          |Note: When this register is written, hardware divider will start calculate.
    */
    __IO uint32_t DIVISOR;

    /**
     * QUOTIENT
     * ===================================================================================================
     * Offset: 0x08  Quotient Result Resister
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |QUOTIENT  |Quotient Result
     * |        |          |This register holds the quotient result of divider after calculation complete.
    */
    __IO uint32_t QUOTIENT;

    /**
     * REM
     * ===================================================================================================
     * Offset: 0x0C  Remainder Result Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |REM       |Remainder Result
     * |        |          |The remainder of hardware divider is 16-bit sign integer (REM[15:0]) with sign extension
     * |        |          |(REM[31:16]) to 32-bit integer.
    */
    __IO uint32_t REM;

    /**
     * STATUS
     * ===================================================================================================
     * Offset: 0x10  Divider Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |DIVBYZERO |Divisor Zero Warning
     * |        |          |0 = The divisor is not 0.
     * |        |          |1 = The divisor is 0.
     * |        |          |Note: The DIVBYZERO flag is used to indicate divide-by-zero situation and updated whenever
     * |        |          |HDIV_DIVISOR is written.
     * |        |          |This register is read only.
    */
    __I  uint32_t STATUS;

} HDIV_T;

/**
    @addtogroup HDIV_CONST HDIV Bit Field Definition
    Constant Definitions for HDIV Controller
@{ */

#define HDIV_DIVIDEND_DIVIDEND_Pos       (0)                                               /*!< HDIV_T::DIVIDEND: DIVIDEND Position       */
#define HDIV_DIVIDEND_DIVIDEND_Msk       (0xfffffffful << HDIV_DIVIDEND_DIVIDEND_Pos)      /*!< HDIV_T::DIVIDEND: DIVIDEND Mask           */

#define HDIV_DIVISOR_DIVISOR_Pos         (0)                                               /*!< HDIV_T::DIVISOR: DIVISOR Position         */
#define HDIV_DIVISOR_DIVISOR_Msk         (0xfffful << HDIV_DIVISOR_DIVISOR_Pos)            /*!< HDIV_T::DIVISOR: DIVISOR Mask             */

#define HDIV_QUOTIENT_QUOTIENT_Pos       (0)                                               /*!< HDIV_T::QUOTIENT: QUOTIENT Position       */
#define HDIV_QUOTIENT_QUOTIENT_Msk       (0xfffffffful << HDIV_QUOTIENT_QUOTIENT_Pos)      /*!< HDIV_T::QUOTIENT: QUOTIENT Mask           */

#define HDIV_REM_REM_Pos                 (0)                                               /*!< HDIV_T::REM: REM Position                 */
#define HDIV_REM_REM_Msk                 (0xfffffffful << HDIV_REM_REM_Pos)                /*!< HDIV_T::REM: REM Mask                     */

#define HDIV_STATUS_DIVBYZERO_Pos        (1)                                               /*!< HDIV_T::STATUS: DIVBYZERO Position        */
#define HDIV_STATUS_DIVBYZERO_Msk        (0x1ul << HDIV_STATUS_DIVBYZERO_Pos)              /*!< HDIV_T::STATUS: DIVBYZERO Mask            */

/**@}*/ /* HDIV_CONST */
/**@}*/ /* end of HDIV register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __HDIV_REG_H__ */


/**@}*/ /* HDIV_CONST */
/**@}*/ /* end of HDIV register group */
