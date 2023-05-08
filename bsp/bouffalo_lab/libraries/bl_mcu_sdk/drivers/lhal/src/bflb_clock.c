#include "bflb_clock.h"
#if defined(BL702)
#include "bl702_clock.h"
#elif defined(BL702L)
#include "bl702l_clock.h"
#elif defined(BL606P)
#include "bl606p_clock.h"
#elif defined(BL808)
#include "bl808_clock.h"
#elif defined(BL616)
#include "bl616_clock.h"
#elif defined(WB03)
#include "wb03_clock.h"
#elif defined(BL628)
#include "bl628_clock.h"
#endif

/****************************************************************************/ /**
 * @brief  get system clock
 *
 * @param  type: BFLB_SYSTEM_XXX
 *
 * @return NONE
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION bflb_clk_get_system_clock(uint8_t type)
{
    switch (type) {
        case BFLB_SYSTEM_ROOT_CLOCK:
            return bflb_clock_get_root();
        case BFLB_SYSTEM_CPU_CLK:
            return bflb_clock_get_fclk();
        case BFLB_SYSTEM_PBCLK:
            return bflb_clock_get_bclk();
        case BFLB_SYSTEM_XCLK:
            return bflb_clock_get_xclk();
        case BFLB_SYSTEM_32K_CLK:
            return bflb_clock_get_f32k();
        default:
            return 0;
    }
    return 0;
}

/****************************************************************************/ /**
 * @brief  get peripheral clock
 *
 * @param  type: BFLB_DEVICE_TYPE_XXX
 * @param  idx: peripheral index
 *
 * @return NONE
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION bflb_clk_get_peripheral_clock(uint8_t type, uint8_t idx)
{
    switch (type) {
        case BFLB_DEVICE_TYPE_ADC:
            return bflb_clock_get_adc();
        case BFLB_DEVICE_TYPE_DAC:
            return bflb_clock_get_dac();
        case BFLB_DEVICE_TYPE_UART:
            return bflb_clock_get_uart();
        case BFLB_DEVICE_TYPE_SPI:
            return bflb_clock_get_spi();
        case BFLB_DEVICE_TYPE_I2C:
            return bflb_clock_get_i2c();
        case BFLB_DEVICE_TYPE_PWM:
            return bflb_clock_get_pwm();
        case BFLB_DEVICE_TYPE_TIMER:
            return bflb_clock_get_timer(idx);
        case BFLB_DEVICE_TYPE_WDT:
            return bflb_clock_get_wdt();
        case BFLB_DEVICE_TYPE_FLASH:
            return bflb_clock_get_flash();
        case BFLB_DEVICE_TYPE_IR:
            return bflb_clock_get_ir();
        case BFLB_DEVICE_TYPE_PKA:
            return bflb_clock_get_pka();
        case BFLB_DEVICE_TYPE_SDH:
            return bflb_clock_get_sdh();
        case BFLB_DEVICE_TYPE_CAMERA:
            return bflb_clock_get_cam();
        case BFLB_DEVICE_TYPE_DBI:
            return bflb_clock_get_dbi();
        case BFLB_DEVICE_TYPE_I2S:
            return bflb_clock_get_i2s();
        default:
            return 0;
    }
    return 0;
}
