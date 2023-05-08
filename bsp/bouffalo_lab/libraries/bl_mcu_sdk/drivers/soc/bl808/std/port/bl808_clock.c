#include "bflb_clock.h"
#include "bl808_clock.h"

uint32_t bflb_clk_get_system_clock(uint8_t type)
{
    return 0;
}

uint32_t bflb_clk_get_peripheral_clock(uint8_t type, uint8_t idx)
{
    if (type == BFLB_DEVICE_TYPE_UART) {
        return Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_UART0);
    } else if (type == BFLB_DEVICE_TYPE_SPI) {
        return Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_SPI0);
    } else if (type == BFLB_DEVICE_TYPE_I2C) {
        return Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_I2C0);
    } else if (type == BFLB_DEVICE_TYPE_SDH) {
        return Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_SDH);
    }
    return 0;
}