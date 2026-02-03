/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file Eif_timer.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "Eif_timer.h"
#include "bsp_timer.h"
#include "ke_event.h"
//#include "Eif_iom.h"


/*************************************
*函数名：eif_timer_isr
*功能：设置一个定时器事件
*参数：void
*
*返回值：void
*备注：
**************************************/
void eif_timer_isr(void)
{
    ke_event_set(KE_EVENT_KE_TIMER);
}

/*************************************
*函数名：eif_timer_init
*功能：定时器初始化，配置自动重装值和分频系数
*参数：void
*
*返回值：void
*备注：
**************************************/
void eif_timer_init(void)
{
    TIM3_config(9999,35);//36分频,1MHz计数,10ms定时中断
}

/*************************************
*函数名：eif_set_timeout
*功能：设置超时时间,10ms计时基数
*参数：to，超时时长
*
*返回值：void
*备注：
**************************************/
void eif_set_timeout(uint32_t to)
{
    TIM3_set_timeout(to);
}

/*************************************
*函数名：eif_get_time
*功能：获取超时剩余时间,单位ms
*参数：void
*
*返回值：void
*备注：
**************************************/
uint32_t eif_get_time(void)
{
    return (TIM3_get_time());
}

/*************************************
*函数名：eif_enable_timer
*功能：启动或关闭定时器
*参数：enable，1：启动； 0：关闭
*
*返回值：void
*备注：
**************************************/
void eif_enable_timer(bool enable)
{
    TIM3_IRQ_enable(enable);
}

