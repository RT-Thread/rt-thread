/**
 * \file
 *
 * \brief Instance description for IDAU
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

/* file generated from device description version 2019-01-31T14:29:25Z */
#ifndef _SAML10_IDAU_INSTANCE_H_
#define _SAML10_IDAU_INSTANCE_H_

/* ========== Register definition for IDAU peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))



#else



#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for IDAU peripheral ========== */
#define IDAU_GRANULARITY_BOOTPROT                0x100      /* BOOTPROT region granularity */
#define IDAU_REGION_BOOTROM                      0x09       /* Boot ROM region number */
#define IDAU_REGION_IOBUS                        0x00       /* IOBUS region number (invalid) */
#define IDAU_REGION_OTHER                        0x00       /* Others region number (invalid) */
#define IDAU_REGION_PERIPHERALS                  0x00       /* Peripherals region number (invalid) */
#define IDAU_INSTANCE_ID                         32         

#endif /* _SAML10_IDAU_INSTANCE_ */
