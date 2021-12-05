#ifndef __PM_CFG_H__
#define __PM_CFG_H__

enum pm_module_id
{
    PM_NONE_ID = 0,
    PM_POWER_ID,
    PM_BOARD_ID,
    PM_LCD_ID,
    PM_KEY_ID,
    PM_TP_ID,
    PM_OTA_ID,
    PM_SPI_ID,
    PM_I2C_ID,
    PM_ADC_ID,
    PM_RTC_ID,
    PM_GPIO_ID,
    PM_UART_ID,
    PM_SENSOR_ID,
    PM_ALARM_ID,
    PM_BLE_ID,
    PM_MODULE_MAX_ID, /* enum must! */
};

#endif
