/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "de/include.h"
#include "de/bsp_display.h"
#include "disp_sys_intf.h"
#include "dev_disp.h"
#include <platform_resource.h>
#include <disp_board_config.h>
#include <debug.h>
#include <hal_timer.h>
#include <hal_cfg.h>
#include <script.h>

s32 disp_sys_clk_set_rate(hal_clk_id_t p_clk, u32 rate)
{

    hal_clk_status_t ret;
    hal_clk_t clk_t;
    hal_clk_id_t clk = (hal_clk_id_t)p_clk;
    struct reset_control *rst = NULL;
    plat_get_clk_from_id(clk, &clk_t, &rst);
    ret = hal_clk_set_rate(clk_t, rate);
    if (ret) {
        DE_WRN("Set clk:%d rate:%d fail:%d!\n", clk, rate, ret);
        return -1;
    }

    return 0;
}

u32 disp_sys_clk_get_rate(hal_clk_id_t p_clk)
{
    hal_clk_id_t clk = (hal_clk_id_t)p_clk;
    hal_clk_t clk_t;
    struct reset_control *rst = NULL;
    plat_get_clk_from_id(clk, &clk_t, &rst);
    return hal_clk_get_rate(clk_t);
}

s32 disp_sys_clk_enable(hal_clk_id_t clk)
{
    hal_clk_status_t ret;
    hal_clk_id_t parent;
    hal_clk_id_t child = (hal_clk_id_t)clk;
    hal_clk_t clk_t;
    struct reset_control *rst = NULL;
    if(child == (hal_clk_id_t)-1) {
        return 0;
    }
    if (!plat_get_clk_parent(child, &parent)) {
        plat_get_clk_from_id(parent, &clk_t, &rst);
        ret = hal_clock_enable(clk_t);
        if (ret) {
            DE_INF("Enable parent clk:%d fail:%d\n", parent, ret);
        }
    }

    plat_get_clk_from_id(child, &clk_t, &rst);
    ret = hal_reset_control_deassert(rst);
    if (ret) {
        DE_WRN("Enable clk:%d fail:%d\n", child, ret);
        return -1;
    }
    ret = hal_clock_enable(clk_t);
    if (ret) {
        DE_WRN("Enable clk:%d fail:%d\n", child, ret);
        return -1;
    }

    return 0;
}

bool disp_clock_is_enabled(hal_clk_id_t clk)
{
    hal_clk_status_t ret;
    hal_clk_t clk_t;
    struct reset_control *rst = NULL;
    plat_get_clk_from_id(clk, &clk_t, &rst);
    ret = hal_clock_is_enabled(clk_t);
    if (ret == HAL_CLK_STATUS_ENABLED)
        return true;
    return false;
}

s32 disp_sys_clk_disable(hal_clk_id_t clk)
{

    hal_clk_status_t ret;
    hal_clk_id_t parent;
    hal_clk_id_t child = (hal_clk_id_t)clk;
    hal_clk_t clk_t;
    struct reset_control *rst = NULL;

    if(child == (hal_clk_id_t)-1) {
        return 0;
    }
    plat_get_clk_from_id(child, &clk_t, &rst);

    ret = hal_clock_disable(clk_t);
    if (ret) {
        DE_WRN("Disable clk:%d fail:%d\n", child, ret);
        return -1;
    }
    ret = hal_reset_control_assert(rst);
    if (ret) {
        DE_WRN("Disable clk:%d fail:%d\n", child, ret);
        return -1;
    }
    return 0;

}


s32 disp_sys_clk_set_parent(hal_clk_id_t clk, hal_clk_id_t parent)
{
    hal_clk_status_t ret;
    hal_clk_id_t child = (hal_clk_id_t)clk;
    hal_clk_id_t papa = (hal_clk_id_t)parent;
    hal_clk_t clk_child_t;
    hal_clk_t clk_papa_t;
    struct reset_control *rst = NULL;
    if(child == (hal_clk_id_t)-1  || papa == (hal_clk_id_t)-1) {
        return 0;
    }

    plat_get_clk_from_id(child, &clk_child_t, &rst);
    plat_get_clk_from_id(papa, &clk_papa_t, &rst);

    ret = hal_clk_set_parent(clk_child_t, clk_papa_t);
    if (!ret)
        return 0;
    else {
        DE_WRN("Set parent err:%d\n", ret);
        return -1;
    }
}

hal_clk_id_t disp_sys_clk_get_parent(hal_clk_id_t clk)
{
    hal_clk_id_t child = (hal_clk_id_t)clk;
    hal_clk_id_t papa;

    if (!plat_get_clk_parent(child, &papa)) {
        return papa;
    } else
        return (hal_clk_id_t)-1;
}


s32 disp_delay_ms(u32 ms)
{
    return hal_msleep(ms);
}

s32 disp_delay_us(u32 us)
{

    return hal_usleep(us);
}

void *disp_sys_malloc(u32 size)
{
    void *ptr = hal_malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

void disp_sys_free(void *ptr)
{
    hal_free(ptr);
}

void *disp_dma_malloc(u32 num_bytes, void *phys_addr)
{
    u32 actual_bytes;
    void *address = NULL;

    if (num_bytes != 0) {
        actual_bytes = DISP_BYTE_ALIGN(num_bytes);

        address = hal_malloc(actual_bytes);
        *(uint32_t *)phys_addr = __va_to_pa((unsigned long)address);
        if (address) {
            DE_INF("hal_malloc ok, phy addr=0x%p, vir addr=%p size=0x%x\n",
                 (void *)(*(unsigned long *)phys_addr), address, num_bytes);
            return address;
        }

        DE_WRN("dma_alloc_coherent fail, size=0x%x\n", num_bytes);
        return NULL;
    }

    DE_WRN("%s size is zero\n", __func__);

    return NULL;
}

void disp_dma_free(void *virt_addr, void *phys_addr, u32 num_bytes)
{
    u32 actual_bytes;

    actual_bytes = DISP_BYTE_ALIGN(num_bytes);
    if (phys_addr && virt_addr)
        hal_free(virt_addr);
}

int disp_sys_mutex_lock(hal_sem_t *sem)
{
    return hal_sem_wait(*sem);
}

int disp_sys_mutex_unlock(hal_sem_t *sem)
{
    return hal_sem_post(*sem);
}

int disp_sys_mutex_init(hal_sem_t *lock)
{
    *lock = hal_sem_create(1);

    if (*lock == NULL)
        return -1;

    return 0;
}

int disp_sys_register_irq(u32 IrqNo, u32 Flags, void *Handler, void *pArg,
              u32 DataSize, u32 Prio)
{
    DE_INF("%s, irqNo=%ld, Handler=0x%p, pArg=0x%p\n", __func__, IrqNo,
          Handler, pArg);
    return request_irq(IrqNo, (irq_handler_t) Handler, 0x0,
               "display", pArg);
}

void disp_sys_unregister_irq(u32 IrqNo, void *Handler, void *pArg)
{
    free_irq(IrqNo, pArg);
}

void disp_sys_enable_irq(u32 IrqNo)
{
    enable_irq(IrqNo);
}

void disp_sys_disable_irq(u32 IrqNo)
{
    disable_irq(IrqNo);
}

/* type: 0:invalid, 1: int; 2:str, 3: gpio */
s32 disp_sys_script_get_item(char *main_name, char *sub_name, s32 value[],
                 s32 type)
{
#ifdef CONFIG_OF
    char compat[32];
    u32 len = 0;
    struct device_node *node;
    s32 ret = 0;
    struct gpio_config config;

    len = sprintf(compat, "allwinner,sunxi-%s", main_name);
    if (len > 32)
        DE_WRN("size of mian_name is out of range\n");

    node = of_find_compatible_node(NULL, NULL, compat);
    if (!node) {
        DE_WRN("of_find_compatible_node %s fail\n", compat);
        return ret;
    }

    if (type == 1) {
        if (of_property_read_u32_array(node, sub_name, value, 1))
            DE_INF("of_property_read_u32_array %s.%s fail\n",
                  main_name, sub_name);
        else
            ret = type;
    } else if (type == 2) {
        const char *str;

        if (of_property_read_string(node, sub_name, &str))
            DE_INF("of_property_read_string %s.%s fail\n", main_name,
                  sub_name);
        else {
            ret = type;
            memcpy((void *)value, str, strlen(str) + 1);
        }
    } else if (type == 3) {
        ret = 3;
    }

exit:
    return ret;
#elif RTTHREAD_KERNEL == 1
    int ret;
    int gpio_count = 0;
    int i;
    user_gpio_set_t gpiocfg[5] = {0};

    if (type == PROPERTY_INTGER) {
        /* get integer */
        if (Hal_Cfg_GetKeyValue(main_name, sub_name, value, 1)) {
            DE_INF("of_property_read_u32_array %s.%s fail\n",
                  main_name, sub_name);
            goto not_found;
        } else
            ret = type;
    } else if (type == PROPERTY_STRING) {
        /* get string */
        char str[40] = {0};

        if (Hal_Cfg_GetKeyValue(main_name, sub_name, (void *)str, sizeof(str))) {
            DE_INF("hal get value %s.%s fail\n", main_name,
                  sub_name);
            goto not_found;
        } else {
            ret = type;
            memcpy((void *)value, (void *)str, strlen(str) + 1);
        }
    } else if (type == PROPERTY_GPIO) {
        /* get gpio */
        gpio_count = Hal_Cfg_GetGPIOSecKeyCount(main_name);
        /* get all gpio in main_name */
        Hal_Cfg_GetGPIOSecData(main_name, gpiocfg, gpio_count);

        for (i = 0; i < gpio_count; i++) {
            if (!strcmp(gpiocfg[i].gpio_name, sub_name)) {
                struct disp_gpio_set_t *gpio_info = (struct disp_gpio_set_t *) value;
                gpio_info->gpio = (gpiocfg[i].port - 1) * 32 + gpiocfg[i].port_num;
                gpio_info->port = gpiocfg[i].port;
                gpio_info->port_num = gpiocfg[i].port_num;
                gpio_info->mul_sel = gpiocfg[i].mul_sel;
                gpio_info->pull = gpiocfg[i].pull;
                gpio_info->drv_level = gpiocfg[i].drv_level;
                gpio_info->data = gpiocfg[i].data;
                memcpy(gpio_info->gpio_name, sub_name, strlen(sub_name) + 1);
            }
        }
        ret = PROPERTY_GPIO;
    } else {
        ret = PROPERTY_UNDEFINED;
    }

exit:
    return ret;
not_found:
    return PROPERTY_UNDEFINED;
#else
    return disp_get_property_value(main_name, sub_name, value);

#endif
}

int disp_sys_get_ic_ver(void)
{
    return 0;
}

int disp_sys_gpio_request(struct disp_gpio_set_t *gpio_list,
              u32 group_count_max)
{
    int ret = 0;
    u32 gpio, mul_sel, pull, drv_level, data;
    char pin_name[32];
    u32 config;

    if (gpio_list == NULL) {
        DE_WRN("%s: gpio list is null\n", __func__);
        return 0;
    }

    gpio = gpio_list->gpio;
    mul_sel = gpio_list->mul_sel;
    pull = gpio_list->pull;
    drv_level = gpio_list->drv_level;
    data = gpio_list->data;
    hal_gpio_pinmux_set_function(gpio, mul_sel);
    //hal_gpio_set_direction(gpio, GPIO_DIRECTION_OUTPUT);
    hal_gpio_set_pull(gpio, pull);
    hal_gpio_set_driving_level(gpio, drv_level);
    hal_gpio_set_data(gpio, data);

    return gpio;
}

int disp_sys_gpio_release(int p_handler, s32 if_release_to_default_status)
{
    if (p_handler)
        hal_gpio_pinmux_set_function(p_handler, 7);
    else
        DE_WRN("OSAL_GPIO_Release, hdl is NULL\n");

    return 0;
}

/* direction: 0:input, 1:output */
int disp_sys_gpio_set_direction(u32 p_handler, u32 direction,
                const char *gpio_name)
{
    int ret = -1;

    if (p_handler) {
        ret = hal_gpio_set_direction(p_handler, direction);
    } else {
        DE_WRN("OSAL_GPIO_DevSetONEPIN_IO_STATUS, hdl is NULL\n");
        ret = -1;
    }
    return ret;
}

int disp_sys_gpio_get_value(u32 p_handler, const char *gpio_name)
{
    gpio_data_t data = 0;
    if (p_handler) {
        if(!hal_gpio_get_data(p_handler, &data))
            return data;
        else {
            DE_WRN("gpio_get_data fail!\n");
            return -1;
        }
    }
    DE_WRN("disp_sys_gpio_get_value, hdl is NULL\n");

    return -1;
}

int disp_sys_gpio_set_value(u32 p_handler, u32 value_to_gpio,
                const char *gpio_name)
{
    if (p_handler)
        hal_gpio_set_data(p_handler, value_to_gpio);
    else
        DE_WRN("OSAL_GPIO_DevWRITE_ONEPIN_DATA, hdl is NULL\n");

    return 0;
}

int disp_sys_pin_set_state(char *dev_name, char *name)
{
#ifdef CONFIG_OF
    return 0;
#else
    u32 len  = 0, i = 0;
    struct disp_gpio_set_t *p_list = NULL;
    p_list = disp_get_all_pin_property(dev_name, &len);

    if (!p_list || !len) {
        DE_INF("No pin to be configureed!\n");
        return 0;
    }
    for (i = 0; i < len; ++i) {
        if (!strcmp(name, DISP_PIN_STATE_ACTIVE)) {
            hal_gpio_pinmux_set_function(p_list[i].gpio,
                             p_list[i].mul_sel);
            hal_gpio_set_pull(p_list[i].gpio, p_list[i].pull);
            hal_gpio_set_driving_level(p_list[i].gpio,
                           p_list[i].drv_level);
            hal_gpio_set_data(p_list[i].gpio, p_list[i].data);
        } else if (!strcmp(name, DISP_PIN_STATE_SLEEP)) {
            hal_gpio_pinmux_set_function(p_list[i].gpio,
                             GPIO_MUXSEL_DISABLED);
            hal_gpio_set_pull(p_list[i].gpio, p_list[i].pull);
            hal_gpio_set_driving_level(p_list[i].gpio,
                           p_list[i].drv_level);
            hal_gpio_set_data(p_list[i].gpio, p_list[i].data);
        } else {
            DE_WRN("Wrong pin state name:%s\n", name);
            return -1;
        }
    }
    return 0;
#endif
}

s32 disp_sys_power_enable(void *p_power)
{
    s32 ret = 0;

#ifdef CONFIG_DRIVERS_REGULATOR
    struct disp_power_t *tmp = (struct disp_power_t *)p_power;
    struct regulator_dev regulator;

    if (!tmp) {
        ret = -1;
        DE_WRN("NUll pointer!\n");
        goto OUT;
    }
    DE_INF("Enabling power :%s %lu\n", tmp->power_name, tmp->power_vol);
    hal_regulator_get(REGULATOR_GET(tmp->power_type, tmp->power_id), &regulator);
    ret = hal_regulator_set_voltage(&regulator, tmp->power_vol);
    if (ret)
        DE_WRN("set %s power vol %d fail!\n", tmp->power_name, tmp->power_vol);

    ret = hal_regulator_enable(&regulator);
    if (ret)
        DE_WRN("Enable %s power fail!\n", tmp->power_name);

OUT:
#endif
    return ret;
}

s32 disp_sys_power_disable(void *p_power)
{
    s32 ret = 0;
#ifdef CONFIG_DRIVERS_REGULATOR
    struct disp_power_t *tmp = (struct disp_power_t *)p_power;
    struct regulator_dev regulator;

    if (!tmp) {
        ret = -1;
        DE_WRN("NUll pointer!\n");
        goto OUT;
    }
    ret = hal_regulator_get(REGULATOR_GET(tmp->power_type, tmp->power_id), &regulator);

    if (tmp->always_on == false) {
        DE_INF("Disabling power :%s\n", tmp->power_name);
        ret = hal_regulator_disable(&regulator);
        if (ret)
            DE_WRN("Disable %s power fail!\n", tmp->power_name);
    }

OUT:
#endif
    return ret;
}

u32 disp_getprop_regbase(char *main_name, u32 index)
{
#ifdef CONFIG_OF
    char compat[32];
    u32 len = 0;
    struct device_node *node;
    int ret = -1;
    int value[32] = {0};
    uintptr_t reg_base = 0;

    len = sprintf(compat, "allwinner,sunxi-%s", main_name);
    if (len > 32)
        DE_WRN("size of mian_name is out of range\n");

    //node = fdt_path_offset(working_fdt,compat);
    node = of_find_compatible_node(NULL, NULL, compat);
    if (node < 0) {
        DE_WRN("of_find_compatible_node %s fail\n", compat);
        goto exit;
    }

    ret = of_property_read_u32_array(node, "reg", (uint32_t*)value);
    if (0 > ret)
        __wrn("fdt_getprop_u32 %s.%s fail\n", main_name, sub_name);
    else {
        reg_base = value[index * 4] + value[index * 4 + 1];
    }

exit:
    return reg_base;
#else
    u32 reg_base = 0;
    if(plat_get_reg_base(index, &reg_base))
        DE_WRN("Get reg base %d fail!\n", index);
    return reg_base;
#endif
}

u32 disp_getprop_irq(char *main_name, u32 index)
{
#ifdef CONFIG_OF
    char compat[32];
    u32 len = 0;
    int node;
    int ret = -1;
    int value[32] = {0};
    u32 irq = 0;

    len = sprintf(compat, "%s", main_name);
    if (len > 32)
        __wrn("size of mian_name is out of range\n");

    //node = fdt_path_offset(working_fdt,compat);
    node = disp_fdt_nodeoffset(compat);
    if (node < 0) {
        __wrn("fdt_path_offset %s fail\n", compat);
        goto exit;
    }

    ret = fdt_getprop_u32(working_fdt, node, sub_name, (uint32_t*)value);
    if (0 > ret)
        __wrn("fdt_getprop_u32 %s.%s fail\n", main_name, sub_name);
    else {
        irq = value[index * 3 + 1];
        if (0 == value[index * 3])
            irq += 32;
    }

exit:
    return irq;
#else
    u32 irq = 0;
    if(plat_get_irq_no(index, &irq))
        DE_WRN("Get irq no %d fail!\n", index);
    return irq;

#endif
}

u32 disp_getprop_clk(char *main_name)
{
#ifdef CONFIG_OF
#else
    hal_clk_id_t clk_no = (hal_clk_id_t)-1;
    if(plat_get_clk(main_name, &clk_no))
        DE_WRN("Get clk no %s fail!\n", main_name);
    return clk_no;
#endif
    return 0;
}

struct reset_control *disp_get_rst_by_name(char *main_name)
{
#ifdef CONFIG_OF
#else
    struct reset_control *rst;
    if(plat_get_rst_by_name(main_name, &rst)) {
        DE_WRN("Get clk no %s fail!\n", main_name);
        return NULL;
    }
    return rst;
#endif
    return 0;
}

uintptr_t disp_sys_pwm_request(u32 pwm_id)
{
    uintptr_t ret = 0;
#if !defined(CONFIG_FPGA_V4_PLATFORM) \
    && !defined(CONFIG_FPGA_V7_PLATFORM)
    struct disp_pwm_dev *dev = NULL;

    hal_pwm_init();
    dev = disp_sys_malloc(sizeof(struct disp_pwm_dev));
    dev->pwm_channel_id = pwm_id;

    ret = (uintptr_t) dev;

#endif
    return ret;
}


int disp_sys_pwm_free(uintptr_t p_handler)
{
    int ret = 0;
#if !defined(CONFIG_FPGA_V4_PLATFORM) \
    && !defined(CONFIG_FPGA_V7_PLATFORM)
    struct disp_pwm_dev *dev = (struct disp_pwm_dev *)p_handler;

    if (dev)
        disp_sys_free(dev);

#endif
    return ret;
}

int disp_sys_pwm_enable(uintptr_t p_handler)
{
    int ret = 0;

#if !defined(CONFIG_FPGA_V4_PLATFORM) \
    && !defined(CONFIG_FPGA_V7_PLATFORM)
    struct disp_pwm_dev *pwm_dev;

    pwm_dev = (struct disp_pwm_dev *)p_handler;
    if (pwm_dev) {
        DE_INF("period_ns = %d \n", pwm_dev->cfg.period_ns);
        DE_INF("duty_ns = %d \n",  pwm_dev->cfg.duty_ns);
        DE_INF("polarity = %d \n", pwm_dev->cfg.polarity);
        DE_INF("channel = %d \n", pwm_dev->pwm_channel_id);
        if (pwm_dev->cfg.period_ns != 0 && pwm_dev->cfg.duty_ns !=0)
            ret = hal_pwm_control(pwm_dev->pwm_channel_id, &pwm_dev->cfg);
        pwm_dev->enable = true;
    }
#endif
    return ret;
}

int disp_sys_pwm_disable(uintptr_t p_handler)
{
    int ret = 0;
#if !defined(CONFIG_FPGA_V4_PLATFORM) \
    && !defined(CONFIG_FPGA_V7_PLATFORM)
    struct disp_pwm_dev *pwm_dev;

    pwm_dev = (struct disp_pwm_dev *)p_handler;
    pwm_dev->enable = false;

    if (pwm_dev->cfg.polarity)
        pwm_dev->cfg.duty_ns = 0;
    else
        pwm_dev->cfg.duty_ns = pwm_dev->cfg.period_ns;
    if (pwm_dev)
        ret = hal_pwm_control(pwm_dev->pwm_channel_id, &pwm_dev->cfg);

    hal_pwm_disable_controller(pwm_dev->pwm_channel_id);
#endif
    return ret;
}

int disp_sys_pwm_config(uintptr_t p_handler, int duty_ns, int period_ns)
{
    int ret = 0;
#if !defined(CONFIG_FPGA_V4_PLATFORM) \
    && !defined(CONFIG_FPGA_V7_PLATFORM)
    struct disp_pwm_dev *pwm_dev;

    pwm_dev = (struct disp_pwm_dev *)p_handler;
    if (!pwm_dev) {
        DE_WRN("disp_sys_pwm_Config, handle is NULL!\n");
        ret = -1;
    } else {
        pwm_dev->cfg.duty_ns = duty_ns;
        pwm_dev->cfg.period_ns = period_ns;
        if (pwm_dev->enable == true)
            ret = hal_pwm_control(pwm_dev->pwm_channel_id, &pwm_dev->cfg);
    }
#endif
    return ret;
}

int disp_sys_pwm_set_polarity(uintptr_t p_handler, int polarity)
{
    int ret = 0;
#if !defined(CONFIG_FPGA_V4_PLATFORM) \
    && !defined(CONFIG_FPGA_V7_PLATFORM)
    struct disp_pwm_dev *pwm_dev;

    pwm_dev = (struct disp_pwm_dev *)p_handler;
    if (!pwm_dev) {
        DE_WRN("disp_sys_pwm_Config, handle is NULL!\n");
        ret = -1;
    } else {
        pwm_dev->cfg.polarity = polarity;
    }
#endif
    return ret;
}
