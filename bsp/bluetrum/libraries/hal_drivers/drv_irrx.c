/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-04-12     greedyhao         first version
 */

#include <board.h>

#ifdef BSP_USING_IRRX

//#define DRV_DEBUG
#define LOG_TAG             "drv.irrx"
#include <drv_log.h>

#ifdef BSP_USING_TIM3
#error "IRRX is conflict with hardware timer3!"
#endif

#ifdef BSP_USING_IRRX_HW
///硬件IR receiver参数
#define IR32KSEL_EN         0                     //IR clock source select 32K
#if IR32KSEL_EN
    #define RPTERR_CNT      33                    //配置11.25ms ± (RPTERR_CNT + 1)*32K的repeat code允许范围
    #define DATERR_CNT      33                    //配置13.5ms ± (DATERR_CNT + 1)*32K引导码允许范围
    #define ONEERR_CNT      7                     //配置2.25ms ± (ONEERR_CNT + 1)*32K的logic "1"允许范围
    #define ZEROERR_CNT     3                     //配置1.12ms ± (ONEERR_CNT + 1)*32K数logic "0"允许范围
    #define TOPR_CNT        55                    //IR time out length = (TOPR + 1) * 64 *32K
#else
    #define RPTERR_CNT      1000                  //配置11.25ms ± (RPTERR_CNT + 1)us的repeat code允许范围
    #define DATERR_CNT      1000                  //配置13.5ms ± (DATERR_CNT + 1)us引导码允许范围
    #define ONEERR_CNT      250                   //配置2.25ms ± (ONEERR_CNT + 1)us的logic "1"允许范围
    #define ZEROERR_CNT     125                   //配置1.12ms ± (ONEERR_CNT + 1)us数logic "0"允许范围
    #define TOPR_CNT        1718                  //IR time out length = (TOPR + 1) * 64 us
#endif // IR32KSEL_EN
#endif // BSP_USING_IRRX_HW

#define NO_KEY      (0u)

struct ab32_irrx_data{
    rt_uint16_t cnt;                            //ir data bit counter
    rt_uint16_t rpt_cnt;                        //ir repeat counter
    rt_uint16_t addr;                           //address,  inverted address   Extended NEC: 16bits address
    rt_uint16_t cmd;                            //command,  inverted command
};
typedef struct ab32_irrx_data *ab32_irrx_data_t;

static struct ab32_irrx_data _irrx = {0};

/**
 * @brief A non-zero value is returned
 *        when IR key is detectedto be pressed.
 *
 * @param addr inverted address   Extended NEC: 16bits address
 * @param cmd  inverted command
 */
rt_section(".irq.irrx")
rt_uint8_t ab32_get_irkey(rt_uint16_t *addr, rt_uint16_t *cmd)
{
    if (_irrx.cnt != 32) {
        return NO_KEY;
    }
    if (addr != RT_NULL) {
        *addr = _irrx.addr;
    }
    if (cmd != RT_NULL) {
        *cmd = _irrx.cmd;
    }
    return !NO_KEY;
}

/**
 * @brief Invalid the current IR key.
 *
 */
void ab32_clr_irkey(void)
{
    _irrx.cnt = 0;
}

#ifdef BSP_USING_IRRX_HW
rt_section(".irq.irrx")
static void irrx_isr(int vector, void *param)
{
    rt_interrupt_enter();

    //IR RX data finish interrupt
    if (IRRXCON & BIT(16)) {
        IRRXCPND = BIT(16);
        _irrx.addr = (rt_uint16_t)IRRXDAT;
        _irrx.cmd = (rt_uint16_t)(IRRXDAT >> 16);
        _irrx.cnt = 32;
    }

    //IR key release interrupt
    if (IRRXCON & BIT(17)) {
        IRRXCPND = BIT(17);
        _irrx.cnt = 0;
    }

    rt_interrupt_leave();
}

static void _irrx_hw_init(void)
{
    GPIOEDE |= BIT(6);
    GPIOEPU |= BIT(6);
    GPIOEDIR |= BIT(6);
    FUNCMCON2 |= 0xf << 20;
    FUNCMCON2 |= (7 << 20);                         //IR mapping to G6
    rt_memset(&_irrx, 0, sizeof(_irrx));

    IRRXERR0 = (RPTERR_CNT << 16) | DATERR_CNT;     //RPTERR[27:16], DATERR[11:0]
    IRRXERR1 = (TOPR_CNT << 20) | (ONEERR_CNT << 10) | ZEROERR_CNT;    //TOPR[31:20], ONEERR[19:10], ZEROERR[9:0]

#if IR32KSEL_EN
    CLKCON1 &= ~BIT(5);
    CLKCON1 |= BIT(4);                              //enable 26M分频32K
    IRRXCON |= BIT(3);                              //ir clock source select 32K
#endif // IR32KSEL_EN

    rt_hw_interrupt_install(IRQ_IRRX_VECTOR, irrx_isr, RT_NULL, "irrx_isr");
    IRRXCON = 0x03;

    // LOG_D("IRRXCON:%08x", IRRXCON);
}
#endif

#ifdef BSP_USING_IRRX_SW

#define TMR3_RCLK               (1000u)            //xosc26m_div 1M

rt_section(".irq.irrx")
static void irrx_isr(int vector, void *param)
{
    rt_uint32_t tmrcnt;

    if (TMR3CON & BIT(17)) {
        //timer1 capture interrupt
        TMR3CNT  = TMR3CNT - TMR3CPT;
        tmrcnt = TMR3CPT;
        TMR3CPND = BIT(17);
        tmrcnt /= TMR3_RCLK;                //convert to ms
    } else if (TMR3CON & BIT(16)){
        //timer1 overflow interrupt
        TMR3CPND = BIT(16);
        tmrcnt = 110;                   //110ms overflow
    } else {
        return;
    }

    //processing repeat code
    if (_irrx.cnt == 32) {
        if ((tmrcnt >= 10) && (tmrcnt <= 12)) {
            //repeat code is simply 9ms+2.25ms
            _irrx.rpt_cnt = 0;
        } else {
            _irrx.rpt_cnt += tmrcnt;
            if (_irrx.rpt_cnt > 108) {
                _irrx.rpt_cnt = 0;
                _irrx.cnt = 0;          //ir key release
            }
        }
        return;
    } else if ((tmrcnt > 7) || (tmrcnt == 0)) {     //A message is started by a 9ms AGC burst
        _irrx.rpt_cnt = 0;
        _irrx.cnt = 0;                  //ir key message started
        return;
    }

    _irrx.cmd >>= 1;
    _irrx.cnt++;
    if (tmrcnt == 2) {                  //Bit time of 1.125ms(0) or 2.25ms(1)
        _irrx.cmd |= 0x8000;
    }

    if (_irrx.cnt == 16) {
        _irrx.addr = _irrx.cmd;         //save address data
    } else if (_irrx.cnt == 32) {
        //got ir key message
        if ((rt_uint8_t)_irrx.cmd > 96) {
            _irrx.cmd = NO_KEY;
        }
    }
}

static void timer3_init(void)
{
    rt_hw_interrupt_install(IRQ_IRRX_VECTOR, irrx_isr, RT_NULL, "irrx_isr");
    TMR3CNT  = 0;
    TMR3PR   = TMR3_RCLK*110 - 1;                                //110ms Timer overflow interrupt
    TMR3CON  = BIT(8) | BIT(7) | BIT(5) | BIT(2) | BIT(1) | BIT(0);   //capture & overflow interrupt enable, falling edge, Capture Mode
}

static void _irrx_hw_init(void)
{
    GPIOEDE |= BIT(6);
    GPIOEPU |= BIT(6);
    GPIOEDIR |= BIT(6);
    FUNCMCON2 |= 0xf << 4;
    FUNCMCON2 |= (7 << 4);                              // timer3 G6 PE6 capture
    rt_memset(&_irrx, 0, sizeof(_irrx));

    timer3_init();
}
#endif

static int ab32_irrx_init(void)
{
    _irrx_hw_init();
    LOG_D("irrx init success");
    return RT_EOK;
}
INIT_BOARD_EXPORT(ab32_irrx_init);

#endif
