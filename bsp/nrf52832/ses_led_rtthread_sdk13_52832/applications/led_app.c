#include <rtthread.h>

#include "nrf_gpio.h"

// LEDs definitions for PCA10040
#define LEDS_NUMBER    4

#define LED_START      17
#define LED_1          17
#define LED_2          18
#define LED_3          19
#define LED_4          20
#define LED_STOP       20

#define LEDS_ACTIVE_STATE 0

#define LEDS_INV_MASK  LEDS_MASK

#define LEDS_LIST { LED_1, LED_2, LED_3, LED_4 }

#define BSP_LED_0      LED_1
#define BSP_LED_1      LED_2
#define BSP_LED_2      LED_3
#define BSP_LED_3      LED_4

#define BUTTONS_NUMBER 4

#define BUTTON_START   13
#define BUTTON_1       13
#define BUTTON_2       14
#define BUTTON_3       15
#define BUTTON_4       16
#define BUTTON_STOP    16
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4 }

#define BSP_BUTTON_0   BUTTON_1
#define BSP_BUTTON_1   BUTTON_2
#define BSP_BUTTON_2   BUTTON_3
#define BSP_BUTTON_3   BUTTON_4


#define BSP_BOARD_LED_0 0
#define BSP_BOARD_LED_1 1
#define BSP_BOARD_LED_2 2
#define BSP_BOARD_LED_3 3
#define BSP_BOARD_LED_4 4
#define BSP_BOARD_LED_5 5
#define BSP_BOARD_LED_6 6
#define BSP_BOARD_LED_7 7

#ifdef BSP_LED_0
#define BSP_LED_0_MASK (1<<BSP_LED_0)
#else
#define BSP_LED_0_MASK 0
#endif
#ifdef BSP_LED_1
#define BSP_LED_1_MASK (1<<BSP_LED_1)
#else
#define BSP_LED_1_MASK 0
#endif
#ifdef BSP_LED_2
#define BSP_LED_2_MASK (1<<BSP_LED_2)
#else
#define BSP_LED_2_MASK 0
#endif
#ifdef BSP_LED_3
#define BSP_LED_3_MASK (1<<BSP_LED_3)
#else
#define BSP_LED_3_MASK 0
#endif
#ifdef BSP_LED_4
#define BSP_LED_4_MASK (1<<BSP_LED_4)
#else
#define BSP_LED_4_MASK 0
#endif
#ifdef BSP_LED_5
#define BSP_LED_5_MASK (1<<BSP_LED_5)
#else
#define BSP_LED_5_MASK 0
#endif
#ifdef BSP_LED_6
#define BSP_LED_6_MASK (1<<BSP_LED_6)
#else
#define BSP_LED_6_MASK 0
#endif
#ifdef BSP_LED_7
#define BSP_LED_7_MASK (1<<BSP_LED_7)
#else
#define BSP_LED_7_MASK 0
#endif


#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK | \
                        BSP_LED_2_MASK | BSP_LED_3_MASK | \
                        BSP_LED_4_MASK | BSP_LED_5_MASK | \
                        BSP_LED_6_MASK | BSP_LED_7_MASK)

#define BSP_BOARD_BUTTON_0 0
#define BSP_BOARD_BUTTON_1 1
#define BSP_BOARD_BUTTON_2 2
#define BSP_BOARD_BUTTON_3 3
#define BSP_BOARD_BUTTON_4 4
#define BSP_BOARD_BUTTON_5 5
#define BSP_BOARD_BUTTON_6 6
#define BSP_BOARD_BUTTON_7 7


#ifdef BSP_BUTTON_0
#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#else
#define BSP_BUTTON_0_MASK 0
#endif
#ifdef BSP_BUTTON_1
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)
#else
#define BSP_BUTTON_1_MASK 0
#endif
#ifdef BSP_BUTTON_2
#define BSP_BUTTON_2_MASK (1<<BSP_BUTTON_2)
#else
#define BSP_BUTTON_2_MASK 0
#endif
#ifdef BSP_BUTTON_3
#define BSP_BUTTON_3_MASK (1<<BSP_BUTTON_3)
#else
#define BSP_BUTTON_3_MASK 0
#endif
#ifdef BSP_BUTTON_4
#define BSP_BUTTON_4_MASK (1<<BSP_BUTTON_4)
#else
#define BSP_BUTTON_4_MASK 0
#endif
#ifdef BSP_BUTTON_5
#define BSP_BUTTON_5_MASK (1<<BSP_BUTTON_5)
#else
#define BSP_BUTTON_5_MASK 0
#endif
#ifdef BSP_BUTTON_6
#define BSP_BUTTON_6_MASK (1<<BSP_BUTTON_6)
#else
#define BSP_BUTTON_6_MASK 0
#endif
#ifdef BSP_BUTTON_7
#define BSP_BUTTON_7_MASK (1<<BSP_BUTTON_7)
#else
#define BSP_BUTTON_7_MASK 0
#endif

#define BUTTONS_MASK   (BSP_BUTTON_0_MASK | BSP_BUTTON_1_MASK | \
                        BSP_BUTTON_2_MASK | BSP_BUTTON_3_MASK | \
                        BSP_BUTTON_4_MASK | BSP_BUTTON_5_MASK | \
                        BSP_BUTTON_6_MASK | BSP_BUTTON_7_MASK)


#define LEDS_OFF(leds_mask) do {  ASSERT(sizeof(leds_mask) == 4);                     \
                        NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                        NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LEDS_ON(leds_mask) do {  ASSERT(sizeof(leds_mask) == 4);                     \
                       NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                       NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LED_IS_ON(leds_mask) ((leds_mask) & (NRF_GPIO->OUT ^ LEDS_INV_MASK) )

#define LEDS_INVERT(leds_mask) do { uint32_t gpio_state = NRF_GPIO->OUT;      \
                              ASSERT(sizeof(leds_mask) == 4);                 \
                              NRF_GPIO->OUTSET = ((leds_mask) & ~gpio_state); \
                              NRF_GPIO->OUTCLR = ((leds_mask) & gpio_state); } while (0)

#define LEDS_CONFIGURE(leds_mask) do { uint32_t pin;                  \
                                  ASSERT(sizeof(leds_mask) == 4);     \
                                  for (pin = 0; pin < 32; pin++)      \
                                      if ( (leds_mask) & (1 << pin) ) \
                                          nrf_gpio_cfg_output(pin); } while (0)


#if LEDS_NUMBER > 0
static const uint8_t m_board_led_list[LEDS_NUMBER] = LEDS_LIST;
#endif

#if BUTTONS_NUMBER > 0
static const uint8_t m_board_btn_list[BUTTONS_NUMBER] = BUTTONS_LIST;
#endif

#if LEDS_NUMBER > 0
bool bsp_board_led_state_get(uint32_t led_idx)
{
    ASSERT(led_idx < LEDS_NUMBER);
    bool pin_set = nrf_gpio_pin_out_read(m_board_led_list[led_idx]) ? true : false;
    return (pin_set == (LEDS_ACTIVE_STATE ? true : false));
}

void bsp_board_led_on(uint32_t led_idx)
{
        ASSERT(led_idx < LEDS_NUMBER);
        nrf_gpio_pin_write(m_board_led_list[led_idx], LEDS_ACTIVE_STATE ? 1 : 0);
}

void bsp_board_led_off(uint32_t led_idx)
{
    ASSERT(led_idx < LEDS_NUMBER);
    nrf_gpio_pin_write(m_board_led_list[led_idx], LEDS_ACTIVE_STATE ? 0 : 1);
}

void bsp_board_leds_off(void)
{
    uint32_t i;
    for(i = 0; i < LEDS_NUMBER; ++i)
    {
        bsp_board_led_off(i);
    }
}

void bsp_board_leds_on(void)
{
    uint32_t i;
    for(i = 0; i < LEDS_NUMBER; ++i)
    {
        bsp_board_led_on(i);
    }
}

void bsp_board_led_invert(uint32_t led_idx)
{
    ASSERT(led_idx < LEDS_NUMBER);
    nrf_gpio_pin_toggle(m_board_led_list[led_idx]);
}

void bsp_board_leds_init(void)
{
    uint32_t i;
    for(i = 0; i < LEDS_NUMBER; ++i)
    {
        nrf_gpio_cfg_output(m_board_led_list[i]);
    }
    bsp_board_leds_off();
}

uint32_t bsp_board_led_idx_to_pin(uint32_t led_idx)
{
    ASSERT(led_idx < LEDS_NUMBER);
    return m_board_led_list[led_idx];
}

uint32_t bsp_board_pin_to_led_idx(uint32_t pin_number)
{
    uint32_t ret = 0xFFFFFFFF;
    uint32_t i;
    for(i = 0; i < LEDS_NUMBER; ++i)
    {
        if (m_board_led_list[i] == pin_number)
        {
            ret = i;
            break;
        }
    }
    return ret;
}
#endif //LEDS_NUMBER > 0

#if BUTTONS_NUMBER > 0
bool bsp_board_button_state_get(uint32_t button_idx)
{
    ASSERT(button_idx < BUTTONS_NUMBER);
    bool pin_set = nrf_gpio_pin_read(m_board_btn_list[button_idx]) ? true : false;
    return (pin_set == (BUTTONS_ACTIVE_STATE ? true : false));
}

void bsp_board_buttons_init(void)
{
    uint32_t i;
    for(i = 0; i < BUTTONS_NUMBER; ++i)
    {
        nrf_gpio_cfg_input(m_board_btn_list[i], BUTTON_PULL);
    }
}

uint32_t bsp_board_pin_to_button_idx(uint32_t pin_number)
{
    uint32_t i;
    uint32_t ret = 0xFFFFFFFF;
    for(i = 0; i < BUTTONS_NUMBER; ++i)
    {
        if (m_board_btn_list[i] == pin_number)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

uint32_t bsp_board_button_idx_to_pin(uint32_t button_idx)
{
    ASSERT(button_idx < BUTTONS_NUMBER);
    return m_board_btn_list[button_idx];
}
#endif //BUTTONS_NUMBER > 0