/**************************************************************************//**
 * @file     NUC100Series.h
 * @version  V3.0
 * $Revision: 33 $
 * $Date: 17/05/26 10:54a $
 * @brief    NUC100 Series Peripheral Access Layer Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/



/**
  \mainpage Introduction
  *
  *
  * This user manual describes the usage of NUC100 Series MCU device driver
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

#ifndef __NUC100Series_H__
#define __NUC100Series_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
*/

/** @addtogroup CMSIS Device Definitions for CMSIS
  Interrupt Number Definition and Configurations for CMSIS
  @{
*/

/**
 * @details  Interrupt Number Definition. The maximum of 32 Specific Interrupts are possible.
 */

typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< Non Maskable Interrupt                                 */
    HardFault_IRQn              = -13,    /*!< Cortex-M0 Hard Fault Interrupt                         */
    SVCall_IRQn                 = -5,     /*!< Cortex-M0 SV Call Interrupt                            */
    PendSV_IRQn                 = -2,     /*!< Cortex-M0 Pend SV Interrupt                            */
    SysTick_IRQn                = -1,     /*!< Cortex-M0 System Tick Interrupt                        */

    /******  ARMIKMCU Swift specific Interrupt Numbers ************************************************/
    BOD_IRQn                  = 0,        /*!< Brown-Out Low Voltage Detected Interrupt               */
    WDT_IRQn                  = 1,        /*!< Watch Dog Timer Interrupt                              */
    EINT0_IRQn                = 2,        /*!< EINT0 Interrupt                                        */
    EINT1_IRQn                = 3,        /*!< EINT1 Interrupt                                        */
    GPAB_IRQn                 = 4,        /*!< GPIO_PA/PB Interrupt                                   */
    GPCDEF_IRQn               = 5,        /*!< GPIO_PC/PD/PE/PF Interrupt                             */
    PWMA_IRQn                 = 6,        /*!< PWMA Interrupt                                         */
    PWMB_IRQn                 = 7,        /*!< PWMB Interrupt                                         */
    TMR0_IRQn                 = 8,        /*!< TIMER0 Interrupt                                       */
    TMR1_IRQn                 = 9,        /*!< TIMER1 Interrupt                                       */
    TMR2_IRQn                 = 10,       /*!< TIMER2 Interrupt                                       */
    TMR3_IRQn                 = 11,       /*!< TIMER3 Interrupt                                       */
    UART02_IRQn               = 12,       /*!< UART0/UART2 Interrupt                                  */
    UART1_IRQn                = 13,       /*!< UART1 Interrupt                                        */
    SPI0_IRQn                 = 14,       /*!< SPI0 Interrupt                                         */
    SPI1_IRQn                 = 15,       /*!< SPI1 Interrupt                                         */
    SPI2_IRQn                 = 16,       /*!< SPI2 Interrupt                                         */
    SPI3_IRQn                 = 17,       /*!< SPI3 Interrupt                                         */
    I2C0_IRQn                 = 18,       /*!< I2C0 Interrupt                                         */
    I2C1_IRQn                 = 19,       /*!< I2C1 Interrupt                                         */
    CAN0_IRQn                 = 20,       /*!< CAN0 Interrupt                                         */
    CAN1_IRQn                 = 21,       /*!< CAN1 Interrupt                                         */
    SC012_IRQn                = 22,       /*!< SC0/SC1/SC2 Interrupt                                  */
    USBD_IRQn                 = 23,       /*!< USB device Interrupt                                   */
    PS2_IRQn                  = 24,       /*!< PS/2 device Interrupt                                  */
    ACMP_IRQn                 = 25,       /*!< ACMP0 Interrupt                                        */
    PDMA_IRQn                 = 26,       /*!< PDMA Interrupt                                         */
    I2S_IRQn                  = 27,       /*!< I2S Interrupt                                          */
    PWRWU_IRQn                = 28,       /*!< Power Down Wake Up Interrupt                           */
    ADC_IRQn                  = 29,       /*!< ADC Interrupt                                          */
    IRC_IRQn                  = 30,       /*!< IRC TRIM Interrupt                                     */
    RTC_IRQn                  = 31        /*!< RTC Interrupt                                          */
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


/*@}*/ /* end of group CMSIS */


#include "core_cm0.h"                   /* Cortex-M0 processor and core peripherals               */
#include "system_NUC100Series.h"        /* NUC100 System                                          */

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif


/*-------------------------------- Device Specific Peripheral registers structures ---------------------*/
/** @addtogroup REGISTER Control Register
  Peripheral Control Registers
  @{
 */

/*---------------------- Analog Comparator Controller -------------------------*/
/**
    @addtogroup ACMP Analog Comparator Controller (ACMP)
    Memory Mapped Structure for ACMP Controller
@{ */



typedef struct
{


/**
 * @var ACMP_T::CMPCR
 * Offset: 0x00~0x04  Analog Comparator Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CMPEN     |Comparator Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[1]     |CMPIE     |Comparator Interrupt Enable
 * |        |          |0 = Interrupt function
 * |        |          |Disabled.
 * |        |          |1 = Interrupt function
 * |        |          |Enabled.
 * |[2]     |CMP_HYSEN |Comparator Hysteresis Enable
 * |        |          |0 = Hysteresis function Disabled (Default).
 * |        |          |1 = Hysteresis function
 * |        |          |Enabled.
 * |[4]     |CMPCN     |Comparator Negative Input Selection
 * |        |          |0 = The source of the negative comparator input is from ACMPn_N pin (n = 0, 1).
 * |        |          |1 = Internal band-gap reference voltage is selected as the source
 * |        |          |    of negative comparator input.
 * @var ACMP_T::CMPSR
 * Offset: 0x08  Analog Comparator Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CMPF0     |Comparator 0 Interrupt Flag
 * |        |          |This bit is set by hardware whenever the comparator 0 output changes state.
 * |        |          |This will cause an interrupt if CMPCR0[1] is set to 1.
 * |        |          |Write 1 to clear this bit to 0.
 * |[1]     |CMPF1     |Comparator 1 Interrupt Flag
 * |        |          |This bit is set by hardware whenever the comparator 1 output changes state.
 * |        |          |This will cause an interrupt if CMPCR1[1] is set to 1.
 * |        |          |Write 1 to clear this bit to 0.
 * |[2]     |CO0       |Comparator 0 Output
 * |        |          |Synchronized to the APB clock to allow reading by software.
 * |        |          |Cleared when the comparator 0 is disabled (CMPCR0[0] = 0).
 * |[3]     |CO1       |Comparator 1 Output
 * |        |          |Synchronized to the APB clock to allow reading by software.
 * |        |          |Cleared when the comparator 1 is disabled (CMPCR1[0] = 0).
 */

    __IO uint32_t CMPCR[2];      /* Offset: 0x00  Analog Comparator 0 Control Register                               */
    __IO uint32_t CMPSR;         /* Offset: 0x04  Analog Comparator 1 Control Register                               */

} ACMP_T;



/**
    @addtogroup ACMP_CONST ACMP Bit Field Definition
    Constant Definitions for ACMP Controller
@{ */


/* CMPCR Bit Field Definitions */
#define ACMP_CMPCR_CMPCN_Pos       4                                   /*!< ACMP_T::CMPCR: CMPCN Position */
#define ACMP_CMPCR_CMPCN_Msk       (1ul << ACMP_CMPCR_CMPCN_Pos)       /*!< ACMP_T::CMPCR: CMPCN Mask */

#define ACMP_CMPCR_CMP_HYSEN_Pos   2                                   /*!< ACMP_T::CMPCR: CMP_HYSEN Position */
#define ACMP_CMPCR_CMP_HYSEN_Msk   (1ul << ACMP_CMPCR_CMP_HYSEN_Pos)   /*!< ACMP_T::CMPCR: CMP_HYSEN Mask */

#define ACMP_CMPCR_CMPIE_Pos       1                                   /*!< ACMP_T::CMPCR: CMPIE Position */
#define ACMP_CMPCR_CMPIE_Msk       (1ul << ACMP_CMPCR_CMPIE_Pos)       /*!< ACMP_T::CMPCR: CMPIE Mask */

#define ACMP_CMPCR_CMPEN_Pos       0                                   /*!< ACMP_T::CMPCR: CMPEN Position */
#define ACMP_CMPCR_CMPEN_Msk       (1ul << ACMP_CMPCR_CMPEN_Pos)       /*!< ACMP_T::CMPCR: CMPEN Mask */

/* CMPSR Bit Field Definitions */
#define ACMP_CMPSR_CO1_Pos     3                                 /*!< ACMP_T::CMPSR: CO1 Position */
#define ACMP_CMPSR_CO1_Msk     (1ul << ACMP_CMPSR_CO1_Pos)       /*!< ACMP_T::CMPSR: CO1 Mask */

#define ACMP_CMPSR_CO0_Pos     2                                 /*!< ACMP_T::CMPSR: CO0 Position */
#define ACMP_CMPSR_CO0_Msk     (1ul << ACMP_CMPSR_CO0_Pos)       /*!< ACMP_T::CMPSR: CO0 Mask */

#define ACMP_CMPSR_CMPF1_Pos   1                                 /*!< ACMP_T::CMPSR: CMPF1 Position */
#define ACMP_CMPSR_CMPF1_Msk   (1ul << ACMP_CMPSR_CMPF1_Pos)     /*!< ACMP_T::CMPSR: CMPF1 Mask */

#define ACMP_CMPSR_CMPF0_Pos   0                                 /*!< ACMP_T::CMPSR: CMPF0 Position */
#define ACMP_CMPSR_CMPF0_Msk   (1ul << ACMP_CMPSR_CMPF0_Pos)     /*!< ACMP_T::CMPSR: CMPF0 Mask */

/*@}*/ /* end of group ACMP_CONST */
/*@}*/ /* end of group ACMP */




/*----------------------------- ADC Controller -------------------------------*/
/** @addtogroup ADC Analog to Digital Converter (ADC)
  Memory Mapped Structure for ADC Controller
  @{
 */


typedef struct
{



/**
 * @var ADC_T::ADDR
 * Offset: 0x00-0x1C  ADC Data Register x
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |RSLT      |A/D Conversion Result
 * |        |          |This field contains conversion result of ADC.
 * |        |          |When DMOF bit (ADCR[31]) set to 0, 12-bit ADC conversion result with unsigned format will be
 * |        |          |filled in RSLT (ADDRx[11:0], x=0~7) and zero will be filled in RSLT (ADDRx[15:12], x=0~7).
 * |        |          |When DMOF bit (ADCR[31]) set to 1, 12-bit ADC conversion result with 2'complement format
 * |        |          |will be filled in RSLT(ADDRx[11:0], x=0~7) and signed bits to will be filled in RSLT
 * |        |          |(ADDRx[15:12], x=0~7).
 * |[16]    |OVERRUN   |Overrun Flag
 * |        |          |0 = Data in RSLT (ADDRx[15:0], x=0~7) is recent conversion result.
 * |        |          |1 = Data in RSLT (ADDRx[15:0], x=0~7) is overwritten.
 * |        |          |If converted data in RSLT has not been read before new conversion result is loaded to this
 * |        |          |register, OVERRUN is set to 1 and previous conversion result is gone.
 * |        |          |It is cleared by hardware after ADDR register is read.
 * |        |          |This is a read only bit.
 * |[17]    |VALID     |Valid Flag
 * |        |          |0 = Data in RSLT bits (ADDRx[15:0], x=0~7) is not valid.
 * |        |          |1 = Data in RSLT bits (ADDRx[15:0], x=0~7) is valid.
 * |        |          |This bit is set to 1 when corresponding channel analog input conversion is completed and
 * |        |          |cleared by hardware after ADDR register is read.
 * |        |          |This is a read only bit
 * @var ADC_T::ADCR
 * Offset: 0x20  ADC Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |ADEN      |A/D Converter Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |        |          |Before starting A/D conversion function, this bit should be set to 1.
 * |        |          |Clear it to 0 to disable A/D converter analog circuit for saving power consumption.
 * |[1]     |ADIE      |A/D Interrupt Enable
 * |        |          |0 = A/D interrupt function Disabled.
 * |        |          |1 = A/D interrupt function Enabled.
 * |        |          |A/D conversion end interrupt request is generated if ADIE bit (ADCR[1]) is set to 1.
 * |[3:2]   |ADMD      |A/D Converter Operation Mode
 * |        |          |00 = Single conversion.
 * |        |          |01 = Reserved.
 * |        |          |10 = Single-cycle scan.
 * |        |          |11 = Continuous scan.
 * |        |          |When changing the operation mode, software should disable ADST bit (ADCR[11]) firstly.
 * |[5:4]   |TRGS      |Hardware Trigger Source
 * |        |          |00 = A/D conversion is started by external STADC pin.
 * |        |          |11 = A/D conversion is started by PWM Center-aligned trigger.
 * |        |          |Others = Reserved.
 * |        |          |Software should disable TRGEN (ADCR[8]) and ADST (ADCR[11]) before change TRGS.
 * |[7:6]   |TRGCOND   |External Trigger Condition
 * |        |          |These two bits decide external pin STADC trigger event is level or edge.
 * |        |          |The signal must be kept at stable state at least 8 PCLKs for level trigger and 4 PCLKs at
 * |        |          |high and low state for edge trigger.
 * |        |          |00 = Low level.
 * |        |          |01 = High level.
 * |        |          |10 = Falling edge.
 * |        |          |11 = Rising edge.
 * |[8]     |TRGEN     |Hardware Trigger Enable
 * |        |          |Enable or disable triggering of A/D conversion by hardware (external STADC pin or PWM
 * |        |          |Center-aligned trigger).
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |        |          |ADC hardware trigger function is only supported in single-cycle scan mode.
 * |        |          |If hardware trigger mode, the ADST bit (ADCR[11]) can be set to 1 by the selected hardware
 * |        |          |trigger source.
 * |[9]     |PTEN      |PDMA Transfer Enable
 * |        |          |0 = PDMA data transfer Disabled.
 * |        |          |1 = PDMA data transfer in ADDR 0~7 Enabled.
 * |        |          |When A/D conversion is completed, the converted data is loaded into ADDR 0~7, software can
 * |        |          |enable this bit to generate a PDMA data transfer request.
 * |        |          |When PTEN=1, software must set ADIE=0 (ADCR[1]) to disable interrupt.
 * |[10]    |DIFFEN    |Differential Input Mode Enable
 * |        |          |0 = Single-end analog input mode.
 * |        |          |1 = Differential analog input mode.
 * |        |          |Differential   input Paired Channel
 * |        |          |Differential input voltage (Vdiff) = Vplus - Vminus, where Vplus
 * |        |          |is the analog input; Vminus is the inverted analog input.
 * |        |          |In differential input mode, only the even number of the two corresponding channels needs to
 * |        |          |be enabled in ADCHER.
 * |        |          |The conversion result will be placed to the corresponding data register of the enabled
 * |        |          |channel.
 * |[11]    |ADST      |A/D Conversion Start
 * |        |          |0 = Conversion stops and A/D converter enter idle state.
 * |        |          |1 = Conversion starts.
 * |        |          |ADST bit can be set to 1 from three sources: software, PWM Center-aligned trigger and
 * |        |          |external pin STADC.
 * |        |          |ADST will be cleared to 0 by hardware automatically at the ends of single mode and
 * |        |          |single-cycle scan mode.
 * |        |          |In continuous scan mode, A/D conversion is continuously performed until software writes 0 to
 * |        |          |this bit or chip reset.
 * |[31]    |DMOF      |A/D Differential Input Mode Output Format
 * |        |          |0 = A/D Conversion result will be filled in RSLT at ADDRx registers with unsigned format.
 * |        |          |1 = A/D Conversion result will be filled in RSLT at ADDRx registers with 2'complement
 * |        |          |format.
 * @var ADC_T::ADCHER
 * Offset: 0x24  ADC Channel Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |CHEN      |Analog Input Channel Enable
 * |        |          |Set CHEN[7:0] to enable the corresponding analog input channel 7 ~ 0.
 * |        |          |If DIFFEN bit (ADCR[10]) is set to 1, only the even number channels need to be enabled.
 * |        |          |0 = ADC input channel Disabled.
 * |        |          |1 = ADC input channel Enabled.
 * |[9:8]   |PRESEL    |Analog Input Channel 7 Select
 * |        |          |00 = External analog input.
 * |        |          |01 = Internal band-gap voltage.
 * |        |          |10 = Internal temperature sensor.
 * |        |          |11 = Reserved.
 * |        |          |Note:
 * |        |          |When software select the band-gap voltage as the analog input source of ADC channel 7, ADC
 * |        |          |clock rate needs to be limited to slower than 300 kHz.
 * @var ADC_T::ADCMPR
 * Offset: 0x28  ADC Compare Register x
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CMPEN     |Compare Enable
 * |        |          |0 = Compare function Disabled.
 * |        |          |1 = Compare function Enabled.
 * |        |          |Set this bit to 1 to enable ADC controller to compare CMPD (ADCMPR0/1[27:16]) with specified
 * |        |          |channel conversion result when converted data is loaded into ADDR register.
 * |[1]     |CMPIE     |Compare Interrupt Enable
 * |        |          |0 = Compare function interrupt Disabled.
 * |        |          |1 = Compare function interrupt Enabled.
 * |        |          |If the compare function is enabled and the compare condition matches the setting of CMPCOND
 * |        |          |(ADCMPR0/1[2]) and CMPMATCNT (ADCMPR0/1[11:8]), CMPF0/1 bit (ADSR[1]/[2]) will be asserted,
 * |        |          |in the meanwhile, if CMPIE (ADCMPR0/1[1]) is set to 1, a compare interrupt request is
 * |        |          |generated.
 * |[2]     |CMPCOND   |Compare Condition
 * |        |          |0 = Set the compare condition as that when a 12-bit A/D conversion result is less than the
 * |        |          |12-bit CMPD (ADCMPR0/1[27:16]), the internal match counter will increase one.
 * |        |          |1 = Set the compare condition as that when a 12-bit A/D conversion result is greater or
 * |        |          |equal to the 12-bit CMPD (ADCMPR0/1[27:16]), the internal match counter will increase one.
 * |        |          |Note: When the internal counter reaches the value to (CMPMATCNT (ADCMPR0/1[11:8])+1), the
 * |        |          |CMPF0/1 bit (ADSR[1]/[2]) will be set.
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
 * |        |          |When the specified A/D channel analog conversion result matches the compare condition
 * |        |          |defined by CMPCOND (ADCMPR0/1[2]), the internal match counter will increase 1.
 * |        |          |When the internal counter reaches the value to (CMPMATCNT (ADCMPR0/1[11:8]) +1), the CMPF0/1
 * |        |          |bit (ADSR[1]/[2]) will be set.
 * |[27:16] |CMPD      |Comparison Data
 * |        |          |The 12-bit data is used to compare with conversion result of specified channel.
 * |        |          |When DMOF bit (ADCR[31]) is set to 0, ADC comparator compares CMPD with conversion result
 * |        |          |with unsigned format.
 * |        |          |CMPD should be filled in unsigned format.
 * |        |          |When DMOF bit (ADCR[31]) is set to 1, ADC comparator compares CMPD with conversion result
 * |        |          |with 2'complement format.
 * |        |          |CMPD should be filled in 2'complement format.
 * @var ADC_T::ADSR
 * Offset: 0x30  ADC Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |ADF       |A/D Conversion End Flag
 * |        |          |A status flag that indicates the end of A/D conversion.
 * |        |          |ADF is set to 1 at these two conditions:
 * |        |          |1. When A/D conversion ends in Single mode.
 * |        |          |2. When A/D conversion ends on all specified channels in Scan mode.
 * |        |          |This flag can be cleared by writing 1 to itself.
 * |[1]     |CMPF0     |Compare Flag
 * |        |          |When the selected channel A/D conversion result meets setting condition in ADCMPR0 then this
 * |        |          |bit is set to 1.
 * |        |          |And it is cleared by writing 1 to self.
 * |        |          |0 = Conversion result in ADDR does not meet ADCMPR0 setting.
 * |        |          |1 = Conversion result in ADDR meets ADCMPR0 setting.
 * |[2]     |CMPF1     |Compare Flag
 * |        |          |When the selected channel A/D conversion result meets setting condition in ADCMPR1 then this
 * |        |          |bit is set to 1.
 * |        |          |And it is cleared by writing 1 to self.
 * |        |          |0 = Conversion result in ADDR does not meet ADCMPR1 setting.
 * |        |          |1 = Conversion result in ADDR meets ADCMPR1 setting.
 * |[3]     |BUSY      |BUSY/IDLE
 * |        |          |0 = A/D converter is in idle state.
 * |        |          |1 = A/D converter is busy at conversion.
 * |        |          |This bit is mirror of as ADST bit (ADCR[11]).
 * |        |          |It is read only.
 * |[6:4]   |CHANNEL   |Current Conversion Channel
 * |        |          |This field reflects the current conversion channel when BUSY = 1 (ADSR[3]).
 * |        |          |When BUSY = 0, it shows the number of the next converted channel.
 * |        |          |It is read only.
 * |[15:8]  |VALID     |Data Valid Flag
 * |        |          |It is a mirror of VALID bit (ADDR0~7[17]).
 * |        |          |It is read only.
 * |[23:16] |OVERRUN   |Overrun Flag
 * |        |          |It is a mirror to OVERRUN bit (ADDR0~7[16]).
 * |        |          |It is read only.
 * @var ADC_T::ADPDMA
 * Offset: 0x40  ADC PDMA Current Transfer Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[17:0]  |AD_PDMA   |ADC PDMA Current Transfer Data Register
 * |        |          |When PDMA transferring, read this register can monitor current PDMA transfer data.
 * |        |          |Current PDMA transfer data is the content of ADDR0 ~ ADDR7.
 * |        |          |This is a read only register.
 */

    __I  uint32_t ADDR[8];       /* Offset: 0x00-0x1C  ADC Data Register x                                           */
    __IO uint32_t ADCR;          /* Offset: 0x20  ADC Control Register                                               */
    __IO uint32_t ADCHER;        /* Offset: 0x24  ADC Channel Enable Register                                        */
    __IO uint32_t ADCMPR[2];     /* Offset: 0x28  ADC Compare Register x                                             */
    __IO uint32_t ADSR;          /* Offset: 0x30  ADC Status Register                                                */
    __I  uint32_t RESERVE0[3];  
    __I  uint32_t ADPDMA;        /* Offset: 0x40  ADC PDMA Current Transfer Data Register                            */

} ADC_T;



/**
    @addtogroup ADC_CONST ADC Bit Field Definition
    Constant Definitions for ADC Controller
@{ */

/* ADDR Bit Field Definitions */
#define ADC_ADDR_VALID_Pos      17                                /*!< ADC_T::ADDR: VALID Position */
#define ADC_ADDR_VALID_Msk      (1ul << ADC_ADDR_VALID_Pos)       /*!< ADC_T::ADDR: VALID Mask */

#define ADC_ADDR_OVERRUN_Pos    16                                /*!< ADC_T::ADDR: OVERRUN Position */
#define ADC_ADDR_OVERRUN_Msk    (1ul << ADC_ADDR_OVERRUN_Pos)     /*!< ADC_T::ADDR: OVERRUN Mask */

#define ADC_ADDR_RSLT_Pos       0                                 /*!< ADC_T::ADDR: RSLT Position */
#define ADC_ADDR_RSLT_Msk       (0xFFFFul << ADC_ADDR_RSLT_Pos)   /*!< ADC_T::ADDR: RSLT Mask */

/* ADCR Bit Field Definitions */
#define ADC_ADCR_DMOF_Pos       31                                /*!< ADC_T::ADCR: DMOF Position */
#define ADC_ADCR_DMOF_Msk       (1ul << ADC_ADCR_DMOF_Pos)        /*!< ADC_T::ADCR: DMOF Mask */

#define ADC_ADCR_ADST_Pos       11                                /*!< ADC_T::ADCR: ADST Position */
#define ADC_ADCR_ADST_Msk       (1ul << ADC_ADCR_ADST_Pos)        /*!< ADC_T::ADCR: ADST Mask */

#define ADC_ADCR_DIFFEN_Pos     10                                /*!< ADC_T::ADCR: DIFFEN Position */
#define ADC_ADCR_DIFFEN_Msk     (1ul << ADC_ADCR_DIFFEN_Pos)      /*!< ADC_T::ADCR: DIFFEN Mask */

#define ADC_ADCR_PTEN_Pos       9                                 /*!< ADC_T::ADCR: PTEN Position */
#define ADC_ADCR_PTEN_Msk       (1ul << ADC_ADCR_PTEN_Pos)        /*!< ADC_T::ADCR: PTEN Mask */

#define ADC_ADCR_TRGEN_Pos      8                                 /*!< ADC_T::ADCR: TRGEN Position */
#define ADC_ADCR_TRGEN_Msk      (1ul << ADC_ADCR_TRGEN_Pos)       /*!< ADC_T::ADCR: TRGEN Mask */

#define ADC_ADCR_TRGCOND_Pos    6                                 /*!< ADC_T::ADCR: TRGCOND Position */
#define ADC_ADCR_TRGCOND_Msk    (3ul << ADC_ADCR_TRGCOND_Pos)     /*!< ADC_T::ADCR: TRGCOND Mask */

#define ADC_ADCR_TRGS_Pos       4                                 /*!< ADC_T::ADCR: TRGS Position */
#define ADC_ADCR_TRGS_Msk       (3ul << ADC_ADCR_TRGS_Pos)        /*!< ADC_T::ADCR: TRGS Mask */

#define ADC_ADCR_ADMD_Pos       2                                 /*!< ADC_T::ADCR: ADMD Position */
#define ADC_ADCR_ADMD_Msk       (3ul << ADC_ADCR_ADMD_Pos)        /*!< ADC_T::ADCR: ADMD Mask */

#define ADC_ADCR_ADIE_Pos       1                                 /*!< ADC_T::ADCR: ADIE Position */
#define ADC_ADCR_ADIE_Msk       (1ul << ADC_ADCR_ADIE_Pos)        /*!< ADC_T::ADCR: ADIE Mask */

#define ADC_ADCR_ADEN_Pos       0                                 /*!< ADC_T::ADCR: ADEN Position */
#define ADC_ADCR_ADEN_Msk       (1ul << ADC_ADCR_ADEN_Pos)        /*!< ADC_T::ADCR: ADEN Mask */

/* ADCHER Bit Field Definitions */
#define ADC_ADCHER_PRESEL_Pos   8                                 /*!< ADC_T::ADCHER: PRESEL Position */
#define ADC_ADCHER_PRESEL_Msk   (3ul << ADC_ADCHER_PRESEL_Pos)    /*!< ADC_T::ADCHER: PRESEL Mask */

#define ADC_ADCHER_CHEN_Pos     0                                 /*!< ADC_T::ADCHER: CHEN Position */
#define ADC_ADCHER_CHEN_Msk     (0xFFul << ADC_ADCHER_CHEN_Pos)   /*!< ADC_T::ADCHER: CHEN Mask */

/* ADCMPR Bit Field Definitions */
#define ADC_ADCMPR_CMPD_Pos        16                                    /*!< ADC_T::ADCMPR: CMPD Position */
#define ADC_ADCMPR_CMPD_Msk        (0xFFFul << ADC_ADCMPR_CMPD_Pos)      /*!< ADC_T::ADCMPR: CMPD Mask */

#define ADC_ADCMPR_CMPMATCNT_Pos   8                                     /*!< ADC_T::ADCMPR: CMPMATCNT Position */
#define ADC_ADCMPR_CMPMATCNT_Msk   (0xFul << ADC_ADCMPR_CMPMATCNT_Pos)   /*!< ADC_T::ADCMPR: CMPMATCNT Mask */

#define ADC_ADCMPR_CMPCH_Pos       3                                     /*!< ADC_T::ADCMPR: CMPCH Position */
#define ADC_ADCMPR_CMPCH_Msk       (7ul << ADC_ADCMPR_CMPCH_Pos)         /*!< ADC_T::ADCMPR: CMPCH Mask */

#define ADC_ADCMPR_CMPCOND_Pos     2                                     /*!< ADC_T::ADCMPR: CMPCOND Position */
#define ADC_ADCMPR_CMPCOND_Msk     (1ul << ADC_ADCMPR_CMPCOND_Pos)       /*!< ADC_T::ADCMPR: CMPCOND Mask */

#define ADC_ADCMPR_CMPIE_Pos       1                                     /*!< ADC_T::ADCMPR: CMPIE Position */
#define ADC_ADCMPR_CMPIE_Msk       (1ul << ADC_ADCMPR_CMPIE_Pos)         /*!< ADC_T::ADCMPR: CMPIE Mask */

#define ADC_ADCMPR_CMPEN_Pos       0                                     /*!< ADC_T::ADCMPR: CMPEN Position */
#define ADC_ADCMPR_CMPEN_Msk       (1ul << ADC_ADCMPR_CMPEN_Pos)         /*!< ADC_T::ADCMPR: CMPEN Mask */

/* ADSR Bit Field Definitions */
#define ADC_ADSR_OVERRUN_Pos       16                                    /*!< ADC_T::ADSR: OVERRUN Position */
#define ADC_ADSR_OVERRUN_Msk       (0xFFul << ADC_ADSR_OVERRUN_Pos)      /*!< ADC_T::ADSR: OVERRUN Mask */

#define ADC_ADSR_VALID_Pos         8                                     /*!< ADC_T::ADSR: VALID Position */
#define ADC_ADSR_VALID_Msk         (0xFFul << ADC_ADSR_VALID_Pos)        /*!< ADC_T::ADSR: VALID Mask */

#define ADC_ADSR_CHANNEL_Pos       4                                     /*!< ADC_T::ADSR: CHANNEL Position */
#define ADC_ADSR_CHANNEL_Msk       (7ul << ADC_ADSR_CHANNEL_Pos)         /*!< ADC_T::ADSR: CHANNEL Mask */

#define ADC_ADSR_BUSY_Pos          3                                     /*!< ADC_T::ADSR: BUSY Position */
#define ADC_ADSR_BUSY_Msk          (1ul << ADC_ADSR_BUSY_Pos)            /*!< ADC_T::ADSR: BUSY Mask */

#define ADC_ADSR_CMPF1_Pos         2                                     /*!< ADC_T::ADSR: CMPF1 Position */
#define ADC_ADSR_CMPF1_Msk         (1ul << ADC_ADSR_CMPF1_Pos)           /*!< ADC_T::ADSR: CMPF1 Mask */

#define ADC_ADSR_CMPF0_Pos         1                                     /*!< ADC_T::ADSR: CMPF0 Position */
#define ADC_ADSR_CMPF0_Msk         (1ul << ADC_ADSR_CMPF0_Pos)           /*!< ADC_T::ADSR: CMPF0 Mask */

#define ADC_ADSR_ADF_Pos           0                                     /*!< ADC_T::ADSR: ADF Position */
#define ADC_ADSR_ADF_Msk           (1ul << ADC_ADSR_ADF_Pos)             /*!< ADC_T::ADSR: ADF Mask */

/* ADPDMA Bit Field Definitions */
#define ADC_ADPDMA_AD_PDMA_Pos     0                                     /*!< ADC_T::ADPDMA: AD_PDMA Position */
#define ADC_ADPDMA_AD_PDMA_Msk     (0x3FFFFul << ADC_ADPDMA_AD_PDMA_Pos) /*!< ADC_T::ADPDMA: AD_PDMA Mask */

/*@}*/ /* end of group ADC_CONST */
/*@}*/ /* end of group ADC */



/*---------------------------- Clock Controller ------------------------------*/
/** @addtogroup CLK System Clock Controller (CLK)
  Memory Mapped Structure for System Clock Controller
  @{
 */


typedef struct
{



/**
 * @var CLK_T::PWRCON
 * Offset: 0x00  System Power-down Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |XTL12M_EN |External 4~24 MHz High Speed Crystal Enable (HXT) Control (Write Protect)
 * |        |          |The bit default value is set by flash controller user configuration register CFOSC (Config0[26:24]).
 * |        |          |When the default clock source is from external 4~24 MHz high speed crystal, this bit is set to 1 automatically.
 * |        |          |0 = External 4~24 MHz high speed crystal oscillator (HXT) Disabled.
 * |        |          |1 = External 4~24 MHz high speed crystal oscillator (HXT) Enabled.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.    
 * |[1]     |XTL32K_EN |External 32.768 KHz Low Speed Crystal Enable (LXT) Control (Write Protect)
 * |        |          |0 = External 32.768 kHz low speed crystal oscillator (LXT) Disabled.
 * |        |          |1 = External 32.768 kHz low speed crystal oscillator (LXT) Enabled (Normal operation).
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register. 
 * |[2]     |OSC22M_EN |Internal 22.1184 MHz High Speed Oscillator (HIRC) Enable Control (Write Protect)
 * |        |          |0 = Internal 22.1184 MHz high speed oscillator (HIRC) Disabled.
 * |        |          |1 = Internal 22.1184 MHz high speed oscillator (HIRC) Enabled.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register. 
 * |[3]     |OSC10K_EN |Internal 10 KHz Low Speed Oscillator (LIRC) Enable Control (Write Protect)
 * |        |          |0 = Internal 10 kHz low speed oscillator (LIRC) Disabled.
 * |        |          |1 = Internal 10 kHz low speed oscillator (LIRC) Enabled.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[4]     |PD_WU_DLY |Wake-up Delay Counter Enable Control (Write Protect)
 * |        |          |When the chip wakes up from Power-down mode, the clock control will delay certain clock cycles to wait system clock stable.
 * |        |          |The delayed clock cycle is 4096 clock cycles when chip work at external 4~24 MHz high speed crystal, and 256 clock cycles when chip work at internal 22.1184 MHz high speed oscillator.
 * |        |          |0 = Clock cycles delay Disabled.
 * |        |          |1 = Clock cycles delay Enabled.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[5]     |PD_WU_INT_EN|Power-Down Mode Wake-Up Interrupt Enable Control (Write Protect)
 * |        |          |0 = Power-down mode wake-up interrupt Disabled.
 * |        |          |1 = Power-down mode wake-up interrupt Enabled.
 * |        |          |Note1: The interrupt will occur when both PD_WU_STS and PD_WU_INT_EN are high.
 * |        |          |Note2: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[6]     |PD_WU_STS |Power-Down Mode Wake-Up Interrupt Status
 * |        |          |Set by "Power-down wake-up event", it indicates that resume from Power-down mode.
 * |        |          |The flag is set if the GPIO, USB, UART, WDT, I2C, TIMER, ACMP, BOD or RTC wake-up occurred.
 * |        |          |Write 1 to clear the bit to 0.
 * |        |          |Note: This bit is working only if PD_WU_INT_EN (PWRCON[5]) set to 1.
 * |[7]     |PWR_DOWN_EN|System Power-Down Enable Bit (Write Protect)
 * |        |          |When this bit is set to 1, Power-down mode is enabled and chip Power-down behavior willdepends on the PD_WAIT_CPU bit.
 * |        |          |(a) If the PD_WAIT_CPU is 0, then the chip enters Power-down mode immediately after the PWR_DOWN_EN bit set.
 * |        |          |(b) if the PD_WAIT_CPU is 1, then the chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode. (recommend)
 * |        |          |When chip wakes up from Power-down mode, this bit is cleared by hardware.
 * |        |          |User needs to set this bit again for next Power-down.
 * |        |          |In Power-down mode, external 4~24 MHz high speed crystal oscillator and the internal 22.1184 MHz high speed oscillator will be disabled in this mode, 
 * |        |          |but the external 32.768 kHz low speed crystal and internal 10 kHz low speed oscillator are not controlled by Power-down mode.
 * |        |          |In Power- down mode, the PLL and system clock are disabled, and ignored the clock source selection.
 * |        |          |The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from external 32.768 kHz low speed crystal oscillator or the internal 10 kHz low speed oscillator.
 * |        |          |0 = Chip operating normally or chip in Idle mode because of WFI command.
 * |        |          |1 = Chip enters Power-down mode instantly or waits CPU sleep command WFI.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[8]     |PD_WAIT_CPU|This Bit Control The Power-Down Entry Condition (Write Protect)
 * |        |          |0 = Chip enters Power-down mode when the PWR_DOWN_EN bit is set to 1.
 * |        |          |1 = Chip enters Power- down mode when the both PD_WAIT_CPU and PWR_DOWN_EN bits are set to 1 and CPU run WFI instruction.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * @var CLK_T::AHBCLK
 * Offset: 0x04  AHB Devices Clock Enable Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1]     |PDMA_EN   |PDMA Controller Clock Enable Control
 * |        |          |0 = PDMA peripheral clock Disabled.
 * |        |          |1 = PDMA peripheral clock Enabled.
 * |[2]     |ISP_EN    |Flash ISP Controller Clock Enable Control
 * |        |          |0 = Flash ISP peripheral clock Disabled.
 * |        |          |1 = Flash ISP peripheral clock Enabled.
 * |[3]     |EBI_EN    |EBI Controller Clock Enable Control
 * |        |          |0 = EBI peripheral clock Disabled.
 * |        |          |1 = EBI peripheral clock Enabled.
 * @var CLK_T::APBCLK
 * Offset: 0x08  APB Devices Clock Enable Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |WDT_EN    |Watchdog Timer Clock Enable Control (Write Protect)
 * |        |          |0 = Watchdog Timer clock Disabled.
 * |        |          |1 = Watchdog Timer clock Enabled.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[1]     |RTC_EN    |Real-Time-Clock APB Interface Clock Enable Control
 * |        |          |This bit is used to control the RTC APB clock only. The RTC clock source is from the external 32.768 kHz low speed crystal. 
 * |        |          |0 = RTC clock Disabled.
 * |        |          |1 = RTC clock Enabled.
 * |[2]     |TMR0_EN   |Timer0 Clock Enable Control
 * |        |          |0 = Timer0 clock Disabled.
 * |        |          |1 = Timer0 clock Enabled.
 * |[3]     |TMR1_EN   |Timer1 Clock Enable Control
 * |        |          |0 = Timer1 clock Disabled.
 * |        |          |1 = Timer1 clock Enabled.
 * |[4]     |TMR2_EN   |Timer2 Clock Enable Control
 * |        |          |0 = Timer2 clock Disabled.
 * |        |          |1 = Timer2 clock Enabled.
 * |[5]     |TMR3_EN   |Timer3 Clock Enable Control
 * |        |          |0 = Timer3 clock Disabled.
 * |        |          |1 = Timer3 clock Enabled.
 * |[6]     |FDIV_EN   |Frequency Divider Output Clock Enable Control
 * |        |          |0 = FDIV clock Disabled.
 * |        |          |1 = FDIV clock Enabled.
 * |[8]     |I2C0_EN   |I2C0 Clock Enable Control
 * |        |          |0 = I2C0 clock Disabled.
 * |        |          |1 = I2C0 clock Enabled.
 * |[9]     |I2C1_EN   |I2C1 Clock Enable Control
 * |        |          |0 = I2C1 clock Disabled.
 * |        |          |1 = I2C1 clock Enabled.
 * |[12]    |SPI0_EN   |SPI0 Clock Enable Control
 * |        |          |0 = SPI0 clock Disabled.
 * |        |          |1 = SPI0 clock Enabled.
 * |[13]    |SPI1_EN   |SPI1 Clock Enable Control
 * |        |          |0 = SPI1 clock Disabled.
 * |        |          |1 = SPI1 clock Enabled.
 * |[14]    |SPI2_EN   |SPI2 Clock Enable Control
 * |        |          |0 = SPI2 clock Disabled.
 * |        |          |1 = SPI2 clock Enabled.
 * |[15]    |SPI3_EN   |SPI3 Clock Enable Control
 * |        |          |0 = SPI3 clock Disabled.
 * |        |          |1 = SPI3 clock Enabled.
 * |[16]    |UART0_EN  |UART0 Clock Enable Control
 * |        |          |0 = UART0 clock Disabled.
 * |        |          |1 = UART0 clock Enabled.
 * |[17]    |UART1_EN  |UART1 Clock Enable Control
 * |        |          |0 = UART1 clock Disabled.
 * |        |          |1 = UART1 clock Enabled.
 * |[18]    |UART2_EN  |UART2 Clock Enable Control
 * |        |          |0 = UART2 clock Disabled.
 * |        |          |1 = UART2 clock Enabled.
 * |[20]    |PWM01_EN  |PWM_01 Clock Enable Control
 * |        |          |0 = PWM01 clock Disabled.
 * |        |          |1 = PWM01 clock Enabled.
 * |[21]    |PWM23_EN  |PWM_23 Clock Enable Control
 * |        |          |0 = PWM23 clock Disabled.
 * |        |          |1 = PWM23 clock Enabled.
 * |[22]    |PWM45_EN  |PWM_45 Clock Enable Control
 * |        |          |0 = PWM45 clock Disabled.
 * |        |          |1 = PWM45 clock Enabled.
 * |[23]    |PWM67_EN  |PWM_67 Clock Enable Control
 * |        |          |0 = PWM67 clock Disabled.
 * |        |          |1 = PWM67 clock Enabled.
 * |[27]    |USBD_EN   |USB 2.0 FS Device Controller Clock Enable Control
 * |        |          |0 = USB clock Disabled.
 * |        |          |1 = USB clock Enabled.
 * |[28]    |ADC_EN    |Analog-Digital-Converter (ADC) Clock Enable Control
 * |        |          |0 = ADC clock Disabled.
 * |        |          |1 = ADC clock Enabled.
 * |[29]    |I2S_EN    |I2S Clock Enable Control
 * |        |          |0 = I2S clock Disabled.
 * |        |          |1 = I2S clock Enabled.
 * |[30]    |ACMP_EN   |Analog Comparator Clock Enable Control
 * |        |          |0 = Analog Comparator clock Disabled.
 * |        |          |1 = Analog Comparator clock Enabled.
 * |[31]    |PS2_EN    |PS/2 Clock Enable Control
 * |        |          |0 = PS/2 clock Disabled.
 * |        |          |1 = PS/2 clock Enabled.
 * @var CLK_T::CLKSTATUS
 * Offset: 0x0C  Clock status monitor Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |XTL12M_STB|External 4~24 MHz High Speed Crystal (HXT) Clock Source Stable Flag (Read Only)
 * |        |          |0 = External 4~24 MHz high speed crystal clock (HXT) is not stable or disabled.
 * |        |          |1 = External 4~24 MHz high speed crystal clock (HXT) is stable and enabled.
 * |[1]     |XTL32K_STB|External 32.768 KHz Low Speed Crystal (LXT) Clock Source Stable Flag(Read Only)
 * |        |          |0 = External 32.768 kHz low speed crystal (LXT) clock is not stable or disabled.
 * |        |          |1 = External 32.768 kHz low speed crystal (LXT) clock is stable and enabled.
 * |[2]     |PLL_STB   |Internal PLL Clock Source Stable Flag (Read Only)
 * |        |          |0 = Internal PLL clock is not stable or disabled.
 * |        |          |1 = Internal PLL clock is stable in normal mode.
 * |[3]     |OSC10K_STB|Internal 10 KHz Low Speed Oscillator (LIRC) Clock Source Stable Flag (Read Only)
 * |        |          |0 = Internal 10 kHz low speed oscillator clock (LIRC) is not stable or disabled.
 * |        |          |1 = Internal 10 kHz low speed oscillator clock (LIRC) is stable and enabled.
 * |[4]     |OSC22M_STB|Internal 22.1184 MHz High Speed Oscillator (HIRC) Clock Source Stable Flag (Read Only)
 * |        |          |0 = Internal 22.1184 MHz high speed oscillator (HIRC) clock is not stable or disabled.
 * |        |          |1 = Internal 22.1184 MHz high speed oscillator (HIRC) clock is stable and enabled.
 * |[7]     |CLK_SW_FAIL|Clock Switching Fail Flag
 * |        |          |0 = Clock switching success.
 * |        |          |1 = Clock switching failed.
 * |        |          |This bit is updated when software switches system clock source. 
 * |        |          |If switch target clock is stable, this bit will be set to 0. 
 * |        |          |If switch target clock is not stable, this bit will be set to 1.
 * |        |          |Write 1 to clear the bit to 0. 
 * @var CLK_T::CLKSEL0
 * Offset: 0x10  Clock Source Select Control Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[2:0]   |HCLK_S    |HCLK Clock Source Selection (Write Protect)
 * |        |          |1. Before clock switching, the related clock sources (both pre-select and new-select) must be turn on.
 * |        |          |2. The 3-bit default value is reloaded from the value of CFOSC (Config0[26:24]) in user configuration register of Flash controller by any reset. Therefore the default value is either 000b or 111b.
 * |        |          |000 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |001 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |010 = Clock source from PLL clock.
 * |        |          |011 = Clock source from internal 10 kHz low speed oscillator clock.
 * |        |          |111 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |Note: These bits are write protected bit. Refer to the REGWRPROT register.
 * |[5:3]   |STCLK_S   |Cortex-M0 SysTick Clock Source Selection (Write Protect)
 * |        |          |If SYST_CSR[2] = 1, SysTick clock source is from HCLK.
 * |        |          |If SYST_CSR[2] = 0, SysTick clock source is defined by STCLK_S(CLKSEL0[5:3]).
 * |        |          |000 = Clock source from external 4~24 MHz high speed crystal clock.
 * |        |          |001 = Clock source from external 32.768 kHz low speed crystal clock.
 * |        |          |010 = Clock source from external 4~24 MHz high speed crystal clock/2.
 * |        |          |011 = Clock source from HCLK/2.
 * |        |          |111 = Clock source from internal 22.1184 MHz high speed oscillator clock/2.
 * |        |          |Note1: These bits are write protected bit. Refer to the REGWRPROT register.
 * |        |          |Note2: if SysTick clock source is not from HCLK (i.e. SYST_CSR[2] = 0), SysTick clock source must less than or equal to HCLK/2.
 * @var CLK_T::CLKSEL1
 * Offset: 0x14  Clock Source Select Control Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |WDT_S     |Watchdog Timer Clock Source Select (Write Protect)
 * |        |          |00 = Reserved.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK/2048 clock.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |        |          |Note: These bits are write protected bit. Refer to the REGWRPROT register.
 * |[3:2]   |ADC_S     |ADC Clock Source Select
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from PLL clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |[4]     |SPI0_S    |SPI0 Clock Source Selection
 * |        |          |0 = Clock source from PLL clock.
 * |        |          |1 = Clock source from HCLK.
 * |[5]     |SPI1_S    |SPI1 Clock Source Selection
 * |        |          |0 = Clock source from PLL clock.
 * |        |          |1 = Clock source from HCLK.
 * |[6]     |SPI2_S    |SPI2 Clock Source Selection
 * |        |          |0 = Clock source from PLL clock.
 * |        |          |1 = Clock source from HCLK.
 * |[7]     |SPI3_S    |SPI3 Clock Source Selection
 * |        |          |0 = Clock source from PLL clock.
 * |        |          |1 = Clock source from HCLK.
 * |[10:8]  |TMR0_S    |TIMER0 Clock Source Selection
 * |        |          |000 = Clock source from external 4~24 MHz high speed crystal clock.
 * |        |          |001 = Clock source from external 32.768 kHz low speed crystal clock.
 * |        |          |010 = Clock source from HCLK.
 * |        |          |011 = Clock source from external trigger.
 * |        |          |101 = Clock source from internal 10 kHz low speed oscillator clock.
 * |        |          |111 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |Others = Reserved.
 * |[14:12] |TMR1_S    |TIMER1 Clock Source Selection
 * |        |          |000 = Clock source from external 4~24 MHz high speed crystal clock.
 * |        |          |001 = Clock source from external 32.768 kHz low speed crystal clock.
 * |        |          |010 = Clock source from HCLK.
 * |        |          |011 = Clock source from external trigger.
 * |        |          |101 = Clock source from internal 10 kHz low speed oscillator clock.
 * |        |          |111 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |Others = Reserved.
 * |[18:16] |TMR2_S    |TIMER2 Clock Source Selection
 * |        |          |000 = Clock source from external 4~24 MHz high speed crystal clock.
 * |        |          |001 = Clock source from external 32.768 kHz low speed crystal clock.
 * |        |          |010 = Clock source from HCLK.
 * |        |          |011 = Clock source from external trigger.
 * |        |          |101 = Clock source from internal 10 kHz low speed oscillator clock.
 * |        |          |111 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |Others = Reserved.
 * |[22:20] |TMR3_S    |TIMER3 Clock Source Selection
 * |        |          |000 = Clock source from external 4~24 MHz high speed crystal clock.
 * |        |          |001 = Clock source from external 32.768 kHz low speed crystal clock.
 * |        |          |010 = Clock source from HCLK.
 * |        |          |011 = Clock source from external trigger.
 * |        |          |101 = Clock source from internal 10 kHz low speed oscillator clock.
 * |        |          |111 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |Others = Reserved.
 * |[25:24] |UART_S    |UART Clock Source Selection
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from PLL clock.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |[29:28] |PWM01_S   |PWM0 And PWM1 Clock Source Selection
 * |        |          |PWM0 and PWM1 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM0 and PWM1 is defined by PWM01_S (CLKSEL1[29:28]) and PWM01_S_E (CLKSEL2[8]).
 * |        |          |If PWM01_S_E = 0, the clock source of PWM0 and PWM1 defined by PWM01_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM01_S_E = 1, the clock source of PWM0 and PWM1 defined by PWM01_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[31:30] |PWM23_S   |PWM2 And PWM3 Clock Source Selection
 * |        |          |PWM2 and PWM3 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM2 and PWM3 is defined by PWM23_S (CLKSEL1[31:30]) and PWM23_S_E (CLKSEL2[9]).
 * |        |          |If PWM23_S_E = 0, the clock source of PWM2 and PWM3 defined by PWM23_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM23_S_E = 1, the clock source of PWM2 and PWM3 defined by PWM23_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * @var CLK_T::CLKDIV
 * Offset: 0x18  Clock Divider Number Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |HCLK_N    |HCLK Clock Divide Number From HCLK Clock Source
 * |        |          |HCLK clock frequency = (HCLK clock source frequency) / (HCLK_N + 1).
 * |[7:4]   |USB_N     |USB Clock Divide Number From PLL Clock
 * |        |          |USB clock frequency = (PLL frequency) / (USB_N + 1).
 * |[11:8]  |UART_N    |UART Clock Divide Number From UART Clock Source
 * |        |          |UART clock frequency = (UART clock source frequency) / (UART_N + 1).
 * |[23:16] |ADC_N     |ADC Clock Divide Number From ADC Clock Source
 * |        |          |ADC clock frequency = (ADC clock source frequency) / (ADC_N + 1).
 * @var CLK_T::CLKSEL2
 * Offset: 0x1C  Clock Source Select Control Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |I2S_S     |I2S Clock Source Selection
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from PLL clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |[3:2]   |FRQDIV_S  |Clock Divider Clock Source Selection
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |[5:4]   |PWM45_S   |PWM4 And PWM5 Clock Source Selection
 * |        |          |PWM4 and PWM5 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM4 and PWM5 is defined by PWM45_S (CLKSEL2[5:4]) and PWM45_S_E (CLKSEL2[10]).
 * |        |          |If PWM45_S_E = 0, the clock source of PWM4 and PWM5 defined by PWM45_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM45_S_E = 1, the clock source of PWM4 and PWM5 defined by PWM45_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[7:6]   |PWM67_S   |PWM6 And PWM7 Clock Source Selection
 * |        |          |PWM6 and PWM7 used the sameclock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM6 and PWM7 is defined by PWM67_S (CLKSEL2[7:6]) and PWM67_S_E (CLKSEL2[11]).
 * |        |          |If PWM67_S_E = 0, the clock source of PWM6 and PWM7 defined by PWM67_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM67_S_E = 1, the clock source of PWM6 and PWM7 defined by PWM67_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[8]     |PWM01_S_E |PWM0 And PWM1 Clock Source Selection Extend
 * |        |          |PWM0 and PWM1 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM0 and PWM1 is defined by PWM01_S (CLKSEL1[29:28]) and PWM01_S_E (CLKSEL2[8]).
 * |        |          |If PWM01_S_E = 0, the clock source of PWM0 and PWM1 defined by PWM01_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM01_S_E = 1, the clock source of PWM0 and PWM1 defined by PWM01_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[9]     |PWM23_S_E |PWM2 And PWM3 Clock Source Selection Extend
 * |        |          |PWM2 and PWM3 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM2 and PWM3 is defined by PWM23_S (CLKSEL1[31:30]) and PWM23_S_E (CLKSEL2[9]).
 * |        |          |If PWM23_S_E = 0, the clock source of PWM2 and PWM3 defined by PWM23_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM23_S_E = 1, the clock source of PWM2 and PWM3 defined by PWM23_S listbelow:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[10]    |PWM45_S_E |PWM4 And PWM5 Clock Source Selection Extend
 * |        |          |PWM4 and PWM5 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM4 and PWM5 is defined by PWM45_S (CLKSEL2[5:4]) and PWM45_S_E (CLKSEL2[10]).
 * |        |          |If PWM45_S_E = 0, the clock source of PWM4 and PWM5 defined by PWM45_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM45_S_E = 1, the clock source of PWM4 and PWM5 defined by PWM45_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[11]    |PWM67_S_E |PWM6 And PWM7 Clock Source Selection Extend
 * |        |          |PWM6 and PWM7 used the same clock source; both of them used the same prescaler.
 * |        |          |The clock source of PWM6 and PWM7 is defined by PWM67_S (CLKSEL2[7:6]) and PWM67_S_E (CLKSEL2[11]).
 * |        |          |If PWM67_S_E = 0, the peripheral clock source of PWM6 and PWM7 defined by PWM67_S list below:
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from external 32.768 kHz low speed crystal oscillator clock.
 * |        |          |10 = Clock source from HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |        |          |If PWM67_S_E = 1, the clock source of PWM6 and PWM7 defined by PWM67_S list below:
 * |        |          |00 = Reserved.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * |[17:16] |WWDT_S    |Window Watchdog Timer Clock Source Selection
 * |        |          |10 = Clock source from HCLK/2048 clock.
 * |        |          |11 = Clock source from internal 10 kHz low speed oscillator clock.
 * @var CLK_T::PLLCON
 * Offset: 0x20  PLL Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8:0]   |FB_DV     |PLL Feedback Divider Control Bits
 * |        |          |Refer to the PLL formulas.
 * |[13:9]  |IN_DV     |PLL Input Divider Control Bits
 * |        |          |Refer to the PLL formulas.
 * |[15:14] |OUT_DV    |PLL Output Divider Control Bits
 * |        |          |Refer to the PLL formulas.
 * |[16]    |PD        |Power-Down Mode
 * |        |          |If the PWR_DOWN_EN bit is set to 1 in PWRCON register, the PLL will enter Power-down mode too.     
 * |        |          |0 = PLL is in Normal mode.
 * |        |          |1 = PLL is in Power-down mode (default).
 * |[17]    |BP        |PLL Bypass Control
 * |        |          |0 = PLL is in Normal mode (default).
 * |        |          |1 = PLL clock output is same as PLL source clock input.
 * |[18]    |OE        |PLL OE (FOUT Enable) Control
 * |        |          |0 = PLL FOUT Enabled.
 * |        |          |1 = PLL FOUT is fixed low.
 * |[19]    |PLL_SRC   |PLL Source Clock Selection
 * |        |          |0 = PLL source clock from external 4~24 MHz high speed crystal.
 * |        |          |1 = PLL source clock from internal 22.1184 MHz high speed oscillator.
 * @var CLK_T::FRQDIV
 * Offset: 0x24  Frequency Divider Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |FSEL      |Divider Output Frequency Selection Bits
 * |        |          |The formula of output frequency is Fout = Fin/2(N+1).
 * |        |          |Fin is the input clock frequency.
 * |        |          |Fout is the frequency of divider output clock.
 * |        |          |N is the 4-bit value of FSEL[3:0].
 * |[4]     |DIVIDER_EN|Frequency Divider Enable Bit
 * |        |          |0 = Frequency Divider function Disabled.
 * |        |          |1 = Frequency Divider function Enabled.
 * @var CLK_T::APBCLK1
 * Offset: 0x30  APB Devices Clock Enable Control Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |SC0_EN    |SC0 Clock Enable Control
 * |        |          |0 = SC0 Clock Disabled.
 * |        |          |1 = SC0 Clock Enabled.
 * |[1]     |SC1_EN    |SC1 Clock Enable Control
 * |        |          |0 = SC1 clock Disabled.
 * |        |          |1 = SC1 clock Enabled.
 * |[2]     |SC2_EN    |SC2 Clock Enable Control
 * |        |          |0 = SC2 clock Disabled.
 * |        |          |1 = SC2 clock Enabled.
 * @var CLK_T::CLKSEL3
 * Offset: 0x34  Clock Source Select Control Register 3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |SC0_S     |SC0 Clock Source Selection
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from PLL clock.
 * |        |          |10 = HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |[3:2]   |SC1_S     |SC1 Clock Source Selection
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from PLL clock.
 * |        |          |10 = HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * |[5:4]   |SC2_S     |SC2 Clock Source Selection
 * |        |          |00 = Clock source from external 4~24 MHz high speed crystal oscillator clock.
 * |        |          |01 = Clock source from PLL clock.
 * |        |          |10 = HCLK.
 * |        |          |11 = Clock source from internal 22.1184 MHz high speed oscillator clock.
 * @var CLK_T::CLKDIV1
 * Offset: 0x38  Clock Divider Number Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |SC0_N     |SC0 Clock Divide Number From SC0 Clock Source
 * |        |          |The SC0 clock frequency = (SC0 clock source frequency) / (SC0_N + 1).
 * |[15:8]  |SC1_N     |SC1 Clock Divide Number From SC1 Clock Source
 * |        |          |The SC1 clock frequency = (SC1 clock source frequency) / (SC1_N + 1).
 * |[23:16] |SC2_N     |SC2 Clock Divide Number From SC2 Clock Source
 * |        |          |The SC2 clock frequency = (SC2 clock source frequency) / (SC2_N + 1).
 */

    __IO uint32_t PWRCON;        /* Offset: 0x00  System Power-down Control Register                                 */
    __IO uint32_t AHBCLK;        /* Offset: 0x04  AHB Devices Clock Enable Control Register                          */
    __IO uint32_t APBCLK;        /* Offset: 0x08  APB Devices Clock Enable Control Register                          */
    __IO uint32_t CLKSTATUS;     /* Offset: 0x0C  Clock status monitor Register                                      */
    __IO uint32_t CLKSEL0;       /* Offset: 0x10  Clock Source Select Control Register 0                             */
    __IO uint32_t CLKSEL1;       /* Offset: 0x14  Clock Source Select Control Register 1                             */
    __IO uint32_t CLKDIV;        /* Offset: 0x18  Clock Divider Number Register                                      */
    __IO uint32_t CLKSEL2;       /* Offset: 0x1C  Clock Source Select Control Register 2                             */
    __IO uint32_t PLLCON;        /* Offset: 0x20  PLL Control Register                                               */
    __IO uint32_t FRQDIV;        /* Offset: 0x24  Frequency Divider Control Register                                 */
    __IO uint32_t RESERVE[2];   
    __IO uint32_t APBCLK1;       /* Offset: 0x30  APB Devices Clock Enable Control Register 1                        */
    __IO uint32_t CLKSEL3;       /* Offset: 0x34  Clock Source Select Control Register 3                             */
    __IO uint32_t CLKDIV1;       /* Offset: 0x38  Clock Divider Number Register 1                                    */

} CLK_T;



/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
@{ */

/* CLK PWRCON Bit Field Definitions */
#define CLK_PWRCON_PD_WAIT_CPU_Pos           8                                    /*!< CLK_T::PWRCON: PD_WAIT_CPU Position */
#define CLK_PWRCON_PD_WAIT_CPU_Msk           (1ul << CLK_PWRCON_PD_WAIT_CPU_Pos)  /*!< CLK_T::PWRCON: PD_WAIT_CPU Mask */

#define CLK_PWRCON_PWR_DOWN_EN_Pos           7                                    /*!< CLK_T::PWRCON: PWR_DOWN_EN Position */
#define CLK_PWRCON_PWR_DOWN_EN_Msk           (1ul << CLK_PWRCON_PWR_DOWN_EN_Pos)  /*!< CLK_T::PWRCON: PWR_DOWN_EN Mask */

#define CLK_PWRCON_PD_WU_STS_Pos             6                                    /*!< CLK_T::PWRCON: PD_WU_STS Position */
#define CLK_PWRCON_PD_WU_STS_Msk             (1ul << CLK_PWRCON_PD_WU_STS_Pos)    /*!< CLK_T::PWRCON: PD_WU_STS Mask */

#define CLK_PWRCON_PD_WU_INT_EN_Pos          5                                    /*!< CLK_T::PWRCON: PD_WU_INT_EN Position */
#define CLK_PWRCON_PD_WU_INT_EN_Msk          (1ul << CLK_PWRCON_PD_WU_INT_EN_Pos) /*!< CLK_T::PWRCON: PD_WU_INT_EN Mask */

#define CLK_PWRCON_PD_WU_DLY_Pos             4                                    /*!< CLK_T::PWRCON: PD_WU_DLY Position */
#define CLK_PWRCON_PD_WU_DLY_Msk             (1ul << CLK_PWRCON_PD_WU_DLY_Pos)    /*!< CLK_T::PWRCON: PD_WU_DLY Mask */

#define CLK_PWRCON_OSC10K_EN_Pos             3                                    /*!< CLK_T::PWRCON: OSC10K_EN Position */
#define CLK_PWRCON_OSC10K_EN_Msk             (1ul << CLK_PWRCON_OSC10K_EN_Pos)    /*!< CLK_T::PWRCON: OSC10K_EN Mask */
#define CLK_PWRCON_IRC10K_EN_Pos             3                                    /*!< CLK_T::PWRCON: IRC10K_EN Position */
#define CLK_PWRCON_IRC10K_EN_Msk             (1ul << CLK_PWRCON_IRC10K_EN_Pos)    /*!< CLK_T::PWRCON: IRC10K_EN Mask */

#define CLK_PWRCON_OSC22M_EN_Pos             2                                    /*!< CLK_T::PWRCON: OSC22M_EN Position */
#define CLK_PWRCON_OSC22M_EN_Msk             (1ul << CLK_PWRCON_OSC22M_EN_Pos)    /*!< CLK_T::PWRCON: OSC22M_EN Mask */
#define CLK_PWRCON_IRC22M_EN_Pos             2                                    /*!< CLK_T::PWRCON: IRC22M_EN Position */
#define CLK_PWRCON_IRC22M_EN_Msk             (1ul << CLK_PWRCON_IRC22M_EN_Pos)    /*!< CLK_T::PWRCON: IRC22M_EN Mask */

#define CLK_PWRCON_XTL32K_EN_Pos             1                                    /*!< CLK_T::PWRCON: XTL32K_EN Position */
#define CLK_PWRCON_XTL32K_EN_Msk             (1ul << CLK_PWRCON_XTL32K_EN_Pos)    /*!< CLK_T::PWRCON: XTL32K_EN Mask */

#define CLK_PWRCON_XTL12M_EN_Pos             0                                    /*!< CLK_T::PWRCON: XTL12M_EN Position */
#define CLK_PWRCON_XTL12M_EN_Msk             (1ul << CLK_PWRCON_XTL12M_EN_Pos)    /*!< CLK_T::PWRCON: XTL12M_EN Mask */

/* CLK AHBCLK Bit Field Definitions */
#define CLK_AHBCLK_EBI_EN_Pos                3                                    /*!< CLK_T::AHBCLK: EBI_EN Position */
#define CLK_AHBCLK_EBI_EN_Msk                (1ul << CLK_AHBCLK_EBI_EN_Pos)       /*!< CLK_T::AHBCLK: EBI_EN Mask */

#define CLK_AHBCLK_ISP_EN_Pos                2                                    /*!< CLK_T::AHBCLK: ISP_EN Position */
#define CLK_AHBCLK_ISP_EN_Msk                (1ul << CLK_AHBCLK_ISP_EN_Pos)       /*!< CLK_T::AHBCLK: ISP_EN Mask */

#define CLK_AHBCLK_PDMA_EN_Pos               1                                    /*!< CLK_T::AHBCLK: PDMA_EN Position */
#define CLK_AHBCLK_PDMA_EN_Msk               (1ul << CLK_AHBCLK_PDMA_EN_Pos)      /*!< CLK_T::AHBCLK: PDMA_EN Mask */


/* CLK APBCLK Bit Field Definitions */
#define CLK_APBCLK_PS2_EN_Pos                31                                   /*!< CLK_T::APBCLK: PS2_EN Position */
#define CLK_APBCLK_PS2_EN_Msk                (1ul << CLK_APBCLK_PS2_EN_Pos)       /*!< CLK_T::APBCLK: PS2_EN Mask */

#define CLK_APBCLK_ACMP_EN_Pos               30                                   /*!< CLK_T::APBCLK: ACMP_EN Position */
#define CLK_APBCLK_ACMP_EN_Msk               (1ul << CLK_APBCLK_ACMP_EN_Pos)      /*!< CLK_T::APBCLK: ACMP_EN Mask */

#define CLK_APBCLK_I2S_EN_Pos                29                                   /*!< CLK_T::APBCLK: I2S_EN Position */
#define CLK_APBCLK_I2S_EN_Msk                (1ul << CLK_APBCLK_I2S_EN_Pos)       /*!< CLK_T::APBCLK: I2S_EN Mask */

#define CLK_APBCLK_ADC_EN_Pos                28                                   /*!< CLK_T::APBCLK: ADC_EN Position */
#define CLK_APBCLK_ADC_EN_Msk                (1ul << CLK_APBCLK_ADC_EN_Pos)       /*!< CLK_T::APBCLK: ADC_EN Mask */

#define CLK_APBCLK_USBD_EN_Pos               27                                   /*!< CLK_T::APBCLK: USBD_EN Position */
#define CLK_APBCLK_USBD_EN_Msk               (1ul << CLK_APBCLK_USBD_EN_Pos)      /*!< CLK_T::APBCLK: USBD_EN Mask */

#define CLK_APBCLK_PWM67_EN_Pos              23                                   /*!< CLK_T::APBCLK: PWM67_EN Position */
#define CLK_APBCLK_PWM67_EN_Msk              (1ul << CLK_APBCLK_PWM67_EN_Pos)     /*!< CLK_T::APBCLK: PWM67_EN Mask */

#define CLK_APBCLK_PWM45_EN_Pos              22                                   /*!< CLK_T::APBCLK: PWM45_EN Position */
#define CLK_APBCLK_PWM45_EN_Msk              (1ul << CLK_APBCLK_PWM45_EN_Pos)     /*!< CLK_T::APBCLK: PWM45_EN Mask */

#define CLK_APBCLK_PWM23_EN_Pos              21                                   /*!< CLK_T::APBCLK: PWM23_EN Position */
#define CLK_APBCLK_PWM23_EN_Msk              (1ul << CLK_APBCLK_PWM23_EN_Pos)     /*!< CLK_T::APBCLK: PWM23_EN Mask */

#define CLK_APBCLK_PWM01_EN_Pos              20                                   /*!< CLK_T::APBCLK: PWM01_EN Position */
#define CLK_APBCLK_PWM01_EN_Msk              (1ul << CLK_APBCLK_PWM01_EN_Pos)     /*!< CLK_T::APBCLK: PWM01_EN Mask */

#define CLK_APBCLK_UART2_EN_Pos              18                                   /*!< CLK_T::APBCLK: UART2_EN Position */
#define CLK_APBCLK_UART2_EN_Msk              (1ul << CLK_APBCLK_UART2_EN_Pos)     /*!< CLK_T::APBCLK: UART2_EN Mask */

#define CLK_APBCLK_UART1_EN_Pos              17                                   /*!< CLK_T::APBCLK: UART1_EN Position */
#define CLK_APBCLK_UART1_EN_Msk              (1ul << CLK_APBCLK_UART1_EN_Pos)     /*!< CLK_T::APBCLK: UART1_EN Mask */

#define CLK_APBCLK_UART0_EN_Pos              16                                   /*!< CLK_T::APBCLK: UART0_EN Position */
#define CLK_APBCLK_UART0_EN_Msk              (1ul << CLK_APBCLK_UART0_EN_Pos)     /*!< CLK_T::APBCLK: UART0_EN Mask */

#define CLK_APBCLK_SPI3_EN_Pos               15                                   /*!< CLK_T::APBCLK: SPI3_EN Position */
#define CLK_APBCLK_SPI3_EN_Msk               (1ul << CLK_APBCLK_SPI3_EN_Pos)      /*!< CLK_T::APBCLK: SPI3_EN Mask */

#define CLK_APBCLK_SPI2_EN_Pos               14                                   /*!< CLK_T::APBCLK: SPI2_EN Position */
#define CLK_APBCLK_SPI2_EN_Msk               (1ul << CLK_APBCLK_SPI2_EN_Pos)      /*!< CLK_T::APBCLK: SPI2_EN Mask */

#define CLK_APBCLK_SPI1_EN_Pos               13                                   /*!< CLK_T::APBCLK: SPI1_EN Position */
#define CLK_APBCLK_SPI1_EN_Msk               (1ul << CLK_APBCLK_SPI1_EN_Pos)      /*!< CLK_T::APBCLK: SPI1_EN Mask */

#define CLK_APBCLK_SPI0_EN_Pos               12                                   /*!< CLK_T::APBCLK: SPI0_EN Position */
#define CLK_APBCLK_SPI0_EN_Msk               (1ul << CLK_APBCLK_SPI0_EN_Pos)      /*!< CLK_T::APBCLK: SPI0_EN Mask */

#define CLK_APBCLK_I2C1_EN_Pos               9                                    /*!< CLK_T::APBCLK: I2C1_EN Position */
#define CLK_APBCLK_I2C1_EN_Msk               (1ul << CLK_APBCLK_I2C1_EN_Pos)      /*!< CLK_T::APBCLK: I2C1_EN Mask */

#define CLK_APBCLK_I2C0_EN_Pos               8                                    /*!< CLK_T::APBCLK: I2C0_EN_ Position */
#define CLK_APBCLK_I2C0_EN_Msk               (1ul << CLK_APBCLK_I2C0_EN_Pos)      /*!< CLK_T::APBCLK: I2C0_EN_ Mask */

#define CLK_APBCLK_FDIV_EN_Pos               6                                    /*!< CLK_T::APBCLK: FDIV_EN Position */
#define CLK_APBCLK_FDIV_EN_Msk               (1ul << CLK_APBCLK_FDIV_EN_Pos)      /*!< CLK_T::APBCLK: FDIV_EN Mask */

#define CLK_APBCLK_TMR3_EN_Pos               5                                    /*!< CLK_T::APBCLK: TMR3_EN Position */
#define CLK_APBCLK_TMR3_EN_Msk               (1ul << CLK_APBCLK_TMR3_EN_Pos)      /*!< CLK_T::APBCLK: TMR3_EN Mask */

#define CLK_APBCLK_TMR2_EN_Pos               4                                    /*!< CLK_T::APBCLK: TMR2_EN Position */
#define CLK_APBCLK_TMR2_EN_Msk               (1ul << CLK_APBCLK_TMR2_EN_Pos)      /*!< CLK_T::APBCLK: TMR2_EN Mask */

#define CLK_APBCLK_TMR1_EN_Pos               3                                    /*!< CLK_T::APBCLK: TMR1_EN Position */
#define CLK_APBCLK_TMR1_EN_Msk               (1ul << CLK_APBCLK_TMR1_EN_Pos)      /*!< CLK_T::APBCLK: TMR1_EN Mask */

#define CLK_APBCLK_TMR0_EN_Pos               2                                    /*!< CLK_T::APBCLK: TMR0_EN Position */
#define CLK_APBCLK_TMR0_EN_Msk               (1ul << CLK_APBCLK_TMR0_EN_Pos)      /*!< CLK_T::APBCLK: TMR0_EN Mask */

#define CLK_APBCLK_RTC_EN_Pos                1                                    /*!< CLK_T::APBCLK: RTC_EN Position */
#define CLK_APBCLK_RTC_EN_Msk                (1ul << CLK_APBCLK_RTC_EN_Pos)       /*!< CLK_T::APBCLK: RTC_EN Mask */

#define CLK_APBCLK_WDT_EN_Pos                0                                    /*!< CLK_T::APBCLK: WDT_EN Position */
#define CLK_APBCLK_WDT_EN_Msk                (1ul << CLK_APBCLK_WDT_EN_Pos)       /*!< CLK_T::APBCLK: WDT_EN Mask */

/* CLK APBCLK1 Bit Field Definitions */
#define CLK_APBCLK1_SC2_EN_Pos                2                                   /*!< CLK_T::APBCLK1: SC2_EN Position */
#define CLK_APBCLK1_SC2_EN_Msk                (1ul << CLK_APBCLK1_SC2_EN_Pos)     /*!< CLK_T::APBCLK1: SC2_EN Mask */

#define CLK_APBCLK1_SC1_EN_Pos                1                                   /*!< CLK_T::APBCLK1: SC1_EN Position */
#define CLK_APBCLK1_SC1_EN_Msk                (1ul << CLK_APBCLK1_SC1_EN_Pos)     /*!< CLK_T::APBCLK1: SC1_EN Mask */

#define CLK_APBCLK1_SC0_EN_Pos                0                                   /*!< CLK_T::APBCLK1: SC0_EN Position */
#define CLK_APBCLK1_SC0_EN_Msk                (1ul << CLK_APBCLK1_SC0_EN_Pos)     /*!< CLK_T::APBCLK1: SC0_EN Mask */

/* CLK CLKSTATUS Bit Field Definitions */
#define CLK_CLKSTATUS_CLK_SW_FAIL_Pos        7                                        /*!< CLK_T::CLKSTATUS: CLK_SW_FAIL Position */
#define CLK_CLKSTATUS_CLK_SW_FAIL_Msk        (1ul << CLK_CLKSTATUS_CLK_SW_FAIL_Pos)   /*!< CLK_T::CLKSTATUS: CLK_SW_FAIL Mask */

#define CLK_CLKSTATUS_OSC22M_STB_Pos         4                                        /*!< CLK_T::CLKSTATUS: OSC22M_STB Position */
#define CLK_CLKSTATUS_OSC22M_STB_Msk         (1ul << CLK_CLKSTATUS_OSC22M_STB_Pos)    /*!< CLK_T::CLKSTATUS: OSC22M_STB Mask */
#define CLK_CLKSTATUS_IRC22M_STB_Pos         4                                        /*!< CLK_T::CLKSTATUS: IRC22M_STB Position */
#define CLK_CLKSTATUS_IRC22M_STB_Msk         (1ul << CLK_CLKSTATUS_IRC22M_STB_Pos)    /*!< CLK_T::CLKSTATUS: IRC22M_STB Mask */

#define CLK_CLKSTATUS_OSC10K_STB_Pos         3                                        /*!< CLK_T::CLKSTATUS: OSC10K_STB Position */
#define CLK_CLKSTATUS_OSC10K_STB_Msk         (1ul << CLK_CLKSTATUS_OSC10K_STB_Pos)    /*!< CLK_T::CLKSTATUS: OSC10K_STB Mask */
#define CLK_CLKSTATUS_IRC10K_STB_Pos         3                                        /*!< CLK_T::CLKSTATUS: IRC10K_STB Position */
#define CLK_CLKSTATUS_IRC10K_STB_Msk         (1ul << CLK_CLKSTATUS_IRC10K_STB_Pos)    /*!< CLK_T::CLKSTATUS: IRC10K_STB Mask */

#define CLK_CLKSTATUS_PLL_STB_Pos            2                                        /*!< CLK_T::CLKSTATUS: PLL_STB Position */
#define CLK_CLKSTATUS_PLL_STB_Msk            (1ul << CLK_CLKSTATUS_PLL_STB_Pos)       /*!< CLK_T::CLKSTATUS: PLL_STB Mask */

#define CLK_CLKSTATUS_XTL32K_STB_Pos         1                                        /*!< CLK_T::CLKSTATUS: XTL32K_STB Position */
#define CLK_CLKSTATUS_XTL32K_STB_Msk         (1ul << CLK_CLKSTATUS_XTL32K_STB_Pos)    /*!< CLK_T::CLKSTATUS: XTL32K_STB Mask */

#define CLK_CLKSTATUS_XTL12M_STB_Pos         0                                        /*!< CLK_T::CLKSTATUS: XTL12M_STB Position */
#define CLK_CLKSTATUS_XTL12M_STB_Msk         (1ul << CLK_CLKSTATUS_XTL12M_STB_Pos)    /*!< CLK_T::CLKSTATUS: XTL12M_STB Mask */

/* CLK CLKSEL0 Bit Field Definitions */
#define CLK_CLKSEL0_STCLK_S_Pos              3                                        /*!< CLK_T::CLKSEL0: STCLK_S Position */
#define CLK_CLKSEL0_STCLK_S_Msk              (7ul << CLK_CLKSEL0_STCLK_S_Pos)         /*!< CLK_T::CLKSEL0: STCLK_S Mask */

#define CLK_CLKSEL0_HCLK_S_Pos               0                                        /*!< CLK_T::CLKSEL0: HCLK_S Position */
#define CLK_CLKSEL0_HCLK_S_Msk               (7ul << CLK_CLKSEL0_HCLK_S_Pos)          /*!< CLK_T::CLKSEL0: HCLK_S Mask */

/* CLK CLKSEL1 Bit Field Definitions */
#define CLK_CLKSEL1_PWM23_S_Pos              30                                       /*!< CLK_T::CLKSEL1: PWM23_S Position */
#define CLK_CLKSEL1_PWM23_S_Msk              (3ul << CLK_CLKSEL1_PWM23_S_Pos)         /*!< CLK_T::CLKSEL1: PWM23_S Mask */

#define CLK_CLKSEL1_PWM01_S_Pos              28                                       /*!< CLK_T::CLKSEL1: PWM01_S Position */
#define CLK_CLKSEL1_PWM01_S_Msk              (3ul << CLK_CLKSEL1_PWM01_S_Pos)         /*!< CLK_T::CLKSEL1: PWM01_S Mask */

#define CLK_CLKSEL1_UART_S_Pos               24                                       /*!< CLK_T::CLKSEL1: UART_S Position */
#define CLK_CLKSEL1_UART_S_Msk               (3ul << CLK_CLKSEL1_UART_S_Pos)          /*!< CLK_T::CLKSEL1: UART_S Mask */

#define CLK_CLKSEL1_TMR3_S_Pos               20                                       /*!< CLK_T::CLKSEL1: TMR3_S Position */
#define CLK_CLKSEL1_TMR3_S_Msk               (7ul << CLK_CLKSEL1_TMR3_S_Pos)          /*!< CLK_T::CLKSEL1: TMR3_S Mask */

#define CLK_CLKSEL1_TMR2_S_Pos               16                                       /*!< CLK_T::CLKSEL1: TMR2_S Position */
#define CLK_CLKSEL1_TMR2_S_Msk               (7ul << CLK_CLKSEL1_TMR2_S_Pos)          /*!< CLK_T::CLKSEL1: TMR2_S Mask */

#define CLK_CLKSEL1_TMR1_S_Pos               12                                       /*!< CLK_T::CLKSEL1: TMR1_S Position */
#define CLK_CLKSEL1_TMR1_S_Msk               (7ul << CLK_CLKSEL1_TMR1_S_Pos)          /*!< CLK_T::CLKSEL1: TMR1_S Mask */

#define CLK_CLKSEL1_TMR0_S_Pos               8                                        /*!< CLK_T::CLKSEL1: TMR0_S Position */
#define CLK_CLKSEL1_TMR0_S_Msk               (7ul << CLK_CLKSEL1_TMR0_S_Pos)          /*!< CLK_T::CLKSEL1: TMR0_S Mask */

#define CLK_CLKSEL1_SPI3_S_Pos               7                                        /*!< CLK_T::CLKSEL1: SPI3_S Position */
#define CLK_CLKSEL1_SPI3_S_Msk               (1ul << CLK_CLKSEL1_SPI3_S_Pos)          /*!< CLK_T::CLKSEL1: SPI3_S Mask */

#define CLK_CLKSEL1_SPI2_S_Pos               6                                        /*!< CLK_T::CLKSEL1: SPI2_S Position */
#define CLK_CLKSEL1_SPI2_S_Msk               (1ul << CLK_CLKSEL1_SPI2_S_Pos)          /*!< CLK_T::CLKSEL1: SPI2_S Mask */

#define CLK_CLKSEL1_SPI1_S_Pos               5                                        /*!< CLK_T::CLKSEL1: SPI1_S Position */
#define CLK_CLKSEL1_SPI1_S_Msk               (1ul << CLK_CLKSEL1_SPI1_S_Pos)          /*!< CLK_T::CLKSEL1: SPI1_S Mask */

#define CLK_CLKSEL1_SPI0_S_Pos               4                                        /*!< CLK_T::CLKSEL1: SPI0_S Position */
#define CLK_CLKSEL1_SPI0_S_Msk               (1ul << CLK_CLKSEL1_SPI0_S_Pos)          /*!< CLK_T::CLKSEL1: SPI0_S Mask */

#define CLK_CLKSEL1_ADC_S_Pos                2                                        /*!< CLK_T::CLKSEL1: ADC_S Position */
#define CLK_CLKSEL1_ADC_S_Msk                (3ul << CLK_CLKSEL1_ADC_S_Pos)           /*!< CLK_T::CLKSEL1: ADC_S Mask */

#define CLK_CLKSEL1_WDT_S_Pos                0                                        /*!< CLK_T::CLKSEL1: WDT_S Position */
#define CLK_CLKSEL1_WDT_S_Msk                (3ul << CLK_CLKSEL1_WDT_S_Pos)           /*!< CLK_T::CLKSEL1: WDT_S Mask */

/* CLK CLKSEL2 Bit Field Definitions */
#define CLK_CLKSEL2_WWDT_S_Pos               16                                       /*!< CLK_T::CLKSEL2: WWDT_S Position */
#define CLK_CLKSEL2_WWDT_S_Msk               (3ul << CLK_CLKSEL2_WWDT_S_Pos)          /*!< CLK_T::CLKSEL2: WWDT_S Mask */

#define CLK_CLKSEL2_PWM67_S_E_Pos            11                                       /*!< CLK_T::CLKSEL2: PWM67_S_E Position */
#define CLK_CLKSEL2_PWM67_S_E_Msk            (1ul << CLK_CLKSEL2_PWM67_S_E_Pos)       /*!< CLK_T::CLKSEL2: PWM67_S_E Mask */
#define CLK_CLKSEL2_PWM67_S_EXT_Pos          11                                       /*!< CLK_T::CLKSEL2: PWM67_S_E Position */
#define CLK_CLKSEL2_PWM67_S_EXT_Msk          (1ul << CLK_CLKSEL2_PWM67_S_EXT_Pos)     /*!< CLK_T::CLKSEL2: PWM67_S_E Mask */

#define CLK_CLKSEL2_PWM45_S_E_Pos            10                                       /*!< CLK_T::CLKSEL2: PWM45_S_E Position */
#define CLK_CLKSEL2_PWM45_S_E_Msk            (1ul << CLK_CLKSEL2_PWM45_S_E_Pos)       /*!< CLK_T::CLKSEL2: PWM45_S_E Mask */
#define CLK_CLKSEL2_PWM45_S_EXT_Pos          10                                       /*!< CLK_T::CLKSEL2: PWM45_S_EXT Position */
#define CLK_CLKSEL2_PWM45_S_EXT_Msk          (1ul << CLK_CLKSEL2_PWM45_S_EXT_Pos)     /*!< CLK_T::CLKSEL2: PWM45_S_EXT Mask */

#define CLK_CLKSEL2_PWM23_S_E_Pos            9                                        /*!< CLK_T::CLKSEL2: PWM23_S_E Position */
#define CLK_CLKSEL2_PWM23_S_E_Msk            (1ul << CLK_CLKSEL2_PWM23_S_E_Pos)       /*!< CLK_T::CLKSEL2: PWM23_S_E Mask */
#define CLK_CLKSEL2_PWM23_S_EXT_Pos          9                                        /*!< CLK_T::CLKSEL2: PWM23_S_EXT Position */
#define CLK_CLKSEL2_PWM23_S_EXT_Msk          (1ul << CLK_CLKSEL2_PWM23_S_EXT_Pos)     /*!< CLK_T::CLKSEL2: PWM23_S_EXT Mask */

#define CLK_CLKSEL2_PWM01_S_E_Pos            8                                        /*!< CLK_T::CLKSEL2: PWM01_S_E Position */
#define CLK_CLKSEL2_PWM01_S_E_Msk            (1ul << CLK_CLKSEL2_PWM01_S_E_Pos)       /*!< CLK_T::CLKSEL2: PWM01_S_E Mask */
#define CLK_CLKSEL2_PWM01_S_EXT_Pos          8                                        /*!< CLK_T::CLKSEL2: PWM01_S_EXT Position */
#define CLK_CLKSEL2_PWM01_S_EXT_Msk          (1ul << CLK_CLKSEL2_PWM01_S_EXT_Pos)     /*!< CLK_T::CLKSEL2: PWM01_S_EXT Mask */

#define CLK_CLKSEL2_PWM67_S_Pos              6                                        /*!< CLK_T::CLKSEL2: PWM67_S_ Position */
#define CLK_CLKSEL2_PWM67_S_Msk              (3ul << CLK_CLKSEL2_PWM67_S_Pos)         /*!< CLK_T::CLKSEL2: PWM67_S_ Mask */

#define CLK_CLKSEL2_PWM45_S_Pos              4                                        /*!< CLK_T::CLKSEL2: PWM45_S Position */
#define CLK_CLKSEL2_PWM45_S_Msk              (3ul << CLK_CLKSEL2_PWM45_S_Pos)         /*!< CLK_T::CLKSEL2: PWM45_S Mask */

#define CLK_CLKSEL2_FRQDIV_S_Pos             2                                        /*!< CLK_T::CLKSEL2: FRQDIV_S Position */
#define CLK_CLKSEL2_FRQDIV_S_Msk             (3ul << CLK_CLKSEL2_FRQDIV_S_Pos)        /*!< CLK_T::CLKSEL2: FRQDIV_S Mask */

#define CLK_CLKSEL2_I2S_S_Pos                0                                        /*!< CLK_T::CLKSEL2: I2S_S Position */
#define CLK_CLKSEL2_I2S_S_Msk                (3ul << CLK_CLKSEL2_I2S_S_Pos)           /*!< CLK_T::CLKSEL2: I2S_S Mask */

/* CLK CLKSEL3 Bit Field Definitions */
#define CLK_CLKSEL3_SC2_S_Pos                4                                        /*!< CLK_T::CLKSEL3: SC2_S Position */
#define CLK_CLKSEL3_SC2_S_Msk                (3ul << CLK_CLKSEL3_SC2_S_Pos)           /*!< CLK_T::CLKSEL3: SC2_S Mask */

#define CLK_CLKSEL3_SC1_S_Pos                2                                        /*!< CLK_T::CLKSEL3: SC1_S Position */
#define CLK_CLKSEL3_SC1_S_Msk                (3ul << CLK_CLKSEL3_SC1_S_Pos)           /*!< CLK_T::CLKSEL3: SC1_S Mask */

#define CLK_CLKSEL3_SC0_S_Pos                0                                        /*!< CLK_T::CLKSEL3: SC0_S Position */
#define CLK_CLKSEL3_SC0_S_Msk                (3ul << CLK_CLKSEL3_SC0_S_Pos)           /*!< CLK_T::CLKSEL3: SC0_S Mask */

/* CLK CLKDIV Bit Field Definitions */
#define CLK_CLKDIV_ADC_N_Pos                 16                                       /*!< CLK_T::CLKDIV: ADC_N Position */
#define CLK_CLKDIV_ADC_N_Msk                 (0xFFul << CLK_CLKDIV_ADC_N_Pos)         /*!< CLK_T::CLKDIV: ADC_N Mask */

#define CLK_CLKDIV_UART_N_Pos                8                                        /*!< CLK_T::CLKDIV: UART_N Position */
#define CLK_CLKDIV_UART_N_Msk                (0xFul << CLK_CLKDIV_UART_N_Pos)         /*!< CLK_T::CLKDIV: UART_N Mask */

#define CLK_CLKDIV_USB_N_Pos                 4                                        /*!< CLK_T::CLKDIV: USB_N Position */
#define CLK_CLKDIV_USB_N_Msk                 (0xFul << CLK_CLKDIV_USB_N_Pos)          /*!< CLK_T::CLKDIV: USB_N Mask */

#define CLK_CLKDIV_HCLK_N_Pos                0                                        /*!< CLK_T::CLKDIV: HCLK_N Position */
#define CLK_CLKDIV_HCLK_N_Msk                (0xFul << CLK_CLKDIV_HCLK_N_Pos)         /*!< CLK_T::CLKDIV: HCLK_N Mask */

/* CLK CLKDIV1 Bit Field Definitions */
#define CLK_CLKDIV1_SC2_N_Pos                16                                       /*!< CLK_T::CLKDIV: SC2_N Position */
#define CLK_CLKDIV1_SC2_N_Msk                (0xFFul << CLK_CLKDIV1_SC2_N_Pos)        /*!< CLK_T::CLKDIV: SC2_N Mask */

#define CLK_CLKDIV1_SC1_N_Pos                8                                        /*!< CLK_T::CLKDIV: SC1_N Position */
#define CLK_CLKDIV1_SC1_N_Msk                (0xFFul << CLK_CLKDIV1_SC1_N_Pos)        /*!< CLK_T::CLKDIV: SC1_N Mask */

#define CLK_CLKDIV1_SC0_N_Pos                0                                        /*!< CLK_T::CLKDIV: SC0_N Position */
#define CLK_CLKDIV1_SC0_N_Msk                (0xFFul << CLK_CLKDIV1_SC0_N_Pos)        /*!< CLK_T::CLKDIV: SC0_N Mask */

/* CLK PLLCON Bit Field Definitions */
#define CLK_PLLCON_PLL_SRC_Pos               19                                       /*!< CLK_T::PLLCON: PLL_SRC Position */
#define CLK_PLLCON_PLL_SRC_Msk               (1ul << CLK_PLLCON_PLL_SRC_Pos)          /*!< CLK_T::PLLCON: PLL_SRC Mask */

#define CLK_PLLCON_OE_Pos                    18                                       /*!< CLK_T::PLLCON: PLL_SRC Position */
#define CLK_PLLCON_OE_Msk                    (1ul << CLK_PLLCON_OE_Pos)               /*!< CLK_T::PLLCON: PLL_SRC Mask */

#define CLK_PLLCON_BP_Pos                    17                                       /*!< CLK_T::PLLCON: OE Position */
#define CLK_PLLCON_BP_Msk                    (1ul << CLK_PLLCON_BP_Pos)               /*!< CLK_T::PLLCON: OE Mask */

#define CLK_PLLCON_PD_Pos                    16                                       /*!< CLK_T::PLLCON: PD Position */
#define CLK_PLLCON_PD_Msk                    (1ul << CLK_PLLCON_PD_Pos)               /*!< CLK_T::PLLCON: PD Mask */

#define CLK_PLLCON_OUT_DV_Pos                14                                       /*!< CLK_T::PLLCON: OUT_DV Position */
#define CLK_PLLCON_OUT_DV_Msk                (3ul << CLK_PLLCON_OUT_DV_Pos)           /*!< CLK_T::PLLCON: OUT_DV Mask */

#define CLK_PLLCON_IN_DV_Pos                 9                                        /*!< CLK_T::PLLCON: IN_DV Position */
#define CLK_PLLCON_IN_DV_Msk                 (0x1Ful << CLK_PLLCON_IN_DV_Pos)         /*!< CLK_T::PLLCON: IN_DV Mask */

#define CLK_PLLCON_FB_DV_Pos                 0                                        /*!< CLK_T::PLLCON: FB_DV Position */
#define CLK_PLLCON_FB_DV_Msk                 (0x1FFul << CLK_PLLCON_FB_DV_Pos)        /*!< CLK_T::PLLCON: FB_DV Mask */

/* CLK FRQDIV Bit Field Definitions */
#define CLK_FRQDIV_DIVIDER_EN_Pos            4                                        /*!< CLK_T::FRQDIV: DIVIDER_EN Position */
#define CLK_FRQDIV_DIVIDER_EN_Msk            (1ul << CLK_FRQDIV_DIVIDER_EN_Pos)       /*!< CLK_T::FRQDIV: DIVIDER_EN Mask */

#define CLK_FRQDIV_FSEL_Pos                  0                                        /*!< CLK_T::FRQDIV: FRQDIV_FSEL Position */
#define CLK_FRQDIV_FSEL_Msk                  (0xFul << CLK_FRQDIV_FSEL_Pos)           /*!< CLK_T::FRQDIV: FRQDIV_FSEL Mask */

/*@}*/ /* end of group CLK_CONST */
/*@}*/ /* end of group CLK */



/*----------------------------- Cyclic Redundancy Check (CRC) Controller -----------------------------*/
/** @addtogroup CRC Cyclic Redundancy Check Controller (CRC)
  Memory Mapped Structure for Cyclic Redundancy Check
  @{
 */


typedef struct
{


/**
 * @var CRC_T::CTL
 * Offset: 0x00  CRC Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CRCCEN    |CRC Channel Enable
 * |        |          |0 = No effect.
 * |        |          |1 = CRC operation Enabled.
 * |        |          |Note1: When operating in CRC DMA mode (TRIG_EN (CRC_CTL[23]) = 1), if user clears this bit,
 * |        |          |the DMA operation will be continuous until all CRC DMA operation is done, and the TRIG_EN
 * |        |          |(CRC_CTL[23]) bit will keep 1until all CRC DMA operation done.
 * |        |          |But in this case, the CRC_BLKD_IF (CRC_DMAISR[1])flag will inactive, user can read CRC
 * |        |          |checksum result only if TRIG_EN (CRC_CTL[23]) clears to 0.
 * |        |          |Note2: When operating in CRC DMA mode (TRIG_EN (CRC_CTL[23]) = 1), if user wants to stop the
 * |        |          |transfer immediately, user can write 1 to CRC_RST (CRC_CTL [1]) bit to stop the
 * |        |          |transmission.
 * |[1]     |CRC_RST   |CRC Engine Reset
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the internal CRC state machine and internal buffer.
 * |        |          |The others contents of CRC_CTL register will not be cleared.
 * |        |          |This bit will be cleared automatically.
 * |        |          |Note: When operated in CPU PIO mode, setting this bit will reload the initial seed value
 * |        |          |(CRC_SEED register).
 * |[23]    |TRIG_EN   |Trigger Enable
 * |        |          |This bit is used to trigger the CRC DMA transfer.
 * |        |          |0 = No effect.
 * |        |          |1 = CRC DMA data read or write transfer Enabled.
 * |        |          |Note1: If this bit asserts which indicates the CRC engine operation in CRC DMA mode, do not
 * |        |          |fill in any data in CRC_WDATA register.
 * |        |          |Note2: When CRC DMA transfer completed, this bit will be cleared automatically.
 * |        |          |Note3: If the bus error occurs when CRC DMA transfer data, all CRC DMA transfer will be
 * |        |          |stopped.
 * |        |          |Software must reset all DMA channel before trigger DMA again.
 * |[24]    |WDATA_RVS |Write Data Order Reverse
 * |        |          |This bit is used to enable the bit order reverse function for write data value in CRC_WDATA
 * |        |          |register.
 * |        |          |0 = Bit order reverse for CRC write data in Disabled.
 * |        |          |1 = Bit order reverse for CRC write data in Enabled (per byre).
 * |        |          |Note: If the write data is 0xAABBCCDD, the bit order reverse for CRC write data in is
 * |        |          |0x55DD33BB
 * |[25]    |CHECKSUM_RVS|Checksum Reverse
 * |        |          |This bit is used to enable the bit order reverse function for write data value in
 * |        |          |CRC_CHECKSUM register.
 * |        |          |0 = Bit order reverse for CRC checksum Disabled.
 * |        |          |1 = Bit order reverse for CRC checksum Enabled.
 * |        |          |Note: If the checksum result is 0XDD7B0F2E, the bit order reverse for CRC checksum is
 * |        |          |0x74F0DEBB
 * |[26]    |WDATA_COM |Write Data 1's Complement
 * |        |          |This bit is used to enable the 1's complement function for write data value in CRC_WDATA
 * |        |          |register.
 * |        |          |0 = 1's complement for CRC write data in Disabled.
 * |        |          |1 = 1's complement for CRC write data in Enabled.
 * |[27]    |CHECKSUM_COM|Checksum 1's Complement
 * |        |          |This bit is used to enable the 1's complement function for checksum result in CRC_CHECKSUM
 * |        |          |register.
 * |        |          |0 = 1's complement for CRC checksum Disabled.
 * |        |          |1 = 1's complement for CRC checksum Enabled.
 * |[29:28] |CPU_WDLEN |CPU Write Data Length
 * |        |          |This field indicates the CPU write data length only when operating in CPU PIO mode.
 * |        |          |00 = The write data length is 8-bit mode.
 * |        |          |01 = The write data length is 16-bit mode.
 * |        |          |10 = The write data length is 32-bit mode.
 * |        |          |11 = Reserved.
 * |        |          |Note1: This field is only valid when operating in CPU PIO mode.
 * |        |          |Note2: When the write data length is 8-bit mode, the valid data in CRC_WDATA register is
 * |        |          |only CRC_WDATA [7:0] bits; if the write data length is 16-bit mode, the valid data in
 * |        |          |CRC_WDATA register is only CRC_WDATA [15:0].
 * |[31:30] |CRC_MODE  |CRC Polynomial Mode
 * |        |          |This field indicates the CRC operation polynomial mode.
 * |        |          |00 = CRC-CCITT Polynomial Mode.
 * |        |          |01 = CRC-8 Polynomial Mode.
 * |        |          |10 = CRC-16 Polynomial Mode.
 * |        |          |11 = CRC-32 Polynomial Mode.
 * @var CRC_T::DMASAR
 * Offset: 0x04  CRC DMA Source Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |CRC_DMASAR|CRC DMA Transfer Source Address Register
 * |        |          |This field indicates a 32-bit source address of CRC DMA.
 * |        |          |(CRC_DMASAR + CRC_DMABCR) = (CRC_DMACSAR + CRC_DMACBCR).
 * |        |          |Note: The source address must be word alignment
 * @var CRC_T::DMABCR
 * Offset: 0x0C  CRC DMA Transfer Byte Count Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CRC_DMABCR|CRC DMA Transfer Byte Count Register
 * |        |          |This field indicates a 16-bit total transfer byte count number of CRC DMA
 * |        |          |(CRC_DMASAR + CRC_DMABCR) = (CRC_DMACSAR + CRC_DMACBCR).
 * @var CRC_T::DMACSAR
 * Offset: 0x14  CRC DMA Current Source Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |CRC_DMACSAR|CRC DMA Current Source Address Register (Read Only)
 * |        |          |This field indicates the current source address where the CRC DMA transfer just occurs.
 * |        |          |(CRC_DMASAR + CRC_DMABCR) = (CRC_DMACSAR + CRC_DMACBCR).
 * @var CRC_T::DMACBCR
 * Offset: 0x1C  CRC DMA Current Transfer Byte Count Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CRC_DMACBCR|CRC DMA Current Remained Byte Count Register (Read Only)
 * |        |          |This field indicates the current remained byte count of CRC DMA.
 * |        |          |(CRC_DMASAR + CRC_DMABCR) = (CRC_DMACSAR + CRC_DMACBCR).
 * |        |          |Note: Setting CRC_RST (CRC_CTL[1]) bit to 1 will clear this register value.
 * @var CRC_T::DMAIER
 * Offset: 0x20  CRC DMA Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CRC_TABORT_IE|CRC DMA Read/Write Target Abort Interrupt Enable
 * |        |          |Enable this bit will generate the CRC DMA Target Abort interrupt signal while CRC_TARBOT_IF
 * |        |          |(CRC_DMAISR[0]) bit is set to 1.
 * |        |          |0 = Target abort interrupt generation Disabled during CRC DMA transfer.
 * |        |          |1 = Target abort interrupt generation Enabled during CRC DMA transfer.
 * |[1]     |CRC_BLKD_IE|CRC DMA Block Transfer Done Interrupt Enable
 * |        |          |Enable this bit will generate the CRC DMA Transfer Done interrupt signal while CRC_BLKD_IF
 * |        |          |(CRC_DMAISR[1]) bit is set to 1.
 * |        |          |0 = Interrupt generator Disabled when CRC DMA transfer done.
 * |        |          |1 = Interrupt generator Enabled when CRC DMA transfer done.
 * @var CRC_T::DMAISR
 * Offset: 0x24  CRC DMA Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CRC_TABORT_IF|CRC DMA Read/Write Target Abort Interrupt Flag
 * |        |          |This bit indicates that CRC bus has error or not during CRC DMA transfer.
 * |        |          |0 = No bus error response received during CRC DMA transfer.
 * |        |          |1 = Bus error response received during CRC DMA transfer.
 * |        |          |It is cleared by writing 1 to it through software.
 * |        |          |Note: The bit filed indicate bus master received error response or not.
 * |        |          |If bus master received error response, it means that CRC transfer target abort is happened.
 * |        |          |DMA will stop transfer and respond this event to software then CRC state machine goes to
 * |        |          |IDLE state.
 * |        |          |When target abort occurred, software must reset DMA before transfer those data again.
 * |[1]     |CRC_BLKD_IF|CRC DMA Block Transfer Done Interrupt Flag
 * |        |          |This bit indicates that CRC DMA transfer has finished or not.
 * |        |          |0 = Not finished if TRIG_EN (CRC_CTL[23]) bit has enabled.
 * |        |          |1 = CRC transfer done if TRIG_EN (CRC_CTL[23]) bit has enabled.
 * |        |          |It is cleared by writing 1 to it through software.
 * |        |          |(When CRC DMA transfer done, TRIG_EN (CRC_CTL[23]) bit will be cleared automatically)
 * @var CRC_T::WDATA
 * Offset: 0x80  CRC Write Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |CRC_WDATA |CRC Write Data Register
 * |        |          |When operating in CPU PIO mode, software can write data to this field to perform CRC
 * |        |          |operation.
 * |        |          |When operating in DMA mode, this field indicates the DMA read data from memory and cannot be
 * |        |          |written.
 * |        |          |Note: When the write data length is 8-bit mode, the valid data in CRC_WDATA register is only
 * |        |          |CRC_WDATA [7:0] bits; if the write data length is 16-bit mode, the valid data in CRC_WDATA
 * |        |          |register is only CRC_WDATA [15:0].
 * @var CRC_T::SEED
 * Offset: 0x84  CRC Seed Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |CRC_SEED  |CRC Seed Register
 * |        |          |This field indicates the CRC seed value.
 * @var CRC_T::CHECKSUM
 * Offset: 0x88  CRC Checksum Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |CRC_CHECKSUM|CRC Checksum Register
 * |        |          |This fields indicates the CRC checksum result
 */

    __IO uint32_t CTL;           /* Offset: 0x00  CRC Control Register                                               */
    __IO uint32_t DMASAR;        /* Offset: 0x04  CRC DMA Source Address Register                                    */
    __I  uint32_t RESERVED0;    
    __IO uint32_t DMABCR ;       /* Offset: 0x0C  CRC DMA Transfer Byte Count Register                               */
    __I  uint32_t RESERVED1;    
    __I  uint32_t DMACSAR;       /* Offset: 0x14  CRC DMA Current Source Address Register                            */
    __I  uint32_t RESERVED2;    
    __I  uint32_t DMACBCR;       /* Offset: 0x1C  CRC DMA Current Transfer Byte Count Register                       */
    __IO uint32_t DMAIER ;       /* Offset: 0x20  CRC DMA Interrupt Enable Register                                  */
    __IO uint32_t DMAISR;        /* Offset: 0x24  CRC DMA Interrupt Status Register                                  */
    __I  uint32_t RESERVED3[22];
    __IO uint32_t WDATA;         /* Offset: 0x80  CRC Write Data Register                                            */
    __IO uint32_t SEED;          /* Offset: 0x84  CRC Seed Register                                                  */
    __I  uint32_t CHECKSUM;      /* Offset: 0x88  CRC Checksum Register                                              */

} CRC_T;




/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
@{ */

/* CRC CTL Bit Field Definitions */
#define CRC_CTL_CRC_MODE_Pos            30                                      /*!< CRC_T::CTL: CRC_MODE Position */
#define CRC_CTL_CRC_MODE_Msk            (0x3ul << CRC_CTL_CRC_MODE_Pos)         /*!< CRC_T::CTL: CRC_MODE Mask */

#define CRC_CTL_CPU_WDLEN_Pos           28                                      /*!< CRC_T::CTL: CPU_WDLEN Position */
#define CRC_CTL_CPU_WDLEN_Msk           (0x3ul << CRC_CTL_CPU_WDLEN_Pos)        /*!< CRC_T::CTL: CPU_WDLEN Mask */

#define CRC_CTL_CHECKSUM_COM_Pos        27                                      /*!< CRC_T::CTL: CHECKSUM_COM Position */
#define CRC_CTL_CHECKSUM_COM_Msk        (1ul << CRC_CTL_CHECKSUM_COM_Pos)       /*!< CRC_T::CTL: CHECKSUM_COM Mask */

#define CRC_CTL_WDATA_COM_Pos           26                                      /*!< CRC_T::CTL: WDATA_COM Position */
#define CRC_CTL_WDATA_COM_Msk           (1ul << CRC_CTL_WDATA_COM_Pos)          /*!< CRC_T::CTL: WDATA_COM Mask */

#define CRC_CTL_CHECKSUM_RVS_Pos        25                                      /*!< CRC_T::CTL: CHECKSUM_RVS Position */
#define CRC_CTL_CHECKSUM_RVS_Msk        (1ul << CRC_CTL_CHECKSUM_RVS_Pos)       /*!< CRC_T::CTL: CHECKSUM_RVS Mask */

#define CRC_CTL_WDATA_RVS_Pos           24                                      /*!< CRC_T::CTL: WDATA_RVS Position */
#define CRC_CTL_WDATA_RVS_Msk           (1ul << CRC_CTL_WDATA_RVS_Pos)          /*!< CRC_T::CTL: WDATA_RVS Mask */

#define CRC_CTL_TRIG_EN_Pos             23                                      /*!< CRC_T::CTL: TRIG_EN Position */
#define CRC_CTL_TRIG_EN_Msk             (1ul << CRC_CTL_TRIG_EN_Pos)            /*!< CRC_T::CTL: TRIG_EN Mask */

#define CRC_CTL_CRC_RST_Pos             1                                       /*!< CRC_T::CTL: CRC_RST Position */
#define CRC_CTL_CRC_RST_Msk             (1ul << CRC_CTL_CRC_RST_Pos)            /*!< CRC_T::CTL: CRC_RST Mask */

#define CRC_CTL_CRCCEN_Pos              0                                       /*!< CRC_T::CTL: CRCCEN Position */
#define CRC_CTL_CRCCEN_Msk              (1ul << CRC_CTL_CRCCEN_Pos)             /*!< CRC_T::CTL: CRCCEN Mask */

/* CRC DMASAR Bit Field Definitions */
#define CRC_DMASAR_CRC_DMASAR_Pos       0                                               /*!< CRC_T::DMASAR: CRC_DMASAR Position */
#define CRC_DMASAR_CRC_DMASAR_Msk       (0xFFFFFFFFul << CRC_DMASAR_CRC_DMASAR_Pos)     /*!< CRC_T::DMASAR: CRC_DMASAR Mask */

/* CRC DMABCR Bit Field Definitions */
#define CRC_DMABCR_CRC_DMABCR_Pos       0                                               /*!< CRC_T::DMABCR: CRC_DMABCR Position */
#define CRC_DMABCR_CRC_DMABCR_Msk       (0xFFFFul << CRC_DMABCR_CRC_DMABCR_Pos)         /*!< CRC_T::DMABCR: CRC_DMABCR Mask */

/* CRC DMACSAR Bit Field Definitions */
#define CRC_DMACSAR_CRC_DMACSAR_Pos     0                                               /*!< CRC_T::DMACSAR: CRC_DMACSAR Position */
#define CRC_DMACSAR_CRC_DMACSAR_Msk     (0xFFFFFFFFul << CRC_DMACSAR_CRC_DMACSAR_Pos)   /*!< CRC_T::DMACSAR: CRC_DMACSAR Mask */

/* CRC DMACBCR Bit Field Definitions */
#define CRC_DMACBCR_CRC_DMACBCR_Pos     0                                               /*!< CRC_T::DMACBCR: DMACBCR Position */
#define CRC_DMACBCR_CRC_DMACBCR_Msk     (0xFFFFul << CRC_DMACBCR_CRC_DMACBCR_Pos)       /*!< CRC_T::DMACBCR: DMACBCR Mask */

/* CRC DMAIER Bit Field Definitions */
#define CRC_DMAIER_CRC_BLKD_IE_Pos      1                                               /*!< CRC_T::DMAIER: CRC_BLKD_IE Position */
#define CRC_DMAIER_CRC_BLKD_IE_Msk      (1ul << CRC_DMAIER_CRC_BLKD_IE_Pos)             /*!< CRC_T::DMAIER: CRC_BLKD_IE Mask */

#define CRC_DMAIER_CRC_TABORT_IE_Pos    0                                               /*!< CRC_T::DMAIER: CRC_TABORT_IE Position */
#define CRC_DMAIER_CRC_TABORT_IE_Msk    (1ul << CRC_DMAIER_CRC_TABORT_IE_Pos)           /*!< CRC_T::DMAIER: CRC_TABORT_IE Mask */

/* CRC DMAISR Bit Field Definitions */
#define CRC_DMAISR_CRC_BLKD_IF_Pos      1                                               /*!< CRC_T::DMAISR: CRC_BLKD_IF Position */
#define CRC_DMAISR_CRC_BLKD_IF_Msk      (1ul << CRC_DMAISR_CRC_BLKD_IF_Pos)             /*!< CRC_T::DMAISR: CRC_BLKD_IF Mask */

#define CRC_DMAISR_CRC_TABORT_IF_Pos    0                                               /*!< CRC_T::DMAISR: CRC_TABORT_IF Position */
#define CRC_DMAISR_CRC_TABORT_IF_Msk    (1ul << CRC_DMAISR_CRC_TABORT_IF_Pos)           /*!< CRC_T::DMAISR: CRC_TABORT_IF Mask */

/* CRC WDATA Bit Field Definitions */
#define CRC_WDATA_CRC_WDATA_Pos         0                                               /*!< CRC_T::WDATA: CRC_WDATA Position */
#define CRC_WDATA_CRC_WDATA_Msk         (0xFFFFFFFFul << CRC_WDATA_CRC_WDATA_Pos)       /*!< CRC_T::WDATA: CRC_WDATA Mask */

/* CRC SEED Bit Field Definitions */
#define CRC_SEED_CRC_SEED_Pos           0                                               /*!< CRC_T::SEED: CRC_SEED Position */
#define CRC_SEED_CRC_SEED_Msk           (0xFFFFFFFFul << CRC_SEED_CRC_SEED_Pos)         /*!< CRC_T::SEED: CRC_SEED Mask */

/* CRC CHECKSUM Bit Field Definitions */
#define CRC_CHECKSUM_CRC_CHECKSUM_Pos   0                                               /*!< CRC_T::CHECKSUM: CRC_CHECKSUM Position */
#define CRC_CHECKSUM_CRC_CHECKSUM_Msk   (0xFFFFFFFFul << CRC_CHECKSUM_CRC_CHECKSUM_Pos) /*!< CRC_T::CHECKSUM: CRC_CHECKSUM Mask */
/*@}*/ /* end of group CRC_CONST */
/*@}*/ /* end of group CRC */



/*---------------------- External Bus Interface Controller -------------------------*/
/**
    @addtogroup EBI External Bus Interface Controller (EBI)
    Memory Mapped Structure for EBI Controller
@{ */



typedef struct
{


/**
 * @var EBI_T::EBICON
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
 * @var EBI_T::EXTIME
 * Offset: 0x04  EBI Timing Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:3]   |ExttACC   |EBI Data Access Time
 * |        |          |ExttACC define data access time (tACC).
 * |        |          |tACC = (ExttACC + 1) * MCLK
 * |[10:8]  |ExttAHD   |EBI Data Access Hold Time
 * |        |          |ExttAHD define data access hold time (tAHD).
 * |        |          |tAHD = (ExttAHD + 1) * MCLK
 * |[15:12] |ExtIW2X   |Idle State Cycle After Write
 * |        |          |When write action is finish, idle state is inserted and nCS return to high if ExtIW2X is not
 * |        |          |zero.
 * |        |          |Idle state cycle = (ExtIW2X * MCLK)
 * |[27:24] |ExtIR2R   |Idle State Cycle Between Read-Read
 * |        |          |When read action is finish and next action is going to read, idle state is inserted and nCS
 * |        |          |return
 * |        |          |to high if ExtIR2R is not zero.
 * |        |          |Idle state cycle = (ExtIR2R * MCLK)
 * @var EBI_T::EBICON2
 * Offset: 0x08   External Bus Interface General Control Register 2
 * ---------------------------------------------------------------------------------------------------
 */

    __IO uint32_t EBICON;        /* Offset: 0x00  EBI Control Register                                               */
    __IO uint32_t EXTIME;        /* Offset: 0x04  EBI Timing Control Register                                        */
    __IO uint32_t EBICON2;       /* Offset: 0x08   External Bus Interface General Control Register 2                 */

} EBI_T;



/**
    @addtogroup EBI_CONST EBI Bit Field Definition
    Constant Definitions for EBI Controller
@{ */

/* EBI EBICON Bit Field Definitions */
#define EBI_EBICON_ExttALE_Pos      16                                          /*!< EBI_T::EBICON: ExttALE Position */
#define EBI_EBICON_ExttALE_Msk      (0x7ul << EBI_EBICON_ExttALE_Pos)           /*!< EBI_T::EBICON: ExttALE Mask */

#define EBI_EBICON_MCLKDIV_Pos      8                                           /*!< EBI_T::EBICON: MCLKDIV Position */
#define EBI_EBICON_MCLKDIV_Msk      (0x7ul << EBI_EBICON_MCLKDIV_Pos)           /*!< EBI_T::EBICON: MCLKDIV Mask */

#define EBI_EBICON_ExtBW16_Pos      1                                           /*!< EBI_T::EBICON: ExtBW16 Position */
#define EBI_EBICON_ExtBW16_Msk      (1ul << EBI_EBICON_ExtBW16_Pos)             /*!< EBI_T::EBICON: ExtBW16 Mask */

#define EBI_EBICON_ExtEN_Pos        0                                           /*!< EBI_T::EBICON: ExtEN Position */
#define EBI_EBICON_ExtEN_Msk        (1ul << EBI_EBICON_ExtEN_Pos)               /*!< EBI_T::EBICON: ExtEN Mask */

/* EBI EXTIME Bit Field Definitions */
#define EBI_EXTIME_ExtIR2R_Pos      24                                          /*!< EBI_T::EXTIME: ExtIR2R Position */
#define EBI_EXTIME_ExtIR2R_Msk      (0xFul << EBI_EXTIME_ExtIR2R_Pos)           /*!< EBI_T::EXTIME: ExtIR2R Mask */

#define EBI_EXTIME_ExtIW2X_Pos      12                                          /*!< EBI_T::EXTIME: ExtIW2X Position */
#define EBI_EXTIME_ExtIW2X_Msk      (0xFul << EBI_EXTIME_ExtIW2X_Pos)           /*!< EBI_T::EXTIME: ExtIW2X Mask */

#define EBI_EXTIME_ExttAHD_Pos      8                                           /*!< EBI_T::EXTIME: ExttAHD Position */
#define EBI_EXTIME_ExttAHD_Msk      (0x7ul << EBI_EXTIME_ExttAHD_Pos)           /*!< EBI_T::EXTIME: ExttAHD Mask */

#define EBI_EXTIME_ExttACC_Pos      3                                           /*!< EBI_T::EXTIME: ExttACC Position */
#define EBI_EXTIME_ExttACC_Msk      (0x1Ful << EBI_EXTIME_ExttACC_Pos)          /*!< EBI_T::EXTIME: ExttACC Mask */

/* EBI EBICON2 Bit Field Definitions */
#define EBI_EBICON2_WAHD_OFF_Pos    2                                           /*!< EBI_T::EBICON2: WAHD_OFF Position */
#define EBI_EBICON2_WAHD_OFF_Msk    (1ul << EBI_EBICON2_WAHD_OFF_Pos)           /*!< EBI_T::EBICON2: WAHD_OFF Mask */

#define EBI_EBICON2_RAHD_OFF_Pos    1                                           /*!< EBI_T::EBICON2: RAHD_OFF Position */
#define EBI_EBICON2_RAHD_OFF_Msk    (1ul << EBI_EBICON2_RAHD_OFF_Pos)           /*!< EBI_T::EBICON2: RAHD_OFF Mask */

#define EBI_EBICON2_WBUFF_EN_Pos    0                                           /*!< EBI_T::EBICON2: WBUFF_EN Position */
#define EBI_EBICON2_WBUFF_EN_Msk    (1ul << EBI_EBICON2_WBUFF_EN_Pos)           /*!< EBI_T::EBICON2: WBUFF_EN Mask */
/*@}*/ /* end of group EBI_CONST */
/*@}*/ /* end of group EBI */



/*---------------------- Flash Memory Controller -------------------------*/
/**
    @addtogroup FMC Flash Memory Controller (FMC)
    Memory Mapped Structure for FMC Controller
@{ */


typedef struct
{


/**
 * @var FMC_T::ISPCON
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
 * |        |          |respectively. This bit also functions as MCU booting status flag, which can be used to check
 * |        |          |where
 * |        |          |MCU booted from. This bit is initiated with the inverted value of CBS in Config0 after
 * |        |          |power-
 * |        |          |on reset; It keeps the same value at other reset.
 * |        |          |1 = boot from LDROM
 * |        |          |0 = boot from APROM
 * |[4]     |CFGUEN    |Config Update Enable
 * |        |          |Writing this bit to 1 enables s/w to update Config value by ISP procedure regardless of
 * |        |          |program
 * |        |          |code is running in APROM or LDROM.
 * |        |          |1 = Config update enable
 * |        |          |0 = Config update disable
 * |[5]     |LDUEN     |LDROM Update Enable
 * |        |          |LDROM update enable bit.
 * |        |          |1 = LDROM can be updated when the MCU runs in APROM.
 * |        |          |0 = LDROM cannot be updated
 * |[6]     |ISPFF     |ISP Fail Flag
 * |        |          |This bit is set by hardware when a triggered ISP meets any of the following conditions:
 * |        |          |(1) APROM writes to itself.
 * |        |          |(2) LDROM writes to itself.
 * |        |          |(3) Destination address is illegal, such as over an available range.
 * |        |          |Write 1 to clear.
 * |[7]     |SWRST     |Software Reset
 * |        |          |Writing 1 to this bit to start software reset.
 * |        |          |It is cleared by hardware after reset is finished.
 * |[10:8]  |PT        |Flash Program Time
 * |        |          |000 = 40 us
 * |        |          |001 = 45 us
 * |        |          |010 = 50 us
 * |        |          |011 = 55 us
 * |        |          |100 = 20 us
 * |        |          |101 = 25 us
 * |        |          |110 = 30 us
 * |        |          |111 = 35 us
 * |[14:12] |ET        |Flash Erase Time
 * |        |          |000 = 20 ms (default)
 * |        |          |001 = 25 ms
 * |        |          |010 = 30 ms
 * |        |          |011 = 35 ms
 * |        |          |100 = 3  ms
 * |        |          |101 = 5  ms
 * |        |          |110 = 10 ms
 * |        |          |111 = 15 ms
 * @var FMC_T::ISPADR
 * Offset: 0x04  ISP Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |ISPADR    |ISP Address
 * |        |          |NuMicro M051 series equips with a maximum 16kx32 embedded flash, it supports word program
 * |        |          |only. ISPARD[1:0] must be kept 2'b00 for ISP operation.
 * @var FMC_T::ISPDAT
 * Offset: 0x08  ISP Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |ISPDAT    |ISP Data
 * |        |          |Write data to this register before ISP program operation
 * |        |          |Read data from this register after ISP read operation
 * @var FMC_T::ISPCMD
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
 * @var FMC_T::ISPTRG
 * Offset: 0x10  IISP Trigger Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |ISPGO     |ISP start trigger
 * |        |          |Write 1 to start ISP operation and this bit will be cleared to 0 by hardware automatically
 * |        |          |when ISP
 * |        |          |operation is finish.
 * |        |          |1 = ISP is on going
 * |        |          |0 = ISP done
 * @var FMC_T::DFBADR
 * Offset: 0x14  Data Flash Base Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |DFBA      |Data Flash Base Address
 * |        |          |This register indicates data flash start address.
 * |        |          |It is a read only register.
 * |        |          |For 8/16/32/64kB flash memory device, the data flash size is 4kB and it start address is
 * |        |          |fixed at
 * |        |          |0x01F000 by hardware internally.
 * @var FMC_T::FATCON
 * Offset: 0x18  Flash Access Time Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |FPSEN     |Flash Power Save Enable
 * |        |          |If CPU clock is slower than 24 MHz, then s/w can enable flash power saving function.
 * |        |          |1 = Enable flash power saving
 * |        |          |0 = Disable flash power saving
 * |[3:1]   |FATS      |Flash Access Time Window Select
 * |        |          |These bits are used to decide flash sense amplifier active duration.
 * |        |          |000 = 40 ns
 * |        |          |001 = 50 ns
 * |        |          |010 = 60 ns
 * |        |          |011 = 70 ns
 * |        |          |100 = 80 ns
 * |        |          |101 = 90 ns
 * |        |          |110 = 100 ns
 * |        |          |111 = Reserved
 * |[4]     |L_SPEED   |Flash Low Speed Mode Enable
 * |        |          |1 = Flash access always no wait state (zero wait state)
 * |        |          |0 = Insert wait state while Flash access discontinued address.
 * |        |          |Note: Set this bit only when HCLK <= 25MHz. If HCLK > 25MHz, CPU will fetch wrong
 * |        |          |code and cause fail result.
 * @var FMC_T::ISPSTA
 * Offset: 0x40  ISP Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |ISPGO     |ISP Start Trigger (Read Only)
 * |        |          |Write 1 to start ISP operation and this bit will be cleared to 0 by hardware
 * |        |          |automatically when ISP operation is finished.
 * |        |          |0 = ISP operation finished.
 * |        |          |1 = ISP operation progressed.
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
 * |        |          |{VECMAP[11:0], 9'h000} ~ {VECMAP[11:0], 9'h1FF}
 */

    __IO uint32_t ISPCON;        /* Offset: 0x00  ISP Control Register                                               */
    __IO uint32_t ISPADR;        /* Offset: 0x04  ISP Address Register                                               */
    __IO uint32_t ISPDAT;        /* Offset: 0x08  ISP Data Register                                                  */
    __IO uint32_t ISPCMD;        /* Offset: 0x0C  ISP Command Register                                               */
    __IO uint32_t ISPTRG;        /* Offset: 0x10  IISP Trigger Control Register                                      */
    __I  uint32_t DFBADR;        /* Offset: 0x14  Data Flash Base Address Register                                   */
    __IO uint32_t FATCON;        /* Offset: 0x18  Flash Access Time Control Register                                 */
    __I  uint32_t RESERVED[9];  
    __IO uint32_t ISPSTA;        /* Offset: 0x40  ISP Status Regisger                                                */

} FMC_T;



/**
    @addtogroup FMC_CONST FMC Bit Field Definition
    Constant Definitions for FMC Controller
@{ */

/* FMC ISPCON Bit Field Definitions */
#define FMC_ISPCON_ET_Pos                       12                                      /*!< FMC_T::ISPCON: ET Position */
#define FMC_ISPCON_ET_Msk                       (7ul << FMC_ISPCON_ET_Pos)              /*!< FMC_T::ISPCON: ET Mask     */

#define FMC_ISPCON_PT_Pos                       8                                       /*!< FMC_T::ISPCON: PT Position */
#define FMC_ISPCON_PT_Msk                       (7ul << FMC_ISPCON_PT_Pos)              /*!< FMC_T::ISPCON: PT Mask     */

#define FMC_ISPCON_ISPFF_Pos                    6                                       /*!< FMC_T::ISPCON: ISPFF Position */
#define FMC_ISPCON_ISPFF_Msk                    (1ul << FMC_ISPCON_ISPFF_Pos)           /*!< FMC_T::ISPCON: ISPFF Mask */

#define FMC_ISPCON_LDUEN_Pos                    5                                       /*!< FMC_T::ISPCON: LDUEN Position */
#define FMC_ISPCON_LDUEN_Msk                    (1ul << FMC_ISPCON_LDUEN_Pos)           /*!< FMC_T::ISPCON: LDUEN Mask */

#define FMC_ISPCON_CFGUEN_Pos                   4                                       /*!< FMC_T::ISPCON: CFGUEN Position */
#define FMC_ISPCON_CFGUEN_Msk                   (1ul << FMC_ISPCON_CFGUEN_Pos)          /*!< FMC_T::ISPCON: CFGUEN Mask */

#define FMC_ISPCON_APUEN_Pos                    3                                       /*!< FMC_T::ISPCON: APUEN Position */
#define FMC_ISPCON_APUEN_Msk                    (1ul << FMC_ISPCON_APUEN_Pos)           /*!< FMC_T::ISPCON: APUEN Mask */

#define FMC_ISPCON_BS_Pos                       1                                       /*!< FMC_T::ISPCON: BS Position */
#define FMC_ISPCON_BS_Msk                       (0x1ul << FMC_ISPCON_BS_Pos)            /*!< FMC_T::ISPCON: BS Mask */

#define FMC_ISPCON_ISPEN_Pos                    0                                       /*!< FMC_T::ISPCON: ISPEN Position */
#define FMC_ISPCON_ISPEN_Msk                    (1ul << FMC_ISPCON_ISPEN_Pos)           /*!< FMC_T::ISPCON: ISPEN Mask */

/* FMC ISPADR Bit Field Definitions */
#define FMC_ISPADR_ISPADR_Pos                   0                                       /*!< FMC_T::ISPADR: ISPADR Position */
#define FMC_ISPADR_ISPADR_Msk                   (0xFFFFFFFFul << FMC_ISPADR_ISPADR_Pos) /*!< FMC_T::ISPADR: ISPADR Mask     */

/* FMC ISPADR Bit Field Definitions */
#define FMC_ISPDAT_ISPDAT_Pos                   0                                       /*!< FMC_T::ISPDAT: ISPDAT Position */
#define FMC_ISPDAT_ISPDAT_Msk                   (0xFFFFFFFFul << FMC_ISPDAT_ISPDAT_Pos) /*!< FMC_T::ISPDAT: ISPDAT Mask     */

/* FMC ISPCMD Bit Field Definitions */
#define FMC_ISPCMD_FOEN_Pos                     5                                       /*!< FMC_T::ISPCMD: FOEN Position */
#define FMC_ISPCMD_FOEN_Msk                     (1ul << FMC_ISPCMD_FOEN_Pos)            /*!< FMC_T::ISPCMD: FOEN Mask */

#define FMC_ISPCMD_FCEN_Pos                     4                                       /*!< FMC_T::ISPCMD: FCEN Position */
#define FMC_ISPCMD_FCEN_Msk                     (1ul << FMC_ISPCMD_FCEN_Pos)            /*!< FMC_T::ISPCMD: FCEN Mask */

#define FMC_ISPCMD_FCTRL_Pos                    0                                       /*!< FMC_T::ISPCMD: FCTRL Position */
#define FMC_ISPCMD_FCTRL_Msk                    (0xFul << FMC_ISPCMD_FCTRL_Pos)         /*!< FMC_T::ISPCMD: FCTRL Mask */

/* FMC ISPTRG Bit Field Definitions */
#define FMC_ISPTRG_ISPGO_Pos                    0                                       /*!< FMC_T::ISPTRG: ISPGO Position */
#define FMC_ISPTRG_ISPGO_Msk                    (1ul << FMC_ISPTRG_ISPGO_Pos)           /*!< FMC_T::ISPTRG: ISPGO Mask */

/* FMC DFBADR Bit Field Definitions */
#define FMC_DFBADR_DFBA_Pos                     0                                       /*!< FMC_T::DFBADR: DFBA Position */
#define FMC_DFBADR_DFBA_Msk                     (0xFFFFFFFFul << FMC_DFBADR_DFBA_Pos)   /*!< FMC_T::DFBADR: DFBA Mask     */

/* FMC FATCON Bit Field Definitions */
#define FMC_FATCON_FOMSEL1_Pos                  6                                       /*!< FMC_T::FATCON: FOMSEL1 Position */
#define FMC_FATCON_FOMSEL1_Msk                  (1ul << FMC_FATCON_FOMSEL1_Pos)         /*!< FMC_T::FATCON: FOMSEL1 Mask */

#define FMC_FATCON_FOMSEL0_Pos                  4                                       /*!< FMC_T::FATCON: FOMSEL0 Position */
#define FMC_FATCON_FOMSEL0_Msk                  (1ul << FMC_FATCON_FOMSEL0_Pos)         /*!< FMC_T::FATCON: FOMSEL0 Mask */

#define FMC_FATCON_FATS_Pos                     1                                       /*!< FMC_T::FATCON: FATS Position */
#define FMC_FATCON_FATS_Msk                     (7ul << FMC_FATCON_FATS_Pos)            /*!< FMC_T::FATCON: FATS Mask */

#define FMC_FATCON_FPSEN_Pos                    0                                       /*!< FMC_T::FATCON: FPSEN Position */
#define FMC_FATCON_FPSEN_Msk                    (1ul << FMC_FATCON_FPSEN_Pos)           /*!< FMC_T::FATCON: FPSEN Mask */


#define FMC_ISPSTA_ISPGO_Pos                    0                                       /*!< FMC_T::ISPSTA: ISPGO Position */
#define FMC_ISPSTA_ISPGO_Msk                    (1ul << FMC_ISPSTA_ISPGO_Pos)           /*!< FMC_T::ISPSTA: ISPGO Mask */

#define FMC_ISPSTA_CBS_Pos                      1                                       /*!< FMC_T::ISPSTA: CBS Position */
#define FMC_ISPSTA_CBS_Msk                      (0x3ul << FMC_ISPSTA_CBS_Pos)           /*!< FMC_T::ISPSTA: CBS Mask */

#define FMC_ISPSTA_ISPFF_Pos                    6                                       /*!< FMC_T::ISPSTA: ISPFF Position */
#define FMC_ISPSTA_ISPFF_Msk                    (0x3ul << FMC_ISPSTA_ISPFF_Pos)         /*!< FMC_T::ISPSTA: ISPFF Mask */

#define FMC_ISPSTA_VECMAP_Pos                   9                                       /*!< FMC_T::ISPSTA: VECMAP Position */
#define FMC_ISPSTA_VECMAP_Msk                   (0xFFFul << FMC_ISPSTA_VECMAP_Pos)      /*!< FMC_T::ISPSTA: VECMAP Mask */
/*@}*/ /* end of group FMC_CONST */
/*@}*/ /* end of group FMC */




/*---------------------- General Purpose Input/Output Controller -------------------------*/
/**
    @addtogroup GPIO General Purpose Input/Output Controller (GPIO)
    Memory Mapped Structure for GPIO Controller
@{ */


typedef struct
{


/**
 * @var GPIO_T::PMD
 * Offset: 0x00  GPIO Port [A/B/C/D/E/F] Pin I/O Mode Control
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[2n+1:2n]|PMDn     |GPIOx I/O Pin[n] Mode Control
 * |        |          |Determine each I/O mode of GPIOx pins.
 * |        |          |00 = GPIO port [n] pin is in Input mode.
 * |        |          |01 = GPIO port [n] pin is in Push-pull Output mode.
 * |        |          |10 = GPIO port [n] pin is in Open-drain Output mode.
 * |        |          |11 = GPIO port [n] pin is in Quasi-bidirectional mode.
 * |        |          |Note1: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE.
 * |        |          |Note2:
 * |        |          |The initial value of this field is defined by CIOINI (Config0[10]).
 * |        |          |If CIOINI is set to 1, the default value is 0xFFFF_FFFF and all pins will be Quasi-bidirectional mode after chip is powered on.
 * |        |          |If CIOINI is cleared to 0, the default value is 0x0000_0000 and all pins will be input only mode after chip is powered on.
 * @var GPIO_T::OFFD
 * Offset: 0x04  GPIO Port [A/B/C/D/E/F] Pin Digital Input Path Disable Control
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:16] |OFFD      |GPIOx Pin[n] Digital Input Path Disable Control
 * |        |          |Each of these bits is used to control if the digital input path of corresponding GPIO pin is disabled.
 * |        |          |If input is analog signal, users can disable GPIO digital input path to avoid current leakage.
 * |        |          |0 = I/O digital input path Enabled.
 * |        |          |1 = I/O digital input path Disabled (digital input tied to low). 
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE.
 * @var GPIO_T::DOUT
 * Offset: 0x08  GPIO Port [A/B/C/D/E/F] Data Output Value
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |DOUTn     |GPIOx Pin[n] Output Value
 * |        |          |Each of these bits controls the status of a GPIO pin when the GPIO pin is configured as Push-pull output, open-drain output or quasi-bidirectional mode.
 * |        |          |0 = GPIO port [A/B/C/D/E/F] Pin[n] will drive Low if the GPIO pin is configured as Push-pull output, Open-drain output or Quasi-bidirectional mode.
 * |        |          |1 = GPIO port [A/B/C/D/E/F] Pin[n] will drive High if the GPIO pin is configured as Push-pull output or Quasi-bidirectional mode.
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE. 
 * @var GPIO_T::DMASK
 * Offset: 0x0C  GPIO Port [A/B/C/D/E/F] Data Output Write Mask
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |DMASKn    |Port [A/B/C/D/E/F] Data Output Write Mask
 * |        |          |These bits are used to protect the corresponding register of GPIOx_DOUT bit[n].
 * |        |          |When the DMASK bit[n] is set to 1, the corresponding GPIOx_DOUT[n] bit is protected.
 * |        |          |If the write signal is masked, write data to the protect bit is ignored.
 * |        |          |0 = Corresponding GPIOx_DOUT[n] bit can be updated.
 * |        |          |1 = Corresponding GPIOx_DOUT[n] bit protected.
 * |        |          |Note1: This function only protects the corresponding GPIOx_DOUT[n] bit, and will not protect the corresponding bit control register (PAn_PDIO, PBn_PDIO, PCn_PDIO, PDn_PDIO, PEn_PDIO and PFn_PDIO). 
 * |        |          |Note2: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE.
 * @var GPIO_T::PIN
 * Offset: 0x10  GPIO Port [A/B/C/D/E/F] Pin Value
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |PINn      |Port [A/B/C/D/E/F] Pin Values
 * |        |          |Each bit of the register reflects the actual status of the respective GPIO pin.
 * |        |          |If the bit is 1, it indicates the corresponding pin status is high, else the pin status is low.
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE. 
 * @var GPIO_T::DBEN
 * Offset: 0x14  GPIO Port [A/B/C/D/E/F] De-bounce Enable
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |DBENn     |Port [A/B/C/D/E/F] Input Signal De-Bounce Enable
 * |        |          |DBEN[n] is used to enable the de-bounce function for each corresponding bit.
 * |        |          |If the input signal pulse width cannot be sampled by continuous two de-bounce sample cycle, the input signal transition is seen as the signal bounce and will not trigger the interrupt.
 * |        |          |The de-bounce clock source is controlled by DBNCECON[4], one de-bounce sample cycle period is controlled by DBNCECON[3:0].
 * |        |          |0 = Bit[n] de-bounce function Disabled.
 * |        |          |1 = Bit[n] de-bounce function Enabled.
 * |        |          |The de-bounce function is valid only for edge triggered interrupt.
 * |        |          |If the interrupt mode is level triggered, the de-bounce enable bit is ignored.
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE.
 * @var GPIO_T::IMD
 * Offset: 0x18  GPIO Port [A/B/C/D/E/F] Interrupt Mode Control
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |IMDn      |Port [A/B/C/D/E/F] Edge Or Level Detection Interrupt Control
 * |        |          |IMD[n] is used to control the interrupt is by level trigger or by edge trigger.
 * |        |          |If the interrupt is by edge trigger, the trigger source can be controlled by de-bounce.
 * |        |          |If the interrupt is by level trigger, the input source is sampled by one HCLK.
 * |        |          |clock and generates the interrupt.
 * |        |          |0 = Edge trigger interrupt.
 * |        |          |1 = Level trigger interrupt.
 * |        |          |If the pin is set as the level trigger interrupt, only one level can be set on the registers GPIOx_IEN.
 * |        |          |If both levels to trigger interrupt are set, the setting is ignored and no interrupt will occur.
 * |        |          |The de-bounce function is valid only for edge triggered interrupt.
 * |        |          |If the interrupt mode is level triggered, the de-bounce enable bit is ignored.
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE. 
 * @var GPIO_T::IEN
 * Offset: 0x1C  GPIO Port [A/B/C/D/E/F] Interrupt Enable
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |IF_ENn    |Port [A/B/C/D/E/F] Interrupt Enable By Input Falling Edge Or Input Level Low
 * |        |          |IF_EN[n] is used to enable the interrupt for each of the corresponding input GPIO_PIN[n].
 * |        |          |Set bit to 1 also enable the pin wake-up function.
 * |        |          |When setting the IF_EN[n] bit to 1:
 * |        |          |If the interrupt is level trigger, the input PIN[n] state at level "low" will generate the interrupt.
 * |        |          |If the interrupt is edge trigger, the input PIN[n] state change from "high-to-low" will generate the interrupt.
 * |        |          |0 = PIN[n] state low-level or high-to-low change interrupt Disabled.
 * |        |          |1 = PIN[n] state low-level or high-to-low change interrupt Enabled.
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE.
 * |[n+16]  |IR_ENn    |Port [A/B/C/D/E/F] Interrupt Enable By Input Rising Edge Or Input Level High
 * |        |          |IR_EN[n] used to enable the interrupt for each of the corresponding input GPIO_PIN[n].
 * |        |          |Set bit to 1 also enable the pin wake-up function.
 * |        |          |When setting the IR_EN[n] bit to 1:
 * |        |          |If the interrupt is level trigger, the input PIN[n] state at level "high" will generate the interrupt.
 * |        |          |If the interrupt is edge trigger, the input PIN[n] state change from "low-to-high" will generate the interrupt.
 * |        |          |0 = PIN[n] level-high or low-to-high interrupt Disabled.
 * |        |          |1 = PIN[n] level-high or low-to-high interrupt Enabled.
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE.
 * @var GPIO_T::ISRC
 * Offset: 0x20  GPIO Port [A/B/C/D/E/F] Interrupt Source Flag
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[n]     |ISRCn     |Port [A/B/C/D/E/F] Interrupt Source Flag
 * |        |          |Read :
 * |        |          |0 = No interrupt at GPIOx[n].
 * |        |          |1 = GPIOx[n] generates an interrupt.
 * |        |          |Write :
 * |        |          |0= No action.
 * |        |          |1= Clear the corresponding pending interrupt. 
 * |        |          |Note: Max. n = 3 for GPIOF; Max. n = 15 for GPIOA/GPIOB/GPIOC/GPIOD/GPIOE. 
 */

    __IO uint32_t PMD;           /* Offset: 0x00  GPIO Port [A/B/C/D/E/F] Pin I/O Mode Control                       */
    __IO uint32_t OFFD;          /* Offset: 0x04  GPIO Port [A/B/C/D/E/F] Pin Digital Input Path Disable Control     */
    __IO uint32_t DOUT;          /* Offset: 0x08  GPIO Port [A/B/C/D/E/F] Data Output Value                          */
    __IO uint32_t DMASK;         /* Offset: 0x0C  GPIO Port [A/B/C/D/E/F] Data Output Write Mask                     */
    __I  uint32_t PIN;           /* Offset: 0x10  GPIO Port [A/B/C/D/E/F] Pin Value                                  */
    __IO uint32_t DBEN;          /* Offset: 0x14  GPIO Port [A/B/C/D/E/F] De-bounce Enable                           */
    __IO uint32_t IMD;           /* Offset: 0x18  GPIO Port [A/B/C/D/E/F] Interrupt Mode Control                     */
    __IO uint32_t IEN;           /* Offset: 0x1C  GPIO Port [A/B/C/D/E/F] Interrupt Enable                           */
    __IO uint32_t ISRC;          /* Offset: 0x20  GPIO Port [A/B/C/D/E/F] Interrupt Source Flag                      */

} GPIO_T;





typedef struct
{


/**
 * @var GPIO_DBNCECON_T::DBNCECON
 * Offset: 0x180  External Interrupt De-bounce Control
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |DBCLKSEL  |De-Bounce Sampling Cycle Selection
 * |        |          |0000 = Sample interrupt input once per 1 clocks
 * |        |          |0001 = Sample interrupt input once per 2 clocks
 * |        |          |0010 = Sample interrupt input once per 4 clocks
 * |        |          |0011 = Sample interrupt input once per 8 clocks
 * |        |          |0100 = Sample interrupt input once per 16 clocks
 * |        |          |0101 = Sample interrupt input once per 32 clocks
 * |        |          |0110 = Sample interrupt input once per 64 clocks
 * |        |          |0111 = Sample interrupt input once per 128 clocks
 * |        |          |1000 = Sample interrupt input once per 256 clocks
 * |        |          |1001 = Sample interrupt input once per 2*256 clocks
 * |        |          |1010 = Sample interrupt input once per 4*256clocks
 * |        |          |1011 = Sample interrupt input once per 8*256 clocks
 * |        |          |1100 = Sample interrupt input once per 16*256 clocks
 * |        |          |1101 = Sample interrupt input once per 32*256 clocks
 * |        |          |1110 = Sample interrupt input once per 64*256 clocks
 * |        |          |1111 = Sample interrupt input once per 128*256 clocks
 * |[4]     |DBCLKSRC  |De-Bounce Counter Clock Source Selection
 * |        |          |0 = De-bounce counter clock source is the HCLK.
 * |        |          |1 = De-bounce counter clock source is the internal 10 kHz low speed oscillator.
 * |[5]     |ICLK_ON   |Interrupt Clock On Mode
 * |        |          |0 = Edge detection circuit is active only if I/O pin corresponding GPIOx_IEN bit is set to 1.
 * |        |          |1 = All I/O pins edge detection circuit is always active after reset.
 * |        |          |It is recommended to turn off this bit to save system power if no special application concern.
 */

    __IO uint32_t DBNCECON;      /* Offset: 0x180  External Interrupt De-bounce Control                              */

} GPIO_DBNCECON_T;



/**
    @addtogroup GPIO_CONST GPIO Bit Field Definition
    Constant Definitions for GPIO Controller
@{ */


/* GPIO PMD Bit Field Definitions */
#define GPIO_PMD_PMD15_Pos          30                                          /*!< GPIO_T::PMD: PMD15 Position */
#define GPIO_PMD_PMD15_Msk          (0x3ul << GPIO_PMD_PMD15_Pos)               /*!< GPIO_T::PMD: PMD15 Mask */

#define GPIO_PMD_PMD14_Pos          28                                          /*!< GPIO_T::PMD: PMD14 Position */
#define GPIO_PMD_PMD14_Msk          (0x3ul << GPIO_PMD_PMD14_Pos)               /*!< GPIO_T::PMD: PMD14 Mask */

#define GPIO_PMD_PMD13_Pos          26                                          /*!< GPIO_T::PMD: PMD13 Position */
#define GPIO_PMD_PMD13_Msk          (0x3ul << GPIO_PMD_PMD13_Pos)               /*!< GPIO_T::PMD: PMD13 Mask */

#define GPIO_PMD_PMD12_Pos          24                                          /*!< GPIO_T::PMD: PMD12 Position */
#define GPIO_PMD_PMD12_Msk          (0x3ul << GPIO_PMD_PMD12_Pos)               /*!< GPIO_T::PMD: PMD12 Mask */

#define GPIO_PMD_PMD11_Pos          22                                          /*!< GPIO_T::PMD: PMD11 Position */
#define GPIO_PMD_PMD11_Msk          (0x3ul << GPIO_PMD_PMD11_Pos)               /*!< GPIO_T::PMD: PMD11 Mask */

#define GPIO_PMD_PMD10_Pos          20                                          /*!< GPIO_T::PMD: PMD10 Position */
#define GPIO_PMD_PMD10_Msk          (0x3ul << GPIO_PMD_PMD10_Pos)               /*!< GPIO_T::PMD: PMD10 Mask */

#define GPIO_PMD_PMD9_Pos           18                                          /*!< GPIO_T::PMD: PMD9 Position */
#define GPIO_PMD_PMD9_Msk           (0x3ul << GPIO_PMD_PMD9_Pos)                /*!< GPIO_T::PMD: PMD9 Mask */

#define GPIO_PMD_PMD8_Pos           16                                          /*!< GPIO_T::PMD: PMD8 Position */
#define GPIO_PMD_PMD8_Msk           (0x3ul << GPIO_PMD_PMD8_Pos)                /*!< GPIO_T::PMD: PMD8 Mask */

#define GPIO_PMD_PMD7_Pos           14                                          /*!< GPIO_T::PMD: PMD7 Position */
#define GPIO_PMD_PMD7_Msk           (0x3ul << GPIO_PMD_PMD7_Pos)                /*!< GPIO_T::PMD: PMD7 Mask */

#define GPIO_PMD_PMD6_Pos           12                                          /*!< GPIO_T::PMD: PMD6 Position */
#define GPIO_PMD_PMD6_Msk           (0x3ul << GPIO_PMD_PMD6_Pos)                /*!< GPIO_T::PMD: PMD6 Mask */

#define GPIO_PMD_PMD5_Pos           10                                          /*!< GPIO_T::PMD: PMD5 Position */
#define GPIO_PMD_PMD5_Msk           (0x3ul << GPIO_PMD_PMD5_Pos)                /*!< GPIO_T::PMD: PMD5 Mask */

#define GPIO_PMD_PMD4_Pos           8                                           /*!< GPIO_T::PMD: PMD4 Position */
#define GPIO_PMD_PMD4_Msk           (0x3ul << GPIO_PMD_PMD4_Pos)                /*!< GPIO_T::PMD: PMD4 Mask */

#define GPIO_PMD_PMD3_Pos           6                                           /*!< GPIO_T::PMD: PMD3 Position */
#define GPIO_PMD_PMD3_Msk           (0x3ul << GPIO_PMD_PMD3_Pos)                /*!< GPIO_T::PMD: PMD3 Mask */

#define GPIO_PMD_PMD2_Pos           4                                           /*!< GPIO_T::PMD: PMD2 Position */
#define GPIO_PMD_PMD2_Msk           (0x3ul << GPIO_PMD_PMD2_Pos)                /*!< GPIO_T::PMD: PMD2 Mask */

#define GPIO_PMD_PMD1_Pos           2                                           /*!< GPIO_T::PMD: PMD1 Position */
#define GPIO_PMD_PMD1_Msk           (0x3ul << GPIO_PMD_PMD1_Pos)                /*!< GPIO_T::PMD: PMD1 Mask */

#define GPIO_PMD_PMD0_Pos           0                                           /*!< GPIO_T::PMD: PMD0 Position */
#define GPIO_PMD_PMD0_Msk           (0x3ul << GPIO_PMD_PMD0_Pos)                /*!< GPIO_T::PMD: PMD0 Mask */

/* GPIO OFFD Bit Field Definitions */
#define GPIO_OFFD_OFFD_Pos          16                                          /*!< GPIO_T::OFFD: OFFD Position */
#define GPIO_OFFD_OFFD_Msk          (0xFFFFul << GPIO_OFFD_OFFD_Pos)            /*!< GPIO_T::OFFD: OFFD Mask */

/* GPIO DOUT Bit Field Definitions */
#define GPIO_DOUT_DOUT_Pos          0                                           /*!< GPIO_T::DOUT: DOUT Position */
#define GPIO_DOUT_DOUT_Msk          (0xFFFFul << GPIO_DOUT_DOUT_Pos)            /*!< GPIO_T::DOUT: DOUT Mask */

/* GPIO DMASK Bit Field Definitions */
#define GPIO_DMASK_DMASK_Pos        0                                           /*!< GPIO_T::DMASK: DMASK Position */
#define GPIO_DMASK_DMASK_Msk        (0xFFFFul << GPIO_DMASK_DMASK_Pos)          /*!< GPIO_T::DMASK: DMASK Mask */

/* GPIO PIN Bit Field Definitions */
#define GPIO_PIN_PIN_Pos            0                                           /*!< GPIO_T::PIN: PIN Position */
#define GPIO_PIN_PIN_Msk            (0xFFFFul << GPIO_PIN_PIN_Pos)              /*!< GPIO_T::PIN: PIN Mask */

/* GPIO DBEN Bit Field Definitions */
#define GPIO_DBEN_DBEN_Pos          0                                           /*!< GPIO_T::DBEN: DBEN Position */
#define GPIO_DBEN_DBEN_Msk          (0xFFFFul << GPIO_DBEN_DBEN_Pos)            /*!< GPIO_T::DBEN: DBEN Mask */

/* GPIO IMD Bit Field Definitions */
#define GPIO_IMD_IMD_Pos            0                                           /*!< GPIO_T::IMD: IMD Position */
#define GPIO_IMD_IMD_Msk            (0xFFFFul << GPIO_IMD_IMD_Pos)              /*!< GPIO_T::IMD: IMD Mask */

/* GPIO IEN Bit Field Definitions */
#define GPIO_IEN_IR_EN_Pos          16                                          /*!< GPIO_T::IEN: IR_EN Position */
#define GPIO_IEN_IR_EN_Msk          (0xFFFFul << GPIO_IEN_IR_EN_Pos)            /*!< GPIO_T::IEN: IR_EN Mask */

#define GPIO_IEN_IF_EN_Pos          0                                           /*!< GPIO_T::IEN: IF_EN Position */
#define GPIO_IEN_IF_EN_Msk          (0xFFFFul << GPIO_IEN_IF_EN_Pos)            /*!< GPIO_T::IEN: IF_EN Mask */

/* GPIO ISRC Bit Field Definitions */
#define GPIO_ISRC_ISRC_Pos          0                                           /*!< GPIO_T::ISRC: ISRC Position */
#define GPIO_ISRC_ISRC_Msk          (0xFFFFul << GPIO_ISRC_ISRC_Pos)            /*!< GPIO_T::ISRC: ISRC Mask */

/* GPIO DBNCECON Bit Field Definitions */
#define GPIO_DBNCECON_ICLK_ON_Pos   5                                           /*!< GPIO_DBNCECON_T::DBNCECON: ICLK_ON  Position */
#define GPIO_DBNCECON_ICLK_ON_Msk   (1ul << GPIO_DBNCECON_ICLK_ON_Pos)          /*!< GPIO_DBNCECON_T::DBNCECON: ICLK_ON  Mask */

#define GPIO_DBNCECON_DBCLKSRC_Pos  4                                           /*!< GPIO_DBNCECON_T::DBNCECON: DBCLKSRC Position */
#define GPIO_DBNCECON_DBCLKSRC_Msk  (1ul << GPIO_DBNCECON_DBCLKSRC_Pos)         /*!< GPIO_DBNCECON_T::DBNCECON: DBCLKSRC Mask */

#define GPIO_DBNCECON_DBCLKSEL_Pos  0                                           /*!< GPIO_DBNCECON_T::DBNCECON: DBCLKSEL Position */
#define GPIO_DBNCECON_DBCLKSEL_Msk  (0xFul << GPIO_DBNCECON_DBCLKSEL_Pos)       /*!< GPIO_DBNCECON_T::DBNCECON: DBCLKSEL Mask */
/*@}*/ /* end of group GPIO_CONST */
/*@}*/ /* end of group GPIO */




/*---------------------- Inter-IC Bus Controller -------------------------*/
/**
    @addtogroup I2C Inter-IC Bus Controller (I2C)
    Memory Mapped Structure for I2C Controller
@{ */


typedef struct
{


/**
 * @var I2C_T::I2CON
 * Offset: 0x00  I2C Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[2]     |AA        |Assert Acknowledge Control
 * |        |          |When AA =1 prior to address or data received, an acknowledged (low level to I2Cn_SDA) will
 * |        |          |be returned during the acknowledge clock pulse on the I2Cn_SCL line when 1.) A slave is
 * |        |          |acknowledging the address sent from master, 2.) The receiver devices are acknowledging the
 * |        |          |data sent by transmitter.
 * |        |          |When AA=0 prior to address or data received, a Not acknowledged (high level to I2Cn_SDA)
 * |        |          |will be returned during the acknowledge clock pulse on the I2Cn_SCL line.
 * |[3]     |SI        |I2C Interrupt Flag
 * |        |          |When a new I2C state is present in the I2CSTATUS register, the SI flag is set by hardware,
 * |        |          |and if bit EI (I2CON [7]) is set, the I2C interrupt is requested.
 * |        |          |SI must be cleared by software.
 * |        |          |Clear SI by writing 1 to this bit.
 * |[4]     |STO       |I2C STOP Control
 * |        |          |In Master mode, setting STO to transmit a STOP condition to bus then I2C hardware will check
 * |        |          |the bus condition if a STOP condition is detected this bit will be cleared by hardware
 * |        |          |automatically.
 * |        |          |In a slave mode, setting STO resets I2C hardware to the defined "not addressed" slave mode.
 * |        |          |This means it is NO LONGER in the slave receiver mode to receive data from the master
 * |        |          |transmit device.
 * |[5]     |STA       |I2C START Control
 * |        |          |Setting STA to logic 1 to enter Master mode, the I2C hardware sends a START or repeat START
 * |        |          |condition to bus when the bus is free.
 * |[6]     |ENS1      |I2C Controller Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |        |          |Set to enable I2C serial function controller.
 * |        |          |When ENS1=1 the I2C serial function enables.
 * |        |          |The multi-function pin function of I2Cn_SDA and I2Cn_SCL must set to I2C function first.
 * |[7]     |EI        |Enable Interrupt
 * |        |          |0 = I2C interrupt Disabled.
 * |        |          |1 = I2C interrupt Enabled.
 * @var I2C_T::I2CADDR0
 * Offset: 0x04  I2C Slave Address Register0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GC        |General Call Function
 * |        |          |0 = General Call Function Disabled.
 * |        |          |1 = General Call Function Enabled.
 * |[7:1]   |I2CADDR   |I2C Address Register
 * |        |          |The content of this register is irrelevant when I2C is in Master mode.
 * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own
 * |        |          |address.
 * |        |          |The I2C hardware will react if either of the address is matched.
 * @var I2C_T::I2CDAT
 * Offset: 0x08  I2C Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |I2CDAT    |I2C Data Register
 * |        |          |Bit [7:0] is located with the 8-bit transferred data of I2C serial port.
 * @var I2C_T::I2CSTATUS
 * Offset: 0x0C  I2C Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |I2CSTATUS |I2C Status Register
 * |        |          |The status register of I2C:
 * |        |          |The three least significant bits are always 0.
 * |        |          |The five most significant bits contain the status code.
 * |        |          |There are 26 possible status codes.
 * |        |          |When I2CSTATUS contains F8H, no serial interrupt is requested.
 * |        |          |All other I2CSTATUS values correspond to defined I2C states.
 * |        |          |When each of these states is entered, a status interrupt is requested (SI = 1).
 * |        |          |A valid status code is present in I2CSTATUS one cycle after SI is set by hardware and is
 * |        |          |still present one cycle after SI has been reset by software.
 * |        |          |In addition, states 00H stands for a Bus Error.
 * |        |          |A Bus Error occurs when a START or STOP condition is present at an illegal position in the
 * |        |          |formation frame.
 * |        |          |Example of illegal position are during the serial transfer of an address byte, a data byte
 * |        |          |or an acknowledge bit.
 * @var I2C_T::I2CLK
 * Offset: 0x10  I2C Clock Divided Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |I2CLK     |I2C clock divided Register
 * |        |          |The I2C clock rate bits: Data Baud Rate of I2C = (system clock) / (4x (I2CLK+1)).
 * |        |          |Note: The minimum value of I2CLK is 4.
 * @var I2C_T::I2CTOC
 * Offset: 0x14  I2C Time-out Counter Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TIF       |Time-out Flag
 * |        |          |This bit is set by H/W when I2C time-out happened and it can interrupt CPU if I2C interrupt
 * |        |          |enable bit (EI) is set to 1.
 * |        |          |Note: Write 1 to clear this bit.
 * |[1]     |DIV4      |Time-out Counter Input Clock Divided by 4
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |        |          |When Enabled, The time-out period is extend 4 times.
 * |[2]     |ENTI      |Time-out Counter Enable/Disable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |        |          |When Enabled, the 14-bit time-out counter will start counting when SI is clear.
 * |        |          |Setting flag SI to high will reset counter and re-start up counting after SI is cleared.
 * @var I2C_T::I2CADDR1
 * Offset: 0x18  I2C Slave Address Register1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GC        |General Call Function
 * |        |          |0 = General Call Function Disabled.
 * |        |          |1 = General Call Function Enabled.
 * |[7:1]   |I2CADDR   |I2C Address Register
 * |        |          |The content of this register is irrelevant when I2C is in Master mode.
 * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own
 * |        |          |address.
 * |        |          |The I2C hardware will react if either of the address is matched.
 * @var I2C_T::I2CADDR2
 * Offset: 0x1C  I2C Slave Address Register2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GC        |General Call Function
 * |        |          |0 = General Call Function Disabled.
 * |        |          |1 = General Call Function Enabled.
 * |[7:1]   |I2CADDR   |I2C Address Register
 * |        |          |The content of this register is irrelevant when I2C is in Master mode.
 * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own
 * |        |          |address.
 * |        |          |The I2C hardware will react if either of the address is matched.
 * @var I2C_T::I2CADDR3
 * Offset: 0x20  I2C Slave Address Register3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GC        |General Call Function
 * |        |          |0 = General Call Function Disabled.
 * |        |          |1 = General Call Function Enabled.
 * |[7:1]   |I2CADDR   |I2C Address Register
 * |        |          |The content of this register is irrelevant when I2C is in Master mode.
 * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own
 * |        |          |address.
 * |        |          |The I2C hardware will react if either of the address is matched.
 * @var I2C_T::I2CADM0
 * Offset: 0x24  I2C Slave Address Mask Register0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:1]   |I2CADM    |I2C Address Mask Register
 * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as
 * |        |          |address register.).
 * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
 * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
 * |        |          |When the bit in the address mask register is set to one, it means the received corresponding
 * |        |          |address bit is don't-care.
 * |        |          |If the bit is set to zero, that means the received corresponding register bit should be
 * |        |          |exact the same as address register.
 * @var I2C_T::I2CADM1
 * Offset: 0x28  I2C Slave Address Mask Register1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:1]   |I2CADM    |I2C Address Mask Register
 * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as
 * |        |          |address register.).
 * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
 * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
 * |        |          |When the bit in the address mask register is set to one, it means the received corresponding
 * |        |          |address bit is don't-care.
 * |        |          |If the bit is set to zero, that means the received corresponding register bit should be
 * |        |          |exact the same as address register.
 * @var I2C_T::I2CADM2
 * Offset: 0x2C  I2C Slave Address Mask Register2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:1]   |I2CADM    |I2C Address Mask Register
 * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as
 * |        |          |address register.).
 * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
 * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
 * |        |          |When the bit in the address mask register is set to one, it means the received corresponding
 * |        |          |address bit is don't-care.
 * |        |          |If the bit is set to zero, that means the received corresponding register bit should be
 * |        |          |exact the same as address register.
 * @var I2C_T::I2CADM3
 * Offset: 0x30  I2C Slave Address Mask Register3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:1]   |I2CADM    |I2C Address Mask Register
 * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as
 * |        |          |address register.).
 * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
 * |        |          |I2C bus controllers support multiple address recognition with four address mask register.
 * |        |          |When the bit in the address mask register is set to one, it means the received corresponding
 * |        |          |address bit is don't-care.
 * |        |          |If the bit is set to zero, that means the received corresponding register bit should be
 * |        |          |exact the same as address register.
 * @var I2C_T::I2CWKUPCON
 * Offset: 0x3C  I2C Wake-up Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |WKUPEN    |I2C Wake-up Enable
 * |        |          |0 = I2C wake-up function Disabled.
 * |        |          |1= I2C wake-up function Enabled.
 * @var I2C_T::I2CWKUPSTS
 * Offset: 0x40  I2C Wake-up Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |WKUPIF    |I2C Wake-up Flag
 * |        |          |When chip is woken up from Power-down mode by I2C, this bit is set to 1.
 * |        |          |Software can write 1 to clear this bit.
 */

    __IO uint32_t I2CON;         /* Offset: 0x00  I2C Control Register                                               */
    __IO uint32_t I2CADDR0;      /* Offset: 0x04  I2C Slave Address Register0                                        */
    __IO uint32_t I2CDAT;        /* Offset: 0x08  I2C Data Register                                                  */
    __I  uint32_t I2CSTATUS;     /* Offset: 0x0C  I2C Status Register                                                */
    __IO uint32_t I2CLK;         /* Offset: 0x10  I2C Clock Divided Register                                         */
    __IO uint32_t I2CTOC;        /* Offset: 0x14  I2C Time-out Counter Register                                      */
    __IO uint32_t I2CADDR1;      /* Offset: 0x18  I2C Slave Address Register1                                        */
    __IO uint32_t I2CADDR2;      /* Offset: 0x1C  I2C Slave Address Register2                                        */
    __IO uint32_t I2CADDR3;      /* Offset: 0x20  I2C Slave Address Register3                                        */
    __IO uint32_t I2CADM0;       /* Offset: 0x24  I2C Slave Address Mask Register0                                   */
    __IO uint32_t I2CADM1;       /* Offset: 0x28  I2C Slave Address Mask Register1                                   */
    __IO uint32_t I2CADM2;       /* Offset: 0x2C  I2C Slave Address Mask Register2                                   */
    __IO uint32_t I2CADM3;       /* Offset: 0x30  I2C Slave Address Mask Register3                                   */
    __I  uint32_t RESERVED0[2];
    __IO uint32_t I2CWKUPCON;    /* Offset: 0x3C  I2C Wake-up Control Register                                       */
    __IO uint32_t I2CWKUPSTS;    /* Offset: 0x40  I2C Wake-up Status Register                                        */

} I2C_T;




/**
    @addtogroup I2C_CONST I2C Bit Field Definition
    Constant Definitions for I2C Controller
@{ */

/* I2C I2CON Bit Field Definitions */
#define I2C_I2CON_EI_Pos                        7                                       /*!< I2C_T::I2CON: EI Position */
#define I2C_I2CON_EI_Msk                        (1ul << I2C_I2CON_EI_Pos)               /*!< I2C_T::I2CON: EI Mask */

#define I2C_I2CON_ENS1_Pos                      6                                       /*!< I2C_T::I2CON: ENS1 Position */
#define I2C_I2CON_ENS1_Msk                      (1ul << I2C_I2CON_ENS1_Pos)             /*!< I2C_T::I2CON: ENS1 Mask */

#define I2C_I2CON_STA_Pos                       5                                       /*!< I2C_T::I2CON: STA Position */
#define I2C_I2CON_STA_Msk                       (1ul << I2C_I2CON_STA_Pos)              /*!< I2C_T::I2CON: STA Mask */

#define I2C_I2CON_STO_Pos                       4                                       /*!< I2C_T::I2CON: STO Position */
#define I2C_I2CON_STO_Msk                       (1ul << I2C_I2CON_STO_Pos)              /*!< I2C_T::I2CON: STO Mask */

#define I2C_I2CON_SI_Pos                        3                                       /*!< I2C_T::I2CON: SI Position */
#define I2C_I2CON_SI_Msk                        (1ul << I2C_I2CON_SI_Pos)               /*!< I2C_T::I2CON: SI Mask */

#define I2C_I2CON_AA_Pos                        2                                       /*!< I2C_T::I2CON: AA Position */
#define I2C_I2CON_AA_Msk                        (1ul << I2C_I2CON_AA_Pos)               /*!< I2C_T::I2CON: AA Mask */

/* I2C I2CADDR Bit Field Definitions */
#define I2C_I2CADDR_I2CADDR_Pos                 1                                       /*!< I2C_T::I2CADDR1: I2CADDR Position */
#define I2C_I2CADDR_I2CADDR_Msk                 (0x7Ful << I2C_I2CADDR_I2CADDR_Pos)     /*!< I2C_T::I2CADDR1: I2CADDR Mask */

#define I2C_I2CADDR_GC_Pos                      0                                       /*!< I2C_T::I2CADDR1: GC Position */
#define I2C_I2CADDR_GC_Msk                      (1ul << I2C_I2CADDR_GC_Pos)             /*!< I2C_T::I2CADDR1: GC Mask */

/* I2C I2CDAT Bit Field Definitions */
#define I2C_I2CDAT_I2CDAT_Pos                   0                                       /*!< I2C_T::I2CDAT: I2CDAT Position */
#define I2C_I2CDAT_I2CDAT_Msk                   (0xFFul << I2C_I2CDAT_I2CDAT_Pos)       /*!< I2C_T::I2CDAT: I2CDAT Mask */

/* I2C I2CSTATUS Bit Field Definitions */
#define I2C_I2CSTATUS_I2CSTATUS_Pos             0                                       /*!< I2C_T::I2CSTATUS: I2CSTATUS Position */
#define I2C_I2CSTATUS_I2CSTATUS_Msk             (0xFFul << I2C_I2CSTATUS_I2CSTATUS_Pos) /*!< I2C_T::I2CSTATUS: I2CSTATUS Mask */

/* I2C I2CLK Bit Field Definitions */
#define I2C_I2CLK_I2CLK_Pos                     0                                       /*!< I2C_T::I2CLK: I2CLK Position */
#define I2C_I2CLK_I2CLK_Msk                     (0xFFul << I2C_I2CLK_I2CLK_Pos)         /*!< I2C_T::I2CLK: I2CLK Mask */

/* I2C I2CTOC Bit Field Definitions */
#define I2C_I2CTOC_ENTI_Pos                     2                                       /*!< I2C_T::I2CTOC: ENTI Position */
#define I2C_I2CTOC_ENTI_Msk                     (1ul << I2C_I2CTOC_ENTI_Pos)            /*!< I2C_T::I2CTOC: ENTI Mask */

#define I2C_I2CTOC_DIV4_Pos                     1                                       /*!< I2C_T::I2CTOC: DIV4 Position */
#define I2C_I2CTOC_DIV4_Msk                     (1ul << I2C_I2CTOC_DIV4_Pos)            /*!< I2C_T::I2CTOC: DIV4 Mask */

#define I2C_I2CTOC_TIF_Pos                      0                                       /*!< I2C_T::I2CTOC: TIF Position */
#define I2C_I2CTOC_TIF_Msk                      (1ul << I2C_I2CTOC_TIF_Pos)             /*!< I2C_T::I2CTOC: TIF Mask */

/* I2C I2CADM Bit Field Definitions */
#define I2C_I2CADM_I2CADM_Pos                   1                                       /*!< I2C_T::I2CADM0: I2CADM Position */
#define I2C_I2CADM_I2CADM_Msk                   (0x7Ful << I2C_I2CADM_I2CADM_Pos)       /*!< I2C_T::I2CADM0: I2CADM Mask */

/* I2C I2CWKUPCON Bit Field Definitions */
#define I2C_I2CWKUPCON_WKUPEN_Pos               0                                       /*!< I2C_T::I2CWKUPCON: WKUPEN Position */
#define I2C_I2CWKUPCON_WKUPEN_Msk               (1ul << I2C_I2CWKUPCON_WKUPEN_Pos)      /*!< I2C_T::I2CWKUPCON: WKUPEN Mask */

/* I2C I2CWKUPSTS Bit Field Definitions */
#define I2C_I2CWKUPSTS_WKUPIF_Pos               0                                       /*!< I2C_T::I2CWKUPSTS: WKUPIF Position */
#define I2C_I2CWKUPSTS_WKUPIF_Msk               (1ul << I2C_I2CWKUPSTS_WKUPIF_Pos)      /*!< I2C_T::I2CWKUPSTS: WKUPIF Mask */

/*@}*/ /* end of group I2C_CONST */
/*@}*/ /* end of group I2C */



/*----------------------------- I2S Controller -------------------------------*/
/** @addtogroup I2S Integrated Inter-chip Sound(I2S)
  Memory Mapped Structure for I2S Interface Controller
  @{
 */


typedef struct
{


/**
 * @var I2S_T::CON
 * Offset: 0x00  I2S Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |I2SEN     |I2S Controller Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[1]     |TXEN      |Transmit Enable
 * |        |          |0 = Data transmit Disabled.
 * |        |          |1 = Data transmit Enabled.
 * |[2]     |RXEN      |Receive Enable
 * |        |          |0 = Data receiving Disabled.
 * |        |          |1 = Data receiving Enabled.
 * |[3]     |MUTE      |Transmit Mute Enable
 * |        |          |0 = Transmit data is shifted from buffer.
 * |        |          |1 = Send zero on transmit channel.
 * |[5:4]   |WORDWIDTH |Word Width
 * |        |          |00 = data is 8-bit word.
 * |        |          |01 = data is 16-bit word.
 * |        |          |10 = data is 24-bit word.
 * |        |          |11 = data is 32-bit word.
 * |[6]     |MONO      |Monaural Data
 * |        |          |0 = Data is stereo format.
 * |        |          |1 = Data is monaural format.
 * |[7]     |FORMAT    |Data Format
 * |        |          |0 = I2S data format.
 * |        |          |1 = MSB justified data format.
 * |[8]     |SLAVE     |Slave Mode
 * |        |          |I2S can operate as master or slave.
 * |        |          |For Master mode, I2S_BCLK and I2S_LRCLK pins are output mode and send bit clock from MCU to
 * |        |          |Audio CODEC chip.
 * |        |          |In Slave mode, I2S_BCLK and I2S_LRCLK pins are input mode and I2S_BCLK and I2S_LRCLK signals
 * |        |          |are received from outer Audio CODEC chip.
 * |        |          |0 = Master mode.
 * |        |          |1 = Slave mode.
 * |[11:9]  |TXTH      |Transmit FIFO Threshold Level
 * |        |          |If the count of remaining data word (32 bits) in transmit FIFO is equal to or less than
 * |        |          |threshold level then TXTHF (I2SSTATUS[18]) is set.
 * |        |          |000 = 0 word data in transmit FIFO.
 * |        |          |001 = 1 word data in transmit FIFO.
 * |        |          |010 = 2 words data in transmit FIFO.
 * |        |          |011 = 3 words data in transmit FIFO.
 * |        |          |100 = 4 words data in transmit FIFO.
 * |        |          |101 = 5 words data in transmit FIFO.
 * |        |          |110 = 6 words data in transmit FIFO.
 * |        |          |111 = 7 words data in transmit FIFO.
 * |[14:12] |RXTH      |Receive FIFO Threshold Level
 * |        |          |When the count of received data word(s) in buffer is equal to or higher than threshold
 * |        |          |level, RXTHF (I2SSTATUS[10]) will be set.
 * |        |          |000 = 1 word data in receive FIFO.
 * |        |          |001 = 2 word data in receive FIFO.
 * |        |          |010 = 3 word data in receive FIFO.
 * |        |          |011 = 4 word data in receive FIFO.
 * |        |          |100 = 5 word data in receive FIFO.
 * |        |          |101 = 6 word data in receive FIFO.
 * |        |          |110 = 7 word data in receive FIFO.
 * |        |          |111 = 8 word data in receive FIFO.
 * |[15]    |MCLKEN    |Master Clock Enable
 * |        |          |If MCLKEN is set to 1, I2S controller will generate master clock on I2S_MCLK pin for
 * |        |          |external audio devices.
 * |        |          |0 = Master clock Disabled.
 * |        |          |1 = Master clock Enabled.
 * |[16]    |RCHZCEN   |Right Channel Zero Cross Detection Enable
 * |        |          |If this bit is set to 1, when right channel data sign bit change or next shift data bits are
 * |        |          |all 0 then RZCF flag in I2SSTATUS register is set to 1.
 * |        |          |This function is only available in transmit operation.
 * |        |          |0 = Right channel zero cross detection Disabled.
 * |        |          |1 = Right channel zero cross detection Enabled.
 * |[17]    |LCHZCEN   |Left Channel Zero Cross Detection Enable
 * |        |          |If this bit is set to 1, when left channel data sign bit changes or next shift data bits are
 * |        |          |all 0 then LZCF flag in I2SSTATUS register is set to 1.
 * |        |          |This function is only available in transmit operation.
 * |        |          |0 = Left channel zero cross detection Disabled.
 * |        |          |1 = Left channel zero cross detection Enabled.
 * |[18]    |CLR_TXFIFO|Clear Transmit FIFO
 * |        |          |Write 1 to clear transmit FIFO, internal pointer is reset to FIFO start point, and
 * |        |          |TX_LEVEL[3:0] returns to 0 and
 * |        |          |transmit FIFO becomes empty but data in transmit FIFO is not changed.
 * |        |          |This bit is cleared by hardware automatically. Returns 0 on read.
 * |[19]    |CLR_RXFIFO|Clear Receive FIFO
 * |        |          |Write 1 to clear receive FIFO, internal pointer is reset to FIFO start point, and
 * |        |          |RX_LEVEL[3:0] returns 0 and receive FIFO becomes empty.
 * |        |          |This bit is cleared by hardware automatically. Returns 0 on read.
 * |[20]    |TXDMA     |Enable Transmit DMA
 * |        |          |When TX DMA is enabled, I2S request DMA to transfer data from SRAM to transmit FIFO if FIFO
 * |        |          |is not full.
 * |        |          |0 = TX DMA Disabled.
 * |        |          |1 = TX DMA Enabled.
 * |[21]    |RXDMA     |Enable Receive DMA
 * |        |          |When RX DMA is enabled, I2S requests DMA to transfer data from receive FIFO to SRAM if FIFO
 * |        |          |is not empty.
 * |        |          |0 = RX DMA Disabled.
 * |        |          |1 = RX DMA Enabled.
 * |[23]    |RXLCH     |Receive Left Channel Enable
 * |        |          |When monaural format is selected (MONO = 1), I2S controller will receive right channel data
 * |        |          |if RXLCH is set to 0,
 * |        |          |and receive left channel data if RXLCH is set to 1.
 * |        |          |0 = Receive right channel data in Mono mode.
 * |        |          |1 = Receive left channel data in Mono mode.
 * @var I2S_T::CLKDIV
 * Offset: 0x04  I2S Clock Divider Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[2:0]   |MCLK_DIV  |Master Clock Divider
 * |        |          |If MCLKEN is set to 1, I2S controller will generate master clock for external audio devices.
 * |        |          |The master clock rate, F_MCLK, is determined by the following expressions.
 * |        |          |If MCLK_DIV >= 1, F_MCLK = F_I2SCLK/(2x(MCLK_DIV)).
 * |        |          |If MCLK_DIV = 0, F_MCLK = F_I2SCLK.
 * |        |          |F_I2SCLK is the frequency of I2S peripheral clock.
 * |        |          |In general, the master clock rate is 256 times sampling clock rate.
 * |[15:8]  |BCLK_DIV  |Bit Clock Divider
 * |        |          |The I2S controller will generate bit clock in Master mode.
 * |        |          |The bit clock rate, F_BCLK, is determined by the following expression.
 * |        |          |F_BCLK = F_I2SCLK /(2x(BCLK_DIV + 1)) , where F_I2SCLK is the frequency of I2S peripheral
 * |        |          |clock.
 * @var I2S_T::IE
 * Offset: 0x08  I2S Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RXUDFIE   |Receive FIFO Underflow Interrupt Enable
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[1]     |RXOVFIE   |Receive FIFO Overflow Interrupt Enable
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[2]     |RXTHIE    |Receive FIFO Threshold Level Interrupt Enable
 * |        |          |When the count of data words in receive FIFO is equal to or higher than RXTH (I2SCON[14:12])
 * |        |          |and
 * |        |          |this bit is set to 1, receive FIFO threshold level interrupt will be asserted.
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[8]     |TXUDFIE   |Transmit FIFO Underflow Interrupt Enable
 * |        |          |Interrupt occurs if this bit is set to 1 and the transmit FIFO underflow flag is set to 1.
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[9]     |TXOVFIE   |Transmit FIFO Overflow Interrupt Enable
 * |        |          |Interrupt occurs if this bit is set to 1 and the transmit FIFO overflow flag is set to 1
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[10]    |TXTHIE    |Transmit FIFO Threshold Level Interrupt Enable
 * |        |          |Interrupt occurs if this bit is set to 1 and the count of data words in transmit FIFO is
 * |        |          |less than TXTH (I2SCON[11:9]).
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[11]    |RZCIE     |Right Channel Zero-Cross Interrupt Enable
 * |        |          |Interrupt occurs if this bit is set to 1 and right channel zero-cross event is detected.
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * |[12]    |LZCIE     |Left Channel Zero-Cross Interrupt Enable
 * |        |          |Interrupt occurs if this bit is set to 1 and left channel zero-cross event is detected.
 * |        |          |0 = Interrupt Disabled.
 * |        |          |1 = Interrupt Enabled.
 * @var I2S_T::STATUS
 * Offset: 0x0C  I2S Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |I2SINT    |I2S Interrupt Flag
 * |        |          |This bit is wire-OR of I2STXINT and I2SRXINT bits.
 * |        |          |0 = No I2S interrupt.
 * |        |          |1 = I2S interrupt.
 * |        |          |Note: This bit is read only.
 * |[1]     |I2SRXINT  |I2S Receive Interrupt
 * |        |          |0 = No receive interrupt.
 * |        |          |1 = Receive interrupt.
 * |        |          |Note: This bit is read only.
 * |[2]     |I2STXINT  |I2S Transmit Interrupt
 * |        |          |0 = No transmit interrupt.
 * |        |          |1 = Transmit interrupt.
 * |        |          |Note: This bit is read only.
 * |[3]     |RIGHT     |Right Channel
 * |        |          |This bit indicates current transmit data is belong to which channel
 * |        |          |0 = Left channel.
 * |        |          |1 = Right channel.
 * |        |          |Note: This bit is read only.
 * |[8]     |RXUDF     |Receive FIFO Underflow Flag
 * |        |          |Underflow event will occur if read the empty receive FIFO.
 * |        |          |0 = No underflow event occurred.
 * |        |          |1 = Underflow.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[9]     |RXOVF     |Receive FIFO Overflow Flag
 * |        |          |When receive FIFO is full and hardware attempt to write data to receive FIFO, this bit will
 * |        |          |be set to 1, data in 1st buffer will be overwrote.
 * |        |          |0 = No overflow.
 * |        |          |1 = Overflow.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[10]    |RXTHF     |Receive FIFO Threshold Flag
 * |        |          |When data word(s) in receive FIFO is equal to or larger than threshold value set in RXTH
 * |        |          |(I2SCON[14:12]).
 * |        |          |The RXTHF bit becomes to 1.
 * |        |          |It keeps at 1 till RX_LEVEL (I2SSTATUS[27:24]) is less than RXTH.
 * |        |          |0 = Data word(s) in FIFO is less than threshold level.
 * |        |          |1 = Data word(s) in FIFO is equal to or larger than threshold level.
 * |        |          |Note: This bit is read only.
 * |[11]    |RXFULL    |Receive FIFO Full
 * |        |          |This bit reflects the count of data in receive FIFO is 8
 * |        |          |0 = Not full.
 * |        |          |1 = Full.
 * |        |          |Note: This bit is read only.
 * |[12]    |RXEMPTY   |Receive FIFO Empty
 * |        |          |This bit reflects the count of data in receive FIFO is 0
 * |        |          |0 = Not empty.
 * |        |          |1 = Empty.
 * |        |          |Note: This bit is read only.
 * |[16]    |TXUDF     |Transmit FIFO Underflow Flag
 * |        |          |If transmit FIFO is empty and hardware reads data from transmit FIFO. This bit will be set
 * |        |          |to 1.
 * |        |          |0 = No underflow.
 * |        |          |1 = Underflow.
 * |        |          |Note: Software can write 1 to clear this bit to 0.
 * |[17]    |TXOVF     |Transmit FIFO Overflow Flag
 * |        |          |This bit will be set to 1 if writes data to transmit FIFO when transmit FIFO is full.
 * |        |          |0 = No overflow.
 * |        |          |1 = Overflow.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[18]    |TXTHF     |Transmit FIFO Threshold Flag
 * |        |          |When the count of data stored in transmit-FIFO is equal to or less than threshold value set
 * |        |          |in TXTH (I2SCON[11:9]).
 * |        |          |The TXTHF bit becomes to 1.
 * |        |          |It keeps at 1 till TX_LEVEL (I2SSTATUS[31:28]) is larger than TXTH.
 * |        |          |0 = Data word(s) in FIFO is larger than threshold level.
 * |        |          |1 = Data word(s) in FIFO is equal to or less than threshold level.
 * |        |          |Note: This bit is read only.
 * |[19]    |TXFULL    |Transmit FIFO Full
 * |        |          |This bit reflects data word number in transmit FIFO is 8
 * |        |          |0 = Not full.
 * |        |          |1 = Full.
 * |        |          |Note: This bit is read only.
 * |[20]    |TXEMPTY   |Transmit FIFO Empty
 * |        |          |This bit reflects data word number in transmit FIFO is 0
 * |        |          |0 = Not empty.
 * |        |          |1 = Empty.
 * |        |          |Note: This bit is read only.
 * |[21]    |TXBUSY    |Transmit Busy
 * |        |          |This bit is cleared to 0 when all data in transmit FIFO and shift buffer is shifted out.
 * |        |          |And set to 1 when 1st data is load to shift buffer.
 * |        |          |0 = Transmit shift buffer is empty.
 * |        |          |1 = Transmit shift buffer is not empty.
 * |        |          |Note: This bit is read only.
 * |[22]    |RZCF      |Right Channel Zero-Cross Flag
 * |        |          |It indicates the sign bit of right channel sample data is changed or all data bits are 0.
 * |        |          |0 = No zero-cross.
 * |        |          |1 = Right channel zero-cross event is detected.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[23]    |LZCF      |Left Channel Zero-Cross Flag
 * |        |          |It indicates the sign bit of left channel sample data is changed or all data bits are 0.
 * |        |          |0 = No zero-cross.
 * |        |          |1 = Left channel zero-cross event is detected.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[27:24] |RX_LEVEL  |Receive FIFO Level
 * |        |          |These bits indicate word number in receive FIFO
 * |        |          |0000 = No data.
 * |        |          |0001 = 1 word in receive FIFO.
 * |        |          |....
 * |        |          |1000 = 8 words in receive FIFO.
 * |[31:28] |TX_LEVEL  |Transmit FIFO Level
 * |        |          |These bits indicate word number in transmit FIFO
 * |        |          |0000 = No data.
 * |        |          |0001 = 1 word in transmit FIFO.
 * |        |          |....
 * |        |          |1000 = 8 words in transmit FIFO.
 * @var I2S_T::TXFIFO
 * Offset: 0x10  I2S Transmit FIFO Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |TXFIFO    |Transmit FIFO Register
 * |        |          |I2S contains 8 words (8x32 bits) data buffer for data transmit.
 * |        |          |Write data to this register to prepare data for transmission.
 * |        |          |The remaining word number is indicated by TX_LEVEL (I2SSTATUS[31:28]).
 * @var I2S_T::RXFIFO
 * Offset: 0x14  I2S Receive FIFO Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |RXFIFO    |Receive FIFO Register
 * |        |          |I2S contains 8 words (8x32 bits) data buffer for data receive.
 * |        |          |Read this register to get data of receive FIFO.
 * |        |          |The remaining data word number is indicated by RX_LEVEL (I2SSTATUS[27:24]).
 */

    __IO uint32_t CON;           /* Offset: 0x00  I2S Control Register                                               */
    __IO uint32_t CLKDIV;        /* Offset: 0x04  I2S Clock Divider Control Register                                 */
    __IO uint32_t IE;            /* Offset: 0x08  I2S Interrupt Enable Register                                      */
    __IO uint32_t STATUS;        /* Offset: 0x0C  I2S Status Register                                                */
    __O  uint32_t TXFIFO;        /* Offset: 0x10  I2S Transmit FIFO Register                                         */
    __I  uint32_t RXFIFO;        /* Offset: 0x14  I2S Receive FIFO Register                                          */

} I2S_T;




/**
    @addtogroup I2S_CONST I2S Bit Field Definition
    Constant Definitions for I2S Controller
@{ */

/* I2S I2SCON Bit Field Definitions */
#define I2S_CON_RXLCH_Pos                    23                                   /*!< I2S_T::CON: RXLCH Position         */
#define I2S_CON_RXLCH_Msk                    (1ul << I2S_CON_RXLCH_Pos)           /*!< I2S_T::CON: RXLCH Mask             */

#define I2S_CON_RXDMA_Pos                    21                                   /*!< I2S_T::CON: RXDMA Position         */
#define I2S_CON_RXDMA_Msk                    (1ul << I2S_CON_RXDMA_Pos)           /*!< I2S_T::CON: RXDMA Mask             */

#define I2S_CON_TXDMA_Pos                    20                                   /*!< I2S_T::CON: TXDMA Position         */
#define I2S_CON_TXDMA_Msk                    (1ul << I2S_CON_TXDMA_Pos)           /*!< I2S_T::CON: TXDMA Mask             */

#define I2S_CON_CLR_RXFIFO_Pos               19                                   /*!< I2S_T::CON: CLR_RXFIFO Position    */
#define I2S_CON_CLR_RXFIFO_Msk               (1ul << I2S_CON_CLR_RXFIFO_Pos)      /*!< I2S_T::CON: CLR_RXFIFO Mask        */

#define I2S_CON_CLR_TXFIFO_Pos               18                                   /*!< I2S_T::CON: CLR_TXFIFO Position    */
#define I2S_CON_CLR_TXFIFO_Msk               (1ul << I2S_CON_CLR_TXFIFO_Pos)      /*!< I2S_T::CON: CLR_TXFIFO Mask        */

#define I2S_CON_LCHZCEN_Pos                  17                                   /*!< I2S_T::CON: LCHZCEN Position       */
#define I2S_CON_LCHZCEN_Msk                  (1ul << I2S_CON_LCHZCEN_Pos)         /*!< I2S_T::CON: LCHZCEN Mask           */

#define I2S_CON_RCHZCEN_Pos                  16                                   /*!< I2S_T::CON: RCHZCEN Position       */
#define I2S_CON_RCHZCEN_Msk                  (1ul << I2S_CON_RCHZCEN_Pos)         /*!< I2S_T::CON: RCHZCEN Mask           */

#define I2S_CON_MCLKEN_Pos                   15                                   /*!< I2S_T::CON: MCLKEN Position        */
#define I2S_CON_MCLKEN_Msk                   (1ul << I2S_CON_MCLKEN_Pos)          /*!< I2S_T::CON: MCLKEN Mask            */

#define I2S_CON_RXTH_Pos                     12                                   /*!< I2S_T::CON: RXTH Position          */
#define I2S_CON_RXTH_Msk                     (7ul << I2S_CON_RXTH_Pos)            /*!< I2S_T::CON: RXTH Mask              */

#define I2S_CON_TXTH_Pos                     9                                    /*!< I2S_T::CON: TXTH Position          */
#define I2S_CON_TXTH_Msk                     (7ul << I2S_CON_TXTH_Pos)            /*!< I2S_T::CON: TXTH Mask              */

#define I2S_CON_SLAVE_Pos                    8                                    /*!< I2S_T::CON: SLAVE Position         */
#define I2S_CON_SLAVE_Msk                    (1ul << I2S_CON_SLAVE_Pos)           /*!< I2S_T::CON: SLAVE Mask             */

#define I2S_CON_FORMAT_Pos                   7                                    /*!< I2S_T::CON: FORMAT Position        */
#define I2S_CON_FORMAT_Msk                   (1ul << I2S_CON_FORMAT_Pos)          /*!< I2S_T::CON: FORMAT Mask            */

#define I2S_CON_MONO_Pos                     6                                    /*!< I2S_T::CON: MONO Position          */
#define I2S_CON_MONO_Msk                     (1ul << I2S_CON_MONO_Pos)            /*!< I2S_T::CON: MONO Mask              */

#define I2S_CON_WORDWIDTH_Pos                4                                    /*!< I2S_T::CON: WORDWIDTH Position     */
#define I2S_CON_WORDWIDTH_Msk                (3ul << I2S_CON_WORDWIDTH_Pos)       /*!< I2S_T::CON: WORDWIDTH Mask         */

#define I2S_CON_MUTE_Pos                     3                                    /*!< I2S_T::CON: MUTE Position          */
#define I2S_CON_MUTE_Msk                     (1ul << I2S_CON_MUTE_Pos)            /*!< I2S_T::CON: MUTE Mask              */

#define I2S_CON_RXEN_Pos                     2                                    /*!< I2S_T::CON: RXEN Position          */
#define I2S_CON_RXEN_Msk                     (1ul << I2S_CON_RXEN_Pos)            /*!< I2S_T::CON: RXEN Mask              */

#define I2S_CON_TXEN_Pos                     1                                    /*!< I2S_T::CON: TXEN Position          */
#define I2S_CON_TXEN_Msk                     (1ul << I2S_CON_TXEN_Pos)            /*!< I2S_T::CON: TXEN Mask              */

#define I2S_CON_I2SEN_Pos                    0                                    /*!< I2S_T::CON: I2SEN Position         */
#define I2S_CON_I2SEN_Msk                    (1ul << I2S_CON_I2SEN_Pos)           /*!< I2S_T::CON: I2SEN Mask             */

/* I2S I2SCLKDIV Bit Field Definitions */                                                 
#define I2S_CLKDIV_BCLK_DIV_Pos              8                                    /*!< I2S_T::CLKDIV: BCLK_DIV Position   */
#define I2S_CLKDIV_BCLK_DIV_Msk              (0xFFul << I2S_CLKDIV_BCLK_DIV_Pos)  /*!< I2S_T::CLKDIV: BCLK_DIV Mask       */

#define I2S_CLKDIV_MCLK_DIV_Pos              0                                    /*!< I2S_T::CLKDIV: MCLK_DIV Position   */
#define I2S_CLKDIV_MCLK_DIV_Msk              (7ul << I2S_CLKDIV_MCLK_DIV_Pos)     /*!< I2S_T::CLKDIV: MCLK_DIV Mask       */

/* I2S I2SIE Bit Field Definitions */                                                     
#define I2S_IE_LZCIE_Pos                     12                                   /*!< I2S_T::IE: LZCIE Position          */
#define I2S_IE_LZCIE_Msk                     (1ul << I2S_IE_LZCIE_Pos)            /*!< I2S_T::IE: LZCIE Mask              */

#define I2S_IE_RZCIE_Pos                     11                                   /*!< I2S_T::IE: RZCIE Position          */
#define I2S_IE_RZCIE_Msk                     (1ul << I2S_IE_RZCIE_Pos)            /*!< I2S_T::IE: RZCIE Mask              */

#define I2S_IE_TXTHIE_Pos                    10                                   /*!< I2S_T::IE: TXTHIE Position         */
#define I2S_IE_TXTHIE_Msk                    (1ul << I2S_IE_TXTHIE_Pos)           /*!< I2S_T::IE: TXTHIE Mask             */

#define I2S_IE_TXOVFIE_Pos                   9                                    /*!< I2S_T::IE: TXOVFIE Position        */
#define I2S_IE_TXOVFIE_Msk                   (1ul << I2S_IE_TXOVFIE_Pos)          /*!< I2S_T::IE: TXOVFIE Mask            */

#define I2S_IE_TXUDFIE_Pos                   8                                    /*!< I2S_T::IE: TXUDFIE Position        */
#define I2S_IE_TXUDFIE_Msk                   (1ul << I2S_IE_TXUDFIE_Pos)          /*!< I2S_T::IE: TXUDFIE Mask            */

#define I2S_IE_RXTHIE_Pos                    2                                    /*!< I2S_T::IE: RXTHIE Position         */
#define I2S_IE_RXTHIE_Msk                    (1ul << I2S_IE_RXTHIE_Pos)           /*!< I2S_T::IE: RXTHIE Mask             */

#define I2S_IE_RXOVFIE_Pos                   1                                    /*!< I2S_T::IE: RXOVFIE Position        */
#define I2S_IE_RXOVFIE_Msk                   (1ul << I2S_IE_RXOVFIE_Pos)          /*!< I2S_T::IE: RXOVFIE Mask            */

#define I2S_IE_RXUDFIE_Pos                   0                                    /*!< I2S_T::IE: RXUDFIE Position        */
#define I2S_IE_RXUDFIE_Msk                   (1ul << I2S_IE_RXUDFIE_Pos)          /*!< I2S_T::IE: RXUDFIE Mask            */


/* I2S I2SSTATUS Bit Field Definitions */
#define I2S_STATUS_TX_LEVEL_Pos              28                                   /*!< I2S_T::STATUS: TX_LEVEL Position   */
#define I2S_STATUS_TX_LEVEL_Msk              (0xFul << I2S_STATUS_TX_LEVEL_Pos)   /*!< I2S_T::STATUS: TX_LEVEL Mask       */

#define I2S_STATUS_RX_LEVEL_Pos              24                                   /*!< I2S_T::STATUS: RX_LEVEL Position   */
#define I2S_STATUS_RX_LEVEL_Msk              (0xFul << I2S_STATUS_RX_LEVEL_Pos)   /*!< I2S_T::STATUS: RX_LEVEL Mask       */

#define I2S_STATUS_LZCF_Pos                  23                                   /*!< I2S_T::STATUS: LZCF Position       */
#define I2S_STATUS_LZCF_Msk                  (1ul << I2S_STATUS_LZCF_Pos)         /*!< I2S_T::STATUS: LZCF Mask           */

#define I2S_STATUS_RZCF_Pos                  22                                   /*!< I2S_T::STATUS: RZCF Position       */
#define I2S_STATUS_RZCF_Msk                  (1ul << I2S_STATUS_RZCF_Pos)         /*!< I2S_T::STATUS: RZCF Mask           */

#define I2S_STATUS_TXBUSY_Pos                21                                   /*!< I2S_T::STATUS: TXBUSY Position     */
#define I2S_STATUS_TXBUSY_Msk                (1ul << I2S_STATUS_TXBUSY_Pos)       /*!< I2S_T::STATUS: TXBUSY Mask         */

#define I2S_STATUS_TXEMPTY_Pos               20                                   /*!< I2S_T::STATUS: TXEMPTY Position    */
#define I2S_STATUS_TXEMPTY_Msk               (1ul << I2S_STATUS_TXEMPTY_Pos)      /*!< I2S_T::STATUS: TXEMPTY Mask        */

#define I2S_STATUS_TXFULL_Pos                19                                   /*!< I2S_T::STATUS: TXFULL Position     */
#define I2S_STATUS_TXFULL_Msk                (1ul << I2S_STATUS_TXFULL_Pos)       /*!< I2S_T::STATUS: TXFULL Mask         */

#define I2S_STATUS_TXTHF_Pos                 18                                   /*!< I2S_T::STATUS: TXTHF Position      */
#define I2S_STATUS_TXTHF_Msk                 (1ul << I2S_STATUS_TXTHF_Pos)        /*!< I2S_T::STATUS: TXTHF Mask          */

#define I2S_STATUS_TXOVF_Pos                 17                                   /*!< I2S_T::STATUS: TXOVF Position      */
#define I2S_STATUS_TXOVF_Msk                 (1ul << I2S_STATUS_TXOVF_Pos)        /*!< I2S_T::STATUS: TXOVF Mask          */

#define I2S_STATUS_TXUDF_Pos                 16                                   /*!< I2S_T::STATUS: TXUDF Position      */
#define I2S_STATUS_TXUDF_Msk                 (1ul << I2S_STATUS_TXUDF_Pos)        /*!< I2S_T::STATUS: TXUDF Mask          */

#define I2S_STATUS_RXEMPTY_Pos               12                                   /*!< I2S_T::STATUS: RXEMPTY Position    */
#define I2S_STATUS_RXEMPTY_Msk               (1ul << I2S_STATUS_RXEMPTY_Pos)      /*!< I2S_T::STATUS: RXEMPTY Mask        */

#define I2S_STATUS_RXFULL_Pos                11                                   /*!< I2S_T::STATUS: RXFULL Position     */
#define I2S_STATUS_RXFULL_Msk                (1ul << I2S_STATUS_RXFULL_Pos)       /*!< I2S_T::STATUS: RXFULL Mask         */

#define I2S_STATUS_RXTHF_Pos                 10                                   /*!< I2S_T::STATUS: RXTHF Position      */
#define I2S_STATUS_RXTHF_Msk                 (1ul << I2S_STATUS_RXTHF_Pos)        /*!< I2S_T::STATUS: RXTHF Mask          */

#define I2S_STATUS_RXOVF_Pos                 9                                    /*!< I2S_T::STATUS: RXOVF Position      */
#define I2S_STATUS_RXOVF_Msk                 (1ul << I2S_STATUS_RXOVF_Pos)        /*!< I2S_T::STATUS: RXOVF Mask          */

#define I2S_STATUS_RXUDF_Pos                 8                                    /*!< I2S_T::STATUS: RXUDF Position      */
#define I2S_STATUS_RXUDF_Msk                 (1ul << I2S_STATUS_RXUDF_Pos)        /*!< I2S_T::STATUS: RXUDF Mask          */

#define I2S_STATUS_RIGHT_Pos                 3                                    /*!< I2S_T::STATUS: RIGHT Position      */
#define I2S_STATUS_RIGHT_Msk                 (1ul << I2S_STATUS_RIGHT_Pos)        /*!< I2S_T::STATUS: RIGHT Mask          */

#define I2S_STATUS_I2STXINT_Pos              2                                    /*!< I2S_T::STATUS: I2STXINT Position   */
#define I2S_STATUS_I2STXINT_Msk              (1ul << I2S_STATUS_I2STXINT_Pos)     /*!< I2S_T::STATUS: I2STXINT Mask       */

#define I2S_STATUS_I2SRXINT_Pos              1                                    /*!< I2S_T::STATUS: I2SRXINT Position   */
#define I2S_STATUS_I2SRXINT_Msk              (1ul << I2S_STATUS_I2SRXINT_Pos)     /*!< I2S_T::STATUS: I2SRXINT Mask       */

#define I2S_STATUS_I2SINT_Pos                0                                    /*!< I2S_T::STATUS: I2SINT Position     */
#define I2S_STATUS_I2SINT_Msk                (1ul << I2S_STATUS_I2SINT_Pos)       /*!< I2S_T::STATUS: I2SINT Mask         */

/*@}*/ /* end of group I2S_CONST */
/*@}*/ /* end of group I2S */



/*---------------------- Peripheral Direct Memory Access Controller -------------------------*/
/**
    @addtogroup PDMA Peripheral Direct Memory Access Controller (PDMA)
    Memory Mapped Structure for PDMA Controller
@{ */


typedef struct
{


/**
 * @var PDMA_T::CSR
 * Offset: 0x00  PDMA Channel x Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PDMACEN   |PDMA Channel Enable
 * |        |          |Setting this bit to 1 enables PDMA operation.
 * |        |          |If this bit is cleared, PDMA will ignore all PDMA request and force Bus Master into IDLE
 * |        |          |state.
 * |        |          |Note: SW_RST(PDMA_CSRx[1], x= 0~8) will clear this bit.
 * |[1]     |SW_RST    |Software Engine Reset
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the internal state machine, pointers and internal buffer.
 * |        |          |The contents of control register will not be cleared.
 * |        |          |This bit will be automatically cleared after few clock cycles.
 * |[3:2]   |MODE_SEL  |PDMA Mode Selection
 * |        |          |00 = Memory to Memory mode (Memory-to-Memory).
 * |        |          |01 = Peripheral to Memory mode (Peripheral-to-Memory).
 * |        |          |10 = Memory to Peripheral mode (Memory-to-Peripheral).
 * |[5:4]   |SAD_SEL   |Transfer Source Address Direction Selection
 * |        |          |00 = Transfer source address is increasing successively.
 * |        |          |01 = Reserved.
 * |        |          |10 = Transfer source address is fixed (This feature can be used when data where transferred
 * |        |          |from a single source to multiple destinations).
 * |        |          |11 = Reserved.
 * |[7:6]   |DAD_SEL   |Transfer Destination Address Direction Selection
 * |        |          |00 = Transfer destination address is increasing successively.
 * |        |          |01 = Reserved.
 * |        |          |10 = Transfer destination address is fixed.
 * |        |          |(This feature can be used when data where transferred from multiple sources to a single
 * |        |          |destination).
 * |        |          |11 = Reserved.
 * |[20:19] |APB_TWS   |Peripheral Transfer Width Selection
 * |        |          |00 = One word (32-bit) is transferred for every PDMA operation.
 * |        |          |01 = One byte (8-bit) is transferred for every PDMA operation.
 * |        |          |10 = One half-word (16-bit) is transferred for every PDMA operation.
 * |        |          |11 = Reserved.
 * |        |          |Note: This field is meaningful only when MODE_SEL (PDMA_CSRx[3:2]) is Peripheral to Memory
 * |        |          |mode (Peripheral-to-Memory) or Memory to Peripheral mode (Memory-to-Peripheral).
 * |[23]    |TRIG_EN   |Trigger Enable
 * |        |          |0 = No effect.
 * |        |          |1 = PDMA data read or write transfer Enabled.
 * |        |          |Note: When PDMA transfer completed, this bit will be cleared automatically.
 * |        |          |If the bus error occurs, all PDMA transfer will be stopped.
 * |        |          |Software must reset all PDMA channel, and then trigger again.
 * @var PDMA_T::SAR
 * Offset: 0x04  PDMA Channel x Source Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PDMA_SAR  |PDMA Transfer Source Address Register
 * |        |          |This field indicates a 32-bit source address of PDMA.
 * |        |          |Note: The source address must be word alignment.
 * @var PDMA_T::DAR
 * Offset: 0x08  PDMA Channel x Destination Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PDMA_DAR  |PDMA Transfer Destination Address Register
 * |        |          |This field indicates a 32-bit destination address of PDMA.
 * |        |          |Note: The destination address must be word alignment
 * @var PDMA_T::BCR
 * Offset: 0x0C  PDMA Channel x Transfer Byte Count Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |PDMA_BCR  |PDMA Transfer Byte Count Register
 * |        |          |This field indicates a 16-bit transfer byte count number of PDMA; it must be word alignment.
 * @var PDMA_T::POINT
 * Offset: 0x10  PDMA Channel x Internal buffer pointer Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |PDMA_POINT|PDMA Internal Buffer Pointer Register (Read Only)
 * |        |          |This field indicates the internal buffer pointer.
 * @var PDMA_T::CSAR
 * Offset: 0x14  PDMA Channel x Current Source Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PDMA_CSAR |PDMA Current Source Address Register (Read Only)
 * |        |          |This field indicates the source address where the PDMA transfer just occurred.
 * @var PDMA_T::CDAR
 * Offset: 0x18  PDMA Channel x Current Destination Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PDMA_CDAR |PDMA Current Destination Address Register (Read Only)
 * |        |          |This field indicates the destination address where the PDMA transfer just occurred.
 * @var PDMA_T::CBCR
 * Offset: 0x1C  PDMA Channel x Current Transfer Byte Count Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |PDMA_CBCR |PDMA Current Byte Count Register (Read Only)
 * |        |          |This field indicates the current remained byte count of PDMA.
 * |        |          |Note: This field value will be cleared to 0, when software set SW_RST (PDMA_CSRx[1]) to "1".
 * @var PDMA_T::IER
 * Offset: 0x20  PDMA Channel x Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TABORT_IE |PDMA Read/Write Target Abort Interrupt Enable
 * |        |          |0 = Target abort interrupt generation Disabled during PDMA transfer.
 * |        |          |1 = Target abort interrupt generation Enabled during PDMA transfer.
 * |[1]     |BLKD_IE   |PDMA Block Transfer Done Interrupt Enable
 * |        |          |0 = Interrupt generator Disabled when PDMA transfer is done.
 * |        |          |1 = Interrupt generator Enabled when PDMA transfer is done.
 * @var PDMA_T::ISR
 * Offset: 0x24  PDMA Channel x Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TABORT_IF |PDMA Read/Write Target Abort Interrupt Flag
 * |        |          |Write 1 to clear this bit to 0.
 * |        |          |0 = No bus ERROR response received.
 * |        |          |1 = Bus ERROR response received.
 * |        |          |Note: This bit filed indicates bus master received ERROR response or not.
 * |        |          |If bus master received ERROR response, it means that target abort is happened.
 * |        |          |PDMA controller will stop transfer and respond this event to software then goes to IDLE
 * |        |          |state.
 * |        |          |When target abort occurred, software must reset PDMA, and then transfer those data again.
 * |[1]     |BLKD_IF   |PDMA Block Transfer Done Interrupt Flag
 * |        |          |This bit indicates that PDMA has finished all transfers.
 * |        |          |0 = Not finished.
 * |        |          |1 = Done.
 * |        |          |Write 1 to clear this bit to 0.
 * @var PDMA_T::SBUF
 * Offset: 0x80  PDMA Channel x Shared Buffer FIFO x Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PDMA_SBUF0|PDMA Shared Buffer FIFO 0 (Read Only)
 * |        |          |Each channel has its own 1 word internal buffer.
 */

    __IO uint32_t CSR;           /* Offset: 0x00  PDMA Channel x Control Register                                    */
    __IO uint32_t SAR;           /* Offset: 0x04  PDMA Channel x Source Address Register                             */
    __IO uint32_t DAR;           /* Offset: 0x08  PDMA Channel x Destination Address Register                        */
    __IO uint32_t BCR;           /* Offset: 0x0C  PDMA Channel x Transfer Byte Count Register                        */
    __I  uint32_t POINT;         /* Offset: 0x10  PDMA Channel x Internal buffer pointer Register                    */
    __I  uint32_t CSAR;          /* Offset: 0x14  PDMA Channel x Current Source Address Register                     */
    __I  uint32_t CDAR;          /* Offset: 0x18  PDMA Channel x Current Destination Address Register                */
    __I  uint32_t CBCR;          /* Offset: 0x1C  PDMA Channel x Current Transfer Byte Count Register                */
    __IO uint32_t IER;           /* Offset: 0x20  PDMA Channel x Interrupt Enable Register                           */
    __IO uint32_t ISR;           /* Offset: 0x24  PDMA Channel x Interrupt Status Register                           */
    __I  uint32_t RESERVE[22];  
    __I  uint32_t SBUF;          /* Offset: 0x80  PDMA Channel x Shared Buffer FIFO x Register                       */

} PDMA_T;





typedef struct
{


/**
 * @var PDMA_GCR_T::GCRCSR
 * Offset: 0x00  PDMA Global Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8]     |CLK0_EN   |PDMA Controller Channel 0 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[9]     |CLK1_EN   |PDMA Controller Channel 1 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[10]    |CLK2_EN   |PDMA Controller Channel 2 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[11]    |CLK3_EN   |PDMA Controller Channel 3 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[12]    |CLK4_EN   |PDMA Controller Channel 4 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[13]    |CLK5_EN   |PDMA Controller Channel 5 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[14]    |CLK6_EN   |PDMA Controller Channel 6 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[15]    |CLK7_EN   |PDMA Controller Channel 7 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[16]    |CLK8_EN   |PDMA Controller Channel 8 Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[24]    |CRC_CLK_EN|CRC Controller Clock Enable Control
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * @var PDMA_GCR_T::PDSSR0
 * Offset: 0x04  PDMA Service Selection Control Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |SPI0_RXSEL|PDMA SPI0 RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI0 RX.
 * |        |          |Software can change the channel RX setting by this field.
 * |        |          |For example, SPI0_RXSEL (PDMA_PDSSR0[3:0]) = 0110, that means SPI0_RX is connected to
 * |        |          |PDMA_CH6.
 * |        |          |0000: CH0
 * |        |          |0001: CH1
 * |        |          |0010: CH2
 * |        |          |0011: CH3
 * |        |          |0100: CH4
 * |        |          |0101: CH5
 * |        |          |0110: CH6
 * |        |          |0111: CH7
 * |        |          |1000: CH8
 * |        |          |Others : Reserved
 * |[7:4]   |SPI0_TXSEL|PDMA SPI0 TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI0 TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * |[11:8]  |SPI1_RXSEL|PDMA SPI1 RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI1 RX.
 * |        |          |Software can configure the RX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * |[15:12] |SPI1_TXSEL|PDMA SPI1 TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI1 TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * |[19:16] |SPI2_RXSEL|PDMA SPI2 RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI2 RX.
 * |        |          |Software can configure the RX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * |[23:20] |SPI2_TXSEL|PDMA SPI2 TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI2 TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * |[27:24] |SPI3_RXSEL|PDMA SPI3 RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI3 RX.
 * |        |          |Software can configure the RX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * |[31:28] |SPI3_TXSEL|PDMA SPI3 TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral SPI3 TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as SPI0_RXSEL (PDMA_PDSSR0[3:0]) field.
 * |        |          |Please refer to the explanation of SPI0_RXSEL (PDMA_PDSSR0[3:0]).
 * @var PDMA_GCR_T::PDSSR1
 * Offset: 0x08  PDMA Service Selection Control Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |UART0_RXSEL|PDMA UART0 RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral UART0 RX.
 * |        |          |Software can change the channel RX setting by this field.
 * |        |          |For example, UART0_RXSEL (PDMA_PDSSR1[3:0]) = 0110, which means UART0_RX is connected to
 * |        |          |PDMA_CH6.
 * |        |          |0000: CH0
 * |        |          |0001: CH1
 * |        |          |0010: CH2
 * |        |          |0011: CH3
 * |        |          |0100: CH4
 * |        |          |0101: CH5
 * |        |          |0110: CH6
 * |        |          |0111: CH7
 * |        |          |1000: CH8
 * |        |          |Others : Reserved
 * |[7:4]   |UART0_TXSEL|PDMA UART0 TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral UART0 TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as UART0_RXSEL (PDMA_PDSSR1[3:0]) field.
 * |        |          |Please refer to the explanation of UART0_RXSEL (PDMA_PDSSR1[3:0]).
 * |[11:8]  |UART1_RXSEL|PDMA UART1 RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral UART1 RX.
 * |        |          |Software can configure the RX channel setting by this field.
 * |        |          |The channel configuration is the same as UART0_RXSEL (PDMA_PDSSR1[3:0]) field.
 * |        |          |Please refer to the explanation of UART0_RXSEL (PDMA_PDSSR1[3:0]).
 * |[15:12] |UART1_TXSEL|PDMA UART1 TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral UART1 TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as UART0_RXSEL (PDMA_PDSSR1[3:0]) field.
 * |        |          |Please refer to the explanation of UART0_RXSEL (PDMA_PDSSR1[3:0]).
 * |[27:24] |ADC_RXSEL |PDMA ADC RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral ADC RX.
 * |        |          |Software can configure the RX channel setting by this field.
 * |        |          |The channel configuration is the same as UART0_RXSEL (PDMA_PDSSR1[3:0]) field.
 * |        |          |Please refer to the explanation of UART0_RXSEL (PDMA_PDSSR1[3:0]).
 * @var PDMA_GCR_T::GCRISR
 * Offset: 0x0C  PDMA Global Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |INTR0     |Interrupt Status Of Channel 0
 * |        |          |This bit is the interrupt status of PDMA channel0.
 * |        |          |Note: This bit is read only
 * |[1]     |INTR1     |Interrupt Status Of Channel 1
 * |        |          |This bit is the interrupt status of PDMA channel1.
 * |        |          |Note: This bit is read only
 * |[2]     |INTR2     |Interrupt Status Of Channel 2
 * |        |          |This bit is the interrupt status of PDMA channel2.
 * |        |          |Note: This bit is read only
 * |[3]     |INTR3     |Interrupt Status Of Channel 3
 * |        |          |This bit is the interrupt status of PDMA channel3.
 * |        |          |Note: This bit is read only
 * |[4]     |INTR4     |Interrupt Status Of Channel 4
 * |        |          |This bit is the interrupt status of PDMA channel4.
 * |        |          |Note: This bit is read only
 * |[5]     |INTR5     |Interrupt Status Of Channel 5
 * |        |          |This bit is the interrupt status of PDMA channel5.
 * |        |          |Note: This bit is read only
 * |[6]     |INTR6     |Interrupt Status Of Channel 6
 * |        |          |This bit is the interrupt status of PDMA channel6.
 * |        |          |Note: This bit is read only
 * |[7]     |INTR7     |Interrupt Status Of Channel 7
 * |        |          |This bit is the interrupt status of PDMA channel7.
 * |        |          |Note: This bit is read only
 * |[8]     |INTR8     |Interrupt Status Of Channel 8
 * |        |          |This bit is the interrupt status of PDMA channel8.
 * |        |          |Note: This bit is read only
 * |[16]    |INTRCRC   |Interrupt Status Of CRC Controller
 * |        |          |This bit is the interrupt status of CRC controller
 * |        |          |Note: This bit is read only
 * |[31]    |INTR      |Interrupt Status
 * |        |          |This bit is the interrupt status of PDMA controller.
 * |        |          |Note: This bit is read only
 * @var PDMA_GCR_T::PDSSR2
 * Offset: 0x10  PDMA Service Selection Control Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |I2S_RXSEL |PDMA I2S RX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral I2S RX.
 * |        |          |Software can change the channel RX setting by this field.
 * |        |          |For example: I2S_RXSEL (PDMA_PDSSR2[3:0]) = 0110, that means I2S_RX is connected to
 * |        |          |PDMA_CH6.
 * |        |          |0000: CH0
 * |        |          |0001: CH1
 * |        |          |0010: CH2
 * |        |          |0011: CH3
 * |        |          |0100: CH4
 * |        |          |0101: CH5
 * |        |          |0110: CH6
 * |        |          |0111: CH7
 * |        |          |1000: CH8
 * |        |          |Others : Reserved
 * |[7:4]   |I2S_TXSEL |PDMA I2S TX Selection
 * |        |          |This field defines which PDMA channel is connected to the on-chip peripheral I2S TX.
 * |        |          |Software can configure the TX channel setting by this field.
 * |        |          |The channel configuration is the same as I2S_RXSEL (PDMA_PDSSR2[3:0]) field.
 * |        |          |Please refer to the explanation of I2S_RXSEL (PDMA_PDSSR2[3:0]).
 */

    __IO uint32_t GCRCSR;        /* Offset: 0x00  PDMA Global Control Register                                       */
    __IO uint32_t PDSSR0;        /* Offset: 0x04  PDMA Service Selection Control Register 0                          */
    __IO uint32_t PDSSR1;        /* Offset: 0x08  PDMA Service Selection Control Register 1                          */
    __IO uint32_t GCRISR;        /* Offset: 0x0C  PDMA Global Interrupt Status Register                              */
    __IO uint32_t PDSSR2;        /* Offset: 0x10  PDMA Service Selection Control Register 2                          */

} PDMA_GCR_T;



/**
    @addtogroup PDMA_CONST PDMA Bit Field Definition
    Constant Definitions for PDMA Controller
@{ */


/* PDMA CSR Bit Field Definitions */
#define PDMA_CSR_TRIG_EN_Pos                        23                              /*!< PDMA_T::CSR: TRIG_EN Position */
#define PDMA_CSR_TRIG_EN_Msk                        (1ul << PDMA_CSR_TRIG_EN_Pos)   /*!< PDMA_T::CSR: TRIG_EN Mask */

#define PDMA_CSR_APB_TWS_Pos                        19                              /*!< PDMA_T::CSR: APB_TWS Position */
#define PDMA_CSR_APB_TWS_Msk                        (3ul << PDMA_CSR_APB_TWS_Pos)   /*!< PDMA_T::CSR: APB_TWS Mask */

#define PDMA_CSR_DAD_SEL_Pos                        6                               /*!< PDMA_T::CSR: DAD_SEL Position */
#define PDMA_CSR_DAD_SEL_Msk                        (3ul << PDMA_CSR_DAD_SEL_Pos)   /*!< PDMA_T::CSR: DAD_SEL Mask */

#define PDMA_CSR_SAD_SEL_Pos                        4                               /*!< PDMA_T::CSR: SAD_SEL Position */
#define PDMA_CSR_SAD_SEL_Msk                        (3ul << PDMA_CSR_SAD_SEL_Pos)   /*!< PDMA_T::CSR: SAD_SEL Mask */

#define PDMA_CSR_MODE_SEL_Pos                       2                               /*!< PDMA_T::CSR: MODE_SEL Position */
#define PDMA_CSR_MODE_SEL_Msk                       (3ul << PDMA_CSR_MODE_SEL_Pos)  /*!< PDMA_T::CSR: MODE_SEL Mask */

#define PDMA_CSR_SW_RST_Pos                         1                               /*!< PDMA_T::CSR: SW_RST Position */
#define PDMA_CSR_SW_RST_Msk                         (1ul << PDMA_CSR_SW_RST_Pos)    /*!< PDMA_T::CSR: SW_RST Mask */

#define PDMA_CSR_PDMACEN_Pos                        0                               /*!< PDMA_T::CSR: PDMACEN Position */
#define PDMA_CSR_PDMACEN_Msk                        (1ul << PDMA_CSR_PDMACEN_Pos)   /*!< PDMA_T::CSR: PDMACEN Mask */

/* PDMA BCR Bit Field Definitions */
#define PDMA_BCR_BCR_Pos                            0                               /*!< PDMA_T::BCR: BCR Position */
#define PDMA_BCR_BCR_Msk                            (0xFFFFul << PDMA_BCR_BCR_Pos)  /*!< PDMA_T::BCR: BCR Mask */

/* PDMA POINT Bit Field Definitions */
#define PDMA_POINT_POINT_Pos                        0                               /*!< PDMA_T::POINT: POINT Position */
#define PDMA_POINT_POINT_Msk                        (0xFul << PDMA_POINT_POINT_Pos) /*!< PDMA_T::POINT: POINT Mask */

/* PDMA CBCR Bit Field Definitions */
#define PDMA_CBCR_CBCR_Pos                          0                                   /*!< PDMA_T::CBCR: CBCR Position */
#define PDMA_CBCR_CBCR_Msk                          (0xFFFFul << PDMA_CBCR_CBCR_Pos)    /*!< PDMA_T::CBCR: CBCR Mask */


/* PDMA IER Bit Field Definitions */
#define PDMA_IER_BLKD_IE_Pos                        1                               /*!< PDMA_T::IER: BLKD_IE Position */
#define PDMA_IER_BLKD_IE_Msk                        (1ul << PDMA_IER_BLKD_IE_Pos)   /*!< PDMA_T::IER: BLKD_IE Mask */

#define PDMA_IER_TABORT_IE_Pos                      0                               /*!< PDMA_T::IER: TABORT_IE Position */
#define PDMA_IER_TABORT_IE_Msk                      (1ul << PDMA_IER_TABORT_IE_Pos) /*!< PDMA_T::IER: TABORT_IE Mask */

/* PDMA ISR Bit Field Definitions */
#define PDMA_ISR_BLKD_IF_Pos                        1                               /*!< PDMA_T::ISR: BLKD_IF Position */
#define PDMA_ISR_BLKD_IF_Msk                        (1ul << PDMA_ISR_BLKD_IF_Pos)   /*!< PDMA_T::ISR: BLKD_IF Mask */

#define PDMA_ISR_TABORT_IF_Pos                      0                               /*!< PDMA_T::ISR: TABORT_IF Position */
#define PDMA_ISR_TABORT_IF_Msk                      (1ul << PDMA_ISR_TABORT_IF_Pos) /*!< PDMA_T::ISR: TABORT_IF Mask */

/* PDMA GCRCSR Bit Field Definitions */
#define PDMA_GCRCSR_CRC_CLK_EN_Pos                  24                                  /*!< PDMA_GCR_T::GCRCSR: CRC_CLK_EN Position */
#define PDMA_GCRCSR_CRC_CLK_EN_Msk                  (1ul << PDMA_GCRCSR_CRC_CLK_EN_Pos) /*!< PDMA_GCR_T::GCRCSR: CRC_CLK_EN Mask */

#define PDMA_GCRCSR_CLK8_EN_Pos                     16                                  /*!< PDMA_GCR_T::GCRCSR: CLK8_EN Position */
#define PDMA_GCRCSR_CLK8_EN_Msk                     (1ul << PDMA_GCRCSR_CLK8_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK8_EN Mask */

#define PDMA_GCRCSR_CLK7_EN_Pos                     15                                  /*!< PDMA_GCR_T::GCRCSR: CLK7_EN Position */
#define PDMA_GCRCSR_CLK7_EN_Msk                     (1ul << PDMA_GCRCSR_CLK7_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK7_EN Mask */

#define PDMA_GCRCSR_CLK6_EN_Pos                     14                                  /*!< PDMA_GCR_T::GCRCSR: CLK6_EN Position */
#define PDMA_GCRCSR_CLK6_EN_Msk                     (1ul << PDMA_GCRCSR_CLK6_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK6_EN Mask */

#define PDMA_GCRCSR_CLK5_EN_Pos                     13                                  /*!< PDMA_GCR_T::GCRCSR: CLK5_EN Position */
#define PDMA_GCRCSR_CLK5_EN_Msk                     (1ul << PDMA_GCRCSR_CLK5_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK5_EN Mask */

#define PDMA_GCRCSR_CLK4_EN_Pos                     12                                  /*!< PDMA_GCR_T::GCRCSR: CLK4_EN Position */
#define PDMA_GCRCSR_CLK4_EN_Msk                     (1ul << PDMA_GCRCSR_CLK4_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK4_EN Mask */

#define PDMA_GCRCSR_CLK3_EN_Pos                     11                                  /*!< PDMA_GCR_T::GCRCSR: CLK3_EN Position */
#define PDMA_GCRCSR_CLK3_EN_Msk                     (1ul << PDMA_GCRCSR_CLK3_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK3_EN Mask */

#define PDMA_GCRCSR_CLK2_EN_Pos                     10                                  /*!< PDMA_GCR_T::GCRCSR: CLK2_EN Position */
#define PDMA_GCRCSR_CLK2_EN_Msk                     (1ul << PDMA_GCRCSR_CLK2_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK2_EN Mask */

#define PDMA_GCRCSR_CLK1_EN_Pos                     9                                   /*!< PDMA_GCR_T::GCRCSR: CLK1_EN Position */
#define PDMA_GCRCSR_CLK1_EN_Msk                     (1ul << PDMA_GCRCSR_CLK1_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK1_EN Mask */

#define PDMA_GCRCSR_CLK0_EN_Pos                     8                                   /*!< PDMA_GCR_T::GCRCSR: CLK0_EN Position */
#define PDMA_GCRCSR_CLK0_EN_Msk                     (1ul << PDMA_GCRCSR_CLK0_EN_Pos)    /*!< PDMA_GCR_T::GCRCSR: CLK0_EN Mask */

/* PDMA PDSSR0 Bit Field Definitions */
#define PDMA_PDSSR0_SPI3_TXSEL_Pos                  28                                      /*!< PDMA_GCR_T::PDSSR0: SPI3_TXSEL Position */
#define PDMA_PDSSR0_SPI3_TXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI3_TXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI3_TXSEL Mask */

#define PDMA_PDSSR0_SPI3_RXSEL_Pos                  24                                      /*!< PDMA_GCR_T::PDSSR0: SPI3_RXSEL Position */
#define PDMA_PDSSR0_SPI3_RXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI3_RXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI3_RXSEL Mask */

#define PDMA_PDSSR0_SPI2_TXSEL_Pos                  20                                      /*!< PDMA_GCR_T::PDSSR0: SPI2_TXSEL Position */
#define PDMA_PDSSR0_SPI2_TXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI2_TXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI2_TXSEL Mask */

#define PDMA_PDSSR0_SPI2_RXSEL_Pos                  16                                      /*!< PDMA_GCR_T::PDSSR0: SPI2_RXSEL Position */
#define PDMA_PDSSR0_SPI2_RXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI2_RXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI2_RXSEL Mask */

#define PDMA_PDSSR0_SPI1_TXSEL_Pos                  12                                      /*!< PDMA_GCR_T::PDSSR0: SPI1_TXSEL Position */
#define PDMA_PDSSR0_SPI1_TXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI1_TXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI1_TXSEL Mask */

#define PDMA_PDSSR0_SPI1_RXSEL_Pos                  8                                       /*!< PDMA_GCR_T::PDSSR0: SPI1_RXSEL Position */
#define PDMA_PDSSR0_SPI1_RXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI1_RXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI1_RXSEL Mask */

#define PDMA_PDSSR0_SPI0_TXSEL_Pos                  4                                       /*!< PDMA_GCR_T::PDSSR0: SPI0_TXSEL Position */
#define PDMA_PDSSR0_SPI0_TXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI0_TXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI0_TXSEL Mask */

#define PDMA_PDSSR0_SPI0_RXSEL_Pos                  0                                       /*!< PDMA_GCR_T::PDSSR0: SPI0_RXSEL Position */
#define PDMA_PDSSR0_SPI0_RXSEL_Msk                  (0xFul << PDMA_PDSSR0_SPI0_RXSEL_Pos)   /*!< PDMA_GCR_T::PDSSR0: SPI0_RXSEL Mask */

/* PDMA PDSSR1 Bit Field Definitions */
#define PDMA_PDSSR1_ADC_RXSEL_Pos                   24                                      /*!< PDMA_GCR_T::PDSSR1: ADC_RXSEL Position */
#define PDMA_PDSSR1_ADC_RXSEL_Msk                   (0xFul << PDMA_PDSSR1_ADC_RXSEL_Pos)    /*!< PDMA_GCR_T::PDSSR1: ADC_RXSEL Mask */

#define PDMA_PDSSR1_UART1_TXSEL_Pos                 12                                      /*!< PDMA_GCR_T::PDSSR1: UART1_TXSEL Position */
#define PDMA_PDSSR1_UART1_TXSEL_Msk                 (0xFul << PDMA_PDSSR1_UART1_TXSEL_Pos)  /*!< PDMA_GCR_T::PDSSR1: UART1_TXSEL Mask */

#define PDMA_PDSSR1_UART1_RXSEL_Pos                 8                                       /*!< PDMA_GCR_T::PDSSR1: UART1_RXSEL Position */
#define PDMA_PDSSR1_UART1_RXSEL_Msk                 (0xFul << PDMA_PDSSR1_UART1_RXSEL_Pos)  /*!< PDMA_GCR_T::PDSSR1: UART1_RXSEL Mask */

#define PDMA_PDSSR1_UART0_TXSEL_Pos                 4                                       /*!< PDMA_GCR_T::PDSSR1: UART0_TXSEL Position */
#define PDMA_PDSSR1_UART0_TXSEL_Msk                 (0xFul << PDMA_PDSSR1_UART0_TXSEL_Pos)  /*!< PDMA_GCR_T::PDSSR1: UART0_TXSEL Mask */

#define PDMA_PDSSR1_UART0_RXSEL_Pos                 0                                       /*!< PDMA_GCR_T::PDSSR1: UART0_RXSEL Position */
#define PDMA_PDSSR1_UART0_RXSEL_Msk                 (0xFul << PDMA_PDSSR1_UART0_RXSEL_Pos)  /*!< PDMA_GCR_T::PDSSR1: UART0_RXSEL Mask */

/* PDMA GCRISR Bit Field Definitions */
#define PDMA_GCRISR_INTR_Pos                        31                              /*!< PDMA_GCR_T::GCRISR: INTR Position */
#define PDMA_GCRISR_INTR_Msk                        (1ul << PDMA_GCRISR_INTR_Pos)   /*!< PDMA_GCR_T::GCRISR: INTR Mask */

#define PDMA_GCRISR_INTRCRC_Pos                     16                               /*!< PDMA_GCR_T::GCRISR: INTRCRC Position */
#define PDMA_GCRISR_INTRCRC_Msk                     (1ul << PDMA_GCRISR_INTRCRC_Pos) /*!< PDMA_GCR_T::GCRISR: INTRCRC Mask */

#define PDMA_GCRISR_INTR8_Pos                       8                               /*!< PDMA_GCR_T::GCRISR: INTR8 Position */
#define PDMA_GCRISR_INTR8_Msk                       (1ul << PDMA_GCRISR_INTR8_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR8 Mask */

#define PDMA_GCRISR_INTR7_Pos                       7                               /*!< PDMA_GCR_T::GCRISR: INTR7 Position */
#define PDMA_GCRISR_INTR7_Msk                       (1ul << PDMA_GCRISR_INTR7_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR7 Mask */

#define PDMA_GCRISR_INTR6_Pos                       6                               /*!< PDMA_GCR_T::GCRISR: INTR6 Position */
#define PDMA_GCRISR_INTR6_Msk                       (1ul << PDMA_GCRISR_INTR6_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR6 Mask */

#define PDMA_GCRISR_INTR5_Pos                       5                               /*!< PDMA_GCR_T::GCRISR: INTR5 Position */
#define PDMA_GCRISR_INTR5_Msk                       (1ul << PDMA_GCRISR_INTR5_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR5 Mask */

#define PDMA_GCRISR_INTR4_Pos                       4                               /*!< PDMA_GCR_T::GCRISR: INTR4 Position */
#define PDMA_GCRISR_INTR4_Msk                       (1ul << PDMA_GCRISR_INTR4_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR4 Mask */

#define PDMA_GCRISR_INTR3_Pos                       3                               /*!< PDMA_GCR_T::GCRISR: INTR3 Position */
#define PDMA_GCRISR_INTR3_Msk                       (1ul << PDMA_GCRISR_INTR3_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR3 Mask */

#define PDMA_GCRISR_INTR2_Pos                       2                               /*!< PDMA_GCR_T::GCRISR: INTR2 Position */
#define PDMA_GCRISR_INTR2_Msk                       (1ul << PDMA_GCRISR_INTR2_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR2 Mask */

#define PDMA_GCRISR_INTR1_Pos                       1                               /*!< PDMA_GCR_T::GCRISR: INTR1 Position */
#define PDMA_GCRISR_INTR1_Msk                       (1ul << PDMA_GCRISR_INTR1_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR1 Mask */

#define PDMA_GCRISR_INTR0_Pos                       0                               /*!< PDMA_GCR_T::GCRISR: INTR0 Position */
#define PDMA_GCRISR_INTR0_Msk                       (1ul << PDMA_GCRISR_INTR0_Pos)  /*!< PDMA_GCR_T::GCRISR: INTR0 Mask */

/* PDMA PDSSR2 Bit Field Definitions */
#define PDMA_PDSSR2_I2S_TXSEL_Pos                   4                                       /*!< PDMA_GCR_T::PDSSR2: I2S_TXSEL Position */
#define PDMA_PDSSR2_I2S_TXSEL_Msk                   (0xFul << PDMA_PDSSR2_I2S_TXSEL_Pos)    /*!< PDMA_GCR_T::PDSSR2: I2S_TXSEL Mask */

#define PDMA_PDSSR2_I2S_RXSEL_Pos                   0                                       /*!< PDMA_GCR_T::PDSSR2: I2S_RXSEL Position */
#define PDMA_PDSSR2_I2S_RXSEL_Msk                   (0xFul << PDMA_PDSSR2_I2S_RXSEL_Pos)    /*!< PDMA_GCR_T::PDSSR2: I2S_RXSEL Mask */
/*@}*/ /* end of group PDMA_CONST */
/*@}*/ /* end of group PDMA */



/*------------------------------ PS2 Controller ------------------------------*/
/** @addtogroup PS2 PS2 Serial Interface(PS2)
  Memory Mapped Structure for PS2 Serial Interface Controller
  @{
 */


typedef struct
{


/**
 * @var PS2_T::PS2CON
 * Offset: 0x00  PS/2 Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PS2EN     |Enable PS/2 Device
 * |        |          |Enable PS/2 device controller
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[1]     |TXINTEN   |Enable Transmit Interrupt
 * |        |          |0 = Data transmit complete interrupt Disabled.
 * |        |          |1 = Data transmit complete interrupt Enabled.
 * |[2]     |RXINTEN   |Enable Receive Interrupt
 * |        |          |0 = Data receive complete interrupt Disabled.
 * |        |          |1 = Data receive complete interrupt Enabled.
 * |[6:3]   |TXFIFO_DEPTH|Transmit Data FIFO Depth
 * |        |          |There are 16 bytes buffer for data transmit.
 * |        |          |Software can define the FIFO depth from 1 to 16 bytes depends on application needs.
 * |        |          |0 = 1 byte.
 * |        |          |1 = 2 bytes.
 * |        |          |...
 * |        |          |14 = 15 bytes.
 * |        |          |15 = 16 bytes.
 * |[7]     |ACK       |Acknowledge Enable
 * |        |          |0 = Always send acknowledge to host at 12th clock for host to device communication.
 * |        |          |1 = If parity bit error or stop bit is not received correctly, acknowledge bit will not be
 * |        |          |sent to host at 12th clock.
 * |[8]     |CLRFIFO   |Clear TX FIFO
 * |        |          |Write 1 to this bit to terminate device to host transmission.
 * |        |          |The TXEMPTY(PS2STATUS[7]) bit will be set to 1 and pointer BYTEIDEX(PS2STATUS[11:8]) is
 * |        |          |reset to 0 regardless there is residue data in buffer or not.
 * |        |          |The buffer content is not been cleared.
 * |        |          |0 = Not active.
 * |        |          |1 = Clear FIFO.
 * |[9]     |OVERRIDE  |Software Override PS/2 CLK/DATA Pin State
 * |        |          |0 = PS2_CLK and PS2_DATA pins are controlled by internal state machine.
 * |        |          |1 = PS2_CLK and PS2_DATA pins are controlled by software.
 * |[10]    |FPS2CLK   |Force PS2CLK Line
 * |        |          |It forces PS2_CLK line high or low regardless of the internal state of the device controller
 * |        |          |if OVERRIDE(PS2CON[9]) is set to 1.
 * |        |          |0 = Force PS2_CLK line low.
 * |        |          |1 = Force PS2_CLK line high.
 * |[11]    |FPS2DAT   |Force PS2DATA Line
 * |        |          |It forces PS2_DATA high or low regardless of the internal state of the device controller if
 * |        |          |OVERRIDE (PS2CON[9]) is set to 1.
 * |        |          |0 = Force PS2_DATA low.
 * |        |          |1 = Force PS2_DATA high.
 * @var PS2_T::PS2TXDATA0
 * Offset: 0x04  PS/2 Transmit Data Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PS2TXDATAx|Transmit Data
 * |        |          |Writing data to this register starts in device to host communication if bus is in IDLE
 * |        |          |state.
 * |        |          |Software must enable PS2EN(PS2CON[0]) before writing data to TX buffer.
 * @var PS2_T::PS2TXDATA1
 * Offset: 0x08  PS/2 Transmit Data Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PS2TXDATAx|Transmit Data
 * |        |          |Writing data to this register starts in device to host communication if bus is in IDLE
 * |        |          |state.
 * |        |          |Software must enable PS2EN(PS2CON[0]) before writing data to TX buffer.
 * @var PS2_T::PS2TXDATA2
 * Offset: 0x0C  PS/2 Transmit Data Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PS2TXDATAx|Transmit Data
 * |        |          |Writing data to this register starts in device to host communication if bus is in IDLE
 * |        |          |state.
 * |        |          |Software must enable PS2EN(PS2CON[0]) before writing data to TX buffer.
 * @var PS2_T::PS2TXDATA3
 * Offset: 0x10  PS/2 Transmit Data Register 3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PS2TXDATAx|Transmit Data
 * |        |          |Writing data to this register starts in device to host communication if bus is in IDLE
 * |        |          |state.
 * |        |          |Software must enable PS2EN(PS2CON[0]) before writing data to TX buffer.
 * @var PS2_T::PS2RXDATA
 * Offset: 0x14  PS/2 Receive Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |RXDATA    |Received Data
 * |        |          |For host to device communication, after acknowledge bit is sent, the received data is copied
 * |        |          |from receive shift register to PS2RXDATA register.
 * |        |          |CPU must read this register before next byte reception complete, otherwise the data will be
 * |        |          |overwritten and RXOVF(PS2STATUS[6]) bit will be set to 1.
 * @var PS2_T::PS2STATUS
 * Offset: 0x18  PS/2 Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PS2CLK    |CLK Pin State
 * |        |          |This bit reflects the status of the PS2_CLK line after synchronizing.
 * |[1]     |PS2DATA   |DATA Pin State
 * |        |          |This bit reflects the status of the PS2_DATA line after synchronizing and sampling.
 * |[2]     |FRAMERR   |Frame Error
 * |        |          |For host to device communication, this bit sets to 1 if STOP bit (logic 1) is not received.
 * |        |          |If frame error occurs, the PS/2_DATA line may keep at low state after 12th clock.
 * |        |          |At this moment, software overrides PS2_CLK to send clock till PS2_DATA release to high
 * |        |          |state.
 * |        |          |After that, device sends a "Resend" command to host.
 * |        |          |0 = No frame error.
 * |        |          |1 = Frame error occur.
 * |        |          |Write 1 to clear this bit.
 * |[3]     |RXPARITY  |Received Parity
 * |        |          |This bit reflects the parity bit for the last received data byte (odd parity).
 * |        |          |This bit is read only.
 * |[4]     |RXBUSY    |Receive Busy
 * |        |          |This bit indicates that the PS/2 device is currently receiving data.
 * |        |          |0 = Idle.
 * |        |          |1 = Currently receiving data.
 * |        |          |This bit is read only.
 * |[5]     |TXBUSY    |Transmit Busy
 * |        |          |This bit indicates that the PS/2 device is currently sending data.
 * |        |          |0 = Idle.
 * |        |          |1 = Currently sending data.
 * |        |          |This bit is read only.
 * |[6]     |RXOVF     |RX Buffer Overwrite
 * |        |          |0 = No overwrite.
 * |        |          |1 = Data in PS2RXDATA register is overwritten by new received data.
 * |        |          |Write 1 to clear this bit.
 * |[7]     |TXEMPTY   |TX FIFO Empty
 * |        |          |When software writes data to PS2TXDATA0-3, the TXEMPTY bit is cleared to 0 immediately if
 * |        |          |PS2EN(PS2CON[0]) is enabled.
 * |        |          |When transmitted data byte number is equal to FIFODEPTH(PS2CON[6:3]) then TXEMPTY bit is set
 * |        |          |to 1.
 * |        |          |0 = There is data to be transmitted.
 * |        |          |1 = FIFO is empty.
 * |        |          |This bit is read only.
 * |[11:8]  |BYTEIDX   |Byte Index
 * |        |          |It indicates which data byte in transmit data shift register.
 * |        |          |When all data in FIFO is transmitted and it will be cleared to 0.
 * |        |          |This bit is read only.
 * |        |          |BYTEIDX,    DATA Transmit , BYTEIDX,    DATA Transmit
 * |        |          |0000   , PS2TXDATA0[ 7: 0], 1000   , PS2TXDATA2[ 7: 0],
 * |        |          |0001   , PS2TXDATA0[15: 8], 1001   , PS2TXDATA2[15: 8],
 * |        |          |0010   , PS2TXDATA0[23:16], 1010   , PS2TXDATA2[23:16],
 * |        |          |0011   , PS2TXDATA0[31:24], 1011   , PS2TXDATA2[31:24],
 * |        |          |0100   , PS2TXDATA1[ 7: 0], 1100   , PS2TXDATA3[ 7: 0],
 * |        |          |0101   , PS2TXDATA1[15: 8], 1101   , PS2TXDATA3[15: 8],
 * |        |          |0110   , PS2TXDATA1[23:16], 1110   , PS2TXDATA3[23:16],
 * |        |          |0111   , PS2TXDATA1[31:24], 1111   , PS2TXDATA3[31:24],
 * @var PS2_T::PS2INTID
 * Offset: 0x1C  PS/2 Interrupt Identification Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RXINT     |Receive Interrupt
 * |        |          |This bit is set to 1 when acknowledge bit is sent for Host to device communication.
 * |        |          |Interrupt occurs if RXINTEN(PS2CON[2]) bit is set to 1.
 * |        |          |0 = No interrupt.
 * |        |          |1 = Receive interrupt occurs.
 * |        |          |Write 1 to clear this bit to 0.
 * |[1]     |TXINT     |Transmit Interrupt
 * |        |          |This bit is set to 1 after STOP bit is transmitted.
 * |        |          |Interrupt occur if TXINTEN(PS2CON[1]) bit is set to 1.
 * |        |          |0 = No interrupt.
 * |        |          |1 = Transmit interrupt occurs.
 * |        |          |Write 1 to clear this bit to 0.
 */

    __IO uint32_t PS2CON;        /* Offset: 0x00  PS/2 Control Register                                              */
    __IO uint32_t PS2TXDATA0;    /* Offset: 0x04  PS/2 Transmit Data Register 0                                      */
    __IO uint32_t PS2TXDATA1;    /* Offset: 0x08  PS/2 Transmit Data Register 1                                      */
    __IO uint32_t PS2TXDATA2;    /* Offset: 0x0C  PS/2 Transmit Data Register 2                                      */
    __IO uint32_t PS2TXDATA3;    /* Offset: 0x10  PS/2 Transmit Data Register 3                                      */
    __IO uint32_t PS2RXDATA;     /* Offset: 0x14  PS/2 Receive Data Register                                         */
    __IO uint32_t PS2STATUS;     /* Offset: 0x18  PS/2 Status Register                                               */
    __IO uint32_t PS2INTID;      /* Offset: 0x1C  PS/2 Interrupt Identification Register                             */

} PS2_T;




/**
    @addtogroup PS2_CONST PS2 Bit Field Definition
    Constant Definitions for PS2 Controller
@{ */

/* PS2 PS2CON Bit Field Definitions */
#define PS2_PS2CON_PS2EN_Pos                       0                                        /*!< PS2_T::PS2CON: PS2EN Position */
#define PS2_PS2CON_PS2EN_Msk                       (1ul << PS2_PS2CON_PS2EN_Pos)            /*!< PS2_T::PS2CON: PS2EN Mask */

#define PS2_PS2CON_TXINTEN_Pos                     1                                        /*!< PS2_T::PS2CON: TXINTEN Position */
#define PS2_PS2CON_TXINTEN_Msk                     (1ul << PS2_PS2CON_TXINTEN_Pos)          /*!< PS2_T::PS2CON: TXINTEN Mask */

#define PS2_PS2CON_RXINTEN_Pos                     2                                        /*!< PS2_T::PS2CON: RXINTEN Position */
#define PS2_PS2CON_RXINTEN_Msk                     (1ul << PS2_PS2CON_RXINTEN_Pos)          /*!< PS2_T::PS2CON: RXINTEN Mask */

#define PS2_PS2CON_TXFIFO_DEPTH_Pos                3                                        /*!< PS2_T::PS2CON: TXFIFO_DEPTH Position */
#define PS2_PS2CON_TXFIFO_DEPTH_Msk                (0xFul << PS2_PS2CON_TXFIFO_DEPTH_Pos)   /*!< PS2_T::PS2CON: TXFIFO_DEPTH Mask */

#define PS2_PS2CON_ACK_Pos                         7                                        /*!< PS2_T::PS2CON: ACK Position */
#define PS2_PS2CON_ACK_Msk                         (1ul << PS2_PS2CON_ACK_Pos)              /*!< PS2_T::PS2CON: ACK Mask */

#define PS2_PS2CON_CLRFIFO_Pos                     8                                        /*!< PS2_T::PS2CON: CLRFIFO Position */
#define PS2_PS2CON_CLRFIFO_Msk                     (1ul << PS2_PS2CON_CLRFIFO_Pos)          /*!< PS2_T::PS2CON: CLRFIFO Mask */

#define PS2_PS2CON_OVERRIDE_Pos                    9                                        /*!< PS2_T::PS2CON: OVERRIDE Position */
#define PS2_PS2CON_OVERRIDE_Msk                    (1ul << PS2_PS2CON_OVERRIDE_Pos)         /*!< PS2_T::PS2CON: OVERRIDE Mask */

#define PS2_PS2CON_FPS2CLK_Pos                     10                                       /*!< PS2_T::PS2CON: FPS2CLK Position */
#define PS2_PS2CON_FPS2CLK_Msk                     (1ul << PS2_PS2CON_FPS2CLK_Pos)          /*!< PS2_T::PS2CON: FPS2CLK Mask */

#define PS2_PS2CON_FPS2DAT_Pos                     11                                       /*!< PS2_T::PS2CON: FPS2DAT Position */
#define PS2_PS2CON_FPS2DAT_Msk                     (1ul << PS2_PS2CON_FPS2DAT_Pos)          /*!< PS2_T::PS2CON: FPS2DAT Mask */

/* PS/2 PS2RXDATA Bit Field Definitions */
#define PS2_PS2RXDATA_RXDATA_Pos                   0                                        /*!< PS2_T::PS2RXDATA: RXDATA Position */
#define PS2_PS2RXDATA_RXDATA_Msk                   (0xFFul << PS2_PS2RXDATA_RXDATA_Pos)     /*!< PS2_T::PS2RXDATA: RXDATA Mask */

/* PS/2 PS2STATUS Bit Field Definitions */
#define PS2_PS2STATUS_PS2CLK_Pos                   0                                        /*!< PS2_T::PS2STATUS: PS2CLK Position */
#define PS2_PS2STATUS_PS2CLK_Msk                   (1ul << PS2_PS2STATUS_PS2CLK_Pos)        /*!< PS2_T::PS2STATUS: PS2CLK Mask */

#define PS2_PS2STATUS_PS2DATA_Pos                  1                                        /*!< PS2_T::PS2STATUS: PS2DATA Position */
#define PS2_PS2STATUS_PS2DATA_Msk                  (1ul << PS2_PS2STATUS_PS2DATA_Pos)       /*!< PS2_T::PS2STATUS: PS2DATA Mask */

#define PS2_PS2STATUS_FRAMERR_Pos                  2                                        /*!< PS2_T::PS2STATUS: FRAMERR Position */
#define PS2_PS2STATUS_FRAMERR_Msk                  (1ul << PS2_PS2STATUS_FRAMERR_Pos)       /*!< PS2_T::PS2STATUS: FRAMERR Mask */

#define PS2_PS2STATUS_RXPARITY_Pos                 3                                        /*!< PS2_T::PS2STATUS: RXPARITY Position */
#define PS2_PS2STATUS_RXPARITY_Msk                 (1ul << PS2_PS2STATUS_RXPARITY_Pos)      /*!< PS2_T::PS2STATUS: RXPARITY Mask */

#define PS2_PS2STATUS_RXBUSY_Pos                   4                                        /*!< PS2_T::PS2STATUS: RXBUSY Position */
#define PS2_PS2STATUS_RXBUSY_Msk                   (1ul << PS2_PS2STATUS_RXBUSY_Pos)        /*!< PS2_T::PS2STATUS: RXBUSY Mask */

#define PS2_PS2STATUS_TXBUSY_Pos                   5                                        /*!< PS2_T::PS2STATUS: TXBUSY Position */
#define PS2_PS2STATUS_TXBUSY_Msk                   (1ul << PS2_PS2STATUS_TXBUSY_Pos)        /*!< PS2_T::PS2STATUS: TXBUSY Mask */

#define PS2_PS2STATUS_RXOVF_Pos                    6                                        /*!< PS2_T::PS2STATUS: RXOVF Position */
#define PS2_PS2STATUS_RXOVF_Msk                    (1ul << PS2_PS2STATUS_RXOVF_Pos)         /*!< PS2_T::PS2STATUS: RXOVF Mask */

#define PS2_PS2STATUS_TXEMPTY_Pos                  7                                        /*!< PS2_T::PS2STATUS: TXEMPTY Position */
#define PS2_PS2STATUS_TXEMPTY_Msk                  (1ul << PS2_PS2STATUS_TXEMPTY_Pos)       /*!< PS2_T::PS2STATUS: TXEMPTY Mask */

#define PS2_PS2STATUS_BYTEIDX_Pos                  8                                        /*!< PS2_T::PS2STATUS: BYTEIDX Position */
#define PS2_PS2STATUS_BYTEIDX_Msk                  (0xFul << PS2_PS2STATUS_BYTEIDX_Pos)     /*!< PS2_T::PS2STATUS: BYTEIDX Mask */

/* PS/2 PS2INTID Bit Field Definitions */
#define PS2_PS2INTID_RXINT_Pos                     0                                        /*!< PS2_T::PS2INTID: RXINT Position */
#define PS2_PS2INTID_RXINT_Msk                     (1ul << PS2_PS2INTID_RXINT_Pos)          /*!< PS2_T::PS2INTID: RXINT Mask */
                                                                                                    
#define PS2_PS2INTID_TXINT_Pos                     1                                        /*!< PS2_T::PS2INTID: TXINT Position */
#define PS2_PS2INTID_TXINT_Msk                     (1ul << PS2_PS2INTID_TXINT_Pos)          /*!< PS2_T::PS2INTID: TXINT Mask */
/*@}*/ /* end of group PS2_CONST */
/*@}*/ /* end of group PS2 */


/*---------------------- Pulse Width Modulation Controller -------------------------*/
/**
    @addtogroup PWM Pulse Width Modulation Controller (PWM)
    Memory Mapped Structure for PWM Controller
@{ */


typedef struct
{


/**
 * @var PWM_T::PPR
 * Offset: 0x00  PWM Prescaler Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits     |Field     |Descriptions
 * | :----:  | :----:   | :---- |
 * |[7:0]    |CP01      |Clock Prescaler 0 (PWM-Timer 0 / 1 For Group A And PWM-Timer 4 / 5 For Group B)
 * |         |          |Clock input is divided by (CP01 + 1) before it is fed to the corresponding PWM-timer
 * |         |          |If CP01=0, then the clock prescaler 0 output clock will be stopped.
 * |         |          |So corresponding PWM-timer will also be stopped.
 * |[15:8]   |CP23      |Clock Prescaler 2 (PWM-Timer2 / 3 For Group A And PWM-Timer 6 / 7 For Group B)
 * |         |          |Clock input is divided by (CP23 + 1) before it is fed to the corresponding PWM-timer
 * |         |          |If CP23=0, then the clock prescaler 2 output clock will be stopped.
 * |         |          |So corresponding PWM-timer will also be stopped.
 * |[23:16]  |DZI01     |Dead-Zone Interval For Pair Of Channel 0 And Channel 1 (PWM0 And PWM1 Pair For PWM Group A, PWM4 And PWM5 Pair For PWM Group B)
 * |         |          |These 8-bit determine the Dead-zone length.
 * |        |          |The unit time of Dead-zone length = [(prescale+1)*(clock source divider)]/ PWMxy_CLK (where
 * |        |          |xy could be 01 or 45, depends on selected PWM channel.).
 * |[31:24]  |DZI23     |Dead-Zone Interval For Pair Of Channel2 And Channel3 (PWM2 And PWM3 Pair For PWM Group A, PWM6 And PWM7 Pair For PWM Group B)
 * |         |          |These 8-bit determine the Dead-zone length.
 * |        |          |The unit time of Dead-zone length = [(prescale+1)*(clock source divider)]/ PWMxy_CLK (where
 * |        |          |xy could be 23 or 67, depends on selected PWM channel.).
 * @var PWM_T::CSR
 * Offset: 0x04  PWM Clock Source Divider Select Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits      |Field     |Descriptions
 * | :----:   | :----:   | :---- |
 * |[2:0]     |CSR0      |Timer 0 Clock Source Selection(PWM timer 0 for group A and PWM timer 4 for group B)
 * |          |          |Select clock input for timer.
 * |          |          |(Table is the same as CSR3)
 * |[6:4]     |CSR1      |Timer 1 Clock Source Selection(PWM timer 1 for group A and PWM timer 5 for group B)
 * |          |          |Select clock input for timer.
 * |          |          |(Table is the same as CSR3)
 * |[10:8]    |CSR2      |Timer 2 Clock Source Selection(PWM timer 2 for group A and PWM timer 6 for group B)
 * |          |          |Select clock input for timer.
 * |          |          |(Table is the same as CSR3)
 * |[14:12]   |CSR3      |Timer 3 Clock Source Selection (PWM timer 3 for group A and PWM timer 7 for group B)
 * |          |          |Select clock input for timer.
 * |          |          |CSRx[2:0] = Input clock divider
 * |          |          |100 = 1
 * |          |          |011 = 16
 * |          |          |010 = 8
 * |          |          |001 = 4
 * |          |          |000 = 2
 * @var PWM_T::PCR
 * Offset: 0x08  PWM Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits     |Field         |Descriptions
 * | :----:  | :----:       | :---- |
 * |[0]      |CH0EN         |PWM-Timer 0 Enable (PWM Timer 0 For Group A And PWM Timer 4 For Group B)
 * |         |              |0 = The corresponding PWM-Timer stops running.
 * |         |              |1 = The corresponding PWM-Timer starts running.
 * |[1]      |CH0PINV       |PWM-Timer 0 Output Polar Inverse Enable (PWM Timer 0 For Group A And PWM Timer 4 For Group B)
 * |         |              |0 = PWM0 output polar inverse Disabled.
 * |         |              |1 = PWM0 output polar inverse Enabled.
 * |[2]      |CH0INV        |PWM-Timer 0 Output Inverter Enable (PWM Timer 0 For Group A And PWM Timer 4 For Group B)
 * |         |              |0 = Inverter Disabled.
 * |         |              |1 = Inverter Enabled.
 * |[3]      |CH0MOD        |PWM-Timer 0 Auto-Reload/One-Shot Mode (PWM Timer 0 For Group A And PWM Timer 4 For Group B)
 * |         |              |0 = One-shot mode.
 * |         |              |1 = Auto-reload mode.
 * |         |              |Note: If there is a transition at this bit, it will cause CNR0 and CMR0 be cleared.
 * |[4]      |DZEN01        |Dead-Zone 0 Generator Enable (PWM0 And PWM1 Pair For PWM Group A, PWM4 And PWM5 Pair For PWM Group B)
 * |         |              |0 = Disabled.
 * |         |              |1 = Enabled.
 * |        |          |Note: When Dead-zone generator is enabled, the pair of PWM0 and PWM1 becomes a complementary
 * |        |          |pair for PWM group A and the pair of PWM4 and PWM5 becomes a complementary pair for PWM
 * |        |          |group B.
 * |[5]      |DZEN23        |Dead-Zone 2 Generator Enable (PWM2 And PWM3 Pair For PWM Group A, PWM6 And PWM7 Pair For PWM Group B)
 * |         |              |0 = Disabled.
 * |         |              |1 = Enabled.
 * |        |          |Note: When Dead-zone generator is enabled, the pair of PWM2 and PWM3 becomes a complementary
 * |        |          |pair for PWM group A and the pair of PWM6 and PWM7 becomes a complementary pair for PWM
 * |        |          |group B.
 * |[8]      |CH1EN         |PWM-Timer 1 Enable (PWM Timer 1 For Group A And PWM Timer 5 For Group B)
 * |         |              |0 = Corresponding PWM-Timer Stopped.
 * |         |              |1 = Corresponding PWM-Timer Start Running.
 * |[9]      |CH1PINV       |PWM-Timer 1 Output Polar Inverse Enable (PWM Timer 1 For Group A And PWM Timer 5 For Group B)
 * |         |              |0 = PWM1 output polar inverse Disabled.
 * |         |              |1 = PWM1 output polar inverse Enabled.
 * |[10]     |CH1INV        |PWM-Timer 1 Output Inverter Enable (PWM Timer 1 For Group A And PWM Timer 5 For Group B)
 * |         |              |0 = Inverter Disable.
 * |         |              |1 = Inverter Enable.
 * |[11]     |CH1MOD        |PWM-Timer 1 Auto-Reload/One-Shot Mode (PWM Timer 1 For Group A And PWM Timer 5 For Group B)
 * |         |              |0 = One-shot mode.
 * |         |              |1 = Auto-reload mode.
 * |         |              |Note: If there is a transition at this bit, it will cause CNR1 and CMR1 be cleared.
 * |[16]     |CH2EN         |PWM-Timer 2 Enable (PWM Timer 2 For Group A And PWM Timer 6 For Group B)
 * |         |              |0 = Corresponding PWM-Timer Stopped.
 * |         |              |1 = Corresponding PWM-Timer Start Running.
 * |[17]     |CH2PINV       |PWM-Timer 2 Output Polar Inverse Enable (PWM Timer 2 For Group A And PWM Timer 6 For Group B)
 * |         |              |0 = PWM2 output polar inverse Disabled.
 * |         |              |1 = PWM2 output polar inverse Enabled.
 * |[18]     |CH2INV        |PWM-Timer 2 Output Inverter Enable (PWM Timer 2 For Group A And PWM Timer 6 For Group B)
 * |         |              |0 = Inverter Disabled.
 * |         |              |1 = Inverter Enabled.
 * |[19]     |CH2MOD        |PWM-Timer 2 Auto-Reload/One-Shot Mode (PWM Timer 2 For Group A And PWM Timer 6 For Group B)
 * |         |              |0 = One-shot mode.
 * |         |              |1 = Auto-reload mode.
 * |         |              |Note: If there is a transition at this bit, it will cause CNR2 and CMR2 be cleared.
 * |[24]     |CH3EN         |PWM-Timer 3 Enable (PWM Timer 3 For Group A And PWM Timer 7 For Group B)
 * |         |              |0 = Corresponding PWM-Timer Stopped.
 * |         |              |1 = Corresponding PWM-Timer Start Running.
 * |[25]     |CH3PINV       |PWM-Timer 3 Output Polar Inverse Enable (PWM Timer 3 For Group A And PWM Timer 7 For Group B)
 * |         |              |0 = PWM3 output polar inverse Disable.
 * |         |              |1 = PWM3 output polar inverse Enable.
 * |[26]     |CH3INV        |PWM-Timer 3 Output Inverter Enable (PWM Timer 3 For Group A And PWM Timer 7 For Group B)
 * |         |              |0 = Inverter Disabled.
 * |         |              |1 = Inverter Enabled.
 * |[27]     |CH3MOD        |PWM-Timer 3 Auto-Reload/One-Shot Mode (PWM Timer 3 For Group A And PWM Timer 7 For Group B)
 * |         |              |0 = One-shot mode.
 * |         |              |1 = Auto-reload mode.
 * |         |              |Note: If there is a transition at this bit, it will cause CNR3 and CMR3 be cleared.
 * |[30]     |PWM01TYPE     |PWM01 Aligned Type Selection Bit (PWM0 And PWM1 Pair For PWM Group A, PWM4 And PWM5 Pair For PWM Group B)
 * |         |              |0 = Edge-aligned type.
 * |         |              |1 = Center-aligned type.
 * |[31]     |PWM23TYPE     |PWM23 Aligned Type Selection Bit (PWM2 And PWM3 Pair For PWM Group A, PWM6 And PWM7 Pair For PWM Group B)
 * |         |              |0 = Edge-aligned type.
 * |         |              |1 = Center-aligned type.
 * @var PWM_T::CNR0
 * Offset: 0x0C  PWM Counter Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CNRx      |PWM Timer Loaded Value
 * |        |          |CNR determines the PWM period.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * |        |          |Note: When PWM operating at Center-aligned type, CNR value should be set between 0x0000 to
 * |        |          |0xFFFE.
 * |        |          |If CNR equal to 0xFFFF, the PWM will work unpredictable.
 * |        |          |Note: When CNR value is set to 0, PWM output is always high.
 * @var PWM_T::CMR0
 * Offset: 0x0C  PWM Counter Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CNRx      |PWM Timer Loaded Value
 * |        |          |CNR determines the PWM period.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * |        |          |Note: When PWM operating at Center-aligned type, CNR value should be set between 0x0000 to
 * |        |          |0xFFFE.
 * |        |          |If CNR equal to 0xFFFF, the PWM will work unpredictable.
 * |        |          |Note: When CNR value is set to 0, PWM output is always high.
 * @var PWM_T::PDR0
 * Offset: 0x14  PWM Data Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |PDRx      |PWM Data Register
 * |        |          |User can monitor PDR to know the current value in 16-bit counter.
 * @var PWM_T::CNR1
 * Offset: 0x18  PWM Counter Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CNRx      |PWM Timer Loaded Value
 * |        |          |CNR determines the PWM period.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * |        |          |Note: When PWM operating at Center-aligned type, CNR value should be set between 0x0000 to
 * |        |          |0xFFFE.
 * |        |          |If CNR equal to 0xFFFF, the PWM will work unpredictable.
 * |        |          |Note: When CNR value is set to 0, PWM output is always high.
 * @var PWM_T::CMR1
 * Offset: 0x1C  PWM Comparator Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CMRx      |PWM Comparator Register
 * |        |          |CMR determines the PWM duty.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * @var PWM_T::PDR1
 * Offset: 0x20  PWM Data Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |PDRx      |PWM Data Register
 * |        |          |User can monitor PDR to know the current value in 16-bit counter.
 * @var PWM_T::CNR2
 * Offset: 0x24  PWM Counter Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CNRx      |PWM Timer Loaded Value
 * |        |          |CNR determines the PWM period.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * |        |          |Note: When PWM operating at Center-aligned type, CNR value should be set between 0x0000 to
 * |        |          |0xFFFE.
 * |        |          |If CNR equal to 0xFFFF, the PWM will work unpredictable.
 * |        |          |Note: When CNR value is set to 0, PWM output is always high.
 * @var PWM_T::CMR2
 * Offset: 0x28  PWM Comparator Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CMRx      |PWM Comparator Register
 * |        |          |CMR determines the PWM duty.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * @var PWM_T::PDR2
 * Offset: 0x2C  PWM Data Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |PDRx      |PWM Data Register
 * |        |          |User can monitor PDR to know the current value in 16-bit counter.
 * @var PWM_T::CNR3
 * Offset: 0x30  PWM Counter Register 3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CNRx      |PWM Timer Loaded Value
 * |        |          |CNR determines the PWM period.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * |        |          |Note: When PWM operating at Center-aligned type, CNR value should be set between 0x0000 to
 * |        |          |0xFFFE.
 * |        |          |If CNR equal to 0xFFFF, the PWM will work unpredictable.
 * |        |          |Note: When CNR value is set to 0, PWM output is always high.
 * @var PWM_T::CMR3
 * Offset: 0x34  PWM Comparator Register 3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CMRx      |PWM Comparator Register
 * |        |          |CMR determines the PWM duty.
 * |        |          |PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)]; where xy, could be 01, 23,
 * |        |          |45 or 67, depends on selected PWM channel.
 * |        |          |For Edge-aligned type:
 * |        |          | Duty ratio = (CMR+1)/(CNR+1).
 * |        |          | CMR >= CNR: PWM output is always high.
 * |        |          | CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
 * |        |          | CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit.
 * |        |          |For Center-aligned type:
 * |        |          | Duty ratio = [(2 x CMR) + 1]/[2 x (CNR+1)].
 * |        |          | CMR > CNR: PWM output is always high.
 * |        |          | CMR <= CNR: PWM low width = 2 x (CNR-CMR) + 1 unit; PWM high width = (2 x CMR) + 1 unit.
 * |        |          | CMR = 0: PWM low width = 2 x CNR + 1 unit; PWM high width = 1 unit.
 * |        |          |(Unit = one PWM clock cycle).
 * |        |          |Note: Any write to CNR will take effect in next PWM cycle.
 * @var PWM_T::PDR3
 * Offset: 0x38  PWM Data Register 3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |PDRx      |PWM Data Register
 * |        |          |User can monitor PDR to know the current value in 16-bit counter.
 * @var PWM_T::PBCR
 * Offset: 0x3C  PWM Backward Compatible Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |BCn       |PWM Backward Compatible Register
 * |        |          |0 = Configure write 0 to clear CFLRI0~3 and CRLRI0~3.
 * |        |          |1 = Configure write 1 to clear CFLRI0~3 and CRLRI0~3.
 * |        |          |Refer to the CCR0/CCR2 register bit 6, 7, 22, 23 description
 * |        |          |Note: It is recommended that this bit be set to 1 to prevent CFLRIx and CRLRIx from being
 * |        |          |cleared when writing CCR0/CCR2.
 * @var PWM_T::PIER
 * Offset: 0x40  PWM Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PWMIE0    |PWM Channel 0 Period Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[1]     |PWMIE1    |PWM Channel 1 Period Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[2]     |PWMIE2    |PWM Channel 2 Period Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[3]     |PWMIE3    |PWM Channel 3 Period Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[8]     |PWMDIE0   |PWM Channel 0 Duty Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[9]     |PWMDIE1   |PWM Channel 1 Duty Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[10]    |PWMDIE2   |PWM Channel 2 Duty Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[11]    |PWMDIE3   |PWM Channel 3 Duty Interrupt Enable
 * |        |          |0 = Disabled.
 * |        |          |1 = Enabled.
 * |[16]    |INT01TYPE |PWM01 Interrupt Period Type Selection Bit (PWM0 And PWM1 Pair For PWM Group A, PWM4 And PWM5 Pair For PWM Group B)
 * |        |          |0 = PWMIFn will be set if PWM counter underflow.
 * |        |          |1 = PWMIFn will be set if PWM counter matches CNRn register.
 * |        |          |Note: This bit is effective when PWM in Center-aligned type only.
 * |[17]    |INT23TYPE |PWM23 Interrupt Period Type Selection Bit (PWM2 And PWM3 Pair For PWM Group A, PWM6 And PWM7 Pair For PWM Group B)
 * |        |          |0 = PWMIFn will be set if PWM counter underflow.
 * |        |          |1 = PWMIFn will be set if PWM counter matches CNRn register.
 * |        |          |Note: This bit is effective when PWM in Center-aligned type only.
 * @var PWM_T::PIIR
 * Offset: 0x44  PWM Interrupt Indication Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PWMIF0    |PWM Channel 0 Period Interrupt Status
 * |        |          |This bit is set by hardware when PWM0 counter reaches the requirement of interrupt (depend
 * |        |          |on INT01TYPE bit of PIER register), software can write 1 to clear this bit to 0.
 * |[1]     |PWMIF1    |PWM Channel 1 Period Interrupt Status
 * |        |          |This bit is set by hardware when PWM1 counter reaches the requirement of interrupt (depend
 * |        |          |on INT01TYPE bit of PIER register), software can write 1 to clear this bit to 0.
 * |[2]     |PWMIF2    |PWM Channel 2 Period Interrupt Status
 * |        |          |This bit is set by hardware when PWM2 counter reaches the requirement of interrupt (depend
 * |        |          |on INT23TYPE bit of PIER register), software can write 1 to clear this bit to 0.
 * |[3]     |PWMIF3    |PWM Channel 3 Period Interrupt Status
 * |        |          |This bit is set by hardware when PWM3 counter reaches the requirement of interrupt (depend
 * |        |          |on INT23TYPE bit of PIER register), software can write 1 to clear this bit to 0.
 * |[8]     |PWMDIF0   |PWM Channel 0 Duty Interrupt Flag
 * |        |          |Flag is set by hardware when channel 0 PWM counter down count and reaches CMR0, software can
 * |        |          |clear this bit by writing a one to it.
 * |        |          |Note: If CMR equal to CNR, this flag is not working in Edge-aligned type selection
 * |[9]     |PWMDIF1   |PWM Channel 1 Duty Interrupt Flag
 * |        |          |Flag is set by hardware when channel 1 PWM counter down count and reaches CMR1, software can
 * |        |          |clear this bit by writing a one to it.
 * |        |          |Note: If CMR equal to CNR, this flag is not working in Edge-aligned type selection
 * |[10]    |PWMDIF2   |PWM Channel 2 Duty Interrupt Flag
 * |        |          |Flag is set by hardware when channel 2 PWM counter down count and reaches CMR2, software can
 * |        |          |clear this bit by writing a one to it.
 * |        |          |Note: If CMR equal to CNR, this flag is not working in Edge-aligned type selection
 * |[11]    |PWMDIF3   |PWM Channel 3 Duty Interrupt Flag
 * |        |          |Flag is set by hardware when channel 3 PWM counter down count and reaches CMR3, software can
 * |        |          |clear this bit by writing a one to it.
 * |        |          |Note: If CMR equal to CNR, this flag is not working in Edge-aligned type selection
 * @var PWM_T::CCR0
 * Offset: 0x50  PWM Capture Control Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |INV0      |Channel 0 Inverter Enable
 * |        |          |0 = Inverter Disabled.
 * |        |          |1 = Inverter Enabled. Reverse the input signal from GPIO before fed to Capture timer
 * |[1]     |CRL_IE0   |Channel 0 Rising Latch Interrupt Enable
 * |        |          |0 = Rising latch interrupt Disabled.
 * |        |          |1 = Rising latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 0 has rising transition, Capture will
 * |        |          |issue an Interrupt.
 * |[2]     |CFL_IE0   |Channel 0 Falling Latch Interrupt Enable
 * |        |          |0 = Falling latch interrupt Disabled.
 * |        |          |1 = Falling latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 0 has falling transition, Capture will
 * |        |          |issue an Interrupt.
 * |[3]     |CAPCH0EN  |Channel 0 Capture Function Enable
 * |        |          |0 = Capture function on PWM group channel 0 Disabled.
 * |        |          |1 = Capture function on PWM group channel 0 Enabled.
 * |        |          |When Enabled, Capture latched the PWM-counter value and saved to CRLR (Rising latch) and
 * |        |          |CFLR (Falling latch).
 * |        |          |When Disabled, Capture does not update CRLR and CFLR, and disable PWM group channel 0
 * |        |          |Interrupt.
 * |[4]     |CAPIF0    |Channel 0 Capture Interrupt Indication Flag
 * |        |          |If PWM group channel 0 rising latch interrupt is enabled (CRL_IE0 = 1), a rising transition
 * |        |          |occurs at PWM group channel 0 will result in CAPIF0 to high; Similarly, a falling transition
 * |        |          |will cause CAPIF0 to be set high if PWM group channel 0 falling latch interrupt is enabled
 * |        |          |(CFL_IE0 = 1).
 * |        |          |Write 1 to clear this bit to 0.
 * |[6]     |CRLRI0    |CRLR0 Latched Indicator Bit
 * |        |          |When PWM group input channel 0 has a rising transition, CRLR0 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if the BCn bit is 0, and can write 1 to clear
 * |        |          |this bit to 0 if the BCn bit is 1.
 * |[7]     |CFLRI0    |CFLR0 Latched Indicator Bit
 * |        |          |When PWM group input channel 0 has a falling transition, CFLR0 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if the BCn bit is 0, and can write 1 to clear
 * |        |          |this bit to0 if BCn bit is 1.
 * |[16]    |INV1      |Channel 1 Inverter Enable
 * |        |          |0 = Inverter Disabled.
 * |        |          |1 = Inverter Enabled. Reverse the input signal from GPIO before fed to Capture timer
 * |[17]    |CRL_IE1   |Channel 1 Rising Latch Interrupt Enable
 * |        |          |0 = Rising latch interrupt Disabled.
 * |        |          |1 = Rising latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 1 has rising transition, Capture will
 * |        |          |issue an Interrupt.
 * |[18]    |CFL_IE1   |Channel 1 Falling Latch Interrupt Enable
 * |        |          |0 = Falling latch interrupt Disabled.
 * |        |          |1 = Falling latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 1 has falling transition, Capture will
 * |        |          |issue an Interrupt.
 * |[19]    |CAPCH1EN  |Channel 1 Capture Function Enable
 * |        |          |0 = Capture function on PWM group channel 1 Disabled.
 * |        |          |1 = Capture function on PWM group channel 1 Enabled.
 * |        |          |When Enabled, Capture latched the PWM-counter and saved to CRLR (Rising latch) and CFLR
 * |        |          |(Falling latch).
 * |        |          |When Disabled, Capture does not update CRLR and CFLR, and disable PWM group channel 1
 * |        |          |Interrupt.
 * |[20]    |CAPIF1    |Channel 1 Capture Interrupt Indication Flag
 * |        |          |If PWM group channel 1 rising latch interrupt is enabled (CRL_IE1 = 1), a rising transition
 * |        |          |occurs at PWM group channel 1 will result in CAPIF1 to high; Similarly, a falling transition
 * |        |          |will cause CAPIF1 to be set high if PWM group channel 1 falling latch interrupt is enabled
 * |        |          |(CFL_IE1 = 1).
 * |        |          |Write 1 to clear this bit to 0.
 * |[22]    |CRLRI1    |CRLR1 Latched Indicator Bit
 * |        |          |When PWM group input channel 1 has a rising transition, CRLR1 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if BCn bit is 0, and can write 1 to clear this
 * |        |          |bit to0 if BCn bit is 1.
 * |[23]    |CFLRI1    |CFLR1 Latched Indicator Bit
 * |        |          |When PWM group input channel 1 has a falling transition, CFLR1 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if BCn bit is 0, and can write 1 to clear this
 * |        |          |bit to 0 if BCn bit is 1.
 * @var PWM_T::CCR2
 * Offset: 0x54  PWM Capture Control Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |INV2      |Channel 2 Inverter Enable
 * |        |          |0 = Inverter Disabled.
 * |        |          |1 = Inverter Enabled. Reverse the input signal from GPIO before fed to Capture timer
 * |[1]     |CRL_IE2   |Channel 2 Rising Latch Interrupt Enable
 * |        |          |0 = Rising latch interrupt Disabled.
 * |        |          |1 = Rising latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 2 has rising transition, Capture will
 * |        |          |issue an Interrupt.
 * |[2]     |CFL_IE2   |Channel 2 Falling Latch Interrupt Enable
 * |        |          |0 = Falling latch interrupt Disabled.
 * |        |          |1 = Falling latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 2 has falling transition, Capture will
 * |        |          |issue an Interrupt.
 * |[3]     |CAPCH2EN  |Channel 2 Capture Function Enable
 * |        |          |0 = Capture function on PWM group channel 2 Disabled.
 * |        |          |1 = Capture function on PWM group channel 2 Enabled.
 * |        |          |When Enabled, Capture latched the PWM-counter value and saved to CRLR (Rising latch) and
 * |        |          |CFLR (Falling latch).
 * |        |          |When Disabled, Capture does not update CRLR and CFLR, and disable PWM group channel 2
 * |        |          |Interrupt.
 * |[4]     |CAPIF2    |Channel 2 Capture Interrupt Indication Flag
 * |        |          |If PWM group channel 2 rising latch interrupt is enabled (CRL_IE2=1), a rising transition
 * |        |          |occurs at PWM group channel 2 will result in CAPIF2 to high; Similarly, a falling transition
 * |        |          |will cause CAPIF2 to be set high if PWM group channel 2 falling latch interrupt is enabled
 * |        |          |(CFL_IE2=1).
 * |        |          |Write 1 to clear this bit to 0
 * |[6]     |CRLRI2    |CRLR2 Latched Indicator Bit
 * |        |          |When PWM group input channel 2 has a rising transition, CRLR2 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if the BCn bit is 0, and can write 1 to clear
 * |        |          |this bit to 0 if the BCn bit is 1.
 * |[7]     |CFLRI2    |CFLR2 Latched Indicator Bit
 * |        |          |When PWM group input channel 2 has a falling transition, CFLR2 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if BCn bit is 0, and can write 1 to clear this
 * |        |          |bit to 0 if the BCn bit is 1.
 * |[16]    |INV3      |Channel 3 Inverter Enable
 * |        |          |0 = Inverter Disabled.
 * |        |          |1 = Inverter Enabled. Reverse the input signal from GPIO before fed to Capture timer
 * |[17]    |CRL_IE3   |Channel 3 Rising Latch Interrupt Enable
 * |        |          |0 = Rising latch interrupt Disabled.
 * |        |          |1 = Rising latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 3 has rising transition, Capture will
 * |        |          |issue an Interrupt.
 * |[18]    |CFL_IE3   |Channel 3 Falling Latch Interrupt Enable
 * |        |          |0 = Falling latch interrupt Disabled.
 * |        |          |1 = Falling latch interrupt Enabled.
 * |        |          |When Enabled, if Capture detects PWM group channel 3 has falling transition, Capture will
 * |        |          |issue an Interrupt.
 * |[19]    |CAPCH3EN  |Channel 3 Capture Function Enable
 * |        |          |0 = Capture function on PWM group channel 3 Disabled.
 * |        |          |1 = Capture function on PWM group channel 3 Enabled.
 * |        |          |When Enabled, Capture latched the PWM-counter and saved to CRLR (Rising latch) and CFLR
 * |        |          |(Falling latch).
 * |        |          |When Disabled, Capture does not update CRLR and CFLR, and disable PWM group channel 3
 * |        |          |Interrupt.
 * |[20]    |CAPIF3    |Channel 3 Capture Interrupt Indication Flag
 * |        |          |If PWM group channel 3 rising latch interrupt is enabled (CRL_IE3=1), a rising transition
 * |        |          |occurs at PWM group channel 3 will result in CAPIF3 to high; Similarly, a falling transition
 * |        |          |will cause CAPIF3 to be set high if PWM group channel 3 falling latch interrupt is enabled
 * |        |          |(CFL_IE3=1).
 * |        |          |Write 1 to clear this bit to 0
 * |[22]    |CRLRI3    |CRLR3 Latched Indicator Bit
 * |        |          |When PWM group input channel 3 has a rising transition, CRLR3 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if the BCn bit is 0, and can write 1 to clear
 * |        |          |this bit to 0 if the BCn bit is 1.
 * |[23]    |CFLRI3    |CFLR3 Latched Indicator Bit
 * |        |          |When PWM group input channel 3 has a falling transition, CFLR3 was latched with the value of
 * |        |          |PWM down-counter and this bit is set by hardware.
 * |        |          |Software can write 0 to clear this bit to 0 if the BCn bit is 0, and can write 1 to clear
 * |        |          |this bit to 0 if the BCn bit is 1.
 * @var PWM_T::CRLR0
 * Offset: 0x58  PWM Capture Rising Latch Register (Channel 0)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CRLRx     |Capture Rising Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
 * @var PWM_T::CFLR0
 * Offset: 0x5C  PWM Capture Falling Latch Register (Channel 0)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CFLRx     |Capture Falling Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has Falling transition.
 * @var PWM_T::CRLR1
 * Offset: 0x60  PWM Capture Rising Latch Register (Channel 1)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CRLRx     |Capture Rising Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
 * @var PWM_T::CFLR1
 * Offset: 0x64  PWM Capture Falling Latch Register (Channel 1)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CFLRx     |Capture Falling Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has Falling transition.
 * @var PWM_T::CRLR2
 * Offset: 0x68  PWM Capture Rising Latch Register (Channel 2)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CRLRx     |Capture Rising Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
 * @var PWM_T::CFLR2
 * Offset: 0x6C  PWM Capture Falling Latch Register (Channel 2)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CFLRx     |Capture Falling Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has Falling transition.
 * @var PWM_T::CRLR3
 * Offset: 0x70  PWM Capture Rising Latch Register (Channel 3)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CRLRx     |Capture Rising Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has rising transition.
 * @var PWM_T::CFLR3
 * Offset: 0x74  PWM Capture Falling Latch Register (Channel 3)
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |CFLRx     |Capture Falling Latch Register
 * |        |          |Latch the PWM counter when Channel 0/1/2/3 has Falling transition.
 * @var PWM_T::CAPENR
 * Offset: 0x78  PWM Capture Input 0~3 Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CINEN0    |Channel 0 Capture Input Enable
 * |        |          |0 = PWM Channel 0 capture input path Disabled.
 * |        |          |The input of PWM channel 0 capture function is always regarded as 0.
 * |        |          |1 = PWM Channel 0 capture input path Enabled.
 * |        |          |The input of PWM channel 0 capture function comes from correlative multifunction pin if GPIO
 * |        |          |multi-function is set as PWM0.
 * |[1]     |CINEN1    |Channel 1 Capture Input Enable
 * |        |          |0 = PWM Channel 1 capture input path Disabled.
 * |        |          |The input of PWM channel 1 capture function is always regarded as 0.
 * |        |          |1 = PWM Channel 1 capture input path Enabled.
 * |        |          |The input of PWM channel 1 capture function comes from correlative multifunction pin if GPIO
 * |        |          |multi-function is set as PWM1.
 * |[2]     |CINEN2    |Channel 2 Capture Input Enable
 * |        |          |0 = PWM Channel 2 capture input path Disabled.
 * |        |          |The input of PWM channel 2 capture function is always regarded as 0.
 * |        |          |1 = PWM Channel 2 capture input path Enabled.
 * |        |          |The input of PWM channel 2 capture function comes from correlative multifunction pin if GPIO
 * |        |          |multi-function is set as PWM2.
 * |[3]     |CINEN3    |Channel 3 Capture Input Enable
 * |        |          |0 = PWM Channel 3 capture input path Disabled.
 * |        |          |The input of PWM channel 3 capture function is always regarded as 0.
 * |        |          |1 = PWM Channel 3 capture input path Enabled.
 * |        |          |The input of PWM channel 3 capture function comes from correlative multifunction pin if GPIO
 * |        |          |multi-function is set as PWM3.
 * @var PWM_T::POE
 * Offset: 0x7C  PWM Output Enable for Channel 0~3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |POE0      |Channel 0 Output Enable Register
 * |        |          |0 = PWM channel 0 output to pin Disabled.
 * |        |          |1 = PWM channel 0 output to pin Enabled.
 * |        |          |Note: The corresponding GPIO pin must also be switched to PWM function
 * |[1]     |POE1      |Channel 1 Output Enable Register
 * |        |          |0 = PWM channel 1 output to pin Disabled.
 * |        |          |1 = PWM channel 1 output to pin Enabled.
 * |        |          |Note: The corresponding GPIO pin must also be switched to PWM function
 * |[2]     |POE2      |Channel 2 Output Enable Register
 * |        |          |0 = PWM channel 2 output to pin Disabled.
 * |        |          |1 = PWM channel 2 output to pin Enabled.
 * |        |          |Note: The corresponding GPIO pin must also be switched to PWM function
 * |[3]     |POE3      |Channel 3 Output Enable Register
 * |        |          |0 = PWM channel 3 output to pin Disabled.
 * |        |          |1 = PWM channel 3 output to pin Enabled.
 * |        |          |Note: The corresponding GPIO pin must also be switched to PWM function
 * @var PWM_T::TCON
 * Offset: 0x80  PWM Trigger Control for Channel 0~3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PWM0TEN   |Channel 0 Center-Aligned Trigger Enable Register
 * |        |          |0 = PWM channel 0 trigger ADC function Disabled.
 * |        |          |1 = PWM channel 0 trigger ADC function Enabled.
 * |        |          |PWM can trigger ADC to start conversion when PWM counter up count to CNR if this bit is set
 * |        |          |to 1.
 * |        |          |Note: This function is only supported when PWM operating at Center-aligned type.
 * |[1]     |PWM1TEN   |Channel 1 Center-Aligned Trigger Enable Register
 * |        |          |0 = PWM channel 1 trigger ADC function Disabled.
 * |        |          |1 = PWM channel 1 trigger ADC function Enabled.
 * |        |          |PWM can trigger ADC to start conversion when PWM counter up count to CNR if this bit is set
 * |        |          |to 1.
 * |        |          |Note: This function is only supported when PWM operating at Center-aligned type.
 * |[2]     |PWM2TEN   |Channel 2 Center-Aligned Trigger Enable Register
 * |        |          |0 = PWM channel 2 trigger ADC function Disabled.
 * |        |          |1 = PWM channel 2 trigger ADC function Enabled.
 * |        |          |PWM can trigger ADC to start conversion when PWM counter up count to CNR if this bit is set
 * |        |          |to 1.
 * |        |          |Note: This function is only supported when PWM operating at Center-aligned type.
 * |[3]     |PWM3TEN   |Channel 3 Center-Aligned Trigger Enable Register
 * |        |          |0 = PWM channel 3 trigger ADC function Disabled.
 * |        |          |1 = PWM channel 3 trigger ADC function Enabled.
 * |        |          |PWM can trigger ADC to start conversion when PWM counter up count to CNR if this bit is set
 * |        |          |to 1.
 * |        |          |Note: This function is only supported when PWM operating at Center-aligned type.
 * @var PWM_T::TSTATUS
 * Offset: 0x84  PWM Trigger Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PWM0TF    |Channel 0 Center-Aligned Trigger Flag
 * |        |          |For Center-aligned Operating mode, this bit is set to 1 by hardware when PWM counter up
 * |        |          |counts to CNR if PWM0TEN bit is set to 1.
 * |        |          |After this bit is set to 1, ADC will start conversion if ADC triggered source is selected by
 * |        |          |PWM.
 * |        |          |Software can write 1 to clear this bit.
 * |[1]     |PWM1TF    |Channel 1 Center-Aligned Trigger Flag
 * |        |          |For Center-aligned Operating mode, this bit is set to 1 by hardware when PWM counter up
 * |        |          |count to CNR if PWM1TEN bit is set to 1.
 * |        |          |After this bit is set to 1, ADC will start conversion if ADC triggered source is selected by
 * |        |          |PWM.
 * |        |          |Software can write 1 to clear this bit.
 * |[2]     |PWM2TF    |Channel 2 Center-Aligned Trigger Flag
 * |        |          |For Center-aligned Operating mode, this bit is set to 1 by hardware when PWM counter up
 * |        |          |count to CNR if PWM2TEN bit is set to 1.
 * |        |          |After this bit is set to 1, ADC will start conversion if ADC triggered source is selected by
 * |        |          |PWM.
 * |        |          |Software can write 1 to clear this bit.
 * |[3]     |PWM3TF    |Channel 3 Center-Aligned Trigger Flag
 * |        |          |For Center-aligned Operating mode, this bit is set to 1 by hardware when PWM counter up
 * |        |          |count to CNR if PWM3TEN bit is set to 1.
 * |        |          |After this bit is set to 1, ADC will start conversion if ADC triggered source is selected by
 * |        |          |PWM.
 * |        |          |Software can write 1 to clear this bit.
 * @var PWM_T::SYNCBUSY0
 * Offset: 0x88  PWM0 Synchronous Busy Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |S_BUSY    |PWM Synchronous Busy
 * |        |          |When software writes CNR0/CMR0/PPR or switches PWM0 operation mode (PCR[3]), PWM will have a
 * |        |          |busy time to update these values completely because PWM clock may be different from system
 * |        |          |clock domain.
 * |        |          |Software needs to check this busy status before writing CNR0/CMR0/PPR or switching PWM0
 * |        |          |operation mode (PCR[3]) to make sure previous setting has been updated completely.
 * |        |          |This bit will be set when software writes CNR0/CMR0/PPR or switches PWM0 operation mode
 * |        |          |(PCR[3]) and will be cleared by hardware automatically when PWM update these value
 * |        |          |completely.
 * @var PWM_T::SYNCBUSY1
 * Offset: 0x8C  PWM1 Synchronous Busy Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |S_BUSY    |PWM Synchronous Busy
 * |        |          |When Software writes CNR1/CMR1/PPR or switches PWM1 operation mode (PCR[11]), PWM will have
 * |        |          |a busy time to update these values completely because PWM clock may be different from system
 * |        |          |clock domain.
 * |        |          |Software needs to check this busy status before writing CNR1/CMR1/PPR or switching PWM1
 * |        |          |operation mode (PCR[11]) to make sure previous setting has been updated completely.
 * |        |          |This bit will be set when software writes CNR1/CMR1/PPR or switches PWM1 operation mode
 * |        |          |(PCR[11]) and will be cleared by hardware automatically when PWM update these value
 * |        |          |completely.
 * @var PWM_T::SYNCBUSY2
 * Offset: 0x90  PWM2 Synchronous Busy Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |S_BUSY    |PWM Synchronous Busy
 * |        |          |When Software writes CNR2/CMR2/PPR or switch PWM2 operation mode (PCR[19]), PWM will have a
 * |        |          |busy time to update these values completely because PWM clock may be different from system
 * |        |          |clock domain.
 * |        |          |Software needs to check this busy status before writing CNR2/CMR2/PPR or switching PWM2
 * |        |          |operation mode (PCR[19]) to make sure previous setting has been updated completely.
 * |        |          |This bit will be set when software writes CNR2/CMR2/PPR or switch PWM2 operation mode
 * |        |          |(PCR[19]) and will be cleared by hardware automatically when PWM update these value
 * |        |          |completely.
 * @var PWM_T::SYNCBUSY3
 * Offset: 0x94  PWM3 Synchronous Busy Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |S_BUSY    |PWM Synchronous Busy
 * |        |          |When Software writes CNR3/CMR3/PPR or switch PWM3 operation mode (PCR[27]), PWM will have a
 * |        |          |busy time to update these values completely because PWM clock may be different from system
 * |        |          |clock domain.
 * |        |          |Software need to check this busy status before writing CNR3/CMR3/PPR or switching PWM3
 * |        |          |operation mode (PCR[27]) to make sure previous setting has been updated completely.
 * |        |          |This bit will be set when Software writes CNR3/CMR3/PPR or switch PWM3 operation mode
 * |        |          |(PCR[27]) and will be cleared by hardware automatically when PWM update these value
 * |        |          |completely.
 */

    __IO uint32_t PPR;           /* Offset: 0x00  PWM Prescaler Register                                             */
    __IO uint32_t CSR;           /* Offset: 0x04  PWM Clock Source Divider Select Register                           */
    __IO uint32_t PCR;           /* Offset: 0x08  PWM Control Register                                               */
    __IO uint32_t CNR0;          /* Offset: 0x0C  PWM Counter Register 0                                             */
    __IO uint32_t CMR0;          /* Offset: 0x10  PWM Comparator Register 0                                          */
    __I  uint32_t PDR0;          /* Offset: 0x14  PWM Data Register 0                                                */
    __IO uint32_t CNR1;          /* Offset: 0x18  PWM Counter Register 1                                             */
    __IO uint32_t CMR1;          /* Offset: 0x1C  PWM Comparator Register 1                                          */
    __I  uint32_t PDR1;          /* Offset: 0x20  PWM Data Register 1                                                */
    __IO uint32_t CNR2;          /* Offset: 0x24  PWM Counter Register 2                                             */
    __IO uint32_t CMR2;          /* Offset: 0x28  PWM Comparator Register 2                                          */
    __I  uint32_t PDR2;          /* Offset: 0x2C  PWM Data Register 2                                                */
    __IO uint32_t CNR3;          /* Offset: 0x30  PWM Counter Register 3                                             */
    __IO uint32_t CMR3;          /* Offset: 0x34  PWM Comparator Register 3                                          */
    __I  uint32_t PDR3;          /* Offset: 0x38  PWM Data Register 3                                                */
    __IO uint32_t PBCR;          /* Offset: 0x3C  PWM Backward Compatible Register                                   */
    __IO uint32_t PIER;          /* Offset: 0x40  PWM Interrupt Enable Register                                      */
    __IO uint32_t PIIR;          /* Offset: 0x44  PWM Interrupt Indication Register                                  */
    __I  uint32_t RESERVE1[2];  
    __IO uint32_t CCR0;          /* Offset: 0x50  PWM Capture Control Register 0                                     */
    __IO uint32_t CCR2;          /* Offset: 0x54  PWM Capture Control Register 2                                     */
    __IO uint32_t CRLR0;         /* Offset: 0x58  PWM Capture Rising Latch Register (Channel 0)                      */
    __IO uint32_t CFLR0;         /* Offset: 0x5C  PWM Capture Falling Latch Register (Channel 0)                     */
    __IO uint32_t CRLR1;         /* Offset: 0x60  PWM Capture Rising Latch Register (Channel 1)                      */
    __IO uint32_t CFLR1;         /* Offset: 0x64  PWM Capture Falling Latch Register (Channel 1)                     */
    __IO uint32_t CRLR2;         /* Offset: 0x68  PWM Capture Rising Latch Register (Channel 2)                      */
    __IO uint32_t CFLR2;         /* Offset: 0x6C  PWM Capture Falling Latch Register (Channel 2)                     */
    __IO uint32_t CRLR3;         /* Offset: 0x70  PWM Capture Rising Latch Register (Channel 3)                      */
    __IO uint32_t CFLR3;         /* Offset: 0x74  PWM Capture Falling Latch Register (Channel 3)                     */
    __IO uint32_t CAPENR;        /* Offset: 0x78  PWM Capture Input 0~3 Enable Register                              */
    __IO uint32_t POE;           /* Offset: 0x7C  PWM Output Enable for Channel 0~3                                  */
    __IO uint32_t TCON;          /* Offset: 0x80  PWM Trigger Control for Channel 0~3                                */
    __IO uint32_t TSTATUS;       /* Offset: 0x84  PWM Trigger Status Register                                        */
    __IO uint32_t SYNCBUSY0;     /* Offset: 0x88  PWM0 Synchronous Busy Status Register                              */
    __IO uint32_t SYNCBUSY1;     /* Offset: 0x8C  PWM1 Synchronous Busy Status Register                              */
    __IO uint32_t SYNCBUSY2;     /* Offset: 0x90  PWM2 Synchronous Busy Status Register                              */
    __IO uint32_t SYNCBUSY3;     /* Offset: 0x94  PWM3 Synchronous Busy Status Register                              */

} PWM_T;



/**
    @addtogroup PWM_CONST PWM Bit Field Definition
    Constant Definitions for PWM Controller
@{ */

/* PWM PPR Bit Field Definitions */
#define PWM_PPR_DZI23_Pos                       24                                  /*!< PWM_T::PPR: DZI23 Position */
#define PWM_PPR_DZI23_Msk                       (0xFFul << PWM_PPR_DZI23_Pos)       /*!< PWM_T::PPR: DZI23 Mask */

#define PWM_PPR_DZI01_Pos                       16                                  /*!< PWM_T::PPR: DZI01 Position */
#define PWM_PPR_DZI01_Msk                       (0xFFul << PWM_PPR_DZI01_Pos)       /*!< PWM_T::PPR: DZI01 Mask */

#define PWM_PPR_CP23_Pos                        8                                   /*!< PWM_T::PPR: CP23 Position */
#define PWM_PPR_CP23_Msk                        (0xFFul << PWM_PPR_CP23_Pos)        /*!< PWM_T::PPR: CP23 Mask */

#define PWM_PPR_CP01_Pos                        0                                   /*!< PWM_T::PPR: CP01 Position */
#define PWM_PPR_CP01_Msk                        (0xFFul << PWM_PPR_CP01_Pos)        /*!< PWM_T::PPR: CP01 Mask */

/* PWM CSR Bit Field Definitions */
#define PWM_CSR_CSR3_Pos                        12                                  /*!< PWM_T::CSR: CSR3 Position */
#define PWM_CSR_CSR3_Msk                        (7ul << PWM_CSR_CSR3_Pos)           /*!< PWM_T::CSR: CSR3 Mask */

#define PWM_CSR_CSR2_Pos                        8                                   /*!< PWM_T::CSR: CSR2 Position */
#define PWM_CSR_CSR2_Msk                        (7ul << PWM_CSR_CSR2_Pos)           /*!< PWM_T::CSR: CSR2 Mask */

#define PWM_CSR_CSR1_Pos                        4                                   /*!< PWM_T::CSR: CSR1 Position */
#define PWM_CSR_CSR1_Msk                        (7ul << PWM_CSR_CSR1_Pos)           /*!< PWM_T::CSR: CSR1 Mask */

#define PWM_CSR_CSR0_Pos                        0                                   /*!< PWM_T::CSR: CSR0 Position */
#define PWM_CSR_CSR0_Msk                        (7ul << PWM_CSR_CSR0_Pos)           /*!< PWM_T::CSR: CSR0 Mask */

/* PWM PCR Bit Field Definitions */
#define PWM_PCR_PWM23TYPE_Pos                   31                                  /*!< PWM_T::PCR: PWM23TYPE Position */
#define PWM_PCR_PWM23TYPE_Msk                   (1ul << PWM_PCR_PWM23TYPE_Pos)      /*!< PWM_T::PCR: PWM23TYPE Mask */

#define PWM_PCR_PWM01TYPE_Pos                   30                                  /*!< PWM_T::PCR: PWM01TYPE Position */
#define PWM_PCR_PWM01TYPE_Msk                   (1ul << PWM_PCR_PWM01TYPE_Pos)      /*!< PWM_T::PCR: PWM01TYPE Mask */

#define PWM_PCR_CH3MOD_Pos                      27                                  /*!< PWM_T::PCR: CH3MOD Position */
#define PWM_PCR_CH3MOD_Msk                      (1ul << PWM_PCR_CH3MOD_Pos)         /*!< PWM_T::PCR: CH3MOD Mask */

#define PWM_PCR_CH3INV_Pos                      26                                  /*!< PWM_T::PCR: CH3INV Position */
#define PWM_PCR_CH3INV_Msk                      (1ul << PWM_PCR_CH3INV_Pos)         /*!< PWM_T::PCR: CH3INV Mask */

#define PWM_PCR_CH3PINV_Pos                     25                                  /*!< PWM_T::PCR: CH3PINV Position */
#define PWM_PCR_CH3PINV_Msk                     (1ul << PWM_PCR_CH3PINV_Pos)        /*!< PWM_T::PCR: CH3PINV Mask */

#define PWM_PCR_CH3EN_Pos                       24                                  /*!< PWM_T::PCR: CH3EN Position */
#define PWM_PCR_CH3EN_Msk                       (1ul << PWM_PCR_CH3EN_Pos)          /*!< PWM_T::PCR: CH3EN Mask */

#define PWM_PCR_CH2MOD_Pos                      19                                  /*!< PWM_T::PCR: CH2MOD Position */
#define PWM_PCR_CH2MOD_Msk                      (1ul << PWM_PCR_CH2MOD_Pos)         /*!< PWM_T::PCR: CH2MOD Mask */

#define PWM_PCR_CH2INV_Pos                      18                                  /*!< PWM_T::PCR: CH2INV Position */
#define PWM_PCR_CH2INV_Msk                      (1ul << PWM_PCR_CH2INV_Pos)         /*!< PWM_T::PCR: CH2INV Mask */

#define PWM_PCR_CH2PINV_Pos                     17                                  /*!< PWM_T::PCR: CH2PINV Position */
#define PWM_PCR_CH2PINV_Msk                     (1ul << PWM_PCR_CH2PINV_Pos)        /*!< PWM_T::PCR: CH2PINV Mask */

#define PWM_PCR_CH2EN_Pos                       16                                  /*!< PWM_T::PCR: CH2EN Position */
#define PWM_PCR_CH2EN_Msk                       (1ul << PWM_PCR_CH2EN_Pos)          /*!< PWM_T::PCR: CH2EN Mask */

#define PWM_PCR_CH1MOD_Pos                      11                                  /*!< PWM_T::PCR: CH1MOD Position */
#define PWM_PCR_CH1MOD_Msk                      (1ul << PWM_PCR_CH1MOD_Pos)         /*!< PWM_T::PCR: CH1MOD Mask */

#define PWM_PCR_CH1INV_Pos                      10                                  /*!< PWM_T::PCR: CH1INV Position */
#define PWM_PCR_CH1INV_Msk                      (1ul << PWM_PCR_CH1INV_Pos)         /*!< PWM_T::PCR: CH1INV Mask */

#define PWM_PCR_CH1PINV_Pos                     9                                   /*!< PWM_T::PCR: CH1PINV Position */
#define PWM_PCR_CH1PINV_Msk                     (1ul << PWM_PCR_CH1PINV_Pos)        /*!< PWM_T::PCR: CH1PINV Mask */

#define PWM_PCR_CH1EN_Pos                       8                                   /*!< PWM_T::PCR: CH1EN Position */
#define PWM_PCR_CH1EN_Msk                       (1ul << PWM_PCR_CH1EN_Pos)          /*!< PWM_T::PCR: CH1EN Mask */

#define PWM_PCR_DZEN23_Pos                      5                                   /*!< PWM_T::PCR: DZEN23 Position */
#define PWM_PCR_DZEN23_Msk                      (1ul << PWM_PCR_DZEN23_Pos)         /*!< PWM_T::PCR: DZEN23 Mask */

#define PWM_PCR_DZEN01_Pos                      4                                   /*!< PWM_T::PCR: DZEN01 Position */
#define PWM_PCR_DZEN01_Msk                      (1ul << PWM_PCR_DZEN01_Pos)         /*!< PWM_T::PCR: DZEN01 Mask */

#define PWM_PCR_CH0MOD_Pos                      3                                   /*!< PWM_T::PCR: CH0MOD Position */
#define PWM_PCR_CH0MOD_Msk                      (1ul << PWM_PCR_CH0MOD_Pos)         /*!< PWM_T::PCR: CH0MOD Mask */

#define PWM_PCR_CH0INV_Pos                      2                                   /*!< PWM_T::PCR: CH0INV Position */
#define PWM_PCR_CH0INV_Msk                      (1ul << PWM_PCR_CH0INV_Pos)         /*!< PWM_T::PCR: CH0INV Mask */

#define PWM_PCR_CH0PINV_Pos                      1                                  /*!< PWM_T::PCR: CH0PINV Position */
#define PWM_PCR_CH0PINV_Msk                     (1ul << PWM_PCR_CH0PINV_Pos)        /*!< PWM_T::PCR: CH0PINV Mask */

#define PWM_PCR_CH0EN_Pos                       0                                   /*!< PWM_T::PCR: CH0EN Position */
#define PWM_PCR_CH0EN_Msk                       (1ul << PWM_PCR_CH0EN_Pos)          /*!< PWM_T::PCR: CH0EN Mask */

/* PWM CNR Bit Field Definitions */
#define PWM_CNR_CNR_Pos                         0                                   /*!< PWM_T::CNR0: CNR Position */
#define PWM_CNR_CNR_Msk                         (0xFFFFul << PWM_CNR_CNR_Pos)       /*!< PWM_T::CNR0: CNR Mask */
                                                                                            
/* PWM CMR Bit Field Definitions */                                                         
#define PWM_CMR_CMR_Pos                         0                                   /*!< PWM_T::CMR0: CMR Position */
#define PWM_CMR_CMR_Msk                         (0xFFFFul << PWM_CMR_CMR_Pos)       /*!< PWM_T::CMR0: CMR Mask */
                                                                                            
/* PWM PDR Bit Field Definitions */                                                         
#define PWM_PDR_PDR_Pos                         0                                   /*!< PWM_T::PDR0: PDR Position */
#define PWM_PDR_PDR_Msk                         (0xFFFFul << PWM_PDR_PDR_Pos)       /*!< PWM_T::PDR0: PDR Mask */

/* PWM PBCR Bit Field Definitions */
#define PWM_PBCR_BCn_Pos                         0                                  /*!< PWM_T::PBCR: BCn Position */
#define PWM_PBCR_BCn_Msk                         (1ul << PWM_PBCR_BCn_Pos)          /*!< PWM_T::PBCR: BCn Mask */

/* PWM PIER Bit Field Definitions */

#define PWM_PIER_INT23TYPE_Pos                  17                                  /*!< PWM_T::PIER: INT23TYPE Position */
#define PWM_PIER_INT23TYPE_Msk                     (1ul << PWM_PIER_INT23TYPE_Pos)  /*!< PWM_T::PIER: INT23TYPE Mask */

#define PWM_PIER_INT01TYPE_Pos                  16                                  /*!< PWM_T::PIER: INT01TYPE Position */
#define PWM_PIER_INT01TYPE_Msk                     (1ul << PWM_PIER_INT01TYPE_Pos)  /*!< PWM_T::PIER: INT01TYPE Mask */

#define PWM_PIER_PWMDIE3_Pos                    11                                  /*!< PWM_T::PIER: PWMDIE3 Position */
#define PWM_PIER_PWMDIE3_Msk                     (1ul << PWM_PIER_PWMDIE3_Pos)      /*!< PWM_T::PIER: PWMDIE3 Mask */

#define PWM_PIER_PWMDIE2_Pos                    10                                  /*!< PWM_T::PIER: PWMDIE2 Position */
#define PWM_PIER_PWMDIE2_Msk                     (1ul << PWM_PIER_PWMDIE2_Pos)      /*!< PWM_T::PIER: PWMDIE2 Mask */

#define PWM_PIER_PWMDIE1_Pos                    9                                   /*!< PWM_T::PIER: PWMDIE1 Position */
#define PWM_PIER_PWMDIE1_Msk                     (1ul << PWM_PIER_PWMDIE1_Pos)      /*!< PWM_T::PIER: PWMDIE1 Mask */

#define PWM_PIER_PWMDIE0_Pos                    8                                   /*!< PWM_T::PIER: PWMDIE0 Position */
#define PWM_PIER_PWMDIE0_Msk                     (1ul << PWM_PIER_PWMDIE0_Pos)      /*!< PWM_T::PIER: PWMDIE0 Mask */

#define PWM_PIER_PWMIE3_Pos                     3                                   /*!< PWM_T::PIER: PWMIE3 Position */
#define PWM_PIER_PWMIE3_Msk                     (1ul << PWM_PIER_PWMIE3_Pos)        /*!< PWM_T::PIER: PWMIE3 Mask */

#define PWM_PIER_PWMIE2_Pos                     2                                   /*!< PWM_T::PIER: PWMIE2 Position */
#define PWM_PIER_PWMIE2_Msk                     (1ul << PWM_PIER_PWMIE2_Pos)        /*!< PWM_T::PIER: PWMIE2 Mask */

#define PWM_PIER_PWMIE1_Pos                     1                                   /*!< PWM_T::PIER: PWMIE1 Position */
#define PWM_PIER_PWMIE1_Msk                     (1ul << PWM_PIER_PWMIE1_Pos)        /*!< PWM_T::PIER: PWMIE1 Mask */

#define PWM_PIER_PWMIE0_Pos                     0                                   /*!< PWM_T::PIER: PWMIE0 Position */
#define PWM_PIER_PWMIE0_Msk                     (1ul << PWM_PIER_PWMIE0_Pos)        /*!< PWM_T::PIER: PWMIE0 Mask */

/* PWM PIIR Bit Field Definitions */
#define PWM_PIIR_PWMDIF3_Pos                    11                                  /*!< PWM_T::PIIR: PWMDIF3 Position */
#define PWM_PIIR_PWMDIF3_Msk                    (1ul << PWM_PIIR_PWMDIF3_Pos)       /*!< PWM_T::PIIR: PWMDIF3 Mask */

#define PWM_PIIR_PWMDIF2_Pos                    10                                  /*!< PWM_T::PIIR: PWMDIF2 Position */
#define PWM_PIIR_PWMDIF2_Msk                    (1ul << PWM_PIIR_PWMDIF2_Pos)       /*!< PWM_T::PIIR: PWMDIF2 Mask */

#define PWM_PIIR_PWMDIF1_Pos                    9                                   /*!< PWM_T::PIIR: PWMDIF1 Position */
#define PWM_PIIR_PWMDIF1_Msk                    (1ul << PWM_PIIR_PWMDIF1_Pos)       /*!< PWM_T::PIIR: PWMDIF1 Mask */

#define PWM_PIIR_PWMDIF0_Pos                    8                                   /*!< PWM_T::PIIR: PWMDIF0 Position */
#define PWM_PIIR_PWMDIF0_Msk                    (1ul << PWM_PIIR_PWMDIF0_Pos)       /*!< PWM_T::PIIR: PWMDIF0 Mask */

#define PWM_PIIR_PWMIF3_Pos                     3                                   /*!< PWM_T::PIIR: PWMIF3 Position */
#define PWM_PIIR_PWMIF3_Msk                     (1ul << PWM_PIIR_PWMIF3_Pos)        /*!< PWM_T::PIIR: PWMIF3 Mask */

#define PWM_PIIR_PWMIF2_Pos                     2                                   /*!< PWM_T::PIIR: PWMIF2 Position */
#define PWM_PIIR_PWMIF2_Msk                     (1ul << PWM_PIIR_PWMIF2_Pos)        /*!< PWM_T::PIIR: PWMIF2 Mask */

#define PWM_PIIR_PWMIF1_Pos                     1                                   /*!< PWM_T::PIIR: PWMIF1 Position */
#define PWM_PIIR_PWMIF1_Msk                     (1ul << PWM_PIIR_PWMIF1_Pos)        /*!< PWM_T::PIIR: PWMIF1 Mask */

#define PWM_PIIR_PWMIF0_Pos                     0                                   /*!< PWM_T::PIIR: PWMIF0 Position */
#define PWM_PIIR_PWMIF0_Msk                     (1ul << PWM_PIIR_PWMIF0_Pos)        /*!< PWM_T::PIIR: PWMIF0 Mask */

/* PWM CCR0 Bit Field Definitions */
#define PWM_CCR0_CFLRI1_Pos                     23                                  /*!< PWM_T::CCR0: CFLRI1 Position */
#define PWM_CCR0_CFLRI1_Msk                     (1ul << PWM_CCR0_CFLRI1_Pos)        /*!< PWM_T::CCR0: CFLRI1 Mask */

#define PWM_CCR0_CRLRI1_Pos                     22                                  /*!< PWM_T::CCR0: CRLRI1 Position */
#define PWM_CCR0_CRLRI1_Msk                     (1ul << PWM_CCR0_CRLRI1_Pos)        /*!< PWM_T::CCR0: CRLRI1 Mask */

#define PWM_CCR0_CAPIF1_Pos                     20                                  /*!< PWM_T::CCR0: CAPIF1 Position */
#define PWM_CCR0_CAPIF1_Msk                     (1ul << PWM_CCR0_CAPIF1_Pos)        /*!< PWM_T::CCR0: CAPIF1 Mask */

#define PWM_CCR0_CAPCH1EN_Pos                   19                                  /*!< PWM_T::CCR0: CAPCH1EN Position */
#define PWM_CCR0_CAPCH1EN_Msk                   (1ul << PWM_CCR0_CAPCH1EN_Pos)      /*!< PWM_T::CCR0: CAPCH1EN Mask */

#define PWM_CCR0_CFL_IE1_Pos                    18                                  /*!< PWM_T::CCR0: CFL_IE1 Position */
#define PWM_CCR0_CFL_IE1_Msk                    (1ul << PWM_CCR0_CFL_IE1_Pos)       /*!< PWM_T::CCR0: CFL_IE1 Mask */

#define PWM_CCR0_CRL_IE1_Pos                    17                                  /*!< PWM_T::CCR0: CRL_IE1 Position */
#define PWM_CCR0_CRL_IE1_Msk                    (1ul << PWM_CCR0_CRL_IE1_Pos)       /*!< PWM_T::CCR0: CRL_IE1 Mask */

#define PWM_CCR0_INV1_Pos                       16                                  /*!< PWM_T::CCR0: INV1 Position */
#define PWM_CCR0_INV1_Msk                       (1ul << PWM_CCR0_INV1_Pos)          /*!< PWM_T::CCR0: INV1 Mask */

#define PWM_CCR0_CFLRI0_Pos                     7                                   /*!< PWM_T::CCR0: CFLRI0 Position */
#define PWM_CCR0_CFLRI0_Msk                     (1ul << PWM_CCR0_CFLRI0_Pos)        /*!< PWM_T::CCR0: CFLRI0 Mask */

#define PWM_CCR0_CRLRI0_Pos                     6                                   /*!< PWM_T::CCR0: CRLRI0 Position */
#define PWM_CCR0_CRLRI0_Msk                     (1ul << PWM_CCR0_CRLRI0_Pos)        /*!< PWM_T::CCR0: CRLRI0 Mask */

#define PWM_CCR0_CAPIF0_Pos                     4                                   /*!< PWM_T::CCR0: CAPIF0 Position */
#define PWM_CCR0_CAPIF0_Msk                     (1ul << PWM_CCR0_CAPIF0_Pos)        /*!< PWM_T::CCR0: CAPIF0 Mask */

#define PWM_CCR0_CAPCH0EN_Pos                   3                                   /*!< PWM_T::CCR0: CAPCH0EN Position */
#define PWM_CCR0_CAPCH0EN_Msk                   (1ul << PWM_CCR0_CAPCH0EN_Pos)      /*!< PWM_T::CCR0: CAPCH0EN Mask */

#define PWM_CCR0_CFL_IE0_Pos                    2                                   /*!< PWM_T::CCR0: CFL_IE0 Position */
#define PWM_CCR0_CFL_IE0_Msk                    (1ul << PWM_CCR0_CFL_IE0_Pos)       /*!< PWM_T::CCR0: CFL_IE0 Mask */

#define PWM_CCR0_CRL_IE0_Pos                    1                                   /*!< PWM_T::CCR0: CRL_IE0 Position */
#define PWM_CCR0_CRL_IE0_Msk                    (1ul << PWM_CCR0_CRL_IE0_Pos)       /*!< PWM_T::CCR0: CRL_IE0 Mask */

#define PWM_CCR0_INV0_Pos                       0                                   /*!< PWM_T::CCR0: INV0 Position */
#define PWM_CCR0_INV0_Msk                       (1ul << PWM_CCR0_INV0_Pos)          /*!< PWM_T::CCR0: INV0 Mask */

/* PWM CCR2 Bit Field Definitions */
#define PWM_CCR2_CFLRI3_Pos                     23                                  /*!< PWM_T::CCR2: CFLRI3 Position */
#define PWM_CCR2_CFLRI3_Msk                     (1ul << PWM_CCR2_CFLRI3_Pos)        /*!< PWM_T::CCR2: CFLRI3 Mask */

#define PWM_CCR2_CRLRI3_Pos                     22                                  /*!< PWM_T::CCR2: CRLRI3 Position */
#define PWM_CCR2_CRLRI3_Msk                     (1ul << PWM_CCR2_CRLRI3_Pos)        /*!< PWM_T::CCR2: CRLRI3 Mask */

#define PWM_CCR2_CAPIF3_Pos                     20                                  /*!< PWM_T::CCR2: CAPIF3 Position */
#define PWM_CCR2_CAPIF3_Msk                     (1ul << PWM_CCR2_CAPIF3_Pos)        /*!< PWM_T::CCR2: CAPIF3 Mask */

#define PWM_CCR2_CAPCH3EN_Pos                   19                                  /*!< PWM_T::CCR2: CAPCH3EN Position */
#define PWM_CCR2_CAPCH3EN_Msk                   (1ul << PWM_CCR2_CAPCH3EN_Pos)      /*!< PWM_T::CCR2: CAPCH3EN Mask */

#define PWM_CCR2_CFL_IE3_Pos                    18                                  /*!< PWM_T::CCR2: CFL_IE3 Position */
#define PWM_CCR2_CFL_IE3_Msk                    (1ul << PWM_CCR2_CFL_IE3_Pos)       /*!< PWM_T::CCR2: CFL_IE3 Mask */

#define PWM_CCR2_CRL_IE3_Pos                    17                                  /*!< PWM_T::CCR2: CRL_IE3 Position */
#define PWM_CCR2_CRL_IE3_Msk                    (1ul << PWM_CCR2_CRL_IE3_Pos)       /*!< PWM_T::CCR2: CRL_IE3 Mask */

#define PWM_CCR2_INV3_Pos                       16                                  /*!< PWM_T::CCR2: INV3 Position */
#define PWM_CCR2_INV3_Msk                       (1ul << PWM_CCR2_INV3_Pos)          /*!< PWM_T::CCR2: INV3 Mask */

#define PWM_CCR2_CFLRI2_Pos                     7                                   /*!< PWM_T::CCR2: CFLRI2 Position */
#define PWM_CCR2_CFLRI2_Msk                     (1ul << PWM_CCR2_CFLRI2_Pos)        /*!< PWM_T::CCR2: CFLRI2 Mask */

#define PWM_CCR2_CRLRI2_Pos                     6                                   /*!< PWM_T::CCR2: CRLRI2 Position */
#define PWM_CCR2_CRLRI2_Msk                     (1ul << PWM_CCR2_CRLRI2_Pos)        /*!< PWM_T::CCR2: CRLRI2 Mask */

#define PWM_CCR2_CAPIF2_Pos                     4                                   /*!< PWM_T::CCR2: CAPIF2 Position */
#define PWM_CCR2_CAPIF2_Msk                     (1ul << PWM_CCR2_CAPIF2_Pos)        /*!< PWM_T::CCR2: CAPIF2 Mask */

#define PWM_CCR2_CAPCH2EN_Pos                   3                                   /*!< PWM_T::CCR2: CAPCH2EN Position */
#define PWM_CCR2_CAPCH2EN_Msk                   (1ul << PWM_CCR2_CAPCH2EN_Pos)      /*!< PWM_T::CCR2: CAPCH2EN Mask */

#define PWM_CCR2_CFL_IE2_Pos                    2                                   /*!< PWM_T::CCR2: CFL_IE2 Position */
#define PWM_CCR2_CFL_IE2_Msk                    (1ul << PWM_CCR2_CFL_IE2_Pos)       /*!< PWM_T::CCR2: CFL_IE2 Mask */

#define PWM_CCR2_CRL_IE2_Pos                    1                                   /*!< PWM_T::CCR2: CRL_IE2 Position */
#define PWM_CCR2_CRL_IE2_Msk                    (1ul << PWM_CCR2_CRL_IE2_Pos)       /*!< PWM_T::CCR2: CRL_IE2 Mask */

#define PWM_CCR2_INV2_Pos                       0                                   /*!< PWM_T::CCR2: INV2 Position */
#define PWM_CCR2_INV2_Msk                       (1ul << PWM_CCR2_INV2_Pos)          /*!< PWM_T::CCR2: INV2 Mask */

/* PWM CRLR Bit Field Definitions */
#define PWM_CRLR_CRLR_Pos                       0                                   /*!< PWM_T::CRLR0: CRLR Position */
#define PWM_CRLR_CRLR_Msk                       (0xFFFFul << PWM_CRLR_CRLR_Pos)     /*!< PWM_T::CRLR0: CRLR Mask */

/* PWM CFLR Bit Field Definitions */
#define PWM_CFLR_CFLR_Pos                       0                                   /*!< PWM_T::CFLR0: CFLR Position */
#define PWM_CFLR_CFLR_Msk                       (0xFFFFul << PWM_CFLR_CFLR_Pos)     /*!< PWM_T::CFLR0: CFLR Mask */

/* PWM CAPENR Bit Field Definitions */
#define PWM_CAPENR_CINEN3_Pos                   3                                   /*!< PWM_T::CAPENR: CINEN3 Position */
#define PWM_CAPENR_CINEN3_Msk                   (1ul << PWM_CAPENR_CINEN3_Pos)      /*!< PWM_T::CAPENR: CINEN3 Mask */

#define PWM_CAPENR_CINEN2_Pos                   2                                   /*!< PWM_T::CAPENR: CINEN2 Position */
#define PWM_CAPENR_CINEN2_Msk                   (1ul << PWM_CAPENR_CINEN2_Pos)      /*!< PWM_T::CAPENR: CINEN2 Mask */

#define PWM_CAPENR_CINEN1_Pos                   1                                   /*!< PWM_T::CAPENR: CINEN1 Position */
#define PWM_CAPENR_CINEN1_Msk                   (1ul << PWM_CAPENR_CINEN1_Pos)      /*!< PWM_T::CAPENR: CINEN1 Mask */

#define PWM_CAPENR_CINEN0_Pos                   0                                   /*!< PWM_T::CAPENR: CINEN0 Position */
#define PWM_CAPENR_CINEN0_Msk                   (1ul << PWM_CAPENR_CINEN0_Pos)      /*!< PWM_T::CAPENR: CINEN0 Mask */

/* PWM POE Bit Field Definitions */
#define PWM_POE_POE3_Pos                        3                                   /*!< PWM_T::POE: POE3 Position */
#define PWM_POE_POE3_Msk                        (1ul << PWM_POE_POE3_Pos)           /*!< PWM_T::POE: POE3 Mask */

#define PWM_POE_POE2_Pos                        2                                   /*!< PWM_T::POE: POE2 Position */
#define PWM_POE_POE2_Msk                        (1ul << PWM_POE_POE2_Pos)           /*!< PWM_T::POE: POE2 Mask */

#define PWM_POE_POE1_Pos                        1                                   /*!< PWM_T::POE: POE1 Position */
#define PWM_POE_POE1_Msk                        (1ul << PWM_POE_POE1_Pos)           /*!< PWM_T::POE: POE1 Mask */

#define PWM_POE_POE0_Pos                        0                                   /*!< PWM_T::POE: POE0 Position */
#define PWM_POE_POE0_Msk                        (1ul << PWM_POE_POE0_Pos)           /*!< PWM_T::POE: POE0 Mask */

/* PWM TCON Bit Field Definitions */

#define PWM_TCON_PWM3TEN_Pos                    3                                   /*!< PWM_T::TCON: PWM3TEN Position */
#define PWM_TCON_PWM3TEN_Msk                    (1ul << PWM_TCON_PWM3TEN_Pos)       /*!< PWM_T::TCON: PWM3TEN Mask */

#define PWM_TCON_PWM2TEN_Pos                    2                                   /*!< PWM_T::TCON: PWM2TEN Position */
#define PWM_TCON_PWM2TEN_Msk                    (1ul << PWM_TCON_PWM2TEN_Pos)       /*!< PWM_T::TCON: PWM2TEN Mask */

#define PWM_TCON_PWM1TEN_Pos                    1                                   /*!< PWM_T::TCON: PWM1TEN Position */
#define PWM_TCON_PWM1TEN_Msk                    (1ul << PWM_TCON_PWM1TEN_Pos)       /*!< PWM_T::TCON: PWM1TEN Mask */

#define PWM_TCON_PWM0TEN_Pos                    0                                   /*!< PWM_T::TCON: PWM0TEN Position */
#define PWM_TCON_PWM0TEN_Msk                    (1ul << PWM_TCON_PWM0TEN_Pos)       /*!< PWM_T::TCON: PWM0TEN Mask */

/* PWM TSTATUS Bit Field Definitions */

#define PWM_TSTATUS_PWM3TF_Pos                  3                                   /*!< PWM_T::TSTATUS: PWM3TF Position */
#define PWM_TSTATUS_PWM3TF_Msk                  (1ul << PWM_TSTATUS_PWM3TF_Pos)     /*!< PWM_T::TSTATUS: PWM3TF Mask */

#define PWM_TSTATUS_PWM2TF_Pos                  2                                   /*!< PWM_T::TSTATUS: PWM2TF Position */
#define PWM_TSTATUS_PWM2TF_Msk                  (1ul << PWM_TSTATUS_PWM2TF_Pos)     /*!< PWM_T::TSTATUS: PWM2TF Mask */

#define PWM_TSTATUS_PWM1TF_Pos                  1                                   /*!< PWM_T::TSTATUS: PWM1TF Position */
#define PWM_TSTATUS_PWM1TF_Msk                  (1ul << PWM_TSTATUS_PWM1TF_Pos)     /*!< PWM_T::TSTATUS: PWM1TF Mask */

#define PWM_TSTATUS_PWM0TF_Pos                  0                                   /*!< PWM_T::TSTATUS: PWM0TF Position */
#define PWM_TSTATUS_PWM0TF_Msk                  (1ul << PWM_TSTATUS_PWM0TF_Pos)     /*!< PWM_T::TSTATUS: PWM0TF Mask */

/* PWM SYNCBUSY0 Bit Field Definitions */
#define PWM_SYNCBUSY0_S_BUSY_Pos                0                                   /*!< PWM_T::SYNCBUSY0: S_BUSY Position */
#define PWM_SYNCBUSY0_S_BUSY_Msk                (1ul << PWM_SYNCBUSY0_S_BUSY_Pos)   /*!< PWM_T::SYNCBUSY0: S_BUSY Mask */

/* PWM SYNCBUSY1 Bit Field Definitions */
#define PWM_SYNCBUSY1_S_BUSY_Pos                0                                   /*!< PWM_T::SYNCBUSY1: S_BUSY Position */
#define PWM_SYNCBUSY1_S_BUSY_Msk                (1ul << PWM_SYNCBUSY1_S_BUSY_Pos)   /*!< PWM_T::SYNCBUSY1: S_BUSY Mask */

/* PWM SYNCBUSY2 Bit Field Definitions */
#define PWM_SYNCBUSY2_S_BUSY_Pos                0                                   /*!< PWM_T::SYNCBUSY2: S_BUSY Position */
#define PWM_SYNCBUSY2_S_BUSY_Msk                (1ul << PWM_SYNCBUSY2_S_BUSY_Pos)   /*!< PWM_T::SYNCBUSY2: S_BUSY Mask */

/* PWM SYNCBUSY3 Bit Field Definitions */
#define PWM_SYNCBUSY3_S_BUSY_Pos                0                                   /*!< PWM_T::SYNCBUSY3: S_BUSY Position */
#define PWM_SYNCBUSY3_S_BUSY_Msk                (1ul << PWM_SYNCBUSY3_S_BUSY_Pos)   /*!< PWM_T::SYNCBUSY3: S_BUSY Mask */
/*@}*/ /* end of group PWM_CONST */
/*@}*/ /* end of group PWM */





/*---------------------- Real Time Clock Controller -------------------------*/
/**
    @addtogroup RTC Real Time Clock Controller (RTC)
    Memory Mapped Structure for RTC Controller
@{ */


typedef struct
{


/**
 * @var RTC_T::INIR
 * Offset: 0x00  RTC Initiation Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |INIR0_Active|RTC Active Status (Read Only)
 * |        |          |0 = RTC is at reset state.
 * |        |          |1 = RTC is at normal active state.
 * |[31:1]  |INIR      |RTC Initiation
 * |        |          |When RTC block is powered on, RTC is at reset state.
 * |        |          |User has to write a number (0xa5eb1357) to INIR to make RTC leaving reset state.
 * |        |          |Once the INIR is written as 0xa5eb1357, the RTC will be in un-reset state permanently.
 * |        |          |The INIR is a write-only field and read value will be always 0.
 * @var RTC_T::AER
 * Offset: 0x04  RTC Access Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |AER       |RTC Register Access Enable Password (Write Only)
 * |        |          |Writing 0xA965 to this register will enable RTC access and keep 1024 RTC clocks.
 * |[16]    |ENF       |RTC Register Access Enable Flag (Read Only)
 * |        |          |0 = RTC register read/write access Disabled.
 * |        |          |1 = RTC register read/write access Enabled.
 * |        |          |This bit will be set after AER[15:0] is load a 0xA965, and will be cleared automatically
 * |        |          |after 1024 RTC clocks.
 * @var RTC_T::FCR
 * Offset: 0x08  RTC Frequency Compensation Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[5:0]   |FRACTION  |Fraction Part
 * |        |          |Formula = (fraction part of detected value) x 60.
 * |        |          |Note: Digit in FCR must be expressed as hexadecimal number.
 * |[11:8]  |INTEGER   |Integer Part
 * @var RTC_T::TLR
 * Offset: 0x0C  Time Loading Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |1SEC      |1-Sec Time Digit (0~9)
 * |[6:4]   |10SEC     |10-Sec Time Digit (0~5)
 * |[11:8]  |1MIN      |1-Min Time Digit (0~9)
 * |[14:12] |10MIN     |10-Min Time Digit (0~5)
 * |[19:16] |1HR       |1-Hour Time Digit (0~9)
 * |[21:20] |10HR      |10-Hour Time Digit (0~2)
 * @var RTC_T::CLR
 * Offset: 0x10  Calendar Loading Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |1DAY      |1-Day Calendar Digit (0~9)
 * |[5:4]   |10DAY     |10-Day Calendar Digit (0~3)
 * |[11:8]  |1MON      |1-Month Calendar Digit (0~9)
 * |[12]    |10MON     |10-Month Calendar Digit (0~1)
 * |[19:16] |1YEAR     |1-Year Calendar Digit (0~9)
 * |[23:20] |10YEAR    |10-Year Calendar Digit (0~9)
 * @var RTC_T::TSSR
 * Offset: 0x14  Time Scale Selection Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |24H_12H   |24-Hour / 12-Hour Time Scale Selection
 * |        |          |It indicates that RTC TLR and TAR counter are in 24-hour time scale or 12-hour time scale.
 * |        |          |0 = 24-hour time scale selected.
 * |        |          |1 = 24-hour time scale selected.
 * @var RTC_T::DWR
 * Offset: 0x18  Day of the Week Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[2:0]   |DWR       |Day Of The Week Register
 * |        |          |000 = Sunday.
 * |        |          |001 = Monday.
 * |        |          |010 = Tuesday.
 * |        |          |011 = Wednesday.
 * |        |          |100 = Thursday.
 * |        |          |101 = Friday.
 * |        |          |110 = Saturday.
 * |        |          |111 = Reserved.
 * @var RTC_T::TAR
 * Offset: 0x1C  Time Alarm Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |1SEC      |1-Sec Time Digit of Alarm Setting (0~9)
 * |[6:4]   |10SEC     |10-Sec Time Digit of Alarm Setting (0~5)
 * |[11:8]  |1MIN      |1-Min Time Digit of Alarm Setting (0~9)
 * |[14:12] |10MIN     |10-Min Time Digit of Alarm Setting (0~5)
 * |[19:16] |1HR       |1-Hour Time Digit of Alarm Setting (0~9)
 * |[21:20] |10HR      |10-Hour Time Digit of Alarm Setting (0~2)
 * @var RTC_T::CAR
 * Offset: 0x20  Calendar Alarm Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |1DAY      |1-Day Calendar Digit of Alarm Setting (0~9)
 * |[5:4]   |10DAY     |10-Day Calendar Digit of Alarm Setting (0~3)
 * |[11:8]  |1MON      |1-Month Calendar Digit of Alarm Setting (0~9)
 * |[12]    |10MON     |10-Month Calendar Digit of Alarm Setting (0~1)
 * |[19:16] |1YEAR     |1-Year Calendar Digit of Alarm Setting (0~9)
 * |[23:20] |10YEAR    |10-Year Calendar Digit of Alarm Setting (0~9)
 * @var RTC_T::LIR
 * Offset: 0x24  Leap Year Indicator Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |LIR       |Leap Year Indication Register (Read Only)
 * |        |          |0 = This year is not a leap year.
 * |        |          |1 = This year is a leap year.
 * @var RTC_T::RIER
 * Offset: 0x28  RTC Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |AIER      |Alarm Interrupt Enable
 * |        |          |This bit is used to enable/disable RTC Alarm Interrupt, and generate an interrupt signal if
 * |        |          |AIF (RIIR[0] RTC Alarm Interrupt Flag) is set to 1.
 * |        |          |0 = RTC Alarm Interrupt Disabled.
 * |        |          |1 = RTC Alarm Interrupt Enabled.
 * |        |          |Note: This bit will also trigger a wake-up event while system runs in Idle/Power-down mode
 * |        |          |and RTC Alarm Interrupt signal generated.
 * |[1]     |TIER      |Time Tick Interrupt Enable
 * |        |          |This bit is used to enable/disable RTC Time Tick Interrupt, and generate an interrupt signal
 * |        |          |if TIF (RIIR[1] RTC Time Tick Interrupt Flag) is set to 1.
 * |        |          |0 = RTC Time Tick Interrupt Disabled.
 * |        |          |1 = RTC Time Tick Interrupt Enabled.
 * |        |          |Note: This bit will also trigger a wake-up event while system runs in Idle/Power-down mode
 * |        |          |and RTC Time Tick Interrupt signal generated.
 * |[2]     |SNOOPIER  |Snoop Detection Interrupt Enable
 * |        |          |This bit is used to enable/disable RTC Snoop Detection Interrupt, and generate an interrupt
 * |        |          |signal if SNOOPIF (RIIR[2] RTC Snoop Detection Interrupt Flag) is set to 1.
 * |        |          |0 = Snoop detected interrupt Disabled.
 * |        |          |1 = Snoop detected interrupt Enabled.
 * |        |          |Note: This bit will also trigger a wake-up event while system runs in Idle/Power-down mode
 * |        |          |and RTC Snoop Interrupt signal generated.
 * @var RTC_T::RIIR
 * Offset: 0x2C  RTC Interrupt Indicator Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |AIF       |RTC Alarm Interrupt Flag
 * |        |          |When RTC time counters TLR and CLR match the alarm setting time registers TAR and CAR, this
 * |        |          |bit will be set to 1 and an interrupt will be generated if RTC Alarm Interrupt enabled AIER
 * |        |          |(RIER[0]) is set to 1.
 * |        |          |Chip will be wake-up if RTC Alarm Interrupt is enabled when chip is at Power-down mode.
 * |        |          |0 = Alarm condition is not matched.
 * |        |          |1 = Alarm condition is matched.
 * |        |          |Note: Write 1 to clear this bit.
 * |[1]     |TIF       |RTC Time Tick Interrupt Flag
 * |        |          |When RTC time tick happened, this bit will be set to 1 and an interrupt will be generated if
 * |        |          |RTC Tick Interrupt enabled TIER (RIER[1]) is set to 1.
 * |        |          |Chip will also be wake-up if RTC Tick Interrupt is enabled and this bit is set to 1 when
 * |        |          |chip is running at Power-down mode.
 * |        |          |0 = Tick condition does not occur.
 * |        |          |1 = Tick condition occur.
 * |        |          |Note: Write 1 to clear to clear this bit.
 * |[2]     |SNOOPIF   |Snoop Detection Interrupt Flag
 * |        |          |When snooper pin transition event is detected, this bit is set to 1 and an interrupt is
 * |        |          |generated if Snoop Detection Interrupt enabled SNOOPIER (RIER[2]) is set to1.
 * |        |          |Chip will be wake-up from Power-down mode if Snoop Detection Interrupt is enabled.
 * |        |          |0 = No snoop event is detected.
 * |        |          |1 = Snoop event is detected.
 * |        |          |Note: Write 1 to clear this bit.
 * @var RTC_T::TTR
 * Offset: 0x30  RTC Time Tick Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[2:0]   |TTR       |Time Tick Register
 * |        |          |These bits are used to select RTC time tick period for Periodic Time Tick Interrupt request.
 * |        |          |000 = Time tick is 1 second.
 * |        |          |001 = Time tick is 1/2 second.
 * |        |          |010 = Time tick is 1/4 second.
 * |        |          |011 = Time tick is 1/8 second.
 * |        |          |100 = Time tick is 1/16 second.
 * |        |          |101 = Time tick is 1/32 second.
 * |        |          |110 = Time tick is 1/64 second.
 * |        |          |111 = Time tick is 1/28 second.
 * |        |          |Note: This register can be read back after the RTC register access enable bit ENF (AER[16])
 * |        |          |is active.
 * @var RTC_T::SPRCTL
 * Offset: 0x3C  RTC Spare Functional Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |SNOOPEN   |Snoop Detection Enable
 * |        |          |0 = Snoop detection function Disabled.
 * |        |          |1 = Snoop detection function Enabled.
 * |[1]     |SNOOPLEVEL|Snoop Detection Level Selection
 * |        |          |This bit controls snoop detect event is high level/rising edge or low level/falling edge.
 * |        |          |0 = Low level/Falling edge detection.
 * |        |          |1 = High level/Rising edge detection.
 * |[2]     |SPREN     |SPR Register Enable
 * |        |          |0 = Spare register is Disabled.
 * |        |          |1 = Spare register is Enabled.
 * |        |          |Note: When spare register is disabled, RTC SPR0 ~ SPR19 cannot be accessed.
 * |[3]     |SNOOPMODE |Snoop Detection Mode Selection
 * |        |          |This bit controls snoop detect event is edge or level detection.
 * |        |          |0 = Level detection.
 * |        |          |1 = Edge detection.
 * |[5]     |SPRCFLG   |Spare Register Clear Flag
 * |        |          |This bit indicates if the SPR0 ~ SPR19 content is cleared when snoop specify event is
 * |        |          |detected.
 * |        |          |0 = Spare register content is not cleared.
 * |        |          |1 = Spare register content is cleared.
 * |        |          |Note: Writes 1 to clear this bit.
 * |[7]     |SPRRDY    |SPR Register Ready
 * |        |          |This bit indicates if the registers SPRCTL, SPR0 ~ SPR19 are ready to be accessed.
 * |        |          |After user writing registers SPRCTL, SPR0 ~ SPR19, read this bit to check if these registers
 * |        |          |are updated done is necessary.
 * |        |          |0 = SPRCTL, SPR0 ~ SPR19 updating is in progress.
 * |        |          |1 = SPRCTL, SPR0 ~ SPR19 are updated done and ready to be accessed.
 * |        |          |Note: This bit is read only and any write to it won't take any effect.
 * @var RTC_T::SPR
 * Offset: 0x40  RTC Spare Register 0 ~ 19
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |SPARE     |SPARE Register
 * |        |          |This field is used to store back-up information defined by software.
 * |        |          |This field will be cleared by hardware automatically once a snooper pin event is detected.
 * |        |          |Before store back-up information in to SPARE register, software should write 0xA965 to AER
 * |        |          |to make sure register read/write enable.
 */

    __IO uint32_t INIR;          /* Offset: 0x00  RTC Initiation Register                                            */
    __IO uint32_t AER;           /* Offset: 0x04  RTC Access Enable Register                                         */
    __IO uint32_t FCR;           /* Offset: 0x08  RTC Frequency Compensation Register                                */
    __IO uint32_t TLR;           /* Offset: 0x0C  Time Loading Register                                              */
    __IO uint32_t CLR;           /* Offset: 0x10  Calendar Loading Register                                          */
    __IO uint32_t TSSR;          /* Offset: 0x14  Time Scale Selection Register                                      */
    __IO uint32_t DWR;           /* Offset: 0x18  Day of the Week Register                                           */
    __IO uint32_t TAR;           /* Offset: 0x1C  Time Alarm Register                                                */
    __IO uint32_t CAR;           /* Offset: 0x20  Calendar Alarm Register                                            */
    __I  uint32_t LIR;           /* Offset: 0x24  Leap Year Indicator Register                                       */
    __IO uint32_t RIER;          /* Offset: 0x28  RTC Interrupt Enable Register                                      */
    __IO uint32_t RIIR;          /* Offset: 0x2C  RTC Interrupt Indicator Register                                   */
    __IO uint32_t TTR;           /* Offset: 0x30  RTC Time Tick Register                                             */
    __I  uint32_t RESERVED[2];  
    __IO uint32_t SPRCTL;        /* Offset: 0x3C  RTC Spare Functional Control Register                              */
    __IO uint32_t SPR[20];       /* Offset: 0x40  RTC Spare Register 0 ~ 19                                          */

} RTC_T;



/**
    @addtogroup RTC_CONST RTC Bit Field Definition
    Constant Definitions for RTC Controller
@{ */

/* RTC INIR Bit Field Definitions */
#define RTC_INIR_INIR_Pos       0                                               /*!< RTC_T::INIR: INIR Position */
#define RTC_INIR_INIR_Msk       (0xFFFFFFFFul << RTC_INIR_INIR_Pos)             /*!< RTC_T::INIR: INIR Mask */

#define RTC_INIR_ACTIVE_Pos     0                                               /*!< RTC_T::INIR: ACTIVE Position */
#define RTC_INIR_ACTIVE_Msk     (1ul << RTC_INIR_ACTIVE_Pos)                    /*!< RTC_T::INIR: ACTIVE Mask */

/* RTC AER Bit Field Definitions */
#define RTC_AER_ENF_Pos         16                                              /*!< RTC_T::AER: ENF Position */
#define RTC_AER_ENF_Msk         (1ul << RTC_AER_ENF_Pos)                        /*!< RTC_T::AER: ENF Mask */

#define RTC_AER_AER_Pos         0                                               /*!< RTC_T::AER: AER Position */
#define RTC_AER_AER_Msk         (0xFFFFul << RTC_AER_AER_Pos)                   /*!< RTC_T::AER: AER Mask */

/* RTC FCR Bit Field Definitions */
#define RTC_FCR_INTEGER_Pos     8                                               /*!< RTC_T::FCR: INTEGER Position */
#define RTC_FCR_INTEGER_Msk     (0xFul << RTC_FCR_INTEGER_Pos)                  /*!< RTC_T::FCR: INTEGER Mask */

#define RTC_FCR_FRACTION_Pos    0                                               /*!< RTC_T::FCR: FRACTION Position */
#define RTC_FCR_FRACTION_Msk    (0x3Ful << RTC_FCR_FRACTION_Pos)                /*!< RTC_T::FCR: FRACTION Mask */

/* RTC TLR Bit Field Definitions */
#define RTC_TLR_10HR_Pos        20                                              /*!< RTC_T::TLR: 10HR Position */
#define RTC_TLR_10HR_Msk        (0x3ul << RTC_TLR_10HR_Pos)                     /*!< RTC_T::TLR: 10HR Mask */

#define RTC_TLR_1HR_Pos         16                                              /*!< RTC_T::TLR: 1HR Position */
#define RTC_TLR_1HR_Msk         (0xFul << RTC_TLR_1HR_Pos)                      /*!< RTC_T::TLR: 1HR Mask */

#define RTC_TLR_10MIN_Pos       12                                              /*!< RTC_T::TLR: 10MIN Position */
#define RTC_TLR_10MIN_Msk       (0x7ul << RTC_TLR_10MIN_Pos)                    /*!< RTC_T::TLR: 10MIN Mask */

#define RTC_TLR_1MIN_Pos        8                                               /*!< RTC_T::TLR: 1MIN Position */
#define RTC_TLR_1MIN_Msk        (0xFul << RTC_TLR_1MIN_Pos)                     /*!< RTC_T::TLR: 1MIN Mask */

#define RTC_TLR_10SEC_Pos       4                                               /*!< RTC_T::TLR: 10SEC Position */
#define RTC_TLR_10SEC_Msk       (0x7ul << RTC_TLR_10SEC_Pos)                    /*!< RTC_T::TLR: 10SEC Mask */

#define RTC_TLR_1SEC_Pos        0                                               /*!< RTC_T::TLR: 1SEC Position */
#define RTC_TLR_1SEC_Msk        (0xFul << RTC_TLR_1SEC_Pos)                     /*!< RTC_T::TLR: 1SEC Mask */

/* RTC CLR Bit Field Definitions */
#define RTC_CLR_10YEAR_Pos      20                                              /*!< RTC_T::CLR: 10YEAR Position */
#define RTC_CLR_10YEAR_Msk      (0xFul << RTC_CLR_10YEAR_Pos)                   /*!< RTC_T::CLR: 10YEAR Mask */

#define RTC_CLR_1YEAR_Pos       16                                              /*!< RTC_T::CLR: 1YEAR Position */
#define RTC_CLR_1YEAR_Msk       (0xFul << RTC_CLR_1YEAR_Pos)                    /*!< RTC_T::CLR: 1YEAR Mask */

#define RTC_CLR_10MON_Pos       12                                              /*!< RTC_T::CLR: 10MON Position */
#define RTC_CLR_10MON_Msk       (1ul << RTC_CLR_10MON_Pos)                      /*!< RTC_T::CLR: 10MON Mask */

#define RTC_CLR_1MON_Pos        8                                               /*!< RTC_T::CLR: 1MON Position */
#define RTC_CLR_1MON_Msk        (0xFul << RTC_CLR_1MON_Pos)                     /*!< RTC_T::CLR: 1MON Mask */

#define RTC_CLR_10DAY_Pos       4                                               /*!< RTC_T::CLR: 10DAY Position */
#define RTC_CLR_10DAY_Msk       (0x3ul << RTC_CLR_10DAY_Pos)                    /*!< RTC_T::CLR: 10DAY Mask */

#define RTC_CLR_1DAY_Pos        0                                               /*!< RTC_T::CLR: 1DAY Position */
#define RTC_CLR_1DAY_Msk        (0xFul << RTC_CLR_1DAY_Pos)                     /*!< RTC_T::CLR: 1DAY Mask */

/* RTC TSSR Bit Field Definitions */
#define RTC_TSSR_24H_12H_Pos    0                                               /*!< RTC_T::TSSR: 24H_12H Position */
#define RTC_TSSR_24H_12H_Msk    (1ul << RTC_TSSR_24H_12H_Pos)                   /*!< RTC_T::TSSR: 24H_12H Mask */

/* RTC DWR Bit Field Definitions */
#define RTC_DWR_DWR_Pos         0                                               /*!< RTC_T::DWR: DWR Position */
#define RTC_DWR_DWR_Msk         (0x7ul << RTC_DWR_DWR_Pos)                      /*!< RTC_T::DWR: DWR Mask */

/* RTC TAR Bit Field Definitions */
#define RTC_TAR_10HR_Pos        20                                              /*!< RTC_T::TAR: 10HR Position */
#define RTC_TAR_10HR_Msk        (0x3ul << RTC_TAR_10HR_Pos)                     /*!< RTC_T::TAR: 10HR Mask */

#define RTC_TAR_1HR_Pos         16                                              /*!< RTC_T::TAR: 1HR Position */
#define RTC_TAR_1HR_Msk         (0xFul << RTC_TAR_1HR_Pos)                      /*!< RTC_T::TAR: 1HR Mask */

#define RTC_TAR_10MIN_Pos       12                                              /*!< RTC_T::TAR: 10MIN Position */
#define RTC_TAR_10MIN_Msk       (0x7ul << RTC_TAR_10MIN_Pos)                    /*!< RTC_T::TAR: 10MIN Mask */

#define RTC_TAR_1MIN_Pos        8                                               /*!< RTC_T::TAR: 1MIN Position */
#define RTC_TAR_1MIN_Msk        (0xFul << RTC_TAR_1MIN_Pos)                     /*!< RTC_T::TAR: 1MIN Mask */

#define RTC_TAR_10SEC_Pos       4                                               /*!< RTC_T::TAR: 10SEC Position */
#define RTC_TAR_10SEC_Msk       (0x7ul << RTC_TAR_10SEC_Pos)                    /*!< RTC_T::TAR: 10SEC Mask */

#define RTC_TAR_1SEC_Pos        0                                               /*!< RTC_T::TAR: 1SEC Position */
#define RTC_TAR_1SEC_Msk        (0xFul << RTC_TAR_1SEC_Pos)                     /*!< RTC_T::TAR: 1SEC Mask */

/* RTC CAR Bit Field Definitions */
#define RTC_CAR_10YEAR_Pos      20                                              /*!< RTC_T::CAR: 10YEAR Position */
#define RTC_CAR_10YEAR_Msk      (0xFul << RTC_CAR_10YEAR_Pos)                   /*!< RTC_T::CAR: 10YEAR Mask */

#define RTC_CAR_1YEAR_Pos       16                                              /*!< RTC_T::CAR: 1YEAR Position */
#define RTC_CAR_1YEAR_Msk       (0xFul << RTC_CAR_1YEAR_Pos)                    /*!< RTC_T::CAR: 1YEAR Mask */

#define RTC_CAR_10MON_Pos       12                                              /*!< RTC_T::CAR: 10MON Position */
#define RTC_CAR_10MON_Msk       (1ul << RTC_CAR_10MON_Pos)                      /*!< RTC_T::CAR: 10MON Mask */

#define RTC_CAR_1MON_Pos        8                                               /*!< RTC_T::CAR: 1MON Position */
#define RTC_CAR_1MON_Msk        (0xFul << RTC_CAR_1MON_Pos)                     /*!< RTC_T::CAR: 1MON Mask */

#define RTC_CAR_10DAY_Pos       4                                               /*!< RTC_T::CAR: 10DAY Position */
#define RTC_CAR_10DAY_Msk       (0x3ul << RTC_CAR_10DAY_Pos)                    /*!< RTC_T::CAR: 10DAY Mask */

#define RTC_CAR_1DAY_Pos        0                                               /*!< RTC_T::CAR: 1DAY Position */
#define RTC_CAR_1DAY_Msk        (0xFul << RTC_CAR_1DAY_Pos)                     /*!< RTC_T::CAR: 1DAY Mask */

/* RTC LIR Bit Field Definitions */
#define RTC_LIR_LIR_Pos         0                                               /*!< RTC_T::LIR: LIR Position */
#define RTC_LIR_LIR_Msk         (1ul << RTC_LIR_LIR_Pos)                        /*!< RTC_T::LIR: LIR Mask */

/* RTC RIER Bit Field Definitions */
#define RTC_RIER_SNOOPIER_Pos   2                                               /*!< RTC_T::RIER: SNOOPIER Position */
#define RTC_RIER_SNOOPIER_Msk   (1ul << RTC_RIER_SNOOPIER_Pos)                  /*!< RTC_T::RIER: SNOOPIER Mask */

#define RTC_RIER_TIER_Pos       1                                               /*!< RTC_T::RIER: TIER Position */
#define RTC_RIER_TIER_Msk       (1ul << RTC_RIER_TIER_Pos)                      /*!< RTC_T::RIER: TIER Mask */

#define RTC_RIER_AIER_Pos       0                                               /*!< RTC_T::RIER: AIER Position */
#define RTC_RIER_AIER_Msk       (1ul << RTC_RIER_AIER_Pos)                      /*!< RTC_T::RIER: AIER Mask */

/* RTC RIIR Bit Field Definitions */
#define RTC_RIIR_SNOOPIF_Pos    2                                               /*!< RTC_T::RIIR: SNOOPIF Position */
#define RTC_RIIR_SNOOPIF_Msk    (1ul << RTC_RIIR_SNOOPIF_Pos)                   /*!< RTC_T::RIIR: SNOOPIF Mask */

#define RTC_RIIR_TIF_Pos        1                                               /*!< RTC_T::RIIR: TIF Position */
#define RTC_RIIR_TIF_Msk        (1ul << RTC_RIIR_TIF_Pos)                       /*!< RTC_T::RIIR: TIF Mask */

#define RTC_RIIR_AIF_Pos        0                                               /*!< RTC_T::RIIR: AIF Position */
#define RTC_RIIR_AIF_Msk        (1ul << RTC_RIIR_AIF_Pos)                       /*!< RTC_T::RIIR: AIF Mask */

/* RTC TTR Bit Field Definitions */
#define RTC_TTR_TTR_Pos         0                                               /*!< RTC_T::TTR: TTR Position */
#define RTC_TTR_TTR_Msk         (0x7ul << RTC_TTR_TTR_Pos)                      /*!< RTC_T::TTR: TTR Mask */

/* RTC SPRCTL Bit Field Definitions */
#define RTC_SPRCTL_SPRRDY_Pos       7                                           /*!< RTC_T::SPRCTL: SPRRDY Position */
#define RTC_SPRCTL_SPRRDY_Msk       (1ul << RTC_SPRCTL_SPRRDY_Pos)              /*!< RTC_T::SPRCTL: SPRRDY Mask */

#define RTC_SPRCTL_SPRCFLG_Pos      5                                           /*!< RTC_T::SPRCTL: SPRCFLG Position */
#define RTC_SPRCTL_SPRCFLG_Msk      (1ul << RTC_SPRCTL_SPRCFLG_Pos)             /*!< RTC_T::SPRCTL: SPRCFLG Mask */

#define RTC_SPRCTL_SNOOPMODE_Pos    3                                           /*!< RTC_T::SPRCTL: SNOOPMODE Position */
#define RTC_SPRCTL_SNOOPMODE_Msk    (1ul << RTC_SPRCTL_SNOOPMODE_Pos)           /*!< RTC_T::SPRCTL: SNOOPMODE Mask */

#define RTC_SPRCTL_SPREN_Pos        2                                           /*!< RTC_T::SPRCTL: SPREN Position */
#define RTC_SPRCTL_SPREN_Msk        (1ul << RTC_SPRCTL_SPREN_Pos)               /*!< RTC_T::SPRCTL: SPREN Mask */

#define RTC_SPRCTL_SNOOPLEVEL_Pos   1                                           /*!< RTC_T::SPRCTL: SNOOPLEVEL Position */
#define RTC_SPRCTL_SNOOPLEVEL_Msk   (1ul << RTC_SPRCTL_SNOOPLEVEL_Pos)          /*!< RTC_T::SPRCTL: SNOOPLEVEL Mask */

#define RTC_SPRCTL_SNOOPEN_Pos      0                                           /*!< RTC_T::SPRCTL: SNOOPEN Position */
#define RTC_SPRCTL_SNOOPEN_Msk      (1ul << RTC_SPRCTL_SNOOPEN_Pos)             /*!< RTC_T::SPRCTL: SNOOPEN Mask */
/*@}*/ /* end of group RTC_CONST */
/*@}*/ /* end of group RTC */




/*---------------------- Smart Card Host Interface Controller -------------------------*/
/**
    @addtogroup SC Smart Card Host Interface Controller (SC)
    Memory Mapped Structure for SC Controller
@{ */


typedef struct
{


    /**
 * @var SC_T::RBR
 * Offset: 0x00  SC Receiving Buffer Register.
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |RBR       |Receiving Buffer
 * |        |          |By reading RBR, the SC will return an 8-bit received data.
 * @var SC_T::THR
 * Offset: 0x00  SC Transmit Holding Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |THR       |Transmit Holding Buffer
 * |        |          |By writing data to THR, the SC will send out an 8-bit data.
 * |        |          |Note: If SC_CEN(SC_CTL[0]) is not enabled, THR cannot be programmed.
 * @var SC_T::CTL
 * Offset: 0x04  SC Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |SC_CEN    |SC Engine Enable Control
 * |        |          |Set this bit to 1 to enable SC operation.
 * |        |          |If this bit is cleared, SC will force all transition to IDLE state.
 * |[1]     |DIS_RX    |RX Transition Disable Control
 * |        |          |0 = The receiver Enabled.
 * |        |          |1 = The receiver Disabled.
 * |        |          |Note:
 * |        |          |If AUTO_CON_EN (SC_CTL[3])is enabled, these fields must be ignored.
 * |[2]     |DIS_TX    |TX Transition Disable Control
 * |        |          |0 = The transceiver Enabled.
 * |        |          |1 = The transceiver Disabled.
 * |[3]     |AUTO_CON_EN|Auto Convention Enable Control
 * |        |          |0 = Auto-convention Disabled.
 * |        |          |1 = Auto-convention Enabled.
 * |        |          |When hardware receives TS in answer to reset state and the TS is direct convention,
 * |        |          |CON_SEL(SC_CTL[5:4]) will be set to 00 automatically, otherwise if the TS is inverse
 * |        |          |convention, and CON_SEL (SC_CTL[5:4]) will be set to 11.
 * |        |          |If software enables auto convention function, the setting step must be done before Answer to
 * |        |          |Reset state and the first data must be 0x3B or 0x3F.
 * |        |          |After hardware received first data and stored it at buffer, hardware will decided the
 * |        |          |convention and change the CON_SEL (SC_CTL[5:4]) bits automatically.
 * |        |          |If the first data is not 0x3B or 0x3F, hardware will generate an interrupt INT_ACON_ERR (if
 * |        |          |ACON_ERR IE (SC_IER[10]) = 1 to CPU.
 * |[5:4]   |CON_SEL   |Convention Selection
 * |        |          |00 = Direct convention.
 * |        |          |01 = Reserved.
 * |        |          |10 = Reserved.
 * |        |          |11 = Inverse convention.
 * |        |          |Note:
 * |        |          |If AUTO_CON_EN(SC_CTL[3]) enabled, this fields are ignored.
 * |[7:6]   |RX_FTRI_LEV|Rx Buffer Trigger Level
 * |        |          |When the number of bytes in the receiving buffer equals the RX_FTRI_LEV, the RDA_IF will be
 * |        |          |set (if IER [RDA_IEN] is enabled, an interrupt will be generated).
 * |        |          |00 = INTR_RDA Trigger Level with 01 Bytes.
 * |        |          |01 = INTR_RDA Trigger Level with 02 Bytes.
 * |        |          |10 = INTR_RDA Trigger Level with 03 Bytes.
 * |        |          |11 = Reserved.
 * |[12:8]  |BGT       |Block Guard Time (BGT)
 * |        |          |Block guard time means the minimum bit length between the leading edges of two consecutive
 * |        |          |characters between different transfer directions.
 * |        |          |This field indicates the counter for the bit length of block guard time.
 * |        |          |According to ISO7816-3, in T = 0 mode, software must fill 15 (real block guard time = 16.5)
 * |        |          |to this field; in T = 1 mode, software must fill 21 (real block guard time = 22.5) to it.
 * |        |          |Note:
 * |        |          |The real block guard time is BGT + 1.
 * |[14:13] |TMR_SEL   |Timer Selection
 * |        |          |00 = All internal timer function Disabled.
 * |        |          |01 = Internal 24 bit timer Enabled.
 * |        |          |Software can configure it by setting SC_TMR0 [23:0].
 * |        |          |SC_TMR1 and SC_TMR2 will be ignored in this mode.
 * |        |          |10 = internal 24 bit timer and 8 bit internal timer Enabled.
 * |        |          |Software can configure the 24 bit timer by setting SC_TMR0 [23:0] and configure the 8 bit
 * |        |          |timer by setting SC_TMR1[7:0].
 * |        |          |SC_TMR2 will be ignored in this mode.
 * |        |          |11 = Internal 24 bit timer and two 8 bit timers Enabled.
 * |        |          |Software can configure them by setting SC_TMR0 [23:0], SC_TMR1 [7:0] and SC_TMR2 [7:0].
 * |[15]    |SLEN      |Stop Bit Length
 * |        |          |This field indicates the length of stop bit.
 * |        |          |0 = The stop bit length is 2 ETU.
 * |        |          |1= The stop bit length is 1 ETU.
 * |        |          |Note:
 * |        |          |The default stop bit length is 2. SMC and UART adopts SLEN to program the stop bit length
 * |[18:16] |RX_ERETRY |RX Error Retry Count Number
 * |        |          |This field indicates the maximum number of receiver retries that are allowed when parity
 * |        |          |error has occurred
 * |        |          |Note1: The real retry number is RX_ERETRY + 1, so 8 is the maximum retry number.
 * |        |          |Note2: This field cannot be changed when RX_ERETRY_EN enabled.
 * |        |          |The change flow is to disable RX_ETRTRY_EN first and then fill in new retry value.
 * |[19]    |RX_ERETRY_EN|RX Error Retry Enable Control
 * |        |          |This bit enables receiver retry function when parity error has occurred.
 * |        |          |0 = RX error retry function Disabled.
 * |        |          |1 = RX error retry function Enabled.
 * |        |          |Note: Software must fill in the RX_ERETRY value before enabling this bit.
 * |[22:20] |TX_ERETRY |TX Error Retry Count Number
 * |        |          |This field indicates the maximum number of transmitter retries that are allowed when parity
 * |        |          |error has occurred.
 * |        |          |Note1: The real retry number is TX_ERETRY + 1, so 8 is the maximum retry number.
 * |        |          |Note2: This field cannot be changed when TX_ERETRY_EN enabled.
 * |        |          |The change flow is to disable TX_ETRTRY_EN first and then fill in new retry value.
 * |[23]    |TX_ERETRY_EN|TX Error Retry Enable Control
 * |        |          |This bit enables transmitter retry function when parity error has occurred.
 * |        |          |0 = TX error retry function Disabled.
 * |        |          |1 = TX error retry function Enabled.
 * |[25:24] |CD_DEB_SEL|Card Detect De-Bounce Selection
 * |        |          |This field indicates the card detect de-bounce selection.
 * |        |          |00 = De-bounce sample card insert once per 384 (128 * 3) engine clocks and de-bounce sample
 * |        |          |card removal once per 128 engine clocks.
 * |        |          |01 = De-bounce sample card insert once per 192 (64 * 3) engine clocks and de-bounce sample
 * |        |          |card removal once per 64 engine clocks.
 * |        |          |10 = De-bounce sample card insert once per 96 (32 * 3) engine clocks and de-bounce sample
 * |        |          |card removal once per 32 engine clocks.
 * |        |          |11 = De-bounce sample card insert once per 48 (16 * 3) engine clocks and de-bounce sample
 * |        |          |card removal once per 16 engine clocks.
 * |[30]    |SYNC      |SYNC Flag Indicator
 * |        |          |Due to synchronization, software should check this bit before writing a new value to
 * |        |          |RX_ERETRY and TX_ERETRY.
 * |        |          |0 = synchronizing is completion, user can write new data to RX_ERETRY and TX_ERETRY.
 * |        |          |1 = Last value is synchronizing.
 * |        |          |Note: This bit is read only.
 * @var SC_T::ALTCTL
 * Offset: 0x08  SC Alternate Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TX_RST    |TX Software Reset
 * |        |          |When TX_RST is set, all the bytes in the transmit buffer and TX internal state machine will
 * |        |          |be cleared.
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the TX internal state machine and pointers.
 * |        |          |Note:
 * |        |          |This bit will be auto cleared after reset is complete.
 * |[1]     |RX_RST    |Rx Software Reset
 * |        |          |When RX_RST is set, all the bytes in the receiver buffer and Rx internal state machine will
 * |        |          |be cleared.
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the Rx internal state machine and pointers.
 * |        |          |Note:
 * |        |          |This bit will be auto cleared after reset is complete.
 * |[2]     |DACT_EN   |Deactivation Sequence Generator Enable Control
 * |        |          |This bit enables SC controller to initiate the card by deactivation sequence
 * |        |          |0 = No effect.
 * |        |          |1 = Deactivation sequence generator Enabled.
 * |        |          |Note1:
 * |        |          |When the deactivation sequence completed, this bit will be cleared automatically and the
 * |        |          |INIT_IS(SC_ISR[8]) will be set to 1.
 * |        |          |Note2:
 * |        |          |This field will be cleared by TX_RST (SC_ALTCTL[0]) and RX_RST(SC_ALTCTL[1]).
 * |        |          |So don't fill this bit, TX_RST, and RX_RST at the same time.
 * |        |          |Note3:
 * |        |          |If SC_CEN (SC_CTL[0]) is not enabled, this filed cannot be programmed.
 * |[3]     |ACT_EN    |Activation Sequence Generator Enable Control
 * |        |          |This bit enables SC controller to initiate the card by activation sequence
 * |        |          |0 = No effect.
 * |        |          |1 = Activation sequence generator Enabled.
 * |        |          |Note1:
 * |        |          |When the activation sequence completed, this bit will be cleared automatically and the
 * |        |          |INIT_IS(SC_ISR[8]) will be set to 1.
 * |        |          |Note2:
 * |        |          |This field will be cleared by TX_RST(SC_ALTCTL[0]) and RX_RST(SC_ALTCTL[1]), so don't fill
 * |        |          |this bit, TX_RST(SC_ALTCTL[0]), and RX_RST(SC_ALTCTL[1]) at the same time.
 * |        |          |Note3:
 * |        |          |If SC_CEN(SC_CTL[0]) is not enabled, this filed cannot be programmed.
 * |[4]     |WARST_EN  |Warm Reset Sequence Generator Enable Control
 * |        |          |This bit enables SC controller to initiate the card by warm reset sequence
 * |        |          |0 = No effect.
 * |        |          |1 = Warm reset sequence generator Enabled.
 * |        |          |Note1:
 * |        |          |When the warm reset sequence completed, this bit will be cleared automatically and the
 * |        |          |INIT_IS(SC_ISR[8]) will be set to 1.
 * |        |          |Note2:
 * |        |          |This field will be cleared by TX_RST(SC_ALTCTL[0]) and RX_RST(SC_ALTCTL[1]), so don't fill
 * |        |          |this bit, TX_RST, and RX_RST at the same time.
 * |        |          |Note3:
 * |        |          |If SC_CEN(SC_CTL[0]) is not enabled, this filed cannot be programmed.
 * |[5]     |TMR0_SEN  |Internal Timer0 Start Enable Control
 * |        |          |This bit enables Timer 0 to start counting.
 * |        |          |Software can fill 0 to stop it and set 1 to reload and count.
 * |        |          |0 = Stops counting.
 * |        |          |1 = Start counting.
 * |        |          |Note1:
 * |        |          |This field is used for internal 24 bit timer when TMR_SEL (SC_CTL[14:13]) = 01.
 * |        |          |Note2:
 * |        |          |If the operation mode is not in auto-reload mode (SC_TMR0[26] = 0), this bit will be
 * |        |          |auto-cleared by hardware.
 * |        |          |Note3:
 * |        |          |This field will be cleared by TX_RST(SC_ALTCTL[0]) and RX_RST(SC_ALTCTL[1]).
 * |        |          |So don't fill this bit, TX_RST and RX_RST at the same time.
 * |        |          |Note4: If SC_CEN(SC_CTL[0]) is not enabled, this filed cannot be programmed.
 * |[6]     |TMR1_SEN  |Internal Timer1 Start Enable Control
 * |        |          |This bit enables Timer 1 to start counting.
 * |        |          |Software can fill 0 to stop it and set 1 to reload and count.
 * |        |          |0 = Stops counting.
 * |        |          |1 = Start counting.
 * |        |          |Note1:
 * |        |          |This field is used for internal 8 bit timer when TMR_SEL(SC_CTL[14:13]) = 10 or
 * |        |          |TMR_SEL(SC_CTL[14:13]) = 11.
 * |        |          |Don't filled TMR1_SEN when TMR_SEL(SC_CTL[14:13]) = 00 or TMR_SEL(SC_CTL[14:13]) = 01.
 * |        |          |Note2:
 * |        |          |If the operation mode is not in auto-reload mode (SC_TMR1[26] = 0), this bit will be
 * |        |          |auto-cleared by hardware.
 * |        |          |Note3:
 * |        |          |This field will be cleared by TX_RST(SC_ALTCTL[0]) and RX_RST(SC_ALTCTL[1]), so don't fill
 * |        |          |this bit, TX_RST(SC_ALTCTL[0]), and RX_RST(SC_ALTCTL[1]) at the same time.
 * |        |          |Note4:
 * |        |          |If SC_CEN(SC_CTL[0]) is not enabled, this filed cannot be programmed.
 * |[7]     |TMR2_SEN  |Internal Timer2 Start Enable Control
 * |        |          |This bit enables Timer 2 to start counting.
 * |        |          |Software can fill 0 to stop it and set 1 to reload and count.
 * |        |          |0 = Stops counting.
 * |        |          |1 = Start counting.
 * |        |          |Note1:
 * |        |          |This field is used for internal 8 bit timer when TMR_SEL(SC_CTL[14:13]) = 11.
 * |        |          |Don't filled TMR2_SEN when TMR_SEL(SC_CTL[14:13]) = 00 or TMR_SEL(SC_CTL[14:13]) = 01 or
 * |        |          |TMR_SEL(SC_CTL[14:13]) = 10.
 * |        |          |Note2:
 * |        |          |If the operation mode is not in auto-reload mode (SC_TMR2[26] = 0), this bit will be
 * |        |          |auto-cleared by hardware.
 * |        |          |Note3:
 * |        |          |This field will be cleared by TX_RST(SC_ALTCTL[0]) and RX_RST(SC_ALTCTL[1]).
 * |        |          |So don't fill this bit, TX_RST(SC_ALTCTL[0]), and RX_RST(SC_ALTCTL[1]) at the same time.
 * |        |          |Note4:
 * |        |          |If SC_CEN(SC_CTL[0]) is not enabled, this filed cannot be programmed.
 * |[9:8]   |INIT_SEL  |Initial Timing Selection
 * |        |          |This fields indicates the timing of hardware initial state (activation or warm-reset or
 * |        |          |deactivation).
 * |        |          |Unit: SC clock
 * |        |          |Activation: refer to SC Activation Sequence in Figure 5-100.
 * |        |          |Warm-reset: refer to Warm-Reset Sequence in Figure 5-101.
 * |        |          |Deactivation: refer to Deactivation Sequence in Figure 5-102.
 * |[12]    |RX_BGT_EN |Receiver Block Guard Time Function Enable Control
 * |        |          |0 = Receiver block guard time function Disabled.
 * |        |          |1 = Receiver block guard time function Enabled.
 * |[13]    |TMR0_ATV  |Internal Timer0 Active State (Read Only)
 * |        |          |This bit indicates the timer counter status of timer0.
 * |        |          |0 = Timer0 is not active.
 * |        |          |1 = Timer0 is active.
 * |[14]    |TMR1_ATV  |Internal Timer1 Active State (Read Only)
 * |        |          |This bit indicates the timer counter status of timer1.
 * |        |          |0 = Timer1 is not active.
 * |        |          |1 = Timer1 is active.
 * |[15]    |TMR2_ATV  |Internal Timer2 Active State (Read Only)
 * |        |          |This bit indicates the timer counter status of timer2.
 * |        |          |0 = Timer2 is not active.
 * |        |          |1 = Timer2 is active.
 * |[16]    |OUTSEL    |Smartcard Data Pin Output Mode Selection
 * |        |          |Use this bit to select smartcard data pin (SC_DATA) output mode
 * |        |          |0 = Quasi mode.
 * |        |          |1 = Open-drain mode.
 * @var SC_T::EGTR
 * Offset: 0x0C  SC Extend Guard Time Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |EGT       |Extended Guard Time
 * |        |          |This field indicates the extended guard timer value.
 * |        |          |Note:
 * |        |          |The counter is ETU base and the real extended guard time is EGT.
 * @var SC_T::RFTMR
 * Offset: 0x10  SC Receive buffer Time-out Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8:0]   |RFTM      |SC Receiver Buffer Time-Out (ETU Base)
 * |        |          |The time-out counter resets and starts counting whenever the RX buffer received a new data
 * |        |          |word.
 * |        |          |Once the counter decrease to 1 and no new data is received or CPU does not read data by
 * |        |          |reading SC_RBR buffer, a receiver time-out interrupt INT_RTMR will be generated(if
 * |        |          |RTMR_IE(SC_IER[9]) = 1 ).
 * |        |          |Note1: The counter unit is ETU based and the interval of time-out is RFTM + 0.5
 * |        |          |Note2:
 * |        |          |Fill all 0 to this field indicates to disable this function.
 * @var SC_T::ETUCR
 * Offset: 0x14  SC ETU Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[11:0]  |ETU_RDIV  |ETU Rate Divider
 * |        |          |The field indicates the clock rate divider.
 * |        |          |The real ETU is ETU_RDIV + 1.
 * |        |          |Note:
 * |        |          |Software can configure this field, but this field must be greater than 0x004.
 * |[15]    |COMPEN_EN |Compensation Mode Enable Control
 * |        |          |This bit enables clock compensation function.
 * |        |          |When this bit enabled, hardware will alternate between n clock cycles and n-1 clock cycles,
 * |        |          |where n is the value to be written into the ETU_RDIV .
 * |        |          |0 = Compensation function Disabled.
 * |        |          |1 = Compensation function Enabled.
 * @var SC_T::IER
 * Offset: 0x18  SC Interrupt Enable Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RDA_IE    |Receive Data Reach Interrupt Enable Control
 * |        |          |This field is used for received data reaching trigger level RX_FTRI_LEV (SC_CTL[7:6])
 * |        |          |interrupt enable.
 * |        |          |0 = Receive data reach trigger level interrupt Disabled.
 * |        |          |1 = Receive data reach trigger level interrupt Enabled.
 * |[1]     |TXBE_IE   |Transmit Buffer Empty Interrupt Enable Control
 * |        |          |This field is used for transmit buffer empty interrupt enable.
 * |        |          |0 = Transmit buffer empty interrupt Disabled.
 * |        |          |1 = Transmit buffer empty interrupt Enabled.
 * |[2]     |TERR_IE   |Transfer Error Interrupt Enable Control
 * |        |          |This field is used for transfer error interrupt enable.
 * |        |          |The transfer error states is at SC_SR register which includes receiver break error
 * |        |          |RX_EBR_F(SC_SR[6]), frame error RX_EFR_F(SC_SR[5]), parity error RX_EPA_F(SC_SR[4]),
 * |        |          |receiver buffer overflow error RX_OVER_F(SC_SR[0]), transmit buffer overflow error
 * |        |          |TX_OVER_F(SC_SR[8]), receiver retry over limit error RX_OVER_REERR(SC_SR[22]) and
 * |        |          |transmitter retry over limit error TX_OVER_REERR(SC_SR[30]).
 * |        |          |0 = Transfer error interrupt Disabled.
 * |        |          |1 = Transfer error interrupt Enabled.
 * |[3]     |TMR0_IE   |Timer0 Interrupt Enable Control
 * |        |          |This field is used to enable TMR0 interrupt enable.
 * |        |          |0 = Timer0 interrupt Disabled.
 * |        |          |1 = Timer0 interrupt Enabled.
 * |[4]     |TMR1_IE   |Timer1 Interrupt Enable Control
 * |        |          |This field is used to enable the TMR1 interrupt.
 * |        |          |0 = Timer1 interrupt Disabled.
 * |        |          |1 = Timer1 interrupt Enabled.
 * |[5]     |TMR2_IE   |Timer2 Interrupt Enable Control
 * |        |          |This field is used for TMR2 interrupt enable.
 * |        |          |0 = Timer2 interrupt Disabled.
 * |        |          |1 = Timer2 interrupt Enabled.
 * |[6]     |BGT_IE    |Block Guard Time Interrupt Enable Control
 * |        |          |This field is used for block guard time interrupt enable.
 * |        |          |0 = Block guard time Disabled.
 * |        |          |1 = Block guard time Enabled.
 * |[7]     |CD_IE     |Card Detect Interrupt Enable Control
 * |        |          |This field is used for card detect interrupt enable. The card detect status is
 * |        |          |CD_INS_F(SC_SR[12])
 * |        |          |0 = Card detect interrupt Disabled.
 * |        |          |1 = Card detect interrupt Enabled.
 * |[8]     |INIT_IE   |Initial End Interrupt Enable Control
 * |        |          |This field is used for activation (ACT_EN(SC_ALTCTL[3] = 1)), deactivation ((DACT_EN
 * |        |          |SC_ALTCTL[2]) = 1) and warm reset (WARST_EN (SC_ALTCTL [4])) sequence interrupt enable.
 * |        |          |0 = Initial end interrupt Disabled.
 * |        |          |1 = Initial end interrupt Enabled.
 * |[9]     |RTMR_IE   |Receiver Buffer Time-Out Interrupt Enable Control
 * |        |          |This field is used for receiver buffer time-out interrupt enable.
 * |        |          |0 = Receiver buffer time-out interrupt Disabled.
 * |        |          |1 = Receiver buffer time-out interrupt Enabled.
 * |[10]    |ACON_ERR_IE|Auto Convention Error Interrupt Enable Control
 * |        |          |This field is used for auto-convention error interrupt enable.
 * |        |          |0 = Auto-convention error interrupt Disabled.
 * |        |          |1 = Auto-convention error interrupt Enabled.
 * @var SC_T::ISR
 * Offset: 0x1C  SC Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RDA_IS    |Receive Data Reach Interrupt Status Flag (Read Only)
 * |        |          |This field is used for received data reaching trigger level RX_FTRI_LEV (SC_CTL[7:6])
 * |        |          |interrupt status flag.
 * |        |          |Note: This field is the status flag of received data reaching RX_FTRI_LEV (SC_CTL[7:6]).
 * |        |          |If software reads data from SC_RBR and receiver buffer data byte number is less than
 * |        |          |RX_FTRI_LEV (SC_CTL[7:6]), this bit will be cleared automatically.
 * |[1]     |TBE_IS    |Transmit Buffer Empty Interrupt Status Flag (Read Only)
 * |        |          |This field is used for transmit buffer empty interrupt status flag.
 * |        |          |Note: This field is the status flag of transmit buffer empty state.
 * |        |          |If software wants to clear this bit, software must write data to THR(SC_THR[7:0]) buffer and
 * |        |          |then this bit will be cleared automatically.
 * |[2]     |TERR_IS   |Transfer Error Interrupt Status Flag (Read Only)
 * |        |          |This field is used for transfer error interrupt status flag.
 * |        |          |The transfer error states is at SC_SR register which includes receiver break error
 * |        |          |RX_EBR_F(SC_SR[6]), frame error RX_EFR_F(SC_TRSR[5], parity error RX_EPA_F(SC_TRSR[4] and
 * |        |          |receiver buffer overflow error RX_OVER_F(SC_TRSR[0]), transmit buffer overflow error
 * |        |          |TX_OVER_F(SC_TRSR[8]), receiver retry over limit error RX_OVER_REERR(SC_TRSR[22] and
 * |        |          |transmitter retry over limit error TX_OVER_REERR(SC_TRSR[30]).
 * |        |          |Note: This field is the status flag of
 * |        |          |RX_EBR_F(SC_TRSR[6]), RX_EFR_F(SC_TRSR[5]), RX_EPA_F(SC_TRSR[4]), RX_OVER_F(SC_TRSR[0]),
 * |        |          |TX_OVER_F(SC_TRSR[8]), RX_OVER_REERR(SC_TRSR[22]) or TX_OVER_REERR(SC_TRSR[30]).
 * |        |          |So, if software wants to clear this bit, software must write 1 to each field.
 * |[3]     |TMR0_IS   |Timer0 Interrupt Status Flag (Read Only)
 * |        |          |This field is used for TMR0 interrupt status flag.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[4]     |TMR1_IS   |Timer1 Interrupt Status Flag (Read Only)
 * |        |          |This field is used for TMR1 interrupt status flag.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[5]     |TMR2_IS   |Timer2 Interrupt Status Flag (Read Only)
 * |        |          |This field is used for TMR2 interrupt status flag.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[6]     |BGT_IS    |Block   Guard Time Interrupt Status Flag (Read Only)
 * |        |          |This field   is used for block guard time interrupt status flag.
 * |        |          |Note1: This bit is valid when RX_BGT_EN   (SC_ALTCTL[12]) is enabled.
 * |        |          |Note2: This bit is read only, but it can be cleared by   writing "1" to it.
 * |[7]     |CD_IS     |Card Detect Interrupt Status Flag (Read Only)
 * |        |          |This field is used for card detect interrupt status flag.
 * |        |          |The card detect status is CD_INS_F (SC_SR[12]) and CD_REM_F(SC_SR[11]).
 * |        |          |Note:
 * |        |          |This field is the status flag of CD_INS_F(SC_SR[12]) or CD_REM_F(SC_TRSR[11])].
 * |        |          |So if software wants to clear this bit, software must write 1 to this field.
 * |[8]     |INIT_IS   |Initial End Interrupt Status Flag (Read Only)
 * |        |          |This field is used for activation (ACT_EN(SC_ALTCTL[3])), deactivation (DACT_EN
 * |        |          |(SC_ALTCTL[2])) and warm reset (WARST_EN (SC_ALTCTL[4])) sequence interrupt status flag.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[9]     |RTMR_IS   |Receiver Buffer Time-Out Interrupt Status Flag (Read Only)
 * |        |          |This field is used for receiver buffer time-out interrupt status flag.
 * |        |          |Note: This field is the status flag of receiver buffer time-out state.
 * |        |          |If software wants to clear this bit, software must read all receiver buffer remaining data
 * |        |          |by reading SC_RBR buffer,.
 * |[10]    |ACON_ERR_IS|Auto Convention Error Interrupt Status Flag (Read Only)
 * |        |          |This field indicates auto convention sequence error.
 * |        |          |If the received TS at ATR state is neither 0x3B nor 0x3F, this bit will be set.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * @var SC_T::TRSR
 * Offset: 0x20  SC Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RX_OVER_F |RX Overflow Error Status Flag (Read Only)
 * |        |          |This bit is set when RX buffer overflow.
 * |        |          |If the number of received bytes is greater than Rx Buffer size (4 bytes), this bit will be
 * |        |          |set.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[1]     |RX_EMPTY_F|Receiver Buffer Empty Status Flag(Read Only)
 * |        |          |This bit indicates RX buffer empty or not.
 * |        |          |When the last byte of Rx buffer has been read by CPU, hardware sets this bit high.
 * |        |          |It will be cleared when SC receives any new data.
 * |[2]     |RX_FULL_F |Receiver Buffer Full Status Flag (Read Only)
 * |        |          |This bit indicates RX buffer full or not.
 * |        |          |This bit is set when RX pointer is equal to 4, otherwise it is cleared by hardware.
 * |[4]     |RX_EPA_F  |Receiver Parity Error Status Flag (Read Only)
 * |        |          |This bit is set to logic 1 whenever the received character does not have a valid
 * |        |          |"parity bit".
 * |        |          |Note1:
 * |        |          |This bit is read only, but it can be cleared by writing 1 to it.
 * |        |          |Note2:
 * |        |          |If CPU sets receiver retries function by setting RX_ERETRY_EN(SC_CTL[19]) , hardware will
 * |        |          |not set this flag.
 * |[5]     |RX_EFR_F  |Receiver Frame Error Status Flag (Read Only)
 * |        |          |This bit is set to logic 1 whenever the received character does not have a valid "stop bit"
 * |        |          |(that is, the stop bit following the last data bit or parity bit is detected as logic 0).
 * |        |          |Note1:
 * |        |          |This bit is read only, but it can be cleared by writing 1 to it.
 * |        |          |Note2:
 * |        |          |If CPU sets receiver retries function by setting RX_ERETRY_EN(SC_CTL[19]) , hardware will
 * |        |          |not set this flag.
 * |[6]     |RX_EBR_F  |Receiver Break Error Status Flag (Read Only)
 * |        |          |This bit is set to logic 1 whenever the received data input (RX) held in the "spacing state"
 * |        |          |(logic 0) is longer than a full word transmission time (that is, the total time of "start bit"
 * |        |          | + data bits + parity + stop bits).
 * |        |          |Note1:
 * |        |          |This bit is read only, but it can be cleared by writing 1 to it.
 * |        |          |Note2:
 * |        |          |If CPU sets receiver retries function by setting RX_ERETRY_EN(SC_CTL[19]) , hardware will
 * |        |          |not set this flag.
 * |[8]     |TX_OVER_F |TX Overflow Error Interrupt Status Flag (Read Only)
 * |        |          |If TX buffer is full, an additional write to THR(SC_THR[7:0]) will cause this bit be set to
 * |        |          |"1" by hardware.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[9]     |TX_EMPTY_F|Transmit Buffer Empty Status Flag (Read Only)
 * |        |          |This bit indicates TX buffer empty or not.
 * |        |          |When the last byte of TX buffer has been transferred to Transmitter Shift Register, hardware
 * |        |          |sets this bit high.
 * |        |          |It will be cleared when writing data into THR(SC_THR[7:0]) (TX buffer not empty).
 * |[10]    |TX_FULL_F |Transmit Buffer Full Status Flag (Read Only)
 * |        |          |This bit indicates TX buffer full or not.This bit is set when TX pointer is equal to 4,
 * |        |          |otherwise is cleared by hardware.
 * |[17:16] |RX_POINT_F|Receiver Buffer Pointer Status Flag (Read Only)
 * |        |          |This field indicates the RX buffer pointer status flag.
 * |        |          |When SC receives one byte from external device, RX_POINT_F(SC_SR[17:16]) increases one.
 * |        |          |When one byte of RX buffer is read by CPU, RX_POINT_F(SC_SR[17:16]) decreases one.
 * |[21]    |RX_REERR  |Receiver Retry Error (Read Only)
 * |        |          |This bit is set by hardware when RX has any error and retries transfer.
 * |        |          |Note1: This bit is read only, but it can be cleared by writing 1 to it.
 * |        |          |Note2 This bit is a flag and cannot generate any interrupt to CPU.
 * |        |          |Note3: If CPU enables receiver retry function by setting RX_ERETRY_EN
 * |        |          |(SC_CTL[19]) , the RX_EPA_F(SC_TRSR[4]) flag will be ignored (hardware will not set
 * |        |          |RX_EPA_F(SC_TRSR[4])).
 * |[22]    |RX_OVER_REERR|Receiver Over Retry Error (Read Only)
 * |        |          |This bit is set by hardware when RX transfer error retry over retry number limit.
 * |        |          |Note1: This bit is read only, but it can be cleared by writing 1 to it.
 * |        |          |Note2: If CPU enables receiver retries function by setting RX_ERETRY_EN
 * |        |          |(SC_CTL[19]), the RX_EPA_F(SC_TRSR[4]) flag will be ignored (hardware will not set
 * |        |          |RX_EPA_F(SC_TRSR[4])).
 * |[23]    |RX_ATV    |Receiver In Active Status Flag (Read Only)
 * |        |          |This bit is set by hardware when RX transfer is in active.
 * |        |          |This bit is cleared automatically when RX transfer is finished.
 * |[25:24] |TX_POINT_F|Transmit Buffer Pointer Status Flag (Read Only)
 * |        |          |This field indicates the TX buffer pointer status flag.
 * |        |          |When CPU writes data into SC_THR, TX_POINT_F increases one.
 * |        |          |When one byte of TX Buffer is transferred to transmitter shift register, TX_POINT_F
 * |        |          |decreases one.
 * |[29]    |TX_REERR  |Transmitter Retry Error (Read Only)
 * |        |          |This bit is set by hardware when transmitter re-transmits.
 * |        |          |Note1: This bit is read only, but it can be cleared by writing 1 to it.
 * |        |          |Note2 This bit is a flag and cannot generate any interrupt to CPU.
 * |[30]    |TX_OVER_REERR|Transmitter Over Retry Error (Read Only)
 * |        |          |This bit is set by hardware when transmitter re-transmits over retry number limitation.
 * |        |          |Note: This bit is read only, but it can be cleared by writing 1 to it.
 * |[31]    |TX_ATV    |Transmit In Active Status Flag (Read Only)
 * |        |          |0 = This bit is cleared automatically when TX transfer is finished or the last byte
 * |        |          |transmission has completed.
 * |        |          |1 = This bit is set by hardware when TX transfer is in active and the STOP bit of the last
 * |        |          |byte has been transmitted.
 * @var SC_T::PINCSR
 * Offset: 0x24  SC Pin Control State Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |POW_EN    |SC_POW_EN Pin Signal
 * |        |          |Software can set POW_EN (SC_PINCSR[0]) and POW_INV (SC_PINCSR[11])to decide SC_PWR pin is in
 * |        |          |high or low level.
 * |        |          |Write this field to drive SC_PWR pin
 * |        |          |Refer POW_INV (SC_PINCSR[11]) description for programming SC_PWR pin voltage level.
 * |        |          |Read this field to get SC_PWR pin status.
 * |        |          |0 = SC_PWR pin status is low.
 * |        |          |1 = SC_PWR pin status is high.
 * |        |          |Note: When operating at activation, warm reset or deactivation mode, this bit will be
 * |        |          |changed automatically.
 * |        |          |So don't fill this field when operating in these modes.
 * |[1]     |SC_RST    |SC_RST Pin Signal
 * |        |          |This bit is the pin status of SC_RST but user can drive SC_RST pin to high or low by setting
 * |        |          |this bit.
 * |        |          |Write this field to drive SC_RST pin.
 * |        |          |0 = Drive SC_RST pin to low.
 * |        |          |1 = Drive SC_RST pin to high.
 * |        |          |Read this field to get SC_RST pin status.
 * |        |          |0 = SC_RST pin status is low.
 * |        |          |1 = SC_RST pin status is high.
 * |        |          |Note: When operating at activation, warm reset or deactivation mode, this bit will be
 * |        |          |changed automatically.
 * |        |          |So don't fill this field when operating in these modes.
 * |[2]     |CD_REM_F  |Card Detect Removal Status Of SC_CD Pin (Read Only)
 * |        |          |This bit is set whenever a card has been removed.
 * |        |          |0 = No effect.
 * |        |          |1 = Card removed.
 * |        |          |Note1: This bit is read only, but it can be cleared by writing "1" to it.
 * |        |          |Note2: Card detect engine will start after SC_CEN (SC_CTL[0] )set.
 * |[3]     |CD_INS_F  |Card Detect Insert Status Of SC_CD Pin (Read Only)
 * |        |          |This bit is set whenever card has been inserted.
 * |        |          |0 = No effect.
 * |        |          |1 = Card insert.
 * |        |          |Note1: This bit is read only, but it can be cleared by writing "1" to it.
 * |        |          |Note2: The
 * |        |          |card detect engine will start after SC_CEN (SC_CTL[0] )set.
 * |[4]     |CD_PIN_ST |Card Detect Status Of SC_CD Pin Status (Read Only)
 * |        |          |This bit is the pin status flag of SC_CD
 * |        |          |0 = The SC_CD pin state at low.
 * |        |          |1 = The SC_CD pin state at high.
 * |[6]     |CLK_KEEP  |SC Clock Enable Control
 * |        |          |0 = SC clock generation Disabled.
 * |        |          |1 = SC clock always keeps free running.
 * |        |          |Note: When operating in activation, warm reset or deactivation mode, this bit will be
 * |        |          |changed automatically.
 * |        |          |So don't fill this field when operating in these modes.
 * |[7]     |ADAC_CD_EN|Auto Deactivation When Card Removal
 * |        |          |0 = Auto deactivation Disabled when hardware detected the card removal.
 * |        |          |1 = Auto deactivation Enabled when hardware detected the card removal.
 * |        |          |Note: When the card is removed, hardware will stop any process and then do deactivation
 * |        |          |sequence (if this bit be setting).
 * |        |          |If this process completes.
 * |        |          |Hardware will generate an initial end.
 * |        |          |interrupt to CPU.
 * |[8]     |SC_OEN_ST |SC Data Output Enable Pin Status (Read Only)
 * |        |          |This bit is the pin status of SC_DATA_OEN
 * |        |          |0 = The SC_DATA_OEN pin state at low.
 * |        |          |1 = The SC_DATA_OEN pin state at high.
 * |[9]     |SC_DATA_O |SC Data Output Pin
 * |        |          |This bit is the pin status of SC_DATA_O but user can drive SC_DATA_O pin to high or low by
 * |        |          |setting this bit.
 * |        |          |0 = Drive SC_DATA_O pin to low.
 * |        |          |1 = Drive SC_DATA_O pin to high.
 * |        |          |Note: When SC is at activation, warm reset or deactivation mode, this bit will be changed
 * |        |          |automatically.
 * |        |          |So don't fill this field when SC is in these modes.
 * |[10]    |CD_LEV    |Card Detect Level
 * |        |          |0 = When hardware detects the card detect pin from high to low, it indicates a card is
 * |        |          |detected.
 * |        |          |1 = When hardware detects the card detect pin from low to high, it indicates a card is
 * |        |          |detected.
 * |        |          |Note: Software must select card detect level before Smart Card engine is enabled
 * |[11]    |POW_INV   |SC_POW Pin Inverse
 * |        |          |This bit is used for inverse the SC_POW pin.
 * |        |          |There are four kinds of combination for SC_POW pin setting by POW_INV(SC_PINCSR[11]) and
 * |        |          |POW_EN(SC_PINCSR[0]).
 * |        |          |POW_INV (SC_PINCSR[11]) is bit 1 and POW_EN(SC_PINCSR[0]) is bit 0 for SC_POW_Pin as high or
 * |        |          |low voltage selection.
 * |        |          |00 = SC_POW_ Pin is 0.
 * |        |          |01 = SC_POW _Pin is 1.
 * |        |          |10 = SC_POW _Pin is 1.
 * |        |          |11 = SC_POW_ Pin is 0.
 * |        |          |Note: Software must select POW_INV (SC_PINCSR[11]) before Smart Card is enabled by SC_CEN
 * |        |          |(SC_CTL[0]).
 * |[16]    |SC_DATA_I_ST|SC Data Pin Status (Read Only)
 * |        |          |This bit is the pin status of SC_DATA
 * |        |          |0 = The SC_DATA pin is low.
 * |        |          |1 = The SC_DATA pin is high.
 * |[30]    |SYNC      |SYNC Flag Indicator
 * |        |          |Due to synchronization, software should check this bit when writing a new value to SC_PINCSR
 * |        |          |register.
 * |        |          |0 = Synchronizing is completion, user can write new data to SC_PINCSR register.
 * |        |          |1 = Last value is synchronizing.
 * |        |          |Note: This bit is read only.
 * @var SC_T::TMR0
 * Offset: 0x28  SC Internal Timer Control Register 0
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[23:0]  |CNT0      |Timer 0 Counter Value (ETU Base)
 * |        |          |This field indicates the internal timer operation values.
 * |[27:24] |MODE      |Timer 0 Operation Mode Selection
 * |        |          |This field indicates the internal 24-bit timer operation selection.
 * |        |          |Refer to 5.15.5.4 for programming Timer0
 * @var SC_T::TMR1
 * Offset: 0x2C  SC Internal Timer Control Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |CNT1      |Timer 1 Counter Value (ETU Base)
 * |        |          |This field indicates the internal timer operation values.
 * |[27:24] |MODE      |Timer 1 Operation Mode Selection
 * |        |          |This field indicates the internal 8-bit timer operation selection.
 * |        |          |Refer to 5.15.5.4 for programming Timer1
 * @var SC_T::TMR2
 * Offset: 0x30  SC Internal Timer Control Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |CNT2      |Timer 2 Counter Value (ETU Base)
 * |        |          |This field indicates the internal timer operation values.
 * |[27:24] |MODE      |Timer 2 Operation Mode Selection
 * |        |          |This field indicates the internal 8-bit timer operation selection
 * |        |          |Refer to 5.15.5.4 for programming Timer2
 * @var SC_T::TDRA
 * Offset: 0x38  SC Timer Current Data Register A
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[23:0]  |TDR0      |Timer0 Current Data value(Read Only)
 * |        |          |This field indicates the current count values of timer0.
 * @var SC_T::TDRB
 * Offset: 0x3C  SC Timer Current Data Register B
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |TDR1      |Timer1 Current Data value(Read Only)
 * |        |          |This field indicates the current count values of timer1.
 * |[15:8]  |TDR2      |Timer2 Current Data value (Read Only)
 * |        |          |This field indicates the current count values of timer2.
 */

    union {
    __I  uint32_t RBR;           /* Offset: 0x00  SC Receiving Buffer Register.                                      */
    __O  uint32_t THR;           /* Offset: 0x00  SC Transmit Holding Register                                       */
    };
    __IO uint32_t CTL;           /* Offset: 0x04  SC Control Register                                                */
    __IO uint32_t ALTCTL;        /* Offset: 0x08  SC Alternate Control Register                                      */
    __IO uint32_t EGTR;          /* Offset: 0x0C  SC Extend Guard Time Register                                      */
    __IO uint32_t RFTMR;         /* Offset: 0x10  SC Receive buffer Time-out Register                                */
    __IO uint32_t ETUCR;         /* Offset: 0x14  SC ETU Control Register                                            */
    __IO uint32_t IER;           /* Offset: 0x18  SC Interrupt Enable Control Register                               */
    __IO uint32_t ISR;           /* Offset: 0x1C  SC Interrupt Status Register                                       */
    __IO uint32_t TRSR;          /* Offset: 0x20  SC Status Register                                                 */
    __IO uint32_t PINCSR;        /* Offset: 0x24  SC Pin Control State Register                                      */
    __IO uint32_t TMR0;          /* Offset: 0x28  SC Internal Timer Control Register 0                               */
    __IO uint32_t TMR1;          /* Offset: 0x2C  SC Internal Timer Control Register 1                               */
    __IO uint32_t TMR2;          /* Offset: 0x30  SC Internal Timer Control Register 2                               */
    __I  uint32_t RESERVED0;    
    __I  uint32_t TDRA;          /* Offset: 0x38  SC Timer Current Data Register A                                   */
    __I  uint32_t TDRB;          /* Offset: 0x3C  SC Timer Current Data Register B                                   */

} SC_T;



/**
    @addtogroup SC_CONST SC Bit Field Definition
    Constant Definitions for SC Controller
@{ */

/* SC RBR Bit Field Definitions */
#define SC_RBR_RBR_Pos                      0                                /*!< SC_T::RBR: RBR Position */
#define SC_RBR_RBR_Msk                      (0xFFul << SC_RBR_RBR_Pos)       /*!< SC_T::RBR: RBR Mask */

/* SC THR Bit Field Definitions */
#define SC_THR_THR_Pos                      0                                /*!< SC_T::THR: THR Position */
#define SC_THR_THR_Msk                      (0xFFul << SC_THR_THR_Pos)       /*!< SC_T::THR: THR Mask */

/* SC CTL Bit Field Definitions */
#define SC_CTL_SYNC_Pos                     30                               /*!< SC_T::CTL: SYNC Position */
#define SC_CTL_SYNC_Msk                     (1ul << SC_CTL_SYNC_Pos)         /*!< SC_T::CTL: SYNC Mask */

#define SC_CTL_CD_DEB_SEL_Pos               24                               /*!< SC_T::CTL: CD_DEB_SEL Position */
#define SC_CTL_CD_DEB_SEL_Msk               (3ul << SC_CTL_CD_DEB_SEL_Pos)   /*!< SC_T::CTL: CD_DEB_SEL Mask */

#define SC_CTL_TX_ERETRY_EN_Pos             23                               /*!< SC_T::CTL: TX_ERETRY_EN Position */
#define SC_CTL_TX_ERETRY_EN_Msk             (1ul << SC_CTL_TX_ERETRY_EN_Pos) /*!< SC_T::CTL: TX_ERETRY_EN Mask */

#define SC_CTL_TX_ERETRY_Pos                20                               /*!< SC_T::CTL: TX_ERETRY Position */
#define SC_CTL_TX_ERETRY_Msk                (7ul << SC_CTL_TX_ERETRY_Pos)    /*!< SC_T::CTL: TX_ERETRY Mask */

#define SC_CTL_RX_ERETRY_EN_Pos             19                               /*!< SC_T::CTL: RX_ERETRY_EN Position */
#define SC_CTL_RX_ERETRY_EN_Msk             (1ul << SC_CTL_RX_ERETRY_EN_Pos) /*!< SC_T::CTL: RX_ERETRY_EN Mask */

#define SC_CTL_RX_ERETRY_Pos                16                               /*!< SC_T::CTL: RX_ERETRY Position */
#define SC_CTL_RX_ERETRY_Msk                (7ul << SC_CTL_RX_ERETRY_Pos)    /*!< SC_T::CTL: RX_ERETRY Mask */

#define SC_CTL_SLEN_Pos                     15                               /*!< SC_T::CTL: SLEN Position */
#define SC_CTL_SLEN_Msk                     (1ul << SC_CTL_SLEN_Pos)         /*!< SC_T::CTL: SLEN Mask */

#define SC_CTL_TMR_SEL_Pos                  13                               /*!< SC_T::CTL: TMR_SEL Position */
#define SC_CTL_TMR_SEL_Msk                  (3ul << SC_CTL_TMR_SEL_Pos)      /*!< SC_T::CTL: TMR_SEL Mask */

#define SC_CTL_BGT_Pos                      8                                /*!< SC_T::CTL: BGT Position */
#define SC_CTL_BGT_Msk                      (0x1Ful << SC_CTL_BGT_Pos)       /*!< SC_T::CTL: BGT Mask */

#define SC_CTL_RX_FTRI_LEV_Pos              6                                /*!< SC_T::CTL: RX_FTRI_LEV Position */
#define SC_CTL_RX_FTRI_LEV_Msk              (3ul << SC_CTL_RX_FTRI_LEV_Pos)  /*!< SC_T::CTL: RX_FTRI_LEV Mask */

#define SC_CTL_CON_SEL_Pos                  4                                /*!< SC_T::CTL: CON_SEL Position */
#define SC_CTL_CON_SEL_Msk                  (3ul << SC_CTL_CON_SEL_Pos)      /*!< SC_T::CTL: CON_SEL Mask */

#define SC_CTL_AUTO_CON_EN_Pos              3                                /*!< SC_T::CTL: AUTO_CON_EN Position */
#define SC_CTL_AUTO_CON_EN_Msk              (1ul << SC_CTL_AUTO_CON_EN_Pos)  /*!< SC_T::CTL: AUTO_CON_EN Mask */

#define SC_CTL_DIS_TX_Pos                   2                                /*!< SC_T::CTL: DIS_TX Position */
#define SC_CTL_DIS_TX_Msk                   (1ul << SC_CTL_DIS_TX_Pos)       /*!< SC_T::CTL: DIS_TX Mask */

#define SC_CTL_DIS_RX_Pos                   1                                /*!< SC_T::CTL: DIS_RX Position */
#define SC_CTL_DIS_RX_Msk                   (1ul << SC_CTL_DIS_RX_Pos)       /*!< SC_T::CTL: DIS_RX Mask */

#define SC_CTL_SC_CEN_Pos                   0                                /*!< SC_T::CTL: SC_CEN Position */
#define SC_CTL_SC_CEN_Msk                   (1ul << SC_CTL_SC_CEN_Pos)       /*!< SC_T::CTL: SC_CEN Mask */

/* SC ALTCTL Bit Field Definitions */
#define SC_ALTCTL_OUTSEL_Pos                16                               /*!< SC_T::ALTCTL: OUTSEL Position */
#define SC_ALTCTL_OUTSEL_Msk                (1ul << SC_ALTCTL_OUTSEL_Pos)    /*!< SC_T::ALTCTL: OUTSEL Mask */

#define SC_ALTCTL_TMR2_ATV_Pos              15                               /*!< SC_T::ALTCTL: TMR2_ATV Position */
#define SC_ALTCTL_TMR2_ATV_Msk              (1ul << SC_ALTCTL_TMR2_ATV_Pos)  /*!< SC_T::ALTCTL: TMR2_ATV Mask */

#define SC_ALTCTL_TMR1_ATV_Pos              14                               /*!< SC_T::ALTCTL: TMR1_ATV Position */
#define SC_ALTCTL_TMR1_ATV_Msk              (1ul << SC_ALTCTL_TMR1_ATV_Pos)  /*!< SC_T::ALTCTL: TMR1_ATV Mask */

#define SC_ALTCTL_TMR0_ATV_Pos              13                               /*!< SC_T::ALTCTL: TMR0_ATV Position */
#define SC_ALTCTL_TMR0_ATV_Msk              (1ul << SC_ALTCTL_TMR0_ATV_Pos)  /*!< SC_T::ALTCTL: TMR0_ATV Mask */

#define SC_ALTCTL_RX_BGT_EN_Pos             12                               /*!< SC_T::ALTCTL: RX_BGT_EN Position */
#define SC_ALTCTL_RX_BGT_EN_Msk             (1ul << SC_ALTCTL_RX_BGT_EN_Pos) /*!< SC_T::ALTCTL: RX_BGT_EN Mask */

#define SC_ALTCTL_INIT_SEL_Pos              8                                /*!< SC_T::ALTCTL: INIT_SEL Position */
#define SC_ALTCTL_INIT_SEL_Msk              (3ul << SC_ALTCTL_INIT_SEL_Pos)  /*!< SC_T::ALTCTL: INIT_SEL Mask */

#define SC_ALTCTL_TMR2_SEN_Pos              7                                /*!< SC_T::ALTCTL: TMR2_SEN Position */
#define SC_ALTCTL_TMR2_SEN_Msk              (1ul << SC_ALTCTL_TMR2_SEN_Pos)  /*!< SC_T::ALTCTL: TMR2_SEN Mask */

#define SC_ALTCTL_TMR1_SEN_Pos              6                                /*!< SC_T::ALTCTL: TMR1_SEN Position */
#define SC_ALTCTL_TMR1_SEN_Msk              (1ul << SC_ALTCTL_TMR1_SEN_Pos)  /*!< SC_T::ALTCTL: TMR1_SEN Mask */

#define SC_ALTCTL_TMR0_SEN_Pos              5                                /*!< SC_T::ALTCTL: TMR0_SEN Position */
#define SC_ALTCTL_TMR0_SEN_Msk              (1ul << SC_ALTCTL_TMR0_SEN_Pos)  /*!< SC_T::ALTCTL: TMR0_SEN Mask */

#define SC_ALTCTL_WARST_EN_Pos              4                                /*!< SC_T::ALTCTL: WARST_EN Position */
#define SC_ALTCTL_WARST_EN_Msk              (1ul << SC_ALTCTL_WARST_EN_Pos)  /*!< SC_T::ALTCTL: WARST_EN Mask */

#define SC_ALTCTL_ACT_EN_Pos                3                                /*!< SC_T::ALTCTL: ACT_EN Position */
#define SC_ALTCTL_ACT_EN_Msk                (1ul << SC_ALTCTL_ACT_EN_Pos)    /*!< SC_T::ALTCTL: ACT_EN Mask */

#define SC_ALTCTL_DACT_EN_Pos               2                                /*!< SC_T::ALTCTL: DACT_EN Position */
#define SC_ALTCTL_DACT_EN_Msk               (1ul << SC_ALTCTL_DACT_EN_Pos)   /*!< SC_T::ALTCTL: DACT_EN Mask */

#define SC_ALTCTL_RX_RST_Pos                1                                /*!< SC_T::ALTCTL: RX_RST Position */
#define SC_ALTCTL_RX_RST_Msk                (1ul << SC_ALTCTL_RX_RST_Pos)    /*!< SC_T::ALTCTL: RX_RST Mask */

#define SC_ALTCTL_TX_RST_Pos                0                                /*!< SC_T::ALTCTL: TX_RST Position */
#define SC_ALTCTL_TX_RST_Msk                (1ul << SC_ALTCTL_TX_RST_Pos)    /*!< SC_T::ALTCTL: TX_RST Mask */

/* SC EGTR Bit Field Definitions */
#define SC_EGTR_EGT_Pos                     0                               /*!< SC_T::EGTR: EGT Position */
#define SC_EGTR_EGT_Msk                     (0xFFul << SC_EGTR_EGT_Pos)     /*!< SC_T::EGTR: EGT Mask */

/* SC RFTMR Bit Field Definitions */
#define SC_RFTMR_RFTM_Pos                   0                               /*!< SC_T::RFTMR: RFTM Position */
#define SC_RFTMR_RFTM_Msk                   (0x1FFul << SC_RFTMR_RFTM_Pos)  /*!< SC_T::RFTMR: RFTM Mask */

/* SC ETUCR Bit Field Definitions */
#define SC_ETUCR_COMPEN_EN_Pos              15                               /*!< SC_T::ETUCR: COMPEN_EN Position */
#define SC_ETUCR_COMPEN_EN_Msk              (1ul << SC_ETUCR_COMPEN_EN_Pos)  /*!< SC_T::ETUCR: COMPEN_EN Mask */

#define SC_ETUCR_ETU_RDIV_Pos               0                                   /*!< SC_T::ETUCR: ETU_RDIV Position */
#define SC_ETUCR_ETU_RDIV_Msk               (0xFFFul << SC_ETUCR_ETU_RDIV_Pos)  /*!< SC_T::ETUCR: ETU_RDIV Mask */

/* SC IER Bit Field Definitions */
#define SC_IER_ACON_ERR_IE_Pos              10                                  /*!< SC_T::IER: ACON_ERR_IE Position */
#define SC_IER_ACON_ERR_IE_Msk              (1ul << SC_IER_ACON_ERR_IE_Pos)     /*!< SC_T::IER: ACON_ERR_IE Mask */

#define SC_IER_RTMR_IE_Pos                  9                               /*!< SC_T::IER: RTMR_IE Position */
#define SC_IER_RTMR_IE_Msk                  (1ul << SC_IER_RTMR_IE_Pos)     /*!< SC_T::IER: RTMR_IE Mask */

#define SC_IER_INIT_IE_Pos                  8                               /*!< SC_T::IER: INIT_IE Position */
#define SC_IER_INIT_IE_Msk                  (1ul << SC_IER_INIT_IE_Pos)     /*!< SC_T::IER: INIT_IE Mask */

#define SC_IER_CD_IE_Pos                    7                               /*!< SC_T::IER: CD_IE Position */
#define SC_IER_CD_IE_Msk                    (1ul << SC_IER_CD_IE_Pos)       /*!< SC_T::IER: CD_IE Mask */

#define SC_IER_BGT_IE_Pos                   6                               /*!< SC_T::IER: BGT_IE Position */
#define SC_IER_BGT_IE_Msk                   (1ul << SC_IER_BGT_IE_Pos)      /*!< SC_T::IER: BGT_IE Mask */

#define SC_IER_TMR2_IE_Pos                  5                               /*!< SC_T::IER: TMR2_IE Position */
#define SC_IER_TMR2_IE_Msk                  (1ul << SC_IER_TMR2_IE_Pos)     /*!< SC_T::IER: TMR2_IE Mask */

#define SC_IER_TMR1_IE_Pos                  4                               /*!< SC_T::IER: TMR1_IE Position */
#define SC_IER_TMR1_IE_Msk                  (1ul << SC_IER_TMR1_IE_Pos)     /*!< SC_T::IER: TMR1_IE Mask */

#define SC_IER_TMR0_IE_Pos                  3                               /*!< SC_T::IER: TMR0_IE Position */
#define SC_IER_TMR0_IE_Msk                  (1ul << SC_IER_TMR0_IE_Pos)     /*!< SC_T::IER: TMR0_IE Mask */

#define SC_IER_TERR_IE_Pos                  2                               /*!< SC_T::IER: TERR_IE Position */
#define SC_IER_TERR_IE_Msk                  (1ul << SC_IER_TERR_IE_Pos)     /*!< SC_T::IER: TERR_IE Mask */

#define SC_IER_TBE_IE_Pos                   1                               /*!< SC_T::IER: TBE_IE Position */
#define SC_IER_TBE_IE_Msk                   (1ul << SC_IER_TBE_IE_Pos)      /*!< SC_T::IER: TBE_IE Mask */

#define SC_IER_RDA_IE_Pos                   0                               /*!< SC_T::IER: RDA_IE Position */
#define SC_IER_RDA_IE_Msk                   (1ul << SC_IER_RDA_IE_Pos)      /*!< SC_T::IER: RDA_IE Mask */

/* SC ISR Bit Field Definitions */
#define SC_ISR_ACON_ERR_IS_Pos              10                              /*!< SC_T::ISR: ACON_ERR_IS Position */
#define SC_ISR_ACON_ERR_IS_Msk              (1ul << SC_ISR_ACON_ERR_IS_Pos) /*!< SC_T::ISR: ACON_ERR_IS Mask */

#define SC_ISR_RTMR_IS_Pos                  9                               /*!< SC_T::ISR: RTMR_IS Position */
#define SC_ISR_RTMR_IS_Msk                  (1ul << SC_ISR_RTMR_IS_Pos)     /*!< SC_T::ISR: RTMR_IS Mask */

#define SC_ISR_INIT_IS_Pos                  8                               /*!< SC_T::ISR: INIT_IS Position */
#define SC_ISR_INIT_IS_Msk                  (1ul << SC_ISR_INIT_IS_Pos)     /*!< SC_T::ISR: INIT_IS Mask */

#define SC_ISR_CD_IS_Pos                    7                               /*!< SC_T::ISR: CD_IS Position */
#define SC_ISR_CD_IS_Msk                    (1ul << SC_ISR_CD_IS_Pos)       /*!< SC_T::ISR: CD_IS Mask */

#define SC_ISR_BGT_IS_Pos                   6                               /*!< SC_T::ISR: BGT_IS Position */
#define SC_ISR_BGT_IS_Msk                   (1ul << SC_ISR_BGT_IS_Pos)      /*!< SC_T::ISR: BGT_IS Mask */

#define SC_ISR_TMR2_IS_Pos                  5                               /*!< SC_T::ISR: TMR2_IS Position */
#define SC_ISR_TMR2_IS_Msk                  (1ul << SC_ISR_TMR2_IS_Pos)     /*!< SC_T::ISR: TMR2_IS Mask */

#define SC_ISR_TMR1_IS_Pos                  4                               /*!< SC_T::ISR: TMR1_IS Position */
#define SC_ISR_TMR1_IS_Msk                  (1ul << SC_ISR_TMR1_IS_Pos)     /*!< SC_T::ISR: TMR1_IS Mask */

#define SC_ISR_TMR0_IS_Pos                  3                               /*!< SC_T::ISR: TMR0_IS Position */
#define SC_ISR_TMR0_IS_Msk                  (1ul << SC_ISR_TMR0_IS_Pos)     /*!< SC_T::ISR: TMR0_IS Mask */

#define SC_ISR_TERR_IS_Pos                  2                               /*!< SC_T::ISR: TERR_IS Position */
#define SC_ISR_TERR_IS_Msk                  (1ul << SC_ISR_TERR_IS_Pos)     /*!< SC_T::ISR: TERR_IS Mask */

#define SC_ISR_TBE_IS_Pos                   1                               /*!< SC_T::ISR: TXBE_IS Position */
#define SC_ISR_TBE_IS_Msk                   (1ul << SC_ISR_TBE_IS_Pos)      /*!< SC_T::ISR: TXBE_IS Mask */

#define SC_ISR_RDA_IS_Pos                   0                               /*!< SC_T::ISR: RDA_IS Position */
#define SC_ISR_RDA_IS_Msk                   (1ul << SC_ISR_RDA_IS_Pos)      /*!< SC_T::ISR: RDA_IS Mask */


/* SC TRSR Bit Field Definitions */
#define SC_TRSR_TX_ATV_Pos                  31                              /*!< SC_T::TRSR: TX_ATV Position */
#define SC_TRSR_TX_ATV_Msk                  (1ul << SC_TRSR_TX_ATV_Pos)     /*!< SC_T::TRSR: TX_ATV Mask */

#define SC_TRSR_TX_OVER_REERR_Pos           30                                  /*!< SC_T::TRSR: TX_OVER_REERR Position */
#define SC_TRSR_TX_OVER_REERR_Msk           (1ul << SC_TRSR_TX_OVER_REERR_Pos)  /*!< SC_T::TRSR: TX_OVER_REERR Mask */

#define SC_TRSR_TX_REERR_Pos                29                               /*!< SC_T::TRSR: TX_REERR Position */
#define SC_TRSR_TX_REERR_Msk                (1ul << SC_TRSR_TX_REERR_Pos)    /*!< SC_T::TRSR: TX_REERR Mask */

#define SC_TRSR_TX_POINT_F_Pos              24                               /*!< SC_T::TRSR: TX_POINT_F Position */
#define SC_TRSR_TX_POINT_F_Msk              (7ul << SC_TRSR_TX_POINT_F_Pos)  /*!< SC_T::TRSR: TX_POINT_F Mask */

#define SC_TRSR_RX_ATV_Pos                  23                               /*!< SC_T::TRSR: RX_ATV Position */
#define SC_TRSR_RX_ATV_Msk                  (1ul << SC_TRSR_RX_ATV_Pos)      /*!< SC_T::TRSR: RX_ATV Mask */

#define SC_TRSR_RX_OVER_REERR_Pos           22                                  /*!< SC_T::TRSR: RX_OVER_REERR Position */
#define SC_TRSR_RX_OVER_REERR_Msk           (1ul << SC_TRSR_RX_OVER_REERR_Pos)  /*!< SC_T::TRSR: RX_OVER_REERR Mask */

#define SC_TRSR_RX_REERR_Pos                21                                  /*!< SC_T::TRSR: RX_REERR Position */
#define SC_TRSR_RX_REERR_Msk                (1ul << SC_TRSR_RX_REERR_Pos)       /*!< SC_T::TRSR: RX_REERR Mask */

#define SC_TRSR_RX_POINT_F_Pos              16                                  /*!< SC_T::TRSR: RX_POINT_F Position */
#define SC_TRSR_RX_POINT_F_Msk              (7ul << SC_TRSR_RX_POINT_F_Pos)     /*!< SC_T::TRSR: RX_POINT_F Mask */

#define SC_TRSR_TX_FULL_F_Pos               10                                  /*!< SC_T::TRSR: TX_FULL_F Position */
#define SC_TRSR_TX_FULL_F_Msk               (1ul << SC_TRSR_TX_FULL_F_Pos)      /*!< SC_T::TRSR: TX_FULL_F Mask */

#define SC_TRSR_TX_EMPTY_F_Pos              9                                   /*!< SC_T::TRSR: TX_EMPTY_F Position */
#define SC_TRSR_TX_EMPTY_F_Msk              (1ul << SC_TRSR_TX_EMPTY_F_Pos)     /*!< SC_T::TRSR: TX_EMPTY_F Mask */

#define SC_TRSR_TX_OVER_F_Pos               8                                   /*!< SC_T::TRSR: TX_OVER_F Position */
#define SC_TRSR_TX_OVER_F_Msk               (1ul << SC_TRSR_TX_OVER_F_Pos)      /*!< SC_T::TRSR: TX_OVER_F Mask */

#define SC_TRSR_RX_EBR_F_Pos                6                                   /*!< SC_T::TRSR: RX_EBR_F Position */
#define SC_TRSR_RX_EBR_F_Msk                (1ul << SC_TRSR_RX_EBR_F_Pos)       /*!< SC_T::TRSR: RX_EBR_F Mask */

#define SC_TRSR_RX_EFR_F_Pos                5                                   /*!< SC_T::TRSR: RX_EFR_F Position */
#define SC_TRSR_RX_EFR_F_Msk                (1ul << SC_TRSR_RX_EFR_F_Pos)       /*!< SC_T::TRSR: RX_EFR_F Mask */

#define SC_TRSR_RX_EPA_F_Pos                4                                   /*!< SC_T::TRSR: RX_EPA_F Position */
#define SC_TRSR_RX_EPA_F_Msk                (1ul << SC_TRSR_RX_EPA_F_Pos)       /*!< SC_T::TRSR: RX_EPA_F Mask */

#define SC_TRSR_RX_FULL_F_Pos               2                                   /*!< SC_T::TRSR: RX_FULL_F Position */
#define SC_TRSR_RX_FULL_F_Msk               (1ul << SC_TRSR_RX_FULL_F_Pos)      /*!< SC_T::TRSR: RX_FULL_F Mask */

#define SC_TRSR_RX_EMPTY_F_Pos              1                                   /*!< SC_T::TRSR: RX_EMPTY_F Position */
#define SC_TRSR_RX_EMPTY_F_Msk              (1ul << SC_TRSR_RX_EMPTY_F_Pos)     /*!< SC_T::TRSR: RX_EMPTY_F Mask */

#define SC_TRSR_RX_OVER_F_Pos               0                                   /*!< SC_T::TRSR: RX_OVER_F Position */
#define SC_TRSR_RX_OVER_F_Msk               (1ul << SC_TRSR_RX_OVER_F_Pos)      /*!< SC_T::TRSR: RX_OVER_F Mask */

/* SC PINCSR Bit Field Definitions */
#define SC_PINCSR_SYNC_Pos                  30                                  /*!< SC_T::PINCSR: SYNC Position */
#define SC_PINCSR_SYNC_Msk                  (1ul << SC_PINCSR_SYNC_Pos)         /*!< SC_T::PINCSR: SYNC Mask */

#define SC_PINCSR_SC_DATA_I_ST_Pos          16                                  /*!< SC_T::PINCSR: SC_DATA_I_ST Position */
#define SC_PINCSR_SC_DATA_I_ST_Msk          (1ul << SC_PINCSR_SC_DATA_I_ST_Pos) /*!< SC_T::PINCSR: SC_DATA_I_ST Mask */

#define SC_PINCSR_POW_INV_Pos               11                                  /*!< SC_T::PINCSR: POW_INV Position */
#define SC_PINCSR_POW_INV_Msk               (1ul << SC_PINCSR_POW_INV_Pos)      /*!< SC_T::PINCSR: POW_INV Mask */

#define SC_PINCSR_CD_LEV_Pos                10                                  /*!< SC_T::PINCSR: CD_LEV Position */
#define SC_PINCSR_CD_LEV_Msk                (1ul << SC_PINCSR_CD_LEV_Pos)       /*!< SC_T::PINCSR: CD_LEV Mask */

#define SC_PINCSR_SC_DATA_O_Pos             9                                   /*!< SC_T::PINCSR: SC_DATA_O Position */
#define SC_PINCSR_SC_DATA_O_Msk             (1ul << SC_PINCSR_SC_DATA_O_Pos)    /*!< SC_T::PINCSR: SC_DATA_O Mask */

#define SC_PINCSR_SC_OEN_ST_Pos             8                                   /*!< SC_T::PINCSR: SC_OEN_ST Position */
#define SC_PINCSR_SC_OEN_ST_Msk             (1ul << SC_PINCSR_SC_OEN_ST_Pos)    /*!< SC_T::PINCSR: SC_OEN_ST Mask */

#define SC_PINCSR_ADAC_CD_EN_Pos            7                                   /*!< SC_T::PINCSR: ADAC_CD_EN Position */
#define SC_PINCSR_ADAC_CD_EN_Msk            (1ul << SC_PINCSR_ADAC_CD_EN_Pos)   /*!< SC_T::PINCSR: ADAC_CD_EN Mask */

#define SC_PINCSR_CLK_KEEP_Pos              6                                   /*!< SC_T::PINCSR: CLK_KEEP Position */
#define SC_PINCSR_CLK_KEEP_Msk              (1ul << SC_PINCSR_CLK_KEEP_Pos)     /*!< SC_T::PINCSR: CLK_KEEP Mask */

#define SC_PINCSR_CD_PIN_ST_Pos             4                                   /*!< SC_T::PINCSR: CD_PIN_ST Position */
#define SC_PINCSR_CD_PIN_ST_Msk             (1ul << SC_PINCSR_CD_PIN_ST_Pos)    /*!< SC_T::PINCSR: CD_PIN_ST Mask */

#define SC_PINCSR_CD_INS_F_Pos              3                                   /*!< SC_T::PINCSR: CD_INS_F Position */
#define SC_PINCSR_CD_INS_F_Msk              (1ul << SC_PINCSR_CD_INS_F_Pos)     /*!< SC_T::PINCSR: CD_INS_F Mask */

#define SC_PINCSR_CD_REM_F_Pos              2                                   /*!< SC_T::PINCSR: CD_REM_F Position */
#define SC_PINCSR_CD_REM_F_Msk              (1ul << SC_PINCSR_CD_REM_F_Pos)     /*!< SC_T::PINCSR: CD_REM_F Mask */

#define SC_PINCSR_SC_RST_Pos                1                                   /*!< SC_T::PINCSR: SC_RST Position */
#define SC_PINCSR_SC_RST_Msk                (1ul << SC_PINCSR_SC_RST_Pos)       /*!< SC_T::PINCSR: SC_RST Mask */

#define SC_PINCSR_POW_EN_Pos                0                                   /*!< SC_T::PINCSR: POW_EN Position */
#define SC_PINCSR_POW_EN_Msk                (1ul << SC_PINCSR_POW_EN_Pos)       /*!< SC_T::PINCSR: POW_EN Mask */

/* SC TMR0 Bit Field Definitions */
#define SC_TMR0_MODE_Pos                    24                              /*!< SC_T::TMR0: MODE Position */
#define SC_TMR0_MODE_Msk                    (0xFul << SC_TMR0_MODE_Pos)     /*!< SC_T::TMR0: MODE Mask */

#define SC_TMR0_CNT_Pos                     0                               /*!< SC_T::TMR0: CNT Position */
#define SC_TMR0_CNT_Msk                     (0xFFFFFFul << SC_TMR0_CNT_Pos) /*!< SC_T::TMR0: CNT Mask */

/* SC TMR1 Bit Field Definitions */
#define SC_TMR1_MODE_Pos                    24                              /*!< SC_T::TMR1: MODE Position */
#define SC_TMR1_MODE_Msk                    (0xFul << SC_TMR1_MODE_Pos)     /*!< SC_T::TMR1: MODE Mask */

#define SC_TMR1_CNT_Pos                     0                               /*!< SC_T::TMR1: CNT Position */
#define SC_TMR1_CNT_Msk                     (0xFFul << SC_TMR1_CNT_Pos)     /*!< SC_T::TMR1: CNT Mask */

/* SC TMR2 Bit Field Definitions */
#define SC_TMR2_MODE_Pos                    24                              /*!< SC_T::TMR2: MODE Position */
#define SC_TMR2_MODE_Msk                    (0xFul << SC_TMR2_MODE_Pos)     /*!< SC_T::TMR2: MODE Mask */

#define SC_TMR2_CNT_Pos                     0                               /*!< SC_T::TMR2: CNT Position */
#define SC_TMR2_CNT_Msk                     (0xFFul << SC_TMR2_CNT_Pos)     /*!< SC_T::TMR2: CNT Mask */

/* SC TDRA Bit Field Definitions */
#define SC_TDRA_TDR0_Pos                    0                                   /*!< SC_T::TDRA: TDR0 Position */
#define SC_TDRA_TDR0_Msk                    (0xFFFFFFul << SC_TDRA_TDR0_Pos)    /*!< SC_T::TDRA: TDR0 Mask */

/* SC TDRB Bit Field Definitions */
#define SC_TDRB_TDR2_Pos                    8                               /*!< SC_T::TDRB: TDR2 Position */
#define SC_TDRB_TDR2_Msk                    (0xFFul << SC_TDRB_TDR2_Pos)    /*!< SC_T::TDRB: TDR2 Mask */

#define SC_TDRB_TDR1_Pos                    0                               /*!< SC_T::TDRB: TDR1 Position */
#define SC_TDRB_TDR1_Msk                    (0xFFul << SC_TDRB_TDR1_Pos)    /*!< SC_T::TDRB: TDR1 Mask */
/*@}*/ /* end of group SC_CONST */
/*@}*/ /* end of group SC */




/*---------------------- Serial Peripheral Interface Controller -------------------------*/
/**
    @addtogroup SPI Serial Peripheral Interface Controller (SPI)
    Memory Mapped Structure for SPI Controller
@{ */


typedef struct
{


/**
 * @var SPI_T::CNTRL
 * Offset: 0x00  Control and Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GO_BUSY   |SPI Transfer Control Bit and Busy Status
 * |        |          |0 = Data transfer stopped.
 * |        |          |1 = In Master mode, writing 1 to this bit to start the SPI data transfer; in Slave mode,
 * |        |          |    writing 1 to this bit indicates that the slave is ready to communicate with a master.
 * |        |          |If FIFO mode is disabled, during the data transfer, this bit keeps the value of 1.
 * |        |          |As the transfer is finished, this bit will be cleared automatically.
 * |        |          |Software can read this bit to check if the SPI is in busy status.
 * |        |          |In FIFO mode, this bit will be controlled by hardware.
 * |        |          |Software should not modify this bit.
 * |        |          |In Slave mode, this bit always returns 1 when this register is read by software.
 * |        |          |In Master mode, this bit reflects the busy or idle status of SPI.
 * |        |          |Note:
 * |        |          |1. When FIFO mode is disabled, all configurations should be set before writing 1 to this
 * |        |          |GO_BUSY bit.
 * |        |          |2. When FIFO mode is disabled and the software uses TX or RX PDMA function to transfer data,
 * |        |          |this bit
 * |        |          |   will be cleared after the PDMA finishes the data transfer.
 * |[1]     |RX_NEG    |Receive on Negative Edge
 * |        |          |0 = Received data input signal is latched on the rising edge of SPI bus clock.
 * |        |          |1 = Received data input signal is latched on the falling edge of SPI bus clock.
 * |[2]     |TX_NEG    |Transmit on Negative Edge
 * |        |          |0 = Transmitted data output signal is changed on the rising edge of SPI bus clock.
 * |        |          |1 = Transmitted data output signal is changed on the falling edge of SPI bus clock.
 * |[7:3]   |TX_BIT_LEN|Transmit Bit Length
 * |        |          |This field specifies how many bits can be transmitted / received in one transaction.
 * |        |          |The minimum bit length is 8 bits and can up to 32 bits.
 * |        |          |TX_BIT_LEN = 0x08 ... 8 bits.
 * |        |          |TX_BIT_LEN = 0x09 ... 9 bits.
 * |        |          |......
 * |        |          |TX_BIT_LEN = 0x1F ... 31 bits.
 * |        |          |TX_BIT_LEN = 0x00 ... 32 bits.
 * |[10]    |LSB       |Send LSB First
 * |        |          |0 = The MSB, which bit of transmit/receive register depends on the setting of TX_BIT_LEN, is
 * |        |          |transmitted/received first.
 * |        |          |1 = The LSB, bit 0 of the SPI TX0/1 register, is sent first to the SPI data output pin, and
 * |        |          |the first bit received from
 * |        |          | the SPI data input pin will be put in the LSB position of the RX register (bit 0 of
 * |        |          |SPI_RX0/1).
 * |[11]    |CLKP      |Clock Polarity
 * |        |          |0 = SPI bus clock is idle low.
 * |        |          |1 = SPI bus clock is idle high.
 * |[15:12] |SP_CYCLE  |Suspend Interval (Master Only)
 * |        |          |The four bits provide configurable suspend interval between two successive transmit/receive
 * |        |          |transaction in a transfer.
 * |        |          |The definition of the suspend interval is the interval between the last clock edge of the
 * |        |          |preceding transaction word
 * |        |          |and the first clock edge of the following transaction word.
 * |        |          |The default value is 0x3.
 * |        |          |The period of the suspend interval is obtained according to the following equation.
 * |        |          |(SP_CYCLE[3:0] + 0.5) * period of SPI bus clock cycle
 * |        |          |Example:
 * |        |          |SP_CYCLE = 0x0 ... 0.5 SPI bus clock cycle.
 * |        |          |SP_CYCLE = 0x1 ... 1.5 SPI bus clock cycle.
 * |        |          |......
 * |        |          |SP_CYCLE = 0xE ... 14.5 SPI bus clock cycle.
 * |        |          |SP_CYCLE = 0xF ... 15.5 SPI bus clock cycle.
 * |        |          |If the variable clock function is enabled and the transmit FIFO buffer is not empty, the
 * |        |          |minimum period of suspend
 * |        |          |interval between the successive transactions is (6.5 + SP_CYCLE) * SPI bus clock cycle.
 * |[16]    |IF        |Unit Transfer Interrupt Flag
 * |        |          |0 = No transaction has been finished since this bit was cleared to 0.
 * |        |          |1 = SPI controller has finished one unit transfer.
 * |        |          |Note: This bit will be cleared by writing 1 to itself.
 * |[17]    |IE        |Unit Transfer Interrupt Enable
 * |        |          |0 = SPI unit transfer interrupt Disabled.
 * |        |          |1 = SPI unit transfer interrupt Enabled.
 * |[18]    |SLAVE     |Slave Mode Enable
 * |        |          |0 = Master mode.
 * |        |          |1 = Slave mode.
 * |[19]    |REORDER   |Byte Reorder Function Enable
 * |        |          |0 = Byte Reorder function Disabled.
 * |        |          |1 = Byte Reorder function Enabled.
 * |        |          |A byte suspend interval will be inserted among each byte.
 * |        |          |The period of the byte suspend interval depends on the setting of SP_CYCLE.
 * |        |          |Note:
 * |        |          |1. Byte Reorder function is only available if TX_BIT_LEN is defined as 16, 24, and 32 bits.
 * |        |          |2. In Slave mode with level-trigger configuration, the slave select pin must be kept at
 * |        |          |active state during the
 * |        |          |   byte suspend interval.
 * |        |          |3. The Byte Reorder function is not supported when the variable bus clock function or Dual
 * |        |          |I/O mode is enabled.
 * |[21]    |FIFO      |FIFO Mode Enable
 * |        |          |0 = FIFO mode Disabled.
 * |        |          |1 = FIFO mode Enabled.
 * |        |          |Note:
 * |        |          |1. Before enabling FIFO mode, the other related settings should be set in advance.
 * |        |          |2. In Master mode, if the FIFO mode is enabled, the GO_BUSY bit will be set to 1
 * |        |          |automatically after writing data
 * |        |          | to the transmit FIFO buffer; the GO_BUSY bit will be cleared to 0 automatically when the
 * |        |          |SPI controller is in idle.
 * |        |          | If all data stored at transmit FIFO buffer are sent out, the TX_EMPTY bit will be set to 1
 * |        |          |and the GO_BUSY bit will be cleared to 0.
 * |        |          |3. After clearing this bit to 0, user must wait for at least 2 peripheral clock periods
 * |        |          |before setting this bit to 1 again.
 * |[22]    |TWOB      |2-Bit Transfer Mode Enable
 * |        |          |0 = 2-bit Transfer mode Disabled.
 * |        |          |1 = 2-bit Transfer mode Enabled.
 * |        |          |Note: When 2-bit Transfer mode is enabled, the serial transmitted 2-bit data are from
 * |        |          |SPI_TX1/0, and the received 2-bit data input are put in SPI_RX1/0.
 * |[23]    |VARCLK_EN |Variable Clock Enable (Master Only)
 * |        |          |0 = SPI clock output frequency is fixed and decided only by the value of DIVIDER.
 * |        |          |1 = SPI clock output frequency is variable.
 * |        |          |The output frequency is decided by the value of VARCLK, DIVIDER, and DIVIDER2.
 * |        |          |Note: When this VARCLK_EN bit is set to 1, the setting of TX_BIT_LEN must be programmed as
 * |        |          |0x10 (16-bit mode).
 * |[24]    |RX_EMPTY  |Receive FIFO Buffer Empty Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_STATUS[24].
 * |        |          |0 = Receive FIFO buffer is not empty.
 * |        |          |1 = Receive FIFO buffer is empty.
 * |[25]    |RX_FULL   |Receive FIFO Buffer Full Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_STATUS[25].
 * |        |          |0 = Receive FIFO buffer is not full.
 * |        |          |1 = Receive FIFO buffer is full.
 * |[26]    |TX_EMPTY  |Transmit FIFO Buffer Empty Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_STATUS[26].
 * |        |          |0 = Transmit FIFO buffer is not empty.
 * |        |          |1 = Transmit FIFO buffer is empty.
 * |[27]    |TX_FULL   |Transmit FIFO Buffer Full Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_STATUS[27].
 * |        |          |0 = Transmit FIFO buffer is not full.
 * |        |          |1 = Transmit FIFO buffer is full.
 * @var SPI_T::DIVIDER
 * Offset: 0x04  Clock Divider Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |DIVIDER   |Clock Divider 1 Register
 * |        |          |The value in this field is the frequency divider for generating the SPI peripheral clock and
 * |        |          |the SPI bus clock of SPI master.
 * |        |          |The frequency is obtained according to the following equation.
 * |        |          |If the bit of BCn, SPI_CNTRL2[31], is set to 0,
 * |        |          |   SPI peripheral clock frequency = system clock frequency / (DIVIDER + 1) / 2
 * |        |          |else if BCn is set to 1,
 * |        |          |   SPI peripheral clock frequency = SPI peripheral clock source frequency / (DIVIDER + 1)
 * |        |          |The SPI peripheral clock source is defined in the CLKSEL1 register.
 * |[23:16] |DIVIDER2  |Clock Divider 2 Register (Master Only)
 * |        |          |The value in this field is the 2nd frequency divider for generating the second clock of the
 * |        |          |variable clock function.
 * |        |          |The frequency is obtained according to the following equation:
 * |        |          |   f_clk2 = SPI peripheral clock frequency / (DIVIDER2 + 1) / 2
 * |        |          |If the VARCLK_EN bit is cleared to 0, this setting is unmeaning.
 * @var SPI_T::SSR
 * Offset: 0x08  Slave Select Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |SSR       |Slave Select Control Bits (Master Only)
 * |        |          |If AUTOSS bit is cleared, writing 1 to any bit of this field sets the proper SPIn_SPISS0/1
 * |        |          |line to an active state and writing 0 sets the line back to inactive state.
 * |        |          |If the AUTOSS bit is set, writing 0 to any bit location of this field will keep the
 * |        |          |corresponding
 * |        |          |SPIn_SPISS0/1 line at inactive state; writing 1 to any bit location of this field will
 * |        |          |select
 * |        |          |appropriate SPIn_SPISS0/1 line to be automatically driven to active state for the duration
 * |        |          |of the
 * |        |          |transmit/receive, and will be driven to inactive state for the rest of the time.
 * |        |          |The active state of SPIn_SPISS0/1 is specified in SS_LVL.
 * |        |          |Note: SPIn_SPISS0 is defined as the slave select input in Slave mode.
 * |[2]     |SS_LVL    |Slave Select Active Level
 * |        |          |This bit defines the active status of slave select signal (SPIn_SPISS0/1).
 * |        |          |0 = The slave select signal SPIn_SPISS0/1 is active on low-level/falling-edge.
 * |        |          |1 = The slave select signal SPIn_SPISS0/1 is active on high-level/rising-edge.
 * |[3]     |AUTOSS    |Automatic Slave Select Function Enable (Master Only)
 * |        |          |0 = If this bit is cleared, slave select signals will be asserted/de-asserted by setting
 * |        |          |/clearing
 * |        |          |    the corresponding bits of SPI_SSR[1:0].
 * |        |          |1 = If this bit is set, SPIn_SPISS0/1 signals will be generated automatically.
 * |        |          | It means that device/slave select signal, which is set in SPI_SSR[1:0], will be asserted by
 * |        |          |the
 * |        |          | SPI controller when transmit/receive is started, and will be de-asserted after each
 * |        |          |transmit/receive is finished.
 * |[4]     |SS_LTRIG  |Slave Select Level Trigger Enable (Slave Only)
 * |        |          |0 = Slave select signal is edge-trigger.
 * |        |          |    This is the default value.
 * |        |          |    The SS_LVL bit decides the signal is active after a falling-edge or rising-edge.
 * |        |          |1 = Slave select signal is level-trigger.
 * |        |          |    The SS_LVL bit decides the signal is active low or active high.
 * |[5]     |LTRIG_FLAG|Level Trigger Accomplish Flag
 * |        |          |In Slave mode, this bit indicates whether the received bit number meets the requirement or
 * |        |          |not after the current transaction done.
 * |        |          |0 = Transferred bit length of one transaction does not meet the specified requirement.
 * |        |          |1 = Transferred bit length meets the specified requirement which defined in TX_BIT_LEN.
 * |        |          |Note: This bit is READ only.
 * |        |          |As the GO_BUSY bit is set to 1 by software, the LTRIG_FLAG will be cleared to 0 after 4 SPI
 * |        |          |peripheral clock periods plus 1 system clock period.
 * |        |          |In FIFO mode, this bit has no meaning.
 * @var SPI_T::RX
 * Offset: 0x10~0x14  Data Receive Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |RX        |Data Receive Register
 * |        |          |The data receive register holds the datum received from SPI data input pin.
 * |        |          |If FIFO mode is disabled, the last received data can be accessed through software by reading
 * |        |          |this register.
 * |        |          |If the FIFO bit is set as 1 and the RX_EMPTY bit, SPI_CNTRL[24] or SPI_STATUS[24], is not
 * |        |          |set to 1, the receive
 * |        |          |FIFO buffer can be accessed through software by reading this register. This is a read-only
 * |        |          |register.
 * @var SPI_T::TX
 * Offset: 0x20~0x24  Data Transmit Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |TX        |Data Transmit Register
 * |        |          |The data transmit registers hold the data to be transmitted in the next transfer.
 * |        |          |The number of valid bits depends on the setting of transmit bit length field of the
 * |        |          |SPI_CNTRL register.
 * |        |          |For example, if TX_BIT_LEN is set to 0x08, the bits TX[7:0] will be transmitted in next
 * |        |          |transfer.
 * |        |          |If TX_BIT_LEN is set to 0x00, the SPI controller will perform a 32-bit transfer.
 * |        |          |Note 1: When the SPI controller is configured as a slave device and FIFO mode is disabled,
 * |        |          |if the SPI
 * |        |          | controller attempts to transmit data to a master, the transmit data register should be
 * |        |          |updated
 * |        |          |        by software before setting the GO_BUSY bit to 1.
 * |        |          |Note 2: In Master mode, SPI controller will start to transfer after 5 peripheral clock
 * |        |          |cycles after user writes to this register.
 * @var SPI_T::VARCLK
 * Offset: 0x34  Variable Clock Pattern Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |VARCLK    |Variable Clock Pattern
 * |        |          |This register defines the clock pattern of the SPI transfer.
 * |        |          |If the variable clock function is disabled, this setting is unmeaning.
 * @var SPI_T::DMA
 * Offset: 0x38  SPI DMA Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TX_DMA_GO |Transmit DMA Start
 * |        |          |Setting this bit to 1 will start the transmit PDMA process.
 * |        |          |SPI controller will issue request to PDMA controller automatically.
 * |        |          |Hardware will clear this bit to 0 automatically after PDMA transfer done.
 * |        |          |If the SPI transmit PDMA function is used to transfer data, the GO_BUSY bit should not be
 * |        |          |set to 1 by software.
 * |        |          |The PDMA control logic of SPI controller will set it automatically whenever necessary.
 * |        |          |In Slave mode and when FIFO mode is disabled, the minimal suspend interval between two
 * |        |          |successive transactions
 * |        |          |must be larger than (8 SPI clock periods + 14 APB clock periods) for edge-trigger mode or
 * |        |          |(9.5 SPI clock periods + 14 APB clock periods) for level-trigger mode.
 * |        |          |If the 2-bit Transfer mode is enabled, additional 18 APB clock periods for the above
 * |        |          |conditions is required.
 * |[1]     |RX_DMA_GO |Receive DMA Start
 * |        |          |Setting this bit to 1 will start the receive PDMA process.
 * |        |          |The SPI controller will issue request to PDMA controller automatically when the SPI receive
 * |        |          |buffer is not empty.
 * |        |          |This bit will be cleared to 0 by hardware automatically after PDMA transfer is done.
 * |        |          |If the software uses the receive PDMA function to access the received data of SPI and does
 * |        |          |not use the transmit
 * |        |          |PDMA function, the GO_BUSY bit should be set by software.
 * |        |          |Enabling FIFO mode is recommended if the software uses more than one PDMA channel to
 * |        |          |transfer data.
 * |        |          |In Slave mode and when FIFO mode is disabled, if the software only uses one PDMA channel for
 * |        |          |SPI receive PDMA
 * |        |          |function and the other PDMA channels are not in use, the minimal suspend interval between
 * |        |          |two successive
 * |        |          |transactions must be larger than (9 SPI slave peripheral clock periods + 4 APB clock
 * |        |          |periods) for Edge-trigger
 * |        |          |mode or (9.5 SPI slave peripheral clock periods + 4 APB clock periods) for Level-trigger
 * |        |          |mode.
 * |[2]     |PDMA_RST  |PDMA Reset
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the PDMA control logic of the SPI controller. This bit will be cleared to 0
 * |        |          |automatically.
 * @var SPI_T::CNTRL2
 * Offset: 0x3C  Control and Status Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8]     |NOSLVSEL  |Slave 3-Wire Mode Enable
 * |        |          |This is used to ignore the slave select signal in Slave mode.
 * |        |          |The SPI controller can work with 3-wire interface including SPIn_CLK, SPIn_MISO, and
 * |        |          |SPIn_MOSI.
 * |        |          |0 = 4-wire bi-direction interface.
 * |        |          |1 = 3-wire bi-direction interface.
 * |        |          |Note: In Slave 3-wire mode, the SS_LTRIG, SPI_SSR[4] will be set as 1 automatically.
 * |[9]     |SLV_ABORT |Slave 3-Wire Mode Abort Control
 * |        |          |In normal operation, there is an interrupt event when the received data meet the required
 * |        |          |bits which defined in TX_BIT_LEN.
 * |        |          |If the received bits are less than the requirement and there is no more SPI clock input over
 * |        |          |the one transfer time in
 * |        |          |Slave 3-wire mode, the user can set this bit to force the current transfer done and then the
 * |        |          |user can get a transfer done interrupt event.
 * |        |          |Note: This bit will be cleared to 0 automatically by hardware after it is set to 1 by
 * |        |          |software.
 * |[10]    |SSTA_INTEN|Slave 3-Wire Mode Start Interrupt Enable
 * |        |          |Used to enable interrupt when the transfer has started in Slave 3-wire mode.
 * |        |          |If there is no transfer done interrupt over the time period which is defined by user after
 * |        |          |the transfer start,
 * |        |          |the user can set the SLV_ABORT bit to force the transfer done.
 * |        |          |0 = Transaction start interrupt Disabled.
 * |        |          |1 = Transaction start interrupt Enabled.
 * |        |          |It will be cleared to 0 as the current transfer is done or the SLV_START_INTSTS bit is
 * |        |          |cleared.
 * |[11]    |SLV_START_INTSTS|Slave 3-Wire Mode Start Interrupt Status
 * |        |          |This bit indicates if a transaction has started in Slave 3-wire mode.
 * |        |          |It is a mutual mirror bit of SPI_STATUS[11].
 * |        |          |0 = Slave has not detected any SPI clock transition since the SSTA_INTEN bit was set to 1.
 * |        |          |1 = A transaction has started in Slave 3-wire mode.
 * |        |          |It will be cleared automatically when a transaction is done or by writing 1 to this bit.
 * |[12]    |DUAL_IO_DIR|Dual I/O Mode Direction Control
 * |        |          |0 = Dual Input mode.
 * |        |          |1 = Dual Output mode.
 * |[13]    |DUAL_IO_EN|Dual I/O Mode Enable
 * |        |          |0 = Dual I/O mode Disabled.
 * |        |          |1 = Dual I/O mode Enabled.
 * |[16]    |SS_INT_OPT|Slave Select Inactive Interrupt Option
 * |        |          |This setting is only available if the SPI controller is configured as level trigger slave
 * |        |          |device.
 * |        |          |0 = As the slave select signal goes to inactive level, the IF bit will NOT be set to 1.
 * |        |          |1 = As the slave select signal goes to inactive level, the IF bit will be set to 1.
 * |[31]    |BCn       |SPI Peripheral Clock Backward Compatible Option
 * |        |          |0 = Backward compatible clock configuration.
 * |        |          |1 = Clock configuration is not backward compatible.
 * |        |          |Refer to the description of SPI_DIVIDER register for details.
 * @var SPI_T::FIFO_CTL
 * Offset: 0x40  SPI FIFO Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RX_CLR    |Clear Receive FIFO Buffer
 * |        |          |0 = No effect.
 * |        |          |1 = Clear receive FIFO buffer.
 * |        |          |The RX_FULL flag will be cleared to 0 and the RX_EMPTY flag will be set to 1.
 * |        |          |This bit will be cleared to 0 by hardware after it is set to 1 by software.
 * |[1]     |TX_CLR    |Clear Transmit FIFO Buffer
 * |        |          |0 = No effect.
 * |        |          |1 = Clear transmit FIFO buffer.
 * |        |          |The TX_FULL flag will be cleared to 0 and the TX_EMPTY flag will be set to 1.
 * |        |          |This bit will be cleared to 0 by hardware after it is set to 1 by software.
 * |[2]     |RX_INTEN  |Receive Threshold Interrupt Enable
 * |        |          |0 = RX threshold interrupt Disabled.
 * |        |          |1 = RX threshold interrupt Enabled.
 * |[3]     |TX_INTEN  |Transmit Threshold Interrupt Enable
 * |        |          |0 = TX threshold interrupt Disabled.
 * |        |          |1 = TX threshold interrupt Enabled.
 * |[6]     |RXOV_INTEN|Receive FIFO Overrun Interrupt Enable
 * |        |          |0 = Receive FIFO overrun interrupt Disabled.
 * |        |          |1 = Receive FIFO overrun interrupt Enabled.
 * |[21]    |TIMEOUT_INTEN|Receive FIFO Time-Out Interrupt Enable
 * |        |          |0 = Time-out interrupt Disabled.
 * |        |          |1 = Time-out interrupt Enabled.
 * |[26:24] |RX_THRESHOLD|Receive FIFO Threshold
 * |        |          |If the valid data count of the receive FIFO buffer is larger than the RX_THRESHOLD setting,
 * |        |          |the RX_INTSTS bit will be set to 1, else the RX_INTSTS bit will be cleared to 0.
 * |[30:28] |TX_THRESHOLD|Transmit FIFO Threshold
 * |        |          |If the valid data count of the transmit FIFO buffer is less than or equal to the
 * |        |          |TX_THRESHOLD
 * |        |          |setting, the TX_INTSTS bit will be set to 1, else the TX_INTSTS bit will be cleared to 0.
 * @var SPI_T::STATUS
 * Offset: 0x44  SPI Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RX_INTSTS |Receive FIFO Threshold Interrupt Status (Read Only)
 * |        |          |0 = The valid data count within the Rx FIFO buffer is smaller than or equal to the setting
 * |        |          |value of RX_THRESHOLD.
 * |        |          |1 = The valid data count within the receive FIFO buffer is larger than the setting value of
 * |        |          |RX_THRESHOLD.
 * |        |          |Note: If RX_INTEN = 1 and RX_INTSTS = 1, the SPI controller will generate a SPI interrupt
 * |        |          |request.
 * |[2]     |RX_OVERRUN|Receive FIFO Overrun Status
 * |        |          |When the receive FIFO buffer is full, the follow-up data will be dropped and this bit will
 * |        |          |be set to 1.
 * |        |          |Note: This bit will be cleared by writing 1 to itself.
 * |[4]     |TX_INTSTS |Transmit FIFO Threshold Interrupt Status (Read Only)
 * |        |          |0 = The valid data count within the transmit FIFO buffer is larger than the setting value of
 * |        |          |TX_THRESHOLD.
 * |        |          |1 = The valid data count within the transmit FIFO buffer is less than or equal to the
 * |        |          |setting value of TX_THRESHOLD.
 * |        |          |Note: If TX_INTEN = 1 and TX_INTSTS = 1, the SPI controller will generate a SPI interrupt
 * |        |          |request.
 * |[11]    |SLV_START_INTSTS|Slave Start Interrupt Status
 * |        |          |It is used to dedicate if a transaction has started in Slave 3-wire mode.
 * |        |          |It is a mutual mirror bit of SPI_CNTRL2[11].
 * |        |          |0 = Slave has not detected any SPI clock transition since the SSTA_INTEN bit was set to 1.
 * |        |          |1 = A transaction has started in Slave 3-wire mode.
 * |        |          |It will be cleared as a transaction is done or by writing 1 to this bit.
 * |[15:12] |RX_FIFO_COUNT|Receive FIFO Data Count (Read Only)
 * |        |          |This bit field indicates the valid data count of receive FIFO buffer.
 * |[16]    |IF        |SPI Unit Transfer Interrupt Flag
 * |        |          |It is a mutual mirror bit of SPI_CNTRL[16].
 * |        |          |0 = No transaction has been finished since this bit was cleared to 0.
 * |        |          |1 = SPI controller has finished one unit transfer.
 * |        |          |Note: This bit will be cleared by writing 1 to itself.
 * |[20]    |TIMEOUT   |Time-Out Interrupt Flag
 * |        |          |0 = No receive FIFO time-out event.
 * |        |          |1 = Receive FIFO buffer is not empty and no read operation on receive FIFO buffer over 64
 * |        |          |SPI clock
 * |        |          |period in Master mode or over 576 SPI peripheral clock period in Slave mode.
 * |        |          |When the received FIFO buffer is read by software, the time-out status will be cleared
 * |        |          |automatically.
 * |        |          |Note: This bit will be cleared by writing 1 to itself.
 * |[24]    |RX_EMPTY  |Receive FIFO Buffer Empty Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_CNTRL[24].
 * |        |          |0 = Receive FIFO buffer is not empty.
 * |        |          |1 = Receive FIFO buffer is empty.
 * |[25]    |RX_FULL   |Receive FIFO Buffer Empty Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_CNTRL[25].
 * |        |          |0 = Receive FIFO buffer is not empty.
 * |        |          |1 = Receive FIFO buffer is empty.
 * |[26]    |TX_EMPTY  |Transmit FIFO Buffer Empty Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_CNTRL[26].
 * |        |          |0 = Transmit FIFO buffer is not empty.
 * |        |          |1 = Transmit FIFO buffer is empty.
 * |[27]    |TX_FULL   |Transmit FIFO Buffer Full Indicator (Read Only)
 * |        |          |It is a mutual mirror bit of SPI_CNTRL[27].
 * |        |          |0 = Transmit FIFO buffer is not full.
 * |        |          |1 = Transmit FIFO buffer is full.
 * |[31:28] |TX_FIFO_COUNT|Transmit FIFO Data Count (Read Only)
 * |        |          |This bit field indicates the valid data count of transmit FIFO buffer.
 */

    __IO uint32_t CNTRL;         /* Offset: 0x00  Control and Status Register                                        */
    __IO uint32_t DIVIDER;       /* Offset: 0x04  Clock Divider Register                                             */
    __IO uint32_t SSR;           /* Offset: 0x08  Slave Select Register                                              */
    __I  uint32_t RESERVE0;     
    __I  uint32_t RX[2];         /* Offset: 0x10  Data Receive Register                                              */
    __I  uint32_t RESERVE1;     
    __I  uint32_t RESERVE2;     
    __O  uint32_t TX[2];         /* Offset: 0x20  Data Transmit Register                                             */
    __I  uint32_t RESERVE3;     
    __I  uint32_t RESERVE4;     
    __I  uint32_t RESERVE5;     
    __IO uint32_t VARCLK;        /* Offset: 0x34  Variable Clock Pattern Register                                    */
    __IO uint32_t DMA;           /* Offset: 0x38  SPI DMA Control Register                                           */
    __IO uint32_t CNTRL2;        /* Offset: 0x3C  Control and Status Register 2                                      */
    __IO uint32_t FIFO_CTL;      /* Offset: 0x40  SPI FIFO Control Register                                          */
    __IO uint32_t STATUS;        /* Offset: 0x44  SPI Status Register                                                */
    
} SPI_T;



/**
    @addtogroup SPI_CONST SPI Bit Field Definition
    Constant Definitions for SPI Controller
@{ */

/* SPI_CNTRL Bit Field Definitions */
#define SPI_CNTRL_TX_FULL_Pos      27                                     /*!< SPI_T::CNTRL: TX_FULL Position */
#define SPI_CNTRL_TX_FULL_Msk      (1ul << SPI_CNTRL_TX_FULL_Pos)         /*!< SPI_T::CNTRL: TX_FULL Mask     */

#define SPI_CNTRL_TX_EMPTY_Pos     26                                     /*!< SPI_T::CNTRL: TX_EMPTY Position */
#define SPI_CNTRL_TX_EMPTY_Msk     (1ul << SPI_CNTRL_TX_EMPTY_Pos)        /*!< SPI_T::CNTRL: TX_EMPTY Mask     */

#define SPI_CNTRL_RX_FULL_Pos      25                                     /*!< SPI_T::CNTRL: RX_FULL Position */
#define SPI_CNTRL_RX_FULL_Msk      (1ul << SPI_CNTRL_RX_FULL_Pos)         /*!< SPI_T::CNTRL: RX_FULL Mask     */

#define SPI_CNTRL_RX_EMPTY_Pos     24                                     /*!< SPI_T::CNTRL: RX_EMPTY Position */
#define SPI_CNTRL_RX_EMPTY_Msk     (1ul << SPI_CNTRL_RX_EMPTY_Pos)        /*!< SPI_T::CNTRL: RX_EMPTY Mask     */

#define SPI_CNTRL_VARCLK_EN_Pos    23                                     /*!< SPI_T::CNTRL: VARCLK_EN Position */
#define SPI_CNTRL_VARCLK_EN_Msk    (1ul << SPI_CNTRL_VARCLK_EN_Pos)       /*!< SPI_T::CNTRL: VARCLK_EN Mask     */

#define SPI_CNTRL_TWOB_Pos         22                                     /*!< SPI_T::CNTRL: TWOB Position */
#define SPI_CNTRL_TWOB_Msk         (1ul << SPI_CNTRL_TWOB_Pos)            /*!< SPI_T::CNTRL: TWOB Mask     */

#define SPI_CNTRL_FIFO_Pos         21                                     /*!< SPI_T::CNTRL: FIFO Position */
#define SPI_CNTRL_FIFO_Msk         (1ul << SPI_CNTRL_FIFO_Pos)            /*!< SPI_T::CNTRL: FIFO Mask     */

#define SPI_CNTRL_REORDER_Pos      19                                     /*!< SPI_T::CNTRL: REORDER Position */
#define SPI_CNTRL_REORDER_Msk      (1ul << SPI_CNTRL_REORDER_Pos)         /*!< SPI_T::CNTRL: REORDER Mask     */

#define SPI_CNTRL_SLAVE_Pos        18                                     /*!< SPI_T::CNTRL: SLAVE Position */
#define SPI_CNTRL_SLAVE_Msk        (1ul << SPI_CNTRL_SLAVE_Pos)           /*!< SPI_T::CNTRL: SLAVE Mask     */

#define SPI_CNTRL_IE_Pos           17                                     /*!< SPI_T::CNTRL: IE Position */
#define SPI_CNTRL_IE_Msk           (1ul << SPI_CNTRL_IE_Pos)              /*!< SPI_T::CNTRL: IE Mask     */

#define SPI_CNTRL_IF_Pos           16                                     /*!< SPI_T::CNTRL: IF Position */
#define SPI_CNTRL_IF_Msk           (1ul << SPI_CNTRL_IF_Pos)              /*!< SPI_T::CNTRL: IF Mask     */

#define SPI_CNTRL_SP_CYCLE_Pos     12                                     /*!< SPI_T::CNTRL: SP_CYCLE Position */
#define SPI_CNTRL_SP_CYCLE_Msk     (0xFul << SPI_CNTRL_SP_CYCLE_Pos)      /*!< SPI_T::CNTRL: SP_CYCLE Mask     */

#define SPI_CNTRL_CLKP_Pos         11                                     /*!< SPI_T::CNTRL: CLKP Position */
#define SPI_CNTRL_CLKP_Msk         (1ul << SPI_CNTRL_CLKP_Pos)            /*!< SPI_T::CNTRL: CLKP Mask     */

#define SPI_CNTRL_LSB_Pos          10                                     /*!< SPI_T::CNTRL: LSB Position */
#define SPI_CNTRL_LSB_Msk          (1ul << SPI_CNTRL_LSB_Pos)             /*!< SPI_T::CNTRL: LSB Mask     */

#define SPI_CNTRL_TX_BIT_LEN_Pos   3                                      /*!< SPI_T::CNTRL: TX_BIT_LEN Position */
#define SPI_CNTRL_TX_BIT_LEN_Msk   (0x1Ful << SPI_CNTRL_TX_BIT_LEN_Pos)   /*!< SPI_T::CNTRL: TX_BIT_LEN Mask     */

#define SPI_CNTRL_TX_NEG_Pos       2                                      /*!< SPI_T::CNTRL: TX_NEG Position */
#define SPI_CNTRL_TX_NEG_Msk       (1ul << SPI_CNTRL_TX_NEG_Pos)          /*!< SPI_T::CNTRL: TX_NEG Mask     */

#define SPI_CNTRL_RX_NEG_Pos       1                                      /*!< SPI_T::CNTRL: RX_NEG Position */
#define SPI_CNTRL_RX_NEG_Msk       (1ul << SPI_CNTRL_RX_NEG_Pos)          /*!< SPI_T::CNTRL: RX_NEG Mask     */

#define SPI_CNTRL_GO_BUSY_Pos      0                                      /*!< SPI_T::CNTRL: GO_BUSY Position */
#define SPI_CNTRL_GO_BUSY_Msk      (1ul << SPI_CNTRL_GO_BUSY_Pos)         /*!< SPI_T::CNTRL: GO_BUSY Mask     */

/* SPI_DIVIDER Bit Field Definitions */
#define SPI_DIVIDER_DIVIDER2_Pos   16                                     /*!< SPI_T::DIVIDER: DIVIDER2 Position */
#define SPI_DIVIDER_DIVIDER2_Msk   (0xFFul << SPI_DIVIDER_DIVIDER2_Pos)   /*!< SPI_T::DIVIDER: DIVIDER2 Mask */

#define SPI_DIVIDER_DIVIDER_Pos    0                                      /*!< SPI_T::DIVIDER: DIVIDER Position */
#define SPI_DIVIDER_DIVIDER_Msk    (0xFFul << SPI_DIVIDER_DIVIDER_Pos)    /*!< SPI_T::DIVIDER: DIVIDER Mask */

/* SPI_SSR Bit Field Definitions */
#define SPI_SSR_LTRIG_FLAG_Pos     5                                 /*!< SPI_T::SSR: LTRIG_FLAG Position */
#define SPI_SSR_LTRIG_FLAG_Msk     (1ul << SPI_SSR_LTRIG_FLAG_Pos)   /*!< SPI_T::SSR: LTRIG_FLAG Mask */

#define SPI_SSR_SS_LTRIG_Pos       4                                 /*!< SPI_T::SSR: SS_LTRIG Position */
#define SPI_SSR_SS_LTRIG_Msk       (1ul << SPI_SSR_SS_LTRIG_Pos)     /*!< SPI_T::SSR: SS_LTRIG Mask */

#define SPI_SSR_AUTOSS_Pos         3                                 /*!< SPI_T::SSR: AUTOSS Position */
#define SPI_SSR_AUTOSS_Msk         (1ul << SPI_SSR_AUTOSS_Pos)       /*!< SPI_T::SSR: AUTOSS Mask */

#define SPI_SSR_SS_LVL_Pos         2                                 /*!< SPI_T::SSR: SS_LVL Position */
#define SPI_SSR_SS_LVL_Msk         (1ul << SPI_SSR_SS_LVL_Pos)       /*!< SPI_T::SSR: SS_LVL Mask */

#define SPI_SSR_SSR_Pos            0                                 /*!< SPI_T::SSR: SSR Position */
#define SPI_SSR_SSR_Msk            (3ul << SPI_SSR_SSR_Pos)          /*!< SPI_T::SSR: SSR Mask */

/* SPI_DMA Bit Field Definitions */
#define SPI_DMA_PDMA_RST_Pos   2                                     /*!< SPI_T::DMA: PDMA_RST Position */
#define SPI_DMA_PDMA_RST_Msk   (1ul << SPI_DMA_PDMA_RST_Pos)         /*!< SPI_T::DMA: PDMA_RST Mask */

#define SPI_DMA_RX_DMA_GO_Pos   1                                    /*!< SPI_T::DMA: RX_DMA_GO Position */
#define SPI_DMA_RX_DMA_GO_Msk   (1ul << SPI_DMA_RX_DMA_GO_Pos)       /*!< SPI_T::DMA: RX_DMA_GO Mask */

#define SPI_DMA_TX_DMA_GO_Pos   0                                    /*!< SPI_T::DMA: TX_DMA_GO Position */
#define SPI_DMA_TX_DMA_GO_Msk   (1ul << SPI_DMA_TX_DMA_GO_Pos)       /*!< SPI_T::DMA: TX_DMA_GO Mask */

/* SPI_CNTRL2 Bit Field Definitions */
#define SPI_CNTRL2_BCn_Pos   31                                                      /*!< SPI_T::CNTRL2: BCn Position */
#define SPI_CNTRL2_BCn_Msk   (1ul << SPI_CNTRL2_BCn_Pos)                             /*!< SPI_T::CNTRL2: BCn Mask */

#define SPI_CNTRL2_SS_INT_OPT_Pos   16                                               /*!< SPI_T::CNTRL2: SS_INT_OPT Position */
#define SPI_CNTRL2_SS_INT_OPT_Msk   (1ul << SPI_CNTRL2_SS_INT_OPT_Pos)               /*!< SPI_T::CNTRL2: SS_INT_OPT Mask */

#define SPI_CNTRL2_DUAL_IO_EN_Pos   13                                               /*!< SPI_T::CNTRL2: DUAL_IO_EN Position */
#define SPI_CNTRL2_DUAL_IO_EN_Msk   (1ul << SPI_CNTRL2_DUAL_IO_EN_Pos)               /*!< SPI_T::CNTRL2: DUAL_IO_EN Mask */

#define SPI_CNTRL2_DUAL_IO_DIR_Pos   12                                              /*!< SPI_T::CNTRL2: DUAL_IO_DIR Position */
#define SPI_CNTRL2_DUAL_IO_DIR_Msk   (1ul << SPI_CNTRL2_DUAL_IO_DIR_Pos)             /*!< SPI_T::CNTRL2: DUAL_IO_DIR Mask */

#define SPI_CNTRL2_SLV_START_INTSTS_Pos   11                                         /*!< SPI_T::CNTRL2: SLV_START_INTSTS Position */
#define SPI_CNTRL2_SLV_START_INTSTS_Msk   (1ul << SPI_CNTRL2_SLV_START_INTSTS_Pos)   /*!< SPI_T::CNTRL2: SLV_START_INTSTS Mask */

#define SPI_CNTRL2_SSTA_INTEN_Pos   10                                               /*!< SPI_T::CNTRL2: SSTA_INTEN Position */
#define SPI_CNTRL2_SSTA_INTEN_Msk   (1ul << SPI_CNTRL2_SSTA_INTEN_Pos)               /*!< SPI_T::CNTRL2: SSTA_INTEN Mask */

#define SPI_CNTRL2_SLV_ABORT_Pos    9                                                /*!< SPI_T::CNTRL2: SLV_ABORT Position */
#define SPI_CNTRL2_SLV_ABORT_Msk    (1ul << SPI_CNTRL2_SLV_ABORT_Pos)                /*!< SPI_T::CNTRL2: SLV_ABORT Mask */

#define SPI_CNTRL2_NOSLVSEL_Pos     8                                                /*!< SPI_T::CNTRL2: NOSLVSEL Position */
#define SPI_CNTRL2_NOSLVSEL_Msk     (1ul << SPI_CNTRL2_NOSLVSEL_Pos)                 /*!< SPI_T::CNTRL2: NOSLVSEL Mask */

/* SPI_FIFO_CTL Bit Field Definitions */
#define SPI_FIFO_CTL_TX_THRESHOLD_Pos   28                                         /*!< SPI_T::FIFO_CTL: TX_THRESHOLD Position */
#define SPI_FIFO_CTL_TX_THRESHOLD_Msk   (7ul << SPI_FIFO_CTL_TX_THRESHOLD_Pos)     /*!< SPI_T::FIFO_CTL: TX_THRESHOLD Mask */

#define SPI_FIFO_CTL_RX_THRESHOLD_Pos   24                                         /*!< SPI_T::FIFO_CTL: RX_THRESHOLD Position */
#define SPI_FIFO_CTL_RX_THRESHOLD_Msk   (7ul << SPI_FIFO_CTL_RX_THRESHOLD_Pos)     /*!< SPI_T::FIFO_CTL: RX_THRESHOLD Mask */

#define SPI_FIFO_CTL_TIMEOUT_INTEN_Pos   21                                        /*!< SPI_T::FIFO_CTL: TIMEOUT_INTEN Position */
#define SPI_FIFO_CTL_TIMEOUT_INTEN_Msk   (1ul << SPI_FIFO_CTL_TIMEOUT_INTEN_Pos)   /*!< SPI_T::FIFO_CTL: TIMEOUT_INTEN Mask */

#define SPI_FIFO_CTL_RXOV_INTEN_Pos    6                                           /*!< SPI_T::FIFO_CTL: RXOV_INTEN Position */
#define SPI_FIFO_CTL_RXOV_INTEN_Msk    (1ul << SPI_FIFO_CTL_RXOV_INTEN_Pos)        /*!< SPI_T::FIFO_CTL: RXOV_INTEN Mask */

#define SPI_FIFO_CTL_TX_INTEN_Pos    3                                             /*!< SPI_T::FIFO_CTL: TX_INTEN Position */
#define SPI_FIFO_CTL_TX_INTEN_Msk    (1ul << SPI_FIFO_CTL_TX_INTEN_Pos)            /*!< SPI_T::FIFO_CTL: TX_INTEN Mask */

#define SPI_FIFO_CTL_RX_INTEN_Pos    2                                             /*!< SPI_T::FIFO_CTL: RX_INTEN Position */
#define SPI_FIFO_CTL_RX_INTEN_Msk    (1ul << SPI_FIFO_CTL_RX_INTEN_Pos)            /*!< SPI_T::FIFO_CTL: RX_INTEN Mask */

#define SPI_FIFO_CTL_TX_CLR_Pos     1                                              /*!< SPI_T::FIFO_CTL: TX_CLR Position */
#define SPI_FIFO_CTL_TX_CLR_Msk     (1ul << SPI_FIFO_CTL_TX_CLR_Pos)               /*!< SPI_T::FIFO_CTL: TX_CLR Mask */

#define SPI_FIFO_CTL_RX_CLR_Pos      0                                             /*!< SPI_T::FIFO_CTL: RX_CLR Position */
#define SPI_FIFO_CTL_RX_CLR_Msk      (1ul << SPI_FIFO_CTL_RX_CLR_Pos)              /*!< SPI_T::FIFO_CTL: RX_CLR Mask */

/* SPI_STATUS Bit Field Definitions */
#define SPI_STATUS_TX_FIFO_COUNT_Pos   28                                            /*!< SPI_T::STATUS: TX_FIFO_COUNT Position */
#define SPI_STATUS_TX_FIFO_COUNT_Msk   (0xFul << SPI_STATUS_TX_FIFO_COUNT_Pos)       /*!< SPI_T::STATUS: TX_FIFO_COUNT Mask */

#define SPI_STATUS_TX_FULL_Pos   27                                                  /*!< SPI_T::STATUS: TX_FULL Position */
#define SPI_STATUS_TX_FULL_Msk   (1ul << SPI_STATUS_TX_FULL_Pos)                     /*!< SPI_T::STATUS: TX_FULL Mask */

#define SPI_STATUS_TX_EMPTY_Pos   26                                                 /*!< SPI_T::STATUS: TX_EMPTY Position */
#define SPI_STATUS_TX_EMPTY_Msk   (1ul << SPI_STATUS_TX_EMPTY_Pos)                   /*!< SPI_T::STATUS: TX_EMPTY Mask */

#define SPI_STATUS_RX_FULL_Pos   25                                                  /*!< SPI_T::STATUS: RX_FULL Position */
#define SPI_STATUS_RX_FULL_Msk   (1ul << SPI_STATUS_RX_FULL_Pos)                     /*!< SPI_T::STATUS: RX_FULL Mask */

#define SPI_STATUS_RX_EMPTY_Pos   24                                                 /*!< SPI_T::STATUS: RX_EMPTY Position */
#define SPI_STATUS_RX_EMPTY_Msk   (1ul << SPI_STATUS_RX_EMPTY_Pos)                   /*!< SPI_T::STATUS: RX_EMPTY Mask */

#define SPI_STATUS_TIMEOUT_Pos   20                                                  /*!< SPI_T::STATUS: TIMEOUT Position */
#define SPI_STATUS_TIMEOUT_Msk   (1ul << SPI_STATUS_TIMEOUT_Pos)                     /*!< SPI_T::STATUS: TIMEOUT Mask */

#define SPI_STATUS_IF_Pos   16                                                       /*!< SPI_T::STATUS: IF Position */
#define SPI_STATUS_IF_Msk   (1ul << SPI_STATUS_IF_Pos)                               /*!< SPI_T::STATUS: IF Mask     */

#define SPI_STATUS_RX_FIFO_COUNT_Pos   12                                            /*!< SPI_T::STATUS: RX_FIFO_COUNT Position */
#define SPI_STATUS_RX_FIFO_COUNT_Msk   (0xFul << SPI_STATUS_RX_FIFO_COUNT_Pos)       /*!< SPI_T::STATUS: RX_FIFO_COUNT Mask */

#define SPI_STATUS_SLV_START_INTSTS_Pos   11                                         /*!< SPI_T::STATUS: SLV_START_INTSTS Position */
#define SPI_STATUS_SLV_START_INTSTS_Msk   (1ul << SPI_STATUS_SLV_START_INTSTS_Pos)   /*!< SPI_T::STATUS: SLV_START_INTSTS Mask */

#define SPI_STATUS_TX_INTSTS_Pos   4                                                 /*!< SPI_T::STATUS: TX_INTSTS Position */
#define SPI_STATUS_TX_INTSTS_Msk   (1ul << SPI_STATUS_TX_INTSTS_Pos)                 /*!< SPI_T::STATUS: TX_INTSTS Mask */

#define SPI_STATUS_RX_OVERRUN_Pos   2                                                /*!< SPI_T::STATUS: RX_OVERRUN Position */
#define SPI_STATUS_RX_OVERRUN_Msk   (1ul << SPI_STATUS_RX_OVERRUN_Pos)               /*!< SPI_T::STATUS: RX_OVERRUN Mask */

#define SPI_STATUS_RX_INTSTS_Pos   0                                                 /*!< SPI_T::STATUS: RX_INTSTS Position */
#define SPI_STATUS_RX_INTSTS_Msk   (1ul << SPI_STATUS_RX_INTSTS_Pos)                 /*!< SPI_T::STATUS: RX_INTSTS Mask */
/*@}*/ /* end of group SPI_CONST */
/*@}*/ /* end of group SPI */




/*---------------------- System Manger Controller -------------------------*/
/**
    @addtogroup SYS System Manger Controller (SYS)
    Memory Mapped Structure for SYS Controller
@{ */



typedef struct
{



/**
 * @var GCR_T::PDID
 * Offset: 0x00  Part Device Identification Number Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |PDID      |Part Device Identification Number
 * |        |          |This register reflects device part number code.
 * |        |          |Software can read this register to identify which device is used.
 * @var GCR_T::RSTSRC
 * Offset: 0x04  System Reset Source Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RSTS_POR  |Power-on Reset Flag
 * |        |          |The RSTS_POR flag is set by the "reset signal" from the Power-On Reset (POR) controller or bit CHIP_RST (IPRSTC1[0]) to indicate the previous reset source.
 * |        |          |0 = No reset from POR or CHIP_RST (IPRSTC1[0]).
 * |        |          |1 = Power-on Reset (POR) or CHIP_RST (IPRSTC1[0]) had issued the reset signal to reset the system.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[1]     |RSTS_RESET|Reset Pin Reset Flag
 * |        |          |The RSTS_RESET flag is set by the "Reset Signal" from the /RESET pin to indicate the previous reset source.
 * |        |          |0 = No reset from /RESET pin.
 * |        |          |1 = The Pin /RESET had issued the reset signal to reset the system.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[2]     |RSTS_WDT  |Watchdog Reset Flag
 * |        |          |The RSTS_WDT flag is set by The "Reset Signal" from the Watchdog Timer to indicate the previous reset source
 * |        |          |0 = No reset from watchdog timer.
 * |        |          |1 = The watchdog timer had issued the reset signal to reset the system.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[3]     |RSTS_LVR  |Low Voltage Reset Flag
 * |        |          |The RSTS_LVR flag Is Set By The "Reset Signal" From The Low-Voltage-Reset Controller To Indicate The Previous Reset Source
 * |        |          |0 = No reset from LVR.
 * |        |          |1 = The LVR controller had issued the reset signal to reset the system.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[4]     |RSTS_BOD  |Brown-out Detector Reset Flag
 * |        |          |The RSTS_BOD flag is set by the "Reset Signal" from the Brown-Out Detector to indicate the previous reset source.
 * |        |          |0 = No reset from BOD.
 * |        |          |1 = The BOD had issued the reset signal to reset the system.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[5]     |RSTS_SYS  |SYS Reset Flag
 * |        |          |The RSTS_SYS flag is set by the "Reset Signal" from the Cortex-M0 kernel to indicate the previous reset source.
 * |        |          |0 = No reset from Cortex-M0.
 * |        |          |1 = The Cortex-M0 had issued the reset signal to reset the system by writing 1 to bit SYSRESETREQ (AIRCR[2], Application Interrupt and Reset Control Register, address = 0xE000ED0C) in system control registers of Cortex-M0 kernel.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[7]     |RSTS_CPU  |CPU Reset Flag
 * |        |          |The RSTS_CPU flag is set by hardware if software writes CPU_RST (IPRSTC1[1]) 1 to reset Cortex-M0 CPU kernel and flash. Memory Controller (FMC)
 * |        |          |0 = No reset from CPU.
 * |        |          |1 = Cortex-M0 CPU kernel and FMC are reset by software setting CPU_RST(IPRSTC1[1]) to 1.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * @var GCR_T::IPRSTC1
 * Offset: 0x08  IP Reset Control Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CHIP_RST  |CHIP One-Shot Reset (Write Protect)
 * |        |          |Setting this bit will reset the whole chip, including CPU kernel and all peripherals, and this bit will automatically return to 0 after the 2 clock cycles.
 * |        |          |The CHIP_RST is the same as the POR reset, all the chip controllers are reset and the chip setting from flash are also reload.
 * |        |          |0 = CHIP normal operation.
 * |        |          |1 = CHIP one-shot reset.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[1]     |CPU_RST   |CPU Kernel One-Shot Reset (Write Protect)
 * |        |          |Setting this bit will only reset the CPU kernel and Flash Memory Controller(FMC), and this bit will automatically return 0 after the two clock cycles.
 * |        |          |0 = CPU normal operation.
 * |        |          |1 = CPU one-shot reset.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[2]     |PDMA_RST  |PDMA Controller Reset (Write Protect)
 * |        |          |Setting this bit to 1 will generate a reset signal to the PDMA.
 * |        |          |User need to set this bit to 0 to release from reset state.
 * |        |          |0 = PDMA controller normal operation.
 * |        |          |1 = PDMA controller reset.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[3]     |EBI_RST   |EBI Controller Reset (Write Protect)
 * |        |          |Setting this bit to 1 will generate a reset signal to the EBI.
 * |        |          |User need to set this bit to 0 to release from reset state.
 * |        |          |0 = EBI controller normal operation.
 * |        |          |1 = EBI controller reset.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * @var GCR_T::IPRSTC2
 * Offset: 0x0C  IP Reset Control Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1]     |GPIO_RST  |GPIO Controller Reset
 * |        |          |0 = GPIO controller normal operation.
 * |        |          |1 = GPIO controller reset.
 * |[2]     |TMR0_RST  |Timer0 Controller Reset
 * |        |          |0 = Timer0 controller normal operation.
 * |        |          |1 = Timer0 controller reset.
 * |[3]     |TMR1_RST  |Timer1 Controller Reset
 * |        |          |0 = Timer1 controller normal operation.
 * |        |          |1 = Timer1 controller reset.
 * |[4]     |TMR2_RST  |Timer2 Controller Reset
 * |        |          |0 = Timer2 controller normal operation.
 * |        |          |1 = Timer2 controller reset.
 * |[5]     |TMR3_RST  |Timer3 Controller Reset
 * |        |          |0 = Timer3 controller normal operation.
 * |        |          |1 = Timer3 controller reset.
 * |[8]     |I2C0_RST  |I2C0 Controller Reset
 * |        |          |0 = I2C0 controller normal operation.
 * |        |          |1 = I2C0 controller reset.
 * |[9]     |I2C1_RST  |I2C1 Controller Reset
 * |        |          |0 = I2C1 controller normal operation.
 * |        |          |1 = I2C1 controller reset.
 * |[12]    |SPI0_RST  |SPI0 Controller Reset
 * |        |          |0 = SPI0 controller normal operation.
 * |        |          |1 = SPI0 controller reset.
 * |[13]    |SPI1_RST  |SPI1 Controller Reset
 * |        |          |0 = SPI1 controller normal operation.
 * |        |          |1 = SPI1 controller reset.
 * |[14]    |SPI2_RST  |SPI2 Controller Reset
 * |        |          |0 = SPI2 controller normal operation.
 * |        |          |1 = SPI2 controller reset.
 * |[15]    |SPI3_RST  |SPI3 Controller Reset
 * |        |          |0 = SPI3 controller normal operation.
 * |        |          |1 = SPI3 controller reset.
 * |[16]    |UART0_RST |UART0 Controller Reset
 * |        |          |0 = UART0 controller normal operation.
 * |        |          |1 = UART0 controller reset.
 * |[17]    |UART1_RST |UART1 Controller Reset
 * |        |          |0 = UART1 controller normal operation.
 * |        |          |1 = UART1 controller reset.
 * |[18]    |UART2_RST |UART2 Controller Reset
 * |        |          |0 = UART2 controller normal operation.
 * |        |          |1 = UART2 controller reset.
 * |[20]    |PWM03_RST |PWM03 Controller Reset
 * |        |          |0 = PWM03 controller normal operation.
 * |        |          |1 = PWM03 controller reset.
 * |[21]    |PWM47_RST |PWM47 Controller Reset
 * |        |          |0 = PWM47 controller normal operation.
 * |        |          |1 = PWM47 controller reset.
 * |[22]    |ACMP_RST  |Analog Comparator Controller Reset
 * |        |          |0 = Analog Comparator controller normal operation.
 * |        |          |1 = Analog Comparator controller reset.
 * |[23]    |PS2_RST   |PS/2 Controller Reset
 * |        |          |0 = PS/2 controller normal operation.
 * |        |          |1 = PS/2 controller reset.
 * |[27]    |USBD_RST  |USB Device Controller Reset
 * |        |          |0 = USB device controller normal operation.
 * |        |          |1 = USB device controller reset.
 * |[28]    |ADC_RST   |ADC Controller Reset
 * |        |          |0 = ADC controller normal operation.
 * |        |          |1 = ADC controller reset.
 * |[29]    |I2S_RST   |I2S Controller Reset
 * |        |          |0 = I2S controller normal operation.
 * |        |          |1 = I2S controller reset.
 * @var GCR_T::IPRSTC3
 * Offset: 0x10  IP Reset Control Register 3
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |SC0_RST   |SC0 Controller Reset
 * |        |          |0 = SC0 controller normal operation.
 * |        |          |1 = SC0 controller reset.
 * |[1]     |SC1_RST   |SC1 Controller Reset
 * |        |          |0 = SC1 controller normal operation.
 * |        |          |1 = SC1 controller reset.
 * |[2]     |SC2_RST   |SC2 Controller Reset
 * |        |          |0 = SC2 controller normal operation.
 * |        |          |1 = SC2 controller reset.
 * @var GCR_T::BODCR
 * Offset: 0x18  Brown-out Detector Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |BOD_EN    |Brown-Out Detector Enable Bit (Write Protect)
 * |        |          |The default value is set by flash memory controller user configuration register CBODEN (Config0[23]) bit.
 * |        |          |0 = Brown-out Detector function Disabled.
 * |        |          |1 = Brown-out Detector function Enabled.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[2:1]   |BOD_VL    |Brown-Out Detector Threshold Voltage Selection (Write Protect)
 * |        |          |The default value is set by flash controller user configuration register CBOV (Config0[22:21]) bit.
 * |        |          |00 = Brown-out voltage is 2.2V.
 * |        |          |01 = Brown-out voltage is 2.7V.
 * |        |          |10 = Brown-out voltage is 3.7V.
 * |        |          |11 = Brown-out voltage is 4.4V.
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[3]     |BOD_RSTEN |Brown-out Reset Enable Control (Write Protect)
 * |        |          |0 = Brown-out "INTERRUPT" function Enabled.
 * |        |          |While the BOD function is enabled (BOD_EN high) and BOD interrupt function is enabled (BOD_RSTEN low), BOD will assert an interrupt if BOD_OUT is high.
 * |        |          |BOD interrupt will keep till to the BOD_EN set to 0. BOD interrupt can be blocked by disabling the NVIC BOD interrupt or disabling BOD function (set BOD_EN low).
 * |        |          |1 = Brown-out "RESET" function Enabled.
 * |        |          |Note1: While the Brown-out Detector function is enabled (BOD_EN high) and BOD reset function is enabled (BOD_RSTEN high), BOD will assert a signal to reset chip when the detected voltage is lower than the threshold (BOD_OUT high).
 * |        |          |Note2: The default value is set by flash controller user configuration register CBORST (Config0[20]) bit.
 * |        |          |Note3: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[4]     |BOD_INTF  |Brown-out Detector Interrupt Flag
 * |        |          |0 = Brown-out Detector does not detect any voltage draft at VDD down through or up through the voltage of BOD_VL setting.
 * |        |          |1 = When Brown-out Detector detects the VDD is dropped down through the voltage of BOD_VL setting or the VDD is raised up through the voltage of BOD_VL setting, this bit is set to 1 and the Brown-out interrupt is requested if Brown-out interrupt is enabled.
 * |        |          |Note: Write 1 to clear this bit to 0.
 * |[5]     |BOD_LPM   |Brown-out Detector Low Power Mode (Write Protection)
 * |        |          |0 = BOD operated in Normal mode (default).
 * |        |          |1 = BOD Low Power mode Enabled.
 * |        |          |Note1: The BOD consumes about 100 uA in Normal mode, and the low power mode can reduce the current to about 1/10 but slow the BOD response.
 * |        |          |Note2: This bit is write protected bit. Refer to the REGWRPROT register.
 * |[6]     |BOD_OUT   |Brown-out Detector Output Status
 * |        |          |0 = Brown-out Detector output status is 0. It means the detected voltage is higher than BOD_VL setting or BOD_EN is 0.
 * |        |          |1 = Brown-out Detector output status is 1. It means the detected voltage is lower than BOD_VL setting. If the BOD_EN is 0, BOD function disabled, this bit always responds to 0.
 * |[7]     |LVR_EN    |Low Voltage Reset Enable Bit (Write Protect)
 * |        |          |The LVR function reset the chip when the input power voltage is lower than LVR circuit setting. LVR function is enabled by default.
 * |        |          |0 = Low Voltage Reset function Disabled.
 * |        |          |1 = Low Voltage Reset function Enabled - After enabling the bit, the LVR function will be active with 100us delay for LVR output stable (default).
 * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
 * @var GCR_T::TEMPCR
 * Offset: 0x1C  Temperature Sensor Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |VTEMP_EN  |Temperature Sensor Enable Control
 * |        |          |This bit is used to enable/disable temperature sensor function.
 * |        |          |0 = Temperature sensor function Disabled (default).
 * |        |          |1 = Temperature sensor function Enabled.
 * |        |          |Note: After this bit is set to 1, the value of temperature can be obtained from ADC conversion result.
 * |        |          |Please refer to the ADC function chapter for detail ADC conversion functional description.
 * @var GCR_T::PORCR
 * Offset: 0x24  Power-on-Reset Controller Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |POR_DIS_CODE|Power-on Reset Enable Control (Write Protect)
 * |        |          |When powered on, the POR circuit generates a reset signal to reset the whole chip function, but noise on the power may cause the POR active again.
 * |        |          |User can disable internal POR circuit to avoid unpredictable noise to cause chip reset by writing 0x5AA5 to this field.
 * |        |          |The POR function will be active again when this field is set to another value or chip is reset by other reset source, including:
 * |        |          |nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
 * |        |          |Note: These bits are write protected bit. Refer to the REGWRPROT register.
 * @var GCR_T::GPA_MFP
 * Offset: 0x30  GPIOA Multiple Function and Input Type Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GPA_MFP0  |PA.0 Pin Function Selection
 * |        |          |Bit PA0_SC0PWR (ALT_MFP1[2]) and GPA_MFP[0] determine the PA.0 function.
 * |        |          |(PA0_SC0PWR, GPA_MFP0) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = ADC0 function is selected.
 * |        |          |(1, 1) = SC0_PWR function is selected.  
 * |[1]     |GPA_MFP1  |PA.1 Pin Function Selection
 * |        |          |Bit EBI_HB_EN[4] (ALT_MFP[20]), EBI_EN (ALT_MFP[11]), PA1_SC0RST (ALT_MFP1[3]) and GPA_MFP[1] determine the PA.1 function.
 * |        |          |(EBI_HB_EN[4], EBI_EN, PA1_SC0RST, GPA_MFP1) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC1 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD12 function is selected.          
 * |[2]     |GPA_MFP2  |PA.2 Pin Function Selection
 * |        |          |Bits EBI_HB_EN[3] (ALT_MFP[19]), EBI_EN (ALT_MFP[11]), PA2_SC0CLK (ALT_MFP1[0]) and GPA_MFP[2] determine the PA.2 function.
 * |        |          |(EBI_HB_EN[3], EBI_EN, PA2_SC0CLK, GPA_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC2 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_CLK function is selected.
 * |        |          |(1, 1, 0, 1) = AD11 function is selected.         
 * |[3]     |GPA_MFP3  |PA.3 Pin Function Selection   
 * |        |          |Bits EBI_HB_EN[2] (ALT_MFP[18]), EBI_EN (ALT_MFP[11]), PA3_SC0DAT (ALT_MFP1[1]) and GPA_MFP[3] determine the PA.3 function.
 * |        |          |(EBI_HB_EN[2], EBI_EN, PA3_SC0DAT, GPA_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC3 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_DAT function is selected.
 * |        |          |(1, 1, 0, 1) = AD10 function is selected.
 * |[4]     |GPA_MFP4  |PA.4 Pin Function Selection     
 * |        |          |Bits EBI_HB_EN[1] (ALT_MFP[17]), EBI_EN (ALT_MFP[11]), PA4_SC1PWR (ALT_MFP1[7]) and GPA_MFP[4] determine the PA.4 function.
 * |        |          |(EBI_HB_EN[1], EBI_EN, PA4_SC1PWR, GPA_MFP4) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC4 function is selected.
 * |        |          |(0, 0, 1, 1) = SC1_PWR function is selected.
 * |        |          |(1, 1, 0, 1) = AD9 function is selected.     
 * |[5]     |GPA_MFP5  |PA.5 Pin Function Selection    
 * |        |          |Bits EBI_HB_EN[0] (ALT_MFP[16]), EBI_EN (ALT_MFP[11]), PA5_SC1RST (ALT_MFP1[8]) and GPA_MFP[5] determine the PA.5 function.
 * |        |          |(EBI_HB_EN[0], EBI_EN, PA5_SC1RST, GPA_MFP5) value and function mapping is as following list,
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC5 function is selected.
 * |        |          |(0, 0, 1, 1) = SC1_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD8 function is selected.     
 * |[6]     |GPA_MFP6  |PA.6 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PA6_SC1CLK (ALT_MFP1[5]) and GPA_MFP[6] determine the PA.6 function.
 * |        |          |(EBI_EN, PA6_SC1CLK, GPA_MFP6) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ADC6 function is selected.
 * |        |          |(0, 1, 1) = SC1_CLK function is selected.
 * |        |          |(1, 0, 1) = AD7 function is selected.     
 * |[7]     |GPA_MFP7  |PA.7 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PA7_SC1DAT (ALT_MFP1[6]), PA7_S21 (ALT_MFP[2]) and GPA_MFP[7] determine the PA.7 function.
 * |        |          |(EBI_EN, PA7_SC1DAT, PA7_S21, GPA_MFP7) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC7 function is selected.
 * |        |          |(0, 0, 1, 1) = SPI2_SS1 function is selected.
 * |        |          |(0, 1, 0, 1) = SC1_DAT function is selected.
 * |        |          |(1, 0, 0, 1) = AD6 function is selected.     
 * |[8]     |GPA_MFP8  |PA.8 Pin Function Selection
 * |        |          |Bit GPA_MFP[8] determines the PA.8 function.
 * |        |          |0 = GPIO function is selected to the pin PA.8.
 * |        |          |1 = I2C0_SDA function is selected to the pin PA.8.
 * |[10]    |GPA_MFP9  |PA.9 Pin Function Selection
 * |        |          |Bit GPA_MFP[9] determines the PA.9 function.
 * |        |          |0 = GPIO function is selected to the pin PA.9.
 * |        |          |1 = I2C0_SCL function is selected to the pin PA.9.
 * |[10]    |GPA_MFP10 |PA.10 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]) and GPA_MFP[10] determine the PA.10 function.
 * |        |          |(EBI_EN, GPA_MFP10) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = I2C1_SDA function is selected.
 * |        |          |(1, 1) = nWR(EBI) function is selected.     
 * |[11]    |GPA_MFP11 |PA.11 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]) and GPA_MFP[11] determine the PA.11 function.
 * |        |          |(EBI_EN, GPA_MFP11) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = I2C1_SCL function is selected.
 * |        |          |(1, 1) = nRD(EBI) function is selected.     
 * |[12]    |GPA_MFP12 |PA.12 Pin Function Selection
 * |        |          |Bits EBI_HB_EN[5] (ALT_MFP[21]), EBI_EN (ALT_MFP[11]), PA12_SC2DAT (ALT_MFP1[11]) and GPA_MFP[12] determine the PA.12 function.
 * |        |          |(EBI_HB_EN[5], EBI_EN, PA12_SC2DAT, GPA_MFP12) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM0 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_DAT function is selected.
 * |        |          |(1, 1, 0, 1) = AD13 function is selected.       
 * |[13]    |GPA_MFP13 |PA.13 Pin Function Selection     
 * |        |          |Bits EBI_HB_EN[6] (ALT_MFP[22]), EBI_EN (ALT_MFP[11]), PA13_SC2CLK (ALT_MFP1[10]) and GPA_MFP[13] determine the PA.13 function.
 * |        |          |(EBI_HB_EN[6], EBI_EN, PA13_SC2CLK, GPA_MFP13) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM1 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_CLK function is selected.
 * |        |          |(1, 1, 0, 1) = AD14 function is selected.        
 * |[14]    |GPA_MFP14 |PA.14 Pin Function Selection
 * |        |          |Bits EBI_HB_EN[7] (ALT_MFP[23]), EBI_EN (ALT_MFP[11]), PA14_SC2RST (ALT_MFP1[13]) and GPA_MFP[14] determine the PA.14 function.
 * |        |          |(EBI_HB_EN , EBI_EN, PA14_SC2RST, GPA_MFP14) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM2 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD15 function is selected.        
 * |[15]    |GPA_MFP15 |PA.15 Pin Function Selection     
 * |        |          |Bits PA15_SC2PWR (ALT_MFP1[12]), PA15_I2SMCLK (ALT_MFP[9]) and GPA_MFP[15] determine the PA.15 function.
 * |        |          |(PA15_SC2PWR, PA15_I2SMCLK, GPA_MFP15) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = PWM3 function is selected.
 * |        |          |(0, 1, 1) = I2S_MCLK function is selected.
 * |        |          |(1, 0, 1) = SC2_PWR function is selected.         
 * |[16:31] |GPA_TYPEn |Trigger Function Selection
 * |        |          |0 = GPIOA[15:0] I/O input Schmitt Trigger function Disabled.
 * |        |          |1 = GPIOA[15:0] I/O input Schmitt Trigger function Enabled.
 * @var GCR_T::GPB_MFP
 * Offset: 0x34  GPIOB Multiple Function and Input Type Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GPB_MFP0  |PB.0 Pin Function Selection     
 * |        |          |Bit GPB_MFP[0] determines the PB.0 function.
 * |        |          |0 = GPIO function is selected to the pin PB.0.
 * |        |          |1 = UART0_RXD function is selected to the pin PB.0.       
 * |[1]     |GPB_MFP1  |PB.1 Pin Function Selection
 * |        |          |Bit GPB_MFP[1] determines the PB.1 function.
 * |        |          |0 = GPIO function is selected to the pin PB.1.
 * |        |          |1 = UART0_TXD function is selected to the pin PB.1.     
 * |[2]     |GPB_MFP2  |PB.2 Pin Function Selection
 * |        |          |Bits EBI_nWRL_EN (ALT_MFP[13]), EBI_EN (ALT_MFP[11]), PB2_T2EX (ALT_MFP[26]) and GPB_MFP[2] determine the PB.2 function.
 * |        |          |(EBI_nWRL_EN, EBI_EN, PB2_T2EX, GPB_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = UART0_nRTS function is selected.
 * |        |          |(0, 0, 1, 1) = TM2_EXT function is selected.
 * |        |          |(1, 1, 0, 1) = nWRL(EBI) function is selected.     
 * |[3]     |GPB_MFP3  |PB.3 Pin Function Selection
 * |        |          |Bits EBI_nWRH_EN (ALT_MFP[14]), EBI_EN (ALT_MFP[11]), PB3_SC2CD (ALT_MFP1[14]), PB3_T3EX (ALT_MFP[27]) and GPB_MFP[3] determine the PB.3 function.
 * |        |          |(EBI_nWRH_EN, EBI_EN, PB3_SC2CD, PB3_T3EX, GPB_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 0, 1) = UART0_nCTS function is selected.
 * |        |          |(0, 0, 0, 1, 1) = TM3_EXT function is selected.
 * |        |          |(0, 0, 1, 0, 1) = SC2_CD function is selected.
 * |        |          |(1, 1, 0, 0, 1) = nWRH(EBI) function is selected.              
 * |[4]     |GPB_MFP4  |PB.4 Pin Function Selection
 * |        |          |Bit GPB_MFP[4] determines the PB.4 function.
 * |        |          |0 = GPIO function is selected to the pin PB.4.
 * |        |          |1 = UART1_RXD function is selected to the pin PB.4.     
 * |[5]     |GPB_MFP5  |PB 5 Pin Function Selection
 * |        |          |Bit GPB_MFP[5] determines the PB.5 function.
 * |        |          |0 = GPIO function is selected to the pin PB.5.
 * |        |          |1 = UART1_TXD function is selected to the pin PB.5.     
 * |[6]     |GPB_MFP6  |PB.6 Pin Function Selection 
 * |        |          |Bit EBI_EN (ALT_MFP[11]) and GPB_MFP[6] determines the PB.6 function.
 * |        |          |(EBI_EN, GPB_MFP6) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = UART1_nRTS function is selected .
 * |        |          |(1, 1) = ALE(EBI) function is selected.
 * |[7]     |GPB_MFP7  |PB.7 Pin Function Selection
 * |        |          |Bit EBI_EN (ALT_MFP[11]) and GPB_MFP[7] determines the PB.7 function.
 * |        |          |(EBI_EN, GPB_MFP7) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = UART1_nCTS function is selected.
 * |        |          |(1, 1) = nCS(EBI) function is selected.         
 * |[8]     |GPB_MFP8  |PB.8 Pin Function Selection
 * |        |          |Bit GPB_MFP[8] determines the PB.8 function.
 * |        |          |0 = GPIO function is selected to the pin PB.8.
 * |        |          |1 = TM0 function is selected to the pin PB.8.        
 * |[9]     |GPB_MFP9  |PB.9 Pin Function Selection
 * |        |          |Bits PB9_S11 (ALT_MFP[1]) and GPB_MFP[9] determine the PB.9 function.
 * |        |          |(PB9_S11, GPB_MFP9) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = TM1 function is selected.
 * |        |          |(1, 1) = SPI1_SS1 function is selected.         
 * |[10]    |GPB_MFP10 |PB.10 Pin Function Selection
 * |        |          |Bits PB10_S01 (ALT_MFP[0]) and GPB_MFP[10] determine the PB.10 function.
 * |        |          |(PB10_S01, GPB_MFP10) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = TM2 function is selected.
 * |        |          |(1, 1) = SPI0_SS1 function is selected.     
 * |[11]    |GPB_MFP11 |PB.11 Pin Function Selection
 * |        |          |Bits PB11_PWM4 (ALT_MFP[4]) and GPB_MFP[11] determine the PB.11 function.
 * |        |          |(PB11_PWM4, GPB_MFP11) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = TM3 function is selected.     
 * |        |          |(1, 1) = PWM4 function is selected. 
 * |[12]    |GPB_MFP12 |PB.12 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PB12_CLKO (ALT_MFP[10]) and GPB_MFP[12] determine the PB.12 function.
 * |        |          |(EBI_EN, PB12_CLKO, GPB_MFP12) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ACMP0_O function is selected.
 * |        |          |(0, 1, 1) = CLKO (Clock Driver output) function is selected.     
 * |        |          |(1, 0, 1) = AD0 function is selected.   
 * |[13]    |GPB_MFP13 |PB.13 Pin Function Selection
 * |        |          |Bit EBI_EN (ALT_MFP[11]) and GPB_MFP[13] determines the PB.13 function.
 * |        |          |(EBI_EN, GPB_MFP13) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = ACMP1_O function is selected.
 * |        |          |(1, 1) = AD1 function is selected.     
 * |[14]    |GPB_MFP14 |PB.14 Pin Function Selection
 * |        |          |Bits PB14_S31 (ALT_MFP[3]) and GPB_MFP[14] determine the PB.14 function.
 * |        |          |(PB14_S31, GPB_MFP14) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = INT0 function is selected.
 * |        |          |(1, 1) = SPI3_SS1 function is selected.
 * |[15]    |GPB_MFP15 |PB.15 Pin Function Selection
 * |        |          |Bits PB15_T0EX (ALT_MFP[24]) and GPB_MFP[15] determine the PB.15 function.
 * |        |          |(PB15_T0EX, GPB_MFP15) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = INT1 function is selected.
 * |        |          |(1, 1) = TM0_EXT function is selected.  
 * |[16:31] |GPB_TYPEn |Trigger Function Selection
 * |        |          |0 = GPIOB[15:0] I/O input Schmitt Trigger function Disabled.
 * |        |          |1 = GPIOB[15:0] I/O input Schmitt Trigger function Enabled.
 * @var GCR_T::GPC_MFP
 * Offset: 0x38  GPIOC Multiple Function and Input Type Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GPC_MFP0  |PC.0 Pin Function Selection
 * |        |          |Bits PC0_I2SLRCLK (ALT_MFP[5]) and GPC_MFP[0] determine the PC.0 function.
 * |        |          |(PC0_I2SLRCLK, GPC_MFP0) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_SS0 function is selected.
 * |        |          |(1, 1) = I2S_LRCLK function is selected.          
 * |[1]     |GPC_MFP1  |PC.1 Pin Function Selection
 * |        |          |Bits PC1_I2SBCLK (ALT_MFP[6]) and GPC_MFP[1] determine the PC.1 function.
 * |        |          |(PC1_I2SBCLK, GPC_MFP1) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_CLK function is selected.
 * |        |          |(1, 1) = I2S_BCLK function is selected.     
 * |[2]     |GPC_MFP2  |PC.2 Pin Function Selection
 * |        |          |Bits PC2_I2SDI (ALT_MFP[7]) and GPC_MFP[2] determine the PC.2 function.
 * |        |          |(PC2_I2SDI, GPC_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_MISO0 function is selected.
 * |        |          |(1, 1) = I2S_DI function is selected.
 * |[3]     |GPC_MFP3  |PC.3 Pin Function Selection
 * |        |          |Bits PC3_I2SDO (ALT_MFP[8]) and GPC_MFP[3] determine the PC.3 function.
 * |        |          |(PC3_I2SDO, GPC_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_MOSI0 function is selected.
 * |        |          |(1, 1) = I2S_DO function is selected.     
 * |[4]     |GPC_MFP4  |PC.4 Pin Function Selection
 * |        |          |Bit GPC_MFP[9] determines the PC.4 function.
 * |        |          |0 = GPIO function is selected to the pin PC.4.
 * |        |          |1 = SPI0_MISO1 function is selected to the pin PC.4.     
 * |[5]     |GPC_MFP5  |PC.5 Pin Function Selection
 * |        |          |Bit GPC_MFP[5] determines the PC.5 function.
 * |        |          |0 = GPIO function is selected to the pin PC.5.
 * |        |          |1 = SPI0_MOSI1 function is selected to the pin PC.5.     
 * |[6]     |GPC_MFP6  |PC.6 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]). PC6_SC0CD (ALT_MFP1[4]) and GPC_MFP[6] determine the PC.6 function.
 * |        |          |(EBI_EN, PC6_SC0CD, GPC_MFP6) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ACMP0_P function is selected.
 * |        |          |(0, 1, 1) = SC0_CD function is selected.
 * |        |          |(1, 0, 1) = AD4 function is selected.     
 * |[7]     |GPC_MFP7  |PC.7 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PC7_SC1CD (ALT_MFP1[9]) and GPC_MFP[7] determine the PC.7 function.
 * |        |          |(EBI_EN, PC7_SC1CD, GPC_MFP7) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ACMP0_N function is selected.
 * |        |          |(0, 1, 1) = SC1_CD function is selected.
 * |        |          |(1, 0, 1) = AD5 function is selected.      
 * |[8]     |GPC_MFP8  |PC.8 Pin Function Selection
 * |        |          |Bits EBI_MCLK_EN (ALT_MFP[12]), EBI_EN (ALT_MFP[11]), GPC_MFP[8] determine the PC.8 function.
 * |        |          |(EBI_MCLK_EN, EBI_EN, GPC_MFP8) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0 ,1) = SPI1_SS0 function is selected.
 * |        |          |(1, 1, 1) = MCLK(EBI) function is selected.     
 * |[9]     |GPC_MFP9  |PC.9 Pin Function Selection
 * |        |          |Bit GPC_MFP[9] determines the PC.9 function.
 * |        |          |0 = GPIO function is selected to the pin PC.9.
 * |        |          |1 = SPI1_CLK function is selected to the pin PC.9.          
 * |[10]    |GPC_MFP10 |PC.10 Pin Function Selection
 * |        |          |Bit GPC_MFP[10] determines the PC.10 function.
 * |        |          |0 = GPIO function is selected to the pin PC.10.
 * |        |          |1 = SPI1_MISO0 function is selected to the pin PC.10.    
 * |[11]    |GPC_MFP11 |PC.11 Pin Function Selection
 * |        |          |Bit GPC_MFP[11] determines the PC.11 function.
 * |        |          |0 = GPIO function is selected to the pin PC.11.
 * |        |          |1 = SPI1_MOSI0 function is selected to the pin PC.11.        
 * |[12]    |GPC_MFP12 |PC.12 Pin Function Selection
 * |        |          |Bit GPC_MFP[12] determines the PC.12 function.
 * |        |          |0 = GPIO function is selected to the pin PC.12.
 * |        |          |1 = SPI1_MISO1 function is selected to the pin PC.12.      
 * |[13]    |GPC_MFP13 |PC.13 Pin Function Selection
 * |        |          |Bit GPC_MFP[13] determines the PC.13 function.
 * |        |          |0 = GPIO function is selected to the pin PC.13.
 * |        |          |1 = SPI1_MOSI1 function is selected to the pin PC.13.     
 * |[14]    |GPC_MFP14 |PC.14 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]) and GPC_MFP[14] determine the PC.14 function.
 * |        |          |(EBI_EN, GPC_MFP14) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = ACMP1_P function is selected.
 * |        |          |(1, 1) = AD2 function is selected.       
 * |[15]    |GPC_MFP15 |PC.15 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]) and GPC_MFP[15] determine the PC.15 function.
 * |        |          |(EBI_EN, GPC_MFP15) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = ACMP1_N function is selected.
 * |        |          |(1, 1) = AD3 function is selected.        
 * |[16:31] |GPC_TYPEn |Trigger Function Selection
 * |        |          |0 = GPIOC[15:0] I/O input Schmitt Trigger function Disabled.
 * |        |          |1 = GPIOC[15:0] I/O input Schmitt Trigger function Enabled.
 * @var GCR_T::GPD_MFP
 * Offset: 0x3C  GPIOD Multiple Function and Input Type Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GPD_MFP0  |PD.0 Pin Function Selection
 * |        |          |Bit GPD_MFP[0] determines the PD.0 function.
 * |        |          |0 = GPIO function is selected to the pin PD.0.
 * |        |          |1 = SPI2_SS0 function is selected to the pin PD.0.     
 * |[1]     |GPD_MFP1  |PD.1 Pin Function Selection
 * |        |          |Bit GPD_MFP[1] determines the PD.1 function.
 * |        |          |0 = GPIO function is selected to the pin PD.1.
 * |        |          |1 = SPI2_CLK function is selected to the pin PD.1.
 * |[2]     |GPD_MFP2  |PD.2 Pin Function Selection
 * |        |          |Bit GPD_MFP[2] determines the PD.2 function.
 * |        |          |0 = GPIO function is selected to the pin PD.2.
 * |        |          |1 = SPI2_MISO0 function is selected to the pin PD.2.     
 * |[3]     |GPD_MFP3  |PD.3 Pin Function Selection
 * |        |          |Bit GPD_MFP[3] determines the PD.3 function.
 * |        |          |0 = GPIO function is selected to the pin PD.3.
 * |        |          |1 = SPI2_MOSI0 function is selected to the pin PD.3.     
 * |[4]     |GPD_MFP4  |PD.4 Pin Function Selection
 * |        |          |Bit GPD_MFP[4] determines the PD.4 function.
 * |        |          |0 = GPIO function is selected to the pin PD.4.
 * |        |          |1 = SPI2_MISO1 function is selected to the pin PD.4.     
 * |[5]     |GPD_MFP5  |PD.5 Pin Function Selection
 * |        |          |Bit GPD_MFP[9] determines the PD.5 function.
 * |        |          |0 = GPIO function is selected to the pin PD.5.
 * |        |          |1 = SPI2_MOSI1 function is selected to the pin PD.5.      
 * |[8]     |GPD_MFP8  |PD.8 Pin Function Selection
 * |        |          |Bit GPD_MFP[8] determines the PD.8 function.
 * |        |          |0 = GPIO function is selected to the pin PD.8.
 * |        |          |1 = SPI3_SS0 function is selected to the pin PD.8.     
 * |[9]     |GPD_MFP9  |PD.9 Pin Function Selection
 * |        |          |Bit GPD_MFP[9] determines the PD.9 function.
 * |        |          |0 = GPIO is function is selected to the pin PD.9.
 * |        |          |1 = SPI3_CLK function is selected to the pin PD.9.     
 * |[10]    |GPD_MFP10 |PD.10 Pin Function Selection
 * |        |          |Bit GPD_MFP[10] determines the PD.10 function.
 * |        |          |0 = GPIO function is selected to the pin PD.10.
 * |        |          |1 = SPI3_MISO0 function is selected to the pin PD.10.     
 * |[11]    |GPD_MFP11 |PD.11 Pin Function Selection
 * |        |          |Bit GPD_MFP[11] determines the PD.11 function.
 * |        |          |0 = GPIO function is selected to the pin PD.11.
 * |        |          |1 = SPI3_MOSI0 function is selected to the pin PD.11.     
 * |[12]    |GPD_MFP12 |PD.12 Pin Function Selection
 * |        |          |Bit GPD_MFP[12] determines the PD.12 function.
 * |        |          |0 = GPIO function is selected to the pin PD.12.
 * |        |          |1 = SPI3_MISO1 function is selected to the pin PD.12.     
 * |[13]    |GPD_MFP13 |PD.13 Pin Function Selection
 * |        |          |Bit GPD_MFP[13] determines the PD.13 function.
 * |        |          |0 = GPIO function is selected to the pin PD.13.
 * |        |          |1 = SPI3_MOSI1 function is selected to the pin PD.13.     
 * |[14]    |GPD_MFP14 |PD.14 Pin Function Selection
 * |        |          |Bit GPD_MFP[14] determines the PD.14 function.
 * |        |          |0 = GPIO function is selected.
 * |        |          |1 = UART2_RXD function is selected.  
 * |[15]    |GPD_MFP15 |PD.15 Pin Function Selection
 * |        |          |Bit GPD_MFP[15] determines the PD.15 function.
 * |        |          |0 = GPIO function is selected.
 * |        |          |1 = UART2_TXD function is selected.  
 * |[16:31] |GPD_TYPEn |Trigger Function Selection
 * |        |          |0 = GPIOD[15:0] I/O input Schmitt Trigger function Disabled.
 * |        |          |1 = GPIOD[15:0] I/O input Schmitt Trigger function Enabled.
 * @var GCR_T::GPE_MFP
 * Offset: 0x40  GPIOE Multiple Function and Input Type Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GPE_MFP0  |PE.0 Pin Function Selection
 * |        |          |Bit GPE_MFP[0] determines the PE.0 function.
 * |        |          |0 = GPIO function is selected to the pin PE.0.
 * |        |          |1 = PWM6 function is selected to the pin PE.0.     
 * |[1]     |GPE_MFP1  |PE.1 Pin Function Selection
 * |        |          |Bit GPE_MFP[1] determines the PE.1 function.
 * |        |          |0 = GPIO function is selected to the pin PE.1.
 * |        |          |1 = PWM7 function is selected to the pin PE.1.     
 * |[5]     |GPE_MFP5  |PE.5 Pin Function Selection
 * |        |          |Bits PE5_T1EX (ALT_MFP[25]) and GPE_MFP5 determine the PE.5 function.
 * |        |          |(PE5_T1EX, GPE_MFP5) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = PWM5 function is selected.
 * |        |          |(1, 1) = TM1_EXT function is selected.  
 * |[16:31] |GPE_TYPEn |Trigger Function Selection
 * |        |          |0 = GPIOD[15:0] I/O input Schmitt Trigger function Disabled.
 * |        |          |1 = GPIOD[15:0] I/O input Schmitt Trigger function Enabled.
 * @var GCR_T::GPF_MFP
 * Offset: 0x44  GPIOF Multiple Function and Input Type Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |GPF_MFP0  |PF.0 Pin Function Selection
 * |        |          |Bit GPF_MFP[0] determines the PF.0 function
 * |        |          |0 = GPIO function is selected to the pin PF.0.
 * |        |          |1 = XT1_OUT function is selected to the pin PF.0.
 * |        |          |Note: This bit is read only and is decided by user configuration CGPFMFP (Config0[27]).     
 * |[1]     |GPF_MFP1  |PF.1 Pin Function Selection
 * |        |          |Bit GPF_MFP[1] determines the PF.1 function.
 * |        |          |0 = GPIO function is selected to the pin PF.1.
 * |        |          |1 = XT1_IN function is selected to the pin PF.1.
 * |        |          |Note: This bit is read only and is decided by user configuration CGPFMFP (Config0[27]).     
 * |[2]     |GPF_MFP2  |PF.2 Pin Function Selection
 * |        |          |Bit GPF_MFP[2] determines the PF.2 function.
 * |        |          |0 = GPIO function is selected to the pin PF.2.
 * |        |          |1 = PS2_DAT function is selected to the pin PF.2.     
 * |[3]     |GPF_MFP3  |PF.3 Pin Function Selection
 * |        |          |Bit GPF_MFP[3] determines the PF.3 function.
 * |        |          |0 = GPIO function is selected to the pin PF.3.
 * |        |          |1 = PS2_CLK function is selected to the pin PF.3.     
 * |[16:19] |GPF_TYPEn |Trigger Function Selection
 * |        |          |0 = GPIOF[3:0] I/O input Schmitt Trigger function Disabled.
 * |        |          |1 = GPIOF[3:0] I/O input Schmitt Trigger function Enabled.
 * @var GCR_T::ALT_MFP
 * Offset: 0x50  Alternative Multiple Function Pin Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PB10_S01  |PB.10 Pin Alternative Function Selection
 * |        |          |Bits PB10_S01 (ALT_MFP[0]) and GPB_MFP[10] determine the PB.10 function.
 * |        |          |(PB10_S01, GPB_MFP10) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = TM2 function is selected.
 * |        |          |(1, 1) = SPI0_SS1 function is selected.       
 * |[1]     |PB9_S11   |PB.9 Pin Alternative Function Selection
 * |        |          |Bits PB9_S11 (ALT_MFP[1]) and GPB_MFP[9] determine the PB.9 function.
 * |        |          |(PB9_S11, GPB_MFP9) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = TM1 function is selected.
 * |        |          |(1, 1) = SPI1_SS1 function is selected.           
 * |[2]     |PA7_S21   |PA.7 Pin Alternative Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PA7_SC1DAT (ALT_MFP1[6]), PA7_S21 (ALT_MFP[2]) and GPA_MFP[7] determine the PA.7 function.
 * |        |          |(EBI_EN, PA7_SC1DAT, PA7_S21, GPA_MFP7) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC7 function is selected.
 * |        |          |(0, 0, 1, 1) = SPI2_SS1 function is selected.
 * |        |          |(0, 1, 0, 1) = SC1_DAT function is selected.
 * |        |          |(1, 0, 0, 1) = AD6 function is selected.                  
 * |[3]     |PB14_S31  |PB.14 Pin Alternative Function Selection
 * |        |          |Bits PB14_S31 (ALT_MFP[3]) and GPB_MFP[14] determine the PB.14 function.
 * |        |          |(PB14_S31, GPB_MFP14) value and function mapping is as following list
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = INT0 function is selected.
 * |        |          |(1, 1) = SPI3_SS1 function is selected.  
 * |[4]     |PB11_PWM4 |PB.11 Pin Alternative Function Selection     
 * |        |          |Bits PB11_PWM4 (ALT_MFP[4]) and GPB_MFP[11] determine the PB.11 function.
 * |        |          |(PB11_PWM4, GPB_MFP11) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = TM3 function is selected.     
 * |        |          |(1, 1) = PWM4 function is selected.      
 * |[5]     |PC0_I2SLRCLK|PC.0 Pin Alternative Function Selection
 * |        |          |Bits PC0_I2SLRCLK (ALT_MFP[5]) and GPC_MFP[0] determine the PC.0 function.
 * |        |          |(PC0_I2SLRCLK, GPC_MFP0) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_SS0 function is selected.
 * |        |          |(1, 1) = I2S_LRLCK function is selected.         
 * |[6]     |PC1_I2SBCLK|PC.1 Pin Alternative Function Selection
 * |        |          |Bits PC0_I2SLRCLK (ALT_MFP[5]) and GPC_MFP[0] determine the PC.0 function.
 * |        |          |(PC0_I2SLRCLK, GPC_MFP0) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_SS0 function is selected.
 * |        |          |(1, 1) = I2S_LRCK function is selected.         
 * |[7]     |PC2_I2SDI |PC.2 Pin Alternative Function Selection
 * |        |          |Bits PC2_I2SDI (ALT_MFP[7]) and GPC_MFP[2] determine the PC.2 function.
 * |        |          |(PC2_I2SDI, GPC_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_MISO0 function is selected.
 * |        |          |(1, 1) = I2S_DI function is selected.     
 * |[8]     |PC3_I2SDO |PC.3 Pin Alternative Function Selection
 * |        |          |Bits PC3_I2SDO (ALT_MFP[8]) and GPC_MFP[3] determine the PC.3 function.
 * |        |          |(PC3_I2SDO, GPC_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = SPI0_MOSI0 function is selected.
 * |        |          |(1, 1) = I2S_DO function is selected. 
 * |[9]     |PA15_I2SMCLK|PA.15 Pin Alternative Function Selection
 * |        |          |Bits PA15_SC2PWR (ALT_MFP1[12]), PA15_I2SMCLK (ALT_MFP[9]) and GPA_MFP[15] determine the PA.15 function.
 * |        |          |(PA15_SC2PWR, PA15_I2SMCLK, GPA_MFP15) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = PWM3 function is selected.
 * |        |          |(0, 1, 1) = I2S_MCLK function is selected.
 * |        |          |(1, 0, 1) = SC2_PWR function is selected.  
 * |[10]    |PB12_CLKO |PB.12 Pin Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PB12_CLKO (ALT_MFP[10]) and GPB_MFP[12] determine the PB.12 function.
 * |        |          |(EBI_EN, PB12_CLKO, GPB_MFP12) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ACMP0_O function is selected.
 * |        |          |(0, 1, 1) = CLKO (Clock Driver output) function is selected.     
 * |        |          |(1, 0, 1) = AD0 function is selected.          
 * |[11]    |EBI_EN    |EBI Pin Function Selection
 * |        |          |EBI_EN is use to switch GPIO function to EBI function (AD[15:0], ALE, RE, WE, CS, MCLK), it need additional registers EBI_EN[7:0] and EBI_MCLK_EN for some GPIO to switch to EBI function(AD[15:8], MCLK).
 * |[12]    |EBI_MCLK_EN|PC.8 Pin Alternative Function Selection
 * |        |          |Bits EBI_MCLK_EN (ALT_MFP[12]), EBI_EN (ALT_MFP[11]), GPC_MFP[8] determine the PC.8 function.
 * |        |          |(EBI_MCLK_EN, EBI_EN, GPC_MFP8) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0 ,1) = SPI1_SS0 function is selected.
 * |        |          |(1, 1, 1) = MCLK(EBI) function is selected.
 * |[13]    |EBI_nWRL_EN|PB.2 Pin Alternative Function Selection
 * |        |          |Bits EBI_nWRL_EN (ALT_MFP[13]), EBI_EN (ALT_MFP[11]) PB2_T2EX (ALT_MFP[26]) and GPB_MFP[2] determine the PB.2 function.
 * |        |          |(EBI_nWRL_EN, EBI_EN, PB2_T2EX, GPB_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = UART0_nRTS function is selected.
 * |        |          |(0, 0, 1, 1) = TM2_EXT function is selected.
 * |        |          |(1, 1, 0, 1) = nWRL(EBI) function is selected. 
 * |[14]    |EBI_nWRH_EN|PB.3 Pin Alternative Function Selection
 * |        |          |Bits EBI_nWRH_EN (ALT_MFP[14]), EBI_EN (ALT_MFP[11]), PB3_SC2CD (ALT_MFP1[14]), PB3_T3EX (ALT_MFP[27]) and GPB_MFP[3] determine the PB.3 function.
 * |        |          |(EBI_nWRH_EN, EBI_EN, PB3_SC2CD, PB3_T3EX, GPB_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 0, 1) = UART0_nCTS function is selected.
 * |        |          |(0, 0, 0, 1, 1) = TM3_EXT function is selected.
 * |        |          |(0, 0, 1, 0, 1) = SC2_CD function is selected.
 * |        |          |(1, 1, 0, 0, 1) = nWRH(EBI) function is selected.   
 * |[16]    |EBI_HB_EN[0]|PA.5 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[0] (ALT_MFP[16]), EBI_EN (ALT_MFP[11]), PA5_SC1RST (ALT_MFP1[8]) and GPA_MFP[5] determine the PA.5 function.
 * |        |          |(EBI_HB_EN[0], EBI_EN, PA5_SC1RST, GPA_MFP5) value and function mapping is as following list,
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC5 function is selected.
 * |        |          |(0, 0, 1, 1) = SC1_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD8 function is selected.    
 * |[17]    |EBI_HB_EN[1]|PA.4 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[1] (ALT_MFP[17]), EBI_EN (ALT_MFP[11]), PA4_SC1PWR (ALT_MFP1[7]) and GPA_MFP[4] determine the PA.4 function.
 * |        |          |(EBI_HB_EN[1], EBI_EN, PA4_SC1PWR, GPA_MFP4) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC4 function is selected.
 * |        |          |(0, 0, 1, 1) = SC1_PWR function is selected.
 * |        |          |(1, 1, 0, 1) = AD9 function is selected.        
 * |[18]    |EBI_HB_EN[2]|PA.3 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[2] (ALT_MFP[18]), EBI_EN (ALT_MFP[11]), PA3_SC0DAT (ALT_MFP1[1]) and GPA_MFP[3] determine the PA.3 function.
 * |        |          |(EBI_HB_EN[2], EBI_EN, PA3_SC0DAT, GPA_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC3 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_DAT function is selected.
 * |        |          |(1, 1, 0, 1) = AD10 function is selected.
 * |[19]    |EBI_HB_EN[3]|PA.2 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[3] (ALT_MFP[19]), EBI_EN (ALT_MFP[11]), PA2_SC0CLK (ALT_MFP1[0]) and GPA_MFP[2] determine the PA.2 function.
 * |        |          |(EBI_HB_EN[3], EBI_EN, PA2_SC0CLK, GPA_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC2 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_CLK function is selected.
 * |        |          |(1, 1, 0, 1) = AD11 function is selected.   
 * |[20]    |EBI_HB_EN[4]|PA.1 Pin Alternative Function Selection
 * |        |          |Bit EBI_HB_EN[4] (ALT_MFP[20]), EBI_EN (ALT_MFP[11]), PA1_SC0RST (ALT_MFP1[3]) and GPA_MFP[1] determine the PA.1 function.
 * |        |          |(EBI_HB_EN[4], EBI_EN, PA1_SC0RST, GPA_MFP1) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC1 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD12 function is selected.   
 * |[21]    |EBI_HB_EN[5]|PA.12 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[5] (ALT_MFP[21]), EBI_EN (ALT_MFP[11]), PA12_SC2DAT (ALT_MFP1[11]) and GPA_MFP[12] determine the PA.12 function.
 * |        |          |(EBI_HB_EN[5], EBI_EN, PA12_SC2DAT, GPA_MFP12) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM0 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_DAT function is selected.
 * |        |          |(1, 1, 0, 1) = AD13 function is selected.
 * |[22]    |EBI_HB_EN[6]|PA.13 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[6] (ALT_MFP[22]), EBI_EN (ALT_MFP[11]), PA13_SC2CLK (ALT_MFP1[10]) and GPA_MFP[13] determine the PA.13 function.
 * |        |          |(EBI_HB_EN[6], EBI_EN, PA13_SC2CLK, GPA_MFP13) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM1 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_CLK function is selected.
 * |        |          |(1, 1, 0, 1) = AD14 function is selected. 
 * |[23]    |EBI_HB_EN[7]|PA.14 Pin Alternative Function Selection     
 * |        |          |Bits EBI_HB_EN[7] (ALT_MFP[23]), EBI_EN (ALT_MFP[11]), PA14_SC2RST (ALT_MFP1[13]) and GPA_MFP[14] determine the PA.14 function.
 * |        |          |(EBI_HB_EN , EBI_EN, PA14_SC2RST, GPA_MFP14) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM2 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD15 function is selected.       
 * |[24]    |PB15_T0EX |PB.15 Pin Alternative Function Selection  
 * |        |          |Bits PB15_T0EX (ALT_MFP[24]) and GPB_MFP[15] determine the PB.15 function.
 * |        |          |(PB15_T0EX, GPB_MFP15) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = INT1 function is selected.
 * |        |          |(1, 1) = TM0_EXT function is selected. 
 * |[25]    |PE5_T1EX  |PE.5 Pin Alternative Function Selection
 * |        |          |Bits PE5_T1EX (ALT_MFP[25]) and GPE_MFP5 determine the PE.5 function.
 * |        |          |(PE5_T1EX, GPE_MFP5) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = PWM5 function is selected.
 * |        |          |(1, 1) = TM1_EXT function is selected.   
 * |[26]    |PB2_T2EX  |PB.2 Pin Alternative Function Selection
 * |        |          |Bits EBI_nWRL_EN (ALT_MFP[13]), EBI_EN (ALT_MFP[11]), PB2_T2EX (ALT_MFP[26]) and GPB_MFP[2] determine the PB.2 function.
 * |        |          |(EBI_nWRL_EN, EBI_EN, PB2_T2EX, GPB_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = UART0_nRTS function is selected.
 * |        |          |(0, 0, 1, 1) = TM2_EXT function is selected.
 * |        |          |(1, 1, 0, 1) = nWRL(EBI) function is selected.           
 * |[27]    |PB3_T3EX  |PB.3 Pin Alternative Function Selection
 * |        |          |Bits EBI_nWRH_EN (ALT_MFP[14]), EBI_EN (ALT_MFP[11]), PB3_SC2CD (ALT_MFP1[14]), PB3_T3EX (ALT_MFP[27]) and GPB_MFP[3] determine the PB.3 function.
 * |        |          |(EBI_nWRH_EN, EBI_EN, PB3_SC2CD, PB3_T3EX, GPB_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 0, 1) = UART0_nCTS function is selected.
 * |        |          |(0, 0, 0, 1, 1) = TM3_EXT function is selected.
 * |        |          |(0, 0, 1, 0, 1) = SC2_CD function is selected.
 * |        |          |(1, 1, 0, 0, 1) = nWRH(EBI) function is selected.
 * @var GCR_T::ALT_MFP1
 * Offset: 0x58  Alternative Multiple Function Pin Control Register 1
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |PA2_SC0CLK|PA.2 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[3] (ALT_MFP[19]), EBI_EN (ALT_MFP[11]), PA2_SC0CLK (ALT_MFP1[0]) and GPA_MFP[2] determine the PA.2 function.
 * |        |          |(EBI_HB_EN[3], EBI_EN, PA2_SC0CLK, GPA_MFP2) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC2 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_CLK function is selected.
 * |        |          |(1, 1, 0, 1) = AD11 function is selected.               
 * |[1]     |PA3_SC0DAT|PA.3 Pin Alternative Function Selection 
 * |        |          |Bits EBI_HB_EN[2] (ALT_MFP[18]), EBI_EN (ALT_MFP[11]), PA3_SC0DAT (ALT_MFP1[1]) and GPA_MFP[3] determine the PA.3 function.
 * |        |          |(EBI_HB_EN[2], EBI_EN, PA3_SC0DAT, GPA_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC3 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_DAT function is selected.
 * |        |          |(1, 1, 0, 1) = AD10 function is selected.   
 * |[2]     |PA0_SC0PWR|PA.0 Pin Alternative Function Selection
 * |        |          |Bit PA0_SC0PWR (ALT_MFP1[2]) and GPA_MFP[0] determine the PA.0 function.
 * |        |          |(PA0_SC0PWR, GPA_MFP0) value and function mapping is as following list.
 * |        |          |(0, 0) = GPIO function is selected.
 * |        |          |(0, 1) = ADC0 function is selected.
 * |        |          |(1, 1) = SC0_PWR function is selected.  
 * |[3]     |PA1_SC0RST|PA.1 Pin Alternative Function Selection     
 * |        |          |Bit EBI_HB_EN[4] (ALT_MFP[20]), EBI_EN (ALT_MFP[11]), PA1_SC0RST (ALT_MFP1[3]) and GPA_MFP[1] determine the PA.1 function.
 * |        |          |(EBI_HB_EN[4], EBI_EN, PA1_SC0RST, GPA_MFP1) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC1 function is selected.
 * |        |          |(0, 0, 1, 1) = SC0_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD12 function is selected.       
 * |[4]     |PC6_SC0CD |PC.6 Pin Alternative Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]). PC6_SC0CD (ALT_MFP1[4]) and GPC_MFP[6] determine the PC.6 function.
 * |        |          |(EBI_EN, PC6_SC0CD, GPC_MFP6) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ACMP0_P function is selected.
 * |        |          |(0, 1, 1) = SC0_CD function is selected.
 * |        |          |(1, 0, 1) = AD4 function is selected.        
 * |[5]     |PA6_SC1CLK|PA.6 Pin Alternative Function Selection     
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PA6_SC1CLK (ALT_MFP1[5]) and GPA_MFP[6] determine the PA.6 function.
 * |        |          |(EBI_EN, PA6_SC1CLK, GPA_MFP6) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ADC6 function is selected.
 * |        |          |(0, 1, 1) = SC1_CLK function is selected.
 * |        |          |(1, 0, 1) = AD7 function is selected.          
 * |[6]     |PA7_SC1DAT|PA.7 Pin Alternative Function Selection
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PA7_SC1DAT (ALT_MFP1[6]), PA7_S21 (ALT_MFP[2]) and GPA_MFP[7] determine the PA.7 function.
 * |        |          |(EBI_EN, PA7_SC1DAT, PA7_S21, GPA_MFP7) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC7 function is selected.
 * |        |          |(0, 0, 1, 1) = SPI2_SS1 function is selected.
 * |        |          |(0, 1, 0, 1) = SC1_DAT function is selected.
 * |        |          |(1, 0, 0, 1) = AD6 function is selected.          
 * |[7]     |PA4_SC1PWR|PA.4 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[1] (ALT_MFP[17]), EBI_EN (ALT_MFP[11]), PA4_SC1PWR (ALT_MFP1[7]) and GPA_MFP[4] determine the PA.4 function.
 * |        |          |(EBI_HB_EN[1], EBI_EN, PA4_SC1PWR, GPA_MFP4) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC4 function is selected.
 * |        |          |(0, 0, 1, 1) = SC1_PWR function is selected.
 * |        |          |(1, 1, 0, 1) = AD9 function is selected.     
 * |[8]     |PA5_SC1RST|PA.5 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[0] (ALT_MFP[16]), EBI_EN (ALT_MFP[11]), PA5_SC1RST (ALT_MFP1[8]) and GPA_MFP[5] determine the PA.5 function.
 * |        |          |(EBI_HB_EN[0], EBI_EN, PA5_SC1RST, GPA_MFP5) value and function mapping is as following list,
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = ADC5 function is selected.
 * |        |          |(0, 0, 1, 1) = SC1_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD8 function is selected.     
 * |[9]     |PC7_SC1CD |PC.7 Pin Alternative Function Selection     
 * |        |          |Bits EBI_EN (ALT_MFP[11]), PC7_SC1CD (ALT_MFP1[9]) and GPC_MFP[7] determine the PC.7 function.
 * |        |          |(EBI_EN, PC7_SC1CD, GPC_MFP7) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = ACMP0_N function is selected.
 * |        |          |(0, 1, 1) = SC1_CD function is selected.
 * |        |          |(1, 0, 1) = AD5 function is selected.   
 * |[10]    |PA13_SC2CLK|PA.13 Pin Alternative Function Selection 
 * |        |          |Bits EBI_HB_EN[6] (ALT_MFP[22]), EBI_EN (ALT_MFP[11]), PA13_SC2CLK (ALT_MFP1[10]) and GPA_MFP[13] determine the PA.13 function.
 * |        |          |(EBI_HB_EN[6], EBI_EN, PA13_SC2CLK, GPA_MFP13) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM1 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_CLK function is selected.
 * |        |          |(1, 1, 0, 1) = AD14 function is selected.         
 * |[11]    |PA12_SC2DAT|PA.12 Pin Alternative Function Selection 
 * |        |          |Bits EBI_HB_EN[5] (ALT_MFP[21]), EBI_EN (ALT_MFP[11]), PA12_SC2DAT (ALT_MFP1[11]) and GPA_MFP[12] determine the PA.12 function.
 * |        |          |(EBI_HB_EN[5], EBI_EN, PA12_SC2DAT, GPA_MFP12) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM0 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_DAT function is selected.
 * |        |          |(1, 1, 0, 1) = AD13 function is selected.           
 * |[12]    |PA15_SC2PWR|PA.15 Pin Alternative Function Selection
 * |        |          |Bits PA15_SC2PWR (ALT_MFP1[12]), PA15_I2SMCLK (ALT_MFP[9]) and GPA_MFP[15] determine the PA.15 function.
 * |        |          |(PA15_SC2PWR, PA15_I2SMCLK, GPA_MFP15) value and function mapping is as following list.
 * |        |          |(0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 1) = PWM3 function is selected.
 * |        |          |(0, 1, 1) = I2S_MCLK function is selected.
 * |        |          |(1, 0, 1) = SC2_PWR function is selected.             
 * |[13]    |PA14_SC2RST|PA.14 Pin Alternative Function Selection
 * |        |          |Bits EBI_HB_EN[7] (ALT_MFP[23]), EBI_EN (ALT_MFP[11]), PA14_SC2RST (ALT_MFP1[13]) and GPA_MFP[14] determine the PA.14 function.
 * |        |          |(EBI_HB_EN , EBI_EN, PA14_SC2RST, GPA_MFP14) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 1) = PWM2 function is selected.
 * |        |          |(0, 0, 1, 1) = SC2_RST function is selected.
 * |        |          |(1, 1, 0, 1) = AD15 function is selected.             
 * |[14]    |PB3_SC2CD |PB.3 Pin Alternative Function Selection
 * |        |          |Bits EBI_nWRH_EN (ALT_MFP[14]), EBI_EN (ALT_MFP[11]), PB3_SC2CD (ALT_MFP1[14]), PB3_T3EX (ALT_MFP[27]) and GPB_MFP[3] determine the PB.3 function.
 * |        |          |(EBI_nWRH_EN, EBI_EN, PB3_SC2CD, PB3_T3EX, GPB_MFP3) value and function mapping is as following list.
 * |        |          |(0, 0, 0, 0, 0) = GPIO function is selected.
 * |        |          |(0, 0, 0, 0, 1) = UART0_nCTS function is selected.
 * |        |          |(0, 0, 0, 1, 1) = TM3_EXT function is selected.
 * |        |          |(0, 0, 1, 0, 1) = SC2_CD function is selected.
 * |        |          |(1, 1, 0, 0, 1) = nWRH(EBI) function is selected.
 * @var GCR_T::ALT_MFP2
 * Offset: 0x5C  Alternative Multiple Function Pin Control Register 2
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |Reserved  |Reserved
 * |        |          |Reserved
 * @var GCR_T::IRCTRIMCTL
 * Offset: 0x80  IRC Trim Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |TRIM_SEL  |Trim Frequency Selection
 * |        |          |This field indicates the target frequency of internal 22.1184 MHz high speed oscillator will trim to precise 22.1184MHz or 24MHz automatically.
 * |        |          |If no any target frequency is selected (TRIM_SEL is 00), the HIRC auto trim function is disabled.
 * |        |          |During auto trim operation, if clock error detected because of CLKERR_STOP_EN is set to 1 or trim retry limitation counts reached, this field will be cleared to 00 automatically.
 * |        |          |00 = HIRC auto trim function Disabled.
 * |        |          |01 = HIRC auto trim function Enabled and HIRC trimmed to 22.1184 MHz.
 * |        |          |10 = HIRC auto trim function Enabled and HIRC trimmed to 24 MHz.
 * |        |          |11 = Reserved.
 * |[5:4]   |TRIM_LOOP |Trim Calculation Loop
 * |        |          |This field defines that trim value calculation is based on how many 32.768 kHz clocks in.
 * |        |          |For example, if TRIM_LOOP is set as 00, auto trim circuit will calculate trim value based on the average frequency difference in 4 32.768 kHz clock.
 * |        |          |00 = Trim value calculation is based on average difference in 4 clocks.
 * |        |          |01 = Trim value calculation is based on average difference in 8 clocks.
 * |        |          |10 = Trim value calculation is based on average difference in 16 clocks.
 * |        |          |11 = Trim value calculation is based on average difference in 32 clocks.
 * |[7:6]   |TRIM_RETRY_CNT|Trim Value Update Limitation Count
 * |        |          |The field defines that how many times of HIRC trim value is updated by auto trim circuit before the HIRC frequency locked.
 * |        |          |Once the HIRC locked, the internal trim value update counter will be reset.
 * |        |          |If the trim value update counter reached this limitation value and frequency of HIRC still doesn't lock, the auto trim operation will be disabled and TRIM_SEL will be cleared to 00.
 * |        |          |00 = Trim retry count limitation is 64.
 * |        |          |01 = Trim retry count limitation is 128.
 * |        |          |10 = Trim retry count limitation is 256.
 * |        |          |11 = Trim retry count limitation is 512.
 * |[8]     |CLKERR_STOP_EN|Clock Error Stop Enable
 * |        |          |When this bit is set to 0, the trim operation is keep going if clock is inaccuracy.
 * |        |          |When this bit is set to 1, the trim operation is stopped if clock is inaccuracy.
 * @var GCR_T::IRCTRIMIEN
 * Offset: 0x84  IRC Trim Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1]     |TRIM_FAIL_IEN|Trim Failure Interrupt Enable
 * |        |          |This bit controls if an interrupt will be triggered while HIRC trim value update limitation |count reached and HIRC frequency still not locked on target frequency set by TRIM_SEL (IRCTRIMCTL[1:0]).
 * |        |          |If this bit is high and TRIM_FAIL_INT (IRCTRIMINT[1]) is set during auto trim operation.
 * |        |          |An interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
 * |        |          |0 = TRIM_FAIL_INT (IRCTRIMINT[1]) status to trigger an interrupt to CPU Disabled.
 * |        |          |1 = TRIM_FAIL_INT (IRCTRIMINT[1]) status to trigger an interrupt to CPU Enabled.
 * |[2]     |CLKERR_IEN|Clock Error Interrupt Enable
 * |        |          |This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
 * |        |          |If this bit is set to1, and CLKERR_INT (IRCTRIMINT[2]) is set during auto trim operation.
 * |        |          |An interrupt will be triggered to notify the clock frequency is inaccuracy.
 * |        |          |0 = CLKERR_INT (IRCTRIMINT[2]) status to trigger an interrupt to CPU Disabled.
 * |        |          |1 = CLKERR_INT (IRCTRIMINT[2]) status to trigger an interrupt to CPU Enabled.
 * @var GCR_T::IRCTRIMINT
 * Offset: 0x88  IRC Trim Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |FREQ_LOCK |HIRC Frequency Lock Status
 * |        |          |This bit indicates the internal 22.1184 MHz high speed oscillator frequency is locked.
 * |        |          |This is a status bit and doesn't trigger any interrupt.
 * |[1]     |TRIM_FAIL_INT|Trim Failure Interrupt Status
 * |        |          |This bit indicates that internal 22.1184 MHz high speed oscillator trim value update limitation count reached and the internal 22.1184 MHz high speed oscillator clock frequency still doesn't be locked.
 * |        |          |Once this bit is set, the auto trim operation stopped and TRIM_SEL (IRCTRIMCTL [1:0]) will be cleared to 00 by hardware automatically.
 * |        |          |If this bit is set and TRIM_FAIL_IEN (IRCTRIMIEN[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
 * |        |          |Write 1 to clear this to 0.
 * |        |          |0 = Trim value update limitation count did not reach.
 * |        |          |1 = Trim value update limitation count reached and internal 22.1184 MHz high speed
 * |        |          |oscillator frequency was still not locked.
 * |[2]     |CLKERR_INT|Clock Error Interrupt Status
 * |        |          |When the frequency of external 32.768 kHz low speed crystal or internal 22.1184 MHz high speed oscillator is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy.
 * |        |          |Once this bit is set to 1, the auto trim operation stopped and TRIM_SEL (IRCTRIMCTL [1:0]) will be cleared to 00 by hardware automatically if CLKERR_STOP_EN (IRCTRIMCTL [8]) is set to 1.
 * |        |          |If this bit is set and CLKERR_IEN (IRCTRIMIEN [2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
 * |        |          |Write 1 to clear this to 0.
 * |        |          |0 = Clock frequency is accurate.
 * |        |          |1 = Clock frequency is inaccurate.
 * @var GCR_T::REGWRPROT
 * Offset: 0x100  Register Write Protection Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |REGPROTDIS|Register Write-Protection Disable Index (Read Only)
 * |        |          |0 = Write-protection is enabled for writing protected registers.
 * |        |          |Any write to the protected register is ignored.
 * |        |          |1 = Write-protection is disabled for writing protected registers.
 * |        |          |The Protected registers are:
 * |        |          |IPRSTC1: address 0x5000_0008
 * |        |          |BODCR: address 0x5000_0018
 * |        |          |PORCR: address 0x5000_0024
 * |        |          |PWRCON: address 0x5000_0200 (bit[6] is not protected for power wake-up interrupt clear)
 * |        |          |APBCLK bit[0]: address 0x5000_0208 (bit[0] is watchdog clock enable)
 * |        |          |CLKSEL0: address 0x5000_0210 (for HCLK and CPU STCLK clock source selection)
 * |        |          |CLKSEL1 bit[1:0]: address 0x5000_0214 (for watchdog clock source selection)
 * |        |          |NMI_SEL bit[8]: address 0x5000_0380 (for NMI_EN NMI interrupt enable)
 * |        |          |ISPCON: address 0x5000_C000 (Flash ISP Control register)
 * |        |          |ISPTRG: address 0x5000_C010 (ISP Trigger Control register)
 * |        |          |WTCR: address 0x4000_4000
 * |        |          |FATCON: address 0x5000_C018
 * |        |          |Note: The bits which are write-protected will be noted as" (Write Protect)" beside the
 * |        |          |description.
 * |[7:0]   |REGWRPROT |Register Write-Protection Code (Write Only)
 * |        |          |Some registers have write-protection function.
 * |        |          |Writing these registers have to disable the protected function by writing the sequence value "59h", "16h", "88h" to this field.
 * |        |          |After this sequence is completed, the REGPROTDIS bit will be set to 1 and write-protection registers can be normal write.
 */

    __I  uint32_t PDID;          /* Offset: 0x00  Part Device Identification Number Register                         */
    __IO uint32_t RSTSRC;        /* Offset: 0x04  System Reset Source Register                                       */
    __IO uint32_t IPRSTC1;       /* Offset: 0x08  IP Reset Control Register 1                                        */
    __IO uint32_t IPRSTC2;       /* Offset: 0x0C  IP Reset Control Register 2                                        */
    __IO uint32_t IPRSTC3;       /* Offset: 0x10  IP Reset Control Register 3                                        */
    __I  uint32_t RESERVE0;
    __IO uint32_t BODCR;         /* Offset: 0x18  Brown-out Detector Control Register                                */
    __IO uint32_t TEMPCR;        /* Offset: 0x1C  Temperature Sensor Control Register                                */
    __I  uint32_t RESERVE1;
    __IO uint32_t PORCR;         /* Offset: 0x24  Power-on-Reset Controller Register                                 */
    __I  uint32_t RESERVE2[2];
    __IO uint32_t GPA_MFP;       /* Offset: 0x30  GPIOA Multiple Function and Input Type Control Register            */
    __IO uint32_t GPB_MFP;       /* Offset: 0x34  GPIOB Multiple Function and Input Type Control Register            */
    __IO uint32_t GPC_MFP;       /* Offset: 0x38  GPIOC Multiple Function and Input Type Control Register            */
    __IO uint32_t GPD_MFP;       /* Offset: 0x3C  GPIOD Multiple Function and Input Type Control Register            */
    __IO uint32_t GPE_MFP;       /* Offset: 0x40  GPIOE Multiple Function and Input Type Control Register            */
    __IO uint32_t GPF_MFP;       /* Offset: 0x44  GPIOF Multiple Function and Input Type Control Register            */
    __I  uint32_t RESERVE3[2];
    __IO uint32_t ALT_MFP;       /* Offset: 0x50  Alternative Multiple Function Pin Control Register                 */
    __I  uint32_t RESERVE4;
    __IO uint32_t ALT_MFP1;      /* Offset: 0x58  Alternative Multiple Function Pin Control Register 1               */
    __IO uint32_t ALT_MFP2;      /* Offset: 0x5C  Alternative Multiple Function Pin Control Register 2               */
    __I  uint32_t RESERVE5[8];
    __IO uint32_t IRCTRIMCTL;    /* Offset: 0x80  IRC Trim Control Register                                          */
    __IO uint32_t IRCTRIMIEN;    /* Offset: 0x84  IRC Trim Interrupt Enable Register                                 */
    __IO uint32_t IRCTRIMINT;    /* Offset: 0x88  IRC Trim Interrupt Status Register                                 */
    __I  uint32_t RESERVE6[29];   
    __IO uint32_t REGWRPROT;     /* Offset: 0x100  Register Write Protection Register                                */

} GCR_T;




/**
    @addtogroup SYS_CONST SYS Bit Field Definition
    Constant Definitions for SYS Controller
@{ */

/* GCR RSTSRC Bit Field Definitions */
#define SYS_RSTSRC_RSTS_CPU_Pos                 7                                   /*!< GCR_T::RSTSRC: RSTS_CPU Position */
#define SYS_RSTSRC_RSTS_CPU_Msk                 (1ul << SYS_RSTSRC_RSTS_CPU_Pos)    /*!< GCR_T::RSTSRC: RSTS_CPU Mask */

#define SYS_RSTSRC_RSTS_SYS_Pos                 5                                   /*!< GCR_T::RSTSRC: RSTS_SYS Position */
#define SYS_RSTSRC_RSTS_SYS_Msk                 (1ul << SYS_RSTSRC_RSTS_SYS_Pos)    /*!< GCR_T::RSTSRC: RSTS_SYS Mask */

#define SYS_RSTSRC_RSTS_BOD_Pos                 4                                   /*!< GCR_T::RSTSRC: RSTS_BOD Position */
#define SYS_RSTSRC_RSTS_BOD_Msk                 (1ul << SYS_RSTSRC_RSTS_BOD_Pos)    /*!< GCR_T::RSTSRC: RSTS_BOD Mask */

#define SYS_RSTSRC_RSTS_LVR_Pos                 3                                   /*!< GCR_T::RSTSRC: RSTS_LVR Position */
#define SYS_RSTSRC_RSTS_LVR_Msk                 (1ul << SYS_RSTSRC_RSTS_LVR_Pos)    /*!< GCR_T::RSTSRC: RSTS_LVR Mask */

#define SYS_RSTSRC_RSTS_WDT_Pos                 2                                   /*!< GCR_T::RSTSRC: RSTS_WDT Position */
#define SYS_RSTSRC_RSTS_WDT_Msk                 (1ul << SYS_RSTSRC_RSTS_WDT_Pos)    /*!< GCR_T::RSTSRC: RSTS_WDT Mask */

#define SYS_RSTSRC_RSTS_RESET_Pos               1                                   /*!< GCR_T::RSTSRC: RSTS_RESET Position */
#define SYS_RSTSRC_RSTS_RESET_Msk               (1ul << SYS_RSTSRC_RSTS_RESET_Pos)  /*!< GCR_T::RSTSRC: RSTS_RESET Mask */

#define SYS_RSTSRC_RSTS_POR_Pos                 0                                   /*!< GCR_T::RSTSRC: RSTS_POR Position */
#define SYS_RSTSRC_RSTS_POR_Msk                 (1ul << SYS_RSTSRC_RSTS_POR_Pos)    /*!< GCR_T::RSTSRC: RSTS_POR Mask */

/* GCR IPRSTC1 Bit Field Definitions */
#define SYS_IPRSTC1_EBI_RST_Pos                 3                                   /*!< GCR_T::IPRSTC1: EBI_RST Position */
#define SYS_IPRSTC1_EBI_RST_Msk                 (1ul << SYS_IPRSTC1_EBI_RST_Pos)    /*!< GCR_T::IPRSTC1: EBI_RST Mask */

#define SYS_IPRSTC1_PDMA_RST_Pos                2                                   /*!< GCR_T::IPRSTC1: PDMA_RST Position */
#define SYS_IPRSTC1_PDMA_RST_Msk                (1ul << SYS_IPRSTC1_PDMA_RST_Pos)   /*!< GCR_T::IPRSTC1: PDMA_RST Mask */

#define SYS_IPRSTC1_CPU_RST_Pos                 1                                   /*!< GCR_T::IPRSTC1: CPU_RST Position */
#define SYS_IPRSTC1_CPU_RST_Msk                 (1ul << SYS_IPRSTC1_CPU_RST_Pos)    /*!< GCR_T::IPRSTC1: CPU_RST Mask */

#define SYS_IPRSTC1_CHIP_RST_Pos                0                                   /*!< GCR_T::IPRSTC1: CHIP_RST Position */
#define SYS_IPRSTC1_CHIP_RST_Msk                (1ul << SYS_IPRSTC1_CHIP_RST_Pos)   /*!< GCR_T::IPRSTC1: CHIP_RST Mask */

/* GCR IPRSTC2 Bit Field Definitions */
#define SYS_IPRSTC2_I2S_RST_Pos                 29                                  /*!< GCR_T::IPRSTC2: I2S_RST Position */
#define SYS_IPRSTC2_I2S_RST_Msk                 (1ul << SYS_IPRSTC2_I2S_RST_Pos)    /*!< GCR_T::IPRSTC2: I2S_RST Mask */

#define SYS_IPRSTC2_ADC_RST_Pos                 28                                  /*!< GCR_T::IPRSTC2: ADC_RST Position */
#define SYS_IPRSTC2_ADC_RST_Msk                 (1ul << SYS_IPRSTC2_ADC_RST_Pos)    /*!< GCR_T::IPRSTC2: ADC_RST Mask */

#define SYS_IPRSTC2_USBD_RST_Pos                27                                  /*!< GCR_T::IPRSTC2: USBD_RST Position */
#define SYS_IPRSTC2_USBD_RST_Msk                (1ul << SYS_IPRSTC2_USBD_RST_Pos)   /*!< GCR_T::IPRSTC2: USBD_RST Mask */

#define SYS_IPRSTC2_PS2_RST_Pos                 23                                  /*!< GCR_T::IPRSTC2: PS2_RST Position */
#define SYS_IPRSTC2_PS2_RST_Msk                 (1ul << SYS_IPRSTC2_PS2_RST_Pos)    /*!< GCR_T::IPRSTC2: PS2_RST Mask */

#define SYS_IPRSTC2_ACMP_RST_Pos                22                                  /*!< GCR_T::IPRSTC2: ACMP_RST Position */
#define SYS_IPRSTC2_ACMP_RST_Msk                (1ul << SYS_IPRSTC2_ACMP_RST_Pos)   /*!< GCR_T::IPRSTC2: ACMP_RST Mask */

#define SYS_IPRSTC2_PWM47_RST_Pos               21                                  /*!< GCR_T::IPRSTC2: PWM47_RST Position */
#define SYS_IPRSTC2_PWM47_RST_Msk               (1ul << SYS_IPRSTC2_PWM47_RST_Pos)  /*!< GCR_T::IPRSTC2: PWM47_RST Mask */

#define SYS_IPRSTC2_PWM03_RST_Pos               20                                  /*!< GCR_T::IPRSTC2: PWM03_RST Position */
#define SYS_IPRSTC2_PWM03_RST_Msk               (1ul << SYS_IPRSTC2_PWM03_RST_Pos)  /*!< GCR_T::IPRSTC2: PWM03_RST Mask */

#define SYS_IPRSTC2_UART2_RST_Pos               18                                  /*!< GCR_T::IPRSTC2: UART2_RST Position */
#define SYS_IPRSTC2_UART2_RST_Msk               (1ul << SYS_IPRSTC2_UART2_RST_Pos)  /*!< GCR_T::IPRSTC2: UART2_RST Mask */

#define SYS_IPRSTC2_UART1_RST_Pos               17                                  /*!< GCR_T::IPRSTC2: UART1_RST Position */
#define SYS_IPRSTC2_UART1_RST_Msk               (1ul << SYS_IPRSTC2_UART1_RST_Pos)  /*!< GCR_T::IPRSTC2: UART1_RST Mask */

#define SYS_IPRSTC2_UART0_RST_Pos               16                                  /*!< GCR_T::IPRSTC2: UART0_RST Position */
#define SYS_IPRSTC2_UART0_RST_Msk               (1ul << SYS_IPRSTC2_UART0_RST_Pos)  /*!< GCR_T::IPRSTC2: UART0_RST Mask */

#define SYS_IPRSTC2_SPI3_RST_Pos                15                                  /*!< GCR_T::IPRSTC2: SPI3_RST Position */
#define SYS_IPRSTC2_SPI3_RST_Msk                (1ul << SYS_IPRSTC2_SPI3_RST_Pos)   /*!< GCR_T::IPRSTC2: SPI3_RST Mask */

#define SYS_IPRSTC2_SPI2_RST_Pos                14                                  /*!< GCR_T::IPRSTC2: SPI2_RST Position */
#define SYS_IPRSTC2_SPI2_RST_Msk                (1ul << SYS_IPRSTC2_SPI2_RST_Pos)   /*!< GCR_T::IPRSTC2: SPI2_RST Mask */

#define SYS_IPRSTC2_SPI1_RST_Pos                13                                  /*!< GCR_T::IPRSTC2: SPI1_RST Position */
#define SYS_IPRSTC2_SPI1_RST_Msk                (1ul << SYS_IPRSTC2_SPI1_RST_Pos)   /*!< GCR_T::IPRSTC2: SPI1_RST Mask */

#define SYS_IPRSTC2_SPI0_RST_Pos                12                                  /*!< GCR_T::IPRSTC2: SPI0_RST Position */
#define SYS_IPRSTC2_SPI0_RST_Msk                (1ul << SYS_IPRSTC2_SPI0_RST_Pos)   /*!< GCR_T::IPRSTC2: SPI0_RST Mask */

#define SYS_IPRSTC2_I2C1_RST_Pos                9                                   /*!< GCR_T::IPRSTC2: I2C1_RST Position */
#define SYS_IPRSTC2_I2C1_RST_Msk                (1ul << SYS_IPRSTC2_I2C1_RST_Pos)   /*!< GCR_T::IPRSTC2: I2C1_RST Mask */

#define SYS_IPRSTC2_I2C0_RST_Pos                8                                   /*!< GCR_T::IPRSTC2: I2C0_RST Position */
#define SYS_IPRSTC2_I2C0_RST_Msk                (1ul << SYS_IPRSTC2_I2C0_RST_Pos)   /*!< GCR_T::IPRSTC2: I2C0_RST Mask */

#define SYS_IPRSTC2_TMR3_RST_Pos                5                                   /*!< GCR_T::IPRSTC2: TMR3_RST Position */
#define SYS_IPRSTC2_TMR3_RST_Msk                (1ul << SYS_IPRSTC2_TMR3_RST_Pos)   /*!< GCR_T::IPRSTC2: TMR3_RST Mask */

#define SYS_IPRSTC2_TMR2_RST_Pos                4                                   /*!< GCR_T::IPRSTC2: TMR2_RST Position */
#define SYS_IPRSTC2_TMR2_RST_Msk                (1ul << SYS_IPRSTC2_TMR2_RST_Pos)   /*!< GCR_T::IPRSTC2: TMR2_RST Mask */

#define SYS_IPRSTC2_TMR1_RST_Pos                3                                   /*!< GCR_T::IPRSTC2: TMR1_RST Position */
#define SYS_IPRSTC2_TMR1_RST_Msk                (1ul << SYS_IPRSTC2_TMR1_RST_Pos)   /*!< GCR_T::IPRSTC2: TMR1_RST Mask */

#define SYS_IPRSTC2_TMR0_RST_Pos                2                                   /*!< GCR_T::IPRSTC2: TMR0_RST Position */
#define SYS_IPRSTC2_TMR0_RST_Msk                (1ul << SYS_IPRSTC2_TMR0_RST_Pos)   /*!< GCR_T::IPRSTC2: TMR0_RST Mask */

#define SYS_IPRSTC2_GPIO_RST_Pos                1                                   /*!< GCR_T::IPRSTC2: GPIO_RST Position */
#define SYS_IPRSTC2_GPIO_RST_Msk                (1ul << SYS_IPRSTC2_GPIO_RST_Pos)   /*!< GCR_T::IPRSTC2: GPIO_RST Mask */

/* GCR IPRSTC3 Bit Field Definitions */
#define SYS_IPRSTC3_SC2_RST_Pos                 2                                   /*!< GCR_T::IPRSTC3: SC2_RST Position */
#define SYS_IPRSTC3_SC2_RST_Msk                 (1ul << SYS_IPRSTC3_SC2_RST_Pos)    /*!< GCR_T::IPRSTC3: SC2_RST Mask */

#define SYS_IPRSTC3_SC1_RST_Pos                 1                                   /*!< GCR_T::IPRSTC3: SC1_RST Position */
#define SYS_IPRSTC3_SC1_RST_Msk                 (1ul << SYS_IPRSTC3_SC1_RST_Pos)    /*!< GCR_T::IPRSTC3: SC1_RST Mask */

#define SYS_IPRSTC3_SC0_RST_Pos                 0                                   /*!< GCR_T::IPRSTC3: SC0_RST Position */
#define SYS_IPRSTC3_SC0_RST_Msk                 (1ul << SYS_IPRSTC3_SC0_RST_Pos)    /*!< GCR_T::IPRSTC3: SC0_RST Mask */

/* GCR BODCR Bit Field Definitions */
#define SYS_BODCR_LVR_EN_Pos                    7                                   /*!< GCR_T::BODCR: LVR_EN Position */
#define SYS_BODCR_LVR_EN_Msk                    (1ul << SYS_BODCR_LVR_EN_Pos)       /*!< GCR_T::BODCR: LVR_EN Mask */

#define SYS_BODCR_BOD_OUT_Pos                   6                                   /*!< GCR_T::BODCR: BOD_OUT Position */
#define SYS_BODCR_BOD_OUT_Msk                   (1ul << SYS_BODCR_BOD_OUT_Pos)      /*!< GCR_T::BODCR: BOD_OUT Mask */

#define SYS_BODCR_BOD_LPM_Pos                   5                                   /*!< GCR_T::BODCR: BOD_LPM Position */
#define SYS_BODCR_BOD_LPM_Msk                   (1ul << SYS_BODCR_BOD_LPM_Pos)      /*!< GCR_T::BODCR: BOD_LPM Mask */

#define SYS_BODCR_BOD_INTF_Pos                  4                                   /*!< GCR_T::BODCR: BOD_INTF Position */
#define SYS_BODCR_BOD_INTF_Msk                  (1ul << SYS_BODCR_BOD_INTF_Pos)     /*!< GCR_T::BODCR: BOD_INTF Mask */

#define SYS_BODCR_BOD_RSTEN_Pos                 3                                   /*!< GCR_T::BODCR: BOD_RSTEN Position */
#define SYS_BODCR_BOD_RSTEN_Msk                 (1ul << SYS_BODCR_BOD_RSTEN_Pos)    /*!< GCR_T::BODCR: BOD_RSTEN Mask */

#define SYS_BODCR_BOD_VL_Pos                    1                                   /*!< GCR_T::BODCR: BOD_VL Position */
#define SYS_BODCR_BOD_VL_Msk                    (3ul << SYS_BODCR_BOD_VL_Pos)       /*!< GCR_T::BODCR: BOD_VL Mask */

#define SYS_BODCR_BOD_EN_Pos                    0                                   /*!< GCR_T::BODCR: BOD_EN Position */
#define SYS_BODCR_BOD_EN_Msk                    (1ul << SYS_BODCR_BOD_EN_Pos)       /*!< GCR_T::BODCR: BOD_EN Mask */

/* GCR TEMPCR Bit Field Definitions */
#define SYS_TEMPCR_VTEMP_EN_Pos                 0                                   /*!< GCR_T::TEMPCR: VTEMP_EN Position */
#define SYS_TEMPCR_VTEMP_EN_Msk                 (1ul << SYS_TEMPCR_VTEMP_EN_Pos)    /*!< GCR_T::TEMPCR: VTEMP_EN Mask */

/* GCR PORCR Bit Field Definitions */
#define SYS_PORCR_POR_DIS_CODE_Pos              0                                           /*!< GCR_T::PORCR: POR_DIS_CODE Position */
#define SYS_PORCR_POR_DIS_CODE_Msk              (0xFFFFul << SYS_PORCR_POR_DIS_CODE_Pos)    /*!< GCR_T::PORCR: POR_DIS_CODE Mask */

/* GCR GPAMFP Bit Field Definitions */
#define SYS_GPA_MFP_GPA_TYPE_Pos                 16                                         /*!< GCR_T::GPA_MFP: GPA_TYPE Position */
#define SYS_GPA_MFP_GPA_TYPE_Msk                 (0xFFFFul << SYS_GPA_MFP_GPA_TYPE_Pos)     /*!< GCR_T::GPA_MFP: GPA_TYPE Mask */

#define SYS_GPA_MFP_GPA_MFP_Pos                  0                                          /*!< GCR_T::GPA_MFP: GPA_MFP Position */
#define SYS_GPA_MFP_GPA_MFP_Msk                  (0xFFFFul << SYS_GPA_MFP_GPA_MFP_Pos)      /*!< GCR_T::GPA_MFP: GPA_MFP Mask */


/* GCR GPBMFP Bit Field Definitions */
#define SYS_GPB_MFP_GPB_TYPE_Pos                 16                                         /*!< GCR_T::GPB_MFP: GPB_TYPE Position */
#define SYS_GPB_MFP_GPB_TYPE_Msk                 (0xFFFFul << SYS_GPB_MFP_GPB_TYPE_Pos)     /*!< GCR_T::GPB_MFP: GPB_TYPE Mask */

#define SYS_GPB_MFP_GPB_MFP_Pos                  0                                          /*!< GCR_T::GPB_MFP: GPB_MFP Position */
#define SYS_GPB_MFP_GPB_MFP_Msk                  (0xFFFFul << SYS_GPB_MFP_GPB_MFP_Pos)      /*!< GCR_T::GPB_MFP: GPB_MFP Mask */

/* GCR GPCMFP Bit Field Definitions */
#define SYS_GPC_MFP_GPC_TYPE_Pos                 16                                         /*!< GCR_T::GPC_MFP: GPC_TYPE Position */
#define SYS_GPC_MFP_GPC_TYPE_Msk                 (0xFFFFul << SYS_GPC_MFP_GPC_TYPE_Pos)     /*!< GCR_T::GPC_MFP: GPC_TYPE Mask */

#define SYS_GPC_MFP_GPC_MFP_Pos                  0                                          /*!< GCR_T::GPC_MFP: GPC_MFP Position */
#define SYS_GPC_MFP_GPC_MFP_Msk                  (0xFFFFul << SYS_GPC_MFP_GPC_MFP_Pos)      /*!< GCR_T::GPC_MFP: GPC_MFP Mask */

/* GCR GPDMFP Bit Field Definitions */
#define SYS_GPD_MFP_GPD_TYPE_Pos                 16                                         /*!< GCR_T::GPD_MFP: GPD_TYPE Position */
#define SYS_GPD_MFP_GPD_TYPE_Msk                 (0xFFFFul << SYS_GPD_MFP_GPD_TYPE_Pos)     /*!< GCR_T::GPD_MFP: GPD_TYPE Mask */

#define SYS_GPD_MFP_GPD_MFP_Pos                  0                                          /*!< GCR_T::GPD_MFP: GPD_MFP Position */
#define SYS_GPD_MFP_GPD_MFP_Msk                  (0xFFFFul << SYS_GPD_MFP_GPD_MFP_Pos)      /*!< GCR_T::GPD_MFP: GPD_MFP Mask */

/* GCR GPEMFP Bit Field Definitions */
#define SYS_GPE_MFP_GPE_TYPE_Pos                 16                                         /*!< GCR_T::GPE_MFP: GPE_TYPE Position */
#define SYS_GPE_MFP_GPE_TYPE_Msk                 (0xFFFFul << SYS_GPE_MFP_GPE_TYPE_Pos)     /*!< GCR_T::GPE_MFP: GPE_TYPE Mask */

#define SYS_GPE_MFP_GPE_MFP5_Pos                 5                                          /*!< GCR_T::GPE_MFP: GPE_MFP5 Position */
#define SYS_GPE_MFP_GPE_MFP5_Msk                 (1ul << SYS_GPE_MFP_GPE_MFP5_Pos)          /*!< GCR_T::GPE_MFP: GPE_MFP5 Mask */

#define SYS_GPE_MFP_GPE_MFP1_Pos                 1                                          /*!< GCR_T::GPE_MFP: GPE_MFP1 Position */
#define SYS_GPE_MFP_GPE_MFP1_Msk                 (1ul << SYS_GPE_MFP_GPE_MFP1_Pos)          /*!< GCR_T::GPE_MFP: GPE_MFP1 Mask */

#define SYS_GPE_MFP_GPE_MFP0_Pos                 0                                          /*!< GCR_T::GPE_MFP: GPE_MFP0 Position */
#define SYS_GPE_MFP_GPE_MFP0_Msk                 (1ul << SYS_GPE_MFP_GPE_MFP0_Pos)          /*!< GCR_T::GPE_MFP: GPE_MFP0 Mask */

/* GCR GPFMFP Bit Field Definitions */
#define SYS_GPF_MFP_GPF_TYPE_Pos                 16                                         /*!< GCR_T::GPF_MFP: GPF_TYPE Position */
#define SYS_GPF_MFP_GPF_TYPE_Msk                 (0xFul << SYS_GPF_MFP_GPF_TYPE_Pos)        /*!< GCR_T::GPF_MFP: GPF_TYPE Mask */

#define SYS_GPF_MFP_GPF_MFP3_Pos                 3                                          /*!< GCR_T::GPF_MFP: GPF_MFP3 Position */
#define SYS_GPF_MFP_GPF_MFP3_Msk                 (1ul << SYS_GPF_MFP_GPF_MFP3_Pos)          /*!< GCR_T::GPF_MFP: GPF_MFP3 Mask */

#define SYS_GPF_MFP_GPF_MFP2_Pos                 2                                          /*!< GCR_T::GPF_MFP: GPF_MFP2 Position */
#define SYS_GPF_MFP_GPF_MFP2_Msk                 (1ul << SYS_GPF_MFP_GPF_MFP2_Pos)          /*!< GCR_T::GPF_MFP: GPF_MFP2 Mask */

#define SYS_GPF_MFP_GPF_MFP1_Pos                 1                                          /*!< GCR_T::GPF_MFP: GPF_MFP1 Position */
#define SYS_GPF_MFP_GPF_MFP1_Msk                 (1ul << SYS_GPF_MFP_GPF_MFP1_Pos)          /*!< GCR_T::GPF_MFP: GPF_MFP1 Mask */

#define SYS_GPF_MFP_GPF_MFP0_Pos                 0                                          /*!< GCR_T::GPF_MFP: GPF_MFP0 Position */
#define SYS_GPF_MFP_GPF_MFP0_Msk                 (1ul << SYS_GPF_MFP_GPF_MFP0_Pos)          /*!< GCR_T::GPF_MFP: GPF_MFP0 Mask */

/* GCR ALTMFP Bit Field Definitions */
#define SYS_ALT_MFP_PB3_T3EX_Pos                 27                                         /*!< GCR_T::ALT_MFP: PB3_T3EX Position */
#define SYS_ALT_MFP_PB3_T3EX_Msk                 (1ul << SYS_ALT_MFP_PB3_T3EX_Pos)          /*!< GCR_T::ALT_MFP: PB3_T3EX Mask */

#define SYS_ALT_MFP_PB2_T2EX_Pos                 26                                         /*!< GCR_T::ALT_MFP: PB2_T2EX Position */
#define SYS_ALT_MFP_PB2_T2EX_Msk                 (1ul << SYS_ALT_MFP_PB2_T2EX_Pos)          /*!< GCR_T::ALT_MFP: PB3_T3EX Mask */

#define SYS_ALT_MFP_PE5_T1EX_Pos                 25                                         /*!< GCR_T::ALT_MFP: PE5_T1EX Position */
#define SYS_ALT_MFP_PE5_T1EX_Msk                 (1ul << SYS_ALT_MFP_PE5_T1EX_Pos)          /*!< GCR_T::ALT_MFP: PE5_T1EX Mask */

#define SYS_ALT_MFP_PB15_T0EX_Pos                24                                         /*!< GCR_T::ALT_MFP: PB15_T0EX Position */
#define SYS_ALT_MFP_PB15_T0EX_Msk                (1ul << SYS_ALT_MFP_PB15_T0EX_Pos)         /*!< GCR_T::ALT_MFP: PB15_T0EX Mask */

#define SYS_ALT_MFP_EBI_HB_EN_Pos                16                                         /*!< GCR_T::ALT_MFP: EBI_HB_EN Position */
#define SYS_ALT_MFP_EBI_HB_EN_Msk                (0xFFul << SYS_ALT_MFP_EBI_HB_EN_Pos)      /*!< GCR_T::ALT_MFP: EBI_HB_EN Mask */

#define SYS_ALT_MFP_EBI_nWRH_EN_Pos              14                                         /*!< GCR_T::ALT_MFP: EBI_nWRH_EN Position */
#define SYS_ALT_MFP_EBI_nWRH_EN_Msk              (1ul << SYS_ALT_MFP_EBI_nWRH_EN_Pos)       /*!< GCR_T::ALT_MFP: EBI_nWRH_EN Mask */

#define SYS_ALT_MFP_EBI_nWRL_EN_Pos              13                                         /*!< GCR_T::ALT_MFP: EBI_nWRL_EN Position */
#define SYS_ALT_MFP_EBI_nWRL_EN_Msk              (1ul << SYS_ALT_MFP_EBI_nWRL_EN_Pos)       /*!< GCR_T::ALT_MFP: EBI_nWRL_EN Mask */

#define SYS_ALT_MFP_EBI_MCLK_EN_Pos              12                                         /*!< GCR_T::ALT_MFP: EBI_MCLK_EN Position */
#define SYS_ALT_MFP_EBI_MCLK_EN_Msk              (1ul << SYS_ALT_MFP_EBI_MCLK_EN_Pos)       /*!< GCR_T::ALT_MFP: EBI_MCLK_EN Mask */

#define SYS_ALT_MFP_EBI_EN_Pos                   11                                         /*!< GCR_T::ALT_MFP: EBI_EN Position */
#define SYS_ALT_MFP_EBI_EN_Msk                   (1ul << SYS_ALT_MFP_EBI_EN_Pos)            /*!< GCR_T::ALT_MFP: EBI_EN Mask */

#define SYS_ALT_MFP_PB12_CLKO_Pos                10                                         /*!< GCR_T::ALT_MFP: PB12_CLKO Position */
#define SYS_ALT_MFP_PB12_CLKO_Msk                (1ul << SYS_ALT_MFP_PB12_CLKO_Pos)         /*!< GCR_T::ALT_MFP: PB12_CLKO Mask */

#define SYS_ALT_MFP_PA15_I2SMCLK_Pos             9                                          /*!< GCR_T::ALT_MFP: PA15_I2SMCLK Position */
#define SYS_ALT_MFP_PA15_I2SMCLK_Msk             (1ul << SYS_ALT_MFP_PA15_I2SMCLK_Pos)      /*!< GCR_T::ALT_MFP: PA15_I2SMCLK Mask */

#define SYS_ALT_MFP_PC3_I2SDO_Pos                8                                          /*!< GCR_T::ALT_MFP: PC3_I2SDO Position */
#define SYS_ALT_MFP_PC3_I2SDO_Msk                (1ul << SYS_ALT_MFP_PC3_I2SDO_Pos)         /*!< GCR_T::ALT_MFP: PC3_I2SDO Mask */

#define SYS_ALT_MFP_PC2_I2SDI_Pos                7                                          /*!< GCR_T::ALT_MFP: PC2_I2SDI Position */
#define SYS_ALT_MFP_PC2_I2SDI_Msk                (1ul << SYS_ALT_MFP_PC2_I2SDI_Pos)         /*!< GCR_T::ALT_MFP: PC2_I2SDI Mask */

#define SYS_ALT_MFP_PC1_I2SBCLK_Pos              6                                          /*!< GCR_T::ALT_MFP: PC1_I2SBCLK Position */
#define SYS_ALT_MFP_PC1_I2SBCLK_Msk              (1ul << SYS_ALT_MFP_PC1_I2SBCLK_Pos)       /*!< GCR_T::ALT_MFP: PC1_I2SBCLK Mask */

#define SYS_ALT_MFP_PC0_I2SLRCLK_Pos             5                                          /*!< GCR_T::ALT_MFP: PC0_I2SLRCLK Position */
#define SYS_ALT_MFP_PC0_I2SLRCLK_Msk             (1ul << SYS_ALT_MFP_PC0_I2SLRCLK_Pos)      /*!< GCR_T::ALT_MFP: PC0_I2SLRCLK Mask */

#define SYS_ALT_MFP_PB11_PWM4_Pos                4                                          /*!< GCR_T::ALT_MFP: PB11_PWM4 Position */
#define SYS_ALT_MFP_PB11_PWM4_Msk                (1ul << SYS_ALT_MFP_PB11_PWM4_Pos)         /*!< GCR_T::ALT_MFP: PB11_PWM4 Mask */

#define SYS_ALT_MFP_PB14_S31_Pos                 3                                          /*!< GCR_T::ALT_MFP: PB14_S31 Position */
#define SYS_ALT_MFP_PB14_S31_Msk                 (1ul << SYS_ALT_MFP_PB14_S31_Pos)          /*!< GCR_T::ALT_MFP: PB14_S31 Mask */

#define SYS_ALT_MFP_PA7_S21_Pos                  2                                          /*!< GCR_T::ALT_MFP: PA7_S21 Position */
#define SYS_ALT_MFP_PA7_S21_Msk                  (1ul << SYS_ALT_MFP_PA7_S21_Pos)           /*!< GCR_T::ALT_MFP: PA7_S21 Mask */

#define SYS_ALT_MFP_PB9_S11_Pos                  1                                          /*!< GCR_T::ALT_MFP: PB9_S11 Position */
#define SYS_ALT_MFP_PB9_S11_Msk                  (1ul << SYS_ALT_MFP_PB9_S11_Pos)           /*!< GCR_T::ALT_MFP: PB9_S11 Mask */

#define SYS_ALT_MFP_PB10_S01_Pos                 0                                          /*!< GCR_T::ALT_MFP: PB10_S01 Position */
#define SYS_ALT_MFP_PB10_S01_Msk                 (1ul << SYS_ALT_MFP_PB10_S01_Pos)          /*!< GCR_T::ALT_MFP: PB10_S01 Mask */

/* GCR ALTMFP1 Bit Field Definitions */
#define SYS_ALT_MFP1_PB3_SC2CD_Pos              14                                          /*!< GCR_T::ALT_MFP1: PB3_SC2CD Position */
#define SYS_ALT_MFP1_PB3_SC2CD_Msk              (1ul << SYS_ALT_MFP1_PB3_SC2CD_Pos)         /*!< GCR_T::ALT_MFP1: PB3_SC2CD Mask */

#define SYS_ALT_MFP1_PA14_SC2RST_Pos            13                                          /*!< GCR_T::ALT_MFP1: PA14_SC2RST Position */
#define SYS_ALT_MFP1_PA14_SC2RST_Msk            (1ul << SYS_ALT_MFP1_PA14_SC2RST_Pos)       /*!< GCR_T::ALT_MFP1: PA14_SC2RST Mask */

#define SYS_ALT_MFP1_PA15_SC2PWR_Pos            12                                          /*!< GCR_T::ALT_MFP1: PA15_SC2PWR Position */
#define SYS_ALT_MFP1_PA15_SC2PWR_Msk            (1ul << SYS_ALT_MFP1_PA15_SC2PWR_Pos)       /*!< GCR_T::ALT_MFP1: PA15_SC2PWR Mask */

#define SYS_ALT_MFP1_PA12_SC2DAT_Pos            11                                          /*!< GCR_T::ALT_MFP1: PA12_SC2DAT Position */
#define SYS_ALT_MFP1_PA12_SC2DAT_Msk            (1ul << SYS_ALT_MFP1_PA12_SC2DAT_Pos)       /*!< GCR_T::ALT_MFP1: PA12_SC2DAT Mask */

#define SYS_ALT_MFP1_PA13_SC2CLK_Pos            10                                          /*!< GCR_T::ALT_MFP1: PA13_SC2CLK Position */
#define SYS_ALT_MFP1_PA13_SC2CLK_Msk            (1ul << SYS_ALT_MFP1_PA13_SC2CLK_Pos)       /*!< GCR_T::ALT_MFP1: PA13_SC2CLK Mask */

#define SYS_ALT_MFP1_PC7_SC1CD_Pos              9                                           /*!< GCR_T::ALT_MFP1: PC7_SC1CD Position */
#define SYS_ALT_MFP1_PC7_SC1CD_Msk              (1ul << SYS_ALT_MFP1_PC7_SC1CD_Pos)         /*!< GCR_T::ALT_MFP1: PC7_SC1CD Mask */

#define SYS_ALT_MFP1_PA5_SC1RST_Pos             8                                           /*!< GCR_T::ALT_MFP1: PA5_SC1RST Position */
#define SYS_ALT_MFP1_PA5_SC1RST_Msk             (1ul << SYS_ALT_MFP1_PA5_SC1RST_Pos)        /*!< GCR_T::ALT_MFP1: PA5_SC1RST Mask */

#define SYS_ALT_MFP1_PA4_SC1PWR_Pos             7                                           /*!< GCR_T::ALT_MFP1: PA4_SC1PWR Position */
#define SYS_ALT_MFP1_PA4_SC1PWR_Msk             (1ul << SYS_ALT_MFP1_PA4_SC1PWR_Pos)        /*!< GCR_T::ALT_MFP1: PA4_SC1PWR Mask */

#define SYS_ALT_MFP1_PA7_SC1DAT_Pos             6                                           /*!< GCR_T::ALT_MFP1: PA7_SC1DAT Position */
#define SYS_ALT_MFP1_PA7_SC1DAT_Msk             (1ul << SYS_ALT_MFP1_PA7_SC1DAT_Pos)        /*!< GCR_T::ALT_MFP1: PA7_SC1DAT Mask */

#define SYS_ALT_MFP1_PA6_SC1CLK_Pos             5                                           /*!< GCR_T::ALT_MFP1: PA6_SC1CLK Position */
#define SYS_ALT_MFP1_PA6_SC1CLK_Msk             (1ul << SYS_ALT_MFP1_PA6_SC1CLK_Pos)        /*!< GCR_T::ALT_MFP1: PA6_SC1CLK Mask */

#define SYS_ALT_MFP1_PC6_SC0CD_Pos              4                                           /*!< GCR_T::ALT_MFP1: PC6_SC0CD Position */
#define SYS_ALT_MFP1_PC6_SC0CD_Msk              (1ul << SYS_ALT_MFP1_PC6_SC0CD_Pos)         /*!< GCR_T::ALT_MFP1: PC6_SC0CD Mask */

#define SYS_ALT_MFP1_PA1_SC0RST_Pos             3                                           /*!< GCR_T::ALT_MFP1: PA1_SC0RST Position */
#define SYS_ALT_MFP1_PA1_SC0RST_Msk             (1ul << SYS_ALT_MFP1_PA1_SC0RST_Pos)        /*!< GCR_T::ALT_MFP1: PA1_SC0RST Mask */

#define SYS_ALT_MFP1_PA0_SC0PWR_Pos             2                                           /*!< GCR_T::ALT_MFP1: PA0_SC0PWR Position */
#define SYS_ALT_MFP1_PA0_SC0PWR_Msk             (1ul << SYS_ALT_MFP1_PA0_SC0PWR_Pos)        /*!< GCR_T::ALT_MFP1: PA0_SC0PWR Mask */

#define SYS_ALT_MFP1_PA3_SC0DAT_Pos             1                                           /*!< GCR_T::ALT_MFP1: PA3_SC0DAT Position */
#define SYS_ALT_MFP1_PA3_SC0DAT_Msk             (1ul << SYS_ALT_MFP1_PA3_SC0DAT_Pos)        /*!< GCR_T::ALT_MFP1: PA3_SC0DAT Mask */

#define SYS_ALT_MFP1_PA2_SC0CLK_Pos             0                                           /*!< GCR_T::ALT_MFP1: PA2_SC0CLK Position */
#define SYS_ALT_MFP1_PA2_SC0CLK_Msk             (1ul << SYS_ALT_MFP1_PA2_SC0CLK_Pos)        /*!< GCR_T::ALT_MFP1: PA2_SC0CLK Mask */

/* GCR IRCTRIMCTL Bit Field Definitions */
#define SYS_IRCTRIMCTL_CLKERR_STOP_EN_Pos       8                                           /*!< GCR_T::IRCTRIMCTL: CLKERR_STOP_EN Position */
#define SYS_IRCTRIMCTL_CLKERR_STOP_EN_Msk       (1ul << SYS_IRCTRIMCTL_CLKERR_STOP_EN_Pos)  /*!< GCR_T::IRCTRIMCTL: CLKERR_STOP_EN Mask */

#define SYS_IRCTRIMCTL_TRIM_RETRY_CNT_Pos       6                                           /*!< GCR_T::IRCTRIMCTL: TRIM_RETRY_CNT Position */
#define SYS_IRCTRIMCTL_TRIM_RETRY_CNT_Msk       (3ul << SYS_IRCTRIMCTL_TRIM_RETRY_CNT_Pos)  /*!< GCR_T::IRCTRIMCTL: TRIM_RETRY_CNT Mask */

#define SYS_IRCTRIMCTL_TRIM_LOOP_Pos            4                                           /*!< GCR_T::IRCTRIMCTL: TRIM_LOOP Position */
#define SYS_IRCTRIMCTL_TRIM_LOOP_Msk            (3ul << SYS_IRCTRIMCTL_TRIM_LOOP_Pos)       /*!< GCR_T::IRCTRIMCTL: TRIM_LOOP Mask */

#define SYS_IRCTRIMCTL_TRIM_SEL_Pos             0                                           /*!< GCR_T::IRCTRIMCTL: TRIM_SEL Position */
#define SYS_IRCTRIMCTL_TRIM_SEL_Msk             (3ul << SYS_IRCTRIMCTL_TRIM_SEL_Pos)        /*!< GCR_T::IRCTRIMCTL: TRIM_SEL Mask */

/* GCR IRCTRIMIEN Bit Field Definitions */
#define SYS_IRCTRIMIEN_CLKERR_IEN_Pos           2                                           /*!< GCR_T::IRCTRIMIEN: CLKERR_IEN Position */
#define SYS_IRCTRIMIEN_CLKERR_IEN_Msk           (1ul << SYS_IRCTRIMIEN_CLKERR_IEN_Pos)      /*!< GCR_T::IRCTRIMIEN: CLKERR_IEN Mask */

#define SYS_IRCTRIMIEN_TRIM_FAIL_IEN_Pos        1                                           /*!< GCR_T::IRCTRIMIEN: TRIM_FAIL_IEN Position */
#define SYS_IRCTRIMIEN_TRIM_FAIL_IEN_Msk        (1ul << SYS_IRCTRIMIEN_TRIM_FAIL_IEN_Pos)   /*!< GCR_T::IRCTRIMIEN: TRIM_FAIL_IEN Mask */

/* GCR IRCTRIMINT Bit Field Definitions */
#define SYS_IRCTRIMINT_CLKERR_INT_Pos           2                                           /*!< GCR_T::IRCTRIMINT: CLKERR_INT Position */
#define SYS_IRCTRIMINT_CLKERR_INT_Msk           (1ul << SYS_IRCTRIMINT_CLKERR_INT_Pos)      /*!< GCR_T::IRCTRIMINT: CLKERR_INT Mask */

#define SYS_IRCTRIMINT_TRIM_FAIL_INT_Pos        1                                           /*!< GCR_T::IRCTRIMINT: TRIM_FAIL_INT Position */
#define SYS_IRCTRIMINT_TRIM_FAIL_INT_Msk        (1ul << SYS_IRCTRIMINT_TRIM_FAIL_INT_Pos)   /*!< GCR_T::IRCTRIMINT: TRIM_FAIL_INT Mask */

#define SYS_IRCTRIMINT_FREQ_LOCK_Pos            0                                           /*!< GCR_T::IRCTRIMINT: FREQ_LOCK Position */
#define SYS_IRCTRIMINT_FREQ_LOCK_Msk            (1ul << SYS_IRCTRIMINT_FREQ_LOCK_Pos)       /*!< GCR_T::IRCTRIMINT: FREQ_LOCK Mask */

/* GCR REGWRPROT Bit Field Definitions */
#define SYS_REGWRPROT_REGWRPROT_Pos             0                                           /*!< GCR_T::REGWRPROT: REGWRPROT Position */
#define SYS_REGWRPROT_REGWRPROT_Msk             (0xFFul << SYS_REGWRPROT_REGWRPROT_Pos)     /*!< GCR_T::REGWRPROT: REGWRPROT Mask */

#define SYS_REGWRPROT_REGPROTDIS_Pos            0                                       /*!< GCR_T::REGWRPROT: REGPROTDIS Position */
#define SYS_REGWRPROT_REGPROTDIS_Msk            (1ul << SYS_REGWRPROT_REGPROTDIS_Pos)   /*!< GCR_T::REGWRPROT: REGPROTDIS Mask */



typedef struct
{

    /**
     * @var GCR_INT_T::IRQSRC[32]
     * Offset: 0x00-0x7C  IRQn(n=0~31) Interrupt Source Identity Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |INT_SRC   |Interrupt Source Identity
     * |        |          |IRQ_SRC[0].0 - BOD INT
     * |        |          |IRQ_SRC[1].0 - WDT INT
     * |        |          |IRQ_SRC[1].1 - WWDT INT
     * |        |          |IRQ_SRC[2].0 - EINT0, external interrupt 0 from PB.14
     * |        |          |IRQ_SRC[3].0 - EINT1, external interrupt 1 from PB.15
     * |        |          |IRQ_SRC[4].0 - GPA INT
     * |        |          |IRQ_SRC[4].1 - GPB INT
     * |        |          |IRQ_SRC[5].0 - GPC INT
     * |        |          |IRQ_SRC[5].1 - GPD INT
     * |        |          |IRQ_SRC[5].2 - GPE INT
     * |        |          |IRQ_SRC[5].3 - GPF INT
     * |        |          |IRQ_SRC[6].0 - PWM0 INT
     * |        |          |IRQ_SRC[6].1 - PWM1 INT
     * |        |          |IRQ_SRC[6].2 - PWM2 INT
     * |        |          |IRQ_SRC[6].3 - PWM3 INT
     * |        |          |IRQ_SRC[7].0 - PWM4 INT
     * |        |          |IRQ_SRC[7].1 - PWM5 INT
     * |        |          |IRQ_SRC[7].2 - PWM6 INT
     * |        |          |IRQ_SRC[7].3 - PWM7 INT
     * |        |          |IRQ_SRC[8].0 - TMR0 INT
     * |        |          |IRQ_SRC[9].0 - TMR1 INT
     * |        |          |IRQ_SRC[10].0 - TMR2 INT
     * |        |          |IRQ_SRC[11].0 - TMR3 INT
     * |        |          |IRQ_SRC[12].0 - UART0 INT
     * |        |          |IRQ_SRC[12].1 - UART2 INT
     * |        |          |IRQ_SRC[13].0 - UART1 INT
     * |        |          |IRQ_SRC[14].0 - SPI0 INT
     * |        |          |IRQ_SRC[15].0 - SPI1 INT
     * |        |          |IRQ_SRC[16].0 - SPI2 INT
     * |        |          |IRQ_SRC[17].0 - SPI3 INT
     * |        |          |IRQ_SRC[18].0 - I2C0 INT
     * |        |          |IRQ_SRC[19].0 - I2C1 INT
     * |        |          |IRQ_SRC[22].0 - SC0 INT
     * |        |          |IRQ_SRC[22].1 - SC1 INT
     * |        |          |IRQ_SRC[22].2 - SC2 INT
     * |        |          |IRQ_SRC[23].0 - USB INT
     * |        |          |IRQ_SRC[24].0 - PS2 INT
     * |        |          |IRQ_SRC[25].0 - ACMP INT
     * |        |          |IRQ_SRC[26].0 - PDMA INT
     * |        |          |IRQ_SRC[27].0 - I2S INT
     * |        |          |IRQ_SRC[28].0 - Power Down Wake up INT
     * |        |          |IRQ_SRC[29].0 - ADC INT
     * |        |          |IRQ_SRC[30].0 - IRC INT
     * |        |          |IRQ_SRC[31].0 - RTC INT
     * @var GCR_INT_T::NMISEL
     * Offset: 0x80  NMI Interrupt Source Select Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NMI_SEL   |NMI interrupt source selection
     * |        |          |The NMI interrupt to Cortex-M0 can be selected from one of IRQ0~IRQ31 by setting NMI_SEL with IRQ number.
     * |        |          |The default NMI interrupt is assigned as IRQ0 interrupt if NMI is enabled by setting NMI_SEL[8].
     * |[8]     |NMI_EN    |NMI interrupt enable (Write Protect)
     * |        |          |0 = IRQ0~31 assigned to NMI interrupt Disabled. (NMI still can be software triggered by setting its pending flag.)
     * |        |          |1 = IRQ0~31 assigned to NMI interrupt Enabled.
     * |        |          |Note: This bit is write protected bit. Refer to the REGWRPROT register.
     * @var GCR_INT_T::MCUIRQ
     * Offset: 0x84  MCU Interrupt Request Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MCU_IRQ   |MCU IRQ Source Register
     * |        |          |The MCU_IRQ collects all the interrupts from the peripherals and generates the synchronous interrupt to Cortex-M0.
     * |        |          |When the MCU_IRQ[n] is 0:
     * |        |          |0 = No effect.
     * |        |          |1 = Generate an interrupt to Cortex_M0 NVIC[n].
     * |        |          |When the MCU_IRQ[n] is 1 (means an interrupt is assert):
     * |        |          |0 = No effect.
     * |        |          |1 = Clear the interrupt and MCU_IRQ[n].
     */

    __I  uint32_t IRQSRC[32];   /* Offset: 0x00-0x7C  IRQn(n=0~31) Interrupt Source Identity Register               */
    __IO uint32_t NMISEL;       /* Offset: 0x80  NMI Interrupt Source Select Control Register                       */
    __IO uint32_t MCUIRQ;       /* Offset: 0x84  MCU Interrupt Request Source Register                              */
    
} GCR_INT_T;



/* INT IRQSRC Bit Field Definitions */
#define INT_IRQSRC_INT_SRC_Pos                  0                                   /*!< GCR_INT_T::IRQSRC: INT_SRC Position */
#define INT_IRQSRC_INT_SRC_Msk                  (0xFul << INT_IRQSRC_INT_SRC_Pos)

/* INT NMISEL Bit Field Definitions */
#define INT_NMISEL_NMI_EN_Pos                   8                                   /*!< GCR_INT_T::NMISEL: NMI_EN Position */
#define INT_NMISEL_NMI_EN_Msk                   (1ul << INT_NMISEL_NMI_EN_Pos)      /*!< GCR_INT_T::NMISEL: NMI_EN Mask */

#define INT_NMISEL_NMI_SEL_Pos                  0                                   /*!< GCR_INT_T::NMISEL: NMI_SEL Position */
#define INT_NMISEL_NMI_SEL_Msk                  (0x1Ful << INT_NMISEL_NMI_SEL_Pos)  /*!< GCR_INT_T::NMISEL: NMI_SEL Mask */

/* INT MCUIRQ Bit Field Definitions */
#define INT_MCUIRQ_MCU_IRQ_Pos                  0                                           /*!< GCR_INT_T::MCUIRQ: MCU_IRQ Position */
#define INT_MCUIRQ_MCU_IRQ_Msk                  (0xFFFFFFFFul << INT_MCUIRQ_MCU_IRQ_Pos)    /*!< GCR_INT_T::MCUIRQ: MCU_IRQ Mask */
/*@}*/ /* end of group SYS_CONST */
/*@}*/ /* end of group SYS */




/*---------------------- Timer Controller -------------------------*/
/**
    @addtogroup TIMER Timer Controller (TIMER)
    Memory Mapped Structure for TMR Controller
@{ */


typedef struct
{


/**
 * @var TIMER_T::TCSR
 * Offset: 0x00  Timer Control and Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |PRESCALE  |Prescale Counter
 * |        |          |Timer input clock source is divided by (PRESCALE+1) before it is fed to the Timer up
 * |        |          |counter.
 * |        |          |If this field is 0 (PRESCALE = 0), then there is no scaling.
 * |[16]    |TDR_EN    |Data Load Enable Control
 * |        |          |When TDR_EN is set, TDR (Timer Data Register) will be updated continuously with the 24-bit
 * |        |          |up-timer value as the timer is counting.
 * |        |          |0 = Timer Data Register update Disabled.
 * |        |          |1 = Timer Data Register update Enabled while Timer counter is active.
 * |[23]    |WAKE_EN   |Wake Up Function Enable Control
 * |        |          |0 = Wake-up trigger event Disabled.
 * |        |          |1 = Wake-up trigger event Enabled.
 * |[24]    |CTB       |Counter Mode Enable Control
 * |        |          |This bit is for external counting pin function enabled.
 * |        |          |When timer is used as an event counter, this bit should be set to 1 and select HCLK as timer
 * |        |          |clock source.
 * |        |          |Please refer to 5.17.5.6 for detail description.
 * |        |          |0 = External counter mode Disabled.
 * |        |          |1 = External counter mode Enabled.
 * |[25]    |CACT      |Timer Active Status (Read Only)
 * |        |          |This bit indicates the 24-bit up counter status.
 * |        |          |0 = 24-bit up counter is not active.
 * |        |          |1 = 24-bit up counter is active.
 * |[26]    |CRST      |Timer Reset
 * |        |          |0 = No effect.
 * |        |          |1 = Reset 8-bit prescale counter, 24-bit up counter value and CEN bit if CACT is 1.
 * |[28:27] |MODE      |Timer Operating Mode
 * |        |          |00 = The Timer controller is operated in One-shot mode.
 * |        |          |01 = The Timer controller is operated in Periodic mode.
 * |        |          |10 = The Timer controller is operated in Toggle-output mode.
 * |        |          |11 = The Timer controller is operated in Continuous Counting mode.
 * |[29]    |IE        |Interrupt Enable Control
 * |        |          |0 = Timer Interrupt function Disabled.
 * |        |          |1 = Timer Interrupt function Enabled.
 * |        |          |If this bit is enabled, when the timer interrupt flag (TISR[0] TIF) is set to 1, the timer
 * |        |          |interrupt signal is generated and inform to CPU.
 * |[30]    |CEN       |Timer Enable Control
 * |        |          |0 = Stops/Suspends counting.
 * |        |          |1 = Starts counting.
 * |        |          |Note1: In stop status, and then set CEN to 1 will enable the 24-bit up counter to keep
 * |        |          |counting from the last stop counting value.
 * |        |          |Note2: This bit is auto-cleared by hardware in one-shot mode (TCSR [28:27] = 00) when the
 * |        |          |timer interrupt flag (TISR[0] TIF) is generated.
 * |[31]    |DBGACK_TMR|ICE Debug Mode Acknowledge Disable (Write Protect)
 * |        |          |0 = ICE debug mode acknowledgment effects TIMER counting.
 * |        |          |TIMER counter will be held while CPU is held by ICE.
 * |        |          |1 = ICE debug mode acknowledgment Disabled.
 * |        |          |TIMER counter will keep going no matter CPU is held by ICE or not.
 * @var TIMER_T::TCMPR
 * Offset: 0x04  Timer Compare Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[23:0]  |TCMP      |Timer Compared Value
 * |        |          |TCMP is a 24-bit compared value register.
 * |        |          |When the internal 24-bit up counter value is equal to TCMP value, the TIF flag will set to
 * |        |          |1.
 * |        |          |Time-out period = (Period of Timer clock input) * (8-bit PRESCALE + 1) * (24-bit TCMP).
 * |        |          |Note1: Never write 0x0 or 0x1 in TCMP field, or the core will run into unknown state.
 * |        |          |Note2: When timer is operating at continuous counting mode, the 24-bit up counter will keep
 * |        |          |counting continuously even if user writes a new value into TCMP field.
 * |        |          |But if timer is operating at other modes, the 24-bit up counter will restart counting and
 * |        |          |using newest TCMP value to be the timer compared value if user writes a new value into TCMP
 * |        |          |field.
 * @var TIMER_T::TISR
 * Offset: 0x08  Timer Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TIF       |Timer Interrupt Flag
 * |        |          |This bit indicates the interrupt flag status of Timer while TDR value reaches to TCMP value.
 * |        |          |0 = No effect.
 * |        |          |1 = TDR value matches the TCMP value.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * |[1]     |TWF       |Timer Wake-Up Flag
 * |        |          |This bit indicates the interrupt wake-up flag status of Timer.
 * |        |          |0 = Timer does not cause CPU wake-up.
 * |        |          |1 = CPU wake-up from Idle or Power-down mode if Timer time-out interrupt signal generated.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * @var TIMER_T::TDR
 * Offset: 0x0C  Timer Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[23:0]  |TDR       |Timer Data Register
 * |        |          |If TDR_EN (TCSR[16]) is set to 1, TDR register will be updated continuously to monitor
 * |        |          |24-bit up counter value.
 * @var TIMER_T::TCAP
 * Offset: 0x10  Timer Capture Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[23:0]  |TCAP      |Timer Capture Data Register
 * |        |          |When TEXIF flag is set to 1, the current TDR value will be auto-loaded into this TCAP filed
 * |        |          |immediately.
 * @var TIMER_T::TEXCON
 * Offset: 0x14  Timer External Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TX_PHASE  |Timer External Count Pin Phase Detect Selection
 * |        |          |This bit indicates the detection phase of TMx pin.
 * |        |          |0 = A falling edge of TMx pin will be counted.
 * |        |          |1 = A rising edge of TMx pin will be counted.
 * |[2:1]   |TEX_EDGE  |Timer External Capture Pin Edge Detect Selection
 * |        |          |00 = A 1 to 0 transition on TMx_EXT pin will be detected.
 * |        |          |01 = A 0 to 1 transition on TMx_EXT pin will be detected.
 * |        |          |10 = Either 1 to 0 or 0 to 1 transition on TMx_EXT pin will be detected.
 * |        |          |11 = Reserved.
 * |[3]     |TEXEN     |Timer External Pin Function Enable
 * |        |          |This bit enables the RSTCAPSEL function on the TxEX pin.
 * |        |          |0 = RSTCAPSEL function of TxEX pin will be ignored.
 * |        |          |1 = RSTCAPSEL function of TxEX pin is active.
 * |[4]     |RSTCAPSEL |Timer External Reset Counter / Timer External Capture Mode Selection
 * |        |          |0 = Transition on TMx_EXT
 * |        |          |pin is using to save the TDR value into TCAP value if TEXIF flag is set to 1.
 * |        |          |1 = Transition on TMx_EXT pin is using to reset the 24-bit up counter.
 * |[5]     |TEXIEN    |Timer External Capture Interrupt Enable Control
 * |        |          |0 = TMx_EXT pin detection Interrupt Disabled.
 * |        |          |1 = TMx_EXT pin detection Interrupt Enabled.
 * |        |          |If TEXIEN enabled, Timer will raise an external capture interrupt signal and inform to CPU
 * |        |          |while TEXIF flag is set to 1.
 * |[6]     |TEXDB     |Timer External Capture Input Pin De-Bounce Enable Control
 * |        |          |0 = TMx_EXT pin de-bounce Disabled.
 * |        |          |1 = TMx_EXT pin de-bounce Enabled.
 * |        |          |If this bit is enabled, the edge detection of TMx_EXT pin is detected with de-bounce
 * |        |          |circuit.
 * |[7]     |TCDB      |Timer External Counter Input Pin De-Bounce Enable Control
 * |        |          |0 = TMx pin de-bounce Disabled.
 * |        |          |1 = TMx pin de-bounce Enabled.
 * |        |          |If this bit is enabled, the edge detection of TMx pin is detected with de-bounce circuit.
 * @var TIMER_T::TEXISR
 * Offset: 0x18  Timer External Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |TEXIF     |Timer External Capture Interrupt Flag
 * |        |          |This bit indicates the external capture interrupt flag status.
 * |        |          |When TEXEN enabled, TMx_EXT pin selected as external capture function, and a transition on
 * |        |          |TMx_EXT pin matched the TEX_EDGE setting, this flag will set to 1 by hardware.
 * |        |          |1 = TMx_EXT
 * |        |          |pin interrupt occurred.
 * |        |          |0 = TMx_EXT
 * |        |          |pin interrupt did not occur.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 */

    __IO uint32_t TCSR;          /* Offset: 0x00  Timer Control and Status Register                                  */
    __IO uint32_t TCMPR;         /* Offset: 0x04  Timer Compare Register                                             */
    __IO uint32_t TISR;          /* Offset: 0x08  Timer Interrupt Status Register                                    */
    __I  uint32_t TDR;           /* Offset: 0x0C  Timer Data Register                                                */
    __I  uint32_t TCAP;          /* Offset: 0x10  Timer Capture Data Register                                        */
    __IO uint32_t TEXCON;        /* Offset: 0x14  Timer External Control Register                                    */
    __IO uint32_t TEXISR;        /* Offset: 0x18  Timer External Interrupt Status Register                           */

} TIMER_T;



/**
    @addtogroup TIMER_CONST TMR Bit Field Definition
    Constant Definitions for TMR Controller
@{ */

/* TIMER TCSR Bit Field Definitions */
#define TIMER_TCSR_DBGACK_TMR_Pos   31                                          /*!< TIMER_T::TCSR: DBGACK_TMR Position */
#define TIMER_TCSR_DBGACK_TMR_Msk   (1ul << TIMER_TCSR_DBGACK_TMR_Pos)          /*!< TIMER_T::TCSR: DBGACK_TMR Mask */

#define TIMER_TCSR_CEN_Pos          30                                          /*!< TIMER_T::TCSR: CEN Position */
#define TIMER_TCSR_CEN_Msk          (1ul << TIMER_TCSR_CEN_Pos)                 /*!< TIMER_T::TCSR: CEN Mask */

#define TIMER_TCSR_IE_Pos           29                                          /*!< TIMER_T::TCSR: IE Position */
#define TIMER_TCSR_IE_Msk           (1ul << TIMER_TCSR_IE_Pos)                  /*!< TIMER_T::TCSR: IE Mask */

#define TIMER_TCSR_MODE_Pos         27                                          /*!< TIMER_T::TCSR: MODE Position */
#define TIMER_TCSR_MODE_Msk         (0x3ul << TIMER_TCSR_MODE_Pos)              /*!< TIMER_T::TCSR: MODE Mask */

#define TIMER_TCSR_CRST_Pos         26                                          /*!< TIMER_T::TCSR: CRST Position */
#define TIMER_TCSR_CRST_Msk         (1ul << TIMER_TCSR_CRST_Pos)                /*!< TIMER_T::TCSR: CRST Mask */

#define TIMER_TCSR_CACT_Pos         25                                          /*!< TIMER_T::TCSR: CACT Position */
#define TIMER_TCSR_CACT_Msk         (1ul << TIMER_TCSR_CACT_Pos)                /*!< TIMER_T::TCSR: CACT Mask */

#define TIMER_TCSR_CTB_Pos          24                                          /*!< TIMER_T::TCSR: CTB Position */
#define TIMER_TCSR_CTB_Msk          (1ul << TIMER_TCSR_CTB_Pos)                 /*!< TIMER_T::TCSR: CTB Mask */

#define TIMER_TCSR_WAKE_EN_Pos      23                                          /*!< TIMER_T::TCSR: WAKE_EN Position */
#define TIMER_TCSR_WAKE_EN_Msk      (1ul << TIMER_TCSR_WAKE_EN_Pos)             /*!< TIMER_T::TCSR: WAKE_EN Mask */

#define TIMER_TCSR_TDR_EN_Pos       16                                          /*!< TIMER_T::TCSR: TDR_EN Position */
#define TIMER_TCSR_TDR_EN_Msk       (1ul << TIMER_TCSR_TDR_EN_Pos)              /*!< TIMER_T::TCSR: TDR_EN Mask */

#define TIMER_TCSR_PRESCALE_Pos     0                                           /*!< TIMER_T::TCSR: PRESCALE Position */
#define TIMER_TCSR_PRESCALE_Msk     (0xFFul << TIMER_TCSR_PRESCALE_Pos)         /*!< TIMER_T::TCSR: PRESCALE Mask */

/* TIMER TCMPR Bit Field Definitions */
#define TIMER_TCMP_TCMP_Pos         0                                           /*!< TIMER_T::TCMPR: TCMP Position */
#define TIMER_TCMP_TCMP_Msk         (0xFFFFFFul << TIMER_TCMP_TCMP_Pos)         /*!< TIMER_T::TCMPR: TCMP Mask */

/* TIMER TISR Bit Field Definitions */
#define TIMER_TISR_TWF_Pos          1                                           /*!< TIMER_T::TISR: TWF Position */
#define TIMER_TISR_TWF_Msk          (1ul << TIMER_TISR_TWF_Pos)                 /*!< TIMER_T::TISR: TWF Mask */

#define TIMER_TISR_TIF_Pos          0                                           /*!< TIMER_T::TISR: TIF Position */
#define TIMER_TISR_TIF_Msk          (1ul << TIMER_TISR_TIF_Pos)                 /*!< TIMER_T::TISR: TIF Mask */

/* TIMER TDR Bit Field Definitions */
#define TIMER_TDR_TDR_Pos           0                                           /*!< TIMER_T::TDR: TDR Position */
#define TIMER_TDR_TDR_Msk           (0xFFFFFFul << TIMER_TDR_TDR_Pos)           /*!< TIMER_T::TDR: TDR Mask */

/* TIMER TCAP Bit Field Definitions */
#define TIMER_TCAP_TCAP_Pos         0                                           /*!< TIMER_T::TCAP: TCAP Position */
#define TIMER_TCAP_TCAP_Msk         (0xFFFFFFul << TIMER_TCAP_TCAP_Pos)         /*!< TIMER_T::TCAP: TCAP Mask */

/* TIMER TEXCON Bit Field Definitions */
#define TIMER_TEXCON_TCDB_Pos       7                                           /*!< TIMER_T::TEXCON: TCDB Position */
#define TIMER_TEXCON_TCDB_Msk       (1ul << TIMER_TEXCON_TCDB_Pos)              /*!< TIMER_T::TEXCON: TCDB Mask */

#define TIMER_TEXCON_TEXDB_Pos      6                                           /*!< TIMER_T::TEXCON: TEXDB Position */
#define TIMER_TEXCON_TEXDB_Msk      (1ul << TIMER_TEXCON_TEXDB_Pos)             /*!< TIMER_T::TEXCON: TEXDB Mask */

#define TIMER_TEXCON_TEXIEN_Pos     5                                           /*!< TIMER_T::TEXCON: TEXIEN Position */
#define TIMER_TEXCON_TEXIEN_Msk     (1ul << TIMER_TEXCON_TEXIEN_Pos)            /*!< TIMER_T::TEXCON: TEXIEN Mask */

#define TIMER_TEXCON_RSTCAPSEL_Pos  4                                           /*!< TIMER_T::TEXCON: RSTCAPSEL Position */
#define TIMER_TEXCON_RSTCAPSEL_Msk  (1ul << TIMER_TEXCON_RSTCAPSEL_Pos)         /*!< TIMER_T::TEXCON: RSTCAPSEL Mask */

#define TIMER_TEXCON_TEXEN_Pos      3                                           /*!< TIMER_T::TEXCON: TEXEN Position */
#define TIMER_TEXCON_TEXEN_Msk      (1ul << TIMER_TEXCON_TEXEN_Pos)             /*!< TIMER_T::TEXCON: TEXEN Mask */

#define TIMER_TEXCON_TEX_EDGE_Pos   1                                           /*!< TIMER_T::TEXCON: TEX_EDGE Position */
#define TIMER_TEXCON_TEX_EDGE_Msk   (0x3ul << TIMER_TEXCON_TEX_EDGE_Pos)        /*!< TIMER_T::TEXCON: TEX_EDGE Mask */

#define TIMER_TEXCON_TX_PHASE_Pos   0                                           /*!< TIMER_T::TEXCON: TX_PHASE Position */
#define TIMER_TEXCON_TX_PHASE_Msk   (1ul << TIMER_TEXCON_TX_PHASE_Pos)          /*!< TIMER_T::TEXCON: TX_PHASE Mask */

/* TIMER TEXISR Bit Field Definitions */
#define TIMER_TEXISR_TEXIF_Pos      0                                           /*!< TIMER_T::TEXISR: TEXIF Position */
#define TIMER_TEXISR_TEXIF_Msk      (1ul << TIMER_TEXISR_TEXIF_Pos)             /*!< TIMER_T::TEXISR: TEXIF Mask */
/*@}*/ /* end of group TIMER_CONST */
/*@}*/ /* end of group TIMER */



/*---------------------- Universal Asynchronous Receiver/Transmitter Controller -------------------------*/
/**
    @addtogroup UART Universal Asynchronous Receiver/Transmitter Controller (UART)
    Memory Mapped Structure for UART Controller
@{ */


typedef struct
{



/**
 * @var UART_T::DATA
 * Offset: 0x00  UART Data Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |DATA      |Data Register
 * |        |          |By writing to this register, the UART will send out an 8-bit data through the UART_TXD pin (LSB first).
 * |        |          |By reading this register, the UART will return an 8-bit data received from UART_RXD pin (LSB first).
 * @var UART_T::THR
 * Offset: 0x00  UART Transmit Holding Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |THR       |Transmit Holding Register
 * |        |          |By writing to this register, the UART will send out an 8-bit data through the UART_TXD pin (LSB first).
 * @var UART_T::RBR
 * Offset: 0x00  UART Receive Buffer Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |RBR       |Receive Buffer Register (Read Only)
 * |        |          |By reading this register, the UART will return an 8-bit data received from UART_RXD pin (LSB first).
 * @var UART_T::IER
 * Offset: 0x04  UART Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RDA_IEN   |Receive Data Available Interrupt Enable Control
 * |        |          |0 = RDA_INT Masked off.
 * |        |          |1 = RDA_INT Enabled.
 * |[1]     |THRE_IEN  |Transmit Holding Register Empty Interrupt Enable Control
 * |        |          |0 = THRE_INT Masked off.
 * |        |          |1 = THRE_INT Enabled.
 * |[2]     |RLS_IEN   |Receive Line Status Interrupt Enable Control
 * |        |          |0 = RLS_INT Masked off.
 * |        |          |1 = RLS_INT Enabled
 * |[3]     |MODEM_IEN |Modem Status Interrupt Enable Control (Not Available In UART2 Channel)
 * |        |          |0 = MODEM_INT Masked off.
 * |        |          |1 = MODEM_INT Enabled.
 * |[4]     |TOUT_IEN  |RX Time-Out Interrupt Enable Control
 * |        |          |0 = TOUT_INT Masked off.
 * |        |          |1 = TOUT_INT Enabled.
 * |[5]     |BUF_ERR_IEN|Buffer Error Interrupt Enable Control
 * |        |          |0 = BUF_ERR_INT Masked off.
 * |        |          |1 = BUF_ERR_INT Enabled.
 * |[6]     |WAKE_EN   |UART Wake-Up Function Enable (Not Available In UART2 Channel)
 * |        |          |0 = UART wake-up function Disabled.
 * |        |          |1 = UART wake-up function Enabled, when the chip is in Power-down mode, an external CTS
 * |        |          |change will wake-up chip from Power-down mode.
 * |[8]     |LIN_IEN   |LIN Bus Interrupt Enable
 * |        |          |0 = Lin bus interrupt Disabled.
 * |        |          |1 = Lin bus interrupt Enabled.
 * |        |          |Note: This field is used for LIN function mode.
 * |[11]    |TIME_OUT_EN|Time-Out Counter Enable
 * |        |          |0 = Time-out counter Disabled.
 * |        |          |1 = Time-out counter Enabled.
 * |[12]    |AUTO_RTS_EN|RTS Auto Flow Control Enable (Not Available in UART2 Channel)
 * |        |          |0 = RTS auto flow control Disabled.
 * |        |          |1 = RTS auto flow control Enabled.
 * |        |          |When RTS auto-flow is enabled, if the number of bytes in the RX FIFO equals the RTS_TRI_LEV (UA_FCR [19:16]), the UART will de-assert RTS signal.
 * |[13]    |AUTO_CTS_EN|CTS Auto Flow Control Enable (Not Available in UART2 Channel)
 * |        |          |0 = CTS auto flow control Disabled.
 * |        |          |1 = CTS auto flow control Enabled.
 * |        |          |When CTS auto-flow is enabled, the UART will send data to external device when CTS input
 * |        |          |assert (UART will not send data to device until CTS is asserted).
 * |[14]    |DMA_TX_EN |TX DMA Enable (Not Available In UART2 Channel)
 * |        |          |This bit can enable or disable TX DMA service.
 * |        |          |0 = TX DMA Disabled.
 * |        |          |1 = TX DMA Enabled.
 * |[15]    |DMA_RX_EN |RX DMA Enable (Not Available In UART2 Channel)
 * |        |          |This bit can enable or disable RX DMA service.
 * |        |          |0 = RX DMA Disabled.
 * |        |          |1 = RX DMA Enabled.
 * @var UART_T::FCR
 * Offset: 0x08  UART FIFO Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1]     |RFR       |RX Field Software Reset
 * |        |          |When RFR is set, all the byte in the receiver FIFO and RX internal state machine are cleared.
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the RX internal state machine and pointers.
 * |        |          |Note: This bit will automatically clear at least 3 UART peripheral clock cycles.
 * |[2]     |TFR       |TX Field Software Reset
 * |        |          |When TFR is set, all the byte in the transmit FIFO and TX internal state machine are cleared.
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the TX internal state machine and pointers.
 * |        |          |Note: This bit will automatically clear at least 3 UART peripheral clock cycles.
 * |[7:4]   |RFITL     |RX FIFO Interrupt Trigger Level
 * |        |          |When the number of bytes in the receive FIFO equals the RFITL, the RDA_IF will be set (if RDA_IEN (UA_IER[0]) enabled, and an interrupt will be generated).
 * |        |          |0000 = RX FIFO Interrupt Trigger Level is 1 byte.
 * |        |          |0001 = RX FIFO Interrupt Trigger Level is 4 bytes.
 * |        |          |0010 = RX FIFO Interrupt Trigger Level is 8 bytes.
 * |        |          |0011 = RX FIFO Interrupt Trigger Level is 14 bytes.
 * |        |          |0100 = RX FIFO Interrupt Trigger Level is 30/14 bytes (High Speed/Normal Speed).
 * |        |          |0101 = RX FIFO Interrupt Trigger Level is 46/14 bytes (High Speed/Normal Speed).
 * |        |          |0110 = RX FIFO Interrupt Trigger Level is 62/14 bytes (High Speed/Normal Speed).
 * |        |          |Other = Reserved.
 * |[8]     |RX_DIS    |Receiver Disable Register
 * |        |          |The receiver is disabled or not (set 1 to disable receiver).
 * |        |          |0 = Receiver Enabled.
 * |        |          |1 = Receiver Disabled.
 * |        |          |Note: This field is used for RS-485 Normal Multi-drop mode. It should be programmed before RS485_NMM (UA_ALT_CSR[8]) is programmed.
 * |[19:16] |RTS_TRI_LEV|RTS Trigger Level For Auto-Flow Control Use (Not Available In UART2 Channel)
 * |        |          |0000 = RTS Trigger Level is 1 byte.
 * |        |          |0001 = RTS Trigger Level is 4 bytes.
 * |        |          |0010 = RTS Trigger Level is 8 bytes.
 * |        |          |0011 = RTS Trigger Level is 14 bytes.
 * |        |          |0100 = RTS Trigger Level is 30/14 bytes (High Speed/Normal Speed).
 * |        |          |0101 = RTS Trigger Level is 46/14 bytes (High Speed/Normal Speed).
 * |        |          |0110 = RTS Trigger Level is 62/14 bytes (High Speed/Normal Speed).
 * |        |          |Other = Reserved.
 * |        |          |Note: This field is used for RTS auto-flow control.
 * @var UART_T::LCR
 * Offset: 0x0C  UART Line Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |WLS       |Word Length Selection
 * |        |          |00 = Word length is 5-bit.
 * |        |          |01 = Word length is 6-bit.
 * |        |          |10 = Word length is 7-bit
 * |        |          |11 = Word length is 8-bit
 * |[2]     |NSB       |Number Of "STOP Bit"
 * |        |          |0 = One " STOP bit" is generated in the transmitted data.
 * |        |          |1 = When select 5-bit word length, 1.5 "STOP bit" is generated in the transmitted data.
 * |        |          |When select 6-,7- and 8-bit word length, 2 "STOP bit" is generated in the transmitted data.
 * |[3]     |PBE       |Parity Bit Enable
 * |        |          |0 = No parity bit.
 * |        |          |1 = Parity bit is generated on each outgoing character and is checked on each incoming data.
 * |[4]     |EPE       |Even Parity Enable
 * |        |          |0 = Odd number of logic 1's is transmitted and checked in each word.
 * |        |          |1 = Even number of logic 1's is transmitted and checked in each word.
 * |        |          |This bit has effect only when PBE (UA_LCR[3]) is set.
 * |[5]     |SPE       |Stick Parity Enable
 * |        |          |0 = Stick parity Disabled.
 * |        |          |1 = If PBE (UA_LCR[3]) and EBE (UA_LCR[4]) are logic 1, the parity bit is transmitted and checked as logic 0.
 * |        |          |If PBE (UA_LCR[3]) is 1 and EBE (UA_LCR[4]) is 0 then the parity bit is transmitted and checked as 1.
 * |[6]     |BCB       |Break Control Bit
 * |        |          |When this bit is set to logic 1, the serial data output (TX) is forced to the Spacing State (logic 0).
 * |        |          |This bit acts only on TX and has no effect on the transmitter logic.
 * @var UART_T::MCR
 * Offset: 0x10  UART Modem Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1]     |RTS       |RTS (Request-To-Send) Signal Control (Not Available In UART2 Channel)
 * |        |          |This bit is direct control internal RTS signal active or not, and then drive the RTS pin output with LEV_RTS bit configuration.
 * |        |          |0 = RTS signal is active.
 * |        |          |1 = RTS signal is inactive.
 * |        |          |Note1: This RTS signal control bit is not effective when RTS auto-flow control is enabled in UART function mode.
 * |        |          |Note2: This RTS signal control bit is not effective when RS-485 auto direction mode (AUD) is enabled in RS-485 function mode.
 * |[9]     |LEV_RTS   |RTS Pin Active Level (Not Available In UART2 Channel)
 * |        |          |This bit defines the active level state of RTS pin output.
 * |        |          |0 = RTS pin output is high level active.
 * |        |          |1 = RTS pin output is low level active.
 * |[13]    |RTS_ST    |RTS Pin State (Read Only) (Not Available In UART2 Channel)
 * |        |          |This bit mirror from RTS pin output of voltage logic status.
 * |        |          |0 = RTS pin output is low level voltage logic state.
 * |        |          |1 = RTS pin output is high level voltage logic state.
 * @var UART_T::MSR
 * Offset: 0x14  UART Modem Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |DCTSF     |Detect CTS State Change Flag (Not Available In UART2 Channel)
 * |        |          |This bit is set whenever CTS input has change state, and it will generate Modem interrupt to CPU when MODEM_IEN (UA_IER [3]) is set to 1.
 * |        |          |0 = CTS input has not change state.
 * |        |          |1 = CTS input has change state.
 * |        |          |Note: This bit can be cleared by writing "1" to it.
 * |[4]     |CTS_ST    |CTS Pin Status (Read Only) (Not Available In UART2 Channel)
 * |        |          |This bit mirror from CTS pin input of voltage logic status.
 * |        |          |0 = CTS pin input is low level voltage logic state.
 * |        |          |1 = CTS pin input is high level voltage logic state.
 * |        |          |Note: This bit echoes when UART Controller peripheral clock is enabled, and CTS multi-function port is selected.
 * |[8]     |LEV_CTS   |CTS Pin Active Level
 * |        |          |This bit defines the active level state of CTS pin input.
 * |        |          |0 = CTS pin input is high level active.
 * |        |          |1 = CTS pin input is low level active.
 * @var UART_T::FSR
 * Offset: 0x18  UART FIFO Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RX_OVER_IF|RX Overflow Error Interrupt Flag
 * |        |          |This bit is set when RX FIFO overflow.
 * |        |          |If the number of bytes of received data is greater than RX_FIFO (UA_RBR) size, 64/16/16 bytes of UART0/UART1/UART2, this bit will be set.
 * |        |          |0 = RX FIFO is not overflow.
 * |        |          |1 = RX FIFO is overflow.
 * |        |          |Note: This bit can be cleared by writing "1" to it.
 * |[3]     |RS485_ADD_DETF|RS-485 Address Byte Detection Flag 
 * |        |          |0 = Receiver detects a data that is not an address bit (bit 9 ='1').
 * |        |          |1 = Receiver detects a data that is an address bit (bit 9 ='1').
 * |        |          |Note1: This field is used for RS-485 function mode and RS485_ADD_EN (UA_ALT_CSR[15]) is set to 1 to enable Address detection mode.
 * |        |          |Note2: This bit can be cleared by writing '1' to it.
 * |[4]     |PEF       |Parity Error Flag 
 * |        |          |This bit is set to logic 1 whenever the received character does not have a valid "parity bit", and is reset whenever the CPU writes 1 to this bit.
 * |        |          |0 = No parity error is generated.
 * |        |          |1 = Parity error is generated.
 * |        |          |Note: This bit can be cleared by writing "1" to it.
 * |[5]     |FEF       |Framing Error Flag
 * |        |          |This bit is set to logic 1 whenever the received character does not have a valid "stop bit" (that is, the stop bit following the last data bit or parity bit is detected as logic 0), and is reset whenever the CPU writes 1 to this bit.
 * |        |          |0 = No framing error is generated.
 * |        |          |1 = Framing error is generated.
 * |        |          |Note: This bit can be cleared by writing "1" to it.
 * |[6]     |BIF       |Break Interrupt Flag
 * |        |          |This bit is set to logic 1 whenever the received data input(RX) is held in the "spacing state" (logic 0) for longer than a full word transmission time (that is, the total time of "start bit" + data bits + parity + stop bits) and is reset whenever the CPU writes 1 to this bit.
 * |        |          |0 = No Break interrupt is generated.
 * |        |          |1 = Break interrupt is generated.
 * |        |          |Note: This bit can be cleared by writing "1" to it.
 * |[13:8]  |RX_POINTER|RX FIFO Pointer (Read Only)
 * |        |          |This field indicates the RX FIFO Buffer Pointer.
 * |        |          |When UART receives one byte from external device, then RX_POINTER increases one.
 * |        |          |When one byte of RX FIFO is read by CPU, then RX_POINTER decreases one.
 * |        |          |The Maximum value shown in RX_POINTER is 63/15/15 (UART0/UART1/UART2).
 * |        |          |When the using level of RX FIFO Buffer equal to 64/16/16, the RX_FULL bit is set to 1 and RX_POINTER will show 0.
 * |        |          |As one byte of RX FIFO is read by CPU, the RX_FULL bit is cleared to 0 and RX_POINTER will show 63/15/15 (UART0/UART1/UART2).
 * |[14]    |RX_EMPTY  |Receiver FIFO Empty (Read Only)
 * |        |          |This bit initiate RX FIFO empty or not.
 * |        |          |0 = RX FIFO is not empty.
 * |        |          |1 = RX FIFO is empty.
 * |        |          |Note: When the last byte of RX FIFO has been read by CPU, hardware sets this bit high. It will be cleared when UART receives any new data.
 * |[15]    |RX_FULL   |Receiver FIFO Full (Read Only)
 * |        |          |This bit initiates RX FIFO is full or not.
 * |        |          |0 = RX FIFO is not full.
 * |        |          |1 = RX FIFO is full.
 * |        |          |Note: This bit is set when the number of usage in RX FIFO Buffer is equal to 64/16/16(UART0/UART1/UART2), otherwise is cleared by hardware.
 * |[21:16] |TX_POINTER|TX FIFO Pointer (Read Only)
 * |        |          |This field indicates the TX FIFO Buffer Pointer.
 * |        |          |When CPU writes one byte into UA_THR, then TX_POINTER increases one.
 * |        |          |When one byte of TX FIFO is transferred to Transmitter Shift Register, then TX_POINTER decreases one.
 * |        |          |The Maximum value shown in TX_POINTER is 63/15/15 (UART0/UART1/UART2).
 * |        |          |When the using level of TX FIFO Buffer equal to 64/16/16, the TX_FULL bit is set to 1 and TX_POINTER will show 0.
 * |        |          |As one byte of TX FIFO is transferred to Transmitter Shift Register, the TX_FULL bit is cleared to 0 and TX_POINTER will show 63/15/15 (UART0/UART1/UART2).
 * |[22]    |TX_EMPTY  |Transmitter FIFO Empty (Read Only)
 * |        |          |This bit indicates TX FIFO empty or not.
 * |        |          |0 = TX FIFO is not empty.
 * |        |          |1 = TX FIFO is empty.
 * |        |          |Note: When the last byte of TX FIFO has been transferred to Transmitter Shift Register, hardware sets this bit high. It will be cleared when writing data into THR (TX FIFO not empty).
 * |[23]    |TX_FULL   |Transmitter FIFO Full (Read Only)
 * |        |          |This bit indicates TX FIFO full or not.
 * |        |          |0 = TX FIFO is not full.
 * |        |          |1 = TX FIFO is full.
 * |        |          |This bit is set when the number of usage in TX FIFO Buffer is equal to 64/16/16(UART0/UART1/UART2), otherwise is cleared by hardware.
 * |[24]    |TX_OVER_IF|TX Overflow Error Interrupt Flag 
 * |        |          |If TX FIFO (UA_THR) is full, an additional write to UA_THR will cause this bit to logic 1.
 * |        |          |0 = TX FIFO is not overflow.
 * |        |          |1 = TX FIFO is overflow.
 * |        |          |Note: This bit can be cleared by writing "1" to it.
 * |[28]    |TE_FLAG   |Transmitter Empty Flag (Read Only)
 * |        |          |This bit is set by hardware when TX FIFO (UA_THR) is empty and the STOP bit of the last byte has been transmitted.
 * |        |          |0 = TX FIFO is not empty.
 * |        |          |1 = TX FIFO is empty.
 * |        |          |Note: This bit is cleared automatically when TX FIFO is not empty or the last byte transmission has not completed.
 * @var UART_T::ISR
 * Offset: 0x1C  UART Interrupt Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |RDA_IF    |Receive Data Available Interrupt Flag (Read Only)
 * |        |          |When the number of bytes in the RX FIFO equals the RFITL then the RDA_IF(UA_ISR[0]) will be set.
 * |        |          |If RDA_IEN (UA_IER [0]) is enabled, the RDA interrupt will be generated.
 * |        |          |0 = No RDA interrupt flag is generated.
 * |        |          |1 = RDA interrupt flag is generated.
 * |        |          |Note: This bit is read only and it will be cleared when the number of unread bytes of RX FIFO drops below the threshold level (RFITL(UA_FCR[7:4]).
 * |[1]     |THRE_IF   |Transmit Holding Register Empty Interrupt Flag (Read Only)
 * |        |          |This bit is set when the last data of TX FIFO is transferred to Transmitter Shift Register.
 * |        |          |If THRE_IEN (UA_IER[1]) is enabled, the THRE interrupt will be generated.
 * |        |          |0 = No THRE interrupt flag is generated.
 * |        |          |1 = THRE interrupt flag is generated.
 * |        |          |Note: This bit is read only and it will be cleared when writing data into THR (TX FIFO not empty).
* |[2]     |RLS_IF    |Receive Line Interrupt Flag
* |        |          |This bit is set when the RX receive data have parity error, frame error or break error (at least one of 3 bits, BIF(UA_FSR[6]), FEF(UA_FSR[5]) and PEF(UA_FSR[4]), is set).
* |        |          |If RLS_IEN (UA_IER [2]) is enabled, the RLS interrupt will be generated.
* |        |          |0 = No RLS interrupt flag is generated.
* |        |          |1 = RLS interrupt flag is generated.
* |        |          |Note1: In RS-485 function mode, this field is set include receiver detect and received address byte character (bit9 = '1') bit. At the same time, the bit of RS485_ADD_DETF(UA_FSR[3]) is also set.
* |        |          |Note2: This bit is read only and reset to 0 when all bits of BIF(UA_FSR[6]), FEF(UA_FSR[5]) and PEF(UA_FSR[4]) are cleared.
* |        |          |Note3: In RS-485 function mode, this bit is read only and reset to 0 when all bits of BIF(UA_FSR[6]) , FEF(UA_FSR[5]) and PEF(UA_FSR[4]) and RS485_ADD_DETF (UA_FSR[3]) are cleared.
 * |[3]     |MODEM_IF  |MODEM Interrupt Flag (Read Only) (Not Available In UART2 Channel)
 * |        |          |This bit is set when the CTS pin has state change (DCTSF (UA_MSR[0]) = 1).
 * |        |          |If MODEM_IEN (UA_IER [3]) is enabled, the Modem interrupt will be generated.
 * |        |          |0 = No Modem interrupt flag is generated.
 * |        |          |1 = Modem interrupt flag is generated.
 * |        |          |Note: This bit is read only and reset to 0 when bit DCTSF is cleared by a write 1 on DCTSF(UA_MSR[0]).
 * |[4]     |TOUT_IF   |Time-out Interrupt Flag (Read Only)
 * |        |          |This bit is set when the RX FIFO is not empty and no activities occurred in the RX FIFO and the time-out counter equal to TOIC(UA_TOR[7:0]).
 * |        |          |If TOUT_IEN (UA_IER [4]) is enabled, the Time-out interrupt will be generated.
 * |        |          |0 = No Time-out interrupt flag is generated.
 * |        |          |1 = Time-out interrupt flag is generated.
 * |        |          |Note: This bit is read only and user can read UA_RBR (RX is in active) to clear it.
 * |[5]     |BUF_ERR_IF|Buffer Error Interrupt Flag (Read Only)
 * |        |          |This bit is set when the TX FIFO or RX FIFO overflows (TX_OVER_IF (UA_FSR[24]) or RX_OVER_IF (UA_FSR[0]) is set).
 * |        |          |When BUF_ERR_IF (UA_ISR[5])is set, the transfer is not correct.
 * |        |          |If BUF_ERR_IEN (UA_IER [8]) is enabled, the buffer error interrupt will be generated.
 * |        |          |0 = No buffer error interrupt flag is generated.
 * |        |          |1 = Buffer error interrupt flag is generated.
 * |        |          |Note: This bit is read only and reset to 0 when all bits of TX_OVER_IF(UA_FSR[24]) and RX_OVER_IF(UA_FSR[0]) are cleared.
 * |[7]     |LIN_IF    |LIN Bus Flag (Read Only)
 * |        |          |This bit is set when LIN slave header detect (LINS_HDET_F (UA_LIN_SR[0] = 1)), LIN break detect (LIN_BKDET_F(UA_LIN_SR[9]=1)), bit error detect (BIT_ERR_F(UA_LIN_SR[9]=1), LIN slave ID parity error (LINS_IDPERR_F(UA_LIN_SR[2] = 1) or LIN slave header error detect (LINS_HERR_F (UA_LIN_SR[1])).
 * |        |          |If LIN_ IEN (UA_IER [8]) is enabled the LIN interrupt will be generated.
 * |        |          |0 = None of LINS_HDET_F, LIN_BKDET_F, BIT_ERR_F, LINS_IDPERR_F and LINS_HERR_F is generated.
 * |        |          |1 = At least one of LINS_HDET_F, LIN_BKDET_F, BIT_ERR_F, LINS_IDPERR_F and LINS_HERR_F is generated.
 * |        |          |Note: This bit is read only. This bit is cleared when LINS_HDET_F(UA_LIN_SR[0]), LIN_BKDET_F(UA_LIN_SR[9]), BIT_ERR_F(UA_LIN_SR[9]), LINS_IDPENR_F (UA_LIN_SR[2]) and LINS_HERR_F(UA_LIN_SR[1]) all are cleared.
 * |[8]     |RDA_INT   |Receive Data Available Interrupt Indicator (Read Only)
 * |        |          |This bit is set if RDA_IEN (UA_IER[0]) and RDA_IF (UA_ISR[0]) are both set to 1.
 * |        |          |0 = No RDA interrupt is generated.
 * |        |          |1 = RDA interrupt is generated.
 * |[9]     |THRE_INT  |Transmit Holding Register Empty Interrupt Indicator (Read Only)
 * |        |          |This bit is set if THRE_IEN (UA_IER[1])and THRE_IF(UA_SR[1]) are both set to 1.
 * |        |          |0 = No THRE interrupt is generated.
 * |        |          |1 = THRE interrupt is generated.
 * |[10]    |RLS_INT   |Receive Line Status Interrupt Indicator (Read Only)
 * |        |          |This bit is set if RLS_IEN (UA_IER[2]) and RLS_IF(UA_ISR[2]) are both set to 1.
 * |        |          |0 = No RLS interrupt is generated.
 * |        |          |1 = RLS interrupt is generated
 * |[11]    |MODEM_INT |MODEM Status Interrupt Indicator (Read Only) (Not Available In UART2 Channel)
 * |        |          |This bit is set if MODEM_IEN(UA_IER[3] and MODEM_IF(UA_ISR[4]) are both set to 1
 * |        |          |0 = No Modem interrupt is generated.
 * |        |          |1 = Modem interrupt is generated.
 * |[12]    |TOUT_INT  |Time-Out Interrupt Indicator (Read Only)
 * |        |          |This bit is set if TOUT_IEN(UA_IER[4]) and TOUT_IF(UA_ISR[4]) are both set to 1.
 * |        |          |0 = No Time-Out interrupt is generated.
 * |        |          |1 = Time-Out interrupt is generated.
 * |[13]    |BUF_ERR_INT|Buffer Error Interrupt Indicator (Read Only)
 * |        |          |This bit is set if BUF_ERR_IEN(UA_IER[5] and BUF_ERR_IF(UA_ISR[5]) are both set to 1.
 * |        |          |0 = No buffer error interrupt is generated.
 * |        |          |1 = Buffer error interrupt is generated.
 * |[15]    |LIN_INT   |LIN Bus Interrupt Indicator (Read Only)
 * |        |          |This bit is set if LIN_IEN (UA_IER[8]) and LIN _IF(UA_ISR[7]) are both set to 1.
 * |        |          |0 = No LIN Bus interrupt is generated.
 * |        |          |1 = The LIN Bus interrupt is generated.
 * |[18]    |HW_RLS_IF |In DMA Mode, Receive Line Status Flag (Read Only)
 * |        |          |This bit is set when the RX receive data have parity error, frame error or break error (at least one of 3 bits, BIF (UA_FSR[6]), FEF (UA_FSR[5]) and PEF (UA_FSR[4]) is set).
 * |        |          |If RLS_IEN (UA_IER [2]) is enabled, the RLS interrupt will be generated.
 * |        |          |0 = No RLS interrupt flag is generated in DMA mode.
 * |        |          |1 = RLS interrupt flag is generated in DMA mode.
 * |        |          |Note1: In RS-485 function mode, this field include receiver detect any address byte received address byte character (bit9 = '1') bit.
 * |        |          |Note2: In UART function mode, this bit is read only and reset to 0 when all bits of BIF(UA_FSR[6]) , FEF(UA_FSR[5]) and PEF(UA_FSR[4]) are cleared.
 * |        |          |Note3: In RS-485 function mode, this bit is read only and reset to 0 when all bits of BIF(UA_FSR[6]) , FEF(UA_FSR[5]) and PEF(UA_FSR[4]) and RS485_ADD_DETF (UA_FSR[3]) are cleared.
 * |[19]    |HW_MODEM_IF|In DMA Mode, MODEM Interrupt Flag (Read Only) (Not Available In UART2 Channel)
 * |        |          |This bit is set when the CTS pin has state change (DCTSF (US_MSR[0] =1)).
 * |        |          |If MODEM_IEN (UA_IER [3]) is enabled, the Modem interrupt will be generated.
 * |        |          |0 = No Modem interrupt flag is generated in DMA mode.
 * |        |          |1 = Modem interrupt flag is generated in DMA mode.
 * |        |          |Note: This bit is read only and reset to 0 when the bit DCTSF(US_MSR[0]) is cleared by writing 1 on DCTSF (US_MSR[0]).
 * |[20]    |HW_TOUT_IF|In DMA Mode, Time-Out Interrupt Flag (Read Only)
 * |        |          |This bit is set when the RX FIFO is not empty and no activities occurred in the RX FIFO and the time-out counter equal to TOIC (UA_TOR[7:0]).
 * |        |          |If TOUT_IEN (UA_IER [4]) is enabled, the Tout interrupt will be generated.
 * |        |          |0 = No Time-out interrupt flag is generated in DMA mode.
 * |        |          |1 = Time-out interrupt flag is generated in DMA mode.
 * |        |          |Note: This bit is read only and user can read UA_RBR (RX is in active) to clear it.
 * |[21]    |HW_BUF_ERR_IF|In DMA Mode, Buffer Error Interrupt Flag (Read Only)
 * |        |          |This bit is set when the TX or RX FIFO overflows (TX_OVER_IF (UA__FSR[24]) or RX_OVER_IF (UA_FSR[0]) is set).
 * |        |          |When BUF_ERR_IF (UA_ISR[5]) is set, the transfer maybe is not correct.
 * |        |          |If BUF_ERR_IEN (UA_IER [5]) is enabled, the buffer error interrupt will be generated.
 * |        |          |0 = No buffer error interrupt flag is generated in DMA mode.
 * |        |          |1 = Buffer error interrupt flag is generated in DMA mode.
 * |        |          |Note: This bit is cleared when both TX_OVER_IF (UA_FSR[24]]) and RX_OVER_IF (UA_FSR[0]) are cleared.
 * |[26]    |HW_RLS_INT|In DMA Mode, Receive Line Status Interrupt Indicator (Read Only)
 * |        |          |This bit is set if RLS_IEN (UA_IER[2])and HW_RLS_IF(UA_ISR[18]) are both set to 1.
 * |        |          |0 = No RLS interrupt is generated in DMA mode.
 * |        |          |1 = RLS interrupt is generated in DMA mode.
 * |[27]    |HW_MODEM_INT|In DMA Mode, MODEM Status Interrupt Indicator (Read Only) (Not Available In UART2 Channel)
 * |        |          |This bit is set if MODEM_IEN(UA_IER[3]) and HW_MODEM_IF(UA_ ISR[3]) are both set to 1.
 * |        |          |0 = No Modem interrupt is generated in DMA mode.
 * |        |          |1 = Modem interrupt is generated in DMA mode.
 * |[28]    |HW_TOUT_INT|In DMA Mode, Time-Out Interrupt Indicator (Read Only)
 * |        |          |This bit is set if TOUT_IEN (UA_IER[4])and HW_TOUT_IF(UA_ISR[20]) are both set to 1.
 * |        |          |0 = No Tout interrupt is generated in DMA mode.
 * |        |          |1 = Tout interrupt is generated in DMA mode.
 * |[29]    |HW_BUF_ERR_INT|In DMA Mode, Buffer Error Interrupt Indicator (Read Only)
 * |        |          |This bit is set if BUF_ERR_IEN (UA_IER[5]) and HW_BUF_ERR_IF (UA_ISR[5])are both set to 1.
 * |        |          |0 = No buffer error interrupt is generated in DMA mode.
 * |        |          |1 = Buffer error interrupt is generated in DMA mode.
 * @var UART_T::TOR
 * Offset: 0x20  UART Time-out Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7:0]   |TOIC      |Time-out Interrupt Comparator
 * |        |          |The time-out counter resets and starts counting (the counting clock = baud rate) whenever the RX FIFO receives a new data word.
 * |        |          |Once the content of time-out counter is equal to that of time-out interrupt comparator (TOIC (UA_TOR[7:0])), a receiver time-out interrupt is generated if TOUT_IEN (UA_IER [4]) enabled.
 * |        |          |A new incoming data word or RX FIFO empty will clear TOUT_IF(UA_IER[4]).
 * |        |          |In order to avoid receiver time-out interrupt generation immediately during one character is being received, TOIC (UA_TOR[7:0]) value should be set between 40 and 255.
 * |        |          |So, for example, if TOIC (UA_TOR[7:0]) is set with 40, the time-out interrupt is generated after four characters are not received when 1 stop bit and no parity check is set for UART transfer.
 * |[15:8]  |DLY       |TX Delay Time Value
 * |        |          |This field is used to programming the transfer delay time between the last stop bit and next start bit.
 * @var UART_T::BAUD
 * Offset: 0x24  UART Baud Rate Divisor Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[15:0]  |BRD       |Baud Rate Divider
 * |        |          |The field indicates the baud rate divider.
 * |[27:24] |DIVIDER_X |Divider X
 * |        |          |The baud rate divider M = X+1.
 * |[28]    |DIV_X_ONE |Divider X Equal To 1
 * |        |          |0 = Divider M is X+1 (the equation of M = X+1, but DIVIDER_X[27:24] must >= 8).
 * |        |          |1 = Divider M is 1.
 * |[29]    |DIV_X_EN  |Divider X Enable
 * |        |          |The BRD = Baud Rate Divider, and the baud rate equation is
 * |        |          |Baud Rate = Clock / [M * (BRD + 2)]; The default value of M is 16.
 * |        |          |0 = Divider X Disabled (the equation of M = 16).
 * |        |          |1 = Divider X Enabled (the equation of M = X+1, but DIVIDER_X [27:24] must >= 8).
 * |        |          |Note: In IrDA mode, this bit must disable.
 * @var UART_T::IRCR
 * Offset: 0x28  UART IrDA Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1]     |TX_SELECT |IrDA Receiver/Transmitter Selection Enable Control
 * |        |          |0 = IrDA Transmitter Disabled and Receiver Enabled.
 * |        |          |1 = IrDA Transmitter Enabled and Receiver Disabled.
 * |[5]     |INV_TX    |IrDA inverse Transmitting Output Signal Control
 * |        |          |0 = None inverse transmitting signal.
 * |        |          |1 = Inverse transmitting output signal.
 * |[6]     |INV_RX    |IrDA inverse Receive Input Signal Control
 * |        |          |0 = None inverse receiving input signal.
 * |        |          |1 = Inverse receiving input signal.
 * @var UART_T::ALT_CSR
 * Offset: 0x2C  UART Alternate Control/Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |LIN_BKFL  |UART LIN Break Field Length
 * |        |          |This field indicates a 4-bit LIN TX break field count.
 * |        |          |Note1: This break field length is UA_LIN_BKFL + 1
 * |        |          |Note2: According to LIN spec, the reset value is 0xC (break field length = 13).
 * |[6]     |LIN_RX_EN |LIN RX Enable
 * |        |          |0 = LIN RX mode Disabled.
 * |        |          |1 = LIN RX mode Enabled.
 * |[7]     |LIN_TX_EN |LIN TX Break Mode Enable
 * |        |          |0 = LIN TX Break mode Disabled.
 * |        |          |1 = LIN TX Break mode Enabled.
 * |        |          |Note: When TX break field transfer operation finished, this bit will be cleared automatically.
 * |[8]     |RS485_NMM |RS-485 Normal Multi-Drop Operation Mode (NMM)
 * |        |          |0 = RS-485 Normal Multi-drop Operation mode (NMM) Disabled.
 * |        |          |1 = RS-485 Normal Multi-drop Operation mode (NMM) Enabled.
 * |        |          |Note: It cannot be active with RS-485_AAD operation mode.
 * |[9]     |RS485_AAD |RS-485 Auto Address Detection Operation Mode (AAD)
 * |        |          |0 = RS-485 Auto Address Detection Operation mode (AAD) Disabled.
 * |        |          |1 = RS-485 Auto Address Detection Operation mode (AAD) Enabled.
 * |        |          |Note: It cannot be active with RS-485_NMM operation mode.
 * |[10]    |RS485_AUD |RS-485 Auto Direction Mode (AUD)
 * |        |          |0 = RS-485 Auto Direction Operation mode (AUO) Disabled.
 * |        |          |1 = RS-485 Auto Direction Operation mode (AUO) Enabled.
 * |        |          |Note: It can be active with RS-485_AAD or RS-485_NMM operation mode.
 * |[15]    |RS485_ADD_EN|RS-485 Address Detection Enable
 * |        |          |This bit is used to enable RS-485 Address Detection mode.
 * |        |          |0 = Address detection mode Disabled.
 * |        |          |1 = Address detection mode Enabled.
 * |        |          |Note: This bit is used for RS-485 any operation mode.
 * |[31:24] |ADDR_MATCH|Address Match Value Register
 * |        |          |This field contains the RS-485 address match values.
 * |        |          |Note: This field is used for RS-485 auto address detection mode.
 * @var UART_T::FUN_SEL
 * Offset: 0x30  UART Function Select Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |FUN_SEL   |Function Select Enable
 * |        |          |00 = UART function Enabled.
 * |        |          |01 = LIN function Enabled.
 * |        |          |10 = IrDA function Enabled.
 * |        |          |11 = RS-485 function Enabled.
 * @var UART_T::LIN_CTL
 * Offset: 0x34  UART LIN Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |LINS_EN   |LIN Slave Mode Enable Control
 * |        |          |0 = LIN slave mode Disabled.
 * |        |          |1 = LIN slave mode Enabled.
 * |[1]     |LINS_HDET_EN|LIN Slave Header Detection Enable Control
 * |        |          |0 = LIN slave header detection Disabled.
 * |        |          |1 = LIN slave header detection Enabled.
 * |        |          |Note1: This bit only valid when in LIN slave mode (LINS_EN (UA_LIN_CTL[0]) = 1).
 * |        |          |Note2: In LIN function mode, when detect header field (break + sync + frame ID), LINS_HDET_F (UA_LIN_SR [0]) flag will be asserted. If the LIN_IEN (UA_IER[8]) = 1, an interrupt will be generated.
 * |[2]     |LINS_ARS_EN|LIN Slave Automatic Resynchronization Mode Enable Control
 * |        |          |0 = LIN automatic resynchronization Disabled.
 * |        |          |1 = LIN automatic resynchronization Enabled.
 * |        |          |Note1: This bit only valid when in LIN slave mode (LINS_EN (UA_LIN_CTL[0]) = 1).
 * |        |          |Note2: When operation in Automatic Resynchronization mode, the baud rate setting must be mode2 (BAUD_M1 (UA_BAUD [29]) and BAUD_M0 (UA_BAUD [28]) must be 1). 
 * |        |          |(Slave mode with automatic resynchronization).
 * |[3]     |LINS_DUM_EN|LIN Slave Divider Update Method Enable Control
 * |        |          |0 = UA_BAUD updated is written by software (if no automatic resynchronization update occurs at the same time).
 * |        |          |1 = UA_BAUD is updated at the next received character. User must set the bit before checksum reception.
 * |        |          |Note1: This bit only valid when in LIN slave mode (LINS_EN (UA_LIN_CTL[0]) = 1).
 * |        |          |Note2: This bit used for LIN Slave Automatic Resynchronization mode.
 * |        |          |(for Non-Automatic Resynchronization mode, this bit should be kept cleared).
 * |        |          |(Slave mode with automatic resynchronization).
 * |[4]     |LIN_MUTE_EN|LIN Mute Mode Enable Control
 * |        |          |0 = LIN mute mode Disabled.
 * |        |          |1 = LIN mute mode Enabled.
 * |        |          |Note: The exit from mute mode condition and each control and interactions of this field are explained in (LIN slave mode).
 * |[8]     |LIN_SHD   |LIN TX Send Header Enable Control
 * |        |          |The LIN TX header can be "break field" or "break and sync field" or "break, sync and frame ID field",  it is depend on setting LIN_HEAD_SEL (UA_LIN_CTL[23:22]).
 * |        |          |0 = Send LIN TX header Disabled.
 * |        |          |1 = Send LIN TX header Enabled.
 * |        |          |Note1: These registers are shadow registers of LIN_SHD (UA_ALT_CSR [7]); user can read/write it by setting LIN_SHD (UA_ALT_CSR [7]) or LIN_SHD (UA_LIN_CTL [8]).
 * |        |          |Note2: When transmitter header field (it may be "break" or "break + sync" or "break + sync + frame ID"  selected by LIN_HEAD_SEL (UA_LIN_CTL[23:22]) field) transfer operation finished, this bit will be cleared automatically.
 * |[9]     |LIN_IDPEN |LIN ID Parity Enable Control
 * |        |          |0 = LIN frame ID parity Disabled.
 * |        |          |1 = LIN frame ID parity Enabled.
 * |        |          |Note1: This bit can be used for LIN master to sending header field (LIN_SHD (UA_LIN_CTL[8])) = 1 and LIN_HEAD_SEL (UA_LIN_CTL[23:22]) = 10) or be used for enable LIN slave received frame ID parity checked.
 * |        |          |Note2: This bit is only use when the operation header transmitter is in LIN_HEAD_SEL (UA_LIN_CTL[23:22]) = 10.
 * |[10]    |LIN_BKDET_EN|LIN Break Detection Enable Control
 * |        |          |When detect consecutive dominant greater than 11 bits, and are followed by a delimiter character, the LIN_BKDET_F (UA_LIN_SR[8]) flag is set in UA_LIN_SR register at the end of break field.
 * |        |          |If the LIN_IEN (UA_IER [8])=1, an interrupt will be generated.
 * |        |          |0 = LIN break detection Disabled.
 * |        |          |1 = LIN break detection Enabled.
 * |[11]    |LIN_RX_DIS|LIN Receiver Disable Control
 * |        |          |If the receiver is enabled (LIN_RX_DIS (UA_LIN_CTL[11] ) = 0), all received byte data will be accepted and stored in the RX-FIFO, and if the receiver is disabled (LIN_RX_DIS (UA_LIN_CTL[11] = 1), all received byte data will be ignore.
 * |        |          |0 = LIN receiver Enabled.
 * |        |          |1 = LIN receiver Disabled.
 * |        |          |Note: This bit is only valid when operating in LIN function mode (FUN_SEL (UA_FUN_SEL[1:0]) = 01).
 * |[12]    |BIT_ERR_EN|Bit Error Detect Enable Control
 * |        |          |0 = Bit error detection function Disabled.
 * |        |          |1 = Bit error detection Enabled.
 * |        |          |Note: In LIN function mode, when occur bit error, the BIT_ERR_F (UA_LIN_SR[9]) flag will be asserted. If the LIN_IEN (UA_IER[8]) = 1, an interrupt will be generated.
 * |[19:16] |LIN_BKFL  |LIN Break Field Length
 * |        |          |This field indicates a 4-bit LIN TX break field count.
 * |        |          |Note1: These registers are shadow registers of LIN_BKFL, User can read/write it by setting LIN_BKFL (UA_ALT_CSR[3:0]) or LIN_BKFL (UA_LIN_CTL[19:16].
 * |        |          |Note2: This break field length is LIN_BKFL + 1.
 * |        |          |Note3: According to LIN spec, the reset value is 12 (break field length = 13).
 * |[21:20] |LIN_BS_LEN|LIN Break/Sync Delimiter Length
 * |        |          |00 = The LIN break/sync delimiter length is 1 bit time.
 * |        |          |10 = The LIN break/sync delimiter length is 2 bit time.
 * |        |          |10 = The LIN break/sync delimiter length is 3 bit time.
 * |        |          |11 = The LIN break/sync delimiter length is 4 bit time.
 * |        |          |Note: This bit used for LIN master to sending header field.
 * |[23:22] |LIN_HEAD_SEL|LIN Header Select
 * |        |          |00 = The LIN header includes "break field".
 * |        |          |01 = The LIN header includes "break field" and "sync field".
 * |        |          |10 = The LIN header includes "break field", "sync field" and "frame ID field".
 * |        |          |11 = Reserved.
 * |        |          |Note: This bit is used to master mode for LIN to send header field (LIN_SHD (UA_LIN_CTL [8]) = 1) or used to slave to indicates exit from mute mode condition (LIN_MUTE_EN (UA_LIN_CTL[4] = 1).
 * |[31:24] |LIN_PID   |LIN PID Register
 * |        |          |This field contains the LIN frame ID value when in LIN function mode, the frame ID parity can be generated by software or hardware depends on LIN_IDPEN (UA_LIN_CTL[9]) = 1.
 * |        |          |If the parity generated by hardware, user fill ID0~ID5, (LIN_PID [29:24] )hardware will calculate P0 (LIN_PID[30]) and P1 (LIN_PID[31]), otherwise user must filled frame ID and parity in this field.
 * |        |          |Note1: User can fill any 8-bit value to this field and the bit 24 indicates ID0 (LSB first).
 * |        |          |Note2: This field can be used for LIN master mode or slave mode.
 * @var UART_T::LIN_SR
 * Offset: 0x38  UART LIN Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |LINS_HDET_F|LIN Slave Header Detection Flag
 * |        |          |This bit is set by hardware when a LIN header is detected in LIN slave mode and be cleared by writing 1 to it.
 * |        |          |0 = LIN header not detected.
 * |        |          |1 = LIN header detected (break + sync + frame ID).
 * |        |          |Note1: This bit is can be cleared by writing 1 to it.
 * |        |          |Note2: This bit is only valid when in LIN slave mode (LINS_EN (UA_LIN_CTL [0]) = 1) and enable LIN slave header detection function (LINS_HDET_EN (UA_LIN_CTL [1])).
 * |        |          |Note3: When enable ID parity check LIN_IDPEN (UA_LIN_CTL [9]), if hardware detect complete header ("break + sync + frame ID"), the LINS_HEDT_F will be set whether the frame ID correct or not.
 * |[1]     |LINS_HERR_F|LIN Slave Header Error Flag
 * |        |          |This bit is set by hardware when a LIN header error is detected in LIN slave mode and be cleared by writing 1 to it.
 * |        |          |The header errors include "break delimiter is too short (less than 0.5 bit time)", "frame error in sync field or Identifier field", "sync field data is not 0x55 in Non-Automatic Resynchronization mode", "sync field deviation error with Automatic Resynchronization mode", "sync field measure time-out with Automatic Resynchronization mode" and "LIN header reception time-out".
 * |        |          |0 = LIN header error not detected.
 * |        |          |1 = LIN header error detected.
 * |        |          |Note1: This bit can be cleared by writing 1 to it.
 * |        |          |Note2: This bit is only valid when UART is operated in LIN slave mode (LINS_EN (UA_LIN_CTL [0]) = 1) and enables LIN slave header detection function (LINS_HDET_EN (UA_LIN_CTL [1])).
 * |[2]     |LINS_IDPERR_F|LIN Slave ID Parity Error Flag
 * |        |          |This bit is set by hardware when receipted frame ID parity is not correct.
 * |        |          |0 = No active.
 * |        |          |1 = Receipted frame ID parity is not correct.
 * |        |          |Note1: This bit iscan be cleared by writing "1" to it.
 * |        |          |Note2: This bit is only valid when in LIN slave mode (LINS_EN (UA_LIN_CTL [0])= 1) and enable LIN frame ID parity check function LIN_IDPEN (UA_LIN_CTL [9]).
 * |[3]     |LINS_SYNC_F|LIN Slave Sync Field
 * |        |          |This bit indicates that the LIN sync field is being analyzed in Automatic Resynchronization mode.
 * |        |          |When the receiver header have some error been detect, user must reset the internal circuit to re-search new frame header by writing 1 to this bit.
 * |        |          |0 = The current character is not at LIN sync state.
 * |        |          |1 = The current character is at LIN sync state.
 * |        |          |Note1: This bit is only valid when in LIN Slave mode (LINS_EN(UA_LIN_CTL[0]) = 1).
 * |        |          |Note2: This bitcan be cleared by writing 1 to it.
 * |        |          |Note3: When writing 1 to it, hardware will reload the initial baud rate and re-search a new frame header.
 * |[8]     |LIN_BKDET_F|LIN Break Detection Flag
 * |        |          |This bit is set by hardware when a break is detected and be cleared by writing 1 to it through software.
 * |        |          |0 = LIN break not detected.
 * |        |          |1 = LIN break detected.
 * |        |          |Note1: This bitcan be cleared by writing 1 to it.
 * |        |          |Note2: This bit is only valid when LIN break detection function is enabled (LIN_BKDET_EN (UA_LIN_CTL[10]) =1).
 * |[9]     |BIT_ERR_F |Bit Error Detect Status Flag
 * |        |          |At TX transfer state, hardware will monitoring the bus state, if the input pin (SIN) state not equals to the output pin (SOUT) state, BIT_ERR_F (UA_LIN_SR[9]) will be set.
 * |        |          |When occur bit error, if the LIN_IEN (UA_IER[8]) = 1, an interrupt will be generated.
 * |        |          |Note1: This bit iscan be cleared by writing 1 to it.
 * |        |          |Note2: This bit is only valid when enable bit error detection function (BIT_ERR_EN (UA_LIN_CTL [12]) = 1).
 */

    union
    {
        __IO uint32_t DATA;          /* Offset: 0x00  UART Data Register                                                 */
        __IO uint32_t THR;           /* Offset: 0x00  UART Transmit Holding Register                                     */
        __IO uint32_t RBR;           /* Offset: 0x00  UART Receive Buffer Register                                       */
    };
    __IO uint32_t IER;           /* Offset: 0x04  UART Interrupt Enable Register                                     */
    __IO uint32_t FCR;           /* Offset: 0x08  UART FIFO Control Register                                         */
    __IO uint32_t LCR;           /* Offset: 0x0C  UART Line Control Register                                         */
    __IO uint32_t MCR;           /* Offset: 0x10  UART Modem Control Register                                        */
    __IO uint32_t MSR;           /* Offset: 0x14  UART Modem Status Register                                         */
    __IO uint32_t FSR;           /* Offset: 0x18  UART FIFO Status Register                                          */
    __IO uint32_t ISR;           /* Offset: 0x1C  UART Interrupt Status Register                                     */
    __IO uint32_t TOR;           /* Offset: 0x20  UART Time-out Register                                             */
    __IO uint32_t BAUD;          /* Offset: 0x24  UART Baud Rate Divisor Register                                    */
    __IO uint32_t IRCR;          /* Offset: 0x28  UART IrDA Control Register                                         */
    __IO uint32_t ALT_CSR;       /* Offset: 0x2C  UART Alternate Control/Status Register                             */
    __IO uint32_t FUN_SEL;       /* Offset: 0x30  UART Function Select Register                                      */
    __IO uint32_t LIN_CTL;       /* Offset: 0x34  UART LIN Control Register                                          */
    __IO uint32_t LIN_SR;        /* Offset: 0x38  UART LIN Status Register                                           */
    

} UART_T;




/**
    @addtogroup UART_CONST UART Bit Field Definition
    Constant Definitions for UART Controller
@{ */

/* UART THR Bit Field Definitions */
#define UART_THR_THR_Pos         0                                          /*!< UART_T::THR: THR Position  */
#define UART_THR_THR_Msk        (0xFul << UART_THR_THR_Pos)                 /*!< UART_T::THR: THR Mask      */

/* UART RBR Bit Field Definitions */
#define UART_RBR_RBR_Pos         0                                          /*!< UART_T::RBR: RBR Position  */
#define UART_RBR_RBR_Msk        (0xFul << UART_RBR_RBR_Pos)                 /*!< UART_T::RBR: RBR Mask      */

/* UART IER Bit Field Definitions */
#define UART_IER_DMA_RX_EN_Pos      15                                      /*!< UART_T::IER: RX DMA Enable Position  */
#define UART_IER_DMA_RX_EN_Msk      (1ul << UART_IER_DMA_RX_EN_Pos)         /*!< UART_T::IER: RX DMA Enable Mask      */

#define UART_IER_DMA_TX_EN_Pos      14                                      /*!< UART_T::IER: TX DMA Enable Position  */
#define UART_IER_DMA_TX_EN_Msk      (1ul << UART_IER_DMA_TX_EN_Pos)         /*!< UART_T::IER: TX DMA Enable Mask      */

#define UART_IER_AUTO_CTS_EN_Pos    13                                      /*!< UART_T::IER: AUTO_CTS_EN Position       */
#define UART_IER_AUTO_CTS_EN_Msk    (1ul << UART_IER_AUTO_CTS_EN_Pos)       /*!< UART_T::IER: AUTO_CTS_EN Mask           */
 
#define UART_IER_AUTO_RTS_EN_Pos    12                                      /*!< UART_T::IER: AUTO_RTS_EN Position       */
#define UART_IER_AUTO_RTS_EN_Msk    (1ul << UART_IER_AUTO_RTS_EN_Pos)       /*!< UART_T::IER: AUTO_RTS_EN Mask           */

#define UART_IER_TIME_OUT_EN_Pos    11                                      /*!< UART_T::IER: TIME_OUT_EN Position       */
#define UART_IER_TIME_OUT_EN_Msk    (1ul << UART_IER_TIME_OUT_EN_Pos)       /*!< UART_T::IER: TIME_OUT_EN Mask           */

#define UART_IER_LIN_IEN_Pos        8                                       /*!< UART_T::IER: LIN_IEN Position           */
#define UART_IER_LIN_IEN_Msk        (1ul << UART_IER_LIN_IEN_Pos)           /*!< UART_T::IER: LIN_IEN Mask               */

#define UART_IER_WAKE_EN_Pos        6                                       /*!< UART_T::IER: WAKE_EN Position           */
#define UART_IER_WAKE_EN_Msk        (1ul << UART_IER_WAKE_EN_Pos)           /*!< UART_T::IER: WAKE_EN Mask               */

#define UART_IER_BUF_ERR_IEN_Pos    5                                       /*!< UART_T::IER: BUF_ERR_IEN Position       */
#define UART_IER_BUF_ERR_IEN_Msk    (1ul << UART_IER_BUF_ERR_IEN_Pos)       /*!< UART_T::IER: BUF_ERR_IEN Mask           */

#define UART_IER_TOUT_IEN_Pos        4                                      /*!< UART_T::IER: TOUT_IEN Position           */
#define UART_IER_TOUT_IEN_Msk        (1ul << UART_IER_TOUT_IEN_Pos)         /*!< UART_T::IER: TOUT_IEN Mask               */

#define UART_IER_MODEM_IEN_Pos      3                                       /*!< UART_T::IER: MODEM_IEN Position         */
#define UART_IER_MODEM_IEN_Msk      (1ul << UART_IER_MODEM_IEN_Pos)         /*!< UART_T::IER: MODEM_IEN Mask             */

#define UART_IER_RLS_IEN_Pos        2                                       /*!< UART_T::IER: RLS_IEN Position           */
#define UART_IER_RLS_IEN_Msk        (1ul << UART_IER_RLS_IEN_Pos)           /*!< UART_T::IER: RLS_IEN Mask               */

#define UART_IER_THRE_IEN_Pos       1                                       /*!< UART_T::IER: THRE_IEN Position          */
#define UART_IER_THRE_IEN_Msk       (1ul << UART_IER_THRE_IEN_Pos)          /*!< UART_T::IER: THRE_IEN Mask              */

#define UART_IER_RDA_IEN_Pos        0                                       /*!< UART_T::IER: RDA_IEN Position           */
#define UART_IER_RDA_IEN_Msk        (1ul << UART_IER_RDA_IEN_Pos)           /*!< UART_T::IER: RDA_IEN Mask               */

/* UART FCR Bit Field Definitions */
#define UART_FCR_RTS_TRI_LEV_Pos    16                                      /*!< UART_T::FCR: RTS_TRI_LEV Position       */
#define UART_FCR_RTS_TRI_LEV_Msk    (0xFul << UART_FCR_RTS_TRI_LEV_Pos)     /*!< UART_T::FCR: RTS_TRI_LEV Mask           */

#define UART_FCR_RX_DIS_Pos         8                                       /*!< UART_T::FCR: RX_DIS Position            */
#define UART_FCR_RX_DIS_Msk         (1ul << UART_FCR_RX_DIS_Pos)            /*!< UART_T::FCR: RX_DIS Mask                */

#define UART_FCR_RFITL_Pos          4                                       /*!< UART_T::FCR: RFITL Position             */
#define UART_FCR_RFITL_Msk          (0xFul << UART_FCR_RFITL_Pos)           /*!< UART_T::FCR: RFITL Mask                 */

#define UART_FCR_TFR_Pos            2                                       /*!< UART_T::FCR: TFR Position               */
#define UART_FCR_TFR_Msk            (1ul << UART_FCR_TFR_Pos)               /*!< UART_T::FCR: TFR Mask                   */

#define UART_FCR_RFR_Pos            1                                       /*!< UART_T::FCR: RFR Position               */
#define UART_FCR_RFR_Msk            (1ul << UART_FCR_RFR_Pos)               /*!< UART_T::FCR: RFR Mask                   */

/* UART LCR Bit Field Definitions */
#define UART_LCR_BCB_Pos            6                                       /*!< UART_T::LCR: BCB Position               */
#define UART_LCR_BCB_Msk            (1ul << UART_LCR_BCB_Pos)               /*!< UART_T::LCR: BCB Mask                   */

#define UART_LCR_SPE_Pos            5                                       /*!< UART_T::LCR: SPE Position               */
#define UART_LCR_SPE_Msk            (1ul << UART_LCR_SPE_Pos)               /*!< UART_T::LCR: SPE Mask                   */

#define UART_LCR_EPE_Pos            4                                       /*!< UART_T::LCR: EPE Position               */
#define UART_LCR_EPE_Msk            (1ul << UART_LCR_EPE_Pos)               /*!< UART_T::LCR: EPE Mask                   */

#define UART_LCR_PBE_Pos            3                                       /*!< UART_T::LCR: PBE Position               */
#define UART_LCR_PBE_Msk            (1ul << UART_LCR_PBE_Pos)               /*!< UART_T::LCR: PBE Mask                   */

#define UART_LCR_NSB_Pos            2                                       /*!< UART_T::LCR: NSB Position               */
#define UART_LCR_NSB_Msk            (1ul << UART_LCR_NSB_Pos)               /*!< UART_T::LCR: NSB Mask                   */

#define UART_LCR_WLS_Pos            0                                       /*!< UART_T::LCR: WLS Position               */
#define UART_LCR_WLS_Msk            (0x3ul << UART_LCR_WLS_Pos)             /*!< UART_T::LCR: WLS Mask                   */

/* UART MCR Bit Field Definitions */
#define UART_MCR_RTS_ST_Pos         13                                      /*!< UART_T::MCR: RTS_ST Position            */
#define UART_MCR_RTS_ST_Msk         (1ul << UART_MCR_RTS_ST_Pos)            /*!< UART_T::MCR: RTS_ST Mask                */

#define UART_MCR_LEV_RTS_Pos        9                                       /*!< UART_T::MCR: LEV_RTS Position           */
#define UART_MCR_LEV_RTS_Msk        (1ul << UART_MCR_LEV_RTS_Pos)           /*!< UART_T::MCR: LEV_RTS Mask               */

#define UART_MCR_RTS_Pos            1                                       /*!< UART_T::MCR: RTS Position               */
#define UART_MCR_RTS_Msk            (1ul << UART_MCR_RTS_Pos)               /*!< UART_T::MCR: RTS Mask                   */

/* UART MSR Bit Field Definitions */
#define UART_MSR_LEV_CTS_Pos        8                                       /*!< UART_T::MSR: LEV_CTS Position           */
#define UART_MSR_LEV_CTS_Msk        (1ul << UART_MSR_LEV_CTS_Pos)           /*!< UART_T::MSR: LEV_CTS Mask               */

#define UART_MSR_CTS_ST_Pos         4                                       /*!< UART_T::MSR: CTS_ST Position            */
#define UART_MSR_CTS_ST_Msk         (1ul << UART_MSR_CTS_ST_Pos)            /*!< UART_T::MSR: CTS_ST Mask                */

#define UART_MSR_DCTSF_Pos          0                                       /*!< UART_T::MSR: DCTST Position             */
#define UART_MSR_DCTSF_Msk          (1ul << UART_MSR_DCTSF_Pos)             /*!< UART_T::MSR: DCTST Mask                 */


/* UART FSR Bit Field Definitions */
#define UART_FSR_TE_FLAG_Pos        28                                      /*!< UART_T::FSR: TE_FLAG Position           */
#define UART_FSR_TE_FLAG_Msk        (1ul << UART_FSR_TE_FLAG_Pos)           /*!< UART_T::FSR: TE_FLAG Mask               */

#define UART_FSR_TX_OVER_IF_Pos     24                                      /*!< UART_T::FSR: TX_OVER_IF Position        */
#define UART_FSR_TX_OVER_IF_Msk     (1ul << UART_FSR_TX_OVER_IF_Pos)        /*!< UART_T::FSR: TX_OVER_IF Mask            */

#define UART_FSR_TX_FULL_Pos        23                                      /*!< UART_T::FSR: TX_FULL Position           */
#define UART_FSR_TX_FULL_Msk        (1ul << UART_FSR_TX_FULL_Pos)           /*!< UART_T::FSR: TX_FULL Mask               */

#define UART_FSR_TX_EMPTY_Pos       22                                      /*!< UART_T::FSR: TX_EMPTY Position          */
#define UART_FSR_TX_EMPTY_Msk       (1ul << UART_FSR_TX_EMPTY_Pos)          /*!< UART_T::FSR: TX_EMPTY Mask              */

#define UART_FSR_TX_POINTER_Pos     16                                      /*!< UART_T::FSR: TX_POINTER Position        */
#define UART_FSR_TX_POINTER_Msk     (0x3Ful << UART_FSR_TX_POINTER_Pos)     /*!< UART_T::FSR: TX_POINTER Mask            */

#define UART_FSR_RX_FULL_Pos        15                                      /*!< UART_T::FSR: RX_FULL Position           */
#define UART_FSR_RX_FULL_Msk        (1ul << UART_FSR_RX_FULL_Pos)           /*!< UART_T::FSR: RX_FULL Mask               */

#define UART_FSR_RX_EMPTY_Pos       14                                      /*!< UART_T::FSR: RX_EMPTY Position          */
#define UART_FSR_RX_EMPTY_Msk       (1ul << UART_FSR_RX_EMPTY_Pos)          /*!< UART_T::FSR: RX_EMPTY Mask              */

#define UART_FSR_RX_POINTER_Pos     8                                       /*!< UART_T::FSR: RX_POINTERS Position       */
#define UART_FSR_RX_POINTER_Msk     (0x3Ful << UART_FSR_RX_POINTER_Pos)     /*!< UART_T::FSR: RX_POINTER Mask            */

#define UART_FSR_BIF_Pos            6                                       /*!< UART_T::FSR: BIF Position               */
#define UART_FSR_BIF_Msk            (1ul << UART_FSR_BIF_Pos)               /*!< UART_T::FSR: BIF Mask                   */

#define UART_FSR_FEF_Pos            5                                       /*!< UART_T::FSR: FEF Position               */
#define UART_FSR_FEF_Msk            (1ul << UART_FSR_FEF_Pos)               /*!< UART_T::FSR: FEF Mask                   */

#define UART_FSR_PEF_Pos            4                                       /*!< UART_T::FSR: PEF Position               */
#define UART_FSR_PEF_Msk            (1ul << UART_FSR_PEF_Pos)               /*!< UART_T::FSR: PEF Mask                   */

#define UART_FSR_RS485_ADD_DETF_Pos 3                                       /*!< UART_T::FSR: RS485_ADD_DETF Position    */
#define UART_FSR_RS485_ADD_DETF_Msk (1ul << UART_FSR_RS485_ADD_DETF_Pos)    /*!< UART_T::FSR: RS485_ADD_DETF Mask        */

#define UART_FSR_RX_OVER_IF_Pos     0                                       /*!< UART_T::FSR: RX_OVER_IF Position        */
#define UART_FSR_RX_OVER_IF_Msk     (1ul << UART_FSR_RX_OVER_IF_Pos)        /*!< UART_T::FSR: RX_OVER_IF Mask            */

/* UART ISR Bit Field Definitions */
#define UART_ISR_HW_BUF_ERR_INT_Pos 29                                      /*!< UART_T::ISR: HW BUF_ERR_INT Position    */
#define UART_ISR_HW_BUF_ERR_INT_Msk (1ul << UART_ISR_HW_BUF_ERR_INT_Pos)    /*!< UART_T::ISR: HW BUF_ERR_INT Mask        */

#define UART_ISR_HW_TOUT_INT_Pos    28                                      /*!< UART_T::ISR: HW TOUT_INT Position       */
#define UART_ISR_HW_TOUT_INT_Msk    (1ul << UART_ISR_HW_TOUT_INT_Pos)       /*!< UART_T::ISR: HW TOUT_INT Mask           */

#define UART_ISR_HW_MODEM_INT_Pos   27                                      /*!< UART_T::ISR: HW MODEM_INT Position      */
#define UART_ISR_HW_MODEM_INT_Msk   (1ul << UART_ISR_HW_MODEM_INT_Pos)      /*!< UART_T::ISR: HW MODEM_INT Mask          */

#define UART_ISR_HW_RLS_INT_Pos     26                                      /*!< UART_T::ISR: HW RLS_INT Position        */
#define UART_ISR_HW_RLS_INT_Msk     (1ul << UART_ISR_HW_RLS_INT_Pos)        /*!< UART_T::ISR: HW RLS_INT Position        */

#define UART_ISR_HW_BUF_ERR_IF_Pos  21                                      /*!< UART_T::ISR: HW BUF_ERR_IF Position     */
#define UART_ISR_HW_BUF_ERR_IF_Msk  (1ul << UART_ISR_HW_BUF_ERR_IF_Pos)     /*!< UART_T::ISR: HW BUF_ERR_IF Mask         */

#define UART_ISR_HW_TOUT_IF_Pos     20                                      /*!< UART_T::ISR: HW TOUT_IF Position        */
#define UART_ISR_HW_TOUT_IF_Msk     (1ul << UART_ISR_HW_TOUT_IF_Pos)        /*!< UART_T::ISR: HW TOUT_IF Mask            */

#define UART_ISR_HW_MODEM_IF_Pos    19                                      /*!< UART_T::ISR: HW MODEM_IF Position       */
#define UART_ISR_HW_MODEM_IF_Msk    (1ul << UART_ISR_HW_MODEM_IF_Pos)       /*!< UART_T::ISR: HW MODEM_IF Mask           */

#define UART_ISR_HW_RLS_IF_Pos      18                                      /*!< UART_T::ISR: HW RLS_IF Position         */
#define UART_ISR_HW_RLS_IF_Msk      (1ul << UART_ISR_HW_RLS_IF_Pos)         /*!< UART_T::ISR: HW RLS_IF Mark             */

#define UART_ISR_LIN_INT_Pos        15                                      /*!< UART_T::ISR: LIN_INT Position           */
#define UART_ISR_LIN_INT_Msk        (1ul << UART_ISR_LIN_INT_Pos)           /*!< UART_T::ISR: LIN_INT Mask               */

#define UART_ISR_BUF_ERR_INT_Pos    13                                      /*!< UART_T::ISR: BUF_ERR_INT Position       */
#define UART_ISR_BUF_ERR_INT_Msk    (1ul << UART_ISR_BUF_ERR_INT_Pos)       /*!< UART_T::ISR: BUF_ERR_INT Mask           */

#define UART_ISR_TOUT_INT_Pos       12                                      /*!< UART_T::ISR: TOUT_INT Position          */
#define UART_ISR_TOUT_INT_Msk       (1ul << UART_ISR_TOUT_INT_Pos)          /*!< UART_T::ISR: TOUT_INT Mask              */

#define UART_ISR_MODEM_INT_Pos      11                                      /*!< UART_T::ISR: MODEM_INT Position         */
#define UART_ISR_MODEM_INT_Msk      (1ul << UART_ISR_MODEM_INT_Pos)         /*!< UART_T::ISR: MODEM_INT Mask             */

#define UART_ISR_RLS_INT_Pos        10                                      /*!< UART_T::ISR: RLS_INT Position           */
#define UART_ISR_RLS_INT_Msk        (1ul << UART_ISR_RLS_INT_Pos)           /*!< UART_T::ISR: RLS_INT Mask               */

#define UART_ISR_THRE_INT_Pos       9                                       /*!< UART_T::ISR: THRE_INT Position          */
#define UART_ISR_THRE_INT_Msk       (1ul << UART_ISR_THRE_INT_Pos)          /*!< UART_T::ISR: THRE_INT Mask              */

#define UART_ISR_RDA_INT_Pos        8                                       /*!< UART_T::ISR: RDA_INT Position           */
#define UART_ISR_RDA_INT_Msk        (1ul << UART_ISR_RDA_INT_Pos)           /*!< UART_T::ISR: RDA_INT Mask               */

#define UART_ISR_LIN_IF_Pos         7                                       /*!< UART_T::ISR: LIN RX_IF Position         */
#define UART_ISR_LIN_IF_Msk         (1ul << UART_ISR_LIN_IF_Pos)            /*!< UART_T::ISR: LIN RX_IF Mask             */

#define UART_ISR_BUF_ERR_IF_Pos     5                                       /*!< UART_T::ISR: BUF_ERR_IF Position        */
#define UART_ISR_BUF_ERR_IF_Msk     (1ul << UART_ISR_BUF_ERR_IF_Pos)        /*!< UART_T::ISR: BUF_ERR_IF Mask            */

#define UART_ISR_TOUT_IF_Pos        4                                       /*!< UART_T::ISR: TOUT_IF Position           */
#define UART_ISR_TOUT_IF_Msk        (1ul << UART_ISR_TOUT_IF_Pos)           /*!< UART_T::ISR: TOUT_IF Mask               */

#define UART_ISR_MODEM_IF_Pos       3                                       /*!< UART_T::ISR: MODEM_IF Position          */
#define UART_ISR_MODEM_IF_Msk       (1ul << UART_ISR_MODEM_IF_Pos)          /*!< UART_T::ISR: MODEM_IF Mask              */

#define UART_ISR_RLS_IF_Pos         2                                       /*!< UART_T::ISR: RLS_IF Position            */
#define UART_ISR_RLS_IF_Msk         (1ul << UART_ISR_RLS_IF_Pos)            /*!< UART_T::ISR: RLS_IF Mask                */

#define UART_ISR_THRE_IF_Pos        1                                       /*!< UART_T::ISR: THRE_IF Position           */
#define UART_ISR_THRE_IF_Msk        (1ul << UART_ISR_THRE_IF_Pos)           /*!< UART_T::ISR: THRE_IF Mask               */

#define UART_ISR_RDA_IF_Pos         0                                       /*!< UART_T::ISR: RDA_IF Position            */
#define UART_ISR_RDA_IF_Msk         (1ul << UART_ISR_RDA_IF_Pos)            /*!< UART_T::ISR: RDA_IF Mask                */


/* UART TOR Bit Field Definitions */
#define UART_TOR_DLY_Pos           8                                        /*!< UART_T::TOR: DLY Position               */
#define UART_TOR_DLY_Msk           (0xFFul << UART_TOR_DLY_Pos)             /*!< UART_T::TOR: DLY Mask                   */

#define UART_TOR_TOIC_Pos          0                                        /*!< UART_T::TOR: TOIC Position              */
#define UART_TOR_TOIC_Msk          (0xFFul << UART_TOR_TOIC_Pos)

/* UART BAUD Bit Field Definitions */
#define UART_BAUD_DIV_X_EN_Pos    29                                        /*!< UART_T::BAUD: DIV_X_EN Position         */
#define UART_BAUD_DIV_X_EN_Msk    (1ul << UART_BAUD_DIV_X_EN_Pos)           /*!< UART_T::BAUD: DIV_X_EN Mask             */
                                                                                     
#define UART_BAUD_DIV_X_ONE_Pos   28                                        /*!< UART_T::BAUD: DIV_X_ONE Position        */
#define UART_BAUD_DIV_X_ONE_Msk   (1ul << UART_BAUD_DIV_X_ONE_Pos)          /*!< UART_T::BAUD: DIV_X_ONE Mask            */
                                                                                     
#define UART_BAUD_DIVIDER_X_Pos   24                                        /*!< UART_T::BAUD: DIVIDER_X Position        */
#define UART_BAUD_DIVIDER_X_Msk   (0xFul << UART_BAUD_DIVIDER_X_Pos)        /*!< UART_T::BAUD: DIVIDER_X Mask            */
                                                                                     
#define UART_BAUD_BRD_Pos         0                                         /*!< UART_T::BAUD: BRD Position              */
#define UART_BAUD_BRD_Msk         (0xFFFFul << UART_BAUD_BRD_Pos)           /*!< UART_T::BAUD: BRD Mask                  */

/* UART IRCR Bit Field Definitions */
#define UART_IRCR_INV_RX_Pos      6                                         /*!< UART_T::IRCR: INV_RX Position           */
#define UART_IRCR_INV_RX_Msk     (1ul << UART_IRCR_INV_RX_Pos)              /*!< UART_T::IRCR: INV_RX Mask               */

#define UART_IRCR_INV_TX_Pos      5                                         /*!< UART_T::IRCR: INV_TX Position           */
#define UART_IRCR_INV_TX_Msk     (1ul << UART_IRCR_INV_TX_Pos)              /*!< UART_T::IRCR: INV_TX Mask               */

#define UART_IRCR_TX_SELECT_Pos   1                                         /*!< UART_T::IRCR: TX_SELECT Position        */
#define UART_IRCR_TX_SELECT_Msk   (1ul << UART_IRCR_TX_SELECT_Pos)          /*!< UART_T::IRCR: TX_SELECT Mask            */

/* UART ALT_CSR Bit Field Definitions */
#define UART_ALT_CSR_ADDR_MATCH_Pos      24                                      /*!< UART_T::ALT_CSR: ADDR_MATCH Position    */
#define UART_ALT_CSR_ADDR_MATCH_Msk     (0xFFul << UART_ALT_CSR_ADDR_MATCH_Pos)  /*!< UART_T::ALT_CSR: ADDR_MATCH Mask        */

#define UART_ALT_CSR_RS485_ADD_EN_Pos   15                                       /*!< UART_T::ALT_CSR: RS485_ADD_EN Position  */
#define UART_ALT_CSR_RS485_ADD_EN_Msk   (1ul << UART_ALT_CSR_RS485_ADD_EN_Pos)   /*!< UART_T::ALT_CSR: RS485_ADD_EN Mask      */

#define UART_ALT_CSR_RS485_AUD_Pos      10                                       /*!< UART_T::ALT_CSR: RS485_AUD Position     */
#define UART_ALT_CSR_RS485_AUD_Msk      (1ul << UART_ALT_CSR_RS485_AUD_Pos)      /*!< UART_T::ALT_CSR: RS485_AUD Mask         */

#define UART_ALT_CSR_RS485_AAD_Pos      9                                        /*!< UART_T::ALT_CSR: RS485_AAD Position     */
#define UART_ALT_CSR_RS485_AAD_Msk      (1ul << UART_ALT_CSR_RS485_AAD_Pos)      /*!< UART_T::ALT_CSR: RS485_AAD Mask         */

#define UART_ALT_CSR_RS485_NMM_Pos      8                                        /*!< UART_T::ALT_CSR: RS485_NMM Position     */
#define UART_ALT_CSR_RS485_NMM_Msk      (1ul << UART_ALT_CSR_RS485_NMM_Pos)      /*!< UART_T::ALT_CSR: RS485_NMM Mask         */

#define UART_ALT_CSR_LIN_TX_EN_Pos      7                                        /*!< UART_T::ALT_CSR: LIN TX Break Mode Enable Position     */
#define UART_ALT_CSR_LIN_TX_EN_Msk      (1ul << UART_ALT_CSR_LIN_TX_EN_Pos)      /*!< UART_T::ALT_CSR: LIN TX Break Mode Enable Mask         */

#define UART_ALT_CSR_LIN_RX_EN_Pos      6                                        /*!< UART_T::ALT_CSR: LIN RX Enable Position     */
#define UART_ALT_CSR_LIN_RX_EN_Msk      (1ul << UART_ALT_CSR_LIN_RX_EN_Pos)      /*!< UART_T::ALT_CSR: LIN RX Enable Mask         */

#define UART_ALT_CSR_UA_LIN_BKFL_Pos    0                                        /*!< UART_T::ALT_CSR: UART LIN Break Field Length Position     */
#define UART_ALT_CSR_UA_LIN_BKFL_Msk    (0xFul << UART_ALT_CSR_UA_LIN_BKFL_Pos)  /*!< UART_T::ALT_CSR: UART LIN Break Field Length Mask         */

/* UART FUN_SEL Bit Field Definitions */
#define UART_FUN_SEL_FUN_SEL_Pos        0                                        /*!< UART_T::FUN_SEL: FUN_SEL Position       */
#define UART_FUN_SEL_FUN_SEL_Msk       (0x3ul << UART_FUN_SEL_FUN_SEL_Pos)       /*!< UART_T::FUN_SEL: FUN_SEL Mask           */

/* UART LIN_CTL Bit Field Definitions */
#define UART_LIN_CTL_LIN_PID_Pos        24                                        /*!< UART_T::LIN_CTL: LIN_PID Position       */
#define UART_LIN_CTL_LIN_PID_Msk        (0xFFul << UART_LIN_CTL_LIN_PID_Pos)      /*!< UART_T::LIN_CTL: LIN_PID Mask           */

#define UART_LIN_CTL_LIN_HEAD_SEL_Pos   22                                        /*!< UART_T::LIN_CTL: LIN_HEAD_SEL Position       */
#define UART_LIN_CTL_LIN_HEAD_SEL_Msk   (0x3ul << UART_LIN_CTL_LIN_HEAD_SEL_Pos)  /*!< UART_T::LIN_CTL: LIN_HEAD_SEL Mask           */

#define UART_LIN_CTL_LIN_BS_LEN_Pos     20                                        /*!< UART_T::LIN_CTL: LIN_BS_LEN Position       */
#define UART_LIN_CTL_LIN_BS_LEN_Msk     (0x3ul << UART_LIN_CTL_LIN_BS_LEN_Pos)    /*!< UART_T::LIN_CTL: LIN_BS_LEN Mask           */

#define UART_LIN_CTL_LIN_BKFL_Pos       16                                        /*!< UART_T::LIN_CTL: LIN_BKFL Position       */
#define UART_LIN_CTL_LIN_BKFL_Msk       (0xFul << UART_LIN_CTL_LIN_BKFL_Pos)      /*!< UART_T::LIN_CTL: LIN_BKFL Mask           */

#define UART_LIN_CTL_BIT_ERR_EN_Pos     12                                        /*!< UART_T::LIN_CTL: BIT_ERR_EN Position       */
#define UART_LIN_CTL_BIT_ERR_EN_Msk     (1ul << UART_LIN_CTL_BIT_ERR_EN_Pos)      /*!< UART_T::LIN_CTL: BIT_ERR_EN Mask           */

#define UART_LIN_CTL_LIN_RX_DIS_Pos     11                                        /*!< UART_T::LIN_CTL: LIN_RX_DIS Position       */
#define UART_LIN_CTL_LIN_RX_DIS_Msk     (1ul << UART_LIN_CTL_LIN_RX_DIS_Pos)      /*!< UART_T::LIN_CTL: LIN_RX_DIS Mask           */

#define UART_LIN_CTL_LIN_BKDET_EN_Pos   10                                        /*!< UART_T::LIN_CTL: LIN_BKDET_EN Position       */
#define UART_LIN_CTL_LIN_BKDET_EN_Msk   (1ul << UART_LIN_CTL_LIN_BKDET_EN_Pos)    /*!< UART_T::LIN_CTL: LIN_BKDET_EN Mask           */

#define UART_LIN_CTL_LIN_IDPEN_Pos      9                                         /*!< UART_T::LIN_CTL: LIN_IDPEN Position       */
#define UART_LIN_CTL_LIN_IDPEN_Msk      (1ul << UART_LIN_CTL_LIN_IDPEN_Pos)       /*!< UART_T::LIN_CTL: LIN_IDPEN Mask           */

#define UART_LIN_CTL_LIN_SHD_Pos        8                                         /*!< UART_T::LIN_CTL: LIN_SHD Position       */
#define UART_LIN_CTL_LIN_SHD_Msk        (1ul << UART_LIN_CTL_LIN_SHD_Pos)         /*!< UART_T::LIN_CTL: LIN_SHD Mask           */

#define UART_LIN_CTL_LIN_MUTE_EN_Pos    4                                          /*!< UART_T::LIN_CTL: LIN_MUTE_EN Position       */
#define UART_LIN_CTL_LIN_MUTE_EN_Msk    (1ul << UART_LIN_CTL_LIN_MUTE_EN_Pos)      /*!< UART_T::LIN_CTL: LIN_MUTE_EN Mask           */

#define UART_LIN_CTL_LINS_DUM_EN_Pos    3                                          /*!< UART_T::LIN_CTL: LINS_DUM_EN Position       */
#define UART_LIN_CTL_LINS_DUM_EN_Msk    (1ul << UART_LIN_CTL_LINS_DUM_EN_Pos)      /*!< UART_T::LIN_CTL: LINS_DUM_EN Mask           */

#define UART_LIN_CTL_LINS_ARS_EN_Pos    2                                          /*!< UART_T::LIN_CTL: LINS_ARS_EN Position       */
#define UART_LIN_CTL_LINS_ARS_EN_Msk    (1ul << UART_LIN_CTL_LINS_ARS_EN_Pos)      /*!< UART_T::LIN_CTL: LINS_ARS_EN Mask           */

#define UART_LIN_CTL_LINS_HDET_EN_Pos   1                                          /*!< UART_T::LIN_CTL: LINS_HDET_EN Position       */
#define UART_LIN_CTL_LINS_HDET_EN_Msk   (1ul << UART_LIN_CTL_LINS_HDET_EN_Pos)     /*!< UART_T::LIN_CTL: LINS_HDET_EN Mask           */

#define UART_LIN_CTL_LINS_EN_Pos        0                                          /*!< UART_T::LIN_CTL: LINS_EN Position       */
#define UART_LIN_CTL_LINS_EN_Msk        (1ul << UART_LIN_CTL_LINS_EN_Pos)          /*!< UART_T::LIN_CTL: LINS_EN Mask           */

/* UART LIN_SR Bit Field Definitions */
#define UART_LIN_SR_BIT_ERR_F_Pos       9                                           /*!< UART_T::LIN_SR: BIT_ERR_F Position         */
#define UART_LIN_SR_BIT_ERR_F_Msk       (1ul << UART_LIN_SR_BIT_ERR_F_Pos)          /*!< UART_T::LIN_SR: BIT_ERR_F Mask             */

#define UART_LIN_SR_LINS_BKDET_F_Pos    8                                           /*!< UART_T::LIN_SR: LINS_BKDET_F Position      */
#define UART_LIN_SR_LINS_BKDET_F_Msk    (1ul << UART_LIN_SR_LINS_BKDET_F_Pos)       /*!< UART_T::LIN_SR: LINS_BKDET_F Mask          */

#define UART_LIN_SR_LINS_SYNC_F_Pos     3                                           /*!< UART_T::LIN_SR: LINS_SYNC_F Position       */
#define UART_LIN_SR_LINS_SYNC_F_Msk     (1ul << UART_LIN_SR_LINS_SYNC_F_Pos)        /*!< UART_T::LIN_SR: LINS_SYNC_F Mask           */

#define UART_LIN_SR_LINS_IDPERR_F_Pos   2                                           /*!< UART_T::LIN_SR: LINS_IDPERR_F Position     */
#define UART_LIN_SR_LINS_IDPERR_F_Msk   (1ul << UART_LIN_SR_LINS_IDPERR_F_Pos)      /*!< UART_T::LIN_SR: LINS_IDPERR_F Mask         */

#define UART_LIN_SR_LINS_HERR_F_Pos     1                                           /*!< UART_T::LIN_SR: LINS_HERR_F Position       */
#define UART_LIN_SR_LINS_HERR_F_Msk     (1ul << UART_LIN_SR_LINS_HERR_F_Pos)        /*!< UART_T::LIN_SR: LINS_HERR_F Mask           */

#define UART_LIN_SR_LINS_HDET_F_Pos     0                                           /*!< UART_T::LIN_SR: LINS_HDET_F Position       */
#define UART_LIN_SR_LINS_HDET_F_Msk     (1ul << UART_LIN_SR_LINS_HDET_F_Pos)        /*!< UART_T::LIN_SR: LINS_HDET_F Mask           */
/*@}*/ /* end of group UART_CONST */
/*@}*/ /* end of group UART */



/*---------------------- Universal Serial Bus Device Controller -------------------------*/
/**
    @addtogroup USBD Universal Serial Bus Device Controller (USBD)
    Memory Mapped Structure for USBD Controller
@{ */



typedef struct
{


/**
 * @var USBD_EP_T::BUFSEG
 * Offset: 0x20/0x30/0x40/0x50/0x60/0x70  Endpoint 0~5 Buffer Segmentation Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8:3]   |BUFSEG    |Endpoint Buffer Segmentation
 * |        |          |It is used to indicate the offset address for each endpoint with the USB SRAM starting
 * |        |          |address The effective starting address of the endpoint is
 * |        |          |USB_SRAM address + { BUFSEG[8:3], 3'b000}
 * |        |          |Where the USB_SRAM address = USBD_BA+0x100h.
 * |        |          |Refer to the section 5.4.4.7 for the endpoint SRAM structure and its description.
 * @var USBD_EP_T::MXPLD
 * Offset: 0x24/0x34/0x44/0x54/0x64/0x74  Endpoint 0~5 Maximal Payload Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8:0]   |MXPLD     |Maximal Payload
 * |        |          |Define the data length which is transmitted to host (IN token) or the actual data length
 * |        |          |which is received from the host (OUT token).
 * |        |          |It also used to indicate that the endpoint is ready to be transmitted in IN token or
 * |        |          |received in OUT token.
 * |        |          |(1) When the register is written by CPU,
 * |        |          |For IN token, the value of MXPLD is used to define the data length to be transmitted and
 * |        |          |indicate the data buffer is ready.
 * |        |          |For OUT token, it means that the controller is ready to receive data from the host and the
 * |        |          |value of MXPLD is the maximal data length comes from host.
 * |        |          |(2) When the register is read by CPU,
 * |        |          |For IN token, the value of MXPLD is indicated by the data length be transmitted to host
 * |        |          |For OUT token, the value of MXPLD is indicated the actual data length receiving from host.
 * |        |          |Note: Once MXPLD is written, the data packets will be transmitted/received immediately after
 * |        |          |IN/OUT token arrived.
 * @var USBD_EP_T::CFG
 * Offset: 0x28/0x38/0x48/0x58/0x68/0x78  Endpoint 0~5 Configuration Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[3:0]   |EP_NUM    |Endpoint Number
 * |        |          |These bits are used to define the endpoint number of the current endpoint.
 * |[4]     |ISOCH     |Isochronous Endpoint
 * |        |          |This bit is used to set the endpoint as Isochronous endpoint, no handshake.
 * |        |          |0 = No Isochronous endpoint.
 * |        |          |1 = Isochronous endpoint.
 * |[6:5]   |STATE     |Endpoint STATE
 * |        |          |00 = Endpoint is Disabled.
 * |        |          |01 = Out endpoint.
 * |        |          |10 = IN endpoint.
 * |        |          |11 = Undefined.
 * |[7]     |DSQ_SYNC  |Data Sequence Synchronization
 * |        |          |0 = DATA0 PID.
 * |        |          |1 = DATA1 PID.
 * |        |          |Note: It is used to specify the DATA0 or DATA1 PID in the following IN token transaction.
 * |        |          |Hardware will toggle automatically in IN token base on the bit.
 * |[9]     |CSTALL    |Clear STALL Response
 * |        |          |0 = Disable the device to clear the STALL handshake in setup stage.
 * |        |          |1 = Clear the device to response STALL handshake in setup stage.
 * @var USBD_EP_T::CFGP
 * Offset: 0x2C/0x3C/0x4C/0x5C/0x6C/0x7C  Endpoint 0~5 Set Stall and Clear In/Out Ready Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |CLRRDY    |Clear Ready
 * |        |          |When the USB_MXPLD register is set by user, it means that the endpoint is ready to transmit
 * |        |          |or receive data.
 * |        |          |If the user wants to turn off this transaction before the transaction start, users can set
 * |        |          |this bit to 1 to turn it off and it will be cleared to 0 automatically.
 * |        |          |For IN token, write '1' to clear the IN token had ready to transmit the data to USB.
 * |        |          |For OUT token, write '1' to clear the OUT token had ready to receive the data from USB.
 * |        |          |This bit is write 1 only and is always 0 when it is read back.
 * |[1]     |SSTALL    |Set STALL
 * |        |          |0 = Disable the device to response STALL.
 * |        |          |1 = Set the device to respond STALL automatically.
 */

    __IO uint32_t BUFSEG;        /* Offset: 0x20/0x30/0x40/0x50/0x60/0x70  Endpoint 0~5 Buffer Segmentation Register */
    __IO uint32_t MXPLD;         /* Offset: 0x24/0x34/0x44/0x54/0x64/0x74  Endpoint 0~5 Maximal Payload Register     */
    __IO uint32_t CFG;           /* Offset: 0x28/0x38/0x48/0x58/0x68/0x78  Endpoint 0~5 Configuration Register       */
    __IO uint32_t CFGP;          /* Offset: 0x2C/0x3C/0x4C/0x5C/0x6C/0x7C  Endpoint 0~5 Set Stall and Clear In/Out Ready Control Register */

} USBD_EP_T;







typedef struct
{


/**
 * @var USBD_T::INTEN
 * Offset: 0x00  USB Interrupt Enable Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |BUS_IE    |Bus Event Interrupt Enable
 * |        |          |0 = BUS event interrupt Disabled.
 * |        |          |1 = BUS event interrupt Enabled.
 * |[1]     |USB_IE    |USB Event Interrupt Enable
 * |        |          |0 = USB event interrupt Disabled.
 * |        |          |1 = USB event interrupt Enabled.
 * |[2]     |FLDET_IE  |Floating Detection Interrupt Enable
 * |        |          |0 = Floating detection Interrupt Disabled.
 * |        |          |1 = Floating detection Interrupt Enabled.
 * |[3]     |WAKEUP_IE |USB Wake-Up Interrupt Enable
 * |        |          |0 = Wake-up Interrupt Disabled.
 * |        |          |1 = Wake-up Interrupt Enabled.
 * |[8]     |WAKEUP_EN |Wake-Up Function Enable
 * |        |          |0 = USB wake-up function Disabled.
 * |        |          |1 = USB wake-up function Enabled.
 * |[15]    |INNAK_EN  |Active NAK Function And Its Status In IN Token
 * |        |          |0 = When device responds NAK after receiving IN token, IN NAK status will not be
 * |        |          |    updated to USBD_EPSTS register, so that the USB interrupt event will not be asserted.
 * |        |          |1 = IN NAK status will be updated to USBD_EPSTS register and the USB interrupt event
 * |        |          |    will be asserted, when the device responds NAK after receiving IN token.
 * @var USBD_T::INTSTS
 * Offset: 0x04  USB Interrupt Event Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |BUS_STS   |BUS Interrupt Status
 * |        |          |The BUS event means that there is one of the suspense or the resume function in the bus.
 * |        |          |0 = No BUS event occurred.
 * |        |          |1 = Bus event occurred; check USB_ATTR[3:0] to know which kind of bus event was occurred,
 * |        |          |cleared by write 1 to USB_INTSTS[0].
 * |[1]     |USB_STS   |USB Event Interrupt Status
 * |        |          |The USB event includes the SETUP Token, IN Token, OUT ACK, ISO IN, or ISO OUT events in the
 * |        |          |bus.
 * |        |          |0 = No USB event occurred.
 * |        |          |1 = USB event occurred, check EPSTS0~7 to know which kind of USB event occurred.
 * |        |          |Cleared by write 1 to USB_INTSTS[1] or EPEVT0~7 and SETUP (USB_INTSTS[31]).
 * |[2]     |FLDET_STS |Floating Detection Interrupt Status
 * |        |          |0 = There is not attached/detached event in the USB.
 * |        |          |1 = There is attached/detached event in the USB bus and it is cleared by write 1 to
 * |        |          |USB_INTSTS[2].
 * |[3]     |WAKEUP_STS|Wake-Up Interrupt Status
 * |        |          |0 = No Wake-up event occurred.
 * |        |          |1 = Wake-up event occurred, cleared by write 1 to USB_INTSTS[3].
 * |[16]    |EPEVT0    |Endpoint 0's USB Event Status
 * |        |          |0 = No event occurred on endpoint 0.
 * |        |          |1 = USB event occurred on Endpoint 0, check USB_EPSTS[10:8] to know which kind of USB event
 * |        |          |was occurred, cleared by write 1 to USB_INTSTS[16] or USB_INTSTS[1].
 * |[17]    |EPEVT1    |Endpoint 1's USB Event Status
 * |        |          |0 = No event occurred on endpoint 1.
 * |        |          |1 = USB event occurred on Endpoint 1, check USB_EPSTS[13:11] to know which kind of USB event
 * |        |          |was occurred, cleared by write 1 to USB_INTSTS[17] or USB_INTSTS[1].
 * |[18]    |EPEVT2    |Endpoint 2's USB Event Status
 * |        |          |0 = No event occurred on endpoint 2.
 * |        |          |1 = USB event occurred on Endpoint 2, check USB_EPSTS[16:14] to know which kind of USB event
 * |        |          |was occurred, cleared by write 1 to USB_INTSTS[18] or USB_INTSTS[1].
 * |[19]    |EPEVT3    |Endpoint 3's USB Event Status
 * |        |          |0 = No event occurred on endpoint 3.
 * |        |          |1 = USB event occurred on Endpoint 3, check USB_EPSTS[19:17] to know which kind of USB event
 * |        |          |was occurred, cleared by write 1 to USB_INTSTS[19] or USB_INTSTS[1].
 * |[20]    |EPEVT4    |Endpoint 4's USB Event Status
 * |        |          |0 = No event occurred on endpoint 4.
 * |        |          |1 = USB event occurred on Endpoint 4, check USB_EPSTS[22:20] to know which kind of USB event
 * |        |          |was occurred, cleared by write 1 to USB_INTSTS[20] or USB_INTSTS[1].
 * |[21]    |EPEVT5    |Endpoint 5's USB Event Status
 * |        |          |0 = No event occurred on endpoint 5.
 * |        |          |1 = USB event occurred on Endpoint 5, check USB_EPSTS[25:23] to know which kind of USB event
 * |        |          |was occurred, cleared by write 1 to USB_INTSTS[21] or USB_INTSTS[1].
 * |[31]    |SETUP     |Setup Event Status
 * |        |          |0 = No Setup event.
 * |        |          |1 = SETUP event occurred, cleared by write 1 to USB_INTSTS[31].
 * @var USBD_T::FADDR
 * Offset: 0x08  USB Device Function Address Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[6:0]   |FADDR     |USB Device Function Address
 * @var USBD_T::EPSTS
 * Offset: 0x0C  USB Endpoint Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[7]     |OVERRUN   |Overrun
 * |        |          |It indicates that the received data is over the maximum payload number or not.
 * |        |          |0 = No overrun.
 * |        |          |1 = Out Data is more than the Max Payload in MXPLD register or the Setup Data is more than 8
 * |        |          |Bytes.
 * |[10:8]  |EPSTS0    |Endpoint 0 Bus Status
 * |        |          |These bits are used to indicate the current status of this endpoint
 * |        |          |000 = In ACK.
 * |        |          |001 = In NAK.
 * |        |          |010 = Out Packet Data0 ACK.
 * |        |          |110 = Out Packet Data1 ACK.
 * |        |          |011 = Setup ACK.
 * |        |          |111 = Isochronous transfer end.
 * |[13:11] |EPSTS1    |Endpoint 1 Bus Status
 * |        |          |These bits are used to indicate the current status of this endpoint
 * |        |          |000 = In ACK.
 * |        |          |001 = In NAK.
 * |        |          |010 = Out Packet Data0 ACK.
 * |        |          |110 = Out Packet Data1 ACK.
 * |        |          |011 = Setup ACK.
 * |        |          |111 = Isochronous transfer end.
 * |[16:14] |EPSTS2    |Endpoint 2 Bus Status
 * |        |          |These bits are used to indicate the current status of this endpoint
 * |        |          |000 = In ACK.
 * |        |          |001 = In NAK.
 * |        |          |010 = Out Packet Data0 ACK.
 * |        |          |110 = Out Packet Data1 ACK.
 * |        |          |011 = Setup ACK.
 * |        |          |111 = Isochronous transfer end.
 * |[19:17] |EPSTS3    |Endpoint 3 Bus Status
 * |        |          |These bits are used to indicate the current status of this endpoint
 * |        |          |000 = In ACK.
 * |        |          |001 = In NAK.
 * |        |          |010 = Out Packet Data0 ACK.
 * |        |          |110 = Out Packet Data1 ACK.
 * |        |          |011 = Setup ACK.
 * |        |          |111 = Isochronous transfer end.
 * |[22:20] |EPSTS4    |Endpoint 4 Bus Status
 * |        |          |These bits are used to indicate the current status of this endpoint
 * |        |          |000 = In ACK.
 * |        |          |001 = In NAK.
 * |        |          |010 = Out Packet Data0 ACK.
 * |        |          |110 = Out Packet Data1 ACK.
 * |        |          |011 = Setup ACK.
 * |        |          |111 = Isochronous transfer end.
 * |[25:23] |EPSTS5    |Endpoint 5 Bus Status
 * |        |          |These bits are used to indicate the current status of this endpoint
 * |        |          |000 = In ACK.
 * |        |          |001 = In NAK.
 * |        |          |010 = Out Packet Data0 ACK.
 * |        |          |110 = Out Packet Data1 ACK.
 * |        |          |011 = Setup ACK.
 * |        |          |111 = Isochronous transfer end.
 * @var USBD_T::ATTR
 * Offset: 0x10  USB Bus Status and Attribution Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |USBRST    |USB Reset Status
 * |        |          |0 = Bus no reset.
 * |        |          |1 = Bus reset when SE0 (single-ended 0) is presented more than 2.5us.
 * |        |          |Note: This bit is read only.
 * |[1]     |SUSPEND   |Suspend Status
 * |        |          |0 = Bus no suspend.
 * |        |          |1 = Bus idle more than 3ms, either cable is plugged off or host is sleeping.
 * |        |          |Note: This bit is read only.
 * |[2]     |RESUME    |Resume Status
 * |        |          |0 = No bus resume.
 * |        |          |1 = Resume from suspend.
 * |        |          |Note: This bit is read only.
 * |[3]     |TIMEOUT   |Time-Out Status
 * |        |          |0 = No time-out.
 * |        |          |1 = No Bus response more than 18 bits time.
 * |        |          |Note: This bit is read only.
 * |[4]     |PHY_EN    |PHY Transceiver Function Enable
 * |        |          |0 = PHY transceiver function Disabled.
 * |        |          |1 = PHY transceiver function Enabled.
 * |[5]     |RWAKEUP   |Remote Wake-Up
 * |        |          |0 = Release the USB bus from K state.
 * |        |          |1 = Force USB bus to K (USB_D+ low, USB_D- high) state, used for remote wake-up.
 * |[7]     |USB_EN    |USB Controller Enable
 * |        |          |0 = USB Controller Disabled.
 * |        |          |1 = USB Controller Enabled.
 * |[8]     |DPPU_EN   |Pull-Up Resistor On USB_D+ Enable
 * |        |          |0 = Pull-up resistor in USB_D+ pin Disabled.
 * |        |          |1 = Pull-up resistor in USB_D+ pin Enabled.
 * |[9]     |PWRDN     |Power-Down PHY Transceiver, Low Active
 * |        |          |0 = Power-down related circuit of PHY transceiver.
 * |        |          |1 = Turn-on related circuit of PHY transceiver.
 * |[10]    |BYTEM     |CPU Access USB SRAM Size Mode Selection
 * |        |          |0 = Word mode: The size of the transfer from CPU to USB SRAM can be Word only.
 * |        |          |1 = Byte mode: The size of the transfer from CPU to USB SRAM can be Byte only.
 * @var USBD_T::FLDET
 * Offset: 0x14  USB Floating Detection Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |FLDET     |Device Floating Detected
 * |        |          |0 = Controller is not attached into the USB host.
 * |        |          |1 =Controller is attached into the BUS.
 * @var USBD_T::STBUFSEG
 * Offset: 0x18  Setup Token Buffer Segmentation Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[8:3]   |STBUFSEG  |Setup Token Buffer Segmentation
 * |        |          |It is used to indicate the offset address for the SETUP token with the USB Device SRAM
 * |        |          |starting address The effective starting address is
 * |        |          |USB_SRAM address + {STBUFSEG[8:3], 3'b000}
 * |        |          |Where the USB_SRAM address = USBD_BA+0x100h.
 * |        |          |Note: It is used for SETUP token only.
 * @var USBD_T::DRVSE0
 * Offset: 0x90  USB Drive SE0 Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |DRVSE0    |Drive Single Ended Zero In USB Bus
 * |        |          |The Single Ended Zero (SE0) is when both lines (USB_D+ and USB_D-) are being pulled low.
 * |        |          |0 = None.
 * |        |          |1 = Force USB PHY transceiver to drive SE0.
 */

    __IO uint32_t INTEN;         /* Offset: 0x00  USB Interrupt Enable Register                                      */
    __IO uint32_t INTSTS;        /* Offset: 0x04  USB Interrupt Event Status Register                                */
    __IO uint32_t FADDR;         /* Offset: 0x08  USB Device Function Address Register                               */
    __I  uint32_t EPSTS;         /* Offset: 0x0C  USB Endpoint Status Register                                       */
    __IO uint32_t ATTR;          /* Offset: 0x10  USB Bus Status and Attribution Register                            */
    __I  uint32_t FLDET;         /* Offset: 0x14  USB Floating Detection Register                                    */
    __IO uint32_t STBUFSEG;      /* Offset: 0x18  Setup Token Buffer Segmentation Register                           */
    __I  uint32_t RESERVE0;   
    USBD_EP_T     EP[6];         /* Offset: 0x20  Endpoint Related Configuration Registers                           */
    __I  uint32_t RESERVE1[4];  
    __IO uint32_t DRVSE0;        /* Offset: 0x90  USB Drive SE0 Control Register                                     */

} USBD_T;




/**
    @addtogroup USBD_CONST USBD Bit Field Definition
    Constant Definitions for USBD Controller
@{ */

/* USBD INTEN Bit Field Definitions */
#define USBD_INTEN_INNAK_EN_Pos    15                                    /*!< USBD_T::INTEN: INNAK_EN Position */
#define USBD_INTEN_INNAK_EN_Msk    (1ul << USBD_INTEN_INNAK_EN_Pos)      /*!< USBD_T::INTEN: INNAK_EN Mask */

#define USBD_INTEN_WAKEUP_EN_Pos   8                                     /*!< USBD_T::INTEN: RWAKEUP Position */
#define USBD_INTEN_WAKEUP_EN_Msk   (1ul << USBD_INTEN_WAKEUP_EN_Pos)     /*!< USBD_T::INTEN: RWAKEUP Mask */

#define USBD_INTEN_WAKEUP_IE_Pos   3                                     /*!< USBD_T::INTEN: WAKEUP_IE Position */
#define USBD_INTEN_WAKEUP_IE_Msk   (1ul << USBD_INTEN_WAKEUP_IE_Pos)     /*!< USBD_T::INTEN: WAKEUP_IE Mask */

#define USBD_INTEN_FLDET_IE_Pos    2                                     /*!< USBD_T::INTEN: FLDET_IE Position */
#define USBD_INTEN_FLDET_IE_Msk    (1ul << USBD_INTEN_FLDET_IE_Pos)      /*!< USBD_T::INTEN: FLDET_IE Mask */

#define USBD_INTEN_USB_IE_Pos      1                                     /*!< USBD_T::INTEN: USB_IE Position */
#define USBD_INTEN_USB_IE_Msk      (1ul << USBD_INTEN_USB_IE_Pos)        /*!< USBD_T::INTEN: USB_IE Mask */

#define USBD_INTEN_BUS_IE_Pos      0                                     /*!< USBD_T::INTEN: BUS_IE Position */
#define USBD_INTEN_BUS_IE_Msk      (1ul << USBD_INTEN_BUS_IE_Pos)        /*!< USBD_T::INTEN: BUS_IE Mask */

/* USBD INTSTS Bit Field Definitions */                                          
#define USBD_INTSTS_SETUP_Pos        31                                  /*!< USBD_T::INTSTS: SETUP Position */
#define USBD_INTSTS_SETUP_Msk        (1ul << USBD_INTSTS_SETUP_Pos)      /*!< USBD_T::INTSTS: SETUP Mask */

#define USBD_INTSTS_EPEVT_Pos        16                                  /*!< USBD_T::INTSTS: EPEVT Position */
#define USBD_INTSTS_EPEVT_Msk        (0x3Ful << USBD_INTSTS_EPEVT_Pos)   /*!< USBD_T::INTSTS: EPEVT Mask */

#define USBD_INTSTS_WAKEUP_STS_Pos   3                                   /*!< USBD_T::INTSTS: WAKEUP_STS Position */
#define USBD_INTSTS_WAKEUP_STS_Msk   (1ul << USBD_INTSTS_WAKEUP_STS_Pos) /*!< USBD_T::INTSTS: WAKEUP_STS Mask */

#define USBD_INTSTS_FLDET_STS_Pos    2                                   /*!< USBD_T::INTSTS: FLDET_STS Position */
#define USBD_INTSTS_FLDET_STS_Msk    (1ul << USBD_INTSTS_FLDET_STS_Pos)  /*!< USBD_T::INTSTS: FLDET_STS Mask */

#define USBD_INTSTS_USB_STS_Pos      1                                   /*!< USBD_T::INTSTS: USB_STS Position */
#define USBD_INTSTS_USB_STS_Msk      (1ul << USBD_INTSTS_USB_STS_Pos)    /*!< USBD_T::INTSTS: USB_STS Mask */

#define USBD_INTSTS_BUS_STS_Pos      0                                   /*!< USBD_T::INTSTS: BUS_STS Position */
#define USBD_INTSTS_BUS_STS_Msk      (1ul << USBD_INTSTS_BUS_STS_Pos)    /*!< USBD_T::INTSTS: BUS_STS Mask */

/* USBD FADDR Bit Field Definitions */                                           
#define USBD_FADDR_FADDR_Pos     0                                       /*!< USBD_T::FADDR: FADDR Position */
#define USBD_FADDR_FADDR_Msk     (0x7Ful << USBD_FADDR_FADDR_Pos)        /*!< USBD_T::FADDR: FADDR Mask */

/* USBD EPSTS Bit Field Definitions */                                           
#define USBD_EPSTS_EPSTS5_Pos    23                                      /*!< USBD_T::EPSTS: EPSTS5 Position */
#define USBD_EPSTS_EPSTS5_Msk    (7ul << USBD_EPSTS_EPSTS5_Pos)          /*!< USBD_T::EPSTS: EPSTS5 Mask */

#define USBD_EPSTS_EPSTS4_Pos    20                                      /*!< USBD_T::EPSTS: EPSTS4 Position */
#define USBD_EPSTS_EPSTS4_Msk    (7ul << USBD_EPSTS_EPSTS4_Pos)          /*!< USBD_T::EPSTS: EPSTS4 Mask */

#define USBD_EPSTS_EPSTS3_Pos    17                                      /*!< USBD_T::EPSTS: EPSTS3 Position */
#define USBD_EPSTS_EPSTS3_Msk    (7ul << USBD_EPSTS_EPSTS3_Pos)          /*!< USBD_T::EPSTS: EPSTS3 Mask */

#define USBD_EPSTS_EPSTS2_Pos    14                                      /*!< USBD_T::EPSTS: EPSTS2 Position */
#define USBD_EPSTS_EPSTS2_Msk    (7ul << USBD_EPSTS_EPSTS2_Pos)          /*!< USBD_T::EPSTS: EPSTS2 Mask */

#define USBD_EPSTS_EPSTS1_Pos    11                                      /*!< USBD_T::EPSTS: EPSTS1 Position */
#define USBD_EPSTS_EPSTS1_Msk    (7ul << USBD_EPSTS_EPSTS1_Pos)          /*!< USBD_T::EPSTS: EPSTS1 Mask */

#define USBD_EPSTS_EPSTS0_Pos    8                                       /*!< USBD_T::EPSTS: EPSTS0 Position */
#define USBD_EPSTS_EPSTS0_Msk    (7ul << USBD_EPSTS_EPSTS0_Pos)          /*!< USBD_T::EPSTS: EPSTS0 Mask */

#define USBD_EPSTS_OVERRUN_Pos   7                                       /*!< USBD_T::EPSTS: OVERRUN Position */
#define USBD_EPSTS_OVERRUN_Msk   (1ul << USBD_EPSTS_OVERRUN_Pos)         /*!< USBD_T::EPSTS: OVERRUN Mask */

/* USBD ATTR Bit Field Definitions */                                            
#define USBD_ATTR_BYTEM_Pos      10                                      /*!< USBD_T::ATTR: BYTEM Position */
#define USBD_ATTR_BYTEM_Msk      (1ul << USBD_ATTR_BYTEM_Pos)            /*!< USBD_T::ATTR: BYTEM Mask */

#define USBD_ATTR_PWRDN_Pos      9                                       /*!< USBD_T::ATTR: PWRDN Position */
#define USBD_ATTR_PWRDN_Msk      (1ul << USBD_ATTR_PWRDN_Pos)            /*!< USBD_T::ATTR: PWRDN Mask */

#define USBD_ATTR_DPPU_EN_Pos    8                                       /*!< USBD_T::ATTR: DPPU_EN Position */
#define USBD_ATTR_DPPU_EN_Msk    (1ul << USBD_ATTR_DPPU_EN_Pos)          /*!< USBD_T::ATTR: DPPU_EN Mask */

#define USBD_ATTR_USB_EN_Pos     7                                       /*!< USBD_T::ATTR: USB_EN Position */
#define USBD_ATTR_USB_EN_Msk     (1ul << USBD_ATTR_USB_EN_Pos)           /*!< USBD_T::ATTR: USB_EN Mask */

#define USBD_ATTR_RWAKEUP_Pos    5                                       /*!< USBD_T::ATTR: RWAKEUP Position */
#define USBD_ATTR_RWAKEUP_Msk    (1ul << USBD_ATTR_RWAKEUP_Pos)          /*!< USBD_T::ATTR: RWAKEUP Mask */

#define USBD_ATTR_PHY_EN_Pos     4                                       /*!< USBD_T::ATTR: PHY_EN Position */
#define USBD_ATTR_PHY_EN_Msk     (1ul << USBD_ATTR_PHY_EN_Pos)           /*!< USBD_T::ATTR: PHY_EN Mask */

#define USBD_ATTR_TIMEOUT_Pos    3                                       /*!< USBD_T::ATTR: TIMEOUT Position */
#define USBD_ATTR_TIMEOUT_Msk    (1ul << USBD_ATTR_TIMEOUT_Pos)          /*!< USBD_T::ATTR: TIMEOUT Mask */

#define USBD_ATTR_RESUME_Pos     2                                       /*!< USBD_T::ATTR: RESUME Position */
#define USBD_ATTR_RESUME_Msk     (1ul << USBD_ATTR_RESUME_Pos)           /*!< USBD_T::ATTR: RESUME Mask */

#define USBD_ATTR_SUSPEND_Pos    1                                       /*!< USBD_T::ATTR: SUSPEND Position */
#define USBD_ATTR_SUSPEND_Msk    (1ul << USBD_ATTR_SUSPEND_Pos)          /*!< USBD_T::ATTR: SUSPEND Mask */

#define USBD_ATTR_USBRST_Pos     0                                       /*!< USBD_T::ATTR: USBRST Position */
#define USBD_ATTR_USBRST_Msk     (1ul << USBD_ATTR_USBRST_Pos)           /*!< USBD_T::ATTR: USBRST Mask */

/* USBD FLDET Bit Field Definitions */                                           
#define USBD_FLDET_FLDET_Pos     0                                       /*!< USBD_T::FLDET: FLDET Position */
#define USBD_FLDET_FLDET_Msk     (1ul << USBD_FLDET_FLDET_Pos)           /*!< USBD_T::FLDET: FLDET Mask */

/* USBD STBUFSEG Bit Field Definitions */
#define USBD_STBUFSEG_STBUFSEG_Pos   3                                        /*!< USBD_T::STBUFSEG: STBUFSEG Position */
#define USBD_STBUFSEG_STBUFSEG_Msk   (0x3Ful << USBD_STBUFSEG_STBUFSEG_Pos)   /*!< USBD_T::STBUFSEG: STBUFSEG Mask */

/* USBD BUFSEG Bit Field Definitions */
#define USBD_BUFSEG_BUFSEG_Pos   3                                       /*!< USBD_EP_T::BUFSEG: BUFSEG Position */
#define USBD_BUFSEG_BUFSEG_Msk   (0x3Ful << USBD_BUFSEG_BUFSEG_Pos)      /*!< USBD_EP_T::BUFSEG: BUFSEG Mask */

/* USBD MXPLD Bit Field Definitions */                                           
#define USBD_MXPLD_MXPLD_Pos    0                                        /*!< USBD_EP_T::MXPLD: MXPLD Position */
#define USBD_MXPLD_MXPLD_Msk    (0x1FFul << USBD_MXPLD_MXPLD_Pos)        /*!< USBD_EP_T::MXPLD: MXPLD Mask */

/* USBD CFG Bit Field Definitions */                                             
#define USBD_CFG_CSTALL_Pos     9                                        /*!< USBD_EP_T::CFG: CSTALL Position */
#define USBD_CFG_CSTALL_Msk     (1ul << USBD_CFG_CSTALL_Pos)             /*!< USBD_EP_T::CFG: CSTALL Mask */

#define USBD_CFG_DSQ_SYNC_Pos   7                                        /*!< USBD_EP_T::CFG: DSQ_SYNC Position */
#define USBD_CFG_DSQ_SYNC_Msk   (1ul << USBD_CFG_DSQ_SYNC_Pos)           /*!< USBD_EP_T::CFG: DSQ_SYNC Mask */

#define USBD_CFG_STATE_Pos      5                                        /*!< USBD_EP_T::CFG: STATE Position */
#define USBD_CFG_STATE_Msk      (3ul << USBD_CFG_STATE_Pos)              /*!< USBD_EP_T::CFG: STATE Mask */

#define USBD_CFG_ISOCH_Pos      4                                        /*!< USBD_EP_T::CFG: ISOCH Position */
#define USBD_CFG_ISOCH_Msk      (1ul << USBD_CFG_ISOCH_Pos)              /*!< USBD_EP_T::CFG: ISOCH Mask */

#define USBD_CFG_EP_NUM_Pos     0                                        /*!< USBD_EP_T::CFG: EP_NUM Position */
#define USBD_CFG_EP_NUM_Msk     (0xFul << USBD_CFG_EP_NUM_Pos)           /*!< USBD_EP_T::CFG: EP_NUM Mask */

/* USBD CFGP Bit Field Definitions */                                            
#define USBD_CFGP_SSTALL_Pos    1                                        /*!< USBD_EP_T::CFGP: SSTALL Position */
#define USBD_CFGP_SSTALL_Msk    (1ul << USBD_CFGP_SSTALL_Pos)            /*!< USBD_EP_T::CFGP: SSTALL Mask */

#define USBD_CFGP_CLRRDY_Pos    0                                        /*!< USBD_EP_T::CFGP: CLRRDY Position */
#define USBD_CFGP_CLRRDY_Msk    (1ul << USBD_CFGP_CLRRDY_Pos)            /*!< USBD_EP_T::CFGP: CLRRDY Mask */

/* USBD DRVSE0 Bit Field Definitions */                                          
#define USBD_DRVSE0_DRVSE0_Pos   0                                       /*!< USBD_T::DRVSE0: DRVSE0 Position */
#define USBD_DRVSE0_DRVSE0_Msk   (1ul << USBD_DRVSE0_DRVSE0_Pos)         /*!< USBD_T::DRVSE0: DRVSE0 Mask */

/*@}*/ /* end of group USBD_CONST */
/*@}*/ /* end of group USBD */




/*---------------------- Watch Dog Timer Controller -------------------------*/
/**
    @addtogroup WDT Watch Dog Timer Controller (WDT)
    Memory Mapped Structure for WDT Controller
@{ */


typedef struct
{


/**
 * @var WDT_T::WTCR
 * Offset: 0x00  Watchdog Timer Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |WTR       |Reset Watchdog Timer Up Counter (Write Protect)
 * |        |          |0 = No effect.
 * |        |          |1 = Reset the internal 18-bit WDT up counter value.
 * |        |          |Note: This bit will be automatically cleared by hardware.
 * |[1]     |WTRE      |Watchdog Timer Reset Enable (Write Protect)
 * |        |          |Setting this bit will enable the WDT time-out reset function if the WDT up counter value has
 * |        |          |not been cleared after the specific WDT reset delay period expires.
 * |        |          |0 = WDT time-out reset function Disabled.
 * |        |          |1 = WDT time-out reset function Enabled.
 * |[2]     |WTRF      |Watchdog Timer Time-out Reset Flag
 * |        |          |This bit indicates the system has been reset by WDT time-out reset or not.
 * |        |          |0 = WDT time-out reset did not occur.
 * |        |          |1 = WDT time-out reset occurred.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * |[3]     |WTIF      |Watchdog Timer Time-out Interrupt Flag
 * |        |          |This bit will set to 1 while WDT up counter value reaches the selected WDT time-out
 * |        |          |interval.
 * |        |          |0 = WDT time-out interrupt did not occur.
 * |        |          |1 = WDT time-out interrupt occurred.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * |[4]     |WTWKE     |Watchdog Timer Time-out Wake-Up Function Control
 * |        |          |(Write Protect)
 * |        |          |If this bit is set to 1, while WTIF is generated to 1 and WTIE enabled, the WDT time-out
 * |        |          |interrupt signal will generate a wake-up trigger event to chip.
 * |        |          |0 = Wake-up trigger event Disabled if WDT time-out interrupt signal generated.
 * |        |          |1 = Wake-up trigger event Enabled if WDT time-out interrupt signal generated.
 * |        |          |Note: Chip can be woken-up by WDT time-out interrupt signal generated only if WDT clock
 * |        |          |source is selected to 10 kHz oscillator.
 * |[5]     |WTWKF     |Watchdog Timer Time-out Wake-Up Flag
 * |        |          |This bit indicates the interrupt wake-up flag status of WDT.
 * |        |          |0 = WDT does not cause chip wake-up.
 * |        |          |1 = Chip wake-up from Idle or Power-down mode if WDT time-out interrupt signal generated.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * |[6]     |WTIE      |Watchdog Timer Time-out Interrupt Enable Control (Write Protect)
 * |        |          |If this bit is enabled, the WDT time-out interrupt signal is generated and inform to CPU.
 * |        |          |0 = WDT time-out interrupt Disabled.
 * |        |          |1 = WDT time-out interrupt Enabled.
 * |[7]     |WTE       |Watchdog Timer Enable Control (Write Protect)
 * |        |          |0 = WDT Disabled. (This action will reset the internal up counter value.)
 * |        |          |1 = WDT Enabled.
 * |        |          |Note: If CWDTEN (CONFIG0[31] Watchdog Enable) bit is set to 0, this bit is forced as 1 and
 * |        |          | user cannot change this bit to 0.
 * |[10:8]  |WTIS      |Watchdog Timer Time-out Interval Selection (Write Protect)
 * |        |          |These three bits select the time-out interval period for the WDT.
 * |        |          |000 = 24 *TWDT.
 * |        |          |001 = 26 * TWDT.
 * |        |          |010 = 28 * TWDT.
 * |        |          |011 = 210 * TWDT.
 * |        |          |100 = 212 * TWDT.
 * |        |          |101 = 214 * TWDT.
 * |        |          |110 = 216 * TWDT.
 * |        |          |111 = 218 * TWDT.
 * |[31]    |DBGACK_WDT|ICE Debug Mode Acknowledge Disable Control (Write Protect)
 * |        |          |0 = ICE debug mode acknowledgment effects WDT counting.
 * |        |          |WDT up counter will be held while CPU is held by ICE.
 * |        |          |1 = ICE debug mode acknowledgment Disabled.
 * |        |          |WDT up counter will keep going no matter CPU is held by ICE or not.
 * @var WDT_T::WTCRALT
 * Offset: 0x04  Watchdog Timer Alternative Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[1:0]   |WTRDSEL   |Watchdog Timer Reset Delay Selection (Write Protect)
 * |        |          |When WDT time-out happened, user has a time named WDT Reset Delay Period to clear WDT
 * |        |          |counter to prevent WDT time-out reset happened.
 * |        |          |User can select a suitable value of WDT Reset Delay Period for different WDT time-out
 * |        |          |period.
 * |        |          |These bits are protected bit.
 * |        |          |It means programming this bit needs to write "59h", "16h", "88h" to address 0x5000_0100 to
 * |        |          |disable register protection.
 * |        |          |Reference the register REGWRPROT at address GCR_BA+0x100.
 * |        |          |00 = Watchdog Timer Reset Delay Period is 1026 * WDT_CLK.
 * |        |          |01 = Watchdog Timer Reset Delay Period is 130 * WDT_CLK.
 * |        |          |10 = Watchdog Timer Reset Delay Period is 18 * WDT_CLK.
 * |        |          |11 = Watchdog Timer Reset Delay Period is 3 * WDT_CLK.
 * |        |          |Note: This register will be reset to 0 if WDT time-out reset happened.
 */

    __IO uint32_t WTCR;          /* Offset: 0x00  Watchdog Timer Control Register                                    */
    __IO uint32_t WTCRALT;       /* Offset: 0x04  Watchdog Timer Alternative Control Register                        */

} WDT_T;



/**
    @addtogroup WDT_CONST WDT Bit Field Definition
    Constant Definitions for WDT Controller
@{ */

/* WDT WTCR Bit Field Definitions */
#define WDT_WTCR_DBGACK_WDT_Pos 31                                              /*!< WDT_T::WTCR: DBGACK_WDT Position */
#define WDT_WTCR_DBGACK_WDT_Msk (1ul << WDT_WTCR_DBGACK_WDT_Pos)                /*!< WDT_T::WTCR: DBGACK_WDT Mask     */

#define WDT_WTCR_WTIS_Pos       8                                               /*!< WDT_T::WTCR: WTIS Position */
#define WDT_WTCR_WTIS_Msk       (0x7ul << WDT_WTCR_WTIS_Pos)                    /*!< WDT_T::WTCR: WTIS Mask     */

#define WDT_WTCR_WTE_Pos        7                                               /*!< WDT_T::WTCR: WTE Position  */
#define WDT_WTCR_WTE_Msk        (1ul << WDT_WTCR_WTE_Pos)                       /*!< WDT_T::WTCR: WTE Mask      */

#define WDT_WTCR_WTIE_Pos       6                                               /*!< WDT_T::WTCR: WTIE Position */
#define WDT_WTCR_WTIE_Msk       (1ul << WDT_WTCR_WTIE_Pos)                      /*!< WDT_T::WTCR: WTIE Mask     */

#define WDT_WTCR_WTWKF_Pos      5                                               /*!< WDT_T::WTCR: WTWKF Position */
#define WDT_WTCR_WTWKF_Msk      (1ul << WDT_WTCR_WTWKF_Pos)                     /*!< WDT_T::WTCR: WTWKF Mask     */

#define WDT_WTCR_WTWKE_Pos      4                                               /*!< WDT_T::WTCR: WTWKE Position */
#define WDT_WTCR_WTWKE_Msk      (1ul << WDT_WTCR_WTWKE_Pos)                     /*!< WDT_T::WTCR: WTWKE Mask     */

#define WDT_WTCR_WTIF_Pos       3                                               /*!< WDT_T::WTCR: WTIF Position  */
#define WDT_WTCR_WTIF_Msk       (1ul << WDT_WTCR_WTIF_Pos)                      /*!< WDT_T::WTCR: WTIF Mask      */

#define WDT_WTCR_WTRF_Pos       2                                               /*!< WDT_T::WTCR: WTRF Position  */
#define WDT_WTCR_WTRF_Msk       (1ul << WDT_WTCR_WTRF_Pos)                      /*!< WDT_T::WTCR: WTRF Mask      */

#define WDT_WTCR_WTRE_Pos       1                                               /*!< WDT_T::WTCR: WTRE Position  */
#define WDT_WTCR_WTRE_Msk       (1ul << WDT_WTCR_WTRE_Pos)                      /*!< WDT_T::WTCR: WTRE Mask      */

#define WDT_WTCR_WTR_Pos        0                                               /*!< WDT_T::WTCR: WTR Position   */
#define WDT_WTCR_WTR_Msk        (1ul << WDT_WTCR_WTR_Pos)                       /*!< WDT_T::WTCR: WTR Mask       */

/* WDT WTCRALT Bit Field Definitions */                                                 
#define WDT_WTCRALT_WTRDSEL_Pos 0                                               /*!< WDT_T::WTCRALT: WTRDSEL Position */
#define WDT_WTCRALT_WTRDSEL_Msk (0x3ul << WDT_WTCRALT_WTRDSEL_Pos)              /*!< WDT_T::WTCRALT: WTRDSEL Mask */
/*@}*/ /* end of group WDT_CONST */
/*@}*/ /* end of group WDT */


/*---------------------- Window Watchdog Timer -------------------------*/
/**
    @addtogroup WWDT Window Watchdog Timer (WWDT)
    Memory Mapped Structure for WWDT Controller
@{ */


typedef struct
{


/**
 * @var WWDT_T::WWDTRLD
 * Offset: 0x00  Window Watchdog Timer Reload Counter Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[31:0]  |WWDTRLD   |WWDT Reload Counter Register
 * |        |          |Writing 0x00005AA5 to this register will reload the WWDT counter value to 0x3F.
 * |        |          |Note: User can only write WWDTRLD to reload WWDT counter value when current WWDT
 * |        |          | counter value between 0 and WINCMP. If user writes WWDTRLD when current WWDT
 * |        |          | counter value is larger than WINCMP, WWDT reset signal will generate immediately.
 * @var WWDT_T::WWDTCR
 * Offset: 0x04  Window Watchdog Timer Control Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |WWDTEN    |WWDT Enable Control
 * |        |          |0 = WWDT counter is stopped.
 * |        |          |1 = WWDT counter is starting counting.
 * |[1]     |WWDTIE    |WWDT Interrupt Enable Control
 * |        |          |If this bit is enabled, the WWDT counter compare match interrupt signal is generated and
 * |        |          |inform to CPU.
 * |        |          |0 = WWDT counter compare match interrupt Disabled.
 * |        |          |1 = WWDT counter compare match interrupt Enabled.
 * |[11:8]  |PERIODSEL |WWDT Counter Prescale Period Selection
 * |        |          |0000 = Pre-scale is 1; Max time-out period is 1 * 64 * TWWDT.
 * |        |          |0001 = Pre-scale is 2; Max time-out period is 2 * 64 * TWWDT.
 * |        |          |0010 = Pre-scale is 4; Max time-out period is 4 * 64 * TWWDT.
 * |        |          |0011 = Pre-scale is 8; Max time-out period is 8 * 64 * TWWDT.
 * |        |          |0100 = Pre-scale is 16; Max time-out period is 16 * 64 * TWWDT.
 * |        |          |0101 = Pre-scale is 32; Max time-out period is 32 * 64 * TWWDT.
 * |        |          |0110 = Pre-scale is 64; Max time-out period is 64 * 64 * TWWDT.
 * |        |          |0111 = Pre-scale is 128; Max time-out period is 128 * 64 * TWWDT.
 * |        |          |1000 = Pre-scale is 192; Max time-out period is 192 * 64 * TWWDT.
 * |        |          |1001 = Pre-scale is 256; Max time-out period is 256 * 64 * TWWDT.
 * |        |          |1010 = Pre-scale is 384; Max time-out period is 384 * 64 * TWWDT.
 * |        |          |1011 = Pre-scale is 512; Max time-out period is 512 * 64 * TWWDT.
 * |        |          |1100 = Pre-scale is 768; Max time-out period is 768 * 64 * TWWDT.
 * |        |          |1101 = Pre-scale is 1024; Max time-out period is 1024 * 64 * TWWDT.
 * |        |          |1110 = Pre-scale is 1536; Max time-out period is 1536 * 64 * TWWDT.
 * |        |          |1111 = Pre-scale is 2048; Max time-out period is 2048 * 64 * TWWDT.
 * |[21:16] |WINCMP    |WWDT Window Compare Register
 * |        |          |Set this register to adjust the valid reload window.
 * |        |          |Note: User can only write WWDTRLD to reload WWDT counter value when current WWDT counter
 * |        |          |value between 0 and WINCMP.
 * |        |          |If user writes WWDTRLD when current WWDT counter value larger than WINCMP, WWDT reset signal
 * |        |          |will generate immediately.
 * |[31]    |DBGACK_WWDT|ICE Debug Mode Acknowledge Disable Control
 * |        |          |0 = ICE debug mode acknowledgment effects WWDT counting.
 * |        |          |WWDT down counter will be held while CPU is held by ICE.
 * |        |          |1 = ICE debug mode acknowledgment Disabled.
 * |        |          |WWDT down counter will keep going no matter CPU is held by ICE or not.
 * @var WWDT_T::WWDTSR
 * Offset: 0x08  Window Watchdog Timer Status Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[0]     |WWDTIF    |WWDT Compare Match Interrupt Flag
 * |        |          |This bit indicates the interrupt flag status of WWDT while WWDT counter value matches WINCMP
 * |        |          |value.
 * |        |          |0 = No effect.
 * |        |          |1 = WWDT counter value matches WINCMP value.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * |[1]     |WWDTRF    |WWDT Time-out Reset Flag
 * |        |          |This bit indicates the system has been reset by WWDT time-out reset or not.
 * |        |          |0 = WWDT time-out reset did not occur.
 * |        |          |1 = WWDT time-out reset occurred.
 * |        |          |Note: This bit is cleared by writing 1 to it.
 * @var WWDT_T::WWDTCVR
 * Offset: 0x0C  Window Watchdog Timer Counter Value Register
 * ---------------------------------------------------------------------------------------------------
 * |Bits    |Field     |Descriptions
 * | :----: | :----:   | :---- |
 * |[5:0]   |WWDTCVAL  |WWDT Counter Value
 * |        |          |WWDTCVAL will be updated continuously to monitor 6-bit down counter value.
 */

    __IO uint32_t WWDTRLD;       /* Offset: 0x00  Window Watchdog Timer Reload Counter Register                      */
    __IO uint32_t WWDTCR;        /* Offset: 0x04  Window Watchdog Timer Control Register                             */
    __IO uint32_t WWDTSR;        /* Offset: 0x08  Window Watchdog Timer Status Register                              */
    __I  uint32_t WWDTCVR;       /* Offset: 0x0C  Window Watchdog Timer Counter Value Register                       */

} WWDT_T;



/**
    @addtogroup WWDT_CONST WWDT Bit Field Definition
    Constant Definitions for WWDT Controller
@{ */

/* WWDT WWDTRLD Bit Field Definitions */
#define WWDT_WWDTRLD_WWDTRLD_Pos    0                                           /*!< WWDT_T::WWDTRLD: WWDTRLD Position */
#define WWDT_WWDTRLD_WWDTRLD_Msk    (0xFFFFFFFFul << WWDT_WWDTRLD_WWDTRLD_Pos)  /*!< WWDT_T::WWDTRLD: WWDTRLD Mask */

/* WWDT WWDTCR Bit Field Definitions */                                                  
#define WWDT_WWDTCR_DBGACK_WWDT_Pos 31                                          /*!< WWDT_T::WWDTCR: DBGACK_WWDT Position */
#define WWDT_WWDTCR_DBGACK_WWDT_Msk (1ul << WWDT_WWDTCR_DBGACK_WWDT_Pos)        /*!< WWDT_T::WWDTCR: DBGACK_WWDT Mask */

#define WWDT_WWDTCR_WINCMP_Pos      16                                          /*!< WWDT_T::WWDTCR: WINCMP Position */
#define WWDT_WWDTCR_WINCMP_Msk      (0x3Ful << WWDT_WWDTCR_WINCMP_Pos)          /*!< WWDT_T::WWDTCR: WINCMP Mask */

#define WWDT_WWDTCR_PERIODSEL_Pos   8                                           /*!< WWDT_T::WWDTCR: PERIODSEL Position */
#define WWDT_WWDTCR_PERIODSEL_Msk   (0xFul << WWDT_WWDTCR_PERIODSEL_Pos)        /*!< WWDT_T::WWDTCR: PERIODSEL Mask */

#define WWDT_WWDTCR_WWDTIE_Pos      1                                           /*!< WWDT_T::WWDTCR: WWDTIE Position */
#define WWDT_WWDTCR_WWDTIE_Msk      (1ul << WWDT_WWDTCR_WWDTIE_Pos)             /*!< WWDT_T::WWDTCR: WWDTIE Mask */

#define WWDT_WWDTCR_WWDTEN_Pos      0                                           /*!< WWDT_T::WWDTCR: WWDTEN Position */
#define WWDT_WWDTCR_WWDTEN_Msk      (1ul << WWDT_WWDTCR_WWDTEN_Pos)             /*!< WWDT_T::WWDTCR: WWDTEN Mask */

/* WWDT WWDTSR Bit Field Definitions */                                                  
#define WWDT_WWDTSR_WWDTRF_Pos      1                                           /*!< WWDT_T::WWDTSR: WWDTRF Position */
#define WWDT_WWDTSR_WWDTRF_Msk      (1ul << WWDT_WWDTSR_WWDTRF_Pos)             /*!< WWDT_T::WWDTSR: WWDTRF Mask */

#define WWDT_WWDTSR_WWDTIF_Pos      0                                           /*!< WWDT_T::WWDTSR: WWDTIF Position */
#define WWDT_WWDTSR_WWDTIF_Msk      (1ul << WWDT_WWDTSR_WWDTIF_Pos)             /*!< WWDT_T::WWDTSR: WWDTIF Mask */

/* WWDT WWDTCVR Bit Field Definitions */                                                 
#define WWDT_WWDTCVR_WWDTCVAL_Pos   0                                           /*!< WWDT_T::WWDTCVR: WWDTRF Position */
#define WWDT_WWDTCVR_WWDTCVAL_Msk   (0x3Ful << WWDT_WWDTCVR_WWDTCVAL_Pos)       /*!< WWDT_T::WWDTCVR: WWDTRF Mask */
/*@}*/ /* end of group WWDT_CONST */
/*@}*/ /* end of group WWDT */
/*@}*/ /* end of group REGISTER */


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup PERIPHERAL_MEM_MAP Peripheral Memory Map
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
#define GPIO_BASE           (AHB_BASE        + 0x4000)                   /*!< GPIO Base Address                                   */
#define PA_BASE             (GPIO_BASE               )                   /*!< GPIO PORTA Base Address                             */
#define PB_BASE             (GPIO_BASE       + 0x0040)                   /*!< GPIO PORTB Base Address                             */
#define PC_BASE             (GPIO_BASE       + 0x0080)                   /*!< GPIO PORTC Base Address                             */
#define PD_BASE             (GPIO_BASE       + 0x00C0)                   /*!< GPIO PORTD Base Address                             */
#define PE_BASE             (GPIO_BASE       + 0x0100)                   /*!< GPIO PORTE Base Address                             */
#define PF_BASE             (GPIO_BASE       + 0x0140)                   /*!< GPIO PORTF Base Address                             */
#define GPIO_DBNCECON_BASE  (GPIO_BASE       + 0x0180)                   /*!< GPIO De-bounce Cycle Control Base Address           */
#define GPIO_PIN_DATA_BASE  (GPIO_BASE       + 0x0200)                   /*!< GPIO Pin Data Input/Output Control Base Address     */


#define UART0_BASE           (APB1_BASE      + 0x50000)
#define UART1_BASE           (APB2_BASE      + 0x50000)
#define UART2_BASE           (APB2_BASE      + 0x54000)


#define TIMER0_BASE          (APB1_BASE      + 0x10000)                 /*!< Timer0 Base Address                              */
#define TIMER1_BASE          (APB1_BASE      + 0x10020)                 /*!< Timer1 Base Address                              */
#define TIMER2_BASE          (APB2_BASE      + 0x10000)                 /*!< Timer2 Base Address                              */
#define TIMER3_BASE          (APB2_BASE      + 0x10020)                 /*!< Timer3 Base Address                              */

#define WDT_BASE             (APB1_BASE      + 0x4000)                  /*!< Watchdog Timer Base Address                      */

#define WWDT_BASE            (APB1_BASE      + 0x4100)                  /*!< Window Watchdog Timer Base Address               */

#define SPI0_BASE            (APB1_BASE      + 0x30000)                 /*!< SPI0 Base Address                                */
#define SPI1_BASE            (APB1_BASE      + 0x34000)                 /*!< SPI1 Base Address                                */
#define SPI2_BASE            (APB2_BASE      + 0x30000)                 /*!< SPI2 Base Address                                */
#define SPI3_BASE            (APB2_BASE      + 0x34000)                 /*!< SPI3 Base Address                                */

#define I2C0_BASE            (APB1_BASE      + 0x20000)                 /*!< I2C0 Base Address                                */
#define I2C1_BASE            (APB2_BASE      + 0x20000)                 /*!< I2C1 Base Address                                */

#define RTC_BASE             (APB1_BASE      + 0x08000)                 /*!< RTC Base Address                                 */

#define ADC_BASE             (APB1_BASE      + 0xE0000)                 /*!< ADC Base Address                                 */

#define ACMP_BASE            (APB1_BASE      + 0xD0000)                 /*!< ACMP Base Address                                */

#define CLK_BASE             (AHB_BASE       + 0x00200)                 /*!< System Clock Controller Base Address             */

#define GCR_BASE             (AHB_BASE       + 0x00000)                 /*!< System Global Controller Base Address            */

#define INT_BASE             (AHB_BASE       + 0x00300)                 /*!< Interrupt Source Controller Base Address         */

#define FMC_BASE             (AHB_BASE       + 0x0C000)

#define PS2_BASE             (APB2_BASE      + 0x00000)                 /*!< PS/2 Base Address                                */

#define USBD_BASE            (APB1_BASE      + 0x60000)                 /*!< USBD Base Address                                */

#define PDMA0_BASE           (AHB_BASE       + 0x08000)                 /*!< PDMA0 Base Address                               */
#define PDMA1_BASE           (AHB_BASE       + 0x08100)                 /*!< PDMA1 Base Address                               */
#define PDMA2_BASE           (AHB_BASE       + 0x08200)                 /*!< PDMA2 Base Address                               */
#define PDMA3_BASE           (AHB_BASE       + 0x08300)                 /*!< PDMA3 Base Address                               */
#define PDMA4_BASE           (AHB_BASE       + 0x08400)                 /*!< PDMA4 Base Address                               */
#define PDMA5_BASE           (AHB_BASE       + 0x08500)                 /*!< PDMA5 Base Address                               */
#define PDMA6_BASE           (AHB_BASE       + 0x08600)                 /*!< PDMA6 Base Address                               */
#define PDMA7_BASE           (AHB_BASE       + 0x08700)                 /*!< PDMA7 Base Address                               */
#define PDMA8_BASE           (AHB_BASE       + 0x08800)                 /*!< PDMA8 Base Address                               */

#define PDMA_GCR_BASE        (AHB_BASE       + 0x08F00)                 /*!< PDMA Global Base Address                         */

#define CRC_BASE             (AHB_BASE       + 0x08E00)                 /*!< CRC Base Address                                 */

#define PWMA_BASE            (APB1_BASE      + 0x40000)                 /*!< PWMA Base Address                                */
#define PWMB_BASE            (APB2_BASE      + 0x40000)                 /*!< PWMB Base Address                                */

#define SC0_BASE             (APB2_BASE      + 0x90000)                 /*!< SC0 Base Address                                 */
#define SC1_BASE             (APB2_BASE      + 0x94000)                 /*!< SC1 Base Address                                 */
#define SC2_BASE             (APB2_BASE      + 0x98000)                 /*!< SC2 Base Address                                 */

#define I2S_BASE             (APB2_BASE      + 0xA0000)                 /*!< I2S Base Address                                 */

#define EBI_BASE             (AHB_BASE       + 0x10000)                 /*!< EBI Base Address                                 */
/*@}*/ /* end of group PERIPHERAL_MEM_MAP */

/******************************************************************************/
/*                         Peripheral Definitions                             */
/******************************************************************************/

/** @addtogroup PERIPHERAL Peripheral Definitions
  The Definitions of Series Peripheral
  @{
 */
#define PA                  ((GPIO_T *) PA_BASE)                        /*!< GPIO PORTA Configuration Struct                        */
#define PB                  ((GPIO_T *) PB_BASE)                        /*!< GPIO PORTB Configuration Struct                        */
#define PC                  ((GPIO_T *) PC_BASE)                        /*!< GPIO PORTC Configuration Struct                        */
#define PD                  ((GPIO_T *) PD_BASE)                        /*!< GPIO PORTD Configuration Struct                        */
#define PE                  ((GPIO_T *) PE_BASE)                        /*!< GPIO PORTE Configuration Struct                        */
#define PF                  ((GPIO_T *) PF_BASE)                        /*!< GPIO PORTF Configuration Struct                        */
#define GPIO                ((GPIO_DBNCECON_T *) GPIO_DBNCECON_BASE)    /*!< Interrupt De-bounce Cycle Control Configuration Struct */

#define UART0               ((UART_T *) UART0_BASE)
#define UART1               ((UART_T *) UART1_BASE)
#define UART2               ((UART_T *) UART2_BASE)

#define TIMER0              ((TIMER_T *) TIMER0_BASE)                   /*!< Timer0 Configuration Struct                      */
#define TIMER1              ((TIMER_T *) TIMER1_BASE)                   /*!< Timer1 Configuration Struct                      */
#define TIMER2              ((TIMER_T *) TIMER2_BASE)                   /*!< Timer2 Configuration Struct                      */
#define TIMER3              ((TIMER_T *) TIMER3_BASE)                   /*!< Timer3 Configuration Struct                      */

#define WDT                 ((WDT_T *) WDT_BASE)                        /*!< Watchdog Timer Configuration Struct              */

#define WWDT                ((WWDT_T *) WWDT_BASE)                      /*!< Window Watchdog Timer Configuration Struct       */

#define SPI0                ((SPI_T *) SPI0_BASE)                       /*!< SPI0 Configuration Struct                        */
#define SPI1                ((SPI_T *) SPI1_BASE)                       /*!< SPI1 Configuration Struct                        */
#define SPI2                ((SPI_T *) SPI2_BASE)                       /*!< SPI2 Configuration Struct                        */
#define SPI3                ((SPI_T *) SPI3_BASE)                       /*!< SPI3 Configuration Struct                        */

#define I2C0                ((I2C_T *) I2C0_BASE)                       /*!< I2C0 Configuration Struct                        */
#define I2C1                ((I2C_T *) I2C1_BASE)                       /*!< I2C1 Configuration Struct                        */

#define I2S                 ((I2S_T *) I2S_BASE)                        /*!< I2S Configuration Struct                         */

#define RTC                 ((RTC_T *) RTC_BASE)                        /*!< RTC Configuration Struct                         */

#define ADC                 ((ADC_T *) ADC_BASE)                        /*!< ADC Configuration Struct                         */

#define ACMP                ((ACMP_T *) ACMP_BASE)                      /*!< ACMP Configuration Struct                        */

#define CLK                 ((CLK_T *) CLK_BASE)                        /*!< System Clock Controller Configuration Struct     */

#define SYS                 ((GCR_T *) GCR_BASE)                        /*!< System Global Controller Configuration Struct    */

#define SYSINT              ((GCR_INT_T *) INT_BASE)                    /*!< Interrupt Source Controller Configuration Struct */

#define FMC                 ((FMC_T *) FMC_BASE)

#define PS2                 ((PS2_T *) PS2_BASE)                        /*!< PS/2 Configuration Struct                        */

#define USBD                ((USBD_T *) USBD_BASE)                      /*!< USBD Configuration Struct                        */

#define PDMA0               ((PDMA_T *) PDMA0_BASE)                     /*!< PDMA0 Configuration Struct                       */
#define PDMA1               ((PDMA_T *) PDMA1_BASE)                     /*!< PDMA1 Configuration Struct                       */
#define PDMA2               ((PDMA_T *) PDMA2_BASE)                     /*!< PDMA2 Configuration Struct                       */
#define PDMA3               ((PDMA_T *) PDMA3_BASE)                     /*!< PDMA3 Configuration Struct                       */
#define PDMA4               ((PDMA_T *) PDMA4_BASE)                     /*!< PDMA4 Configuration Struct                       */
#define PDMA5               ((PDMA_T *) PDMA5_BASE)                     /*!< PDMA5 Configuration Struct                       */
#define PDMA6               ((PDMA_T *) PDMA6_BASE)                     /*!< PDMA6 Configuration Struct                       */
#define PDMA7               ((PDMA_T *) PDMA7_BASE)                     /*!< PDMA7 Configuration Struct                       */
#define PDMA8               ((PDMA_T *) PDMA8_BASE)                     /*!< PDMA8 Configuration Struct                       */

#define PDMA_GCR            ((PDMA_GCR_T *) PDMA_GCR_BASE)              /*!< PDMA Global Configuration Struct                 */

#define CRC                 ((CRC_T *) CRC_BASE)                        /*!< CRC Configuration Struct                         */

#define PWMA                ((PWM_T *) PWMA_BASE)                       /*!< PWMA Configuration Struct                        */
#define PWMB                ((PWM_T *) PWMB_BASE)                       /*!< PWMB Configuration Struct                        */

#define SC0                 ((SC_T *) SC0_BASE)                         /*!< SC0 Configuration Struct                        */
#define SC1                 ((SC_T *) SC1_BASE)                         /*!< SC1 Configuration Struct                        */
#define SC2                 ((SC_T *) SC2_BASE)                         /*!< SC2 Configuration Struct                        */

#define EBI                 ((EBI_T *) EBI_BASE)                        /*!< EBI Configuration Struct                         */

/*@}*/ /* end of group PERIPHERAL */

#define UNLOCKREG(x)        do{*((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x59;*((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x16;*((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x88;}while(*((__IO uint32_t *)(GCR_BASE + 0x100))==0)
#define LOCKREG(x)          *((__IO uint32_t *)(GCR_BASE + 0x100)) = 0x00

#define REGCOPY(dest, src)  *((uint32_t *)&(dest)) = *((uint32_t *)&(src))
#define CLEAR(dest)         *((uint32_t *)&(dest)) = 0

//=============================================================================
/** @addtogroup IO_ROUTINE I/O routines
  The Declaration of I/O routines
  @{
 */

typedef volatile unsigned char  vu8;        ///< Define 8-bit unsigned volatile data type
typedef volatile unsigned short vu16;       ///< Define 16-bit unsigned volatile data type
typedef volatile unsigned long  vu32;       ///< Define 32-bit unsigned volatile data type

/**
  * @brief Get a 8-bit unsigned value from specified address
  * @param[in] addr Address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified address
  */
#define M8(addr)  (*((vu8  *) (addr)))

/**
  * @brief Get a 16-bit unsigned value from specified address
  * @param[in] addr Address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified address
  * @note The input address must be 16-bit aligned
  */
#define M16(addr) (*((vu16 *) (addr)))

/**
  * @brief Get a 32-bit unsigned value from specified address
  * @param[in] addr Address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified address
  * @note The input address must be 32-bit aligned
  */
#define M32(addr) (*((vu32 *) (addr)))

/**
  * @brief Set a 32-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 32-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 32-bit aligned
  */
#define outpw(port,value)     *((volatile unsigned int *)(port)) = value

/**
  * @brief Get a 32-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified I/O port
  * @note The input port must be 32-bit aligned
  */
#define inpw(port)            (*((volatile unsigned int *)(port)))

/**
  * @brief Set a 16-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 16-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 16-bit aligned
  */
#define outps(port,value)     *((volatile unsigned short *)(port)) = value

/**
  * @brief Get a 16-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified I/O port
  * @note The input port must be 16-bit aligned
  */
#define inps(port)            (*((volatile unsigned short *)(port)))

/**
  * @brief Set a 8-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 8-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  */
#define outpb(port,value)     *((volatile unsigned char *)(port)) = value

/**
  * @brief Get a 8-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified I/O port
  */
#define inpb(port)            (*((volatile unsigned char *)(port)))

/**
  * @brief Set a 32-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 32-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 32-bit aligned
  */
#define outp32(port,value)    *((volatile unsigned int *)(port)) = value

/**
  * @brief Get a 32-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 32-bit data from
  * @return  32-bit unsigned value stored in specified I/O port
  * @note The input port must be 32-bit aligned
  */
#define inp32(port)           (*((volatile unsigned int *)(port)))

/**
  * @brief Set a 16-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 16-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  * @note The output port must be 16-bit aligned
  */
#define outp16(port,value)    *((volatile unsigned short *)(port)) = value

/**
  * @brief Get a 16-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 16-bit data from
  * @return  16-bit unsigned value stored in specified I/O port
  * @note The input port must be 16-bit aligned
  */
#define inp16(port)           (*((volatile unsigned short *)(port)))

/**
  * @brief Set a 8-bit unsigned value to specified I/O port
  * @param[in] port Port address to set 8-bit data
  * @param[in] value Value to write to I/O port
  * @return  None
  */
#define outp8(port,value)     *((volatile unsigned char *)(port)) = value

/**
  * @brief Get a 8-bit unsigned value from specified I/O port
  * @param[in] port Port address to get 8-bit data from
  * @return  8-bit unsigned value stored in specified I/O port
  */
#define inp8(port)            (*((volatile unsigned char *)(port)))

/*@}*/ /* end of group IO_ROUTINE */




/** @addtogroup legacy_Constants Legacy Constants
  Legacy Constants
  @{
*/


#define E_SUCCESS   0
#ifndef NULL
#define NULL        0
#endif

#define TRUE        1
#define FALSE       0

#define ENABLE     1
#define DISABLE    0

/* Define one bit mask */
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

/*@}*/ /* end of group legacy_Constants */

/*@}*/ /* end of group Definitions */


/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "sys.h"
#include "adc.h"
#include "fmc.h"
#include "gpio.h"
#include "i2c.h"
#include "pwm.h"
#include "spi.h"
#include "crc.h"
#include "timer.h"
#include "wdt.h"
#include "wwdt.h"
#include "rtc.h"
#include "uart.h"
#include "i2s.h"
#include "usbd.h"
#include "pdma.h"
#include "sc.h"
#include "ps2.h"
#include "clk.h"
#include "acmp.h"
#endif





