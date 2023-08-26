/******************************************************************************
 * @file     startup_ARMCM0.c
 * @brief    CMSIS-Core(M) Device Startup File for a Cortex-M0 Device
 * @version  V2.0.2
 * @date     15. November 2019
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ARMCM0.h"

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void __NO_RETURN Default_Handler(void);
void __NO_RETURN Reset_Handler  (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void Interrupt0_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt2_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt3_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt4_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt5_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt6_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt7_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt8_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt9_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[48];
       const VECTOR_TABLE_Type __VECTOR_TABLE[48] __VECTOR_TABLE_ATTRIBUTE = {
  (VECTOR_TABLE_Type)(&__INITIAL_SP),       /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Reset Handler */
  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVCall Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */

  /* Interrupts */
  Interrupt0_Handler,                       /*   0 Interrupt 0 */
  Interrupt1_Handler,                       /*   1 Interrupt 1 */
  Interrupt2_Handler,                       /*   2 Interrupt 2 */
  Interrupt3_Handler,                       /*   3 Interrupt 3 */
  Interrupt4_Handler,                       /*   4 Interrupt 4 */
  Interrupt5_Handler,                       /*   5 Interrupt 5 */
  Interrupt6_Handler,                       /*   6 Interrupt 6 */
  Interrupt7_Handler,                       /*   7 Interrupt 7 */
  Interrupt8_Handler,                       /*   8 Interrupt 8 */
  Interrupt9_Handler                        /*   9 Interrupt 9 */
                                            /* Interrupts 10..31 are left out */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
  SystemInit();                             /* CMSIS System Initialization */
  __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}

/*----------------------------------------------------------------------------
  Hard Fault Handler
 *----------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
  while(1);
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}
