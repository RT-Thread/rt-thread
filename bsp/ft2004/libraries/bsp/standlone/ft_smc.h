/*
 * @[H]: Copyright (C) 2014-2021 Phytium Technology.  All rights reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  Use of the Software is limited solely to applications:
 *  (a) running on a Phytium device, or
 *  (b) that interact with a Phytium device through a bus or interconnect.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  PHYTIUM  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 *  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 * 
 *  Except as contained in this notice, the name of the Phytium shall not be used
 *  in advertising or otherwise to promote the sale, use or other dealings in
 *  this Software without prior written authorization from Phytium. 
 * 
 * @Date: 2021-04-21 11:53:38
 * @LastEditTime: 2021-04-21 11:53:38
 * @Description:  Description of file
 * @Modify History: 
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#ifndef FT_SMC_H
#define FT_SMC_H

#include "ft_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        /* data */
        u32 FunctionIdentifier;
        u32 a1;
        u32 a2;
        u32 a3;
        u32 a4;
        u32 a5;
        u32 a6;

    } FSmc_Data_t;

    void FSmc_Call(FSmc_Data_t *Input, FSmc_Data_t *Output);

#ifdef __cplusplus
}
#endif

#endif // !FT_SMC_H