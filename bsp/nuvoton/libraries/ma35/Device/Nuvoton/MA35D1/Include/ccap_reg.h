/**************************************************************************//**
 * @file     ccap_reg.h
 * @version  V3.00
 * @brief    CCAP register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CCAP_REG_H__
#define __CCAP_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CCAP Camera Capture Interface Controller (CCAP)
    Memory Mapped Structure for CCAP Controller
@{ */


typedef struct
{


    /**
     * @var CCAP_T::CTL
     * Offset: 0x00  Camera Capture Interface Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CCAPEN    |Camera Capture Interface Enable Bit
     * |        |          |0 = Camera Capture Interface Disabled.
     * |        |          |1 = Camera Capture Interface Enabled.
     * |[6]     |PKTEN     |Packet Output Enable Bit
     * |        |          |0 = Packet output Disabled.
     * |        |          |1 = Packet output Enabled.
     * |[7]     |MONO      |Monochrome CMOS Sensor Select
     * |        |          |0 = Color CMOS Sensor.
     * |        |          |1 = Monochrome CMOS Sensor. The U/V components are ignored when the MONO is enabled.
     * |[16]    |SHUTTER   |Camera Capture Interface Automatically Disable the Capture Interface After a Frame Had Been Captured
     * |        |          |0 = Shutter Disabled.
     * |        |          |1 = Shutter Enabled.
     * |[17]    |MY4_SWAP  |Monochrome CMOS Sensor 4-bit Data Nibble Swap
     * |        |          |0 = The 4-bit data input sequence: 1st Pixel is for 1st Nibble (1st pixel at MSB).
     * |        |          |1 = The 4-bit data input sequence: 1st Pixel is for 2nd Nibble (1st pixel at LSB).
     * |[18]    |MY8_MY4   |Monochrome CMOS Sensor Data I/O Interface
     * |        |          |0 = Monochrome CMOS sensor is by the 4-bit data I/O interface.
     * |        |          |1 = Monochrome CMOS sensor is by the 8-bit data I/O interface.
     * |[19]    |Luma_Y_One|Color/Monochrome CMOS Sensor Luminance 8-bit Y to 1-bit Y Conversion
     * |        |          |0 = Color/Monochrome CMOS sensor Luma-Y-One bit Disabled.
     * |        |          |1 = Color/Monochrome CMOS sensor Luma-Y-One bit Enabled.
     * |        |          |Note: Color CMOS sensor U/V components are ignored when the Luma_Y_One is enabled.
     * |[20]    |UPDATE    |Update Register at New Frame
     * |        |          |0 = Update register at new frame Disabled.
     * |        |          |1 = Update register at new frame Enabled (Auto clear to 0 when register updated).
     * |[24]    |VPRST     |Capture Interface Reset
     * |        |          |0 = Capture interface reset Disabled.
     * |        |          |1 = Capture interface reset Enabled.
     * @var CCAP_T::PAR
     * Offset: 0x04  Camera Capture Interface Parameter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INFMT     |Sensor Input Data Format
     * |        |          |0 = YCbCr422.
     * |        |          |1 = RGB565.
     * |[1]     |SENTYPE   |Sensor Input Type
     * |        |          |0 = CCIR601.
     * |        |          |1 = CCIR656, VSync & Hsync embedded in the data signal.
     * |[3:2]   |INDATORD  |Sensor Input Data Order
     * |        |          |If INFMT (CCAP_PAR[0]) = 0 (YCbCr):
     * |        |          |00 = Sensor input data (Byte 0 1 2 3) is Y0 U0 Y1 V0.
     * |        |          |01 = Sensor input data (Byte 0 1 2 3) is Y0 V0 Y1 U0.
     * |        |          |10 = Sensor input data (Byte 0 1 2 3) is U0 Y0 V0 Y1.
     * |        |          |11 = Sensor input data (Byte 0 1 2 3) is V0 Y0 U0 Y1.
     * |        |          |If INFMT (CCAP_PAR[0]) = 1 (RGB565):
     * |        |          |00 = Sensor input data (Byte 0) is {R[4:0],G[5:3]}. Sensor input data (Byte 1) is {G[2:0], B[4:0]}.
     * |        |          |01 = Sensor input data (Byte 0) is {B[4:0],G[5:3]}. Sensor input data (Byte 1) is {G[2:0], R[4:0]}.
     * |        |          |10 = Sensor input data (Byte 0) is {G[2:0],B[4:0]}. Sensor input data (Byte 1) is {R[4:0], G[5:3]}.
     * |        |          |11 = Sensor input data (Byte 0) is {G[2:0],R[4:0]}. Sensor input data (Byte 1) is {B[4:0], G[5:3]}.
     * |[5:4]   |OUTFMT    |Image Data Format Output to System Memory
     * |        |          |00 = YCbCr422.
     * |        |          |01 = Only output Y. (Select this format when CCAP_CTL "Luma_Y_One" or "MONO" enabled).
     * |        |          |10 = RGB555.
     * |        |          |11 = RGB565.
     * |[6]     |RANGE     |Scale Input YUV CCIR601 Color Range to Full Range
     * |        |          |0 = Default.
     * |        |          |1 = Scale to full range.
     * |[8]     |PCLKP     |Sensor Pixel Clock Polarity
     * |        |          |0 = Input video data and signals are latched by falling edge of Pixel Clock.
     * |        |          |1 = Input video data and signals are latched by rising edge of Pixel Clock.
     * |[9]     |HSP       |Sensor Hsync Polarity
     * |        |          |0 = Sync Low.
     * |        |          |1 = Sync High.
     * |[10]    |VSP       |Sensor Vsync Polarity
     * |        |          |0 = Sync Low.
     * |        |          |1 = Sync High.
     * |[18]    |FBB       |Field by Blank
     * |        |          |Field by Blank (only in ccir-656 mode) means blanking pixel data(0x80108010) have to transfer to system memory or not.
     * |        |          |0 = Field by blank Disabled. (blank pixel data will transfer to system memory).
     * |        |          |1 = Field by blank Enabled. (only active data will transfer to system memory).
     * @var CCAP_T::INT
     * Offset: 0x08  Camera Capture Interface Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |VINTF     |Video Frame End Interrupt
     * |        |          |0 = Did not receive a frame completely.
     * |        |          |1 = Received a frame completely.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[1]     |MEINTF    |Bus Master Transfer Error Interrupt
     * |        |          |0 = Transfer Error did not occur.
     * |        |          |1 = Transfer Error occurred.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[3]     |ADDRMINTF |Memory Address Match Interrupt
     * |        |          |0 = Memory Address Match Interrupt did not occur.
     * |        |          |1 = Memory Address Match Interrupt occurred.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[16]    |VIEN      |Video Frame End Interrupt Enable Bit
     * |        |          |0 = Video frame end interrupt Disabled.
     * |        |          |1 = Video frame end interrupt Enabled.
     * |[17]    |MEIEN     |Bus Master Transfer Error Interrupt Enable Bit
     * |        |          |0 = Bus Master Transfer error interrupt Disabled.
     * |        |          |1 = Bus Master Transfer error interrupt Enabled.
     * |[19]    |ADDRMIEN  |Memory Address Match Interrupt Enable Bit
     * |        |          |0 = Memory address match interrupt Disabled.
     * |        |          |1 = Memory address match interrupt Enabled.
     * @var CCAP_T::CWSP
     * Offset: 0x20  Cropping Window Starting Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |CWSADDRH  |Cropping Window Horizontal Starting Address
     * |        |          |Specify the value of the cropping window horizontal start address.
     * |[26:16] |CWSADDRV  |Cropping Window Vertical Starting Address
     * |        |          |Specify the value of the cropping window vertical start address.
     * @var CCAP_T::CWS
     * Offset: 0x24  Cropping Window Size Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |CWW       |Cropping Window Width
     * |        |          |Specify the size of the cropping window width.
     * |[26:16] |CWH       |Cropping Window Height
     * |        |          |Specify the size of the cropping window height.
     * @var CCAP_T::PKTSL
     * Offset: 0x28  Packet Scaling Vertical/Horizontal Factor Register (LSB)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PKTSHML   |Packet Scaling Horizontal Factor M
     * |        |          |Specifies the lower 8-bit of denominator part (M) of the horizontal scaling factor.
     * |        |          |The lower 8-bit will be cascaded with higher 8-bit (PKDSHMH) to form a 16-bit denominator (M) of vertical factor.
     * |        |          |The output image width will be equal to the image width * N/M.
     * |        |          |Note: The value of N must be equal to or less than M.
     * |[15:8]  |PKTSHNL   |Packet Scaling Horizontal Factor N
     * |        |          |Specify the lower 8-bit of numerator part (N) of the horizontal scaling factor.
     * |        |          |The lower 8-bit will be cascaded with higher 8-bit (PKDSHNH) to form a 16-bit numerator of horizontal factor.
     * |[23:16] |PKTSVML   |Packet Scaling Vertical Factor M
     * |        |          |Specify the lower 8-bit of denominator part (M) of the vertical scaling factor.
     * |        |          |The lower 8-bit will be cascaded with higher 8-bit (PKDSVMH) to form a 16-bit denominator (M) of vertical factor.
     * |        |          |The output image width will be equal to the image height * N/M.
     * |        |          |Note: The value of N must be equal to or less than M.
     * |[31:24] |PKTSVNL   |Packet Scaling Vertical Factor N
     * |        |          |Specify the lower 8-bit of numerator part (N) of the vertical scaling factor.
     * |        |          |The lower 8-bit will be cascaded with higher 8-bit (PKDSVNH) to form a 16-bit numerator of vertical factor.
     * @var CCAP_T::FRCTL
     * Offset: 0x30  Scaling Frame Rate Factor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |FRM       |Scaling Frame Rate Factor M
     * |        |          |Specify the denominator part (M) of the frame rate scaling factor.
     * |        |          |The output image frame rate will be equal to input image frame rate * (N/M).
     * |        |          |Note: The value of N must be equal to or less than M.
     * |[13:8]  |FRN       |Scaling Frame Rate Factor N
     * |        |          |Specify the numerator part (N) of the frame rate scaling factor.
     * @var CCAP_T::STRIDE
     * Offset: 0x34  Frame Output Pixel Stride Width Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[13:0]  |PKTSTRIDE |Packet Frame Output Pixel Stride Width
     * |        |          |The output pixel stride size of packet pipe.
     * |        |          |It is a 32-pixel aligned stride width for the Luma-Y-One bit format or a 4-pixel aligned stride with for the Luma-Y-Eight bit format when color or monochrome CMOS sensors used.
     * |        |          |This means that every new captured line is by word alignment address when color or monochrome CMOS sensors used.
     * @var CCAP_T::FIFOTH
     * Offset: 0x3C  FIFO Threshold Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[28:24] |PKTFTH    |Packet FIFO Threshold
     * |        |          |Specify the 5-bit value of the packet FIFO threshold.
     * |[31]    |OVF       |FIFO Overflow Flag
     * |        |          |Indicate the FIFO overflow flag.
     * @var CCAP_T::CMPADDR
     * Offset: 0x40  Compare Memory Base Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CMPADDR   |Compare Memory Base Address
     * |        |          |It is a word alignment address, that is, the address is aligned by ignoring the 2 LSB bits [1:0].
     * @var CCAP_T::LUMA_Y1_THD
     * Offset: 0x44  Luminance Y8 to Y1 Threshold Value Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field          |Descriptions
     * | :----: | :-----------: | :---- |
     * |[7:0]   |LUMA_Y1_THRESH |Luminance Y8 to Y1 Threshold Value
     * |        |               |Specify the 8-bit threshold value for the luminance Y bit-8 to the luminance Y 1-bit conversion.
     * @var CCAP_T::PKTSM
     * Offset: 0x48  Packet Scaling Vertical/Horizontal Factor Register (MSB)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PKTSHMH   |Packet Scaling Horizontal Factor M
     * |        |          |Specify the higher 8-bit of denominator part (M) of the horizontal scaling factor.
     * |        |          |Please refer to the register CCAP_PKTSL for the detailed operation.
     * |[15:8]  |PKTSHNH   |Packet Scaling Horizontal Factor N
     * |        |          |Specify the higher 8-bit of numerator part (N) of the horizontal scaling factor.
     * |        |          |Please refer to the register CCAP_PKTSL for the detailed operation.
     * |[23:16] |PKTSVMH   |Packet Scaling Vertical Factor M
     * |        |          |Specify the higher 8-bit of denominator part (M) of the vertical scaling factor.
     * |        |          |Please refer to the register CCAP_PKTSL to check the cooperation between these two registers.
     * |[31:24] |PKTSVNH   |Packet Scaling Vertical Factor N
     * |        |          |Specify the higher 8-bit of numerator part (N) of the vertical scaling factor.
     * |        |          |Please refer to the register CCAP_PKTSL to check the cooperation between these two registers.
     * @var CCAP_T::CURADDRP
     * Offset: 0x50  Current Packet System Memory Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURADDR   |Current Packet Output Memory Address
     * |        |          |Specify the 32-bit value of the current packet output memory address.
     * @var CCAP_T::PKTBA0
     * Offset: 0x60  System Memory Packet Base Address 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |BASEADDR  |System Memory Packet Base Address 0
     * |        |          |It is a word alignment address, that is, the address is aligned by ignoring the 2 LSB bits [1:0].
     */
    __IO uint32_t CTL;                   /*!< [0x0000] Camera Capture Interface Control Register                        */
    __IO uint32_t PAR;                   /*!< [0x0004] Camera Capture Interface Parameter Register                      */
    __IO uint32_t INT;                   /*!< [0x0008] Camera Capture Interface Interrupt Register                      */
    __I  uint32_t RESERVE0[5];
    __IO uint32_t CWSP;                  /*!< [0x0020] Cropping Window Starting Address Register                        */
    __IO uint32_t CWS;                   /*!< [0x0024] Cropping Window Size Register                                    */
    __IO uint32_t PKTSL;                 /*!< [0x0028] Packet Scaling Vertical/Horizontal Factor Register (LSB)         */
    __IO uint32_t PLNSL;                 /*!< [0x002C] Planar Scaling Vertical/Horizontal Factor Register (LSB)         */
    __IO uint32_t FRCTL;                 /*!< [0x0030] Scaling Frame Rate Factor Register                               */
    __IO uint32_t STRIDE;                /*!< [0x0034] Frame Output Pixel Stride Width Register                         */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t FIFOTH;                /*!< [0x003C] FIFO Threshold Register                                          */
    __IO uint32_t CMPADDR;               /*!< [0x0040] Compare Memory Base Address Register                             */
    __IO uint32_t LUMA_Y1_THD;           /*!< [0x0044] Luminance Y8 to Y1 Threshold Value Register                      */
    __IO uint32_t PKTSM;                 /*!< [0x0048] Packet Scaling Vertical/Horizontal Factor Register (MSB)         */
    __IO uint32_t PLNSM;                 /*!< [0x004C] Planar Scaling Vertical/Horizontal Factor Register (MSB)         */
    __I  uint32_t CURADDRP;              /*!< [0x0050] Current Packet System Memory Address Register                    */
    __I  uint32_t CURADDRY;              /*!< [0x0054] Current Planar Y System Memory Address Register                    */
    __I  uint32_t CURADDRU;              /*!< [0x0058] Current Planar U System Memory Address Register                    */
    __I  uint32_t CURADDRV;              /*!< [0x005C] Current Planar V System Memory Address Register                    */
    __IO uint32_t PKTBA0;                /*!< [0x0060] System Memory Packet Base Address 0 Register                     */
    __I  uint32_t RESERVE4[7];
    __IO uint32_t YBA;                   /*!< [0x0080] System Memory Planar Y Base Address Register                     */
    __IO uint32_t UBA;                   /*!< [0x0084] System Memory Planar U Base Address Register                     */
    __IO uint32_t VBA;                   /*!< [0x0088] System Memory Planar V Base Address Register                     */
} CCAP_T;

/**
    @addtogroup CCAP_CONST CCAP Bit Field Definition
    Constant Definitions for CCAP Controller
@{ */

#define CCAP_CTL_CCAPEN_Pos               (0)                                               /*!< CCAP_T::CTL: CCAPEN Position               */
#define CCAP_CTL_CCAPEN_Msk               (0x1ul << CCAP_CTL_CCAPEN_Pos)                    /*!< CCAP_T::CTL: CCAPEN Mask                   */

#define CCAP_CTL_PLNEN_Pos                (5)                                               /*!< CCAP_T::CTL: PLNEN Position                */
#define CCAP_CTL_PLNEN_Msk                (0x1ul << CCAP_CTL_PLNEN_Pos)                     /*!< CCAP_T::CTL: PLNEN Mask                    */

#define CCAP_CTL_PKTEN_Pos                (6)                                               /*!< CCAP_T::CTL: PKTEN Position                */
#define CCAP_CTL_PKTEN_Msk                (0x1ul << CCAP_CTL_PKTEN_Pos)                     /*!< CCAP_T::CTL: PKTEN Mask                    */

#define CCAP_CTL_MONO_Pos                 (7)                                               /*!< CCAP_T::CTL: MONO Position                 */
#define CCAP_CTL_MONO_Msk                 (0x1ul << CCAP_CTL_MONO_Pos)                      /*!< CCAP_T::CTL: MONO Mask                     */

#define CCAP_CTL_SHUTTER_Pos              (16)                                              /*!< CCAP_T::CTL: SHUTTER Position              */
#define CCAP_CTL_SHUTTER_Msk              (0x1ul << CCAP_CTL_SHUTTER_Pos)                   /*!< CCAP_T::CTL: SHUTTER Mask                  */

#define CCAP_CTL_MY4_SWAP_Pos             (17)                                              /*!< CCAP_T::CTL: MY4_SWAP Position             */
#define CCAP_CTL_MY4_SWAP_Msk             (0x1ul << CCAP_CTL_MY4_SWAP_Pos)                  /*!< CCAP_T::CTL: MY4_SWAP Mask                 */

#define CCAP_CTL_MY8_MY4_Pos              (18)                                              /*!< CCAP_T::CTL: MY8_MY4 Position              */
#define CCAP_CTL_MY8_MY4_Msk              (0x1ul << CCAP_CTL_MY8_MY4_Pos)                   /*!< CCAP_T::CTL: MY8_MY4 Mask                  */

#define CCAP_CTL_Luma_Y_One_Pos           (19)                                              /*!< CCAP_T::CTL: Luma_Y_One Position           */
#define CCAP_CTL_Luma_Y_One_Msk           (0x1ul << CCAP_CTL_Luma_Y_One_Pos)                /*!< CCAP_T::CTL: Luma_Y_One Mask               */

#define CCAP_CTL_UPDATE_Pos               (20)                                              /*!< CCAP_T::CTL: UPDATE Position               */
#define CCAP_CTL_UPDATE_Msk               (0x1ul << CCAP_CTL_UPDATE_Pos)                    /*!< CCAP_T::CTL: UPDATE Mask                   */

#define CCAP_CTL_VPRST_Pos                (24)                                              /*!< CCAP_T::CTL: VPRST Position                */
#define CCAP_CTL_VPRST_Msk                (0x1ul << CCAP_CTL_VPRST_Pos)                     /*!< CCAP_T::CTL: VPRST Mask                    */

#define CCAP_PAR_INFMT_Pos                (0)                                               /*!< CCAP_T::PAR: INFMT Position                */
#define CCAP_PAR_INFMT_Msk                (0x1ul << CCAP_PAR_INFMT_Pos)                     /*!< CCAP_T::PAR: INFMT Mask                    */

#define CCAP_PAR_SENTYPE_Pos              (1)                                               /*!< CCAP_T::PAR: SENTYPE Position              */
#define CCAP_PAR_SENTYPE_Msk              (0x1ul << CCAP_PAR_SENTYPE_Pos)                   /*!< CCAP_T::PAR: SENTYPE Mask                  */

#define CCAP_PAR_INDATORD_Pos             (2)                                               /*!< CCAP_T::PAR: INDATORD Position             */
#define CCAP_PAR_INDATORD_Msk             (0x3ul << CCAP_PAR_INDATORD_Pos)                  /*!< CCAP_T::PAR: INDATORD Mask                 */

#define CCAP_PAR_PLNFMT_Pos               (7)                                               /*!< CCAP_T::PAR: OUTFMT Position               */
#define CCAP_PAR_PLNFMT_Msk               (0x1ul << CCAP_PAR_OUTFMT_Pos)                    /*!< CCAP_T::PAR: OUTFMT Mask                   */

#define CCAP_PAR_OUTFMT_Pos               (4)                                               /*!< CCAP_T::PAR: OUTFMT Position               */
#define CCAP_PAR_OUTFMT_Msk               (0x3ul << CCAP_PAR_OUTFMT_Pos)                    /*!< CCAP_T::PAR: OUTFMT Mask                   */

#define CCAP_PAR_RANGE_Pos                (6)                                               /*!< CCAP_T::PAR: RANGE Position                */
#define CCAP_PAR_RANGE_Msk                (0x1ul << CCAP_PAR_RANGE_Pos)                     /*!< CCAP_T::PAR: RANGE Mask                    */

#define CCAP_PAR_PCLKP_Pos                (8)                                               /*!< CCAP_T::PAR: PCLKP Position                */
#define CCAP_PAR_PCLKP_Msk                (0x1ul << CCAP_PAR_PCLKP_Pos)                     /*!< CCAP_T::PAR: PCLKP Mask                    */

#define CCAP_PAR_HSP_Pos                  (9)                                               /*!< CCAP_T::PAR: HSP Position                  */
#define CCAP_PAR_HSP_Msk                  (0x1ul << CCAP_PAR_HSP_Pos)                       /*!< CCAP_T::PAR: HSP Mask                      */

#define CCAP_PAR_VSP_Pos                  (10)                                              /*!< CCAP_T::PAR: VSP Position                  */
#define CCAP_PAR_VSP_Msk                  (0x1ul << CCAP_PAR_VSP_Pos)                       /*!< CCAP_T::PAR: VSP Mask                      */

#define CCAP_PAR_FBB_Pos                  (18)                                              /*!< CCAP_T::PAR: FBB Position                  */
#define CCAP_PAR_FBB_Msk                  (0x1ul << CCAP_PAR_FBB_Pos)                       /*!< CCAP_T::PAR: FBB Mask                      */

#define CCAP_INT_VINTF_Pos                (0)                                               /*!< CCAP_T::INT: VINTF Position                */
#define CCAP_INT_VINTF_Msk                (0x1ul << CCAP_INT_VINTF_Pos)                     /*!< CCAP_T::INT: VINTF Mask                    */

#define CCAP_INT_MEINTF_Pos               (1)                                               /*!< CCAP_T::INT: MEINTF Position               */
#define CCAP_INT_MEINTF_Msk               (0x1ul << CCAP_INT_MEINTF_Pos)                    /*!< CCAP_T::INT: MEINTF Mask                   */

#define CCAP_INT_ADDRMINTF_Pos            (3)                                               /*!< CCAP_T::INT: ADDRMINTF Position            */
#define CCAP_INT_ADDRMINTF_Msk            (0x1ul << CCAP_INT_ADDRMINTF_Pos)                 /*!< CCAP_T::INT: ADDRMINTF Mask                */

#define CCAP_INT_VIEN_Pos                 (16)                                              /*!< CCAP_T::INT: VIEN Position                 */
#define CCAP_INT_VIEN_Msk                 (0x1ul << CCAP_INT_VIEN_Pos)                      /*!< CCAP_T::INT: VIEN Mask                     */

#define CCAP_INT_MEIEN_Pos                (17)                                              /*!< CCAP_T::INT: MEIEN Position                */
#define CCAP_INT_MEIEN_Msk                (0x1ul << CCAP_INT_MEIEN_Pos)                     /*!< CCAP_T::INT: MEIEN Mask                    */

#define CCAP_INT_ADDRMIEN_Pos             (19)                                              /*!< CCAP_T::INT: ADDRMIEN Position             */
#define CCAP_INT_ADDRMIEN_Msk             (0x1ul << CCAP_INT_ADDRMIEN_Pos)                  /*!< CCAP_T::INT: ADDRMIEN Mask                 */

#define CCAP_CWSP_CWSADDRH_Pos            (0)                                               /*!< CCAP_T::CWSP: CWSADDRH Position            */
#define CCAP_CWSP_CWSADDRH_Msk            (0xffful << CCAP_CWSP_CWSADDRH_Pos)               /*!< CCAP_T::CWSP: CWSADDRH Mask                */

#define CCAP_CWSP_CWSADDRV_Pos            (16)                                              /*!< CCAP_T::CWSP: CWSADDRV Position            */
#define CCAP_CWSP_CWSADDRV_Msk            (0x7fful << CCAP_CWSP_CWSADDRV_Pos)               /*!< CCAP_T::CWSP: CWSADDRV Mask                */

#define CCAP_CWS_CWW_Pos                  (0)                                               /*!< CCAP_T::CWS: CWW Position                  */
#define CCAP_CWS_CWW_Msk                  (0xffful << CCAP_CWS_CWW_Pos)                     /*!< CCAP_T::CWS: CWW Mask                      */

#define CCAP_CWS_CWH_Pos                  (16)                                              /*!< CCAP_T::CWS: CIWH Position                 */
#define CCAP_CWS_CWH_Msk                  (0x7fful << CCAP_CWS_CWH_Pos)                     /*!< CCAP_T::CWS: CIWH Mask                     */

#define CCAP_PKTSL_PKTSHML_Pos            (0)                                               /*!< CCAP_T::PKTSL: PKTSHML Position            */
#define CCAP_PKTSL_PKTSHML_Msk            (0xfful << CCAP_PKTSL_PKTSHML_Pos)                /*!< CCAP_T::PKTSL: PKTSHML Mask                */

#define CCAP_PKTSL_PKTSHNL_Pos            (8)                                               /*!< CCAP_T::PKTSL: PKTSHNL Position            */
#define CCAP_PKTSL_PKTSHNL_Msk            (0xfful << CCAP_PKTSL_PKTSHNL_Pos)                /*!< CCAP_T::PKTSL: PKTSHNL Mask                */

#define CCAP_PKTSL_PKTSVML_Pos            (16)                                              /*!< CCAP_T::PKTSL: PKTSVML Position            */
#define CCAP_PKTSL_PKTSVML_Msk            (0xfful << CCAP_PKTSL_PKTSVML_Pos)                /*!< CCAP_T::PKTSL: PKTSVML Mask                */

#define CCAP_PKTSL_PKTSVNL_Pos            (24)                                              /*!< CCAP_T::PKTSL: PKTSVNL Position            */
#define CCAP_PKTSL_PKTSVNL_Msk            (0xfful << CCAP_PKTSL_PKTSVNL_Pos)                /*!< CCAP_T::PKTSL: PKTSVNL Mask                */

#define CCAP_PLNSL_PLNSHML_Pos            (0)                                               /*!< CCAP_T::PLNSL: PLNSHML Position            */
#define CCAP_PLNSL_PLNSHML_Msk            (0xfful << CCAP_PLNSL_PLNSHML_Pos)                /*!< CCAP_T::PLNSL: PLNSHML Mask                */

#define CCAP_PLNSL_PLNSHNL_Pos            (8)                                               /*!< CCAP_T::PLNSL: PLNSHNL Position            */
#define CCAP_PLNSL_PLNSHNL_Msk            (0xfful << CCAP_PLNSL_PLNSHNL_Pos)                /*!< CCAP_T::PLNSL: PLNSHNL Mask                */

#define CCAP_PLNSL_PLNSVML_Pos            (16)                                              /*!< CCAP_T::PLNSL: PLNSVML Position            */
#define CCAP_PLNSL_PLNSVML_Msk            (0xfful << CCAP_PLNSL_PLNSVML_Pos)                /*!< CCAP_T::PLNSL: PLNSVML Mask                */

#define CCAP_PLNSL_PLNSVNL_Pos            (24)                                              /*!< CCAP_T::PLNSL: PLNSVNL Position            */
#define CCAP_PLNSL_PLNSVNL_Msk            (0xfful << CCAP_PLNSL_PLNSVNL_Pos)                /*!< CCAP_T::PLNSL: PLNSVNL Mask                */

#define CCAP_FRCTL_FRM_Pos                (0)                                               /*!< CCAP_T::FRCTL: FRM Position                */
#define CCAP_FRCTL_FRM_Msk                (0x3ful << CCAP_FRCTL_FRM_Pos)                    /*!< CCAP_T::FRCTL: FRM Mask                    */

#define CCAP_FRCTL_FRN_Pos                (8)                                               /*!< CCAP_T::FRCTL: FRN Position                */
#define CCAP_FRCTL_FRN_Msk                (0x3ful << CCAP_FRCTL_FRN_Pos)                    /*!< CCAP_T::FRCTL: FRN Mask                    */

#define CCAP_STRIDE_PKTSTRIDE_Pos         (0)                                               /*!< CCAP_T::STRIDE: PKTSTRIDE Position         */
#define CCAP_STRIDE_PKTSTRIDE_Msk         (0x3ffful << CCAP_STRIDE_PKTSTRIDE_Pos)           /*!< CCAP_T::STRIDE: PKTSTRIDE Mask             */

#define CCAP_STRIDE_PLNSTRIDE_Pos         (16)                                              /*!< CCAP_T::STRIDE: PLNSTRIDE Position         */
#define CCAP_STRIDE_PLNSTRIDE_Msk         (0x3ffful << CCAP_STRIDE_PLNSTRIDE_Pos)           /*!< CCAP_T::STRIDE: PLNSTRIDE Mask             */

#define CCAP_FIFOTH_PKTFTH_Pos            (24)                                              /*!< CCAP_T::FIFOTH: PKTFTH Position            */
#define CCAP_FIFOTH_PKTFTH_Msk            (0x1ful << CCAP_FIFOTH_PKTFTH_Pos)                /*!< CCAP_T::FIFOTH: PKTFTH Mask                */

#define CCAP_FIFOTH_OVF_Pos               (31)                                              /*!< CCAP_T::FIFOTH: OVF Position               */
#define CCAP_FIFOTH_OVF_Msk               (0x1ul << CCAP_FIFOTH_OVF_Pos)                    /*!< CCAP_T::FIFOTH: OVF Mask                   */

#define CCAP_CMPADDR_CMPADDR_Pos          (0)                                               /*!< CCAP_T::CMPADDR: CMPADDR Position          */
#define CCAP_CMPADDR_CMPADDR_Msk          (0xfffffffful << CCAP_CMPADDR_CMPADDR_Pos)        /*!< CCAP_T::CMPADDR: CMPADDR Mask              */

#define CCAP_PKTSM_PKTSHMH_Pos            (0)                                               /*!< CCAP_T::PKTSM: PKTSHMH Position            */
#define CCAP_PKTSM_PKTSHMH_Msk            (0xfful << CCAP_PKTSM_PKTSHMH_Pos)                /*!< CCAP_T::PKTSM: PKTSHMH Mask                */

#define CCAP_PKTSM_PKTSHNH_Pos            (8)                                               /*!< CCAP_T::PKTSM: PKTSHNH Position            */
#define CCAP_PKTSM_PKTSHNH_Msk            (0xfful << CCAP_PKTSM_PKTSHNH_Pos)                /*!< CCAP_T::PKTSM: PKTSHNH Mask                */

#define CCAP_PKTSM_PKTSVMH_Pos            (16)                                              /*!< CCAP_T::PKTSM: PKTSVMH Position            */
#define CCAP_PKTSM_PKTSVMH_Msk            (0xfful << CCAP_PKTSM_PKTSVMH_Pos)                /*!< CCAP_T::PKTSM: PKTSVMH Mask                */

#define CCAP_PKTSM_PKTSVNH_Pos            (24)                                              /*!< CCAP_T::PKTSM: PKTSVNH Position            */
#define CCAP_PKTSM_PKTSVNH_Msk            (0xfful << CCAP_PKTSM_PKTSVNH_Pos)                /*!< CCAP_T::PKTSM: PKTSVNH Mask                */

#define CCAP_PLNSM_PLNSHMH_Pos            (0)                                               /*!< CCAP_T::PLNSM: PLNSHMH Position            */
#define CCAP_PLNSM_PLNSHMH_Msk            (0xfful << CCAP_PLNSM_PLNSHMH_Pos)                /*!< CCAP_T::PLNSM: PLNSHMH Mask                */

#define CCAP_PLNSM_PLNSHNH_Pos            (8)                                               /*!< CCAP_T::PLNSM: PLNSHNH Position            */
#define CCAP_PLNSM_PLNSHNH_Msk            (0xfful << CCAP_PLNSM_PLNSHNH_Pos)                /*!< CCAP_T::PLNSM: PLNSHNH Mask                */

#define CCAP_PLNSM_PLNSVMH_Pos            (16)                                              /*!< CCAP_T::PLNSM: PLNSVMH Position            */
#define CCAP_PLNSM_PLNSVMH_Msk            (0xfful << CCAP_PLNSM_PLNSVMH_Pos)                /*!< CCAP_T::PLNSM: PLNSVMH Mask                */

#define CCAP_PLNSM_PLNSVNH_Pos            (24)                                              /*!< CCAP_T::PLNSM: PLNSVNH Position            */
#define CCAP_PLNSM_PLNSVNH_Msk            (0xfful << CCAP_PLNSM_PLNSVNH_Pos)                /*!< CCAP_T::PLNSM: PLNSVNH Mask                */

#define CCAP_CURADDRP_CURADDR_Pos         (0)                                               /*!< CCAP_T::CURADDRP: CURADDR Position         */
#define CCAP_CURADDRP_CURADDR_Msk         (0xfffffffful << CCAP_CURADDRP_CURADDR_Pos)       /*!< CCAP_T::CURADDRP: CURADDR Mask             */

#define CCAP_PKTBA0_BASEADDR_Pos          (0)                                               /*!< CCAP_T::PKTBA0: BASEADDR Position          */
#define CCAP_PKTBA0_BASEADDR_Msk          (0xfffffffful << CCAP_PKTBA0_BASEADDR_Pos)        /*!< CCAP_T::PKTBA0: BASEADDR Mask              */

/**@}*/ /* CCAP_CONST */
/**@}*/ /* end of CCAP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __CCAP_REG_H__ */
