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
**         CMSIS Peripheral Access Layer for XBARA
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
 * @file PERI_XBARA.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for XBARA
 *
 * CMSIS Peripheral Access Layer for XBARA
 */

#if !defined(PERI_XBARA_H_)
#define PERI_XBARA_H_                            /**< Symbol preventing repeated inclusion */

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
   -- XBARA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARA_Peripheral_Access_Layer XBARA Peripheral Access Layer
 * @{
 */

/** XBARA - Register Layout Typedef */
typedef struct {
  __IO uint16_t SEL0;                              /**< Crossbar A Select Register 0, offset: 0x0 */
  __IO uint16_t SEL1;                              /**< Crossbar A Select Register 1, offset: 0x2 */
  __IO uint16_t SEL2;                              /**< Crossbar A Select Register 2, offset: 0x4 */
  __IO uint16_t SEL3;                              /**< Crossbar A Select Register 3, offset: 0x6 */
  __IO uint16_t SEL4;                              /**< Crossbar A Select Register 4, offset: 0x8 */
  __IO uint16_t SEL5;                              /**< Crossbar A Select Register 5, offset: 0xA */
  __IO uint16_t SEL6;                              /**< Crossbar A Select Register 6, offset: 0xC */
  __IO uint16_t SEL7;                              /**< Crossbar A Select Register 7, offset: 0xE */
  __IO uint16_t SEL8;                              /**< Crossbar A Select Register 8, offset: 0x10 */
  __IO uint16_t SEL9;                              /**< Crossbar A Select Register 9, offset: 0x12 */
  __IO uint16_t SEL10;                             /**< Crossbar A Select Register 10, offset: 0x14 */
  __IO uint16_t SEL11;                             /**< Crossbar A Select Register 11, offset: 0x16 */
  __IO uint16_t SEL12;                             /**< Crossbar A Select Register 12, offset: 0x18 */
  __IO uint16_t SEL13;                             /**< Crossbar A Select Register 13, offset: 0x1A */
  __IO uint16_t SEL14;                             /**< Crossbar A Select Register 14, offset: 0x1C */
  __IO uint16_t SEL15;                             /**< Crossbar A Select Register 15, offset: 0x1E */
  __IO uint16_t SEL16;                             /**< Crossbar A Select Register 16, offset: 0x20 */
  __IO uint16_t SEL17;                             /**< Crossbar A Select Register 17, offset: 0x22 */
  __IO uint16_t SEL18;                             /**< Crossbar A Select Register 18, offset: 0x24 */
  __IO uint16_t SEL19;                             /**< Crossbar A Select Register 19, offset: 0x26 */
  __IO uint16_t SEL20;                             /**< Crossbar A Select Register 20, offset: 0x28 */
  __IO uint16_t SEL21;                             /**< Crossbar A Select Register 21, offset: 0x2A */
  __IO uint16_t SEL22;                             /**< Crossbar A Select Register 22, offset: 0x2C */
  __IO uint16_t SEL23;                             /**< Crossbar A Select Register 23, offset: 0x2E */
  __IO uint16_t SEL24;                             /**< Crossbar A Select Register 24, offset: 0x30 */
  __IO uint16_t SEL25;                             /**< Crossbar A Select Register 25, offset: 0x32 */
  __IO uint16_t SEL26;                             /**< Crossbar A Select Register 26, offset: 0x34 */
  __IO uint16_t SEL27;                             /**< Crossbar A Select Register 27, offset: 0x36 */
  __IO uint16_t SEL28;                             /**< Crossbar A Select Register 28, offset: 0x38 */
  __IO uint16_t SEL29;                             /**< Crossbar A Select Register 29, offset: 0x3A */
  __IO uint16_t SEL30;                             /**< Crossbar A Select Register 30, offset: 0x3C */
  __IO uint16_t SEL31;                             /**< Crossbar A Select Register 31, offset: 0x3E */
  __IO uint16_t SEL32;                             /**< Crossbar A Select Register 32, offset: 0x40 */
  __IO uint16_t SEL33;                             /**< Crossbar A Select Register 33, offset: 0x42 */
  __IO uint16_t SEL34;                             /**< Crossbar A Select Register 34, offset: 0x44 */
  __IO uint16_t SEL35;                             /**< Crossbar A Select Register 35, offset: 0x46 */
  __IO uint16_t SEL36;                             /**< Crossbar A Select Register 36, offset: 0x48 */
  __IO uint16_t SEL37;                             /**< Crossbar A Select Register 37, offset: 0x4A */
  __IO uint16_t SEL38;                             /**< Crossbar A Select Register 38, offset: 0x4C */
  __IO uint16_t SEL39;                             /**< Crossbar A Select Register 39, offset: 0x4E */
  __IO uint16_t SEL40;                             /**< Crossbar A Select Register 40, offset: 0x50 */
  __IO uint16_t SEL41;                             /**< Crossbar A Select Register 41, offset: 0x52 */
  __IO uint16_t SEL42;                             /**< Crossbar A Select Register 42, offset: 0x54 */
  __IO uint16_t SEL43;                             /**< Crossbar A Select Register 43, offset: 0x56 */
  __IO uint16_t SEL44;                             /**< Crossbar A Select Register 44, offset: 0x58 */
  __IO uint16_t SEL45;                             /**< Crossbar A Select Register 45, offset: 0x5A */
  __IO uint16_t SEL46;                             /**< Crossbar A Select Register 46, offset: 0x5C */
  __IO uint16_t SEL47;                             /**< Crossbar A Select Register 47, offset: 0x5E */
  __IO uint16_t SEL48;                             /**< Crossbar A Select Register 48, offset: 0x60 */
  __IO uint16_t SEL49;                             /**< Crossbar A Select Register 49, offset: 0x62 */
  __IO uint16_t SEL50;                             /**< Crossbar A Select Register 50, offset: 0x64 */
  __IO uint16_t SEL51;                             /**< Crossbar A Select Register 51, offset: 0x66 */
  __IO uint16_t SEL52;                             /**< Crossbar A Select Register 52, offset: 0x68 */
  __IO uint16_t SEL53;                             /**< Crossbar A Select Register 53, offset: 0x6A */
  __IO uint16_t SEL54;                             /**< Crossbar A Select Register 54, offset: 0x6C */
  __IO uint16_t SEL55;                             /**< Crossbar A Select Register 55, offset: 0x6E */
  __IO uint16_t SEL56;                             /**< Crossbar A Select Register 56, offset: 0x70 */
  __IO uint16_t SEL57;                             /**< Crossbar A Select Register 57, offset: 0x72 */
  __IO uint16_t SEL58;                             /**< Crossbar A Select Register 58, offset: 0x74 */
  __IO uint16_t SEL59;                             /**< Crossbar A Select Register 59, offset: 0x76 */
  __IO uint16_t SEL60;                             /**< Crossbar A Select Register 60, offset: 0x78 */
  __IO uint16_t SEL61;                             /**< Crossbar A Select Register 61, offset: 0x7A */
  __IO uint16_t SEL62;                             /**< Crossbar A Select Register 62, offset: 0x7C */
  __IO uint16_t SEL63;                             /**< Crossbar A Select Register 63, offset: 0x7E */
  __IO uint16_t SEL64;                             /**< Crossbar A Select Register 64, offset: 0x80 */
  __IO uint16_t SEL65;                             /**< Crossbar A Select Register 65, offset: 0x82 */
  __IO uint16_t SEL66;                             /**< Crossbar A Select Register 66, offset: 0x84 */
  __IO uint16_t SEL67;                             /**< Crossbar A Select Register 67, offset: 0x86 */
  __IO uint16_t SEL68;                             /**< Crossbar A Select Register 68, offset: 0x88 */
  __IO uint16_t SEL69;                             /**< Crossbar A Select Register 69, offset: 0x8A */
  __IO uint16_t SEL70;                             /**< Crossbar A Select Register 70, offset: 0x8C */
  __IO uint16_t SEL71;                             /**< Crossbar A Select Register 71, offset: 0x8E */
  __IO uint16_t SEL72;                             /**< Crossbar A Select Register 72, offset: 0x90 */
  __IO uint16_t SEL73;                             /**< Crossbar A Select Register 73, offset: 0x92 */
  __IO uint16_t SEL74;                             /**< Crossbar A Select Register 74, offset: 0x94 */
  __IO uint16_t SEL75;                             /**< Crossbar A Select Register 75, offset: 0x96 */
  __IO uint16_t SEL76;                             /**< Crossbar A Select Register 76, offset: 0x98 */
  __IO uint16_t SEL77;                             /**< Crossbar A Select Register 77, offset: 0x9A */
  __IO uint16_t SEL78;                             /**< Crossbar A Select Register 78, offset: 0x9C */
  __IO uint16_t SEL79;                             /**< Crossbar A Select Register 79, offset: 0x9E */
  __IO uint16_t SEL80;                             /**< Crossbar A Select Register 80, offset: 0xA0 */
  __IO uint16_t SEL81;                             /**< Crossbar A Select Register 81, offset: 0xA2 */
  __IO uint16_t SEL82;                             /**< Crossbar A Select Register 82, offset: 0xA4 */
  __IO uint16_t SEL83;                             /**< Crossbar A Select Register 83, offset: 0xA6 */
  __IO uint16_t SEL84;                             /**< Crossbar A Select Register 84, offset: 0xA8 */
  __IO uint16_t SEL85;                             /**< Crossbar A Select Register 85, offset: 0xAA */
  __IO uint16_t SEL86;                             /**< Crossbar A Select Register 86, offset: 0xAC */
  __IO uint16_t SEL87;                             /**< Crossbar A Select Register 87, offset: 0xAE */
  __IO uint16_t CTRL0;                             /**< Crossbar A Control Register 0, offset: 0xB0 */
  __IO uint16_t CTRL1;                             /**< Crossbar A Control Register 1, offset: 0xB2 */
} XBARA_Type;

/* ----------------------------------------------------------------------------
   -- XBARA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBARA_Register_Masks XBARA Register Masks
 * @{
 */

/*! @name SEL0 - Crossbar A Select Register 0 */
/*! @{ */

#define XBARA_SEL0_SEL0_MASK                     (0xFFU)
#define XBARA_SEL0_SEL0_SHIFT                    (0U)
#define XBARA_SEL0_SEL0(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL0_SEL0_SHIFT)) & XBARA_SEL0_SEL0_MASK)

#define XBARA_SEL0_SEL1_MASK                     (0xFF00U)
#define XBARA_SEL0_SEL1_SHIFT                    (8U)
#define XBARA_SEL0_SEL1(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL0_SEL1_SHIFT)) & XBARA_SEL0_SEL1_MASK)
/*! @} */

/*! @name SEL1 - Crossbar A Select Register 1 */
/*! @{ */

#define XBARA_SEL1_SEL2_MASK                     (0xFFU)
#define XBARA_SEL1_SEL2_SHIFT                    (0U)
#define XBARA_SEL1_SEL2(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL1_SEL2_SHIFT)) & XBARA_SEL1_SEL2_MASK)

#define XBARA_SEL1_SEL3_MASK                     (0xFF00U)
#define XBARA_SEL1_SEL3_SHIFT                    (8U)
#define XBARA_SEL1_SEL3(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL1_SEL3_SHIFT)) & XBARA_SEL1_SEL3_MASK)
/*! @} */

/*! @name SEL2 - Crossbar A Select Register 2 */
/*! @{ */

#define XBARA_SEL2_SEL4_MASK                     (0xFFU)
#define XBARA_SEL2_SEL4_SHIFT                    (0U)
#define XBARA_SEL2_SEL4(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL2_SEL4_SHIFT)) & XBARA_SEL2_SEL4_MASK)

#define XBARA_SEL2_SEL5_MASK                     (0xFF00U)
#define XBARA_SEL2_SEL5_SHIFT                    (8U)
#define XBARA_SEL2_SEL5(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL2_SEL5_SHIFT)) & XBARA_SEL2_SEL5_MASK)
/*! @} */

/*! @name SEL3 - Crossbar A Select Register 3 */
/*! @{ */

#define XBARA_SEL3_SEL6_MASK                     (0xFFU)
#define XBARA_SEL3_SEL6_SHIFT                    (0U)
#define XBARA_SEL3_SEL6(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL3_SEL6_SHIFT)) & XBARA_SEL3_SEL6_MASK)

#define XBARA_SEL3_SEL7_MASK                     (0xFF00U)
#define XBARA_SEL3_SEL7_SHIFT                    (8U)
#define XBARA_SEL3_SEL7(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL3_SEL7_SHIFT)) & XBARA_SEL3_SEL7_MASK)
/*! @} */

/*! @name SEL4 - Crossbar A Select Register 4 */
/*! @{ */

#define XBARA_SEL4_SEL8_MASK                     (0xFFU)
#define XBARA_SEL4_SEL8_SHIFT                    (0U)
#define XBARA_SEL4_SEL8(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL4_SEL8_SHIFT)) & XBARA_SEL4_SEL8_MASK)

#define XBARA_SEL4_SEL9_MASK                     (0xFF00U)
#define XBARA_SEL4_SEL9_SHIFT                    (8U)
#define XBARA_SEL4_SEL9(x)                       (((uint16_t)(((uint16_t)(x)) << XBARA_SEL4_SEL9_SHIFT)) & XBARA_SEL4_SEL9_MASK)
/*! @} */

/*! @name SEL5 - Crossbar A Select Register 5 */
/*! @{ */

#define XBARA_SEL5_SEL10_MASK                    (0xFFU)
#define XBARA_SEL5_SEL10_SHIFT                   (0U)
#define XBARA_SEL5_SEL10(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL5_SEL10_SHIFT)) & XBARA_SEL5_SEL10_MASK)

#define XBARA_SEL5_SEL11_MASK                    (0xFF00U)
#define XBARA_SEL5_SEL11_SHIFT                   (8U)
#define XBARA_SEL5_SEL11(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL5_SEL11_SHIFT)) & XBARA_SEL5_SEL11_MASK)
/*! @} */

/*! @name SEL6 - Crossbar A Select Register 6 */
/*! @{ */

#define XBARA_SEL6_SEL12_MASK                    (0xFFU)
#define XBARA_SEL6_SEL12_SHIFT                   (0U)
#define XBARA_SEL6_SEL12(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL6_SEL12_SHIFT)) & XBARA_SEL6_SEL12_MASK)

#define XBARA_SEL6_SEL13_MASK                    (0xFF00U)
#define XBARA_SEL6_SEL13_SHIFT                   (8U)
#define XBARA_SEL6_SEL13(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL6_SEL13_SHIFT)) & XBARA_SEL6_SEL13_MASK)
/*! @} */

/*! @name SEL7 - Crossbar A Select Register 7 */
/*! @{ */

#define XBARA_SEL7_SEL14_MASK                    (0xFFU)
#define XBARA_SEL7_SEL14_SHIFT                   (0U)
#define XBARA_SEL7_SEL14(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL7_SEL14_SHIFT)) & XBARA_SEL7_SEL14_MASK)

#define XBARA_SEL7_SEL15_MASK                    (0xFF00U)
#define XBARA_SEL7_SEL15_SHIFT                   (8U)
#define XBARA_SEL7_SEL15(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL7_SEL15_SHIFT)) & XBARA_SEL7_SEL15_MASK)
/*! @} */

/*! @name SEL8 - Crossbar A Select Register 8 */
/*! @{ */

#define XBARA_SEL8_SEL16_MASK                    (0xFFU)
#define XBARA_SEL8_SEL16_SHIFT                   (0U)
#define XBARA_SEL8_SEL16(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL8_SEL16_SHIFT)) & XBARA_SEL8_SEL16_MASK)

#define XBARA_SEL8_SEL17_MASK                    (0xFF00U)
#define XBARA_SEL8_SEL17_SHIFT                   (8U)
#define XBARA_SEL8_SEL17(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL8_SEL17_SHIFT)) & XBARA_SEL8_SEL17_MASK)
/*! @} */

/*! @name SEL9 - Crossbar A Select Register 9 */
/*! @{ */

#define XBARA_SEL9_SEL18_MASK                    (0xFFU)
#define XBARA_SEL9_SEL18_SHIFT                   (0U)
#define XBARA_SEL9_SEL18(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL9_SEL18_SHIFT)) & XBARA_SEL9_SEL18_MASK)

#define XBARA_SEL9_SEL19_MASK                    (0xFF00U)
#define XBARA_SEL9_SEL19_SHIFT                   (8U)
#define XBARA_SEL9_SEL19(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_SEL9_SEL19_SHIFT)) & XBARA_SEL9_SEL19_MASK)
/*! @} */

/*! @name SEL10 - Crossbar A Select Register 10 */
/*! @{ */

#define XBARA_SEL10_SEL20_MASK                   (0xFFU)
#define XBARA_SEL10_SEL20_SHIFT                  (0U)
#define XBARA_SEL10_SEL20(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL10_SEL20_SHIFT)) & XBARA_SEL10_SEL20_MASK)

#define XBARA_SEL10_SEL21_MASK                   (0xFF00U)
#define XBARA_SEL10_SEL21_SHIFT                  (8U)
#define XBARA_SEL10_SEL21(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL10_SEL21_SHIFT)) & XBARA_SEL10_SEL21_MASK)
/*! @} */

/*! @name SEL11 - Crossbar A Select Register 11 */
/*! @{ */

#define XBARA_SEL11_SEL22_MASK                   (0xFFU)
#define XBARA_SEL11_SEL22_SHIFT                  (0U)
#define XBARA_SEL11_SEL22(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL11_SEL22_SHIFT)) & XBARA_SEL11_SEL22_MASK)

#define XBARA_SEL11_SEL23_MASK                   (0xFF00U)
#define XBARA_SEL11_SEL23_SHIFT                  (8U)
#define XBARA_SEL11_SEL23(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL11_SEL23_SHIFT)) & XBARA_SEL11_SEL23_MASK)
/*! @} */

/*! @name SEL12 - Crossbar A Select Register 12 */
/*! @{ */

#define XBARA_SEL12_SEL24_MASK                   (0xFFU)
#define XBARA_SEL12_SEL24_SHIFT                  (0U)
#define XBARA_SEL12_SEL24(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL12_SEL24_SHIFT)) & XBARA_SEL12_SEL24_MASK)

#define XBARA_SEL12_SEL25_MASK                   (0xFF00U)
#define XBARA_SEL12_SEL25_SHIFT                  (8U)
#define XBARA_SEL12_SEL25(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL12_SEL25_SHIFT)) & XBARA_SEL12_SEL25_MASK)
/*! @} */

/*! @name SEL13 - Crossbar A Select Register 13 */
/*! @{ */

#define XBARA_SEL13_SEL26_MASK                   (0xFFU)
#define XBARA_SEL13_SEL26_SHIFT                  (0U)
#define XBARA_SEL13_SEL26(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL13_SEL26_SHIFT)) & XBARA_SEL13_SEL26_MASK)

#define XBARA_SEL13_SEL27_MASK                   (0xFF00U)
#define XBARA_SEL13_SEL27_SHIFT                  (8U)
#define XBARA_SEL13_SEL27(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL13_SEL27_SHIFT)) & XBARA_SEL13_SEL27_MASK)
/*! @} */

/*! @name SEL14 - Crossbar A Select Register 14 */
/*! @{ */

#define XBARA_SEL14_SEL28_MASK                   (0xFFU)
#define XBARA_SEL14_SEL28_SHIFT                  (0U)
#define XBARA_SEL14_SEL28(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL14_SEL28_SHIFT)) & XBARA_SEL14_SEL28_MASK)

#define XBARA_SEL14_SEL29_MASK                   (0xFF00U)
#define XBARA_SEL14_SEL29_SHIFT                  (8U)
#define XBARA_SEL14_SEL29(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL14_SEL29_SHIFT)) & XBARA_SEL14_SEL29_MASK)
/*! @} */

/*! @name SEL15 - Crossbar A Select Register 15 */
/*! @{ */

#define XBARA_SEL15_SEL30_MASK                   (0xFFU)
#define XBARA_SEL15_SEL30_SHIFT                  (0U)
#define XBARA_SEL15_SEL30(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL15_SEL30_SHIFT)) & XBARA_SEL15_SEL30_MASK)

#define XBARA_SEL15_SEL31_MASK                   (0xFF00U)
#define XBARA_SEL15_SEL31_SHIFT                  (8U)
#define XBARA_SEL15_SEL31(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL15_SEL31_SHIFT)) & XBARA_SEL15_SEL31_MASK)
/*! @} */

/*! @name SEL16 - Crossbar A Select Register 16 */
/*! @{ */

#define XBARA_SEL16_SEL32_MASK                   (0xFFU)
#define XBARA_SEL16_SEL32_SHIFT                  (0U)
#define XBARA_SEL16_SEL32(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL16_SEL32_SHIFT)) & XBARA_SEL16_SEL32_MASK)

#define XBARA_SEL16_SEL33_MASK                   (0xFF00U)
#define XBARA_SEL16_SEL33_SHIFT                  (8U)
#define XBARA_SEL16_SEL33(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL16_SEL33_SHIFT)) & XBARA_SEL16_SEL33_MASK)
/*! @} */

/*! @name SEL17 - Crossbar A Select Register 17 */
/*! @{ */

#define XBARA_SEL17_SEL34_MASK                   (0xFFU)
#define XBARA_SEL17_SEL34_SHIFT                  (0U)
#define XBARA_SEL17_SEL34(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL17_SEL34_SHIFT)) & XBARA_SEL17_SEL34_MASK)

#define XBARA_SEL17_SEL35_MASK                   (0xFF00U)
#define XBARA_SEL17_SEL35_SHIFT                  (8U)
#define XBARA_SEL17_SEL35(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL17_SEL35_SHIFT)) & XBARA_SEL17_SEL35_MASK)
/*! @} */

/*! @name SEL18 - Crossbar A Select Register 18 */
/*! @{ */

#define XBARA_SEL18_SEL36_MASK                   (0xFFU)
#define XBARA_SEL18_SEL36_SHIFT                  (0U)
#define XBARA_SEL18_SEL36(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL18_SEL36_SHIFT)) & XBARA_SEL18_SEL36_MASK)

#define XBARA_SEL18_SEL37_MASK                   (0xFF00U)
#define XBARA_SEL18_SEL37_SHIFT                  (8U)
#define XBARA_SEL18_SEL37(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL18_SEL37_SHIFT)) & XBARA_SEL18_SEL37_MASK)
/*! @} */

/*! @name SEL19 - Crossbar A Select Register 19 */
/*! @{ */

#define XBARA_SEL19_SEL38_MASK                   (0xFFU)
#define XBARA_SEL19_SEL38_SHIFT                  (0U)
#define XBARA_SEL19_SEL38(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL19_SEL38_SHIFT)) & XBARA_SEL19_SEL38_MASK)

#define XBARA_SEL19_SEL39_MASK                   (0xFF00U)
#define XBARA_SEL19_SEL39_SHIFT                  (8U)
#define XBARA_SEL19_SEL39(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL19_SEL39_SHIFT)) & XBARA_SEL19_SEL39_MASK)
/*! @} */

/*! @name SEL20 - Crossbar A Select Register 20 */
/*! @{ */

#define XBARA_SEL20_SEL40_MASK                   (0xFFU)
#define XBARA_SEL20_SEL40_SHIFT                  (0U)
#define XBARA_SEL20_SEL40(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL20_SEL40_SHIFT)) & XBARA_SEL20_SEL40_MASK)

#define XBARA_SEL20_SEL41_MASK                   (0xFF00U)
#define XBARA_SEL20_SEL41_SHIFT                  (8U)
#define XBARA_SEL20_SEL41(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL20_SEL41_SHIFT)) & XBARA_SEL20_SEL41_MASK)
/*! @} */

/*! @name SEL21 - Crossbar A Select Register 21 */
/*! @{ */

#define XBARA_SEL21_SEL42_MASK                   (0xFFU)
#define XBARA_SEL21_SEL42_SHIFT                  (0U)
#define XBARA_SEL21_SEL42(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL21_SEL42_SHIFT)) & XBARA_SEL21_SEL42_MASK)

#define XBARA_SEL21_SEL43_MASK                   (0xFF00U)
#define XBARA_SEL21_SEL43_SHIFT                  (8U)
#define XBARA_SEL21_SEL43(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL21_SEL43_SHIFT)) & XBARA_SEL21_SEL43_MASK)
/*! @} */

/*! @name SEL22 - Crossbar A Select Register 22 */
/*! @{ */

#define XBARA_SEL22_SEL44_MASK                   (0xFFU)
#define XBARA_SEL22_SEL44_SHIFT                  (0U)
#define XBARA_SEL22_SEL44(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL22_SEL44_SHIFT)) & XBARA_SEL22_SEL44_MASK)

#define XBARA_SEL22_SEL45_MASK                   (0xFF00U)
#define XBARA_SEL22_SEL45_SHIFT                  (8U)
#define XBARA_SEL22_SEL45(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL22_SEL45_SHIFT)) & XBARA_SEL22_SEL45_MASK)
/*! @} */

/*! @name SEL23 - Crossbar A Select Register 23 */
/*! @{ */

#define XBARA_SEL23_SEL46_MASK                   (0xFFU)
#define XBARA_SEL23_SEL46_SHIFT                  (0U)
#define XBARA_SEL23_SEL46(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL23_SEL46_SHIFT)) & XBARA_SEL23_SEL46_MASK)

#define XBARA_SEL23_SEL47_MASK                   (0xFF00U)
#define XBARA_SEL23_SEL47_SHIFT                  (8U)
#define XBARA_SEL23_SEL47(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL23_SEL47_SHIFT)) & XBARA_SEL23_SEL47_MASK)
/*! @} */

/*! @name SEL24 - Crossbar A Select Register 24 */
/*! @{ */

#define XBARA_SEL24_SEL48_MASK                   (0xFFU)
#define XBARA_SEL24_SEL48_SHIFT                  (0U)
#define XBARA_SEL24_SEL48(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL24_SEL48_SHIFT)) & XBARA_SEL24_SEL48_MASK)

#define XBARA_SEL24_SEL49_MASK                   (0xFF00U)
#define XBARA_SEL24_SEL49_SHIFT                  (8U)
#define XBARA_SEL24_SEL49(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL24_SEL49_SHIFT)) & XBARA_SEL24_SEL49_MASK)
/*! @} */

/*! @name SEL25 - Crossbar A Select Register 25 */
/*! @{ */

#define XBARA_SEL25_SEL50_MASK                   (0xFFU)
#define XBARA_SEL25_SEL50_SHIFT                  (0U)
#define XBARA_SEL25_SEL50(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL25_SEL50_SHIFT)) & XBARA_SEL25_SEL50_MASK)

#define XBARA_SEL25_SEL51_MASK                   (0xFF00U)
#define XBARA_SEL25_SEL51_SHIFT                  (8U)
#define XBARA_SEL25_SEL51(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL25_SEL51_SHIFT)) & XBARA_SEL25_SEL51_MASK)
/*! @} */

/*! @name SEL26 - Crossbar A Select Register 26 */
/*! @{ */

#define XBARA_SEL26_SEL52_MASK                   (0xFFU)
#define XBARA_SEL26_SEL52_SHIFT                  (0U)
#define XBARA_SEL26_SEL52(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL26_SEL52_SHIFT)) & XBARA_SEL26_SEL52_MASK)

#define XBARA_SEL26_SEL53_MASK                   (0xFF00U)
#define XBARA_SEL26_SEL53_SHIFT                  (8U)
#define XBARA_SEL26_SEL53(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL26_SEL53_SHIFT)) & XBARA_SEL26_SEL53_MASK)
/*! @} */

/*! @name SEL27 - Crossbar A Select Register 27 */
/*! @{ */

#define XBARA_SEL27_SEL54_MASK                   (0xFFU)
#define XBARA_SEL27_SEL54_SHIFT                  (0U)
#define XBARA_SEL27_SEL54(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL27_SEL54_SHIFT)) & XBARA_SEL27_SEL54_MASK)

#define XBARA_SEL27_SEL55_MASK                   (0xFF00U)
#define XBARA_SEL27_SEL55_SHIFT                  (8U)
#define XBARA_SEL27_SEL55(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL27_SEL55_SHIFT)) & XBARA_SEL27_SEL55_MASK)
/*! @} */

/*! @name SEL28 - Crossbar A Select Register 28 */
/*! @{ */

#define XBARA_SEL28_SEL56_MASK                   (0xFFU)
#define XBARA_SEL28_SEL56_SHIFT                  (0U)
#define XBARA_SEL28_SEL56(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL28_SEL56_SHIFT)) & XBARA_SEL28_SEL56_MASK)

#define XBARA_SEL28_SEL57_MASK                   (0xFF00U)
#define XBARA_SEL28_SEL57_SHIFT                  (8U)
#define XBARA_SEL28_SEL57(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL28_SEL57_SHIFT)) & XBARA_SEL28_SEL57_MASK)
/*! @} */

/*! @name SEL29 - Crossbar A Select Register 29 */
/*! @{ */

#define XBARA_SEL29_SEL58_MASK                   (0xFFU)
#define XBARA_SEL29_SEL58_SHIFT                  (0U)
#define XBARA_SEL29_SEL58(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL29_SEL58_SHIFT)) & XBARA_SEL29_SEL58_MASK)

#define XBARA_SEL29_SEL59_MASK                   (0xFF00U)
#define XBARA_SEL29_SEL59_SHIFT                  (8U)
#define XBARA_SEL29_SEL59(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL29_SEL59_SHIFT)) & XBARA_SEL29_SEL59_MASK)
/*! @} */

/*! @name SEL30 - Crossbar A Select Register 30 */
/*! @{ */

#define XBARA_SEL30_SEL60_MASK                   (0xFFU)
#define XBARA_SEL30_SEL60_SHIFT                  (0U)
#define XBARA_SEL30_SEL60(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL30_SEL60_SHIFT)) & XBARA_SEL30_SEL60_MASK)

#define XBARA_SEL30_SEL61_MASK                   (0xFF00U)
#define XBARA_SEL30_SEL61_SHIFT                  (8U)
#define XBARA_SEL30_SEL61(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL30_SEL61_SHIFT)) & XBARA_SEL30_SEL61_MASK)
/*! @} */

/*! @name SEL31 - Crossbar A Select Register 31 */
/*! @{ */

#define XBARA_SEL31_SEL62_MASK                   (0xFFU)
#define XBARA_SEL31_SEL62_SHIFT                  (0U)
#define XBARA_SEL31_SEL62(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL31_SEL62_SHIFT)) & XBARA_SEL31_SEL62_MASK)

#define XBARA_SEL31_SEL63_MASK                   (0xFF00U)
#define XBARA_SEL31_SEL63_SHIFT                  (8U)
#define XBARA_SEL31_SEL63(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL31_SEL63_SHIFT)) & XBARA_SEL31_SEL63_MASK)
/*! @} */

/*! @name SEL32 - Crossbar A Select Register 32 */
/*! @{ */

#define XBARA_SEL32_SEL64_MASK                   (0xFFU)
#define XBARA_SEL32_SEL64_SHIFT                  (0U)
#define XBARA_SEL32_SEL64(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL32_SEL64_SHIFT)) & XBARA_SEL32_SEL64_MASK)

#define XBARA_SEL32_SEL65_MASK                   (0xFF00U)
#define XBARA_SEL32_SEL65_SHIFT                  (8U)
#define XBARA_SEL32_SEL65(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL32_SEL65_SHIFT)) & XBARA_SEL32_SEL65_MASK)
/*! @} */

/*! @name SEL33 - Crossbar A Select Register 33 */
/*! @{ */

#define XBARA_SEL33_SEL66_MASK                   (0xFFU)
#define XBARA_SEL33_SEL66_SHIFT                  (0U)
#define XBARA_SEL33_SEL66(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL33_SEL66_SHIFT)) & XBARA_SEL33_SEL66_MASK)

#define XBARA_SEL33_SEL67_MASK                   (0xFF00U)
#define XBARA_SEL33_SEL67_SHIFT                  (8U)
#define XBARA_SEL33_SEL67(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL33_SEL67_SHIFT)) & XBARA_SEL33_SEL67_MASK)
/*! @} */

/*! @name SEL34 - Crossbar A Select Register 34 */
/*! @{ */

#define XBARA_SEL34_SEL68_MASK                   (0xFFU)
#define XBARA_SEL34_SEL68_SHIFT                  (0U)
#define XBARA_SEL34_SEL68(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL34_SEL68_SHIFT)) & XBARA_SEL34_SEL68_MASK)

#define XBARA_SEL34_SEL69_MASK                   (0xFF00U)
#define XBARA_SEL34_SEL69_SHIFT                  (8U)
#define XBARA_SEL34_SEL69(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL34_SEL69_SHIFT)) & XBARA_SEL34_SEL69_MASK)
/*! @} */

/*! @name SEL35 - Crossbar A Select Register 35 */
/*! @{ */

#define XBARA_SEL35_SEL70_MASK                   (0xFFU)
#define XBARA_SEL35_SEL70_SHIFT                  (0U)
#define XBARA_SEL35_SEL70(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL35_SEL70_SHIFT)) & XBARA_SEL35_SEL70_MASK)

#define XBARA_SEL35_SEL71_MASK                   (0xFF00U)
#define XBARA_SEL35_SEL71_SHIFT                  (8U)
#define XBARA_SEL35_SEL71(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL35_SEL71_SHIFT)) & XBARA_SEL35_SEL71_MASK)
/*! @} */

/*! @name SEL36 - Crossbar A Select Register 36 */
/*! @{ */

#define XBARA_SEL36_SEL72_MASK                   (0xFFU)
#define XBARA_SEL36_SEL72_SHIFT                  (0U)
#define XBARA_SEL36_SEL72(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL36_SEL72_SHIFT)) & XBARA_SEL36_SEL72_MASK)

#define XBARA_SEL36_SEL73_MASK                   (0xFF00U)
#define XBARA_SEL36_SEL73_SHIFT                  (8U)
#define XBARA_SEL36_SEL73(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL36_SEL73_SHIFT)) & XBARA_SEL36_SEL73_MASK)
/*! @} */

/*! @name SEL37 - Crossbar A Select Register 37 */
/*! @{ */

#define XBARA_SEL37_SEL74_MASK                   (0xFFU)
#define XBARA_SEL37_SEL74_SHIFT                  (0U)
#define XBARA_SEL37_SEL74(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL37_SEL74_SHIFT)) & XBARA_SEL37_SEL74_MASK)

#define XBARA_SEL37_SEL75_MASK                   (0xFF00U)
#define XBARA_SEL37_SEL75_SHIFT                  (8U)
#define XBARA_SEL37_SEL75(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL37_SEL75_SHIFT)) & XBARA_SEL37_SEL75_MASK)
/*! @} */

/*! @name SEL38 - Crossbar A Select Register 38 */
/*! @{ */

#define XBARA_SEL38_SEL76_MASK                   (0xFFU)
#define XBARA_SEL38_SEL76_SHIFT                  (0U)
#define XBARA_SEL38_SEL76(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL38_SEL76_SHIFT)) & XBARA_SEL38_SEL76_MASK)

#define XBARA_SEL38_SEL77_MASK                   (0xFF00U)
#define XBARA_SEL38_SEL77_SHIFT                  (8U)
#define XBARA_SEL38_SEL77(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL38_SEL77_SHIFT)) & XBARA_SEL38_SEL77_MASK)
/*! @} */

/*! @name SEL39 - Crossbar A Select Register 39 */
/*! @{ */

#define XBARA_SEL39_SEL78_MASK                   (0xFFU)
#define XBARA_SEL39_SEL78_SHIFT                  (0U)
#define XBARA_SEL39_SEL78(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL39_SEL78_SHIFT)) & XBARA_SEL39_SEL78_MASK)

#define XBARA_SEL39_SEL79_MASK                   (0xFF00U)
#define XBARA_SEL39_SEL79_SHIFT                  (8U)
#define XBARA_SEL39_SEL79(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL39_SEL79_SHIFT)) & XBARA_SEL39_SEL79_MASK)
/*! @} */

/*! @name SEL40 - Crossbar A Select Register 40 */
/*! @{ */

#define XBARA_SEL40_SEL80_MASK                   (0xFFU)
#define XBARA_SEL40_SEL80_SHIFT                  (0U)
#define XBARA_SEL40_SEL80(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL40_SEL80_SHIFT)) & XBARA_SEL40_SEL80_MASK)

#define XBARA_SEL40_SEL81_MASK                   (0xFF00U)
#define XBARA_SEL40_SEL81_SHIFT                  (8U)
#define XBARA_SEL40_SEL81(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL40_SEL81_SHIFT)) & XBARA_SEL40_SEL81_MASK)
/*! @} */

/*! @name SEL41 - Crossbar A Select Register 41 */
/*! @{ */

#define XBARA_SEL41_SEL82_MASK                   (0xFFU)
#define XBARA_SEL41_SEL82_SHIFT                  (0U)
#define XBARA_SEL41_SEL82(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL41_SEL82_SHIFT)) & XBARA_SEL41_SEL82_MASK)

#define XBARA_SEL41_SEL83_MASK                   (0xFF00U)
#define XBARA_SEL41_SEL83_SHIFT                  (8U)
#define XBARA_SEL41_SEL83(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL41_SEL83_SHIFT)) & XBARA_SEL41_SEL83_MASK)
/*! @} */

/*! @name SEL42 - Crossbar A Select Register 42 */
/*! @{ */

#define XBARA_SEL42_SEL84_MASK                   (0xFFU)
#define XBARA_SEL42_SEL84_SHIFT                  (0U)
#define XBARA_SEL42_SEL84(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL42_SEL84_SHIFT)) & XBARA_SEL42_SEL84_MASK)

#define XBARA_SEL42_SEL85_MASK                   (0xFF00U)
#define XBARA_SEL42_SEL85_SHIFT                  (8U)
#define XBARA_SEL42_SEL85(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL42_SEL85_SHIFT)) & XBARA_SEL42_SEL85_MASK)
/*! @} */

/*! @name SEL43 - Crossbar A Select Register 43 */
/*! @{ */

#define XBARA_SEL43_SEL86_MASK                   (0xFFU)
#define XBARA_SEL43_SEL86_SHIFT                  (0U)
#define XBARA_SEL43_SEL86(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL43_SEL86_SHIFT)) & XBARA_SEL43_SEL86_MASK)

#define XBARA_SEL43_SEL87_MASK                   (0xFF00U)
#define XBARA_SEL43_SEL87_SHIFT                  (8U)
#define XBARA_SEL43_SEL87(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL43_SEL87_SHIFT)) & XBARA_SEL43_SEL87_MASK)
/*! @} */

/*! @name SEL44 - Crossbar A Select Register 44 */
/*! @{ */

#define XBARA_SEL44_SEL88_MASK                   (0xFFU)
#define XBARA_SEL44_SEL88_SHIFT                  (0U)
#define XBARA_SEL44_SEL88(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL44_SEL88_SHIFT)) & XBARA_SEL44_SEL88_MASK)

#define XBARA_SEL44_SEL89_MASK                   (0xFF00U)
#define XBARA_SEL44_SEL89_SHIFT                  (8U)
#define XBARA_SEL44_SEL89(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL44_SEL89_SHIFT)) & XBARA_SEL44_SEL89_MASK)
/*! @} */

/*! @name SEL45 - Crossbar A Select Register 45 */
/*! @{ */

#define XBARA_SEL45_SEL90_MASK                   (0xFFU)
#define XBARA_SEL45_SEL90_SHIFT                  (0U)
#define XBARA_SEL45_SEL90(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL45_SEL90_SHIFT)) & XBARA_SEL45_SEL90_MASK)

#define XBARA_SEL45_SEL91_MASK                   (0xFF00U)
#define XBARA_SEL45_SEL91_SHIFT                  (8U)
#define XBARA_SEL45_SEL91(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL45_SEL91_SHIFT)) & XBARA_SEL45_SEL91_MASK)
/*! @} */

/*! @name SEL46 - Crossbar A Select Register 46 */
/*! @{ */

#define XBARA_SEL46_SEL92_MASK                   (0xFFU)
#define XBARA_SEL46_SEL92_SHIFT                  (0U)
#define XBARA_SEL46_SEL92(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL46_SEL92_SHIFT)) & XBARA_SEL46_SEL92_MASK)

#define XBARA_SEL46_SEL93_MASK                   (0xFF00U)
#define XBARA_SEL46_SEL93_SHIFT                  (8U)
#define XBARA_SEL46_SEL93(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL46_SEL93_SHIFT)) & XBARA_SEL46_SEL93_MASK)
/*! @} */

/*! @name SEL47 - Crossbar A Select Register 47 */
/*! @{ */

#define XBARA_SEL47_SEL94_MASK                   (0xFFU)
#define XBARA_SEL47_SEL94_SHIFT                  (0U)
#define XBARA_SEL47_SEL94(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL47_SEL94_SHIFT)) & XBARA_SEL47_SEL94_MASK)

#define XBARA_SEL47_SEL95_MASK                   (0xFF00U)
#define XBARA_SEL47_SEL95_SHIFT                  (8U)
#define XBARA_SEL47_SEL95(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL47_SEL95_SHIFT)) & XBARA_SEL47_SEL95_MASK)
/*! @} */

/*! @name SEL48 - Crossbar A Select Register 48 */
/*! @{ */

#define XBARA_SEL48_SEL96_MASK                   (0xFFU)
#define XBARA_SEL48_SEL96_SHIFT                  (0U)
#define XBARA_SEL48_SEL96(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL48_SEL96_SHIFT)) & XBARA_SEL48_SEL96_MASK)

#define XBARA_SEL48_SEL97_MASK                   (0xFF00U)
#define XBARA_SEL48_SEL97_SHIFT                  (8U)
#define XBARA_SEL48_SEL97(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL48_SEL97_SHIFT)) & XBARA_SEL48_SEL97_MASK)
/*! @} */

/*! @name SEL49 - Crossbar A Select Register 49 */
/*! @{ */

#define XBARA_SEL49_SEL98_MASK                   (0xFFU)
#define XBARA_SEL49_SEL98_SHIFT                  (0U)
#define XBARA_SEL49_SEL98(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL49_SEL98_SHIFT)) & XBARA_SEL49_SEL98_MASK)

#define XBARA_SEL49_SEL99_MASK                   (0xFF00U)
#define XBARA_SEL49_SEL99_SHIFT                  (8U)
#define XBARA_SEL49_SEL99(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_SEL49_SEL99_SHIFT)) & XBARA_SEL49_SEL99_MASK)
/*! @} */

/*! @name SEL50 - Crossbar A Select Register 50 */
/*! @{ */

#define XBARA_SEL50_SEL100_MASK                  (0xFFU)
#define XBARA_SEL50_SEL100_SHIFT                 (0U)
#define XBARA_SEL50_SEL100(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL50_SEL100_SHIFT)) & XBARA_SEL50_SEL100_MASK)

#define XBARA_SEL50_SEL101_MASK                  (0xFF00U)
#define XBARA_SEL50_SEL101_SHIFT                 (8U)
#define XBARA_SEL50_SEL101(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL50_SEL101_SHIFT)) & XBARA_SEL50_SEL101_MASK)
/*! @} */

/*! @name SEL51 - Crossbar A Select Register 51 */
/*! @{ */

#define XBARA_SEL51_SEL102_MASK                  (0xFFU)
#define XBARA_SEL51_SEL102_SHIFT                 (0U)
#define XBARA_SEL51_SEL102(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL51_SEL102_SHIFT)) & XBARA_SEL51_SEL102_MASK)

#define XBARA_SEL51_SEL103_MASK                  (0xFF00U)
#define XBARA_SEL51_SEL103_SHIFT                 (8U)
#define XBARA_SEL51_SEL103(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL51_SEL103_SHIFT)) & XBARA_SEL51_SEL103_MASK)
/*! @} */

/*! @name SEL52 - Crossbar A Select Register 52 */
/*! @{ */

#define XBARA_SEL52_SEL104_MASK                  (0xFFU)
#define XBARA_SEL52_SEL104_SHIFT                 (0U)
#define XBARA_SEL52_SEL104(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL52_SEL104_SHIFT)) & XBARA_SEL52_SEL104_MASK)

#define XBARA_SEL52_SEL105_MASK                  (0xFF00U)
#define XBARA_SEL52_SEL105_SHIFT                 (8U)
#define XBARA_SEL52_SEL105(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL52_SEL105_SHIFT)) & XBARA_SEL52_SEL105_MASK)
/*! @} */

/*! @name SEL53 - Crossbar A Select Register 53 */
/*! @{ */

#define XBARA_SEL53_SEL106_MASK                  (0xFFU)
#define XBARA_SEL53_SEL106_SHIFT                 (0U)
#define XBARA_SEL53_SEL106(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL53_SEL106_SHIFT)) & XBARA_SEL53_SEL106_MASK)

#define XBARA_SEL53_SEL107_MASK                  (0xFF00U)
#define XBARA_SEL53_SEL107_SHIFT                 (8U)
#define XBARA_SEL53_SEL107(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL53_SEL107_SHIFT)) & XBARA_SEL53_SEL107_MASK)
/*! @} */

/*! @name SEL54 - Crossbar A Select Register 54 */
/*! @{ */

#define XBARA_SEL54_SEL108_MASK                  (0xFFU)
#define XBARA_SEL54_SEL108_SHIFT                 (0U)
#define XBARA_SEL54_SEL108(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL54_SEL108_SHIFT)) & XBARA_SEL54_SEL108_MASK)

#define XBARA_SEL54_SEL109_MASK                  (0xFF00U)
#define XBARA_SEL54_SEL109_SHIFT                 (8U)
#define XBARA_SEL54_SEL109(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL54_SEL109_SHIFT)) & XBARA_SEL54_SEL109_MASK)
/*! @} */

/*! @name SEL55 - Crossbar A Select Register 55 */
/*! @{ */

#define XBARA_SEL55_SEL110_MASK                  (0xFFU)
#define XBARA_SEL55_SEL110_SHIFT                 (0U)
#define XBARA_SEL55_SEL110(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL55_SEL110_SHIFT)) & XBARA_SEL55_SEL110_MASK)

#define XBARA_SEL55_SEL111_MASK                  (0xFF00U)
#define XBARA_SEL55_SEL111_SHIFT                 (8U)
#define XBARA_SEL55_SEL111(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL55_SEL111_SHIFT)) & XBARA_SEL55_SEL111_MASK)
/*! @} */

/*! @name SEL56 - Crossbar A Select Register 56 */
/*! @{ */

#define XBARA_SEL56_SEL112_MASK                  (0xFFU)
#define XBARA_SEL56_SEL112_SHIFT                 (0U)
#define XBARA_SEL56_SEL112(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL56_SEL112_SHIFT)) & XBARA_SEL56_SEL112_MASK)

#define XBARA_SEL56_SEL113_MASK                  (0xFF00U)
#define XBARA_SEL56_SEL113_SHIFT                 (8U)
#define XBARA_SEL56_SEL113(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL56_SEL113_SHIFT)) & XBARA_SEL56_SEL113_MASK)
/*! @} */

/*! @name SEL57 - Crossbar A Select Register 57 */
/*! @{ */

#define XBARA_SEL57_SEL114_MASK                  (0xFFU)
#define XBARA_SEL57_SEL114_SHIFT                 (0U)
#define XBARA_SEL57_SEL114(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL57_SEL114_SHIFT)) & XBARA_SEL57_SEL114_MASK)

#define XBARA_SEL57_SEL115_MASK                  (0xFF00U)
#define XBARA_SEL57_SEL115_SHIFT                 (8U)
#define XBARA_SEL57_SEL115(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL57_SEL115_SHIFT)) & XBARA_SEL57_SEL115_MASK)
/*! @} */

/*! @name SEL58 - Crossbar A Select Register 58 */
/*! @{ */

#define XBARA_SEL58_SEL116_MASK                  (0xFFU)
#define XBARA_SEL58_SEL116_SHIFT                 (0U)
#define XBARA_SEL58_SEL116(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL58_SEL116_SHIFT)) & XBARA_SEL58_SEL116_MASK)

#define XBARA_SEL58_SEL117_MASK                  (0xFF00U)
#define XBARA_SEL58_SEL117_SHIFT                 (8U)
#define XBARA_SEL58_SEL117(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL58_SEL117_SHIFT)) & XBARA_SEL58_SEL117_MASK)
/*! @} */

/*! @name SEL59 - Crossbar A Select Register 59 */
/*! @{ */

#define XBARA_SEL59_SEL118_MASK                  (0xFFU)
#define XBARA_SEL59_SEL118_SHIFT                 (0U)
#define XBARA_SEL59_SEL118(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL59_SEL118_SHIFT)) & XBARA_SEL59_SEL118_MASK)

#define XBARA_SEL59_SEL119_MASK                  (0xFF00U)
#define XBARA_SEL59_SEL119_SHIFT                 (8U)
#define XBARA_SEL59_SEL119(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL59_SEL119_SHIFT)) & XBARA_SEL59_SEL119_MASK)
/*! @} */

/*! @name SEL60 - Crossbar A Select Register 60 */
/*! @{ */

#define XBARA_SEL60_SEL120_MASK                  (0xFFU)
#define XBARA_SEL60_SEL120_SHIFT                 (0U)
#define XBARA_SEL60_SEL120(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL60_SEL120_SHIFT)) & XBARA_SEL60_SEL120_MASK)

#define XBARA_SEL60_SEL121_MASK                  (0xFF00U)
#define XBARA_SEL60_SEL121_SHIFT                 (8U)
#define XBARA_SEL60_SEL121(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL60_SEL121_SHIFT)) & XBARA_SEL60_SEL121_MASK)
/*! @} */

/*! @name SEL61 - Crossbar A Select Register 61 */
/*! @{ */

#define XBARA_SEL61_SEL122_MASK                  (0xFFU)
#define XBARA_SEL61_SEL122_SHIFT                 (0U)
#define XBARA_SEL61_SEL122(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL61_SEL122_SHIFT)) & XBARA_SEL61_SEL122_MASK)

#define XBARA_SEL61_SEL123_MASK                  (0xFF00U)
#define XBARA_SEL61_SEL123_SHIFT                 (8U)
#define XBARA_SEL61_SEL123(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL61_SEL123_SHIFT)) & XBARA_SEL61_SEL123_MASK)
/*! @} */

/*! @name SEL62 - Crossbar A Select Register 62 */
/*! @{ */

#define XBARA_SEL62_SEL124_MASK                  (0xFFU)
#define XBARA_SEL62_SEL124_SHIFT                 (0U)
#define XBARA_SEL62_SEL124(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL62_SEL124_SHIFT)) & XBARA_SEL62_SEL124_MASK)

#define XBARA_SEL62_SEL125_MASK                  (0xFF00U)
#define XBARA_SEL62_SEL125_SHIFT                 (8U)
#define XBARA_SEL62_SEL125(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL62_SEL125_SHIFT)) & XBARA_SEL62_SEL125_MASK)
/*! @} */

/*! @name SEL63 - Crossbar A Select Register 63 */
/*! @{ */

#define XBARA_SEL63_SEL126_MASK                  (0xFFU)
#define XBARA_SEL63_SEL126_SHIFT                 (0U)
#define XBARA_SEL63_SEL126(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL63_SEL126_SHIFT)) & XBARA_SEL63_SEL126_MASK)

#define XBARA_SEL63_SEL127_MASK                  (0xFF00U)
#define XBARA_SEL63_SEL127_SHIFT                 (8U)
#define XBARA_SEL63_SEL127(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL63_SEL127_SHIFT)) & XBARA_SEL63_SEL127_MASK)
/*! @} */

/*! @name SEL64 - Crossbar A Select Register 64 */
/*! @{ */

#define XBARA_SEL64_SEL128_MASK                  (0xFFU)
#define XBARA_SEL64_SEL128_SHIFT                 (0U)
#define XBARA_SEL64_SEL128(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL64_SEL128_SHIFT)) & XBARA_SEL64_SEL128_MASK)

#define XBARA_SEL64_SEL129_MASK                  (0xFF00U)
#define XBARA_SEL64_SEL129_SHIFT                 (8U)
#define XBARA_SEL64_SEL129(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL64_SEL129_SHIFT)) & XBARA_SEL64_SEL129_MASK)
/*! @} */

/*! @name SEL65 - Crossbar A Select Register 65 */
/*! @{ */

#define XBARA_SEL65_SEL130_MASK                  (0xFFU)
#define XBARA_SEL65_SEL130_SHIFT                 (0U)
#define XBARA_SEL65_SEL130(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL65_SEL130_SHIFT)) & XBARA_SEL65_SEL130_MASK)

#define XBARA_SEL65_SEL131_MASK                  (0xFF00U)
#define XBARA_SEL65_SEL131_SHIFT                 (8U)
#define XBARA_SEL65_SEL131(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL65_SEL131_SHIFT)) & XBARA_SEL65_SEL131_MASK)
/*! @} */

/*! @name SEL66 - Crossbar A Select Register 66 */
/*! @{ */

#define XBARA_SEL66_SEL132_MASK                  (0xFFU)
#define XBARA_SEL66_SEL132_SHIFT                 (0U)
#define XBARA_SEL66_SEL132(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL66_SEL132_SHIFT)) & XBARA_SEL66_SEL132_MASK)

#define XBARA_SEL66_SEL133_MASK                  (0xFF00U)
#define XBARA_SEL66_SEL133_SHIFT                 (8U)
#define XBARA_SEL66_SEL133(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL66_SEL133_SHIFT)) & XBARA_SEL66_SEL133_MASK)
/*! @} */

/*! @name SEL67 - Crossbar A Select Register 67 */
/*! @{ */

#define XBARA_SEL67_SEL134_MASK                  (0xFFU)
#define XBARA_SEL67_SEL134_SHIFT                 (0U)
#define XBARA_SEL67_SEL134(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL67_SEL134_SHIFT)) & XBARA_SEL67_SEL134_MASK)

#define XBARA_SEL67_SEL135_MASK                  (0xFF00U)
#define XBARA_SEL67_SEL135_SHIFT                 (8U)
#define XBARA_SEL67_SEL135(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL67_SEL135_SHIFT)) & XBARA_SEL67_SEL135_MASK)
/*! @} */

/*! @name SEL68 - Crossbar A Select Register 68 */
/*! @{ */

#define XBARA_SEL68_SEL136_MASK                  (0xFFU)
#define XBARA_SEL68_SEL136_SHIFT                 (0U)
#define XBARA_SEL68_SEL136(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL68_SEL136_SHIFT)) & XBARA_SEL68_SEL136_MASK)

#define XBARA_SEL68_SEL137_MASK                  (0xFF00U)
#define XBARA_SEL68_SEL137_SHIFT                 (8U)
#define XBARA_SEL68_SEL137(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL68_SEL137_SHIFT)) & XBARA_SEL68_SEL137_MASK)
/*! @} */

/*! @name SEL69 - Crossbar A Select Register 69 */
/*! @{ */

#define XBARA_SEL69_SEL138_MASK                  (0xFFU)
#define XBARA_SEL69_SEL138_SHIFT                 (0U)
#define XBARA_SEL69_SEL138(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL69_SEL138_SHIFT)) & XBARA_SEL69_SEL138_MASK)

#define XBARA_SEL69_SEL139_MASK                  (0xFF00U)
#define XBARA_SEL69_SEL139_SHIFT                 (8U)
#define XBARA_SEL69_SEL139(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL69_SEL139_SHIFT)) & XBARA_SEL69_SEL139_MASK)
/*! @} */

/*! @name SEL70 - Crossbar A Select Register 70 */
/*! @{ */

#define XBARA_SEL70_SEL140_MASK                  (0xFFU)
#define XBARA_SEL70_SEL140_SHIFT                 (0U)
#define XBARA_SEL70_SEL140(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL70_SEL140_SHIFT)) & XBARA_SEL70_SEL140_MASK)

#define XBARA_SEL70_SEL141_MASK                  (0xFF00U)
#define XBARA_SEL70_SEL141_SHIFT                 (8U)
#define XBARA_SEL70_SEL141(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL70_SEL141_SHIFT)) & XBARA_SEL70_SEL141_MASK)
/*! @} */

/*! @name SEL71 - Crossbar A Select Register 71 */
/*! @{ */

#define XBARA_SEL71_SEL142_MASK                  (0xFFU)
#define XBARA_SEL71_SEL142_SHIFT                 (0U)
#define XBARA_SEL71_SEL142(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL71_SEL142_SHIFT)) & XBARA_SEL71_SEL142_MASK)

#define XBARA_SEL71_SEL143_MASK                  (0xFF00U)
#define XBARA_SEL71_SEL143_SHIFT                 (8U)
#define XBARA_SEL71_SEL143(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL71_SEL143_SHIFT)) & XBARA_SEL71_SEL143_MASK)
/*! @} */

/*! @name SEL72 - Crossbar A Select Register 72 */
/*! @{ */

#define XBARA_SEL72_SEL144_MASK                  (0xFFU)
#define XBARA_SEL72_SEL144_SHIFT                 (0U)
#define XBARA_SEL72_SEL144(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL72_SEL144_SHIFT)) & XBARA_SEL72_SEL144_MASK)

#define XBARA_SEL72_SEL145_MASK                  (0xFF00U)
#define XBARA_SEL72_SEL145_SHIFT                 (8U)
#define XBARA_SEL72_SEL145(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL72_SEL145_SHIFT)) & XBARA_SEL72_SEL145_MASK)
/*! @} */

/*! @name SEL73 - Crossbar A Select Register 73 */
/*! @{ */

#define XBARA_SEL73_SEL146_MASK                  (0xFFU)
#define XBARA_SEL73_SEL146_SHIFT                 (0U)
#define XBARA_SEL73_SEL146(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL73_SEL146_SHIFT)) & XBARA_SEL73_SEL146_MASK)

#define XBARA_SEL73_SEL147_MASK                  (0xFF00U)
#define XBARA_SEL73_SEL147_SHIFT                 (8U)
#define XBARA_SEL73_SEL147(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL73_SEL147_SHIFT)) & XBARA_SEL73_SEL147_MASK)
/*! @} */

/*! @name SEL74 - Crossbar A Select Register 74 */
/*! @{ */

#define XBARA_SEL74_SEL148_MASK                  (0xFFU)
#define XBARA_SEL74_SEL148_SHIFT                 (0U)
#define XBARA_SEL74_SEL148(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL74_SEL148_SHIFT)) & XBARA_SEL74_SEL148_MASK)

#define XBARA_SEL74_SEL149_MASK                  (0xFF00U)
#define XBARA_SEL74_SEL149_SHIFT                 (8U)
#define XBARA_SEL74_SEL149(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL74_SEL149_SHIFT)) & XBARA_SEL74_SEL149_MASK)
/*! @} */

/*! @name SEL75 - Crossbar A Select Register 75 */
/*! @{ */

#define XBARA_SEL75_SEL150_MASK                  (0xFFU)
#define XBARA_SEL75_SEL150_SHIFT                 (0U)
#define XBARA_SEL75_SEL150(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL75_SEL150_SHIFT)) & XBARA_SEL75_SEL150_MASK)

#define XBARA_SEL75_SEL151_MASK                  (0xFF00U)
#define XBARA_SEL75_SEL151_SHIFT                 (8U)
#define XBARA_SEL75_SEL151(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL75_SEL151_SHIFT)) & XBARA_SEL75_SEL151_MASK)
/*! @} */

/*! @name SEL76 - Crossbar A Select Register 76 */
/*! @{ */

#define XBARA_SEL76_SEL152_MASK                  (0xFFU)
#define XBARA_SEL76_SEL152_SHIFT                 (0U)
#define XBARA_SEL76_SEL152(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL76_SEL152_SHIFT)) & XBARA_SEL76_SEL152_MASK)

#define XBARA_SEL76_SEL153_MASK                  (0xFF00U)
#define XBARA_SEL76_SEL153_SHIFT                 (8U)
#define XBARA_SEL76_SEL153(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL76_SEL153_SHIFT)) & XBARA_SEL76_SEL153_MASK)
/*! @} */

/*! @name SEL77 - Crossbar A Select Register 77 */
/*! @{ */

#define XBARA_SEL77_SEL154_MASK                  (0xFFU)
#define XBARA_SEL77_SEL154_SHIFT                 (0U)
#define XBARA_SEL77_SEL154(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL77_SEL154_SHIFT)) & XBARA_SEL77_SEL154_MASK)

#define XBARA_SEL77_SEL155_MASK                  (0xFF00U)
#define XBARA_SEL77_SEL155_SHIFT                 (8U)
#define XBARA_SEL77_SEL155(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL77_SEL155_SHIFT)) & XBARA_SEL77_SEL155_MASK)
/*! @} */

/*! @name SEL78 - Crossbar A Select Register 78 */
/*! @{ */

#define XBARA_SEL78_SEL156_MASK                  (0xFFU)
#define XBARA_SEL78_SEL156_SHIFT                 (0U)
#define XBARA_SEL78_SEL156(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL78_SEL156_SHIFT)) & XBARA_SEL78_SEL156_MASK)

#define XBARA_SEL78_SEL157_MASK                  (0xFF00U)
#define XBARA_SEL78_SEL157_SHIFT                 (8U)
#define XBARA_SEL78_SEL157(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL78_SEL157_SHIFT)) & XBARA_SEL78_SEL157_MASK)
/*! @} */

/*! @name SEL79 - Crossbar A Select Register 79 */
/*! @{ */

#define XBARA_SEL79_SEL158_MASK                  (0xFFU)
#define XBARA_SEL79_SEL158_SHIFT                 (0U)
#define XBARA_SEL79_SEL158(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL79_SEL158_SHIFT)) & XBARA_SEL79_SEL158_MASK)

#define XBARA_SEL79_SEL159_MASK                  (0xFF00U)
#define XBARA_SEL79_SEL159_SHIFT                 (8U)
#define XBARA_SEL79_SEL159(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL79_SEL159_SHIFT)) & XBARA_SEL79_SEL159_MASK)
/*! @} */

/*! @name SEL80 - Crossbar A Select Register 80 */
/*! @{ */

#define XBARA_SEL80_SEL160_MASK                  (0xFFU)
#define XBARA_SEL80_SEL160_SHIFT                 (0U)
#define XBARA_SEL80_SEL160(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL80_SEL160_SHIFT)) & XBARA_SEL80_SEL160_MASK)

#define XBARA_SEL80_SEL161_MASK                  (0xFF00U)
#define XBARA_SEL80_SEL161_SHIFT                 (8U)
#define XBARA_SEL80_SEL161(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL80_SEL161_SHIFT)) & XBARA_SEL80_SEL161_MASK)
/*! @} */

/*! @name SEL81 - Crossbar A Select Register 81 */
/*! @{ */

#define XBARA_SEL81_SEL162_MASK                  (0xFFU)
#define XBARA_SEL81_SEL162_SHIFT                 (0U)
#define XBARA_SEL81_SEL162(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL81_SEL162_SHIFT)) & XBARA_SEL81_SEL162_MASK)

#define XBARA_SEL81_SEL163_MASK                  (0xFF00U)
#define XBARA_SEL81_SEL163_SHIFT                 (8U)
#define XBARA_SEL81_SEL163(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL81_SEL163_SHIFT)) & XBARA_SEL81_SEL163_MASK)
/*! @} */

/*! @name SEL82 - Crossbar A Select Register 82 */
/*! @{ */

#define XBARA_SEL82_SEL164_MASK                  (0xFFU)
#define XBARA_SEL82_SEL164_SHIFT                 (0U)
#define XBARA_SEL82_SEL164(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL82_SEL164_SHIFT)) & XBARA_SEL82_SEL164_MASK)

#define XBARA_SEL82_SEL165_MASK                  (0xFF00U)
#define XBARA_SEL82_SEL165_SHIFT                 (8U)
#define XBARA_SEL82_SEL165(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL82_SEL165_SHIFT)) & XBARA_SEL82_SEL165_MASK)
/*! @} */

/*! @name SEL83 - Crossbar A Select Register 83 */
/*! @{ */

#define XBARA_SEL83_SEL166_MASK                  (0xFFU)
#define XBARA_SEL83_SEL166_SHIFT                 (0U)
#define XBARA_SEL83_SEL166(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL83_SEL166_SHIFT)) & XBARA_SEL83_SEL166_MASK)

#define XBARA_SEL83_SEL167_MASK                  (0xFF00U)
#define XBARA_SEL83_SEL167_SHIFT                 (8U)
#define XBARA_SEL83_SEL167(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL83_SEL167_SHIFT)) & XBARA_SEL83_SEL167_MASK)
/*! @} */

/*! @name SEL84 - Crossbar A Select Register 84 */
/*! @{ */

#define XBARA_SEL84_SEL168_MASK                  (0xFFU)
#define XBARA_SEL84_SEL168_SHIFT                 (0U)
#define XBARA_SEL84_SEL168(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL84_SEL168_SHIFT)) & XBARA_SEL84_SEL168_MASK)

#define XBARA_SEL84_SEL169_MASK                  (0xFF00U)
#define XBARA_SEL84_SEL169_SHIFT                 (8U)
#define XBARA_SEL84_SEL169(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL84_SEL169_SHIFT)) & XBARA_SEL84_SEL169_MASK)
/*! @} */

/*! @name SEL85 - Crossbar A Select Register 85 */
/*! @{ */

#define XBARA_SEL85_SEL170_MASK                  (0xFFU)
#define XBARA_SEL85_SEL170_SHIFT                 (0U)
#define XBARA_SEL85_SEL170(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL85_SEL170_SHIFT)) & XBARA_SEL85_SEL170_MASK)

#define XBARA_SEL85_SEL171_MASK                  (0xFF00U)
#define XBARA_SEL85_SEL171_SHIFT                 (8U)
#define XBARA_SEL85_SEL171(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL85_SEL171_SHIFT)) & XBARA_SEL85_SEL171_MASK)
/*! @} */

/*! @name SEL86 - Crossbar A Select Register 86 */
/*! @{ */

#define XBARA_SEL86_SEL172_MASK                  (0xFFU)
#define XBARA_SEL86_SEL172_SHIFT                 (0U)
#define XBARA_SEL86_SEL172(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL86_SEL172_SHIFT)) & XBARA_SEL86_SEL172_MASK)

#define XBARA_SEL86_SEL173_MASK                  (0xFF00U)
#define XBARA_SEL86_SEL173_SHIFT                 (8U)
#define XBARA_SEL86_SEL173(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL86_SEL173_SHIFT)) & XBARA_SEL86_SEL173_MASK)
/*! @} */

/*! @name SEL87 - Crossbar A Select Register 87 */
/*! @{ */

#define XBARA_SEL87_SEL174_MASK                  (0xFFU)
#define XBARA_SEL87_SEL174_SHIFT                 (0U)
#define XBARA_SEL87_SEL174(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL87_SEL174_SHIFT)) & XBARA_SEL87_SEL174_MASK)

#define XBARA_SEL87_SEL175_MASK                  (0xFF00U)
#define XBARA_SEL87_SEL175_SHIFT                 (8U)
#define XBARA_SEL87_SEL175(x)                    (((uint16_t)(((uint16_t)(x)) << XBARA_SEL87_SEL175_SHIFT)) & XBARA_SEL87_SEL175_MASK)
/*! @} */

/*! @name CTRL0 - Crossbar A Control Register 0 */
/*! @{ */

#define XBARA_CTRL0_DEN0_MASK                    (0x1U)
#define XBARA_CTRL0_DEN0_SHIFT                   (0U)
/*! DEN0 - DMA Enable for XBAR_OUT0
 *  0b0..DMA disabled
 *  0b1..DMA enabled
 */
#define XBARA_CTRL0_DEN0(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_DEN0_SHIFT)) & XBARA_CTRL0_DEN0_MASK)

#define XBARA_CTRL0_IEN0_MASK                    (0x2U)
#define XBARA_CTRL0_IEN0_SHIFT                   (1U)
/*! IEN0 - Interrupt Enable for XBAR_OUT0
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define XBARA_CTRL0_IEN0(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_IEN0_SHIFT)) & XBARA_CTRL0_IEN0_MASK)

#define XBARA_CTRL0_EDGE0_MASK                   (0xCU)
#define XBARA_CTRL0_EDGE0_SHIFT                  (2U)
/*! EDGE0 - Active edge for edge detection on XBAR_OUT0
 *  0b00..STS0 never asserts
 *  0b01..STS0 asserts on rising edges of XBAR_OUT0
 *  0b10..STS0 asserts on falling edges of XBAR_OUT0
 *  0b11..STS0 asserts on rising and falling edges of XBAR_OUT0
 */
#define XBARA_CTRL0_EDGE0(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_EDGE0_SHIFT)) & XBARA_CTRL0_EDGE0_MASK)

#define XBARA_CTRL0_STS0_MASK                    (0x10U)
#define XBARA_CTRL0_STS0_SHIFT                   (4U)
/*! STS0 - Edge detection status for XBAR_OUT0
 *  0b0..Active edge not yet detected on XBAR_OUT0
 *  0b1..Active edge detected on XBAR_OUT0
 */
#define XBARA_CTRL0_STS0(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_STS0_SHIFT)) & XBARA_CTRL0_STS0_MASK)

#define XBARA_CTRL0_DEN1_MASK                    (0x100U)
#define XBARA_CTRL0_DEN1_SHIFT                   (8U)
/*! DEN1 - DMA Enable for XBAR_OUT1
 *  0b0..DMA disabled
 *  0b1..DMA enabled
 */
#define XBARA_CTRL0_DEN1(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_DEN1_SHIFT)) & XBARA_CTRL0_DEN1_MASK)

#define XBARA_CTRL0_IEN1_MASK                    (0x200U)
#define XBARA_CTRL0_IEN1_SHIFT                   (9U)
/*! IEN1 - Interrupt Enable for XBAR_OUT1
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define XBARA_CTRL0_IEN1(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_IEN1_SHIFT)) & XBARA_CTRL0_IEN1_MASK)

#define XBARA_CTRL0_EDGE1_MASK                   (0xC00U)
#define XBARA_CTRL0_EDGE1_SHIFT                  (10U)
/*! EDGE1 - Active edge for edge detection on XBAR_OUT1
 *  0b00..STS1 never asserts
 *  0b01..STS1 asserts on rising edges of XBAR_OUT1
 *  0b10..STS1 asserts on falling edges of XBAR_OUT1
 *  0b11..STS1 asserts on rising and falling edges of XBAR_OUT1
 */
#define XBARA_CTRL0_EDGE1(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_EDGE1_SHIFT)) & XBARA_CTRL0_EDGE1_MASK)

#define XBARA_CTRL0_STS1_MASK                    (0x1000U)
#define XBARA_CTRL0_STS1_SHIFT                   (12U)
/*! STS1 - Edge detection status for XBAR_OUT1
 *  0b0..Active edge not yet detected on XBAR_OUT1
 *  0b1..Active edge detected on XBAR_OUT1
 */
#define XBARA_CTRL0_STS1(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL0_STS1_SHIFT)) & XBARA_CTRL0_STS1_MASK)
/*! @} */

/*! @name CTRL1 - Crossbar A Control Register 1 */
/*! @{ */

#define XBARA_CTRL1_DEN2_MASK                    (0x1U)
#define XBARA_CTRL1_DEN2_SHIFT                   (0U)
/*! DEN2 - DMA Enable for XBAR_OUT2
 *  0b0..DMA disabled
 *  0b1..DMA enabled
 */
#define XBARA_CTRL1_DEN2(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_DEN2_SHIFT)) & XBARA_CTRL1_DEN2_MASK)

#define XBARA_CTRL1_IEN2_MASK                    (0x2U)
#define XBARA_CTRL1_IEN2_SHIFT                   (1U)
/*! IEN2 - Interrupt Enable for XBAR_OUT2
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define XBARA_CTRL1_IEN2(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_IEN2_SHIFT)) & XBARA_CTRL1_IEN2_MASK)

#define XBARA_CTRL1_EDGE2_MASK                   (0xCU)
#define XBARA_CTRL1_EDGE2_SHIFT                  (2U)
/*! EDGE2 - Active edge for edge detection on XBAR_OUT2
 *  0b00..STS2 never asserts
 *  0b01..STS2 asserts on rising edges of XBAR_OUT2
 *  0b10..STS2 asserts on falling edges of XBAR_OUT2
 *  0b11..STS2 asserts on rising and falling edges of XBAR_OUT2
 */
#define XBARA_CTRL1_EDGE2(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_EDGE2_SHIFT)) & XBARA_CTRL1_EDGE2_MASK)

#define XBARA_CTRL1_STS2_MASK                    (0x10U)
#define XBARA_CTRL1_STS2_SHIFT                   (4U)
/*! STS2 - Edge detection status for XBAR_OUT2
 *  0b0..Active edge not yet detected on XBAR_OUT2
 *  0b1..Active edge detected on XBAR_OUT2
 */
#define XBARA_CTRL1_STS2(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_STS2_SHIFT)) & XBARA_CTRL1_STS2_MASK)

#define XBARA_CTRL1_DEN3_MASK                    (0x100U)
#define XBARA_CTRL1_DEN3_SHIFT                   (8U)
/*! DEN3 - DMA Enable for XBAR_OUT3
 *  0b0..DMA disabled
 *  0b1..DMA enabled
 */
#define XBARA_CTRL1_DEN3(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_DEN3_SHIFT)) & XBARA_CTRL1_DEN3_MASK)

#define XBARA_CTRL1_IEN3_MASK                    (0x200U)
#define XBARA_CTRL1_IEN3_SHIFT                   (9U)
/*! IEN3 - Interrupt Enable for XBAR_OUT3
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define XBARA_CTRL1_IEN3(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_IEN3_SHIFT)) & XBARA_CTRL1_IEN3_MASK)

#define XBARA_CTRL1_EDGE3_MASK                   (0xC00U)
#define XBARA_CTRL1_EDGE3_SHIFT                  (10U)
/*! EDGE3 - Active edge for edge detection on XBAR_OUT3
 *  0b00..STS3 never asserts
 *  0b01..STS3 asserts on rising edges of XBAR_OUT3
 *  0b10..STS3 asserts on falling edges of XBAR_OUT3
 *  0b11..STS3 asserts on rising and falling edges of XBAR_OUT3
 */
#define XBARA_CTRL1_EDGE3(x)                     (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_EDGE3_SHIFT)) & XBARA_CTRL1_EDGE3_MASK)

#define XBARA_CTRL1_STS3_MASK                    (0x1000U)
#define XBARA_CTRL1_STS3_SHIFT                   (12U)
/*! STS3 - Edge detection status for XBAR_OUT3
 *  0b0..Active edge not yet detected on XBAR_OUT3
 *  0b1..Active edge detected on XBAR_OUT3
 */
#define XBARA_CTRL1_STS3(x)                      (((uint16_t)(((uint16_t)(x)) << XBARA_CTRL1_STS3_SHIFT)) & XBARA_CTRL1_STS3_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group XBARA_Register_Masks */


/*!
 * @}
 */ /* end of group XBARA_Peripheral_Access_Layer */


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


#endif  /* PERI_XBARA_H_ */

