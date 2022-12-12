/**************************************************************************//**
 * @file     bmc_reg.h
 * @version  V3.00
 * @brief    BMC register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __BMC_REG_H__
#define __BMC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup BMC Controller
    Memory Mapped Structure for BMC Controller
@{ */

typedef struct
{


    /**
     * @var BMC_T::CTL
     * Offset: 0x00  Biphase Mask Coding Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BMCEN     |Biphase Mask Coding Enable
     * |        |          |0 = Biphase Mask Coding function is Disabled. It is cleared after current frame data transfer done.
     * |        |          |1 = Biphase Mask Coding function is Enabled.
     * |[1]     |BWADJ     |Bit Width Adjustment 1.5 Time
     * |        |          |0 = The bit time period of Logic '0' is same as Logic '1'.
     * |        |          |1 = The bit time period of Logic '0' is 1.5 times as Logic '1'.
     * |        |          |Note: When this bit is set, the PDMA
     * |[2]     |PREAM32   |Preamble Bit Number 32
     * |        |          |0 = The bit number of Preamble is 64 bits.
     * |        |          |1 = The bit number of Preamble is 32 bits.
     * |[3]     |DUMLVL    |Dummy Bit Level
     * |        |          |0 = The logic level of dummy bit is LOW.
     * |        |          |1 = The logic level of dummy bit is HIGH.
     * |[4]     |DMAEN     |PDMA Channel Enable
     * |        |          |0 = PDMA function Disabled.
     * |        |          |1 = PDMA function Enabled.
     * |[8]     |G0CHEN    |BMC Group 0 Channel Enable
     * |        |          |0 = BMC Channel 0~3 Disabled.
     * |        |          |1 = BMC Channel 0~3 Enabled.
     * |[9]     |G1CHEN    |BMC Group 1 Channel Enable
     * |        |          |0 = BMC Channel 4~7 Disabled.
     * |        |          |1 = BMC Channel 4~7 Enabled.
     * |[10]    |G2CHEN    |BMC Group 2 Channel Enable
     * |        |          |0 = BMC Channel 8~11 Disabled.
     * |        |          |1 = BMC Channel 8~11 Enabled.
     * |[11]    |G3CHEN    |BMC Group 3 Channel Enable
     * |        |          |0 = BMC Channel 12~15 Disabled.
     * |        |          |1 = BMC Channel 12~15 Enabled.
     * |[12]    |G4CHEN    |BMC Group 4 Channel Enable
     * |        |          |0 = BMC Channel 16~19 Disabled.
     * |        |          |1 = BMC Channel 16~19 Enabled.
     * |[13]    |G5CHEN    |BMC Group 5 Channel Enable
     * |        |          |0 = BMC Channel 20~23 Disabled.
     * |        |          |1 = BMC Channel 20~23 Enabled.
     * |[14]    |G6CHEN    |BMC Group 6 Channel Enable
     * |        |          |0 = BMC Channel 24~27 Disabled.
     * |        |          |1 = BMC Channel 24~27 Enabled.
     * |[15]    |G7CHEN    |BMC Group 7 Channel Enable
     * |        |          |0 = BMC Channel 28~31 Disabled.
     * |        |          |1 = BMC Channel 28~31 Enabled.
     * |[24:16] |BTDIV     |Bit Time Divider
     * |        |          |These bit field indicates the half bit time divider for Biphase Mask Coding bit.
     * |        |          |For example, if the HCLK is 200 MHz, the divider can be set as 0x64
     * |        |          |It will generate 2 MHz reference clock and the Biphase Mask Coding transmitting data is sent according the reference divided clock.
     * @var BMC_T::DNUM0
     * Offset: 0x04  Biphase Mask Coding Dummy Bit Number Channel Group 0~3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DNUMG0    |Dummy Number for Channel 0~3
     * |        |          |These bit field defines the dummy bit number for the group of channel 0~3
     * |        |          |Each dummy bit equal 8 bit data period.
     * |[15:8]  |DNUMG1    |Dummy Number for Channel 4~7
     * |        |          |These bit field defines the dummy bit number for the group of channel 4~7
     * |        |          |Each dummy bit equal 8 bit data period.
     * |[23:16] |DNUMG2    |Dummy Number for Channel 8~11
     * |        |          |These bit field defines the dummy bit number for the group of channel 8~11
     * |        |          |Each dummy bit equal 8 bit data period.
     * |[31:24] |DNUMG3    |Dummy Number for Channel 12~15
     * |        |          |These bit field defines the dummy bit number for the group of channel 12~15
     * |        |          |Each dummy bit equal 8 bit data period.
     * @var BMC_T::DNUM1
     * Offset: 0x08  Biphase Mask Coding Dummy Bit Number Channel Group 4~7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DNUMG4    |Dummy Number for Channel 16~19
     * |        |          |These bit field defines the dummy bit number for the group of channel 16~19
     * |        |          |Each dummy bit equal 8 bit data period.
     * |[15:8]  |DNUMG5    |Dummy Number for Channel 20~23
     * |        |          |These bit field defines the dummy bit number for the group of channel 20~23
     * |        |          |Each dummy bit equal 8 bit data period.
     * |[23:16] |DNUMG6    |Dummy Number for Channel 24~27
     * |        |          |These bit field defines the dummy bit number for the group of channel 24~27
     * |        |          |Each dummy bit equal 8 bit data period.
     * |[31:24] |DNUMG7    |Dummy Number for Channel 28~31
     * |        |          |These bit field defines the dummy bit number for the group of channel 28~31
     * |        |          |Each dummy bit equal 8 bit data period.
     * @var BMC_T::INTEN
     * Offset: 0x0C  Biphase Mask Coding Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FTXDIEN   |Frame Transmit Done Interrupt Enable Bit
     * |        |          |0 = Frame transmit done interrupt Disabled.
     * |        |          |1 = Frame transmit done interrupt Enabled.
     * |[1]     |TXUNDIEN  |Transmit Data Under Run Interrupt Enable Bit
     * |        |          |0 = Transmit data register under run interrupt Disabled.
     * |        |          |1 = Transmit data register under run interrupt Enabled.
     * @var BMC_T::INTSTS
     * Offset: 0x10  Biphase Mask Coding Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FTXDIF    |Frame Transmit Done Interrupt Flag
     * |        |          |0 = No frame transmit done interrupt flag.
     * |        |          |1 = Frame transmit done interrupt flag. Write 1 to clear.
     * |[1]     |TXUNDIF   |Transmit Data Register Under Run Interrupt Flag
     * |        |          |0 = No transmit data register under run interrupt flag.
     * |        |          |1 = Transmit data register under interrupt flag. This bit is the OR function of BMC_INTSTS[15:8].
     * |[8]     |G0TXUND   |Channel 0~3 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 0~3.
     * |        |          |1 = Transmit data under run active in one of channel 0~3. Write 1 to clear.

     * |[9]     |G1TXUND   |Channel 4~7 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 4~7.
     * |        |          |1 = Transmit data under run active in one of channel 4~7. Write 1 to clear.
     * |[10]    |G2TXUND   |Channel 8~11 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 8~11.
     * |        |          |1 = Transmit data under run active in one of channel 8~11. Write 1 to clear.
     * |[10]    |G3TXUND   |Channel 12~15 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 12~15.
     * |        |          |1 = Transmit data under run active in one of channel 12~15. Write 1 to clear.
     * |[12]    |G4TXUND   |Channel 16~19 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 16~19.
     * |        |          |1 = Transmit data under run active in one of channel 16~19. Write 1 to clear.
     * |[13]    |G5TXUND   |Channel 20~23 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 20~23.
     * |        |          |1 = Transmit data under run active in one of channel 20~23. Write 1 to clear.
     * |[14]    |G6TXUND   |Channel 24~27 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 24~27.
     * |        |          |1 = Transmit data under run active in one of channel 24~27. Write 1 to clear.
     * |[15]    |G7TXUND   |Channel 28~31 Transmit Data Under Run
     * |        |          |0 = No Transmit data under run active in one of channel 28~31.
     * |        |          |1 = Transmit data under run active in one of channel 28~31. Write 1 to clear.
     * @var BMC_T::CHEMPTY
     * Offset: 0x14  Biphase Mask Coding Channel Done Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CH0EPT    |BMC Channel 0 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[1]     |CH1EPT    |BMC Channel 1 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[2]     |CH2EPT    |BMC Channel 2 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[3]     |CH3EPT    |BMC Channel 3 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[4]     |CH4EPT    |BMC Channel 4 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[5]     |CH5EPT    |BMC Channel 5 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[6]     |CH6EPT    |BMC Channel 6 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[7]     |CH7EPT    |BMC Channel 7 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[8]     |CH8EPT    |BMC Channel 8 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[9]     |CH9EPT    |BMC Channel 9 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[10]    |CH10EPT   |BMC Channel 10 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[11]    |CH11EPT   |BMC Channel 11 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[12]    |CH12EPT   |BMC Channel 12 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[13]    |CH13EPT   |BMC Channel 13 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[14]    |CH14EPT   |BMC Channel 14 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[15]    |CH15EPT   |BMC Channel 15 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[16]    |CH16EPT   |BMC Channel 16 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[17]    |CH17EPT   |BMC Channel 17 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[18]    |CH18EPT   |BMC Channel 18 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[19]    |CH19EPT   |BMC Channel 19 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[20]    |CH20EPT   |BMC Channel 20 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[21]    |CH21EPT   |BMC Channel 21 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[22]    |CH22EPT   |BMC Channel 22 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[23]    |CH23EPT   |BMC Channel 23 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[24]    |CH24EPT   |BMC Channel 24 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[25]    |CH25EPT   |BMC Channel 25 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[26]    |CH26EPT   |BMC Channel 26 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[27]    |CH27EPT   |BMC Channel 27 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[28]    |CH28EPT   |BMC Channel 28 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[29]    |CH29EPT   |BMC Channel 29 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[30]    |CH30EPT   |BMC Channel 30 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * |[31]    |CH31EPT   |BMC Channel 31 Current FIFO Empty
     * |        |          |0 = The current transmitted FIFO no empty.
     * |        |          |1 = The current transmitted FIFO empty.
     * |        |          |Note: This bit be clear automatically by writing the relative channel data (byte).
     * @var BMC_T::TXDATG0
     * Offset: 0x18  Biphase Mask Coding Transmit Data Group 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH0_TXDAT |Biphase Mask Coding Channel 0 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 0.
     * |[12:8]  |CH1_TXDAT |Biphase Mask Coding Channel 1 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 1.
     * |[20:16] |CH2_TXDAT |Biphase Mask Coding Channel 2 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 2.
     * |[28:24] |CH3_TXDAT |Biphase Mask Coding Channel 3 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 3.
     * @var BMC_T::TXDATG1
     * Offset: 0x1C  Biphase Mask Coding Transmit Data Group 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH4_TXDAT |Biphase Mask Coding Channel 4 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 4.
     * |[12:8]  |CH5_TXDAT |Biphase Mask Coding Channel 5 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 5.
     * |[20:16] |CH6_TXDAT |Biphase Mask Coding Channel 6 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 6.
     * |[28:24] |CH7_TXDAT |Biphase Mask Coding Channel 7 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 7.
     * @var BMC_T::TXDATG2
     * Offset: 0x20  Biphase Mask Coding Transmit Data Group 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH8_TXDAT |Biphase Mask Coding Channel 8 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 8.
     * |[12:8]  |CH9_TXDAT |Biphase Mask Coding Channel 9 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 9.
     * |[20:16] |CH10_TXDAT|Biphase Mask Coding Channel 10 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 10.
     * |[28:24] |CH11_TXDAT|Biphase Mask Coding Channel 11 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 11.
     * @var BMC_T::TXDATG3
     * Offset: 0x24  Biphase Mask Coding Transmit Data Group 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH12_TXDAT|Biphase Mask Coding Channel 12 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 12.
     * |[12:8]  |CH13_TXDAT|Biphase Mask Coding Channel 13 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 13.
     * |[20:16] |CH14_TXDAT|Biphase Mask Coding Channel 14 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 14.
     * |[28:24] |CH15_TXDAT|Biphase Mask Coding Channel 15 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 15.
     * @var BMC_T::TXDATG4
     * Offset: 0x28  Biphase Mask Coding Transmit Data Group 4 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH16_TXDAT|Biphase Mask Coding Channel 16 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 16.
     * |[12:8]  |CH17_TXDAT|Biphase Mask Coding Channel 17 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 17.
     * |[20:16] |CH18_TXDAT|Biphase Mask Coding Channel 18 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 18.
     * |[28:24] |CH19_TXDAT|Biphase Mask Coding Channel 19 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 19.
     * @var BMC_T::TXDATG5
     * Offset: 0x2C  Biphase Mask Coding Transmit Data Group 5 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH20_TXDAT|Biphase Mask Coding Channel 20 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 20.
     * |[12:8]  |CH21_TXDAT|Biphase Mask Coding Channel 21 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 21.
     * |[20:16] |CH22_TXDAT|Biphase Mask Coding Channel 22 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 22.
     * |[28:24] |CH23_TXDAT|Biphase Mask Coding Channel 23 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 23.
     * @var BMC_T::TXDATG6
     * Offset: 0x30  Biphase Mask Coding Transmit Data Group 6 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH24_TXDAT|Biphase Mask Coding Channel 24 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 24.
     * |[12:8]  |CH25_TXDAT|Biphase Mask Coding Channel 25 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 25.
     * |[20:16] |CH26_TXDAT|Biphase Mask Coding Channel 26 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 26.
     * |[28:24] |CH27_TXDAT|Biphase Mask Coding Channel 27 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 27.
     * @var BMC_T::TXDATG7
     * Offset: 0x34  Biphase Mask Coding Transmit Data Group 7 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |CH28_TXDAT|Biphase Mask Coding Channel 28 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 28.
     * |[12:8]  |CH29_TXDAT|Biphase Mask Coding Channel 29 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 29.
     * |[20:16] |CH30_TXDAT|Biphase Mask Coding Channel 30 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 30.
     * |[28:24] |CH31_TXDAT|Biphase Mask Coding Channel 31 Transmit Data
     * |        |          |The bits field indicates the transmit data buffer for channel 31.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] Biphase Mask Coding Control Register                             */
    __IO uint32_t DNUM0;                 /*!< [0x0004] Biphase Mask Coding Dummy Bit Number Channel Group 0~3 Register  */
    __IO uint32_t DNUM1;                 /*!< [0x0008] Biphase Mask Coding Dummy Bit Number Channel Group 4~7 Register  */
    __IO uint32_t INTEN;                 /*!< [0x000c] Biphase Mask Coding Interrupt Enable Register                    */
    __IO uint32_t INTSTS;                /*!< [0x0010] Biphase Mask Coding Interrupt Status Register                    */
    __IO uint32_t CHEMPTY;               /*!< [0x0014] Biphase Mask Coding Channel Done Status Register                 */
    __O  uint32_t TXDATG0;               /*!< [0x0018] Biphase Mask Coding Transmit Data Group 0 Register               */
    __O  uint32_t TXDATG1;               /*!< [0x001c] Biphase Mask Coding Transmit Data Group 1 Register               */
    __O  uint32_t TXDATG2;               /*!< [0x0020] Biphase Mask Coding Transmit Data Group 2 Register               */
    __O  uint32_t TXDATG3;               /*!< [0x0024] Biphase Mask Coding Transmit Data Group 3 Register               */
    __O  uint32_t TXDATG4;               /*!< [0x0028] Biphase Mask Coding Transmit Data Group 4 Register               */
    __O  uint32_t TXDATG5;               /*!< [0x002c] Biphase Mask Coding Transmit Data Group 5 Register               */
    __O  uint32_t TXDATG6;               /*!< [0x0030] Biphase Mask Coding Transmit Data Group 6 Register               */
    __O  uint32_t TXDATG7;               /*!< [0x0034] Biphase Mask Coding Transmit Data Group 7 Register               */

} BMC_T;

/**
    @addtogroup BMC_CONST BMC Bit Field Definition
    Constant Definitions for BMC Controller
@{ */

#define BMC_CTL_BMCEN_Pos                (0)                                               /*!< BMC_T::CTL: BMCEN Position             */
#define BMC_CTL_BMCEN_Msk                (0x1ul << BMC_CTL_BMCEN_Pos)                      /*!< BMC_T::CTL: BMCEN Mask                 */

#define BMC_CTL_BWADJ_Pos                (1)                                               /*!< BMC_T::CTL: BWADJ Position             */
#define BMC_CTL_BWADJ_Msk                (0x1ul << BMC_CTL_BWADJ_Pos)                      /*!< BMC_T::CTL: BWADJ Mask                 */

#define BMC_CTL_PREAM32_Pos              (2)                                               /*!< BMC_T::CTL: PREAM32 Position           */
#define BMC_CTL_PREAM32_Msk              (0x1ul << BMC_CTL_PREAM32_Pos)                    /*!< BMC_T::CTL: PREAM32 Mask               */

#define BMC_CTL_DUMLVL_Pos               (3)                                               /*!< BMC_T::CTL: DUMLVL Position            */
#define BMC_CTL_DUMLVL_Msk               (0x1ul << BMC_CTL_DUMLVL_Pos)                     /*!< BMC_T::CTL: DUMLVL Mask                */

#define BMC_CTL_DMAEN_Pos                (4)                                               /*!< BMC_T::CTL: DMAEN Position             */
#define BMC_CTL_DMAEN_Msk                (0x1ul << BMC_CTL_DMAEN_Pos)                      /*!< BMC_T::CTL: DMAEN Mask                 */

#define BMC_CTL_G0CHEN_Pos               (8)                                               /*!< BMC_T::CTL: G0CHEN Position            */
#define BMC_CTL_G0CHEN_Msk               (0x1ul << BMC_CTL_G0CHEN_Pos)                     /*!< BMC_T::CTL: G0CHEN Mask                */

#define BMC_CTL_G1CHEN_Pos               (9)                                               /*!< BMC_T::CTL: G1CHEN Position            */
#define BMC_CTL_G1CHEN_Msk               (0x1ul << BMC_CTL_G1CHEN_Pos)                     /*!< BMC_T::CTL: G1CHEN Mask                */

#define BMC_CTL_G2CHEN_Pos               (10)                                              /*!< BMC_T::CTL: G2CHEN Position            */
#define BMC_CTL_G2CHEN_Msk               (0x1ul << BMC_CTL_G2CHEN_Pos)                     /*!< BMC_T::CTL: G2CHEN Mask                */

#define BMC_CTL_G3CHEN_Pos               (11)                                              /*!< BMC_T::CTL: G3CHEN Position            */
#define BMC_CTL_G3CHEN_Msk               (0x1ul << BMC_CTL_G3CHEN_Pos)                     /*!< BMC_T::CTL: G3CHEN Mask                */

#define BMC_CTL_G4CHEN_Pos               (12)                                              /*!< BMC_T::CTL: G4CHEN Position            */
#define BMC_CTL_G4CHEN_Msk               (0x1ul << BMC_CTL_G4CHEN_Pos)                     /*!< BMC_T::CTL: G4CHEN Mask                */

#define BMC_CTL_G5CHEN_Pos               (13)                                              /*!< BMC_T::CTL: G5CHEN Position            */
#define BMC_CTL_G5CHEN_Msk               (0x1ul << BMC_CTL_G5CHEN_Pos)                     /*!< BMC_T::CTL: G5CHEN Mask                */

#define BMC_CTL_G6CHEN_Pos               (14)                                              /*!< BMC_T::CTL: G6CHEN Position            */
#define BMC_CTL_G6CHEN_Msk               (0x1ul << BMC_CTL_G6CHEN_Pos)                     /*!< BMC_T::CTL: G6CHEN Mask                */

#define BMC_CTL_G7CHEN_Pos               (15)                                              /*!< BMC_T::CTL: G7CHEN Position            */
#define BMC_CTL_G7CHEN_Msk               (0x1ul << BMC_CTL_G7CHEN_Pos)                     /*!< BMC_T::CTL: G7CHEN Mask                */

#define BMC_CTL_BTDIV_Pos                (16)                                              /*!< BMC_T::CTL: BTDIV Position             */
#define BMC_CTL_BTDIV_Msk                (0x1fful << BMC_CTL_BTDIV_Pos)                    /*!< BMC_T::CTL: BTDIV Mask                 */

#define BMC_DNUM0_DNUMG0_Pos             (0)                                               /*!< BMC_T::DNUM0: DNUMG0 Position          */
#define BMC_DNUM0_DNUMG0_Msk             (0xfful << BMC_DNUM0_DNUMG0_Pos)                  /*!< BMC_T::DNUM0: DNUMG0 Mask              */

#define BMC_DNUM0_DNUMG1_Pos             (8)                                               /*!< BMC_T::DNUM0: DNUMG1 Position          */
#define BMC_DNUM0_DNUMG1_Msk             (0xfful << BMC_DNUM0_DNUMG1_Pos)                  /*!< BMC_T::DNUM0: DNUMG1 Mask              */

#define BMC_DNUM0_DNUMG2_Pos             (16)                                              /*!< BMC_T::DNUM0: DNUMG2 Position          */
#define BMC_DNUM0_DNUMG2_Msk             (0xfful << BMC_DNUM0_DNUMG2_Pos)                  /*!< BMC_T::DNUM0: DNUMG2 Mask              */

#define BMC_DNUM0_DNUMG3_Pos             (24)                                              /*!< BMC_T::DNUM0: DNUMG3 Position          */
#define BMC_DNUM0_DNUMG3_Msk             (0xfful << BMC_DNUM0_DNUMG3_Pos)                  /*!< BMC_T::DNUM0: DNUMG3 Mask              */

#define BMC_DNUM1_DNUMG4_Pos             (0)                                               /*!< BMC_T::DNUM1: DNUMG4 Position          */
#define BMC_DNUM1_DNUMG4_Msk             (0xfful << BMC_DNUM1_DNUMG4_Pos)                  /*!< BMC_T::DNUM1: DNUMG4 Mask              */

#define BMC_DNUM1_DNUMG5_Pos             (8)                                               /*!< BMC_T::DNUM1: DNUMG5 Position          */
#define BMC_DNUM1_DNUMG5_Msk             (0xfful << BMC_DNUM1_DNUMG5_Pos)                  /*!< BMC_T::DNUM1: DNUMG5 Mask              */

#define BMC_DNUM1_DNUMG6_Pos             (16)                                              /*!< BMC_T::DNUM1: DNUMG6 Position          */
#define BMC_DNUM1_DNUMG6_Msk             (0xfful << BMC_DNUM1_DNUMG6_Pos)                  /*!< BMC_T::DNUM1: DNUMG6 Mask              */

#define BMC_DNUM1_DNUMG7_Pos             (24)                                              /*!< BMC_T::DNUM1: DNUMG7 Position          */
#define BMC_DNUM1_DNUMG7_Msk             (0xfful << BMC_DNUM1_DNUMG7_Pos)                  /*!< BMC_T::DNUM1: DNUMG7 Mask              */

#define BMC_INTEN_FTXDIEN_Pos            (0)                                               /*!< BMC_T::INTEN: FTXDIEN Position         */
#define BMC_INTEN_FTXDIEN_Msk            (0x1ul << BMC_INTEN_FTXDIEN_Pos)                  /*!< BMC_T::INTEN: FTXDIEN Mask             */

#define BMC_INTEN_TXUNDIEN_Pos           (1)                                               /*!< BMC_T::INTEN: TXUNDIEN Position        */
#define BMC_INTEN_TXUNDIEN_Msk           (0x1ul << BMC_INTEN_TXUNDIEN_Pos)                 /*!< BMC_T::INTEN: TXUNDIEN Mask            */

#define BMC_INTSTS_FTXDIF_Pos            (0)                                               /*!< BMC_T::INTSTS: FTXDIF Position         */
#define BMC_INTSTS_FTXDIF_Msk            (0x1ul << BMC_INTSTS_FTXDIF_Pos)                  /*!< BMC_T::INTSTS: FTXDIF Mask             */

#define BMC_INTSTS_TXUNDIF_Pos           (1)                                               /*!< BMC_T::INTSTS: TXUNDIF Position        */
#define BMC_INTSTS_TXUNDIF_Msk           (0x1ul << BMC_INTSTS_TXUNDIF_Pos)                 /*!< BMC_T::INTSTS: TXUNDIF Mask            */

#define BMC_INTSTS_G0TXUND_Pos           (8)                                               /*!< BMC_T::INTSTS: G0TXUND Position        */
#define BMC_INTSTS_G0TXUND_Msk           (0x1ul << BMC_INTSTS_G0TXUND_Pos)                 /*!< BMC_T::INTSTS: G0TXUND Mask            */

#define BMC_INTSTS_G1TXUND_Pos           (9)                                               /*!< BMC_T::INTSTS: G1TXUND Position        */
#define BMC_INTSTS_G1TXUND_Msk           (0x1ul << BMC_INTSTS_G1TXUND_Pos)                 /*!< BMC_T::INTSTS: G1TXUND Mask            */

#define BMC_INTSTS_G2TXUND_Pos           (10)                                              /*!< BMC_T::INTSTS: G2TXUND Position        */
#define BMC_INTSTS_G2TXUND_Msk           (0x1ul << BMC_INTSTS_G2TXUND_Pos)                 /*!< BMC_T::INTSTS: G2TXUND Mask            */

#define BMC_INTSTS_G3TXUND_Pos           (11)                                              /*!< BMC_T::INTSTS: G3TXUND Position        */
#define BMC_INTSTS_G3TXUND_Msk           (0x1ul << BMC_INTSTS_G3TXUND_Pos)                 /*!< BMC_T::INTSTS: G3TXUND Mask            */

#define BMC_INTSTS_G4TXUND_Pos           (12)                                              /*!< BMC_T::INTSTS: G4TXUND Position        */
#define BMC_INTSTS_G4TXUND_Msk           (0x1ul << BMC_INTSTS_G4TXUND_Pos)                 /*!< BMC_T::INTSTS: G4TXUND Mask            */

#define BMC_INTSTS_G5TXUND_Pos           (13)                                              /*!< BMC_T::INTSTS: G5TXUND Position        */
#define BMC_INTSTS_G5TXUND_Msk           (0x1ul << BMC_INTSTS_G5TXUND_Pos)                 /*!< BMC_T::INTSTS: G5TXUND Mask            */

#define BMC_INTSTS_G6TXUND_Pos           (14)                                              /*!< BMC_T::INTSTS: G6TXUND Position        */
#define BMC_INTSTS_G6TXUND_Msk           (0x1ul << BMC_INTSTS_G6TXUND_Pos)                 /*!< BMC_T::INTSTS: G6TXUND Mask            */

#define BMC_INTSTS_G7TXUND_Pos           (15)                                              /*!< BMC_T::INTSTS: G7TXUND Position        */
#define BMC_INTSTS_G7TXUND_Msk           (0x1ul << BMC_INTSTS_G7TXUND_Pos)                 /*!< BMC_T::INTSTS: G7TXUND Mask            */

#define BMC_CHEMPTY_CH0EPT_Pos           (0)                                               /*!< BMC_T::CHEMPTY: CH0EPT Position        */
#define BMC_CHEMPTY_CH0EPT_Msk           (0x1ul << BMC_CHEMPTY_CH0EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH0EPT Mask            */

#define BMC_CHEMPTY_CH1EPT_Pos           (1)                                               /*!< BMC_T::CHEMPTY: CH1EPT Position        */
#define BMC_CHEMPTY_CH1EPT_Msk           (0x1ul << BMC_CHEMPTY_CH1EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH1EPT Mask            */

#define BMC_CHEMPTY_CH2EPT_Pos           (2)                                               /*!< BMC_T::CHEMPTY: CH2EPT Position        */
#define BMC_CHEMPTY_CH2EPT_Msk           (0x1ul << BMC_CHEMPTY_CH2EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH2EPT Mask            */

#define BMC_CHEMPTY_CH3EPT_Pos           (3)                                               /*!< BMC_T::CHEMPTY: CH3EPT Position        */
#define BMC_CHEMPTY_CH3EPT_Msk           (0x1ul << BMC_CHEMPTY_CH3EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH3EPT Mask            */

#define BMC_CHEMPTY_CH4EPT_Pos           (4)                                               /*!< BMC_T::CHEMPTY: CH4EPT Position        */
#define BMC_CHEMPTY_CH4EPT_Msk           (0x1ul << BMC_CHEMPTY_CH4EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH4EPT Mask            */

#define BMC_CHEMPTY_CH5EPT_Pos           (5)                                               /*!< BMC_T::CHEMPTY: CH5EPT Position        */
#define BMC_CHEMPTY_CH5EPT_Msk           (0x1ul << BMC_CHEMPTY_CH5EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH5EPT Mask            */

#define BMC_CHEMPTY_CH6EPT_Pos           (6)                                               /*!< BMC_T::CHEMPTY: CH6EPT Position        */
#define BMC_CHEMPTY_CH6EPT_Msk           (0x1ul << BMC_CHEMPTY_CH6EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH6EPT Mask            */

#define BMC_CHEMPTY_CH7EPT_Pos           (7)                                               /*!< BMC_T::CHEMPTY: CH7EPT Position        */
#define BMC_CHEMPTY_CH7EPT_Msk           (0x1ul << BMC_CHEMPTY_CH7EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH7EPT Mask            */

#define BMC_CHEMPTY_CH8EPT_Pos           (8)                                               /*!< BMC_T::CHEMPTY: CH8EPT Position        */
#define BMC_CHEMPTY_CH8EPT_Msk           (0x1ul << BMC_CHEMPTY_CH8EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH8EPT Mask            */

#define BMC_CHEMPTY_CH9EPT_Pos           (9)                                               /*!< BMC_T::CHEMPTY: CH9EPT Position        */
#define BMC_CHEMPTY_CH9EPT_Msk           (0x1ul << BMC_CHEMPTY_CH9EPT_Pos)                 /*!< BMC_T::CHEMPTY: CH9EPT Mask            */

#define BMC_CHEMPTY_CH10EPT_Pos          (10)                                              /*!< BMC_T::CHEMPTY: CH10EPT Position       */
#define BMC_CHEMPTY_CH10EPT_Msk          (0x1ul << BMC_CHEMPTY_CH10EPT_Pos)                /*!< BMC_T::CHEMPTY: CH10EPT Mask           */

#define BMC_CHEMPTY_CH11EPT_Pos          (11)                                              /*!< BMC_T::CHEMPTY: CH11EPT Position       */
#define BMC_CHEMPTY_CH11EPT_Msk          (0x1ul << BMC_CHEMPTY_CH11EPT_Pos)                /*!< BMC_T::CHEMPTY: CH11EPT Mask           */

#define BMC_CHEMPTY_CH12EPT_Pos          (12)                                              /*!< BMC_T::CHEMPTY: CH12EPT Position       */
#define BMC_CHEMPTY_CH12EPT_Msk          (0x1ul << BMC_CHEMPTY_CH12EPT_Pos)                /*!< BMC_T::CHEMPTY: CH12EPT Mask           */

#define BMC_CHEMPTY_CH13EPT_Pos          (13)                                              /*!< BMC_T::CHEMPTY: CH13EPT Position       */
#define BMC_CHEMPTY_CH13EPT_Msk          (0x1ul << BMC_CHEMPTY_CH13EPT_Pos)                /*!< BMC_T::CHEMPTY: CH13EPT Mask           */

#define BMC_CHEMPTY_CH14EPT_Pos          (14)                                              /*!< BMC_T::CHEMPTY: CH14EPT Position       */
#define BMC_CHEMPTY_CH14EPT_Msk          (0x1ul << BMC_CHEMPTY_CH14EPT_Pos)                /*!< BMC_T::CHEMPTY: CH14EPT Mask           */

#define BMC_CHEMPTY_CH15EPT_Pos          (15)                                              /*!< BMC_T::CHEMPTY: CH15EPT Position       */
#define BMC_CHEMPTY_CH15EPT_Msk          (0x1ul << BMC_CHEMPTY_CH15EPT_Pos)                /*!< BMC_T::CHEMPTY: CH15EPT Mask           */

#define BMC_CHEMPTY_CH16EPT_Pos          (16)                                              /*!< BMC_T::CHEMPTY: CH16EPT Position       */
#define BMC_CHEMPTY_CH16EPT_Msk          (0x1ul << BMC_CHEMPTY_CH16EPT_Pos)                /*!< BMC_T::CHEMPTY: CH16EPT Mask           */

#define BMC_CHEMPTY_CH17EPT_Pos          (17)                                              /*!< BMC_T::CHEMPTY: CH17EPT Position       */
#define BMC_CHEMPTY_CH17EPT_Msk          (0x1ul << BMC_CHEMPTY_CH17EPT_Pos)                /*!< BMC_T::CHEMPTY: CH17EPT Mask           */

#define BMC_CHEMPTY_CH18EPT_Pos          (18)                                              /*!< BMC_T::CHEMPTY: CH18EPT Position       */
#define BMC_CHEMPTY_CH18EPT_Msk          (0x1ul << BMC_CHEMPTY_CH18EPT_Pos)                /*!< BMC_T::CHEMPTY: CH18EPT Mask           */

#define BMC_CHEMPTY_CH19EPT_Pos          (19)                                              /*!< BMC_T::CHEMPTY: CH19EPT Position       */
#define BMC_CHEMPTY_CH19EPT_Msk          (0x1ul << BMC_CHEMPTY_CH19EPT_Pos)                /*!< BMC_T::CHEMPTY: CH19EPT Mask           */

#define BMC_CHEMPTY_CH20EPT_Pos          (20)                                              /*!< BMC_T::CHEMPTY: CH20EPT Position       */
#define BMC_CHEMPTY_CH20EPT_Msk          (0x1ul << BMC_CHEMPTY_CH20EPT_Pos)                /*!< BMC_T::CHEMPTY: CH20EPT Mask           */

#define BMC_CHEMPTY_CH21EPT_Pos          (21)                                              /*!< BMC_T::CHEMPTY: CH21EPT Position       */
#define BMC_CHEMPTY_CH21EPT_Msk          (0x1ul << BMC_CHEMPTY_CH21EPT_Pos)                /*!< BMC_T::CHEMPTY: CH21EPT Mask           */

#define BMC_CHEMPTY_CH22EPT_Pos          (22)                                              /*!< BMC_T::CHEMPTY: CH22EPT Position       */
#define BMC_CHEMPTY_CH22EPT_Msk          (0x1ul << BMC_CHEMPTY_CH22EPT_Pos)                /*!< BMC_T::CHEMPTY: CH22EPT Mask           */

#define BMC_CHEMPTY_CH23EPT_Pos          (23)                                              /*!< BMC_T::CHEMPTY: CH23EPT Position       */
#define BMC_CHEMPTY_CH23EPT_Msk          (0x1ul << BMC_CHEMPTY_CH23EPT_Pos)                /*!< BMC_T::CHEMPTY: CH23EPT Mask           */

#define BMC_CHEMPTY_CH24EPT_Pos          (24)                                              /*!< BMC_T::CHEMPTY: CH24EPT Position       */
#define BMC_CHEMPTY_CH24EPT_Msk          (0x1ul << BMC_CHEMPTY_CH24EPT_Pos)                /*!< BMC_T::CHEMPTY: CH24EPT Mask           */

#define BMC_CHEMPTY_CH25EPT_Pos          (25)                                              /*!< BMC_T::CHEMPTY: CH25EPT Position       */
#define BMC_CHEMPTY_CH25EPT_Msk          (0x1ul << BMC_CHEMPTY_CH25EPT_Pos)                /*!< BMC_T::CHEMPTY: CH25EPT Mask           */

#define BMC_CHEMPTY_CH26EPT_Pos          (26)                                              /*!< BMC_T::CHEMPTY: CH26EPT Position       */
#define BMC_CHEMPTY_CH26EPT_Msk          (0x1ul << BMC_CHEMPTY_CH26EPT_Pos)                /*!< BMC_T::CHEMPTY: CH26EPT Mask           */

#define BMC_CHEMPTY_CH27EPT_Pos          (27)                                              /*!< BMC_T::CHEMPTY: CH27EPT Position       */
#define BMC_CHEMPTY_CH27EPT_Msk          (0x1ul << BMC_CHEMPTY_CH27EPT_Pos)                /*!< BMC_T::CHEMPTY: CH27EPT Mask           */

#define BMC_CHEMPTY_CH28EPT_Pos          (28)                                              /*!< BMC_T::CHEMPTY: CH28EPT Position       */
#define BMC_CHEMPTY_CH28EPT_Msk          (0x1ul << BMC_CHEMPTY_CH28EPT_Pos)                /*!< BMC_T::CHEMPTY: CH28EPT Mask           */

#define BMC_CHEMPTY_CH29EPT_Pos          (29)                                              /*!< BMC_T::CHEMPTY: CH29EPT Position       */
#define BMC_CHEMPTY_CH29EPT_Msk          (0x1ul << BMC_CHEMPTY_CH29EPT_Pos)                /*!< BMC_T::CHEMPTY: CH29EPT Mask           */

#define BMC_CHEMPTY_CH30EPT_Pos          (30)                                              /*!< BMC_T::CHEMPTY: CH30EPT Position       */
#define BMC_CHEMPTY_CH30EPT_Msk          (0x1ul << BMC_CHEMPTY_CH30EPT_Pos)                /*!< BMC_T::CHEMPTY: CH30EPT Mask           */

#define BMC_CHEMPTY_CH31EPT_Pos          (31)                                              /*!< BMC_T::CHEMPTY: CH31EPT Position       */
#define BMC_CHEMPTY_CH31EPT_Msk          (0x1ul << BMC_CHEMPTY_CH31EPT_Pos)                /*!< BMC_T::CHEMPTY: CH31EPT Mask           */

#define BMC_TXDATG0_CH0_TXDAT_Pos        (0)                                               /*!< BMC_T::TXDATG0: CH0_TXDAT Position     */
#define BMC_TXDATG0_CH0_TXDAT_Msk        (0x1ful << BMC_TXDATG0_CH0_TXDAT_Pos)             /*!< BMC_T::TXDATG0: CH0_TXDAT Mask         */

#define BMC_TXDATG0_CH1_TXDAT_Pos        (8)                                               /*!< BMC_T::TXDATG0: CH1_TXDAT Position     */
#define BMC_TXDATG0_CH1_TXDAT_Msk        (0x1ful << BMC_TXDATG0_CH1_TXDAT_Pos)             /*!< BMC_T::TXDATG0: CH1_TXDAT Mask         */

#define BMC_TXDATG0_CH2_TXDAT_Pos        (16)                                              /*!< BMC_T::TXDATG0: CH2_TXDAT Position     */
#define BMC_TXDATG0_CH2_TXDAT_Msk        (0x1ful << BMC_TXDATG0_CH2_TXDAT_Pos)             /*!< BMC_T::TXDATG0: CH2_TXDAT Mask         */

#define BMC_TXDATG0_CH3_TXDAT_Pos        (24)                                              /*!< BMC_T::TXDATG0: CH3_TXDAT Position     */
#define BMC_TXDATG0_CH3_TXDAT_Msk        (0x1ful << BMC_TXDATG0_CH3_TXDAT_Pos)             /*!< BMC_T::TXDATG0: CH3_TXDAT Mask         */

#define BMC_TXDATG1_CH4_TXDAT_Pos        (0)                                               /*!< BMC_T::TXDATG1: CH4_TXDAT Position     */
#define BMC_TXDATG1_CH4_TXDAT_Msk        (0x1ful << BMC_TXDATG1_CH4_TXDAT_Pos)             /*!< BMC_T::TXDATG1: CH4_TXDAT Mask         */

#define BMC_TXDATG1_CH5_TXDAT_Pos        (8)                                               /*!< BMC_T::TXDATG1: CH5_TXDAT Position     */
#define BMC_TXDATG1_CH5_TXDAT_Msk        (0x1ful << BMC_TXDATG1_CH5_TXDAT_Pos)             /*!< BMC_T::TXDATG1: CH5_TXDAT Mask         */

#define BMC_TXDATG1_CH6_TXDAT_Pos        (16)                                              /*!< BMC_T::TXDATG1: CH6_TXDAT Position     */
#define BMC_TXDATG1_CH6_TXDAT_Msk        (0x1ful << BMC_TXDATG1_CH6_TXDAT_Pos)             /*!< BMC_T::TXDATG1: CH6_TXDAT Mask         */

#define BMC_TXDATG1_CH7_TXDAT_Pos        (24)                                              /*!< BMC_T::TXDATG1: CH7_TXDAT Position     */
#define BMC_TXDATG1_CH7_TXDAT_Msk        (0x1ful << BMC_TXDATG1_CH7_TXDAT_Pos)             /*!< BMC_T::TXDATG1: CH7_TXDAT Mask         */

#define BMC_TXDATG2_CH8_TXDAT_Pos        (0)                                               /*!< BMC_T::TXDATG2: CH8_TXDAT Position     */
#define BMC_TXDATG2_CH8_TXDAT_Msk        (0x1ful << BMC_TXDATG2_CH8_TXDAT_Pos)             /*!< BMC_T::TXDATG2: CH8_TXDAT Mask         */

#define BMC_TXDATG2_CH9_TXDAT_Pos        (8)                                               /*!< BMC_T::TXDATG2: CH9_TXDAT Position     */
#define BMC_TXDATG2_CH9_TXDAT_Msk        (0x1ful << BMC_TXDATG2_CH9_TXDAT_Pos)             /*!< BMC_T::TXDATG2: CH9_TXDAT Mask         */

#define BMC_TXDATG2_CH10_TXDAT_Pos       (16)                                              /*!< BMC_T::TXDATG2: CH10_TXDAT Position    */
#define BMC_TXDATG2_CH10_TXDAT_Msk       (0x1ful << BMC_TXDATG2_CH10_TXDAT_Pos)            /*!< BMC_T::TXDATG2: CH10_TXDAT Mask        */

#define BMC_TXDATG2_CH11_TXDAT_Pos       (24)                                              /*!< BMC_T::TXDATG2: CH11_TXDAT Position    */
#define BMC_TXDATG2_CH11_TXDAT_Msk       (0x1ful << BMC_TXDATG2_CH11_TXDAT_Pos)            /*!< BMC_T::TXDATG2: CH11_TXDAT Mask        */

#define BMC_TXDATG3_CH12_TXDAT_Pos       (0)                                               /*!< BMC_T::TXDATG3: CH12_TXDAT Position    */
#define BMC_TXDATG3_CH12_TXDAT_Msk       (0x1ful << BMC_TXDATG3_CH12_TXDAT_Pos)            /*!< BMC_T::TXDATG3: CH12_TXDAT Mask        */

#define BMC_TXDATG3_CH13_TXDAT_Pos       (8)                                               /*!< BMC_T::TXDATG3: CH13_TXDAT Position    */
#define BMC_TXDATG3_CH13_TXDAT_Msk       (0x1ful << BMC_TXDATG3_CH13_TXDAT_Pos)            /*!< BMC_T::TXDATG3: CH13_TXDAT Mask        */

#define BMC_TXDATG3_CH14_TXDAT_Pos       (16)                                              /*!< BMC_T::TXDATG3: CH14_TXDAT Position    */
#define BMC_TXDATG3_CH14_TXDAT_Msk       (0x1ful << BMC_TXDATG3_CH14_TXDAT_Pos)            /*!< BMC_T::TXDATG3: CH14_TXDAT Mask        */

#define BMC_TXDATG3_CH15_TXDAT_Pos       (24)                                              /*!< BMC_T::TXDATG3: CH15_TXDAT Position    */
#define BMC_TXDATG3_CH15_TXDAT_Msk       (0x1ful << BMC_TXDATG3_CH15_TXDAT_Pos)            /*!< BMC_T::TXDATG3: CH15_TXDAT Mask        */

#define BMC_TXDATG4_CH16_TXDAT_Pos       (0)                                               /*!< BMC_T::TXDATG4: CH16_TXDAT Position    */
#define BMC_TXDATG4_CH16_TXDAT_Msk       (0x1ful << BMC_TXDATG4_CH16_TXDAT_Pos)            /*!< BMC_T::TXDATG4: CH16_TXDAT Mask        */

#define BMC_TXDATG4_CH17_TXDAT_Pos       (8)                                               /*!< BMC_T::TXDATG4: CH17_TXDAT Position    */
#define BMC_TXDATG4_CH17_TXDAT_Msk       (0x1ful << BMC_TXDATG4_CH17_TXDAT_Pos)            /*!< BMC_T::TXDATG4: CH17_TXDAT Mask        */

#define BMC_TXDATG4_CH18_TXDAT_Pos       (16)                                              /*!< BMC_T::TXDATG4: CH18_TXDAT Position    */
#define BMC_TXDATG4_CH18_TXDAT_Msk       (0x1ful << BMC_TXDATG4_CH18_TXDAT_Pos)            /*!< BMC_T::TXDATG4: CH18_TXDAT Mask        */

#define BMC_TXDATG4_CH19_TXDAT_Pos       (24)                                              /*!< BMC_T::TXDATG4: CH19_TXDAT Position    */
#define BMC_TXDATG4_CH19_TXDAT_Msk       (0x1ful << BMC_TXDATG4_CH19_TXDAT_Pos)            /*!< BMC_T::TXDATG4: CH19_TXDAT Mask        */

#define BMC_TXDATG5_CH20_TXDAT_Pos       (0)                                               /*!< BMC_T::TXDATG5: CH20_TXDAT Position    */
#define BMC_TXDATG5_CH20_TXDAT_Msk       (0x1ful << BMC_TXDATG5_CH20_TXDAT_Pos)            /*!< BMC_T::TXDATG5: CH20_TXDAT Mask        */

#define BMC_TXDATG5_CH21_TXDAT_Pos       (8)                                               /*!< BMC_T::TXDATG5: CH21_TXDAT Position    */
#define BMC_TXDATG5_CH21_TXDAT_Msk       (0x1ful << BMC_TXDATG5_CH21_TXDAT_Pos)            /*!< BMC_T::TXDATG5: CH21_TXDAT Mask        */

#define BMC_TXDATG5_CH22_TXDAT_Pos       (16)                                              /*!< BMC_T::TXDATG5: CH22_TXDAT Position    */
#define BMC_TXDATG5_CH22_TXDAT_Msk       (0x1ful << BMC_TXDATG5_CH22_TXDAT_Pos)            /*!< BMC_T::TXDATG5: CH22_TXDAT Mask        */

#define BMC_TXDATG5_CH23_TXDAT_Pos       (24)                                              /*!< BMC_T::TXDATG5: CH23_TXDAT Position    */
#define BMC_TXDATG5_CH23_TXDAT_Msk       (0x1ful << BMC_TXDATG5_CH23_TXDAT_Pos)            /*!< BMC_T::TXDATG5: CH23_TXDAT Mask        */

#define BMC_TXDATG6_CH24_TXDAT_Pos       (0)                                               /*!< BMC_T::TXDATG6: CH24_TXDAT Position    */
#define BMC_TXDATG6_CH24_TXDAT_Msk       (0x1ful << BMC_TXDATG6_CH24_TXDAT_Pos)            /*!< BMC_T::TXDATG6: CH24_TXDAT Mask        */

#define BMC_TXDATG6_CH25_TXDAT_Pos       (8)                                               /*!< BMC_T::TXDATG6: CH25_TXDAT Position    */
#define BMC_TXDATG6_CH25_TXDAT_Msk       (0x1ful << BMC_TXDATG6_CH25_TXDAT_Pos)            /*!< BMC_T::TXDATG6: CH25_TXDAT Mask        */

#define BMC_TXDATG6_CH26_TXDAT_Pos       (16)                                              /*!< BMC_T::TXDATG6: CH26_TXDAT Position    */
#define BMC_TXDATG6_CH26_TXDAT_Msk       (0x1ful << BMC_TXDATG6_CH26_TXDAT_Pos)            /*!< BMC_T::TXDATG6: CH26_TXDAT Mask        */

#define BMC_TXDATG6_CH27_TXDAT_Pos       (24)                                              /*!< BMC_T::TXDATG6: CH27_TXDAT Position    */
#define BMC_TXDATG6_CH27_TXDAT_Msk       (0x1ful << BMC_TXDATG6_CH27_TXDAT_Pos)            /*!< BMC_T::TXDATG6: CH27_TXDAT Mask        */

#define BMC_TXDATG7_CH28_TXDAT_Pos       (0)                                               /*!< BMC_T::TXDATG7: CH28_TXDAT Position    */
#define BMC_TXDATG7_CH28_TXDAT_Msk       (0x1ful << BMC_TXDATG7_CH28_TXDAT_Pos)            /*!< BMC_T::TXDATG7: CH28_TXDAT Mask        */

#define BMC_TXDATG7_CH29_TXDAT_Pos       (8)                                               /*!< BMC_T::TXDATG7: CH29_TXDAT Position    */
#define BMC_TXDATG7_CH29_TXDAT_Msk       (0x1ful << BMC_TXDATG7_CH29_TXDAT_Pos)            /*!< BMC_T::TXDATG7: CH29_TXDAT Mask        */

#define BMC_TXDATG7_CH30_TXDAT_Pos       (16)                                              /*!< BMC_T::TXDATG7: CH30_TXDAT Position    */
#define BMC_TXDATG7_CH30_TXDAT_Msk       (0x1ful << BMC_TXDATG7_CH30_TXDAT_Pos)            /*!< BMC_T::TXDATG7: CH30_TXDAT Mask        */

#define BMC_TXDATG7_CH31_TXDAT_Pos       (24)                                              /*!< BMC_T::TXDATG7: CH31_TXDAT Position    */
#define BMC_TXDATG7_CH31_TXDAT_Msk       (0x1ful << BMC_TXDATG7_CH31_TXDAT_Pos)            /*!< BMC_T::TXDATG7: CH31_TXDAT Mask        */


/**@}*/ /* BMC_CONST */
/**@}*/ /* end of BMC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __BMC_REG_H__ */

