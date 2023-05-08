/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include <stdlib.h>
#include <hal_interrupt.h>

#include <hal_log.h>
#include <gpio/gpio.h>
#include <platform-gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_DRIVERS_GPIO_DEBUG
#ifndef CONFIG_DRIVERS_GPIO_DEBUG
#define GPIO_INFO(fmt, arg...) hal_log_info(fmt, ##arg)
#else
#define GPIO_INFO(fmt, arg...) do {}while(0)
#endif

#define GPIO_ERR(fmt, arg...) hal_log_err(fmt, ##arg)

/**This enum defines the GPIO MUX function*/
#if defined(CONFIG_SOC_SUN20IW1) || defined(CONFIG_ARCH_SUN8IW20)
typedef enum
{
    GPIO_MUXSEL_IN = 0,
    GPIO_MUXSEL_OUT = 1,
    GPIO_MUXSEL_FUNCTION2 = 2,
    GPIO_MUXSEL_FUNCTION3 = 3,
    GPIO_MUXSEL_FUNCTION4 = 4,
    GPIO_MUXSEL_FUNCTION5 = 5,
    GPIO_MUXSEL_FUNCTION6 = 6,
    GPIO_MUXSEL_FUNCTION7 = 7,
    GPIO_MUXSEL_FUNCTION8 = 8,
    GPIO_MUXSEL_FUNCTION9 = 9,
    GPIO_MUXSEL_FUNCTION10 = 10,
    GPIO_MUXSEL_FUNCTION11 = 11,
    GPIO_MUXSEL_FUNCTION12 = 12,
    GPIO_MUXSEL_FUNCTION13 = 13,
    GPIO_MUXSEL_EINT = 14,
    GPIO_MUXSEL_DISABLED = 15,
} gpio_muxsel_t;
#else
typedef enum
{
    GPIO_MUXSEL_IN = 0,
    GPIO_MUXSEL_OUT = 1,
    GPIO_MUXSEL_FUNCTION2 = 2,
    GPIO_MUXSEL_FUNCTION3 = 3,
    GPIO_MUXSEL_FUNCTION4 = 4,
    GPIO_MUXSEL_FUNCTION5 = 5,
    GPIO_MUXSEL_EINT = 6,
    GPIO_MUXSEL_DISABLED = 7,
} gpio_muxsel_t;
#endif

typedef enum
{
    GPIO_DRIVING_LEVEL0    = 0,        /**< Defines GPIO driving current as level0.  */
    GPIO_DRIVING_LEVEL1    = 1,        /**< Defines GPIO driving current as level1.  */
    GPIO_DRIVING_LEVEL2    = 2,        /**< Defines GPIO driving current as level2. */
    GPIO_DRIVING_LEVEL3    = 3         /**< Defines GPIO driving current as level3. */
} gpio_driving_level_t;

typedef enum
{
    GPIO_PULL_DOWN_DISABLED    = 0,        /**< Defines GPIO pull up and pull down disable.  */
    GPIO_PULL_UP          = 1,        /**< Defines GPIO is pull up state.  */
    GPIO_PULL_DOWN            = 2,        /**< Defines GPIO is pull down state. */
} gpio_pull_status_t;

/** This enum defines the GPIO direction. */
typedef enum
{
    GPIO_DIRECTION_INPUT  = 0,              /**<  GPIO input direction. */
    GPIO_DIRECTION_OUTPUT = 1               /**<  GPIO output direction. */
} gpio_direction_t;

/** This enum defines the data type of GPIO. */
typedef enum
{
    GPIO_DATA_LOW  = 0,                     /**<  GPIO data low. */
    GPIO_DATA_HIGH = 1                      /**<  GPIO data high. */
} gpio_data_t;

typedef enum
{
    POWER_MODE_330 = 0,
    POWER_MODE_180 = 1
} gpio_power_mode_t;

bool hal_gpio_check_valid(gpio_pin_t pin);
int hal_gpio_get_data(gpio_pin_t pin, gpio_data_t *data);
int hal_gpio_set_data(gpio_pin_t pin, gpio_data_t data);
int hal_gpio_set_direction(gpio_pin_t pin, gpio_direction_t direction);
int hal_gpio_get_direction(gpio_pin_t pin, gpio_direction_t *direction);
int hal_gpio_set_pull(gpio_pin_t pin, gpio_pull_status_t pull);
int hal_gpio_get_pull(gpio_pin_t pin, gpio_pull_status_t *pull);
int hal_gpio_set_driving_level(gpio_pin_t pin, gpio_driving_level_t level);
int hal_gpio_get_driving_level(gpio_pin_t pin, gpio_driving_level_t *level);
int hal_gpio_pinmux_set_function(gpio_pin_t pin, gpio_muxsel_t function_index);
int hal_gpio_sel_vol_mode(gpio_pin_t pins, gpio_power_mode_t pm_sel);
int hal_gpio_set_debounce(gpio_pin_t pin, unsigned value);
int hal_gpio_to_irq(gpio_pin_t pin, uint32_t *irq);
int hal_gpio_irq_attach(uint32_t irq, void (*hdle)(void *), unsigned long flags, void *data);
int hal_gpio_irq_request(uint32_t irq, irq_handler_t hdle, unsigned long flags, void *data);
int hal_gpio_irq_free(uint32_t irq);
int hal_gpio_irq_enable(uint32_t irq);
int hal_gpio_irq_disable(uint32_t irq);
int hal_gpio_init(void);

#ifdef __cplusplus
}
#endif
#endif
