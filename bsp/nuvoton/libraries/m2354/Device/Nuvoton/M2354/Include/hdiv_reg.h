/**************************************************************************//**
 * @file     hdiv_reg.h
 * @version  V1.00
 * @brief    HDIV register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HDIV_REG_H__
#define __HDIV_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- Hardware Divider --------------------------------*/
/**
    @addtogroup HDIV Hardware Divider(HDIV)
    Memory Mapped Structure for HDIV Controller
  @{
*/

typedef struct
{


    /**
     * @var HDIV_T::DIVIDEND
     * Offset: 0x00  Dividend Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DIVIDEND  |Dividend Source
     * |        |          |This register is given the dividend of divider before calculation starting.
     * @var HDIV_T::DIVISOR
     * Offset: 0x04  Divisor Source Resister
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |DIVISOR   |Divisor Source
     * |        |          |This register is given the divisor of divider before calculation starts.
     * |        |          |Note: When this register is written, hardware divider will start calculate.
     * @var HDIV_T::DIVQUO
     * Offset: 0x08  Quotient Result Resister
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |QUOTIENT  |Quotient Result
     * |        |          |This register holds the quotient result of divider after calculation complete.
     * @var HDIV_T::DIVREM
     * Offset: 0x0C  Remainder Result Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |REMAINDER |Remainder Result
     * |        |          |The remainder of hardware divider is 16-bit sign integer (REMAINDER[15:0]), which holds the remainder result of divider after calculation complete.
     * |        |          |The remainder of hardware divider with sign extension (REMAINDER[31:16]) to 32-bit integer.
     * |        |          |This register holds the remainder result of divider after calculation complete.
     * @var HDIV_T::DIVSTS
     * Offset: 0x10  Divider Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FINISH    |Division Finish Flag
     * |        |          |0 = Under Calculation.
     * |        |          |1 = Calculation finished.
     * |        |          |The flag will become low when the divider is in calculation.
     * |        |          |The flag will go back to high once the calculation finished.
     * |[1]     |DIV0      |Divisor Zero Warning
     * |        |          |0 = The divisor is not 0.
     * |        |          |1 = The divisor is 0.
     * |        |          |Note: The DIV0 flag is used to indicate divide-by-zero situation and updated whenever DIVISOR is written
     * |        |          |This register is read only.
     */
    __IO uint32_t DIVIDEND;              /*!< [0x0000] Dividend Source Register                                         */
    __IO uint32_t DIVISOR;               /*!< [0x0004] Divisor Source Resister                                          */
    __IO uint32_t DIVQUO;                /*!< [0x0008] Quotient Result Resister                                         */
    __IO uint32_t DIVREM;                /*!< [0x000c] Remainder Result Register                                        */
    __I  uint32_t DIVSTS;                /*!< [0x0010] Divider Status Register                                          */

} HDIV_T;

/**
    @addtogroup HDIV_CONST HDIV Bit Field Definition
    Constant Definitions for HDIV Controller
  @{
*/

#define HDIV_DIVIDEND_DIVIDEND_Pos       (0)                                               /*!< HDIV_T::DIVIDEND: DIVIDEND Position    */
#define HDIV_DIVIDEND_DIVIDEND_Msk       (0xfffffffful << HDIV_DIVIDEND_DIVIDEND_Pos)      /*!< HDIV_T::DIVIDEND: DIVIDEND Mask        */

#define HDIV_DIVISOR_DIVISOR_Pos         (0)                                               /*!< HDIV_T::DIVISOR: DIVISOR Position      */
#define HDIV_DIVISOR_DIVISOR_Msk         (0xfffful << HDIV_DIVISOR_DIVISOR_Pos)            /*!< HDIV_T::DIVISOR: DIVISOR Mask          */

#define HDIV_DIVQUO_QUOTIENT_Pos         (0)                                               /*!< HDIV_T::DIVQUO: QUOTIENT Position      */
#define HDIV_DIVQUO_QUOTIENT_Msk         (0xfffffffful << HDIV_DIVQUO_QUOTIENT_Pos)        /*!< HDIV_T::DIVQUO: QUOTIENT Mask          */

#define HDIV_DIVREM_REMAINDER_Pos        (0)                                               /*!< HDIV_T::DIVREM: REMAINDER Position     */
#define HDIV_DIVREM_REMAINDER_Msk        (0xfffffffful << HDIV_DIVREM_REMAINDER_Pos)       /*!< HDIV_T::DIVREM: REMAINDER Mask         */

#define HDIV_DIVSTS_FINISH_Pos           (0)                                               /*!< HDIV_T::DIVSTS: FINISH Position        */
#define HDIV_DIVSTS_FINISH_Msk           (0x1ul << HDIV_DIVSTS_FINISH_Pos)                 /*!< HDIV_T::DIVSTS: FINISH Mask            */

#define HDIV_DIVSTS_DIV0_Pos             (1)                                               /*!< HDIV_T::DIVSTS: DIV0 Position          */
#define HDIV_DIVSTS_DIV0_Msk             (0x1ul << HDIV_DIVSTS_DIV0_Pos)                   /*!< HDIV_T::DIVSTS: DIV0 Mask              */

/**@}*/ /* HDIV_CONST */
/**@}*/ /* end of HDIV register group */
/**@}*/ /* end of REGISTER group */


#endif /* __HDIV_REG_H__ */
