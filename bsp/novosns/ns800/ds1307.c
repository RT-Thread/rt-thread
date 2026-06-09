/*
 * Copyright (c) 2026, NS800RT7P65D RTC Driver
 * 
 * DS1307 RTC driver - GPIO bitbang I2C
 * 
 * Hardware: DS1307 RTC module, I2C address 0x68, 5V supply
 * Pins:     PB2(SDA/GP34), PB3(SCL/GP35)
 * 
 * NS800 GPIO configuration requirements:
 *   GPIO_setAnalogMode(..., GPIO_ANALOG_DISABLED)   - enable digital input
 *   GPIO_setQualificationMode(..., GPIO_QUAL_ASYNC) - bypass input sampling
 */

#include <rtthread.h>
#include <rthw.h>
#include <string.h>
#include "ds1307.h"
#include "gpio.h"
#include "board.h"

#define ADDR     0x68
#define PORT     GPIOB
#define PIN_SDA  GPIO_PIN_2
#define PIN_SCL  GPIO_PIN_3
#define DELAY_CNT 3000

/* ========== I2C bitbang primitives ========== */
static void dly(void) { volatile uint32_t i; for(i=0;i<DELAY_CNT;i++); }

static void sda_l(void) { GPIO_setDirectionMode(PORT,PIN_SDA,GPIO_DIR_MODE_OUT); GPIO_clearPin(PORT,PIN_SDA); dly(); }
static void sda_h(void) { GPIO_setDirectionMode(PORT,PIN_SDA,GPIO_DIR_MODE_IN); dly(); }
static void scl_l(void) { GPIO_setDirectionMode(PORT,PIN_SCL,GPIO_DIR_MODE_OUT); GPIO_clearPin(PORT,PIN_SCL); dly(); }
static void scl_h(void) { GPIO_setDirectionMode(PORT,PIN_SCL,GPIO_DIR_MODE_IN); dly(); }
static uint8_t sda_r(void) { GPIO_setDirectionMode(PORT,PIN_SDA,GPIO_DIR_MODE_IN); return GPIO_readPin(PORT,PIN_SDA); }

static void i2c_init(void)
{
    GPIO_setPinConfig(GPIO_34_GPIO34);
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setPadConfig(PORT,PIN_SDA,GPIO_PIN_TYPE_STD|GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(PORT,PIN_SCL,GPIO_PIN_TYPE_STD|GPIO_PIN_TYPE_PULLUP);
    GPIO_setAnalogMode(PORT,PIN_SDA,GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(PORT,PIN_SCL,GPIO_ANALOG_DISABLED);
    GPIO_setQualificationMode(PORT,PIN_SDA,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(PORT,PIN_SCL,GPIO_QUAL_ASYNC);
    sda_h(); scl_h();
}

static void i2c_sta(void) { sda_h();scl_h();dly();sda_l();scl_l(); }
static void i2c_sto(void) { sda_l();scl_h();dly();sda_h();dly(); }
static void i2c_bit(uint8_t b) { if(b)sda_h();else sda_l(); scl_h();scl_l(); }

static int i2c_send(uint8_t d) {
    for(int i=7;i>=0;i--) i2c_bit((d>>i)&1);
    sda_h();scl_h();dly(); int ack=sda_r()?1:0; scl_l();dly(); return ack;
}

static uint8_t i2c_recv(uint8_t nak) {
    uint8_t d=0; sda_h();
    for(int i=7;i>=0;i--){ sda_h();dly();scl_h();dly(); if(sda_r()) d|=(1<<i); scl_l();dly(); }
    if(nak)sda_h();else sda_l(); dly(); scl_h();dly();scl_l();dly();sda_h(); return d;
}

/* ========== DS1307 access ========== */
static int ds_write(uint8_t reg, uint8_t *data, uint8_t len) {
    rt_base_t l=rt_hw_interrupt_disable(); int r=0;
    i2c_sta(); if(i2c_send(ADDR<<1)){i2c_sto();r=-1;goto out;}
    if(i2c_send(reg)){i2c_sto();r=-1;goto out;}
    for(int i=0;i<len;i++) if(i2c_send(data[i])){i2c_sto();r=-1;goto out;}
    i2c_sto(); dly();
out: rt_hw_interrupt_enable(l); return r;
}

static int ds_read(uint8_t reg, uint8_t *buf, uint8_t len) {
    rt_base_t l=rt_hw_interrupt_disable(); int r=0;
    i2c_sta(); if(i2c_send(ADDR<<1)){i2c_sto();r=-1;goto out2;}
    if(i2c_send(reg)){i2c_sto();r=-1;goto out2;} i2c_sto(); dly();
    i2c_sta(); if(i2c_send((ADDR<<1)|1)){i2c_sto();r=-1;goto out2;}
    for(int i=0;i<len;i++) buf[i]=i2c_recv(i<len-1?0:1);
    i2c_sto(); dly();
out2: rt_hw_interrupt_enable(l); return r;
}

/* ========== BCD helpers ========== */
static inline uint8_t b2b(uint8_t x){return ((x>>4)*10)+(x&0xF);}
static inline uint8_t x2b(uint8_t v){return ((v/10)<<4)|(v%10);}

/* ========== Public API ========== */
rt_err_t ds1307_init(void) {
    uint8_t sec; i2c_init();
    rt_kprintf("[DS1307] Init...\n");
    if(ds_read(0x00,&sec,1)<0){rt_kprintf("No ACK\n");return -RT_ERROR;}
    if(sec&0x80){sec&=0x7F; ds_write(0x00,&sec,1); rt_kprintf("Clock started\n");}
    rt_kprintf("OK\n"); return RT_EOK;
}

rt_err_t ds1307_get_time(struct tm *t) {
    uint8_t b[7]; if(!t||ds_read(0x00,b,7)<0) return -RT_ERROR;
    memset(t,0,sizeof(*t));
    t->tm_sec=b2b(b[0]&0x7F); t->tm_min=b2b(b[1]&0x7F); t->tm_hour=b2b(b[2]&0x3F);
    t->tm_mday=b2b(b[3]&0x3F); t->tm_wday=b[4]&0x07; t->tm_mon=b2b(b[5]&0x1F)-1;
    t->tm_year=b2b(b[6])+100; return RT_EOK;
}

rt_err_t ds1307_set_time(struct tm *t) {
    if(!t) return -RT_ERROR;
    uint8_t v;
    v=x2b(t->tm_year-100); if(ds_write(0x06,&v,1)<0) return -RT_ERROR;
    v=x2b(t->tm_mon+1);    if(ds_write(0x05,&v,1)<0) return -RT_ERROR;
    v=x2b(t->tm_mday);     if(ds_write(0x04,&v,1)<0) return -RT_ERROR;
    v=t->tm_wday&0x07;     if(ds_write(0x03,&v,1)<0) return -RT_ERROR;
    v=x2b(t->tm_hour);     if(ds_write(0x02,&v,1)<0) return -RT_ERROR;
    v=x2b(t->tm_min);      if(ds_write(0x01,&v,1)<0) return -RT_ERROR;
    v=x2b(t->tm_sec);      if(ds_write(0x00,&v,1)<0) return -RT_ERROR;
    return RT_EOK;
}
