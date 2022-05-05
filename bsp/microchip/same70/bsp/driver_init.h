/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_H_INCLUDED
#define DRIVER_INIT_H_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_adc_sync.h>

#include <hal_i2c_m_sync.h>
#include <hal_usart_async.h>

#include <hal_mac_async.h>
#include <hal_can_async.h>

extern struct adc_sync_descriptor ADC_0;

#define CONF_ADC_0_CHANNEL_10 10

extern struct i2c_m_sync_desc        I2C_0;
extern struct usart_async_descriptor TARGET_IO;

extern struct mac_async_descriptor MACIF;
extern struct can_async_descriptor CAN_0;

void ADC_0_PORT_init(void);
void ADC_0_CLOCK_init(void);
void ADC_0_init(void);

void I2C_0_CLOCK_init(void);
void I2C_0_init(void);
void I2C_0_PORT_init(void);

void TARGET_IO_PORT_init(void);
void TARGET_IO_CLOCK_init(void);
void TARGET_IO_init(void);

void MACIF_CLOCK_init(void);
void MACIF_init(void);
void MACIF_PORT_init(void);

void CAN_0_PORT_init(void);
void CAN_0_CLOCK_init(void);
void CAN_0_init(void);
void CAN_0_example(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_H_INCLUDED
