#include "core-v-mcu-config.h"
#include "hal_apb_i2cs_reg_defs.h"

uint8_t hal_get_apb_i2cs_slave_address(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_dev_address_b.slave_addr;
}

void hal_set_apb_i2cs_slave_address(uint8_t aSlaveAddress)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*) I2CS_START_ADDR;
	apbI2cSlave->i2cs_dev_address_b.slave_addr = aSlaveAddress;
}

uint8_t hal_set_apb_i2cs_slave_on_off(uint8_t aStatus)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	if( aStatus == 1 )
		apbI2cSlave->i2cs_enable_b.ip_enable = 1;
	else if( aStatus == 0 )
		apbI2cSlave->i2cs_enable_b.ip_enable = 0;
	return (uint8_t)apbI2cSlave->i2cs_enable_b.ip_enable;
}


uint8_t hal_get_i2cs_fifo_i2c_apb_read_data_port(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_fifo_i2c_apb_read_data_port;
}

void hal_set_i2cs_fifo_apb_i2c_write_data_port(uint8_t aData)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*) I2CS_START_ADDR;
	apbI2cSlave->i2cs_fifo_apb_i2c_write_data_port = aData;
}

uint8_t hal_get_i2cs_fifo_i2c_apb_write_flags(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_fifo_i2c_apb_write_flags;
}


uint8_t hal_get_i2cs_fifo_i2c_apb_read_flags(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_fifo_i2c_apb_read_flags;
}

uint8_t hal_get_i2cs_fifo_apb_i2c_read_flags(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_fifo_apb_i2c_read_flags;
}

uint8_t hal_get_i2cs_fifo_apb_i2c_write_flags(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_fifo_apb_i2c_write_flags;
}


uint8_t hal_get_i2cs_msg_i2c_apb(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*) I2CS_START_ADDR;
	return (apbI2cSlave->i2cs_msg_i2c_apb);
}

uint8_t hal_get_i2cs_msg_i2c_apb_status(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_msg_i2c_apb_status;
}


void hal_set_i2cs_msg_apb_i2c(uint8_t aData)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*) I2CS_START_ADDR;
	apbI2cSlave->i2cs_msg_apb_i2c = aData;
}

uint8_t hal_get_i2cs_msg_apb_i2c_status(void)
{

	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	return (uint8_t )apbI2cSlave->i2cs_msg_apb_i2c_status;
}


void hal_i2cs_fifo_i2c_apb_FIFO_flush(void)
{
	int i = 0;
	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	apbI2cSlave->i2cs_fifo_i2c_apb_flush_b.enable = 1;
	for( i=0; i<1000; i++);
	apbI2cSlave->i2cs_fifo_i2c_apb_flush_b.enable = 0;
	for( i=0; i<1000; i++);
}

void hal_i2cs_fifo_apb_i2c_FIFO_flush(void)
{
	int i = 0;
	ApbI2cs_t *apbI2cSlave = (ApbI2cs_t*)I2CS_START_ADDR;
	apbI2cSlave->i2cs_fifo_apb_i2c_flush_b.enable = 1;
	for( i=0; i<1000; i++);
	apbI2cSlave->i2cs_fifo_apb_i2c_flush_b.enable = 0;
	for( i=0; i<1000; i++);
}
