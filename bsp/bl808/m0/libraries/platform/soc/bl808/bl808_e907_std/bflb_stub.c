/**
 * *****************************************************************************
 * @file bflb_stub.c
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
#include "bflb_stub.h"
#include "bflb_bsp_driver_glue.h"


void BFLB_Delay_Ms(uint32_t tim){
    ARCH_Delay_MS(tim);
}

void BFLB_Delay_Us(uint32_t tim){
    ARCH_Delay_US(tim);
}

int BFLB_BSP_Get_Random(uint8_t *data,uint32_t len)
{
    uint8_t tmpBuf[32];
    uint32_t readLen=0;
    uint32_t i=0,cnt=0;

    while(readLen<len){
        if(Sec_Eng_Trng_Read(tmpBuf)!=SUCCESS){
            return -1;
        }
        cnt=len-readLen;
        if(cnt>sizeof(tmpBuf)){
            cnt=sizeof(tmpBuf);
        }
        for(i=0;i<cnt;i++){
            data[readLen+i]=tmpBuf[i];
        }
        readLen+=cnt;
    }

    return 0;
}

void BFLB_BSP_Init_Time()
{
    CPU_Interrupt_Disable(MTIME_IRQn);
    /* Set MTimer the same frequency as SystemCoreClock */

    GLB_Set_MTimer_CLK(1,GLB_MTIMER_CLK_BCLK,7);

    BFLB_BSP_Clear_Time();
}

void BFLB_BSP_Clear_Time()
{
    *(volatile uint64_t*) (CLIC_CTRL_ADDR + CLIC_MTIME) = 0;
}

uint64_t  BFLB_BSP_Get_Time_Ms()
{

    uint32_t tmpValLow,tmpValHigh,tmpValLow1,tmpValHigh1;
    uint32_t cnt=0,tmp;

    do{
        tmpValLow=*(volatile uint32_t*) (CLIC_CTRL_ADDR + CLIC_MTIME);
        tmpValHigh=*(volatile uint32_t*) (CLIC_CTRL_ADDR + CLIC_MTIME+4);
        tmpValLow1=*(volatile uint32_t*) (CLIC_CTRL_ADDR + CLIC_MTIME);
        tmpValHigh1=*(volatile uint32_t*) (CLIC_CTRL_ADDR + CLIC_MTIME+4);
        cnt++;
        if(cnt>4){
            break;
        }
    }while(tmpValLow>tmpValLow1||tmpValHigh>tmpValHigh1);

    tmp=(SystemCoreClockGet()/(GLB_Get_BCLK_Div()+1));
    tmp=(tmp>>3)/1000;

    if(tmpValHigh1==0){
        return(uint64_t)(tmpValLow1/tmp);
    }else{
        return (((uint64_t)tmpValHigh1<<32)+tmpValLow1)/tmp;
    }
}

void BFLB_BSP_Start_Time()
{
    *(volatile uint64_t*) (CLIC_CTRL_ADDR + CLIC_MTIME) = 0;
}

void BFLB_BSP_Stop_Time()
{

}

void BFLB_BSP_Set_Alarm_Time(uint64_t time)
{
    uint32_t tmp;

    tmp=(SystemCoreClockGet()/(GLB_Get_BCLK_Div()+1));
    tmp=(tmp>>3)/1000;

    time = time*tmp;

    *(volatile uint64_t*) (CLIC_CTRL_ADDR + CLIC_MTIMECMP) = (*(volatile uint64_t*) (CLIC_CTRL_ADDR + CLIC_MTIME) + time) ;
    CPU_Interrupt_Enable(MTIME_IRQn);
}

void BFLB_BSP_Set_Alarm_CallBack(void( *interruptFun )( void ) )
{
    Interrupt_Handler_Register(MTIME_IRQn,interruptFun);
}

void BFLB_BSP_Deinit_Time()
{
    CPU_Interrupt_Disable(MTIME_IRQn);
    BFLB_BSP_Stop_Time();
}

void BFLB_BSP_Delay_Ms(uint32_t time)
{
    uint64_t cnt=0;
    uint32_t clock=SystemCoreClockGet();
    uint64_t startTime=BFLB_BSP_Get_Time_Ms();

    while(BFLB_BSP_Get_Time_Ms()-startTime<time){
        cnt++;
        /* assume BFLB_BSP_Get_Time_Ms take 32 cycles*/
        if(cnt>(time*(clock>>(10+5)))*2){
            break;
        }
    }
}