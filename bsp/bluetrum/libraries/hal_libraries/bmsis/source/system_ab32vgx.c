/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ab32vgx.h"

#ifndef ALIGN
#define ALIGN(n)                    __attribute__((aligned(n)))
#endif // ALIGN

typedef struct _sys_t {
    uint8_t cnt_1us;             //delay 1us cnt
    uint8_t main_start;          //Main是否已启动
    uint8_t clk_sel;             //system clock select
    uint8_t sys_clk;
//    uint8_t aupll_type;          //区分AUPLL的频率
    uint16_t rand_seed;
    uint32_t uart0baud;          //UART0BAUD
} sys_t;

const uint8_t sysclk_sel_tbl[] = {
    OSCDIV_2M,          //SYS_2M
    PLL0DIV_12M,        //SYS_12M
    OSCDIV_13M,         //SYS_13M
    PLL0DIV_24M,        //SYS_24M
    OSCDIV_26M,         //SYS_26M
    PLL0DIV_30M,        //SYS_30M
    PLL0DIV_48M,        //SYS_48M
    PLL0DIV_60M,        //SYS_60M
    PLL0DIV_80M,        //SYS_80M
    PLL0DIV_120M,       //SYS_120M
};

const uint8_t sysclk_index[] = {
    2,
    12,
    13,
    24,
    26,
    30,
    48,
    60,
    80,
    120,
};

sys_t sys = {0};
void my_printf(const char *format, ...);

static void delay_us(uint16_t nus)
{
   int i;
   for (i = 0; i < nus*10; i++) {
        asm("nop");
   }
}

uint8_t get_clksel_val(uint8_t val)
{
    return sysclk_sel_tbl[val];
}

uint8_t get_cur_sysclk(void)
{
    return sys.sys_clk;
}

uint32_t get_sysclk_nhz(void)
{
    return sysclk_index[sys.sys_clk] * 1000000;
}

////AT(.com_text.set_flash_safety)
//static ALWAYS_INLINE void set_flash_safety(uint32_t sys_clk)
//{
//    SPI0CON |= BIT(10);
//    if (sys_clk > SYS_48M) {
//        SPI0CON |= BIT(3);                          //2bit mode
//        spiflash_init(0x3b, 1);                     //dummy = 1
//    } else {
//        SPI0CON &= ~BIT(3);                         //2bit mode
//        spiflash_init(0x0b, 1);                     //dummy = 0
//    }
//}

uint8_t get_sd_rate(void)
{
    return 0;  //unit: M
}

uint8_t set_sd_baud(uint8_t sd_rate)
{
    uint8_t sd0baud=0;
    uint8_t sys_clk=0;
    if(sd_rate > 14){//不支持超过14M
        return 0;
    }
    if (sys.sys_clk <= SYSCLK_26M) {
        sys_clk=26;
    }else if (sys.sys_clk == SYSCLK_48M) {
        sys_clk=48;
    }  else if (sys.sys_clk <= SYSCLK_60M) {
        sys_clk=52;
    } else if (sys.sys_clk == SYSCLK_80M) {
        sys_clk=80;
    } else if (sys.sys_clk <= SYSCLK_120M) {
        sys_clk=120;
    }
    sd0baud = sys_clk/sd_rate-1;
    if(sys_clk%sd_rate*2/sd_rate) {
        sd0baud=sd0baud+1;
    }
    return sd0baud;
}

void update_sd0baud(void)
{
    if (!(SD0CON & BIT(0))) {
        return;
    }

    uint8_t sd_rate=get_sd_rate();
    if(sd_rate){
        uint8_t sd0baud=set_sd_baud(sd_rate);
        if(sd0baud){
             SD0BAUD=sd0baud;
             return ;
        }
    }

    if (sys.sys_clk <= SYSCLK_30M) {
        SD0BAUD = 1;
    } else if (sys.sys_clk <= SYSCLK_60M) {
        SD0BAUD = 3;
    } else if (sys.sys_clk == SYSCLK_80M) {
        SD0BAUD = 5;
    } else if (sys.sys_clk <= SYSCLK_120M) {
        SD0BAUD = 9;
    }
}

uint8_t sysclk_update_baud(uint8_t baud)
{
    uint8_t sd_rate=get_sd_rate();
    if(baud>20||!sd_rate) {
        if (sys.sys_clk == SYSCLK_120M) {
            return ((uint16_t)(baud + 1) * 25 / 10 - 1);
        } else if (sys.sys_clk >= SYSCLK_80M) {
            return ((baud + 1) * 2 - 1);
        } else if (sys.sys_clk <= SYSCLK_30M) {
            return (((baud + 1) >> 1) - 1);
        }
    } else if (sd_rate){
        return  set_sd_baud(sd_rate);
    }
    return baud;
}

//客户可能用到UART0(使用26M时钟源)做通信,这里可选设置系统时钟时不改波特率
WEAK void update_uart0baud_in_sysclk(uint32_t uart_baud)
{
    if(UART0CON & BIT(0)) {
        while (!(UART0CON & BIT(8)));
    }
    UART0BAUD = (uart_baud << 16) | uart_baud;
}

void set_sys_uart0baud(uint32_t baud)
{
    sys.uart0baud = baud;
}

//切系统时钟前，先设置模块时钟分频较大值，保证模块不会超频的情况
void set_peripherals_clkdiv_safety(void)
{
    uint32_t clkcon3 = CLKCON3;
    uint32_t clkcon2 = CLKCON2;

    //src clkdiv
    clkcon3 &= ~0xf0;                               //reset src clkdiv
    clkcon3 |= (1 << 4);                            //src clk = sys_clk / (n+1)

    //sbcenc硬件要小于48M
    clkcon3 &= ~(0x0f << 12);                       //reset sbcenc clkdiv
    clkcon3 |= (2 << 12);                           //src clk = sys_clk / (n+1)

    //aec ram硬件要小于50M
    clkcon3 &= ~0x0f;                               //reset aec clkdiv
    clkcon3 &= ~(0x0f << 19);                       //reset plc clkdiv
    clkcon3 &= ~(0x0f << 23);                       //reset cvsd clkdiv
    clkcon3 |= 0x02;                                //aec clk = sys_clk / (n+1)
    clkcon3 |= (2 << 19);                           //plc clk = sys_clk / (n+1)
    clkcon3 |= (2 << 23);                           //cvsd clk = sys_clk / (n+1)

    //audec硬件要小于48M
    clkcon2 &= ~(0x0f << 13);                       //reset audec clkdiv
    clkcon2 |= (2 << 13);                           //audec clk = sys_clk / (n+1)

    CLKCON3 = clkcon3;
    CLKCON2 = clkcon2;
}

//根据实际系统时钟，设置合适的模块时钟分频
void set_peripherals_clkdiv(void)
{
    uint32_t clkcon3 = CLKCON3;
    uint32_t clkcon2 = CLKCON2;
    uint32_t clkdiv;
    uint8_t  sys_clk = sys.sys_clk;

    //src clkdiv
    clkcon3 &= ~0xf0;                               //reset src clkdiv
    if (sys_clk > SYSCLK_80M) {
        clkcon3 |= (1 << 4);                        //src clk = sys_clk / (n+1)
    }

    //sbcec硬件要小于48M
    clkcon3 &= ~(0x0f << 12);
    if (sys_clk > SYSCLK_80M) {
        clkcon3 |= (2 << 12);
    } else if (sys_clk >= SYSCLK_60M) {
        clkcon3 |= (1 << 12);
    }

    //aec ram硬件要小于50M
    clkcon3 &= ~0x0f;                               //reset aec clkdiv
    clkcon3 &= ~(0x0f << 19);                       //reset plc clkdiv
    clkcon3 &= ~(0x0f << 23);                       //reset cvsd clkdiv
    if (sys_clk > SYSCLK_80M) {
        clkdiv = 2;
    } else if (sys_clk >= SYSCLK_60M) {
        clkdiv = 1;
    } else {
        clkdiv = 0;
    }
    clkcon3 |= clkdiv;                              //aec clk = sys_clk / (n+1)
    clkcon3 |= (clkdiv << 19);                      //plc clk = sys_clk / (n+1)
    clkcon3 |= (clkdiv << 23);                      //cvsd clk = sys_clk / (n+1)

    //audec硬件要小于48M
    clkcon2 &= ~(0x0f << 13);                       //reset audec clkdiv
    if (sys_clk > SYSCLK_80M) {
        clkdiv = 2;
    } else if (sys_clk >= SYSCLK_60M) {
        clkdiv = 1;
    } else {
        clkdiv = 0;
    }
    clkcon2 |= (clkdiv << 13);                     //audec clk = sys_clk / (n+1)

    CLKCON3 = clkcon3;
    CLKCON2 = clkcon2;

//    if (sys_clk <= SYS_48M) {
//        PWRCON0 = (PWRCON0 & ~0xf) | (sys_trim.vddcore);                //VDDCORE减一档
//    }
//    vddcore_other_offset();
}

ALIGN(512)  //注意：超过512byte时，要用lock cache
static void set_sysclk_do(uint32_t sys_clk, uint32_t clk_sel, uint32_t spll_div, uint32_t spi_baud, uint32_t spi1baud)
{
    uint32_t cpu_ie;
    cpu_ie = PICCON & BIT(0);
    PICCONCLR = BIT(0);                             //关中断，切换系统时钟
    set_peripherals_clkdiv_safety();

    CLKCON0 &= ~(BIT(2) | BIT(3));                  //sysclk sel rc2m
    CLKCON2 &= ~(0x1f << 8);                        //reset spll div

    if(clk_sel <= PLL0DIV_120M) {
        //sys_clk来源PLL0的分频配置
        CLKCON0 &= ~(BIT(4) | BIT(5) | BIT(6));     //sys_pll select pll0out
        if (PLL0DIV != (240 * 65536 / 26)) {
            PLL0DIV = 240 * 65536 / 26;             //pll: 240M, XOSC: 26M
            PLL0CON &= ~(BIT(3) | BIT(4) | BIT(5));
            PLL0CON |= BIT(3);                      //Select PLL/VCO frequency band (PLL大于206M vcos = 0x01, 否则为0)
            PLL0CON |= BIT(20);                     //update pll0div to pll0_clk
            CLKCON3 &= ~(7 << 16);
            CLKCON3 |= (4 << 16);                   //USB CLK 48M
        }
    } else if (clk_sel <= OSCDIV_26M) {
        //sys_clk来源于XOSC26M时钟分频, 无USB时关闭PLL0
//        if (!is_usb_support()) {
//            PLL0CON &= ~BIT(18);
//            PLL0CON &= ~(BIT(12) | BIT(6));         //close pll0
//        }

        CLKCON0 &= ~(BIT(4) | BIT(5) | BIT(6));
        CLKCON0 |= BIT(6);                          //spll select xosc26m_clk
    }

    CLKCON2 |= (spll_div << 8);
    CLKCON0 |= BIT(3);                          //sysclk sel spll
    SPI0BAUD = spi_baud;
    if (CLKGAT1 & BIT(12)) {
        SPI1BAUD = spi1baud;
    }
//    if (spiflash_speed_up_en()) {
//        set_flash_safety(sys_clk);
//    }
    PICCON |= cpu_ie;
}

void set_sysclk(uint32_t sys_clk)
{
    uint32_t uart_baud, spll_div = 0, spi_baud = 0, spi1baud;
    uint8_t cnt_1us, clk_sel;

    clk_sel = get_clksel_val(sys_clk);
    if(sys.clk_sel == clk_sel) {
        return;
    }
//    if (sys_clk > SYSCLK_48M) {
//        PWRCON0 = (PWRCON0 & ~0xf) | (sys_trim.vddcore + 1);            //VDDCORE加一档
//    }
//    vddcore_other_offset();

//    printf("%s: %d, %d\n", __func__, sys_clk, clk_sel);
    switch (sys_clk) {
    case SYSCLK_12M:
        spll_div = 19;                   //pll0 240M
        cnt_1us = 1;
        spi_baud = 0;
        spi1baud = 0;
        break;

    case SYSCLK_24M:
        spll_div = 9;                   //pll0 240M
        cnt_1us = 2;
        spi_baud = 0;
        spi1baud = 1;
        break;

    case SYSCLK_30M:
        spll_div = 7;                   //pll0 240M
        cnt_1us = 3;
        spi_baud = 1;                   //Baud Rate =Fsys clock / (SPI_BAUD+1)
        spi1baud = 1;
        break;

    case SYSCLK_48M:
        spll_div = 4;                   //pll0 240M
        cnt_1us = 4;
        spi_baud = 1;                   //Baud Rate =Fsys clock / (SPI_BAUD+1)
        spi1baud = 3;
        break;

    case SYSCLK_60M:
        spll_div = 3;                   //pll0 240M
        cnt_1us = 5;
        spi_baud = 2;                   //Baud Rate =Fsys clock / (SPI_BAUD+1)
        spi1baud = 3;
        break;

    case SYSCLK_80M:
        spll_div = 2;                   //pll0 240M
        cnt_1us = 7;
        spi_baud = 3;                   //Baud Rate =Fsys clock / (SPI_BAUD+1)
        spi1baud = 4;
        break;

    case SYSCLK_120M:
        spll_div = 1;                   //pll0 240M
        cnt_1us = 10;
        spi_baud = 4;                   //Baud Rate =Fsys clock / (SPI_BAUD+1)     //spiclk 120/5 = 24M
        spi1baud = 9;
        break;

    case SYSCLK_26M:
        spll_div = 0;
        cnt_1us = 3;
        spi_baud = 1;
        spi1baud = 1;
        break;

    case SYSCLK_13M:
        spll_div = 1;
        cnt_1us = 1;
        spi_baud = 0;
        spi1baud = 0;
        break;

    case SYSCLK_2M:
        spll_div = 1;
        cnt_1us = 1;
        spi_baud = 0;
        spi1baud = 0;
        break;

    default:
        return;
    }

    //先判断PLL0是否打开
    if(clk_sel <= PLL0DIV_120M) {
        if (!(PLL0CON & BIT(12))) {
            PLL0CON &= ~(BIT(3) | BIT(4) | BIT(5));
            PLL0CON |= BIT(3);                     //Select PLL/VCO frequency band (PLL大于206M vcos = 0x01, 否则为0)
            PLL0CON |= BIT(12);                    //enable pll0 ldo
            delay_us(100);                         //delay 100us
            PLL0DIV = 240 * 65536 / 26;            //pll0: 240M, XOSC: 26M
            PLL0CON |= BIT(20);                    //update pll0div to pll0_clk
            PLL0CON |= BIT(6);                     //enable analog pll0
            PLL0CON |= BIT(18);                    //pll0 sdm enable
            delay_us(1000);                        //wait pll0 stable
        }
    }

    sys.cnt_1us = cnt_1us;
    sys.sys_clk = sys_clk;
    sys.clk_sel = clk_sel;
    uart_baud =  (((get_sysclk_nhz() + (sys.uart0baud / 2)) / sys.uart0baud) - 1);

    set_sysclk_do(sys_clk, clk_sel,spll_div, spi_baud, spi1baud);
    set_peripherals_clkdiv();
    update_sd0baud();       //更新下SD0BAUD
    update_uart0baud_in_sysclk(uart_baud);
}
