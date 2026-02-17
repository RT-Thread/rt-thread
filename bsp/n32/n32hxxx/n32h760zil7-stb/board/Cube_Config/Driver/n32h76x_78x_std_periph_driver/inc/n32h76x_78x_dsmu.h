/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_dsmu.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76x_78x_DSMU_H__
#define __N32H76x_78x_DSMU_H__ 

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32h76x_78x.h"

/** DSMU channel output clock structure definition **/
typedef struct
{
    FunctionalState Activation; /* Output clock enable/disable */
    uint32_t        Selection;  /* Output clock is system clock or audio clock.
                                   This parameter can be a value of @ref DSMU_Channel_OuputClock */
    uint32_t        Divider;    /* Output clock divider.
                                   This parameter must be a number between Min_Data = 2 and Max_Data = 256 */
}DSMU_Channel_OutputClockType;

/** DSMU channel input structure definition **/
typedef struct
{
    uint32_t Multiplexer; /* Input is external serial inputs, internal register or ADC output.
                             This parameter can be a value of @ref DSMU_Channel_InputMultiplexer */
    uint32_t DataPacking; /* Standard, interleaved or dual mode for internal register.
                             This parameter can be a value of @ref DSMU_Channel_DataPacking */
    uint32_t Pins;        /* Input pins are taken from same or following channel.
                             This parameter can be a value of @ref DSMU_Channel_InputPins */
}DSMU_Channel_InputType;

/** DSMU channel serial interface structure definition **/
typedef struct
{
    uint32_t Type;     /* SPI or Manchester modes.
                          This parameter can be a value of @ref DSMU_Channel_SerialInterfaceType */
    uint32_t SpiClock; /* SPI clock select (external or internal with different sampling point).
                          This parameter can be a value of @ref DSMU_Channel_SpiClock */
} DSMU_Channel_SerialInterfaceType;

/** DSMU channel analog watchdog structure definition **/
typedef struct
{
    uint32_t FilterOrder;  /* Analog watchdog Sinc filter order.
                              This parameter can be a value of @ref DSMU_Channel_AwdFilterOrder */
    uint32_t Oversampling; /* Analog watchdog filter oversampling ratio.
                              This parameter must be a number between Min_Data = 1 and Max_Data = 32 */
} DSMU_Channel_AwdType;

/** DSMU channel init structure definition **/
typedef struct
{
    DSMU_Channel_OutputClockType        OutputClock;     /* DSMU channel output clock parameters */
    DSMU_Channel_InputType              Input;           /* DSMU channel input parameters */
    DSMU_Channel_SerialInterfaceType    SerialInterface; /* DSMU channel serial interface parameters */
    DSMU_Channel_AwdType                Awd;             /* DSMU channel analog watchdog parameters */
    int32_t                             Offset;          /* DSMU channel offset.
                                                             This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607 */
    uint32_t                            RightBitShift;   /* DSMU channel right bit shift.
                                                             This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */
} DSMU_Channel_InitType;

/** DSMU filter regular conversion parameters structure definition **/
typedef struct
{
    uint32_t        Trigger;  /* Trigger used to start regular conversion: software or synchronous.
                                 This parameter can be a value of @ref DSMU_Filter_Trigger */
    FunctionalState FastMode; /* Enable/disable fast mode for regular conversion */
    FunctionalState DmaMode;  /* Enable/disable DMA for regular conversion */
} DSMU_Filter_RegularParamType;

/** DSMU filter injected conversion parameters structure definition **/
typedef struct
{
    uint32_t        Trigger;        /* Trigger used to start injected conversion: software, external or synchronous.
                                       This parameter can be a value of @ref DSMU_Filter_Trigger */
    FunctionalState ScanMode;       /* Enable/disable scanning mode for injected conversion */
    FunctionalState DmaMode;        /* Enable/disable DMA for injected conversion */
    uint32_t        ExtTrigger;     /* External trigger.
                                       This parameter can be a value of @ref DSMU_Filter_ExtTrigger */
} DSMU_Filter_InjectedParamType;

/** DSMU filter parameters structure definition **/
typedef struct
{
    uint32_t SincOrder;       /* Sinc filter order.
                                 This parameter can be a value of @ref DSMU_Filter_SincOrder */
    uint32_t Oversampling;    /* Filter oversampling ratio.
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 1024 */
    uint32_t IntOversampling; /* Integrator oversampling ratio.
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 256 */
} DSMU_Filter_FilterParamType;

/** DSMU filter init structure definition **/
typedef struct
{
    DSMU_Filter_RegularParamType  RegularParam;  /* DSMU regular conversion parameters */
    DSMU_Filter_InjectedParamType InjectedParam; /* DSMU injected conversion parameters */
    DSMU_Filter_FilterParamType   FilterParam;   /* DSMU filter parameters */
} DSMU_Filter_InitType;


/** DSMU filter analog watchdog parameters structure definition **/
typedef struct
{
    uint32_t DataSource;      /* Values from digital filter or from channel watchdog filter.
                                 This parameter can be a value of @ref DSMU_Filter_AwdDataSource */
    uint32_t ChannelSelect;   /* Analog watchdog channel selection.
                                 This parameter can be a values combination of @ref DSMU_Channel_Selection */
    int32_t  HighThreshold;   /* High threshold for the analog watchdog.
                                 This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607 */
    int32_t  LowThreshold;    /* Low threshold for the analog watchdog.
                                 This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607 */
    uint32_t HighBreakSignal; /* Break signal assigned to analog watchdog high threshold event.
                                 This parameter can be a values combination of @ref DSMU_BreakSignals */
    uint32_t LowBreakSignal;  /* Break signal assigned to analog watchdog low threshold event.
                                 This parameter can be a values combination of @ref DSMU_BreakSignals */
} DSMU_Filter_AwdParamType;

/**  DSMU_Channel_OuputClock DSMU channel output clock selection **/
#define DSMU_CHANNEL_OUTPUT_CLOCK_SYSTEM    ((uint32_t)0x00000000U)     /* Source for output clock is system clock */
#define DSMU_CHANNEL_OUTPUT_CLOCK_AUDIO     (DSMU_CHYCFG1_CLKOUTSRC)    /* Source for output clock is audio clock */

/**  DSMU_Channel_InputMultiplexer DSMU channel input multiplexer **/
#define DSMU_CHANNEL_EXTERNAL_INPUTS        ((uint32_t)0x00000000U)     /* Data are taken from external inputs */
#define DSMU_CHANNEL_ADC_OUTPUT             (DSMU_CHYCFG1_DATMUX_0)     /* Data are taken from ADC output */
#define DSMU_CHANNEL_INTERNAL_REGISTER      (DSMU_CHYCFG1_DATMUX_1)     /* Data are taken from internal register */

/**  DSMU_Channel_DataPacking DSMU channel input data packing **/
#define DSMU_CHANNEL_STANDARD_MODE          ((uint32_t)0x00000000U)     /* Standard data packing mode */
#define DSMU_CHANNEL_INTERLEAVED_MODE       (DSMU_CHYCFG1_DATPACK_0)    /* Interleaved data packing mode */
#define DSMU_CHANNEL_DUAL_MODE              (DSMU_CHYCFG1_DATPACK_1)    /* Dual data packing mode */

/**  DSMU_Channel_InputPins DSMU channel input pins **/
#define DSMU_CHANNEL_SAME_CHANNEL_PINS      ((uint32_t)0x00000000U)     /* Input from pins on same channel */
#define DSMU_CHANNEL_FOLLOWING_CHANNEL_PINS (DSMU_CHYCFG1_CHINSEL)      /* Input from pins on following channel */

/**  DSMU_Channel_SerialInterfaceType DSMU channel serial interface type **/
#define DSMU_CHANNEL_SPI_RISING             ((uint32_t)0x00000000U)     /* SPI with rising edge */
#define DSMU_CHANNEL_SPI_FALLING            (DSMU_CHYCFG1_SITP_0)       /* SPI with falling edge */
#define DSMU_CHANNEL_MANCHESTER_RISING      (DSMU_CHYCFG1_SITP_1)       /* Manchester with rising edge */
#define DSMU_CHANNEL_MANCHESTER_FALLING     (DSMU_CHYCFG1_SITP)         /* Manchester with falling edge */

/**  DSMU_Channel_SpiClock DSMU channel SPI clock selection **/
#define DSMU_CHANNEL_SPI_CLOCK_EXTERNAL                 ((uint32_t)0x00000000U)     /* External SPI clock */
#define DSMU_CHANNEL_SPI_CLOCK_INTERNAL                 (DSMU_CHYCFG1_SPICLKSEL_0)  /* Internal SPI clock */
#define DSMU_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING    (DSMU_CHYCFG1_SPICLKSEL_1)  /* Internal SPI clock divided by 2, falling edge */
#define DSMU_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING     (DSMU_CHYCFG1_SPICLKSEL)    /* Internal SPI clock divided by 2, rising edge */

/**  DSMU_Channel_AwdFilterOrder DSMU channel analog watchdog filter order **/
#define DSMU_AWD_FASTSINC_ORDER             ((uint32_t)0x00000000U)         /* FastSinc filter type */
#define DSMU_AWD_SINC1_ORDER                (DSMU_CHYAWDSCDET_AWDFORD_0)    /* Sinc 1 filter type */
#define DSMU_AWD_SINC2_ORDER                (DSMU_CHYAWDSCDET_AWDFORD_1)    /* Sinc 2 filter type */
#define DSMU_AWD_SINC3_ORDER                (DSMU_CHYAWDSCDET_AWDFORD)      /* Sinc 3 filter type */

/**  DSMU_Filter_Trigger DSMU filter conversion trigger **/
#define DSMU_FILTER_SW_TRIGGER              ((uint32_t)0x00000000U) /* Software trigger */
#define DSMU_FILTER_SYNC_TRIGGER            ((uint32_t)0x00000001U) /* Synchronous with DSMU_FLT0 */
#define DSMU_FILTER_EXT_TRIGGER             ((uint32_t)0x00000002U) /* External trigger (only for injected conversion) */

/**  DSMU_Channel_Selection DSMU filter channel select **/
/* bit[31:24] used for FLTxCTRL1.RCH[2:0]*/
/* bit[23:16] used for FLTxCTRL2.AWDCH[7:0]*/
/* bit[15:8] used for FLTxCTRL2.EXDETCH[7:0]*/
/* bit[7:0] used for FLTxJCHG.JCHG[7:0]*/
#define DSMU_CHANNEL_SELECT_0               ((uint32_t)0x00010101U) /* Select Channel 0 */
#define DSMU_CHANNEL_SELECT_1               ((uint32_t)0x01020202U) /* Select Channel 1 */
#define DSMU_CHANNEL_SELECT_2               ((uint32_t)0x02040404U) /* Select Channel 2 */
#define DSMU_CHANNEL_SELECT_3               ((uint32_t)0x03080808U) /* Select Channel 3 */
#define DSMU_CHANNEL_SELECT_4               ((uint32_t)0x04101010U) /* Select Channel 4 */
#define DSMU_CHANNEL_SELECT_5               ((uint32_t)0x05202020U) /* Select Channel 5 */
#define DSMU_CHANNEL_SELECT_6               ((uint32_t)0x06404040U) /* Select Channel 6 */
#define DSMU_CHANNEL_SELECT_7               ((uint32_t)0x07808080U) /* Select Channel 7 */

/**  DSMU_Filter_ExtTrigger DSMU filter external trigger **/
#define DSMU_FILTER_EXT_TRIG_ATIM1_TRGO         ((uint32_t)0x00000000U) /* Select ATIM1_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_ATIM2_TRGO         ((uint32_t)0x00000100U) /* Select ATIM2_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_ATIM3_TRGO         ((uint32_t)0x00000200U) /* Select ATIM3_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_ATIM4_TRGO         ((uint32_t)0x00000300U) /* Select ATIM4_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMB1_TRGO        ((uint32_t)0x00000400U) /* Select GTIMB1_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMB2_TRGO        ((uint32_t)0x00000500U) /* Select GTIMB2_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMB3_TRGO        ((uint32_t)0x00000600U) /* Select GTIMB3_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMA1_TRGO        ((uint32_t)0x00000700U) /* Select GTIMA1_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMA2_TRGO        ((uint32_t)0x00000800U) /* Select GTIMA2_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMA3_TRGO        ((uint32_t)0x00000900U) /* Select GTIMA3_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMA4_TRGO        ((uint32_t)0x00000A00U) /* Select GTIMA4_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_GTIMA5_TRGO        ((uint32_t)0x00000B00U) /* Select GTIMA5_TRGO as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_ATIM1_TRGO2        ((uint32_t)0x00000C00U) /* Select ATIM1_TRGO2 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_ATIM3_TRGO2        ((uint32_t)0x00000D00U) /* Select ATIM3_TRGO2 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG1   ((uint32_t)0x00000E00U) /* Select SHRTIM1_ADC_TRG1 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG2   ((uint32_t)0x00000F00U) /* Select SHRTIM1_ADC_TRG2 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG3   ((uint32_t)0x00001000U) /* Select SHRTIM1_ADC_TRG3 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG4   ((uint32_t)0x00001100U) /* Select SHRTIM1_ADC_TRG4 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG1   ((uint32_t)0x00001200U) /* Select SHRTIM2_ADC_TRG1 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG2   ((uint32_t)0x00001300U) /* Select SHRTIM2_ADC_TRG2 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG3   ((uint32_t)0x00001400U) /* Select SHRTIM2_ADC_TRG3 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG4   ((uint32_t)0x00001500U) /* Select SHRTIM2_ADC_TRG4 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI6              ((uint32_t)0x00001600U) /* Select EXTI6 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI7              ((uint32_t)0x00001700U) /* Select EXTI7  as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI8              ((uint32_t)0x00001800U) /* Select EXTI8  as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI9              ((uint32_t)0x00001900U) /* Select EXTI9  as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI10             ((uint32_t)0x00001A00U) /* Select EXTI10 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI11             ((uint32_t)0x00001B00U) /* Select EXTI11 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI12             ((uint32_t)0x00001C00U) /* Select EXTI12 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI13             ((uint32_t)0x00001D00U) /* Select EXTI13 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI14             ((uint32_t)0x00001E00U) /* Select EXTI14 as trigger signal for injected conversion */
#define DSMU_FILTER_EXT_TRIG_EXTI15             ((uint32_t)0x00001F00U) /* Select EXTI15 as trigger signal for injected conversion */

/**  DSMU_Filter_ExtTriggerEdge DSMU filter external trigger edge **/
#define DSMU_FILTER_EXT_TRIG_DISABLE        ((uint32_t)0x00000000U)     /* External trigger disable */
#define DSMU_FILTER_EXT_TRIG_RISING_EDGE    (DSMU_FLTXCTRL1_JEXTEN_0)   /* External rising edge */
#define DSMU_FILTER_EXT_TRIG_FALLING_EDGE   (DSMU_FLTXCTRL1_JEXTEN_1)   /* External falling edge */
#define DSMU_FILTER_EXT_TRIG_BOTH_EDGES     (DSMU_FLTXCTRL1_JEXTEN)     /* External rising and falling edges */

/**  DSMU_Filter_SincOrder DSMU filter sinc order **/
#define DSMU_FILTER_FASTSINC_ORDER          ((uint32_t)0x00000000U)     /* FastSinc filter type */
#define DSMU_FILTER_SINC1_ORDER             ( DSMU_FLTXFCTRL_FORD_0)     /* Sinc 1 filter type */
#define DSMU_FILTER_SINC2_ORDER             ( DSMU_FLTXFCTRL_FORD_1)     /* Sinc 2 filter type */
#define DSMU_FILTER_SINC3_ORDER             ( DSMU_FLTXFCTRL_FORD_0  \
                                            | DSMU_FLTXFCTRL_FORD_1)     /* Sinc 3 filter type */
#define DSMU_FILTER_SINC4_ORDER             ( DSMU_FLTXFCTRL_FORD_2)     /* Sinc 4 filter type */
#define DSMU_FILTER_SINC5_ORDER             ( DSMU_FLTXFCTRL_FORD_0  \
                                            | DSMU_FLTXFCTRL_FORD_2)     /* Sinc 5 filter type */

/**  DSMU_Filter_AwdDataSource DSMU filter analog watchdog data source **/
#define DSMU_FILTER_AWD_FILTER_DATA         ((uint32_t)0x00000000U)     /* From digital filter */
#define DSMU_FILTER_AWD_CHANNEL_DATA        (DSMU_FLTXCTRL1_AWDFSEL)    /* From analog watchdog channel */

/**  DSMU_BreakSignals DSMU break signals **/
#define DSMU_NO_BREAK_SIGNAL                ((uint32_t)0x00000000U) /* No break signal */
#define DSMU_BREAK_SIGNAL_0                 ((uint32_t)0x00000001U) /* Break signal 0 */
#define DSMU_BREAK_SIGNAL_1                 ((uint32_t)0x00000002U) /* Break signal 1 */
#define DSMU_BREAK_SIGNAL_2                 ((uint32_t)0x00000004U) /* Break signal 2 */
#define DSMU_BREAK_SIGNAL_3                 ((uint32_t)0x00000008U) /* Break signal 3 */

/**  DSMU_ContinuousMode DSMU Continuous Mode **/
#define DSMU_CONTINUOUS_CONV_OFF            ((uint32_t)0x00000000U) /* Conversion are not continuous */
#define DSMU_CONTINUOUS_CONV_ON             (DSMU_FLTXCTRL1_RCONT)  /* Conversion are continuous */

/**  DSMU_AwdThreshold DSMU analog watchdog threshold **/
#define DSMU_AWD_HIGH_THRESHOLD             ((uint32_t)0x00000000U) /* Analog watchdog high threshold */
#define DSMU_AWD_LOW_THRESHOLD              ((uint32_t)0x00000001U) /* Analog watchdog low threshold */

/**  DSMU interrupt enable bit **/
#define DSMU_INT_CLOCK_ABSENCE              (DSMU_FLTXCTRL2_CLKABIEN)   /* Clock absence interrupt enable */
#define DSMU_INT_SHORT_CIRCUIT              (DSMU_FLTXCTRL2_SCDETIEN)   /* Short circuit interrupt enable */
#define DSMU_INT_ANALOG_WATCHDOG            (DSMU_FLTXCTRL2_AWDIEN)     /* Analog watchdog interrupt enable */
#define DSMU_INT_REGULAR_OVERRUN            (DSMU_FLTXCTRL2_ROVRIEN)    /* Regular conversion overrun interrupt enable */
#define DSMU_INT_INJECT_OVERRUN             (DSMU_FLTXCTRL2_JOVRIEN)    /* Injected conversion overrun interrupt enable */
#define DSMU_INT_REGULAR_END                (DSMU_FLTXCTRL2_REOCIEN)    /* Regular conversion end interrupt enable */
#define DSMU_INT_INJECT_END                 (DSMU_FLTXCTRL2_JEOCIEN)    /* Injected conversion end interrupt enable */

/**  DSMU interrupt flag bit **/
#define DSMU_FLAG_SHORT_CIRCUIT_CH0         (DSMU_FLTXSTS_SCDETF_0)     /* Short circuit event flag for channel0 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH1         (DSMU_FLTXSTS_SCDETF_1)     /* Short circuit event flag for channel1 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH2         (DSMU_FLTXSTS_SCDETF_2)     /* Short circuit event flag for channel2 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH3         (DSMU_FLTXSTS_SCDETF_3)     /* Short circuit event flag for channel3 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH4         (DSMU_FLTXSTS_SCDETF_4)     /* Short circuit event flag for channel4 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH5         (DSMU_FLTXSTS_SCDETF_5)     /* Short circuit event flag for channel5 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH6         (DSMU_FLTXSTS_SCDETF_6)     /* Short circuit event flag for channel6 */
#define DSMU_FLAG_SHORT_CIRCUIT_CH7         (DSMU_FLTXSTS_SCDETF_7)     /* Short circuit event flag for channel7 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH0         (DSMU_FLTXSTS_CLKABF_0)     /* Clock absence event flag for channel0 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH1         (DSMU_FLTXSTS_CLKABF_1)     /* Clock absence event flag for channel1 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH2         (DSMU_FLTXSTS_CLKABF_2)     /* Clock absence event flag for channel2 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH3         (DSMU_FLTXSTS_CLKABF_3)     /* Clock absence event flag for channel3 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH4         (DSMU_FLTXSTS_CLKABF_4)     /* Clock absence event flag for channel4 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH5         (DSMU_FLTXSTS_CLKABF_5)     /* Clock absence event flag for channel5 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH6         (DSMU_FLTXSTS_CLKABF_6)     /* Clock absence event flag for channel6 */
#define DSMU_FLAG_CLOCK_ABSENCE_CH7         (DSMU_FLTXSTS_CLKABF_7)     /* Clock absence event flag for channel7 */
#define DSMU_FLAG_REGULAR_ACTIVE            (DSMU_FLTXSTS_RCIP)         /* Rugular conversion active flag */
#define DSMU_FLAG_INJECT_ACTIVE             (DSMU_FLTXSTS_JCIP)         /* Injected conversion active flag */
#define DSMU_FLAG_ANALOG_WATCHDOG           (DSMU_FLTXSTS_AWDF)         /* Analog watchdog event flag */
#define DSMU_FLAG_REGULAR_OVERRUN           (DSMU_FLTXSTS_ROVRF)        /* Regular conversion overrun flag */
#define DSMU_FLAG_INJECT_OVERRUN            (DSMU_FLTXSTS_JOVRF)        /* Injected conversion overrun flag */
#define DSMU_FLAG_REGULAR_END               (DSMU_FLTXSTS_REOCF)        /* Regular conversion end flag */
#define DSMU_FLAG_INJECT_END                (DSMU_FLTXSTS_JEOCF)        /* Injected conversion end flag */

/**  DSMU interrupt flag clear bit **/
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH0   (DSMU_FLTXINTCLR_CLRSCDETF_0)   /* Clear Short circuit event flag for channel0 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH1   (DSMU_FLTXINTCLR_CLRSCDETF_1)   /* Clear Short circuit event flag for channel1 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH2   (DSMU_FLTXINTCLR_CLRSCDETF_2)   /* Clear Short circuit event flag for channel2 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH3   (DSMU_FLTXINTCLR_CLRSCDETF_3)   /* Clear Short circuit event flag for channel3 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH4   (DSMU_FLTXINTCLR_CLRSCDETF_4)   /* Clear Short circuit event flag for channel4 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH5   (DSMU_FLTXINTCLR_CLRSCDETF_5)   /* Clear Short circuit event flag for channel5 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH6   (DSMU_FLTXINTCLR_CLRSCDETF_6)   /* Clear Short circuit event flag for channel6 */
#define DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH7   (DSMU_FLTXINTCLR_CLRSCDETF_7)   /* Clear Short circuit event flag for channel7 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH0   (DSMU_FLTXINTCLR_CLRCLKABF_0)   /* Clear Clock absence event flag for channel0 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH1   (DSMU_FLTXINTCLR_CLRCLKABF_1)   /* Clear Clock absence event flag for channel1 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH2   (DSMU_FLTXINTCLR_CLRCLKABF_2)   /* Clear Clock absence event flag for channel2 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH3   (DSMU_FLTXINTCLR_CLRCLKABF_3)   /* Clear Clock absence event flag for channel3 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH4   (DSMU_FLTXINTCLR_CLRCLKABF_4)   /* Clear Clock absence event flag for channel4 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH5   (DSMU_FLTXINTCLR_CLRCLKABF_5)   /* Clear Clock absence event flag for channel5 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH6   (DSMU_FLTXINTCLR_CLRCLKABF_6)   /* Clear Clock absence event flag for channel6 */
#define DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH7   (DSMU_FLTXINTCLR_CLRCLKABF_7)   /* Clear Clock absence event flag for channel7 */
#define DSMU_CLEAR_FLAG_REGULAR_OVERRUN     (DSMU_FLTXINTCLR_CLRROVRF)      /* Clear Regular conversion overrun flag */
#define DSMU_CLEAR_FLAG_INJECT_OVERRUN      (DSMU_FLTXINTCLR_CLRJOVRF)      /* Clear Injected conversion overrun flag */
#define DSMU_CLEAR_FLAG_ALL                 ( DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH0 | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH1 \
                                            | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH2 | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH3 \
                                            | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH4 | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH5 \
                                            | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH6 | DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH7 \
                                            | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH0 | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH1 \
                                            | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH2 | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH3 \
                                            | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH4 | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH5 \
                                            | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH6 | DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH7 \
                                            | DSMU_CLEAR_FLAG_REGULAR_OVERRUN   | DSMU_CLEAR_FLAG_INJECT_OVERRUN    )

/**  DSMU analog watchdog flag bit **/
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH0    (DSMU_FLTXAWDSTS_AWDHTF_0)  /* Analog wathcdog high threshold error flag for channel0 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH1    (DSMU_FLTXAWDSTS_AWDHTF_1)  /* Analog wathcdog high threshold error flag for channel1 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH2    (DSMU_FLTXAWDSTS_AWDHTF_2)  /* Analog wathcdog high threshold error flag for channel2 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH3    (DSMU_FLTXAWDSTS_AWDHTF_3)  /* Analog wathcdog high threshold error flag for channel3 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH4    (DSMU_FLTXAWDSTS_AWDHTF_4)  /* Analog wathcdog high threshold error flag for channel4 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH5    (DSMU_FLTXAWDSTS_AWDHTF_5)  /* Analog wathcdog high threshold error flag for channel5 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH6    (DSMU_FLTXAWDSTS_AWDHTF_6)  /* Analog wathcdog high threshold error flag for channel6 */
#define DSMU_AWD_FLAG_HIGH_THRESHOLD_CH7    (DSMU_FLTXAWDSTS_AWDHTF_7)  /* Analog wathcdog high threshold error flag for channel7 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH0     (DSMU_FLTXAWDSTS_AWDLTF_0)  /* Analog wathcdog low threshold error flag for channel0 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH1     (DSMU_FLTXAWDSTS_AWDLTF_1)  /* Analog wathcdog low threshold error flag for channel1 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH2     (DSMU_FLTXAWDSTS_AWDLTF_2)  /* Analog wathcdog low threshold error flag for channel2 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH3     (DSMU_FLTXAWDSTS_AWDLTF_3)  /* Analog wathcdog low threshold error flag for channel3 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH4     (DSMU_FLTXAWDSTS_AWDLTF_4)  /* Analog wathcdog low threshold error flag for channel4 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH5     (DSMU_FLTXAWDSTS_AWDLTF_5)  /* Analog wathcdog low threshold error flag for channel5 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH6     (DSMU_FLTXAWDSTS_AWDLTF_6)  /* Analog wathcdog low threshold error flag for channel6 */
#define DSMU_AWD_FLAG_LOW_THRESHOLD_CH7     (DSMU_FLTXAWDSTS_AWDLTF_7)  /* Analog wathcdog low threshold error flag for channel7 */

/**  DSMU analog watchdog flag clear bit **/
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH0  (DSMU_FLTXAWDCLR_CLRAWDHTF_0)   /* Clear Analog wathcdog high threshold error flag for channel0 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH1  (DSMU_FLTXAWDCLR_CLRAWDHTF_1)   /* Clear Analog wathcdog high threshold error flag for channel1 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH2  (DSMU_FLTXAWDCLR_CLRAWDHTF_2)   /* Clear Analog wathcdog high threshold error flag for channel2 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH3  (DSMU_FLTXAWDCLR_CLRAWDHTF_3)   /* Clear Analog wathcdog high threshold error flag for channel3 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH4  (DSMU_FLTXAWDCLR_CLRAWDHTF_4)   /* Clear Analog wathcdog high threshold error flag for channel4 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH5  (DSMU_FLTXAWDCLR_CLRAWDHTF_5)   /* Clear Analog wathcdog high threshold error flag for channel5 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH6  (DSMU_FLTXAWDCLR_CLRAWDHTF_6)   /* Clear Analog wathcdog high threshold error flag for channel6 */
#define DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH7  (DSMU_FLTXAWDCLR_CLRAWDHTF_7)   /* Clear Analog wathcdog high threshold error flag for channel7 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH0   (DSMU_FLTXAWDCLR_CLRAWDLTF_0)   /* Clear Analog wathcdog low threshold error flag for channel0 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH1   (DSMU_FLTXAWDCLR_CLRAWDLTF_1)   /* Clear Analog wathcdog low threshold error flag for channel1 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH2   (DSMU_FLTXAWDCLR_CLRAWDLTF_2)   /* Clear Analog wathcdog low threshold error flag for channel2 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH3   (DSMU_FLTXAWDCLR_CLRAWDLTF_3)   /* Clear Analog wathcdog low threshold error flag for channel3 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH4   (DSMU_FLTXAWDCLR_CLRAWDLTF_4)   /* Clear Analog wathcdog low threshold error flag for channel4 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH5   (DSMU_FLTXAWDCLR_CLRAWDLTF_5)   /* Clear Analog wathcdog low threshold error flag for channel5 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH6   (DSMU_FLTXAWDCLR_CLRAWDLTF_6)   /* Clear Analog wathcdog low threshold error flag for channel6 */
#define DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH7   (DSMU_FLTXAWDCLR_CLRAWDLTF_7)   /* Clear Analog wathcdog low threshold error flag for channel7 */
#define DSMU_CLEAR_AWD_FLAG_ALL                 ( DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH0 | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH1 \
                                                | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH2 | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH3 \
                                                | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH4 | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH5 \
                                                | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH6 | DSMU_CLEAR_AWD_FLAG_HIGH_THRESHOLD_CH7 \
                                                | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH0  | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH1 \
                                                | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH2  | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH3 \
                                                | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH4  | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH5 \
                                                | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH6  | DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH7)


void DSMU_DeInit(void);
void DSMU_InitChannelStruct(DSMU_Channel_InitType* DSMU_ChannelInitStruct);
void DSMU_InitFilterStruct(DSMU_Filter_InitType* DSMU_FilterInitStruct);
ErrorStatus DSMU_ChannelInit(DSMU_Channel_Submodule* DSMU_Channely, DSMU_Channel_InitType* DSMU_ChannelInitStruct);
void DSMU_ChannelDeInit(DSMU_Channel_Submodule* DSMU_Channely);
void DSMU_ChannelCkAbEnable(DSMU_Channel_Submodule* DSMU_Channely);
void DSMU_ChannelCkAbDisable(DSMU_Channel_Submodule* DSMU_Channely);
void DSMU_ChannelScdStart(DSMU_Channel_Submodule* DSMU_Channely,uint32_t Threshold, uint32_t BreakSignal);
void DSMU_ChannelScdStop(DSMU_Channel_Submodule* DSMU_Channely);
int16_t DSMU_ChannelGetAwdValue(const DSMU_Channel_Submodule* DSMU_Channely);
void DSMU_ChannelModifyOffset(DSMU_Channel_Submodule* DSMU_Channely, int32_t Offset);
void DSMU_ChannelWriteData(DSMU_Channel_Submodule* DSMU_Channely,uint32_t data);
ErrorStatus DSMU_FilterInit(DSMU_Filter_Submodule* DSMU_Filterx, DSMU_Filter_InitType* DSMU_FilterInitStruct);
void DSMU_FilterEnable(DSMU_Filter_Submodule* DSMU_Filterx, FunctionalState Cmd);
void DSMU_FilterConfigRegChannel(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t  ChannelSelect,uint32_t  ContinuousMode);
void DSMU_FilterConfigInjChannel(DSMU_Filter_Submodule* DSMU_Filterx,uint32_t ChannelSelect);
int32_t DSMU_FilterGetRegularValue(const DSMU_Filter_Submodule* DSMU_Filterx, uint32_t* Channel);
int32_t DSMU_FilterGetInjectedValue(const DSMU_Filter_Submodule* DSMU_Filterx,uint32_t* Channel);
void DSMU_FilterAwdStart(DSMU_Filter_Submodule* DSMU_Filterx, DSMU_Filter_AwdParamType* awdParam);
void DSMU_FilterAwdStop(DSMU_Filter_Submodule* DSMU_Filterx);
void DSMU_FilterExdStart(DSMU_Filter_Submodule* DSMU_Filterx,uint32_t ChannelSelect);
void DSMU_FilterExdStop(DSMU_Filter_Submodule* DSMU_Filterx);
int32_t DSMU_FilterGetExdMaxValue(const DSMU_Filter_Submodule* DSMU_Filterx,uint32_t* Channel);
int32_t DSMU_FilterGetExdMinValue(const DSMU_Filter_Submodule* DSMU_Filterx,uint32_t* Channel);
uint32_t DSMU_FilterGetConvTimeValue(const DSMU_Filter_Submodule* DSMU_Filterx);
void DSMU_RegConvStart(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger);
void DSMU_RegConvStop(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger);
void DSMU_InjConvStart(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger, uint32_t TiggerEdge);
void DSMU_InjConvStop(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger);
FlagStatus DSMU_GetFlagStatus(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_IntFlag);
void DSMU_ClearFlag(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_IntFlagClear);
FlagStatus DSMU_GetAwdFlagStatus(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_AwdFlag);
void DSMU_ClearAwdFlag(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_AwdFlagClear);
void DSMU_ConfigInt(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_Int, FunctionalState Cmd);
void DSMU_ConfigRegChDMA(DSMU_Filter_Submodule* DSMU_Filterx, FunctionalState Cmd);
void DSMU_ConfigInjChDMA(DSMU_Filter_Submodule* DSMU_Filterx, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /* N32H76x_78x_DSMU_H */

