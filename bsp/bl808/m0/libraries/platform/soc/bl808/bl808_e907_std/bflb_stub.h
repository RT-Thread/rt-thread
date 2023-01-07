/**
 * *****************************************************************************
 * @file bflb_stub.h
 * @version 0.1
 * @date 2020-07-08
 * @brief 
 * *****************************************************************************
 * @attention
 * 
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 * 
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * *****************************************************************************
 */
#ifndef __BFLB_STUB__
#define __BFLB_STUB__

#include "stdint.h"

void BFLB_Delay_Ms(uint32_t tim);
void BFLB_Delay_Us(uint32_t tim);
int BFLB_BSP_Get_Random(uint8_t *data,uint32_t len);
void BFLB_BSP_Init_Time(void);
void BFLB_BSP_Clear_Time(void);
uint64_t  BFLB_BSP_Get_Time_Ms(void);
void BFLB_BSP_Start_Time(void);
void BFLB_BSP_Stop_Time(void);
void BFLB_BSP_Set_Alarm_CallBack(void( *interruptFun )( void ));
void BFLB_BSP_Set_Alarm_Time(uint64_t time);
void BFLB_BSP_Deinit_Time(void);
void BFLB_BSP_Delay_Ms(uint32_t time);

#endif