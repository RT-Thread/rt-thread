/*
 * Copyright (C) 2024, Phytium Technology Co., Ltd.   All Rights Reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * 
 * FilePath: helper.h
 * Created Date: 2024-05-14 10:51:06
 * Last Modified: 2024-07-03 11:21:58
 * Description:  This file is for helper functions.
 * 
 * Modify History:
 *   Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 *  1.0    liusm    2024-05-14 10:51:06  First version.
 */

#ifndef HELPER_H_
#define HELPER_H_

#include "ftypes.h"

#if defined __cplusplus
extern "C" {
#endif

int init_system(void);
void cleanup_system(void);

#if defined __cplusplus
}
#endif

#endif /*  */
