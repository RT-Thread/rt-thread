/**************************************************************************//**
 * @file     M051Series.h
 * @version  V3.0
 * $Revision: 53 $
 * $Date: 14/01/28 2:28p $
 * @brief    M051 Series Peripheral Access Layer Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/

/**
  \mainpage Introduction
  *
  *
  * This user manual describes the usage of M051DN/DE Series MCU device driver
  *
  * <b>Disclaimer</b>
  *
  * The Software is furnished "AS IS", without warranty as to performance or results, and
  * the entire risk as to performance or results is assumed by YOU. Nuvoton disclaims all
  * warranties, express, implied or otherwise, with regard to the Software, its use, or
  * operation, including without limitation any and all warranties of merchantability, fitness
  * for a particular purpose, and non-infringement of intellectual property rights.
  *
  * <b>Copyright Notice</b>
  *
  * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
  */

/**
  * \page PG_DIR Directory Structure
  * The BSP directory structure is shown in following figure.
  *
  * \image html dir.jpg "BSP Directory Structure"
  * \image latex dir.jpg "BSP Directory Structure" width=12cm
  *
  * \page PG_REV Revision History
  *
  *
  * <b>Revision 3.00.001</b>
  * \li Initial release.
*/

#ifndef __M051Series_H__
#define __M051Series_H__


/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

/**
 * @details  Interrupt Number Definition. The maximum of 32 Specific Interrupts are possible.
 */
typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn       = -14,      /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn            = -13,      /*!< 3 Cortex-M0 Hard Fault Interrupt                     */
    SVCall_IRQn               = -5,       /*!< 11 Cortex-M0 SV Call Interrupt                       */
    PendSV_IRQn               = -2,       /*!< 14 Cortex-M0 Pend SV Interrupt                       */
    SysTick_IRQn              = -1,       /*!< 15 Cortex-M0 System Tick Interrupt                   */

    /******  ARMIKMCU Swift specific Interrupt Numbers ************************************************/
    BOD_IRQn                  = 0,        /*!< Brown-Out Low Voltage Detected Interrupt             */
    WDT_IRQn                  = 1,        /*!< Watch Dog Timer Interrupt                            */
    EINT0_IRQn                = 2,        /*!< EINT0 Interrupt                                      */
    EINT1_IRQn                = 3,        /*!< EINT1 Interrupt                                      */
    GPIO_P0P1_IRQn            = 4,        /*!< GPIO_P0P1 Interrupt                                  */
    GPIO_P2P3P4_IRQn          = 5,        /*!< GPIO_P2P3P4 Interrupt                                */
    PWMA_IRQn                 = 6,        /*!< PWMA Interrupt                                       */
    PWMB_IRQn                 = 7,        /*!< PWMB Interrupt                                       */
    TMR0_IRQn                 = 8,        /*!< TIMER0 Interrupt                                     */
    TMR1_IRQn                 = 9,        /*!< TIMER1 Interrupt                                     */
    TMR2_IRQn                 = 10,       /*!< TIMER2 Interrupt                                     */
    TMR3_IRQn                 = 11,       /*!< TIMER3 Interrupt                                     */
    UART0_IRQn                = 12,       /*!< UART0 Interrupt                                      */
    UART1_IRQn                = 13,       /*!< UART1 Interrupt                                      */
    SPI0_IRQn                 = 14,       /*!< SPI0 Interrupt                                       */
    SPI1_IRQn                 = 15,       /*!< SPI1 Interrupt                                       */
    I2C0_IRQn                 = 18,       /*!< I2C0 Interrupt                                       */
    I2C1_IRQn                 = 19,       /*!< I2C1 Interrupt                                       */
    ACMP01_IRQn               = 25,       /*!< ACMP0/1 Interrupt                                    */
    ACMP23_IRQn               = 26,       /*!< ACMP2/3 Interrupt                                    */
    PWRWU_IRQn                = 28,       /*!< Power Down Wake Up Interrupt                         */
    ADC_IRQn                  = 29        /*!< ADC Interrupt                                        */

} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT           0       /*!< armikcmu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        2       /*!< armikcmu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */


#include "core_cm0.h"                   /*!< Cortex-M0 processor and core peripherals             */
#include "system_M051Series.h"          /*!< M051Series System                                    */


#if defined ( __CC_ARM   )
#pragma anon_unions
#endif


/**
 * Initialize the system clock
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system
 *         Initialize the PLL and update the SystemFrequency variable
 */
extern void SystemInit(void);


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- Analog Comparator Controller -------------------------*/
/** @addtogroup ACMP Analog Comparator Controller(ACMP)
  Memory Mapped Structure for ACMP Controller
  @{

 */
typedef struct
{
    __IO uint32_t CR[2];

    __IO uint32_t SR;

} ACMP_T;

/** @addtogroup ACMP_CONST ACMP Bit Field Definition
  Constant Definitions for ACMP Controller
  @{
 */

/* ACMP_CR Bit Field Definitions */
#define ACMP_CR_ACMPOINV_Pos   6                                 /*!< ACMP CR: ACMPOINV Position */
#define ACMP_CR_ACMPOINV_Msk   (1ul << ACMP_CR_ACMPOINV_Pos)     /*!< ACMP CR: ACMPOINV Mask */

#define ACMP_CR_NEGSEL_Pos     4                                 /*!< ACMP CR: NEGSEL Position */
#define ACMP_CR_NEGSEL_Msk     (1ul << ACMP_CR_NEGSEL_Pos)       /*!< ACMP CR: NEGSEL Mask */

#define ACMP_CR_HYSEN_Pos      2                                 /*!< ACMP CR: HYSEN Position */
#define ACMP_CR_HYSEN_Msk      (1ul << ACMP_CR_HYSEN_Pos)        /*!< ACMP CR: HYSEN Mask */

#define ACMP_CR_ACMPIE_Pos     1                                 /*!< ACMP CR: ACMPIE Position */
#define ACMP_CR_ACMPIE_Msk     (1ul << ACMP_CR_ACMPIE_Pos)       /*!< ACMP CR: ACMPIE Mask */

#define ACMP_CR_ACMPEN_Pos     0                                 /*!< ACMP CR: ACMPEN Position */
#define ACMP_CR_ACMPEN_Msk     (1ul << ACMP_CR_ACMPEN_Pos)       /*!< ACMP CR: ACMPEN Mask */

/* ACMP_SR01 Bit Field Definitions */
#define ACMP_SR_ACMPO1_Pos   3                                   /*!< ACMP SR01: ACMPO1 Position */
#define ACMP_SR_ACMPO1_Msk   (1ul << ACMP_SR_ACMPO1_Pos)         /*!< ACMP SR01: ACMPO1 Mask */

#define ACMP_SR_ACMPO0_Pos   2                                   /*!< ACMP SR01: ACMPO0 Position */
#define ACMP_SR_ACMPO0_Msk   (1ul << ACMP_SR_ACMPO0_Pos)         /*!< ACMP SR01: ACMPO0 Mask */

#define ACMP_SR_ACMPF1_Pos   1                                   /*!< ACMP SR01: ACMPF1 Position */
#define ACMP_SR_ACMPF1_Msk   (1ul << ACMP_SR_ACMPF1_Pos)         /*!< ACMP SR01: ACMPF1 Mask */

#define ACMP_SR_ACMPF0_Pos   0                                   /*!< ACMP SR01: ACMPF0 Position */
#define ACMP_SR_ACMPF0_Msk   (1ul << ACMP_SR_ACMPF0_Pos)         /*!< ACMP SR01: ACMPF0 Mask */

/* ACMP_SR23 Bit Field Definitions */
#define ACMP_SR_ACMPO3_Pos   3                                   /*!< ACMP SR23: ACMPO3 Position */
#define ACMP_SR_ACMPO3_Msk   (1ul << ACMP_SR_ACMPO3_Pos)         /*!< ACMP SR23: ACMPO3 Mask */

#define ACMP_SR_ACMPO2_Pos   2                                   /*!< ACMP SR23: ACMPO2 Position */
#define ACMP_SR_ACMPO2_Msk   (1ul << ACMP_SR_ACMPO2_Pos)         /*!< ACMP SR23: ACMPO2 Mask */

#define ACMP_SR_ACMPF3_Pos   1                                   /*!< ACMP SR23: ACMPF3 Position */
#define ACMP_SR_ACMPF3_Msk   (1ul << ACMP_SR_ACMPF3_Pos)         /*!< ACMP SR23: ACMPF3 Mask */

#define ACMP_SR_ACMPF2_Pos   0                                   /*!< ACMP SR23: ACMPF2 Position */
#define ACMP_SR_ACMPF2_Msk   (1ul << ACMP_SR_ACMPF2_Pos)         /*!< ACMP SR23: ACMPF2 Mask */
/**@}*/ /* ACMP_CONST */
/**@}*/ /* ACMP_REG */


/*----------------------------- ADC Controller -------------------------------*/
/** @addtogroup ADC Analog to Digitial Converter(ADC)
  Memory Mapped Structure for ADC Controller
  @{
 */
typedef struct
{
    /**
     * ADDR
     * ===================================================================================================
     * Offset: 0x00-0x1C  A/D Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:0]  |RSLT      |A/D Conversion Result
     * |        |          |This field contains 12 bits conversion result.
     * |[16]    |OVERRUN   |Over Run Flag
     * |        |          |1 = Data in RSLT[11:0] is overwrite.
     * |        |          |0 = Data in RSLT[11:0] is recent conversion result.
     * |        |          |If converted data in RSLT[11:0] has not been read before new conversion result is
     * |        |          |loaded to this register, OVERRUN is set to 1. It will be cleared by hardware after
     * |        |          |ADDR register is read.
     * |[17]    |VALID     |Valid Flag
     * |        |          |1 = Data in RSLT[11:0] bits is valid.
     * |        |          |0 = Data in RSLT[11:0] bits is not valid.
     * |        |          |This bit is set to 1 when corresponding channel analog input conversion is completed
     * |        |          |and cleared by hardware after ADDR register is read.
     */
    __I uint32_t ADDR[8];

    /**
     * ADCR
     * ===================================================================================================
     * Offset: 0x20  A/D Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADEN      |A/D Converter Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |Before starting A/D conversion function, this bit should be set to 1. Clear it to 0 to
     * |        |          |disable A/D converter analog circuit for saving power consumption.
     * |[1]     |ADIE      |A/D Interrupt Enable
     * |        |          |1 = Enable A/D interrupt function
     * |        |          |0 = Disable A/D interrupt function
     * |        |          |A/D conversion end interrupt request is generated if ADIE bit is set to 1.
     * |[3:2]   |ADMD      |A/D Converter Operation Mode
     * |        |          |00 = Single conversion
     * |        |          |01 = Burst conversion
     * |        |          |10 = Single-cycle scan
     * |        |          |11 = Continuous scan
     * |        |          |When changing the operation mode, software should disable ADST bit firstly.
     * |        |          |Note: In Burst Mode, the A/D result data always at Data Register 0.
     * |[5:4]   |TRGS      |Hardware Trigger Source
     * |        |          |00 = A/D conversion is started by external STADC pin.
     * |        |          |Others = Reserved
     * |        |          |Software should disable TRGE and ADST before change TRGS.
     * |        |          |In hardware trigger mode, the ADST bit is set by the external trigger from STADC.
     * |[7:6]   |TRGCOND   |External Trigger Condition
     * |        |          |These two bits decide external pin STADC trigger event is level or edge. The signal
     * |        |          |must be kept at stable state at least 8 PCLKs for level trigger and 4 PCLKs at high and
     * |        |          |low state.
     * |        |          |00 = Low level
     * |        |          |01 = High level
     * |        |          |10 = Falling edge
     * |        |          |11 = Rising edge
     * |[8]     |TRGE      |External Trigger Enable
     * |        |          |Enable or disable triggering of A/D conversion by external STADC pin.
     * |        |          |1= Enable
     * |        |          |0= Disable
     * |[10]    |DIFFEN    |A/D Differential Input Mode Enable
     * |        |          |1 = A/D is in differential analog input mode
     * |        |          |0 = A/D is in single-end analog input mode
     * |        |          |Differential input voltage (Vdiff) = Vplus - Vminus
     * |        |          |The Vplus of differential input paired channel 0 is from ADC0 pin; Vminus is from ADC1 pin.
     * |        |          |The Vplus of differential input paired channel 1 is from ADC2 pin; Vminus is from ADC3 pin.
     * |        |          |The Vplus of differential input paired channel 2 is from ADC4 pin; Vminus is from ADC5 pin.
     * |        |          |The Vplus of differential input paired channel 3 is from ADC6 pin; Vminus is from ADC7 pin.
     * |        |          |In differential input mode, only one of the two corresponding channels needs to be
     * |        |          |enabled in ADCHER. The conversion result will be placed to the corresponding data
     * |        |          |register of the enabled channel. If both channels of a differential input paired channel
     * |        |          |are enabled, the ADC will convert it twice in scan mode. And then write the conversion
     * |        |          |result to the two corresponding data registers.
     * |[11]    |ADST      |A/D Conversion Start
     * |        |          |1 = Conversion start.
     * |        |          |0 = Conversion stopped and A/D converter enter idle state.
     * |        |          |ADST bit can be controlled by two sources: software write and external pin STADC.
     * |        |          |ADST is cleared to 0 by hardware automatically at the ends of single mode and single-
     * |        |          |cycle scan mode on specified channels. In continuous scan mode, A/D conversion is
     * |        |          |continuously performed sequentially until this bit is cleared to 0 or chip reset.
     */
    __IO uint32_t ADCR;

    /**
     * ADCHER
     * ===================================================================================================
     * Offset: 0x24  A/D Channel Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CHEN0     |Analog Input Channel 0 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |This channel is the default enabled channel if CHEN0~7 are set as 0s.
     * |[1]     |CHEN1     |Analog Input Channel 1 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[2]     |CHEN2     |Analog Input Channel 2 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[3]     |CHEN3     |Analog Input Channel 3 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[4]     |CHEN4     |Analog Input Channel 4 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[5]     |CHEN5     |Analog Input Channel 5 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[6]     |CHEN6     |Analog Input Channel 6 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[7]     |CHEN7     |Analog Input Channel 7 Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[9:8]   |PRESEL    |Analog Input Channel 7 select
     * |        |          |00: External analog input
     * |        |          |01: Internal bandgap voltage
     * |        |          |1x: Reserved
     */
    __IO uint32_t ADCHER;

    /**
     * ADCMPR
     * ===================================================================================================
     * Offset: 0x28,0x2C  A/D Compare Register 0 & 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CMPEN     |Compare Enable
     * |        |          |1 = Enable compare.
     * |        |          |0 = Disable compare.
     * |        |          |Set this bit to 1 to enable compare CMPD[11:0] with specified channel conversion
     * |        |          |result when converted data is loaded into ADDR register.
     * |[1]     |CMPIE     |Compare Interrupt Enable
     * |        |          |1 = Enable compare function interrupt.
     * |        |          |0 = Disable compare function interrupt.
     * |        |          |If the compare function is enabled and the compare condition matches the settings
     * |        |          |of CMPCOND and CMPMATCNT, CMPF0 bit will be asserted. If CMPIE is set to
     * |        |          |1, a compare interrupt request is generated.
     * |[2]     |CMPCOND   |Compare Condition
     * |        |          |1= Set the compare condition as that when a 12-bit A/D conversion result is
     * |        |          |greater or equal to the 12-bit CMPD(ADCMPR0[27:16]), the internal match
     * |        |          |counter will increase one.
     * |        |          |0= Set the compare condition as that when a 12-bit A/D conversion result is less
     * |        |          |than the 12-bit CMPD(ADCMPR0[27:16]), the internal match counter will
     * |        |          |increase one.
     * |        |          |Note: When the internal counter reaches the value to (CMPMATCNT +1), the
     * |        |          |CMPF0 bit will be set.
     * |[5:3]   |CMPCH     |Compare Channel Selection
     * |        |          |000 = Channel 0 conversion result is selected to be compared.
     * |        |          |001 = Channel 1 conversion result is selected to be compared.
     * |        |          |010 = Channel 2 conversion result is selected to be compared.
     * |        |          |011 = Channel 3 conversion result is selected to be compared.
     * |        |          |100 = Channel 4 conversion result is selected to be compared.
     * |        |          |101 = Channel 5 conversion result is selected to be compared.
     * |        |          |110 = Channel 6 conversion result is selected to be compared.
     * |        |          |111 = Channel 7 conversion result is selected to be compared.
     * |[11:8]  |CMPMATCNT |Compare Match Count
     * |        |          |When the specified A/D channel analog conversion result matches the compare
     * |        |          |condition defined by CMPCOND[2], the internal match counter will increase 1.
     * |        |          |When the internal counter reaches the value to (CMPMATCNT +1), the CMPF0 bit
     * |        |          |will be set.
     * |[27:16] |CMPD      |Comparison Data
     * |        |          |The 12 bits data is used to compare with conversion result of specified channel.
     * |        |          |Software can use it to monitor the external analog input pin voltage transition in
     * |        |          |scan mode without imposing a load on software.
     */
    __IO uint32_t ADCMPR[2];

    /**
     * ADSR
     * ===================================================================================================
     * Offset: 0x30  ADC Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADF       |A/D Conversion End Flag
     * |        |          |A status flag that indicates the end of A/D conversion.
     * |        |          |ADF is set to 1 at these two conditions:
     * |        |          |1.  When A/D conversion ends in single mode
     * |        |          |2.  When A/D conversion ends on all specified channels in scan mode.
     * |        |          |3.  When more than 4 samples in FIFO in Burst mode.
     * |        |          |This bit can be cleared by writing 1 to itself.
     * |[1]     |CMPF0     |Compare Flag
     * |        |          |When the selected channel A/D conversion result meets the setting conditions of
     * |        |          |ADCMPR0 then this bit will be set to 1. And it can be cleared by writing 1 to itself.
     * |        |          |1 = Conversion result in ADDR meets ADCMPR0 setting
     * |        |          |0 = Conversion result in ADDR does not meet ADCMPR0 setting
     * |[2]     |CMPF1     |Compare Flag
     * |        |          |When the selected channel A/D conversion result meets the setting conditions of
     * |        |          |ADCMPR1 then this bit will be set to 1. And it can be cleared by writing 1 to itself.
     * |        |          |1 = Conversion result in ADDR meets ADCMPR1 setting
     * |        |          |0 = Conversion result in ADDR does not meet ADCMPR1 setting
     * |[3]     |BUSY      |BUSY/IDLE
     * |        |          |1 = A/D converter is busy at conversion.
     * |        |          |0 = A/D converter is in idle state.
     * |        |          |This bit is mirror of as ADST bit in ADCR.
     * |        |          |It is read only.
     * |[6:4]   |CHANNEL   |Current Conversion Channel
     * |        |          |This filed reflects current conversion channel when BUSY=1. When BUSY=0, it
     * |        |          |shows the next channel will be converted.
     * |        |          |It is read only.
     * |[15:8]  |VALID     |Data Valid flag
     * |        |          |It is a mirror of VALID bit in ADDRx
     * |        |          |When ADC is in Burst Mode, and there is at least one valid conversion result in buffer,
     * |        |          |VALID[7:0] will all set to 1.
     * |[23:16] |OVERRUN   |Over Run flag
     * |        |          |It is a mirror to OVERRUN bit in ADDRx
     * |        |          |When ADC is in Burst Mode, and the buffer is overrun, OVERRUN[7:0] will all set to
     * |        |          |1.
     */
    __IO uint32_t ADSR;

    __I  uint32_t RESERVED0[4];

    __IO uint32_t ADTDCR;

} ADC_T;


/** @addtogroup ADC_CONST ADC Bit Field Definition
  Constant Definitions for ADC Controller
  @{
 */
/* ADDR Bit Field Definitions */
#define ADC_ADDR_VALID_Pos      17                                /*!< ADC ADDR: VALID Position */
#define ADC_ADDR_VALID_Msk      (1ul << ADC_ADDR_VALID_Pos)       /*!< ADC ADDR: VALID Mask */

#define ADC_ADDR_OVERRUN_Pos    16                                /*!< ADC ADDR: OVERRUN Position */
#define ADC_ADDR_OVERRUN_Msk    (1ul << ADC_ADDR_OVERRUN_Pos)     /*!< ADC ADDR: OVERRUN Mask */

#define ADC_ADDR_RSLT_Pos       0                                 /*!< ADC ADDR: RSLT Position */
#define ADC_ADDR_RSLT_Msk       (0xFFFFul << ADC_ADDR_RSLT_Pos)   /*!< ADC ADDR: RSLT Mask */

/* ADCR Bit Field Definitions */
#define ADC_ADCR_DMOF_Pos       31                                /*!< ADC ADCR: DMOF Position */
#define ADC_ADCR_DMOF_Msk       (1ul << ADC_ADCR_DMOF_Pos)        /*!< ADC ADCR: DMOF Mask */

#define ADC_ADCR_ADST_Pos       11                                /*!< ADC ADCR: ADST Position */
#define ADC_ADCR_ADST_Msk       (1ul << ADC_ADCR_ADST_Pos)        /*!< ADC ADCR: ADST Mask */

#define ADC_ADCR_DIFFEN_Pos     10                                /*!< ADC ADCR: DIFFEN Position */
#define ADC_ADCR_DIFFEN_Msk     (1ul << ADC_ADCR_DIFFEN_Pos)      /*!< ADC ADCR: DIFFEN Mask */

#define ADC_ADCR_TRGEN_Pos      8                                 /*!< ADC ADCR: TRGEN Position */
#define ADC_ADCR_TRGEN_Msk      (1ul << ADC_ADCR_TRGEN_Pos)       /*!< ADC ADCR: TRGEN Mask */

#define ADC_ADCR_TRGCOND_Pos    6                                 /*!< ADC ADCR: TRGCOND Position */
#define ADC_ADCR_TRGCOND_Msk    (3ul << ADC_ADCR_TRGCOND_Pos)     /*!< ADC ADCR: TRGCOND Mask */

#define ADC_ADCR_TRGS_Pos       4                                 /*!< ADC ADCR: TRGS Position */
#define ADC_ADCR_TRGS_Msk       (3ul << ADC_ADCR_TRGS_Pos)        /*!< ADC ADCR: TRGS Mask */

#define ADC_ADCR_ADMD_Pos       2                                 /*!< ADC ADCR: ADMD Position */
#define ADC_ADCR_ADMD_Msk       (3ul << ADC_ADCR_ADMD_Pos)        /*!< ADC ADCR: ADMD Mask */

#define ADC_ADCR_ADIE_Pos       1                                 /*!< ADC ADCR: ADIE Position */
#define ADC_ADCR_ADIE_Msk       (1ul << ADC_ADCR_ADIE_Pos)        /*!< ADC ADCR: ADIE Mask */

#define ADC_ADCR_ADEN_Pos       0                                 /*!< ADC ADCR: ADEN Position */
#define ADC_ADCR_ADEN_Msk       (1ul << ADC_ADCR_ADEN_Pos)        /*!< ADC ADCR: ADEN Mask */

/* ADCHER Bit Field Definitions */
#define ADC_ADCHER_PRESEL_Pos   8                                 /*!< ADC ADCHER: PRESEL Position */
#define ADC_ADCHER_PRESEL_Msk   (3ul << ADC_ADCHER_PRESEL_Pos)    /*!< ADC ADCHER: PRESEL Mask */

#define ADC_ADCHER_CHEN_Pos     0                                 /*!< ADC ADCHER: CHEN Position */
#define ADC_ADCHER_CHEN_Msk     (0xFFul << ADC_ADCHER_CHEN_Pos)   /*!< ADC ADCHER: CHEN Mask */

/* ADCMPR Bit Field Definitions */
#define ADC_ADCMPR_CMPD_Pos        16                                    /*!< ADC ADCMPR: CMPD Position */
#define ADC_ADCMPR_CMPD_Msk        (0xFFFul << ADC_ADCMPR_CMPD_Pos)      /*!< ADC ADCMPR: CMPD Mask */

#define ADC_ADCMPR_CMPMATCNT_Pos   8                                     /*!< ADC ADCMPR: CMPMATCNT Position */
#define ADC_ADCMPR_CMPMATCNT_Msk   (0xFul << ADC_ADCMPR_CMPMATCNT_Pos)   /*!< ADC ADCMPR: CMPMATCNT Mask */

#define ADC_ADCMPR_CMPCH_Pos       3                                     /*!< ADC ADCMPR: CMPCH Position */
#define ADC_ADCMPR_CMPCH_Msk       (7ul << ADC_ADCMPR_CMPCH_Pos)         /*!< ADC ADCMPR: CMPCH Mask */

#define ADC_ADCMPR_CMPCOND_Pos     2                                     /*!< ADC ADCMPR: CMPCOND Position */
#define ADC_ADCMPR_CMPCOND_Msk     (1ul << ADC_ADCMPR_CMPCOND_Pos)       /*!< ADC ADCMPR: CMPCOND Mask */

#define ADC_ADCMPR_CMPIE_Pos       1                                     /*!< ADC ADCMPR: CMPIE Position */
#define ADC_ADCMPR_CMPIE_Msk       (1ul << ADC_ADCMPR_CMPIE_Pos)         /*!< ADC ADCMPR: CMPIE Mask */

#define ADC_ADCMPR_CMPEN_Pos       0                                     /*!< ADC ADCMPR: CMPEN Position */
#define ADC_ADCMPR_CMPEN_Msk       (1ul << ADC_ADCMPR_CMPEN_Pos)         /*!< ADC ADCMPR: CMPEN Mask */

/* ADSR Bit Field Definitions */
#define ADC_ADSR_OVERRUN_Pos       16                                    /*!< ADC ADSR: OVERRUN Position */
#define ADC_ADSR_OVERRUN_Msk       (0xFFul << ADC_ADSR_OVERRUN_Pos)      /*!< ADC ADSR: OVERRUN Mask */

#define ADC_ADSR_VALID_Pos         8                                     /*!< ADC ADSR: VALID Position */
#define ADC_ADSR_VALID_Msk         (0xFFul << ADC_ADSR_VALID_Pos)        /*!< ADC ADSR: VALID Mask */

#define ADC_ADSR_CHANNEL_Pos       4                                     /*!< ADC ADSR: CHANNEL Position */
#define ADC_ADSR_CHANNEL_Msk       (7ul << ADC_ADSR_CHANNEL_Pos)         /*!< ADC ADSR: CHANNEL Mask */

#define ADC_ADSR_BUSY_Pos          3                                     /*!< ADC ADSR: BUSY Position */
#define ADC_ADSR_BUSY_Msk          (1ul << ADC_ADSR_BUSY_Pos)            /*!< ADC ADSR: BUSY Mask */

#define ADC_ADSR_CMPF1_Pos         2                                     /*!< ADC ADSR: CMPF1 Position */
#define ADC_ADSR_CMPF1_Msk         (1ul << ADC_ADSR_CMPF1_Pos)           /*!< ADC ADSR: CMPF1 Mask */

#define ADC_ADSR_CMPF0_Pos         1                                     /*!< ADC ADSR: CMPF0 Position */
#define ADC_ADSR_CMPF0_Msk         (1ul << ADC_ADSR_CMPF0_Pos)           /*!< ADC ADSR: CMPF0 Mask */

#define ADC_ADSR_ADF_Pos           0                                     /*!< ADC ADSR: ADF Position */
#define ADC_ADSR_ADF_Msk           (1ul << ADC_ADSR_ADF_Pos)             /*!< ADC ADSR: ADF Mask */

/* ADTDCR Bit Field Definitions */
#define ADC_ADTDCR_PTDT_Pos        0                                     /*!< ADC ADTDCR: PTDT Position */
#define ADC_ADTDCR_PTDT_Msk        (0xFFul << ADC_ADTDCR_PTDT_Pos)       /*!< ADC ADTDCR: PTDT Mask */
/**@}*/ /* ADC_CONST */
/**@}*/ /* ADC */



/*----------------------- Hardware Divider Interface Controller ------------------*/
/** @addtogroup HDIV Hardware Divider(HDIV)
  Memory Mapped Structure for Divider Interface Controller
  @{
 */
typedef struct
{
    /**
     * DIVIDEND
     * ===================================================================================================
     * Offset: 0x00  Dividend Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DIVIDEND  |Dividend Source.
     * |        |          |This register is given the dividend of divider before calculation starts.
     */
    __IO  int32_t DIVIDEND;

    /**
     * DIVISOR
     * ===================================================================================================
     * Offset: 0x04  Divisor Source Resister
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |DIVISOR   |Divisor Source.
     * |        |          |This register is given the divisor of divider before calculation starts.
     * |        |          |Note: when this register is written, hardware divider will start calculate
     */
    __IO  int32_t DIVISOR;

    /**
     * DIVQUO
     * ===================================================================================================
     * Offset: 0x08  Quotient Result Resister
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |QUOTIENT  |Quotient Result
     * |        |          |This register holds the quotient result of divider after calculation complete.
     */
    __IO  int32_t DIVQUO;

    /**
     * DIVREM
     * ===================================================================================================
     * Offset: 0x08  Reminder Result Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |QUOTIENT  |Reminder Result
     * |        |          |This register holds the reminder result of divider after calculation complete.
     */
    __IO  int32_t DIVREM;

    /**
     * DIVSTS
     * ===================================================================================================
     * Offset: 0x08  Divider Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DIV_FINISH|Divider operation finished.
     * |        |          |0 = The divider calculation is not yet.
     * |        |          |1 = The divider calculation is finished.
     * |        |          |This register is read only.
     * |[1]     |DIV0      |Divisor zero warning.
     * |        |          |0 = The divisor is not 0.
     * |        |          |1 = The divisor is 0.
     * |        |          |This register is read only.
     */
    __IO uint32_t DIVSTS;

} HDIV_T;


/** @addtogroup HDIV_CONST HDIV Bit Field Definition
  Constant Definitions for HDIV Controller
  @{
 */

#define HDIV_DIVSTS_DIV_FINISH_Pos   0
#define HDIV_DIVSTS_DIV_FINISH_Msk   (1ul << HDIV_DIVSTS_DIV_FINISH_Pos)

#define HDIV_DIVSTS_DIV0_Pos         1
#define HDIV_DIVSTS_DIV0_Msk         (1ul << HDIV_DIVSTS_DIV0_Pos)

/**@}*/ /* HDIV_CONST */
/**@}*/ /* DIV */



/*----------------------- External Bus Interface Controller ------------------*/
/** @addtogroup EBI External Bus Interface(EBI)
  Memory Mapped Structure for External Bus Interface Controller
  @{
 */
typedef struct
{
    /**
     * EBICON
     * ===================================================================================================
     * Offset: 0x00  EBI Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ExtEN     |EBI Enable
     * |        |          |This bit is the functional enable bit for EBI.
     * |        |          |0 = EBI function is disabled
     * |        |          |1 = EBI function is enabled
     * |[1]     |ExtBW16   |EBI data width 16 bit
     * |        |          |This bit defines if the data bus is 8-bit or 16-bit.
     * |        |          |0 = EBI data width is 8 bit
     * |        |          |1 = EBI data width is 16 bit
     * |[10:8]  |MCLKDIV   |External Output Clock Divider
     * |        |          |The frequency of EBI output clock is controlled by MCLKDIV.
     * |        |          |000 = HCLK/1
     * |        |          |001 = HCLK/2
     * |        |          |010 = HCLK/4
     * |        |          |011 = HCLK/8
     * |        |          |100 = HCLK/16
     * |        |          |101 = HCKL/32
     * |        |          |11X = default
     * |        |          |Notice: Default value of output clock is HCLK/1
     * |[18:16] |ExttALE   |Expand Time of ALE
     * |        |          |The ALE width (tALE) to latch the address can be controlled by ExttALE.
     * |        |          |tALE = (ExttALE + 1) * MCLK
     */
    __IO uint32_t EBICON;

    /**
     * EXTIME
     * ===================================================================================================
     * Offset: 0x04  EBI Timing Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:3]   |ExttACC   |EBI Data Accesss Time
     * |        |          |ExttACC define data access time (tACC).
     * |        |          |tACC = (ExttACC + 1) * MCLK
     * |[10:8]  |ExttAHD   |EBI Data Access Hold Time
     * |        |          |ExttAHD define data access hold time (tAHD).
     * |        |          |tAHD = (ExttAHD + 1) * MCLK
     * |[15:12] |ExtIW2X   |Idle State Cycle After Write
     * |        |          |When write action is finish, idle state is inserted and nCS return to high if ExtIW2X is not zero.
     * |        |          |Idle state cycle = (ExtIW2X * MCLK)
     * |[27:24] |ExtIR2R   |Idle State Cycle Between Read-Read
     * |        |          |When read action is finish and next action is going to read, idle state is inserted and nCS return
     * |        |          |to high if ExtIR2R is not zero.
     * |        |          |Idle state cycle = (ExtIR2R * MCLK)
     */
    __IO uint32_t EXTIME;

    /**
     * EBICON2
     * ===================================================================================================
     * Offset: 0x08   External Bus Interface General Control Register 2
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t EBICON2;
} EBI_T;


/** @addtogroup EBI_CONST EBI Bit Field Definition
  Constant Definitions for EBI Controller
  @{
 */
/* EBI EBICON Bit Field Definitions */
#define EBI_EBICON_ExttALE_Pos      16                                          /*!< EBI EBICON: ExttALE Position */
#define EBI_EBICON_ExttALE_Msk      (0x7ul << EBI_EBICON_ExttALE_Pos)           /*!< EBI EBICON: ExttALE Mask */

#define EBI_EBICON_MCLKDIV_Pos      8                                           /*!< EBI EBICON: MCLKDIV Position */
#define EBI_EBICON_MCLKDIV_Msk      (0x7ul << EBI_EBICON_MCLKDIV_Pos)           /*!< EBI EBICON: MCLKDIV Mask */

#define EBI_EBICON_ExtBW16_Pos      1                                           /*!< EBI EBICON: ExtBW16 Position */
#define EBI_EBICON_ExtBW16_Msk      (1ul << EBI_EBICON_ExtBW16_Pos)             /*!< EBI EBICON: ExtBW16 Mask */

#define EBI_EBICON_ExtEN_Pos        0                                           /*!< EBI EBICON: ExtEN Position */
#define EBI_EBICON_ExtEN_Msk        (1ul << EBI_EBICON_ExtEN_Pos)               /*!< EBI EBICON: ExtEN Mask */

/* EBI EXTIME Bit Field Definitions */
#define EBI_EXTIME_ExtIR2R_Pos      24                                          /*!< EBI EXTIME: ExtIR2R Position */
#define EBI_EXTIME_ExtIR2R_Msk      (0xFul << EBI_EXTIME_ExtIR2R_Pos)           /*!< EBI EXTIME: ExtIR2R Mask */

#define EBI_EXTIME_ExtIW2X_Pos      12                                          /*!< EBI EXTIME: ExtIW2X Position */
#define EBI_EXTIME_ExtIW2X_Msk      (0xFul << EBI_EXTIME_ExtIW2X_Pos)           /*!< EBI EXTIME: ExtIW2X Mask */

#define EBI_EXTIME_ExttAHD_Pos      8                                           /*!< EBI EXTIME: ExttAHD Position */
#define EBI_EXTIME_ExttAHD_Msk      (0x7ul << EBI_EXTIME_ExttAHD_Pos)           /*!< EBI EXTIME: ExttAHD Mask */

#define EBI_EXTIME_ExttACC_Pos      3                                           /*!< EBI EXTIME: ExttACC Position */
#define EBI_EXTIME_ExttACC_Msk      (0x1Ful << EBI_EXTIME_ExttACC_Pos)          /*!< EBI EXTIME: ExttACC Mask */

/* EBI EBICON2 Bit Field Definitions */
#define EBI_EBICON2_WAHD_OFF_Pos    2                                           /*!< EBI EBICON2: WAHD_OFF Position */
#define EBI_EBICON2_WAHD_OFF_Msk    (1ul << EBI_EBICON2_WAHD_OFF_Pos)           /*!< EBI EBICON2: WAHD_OFF Mask */

#define EBI_EBICON2_RAHD_OFF_Pos    1                                           /*!< EBI EBICON2: RAHD_OFF Position */
#define EBI_EBICON2_RAHD_OFF_Msk    (1ul << EBI_EBICON2_RAHD_OFF_Pos)           /*!< EBI EBICON2: RAHD_OFF Mask */

#define EBI_EBICON2_WBUFF_EN_Pos    0                                           /*!< EBI EBICON2: WBUFF_EN Position */
#define EBI_EBICON2_WBUFF_EN_Msk    (1ul << EBI_EBICON2_WBUFF_EN_Pos)           /*!< EBI EBICON2: WBUFF_EN Mask */
/**@}*/ /* EBI_CONST */
/**@}*/ /* EBI */




/*-------------------------- FLASH Memory Controller -------------------------*/

/** @addtogroup FMC Flash Memory Controller(FMC)
 *
 * Memory Mapped Structure for Flash Memory Controller
 * @{
 */
typedef struct
{
    /**
     * ISPCON
     * ===================================================================================================
     * Offset: 0x00  ISP Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISPEN     |ISP Enable
     * |        |          |This bit is protected bit. ISP function enable bit. Set this bit to enable ISP function.
     * |        |          |1 = Enable ISP function
     * |        |          |0 = Disable ISP function
     * |[1]     |BS        |Boot Select
     * |        |          |This bit is protected bit. Set/clear this bit to select next booting from LDROM/APROM,
     * |        |          |respectively. This bit also functions as MCU booting status flag, which can be used to check where
     * |        |          |MCU booted from. This bit is initiated with the inversed value of CBS in Config0 after power-
     * |        |          |on reset; It keeps the same value at other reset.
     * |        |          |1 = boot from LDROM
     * |        |          |0 = boot from APROM
     * |[3]     |APUEN     |APROM Update Enable (write-protected)
     * |        |          |1 = APROM can be updated when the chip runs in APROM
     * |        |          |0 = APROM can not be updated when the chip runs in APROM
     * |[4]     |CFGUEN    |Config Update Enable
     * |        |          |Writing this bit to 1 enables s/w to update Config value by ISP procedure regardless of program
     * |        |          |code is running in APROM or LDROM.
     * |        |          |1 = Config update enable
     * |        |          |0 = Config update disable
     * |[5]     |LDUEN     |LDROM Update Enable
     * |        |          |LDROM update enable bit.
     * |        |          |1 = LDROM can be updated when the MCU runs in APROM.
     * |        |          |0 = LDROM cannot be updated
     * |[6]     |ISPFF     |ISP Fail Flag
     * |        |          |(1) APROM writes to itself.
     * |        |          |(2) LDROM writes to itself.
     * |        |          |(3) CONFIG is erased/programmed when CFGUEN is set to 0
     * |        |          |(4) Destination address is illegal, such as over an available range.
     * |        |          |Write 1 to clear this bit.
     */
    __IO uint32_t ISPCON;

    /**
     * ISPADR
     * ===================================================================================================
     * Offset: 0x04  ISP Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPADR    |ISP Address
     * |        |          |NuMicro M051 series equips with a maximum 16kx32 embedded flash, it supports word program
     * |        |          |only. ISPARD[1:0] must be kept 2'b00 for ISP operation.
     */
    __IO uint32_t ISPADR;

    /**
     * ISPDAT
     * ===================================================================================================
     * Offset: 0x08  ISP Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPDAT    |ISP Data
     * |        |          |Write data to this register before ISP program operation
     * |        |          |Read data from this register after ISP read operation
     */
    __IO uint32_t ISPDAT;

    /**
     * ISPCMD
     * ===================================================================================================
     * Offset: 0x0C  ISP Command Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |FOEN_FCEN_FCTRL|ISP Command
     * |        |          |ISP command table is shown below:
     * |        |          |Operation Mode, FOEN, FCEN, FCTRL[3:0]
     * |        |          |Read          ,    0,    0, 0000
     * |        |          |Program       ,    1,    0, 0001
     * |        |          |Page Erase    ,    1,    0, 0010
     */
    __IO uint32_t ISPCMD;

    /**
     * ISPTRG
     * ===================================================================================================
     * Offset: 0x10  IISP Trigger Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISPGO     |ISP start trigger
     * |        |          |Write 1 to start ISP operation and this bit will be cleared to 0 by hardware automatically when ISP
     * |        |          |operation is finish.
     * |        |          |1 = ISP is on going
     * |        |          |0 = ISP done
     */
    __IO uint32_t ISPTRG;

    /**
     * DFBADR
     * ===================================================================================================
     * Offset: 0x14  Data Flash Base Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DFBA      |Data Flash Base Address
     * |        |          |This register indicates data flash start address.
     * |        |          |It is a read only register.
     * |        |          |For 8/16/32/64kB flash memory device, the data flash size is 4kB and it start address is fixed at
     * |        |          |0x01F000 by hardware internally.
     */
    __I  uint32_t DFBADR;

    /**
     * FATCON
     * ===================================================================================================
     * Offset: 0x18  Flash Access Time Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4]     |LFOM      |Low Frequency Optimization Mode (write-protected)
     * |        |          |1 = Flash access always no wait state (zero wait state)
     * |        |          |0 = Insert wait state while Flash access discontinued address.
     * |        |          |Note: Set this bit only when HCLK <= 25MHz. If HCLK > 25MHz, CPU will fetch wrong
     * |        |          |code and cause fail result.
     */
    __IO uint32_t FATCON;

    __I uint32_t Reserved[9];

    /**
     * ISPSTA
     * ===================================================================================================
     * Offset: 0x40  ISP Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISPGO     |ISP Start Trigger (Read Only)
     * |        |          |Write 1 to start ISP operation and this bit will be cleared to 0 by hardware
     * |        |          |automatically when ISP operation is finished.
     * |        |          |1 = ISP operation progressed.
     * |        |          |0 = ISP operation finished.
     * |        |          |Note: This bit is the same as ISPTRG bit0
     * |[2:1]   |CBS       |Chip Boot Selection (Read Only)
     * |        |          |This is a mirror of CBS in Config0.
     * |[6]     |ISPFF     |ISP Fail Flag (Write-protection Bit)
     * |        |          |This bit is set by hardware when a triggered ISP meets any of the following conditions:
     * |        |          |(1) APROM writes to itself.
     * |        |          |(2) LDROM writes to itself.
     * |        |          |(3) CONFIG is erased/programmed when CFGUEN is set to 0
     * |        |          |(4) Destination address is illegal, such as over an available range.
     * |[20:9]  |VECMAP    |Vector Page Mapping Address (Read Only)
     * |        |          |The current flash address space 0x0000_0000~0x0000_01FF is mapping to the address
     * |        |          |specified by the VECMAP * 512.
     */
    __IO uint32_t ISPSTA;

} FMC_T;

/** @addtogroup FMC_CONST FMC Bit Field Definition
  Constant Definitions for FMC Controller
  @{
 */
/* FMC ISPCON Bit Field Definitions */
#define FMC_ISPCON_ISPFF_Pos                    6                                       /*!< FMC ISPCON: ISPFF Position */
#define FMC_ISPCON_ISPFF_Msk                    (1ul << FMC_ISPCON_ISPFF_Pos)           /*!< FMC ISPCON: ISPFF Mask */

#define FMC_ISPCON_LDUEN_Pos                    5                                       /*!< FMC ISPCON: LDUEN Position */
#define FMC_ISPCON_LDUEN_Msk                    (1ul << FMC_ISPCON_LDUEN_Pos)           /*!< FMC ISPCON: LDUEN Mask */

#define FMC_ISPCON_CFGUEN_Pos                   4                                       /*!< FMC ISPCON: CFGUEN Position */
#define FMC_ISPCON_CFGUEN_Msk                   (1ul << FMC_ISPCON_CFGUEN_Pos)          /*!< FMC ISPCON: CFGUEN Mask */

#define FMC_ISPCON_APUEN_Pos                    3                                       /*!< FMC ISPCON: APUEN Position */
#define FMC_ISPCON_APUEN_Msk                    (1ul << FMC_ISPCON_APUEN_Pos)           /*!< FMC ISPCON: APUEN Mask */

#define FMC_ISPCON_BS_Pos                       1                                       /*!< FMC ISPCON: BS Position */
#define FMC_ISPCON_BS_Msk                       (1ul << FMC_ISPCON_BS_Pos)              /*!< FMC ISPCON: BS Mask */

#define FMC_ISPCON_ISPEN_Pos                    0                                       /*!< FMC ISPCON: ISPEN Position */
#define FMC_ISPCON_ISPEN_Msk                    (1ul << FMC_ISPCON_ISPEN_Pos)           /*!< FMC ISPCON: ISPEN Mask */


/* FMC ISPCMD Bit Field Definitions */
#define FMC_ISPCMD_FOEN_Pos                     5                                       /*!< FMC ISPCMD: FOEN Position */
#define FMC_ISPCMD_FOEN_Msk                     (1ul << FMC_ISPCMD_FOEN_Pos)            /*!< FMC ISPCMD: FOEN Mask */

#define FMC_ISPCMD_FCEN_Pos                     4                                       /*!< FMC ISPCMD: FCEN Position */
#define FMC_ISPCMD_FCEN_Msk                     (1ul << FMC_ISPCMD_FCEN_Pos)            /*!< FMC ISPCMD: FCEN Mask */

#define FMC_ISPCMD_FCTRL_Pos                    0                                       /*!< FMC ISPCMD: FCTRL Position */
#define FMC_ISPCMD_FCTRL_Msk                    (0xFul << FMC_ISPCMD_FCTRL_Pos)         /*!< FMC ISPCMD: FCTRL Mask */

/* FMC ISPTRG Bit Field Definitions */
#define FMC_ISPTRG_ISPGO_Pos                    0                                       /*!< FMC ISPTRG: ISPGO Position */
#define FMC_ISPTRG_ISPGO_Msk                    (1ul << FMC_ISPTRG_ISPGO_Pos)           /*!< FMC ISPTRG: ISPGO Mask */

/* FMC FATCON Bit Field Definitions */
#define FMC_FATCON_LFOM_Pos                     4                                       /*!< FMC FATCON: LFOM Position */
#define FMC_FATCON_LFOM_Msk                     (1ul << FMC_FATCON_LFOM_Pos)            /*!< FMC FATCON: LFOM Mask */

/* FMC ISPSTA Bit Field Definitions */
#define FMC_ISPSTA_ISPGO_Pos                    0                                       /*!< FMC ISPSTA: ISPGO Position */
#define FMC_ISPSTA_ISPGO_Msk                    (1ul << FMC_ISPSTA_ISPGO_Pos)           /*!< FMC ISPSTA: ISPGO Mask */

#define FMC_ISPSTA_CBS_Pos                      1                                       /*!< FMC ISPSTA: CBS Position */
#define FMC_ISPSTA_CBS_Msk                      (3ul << FMC_ISPSTA_CBS_Pos)             /*!< FMC ISPSTA: CBS Mask */

#define FMC_ISPSTA_ISPFF_Pos                    6                                       /*!< FMC ISPSTA: ISPFF Position */
#define FMC_ISPSTA_ISPFF_Msk                    (1ul << FMC_ISPSTA_ISPFF_Pos)           /*!< FMC ISPSTA: ISPFF Mask */

#define FMC_ISPSTA_VECMAP_Pos                   9                                       /*!< FMC ISPSTA: VECMAP Position */
#define FMC_ISPSTA_VECMAP_Msk                   (0xffful << FMC_ISPSTA_VECMAP_Pos)      /*!< FMC ISPSTA: VECMAP Mask */
/**@}*/ /* FMC_CONST */
/**@}*/ /* FMC */

/*---------------------------- Global Controller -----------------------------*/

/** @addtogroup GCR System Global Contoller(SYS)
  Memory Mapped Structure for System Global Controller
  @{
 */
typedef struct
{
    /**
     * PDID
     * ===================================================================================================
     * Offset: 0x00  Part Device Identification Number Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |PDID      |This register reflects device part number code. S/W can read this register to identify which device is
     * |        |          |used.
     */
    __I  uint32_t PDID;

    /**
     * RSTSRC
     * ===================================================================================================
     * Offset: 0x04  System Reset Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:8]  |Reserved  |Reserved
     * |[7]     |RSTS_CPU  |The RSTS_CPU flag is set by hardware if software writes CPU_RST (IPRSTC1[1]) 1 to reset Cortex-M0 CPU kernel and Flash memory controller (FMC).
     * |        |          |1 = The Cortex-M0 CPU kernel and FMC are reset by software setting CPU_RST to 1.
     * |        |          |0 = No reset from CPU
     * |        |          |Software can write 1 to clear this bit to zero.
     * |[6]     |Reserved  |Reserved
     * |[5]     |RSTS_MCU  |The RSTS_MCU flag is set by the "reset signal" from the MCU Cortex_M0 kernel to indicate the previous reset source.
     * |        |          |1= The MCU Cortex_M0 had issued the reset signal to reset the system by software writing 1 to bit SYSRESTREQ(AIRCR[2], Application Interrupt and Reset Control Register) in system control registers of Cortex_M0 kernel.
     * |        |          |0= No reset from MCU
     * |        |          |This bit is cleared by writing 1 to itself.
     * |[4]     |RSTS_BOD  |The RSTS_BOD flag is set by the "reset signal" from the Brown-Out Detector to indicate the previous reset source.
     * |        |          |1= The Brown-Out Detector module had issued the reset signal to reset the system.
     * |        |          |0= No reset from BOD
     * |        |          |Software can write 1 to clear this bit to zero.
     * |[3]     |RSTS_LVR  |The RSTS_LVR flag is set by the "reset signal" from the Low-Voltage-Reset controller to indicate the previous reset source.
     * |        |          |1= The LVR module had issued the reset signal to reset the system.
     * |        |          |0= No reset from LVR
     * |        |          |Software can write 1 to clear this bit to zero.
     * |[2]     |RSTS_WDT  |The RSTS_WDT flag is set by the "reset signal" from the Watchdog timer to indicate the previous reset source.
     * |        |          |1= The Watchdog timer had issued the reset signal to reset the system.
     * |        |          |0= No reset from Watchdog timer
     * |        |          |Software can write 1 to clear this bit to zero.
     * |[1]     |RSTS_RESET|The RSTS_RESET flag is set by the "reset signal" from the /RESET pin to indicate the previous reset source.
     * |        |          |1= The Pin /RESET had issued the reset signal to reset the system.
     * |        |          |0= No reset from Pin /RESET
     * |        |          |Software can write 1 to clear this bit to zero.
     * |[0]     |RSTS_POR  |The RSTS_POR flag is set by the "reset signal", which is from the Power-On Reset (POR) module or bit CHIP_RST (IPRSTC1[0]) is set, to indicate the previous reset source.
     * |        |          |1= The Power-On-Reset (POR) or CHIP_RST had issued the reset signal to reset the system.
     * |        |          |0= No reset from POR or CHIP_RST
     * |        |          |Software can write 1 to clear this bit to zero.
     */
    __IO uint32_t RSTSRC;

    /**
     * IPRSTC1
     * ===================================================================================================
     * Offset: 0x08  Peripheral Reset Control Resister 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CHIP_RST  |CHIP one shot reset.
     * |        |          |Set this bit will reset the CHIP, including CPU kernel and all peripherals, and this bit will
     * |        |          |automatically return to "0" after the 2 clock cycles.
     * |        |          |The CHIP_RST is same as the POR reset , all the chip module is reset and the chip setting from
     * |        |          |flash are also reload
     * |        |          |This bit is the protected bit, program this need an open lock sequence, write "59h","16h","88h" to
     * |        |          |address 0x5000_0100 to un-lock this bit. Reference the register REGWRPROT at address GCR_BA
     * |        |          |+ 0x100
     * |        |          |0= Normal
     * |        |          |1= Reset CHIP
     * |[1]     |CPU_RST   |CPU kernel one shot reset.
     * |        |          |Set this bit will reset the Cortex-M0 CPU kernel and Flash memory controller (FMC). This bit will
     * |        |          |automatically return to "0" after the 2 clock cycles
     * |        |          |This bit is the protected bit, program this need an open lock sequence, write "59h","16h","88h" to
     * |        |          |address 0x5000_0100 to un-lock this bit. Reference the register REGWRPROT at address GCR_BA
     * |        |          |+ 0x100
     * |        |          |0= Normal
     * |        |          |1= Reset CPU
     * |[3]     |EBI_RST   |EBI Controller Reset
     * |        |          |Set these bit "1" will generate a reset signal to the EBI. User need to set this bit to "0" to release
     * |        |          |from the reset state
     * |        |          |This bit is the protected bit, program this need an open lock sequence, write "59h","16h","88h" to
     * |        |          |address 0x5000_0100 to un-lock this bit. Reference the register REGWRPROT at address GCR_BA
     * |        |          |+ 0x100
     * |        |          |0= Normal operation
     * |        |          |1= EBI IP reset
     */
    __IO uint32_t IPRSTC1;

    /**
     * IPRSTC2
     * ===================================================================================================
     * Offset: 0x0C  Peripheral Reset Control Resister 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |GPIO_RST  |GPIO (P0~P4) controller Reset
     * |        |          |0= GPIO controller normal operation
     * |        |          |1= GPIO controller reset
     * |[2]     |TMR0_RST  |Timer0 controller Reset
     * |        |          |0= Timer0 controller normal operation
     * |        |          |1= Timer0 controller reset
     * |[3]     |TMR1_RST  |Timer1 controller Reset
     * |        |          |0= Timer1 controller normal operation
     * |        |          |1= Timer1 controller reset
     * |[4]     |TMR2_RST  |Timer2 controller Reset
     * |        |          |0= Timer2 controller normal operation
     * |        |          |1= Timer2 controller reset
     * |[5]     |TMR3_RST  |Timer3 controller Reset
     * |        |          |0= Timer3 controller normal operation
     * |        |          |1= Timer3 controller reset
     * |[8]     |I2C_RST   |I2C controller Reset
     * |        |          |0= I2C controller normal operation
     * |        |          |1= I2C controller reset
     * |[12]    |SPI0_RST  |SPI0 controller Reset
     * |        |          |0= SPI0 controller normal operation
     * |        |          |1= SPI0 controller reset
     * |[13]    |SPI1_RST  |SPI1 controller Reset
     * |        |          |0= SPI1 controller normal operation
     * |        |          |1= SPI1 controller reset
     * |[16]    |UART0_RST |UART0 controller Reset
     * |        |          |0= UART0 controller Normal operation
     * |        |          |1= UART0 controller reset
     * |[17]    |UART1_RST |UART1 controller Reset
     * |        |          |0 = UART1 controller normal operation
     * |        |          |1 = UART1 controller reset
     * |[20]    |PWM03_RST |PWM0~3 controller Reset
     * |        |          |0= PWM0~3 controller normal operation
     * |        |          |1= PWM0~3 controller reset
     * |[21]    |PWM47_RST |PWM4~7 controller Reset
     * |        |          |0= PWM4~7 controller normal operation
     * |        |          |1= PWM4~7 controller reset
     * |[28]    |ADC_RST   |ADC Controller Reset
     * |        |          |0= ADC controller normal operation
     * |        |          |1= ADC controller reset
     */
    __IO uint32_t IPRSTC2;

    /**
     * RESERVED0
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    uint32_t RESERVED0[2];

    /**
     * BODCR
     * ===================================================================================================
     * Offset: 0x18  Brown-Out Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BOD_EN    |Brown Out Detector Enable (initiated & write-protected bit)
     * |        |          |The default value is set by flash controller user configuration register config0 bit[23]
     * |        |          |1= Brown Out Detector function is enabled
     * |        |          |0= Brown Out Detector function is disabled
     * |[2:1]   |BOD_VL    |Brown Out Detector Threshold Voltage Selection (initiated & write-protected bit)
     * |        |          |The default value is set by flash controller user configuration register config0 bit[22:21]
     * |        |          |CBOV[1]
     * |        |          |CBOV[0]
     * |        |          |Brown out voltage
     * |        |          |11 = 4.5V
     * |        |          |10 = 3.8V
     * |        |          |01 = 2.7V
     * |        |          |00 = 2.2V
     * |[3]     |BOD_RSTEN |Brown Out Reset Enable (initiated & write-protected bit)
     * |        |          |1= Enable the Brown Out "RESET" function, when the Brown Out Detector function is enable
     * |        |          |and the detected voltage is lower than the threshold then assert a signal to reset the chip
     * |        |          |The default value is set by flash controller user configuration register config0 bit[20]
     * |        |          |0= Enable the Brown Out "INTERRUPT" function, when the Brown Out Detector function is
     * |        |          |enable and the detected voltage is lower than the threshold then assert a signal to interrupt
     * |        |          |the MCU Cortex-M0
     * |        |          |When the BOD_EN is enabled and the interrupt is assert, the interrupt will keep till to the
     * |        |          |BOD_EN set to "0". The interrupt for CPU can be blocked by disable the NVIC in CPU for BOD
     * |        |          |interrupt or disable the interrupt source by disable the BOD_EN and then re-enable the BOD_EN
     * |        |          |function if the BOD function is required
     * |[4]     |BOD_INTF  |Brown Out Detector Interrupt Flag
     * |        |          |1= When Brown Out Detector detects the VDD is dropped through the voltage of BOD_VL setting
     * |        |          |or the VDD is raised up through the voltage of BOD_VL setting, this bit is set to "1" and the
     * |        |          |brown out interrupt is requested if brown out interrupt is enabled.
     * |        |          |0= Brown Out Detector does not detect any voltage draft at VDD down through or up through the
     * |        |          |voltage of BOD_VL setting.
     * |[5]     |BOD_LPM   |Brown Out Detector Low power Mode (write-protected bit)
     * |        |          |1= Enable the BOD low power mode
     * |        |          |0= BOD operate in normal mode (default)
     * |        |          |The BOD consumes about 100uA in normal mode, the low power mode can reduce the current
     * |        |          |to about 1/10 but slow the BOD response.
     * |[6]     |BOD_OUT   |The status for Brown Out Detector output state
     * |        |          |1= Brown Out Detector status output is 1, the detected voltage is lower than BOD_VL setting. If
     * |        |          |the BOD_EN is "0"(disabled), this bit always response "0"
     * |        |          |0= Brown Out Detector status output is 0, the detected voltage is higher than BOD_VL setting
     * |[7]     |LVR_EN    |Low Voltage Reset Enable (write-protected bit)
     * |        |          |The LVR function reset the chip when the input power voltage is lower than LVR circuit setting.
     * |        |          |LVR function is enabled in default.
     * |        |          |1= Enabled Low Voltage Reset function - After enable the bit, the LVR function will active with
     * |        |          |100uS delay for LVR output stable.(default).
     * |        |          |0= Disabled Low Voltage Reset function
     */
    __IO uint32_t BODCR;

    /**
     * TEMPCR
     * ===================================================================================================
     * Offset: 0x1C  Temperature Sensor Control Register
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t TEMPCR;

    /**
     * RESERVED1
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    uint32_t RESERVED1;

    /**
     * PORCR
     * ===================================================================================================
     * Offset: 0x24  Power-On-Reset Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field       |Descriptions
     * | :----: | :----:     | :---- |
     * |[15:0]  |POR_DIS_CODE|The register is used for the Power-On-Reset enable control.
     * |        |            |When power on, the POR circuit generates a reset signal to reset the whole chip function,
     * |        |            |but noise on the power may cause the POR active again. If set the POR_DIS_CODE equal
     * |        |            |to 0x5AA5, the POR reset function will be disabled and the POR function will re-active till
     * |        |            |the power voltage is lower to set the POR_DIS_CODE to another value or reset by chip
     * |        |            |other reset function. Include:
     * |        |            |PIN reset, Watch dog, LVR reset BOD reset, ICE reset command and the software-chip
     * |        |            |reset function
     * |        |            |This register is the protected register, program this need an open lock sequence, write
     * |        |            |"59h","16h","88h" to address 0x5000_0100 to un-lock this bit. Reference the register
     * |        |            |REGWRPROT at address GCR_BA + 0x100
     */
    __IO uint32_t PORCR;

    /**
     * RESERVED2
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    uint32_t RESERVED2[2];

    /**
     * P0_MFP
     * ===================================================================================================
     * Offset: 0x30  P0 Multiple Function and Input Type Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |P0_MFP    |P0 multiple function Selection
     * |        |          |The pin function of P0 is depending on P0_MFP and P0_ALT.
     * |        |          |Refer to P0_ALT descriptions in detail.
     * |[8]     |P0_ALT0   |P0.0 alternate function Selection
     * |        |          |The pin function of P0.0 is depend on P0_MFP[0] and P0_ALT[0].
     * |        |          |P0_ALT[0]P0_MFP[0] = P0.0 Function
     * |        |          |00 = P0.0
     * |        |          |01 = AD0(EBI)
     * |        |          |10 = CTS1(UART1)
     * |        |          |11 = Reserved
     * |[9]     |P0_ALT1   |P0.1 alternate function Selection
     * |        |          |The pin function of P0.1 is depend on P0_MFP[1] and P0_ALT[1].
     * |        |          |P0_ALT[1] P0_MFP[1] = P0.1 Function
     * |        |          |00 = P0.1
     * |        |          |01 = AD1(EBI)
     * |        |          |10 = RTS1(UART1)
     * |        |          |11 = Reserved
     * |[10]    |P0_ALT2   |P0.2 alternate function Selection
     * |        |          |The pin function of P0.2 is depend on P0_MFP[2] and P0_ALT[2].
     * |        |          |P0_ALT[2] P0_MFP[2] = P0.2 Function
     * |        |          |00 = P0.2
     * |        |          |01 = AD2(EBI)
     * |        |          |10 = CTS0(UART0)
     * |        |          |11 = Reserved
     * |[11]    |P0_ALT3   |P0.3 alternate function Selection
     * |        |          |The pin function of P0.3 is depend on P0_MFP[3] and P0_ALT[3].
     * |        |          |P0_ALT[3] P0_MFP[3] = P0.3 Function
     * |        |          |00 = P0.3
     * |        |          |01 = AD3(EBI)
     * |        |          |10 = RTS0(UART0)
     * |        |          |11 = Reserved
     * |[12]    |P0_ALT4   |P0.4 alternate function Selection
     * |        |          |The pin function of P0.4 is depend on P0_MFP[4] and P0_ALT[4].
     * |        |          |P0_ALT[4] P0_MFP[4] = P0.4 Function
     * |        |          |00 = P0.4
     * |        |          |01 = AD4(EBI)
     * |        |          |10 = SPISS1(SPI1)
     * |        |          |11 = Reserved
     * |[13]    |P0_ALT5   |P0.5 alternate function Selection
     * |        |          |The pin function of P0.5 is depend on P0_MFP[5] and P0_ALT[5].
     * |        |          |P0_ALT[5] P0_MFP[5] = P0.5 Function
     * |        |          |00 = P0.5
     * |        |          |01 = AD5(EBI)
     * |        |          |10 = MOSI_1(SPI1)
     * |        |          |11 = Reserved
     * |[14]    |P0_ALT6   |P0.6 alternate function Selection
     * |        |          |The pin function of P0.6 is depend on P0_MFP[6] and P0_ALT[6].
     * |        |          |P0_ALT[6] P0_MFP[6] = P0.6 Function
     * |        |          |00 = P0.6
     * |        |          |01 = AD6(EBI)
     * |        |          |10 = MISO_1(SPI1)
     * |        |          |11 = Reserved
     * |[15]    |P0_ALT7   |P0.7 alternate function Selection
     * |        |          |The pin function of P0.7 is depend on P0_MFP[7] and P0_ALT[7].
     * |        |          |P0_ALT[7] P0_MFP[7] = P0.7 Function
     * |        |          |00 = P0.7
     * |        |          |01 = AD7(EBI)
     * |        |          |10 = SPICLK1(SPI1)
     * |        |          |11 = Reserved
     * |[23:16] |P0_TYPEn  |P0[7:0] input Schmitt Trigger function Enable
     * |        |          |1= P0[7:0] I/O input Schmitt Trigger function enable
     * |        |          |0= P0[7:0] I/O input Schmitt Trigger function disable
     */
    __IO uint32_t P0_MFP;

    /**
     * P1_MFP
     * ===================================================================================================
     * Offset: 0x34  P1 Multiple Function and Input Type Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |P1_MFP    |P1 multiple function Selection
     * |        |          |The pin function of P1 is depending on P1_MFP and P1_ALT.
     * |        |          |Refer to P1_ALT descriptions in detail.
     * |[8]     |P1_ALT0   |P1.0 alternate function Selection
     * |        |          |The pin function of P1.0 is depend on P1_MFP[0] and P1_ALT[0].
     * |        |          |P1_ALT[0] P1_MFP[0] = P1.0 Function
     * |        |          |00 = P1.0
     * |        |          |01 = AIN0(ADC)
     * |        |          |10 = T2(Timer2)
     * |        |          |11 = Reserved
     * |[9]     |P1_ALT1   |P1.1 alternate function Selection
     * |        |          |The pin function of P1.1 is depend on P1_MFP[1] and P1_ALT[1].
     * |        |          |P1_ALT[1] P1_MFP[1] = P1.1 Function
     * |        |          |00 = P1.1
     * |        |          |01 = AIN1(ADC)
     * |        |          |10 = T3(Timer3)
     * |        |          |11 = Reserved
     * |[10]    |P1_ALT2   |P1.2 alternate function Selection
     * |        |          |The pin function of P1.2 is depend on P1_MFP[2] and P1_ALT[2].
     * |        |          |P1_ALT[2] P1_MFP[2] = P1.2 Function
     * |        |          |00 = P1.2
     * |        |          |01 = AIN2(ADC)
     * |        |          |10 = RXD1(UART1)
     * |        |          |11 = Reserved
     * |[11]    |P1_ALT3   |P1.3 alternate function Selection
     * |        |          |The pin function of P1.3 is depend on P1_MFP[3] and P1_ALT[3].
     * |        |          |P1_ALT[3] P1_MFP[3] = P1.3 Function
     * |        |          |00 = P1.3
     * |        |          |01 = AIN3(ADC)
     * |        |          |10 = TXD1(UART1)
     * |        |          |11 = Reserved
     * |[12]    |P1_ALT4   |P1.4 alternate function Selection
     * |        |          |The pin function of P1.4 is depend on P1_MFP[4] and P1_ALT[4].
     * |        |          |P1_ALT[4] P1_MFP[4] = P1.4 Function
     * |        |          |00 = P1.4
     * |        |          |01 = AIN4(ADC)
     * |        |          |10 = SPISS0(SPI0)
     * |        |          |11 = Reserved
     * |[13]    |P1_ALT5   |P1.5 alternate function Selection
     * |        |          |The pin function of P1.5 is depend on P1_MFP[5] and P1_ALT[5].
     * |        |          |P1_ALT[5] P1_MFP[5] = P1.5 Function
     * |        |          |00 = P1.5
     * |        |          |01 = AIN5(ADC)
     * |        |          |10 = MOSI_0(SPI0)
     * |        |          |11 = Reserved
     * |[14]    |P1_ALT6   |P1.6 alternate function Selection
     * |        |          |The pin function of P1.6 is depend on P1_MFP[6] and P1_ALT[6].
     * |        |          |P1_ALT[6] P1_MFP[6] = P1.6 Function
     * |        |          |00 = P1.6
     * |        |          |01 = AIN6(ADC)
     * |        |          |10 = MISO_0(SPI0)
     * |        |          |11 = Reserved
     * |[15]    |P1_ALT7   |P1.7 alternate function Selection
     * |        |          |The pin function of P1.7 is depend on P1_MFP[7] and P1_ALT[7].
     * |        |          |P1_ALT[7] P1_MFP[7] = P1.7 Function
     * |        |          |00 = P1.7
     * |        |          |01 = AIN7(ADC)
     * |        |          |10 = SPICLK0(SPI0)
     * |        |          |11 = Reserved
     * |[23:16] |P1_TYPEn  |P1[7:0] input Schmitt Trigger function Enable
     * |        |          |1= P1[7:0] I/O input Schmitt Trigger function enable
     * |        |          |0= P1[7:0] I/O input Schmitt Trigger function disable
     */
    __IO uint32_t P1_MFP;

    /**
     * P2_MFP
     * ===================================================================================================
     * Offset: 0x38  P2 Multiple Function and Input Type Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |P2_MFP    |P2 multiple function Selection
     * |        |          |The pin function of P2 is depending on P2_MFP and P2_ALT.
     * |        |          |Refer to P2_ALT descriptions in detail.
     * |[8]     |P2_ALT0   |P2.0 alternate function Selection
     * |        |          |The pin function of P2.0 is depend on P2_MFP[0] and P2_ALT[0].
     * |        |          |P2_ALT[0] P2_MFP[0] = P2.0 Function
     * |        |          |00 = P2.0
     * |        |          |01 = AD8(EBI)
     * |        |          |10 = PWM0(PWM generator 0)
     * |        |          |11 = Reserved
     * |[9]     |P2_ALT1   |P2.1 alternate function Selection
     * |        |          |The pin function of P2.1 is depend on P2_MFP[1] and P2_ALT[1].
     * |        |          |P2_ALT[1] P2_MFP[1] = P2.1 Function
     * |        |          |00 = P2.1
     * |        |          |01 = AD9(EBI)
     * |        |          |10 = PWM1(PWM generator 0)
     * |        |          |11 = Reserved
     * |[10]    |P2_ALT2   |P2.2 alternate function Selection
     * |        |          |The pin function of P2.2 is depend on P2_MFP[2] and P2_ALT[2].
     * |        |          |P2_ALT[2] P2_MFP[2] = P2.2 Function
     * |        |          |00 = P2.2
     * |        |          |01 = AD10(EBI)
     * |        |          |10 = PWM2(PWM generator 2)
     * |        |          |11 = Reserved
     * |[11]    |P2_ALT3   |P2.3 alternate function Selection
     * |        |          |The pin function of P2.3 is depend on P2_MFP[3] and P2_ALT[3].
     * |        |          |P2_ALT[3] P2_MFP[3] = P2.3 Function
     * |        |          |00 = P2.3
     * |        |          |01 = AD11(EBI)
     * |        |          |10 = PWM3(PWM generator 2)
     * |        |          |11 = Reserved
     * |[12]    |P2_ALT4   |P2.4 alternate function Selection
     * |        |          |The pin function of P2.4 is depend on P2_MFP[4] and P2_ALT[4].
     * |        |          |P2_ALT[4] P2_MFP[4] = P0.4 Function
     * |        |          |00 = P0.4
     * |        |          |01 = AD12(EBI)
     * |        |          |10 = PWM4(PWM generator 4)
     * |        |          |11 = Reserved
     * |[13]    |P2_ALT5   |P2.5 alternate function Selection
     * |        |          |The pin function of P2.5 is depend on P2_MFP[5] and P2_ALT[5].
     * |        |          |P2_ALT[5] P2_MFP[5] = P2.5 Function
     * |        |          |00 = P2.5
     * |        |          |01 = AD13(EBI)
     * |        |          |10 = PWM5(PWM generator 4)
     * |        |          |11 = Reserved
     * |[14]    |P2_ALT6   |P2.6 alternate function Selection
     * |        |          |The pin function of P2.6 is depend on P2_MFP[6] and P2_ALT[6].
     * |        |          |P2_ALT[6] P2_MFP[6] = P2.6 Function
     * |        |          |00 = P2.6
     * |        |          |01 = AD14(EBI)
     * |        |          |10 = PWM6(PWM generator 6)
     * |        |          |11 = Reserved
     * |[15]    |P2_ALT7   |P2.7 alternate function Selection
     * |        |          |The pin function of P2.7 is depend on P2_MFP[7] and P2_ALT[7].
     * |        |          |P2_ALT[7] P2_MFP[7] = P2.7 Function
     * |        |          |00 = P2.7
     * |        |          |01 = AD15(EBI)
     * |        |          |10 = PWM7(PWM generator 6)
     * |        |          |11 = Reserved
     * |[23:16] |P2_TYPEn  |P2[7:0] input Schmitt Trigger function Enable
     * |        |          |1= P2[7:0] I/O input Schmitt Trigger function enable
     * |        |          |0= P2[7:0] I/O input Schmitt Trigger function disable
     */
    __IO uint32_t P2_MFP;

    /**
     * P3_MFP
     * ===================================================================================================
     * Offset: 0x3C  P3 Multiple Function and Input Type Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |P3_MFP    |P3 multiple function Selection
     * |        |          |The pin function of P3 is depending on P3_MFP and P3_ALT.
     * |        |          |Refer to P3_ALT descriptions in detail.
     * |[8]     |P3_ALT0   |P3.0 alternate function Selection
     * |        |          |The pin function of P3.0 is depend on P3_MFP[0] and P3_ALT[0].
     * |        |          |P3_ALT[0] P3_MFP[0] = P3.0 Function
     * |        |          |00 = P3.0
     * |        |          |01 = RXD(UART0)
     * |        |          |1x = Reserved
     * |[9]     |P3_ALT1   |P3.1 alternate function Selection
     * |        |          |The pin function of P3.1 is depend on P3_MFP[1] and P3_ALT[1].
     * |        |          |P3_ALT[1] P3_MFP[1] = P3.1 Function
     * |        |          |00 = P3.1
     * |        |          |01 = TXD(UART0)
     * |        |          |1x = Reserved
     * |[10]    |P3_ALT2   |P3.2 alternate function Selection
     * |        |          |The pin function of P3.2 is depend on P3_MFP[2] and P3_ALT[2].
     * |        |          |P3_ALT[2] P3_MFP[2] = P3.2 Function
     * |        |          |00 = P3.2
     * |        |          |01 = /INT0
     * |        |          |11 = Reserved
     * |[11]    |P3_ALT3   |P3.3 alternate function Selection
     * |        |          |The pin function of P3.3 is depend on P3_MFP[3] and P3_ALT[3].
     * |        |          |P3_ALT[3] P3_MFP[3] = P3.3 Function
     * |        |          |00 = P3.3
     * |        |          |01 = /INT1
     * |        |          |10 = MCLK(EBI)
     * |        |          |1x = Reserved
     * |[12]    |P3_ALT4   |P3.4 alternate function Selection
     * |        |          |The pin function of P3.4 is depend on P3_MFP[4] and P3_ALT[4].
     * |        |          |P3_ALT[4] P3_MFP[4] = P3.4 Function
     * |        |          |00 = P3.4
     * |        |          |01 = T0(Timer0)
     * |        |          |10 = SDA(I2C)
     * |        |          |11 = Reserved
     * |[13]    |P3_ALT5   |P3.5 alternate function Selection
     * |        |          |The pin function of P3.5 is depend on P3_MFP[5] and P3_ALT[5].
     * |        |          |P3_ALT[5] P3_MFP[5] = P3.5 Function
     * |        |          |00 = P3.5
     * |        |          |01 = T1(Timer1)
     * |        |          |10 = SCL(I2C)
     * |        |          |11 = Reserved
     * |[14]    |P3_ALT6   |P3.6 alternate function Selection
     * |        |          |The pin function of P3.6 is depend on P3_MFP[6] and P3_ALT[6].
     * |        |          |P3_ALT[6] P3_MFP[6] = P3.6 Function
     * |        |          |00 = P3.6
     * |        |          |01 = WR(EBI)
     * |        |          |10 = CKO(Clock Driver output)
     * |        |          |11 = Reserved
     * |[15]    |P3_ALT7   |P3.7 alternate function Selection
     * |        |          |The pin function of P3.7 is depend on P3_MFP[7] and P3_ALT[7].
     * |        |          |P3_ALT[7] P3_MFP[7] = P3.7 Function
     * |        |          |00 = P3.7
     * |        |          |01 = RD(EBI)
     * |        |          |1x = Reserved
     * |[23:16] |P3_TYPEn  |P3[7:0] input Schmitt Trigger function Enable
     * |        |          |1= P3[7:0] I/O input Schmitt Trigger function enable
     * |        |          |0= P3[7:0] I/O input Schmitt Trigger function disable
     */
    __IO uint32_t P3_MFP;

    /**
     * P4_MFP
     * ===================================================================================================
     * Offset: 0x40  P4 Multiple Function and Input Type Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |P4_MFP    |P4 multiple function Selection
     * |        |          |The pin function of P4 is depending on P4_MFP and P4_ALT.
     * |        |          |Refer to P4_ALT descriptions in detail.
     * |[8]     |P4_ALT0   |P4.0 alternate function Selection
     * |        |          |The pin function of P4.0 is depend on P4_MFP[0] and P4_ALT[0].
     * |        |          |P4_ALT[0] P4_MFP[0] = P4.0 Function
     * |        |          |00 = P4.0
     * |        |          |01 = PWM0(PWM generator 0)
     * |        |          |1x = Reserved
     * |[9]     |P4_ALT1   |P4.1 alternate function Selection
     * |        |          |The pin function of P4.1 is depend on P4_MFP[1] and P4_ALT[1].
     * |        |          |P4_ALT[1] P4_MFP[1] = P4.1 Function
     * |        |          |00 = P4.1
     * |        |          |01 = PWM1(PWM generator 0)
     * |        |          |1x = Reserved
     * |[10]    |P4_ALT2   |P4.2 alternate function Selection
     * |        |          |The pin function of P4.2 is depend on P4_MFP[2] and P4_ALT[2].
     * |        |          |P4_ALT[2] P4_MFP[2] = P4.2 Function
     * |        |          |00 = P4.2
     * |        |          |01 = PWM2(PWM generator 2)
     * |        |          |1x = Reserved
     * |[11]    |P4_ALT3   |P4.3 alternate function Selection
     * |        |          |The pin function of P4.3 is depend on P4_MFP[3] and P4_ALT[3].
     * |        |          |P4_ALT[3] P4_MFP[3] = P4.3 Function
     * |        |          |00 = P4.3
     * |        |          |01 = PWM3(PWM generator 2)
     * |        |          |1x = Reserved
     * |[12]    |P4_ALT4   |P4.4 alternate function Selection
     * |        |          |The pin function of P4.4 is depend on P4_MFP[4] and P4_ALT[4].
     * |        |          |P4_ALT[4] P4_MFP[4] = P4.4 Function
     * |        |          |00 = P4.4
     * |        |          |01 = /CS(EBI)
     * |        |          |1x = Reserved
     * |[13]    |P4_ALT5   |P4.5 alternate function Selection
     * |        |          |The pin function of P4.5 is depend on P4_MFP[5] and P4_ALT[5].
     * |        |          |P4_ALT[5] P4_MFP[5] = P4.5 Function
     * |        |          |00 = P4.5
     * |        |          |01 = ALE(EBI)
     * |        |          |1x = Reserved
     * |[14]    |P4_ALT6   |P4.6 alternate function Selection
     * |        |          |The pin function of P4.6 is depend on P4_MFP[6] and P4_ALT[6].
     * |        |          |P4_ALT[6] P4_MFP[6] = P4.6 Function
     * |        |          |00 = P4.6
     * |        |          |01 = ICE_CLK(ICE)
     * |        |          |1x = Reserved
     * |[15]    |P4_ALT7   |P4.7 alternate function Selection
     * |        |          |The pin function of P4.7 is depend on P4_MFP[7] and P4_ALT[7].
     * |        |          |P4_ALT[7] P4_MFP[7] = P4.7 Function
     * |        |          |00 = P4.7
     * |        |          |01 = ICE_DAT(ICE)
     * |        |          |1x = Reserved
     * |[23:16] |P4_TYPEn  |P4[7:0] input Schmitt Trigger function Enable
     * |        |          |1= P4[7:0] I/O input Schmitt Trigger function enable
     * |        |          |0= P4[7:0] I/O input Schmitt Trigger function disable
     */
    __IO uint32_t P4_MFP;

    /**
     * RESERVED3
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    uint32_t RESERVED3[47];

    /**
     * REGWRPROT
     * ===================================================================================================
     * Offset: 0x100 Register Write-Protection Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |REGWRPROT |Register Write-Protected Code (Write Only)
     * |        |          |Some write-protected registers have to be disabled the protected function by writing the
     * |        |          |sequence value "59h", "16h", "88h" to this field. After this sequence is completed, the
     * |        |          |REGPROTDIS bit will be set to 1 and write-protected registers can be normal write.
     * |[0]     |REGPROTDIS|Register Write-Protected Disable index (Read only)
     * |        |          |1 = Protection is disabled for writing protected registers
     * |        |          |0 = Protection is enabled for writing protected registers. Any write to the protected register is
     * |        |          |ignored.
     * |        |          |The Write-Protected registers list are below table:
     * |        |          |Registers Address Note
     * |        |          |IPRSTC1 0x5000_0008 None
     * |        |          |BODCR 0x5000_0018 None
     * |        |          |PORCR 0x5000_001C None
     * |        |          |PWRCON 0x5000_0200 bit[6] is not protected for power, wake-up interrupt clear
     * |        |          |APBCLK bit[0] 0x5000_0208 bit[0] is watch dog clock enable
     * |        |          |CLKSEL0 0x5000_0210 HCLK and CPU STCLK clock source select
     * |        |          |CLK_SEL1 bit[1:0] 0x5000_0214 Watch dog clock source select
     * |        |          |ISPCON 0x5000_C000 Flash ISP Control register
     * |        |          |WTCR 0x4000_4000 None
     * |        |          |FATCON 0x5000_C018 None
     */
    __IO uint32_t REGWRPROT;

} GCR_T;


/** @addtogroup GCR_CONST GCR Bit Field Definition
  Constant Definitions for GCR Controller
  @{
 */

/* GCR RSTSRC Bit Field Definitions */
#define SYS_RSTSRC_RSTS_CPU_Pos                 7                                       /*!< GCR RSTSRC: RSTS_CPU Position */
#define SYS_RSTSRC_RSTS_CPU_Msk                 (1ul << SYS_RSTSRC_RSTS_CPU_Pos)        /*!< GCR RSTSRC: RSTS_CPU Mask */

#define SYS_RSTSRC_RSTS_MCU_Pos                 5                                       /*!< GCR RSTSRC: RSTS_MCU Position */
#define SYS_RSTSRC_RSTS_MCU_Msk                 (1ul << SYS_RSTSRC_RSTS_MCU_Pos)        /*!< GCR RSTSRC: RSTS_MCU Mask */

#define SYS_RSTSRC_RSTS_BOD_Pos                 4                                       /*!< GCR RSTSRC: RSTS_BOD Position */
#define SYS_RSTSRC_RSTS_BOD_Msk                 (1ul << SYS_RSTSRC_RSTS_BOD_Pos)        /*!< GCR RSTSRC: RSTS_BOD Mask */

#define SYS_RSTSRC_RSTS_LVR_Pos                 3                                       /*!< GCR RSTSRC: RSTS_LVR Position */
#define SYS_RSTSRC_RSTS_LVR_Msk                 (1ul << SYS_RSTSRC_RSTS_LVR_Pos)        /*!< GCR RSTSRC: RSTS_LVR Mask */

#define SYS_RSTSRC_RSTS_WDT_Pos                 2                                       /*!< GCR RSTSRC: RSTS_WDT Position */
#define SYS_RSTSRC_RSTS_WDT_Msk                 (1ul << SYS_RSTSRC_RSTS_WDT_Pos)        /*!< GCR RSTSRC: RSTS_WDT Mask */

#define SYS_RSTSRC_RSTS_RESET_Pos               1                                       /*!< GCR RSTSRC: RSTS_RESET Position */
#define SYS_RSTSRC_RSTS_RESET_Msk               (1ul << SYS_RSTSRC_RSTS_RESET_Pos)      /*!< GCR RSTSRC: RSTS_RESET Mask */

#define SYS_RSTSRC_RSTS_POR_Pos                 0                                       /*!< GCR RSTSRC: RSTS_POR Position */
#define SYS_RSTSRC_RSTS_POR_Msk                 (1ul << SYS_RSTSRC_RSTS_POR_Pos)        /*!< GCR RSTSRC: RSTS_POR Mask */

/* GCR IPRSTC1 Bit Field Definitions */
#define SYS_IPRSTC1_HDIV_RST_Pos                4                                       /*!< GCR IPRSTC1: DIV_RST Position */
#define SYS_IPRSTC1_HDIV_RST_Msk                (1ul << SYS_IPRSTC1_HDIV_RST_Pos)        /*!< GCR IPRSTC1: DIV_RST Mask */

#define SYS_IPRSTC1_EBI_RST_Pos                 3                                       /*!< GCR IPRSTC1: EBI_RST Position */
#define SYS_IPRSTC1_EBI_RST_Msk                 (1ul << SYS_IPRSTC1_EBI_RST_Pos)        /*!< GCR IPRSTC1: EBI_RST Mask */

#define SYS_IPRSTC1_CPU_RST_Pos                 1                                       /*!< GCR IPRSTC1: CPU_RST Position */
#define SYS_IPRSTC1_CPU_RST_Msk                 (1ul << SYS_IPRSTC1_CPU_RST_Pos)        /*!< GCR IPRSTC1: CPU_RST Mask */

#define SYS_IPRSTC1_CHIP_RST_Pos                0                                       /*!< GCR IPRSTC1: CHIP_RST Position */
#define SYS_IPRSTC1_CHIP_RST_Msk                (1ul << SYS_IPRSTC1_CHIP_RST_Pos)       /*!< GCR IPRSTC1: CHIP_RST Mask */

/* GCR IPRSTC2 Bit Field Definitions */
#define SYS_IPRSTC2_ADC_RST_Pos                 28                                      /*!< GCR IPRSTC2: ADC_RST Position */
#define SYS_IPRSTC2_ADC_RST_Msk                 (1ul << SYS_IPRSTC2_ADC_RST_Pos)        /*!< GCR IPRSTC2: ADC_RST Mask */

#define SYS_IPRSTC2_ACMP23_RST_Pos              23                                      /*!< GCR IPRSTC2: ACMP23_RST Position */
#define SYS_IPRSTC2_ACMP23_RST_Msk              (1ul << SYS_IPRSTC2_ACMP23_RST_Pos)     /*!< GCR IPRSTC2: ACMP23_RST Mask */

#define SYS_IPRSTC2_ACMP01_RST_Pos              22                                      /*!< GCR IPRSTC2: ACMP01_RST Position */
#define SYS_IPRSTC2_ACMP01_RST_Msk              (1ul << SYS_IPRSTC2_ACMP01_RST_Pos)     /*!< GCR IPRSTC2: ACMP01_RST Mask */

#define SYS_IPRSTC2_PWM47_RST_Pos               21                                      /*!< GCR IPRSTC2: PWM47_RST Position */
#define SYS_IPRSTC2_PWM47_RST_Msk               (1ul << SYS_IPRSTC2_PWM47_RST_Pos)      /*!< GCR IPRSTC2: PWM47_RST Mask */

#define SYS_IPRSTC2_PWM03_RST_Pos               20                                      /*!< GCR IPRSTC2: PWM03_RST Position */
#define SYS_IPRSTC2_PWM03_RST_Msk               (1ul << SYS_IPRSTC2_PWM03_RST_Pos)      /*!< GCR IPRSTC2: PWM03_RST Mask */

#define SYS_IPRSTC2_UART1_RST_Pos               17                                      /*!< GCR IPRSTC2: UART1_RST Position */
#define SYS_IPRSTC2_UART1_RST_Msk               (1ul << SYS_IPRSTC2_UART1_RST_Pos)      /*!< GCR IPRSTC2: UART1_RST Mask */

#define SYS_IPRSTC2_UART0_RST_Pos               16                                      /*!< GCR IPRSTC2: UART0_RST Position */
#define SYS_IPRSTC2_UART0_RST_Msk               (1ul << SYS_IPRSTC2_UART0_RST_Pos)      /*!< GCR IPRSTC2: UART0_RST Mask */

#define SYS_IPRSTC2_SPI1_RST_Pos                13                                      /*!< GCR IPRSTC2: SPI1_RST Position */
#define SYS_IPRSTC2_SPI1_RST_Msk                (1ul << SYS_IPRSTC2_SPI1_RST_Pos)       /*!< GCR IPRSTC2: SPI1_RST Mask */

#define SYS_IPRSTC2_SPI0_RST_Pos                12                                      /*!< GCR IPRSTC2: SPI0_RST Position */
#define SYS_IPRSTC2_SPI0_RST_Msk                (1ul << SYS_IPRSTC2_SPI0_RST_Pos)       /*!< GCR IPRSTC2: SPI0_RST Mask */

#define SYS_IPRSTC2_I2C1_RST_Pos                9                                       /*!< GCR IPRSTC2: I2C1_RST Position */
#define SYS_IPRSTC2_I2C1_RST_Msk                (1ul << SYS_IPRSTC2_I2C1_RST_Pos)       /*!< GCR IPRSTC2: I2C1_RST Mask */

#define SYS_IPRSTC2_I2C0_RST_Pos                8                                       /*!< GCR IPRSTC2: I2C0_RST Position */
#define SYS_IPRSTC2_I2C0_RST_Msk                (1ul << SYS_IPRSTC2_I2C0_RST_Pos)       /*!< GCR IPRSTC2: I2C0_RST Mask */
#define SYS_IPRSTC2_I2C_RST_Pos                 8                                       /*!< GCR IPRSTC2: I2C_RST Position */
#define SYS_IPRSTC2_I2C_RST_Msk                 (1ul << SYS_IPRSTC2_I2C_RST_Pos)        /*!< GCR IPRSTC2: I2C_RST Mask */

#define SYS_IPRSTC2_TMR3_RST_Pos                5                                       /*!< GCR IPRSTC2: TMR3_RST Position */
#define SYS_IPRSTC2_TMR3_RST_Msk                (1ul << SYS_IPRSTC2_TMR3_RST_Pos)       /*!< GCR IPRSTC2: TMR3_RST Mask */

#define SYS_IPRSTC2_TMR2_RST_Pos                4                                       /*!< GCR IPRSTC2: TMR2_RST Position */
#define SYS_IPRSTC2_TMR2_RST_Msk                (1ul << SYS_IPRSTC2_TMR2_RST_Pos)       /*!< GCR IPRSTC2: TMR2_RST Mask */

#define SYS_IPRSTC2_TMR1_RST_Pos                3                                       /*!< GCR IPRSTC2: TMR1_RST Position */
#define SYS_IPRSTC2_TMR1_RST_Msk                (1ul << SYS_IPRSTC2_TMR1_RST_Pos)       /*!< GCR IPRSTC2: TMR1_RST Mask */

#define SYS_IPRSTC2_TMR0_RST_Pos                2                                       /*!< GCR IPRSTC2: TMR0_RST Position */
#define SYS_IPRSTC2_TMR0_RST_Msk                (1ul << SYS_IPRSTC2_TMR0_RST_Pos)       /*!< GCR IPRSTC2: TMR0_RST Mask */

#define SYS_IPRSTC2_GPIO_RST_Pos                1                                       /*!< GCR IPRSTC2: GPIO_RST Position */
#define SYS_IPRSTC2_GPIO_RST_Msk                (1ul << SYS_IPRSTC2_GPIO_RST_Pos)       /*!< GCR IPRSTC2: GPIO_RST Mask */

/* GCR BODCR Bit Field Definitions */
#define SYS_BODCR_LVR_EN_Pos                    7                                       /*!< GCR BODCR: LVR_EN Position */
#define SYS_BODCR_LVR_EN_Msk                    (1ul << SYS_BODCR_LVR_EN_Pos)           /*!< GCR BODCR: LVR_EN Mask */

#define SYS_BODCR_BOD_OUT_Pos                   6                                       /*!< GCR BODCR: BOD_OUT Position */
#define SYS_BODCR_BOD_OUT_Msk                   (1ul << SYS_BODCR_BOD_OUT_Pos)          /*!< GCR BODCR: BOD_OUT Mask */

#define SYS_BODCR_BOD_LPM_Pos                   5                                       /*!< GCR BODCR: BOD_LPM Position */
#define SYS_BODCR_BOD_LPM_Msk                   (1ul << SYS_BODCR_BOD_LPM_Pos)          /*!< GCR BODCR: BOD_LPM Mask */

#define SYS_BODCR_BOD_INTF_Pos                  4                                       /*!< GCR BODCR: BOD_INTF Position */
#define SYS_BODCR_BOD_INTF_Msk                  (1ul << SYS_BODCR_BOD_INTF_Pos)         /*!< GCR BODCR: BOD_INTF Mask */

#define SYS_BODCR_BOD_RSTEN_Pos                 3                                       /*!< GCR BODCR: BOD_RSTEN Position */
#define SYS_BODCR_BOD_RSTEN_Msk                 (1ul << SYS_BODCR_BOD_RSTEN_Pos)        /*!< GCR BODCR: BOD_RSTEN Mask */

#define SYS_BODCR_BOD_VL_Pos                    1                                       /*!< GCR BODCR: BOD_VL Position */
#define SYS_BODCR_BOD_VL_Msk                    (3ul << SYS_BODCR_BOD_VL_Pos)           /*!< GCR BODCR: BOD_VL Mask */

#define SYS_BODCR_BOD_EN_Pos                    0                                       /*!< GCR BODCR: BOD_EN Position */
#define SYS_BODCR_BOD_EN_Msk                    (1ul << SYS_BODCR_BOD_EN_Pos)           /*!< GCR BODCR: BOD_EN Mask */

/* GCR TEMPCR Bit Field Definitions */
#define SYS_TEMPCR_VTEMP_EN_Pos                 0                                       /*!< GCR TEMPCR: VTEMP_EN Position */
#define SYS_TEMPCR_VTEMP_EN_Msk                 (1ul << SYS_TEMPCR_VTEMP_EN_Pos)        /*!< GCR TEMPCR: VTEMP_EN Mask */

/* GCR PORCR Bit Field Definitions */
#define SYS_PORCR_POR_DIS_CODE_Pos              0                                       /*!< GCR PORCR: POR_DIS_CODE Position */
#define SYS_PORCR_POR_DIS_CODE_Msk              (0xFFFFul << SYS_PORCR_POR_DIS_CODE_Pos)/*!< GCR PORCR: POR_DIS_CODE Mask */

/* GCR P0_MFP Bit Field Definitions */
#define SYS_P0_MFP_P0_ALT1_Pos                  24                                      /*!< GCR P0_MFP: P0_ALT1 Position */
#define SYS_P0_MFP_P0_ALT1_Msk                  (3ul << SYS_P0_MFP_P0_ALT1_Pos)         /*!< GCR P0_MFP: P0_ALT1 Mask */

#define SYS_P0_MFP_P0_TYPE_Pos                  16                                      /*!< GCR P0_MFP: P0_TYPE Position */
#define SYS_P0_MFP_P0_TYPE_Msk                  (0xFFul << SYS_P0_MFP_P0_TYPE_Pos)      /*!< GCR P0_MFP: P0_TYPE Mask */

#define SYS_P0_MFP_P0_ALT_Pos                   8                                       /*!< GCR P0_MFP: P0_ALT Position */
#define SYS_P0_MFP_P0_ALT_Msk                   (0xFFul << SYS_P0_MFP_P0_ALT_Pos)       /*!< GCR P0_MFP: P0_ALT Mask */

#define SYS_P0_MFP_P0_MFP_Pos                   0                                       /*!< GCR P0_MFP: P0_MFP Position */
#define SYS_P0_MFP_P0_MFP_Msk                   (0xFFul << SYS_P0_MFP_P0_MFP_Pos)       /*!< GCR P0_MFP: P0_MFP Mask */

/* GCR P1_MFP Bit Field Definitions */
#define SYS_P1_MFP_P1_TYPE_Pos                  16                                      /*!< GCR P1_MFP: P1_TYPE Position */
#define SYS_P1_MFP_P1_TYPE_Msk                  (0xFFul << SYS_P1_MFP_P1_TYPE_Pos)      /*!< GCR P1_MFP: P1_TYPE Mask */

#define SYS_P1_MFP_P1_ALT_Pos                   8                                       /*!< GCR P1_MFP: P1_ALT Position */
#define SYS_P1_MFP_P1_ALT_Msk                   (0xFFul << SYS_P1_MFP_P1_ALT_Pos)       /*!< GCR P1_MFP: P1_ALT Mask */

#define SYS_P1_MFP_P1_MFP_Pos                   0                                       /*!< GCR P1_MFP: P1_MFP Position */
#define SYS_P1_MFP_P1_MFP_Msk                   (0xFFul << SYS_P1_MFP_P1_MFP_Pos)       /*!< GCR P1_MFP: P1_MFP Mask */

/* GCR P2_MFP Bit Field Definitions */
#define SYS_P2_MFP_P2_TYPE_Pos                  16                                      /*!< GCR P2_MFP: P2_TYPE Position */
#define SYS_P2_MFP_P2_TYPE_Msk                  (0xFFul << SYS_P2_MFP_P2_TYPE_Pos)      /*!< GCR P2_MFP: P2_TYPE Mask */

#define SYS_P2_MFP_P2_ALT_Pos                   8                                       /*!< GCR P2_MFP: P2_ALT Position */
#define SYS_P2_MFP_P2_ALT_Msk                   (0xFFul << SYS_P2_MFP_P2_ALT_Pos)       /*!< GCR P2_MFP: P2_ALT Mask */

#define SYS_P2_MFP_P2_MFP_Pos                   0                                       /*!< GCR P2_MFP: P2_MFP Position */
#define SYS_P2_MFP_P2_MFP_Msk                   (0xFFul << SYS_P2_MFP_P2_MFP_Pos)       /*!< GCR P2_MFP: P2_MFP Mask */

/* GCR P3_MFP Bit Field Definitions */
#define SYS_P3_MFP_P3_TYPE_Pos                  16                                      /*!< GCR P3_MFP: P3_TYPE Position */
#define SYS_P3_MFP_P3_TYPE_Msk                  (0xFFul << SYS_P3_MFP_P3_TYPE_Pos)      /*!< GCR P3_MFP: P3_TYPE Mask */

#define SYS_P3_MFP_P3_ALT_Pos                   8                                       /*!< GCR P3_MFP: P3_ALT Position */
#define SYS_P3_MFP_P3_ALT_Msk                   (0xFFul << SYS_P3_MFP_P3_ALT_Pos)       /*!< GCR P3_MFP: P3_ALT Mask */

#define SYS_P3_MFP_P3_MFP_Pos                   0                                       /*!< GCR P3_MFP: P3_MFP Position */
#define SYS_P3_MFP_P3_MFP_Msk                   (0xFFul << SYS_P3_MFP_P3_MFP_Pos)       /*!< GCR P3_MFP: P3_MFP Mask */

/* GCR P4_MFP Bit Field Definitions */
#define SYS_P4_MFP_P4_TYPE_Pos                  16                                      /*!< GCR P4_MFP: P4_TYPE Position */
#define SYS_P4_MFP_P4_TYPE_Msk                  (0xFFul << SYS_P4_MFP_P4_TYPE_Pos)      /*!< GCR P4_MFP: P4_TYPE Mask */

#define SYS_P4_MFP_P4_ALT_Pos                   8                                       /*!< GCR P4_MFP: P4_ALT Position */
#define SYS_P4_MFP_P4_ALT_Msk                   (0xFFul << SYS_P4_MFP_P4_ALT_Pos)       /*!< GCR P4_MFP: P4_ALT Mask */

#define SYS_P4_MFP_P4_MFP_Pos                   0                                       /*!< GCR P4_MFP: P4_MFP Position */
#define SYS_P4_MFP_P4_MFP_Msk                   (0xFFul << SYS_P4_MFP_P4_MFP_Pos)       /*!< GCR P4_MFP: P4_MFP Mask */

/* GCR REGWRPROT Bit Field Definitions */
#define SYS_REGWRPROT_REGWRPROT_Pos             0                                       /*!< GCR REGWRPROT: REGWRPROT Position */
#define SYS_REGWRPROT_REGWRPROT_Msk             (0xFFul << SYS_REGWRPROT_REGWRPROT_Pos) /*!< GCR REGWRPROT: REGWRPROT Mask */

#define SYS_REGWRPROT_REGPROTDIS_Pos            0                                       /*!< GCR REGWRPROT: REGPROTDIS Position */
#define SYS_REGWRPROT_REGPROTDIS_Msk            (1ul << SYS_REGWRPROT_REGPROTDIS_Pos)   /*!< GCR REGWRPROT: REGPROTDIS Mask */
/**@}*/ /* GCR_CONST */


typedef struct
{
    /**
     * IRQSRC
     * ===================================================================================================
     * Offset: 0x00-0x7C MCU IRQn(n=0~31) Interrupt Source Identity Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |INT_SRC   |Interrupt Source Identity
     * |        |          |IRQSRC[0].0 - BOD INT
     * |        |          |IRQSRC[0].1 - 0
     * |        |          |IRQSRC[0].2 - 0
     * |        |          |IRQSRC[1].0 - WDT INT
     * |        |          |IRQSRC[1].1 - 0
     * |        |          |IRQSRC[1].2 - 0
     * |        |          |IRQSRC[2].0 - EINT0, external interrupt 0 from P3.2
     * |        |          |IRQSRC[2].1 - 0
     * |        |          |IRQSRC[2].2 - 0
     * |        |          |IRQSRC[3].0 - EINT1, external interrupt 1 from P3.3
     * |        |          |IRQSRC[3].1 - 0
     * |        |          |IRQSRC[3].2 - 0
     * |        |          |IRQSRC[4].0 - P0 INT
     * |        |          |IRQSRC[4].1 - P1 INT
     * |        |          |IRQSRC[4].2 - 0
     * |        |          |IRQSRC[5].0 - P2 INT
     * |        |          |IRQSRC[5].1 - P3 INT
     * |        |          |IRQSRC[5].2 - P4 INT
     * |        |          |IRQSRC[6].0 - PWM0 INT
     * |        |          |IRQSRC[6].1 - PWM1 INT
     * |        |          |IRQSRC[6].2 - PWM2 INT
     * |        |          |IRQSRC[6].3 - PWM3 INT
     * |        |          |IRQSRC[7].0 - PWM4 INT
     * |        |          |IRQSRC[7].1 - PWM5 INT
     * |        |          |IRQSRC[7].2 - PWM6 INT
     * |        |          |IRQSRC[7].3 - PWM7 INT
     * |        |          |IRQSRC[8].0 - TIMER0 INT
     * |        |          |IRQSRC[8].1 - 0
     * |        |          |IRQSRC[8].2 - 0
     * |        |          |IRQSRC[9].0 - TIMER1 INT
     * |        |          |IRQSRC[9].1 - 0
     * |        |          |IRQSRC[9].2 - 0
     * |        |          |IRQSRC[10].0 - TIMER2 INT
     * |        |          |IRQSRC[10].1 - 0
     * |        |          |IRQSRC[10].2 - 0
     * |        |          |IRQSRC[11].0 - TIMER3 INT
     * |        |          |IRQSRC[11].1 - 0
     * |        |          |IRQSRC[11].2 - 0
     * |        |          |IRQSRC[12].0 - UART0 INT
     * |        |          |IRQSRC[12].1 - 0
     * |        |          |IRQSRC[12].2 - 0
     * |        |          |IRQSRC[13].0 - UART1 INT
     * |        |          |IRQSRC[13].1 - 0
     * |        |          |IRQSRC[13].2 - 0
     * |        |          |IRQSRC[14].0 - SPI0 INT
     * |        |          |IRQSRC[14].1 - 0
     * |        |          |IRQSRC[14].2 - 0
     * |        |          |IRQSRC[15].0 - SPI1 INT
     * |        |          |IRQSRC[15].1 - 0
     * |        |          |IRQSRC[15].2 - 0
     * |        |          |IRQSRC[16].0 - 0
     * |        |          |IRQSRC[16].1 - 0
     * |        |          |IRQSRC[16].2 - 0
     * |        |          |IRQSRC[17].0 - 0
     * |        |          |IRQSRC[17].1 - 0
     * |        |          |IRQSRC[17].2 - 0
     * |        |          |IRQSRC[18].0 - I2C0 INT
     * |        |          |IRQSRC[18].1 - 0
     * |        |          |IRQSRC[18].2 - 0
     * |        |          |IRQSRC[19].0 - I2C1 INT
     * |        |          |IRQSRC[19].1 - 0
     * |        |          |IRQSRC[19].2 - 0
     * |        |          |IRQSRC[20].0 - 0
     * |        |          |IRQSRC[20].1 - 0
     * |        |          |IRQSRC[20].2 - 0
     * |        |          |IRQSRC[21].0 - 0
     * |        |          |IRQSRC[21].1 - 0
     * |        |          |IRQSRC[21].2 - 0
     * |        |          |IRQSRC[22].0 - 0
     * |        |          |IRQSRC[22].1 - 0
     * |        |          |IRQSRC[22].2 - 0
     * |        |          |IRQSRC[23].0 - 0
     * |        |          |IRQSRC[23].1 - 0
     * |        |          |IRQSRC[23].2 - 0
     * |        |          |IRQSRC[24].0 - 0
     * |        |          |IRQSRC[24].1 - 0
     * |        |          |IRQSRC[24].2 - 0
     * |        |          |IRQSRC[25].0 - ACMP0 INT
     * |        |          |IRQSRC[25].1 - 0
     * |        |          |IRQSRC[25].2 - 0
     * |        |          |IRQSRC[26].0 - ACMP1 INT
     * |        |          |IRQSRC[26].1 - 0
     * |        |          |IRQSRC[26].2 - 0
     * |        |          |IRQSRC[27].0 - 0
     * |        |          |IRQSRC[27].1 - 0
     * |        |          |IRQSRC[27].2 - 0
     * |        |          |IRQSRC[28].0 - Power Down Wake up INT
     * |        |          |IRQSRC[28].1 - 0
     * |        |          |IRQSRC[28].2 - 0
     * |        |          |IRQSRC[29].0 - ADC INT
     * |        |          |IRQSRC[29].1 - 0
     * |        |          |IRQSRC[29].2 - 0
     * |        |          |IRQSRC[30].0 - 0
     * |        |          |IRQSRC[30].1 - 0
     * |        |          |IRQSRC[30].2 - 0
     * |        |          |IRQSRC[31].0 - 0
     * |        |          |IRQSRC[31].1 - 0
     * |        |          |IRQSRC[31].2 - 0
     */
    __I  uint32_t IRQSRC[32];

    /**
     * NMISEL
     * ===================================================================================================
     * Offset: 0x80 NMI Interrupt Source Select Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NMI_SEL   |NMI interrupt source selection
     * |        |          |The NMI interrupt to Cortex-M0 can be selected from one of the interrupt[31:0]
     * |        |          |The NMI_SEL bit[4:0] used to select the NMI interrupt source
     * |[8]     |NMI_EN    |NMI interrupt enable (write-protection bit)
     * |        |          |1 = Enable NMI interrupt
     * |        |          |0 = Disable NMI interrupt
     * |        |          |This bit is the protected bit.
     * |        |          |It means programming this needs to write "59h", "16h", "88h"to address 0x5000_0100 to disable register protection.
     * |        |          |Reference the register REGWRPROT at address GCR_BA+0x100
     */
    __IO uint32_t NMISEL;

    /**
     * MCUIRQ
     * ===================================================================================================
     * Offset: 0x84      MCU Interrupt Request Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MCU_IRQ   |MCU IRQ Source Register
     * |        |          |The MCU_IRQ collects all the interrupts from the peripherals and generates the synchronous interrupt to Cortex-M0 core.
     * |        |          |There are two modes to generate interrupt to Cortex-M0, the normal mode and test mode.
     * |        |          |The MCU_IRQ collects all interrupts from each peripheral and synchronizes them then interrupts the Cortex-M0.
     * |        |          |When the MCU_IRQ[n] is "0", set MCU_IRQ[n] "1" will generate an interrupt to Cortex_M0 NVIC[n].
     * |        |          |When the MCU_IRQ[n] is "1" (mean an interrupt is assert), set 1 to the MCU_IRQ[n] will clear the interrupt and set MCU_IRQ[n] "0" : no any effect
     */
    __IO uint32_t MCUIRQ;

} GCR_INT_T;

/** @addtogroup INT_CONST INT Bit Field Definition
  Constant Definitions for INT Controller
  @{
 */

/* INT NMI_SEL Bit Field Definitions */
#define INT_NMI_SEL_NMI_EN_Pos                  8                                       /*!< INT NMI_SEL: NMI_EN Position */
#define INT_NMI_SEL_NMI_EN_Msk                  (1ul << INT_NMI_SEL_NMI_EN_Pos)         /*!< INT NMI_SEL: NMI_EN Mask */

#define INT_NMI_SEL_NMI_SEL_Pos                 0                                       /*!< INT NMI_SEL: NMI_SEL Position */
#define INT_NMI_SEL_NMI_SEL_Msk                 (0x1Ful << INT_NMI_SEL_NMI_SEL_Pos)     /*!< INT NMI_SEL: NMI_SEL Mask */
/**@}*/ /* INT_CONST */


/**@}*/ /* GCR */


/*--------------------- General Purpose Input and Ouptut ---------------------*/
/** @addtogroup GPIO General Purpose Input and Ouptut(GPIO)
  Memory Mapped Structure for General Purpose I/O
  @{
 */
typedef struct
{
    /**
     * PMD
     * ===================================================================================================
     * Offset: 0x00  Port 0-4  I/O Mode Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PMD0      |P0 I/O Pin[0] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[0] pin is in INPUT mode.
     * |        |          |01 = P0[0] pin is in OUTPUT mode.
     * |        |          |10 = P0[0] pin is in Open-Drain mode.
     * |        |          |11 = P0[0] pin is in Quasi-bidirectional mode.
     * |[3:2]   |PMD1      |P0 I/O Pin[1] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[1] pin is in INPUT mode.
     * |        |          |01 = P0[1] pin is in OUTPUT mode.
     * |        |          |10 = P0[1] pin is in Open-Drain mode.
     * |        |          |11 = P0[1] pin is in Quasi-bidirectional mode.
     * |[5:4]   |PMD2      |P0 I/O Pin[2] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[2] pin is in INPUT mode.
     * |        |          |01 = P0[2] pin is in OUTPUT mode.
     * |        |          |10 = P0[2] pin is in Open-Drain mode.
     * |        |          |11 = P0[2] pin is in Quasi-bidirectional mode.
     * |[7:6]   |PMD3      |P0 I/O Pin[3] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[3] pin is in INPUT mode.
     * |        |          |01 = P0[3] pin is in OUTPUT mode.
     * |        |          |10 = P0[3] pin is in Open-Drain mode.
     * |        |          |11 = P0[3] pin is in Quasi-bidirectional mode.
     * |[9:8]   |PMD4      |P0 I/O Pin[4] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[4] pin is in INPUT mode.
     * |        |          |01 = P0[4] pin is in OUTPUT mode.
     * |        |          |10 = P0[4] pin is in Open-Drain mode.
     * |        |          |11 = P0[4] pin is in Quasi-bidirectional mode.
     * |[11:10] |PMD5      |P0 I/O Pin[5] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[5] pin is in INPUT mode.
     * |        |          |01 = P0[5] pin is in OUTPUT mode.
     * |        |          |10 = P0[5] pin is in Open-Drain mode.
     * |        |          |11 = P0[5] pin is in Quasi-bidirectional mode.
     * |[13:12] |PMD6      |P0 I/O Pin[6] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[6] pin is in INPUT mode.
     * |        |          |01 = P0[6] pin is in OUTPUT mode.
     * |        |          |10 = P0[6] pin is in Open-Drain mode.
     * |        |          |11 = P0[6] pin is in Quasi-bidirectional mode.
     * |[15:14] |PMD7      |P0 I/O Pin[7] Mode Control
     * |        |          |Determine each I/O type of P0 pins
     * |        |          |00 = P0[7] pin is in INPUT mode.
     * |        |          |01 = P0[7] pin is in OUTPUT mode.
     * |        |          |10 = P0[7] pin is in Open-Drain mode.
     * |        |          |11 = P0[7] pin is in Quasi-bidirectional mode.
     */
    __IO uint32_t  PMD;

    /**
     * OFFD
     * ===================================================================================================
     * Port 0-4 Digital Input Path Disable Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:16] |OFFD      |OFFD: P0 Pin OFF digital input path Enable
     * |        |          |1 = Disable IO digital input path (digital input tied to low)
     * |        |          |0 = Enable IO digital input path
     */
    __IO uint32_t  OFFD;

    /**
     * DOUT
     * ===================================================================================================
     * Port 0-4 Data Output Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DOUT0     |P0 Pin[0] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[0] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[0] will drive Low if the corresponding output mode enabling bit is set.
     * |[1]     |DOUT1     |P0 Pin[1] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[1] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[1] will drive Low if the corresponding output mode enabling bit is set.
     * |[2]     |DOUT2     |P0 Pin[2] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[2] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[2] will drive Low if the corresponding output mode enabling bit is set.
     * |[3]     |DOUT3     |P0 Pin[3] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[3] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[3] will drive Low if the corresponding output mode enabling bit is set.
     * |[4]     |DOUT4     |P0 Pin[4] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[4] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[4] will drive Low if the corresponding output mode enabling bit is set.
     * |[5]     |DOUT5     |P0 Pin[5] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[5] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[5] will drive Low if the corresponding output mode enabling bit is set.
     * |[6]     |DOUT6     |P0 Pin[6] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[6] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[6] will drive Low if the corresponding output mode enabling bit is set.
     * |[7]     |DOUT7     |P0 Pin[7] Output Value
     * |        |          |Each of these bits control the status of a P0 pin when the P0 pin is configures as output, open-drain
     * |        |          |and quasi-mode.
     * |        |          |1 = P0 Pin[7] will drive High if the corresponding output mode enabling bit is set.
     * |        |          |0 = P0 Pin[7] will drive Low if the corresponding output mode enabling bit is set.
     */
    __IO uint32_t  DOUT;

    /**
     * DMASK
     * ===================================================================================================
     * Port0-4 Data Output Write Mask
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DMASK0    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[0]. When set the
     * |        |          |DMASK bit[0] to "1", the corresponding DOUT0 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[0] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[0] bit is protected
     * |[1]     |DMASK1    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[1]. When set the
     * |        |          |DMASK bit[1] to "1", the corresponding DOUT1 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[1] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[1] bit is protected
     * |[2]     |DMASK2    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[2]. When set the
     * |        |          |DMASK bit[2] to "1", the corresponding DOUT2 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[2] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[2] bit is protected
     * |[3]     |DMASK3    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[3]. When set the
     * |        |          |DMASK bit[3] to "1", the corresponding DOUT3 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[3] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[3] bit is protected
     * |[4]     |DMASK4    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[4]. When set the
     * |        |          |DMASK bit[4] to "1", the corresponding DOUT4 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[4] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[4] bit is protected
     * |[5]     |DMASK5    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[6]. When set the
     * |        |          |DMASK bit[6] to "1", the corresponding DOUT6 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[6] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[6] bit is protected
     * |[6]     |DMASK6    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[6]. When set the
     * |        |          |DMASK bit[6] to "1", the corresponding DOUT6 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[6] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[6] bit is protected
     * |[7]     |DMASK7    |P0 Data Output Write Mask
     * |        |          |These bits are used to protect the corresponding register of P0_DOUT bit[7]. When set the
     * |        |          |DMASK bit[7] to "1", the corresponding DOUT7 bit is protected. The write signal is masked, write
     * |        |          |data to the protect bit is ignored
     * |        |          |0 = The corresponding P0_DOUT[7] bit can be updated
     * |        |          |1 = The corresponding P0_DOUT[7] bit is protected
     */
    __IO uint32_t  DMASK;

    /**
     * PIN;
     * ===================================================================================================
     * Port 0-4 Pin Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PIN0      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[0].
     * |[1]     |PIN1      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[1].
     * |[2]     |PIN2      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[2].
     * |[3]     |PIN3      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[3].
     * |[4]     |PIN4      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[4].
     * |[5]     |PIN5      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[5].
     * |[6]     |PIN6      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[6].
     * |[7]     |PIN7      |P0 Pin Values
     * |        |          |The value read from each of these bit reflects the actual status of the respective P0 Pin[7].
     */
    __IO uint32_t  PIN;

    /**
     * DBEN
     * ===================================================================================================
     * Port 0-4 De-bounce Enable
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DBEN0     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[0] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[0] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[0] de-bounce function is disabled
     * |        |          |1 = The bit[0] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[1]     |DBEN1     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[1] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[1] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[1] de-bounce function is disabled
     * |        |          |1 = The bit[1] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[2]     |DBEN2     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[2] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[2] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[2] de-bounce function is disabled
     * |        |          |1 = The bit[2] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[3]     |DBEN3     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[3] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[3] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[3] de-bounce function is disabled
     * |        |          |1 = The bit[3] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[4]     |DBEN4     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[4] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[4] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[4] de-bounce function is disabled
     * |        |          |1 = The bit[4] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[5]     |DBEN5     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[5] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[5] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[5] de-bounce function is disabled
     * |        |          |1 = The bit[5] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[6]     |DBEN6     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[6] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[6] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[6] de-bounce function is disabled
     * |        |          |1 = The bit[6] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     * |[7]     |DBEN7     |P0 Input Signal De-bounce Enable
     * |        |          |DBEN[7] used to enable the de-bounce function for each corresponding bit. if the input signal pulse
     * |        |          |width can't be sampled by continuous two de-bounce sample cycle. The input signal transition is seen
     * |        |          |as the signal bounce and will not trigger the interrupt.
     * |        |          |The DBEN[7] is used for "edge-trigger" interrupt only, and ignored for "level trigger" interrupt
     * |        |          |0 = The bit[7] de-bounce function is disabled
     * |        |          |1 = The bit[7] de-bounce function is enabled
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered,
     * |        |          |the de-bounce enable bit is ignored.
     */
    __IO uint32_t  DBEN;

    /**
     * IMD
     * ===================================================================================================
     * Port 0-4 Interrupt Mode Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IMD0      |Port 0 Interrupt Mode Control
     * |        |          |IMD[0] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[1]     |IMD1      |Port 0 Interrupt Mode Control
     * |        |          |IMD[1] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[2]     |IMD2      |Port 0 Interrupt Mode Control
     * |        |          |IMD[2] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[3]     |IMD3      |Port 0 Interrupt Mode Control
     * |        |          |IMD[3] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[4]     |IMD4      |Port 0 Interrupt Mode Control
     * |        |          |IMD[4] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[5]     |IMD5      |Port 0 Interrupt Mode Control
     * |        |          |IMD[5] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[6]     |IMD6      |Port 0 Interrupt Mode Control
     * |        |          |IMD[6] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     * |[7]     |IMD7      |Port 0 Interrupt Mode Control
     * |        |          |IMD[7] used to control the interrupt is by level trigger or by edge trigger. If the interrupt is by edge
     * |        |          |trigger, the trigger souce is control de-bounce. If the interrupt is by level trigger, the input source is
     * |        |          |sampled by one clock and the generate the interrupt
     * |        |          |0 = Edge trigger interrupt
     * |        |          |1 = Level trigger interrupt
     * |        |          |if set pin as the level trigger interrupt, then only one level can be set on the registers P0_IEN.
     * |        |          |if set both the level to trigger interrupt, the setting is ignored and no interrupt will occur.
     * |        |          |The de-bounce function is valid for edge triggered interrupt. if the interrupt mode is level triggered, the
     * |        |          |de-bounce enable bit is ignored.
     */
    __IO uint32_t  IMD;

    /**
     * IEN
     * ===================================================================================================
     * Port 0-4 Interrupt Enable Control
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IF_EN0    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[0] used to enable the interrupt for each of the corresponding input P0[0]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[0] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[0] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[0] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[0] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[0] state low-level or high-to-low change interrupt
     * |[1]     |IF_EN1    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[1] used to enable the interrupt for each of the corresponding input P0[1]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[1] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[1] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[1] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[1] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[1] state low-level or high-to-low change interrupt
     * |[2]     |IF_EN2    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[2] used to enable the interrupt for each of the corresponding input P0[2]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[2] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[2] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[2] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[2] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[2] state low-level or high-to-low change interrupt
     * |[3]     |IF_EN3    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[3] used to enable the interrupt for each of the corresponding input P0[3]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[3] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[3] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[3] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[3] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[3] state low-level or high-to-low change interrupt
     * |[4]     |IF_EN4    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[4] used to enable the interrupt for each of the corresponding input P0[4]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[4] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[4] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[4] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[4] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[4] state low-level or high-to-low change interrupt
     * |[5]     |IF_EN5    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[5] used to enable the interrupt for each of the corresponding input P0[5]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[5] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[5] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[5] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[5] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[5] state low-level or high-to-low change interrupt
     * |[6]     |IF_EN6    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[6] used to enable the interrupt for each of the corresponding input P0[6]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[6] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[6] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[6] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[6] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[6] state low-level or high-to-low change interrupt
     * |[7]     |IF_EN7    |Port0 Interrupt Enable by Input Falling Edge or Input Level Low
     * |        |          |IF_EN[7] used to enable the interrupt for each of the corresponding input P0[7]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IF_EN[7] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[7] state at level "low" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[7] state change from "high-to-low" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[7] state low-level or high-to-low change interrupt
     * |        |          |0 = Disable the P0[7] state low-level or high-to-low change interrupt
     * |[16]    |IR_EN0    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[0] used to enable the interrupt for each of the corresponding input P0[0]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[0] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[0] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[0] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[0] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[0] level-high or low-to-high interrupt
     * |[17]    |IR_EN1    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[1] used to enable the interrupt for each of the corresponding input P0[1]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[1] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[1] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[1] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[1] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[1] level-high or low-to-high interrupt
     * |[18]    |IR_EN2    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[2] used to enable the interrupt for each of the corresponding input P0[2]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[2] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[2] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[2] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[2] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[2] level-high or low-to-high interrupt
     * |[19]    |IR_EN3    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[3] used to enable the interrupt for each of the corresponding input P0[3]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[3] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[3] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[3] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[3] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[3] level-high or low-to-high interrupt
     * |[20]    |IR_EN4    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[4] used to enable the interrupt for each of the corresponding input P0[4]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[4] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[4] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[4] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[4] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[4] level-high or low-to-high interrupt
     * |[21]    |IR_EN5    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[5] used to enable the interrupt for each of the corresponding input P0[5]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[5] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[5] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[5] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[5] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[5] level-high or low-to-high interrupt
     * |[22]    |IR_EN6    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[6] used to enable the interrupt for each of the corresponding input P0[6]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[6] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[6] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[6] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[6] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[6] level-high or low-to-high interrupt
     * |[23]    |IR_EN7    |Port 0 Interrupt Enable by Input Rising Edge or Input Level High
     * |        |          |IR_EN[7] used to enable the interrupt for each of the corresponding input P0[7]. Set bit "1" also
     * |        |          |enable the pin wakeup function.
     * |        |          |When set the IR_EN[7] bit "1":
     * |        |          |If the interrupt is level mode trigger, the input P0[7] state at level "high" will generate the interrupt.
     * |        |          |If the interrupt is edge mode trigger, the input P0[7] state change from "low-to-high" will generate
     * |        |          |the interrupt.
     * |        |          |1 = Enable the P0[7] level-high or low-to-high interrupt
     * |        |          |0 = Disable the P0[7] level-high or low-to-high interrupt
     */
    __IO uint32_t  IEN;

    /**
     * ISRC
     * ===================================================================================================
     * Port 0-4 Interrupt Trigger Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISRC0     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[0] generate an interrupt
     * |        |          |0 = No interrupt at P0[0]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[1]     |ISRC1     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[1] generate an interrupt
     * |        |          |0 = No interrupt at P0[1]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[2]     |ISRC2     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[2] generate an interrupt
     * |        |          |0 = No interrupt at P0[2]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[3]     |ISRC3     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[3] generate an interrupt
     * |        |          |0 = No interrupt at P0[3]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[4]     |ISRC4     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[4] generate an interrupt
     * |        |          |0 = No interrupt at P0[4]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[5]     |ISRC5     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[5] generate an interrupt
     * |        |          |0 = No interrupt at P0[5]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[6]     |ISRC6     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[6] generate an interrupt
     * |        |          |0 = No interrupt at P0[6]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     * |[7]     |ISRC7     |Port 0 Interrupt Trigger Source Indicator
     * |        |          |Read:
     * |        |          |1 = Indicates P0[7] generate an interrupt
     * |        |          |0 = No interrupt at P0[7]
     * |        |          |Write:
     * |        |          |1 = Clear the correspond pending interrupt
     * |        |          |0 = No action
     */
    __IO uint32_t  ISRC;
} GPIO_T;

typedef struct
{
    /**
     * DBNCECON
     * ===================================================================================================
     * Offset: 0x180 Interrupt De-bounce Cycle Control
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DBCLKSEL  |De-bounce sampling cycle selection
     * |        |          |DBCLKSEL
     * |        |          |Description
     * |        |          |0 = Sample interrupt input once per 1 clocks
     * |        |          |1 = Sample interrupt input once per 2 clocks
     * |        |          |2 = Sample interrupt input once per 4 clocks
     * |        |          |3 = Sample interrupt input once per 8 clocks
     * |        |          |4 = Sample interrupt input once per 16 clocks
     * |        |          |5 = Sample interrupt input once per 32 clocks
     * |        |          |6 = Sample interrupt input once per 64 clocks
     * |        |          |7 = Sample interrupt input once per 128 clocks
     * |        |          |8 = Sample interrupt input once per 256 clocks
     * |        |          |9 = Sample interrupt input once per 2*256 clocks
     * |        |          |10 = Sample interrupt input once per 4*256clocks
     * |        |          |11 = Sample interrupt input once per 8*256 clocks
     * |        |          |12 = Sample interrupt input once per 16*256 clocks
     * |        |          |13 = Sample interrupt input once per 32*256 clocks
     * |        |          |14 = Sample interrupt input once per 64*256 clocks
     * |        |          |15 = Sample interrupt input once per 128*256 clocks
     * |[4]     |DBCLKSRC  |De-bounce counter clock source select
     * |        |          |1 = De-bounce counter clock source is the internal 10KHz clock
     * |        |          |0 = De-bounce counter clock source is the HCLK
     * |[5]     |ICLK_ON   |Interrupt clock On mode
     * |        |          |Set this bit "0" will disable the interrupt generate circuit clock, if the pin[n] interrupt is disabled
     * |        |          |0 = disable the clock if the P0/1/2/3/4[n] interrupt is disabled
     * |        |          |1 = interrupt generated circuit clock always enable
     * |        |          |n=0~7
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t  DBNCECON;
} GPIO_DBNCECON_T;


/** @addtogroup GPIO_CONST GPIO Bit Field Definition
  Constant Definitions for GPIO Controller
  @{
 */

/* GPIO PMD Bit Field Definitions */
#define GPIO_PMD_PMD7_Pos           14                                          /*!< GPIO PMD: PMD7 Position */
#define GPIO_PMD_PMD7_Msk           (0x3ul << GPIO_PMD_PMD7_Pos)                /*!< GPIO PMD: PMD7 Mask */

#define GPIO_PMD_PMD6_Pos           12                                          /*!< GPIO PMD: PMD6 Position */
#define GPIO_PMD_PMD6_Msk           (0x3ul << GPIO_PMD_PMD6_Pos)                /*!< GPIO PMD: PMD6 Mask */

#define GPIO_PMD_PMD5_Pos           10                                          /*!< GPIO PMD: PMD5 Position */
#define GPIO_PMD_PMD5_Msk           (0x3ul << GPIO_PMD_PMD5_Pos)                /*!< GPIO PMD: PMD5 Mask */

#define GPIO_PMD_PMD4_Pos           8                                           /*!< GPIO PMD: PMD4 Position */
#define GPIO_PMD_PMD4_Msk           (0x3ul << GPIO_PMD_PMD4_Pos)                /*!< GPIO PMD: PMD4 Mask */

#define GPIO_PMD_PMD3_Pos           6                                           /*!< GPIO PMD: PMD3 Position */
#define GPIO_PMD_PMD3_Msk           (0x3ul << GPIO_PMD_PMD3_Pos)                /*!< GPIO PMD: PMD3 Mask */

#define GPIO_PMD_PMD2_Pos           4                                           /*!< GPIO PMD: PMD2 Position */
#define GPIO_PMD_PMD2_Msk           (0x3ul << GPIO_PMD_PMD2_Pos)                /*!< GPIO PMD: PMD2 Mask */

#define GPIO_PMD_PMD1_Pos           2                                           /*!< GPIO PMD: PMD1 Position */
#define GPIO_PMD_PMD1_Msk           (0x3ul << GPIO_PMD_PMD1_Pos)                /*!< GPIO PMD: PMD1 Mask */

#define GPIO_PMD_PMD0_Pos           0                                           /*!< GPIO PMD: PMD0 Position */
#define GPIO_PMD_PMD0_Msk           (0x3ul << GPIO_PMD_PMD0_Pos)                /*!< GPIO PMD: PMD0 Mask */

/* GPIO OFFD Bit Field Definitions */
#define GPIO_OFFD_OFFD_Pos          16                                          /*!< GPIO OFFD: OFFD Position */
#define GPIO_OFFD_OFFD_Msk          (0xFFul << GPIO_OFFD_OFFD_Pos)              /*!< GPIO OFFD: OFFD Mask */

/* GPIO DOUT Bit Field Definitions */
#define GPIO_DOUT_DOUT_Pos          0                                           /*!< GPIO DOUT: DOUT Position */
#define GPIO_DOUT_DOUT_Msk          (0xFFul << GPIO_DOUT_DOUT_Pos)              /*!< GPIO DOUT: DOUT Mask */

/* GPIO DMASK Bit Field Definitions */
#define GPIO_DMASK_DMASK_Pos        0                                           /*!< GPIO DMASK: DMASK Position */
#define GPIO_DMASK_DMASK_Msk        (0xFFul << GPIO_DMASK_DMASK_Pos)            /*!< GPIO DMASK: DMASK Mask */

/* GPIO PIN Bit Field Definitions */
#define GPIO_PIN_PIN_Pos            0                                           /*!< GPIO PIN: PIN Position */
#define GPIO_PIN_PIN_Msk            (0xFFul << GPIO_PIN_PIN_Pos)                /*!< GPIO PIN: PIN Mask */

/* GPIO DBEN Bit Field Definitions */
#define GPIO_DBEN_DBEN_Pos          0                                           /*!< GPIO DBEN: DBEN Position */
#define GPIO_DBEN_DBEN_Msk          (0xFFul << GPIO_DBEN_DBEN_Pos)              /*!< GPIO DBEN: DBEN Mask */

/* GPIO IMD Bit Field Definitions */
#define GPIO_IMD_IMD_Pos            0                                           /*!< GPIO IMD: IMD Position */
#define GPIO_IMD_IMD_Msk            (0xFFul << GPIO_IMD_IMD_Pos)                /*!< GPIO IMD: IMD Mask */

/* GPIO IEN Bit Field Definitions */
#define GPIO_IEN_IR_EN_Pos          16                                          /*!< GPIO IEN: IR_EN Position */
#define GPIO_IEN_IR_EN_Msk          (0xFFul << GPIO_IEN_IR_EN_Pos)              /*!< GPIO IEN: IR_EN Mask */

#define GPIO_IEN_IF_EN_Pos          0                                           /*!< GPIO IEN: IF_EN Position */
#define GPIO_IEN_IF_EN_Msk          (0xFFul << GPIO_IEN_IF_EN_Pos)              /*!< GPIO IEN: IF_EN Mask */

/* GPIO ISRC Bit Field Definitions */
#define GPIO_ISRC_ISRC_Pos          0                                           /*!< GPIO ISRC: ISRC Position */
#define GPIO_ISRC_ISRC_Msk          (0xFFul << GPIO_ISRC_ISRC_Pos)              /*!< GPIO ISRC: ISRC Mask */

/* GPIO DBNCECON Bit Field Definitions */
#define GPIO_DBNCECON_ICLK_ON_Pos   5                                           /*!< GPIO DBNCECON: ICLK_ON  Position */
#define GPIO_DBNCECON_ICLK_ON_Msk   (1ul << GPIO_DBNCECON_ICLK_ON_Pos)          /*!< GPIO DBNCECON: ICLK_ON  Mask */

#define GPIO_DBNCECON_DBCLKSRC_Pos  4                                           /*!< GPIO DBNCECON: DBCLKSRC Position */
#define GPIO_DBNCECON_DBCLKSRC_Msk  (1ul << GPIO_DBNCECON_DBCLKSRC_Pos)         /*!< GPIO DBNCECON: DBCLKSRC Mask */

#define GPIO_DBNCECON_DBCLKSEL_Pos  0                                           /*!< GPIO DBNCECON: DBCLKSEL Position */
#define GPIO_DBNCECON_DBCLKSEL_Msk  (0xFul << GPIO_DBNCECON_DBCLKSEL_Pos)       /*!< GPIO DBNCECON: DBCLKSEL Mask */
/**@}*/ /* GPIO_CONST */
/**@}*/ /* GPIO */


/*------------------------------ I2C Controller ------------------------------*/

/** @addtogroup I2C I2C Controller(I2C)
  Memory Mapped Structure for I2C Serial Interface Controller
  @{
 */
typedef struct
{
    /**
     * I2CON
     * ===================================================================================================
     * Offset: 0x00  I2C Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |AA        |Assert Acknowledge control bit.
     * |        |          |When AA=1 prior to address or data received, an acknowledged (low level to SDA) will be returned during
     * |        |          |the acknowledge clock pulse on the SCL line when 1.) A slave is acknowledging the address sent from
     * |        |          |master, 2.) The receiver devices are acknowledging the data sent by transmitter. When AA=0 prior to
     * |        |          |address or data received, a Not acknowledged (high level to SDA) will be returned during the acknowledge
     * |        |          |clock pulse on the SCL line.
     * |[3]     |SI        |I2C Interrupt Flag.
     * |        |          |When a new SIO state is present in the I2CSTATUS register, the SI flag is set by hardware, and if bit EI
     * |        |          |(I2CON [7]) is set, the I2C interrupt is requested. SI must be cleared by software. Clear SI is by writing one
     * |        |          |to this bit.
     * |[4]     |STO       |I2C STOP Flag.
     * |        |          |In master mode, setting STO to transmit a STOP condition to bus then I2C hardware will check the bus
     * |        |          |condition if a STOP condition is detected this flag will be cleared by hardware automatically.
     * |        |          |In a slave mode, setting STO resets I2C hardware to the defined "not addressed" slave mode. This means
     * |        |          |it is NO LONGER in the slave receiver mode to receive data from the master transmit device.
     * |[5]     |STA       |I2C START Flag.
     * |        |          |Setting STA to logic 1 to enter master mode, the I2C hardware sends a START or repeat START condition
     * |        |          |to bus when the bus is free.
     * |[6]     |ENSI      |I2C controller is enabled/disable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |Set to enable I2C serial function block. When ENS=1 the I2C serial function enables. The multi-function
     * |        |          |pin function of SDA and SCL must set to I2C function first.
     * |[7]     |EI        |Enable interrupt.
     * |        |          |1 = Enable I2C interrupt.
     * |        |          |0 = Disable I2C interrupt.
     */
    __IO uint32_t I2CON;

    /**
     * I2CADDR0
     * ===================================================================================================
     * Offset: 0x04  I2C Slave Address Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = Disable General Call Function.
     * |        |          |1 = Enable General Call Function.
     * |[7:1]   |I2CADDR   |I2C Address Register
     * |        |          |The content of this register is irrelevant when I2C is in master mode. In the slave mode, the seven
     * |        |          |most significant bits must be loaded with the MCU's own address. The I2C hardware will react if
     * |        |          |either of the address is matched.
     */
    __IO uint32_t I2CADDR0;

    /**
     * I2CDAT
     * ===================================================================================================
     * Offset: 0x08  I2C Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |I2CDAT    |I2C Data Register
     * |        |          |Bit[7:0] is located with the 8-bit transferred data of I2C serial port.
     */
    __IO uint32_t I2CDAT;

    /**
     * I2CSTATUS
     * ===================================================================================================
     * Offset: 0x0C  I2C Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |I2CSTATUS |I2C Status Register
     * |        |          |The status register of I2C:
     * |        |          |The three least significant bits are always 0. The five most significant bits contain the status code.
     * |        |          |There are 26 possible status codes. When I2STATUS contains F8H, no serial interrupt is
     * |        |          |requested. All other I2STATUS values correspond to defined I2C states. When each of these
     * |        |          |states is entered, a status interrupt is requested (SI = 1). A valid status code is present in
     * |        |          |I2STATUS one machine cycle after SI is set by hardware and is still present one machine cycle
     * |        |          |after SI has been reset by software. In addition, states 00H stands for a Bus Error. A Bus Error
     * |        |          |occurs when a START or STOP condition is present at an illegal position in the formation frame.
     * |        |          |Example of illegal position are during the serial transfer of an address byte, a data byte or an
     * |        |          |acknowledge bit.
     */
    __I  uint32_t I2CSTATUS;

    /**
     * I2CLK
     * ===================================================================================================
     * Offset: 0x10  I2C Clock Divided Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |I2CLK     |I2C clock divided Register
     * |        |          |The I2C clock rate bits: Data Baud Rate of I2C = PCLK /(4x(I2CLK+1)).
     */
    __IO uint32_t I2CLK;

    /**
     * I2CTOC
     * ===================================================================================================
     * Offset: 0x14  I2C Time-Out Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TIF       |Time-Out flag.
     * |        |          |1 = Time-Out falg is set by H/W. It can interrupt CPU.
     * |        |          |0 = S/W can clear the flag.
     * |[1]     |DIV4      |Time-Out counter input clock is divider by 4
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |When Enable, The time-Out period is prolong 4 times.
     * |[2]     |ENTI      |Time-out counter is enabled/disable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |When Enable, the 14 bit time-out counter will start counting when SI is clear. Setting flag SI to high will
     * |        |          |reset counter and re-start up counting after SI is cleared.
     */
    __IO uint32_t I2CTOC;

    /**
     * I2CADDR1
     * ===================================================================================================
     * Offset: 0x18  I2C Slave Address Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = Disable General Call Function.
     * |        |          |1 = Enable General Call Function.
     * |[7:1]   |I2CADDR   |I2C Address Register
     * |        |          |The content of this register is irrelevant when I2C is in master mode. In the slave mode, the seven
     * |        |          |most significant bits must be loaded with the MCU's own address. The I2C hardware will react if
     * |        |          |either of the address is matched.
     */
    __IO uint32_t I2CADDR1;

    /**
     * I2CADDR2
     * ===================================================================================================
     * Offset: 0x1C  I2C Slave Address Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = Disable General Call Function.
     * |        |          |1 = Enable General Call Function.
     * |[7:1]   |I2CADDR   |I2C Address Register
     * |        |          |The content of this register is irrelevant when I2C is in master mode. In the slave mode, the seven
     * |        |          |most significant bits must be loaded with the MCU's own address. The I2C hardware will react if
     * |        |          |either of the address is matched.
     */
    __IO uint32_t I2CADDR2;

    /**
     * I2CADDR3
     * ===================================================================================================
     * Offset: 0x20  I2C Slave Address Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = Disable General Call Function.
     * |        |          |1 = Enable General Call Function.
     * |[7:1]   |I2CADDR   |I2C Address Register
     * |        |          |The content of this register is irrelevant when I2C is in master mode. In the slave mode, the seven
     * |        |          |most significant bits must be loaded with the MCU's own address. The I2C hardware will react if
     * |        |          |either of the address is matched.
     */
    __IO uint32_t I2CADDR3;

    /**
     * I2CADM0
     * ===================================================================================================
     * Offset: 0x24  I2C Slave Address Mask Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |I2ADMx    |I2C Address Mask register
     * |        |          |1 = Mask enable (the received corresponding address bit is don't care.)
     * |        |          |0 = Mask disable (the received corresponding register bit should be exact the same as
     * |        |          |address register.)
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
     * |        |          |When the bit in the address mask register is set to one, it means the received
     * |        |          |corresponding address bit is don't-care. If the bit is set to zero, that means the received
     * |        |          |corresponding register bit should be exact the same as address register.
     */
    __IO uint32_t I2CADM0;

    /**
     * I2CADM1
     * ===================================================================================================
     * Offset: 0x28  I2C Slave Address Mask Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |I2ADMx    |I2C Address Mask register
     * |        |          |1 = Mask enable (the received corresponding address bit is don't care.)
     * |        |          |0 = Mask disable (the received corresponding register bit should be exact the same as
     * |        |          |address register.)
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
     * |        |          |When the bit in the address mask register is set to one, it means the received
     * |        |          |corresponding address bit is don't-care. If the bit is set to zero, that means the received
     * |        |          |corresponding register bit should be exact the same as address register.
     */
    __IO uint32_t I2CADM1;

    /**
     * I2CADM2
     * ===================================================================================================
     * Offset: 0x2C  I2C Slave Address Mask Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |I2ADMx    |I2C Address Mask register
     * |        |          |1 = Mask enable (the received corresponding address bit is don't care.)
     * |        |          |0 = Mask disable (the received corresponding register bit should be exact the same as
     * |        |          |address register.)
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
     * |        |          |When the bit in the address mask register is set to one, it means the received
     * |        |          |corresponding address bit is don't-care. If the bit is set to zero, that means the received
     * |        |          |corresponding register bit should be exact the same as address register.
     */
    __IO uint32_t I2CADM2;

    /**
     * I2CADM3
     * ===================================================================================================
     * Offset: 0x30  I2C Slave Address Mask Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |I2ADMx    |I2C Address Mask register
     * |        |          |1 = Mask enable (the received corresponding address bit is don't care.)
     * |        |          |0 = Mask disable (the received corresponding register bit should be exact the same as
     * |        |          |address register.)
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
     * |        |          |When the bit in the address mask register is set to one, it means the received
     * |        |          |corresponding address bit is don't-care. If the bit is set to zero, that means the received
     * |        |          |corresponding register bit should be exact the same as address register.
     */
    __IO uint32_t I2CADM3;

    /**
     * RESERVED0
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    uint32_t RESERVED0[2];

    /**
     * I2CWKUPCON
     * ===================================================================================================
     * Offset: 0x3C  I2C Wake Up Control Register
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t I2CWKUPCON;

    /**
     * I2CWKUPSTS
     * ===================================================================================================
     * Offset: 0x40  I2C Wake Up Status Register
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t I2CWKUPSTS;

} I2C_T;

/** @addtogroup I2C_CONST I2C Bit Field Definition
  Constant Definitions for I2C Controller
  @{
 */

/* I2C I2CON Bit Field Definitions */
#define I2C_I2CON_EI_Pos                        7                                       /*!< I2C I2CON: EI Position */
#define I2C_I2CON_EI_Msk                        (1ul << I2C_I2CON_EI_Pos)               /*!< I2C I2CON: EI Mask */

#define I2C_I2CON_ENS1_Pos                      6                                       /*!< I2C I2CON: ENS1 Position */
#define I2C_I2CON_ENS1_Msk                      (1ul << I2C_I2CON_ENS1_Pos)             /*!< I2C I2CON: ENS1 Mask */

#define I2C_I2CON_STA_Pos                       5                                       /*!< I2C I2CON: STA Position */
#define I2C_I2CON_STA_Msk                       (1ul << I2C_I2CON_STA_Pos)              /*!< I2C I2CON: STA Mask */

#define I2C_I2CON_STO_Pos                       4                                       /*!< I2C I2CON: STO Position */
#define I2C_I2CON_STO_Msk                       (1ul << I2C_I2CON_STO_Pos)              /*!< I2C I2CON: STO Mask */

#define I2C_I2CON_SI_Pos                        3                                       /*!< I2C I2CON: SI Position */
#define I2C_I2CON_SI_Msk                        (1ul << I2C_I2CON_SI_Pos)               /*!< I2C I2CON: SI Mask */

#define I2C_I2CON_AA_Pos                        2                                       /*!< I2C I2CON: AA Position */
#define I2C_I2CON_AA_Msk                        (1ul << I2C_I2CON_AA_Pos)               /*!< I2C I2CON: AA Mask */

/* I2C I2CADDR Bit Field Definitions */
#define I2C_I2CADDR_I2CADDR_Pos                 1                                       /*!< I2C I2CADDR: I2CADDR Position */
#define I2C_I2CADDR_I2CADDR_Msk                 (0x7Ful << I2C_I2CADDR_I2CADDR_Pos)     /*!< I2C I2CADDR: I2CADDR Mask */

#define I2C_I2CADDR_GC_Pos                      0                                       /*!< I2C I2CADDR: GC Position */
#define I2C_I2CADDR_GC_Msk                      (1ul << I2C_I2CADDR_GC_Pos)             /*!< I2C I2CADDR: GC Mask */

/* I2C I2CDAT Bit Field Definitions */
#define I2C_I2CDAT_I2CDAT_Pos                   0                                       /*!< I2C I2CDAT: I2CDAT Position */
#define I2C_I2CDAT_I2CDAT_Msk                   (0xFFul << I2C_I2CDAT_I2CDAT_Pos)       /*!< I2C I2CDAT: I2CDAT Mask */

/* I2C I2CSTATUS Bit Field Definitions */
#define I2C_I2CSTATUS_I2CSTATUS_Pos             0                                       /*!< I2C I2CSTATUS: I2CSTATUS Position */
#define I2C_I2CSTATUS_I2CSTATUS_Msk             (0xFFul << I2C_I2CSTATUS_I2CSTATUS_Pos) /*!< I2C I2CSTATUS: I2CSTATUS Mask */

/* I2C I2CLK Bit Field Definitions */
#define I2C_I2CLK_I2CLK_Pos                     0                                       /*!< I2C I2CLK: I2CLK Position */
#define I2C_I2CLK_I2CLK_Msk                     (0xFFul << I2C_I2CLK_I2CLK_Pos)         /*!< I2C I2CLK: I2CLK Mask */

/* I2C I2CTOC Bit Field Definitions */
#define I2C_I2CTOC_ENTI_Pos                     2                                       /*!< I2C I2CTOC: ENTI Position */
#define I2C_I2CTOC_ENTI_Msk                     (1ul << I2C_I2CTOC_ENTI_Pos)            /*!< I2C I2CTOC: ENTI Mask */

#define I2C_I2CTOC_DIV4_Pos                     1                                       /*!< I2C I2CTOC: DIV4 Position */
#define I2C_I2CTOC_DIV4_Msk                     (1ul << I2C_I2CTOC_DIV4_Pos)            /*!< I2C I2CTOC: DIV4 Mask */

#define I2C_I2CTOC_TIF_Pos                      0                                       /*!< I2C I2CTOC: TIF Position */
#define I2C_I2CTOC_TIF_Msk                      (1ul << I2C_I2CTOC_TIF_Pos)             /*!< I2C I2CTOC: TIF Mask */

/* I2C I2CADM Bit Field Definitions */
#define I2C_I2CADM_I2CADM_Pos                   1                                       /*!< I2C I2CADM: I2CADM Position */
#define I2C_I2CADM_I2CADM_Msk                   (0x7Ful << I2C_I2CADM_I2CADM_Pos)       /*!< I2C I2CADM: I2CADM Mask */

/* I2C I2CWKUPCON Bit Field Definitions */
#define I2C_I2CWKUPCON_WKUPEN_Pos               0                                       /*!< I2C I2CWKUPCON: WKUPEN Position */
#define I2C_I2CWKUPCON_WKUPEN_Msk               (1ul << I2C_I2CWKUPCON_WKUPEN_Pos)      /*!< I2C I2CWKUPCON: WKUPEN Mask */

/* I2C I2CWKUPSTS Bit Field Definitions */
#define I2C_I2CWKUPSTS_WKUPIF_Pos               0                                       /*!< I2C I2CWKUPSTS: WKUPIF Position */
#define I2C_I2CWKUPSTS_WKUPIF_Msk               (1ul << I2C_I2CWKUPSTS_WKUPIF_Pos)      /*!< I2C I2CWKUPSTS: WKUPIF Mask */

/**@}*/ /* I2C_CONST */
/**@}*/ /* I2C */



/*----------------------------- PWM Controller -------------------------------*/

/** @addtogroup PWM PWM Controller(PWM)
  Memory Mapped Structure for PWM Generator and Capture Timer
  @{
 */
typedef struct
{
    /**
     * PPR
     * ===================================================================================================
     * Offset: 0x00  PWM Pre-Scale Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |CP01      |Clock pre-scalar 0(PWM counter 0 & 1 for group A and PWM counter 4 & 5 for group B)
     * |        |          |Clock input is divided by (CP01 + 1) before it is fed to the corresponding PWM counter
     * |        |          |If CP01=0, then the pre-scalar 0 output clock will be stopped. So corresponding PWM
     * |        |          |counter will be stopped also.
     * |[15:8]  |CP23      |Clock pre-scalar 2(PWM counter 2 & 3 for group A and PWM counter 6 & 7 for group B)
     * |        |          |Clock input is divided by (CP23 + 1) before it is fed to the corresponding PWM counter
     * |        |          |If CP23=0, then the pre-scalar 2 output clock will be stopped. So corresponding PWM
     * |        |          |counter will be stopped also.
     * |[23:16] |DZI01     |Dead zone interval register for pair of channel 0 and channel 1(PWM0 and PWM1 pair
     * |        |          |for PWM group A, PWM4 and PWM5 pair for PWM group B)
     * |        |          |These 8 bits determine dead zone length.
     * |        |          |The unit time of dead zone length is received from corresponding CSR bits.
     * |[31:24] |DZI23     |Dead zone interval register for pair of channel 2 and channel 3(PWM2 and PWM3 pair
     * |        |          |for PWM group A, PWM6 and PWM7 pair for PWM group B)
     * |        |          |These 8 bits determine dead zone length.
     * |        |          |The unit time of dead zone length is received from corresponding CSR bits.
     */
    __IO uint32_t PPR;

    /**
     * CSR
     * ===================================================================================================
     * Offset: 0x04  PWM Clock Source Divider Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |CSR0      |Timer 0 Clock Source Selection(PWM timer 0 for group A and PWM timer 4 for group B)
     * |        |          |Select clock input for timer.
     * |        |          |(Table is the same as CSR3)
     * |[6:4]   |CSR1      |Timer 1 Clock Source Selection(PWM timer 1 for group A and PWM timer 5 for group B)
     * |        |          |Select clock input for timer.
     * |        |          |(Table is the same as CSR3)
     * |[10:8]  |CSR2      |Timer 2 Clock Source Selection(PWM timer 2 for group A and PWM timer 6 for group B)
     * |        |          |Select clock input for timer.
     * |        |          |(Table is the same as CSR3)
     * |[14:12] |CSR3      |Timer 3 Clock Source Selection (PWM timer 3 for group A and PWM timer 7 for group B)
     * |        |          |Select clock input for timer.
     * |        |          |CSRx[2:0] = Input clock divider
     * |        |          |100 = 1
     * |        |          |011 = 16
     * |        |          |010 = 8
     * |        |          |001 = 4
     * |        |          |000 = 2
     */
    __IO uint32_t CSR;

    /**
     * PCR
     * ===================================================================================================
     * Offset: 0x08  PWM Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CH0EN     |PWM-Timer 0 Enable/Disable Start Run (PWM timer 0 for group A and PWM timer 4 for
     * |        |          |group B)
     * |        |          |1 = Enable corresponding PWM-Timer Start Run
     * |        |          |0 = Stop corresponding PWM-Timer Running
     * |[2]     |CH0INV    |PWM-Timer 0 Output Inverter ON/OFF(PWM timer 0 for group A and PWM timer 4 for
     * |        |          |group B)
     * |        |          |1 = Inverter ON
     * |        |          |0 = Inverter OFF
     * |[3]     |CH0MOD    |PWM-Timer 0 Auto-reload/One-Shot Mode(PWM timer 0 for group A and PWM timer 4
     * |        |          |for group B)
     * |        |          |1 = Auto-reload Mode
     * |        |          |0 = One-Shot Mode
     * |        |          |Note: If there is a rising transition at this bit, it will cause CNR0 and CMR0 be clear.
     * |[4]     |DZEN01    |Dead-Zone 0 Generator Enable/Disable(PWM0 and PWM1 pair for PWM group A,
     * |        |          |PWM4 and PWM5 pair for PWM group B)
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |Note: When Dead-Zone Generator is enabled, the pair of PWM0 and PWM1 becomes a
     * |        |          |complementary pair for PWM group A and the pair of PWM4 and PWM5 becomes a
     * |        |          |complementary pair for PWM group B.
     * |[5]     |DZEN23    |Dead-Zone 2 Generator Enable/Disable(PWM2 and PWM3 pair for PWM group A,
     * |        |          |PWM6 and PWM7 pair for PWM group B)
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |        |          |Note: When Dead-Zone Generator is enabled, the pair of PWM2 and PWM3 becomes a
     * |        |          |complementary pair for PWM group A and the pair of PWM6 and PWM7 becomes a
     * |        |          |complementary pair for PWM group B.
     * |[8]     |CH1EN     |PWM-Timer 1 Enable/Disable Start Run (PWM timer 1 for group A and PWM timer 5 for
     * |        |          |group B)
     * |        |          |1 = Enable corresponding PWM-Timer Start Run
     * |        |          |0 = Stop corresponding PWM-Timer Running
     * |[10]    |CH1INV    |PWM-Timer 1 Output Inverter ON/OFF(PWM timer 1 for group A and PWM timer 5 for
     * |        |          |group B)
     * |        |          |1 = Inverter ON
     * |        |          |0 = Inverter OFF
     * |[11]    |CH1MOD    |PWM-Timer 1 Auto-reload/One-Shot Mode(PWM timer 1 for group A and PWM timer 5
     * |        |          |for group B)
     * |        |          |1 = Auto-reload Mode
     * |        |          |0 = One-Shot Mode
     * |        |          |Note: If there is a rising transition at this bit, it will cause CNR1 and CMR1 be clear.
     * |[16]    |CH2EN     |PWM-Timer 2 Enable/Disable Start Run (PWM timer 2 for group A and PWM timer 6 for
     * |        |          |group B)
     * |        |          |1 = Enable corresponding PWM-Timer Start Run
     * |        |          |0 = Stop corresponding PWM-Timer Running
     * |[18]    |CH2INV    |PWM-Timer 2 Output Inverter ON/OFF(PWM timer 2 for group A and PWM timer 6 for
     * |        |          |group B)
     * |        |          |1 = Inverter ON
     * |        |          |0 = Inverter OFF
     * |[19]    |CH2MOD    |PWM-Timer 2 Auto-reload/One-Shot Mode(PWM timer 2 for group A and PWM timer 6
     * |        |          |for group B)
     * |        |          |1 = Auto-reload Mode
     * |        |          |0 = One-Shot Mode
     * |        |          |Note: If there is a rising transition at this bit, it will cause CNR2 and CMR2 be clear.
     * |[24]    |CH3EN     |PWM-Timer 3 Enable/Disable Start Run (PWM timer 3 for group A and PWM timer 7 for
     * |        |          |group B)
     * |        |          |1 = Enable corresponding PWM-Timer Start Run
     * |        |          |0 = Stop corresponding PWM-Timer Running
     * |[26]    |CH3INV    |PWM-Timer 3 Output Inverter ON/OFF(PWM timer 3 for group A and PWM timer 7 for
     * |        |          |group B)
     * |        |          |1 = Inverter ON
     * |        |          |0 = Inverter OFF
     * |[27]    |CH3MOD    |PWM-Timer 3 Auto-reload/One-Shot Mode(PWM timer 3 for group A and PWM timer 7
     * |        |          |for group B)
     * |        |          |1 = Auto-reload Mode
     * |        |          |0 = One-Shot Mode
     * |        |          |Note: If there is a rising transition at this bit, it will cause CNR3 and CMR3 be clear.
     */
    __IO uint32_t PCR;

    /**
     * CNR0
     * ===================================================================================================
     * Offset: 0x0C  PWM Counter 0/Timer 0 Loaded Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CNR       |PWM Counter/Timer Loaded Value
     * |        |          |CNR determines the PWM period.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CNR0;

    /**
     * CMR0
     * ===================================================================================================
     * Offset: 0x10  PWM Comparator 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CMR       |PWM Comparator Register
     * |        |          |CNR determines the PWM duty.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CMR0;

    /**
     * PDR0
     * ===================================================================================================
     * Offset: 0x14  PWM Data 0 Register(current counter 0 value)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PDR       |PWM Data Register
     * |        |          |User can monitor PDR to know the current value in 16-bit down counter.
     */
    __I  uint32_t PDR0;

    /**
     * CNR1
     * ===================================================================================================
     * Offset: 0x18  PWM Counter 1/Timer 1 Loaded Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CNR       |PWM Counter/Timer Loaded Value
     * |        |          |CNR determines the PWM period.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CNR1;

    /**
     * CMR1
     * ===================================================================================================
     * Offset: 0x1C  PWM Comparator 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CMR       |PWM Comparator Register
     * |        |          |CNR determines the PWM duty.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CMR1;

    /**
     * PDR1
     * ===================================================================================================
     * Offset: 0x20  PWM Data 1 Register(current counter 1 value)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PDR       |PWM Data Register
     * |        |          |User can monitor PDR to know the current value in 16-bit down counter.
     */
    __I  uint32_t PDR1;

    /**
     * CNR2
     * ===================================================================================================
     * Offset: 0x24  PWM Counter 2/Timer 2 Loaded Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CNR       |PWM Counter/Timer Loaded Value
     * |        |          |CNR determines the PWM period.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CNR2;

    /**
     * CMR2
     * ===================================================================================================
     * Offset: 0x28  PWM Comparator 2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CMR       |PWM Comparator Register
     * |        |          |CNR determines the PWM duty.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CMR2;

    /**
     * PDR2
     * ===================================================================================================
     * Offset: 0x2C  PWM Data 2 Register(current counter 2 value)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PDR       |PWM Data Register
     * |        |          |User can monitor PDR to know the current value in 16-bit down counter.
     */
    __I  uint32_t PDR2;

    /**
     * CNR3
     * ===================================================================================================
     * Offset: 0x30  PWM Counter 3/Timer 3 Loaded Value
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CNR       |PWM Counter/Timer Loaded Value
     * |        |          |CNR determines the PWM period.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CNR3;

    /**
     * CMR3
     * ===================================================================================================
     * Offset: 0x34  PWM Comparator 3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CMR       |PWM Comparator Register
     * |        |          |CNR determines the PWM duty.
     * |        |          |PWM frequency = PWMxy_CLK/(prescale+1)/(clock divider)/(CNR+1); where xy, could be 01, 23,
     * |        |          |45 or 67, depends on selected PWM channel.
     * |        |          |Duty ratio = (CMR+1)/(CNR+1).
     * |        |          |CMR >= CNR: PWM output is always high.
     * |        |          |CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
     * |        |          |CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
     * |        |          |(Unit = one PWM clock cycle)
     * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
     */
    __IO uint32_t CMR3;

    /**
     * PDR3
     * ===================================================================================================
     * Offset: 0x38  PWM Data 3 Register(current counter 3 value)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PDR       |PWM Data Register
     * |        |          |User can monitor PDR to know the current value in 16-bit down counter.
     */
    __I  uint32_t PDR3;

    /**
     * RESERVE0
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I uint32_t RESERVE0;

    /**
     * PIER
     * ===================================================================================================
     * Offset: 0x40  PWM Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWMIE0    |PWM channel 0 Interrupt Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[1]     |PWMIE1    |PWM channel 1 Interrupt Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[2]     |PWMIE2    |PWM channel 2 Interrupt Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     * |[3]     |PWMIE3    |PWM channel 3 Interrupt Enable
     * |        |          |1 = Enable
     * |        |          |0 = Disable
     */
    __IO uint32_t PIER;

    /**
     * PIIR
     * ===================================================================================================
     * Offset: 0x44  PWM Interrupt Indication Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWMIF0    |PWM channel 0 Interrupt Status
     * |        |          |Flag is set by hardware when PWM0 down counter reaches zero, software can clear this
     * |        |          |bit by writing a one to it.
     * |[1]     |PWMIF1    |PWM channel 1 Interrupt Status
     * |        |          |Flag is set by hardware when PWM1 down counter reaches zero, software can clear this
     * |        |          |bit by writing a one to it.
     * |[2]     |PWMIF2    |PWM channel 2 Interrupt Status
     * |        |          |Flag is set by hardware when PWM2 down counter reaches zero, software can clear this
     * |        |          |bit by writing a one to it.
     * |[3]     |PWMIF3    |PWM channel 3 Interrupt Status
     * |        |          |Flag is set by hardware when PWM3 down counter reaches zero, software can clear this
     * |        |          |bit by writing a one to it.
     */
    __IO uint32_t PIIR;

    /**
     * RESERVE1
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I uint32_t    RESERVE1[2];

    /**
     * CCR0
     * ===================================================================================================
     * Offset: 0x50  Capture 0/1 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INV0      |PWM Group Channel 0 Inverter ON/OFF
     * |        |          |1 = Inverter ON. Reverse the input signal from GPIO before fed to Capture timer
     * |        |          |0 = Inverter OFF
     * |[1]     |CRL_IE0   |PWM Group Channel 0 Rising Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable rising latch interrupt
     * |        |          |0 = Disable rising latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 0 has rising transition, Capture
     * |        |          |issues an Interrupt.
     * |[2]     |CFL_IE0   |PWM Group Channel 0 Falling Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable falling latch interrupt
     * |        |          |0 = Disable falling latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 0 has falling transition, Capture
     * |        |          |issues an Interrupt.
     * |[3]     |CAPCH0EN  |Capture Channel 0 transition Enable/Disable
     * |        |          |1 = Enable capture function on PWM group channel 0.
     * |        |          |0 = Disable capture function on PWM group channel 0
     * |        |          |When Enable, Capture latched the PWM-counter value and saved to CRLR (Rising
     * |        |          |latch) and CFLR (Falling latch).
     * |        |          |When Disable, Capture does not update CRLR and CFLR, and disable PWM group
     * |        |          |channel 0 Interrupt.
     * |[4]     |CAPIF0    |Capture0 Interrupt Indication Flag
     * |        |          |If PWM group channel 0 rising latch interrupt is enabled (CRL_IE0=1), a rising transition occurs
     * |        |          |at PWM group channel 0 will result in CAPIF0 to high; Similarly, a falling transition will cause
     * |        |          |CAPIF0 to be set high if PWM group channel 0 falling latch interrupt is enabled (CFL_IE0=1).
     * |        |          |This flag is clear by software with a write 1 to itself.
     * |[6]     |CRLRI0    |CRLR0 Latched Indicator Bit
     * |        |          |When PWM group input channel 0 has a rising transition, CRLR0 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     * |[7]     |CFLRI0    |CFLR0 Latched Indicator Bit
     * |        |          |When PWM group input channel 0 has a falling transition, CFLR0 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     * |[16]    |INV1      |PWM Group Channel 1 Inverter ON/OFF
     * |        |          |1 = Inverter ON. Reverse the input signal from GPIO before fed to Capture timer
     * |        |          |0 = Inverter OFF
     * |[17]    |CRL_IE1   |PWM Group Channel 1 Rising Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable rising latch interrupt
     * |        |          |0 = Disable rising latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 1 has rising transition, Capture
     * |        |          |issues an Interrupt.
     * |[18]    |CFL_IE1   |PWM Group Channel 1 Falling Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable falling latch interrupt
     * |        |          |0 = Disable falling latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 1 has falling transition, Capture
     * |        |          |issues an Interrupt.
     * |[19]    |CAPCH1EN  |Capture Channel 1 transition Enable/Disable
     * |        |          |1 = Enable capture function on PWM group channel 1.
     * |        |          |0 = Disable capture function on PWM group channel 1
     * |        |          |When Enable, Capture latched the PWM-counter value and saved to CRLR (Rising
     * |        |          |latch) and CFLR (Falling latch).
     * |        |          |When Disable, Capture does not update CRLR and CFLR, and disable PWM group
     * |        |          |channel 1 Interrupt.
     * |[20]    |CAPIF1    |Capture1 Interrupt Indication Flag
     * |        |          |If PWM group channel 1 rising latch interrupt is enabled (CRL_IE1=1), a rising transition occurs
     * |        |          |at PWM group channel 1 will result in CAPIF1 to high; Similarly, a falling transition will cause
     * |        |          |CAPIF1 to be set high if PWM group channel 1 falling latch interrupt is enabled (CFL_IE1=1).
     * |        |          |This flag is clear by software with a write 1 to itself.
     * |[22]    |CRLRI1    |CRLR1 Latched Indicator Bit
     * |        |          |When PWM group input channel 1 has a rising transition, CRLR1 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     * |[23]    |CFLRI1    |CFLR1 Latched Indicator Bit
     * |        |          |When PWM group input channel 1 has a falling transition, CFLR1 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     */
    __IO uint32_t CCR0;

    /**
     * CCR2
     * ===================================================================================================
     * Offset: 0x54  Capture 2/3 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INV2      |PWM Group Channel 2 Inverter ON/OFF
     * |        |          |1 = Inverter ON. Reverse the input signal from GPIO before fed to Capture timer
     * |        |          |0 = Inverter OFF
     * |[1]     |CRL_IE2   |PWM Group Channel 2 Rising Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable rising latch interrupt
     * |        |          |0 = Disable rising latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 2 has rising transition, Capture
     * |        |          |issues an Interrupt.
     * |[2]     |CFL_IE2   |PWM Group Channel 2 Falling Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable falling latch interrupt
     * |        |          |0 = Disable falling latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 2 has falling transition, Capture
     * |        |          |issues an Interrupt.
     * |[3]     |CAPCH2EN  |Capture Channel 2 transition Enable/Disable
     * |        |          |1 = Enable capture function on PWM group channel 2.
     * |        |          |0 = Disable capture function on PWM group channel 2
     * |        |          |When Enable, Capture latched the PWM-counter value and saved to CRLR (Rising
     * |        |          |latch) and CFLR (Falling latch).
     * |        |          |When Disable, Capture does not update CRLR and CFLR, and disable PWM group
     * |        |          |channel 2 Interrupt.
     * |[4]     |CAPIF2    |Capture2 Interrupt Indication Flag
     * |        |          |If PWM group channel 2 rising latch interrupt is enabled (CRL_IE2=1), a rising transition occurs
     * |        |          |at PWM group channel 2 will result in CAPIF2 to high; Similarly, a falling transition will cause
     * |        |          |CAPIF2 to be set high if PWM group channel 2 falling latch interrupt is enabled (CFL_IE2=1).
     * |        |          |This flag is clear by software with a write 1 to itself.
     * |[6]     |CRLRI2    |CRLR2 Latched Indicator Bit
     * |        |          |When PWM group input channel 2 has a rising transition, CRLR2 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     * |[7]     |CFLRI2    |CFLR2 Latched Indicator Bit
     * |        |          |When PWM group input channel 2 has a falling transition, CFLR2 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     * |[16]    |INV3      |PWM Group Channel 3 Inverter ON/OFF
     * |        |          |1 = Inverter ON. Reverse the input signal from GPIO before fed to Capture timer
     * |        |          |0 = Inverter OFF
     * |[17]    |CRL_IE3   |PWM Group Channel 3 Rising Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable rising latch interrupt
     * |        |          |0 = Disable rising latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 3 has rising transition, Capture
     * |        |          |issues an Interrupt.
     * |[18]    |CFL_IE3   |PWM Group Channel 3 Falling Latch Interrupt Enable ON/OFF
     * |        |          |1 = Enable falling latch interrupt
     * |        |          |0 = Disable falling latch interrupt
     * |        |          |When Enable, if Capture detects PWM group channel 3 has falling transition, Capture
     * |        |          |issues an Interrupt.
     * |[19]    |CAPCH3EN  |Capture Channel 3 transition Enable/Disable
     * |        |          |1 = Enable capture function on PWM group channel 3.
     * |        |          |0 = Disable capture function on PWM group channel 3
     * |        |          |When Enable, Capture latched the PWM-counter value and saved to CRLR (Rising
     * |        |          |latch) and CFLR (Falling latch).
     * |        |          |When Disable, Capture does not update CRLR and CFLR, and disable PWM group
     * |        |          |channel 3 Interrupt.
     * |[20]    |CAPIF3    |Capture3 Interrupt Indication Flag
     * |        |          |If PWM group channel 3 rising latch interrupt is enabled (CRL_IE3=1), a rising transition occurs
     * |        |          |at PWM group channel 3 will result in CAPIF3 to high; Similarly, a falling transition will cause
     * |        |          |CAPIF3 to be set high if PWM group channel 3 falling latch interrupt is enabled (CFL_IE3=1).
     * |        |          |This flag is clear by software with a write 1 to itself.
     * |[22]    |CRLRI3    |CRLR3 Latched Indicator Bit
     * |        |          |When PWM group input channel 3 has a rising transition, CRLR3 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     * |[23]    |CFLRI3    |CFLR3 Latched Indicator Bit
     * |        |          |When PWM group input channel 3 has a falling transition, CFLR3 was latched with the value of
     * |        |          |PWM down-counter and this bit is set by hardware.
     * |        |          |Clear this bit by writing a one to it.
     */
    __IO uint32_t CCR2;

    /**
     * CRLR0
     * ===================================================================================================
     * Offset: 0x58  Capture 0 Rising Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CRLR      |Capture Rising Latch Register
     * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
     */
    __IO uint32_t CRLR0;

    /**
     * CFLR0
     * ===================================================================================================
     * Offset: 0x5C  Capture 0 Falling Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CFLR      |Capture Falling Latch Register
     * |        |          |Latch the PWM counter when Channel 01/2/3 has Falling transition.
     */
    __IO uint32_t CFLR0;

    /**
     * CRLR1
     * ===================================================================================================
     * Offset: 0x60  Capture 1 Rising Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CRLR      |Capture Rising Latch Register
     * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
     */
    __IO uint32_t CRLR1;

    /**
     * CFLR1
     * ===================================================================================================
     * Offset: 0x64  Capture 1 Falling Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CFLR      |Capture Falling Latch Register
     * |        |          |Latch the PWM counter when Channel 01/2/3 has Falling transition.
     */
    __IO uint32_t CFLR1;

    /**
     * CRLR2
     * ===================================================================================================
     * Offset: 0x68  Capture 2 Rising Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CRLR      |Capture Rising Latch Register
     * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
     */
    __IO uint32_t CRLR2;

    /**
     * CFLR2
     * ===================================================================================================
     * Offset: 0x6C  Capture 2 Falling Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CFLR      |Capture Falling Latch Register
     * |        |          |Latch the PWM counter when Channel 0/1/2/3 has Falling transition.
     */
    __IO uint32_t CFLR2;

    /**
     * CRLR3
     * ===================================================================================================
     * Offset: 0x70  Capture 3 Rising Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CRLR      |Capture Rising Latch Register
     * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
     */
    __IO uint32_t CRLR3;

    /**
     * CFLR3
     * ===================================================================================================
     * Offset: 0x74  Capture 3 Falling Latch Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |CFLR      |Capture Falling Latch Register
     * |        |          |Latch the PWM counter when Channel 0/1/2/3 has Falling transition.
     */
    __IO uint32_t CFLR3;

    /**
     * CAPENR
     * ===================================================================================================
     * Offset: 0x78  Capture Input Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |CAPENR    |Capture Input Enable Register
     * |        |          |There are four capture inputs from pad. Bit0~Bit3 are used to control each inputs ON or
     * |        |          |OFF.
     * |        |          |0 = OFF (PWMx multi-function pin input does not affect input capture function.)
     * |        |          |1 = (PWMx multi-function pin input will affect its input capture function.)
     * |        |          |CAPENR
     * |        |          |Bit 3210 for PWM group A
     * |        |          |Bit xxx1 -> Capture channel 0 is from P2 [0]
     * |        |          |Bit xx1x -> Capture channel 1 is from P2 [1]
     * |        |          |Bit x1xx -> Capture channel 2 is from P2 [2]
     * |        |          |Bit 1xxx -> Capture channel 3 is from P2 [3]
     * |        |          |Bit 3210 for PWM group B
     * |        |          |Bit xxx1 -> Capture channel 0 is from P2 [4]
     * |        |          |Bit xx1x -> Capture channel 1 is from P2 [5]
     * |        |          |Bit x1xx -> Capture channel 2 is from P2 [6]
     * |        |          |Bit 1xxx -> Capture channel 3 is from P2 [7]
     */
    __IO uint32_t CAPENR;

    /**
     * POE
     * ===================================================================================================
     * Offset: 0x7C  PWM Output Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWM0      |PWM Channel 0 Output Enable Register
     * |        |          |1 = Enable PWM channel 0 output to pin.
     * |        |          |0 = Disable PWM channel 0 output to pin.
     * |        |          |Note: The corresponding GPIO pin also must be switched to PWM function.
     * |[1]     |PWM1      |PWM Channel 1 Output Enable Register
     * |        |          |1 = Enable PWM channel 1 output to pin.
     * |        |          |0 = Disable PWM channel 1 output to pin.
     * |        |          |Note: The corresponding GPIO pin also must be switched to PWM function.
     * |[2]     |PWM2      |PWM Channel 2 Output Enable Register
     * |        |          |1 = Enable PWM channel 2 output to pin.
     * |        |          |0 = Disable PWM channel 2 output to pin.
     * |        |          |Note: The corresponding GPIO pin also must be switched to PWM function.
     * |[3]     |PWM3      |PWM Channel 3 Output Enable Register
     * |        |          |1 = Enable PWM channel 3 output to pin.
     * |        |          |0 = Disable PWM channel 3 output to pin.
     * |        |          |Note: The corresponding GPIO pin also must be switched to PWM function.
     */
    __IO uint32_t POE;

    /**
     * TCON
     * ===================================================================================================
     * Offset: 0x80  PWM Trigger Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWM0PTEN  |Channel 0 PWM Period Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 0 trigger ADC function
     * |        |          |0 = Disable PWM channel 0 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to underflow.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count to (CNR+1) or down count to underflow based on INT01PTYPE setting.
     * |        |          |1 = Enable PWM channel 0 output to pin.
     * |        |          |0 = Disable PWM channel 0 output to pin.
     * |        |          |Note: The corresponding GPIO pin also must be switched to PWM function.
     * |[1]     |PWM1PTEN  |Channel 1 PWM Period Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 1 trigger ADC function
     * |        |          |0 = Disable PWM channel 1 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to underflow.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count to (CNR+1) or down count to underflow based on INT01PTYPE setting.
     * |[2]     |PWM2PTEN  |Channel 2 PWM Period Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 2 trigger ADC function
     * |        |          |0 = Disable PWM channel 2 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to underflow.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count to (CNR+1) or down count to underflow based on INT23PTYPE setting.
     * |[3]     |PWM3PTEN  |Channel 3 PWM Period Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 3 trigger ADC function
     * |        |          |0 = Disable PWM channel 3 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to underflow.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count to (CNR+1) or down count to underflow based on INT23PTYPE setting.
     * |[8]     |PWM0DTEN  |Channel 0 PWM Duty Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 0 trigger ADC function
     * |        |          |0 = Disable PWM channel 0 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to match CMR.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count or down count to match CMR based on INT01DTYPE setting.
     * |[9]     |PWM1DTEN  |Channel 1 PWM Duty Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 1 trigger ADC function
     * |        |          |0 = Disable PWM channel 1 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to match CMR.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count or down count to match CMR based on INT01DTYPE setting.
     * |[10]    |PWM2DTEN  |Channel 2 PWM Duty Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 2 trigger ADC function
     * |        |          |0 = Disable PWM channel 2 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to match CMR.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count or down count to match CMR based on INT23DTYPE setting.
     * |[11]    |PWM3DTEN  |Channel 3 PWM Duty Trigger ADC Enable Register
     * |        |          |1 = Enable PWM channel 3 trigger ADC function
     * |        |          |0 = Disable PWM channel 3 trigger ADC function
     * |        |          |As PWM operating at edge-aligned mode, enable this bit can make PWM trigger ADC to start conversion when PWM counter down count to match CMR.
     * |        |          |As PWM operating at center-aligned mode, enable this bit can make PWM trigger ADC to start conversion
     * |        |          |when PWM counter up count or down count to match CMR based on INT23DTYPE setting.
     */
    __IO uint32_t TCON;

    /**
     * TSTATUS
     * ===================================================================================================
     * Offset: 0x84  PWM Trigger Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWM0TF    |PWM Channel 0 Trigger ADC Flag
     * |        |          |This bit is set to 1 by hardware when PWM0 trigger ADC condition matched. As this bit is set to 1,
     * |        |          |ADC will start conversion if ADC triggered source is selected by PWM.
     * |        |          |Software can write 1 to clear this bit.
     * |[1]     |PWM1TF    |PWM Channel 1 Trigger ADC Flag
     * |        |          |This bit is set to 1 by hardware when PWM1 trigger ADC condition matched. As this bit is set to 1,
     * |        |          |ADC will start conversion if ADC triggered source is selected by PWM.
     * |        |          |Software can write 1 to clear this bit.
     * |[2]     |PWM2TF    |PWM Channel 2 Trigger ADC Flag
     * |        |          |This bit is set to 1 by hardware when PWM2 trigger ADC condition matched. As this bit is set to 1,
     * |        |          |ADC will start conversion if ADC triggered source is selected by PWM.
     * |        |          |Software can write 1 to clear this bit.
     * |[3]     |PWM3TF    |PWM Channel 3 Trigger ADC Flag
     * |        |          |This bit is set to 1 by hardware when PWM3 trigger ADC condition matched. As this bit is set to 1,
     * |        |          |ADC will start conversion if ADC triggered source is selected by PWM.
     * |        |          |Software can write 1 to clear this bit.
     */
    __IO uint32_t TSTATUS;

    /**
     * RESERVE2
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t  RESERVE2[4];

    /**
     * PSCR
     * ===================================================================================================
     * Offset: 0x98  PWM Synchronous Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8]     |PSSEN1    |PWM1 Synchronous Start Enable
     * |        |          |1 = PWM1 synchronous start enable.
     * |        |          |0 = PWM1 synchronous start disable.
     * |        |          |If this bit is set to 1, PWM-Timer1 will synchronous start with PWM-Timer0 when SW writes 1 to PCR.CH0EN in PWM group A.
     * |[16]    |PSSEN2    |PWM2 Synchronous Start Enable
     * |        |          |1 = PWM2 synchronous start enable.
     * |        |          |0 = PWM2 synchronous start disable.
     * |        |          |If this bit is set to 1, PWM-Timer2 will synchronous start with PWM-Timer0 when SW writes 1 to PCR.CH0EN in PWM group A.
     * |[24]    |PSSEN3    |PWM3 Synchronous Start Enable
     * |        |          |1 = PWM3 synchronous start enable.
     * |        |          |0 = PWM3 synchronous start disable.
     * |        |          |If this bit is set to 1, PWM-Timer3 will synchronous start with PWM-Timer0 when SW writes 1 to PCR.CH0EN in PWM group A.
     */
    __IO uint32_t PSCR;

} PWM_T;

/** @addtogroup PWM_CONST PWM Bit Field Definition
  Constant Definitions for PWM Controller
  @{
 */

/* PWM PPR Bit Field Definitions */
#define PWM_PPR_DZI23_Pos                       24                                  /*!< PWM PPR: DZI23 Position */
#define PWM_PPR_DZI23_Msk                       (0xFFul << PWM_PPR_DZI23_Pos)       /*!< PWM PPR: DZI23 Mask */

#define PWM_PPR_DZI01_Pos                       16                                  /*!< PWM PPR: DZI01 Position */
#define PWM_PPR_DZI01_Msk                       (0xFFul << PWM_PPR_DZI01_Pos)       /*!< PWM PPR: DZI01 Mask */

#define PWM_PPR_CP23_Pos                        8                                   /*!< PWM PPR: CP23 Position */
#define PWM_PPR_CP23_Msk                        (0xFFul << PWM_PPR_CP23_Pos)        /*!< PWM PPR: CP23 Mask */

#define PWM_PPR_CP01_Pos                        0                                   /*!< PWM PPR: CP01 Position */
#define PWM_PPR_CP01_Msk                        (0xFFul << PWM_PPR_CP01_Pos)        /*!< PWM PPR: CP01 Mask */

/* PWM CSR Bit Field Definitions */
#define PWM_CSR_CSR3_Pos                        12                                  /*!< PWM CSR: CSR3 Position */
#define PWM_CSR_CSR3_Msk                        (7ul << PWM_CSR_CSR3_Pos)           /*!< PWM CSR: CSR3 Mask */

#define PWM_CSR_CSR2_Pos                        8                                   /*!< PWM CSR: CSR2 Position */
#define PWM_CSR_CSR2_Msk                        (7ul << PWM_CSR_CSR2_Pos)           /*!< PWM CSR: CSR2 Mask */

#define PWM_CSR_CSR1_Pos                        4                                   /*!< PWM CSR: CSR1 Position */
#define PWM_CSR_CSR1_Msk                        (7ul << PWM_CSR_CSR1_Pos)           /*!< PWM CSR: CSR1 Mask */

#define PWM_CSR_CSR0_Pos                        0                                   /*!< PWM CSR: CSR0 Position */
#define PWM_CSR_CSR0_Msk                        (7ul << PWM_CSR_CSR0_Pos)           /*!< PWM CSR: CSR0 Mask */

/* PWM PCR Bit Field Definitions */
#define PWM_PCR_PWM23TYPE_Pos                   31                                  /*!< PWM PCR: PWM23TYPE Position */
#define PWM_PCR_PWM23TYPE_Msk                   (1ul << PWM_PCR_PWM23TYPE_Pos)      /*!< PWM PCR: PWM23TYPE Mask */

#define PWM_PCR_PWM01TYPE_Pos                   30                                  /*!< PWM PCR: PWM01TYPE Position */
#define PWM_PCR_PWM01TYPE_Msk                   (1ul << PWM_PCR_PWM01TYPE_Pos)      /*!< PWM PCR: PWM01TYPE Mask */

#define PWM_PCR_CH3MOD_Pos                      27                                  /*!< PWM PCR: CH3MOD Position */
#define PWM_PCR_CH3MOD_Msk                      (1ul << PWM_PCR_CH3MOD_Pos)         /*!< PWM PCR: CH3MOD Mask */

#define PWM_PCR_CH3INV_Pos                      26                                  /*!< PWM PCR: CH3INV Position */
#define PWM_PCR_CH3INV_Msk                      (1ul << PWM_PCR_CH3INV_Pos)         /*!< PWM PCR: CH3INV Mask */

#define PWM_PCR_CH3PINV_Pos                     25                                  /*!< PWM PCR: CH3PINV Position */
#define PWM_PCR_CH3PINV_Msk                     (1ul << PWM_PCR_CH3PINV_Pos)        /*!< PWM PCR: CH3PINV Mask */

#define PWM_PCR_CH3EN_Pos                       24                                  /*!< PWM PCR: CH3EN Position */
#define PWM_PCR_CH3EN_Msk                       (1ul << PWM_PCR_CH3EN_Pos)          /*!< PWM PCR: CH3EN Mask */

#define PWM_PCR_CH2MOD_Pos                      19                                  /*!< PWM PCR: CH2MOD Position */
#define PWM_PCR_CH2MOD_Msk                      (1ul << PWM_PCR_CH2MOD_Pos)         /*!< PWM PCR: CH2MOD Mask */

#define PWM_PCR_CH2INV_Pos                      18                                  /*!< PWM PCR: CH2INV Position */
#define PWM_PCR_CH2INV_Msk                      (1ul << PWM_PCR_CH2INV_Pos)         /*!< PWM PCR: CH2INV Mask */

#define PWM_PCR_CH2PINV_Pos                     17                                  /*!< PWM PCR: CH2PINV Position */
#define PWM_PCR_CH2PINV_Msk                     (1ul << PWM_PCR_CH2PINV_Pos)        /*!< PWM PCR: CH2PINV Mask */

#define PWM_PCR_CH2EN_Pos                       16                                  /*!< PWM PCR: CH2EN Position */
#define PWM_PCR_CH2EN_Msk                       (1ul << PWM_PCR_CH2EN_Pos)          /*!< PWM PCR: CH2EN Mask */

#define PWM_PCR_CH1MOD_Pos                      11                                  /*!< PWM PCR: CH1MOD Position */
#define PWM_PCR_CH1MOD_Msk                      (1ul << PWM_PCR_CH1MOD_Pos)         /*!< PWM PCR: CH1MOD Mask */

#define PWM_PCR_CH1INV_Pos                      10                                  /*!< PWM PCR: CH1INV Position */
#define PWM_PCR_CH1INV_Msk                      (1ul << PWM_PCR_CH1INV_Pos)         /*!< PWM PCR: CH1INV Mask */

#define PWM_PCR_CH1PINV_Pos                     9                                   /*!< PWM PCR: CH1PINV Position */
#define PWM_PCR_CH1PINV_Msk                     (1ul << PWM_PCR_CH1PINV_Pos)        /*!< PWM PCR: CH1PINV Mask */

#define PWM_PCR_CH1EN_Pos                       8                                   /*!< PWM PCR: CH1EN Position */
#define PWM_PCR_CH1EN_Msk                       (1ul << PWM_PCR_CH1EN_Pos)          /*!< PWM PCR: CH1EN Mask */

#define PWM_PCR_DZEN23_Pos                      5                                   /*!< PWM PCR: DZEN23 Position */
#define PWM_PCR_DZEN23_Msk                      (1ul << PWM_PCR_DZEN23_Pos)         /*!< PWM PCR: DZEN23 Mask */

#define PWM_PCR_DZEN01_Pos                      4                                   /*!< PWM PCR: DZEN01 Position */
#define PWM_PCR_DZEN01_Msk                      (1ul << PWM_PCR_DZEN01_Pos)         /*!< PWM PCR: DZEN01 Mask */

#define PWM_PCR_CH0MOD_Pos                      3                                   /*!< PWM PCR: CH0MOD Position */
#define PWM_PCR_CH0MOD_Msk                      (1ul << PWM_PCR_CH0MOD_Pos)         /*!< PWM PCR: CH0MOD Mask */

#define PWM_PCR_CH0INV_Pos                      2                                   /*!< PWM PCR: CH0INV Position */
#define PWM_PCR_CH0INV_Msk                      (1ul << PWM_PCR_CH0INV_Pos)         /*!< PWM PCR: CH0INV Mask */

#define PWM_PCR_CH0PINV_Pos                      1                                  /*!< PWM PCR: CH0PINV Position */
#define PWM_PCR_CH0PINV_Msk                     (1ul << PWM_PCR_CH0PINV_Pos)        /*!< PWM PCR: CH0PINV Mask */

#define PWM_PCR_CH0EN_Pos                       0                                   /*!< PWM PCR: CH0EN Position */
#define PWM_PCR_CH0EN_Msk                       (1ul << PWM_PCR_CH0EN_Pos)          /*!< PWM PCR: CH0EN Mask */

/* PWM CNR Bit Field Definitions */
#define PWM_CNR_CNR_Pos                         0                                   /*!< PWM CNR: CNR Position */
#define PWM_CNR_CNR_Msk                         (0xFFFFul << PWM_CNR_CNR_Pos)       /*!< PWM CNR: CNR Mask */

/* PWM CMR Bit Field Definitions */
#define PWM_CMR_CMR_Pos                         0                                   /*!< PWM CMR: CMR Position */
#define PWM_CMR_CMR_Msk                         (0xFFFFul << PWM_CMR_CMR_Pos)       /*!< PWM CMR: CMR Mask */

/* PWM PDR Bit Field Definitions */
#define PWM_PDR_PDR_Pos                         0                                   /*!< PWM PDR: PDR Position */
#define PWM_PDR_PDR_Msk                         (0xFFFFul << PWM_PDR_PDR_Pos)       /*!< PWM PDR: PDR Mask */


/* PWM PIER Bit Field Definitions */
#define PWM_PIER_INT23DTYPE_Pos                 25                                  /*!< PWM PIER: INT23DTYPE Position */
#define PWM_PIER_INT23DTYPE_Msk                 (1ul << PWM_PIER_INT23DTYPE_Pos)    /*!< PWM PIER: INT23DTYPE Mask */

#define PWM_PIER_INT01DTYPE_Pos                 24                                  /*!< PWM PIER: INT01DTYPE Position */
#define PWM_PIER_INT01DTYPE_Msk                 (1ul << PWM_PIER_INT01DTYPE_Pos)    /*!< PWM PIER: INT01DTYPE Mask */

#define PWM_PIER_INT23TYPE_Pos                  17                                  /*!< PWM PIER: INT23TYPE Position */
#define PWM_PIER_INT23TYPE_Msk                  (1ul << PWM_PIER_INT23TYPE_Pos)     /*!< PWM PIER: INT23TYPE Mask */

#define PWM_PIER_INT01TYPE_Pos                  16                                  /*!< PWM PIER: INT01TYPE Position */
#define PWM_PIER_INT01TYPE_Msk                  (1ul << PWM_PIER_INT01TYPE_Pos)     /*!< PWM PIER: INT01TYPE Mask */

#define PWM_PIER_PWMDIE3_Pos                    11                                  /*!< PWM PIER: PWMDIE3 Position */
#define PWM_PIER_PWMDIE3_Msk                    (1ul << PWM_PIER_PWMDIE3_Pos)       /*!< PWM PIER: PWMDIE3 Mask */

#define PWM_PIER_PWMDIE2_Pos                    10                                  /*!< PWM PIER: PWMDIE2 Position */
#define PWM_PIER_PWMDIE2_Msk                    (1ul << PWM_PIER_PWMDIE2_Pos)       /*!< PWM PIER: PWMDIE2 Mask */

#define PWM_PIER_PWMDIE1_Pos                    9                                   /*!< PWM PIER: PWMDIE1 Position */
#define PWM_PIER_PWMDIE1_Msk                     (1ul << PWM_PIER_PWMDIE1_Pos)      /*!< PWM PIER: PWMDIE1 Mask */

#define PWM_PIER_PWMDIE0_Pos                    8                                   /*!< PWM PIER: PWMDIE0 Position */
#define PWM_PIER_PWMDIE0_Msk                    (1ul << PWM_PIER_PWMDIE0_Pos)       /*!< PWM PIER: PWMDIE0 Mask */

#define PWM_PIER_PWMIE3_Pos                     3                                   /*!< PWM PIER: PWMIE3 Position */
#define PWM_PIER_PWMIE3_Msk                     (1ul << PWM_PIER_PWMIE3_Pos)        /*!< PWM PIER: PWMIE3 Mask */

#define PWM_PIER_PWMIE2_Pos                     2                                   /*!< PWM PIER: PWMIE2 Position */
#define PWM_PIER_PWMIE2_Msk                     (1ul << PWM_PIER_PWMIE2_Pos)        /*!< PWM PIER: PWMIE2 Mask */

#define PWM_PIER_PWMIE1_Pos                     1                                   /*!< PWM PIER: PWMIE1 Position */
#define PWM_PIER_PWMIE1_Msk                     (1ul << PWM_PIER_PWMIE1_Pos)        /*!< PWM PIER: PWMIE1 Mask */

#define PWM_PIER_PWMIE0_Pos                     0                                   /*!< PWM PIER: PWMIE0 Position */
#define PWM_PIER_PWMIE0_Msk                     (1ul << PWM_PIER_PWMIE0_Pos)        /*!< PWM PIER: PWMIE0 Mask */

/* PWM PIIR Bit Field Definitions */
#define PWM_PIIR_PWMDIF3_Pos                    11                                  /*!< PWM PIIR: PWMDIF3 Position */
#define PWM_PIIR_PWMDIF3_Msk                    (1ul << PWM_PIIR_PWMDIF3_Pos)       /*!< PWM PIIR: PWMDIF3 Mask */

#define PWM_PIIR_PWMDIF2_Pos                    10                                  /*!< PWM PIIR: PWMDIF2 Position */
#define PWM_PIIR_PWMDIF2_Msk                    (1ul << PWM_PIIR_PWMDIF2_Pos)       /*!< PWM PIIR: PWMDIF2 Mask */

#define PWM_PIIR_PWMDIF1_Pos                    9                                   /*!< PWM PIIR: PWMDIF1 Position */
#define PWM_PIIR_PWMDIF1_Msk                    (1ul << PWM_PIIR_PWMDIF1_Pos)       /*!< PWM PIIR: PWMDIF1 Mask */

#define PWM_PIIR_PWMDIF0_Pos                    8                                   /*!< PWM PIIR: PWMDIF0 Position */
#define PWM_PIIR_PWMDIF0_Msk                    (1ul << PWM_PIIR_PWMDIF0_Pos)       /*!< PWM PIIR: PWMDIF0 Mask */

#define PWM_PIIR_PWMIF3_Pos                     3                                   /*!< PWM PIIR: PWMIF3 Position */
#define PWM_PIIR_PWMIF3_Msk                     (1ul << PWM_PIIR_PWMIF3_Pos)        /*!< PWM PIIR: PWMIF3 Mask */

#define PWM_PIIR_PWMIF2_Pos                     2                                   /*!< PWM PIIR: PWMIF2 Position */
#define PWM_PIIR_PWMIF2_Msk                     (1ul << PWM_PIIR_PWMIF2_Pos)        /*!< PWM PIIR: PWMIF2 Mask */

#define PWM_PIIR_PWMIF1_Pos                     1                                   /*!< PWM PIIR: PWMIF1 Position */
#define PWM_PIIR_PWMIF1_Msk                     (1ul << PWM_PIIR_PWMIF1_Pos)        /*!< PWM PIIR: PWMIF1 Mask */

#define PWM_PIIR_PWMIF0_Pos                     0                                   /*!< PWM PIIR: PWMIF0 Position */
#define PWM_PIIR_PWMIF0_Msk                     (1ul << PWM_PIIR_PWMIF0_Pos)        /*!< PWM PIIR: PWMIF0 Mask */

/* PWM CCR0 Bit Field Definitions */
#define PWM_CCR0_CFLRI1_Pos                     23                                  /*!< PWM CCR0: CFLRI1 Position */
#define PWM_CCR0_CFLRI1_Msk                     (1ul << PWM_CCR0_CFLRI1_Pos)        /*!< PWM CCR0: CFLRI1 Mask */

#define PWM_CCR0_CRLRI1_Pos                     22                                  /*!< PWM CCR0: CRLRI1 Position */
#define PWM_CCR0_CRLRI1_Msk                     (1ul << PWM_CCR0_CRLRI1_Pos)        /*!< PWM CCR0: CRLRI1 Mask */

#define PWM_CCR0_CAPIF1_Pos                     20                                  /*!< PWM CCR0: CAPIF1 Position */
#define PWM_CCR0_CAPIF1_Msk                     (1ul << PWM_CCR0_CAPIF1_Pos)        /*!< PWM CCR0: CAPIF1 Mask */

#define PWM_CCR0_CAPCH1EN_Pos                   19                                  /*!< PWM CCR0: CAPCH1EN Position */
#define PWM_CCR0_CAPCH1EN_Msk                   (1ul << PWM_CCR0_CAPCH1EN_Pos)      /*!< PWM CCR0: CAPCH1EN Mask */

#define PWM_CCR0_CFL_IE1_Pos                    18                                  /*!< PWM CCR0: CFL_IE1 Position */
#define PWM_CCR0_CFL_IE1_Msk                    (1ul << PWM_CCR0_CFL_IE1_Pos)       /*!< PWM CCR0: CFL_IE1 Mask */

#define PWM_CCR0_CRL_IE1_Pos                    17                                  /*!< PWM CCR0: CRL_IE1 Position */
#define PWM_CCR0_CRL_IE1_Msk                    (1ul << PWM_CCR0_CRL_IE1_Pos)       /*!< PWM CCR0: CRL_IE1 Mask */

#define PWM_CCR0_INV1_Pos                       16                                  /*!< PWM CCR0: INV1 Position */
#define PWM_CCR0_INV1_Msk                       (1ul << PWM_CCR0_INV1_Pos)          /*!< PWM CCR0: INV1 Mask */

#define PWM_CCR0_CFLRI0_Pos                     7                                   /*!< PWM CCR0: CFLRI0 Position */
#define PWM_CCR0_CFLRI0_Msk                     (1ul << PWM_CCR0_CFLRI0_Pos)        /*!< PWM CCR0: CFLRI0 Mask */

#define PWM_CCR0_CRLRI0_Pos                     6                                   /*!< PWM CCR0: CRLRI0 Position */
#define PWM_CCR0_CRLRI0_Msk                     (1ul << PWM_CCR0_CRLRI0_Pos)        /*!< PWM CCR0: CRLRI0 Mask */

#define PWM_CCR0_CAPIF0_Pos                     4                                   /*!< PWM CCR0: CAPIF0 Position */
#define PWM_CCR0_CAPIF0_Msk                     (1ul << PWM_CCR0_CAPIF0_Pos)        /*!< PWM CCR0: CAPIF0 Mask */

#define PWM_CCR0_CAPCH0EN_Pos                   3                                   /*!< PWM CCR0: CAPCH0EN Position */
#define PWM_CCR0_CAPCH0EN_Msk                   (1ul << PWM_CCR0_CAPCH0EN_Pos)      /*!< PWM CCR0: CAPCH0EN Mask */

#define PWM_CCR0_CFL_IE0_Pos                    2                                   /*!< PWM CCR0: CFL_IE0 Position */
#define PWM_CCR0_CFL_IE0_Msk                    (1ul << PWM_CCR0_CFL_IE0_Pos)       /*!< PWM CCR0: CFL_IE0 Mask */

#define PWM_CCR0_CRL_IE0_Pos                    1                                   /*!< PWM CCR0: CRL_IE0 Position */
#define PWM_CCR0_CRL_IE0_Msk                    (1ul << PWM_CCR0_CRL_IE0_Pos)       /*!< PWM CCR0: CRL_IE0 Mask */

#define PWM_CCR0_INV0_Pos                       0                                   /*!< PWM CCR0: INV0 Position */
#define PWM_CCR0_INV0_Msk                       (1ul << PWM_CCR0_INV0_Pos)          /*!< PWM CCR0: INV0 Mask */

/* PWM CCR2 Bit Field Definitions */
#define PWM_CCR2_CFLRI3_Pos                     23                                  /*!< PWM CCR2: CFLRI3 Position */
#define PWM_CCR2_CFLRI3_Msk                     (1ul << PWM_CCR2_CFLRI3_Pos)        /*!< PWM CCR2: CFLRI3 Mask */

#define PWM_CCR2_CRLRI3_Pos                     22                                  /*!< PWM CCR2: CRLRI3 Position */
#define PWM_CCR2_CRLRI3_Msk                     (1ul << PWM_CCR2_CRLRI3_Pos)        /*!< PWM CCR2: CRLRI3 Mask */

#define PWM_CCR2_CAPIF3_Pos                     20                                  /*!< PWM CCR2: CAPIF3 Position */
#define PWM_CCR2_CAPIF3_Msk                     (1ul << PWM_CCR2_CAPIF3_Pos)        /*!< PWM CCR2: CAPIF3 Mask */

#define PWM_CCR2_CAPCH3EN_Pos                   19                                  /*!< PWM CCR2: CAPCH3EN Position */
#define PWM_CCR2_CAPCH3EN_Msk                   (1ul << PWM_CCR2_CAPCH3EN_Pos)      /*!< PWM CCR2: CAPCH3EN Mask */

#define PWM_CCR2_CFL_IE3_Pos                    18                                  /*!< PWM CCR2: CFL_IE3 Position */
#define PWM_CCR2_CFL_IE3_Msk                    (1ul << PWM_CCR2_CFL_IE3_Pos)       /*!< PWM CCR2: CFL_IE3 Mask */

#define PWM_CCR2_CRL_IE3_Pos                    17                                  /*!< PWM CCR2: CRL_IE3 Position */
#define PWM_CCR2_CRL_IE3_Msk                    (1ul << PWM_CCR2_CRL_IE3_Pos)       /*!< PWM CCR2: CRL_IE3 Mask */

#define PWM_CCR2_INV3_Pos                       16                                  /*!< PWM CCR2: INV3 Position */
#define PWM_CCR2_INV3_Msk                       (1ul << PWM_CCR2_INV3_Pos)          /*!< PWM CCR2: INV3 Mask */

#define PWM_CCR2_CFLRI2_Pos                     7                                   /*!< PWM CCR2: CFLRI2 Position */
#define PWM_CCR2_CFLRI2_Msk                     (1ul << PWM_CCR2_CFLRI2_Pos)        /*!< PWM CCR2: CFLRI2 Mask */

#define PWM_CCR2_CRLRI2_Pos                     6                                   /*!< PWM CCR2: CRLRI2 Position */
#define PWM_CCR2_CRLRI2_Msk                     (1ul << PWM_CCR2_CRLRI2_Pos)        /*!< PWM CCR2: CRLRI2 Mask */

#define PWM_CCR2_CAPIF2_Pos                     4                                   /*!< PWM CCR2: CAPIF2 Position */
#define PWM_CCR2_CAPIF2_Msk                     (1ul << PWM_CCR2_CAPIF2_Pos)        /*!< PWM CCR2: CAPIF2 Mask */

#define PWM_CCR2_CAPCH2EN_Pos                   3                                   /*!< PWM CCR2: CAPCH2EN Position */
#define PWM_CCR2_CAPCH2EN_Msk                   (1ul << PWM_CCR2_CAPCH2EN_Pos)      /*!< PWM CCR2: CAPCH2EN Mask */

#define PWM_CCR2_CFL_IE2_Pos                    2                                   /*!< PWM CCR2: CFL_IE2 Position */
#define PWM_CCR2_CFL_IE2_Msk                    (1ul << PWM_CCR2_CFL_IE2_Pos)       /*!< PWM CCR2: CFL_IE2 Mask */

#define PWM_CCR2_CRL_IE2_Pos                    1                                   /*!< PWM CCR2: CRL_IE2 Position */
#define PWM_CCR2_CRL_IE2_Msk                    (1ul << PWM_CCR2_CRL_IE2_Pos)       /*!< PWM CCR2: CRL_IE2 Mask */

#define PWM_CCR2_INV2_Pos                       0                                   /*!< PWM CCR2: INV2 Position */
#define PWM_CCR2_INV2_Msk                       (1ul << PWM_CCR2_INV2_Pos)          /*!< PWM CCR2: INV2 Mask */

/* PWM CRLR Bit Field Definitions */
#define PWM_CRLR_CRLR_Pos                       0                                   /*!< PWM CRLR: CRLR Position */
#define PWM_CRLR_CRLR_Msk                       (0xFFFFul << PWM_CRLR_CRLR_Pos)     /*!< PWM CRLR: CRLR Mask */

/* PWM CFLR Bit Field Definitions */
#define PWM_CFLR_CFLR_Pos                       0                                   /*!< PWM CFLR: CFLR Position */
#define PWM_CFLR_CFLR_Msk                       (0xFFFFul << PWM_CFLR_CFLR_Pos)     /*!< PWM CFLR: CFLR Mask */

/* PWM CAPENR Bit Field Definitions */
#define PWM_CAPENR_CINEN3_Pos                   3                                   /*!< PWM CAPENR: CINEN3 Position */
#define PWM_CAPENR_CINEN3_Msk                   (1ul << PWM_CAPENR_CINEN3_Pos)      /*!< PWM CAPENR: CINEN3 Mask */

#define PWM_CAPENR_CINEN2_Pos                   2                                   /*!< PWM CAPENR: CINEN2 Position */
#define PWM_CAPENR_CINEN2_Msk                   (1ul << PWM_CAPENR_CINEN2_Pos)      /*!< PWM CAPENR: CINEN2 Mask */

#define PWM_CAPENR_CINEN1_Pos                   1                                   /*!< PWM CAPENR: CINEN1 Position */
#define PWM_CAPENR_CINEN1_Msk                   (1ul << PWM_CAPENR_CINEN1_Pos)      /*!< PWM CAPENR: CINEN1 Mask */

#define PWM_CAPENR_CINEN0_Pos                   0                                   /*!< PWM CAPENR: CINEN0 Position */
#define PWM_CAPENR_CINEN0_Msk                   (1ul << PWM_CAPENR_CINEN0_Pos)      /*!< PWM CAPENR: CINEN0 Mask */

/* PWM POE Bit Field Definitions */
#define PWM_POE_PWM3_Pos                        3                                   /*!< PWM POE: POE3 Position */
#define PWM_POE_PWM3_Msk                        (1ul << PWM_POE_PWM3_Pos)           /*!< PWM POE: POE3 Mask */

#define PWM_POE_PWM2_Pos                        2                                   /*!< PWM POE: POE2 Position */
#define PWM_POE_PWM2_Msk                        (1ul << PWM_POE_PWM2_Pos)           /*!< PWM POE: POE2 Mask */

#define PWM_POE_PWM1_Pos                        1                                   /*!< PWM POE: POE1 Position */
#define PWM_POE_PWM1_Msk                        (1ul << PWM_POE_PWM1_Pos)           /*!< PWM POE: POE1 Mask */

#define PWM_POE_PWM0_Pos                        0                                   /*!< PWM POE: POE0 Position */
#define PWM_POE_PWM0_Msk                        (1ul << PWM_POE_PWM0_Pos)           /*!< PWM POE: POE0 Mask */

/* PWM TCON Bit Field Definitions */
#define PWM_TCON_PWM3DTEN_Pos                   11                                  /*!< PWM TCON: PWM3DTEN Position */
#define PWM_TCON_PWM3DTEN_Msk                   (1ul << PWM_TCON_PWM3DTEN_Pos)      /*!< PWM TCON: PWM3DTEN Mask */

#define PWM_TCON_PWM2DTEN_Pos                   10                                  /*!< PWM TCON: PWM2DTEN Position */
#define PWM_TCON_PWM2DTEN_Msk                   (1ul << PWM_TCON_PWM2DTEN_Pos)      /*!< PWM TCON: PWM2DTEN Mask */

#define PWM_TCON_PWM1DTEN_Pos                   9                                   /*!< PWM TCON: PWM1DTEN Position */
#define PWM_TCON_PWM1DTEN_Msk                   (1ul << PWM_TCON_PWM1DTEN_Pos)      /*!< PWM TCON: PWM1DTEN Mask */

#define PWM_TCON_PWM0DTEN_Pos                   8                                   /*!< PWM TCON: PWM0DTEN Position */
#define PWM_TCON_PWM0DTEN_Msk                   (1ul << PWM_TCON_PWM0DTEN_Pos)      /*!< PWM TCON: PWM0DTEN Mask */

#define PWM_TCON_PWM3TEN_Pos                    3                                   /*!< PWM TCON: PWM3TEN Position */
#define PWM_TCON_PWM3TEN_Msk                    (1ul << PWM_TCON_PWM3TEN_Pos)       /*!< PWM TCON: PWM3TEN Mask */

#define PWM_TCON_PWM2TEN_Pos                    2                                   /*!< PWM TCON: PWM2TEN Position */
#define PWM_TCON_PWM2TEN_Msk                    (1ul << PWM_TCON_PWM2TEN_Pos)       /*!< PWM TCON: PWM2TEN Mask */

#define PWM_TCON_PWM1TEN_Pos                    1                                   /*!< PWM TCON: PWM1TEN Position */
#define PWM_TCON_PWM1TEN_Msk                    (1ul << PWM_TCON_PWM1TEN_Pos)       /*!< PWM TCON: PWM1TEN Mask */

#define PWM_TCON_PWM0TEN_Pos                    0                                   /*!< PWM TCON: PWM0TEN Position */
#define PWM_TCON_PWM0TEN_Msk                    (1ul << PWM_TCON_PWM0TEN_Pos)       /*!< PWM TCON: PWM0TEN Mask */

/* PWM TSTATUS Bit Field Definitions */
#define PWM_TSTATUS_PWM3TF_Pos                  3                                   /*!< PWM TSTATUS: PWM3TF Position */
#define PWM_TSTATUS_PWM3TF_Msk                  (1ul << PWM_TSTATUS_PWM3TF_Pos)     /*!< PWM TSTATUS: PWM3TF Mask */

#define PWM_TSTATUS_PWM2TF_Pos                  2                                   /*!< PWM TSTATUS: PWM2TF Position */
#define PWM_TSTATUS_PWM2TF_Msk                  (1ul << PWM_TSTATUS_PWM2TF_Pos)     /*!< PWM TSTATUS: PWM2TF Mask */

#define PWM_TSTATUS_PWM1TF_Pos                  1                                   /*!< PWM TSTATUS: PWM1TF Position */
#define PWM_TSTATUS_PWM1TF_Msk                  (1ul << PWM_TSTATUS_PWM1TF_Pos)     /*!< PWM TSTATUS: PWM1TF Mask */

#define PWM_TSTATUS_PWM0TF_Pos                  0                                   /*!< PWM TSTATUS: PWM0TF Position */
#define PWM_TSTATUS_PWM0TF_Msk                  (1ul << PWM_TSTATUS_PWM0TF_Pos)     /*!< PWM TSTATUS: PWM0TF Mask */

/* PWM PSCR Bit Field Definitions */
#define PWM_PSCR_PSSEN3_Pos                     24                                  /*!< PWM PSCR: PSSEN3 Position */
#define PWM_PSCR_PSSEN3_Msk                     (1ul << PWM_PSCR_PSSEN3_Pos)        /*!< PWM PSCR: PSSEN3 Mask */

#define PWM_PSCR_PSSEN2_Pos                     16                                  /*!< PWM PSCR: PSSEN2 Position */
#define PWM_PSCR_PSSEN2_Msk                     (1ul << PWM_PSCR_PSSEN2_Pos)        /*!< PWM PSCR: PSSEN2 Mask */

#define PWM_PSCR_PSSEN1_Pos                     8                                   /*!< PWM PSCR: PSSEN1 Position */
#define PWM_PSCR_PSSEN1_Msk                     (1ul << PWM_PSCR_PSSEN1_Pos)        /*!< PWM PSCR: PSSEN1 Mask */

#define PWM_PSCR_PSSEN0_Pos                     0                                   /*!< PWM PSCR: PSSEN0 Position */
#define PWM_PSCR_PSSEN0_Msk                     (1ul << PWM_PSCR_PSSEN0_Pos)        /*!< PWM PSCR: PSSEN0 Mask */
/**@}*/ /* PWM_CONST */
/**@}*/ /* PWM */




/*------------------------- SPI Interface Controller -------------------------*/
/** @addtogroup SPI SPI Controller(SPI)
  Memory Mapped Structure for SPI Controller
  @{
 */
typedef struct
{
    /**
     * CNTRL
     * ===================================================================================================
     * Offset: 0x00  SPI Control and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GO_BUSY   |Go and Busy Status
     * |        |          |1 = In master mode, writing 1 to this bit to start the SPI data transfer; in slave
     * |        |          |mode, writing 1 to this bit indicates that the slave is ready to communicate with a
     * |        |          |master.
     * |        |          |0 = Writing 0 to this bit to stop data transfer if SPI is transferring.
     * |        |          |During the data transfer, this bit keeps the value of 1. As the transfer is finished, this bit will
     * |        |          |be cleared automatically.
     * |        |          |NOTE: All registers should be set before writing 1 to this GO_BUSY bit. The
     * |        |          |transfer result will be unpredictable if software changes related settings when
     * |        |          |GO_BUSY bit is 1.
     * |[1]     |RX_NEG    |Receive At Negative Edge
     * |        |          |1 = The received data input signal is latched at the falling edge of SPICLK.
     * |        |          |0 = The received data input signal is latched at the rising edge of SPICLK.
     * |[2]     |TX_NEG    |Transmit At Negative Edge
     * |        |          |1 = The transmitted data output signal is changed at the falling edge of SPICLK.
     * |        |          |0 = The transmitted data output signal is changed at the rising edge of SPICLK.
     * |[7:3]   |TX_BIT_LEN|Transmit Bit Length
     * |        |          |This field specifies how many bits are transmitted in one transaction. Up to 32 bits
     * |        |          |can be transmitted.
     * |        |          |TX_BIT_LEN = 0x01 ... 1 bit
     * |        |          |TX_BIT_LEN = 0x02 ... 2 bits
     * |        |          |......
     * |        |          |TX_BIT_LEN = 0x1f ... 31 bits
     * |        |          |TX_BIT_LEN = 0x00 .. 32 bits
     * |[10]    |LSB       |LSB First
     * |        |          |1 = The LSB is sent first on the line (bit 0 of SPI_TX0/1), and the first bit received
     * |        |          |from the line will be put in the LSB position of the RX register (bit 0 of SPI_RX0/1).
     * |        |          |0 = The MSB is transmitted/received first (which bit in SPI_TX0/1 and SPI_RX0/1
     * |        |          |register that is depends on the TX_BIT_LEN field).
     * |[11]    |CLKP      |Clock Polarity
     * |        |          |1 = SPICLK idle high.
     * |        |          |0 = SPICLK idle low.
     * |[15:12] |SP_CYCLE  |Suspend Interval (master only)
     * |        |          |These four bits provide configurable suspend interval between two successive
     * |        |          |transmit/receive transactions in a transfer. The suspend interval is from the last
     * |        |          |falling clock edge of the current transaction to the first rising clock edge of the
     * |        |          |successive transaction if CLKP = 0. If CLKP = 1, the interval is from the rising clock
     * |        |          |edge to the falling clock edge. The default value is 0x0. When TX_NUM = 00b,
     * |        |          |setting this field has no effect on transfer. The desired suspend interval is obtained
     * |        |          |according to the following equation:
     * |        |          |(SP_CYCLE[3:0] + 2)*period of SPI clock
     * |        |          |SP_CYCLE = 0x0 ... 2 SPICLK clock cycle
     * |        |          |SP_CYCLE = 0x1 ... 3 SPICLK clock cycle
     * |        |          |......
     * |        |          |SP_CYCLE = 0xe ... 16 SPICLK clock cycle
     * |        |          |SP_CYCLE = 0xf ... 17 SPICLK clock cycle
     * |[16]    |IF        |Interrupt Flag
     * |        |          |1 = It indicates that the transfer is done. The interrupt flag is set if it was enable.
     * |        |          |0 = It indicates that the transfer does not finish yet.
     * |        |          |NOTE: This bit can be cleared by writing 1 to itself.
     * |[17]    |IE        |Interrupt Enable
     * |        |          |1 = Enable MICROWIRE/SPI Interrupt.
     * |        |          |0 = Disable MICROWIRE/SPI Interrupt.
     * |[18]    |SLAVE     |SLAVE Mode Indication
     * |        |          |1 = Slave mode.
     * |        |          |0 = Master mode.
     * |[19]    |REORDER   |Reorder Mode Select
     * |        |          |0 = Disable byte reorder function.
     * |        |          |1 = Enable byte reorder function.
     * |        |          |Byte reorder function is only available if TX_BIT_LEN is defined as 16, 24 and 32.
     */
    __IO uint32_t CNTRL;

    /**
     * DIVIDER
     * ===================================================================================================
     * Offset: 0x04  SPI Clock Divider Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DIVIDER   |Clock Divider Register
     */
    __IO uint32_t DIVIDER;

    /**
     * SSR
     * ===================================================================================================
     * Offset: 0x08  SPI Slave Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SSR       |Slave Select Register (master only)
     * |        |          |If AUTOSS bit is cleared, writing 1 to this bit sets the SPISSx line to active state and
     * |        |          |writing 0 sets the line back to inactive state.
     * |        |          |If AUTOSS bit is set, writing 1 to this bit will select the SPISSx line to be automatically
     * |        |          |driven to active state for the duration of the transmit/receive, and will be driven to
     * |        |          |inactive state for the rest of the time. (The active level of SPISSx0/1 is specified in
     * |        |          |SS_LVL).
     * |[2]     |SS_LVL    |Slave Select Active Level
     * |        |          |It defines the active level of slave select signal (SPISSx).
     * |        |          |1 = The slave select signal SPISSx is active at high-level/rising-edge.
     * |        |          |0 = The slave select signal SPISSx is active at low-level/falling-edge.
     * |[3]     |AUTOSS    |Automatic Slave Select (master only)
     * |        |          |1 = If this bit is set, SPISSx signal is generated automatically. It means that slave
     * |        |          |select signal will be asserted by the SPI controller when transmit/receive is started by
     * |        |          |setting GO_BUSY, and is de-asserted after each transmit/receive is finished.
     * |        |          |0 = If this bit is cleared, slave select signal will be asserted and de-asserted by setting
     * |        |          |and clearing SSR[0].
     * |[4]     |SS_LTRIG  |Slave Select Level Trigger (slave only)
     * |        |          |1: The slave select signal will be level-trigger. It depends on SS_LVL to decide the
     * |        |          |signal is active low or active high.
     * |        |          |0: The input slave select signal is edge-trigger. This is default value.
     * |[5]     |LTRIG_FLAG|Level Trigger Flag
     * |        |          |When the SS_LTRIG bit is set in slave mode, this bit can be read to indicate the
     * |        |          |received bit number is met the requirement or not.
     * |        |          |1 = The transaction number and the transferred bit length met the specified
     * |        |          |requirements which defined in TX_NUM and TX_BIT_LEN.
     * |        |          |0 = The transaction number or the transferred bit length of one transaction doesn't
     * |        |          |meet the specified requirements.
     * |        |          |Note: This bit is READ only
     */
    __IO uint32_t SSR;

    /**
     * RESERVE0
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE0;

    /**
     * SPI_RX0, SPI_RX1
     * ===================================================================================================
     * Offset: 0x10, 0x14  Data Receive Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RX        |Data Receive Register
     * |        |          |The Data Receive Registers hold the value of received data of the last executed transfer. The
     * |        |          |number of valid bits depend on the transmit bit length field in the SPI_CNTRL register. For
     * |        |          |example, if TX_BIT_LEN is set to 0x08 and TX_NUM is set to 0x0, bit RX0[7:0] holds the
     * |        |          |received data.
     * |        |          |NOTE: The Data Receive Registers are read only registers.
     */
    __I  uint32_t RX0;

    /**
     * RESERVE1
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE1[2];

    /**
     * RESERVE2
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE2;

    /**
     * SPI_TX0, SPI_TX1
     * ===================================================================================================
     * Offset: 0x20, 0x24  Data Transmit Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |TX        |Data Transmit Register
     * |        |          |The Data Transmit Registers hold the data to be transmitted in the next transfer. The number
     * |        |          |of valid bits depend on the transmit bit length field in the CNTRL register.
     * |        |          |For example, if TX_BIT_LEN is set to 0x08 and the TX_NUM is set to 0x0, the bit TX0[7:0] will be
     * |        |          |transmitted in next transfer. If TX_BIT_LEN is set to 0x00 and TX_NUM is set to 0x1, the core will
     * |        |          |perform two successive 32-bit transmit/receive using the same setting (the order is TX0[31:0],
     * |        |          |TX1[31:0]).
     */
    __O  uint32_t TX0;

    /**
     * RESERVE3
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE3[2];

    /**
     * RESERVE4
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE4;

    /**
     * RESERVE5
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE5;

    /**
     * RESERVE6
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE6;

    /**
     * RESERVE7
     * ===================================================================================================
     *
     * ---------------------------------------------------------------------------------------------------
     */
    __I  uint32_t RESERVE7;

    /**
     * CNTRL2
     * ===================================================================================================
     * Offset: 0x3C  SPI Control and Status Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8]     |NOSLVSEL  |Slave 3-Wire Mode Enable Bit
     * |        |          |This is used to ignore the slave select signal in slave mode.
     * |        |          |The SPI controller can work with 3-wire interface including SPICLK, SPI_MISO, and SPI_MOSI.
     * |        |          |0 = 4-wire bi-direction interface.
     * |        |          |1 = 3-wire bi-direction interface.
     * |        |          |Note: In 3-wire mode, the SS_LTRIG, SPI_SSR[4], shall be set as 1.
     * |[9]     |SLV_ABORT |Slave 3-Wire Mode Abort Control Bit
     * |        |          |In normal operation, there is an interrupt event when the received data meet the required bits which defined in TX_BIT_LEN.
     * |        |          |If the received bits are less than the requirement and there is no more serial clock input over the one transfer time in slave 3-wire mode,
     * |        |          |the user can set this bit to force the current transfer done and then the user can get a transfer done interrupt event.
     * |        |          |Note: It will be cleared to 0 automatically by hardware after the software sets this bit to 1.
     * |[10]    |SSTA_INTEN|Slave 3-Wire Mode Start Interrupt Enable
     * |        |          |It is used to enable interrupt when the transfer has started in slave 3-wire mode.
     * |        |          |If there is no transfer done interrupt over the time period which is defined by user after the transfer start,
     * |        |          |the user can set the SLV_ABORT bit to force the transfer done.
     * |        |          |1 = Enable the transaction start interrupt. It will be cleared to 0 as the current transfer is done or the SLV_START_INTSTS bit is cleared.
     * |        |          |0 = Disable the transfer start interrupt.
     * |[11]    |SLV_START_INTSTS|Slave 3-Wire Mode Start Interrupt Status
     * |        |          |It is used to dedicate that the transfer has started in slave 3-wire mode.
     * |        |          |1 = It indicates that the transfer has started in slave 3-wire mode. It will be cleared to 0 as transfer done or by writing one to this bit.
     * |        |          |0 = It indicates that the SPI transfer is not active.
     * |[16]    |SS_INT_OPT|Slave Select Inactive Interrupt Option
     * |        |          |This setting is only available if the SPI controller is configured as level trigger slave device.
     * |        |          |1 = As the slave select signal goes to inactive level, the IF bit will be set to 1.
     * |        |          |0 = As the slave select signal goes to inactive level, the IF bit will NOT be set to 1.
     * |[31]    |BCn       |SPI Engine Clock Backward Compatible Option
     * |        |          |1 = The clock configuration is not backward compatible.
     * |        |          |0 = Backward compatible clock configuration.
     */
    __IO uint32_t CNTRL2;

    /**
     * FIFO_CTL
     * ===================================================================================================
     * Offset: 0x40  SPI FIFO Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RX_CLR    |Clear Receive FIFO Buffer
     * |        |          |0 = No effect.
     * |        |          |1 = Clear receive FIFO buffer. The RX_FULL flag will be cleared to 0 and the RX_EMPTY flag will be set to 1.
     * |        |          |This bit will be cleared to 0 by hardware after software sets it to 1.
     * |[1]     |TX_CLR    |Clear Transmit FIFO Buffer
     * |        |          |0 = No effect.
     * |        |          |1 = Clear transmit FIFO buffer. The TX_FULL flag will be cleared to 0 and the TX_EMPTY flag will be set to 1.
     * |        |          |This bit will be cleared to 0 by hardware after software sets it to 1.
     * |[2]     |RX_INTEN  |Receive Threshold Interrupt Enable
     * |        |          |0 = Disable receive threshold interrupt
     * |        |          |1 = Enable receive threshold interrupt
     * |[3]     |TX_INTEN  |Transmit Threshold Interrupt Enable
     * |        |          |0 = Disable transmit threshold interrupt
     * |        |          |1 = Enable transmit threshold interrupt
     * |[6]     |RXOV_INTEN|Receive FIFO Overrun Interrupt Enable
     * |        |          |1 = Enable Receive FIFO overrun interrupt.
     * |        |          |0 = Disable Receive FIFO overrun interrupt
     * |[21]    |TIMEOUT_INTEN|Receive FIFO Time-out Interrupt Enable
     * |        |          |1 = Enable time-out interrupt.
     * |        |          |0 = Disable time-out interrupt.
     * |[25:24] |RX_THRESHOLD |Received FIFO Threshold
     * |        |          |If the valid data count of the receive FIFO buffer is larger than the RX_THRESHOLD setting,
     * |        |          |the RX_INTSTS bit will be set to 1, else the RX_INTSTS bit will be cleared to 0.
     * |[29:28] |RX_THRESHOLD |Transmit FIFO Threshold
     * |        |          |If the valid data count of the transmit FIFO buffer is less than or equal to the TX_THRESHOLD setting,
     * |        |          |the TX_INTSTS bit will be set to 1, else the TX_INTSTS bit will be cleared to 0.
     */
    __IO uint32_t FIFO_CTL;

    /**
     * STATUS
     * ===================================================================================================
     * Offset: 0x44  SPI Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RX_INTSTS |Receive FIFO Threshold Interrupt Status (read only)
     * |        |          |1 = It indicates that the valid data count within the receive FIFO buffer is larger than the setting value of RX_THRESHOLD.
     * |        |          |0 = It indicates that the valid data count within the Rx FIFO buffer is smaller than or equal to the setting value of RX_THRESHOLD.
     * |        |          |Note: If RX_INTEN = 1 and RX_INTSTS = 1, the SPI controller will generate a SPI interrupt request.
     * |[2]     |RX_OVERRUN|Receive FIFO Overrun Status
     * |        |          |When the receive FIFO buffer is full, the follow-up data will be dropped and this bit will be set to 1.
     * |        |          |Note: This bit will be cleared by writing 1 to itself.
     * |[4]     |TX_INTSTS |Transmit FIFO Threshold Interrupt Status (read only)
     * |        |          |1 = It indicates that the valid data count within the transmit FIFO buffer is less than or equal to the setting value of TX_THRESHOLD.
     * |        |          |0 = It indicates that the valid data count within the transmit FIFO buffer is larger than the setting value of TX_THRESHOLD.
     * |        |          |Note: If TX_INTEN = 1 and TX_INTSTS = 1, the SPI controller will generate a SPI interrupt request.
     * |[11]    |SLV_START_INTSTS|Slave Start Interrupt Status
     * |        |          |It is used to dedicate that the transfer has started in slave 3-wire mode. It's a mutual mirror bit of SPI_CNTRL2[11].
     * |        |          |1 = It indicates that the transfer has started in slave 3-wire mode. It will be cleared as transfer done or by writing one to this bit.
     * |        |          |0 = It indicates that the transfer is not started.
     * |[15:12] |RX_FIFO_COUNT   |Receive FIFO Data Count (read only)
     * |        |          |Indicates the valid data count of receive FIFO buffer.
     * |[16]    |IF        |SPI Unit Transfer Interrupt Flag
     * |        |          |It's a mutual mirror bit of SPI_CNTRL[16].
     * |        |          |1 = It indicates that the SPI controller has finished one unit transfer.
     * |        |          |0 = It indicates that the transfer does not finish yet.
     * |        |          |Note: This bit will be cleared by writing 1 to itself.
     * |[20]    |TIMEOUT   |Time-out Interrupt Flag
     * |        |          |1 = It indicates that the receive FIFO buffer is not empty and there is not be read over 64 SPI clock period in master mode and over 576 SPI engine clock period in slave mode. When the received FIFO buffer is read by software, the time-out status will be cleared automatically.
     * |        |          |0 = No receive FIFO time-out event.
     * |        |          |Note: This bit will be cleared by writing 1 to itself.
     * |[24]    |RX_EMPTY  |Receive FIFO Buffer Empty Indicator (read only)
     * |        |          |It's a mutual mirror bit of SPI_CNTRL[24].
     * |        |          |1 = Indicates that the receive FIFO buffer is empty
     * |        |          |0 = Indicates that the receive FIFO buffer is not empty
     * |[25]    |RX_FULL   |Receive FIFO Buffer Full Indicator (read only)
     * |        |          |It's a mutual mirror bit of SPI_CNTRL[25].
     * |        |          |1 = Indicates that the receive FIFO buffer is full
     * |        |          |0 = Indicates that the receive FIFO buffer is not full
     * |[26]    |TX_EMPTY  |Transmit FIFO Buffer Empty Indicator (read only)
     * |        |          |It's a mutual mirror bit of SPI_CNTRL[26].
     * |        |          |1 = Indicates that the transmit FIFO buffer is empty
     * |        |          |0 = Indicates that the transmit FIFO buffer is not empty
     * |[27]    |TX_FULL   |Transmit FIFO Buffer Full Indicator (read only)
     * |        |          |It's a mutual mirror bit of SPI_CNTRL[27].
     * |        |          |1 = Indicates that the transmit FIFO buffer is full
     * |        |          |0 = Indicates that the transmit FIFO buffer is not full
     * |[31:28] |TX_FIFO_COUNT   |Transmit FIFO Data Count (read only)
     * |        |          |Indicates the valid data count of transmit FIFO buffer.
     */
    __IO uint32_t STATUS;

} SPI_T;

/** @addtogroup SPI_CONST SPI Bit Field Definition
  Constant Definitions for SPI Controller
  @{
 */

/* SPI_CNTRL Bit Field Definitions */
#define SPI_CNTRL_TX_FULL_Pos      27                                     /*!< SPI CNTRL: TX_FULL Position */
#define SPI_CNTRL_TX_FULL_Msk      (1ul << SPI_CNTRL_TX_FULL_Pos)         /*!< SPI CNTRL: TX_FULL Mask     */

#define SPI_CNTRL_TX_EMPTY_Pos     26                                     /*!< SPI CNTRL: TX_EMPTY Position */
#define SPI_CNTRL_TX_EMPTY_Msk     (1ul << SPI_CNTRL_TX_EMPTY_Pos)        /*!< SPI CNTRL: TX_EMPTY Mask     */

#define SPI_CNTRL_RX_FULL_Pos      25                                     /*!< SPI CNTRL: RX_FULL Position */
#define SPI_CNTRL_RX_FULL_Msk      (1ul << SPI_CNTRL_RX_FULL_Pos)         /*!< SPI CNTRL: RX_FULL Mask     */

#define SPI_CNTRL_RX_EMPTY_Pos     24                                     /*!< SPI CNTRL: RX_EMPTY Position */
#define SPI_CNTRL_RX_EMPTY_Msk     (1ul << SPI_CNTRL_RX_EMPTY_Pos)        /*!< SPI CNTRL: RX_EMPTY Mask     */

#define SPI_CNTRL_FIFO_Pos         21                                     /*!< SPI CNTRL: FIFO Position */
#define SPI_CNTRL_FIFO_Msk         (1ul << SPI_CNTRL_FIFO_Pos)            /*!< SPI CNTRL: FIFO Mask     */

#define SPI_CNTRL_REORDER_Pos      19                                     /*!< SPI CNTRL: REORDER Position */
#define SPI_CNTRL_REORDER_Msk      (3ul << SPI_CNTRL_REORDER_Pos)         /*!< SPI CNTRL: REORDER Mask     */

#define SPI_CNTRL_SLAVE_Pos        18                                     /*!< SPI CNTRL: SLAVE Position */
#define SPI_CNTRL_SLAVE_Msk        (1ul << SPI_CNTRL_SLAVE_Pos)           /*!< SPI CNTRL: SLAVE Mask     */

#define SPI_CNTRL_IE_Pos           17                                     /*!< SPI CNTRL: IE Position */
#define SPI_CNTRL_IE_Msk           (1ul << SPI_CNTRL_IE_Pos)              /*!< SPI CNTRL: IE Mask     */

#define SPI_CNTRL_IF_Pos           16                                     /*!< SPI CNTRL: IF Position */
#define SPI_CNTRL_IF_Msk           (1ul << SPI_CNTRL_IF_Pos)              /*!< SPI CNTRL: IF Mask     */

#define SPI_CNTRL_SP_CYCLE_Pos     12                                     /*!< SPI CNTRL: SP_CYCLE Position */
#define SPI_CNTRL_SP_CYCLE_Msk     (0xFul << SPI_CNTRL_SP_CYCLE_Pos)      /*!< SPI CNTRL: SP_CYCLE Mask     */

#define SPI_CNTRL_CLKP_Pos         11                                     /*!< SPI CNTRL: CLKP Position */
#define SPI_CNTRL_CLKP_Msk         (1ul << SPI_CNTRL_CLKP_Pos)            /*!< SPI CNTRL: CLKP Mask     */

#define SPI_CNTRL_LSB_Pos          10                                     /*!< SPI CNTRL: LSB Position */
#define SPI_CNTRL_LSB_Msk          (1ul << SPI_CNTRL_LSB_Pos)             /*!< SPI CNTRL: LSB Mask     */

#define SPI_CNTRL_TX_BIT_LEN_Pos   3                                      /*!< SPI CNTRL: TX_BIT_LEN Position */
#define SPI_CNTRL_TX_BIT_LEN_Msk   (0x1Ful << SPI_CNTRL_TX_BIT_LEN_Pos)   /*!< SPI CNTRL: TX_BIT_LEN Mask     */

#define SPI_CNTRL_TX_NEG_Pos       2                                      /*!< SPI CNTRL: TX_NEG Position */
#define SPI_CNTRL_TX_NEG_Msk       (1ul << SPI_CNTRL_TX_NEG_Pos)          /*!< SPI CNTRL: TX_NEG Mask     */

#define SPI_CNTRL_RX_NEG_Pos       1                                      /*!< SPI CNTRL: RX_NEG Position */
#define SPI_CNTRL_RX_NEG_Msk       (1ul << SPI_CNTRL_RX_NEG_Pos)          /*!< SPI CNTRL: RX_NEG Mask     */

#define SPI_CNTRL_GO_BUSY_Pos      0                                      /*!< SPI CNTRL: GO_BUSY Position */
#define SPI_CNTRL_GO_BUSY_Msk      (1ul << SPI_CNTRL_GO_BUSY_Pos)         /*!< SPI CNTRL: GO_BUSY Mask     */

/* SPI_DIVIDER Bit Field Definitions */
#define SPI_DIVIDER_DIVIDER2_Pos   16                                     /*!< SPI DIVIDER: DIVIDER2 Position */
#define SPI_DIVIDER_DIVIDER2_Msk   (0xFFFFul << SPI_DIVIDER_DIVIDER2_Pos) /*!< SPI DIVIDER: DIVIDER2 Mask */

#define SPI_DIVIDER_DIVIDER_Pos    0                                      /*!< SPI DIVIDER: DIVIDER Position */
#define SPI_DIVIDER_DIVIDER_Msk    (0xFFFFul << SPI_DIVIDER_DIVIDER_Pos)  /*!< SPI DIVIDER: DIVIDER Mask */

/* SPI_SSR Bit Field Definitions */
#define SPI_SSR_LTRIG_FLAG_Pos     5                                 /*!< SPI SSR: LTRIG_FLAG Position */
#define SPI_SSR_LTRIG_FLAG_Msk     (1ul << SPI_SSR_LTRIG_FLAG_Pos)   /*!< SPI SSR: LTRIG_FLAG Mask */

#define SPI_SSR_SS_LTRIG_Pos       4                                 /*!< SPI SSR: SS_LTRIG Position */
#define SPI_SSR_SS_LTRIG_Msk       (1ul << SPI_SSR_SS_LTRIG_Pos)     /*!< SPI SSR: SS_LTRIG Mask */

#define SPI_SSR_AUTOSS_Pos         3                                 /*!< SPI SSR: AUTOSS Position */
#define SPI_SSR_AUTOSS_Msk         (1ul << SPI_SSR_AUTOSS_Pos)       /*!< SPI SSR: AUTOSS Mask */

#define SPI_SSR_SS_LVL_Pos         2                                 /*!< SPI SSR: SS_LVL Position */
#define SPI_SSR_SS_LVL_Msk         (1ul << SPI_SSR_SS_LVL_Pos)       /*!< SPI SSR: SS_LVL Mask */

#define SPI_SSR_SSR_Pos            0                                 /*!< SPI SSR: SSR Position */
#define SPI_SSR_SSR_Msk            (1ul << SPI_SSR_SSR_Pos)          /*!< SPI SSR: SSR Mask */

/* SPI_CNTRL2 Bit Field Definitions */
#define SPI_CNTRL2_BCn_Pos                31                                         /*!< SPI CNTRL2: BCn Position */
#define SPI_CNTRL2_BCn_Msk                (1ul << SPI_CNTRL2_BCn_Pos)                /*!< SPI CNTRL2: BCn Mask */

#define SPI_CNTRL2_SS_INT_OPT_Pos         16                                         /*!< SPI CNTRL2: SS_INT_OPT Position */
#define SPI_CNTRL2_SS_INT_OPT_Msk         (1ul << SPI_CNTRL2_SS_INT_OPT_Pos)         /*!< SPI CNTRL2: SS_INT_OPT Mask */

#define SPI_CNTRL2_SLV_START_INTSTS_Pos   11                                         /*!< SPI CNTRL2: SLV_START_INTSTS Position */
#define SPI_CNTRL2_SLV_START_INTSTS_Msk   (1ul << SPI_CNTRL2_SLV_START_INTSTS_Pos)   /*!< SPI CNTRL2: SLV_START_INTSTS Mask */

#define SPI_CNTRL2_SSTA_INTEN_Pos         10                                         /*!< SPI CNTRL2: SSTA_INTEN Position */
#define SPI_CNTRL2_SSTA_INTEN_Msk         (1ul << SPI_CNTRL2_SSTA_INTEN_Pos)         /*!< SPI CNTRL2: SSTA_INTEN Mask */

#define SPI_CNTRL2_SLV_ABORT_Pos          9                                          /*!< SPI CNTRL2: SLV_ABORT Position */
#define SPI_CNTRL2_SLV_ABORT_Msk          (1ul << SPI_CNTRL2_SLV_ABORT_Pos)          /*!< SPI CNTRL2: SLV_ABORT Mask */

#define SPI_CNTRL2_NOSLVSEL_Pos           8                                          /*!< SPI CNTRL2: NOSLVSEL Position */
#define SPI_CNTRL2_NOSLVSEL_Msk           (1ul << SPI_CNTRL2_NOSLVSEL_Pos)           /*!< SPI CNTRL2: NOSLVSEL Mask */

#define SPI_CNTRL2_DIV_ONE_Pos            0                                          /*!< SPI CNTRL2: DIV_ONE Position */
#define SPI_CNTRL2_DIV_ONE_Msk            (1ul << SPI_CNTRL2_DIV_ONE_Pos)            /*!< SPI CNTRL2: DIV_ONE Mask */

/* SPI_FIFO_CTL Bit Field Definitions */
#define SPI_FIFO_CTL_TX_THRESHOLD_Pos     28                                         /*!< SPI FIFO_CTL: TX_THRESHOLD Position */
#define SPI_FIFO_CTL_TX_THRESHOLD_Msk     (3ul << SPI_FIFO_CTL_TX_THRESHOLD_Pos)     /*!< SPI FIFO_CTL: TX_THRESHOLD Mask */

#define SPI_FIFO_CTL_RX_THRESHOLD_Pos     24                                         /*!< SPI FIFO_CTL: RX_THRESHOLD Position */
#define SPI_FIFO_CTL_RX_THRESHOLD_Msk     (3ul << SPI_FIFO_CTL_RX_THRESHOLD_Pos)     /*!< SPI FIFO_CTL: RX_THRESHOLD Mask */

#define SPI_FIFO_CTL_TIMEOUT_INTEN_Pos    21                                         /*!< SPI FIFO_CTL: TIMEOUT_INTEN Position */
#define SPI_FIFO_CTL_TIMEOUT_INTEN_Msk    (1ul << SPI_FIFO_CTL_TIMEOUT_INTEN_Pos)    /*!< SPI FIFO_CTL: TIMEOUT_INTEN Mask */

#define SPI_FIFO_CTL_RXOV_INTEN_Pos       6                                          /*!< SPI FIFO_CTL: RXOV_INTEN Position */
#define SPI_FIFO_CTL_RXOV_INTEN_Msk       (1ul << SPI_FIFO_CTL_RXOV_INTEN_Pos)       /*!< SPI FIFO_CTL: RXOV_INTEN Mask */

#define SPI_FIFO_CTL_TX_INTEN_Pos         3                                          /*!< SPI FIFO_CTL: TX_INTEN Position */
#define SPI_FIFO_CTL_TX_INTEN_Msk         (1ul << SPI_FIFO_CTL_TX_INTEN_Pos)         /*!< SPI FIFO_CTL: TX_INTEN Mask */

#define SPI_FIFO_CTL_RX_INTEN_Pos         2                                          /*!< SPI FIFO_CTL: RX_INTEN Position */
#define SPI_FIFO_CTL_RX_INTEN_Msk         (1ul << SPI_FIFO_CTL_RX_INTEN_Pos)         /*!< SPI FIFO_CTL: RX_INTEN Mask */

#define SPI_FIFO_CTL_TX_CLR_Pos           1                                          /*!< SPI FIFO_CTL: TX_CLR Position */
#define SPI_FIFO_CTL_TX_CLR_Msk           (1ul << SPI_FIFO_CTL_TX_CLR_Pos)           /*!< SPI FIFO_CTL: TX_CLR Mask */

#define SPI_FIFO_CTL_RX_CLR_Pos           0                                          /*!< SPI FIFO_CTL: RX_CLR Position */
#define SPI_FIFO_CTL_RX_CLR_Msk           (1ul << SPI_FIFO_CTL_RX_CLR_Pos)           /*!< SPI FIFO_CTL: RX_CLR Mask */

/* SPI_STATUS Bit Field Definitions */
#define SPI_STATUS_TX_FIFO_COUNT_Pos      28                                         /*!< SPI STATUS: TX_FIFO_COUNT Position */
#define SPI_STATUS_TX_FIFO_COUNT_Msk      (0xFul << SPI_STATUS_TX_FIFO_COUNT_Pos)    /*!< SPI STATUS: TX_FIFO_COUNT Mask */

#define SPI_STATUS_TX_FULL_Pos            27                                         /*!< SPI STATUS: TX_FULL Position */
#define SPI_STATUS_TX_FULL_Msk            (1ul << SPI_STATUS_TX_FULL_Pos)            /*!< SPI STATUS: TX_FULL Mask */

#define SPI_STATUS_TX_EMPTY_Pos           26                                         /*!< SPI STATUS: TX_EMPTY Position */
#define SPI_STATUS_TX_EMPTY_Msk           (1ul << SPI_STATUS_TX_EMPTY_Pos)           /*!< SPI STATUS: TX_EMPTY Mask */

#define SPI_STATUS_RX_FULL_Pos            25                                         /*!< SPI STATUS: RX_FULL Position */
#define SPI_STATUS_RX_FULL_Msk            (1ul << SPI_STATUS_RX_FULL_Pos)            /*!< SPI STATUS: RX_FULL Mask */

#define SPI_STATUS_RX_EMPTY_Pos           24                                         /*!< SPI STATUS: RX_EMPTY Position */
#define SPI_STATUS_RX_EMPTY_Msk           (1ul << SPI_STATUS_RX_EMPTY_Pos)           /*!< SPI STATUS: RX_EMPTY Mask */

#define SPI_STATUS_TIMEOUT_Pos            20                                         /*!< SPI STATUS: TIMEOUT Position */
#define SPI_STATUS_TIMEOUT_Msk            (1ul << SPI_STATUS_TIMEOUT_Pos)            /*!< SPI STATUS: TIMEOUT Mask */

#define SPI_STATUS_IF_Pos                 16                                         /*!< SPI STATUS: IF Position */
#define SPI_STATUS_IF_Msk                 (1ul << SPI_STATUS_IF_Pos)                 /*!< SPI STATUS: IF Mask     */

#define SPI_STATUS_RX_FIFO_COUNT_Pos      12                                         /*!< SPI STATUS: RX_FIFO_COUNT Position */
#define SPI_STATUS_RX_FIFO_COUNT_Msk      (0xFul << SPI_STATUS_RX_FIFO_COUNT_Pos)    /*!< SPI STATUS: RX_FIFO_COUNT Mask */

#define SPI_STATUS_SLV_START_INTSTS_Pos   11                                         /*!< SPI STATUS: SLV_START_INTSTS Position */
#define SPI_STATUS_SLV_START_INTSTS_Msk   (1ul << SPI_STATUS_SLV_START_INTSTS_Pos)   /*!< SPI STATUS: SLV_START_INTSTS Mask */

#define SPI_STATUS_TX_INTSTS_Pos          4                                          /*!< SPI STATUS: TX_INTSTS Position */
#define SPI_STATUS_TX_INTSTS_Msk          (1ul << SPI_STATUS_TX_INTSTS_Pos)          /*!< SPI STATUS: TX_INTSTS Mask */

#define SPI_STATUS_RX_OVERRUN_Pos         2                                          /*!< SPI STATUS: RX_OVERRUN Position */
#define SPI_STATUS_RX_OVERRUN_Msk         (1ul << SPI_STATUS_RX_OVERRUN_Pos)         /*!< SPI STATUS: RX_OVERRUN Mask */

#define SPI_STATUS_RX_INTSTS_Pos          0                                          /*!< SPI STATUS: RX_INTSTS Position */
#define SPI_STATUS_RX_INTSTS_Msk          (1ul << SPI_STATUS_RX_INTSTS_Pos)          /*!< SPI STATUS: RX_INTSTS Mask */
/**@}*/ /* SPI_CONST */
/**@}*/ /* SPI */




/*---------------------------- Clock Controller ------------------------------*/

/** @addtogroup CLK System Clock Controller(CLK)
  Memory Mapped Structure for System Clock Controller
  @{
 */

typedef struct
{
    /**
     * PWRCON
     * ===================================================================================================
     * Offset: 0x00  System Power Down Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field       |Descriptions
     * | :----: | :----:     | :---- |
     * |[0]     |XTL12M_EN   |External Crystal Oscillator Control
     * |        |            |The bit default value is set by flash controller user configuration register config0 [26:24].
     * |        |            |When the default clock source is from external crystal. The bit is auto set to "1"
     * |        |            |1 = Crystal oscillation enable
     * |        |            |0 = Crystal oscillation disable
     * |[2]     |OSC22M_EN   |Internal 22.1184 MHz Oscillator Control
     * |        |            |1 = 22.1184 MHz Oscillation enable
     * |        |            |0 = 22.1184 MHz Oscillation disable
     * |[3]     |OSC10K_EN   |Internal 10KHz Oscillator Control
     * |        |            |1 = 10KHz Oscillation enable
     * |        |            |0 = 10KHz Oscillation disable
     * |[4]     |PD_WU_DLY   |Enable the wake up delay counter.
     * |        |            |When the chip wakes up from power down mode, the clock control will delay certain clock
     * |        |            |cycles to wait system clock stable.
     * |        |            |The delayed clock cycle is 4096 clock cycles when chip work at external crystal (4 ~
     * |        |            |24MHz), and 256 clock cycles when chip work at 22.1184 MHz oscillator.
     * |        |            |1 = Enable the clock cycle delay
     * |        |            |0 = Disable the clock cycle delay
     * |[5]     |PD_WU_INT_EN|Power down mode wake Up Interrupt Enable
     * |        |            |0 = Disable
     * |        |            |1 = Enable. The interrupt will occur when Power down mode (Deep Sleep Mode) wakeup.
     * |[6]     |PD_WU_STS   |Chip power down wake up status flag
     * |        |            |Set by "power down wake up", it indicates that resume from power down mode
     * |        |            |The flag is set if the GPIO(P0~P4), UART wakeup
     * |        |            |Write 1 to clear the bit
     * |        |            |Note: This bit is working only if PD_WU_INT_EN (PWRCON[5]) set to 1.
     * |[7]     |PWR_DOWN_EN |System power down enable bit
     * |        |            |When set this bit "1", the chip power down mode is enabled and the chip power down active
     * |        |            |is depend on the PD_WAIT_CPU bit
     * |        |            |(a) if the PD_WAIT_CPU is "0" then the chip power down after the PWR_DOWN_EN bit set.
     * |        |            |(b) if the PD_WAIT_CPU is "1" then the chip keep active till the CPU sleep mode also active
     * |        |            |and then the chip power down
     * |        |            |When chip wake up from power down, this bit is auto cleared, user need to set this bit again
     * |        |            |for next power down.
     * |        |            |When in power down mode, external crystal (4~ 24MHz) and the 22.1184 MHz OSC will be
     * |        |            |disabled in this mode, but the 10 kHz OSC is not controlled by power down mode.
     * |        |            |When in power down mode, the PLL and system clock are disabled, and ignored the clock
     * |        |            |source selection. The clocks of peripheral are not controlled by power down mode, if the
     * |        |            |peripheral clock source is from 10 kHz oscillator.
     * |        |            |1 = Chip enter the power down mode instant or wait CPU sleep command WFI
     * |        |            |0 = Chip operate in normal mode or CPU in idle mode (sleep mode) because of WFI
     * |        |            |command
     * |[8]     |PD_WAIT_CPU |This bit control the power down entry condition
     * |        |            |1 = Chip entry power down mode when the both PWR_DOWN and CPU run WFI instruction.
     * |        |            |0 = Chip entry power down mode when the PWR_DOWN bit is set to 1
     */
    __IO uint32_t PWRCON;

    /**
     * AHBCLK
     * ===================================================================================================
     * Offset: 0x04  AHB Devices Clock Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |ISP_EN    |Flash ISP Controller Clock Enable Control.
     * |        |          |1 = To enable the Flash ISP controller clock.
     * |        |          |0 = To disable the Flash ISP controller clock.
     * |[3]     |EBI_EN    |EBI Controller Clock Enable Control.
     * |        |          |1 = To enable the EBI Controller clock.
     * |        |          |0 = To disable the EBI Controller clock.
     * |[4]     |HDIV_EN   |Divider Controller Clock Enable Control.
     * |        |          |1 = To enable the Divider Controller clock.
     * |        |          |0 = To disable the Divider Controller clock.
     */
    __IO uint32_t AHBCLK;

    /**
     * APBCLK
     * ===================================================================================================
     * Offset: 0x08  APB Devices Clock Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDT_EN    |Watch Dog Timer Clock Enable.
     * |        |          |This bit is the protected bit, program this need a open lock sequence, write "59h","16h","88h" to
     * |        |          |address 0x5000_0100 to un-lock this bit. Reference the register REGWRPROT at address
     * |        |          |GCR_BA + 0x100
     * |        |          |0 = Disable Watchdog Timer Clock
     * |        |          |1 = Enable Watchdog Timer Clock
     * |[2]     |TMR0_EN   |Timer0 Clock Enable Control
     * |        |          |0 = Disable Timer0 Clock
     * |        |          |1 = Enable Timer0 Clock
     * |[3]     |TMR1_EN   |Timer1 Clock Enable Control
     * |        |          |0 = Disable Timer1 Clock
     * |        |          |1 = Enable Timer1 Clock
     * |[4]     |TMR2_EN   |Timer2 Clock Enable Control
     * |        |          |0 = Disable Timer2 Clock
     * |        |          |1 = Enable Timer2 Clock
     * |[5]     |TMR3_EN   |Timer3 Clock Enable Control
     * |        |          |0 = Disable Timer3 Clock
     * |        |          |1 = Enable Timer3 Clock
     * |[6]     |FDIV_EN   |Clock Divider Clock Enable Control
     * |        |          |0 = Disable FDIV Clock
     * |        |          |1 = Enable FDIV Clock
     * |[8]     |I2C_EN    |I2C Clock Enable Control.
     * |        |          |0 = Disable I2C Clock
     * |        |          |1 = Enable I2C Clock
     * |[12]    |SPI0_EN   |SPI0 Clock Enable Control.
     * |        |          |0 = Disable SPI0 Clock
     * |        |          |1 = Enable SPI0 Clock
     * |[13]    |SPI1_EN   |SPI1 Clock Enable Control.
     * |        |          |0 = Disable SPI1 Clock
     * |        |          |1 = Enable SPI1 Clock
     * |[16]    |UART0_EN  |UART0 Clock Enable Control.
     * |        |          |1 = Enable UART0 clock
     * |        |          |0 = Disable UART0 clock
     * |[17]    |UART1_EN  |UART1 Clock Enable Control.
     * |        |          |1 = Enable UART1 clock
     * |        |          |0 = Disable UART1 clock
     * |[20]    |PWM01_EN  |PWM_01 Clock Enable Control.
     * |        |          |1 = Enable PWM01 clock
     * |        |          |0 = Disable PWM01 clock
     * |[21]    |PWM23_EN  |PWM_23 Clock Enable Control.
     * |        |          |1 = Enable PWM23 clock
     * |        |          |0 = Disable PWM23 clock
     * |[22]    |PWM45_EN  |PWM_45 Clock Enable Control.
     * |        |          |1 = Enable PWM45 clock
     * |        |          |0 = Disable PWM45 clock
     * |[23]    |PWM67_EN  |PWM_67 Clock Enable Control.
     * |        |          |1 = Enable PWM67 clock
     * |        |          |0 = Disable PWM67 clock
     * |[28]    |ADC_EN    |Analog-Digital-Converter (ADC) Clock Enable Control.
     * |        |          |1 = Enable ADC clock
     * |        |          |0 = Disable ADC clock
     */
    __IO uint32_t APBCLK;

    /**
     * CLKSTATUS
     * ===================================================================================================
     * Offset: 0x0C  Clock Status Monitor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field      |Descriptions
     * | :----: | :----:    | :---- |
     * |[0]     |XTL12M_STB |XTL12M clock source stable flag
     * |        |           |1 = External Crystal clock is stable
     * |        |           |0 = External Crystal clock is not stable or not enable
     * |[2]     |PLL_STB    |PLL clock source stable flag
     * |        |           |1 = PLL clock is stable
     * |        |           |0 = PLL clock is not stable or not enable
     * |[3]     |OSC10K_STB |OSC10K clock source stable flag
     * |        |           |1 = OSC10K clock is stable
     * |        |           |0 = OSC10K clock is not stable or not enable
     * |[4]     |OSC22M_STB |OSC22M clock source stable flag
     * |        |           |1 = OSC22M clock is stable
     * |        |           |0 = OSC22M clock is not stable or not enable
     * |[7]     |CLK_SW_FAIL|Clock switch fail flag
     * |        |           |1 = Clock switch fail
     * |        |           |0 = Clock switch success
     * |        |           |This bit will be set when target switch clock source is not stable. Write 1 to clear this bit to zero.
     */
    __IO uint32_t CLKSTATUS;

    /**
     * CLKSEL0
     * ===================================================================================================
     * Offset: 0x10  Clock Source Select Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |HCLK_S    |HCLK clock source select.
     * |        |          |Note:
     * |        |          |1.  Before clock switch the related clock sources (pre-select and new-select) must be turn on
     * |        |          |2.  The 3-bit default value is reloaded with the value of Config0.CFOSC[26:24] in user
     * |        |          |configuration register in Flash controller by any reset. Therefore the default value is either
     * |        |          |000b or 111b.
     * |        |          |3.  These bits are protected bit, program this need an open lock sequence, write
     * |        |          |"59h","16h","88h" to address 0x5000_0100 to un-lock this bit. Reference the register
     * |        |          |REGWRPROT at address GCR_BA + 0x100
     * |        |          |000 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |010 = clock source from PLL clock
     * |        |          |011 = clock source from internal 10KHz oscillator clock
     * |        |          |111 = clock source from internal 22.1184 MHz oscillator clock
     * |        |          |others = Reserved
     * |[5:3]   |STCLK_S   |MCU Cortex_M0 SysTick clock source select.
     * |        |          |These bits are protected bit, program this need an open lock sequence, write "59h","16h","88h" to
     * |        |          |address 0x5000_0100 to un-lock this bit. Reference the register REGWRPROT at address GCR_BA
     * |        |          |+ 0x100
     * |        |          |000 = Clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |010 = Clock source from external crystal clock (4 ~ 24MHz)/2
     * |        |          |011 = clock source from HCLK/2
     * |        |          |1xx = clock source from internal 22.1184 MHz oscillator clock/2
     */
    __IO uint32_t CLKSEL0;

    /**
     * CLKSEL1
     * ===================================================================================================
     * Offset: 0x14  Clock Source Select Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |WDT_S     |Watchdog Timer clock source select.
     * |        |          |These bits are protected bit, program this need a open lock sequence, write "59h","16h","88h" to
     * |        |          |address 0x5000_0100 to un-lock this bit. Reference the register REGWRPROT at address
     * |        |          |GCR_BA + 0x100
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz).
     * |        |          |10 = clock source from HCLK/2048 clock
     * |        |          |11 = clock source from internal 10KHz oscillator clock
     * |[3:2]   |ADC_S     |ADC clock source select.
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz).
     * |        |          |01 = clock source from PLL clock
     * |        |          |1x = clock source from internal 22.1184 MHz oscillator clock
     * |[10:8]  |TMR0_S    |TIMER0 clock source select.
     * |        |          |000 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |010 = clock source from HCLK
     * |        |          |011 = clock source from external trigger
     * |        |          |1xx = clock source from internal 22.1184 MHz oscillator clock
     * |[14:12] |TMR1_S    |TIMER1 clock source select.
     * |        |          |000 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |010 = clock source from HCLK
     * |        |          |011 = clock source from external trigger
     * |        |          |1xx = clock source from internal 22.1184 MHz oscillator clock
     * |[18:16] |TMR2_S    |TIMER2 clock source select.
     * |        |          |000 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |010 = clock source from HCLK
     * |        |          |011 = clock source from external trigger
     * |        |          |1xx = clock source from internal 22.1184 MHz oscillator clock
     * |[22:20] |TMR3_S    |TIMER3 clock source select.
     * |        |          |000 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |010 = clock source from HCLK
     * |        |          |011 = clock source from external trigger
     * |        |          |1xx = clock source from internal 22.1184 MHz oscillator clock
     * |[25:24] |UART_S    |UART clock source select.
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |01 = clock source from PLL clock
     * |        |          |1x = clock source from internal 22.1184 MHz oscillator clock
     * |[29:28] |PWM01_S   |PWM0 and PWM1 clock source select.
     * |        |          |PWM0 and PWM1 uses the same Engine clock source, both of them with the same pre-scalar
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |10 = clock source from HCLK
     * |        |          |11 = clock source from internal 22.1184 MHz oscillator clock
     * |[31:30] |PWM23_S   |PWM2 and PWM3 clock source select.
     * |        |          |PWM2 and PWM3 uses the same Engine clock source, both of them with the same pre-scalar
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |10 = clock source from HCLK
     * |        |          |11 = clock source from internal 22.1184 MHz oscillator clock
     */
    __IO uint32_t CLKSEL1;

    /**
     * CLKDIV
     * ===================================================================================================
     * Offset: 0x18  Clock Divider Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |HCLK_N    |HCLK clock divide number from HCLK clock source
     * |        |          |The HCLK clock frequency = (HCLK clock source frequency) / (HCLK_N + 1)
     * |[11:8]  |UART_N    |UART clock divide number from UART clock source
     * |        |          |The UART clock frequency = (UART clock source frequency ) / (UART_N + 1)
     * |[23:16] |ADC_N     |ADC clock divide number from ADC clock source
     * |        |          |The ADC clock frequency = (ADC clock source frequency ) / (ADC_N + 1)
     */
    __IO uint32_t CLKDIV;

    /**
     * CLKSEL2
     * ===================================================================================================
     * Offset: 0x1C  Clock Source Select Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:2]   |FRQDIV_S  |Clock Divider Clock Source Select
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |10 = clock source from HCLK
     * |        |          |11 = clock source from internal 22.1184 MHz oscillator clock
     * |[5:4]   |PWM45_S   |PWM4 and PWM5 clock source select. - PWM4 and PWM5 used the same Engine clock source,
     * |        |          |both of them with the same pre-scalar
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |10 = clock source from HCLK
     * |        |          |11 = clock source from internal 22.1184 MHz oscillator clock
     * |[7:6]   |PWM67_S   |PWM6 and PWM7 clock source select. - PWM6 and PWM7 used the same Engine clock source,
     * |        |          |both of them with the same pre-scalar
     * |        |          |00 = clock source from external crystal clock (4 ~ 24MHz)
     * |        |          |10 = clock source from HCLK
     * |        |          |11 = clock source from internal 22.1184 MHz oscillator clock
     */
    __IO uint32_t CLKSEL2;

    /**
     * PLLCON
     * ===================================================================================================
     * Offset: 0x20  PLL Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |FB_DV     |PLL Feedback Divider Control Pins (PLL_F[8:0])
     * |[13:9]  |IN_DV     |PLL Input Divider Control Pins (PLL_R[4:0])
     * |[15:14] |OUT_DV    |PLL Output Divider Control Pins (PLL_OD[1:0])
     * |[16]    |PD        |Power Down Mode.
     * |        |          |If set the IDLE bit "1" in PWRCON register, the PLL will enter power down mode too
     * |        |          |0 = PLL is in normal mode (default)
     * |        |          |1 = PLL is in power-down mode
     * |[17]    |BP        |PLL Bypass Control
     * |        |          |0 = PLL is in normal mode (default)
     * |        |          |1 = PLL clock output is same as clock input (XTALin)
     * |[18]    |OE        |PLL OE (FOUT enable) pin Control
     * |        |          |0 = PLL FOUT enable
     * |        |          |1 = PLL FOUT is fixed low
     * |[19]    |PLL_SRC   |PLL Source Clock Select
     * |        |          |1 = PLL source clock from 22.1184 MHz oscillator
     * |        |          |0 = PLL source clock from external crystal clock (4 ~ 24 MHz)
     */
    __IO uint32_t PLLCON;

    /**
     * FRQDIV
     * ===================================================================================================
     * Offset: 0x24  Frequency Divider Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |FSEL      |Divider Output Frequency Selection Bits
     * |        |          |The formula of output frequency is
     * |        |          |Fout = Fin/2(N+1),
     * |        |          |where Fin is the input clock frequency, Fout is the frequency of divider output clock, N is the 4-bit
     * |        |          |value of FSEL[3:0].
     * |[4]     |DIVIDER_EN|Frequency Divider Enable Bit
     * |        |          |0 = Disable Frequency Divider
     * |        |          |1 = Enable Frequency Divider
     */
    __IO uint32_t FRQDIV;

} CLK_T;

/** @addtogroup CLK_CONST CLK Bit Field Definition
  Constant Definitions for CLK Controller
  @{
 */

/* CLK PWRCON Bit Field Definitions */
#define CLK_PWRCON_PD_WAIT_CPU_Pos           8                                    /*!< CLK PWRCON: PD_WAIT_CPU Position */
#define CLK_PWRCON_PD_WAIT_CPU_Msk           (1ul << CLK_PWRCON_PD_WAIT_CPU_Pos)  /*!< CLK PWRCON: PD_WAIT_CPU Mask */

#define CLK_PWRCON_PWR_DOWN_EN_Pos           7                                    /*!< CLK PWRCON: PWR_DOWN_EN Position */
#define CLK_PWRCON_PWR_DOWN_EN_Msk           (1ul << CLK_PWRCON_PWR_DOWN_EN_Pos)  /*!< CLK PWRCON: PWR_DOWN_EN Mask */

#define CLK_PWRCON_PD_WU_STS_Pos             6                                    /*!< CLK PWRCON: PD_WU_STS Position */
#define CLK_PWRCON_PD_WU_STS_Msk             (1ul << CLK_PWRCON_PD_WU_STS_Pos)    /*!< CLK PWRCON: PD_WU_STS Mask */

#define CLK_PWRCON_PD_WU_INT_EN_Pos          5                                    /*!< CLK PWRCON: PD_WU_INT_EN Position */
#define CLK_PWRCON_PD_WU_INT_EN_Msk          (1ul << CLK_PWRCON_PD_WU_INT_EN_Pos) /*!< CLK PWRCON: PD_WU_INT_EN Mask */

#define CLK_PWRCON_PD_WU_DLY_Pos             4                                    /*!< CLK PWRCON: PD_WU_DLY Position */
#define CLK_PWRCON_PD_WU_DLY_Msk             (1ul << CLK_PWRCON_PD_WU_DLY_Pos)    /*!< CLK PWRCON: PD_WU_DLY Mask */

#define CLK_PWRCON_OSC10K_EN_Pos             3                                    /*!< CLK PWRCON: OSC10K_EN Position */
#define CLK_PWRCON_OSC10K_EN_Msk             (1ul << CLK_PWRCON_OSC10K_EN_Pos)    /*!< CLK PWRCON: OSC10K_EN Mask */
#define CLK_PWRCON_IRC10K_EN_Pos             3                                    /*!< CLK PWRCON: OSC10K_EN Position */
#define CLK_PWRCON_IRC10K_EN_Msk             (1ul << CLK_PWRCON_OSC10K_EN_Pos)    /*!< CLK PWRCON: OSC10K_EN Mask */

#define CLK_PWRCON_OSC22M_EN_Pos             2                                    /*!< CLK PWRCON: OSC22M_EN Position */
#define CLK_PWRCON_OSC22M_EN_Msk             (1ul << CLK_PWRCON_OSC22M_EN_Pos)    /*!< CLK PWRCON: OSC22M_EN Mask */
#define CLK_PWRCON_IRC22M_EN_Pos             2                                    /*!< CLK PWRCON: OSC22M_EN Position */
#define CLK_PWRCON_IRC22M_EN_Msk             (1ul << CLK_PWRCON_OSC22M_EN_Pos)    /*!< CLK PWRCON: OSC22M_EN Mask */

#define CLK_PWRCON_XTL12M_EN_Pos             0                                    /*!< CLK PWRCON: XTL12M_EN Position */
#define CLK_PWRCON_XTL12M_EN_Msk             (1ul << CLK_PWRCON_XTL12M_EN_Pos)    /*!< CLK PWRCON: XTL12M_EN Mask */

/* CLK AHBCLK Bit Field Definitions */
#define CLK_AHBCLK_HDIV_EN_Pos               4                                    /*!< CLK AHBCLK: HDIV_EN Position */
#define CLK_AHBCLK_HDIV_EN_Msk               (1ul << CLK_AHBCLK_HDIV_EN_Pos)      /*!< CLK AHBCLK: HDIV_EN Mask */

#define CLK_AHBCLK_EBI_EN_Pos                3                                    /*!< CLK AHBCLK: EBI_EN Position */
#define CLK_AHBCLK_EBI_EN_Msk                (1ul << CLK_AHBCLK_EBI_EN_Pos)       /*!< CLK AHBCLK: EBI_EN Mask */

#define CLK_AHBCLK_ISP_EN_Pos                2                                    /*!< CLK AHBCLK: ISP_EN Position */
#define CLK_AHBCLK_ISP_EN_Msk                (1ul << CLK_AHBCLK_ISP_EN_Pos)       /*!< CLK AHBCLK: ISP_EN Mask */

/* CLK APBCLK Bit Field Definitions */
#define CLK_APBCLK_ACMP23_EN_Pos             31                                   /*!< CLK APBCLK: ACMP23_EN Position */
#define CLK_APBCLK_ACMP23_EN_Msk             (1ul << CLK_APBCLK_ACMP23_EN_Pos)    /*!< CLK APBCLK: ACMP23_EN Mask */

#define CLK_APBCLK_ACMP01_EN_Pos             30                                   /*!< CLK APBCLK: ACMP01_EN Position */
#define CLK_APBCLK_ACMP01_EN_Msk             (1ul << CLK_APBCLK_ACMP01_EN_Pos)    /*!< CLK APBCLK: ACMP01_EN Mask */

#define CLK_APBCLK_ADC_EN_Pos                28                                   /*!< CLK APBCLK: ADC_EN Position */
#define CLK_APBCLK_ADC_EN_Msk                (1ul << CLK_APBCLK_ADC_EN_Pos)       /*!< CLK APBCLK: ADC_EN Mask */

#define CLK_APBCLK_PWM67_EN_Pos              23                                   /*!< CLK APBCLK: PWM67_EN Position */
#define CLK_APBCLK_PWM67_EN_Msk              (1ul << CLK_APBCLK_PWM67_EN_Pos)     /*!< CLK APBCLK: PWM67_EN Mask */

#define CLK_APBCLK_PWM45_EN_Pos              22                                   /*!< CLK APBCLK: PWM45_EN Position */
#define CLK_APBCLK_PWM45_EN_Msk              (1ul << CLK_APBCLK_PWM45_EN_Pos)     /*!< CLK APBCLK: PWM45_EN Mask */

#define CLK_APBCLK_PWM23_EN_Pos              21                                   /*!< CLK APBCLK: PWM23_EN Position */
#define CLK_APBCLK_PWM23_EN_Msk              (1ul << CLK_APBCLK_PWM23_EN_Pos)     /*!< CLK APBCLK: PWM23_EN Mask */

#define CLK_APBCLK_PWM01_EN_Pos              20                                   /*!< CLK APBCLK: PWM01_EN Position */
#define CLK_APBCLK_PWM01_EN_Msk              (1ul << CLK_APBCLK_PWM01_EN_Pos)     /*!< CLK APBCLK: PWM01_EN Mask */

#define CLK_APBCLK_UART1_EN_Pos              17                                   /*!< CLK APBCLK: UART1_EN Position */
#define CLK_APBCLK_UART1_EN_Msk              (1ul << CLK_APBCLK_UART1_EN_Pos)     /*!< CLK APBCLK: UART1_EN Mask */

#define CLK_APBCLK_UART0_EN_Pos              16                                   /*!< CLK APBCLK: UART0_EN Position */
#define CLK_APBCLK_UART0_EN_Msk              (1ul << CLK_APBCLK_UART0_EN_Pos)     /*!< CLK APBCLK: UART0_EN Mask */

#define CLK_APBCLK_SPI1_EN_Pos               13                                   /*!< CLK APBCLK: SPI1_EN Position */
#define CLK_APBCLK_SPI1_EN_Msk               (1ul << CLK_APBCLK_SPI1_EN_Pos)      /*!< CLK APBCLK: SPI1_EN Mask */

#define CLK_APBCLK_SPI0_EN_Pos               12                                   /*!< CLK APBCLK: SPI0_EN Position */
#define CLK_APBCLK_SPI0_EN_Msk               (1ul << CLK_APBCLK_SPI0_EN_Pos)      /*!< CLK APBCLK: SPI0_EN Mask */

#define CLK_APBCLK_I2C1_EN_Pos               9                                    /*!< CLK APBCLK: I2C1_EN Position */
#define CLK_APBCLK_I2C1_EN_Msk               (1ul << CLK_APBCLK_I2C1_EN_Pos)      /*!< CLK APBCLK: I2C1_EN Mask */

#define CLK_APBCLK_I2C0_EN_Pos               8                                    /*!< CLK APBCLK: I2C0_EN Position */
#define CLK_APBCLK_I2C0_EN_Msk               (1ul << CLK_APBCLK_I2C0_EN_Pos)      /*!< CLK APBCLK: I2C0_EN Mask */
#define CLK_APBCLK_I2C_EN_Pos                8                                    /*!< CLK APBCLK: I2C_EN Position */
#define CLK_APBCLK_I2C_EN_Msk                (1ul << CLK_APBCLK_I2C_EN_Pos)       /*!< CLK APBCLK: I2C_EN Mask */

#define CLK_APBCLK_FDIV_EN_Pos               6                                    /*!< CLK APBCLK: FDIV_EN Position */
#define CLK_APBCLK_FDIV_EN_Msk               (1ul << CLK_APBCLK_FDIV_EN_Pos)      /*!< CLK APBCLK: FDIV_EN Mask */

#define CLK_APBCLK_TMR3_EN_Pos               5                                    /*!< CLK APBCLK: TMR3_EN Position */
#define CLK_APBCLK_TMR3_EN_Msk               (1ul << CLK_APBCLK_TMR3_EN_Pos)      /*!< CLK APBCLK: TMR3_EN Mask */

#define CLK_APBCLK_TMR2_EN_Pos               4                                    /*!< CLK APBCLK: TMR2_EN Position */
#define CLK_APBCLK_TMR2_EN_Msk               (1ul << CLK_APBCLK_TMR2_EN_Pos)      /*!< CLK APBCLK: TMR2_EN Mask */

#define CLK_APBCLK_TMR1_EN_Pos               3                                    /*!< CLK APBCLK: TMR1_EN Position */
#define CLK_APBCLK_TMR1_EN_Msk               (1ul << CLK_APBCLK_TMR1_EN_Pos)      /*!< CLK APBCLK: TMR1_EN Mask */

#define CLK_APBCLK_TMR0_EN_Pos               2                                    /*!< CLK APBCLK: TMR0_EN Position */
#define CLK_APBCLK_TMR0_EN_Msk               (1ul << CLK_APBCLK_TMR0_EN_Pos)      /*!< CLK APBCLK: TMR0_EN Mask */

#define CLK_APBCLK_WDT_EN_Pos                0                                    /*!< CLK APBCLK: WDT_EN Position */
#define CLK_APBCLK_WDT_EN_Msk                (1ul << CLK_APBCLK_WDT_EN_Pos)       /*!< CLK APBCLK: WDT_EN Mask */

/* CLK CLKSTATUS Bit Field Definitions */
#define CLK_CLKSTATUS_CLK_SW_FAIL_Pos        7                                     /*!< CLK CLKSTATUS: CLK_SW_FAIL Position */
#define CLK_CLKSTATUS_CLK_SW_FAIL_Msk        (1ul << CLK_CLKSTATUS_CLK_SW_FAIL_Pos)/*!< CLK CLKSTATUS: CLK_SW_FAIL Mask */

#define CLK_CLKSTATUS_OSC22M_STB_Pos         4                                    /*!< CLK CLKSTATUS: OSC22M_STB Position */
#define CLK_CLKSTATUS_OSC22M_STB_Msk         (1ul << CLK_CLKSTATUS_OSC22M_STB_Pos)/*!< CLK CLKSTATUS: OSC22M_STB Mask */
#define CLK_CLKSTATUS_IRC22M_STB_Pos         4                                    /*!< CLK CLKSTATUS: IRC22M_STB Position */
#define CLK_CLKSTATUS_IRC22M_STB_Msk         (1ul << CLK_CLKSTATUS_IRC22M_STB_Pos)/*!< CLK CLKSTATUS: IRC22M_STB Mask */

#define CLK_CLKSTATUS_OSC10K_STB_Pos         3                                    /*!< CLK CLKSTATUS: OSC10K_STB Position */
#define CLK_CLKSTATUS_OSC10K_STB_Msk         (1ul << CLK_CLKSTATUS_OSC10K_STB_Pos)/*!< CLK CLKSTATUS: OSC10K_STB Mask */
#define CLK_CLKSTATUS_IRC10K_STB_Pos         3                                    /*!< CLK CLKSTATUS: IRC10K_STB Position */
#define CLK_CLKSTATUS_IRC10K_STB_Msk         (1ul << CLK_CLKSTATUS_IRC10K_STB_Pos)/*!< CLK CLKSTATUS: IRC10K_STB Mask */

#define CLK_CLKSTATUS_PLL_STB_Pos            2                                    /*!< CLK CLKSTATUS: PLL_STB Position */
#define CLK_CLKSTATUS_PLL_STB_Msk            (1ul << CLK_CLKSTATUS_PLL_STB_Pos)   /*!< CLK CLKSTATUS: PLL_STB Mask */

#define CLK_CLKSTATUS_XTL12M_STB_Pos         0                                    /*!< CLK CLKSTATUS: XTL12M_STB Position */
#define CLK_CLKSTATUS_XTL12M_STB_Msk         (1ul << CLK_CLKSTATUS_XTL12M_STB_Pos)/*!< CLK CLKSTATUS: XTL12M_STB Mask */

/* CLK CLKSEL0 Bit Field Definitions */
#define CLK_CLKSEL0_STCLK_S_Pos              3                                    /*!< CLK CLKSEL0: STCLK_S Position */
#define CLK_CLKSEL0_STCLK_S_Msk              (7ul << CLK_CLKSEL0_STCLK_S_Pos)     /*!< CLK CLKSEL0: STCLK_S Mask */

#define CLK_CLKSEL0_HCLK_S_Pos               0                                    /*!< CLK CLKSEL0: HCLK_S Position */
#define CLK_CLKSEL0_HCLK_S_Msk               (7ul << CLK_CLKSEL0_HCLK_S_Pos)      /*!< CLK CLKSEL0: HCLK_S Mask */

/* CLK CLKSEL1 Bit Field Definitions */
#define CLK_CLKSEL1_PWM23_S_Pos              30                                   /*!< CLK CLKSEL1: PWM23_S Position */
#define CLK_CLKSEL1_PWM23_S_Msk              (3ul << CLK_CLKSEL1_PWM23_S_Pos)     /*!< CLK CLKSEL1: PWM23_S Mask */

#define CLK_CLKSEL1_PWM01_S_Pos              28                                   /*!< CLK CLKSEL1: PWM01_S Position */
#define CLK_CLKSEL1_PWM01_S_Msk              (3ul << CLK_CLKSEL1_PWM01_S_Pos)     /*!< CLK CLKSEL1: PWM01_S Mask */

#define CLK_CLKSEL1_UART_S_Pos               24                                   /*!< CLK CLKSEL1: UART_S Position */
#define CLK_CLKSEL1_UART_S_Msk               (3ul << CLK_CLKSEL1_UART_S_Pos)      /*!< CLK CLKSEL1: UART_S Mask */

#define CLK_CLKSEL1_TMR3_S_Pos               20                                   /*!< CLK CLKSEL1: TMR3_S Position */
#define CLK_CLKSEL1_TMR3_S_Msk               (7ul << CLK_CLKSEL1_TMR3_S_Pos)      /*!< CLK CLKSEL1: TMR3_S Mask */

#define CLK_CLKSEL1_TMR2_S_Pos               16                                   /*!< CLK CLKSEL1: TMR2_S Position */
#define CLK_CLKSEL1_TMR2_S_Msk               (7ul << CLK_CLKSEL1_TMR2_S_Pos)      /*!< CLK CLKSEL1: TMR2_S Mask */

#define CLK_CLKSEL1_TMR1_S_Pos               12                                   /*!< CLK CLKSEL1: TMR1_S Position */
#define CLK_CLKSEL1_TMR1_S_Msk               (7ul << CLK_CLKSEL1_TMR1_S_Pos)      /*!< CLK CLKSEL1: TMR1_S Mask */

#define CLK_CLKSEL1_TMR0_S_Pos               8                                    /*!< CLK CLKSEL1: TMR0_S Position */
#define CLK_CLKSEL1_TMR0_S_Msk               (7ul << CLK_CLKSEL1_TMR0_S_Pos)      /*!< CLK CLKSEL1: TMR0_S Mask */

#define CLK_CLKSEL1_SPI1_S_Pos               5                                    /*!< CLK CLKSEL1: SPI1_S Position */
#define CLK_CLKSEL1_SPI1_S_Msk               (1ul << CLK_CLKSEL1_SPI1_S_Pos)      /*!< CLK CLKSEL1: SPI1_S Mask */

#define CLK_CLKSEL1_SPI0_S_Pos               4                                    /*!< CLK CLKSEL1: SPI0_S Position */
#define CLK_CLKSEL1_SPI0_S_Msk               (1ul << CLK_CLKSEL1_SPI0_S_Pos)      /*!< CLK CLKSEL1: SPI0_S Mask */

#define CLK_CLKSEL1_ADC_S_Pos                2                                    /*!< CLK CLKSEL1: ADC_S Position */
#define CLK_CLKSEL1_ADC_S_Msk                (3ul << CLK_CLKSEL1_ADC_S_Pos)       /*!< CLK CLKSEL1: ADC_S Mask */

#define CLK_CLKSEL1_WDT_S_Pos                0                                    /*!< CLK CLKSEL1: WDT_S Position */
#define CLK_CLKSEL1_WDT_S_Msk                (3ul << CLK_CLKSEL1_WDT_S_Pos)       /*!< CLK CLKSEL1: WDT_S Mask */

/* CLK CLKSEL2 Bit Field Definitions */
#define CLK_CLKSEL2_WWDT_S_Pos               16                                   /*!< CLK CLKSEL2: WWDT_S Position */
#define CLK_CLKSEL2_WWDT_S_Msk               (3ul << CLK_CLKSEL2_WWDT_S_Pos)      /*!< CLK CLKSEL2: WWDT_S Mask */

#define CLK_CLKSEL2_PWM67_S_Pos              6                                    /*!< CLK CLKSEL2: PWM67_S Position */
#define CLK_CLKSEL2_PWM67_S_Msk              (3ul << CLK_CLKSEL2_PWM67_S_Pos)     /*!< CLK CLKSEL2: PWM67_S Mask */

#define CLK_CLKSEL2_PWM45_S_Pos              4                                    /*!< CLK CLKSEL2: PWM45_S Position */
#define CLK_CLKSEL2_PWM45_S_Msk              (3ul << CLK_CLKSEL2_PWM45_S_Pos)     /*!< CLK CLKSEL2: PWM45_S Mask */

#define CLK_CLKSEL2_FRQDIV_S_Pos             2                                    /*!< CLK CLKSEL2: FRQDIV_S Position */
#define CLK_CLKSEL2_FRQDIV_S_Msk             (3ul << CLK_CLKSEL2_FRQDIV_S_Pos)    /*!< CLK CLKSEL2: FRQDIV_S Mask */

/* CLK CLKDIV Bit Field Definitions */
#define CLK_CLKDIV_ADC_N_Pos                 16                                   /*!< CLK CLKDIV: ADC_N Position */
#define CLK_CLKDIV_ADC_N_Msk                 (0xFFul << CLK_CLKDIV_ADC_N_Pos)     /*!< CLK CLKDIV: ADC_N Mask */

#define CLK_CLKDIV_UART_N_Pos                8                                    /*!< CLK CLKDIV: UART_N Position */
#define CLK_CLKDIV_UART_N_Msk                (0xFul << CLK_CLKDIV_UART_N_Pos)     /*!< CLK CLKDIV: UART_N Mask */

#define CLK_CLKDIV_HCLK_N_Pos                0                                    /*!< CLK CLKDIV: HCLK_N Position */
#define CLK_CLKDIV_HCLK_N_Msk                (0xFul << CLK_CLKDIV_HCLK_N_Pos)     /*!< CLK CLKDIV: HCLK_N Mask */

/* CLK PLLCON Bit Field Definitions */
#define CLK_PLLCON_PLL_SRC_Pos               19                                      /*!< CLK PLLCON: PLL_SRC Position */
#define CLK_PLLCON_PLL_SRC_Msk               (1ul << CLK_PLLCON_PLL_SRC_Pos)      /*!< CLK PLLCON: PLL_SRC Mask */

#define CLK_PLLCON_OE_Pos                    18                                   /*!< CLK PLLCON: OE Position */
#define CLK_PLLCON_OE_Msk                    (1ul << CLK_PLLCON_OE_Pos)           /*!< CLK PLLCON: OE Mask */

#define CLK_PLLCON_BP_Pos                    17                                   /*!< CLK PLLCON: BP Position */
#define CLK_PLLCON_BP_Msk                    (1ul << CLK_PLLCON_BP_Pos)           /*!< CLK PLLCON: BP Mask */

#define CLK_PLLCON_PD_Pos                    16                                   /*!< CLK PLLCON: PD Position */
#define CLK_PLLCON_PD_Msk                    (1ul << CLK_PLLCON_PD_Pos)           /*!< CLK PLLCON: PD Mask */

#define CLK_PLLCON_OUT_DV_Pos                14                                   /*!< CLK PLLCON: OUT_DV Position */
#define CLK_PLLCON_OUT_DV_Msk                (3ul << CLK_PLLCON_OUT_DV_Pos)       /*!< CLK PLLCON: OUT_DV Mask */

#define CLK_PLLCON_IN_DV_Pos                 9                                    /*!< CLK PLLCON: IN_DV Position */
#define CLK_PLLCON_IN_DV_Msk                 (0x1Ful << CLK_PLLCON_IN_DV_Pos)     /*!< CLK PLLCON: IN_DV Mask */

#define CLK_PLLCON_FB_DV_Pos                 0                                    /*!< CLK PLLCON: FB_DV Position */
#define CLK_PLLCON_FB_DV_Msk                 (0x1FFul << CLK_PLLCON_FB_DV_Pos)    /*!< CLK PLLCON: FB_DV Mask */

/* CLK FRQDIV Bit Field Definitions */
#define CLK_FRQDIV_DIVIDER1_Pos              5                                    /*!< CLK FRQDIV: DIVIDER1 Position */
#define CLK_FRQDIV_DIVIDER1_Msk              (1ul << CLK_FRQDIV_DIVIDER1_Pos)     /*!< CLK FRQDIV: DIVIDER1 Mask */

#define CLK_FRQDIV_DIVIDER_EN_Pos            4                                    /*!< CLK FRQDIV: DIVIDER_EN Position */
#define CLK_FRQDIV_DIVIDER_EN_Msk            (1ul << CLK_FRQDIV_DIVIDER_EN_Pos)   /*!< CLK FRQDIV: DIVIDER_EN Mask */

#define CLK_FRQDIV_FSEL_Pos                  0                                    /*!< CLK FRQDIV: FSEL Position */
#define CLK_FRQDIV_FSEL_Msk                  (0xFul << CLK_FRQDIV_FSEL_Pos)       /*!< CLK FRQDIV: FSEL Mask */
/**@}*/ /* CLK_CONST */
/**@}*/ /* CLK */




/*----------------------------- TIMER Controller -----------------------------*/
/** @addtogroup TIMER TIMER Controller(TIMER)
  Memory Mapped Structure for Timer Controller
  @{
 */
typedef struct
{
    /**
     * TCSR
     * ===================================================================================================
     * Offset: 0x00  Timer Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PRESCALE  |Pre-scale Counter
     * |        |          |Clock input is divided by PRESCALE+1 before it is fed to the counter. If
     * |        |          |PRESCALE=0, then there is no scaling.
     * |[16]    |TDR_EN    |Data Load Enable
     * |        |          |When TDR_EN is set, TDR (Timer Data Register) will be updated continuously with
     * |        |          |the 24-bit up-timer value as the timer is counting.
     * |        |          |1 = Timer Data Register update enable.
     * |        |          |0 = Timer Data Register update disable.
     * |[25]    |CACT      |Timer Active Status Bit (Read only)
     * |        |          |This bit indicates the up-timer status.
     * |        |          |0 = Timer is not active.
     * |        |          |1 = Timer is active.
     * |[26]    |CRST      |Timer Reset Bit
     * |        |          |Set this bit will reset the 24-bit up-timer, 8-bit pre-scale counter and also force CEN to
     * |        |          |0.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset Timer's 8-bit pre-scale counter, internal 24-bit up-timer and CEN bit.
     * |[28:27] |MODE      |Timer Operating Mode
     * |        |          |00 =
     * |        |          |The timer is operating in the one-shot mode. The associated
     * |        |          |interrupt signal is generated once (if IE is enabled) and CEN is
     * |        |          |automatically cleared by hardware.
     * |        |          |01 =
     * |        |          |The timer is operating in the periodic mode. The associated
     * |        |          |interrupt signal is generated periodically (if IE is enabled).
     * |        |          |10 =
     * |        |          |The timer is operating in the toggle mode. The interrupt signal is
     * |        |          |generated periodically (if IE is enabled). And the associated
     * |        |          |signal (tout) is changing back and forth with 50% duty cycle.
     * |        |          |11 =
     * |        |          |Reserved
     * |[29]    |IE        |Interrupt Enable Bit
     * |        |          |1 = Enable timer Interrupt.
     * |        |          |0 = Disable timer Interrupt.
     * |        |          |If timer interrupt is enabled, the timer asserts its interrupt signal when the associated
     * |        |          |up-timer value is equal to TCMPR.
     * |[30]    |CEN       |Timer Enable Bit
     * |        |          |1 = Starts counting
     * |        |          |0 = Stops/Suspends counting
     * |        |          |Note1: In stop status, and then set CEN to 1 will enables the 24-bit up-timer keeps up
     * |        |          |counting from the last stop counting value.
     * |        |          |Note2: This bit is auto-cleared by hardware in one-shot mode (MODE[28:27]=00)
     * |        |          |when the associated timer interrupt is generated (IE[29]=1).
     */
    __IO uint32_t  TCSR;

    /**
     * TCMPR
     * ===================================================================================================
     * Offset: 0x04  Timer Compare Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |TCMP      |Timer Compared Value
     * |        |          |TCMP is a 24-bit compared register. When the internal 24-bit up-timer counts and its value
     * |        |          |is equal to TCMP value, a Timer Interrupt is requested if the timer interrupt is enabled with
     * |        |          |TCSR.IE[29]=1. The TCMP value defines the timer counting cycle time.
     * |        |          |Time out period = (Period of timer clock input) * (8-bit PRESCALE + 1) * (24-bit TCMP)
     * |        |          |NOTE1: Never write 0x0 or 0x1 in TCMP, or the core will run into unknown state.
     * |        |          |NOTE2: No matter CEN is 0 or 1, whenever software write a new value into this register,
     * |        |          |TIMER will restart counting using this new value and abort previous count.
     */
    __IO uint32_t  TCMPR;

    /**
     * TISR
     * ===================================================================================================
     * Offset: 0x08  Timer Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TIF       |Timer Interrupt Flag
     * |        |          |This bit indicates the interrupt status of Timer.
     * |        |          |TIF bit is set by hardware when the up counting value of internal 24-bit timer matches the timer
     * |        |          |compared value (TCMP). It is cleared by writing 1 to this bit.
     */
    __IO uint32_t  TISR;

    /**
     * TDR
     * ===================================================================================================
     * Timer Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |TDR       |Timer Data Register
     * |        |          |When TCSR.TDR_EN is set to 1, the internal 24-bit up-timer value will be loaded into TDR.
     * |        |          |User can read this register for the up-timer value.
     */
    __IO uint32_t  TDR;

    /**
     * TCAP
     * ===================================================================================================
     * Timer Capture Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |TCAP      |Timer Capture Data Register
     * |        |          |When TEXEN (TEXCON[3]) is set, RSTCAPSEL (TTXCON[4]) is 0, and the transition on the TEX pins associated TEX_EDGE(TEXCON[2:1]) setting is occurred,
     * |        |          |the internal 24-bit up-timer value will be loaded into TCAP. User can read this register for the counter value.
     */
    __IO uint32_t  TCAP;

    /**
     * TEXCON
     * ===================================================================================================
     * Offset: 0x14  Timer External Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TX_PHASE  |Timer External Count Phase
     * |        |          |This bit indicates the external count pin phase.
     * |        |          |1 = A rising edge of external count pin will be counted.
     * |        |          |0 = A falling edge of external count pin will be counted.
     * |[2:1]   |TEX_EDGE  |Timer External Pin Edge Detect
     * |        |          |00 = a 1 to 0 transition on TEX will be detected.
     * |        |          |01 = a 0 to 1 transition on TEX will be detected.
     * |        |          |10 = either 1 to 0 or 0 to 1 transition on TEX will be detected.
     * |        |          |11 = Reserved.
     * |[3]     |TEXEN     |Timer External Pin Enable.
     * |        |          |This bit enables the reset/capture function on the TEX pin.
     * |        |          |1 = The transition detected on the TEX pin will result in capture or reset of timer counter.
     * |        |          |0 = The TEX pin will be ignored.
     * |[4]     |RSTCAPSEL |Timer External Reset Counter / Capture mode select
     * |        |          |1 = TEX transition is using as the timer counter reset function.
     * |        |          |0 = TEX transition is using as the timer capture function.
     * |[5]     |TEXIEN    |Timer External interrupt Enable Bit
     * |        |          |1 = Enable timer External Interrupt
     * |        |          |0 = Disable timer External Interrupt
     * |        |          |If timer external interrupt is enabled, the timer asserts its external interrupt signal and sent to NVIC to inform CPU
     * |        |          |when the transition on the TEX pins associated with TEX_EDGE(TEXCON[2:1]) setting is happened.
     * |        |          |For example, while TEXIEN = 1, TEXEN = 1, and TEX_EDGE = 00,
     * |        |          |a 1 to 0 transition on the TEX pin will cause the TEXIF(TEXISR[0]) interrupt flag to be set then the interrupt signal is generated and sent to NVIC to inform CPU.
     * |[6]     |TEXDB     |Timer External Capture pin De-bounce enable bit
     * |        |          |1 = Enable De-bounce
     * |        |          |0 = Disable De-bounce
     * |        |          |If this bit is enabled, the edge of T0EX~T3EX pin is detected with de-bounce circuit.
     * |[7]     |TCDB      |Timer Counter pin De-bounce enable bit
     * |        |          |1 = Enable De-bounce
     * |        |          |0 = Disable De-bounce
     * |        |          |If this bit is enabled, the edge of T0~T3 pin is detected with de-bounce circuit.
     */
    __IO uint32_t  TEXCON;

    /**
     * TEXISR
     * ===================================================================================================
     * Offset: 0x14  Timer External Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TEXIF     |Timer External Interrupt Flag
     * |        |          |This bit indicates the external interrupt status of Timer.
     * |        |          |This bit is set by hardware when TEXEN (TEXCON[3]) is to 1,and the transition on the TEX pins associated TEX_EDGE(TEXCON[2:1]) setting is occurred.
     * |        |          |It is cleared by writing 1 to this bit.
     * |        |          |For example, while TEXEN = 1, and TEX_EDGE = 00, a 1 to 0 transition on the TEX pin will cause the TEXIF to be set.
     */
    __IO uint32_t  TEXISR;
} TIMER_T;

/** @addtogroup TMR_CONST Timer Bit Field Definition
  Constant Definitions for Timer Controller
  @{
 */

/* TIMER TCSR Bit Field Definitions */
#define TIMER_TCSR_DBGACK_TMR_Pos   31                                          /*!< TIMER TCSR: DBGACK_TMR Position */
#define TIMER_TCSR_DBGACK_TMR_Msk   (1ul << TIMER_TCSR_DBGACK_TMR_Pos)          /*!< TIMER TCSR: DBGACK_TMR Mask */

#define TIMER_TCSR_CEN_Pos          30                                          /*!< TIMER TCSR: CEN Position */
#define TIMER_TCSR_CEN_Msk          (1ul << TIMER_TCSR_CEN_Pos)                 /*!< TIMER TCSR: CEN Mask */

#define TIMER_TCSR_IE_Pos           29                                          /*!< TIMER TCSR: IE Position */
#define TIMER_TCSR_IE_Msk           (1ul << TIMER_TCSR_IE_Pos)                  /*!< TIMER TCSR: IE Mask */

#define TIMER_TCSR_MODE_Pos         27                                          /*!< TIMER TCSR: MODE Position */
#define TIMER_TCSR_MODE_Msk         (0x3ul << TIMER_TCSR_MODE_Pos)              /*!< TIMER TCSR: MODE Mask */

#define TIMER_TCSR_CRST_Pos         26                                          /*!< TIMER TCSR: CRST Position */
#define TIMER_TCSR_CRST_Msk         (1ul << TIMER_TCSR_CRST_Pos)                /*!< TIMER TCSR: CRST Mask */

#define TIMER_TCSR_CACT_Pos         25                                          /*!< TIMER TCSR: CACT Position */
#define TIMER_TCSR_CACT_Msk         (1ul << TIMER_TCSR_CACT_Pos)                /*!< TIMER TCSR: CACT Mask */

#define TIMER_TCSR_CTB_Pos          24                                          /*!< TIMER TCSR: CTB Position */
#define TIMER_TCSR_CTB_Msk          (1ul << TIMER_TCSR_CTB_Pos)                 /*!< TIMER TCSR: CTB Mask */

#define TIMER_TCSR_WAKE_EN_Pos      23                                          /*!< TIMER TCSR: WAKE_EN Position */
#define TIMER_TCSR_WAKE_EN_Msk      (1ul << TIMER_TCSR_WAKE_EN_Pos)             /*!< TIMER TCSR: WAKE_EN Mask */

#define TIMER_TCSR_CAP_SRC_Pos      22                                          /*!< TIMER TCSR: CAP_SRC Position */
#define TIMER_TCSR_CAP_SRC_Msk      (1ul << TIMER_TCSR_CAP_SRC_Pos)             /*!< TIMER TCSR: CAP_SRC Mask */

#define TIMER_TCSR_TOUT_SEL_Pos     21                                          /*!< TIMER TCSR: TOUT_SEL Position */
#define TIMER_TCSR_TOUT_SEL_Msk     (1ul << TIMER_TCSR_TOUT_SEL_Pos)            /*!< TIMER TCSR: TOUT_SEL Mask */

#define TIMER_TCSR_ERIODIC_SEL_Pos  20                                          /*!< TIMER TCSR: PERIODIC_SEL Position */
#define TIMER_TCSR_ERIODIC_SEL_Msk  (1ul << TIMER_TCSR_ERIODIC_SEL_Pos)         /*!< TIMER TCSR: PERIODIC_SEL Mask */

#define TIMER_TCSR_INTR_TRG_EN_Pos  19                                          /*!< TIMER TCSR: INTR_TRG_EN Position */
#define TIMER_TCSR_INTR_TRG_EN_Msk  (1ul << TIMER_TCSR_INTR_TRG_EN_Pos)         /*!< TIMER TCSR: INTR_TRG_EN Mask */

#define TIMER_TCSR_TDR_EN_Pos       16                                          /*!< TIMER TCSR: TDR_EN Position */
#define TIMER_TCSR_TDR_EN_Msk       (1ul << TIMER_TCSR_TDR_EN_Pos)              /*!< TIMER TCSR: TDR_EN Mask */

#define TIMER_TCSR_PRESCALE_Pos     0                                           /*!< TIMER TCSR: PRESCALE Position */
#define TIMER_TCSR_PRESCALE_Msk     (0xFFul << TIMER_TCSR_PRESCALE_Pos)         /*!< TIMER TCSR: PRESCALE Mask */

/* TIMER TCMPR Bit Field Definitions */
#define TIMER_TCMP_TCMP_Pos         0                                           /*!< TIMER TCMPR: TCMP Position */
#define TIMER_TCMP_TCMP_Msk         (0xFFFFFFul << TIMER_TCMP_TCMP_Pos)         /*!< TIMER TCMPR: TCMP Mask */

/* TIMER TISR Bit Field Definitions */
#define TIMER_TISR_TWF_Pos          1                                           /*!< TIMER TISR: TWF Position */
#define TIMER_TISR_TWF_Msk          (1ul << TIMER_TISR_TWF_Pos)                 /*!< TIMER TISR: TWF Mask */

#define TIMER_TISR_TIF_Pos          0                                           /*!< TIMER TISR: TIF Position */
#define TIMER_TISR_TIF_Msk          (1ul << TIMER_TISR_TIF_Pos)                 /*!< TIMER TISR: TIF Mask */

/* TIMER TDR Bit Field Definitions */
#define TIMER_TDR_TDR_Pos           0                                           /*!< TIMER TDR: TDR Position */
#define TIMER_TDR_TDR_Msk           (0xFFFFFFul << TIMER_TDR_TDR_Pos)           /*!< TIMER TDR: TDR Mask */

/* TIMER TCAP Bit Field Definitions */
#define TIMER_TCAP_TCAP_Pos         0                                           /*!< TIMER TCAP: TCAP Position */
#define TIMER_TCAP_TCAP_Msk         (0xFFFFFFul << TIMER_TCAP_TCAP_Pos)         /*!< TIMER TCAP: TCAP Mask */

/* TIMER TEXCON Bit Field Definitions */
#define TIMER_TEXCON_TCDB_Pos       7                                           /*!< TIMER TEXCON: TCDB Position */
#define TIMER_TEXCON_TCDB_Msk       (1ul << TIMER_TEXCON_TCDB_Pos)              /*!< TIMER TEXCON: TCDB Mask */

#define TIMER_TEXCON_TEXDB_Pos      6                                           /*!< TIMER TEXCON: TEXDB Position */
#define TIMER_TEXCON_TEXDB_Msk      (1ul << TIMER_TEXCON_TEXDB_Pos)             /*!< TIMER TEXCON: TEXDB Mask */

#define TIMER_TEXCON_TEXIEN_Pos     5                                           /*!< TIMER TEXCON: TEXIEN Position */
#define TIMER_TEXCON_TEXIEN_Msk     (1ul << TIMER_TEXCON_TEXIEN_Pos)            /*!< TIMER TEXCON: TEXIEN Mask */

#define TIMER_TEXCON_RSTCAPSEL_Pos  4                                           /*!< TIMER TEXCON: RSTCAPSEL Position */
#define TIMER_TEXCON_RSTCAPSEL_Msk  (1ul << TIMER_TEXCON_RSTCAPSEL_Pos)         /*!< TIMER TEXCON: RSTCAPSEL Mask */

#define TIMER_TEXCON_TEXEN_Pos      3                                           /*!< TIMER TEXCON: TEXEN Position */
#define TIMER_TEXCON_TEXEN_Msk      (1ul << TIMER_TEXCON_TEXEN_Pos)             /*!< TIMER TEXCON: TEXEN Mask */

#define TIMER_TEXCON_TEX_EDGE_Pos   1                                           /*!< TIMER TEXCON: TEX_EDGE Position */
#define TIMER_TEXCON_TEX_EDGE_Msk   (0x3ul << TIMER_TEXCON_TEX_EDGE_Pos)        /*!< TIMER TEXCON: TEX_EDGE Mask */

#define TIMER_TEXCON_TX_PHASE_Pos   0                                           /*!< TIMER TEXCON: TX_PHASE Position */
#define TIMER_TEXCON_TX_PHASE_Msk   (1ul << TIMER_TEXCON_TX_PHASE_Pos)          /*!< TIMER TEXCON: TX_PHASE Mask */

/* TIMER TEXISR Bit Field Definitions */
#define TIMER_TEXISR_TEXIF_Pos      0                                           /*!< TIMER TEXISR: TEXIF Position */
#define TIMER_TEXISR_TEXIF_Msk      (1ul << TIMER_TEXISR_TEXIF_Pos)             /*!< TIMER TEXISR: TEXIF Mask */
/**@}*/ /* TMR_CONST */
/**@}*/ /* TIMER */


/*------------------------- UART Interface Controller ------------------------*/

/** @addtogroup UART UART Controller(UART)
  Memory Mapped Structure for UART Serial Interface Controller
  @{
 */
typedef struct
{

    union
    {
        __IO uint32_t DATA;

        /**
         * THR
         * ===================================================================================================
         * Offset: 0x00 Transmit Holding DATA
         * ---------------------------------------------------------------------------------------------------
         * |Bits    |Field     |Descriptions
         * | :----: | :----:   | :---- |
         * |[7:0]   |          |bitTransmittedData
         * |        |          |Transmit Holding Register
         * |        |          |By writing to this register, the UART will send out an 8-bit data through the Tx pin (LSB
         * |        |          |first).
         */
        __IO uint32_t THR;

        /**
         * RBR
         * ===================================================================================================
         * Offset: 0x00 Receive Buffer
         * ---------------------------------------------------------------------------------------------------
         * |Bits    |Field     |Descriptions
         * | :----: | :----:   | :---- |
         * |[7:0]   |          |Receive Buffer Register
         * |        |          |By reading this register, the UART will return an 8-bit data received from Rx pin (LSB first).
         */
        __IO uint32_t RBR;
    };

    /**
     * IER
     * ===================================================================================================
     * Offset: 0x04  UART Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDA_IEN   |Receive Data Available Interrupt Enable.
     * |        |          |0 = Mask off INT_RDA
     * |        |          |1 = Enable INT_RDA
     * |[1]     |THRE_IEN  |Transmit Holding Register Empty Interrupt Enable
     * |        |          |0 = Mask off INT_THRE
     * |        |          |1 = Enable INT_THRE
     * |[2]     |RLS_IEN   |Receive Line Status Interrupt Enable
     * |        |          |0 = Mask off INT_RLS
     * |        |          |1 = Enable INT_RLS
     * |[3]     |MODEM_IEN |Modem Status Interrupt Enable
     * |        |          |0 = Mask off INT_MOS
     * |        |          |1 = Enable INT_MOS
     * |[4]     |RTO_IEN   |Rx Time out Interrupt Enable
     * |        |          |0 = Mask off INT_tout
     * |        |          |1 = Enable INT_tout
     * |[5]     |BUF_ERR_IEN|Buffer Error Interrupt Enable
     * |        |          |0 = Mask off INT_Buf_err
     * |        |          |1 = Enable INT_Buf_err
     * |[6]     |WAKE_EN   |Wake up CPU function enable
     * |        |          |0 = Disable UART wake up CPU function
     * |        |          |1 = Enable wake up function, when the system is in deep sleep mode, an external /CTS
     * |        |          |change will wake up CPU from deep sleep mode.
     * |[11]    |TIME_OUT_EN|Time-Out Counter Enable
     * |        |          |1 = Enable Time-out counter.
     * |        |          |0 = Disable Time-out counter.
     * |[12]    |AUTO_RTS_EN|RTS Auto Flow Control Enable
     * |        |          |1 = Enable RTS auto flow control.
     * |        |          |0 = Disable RTS auto flow control.
     * |        |          |When RTS auto-flow is enabled, if the number of bytes in the Rx FIFO equals the UA_FCR
     * |        |          |[RTS_TRI_LEV], the UART will dessert RTS signal.|[13]      |Auto_CTS_EN
     * |[13]    |AUTO_CTS_EN|CTS Auto Flow Control Enable
     * |        |          |1 = Enable CTS auto flow control.
     * |        |          |0 = Disable CTS auto flow control.
     * |        |          |When CTS auto-flow is enabled, the UART will send data to external device when CTS input
     * |        |          |assert (UART will not send data to device until CTS is asserted).
     */
    __IO uint32_t IER;

    /**
     * FCR
     * ===================================================================================================
     * Offset: 0x08  UART FIFO Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |RFR       |Rx Software Reset
     * |        |          |When Rx_RST is set, all the bytes in the transmit FIFO and Rx internal state machine are
     * |        |          |cleared.
     * |        |          |0 = Writing 0 to this bit has no effect.
     * |        |          |1 = Writing 1 to this bit will reset the Rx internal state machine and pointers.
     * |        |          |Note: This bit will auto clear and takes at least 3 UART engine clock cycles.
     * |[2]     |TFR       |Tx Software Reset
     * |        |          |When Tx_RST is set, all the bytes in the transmit FIFO and Tx internal state machine are
     * |        |          |cleared.
     * |        |          |0 = Writing 0 to this bit has no effect.
     * |        |          |1 = Writing 1 to this bit will reset the Tx internal state machine and pointers.
     * |        |          |Note: This bit will auto clear and takes at least 3 UART engine clock cycles.
     * |[7:4]   |RFITL     |INT_RDA Tigger Level(Bytes)
     * |        |          |0000 = 01 Bytes
     * |        |          |0001 = 04 Bytes
     * |        |          |0010 = 08 Bytes
     * |        |          |0011 = 14 Bytes
     * |[8]     |RX_DIS    |Receiver Disable register.
     * |        |          |The receiver is disabled or not (set 1 is disable receiver)
     * |        |          |1: Disable Receiver
     * |        |          |0: Enable Receiver
     * |        |          |Note: This field is used for RS-485 Normal Multi-drop mode. It should be programmed before
     * |        |          |RS-485 enable function in UA_FUN_SEL. FUN_SEL is programmed.
     * |[19:16] |RTS_TRI_LEV|RTS Trigger Level Select
     * |        |          |0000 = 01 Bytes
     * |        |          |0001 = 04 Bytes
     * |        |          |0010 = 08 Bytes
     * |        |          |0011 = 14 Bytes
     */
    __IO uint32_t FCR;

    /**
     * LCR
     * ===================================================================================================
     * Offset: 0x0C  UART Line Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |WLS       |Word Length Select
     * |        |          |00 = 5 bits
     * |        |          |01 = 6 bits
     * |        |          |10 = 7 bits
     * |        |          |11 = 8 bits
     * |[2]     |NSB       |Number of "STOP bit"
     * |        |          |0= One "STOP bit" is generated in the transmitted data
     * |        |          |1= One and a half "STOP bit" is generated in the transmitted data when 5-bit word length is selected;
     * |        |          |Two "STOP bit" is generated when 6-, 7- and 8-bit word length is selected.
     * |[3]     |PBE       |Parity Bit Enable
     * |        |          |0 = Parity bit is not generated (transmit data) or checked (receive data) during transfer.
     * |        |          |1 = Parity bit is generated or checked between the "last data word bit" and "stop bit" of the serial data.
     * |[4]     |EPE       |Even Parity Enable
     * |        |          |0 = Odd number of logic 1's are transmitted or checked in the data word and parity bits.
     * |        |          |1 = Even number of logic 1's are transmitted or checked in the data word and parity bits.
     * |        |          |This bit has effect only when bit 3 (parity bit enable) is set.
     * |[5]     |SPE       |Stick Parity Enable
     * |        |          |0 = Disable stick parity
     * |        |          |1 = When bits PBE , EPE and SPE are set, the parity bit is transmitted and checked as cleared. When
     * |        |          |PBE and SPE are set and EPE is cleared, the parity bit is transmitted and checked as set.
     * |[6]     |BCB       |Break Control Bit
     * |        |          |When this bit is set to logic 1, the serial data output (Tx) is forced to the Spacing State (logic 0). This bit
     * |        |          |acts only on Tx and has no effect on the transmitter logic.
     */
    __IO uint32_t LCR;

    /**
     * MCR
     * ===================================================================================================
     * Offset: 0x10  UART Modem Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |RTS       |RTS (Request-To-Send) Signal
     * |        |          |0: Drive RTS pin to logic 1 (If the Lev_RTS set to low level triggered).
     * |        |          |1: Drive RTS pin to logic 0 (If the Lev_RTS set to low level triggered).
     * |        |          |0: Drive RTS pin to logic 0 (If the Lev_RTS set to high level triggered).
     * |        |          |1: Drive RTS pin to logic 1 (If the Lev_RTS set to high level triggered).
     * |[9]     |LEV_RTS   |RTS Trigger Level
     * |        |          |This bit can change the RTS trigger level.
     * |        |          |0= low level triggered
     * |        |          |1= high level triggered
     * |[13]    |RTS_ST    |RTS Pin State
     * |        |          |This bit is the pin status of RTS.
     */
    __IO uint32_t MCR;

    /**
     * MSR
     * ===================================================================================================
     * Offset: 0x14  UART Modem Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DCTSF     |Detect CTS State Change Flag
     * |        |          |This bit is set whenever CTS input has change state, and it will generate Modem interrupt to CPU
     * |        |          |when IER [Modem_IEN].
     * |        |          |NOTE: This bit is cleared by writing 1 to itself.
     * |[4]     |CTS_ST    |CTS Pin Status
     * |        |          |This bit is the pin status of CTS.
     * |[8]     |LEV_CTS   |CTS Trigger Level
     * |        |          |This bit can change the CTS trigger level.
     * |        |          |0= low level triggered
     * |        |          |1= high level triggered
     */
    __IO uint32_t MSR;

    /**
     * FSR
     * ===================================================================================================
     * Offset: 0x18  UART FIFO Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RX_OVER_IF|Rx overflow Error IF (Read Only)
     * |        |          |This bit is set when Rx FIFO overflow.
     * |        |          |If the number of bytes of received data is greater than Rx FIFO(UA_RBR) size, 16 bytes of
     * |        |          |UART0/UART1, this bit will be set.
     * |        |          |NOTE: This bit is cleared by writing 1 to itself.
     * |[3]     |RS485_ADD_DETF|RS-485 Address Byte Detection Flag
     * |        |          |This bit is set to logic 1 and set UA_RS-485_CSR [RS485_ADD_EN] whenever in RS-485
     * |        |          |mode the receiver detect any address byte received address byte character (bit9 = '1') bit",
     * |        |          |and it is reset whenever the CPU writes 1 to this bit.
     * |        |          |Note: This field is used for RS-485 mode.
     * |[4]     |PEF       |Parity Error Flag
     * |        |          |This bit is set to logic 1 whenever the received character does not have a valid "parity bit",
     * |        |          |and is reset whenever the CPU writes 1 to this bit.
     * |[5]     |FEF       |Framing Error Flag
     * |        |          |This bit is set to logic 1 whenever the received character does not have a valid "stop bit" (that
     * |        |          |is, the stop bit following the last data bit or parity bit is detected as a logic 0), and is reset
     * |        |          |whenever the CPU writes 1 to this bit.
     * |[6]     |BIF       |Break Interrupt Flag
     * |        |          |This bit is set to a logic 1 whenever the received data input(Rx) is held in the "spacing state"
     * |        |          |(logic 0) for longer than a full word transmission time (that is, the total time of "start bit" + data
     * |        |          |bits + parity + stop bits) and is reset whenever the CPU writes 1 to this bit.
     * |[13:8]  |RX_POINTER|Rx FIFO pointer (Read Only)
     * |        |          |This field indicates the Rx FIFO Buffer Pointer. When UART receives one byte from external
     * |        |          |device, Rx_Pointer increases one. When one byte of Rx FIFO is read by CPU, Rx_Pointer
     * |        |          |decreases one.
     * |[14]    |RX_EMPTY  |Receiver FIFO Empty (Read Only)
     * |        |          |This bit initiate Rx FIFO empty or not.
     * |        |          |When the last byte of Rx FIFO has been read by CPU, hardware sets this bit high. It will be
     * |        |          |cleared when UART receives any new data.
     * |[15]    |RX_FULL   |Receiver FIFO Full (Read Only)
     * |        |          |This bit initiates Rx FIFO full or not.
     * |        |          |This bit is set when Rx_Pointer is equal to 16(UART0/UART1), otherwise is cleared by
     * |        |          |hardware.
     * |[21:16] |TX_POINTER|TX FIFO Pointer (Read Only)
     * |        |          |This field indicates the Tx FIFO Buffer Pointer. When CPU write one byte into UA_THR,
     * |        |          |Tx_Pointer increases one. When one byte of Tx FIFO is transferred to Transmitter Shift
     * |        |          |Register, Tx_Pointer decreases one.
     * |[22]    |TX_EMPTY  |Transmitter FIFO Empty (Read Only)
     * |        |          |This bit indicates Tx FIFO empty or not.
     * |        |          |When the last byte of Tx FIFO has been transferred to Transmitter Shift Register, hardware
     * |        |          |sets this bit high. It will be cleared when writing data into THR (Tx FIFO not empty).
     * |[23]    |TX_Full   |Transmitter FIFO Full (Read Only)
     * |        |          |This bit indicates Tx FIFO full or not.
     * |        |          |This bit is set when Tx_Pointer is equal to 64/16(UART0/UART1), otherwise is cleared by
     * |        |          |hardware.
     * |[24]    |TX_OVER_IF|Tx Overflow Error Interrupt Flag (Read Only)
     * |        |          |If Tx FIFO(UA_THR) is full, an additional write to UA_THR will cause this bit to logic 1.
     * |        |          |NOTE: This bit is cleared by writing 1 to itself.
     * |[28]    |TE_FLAG   |Transmitter Empty Flag (Read Only)
     * |        |          |Bit is set by hardware when Tx FIFO(UA_THR) is empty and the STOP bit of the last byte
     * |        |          |has been transmitted.
     * |        |          |Bit is cleared automatically when Tx FIFO is not empty or the last byte transmission has not
     * |        |          |completed.
     * |        |          |NOTE: This bit is read only.
     */
    __IO uint32_t FSR;

    /**
     * ISR
     * ===================================================================================================
     * Offset: 0x1C  UART Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDA_IF    |Receive Data Available Interrupt Flag (Read Only).
     * |        |          |When the number of bytes in the Rx FIFO equals the RFITL then the RDA_IF will be set. If
     * |        |          |IER[RDA_IEN] is enabled, the RDA interrupt will be generated.
     * |        |          |NOTE: This bit is read only and it will be cleared when the number of unread bytes of Rx FIFO
     * |        |          |drops below the threshold level (RFITL).
     * |[1]     |THRE_IF   |Transmit Holding Register Empty Interrupt Flag (Read Only).
     * |        |          |This bit is set when the last data of Tx FIFO is transferred to Transmitter Shift Register. If
     * |        |          |IER[THRE_IEN] is enabled, the THRE interrupt will be generated.
     * |        |          |NOTE: This bit is read only and it will be cleared when writing data into THR (Tx FIFO not empty).
     * |[2]     |RLS_IF    |Receive Line Interrupt Flag (Read Only).
     * |        |          |In UART mode this bit is set when the Rx receive data have parity error, framing error or break
     * |        |          |error (at least one of 3 bits, BIF, FEF and PEF, is set). In RS-485 mode, the field includes RS-485
     * |        |          |Address Byte Detection Flag. If IER[RLS_IEN] is enabled, the RLS interrupt will be generated.
     * |        |          |NOTE: This bit is read only and reset to 0 when all bits of BIF, FEF, PEF and RS-485_Add_Det
     * |        |          |are cleared.
     * |[3]     |MODEM_IF  |MODEM Interrupt Flag (Read Only)
     * |        |          |This bit is set when the CTS pin has state change (DCTSF=1). If IER[Modem_IEN] is enabled, the
     * |        |          |Modem interrupt will be generated.
     * |        |          |NOTE: This bit is read only and reset to 0 when bit DCTSF is cleared by a write 1 on DCTSF.
     * |[4]     |TOUT_IF   |Time Out Interrupt Flag (Read Only)
     * |        |          |This bit is set when the Rx FIFO is not empty and no activities occur in the Rx FIFO and the time
     * |        |          |out counter equal to TOIC. If IER [Tout_IEN] is enabled, the Tout interrupt will be generated.
     * |        |          |NOTE: This bit is read only and user can read UA_RBR (Rx is in active) to clear it.
     * |[5]     |BUF_ERR_IF|Buffer Error Interrupt Flag (Read Only)
     * |        |          |This bit is set when the Tx or Rx FIFO overflows (Tx_Over_IF or Rx_Over_IF is set). When
     * |        |          |Buf_Err_IF is set, the transfer maybe not correct. If IER[Buf_Err_IEN] is enabled, the buffer error
     * |        |          |interrupt will be generated.
     * |        |          |NOTE: This bit is cleared when both Tx_Over_IF and Rx_Over_IF are cleared.
     * |[8]     |RDA_INT   |Receive Data Available Interrupt Indicator to Interrupt Controller (INT_RDA).
     * |        |          |An AND output with inputs of RDA_IEN and RDA_IF
     * |[9]     |THRE_INT  |Transmit Holding Register Empty Interrupt Indicator to Interrupt Controller (INT_THRE).
     * |        |          |An AND output with inputs of THRE_IEN and THRE_IF
     * |[10]    |RLS_INT   |Receive Line Status Interrupt Indicator to Interrupt Controller (INT_RLS).
     * |        |          |An AND output with inputs of RLS_IEN and RLS_IF
     * |        |          |Note: In RS-485 mode, the field includes RS-485 Address Byte Detection Flag.
     * |[11]    |MODEM_INT |MODEM Status Interrupt Indicator to Interrupt Controller (INT_MOS).
     * |        |          |An AND output with inputs of Modem_IEN and Modem_IF
     * |[12]    |TOUT_INT  |Time Out Interrupt Indicator to Interrupt Controller (INT_Tout)
     * |        |          |An AND output with inputs of RTO_IEN and Tout_IF
     * |[13]    |BUF_ERR_INT|Buffer Error Interrupt Indicator to Interrupt Controller (INT_Buf_err)
     * |        |          |An AND output with inputs of BUF_ERR_IEN and Buf_Err_IF
     */
    __IO uint32_t ISR;

    /**
     * TOR
     * ===================================================================================================
     * Offset: 0x20  UART Time Out Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |TOIC      |Time Out Interrupt Comparator
     * |        |          |The time out counter resets and starts counting (the counting clock = baud rate) whenever the RX FIFO
     * |        |          |receives a new data word. Once the content of time out counter (TOUT_CNT) is equal to that of time out
     * |        |          |interrupt comparator (TOIC), a receiver time out interrupt (INT_TOUT) is generated if UA_IER[RTO_IEN].
     * |        |          |A new incoming data word or RX FIFO empty clears INT_TOUT.
     * |[15:8]  |DLY       |TX Delay time value
     * |        |          |This field is use to programming the transfer delay time between the last stop bit leaving the TX-FIFO
     * |        |          |and the de-assertion of by setting UA_TOR. DLY register.
     */
    __IO uint32_t TOR;

    /**
     * BAUD
     * ===================================================================================================
     * Offset: 0x24  UART Baud Rate Divisor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BRD_LowByte|Baud Rate Divider
     * |        |          |The low byte of the baud rate divider
     * |[15:8]  |BRD_HighByte|Baud Rate Divider
     * |        |          |The high byte of the baud rate divider
     * |[27:24] |Divider_X |Divider X
     * |        |          |The baud rate divider M = X+1.
     * |[28]    |DIV_X_ONE |Divider X equal 1
     * |        |          |0 = Divider M = X (the equation of M = X+1, but Divider_X[27:24] must > 8)
     * |        |          |1 = Divider M = 1 (the equation of M = 1, but BRD[15:0] must > 3).
     * |[29]    |DIV_X_EN  |Divider X Enable
     * |        |          |The BRD = Baud Rate Divider, and the baud rate equation is
     * |        |          |Baud Rate = Clock / [ M * (BRD + 2) ] ; The default value of M is 16.
     * |        |          |0 = Disable divider X (the equation of M = 16)
     * |        |          |1 = Enable divider X (the equation of M = X+1, but Divider_X[27:24 must > 8).
     * |        |          |NOTE: When in IrDA mode, this bit must disable.
     */
    __IO uint32_t BAUD;

    /**
     * IRCR
     * ===================================================================================================
     * Offset: 0x28  UART IrDA Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |Tx_SELECT |Tx_SELECT
     * |        |          |1: Enable IrDA transmitter
     * |        |          |0: Enable IrDA receiver
     * |[5]     |INV_Tx    |INV_Tx
     * |        |          |1= Inverse Tx output signal
     * |        |          |0= No inversion
     * |[6]     |INV_Rx    |INV_Rx
     * |        |          |1= Inverse Rx input signal
     * |        |          |0= No inversion
     */
    __IO uint32_t IRCR;

    /**
     * ALT_CSR
     * ===================================================================================================
     * Offset: 0x2C  UART Alternate Control/Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |LIN_BKFL  |UART LIN Break Field Length
     * |        |          |This field indicates a 4-bit LIN TX break field count.
     * |        |          |Note: This break field length is UA_LIN_BKFL + 2.
     * |[6]     |LIN_RX_EN |LIN RX Enable
     * |        |          |1 = Enable LIN RX mode
     * |        |          |0 = Disable LIN RX mode
     * |[7]     |LIN_TX_EN |LIN TX Break Mode Enable
     * |        |          |1 = Enable LIN TX Break Mode
     * |        |          |0 = Disable LIN TX Break Mode
     * |        |          |Note: When TX break field transfer operation finished, this bit will be cleared automatically.
     * |[8]     |RS485_NMM |RS-485 Normal Multi-drop Operation Mode (NMM)
     * |        |          |1: Enable RS-485 Normal Multi-drop Operation Mode (NMM)
     * |        |          |0: Disable RS-485 Normal Multi-drop Operation Mode (NMM)
     * |        |          |Note: It can't be active with RS-485_AAD operation mode.
     * |[9]     |RS485_AAD |RS-485 Auto Address Detection Operation Mode (AAD)
     * |        |          |1: Enable RS-485 Auto Address Detection Operation Mode (AAD)
     * |        |          |0: Disable RS-485 Auto Address Detection Operation Mode (AAD)
     * |        |          |Note: It can't be active with RS-485_NMM operation mode.
     * |[10]    |RS485_AUD |RS-485 Auto Direction Mode (AUD)
     * |        |          |1: Enable RS-485 Auto Direction Mode (AUD)
     * |        |          |0: Disable RS-485 Auto Direction Mode (AUD)
     * |        |          |Note: It can be active with RS-485_AAD or RS-485_NMM operation mode.
     * |[15]    |RS485_ADD_EN|RS-485 Address Detection Enable
     * |        |          |This bit is use to enable RS-485 address detection mode.
     * |        |          |1: Enable address detection mode
     * |        |          |0: Disable address detection mode
     * |        |          |Note: This field is used for RS-485 any operation mode.
     * |[31:24] |ADDR_MATCH|Address match value register
     * |        |          |This field contains the RS-485 address match values.
     * |        |          |Note: This field is used for RS-485 auto address detection mode.
     */
    __IO uint32_t ALT_CSR;

    /**
     * FUN_SEL
     * ===================================================================================================
     * Offset: 0x30  UART Function Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |FUN_SEL   |Function Select Enable
     * |        |          |00 = UART Function.
     * |        |          |01 = LIN Function.
     * |        |          |10 = IrDA Function.
     * |        |          |11 = RS-485 Function.
     */
    __IO uint32_t FUN_SEL;
} UART_T;

/** @addtogroup UART_CONST UART Bit Field Definition
  Constant Definitions for UART Controller
  @{
 */

/* UART THR Bit Field Definitions */
#define UART_THR_THR_Pos            0                                       /*!< UART THR: THR Position  */
#define UART_THR_THR_Msk            (0xFul << UART_THR_THR_Pos)             /*!< UART THR: THR Mask      */

/* UART RBR Bit Field Definitions */
#define UART_RBR_RBR_Pos            0                                       /*!< UART RBR: RBR Posistion */
#define UART_RBR_RBR_Msk            (0xFul << UART_RBR_RBR_Pos)             /*!< UART RBR: RBR Mask      */

/* UART IER Bit Field Definitions */
#define UART_IER_AUTO_CTS_EN_Pos    13                                      /*!< UART IER: AUTO_CTS_EN Posistion      */
#define UART_IER_AUTO_CTS_EN_Msk    (1ul << UART_IER_AUTO_CTS_EN_Pos)       /*!< UART IER: AUTO_CTS_EN Mask           */

#define UART_IER_AUTO_RTS_EN_Pos    12                                      /*!< UART IER: AUTO_RTS_EN Posistion      */
#define UART_IER_AUTO_RTS_EN_Msk    (1ul << UART_IER_AUTO_RTS_EN_Pos)       /*!< UART IER: AUTO_RTS_EN Mask           */

#define UART_IER_TIME_OUT_EN_Pos    11                                      /*!< UART IER: TIME_OUT_EN Posistion      */
#define UART_IER_TIME_OUT_EN_Msk    (1ul << UART_IER_TIME_OUT_EN_Pos)       /*!< UART IER: TIME_OUT_EN Mask           */

#define UART_IER_LIN_RX_BRK_IEN_Pos 8                                       /*!< UART IER: LIN_RX_BRK_IEN Posistion   */
#define UART_IER_LIN_RX_BRK_IEN_Msk (1ul << UART_IER_LIN_RX_BRK_IEN_Pos)    /*!< UART IER: LIN_RX_BRK_IEN Mask        */

#define UART_IER_WAKE_EN_Pos        6                                       /*!< UART IER: WAKE_EN Posistion          */
#define UART_IER_WAKE_EN_Msk        (1ul << UART_IER_WAKE_EN_Pos)           /*!< UART IER: WAKE_EN Mask               */

#define UART_IER_BUF_ERR_IEN_Pos    5                                       /*!< UART IER: BUF_ERR_IEN Posistion      */
#define UART_IER_BUF_ERR_IEN_Msk    (1ul << UART_IER_BUF_ERR_IEN_Pos)       /*!< UART IER: BUF_ERR_IEN Mask           */

#define UART_IER_RTO_IEN_Pos        4                                       /*!< UART IER: RTO_IEN Posistion          */
#define UART_IER_RTO_IEN_Msk        (1ul << UART_IER_RTO_IEN_Pos)           /*!< UART IER: RTO_IEN Mask               */

#define UART_IER_MODEM_IEN_Pos      3                                       /*!< UART IER: MODEM_IEN Posistion        */
#define UART_IER_MODEM_IEN_Msk      (1ul << UART_IER_MODEM_IEN_Pos)         /*!< UART IER: MODEM_IEN Mask             */

#define UART_IER_RLS_IEN_Pos        2                                       /*!< UART IER: RLS_IEN Posistion          */
#define UART_IER_RLS_IEN_Msk        (1ul << UART_IER_RLS_IEN_Pos)           /*!< UART IER: RLS_IEN Mask               */

#define UART_IER_THRE_IEN_Pos       1                                       /*!< UART IER: THRE_IEN Posistion         */
#define UART_IER_THRE_IEN_Msk       (1ul << UART_IER_THRE_IEN_Pos)          /*!< UART IER: THRE_IEN Mask              */

#define UART_IER_RDA_IEN_Pos        0                                       /*!< UART IER: RDA_IEN Position           */
#define UART_IER_RDA_IEN_Msk        (1ul << UART_IER_RDA_IEN_Pos)           /*!< UART IER: RDA_IEN Mask               */

/* UART FCR Bit Field Definitions */
#define UART_FCR_RTS_TRI_LEV_Pos    16                                      /*!< UART FCR: RTS_TRI_LEV Position       */
#define UART_FCR_RTS_TRI_LEV_Msk    (0xFul << UART_FCR_RTS_TRI_LEV_Pos)     /*!< UART FCR: RTS_TRI_LEV Mask           */

#define UART_FCR_RX_DIS_Pos         8                                       /*!< UART FCR: RX_DIS Position            */
#define UART_FCR_RX_DIS_Msk         (1ul << UART_FCR_RX_DIS_Pos)            /*!< UART FCR: RX_DIS Mask                */

#define UART_FCR_RFITL_Pos          4                                       /*!< UART FCR: RFITL Position             */
#define UART_FCR_RFITL_Msk          (0xFul << UART_FCR_RFITL_Pos)           /*!< UART FCR: RFITL Mask                 */

#define UART_FCR_TFR_Pos            2                                       /*!< UART FCR: TFR Position               */
#define UART_FCR_TFR_Msk            (1ul << UART_FCR_TFR_Pos)               /*!< UART FCR: TFR Mask                   */

#define UART_FCR_RFR_Pos            1                                       /*!< UART FCR: RFR Position               */
#define UART_FCR_RFR_Msk            (1ul << UART_FCR_RFR_Pos)               /*!< UART FCR: RFR Mask                   */

/* UART LCR Bit Field Definitions */
#define UART_LCR_BCB_Pos            6                                       /*!< UART LCR: BCB Position               */
#define UART_LCR_BCB_Msk            (1ul << UART_LCR_BCB_Pos)               /*!< UART LCR: BCB Mask                   */

#define UART_LCR_SPE_Pos            5                                       /*!< UART LCR: SPE Position               */
#define UART_LCR_SPE_Msk            (1ul << UART_LCR_SPE_Pos)               /*!< UART LCR: SPE Mask                   */

#define UART_LCR_EPE_Pos            4                                       /*!< UART LCR: EPE Position               */
#define UART_LCR_EPE_Msk            (1ul << UART_LCR_EPE_Pos)               /*!< UART LCR: EPE Mask                   */

#define UART_LCR_PBE_Pos            3                                       /*!< UART LCR: PBE Position               */
#define UART_LCR_PBE_Msk            (1ul << UART_LCR_PBE_Pos)               /*!< UART LCR: PBE Mask                   */

#define UART_LCR_NSB_Pos            2                                       /*!< UART LCR: NSB Position               */
#define UART_LCR_NSB_Msk            (1ul << UART_LCR_NSB_Pos)               /*!< UART LCR: NSB Mask                   */

#define UART_LCR_WLS_Pos            0                                       /*!< UART LCR: WLS Position               */
#define UART_LCR_WLS_Msk            (0x3ul << UART_LCR_WLS_Pos)             /*!< UART LCR: WLS Mask                   */

/* UART MCR Bit Field Definitions */
#define UART_MCR_RTS_ST_Pos         13                                      /*!< UART MCR: RTS_ST Position            */
#define UART_MCR_RTS_ST_Msk         (1ul << UART_MCR_RTS_ST_Pos)            /*!< UART MCR: RTS_ST Mask                */

#define UART_MCR_LEV_RTS_Pos        9                                       /*!< UART MCR: LEV_RTS Position           */
#define UART_MCR_LEV_RTS_Msk        (1ul << UART_MCR_LEV_RTS_Pos)           /*!< UART MCR: LEV_RTS Mask               */

#define UART_MCR_RTS_Pos            1                                       /*!< UART MCR: RTS Position               */
#define UART_MCR_RTS_Msk            (1ul << UART_MCR_RTS_Pos)               /*!< UART MCR: RTS Mask                   */

/* UART MSR Bit Field Definitions */
#define UART_MSR_LEV_CTS_Pos        8                                       /*!< UART MSR: LEV_CTS Position           */
#define UART_MSR_LEV_CTS_Msk        (1ul << UART_MSR_LEV_CTS_Pos)           /*!< UART MSR: LEV_CTS Mask               */

#define UART_MSR_CTS_ST_Pos         4                                       /*!< UART MSR: CTS_ST Position            */
#define UART_MSR_CTS_ST_Msk         (1ul << UART_MSR_CTS_ST_Pos)            /*!< UART MSR: CTS_ST Mask                */

#define UART_MSR_DCTSF_Pos          0                                       /*!< UART MSR: DCTST Position             */
#define UART_MSR_DCTSF_Msk          (1ul << UART_MSR_DCTSF_Pos)             /*!< UART MSR: DCTST Mask                 */

/* UART FSR Bit Field Definitions */
#define UART_FSR_TE_FLAG_Pos        28                                      /*!< UART FSR: TE_FLAG Position           */
#define UART_FSR_TE_FLAG_Msk        (1ul << UART_FSR_TE_FLAG_Pos)           /*!< UART FSR: TE_FLAG Mask               */

#define UART_FSR_TX_OVER_IF_Pos     24                                      /*!< UART FSR: TX_OVER_IF Position        */
#define UART_FSR_TX_OVER_IF_Msk     (1ul << UART_FSR_TX_OVER_IF_Pos)        /*!< UART FSR: TX_OVER_IF Mask            */

#define UART_FSR_TX_FULL_Pos        23                                      /*!< UART FSR: TX_FULL Position           */
#define UART_FSR_TX_FULL_Msk        (1ul << UART_FSR_TX_FULL_Pos)           /*!< UART FSR: TX_FULL Mask               */

#define UART_FSR_TX_EMPTY_Pos       22                                      /*!< UART FSR: TX_EMPTY Position          */
#define UART_FSR_TX_EMPTY_Msk       (1ul << UART_FSR_TX_EMPTY_Pos)          /*!< UART FSR: TX_EMPTY Mask              */

#define UART_FSR_TX_POINTER_Pos     16                                      /*!< UART FSR: TX_POINTER Position        */
#define UART_FSR_TX_POINTER_Msk     (0x3Ful << UART_FSR_TX_POINTER_Pos)     /*!< UART FSR: TX_POINTER Mask            */

#define UART_FSR_RX_FULL_Pos        15                                      /*!< UART FSR: RX_FULL Position           */
#define UART_FSR_RX_FULL_Msk        (1ul << UART_FSR_RX_FULL_Pos)           /*!< UART FSR: RX_FULL Mask               */

#define UART_FSR_RX_EMPTY_Pos       14                                      /*!< UART FSR: RX_EMPTY Position          */
#define UART_FSR_RX_EMPTY_Msk       (1ul << UART_FSR_RX_EMPTY_Pos)          /*!< UART FSR: RX_EMPTY Mask              */

#define UART_FSR_RX_POINTER_Pos     8                                       /*!< UART FSR: RX_POINTERS Position       */
#define UART_FSR_RX_POINTER_Msk     (0x3Ful << UART_FSR_RX_POINTER_Pos)     /*!< UART FSR: RX_POINTER Mask            */

#define UART_FSR_BIF_Pos            6                                       /*!< UART FSR: BIF Position               */
#define UART_FSR_BIF_Msk            (1ul << UART_FSR_BIF_Pos)               /*!< UART FSR: BIF Mask                   */

#define UART_FSR_FEF_Pos            5                                       /*!< UART FSR: FEF Position               */
#define UART_FSR_FEF_Msk            (1ul << UART_FSR_FEF_Pos)               /*!< UART FSR: FEF Mask                   */

#define UART_FSR_PEF_Pos            4                                       /*!< UART FSR: PEF Position               */
#define UART_FSR_PEF_Msk            (1ul << UART_FSR_PEF_Pos)               /*!< UART FSR: PEF Mask                   */

#define UART_FSR_RS485_ADD_DETF_Pos 3                                       /*!< UART FSR: RS485_ADD_DETF Position    */
#define UART_FSR_RS485_ADD_DETF_Msk (1ul << UART_FSR_RS485_ADD_DETF_Pos)    /*!< UART FSR: RS485_ADD_DETF Mask        */

#define UART_FSR_RX_OVER_IF_Pos     0                                       /*!< UART FSR: RX_OVER_IF Position        */
#define UART_FSR_RX_OVER_IF_Msk     (1ul << UART_FSR_RX_OVER_IF_Pos)        /*!< UART FSR: RX_OVER_IF Mask            */

/* UART ISR Bit Field Definitions */
#define UART_ISR_LIN_RX_BREAK_INT_Pos    15                                      /*!< UART ISR: LIN_RX_BREAK_INT Position       */
#define UART_ISR_LIN_RX_BREAK_INT_Msk    (1ul << UART_ISR_LIN_RX_BREAK_INT_Pos)  /*!< UART ISR: LIN_RX_BREAK_INT Mask           */

#define UART_ISR_BUF_ERR_INT_Pos    13                                      /*!< UART ISR: BUF_ERR_INT Position       */
#define UART_ISR_BUF_ERR_INT_Msk    (1ul << UART_ISR_BUF_ERR_INT_Pos)       /*!< UART ISR: BUF_ERR_INT Mask           */

#define UART_ISR_TOUT_INT_Pos       12                                      /*!< UART ISR: TOUT_INT Position          */
#define UART_ISR_TOUT_INT_Msk       (1ul << UART_ISR_TOUT_INT_Pos)          /*!< UART ISR: TOUT_INT Mask              */

#define UART_ISR_MODEM_INT_Pos      11                                      /*!< UART ISR: MODEM_INT Position         */
#define UART_ISR_MODEM_INT_Msk      (1ul << UART_ISR_MODEM_INT_Pos)         /*!< UART ISR: MODEM_INT Mask             */

#define UART_ISR_RLS_INT_Pos        10                                      /*!< UART ISR: RLS_INT Position           */
#define UART_ISR_RLS_INT_Msk        (1ul << UART_ISR_RLS_INT_Pos)           /*!< UART ISR: RLS_INT Mask               */

#define UART_ISR_THRE_INT_Pos       9                                       /*!< UART ISR: THRE_INT Position          */
#define UART_ISR_THRE_INT_Msk       (1ul << UART_ISR_THRE_INT_Pos)          /*!< UART ISR: THRE_INT Mask              */

#define UART_ISR_RDA_INT_Pos        8                                       /*!< UART ISR: RDA_INT Position           */
#define UART_ISR_RDA_INT_Msk        (1ul << UART_ISR_RDA_INT_Pos)           /*!< UART ISR: RDA_INT Mask               */

#define UART_ISR_LIN_RX_BREAK_IF_Pos 7                                      /*!< UART ISR: LIN RX BREAK IF Position   */
#define UART_ISR_LIN_RX_BREAK_IF_Msk (1ul << UART_ISR_LIN_RX_BREAK_IF_Pos)  /*!< UART ISR: LIN RX BREAK IF Mask       */

#define UART_ISR_BUF_ERR_IF_Pos     5                                       /*!< UART ISR: BUF_ERR_IF Position        */
#define UART_ISR_BUF_ERR_IF_Msk     (1ul << UART_ISR_BUF_ERR_IF_Pos)        /*!< UART ISR: BUF_ERR_IF Mask            */

#define UART_ISR_TOUT_IF_Pos        4                                       /*!< UART ISR: TOUT_IF Position           */
#define UART_ISR_TOUT_IF_Msk        (1ul << UART_ISR_TOUT_IF_Pos)           /*!< UART ISR: TOUT_IF Mask               */

#define UART_ISR_MODEM_IF_Pos       3                                       /*!< UART ISR: MODEM_IF Position          */
#define UART_ISR_MODEM_IF_Msk       (1ul << UART_ISR_MODEM_IF_Pos)          /*!< UART ISR: MODEM_IF Mask              */

#define UART_ISR_RLS_IF_Pos         2                                       /*!< UART ISR: RLS_IF Position            */
#define UART_ISR_RLS_IF_Msk         (1ul << UART_ISR_RLS_IF_Pos)            /*!< UART ISR: RLS_IF Mask                */

#define UART_ISR_THRE_IF_Pos        1                                       /*!< UART ISR: THRE_IF Position           */
#define UART_ISR_THRE_IF_Msk        (1ul << UART_ISR_THRE_IF_Pos)           /*!< UART ISR: THRE_IF Mask               */

#define UART_ISR_RDA_IF_Pos         0                                       /*!< UART ISR: RDA_IF Position            */
#define UART_ISR_RDA_IF_Msk         (1ul << UART_ISR_RDA_IF_Pos)            /*!< UART ISR: RDA_IF Mask                */

/* UART TOR Bit Field Definitions */
#define UART_TOR_DLY_Pos            8                                       /*!< UART TOR: DLY Position               */
#define UART_TOR_DLY_Msk            (0xFFul << UART_TOR_DLY_Pos)            /*!< UART TOR: DLY Mask                   */

#define UART_TOR_TOIC_Pos           0                                       /*!< UART TOR: TOIC Position              */
#define UART_TOR_TOIC_Msk           (0xFFul << UART_TOR_TOIC_Pos)           /*!< UART TOR: TOIC Mask                  */

/* UART BAUD Bit Field Definitions */
#define UART_BAUD_DIV_X_EN_Pos      29                                      /*!< UART BARD: DIV_X_EN Position         */
#define UART_BAUD_DIV_X_EN_Msk      (1ul << UART_BAUD_DIV_X_EN_Pos)         /*!< UART BARD: DIV_X_EN Mask             */

#define UART_BAUD_DIV_X_ONE_Pos     28                                      /*!< UART BARD: DIV_X_ONE Position        */
#define UART_BAUD_DIV_X_ONE_Msk     (1ul << UART_BAUD_DIV_X_ONE_Pos)        /*!< UART BARD: DIV_X_ONE Mask            */

#define UART_BAUD_DIVIDER_X_Pos     24                                      /*!< UART BARD: DIVIDER_X Position        */
#define UART_BAUD_DIVIDER_X_Msk     (0xFul << UART_BAUD_DIVIDER_X_Pos)      /*!< UART BARD: DIVIDER_X Mask            */

#define UART_BAUD_BRD_Pos           0                                       /*!< UART BARD: BRD Position              */
#define UART_BAUD_BRD_Msk           (0xFFFFul << UART_BAUD_BRD_Pos)         /*!< UART BARD: BRD Mask                  */

/* UART IRCR Bit Field Definitions */
#define UART_IRCR_INV_RX_Pos        6                                       /*!< UART IRCR: INV_RX Position           */
#define UART_IRCR_INV_RX_Msk        (1ul << UART_IRCR_INV_RX_Pos)           /*!< UART IRCR: INV_RX Mask               */

#define UART_IRCR_INV_TX_Pos        5                                       /*!< UART IRCR: INV_TX Position           */
#define UART_IRCR_INV_TX_Msk        (1ul << UART_IRCR_INV_TX_Pos)           /*!< UART IRCR: INV_TX Mask               */

#define UART_IRCR_TX_SELECT_Pos     1                                       /*!< UART IRCR: TX_SELECT Position        */
#define UART_IRCR_TX_SELECT_Msk     (1ul << UART_IRCR_TX_SELECT_Pos)        /*!< UART IRCR: TX_SELECT Mask            */

/* UART ALT_CSR Bit Field Definitions */
#define UART_ALT_CSR_ADDR_MATCH_Pos      24                                      /*!< UART ALT_CSR: ADDR_MATCH Position    */
#define UART_ALT_CSR_ADDR_MATCH_Msk     (0xFFul << UART_ALT_CSR_ADDR_MATCH_Pos)  /*!< UART ALT_CSR: ADDR_MATCH Mask        */

#define UART_ALT_CSR_RS485_ADD_EN_Pos   15                                       /*!< UART ALT_CSR: RS485_ADD_EN Position  */
#define UART_ALT_CSR_RS485_ADD_EN_Msk   (1ul << UART_ALT_CSR_RS485_ADD_EN_Pos)   /*!< UART ALT_CSR: RS485_ADD_EN Mask      */

#define UART_ALT_CSR_RS485_AUD_Pos      10                                       /*!< UART ALT_CSR: RS485_AUD Position     */
#define UART_ALT_CSR_RS485_AUD_Msk      (1ul << UART_ALT_CSR_RS485_AUD_Pos)      /*!< UART ALT_CSR: RS485_AUD Mask         */

#define UART_ALT_CSR_RS485_AAD_Pos      9                                        /*!< UART ALT_CSR: RS485_AAD Position     */
#define UART_ALT_CSR_RS485_AAD_Msk      (1ul << UART_ALT_CSR_RS485_AAD_Pos)      /*!< UART ALT_CSR: RS485_AAD Mask         */

#define UART_ALT_CSR_RS485_NMM_Pos      8                                        /*!< UART ALT_CSR: RS485_NMM Position     */
#define UART_ALT_CSR_RS485_NMM_Msk      (1ul << UART_ALT_CSR_RS485_NMM_Pos)      /*!< UART ALT_CSR: RS485_NMM Mask         */

#define UART_ALT_CSR_LIN_TX_EN_Pos      7                                        /*!< UART ALT_CSR: LIN TX Break Mode Enable Position     */
#define UART_ALT_CSR_LIN_TX_EN_Msk      (1ul << UART_ALT_CSR_LIN_TX_EN_Pos)      /*!< UART ALT_CSR: LIN TX Break Mode Enable Mask         */

#define UART_ALT_CSR_LIN_RX_EN_Pos      6                                        /*!< UART ALT_CSR: LIN RX Enable Position     */
#define UART_ALT_CSR_LIN_RX_EN_Msk      (1ul << UART_ALT_CSR_LIN_RX_EN_Pos)      /*!< UART ALT_CSR: LIN RX Enable Mask         */

#define UART_ALT_CSR_UA_LIN_BKFL_Pos    0                                        /*!< UART ALT_CSR: UART LIN Break Field Length Position     */
#define UART_ALT_CSR_UA_LIN_BKFL_Msk    (0xFul << UART_ALT_CSR_UA_LIN_BKFL_Pos)  /*!< UART ALT_CSR: UART LIN Break Field Length Mask         */

/* UART FUN_SEL Bit Field Definitions */
#define UART_FUN_SEL_FUN_SEL_Pos        0                                        /*!< UART FUN_SEL: FUN_SEL Position       */
#define UART_FUN_SEL_FUN_SEL_Msk        (0x3ul << UART_FUN_SEL_FUN_SEL_Pos)      /*!< UART FUN_SEL: FUN_SEL Mask           */
/**@}*/ /* UART_CONST */
/**@}*/ /* UART */



/*----------------------------- WDT Controller -----------------------------*/
/** @addtogroup WDT WDT Controller(WDT)
  Memory Mapped Structure for Watchdog Timer
  @{
 */
typedef struct
{
    /**
     * WTCR
     * ===================================================================================================
     * Offset: 0x00  Watchdog Timer Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WTR       |Clear Watchdog Timer
     * |        |          |Set this bit will clear the Watchdog timer.
     * |        |          |0= Writing 0 to this bit has no effect
     * |        |          |1= Reset the contents of the Watchdog timer
     * |        |          |NOTE: This bit will auto clear after few clock cycle
     * |[1]     |WTRE      |Watchdog Timer Reset Enable
     * |        |          |Setting this bit will enable the Watchdog timer reset function.
     * |        |          |0= Disable Watchdog timer reset function
     * |        |          |1= Enable Watchdog timer reset function
     * |[2]     |WTRF      |Watchdog Timer Reset Flag
     * |        |          |When the Watchdog timer initiates a reset, the hardware will set this bit. This flag can be read by
     * |        |          |software to determine the source of reset. Software is responsible to clear it manually by writing 1 to
     * |        |          |it. If WTRE is disabled, then the Watchdog timer has no effect on this bit.
     * |        |          |0= Watchdog timer reset does not occur
     * |        |          |1= Watchdog timer reset occurs
     * |        |          |NOTE: This bit is cleared by writing 1 to this bit.
     * |[3]     |WTIF      |Watchdog Timer Interrupt Flag
     * |        |          |If the Watchdog timer interrupt is enabled, then the hardware will set this bit to indicate that the
     * |        |          |Watchdog timer interrupt has occurred. If the Watchdog timer interrupt is not enabled, then this bit
     * |        |          |indicates that a timeout period has elapsed.
     * |        |          |0= Watchdog timer interrupt does not occur
     * |        |          |1= Watchdog timer interrupt occurs
     * |        |          |NOTE: Write 1 to clear this bit to zero.
     * |[4]     |WTWKE     |Watchdog Timer Wakeup Function Enable bit
     * |        |          |0 = Disable Watchdog timer Wakeup CPU function.
     * |        |          |1 = Enable the Wakeup function that Watchdog timer timeout can wake up CPU from power-down
     * |        |          |mode.
     * |[5]     |WTWKF     |Watchdog Timer Wakeup Flag
     * |        |          |If Watchdog timer causes CPU wakes up from power-down mode, this bit will be set to high. It must
     * |        |          |be cleared by software with a write 1 to this bit.
     * |        |          |1 = CPU wake up from sleep or power-down mode by Watchdog timeout.
     * |        |          |0 = Watchdog timer does not cause CPU wakeup.
     * |        |          |NOTE: Write 1 to clear this bit to zero.
     * |[6]     |WTIE      |Watchdog Timer Interrupt Enable
     * |        |          |0= Disable the Watchdog timer interrupt
     * |        |          |1= Enable the Watchdog timer interrupt
     * |[7]     |WTE       |Watchdog Timer Enable
     * |        |          |0= Disable the Watchdog timer (This action will reset the internal counter)
     * |        |          |1= Enable the Watchdog timer
     * |[10:8]  |WTIS      |Watchdog Timer Interval Select (write protection bit)
     * |        |          |These three bits select the timeout interval for the Watchdog timer.
     */
    __IO uint32_t  WTCR;

    /**
     * WTCRALT
     * ===================================================================================================
     * Offset: 0x04  Watchdog Timer Alternative Control Register
     * ---------------------------------------------------------------------------------------------------
     */
    __IO uint32_t  WTCRALT;
} WDT_T;

/** @addtogroup WDT_CONST WDT Bit Field Definition
  Constant Definitions for WDT Controller
  @{
 */

/* WDT WTCR Bit Field Definitions */
#define WDT_WTCR_DBGACK_WDT_Pos 31                                              /*!< WDT WTCR : DBGACK_WDT Position */
#define WDT_WTCR_DBGACK_WDT_Msk (1ul << WDT_WTCR_DBGACK_WDT_Pos)                /*!< WDT WTCR : DBGACK_WDT Mask */

#define WDT_WTCR_WTIS_Pos       8                                               /*!< WDT WTCR : WTIS Position */
#define WDT_WTCR_WTIS_Msk       (0x7ul << WDT_WTCR_WTIS_Pos)                    /*!< WDT WTCR : WTIS Mask */

#define WDT_WTCR_WTE_Pos        7                                               /*!< WDT WTCR : WTE Position */
#define WDT_WTCR_WTE_Msk        (1ul << WDT_WTCR_WTE_Pos)                       /*!< WDT WTCR : WTE Mask */

#define WDT_WTCR_WTIE_Pos       6                                               /*!< WDT WTCR : WTIE Position */
#define WDT_WTCR_WTIE_Msk       (1ul << WDT_WTCR_WTIE_Pos)                      /*!< WDT WTCR : WTIE Mask */

#define WDT_WTCR_WTWKF_Pos      5                                               /*!< WDT WTCR : WTWKF Position */
#define WDT_WTCR_WTWKF_Msk      (1ul << WDT_WTCR_WTWKF_Pos)                     /*!< WDT WTCR : WTWKF Mask */

#define WDT_WTCR_WTWKE_Pos      4                                               /*!< WDT WTCR : WTWKE Position */
#define WDT_WTCR_WTWKE_Msk      (1ul << WDT_WTCR_WTWKE_Pos)                     /*!< WDT WTCR : WTWKE Mask */

#define WDT_WTCR_WTIF_Pos       3                                               /*!< WDT WTCR : WTIF Position */
#define WDT_WTCR_WTIF_Msk       (1ul << WDT_WTCR_WTIF_Pos)                      /*!< WDT WTCR : WTIF Mask */

#define WDT_WTCR_WTRF_Pos       2                                               /*!< WDT WTCR : WTRF Position */
#define WDT_WTCR_WTRF_Msk       (1ul << WDT_WTCR_WTRF_Pos)                      /*!< WDT WTCR : WTRF Mask */

#define WDT_WTCR_WTRE_Pos       1                                               /*!< WDT WTCR : WTRE Position */
#define WDT_WTCR_WTRE_Msk       (1ul << WDT_WTCR_WTRE_Pos)                      /*!< WDT WTCR : WTRE Mask */

#define WDT_WTCR_WTR_Pos        0                                               /*!< WDT WTCR : WTR Position */
#define WDT_WTCR_WTR_Msk        (1ul << WDT_WTCR_WTR_Pos)                       /*!< WDT WTCR : WTR Mask */

/* WDT WTCRALT Bit Field Definitions */
#define WDT_WTCRALT_WTRDSEL_Pos 0                                               /*!< WDT WTCRALT : WTRDSEL Position */
#define WDT_WTCRALT_WTRDSEL_Msk (0x3ul << WDT_WTCRALT_WTRDSEL_Pos)              /*!< WDT WTCRALT : WTRDSEL Mask */
/**@}*/ /* WDT_CONST */
/**@}*/ /* WDT */


/*----------------------------- WWDT Controller -----------------------------*/
/** @addtogroup WWDT Window Watchdog Timer (WWDT)
  Register data structure of Window Watchdog Timer and relative constant definitions.
  @{
 */
typedef struct
{
    /**
     * WWDTRLD
     * ===================================================================================================
     * WWDT Reload Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |WWDTRLD   |WWDT Reload Counter Register
     * |        |          |Writing 0x00005AA5 to this register will reload the Window Watchdog Timer counter value to 0x3F.
     * |        |          |Note: Software can only write WWDTRLD to reload WWDT counter value when current WWDT counter value between 0 and WINCMP.
     * |        |          |If software writes WWDTRLD when current WWDT counter value larger than WINCMP, WWDT reset signal will generate immediately.
     */
    __IO uint32_t  WWDTRLD;

    /**
     * WWDTCR
     * ===================================================================================================
     * Offset: 0x04  Window Watchdog Timer Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WWDTEN    |WWDT Enable
     * |        |          |Set this bit to enable Window Watchdog Timer counter counting.
     * |        |          |0 = Window Watchdog Timer counter is stopped.
     * |        |          |1 = Window Watchdog Timer counter is starting counting.
     * |[1]     |WWDTIE    |WWDT Interrupt Enable
     * |        |          |Setting this bit to enable the Window Watchdog Timer time-out interrupt function.
     * |        |          |0 = WWDT time-out interrupt function Disabled if WWDTIF (WWDTSR[0] WWDT compare match interrupt flag) is 1.
     * |        |          |1 = WWDT time-out interrupt function Enabled if WWDTIF (WWDTSR[0] WWDT compare match interrupt flag) is 1.
     * |[11:8]  |PERIODSEL |WWDT Pre-scale Period Select
     * |        |          |These 4-bit select the pre-scale period for the WWDT counter period.
     * |        |          |PERIODSEL Pre-scale Value Time out Period Max. Time out Interval (WWDT_CLK=10 kHz)
     * |        |          |Timeout period = Pre-scale * 64 * WWDT_CLK.
     * |        |          |PERIODSEL={0,1,2,3, 4, 5, 6,  7,  8,  9, 10, 11, 12,  13,  14,  15}
     * |        |          |Pre-scale={1,2,4,8,16,32,64,128,192,256,384,512,768,1024,1536,2048}
     * |[21:16] |WINCMP    |WWDT Window Compare Register
     * |        |          |Set this register to adjust the valid reload window.
     * |        |          |Note: Software can only write WWDTRLD to reload WWDT counter value when current WWDT counter value between 0 and WINCMP.
     * |        |          |If Software writes WWDTRLD when current WWDT counter value larger than WINCMP, WWDT reset signal will generate immediately.
     * |[31]    |DBGACK_WWDT|ICE debug mode acknowledge Disable
     * |        |          |0 = WWDT counter stopped if system is in Debug mode.
     * |        |          |1 = WWDT still counted even system is in Debug mode.
     */
    __IO uint32_t  WWDTCR;

    /**
     * WWDTSR
     * ===================================================================================================
     * Offset: 0x08  Window Watchdog Timer Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WWDTIF    |WWDT Compare Match Interrupt Flag
     * |        |          |When current WWDT counter value matches to WWCMP, this bit is set to 1. This bit will be cleared by writing 1 to itself.
     * |[1]     |WWDTRF    |WWDT Reset Flag
     * |        |          |When WWDT counter counts down to 0 or writes WWDTRLD during current WWDT counter value larger than WINCMP,
     * |        |          |chip will be reset and this bit is set to 1. This bit will be cleared to 0 by writing 1 to itself.
     */
    __IO uint32_t  WWDTSR;

    /**
     * WWDTCVR
     * ===================================================================================================
     * Offset: 0x0C  Watchdog Timer Alternative Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |WWDTCVAL  |WWDT Counter Value
     * |        |          |This register reflects the current WWDT counter value and this register is read only.
     */
    __IO uint32_t  WWDTCVR;

} WWDT_T;

/** @addtogroup WWDT_CONST WWDT Bit Field Definition
  Constant Definitions for WWDT Controller
  @{
 */

/* WWDT WWDTRLD Bit Field Definitions */
#define WWDT_WWDTRLD_WWDTRLD_Pos    0                                           /*!< WWDT WWDTRLD : WWDTRLD Position */
#define WWDT_WWDTRLD_WWDTRLD_Msk    (0xFFFFFFFFul << WWDT_WWDTRLD_WWDTRLD_Pos)  /*!< WWDT WWDTRLD : WWDTRLD Mask */

/* WWDT WWDTCR Bit Field Definitions */
#define WWDT_WWDTCR_DBGACK_WWDT_Pos 31                                          /*!< WWDT WWDTCR : DBGACK_WWDT Position */
#define WWDT_WWDTCR_DBGACK_WWDT_Msk (1ul << WWDT_WWDTCR_DBGACK_WWDT_Pos)        /*!< WWDT WWDTCR : DBGACK_WWDT Mask */

#define WWDT_WWDTCR_WINCMP_Pos      16                                          /*!< WWDT WWDTCR : WINCMP Position */
#define WWDT_WWDTCR_WINCMP_Msk      (0x3Ful << WWDT_WWDTCR_WINCMP_Pos)          /*!< WWDT WWDTCR : WINCMP Mask */

#define WWDT_WWDTCR_PERIODSEL_Pos   8                                           /*!< WWDT WWDTCR : PERIODSEL Position */
#define WWDT_WWDTCR_PERIODSEL_Msk   (0xFul << WWDT_WWDTCR_PERIODSEL_Pos)        /*!< WWDT WWDTCR : PERIODSEL Mask */

#define WWDT_WWDTCR_WWDTIE_Pos      1                                           /*!< WWDT WWDTCR : WWDTIE Position */
#define WWDT_WWDTCR_WWDTIE_Msk      (1ul << WWDT_WWDTCR_WWDTIE_Pos)             /*!< WWDT WWDTCR : WWDTIE Mask */

#define WWDT_WWDTCR_WWDTEN_Pos      0                                           /*!< WWDT WWDTCR : WWDTEN Position */
#define WWDT_WWDTCR_WWDTEN_Msk      (1ul << WWDT_WWDTCR_WWDTEN_Pos)             /*!< WWDT WWDTCR : WWDTEN Mask */

/* WWDT WWDTSR Bit Field Definitions */
#define WWDT_WWDTSR_WWDTRF_Pos      1                                           /*!< WWDT WWDTSR : WWDTRF Position */
#define WWDT_WWDTSR_WWDTRF_Msk      (1ul << WWDT_WWDTSR_WWDTRF_Pos)             /*!< WWDT WWDTSR : WWDTRF Mask */

#define WWDT_WWDTSR_WWDTIF_Pos      0                                           /*!< WWDT WWDTSR : WWDTIF Position */
#define WWDT_WWDTSR_WWDTIF_Msk      (1ul << WWDT_WWDTSR_WWDTIF_Pos)             /*!< WWDT WWDTSR : WWDTIF Mask */

/* WWDT WWDTCVR Bit Field Definitions */
#define WWDT_WWDTCVR_WWDTCVAL_Pos   0                                           /*!< WWDT WWDTCVR : WWDTRF Position */
#define WWDT_WWDTCVR_WWDTCVAL_Msk   (0x3Ful << WWDT_WWDTCVR_WWDTCVAL_Pos)       /*!< WWDT WWDTCVR : WWDTRF Mask */
/**@}*/ /* end of group WWDT_CONST */
/**@}*/ /* end of group WWDT */
/**@}*/ /* end of group REGISTER */


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup PERIPHERAL_BASE Peripheral Memory Base
  Memory Mapped Structure for Series Peripheral
  @{
 */
/* Peripheral and SRAM base address */
#define FLASH_BASE          ((     uint32_t)0x00000000)
#define SRAM_BASE           ((     uint32_t)0x20000000)
#define AHB_BASE            ((     uint32_t)0x50000000)
#define APB1_BASE           ((     uint32_t)0x40000000)
#define APB2_BASE           ((     uint32_t)0x40100000)

/* Peripheral memory map */
#define GPIO_BASE           (AHB_BASE       + 0x4000)                   /*!< GPIO Base Address                                   */
#define P0_BASE             (GPIO_BASE              )                   /*!< GPIO P0 Base Address                                */
#define P1_BASE             (GPIO_BASE      + 0x0040)                   /*!< GPIO P1 Base Address                                */
#define P2_BASE             (GPIO_BASE      + 0x0080)                   /*!< GPIO P2 Base Address                                */
#define P3_BASE             (GPIO_BASE      + 0x00C0)                   /*!< GPIO P3 Base Address                                */
#define P4_BASE             (GPIO_BASE      + 0x0100)                   /*!< GPIO P4 Base Address                                */
#define GPIO_DBNCECON_BASE  (GPIO_BASE      + 0x0180)                   /*!< GPIO De-bounce Cycle Control Base Address           */
#define GPIO_PIN_DATA_BASE  (GPIO_BASE      + 0x0200)                   /*!< GPIO Pin Data Input/Output Control Base Address     */

#define UART0_BASE          (APB1_BASE      + 0x50000)                  /*!< UART0 Base Address                               */
#define UART1_BASE          (APB2_BASE      + 0x50000)                  /*!< UART1 Base Address                               */

#define TIMER0_BASE         (APB1_BASE      + 0x10000)                  /*!< Timer0 Base Address                              */
#define TIMER1_BASE         (APB1_BASE      + 0x10020)                  /*!< Timer1 Base Address                              */
#define TIMER2_BASE         (APB2_BASE      + 0x10000)                  /*!< Timer2 Base Address                              */
#define TIMER3_BASE         (APB2_BASE      + 0x10020)                  /*!< Timer3 Base Address                              */

#define WDT_BASE            (APB1_BASE      + 0x4000)                   /*!< Watch Dog Timer Base Address                     */

#define WWDT_BASE           (APB1_BASE      + 0x4100)                   /*!< Window Watch Dog Timer Base Address              */

#define SPI0_BASE           (APB1_BASE      + 0x30000)                  /*!< SPI0 Base Address                                */
#define SPI1_BASE           (APB1_BASE      + 0x34000)                  /*!< SPI1 Base Address                                */

#define I2C0_BASE           (APB1_BASE      + 0x20000)                  /*!< I2C0 Base Address                                */
#define I2C1_BASE           (APB2_BASE      + 0x20000)                  /*!< I2C1 Base Address                                */

#define RTC_BASE            (APB1_BASE      + 0x08000)                  /*!< RTC Base Address                                 */

#define ADC_BASE            (APB1_BASE      + 0xE0000)                  /*!< ADC Base Address                                 */

#define ACMP01_BASE         (APB1_BASE      + 0xD0000)                  /*!< ACMP01 Base Address                              */
#define ACMP23_BASE         (APB2_BASE      + 0xD0000)                  /*!< ACMP23 Base Address                              */

#define CLK_BASE            (AHB_BASE       + 0x00200)                  /*!< System Clock Controller Base Address             */

#define GCR_BASE            (AHB_BASE       + 0x00000)                  /*!< System Global Controller Base Address            */

#define INT_BASE            (AHB_BASE       + 0x00300)                  /*!< Interrupt Source Controller Base Address         */

#define FMC_BASE            (AHB_BASE       + 0x0C000)                  /*!< Flash Memory Controller Base Address             */

#define PWMA_BASE           (APB1_BASE      + 0x40000)                  /*!< PWMA Base Address                                */
#define PWMB_BASE           (APB2_BASE      + 0x40000)                  /*!< PWMB Base Address                                */

#define EBI_BASE            (AHB_BASE       + 0x10000)                  /*!< EBI Base Address                                 */

#define HDIV_BASE           (AHB_BASE       + 0x14000)                  /*!< HDIV Base Address                                */

/**@}*/ /* PERIPHERAL */

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

/** @addtogroup PMODULE Peripheral Pointer
  The Declaration of Peripheral Pointer
  @{
 */
#define P0                  ((GPIO_T *) P0_BASE)                        /*!< GPIO PORT0 Configuration Struct                        */
#define P1                  ((GPIO_T *) P1_BASE)                        /*!< GPIO PORT1 Configuration Struct                        */
#define P2                  ((GPIO_T *) P2_BASE)                        /*!< GPIO PORT2 Configuration Struct                        */
#define P3                  ((GPIO_T *) P3_BASE)                        /*!< GPIO PORT3 Configuration Struct                        */
#define P4                  ((GPIO_T *) P4_BASE)                        /*!< GPIO PORT4 Configuration Struct                        */
#define GPIO                ((GPIO_DBNCECON_T *) GPIO_DBNCECON_BASE)    /*!< Interrupt De-bounce Cycle Control Configuration Struct */

#define UART0               ((UART_T *) UART0_BASE)                     /*!< UART0 Configuration Struct                       */
#define UART1               ((UART_T *) UART1_BASE)                     /*!< UART1 Configuration Struct                       */

#define TIMER0              ((TIMER_T *) TIMER0_BASE)                   /*!< TIMER0 Configuration Struct                      */
#define TIMER1              ((TIMER_T *) TIMER1_BASE)                   /*!< TIMER1 Configuration Struct                      */
#define TIMER2              ((TIMER_T *) TIMER2_BASE)                   /*!< TIMER2 Configuration Struct                      */
#define TIMER3              ((TIMER_T *) TIMER3_BASE)                   /*!< TIMER3 Configuration Struct                      */

#define WDT                 ((WDT_T *) WDT_BASE)                        /*!< Watch Dog Timer Configuration Struct             */

#define WWDT                ((WWDT_T *) WWDT_BASE)                      /*!< Window Watch Dog Timer Configuration Struct      */

#define SPI0                ((SPI_T *) SPI0_BASE)                       /*!< SPI0 Configuration Struct                        */
#define SPI1                ((SPI_T *) SPI1_BASE)                       /*!< SPI1 Configuration Struct                        */

#define I2C0                ((I2C_T *) I2C0_BASE)                       /*!< I2C0 Configuration Struct                        */
#define I2C1                ((I2C_T *) I2C1_BASE)                       /*!< I2C1 Configuration Struct                        */

#define ADC                 ((ADC_T *) ADC_BASE)                        /*!< ADC Configuration Struct                         */

#define ACMP01              ((ACMP_T *) ACMP01_BASE)                    /*!< ACMP01 Configuration Struct                      */
#define ACMP23              ((ACMP_T *) ACMP23_BASE)                    /*!< ACMP23 Configuration Struct                      */

#define CLK                 ((CLK_T *) CLK_BASE)                        /*!< System Clock Controller Configuration Struct     */

#define SYS                 ((GCR_T *) GCR_BASE)                        /*!< System Global Controller Configuration Struct    */

#define SYSINT              ((GCR_INT_T *) INT_BASE)                    /*!< Interrupt Source Controller Configuration Struct */

#define FMC                 ((FMC_T *) FMC_BASE)                        /*!< Flash Memory Controller */

#define PWMA                ((PWM_T *) PWMA_BASE)                       /*!< PWMA Configuration Struct                        */
#define PWMB                ((PWM_T *) PWMB_BASE)                       /*!< PWMB Configuration Struct                        */

#define EBI                 ((EBI_T *) EBI_BASE)                        /*!< EBI Configuration Struct                         */

#define HDIV                ((HDIV_T *) HDIV_BASE)                      /*!< HDIV Configuration Struct                         */

/**@}*/ /* end of group PMODULE */


//=============================================================================
typedef volatile unsigned char  vu8;
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
#define M8(adr)  (*((vu8  *) (adr)))
#define M16(adr) (*((vu16 *) (adr)))
#define M32(adr) (*((vu32 *) (adr)))

#define outpw(port,value)   (*((volatile unsigned int *)(port))=(value))
#define inpw(port)          ((*((volatile unsigned int *)(port))))
#define outpb(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inpb(port)          ((*((volatile unsigned char *)(port))))
#define outps(port,value)   (*((volatile unsigned short *)(port))=(value))
#define inps(port)          ((*((volatile unsigned short *)(port))))

#define outp32(port,value)  (*((volatile unsigned int *)(port))=(value))
#define inp32(port)         ((*((volatile unsigned int *)(port))))
#define outp8(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inp8(port)          ((*((volatile unsigned char *)(port))))
#define outp16(port,value)  (*((volatile unsigned short *)(port))=(value))
#define inp16(port)         ((*((volatile unsigned short *)(port))))


#define E_SUCCESS   0
#ifndef NULL
#define NULL        0
#endif

#define TRUE        1
#define FALSE       0

#define ENABLE      1
#define DISABLE     0

/* Bit Mask Definitions */
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000


/* Byte Mask Definitions */
#define BYTE0_Msk               (0x000000FF)
#define BYTE1_Msk               (0x0000FF00)
#define BYTE2_Msk               (0x00FF0000)
#define BYTE3_Msk               (0xFF000000)

#define _GET_BYTE0(u32Param)    ((u32Param & BYTE0_Msk)      )  /*!< Extract Byte 0 (Bit  0~ 7) from parameter u32Param */
#define _GET_BYTE1(u32Param)    ((u32Param & BYTE1_Msk) >>  8)  /*!< Extract Byte 1 (Bit  8~15) from parameter u32Param */
#define _GET_BYTE2(u32Param)    ((u32Param & BYTE2_Msk) >> 16)  /*!< Extract Byte 2 (Bit 16~23) from parameter u32Param */
#define _GET_BYTE3(u32Param)    ((u32Param & BYTE3_Msk) >> 24)  /*!< Extract Byte 3 (Bit 24~31) from parameter u32Param */


/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "sys.h"
#include "clk.h"
#include "adc.h"
#include "ebi.h"
#include "fmc.h"
#include "gpio.h"
#include "i2c.h"
#include "pwm.h"
#include "spi.h"
#include "timer.h"
#include "wdt.h"
#include "wwdt.h"
#include "uart.h"
#include "hdiv.h"
#include "acmp.h"
#endif

/* Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved. */

