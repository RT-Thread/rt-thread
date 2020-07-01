/*
****************************************************************************
* Copyright (C) 2015 - 2016 Bosch Sensortec GmbH
*
* bmm050_support.c
* Date: 2016/03/17
* Revision: 1.0.6 $
*
* Usage: Sensor Driver support file for  BMM050 and BMM150 sensor
*
****************************************************************************
* License:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   Neither the name of the copyright holder nor the names of the
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
* OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*
* The information provided is believed to be accurate and reliable.
* The copyright holder assumes no responsibility
* for the consequences of use
* of such information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of the copyright holder.
**************************************************************************/

/*---------------------------------------------------------------------------*/
/* Includes*/
/*---------------------------------------------------------------------------*/
#include "bmm050.h"

/*----------------------------------------------------------------------------*/
/*  The following functions are used for reading and writing of
 *  sensor data using I2C or SPI communication
 *----------------------------------------------------------------------------*/
#ifdef BMM050_API
    /*  \Brief: The function is used as I2C bus read
    *  \Return : Status of the I2C read
    *  \param dev_addr : The device address of the sensor
    *  \param reg_addr : Address of the first register,
    *        will data is going to be read
    *  \param reg_data : This data read from the sensor,
    *        which is hold in an array
    *  \param cnt : The no of byte of data to be read
    */
    s8 BMM050_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /* \Brief: The function is used as I2C bus write
    *  \Return : Status of the I2C write
    *  \param dev_addr : The device address of the sensor
    *  \param reg_addr : Address of the first register,
    *              will data is going to be written
    *  \param reg_data : It is a value hold in the array,
    *      will be used for write the value into the register
    *  \param cnt : The no of byte of data to be write
    */
    s8 BMM050_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /*  \Brief: The function is used as SPI bus write
    *  \Return : Status of the SPI write
    *  \param dev_addr : The device address of the sensor
    *  \param reg_addr : Address of the first register,
    *              will data is going to be written
    *  \param reg_data : It is a value hold in the array,
    *      will be used for write the value into the register
    *  \param cnt : The no of byte of data to be write
    */
    s8 BMM050_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /*  \Brief: The function is used as SPI bus read
    *  \Return : Status of the SPI read
    *  \param dev_addr : The device address of the sensor
    *  \param reg_addr : Address of the first register,
    *             will data is going to be read
    *  \param reg_data : This data read from the sensor,
    *             which is hold in an array
    *  \param cnt : The no of byte of data to be read
    */
    s8 BMM050_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
    /*
    * \Brief: SPI/I2C init routine
    */
    s8 I2C_routine(void);
    s8 SPI_routine(void);
#endif
/********************End of I2C/SPI function declarations*********************/
/*  Brief : The delay routine
 *  \param : delay in ms
*/
void BMM050_delay_msek(u32 msek);
/* This function is an example for reading sensor data
 *  \param: None
 *  \return: communication result
 */
s32 bmm050_data_readout_template(void);
/*----------------------------------------------------------------------------*
 *  struct bmm050_t parameters can be accessed by using bmm050
 *  bmm050_t having the following parameters
 *  Bus write function pointer: BMM050_WR_FUNC_PTR
 *  Bus read function pointer: BMM050_RD_FUNC_PTR
 *  Burst read function pointer: BMM050_BRD_FUNC_PTR
 *  Delay function pointer: delay_msec
 *  I2C address: dev_addr
 *  Chip id of the sensor: chip_id
 *---------------------------------------------------------------------------*/
struct bmm050_t bmm050;
/*---------------------------------------------------------------------------*/
/* This function is an example for reading sensor data
 *  \param: None
 *  \return: communication result
 */
s32 bmm050_data_readout_template(void)
{
    /* Structure used for read the mag xyz data*/
    struct bmm050_mag_data_s16_t data;
    /* Structure used for read the mag xyz data with 32 bit output*/
    struct bmm050_mag_s32_data_t data_s32;
    /* Structure used for read the mag xyz data with float output*/
    struct bmm050_mag_data_float_t data_float;
    /* Variable used to get the data rate*/
    u8 v_data_rate_u8 = BMM050_INIT_VALUE;
    /* Variable used to set the data rate*/
    u8 v_data_rate_value_u8 = BMM050_INIT_VALUE;
    /* result of communication results*/
    s32 com_rslt = ERROR;

    /*---------------------------------------------------------------------------*
     *********************** START INITIALIZATION ************************
     *--------------------------------------------------------------------------*/
    /* Based on the user need configure I2C or SPI interface.
     * It is sample code to explain how to use the bmm050 API*/
#ifdef BMM050_API
    I2C_routine();
    /*SPI_routine(); */
#endif
    /*--------------------------------------------------------------------------*
     *  This function used to assign the value/reference of
     *  the following parameters
     *  I2C address
     *  Bus Write
     *  Bus read
     *  company_id
    *-------------------------------------------------------------------------*/
    com_rslt = bmm050_init(&bmm050);

    /*  For initialization it is required to set the mode of
     *  the sensor as "NORMAL"
     *  but before set the mode needs to configure the power control bit
     *  in the register 0x4B bit BMM050_INIT_VALUE should be enabled
     *  This bit is enabled by calling bmm050_init function
     *  For the Normal data acquisition/read/write is possible in this mode
     *  by using the below API able to set the power mode as NORMAL*/
    /* Set the power mode as NORMAL*/
    com_rslt += bmm050_set_functional_state(BMM050_NORMAL_MODE);
    /*--------------------------------------------------------------------------*
    ************************* END INITIALIZATION *************************
    *---------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*
    ************************* START GET and SET FUNCTIONS DATA ****************
    *---------------------------------------------------------------------------*/
    /* This API used to Write the data rate of the sensor, input
    value have to be given
    data rate value set from the register 0x4C bit 3 to 5*/
    v_data_rate_value_u8 = BMM050_DATA_RATE_30HZ;/* set data rate of 30Hz*/
    com_rslt += bmm050_set_data_rate(v_data_rate_value_u8);

    /* This API used to read back the written value of data rate*/
    com_rslt += bmm050_get_data_rate(&v_data_rate_u8);
    /*-----------------------------------------------------------------*
    ************************* END GET and SET FUNCTIONS ****************
    *-------------------------------------------------------------------*/
    /*------------------------------------------------------------------*
    ************************* START READ SENSOR DATA(X,Y and Z axis) ********
    *------------------------------------------------------------------*/
    /* accessing the bmm050_mdata parameter by using data*/
    /* Reads the mag x y z data*/
    com_rslt += bmm050_read_mag_data_XYZ(&data);


    /* accessing the bmm050_mdata_float parameter by using data_float*/
    /* Reads mag xyz data output as 32bit value*/
    com_rslt += bmm050_read_mag_data_XYZ_float(&data_float);

    /* accessing the bmm050_mdata_s32 parameter by using data_s32*/
    /* Reads mag xyz data output as float value*/
    com_rslt += bmm050_read_mag_data_XYZ_s32(&data_s32);

    /*--------------------------------------------------------------------*
    ************************* END READ SENSOR DATA(X,Y and Z axis) ************
    *-------------------------------------------------------------------------*/
    /*-----------------------------------------------------------------------*
    ************************* START DE-INITIALIZATION ***********************
    *-------------------------------------------------------------------------*/
    /*  For de-initialization it is required to set the mode of
     *  the sensor as "SUSPEND"
     *  the SUSPEND mode set from the register 0x4B bit BMM050_INIT_VALUE
     *             should be disabled
     *  by using the below API able to set the power mode as SUSPEND*/
    /* Set the power mode as SUSPEND*/
    com_rslt += bmm050_set_functional_state(BMM050_SUSPEND_MODE);
    /*---------------------------------------------------------------------*
    ************************* END DE-INITIALIZATION **********************
    *---------------------------------------------------------------------*/
    return com_rslt;
}

#ifdef BMM050_API
/*--------------------------------------------------------------------------*/
/*  The following function is used to map the I2C bus read, write, delay and
 *  device address with global structure bmm050
 *-------------------------------------------------------------------------*/
s8 I2C_routine(void)
{
    /*--------------------------------------------------------------------------*/
    /*  By using bmm050 the following structure parameter can be accessed
     *  Bus write function pointer: BMM050_WR_FUNC_PTR
     *  Bus read function pointer: BMM050_RD_FUNC_PTR
     *  Delay function pointer: delay_msec
     *  I2C address: dev_addr
     *--------------------------------------------------------------------------*/
    bmm050.bus_write = BMM050_I2C_bus_write;
    bmm050.bus_read = BMM050_I2C_bus_read;
    bmm050.delay_msec = BMM050_delay_msek;
    bmm050.dev_addr = BMM050_I2C_ADDRESS;

    return BMM050_INIT_VALUE;
}

/*---------------------------------------------------------------------------*/
/*  The following function is used to map the SPI bus read, write and delay
 *  with global structure bmm050
 *--------------------------------------------------------------------------*/
s8 SPI_routine(void)
{
    /*--------------------------------------------------------------------------*
     *  By using bmm050 the following structure parameter can be accessed
     *  Bus write function pointer: BMM050_WR_FUNC_PTR
     *  Bus read function pointer: BMM050_RD_FUNC_PTR
     *  Delay function pointer: delay_msec
     *--------------------------------------------------------------------------*/

    bmm050.bus_write = BMM050_SPI_bus_write;
    bmm050.bus_read = BMM050_SPI_bus_read;
    bmm050.delay_msec = BMM050_delay_msek;

    return BMM050_INIT_VALUE;
}

/************** SPI/I2C buffer length ******/
#define I2C_BUFFER_LEN 8
#define SPI_BUFFER_LEN 5
#define MASK_DATA1  0xFF
#define MASK_DATA2  0x80
#define MASK_DATA3  0x7F
#define C_BMM050_ONE_U8X    (1)
#define C_BMM050_TWO_U8X    (2)

/*-------------------------------------------------------------------*
*
*   This is a sample code for read and write the data by using I2C/SPI
*   Use either I2C or SPI based on your need
*   The device address defined in the bmm050.h file
*
*-----------------------------------------------------------------------*/
/* \Brief: The function is used as I2C bus write
*  \Return : Status of the I2C write
*  \param dev_addr : The device address of the sensor
*  \param reg_addr : Address of the first register,
*              will data is going to be written
*  \param reg_data : It is a value hold in the array,
*      will be used for write the value into the register
*  \param cnt : The no of byte of data to be write
*/
s8 BMM050_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMM050_INIT_VALUE;
    u8 array[I2C_BUFFER_LEN];
    u8 stringpos = BMM050_INIT_VALUE;

    array[BMM050_INIT_VALUE] = reg_addr;
    for (stringpos = BMM050_INIT_VALUE; stringpos < cnt; stringpos++)
        array[stringpos + C_BMM050_ONE_U8X] = *(reg_data + stringpos);
    /*
    * Please take the below function as your reference for
    * write the data using I2C communication
    * "IERROR = I2C_WRITE_STRING(DEV_ADDR, ARRAY, CNT+C_BMM050_ONE_U8X)"
    * add your I2C write function here
    * iError is an return value of I2C read function
    * Please select your valid return value
    * In the driver SUCCESS defined as BMM050_INIT_VALUE
    * and FAILURE defined as -C_BMM050_ONE_U8X
    * Note :
    * This is a full duplex operation,
    * The first read data is discarded, for that extra write operation
    * have to be initiated. For that cnt+C_BMM050_ONE_U8X operation done
    * in the I2C write string function
    * For more information please refer data sheet SPI communication:
    */
    return (s8)iError;
}

/* \Brief: The function is used as I2C bus read
*  \Return : Status of the I2C read
*  \param dev_addr : The device address of the sensor
*  \param reg_addr : Address of the first register,
*            will data is going to be read
*  \param reg_data : This data read from the sensor,
*            which is hold in an array
*  \param cnt : The no of byte of data to be read
*/
s8 BMM050_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMM050_INIT_VALUE;
    u8 array[I2C_BUFFER_LEN] = {BMM050_INIT_VALUE};
    u8 stringpos = BMM050_INIT_VALUE;

    array[BMM050_INIT_VALUE] = reg_addr;
    /* Please take the below function as your reference
     * for read the data using I2C communication
     * add your I2C rad function here.
     * "IERROR = I2C_WRITE_READ_STRING(
     *  DEV_ADDR, ARRAY, ARRAY, C_BMM050_ONE_U8X, CNT)"
     * iError is an return value of SPI write function
     * Please select your valid return value
     * In the driver SUCCESS defined as BMM050_INIT_VALUE
     * and FAILURE defined as -C_BMM050_ONE_U8X
     */
    for (stringpos = BMM050_INIT_VALUE; stringpos < cnt; stringpos++)
        *(reg_data + stringpos) = array[stringpos];

    return (s8)iError;
}

/*  \Brief: The function is used as SPI bus read
 *  \Return : Status of the SPI read
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register,
 *      will data is going to be read
 *  \param reg_data : This data read from the sensor,
 *              which is hold in an array
 *  \param cnt : The no of byte of data to be read
 */
s8 BMM050_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMM050_INIT_VALUE;
    u8 array[SPI_BUFFER_LEN] = {MASK_DATA1};
    u8 stringpos;
    /*  For the SPI mode only 7 bits of register addresses are used.
    The MSB of register address is declared the bit what functionality it is
    read/write (read as C_BMM050_ONE_U8X/write as BMM050_INIT_VALUE)*/
    /*read routine is initiated register address is mask with 0x80*/
    array[BMM050_INIT_VALUE] = reg_addr | MASK_DATA2;
    /*
    * Please take the below function as your reference for
    * read the data using SPI communication
    * " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+C_BMM050_ONE_U8X)"
    * add your SPI read function here
    * iError is an return value of SPI read function
    * Please select your valid return value
    * In the driver SUCCESS defined as BMM050_INIT_VALUE
    * and FAILURE defined as -1
    * Note :
    * This is a full duplex operation,
    * The first read data is discarded, for that extra write operation
    * have to be initiated. For that cnt+C_BMM050_ONE_U8X operation done
    * in the SPI read
    * and write string function
    * For more information please refer data sheet SPI communication:
    */
    for (stringpos = BMM050_INIT_VALUE; stringpos < cnt; stringpos++)
        *(reg_data + stringpos) = array[stringpos + C_BMM050_ONE_U8X];

    return (s8)iError;
}

/*  \Brief: The function is used as SPI bus write
 *  \Return : Status of the SPI write
 *  \param dev_addr : The device address of the sensor
 *  \param reg_addr : Address of the first register,
 *      will data is going to be written
 *  \param reg_data : It is a value hold in the array,
 *      will be used for write the value into the register
 *  \param cnt : The no of byte of data to be write
 */
s8 BMM050_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    s32 iError = BMM050_INIT_VALUE;
    u8 array[SPI_BUFFER_LEN * C_BMM050_TWO_U8X];
    u8 stringpos = BMM050_INIT_VALUE;

    for (stringpos = BMM050_INIT_VALUE; stringpos < cnt; stringpos++)
    {
        /* the operation of (reg_addr++)&0x7F done: because it ensure
        the BMM050_INIT_VALUE and C_BMM050_ONE_U8X of the given value
        It is done only for 8bit operation*/
        array[stringpos * C_BMM050_TWO_U8X] = (reg_addr++) & MASK_DATA3;
        array[stringpos * C_BMM050_TWO_U8X + C_BMM050_ONE_U8X] =
            *(reg_data + stringpos);
    }
    /* Please take the below function as your reference
     * for write the data using SPI communication
     * add your SPI write function here.
     * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*C_BMM050_TWO_U8X)"
     * iError is an return value of SPI write function
     * Please select your valid return value
     * In the driver SUCCESS defined as BMM050_INIT_VALUE
     * and FAILURE defined as -1
     */
    return (s8)iError;
}

/*  Brief : The delay routine
 *  \param : delay in ms
*/
void BMM050_delay_msek(u32 msek)
{
    /*Here you can write your own delay routine*/
}
#endif
