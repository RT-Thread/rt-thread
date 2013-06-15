/** @file sys_pcr.h
*   @brief PCR Driver Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __SYS_PCR_H__
#define __SYS_PCR_H__

#include "reg_pcr.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* PCR General Definitions */

typedef uint32 peripheralFrame_CS_t;

#define PeripheralFrame_CS0 0U
#define PeripheralFrame_CS1 1U
#define PeripheralFrame_CS2 2U
#define PeripheralFrame_CS3 3U
#define PeripheralFrame_CS4 4U
#define PeripheralFrame_CS5 5U
#define PeripheralFrame_CS6 6U
#define PeripheralFrame_CS7 7U
#define PeripheralFrame_CS8 8U
#define PeripheralFrame_CS9 9U
#define PeripheralFrame_CS10 10U
#define PeripheralFrame_CS11 11U
#define PeripheralFrame_CS12 12U
#define PeripheralFrame_CS13 13U
#define PeripheralFrame_CS14 14U
#define PeripheralFrame_CS15 15U
#define PeripheralFrame_CS16 16U
#define PeripheralFrame_CS17 17U
#define PeripheralFrame_CS18 18U
#define PeripheralFrame_CS19 19U
#define PeripheralFrame_CS20 20U
#define PeripheralFrame_CS21 21U
#define PeripheralFrame_CS22 22U
#define PeripheralFrame_CS23 23U
#define PeripheralFrame_CS24 24U
#define PeripheralFrame_CS25 25U
#define PeripheralFrame_CS26 26U
#define PeripheralFrame_CS27 27U
#define PeripheralFrame_CS28 28U
#define PeripheralFrame_CS29 29U
#define PeripheralFrame_CS30 30U
#define PeripheralFrame_CS31 31U

/* USER CODE BEGIN (1) */
/* USER CODE END */


typedef uint32 quadrant_Select_t;
#define Quadrant0 1U
#define Quadrant1 2U
#define Quadrant2 4U
#define Quadrant3 8U

/* USER CODE BEGIN (2) */
/* USER CODE END */

/** @typedef peripheral_Frame_Select_t
*   @brief PCR Peripheral Frame Type Definition
*
*   This type is used to access the PCR peripheral Frame configuration register.
*/
typedef struct peripheral_Frame_Select
{
	peripheralFrame_CS_t Peripheral_CS;
	quadrant_Select_t Peripheral_Quadrant;
}peripheral_Frame_Select_t;

/* USER CODE BEGIN (3) */
/* USER CODE END */

/** @typedef peripheral_Quad_ChipSelect_t
*   @brief PCR Peripheral Frame registers Type Definition
*
*   This type is used to access all the PCR peripheral Frame configuration registers.
*/
typedef struct peripheral_Quad_ChipSelect
{
	uint32 Peripheral_Quad0_3_CS0_7;
	uint32 Peripheral_Quad4_7_CS8_15;
	uint32 Peripheral_Quad8_11_CS16_23;
	uint32 Peripheral_Quad12_15_CS24_31;
}peripheral_Quad_ChipSelect_t;

/* USER CODE BEGIN (4) */
/* USER CODE END */

/** @typedef peripheral_Memory_ChipSelect_t
*   @brief PCR Peripheral Memory Frame registers Type Definition
*
*   This type is used to access all the PCR peripheral Memory Frame configuration registers.
*/
typedef struct peripheral_Memory_ChipSelect
{
	uint32 Peripheral_Mem_CS0_31;
	uint32 Peripheral_Mem_CS32_63;
}peripheral_Memory_ChipSelect_t;

/* USER CODE BEGIN (5) */
/* USER CODE END */

typedef uint32 peripheral_MemoryFrame_CS_t;

#define PeripheralMemoryFrame_CS0 0U
#define PeripheralMemoryFrame_CS1 1U
#define PeripheralMemoryFrame_CS2 2U
#define PeripheralMemoryFrame_CS3 3U
#define PeripheralMemoryFrame_CS4 4U
#define PeripheralMemoryFrame_CS5 5U
#define PeripheralMemoryFrame_CS6 6U
#define PeripheralMemoryFrame_CS7 7U
#define PeripheralMemoryFrame_CS8 8U
#define PeripheralMemoryFrame_CS9 9U
#define PeripheralMemoryFrame_CS10 10U
#define PeripheralMemoryFrame_CS11 11U
#define PeripheralMemoryFrame_CS12 12U
#define PeripheralMemoryFrame_CS13 13U
#define PeripheralMemoryFrame_CS14 14U
#define PeripheralMemoryFrame_CS15 15U
#define PeripheralMemoryFrame_CS16 16U
#define PeripheralMemoryFrame_CS17 17U
#define PeripheralMemoryFrame_CS18 18U
#define PeripheralMemoryFrame_CS19 19U
#define PeripheralMemoryFrame_CS20 20U
#define PeripheralMemoryFrame_CS21 21U
#define PeripheralMemoryFrame_CS22 22U
#define PeripheralMemoryFrame_CS23 23U
#define PeripheralMemoryFrame_CS24 24U
#define PeripheralMemoryFrame_CS25 25U
#define PeripheralMemoryFrame_CS26 26U
#define PeripheralMemoryFrame_CS27 27U
#define PeripheralMemoryFrame_CS28 28U
#define PeripheralMemoryFrame_CS29 29U
#define PeripheralMemoryFrame_CS30 30U
#define PeripheralMemoryFrame_CS31 31U
#define PeripheralMemoryFrame_CS32 32U
#define PeripheralMemoryFrame_CS33 33U
#define PeripheralMemoryFrame_CS34 34U
#define PeripheralMemoryFrame_CS35 35U
#define PeripheralMemoryFrame_CS36 36U
#define PeripheralMemoryFrame_CS37 37U
#define PeripheralMemoryFrame_CS38 38U
#define PeripheralMemoryFrame_CS39 39U
#define PeripheralMemoryFrame_CS40 40U
#define PeripheralMemoryFrame_CS41 41U
#define PeripheralMemoryFrame_CS42 42U
#define PeripheralMemoryFrame_CS43 43U
#define PeripheralMemoryFrame_CS44 44U
#define PeripheralMemoryFrame_CS45 45U
#define PeripheralMemoryFrame_CS46 46U
#define PeripheralMemoryFrame_CS47 47U
#define PeripheralMemoryFrame_CS48 48U
#define PeripheralMemoryFrame_CS49 49U
#define PeripheralMemoryFrame_CS50 50U
#define PeripheralMemoryFrame_CS51 51U
#define PeripheralMemoryFrame_CS52 52U
#define PeripheralMemoryFrame_CS53 53U
#define PeripheralMemoryFrame_CS54 54U
#define PeripheralMemoryFrame_CS55 55U
#define PeripheralMemoryFrame_CS56 56U
#define PeripheralMemoryFrame_CS57 57U
#define PeripheralMemoryFrame_CS58 58U
#define PeripheralMemoryFrame_CS59 59U
#define PeripheralMemoryFrame_CS60 60U
#define PeripheralMemoryFrame_CS61 61U
#define PeripheralMemoryFrame_CS62 62U
#define PeripheralMemoryFrame_CS63 63U

/* USER CODE BEGIN (6) */
/* USER CODE END */

/**
 * @defgroup PCR PCR
 * @brief Peripheral Central Resource Controller
 *
 * The PCR manages the accesses to the peripheral registers and peripheral
 * memories. It provides a global reset for all the peripherals. It also supports the
 * capability to selectively enable or disable the clock for each peripheral
 * individually. The PCR also manages the accesses to the system module
 * registers required to configure the device’s clocks, interrupts, and so on. The
 * system module registers also include status flags for indicating exception
 * conditions – resets, aborts, errors, interrupts.
 *
 * Related files:
 * - reg_pcr.h
 * - sys_pcr.h
 * - sys_pcr.c
 *
 * @addtogroup PCR
 * @{
 */
 
/* PCR Interface Functions */

void peripheral_Frame_Protection_Set(peripheral_Frame_Select_t peripheral_Frame);
void peripheral_Frame_Protection_Clr(peripheral_Frame_Select_t peripheral_Frame);
void peripheral_Frame_Powerdown_Set(peripheral_Frame_Select_t peripheral_Frame);
void peripheral_Frame_Powerdown_Clr(peripheral_Frame_Select_t peripheral_Frame);

void peripheral_Protection_Set(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
void peripheral_Protection_Clr(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
peripheral_Quad_ChipSelect_t peripheral_Protection_Status(void);
void peripheral_Powerdown_Set(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
void peripheral_Powerdown_Clr(peripheral_Quad_ChipSelect_t peripheral_Quad_CS);
peripheral_Quad_ChipSelect_t peripheral_Powerdown_Status(void);

void peripheral_Memory_Protection_Set(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
void peripheral_Memory_Protection_Clr(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
peripheral_Memory_ChipSelect_t peripheral_Memory_Protection_Status(void);
void peripheral_Memory_Powerdown_Set(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
void peripheral_Memory_Powerdown_Clr(peripheral_Memory_ChipSelect_t peripheral_Memory_CS);
peripheral_Memory_ChipSelect_t Periipheral_Memory_Powerdown_Status(void);

void peripheral_Mem_Frame_Prot_Set(peripheral_MemoryFrame_CS_t peripheral_Memory_Frame_CS);
void peripheral_Mem_Frame_Prot_Clr(peripheral_MemoryFrame_CS_t peripheral_Memory_Frame_CS);
void peripheral_Mem_Frame_Pwrdwn_Set(peripheral_MemoryFrame_CS_t peripheral_Memory_Frame_CS);
void peripheral_Mem_Frame_Pwrdwn_Clr (peripheral_MemoryFrame_CS_t peripheral_Memory_Frame_CS);

/**@}*/
/* USER CODE BEGIN (7) */
/* USER CODE END */

#endif
