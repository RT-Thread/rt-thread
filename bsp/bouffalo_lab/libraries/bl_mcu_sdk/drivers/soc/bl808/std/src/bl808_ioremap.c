/**
  ******************************************************************************
  * @file    bl808_ioremap.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#ifdef RT_USING_SMART

#include <stdlib.h>
#include <ioremap.h>
#include "bl808.h"

void *glb_base = NULL;
size_t get_glb_base(void) 
{
    if(glb_base == NULL) 
    {
        glb_base = rt_ioremap((void *)GLB_BASE_PHY, 0x1000);
    }
    return (size_t)glb_base;
}

void *cci_base = NULL;
size_t get_cci_base(void) 
{
    if(cci_base == NULL) 
    {
        cci_base = rt_ioremap((void *)CCI_BASE_PHY, 0x1000);
    }
    return (size_t)cci_base;
}

void *pds_base = NULL;
size_t get_pds_base(void) 
{
    if(pds_base == NULL) 
    {
        pds_base = rt_ioremap((void *)PDS_BASE_PHY, 0x1000);
    }
    return (size_t)pds_base;
}

void *hbn_base = NULL;
size_t get_hbn_base(void) 
{
    if(hbn_base == NULL) 
    {
        hbn_base = rt_ioremap((void *)HBN_BASE_PHY, 0x1000);
    }
    return (size_t)hbn_base;
}

void *mm_glb_base = NULL;
size_t get_mm_glb_base(void) 
{
    if(mm_glb_base == NULL) 
    {
        mm_glb_base = rt_ioremap((void *)MM_GLB_BASE_PHY, 0x1000);
    }
    return (size_t)mm_glb_base;
}

#endif
