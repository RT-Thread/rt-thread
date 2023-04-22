/**
  ******************************************************************************
  * @file    platform_dma_reg.h
  * @version V1.0
  * @date    2023-03-01
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __HARDWARE_PLATFORM_DMA_H__
#define __HARDWARE_PLATFORM_DMA_H__

/** @brief Number of registers in the REG_DMA peripheral.
 */
#define REG_DMA_COUNT 49

/** @brief Decoding mask of the REG_DMA peripheral registers from the CPU point of view.
 */
#define REG_DMA_DECODING_MASK 0x000000FF

/**
 * @name CH_LLI_ROOT register definitions
 *
 * @{
 */

/// Address of the CH_LLI_ROOT register
//#define DMA_CH_LLI_ROOT_ADDR   0x24A00000
/// Offset of the CH_LLI_ROOT register from the base address
#define DMA_CH_LLI_ROOT_OFFSET 0x00000000
/// Index of the CH_LLI_ROOT register
#define DMA_CH_LLI_ROOT_INDEX  0x00000000
/// Reset value of the CH_LLI_ROOT register
#define DMA_CH_LLI_ROOT_RESET  0x00000000
/// Number of elements of the CH_LLI_ROOT register array
#define DMA_CH_LLI_ROOT_COUNT  4

/// @}

/**
 * @name DMA_STATUS register definitions
 * <table>
 * <caption>DMA_STATUS bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 31    <td>     CH4_STOPPED <td> W <td> R <td> 0
 * <tr><td> 30    <td>  MID_STREAM_BSY <td> W <td> R <td> 0
 * <tr><td> 29    <td> DOWN_STREAM_BSY <td> W <td> R <td> 0
 * <tr><td> 28    <td>   UP_STREAM_BSY <td> W <td> R <td> 0
 * <tr><td> 27    <td>    ARB_Q4_VALID <td> W <td> R <td> 0
 * <tr><td> 26    <td>    ARB_Q3_VALID <td> W <td> R <td> 0
 * <tr><td> 25    <td>    ARB_Q2_VALID <td> W <td> R <td> 0
 * <tr><td> 24    <td>    ARB_Q1_VALID <td> W <td> R <td> 0
 * <tr><td> 23    <td>    ARB_Q0_VALID <td> W <td> R <td> 0
 * <tr><td> 22:20 <td>   REQUEST_STATE <td> W <td> R <td> 0x0
 * <tr><td> 19    <td>     CH3_STOPPED <td> W <td> R <td> 0
 * <tr><td> 18    <td>     CH2_STOPPED <td> W <td> R <td> 0
 * <tr><td> 17    <td>     CH1_STOPPED <td> W <td> R <td> 0
 * <tr><td> 16    <td>     CH0_STOPPED <td> W <td> R <td> 0
 * <tr><td> 15:00 <td>        OFT_FREE <td> W <td> R <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the DMA_STATUS register
//#define DMA_DMA_STATUS_ADDR   0x24A00010
/// Offset of the DMA_STATUS register from the base address
#define DMA_DMA_STATUS_OFFSET 0x00000010
/// Index of the DMA_STATUS register
#define DMA_DMA_STATUS_INDEX  0x00000004
/// Reset value of the DMA_STATUS register
#define DMA_DMA_STATUS_RESET  0x00000000

// field definitions
/// CH4_STOPPED field bit
#define DMA_CH4_STOPPED_BIT        ((uint32_t)0x80000000)
/// CH4_STOPPED field position
#define DMA_CH4_STOPPED_POS        31
/// MID_STREAM_BSY field bit
#define DMA_MID_STREAM_BSY_BIT     ((uint32_t)0x40000000)
/// MID_STREAM_BSY field position
#define DMA_MID_STREAM_BSY_POS     30
/// DOWN_STREAM_BSY field bit
#define DMA_DOWN_STREAM_BSY_BIT    ((uint32_t)0x20000000)
/// DOWN_STREAM_BSY field position
#define DMA_DOWN_STREAM_BSY_POS    29
/// UP_STREAM_BSY field bit
#define DMA_UP_STREAM_BSY_BIT      ((uint32_t)0x10000000)
/// UP_STREAM_BSY field position
#define DMA_UP_STREAM_BSY_POS      28
/// ARB_Q4_VALID field bit
#define DMA_ARB_Q4_VALID_BIT       ((uint32_t)0x08000000)
/// ARB_Q4_VALID field position
#define DMA_ARB_Q4_VALID_POS       27
/// ARB_Q3_VALID field bit
#define DMA_ARB_Q3_VALID_BIT       ((uint32_t)0x04000000)
/// ARB_Q3_VALID field position
#define DMA_ARB_Q3_VALID_POS       26
/// ARB_Q2_VALID field bit
#define DMA_ARB_Q2_VALID_BIT       ((uint32_t)0x02000000)
/// ARB_Q2_VALID field position
#define DMA_ARB_Q2_VALID_POS       25
/// ARB_Q1_VALID field bit
#define DMA_ARB_Q1_VALID_BIT       ((uint32_t)0x01000000)
/// ARB_Q1_VALID field position
#define DMA_ARB_Q1_VALID_POS       24
/// ARB_Q0_VALID field bit
#define DMA_ARB_Q0_VALID_BIT       ((uint32_t)0x00800000)
/// ARB_Q0_VALID field position
#define DMA_ARB_Q0_VALID_POS       23
/// REQUEST_STATE field mask
#define DMA_REQUEST_STATE_MASK     ((uint32_t)0x00700000)
/// REQUEST_STATE field LSB position
#define DMA_REQUEST_STATE_LSB      20
/// REQUEST_STATE field width
#define DMA_REQUEST_STATE_WIDTH    ((uint32_t)0x00000003)
/// CH3_STOPPED field bit
#define DMA_CH3_STOPPED_BIT        ((uint32_t)0x00080000)
/// CH3_STOPPED field position
#define DMA_CH3_STOPPED_POS        19
/// CH2_STOPPED field bit
#define DMA_CH2_STOPPED_BIT        ((uint32_t)0x00040000)
/// CH2_STOPPED field position
#define DMA_CH2_STOPPED_POS        18
/// CH1_STOPPED field bit
#define DMA_CH1_STOPPED_BIT        ((uint32_t)0x00020000)
/// CH1_STOPPED field position
#define DMA_CH1_STOPPED_POS        17
/// CH0_STOPPED field bit
#define DMA_CH0_STOPPED_BIT        ((uint32_t)0x00010000)
/// CH0_STOPPED field position
#define DMA_CH0_STOPPED_POS        16
/// OFT_FREE field mask
#define DMA_OFT_FREE_MASK          ((uint32_t)0x0000FFFF)
/// OFT_FREE field LSB position
#define DMA_OFT_FREE_LSB           0
/// OFT_FREE field width
#define DMA_OFT_FREE_WIDTH         ((uint32_t)0x00000010)

/// CH4_STOPPED field reset value
#define DMA_CH4_STOPPED_RST        0x0
/// MID_STREAM_BSY field reset value
#define DMA_MID_STREAM_BSY_RST     0x0
/// DOWN_STREAM_BSY field reset value
#define DMA_DOWN_STREAM_BSY_RST    0x0
/// UP_STREAM_BSY field reset value
#define DMA_UP_STREAM_BSY_RST      0x0
/// ARB_Q4_VALID field reset value
#define DMA_ARB_Q4_VALID_RST       0x0
/// ARB_Q3_VALID field reset value
#define DMA_ARB_Q3_VALID_RST       0x0
/// ARB_Q2_VALID field reset value
#define DMA_ARB_Q2_VALID_RST       0x0
/// ARB_Q1_VALID field reset value
#define DMA_ARB_Q1_VALID_RST       0x0
/// ARB_Q0_VALID field reset value
#define DMA_ARB_Q0_VALID_RST       0x0
/// REQUEST_STATE field reset value
#define DMA_REQUEST_STATE_RST      0x0
/// CH3_STOPPED field reset value
#define DMA_CH3_STOPPED_RST        0x0
/// CH2_STOPPED field reset value
#define DMA_CH2_STOPPED_RST        0x0
/// CH1_STOPPED field reset value
#define DMA_CH1_STOPPED_RST        0x0
/// CH0_STOPPED field reset value
#define DMA_CH0_STOPPED_RST        0x0
/// OFT_FREE field reset value
#define DMA_OFT_FREE_RST           0x0

/// @}

/**
 * @name INT_RAWSTATUS register definitions
 * <table>
 * <caption>INT_RAWSTATUS bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 24    <td> CH4_EOT <td> W <td> R <td> 0
 * <tr><td> 23    <td> CH3_EOT <td> W <td> R <td> 0
 * <tr><td> 22    <td> CH2_EOT <td> W <td> R <td> 0
 * <tr><td> 21    <td> CH1_EOT <td> W <td> R <td> 0
 * <tr><td> 20    <td> CH0_EOT <td> W <td> R <td> 0
 * <tr><td> 16    <td>   ERROR <td> W <td> R <td> 0
 * <tr><td> 15:00 <td> LLI_IRQ <td> W <td> R <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the INT_RAWSTATUS register
//#define DMA_INT_RAWSTATUS_ADDR   0x24A00014
/// Offset of the INT_RAWSTATUS register from the base address
#define DMA_INT_RAWSTATUS_OFFSET 0x00000014
/// Index of the INT_RAWSTATUS register
#define DMA_INT_RAWSTATUS_INDEX  0x00000005
/// Reset value of the INT_RAWSTATUS register
#define DMA_INT_RAWSTATUS_RESET  0x00000000

// field definitions
/// CH4_EOT field bit
#define DMA_CH4_EOT_BIT    ((uint32_t)0x01000000)
/// CH4_EOT field position
#define DMA_CH4_EOT_POS    24
/// CH3_EOT field bit
#define DMA_CH3_EOT_BIT    ((uint32_t)0x00800000)
/// CH3_EOT field position
#define DMA_CH3_EOT_POS    23
/// CH2_EOT field bit
#define DMA_CH2_EOT_BIT    ((uint32_t)0x00400000)
/// CH2_EOT field position
#define DMA_CH2_EOT_POS    22
/// CH1_EOT field bit
#define DMA_CH1_EOT_BIT    ((uint32_t)0x00200000)
/// CH1_EOT field position
#define DMA_CH1_EOT_POS    21
/// CH0_EOT field bit
#define DMA_CH0_EOT_BIT    ((uint32_t)0x00100000)
/// CH0_EOT field position
#define DMA_CH0_EOT_POS    20
/// ERROR field bit
#define DMA_ERROR_BIT      ((uint32_t)0x00010000)
/// ERROR field position
#define DMA_ERROR_POS      16
/// LLI_IRQ field mask
#define DMA_LLI_IRQ_MASK   ((uint32_t)0x0000FFFF)
/// LLI_IRQ field LSB position
#define DMA_LLI_IRQ_LSB    0
/// LLI_IRQ field width
#define DMA_LLI_IRQ_WIDTH  ((uint32_t)0x00000010)

/// CH4_EOT field reset value
#define DMA_CH4_EOT_RST    0x0
/// CH3_EOT field reset value
#define DMA_CH3_EOT_RST    0x0
/// CH2_EOT field reset value
#define DMA_CH2_EOT_RST    0x0
/// CH1_EOT field reset value
#define DMA_CH1_EOT_RST    0x0
/// CH0_EOT field reset value
#define DMA_CH0_EOT_RST    0x0
/// ERROR field reset value
#define DMA_ERROR_RST      0x0
/// LLI_IRQ field reset value
#define DMA_LLI_IRQ_RST    0x0

/// @}

/**
 * @name INT_UNMASK_SET register definitions
 * <table>
 * <caption>INT_UNMASK_SET bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 24    <td> CH4_EOT <td> R/W <td> S <td> 0
 * <tr><td> 23    <td> CH3_EOT <td> R/W <td> S <td> 0
 * <tr><td> 22    <td> CH2_EOT <td> R/W <td> S <td> 0
 * <tr><td> 21    <td> CH1_EOT <td> R/W <td> S <td> 0
 * <tr><td> 20    <td> CH0_EOT <td> R/W <td> S <td> 0
 * <tr><td> 16    <td>   ERROR <td> R/W <td> S <td> 0
 * <tr><td> 15:00 <td> LLI_IRQ <td> R/W <td> S <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the INT_UNMASK_SET register
//#define DMA_INT_UNMASK_SET_ADDR   0x24A00018
/// Offset of the INT_UNMASK_SET register from the base address
#define DMA_INT_UNMASK_SET_OFFSET 0x00000018
/// Index of the INT_UNMASK_SET register
#define DMA_INT_UNMASK_SET_INDEX  0x00000006
/// Reset value of the INT_UNMASK_SET register
#define DMA_INT_UNMASK_SET_RESET  0x00000000

// field definitions
/// CH4_EOT field bit
#define DMA_CH4_EOT_BIT    ((uint32_t)0x01000000)
/// CH4_EOT field position
#define DMA_CH4_EOT_POS    24
/// CH3_EOT field bit
#define DMA_CH3_EOT_BIT    ((uint32_t)0x00800000)
/// CH3_EOT field position
#define DMA_CH3_EOT_POS    23
/// CH2_EOT field bit
#define DMA_CH2_EOT_BIT    ((uint32_t)0x00400000)
/// CH2_EOT field position
#define DMA_CH2_EOT_POS    22
/// CH1_EOT field bit
#define DMA_CH1_EOT_BIT    ((uint32_t)0x00200000)
/// CH1_EOT field position
#define DMA_CH1_EOT_POS    21
/// CH0_EOT field bit
#define DMA_CH0_EOT_BIT    ((uint32_t)0x00100000)
/// CH0_EOT field position
#define DMA_CH0_EOT_POS    20
/// ERROR field bit
#define DMA_ERROR_BIT      ((uint32_t)0x00010000)
/// ERROR field position
#define DMA_ERROR_POS      16
/// LLI_IRQ field mask
#define DMA_LLI_IRQ_MASK   ((uint32_t)0x0000FFFF)
/// LLI_IRQ field LSB position
#define DMA_LLI_IRQ_LSB    0
/// LLI_IRQ field width
#define DMA_LLI_IRQ_WIDTH  ((uint32_t)0x00000010)

/// CH4_EOT field reset value
#define DMA_CH4_EOT_RST    0x0
/// CH3_EOT field reset value
#define DMA_CH3_EOT_RST    0x0
/// CH2_EOT field reset value
#define DMA_CH2_EOT_RST    0x0
/// CH1_EOT field reset value
#define DMA_CH1_EOT_RST    0x0
/// CH0_EOT field reset value
#define DMA_CH0_EOT_RST    0x0
/// ERROR field reset value
#define DMA_ERROR_RST      0x0
/// LLI_IRQ field reset value
#define DMA_LLI_IRQ_RST    0x0

/// @}

/**
 * @name INT_UNMASK_CLEAR register definitions
 * <table>
 * <caption>INT_UNMASK_CLEAR bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 24    <td> CH4_EOT <td> R/W <td> C <td> 0
 * <tr><td> 23    <td> CH3_EOT <td> R/W <td> C <td> 0
 * <tr><td> 22    <td> CH2_EOT <td> R/W <td> C <td> 0
 * <tr><td> 21    <td> CH1_EOT <td> R/W <td> C <td> 0
 * <tr><td> 20    <td> CH0_EOT <td> R/W <td> C <td> 0
 * <tr><td> 16    <td>   ERROR <td> R/W <td> C <td> 0
 * <tr><td> 15:00 <td> LLI_IRQ <td> R/W <td> C <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the INT_UNMASK_CLEAR register
//#define DMA_INT_UNMASK_CLEAR_ADDR   0x24A0001C
/// Offset of the INT_UNMASK_CLEAR register from the base address
#define DMA_INT_UNMASK_CLEAR_OFFSET 0x0000001C
/// Index of the INT_UNMASK_CLEAR register
#define DMA_INT_UNMASK_CLEAR_INDEX  0x00000007
/// Reset value of the INT_UNMASK_CLEAR register
#define DMA_INT_UNMASK_CLEAR_RESET  0x00000000

/// @}

/**
 * @name INT_ACK register definitions
 * <table>
 * <caption>INT_ACK bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 24    <td> CH4_EOT <td> R/W <td> C <td> 0
 * <tr><td> 23    <td> CH3_EOT <td> R/W <td> C <td> 0
 * <tr><td> 22    <td> CH2_EOT <td> R/W <td> C <td> 0
 * <tr><td> 21    <td> CH1_EOT <td> R/W <td> C <td> 0
 * <tr><td> 20    <td> CH0_EOT <td> R/W <td> C <td> 0
 * <tr><td> 16    <td>   ERROR <td> R/W <td> C <td> 0
 * <tr><td> 15:00 <td> LLI_IRQ <td> R/W <td> C <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the INT_ACK register
//#define DMA_INT_ACK_ADDR   0x24A00020
/// Offset of the INT_ACK register from the base address
#define DMA_INT_ACK_OFFSET 0x00000020
/// Index of the INT_ACK register
#define DMA_INT_ACK_INDEX  0x00000008
/// Reset value of the INT_ACK register
#define DMA_INT_ACK_RESET  0x00000000


// field definitions
/// CH4_EOT field bit
#define DMA_CH4_EOT_BIT    ((uint32_t)0x01000000)
/// CH4_EOT field position
#define DMA_CH4_EOT_POS    24
/// CH3_EOT field bit
#define DMA_CH3_EOT_BIT    ((uint32_t)0x00800000)
/// CH3_EOT field position
#define DMA_CH3_EOT_POS    23
/// CH2_EOT field bit
#define DMA_CH2_EOT_BIT    ((uint32_t)0x00400000)
/// CH2_EOT field position
#define DMA_CH2_EOT_POS    22
/// CH1_EOT field bit
#define DMA_CH1_EOT_BIT    ((uint32_t)0x00200000)
/// CH1_EOT field position
#define DMA_CH1_EOT_POS    21
/// CH0_EOT field bit
#define DMA_CH0_EOT_BIT    ((uint32_t)0x00100000)
/// CH0_EOT field position
#define DMA_CH0_EOT_POS    20
/// ERROR field bit
#define DMA_ERROR_BIT      ((uint32_t)0x00010000)
/// ERROR field position
#define DMA_ERROR_POS      16
/// LLI_IRQ field mask
#define DMA_LLI_IRQ_MASK   ((uint32_t)0x0000FFFF)
/// LLI_IRQ field LSB position
#define DMA_LLI_IRQ_LSB    0
/// LLI_IRQ field width
#define DMA_LLI_IRQ_WIDTH  ((uint32_t)0x00000010)

/// CH4_EOT field reset value
#define DMA_CH4_EOT_RST    0x0
/// CH3_EOT field reset value
#define DMA_CH3_EOT_RST    0x0
/// CH2_EOT field reset value
#define DMA_CH2_EOT_RST    0x0
/// CH1_EOT field reset value
#define DMA_CH1_EOT_RST    0x0
/// CH0_EOT field reset value
#define DMA_CH0_EOT_RST    0x0
/// ERROR field reset value
#define DMA_ERROR_RST      0x0
/// LLI_IRQ field reset value
#define DMA_LLI_IRQ_RST    0x0

/// @}

/**
 * @name INT_STATUS register definitions
 * <table>
 * <caption>INT_STATUS bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 24    <td> CH4_EOT <td> W <td> R <td> 0
 * <tr><td> 23    <td> CH3_EOT <td> W <td> R <td> 0
 * <tr><td> 22    <td> CH2_EOT <td> W <td> R <td> 0
 * <tr><td> 21    <td> CH1_EOT <td> W <td> R <td> 0
 * <tr><td> 20    <td> CH0_EOT <td> W <td> R <td> 0
 * <tr><td> 16    <td>   ERROR <td> W <td> R <td> 0
 * <tr><td> 15:00 <td> LLI_IRQ <td> W <td> R <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the INT_STATUS register
//#define DMA_INT_STATUS_ADDR   0x24A00024
/// Offset of the INT_STATUS register from the base address
#define DMA_INT_STATUS_OFFSET 0x00000024
/// Index of the INT_STATUS register
#define DMA_INT_STATUS_INDEX  0x00000009
/// Reset value of the INT_STATUS register
#define DMA_INT_STATUS_RESET  0x00000000

// field definitions
/// CH4_EOT field bit
#define DMA_CH4_EOT_BIT    ((uint32_t)0x01000000)
/// CH4_EOT field position
#define DMA_CH4_EOT_POS    24
/// CH3_EOT field bit
#define DMA_CH3_EOT_BIT    ((uint32_t)0x00800000)
/// CH3_EOT field position
#define DMA_CH3_EOT_POS    23
/// CH2_EOT field bit
#define DMA_CH2_EOT_BIT    ((uint32_t)0x00400000)
/// CH2_EOT field position
#define DMA_CH2_EOT_POS    22
/// CH1_EOT field bit
#define DMA_CH1_EOT_BIT    ((uint32_t)0x00200000)
/// CH1_EOT field position
#define DMA_CH1_EOT_POS    21
/// CH0_EOT field bit
#define DMA_CH0_EOT_BIT    ((uint32_t)0x00100000)
/// CH0_EOT field position
#define DMA_CH0_EOT_POS    20
/// ERROR field bit
#define DMA_ERROR_BIT      ((uint32_t)0x00010000)
/// ERROR field position
#define DMA_ERROR_POS      16
/// LLI_IRQ field mask
#define DMA_LLI_IRQ_MASK   ((uint32_t)0x0000FFFF)
/// LLI_IRQ field LSB position
#define DMA_LLI_IRQ_LSB    0
/// LLI_IRQ field width
#define DMA_LLI_IRQ_WIDTH  ((uint32_t)0x00000010)

/// CH4_EOT field reset value
#define DMA_CH4_EOT_RST    0x0
/// CH3_EOT field reset value
#define DMA_CH3_EOT_RST    0x0
/// CH2_EOT field reset value
#define DMA_CH2_EOT_RST    0x0
/// CH1_EOT field reset value
#define DMA_CH1_EOT_RST    0x0
/// CH0_EOT field reset value
#define DMA_CH0_EOT_RST    0x0
/// ERROR field reset value
#define DMA_ERROR_RST      0x0
/// LLI_IRQ field reset value
#define DMA_LLI_IRQ_RST    0x0

/// @}

/**
 * @name ARBITRATION register definitions
 * <table>
 * <caption>ARBITRATION bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 03:00 <td> DOWNSTREAM_TAG_USAGE <td> R <td> R/W <td> 0xC
 * </table>
 *
 * @{
 */

/// Address of the ARBITRATION register
//#define DMA_ARBITRATION_ADDR   0x24A00034
/// Offset of the ARBITRATION register from the base address
#define DMA_ARBITRATION_OFFSET 0x00000034
/// Index of the ARBITRATION register
#define DMA_ARBITRATION_INDEX  0x0000000D
/// Reset value of the ARBITRATION register
#define DMA_ARBITRATION_RESET  0x0000000C

// field definitions
/// DOWNSTREAM_TAG_USAGE field mask
#define DMA_DOWNSTREAM_TAG_USAGE_MASK   ((uint32_t)0x0000000F)
/// DOWNSTREAM_TAG_USAGE field LSB position
#define DMA_DOWNSTREAM_TAG_USAGE_LSB    0
/// DOWNSTREAM_TAG_USAGE field width
#define DMA_DOWNSTREAM_TAG_USAGE_WIDTH  ((uint32_t)0x00000004)

/// DOWNSTREAM_TAG_USAGE field reset value
#define DMA_DOWNSTREAM_TAG_USAGE_RST    0xC

/// @}

/**
 * @name CHANNEL_MUTEX_SET register definitions
 * <table>
 * <caption>CHANNEL_MUTEX_SET bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 04 <td> CH4_MUTEX <td> R/W <td> S <td> 0
 * <tr><td> 03 <td> CH3_MUTEX <td> R/W <td> S <td> 0
 * <tr><td> 02 <td> CH2_MUTEX <td> R/W <td> S <td> 0
 * <tr><td> 01 <td> CH1_MUTEX <td> R/W <td> S <td> 0
 * <tr><td> 00 <td> CH0_MUTEX <td> R/W <td> S <td> 0
 * </table>
 *
 * @{
 */

/// Address of the CHANNEL_MUTEX_SET register
//#define DMA_CHANNEL_MUTEX_SET_ADDR   0x24A00038
/// Offset of the CHANNEL_MUTEX_SET register from the base address
#define DMA_CHANNEL_MUTEX_SET_OFFSET 0x00000038
/// Index of the CHANNEL_MUTEX_SET register
#define DMA_CHANNEL_MUTEX_SET_INDEX  0x0000000E
/// Reset value of the CHANNEL_MUTEX_SET register
#define DMA_CHANNEL_MUTEX_SET_RESET  0x00000000

// field definitions
/// CH4_MUTEX field bit
#define DMA_CH4_MUTEX_BIT    ((uint32_t)0x00000010)
/// CH4_MUTEX field position
#define DMA_CH4_MUTEX_POS    4
/// CH3_MUTEX field bit
#define DMA_CH3_MUTEX_BIT    ((uint32_t)0x00000008)
/// CH3_MUTEX field position
#define DMA_CH3_MUTEX_POS    3
/// CH2_MUTEX field bit
#define DMA_CH2_MUTEX_BIT    ((uint32_t)0x00000004)
/// CH2_MUTEX field position
#define DMA_CH2_MUTEX_POS    2
/// CH1_MUTEX field bit
#define DMA_CH1_MUTEX_BIT    ((uint32_t)0x00000002)
/// CH1_MUTEX field position
#define DMA_CH1_MUTEX_POS    1
/// CH0_MUTEX field bit
#define DMA_CH0_MUTEX_BIT    ((uint32_t)0x00000001)
/// CH0_MUTEX field position
#define DMA_CH0_MUTEX_POS    0

/// CH4_MUTEX field reset value
#define DMA_CH4_MUTEX_RST    0x0
/// CH3_MUTEX field reset value
#define DMA_CH3_MUTEX_RST    0x0
/// CH2_MUTEX field reset value
#define DMA_CH2_MUTEX_RST    0x0
/// CH1_MUTEX field reset value
#define DMA_CH1_MUTEX_RST    0x0
/// CH0_MUTEX field reset value
#define DMA_CH0_MUTEX_RST    0x0

/// @}

/**
 * @name CHANNEL_MUTEX_CLEAR register definitions
 * <table>
 * <caption>CHANNEL_MUTEX_CLEAR bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 04 <td> CH4_MUTEX <td> R/W <td> C <td> 0
 * <tr><td> 03 <td> CH3_MUTEX <td> R/W <td> C <td> 0
 * <tr><td> 02 <td> CH2_MUTEX <td> R/W <td> C <td> 0
 * <tr><td> 01 <td> CH1_MUTEX <td> R/W <td> C <td> 0
 * <tr><td> 00 <td> CH0_MUTEX <td> R/W <td> C <td> 0
 * </table>
 *
 * @{
 */

/// Address of the CHANNEL_MUTEX_CLEAR register
//#define DMA_CHANNEL_MUTEX_CLEAR_ADDR   0x24A0003C
/// Offset of the CHANNEL_MUTEX_CLEAR register from the base address
#define DMA_CHANNEL_MUTEX_CLEAR_OFFSET 0x0000003C
/// Index of the CHANNEL_MUTEX_CLEAR register
#define DMA_CHANNEL_MUTEX_CLEAR_INDEX  0x0000000F
/// Reset value of the CHANNEL_MUTEX_CLEAR register
#define DMA_CHANNEL_MUTEX_CLEAR_RESET  0x00000000

/// @}

/**
 * @name CH4_LLI_ROOT register definitions
 * <table>
 * <caption>CH4_LLI_ROOT bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 31:00 <td> CH4_LLI_ROOT <td> R <td> R/W <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the CH4_LLI_ROOT register
//#define DMA_CH4_LLI_ROOT_ADDR   0x24A00040
/// Offset of the CH4_LLI_ROOT register from the base address
#define DMA_CH4_LLI_ROOT_OFFSET 0x00000040
/// Index of the CH4_LLI_ROOT register
#define DMA_CH4_LLI_ROOT_INDEX  0x00000010
/// Reset value of the CH4_LLI_ROOT register
#define DMA_CH4_LLI_ROOT_RESET  0x00000000

// field definitions
/// CH4_LLI_ROOT field mask
#define DMA_CH4_LLI_ROOT_MASK   ((uint32_t)0xFFFFFFFF)
/// CH4_LLI_ROOT field LSB position
#define DMA_CH4_LLI_ROOT_LSB    0
/// CH4_LLI_ROOT field width
#define DMA_CH4_LLI_ROOT_WIDTH  ((uint32_t)0x00000020)

/// CH4_LLI_ROOT field reset value
#define DMA_CH4_LLI_ROOT_RST    0x0

/// @}

/**
 * @name LLI_COUNTER register definitions
 * <table>
 * <caption>LLI_COUNTER bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 15:00 <td> COUNTER <td> W <td> R <td> 0x0
 * </table>
 *
 * @{
 */

/// Address of the LLI_COUNTER register
//#define DMA_LLI_COUNTER_ADDR   0x24A00080
/// Offset of the LLI_COUNTER register from the base address
#define DMA_LLI_COUNTER_OFFSET 0x00000080
/// Index of the LLI_COUNTER register
#define DMA_LLI_COUNTER_INDEX  0x00000020
/// Reset value of the LLI_COUNTER register
#define DMA_LLI_COUNTER_RESET  0x00000000
/// Number of elements of the LLI_COUNTER register array
#define DMA_LLI_COUNTER_COUNT  16

// field definitions
/// COUNTER field mask
#define DMA_COUNTER_MASK   ((uint32_t)0x0000FFFF)
/// COUNTER field LSB position
#define DMA_COUNTER_LSB    0
/// COUNTER field width
#define DMA_COUNTER_WIDTH  ((uint32_t)0x00000010)

/// COUNTER field reset value
#define DMA_COUNTER_RST    0x0

/// @}

/**
 * @name DUMMY register definitions
 * <table>
 * <caption>DUMMY bitfields</caption>
 * <tr><th>Bits <th>Field Name <th>HW Access <th>SW Access <th>Reset Value
 * <tr><td> 00 <td> DUMMY <td> R <td> R/W <td> 0
 * </table>
 *
 * @{
 */

/// Address of the DUMMY register
//#define DMA_DUMMY_ADDR   0x24A000C0
/// Offset of the DUMMY register from the base address
#define DMA_DUMMY_OFFSET 0x000000C0
/// Index of the DUMMY register
#define DMA_DUMMY_INDEX  0x00000030
/// Reset value of the DUMMY register
#define DMA_DUMMY_RESET  0x00000000

// field definitions
/// DUMMY field bit
#define DMA_DUMMY_BIT    ((uint32_t)0x00000001)
/// DUMMY field position
#define DMA_DUMMY_POS    0

/// DUMMY field reset value
#define DMA_DUMMY_RST    0x0


/// @}

#endif /* __HARDWARE_PLATFORM_DMA_H__ */
