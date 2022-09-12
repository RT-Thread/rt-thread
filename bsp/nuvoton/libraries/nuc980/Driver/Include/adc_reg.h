/**************************************************************************//**
 * @file     adc.h
 * @brief    ADC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020~2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef __ADC_REG_H__
#define __ADC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup ADC Analog to Digital Converter(ADC)
    Memory Mapped Structure for ADC Controller
@{ */

typedef struct
{


    /**
     * @var ADC_T::CTL
     * Offset: 0x00  ADC Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADEN      |ADC Power Control
     * |        |          |0 = Power down ADC.
     * |        |          |1 = Power on ADC.
     * |[8]     |MST       |Menu Start Conversion
     * |        |          |0 = Functional menu not started.
     * |        |          |1 = Start all enable bit in ADC_CONF register.
     * |        |          |Note: This bit is set by software and cleared by hardware when all the tasks listed in ADC_CONF are done.
     * |[9]     |PEDEEN    |Pen Down Event Enable Bit
     * |        |          |0 = Pen down event interrupt Disabled.
     * |        |          |1 = Pen down event interrupt Enabled.
     * |[11]    |WKTEN     |Touch Wake Up Enable Bit
     * |        |          |0 = Touch wake-up Disabled.
     * |        |          |1 = Touch wake-up Enabled.
     * |[16]    |WMSWCH    |Wire Mode Switch for 5-wire/4-wire Configuration
     * |        |          |0 = 4-wire mode.
     * |        |          |1 = 5-wire mode.
     * @var ADC_T::CONF
     * Offset: 0x04  ADC Configure
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TEN       |Touch Detection Enable Bit
     * |        |          |0 = Touch detection function Disabled.
     * |        |          |1 = Touch detection function Enabled.
     * |[1]     |ZEN       |Press Measure Enable Bit
     * |        |          |1 = Press measure function Disabled.
     * |        |          |1 = Press measure function Enabled.
     * |[2]     |NACEN     |Normal A/D Conversion Enable Bit
     * |        |          |ADC normal conversion function enable
     * |        |          |0 = Normal A/D Conversion Disabled.
     * |        |          |1 = Normal A/D Conversion Enabled.
     * |[7:6]   |REFSEL    |ADC Reference Select
     * |        |          |ADC reference voltage select when ADC operate in normal conversion.
     * |        |          |00 = AGND33 vs VREF input.
     * |        |          |01 = YM vs YP.
     * |        |          |10 = XM vs XP.
     * |        |          |11 = AGND33 vs AVDD33.
     * |[14:12] |CHSEL     |Channel Selection
     * |        |          |ADC input channel selection.
     * |        |          |000 = VREF.
     * |        |          |001 = A1.
     * |        |          |010 = A2.
     * |        |          |011 = VSENSE.
     * |        |          |100 = YM.
     * |        |          |101 = YP.
     * |        |          |110 = XM.
     * |        |          |111 = XP.
     * |[20]    |TMAVDIS   |Display T Mean Average Disable Bit
     * |        |          |Touch mean average for X and Y function disable bit.
     * |        |          |0 = Touch mean average for X and Y function Enabled.
     * |        |          |1 = Touch mean average for X and Y function Disabled.
     * |[21]    |ZMAVDIS   |Display Z Mean Average Disable Bit
     * |        |          |Pressure mean average for Z1 and Z2 function disable bit.
     * |        |          |0 = Pressure mean average for Z1 and Z2 function Enabled.
     * |        |          |1 = Pressure mean average for Z1 and Z2 function Disabled.
     * |[22]    |SPEED     |Speed Mode Selection
     * |        |          |0 = All ADC channels set to high speed mode.
     * |        |          |1 = All ADC channels set to low speed mode.
     * @var ADC_T::IER
     * Offset: 0x08  ADC Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MIEN      |Menu Interrupt Enable Bit
     * |        |          |Function menu complete interrupt enable.
     * |        |          |0 = Menu interrupt Disabled.
     * |        |          |1 = Menu interrupt Enabled.
     * |[2]     |PEDEIEN   |Pen Down Event Interrupt Enable Bit
     * |        |          |0 = Pen down event detection interrupt Disabled.
     * |        |          |1 = Pen down event detection interrupt Enabled.
     * |[3]     |WKTIEN    |Wake Up Touch Interrupt Enable Bit
     * |        |          |0 = Wake up touch detection interrupt Disabled.
     * |        |          |1 = Wake up touch detection interrupt Enabled.
     * |[6]     |PEUEIEN   |Pen Up Event Interrupt Enable Bit
     * |        |          |0 = Pen up event detection interrupt Disabled.
     * |        |          |1 = Pen up event detection interrupt Enabled.
     * @var ADC_T::ISR
     * Offset: 0x0C  ADC Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MF        |Menu Complete Flag
     * |        |          |Function menu complete status indicator.
     * |        |          |Note: Set by hardware and write 1 to clear this bit.
     * |[2]     |PEDEF     |Pen Down Event Flag
     * |        |          |Pen down event status indicator.
     * |        |          |Note: Set by hardware and write 1 to clear this bit.
     * |[4]     |PEUEF     |Pen Up Event Flag
     * |        |          |Pen up event status indicator.
     * |        |          |Note: Set by hardware and write 1 to clear this bit.
     * |[8]     |TF        |Touch Conversion Finish
     * |        |          |Functional menu touch detection conversion finish.
     * |        |          |Note: Set by hardware and write 1 to clear this bit.
     * |[9]     |ZF        |Press Conversion Finish
     * |        |          |Functional menu press measure conversion finish.
     * |        |          |Note: Set by hardware and write 1 to clear this bit.
     * |[10]    |NACF      |Normal AD Conversion Finish
     * |        |          |Functional menu normal AD conversion finish.
     * |        |          |Note: Set by hardware and write 1 to clear this bit.
     * |[17]    |INTTC     |Interrupt Signal for Touch Screen Touching Detection
     * |        |          |This signal is directly from analog macro without de-bouncing and can be used to determine the pen down touch event together with PEDEF (ADC_ISR[2]) flag.
     * @var ADC_T::WKISR
     * Offset: 0x10  ADC Wake-up interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |WPEDEF    |Wake Up Pen Down Event Flag
     * |        |          |Pen down event wake up status indicator.
     * @var ADC_T::XYDATA
     * Offset: 0x20  ADC Touch X,Y Position Data
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |XDATA     |ADC X Data
     * |        |          |When TEN (ADC_CONF[0]) is set, the touch x-position will be stored in this register.
     * |        |          |Note: If the TMAVDIS (ADC_CONF[20]) = 0, both x and y position are the results of the mean average of x and y in ADC_XYSORT0 ~ ADC_XYSORT3.
     * |[27:16] |YDATA     |ADC Y Data
     * |        |          |When TEN (ADC_CONF[0]) is set, the touch y-position will be stored in this register.
     * |        |          |Note: If the TMAVDIS (ADC_CONF[20]) = 0, both x and y position are the results of the mean average of x and y in ADC_XYSORT0 ~ ADC_XYSORT3.
     * @var ADC_T::ZDATA
     * Offset: 0x24  ADC Touch Z Pressure Data
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |Z1DATA    |ADC Z1 Data
     * |        |          |When ZEN (ADC_CONF[1]) is set; the touch pressure measure Z1 will be stored in this register.
     * |        |          |Note: If the ZMAVDIS (ADC_CONF[21]) = 0, both Z1 and Z2 data is the results of the mean average of Z1 and Z2 in ADC_ZSORT0 ~ ADC_ZSORT3.
     * |[27:16] |Z2DATA    |ADC Z2 Data
     * |        |          |When ZEN (ADC_CONF[1]) is set; the touch pressure measure Z2 will be stored in this register.
     * |        |          |Note: If the ZMAVDIS (ADC_CONF[21]) = 0, both Z1 and Z2 data is the results of the mean average of Z1 and Z2 in ADC_ZSORT0 ~ ADC_ZSORT3.
     * @var ADC_T::DATA
     * Offset: 0x28  ADC Normal Conversion Data
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |ADCDATA   |ADC Data
     * |        |          |When NACEN (ADC_CONF[2]) is enabled, the AD converting result with corresponding channel is stored in this register.
     * @var ADC_T::XYSORT0
     * Offset: 0x1F4  ADC Touch XY Position Mean Value Sort 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |XSORT0    |X Position Sort Data 0
     * |        |          |X position mean average sort data 0.
     * |[27:16] |YSORT0    |Y Position Sort Data 0
     * |        |          |Y position mean average sort data 0.
     * @var ADC_T::XYSORT1
     * Offset: 0x1F8  ADC Touch XY Position Mean Value Sort 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |XSORT1    |X Position Sort Data 1
     * |        |          |X position mean average sort data 1.
     * |[27:16] |YSORT1    |Y Position Sort Data 1
     * |        |          |Y position mean average sort data 1.
     * @var ADC_T::XYSORT2
     * Offset: 0x1FC  ADC Touch XY Position Mean Value Sort 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |XSORT2    |X Position Sort Data 2
     * |        |          |X position mean average sort data 2.
     * |[27:16] |YSORT2    |Y Position Sort Data 2
     * |        |          |Y position mean average sort data 2.
     * @var ADC_T::XYSORT3
     * Offset: 0x200  ADC Touch XY Position Mean Value Sort 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |XSORT3    |X Position Sort Data 3
     * |        |          |X position mean average sort data 3.
     * |[27:16] |YSORT3    |Y Position Sort Data 3
     * |        |          |Y position mean average sort data 3.
     * @var ADC_T::ZSORT0
     * Offset: 0x204  ADC Touch Z Pressure Mean Value Sort 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |Z1SORT0   |Z1 Position Sort Data 0
     * |        |          |Z1 position Mean average sort data 0.
     * |[27:16] |Z2SORT0   |Z2 Position Sort Data 0
     * |        |          |Z2 position Mean average sort data 0.
     * @var ADC_T::ZSORT1
     * Offset: 0x208  ADC Touch Z Pressure Mean Value Sort 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |Z1SORT1   |Z1 Position Sort Data 1
     * |        |          |Z1 position Mean average sort data 1.
     * |[27:16] |Z2SORT1   |Z2 Position Sort Data 1
     * |        |          |Z2 position Mean average sort data 1.
     * @var ADC_T::ZSORT2
     * Offset: 0x20C  ADC Touch Z Pressure Mean Value Sort 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |Z1SORT2   |Z1 Position Sort Data 2
     * |        |          |Z1 position Mean average sort data 2.
     * |[27:16] |Z2SORT2   |Z2 Position Sort Data 2
     * |        |          |Z2 position Mean average sort data 2.
     * @var ADC_T::ZSORT3
     * Offset: 0x210  ADC Touch Z Pressure Mean Value Sort 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |Z1SORT3   |Z1 Position Sort Data 3
     * |        |          |Z1 position Mean average sort data 3.
     * |[27:16] |Z2SORT3   |Z2 Position Sort Data 3
     * |        |          |Z2 position Mean average sort data 3.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] ADC Control                                                      */
    __IO uint32_t CONF;                  /*!< [0x0004] ADC Configure                                                    */
    __IO uint32_t IER;                   /*!< [0x0008] ADC Interrupt Enable Register                                    */
    __IO uint32_t ISR;                   /*!< [0x000c] ADC Interrupt Status Register                                    */
    __I  uint32_t WKISR;                 /*!< [0x0010] ADC Wake-up interrupt Status Register                            */
    __I  uint32_t RESERVE0[3];
    __I  uint32_t XYDATA;                /*!< [0x0020] ADC Touch X,Y Position Data                                      */
    __I  uint32_t ZDATA;                 /*!< [0x0024] ADC Touch Z Pressure Data                                        */
    __I  uint32_t DATA;                  /*!< [0x0028] ADC Normal Conversion Data                                       */
    __I  uint32_t RESERVE1[114];
    __I  uint32_t XYSORT[4];             /*!< [0x01f4~0x0200] ADC Touch XY Position Mean Value Sort Register            */
    __I  uint32_t ZSORT0[4];             /*!< [0x0204~0x0210] ADC Touch Z Pressure Mean Value Sort Register             */

} ADC_T;

/**
    @addtogroup ADC_CONST ADC Bit Field Definition
    Constant Definitions for ADC Controller
@{ */

#define ADC_CTL_ADEN_Pos                 (0)                                               /*!< ADC_T::CTL: ADEN Position              */
#define ADC_CTL_ADEN_Msk                 (0x1ul << ADC_CTL_ADEN_Pos)                       /*!< ADC_T::CTL: ADEN Mask                  */

#define ADC_CTL_MST_Pos                  (8)                                               /*!< ADC_T::CTL: MST Position               */
#define ADC_CTL_MST_Msk                  (0x1ul << ADC_CTL_MST_Pos)                        /*!< ADC_T::CTL: MST Mask                   */

#define ADC_CTL_PEDEEN_Pos               (9)                                               /*!< ADC_T::CTL: PEDEEN Position            */
#define ADC_CTL_PEDEEN_Msk               (0x1ul << ADC_CTL_PEDEEN_Pos)                     /*!< ADC_T::CTL: PEDEEN Mask                */

#define ADC_CTL_WKTEN_Pos                (11)                                              /*!< ADC_T::CTL: WKTEN Position             */
#define ADC_CTL_WKTEN_Msk                (0x1ul << ADC_CTL_WKTEN_Pos)                      /*!< ADC_T::CTL: WKTEN Mask                 */

#define ADC_CTL_WMSWCH_Pos               (16)                                              /*!< ADC_T::CTL: WMSWCH Position            */
#define ADC_CTL_WMSWCH_Msk               (0x1ul << ADC_CTL_WMSWCH_Pos)                     /*!< ADC_T::CTL: WMSWCH Mask                */

#define ADC_CONF_TEN_Pos                 (0)                                               /*!< ADC_T::CONF: TEN Position              */
#define ADC_CONF_TEN_Msk                 (0x1ul << ADC_CONF_TEN_Pos)                       /*!< ADC_T::CONF: TEN Mask                  */

#define ADC_CONF_ZEN_Pos                 (1)                                               /*!< ADC_T::CONF: ZEN Position              */
#define ADC_CONF_ZEN_Msk                 (0x1ul << ADC_CONF_ZEN_Pos)                       /*!< ADC_T::CONF: ZEN Mask                  */

#define ADC_CONF_NACEN_Pos               (2)                                               /*!< ADC_T::CONF: NACEN Position            */
#define ADC_CONF_NACEN_Msk               (0x1ul << ADC_CONF_NACEN_Pos)                     /*!< ADC_T::CONF: NACEN Mask                */

#define ADC_CONF_REFSEL_Pos              (6)                                               /*!< ADC_T::CONF: REFSEL Position           */
#define ADC_CONF_REFSEL_Msk              (0x3ul << ADC_CONF_REFSEL_Pos)                    /*!< ADC_T::CONF: REFSEL Mask               */

#define ADC_CONF_CHSEL_Pos               (12)                                              /*!< ADC_T::CONF: CHSEL Position            */
#define ADC_CONF_CHSEL_Msk               (0x7ul << ADC_CONF_CHSEL_Pos)                     /*!< ADC_T::CONF: CHSEL Mask                */

#define ADC_CONF_TMAVDIS_Pos             (20)                                              /*!< ADC_T::CONF: TMAVDIS Position          */
#define ADC_CONF_TMAVDIS_Msk             (0x1ul << ADC_CONF_TMAVDIS_Pos)                   /*!< ADC_T::CONF: TMAVDIS Mask              */

#define ADC_CONF_ZMAVDIS_Pos             (21)                                              /*!< ADC_T::CONF: ZMAVDIS Position          */
#define ADC_CONF_ZMAVDIS_Msk             (0x1ul << ADC_CONF_ZMAVDIS_Pos)                   /*!< ADC_T::CONF: ZMAVDIS Mask              */

#define ADC_CONF_SPEED_Pos               (22)                                              /*!< ADC_T::CONF: SPEED Position            */
#define ADC_CONF_SPEED_Msk               (0x1ul << ADC_CONF_SPEED_Pos)                     /*!< ADC_T::CONF: SPEED Mask                */

#define ADC_IER_MIEN_Pos                 (0)                                               /*!< ADC_T::IER: MIEN Position              */
#define ADC_IER_MIEN_Msk                 (0x1ul << ADC_IER_MIEN_Pos)                       /*!< ADC_T::IER: MIEN Mask                  */

#define ADC_IER_PEDEIEN_Pos              (2)                                               /*!< ADC_T::IER: PEDEIEN Position           */
#define ADC_IER_PEDEIEN_Msk              (0x1ul << ADC_IER_PEDEIEN_Pos)                    /*!< ADC_T::IER: PEDEIEN Mask               */

#define ADC_IER_WKTIEN_Pos               (3)                                               /*!< ADC_T::IER: WKTIEN Position            */
#define ADC_IER_WKTIEN_Msk               (0x1ul << ADC_IER_WKTIEN_Pos)                     /*!< ADC_T::IER: WKTIEN Mask                */

#define ADC_IER_PEUEIEN_Pos              (6)                                               /*!< ADC_T::IER: PEUEIEN Position           */
#define ADC_IER_PEUEIEN_Msk              (0x1ul << ADC_IER_PEUEIEN_Pos)                    /*!< ADC_T::IER: PEUEIEN Mask               */

#define ADC_ISR_MF_Pos                   (0)                                               /*!< ADC_T::ISR: MF Position                */
#define ADC_ISR_MF_Msk                   (0x1ul << ADC_ISR_MF_Pos)                         /*!< ADC_T::ISR: MF Mask                    */

#define ADC_ISR_PEDEF_Pos                (2)                                               /*!< ADC_T::ISR: PEDEF Position             */
#define ADC_ISR_PEDEF_Msk                (0x1ul << ADC_ISR_PEDEF_Pos)                      /*!< ADC_T::ISR: PEDEF Mask                 */

#define ADC_ISR_PEUEF_Pos                (4)                                               /*!< ADC_T::ISR: PEUEF Position             */
#define ADC_ISR_PEUEF_Msk                (0x1ul << ADC_ISR_PEUEF_Pos)                      /*!< ADC_T::ISR: PEUEF Mask                 */

#define ADC_ISR_TF_Pos                   (8)                                               /*!< ADC_T::ISR: TF Position                */
#define ADC_ISR_TF_Msk                   (0x1ul << ADC_ISR_TF_Pos)                         /*!< ADC_T::ISR: TF Mask                    */

#define ADC_ISR_ZF_Pos                   (9)                                               /*!< ADC_T::ISR: ZF Position                */
#define ADC_ISR_ZF_Msk                   (0x1ul << ADC_ISR_ZF_Pos)                         /*!< ADC_T::ISR: ZF Mask                    */

#define ADC_ISR_NACF_Pos                 (10)                                              /*!< ADC_T::ISR: NACF Position              */
#define ADC_ISR_NACF_Msk                 (0x1ul << ADC_ISR_NACF_Pos)                       /*!< ADC_T::ISR: NACF Mask                  */

#define ADC_ISR_INTTC_Pos                (17)                                              /*!< ADC_T::ISR: INTTC Position             */
#define ADC_ISR_INTTC_Msk                (0x1ul << ADC_ISR_INTTC_Pos)                      /*!< ADC_T::ISR: INTTC Mask                 */

#define ADC_WKISR_WPEDEF_Pos             (1)                                               /*!< ADC_T::WKISR: WPEDEF Position          */
#define ADC_WKISR_WPEDEF_Msk             (0x1ul << ADC_WKISR_WPEDEF_Pos)                   /*!< ADC_T::WKISR: WPEDEF Mask              */

#define ADC_XYDATA_XDATA_Pos             (0)                                               /*!< ADC_T::XYDATA: XDATA Position          */
#define ADC_XYDATA_XDATA_Msk             (0xffful << ADC_XYDATA_XDATA_Pos)                 /*!< ADC_T::XYDATA: XDATA Mask              */

#define ADC_XYDATA_YDATA_Pos             (16)                                              /*!< ADC_T::XYDATA: YDATA Position          */
#define ADC_XYDATA_YDATA_Msk             (0xffful << ADC_XYDATA_YDATA_Pos)                 /*!< ADC_T::XYDATA: YDATA Mask              */

#define ADC_ZDATA_Z1DATA_Pos             (0)                                               /*!< ADC_T::ZDATA: Z1DATA Position          */
#define ADC_ZDATA_Z1DATA_Msk             (0xffful << ADC_ZDATA_Z1DATA_Pos)                 /*!< ADC_T::ZDATA: Z1DATA Mask              */

#define ADC_ZDATA_Z2DATA_Pos             (16)                                              /*!< ADC_T::ZDATA: Z2DATA Position          */
#define ADC_ZDATA_Z2DATA_Msk             (0xffful << ADC_ZDATA_Z2DATA_Pos)                 /*!< ADC_T::ZDATA: Z2DATA Mask              */

#define ADC_DATA_ADCDATA_Pos             (0)                                               /*!< ADC_T::DATA: ADCDATA Position          */
#define ADC_DATA_ADCDATA_Msk             (0xffful << ADC_DATA_ADCDATA_Pos)                 /*!< ADC_T::DATA: ADCDATA Mask              */

#define ADC_XYSORT_XSORT_Pos             (0)                                               /*!< ADC_T::XYSORT: XSORT Position          */
#define ADC_XYSORT_XSORT_Msk             (0xffful << ADC_XYSORT_XSORT_Pos)                 /*!< ADC_T::XYSORT: XSORT Mask              */

#define ADC_XYSORT_YSORT_Pos             (16)                                              /*!< ADC_T::XYSORT: YSORT Position          */
#define ADC_XYSORT_YSORT_Msk             (0xffful << ADC_XYSORT_YSORT_Pos)                 /*!< ADC_T::XYSORT: YSORT Mask              */

#define ADC_ZSORT_Z1SORT_Pos             (0)                                               /*!< ADC_T::ZSORT: Z1SORT Position          */
#define ADC_ZSORT_Z1SORT_Msk             (0xffful << ADC_ZSORT_Z1SORT_Pos)                 /*!< ADC_T::ZSORT: Z1SORT Mask              */

#define ADC_ZSORT_Z2SORT_Pos             (16)                                              /*!< ADC_T::ZSORT: Z2SORT Position          */
#define ADC_ZSORT_Z2SORT_Msk             (0xffful << ADC_ZSORT_Z2SORT_Pos)                 /*!< ADC_T::ZSORT: Z2SORT Mask              */

/**@}*/ /* ADC_CONST */
/**@}*/ /* end of ADC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif  //__ADC_REG_H__


