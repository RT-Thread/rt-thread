/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for XBARB
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_XBARB.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for XBARB
 *
 * CMSIS Peripheral Access Layer for XBARB
 */

#if !defined(PERI_XBARB_H_)
#define PERI_XBARB_H_                            /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
#if !defined(XBAR_INPUT_SIGNAL_T_)
#define XBAR_INPUT_SIGNAL_T_
typedef enum _xbar_input_signal
{
    kXBARA1_InputLogicLow           = 0|0x100U,    /**< LOGIC_LOW output assigned to XBARA1_IN0 input. */
    kXBARA1_InputLogicHigh          = 1|0x100U,    /**< LOGIC_HIGH output assigned to XBARA1_IN1 input. */
    kXBARA1_InputRESERVED2          = 2|0x100U,    /**< XBARA1_IN2 input is reserved. */
    kXBARA1_InputRESERVED3          = 3|0x100U,    /**< XBARA1_IN3 input is reserved. */
    kXBARA1_InputIomuxXbarInout04   = 4|0x100U,    /**< IOMUX_XBAR_INOUT04 output assigned to XBARA1_IN4 input. */
    kXBARA1_InputIomuxXbarInout05   = 5|0x100U,    /**< IOMUX_XBAR_INOUT05 output assigned to XBARA1_IN5 input. */
    kXBARA1_InputIomuxXbarInout06   = 6|0x100U,    /**< IOMUX_XBAR_INOUT06 output assigned to XBARA1_IN6 input. */
    kXBARA1_InputIomuxXbarInout07   = 7|0x100U,    /**< IOMUX_XBAR_INOUT07 output assigned to XBARA1_IN7 input. */
    kXBARA1_InputIomuxXbarInout08   = 8|0x100U,    /**< IOMUX_XBAR_INOUT08 output assigned to XBARA1_IN8 input. */
    kXBARA1_InputIomuxXbarInout09   = 9|0x100U,    /**< IOMUX_XBAR_INOUT09 output assigned to XBARA1_IN9 input. */
    kXBARA1_InputIomuxXbarInout10   = 10|0x100U,   /**< IOMUX_XBAR_INOUT10 output assigned to XBARA1_IN10 input. */
    kXBARA1_InputIomuxXbarInout11   = 11|0x100U,   /**< IOMUX_XBAR_INOUT11 output assigned to XBARA1_IN11 input. */
    kXBARA1_InputIomuxXbarInout12   = 12|0x100U,   /**< IOMUX_XBAR_INOUT12 output assigned to XBARA1_IN12 input. */
    kXBARA1_InputIomuxXbarInout13   = 13|0x100U,   /**< IOMUX_XBAR_INOUT13 output assigned to XBARA1_IN13 input. */
    kXBARA1_InputIomuxXbarInout14   = 14|0x100U,   /**< IOMUX_XBAR_INOUT14 output assigned to XBARA1_IN14 input. */
    kXBARA1_InputIomuxXbarInout15   = 15|0x100U,   /**< IOMUX_XBAR_INOUT15 output assigned to XBARA1_IN15 input. */
    kXBARA1_InputIomuxXbarInout16   = 16|0x100U,   /**< IOMUX_XBAR_INOUT16 output assigned to XBARA1_IN16 input. */
    kXBARA1_InputIomuxXbarInout17   = 17|0x100U,   /**< IOMUX_XBAR_INOUT17 output assigned to XBARA1_IN17 input. */
    kXBARA1_InputIomuxXbarInout18   = 18|0x100U,   /**< IOMUX_XBAR_INOUT18 output assigned to XBARA1_IN18 input. */
    kXBARA1_InputIomuxXbarInout19   = 19|0x100U,   /**< IOMUX_XBAR_INOUT19 output assigned to XBARA1_IN19 input. */
    kXBARA1_InputIomuxXbarInout20   = 20|0x100U,   /**< IOMUX_XBAR_INOUT20 output assigned to XBARA1_IN20 input. */
    kXBARA1_InputIomuxXbarInout21   = 21|0x100U,   /**< IOMUX_XBAR_INOUT21 output assigned to XBARA1_IN21 input. */
    kXBARA1_InputIomuxXbarInout22   = 22|0x100U,   /**< IOMUX_XBAR_INOUT22 output assigned to XBARA1_IN22 input. */
    kXBARA1_InputIomuxXbarInout23   = 23|0x100U,   /**< IOMUX_XBAR_INOUT23 output assigned to XBARA1_IN23 input. */
    kXBARA1_InputIomuxXbarInout24   = 24|0x100U,   /**< IOMUX_XBAR_INOUT24 output assigned to XBARA1_IN24 input. */
    kXBARA1_InputIomuxXbarInout25   = 25|0x100U,   /**< IOMUX_XBAR_INOUT25 output assigned to XBARA1_IN25 input. */
    kXBARA1_InputIomuxXbarInout26   = 26|0x100U,   /**< IOMUX_XBAR_INOUT26 output assigned to XBARA1_IN26 input. */
    kXBARA1_InputIomuxXbarInout27   = 27|0x100U,   /**< IOMUX_XBAR_INOUT27 output assigned to XBARA1_IN27 input. */
    kXBARA1_InputIomuxXbarInout28   = 28|0x100U,   /**< IOMUX_XBAR_INOUT28 output assigned to XBARA1_IN28 input. */
    kXBARA1_InputIomuxXbarInout29   = 29|0x100U,   /**< IOMUX_XBAR_INOUT29 output assigned to XBARA1_IN29 input. */
    kXBARA1_InputIomuxXbarInout30   = 30|0x100U,   /**< IOMUX_XBAR_INOUT30 output assigned to XBARA1_IN30 input. */
    kXBARA1_InputIomuxXbarInout31   = 31|0x100U,   /**< IOMUX_XBAR_INOUT31 output assigned to XBARA1_IN31 input. */
    kXBARA1_InputIomuxXbarInout32   = 32|0x100U,   /**< IOMUX_XBAR_INOUT32 output assigned to XBARA1_IN32 input. */
    kXBARA1_InputIomuxXbarInout33   = 33|0x100U,   /**< IOMUX_XBAR_INOUT33 output assigned to XBARA1_IN33 input. */
    kXBARA1_InputIomuxXbarInout34   = 34|0x100U,   /**< IOMUX_XBAR_INOUT34 output assigned to XBARA1_IN34 input. */
    kXBARA1_InputIomuxXbarInout35   = 35|0x100U,   /**< IOMUX_XBAR_INOUT35 output assigned to XBARA1_IN35 input. */
    kXBARA1_InputIomuxXbarInout36   = 36|0x100U,   /**< IOMUX_XBAR_INOUT36 output assigned to XBARA1_IN36 input. */
    kXBARA1_InputIomuxXbarInout37   = 37|0x100U,   /**< IOMUX_XBAR_INOUT37 output assigned to XBARA1_IN37 input. */
    kXBARA1_InputIomuxXbarInout38   = 38|0x100U,   /**< IOMUX_XBAR_INOUT38 output assigned to XBARA1_IN38 input. */
    kXBARA1_InputIomuxXbarInout39   = 39|0x100U,   /**< IOMUX_XBAR_INOUT39 output assigned to XBARA1_IN39 input. */
    kXBARA1_InputIomuxXbarInout40   = 40|0x100U,   /**< IOMUX_XBAR_INOUT40 output assigned to XBARA1_IN40 input. */
    kXBARA1_InputRESERVED41         = 41|0x100U,   /**< XBARA1_IN41 input is reserved. */
    kXBARA1_InputAcmp1Out           = 42|0x100U,   /**< ACMP1_OUT output assigned to XBARA1_IN42 input. */
    kXBARA1_InputAcmp2Out           = 43|0x100U,   /**< ACMP2_OUT output assigned to XBARA1_IN43 input. */
    kXBARA1_InputAcmp3Out           = 44|0x100U,   /**< ACMP3_OUT output assigned to XBARA1_IN44 input. */
    kXBARA1_InputAcmp4Out           = 45|0x100U,   /**< ACMP4_OUT output assigned to XBARA1_IN45 input. */
    kXBARA1_InputRESERVED46         = 46|0x100U,   /**< XBARA1_IN46 input is reserved. */
    kXBARA1_InputRESERVED47         = 47|0x100U,   /**< XBARA1_IN47 input is reserved. */
    kXBARA1_InputRESERVED48         = 48|0x100U,   /**< XBARA1_IN48 input is reserved. */
    kXBARA1_InputRESERVED49         = 49|0x100U,   /**< XBARA1_IN49 input is reserved. */
    kXBARA1_InputQtimer1Timer0      = 50|0x100U,   /**< QTIMER1_TIMER0 output assigned to XBARA1_IN50 input. */
    kXBARA1_InputQtimer1Timer1      = 51|0x100U,   /**< QTIMER1_TIMER1 output assigned to XBARA1_IN51 input. */
    kXBARA1_InputQtimer1Timer2      = 52|0x100U,   /**< QTIMER1_TIMER2 output assigned to XBARA1_IN52 input. */
    kXBARA1_InputQtimer1Timer3      = 53|0x100U,   /**< QTIMER1_TIMER3 output assigned to XBARA1_IN53 input. */
    kXBARA1_InputQtimer2Timer0      = 54|0x100U,   /**< QTIMER2_TIMER0 output assigned to XBARA1_IN54 input. */
    kXBARA1_InputQtimer2Timer1      = 55|0x100U,   /**< QTIMER2_TIMER1 output assigned to XBARA1_IN55 input. */
    kXBARA1_InputQtimer2Timer2      = 56|0x100U,   /**< QTIMER2_TIMER2 output assigned to XBARA1_IN56 input. */
    kXBARA1_InputQtimer2Timer3      = 57|0x100U,   /**< QTIMER2_TIMER3 output assigned to XBARA1_IN57 input. */
    kXBARA1_InputQtimer3Timer0      = 58|0x100U,   /**< QTIMER3_TIMER0 output assigned to XBARA1_IN58 input. */
    kXBARA1_InputQtimer3Timer1      = 59|0x100U,   /**< QTIMER3_TIMER1 output assigned to XBARA1_IN59 input. */
    kXBARA1_InputQtimer3Timer2      = 60|0x100U,   /**< QTIMER3_TIMER2 output assigned to XBARA1_IN60 input. */
    kXBARA1_InputQtimer3Timer3      = 61|0x100U,   /**< QTIMER3_TIMER3 output assigned to XBARA1_IN61 input. */
    kXBARA1_InputQtimer4Timer0      = 62|0x100U,   /**< QTIMER4_TIMER0 output assigned to XBARA1_IN62 input. */
    kXBARA1_InputQtimer4Timer1      = 63|0x100U,   /**< QTIMER4_TIMER1 output assigned to XBARA1_IN63 input. */
    kXBARA1_InputQtimer4Timer2      = 64|0x100U,   /**< QTIMER4_TIMER2 output assigned to XBARA1_IN64 input. */
    kXBARA1_InputQtimer4Timer3      = 65|0x100U,   /**< QTIMER4_TIMER3 output assigned to XBARA1_IN65 input. */
    kXBARA1_InputRESERVED66         = 66|0x100U,   /**< XBARA1_IN66 input is reserved. */
    kXBARA1_InputRESERVED67         = 67|0x100U,   /**< XBARA1_IN67 input is reserved. */
    kXBARA1_InputRESERVED68         = 68|0x100U,   /**< XBARA1_IN68 input is reserved. */
    kXBARA1_InputRESERVED69         = 69|0x100U,   /**< XBARA1_IN69 input is reserved. */
    kXBARA1_InputRESERVED70         = 70|0x100U,   /**< XBARA1_IN70 input is reserved. */
    kXBARA1_InputRESERVED71         = 71|0x100U,   /**< XBARA1_IN71 input is reserved. */
    kXBARA1_InputRESERVED72         = 72|0x100U,   /**< XBARA1_IN72 input is reserved. */
    kXBARA1_InputRESERVED73         = 73|0x100U,   /**< XBARA1_IN73 input is reserved. */
    kXBARA1_InputFlexpwm1Pwm0OutTrig0 = 74|0x100U, /**< FLEXPWM1_PWM0_OUT_TRIG0 output assigned to XBARA1_IN74 input. */
    kXBARA1_InputFlexpwm1Pwm0OutTrig1 = 75|0x100U, /**< FLEXPWM1_PWM0_OUT_TRIG1 output assigned to XBARA1_IN75 input. */
    kXBARA1_InputFlexpwm1Pwm1OutTrig0 = 76|0x100U, /**< FLEXPWM1_PWM1_OUT_TRIG0 output assigned to XBARA1_IN76 input. */
    kXBARA1_InputFlexpwm1Pwm1OutTrig1 = 77|0x100U, /**< FLEXPWM1_PWM1_OUT_TRIG1 output assigned to XBARA1_IN77 input. */
    kXBARA1_InputFlexpwm1Pwm2OutTrig0 = 78|0x100U, /**< FLEXPWM1_PWM2_OUT_TRIG0 output assigned to XBARA1_IN78 input. */
    kXBARA1_InputFlexpwm1Pwm2OutTrig1 = 79|0x100U, /**< FLEXPWM1_PWM2_OUT_TRIG1 output assigned to XBARA1_IN79 input. */
    kXBARA1_InputFlexpwm1Pwm3OutTrig0 = 80|0x100U, /**< FLEXPWM1_PWM3_OUT_TRIG0 output assigned to XBARA1_IN80 input. */
    kXBARA1_InputFlexpwm1Pwm3OutTrig1 = 81|0x100U, /**< FLEXPWM1_PWM3_OUT_TRIG1 output assigned to XBARA1_IN81 input. */
    kXBARA1_InputFlexpwm2Pwm0OutTrig01 = 82|0x100U, /**< FLEXPWM2_PWM0_OUT_TRIG0_1 output assigned to XBARA1_IN82 input. */
    kXBARA1_InputFlexpwm2Pwm1OutTrig01 = 83|0x100U, /**< FLEXPWM2_PWM1_OUT_TRIG0_1 output assigned to XBARA1_IN83 input. */
    kXBARA1_InputFlexpwm2Pwm2OutTrig01 = 84|0x100U, /**< FLEXPWM2_PWM2_OUT_TRIG0_1 output assigned to XBARA1_IN84 input. */
    kXBARA1_InputFlexpwm2Pwm3OutTrig01 = 85|0x100U, /**< FLEXPWM2_PWM3_OUT_TRIG0_1 output assigned to XBARA1_IN85 input. */
    kXBARA1_InputFlexpwm3Pwm0OutTrig01 = 86|0x100U, /**< FLEXPWM3_PWM0_OUT_TRIG0_1 output assigned to XBARA1_IN86 input. */
    kXBARA1_InputFlexpwm3Pwm1OutTrig01 = 87|0x100U, /**< FLEXPWM3_PWM1_OUT_TRIG0_1 output assigned to XBARA1_IN87 input. */
    kXBARA1_InputFlexpwm3Pwm2OutTrig01 = 88|0x100U, /**< FLEXPWM3_PWM2_OUT_TRIG0_1 output assigned to XBARA1_IN88 input. */
    kXBARA1_InputFlexpwm3Pwm3OutTrig01 = 89|0x100U, /**< FLEXPWM3_PWM3_OUT_TRIG0_1 output assigned to XBARA1_IN89 input. */
    kXBARA1_InputFlexpwm4Pwm0OutTrig01 = 90|0x100U, /**< FLEXPWM4_PWM0_OUT_TRIG0_1 output assigned to XBARA1_IN90 input. */
    kXBARA1_InputFlexpwm4Pwm1OutTrig01 = 91|0x100U, /**< FLEXPWM4_PWM1_OUT_TRIG0_1 output assigned to XBARA1_IN91 input. */
    kXBARA1_InputFlexpwm4Pwm2OutTrig01 = 92|0x100U, /**< FLEXPWM4_PWM2_OUT_TRIG0_1 output assigned to XBARA1_IN92 input. */
    kXBARA1_InputFlexpwm4Pwm3OutTrig01 = 93|0x100U, /**< FLEXPWM4_PWM3_OUT_TRIG0_1 output assigned to XBARA1_IN93 input. */
    kXBARA1_InputRESERVED94         = 94|0x100U,   /**< XBARA1_IN94 input is reserved. */
    kXBARA1_InputRESERVED95         = 95|0x100U,   /**< XBARA1_IN95 input is reserved. */
    kXBARA1_InputRESERVED96         = 96|0x100U,   /**< XBARA1_IN96 input is reserved. */
    kXBARA1_InputRESERVED97         = 97|0x100U,   /**< XBARA1_IN97 input is reserved. */
    kXBARA1_InputRESERVED98         = 98|0x100U,   /**< XBARA1_IN98 input is reserved. */
    kXBARA1_InputRESERVED99         = 99|0x100U,   /**< XBARA1_IN99 input is reserved. */
    kXBARA1_InputRESERVED100        = 100|0x100U,  /**< XBARA1_IN100 input is reserved. */
    kXBARA1_InputRESERVED101        = 101|0x100U,  /**< XBARA1_IN101 input is reserved. */
    kXBARA1_InputPit1Trigger0       = 102|0x100U,  /**< PIT1_TRIGGER0 output assigned to XBARA1_IN102 input. */
    kXBARA1_InputPit1Trigger1       = 103|0x100U,  /**< PIT1_TRIGGER1 output assigned to XBARA1_IN103 input. */
    kXBARA1_InputPit1Trigger2       = 104|0x100U,  /**< PIT1_TRIGGER2 output assigned to XBARA1_IN104 input. */
    kXBARA1_InputPit1Trigger3       = 105|0x100U,  /**< PIT1_TRIGGER3 output assigned to XBARA1_IN105 input. */
    kXBARA1_InputDec1PosMatch       = 106|0x100U,  /**< DEC1_POS_MATCH output assigned to XBARA1_IN106 input. */
    kXBARA1_InputDec2PosMatch       = 107|0x100U,  /**< DEC2_POS_MATCH output assigned to XBARA1_IN107 input. */
    kXBARA1_InputDec3PosMatch       = 108|0x100U,  /**< DEC3_POS_MATCH output assigned to XBARA1_IN108 input. */
    kXBARA1_InputDec4PosMatch       = 109|0x100U,  /**< DEC4_POS_MATCH output assigned to XBARA1_IN109 input. */
    kXBARA1_InputRESERVED110        = 110|0x100U,  /**< XBARA1_IN110 input is reserved. */
    kXBARA1_InputRESERVED111        = 111|0x100U,  /**< XBARA1_IN111 input is reserved. */
    kXBARA1_InputDmaDone0           = 112|0x100U,  /**< DMA_DONE0 output assigned to XBARA1_IN112 input. */
    kXBARA1_InputDmaDone1           = 113|0x100U,  /**< DMA_DONE1 output assigned to XBARA1_IN113 input. */
    kXBARA1_InputDmaDone2           = 114|0x100U,  /**< DMA_DONE2 output assigned to XBARA1_IN114 input. */
    kXBARA1_InputDmaDone3           = 115|0x100U,  /**< DMA_DONE3 output assigned to XBARA1_IN115 input. */
    kXBARA1_InputDmaDone4           = 116|0x100U,  /**< DMA_DONE4 output assigned to XBARA1_IN116 input. */
    kXBARA1_InputDmaDone5           = 117|0x100U,  /**< DMA_DONE5 output assigned to XBARA1_IN117 input. */
    kXBARA1_InputDmaDone6           = 118|0x100U,  /**< DMA_DONE6 output assigned to XBARA1_IN118 input. */
    kXBARA1_InputDmaDone7           = 119|0x100U,  /**< DMA_DONE7 output assigned to XBARA1_IN119 input. */
    kXBARA1_InputDmaLpsrDone0       = 120|0x100U,  /**< DMA_LPSR_DONE0 output assigned to XBARA1_IN120 input. */
    kXBARA1_InputDmaLpsrDone1       = 121|0x100U,  /**< DMA_LPSR_DONE1 output assigned to XBARA1_IN121 input. */
    kXBARA1_InputDmaLpsrDone2       = 122|0x100U,  /**< DMA_LPSR_DONE2 output assigned to XBARA1_IN122 input. */
    kXBARA1_InputDmaLpsrDone3       = 123|0x100U,  /**< DMA_LPSR_DONE3 output assigned to XBARA1_IN123 input. */
    kXBARA1_InputDmaLpsrDone4       = 124|0x100U,  /**< DMA_LPSR_DONE4 output assigned to XBARA1_IN124 input. */
    kXBARA1_InputDmaLpsrDone5       = 125|0x100U,  /**< DMA_LPSR_DONE5 output assigned to XBARA1_IN125 input. */
    kXBARA1_InputDmaLpsrDone6       = 126|0x100U,  /**< DMA_LPSR_DONE6 output assigned to XBARA1_IN126 input. */
    kXBARA1_InputDmaLpsrDone7       = 127|0x100U,  /**< DMA_LPSR_DONE7 output assigned to XBARA1_IN127 input. */
    kXBARA1_InputAoi1Out0           = 128|0x100U,  /**< AOI1_OUT0 output assigned to XBARA1_IN128 input. */
    kXBARA1_InputAoi1Out1           = 129|0x100U,  /**< AOI1_OUT1 output assigned to XBARA1_IN129 input. */
    kXBARA1_InputAoi1Out2           = 130|0x100U,  /**< AOI1_OUT2 output assigned to XBARA1_IN130 input. */
    kXBARA1_InputAoi1Out3           = 131|0x100U,  /**< AOI1_OUT3 output assigned to XBARA1_IN131 input. */
    kXBARA1_InputAoi2Out0           = 132|0x100U,  /**< AOI2_OUT0 output assigned to XBARA1_IN132 input. */
    kXBARA1_InputAoi2Out1           = 133|0x100U,  /**< AOI2_OUT1 output assigned to XBARA1_IN133 input. */
    kXBARA1_InputAoi2Out2           = 134|0x100U,  /**< AOI2_OUT2 output assigned to XBARA1_IN134 input. */
    kXBARA1_InputAoi2Out3           = 135|0x100U,  /**< AOI2_OUT3 output assigned to XBARA1_IN135 input. */
    kXBARA1_InputAdcEtc0Coco0       = 136|0x100U,  /**< ADC_ETC0_COCO0 output assigned to XBARA1_IN136 input. */
    kXBARA1_InputAdcEtc0Coco1       = 137|0x100U,  /**< ADC_ETC0_COCO1 output assigned to XBARA1_IN137 input. */
    kXBARA1_InputAdcEtc0Coco2       = 138|0x100U,  /**< ADC_ETC0_COCO2 output assigned to XBARA1_IN138 input. */
    kXBARA1_InputAdcEtc0Coco3       = 139|0x100U,  /**< ADC_ETC0_COCO3 output assigned to XBARA1_IN139 input. */
    kXBARA1_InputAdcEtc1Coco0       = 140|0x100U,  /**< ADC_ETC1_COCO0 output assigned to XBARA1_IN140 input. */
    kXBARA1_InputAdcEtc1Coco1       = 141|0x100U,  /**< ADC_ETC1_COCO1 output assigned to XBARA1_IN141 input. */
    kXBARA1_InputAdcEtc1Coco2       = 142|0x100U,  /**< ADC_ETC1_COCO2 output assigned to XBARA1_IN142 input. */
    kXBARA1_InputAdcEtc1Coco3       = 143|0x100U,  /**< ADC_ETC1_COCO3 output assigned to XBARA1_IN143 input. */
    kXBARB2_InputLogicLow           = 0|0x200U,    /**< LOGIC_LOW output assigned to XBARB2_IN0 input. */
    kXBARB2_InputLogicHigh          = 1|0x200U,    /**< LOGIC_HIGH output assigned to XBARB2_IN1 input. */
    kXBARB2_InputAcmp1Out           = 2|0x200U,    /**< ACMP1_OUT output assigned to XBARB2_IN2 input. */
    kXBARB2_InputAcmp2Out           = 3|0x200U,    /**< ACMP2_OUT output assigned to XBARB2_IN3 input. */
    kXBARB2_InputAcmp3Out           = 4|0x200U,    /**< ACMP3_OUT output assigned to XBARB2_IN4 input. */
    kXBARB2_InputAcmp4Out           = 5|0x200U,    /**< ACMP4_OUT output assigned to XBARB2_IN5 input. */
    kXBARB2_InputRESERVED6          = 6|0x200U,    /**< XBARB2_IN6 input is reserved. */
    kXBARB2_InputRESERVED7          = 7|0x200U,    /**< XBARB2_IN7 input is reserved. */
    kXBARB2_InputRESERVED8          = 8|0x200U,    /**< XBARB2_IN8 input is reserved. */
    kXBARB2_InputRESERVED9          = 9|0x200U,    /**< XBARB2_IN9 input is reserved. */
    kXBARB2_InputQtimer1Timer0      = 10|0x200U,   /**< QTIMER1_TIMER0 output assigned to XBARB2_IN10 input. */
    kXBARB2_InputQtimer1Timer1      = 11|0x200U,   /**< QTIMER1_TIMER1 output assigned to XBARB2_IN11 input. */
    kXBARB2_InputQtimer1Timer2      = 12|0x200U,   /**< QTIMER1_TIMER2 output assigned to XBARB2_IN12 input. */
    kXBARB2_InputQtimer1Timer3      = 13|0x200U,   /**< QTIMER1_TIMER3 output assigned to XBARB2_IN13 input. */
    kXBARB2_InputQtimer2Timer0      = 14|0x200U,   /**< QTIMER2_TIMER0 output assigned to XBARB2_IN14 input. */
    kXBARB2_InputQtimer2Timer1      = 15|0x200U,   /**< QTIMER2_TIMER1 output assigned to XBARB2_IN15 input. */
    kXBARB2_InputQtimer2Timer2      = 16|0x200U,   /**< QTIMER2_TIMER2 output assigned to XBARB2_IN16 input. */
    kXBARB2_InputQtimer2Timer3      = 17|0x200U,   /**< QTIMER2_TIMER3 output assigned to XBARB2_IN17 input. */
    kXBARB2_InputQtimer3Timer0      = 18|0x200U,   /**< QTIMER3_TIMER0 output assigned to XBARB2_IN18 input. */
    kXBARB2_InputQtimer3Timer1      = 19|0x200U,   /**< QTIMER3_TIMER1 output assigned to XBARB2_IN19 input. */
    kXBARB2_InputQtimer3Timer2      = 20|0x200U,   /**< QTIMER3_TIMER2 output assigned to XBARB2_IN20 input. */
    kXBARB2_InputQtimer3Timer3      = 21|0x200U,   /**< QTIMER3_TIMER3 output assigned to XBARB2_IN21 input. */
    kXBARB2_InputQtimer4Timer0      = 22|0x200U,   /**< QTIMER4_TIMER0 output assigned to XBARB2_IN22 input. */
    kXBARB2_InputQtimer4Timer1      = 23|0x200U,   /**< QTIMER4_TIMER1 output assigned to XBARB2_IN23 input. */
    kXBARB2_InputQtimer4Timer2      = 24|0x200U,   /**< QTIMER4_TIMER2 output assigned to XBARB2_IN24 input. */
    kXBARB2_InputQtimer4Timer3      = 25|0x200U,   /**< QTIMER4_TIMER3 output assigned to XBARB2_IN25 input. */
    kXBARB2_InputRESERVED26         = 26|0x200U,   /**< XBARB2_IN26 input is reserved. */
    kXBARB2_InputRESERVED27         = 27|0x200U,   /**< XBARB2_IN27 input is reserved. */
    kXBARB2_InputRESERVED28         = 28|0x200U,   /**< XBARB2_IN28 input is reserved. */
    kXBARB2_InputRESERVED29         = 29|0x200U,   /**< XBARB2_IN29 input is reserved. */
    kXBARB2_InputRESERVED30         = 30|0x200U,   /**< XBARB2_IN30 input is reserved. */
    kXBARB2_InputRESERVED31         = 31|0x200U,   /**< XBARB2_IN31 input is reserved. */
    kXBARB2_InputRESERVED32         = 32|0x200U,   /**< XBARB2_IN32 input is reserved. */
    kXBARB2_InputRESERVED33         = 33|0x200U,   /**< XBARB2_IN33 input is reserved. */
    kXBARB2_InputFlexpwm1Pwm0OutTrig01 = 34|0x200U, /**< FLEXPWM1_PWM0_OUT_TRIG0_1 output assigned to XBARB2_IN34 input. */
    kXBARB2_InputFlexpwm1Pwm1OutTrig01 = 35|0x200U, /**< FLEXPWM1_PWM1_OUT_TRIG0_1 output assigned to XBARB2_IN35 input. */
    kXBARB2_InputFlexpwm1Pwm2OutTrig01 = 36|0x200U, /**< FLEXPWM1_PWM2_OUT_TRIG0_1 output assigned to XBARB2_IN36 input. */
    kXBARB2_InputFlexpwm1Pwm3OutTrig01 = 37|0x200U, /**< FLEXPWM1_PWM3_OUT_TRIG0_1 output assigned to XBARB2_IN37 input. */
    kXBARB2_InputFlexpwm2Pwm0OutTrig01 = 38|0x200U, /**< FLEXPWM2_PWM0_OUT_TRIG0_1 output assigned to XBARB2_IN38 input. */
    kXBARB2_InputFlexpwm2Pwm1OutTrig01 = 39|0x200U, /**< FLEXPWM2_PWM1_OUT_TRIG0_1 output assigned to XBARB2_IN39 input. */
    kXBARB2_InputFlexpwm2Pwm2OutTrig01 = 40|0x200U, /**< FLEXPWM2_PWM2_OUT_TRIG0_1 output assigned to XBARB2_IN40 input. */
    kXBARB2_InputFlexpwm2Pwm3OutTrig01 = 41|0x200U, /**< FLEXPWM2_PWM3_OUT_TRIG0_1 output assigned to XBARB2_IN41 input. */
    kXBARB2_InputFlexpwm3Pwm0OutTrig01 = 42|0x200U, /**< FLEXPWM3_PWM0_OUT_TRIG0_1 output assigned to XBARB2_IN42 input. */
    kXBARB2_InputFlexpwm3Pwm1OutTrig01 = 43|0x200U, /**< FLEXPWM3_PWM1_OUT_TRIG0_1 output assigned to XBARB2_IN43 input. */
    kXBARB2_InputFlexpwm3Pwm2OutTrig01 = 44|0x200U, /**< FLEXPWM3_PWM2_OUT_TRIG0_1 output assigned to XBARB2_IN44 input. */
    kXBARB2_InputFlexpwm3Pwm3OutTrig01 = 45|0x200U, /**< FLEXPWM3_PWM3_OUT_TRIG0_1 output assigned to XBARB2_IN45 input. */
    kXBARB2_InputFlexpwm4Pwm0OutTrig01 = 46|0x200U, /**< FLEXPWM4_PWM0_OUT_TRIG0_1 output assigned to XBARB2_IN46 input. */
    kXBARB2_InputFlexpwm4Pwm1OutTrig01 = 47|0x200U, /**< FLEXPWM4_PWM1_OUT_TRIG0_1 output assigned to XBARB2_IN47 input. */
    kXBARB2_InputFlexpwm4Pwm2OutTrig01 = 48|0x200U, /**< FLEXPWM4_PWM2_OUT_TRIG0_1 output assigned to XBARB2_IN48 input. */
    kXBARB2_InputFlexpwm4Pwm3OutTrig01 = 49|0x200U, /**< FLEXPWM4_PWM3_OUT_TRIG0_1 output assigned to XBARB2_IN49 input. */
    kXBARB2_InputRESERVED50         = 50|0x200U,   /**< XBARB2_IN50 input is reserved. */
    kXBARB2_InputRESERVED51         = 51|0x200U,   /**< XBARB2_IN51 input is reserved. */
    kXBARB2_InputRESERVED52         = 52|0x200U,   /**< XBARB2_IN52 input is reserved. */
    kXBARB2_InputRESERVED53         = 53|0x200U,   /**< XBARB2_IN53 input is reserved. */
    kXBARB2_InputRESERVED54         = 54|0x200U,   /**< XBARB2_IN54 input is reserved. */
    kXBARB2_InputRESERVED55         = 55|0x200U,   /**< XBARB2_IN55 input is reserved. */
    kXBARB2_InputRESERVED56         = 56|0x200U,   /**< XBARB2_IN56 input is reserved. */
    kXBARB2_InputRESERVED57         = 57|0x200U,   /**< XBARB2_IN57 input is reserved. */
    kXBARB2_InputPit1Trigger0       = 58|0x200U,   /**< PIT1_TRIGGER0 output assigned to XBARB2_IN58 input. */
    kXBARB2_InputPit1Trigger1       = 59|0x200U,   /**< PIT1_TRIGGER1 output assigned to XBARB2_IN59 input. */
    kXBARB2_InputAdcEtc0Coco0       = 60|0x200U,   /**< ADC_ETC0_COCO0 output assigned to XBARB2_IN60 input. */
    kXBARB2_InputAdcEtc0Coco1       = 61|0x200U,   /**< ADC_ETC0_COCO1 output assigned to XBARB2_IN61 input. */
    kXBARB2_InputAdcEtc0Coco2       = 62|0x200U,   /**< ADC_ETC0_COCO2 output assigned to XBARB2_IN62 input. */
    kXBARB2_InputAdcEtc0Coco3       = 63|0x200U,   /**< ADC_ETC0_COCO3 output assigned to XBARB2_IN63 input. */
    kXBARB2_InputAdcEtc1Coco0       = 64|0x200U,   /**< ADC_ETC1_COCO0 output assigned to XBARB2_IN64 input. */
    kXBARB2_InputAdcEtc1Coco1       = 65|0x200U,   /**< ADC_ETC1_COCO1 output assigned to XBARB2_IN65 input. */
    kXBARB2_InputAdcEtc1Coco2       = 66|0x200U,   /**< ADC_ETC1_COCO2 output assigned to XBARB2_IN66 input. */
    kXBARB2_InputAdcEtc1Coco3       = 67|0x200U,   /**< ADC_ETC1_COCO3 output assigned to XBARB2_IN67 input. */
    kXBARB2_InputRESERVED68         = 68|0x200U,   /**< XBARB2_IN68 input is reserved. */
    kXBARB2_InputRESERVED69         = 69|0x200U,   /**< XBARB2_IN69 input is reserved. */
    kXBARB2_InputRESERVED70         = 70|0x200U,   /**< XBARB2_IN70 input is reserved. */
    kXBARB2_InputRESERVED71         = 71|0x200U,   /**< XBARB2_IN71 input is reserved. */
    kXBARB2_InputRESERVED72         = 72|0x200U,   /**< XBARB2_IN72 input is reserved. */
    kXBARB2_InputRESERVED73         = 73|0x200U,   /**< XBARB2_IN73 input is reserved. */
    kXBARB2_InputRESERVED74         = 74|0x200U,   /**< XBARB2_IN74 input is reserved. */
    kXBARB2_InputRESERVED75         = 75|0x200U,   /**< XBARB2_IN75 input is reserved. */
    kXBARB2_InputDec1PosMatch       = 76|0x200U,   /**< DEC1_POS_MATCH output assigned to XBARB2_IN76 input. */
    kXBARB2_InputDec2PosMatch       = 77|0x200U,   /**< DEC2_POS_MATCH output assigned to XBARB2_IN77 input. */
    kXBARB2_InputDec3PosMatch       = 78|0x200U,   /**< DEC3_POS_MATCH output assigned to XBARB2_IN78 input. */
    kXBARB2_InputDec4PosMatch       = 79|0x200U,   /**< DEC4_POS_MATCH output assigned to XBARB2_IN79 input. */
    kXBARB2_InputRESERVED80         = 80|0x200U,   /**< XBARB2_IN80 input is reserved. */
    kXBARB2_InputRESERVED81         = 81|0x200U,   /**< XBARB2_IN81 input is reserved. */
    kXBARB2_InputDmaDone0           = 82|0x200U,   /**< DMA_DONE0 output assigned to XBARB2_IN82 input. */
    kXBARB2_InputDmaDone1           = 83|0x200U,   /**< DMA_DONE1 output assigned to XBARB2_IN83 input. */
    kXBARB2_InputDmaDone2           = 84|0x200U,   /**< DMA_DONE2 output assigned to XBARB2_IN84 input. */
    kXBARB2_InputDmaDone3           = 85|0x200U,   /**< DMA_DONE3 output assigned to XBARB2_IN85 input. */
    kXBARB2_InputDmaDone4           = 86|0x200U,   /**< DMA_DONE4 output assigned to XBARB2_IN86 input. */
    kXBARB2_InputDmaDone5           = 87|0x200U,   /**< DMA_DONE5 output assigned to XBARB2_IN87 input. */
    kXBARB2_InputDmaDone6           = 88|0x200U,   /**< DMA_DONE6 output assigned to XBARB2_IN88 input. */
    kXBARB2_InputDmaDone7           = 89|0x200U,   /**< DMA_DONE7 output assigned to XBARB2_IN89 input. */
    kXBARB2_InputDmaLpsrDone0       = 90|0x200U,   /**< DMA_LPSR_DONE0 output assigned to XBARB2_IN90 input. */
    kXBARB2_InputDmaLpsrDone1       = 91|0x200U,   /**< DMA_LPSR_DONE1 output assigned to XBARB2_IN91 input. */
    kXBARB2_InputDmaLpsrDone2       = 92|0x200U,   /**< DMA_LPSR_DONE2 output assigned to XBARB2_IN92 input. */
    kXBARB2_InputDmaLpsrDone3       = 93|0x200U,   /**< DMA_LPSR_DONE3 output assigned to XBARB2_IN93 input. */
    kXBARB2_InputDmaLpsrDone4       = 94|0x200U,   /**< DMA_LPSR_DONE4 output assigned to XBARB2_IN94 input. */
    kXBARB2_InputDmaLpsrDone5       = 95|0x200U,   /**< DMA_LPSR_DONE5 output assigned to XBARB2_IN95 input. */
    kXBARB2_InputDmaLpsrDone6       = 96|0x200U,   /**< DMA_LPSR_DONE6 output assigned to XBARB2_IN96 input. */
    kXBARB2_InputDmaLpsrDone7       = 97|0x200U,   /**< DMA_LPSR_DONE7 output assigned to XBARB2_IN97 input. */
    kXBARB3_InputLogicLow           = 0|0x300U,    /**< LOGIC_LOW output assigned to XBARB3_IN0 input. */
    kXBARB3_InputLogicHigh          = 1|0x300U,    /**< LOGIC_HIGH output assigned to XBARB3_IN1 input. */
    kXBARB3_InputAcmp1Out           = 2|0x300U,    /**< ACMP1_OUT output assigned to XBARB3_IN2 input. */
    kXBARB3_InputAcmp2Out           = 3|0x300U,    /**< ACMP2_OUT output assigned to XBARB3_IN3 input. */
    kXBARB3_InputAcmp3Out           = 4|0x300U,    /**< ACMP3_OUT output assigned to XBARB3_IN4 input. */
    kXBARB3_InputAcmp4Out           = 5|0x300U,    /**< ACMP4_OUT output assigned to XBARB3_IN5 input. */
    kXBARB3_InputRESERVED6          = 6|0x300U,    /**< XBARB3_IN6 input is reserved. */
    kXBARB3_InputRESERVED7          = 7|0x300U,    /**< XBARB3_IN7 input is reserved. */
    kXBARB3_InputRESERVED8          = 8|0x300U,    /**< XBARB3_IN8 input is reserved. */
    kXBARB3_InputRESERVED9          = 9|0x300U,    /**< XBARB3_IN9 input is reserved. */
    kXBARB3_InputQtimer1Timer0      = 10|0x300U,   /**< QTIMER1_TIMER0 output assigned to XBARB3_IN10 input. */
    kXBARB3_InputQtimer1Timer1      = 11|0x300U,   /**< QTIMER1_TIMER1 output assigned to XBARB3_IN11 input. */
    kXBARB3_InputQtimer1Timer2      = 12|0x300U,   /**< QTIMER1_TIMER2 output assigned to XBARB3_IN12 input. */
    kXBARB3_InputQtimer1Timer3      = 13|0x300U,   /**< QTIMER1_TIMER3 output assigned to XBARB3_IN13 input. */
    kXBARB3_InputQtimer2Timer0      = 14|0x300U,   /**< QTIMER2_TIMER0 output assigned to XBARB3_IN14 input. */
    kXBARB3_InputQtimer2Timer1      = 15|0x300U,   /**< QTIMER2_TIMER1 output assigned to XBARB3_IN15 input. */
    kXBARB3_InputQtimer2Timer2      = 16|0x300U,   /**< QTIMER2_TIMER2 output assigned to XBARB3_IN16 input. */
    kXBARB3_InputQtimer2Timer3      = 17|0x300U,   /**< QTIMER2_TIMER3 output assigned to XBARB3_IN17 input. */
    kXBARB3_InputQtimer3Timer0      = 18|0x300U,   /**< QTIMER3_TIMER0 output assigned to XBARB3_IN18 input. */
    kXBARB3_InputQtimer3Timer1      = 19|0x300U,   /**< QTIMER3_TIMER1 output assigned to XBARB3_IN19 input. */
    kXBARB3_InputQtimer3Timer2      = 20|0x300U,   /**< QTIMER3_TIMER2 output assigned to XBARB3_IN20 input. */
    kXBARB3_InputQtimer3Timer3      = 21|0x300U,   /**< QTIMER3_TIMER3 output assigned to XBARB3_IN21 input. */
    kXBARB3_InputQtimer4Timer0      = 22|0x300U,   /**< QTIMER4_TIMER0 output assigned to XBARB3_IN22 input. */
    kXBARB3_InputQtimer4Timer1      = 23|0x300U,   /**< QTIMER4_TIMER1 output assigned to XBARB3_IN23 input. */
    kXBARB3_InputQtimer4Timer2      = 24|0x300U,   /**< QTIMER4_TIMER2 output assigned to XBARB3_IN24 input. */
    kXBARB3_InputQtimer4Timer3      = 25|0x300U,   /**< QTIMER4_TIMER3 output assigned to XBARB3_IN25 input. */
    kXBARB3_InputRESERVED26         = 26|0x300U,   /**< XBARB3_IN26 input is reserved. */
    kXBARB3_InputRESERVED27         = 27|0x300U,   /**< XBARB3_IN27 input is reserved. */
    kXBARB3_InputRESERVED28         = 28|0x300U,   /**< XBARB3_IN28 input is reserved. */
    kXBARB3_InputRESERVED29         = 29|0x300U,   /**< XBARB3_IN29 input is reserved. */
    kXBARB3_InputRESERVED30         = 30|0x300U,   /**< XBARB3_IN30 input is reserved. */
    kXBARB3_InputRESERVED31         = 31|0x300U,   /**< XBARB3_IN31 input is reserved. */
    kXBARB3_InputRESERVED32         = 32|0x300U,   /**< XBARB3_IN32 input is reserved. */
    kXBARB3_InputRESERVED33         = 33|0x300U,   /**< XBARB3_IN33 input is reserved. */
    kXBARB3_InputFlexpwm1Pwm0OutTrig01 = 34|0x300U, /**< FLEXPWM1_PWM0_OUT_TRIG0_1 output assigned to XBARB3_IN34 input. */
    kXBARB3_InputFlexpwm1Pwm1OutTrig01 = 35|0x300U, /**< FLEXPWM1_PWM1_OUT_TRIG0_1 output assigned to XBARB3_IN35 input. */
    kXBARB3_InputFlexpwm1Pwm2OutTrig01 = 36|0x300U, /**< FLEXPWM1_PWM2_OUT_TRIG0_1 output assigned to XBARB3_IN36 input. */
    kXBARB3_InputFlexpwm1Pwm3OutTrig01 = 37|0x300U, /**< FLEXPWM1_PWM3_OUT_TRIG0_1 output assigned to XBARB3_IN37 input. */
    kXBARB3_InputFlexpwm2Pwm0OutTrig01 = 38|0x300U, /**< FLEXPWM2_PWM0_OUT_TRIG0_1 output assigned to XBARB3_IN38 input. */
    kXBARB3_InputFlexpwm2Pwm1OutTrig01 = 39|0x300U, /**< FLEXPWM2_PWM1_OUT_TRIG0_1 output assigned to XBARB3_IN39 input. */
    kXBARB3_InputFlexpwm2Pwm2OutTrig01 = 40|0x300U, /**< FLEXPWM2_PWM2_OUT_TRIG0_1 output assigned to XBARB3_IN40 input. */
    kXBARB3_InputFlexpwm2Pwm3OutTrig01 = 41|0x300U, /**< FLEXPWM2_PWM3_OUT_TRIG0_1 output assigned to XBARB3_IN41 input. */
    kXBARB3_InputFlexpwm3Pwm0OutTrig01 = 42|0x300U, /**< FLEXPWM3_PWM0_OUT_TRIG0_1 output assigned to XBARB3_IN42 input. */
    kXBARB3_InputFlexpwm3Pwm1OutTrig01 = 43|0x300U, /**< FLEXPWM3_PWM1_OUT_TRIG0_1 output assigned to XBARB3_IN43 input. */
    kXBARB3_InputFlexpwm3Pwm2OutTrig01 = 44|0x300U, /**< FLEXPWM3_PWM2_OUT_TRIG0_1 output assigned to XBARB3_IN44 input. */
    kXBARB3_InputFlexpwm3Pwm3OutTrig01 = 45|0x300U, /**< FLEXPWM3_PWM3_OUT_TRIG0_1 output assigned to XBARB3_IN45 input. */
    kXBARB3_InputFlexpwm4Pwm0OutTrig01 = 46|0x300U, /**< FLEXPWM4_PWM0_OUT_TRIG0_1 output assigned to XBARB3_IN46 input. */
    kXBARB3_InputFlexpwm4Pwm1OutTrig01 = 47|0x300U, /**< FLEXPWM4_PWM1_OUT_TRIG0_1 output assigned to XBARB3_IN47 input. */
    kXBARB3_InputFlexpwm4Pwm2OutTrig01 = 48|0x300U, /**< FLEXPWM4_PWM2_OUT_TRIG0_1 output assigned to XBARB3_IN48 input. */
    kXBARB3_InputFlexpwm4Pwm3OutTrig01 = 49|0x300U, /**< FLEXPWM4_PWM3_OUT_TRIG0_1 output assigned to XBARB3_IN49 input. */
    kXBARB3_InputRESERVED50         = 50|0x300U,   /**< XBARB3_IN50 input is reserved. */
    kXBARB3_InputRESERVED51         = 51|0x300U,   /**< XBARB3_IN51 input is reserved. */
    kXBARB3_InputRESERVED52         = 52|0x300U,   /**< XBARB3_IN52 input is reserved. */
    kXBARB3_InputRESERVED53         = 53|0x300U,   /**< XBARB3_IN53 input is reserved. */
    kXBARB3_InputRESERVED54         = 54|0x300U,   /**< XBARB3_IN54 input is reserved. */
    kXBARB3_InputRESERVED55         = 55|0x300U,   /**< XBARB3_IN55 input is reserved. */
    kXBARB3_InputRESERVED56         = 56|0x300U,   /**< XBARB3_IN56 input is reserved. */
    kXBARB3_InputRESERVED57         = 57|0x300U,   /**< XBARB3_IN57 input is reserved. */
    kXBARB3_InputPit1Trigger0       = 58|0x300U,   /**< PIT1_TRIGGER0 output assigned to XBARB3_IN58 input. */
    kXBARB3_InputPit1Trigger1       = 59|0x300U,   /**< PIT1_TRIGGER1 output assigned to XBARB3_IN59 input. */
    kXBARB3_InputAdcEtc0Coco0       = 60|0x300U,   /**< ADC_ETC0_COCO0 output assigned to XBARB3_IN60 input. */
    kXBARB3_InputAdcEtc0Coco1       = 61|0x300U,   /**< ADC_ETC0_COCO1 output assigned to XBARB3_IN61 input. */
    kXBARB3_InputAdcEtc0Coco2       = 62|0x300U,   /**< ADC_ETC0_COCO2 output assigned to XBARB3_IN62 input. */
    kXBARB3_InputAdcEtc0Coco3       = 63|0x300U,   /**< ADC_ETC0_COCO3 output assigned to XBARB3_IN63 input. */
    kXBARB3_InputAdcEtc1Coco0       = 64|0x300U,   /**< ADC_ETC1_COCO0 output assigned to XBARB3_IN64 input. */
    kXBARB3_InputAdcEtc1Coco1       = 65|0x300U,   /**< ADC_ETC1_COCO1 output assigned to XBARB3_IN65 input. */
    kXBARB3_InputAdcEtc1Coco2       = 66|0x300U,   /**< ADC_ETC1_COCO2 output assigned to XBARB3_IN66 input. */
    kXBARB3_InputAdcEtc1Coco3       = 67|0x300U,   /**< ADC_ETC1_COCO3 output assigned to XBARB3_IN67 input. */
    kXBARB3_InputRESERVED68         = 68|0x300U,   /**< XBARB3_IN68 input is reserved. */
    kXBARB3_InputRESERVED69         = 69|0x300U,   /**< XBARB3_IN69 input is reserved. */
    kXBARB3_InputRESERVED70         = 70|0x300U,   /**< XBARB3_IN70 input is reserved. */
    kXBARB3_InputRESERVED71         = 71|0x300U,   /**< XBARB3_IN71 input is reserved. */
    kXBARB3_InputRESERVED72         = 72|0x300U,   /**< XBARB3_IN72 input is reserved. */
    kXBARB3_InputRESERVED73         = 73|0x300U,   /**< XBARB3_IN73 input is reserved. */
    kXBARB3_InputRESERVED74         = 74|0x300U,   /**< XBARB3_IN74 input is reserved. */
    kXBARB3_InputRESERVED75         = 75|0x300U,   /**< XBARB3_IN75 input is reserved. */
    kXBARB3_InputDec1PosMatch       = 76|0x300U,   /**< DEC1_POS_MATCH output assigned to XBARB3_IN76 input. */
    kXBARB3_InputDec2PosMatch       = 77|0x300U,   /**< DEC2_POS_MATCH output assigned to XBARB3_IN77 input. */
    kXBARB3_InputDec3PosMatch       = 78|0x300U,   /**< DEC3_POS_MATCH output assigned to XBARB3_IN78 input. */
    kXBARB3_InputDec4PosMatch       = 79|0x300U,   /**< DEC4_POS_MATCH output assigned to XBARB3_IN79 input. */
    kXBARB3_InputRESERVED80         = 80|0x300U,   /**< XBARB3_IN80 input is reserved. */
    kXBARB3_InputRESERVED81         = 81|0x300U,   /**< XBARB3_IN81 input is reserved. */
    kXBARB3_InputDmaDone0           = 82|0x300U,   /**< DMA_DONE0 output assigned to XBARB3_IN82 input. */
    kXBARB3_InputDmaDone1           = 83|0x300U,   /**< DMA_DONE1 output assigned to XBARB3_IN83 input. */
    kXBARB3_InputDmaDone2           = 84|0x300U,   /**< DMA_DONE2 output assigned to XBARB3_IN84 input. */
    kXBARB3_InputDmaDone3           = 85|0x300U,   /**< DMA_DONE3 output assigned to XBARB3_IN85 input. */
    kXBARB3_InputDmaDone4           = 86|0x300U,   /**< DMA_DONE4 output assigned to XBARB3_IN86 input. */
    kXBARB3_InputDmaDone5           = 87|0x300U,   /**< DMA_DONE5 output assigned to XBARB3_IN87 input. */
    kXBARB3_InputDmaDone6           = 88|0x300U,   /**< DMA_DONE6 output assigned to XBARB3_IN88 input. */
    kXBARB3_InputDmaDone7           = 89|0x300U,   /**< DMA_DONE7 output assigned to XBARB3_IN89 input. */
    kXBARB3_InputDmaLpsrDone0       = 90|0x300U,   /**< DMA_LPSR_DONE0 output assigned to XBARB3_IN90 input. */
    kXBARB3_InputDmaLpsrDone1       = 91|0x300U,   /**< DMA_LPSR_DONE1 output assigned to XBARB3_IN91 input. */
    kXBARB3_InputDmaLpsrDone2       = 92|0x300U,   /**< DMA_LPSR_DONE2 output assigned to XBARB3_IN92 input. */
    kXBARB3_InputDmaLpsrDone3       = 93|0x300U,   /**< DMA_LPSR_DONE3 output assigned to XBARB3_IN93 input. */
    kXBARB3_InputDmaLpsrDone4       = 94|0x300U,   /**< DMA_LPSR_DONE4 output assigned to XBARB3_IN94 input. */
    kXBARB3_InputDmaLpsrDone5       = 95|0x300U,   /**< DMA_LPSR_DONE5 output assigned to XBARB3_IN95 input. */
    kXBARB3_InputDmaLpsrDone6       = 96|0x300U,   /**< DMA_LPSR_DONE6 output assigned to XBARB3_IN96 input. */
    kXBARB3_InputDmaLpsrDone7       = 97|0x300U,   /**< DMA_LPSR_DONE7 output assigned to XBARB3_IN97 input. */
} xbar_input_signal_t;
#endif /* XBAR_INPUT_SIGNAL_T_ */

#if !defined(XBAR_OUTPUT_SIGNAL_T_)
#define XBAR_OUTPUT_SIGNAL_T_
typedef enum _xbar_output_signal
{
    kXBARA1_OutputDmaChMuxReq81     = 0|0x100U,    /**< XBARA1_OUT0 output assigned to DMA_CH_MUX_REQ81 */
    kXBARA1_OutputDmaChMuxReq82     = 1|0x100U,    /**< XBARA1_OUT1 output assigned to DMA_CH_MUX_REQ82 */
    kXBARA1_OutputDmaChMuxReq83     = 2|0x100U,    /**< XBARA1_OUT2 output assigned to DMA_CH_MUX_REQ83 */
    kXBARA1_OutputDmaChMuxReq84     = 3|0x100U,    /**< XBARA1_OUT3 output assigned to DMA_CH_MUX_REQ84 */
    kXBARA1_OutputIomuxXbarInout04  = 4|0x100U,    /**< XBARA1_OUT4 output assigned to IOMUX_XBAR_INOUT04 */
    kXBARA1_OutputIomuxXbarInout05  = 5|0x100U,    /**< XBARA1_OUT5 output assigned to IOMUX_XBAR_INOUT05 */
    kXBARA1_OutputIomuxXbarInout06  = 6|0x100U,    /**< XBARA1_OUT6 output assigned to IOMUX_XBAR_INOUT06 */
    kXBARA1_OutputIomuxXbarInout07  = 7|0x100U,    /**< XBARA1_OUT7 output assigned to IOMUX_XBAR_INOUT07 */
    kXBARA1_OutputIomuxXbarInout08  = 8|0x100U,    /**< XBARA1_OUT8 output assigned to IOMUX_XBAR_INOUT08 */
    kXBARA1_OutputIomuxXbarInout09  = 9|0x100U,    /**< XBARA1_OUT9 output assigned to IOMUX_XBAR_INOUT09 */
    kXBARA1_OutputIomuxXbarInout10  = 10|0x100U,   /**< XBARA1_OUT10 output assigned to IOMUX_XBAR_INOUT10 */
    kXBARA1_OutputIomuxXbarInout11  = 11|0x100U,   /**< XBARA1_OUT11 output assigned to IOMUX_XBAR_INOUT11 */
    kXBARA1_OutputIomuxXbarInout12  = 12|0x100U,   /**< XBARA1_OUT12 output assigned to IOMUX_XBAR_INOUT12 */
    kXBARA1_OutputIomuxXbarInout13  = 13|0x100U,   /**< XBARA1_OUT13 output assigned to IOMUX_XBAR_INOUT13 */
    kXBARA1_OutputIomuxXbarInout14  = 14|0x100U,   /**< XBARA1_OUT14 output assigned to IOMUX_XBAR_INOUT14 */
    kXBARA1_OutputIomuxXbarInout15  = 15|0x100U,   /**< XBARA1_OUT15 output assigned to IOMUX_XBAR_INOUT15 */
    kXBARA1_OutputIomuxXbarInout16  = 16|0x100U,   /**< XBARA1_OUT16 output assigned to IOMUX_XBAR_INOUT16 */
    kXBARA1_OutputIomuxXbarInout17  = 17|0x100U,   /**< XBARA1_OUT17 output assigned to IOMUX_XBAR_INOUT17 */
    kXBARA1_OutputIomuxXbarInout18  = 18|0x100U,   /**< XBARA1_OUT18 output assigned to IOMUX_XBAR_INOUT18 */
    kXBARA1_OutputIomuxXbarInout19  = 19|0x100U,   /**< XBARA1_OUT19 output assigned to IOMUX_XBAR_INOUT19 */
    kXBARA1_OutputIomuxXbarInout20  = 20|0x100U,   /**< XBARA1_OUT20 output assigned to IOMUX_XBAR_INOUT20 */
    kXBARA1_OutputIomuxXbarInout21  = 21|0x100U,   /**< XBARA1_OUT21 output assigned to IOMUX_XBAR_INOUT21 */
    kXBARA1_OutputIomuxXbarInout22  = 22|0x100U,   /**< XBARA1_OUT22 output assigned to IOMUX_XBAR_INOUT22 */
    kXBARA1_OutputIomuxXbarInout23  = 23|0x100U,   /**< XBARA1_OUT23 output assigned to IOMUX_XBAR_INOUT23 */
    kXBARA1_OutputIomuxXbarInout24  = 24|0x100U,   /**< XBARA1_OUT24 output assigned to IOMUX_XBAR_INOUT24 */
    kXBARA1_OutputIomuxXbarInout25  = 25|0x100U,   /**< XBARA1_OUT25 output assigned to IOMUX_XBAR_INOUT25 */
    kXBARA1_OutputIomuxXbarInout26  = 26|0x100U,   /**< XBARA1_OUT26 output assigned to IOMUX_XBAR_INOUT26 */
    kXBARA1_OutputIomuxXbarInout27  = 27|0x100U,   /**< XBARA1_OUT27 output assigned to IOMUX_XBAR_INOUT27 */
    kXBARA1_OutputIomuxXbarInout28  = 28|0x100U,   /**< XBARA1_OUT28 output assigned to IOMUX_XBAR_INOUT28 */
    kXBARA1_OutputIomuxXbarInout29  = 29|0x100U,   /**< XBARA1_OUT29 output assigned to IOMUX_XBAR_INOUT29 */
    kXBARA1_OutputIomuxXbarInout30  = 30|0x100U,   /**< XBARA1_OUT30 output assigned to IOMUX_XBAR_INOUT30 */
    kXBARA1_OutputIomuxXbarInout31  = 31|0x100U,   /**< XBARA1_OUT31 output assigned to IOMUX_XBAR_INOUT31 */
    kXBARA1_OutputIomuxXbarInout32  = 32|0x100U,   /**< XBARA1_OUT32 output assigned to IOMUX_XBAR_INOUT32 */
    kXBARA1_OutputIomuxXbarInout33  = 33|0x100U,   /**< XBARA1_OUT33 output assigned to IOMUX_XBAR_INOUT33 */
    kXBARA1_OutputIomuxXbarInout34  = 34|0x100U,   /**< XBARA1_OUT34 output assigned to IOMUX_XBAR_INOUT34 */
    kXBARA1_OutputIomuxXbarInout35  = 35|0x100U,   /**< XBARA1_OUT35 output assigned to IOMUX_XBAR_INOUT35 */
    kXBARA1_OutputIomuxXbarInout36  = 36|0x100U,   /**< XBARA1_OUT36 output assigned to IOMUX_XBAR_INOUT36 */
    kXBARA1_OutputIomuxXbarInout37  = 37|0x100U,   /**< XBARA1_OUT37 output assigned to IOMUX_XBAR_INOUT37 */
    kXBARA1_OutputIomuxXbarInout38  = 38|0x100U,   /**< XBARA1_OUT38 output assigned to IOMUX_XBAR_INOUT38 */
    kXBARA1_OutputIomuxXbarInout39  = 39|0x100U,   /**< XBARA1_OUT39 output assigned to IOMUX_XBAR_INOUT39 */
    kXBARA1_OutputIomuxXbarInout40  = 40|0x100U,   /**< XBARA1_OUT40 output assigned to IOMUX_XBAR_INOUT40 */
    kXBARA1_OutputAcmp1Sample       = 41|0x100U,   /**< XBARA1_OUT41 output assigned to ACMP1_SAMPLE */
    kXBARA1_OutputAcmp2Sample       = 42|0x100U,   /**< XBARA1_OUT42 output assigned to ACMP2_SAMPLE */
    kXBARA1_OutputAcmp3Sample       = 43|0x100U,   /**< XBARA1_OUT43 output assigned to ACMP3_SAMPLE */
    kXBARA1_OutputAcmp4Sample       = 44|0x100U,   /**< XBARA1_OUT44 output assigned to ACMP4_SAMPLE */
    kXBARA1_OutputRESERVED45        = 45|0x100U,   /**< XBARA1_OUT45 output is reserved. */
    kXBARA1_OutputRESERVED46        = 46|0x100U,   /**< XBARA1_OUT46 output is reserved. */
    kXBARA1_OutputRESERVED47        = 47|0x100U,   /**< XBARA1_OUT47 output is reserved. */
    kXBARA1_OutputRESERVED48        = 48|0x100U,   /**< XBARA1_OUT48 output is reserved. */
    kXBARA1_OutputFlexpwm1Pwm0Exta  = 49|0x100U,   /**< XBARA1_OUT49 output assigned to FLEXPWM1_PWM0_EXTA */
    kXBARA1_OutputFlexpwm1Pwm1Exta  = 50|0x100U,   /**< XBARA1_OUT50 output assigned to FLEXPWM1_PWM1_EXTA */
    kXBARA1_OutputFlexpwm1Pwm2Exta  = 51|0x100U,   /**< XBARA1_OUT51 output assigned to FLEXPWM1_PWM2_EXTA */
    kXBARA1_OutputFlexpwm1Pwm3Exta  = 52|0x100U,   /**< XBARA1_OUT52 output assigned to FLEXPWM1_PWM3_EXTA */
    kXBARA1_OutputFlexpwm1Pwm0ExtSync = 53|0x100U, /**< XBARA1_OUT53 output assigned to FLEXPWM1_PWM0_EXT_SYNC */
    kXBARA1_OutputFlexpwm1Pwm1ExtSync = 54|0x100U, /**< XBARA1_OUT54 output assigned to FLEXPWM1_PWM1_EXT_SYNC */
    kXBARA1_OutputFlexpwm1Pwm2ExtSync = 55|0x100U, /**< XBARA1_OUT55 output assigned to FLEXPWM1_PWM2_EXT_SYNC */
    kXBARA1_OutputFlexpwm1Pwm3ExtSync = 56|0x100U, /**< XBARA1_OUT56 output assigned to FLEXPWM1_PWM3_EXT_SYNC */
    kXBARA1_OutputFlexpwm1ExtClk    = 57|0x100U,   /**< XBARA1_OUT57 output assigned to FLEXPWM1_EXT_CLK */
    kXBARA1_OutputFlexpwm1Fault0    = 58|0x100U,   /**< XBARA1_OUT58 output assigned to FLEXPWM1_FAULT0 */
    kXBARA1_OutputFlexpwm1Fault1    = 59|0x100U,   /**< XBARA1_OUT59 output assigned to FLEXPWM1_FAULT1 */
    kXBARA1_OutputFlexpwm1234Fault2 = 60|0x100U,   /**< XBARA1_OUT60 output assigned to FLEXPWM1_2_3_4_FAULT2 */
    kXBARA1_OutputFlexpwm1234Fault3 = 61|0x100U,   /**< XBARA1_OUT61 output assigned to FLEXPWM1_2_3_4_FAULT3 */
    kXBARA1_OutputFlexpwm1ExtForce  = 62|0x100U,   /**< XBARA1_OUT62 output assigned to FLEXPWM1_EXT_FORCE */
    kXBARA1_OutputFlexpwm2Pwm0Exta  = 63|0x100U,   /**< XBARA1_OUT63 output assigned to FLEXPWM2_PWM0_EXTA */
    kXBARA1_OutputFlexpwm2Pwm1Exta  = 64|0x100U,   /**< XBARA1_OUT64 output assigned to FLEXPWM2_PWM1_EXTA */
    kXBARA1_OutputFlexpwm2Pwm2Exta  = 65|0x100U,   /**< XBARA1_OUT65 output assigned to FLEXPWM2_PWM2_EXTA */
    kXBARA1_OutputFlexpwm2Pwm3Exta  = 66|0x100U,   /**< XBARA1_OUT66 output assigned to FLEXPWM2_PWM3_EXTA */
    kXBARA1_OutputFlexpwm2Pwm0ExtSync = 67|0x100U, /**< XBARA1_OUT67 output assigned to FLEXPWM2_PWM0_EXT_SYNC */
    kXBARA1_OutputFlexpwm2Pwm1ExtSync = 68|0x100U, /**< XBARA1_OUT68 output assigned to FLEXPWM2_PWM1_EXT_SYNC */
    kXBARA1_OutputFlexpwm2Pwm2ExtSync = 69|0x100U, /**< XBARA1_OUT69 output assigned to FLEXPWM2_PWM2_EXT_SYNC */
    kXBARA1_OutputFlexpwm2Pwm3ExtSync = 70|0x100U, /**< XBARA1_OUT70 output assigned to FLEXPWM2_PWM3_EXT_SYNC */
    kXBARA1_OutputFlexpwm2ExtClk    = 71|0x100U,   /**< XBARA1_OUT71 output assigned to FLEXPWM2_EXT_CLK */
    kXBARA1_OutputFlexpwm2Fault0    = 72|0x100U,   /**< XBARA1_OUT72 output assigned to FLEXPWM2_FAULT0 */
    kXBARA1_OutputFlexpwm2Fault1    = 73|0x100U,   /**< XBARA1_OUT73 output assigned to FLEXPWM2_FAULT1 */
    kXBARA1_OutputFlexpwm2ExtForce  = 74|0x100U,   /**< XBARA1_OUT74 output assigned to FLEXPWM2_EXT_FORCE */
    kXBARA1_OutputFlexpwm34Pwm0Exta = 75|0x100U,   /**< XBARA1_OUT75 output assigned to FLEXPWM3_4_PWM0_EXTA */
    kXBARA1_OutputFlexpwm34Pwm1Exta = 76|0x100U,   /**< XBARA1_OUT76 output assigned to FLEXPWM3_4_PWM1_EXTA */
    kXBARA1_OutputFlexpwm34Pwm2Exta = 77|0x100U,   /**< XBARA1_OUT77 output assigned to FLEXPWM3_4_PWM2_EXTA */
    kXBARA1_OutputFlexpwm34Pwm3Exta = 78|0x100U,   /**< XBARA1_OUT78 output assigned to FLEXPWM3_4_PWM3_EXTA */
    kXBARA1_OutputFlexpwm34ExtClk   = 79|0x100U,   /**< XBARA1_OUT79 output assigned to FLEXPWM3_4_EXT_CLK */
    kXBARA1_OutputFlexpwm3Pwm0ExtSync = 80|0x100U, /**< XBARA1_OUT80 output assigned to FLEXPWM3_PWM0_EXT_SYNC */
    kXBARA1_OutputFlexpwm3Pwm1ExtSync = 81|0x100U, /**< XBARA1_OUT81 output assigned to FLEXPWM3_PWM1_EXT_SYNC */
    kXBARA1_OutputFlexpwm3Pwm2ExtSync = 82|0x100U, /**< XBARA1_OUT82 output assigned to FLEXPWM3_PWM2_EXT_SYNC */
    kXBARA1_OutputFlexpwm3Pwm3ExtSync = 83|0x100U, /**< XBARA1_OUT83 output assigned to FLEXPWM3_PWM3_EXT_SYNC */
    kXBARA1_OutputFlexpwm3Fault0    = 84|0x100U,   /**< XBARA1_OUT84 output assigned to FLEXPWM3_FAULT0 */
    kXBARA1_OutputFlexpwm3Fault1    = 85|0x100U,   /**< XBARA1_OUT85 output assigned to FLEXPWM3_FAULT1 */
    kXBARA1_OutputFlexpwm3ExtForce  = 86|0x100U,   /**< XBARA1_OUT86 output assigned to FLEXPWM3_EXT_FORCE */
    kXBARA1_OutputFlexpwm4Pwm0ExtSync = 87|0x100U, /**< XBARA1_OUT87 output assigned to FLEXPWM4_PWM0_EXT_SYNC */
    kXBARA1_OutputFlexpwm4Pwm1ExtSync = 88|0x100U, /**< XBARA1_OUT88 output assigned to FLEXPWM4_PWM1_EXT_SYNC */
    kXBARA1_OutputFlexpwm4Pwm2ExtSync = 89|0x100U, /**< XBARA1_OUT89 output assigned to FLEXPWM4_PWM2_EXT_SYNC */
    kXBARA1_OutputFlexpwm4Pwm3ExtSync = 90|0x100U, /**< XBARA1_OUT90 output assigned to FLEXPWM4_PWM3_EXT_SYNC */
    kXBARA1_OutputFlexpwm4Fault0    = 91|0x100U,   /**< XBARA1_OUT91 output assigned to FLEXPWM4_FAULT0 */
    kXBARA1_OutputFlexpwm4Fault1    = 92|0x100U,   /**< XBARA1_OUT92 output assigned to FLEXPWM4_FAULT1 */
    kXBARA1_OutputFlexpwm4ExtForce  = 93|0x100U,   /**< XBARA1_OUT93 output assigned to FLEXPWM4_EXT_FORCE */
    kXBARA1_OutputRESERVED94        = 94|0x100U,   /**< XBARA1_OUT94 output is reserved. */
    kXBARA1_OutputRESERVED95        = 95|0x100U,   /**< XBARA1_OUT95 output is reserved. */
    kXBARA1_OutputRESERVED96        = 96|0x100U,   /**< XBARA1_OUT96 output is reserved. */
    kXBARA1_OutputRESERVED97        = 97|0x100U,   /**< XBARA1_OUT97 output is reserved. */
    kXBARA1_OutputRESERVED98        = 98|0x100U,   /**< XBARA1_OUT98 output is reserved. */
    kXBARA1_OutputRESERVED99        = 99|0x100U,   /**< XBARA1_OUT99 output is reserved. */
    kXBARA1_OutputRESERVED100       = 100|0x100U,  /**< XBARA1_OUT100 output is reserved. */
    kXBARA1_OutputRESERVED101       = 101|0x100U,  /**< XBARA1_OUT101 output is reserved. */
    kXBARA1_OutputRESERVED102       = 102|0x100U,  /**< XBARA1_OUT102 output is reserved. */
    kXBARA1_OutputRESERVED103       = 103|0x100U,  /**< XBARA1_OUT103 output is reserved. */
    kXBARA1_OutputRESERVED104       = 104|0x100U,  /**< XBARA1_OUT104 output is reserved. */
    kXBARA1_OutputRESERVED105       = 105|0x100U,  /**< XBARA1_OUT105 output is reserved. */
    kXBARA1_OutputRESERVED106       = 106|0x100U,  /**< XBARA1_OUT106 output is reserved. */
    kXBARA1_OutputRESERVED107       = 107|0x100U,  /**< XBARA1_OUT107 output is reserved. */
    kXBARA1_OutputDec1Phasea        = 108|0x100U,  /**< XBARA1_OUT108 output assigned to DEC1_PHASEA */
    kXBARA1_OutputDec1Phaseb        = 109|0x100U,  /**< XBARA1_OUT109 output assigned to DEC1_PHASEB */
    kXBARA1_OutputDec1Index         = 110|0x100U,  /**< XBARA1_OUT110 output assigned to DEC1_INDEX */
    kXBARA1_OutputDec1Home          = 111|0x100U,  /**< XBARA1_OUT111 output assigned to DEC1_HOME */
    kXBARA1_OutputDec1Trigger       = 112|0x100U,  /**< XBARA1_OUT112 output assigned to DEC1_TRIGGER */
    kXBARA1_OutputDec2Phasea        = 113|0x100U,  /**< XBARA1_OUT113 output assigned to DEC2_PHASEA */
    kXBARA1_OutputDec2Phaseb        = 114|0x100U,  /**< XBARA1_OUT114 output assigned to DEC2_PHASEB */
    kXBARA1_OutputDec2Index         = 115|0x100U,  /**< XBARA1_OUT115 output assigned to DEC2_INDEX */
    kXBARA1_OutputDec2Home          = 116|0x100U,  /**< XBARA1_OUT116 output assigned to DEC2_HOME */
    kXBARA1_OutputDec2Trigger       = 117|0x100U,  /**< XBARA1_OUT117 output assigned to DEC2_TRIGGER */
    kXBARA1_OutputDec3Phasea        = 118|0x100U,  /**< XBARA1_OUT118 output assigned to DEC3_PHASEA */
    kXBARA1_OutputDec3Phaseb        = 119|0x100U,  /**< XBARA1_OUT119 output assigned to DEC3_PHASEB */
    kXBARA1_OutputDec3Index         = 120|0x100U,  /**< XBARA1_OUT120 output assigned to DEC3_INDEX */
    kXBARA1_OutputDec3Home          = 121|0x100U,  /**< XBARA1_OUT121 output assigned to DEC3_HOME */
    kXBARA1_OutputDec3Trigger       = 122|0x100U,  /**< XBARA1_OUT122 output assigned to DEC3_TRIGGER */
    kXBARA1_OutputDec4Phasea        = 123|0x100U,  /**< XBARA1_OUT123 output assigned to DEC4_PHASEA */
    kXBARA1_OutputDec4Phaseb        = 124|0x100U,  /**< XBARA1_OUT124 output assigned to DEC4_PHASEB */
    kXBARA1_OutputDec4Index         = 125|0x100U,  /**< XBARA1_OUT125 output assigned to DEC4_INDEX */
    kXBARA1_OutputDec4Home          = 126|0x100U,  /**< XBARA1_OUT126 output assigned to DEC4_HOME */
    kXBARA1_OutputDec4Trigger       = 127|0x100U,  /**< XBARA1_OUT127 output assigned to DEC4_TRIGGER */
    kXBARA1_OutputRESERVED128       = 128|0x100U,  /**< XBARA1_OUT128 output is reserved. */
    kXBARA1_OutputRESERVED129       = 129|0x100U,  /**< XBARA1_OUT129 output is reserved. */
    kXBARA1_OutputRESERVED130       = 130|0x100U,  /**< XBARA1_OUT130 output is reserved. */
    kXBARA1_OutputRESERVED131       = 131|0x100U,  /**< XBARA1_OUT131 output is reserved. */
    kXBARA1_OutputCan1              = 132|0x100U,  /**< XBARA1_OUT132 output assigned to CAN1 */
    kXBARA1_OutputCan2              = 133|0x100U,  /**< XBARA1_OUT133 output assigned to CAN2 */
    kXBARA1_OutputRESERVED134       = 134|0x100U,  /**< XBARA1_OUT134 output is reserved. */
    kXBARA1_OutputRESERVED135       = 135|0x100U,  /**< XBARA1_OUT135 output is reserved. */
    kXBARA1_OutputRESERVED136       = 136|0x100U,  /**< XBARA1_OUT136 output is reserved. */
    kXBARA1_OutputRESERVED137       = 137|0x100U,  /**< XBARA1_OUT137 output is reserved. */
    kXBARA1_OutputQtimer1Timer0     = 138|0x100U,  /**< XBARA1_OUT138 output assigned to QTIMER1_TIMER0 */
    kXBARA1_OutputQtimer1Timer1     = 139|0x100U,  /**< XBARA1_OUT139 output assigned to QTIMER1_TIMER1 */
    kXBARA1_OutputQtimer1Timer2     = 140|0x100U,  /**< XBARA1_OUT140 output assigned to QTIMER1_TIMER2 */
    kXBARA1_OutputQtimer1Timer3     = 141|0x100U,  /**< XBARA1_OUT141 output assigned to QTIMER1_TIMER3 */
    kXBARA1_OutputQtimer2Timer0     = 142|0x100U,  /**< XBARA1_OUT142 output assigned to QTIMER2_TIMER0 */
    kXBARA1_OutputQtimer2Timer1     = 143|0x100U,  /**< XBARA1_OUT143 output assigned to QTIMER2_TIMER1 */
    kXBARA1_OutputQtimer2Timer2     = 144|0x100U,  /**< XBARA1_OUT144 output assigned to QTIMER2_TIMER2 */
    kXBARA1_OutputQtimer2Timer3     = 145|0x100U,  /**< XBARA1_OUT145 output assigned to QTIMER2_TIMER3 */
    kXBARA1_OutputQtimer3Timer0     = 146|0x100U,  /**< XBARA1_OUT146 output assigned to QTIMER3_TIMER0 */
    kXBARA1_OutputQtimer3Timer1     = 147|0x100U,  /**< XBARA1_OUT147 output assigned to QTIMER3_TIMER1 */
    kXBARA1_OutputQtimer3Timer2     = 148|0x100U,  /**< XBARA1_OUT148 output assigned to QTIMER3_TIMER2 */
    kXBARA1_OutputQtimer3Timer3     = 149|0x100U,  /**< XBARA1_OUT149 output assigned to QTIMER3_TIMER3 */
    kXBARA1_OutputQtimer4Timer0     = 150|0x100U,  /**< XBARA1_OUT150 output assigned to QTIMER4_TIMER0 */
    kXBARA1_OutputQtimer4Timer1     = 151|0x100U,  /**< XBARA1_OUT151 output assigned to QTIMER4_TIMER1 */
    kXBARA1_OutputQtimer4Timer2     = 152|0x100U,  /**< XBARA1_OUT152 output assigned to QTIMER4_TIMER2 */
    kXBARA1_OutputQtimer4Timer3     = 153|0x100U,  /**< XBARA1_OUT153 output assigned to QTIMER4_TIMER3 */
    kXBARA1_OutputEwmEwmIn          = 154|0x100U,  /**< XBARA1_OUT154 output assigned to EWM_EWM_IN */
    kXBARA1_OutputAdcEtc0Coco0      = 155|0x100U,  /**< XBARA1_OUT155 output assigned to ADC_ETC0_COCO0 */
    kXBARA1_OutputAdcEtc0Coco1      = 156|0x100U,  /**< XBARA1_OUT156 output assigned to ADC_ETC0_COCO1 */
    kXBARA1_OutputAdcEtc0Coco2      = 157|0x100U,  /**< XBARA1_OUT157 output assigned to ADC_ETC0_COCO2 */
    kXBARA1_OutputAdcEtc0Coco3      = 158|0x100U,  /**< XBARA1_OUT158 output assigned to ADC_ETC0_COCO3 */
    kXBARA1_OutputAdcEtc1Coco0      = 159|0x100U,  /**< XBARA1_OUT159 output assigned to ADC_ETC1_COCO0 */
    kXBARA1_OutputAdcEtc1Coco1      = 160|0x100U,  /**< XBARA1_OUT160 output assigned to ADC_ETC1_COCO1 */
    kXBARA1_OutputAdcEtc1Coco2      = 161|0x100U,  /**< XBARA1_OUT161 output assigned to ADC_ETC1_COCO2 */
    kXBARA1_OutputAdcEtc1Coco3      = 162|0x100U,  /**< XBARA1_OUT162 output assigned to ADC_ETC1_COCO3 */
    kXBARA1_OutputRESERVED163       = 163|0x100U,  /**< XBARA1_OUT163 output is reserved. */
    kXBARA1_OutputRESERVED164       = 164|0x100U,  /**< XBARA1_OUT164 output is reserved. */
    kXBARA1_OutputRESERVED165       = 165|0x100U,  /**< XBARA1_OUT165 output is reserved. */
    kXBARA1_OutputRESERVED166       = 166|0x100U,  /**< XBARA1_OUT166 output is reserved. */
    kXBARA1_OutputRESERVED167       = 167|0x100U,  /**< XBARA1_OUT167 output is reserved. */
    kXBARA1_OutputRESERVED168       = 168|0x100U,  /**< XBARA1_OUT168 output is reserved. */
    kXBARA1_OutputRESERVED169       = 169|0x100U,  /**< XBARA1_OUT169 output is reserved. */
    kXBARA1_OutputRESERVED170       = 170|0x100U,  /**< XBARA1_OUT170 output is reserved. */
    kXBARA1_OutputFlexio1TrigIn0    = 171|0x100U,  /**< XBARA1_OUT171 output assigned to FLEXIO1_TRIG_IN0 */
    kXBARA1_OutputFlexio1TrigIn1    = 172|0x100U,  /**< XBARA1_OUT172 output assigned to FLEXIO1_TRIG_IN1 */
    kXBARA1_OutputFlexio2TrigIn0    = 173|0x100U,  /**< XBARA1_OUT173 output assigned to FLEXIO2_TRIG_IN0 */
    kXBARA1_OutputFlexio2TrigIn1    = 174|0x100U,  /**< XBARA1_OUT174 output assigned to FLEXIO2_TRIG_IN1 */
    kXBARB2_OutputAoi1In00          = 0|0x200U,    /**< XBARB2_OUT0 output assigned to AOI1_IN00 */
    kXBARB2_OutputAoi1In01          = 1|0x200U,    /**< XBARB2_OUT1 output assigned to AOI1_IN01 */
    kXBARB2_OutputAoi1In02          = 2|0x200U,    /**< XBARB2_OUT2 output assigned to AOI1_IN02 */
    kXBARB2_OutputAoi1In03          = 3|0x200U,    /**< XBARB2_OUT3 output assigned to AOI1_IN03 */
    kXBARB2_OutputAoi1In04          = 4|0x200U,    /**< XBARB2_OUT4 output assigned to AOI1_IN04 */
    kXBARB2_OutputAoi1In05          = 5|0x200U,    /**< XBARB2_OUT5 output assigned to AOI1_IN05 */
    kXBARB2_OutputAoi1In06          = 6|0x200U,    /**< XBARB2_OUT6 output assigned to AOI1_IN06 */
    kXBARB2_OutputAoi1In07          = 7|0x200U,    /**< XBARB2_OUT7 output assigned to AOI1_IN07 */
    kXBARB2_OutputAoi1In08          = 8|0x200U,    /**< XBARB2_OUT8 output assigned to AOI1_IN08 */
    kXBARB2_OutputAoi1In09          = 9|0x200U,    /**< XBARB2_OUT9 output assigned to AOI1_IN09 */
    kXBARB2_OutputAoi1In10          = 10|0x200U,   /**< XBARB2_OUT10 output assigned to AOI1_IN10 */
    kXBARB2_OutputAoi1In11          = 11|0x200U,   /**< XBARB2_OUT11 output assigned to AOI1_IN11 */
    kXBARB2_OutputAoi1In12          = 12|0x200U,   /**< XBARB2_OUT12 output assigned to AOI1_IN12 */
    kXBARB2_OutputAoi1In13          = 13|0x200U,   /**< XBARB2_OUT13 output assigned to AOI1_IN13 */
    kXBARB2_OutputAoi1In14          = 14|0x200U,   /**< XBARB2_OUT14 output assigned to AOI1_IN14 */
    kXBARB2_OutputAoi1In15          = 15|0x200U,   /**< XBARB2_OUT15 output assigned to AOI1_IN15 */
    kXBARB3_OutputAoi2In00          = 0|0x300U,    /**< XBARB3_OUT0 output assigned to AOI2_IN00 */
    kXBARB3_OutputAoi2In01          = 1|0x300U,    /**< XBARB3_OUT1 output assigned to AOI2_IN01 */
    kXBARB3_OutputAoi2In02          = 2|0x300U,    /**< XBARB3_OUT2 output assigned to AOI2_IN02 */
    kXBARB3_OutputAoi2In03          = 3|0x300U,    /**< XBARB3_OUT3 output assigned to AOI2_IN03 */
    kXBARB3_OutputAoi2In04          = 4|0x300U,    /**< XBARB3_OUT4 output assigned to AOI2_IN04 */
    kXBARB3_OutputAoi2In05          = 5|0x300U,    /**< XBARB3_OUT5 output assigned to AOI2_IN05 */
    kXBARB3_OutputAoi2In06          = 6|0x300U,    /**< XBARB3_OUT6 output assigned to AOI2_IN06 */
    kXBARB3_OutputAoi2In07          = 7|0x300U,    /**< XBARB3_OUT7 output assigned to AOI2_IN07 */
    kXBARB3_OutputAoi2In08          = 8|0x300U,    /**< XBARB3_OUT8 output assigned to AOI2_IN08 */
    kXBARB3_OutputAoi2In09          = 9|0x300U,    /**< XBARB3_OUT9 output assigned to AOI2_IN09 */
    kXBARB3_OutputAoi2In10          = 10|0x300U,   /**< XBARB3_OUT10 output assigned to AOI2_IN10 */
    kXBARB3_OutputAoi2In11          = 11|0x300U,   /**< XBARB3_OUT11 output assigned to AOI2_IN11 */
    kXBARB3_OutputAoi2In12          = 12|0x300U,   /**< XBARB3_OUT12 output assigned to AOI2_IN12 */
    kXBARB3_OutputAoi2In13          = 13|0x300U,   /**< XBARB3_OUT13 output assigned to AOI2_IN13 */
    kXBARB3_OutputAoi2In14          = 14|0x300U,   /**< XBARB3_OUT14 output assigned to AOI2_IN14 */
    kXBARB3_OutputAoi2In15          = 15|0x300U,   /**< XBARB3_OUT15 output assigned to AOI2_IN15 */
} xbar_output_signal_t;
#endif /* XBAR_OUTPUT_SIGNAL_T_ */


/*!
 * @}
 */ /* end of group Mapping_Information */


/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- XBARB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARB_Peripheral_Access_Layer XBARB Peripheral Access Layer
 * @{
 */

/** XBARB - Register Layout Typedef */
typedef struct {
  __IO uint16_t SEL0;                              /**< Crossbar B Select Register 0, offset: 0x0 */
  __IO uint16_t SEL1;                              /**< Crossbar B Select Register 1, offset: 0x2 */
  __IO uint16_t SEL2;                              /**< Crossbar B Select Register 2, offset: 0x4 */
  __IO uint16_t SEL3;                              /**< Crossbar B Select Register 3, offset: 0x6 */
  __IO uint16_t SEL4;                              /**< Crossbar B Select Register 4, offset: 0x8 */
  __IO uint16_t SEL5;                              /**< Crossbar B Select Register 5, offset: 0xA */
  __IO uint16_t SEL6;                              /**< Crossbar B Select Register 6, offset: 0xC */
  __IO uint16_t SEL7;                              /**< Crossbar B Select Register 7, offset: 0xE */
} XBARB_Type;

/* ----------------------------------------------------------------------------
   -- XBARB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARB_Register_Masks XBARB Register Masks
 * @{
 */

/*! @name SEL0 - Crossbar B Select Register 0 */
/*! @{ */

#define XBARB_SEL0_SEL0_MASK                     (0x7FU)
#define XBARB_SEL0_SEL0_SHIFT                    (0U)
#define XBARB_SEL0_SEL0(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL0_SEL0_SHIFT)) & XBARB_SEL0_SEL0_MASK)

#define XBARB_SEL0_SEL1_MASK                     (0x7F00U)
#define XBARB_SEL0_SEL1_SHIFT                    (8U)
#define XBARB_SEL0_SEL1(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL0_SEL1_SHIFT)) & XBARB_SEL0_SEL1_MASK)
/*! @} */

/*! @name SEL1 - Crossbar B Select Register 1 */
/*! @{ */

#define XBARB_SEL1_SEL2_MASK                     (0x7FU)
#define XBARB_SEL1_SEL2_SHIFT                    (0U)
#define XBARB_SEL1_SEL2(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL1_SEL2_SHIFT)) & XBARB_SEL1_SEL2_MASK)

#define XBARB_SEL1_SEL3_MASK                     (0x7F00U)
#define XBARB_SEL1_SEL3_SHIFT                    (8U)
#define XBARB_SEL1_SEL3(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL1_SEL3_SHIFT)) & XBARB_SEL1_SEL3_MASK)
/*! @} */

/*! @name SEL2 - Crossbar B Select Register 2 */
/*! @{ */

#define XBARB_SEL2_SEL4_MASK                     (0x7FU)
#define XBARB_SEL2_SEL4_SHIFT                    (0U)
#define XBARB_SEL2_SEL4(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL2_SEL4_SHIFT)) & XBARB_SEL2_SEL4_MASK)

#define XBARB_SEL2_SEL5_MASK                     (0x7F00U)
#define XBARB_SEL2_SEL5_SHIFT                    (8U)
#define XBARB_SEL2_SEL5(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL2_SEL5_SHIFT)) & XBARB_SEL2_SEL5_MASK)
/*! @} */

/*! @name SEL3 - Crossbar B Select Register 3 */
/*! @{ */

#define XBARB_SEL3_SEL6_MASK                     (0x7FU)
#define XBARB_SEL3_SEL6_SHIFT                    (0U)
#define XBARB_SEL3_SEL6(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL3_SEL6_SHIFT)) & XBARB_SEL3_SEL6_MASK)

#define XBARB_SEL3_SEL7_MASK                     (0x7F00U)
#define XBARB_SEL3_SEL7_SHIFT                    (8U)
#define XBARB_SEL3_SEL7(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL3_SEL7_SHIFT)) & XBARB_SEL3_SEL7_MASK)
/*! @} */

/*! @name SEL4 - Crossbar B Select Register 4 */
/*! @{ */

#define XBARB_SEL4_SEL8_MASK                     (0x7FU)
#define XBARB_SEL4_SEL8_SHIFT                    (0U)
#define XBARB_SEL4_SEL8(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL4_SEL8_SHIFT)) & XBARB_SEL4_SEL8_MASK)

#define XBARB_SEL4_SEL9_MASK                     (0x7F00U)
#define XBARB_SEL4_SEL9_SHIFT                    (8U)
#define XBARB_SEL4_SEL9(x)                       (((uint16_t)(((uint16_t)(x)) << XBARB_SEL4_SEL9_SHIFT)) & XBARB_SEL4_SEL9_MASK)
/*! @} */

/*! @name SEL5 - Crossbar B Select Register 5 */
/*! @{ */

#define XBARB_SEL5_SEL10_MASK                    (0x7FU)
#define XBARB_SEL5_SEL10_SHIFT                   (0U)
#define XBARB_SEL5_SEL10(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL5_SEL10_SHIFT)) & XBARB_SEL5_SEL10_MASK)

#define XBARB_SEL5_SEL11_MASK                    (0x7F00U)
#define XBARB_SEL5_SEL11_SHIFT                   (8U)
#define XBARB_SEL5_SEL11(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL5_SEL11_SHIFT)) & XBARB_SEL5_SEL11_MASK)
/*! @} */

/*! @name SEL6 - Crossbar B Select Register 6 */
/*! @{ */

#define XBARB_SEL6_SEL12_MASK                    (0x7FU)
#define XBARB_SEL6_SEL12_SHIFT                   (0U)
#define XBARB_SEL6_SEL12(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL6_SEL12_SHIFT)) & XBARB_SEL6_SEL12_MASK)

#define XBARB_SEL6_SEL13_MASK                    (0x7F00U)
#define XBARB_SEL6_SEL13_SHIFT                   (8U)
#define XBARB_SEL6_SEL13(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL6_SEL13_SHIFT)) & XBARB_SEL6_SEL13_MASK)
/*! @} */

/*! @name SEL7 - Crossbar B Select Register 7 */
/*! @{ */

#define XBARB_SEL7_SEL14_MASK                    (0x7FU)
#define XBARB_SEL7_SEL14_SHIFT                   (0U)
#define XBARB_SEL7_SEL14(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL7_SEL14_SHIFT)) & XBARB_SEL7_SEL14_MASK)

#define XBARB_SEL7_SEL15_MASK                    (0x7F00U)
#define XBARB_SEL7_SEL15_SHIFT                   (8U)
#define XBARB_SEL7_SEL15(x)                      (((uint16_t)(((uint16_t)(x)) << XBARB_SEL7_SEL15_SHIFT)) & XBARB_SEL7_SEL15_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group XBARB_Register_Masks */


/*!
 * @}
 */ /* end of group XBARB_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_XBARB_H_ */

