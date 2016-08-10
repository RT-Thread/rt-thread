FXOS8700CQ Driver {#fxos}
================
@ingroup fxos

# Overview

The FXOS8700CQ library driver is used to access FXOS8700CQ chip via I2C.

# Add I2C interface

FXOS8700CQ driver can be hooked by a I2C interface, which means that user should pass their I2C driver interface to it.

~~~~~{.c}
i2c_interface.slave.address = BOARD_FXOS8700_I2C_ADDR;
i2c_interface.slave.baudRate_kbps = 100;
i2c_interface.i2c_init = i2c_gpio_init;
i2c_interface.i2c_probe = i2c_gpio_probe;
i2c_interface.i2c_read = i2c_gpio_read;
i2c_interface.i2c_write = i2c_gpio_write;
fxos_dev.i2c = &i2c_interface;
err = fxos_Init(&fxos_dev);
~~~~~

# Use function to get Sensor data

Normally we use fxos_ReadSensorData() to get sensor data.

~~~~~{.c}
/* Read acceleration data. */
fxos_sensorData_t sensorData;

fxos_ReadSensorData(&sensorData);
}
~~~~~

# Interrupt handling (not supported yet)

It is more common for user to use INT1 and INT2 pin interrupt of FXOS8700CQ to check for sensor position change.
This feature is not supported yet.

