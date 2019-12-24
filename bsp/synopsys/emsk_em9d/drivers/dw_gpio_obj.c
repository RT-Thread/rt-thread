/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "inc/arc/arc.h"
#include "inc/arc/arc_builtin.h"

#include "dw_gpio_obj.h"

#include "emsk_hardware.h"
/*
 * Uncomment this to enable default
 * gpio bit handler output message
 * by uart
 */

#ifdef ARC_FEATURE_DMP_PERIPHERAL
#define PERIPHERAL_BASE     ARC_FEATURE_DMP_PERIPHERAL
#else
#define PERIPHERAL_BASE     _arc_aux_read(AUX_DMP_PERIPHERAL)
#endif

#if (USE_DW_GPIO_PORT_A)
static DEV_GPIO     port_a;
static DW_GPIO_PORT dw_gpio_port_a;
static DEV_GPIO_HANDLER dw_gpio_bit_handler_a[EMSK_GPIO_A_INT_MAX_COUNT];
static DW_GPIO_BIT_ISR dw_gpio_bit_isr_a = {
    EMSK_GPIO_A_INT_MAX_COUNT, dw_gpio_bit_handler_a
};

static int32_t porta_open(uint32_t dir)
{
    return dw_gpio_open(&port_a, dir);
}

static int32_t porta_close(void)
{
    return dw_gpio_close(&port_a);
}

static int32_t porta_control(uint32_t ctrl_cmd, void *param)
{
    return dw_gpio_control(&port_a, ctrl_cmd, param);
}

static int32_t porta_write(uint32_t val, uint32_t mask)
{
    return dw_gpio_write(&port_a, val, mask);
}

static int32_t porta_read(uint32_t *val, uint32_t mask)
{
    return dw_gpio_read(&port_a, val, mask);
}

static void porta_isr(void *ptr)
{
    dw_gpio_isr_handler(&port_a, ptr);
}

static void porta_install(void)
{
    uint32_t i;
    DEV_GPIO_PTR port_ptr = &port_a;
    DEV_GPIO_INFO_PTR info_ptr = &(port_a.gpio_info);
    DW_GPIO_PORT_PTR dw_port_ptr = &(dw_gpio_port_a);

    info_ptr->gpio_ctrl = (void *)dw_port_ptr;
    info_ptr->opn_cnt = 0;
    info_ptr->method = 0;
    info_ptr->direction = 0;
    info_ptr->extra = 0;

    dw_port_ptr->no = DW_GPIO_PORT_A;
    dw_port_ptr->regs = (DW_GPIO_REG_PTR)(PERIPHERAL_BASE|REL_REGBASE_GPIO0);
    dw_port_ptr->valid_bit_mask = EMSK_GPIO_A_VALID_MASK;
    dw_port_ptr->intno = INTNO_GPIO;
    dw_port_ptr->int_handler = porta_isr;

    for (i=0; i<dw_gpio_bit_isr_a.int_bit_max_cnt; i++) {
        dw_gpio_bit_isr_a.int_bit_handler_ptr[i] = NULL;
    }
    dw_port_ptr->gpio_bit_isr = &dw_gpio_bit_isr_a;

    port_ptr->gpio_open = porta_open;
    port_ptr->gpio_close = porta_close;
    port_ptr->gpio_control = porta_control;
    port_ptr->gpio_write = porta_write;
    port_ptr->gpio_read = porta_read;
}
#endif

#if (USE_DW_GPIO_PORT_B)
static DEV_GPIO     port_b;
static DW_GPIO_PORT dw_gpio_port_b;

static int32_t portb_open(uint32_t dir)
{
    return dw_gpio_open(&port_b, dir);
}

static int32_t portb_close(void)
{
    return dw_gpio_close(&port_b);
}

static int32_t portb_control(uint32_t ctrl_cmd, void *param)
{
    return dw_gpio_control(&port_b, ctrl_cmd, param);
}

static int32_t portb_write(uint32_t val, uint32_t mask)
{
    return dw_gpio_write(&port_b, val, mask);
}

static int32_t portb_read(uint32_t *val, uint32_t mask)
{
    return dw_gpio_read(&port_b, val, mask);
}

static void portb_isr(void *ptr)
{
    dw_gpio_isr_handler(&port_b, ptr);
}

static void portb_install(void)
{
    DEV_GPIO_PTR port_ptr = &port_b;
    DEV_GPIO_INFO_PTR info_ptr = &(port_b.gpio_info);
    DW_GPIO_PORT_PTR dw_port_ptr = &(dw_gpio_port_b);

    info_ptr->gpio_ctrl = (void *)dw_port_ptr;
    info_ptr->opn_cnt = 0;
    info_ptr->method = 0;
    info_ptr->direction = 0;
    info_ptr->extra = 0;

    dw_port_ptr->no = DW_GPIO_PORT_B;
    dw_port_ptr->regs = (DW_GPIO_REG_PTR)(PERIPHERAL_BASE|REL_REGBASE_GPIO0);
    dw_port_ptr->valid_bit_mask = EMSK_GPIO_B_VALID_MASK;

    dw_port_ptr->intno = INTNO_GPIO;
    dw_port_ptr->int_handler = portb_isr;
    dw_port_ptr->gpio_bit_isr = NULL;

    port_ptr->gpio_open = portb_open;
    port_ptr->gpio_close = portb_close;
    port_ptr->gpio_control = portb_control;
    port_ptr->gpio_write = portb_write;
    port_ptr->gpio_read = portb_read;
}
#endif


#if (USE_DW_GPIO_PORT_C)
static DEV_GPIO     port_c;
static DW_GPIO_PORT dw_gpio_port_c;

static int32_t portc_open(uint32_t dir)
{
    return dw_gpio_open(&port_c, dir);
}

static int32_t portc_close(void)
{
    return dw_gpio_close(&port_c);
}

static int32_t portc_control(uint32_t ctrl_cmd, void *param)
{
    return dw_gpio_control(&port_c, ctrl_cmd, param);
}

static int32_t portc_write(uint32_t val, uint32_t mask)
{
    return dw_gpio_write(&port_c, val, mask);
}

static int32_t portc_read(uint32_t *val, uint32_t mask)
{
    return dw_gpio_read(&port_c, val, mask);
}

static void portc_isr(void *ptr)
{
    dw_gpio_isr_handler(&port_c, ptr);
}

static void portc_install(void)
{
    DEV_GPIO_PTR port_ptr = &port_c;
    DEV_GPIO_INFO_PTR info_ptr = &(port_c.gpio_info);
    DW_GPIO_PORT_PTR dw_port_ptr = &(dw_gpio_port_c);

    info_ptr->gpio_ctrl = (void *)dw_port_ptr;
    info_ptr->opn_cnt = 0;
    info_ptr->method = 0;
    info_ptr->direction = 0;
    info_ptr->extra = 0;

    dw_port_ptr->no = DW_GPIO_PORT_C;
    dw_port_ptr->regs = (DW_GPIO_REG_PTR)(PERIPHERAL_BASE|REL_REGBASE_GPIO0);
    dw_port_ptr->valid_bit_mask = EMSK_GPIO_C_VALID_MASK;

    dw_port_ptr->intno = INTNO_GPIO;
    dw_port_ptr->int_handler = portc_isr;
    dw_port_ptr->gpio_bit_isr = NULL;

    port_ptr->gpio_open = portc_open;
    port_ptr->gpio_close = portc_close;
    port_ptr->gpio_control = portc_control;
    port_ptr->gpio_write = portc_write;
    port_ptr->gpio_read = portc_read;
}
#endif

#if (USE_DW_GPIO_PORT_D)
static DEV_GPIO     port_d;
static DW_GPIO_PORT dw_gpio_port_d;

static int32_t portd_open(uint32_t dir)
{
    return dw_gpio_open(&port_d, dir);
}

static int32_t portd_close(void)
{
    return dw_gpio_close(&port_d);
}

static int32_t portd_control(uint32_t ctrl_cmd, void *param)
{
    return dw_gpio_control(&port_d, ctrl_cmd, param);
}

static int32_t portd_write(uint32_t val, uint32_t mask)
{
    return dw_gpio_write(&port_d, val, mask);
}

static int32_t portd_read(uint32_t *val, uint32_t mask)
{
    return dw_gpio_read(&port_d, val, mask);
}

static void portd_isr(void *ptr)
{
    dw_gpio_isr_handler(&port_d, ptr);
}

static void portd_install(void)
{
    DEV_GPIO_PTR port_ptr = &port_d;
    DEV_GPIO_INFO_PTR info_ptr = &(port_d.gpio_info);
    DW_GPIO_PORT_PTR dw_port_ptr = &(dw_gpio_port_d);

    info_ptr->gpio_ctrl = (void *)dw_port_ptr;
    info_ptr->opn_cnt = 0;
    info_ptr->method = 0;
    info_ptr->direction = 0;
    info_ptr->extra = 0;

    dw_port_ptr->no = DW_GPIO_PORT_D;
    dw_port_ptr->regs = (DW_GPIO_REG_PTR)(PERIPHERAL_BASE|REL_REGBASE_GPIO0);
    dw_port_ptr->valid_bit_mask = EMSK_GPIO_D_VALID_MASK;

    dw_port_ptr->intno = INTNO_GPIO;
    dw_port_ptr->int_handler = portd_isr;
    dw_port_ptr->gpio_bit_isr = NULL;

    port_ptr->gpio_open = portd_open;
    port_ptr->gpio_close = portd_close;
    port_ptr->gpio_control = portd_control;
    port_ptr->gpio_write = portd_write;
    port_ptr->gpio_read = portd_read;
}
#endif

DEV_GPIO_PTR gpio_get_dev(int32_t gpio_id)
{
    static uint32_t install_flag = 0;

    /* intall device objects */
    if (install_flag == 0) {
        install_flag = 1;
        dw_gpio_all_install();
    }

    switch (gpio_id) {
#if (USE_DW_GPIO_PORT_A)
        case DW_GPIO_PORT_A: return &port_a;
#endif
#if (USE_DW_GPIO_PORT_B)
        case DW_GPIO_PORT_B: return &port_b;
#endif
#if (USE_DW_GPIO_PORT_C)
        case DW_GPIO_PORT_C: return &port_c;
#endif
#if (USE_DW_GPIO_PORT_D)
        case DW_GPIO_PORT_D: return &port_d;
#endif
        default:
            break;
    }
    return NULL;
}

void dw_gpio_all_install(void)
{
#if (USE_DW_GPIO_PORT_A)
    porta_install();
#endif
#if (USE_DW_GPIO_PORT_B)
    portb_install();
#endif
#if (USE_DW_GPIO_PORT_C)
    portc_install();
#endif
#if (USE_DW_GPIO_PORT_D)
    portd_install();
#endif
}
