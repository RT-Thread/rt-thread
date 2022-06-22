/**
 * \file
 *
 * \brief Instance description for RSTC
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
#ifndef _SAML10_RSTC_INSTANCE_H_
#define _SAML10_RSTC_INSTANCE_H_

/* ========== Register definition for RSTC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_RSTC_RCAUSE         (0x40000C00) /**< (RSTC) Reset Cause */

#else

#define REG_RSTC_RCAUSE         (*(__I  uint8_t*)0x40000C00U) /**< (RSTC) Reset Cause */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for RSTC peripheral ========== */
#define RSTC_BACKUP_IMPLEMENTED                  0          
#define RSTC_NUMBER_OF_EXTWAKE                   0          /* number of external wakeup line */
#define RSTC_INSTANCE_ID                         3          

#endif /* _SAML10_RSTC_INSTANCE_ */
