/**
 * \file
 *
 * \brief Instance description for MTB
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_MTB_INSTANCE_
#define _SAMC21_MTB_INSTANCE_

/* ========== Register definition for MTB peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MTB_POSITION           (0x41008000) /**< \brief (MTB) MTB Position */
#define REG_MTB_MASTER             (0x41008004) /**< \brief (MTB) MTB Master */
#define REG_MTB_FLOW               (0x41008008) /**< \brief (MTB) MTB Flow */
#define REG_MTB_BASE               (0x4100800C) /**< \brief (MTB) MTB Base */
#define REG_MTB_ITCTRL             (0x41008F00) /**< \brief (MTB) MTB Integration Mode Control */
#define REG_MTB_CLAIMSET           (0x41008FA0) /**< \brief (MTB) MTB Claim Set */
#define REG_MTB_CLAIMCLR           (0x41008FA4) /**< \brief (MTB) MTB Claim Clear */
#define REG_MTB_LOCKACCESS         (0x41008FB0) /**< \brief (MTB) MTB Lock Access */
#define REG_MTB_LOCKSTATUS         (0x41008FB4) /**< \brief (MTB) MTB Lock Status */
#define REG_MTB_AUTHSTATUS         (0x41008FB8) /**< \brief (MTB) MTB Authentication Status */
#define REG_MTB_DEVARCH            (0x41008FBC) /**< \brief (MTB) MTB Device Architecture */
#define REG_MTB_DEVID              (0x41008FC8) /**< \brief (MTB) MTB Device Configuration */
#define REG_MTB_DEVTYPE            (0x41008FCC) /**< \brief (MTB) MTB Device Type */
#define REG_MTB_PID4               (0x41008FD0) /**< \brief (MTB) Peripheral Identification 4 */
#define REG_MTB_PID5               (0x41008FD4) /**< \brief (MTB) Peripheral Identification 5 */
#define REG_MTB_PID6               (0x41008FD8) /**< \brief (MTB) Peripheral Identification 6 */
#define REG_MTB_PID7               (0x41008FDC) /**< \brief (MTB) Peripheral Identification 7 */
#define REG_MTB_PID0               (0x41008FE0) /**< \brief (MTB) Peripheral Identification 0 */
#define REG_MTB_PID1               (0x41008FE4) /**< \brief (MTB) Peripheral Identification 1 */
#define REG_MTB_PID2               (0x41008FE8) /**< \brief (MTB) Peripheral Identification 2 */
#define REG_MTB_PID3               (0x41008FEC) /**< \brief (MTB) Peripheral Identification 3 */
#define REG_MTB_CID0               (0x41008FF0) /**< \brief (MTB) Component Identification 0 */
#define REG_MTB_CID1               (0x41008FF4) /**< \brief (MTB) Component Identification 1 */
#define REG_MTB_CID2               (0x41008FF8) /**< \brief (MTB) Component Identification 2 */
#define REG_MTB_CID3               (0x41008FFC) /**< \brief (MTB) Component Identification 3 */
#else
#define REG_MTB_POSITION           (*(RwReg  *)0x41008000UL) /**< \brief (MTB) MTB Position */
#define REG_MTB_MASTER             (*(RwReg  *)0x41008004UL) /**< \brief (MTB) MTB Master */
#define REG_MTB_FLOW               (*(RwReg  *)0x41008008UL) /**< \brief (MTB) MTB Flow */
#define REG_MTB_BASE               (*(RoReg  *)0x4100800CUL) /**< \brief (MTB) MTB Base */
#define REG_MTB_ITCTRL             (*(RwReg  *)0x41008F00UL) /**< \brief (MTB) MTB Integration Mode Control */
#define REG_MTB_CLAIMSET           (*(RwReg  *)0x41008FA0UL) /**< \brief (MTB) MTB Claim Set */
#define REG_MTB_CLAIMCLR           (*(RwReg  *)0x41008FA4UL) /**< \brief (MTB) MTB Claim Clear */
#define REG_MTB_LOCKACCESS         (*(RwReg  *)0x41008FB0UL) /**< \brief (MTB) MTB Lock Access */
#define REG_MTB_LOCKSTATUS         (*(RoReg  *)0x41008FB4UL) /**< \brief (MTB) MTB Lock Status */
#define REG_MTB_AUTHSTATUS         (*(RoReg  *)0x41008FB8UL) /**< \brief (MTB) MTB Authentication Status */
#define REG_MTB_DEVARCH            (*(RoReg  *)0x41008FBCUL) /**< \brief (MTB) MTB Device Architecture */
#define REG_MTB_DEVID              (*(RoReg  *)0x41008FC8UL) /**< \brief (MTB) MTB Device Configuration */
#define REG_MTB_DEVTYPE            (*(RoReg  *)0x41008FCCUL) /**< \brief (MTB) MTB Device Type */
#define REG_MTB_PID4               (*(RoReg  *)0x41008FD0UL) /**< \brief (MTB) Peripheral Identification 4 */
#define REG_MTB_PID5               (*(RoReg  *)0x41008FD4UL) /**< \brief (MTB) Peripheral Identification 5 */
#define REG_MTB_PID6               (*(RoReg  *)0x41008FD8UL) /**< \brief (MTB) Peripheral Identification 6 */
#define REG_MTB_PID7               (*(RoReg  *)0x41008FDCUL) /**< \brief (MTB) Peripheral Identification 7 */
#define REG_MTB_PID0               (*(RoReg  *)0x41008FE0UL) /**< \brief (MTB) Peripheral Identification 0 */
#define REG_MTB_PID1               (*(RoReg  *)0x41008FE4UL) /**< \brief (MTB) Peripheral Identification 1 */
#define REG_MTB_PID2               (*(RoReg  *)0x41008FE8UL) /**< \brief (MTB) Peripheral Identification 2 */
#define REG_MTB_PID3               (*(RoReg  *)0x41008FECUL) /**< \brief (MTB) Peripheral Identification 3 */
#define REG_MTB_CID0               (*(RoReg  *)0x41008FF0UL) /**< \brief (MTB) Component Identification 0 */
#define REG_MTB_CID1               (*(RoReg  *)0x41008FF4UL) /**< \brief (MTB) Component Identification 1 */
#define REG_MTB_CID2               (*(RoReg  *)0x41008FF8UL) /**< \brief (MTB) Component Identification 2 */
#define REG_MTB_CID3               (*(RoReg  *)0x41008FFCUL) /**< \brief (MTB) Component Identification 3 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */


#endif /* _SAMC21_MTB_INSTANCE_ */
