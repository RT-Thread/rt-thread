
/**
 *  @Component:   PMIC
 *
 *  @Filename:    hw_tps65217.h
 *
 ============================================================================ */
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


#ifndef __TPS65217_H__
#define __TPS65217_H__


/* Address of TPS65217(pmic) over I2C0 */
#define  PMIC_TPS65217_I2C_SLAVE_ADDR   (0x24)


/* Registers */
#define CHIPID                          0x00
#define POWER_PATH                      0x01
#define INTERRUPT                       0x02
#define CHGCONFIG0                      0x03
#define CHGCONFIG1                      0x04
#define CHGCONFIG2                      0x05
#define CHGCONFIG3                      0x06
#define WLEDCTRL1                       0x07
#define WLEDCTRL2                       0x08
#define MUXCTRL                         0x09
#define STATUS                          0x0A
#define PASSWORD                        0x0B
#define PGOOD                           0x0C
#define DEFPG                           0x0D
#define DEFDCDC1                        0x0E
#define DEFDCDC2                        0x0F
#define DEFDCDC3                        0x10
#define DEFSLEW                         0x11
#define DEFLDO1                         0x12
#define DEFLDO2                         0x13
#define DEFLS1                          0x14
#define DEFLS2                          0x15
#define ENABLE                          0x16
#define DEFUVLO                         0x18
#define SEQ1                            0x19
#define SEQ2                            0x1A
#define SEQ3                            0x1B
#define SEQ4                            0x1C
#define SEQ5                            0x1D
#define SEQ6                            0x1E

#define PROT_LEVEL_NONE                 0x00
#define PROT_LEVEL_1                    0x01
#define PROT_LEVEL_2                    0x02

#define PASSWORD_LOCK_FOR_WRITE         0x00
#define PASSWORD_UNLOCK                 0x7D

#define DCDC_GO                         0x80

#define MASK_ALL_BITS                   0xFF

#define USB_INPUT_CUR_LIMIT_MASK        0x03
#define USB_INPUT_CUR_LIMIT_100MA       0x00
#define USB_INPUT_CUR_LIMIT_500MA       0x01
#define USB_INPUT_CUR_LIMIT_1300MA      0x02
#define USB_INPUT_CUR_LIMIT_1800MA      0x03

#define DCDC_VOLT_SEL_1275MV            0x0F
#define DCDC_VOLT_SEL_1200MV           (0x0C)
#define DCDC_VOLT_SEL_1100MV           (0x08)
#define DCDC_VOLT_SEL_0950MV           (0x02)

#define LDO_MASK                        0x1F
#define LDO_VOLTAGE_OUT_3_3             0x1F

#define PWR_SRC_USB_BITMASK             0x4
#define PWR_SRC_AC_BITMASK              0x8

#endif

