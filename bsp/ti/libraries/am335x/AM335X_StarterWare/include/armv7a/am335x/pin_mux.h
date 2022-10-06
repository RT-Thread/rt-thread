/**
 * \file   pin_mux.h
 *
 * \brief  This file contains macro definitions related to Pin Multiplexing.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "hw_control_AM335x.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

/****************************************************************************
**   Macros for every GPIO Pin defining the offset addresses of the Pad
**   Control Registers in the Control Module.                    
****************************************************************************/

/* Macros of Pins in GPIO0 instance. */
#define GPIO_0_0                 (0x0948)
#define GPIO_0_1                 (0x094c)
#define GPIO_0_2                 (0x0950)
#define GPIO_0_3                 (0x0954)
#define GPIO_0_4                 (0x0958)
#define GPIO_0_5                 (0x095c)
#define GPIO_0_6                 (0x0960)
#define GPIO_0_7                 (0x0964)
#define GPIO_0_8                 (0x08d0)
#define GPIO_0_9                 (0x08d4)
#define GPIO_0_10                (0x08d8)
#define GPIO_0_11                (0x08dc)
#define GPIO_0_12                (0x0978)
#define GPIO_0_13                (0x097c)
#define GPIO_0_14                (0x0980)
#define GPIO_0_15                (0x0984)
#define GPIO_0_16                (0x091c)
#define GPIO_0_17                (0x0920)
#define GPIO_0_18                (0x0a1c)
#define GPIO_0_19                (0x09b0)
#define GPIO_0_20                (0x09b4)
#define GPIO_0_21                (0x0924)
#define GPIO_0_22                (0x0820)
#define GPIO_0_23                (0x0824)
#define GPIO_0_26                (0x0828)
#define GPIO_0_27                (0x082c)
#define GPIO_0_28                (0x0928)
#define GPIO_0_29                (0x0944)
#define GPIO_0_30                (0x0870)
#define GPIO_0_31                (0x0874)

/* Macros of Pins in GPIO1 instance. */
#define GPIO_1_0                 (0x0800)
#define GPIO_1_1                 (0x0804)
#define GPIO_1_2                 (0x0808)
#define GPIO_1_3                 (0x080c)
#define GPIO_1_4                 (0x0810)
#define GPIO_1_5                 (0x0814)
#define GPIO_1_6                 (0x0818)
#define GPIO_1_7                 (0x081c)
#define GPIO_1_8                 (0x0968)
#define GPIO_1_9                 (0x096c)
#define GPIO_1_10                (0x0970)
#define GPIO_1_11                (0x0974)
#define GPIO_1_12                (0x0830)
#define GPIO_1_13                (0x0834)
#define GPIO_1_14                (0x0838)
#define GPIO_1_15                (0x083c)
#define GPIO_1_16                (0x0840)
#define GPIO_1_17                (0x0844)
#define GPIO_1_18                (0x0848)
#define GPIO_1_19                (0x084c)
#define GPIO_1_20                (0x0850)
#define GPIO_1_21                (0x0854)
#define GPIO_1_22                (0x0858)
#define GPIO_1_23                (0x085c)
#define GPIO_1_24                (0x0860)
#define GPIO_1_25                (0x0864)
#define GPIO_1_26                (0x0868)
#define GPIO_1_27                (0x086c)
#define GPIO_1_28                (0x0878)
#define GPIO_1_29                (0x087c)
#define GPIO_1_30                (0x0880)
#define GPIO_1_31                (0x0884)

/* Macros of Pins in GPIO2 instance. */
#define GPIO_2_0                 (0x0888)
#define GPIO_2_1                 (0x088c)
#define GPIO_2_2                 (0x0890)
#define GPIO_2_3                 (0x0894)
#define GPIO_2_4                 (0x0898)
#define GPIO_2_5                 (0x089c)
#define GPIO_2_6                 (0x08a0)
#define GPIO_2_7                 (0x08a4)
#define GPIO_2_8                 (0x08a8)
#define GPIO_2_9                 (0x08ac)
#define GPIO_2_10                (0x08b0)
#define GPIO_2_11                (0x08b4)
#define GPIO_2_12                (0x08b8)
#define GPIO_2_13                (0x08bc)
#define GPIO_2_14                (0x08c0)
#define GPIO_2_15                (0x08c4)
#define GPIO_2_16                (0x08c8)
#define GPIO_2_17                (0x08cc)
#define GPIO_2_18                (0x0934)
#define GPIO_2_19                (0x0938)
#define GPIO_2_20                (0x093c)
#define GPIO_2_21                (0x0940)
#define GPIO_2_22                (0x08e0)
#define GPIO_2_23                (0x08e4)
#define GPIO_2_24                (0x08e8)
#define GPIO_2_25                (0x08ec)
#define GPIO_2_26                (0x08f0)
#define GPIO_2_27                (0x08f4)
#define GPIO_2_28                (0x08f8)
#define GPIO_2_29                (0x08fc)
#define GPIO_2_30                (0x0900)
#define GPIO_2_31                (0x0904)

/* Macros of Pins in GPIO3 instance. */
#define GPIO_3_0                 (0x0908)
#define GPIO_3_1                 (0x090c)
#define GPIO_3_2                 (0x0910)
#define GPIO_3_3                 (0x0914)
#define GPIO_3_4                 (0x0918)
#define GPIO_3_5                 (0x0988)
#define GPIO_3_6                 (0x098c)
#define GPIO_3_7                 (0x09e4)
#define GPIO_3_8                 (0x09e8)
#define GPIO_3_9                 (0x092c)
#define GPIO_3_10                (0x0930)
#define GPIO_3_13                (0x0a34)
#define GPIO_3_14                (0x0990)
#define GPIO_3_15                (0x0994)
#define GPIO_3_16                (0x0998)
#define GPIO_3_17                (0x099c)
#define GPIO_3_18                (0x09a0)
#define GPIO_3_19                (0x09a4)
#define GPIO_3_20                (0x09a8)
#define GPIO_3_21                (0x09ac)

/*****************************************************************************
** Macros that define the various combinations of Pad Control Register value.
*****************************************************************************/
/*
** These macros should be read in this pattern.\n
** PAD_SlewRate_RXEnDis_PUPDSel_PUPDEnDis(muxMode).\n
**
** SlewRate -- This represents the selection of Slew Rate.\n
**             FS - Fast Slew Rate.\n
**             SL - Slow Slew Rate.\n
**
** RXEnDis -- This represents whether Reception feature for the Pad is
**            enabled or disabled.\n
**            RXE - Reception feature is Enabled.\n
**            RXD - Reception feature is Disabled.\n
**
** PUPDSel -- This represents whether Pad Pullup or Pad Pulldown feature is
**            selected.\n
**            PU - Pullup feature is selected.\n
**            PD - Pulldown feature is selected.\n
**            NA - Not Applicable, since Pad Pullup/Pulldown feature is
**                 disabled.\n
**
** PUPDEnDis -- This represents whether the Pad Pullup/Pulldown feature is
**              enabled. The selection of the Pull type using 'PUPDSel'
**              is valid only when the Pad Pullup/Pulldown feature is
**              enabled.\n
**              PUPDE - Pad Pullup/Pulldown feature is Enabled.\n
**              PUPDD - Pad Pullup/Pulldown feature is Disabled.\n
**
** muxMode -- This represents the Pad functional signal mux value.\n
**            This can take one of the following values:\n
**            (0 <= muxMode <= 7).\n
*/

/* Fast Slew Rate - Receiver Disabled - NA - PU/PD feature Disabled. */
#define PAD_FS_RXD_NA_PUPDD(n)       (CONTROL_CONF_PULLUDDISABLE | \
                                      CONTROL_CONF_MUXMODE(n))

/* Slow Slew Rate - Receiver Disabled - NA - PU/PD feature Disabled. */
#define PAD_SL_RXD_NA_PUPDD(n)       (CONTROL_CONF_SLOWSLEW |  \
                                      CONTROL_CONF_PULLUDDISABLE | \
                                      CONTROL_CONF_MUXMODE(n))

/* Fast Slew Rate - Receiver Enabled - NA - PU/PD feature Disabled. */
#define PAD_FS_RXE_NA_PUPDD(n)       (CONTROL_CONF_RXACTIVE | \
                                      CONTROL_CONF_PULLUDDISABLE | \
                                      CONTROL_CONF_MUXMODE(n))
                                      
/* Slow Slew Rate - Receiver Enabled - NA - PU/PD feature Disabled. */
#define PAD_SL_RXE_NA_PUPDD(n)       (CONTROL_CONF_SLOWSLEW | \
                                      CONTROL_CONF_RXACTIVE | \
                                      CONTROL_CONF_PULLUDDISABLE | \
                                      CONTROL_CONF_MUXMODE(n))

/* Fast Slew Rate - Receiver Disabled - Pulldown - PU/PD feature Enabled. */
#define PAD_FS_RXD_PD_PUPDE(n)       (CONTROL_CONF_MUXMODE(n))

/* Slow Slew Rate - Receiver Disabled - Pulldown - PU/PD feature Enabled. */
#define PAD_SL_RXD_PD_PUPDE(n)       (CONTROL_CONF_SLOWSLEW | \
                                      CONTROL_CONF_MUXMODE(n))

/* Fast Slew Rate - Receiver Enabled - Pulldown - PU/PD feature Enabled. */
#define PAD_FS_RXE_PD_PUPDE(n)       (CONTROL_CONF_RXACTIVE | \
                                      CONTROL_CONF_MUXMODE(n))

/* Slow Slew Rate - Receiver Enabled - Pulldown - PU/PD feature Enabled. */
#define PAD_SL_RXE_PD_PUPDE(n)       (CONTROL_CONF_SLOWSLEW | \
                                      CONTROL_CONF_RXACTIVE | \
                                      CONTROL_CONF_MUXMODE(n))

/* Fast Slew Rate - Receiver Disabled - Pullup - PU/PD feature Enabled. */
#define PAD_FS_RXD_PU_PUPDE(n)       (CONTROL_CONF_PULLUPSEL | \
                                      CONTROL_CONF_MUXMODE(n))

/* Slow Slew Rate - Receiver Disabled - Pullup - PU/PD feature Enabled. */
#define PAD_SL_RXD_PU_PUPDE(n)       (CONTROL_CONF_SLOWSLEW | \
                                      CONTROL_CONF_PULLUPSEL | \
                                      CONTROL_CONF_MUXMODE(n))

/* Fast Slew Rate - Receiver Enabled - Pullup - PU/PD feature Enabled. */
#define PAD_FS_RXE_PU_PUPDE(n)       (CONTROL_CONF_RXACTIVE | \
                                      CONTROL_CONF_PULLUPSEL | \
                                      CONTROL_CONF_MUXMODE(n))

/* Slow Slew Rate - Receiver Enabled - Pullup - PU/PD feature Enabled. */
#define PAD_SL_RXE_PU_PUPDE(n)       (CONTROL_CONF_SLOWSLEW | \
                                      CONTROL_CONF_RXACTIVE | \
                                      CONTROL_CONF_PULLUPSEL | \
                                      CONTROL_CONF_MUXMODE(n))

/******************************************************************************
**   A Parameterized macro that receives the GPIO Instance Number, Pin Number
**   and the Pad Control Register value as parameters. The GPIO Instance
**   Number and the Pin Number will be used to obtain the offset address of
**   the respective Pad Control Register in the Contorl Module. The Pad 
**   Control Register offset and value is passed to another function
**   which does the necessary Pin Multiplexing.
******************************************************************************/

#define GPIO_PMUX_OFFADDR_VALUE(instance, pin, padConfValue)    \
 GpioPinMuxSetup(GPIO_##instance##_##pin, padConfValue)

#ifdef __cplusplus
}
#endif

#endif
