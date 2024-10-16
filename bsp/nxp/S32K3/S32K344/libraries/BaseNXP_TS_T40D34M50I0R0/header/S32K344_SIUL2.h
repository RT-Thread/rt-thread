/*
** ###################################################################
**     Processor:           S32K344
**     Reference manual:    S32K3xx RM Rev.3
**     Version:             rev. 1.9, 2021-10-27
**     Build:               b211026
**
**     Abstract:
**         Peripheral Access Layer for S32K344
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K344_SIUL2.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SIUL2
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_SIUL2_H_)  /* Check if memory map has not been already included */
#define S32K344_SIUL2_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SIUL2 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIUL2_Peripheral_Access_Layer SIUL2 Peripheral Access Layer
 * @{
 */

/** SIUL2 - Size of Registers Arrays */
#define SIUL2_IFMCR_COUNT                         32u
#define SIUL2_MSCR_COUNT                          220u
#define SIUL2_IMCR_COUNT                          379u
#define SIUL2_MPGPDO_COUNT                        14u

/** SIUL2 - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[4];
  __I  uint32_t MIDR1;                             /**< SIUL2 MCU ID Register #1, offset: 0x4 */
  __I  uint32_t MIDR2;                             /**< SIUL2 MCU ID Register #2, offset: 0x8 */
  uint8_t RESERVED_1[4];
  __IO uint32_t DISR0;                             /**< SIUL2 DMA/Interrupt Status Flag Register0, offset: 0x10 */
  uint8_t RESERVED_2[4];
  __IO uint32_t DIRER0;                            /**< SIUL2 DMA/Interrupt Request Enable Register0, offset: 0x18 */
  uint8_t RESERVED_3[4];
  __IO uint32_t DIRSR0;                            /**< SIUL2 DMA/Interrupt Request Select Register0, offset: 0x20 */
  uint8_t RESERVED_4[4];
  __IO uint32_t IREER0;                            /**< SIUL2 Interrupt Rising-Edge Event Enable Register 0, offset: 0x28 */
  uint8_t RESERVED_5[4];
  __IO uint32_t IFEER0;                            /**< SIUL2 Interrupt Falling-Edge Event Enable Register 0, offset: 0x30 */
  uint8_t RESERVED_6[4];
  __IO uint32_t IFER0;                             /**< SIUL2 Interrupt Filter Enable Register 0, offset: 0x38 */
  uint8_t RESERVED_7[4];
  __IO uint32_t IFMCR[SIUL2_IFMCR_COUNT];          /**< SIUL2 Interrupt Filter Maximum Counter Register, array offset: 0x40, array step: 0x4 */
  __IO uint32_t IFCPR;                             /**< SIUL2 Interrupt Filter Clock Prescaler Register, offset: 0xC0 */
  uint8_t RESERVED_8[316];
  __I  uint32_t MIDR3;                             /**< SIUL2 MCU ID Register #3, offset: 0x200 */
  __I  uint32_t MIDR4;                             /**< SIUL2 MCU ID Register #4, offset: 0x204 */
  uint8_t RESERVED_9[56];
  __IO uint32_t MSCR[SIUL2_MSCR_COUNT];            /**< SIUL2 Multiplexed Signal Configuration Register, array offset: 0x240, array step: 0x4 */
  uint8_t RESERVED_10[1168];
  __IO uint32_t IMCR[SIUL2_IMCR_COUNT];            /**< SIUL2 Input Multiplexed Signal Configuration Register, array offset: 0xA40, array step: 0x4 */
  uint8_t RESERVED_11[724];
  __IO uint8_t GPDO3;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1300 */
  __IO uint8_t GPDO2;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1301 */
  __IO uint8_t GPDO1;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1302 */
  __IO uint8_t GPDO0;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1303 */
  __IO uint8_t GPDO7;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1304 */
  __IO uint8_t GPDO6;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1305 */
  __IO uint8_t GPDO5;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1306 */
  __IO uint8_t GPDO4;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1307 */
  __IO uint8_t GPDO11;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1308 */
  __IO uint8_t GPDO10;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1309 */
  __IO uint8_t GPDO9;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x130A */
  __IO uint8_t GPDO8;                              /**< SIUL2 GPIO Pad Data Output Register, offset: 0x130B */
  __IO uint8_t GPDO15;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x130C */
  __IO uint8_t GPDO14;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x130D */
  __IO uint8_t GPDO13;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x130E */
  __IO uint8_t GPDO12;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x130F */
  __IO uint8_t GPDO19;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1310 */
  __IO uint8_t GPDO18;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1311 */
  __IO uint8_t GPDO17;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1312 */
  __IO uint8_t GPDO16;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1313 */
  __IO uint8_t GPDO23;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1314 */
  __IO uint8_t GPDO22;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1315 */
  __IO uint8_t GPDO21;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1316 */
  __IO uint8_t GPDO20;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1317 */
  __IO uint8_t GPDO27;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1318 */
  __IO uint8_t GPDO26;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1319 */
  __IO uint8_t GPDO25;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x131A */
  __IO uint8_t GPDO24;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x131B */
  __IO uint8_t GPDO31;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x131C */
  __IO uint8_t GPDO30;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x131D */
  __IO uint8_t GPDO29;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x131E */
  __IO uint8_t GPDO28;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x131F */
  __IO uint8_t GPDO35;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1320 */
  __IO uint8_t GPDO34;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1321 */
  __IO uint8_t GPDO33;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1322 */
  __IO uint8_t GPDO32;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1323 */
  uint8_t RESERVED_12[2];
  __IO uint8_t GPDO37;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1326 */
  __IO uint8_t GPDO36;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1327 */
  __IO uint8_t GPDO43;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1328 */
  __IO uint8_t GPDO42;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1329 */
  __IO uint8_t GPDO41;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x132A */
  __IO uint8_t GPDO40;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x132B */
  __IO uint8_t GPDO47;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x132C */
  __IO uint8_t GPDO46;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x132D */
  __IO uint8_t GPDO45;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x132E */
  __IO uint8_t GPDO44;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x132F */
  __IO uint8_t GPDO51;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1330 */
  __IO uint8_t GPDO50;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1331 */
  __IO uint8_t GPDO49;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1332 */
  __IO uint8_t GPDO48;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1333 */
  __IO uint8_t GPDO55;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1334 */
  __IO uint8_t GPDO54;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1335 */
  __IO uint8_t GPDO53;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1336 */
  __IO uint8_t GPDO52;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1337 */
  __IO uint8_t GPDO59;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1338 */
  __IO uint8_t GPDO58;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1339 */
  __IO uint8_t GPDO57;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x133A */
  __IO uint8_t GPDO56;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x133B */
  __IO uint8_t GPDO63;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x133C */
  __IO uint8_t GPDO62;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x133D */
  __IO uint8_t GPDO61;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x133E */
  __IO uint8_t GPDO60;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x133F */
  __IO uint8_t GPDO67;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1340 */
  __IO uint8_t GPDO66;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1341 */
  __IO uint8_t GPDO65;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1342 */
  __IO uint8_t GPDO64;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1343 */
  __IO uint8_t GPDO71;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1344 */
  __IO uint8_t GPDO70;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1345 */
  __IO uint8_t GPDO69;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1346 */
  __IO uint8_t GPDO68;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1347 */
  __IO uint8_t GPDO75;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1348 */
  __IO uint8_t GPDO74;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1349 */
  __IO uint8_t GPDO73;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x134A */
  __IO uint8_t GPDO72;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x134B */
  __IO uint8_t GPDO79;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x134C */
  __IO uint8_t GPDO78;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x134D */
  __IO uint8_t GPDO77;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x134E */
  __IO uint8_t GPDO76;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x134F */
  __IO uint8_t GPDO83;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1350 */
  __IO uint8_t GPDO82;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1351 */
  __IO uint8_t GPDO81;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1352 */
  __IO uint8_t GPDO80;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1353 */
  __IO uint8_t GPDO87;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1354 */
  __IO uint8_t GPDO86;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1355 */
  __IO uint8_t GPDO85;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1356 */
  __IO uint8_t GPDO84;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1357 */
  __IO uint8_t GPDO91;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1358 */
  __IO uint8_t GPDO90;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1359 */
  __IO uint8_t GPDO89;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x135A */
  __IO uint8_t GPDO88;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x135B */
  __IO uint8_t GPDO95;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x135C */
  __IO uint8_t GPDO94;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x135D */
  __IO uint8_t GPDO93;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x135E */
  __IO uint8_t GPDO92;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x135F */
  __IO uint8_t GPDO99;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1360 */
  __IO uint8_t GPDO98;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1361 */
  __IO uint8_t GPDO97;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1362 */
  __IO uint8_t GPDO96;                             /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1363 */
  __IO uint8_t GPDO103;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1364 */
  __IO uint8_t GPDO102;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1365 */
  __IO uint8_t GPDO101;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1366 */
  __IO uint8_t GPDO100;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1367 */
  __IO uint8_t GPDO107;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1368 */
  __IO uint8_t GPDO106;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1369 */
  __IO uint8_t GPDO105;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x136A */
  __IO uint8_t GPDO104;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x136B */
  __IO uint8_t GPDO111;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x136C */
  __IO uint8_t GPDO110;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x136D */
  __IO uint8_t GPDO109;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x136E */
  __IO uint8_t GPDO108;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x136F */
  __IO uint8_t GPDO115;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1370 */
  __IO uint8_t GPDO114;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1371 */
  __IO uint8_t GPDO113;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1372 */
  __IO uint8_t GPDO112;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1373 */
  __IO uint8_t GPDO119;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1374 */
  __IO uint8_t GPDO118;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1375 */
  __IO uint8_t GPDO117;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1376 */
  __IO uint8_t GPDO116;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1377 */
  __IO uint8_t GPDO123;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1378 */
  __IO uint8_t GPDO122;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1379 */
  __IO uint8_t GPDO121;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x137A */
  __IO uint8_t GPDO120;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x137B */
  __IO uint8_t GPDO127;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x137C */
  __IO uint8_t GPDO126;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x137D */
  __IO uint8_t GPDO125;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x137E */
  __IO uint8_t GPDO124;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x137F */
  __IO uint8_t GPDO131;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1380 */
  __IO uint8_t GPDO130;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1381 */
  __IO uint8_t GPDO129;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1382 */
  __IO uint8_t GPDO128;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1383 */
  __IO uint8_t GPDO135;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1384 */
  __IO uint8_t GPDO134;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1385 */
  __IO uint8_t GPDO133;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1386 */
  __IO uint8_t GPDO132;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1387 */
  __IO uint8_t GPDO139;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1388 */
  __IO uint8_t GPDO138;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1389 */
  __IO uint8_t GPDO137;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x138A */
  __IO uint8_t GPDO136;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x138B */
  __IO uint8_t GPDO143;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x138C */
  __IO uint8_t GPDO142;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x138D */
  __IO uint8_t GPDO141;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x138E */
  __IO uint8_t GPDO140;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x138F */
  __IO uint8_t GPDO147;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1390 */
  __IO uint8_t GPDO146;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1391 */
  __IO uint8_t GPDO145;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1392 */
  __IO uint8_t GPDO144;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1393 */
  __IO uint8_t GPDO151;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1394 */
  __IO uint8_t GPDO150;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1395 */
  __IO uint8_t GPDO149;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1396 */
  __IO uint8_t GPDO148;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1397 */
  __IO uint8_t GPDO155;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1398 */
  __IO uint8_t GPDO154;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x1399 */
  __IO uint8_t GPDO153;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x139A */
  __IO uint8_t GPDO152;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x139B */
  __IO uint8_t GPDO159;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x139C */
  __IO uint8_t GPDO158;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x139D */
  __IO uint8_t GPDO157;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x139E */
  __IO uint8_t GPDO156;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x139F */
  __IO uint8_t GPDO163;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A0 */
  __IO uint8_t GPDO162;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A1 */
  __IO uint8_t GPDO161;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A2 */
  __IO uint8_t GPDO160;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A3 */
  __IO uint8_t GPDO167;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A4 */
  __IO uint8_t GPDO166;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A5 */
  __IO uint8_t GPDO165;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A6 */
  __IO uint8_t GPDO164;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A7 */
  __IO uint8_t GPDO171;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A8 */
  __IO uint8_t GPDO170;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13A9 */
  __IO uint8_t GPDO169;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13AA */
  __IO uint8_t GPDO168;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13AB */
  __IO uint8_t GPDO175;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13AC */
  __IO uint8_t GPDO174;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13AD */
  __IO uint8_t GPDO173;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13AE */
  __IO uint8_t GPDO172;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13AF */
  __IO uint8_t GPDO179;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B0 */
  __IO uint8_t GPDO178;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B1 */
  __IO uint8_t GPDO177;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B2 */
  __IO uint8_t GPDO176;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B3 */
  __IO uint8_t GPDO183;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B4 */
  __IO uint8_t GPDO182;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B5 */
  __IO uint8_t GPDO181;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B6 */
  __IO uint8_t GPDO180;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B7 */
  __IO uint8_t GPDO187;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B8 */
  __IO uint8_t GPDO186;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13B9 */
  __IO uint8_t GPDO185;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13BA */
  __IO uint8_t GPDO184;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13BB */
  __IO uint8_t GPDO191;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13BC */
  __IO uint8_t GPDO190;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13BD */
  __IO uint8_t GPDO189;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13BE */
  __IO uint8_t GPDO188;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13BF */
  __IO uint8_t GPDO195;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C0 */
  __IO uint8_t GPDO194;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C1 */
  __IO uint8_t GPDO193;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C2 */
  __IO uint8_t GPDO192;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C3 */
  __IO uint8_t GPDO199;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C4 */
  __IO uint8_t GPDO198;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C5 */
  __IO uint8_t GPDO197;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C6 */
  __IO uint8_t GPDO196;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C7 */
  __IO uint8_t GPDO203;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C8 */
  __IO uint8_t GPDO202;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13C9 */
  __IO uint8_t GPDO201;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13CA */
  __IO uint8_t GPDO200;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13CB */
  __IO uint8_t GPDO207;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13CC */
  __IO uint8_t GPDO206;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13CD */
  __IO uint8_t GPDO205;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13CE */
  __IO uint8_t GPDO204;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13CF */
  __IO uint8_t GPDO211;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D0 */
  __IO uint8_t GPDO210;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D1 */
  __IO uint8_t GPDO209;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D2 */
  __IO uint8_t GPDO208;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D3 */
  __IO uint8_t GPDO215;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D4 */
  __IO uint8_t GPDO214;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D5 */
  __IO uint8_t GPDO213;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D6 */
  __IO uint8_t GPDO212;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D7 */
  __IO uint8_t GPDO219;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D8 */
  __IO uint8_t GPDO218;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13D9 */
  __IO uint8_t GPDO217;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13DA */
  __IO uint8_t GPDO216;                            /**< SIUL2 GPIO Pad Data Output Register, offset: 0x13DB */
  uint8_t RESERVED_13[292];
  __I  uint8_t GPDI3;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1500 */
  __I  uint8_t GPDI2;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1501 */
  __I  uint8_t GPDI1;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1502 */
  __I  uint8_t GPDI0;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1503 */
  __I  uint8_t GPDI7;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1504 */
  __I  uint8_t GPDI6;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1505 */
  __I  uint8_t GPDI5;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1506 */
  __I  uint8_t GPDI4;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1507 */
  __I  uint8_t GPDI11;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1508 */
  __I  uint8_t GPDI10;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1509 */
  __I  uint8_t GPDI9;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x150A */
  __I  uint8_t GPDI8;                              /**< SIUL2 GPIO Pad Data Input Register, offset: 0x150B */
  __I  uint8_t GPDI15;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x150C */
  __I  uint8_t GPDI14;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x150D */
  __I  uint8_t GPDI13;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x150E */
  __I  uint8_t GPDI12;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x150F */
  __I  uint8_t GPDI19;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1510 */
  __I  uint8_t GPDI18;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1511 */
  __I  uint8_t GPDI17;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1512 */
  __I  uint8_t GPDI16;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1513 */
  __I  uint8_t GPDI23;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1514 */
  __I  uint8_t GPDI22;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1515 */
  __I  uint8_t GPDI21;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1516 */
  __I  uint8_t GPDI20;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1517 */
  __I  uint8_t GPDI27;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1518 */
  __I  uint8_t GPDI26;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1519 */
  __I  uint8_t GPDI25;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x151A */
  __I  uint8_t GPDI24;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x151B */
  __I  uint8_t GPDI31;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x151C */
  __I  uint8_t GPDI30;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x151D */
  __I  uint8_t GPDI29;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x151E */
  __I  uint8_t GPDI28;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x151F */
  __I  uint8_t GPDI35;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1520 */
  __I  uint8_t GPDI34;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1521 */
  __I  uint8_t GPDI33;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1522 */
  __I  uint8_t GPDI32;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1523 */
  uint8_t RESERVED_14[2];
  __I  uint8_t GPDI37;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1526 */
  __I  uint8_t GPDI36;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1527 */
  __I  uint8_t GPDI43;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1528 */
  __I  uint8_t GPDI42;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1529 */
  __I  uint8_t GPDI41;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x152A */
  __I  uint8_t GPDI40;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x152B */
  __I  uint8_t GPDI47;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x152C */
  __I  uint8_t GPDI46;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x152D */
  __I  uint8_t GPDI45;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x152E */
  __I  uint8_t GPDI44;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x152F */
  __I  uint8_t GPDI51;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1530 */
  __I  uint8_t GPDI50;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1531 */
  __I  uint8_t GPDI49;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1532 */
  __I  uint8_t GPDI48;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1533 */
  __I  uint8_t GPDI55;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1534 */
  __I  uint8_t GPDI54;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1535 */
  __I  uint8_t GPDI53;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1536 */
  __I  uint8_t GPDI52;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1537 */
  __I  uint8_t GPDI59;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1538 */
  __I  uint8_t GPDI58;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1539 */
  __I  uint8_t GPDI57;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x153A */
  __I  uint8_t GPDI56;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x153B */
  __I  uint8_t GPDI63;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x153C */
  __I  uint8_t GPDI62;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x153D */
  __I  uint8_t GPDI61;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x153E */
  __I  uint8_t GPDI60;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x153F */
  __I  uint8_t GPDI67;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1540 */
  __I  uint8_t GPDI66;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1541 */
  __I  uint8_t GPDI65;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1542 */
  __I  uint8_t GPDI64;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1543 */
  __I  uint8_t GPDI71;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1544 */
  __I  uint8_t GPDI70;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1545 */
  __I  uint8_t GPDI69;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1546 */
  __I  uint8_t GPDI68;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1547 */
  __I  uint8_t GPDI75;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1548 */
  __I  uint8_t GPDI74;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1549 */
  __I  uint8_t GPDI73;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x154A */
  __I  uint8_t GPDI72;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x154B */
  __I  uint8_t GPDI79;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x154C */
  __I  uint8_t GPDI78;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x154D */
  __I  uint8_t GPDI77;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x154E */
  __I  uint8_t GPDI76;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x154F */
  __I  uint8_t GPDI83;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1550 */
  __I  uint8_t GPDI82;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1551 */
  __I  uint8_t GPDI81;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1552 */
  __I  uint8_t GPDI80;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1553 */
  __I  uint8_t GPDI87;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1554 */
  __I  uint8_t GPDI86;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1555 */
  __I  uint8_t GPDI85;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1556 */
  __I  uint8_t GPDI84;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1557 */
  __I  uint8_t GPDI91;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1558 */
  __I  uint8_t GPDI90;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1559 */
  __I  uint8_t GPDI89;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x155A */
  __I  uint8_t GPDI88;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x155B */
  __I  uint8_t GPDI95;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x155C */
  __I  uint8_t GPDI94;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x155D */
  __I  uint8_t GPDI93;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x155E */
  __I  uint8_t GPDI92;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x155F */
  __I  uint8_t GPDI99;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1560 */
  __I  uint8_t GPDI98;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1561 */
  __I  uint8_t GPDI97;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1562 */
  __I  uint8_t GPDI96;                             /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1563 */
  __I  uint8_t GPDI103;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1564 */
  __I  uint8_t GPDI102;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1565 */
  __I  uint8_t GPDI101;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1566 */
  __I  uint8_t GPDI100;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1567 */
  __I  uint8_t GPDI107;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1568 */
  __I  uint8_t GPDI106;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1569 */
  __I  uint8_t GPDI105;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x156A */
  __I  uint8_t GPDI104;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x156B */
  __I  uint8_t GPDI111;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x156C */
  __I  uint8_t GPDI110;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x156D */
  __I  uint8_t GPDI109;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x156E */
  __I  uint8_t GPDI108;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x156F */
  __I  uint8_t GPDI115;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1570 */
  __I  uint8_t GPDI114;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1571 */
  __I  uint8_t GPDI113;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1572 */
  __I  uint8_t GPDI112;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1573 */
  __I  uint8_t GPDI119;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1574 */
  __I  uint8_t GPDI118;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1575 */
  __I  uint8_t GPDI117;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1576 */
  __I  uint8_t GPDI116;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1577 */
  __I  uint8_t GPDI123;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1578 */
  __I  uint8_t GPDI122;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1579 */
  __I  uint8_t GPDI121;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x157A */
  __I  uint8_t GPDI120;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x157B */
  __I  uint8_t GPDI127;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x157C */
  __I  uint8_t GPDI126;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x157D */
  __I  uint8_t GPDI125;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x157E */
  __I  uint8_t GPDI124;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x157F */
  __I  uint8_t GPDI131;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1580 */
  __I  uint8_t GPDI130;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1581 */
  __I  uint8_t GPDI129;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1582 */
  __I  uint8_t GPDI128;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1583 */
  __I  uint8_t GPDI135;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1584 */
  __I  uint8_t GPDI134;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1585 */
  __I  uint8_t GPDI133;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1586 */
  __I  uint8_t GPDI132;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1587 */
  __I  uint8_t GPDI139;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1588 */
  __I  uint8_t GPDI138;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1589 */
  __I  uint8_t GPDI137;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x158A */
  __I  uint8_t GPDI136;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x158B */
  __I  uint8_t GPDI143;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x158C */
  __I  uint8_t GPDI142;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x158D */
  __I  uint8_t GPDI141;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x158E */
  __I  uint8_t GPDI140;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x158F */
  __I  uint8_t GPDI147;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1590 */
  __I  uint8_t GPDI146;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1591 */
  __I  uint8_t GPDI145;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1592 */
  __I  uint8_t GPDI144;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1593 */
  __I  uint8_t GPDI151;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1594 */
  __I  uint8_t GPDI150;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1595 */
  __I  uint8_t GPDI149;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1596 */
  __I  uint8_t GPDI148;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1597 */
  __I  uint8_t GPDI155;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1598 */
  __I  uint8_t GPDI154;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x1599 */
  __I  uint8_t GPDI153;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x159A */
  __I  uint8_t GPDI152;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x159B */
  __I  uint8_t GPDI159;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x159C */
  __I  uint8_t GPDI158;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x159D */
  __I  uint8_t GPDI157;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x159E */
  __I  uint8_t GPDI156;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x159F */
  __I  uint8_t GPDI163;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A0 */
  __I  uint8_t GPDI162;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A1 */
  __I  uint8_t GPDI161;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A2 */
  __I  uint8_t GPDI160;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A3 */
  __I  uint8_t GPDI167;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A4 */
  __I  uint8_t GPDI166;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A5 */
  __I  uint8_t GPDI165;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A6 */
  __I  uint8_t GPDI164;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A7 */
  __I  uint8_t GPDI171;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A8 */
  __I  uint8_t GPDI170;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15A9 */
  __I  uint8_t GPDI169;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15AA */
  __I  uint8_t GPDI168;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15AB */
  __I  uint8_t GPDI175;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15AC */
  __I  uint8_t GPDI174;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15AD */
  __I  uint8_t GPDI173;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15AE */
  __I  uint8_t GPDI172;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15AF */
  __I  uint8_t GPDI179;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B0 */
  __I  uint8_t GPDI178;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B1 */
  __I  uint8_t GPDI177;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B2 */
  __I  uint8_t GPDI176;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B3 */
  __I  uint8_t GPDI183;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B4 */
  __I  uint8_t GPDI182;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B5 */
  __I  uint8_t GPDI181;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B6 */
  __I  uint8_t GPDI180;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B7 */
  __I  uint8_t GPDI187;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B8 */
  __I  uint8_t GPDI186;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15B9 */
  __I  uint8_t GPDI185;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15BA */
  __I  uint8_t GPDI184;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15BB */
  __I  uint8_t GPDI191;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15BC */
  __I  uint8_t GPDI190;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15BD */
  __I  uint8_t GPDI189;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15BE */
  __I  uint8_t GPDI188;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15BF */
  __I  uint8_t GPDI195;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C0 */
  __I  uint8_t GPDI194;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C1 */
  __I  uint8_t GPDI193;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C2 */
  __I  uint8_t GPDI192;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C3 */
  __I  uint8_t GPDI199;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C4 */
  __I  uint8_t GPDI198;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C5 */
  __I  uint8_t GPDI197;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C6 */
  __I  uint8_t GPDI196;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C7 */
  __I  uint8_t GPDI203;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C8 */
  __I  uint8_t GPDI202;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15C9 */
  __I  uint8_t GPDI201;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15CA */
  __I  uint8_t GPDI200;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15CB */
  __I  uint8_t GPDI207;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15CC */
  __I  uint8_t GPDI206;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15CD */
  __I  uint8_t GPDI205;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15CE */
  __I  uint8_t GPDI204;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15CF */
  __I  uint8_t GPDI211;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D0 */
  __I  uint8_t GPDI210;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D1 */
  __I  uint8_t GPDI209;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D2 */
  __I  uint8_t GPDI208;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D3 */
  __I  uint8_t GPDI215;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D4 */
  __I  uint8_t GPDI214;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D5 */
  __I  uint8_t GPDI213;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D6 */
  __I  uint8_t GPDI212;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D7 */
  __I  uint8_t GPDI219;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D8 */
  __I  uint8_t GPDI218;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15D9 */
  __I  uint8_t GPDI217;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15DA */
  __I  uint8_t GPDI216;                            /**< SIUL2 GPIO Pad Data Input Register, offset: 0x15DB */
  uint8_t RESERVED_15[292];
  __IO uint16_t PGPDO1;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1700 */
  __IO uint16_t PGPDO0;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1702 */
  __IO uint16_t PGPDO3;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1704 */
  __IO uint16_t PGPDO2;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1706 */
  __IO uint16_t PGPDO5;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1708 */
  __IO uint16_t PGPDO4;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x170A */
  __IO uint16_t PGPDO7;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x170C */
  __IO uint16_t PGPDO6;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x170E */
  __IO uint16_t PGPDO9;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1710 */
  __IO uint16_t PGPDO8;                            /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1712 */
  __IO uint16_t PGPDO11;                           /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1714 */
  __IO uint16_t PGPDO10;                           /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1716 */
  __IO uint16_t PGPDO13;                           /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x1718 */
  __IO uint16_t PGPDO12;                           /**< SIUL2 Parallel GPIO Pad Data Out Register, offset: 0x171A */
  uint8_t RESERVED_16[36];
  __I  uint16_t PGPDI1;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1740 */
  __I  uint16_t PGPDI0;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1742 */
  __I  uint16_t PGPDI3;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1744 */
  __I  uint16_t PGPDI2;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1746 */
  __I  uint16_t PGPDI5;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1748 */
  __I  uint16_t PGPDI4;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x174A */
  __I  uint16_t PGPDI7;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x174C */
  __I  uint16_t PGPDI6;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x174E */
  __I  uint16_t PGPDI9;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1750 */
  __I  uint16_t PGPDI8;                            /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1752 */
  __I  uint16_t PGPDI11;                           /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1754 */
  __I  uint16_t PGPDI10;                           /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1756 */
  __I  uint16_t PGPDI13;                           /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x1758 */
  __I  uint16_t PGPDI12;                           /**< SIUL2 Parallel GPIO Pad Data In Register, offset: 0x175A */
  uint8_t RESERVED_17[36];
  __O  uint32_t MPGPDO[SIUL2_MPGPDO_COUNT];        /**< SIUL2 Masked Parallel GPIO Pad Data Out Register, array offset: 0x1780, array step: 0x4 */
} SIUL2_Type, *SIUL2_MemMapPtr;

/** Number of instances of the SIUL2 module. */
#define SIUL2_INSTANCE_COUNT                     (1u)

/* SIUL2 - Peripheral instance base addresses */
/** Peripheral SIUL2 base address */
#define IP_SIUL2_BASE                            (0x40290000u)
/** Peripheral SIUL2 base pointer */
#define IP_SIUL2                                 ((SIUL2_Type *)IP_SIUL2_BASE)
/** Array initializer of SIUL2 peripheral base addresses */
#define IP_SIUL2_BASE_ADDRS                      { IP_SIUL2_BASE }
/** Array initializer of SIUL2 peripheral base pointers */
#define IP_SIUL2_BASE_PTRS                       { IP_SIUL2 }

/* ----------------------------------------------------------------------------
   -- SIUL2 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIUL2_Register_Masks SIUL2 Register Masks
 * @{
 */

/*! @name MIDR1 - SIUL2 MCU ID Register #1 */
/*! @{ */

#define SIUL2_MIDR1_MINOR_MASK_MASK              (0xFU)
#define SIUL2_MIDR1_MINOR_MASK_SHIFT             (0U)
#define SIUL2_MIDR1_MINOR_MASK_WIDTH             (4U)
#define SIUL2_MIDR1_MINOR_MASK(x)                (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_MINOR_MASK_SHIFT)) & SIUL2_MIDR1_MINOR_MASK_MASK)

#define SIUL2_MIDR1_MAJOR_MASK_MASK              (0xF0U)
#define SIUL2_MIDR1_MAJOR_MASK_SHIFT             (4U)
#define SIUL2_MIDR1_MAJOR_MASK_WIDTH             (4U)
#define SIUL2_MIDR1_MAJOR_MASK(x)                (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_MAJOR_MASK_SHIFT)) & SIUL2_MIDR1_MAJOR_MASK_MASK)

#define SIUL2_MIDR1_PART_NO_MASK                 (0x3FF0000U)
#define SIUL2_MIDR1_PART_NO_SHIFT                (16U)
#define SIUL2_MIDR1_PART_NO_WIDTH                (10U)
#define SIUL2_MIDR1_PART_NO(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_PART_NO_SHIFT)) & SIUL2_MIDR1_PART_NO_MASK)

#define SIUL2_MIDR1_PRODUCT_LINE_LETTER_MASK     (0xFC000000U)
#define SIUL2_MIDR1_PRODUCT_LINE_LETTER_SHIFT    (26U)
#define SIUL2_MIDR1_PRODUCT_LINE_LETTER_WIDTH    (6U)
#define SIUL2_MIDR1_PRODUCT_LINE_LETTER(x)       (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_PRODUCT_LINE_LETTER_SHIFT)) & SIUL2_MIDR1_PRODUCT_LINE_LETTER_MASK)
/*! @} */

/*! @name MIDR2 - SIUL2 MCU ID Register #2 */
/*! @{ */

#define SIUL2_MIDR2_FLASH_SIZE_CODE_MASK         (0xFFU)
#define SIUL2_MIDR2_FLASH_SIZE_CODE_SHIFT        (0U)
#define SIUL2_MIDR2_FLASH_SIZE_CODE_WIDTH        (8U)
#define SIUL2_MIDR2_FLASH_SIZE_CODE(x)           (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_SIZE_CODE_SHIFT)) & SIUL2_MIDR2_FLASH_SIZE_CODE_MASK)

#define SIUL2_MIDR2_FLASH_SIZE_DATA_MASK         (0xF00U)
#define SIUL2_MIDR2_FLASH_SIZE_DATA_SHIFT        (8U)
#define SIUL2_MIDR2_FLASH_SIZE_DATA_WIDTH        (4U)
#define SIUL2_MIDR2_FLASH_SIZE_DATA(x)           (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_SIZE_DATA_SHIFT)) & SIUL2_MIDR2_FLASH_SIZE_DATA_MASK)

#define SIUL2_MIDR2_FLASH_DATA_MASK              (0x3000U)
#define SIUL2_MIDR2_FLASH_DATA_SHIFT             (12U)
#define SIUL2_MIDR2_FLASH_DATA_WIDTH             (2U)
#define SIUL2_MIDR2_FLASH_DATA(x)                (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_DATA_SHIFT)) & SIUL2_MIDR2_FLASH_DATA_MASK)

#define SIUL2_MIDR2_FLASH_CODE_MASK              (0xC000U)
#define SIUL2_MIDR2_FLASH_CODE_SHIFT             (14U)
#define SIUL2_MIDR2_FLASH_CODE_WIDTH             (2U)
#define SIUL2_MIDR2_FLASH_CODE(x)                (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_CODE_SHIFT)) & SIUL2_MIDR2_FLASH_CODE_MASK)

#define SIUL2_MIDR2_FREQUENCY_MASK               (0xF0000U)
#define SIUL2_MIDR2_FREQUENCY_SHIFT              (16U)
#define SIUL2_MIDR2_FREQUENCY_WIDTH              (4U)
#define SIUL2_MIDR2_FREQUENCY(x)                 (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FREQUENCY_SHIFT)) & SIUL2_MIDR2_FREQUENCY_MASK)

#define SIUL2_MIDR2_PACKAGE_MASK                 (0x3F00000U)
#define SIUL2_MIDR2_PACKAGE_SHIFT                (20U)
#define SIUL2_MIDR2_PACKAGE_WIDTH                (6U)
#define SIUL2_MIDR2_PACKAGE(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_PACKAGE_SHIFT)) & SIUL2_MIDR2_PACKAGE_MASK)

#define SIUL2_MIDR2_TEMPERATURE_MASK             (0x1C000000U)
#define SIUL2_MIDR2_TEMPERATURE_SHIFT            (26U)
#define SIUL2_MIDR2_TEMPERATURE_WIDTH            (3U)
#define SIUL2_MIDR2_TEMPERATURE(x)               (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_TEMPERATURE_SHIFT)) & SIUL2_MIDR2_TEMPERATURE_MASK)

#define SIUL2_MIDR2_TECHNOLOGY_MASK              (0xE0000000U)
#define SIUL2_MIDR2_TECHNOLOGY_SHIFT             (29U)
#define SIUL2_MIDR2_TECHNOLOGY_WIDTH             (3U)
#define SIUL2_MIDR2_TECHNOLOGY(x)                (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_TECHNOLOGY_SHIFT)) & SIUL2_MIDR2_TECHNOLOGY_MASK)
/*! @} */

/*! @name DISR0 - SIUL2 DMA/Interrupt Status Flag Register0 */
/*! @{ */

#define SIUL2_DISR0_EIF0_MASK                    (0x1U)
#define SIUL2_DISR0_EIF0_SHIFT                   (0U)
#define SIUL2_DISR0_EIF0_WIDTH                   (1U)
#define SIUL2_DISR0_EIF0(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF0_SHIFT)) & SIUL2_DISR0_EIF0_MASK)

#define SIUL2_DISR0_EIF1_MASK                    (0x2U)
#define SIUL2_DISR0_EIF1_SHIFT                   (1U)
#define SIUL2_DISR0_EIF1_WIDTH                   (1U)
#define SIUL2_DISR0_EIF1(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF1_SHIFT)) & SIUL2_DISR0_EIF1_MASK)

#define SIUL2_DISR0_EIF2_MASK                    (0x4U)
#define SIUL2_DISR0_EIF2_SHIFT                   (2U)
#define SIUL2_DISR0_EIF2_WIDTH                   (1U)
#define SIUL2_DISR0_EIF2(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF2_SHIFT)) & SIUL2_DISR0_EIF2_MASK)

#define SIUL2_DISR0_EIF3_MASK                    (0x8U)
#define SIUL2_DISR0_EIF3_SHIFT                   (3U)
#define SIUL2_DISR0_EIF3_WIDTH                   (1U)
#define SIUL2_DISR0_EIF3(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF3_SHIFT)) & SIUL2_DISR0_EIF3_MASK)

#define SIUL2_DISR0_EIF4_MASK                    (0x10U)
#define SIUL2_DISR0_EIF4_SHIFT                   (4U)
#define SIUL2_DISR0_EIF4_WIDTH                   (1U)
#define SIUL2_DISR0_EIF4(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF4_SHIFT)) & SIUL2_DISR0_EIF4_MASK)

#define SIUL2_DISR0_EIF5_MASK                    (0x20U)
#define SIUL2_DISR0_EIF5_SHIFT                   (5U)
#define SIUL2_DISR0_EIF5_WIDTH                   (1U)
#define SIUL2_DISR0_EIF5(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF5_SHIFT)) & SIUL2_DISR0_EIF5_MASK)

#define SIUL2_DISR0_EIF6_MASK                    (0x40U)
#define SIUL2_DISR0_EIF6_SHIFT                   (6U)
#define SIUL2_DISR0_EIF6_WIDTH                   (1U)
#define SIUL2_DISR0_EIF6(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF6_SHIFT)) & SIUL2_DISR0_EIF6_MASK)

#define SIUL2_DISR0_EIF7_MASK                    (0x80U)
#define SIUL2_DISR0_EIF7_SHIFT                   (7U)
#define SIUL2_DISR0_EIF7_WIDTH                   (1U)
#define SIUL2_DISR0_EIF7(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF7_SHIFT)) & SIUL2_DISR0_EIF7_MASK)

#define SIUL2_DISR0_EIF8_MASK                    (0x100U)
#define SIUL2_DISR0_EIF8_SHIFT                   (8U)
#define SIUL2_DISR0_EIF8_WIDTH                   (1U)
#define SIUL2_DISR0_EIF8(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF8_SHIFT)) & SIUL2_DISR0_EIF8_MASK)

#define SIUL2_DISR0_EIF9_MASK                    (0x200U)
#define SIUL2_DISR0_EIF9_SHIFT                   (9U)
#define SIUL2_DISR0_EIF9_WIDTH                   (1U)
#define SIUL2_DISR0_EIF9(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF9_SHIFT)) & SIUL2_DISR0_EIF9_MASK)

#define SIUL2_DISR0_EIF10_MASK                   (0x400U)
#define SIUL2_DISR0_EIF10_SHIFT                  (10U)
#define SIUL2_DISR0_EIF10_WIDTH                  (1U)
#define SIUL2_DISR0_EIF10(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF10_SHIFT)) & SIUL2_DISR0_EIF10_MASK)

#define SIUL2_DISR0_EIF11_MASK                   (0x800U)
#define SIUL2_DISR0_EIF11_SHIFT                  (11U)
#define SIUL2_DISR0_EIF11_WIDTH                  (1U)
#define SIUL2_DISR0_EIF11(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF11_SHIFT)) & SIUL2_DISR0_EIF11_MASK)

#define SIUL2_DISR0_EIF12_MASK                   (0x1000U)
#define SIUL2_DISR0_EIF12_SHIFT                  (12U)
#define SIUL2_DISR0_EIF12_WIDTH                  (1U)
#define SIUL2_DISR0_EIF12(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF12_SHIFT)) & SIUL2_DISR0_EIF12_MASK)

#define SIUL2_DISR0_EIF13_MASK                   (0x2000U)
#define SIUL2_DISR0_EIF13_SHIFT                  (13U)
#define SIUL2_DISR0_EIF13_WIDTH                  (1U)
#define SIUL2_DISR0_EIF13(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF13_SHIFT)) & SIUL2_DISR0_EIF13_MASK)

#define SIUL2_DISR0_EIF14_MASK                   (0x4000U)
#define SIUL2_DISR0_EIF14_SHIFT                  (14U)
#define SIUL2_DISR0_EIF14_WIDTH                  (1U)
#define SIUL2_DISR0_EIF14(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF14_SHIFT)) & SIUL2_DISR0_EIF14_MASK)

#define SIUL2_DISR0_EIF15_MASK                   (0x8000U)
#define SIUL2_DISR0_EIF15_SHIFT                  (15U)
#define SIUL2_DISR0_EIF15_WIDTH                  (1U)
#define SIUL2_DISR0_EIF15(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF15_SHIFT)) & SIUL2_DISR0_EIF15_MASK)

#define SIUL2_DISR0_EIF16_MASK                   (0x10000U)
#define SIUL2_DISR0_EIF16_SHIFT                  (16U)
#define SIUL2_DISR0_EIF16_WIDTH                  (1U)
#define SIUL2_DISR0_EIF16(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF16_SHIFT)) & SIUL2_DISR0_EIF16_MASK)

#define SIUL2_DISR0_EIF17_MASK                   (0x20000U)
#define SIUL2_DISR0_EIF17_SHIFT                  (17U)
#define SIUL2_DISR0_EIF17_WIDTH                  (1U)
#define SIUL2_DISR0_EIF17(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF17_SHIFT)) & SIUL2_DISR0_EIF17_MASK)

#define SIUL2_DISR0_EIF18_MASK                   (0x40000U)
#define SIUL2_DISR0_EIF18_SHIFT                  (18U)
#define SIUL2_DISR0_EIF18_WIDTH                  (1U)
#define SIUL2_DISR0_EIF18(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF18_SHIFT)) & SIUL2_DISR0_EIF18_MASK)

#define SIUL2_DISR0_EIF19_MASK                   (0x80000U)
#define SIUL2_DISR0_EIF19_SHIFT                  (19U)
#define SIUL2_DISR0_EIF19_WIDTH                  (1U)
#define SIUL2_DISR0_EIF19(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF19_SHIFT)) & SIUL2_DISR0_EIF19_MASK)

#define SIUL2_DISR0_EIF20_MASK                   (0x100000U)
#define SIUL2_DISR0_EIF20_SHIFT                  (20U)
#define SIUL2_DISR0_EIF20_WIDTH                  (1U)
#define SIUL2_DISR0_EIF20(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF20_SHIFT)) & SIUL2_DISR0_EIF20_MASK)

#define SIUL2_DISR0_EIF21_MASK                   (0x200000U)
#define SIUL2_DISR0_EIF21_SHIFT                  (21U)
#define SIUL2_DISR0_EIF21_WIDTH                  (1U)
#define SIUL2_DISR0_EIF21(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF21_SHIFT)) & SIUL2_DISR0_EIF21_MASK)

#define SIUL2_DISR0_EIF22_MASK                   (0x400000U)
#define SIUL2_DISR0_EIF22_SHIFT                  (22U)
#define SIUL2_DISR0_EIF22_WIDTH                  (1U)
#define SIUL2_DISR0_EIF22(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF22_SHIFT)) & SIUL2_DISR0_EIF22_MASK)

#define SIUL2_DISR0_EIF23_MASK                   (0x800000U)
#define SIUL2_DISR0_EIF23_SHIFT                  (23U)
#define SIUL2_DISR0_EIF23_WIDTH                  (1U)
#define SIUL2_DISR0_EIF23(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF23_SHIFT)) & SIUL2_DISR0_EIF23_MASK)

#define SIUL2_DISR0_EIF24_MASK                   (0x1000000U)
#define SIUL2_DISR0_EIF24_SHIFT                  (24U)
#define SIUL2_DISR0_EIF24_WIDTH                  (1U)
#define SIUL2_DISR0_EIF24(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF24_SHIFT)) & SIUL2_DISR0_EIF24_MASK)

#define SIUL2_DISR0_EIF25_MASK                   (0x2000000U)
#define SIUL2_DISR0_EIF25_SHIFT                  (25U)
#define SIUL2_DISR0_EIF25_WIDTH                  (1U)
#define SIUL2_DISR0_EIF25(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF25_SHIFT)) & SIUL2_DISR0_EIF25_MASK)

#define SIUL2_DISR0_EIF26_MASK                   (0x4000000U)
#define SIUL2_DISR0_EIF26_SHIFT                  (26U)
#define SIUL2_DISR0_EIF26_WIDTH                  (1U)
#define SIUL2_DISR0_EIF26(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF26_SHIFT)) & SIUL2_DISR0_EIF26_MASK)

#define SIUL2_DISR0_EIF27_MASK                   (0x8000000U)
#define SIUL2_DISR0_EIF27_SHIFT                  (27U)
#define SIUL2_DISR0_EIF27_WIDTH                  (1U)
#define SIUL2_DISR0_EIF27(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF27_SHIFT)) & SIUL2_DISR0_EIF27_MASK)

#define SIUL2_DISR0_EIF28_MASK                   (0x10000000U)
#define SIUL2_DISR0_EIF28_SHIFT                  (28U)
#define SIUL2_DISR0_EIF28_WIDTH                  (1U)
#define SIUL2_DISR0_EIF28(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF28_SHIFT)) & SIUL2_DISR0_EIF28_MASK)

#define SIUL2_DISR0_EIF29_MASK                   (0x20000000U)
#define SIUL2_DISR0_EIF29_SHIFT                  (29U)
#define SIUL2_DISR0_EIF29_WIDTH                  (1U)
#define SIUL2_DISR0_EIF29(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF29_SHIFT)) & SIUL2_DISR0_EIF29_MASK)

#define SIUL2_DISR0_EIF30_MASK                   (0x40000000U)
#define SIUL2_DISR0_EIF30_SHIFT                  (30U)
#define SIUL2_DISR0_EIF30_WIDTH                  (1U)
#define SIUL2_DISR0_EIF30(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF30_SHIFT)) & SIUL2_DISR0_EIF30_MASK)

#define SIUL2_DISR0_EIF31_MASK                   (0x80000000U)
#define SIUL2_DISR0_EIF31_SHIFT                  (31U)
#define SIUL2_DISR0_EIF31_WIDTH                  (1U)
#define SIUL2_DISR0_EIF31(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF31_SHIFT)) & SIUL2_DISR0_EIF31_MASK)
/*! @} */

/*! @name DIRER0 - SIUL2 DMA/Interrupt Request Enable Register0 */
/*! @{ */

#define SIUL2_DIRER0_EIRE0_MASK                  (0x1U)
#define SIUL2_DIRER0_EIRE0_SHIFT                 (0U)
#define SIUL2_DIRER0_EIRE0_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE0(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE0_SHIFT)) & SIUL2_DIRER0_EIRE0_MASK)

#define SIUL2_DIRER0_EIRE1_MASK                  (0x2U)
#define SIUL2_DIRER0_EIRE1_SHIFT                 (1U)
#define SIUL2_DIRER0_EIRE1_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE1(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE1_SHIFT)) & SIUL2_DIRER0_EIRE1_MASK)

#define SIUL2_DIRER0_EIRE2_MASK                  (0x4U)
#define SIUL2_DIRER0_EIRE2_SHIFT                 (2U)
#define SIUL2_DIRER0_EIRE2_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE2(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE2_SHIFT)) & SIUL2_DIRER0_EIRE2_MASK)

#define SIUL2_DIRER0_EIRE3_MASK                  (0x8U)
#define SIUL2_DIRER0_EIRE3_SHIFT                 (3U)
#define SIUL2_DIRER0_EIRE3_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE3(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE3_SHIFT)) & SIUL2_DIRER0_EIRE3_MASK)

#define SIUL2_DIRER0_EIRE4_MASK                  (0x10U)
#define SIUL2_DIRER0_EIRE4_SHIFT                 (4U)
#define SIUL2_DIRER0_EIRE4_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE4(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE4_SHIFT)) & SIUL2_DIRER0_EIRE4_MASK)

#define SIUL2_DIRER0_EIRE5_MASK                  (0x20U)
#define SIUL2_DIRER0_EIRE5_SHIFT                 (5U)
#define SIUL2_DIRER0_EIRE5_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE5(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE5_SHIFT)) & SIUL2_DIRER0_EIRE5_MASK)

#define SIUL2_DIRER0_EIRE6_MASK                  (0x40U)
#define SIUL2_DIRER0_EIRE6_SHIFT                 (6U)
#define SIUL2_DIRER0_EIRE6_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE6(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE6_SHIFT)) & SIUL2_DIRER0_EIRE6_MASK)

#define SIUL2_DIRER0_EIRE7_MASK                  (0x80U)
#define SIUL2_DIRER0_EIRE7_SHIFT                 (7U)
#define SIUL2_DIRER0_EIRE7_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE7(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE7_SHIFT)) & SIUL2_DIRER0_EIRE7_MASK)

#define SIUL2_DIRER0_EIRE8_MASK                  (0x100U)
#define SIUL2_DIRER0_EIRE8_SHIFT                 (8U)
#define SIUL2_DIRER0_EIRE8_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE8(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE8_SHIFT)) & SIUL2_DIRER0_EIRE8_MASK)

#define SIUL2_DIRER0_EIRE9_MASK                  (0x200U)
#define SIUL2_DIRER0_EIRE9_SHIFT                 (9U)
#define SIUL2_DIRER0_EIRE9_WIDTH                 (1U)
#define SIUL2_DIRER0_EIRE9(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE9_SHIFT)) & SIUL2_DIRER0_EIRE9_MASK)

#define SIUL2_DIRER0_EIRE10_MASK                 (0x400U)
#define SIUL2_DIRER0_EIRE10_SHIFT                (10U)
#define SIUL2_DIRER0_EIRE10_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE10(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE10_SHIFT)) & SIUL2_DIRER0_EIRE10_MASK)

#define SIUL2_DIRER0_EIRE11_MASK                 (0x800U)
#define SIUL2_DIRER0_EIRE11_SHIFT                (11U)
#define SIUL2_DIRER0_EIRE11_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE11(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE11_SHIFT)) & SIUL2_DIRER0_EIRE11_MASK)

#define SIUL2_DIRER0_EIRE12_MASK                 (0x1000U)
#define SIUL2_DIRER0_EIRE12_SHIFT                (12U)
#define SIUL2_DIRER0_EIRE12_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE12(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE12_SHIFT)) & SIUL2_DIRER0_EIRE12_MASK)

#define SIUL2_DIRER0_EIRE13_MASK                 (0x2000U)
#define SIUL2_DIRER0_EIRE13_SHIFT                (13U)
#define SIUL2_DIRER0_EIRE13_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE13(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE13_SHIFT)) & SIUL2_DIRER0_EIRE13_MASK)

#define SIUL2_DIRER0_EIRE14_MASK                 (0x4000U)
#define SIUL2_DIRER0_EIRE14_SHIFT                (14U)
#define SIUL2_DIRER0_EIRE14_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE14(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE14_SHIFT)) & SIUL2_DIRER0_EIRE14_MASK)

#define SIUL2_DIRER0_EIRE15_MASK                 (0x8000U)
#define SIUL2_DIRER0_EIRE15_SHIFT                (15U)
#define SIUL2_DIRER0_EIRE15_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE15(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE15_SHIFT)) & SIUL2_DIRER0_EIRE15_MASK)

#define SIUL2_DIRER0_EIRE16_MASK                 (0x10000U)
#define SIUL2_DIRER0_EIRE16_SHIFT                (16U)
#define SIUL2_DIRER0_EIRE16_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE16(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE16_SHIFT)) & SIUL2_DIRER0_EIRE16_MASK)

#define SIUL2_DIRER0_EIRE17_MASK                 (0x20000U)
#define SIUL2_DIRER0_EIRE17_SHIFT                (17U)
#define SIUL2_DIRER0_EIRE17_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE17(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE17_SHIFT)) & SIUL2_DIRER0_EIRE17_MASK)

#define SIUL2_DIRER0_EIRE18_MASK                 (0x40000U)
#define SIUL2_DIRER0_EIRE18_SHIFT                (18U)
#define SIUL2_DIRER0_EIRE18_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE18(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE18_SHIFT)) & SIUL2_DIRER0_EIRE18_MASK)

#define SIUL2_DIRER0_EIRE19_MASK                 (0x80000U)
#define SIUL2_DIRER0_EIRE19_SHIFT                (19U)
#define SIUL2_DIRER0_EIRE19_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE19(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE19_SHIFT)) & SIUL2_DIRER0_EIRE19_MASK)

#define SIUL2_DIRER0_EIRE20_MASK                 (0x100000U)
#define SIUL2_DIRER0_EIRE20_SHIFT                (20U)
#define SIUL2_DIRER0_EIRE20_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE20(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE20_SHIFT)) & SIUL2_DIRER0_EIRE20_MASK)

#define SIUL2_DIRER0_EIRE21_MASK                 (0x200000U)
#define SIUL2_DIRER0_EIRE21_SHIFT                (21U)
#define SIUL2_DIRER0_EIRE21_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE21(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE21_SHIFT)) & SIUL2_DIRER0_EIRE21_MASK)

#define SIUL2_DIRER0_EIRE22_MASK                 (0x400000U)
#define SIUL2_DIRER0_EIRE22_SHIFT                (22U)
#define SIUL2_DIRER0_EIRE22_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE22(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE22_SHIFT)) & SIUL2_DIRER0_EIRE22_MASK)

#define SIUL2_DIRER0_EIRE23_MASK                 (0x800000U)
#define SIUL2_DIRER0_EIRE23_SHIFT                (23U)
#define SIUL2_DIRER0_EIRE23_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE23(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE23_SHIFT)) & SIUL2_DIRER0_EIRE23_MASK)

#define SIUL2_DIRER0_EIRE24_MASK                 (0x1000000U)
#define SIUL2_DIRER0_EIRE24_SHIFT                (24U)
#define SIUL2_DIRER0_EIRE24_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE24(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE24_SHIFT)) & SIUL2_DIRER0_EIRE24_MASK)

#define SIUL2_DIRER0_EIRE25_MASK                 (0x2000000U)
#define SIUL2_DIRER0_EIRE25_SHIFT                (25U)
#define SIUL2_DIRER0_EIRE25_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE25(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE25_SHIFT)) & SIUL2_DIRER0_EIRE25_MASK)

#define SIUL2_DIRER0_EIRE26_MASK                 (0x4000000U)
#define SIUL2_DIRER0_EIRE26_SHIFT                (26U)
#define SIUL2_DIRER0_EIRE26_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE26(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE26_SHIFT)) & SIUL2_DIRER0_EIRE26_MASK)

#define SIUL2_DIRER0_EIRE27_MASK                 (0x8000000U)
#define SIUL2_DIRER0_EIRE27_SHIFT                (27U)
#define SIUL2_DIRER0_EIRE27_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE27(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE27_SHIFT)) & SIUL2_DIRER0_EIRE27_MASK)

#define SIUL2_DIRER0_EIRE28_MASK                 (0x10000000U)
#define SIUL2_DIRER0_EIRE28_SHIFT                (28U)
#define SIUL2_DIRER0_EIRE28_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE28(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE28_SHIFT)) & SIUL2_DIRER0_EIRE28_MASK)

#define SIUL2_DIRER0_EIRE29_MASK                 (0x20000000U)
#define SIUL2_DIRER0_EIRE29_SHIFT                (29U)
#define SIUL2_DIRER0_EIRE29_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE29(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE29_SHIFT)) & SIUL2_DIRER0_EIRE29_MASK)

#define SIUL2_DIRER0_EIRE30_MASK                 (0x40000000U)
#define SIUL2_DIRER0_EIRE30_SHIFT                (30U)
#define SIUL2_DIRER0_EIRE30_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE30(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE30_SHIFT)) & SIUL2_DIRER0_EIRE30_MASK)

#define SIUL2_DIRER0_EIRE31_MASK                 (0x80000000U)
#define SIUL2_DIRER0_EIRE31_SHIFT                (31U)
#define SIUL2_DIRER0_EIRE31_WIDTH                (1U)
#define SIUL2_DIRER0_EIRE31(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE31_SHIFT)) & SIUL2_DIRER0_EIRE31_MASK)
/*! @} */

/*! @name DIRSR0 - SIUL2 DMA/Interrupt Request Select Register0 */
/*! @{ */

#define SIUL2_DIRSR0_DIRSR0_MASK                 (0x1U)
#define SIUL2_DIRSR0_DIRSR0_SHIFT                (0U)
#define SIUL2_DIRSR0_DIRSR0_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR0(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR0_SHIFT)) & SIUL2_DIRSR0_DIRSR0_MASK)

#define SIUL2_DIRSR0_DIRSR1_MASK                 (0x2U)
#define SIUL2_DIRSR0_DIRSR1_SHIFT                (1U)
#define SIUL2_DIRSR0_DIRSR1_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR1(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR1_SHIFT)) & SIUL2_DIRSR0_DIRSR1_MASK)

#define SIUL2_DIRSR0_DIRSR2_MASK                 (0x4U)
#define SIUL2_DIRSR0_DIRSR2_SHIFT                (2U)
#define SIUL2_DIRSR0_DIRSR2_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR2(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR2_SHIFT)) & SIUL2_DIRSR0_DIRSR2_MASK)

#define SIUL2_DIRSR0_DIRSR3_MASK                 (0x8U)
#define SIUL2_DIRSR0_DIRSR3_SHIFT                (3U)
#define SIUL2_DIRSR0_DIRSR3_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR3(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR3_SHIFT)) & SIUL2_DIRSR0_DIRSR3_MASK)

#define SIUL2_DIRSR0_DIRSR4_MASK                 (0x10U)
#define SIUL2_DIRSR0_DIRSR4_SHIFT                (4U)
#define SIUL2_DIRSR0_DIRSR4_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR4(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR4_SHIFT)) & SIUL2_DIRSR0_DIRSR4_MASK)

#define SIUL2_DIRSR0_DIRSR5_MASK                 (0x20U)
#define SIUL2_DIRSR0_DIRSR5_SHIFT                (5U)
#define SIUL2_DIRSR0_DIRSR5_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR5(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR5_SHIFT)) & SIUL2_DIRSR0_DIRSR5_MASK)

#define SIUL2_DIRSR0_DIRSR6_MASK                 (0x40U)
#define SIUL2_DIRSR0_DIRSR6_SHIFT                (6U)
#define SIUL2_DIRSR0_DIRSR6_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR6(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR6_SHIFT)) & SIUL2_DIRSR0_DIRSR6_MASK)

#define SIUL2_DIRSR0_DIRSR7_MASK                 (0x80U)
#define SIUL2_DIRSR0_DIRSR7_SHIFT                (7U)
#define SIUL2_DIRSR0_DIRSR7_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR7(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR7_SHIFT)) & SIUL2_DIRSR0_DIRSR7_MASK)

#define SIUL2_DIRSR0_DIRSR8_MASK                 (0x100U)
#define SIUL2_DIRSR0_DIRSR8_SHIFT                (8U)
#define SIUL2_DIRSR0_DIRSR8_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR8(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR8_SHIFT)) & SIUL2_DIRSR0_DIRSR8_MASK)

#define SIUL2_DIRSR0_DIRSR9_MASK                 (0x200U)
#define SIUL2_DIRSR0_DIRSR9_SHIFT                (9U)
#define SIUL2_DIRSR0_DIRSR9_WIDTH                (1U)
#define SIUL2_DIRSR0_DIRSR9(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR9_SHIFT)) & SIUL2_DIRSR0_DIRSR9_MASK)

#define SIUL2_DIRSR0_DIRSR10_MASK                (0x400U)
#define SIUL2_DIRSR0_DIRSR10_SHIFT               (10U)
#define SIUL2_DIRSR0_DIRSR10_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR10(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR10_SHIFT)) & SIUL2_DIRSR0_DIRSR10_MASK)

#define SIUL2_DIRSR0_DIRSR11_MASK                (0x800U)
#define SIUL2_DIRSR0_DIRSR11_SHIFT               (11U)
#define SIUL2_DIRSR0_DIRSR11_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR11(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR11_SHIFT)) & SIUL2_DIRSR0_DIRSR11_MASK)

#define SIUL2_DIRSR0_DIRSR12_MASK                (0x1000U)
#define SIUL2_DIRSR0_DIRSR12_SHIFT               (12U)
#define SIUL2_DIRSR0_DIRSR12_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR12(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR12_SHIFT)) & SIUL2_DIRSR0_DIRSR12_MASK)

#define SIUL2_DIRSR0_DIRSR13_MASK                (0x2000U)
#define SIUL2_DIRSR0_DIRSR13_SHIFT               (13U)
#define SIUL2_DIRSR0_DIRSR13_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR13(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR13_SHIFT)) & SIUL2_DIRSR0_DIRSR13_MASK)

#define SIUL2_DIRSR0_DIRSR14_MASK                (0x4000U)
#define SIUL2_DIRSR0_DIRSR14_SHIFT               (14U)
#define SIUL2_DIRSR0_DIRSR14_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR14(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR14_SHIFT)) & SIUL2_DIRSR0_DIRSR14_MASK)

#define SIUL2_DIRSR0_DIRSR15_MASK                (0x8000U)
#define SIUL2_DIRSR0_DIRSR15_SHIFT               (15U)
#define SIUL2_DIRSR0_DIRSR15_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR15(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR15_SHIFT)) & SIUL2_DIRSR0_DIRSR15_MASK)

#define SIUL2_DIRSR0_DIRSR16_MASK                (0x10000U)
#define SIUL2_DIRSR0_DIRSR16_SHIFT               (16U)
#define SIUL2_DIRSR0_DIRSR16_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR16(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR16_SHIFT)) & SIUL2_DIRSR0_DIRSR16_MASK)

#define SIUL2_DIRSR0_DIRSR17_MASK                (0x20000U)
#define SIUL2_DIRSR0_DIRSR17_SHIFT               (17U)
#define SIUL2_DIRSR0_DIRSR17_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR17(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR17_SHIFT)) & SIUL2_DIRSR0_DIRSR17_MASK)

#define SIUL2_DIRSR0_DIRSR18_MASK                (0x40000U)
#define SIUL2_DIRSR0_DIRSR18_SHIFT               (18U)
#define SIUL2_DIRSR0_DIRSR18_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR18(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR18_SHIFT)) & SIUL2_DIRSR0_DIRSR18_MASK)

#define SIUL2_DIRSR0_DIRSR19_MASK                (0x80000U)
#define SIUL2_DIRSR0_DIRSR19_SHIFT               (19U)
#define SIUL2_DIRSR0_DIRSR19_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR19(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR19_SHIFT)) & SIUL2_DIRSR0_DIRSR19_MASK)

#define SIUL2_DIRSR0_DIRSR20_MASK                (0x100000U)
#define SIUL2_DIRSR0_DIRSR20_SHIFT               (20U)
#define SIUL2_DIRSR0_DIRSR20_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR20(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR20_SHIFT)) & SIUL2_DIRSR0_DIRSR20_MASK)

#define SIUL2_DIRSR0_DIRSR21_MASK                (0x200000U)
#define SIUL2_DIRSR0_DIRSR21_SHIFT               (21U)
#define SIUL2_DIRSR0_DIRSR21_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR21(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR21_SHIFT)) & SIUL2_DIRSR0_DIRSR21_MASK)

#define SIUL2_DIRSR0_DIRSR22_MASK                (0x400000U)
#define SIUL2_DIRSR0_DIRSR22_SHIFT               (22U)
#define SIUL2_DIRSR0_DIRSR22_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR22(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR22_SHIFT)) & SIUL2_DIRSR0_DIRSR22_MASK)

#define SIUL2_DIRSR0_DIRSR23_MASK                (0x800000U)
#define SIUL2_DIRSR0_DIRSR23_SHIFT               (23U)
#define SIUL2_DIRSR0_DIRSR23_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR23(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR23_SHIFT)) & SIUL2_DIRSR0_DIRSR23_MASK)

#define SIUL2_DIRSR0_DIRSR24_MASK                (0x1000000U)
#define SIUL2_DIRSR0_DIRSR24_SHIFT               (24U)
#define SIUL2_DIRSR0_DIRSR24_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR24(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR24_SHIFT)) & SIUL2_DIRSR0_DIRSR24_MASK)

#define SIUL2_DIRSR0_DIRSR25_MASK                (0x2000000U)
#define SIUL2_DIRSR0_DIRSR25_SHIFT               (25U)
#define SIUL2_DIRSR0_DIRSR25_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR25(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR25_SHIFT)) & SIUL2_DIRSR0_DIRSR25_MASK)

#define SIUL2_DIRSR0_DIRSR26_MASK                (0x4000000U)
#define SIUL2_DIRSR0_DIRSR26_SHIFT               (26U)
#define SIUL2_DIRSR0_DIRSR26_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR26(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR26_SHIFT)) & SIUL2_DIRSR0_DIRSR26_MASK)

#define SIUL2_DIRSR0_DIRSR27_MASK                (0x8000000U)
#define SIUL2_DIRSR0_DIRSR27_SHIFT               (27U)
#define SIUL2_DIRSR0_DIRSR27_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR27(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR27_SHIFT)) & SIUL2_DIRSR0_DIRSR27_MASK)

#define SIUL2_DIRSR0_DIRSR28_MASK                (0x10000000U)
#define SIUL2_DIRSR0_DIRSR28_SHIFT               (28U)
#define SIUL2_DIRSR0_DIRSR28_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR28(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR28_SHIFT)) & SIUL2_DIRSR0_DIRSR28_MASK)

#define SIUL2_DIRSR0_DIRSR29_MASK                (0x20000000U)
#define SIUL2_DIRSR0_DIRSR29_SHIFT               (29U)
#define SIUL2_DIRSR0_DIRSR29_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR29(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR29_SHIFT)) & SIUL2_DIRSR0_DIRSR29_MASK)

#define SIUL2_DIRSR0_DIRSR30_MASK                (0x40000000U)
#define SIUL2_DIRSR0_DIRSR30_SHIFT               (30U)
#define SIUL2_DIRSR0_DIRSR30_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR30(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR30_SHIFT)) & SIUL2_DIRSR0_DIRSR30_MASK)

#define SIUL2_DIRSR0_DIRSR31_MASK                (0x80000000U)
#define SIUL2_DIRSR0_DIRSR31_SHIFT               (31U)
#define SIUL2_DIRSR0_DIRSR31_WIDTH               (1U)
#define SIUL2_DIRSR0_DIRSR31(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR31_SHIFT)) & SIUL2_DIRSR0_DIRSR31_MASK)
/*! @} */

/*! @name IREER0 - SIUL2 Interrupt Rising-Edge Event Enable Register 0 */
/*! @{ */

#define SIUL2_IREER0_IREE0_MASK                  (0x1U)
#define SIUL2_IREER0_IREE0_SHIFT                 (0U)
#define SIUL2_IREER0_IREE0_WIDTH                 (1U)
#define SIUL2_IREER0_IREE0(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE0_SHIFT)) & SIUL2_IREER0_IREE0_MASK)

#define SIUL2_IREER0_IREE1_MASK                  (0x2U)
#define SIUL2_IREER0_IREE1_SHIFT                 (1U)
#define SIUL2_IREER0_IREE1_WIDTH                 (1U)
#define SIUL2_IREER0_IREE1(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE1_SHIFT)) & SIUL2_IREER0_IREE1_MASK)

#define SIUL2_IREER0_IREE2_MASK                  (0x4U)
#define SIUL2_IREER0_IREE2_SHIFT                 (2U)
#define SIUL2_IREER0_IREE2_WIDTH                 (1U)
#define SIUL2_IREER0_IREE2(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE2_SHIFT)) & SIUL2_IREER0_IREE2_MASK)

#define SIUL2_IREER0_IREE3_MASK                  (0x8U)
#define SIUL2_IREER0_IREE3_SHIFT                 (3U)
#define SIUL2_IREER0_IREE3_WIDTH                 (1U)
#define SIUL2_IREER0_IREE3(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE3_SHIFT)) & SIUL2_IREER0_IREE3_MASK)

#define SIUL2_IREER0_IREE4_MASK                  (0x10U)
#define SIUL2_IREER0_IREE4_SHIFT                 (4U)
#define SIUL2_IREER0_IREE4_WIDTH                 (1U)
#define SIUL2_IREER0_IREE4(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE4_SHIFT)) & SIUL2_IREER0_IREE4_MASK)

#define SIUL2_IREER0_IREE5_MASK                  (0x20U)
#define SIUL2_IREER0_IREE5_SHIFT                 (5U)
#define SIUL2_IREER0_IREE5_WIDTH                 (1U)
#define SIUL2_IREER0_IREE5(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE5_SHIFT)) & SIUL2_IREER0_IREE5_MASK)

#define SIUL2_IREER0_IREE6_MASK                  (0x40U)
#define SIUL2_IREER0_IREE6_SHIFT                 (6U)
#define SIUL2_IREER0_IREE6_WIDTH                 (1U)
#define SIUL2_IREER0_IREE6(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE6_SHIFT)) & SIUL2_IREER0_IREE6_MASK)

#define SIUL2_IREER0_IREE7_MASK                  (0x80U)
#define SIUL2_IREER0_IREE7_SHIFT                 (7U)
#define SIUL2_IREER0_IREE7_WIDTH                 (1U)
#define SIUL2_IREER0_IREE7(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE7_SHIFT)) & SIUL2_IREER0_IREE7_MASK)

#define SIUL2_IREER0_IREE8_MASK                  (0x100U)
#define SIUL2_IREER0_IREE8_SHIFT                 (8U)
#define SIUL2_IREER0_IREE8_WIDTH                 (1U)
#define SIUL2_IREER0_IREE8(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE8_SHIFT)) & SIUL2_IREER0_IREE8_MASK)

#define SIUL2_IREER0_IREE9_MASK                  (0x200U)
#define SIUL2_IREER0_IREE9_SHIFT                 (9U)
#define SIUL2_IREER0_IREE9_WIDTH                 (1U)
#define SIUL2_IREER0_IREE9(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE9_SHIFT)) & SIUL2_IREER0_IREE9_MASK)

#define SIUL2_IREER0_IREE10_MASK                 (0x400U)
#define SIUL2_IREER0_IREE10_SHIFT                (10U)
#define SIUL2_IREER0_IREE10_WIDTH                (1U)
#define SIUL2_IREER0_IREE10(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE10_SHIFT)) & SIUL2_IREER0_IREE10_MASK)

#define SIUL2_IREER0_IREE11_MASK                 (0x800U)
#define SIUL2_IREER0_IREE11_SHIFT                (11U)
#define SIUL2_IREER0_IREE11_WIDTH                (1U)
#define SIUL2_IREER0_IREE11(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE11_SHIFT)) & SIUL2_IREER0_IREE11_MASK)

#define SIUL2_IREER0_IREE12_MASK                 (0x1000U)
#define SIUL2_IREER0_IREE12_SHIFT                (12U)
#define SIUL2_IREER0_IREE12_WIDTH                (1U)
#define SIUL2_IREER0_IREE12(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE12_SHIFT)) & SIUL2_IREER0_IREE12_MASK)

#define SIUL2_IREER0_IREE13_MASK                 (0x2000U)
#define SIUL2_IREER0_IREE13_SHIFT                (13U)
#define SIUL2_IREER0_IREE13_WIDTH                (1U)
#define SIUL2_IREER0_IREE13(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE13_SHIFT)) & SIUL2_IREER0_IREE13_MASK)

#define SIUL2_IREER0_IREE14_MASK                 (0x4000U)
#define SIUL2_IREER0_IREE14_SHIFT                (14U)
#define SIUL2_IREER0_IREE14_WIDTH                (1U)
#define SIUL2_IREER0_IREE14(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE14_SHIFT)) & SIUL2_IREER0_IREE14_MASK)

#define SIUL2_IREER0_IREE15_MASK                 (0x8000U)
#define SIUL2_IREER0_IREE15_SHIFT                (15U)
#define SIUL2_IREER0_IREE15_WIDTH                (1U)
#define SIUL2_IREER0_IREE15(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE15_SHIFT)) & SIUL2_IREER0_IREE15_MASK)

#define SIUL2_IREER0_IREE16_MASK                 (0x10000U)
#define SIUL2_IREER0_IREE16_SHIFT                (16U)
#define SIUL2_IREER0_IREE16_WIDTH                (1U)
#define SIUL2_IREER0_IREE16(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE16_SHIFT)) & SIUL2_IREER0_IREE16_MASK)

#define SIUL2_IREER0_IREE17_MASK                 (0x20000U)
#define SIUL2_IREER0_IREE17_SHIFT                (17U)
#define SIUL2_IREER0_IREE17_WIDTH                (1U)
#define SIUL2_IREER0_IREE17(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE17_SHIFT)) & SIUL2_IREER0_IREE17_MASK)

#define SIUL2_IREER0_IREE18_MASK                 (0x40000U)
#define SIUL2_IREER0_IREE18_SHIFT                (18U)
#define SIUL2_IREER0_IREE18_WIDTH                (1U)
#define SIUL2_IREER0_IREE18(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE18_SHIFT)) & SIUL2_IREER0_IREE18_MASK)

#define SIUL2_IREER0_IREE19_MASK                 (0x80000U)
#define SIUL2_IREER0_IREE19_SHIFT                (19U)
#define SIUL2_IREER0_IREE19_WIDTH                (1U)
#define SIUL2_IREER0_IREE19(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE19_SHIFT)) & SIUL2_IREER0_IREE19_MASK)

#define SIUL2_IREER0_IREE20_MASK                 (0x100000U)
#define SIUL2_IREER0_IREE20_SHIFT                (20U)
#define SIUL2_IREER0_IREE20_WIDTH                (1U)
#define SIUL2_IREER0_IREE20(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE20_SHIFT)) & SIUL2_IREER0_IREE20_MASK)

#define SIUL2_IREER0_IREE21_MASK                 (0x200000U)
#define SIUL2_IREER0_IREE21_SHIFT                (21U)
#define SIUL2_IREER0_IREE21_WIDTH                (1U)
#define SIUL2_IREER0_IREE21(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE21_SHIFT)) & SIUL2_IREER0_IREE21_MASK)

#define SIUL2_IREER0_IREE22_MASK                 (0x400000U)
#define SIUL2_IREER0_IREE22_SHIFT                (22U)
#define SIUL2_IREER0_IREE22_WIDTH                (1U)
#define SIUL2_IREER0_IREE22(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE22_SHIFT)) & SIUL2_IREER0_IREE22_MASK)

#define SIUL2_IREER0_IREE23_MASK                 (0x800000U)
#define SIUL2_IREER0_IREE23_SHIFT                (23U)
#define SIUL2_IREER0_IREE23_WIDTH                (1U)
#define SIUL2_IREER0_IREE23(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE23_SHIFT)) & SIUL2_IREER0_IREE23_MASK)

#define SIUL2_IREER0_IREE24_MASK                 (0x1000000U)
#define SIUL2_IREER0_IREE24_SHIFT                (24U)
#define SIUL2_IREER0_IREE24_WIDTH                (1U)
#define SIUL2_IREER0_IREE24(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE24_SHIFT)) & SIUL2_IREER0_IREE24_MASK)

#define SIUL2_IREER0_IREE25_MASK                 (0x2000000U)
#define SIUL2_IREER0_IREE25_SHIFT                (25U)
#define SIUL2_IREER0_IREE25_WIDTH                (1U)
#define SIUL2_IREER0_IREE25(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE25_SHIFT)) & SIUL2_IREER0_IREE25_MASK)

#define SIUL2_IREER0_IREE26_MASK                 (0x4000000U)
#define SIUL2_IREER0_IREE26_SHIFT                (26U)
#define SIUL2_IREER0_IREE26_WIDTH                (1U)
#define SIUL2_IREER0_IREE26(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE26_SHIFT)) & SIUL2_IREER0_IREE26_MASK)

#define SIUL2_IREER0_IREE27_MASK                 (0x8000000U)
#define SIUL2_IREER0_IREE27_SHIFT                (27U)
#define SIUL2_IREER0_IREE27_WIDTH                (1U)
#define SIUL2_IREER0_IREE27(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE27_SHIFT)) & SIUL2_IREER0_IREE27_MASK)

#define SIUL2_IREER0_IREE28_MASK                 (0x10000000U)
#define SIUL2_IREER0_IREE28_SHIFT                (28U)
#define SIUL2_IREER0_IREE28_WIDTH                (1U)
#define SIUL2_IREER0_IREE28(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE28_SHIFT)) & SIUL2_IREER0_IREE28_MASK)

#define SIUL2_IREER0_IREE29_MASK                 (0x20000000U)
#define SIUL2_IREER0_IREE29_SHIFT                (29U)
#define SIUL2_IREER0_IREE29_WIDTH                (1U)
#define SIUL2_IREER0_IREE29(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE29_SHIFT)) & SIUL2_IREER0_IREE29_MASK)

#define SIUL2_IREER0_IREE30_MASK                 (0x40000000U)
#define SIUL2_IREER0_IREE30_SHIFT                (30U)
#define SIUL2_IREER0_IREE30_WIDTH                (1U)
#define SIUL2_IREER0_IREE30(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE30_SHIFT)) & SIUL2_IREER0_IREE30_MASK)

#define SIUL2_IREER0_IREE31_MASK                 (0x80000000U)
#define SIUL2_IREER0_IREE31_SHIFT                (31U)
#define SIUL2_IREER0_IREE31_WIDTH                (1U)
#define SIUL2_IREER0_IREE31(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE31_SHIFT)) & SIUL2_IREER0_IREE31_MASK)
/*! @} */

/*! @name IFEER0 - SIUL2 Interrupt Falling-Edge Event Enable Register 0 */
/*! @{ */

#define SIUL2_IFEER0_IFEE0_MASK                  (0x1U)
#define SIUL2_IFEER0_IFEE0_SHIFT                 (0U)
#define SIUL2_IFEER0_IFEE0_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE0(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE0_SHIFT)) & SIUL2_IFEER0_IFEE0_MASK)

#define SIUL2_IFEER0_IFEE1_MASK                  (0x2U)
#define SIUL2_IFEER0_IFEE1_SHIFT                 (1U)
#define SIUL2_IFEER0_IFEE1_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE1(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE1_SHIFT)) & SIUL2_IFEER0_IFEE1_MASK)

#define SIUL2_IFEER0_IFEE2_MASK                  (0x4U)
#define SIUL2_IFEER0_IFEE2_SHIFT                 (2U)
#define SIUL2_IFEER0_IFEE2_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE2(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE2_SHIFT)) & SIUL2_IFEER0_IFEE2_MASK)

#define SIUL2_IFEER0_IFEE3_MASK                  (0x8U)
#define SIUL2_IFEER0_IFEE3_SHIFT                 (3U)
#define SIUL2_IFEER0_IFEE3_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE3(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE3_SHIFT)) & SIUL2_IFEER0_IFEE3_MASK)

#define SIUL2_IFEER0_IFEE4_MASK                  (0x10U)
#define SIUL2_IFEER0_IFEE4_SHIFT                 (4U)
#define SIUL2_IFEER0_IFEE4_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE4(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE4_SHIFT)) & SIUL2_IFEER0_IFEE4_MASK)

#define SIUL2_IFEER0_IFEE5_MASK                  (0x20U)
#define SIUL2_IFEER0_IFEE5_SHIFT                 (5U)
#define SIUL2_IFEER0_IFEE5_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE5(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE5_SHIFT)) & SIUL2_IFEER0_IFEE5_MASK)

#define SIUL2_IFEER0_IFEE6_MASK                  (0x40U)
#define SIUL2_IFEER0_IFEE6_SHIFT                 (6U)
#define SIUL2_IFEER0_IFEE6_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE6(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE6_SHIFT)) & SIUL2_IFEER0_IFEE6_MASK)

#define SIUL2_IFEER0_IFEE7_MASK                  (0x80U)
#define SIUL2_IFEER0_IFEE7_SHIFT                 (7U)
#define SIUL2_IFEER0_IFEE7_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE7(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE7_SHIFT)) & SIUL2_IFEER0_IFEE7_MASK)

#define SIUL2_IFEER0_IFEE8_MASK                  (0x100U)
#define SIUL2_IFEER0_IFEE8_SHIFT                 (8U)
#define SIUL2_IFEER0_IFEE8_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE8(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE8_SHIFT)) & SIUL2_IFEER0_IFEE8_MASK)

#define SIUL2_IFEER0_IFEE9_MASK                  (0x200U)
#define SIUL2_IFEER0_IFEE9_SHIFT                 (9U)
#define SIUL2_IFEER0_IFEE9_WIDTH                 (1U)
#define SIUL2_IFEER0_IFEE9(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE9_SHIFT)) & SIUL2_IFEER0_IFEE9_MASK)

#define SIUL2_IFEER0_IFEE10_MASK                 (0x400U)
#define SIUL2_IFEER0_IFEE10_SHIFT                (10U)
#define SIUL2_IFEER0_IFEE10_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE10(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE10_SHIFT)) & SIUL2_IFEER0_IFEE10_MASK)

#define SIUL2_IFEER0_IFEE11_MASK                 (0x800U)
#define SIUL2_IFEER0_IFEE11_SHIFT                (11U)
#define SIUL2_IFEER0_IFEE11_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE11(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE11_SHIFT)) & SIUL2_IFEER0_IFEE11_MASK)

#define SIUL2_IFEER0_IFEE12_MASK                 (0x1000U)
#define SIUL2_IFEER0_IFEE12_SHIFT                (12U)
#define SIUL2_IFEER0_IFEE12_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE12(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE12_SHIFT)) & SIUL2_IFEER0_IFEE12_MASK)

#define SIUL2_IFEER0_IFEE13_MASK                 (0x2000U)
#define SIUL2_IFEER0_IFEE13_SHIFT                (13U)
#define SIUL2_IFEER0_IFEE13_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE13(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE13_SHIFT)) & SIUL2_IFEER0_IFEE13_MASK)

#define SIUL2_IFEER0_IFEE14_MASK                 (0x4000U)
#define SIUL2_IFEER0_IFEE14_SHIFT                (14U)
#define SIUL2_IFEER0_IFEE14_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE14(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE14_SHIFT)) & SIUL2_IFEER0_IFEE14_MASK)

#define SIUL2_IFEER0_IFEE15_MASK                 (0x8000U)
#define SIUL2_IFEER0_IFEE15_SHIFT                (15U)
#define SIUL2_IFEER0_IFEE15_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE15(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE15_SHIFT)) & SIUL2_IFEER0_IFEE15_MASK)

#define SIUL2_IFEER0_IFEE16_MASK                 (0x10000U)
#define SIUL2_IFEER0_IFEE16_SHIFT                (16U)
#define SIUL2_IFEER0_IFEE16_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE16(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE16_SHIFT)) & SIUL2_IFEER0_IFEE16_MASK)

#define SIUL2_IFEER0_IFEE17_MASK                 (0x20000U)
#define SIUL2_IFEER0_IFEE17_SHIFT                (17U)
#define SIUL2_IFEER0_IFEE17_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE17(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE17_SHIFT)) & SIUL2_IFEER0_IFEE17_MASK)

#define SIUL2_IFEER0_IFEE18_MASK                 (0x40000U)
#define SIUL2_IFEER0_IFEE18_SHIFT                (18U)
#define SIUL2_IFEER0_IFEE18_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE18(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE18_SHIFT)) & SIUL2_IFEER0_IFEE18_MASK)

#define SIUL2_IFEER0_IFEE19_MASK                 (0x80000U)
#define SIUL2_IFEER0_IFEE19_SHIFT                (19U)
#define SIUL2_IFEER0_IFEE19_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE19(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE19_SHIFT)) & SIUL2_IFEER0_IFEE19_MASK)

#define SIUL2_IFEER0_IFEE20_MASK                 (0x100000U)
#define SIUL2_IFEER0_IFEE20_SHIFT                (20U)
#define SIUL2_IFEER0_IFEE20_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE20(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE20_SHIFT)) & SIUL2_IFEER0_IFEE20_MASK)

#define SIUL2_IFEER0_IFEE21_MASK                 (0x200000U)
#define SIUL2_IFEER0_IFEE21_SHIFT                (21U)
#define SIUL2_IFEER0_IFEE21_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE21(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE21_SHIFT)) & SIUL2_IFEER0_IFEE21_MASK)

#define SIUL2_IFEER0_IFEE22_MASK                 (0x400000U)
#define SIUL2_IFEER0_IFEE22_SHIFT                (22U)
#define SIUL2_IFEER0_IFEE22_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE22(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE22_SHIFT)) & SIUL2_IFEER0_IFEE22_MASK)

#define SIUL2_IFEER0_IFEE23_MASK                 (0x800000U)
#define SIUL2_IFEER0_IFEE23_SHIFT                (23U)
#define SIUL2_IFEER0_IFEE23_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE23(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE23_SHIFT)) & SIUL2_IFEER0_IFEE23_MASK)

#define SIUL2_IFEER0_IFEE24_MASK                 (0x1000000U)
#define SIUL2_IFEER0_IFEE24_SHIFT                (24U)
#define SIUL2_IFEER0_IFEE24_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE24(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE24_SHIFT)) & SIUL2_IFEER0_IFEE24_MASK)

#define SIUL2_IFEER0_IFEE25_MASK                 (0x2000000U)
#define SIUL2_IFEER0_IFEE25_SHIFT                (25U)
#define SIUL2_IFEER0_IFEE25_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE25(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE25_SHIFT)) & SIUL2_IFEER0_IFEE25_MASK)

#define SIUL2_IFEER0_IFEE26_MASK                 (0x4000000U)
#define SIUL2_IFEER0_IFEE26_SHIFT                (26U)
#define SIUL2_IFEER0_IFEE26_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE26(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE26_SHIFT)) & SIUL2_IFEER0_IFEE26_MASK)

#define SIUL2_IFEER0_IFEE27_MASK                 (0x8000000U)
#define SIUL2_IFEER0_IFEE27_SHIFT                (27U)
#define SIUL2_IFEER0_IFEE27_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE27(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE27_SHIFT)) & SIUL2_IFEER0_IFEE27_MASK)

#define SIUL2_IFEER0_IFEE28_MASK                 (0x10000000U)
#define SIUL2_IFEER0_IFEE28_SHIFT                (28U)
#define SIUL2_IFEER0_IFEE28_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE28(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE28_SHIFT)) & SIUL2_IFEER0_IFEE28_MASK)

#define SIUL2_IFEER0_IFEE29_MASK                 (0x20000000U)
#define SIUL2_IFEER0_IFEE29_SHIFT                (29U)
#define SIUL2_IFEER0_IFEE29_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE29(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE29_SHIFT)) & SIUL2_IFEER0_IFEE29_MASK)

#define SIUL2_IFEER0_IFEE30_MASK                 (0x40000000U)
#define SIUL2_IFEER0_IFEE30_SHIFT                (30U)
#define SIUL2_IFEER0_IFEE30_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE30(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE30_SHIFT)) & SIUL2_IFEER0_IFEE30_MASK)

#define SIUL2_IFEER0_IFEE31_MASK                 (0x80000000U)
#define SIUL2_IFEER0_IFEE31_SHIFT                (31U)
#define SIUL2_IFEER0_IFEE31_WIDTH                (1U)
#define SIUL2_IFEER0_IFEE31(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE31_SHIFT)) & SIUL2_IFEER0_IFEE31_MASK)
/*! @} */

/*! @name IFER0 - SIUL2 Interrupt Filter Enable Register 0 */
/*! @{ */

#define SIUL2_IFER0_IFE0_MASK                    (0x1U)
#define SIUL2_IFER0_IFE0_SHIFT                   (0U)
#define SIUL2_IFER0_IFE0_WIDTH                   (1U)
#define SIUL2_IFER0_IFE0(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE0_SHIFT)) & SIUL2_IFER0_IFE0_MASK)

#define SIUL2_IFER0_IFE1_MASK                    (0x2U)
#define SIUL2_IFER0_IFE1_SHIFT                   (1U)
#define SIUL2_IFER0_IFE1_WIDTH                   (1U)
#define SIUL2_IFER0_IFE1(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE1_SHIFT)) & SIUL2_IFER0_IFE1_MASK)

#define SIUL2_IFER0_IFE2_MASK                    (0x4U)
#define SIUL2_IFER0_IFE2_SHIFT                   (2U)
#define SIUL2_IFER0_IFE2_WIDTH                   (1U)
#define SIUL2_IFER0_IFE2(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE2_SHIFT)) & SIUL2_IFER0_IFE2_MASK)

#define SIUL2_IFER0_IFE3_MASK                    (0x8U)
#define SIUL2_IFER0_IFE3_SHIFT                   (3U)
#define SIUL2_IFER0_IFE3_WIDTH                   (1U)
#define SIUL2_IFER0_IFE3(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE3_SHIFT)) & SIUL2_IFER0_IFE3_MASK)

#define SIUL2_IFER0_IFE4_MASK                    (0x10U)
#define SIUL2_IFER0_IFE4_SHIFT                   (4U)
#define SIUL2_IFER0_IFE4_WIDTH                   (1U)
#define SIUL2_IFER0_IFE4(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE4_SHIFT)) & SIUL2_IFER0_IFE4_MASK)

#define SIUL2_IFER0_IFE5_MASK                    (0x20U)
#define SIUL2_IFER0_IFE5_SHIFT                   (5U)
#define SIUL2_IFER0_IFE5_WIDTH                   (1U)
#define SIUL2_IFER0_IFE5(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE5_SHIFT)) & SIUL2_IFER0_IFE5_MASK)

#define SIUL2_IFER0_IFE6_MASK                    (0x40U)
#define SIUL2_IFER0_IFE6_SHIFT                   (6U)
#define SIUL2_IFER0_IFE6_WIDTH                   (1U)
#define SIUL2_IFER0_IFE6(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE6_SHIFT)) & SIUL2_IFER0_IFE6_MASK)

#define SIUL2_IFER0_IFE7_MASK                    (0x80U)
#define SIUL2_IFER0_IFE7_SHIFT                   (7U)
#define SIUL2_IFER0_IFE7_WIDTH                   (1U)
#define SIUL2_IFER0_IFE7(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE7_SHIFT)) & SIUL2_IFER0_IFE7_MASK)

#define SIUL2_IFER0_IFE8_MASK                    (0x100U)
#define SIUL2_IFER0_IFE8_SHIFT                   (8U)
#define SIUL2_IFER0_IFE8_WIDTH                   (1U)
#define SIUL2_IFER0_IFE8(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE8_SHIFT)) & SIUL2_IFER0_IFE8_MASK)

#define SIUL2_IFER0_IFE9_MASK                    (0x200U)
#define SIUL2_IFER0_IFE9_SHIFT                   (9U)
#define SIUL2_IFER0_IFE9_WIDTH                   (1U)
#define SIUL2_IFER0_IFE9(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE9_SHIFT)) & SIUL2_IFER0_IFE9_MASK)

#define SIUL2_IFER0_IFE10_MASK                   (0x400U)
#define SIUL2_IFER0_IFE10_SHIFT                  (10U)
#define SIUL2_IFER0_IFE10_WIDTH                  (1U)
#define SIUL2_IFER0_IFE10(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE10_SHIFT)) & SIUL2_IFER0_IFE10_MASK)

#define SIUL2_IFER0_IFE11_MASK                   (0x800U)
#define SIUL2_IFER0_IFE11_SHIFT                  (11U)
#define SIUL2_IFER0_IFE11_WIDTH                  (1U)
#define SIUL2_IFER0_IFE11(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE11_SHIFT)) & SIUL2_IFER0_IFE11_MASK)

#define SIUL2_IFER0_IFE12_MASK                   (0x1000U)
#define SIUL2_IFER0_IFE12_SHIFT                  (12U)
#define SIUL2_IFER0_IFE12_WIDTH                  (1U)
#define SIUL2_IFER0_IFE12(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE12_SHIFT)) & SIUL2_IFER0_IFE12_MASK)

#define SIUL2_IFER0_IFE13_MASK                   (0x2000U)
#define SIUL2_IFER0_IFE13_SHIFT                  (13U)
#define SIUL2_IFER0_IFE13_WIDTH                  (1U)
#define SIUL2_IFER0_IFE13(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE13_SHIFT)) & SIUL2_IFER0_IFE13_MASK)

#define SIUL2_IFER0_IFE14_MASK                   (0x4000U)
#define SIUL2_IFER0_IFE14_SHIFT                  (14U)
#define SIUL2_IFER0_IFE14_WIDTH                  (1U)
#define SIUL2_IFER0_IFE14(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE14_SHIFT)) & SIUL2_IFER0_IFE14_MASK)

#define SIUL2_IFER0_IFE15_MASK                   (0x8000U)
#define SIUL2_IFER0_IFE15_SHIFT                  (15U)
#define SIUL2_IFER0_IFE15_WIDTH                  (1U)
#define SIUL2_IFER0_IFE15(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE15_SHIFT)) & SIUL2_IFER0_IFE15_MASK)

#define SIUL2_IFER0_IFE16_MASK                   (0x10000U)
#define SIUL2_IFER0_IFE16_SHIFT                  (16U)
#define SIUL2_IFER0_IFE16_WIDTH                  (1U)
#define SIUL2_IFER0_IFE16(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE16_SHIFT)) & SIUL2_IFER0_IFE16_MASK)

#define SIUL2_IFER0_IFE17_MASK                   (0x20000U)
#define SIUL2_IFER0_IFE17_SHIFT                  (17U)
#define SIUL2_IFER0_IFE17_WIDTH                  (1U)
#define SIUL2_IFER0_IFE17(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE17_SHIFT)) & SIUL2_IFER0_IFE17_MASK)

#define SIUL2_IFER0_IFE18_MASK                   (0x40000U)
#define SIUL2_IFER0_IFE18_SHIFT                  (18U)
#define SIUL2_IFER0_IFE18_WIDTH                  (1U)
#define SIUL2_IFER0_IFE18(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE18_SHIFT)) & SIUL2_IFER0_IFE18_MASK)

#define SIUL2_IFER0_IFE19_MASK                   (0x80000U)
#define SIUL2_IFER0_IFE19_SHIFT                  (19U)
#define SIUL2_IFER0_IFE19_WIDTH                  (1U)
#define SIUL2_IFER0_IFE19(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE19_SHIFT)) & SIUL2_IFER0_IFE19_MASK)

#define SIUL2_IFER0_IFE20_MASK                   (0x100000U)
#define SIUL2_IFER0_IFE20_SHIFT                  (20U)
#define SIUL2_IFER0_IFE20_WIDTH                  (1U)
#define SIUL2_IFER0_IFE20(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE20_SHIFT)) & SIUL2_IFER0_IFE20_MASK)

#define SIUL2_IFER0_IFE21_MASK                   (0x200000U)
#define SIUL2_IFER0_IFE21_SHIFT                  (21U)
#define SIUL2_IFER0_IFE21_WIDTH                  (1U)
#define SIUL2_IFER0_IFE21(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE21_SHIFT)) & SIUL2_IFER0_IFE21_MASK)

#define SIUL2_IFER0_IFE22_MASK                   (0x400000U)
#define SIUL2_IFER0_IFE22_SHIFT                  (22U)
#define SIUL2_IFER0_IFE22_WIDTH                  (1U)
#define SIUL2_IFER0_IFE22(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE22_SHIFT)) & SIUL2_IFER0_IFE22_MASK)

#define SIUL2_IFER0_IFE23_MASK                   (0x800000U)
#define SIUL2_IFER0_IFE23_SHIFT                  (23U)
#define SIUL2_IFER0_IFE23_WIDTH                  (1U)
#define SIUL2_IFER0_IFE23(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE23_SHIFT)) & SIUL2_IFER0_IFE23_MASK)

#define SIUL2_IFER0_IFE24_MASK                   (0x1000000U)
#define SIUL2_IFER0_IFE24_SHIFT                  (24U)
#define SIUL2_IFER0_IFE24_WIDTH                  (1U)
#define SIUL2_IFER0_IFE24(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE24_SHIFT)) & SIUL2_IFER0_IFE24_MASK)

#define SIUL2_IFER0_IFE25_MASK                   (0x2000000U)
#define SIUL2_IFER0_IFE25_SHIFT                  (25U)
#define SIUL2_IFER0_IFE25_WIDTH                  (1U)
#define SIUL2_IFER0_IFE25(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE25_SHIFT)) & SIUL2_IFER0_IFE25_MASK)

#define SIUL2_IFER0_IFE26_MASK                   (0x4000000U)
#define SIUL2_IFER0_IFE26_SHIFT                  (26U)
#define SIUL2_IFER0_IFE26_WIDTH                  (1U)
#define SIUL2_IFER0_IFE26(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE26_SHIFT)) & SIUL2_IFER0_IFE26_MASK)

#define SIUL2_IFER0_IFE27_MASK                   (0x8000000U)
#define SIUL2_IFER0_IFE27_SHIFT                  (27U)
#define SIUL2_IFER0_IFE27_WIDTH                  (1U)
#define SIUL2_IFER0_IFE27(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE27_SHIFT)) & SIUL2_IFER0_IFE27_MASK)

#define SIUL2_IFER0_IFE28_MASK                   (0x10000000U)
#define SIUL2_IFER0_IFE28_SHIFT                  (28U)
#define SIUL2_IFER0_IFE28_WIDTH                  (1U)
#define SIUL2_IFER0_IFE28(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE28_SHIFT)) & SIUL2_IFER0_IFE28_MASK)

#define SIUL2_IFER0_IFE29_MASK                   (0x20000000U)
#define SIUL2_IFER0_IFE29_SHIFT                  (29U)
#define SIUL2_IFER0_IFE29_WIDTH                  (1U)
#define SIUL2_IFER0_IFE29(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE29_SHIFT)) & SIUL2_IFER0_IFE29_MASK)

#define SIUL2_IFER0_IFE30_MASK                   (0x40000000U)
#define SIUL2_IFER0_IFE30_SHIFT                  (30U)
#define SIUL2_IFER0_IFE30_WIDTH                  (1U)
#define SIUL2_IFER0_IFE30(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE30_SHIFT)) & SIUL2_IFER0_IFE30_MASK)

#define SIUL2_IFER0_IFE31_MASK                   (0x80000000U)
#define SIUL2_IFER0_IFE31_SHIFT                  (31U)
#define SIUL2_IFER0_IFE31_WIDTH                  (1U)
#define SIUL2_IFER0_IFE31(x)                     (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE31_SHIFT)) & SIUL2_IFER0_IFE31_MASK)
/*! @} */

/*! @name IFMCR - SIUL2 Interrupt Filter Maximum Counter Register */
/*! @{ */

#define SIUL2_IFMCR_MAXCNT_MASK                  (0xFU)
#define SIUL2_IFMCR_MAXCNT_SHIFT                 (0U)
#define SIUL2_IFMCR_MAXCNT_WIDTH                 (4U)
#define SIUL2_IFMCR_MAXCNT(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFMCR_MAXCNT_SHIFT)) & SIUL2_IFMCR_MAXCNT_MASK)
/*! @} */

/*! @name IFCPR - SIUL2 Interrupt Filter Clock Prescaler Register */
/*! @{ */

#define SIUL2_IFCPR_IFCP_MASK                    (0xFU)
#define SIUL2_IFCPR_IFCP_SHIFT                   (0U)
#define SIUL2_IFCPR_IFCP_WIDTH                   (4U)
#define SIUL2_IFCPR_IFCP(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_IFCPR_IFCP_SHIFT)) & SIUL2_IFCPR_IFCP_MASK)
/*! @} */

/*! @name MIDR3 - SIUL2 MCU ID Register #3 */
/*! @{ */

#define SIUL2_MIDR3_SYS_RAM_SIZE_MASK            (0x3FU)
#define SIUL2_MIDR3_SYS_RAM_SIZE_SHIFT           (0U)
#define SIUL2_MIDR3_SYS_RAM_SIZE_WIDTH           (6U)
#define SIUL2_MIDR3_SYS_RAM_SIZE(x)              (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_SYS_RAM_SIZE_SHIFT)) & SIUL2_MIDR3_SYS_RAM_SIZE_MASK)

#define SIUL2_MIDR3_PART_NO_SUF_MASK             (0xFC00U)
#define SIUL2_MIDR3_PART_NO_SUF_SHIFT            (10U)
#define SIUL2_MIDR3_PART_NO_SUF_WIDTH            (6U)
#define SIUL2_MIDR3_PART_NO_SUF(x)               (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_PART_NO_SUF_SHIFT)) & SIUL2_MIDR3_PART_NO_SUF_MASK)

#define SIUL2_MIDR3_PROD_FAM_NO_MASK             (0x3FF0000U)
#define SIUL2_MIDR3_PROD_FAM_NO_SHIFT            (16U)
#define SIUL2_MIDR3_PROD_FAM_NO_WIDTH            (10U)
#define SIUL2_MIDR3_PROD_FAM_NO(x)               (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_PROD_FAM_NO_SHIFT)) & SIUL2_MIDR3_PROD_FAM_NO_MASK)

#define SIUL2_MIDR3_PROD_FAM_LET_MASK            (0xFC000000U)
#define SIUL2_MIDR3_PROD_FAM_LET_SHIFT           (26U)
#define SIUL2_MIDR3_PROD_FAM_LET_WIDTH           (6U)
#define SIUL2_MIDR3_PROD_FAM_LET(x)              (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_PROD_FAM_LET_SHIFT)) & SIUL2_MIDR3_PROD_FAM_LET_MASK)
/*! @} */

/*! @name MIDR4 - SIUL2 MCU ID Register #4 */
/*! @{ */

#define SIUL2_MIDR4_CORE_PLAT_FET_MASK           (0x7U)
#define SIUL2_MIDR4_CORE_PLAT_FET_SHIFT          (0U)
#define SIUL2_MIDR4_CORE_PLAT_FET_WIDTH          (3U)
#define SIUL2_MIDR4_CORE_PLAT_FET(x)             (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_CORE_PLAT_FET_SHIFT)) & SIUL2_MIDR4_CORE_PLAT_FET_MASK)

#define SIUL2_MIDR4_EMAC_FET_MASK                (0x18U)
#define SIUL2_MIDR4_EMAC_FET_SHIFT               (3U)
#define SIUL2_MIDR4_EMAC_FET_WIDTH               (2U)
#define SIUL2_MIDR4_EMAC_FET(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_EMAC_FET_SHIFT)) & SIUL2_MIDR4_EMAC_FET_MASK)

#define SIUL2_MIDR4_SEC_FET_MASK                 (0x60U)
#define SIUL2_MIDR4_SEC_FET_SHIFT                (5U)
#define SIUL2_MIDR4_SEC_FET_WIDTH                (2U)
#define SIUL2_MIDR4_SEC_FET(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_SEC_FET_SHIFT)) & SIUL2_MIDR4_SEC_FET_MASK)
/*! @} */

/*! @name MSCR - SIUL2 Multiplexed Signal Configuration Register */
/*! @{ */

#define SIUL2_MSCR_SSS_0_MASK                    (0x1U)
#define SIUL2_MSCR_SSS_0_SHIFT                   (0U)
#define SIUL2_MSCR_SSS_0_WIDTH                   (1U)
#define SIUL2_MSCR_SSS_0(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SSS_0_SHIFT)) & SIUL2_MSCR_SSS_0_MASK)

#define SIUL2_MSCR_SSS_1_MASK                    (0x2U)
#define SIUL2_MSCR_SSS_1_SHIFT                   (1U)
#define SIUL2_MSCR_SSS_1_WIDTH                   (1U)
#define SIUL2_MSCR_SSS_1(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SSS_1_SHIFT)) & SIUL2_MSCR_SSS_1_MASK)

#define SIUL2_MSCR_SSS_2_MASK                    (0x4U)
#define SIUL2_MSCR_SSS_2_SHIFT                   (2U)
#define SIUL2_MSCR_SSS_2_WIDTH                   (1U)
#define SIUL2_MSCR_SSS_2(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SSS_2_SHIFT)) & SIUL2_MSCR_SSS_2_MASK)

#define SIUL2_MSCR_SSS_3_MASK                    (0x8U)
#define SIUL2_MSCR_SSS_3_SHIFT                   (3U)
#define SIUL2_MSCR_SSS_3_WIDTH                   (1U)
#define SIUL2_MSCR_SSS_3(x)                      (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SSS_3_SHIFT)) & SIUL2_MSCR_SSS_3_MASK)

#define SIUL2_MSCR_SMC_MASK                      (0x20U)
#define SIUL2_MSCR_SMC_SHIFT                     (5U)
#define SIUL2_MSCR_SMC_WIDTH                     (1U)
#define SIUL2_MSCR_SMC(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SMC_SHIFT)) & SIUL2_MSCR_SMC_MASK)

#define SIUL2_MSCR_IFE_MASK                      (0x40U)
#define SIUL2_MSCR_IFE_SHIFT                     (6U)
#define SIUL2_MSCR_IFE_WIDTH                     (1U)
#define SIUL2_MSCR_IFE(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_IFE_SHIFT)) & SIUL2_MSCR_IFE_MASK)

#define SIUL2_MSCR_DSE_MASK                      (0x100U)
#define SIUL2_MSCR_DSE_SHIFT                     (8U)
#define SIUL2_MSCR_DSE_WIDTH                     (1U)
#define SIUL2_MSCR_DSE(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_DSE_SHIFT)) & SIUL2_MSCR_DSE_MASK)

#define SIUL2_MSCR_PUS_MASK                      (0x800U)
#define SIUL2_MSCR_PUS_SHIFT                     (11U)
#define SIUL2_MSCR_PUS_WIDTH                     (1U)
#define SIUL2_MSCR_PUS(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_PUS_SHIFT)) & SIUL2_MSCR_PUS_MASK)

#define SIUL2_MSCR_PUE_MASK                      (0x2000U)
#define SIUL2_MSCR_PUE_SHIFT                     (13U)
#define SIUL2_MSCR_PUE_WIDTH                     (1U)
#define SIUL2_MSCR_PUE(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_PUE_SHIFT)) & SIUL2_MSCR_PUE_MASK)

#define SIUL2_MSCR_SRC_MASK                      (0x4000U)
#define SIUL2_MSCR_SRC_SHIFT                     (14U)
#define SIUL2_MSCR_SRC_WIDTH                     (1U)
#define SIUL2_MSCR_SRC(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SRC_SHIFT)) & SIUL2_MSCR_SRC_MASK)

#define SIUL2_MSCR_PKE_MASK                      (0x10000U)
#define SIUL2_MSCR_PKE_SHIFT                     (16U)
#define SIUL2_MSCR_PKE_WIDTH                     (1U)
#define SIUL2_MSCR_PKE(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_PKE_SHIFT)) & SIUL2_MSCR_PKE_MASK)

#define SIUL2_MSCR_INV_MASK                      (0x20000U)
#define SIUL2_MSCR_INV_SHIFT                     (17U)
#define SIUL2_MSCR_INV_WIDTH                     (1U)
#define SIUL2_MSCR_INV(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_INV_SHIFT)) & SIUL2_MSCR_INV_MASK)

#define SIUL2_MSCR_IBE_MASK                      (0x80000U)
#define SIUL2_MSCR_IBE_SHIFT                     (19U)
#define SIUL2_MSCR_IBE_WIDTH                     (1U)
#define SIUL2_MSCR_IBE(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_IBE_SHIFT)) & SIUL2_MSCR_IBE_MASK)

#define SIUL2_MSCR_OBE_MASK                      (0x200000U)
#define SIUL2_MSCR_OBE_SHIFT                     (21U)
#define SIUL2_MSCR_OBE_WIDTH                     (1U)
#define SIUL2_MSCR_OBE(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_OBE_SHIFT)) & SIUL2_MSCR_OBE_MASK)
/*! @} */

/*! @name IMCR - SIUL2 Input Multiplexed Signal Configuration Register */
/*! @{ */

#define SIUL2_IMCR_SSS_MASK                      (0xFU)
#define SIUL2_IMCR_SSS_SHIFT                     (0U)
#define SIUL2_IMCR_SSS_WIDTH                     (4U)
#define SIUL2_IMCR_SSS(x)                        (((uint32_t)(((uint32_t)(x)) << SIUL2_IMCR_SSS_SHIFT)) & SIUL2_IMCR_SSS_MASK)
/*! @} */

/*! @name GPDO3 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO3_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO3_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO3_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO3_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO3_PDO_n_SHIFT)) & SIUL2_GPDO3_PDO_n_MASK)
/*! @} */

/*! @name GPDO2 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO2_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO2_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO2_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO2_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO2_PDO_n_SHIFT)) & SIUL2_GPDO2_PDO_n_MASK)
/*! @} */

/*! @name GPDO1 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO1_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO1_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO1_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO1_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO1_PDO_n_SHIFT)) & SIUL2_GPDO1_PDO_n_MASK)
/*! @} */

/*! @name GPDO0 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO0_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO0_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO0_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO0_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO0_PDO_n_SHIFT)) & SIUL2_GPDO0_PDO_n_MASK)
/*! @} */

/*! @name GPDO7 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO7_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO7_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO7_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO7_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO7_PDO_n_SHIFT)) & SIUL2_GPDO7_PDO_n_MASK)
/*! @} */

/*! @name GPDO6 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO6_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO6_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO6_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO6_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO6_PDO_n_SHIFT)) & SIUL2_GPDO6_PDO_n_MASK)
/*! @} */

/*! @name GPDO5 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO5_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO5_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO5_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO5_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO5_PDO_n_SHIFT)) & SIUL2_GPDO5_PDO_n_MASK)
/*! @} */

/*! @name GPDO4 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO4_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO4_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO4_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO4_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO4_PDO_n_SHIFT)) & SIUL2_GPDO4_PDO_n_MASK)
/*! @} */

/*! @name GPDO11 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO11_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO11_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO11_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO11_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO11_PDO_n_SHIFT)) & SIUL2_GPDO11_PDO_n_MASK)
/*! @} */

/*! @name GPDO10 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO10_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO10_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO10_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO10_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO10_PDO_n_SHIFT)) & SIUL2_GPDO10_PDO_n_MASK)
/*! @} */

/*! @name GPDO9 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO9_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO9_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO9_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO9_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO9_PDO_n_SHIFT)) & SIUL2_GPDO9_PDO_n_MASK)
/*! @} */

/*! @name GPDO8 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO8_PDO_n_MASK                   (0x1U)
#define SIUL2_GPDO8_PDO_n_SHIFT                  (0U)
#define SIUL2_GPDO8_PDO_n_WIDTH                  (1U)
#define SIUL2_GPDO8_PDO_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO8_PDO_n_SHIFT)) & SIUL2_GPDO8_PDO_n_MASK)
/*! @} */

/*! @name GPDO15 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO15_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO15_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO15_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO15_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO15_PDO_n_SHIFT)) & SIUL2_GPDO15_PDO_n_MASK)
/*! @} */

/*! @name GPDO14 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO14_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO14_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO14_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO14_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO14_PDO_n_SHIFT)) & SIUL2_GPDO14_PDO_n_MASK)
/*! @} */

/*! @name GPDO13 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO13_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO13_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO13_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO13_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO13_PDO_n_SHIFT)) & SIUL2_GPDO13_PDO_n_MASK)
/*! @} */

/*! @name GPDO12 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO12_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO12_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO12_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO12_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO12_PDO_n_SHIFT)) & SIUL2_GPDO12_PDO_n_MASK)
/*! @} */

/*! @name GPDO19 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO19_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO19_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO19_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO19_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO19_PDO_n_SHIFT)) & SIUL2_GPDO19_PDO_n_MASK)
/*! @} */

/*! @name GPDO18 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO18_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO18_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO18_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO18_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO18_PDO_n_SHIFT)) & SIUL2_GPDO18_PDO_n_MASK)
/*! @} */

/*! @name GPDO17 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO17_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO17_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO17_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO17_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO17_PDO_n_SHIFT)) & SIUL2_GPDO17_PDO_n_MASK)
/*! @} */

/*! @name GPDO16 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO16_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO16_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO16_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO16_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO16_PDO_n_SHIFT)) & SIUL2_GPDO16_PDO_n_MASK)
/*! @} */

/*! @name GPDO23 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO23_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO23_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO23_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO23_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO23_PDO_n_SHIFT)) & SIUL2_GPDO23_PDO_n_MASK)
/*! @} */

/*! @name GPDO22 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO22_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO22_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO22_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO22_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO22_PDO_n_SHIFT)) & SIUL2_GPDO22_PDO_n_MASK)
/*! @} */

/*! @name GPDO21 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO21_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO21_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO21_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO21_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO21_PDO_n_SHIFT)) & SIUL2_GPDO21_PDO_n_MASK)
/*! @} */

/*! @name GPDO20 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO20_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO20_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO20_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO20_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO20_PDO_n_SHIFT)) & SIUL2_GPDO20_PDO_n_MASK)
/*! @} */

/*! @name GPDO27 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO27_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO27_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO27_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO27_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO27_PDO_n_SHIFT)) & SIUL2_GPDO27_PDO_n_MASK)
/*! @} */

/*! @name GPDO26 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO26_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO26_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO26_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO26_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO26_PDO_n_SHIFT)) & SIUL2_GPDO26_PDO_n_MASK)
/*! @} */

/*! @name GPDO25 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO25_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO25_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO25_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO25_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO25_PDO_n_SHIFT)) & SIUL2_GPDO25_PDO_n_MASK)
/*! @} */

/*! @name GPDO24 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO24_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO24_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO24_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO24_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO24_PDO_n_SHIFT)) & SIUL2_GPDO24_PDO_n_MASK)
/*! @} */

/*! @name GPDO31 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO31_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO31_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO31_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO31_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO31_PDO_n_SHIFT)) & SIUL2_GPDO31_PDO_n_MASK)
/*! @} */

/*! @name GPDO30 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO30_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO30_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO30_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO30_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO30_PDO_n_SHIFT)) & SIUL2_GPDO30_PDO_n_MASK)
/*! @} */

/*! @name GPDO29 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO29_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO29_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO29_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO29_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO29_PDO_n_SHIFT)) & SIUL2_GPDO29_PDO_n_MASK)
/*! @} */

/*! @name GPDO28 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO28_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO28_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO28_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO28_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO28_PDO_n_SHIFT)) & SIUL2_GPDO28_PDO_n_MASK)
/*! @} */

/*! @name GPDO35 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO35_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO35_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO35_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO35_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO35_PDO_n_SHIFT)) & SIUL2_GPDO35_PDO_n_MASK)
/*! @} */

/*! @name GPDO34 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO34_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO34_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO34_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO34_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO34_PDO_n_SHIFT)) & SIUL2_GPDO34_PDO_n_MASK)
/*! @} */

/*! @name GPDO33 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO33_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO33_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO33_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO33_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO33_PDO_n_SHIFT)) & SIUL2_GPDO33_PDO_n_MASK)
/*! @} */

/*! @name GPDO32 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO32_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO32_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO32_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO32_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO32_PDO_n_SHIFT)) & SIUL2_GPDO32_PDO_n_MASK)
/*! @} */

/*! @name GPDO37 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO37_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO37_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO37_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO37_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO37_PDO_n_SHIFT)) & SIUL2_GPDO37_PDO_n_MASK)
/*! @} */

/*! @name GPDO36 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO36_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO36_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO36_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO36_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO36_PDO_n_SHIFT)) & SIUL2_GPDO36_PDO_n_MASK)
/*! @} */

/*! @name GPDO43 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO43_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO43_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO43_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO43_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO43_PDO_n_SHIFT)) & SIUL2_GPDO43_PDO_n_MASK)
/*! @} */

/*! @name GPDO42 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO42_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO42_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO42_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO42_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO42_PDO_n_SHIFT)) & SIUL2_GPDO42_PDO_n_MASK)
/*! @} */

/*! @name GPDO41 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO41_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO41_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO41_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO41_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO41_PDO_n_SHIFT)) & SIUL2_GPDO41_PDO_n_MASK)
/*! @} */

/*! @name GPDO40 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO40_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO40_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO40_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO40_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO40_PDO_n_SHIFT)) & SIUL2_GPDO40_PDO_n_MASK)
/*! @} */

/*! @name GPDO47 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO47_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO47_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO47_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO47_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO47_PDO_n_SHIFT)) & SIUL2_GPDO47_PDO_n_MASK)
/*! @} */

/*! @name GPDO46 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO46_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO46_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO46_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO46_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO46_PDO_n_SHIFT)) & SIUL2_GPDO46_PDO_n_MASK)
/*! @} */

/*! @name GPDO45 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO45_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO45_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO45_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO45_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO45_PDO_n_SHIFT)) & SIUL2_GPDO45_PDO_n_MASK)
/*! @} */

/*! @name GPDO44 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO44_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO44_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO44_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO44_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO44_PDO_n_SHIFT)) & SIUL2_GPDO44_PDO_n_MASK)
/*! @} */

/*! @name GPDO51 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO51_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO51_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO51_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO51_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO51_PDO_n_SHIFT)) & SIUL2_GPDO51_PDO_n_MASK)
/*! @} */

/*! @name GPDO50 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO50_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO50_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO50_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO50_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO50_PDO_n_SHIFT)) & SIUL2_GPDO50_PDO_n_MASK)
/*! @} */

/*! @name GPDO49 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO49_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO49_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO49_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO49_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO49_PDO_n_SHIFT)) & SIUL2_GPDO49_PDO_n_MASK)
/*! @} */

/*! @name GPDO48 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO48_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO48_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO48_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO48_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO48_PDO_n_SHIFT)) & SIUL2_GPDO48_PDO_n_MASK)
/*! @} */

/*! @name GPDO55 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO55_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO55_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO55_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO55_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO55_PDO_n_SHIFT)) & SIUL2_GPDO55_PDO_n_MASK)
/*! @} */

/*! @name GPDO54 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO54_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO54_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO54_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO54_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO54_PDO_n_SHIFT)) & SIUL2_GPDO54_PDO_n_MASK)
/*! @} */

/*! @name GPDO53 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO53_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO53_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO53_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO53_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO53_PDO_n_SHIFT)) & SIUL2_GPDO53_PDO_n_MASK)
/*! @} */

/*! @name GPDO52 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO52_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO52_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO52_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO52_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO52_PDO_n_SHIFT)) & SIUL2_GPDO52_PDO_n_MASK)
/*! @} */

/*! @name GPDO59 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO59_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO59_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO59_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO59_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO59_PDO_n_SHIFT)) & SIUL2_GPDO59_PDO_n_MASK)
/*! @} */

/*! @name GPDO58 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO58_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO58_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO58_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO58_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO58_PDO_n_SHIFT)) & SIUL2_GPDO58_PDO_n_MASK)
/*! @} */

/*! @name GPDO57 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO57_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO57_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO57_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO57_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO57_PDO_n_SHIFT)) & SIUL2_GPDO57_PDO_n_MASK)
/*! @} */

/*! @name GPDO56 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO56_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO56_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO56_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO56_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO56_PDO_n_SHIFT)) & SIUL2_GPDO56_PDO_n_MASK)
/*! @} */

/*! @name GPDO63 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO63_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO63_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO63_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO63_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO63_PDO_n_SHIFT)) & SIUL2_GPDO63_PDO_n_MASK)
/*! @} */

/*! @name GPDO62 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO62_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO62_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO62_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO62_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO62_PDO_n_SHIFT)) & SIUL2_GPDO62_PDO_n_MASK)
/*! @} */

/*! @name GPDO61 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO61_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO61_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO61_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO61_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO61_PDO_n_SHIFT)) & SIUL2_GPDO61_PDO_n_MASK)
/*! @} */

/*! @name GPDO60 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO60_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO60_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO60_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO60_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO60_PDO_n_SHIFT)) & SIUL2_GPDO60_PDO_n_MASK)
/*! @} */

/*! @name GPDO67 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO67_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO67_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO67_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO67_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO67_PDO_n_SHIFT)) & SIUL2_GPDO67_PDO_n_MASK)
/*! @} */

/*! @name GPDO66 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO66_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO66_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO66_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO66_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO66_PDO_n_SHIFT)) & SIUL2_GPDO66_PDO_n_MASK)
/*! @} */

/*! @name GPDO65 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO65_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO65_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO65_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO65_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO65_PDO_n_SHIFT)) & SIUL2_GPDO65_PDO_n_MASK)
/*! @} */

/*! @name GPDO64 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO64_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO64_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO64_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO64_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO64_PDO_n_SHIFT)) & SIUL2_GPDO64_PDO_n_MASK)
/*! @} */

/*! @name GPDO71 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO71_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO71_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO71_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO71_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO71_PDO_n_SHIFT)) & SIUL2_GPDO71_PDO_n_MASK)
/*! @} */

/*! @name GPDO70 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO70_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO70_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO70_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO70_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO70_PDO_n_SHIFT)) & SIUL2_GPDO70_PDO_n_MASK)
/*! @} */

/*! @name GPDO69 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO69_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO69_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO69_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO69_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO69_PDO_n_SHIFT)) & SIUL2_GPDO69_PDO_n_MASK)
/*! @} */

/*! @name GPDO68 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO68_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO68_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO68_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO68_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO68_PDO_n_SHIFT)) & SIUL2_GPDO68_PDO_n_MASK)
/*! @} */

/*! @name GPDO75 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO75_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO75_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO75_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO75_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO75_PDO_n_SHIFT)) & SIUL2_GPDO75_PDO_n_MASK)
/*! @} */

/*! @name GPDO74 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO74_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO74_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO74_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO74_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO74_PDO_n_SHIFT)) & SIUL2_GPDO74_PDO_n_MASK)
/*! @} */

/*! @name GPDO73 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO73_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO73_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO73_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO73_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO73_PDO_n_SHIFT)) & SIUL2_GPDO73_PDO_n_MASK)
/*! @} */

/*! @name GPDO72 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO72_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO72_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO72_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO72_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO72_PDO_n_SHIFT)) & SIUL2_GPDO72_PDO_n_MASK)
/*! @} */

/*! @name GPDO79 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO79_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO79_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO79_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO79_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO79_PDO_n_SHIFT)) & SIUL2_GPDO79_PDO_n_MASK)
/*! @} */

/*! @name GPDO78 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO78_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO78_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO78_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO78_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO78_PDO_n_SHIFT)) & SIUL2_GPDO78_PDO_n_MASK)
/*! @} */

/*! @name GPDO77 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO77_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO77_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO77_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO77_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO77_PDO_n_SHIFT)) & SIUL2_GPDO77_PDO_n_MASK)
/*! @} */

/*! @name GPDO76 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO76_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO76_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO76_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO76_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO76_PDO_n_SHIFT)) & SIUL2_GPDO76_PDO_n_MASK)
/*! @} */

/*! @name GPDO83 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO83_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO83_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO83_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO83_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO83_PDO_n_SHIFT)) & SIUL2_GPDO83_PDO_n_MASK)
/*! @} */

/*! @name GPDO82 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO82_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO82_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO82_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO82_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO82_PDO_n_SHIFT)) & SIUL2_GPDO82_PDO_n_MASK)
/*! @} */

/*! @name GPDO81 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO81_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO81_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO81_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO81_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO81_PDO_n_SHIFT)) & SIUL2_GPDO81_PDO_n_MASK)
/*! @} */

/*! @name GPDO80 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO80_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO80_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO80_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO80_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO80_PDO_n_SHIFT)) & SIUL2_GPDO80_PDO_n_MASK)
/*! @} */

/*! @name GPDO87 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO87_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO87_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO87_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO87_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO87_PDO_n_SHIFT)) & SIUL2_GPDO87_PDO_n_MASK)
/*! @} */

/*! @name GPDO86 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO86_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO86_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO86_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO86_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO86_PDO_n_SHIFT)) & SIUL2_GPDO86_PDO_n_MASK)
/*! @} */

/*! @name GPDO85 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO85_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO85_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO85_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO85_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO85_PDO_n_SHIFT)) & SIUL2_GPDO85_PDO_n_MASK)
/*! @} */

/*! @name GPDO84 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO84_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO84_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO84_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO84_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO84_PDO_n_SHIFT)) & SIUL2_GPDO84_PDO_n_MASK)
/*! @} */

/*! @name GPDO91 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO91_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO91_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO91_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO91_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO91_PDO_n_SHIFT)) & SIUL2_GPDO91_PDO_n_MASK)
/*! @} */

/*! @name GPDO90 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO90_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO90_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO90_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO90_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO90_PDO_n_SHIFT)) & SIUL2_GPDO90_PDO_n_MASK)
/*! @} */

/*! @name GPDO89 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO89_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO89_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO89_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO89_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO89_PDO_n_SHIFT)) & SIUL2_GPDO89_PDO_n_MASK)
/*! @} */

/*! @name GPDO88 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO88_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO88_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO88_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO88_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO88_PDO_n_SHIFT)) & SIUL2_GPDO88_PDO_n_MASK)
/*! @} */

/*! @name GPDO95 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO95_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO95_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO95_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO95_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO95_PDO_n_SHIFT)) & SIUL2_GPDO95_PDO_n_MASK)
/*! @} */

/*! @name GPDO94 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO94_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO94_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO94_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO94_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO94_PDO_n_SHIFT)) & SIUL2_GPDO94_PDO_n_MASK)
/*! @} */

/*! @name GPDO93 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO93_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO93_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO93_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO93_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO93_PDO_n_SHIFT)) & SIUL2_GPDO93_PDO_n_MASK)
/*! @} */

/*! @name GPDO92 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO92_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO92_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO92_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO92_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO92_PDO_n_SHIFT)) & SIUL2_GPDO92_PDO_n_MASK)
/*! @} */

/*! @name GPDO99 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO99_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO99_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO99_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO99_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO99_PDO_n_SHIFT)) & SIUL2_GPDO99_PDO_n_MASK)
/*! @} */

/*! @name GPDO98 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO98_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO98_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO98_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO98_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO98_PDO_n_SHIFT)) & SIUL2_GPDO98_PDO_n_MASK)
/*! @} */

/*! @name GPDO97 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO97_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO97_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO97_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO97_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO97_PDO_n_SHIFT)) & SIUL2_GPDO97_PDO_n_MASK)
/*! @} */

/*! @name GPDO96 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO96_PDO_n_MASK                  (0x1U)
#define SIUL2_GPDO96_PDO_n_SHIFT                 (0U)
#define SIUL2_GPDO96_PDO_n_WIDTH                 (1U)
#define SIUL2_GPDO96_PDO_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO96_PDO_n_SHIFT)) & SIUL2_GPDO96_PDO_n_MASK)
/*! @} */

/*! @name GPDO103 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO103_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO103_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO103_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO103_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO103_PDO_n_SHIFT)) & SIUL2_GPDO103_PDO_n_MASK)
/*! @} */

/*! @name GPDO102 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO102_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO102_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO102_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO102_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO102_PDO_n_SHIFT)) & SIUL2_GPDO102_PDO_n_MASK)
/*! @} */

/*! @name GPDO101 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO101_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO101_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO101_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO101_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO101_PDO_n_SHIFT)) & SIUL2_GPDO101_PDO_n_MASK)
/*! @} */

/*! @name GPDO100 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO100_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO100_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO100_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO100_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO100_PDO_n_SHIFT)) & SIUL2_GPDO100_PDO_n_MASK)
/*! @} */

/*! @name GPDO107 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO107_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO107_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO107_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO107_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO107_PDO_n_SHIFT)) & SIUL2_GPDO107_PDO_n_MASK)
/*! @} */

/*! @name GPDO106 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO106_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO106_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO106_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO106_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO106_PDO_n_SHIFT)) & SIUL2_GPDO106_PDO_n_MASK)
/*! @} */

/*! @name GPDO105 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO105_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO105_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO105_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO105_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO105_PDO_n_SHIFT)) & SIUL2_GPDO105_PDO_n_MASK)
/*! @} */

/*! @name GPDO104 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO104_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO104_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO104_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO104_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO104_PDO_n_SHIFT)) & SIUL2_GPDO104_PDO_n_MASK)
/*! @} */

/*! @name GPDO111 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO111_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO111_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO111_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO111_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO111_PDO_n_SHIFT)) & SIUL2_GPDO111_PDO_n_MASK)
/*! @} */

/*! @name GPDO110 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO110_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO110_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO110_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO110_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO110_PDO_n_SHIFT)) & SIUL2_GPDO110_PDO_n_MASK)
/*! @} */

/*! @name GPDO109 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO109_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO109_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO109_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO109_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO109_PDO_n_SHIFT)) & SIUL2_GPDO109_PDO_n_MASK)
/*! @} */

/*! @name GPDO108 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO108_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO108_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO108_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO108_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO108_PDO_n_SHIFT)) & SIUL2_GPDO108_PDO_n_MASK)
/*! @} */

/*! @name GPDO115 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO115_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO115_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO115_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO115_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO115_PDO_n_SHIFT)) & SIUL2_GPDO115_PDO_n_MASK)
/*! @} */

/*! @name GPDO114 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO114_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO114_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO114_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO114_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO114_PDO_n_SHIFT)) & SIUL2_GPDO114_PDO_n_MASK)
/*! @} */

/*! @name GPDO113 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO113_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO113_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO113_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO113_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO113_PDO_n_SHIFT)) & SIUL2_GPDO113_PDO_n_MASK)
/*! @} */

/*! @name GPDO112 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO112_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO112_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO112_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO112_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO112_PDO_n_SHIFT)) & SIUL2_GPDO112_PDO_n_MASK)
/*! @} */

/*! @name GPDO119 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO119_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO119_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO119_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO119_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO119_PDO_n_SHIFT)) & SIUL2_GPDO119_PDO_n_MASK)
/*! @} */

/*! @name GPDO118 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO118_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO118_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO118_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO118_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO118_PDO_n_SHIFT)) & SIUL2_GPDO118_PDO_n_MASK)
/*! @} */

/*! @name GPDO117 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO117_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO117_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO117_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO117_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO117_PDO_n_SHIFT)) & SIUL2_GPDO117_PDO_n_MASK)
/*! @} */

/*! @name GPDO116 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO116_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO116_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO116_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO116_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO116_PDO_n_SHIFT)) & SIUL2_GPDO116_PDO_n_MASK)
/*! @} */

/*! @name GPDO123 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO123_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO123_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO123_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO123_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO123_PDO_n_SHIFT)) & SIUL2_GPDO123_PDO_n_MASK)
/*! @} */

/*! @name GPDO122 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO122_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO122_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO122_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO122_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO122_PDO_n_SHIFT)) & SIUL2_GPDO122_PDO_n_MASK)
/*! @} */

/*! @name GPDO121 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO121_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO121_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO121_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO121_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO121_PDO_n_SHIFT)) & SIUL2_GPDO121_PDO_n_MASK)
/*! @} */

/*! @name GPDO120 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO120_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO120_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO120_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO120_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO120_PDO_n_SHIFT)) & SIUL2_GPDO120_PDO_n_MASK)
/*! @} */

/*! @name GPDO127 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO127_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO127_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO127_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO127_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO127_PDO_n_SHIFT)) & SIUL2_GPDO127_PDO_n_MASK)
/*! @} */

/*! @name GPDO126 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO126_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO126_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO126_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO126_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO126_PDO_n_SHIFT)) & SIUL2_GPDO126_PDO_n_MASK)
/*! @} */

/*! @name GPDO125 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO125_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO125_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO125_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO125_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO125_PDO_n_SHIFT)) & SIUL2_GPDO125_PDO_n_MASK)
/*! @} */

/*! @name GPDO124 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO124_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO124_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO124_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO124_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO124_PDO_n_SHIFT)) & SIUL2_GPDO124_PDO_n_MASK)
/*! @} */

/*! @name GPDO131 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO131_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO131_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO131_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO131_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO131_PDO_n_SHIFT)) & SIUL2_GPDO131_PDO_n_MASK)
/*! @} */

/*! @name GPDO130 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO130_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO130_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO130_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO130_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO130_PDO_n_SHIFT)) & SIUL2_GPDO130_PDO_n_MASK)
/*! @} */

/*! @name GPDO129 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO129_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO129_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO129_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO129_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO129_PDO_n_SHIFT)) & SIUL2_GPDO129_PDO_n_MASK)
/*! @} */

/*! @name GPDO128 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO128_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO128_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO128_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO128_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO128_PDO_n_SHIFT)) & SIUL2_GPDO128_PDO_n_MASK)
/*! @} */

/*! @name GPDO135 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO135_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO135_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO135_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO135_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO135_PDO_n_SHIFT)) & SIUL2_GPDO135_PDO_n_MASK)
/*! @} */

/*! @name GPDO134 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO134_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO134_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO134_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO134_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO134_PDO_n_SHIFT)) & SIUL2_GPDO134_PDO_n_MASK)
/*! @} */

/*! @name GPDO133 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO133_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO133_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO133_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO133_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO133_PDO_n_SHIFT)) & SIUL2_GPDO133_PDO_n_MASK)
/*! @} */

/*! @name GPDO132 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO132_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO132_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO132_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO132_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO132_PDO_n_SHIFT)) & SIUL2_GPDO132_PDO_n_MASK)
/*! @} */

/*! @name GPDO139 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO139_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO139_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO139_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO139_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO139_PDO_n_SHIFT)) & SIUL2_GPDO139_PDO_n_MASK)
/*! @} */

/*! @name GPDO138 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO138_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO138_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO138_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO138_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO138_PDO_n_SHIFT)) & SIUL2_GPDO138_PDO_n_MASK)
/*! @} */

/*! @name GPDO137 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO137_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO137_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO137_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO137_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO137_PDO_n_SHIFT)) & SIUL2_GPDO137_PDO_n_MASK)
/*! @} */

/*! @name GPDO136 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO136_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO136_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO136_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO136_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO136_PDO_n_SHIFT)) & SIUL2_GPDO136_PDO_n_MASK)
/*! @} */

/*! @name GPDO143 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO143_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO143_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO143_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO143_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO143_PDO_n_SHIFT)) & SIUL2_GPDO143_PDO_n_MASK)
/*! @} */

/*! @name GPDO142 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO142_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO142_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO142_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO142_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO142_PDO_n_SHIFT)) & SIUL2_GPDO142_PDO_n_MASK)
/*! @} */

/*! @name GPDO141 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO141_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO141_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO141_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO141_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO141_PDO_n_SHIFT)) & SIUL2_GPDO141_PDO_n_MASK)
/*! @} */

/*! @name GPDO140 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO140_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO140_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO140_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO140_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO140_PDO_n_SHIFT)) & SIUL2_GPDO140_PDO_n_MASK)
/*! @} */

/*! @name GPDO147 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO147_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO147_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO147_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO147_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO147_PDO_n_SHIFT)) & SIUL2_GPDO147_PDO_n_MASK)
/*! @} */

/*! @name GPDO146 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO146_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO146_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO146_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO146_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO146_PDO_n_SHIFT)) & SIUL2_GPDO146_PDO_n_MASK)
/*! @} */

/*! @name GPDO145 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO145_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO145_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO145_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO145_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO145_PDO_n_SHIFT)) & SIUL2_GPDO145_PDO_n_MASK)
/*! @} */

/*! @name GPDO144 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO144_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO144_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO144_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO144_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO144_PDO_n_SHIFT)) & SIUL2_GPDO144_PDO_n_MASK)
/*! @} */

/*! @name GPDO151 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO151_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO151_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO151_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO151_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO151_PDO_n_SHIFT)) & SIUL2_GPDO151_PDO_n_MASK)
/*! @} */

/*! @name GPDO150 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO150_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO150_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO150_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO150_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO150_PDO_n_SHIFT)) & SIUL2_GPDO150_PDO_n_MASK)
/*! @} */

/*! @name GPDO149 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO149_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO149_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO149_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO149_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO149_PDO_n_SHIFT)) & SIUL2_GPDO149_PDO_n_MASK)
/*! @} */

/*! @name GPDO148 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO148_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO148_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO148_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO148_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO148_PDO_n_SHIFT)) & SIUL2_GPDO148_PDO_n_MASK)
/*! @} */

/*! @name GPDO155 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO155_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO155_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO155_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO155_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO155_PDO_n_SHIFT)) & SIUL2_GPDO155_PDO_n_MASK)
/*! @} */

/*! @name GPDO154 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO154_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO154_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO154_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO154_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO154_PDO_n_SHIFT)) & SIUL2_GPDO154_PDO_n_MASK)
/*! @} */

/*! @name GPDO153 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO153_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO153_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO153_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO153_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO153_PDO_n_SHIFT)) & SIUL2_GPDO153_PDO_n_MASK)
/*! @} */

/*! @name GPDO152 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO152_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO152_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO152_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO152_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO152_PDO_n_SHIFT)) & SIUL2_GPDO152_PDO_n_MASK)
/*! @} */

/*! @name GPDO159 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO159_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO159_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO159_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO159_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO159_PDO_n_SHIFT)) & SIUL2_GPDO159_PDO_n_MASK)
/*! @} */

/*! @name GPDO158 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO158_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO158_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO158_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO158_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO158_PDO_n_SHIFT)) & SIUL2_GPDO158_PDO_n_MASK)
/*! @} */

/*! @name GPDO157 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO157_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO157_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO157_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO157_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO157_PDO_n_SHIFT)) & SIUL2_GPDO157_PDO_n_MASK)
/*! @} */

/*! @name GPDO156 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO156_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO156_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO156_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO156_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO156_PDO_n_SHIFT)) & SIUL2_GPDO156_PDO_n_MASK)
/*! @} */

/*! @name GPDO163 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO163_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO163_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO163_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO163_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO163_PDO_n_SHIFT)) & SIUL2_GPDO163_PDO_n_MASK)
/*! @} */

/*! @name GPDO162 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO162_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO162_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO162_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO162_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO162_PDO_n_SHIFT)) & SIUL2_GPDO162_PDO_n_MASK)
/*! @} */

/*! @name GPDO161 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO161_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO161_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO161_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO161_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO161_PDO_n_SHIFT)) & SIUL2_GPDO161_PDO_n_MASK)
/*! @} */

/*! @name GPDO160 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO160_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO160_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO160_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO160_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO160_PDO_n_SHIFT)) & SIUL2_GPDO160_PDO_n_MASK)
/*! @} */

/*! @name GPDO167 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO167_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO167_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO167_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO167_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO167_PDO_n_SHIFT)) & SIUL2_GPDO167_PDO_n_MASK)
/*! @} */

/*! @name GPDO166 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO166_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO166_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO166_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO166_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO166_PDO_n_SHIFT)) & SIUL2_GPDO166_PDO_n_MASK)
/*! @} */

/*! @name GPDO165 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO165_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO165_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO165_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO165_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO165_PDO_n_SHIFT)) & SIUL2_GPDO165_PDO_n_MASK)
/*! @} */

/*! @name GPDO164 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO164_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO164_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO164_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO164_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO164_PDO_n_SHIFT)) & SIUL2_GPDO164_PDO_n_MASK)
/*! @} */

/*! @name GPDO171 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO171_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO171_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO171_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO171_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO171_PDO_n_SHIFT)) & SIUL2_GPDO171_PDO_n_MASK)
/*! @} */

/*! @name GPDO170 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO170_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO170_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO170_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO170_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO170_PDO_n_SHIFT)) & SIUL2_GPDO170_PDO_n_MASK)
/*! @} */

/*! @name GPDO169 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO169_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO169_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO169_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO169_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO169_PDO_n_SHIFT)) & SIUL2_GPDO169_PDO_n_MASK)
/*! @} */

/*! @name GPDO168 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO168_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO168_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO168_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO168_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO168_PDO_n_SHIFT)) & SIUL2_GPDO168_PDO_n_MASK)
/*! @} */

/*! @name GPDO175 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO175_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO175_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO175_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO175_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO175_PDO_n_SHIFT)) & SIUL2_GPDO175_PDO_n_MASK)
/*! @} */

/*! @name GPDO174 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO174_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO174_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO174_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO174_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO174_PDO_n_SHIFT)) & SIUL2_GPDO174_PDO_n_MASK)
/*! @} */

/*! @name GPDO173 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO173_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO173_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO173_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO173_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO173_PDO_n_SHIFT)) & SIUL2_GPDO173_PDO_n_MASK)
/*! @} */

/*! @name GPDO172 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO172_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO172_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO172_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO172_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO172_PDO_n_SHIFT)) & SIUL2_GPDO172_PDO_n_MASK)
/*! @} */

/*! @name GPDO179 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO179_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO179_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO179_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO179_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO179_PDO_n_SHIFT)) & SIUL2_GPDO179_PDO_n_MASK)
/*! @} */

/*! @name GPDO178 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO178_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO178_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO178_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO178_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO178_PDO_n_SHIFT)) & SIUL2_GPDO178_PDO_n_MASK)
/*! @} */

/*! @name GPDO177 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO177_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO177_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO177_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO177_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO177_PDO_n_SHIFT)) & SIUL2_GPDO177_PDO_n_MASK)
/*! @} */

/*! @name GPDO176 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO176_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO176_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO176_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO176_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO176_PDO_n_SHIFT)) & SIUL2_GPDO176_PDO_n_MASK)
/*! @} */

/*! @name GPDO183 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO183_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO183_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO183_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO183_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO183_PDO_n_SHIFT)) & SIUL2_GPDO183_PDO_n_MASK)
/*! @} */

/*! @name GPDO182 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO182_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO182_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO182_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO182_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO182_PDO_n_SHIFT)) & SIUL2_GPDO182_PDO_n_MASK)
/*! @} */

/*! @name GPDO181 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO181_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO181_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO181_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO181_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO181_PDO_n_SHIFT)) & SIUL2_GPDO181_PDO_n_MASK)
/*! @} */

/*! @name GPDO180 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO180_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO180_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO180_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO180_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO180_PDO_n_SHIFT)) & SIUL2_GPDO180_PDO_n_MASK)
/*! @} */

/*! @name GPDO187 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO187_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO187_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO187_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO187_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO187_PDO_n_SHIFT)) & SIUL2_GPDO187_PDO_n_MASK)
/*! @} */

/*! @name GPDO186 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO186_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO186_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO186_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO186_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO186_PDO_n_SHIFT)) & SIUL2_GPDO186_PDO_n_MASK)
/*! @} */

/*! @name GPDO185 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO185_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO185_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO185_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO185_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO185_PDO_n_SHIFT)) & SIUL2_GPDO185_PDO_n_MASK)
/*! @} */

/*! @name GPDO184 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO184_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO184_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO184_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO184_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO184_PDO_n_SHIFT)) & SIUL2_GPDO184_PDO_n_MASK)
/*! @} */

/*! @name GPDO191 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO191_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO191_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO191_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO191_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO191_PDO_n_SHIFT)) & SIUL2_GPDO191_PDO_n_MASK)
/*! @} */

/*! @name GPDO190 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO190_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO190_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO190_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO190_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO190_PDO_n_SHIFT)) & SIUL2_GPDO190_PDO_n_MASK)
/*! @} */

/*! @name GPDO189 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO189_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO189_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO189_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO189_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO189_PDO_n_SHIFT)) & SIUL2_GPDO189_PDO_n_MASK)
/*! @} */

/*! @name GPDO188 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO188_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO188_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO188_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO188_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO188_PDO_n_SHIFT)) & SIUL2_GPDO188_PDO_n_MASK)
/*! @} */

/*! @name GPDO195 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO195_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO195_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO195_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO195_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO195_PDO_n_SHIFT)) & SIUL2_GPDO195_PDO_n_MASK)
/*! @} */

/*! @name GPDO194 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO194_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO194_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO194_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO194_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO194_PDO_n_SHIFT)) & SIUL2_GPDO194_PDO_n_MASK)
/*! @} */

/*! @name GPDO193 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO193_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO193_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO193_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO193_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO193_PDO_n_SHIFT)) & SIUL2_GPDO193_PDO_n_MASK)
/*! @} */

/*! @name GPDO192 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO192_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO192_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO192_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO192_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO192_PDO_n_SHIFT)) & SIUL2_GPDO192_PDO_n_MASK)
/*! @} */

/*! @name GPDO199 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO199_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO199_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO199_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO199_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO199_PDO_n_SHIFT)) & SIUL2_GPDO199_PDO_n_MASK)
/*! @} */

/*! @name GPDO198 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO198_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO198_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO198_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO198_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO198_PDO_n_SHIFT)) & SIUL2_GPDO198_PDO_n_MASK)
/*! @} */

/*! @name GPDO197 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO197_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO197_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO197_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO197_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO197_PDO_n_SHIFT)) & SIUL2_GPDO197_PDO_n_MASK)
/*! @} */

/*! @name GPDO196 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO196_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO196_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO196_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO196_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO196_PDO_n_SHIFT)) & SIUL2_GPDO196_PDO_n_MASK)
/*! @} */

/*! @name GPDO203 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO203_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO203_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO203_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO203_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO203_PDO_n_SHIFT)) & SIUL2_GPDO203_PDO_n_MASK)
/*! @} */

/*! @name GPDO202 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO202_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO202_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO202_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO202_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO202_PDO_n_SHIFT)) & SIUL2_GPDO202_PDO_n_MASK)
/*! @} */

/*! @name GPDO201 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO201_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO201_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO201_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO201_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO201_PDO_n_SHIFT)) & SIUL2_GPDO201_PDO_n_MASK)
/*! @} */

/*! @name GPDO200 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO200_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO200_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO200_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO200_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO200_PDO_n_SHIFT)) & SIUL2_GPDO200_PDO_n_MASK)
/*! @} */

/*! @name GPDO207 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO207_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO207_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO207_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO207_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO207_PDO_n_SHIFT)) & SIUL2_GPDO207_PDO_n_MASK)
/*! @} */

/*! @name GPDO206 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO206_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO206_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO206_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO206_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO206_PDO_n_SHIFT)) & SIUL2_GPDO206_PDO_n_MASK)
/*! @} */

/*! @name GPDO205 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO205_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO205_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO205_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO205_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO205_PDO_n_SHIFT)) & SIUL2_GPDO205_PDO_n_MASK)
/*! @} */

/*! @name GPDO204 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO204_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO204_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO204_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO204_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO204_PDO_n_SHIFT)) & SIUL2_GPDO204_PDO_n_MASK)
/*! @} */

/*! @name GPDO211 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO211_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO211_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO211_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO211_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO211_PDO_n_SHIFT)) & SIUL2_GPDO211_PDO_n_MASK)
/*! @} */

/*! @name GPDO210 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO210_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO210_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO210_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO210_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO210_PDO_n_SHIFT)) & SIUL2_GPDO210_PDO_n_MASK)
/*! @} */

/*! @name GPDO209 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO209_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO209_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO209_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO209_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO209_PDO_n_SHIFT)) & SIUL2_GPDO209_PDO_n_MASK)
/*! @} */

/*! @name GPDO208 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO208_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO208_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO208_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO208_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO208_PDO_n_SHIFT)) & SIUL2_GPDO208_PDO_n_MASK)
/*! @} */

/*! @name GPDO215 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO215_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO215_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO215_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO215_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO215_PDO_n_SHIFT)) & SIUL2_GPDO215_PDO_n_MASK)
/*! @} */

/*! @name GPDO214 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO214_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO214_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO214_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO214_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO214_PDO_n_SHIFT)) & SIUL2_GPDO214_PDO_n_MASK)
/*! @} */

/*! @name GPDO213 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO213_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO213_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO213_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO213_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO213_PDO_n_SHIFT)) & SIUL2_GPDO213_PDO_n_MASK)
/*! @} */

/*! @name GPDO212 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO212_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO212_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO212_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO212_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO212_PDO_n_SHIFT)) & SIUL2_GPDO212_PDO_n_MASK)
/*! @} */

/*! @name GPDO219 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO219_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO219_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO219_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO219_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO219_PDO_n_SHIFT)) & SIUL2_GPDO219_PDO_n_MASK)
/*! @} */

/*! @name GPDO218 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO218_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO218_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO218_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO218_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO218_PDO_n_SHIFT)) & SIUL2_GPDO218_PDO_n_MASK)
/*! @} */

/*! @name GPDO217 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO217_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO217_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO217_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO217_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO217_PDO_n_SHIFT)) & SIUL2_GPDO217_PDO_n_MASK)
/*! @} */

/*! @name GPDO216 - SIUL2 GPIO Pad Data Output Register */
/*! @{ */

#define SIUL2_GPDO216_PDO_n_MASK                 (0x1U)
#define SIUL2_GPDO216_PDO_n_SHIFT                (0U)
#define SIUL2_GPDO216_PDO_n_WIDTH                (1U)
#define SIUL2_GPDO216_PDO_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO216_PDO_n_SHIFT)) & SIUL2_GPDO216_PDO_n_MASK)
/*! @} */

/*! @name GPDI3 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI3_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI3_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI3_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI3_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI3_PDI_n_SHIFT)) & SIUL2_GPDI3_PDI_n_MASK)
/*! @} */

/*! @name GPDI2 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI2_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI2_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI2_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI2_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI2_PDI_n_SHIFT)) & SIUL2_GPDI2_PDI_n_MASK)
/*! @} */

/*! @name GPDI1 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI1_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI1_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI1_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI1_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI1_PDI_n_SHIFT)) & SIUL2_GPDI1_PDI_n_MASK)
/*! @} */

/*! @name GPDI0 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI0_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI0_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI0_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI0_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI0_PDI_n_SHIFT)) & SIUL2_GPDI0_PDI_n_MASK)
/*! @} */

/*! @name GPDI7 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI7_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI7_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI7_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI7_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI7_PDI_n_SHIFT)) & SIUL2_GPDI7_PDI_n_MASK)
/*! @} */

/*! @name GPDI6 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI6_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI6_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI6_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI6_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI6_PDI_n_SHIFT)) & SIUL2_GPDI6_PDI_n_MASK)
/*! @} */

/*! @name GPDI5 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI5_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI5_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI5_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI5_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI5_PDI_n_SHIFT)) & SIUL2_GPDI5_PDI_n_MASK)
/*! @} */

/*! @name GPDI4 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI4_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI4_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI4_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI4_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI4_PDI_n_SHIFT)) & SIUL2_GPDI4_PDI_n_MASK)
/*! @} */

/*! @name GPDI11 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI11_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI11_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI11_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI11_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI11_PDI_n_SHIFT)) & SIUL2_GPDI11_PDI_n_MASK)
/*! @} */

/*! @name GPDI10 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI10_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI10_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI10_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI10_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI10_PDI_n_SHIFT)) & SIUL2_GPDI10_PDI_n_MASK)
/*! @} */

/*! @name GPDI9 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI9_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI9_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI9_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI9_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI9_PDI_n_SHIFT)) & SIUL2_GPDI9_PDI_n_MASK)
/*! @} */

/*! @name GPDI8 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI8_PDI_n_MASK                   (0x1U)
#define SIUL2_GPDI8_PDI_n_SHIFT                  (0U)
#define SIUL2_GPDI8_PDI_n_WIDTH                  (1U)
#define SIUL2_GPDI8_PDI_n(x)                     (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI8_PDI_n_SHIFT)) & SIUL2_GPDI8_PDI_n_MASK)
/*! @} */

/*! @name GPDI15 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI15_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI15_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI15_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI15_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI15_PDI_n_SHIFT)) & SIUL2_GPDI15_PDI_n_MASK)
/*! @} */

/*! @name GPDI14 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI14_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI14_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI14_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI14_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI14_PDI_n_SHIFT)) & SIUL2_GPDI14_PDI_n_MASK)
/*! @} */

/*! @name GPDI13 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI13_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI13_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI13_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI13_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI13_PDI_n_SHIFT)) & SIUL2_GPDI13_PDI_n_MASK)
/*! @} */

/*! @name GPDI12 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI12_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI12_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI12_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI12_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI12_PDI_n_SHIFT)) & SIUL2_GPDI12_PDI_n_MASK)
/*! @} */

/*! @name GPDI19 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI19_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI19_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI19_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI19_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI19_PDI_n_SHIFT)) & SIUL2_GPDI19_PDI_n_MASK)
/*! @} */

/*! @name GPDI18 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI18_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI18_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI18_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI18_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI18_PDI_n_SHIFT)) & SIUL2_GPDI18_PDI_n_MASK)
/*! @} */

/*! @name GPDI17 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI17_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI17_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI17_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI17_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI17_PDI_n_SHIFT)) & SIUL2_GPDI17_PDI_n_MASK)
/*! @} */

/*! @name GPDI16 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI16_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI16_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI16_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI16_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI16_PDI_n_SHIFT)) & SIUL2_GPDI16_PDI_n_MASK)
/*! @} */

/*! @name GPDI23 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI23_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI23_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI23_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI23_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI23_PDI_n_SHIFT)) & SIUL2_GPDI23_PDI_n_MASK)
/*! @} */

/*! @name GPDI22 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI22_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI22_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI22_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI22_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI22_PDI_n_SHIFT)) & SIUL2_GPDI22_PDI_n_MASK)
/*! @} */

/*! @name GPDI21 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI21_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI21_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI21_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI21_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI21_PDI_n_SHIFT)) & SIUL2_GPDI21_PDI_n_MASK)
/*! @} */

/*! @name GPDI20 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI20_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI20_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI20_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI20_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI20_PDI_n_SHIFT)) & SIUL2_GPDI20_PDI_n_MASK)
/*! @} */

/*! @name GPDI27 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI27_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI27_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI27_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI27_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI27_PDI_n_SHIFT)) & SIUL2_GPDI27_PDI_n_MASK)
/*! @} */

/*! @name GPDI26 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI26_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI26_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI26_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI26_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI26_PDI_n_SHIFT)) & SIUL2_GPDI26_PDI_n_MASK)
/*! @} */

/*! @name GPDI25 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI25_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI25_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI25_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI25_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI25_PDI_n_SHIFT)) & SIUL2_GPDI25_PDI_n_MASK)
/*! @} */

/*! @name GPDI24 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI24_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI24_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI24_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI24_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI24_PDI_n_SHIFT)) & SIUL2_GPDI24_PDI_n_MASK)
/*! @} */

/*! @name GPDI31 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI31_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI31_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI31_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI31_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI31_PDI_n_SHIFT)) & SIUL2_GPDI31_PDI_n_MASK)
/*! @} */

/*! @name GPDI30 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI30_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI30_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI30_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI30_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI30_PDI_n_SHIFT)) & SIUL2_GPDI30_PDI_n_MASK)
/*! @} */

/*! @name GPDI29 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI29_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI29_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI29_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI29_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI29_PDI_n_SHIFT)) & SIUL2_GPDI29_PDI_n_MASK)
/*! @} */

/*! @name GPDI28 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI28_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI28_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI28_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI28_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI28_PDI_n_SHIFT)) & SIUL2_GPDI28_PDI_n_MASK)
/*! @} */

/*! @name GPDI35 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI35_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI35_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI35_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI35_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI35_PDI_n_SHIFT)) & SIUL2_GPDI35_PDI_n_MASK)
/*! @} */

/*! @name GPDI34 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI34_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI34_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI34_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI34_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI34_PDI_n_SHIFT)) & SIUL2_GPDI34_PDI_n_MASK)
/*! @} */

/*! @name GPDI33 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI33_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI33_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI33_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI33_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI33_PDI_n_SHIFT)) & SIUL2_GPDI33_PDI_n_MASK)
/*! @} */

/*! @name GPDI32 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI32_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI32_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI32_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI32_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI32_PDI_n_SHIFT)) & SIUL2_GPDI32_PDI_n_MASK)
/*! @} */

/*! @name GPDI37 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI37_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI37_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI37_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI37_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI37_PDI_n_SHIFT)) & SIUL2_GPDI37_PDI_n_MASK)
/*! @} */

/*! @name GPDI36 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI36_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI36_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI36_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI36_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI36_PDI_n_SHIFT)) & SIUL2_GPDI36_PDI_n_MASK)
/*! @} */

/*! @name GPDI43 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI43_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI43_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI43_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI43_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI43_PDI_n_SHIFT)) & SIUL2_GPDI43_PDI_n_MASK)
/*! @} */

/*! @name GPDI42 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI42_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI42_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI42_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI42_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI42_PDI_n_SHIFT)) & SIUL2_GPDI42_PDI_n_MASK)
/*! @} */

/*! @name GPDI41 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI41_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI41_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI41_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI41_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI41_PDI_n_SHIFT)) & SIUL2_GPDI41_PDI_n_MASK)
/*! @} */

/*! @name GPDI40 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI40_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI40_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI40_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI40_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI40_PDI_n_SHIFT)) & SIUL2_GPDI40_PDI_n_MASK)
/*! @} */

/*! @name GPDI47 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI47_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI47_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI47_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI47_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI47_PDI_n_SHIFT)) & SIUL2_GPDI47_PDI_n_MASK)
/*! @} */

/*! @name GPDI46 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI46_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI46_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI46_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI46_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI46_PDI_n_SHIFT)) & SIUL2_GPDI46_PDI_n_MASK)
/*! @} */

/*! @name GPDI45 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI45_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI45_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI45_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI45_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI45_PDI_n_SHIFT)) & SIUL2_GPDI45_PDI_n_MASK)
/*! @} */

/*! @name GPDI44 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI44_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI44_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI44_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI44_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI44_PDI_n_SHIFT)) & SIUL2_GPDI44_PDI_n_MASK)
/*! @} */

/*! @name GPDI51 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI51_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI51_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI51_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI51_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI51_PDI_n_SHIFT)) & SIUL2_GPDI51_PDI_n_MASK)
/*! @} */

/*! @name GPDI50 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI50_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI50_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI50_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI50_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI50_PDI_n_SHIFT)) & SIUL2_GPDI50_PDI_n_MASK)
/*! @} */

/*! @name GPDI49 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI49_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI49_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI49_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI49_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI49_PDI_n_SHIFT)) & SIUL2_GPDI49_PDI_n_MASK)
/*! @} */

/*! @name GPDI48 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI48_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI48_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI48_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI48_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI48_PDI_n_SHIFT)) & SIUL2_GPDI48_PDI_n_MASK)
/*! @} */

/*! @name GPDI55 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI55_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI55_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI55_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI55_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI55_PDI_n_SHIFT)) & SIUL2_GPDI55_PDI_n_MASK)
/*! @} */

/*! @name GPDI54 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI54_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI54_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI54_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI54_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI54_PDI_n_SHIFT)) & SIUL2_GPDI54_PDI_n_MASK)
/*! @} */

/*! @name GPDI53 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI53_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI53_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI53_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI53_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI53_PDI_n_SHIFT)) & SIUL2_GPDI53_PDI_n_MASK)
/*! @} */

/*! @name GPDI52 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI52_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI52_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI52_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI52_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI52_PDI_n_SHIFT)) & SIUL2_GPDI52_PDI_n_MASK)
/*! @} */

/*! @name GPDI59 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI59_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI59_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI59_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI59_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI59_PDI_n_SHIFT)) & SIUL2_GPDI59_PDI_n_MASK)
/*! @} */

/*! @name GPDI58 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI58_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI58_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI58_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI58_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI58_PDI_n_SHIFT)) & SIUL2_GPDI58_PDI_n_MASK)
/*! @} */

/*! @name GPDI57 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI57_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI57_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI57_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI57_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI57_PDI_n_SHIFT)) & SIUL2_GPDI57_PDI_n_MASK)
/*! @} */

/*! @name GPDI56 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI56_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI56_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI56_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI56_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI56_PDI_n_SHIFT)) & SIUL2_GPDI56_PDI_n_MASK)
/*! @} */

/*! @name GPDI63 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI63_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI63_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI63_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI63_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI63_PDI_n_SHIFT)) & SIUL2_GPDI63_PDI_n_MASK)
/*! @} */

/*! @name GPDI62 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI62_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI62_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI62_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI62_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI62_PDI_n_SHIFT)) & SIUL2_GPDI62_PDI_n_MASK)
/*! @} */

/*! @name GPDI61 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI61_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI61_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI61_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI61_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI61_PDI_n_SHIFT)) & SIUL2_GPDI61_PDI_n_MASK)
/*! @} */

/*! @name GPDI60 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI60_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI60_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI60_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI60_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI60_PDI_n_SHIFT)) & SIUL2_GPDI60_PDI_n_MASK)
/*! @} */

/*! @name GPDI67 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI67_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI67_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI67_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI67_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI67_PDI_n_SHIFT)) & SIUL2_GPDI67_PDI_n_MASK)
/*! @} */

/*! @name GPDI66 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI66_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI66_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI66_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI66_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI66_PDI_n_SHIFT)) & SIUL2_GPDI66_PDI_n_MASK)
/*! @} */

/*! @name GPDI65 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI65_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI65_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI65_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI65_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI65_PDI_n_SHIFT)) & SIUL2_GPDI65_PDI_n_MASK)
/*! @} */

/*! @name GPDI64 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI64_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI64_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI64_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI64_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI64_PDI_n_SHIFT)) & SIUL2_GPDI64_PDI_n_MASK)
/*! @} */

/*! @name GPDI71 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI71_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI71_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI71_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI71_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI71_PDI_n_SHIFT)) & SIUL2_GPDI71_PDI_n_MASK)
/*! @} */

/*! @name GPDI70 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI70_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI70_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI70_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI70_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI70_PDI_n_SHIFT)) & SIUL2_GPDI70_PDI_n_MASK)
/*! @} */

/*! @name GPDI69 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI69_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI69_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI69_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI69_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI69_PDI_n_SHIFT)) & SIUL2_GPDI69_PDI_n_MASK)
/*! @} */

/*! @name GPDI68 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI68_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI68_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI68_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI68_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI68_PDI_n_SHIFT)) & SIUL2_GPDI68_PDI_n_MASK)
/*! @} */

/*! @name GPDI75 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI75_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI75_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI75_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI75_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI75_PDI_n_SHIFT)) & SIUL2_GPDI75_PDI_n_MASK)
/*! @} */

/*! @name GPDI74 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI74_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI74_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI74_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI74_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI74_PDI_n_SHIFT)) & SIUL2_GPDI74_PDI_n_MASK)
/*! @} */

/*! @name GPDI73 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI73_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI73_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI73_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI73_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI73_PDI_n_SHIFT)) & SIUL2_GPDI73_PDI_n_MASK)
/*! @} */

/*! @name GPDI72 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI72_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI72_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI72_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI72_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI72_PDI_n_SHIFT)) & SIUL2_GPDI72_PDI_n_MASK)
/*! @} */

/*! @name GPDI79 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI79_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI79_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI79_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI79_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI79_PDI_n_SHIFT)) & SIUL2_GPDI79_PDI_n_MASK)
/*! @} */

/*! @name GPDI78 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI78_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI78_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI78_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI78_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI78_PDI_n_SHIFT)) & SIUL2_GPDI78_PDI_n_MASK)
/*! @} */

/*! @name GPDI77 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI77_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI77_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI77_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI77_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI77_PDI_n_SHIFT)) & SIUL2_GPDI77_PDI_n_MASK)
/*! @} */

/*! @name GPDI76 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI76_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI76_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI76_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI76_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI76_PDI_n_SHIFT)) & SIUL2_GPDI76_PDI_n_MASK)
/*! @} */

/*! @name GPDI83 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI83_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI83_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI83_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI83_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI83_PDI_n_SHIFT)) & SIUL2_GPDI83_PDI_n_MASK)
/*! @} */

/*! @name GPDI82 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI82_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI82_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI82_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI82_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI82_PDI_n_SHIFT)) & SIUL2_GPDI82_PDI_n_MASK)
/*! @} */

/*! @name GPDI81 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI81_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI81_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI81_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI81_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI81_PDI_n_SHIFT)) & SIUL2_GPDI81_PDI_n_MASK)
/*! @} */

/*! @name GPDI80 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI80_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI80_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI80_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI80_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI80_PDI_n_SHIFT)) & SIUL2_GPDI80_PDI_n_MASK)
/*! @} */

/*! @name GPDI87 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI87_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI87_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI87_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI87_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI87_PDI_n_SHIFT)) & SIUL2_GPDI87_PDI_n_MASK)
/*! @} */

/*! @name GPDI86 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI86_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI86_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI86_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI86_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI86_PDI_n_SHIFT)) & SIUL2_GPDI86_PDI_n_MASK)
/*! @} */

/*! @name GPDI85 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI85_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI85_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI85_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI85_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI85_PDI_n_SHIFT)) & SIUL2_GPDI85_PDI_n_MASK)
/*! @} */

/*! @name GPDI84 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI84_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI84_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI84_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI84_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI84_PDI_n_SHIFT)) & SIUL2_GPDI84_PDI_n_MASK)
/*! @} */

/*! @name GPDI91 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI91_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI91_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI91_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI91_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI91_PDI_n_SHIFT)) & SIUL2_GPDI91_PDI_n_MASK)
/*! @} */

/*! @name GPDI90 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI90_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI90_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI90_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI90_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI90_PDI_n_SHIFT)) & SIUL2_GPDI90_PDI_n_MASK)
/*! @} */

/*! @name GPDI89 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI89_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI89_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI89_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI89_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI89_PDI_n_SHIFT)) & SIUL2_GPDI89_PDI_n_MASK)
/*! @} */

/*! @name GPDI88 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI88_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI88_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI88_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI88_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI88_PDI_n_SHIFT)) & SIUL2_GPDI88_PDI_n_MASK)
/*! @} */

/*! @name GPDI95 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI95_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI95_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI95_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI95_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI95_PDI_n_SHIFT)) & SIUL2_GPDI95_PDI_n_MASK)
/*! @} */

/*! @name GPDI94 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI94_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI94_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI94_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI94_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI94_PDI_n_SHIFT)) & SIUL2_GPDI94_PDI_n_MASK)
/*! @} */

/*! @name GPDI93 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI93_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI93_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI93_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI93_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI93_PDI_n_SHIFT)) & SIUL2_GPDI93_PDI_n_MASK)
/*! @} */

/*! @name GPDI92 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI92_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI92_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI92_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI92_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI92_PDI_n_SHIFT)) & SIUL2_GPDI92_PDI_n_MASK)
/*! @} */

/*! @name GPDI99 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI99_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI99_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI99_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI99_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI99_PDI_n_SHIFT)) & SIUL2_GPDI99_PDI_n_MASK)
/*! @} */

/*! @name GPDI98 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI98_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI98_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI98_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI98_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI98_PDI_n_SHIFT)) & SIUL2_GPDI98_PDI_n_MASK)
/*! @} */

/*! @name GPDI97 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI97_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI97_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI97_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI97_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI97_PDI_n_SHIFT)) & SIUL2_GPDI97_PDI_n_MASK)
/*! @} */

/*! @name GPDI96 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI96_PDI_n_MASK                  (0x1U)
#define SIUL2_GPDI96_PDI_n_SHIFT                 (0U)
#define SIUL2_GPDI96_PDI_n_WIDTH                 (1U)
#define SIUL2_GPDI96_PDI_n(x)                    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI96_PDI_n_SHIFT)) & SIUL2_GPDI96_PDI_n_MASK)
/*! @} */

/*! @name GPDI103 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI103_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI103_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI103_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI103_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI103_PDI_n_SHIFT)) & SIUL2_GPDI103_PDI_n_MASK)
/*! @} */

/*! @name GPDI102 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI102_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI102_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI102_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI102_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI102_PDI_n_SHIFT)) & SIUL2_GPDI102_PDI_n_MASK)
/*! @} */

/*! @name GPDI101 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI101_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI101_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI101_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI101_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI101_PDI_n_SHIFT)) & SIUL2_GPDI101_PDI_n_MASK)
/*! @} */

/*! @name GPDI100 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI100_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI100_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI100_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI100_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI100_PDI_n_SHIFT)) & SIUL2_GPDI100_PDI_n_MASK)
/*! @} */

/*! @name GPDI107 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI107_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI107_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI107_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI107_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI107_PDI_n_SHIFT)) & SIUL2_GPDI107_PDI_n_MASK)
/*! @} */

/*! @name GPDI106 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI106_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI106_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI106_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI106_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI106_PDI_n_SHIFT)) & SIUL2_GPDI106_PDI_n_MASK)
/*! @} */

/*! @name GPDI105 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI105_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI105_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI105_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI105_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI105_PDI_n_SHIFT)) & SIUL2_GPDI105_PDI_n_MASK)
/*! @} */

/*! @name GPDI104 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI104_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI104_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI104_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI104_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI104_PDI_n_SHIFT)) & SIUL2_GPDI104_PDI_n_MASK)
/*! @} */

/*! @name GPDI111 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI111_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI111_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI111_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI111_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI111_PDI_n_SHIFT)) & SIUL2_GPDI111_PDI_n_MASK)
/*! @} */

/*! @name GPDI110 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI110_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI110_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI110_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI110_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI110_PDI_n_SHIFT)) & SIUL2_GPDI110_PDI_n_MASK)
/*! @} */

/*! @name GPDI109 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI109_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI109_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI109_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI109_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI109_PDI_n_SHIFT)) & SIUL2_GPDI109_PDI_n_MASK)
/*! @} */

/*! @name GPDI108 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI108_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI108_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI108_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI108_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI108_PDI_n_SHIFT)) & SIUL2_GPDI108_PDI_n_MASK)
/*! @} */

/*! @name GPDI115 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI115_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI115_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI115_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI115_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI115_PDI_n_SHIFT)) & SIUL2_GPDI115_PDI_n_MASK)
/*! @} */

/*! @name GPDI114 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI114_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI114_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI114_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI114_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI114_PDI_n_SHIFT)) & SIUL2_GPDI114_PDI_n_MASK)
/*! @} */

/*! @name GPDI113 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI113_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI113_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI113_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI113_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI113_PDI_n_SHIFT)) & SIUL2_GPDI113_PDI_n_MASK)
/*! @} */

/*! @name GPDI112 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI112_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI112_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI112_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI112_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI112_PDI_n_SHIFT)) & SIUL2_GPDI112_PDI_n_MASK)
/*! @} */

/*! @name GPDI119 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI119_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI119_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI119_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI119_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI119_PDI_n_SHIFT)) & SIUL2_GPDI119_PDI_n_MASK)
/*! @} */

/*! @name GPDI118 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI118_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI118_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI118_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI118_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI118_PDI_n_SHIFT)) & SIUL2_GPDI118_PDI_n_MASK)
/*! @} */

/*! @name GPDI117 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI117_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI117_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI117_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI117_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI117_PDI_n_SHIFT)) & SIUL2_GPDI117_PDI_n_MASK)
/*! @} */

/*! @name GPDI116 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI116_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI116_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI116_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI116_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI116_PDI_n_SHIFT)) & SIUL2_GPDI116_PDI_n_MASK)
/*! @} */

/*! @name GPDI123 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI123_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI123_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI123_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI123_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI123_PDI_n_SHIFT)) & SIUL2_GPDI123_PDI_n_MASK)
/*! @} */

/*! @name GPDI122 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI122_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI122_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI122_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI122_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI122_PDI_n_SHIFT)) & SIUL2_GPDI122_PDI_n_MASK)
/*! @} */

/*! @name GPDI121 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI121_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI121_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI121_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI121_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI121_PDI_n_SHIFT)) & SIUL2_GPDI121_PDI_n_MASK)
/*! @} */

/*! @name GPDI120 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI120_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI120_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI120_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI120_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI120_PDI_n_SHIFT)) & SIUL2_GPDI120_PDI_n_MASK)
/*! @} */

/*! @name GPDI127 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI127_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI127_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI127_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI127_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI127_PDI_n_SHIFT)) & SIUL2_GPDI127_PDI_n_MASK)
/*! @} */

/*! @name GPDI126 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI126_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI126_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI126_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI126_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI126_PDI_n_SHIFT)) & SIUL2_GPDI126_PDI_n_MASK)
/*! @} */

/*! @name GPDI125 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI125_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI125_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI125_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI125_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI125_PDI_n_SHIFT)) & SIUL2_GPDI125_PDI_n_MASK)
/*! @} */

/*! @name GPDI124 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI124_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI124_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI124_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI124_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI124_PDI_n_SHIFT)) & SIUL2_GPDI124_PDI_n_MASK)
/*! @} */

/*! @name GPDI131 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI131_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI131_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI131_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI131_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI131_PDI_n_SHIFT)) & SIUL2_GPDI131_PDI_n_MASK)
/*! @} */

/*! @name GPDI130 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI130_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI130_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI130_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI130_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI130_PDI_n_SHIFT)) & SIUL2_GPDI130_PDI_n_MASK)
/*! @} */

/*! @name GPDI129 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI129_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI129_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI129_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI129_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI129_PDI_n_SHIFT)) & SIUL2_GPDI129_PDI_n_MASK)
/*! @} */

/*! @name GPDI128 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI128_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI128_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI128_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI128_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI128_PDI_n_SHIFT)) & SIUL2_GPDI128_PDI_n_MASK)
/*! @} */

/*! @name GPDI135 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI135_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI135_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI135_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI135_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI135_PDI_n_SHIFT)) & SIUL2_GPDI135_PDI_n_MASK)
/*! @} */

/*! @name GPDI134 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI134_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI134_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI134_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI134_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI134_PDI_n_SHIFT)) & SIUL2_GPDI134_PDI_n_MASK)
/*! @} */

/*! @name GPDI133 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI133_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI133_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI133_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI133_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI133_PDI_n_SHIFT)) & SIUL2_GPDI133_PDI_n_MASK)
/*! @} */

/*! @name GPDI132 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI132_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI132_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI132_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI132_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI132_PDI_n_SHIFT)) & SIUL2_GPDI132_PDI_n_MASK)
/*! @} */

/*! @name GPDI139 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI139_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI139_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI139_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI139_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI139_PDI_n_SHIFT)) & SIUL2_GPDI139_PDI_n_MASK)
/*! @} */

/*! @name GPDI138 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI138_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI138_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI138_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI138_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI138_PDI_n_SHIFT)) & SIUL2_GPDI138_PDI_n_MASK)
/*! @} */

/*! @name GPDI137 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI137_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI137_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI137_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI137_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI137_PDI_n_SHIFT)) & SIUL2_GPDI137_PDI_n_MASK)
/*! @} */

/*! @name GPDI136 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI136_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI136_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI136_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI136_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI136_PDI_n_SHIFT)) & SIUL2_GPDI136_PDI_n_MASK)
/*! @} */

/*! @name GPDI143 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI143_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI143_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI143_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI143_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI143_PDI_n_SHIFT)) & SIUL2_GPDI143_PDI_n_MASK)
/*! @} */

/*! @name GPDI142 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI142_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI142_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI142_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI142_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI142_PDI_n_SHIFT)) & SIUL2_GPDI142_PDI_n_MASK)
/*! @} */

/*! @name GPDI141 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI141_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI141_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI141_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI141_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI141_PDI_n_SHIFT)) & SIUL2_GPDI141_PDI_n_MASK)
/*! @} */

/*! @name GPDI140 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI140_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI140_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI140_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI140_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI140_PDI_n_SHIFT)) & SIUL2_GPDI140_PDI_n_MASK)
/*! @} */

/*! @name GPDI147 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI147_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI147_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI147_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI147_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI147_PDI_n_SHIFT)) & SIUL2_GPDI147_PDI_n_MASK)
/*! @} */

/*! @name GPDI146 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI146_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI146_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI146_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI146_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI146_PDI_n_SHIFT)) & SIUL2_GPDI146_PDI_n_MASK)
/*! @} */

/*! @name GPDI145 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI145_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI145_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI145_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI145_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI145_PDI_n_SHIFT)) & SIUL2_GPDI145_PDI_n_MASK)
/*! @} */

/*! @name GPDI144 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI144_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI144_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI144_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI144_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI144_PDI_n_SHIFT)) & SIUL2_GPDI144_PDI_n_MASK)
/*! @} */

/*! @name GPDI151 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI151_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI151_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI151_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI151_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI151_PDI_n_SHIFT)) & SIUL2_GPDI151_PDI_n_MASK)
/*! @} */

/*! @name GPDI150 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI150_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI150_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI150_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI150_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI150_PDI_n_SHIFT)) & SIUL2_GPDI150_PDI_n_MASK)
/*! @} */

/*! @name GPDI149 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI149_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI149_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI149_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI149_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI149_PDI_n_SHIFT)) & SIUL2_GPDI149_PDI_n_MASK)
/*! @} */

/*! @name GPDI148 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI148_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI148_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI148_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI148_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI148_PDI_n_SHIFT)) & SIUL2_GPDI148_PDI_n_MASK)
/*! @} */

/*! @name GPDI155 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI155_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI155_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI155_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI155_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI155_PDI_n_SHIFT)) & SIUL2_GPDI155_PDI_n_MASK)
/*! @} */

/*! @name GPDI154 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI154_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI154_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI154_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI154_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI154_PDI_n_SHIFT)) & SIUL2_GPDI154_PDI_n_MASK)
/*! @} */

/*! @name GPDI153 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI153_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI153_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI153_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI153_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI153_PDI_n_SHIFT)) & SIUL2_GPDI153_PDI_n_MASK)
/*! @} */

/*! @name GPDI152 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI152_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI152_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI152_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI152_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI152_PDI_n_SHIFT)) & SIUL2_GPDI152_PDI_n_MASK)
/*! @} */

/*! @name GPDI159 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI159_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI159_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI159_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI159_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI159_PDI_n_SHIFT)) & SIUL2_GPDI159_PDI_n_MASK)
/*! @} */

/*! @name GPDI158 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI158_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI158_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI158_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI158_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI158_PDI_n_SHIFT)) & SIUL2_GPDI158_PDI_n_MASK)
/*! @} */

/*! @name GPDI157 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI157_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI157_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI157_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI157_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI157_PDI_n_SHIFT)) & SIUL2_GPDI157_PDI_n_MASK)
/*! @} */

/*! @name GPDI156 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI156_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI156_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI156_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI156_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI156_PDI_n_SHIFT)) & SIUL2_GPDI156_PDI_n_MASK)
/*! @} */

/*! @name GPDI163 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI163_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI163_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI163_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI163_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI163_PDI_n_SHIFT)) & SIUL2_GPDI163_PDI_n_MASK)
/*! @} */

/*! @name GPDI162 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI162_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI162_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI162_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI162_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI162_PDI_n_SHIFT)) & SIUL2_GPDI162_PDI_n_MASK)
/*! @} */

/*! @name GPDI161 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI161_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI161_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI161_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI161_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI161_PDI_n_SHIFT)) & SIUL2_GPDI161_PDI_n_MASK)
/*! @} */

/*! @name GPDI160 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI160_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI160_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI160_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI160_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI160_PDI_n_SHIFT)) & SIUL2_GPDI160_PDI_n_MASK)
/*! @} */

/*! @name GPDI167 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI167_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI167_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI167_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI167_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI167_PDI_n_SHIFT)) & SIUL2_GPDI167_PDI_n_MASK)
/*! @} */

/*! @name GPDI166 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI166_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI166_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI166_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI166_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI166_PDI_n_SHIFT)) & SIUL2_GPDI166_PDI_n_MASK)
/*! @} */

/*! @name GPDI165 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI165_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI165_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI165_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI165_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI165_PDI_n_SHIFT)) & SIUL2_GPDI165_PDI_n_MASK)
/*! @} */

/*! @name GPDI164 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI164_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI164_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI164_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI164_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI164_PDI_n_SHIFT)) & SIUL2_GPDI164_PDI_n_MASK)
/*! @} */

/*! @name GPDI171 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI171_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI171_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI171_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI171_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI171_PDI_n_SHIFT)) & SIUL2_GPDI171_PDI_n_MASK)
/*! @} */

/*! @name GPDI170 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI170_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI170_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI170_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI170_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI170_PDI_n_SHIFT)) & SIUL2_GPDI170_PDI_n_MASK)
/*! @} */

/*! @name GPDI169 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI169_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI169_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI169_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI169_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI169_PDI_n_SHIFT)) & SIUL2_GPDI169_PDI_n_MASK)
/*! @} */

/*! @name GPDI168 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI168_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI168_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI168_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI168_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI168_PDI_n_SHIFT)) & SIUL2_GPDI168_PDI_n_MASK)
/*! @} */

/*! @name GPDI175 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI175_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI175_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI175_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI175_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI175_PDI_n_SHIFT)) & SIUL2_GPDI175_PDI_n_MASK)
/*! @} */

/*! @name GPDI174 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI174_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI174_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI174_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI174_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI174_PDI_n_SHIFT)) & SIUL2_GPDI174_PDI_n_MASK)
/*! @} */

/*! @name GPDI173 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI173_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI173_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI173_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI173_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI173_PDI_n_SHIFT)) & SIUL2_GPDI173_PDI_n_MASK)
/*! @} */

/*! @name GPDI172 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI172_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI172_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI172_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI172_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI172_PDI_n_SHIFT)) & SIUL2_GPDI172_PDI_n_MASK)
/*! @} */

/*! @name GPDI179 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI179_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI179_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI179_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI179_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI179_PDI_n_SHIFT)) & SIUL2_GPDI179_PDI_n_MASK)
/*! @} */

/*! @name GPDI178 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI178_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI178_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI178_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI178_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI178_PDI_n_SHIFT)) & SIUL2_GPDI178_PDI_n_MASK)
/*! @} */

/*! @name GPDI177 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI177_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI177_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI177_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI177_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI177_PDI_n_SHIFT)) & SIUL2_GPDI177_PDI_n_MASK)
/*! @} */

/*! @name GPDI176 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI176_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI176_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI176_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI176_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI176_PDI_n_SHIFT)) & SIUL2_GPDI176_PDI_n_MASK)
/*! @} */

/*! @name GPDI183 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI183_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI183_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI183_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI183_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI183_PDI_n_SHIFT)) & SIUL2_GPDI183_PDI_n_MASK)
/*! @} */

/*! @name GPDI182 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI182_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI182_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI182_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI182_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI182_PDI_n_SHIFT)) & SIUL2_GPDI182_PDI_n_MASK)
/*! @} */

/*! @name GPDI181 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI181_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI181_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI181_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI181_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI181_PDI_n_SHIFT)) & SIUL2_GPDI181_PDI_n_MASK)
/*! @} */

/*! @name GPDI180 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI180_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI180_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI180_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI180_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI180_PDI_n_SHIFT)) & SIUL2_GPDI180_PDI_n_MASK)
/*! @} */

/*! @name GPDI187 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI187_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI187_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI187_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI187_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI187_PDI_n_SHIFT)) & SIUL2_GPDI187_PDI_n_MASK)
/*! @} */

/*! @name GPDI186 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI186_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI186_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI186_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI186_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI186_PDI_n_SHIFT)) & SIUL2_GPDI186_PDI_n_MASK)
/*! @} */

/*! @name GPDI185 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI185_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI185_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI185_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI185_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI185_PDI_n_SHIFT)) & SIUL2_GPDI185_PDI_n_MASK)
/*! @} */

/*! @name GPDI184 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI184_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI184_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI184_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI184_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI184_PDI_n_SHIFT)) & SIUL2_GPDI184_PDI_n_MASK)
/*! @} */

/*! @name GPDI191 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI191_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI191_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI191_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI191_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI191_PDI_n_SHIFT)) & SIUL2_GPDI191_PDI_n_MASK)
/*! @} */

/*! @name GPDI190 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI190_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI190_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI190_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI190_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI190_PDI_n_SHIFT)) & SIUL2_GPDI190_PDI_n_MASK)
/*! @} */

/*! @name GPDI189 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI189_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI189_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI189_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI189_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI189_PDI_n_SHIFT)) & SIUL2_GPDI189_PDI_n_MASK)
/*! @} */

/*! @name GPDI188 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI188_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI188_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI188_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI188_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI188_PDI_n_SHIFT)) & SIUL2_GPDI188_PDI_n_MASK)
/*! @} */

/*! @name GPDI195 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI195_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI195_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI195_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI195_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI195_PDI_n_SHIFT)) & SIUL2_GPDI195_PDI_n_MASK)
/*! @} */

/*! @name GPDI194 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI194_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI194_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI194_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI194_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI194_PDI_n_SHIFT)) & SIUL2_GPDI194_PDI_n_MASK)
/*! @} */

/*! @name GPDI193 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI193_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI193_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI193_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI193_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI193_PDI_n_SHIFT)) & SIUL2_GPDI193_PDI_n_MASK)
/*! @} */

/*! @name GPDI192 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI192_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI192_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI192_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI192_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI192_PDI_n_SHIFT)) & SIUL2_GPDI192_PDI_n_MASK)
/*! @} */

/*! @name GPDI199 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI199_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI199_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI199_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI199_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI199_PDI_n_SHIFT)) & SIUL2_GPDI199_PDI_n_MASK)
/*! @} */

/*! @name GPDI198 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI198_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI198_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI198_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI198_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI198_PDI_n_SHIFT)) & SIUL2_GPDI198_PDI_n_MASK)
/*! @} */

/*! @name GPDI197 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI197_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI197_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI197_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI197_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI197_PDI_n_SHIFT)) & SIUL2_GPDI197_PDI_n_MASK)
/*! @} */

/*! @name GPDI196 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI196_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI196_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI196_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI196_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI196_PDI_n_SHIFT)) & SIUL2_GPDI196_PDI_n_MASK)
/*! @} */

/*! @name GPDI203 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI203_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI203_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI203_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI203_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI203_PDI_n_SHIFT)) & SIUL2_GPDI203_PDI_n_MASK)
/*! @} */

/*! @name GPDI202 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI202_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI202_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI202_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI202_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI202_PDI_n_SHIFT)) & SIUL2_GPDI202_PDI_n_MASK)
/*! @} */

/*! @name GPDI201 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI201_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI201_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI201_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI201_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI201_PDI_n_SHIFT)) & SIUL2_GPDI201_PDI_n_MASK)
/*! @} */

/*! @name GPDI200 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI200_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI200_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI200_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI200_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI200_PDI_n_SHIFT)) & SIUL2_GPDI200_PDI_n_MASK)
/*! @} */

/*! @name GPDI207 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI207_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI207_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI207_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI207_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI207_PDI_n_SHIFT)) & SIUL2_GPDI207_PDI_n_MASK)
/*! @} */

/*! @name GPDI206 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI206_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI206_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI206_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI206_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI206_PDI_n_SHIFT)) & SIUL2_GPDI206_PDI_n_MASK)
/*! @} */

/*! @name GPDI205 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI205_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI205_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI205_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI205_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI205_PDI_n_SHIFT)) & SIUL2_GPDI205_PDI_n_MASK)
/*! @} */

/*! @name GPDI204 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI204_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI204_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI204_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI204_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI204_PDI_n_SHIFT)) & SIUL2_GPDI204_PDI_n_MASK)
/*! @} */

/*! @name GPDI211 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI211_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI211_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI211_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI211_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI211_PDI_n_SHIFT)) & SIUL2_GPDI211_PDI_n_MASK)
/*! @} */

/*! @name GPDI210 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI210_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI210_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI210_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI210_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI210_PDI_n_SHIFT)) & SIUL2_GPDI210_PDI_n_MASK)
/*! @} */

/*! @name GPDI209 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI209_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI209_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI209_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI209_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI209_PDI_n_SHIFT)) & SIUL2_GPDI209_PDI_n_MASK)
/*! @} */

/*! @name GPDI208 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI208_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI208_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI208_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI208_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI208_PDI_n_SHIFT)) & SIUL2_GPDI208_PDI_n_MASK)
/*! @} */

/*! @name GPDI215 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI215_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI215_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI215_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI215_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI215_PDI_n_SHIFT)) & SIUL2_GPDI215_PDI_n_MASK)
/*! @} */

/*! @name GPDI214 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI214_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI214_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI214_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI214_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI214_PDI_n_SHIFT)) & SIUL2_GPDI214_PDI_n_MASK)
/*! @} */

/*! @name GPDI213 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI213_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI213_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI213_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI213_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI213_PDI_n_SHIFT)) & SIUL2_GPDI213_PDI_n_MASK)
/*! @} */

/*! @name GPDI212 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI212_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI212_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI212_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI212_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI212_PDI_n_SHIFT)) & SIUL2_GPDI212_PDI_n_MASK)
/*! @} */

/*! @name GPDI219 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI219_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI219_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI219_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI219_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI219_PDI_n_SHIFT)) & SIUL2_GPDI219_PDI_n_MASK)
/*! @} */

/*! @name GPDI218 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI218_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI218_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI218_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI218_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI218_PDI_n_SHIFT)) & SIUL2_GPDI218_PDI_n_MASK)
/*! @} */

/*! @name GPDI217 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI217_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI217_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI217_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI217_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI217_PDI_n_SHIFT)) & SIUL2_GPDI217_PDI_n_MASK)
/*! @} */

/*! @name GPDI216 - SIUL2 GPIO Pad Data Input Register */
/*! @{ */

#define SIUL2_GPDI216_PDI_n_MASK                 (0x1U)
#define SIUL2_GPDI216_PDI_n_SHIFT                (0U)
#define SIUL2_GPDI216_PDI_n_WIDTH                (1U)
#define SIUL2_GPDI216_PDI_n(x)                   (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI216_PDI_n_SHIFT)) & SIUL2_GPDI216_PDI_n_MASK)
/*! @} */

/*! @name PGPDO1 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO1_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO1_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO1_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO0_SHIFT)) & SIUL2_PGPDO1_PPDO0_MASK)

#define SIUL2_PGPDO1_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO1_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO1_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO1_SHIFT)) & SIUL2_PGPDO1_PPDO1_MASK)

#define SIUL2_PGPDO1_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO1_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO1_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO2_SHIFT)) & SIUL2_PGPDO1_PPDO2_MASK)

#define SIUL2_PGPDO1_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO1_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO1_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO3_SHIFT)) & SIUL2_PGPDO1_PPDO3_MASK)

#define SIUL2_PGPDO1_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO1_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO1_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO4_SHIFT)) & SIUL2_PGPDO1_PPDO4_MASK)

#define SIUL2_PGPDO1_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO1_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO1_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO5_SHIFT)) & SIUL2_PGPDO1_PPDO5_MASK)

#define SIUL2_PGPDO1_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO1_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO1_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO6_SHIFT)) & SIUL2_PGPDO1_PPDO6_MASK)

#define SIUL2_PGPDO1_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO1_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO1_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO7_SHIFT)) & SIUL2_PGPDO1_PPDO7_MASK)

#define SIUL2_PGPDO1_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO1_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO1_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO8_SHIFT)) & SIUL2_PGPDO1_PPDO8_MASK)

#define SIUL2_PGPDO1_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO1_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO1_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO1_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO9_SHIFT)) & SIUL2_PGPDO1_PPDO9_MASK)

#define SIUL2_PGPDO1_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO1_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO1_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO1_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO10_SHIFT)) & SIUL2_PGPDO1_PPDO10_MASK)

#define SIUL2_PGPDO1_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO1_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO1_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO1_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO11_SHIFT)) & SIUL2_PGPDO1_PPDO11_MASK)

#define SIUL2_PGPDO1_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO1_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO1_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO1_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO12_SHIFT)) & SIUL2_PGPDO1_PPDO12_MASK)

#define SIUL2_PGPDO1_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO1_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO1_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO1_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO13_SHIFT)) & SIUL2_PGPDO1_PPDO13_MASK)

#define SIUL2_PGPDO1_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO1_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO1_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO1_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO14_SHIFT)) & SIUL2_PGPDO1_PPDO14_MASK)

#define SIUL2_PGPDO1_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO1_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO1_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO1_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO15_SHIFT)) & SIUL2_PGPDO1_PPDO15_MASK)
/*! @} */

/*! @name PGPDO0 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO0_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO0_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO0_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO0_SHIFT)) & SIUL2_PGPDO0_PPDO0_MASK)

#define SIUL2_PGPDO0_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO0_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO0_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO1_SHIFT)) & SIUL2_PGPDO0_PPDO1_MASK)

#define SIUL2_PGPDO0_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO0_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO0_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO2_SHIFT)) & SIUL2_PGPDO0_PPDO2_MASK)

#define SIUL2_PGPDO0_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO0_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO0_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO3_SHIFT)) & SIUL2_PGPDO0_PPDO3_MASK)

#define SIUL2_PGPDO0_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO0_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO0_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO4_SHIFT)) & SIUL2_PGPDO0_PPDO4_MASK)

#define SIUL2_PGPDO0_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO0_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO0_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO5_SHIFT)) & SIUL2_PGPDO0_PPDO5_MASK)

#define SIUL2_PGPDO0_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO0_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO0_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO6_SHIFT)) & SIUL2_PGPDO0_PPDO6_MASK)

#define SIUL2_PGPDO0_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO0_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO0_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO7_SHIFT)) & SIUL2_PGPDO0_PPDO7_MASK)

#define SIUL2_PGPDO0_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO0_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO0_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO8_SHIFT)) & SIUL2_PGPDO0_PPDO8_MASK)

#define SIUL2_PGPDO0_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO0_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO0_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO0_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO9_SHIFT)) & SIUL2_PGPDO0_PPDO9_MASK)

#define SIUL2_PGPDO0_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO0_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO0_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO0_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO10_SHIFT)) & SIUL2_PGPDO0_PPDO10_MASK)

#define SIUL2_PGPDO0_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO0_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO0_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO0_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO11_SHIFT)) & SIUL2_PGPDO0_PPDO11_MASK)

#define SIUL2_PGPDO0_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO0_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO0_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO0_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO12_SHIFT)) & SIUL2_PGPDO0_PPDO12_MASK)

#define SIUL2_PGPDO0_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO0_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO0_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO0_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO13_SHIFT)) & SIUL2_PGPDO0_PPDO13_MASK)

#define SIUL2_PGPDO0_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO0_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO0_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO0_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO14_SHIFT)) & SIUL2_PGPDO0_PPDO14_MASK)

#define SIUL2_PGPDO0_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO0_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO0_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO0_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO15_SHIFT)) & SIUL2_PGPDO0_PPDO15_MASK)
/*! @} */

/*! @name PGPDO3 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO3_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO3_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO3_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO0_SHIFT)) & SIUL2_PGPDO3_PPDO0_MASK)

#define SIUL2_PGPDO3_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO3_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO3_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO1_SHIFT)) & SIUL2_PGPDO3_PPDO1_MASK)

#define SIUL2_PGPDO3_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO3_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO3_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO2_SHIFT)) & SIUL2_PGPDO3_PPDO2_MASK)

#define SIUL2_PGPDO3_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO3_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO3_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO3_SHIFT)) & SIUL2_PGPDO3_PPDO3_MASK)

#define SIUL2_PGPDO3_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO3_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO3_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO4_SHIFT)) & SIUL2_PGPDO3_PPDO4_MASK)

#define SIUL2_PGPDO3_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO3_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO3_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO5_SHIFT)) & SIUL2_PGPDO3_PPDO5_MASK)

#define SIUL2_PGPDO3_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO3_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO3_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO6_SHIFT)) & SIUL2_PGPDO3_PPDO6_MASK)

#define SIUL2_PGPDO3_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO3_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO3_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO7_SHIFT)) & SIUL2_PGPDO3_PPDO7_MASK)

#define SIUL2_PGPDO3_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO3_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO3_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO8_SHIFT)) & SIUL2_PGPDO3_PPDO8_MASK)

#define SIUL2_PGPDO3_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO3_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO3_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO3_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO9_SHIFT)) & SIUL2_PGPDO3_PPDO9_MASK)

#define SIUL2_PGPDO3_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO3_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO3_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO3_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO10_SHIFT)) & SIUL2_PGPDO3_PPDO10_MASK)

#define SIUL2_PGPDO3_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO3_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO3_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO3_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO11_SHIFT)) & SIUL2_PGPDO3_PPDO11_MASK)

#define SIUL2_PGPDO3_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO3_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO3_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO3_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO12_SHIFT)) & SIUL2_PGPDO3_PPDO12_MASK)

#define SIUL2_PGPDO3_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO3_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO3_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO3_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO13_SHIFT)) & SIUL2_PGPDO3_PPDO13_MASK)

#define SIUL2_PGPDO3_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO3_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO3_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO3_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO14_SHIFT)) & SIUL2_PGPDO3_PPDO14_MASK)

#define SIUL2_PGPDO3_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO3_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO3_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO3_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO15_SHIFT)) & SIUL2_PGPDO3_PPDO15_MASK)
/*! @} */

/*! @name PGPDO2 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO2_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO2_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO2_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO0_SHIFT)) & SIUL2_PGPDO2_PPDO0_MASK)

#define SIUL2_PGPDO2_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO2_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO2_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO1_SHIFT)) & SIUL2_PGPDO2_PPDO1_MASK)

#define SIUL2_PGPDO2_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO2_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO2_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO2_SHIFT)) & SIUL2_PGPDO2_PPDO2_MASK)

#define SIUL2_PGPDO2_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO2_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO2_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO3_SHIFT)) & SIUL2_PGPDO2_PPDO3_MASK)

#define SIUL2_PGPDO2_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO2_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO2_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO4_SHIFT)) & SIUL2_PGPDO2_PPDO4_MASK)

#define SIUL2_PGPDO2_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO2_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO2_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO5_SHIFT)) & SIUL2_PGPDO2_PPDO5_MASK)

#define SIUL2_PGPDO2_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO2_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO2_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO6_SHIFT)) & SIUL2_PGPDO2_PPDO6_MASK)

#define SIUL2_PGPDO2_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO2_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO2_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO2_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO7_SHIFT)) & SIUL2_PGPDO2_PPDO7_MASK)

#define SIUL2_PGPDO2_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO2_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO2_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO2_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO10_SHIFT)) & SIUL2_PGPDO2_PPDO10_MASK)

#define SIUL2_PGPDO2_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO2_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO2_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO2_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO11_SHIFT)) & SIUL2_PGPDO2_PPDO11_MASK)

#define SIUL2_PGPDO2_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO2_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO2_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO2_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO12_SHIFT)) & SIUL2_PGPDO2_PPDO12_MASK)

#define SIUL2_PGPDO2_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO2_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO2_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO2_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO13_SHIFT)) & SIUL2_PGPDO2_PPDO13_MASK)

#define SIUL2_PGPDO2_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO2_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO2_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO2_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO14_SHIFT)) & SIUL2_PGPDO2_PPDO14_MASK)

#define SIUL2_PGPDO2_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO2_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO2_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO2_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO15_SHIFT)) & SIUL2_PGPDO2_PPDO15_MASK)
/*! @} */

/*! @name PGPDO5 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO5_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO5_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO5_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO0_SHIFT)) & SIUL2_PGPDO5_PPDO0_MASK)

#define SIUL2_PGPDO5_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO5_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO5_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO1_SHIFT)) & SIUL2_PGPDO5_PPDO1_MASK)

#define SIUL2_PGPDO5_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO5_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO5_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO2_SHIFT)) & SIUL2_PGPDO5_PPDO2_MASK)

#define SIUL2_PGPDO5_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO5_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO5_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO3_SHIFT)) & SIUL2_PGPDO5_PPDO3_MASK)

#define SIUL2_PGPDO5_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO5_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO5_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO4_SHIFT)) & SIUL2_PGPDO5_PPDO4_MASK)

#define SIUL2_PGPDO5_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO5_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO5_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO5_SHIFT)) & SIUL2_PGPDO5_PPDO5_MASK)

#define SIUL2_PGPDO5_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO5_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO5_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO6_SHIFT)) & SIUL2_PGPDO5_PPDO6_MASK)

#define SIUL2_PGPDO5_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO5_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO5_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO7_SHIFT)) & SIUL2_PGPDO5_PPDO7_MASK)

#define SIUL2_PGPDO5_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO5_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO5_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO8_SHIFT)) & SIUL2_PGPDO5_PPDO8_MASK)

#define SIUL2_PGPDO5_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO5_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO5_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO5_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO9_SHIFT)) & SIUL2_PGPDO5_PPDO9_MASK)

#define SIUL2_PGPDO5_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO5_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO5_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO5_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO10_SHIFT)) & SIUL2_PGPDO5_PPDO10_MASK)

#define SIUL2_PGPDO5_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO5_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO5_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO5_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO11_SHIFT)) & SIUL2_PGPDO5_PPDO11_MASK)

#define SIUL2_PGPDO5_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO5_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO5_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO5_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO12_SHIFT)) & SIUL2_PGPDO5_PPDO12_MASK)

#define SIUL2_PGPDO5_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO5_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO5_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO5_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO13_SHIFT)) & SIUL2_PGPDO5_PPDO13_MASK)

#define SIUL2_PGPDO5_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO5_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO5_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO5_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO14_SHIFT)) & SIUL2_PGPDO5_PPDO14_MASK)

#define SIUL2_PGPDO5_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO5_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO5_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO5_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO15_SHIFT)) & SIUL2_PGPDO5_PPDO15_MASK)
/*! @} */

/*! @name PGPDO4 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO4_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO4_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO4_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO0_SHIFT)) & SIUL2_PGPDO4_PPDO0_MASK)

#define SIUL2_PGPDO4_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO4_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO4_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO1_SHIFT)) & SIUL2_PGPDO4_PPDO1_MASK)

#define SIUL2_PGPDO4_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO4_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO4_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO2_SHIFT)) & SIUL2_PGPDO4_PPDO2_MASK)

#define SIUL2_PGPDO4_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO4_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO4_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO3_SHIFT)) & SIUL2_PGPDO4_PPDO3_MASK)

#define SIUL2_PGPDO4_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO4_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO4_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO4_SHIFT)) & SIUL2_PGPDO4_PPDO4_MASK)

#define SIUL2_PGPDO4_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO4_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO4_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO5_SHIFT)) & SIUL2_PGPDO4_PPDO5_MASK)

#define SIUL2_PGPDO4_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO4_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO4_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO6_SHIFT)) & SIUL2_PGPDO4_PPDO6_MASK)

#define SIUL2_PGPDO4_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO4_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO4_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO7_SHIFT)) & SIUL2_PGPDO4_PPDO7_MASK)

#define SIUL2_PGPDO4_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO4_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO4_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO8_SHIFT)) & SIUL2_PGPDO4_PPDO8_MASK)

#define SIUL2_PGPDO4_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO4_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO4_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO4_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO9_SHIFT)) & SIUL2_PGPDO4_PPDO9_MASK)

#define SIUL2_PGPDO4_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO4_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO4_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO4_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO10_SHIFT)) & SIUL2_PGPDO4_PPDO10_MASK)

#define SIUL2_PGPDO4_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO4_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO4_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO4_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO11_SHIFT)) & SIUL2_PGPDO4_PPDO11_MASK)

#define SIUL2_PGPDO4_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO4_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO4_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO4_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO12_SHIFT)) & SIUL2_PGPDO4_PPDO12_MASK)

#define SIUL2_PGPDO4_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO4_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO4_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO4_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO13_SHIFT)) & SIUL2_PGPDO4_PPDO13_MASK)

#define SIUL2_PGPDO4_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO4_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO4_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO4_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO14_SHIFT)) & SIUL2_PGPDO4_PPDO14_MASK)

#define SIUL2_PGPDO4_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO4_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO4_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO4_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO15_SHIFT)) & SIUL2_PGPDO4_PPDO15_MASK)
/*! @} */

/*! @name PGPDO7 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO7_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO7_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO7_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO0_SHIFT)) & SIUL2_PGPDO7_PPDO0_MASK)

#define SIUL2_PGPDO7_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO7_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO7_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO1_SHIFT)) & SIUL2_PGPDO7_PPDO1_MASK)

#define SIUL2_PGPDO7_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO7_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO7_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO2_SHIFT)) & SIUL2_PGPDO7_PPDO2_MASK)

#define SIUL2_PGPDO7_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO7_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO7_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO3_SHIFT)) & SIUL2_PGPDO7_PPDO3_MASK)

#define SIUL2_PGPDO7_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO7_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO7_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO4_SHIFT)) & SIUL2_PGPDO7_PPDO4_MASK)

#define SIUL2_PGPDO7_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO7_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO7_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO5_SHIFT)) & SIUL2_PGPDO7_PPDO5_MASK)

#define SIUL2_PGPDO7_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO7_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO7_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO6_SHIFT)) & SIUL2_PGPDO7_PPDO6_MASK)

#define SIUL2_PGPDO7_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO7_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO7_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO7_SHIFT)) & SIUL2_PGPDO7_PPDO7_MASK)

#define SIUL2_PGPDO7_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO7_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO7_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO8_SHIFT)) & SIUL2_PGPDO7_PPDO8_MASK)

#define SIUL2_PGPDO7_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO7_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO7_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO7_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO9_SHIFT)) & SIUL2_PGPDO7_PPDO9_MASK)

#define SIUL2_PGPDO7_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO7_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO7_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO7_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO10_SHIFT)) & SIUL2_PGPDO7_PPDO10_MASK)

#define SIUL2_PGPDO7_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO7_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO7_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO7_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO11_SHIFT)) & SIUL2_PGPDO7_PPDO11_MASK)

#define SIUL2_PGPDO7_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO7_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO7_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO7_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO12_SHIFT)) & SIUL2_PGPDO7_PPDO12_MASK)

#define SIUL2_PGPDO7_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO7_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO7_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO7_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO13_SHIFT)) & SIUL2_PGPDO7_PPDO13_MASK)

#define SIUL2_PGPDO7_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO7_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO7_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO7_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO14_SHIFT)) & SIUL2_PGPDO7_PPDO14_MASK)

#define SIUL2_PGPDO7_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO7_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO7_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO7_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO15_SHIFT)) & SIUL2_PGPDO7_PPDO15_MASK)
/*! @} */

/*! @name PGPDO6 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO6_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO6_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO6_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO0_SHIFT)) & SIUL2_PGPDO6_PPDO0_MASK)

#define SIUL2_PGPDO6_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO6_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO6_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO1_SHIFT)) & SIUL2_PGPDO6_PPDO1_MASK)

#define SIUL2_PGPDO6_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO6_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO6_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO2_SHIFT)) & SIUL2_PGPDO6_PPDO2_MASK)

#define SIUL2_PGPDO6_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO6_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO6_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO3_SHIFT)) & SIUL2_PGPDO6_PPDO3_MASK)

#define SIUL2_PGPDO6_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO6_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO6_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO4_SHIFT)) & SIUL2_PGPDO6_PPDO4_MASK)

#define SIUL2_PGPDO6_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO6_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO6_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO5_SHIFT)) & SIUL2_PGPDO6_PPDO5_MASK)

#define SIUL2_PGPDO6_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO6_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO6_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO6_SHIFT)) & SIUL2_PGPDO6_PPDO6_MASK)

#define SIUL2_PGPDO6_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO6_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO6_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO7_SHIFT)) & SIUL2_PGPDO6_PPDO7_MASK)

#define SIUL2_PGPDO6_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO6_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO6_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO8_SHIFT)) & SIUL2_PGPDO6_PPDO8_MASK)

#define SIUL2_PGPDO6_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO6_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO6_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO6_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO9_SHIFT)) & SIUL2_PGPDO6_PPDO9_MASK)

#define SIUL2_PGPDO6_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO6_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO6_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO6_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO10_SHIFT)) & SIUL2_PGPDO6_PPDO10_MASK)

#define SIUL2_PGPDO6_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO6_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO6_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO6_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO11_SHIFT)) & SIUL2_PGPDO6_PPDO11_MASK)

#define SIUL2_PGPDO6_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO6_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO6_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO6_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO12_SHIFT)) & SIUL2_PGPDO6_PPDO12_MASK)

#define SIUL2_PGPDO6_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO6_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO6_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO6_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO13_SHIFT)) & SIUL2_PGPDO6_PPDO13_MASK)

#define SIUL2_PGPDO6_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO6_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO6_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO6_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO14_SHIFT)) & SIUL2_PGPDO6_PPDO14_MASK)

#define SIUL2_PGPDO6_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO6_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO6_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO6_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO15_SHIFT)) & SIUL2_PGPDO6_PPDO15_MASK)
/*! @} */

/*! @name PGPDO9 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO9_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO9_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO9_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO0_SHIFT)) & SIUL2_PGPDO9_PPDO0_MASK)

#define SIUL2_PGPDO9_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO9_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO9_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO1_SHIFT)) & SIUL2_PGPDO9_PPDO1_MASK)

#define SIUL2_PGPDO9_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO9_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO9_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO2_SHIFT)) & SIUL2_PGPDO9_PPDO2_MASK)

#define SIUL2_PGPDO9_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO9_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO9_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO3_SHIFT)) & SIUL2_PGPDO9_PPDO3_MASK)

#define SIUL2_PGPDO9_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO9_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO9_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO4_SHIFT)) & SIUL2_PGPDO9_PPDO4_MASK)

#define SIUL2_PGPDO9_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO9_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO9_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO5_SHIFT)) & SIUL2_PGPDO9_PPDO5_MASK)

#define SIUL2_PGPDO9_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO9_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO9_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO6_SHIFT)) & SIUL2_PGPDO9_PPDO6_MASK)

#define SIUL2_PGPDO9_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO9_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO9_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO7_SHIFT)) & SIUL2_PGPDO9_PPDO7_MASK)

#define SIUL2_PGPDO9_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO9_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO9_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO8_SHIFT)) & SIUL2_PGPDO9_PPDO8_MASK)

#define SIUL2_PGPDO9_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO9_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO9_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO9_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO9_SHIFT)) & SIUL2_PGPDO9_PPDO9_MASK)

#define SIUL2_PGPDO9_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO9_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO9_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO9_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO10_SHIFT)) & SIUL2_PGPDO9_PPDO10_MASK)

#define SIUL2_PGPDO9_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO9_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO9_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO9_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO11_SHIFT)) & SIUL2_PGPDO9_PPDO11_MASK)

#define SIUL2_PGPDO9_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO9_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO9_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO9_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO12_SHIFT)) & SIUL2_PGPDO9_PPDO12_MASK)

#define SIUL2_PGPDO9_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO9_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO9_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO9_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO13_SHIFT)) & SIUL2_PGPDO9_PPDO13_MASK)

#define SIUL2_PGPDO9_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO9_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO9_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO9_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO14_SHIFT)) & SIUL2_PGPDO9_PPDO14_MASK)

#define SIUL2_PGPDO9_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO9_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO9_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO9_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO15_SHIFT)) & SIUL2_PGPDO9_PPDO15_MASK)
/*! @} */

/*! @name PGPDO8 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO8_PPDO0_MASK                  (0x1U)
#define SIUL2_PGPDO8_PPDO0_SHIFT                 (0U)
#define SIUL2_PGPDO8_PPDO0_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO0_SHIFT)) & SIUL2_PGPDO8_PPDO0_MASK)

#define SIUL2_PGPDO8_PPDO1_MASK                  (0x2U)
#define SIUL2_PGPDO8_PPDO1_SHIFT                 (1U)
#define SIUL2_PGPDO8_PPDO1_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO1_SHIFT)) & SIUL2_PGPDO8_PPDO1_MASK)

#define SIUL2_PGPDO8_PPDO2_MASK                  (0x4U)
#define SIUL2_PGPDO8_PPDO2_SHIFT                 (2U)
#define SIUL2_PGPDO8_PPDO2_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO2_SHIFT)) & SIUL2_PGPDO8_PPDO2_MASK)

#define SIUL2_PGPDO8_PPDO3_MASK                  (0x8U)
#define SIUL2_PGPDO8_PPDO3_SHIFT                 (3U)
#define SIUL2_PGPDO8_PPDO3_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO3_SHIFT)) & SIUL2_PGPDO8_PPDO3_MASK)

#define SIUL2_PGPDO8_PPDO4_MASK                  (0x10U)
#define SIUL2_PGPDO8_PPDO4_SHIFT                 (4U)
#define SIUL2_PGPDO8_PPDO4_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO4_SHIFT)) & SIUL2_PGPDO8_PPDO4_MASK)

#define SIUL2_PGPDO8_PPDO5_MASK                  (0x20U)
#define SIUL2_PGPDO8_PPDO5_SHIFT                 (5U)
#define SIUL2_PGPDO8_PPDO5_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO5_SHIFT)) & SIUL2_PGPDO8_PPDO5_MASK)

#define SIUL2_PGPDO8_PPDO6_MASK                  (0x40U)
#define SIUL2_PGPDO8_PPDO6_SHIFT                 (6U)
#define SIUL2_PGPDO8_PPDO6_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO6_SHIFT)) & SIUL2_PGPDO8_PPDO6_MASK)

#define SIUL2_PGPDO8_PPDO7_MASK                  (0x80U)
#define SIUL2_PGPDO8_PPDO7_SHIFT                 (7U)
#define SIUL2_PGPDO8_PPDO7_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO7_SHIFT)) & SIUL2_PGPDO8_PPDO7_MASK)

#define SIUL2_PGPDO8_PPDO8_MASK                  (0x100U)
#define SIUL2_PGPDO8_PPDO8_SHIFT                 (8U)
#define SIUL2_PGPDO8_PPDO8_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO8_SHIFT)) & SIUL2_PGPDO8_PPDO8_MASK)

#define SIUL2_PGPDO8_PPDO9_MASK                  (0x200U)
#define SIUL2_PGPDO8_PPDO9_SHIFT                 (9U)
#define SIUL2_PGPDO8_PPDO9_WIDTH                 (1U)
#define SIUL2_PGPDO8_PPDO9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO9_SHIFT)) & SIUL2_PGPDO8_PPDO9_MASK)

#define SIUL2_PGPDO8_PPDO10_MASK                 (0x400U)
#define SIUL2_PGPDO8_PPDO10_SHIFT                (10U)
#define SIUL2_PGPDO8_PPDO10_WIDTH                (1U)
#define SIUL2_PGPDO8_PPDO10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO10_SHIFT)) & SIUL2_PGPDO8_PPDO10_MASK)

#define SIUL2_PGPDO8_PPDO11_MASK                 (0x800U)
#define SIUL2_PGPDO8_PPDO11_SHIFT                (11U)
#define SIUL2_PGPDO8_PPDO11_WIDTH                (1U)
#define SIUL2_PGPDO8_PPDO11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO11_SHIFT)) & SIUL2_PGPDO8_PPDO11_MASK)

#define SIUL2_PGPDO8_PPDO12_MASK                 (0x1000U)
#define SIUL2_PGPDO8_PPDO12_SHIFT                (12U)
#define SIUL2_PGPDO8_PPDO12_WIDTH                (1U)
#define SIUL2_PGPDO8_PPDO12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO12_SHIFT)) & SIUL2_PGPDO8_PPDO12_MASK)

#define SIUL2_PGPDO8_PPDO13_MASK                 (0x2000U)
#define SIUL2_PGPDO8_PPDO13_SHIFT                (13U)
#define SIUL2_PGPDO8_PPDO13_WIDTH                (1U)
#define SIUL2_PGPDO8_PPDO13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO13_SHIFT)) & SIUL2_PGPDO8_PPDO13_MASK)

#define SIUL2_PGPDO8_PPDO14_MASK                 (0x4000U)
#define SIUL2_PGPDO8_PPDO14_SHIFT                (14U)
#define SIUL2_PGPDO8_PPDO14_WIDTH                (1U)
#define SIUL2_PGPDO8_PPDO14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO14_SHIFT)) & SIUL2_PGPDO8_PPDO14_MASK)

#define SIUL2_PGPDO8_PPDO15_MASK                 (0x8000U)
#define SIUL2_PGPDO8_PPDO15_SHIFT                (15U)
#define SIUL2_PGPDO8_PPDO15_WIDTH                (1U)
#define SIUL2_PGPDO8_PPDO15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO15_SHIFT)) & SIUL2_PGPDO8_PPDO15_MASK)
/*! @} */

/*! @name PGPDO11 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO11_PPDO0_MASK                 (0x1U)
#define SIUL2_PGPDO11_PPDO0_SHIFT                (0U)
#define SIUL2_PGPDO11_PPDO0_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO0(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO0_SHIFT)) & SIUL2_PGPDO11_PPDO0_MASK)

#define SIUL2_PGPDO11_PPDO1_MASK                 (0x2U)
#define SIUL2_PGPDO11_PPDO1_SHIFT                (1U)
#define SIUL2_PGPDO11_PPDO1_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO1(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO1_SHIFT)) & SIUL2_PGPDO11_PPDO1_MASK)

#define SIUL2_PGPDO11_PPDO2_MASK                 (0x4U)
#define SIUL2_PGPDO11_PPDO2_SHIFT                (2U)
#define SIUL2_PGPDO11_PPDO2_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO2(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO2_SHIFT)) & SIUL2_PGPDO11_PPDO2_MASK)

#define SIUL2_PGPDO11_PPDO3_MASK                 (0x8U)
#define SIUL2_PGPDO11_PPDO3_SHIFT                (3U)
#define SIUL2_PGPDO11_PPDO3_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO3(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO3_SHIFT)) & SIUL2_PGPDO11_PPDO3_MASK)

#define SIUL2_PGPDO11_PPDO4_MASK                 (0x10U)
#define SIUL2_PGPDO11_PPDO4_SHIFT                (4U)
#define SIUL2_PGPDO11_PPDO4_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO4_SHIFT)) & SIUL2_PGPDO11_PPDO4_MASK)

#define SIUL2_PGPDO11_PPDO5_MASK                 (0x20U)
#define SIUL2_PGPDO11_PPDO5_SHIFT                (5U)
#define SIUL2_PGPDO11_PPDO5_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO5_SHIFT)) & SIUL2_PGPDO11_PPDO5_MASK)

#define SIUL2_PGPDO11_PPDO6_MASK                 (0x40U)
#define SIUL2_PGPDO11_PPDO6_SHIFT                (6U)
#define SIUL2_PGPDO11_PPDO6_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO6_SHIFT)) & SIUL2_PGPDO11_PPDO6_MASK)

#define SIUL2_PGPDO11_PPDO7_MASK                 (0x80U)
#define SIUL2_PGPDO11_PPDO7_SHIFT                (7U)
#define SIUL2_PGPDO11_PPDO7_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO7_SHIFT)) & SIUL2_PGPDO11_PPDO7_MASK)

#define SIUL2_PGPDO11_PPDO8_MASK                 (0x100U)
#define SIUL2_PGPDO11_PPDO8_SHIFT                (8U)
#define SIUL2_PGPDO11_PPDO8_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO8_SHIFT)) & SIUL2_PGPDO11_PPDO8_MASK)

#define SIUL2_PGPDO11_PPDO9_MASK                 (0x200U)
#define SIUL2_PGPDO11_PPDO9_SHIFT                (9U)
#define SIUL2_PGPDO11_PPDO9_WIDTH                (1U)
#define SIUL2_PGPDO11_PPDO9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO9_SHIFT)) & SIUL2_PGPDO11_PPDO9_MASK)

#define SIUL2_PGPDO11_PPDO10_MASK                (0x400U)
#define SIUL2_PGPDO11_PPDO10_SHIFT               (10U)
#define SIUL2_PGPDO11_PPDO10_WIDTH               (1U)
#define SIUL2_PGPDO11_PPDO10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO10_SHIFT)) & SIUL2_PGPDO11_PPDO10_MASK)

#define SIUL2_PGPDO11_PPDO11_MASK                (0x800U)
#define SIUL2_PGPDO11_PPDO11_SHIFT               (11U)
#define SIUL2_PGPDO11_PPDO11_WIDTH               (1U)
#define SIUL2_PGPDO11_PPDO11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO11_SHIFT)) & SIUL2_PGPDO11_PPDO11_MASK)

#define SIUL2_PGPDO11_PPDO12_MASK                (0x1000U)
#define SIUL2_PGPDO11_PPDO12_SHIFT               (12U)
#define SIUL2_PGPDO11_PPDO12_WIDTH               (1U)
#define SIUL2_PGPDO11_PPDO12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO12_SHIFT)) & SIUL2_PGPDO11_PPDO12_MASK)

#define SIUL2_PGPDO11_PPDO13_MASK                (0x2000U)
#define SIUL2_PGPDO11_PPDO13_SHIFT               (13U)
#define SIUL2_PGPDO11_PPDO13_WIDTH               (1U)
#define SIUL2_PGPDO11_PPDO13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO13_SHIFT)) & SIUL2_PGPDO11_PPDO13_MASK)

#define SIUL2_PGPDO11_PPDO14_MASK                (0x4000U)
#define SIUL2_PGPDO11_PPDO14_SHIFT               (14U)
#define SIUL2_PGPDO11_PPDO14_WIDTH               (1U)
#define SIUL2_PGPDO11_PPDO14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO14_SHIFT)) & SIUL2_PGPDO11_PPDO14_MASK)

#define SIUL2_PGPDO11_PPDO15_MASK                (0x8000U)
#define SIUL2_PGPDO11_PPDO15_SHIFT               (15U)
#define SIUL2_PGPDO11_PPDO15_WIDTH               (1U)
#define SIUL2_PGPDO11_PPDO15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO11_PPDO15_SHIFT)) & SIUL2_PGPDO11_PPDO15_MASK)
/*! @} */

/*! @name PGPDO10 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO10_PPDO0_MASK                 (0x1U)
#define SIUL2_PGPDO10_PPDO0_SHIFT                (0U)
#define SIUL2_PGPDO10_PPDO0_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO0(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO0_SHIFT)) & SIUL2_PGPDO10_PPDO0_MASK)

#define SIUL2_PGPDO10_PPDO1_MASK                 (0x2U)
#define SIUL2_PGPDO10_PPDO1_SHIFT                (1U)
#define SIUL2_PGPDO10_PPDO1_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO1(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO1_SHIFT)) & SIUL2_PGPDO10_PPDO1_MASK)

#define SIUL2_PGPDO10_PPDO2_MASK                 (0x4U)
#define SIUL2_PGPDO10_PPDO2_SHIFT                (2U)
#define SIUL2_PGPDO10_PPDO2_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO2(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO2_SHIFT)) & SIUL2_PGPDO10_PPDO2_MASK)

#define SIUL2_PGPDO10_PPDO3_MASK                 (0x8U)
#define SIUL2_PGPDO10_PPDO3_SHIFT                (3U)
#define SIUL2_PGPDO10_PPDO3_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO3(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO3_SHIFT)) & SIUL2_PGPDO10_PPDO3_MASK)

#define SIUL2_PGPDO10_PPDO4_MASK                 (0x10U)
#define SIUL2_PGPDO10_PPDO4_SHIFT                (4U)
#define SIUL2_PGPDO10_PPDO4_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO4_SHIFT)) & SIUL2_PGPDO10_PPDO4_MASK)

#define SIUL2_PGPDO10_PPDO5_MASK                 (0x20U)
#define SIUL2_PGPDO10_PPDO5_SHIFT                (5U)
#define SIUL2_PGPDO10_PPDO5_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO5_SHIFT)) & SIUL2_PGPDO10_PPDO5_MASK)

#define SIUL2_PGPDO10_PPDO6_MASK                 (0x40U)
#define SIUL2_PGPDO10_PPDO6_SHIFT                (6U)
#define SIUL2_PGPDO10_PPDO6_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO6_SHIFT)) & SIUL2_PGPDO10_PPDO6_MASK)

#define SIUL2_PGPDO10_PPDO7_MASK                 (0x80U)
#define SIUL2_PGPDO10_PPDO7_SHIFT                (7U)
#define SIUL2_PGPDO10_PPDO7_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO7_SHIFT)) & SIUL2_PGPDO10_PPDO7_MASK)

#define SIUL2_PGPDO10_PPDO8_MASK                 (0x100U)
#define SIUL2_PGPDO10_PPDO8_SHIFT                (8U)
#define SIUL2_PGPDO10_PPDO8_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO8_SHIFT)) & SIUL2_PGPDO10_PPDO8_MASK)

#define SIUL2_PGPDO10_PPDO9_MASK                 (0x200U)
#define SIUL2_PGPDO10_PPDO9_SHIFT                (9U)
#define SIUL2_PGPDO10_PPDO9_WIDTH                (1U)
#define SIUL2_PGPDO10_PPDO9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO9_SHIFT)) & SIUL2_PGPDO10_PPDO9_MASK)

#define SIUL2_PGPDO10_PPDO10_MASK                (0x400U)
#define SIUL2_PGPDO10_PPDO10_SHIFT               (10U)
#define SIUL2_PGPDO10_PPDO10_WIDTH               (1U)
#define SIUL2_PGPDO10_PPDO10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO10_SHIFT)) & SIUL2_PGPDO10_PPDO10_MASK)

#define SIUL2_PGPDO10_PPDO11_MASK                (0x800U)
#define SIUL2_PGPDO10_PPDO11_SHIFT               (11U)
#define SIUL2_PGPDO10_PPDO11_WIDTH               (1U)
#define SIUL2_PGPDO10_PPDO11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO11_SHIFT)) & SIUL2_PGPDO10_PPDO11_MASK)

#define SIUL2_PGPDO10_PPDO12_MASK                (0x1000U)
#define SIUL2_PGPDO10_PPDO12_SHIFT               (12U)
#define SIUL2_PGPDO10_PPDO12_WIDTH               (1U)
#define SIUL2_PGPDO10_PPDO12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO12_SHIFT)) & SIUL2_PGPDO10_PPDO12_MASK)

#define SIUL2_PGPDO10_PPDO13_MASK                (0x2000U)
#define SIUL2_PGPDO10_PPDO13_SHIFT               (13U)
#define SIUL2_PGPDO10_PPDO13_WIDTH               (1U)
#define SIUL2_PGPDO10_PPDO13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO13_SHIFT)) & SIUL2_PGPDO10_PPDO13_MASK)

#define SIUL2_PGPDO10_PPDO14_MASK                (0x4000U)
#define SIUL2_PGPDO10_PPDO14_SHIFT               (14U)
#define SIUL2_PGPDO10_PPDO14_WIDTH               (1U)
#define SIUL2_PGPDO10_PPDO14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO14_SHIFT)) & SIUL2_PGPDO10_PPDO14_MASK)

#define SIUL2_PGPDO10_PPDO15_MASK                (0x8000U)
#define SIUL2_PGPDO10_PPDO15_SHIFT               (15U)
#define SIUL2_PGPDO10_PPDO15_WIDTH               (1U)
#define SIUL2_PGPDO10_PPDO15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO15_SHIFT)) & SIUL2_PGPDO10_PPDO15_MASK)
/*! @} */

/*! @name PGPDO13 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO13_PPDO4_MASK                 (0x10U)
#define SIUL2_PGPDO13_PPDO4_SHIFT                (4U)
#define SIUL2_PGPDO13_PPDO4_WIDTH                (1U)
#define SIUL2_PGPDO13_PPDO4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO4_SHIFT)) & SIUL2_PGPDO13_PPDO4_MASK)

#define SIUL2_PGPDO13_PPDO5_MASK                 (0x20U)
#define SIUL2_PGPDO13_PPDO5_SHIFT                (5U)
#define SIUL2_PGPDO13_PPDO5_WIDTH                (1U)
#define SIUL2_PGPDO13_PPDO5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO5_SHIFT)) & SIUL2_PGPDO13_PPDO5_MASK)

#define SIUL2_PGPDO13_PPDO6_MASK                 (0x40U)
#define SIUL2_PGPDO13_PPDO6_SHIFT                (6U)
#define SIUL2_PGPDO13_PPDO6_WIDTH                (1U)
#define SIUL2_PGPDO13_PPDO6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO6_SHIFT)) & SIUL2_PGPDO13_PPDO6_MASK)

#define SIUL2_PGPDO13_PPDO7_MASK                 (0x80U)
#define SIUL2_PGPDO13_PPDO7_SHIFT                (7U)
#define SIUL2_PGPDO13_PPDO7_WIDTH                (1U)
#define SIUL2_PGPDO13_PPDO7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO7_SHIFT)) & SIUL2_PGPDO13_PPDO7_MASK)

#define SIUL2_PGPDO13_PPDO8_MASK                 (0x100U)
#define SIUL2_PGPDO13_PPDO8_SHIFT                (8U)
#define SIUL2_PGPDO13_PPDO8_WIDTH                (1U)
#define SIUL2_PGPDO13_PPDO8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO8_SHIFT)) & SIUL2_PGPDO13_PPDO8_MASK)

#define SIUL2_PGPDO13_PPDO9_MASK                 (0x200U)
#define SIUL2_PGPDO13_PPDO9_SHIFT                (9U)
#define SIUL2_PGPDO13_PPDO9_WIDTH                (1U)
#define SIUL2_PGPDO13_PPDO9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO9_SHIFT)) & SIUL2_PGPDO13_PPDO9_MASK)

#define SIUL2_PGPDO13_PPDO10_MASK                (0x400U)
#define SIUL2_PGPDO13_PPDO10_SHIFT               (10U)
#define SIUL2_PGPDO13_PPDO10_WIDTH               (1U)
#define SIUL2_PGPDO13_PPDO10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO10_SHIFT)) & SIUL2_PGPDO13_PPDO10_MASK)

#define SIUL2_PGPDO13_PPDO11_MASK                (0x800U)
#define SIUL2_PGPDO13_PPDO11_SHIFT               (11U)
#define SIUL2_PGPDO13_PPDO11_WIDTH               (1U)
#define SIUL2_PGPDO13_PPDO11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO11_SHIFT)) & SIUL2_PGPDO13_PPDO11_MASK)

#define SIUL2_PGPDO13_PPDO12_MASK                (0x1000U)
#define SIUL2_PGPDO13_PPDO12_SHIFT               (12U)
#define SIUL2_PGPDO13_PPDO12_WIDTH               (1U)
#define SIUL2_PGPDO13_PPDO12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO12_SHIFT)) & SIUL2_PGPDO13_PPDO12_MASK)

#define SIUL2_PGPDO13_PPDO13_MASK                (0x2000U)
#define SIUL2_PGPDO13_PPDO13_SHIFT               (13U)
#define SIUL2_PGPDO13_PPDO13_WIDTH               (1U)
#define SIUL2_PGPDO13_PPDO13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO13_SHIFT)) & SIUL2_PGPDO13_PPDO13_MASK)

#define SIUL2_PGPDO13_PPDO14_MASK                (0x4000U)
#define SIUL2_PGPDO13_PPDO14_SHIFT               (14U)
#define SIUL2_PGPDO13_PPDO14_WIDTH               (1U)
#define SIUL2_PGPDO13_PPDO14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO14_SHIFT)) & SIUL2_PGPDO13_PPDO14_MASK)

#define SIUL2_PGPDO13_PPDO15_MASK                (0x8000U)
#define SIUL2_PGPDO13_PPDO15_SHIFT               (15U)
#define SIUL2_PGPDO13_PPDO15_WIDTH               (1U)
#define SIUL2_PGPDO13_PPDO15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO13_PPDO15_SHIFT)) & SIUL2_PGPDO13_PPDO15_MASK)
/*! @} */

/*! @name PGPDO12 - SIUL2 Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_PGPDO12_PPDO0_MASK                 (0x1U)
#define SIUL2_PGPDO12_PPDO0_SHIFT                (0U)
#define SIUL2_PGPDO12_PPDO0_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO0(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO0_SHIFT)) & SIUL2_PGPDO12_PPDO0_MASK)

#define SIUL2_PGPDO12_PPDO1_MASK                 (0x2U)
#define SIUL2_PGPDO12_PPDO1_SHIFT                (1U)
#define SIUL2_PGPDO12_PPDO1_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO1(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO1_SHIFT)) & SIUL2_PGPDO12_PPDO1_MASK)

#define SIUL2_PGPDO12_PPDO2_MASK                 (0x4U)
#define SIUL2_PGPDO12_PPDO2_SHIFT                (2U)
#define SIUL2_PGPDO12_PPDO2_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO2(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO2_SHIFT)) & SIUL2_PGPDO12_PPDO2_MASK)

#define SIUL2_PGPDO12_PPDO3_MASK                 (0x8U)
#define SIUL2_PGPDO12_PPDO3_SHIFT                (3U)
#define SIUL2_PGPDO12_PPDO3_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO3(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO3_SHIFT)) & SIUL2_PGPDO12_PPDO3_MASK)

#define SIUL2_PGPDO12_PPDO4_MASK                 (0x10U)
#define SIUL2_PGPDO12_PPDO4_SHIFT                (4U)
#define SIUL2_PGPDO12_PPDO4_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO4_SHIFT)) & SIUL2_PGPDO12_PPDO4_MASK)

#define SIUL2_PGPDO12_PPDO5_MASK                 (0x20U)
#define SIUL2_PGPDO12_PPDO5_SHIFT                (5U)
#define SIUL2_PGPDO12_PPDO5_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO5_SHIFT)) & SIUL2_PGPDO12_PPDO5_MASK)

#define SIUL2_PGPDO12_PPDO6_MASK                 (0x40U)
#define SIUL2_PGPDO12_PPDO6_SHIFT                (6U)
#define SIUL2_PGPDO12_PPDO6_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO6_SHIFT)) & SIUL2_PGPDO12_PPDO6_MASK)

#define SIUL2_PGPDO12_PPDO7_MASK                 (0x80U)
#define SIUL2_PGPDO12_PPDO7_SHIFT                (7U)
#define SIUL2_PGPDO12_PPDO7_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO7_SHIFT)) & SIUL2_PGPDO12_PPDO7_MASK)

#define SIUL2_PGPDO12_PPDO8_MASK                 (0x100U)
#define SIUL2_PGPDO12_PPDO8_SHIFT                (8U)
#define SIUL2_PGPDO12_PPDO8_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO8_SHIFT)) & SIUL2_PGPDO12_PPDO8_MASK)

#define SIUL2_PGPDO12_PPDO9_MASK                 (0x200U)
#define SIUL2_PGPDO12_PPDO9_SHIFT                (9U)
#define SIUL2_PGPDO12_PPDO9_WIDTH                (1U)
#define SIUL2_PGPDO12_PPDO9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO9_SHIFT)) & SIUL2_PGPDO12_PPDO9_MASK)

#define SIUL2_PGPDO12_PPDO10_MASK                (0x400U)
#define SIUL2_PGPDO12_PPDO10_SHIFT               (10U)
#define SIUL2_PGPDO12_PPDO10_WIDTH               (1U)
#define SIUL2_PGPDO12_PPDO10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO10_SHIFT)) & SIUL2_PGPDO12_PPDO10_MASK)

#define SIUL2_PGPDO12_PPDO11_MASK                (0x800U)
#define SIUL2_PGPDO12_PPDO11_SHIFT               (11U)
#define SIUL2_PGPDO12_PPDO11_WIDTH               (1U)
#define SIUL2_PGPDO12_PPDO11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO11_SHIFT)) & SIUL2_PGPDO12_PPDO11_MASK)

#define SIUL2_PGPDO12_PPDO12_MASK                (0x1000U)
#define SIUL2_PGPDO12_PPDO12_SHIFT               (12U)
#define SIUL2_PGPDO12_PPDO12_WIDTH               (1U)
#define SIUL2_PGPDO12_PPDO12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO12_SHIFT)) & SIUL2_PGPDO12_PPDO12_MASK)

#define SIUL2_PGPDO12_PPDO13_MASK                (0x2000U)
#define SIUL2_PGPDO12_PPDO13_SHIFT               (13U)
#define SIUL2_PGPDO12_PPDO13_WIDTH               (1U)
#define SIUL2_PGPDO12_PPDO13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO13_SHIFT)) & SIUL2_PGPDO12_PPDO13_MASK)

#define SIUL2_PGPDO12_PPDO14_MASK                (0x4000U)
#define SIUL2_PGPDO12_PPDO14_SHIFT               (14U)
#define SIUL2_PGPDO12_PPDO14_WIDTH               (1U)
#define SIUL2_PGPDO12_PPDO14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO14_SHIFT)) & SIUL2_PGPDO12_PPDO14_MASK)

#define SIUL2_PGPDO12_PPDO15_MASK                (0x8000U)
#define SIUL2_PGPDO12_PPDO15_SHIFT               (15U)
#define SIUL2_PGPDO12_PPDO15_WIDTH               (1U)
#define SIUL2_PGPDO12_PPDO15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO12_PPDO15_SHIFT)) & SIUL2_PGPDO12_PPDO15_MASK)
/*! @} */

/*! @name PGPDI1 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI1_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI1_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI1_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI0_SHIFT)) & SIUL2_PGPDI1_PPDI0_MASK)

#define SIUL2_PGPDI1_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI1_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI1_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI1_SHIFT)) & SIUL2_PGPDI1_PPDI1_MASK)

#define SIUL2_PGPDI1_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI1_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI1_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI2_SHIFT)) & SIUL2_PGPDI1_PPDI2_MASK)

#define SIUL2_PGPDI1_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI1_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI1_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI3_SHIFT)) & SIUL2_PGPDI1_PPDI3_MASK)

#define SIUL2_PGPDI1_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI1_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI1_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI4_SHIFT)) & SIUL2_PGPDI1_PPDI4_MASK)

#define SIUL2_PGPDI1_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI1_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI1_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI5_SHIFT)) & SIUL2_PGPDI1_PPDI5_MASK)

#define SIUL2_PGPDI1_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI1_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI1_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI6_SHIFT)) & SIUL2_PGPDI1_PPDI6_MASK)

#define SIUL2_PGPDI1_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI1_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI1_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI7_SHIFT)) & SIUL2_PGPDI1_PPDI7_MASK)

#define SIUL2_PGPDI1_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI1_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI1_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI8_SHIFT)) & SIUL2_PGPDI1_PPDI8_MASK)

#define SIUL2_PGPDI1_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI1_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI1_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI1_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI9_SHIFT)) & SIUL2_PGPDI1_PPDI9_MASK)

#define SIUL2_PGPDI1_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI1_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI1_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI1_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI10_SHIFT)) & SIUL2_PGPDI1_PPDI10_MASK)

#define SIUL2_PGPDI1_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI1_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI1_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI1_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI11_SHIFT)) & SIUL2_PGPDI1_PPDI11_MASK)

#define SIUL2_PGPDI1_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI1_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI1_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI1_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI12_SHIFT)) & SIUL2_PGPDI1_PPDI12_MASK)

#define SIUL2_PGPDI1_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI1_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI1_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI1_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI13_SHIFT)) & SIUL2_PGPDI1_PPDI13_MASK)

#define SIUL2_PGPDI1_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI1_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI1_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI1_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI14_SHIFT)) & SIUL2_PGPDI1_PPDI14_MASK)

#define SIUL2_PGPDI1_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI1_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI1_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI1_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI15_SHIFT)) & SIUL2_PGPDI1_PPDI15_MASK)
/*! @} */

/*! @name PGPDI0 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI0_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI0_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI0_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI0_SHIFT)) & SIUL2_PGPDI0_PPDI0_MASK)

#define SIUL2_PGPDI0_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI0_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI0_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI1_SHIFT)) & SIUL2_PGPDI0_PPDI1_MASK)

#define SIUL2_PGPDI0_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI0_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI0_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI2_SHIFT)) & SIUL2_PGPDI0_PPDI2_MASK)

#define SIUL2_PGPDI0_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI0_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI0_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI3_SHIFT)) & SIUL2_PGPDI0_PPDI3_MASK)

#define SIUL2_PGPDI0_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI0_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI0_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI4_SHIFT)) & SIUL2_PGPDI0_PPDI4_MASK)

#define SIUL2_PGPDI0_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI0_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI0_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI5_SHIFT)) & SIUL2_PGPDI0_PPDI5_MASK)

#define SIUL2_PGPDI0_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI0_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI0_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI6_SHIFT)) & SIUL2_PGPDI0_PPDI6_MASK)

#define SIUL2_PGPDI0_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI0_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI0_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI7_SHIFT)) & SIUL2_PGPDI0_PPDI7_MASK)

#define SIUL2_PGPDI0_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI0_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI0_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI8_SHIFT)) & SIUL2_PGPDI0_PPDI8_MASK)

#define SIUL2_PGPDI0_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI0_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI0_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI0_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI9_SHIFT)) & SIUL2_PGPDI0_PPDI9_MASK)

#define SIUL2_PGPDI0_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI0_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI0_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI0_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI10_SHIFT)) & SIUL2_PGPDI0_PPDI10_MASK)

#define SIUL2_PGPDI0_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI0_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI0_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI0_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI11_SHIFT)) & SIUL2_PGPDI0_PPDI11_MASK)

#define SIUL2_PGPDI0_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI0_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI0_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI0_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI12_SHIFT)) & SIUL2_PGPDI0_PPDI12_MASK)

#define SIUL2_PGPDI0_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI0_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI0_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI0_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI13_SHIFT)) & SIUL2_PGPDI0_PPDI13_MASK)

#define SIUL2_PGPDI0_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI0_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI0_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI0_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI14_SHIFT)) & SIUL2_PGPDI0_PPDI14_MASK)

#define SIUL2_PGPDI0_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI0_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI0_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI0_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI15_SHIFT)) & SIUL2_PGPDI0_PPDI15_MASK)
/*! @} */

/*! @name PGPDI3 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI3_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI3_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI3_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI0_SHIFT)) & SIUL2_PGPDI3_PPDI0_MASK)

#define SIUL2_PGPDI3_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI3_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI3_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI1_SHIFT)) & SIUL2_PGPDI3_PPDI1_MASK)

#define SIUL2_PGPDI3_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI3_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI3_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI2_SHIFT)) & SIUL2_PGPDI3_PPDI2_MASK)

#define SIUL2_PGPDI3_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI3_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI3_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI3_SHIFT)) & SIUL2_PGPDI3_PPDI3_MASK)

#define SIUL2_PGPDI3_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI3_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI3_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI4_SHIFT)) & SIUL2_PGPDI3_PPDI4_MASK)

#define SIUL2_PGPDI3_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI3_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI3_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI5_SHIFT)) & SIUL2_PGPDI3_PPDI5_MASK)

#define SIUL2_PGPDI3_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI3_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI3_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI6_SHIFT)) & SIUL2_PGPDI3_PPDI6_MASK)

#define SIUL2_PGPDI3_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI3_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI3_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI7_SHIFT)) & SIUL2_PGPDI3_PPDI7_MASK)

#define SIUL2_PGPDI3_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI3_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI3_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI8_SHIFT)) & SIUL2_PGPDI3_PPDI8_MASK)

#define SIUL2_PGPDI3_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI3_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI3_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI3_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI9_SHIFT)) & SIUL2_PGPDI3_PPDI9_MASK)

#define SIUL2_PGPDI3_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI3_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI3_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI3_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI10_SHIFT)) & SIUL2_PGPDI3_PPDI10_MASK)

#define SIUL2_PGPDI3_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI3_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI3_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI3_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI11_SHIFT)) & SIUL2_PGPDI3_PPDI11_MASK)

#define SIUL2_PGPDI3_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI3_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI3_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI3_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI12_SHIFT)) & SIUL2_PGPDI3_PPDI12_MASK)

#define SIUL2_PGPDI3_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI3_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI3_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI3_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI13_SHIFT)) & SIUL2_PGPDI3_PPDI13_MASK)

#define SIUL2_PGPDI3_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI3_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI3_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI3_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI14_SHIFT)) & SIUL2_PGPDI3_PPDI14_MASK)

#define SIUL2_PGPDI3_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI3_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI3_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI3_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI15_SHIFT)) & SIUL2_PGPDI3_PPDI15_MASK)
/*! @} */

/*! @name PGPDI2 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI2_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI2_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI2_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI0_SHIFT)) & SIUL2_PGPDI2_PPDI0_MASK)

#define SIUL2_PGPDI2_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI2_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI2_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI1_SHIFT)) & SIUL2_PGPDI2_PPDI1_MASK)

#define SIUL2_PGPDI2_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI2_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI2_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI2_SHIFT)) & SIUL2_PGPDI2_PPDI2_MASK)

#define SIUL2_PGPDI2_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI2_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI2_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI3_SHIFT)) & SIUL2_PGPDI2_PPDI3_MASK)

#define SIUL2_PGPDI2_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI2_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI2_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI4_SHIFT)) & SIUL2_PGPDI2_PPDI4_MASK)

#define SIUL2_PGPDI2_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI2_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI2_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI5_SHIFT)) & SIUL2_PGPDI2_PPDI5_MASK)

#define SIUL2_PGPDI2_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI2_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI2_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI6_SHIFT)) & SIUL2_PGPDI2_PPDI6_MASK)

#define SIUL2_PGPDI2_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI2_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI2_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI2_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI7_SHIFT)) & SIUL2_PGPDI2_PPDI7_MASK)

#define SIUL2_PGPDI2_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI2_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI2_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI2_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI10_SHIFT)) & SIUL2_PGPDI2_PPDI10_MASK)

#define SIUL2_PGPDI2_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI2_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI2_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI2_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI11_SHIFT)) & SIUL2_PGPDI2_PPDI11_MASK)

#define SIUL2_PGPDI2_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI2_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI2_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI2_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI12_SHIFT)) & SIUL2_PGPDI2_PPDI12_MASK)

#define SIUL2_PGPDI2_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI2_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI2_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI2_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI13_SHIFT)) & SIUL2_PGPDI2_PPDI13_MASK)

#define SIUL2_PGPDI2_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI2_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI2_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI2_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI14_SHIFT)) & SIUL2_PGPDI2_PPDI14_MASK)

#define SIUL2_PGPDI2_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI2_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI2_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI2_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI15_SHIFT)) & SIUL2_PGPDI2_PPDI15_MASK)
/*! @} */

/*! @name PGPDI5 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI5_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI5_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI5_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI0_SHIFT)) & SIUL2_PGPDI5_PPDI0_MASK)

#define SIUL2_PGPDI5_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI5_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI5_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI1_SHIFT)) & SIUL2_PGPDI5_PPDI1_MASK)

#define SIUL2_PGPDI5_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI5_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI5_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI2_SHIFT)) & SIUL2_PGPDI5_PPDI2_MASK)

#define SIUL2_PGPDI5_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI5_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI5_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI3_SHIFT)) & SIUL2_PGPDI5_PPDI3_MASK)

#define SIUL2_PGPDI5_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI5_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI5_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI4_SHIFT)) & SIUL2_PGPDI5_PPDI4_MASK)

#define SIUL2_PGPDI5_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI5_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI5_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI5_SHIFT)) & SIUL2_PGPDI5_PPDI5_MASK)

#define SIUL2_PGPDI5_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI5_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI5_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI6_SHIFT)) & SIUL2_PGPDI5_PPDI6_MASK)

#define SIUL2_PGPDI5_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI5_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI5_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI7_SHIFT)) & SIUL2_PGPDI5_PPDI7_MASK)

#define SIUL2_PGPDI5_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI5_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI5_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI8_SHIFT)) & SIUL2_PGPDI5_PPDI8_MASK)

#define SIUL2_PGPDI5_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI5_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI5_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI5_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI9_SHIFT)) & SIUL2_PGPDI5_PPDI9_MASK)

#define SIUL2_PGPDI5_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI5_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI5_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI5_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI10_SHIFT)) & SIUL2_PGPDI5_PPDI10_MASK)

#define SIUL2_PGPDI5_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI5_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI5_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI5_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI11_SHIFT)) & SIUL2_PGPDI5_PPDI11_MASK)

#define SIUL2_PGPDI5_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI5_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI5_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI5_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI12_SHIFT)) & SIUL2_PGPDI5_PPDI12_MASK)

#define SIUL2_PGPDI5_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI5_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI5_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI5_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI13_SHIFT)) & SIUL2_PGPDI5_PPDI13_MASK)

#define SIUL2_PGPDI5_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI5_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI5_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI5_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI14_SHIFT)) & SIUL2_PGPDI5_PPDI14_MASK)

#define SIUL2_PGPDI5_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI5_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI5_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI5_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI15_SHIFT)) & SIUL2_PGPDI5_PPDI15_MASK)
/*! @} */

/*! @name PGPDI4 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI4_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI4_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI4_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI0_SHIFT)) & SIUL2_PGPDI4_PPDI0_MASK)

#define SIUL2_PGPDI4_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI4_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI4_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI1_SHIFT)) & SIUL2_PGPDI4_PPDI1_MASK)

#define SIUL2_PGPDI4_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI4_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI4_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI2_SHIFT)) & SIUL2_PGPDI4_PPDI2_MASK)

#define SIUL2_PGPDI4_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI4_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI4_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI3_SHIFT)) & SIUL2_PGPDI4_PPDI3_MASK)

#define SIUL2_PGPDI4_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI4_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI4_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI4_SHIFT)) & SIUL2_PGPDI4_PPDI4_MASK)

#define SIUL2_PGPDI4_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI4_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI4_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI5_SHIFT)) & SIUL2_PGPDI4_PPDI5_MASK)

#define SIUL2_PGPDI4_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI4_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI4_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI6_SHIFT)) & SIUL2_PGPDI4_PPDI6_MASK)

#define SIUL2_PGPDI4_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI4_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI4_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI7_SHIFT)) & SIUL2_PGPDI4_PPDI7_MASK)

#define SIUL2_PGPDI4_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI4_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI4_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI8_SHIFT)) & SIUL2_PGPDI4_PPDI8_MASK)

#define SIUL2_PGPDI4_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI4_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI4_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI4_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI9_SHIFT)) & SIUL2_PGPDI4_PPDI9_MASK)

#define SIUL2_PGPDI4_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI4_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI4_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI4_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI10_SHIFT)) & SIUL2_PGPDI4_PPDI10_MASK)

#define SIUL2_PGPDI4_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI4_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI4_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI4_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI11_SHIFT)) & SIUL2_PGPDI4_PPDI11_MASK)

#define SIUL2_PGPDI4_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI4_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI4_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI4_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI12_SHIFT)) & SIUL2_PGPDI4_PPDI12_MASK)

#define SIUL2_PGPDI4_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI4_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI4_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI4_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI13_SHIFT)) & SIUL2_PGPDI4_PPDI13_MASK)

#define SIUL2_PGPDI4_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI4_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI4_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI4_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI14_SHIFT)) & SIUL2_PGPDI4_PPDI14_MASK)

#define SIUL2_PGPDI4_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI4_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI4_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI4_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI15_SHIFT)) & SIUL2_PGPDI4_PPDI15_MASK)
/*! @} */

/*! @name PGPDI7 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI7_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI7_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI7_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI0_SHIFT)) & SIUL2_PGPDI7_PPDI0_MASK)

#define SIUL2_PGPDI7_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI7_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI7_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI1_SHIFT)) & SIUL2_PGPDI7_PPDI1_MASK)

#define SIUL2_PGPDI7_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI7_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI7_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI2_SHIFT)) & SIUL2_PGPDI7_PPDI2_MASK)

#define SIUL2_PGPDI7_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI7_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI7_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI3_SHIFT)) & SIUL2_PGPDI7_PPDI3_MASK)

#define SIUL2_PGPDI7_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI7_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI7_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI4_SHIFT)) & SIUL2_PGPDI7_PPDI4_MASK)

#define SIUL2_PGPDI7_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI7_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI7_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI5_SHIFT)) & SIUL2_PGPDI7_PPDI5_MASK)

#define SIUL2_PGPDI7_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI7_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI7_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI6_SHIFT)) & SIUL2_PGPDI7_PPDI6_MASK)

#define SIUL2_PGPDI7_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI7_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI7_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI7_SHIFT)) & SIUL2_PGPDI7_PPDI7_MASK)

#define SIUL2_PGPDI7_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI7_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI7_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI8_SHIFT)) & SIUL2_PGPDI7_PPDI8_MASK)

#define SIUL2_PGPDI7_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI7_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI7_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI7_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI9_SHIFT)) & SIUL2_PGPDI7_PPDI9_MASK)

#define SIUL2_PGPDI7_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI7_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI7_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI7_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI10_SHIFT)) & SIUL2_PGPDI7_PPDI10_MASK)

#define SIUL2_PGPDI7_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI7_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI7_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI7_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI11_SHIFT)) & SIUL2_PGPDI7_PPDI11_MASK)

#define SIUL2_PGPDI7_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI7_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI7_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI7_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI12_SHIFT)) & SIUL2_PGPDI7_PPDI12_MASK)

#define SIUL2_PGPDI7_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI7_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI7_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI7_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI13_SHIFT)) & SIUL2_PGPDI7_PPDI13_MASK)

#define SIUL2_PGPDI7_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI7_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI7_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI7_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI14_SHIFT)) & SIUL2_PGPDI7_PPDI14_MASK)

#define SIUL2_PGPDI7_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI7_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI7_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI7_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI15_SHIFT)) & SIUL2_PGPDI7_PPDI15_MASK)
/*! @} */

/*! @name PGPDI6 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI6_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI6_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI6_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI0_SHIFT)) & SIUL2_PGPDI6_PPDI0_MASK)

#define SIUL2_PGPDI6_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI6_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI6_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI1_SHIFT)) & SIUL2_PGPDI6_PPDI1_MASK)

#define SIUL2_PGPDI6_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI6_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI6_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI2_SHIFT)) & SIUL2_PGPDI6_PPDI2_MASK)

#define SIUL2_PGPDI6_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI6_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI6_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI3_SHIFT)) & SIUL2_PGPDI6_PPDI3_MASK)

#define SIUL2_PGPDI6_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI6_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI6_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI4_SHIFT)) & SIUL2_PGPDI6_PPDI4_MASK)

#define SIUL2_PGPDI6_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI6_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI6_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI5_SHIFT)) & SIUL2_PGPDI6_PPDI5_MASK)

#define SIUL2_PGPDI6_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI6_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI6_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI6_SHIFT)) & SIUL2_PGPDI6_PPDI6_MASK)

#define SIUL2_PGPDI6_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI6_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI6_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI7_SHIFT)) & SIUL2_PGPDI6_PPDI7_MASK)

#define SIUL2_PGPDI6_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI6_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI6_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI8_SHIFT)) & SIUL2_PGPDI6_PPDI8_MASK)

#define SIUL2_PGPDI6_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI6_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI6_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI6_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI9_SHIFT)) & SIUL2_PGPDI6_PPDI9_MASK)

#define SIUL2_PGPDI6_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI6_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI6_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI6_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI10_SHIFT)) & SIUL2_PGPDI6_PPDI10_MASK)

#define SIUL2_PGPDI6_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI6_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI6_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI6_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI11_SHIFT)) & SIUL2_PGPDI6_PPDI11_MASK)

#define SIUL2_PGPDI6_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI6_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI6_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI6_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI12_SHIFT)) & SIUL2_PGPDI6_PPDI12_MASK)

#define SIUL2_PGPDI6_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI6_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI6_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI6_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI13_SHIFT)) & SIUL2_PGPDI6_PPDI13_MASK)

#define SIUL2_PGPDI6_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI6_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI6_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI6_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI14_SHIFT)) & SIUL2_PGPDI6_PPDI14_MASK)

#define SIUL2_PGPDI6_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI6_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI6_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI6_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI15_SHIFT)) & SIUL2_PGPDI6_PPDI15_MASK)
/*! @} */

/*! @name PGPDI9 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI9_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI9_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI9_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI0_SHIFT)) & SIUL2_PGPDI9_PPDI0_MASK)

#define SIUL2_PGPDI9_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI9_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI9_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI1_SHIFT)) & SIUL2_PGPDI9_PPDI1_MASK)

#define SIUL2_PGPDI9_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI9_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI9_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI2_SHIFT)) & SIUL2_PGPDI9_PPDI2_MASK)

#define SIUL2_PGPDI9_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI9_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI9_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI3_SHIFT)) & SIUL2_PGPDI9_PPDI3_MASK)

#define SIUL2_PGPDI9_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI9_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI9_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI4_SHIFT)) & SIUL2_PGPDI9_PPDI4_MASK)

#define SIUL2_PGPDI9_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI9_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI9_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI5_SHIFT)) & SIUL2_PGPDI9_PPDI5_MASK)

#define SIUL2_PGPDI9_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI9_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI9_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI6_SHIFT)) & SIUL2_PGPDI9_PPDI6_MASK)

#define SIUL2_PGPDI9_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI9_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI9_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI7_SHIFT)) & SIUL2_PGPDI9_PPDI7_MASK)

#define SIUL2_PGPDI9_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI9_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI9_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI8_SHIFT)) & SIUL2_PGPDI9_PPDI8_MASK)

#define SIUL2_PGPDI9_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI9_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI9_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI9_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI9_SHIFT)) & SIUL2_PGPDI9_PPDI9_MASK)

#define SIUL2_PGPDI9_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI9_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI9_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI9_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI10_SHIFT)) & SIUL2_PGPDI9_PPDI10_MASK)

#define SIUL2_PGPDI9_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI9_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI9_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI9_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI11_SHIFT)) & SIUL2_PGPDI9_PPDI11_MASK)

#define SIUL2_PGPDI9_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI9_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI9_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI9_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI12_SHIFT)) & SIUL2_PGPDI9_PPDI12_MASK)

#define SIUL2_PGPDI9_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI9_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI9_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI9_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI13_SHIFT)) & SIUL2_PGPDI9_PPDI13_MASK)

#define SIUL2_PGPDI9_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI9_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI9_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI9_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI14_SHIFT)) & SIUL2_PGPDI9_PPDI14_MASK)

#define SIUL2_PGPDI9_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI9_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI9_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI9_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI15_SHIFT)) & SIUL2_PGPDI9_PPDI15_MASK)
/*! @} */

/*! @name PGPDI8 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI8_PPDI0_MASK                  (0x1U)
#define SIUL2_PGPDI8_PPDI0_SHIFT                 (0U)
#define SIUL2_PGPDI8_PPDI0_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI0(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI0_SHIFT)) & SIUL2_PGPDI8_PPDI0_MASK)

#define SIUL2_PGPDI8_PPDI1_MASK                  (0x2U)
#define SIUL2_PGPDI8_PPDI1_SHIFT                 (1U)
#define SIUL2_PGPDI8_PPDI1_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI1(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI1_SHIFT)) & SIUL2_PGPDI8_PPDI1_MASK)

#define SIUL2_PGPDI8_PPDI2_MASK                  (0x4U)
#define SIUL2_PGPDI8_PPDI2_SHIFT                 (2U)
#define SIUL2_PGPDI8_PPDI2_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI2(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI2_SHIFT)) & SIUL2_PGPDI8_PPDI2_MASK)

#define SIUL2_PGPDI8_PPDI3_MASK                  (0x8U)
#define SIUL2_PGPDI8_PPDI3_SHIFT                 (3U)
#define SIUL2_PGPDI8_PPDI3_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI3(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI3_SHIFT)) & SIUL2_PGPDI8_PPDI3_MASK)

#define SIUL2_PGPDI8_PPDI4_MASK                  (0x10U)
#define SIUL2_PGPDI8_PPDI4_SHIFT                 (4U)
#define SIUL2_PGPDI8_PPDI4_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI4(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI4_SHIFT)) & SIUL2_PGPDI8_PPDI4_MASK)

#define SIUL2_PGPDI8_PPDI5_MASK                  (0x20U)
#define SIUL2_PGPDI8_PPDI5_SHIFT                 (5U)
#define SIUL2_PGPDI8_PPDI5_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI5(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI5_SHIFT)) & SIUL2_PGPDI8_PPDI5_MASK)

#define SIUL2_PGPDI8_PPDI6_MASK                  (0x40U)
#define SIUL2_PGPDI8_PPDI6_SHIFT                 (6U)
#define SIUL2_PGPDI8_PPDI6_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI6(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI6_SHIFT)) & SIUL2_PGPDI8_PPDI6_MASK)

#define SIUL2_PGPDI8_PPDI7_MASK                  (0x80U)
#define SIUL2_PGPDI8_PPDI7_SHIFT                 (7U)
#define SIUL2_PGPDI8_PPDI7_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI7(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI7_SHIFT)) & SIUL2_PGPDI8_PPDI7_MASK)

#define SIUL2_PGPDI8_PPDI8_MASK                  (0x100U)
#define SIUL2_PGPDI8_PPDI8_SHIFT                 (8U)
#define SIUL2_PGPDI8_PPDI8_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI8(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI8_SHIFT)) & SIUL2_PGPDI8_PPDI8_MASK)

#define SIUL2_PGPDI8_PPDI9_MASK                  (0x200U)
#define SIUL2_PGPDI8_PPDI9_SHIFT                 (9U)
#define SIUL2_PGPDI8_PPDI9_WIDTH                 (1U)
#define SIUL2_PGPDI8_PPDI9(x)                    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI9_SHIFT)) & SIUL2_PGPDI8_PPDI9_MASK)

#define SIUL2_PGPDI8_PPDI10_MASK                 (0x400U)
#define SIUL2_PGPDI8_PPDI10_SHIFT                (10U)
#define SIUL2_PGPDI8_PPDI10_WIDTH                (1U)
#define SIUL2_PGPDI8_PPDI10(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI10_SHIFT)) & SIUL2_PGPDI8_PPDI10_MASK)

#define SIUL2_PGPDI8_PPDI11_MASK                 (0x800U)
#define SIUL2_PGPDI8_PPDI11_SHIFT                (11U)
#define SIUL2_PGPDI8_PPDI11_WIDTH                (1U)
#define SIUL2_PGPDI8_PPDI11(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI11_SHIFT)) & SIUL2_PGPDI8_PPDI11_MASK)

#define SIUL2_PGPDI8_PPDI12_MASK                 (0x1000U)
#define SIUL2_PGPDI8_PPDI12_SHIFT                (12U)
#define SIUL2_PGPDI8_PPDI12_WIDTH                (1U)
#define SIUL2_PGPDI8_PPDI12(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI12_SHIFT)) & SIUL2_PGPDI8_PPDI12_MASK)

#define SIUL2_PGPDI8_PPDI13_MASK                 (0x2000U)
#define SIUL2_PGPDI8_PPDI13_SHIFT                (13U)
#define SIUL2_PGPDI8_PPDI13_WIDTH                (1U)
#define SIUL2_PGPDI8_PPDI13(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI13_SHIFT)) & SIUL2_PGPDI8_PPDI13_MASK)

#define SIUL2_PGPDI8_PPDI14_MASK                 (0x4000U)
#define SIUL2_PGPDI8_PPDI14_SHIFT                (14U)
#define SIUL2_PGPDI8_PPDI14_WIDTH                (1U)
#define SIUL2_PGPDI8_PPDI14(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI14_SHIFT)) & SIUL2_PGPDI8_PPDI14_MASK)

#define SIUL2_PGPDI8_PPDI15_MASK                 (0x8000U)
#define SIUL2_PGPDI8_PPDI15_SHIFT                (15U)
#define SIUL2_PGPDI8_PPDI15_WIDTH                (1U)
#define SIUL2_PGPDI8_PPDI15(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI15_SHIFT)) & SIUL2_PGPDI8_PPDI15_MASK)
/*! @} */

/*! @name PGPDI11 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI11_PPDI0_MASK                 (0x1U)
#define SIUL2_PGPDI11_PPDI0_SHIFT                (0U)
#define SIUL2_PGPDI11_PPDI0_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI0(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI0_SHIFT)) & SIUL2_PGPDI11_PPDI0_MASK)

#define SIUL2_PGPDI11_PPDI1_MASK                 (0x2U)
#define SIUL2_PGPDI11_PPDI1_SHIFT                (1U)
#define SIUL2_PGPDI11_PPDI1_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI1(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI1_SHIFT)) & SIUL2_PGPDI11_PPDI1_MASK)

#define SIUL2_PGPDI11_PPDI2_MASK                 (0x4U)
#define SIUL2_PGPDI11_PPDI2_SHIFT                (2U)
#define SIUL2_PGPDI11_PPDI2_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI2(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI2_SHIFT)) & SIUL2_PGPDI11_PPDI2_MASK)

#define SIUL2_PGPDI11_PPDI3_MASK                 (0x8U)
#define SIUL2_PGPDI11_PPDI3_SHIFT                (3U)
#define SIUL2_PGPDI11_PPDI3_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI3(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI3_SHIFT)) & SIUL2_PGPDI11_PPDI3_MASK)

#define SIUL2_PGPDI11_PPDI4_MASK                 (0x10U)
#define SIUL2_PGPDI11_PPDI4_SHIFT                (4U)
#define SIUL2_PGPDI11_PPDI4_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI4_SHIFT)) & SIUL2_PGPDI11_PPDI4_MASK)

#define SIUL2_PGPDI11_PPDI5_MASK                 (0x20U)
#define SIUL2_PGPDI11_PPDI5_SHIFT                (5U)
#define SIUL2_PGPDI11_PPDI5_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI5_SHIFT)) & SIUL2_PGPDI11_PPDI5_MASK)

#define SIUL2_PGPDI11_PPDI6_MASK                 (0x40U)
#define SIUL2_PGPDI11_PPDI6_SHIFT                (6U)
#define SIUL2_PGPDI11_PPDI6_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI6_SHIFT)) & SIUL2_PGPDI11_PPDI6_MASK)

#define SIUL2_PGPDI11_PPDI7_MASK                 (0x80U)
#define SIUL2_PGPDI11_PPDI7_SHIFT                (7U)
#define SIUL2_PGPDI11_PPDI7_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI7_SHIFT)) & SIUL2_PGPDI11_PPDI7_MASK)

#define SIUL2_PGPDI11_PPDI8_MASK                 (0x100U)
#define SIUL2_PGPDI11_PPDI8_SHIFT                (8U)
#define SIUL2_PGPDI11_PPDI8_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI8_SHIFT)) & SIUL2_PGPDI11_PPDI8_MASK)

#define SIUL2_PGPDI11_PPDI9_MASK                 (0x200U)
#define SIUL2_PGPDI11_PPDI9_SHIFT                (9U)
#define SIUL2_PGPDI11_PPDI9_WIDTH                (1U)
#define SIUL2_PGPDI11_PPDI9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI9_SHIFT)) & SIUL2_PGPDI11_PPDI9_MASK)

#define SIUL2_PGPDI11_PPDI10_MASK                (0x400U)
#define SIUL2_PGPDI11_PPDI10_SHIFT               (10U)
#define SIUL2_PGPDI11_PPDI10_WIDTH               (1U)
#define SIUL2_PGPDI11_PPDI10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI10_SHIFT)) & SIUL2_PGPDI11_PPDI10_MASK)

#define SIUL2_PGPDI11_PPDI11_MASK                (0x800U)
#define SIUL2_PGPDI11_PPDI11_SHIFT               (11U)
#define SIUL2_PGPDI11_PPDI11_WIDTH               (1U)
#define SIUL2_PGPDI11_PPDI11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI11_SHIFT)) & SIUL2_PGPDI11_PPDI11_MASK)

#define SIUL2_PGPDI11_PPDI12_MASK                (0x1000U)
#define SIUL2_PGPDI11_PPDI12_SHIFT               (12U)
#define SIUL2_PGPDI11_PPDI12_WIDTH               (1U)
#define SIUL2_PGPDI11_PPDI12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI12_SHIFT)) & SIUL2_PGPDI11_PPDI12_MASK)

#define SIUL2_PGPDI11_PPDI13_MASK                (0x2000U)
#define SIUL2_PGPDI11_PPDI13_SHIFT               (13U)
#define SIUL2_PGPDI11_PPDI13_WIDTH               (1U)
#define SIUL2_PGPDI11_PPDI13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI13_SHIFT)) & SIUL2_PGPDI11_PPDI13_MASK)

#define SIUL2_PGPDI11_PPDI14_MASK                (0x4000U)
#define SIUL2_PGPDI11_PPDI14_SHIFT               (14U)
#define SIUL2_PGPDI11_PPDI14_WIDTH               (1U)
#define SIUL2_PGPDI11_PPDI14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI14_SHIFT)) & SIUL2_PGPDI11_PPDI14_MASK)

#define SIUL2_PGPDI11_PPDI15_MASK                (0x8000U)
#define SIUL2_PGPDI11_PPDI15_SHIFT               (15U)
#define SIUL2_PGPDI11_PPDI15_WIDTH               (1U)
#define SIUL2_PGPDI11_PPDI15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI11_PPDI15_SHIFT)) & SIUL2_PGPDI11_PPDI15_MASK)
/*! @} */

/*! @name PGPDI10 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI10_PPDI0_MASK                 (0x1U)
#define SIUL2_PGPDI10_PPDI0_SHIFT                (0U)
#define SIUL2_PGPDI10_PPDI0_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI0(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI0_SHIFT)) & SIUL2_PGPDI10_PPDI0_MASK)

#define SIUL2_PGPDI10_PPDI1_MASK                 (0x2U)
#define SIUL2_PGPDI10_PPDI1_SHIFT                (1U)
#define SIUL2_PGPDI10_PPDI1_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI1(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI1_SHIFT)) & SIUL2_PGPDI10_PPDI1_MASK)

#define SIUL2_PGPDI10_PPDI2_MASK                 (0x4U)
#define SIUL2_PGPDI10_PPDI2_SHIFT                (2U)
#define SIUL2_PGPDI10_PPDI2_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI2(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI2_SHIFT)) & SIUL2_PGPDI10_PPDI2_MASK)

#define SIUL2_PGPDI10_PPDI3_MASK                 (0x8U)
#define SIUL2_PGPDI10_PPDI3_SHIFT                (3U)
#define SIUL2_PGPDI10_PPDI3_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI3(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI3_SHIFT)) & SIUL2_PGPDI10_PPDI3_MASK)

#define SIUL2_PGPDI10_PPDI4_MASK                 (0x10U)
#define SIUL2_PGPDI10_PPDI4_SHIFT                (4U)
#define SIUL2_PGPDI10_PPDI4_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI4_SHIFT)) & SIUL2_PGPDI10_PPDI4_MASK)

#define SIUL2_PGPDI10_PPDI5_MASK                 (0x20U)
#define SIUL2_PGPDI10_PPDI5_SHIFT                (5U)
#define SIUL2_PGPDI10_PPDI5_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI5_SHIFT)) & SIUL2_PGPDI10_PPDI5_MASK)

#define SIUL2_PGPDI10_PPDI6_MASK                 (0x40U)
#define SIUL2_PGPDI10_PPDI6_SHIFT                (6U)
#define SIUL2_PGPDI10_PPDI6_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI6_SHIFT)) & SIUL2_PGPDI10_PPDI6_MASK)

#define SIUL2_PGPDI10_PPDI7_MASK                 (0x80U)
#define SIUL2_PGPDI10_PPDI7_SHIFT                (7U)
#define SIUL2_PGPDI10_PPDI7_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI7_SHIFT)) & SIUL2_PGPDI10_PPDI7_MASK)

#define SIUL2_PGPDI10_PPDI8_MASK                 (0x100U)
#define SIUL2_PGPDI10_PPDI8_SHIFT                (8U)
#define SIUL2_PGPDI10_PPDI8_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI8_SHIFT)) & SIUL2_PGPDI10_PPDI8_MASK)

#define SIUL2_PGPDI10_PPDI9_MASK                 (0x200U)
#define SIUL2_PGPDI10_PPDI9_SHIFT                (9U)
#define SIUL2_PGPDI10_PPDI9_WIDTH                (1U)
#define SIUL2_PGPDI10_PPDI9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI9_SHIFT)) & SIUL2_PGPDI10_PPDI9_MASK)

#define SIUL2_PGPDI10_PPDI10_MASK                (0x400U)
#define SIUL2_PGPDI10_PPDI10_SHIFT               (10U)
#define SIUL2_PGPDI10_PPDI10_WIDTH               (1U)
#define SIUL2_PGPDI10_PPDI10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI10_SHIFT)) & SIUL2_PGPDI10_PPDI10_MASK)

#define SIUL2_PGPDI10_PPDI11_MASK                (0x800U)
#define SIUL2_PGPDI10_PPDI11_SHIFT               (11U)
#define SIUL2_PGPDI10_PPDI11_WIDTH               (1U)
#define SIUL2_PGPDI10_PPDI11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI11_SHIFT)) & SIUL2_PGPDI10_PPDI11_MASK)

#define SIUL2_PGPDI10_PPDI12_MASK                (0x1000U)
#define SIUL2_PGPDI10_PPDI12_SHIFT               (12U)
#define SIUL2_PGPDI10_PPDI12_WIDTH               (1U)
#define SIUL2_PGPDI10_PPDI12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI12_SHIFT)) & SIUL2_PGPDI10_PPDI12_MASK)

#define SIUL2_PGPDI10_PPDI13_MASK                (0x2000U)
#define SIUL2_PGPDI10_PPDI13_SHIFT               (13U)
#define SIUL2_PGPDI10_PPDI13_WIDTH               (1U)
#define SIUL2_PGPDI10_PPDI13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI13_SHIFT)) & SIUL2_PGPDI10_PPDI13_MASK)

#define SIUL2_PGPDI10_PPDI14_MASK                (0x4000U)
#define SIUL2_PGPDI10_PPDI14_SHIFT               (14U)
#define SIUL2_PGPDI10_PPDI14_WIDTH               (1U)
#define SIUL2_PGPDI10_PPDI14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI14_SHIFT)) & SIUL2_PGPDI10_PPDI14_MASK)

#define SIUL2_PGPDI10_PPDI15_MASK                (0x8000U)
#define SIUL2_PGPDI10_PPDI15_SHIFT               (15U)
#define SIUL2_PGPDI10_PPDI15_WIDTH               (1U)
#define SIUL2_PGPDI10_PPDI15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI15_SHIFT)) & SIUL2_PGPDI10_PPDI15_MASK)
/*! @} */

/*! @name PGPDI13 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI13_PPDI4_MASK                 (0x10U)
#define SIUL2_PGPDI13_PPDI4_SHIFT                (4U)
#define SIUL2_PGPDI13_PPDI4_WIDTH                (1U)
#define SIUL2_PGPDI13_PPDI4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI4_SHIFT)) & SIUL2_PGPDI13_PPDI4_MASK)

#define SIUL2_PGPDI13_PPDI5_MASK                 (0x20U)
#define SIUL2_PGPDI13_PPDI5_SHIFT                (5U)
#define SIUL2_PGPDI13_PPDI5_WIDTH                (1U)
#define SIUL2_PGPDI13_PPDI5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI5_SHIFT)) & SIUL2_PGPDI13_PPDI5_MASK)

#define SIUL2_PGPDI13_PPDI6_MASK                 (0x40U)
#define SIUL2_PGPDI13_PPDI6_SHIFT                (6U)
#define SIUL2_PGPDI13_PPDI6_WIDTH                (1U)
#define SIUL2_PGPDI13_PPDI6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI6_SHIFT)) & SIUL2_PGPDI13_PPDI6_MASK)

#define SIUL2_PGPDI13_PPDI7_MASK                 (0x80U)
#define SIUL2_PGPDI13_PPDI7_SHIFT                (7U)
#define SIUL2_PGPDI13_PPDI7_WIDTH                (1U)
#define SIUL2_PGPDI13_PPDI7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI7_SHIFT)) & SIUL2_PGPDI13_PPDI7_MASK)

#define SIUL2_PGPDI13_PPDI8_MASK                 (0x100U)
#define SIUL2_PGPDI13_PPDI8_SHIFT                (8U)
#define SIUL2_PGPDI13_PPDI8_WIDTH                (1U)
#define SIUL2_PGPDI13_PPDI8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI8_SHIFT)) & SIUL2_PGPDI13_PPDI8_MASK)

#define SIUL2_PGPDI13_PPDI9_MASK                 (0x200U)
#define SIUL2_PGPDI13_PPDI9_SHIFT                (9U)
#define SIUL2_PGPDI13_PPDI9_WIDTH                (1U)
#define SIUL2_PGPDI13_PPDI9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI9_SHIFT)) & SIUL2_PGPDI13_PPDI9_MASK)

#define SIUL2_PGPDI13_PPDI10_MASK                (0x400U)
#define SIUL2_PGPDI13_PPDI10_SHIFT               (10U)
#define SIUL2_PGPDI13_PPDI10_WIDTH               (1U)
#define SIUL2_PGPDI13_PPDI10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI10_SHIFT)) & SIUL2_PGPDI13_PPDI10_MASK)

#define SIUL2_PGPDI13_PPDI11_MASK                (0x800U)
#define SIUL2_PGPDI13_PPDI11_SHIFT               (11U)
#define SIUL2_PGPDI13_PPDI11_WIDTH               (1U)
#define SIUL2_PGPDI13_PPDI11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI11_SHIFT)) & SIUL2_PGPDI13_PPDI11_MASK)

#define SIUL2_PGPDI13_PPDI12_MASK                (0x1000U)
#define SIUL2_PGPDI13_PPDI12_SHIFT               (12U)
#define SIUL2_PGPDI13_PPDI12_WIDTH               (1U)
#define SIUL2_PGPDI13_PPDI12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI12_SHIFT)) & SIUL2_PGPDI13_PPDI12_MASK)

#define SIUL2_PGPDI13_PPDI13_MASK                (0x2000U)
#define SIUL2_PGPDI13_PPDI13_SHIFT               (13U)
#define SIUL2_PGPDI13_PPDI13_WIDTH               (1U)
#define SIUL2_PGPDI13_PPDI13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI13_SHIFT)) & SIUL2_PGPDI13_PPDI13_MASK)

#define SIUL2_PGPDI13_PPDI14_MASK                (0x4000U)
#define SIUL2_PGPDI13_PPDI14_SHIFT               (14U)
#define SIUL2_PGPDI13_PPDI14_WIDTH               (1U)
#define SIUL2_PGPDI13_PPDI14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI14_SHIFT)) & SIUL2_PGPDI13_PPDI14_MASK)

#define SIUL2_PGPDI13_PPDI15_MASK                (0x8000U)
#define SIUL2_PGPDI13_PPDI15_SHIFT               (15U)
#define SIUL2_PGPDI13_PPDI15_WIDTH               (1U)
#define SIUL2_PGPDI13_PPDI15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI13_PPDI15_SHIFT)) & SIUL2_PGPDI13_PPDI15_MASK)
/*! @} */

/*! @name PGPDI12 - SIUL2 Parallel GPIO Pad Data In Register */
/*! @{ */

#define SIUL2_PGPDI12_PPDI0_MASK                 (0x1U)
#define SIUL2_PGPDI12_PPDI0_SHIFT                (0U)
#define SIUL2_PGPDI12_PPDI0_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI0(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI0_SHIFT)) & SIUL2_PGPDI12_PPDI0_MASK)

#define SIUL2_PGPDI12_PPDI1_MASK                 (0x2U)
#define SIUL2_PGPDI12_PPDI1_SHIFT                (1U)
#define SIUL2_PGPDI12_PPDI1_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI1(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI1_SHIFT)) & SIUL2_PGPDI12_PPDI1_MASK)

#define SIUL2_PGPDI12_PPDI2_MASK                 (0x4U)
#define SIUL2_PGPDI12_PPDI2_SHIFT                (2U)
#define SIUL2_PGPDI12_PPDI2_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI2(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI2_SHIFT)) & SIUL2_PGPDI12_PPDI2_MASK)

#define SIUL2_PGPDI12_PPDI3_MASK                 (0x8U)
#define SIUL2_PGPDI12_PPDI3_SHIFT                (3U)
#define SIUL2_PGPDI12_PPDI3_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI3(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI3_SHIFT)) & SIUL2_PGPDI12_PPDI3_MASK)

#define SIUL2_PGPDI12_PPDI4_MASK                 (0x10U)
#define SIUL2_PGPDI12_PPDI4_SHIFT                (4U)
#define SIUL2_PGPDI12_PPDI4_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI4(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI4_SHIFT)) & SIUL2_PGPDI12_PPDI4_MASK)

#define SIUL2_PGPDI12_PPDI5_MASK                 (0x20U)
#define SIUL2_PGPDI12_PPDI5_SHIFT                (5U)
#define SIUL2_PGPDI12_PPDI5_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI5(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI5_SHIFT)) & SIUL2_PGPDI12_PPDI5_MASK)

#define SIUL2_PGPDI12_PPDI6_MASK                 (0x40U)
#define SIUL2_PGPDI12_PPDI6_SHIFT                (6U)
#define SIUL2_PGPDI12_PPDI6_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI6(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI6_SHIFT)) & SIUL2_PGPDI12_PPDI6_MASK)

#define SIUL2_PGPDI12_PPDI7_MASK                 (0x80U)
#define SIUL2_PGPDI12_PPDI7_SHIFT                (7U)
#define SIUL2_PGPDI12_PPDI7_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI7(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI7_SHIFT)) & SIUL2_PGPDI12_PPDI7_MASK)

#define SIUL2_PGPDI12_PPDI8_MASK                 (0x100U)
#define SIUL2_PGPDI12_PPDI8_SHIFT                (8U)
#define SIUL2_PGPDI12_PPDI8_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI8(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI8_SHIFT)) & SIUL2_PGPDI12_PPDI8_MASK)

#define SIUL2_PGPDI12_PPDI9_MASK                 (0x200U)
#define SIUL2_PGPDI12_PPDI9_SHIFT                (9U)
#define SIUL2_PGPDI12_PPDI9_WIDTH                (1U)
#define SIUL2_PGPDI12_PPDI9(x)                   (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI9_SHIFT)) & SIUL2_PGPDI12_PPDI9_MASK)

#define SIUL2_PGPDI12_PPDI10_MASK                (0x400U)
#define SIUL2_PGPDI12_PPDI10_SHIFT               (10U)
#define SIUL2_PGPDI12_PPDI10_WIDTH               (1U)
#define SIUL2_PGPDI12_PPDI10(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI10_SHIFT)) & SIUL2_PGPDI12_PPDI10_MASK)

#define SIUL2_PGPDI12_PPDI11_MASK                (0x800U)
#define SIUL2_PGPDI12_PPDI11_SHIFT               (11U)
#define SIUL2_PGPDI12_PPDI11_WIDTH               (1U)
#define SIUL2_PGPDI12_PPDI11(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI11_SHIFT)) & SIUL2_PGPDI12_PPDI11_MASK)

#define SIUL2_PGPDI12_PPDI12_MASK                (0x1000U)
#define SIUL2_PGPDI12_PPDI12_SHIFT               (12U)
#define SIUL2_PGPDI12_PPDI12_WIDTH               (1U)
#define SIUL2_PGPDI12_PPDI12(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI12_SHIFT)) & SIUL2_PGPDI12_PPDI12_MASK)

#define SIUL2_PGPDI12_PPDI13_MASK                (0x2000U)
#define SIUL2_PGPDI12_PPDI13_SHIFT               (13U)
#define SIUL2_PGPDI12_PPDI13_WIDTH               (1U)
#define SIUL2_PGPDI12_PPDI13(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI13_SHIFT)) & SIUL2_PGPDI12_PPDI13_MASK)

#define SIUL2_PGPDI12_PPDI14_MASK                (0x4000U)
#define SIUL2_PGPDI12_PPDI14_SHIFT               (14U)
#define SIUL2_PGPDI12_PPDI14_WIDTH               (1U)
#define SIUL2_PGPDI12_PPDI14(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI14_SHIFT)) & SIUL2_PGPDI12_PPDI14_MASK)

#define SIUL2_PGPDI12_PPDI15_MASK                (0x8000U)
#define SIUL2_PGPDI12_PPDI15_SHIFT               (15U)
#define SIUL2_PGPDI12_PPDI15_WIDTH               (1U)
#define SIUL2_PGPDI12_PPDI15(x)                  (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI12_PPDI15_SHIFT)) & SIUL2_PGPDI12_PPDI15_MASK)
/*! @} */

/*! @name MPGPDO - SIUL2 Masked Parallel GPIO Pad Data Out Register */
/*! @{ */

#define SIUL2_MPGPDO_MPPDO0_MASK                 (0x1U)
#define SIUL2_MPGPDO_MPPDO0_SHIFT                (0U)
#define SIUL2_MPGPDO_MPPDO0_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO0(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO0_SHIFT)) & SIUL2_MPGPDO_MPPDO0_MASK)

#define SIUL2_MPGPDO_MPPDO1_MASK                 (0x2U)
#define SIUL2_MPGPDO_MPPDO1_SHIFT                (1U)
#define SIUL2_MPGPDO_MPPDO1_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO1(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO1_SHIFT)) & SIUL2_MPGPDO_MPPDO1_MASK)

#define SIUL2_MPGPDO_MPPDO2_MASK                 (0x4U)
#define SIUL2_MPGPDO_MPPDO2_SHIFT                (2U)
#define SIUL2_MPGPDO_MPPDO2_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO2(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO2_SHIFT)) & SIUL2_MPGPDO_MPPDO2_MASK)

#define SIUL2_MPGPDO_MPPDO3_MASK                 (0x8U)
#define SIUL2_MPGPDO_MPPDO3_SHIFT                (3U)
#define SIUL2_MPGPDO_MPPDO3_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO3(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO3_SHIFT)) & SIUL2_MPGPDO_MPPDO3_MASK)

#define SIUL2_MPGPDO_MPPDO4_MASK                 (0x10U)
#define SIUL2_MPGPDO_MPPDO4_SHIFT                (4U)
#define SIUL2_MPGPDO_MPPDO4_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO4(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO4_SHIFT)) & SIUL2_MPGPDO_MPPDO4_MASK)

#define SIUL2_MPGPDO_MPPDO5_MASK                 (0x20U)
#define SIUL2_MPGPDO_MPPDO5_SHIFT                (5U)
#define SIUL2_MPGPDO_MPPDO5_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO5(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO5_SHIFT)) & SIUL2_MPGPDO_MPPDO5_MASK)

#define SIUL2_MPGPDO_MPPDO6_MASK                 (0x40U)
#define SIUL2_MPGPDO_MPPDO6_SHIFT                (6U)
#define SIUL2_MPGPDO_MPPDO6_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO6(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO6_SHIFT)) & SIUL2_MPGPDO_MPPDO6_MASK)

#define SIUL2_MPGPDO_MPPDO7_MASK                 (0x80U)
#define SIUL2_MPGPDO_MPPDO7_SHIFT                (7U)
#define SIUL2_MPGPDO_MPPDO7_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO7(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO7_SHIFT)) & SIUL2_MPGPDO_MPPDO7_MASK)

#define SIUL2_MPGPDO_MPPDO8_MASK                 (0x100U)
#define SIUL2_MPGPDO_MPPDO8_SHIFT                (8U)
#define SIUL2_MPGPDO_MPPDO8_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO8(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO8_SHIFT)) & SIUL2_MPGPDO_MPPDO8_MASK)

#define SIUL2_MPGPDO_MPPDO9_MASK                 (0x200U)
#define SIUL2_MPGPDO_MPPDO9_SHIFT                (9U)
#define SIUL2_MPGPDO_MPPDO9_WIDTH                (1U)
#define SIUL2_MPGPDO_MPPDO9(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO9_SHIFT)) & SIUL2_MPGPDO_MPPDO9_MASK)

#define SIUL2_MPGPDO_MPPDO10_MASK                (0x400U)
#define SIUL2_MPGPDO_MPPDO10_SHIFT               (10U)
#define SIUL2_MPGPDO_MPPDO10_WIDTH               (1U)
#define SIUL2_MPGPDO_MPPDO10(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO10_SHIFT)) & SIUL2_MPGPDO_MPPDO10_MASK)

#define SIUL2_MPGPDO_MPPDO11_MASK                (0x800U)
#define SIUL2_MPGPDO_MPPDO11_SHIFT               (11U)
#define SIUL2_MPGPDO_MPPDO11_WIDTH               (1U)
#define SIUL2_MPGPDO_MPPDO11(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO11_SHIFT)) & SIUL2_MPGPDO_MPPDO11_MASK)

#define SIUL2_MPGPDO_MPPDO12_MASK                (0x1000U)
#define SIUL2_MPGPDO_MPPDO12_SHIFT               (12U)
#define SIUL2_MPGPDO_MPPDO12_WIDTH               (1U)
#define SIUL2_MPGPDO_MPPDO12(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO12_SHIFT)) & SIUL2_MPGPDO_MPPDO12_MASK)

#define SIUL2_MPGPDO_MPPDO13_MASK                (0x2000U)
#define SIUL2_MPGPDO_MPPDO13_SHIFT               (13U)
#define SIUL2_MPGPDO_MPPDO13_WIDTH               (1U)
#define SIUL2_MPGPDO_MPPDO13(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO13_SHIFT)) & SIUL2_MPGPDO_MPPDO13_MASK)

#define SIUL2_MPGPDO_MPPDO14_MASK                (0x4000U)
#define SIUL2_MPGPDO_MPPDO14_SHIFT               (14U)
#define SIUL2_MPGPDO_MPPDO14_WIDTH               (1U)
#define SIUL2_MPGPDO_MPPDO14(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO14_SHIFT)) & SIUL2_MPGPDO_MPPDO14_MASK)

#define SIUL2_MPGPDO_MPPDO15_MASK                (0x8000U)
#define SIUL2_MPGPDO_MPPDO15_SHIFT               (15U)
#define SIUL2_MPGPDO_MPPDO15_WIDTH               (1U)
#define SIUL2_MPGPDO_MPPDO15(x)                  (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO15_SHIFT)) & SIUL2_MPGPDO_MPPDO15_MASK)

#define SIUL2_MPGPDO_MASK0_MASK                  (0x10000U)
#define SIUL2_MPGPDO_MASK0_SHIFT                 (16U)
#define SIUL2_MPGPDO_MASK0_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK0(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK0_SHIFT)) & SIUL2_MPGPDO_MASK0_MASK)

#define SIUL2_MPGPDO_MASK1_MASK                  (0x20000U)
#define SIUL2_MPGPDO_MASK1_SHIFT                 (17U)
#define SIUL2_MPGPDO_MASK1_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK1(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK1_SHIFT)) & SIUL2_MPGPDO_MASK1_MASK)

#define SIUL2_MPGPDO_MASK2_MASK                  (0x40000U)
#define SIUL2_MPGPDO_MASK2_SHIFT                 (18U)
#define SIUL2_MPGPDO_MASK2_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK2(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK2_SHIFT)) & SIUL2_MPGPDO_MASK2_MASK)

#define SIUL2_MPGPDO_MASK3_MASK                  (0x80000U)
#define SIUL2_MPGPDO_MASK3_SHIFT                 (19U)
#define SIUL2_MPGPDO_MASK3_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK3(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK3_SHIFT)) & SIUL2_MPGPDO_MASK3_MASK)

#define SIUL2_MPGPDO_MASK4_MASK                  (0x100000U)
#define SIUL2_MPGPDO_MASK4_SHIFT                 (20U)
#define SIUL2_MPGPDO_MASK4_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK4(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK4_SHIFT)) & SIUL2_MPGPDO_MASK4_MASK)

#define SIUL2_MPGPDO_MASK5_MASK                  (0x200000U)
#define SIUL2_MPGPDO_MASK5_SHIFT                 (21U)
#define SIUL2_MPGPDO_MASK5_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK5(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK5_SHIFT)) & SIUL2_MPGPDO_MASK5_MASK)

#define SIUL2_MPGPDO_MASK6_MASK                  (0x400000U)
#define SIUL2_MPGPDO_MASK6_SHIFT                 (22U)
#define SIUL2_MPGPDO_MASK6_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK6(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK6_SHIFT)) & SIUL2_MPGPDO_MASK6_MASK)

#define SIUL2_MPGPDO_MASK7_MASK                  (0x800000U)
#define SIUL2_MPGPDO_MASK7_SHIFT                 (23U)
#define SIUL2_MPGPDO_MASK7_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK7(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK7_SHIFT)) & SIUL2_MPGPDO_MASK7_MASK)

#define SIUL2_MPGPDO_MASK8_MASK                  (0x1000000U)
#define SIUL2_MPGPDO_MASK8_SHIFT                 (24U)
#define SIUL2_MPGPDO_MASK8_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK8(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK8_SHIFT)) & SIUL2_MPGPDO_MASK8_MASK)

#define SIUL2_MPGPDO_MASK9_MASK                  (0x2000000U)
#define SIUL2_MPGPDO_MASK9_SHIFT                 (25U)
#define SIUL2_MPGPDO_MASK9_WIDTH                 (1U)
#define SIUL2_MPGPDO_MASK9(x)                    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK9_SHIFT)) & SIUL2_MPGPDO_MASK9_MASK)

#define SIUL2_MPGPDO_MASK10_MASK                 (0x4000000U)
#define SIUL2_MPGPDO_MASK10_SHIFT                (26U)
#define SIUL2_MPGPDO_MASK10_WIDTH                (1U)
#define SIUL2_MPGPDO_MASK10(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK10_SHIFT)) & SIUL2_MPGPDO_MASK10_MASK)

#define SIUL2_MPGPDO_MASK11_MASK                 (0x8000000U)
#define SIUL2_MPGPDO_MASK11_SHIFT                (27U)
#define SIUL2_MPGPDO_MASK11_WIDTH                (1U)
#define SIUL2_MPGPDO_MASK11(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK11_SHIFT)) & SIUL2_MPGPDO_MASK11_MASK)

#define SIUL2_MPGPDO_MASK12_MASK                 (0x10000000U)
#define SIUL2_MPGPDO_MASK12_SHIFT                (28U)
#define SIUL2_MPGPDO_MASK12_WIDTH                (1U)
#define SIUL2_MPGPDO_MASK12(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK12_SHIFT)) & SIUL2_MPGPDO_MASK12_MASK)

#define SIUL2_MPGPDO_MASK13_MASK                 (0x20000000U)
#define SIUL2_MPGPDO_MASK13_SHIFT                (29U)
#define SIUL2_MPGPDO_MASK13_WIDTH                (1U)
#define SIUL2_MPGPDO_MASK13(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK13_SHIFT)) & SIUL2_MPGPDO_MASK13_MASK)

#define SIUL2_MPGPDO_MASK14_MASK                 (0x40000000U)
#define SIUL2_MPGPDO_MASK14_SHIFT                (30U)
#define SIUL2_MPGPDO_MASK14_WIDTH                (1U)
#define SIUL2_MPGPDO_MASK14(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK14_SHIFT)) & SIUL2_MPGPDO_MASK14_MASK)

#define SIUL2_MPGPDO_MASK15_MASK                 (0x80000000U)
#define SIUL2_MPGPDO_MASK15_SHIFT                (31U)
#define SIUL2_MPGPDO_MASK15_WIDTH                (1U)
#define SIUL2_MPGPDO_MASK15(x)                   (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK15_SHIFT)) & SIUL2_MPGPDO_MASK15_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SIUL2_Register_Masks */

/*!
 * @}
 */ /* end of group SIUL2_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SIUL2_H_) */
