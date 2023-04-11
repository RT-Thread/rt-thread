 /**********************************************************************
 * Copyright (C) 2014-2015 Cadence Design Systems, Inc.- http://www.cadence.com
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***********************************************************************/

#include <stdint.h>

/* NOTE - The driver uses fixed width types as defined in C99

    If not provided by your environment, these are typical definitions for the
 *        fixed width types used in the driver, and should be provided here.
 * typedef signed char            int8_t
 * typedef unsigned char          uint8_t
 * typedef signed short           int16_t
 * typedef unsigned short         uint16_t
 * typedef signed long int        int32_t
 * typedef unsigned long int      uint32_t
 * typedef signed long long int   int64_t
 * typedef unsigned long long int uint64_t
 * typedef int32_t                intptr_t
 * typedef uint32_t               uintptr_t

 * These definitions are for a 32bit system with 32bit int, and should be adjusted
 * for your actual target system and toolchain.

 Under Linux, these will be available in:
 #include <linux/types.h>

*/
