/* -------------------------------------------------------------------------- 
 * Copyright (c) 2013-2017 ARM Limited. All rights reserved.
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
 *
 *---------------------------------------------------------------------------*/

#include <stdio.h>

#include "jtest.h"
#include "all_tests.h"
#include "arm_math.h"


int main (void) {

  JTEST_INIT();                 /* Initialize test framework. */
  JTEST_GROUP_CALL(all_tests);  /* Run all tests. */
  JTEST_ACT_EXIT_FW();          /* Exit test framework.  */

  while(1);						/* Never return */
}
