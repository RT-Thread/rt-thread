/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef _DISP_SYS_INTF_
#define _DISP_SYS_INTF_

#include "de/include.h"
#include <sunxi_hal_regulator.h>

#ifdef CONFIG_PLAN_SPRITE
#define RTTHREAD_KERNEL 1
#else
#define RTTHREAD_KERNEL 0
#endif

struct disp_gpio_set_t {
    char gpio_name[32];
    u32 port;
    u32 port_num;
    u32 mul_sel;
    u32 pull;
    u32 drv_level;
    u32 data;
    u32 gpio;
};

struct disp_pwm_dev {
    u32 pwm_channel_id;
    struct pwm_config cfg;
    bool enable;
};

/**
 * disp_power_t
 */
struct disp_power_t {
    char power_name[32];
    /*see sunxi_hal_regulator.h */
    enum REGULATOR_TYPE_ENUM power_type;
    enum REGULATOR_ID_ENUM power_id;
    /*unit:uV, 1V=1000000uV */
    u32 power_vol;
    bool always_on;
};

#define DISP_PIN_STATE_ACTIVE "active"
#define DISP_PIN_STATE_SLEEP "sleep"

#define DISP_BYTE_ALIGN(x) (((x + (4*1024-1)) >> 12) << 12)

void disp_sys_cache_flush(void *address, u32 length, u32 flags);

int disp_sys_register_irq(u32 IrqNo, u32 Flags, void *Handler, void *pArg,
              u32 DataSize, u32 Prio);
void disp_sys_unregister_irq(u32 IrqNo, void *Handler, void *pArg);
void disp_sys_disable_irq(u32 IrqNo);
void disp_sys_enable_irq(u32 IrqNo);

/* returns: 0:invalid, 1: int; 2:str, 3: gpio */
s32 disp_sys_script_get_item(char *main_name, char *sub_name, s32 value[],
                 s32 type);

int disp_sys_get_ic_ver(void);

int disp_sys_gpio_request(struct disp_gpio_set_t *gpio_list,
              u32 group_count_max);
int disp_sys_gpio_request_simple(struct disp_gpio_set_t *gpio_list,
                 u32 group_count_max);
int disp_sys_gpio_release(int p_handler, s32 if_release_to_default_status);

/* direction: 0:input, 1:output */
int disp_sys_gpio_set_direction(u32 p_handler, u32 direction,
                const char *gpio_name);
int disp_sys_gpio_get_value(u32 p_handler, const char *gpio_name);
int disp_sys_gpio_set_value(u32 p_handler, u32 value_to_gpio,
                const char *gpio_name);
int disp_sys_pin_set_state(char *dev_name, char *name);

s32 disp_sys_power_enable(void *p_power);
s32 disp_sys_power_disable(void *p_power);
void *disp_sys_malloc(u32 size);

uintptr_t disp_sys_pwm_request(u32 pwm_id);
int disp_sys_pwm_free(uintptr_t p_handler);
int disp_sys_pwm_enable(uintptr_t p_handler);
int disp_sys_pwm_disable(uintptr_t p_handler);
int disp_sys_pwm_config(uintptr_t p_handler, int duty_ns, int period_ns);
int disp_sys_pwm_set_polarity(uintptr_t p_handler, int polarity);
s32 disp_delay_us(u32 us);
s32 disp_delay_ms(u32 ms);
u32 disp_getprop_regbase(char *main_name, u32 index);
u32 disp_getprop_irq(char *main_name, u32 index);
u32 disp_getprop_clk(char *main_name);
struct reset_control *disp_get_rst_by_name(char *main_name);
void disp_sys_free(void *ptr);
int disp_sys_mutex_init(hal_sem_t *lock);
int disp_sys_mutex_unlock(hal_sem_t *sem);
int disp_sys_mutex_lock(hal_sem_t *sem);
void *disp_dma_malloc(u32 num_bytes, void *phys_addr);
void disp_dma_free(void *virt_addr, void *phys_addr, u32 num_bytes);
s32 disp_sys_clk_set_rate(hal_clk_id_t p_clk, u32 rate);
u32 disp_sys_clk_get_rate(hal_clk_id_t p_clk);
s32 disp_sys_clk_set_parent(hal_clk_id_t clk, hal_clk_id_t parent);
hal_clk_id_t disp_sys_clk_get_parent(hal_clk_id_t clk);
s32 disp_sys_clk_enable(hal_clk_id_t clk);
s32 disp_sys_clk_disable(hal_clk_id_t clk);
bool disp_clock_is_enabled(hal_clk_id_t clk);

#endif
