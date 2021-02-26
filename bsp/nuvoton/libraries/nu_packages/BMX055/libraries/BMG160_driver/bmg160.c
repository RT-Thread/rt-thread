/*
****************************************************************************
* Copyright (C) 2010 - 2015 Bosch Sensortec GmbH
*
* bmg160.c
* Date: 2015/04/29
* Revision: 2.0.4 $
*
* Usage: Sensor Driver for BMG160 sensor
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
/*! file bmg160.c
    brief Driver for BMG160 */
#include "bmg160.h"
static struct bmg160_t *p_bmg160;


/*!
 *  @brief This function is used for initialize
 *  the bus read and bus write functions
 *  and assign the chip id and I2C address of the gyro
 *  chip id is read in the register 0x00 bit from 0 to 7
 *
 *  @param bmg160 structure pointer.
 *
 *  @note While changing the parameter of the bmg160_t
 *  consider the following point:
 *  @note Changing the reference value of the parameter
 *  will changes the local copy or local reference
 *  make sure your changes will not
 *  affect the reference value of the parameter
 *  (Better case don't change the reference value of the parameter)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_init(struct bmg160_t *bmg160)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* Assign the initial function pointers*/
    p_bmg160 = bmg160;
    /*Read CHIP_ID */
    comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                            BMG160_CHIP_ID_ADDR, &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    p_bmg160->chip_id = v_data_u8;
    return comres;
}
/*!
 * @brief Reads Rate data X in the registers 0x02 to 0x03
 *
 *
 *
 *
 *  @param v_data_x_s16: The value of gyro x axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
*   @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_X(s16 *v_data_x_s16)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres  = BMG160_INIT_VALUE;
    /*Array holding the gyro data x LSB and MSB data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    */
    u8 v_data_u8[BMG160_X_DATA_SIZE] =
    {
        BMG160_INIT_VALUE, BMG160_INIT_VALUE
    };
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the gyro x data */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RATE_X_LSB_BIT__REG,
                                                v_data_u8, BMG160_X_DATA_LENGTH);
        v_data_u8[BMG160_X_LSB_DATA] = BMG160_GET_BITSLICE(
                                           v_data_u8[BMG160_X_LSB_DATA],
                                           BMG160_RATE_X_LSB_BIT);
        *v_data_x_s16 = (s16)
                        ((((s32)((s8)v_data_u8[BMG160_X_MSB_DATA])) <<
                          BMG160_SHIFT_BIT_POSITION_BY_08_BITS)
                         | (v_data_u8[BMG160_X_LSB_DATA]));
    }
    return comres;
}
/*!
 * @brief Reads Rate data Y in the registers 0x04 to 0x05
 *
 *
 *
 *
 *  @param v_data_y_s16: The value of gyro y axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_Y(s16 *v_data_y_s16)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /*Array holding the gyro data y LSB and MSB data
    v_data_u8[0] - Y LSB
    v_data_u8[1] - Y MSB
    */
    u8 v_data_u8[BMG160_Y_DATA_SIZE] =
    {
        BMG160_INIT_VALUE, BMG160_INIT_VALUE
    };
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the gyro  y data*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(
                     p_bmg160->dev_addr,
                     BMG160_RATE_Y_LSB_BIT__REG, v_data_u8,
                     BMG160_Y_DATA_LENGTH);
        v_data_u8[BMG160_Y_LSB_DATA] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_Y_LSB_DATA],
                                BMG160_RATE_Y_LSB_BIT);
        *v_data_y_s16 = (s16)
                        ((((s32)((s8)v_data_u8[BMG160_Y_MSB_DATA]))
                          << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                         (v_data_u8[BMG160_Y_LSB_DATA]));
    }
    return comres;
}
/*!
 *  @brief Reads Rate data Z in the registers 0x06 to 0x07
 *
 *
 *  @param v_data_z_s16: The value of gyro z axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_Z(s16 *v_data_z_s16)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /*Array holding the gyro data z LSB and MSB data
    v_data_u8[0] - Z LSB
    v_data_u8[1] - Z MSB
    */
    u8 v_data_u8[BMG160_Z_DATA_SIZE] =
    {
        BMG160_INIT_VALUE, BMG160_INIT_VALUE
    };
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RATE_Z_LSB_BIT__REG,
                                                v_data_u8, BMG160_Z_DATA_LENGTH);
        v_data_u8[BMG160_Z_LSB_DATA] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_Z_LSB_DATA],
                                BMG160_RATE_Z_LSB_BIT);
        *v_data_z_s16 = (s16)
                        ((((s32)((s8)v_data_u8[BMG160_Z_MSB_DATA]))
                          << BMG160_SHIFT_BIT_POSITION_BY_08_BITS)
                         | (v_data_u8[BMG160_Z_LSB_DATA]));
    }
    return comres;
}
/*!
 * @brief Reads data X,Y and Z from register location 0x02 to 0x07
 *
 *
 *
 *
 *  @param data: The value of gyro xyz axis data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_XYZ(struct bmg160_data_t *data)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /*Array holding the gyro data xyz LSB and MSB data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y MSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z MSB
    v_data_u8[5] - Z MSB
    */
    u8 v_data_u8[BMG160_XYZ_DATA_SIZE] =
    {
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE
    };
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RATE_X_LSB_BIT__REG, v_data_u8,
                                                BMG160_ALL_DATA_FRAME_LENGTH);
        /* Data X */
        v_data_u8[BMG160_DATA_FRAME_X_LSB_BYTE] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_DATA_FRAME_X_LSB_BYTE],
                                BMG160_RATE_X_LSB_BIT);
        data->datax = (s16)
                      ((((s32)((s8)v_data_u8[BMG160_DATA_FRAME_X_MSB_BYTE]))
                        << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                       (v_data_u8[BMG160_DATA_FRAME_X_LSB_BYTE]));
        /* Data Y */
        v_data_u8[BMG160_DATA_FRAME_Y_LSB_BYTE] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_DATA_FRAME_Y_LSB_BYTE],
                                BMG160_RATE_Y_LSB_BIT);
        data->datay = (s16)
                      ((((s32)((s8)v_data_u8[BMG160_DATA_FRAME_Y_MSB_BYTE]))
                        << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                       (v_data_u8[BMG160_DATA_FRAME_Y_LSB_BYTE]));
        /* Data Z */
        v_data_u8[BMG160_DATA_FRAME_Z_LSB_BYTE] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_DATA_FRAME_Z_LSB_BYTE],
                                BMG160_RATE_Z_LSB_BIT);
        data->dataz = (s16)
                      ((((s32)((s8)v_data_u8[BMG160_DATA_FRAME_Z_MSB_BYTE]))
                        << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                       (v_data_u8[BMG160_DATA_FRAME_Z_LSB_BYTE]));
    }
    return comres;
}
/*!
 *  @brief Reads data X,Y,Z and Interrupts
 *  from register location 0x02 to 0x07
 *
 *
 *  @param data: The value of gyro xyz axis data and interrupt status
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_XYZI(struct bmg160_data_t *data)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /*Array holding the gyro data xyz LSB and MSB data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y MSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z MSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - INVALID
    v_data_u8[7] - INTR STATUS1
    v_data_u8[8] - INTR STATUS2
    v_data_u8[9] - INTR STATUS3
    v_data_u8[10] - INTR STATUS4
    v_data_u8[11] - INTR STATUS5
    */
    u8 v_data_u8[BMG160_XYZ_INTR_DATA_SIZE] =
    {
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE,
        BMG160_INIT_VALUE, BMG160_INIT_VALUE
    };
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RATE_X_LSB_BIT__REG, v_data_u8,
                                                BMG160_XYZ_AND_INTR_DATA_LENGTH);
        /* Data X */
        v_data_u8[BMG160_DATA_FRAME_X_LSB_BYTE] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_DATA_FRAME_X_LSB_BYTE],
                                BMG160_RATE_X_LSB_BIT);
        data->datax = (s16)
                      ((((s32)((s8)v_data_u8[BMG160_DATA_FRAME_X_MSB_BYTE]))
                        << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                       (v_data_u8[BMG160_DATA_FRAME_X_LSB_BYTE]));
        /* Data Y */
        v_data_u8[BMG160_DATA_FRAME_Y_LSB_BYTE] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_DATA_FRAME_Y_LSB_BYTE],
                                BMG160_RATE_Y_LSB_BIT);
        data->datay = (s16)
                      ((((s32)((s8)v_data_u8[BMG160_DATA_FRAME_Y_MSB_BYTE]))
                        << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                       (v_data_u8[BMG160_DATA_FRAME_Y_LSB_BYTE]));
        /* Data Z */
        v_data_u8[BMG160_DATA_FRAME_Z_LSB_BYTE] =
            BMG160_GET_BITSLICE(v_data_u8[BMG160_DATA_FRAME_Z_LSB_BYTE],
                                BMG160_RATE_Z_LSB_BIT);
        data->dataz = (s16)
                      ((((s32)((s8)v_data_u8[BMG160_DATA_FRAME_Z_MSB_BYTE]))
                        << BMG160_SHIFT_BIT_POSITION_BY_08_BITS) |
                       (v_data_u8[BMG160_DATA_FRAME_Z_LSB_BYTE]));
        /* interrupt*/
        data->intstatus[BMG160_INTR0_STAT] =
            v_data_u8[BMG160_DATA_FRAME_INTR0_BYTE];
        data->intstatus[BMG160_INTR1_STAT] =
            v_data_u8[BMG160_DATA_FRAME_INTR1_BYTE];
        data->intstatus[BMG160_INTR2_STAT] =
            v_data_u8[BMG160_DATA_FRAME_INTR2_BYTE];
        data->intstatus[BMG160_INTR3_STAT] =
            v_data_u8[BMG160_DATA_FRAME_INTR3_BYTE];
        data->intstatus[BMG160_INTR4_STAT] =
            v_data_u8[BMG160_DATA_FRAME_INTR4_BYTE];
    }
    return comres;
}
/*!
 * @brief Reads Temperature from register location 0x08
 *
 *
 *
 *
 *  @param v_temp_s8: The value of temperature
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_temp(s8 *v_temp_s8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read temperature data*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TEMP_ADDR, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_temp_s8 = v_data_u8;
    }
    return comres;
}
/*!
 * @brief
 *  This API reads the data from
 *  the given register
 *
 *
 *  @param v_addr_u8 -> Address of the register
 *  @param v_data_u8 -> The data from the register
 *  @param v_len_u8 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMG160_RETURN_FUNCTION_TYPE bmg160_read_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr, v_addr_u8, v_data_u8, v_len_u8);
    }
    return comres;
}
/*!
 * @brief
 *  This API reads the data from
 *  the given register
 *
 *
 *  @param v_addr_u8 -> Address of the register
 *  @param v_data_u8 -> The data from the register
 *  @param v_len_u32 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMG160_RETURN_FUNCTION_TYPE bmg160_burst_read(u8 v_addr_u8,
        u8 *v_data_u8, u32 v_len_u32)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BURST_READ_FUNC(p_bmg160->dev_addr,
                 v_addr_u8, v_data_u8, v_len_u32);
    }
    return comres;
}
/*!
 * @brief
 *  This API write the data to
 *  the given register
 *
 *
 *  @param v_addr_u8 -> Address of the register
 *  @param v_data_u8 -> The data from the register
 *  @param v_len_u8 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMG160_RETURN_FUNCTION_TYPE bmg160_write_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                 (p_bmg160->dev_addr, v_addr_u8, v_data_u8, v_len_u8);
    }
    return comres;
}
/*!
 *  @brief This api used to reads interrupt status of
 *  any motion and high rate in the register 0x09
 *  @note  any motion bit   ->  2
 *  @note high rate bit ->  1
 *
 *
 *
 *  @param v_stat0_data_u8 : The interrupt status of
 *  any motion and high rate
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_zero(
    u8 *v_stat0_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the interrupt status any motion and high rate*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_INTR_STAT_ZERO__REG, &v_data_u8,
                  BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_stat0_data_u8 =
            BMG160_GET_BITSLICE(v_data_u8, BMG160_INTR_STAT_ZERO);
    }
    return comres;
}
/*!
 *  @brief This api used to reads the interrupt status of
 *  data, auto_offset, fast_offset and fifo_int in the register 0x0A
 *  @note data bit          ->  7
 *  @note auto_offset bit   ->  6
 *  @note fast_offset bit   ->  5
 *  @note fifo_int bit      ->  4
 *
 *
 *
 *  @param
 *  v_stat1_data_u8 : The interrupt status of
 *  data, auto_offset, fast_offset and fifo_int
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_one(
    u8 *v_stat1_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the interrupt status*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr, BMG160_INTR_STAT_ONE__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_stat1_data_u8 =
            BMG160_GET_BITSLICE(v_data_u8, BMG160_INTR_STAT_ONE);
    }
    return comres;
}
/*!
 *  @brief This api used to reads the interrupt status of
 *  @note any motion sign, any motion first_z, any motion
 *  first_x and any motion first_y in the register 0x0B
 *  @note any motion sign bit       ->  3
 *  @note any motion first_z bit    ->  2
 *  @note any motion first_x bit    ->  1
 *  @note any motion first_y bit    ->  0
 *
 *
 *
 *  @param
 *  v_stat2_data_u8 : Pointer holding the the interrupt status of
 *  any motion sign, any motion first_z,
 *  any motion first_x and any motion first_y
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_two(
    u8 *v_stat2_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the interrupt status */
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_INTR_STAT_TWO__REG, &v_data_u8,
                  BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_stat2_data_u8 =
            BMG160_GET_BITSLICE(v_data_u8, BMG160_INTR_STAT_TWO);
    }
    return comres;
}
/*!
*  @brief This api used to reads the interrupt status of
*  high_rate sign, high_rate first_z, high_rate first_x
*  and high_rate first_y in the register 0x0C
*  @note high_rate sign bit        ->  3
*  @note high_rate first_z bit ->  2
*  @note high_rate first_x bit ->  1
*  @note high_rate first_y bit ->  0
*  @note high_rate first_y bit ->  0
*
*
*
*  @param
*  v_stat3_data_u8 : The interrupt status of
*  high_rate sign, high_rate first_z,
*  high_rate first_x and high_rate first_y
*
*
*  @return results of bus communication function
*  @retval 0 -> Success
*  @retval -1 -> Error
*
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_stat_reg_three(
    u8 *v_stat3_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the interrupt status */
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_INTR_STAT_THREE__REG, &v_data_u8,
                  BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_stat3_data_u8 =
            BMG160_GET_BITSLICE(v_data_u8, BMG160_INTR_STAT_THREE);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the range in the register 0x0F bits from 0 to 2
 *
 *  @param v_range_u8 : The value of gyro range
 *  value    |   range
 * ----------|-----------
 *    0x00   | BMG160_RANGE_2000
 *    0x01   | BMG160_RANGE_1000
 *    0x02   | BMG160_RANGE_500
 *    0x03   | BMG160_RANGE_250
 *    0x04   | BMG160_RANGE_125
 *
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_range_reg(u8 *v_range_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the gyro range */
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_RANGE_ADDR_RANGE__REG, &v_data_u8,
                  BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_range_u8 =
            BMG160_GET_BITSLICE(v_data_u8, BMG160_RANGE_ADDR_RANGE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the range in the register 0x0F bits from 0 to 2
 *
 *  @param v_range_u8 : The value of gyro range
 *  value    |   range
 * ----------|-----------
 *    0x00   | BMG160_RANGE_2000
 *    0x01   | BMG160_RANGE_1000
 *    0x02   | BMG160_RANGE_500
 *    0x03   | BMG160_RANGE_250
 *    0x04   | BMG160_RANGE_125
 *
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_range_reg(u8 v_range_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_range_u8 < BMG160_BIT_LENGTH_RANGE)
        {
            /* write the range*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_RANGE_ADDR_RANGE__REG, &v_data_u8,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_RANGE_ADDR_RANGE,
                                            v_range_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_RANGE_ADDR_RANGE__REG, &v_data_u8,
                       BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the gyro bandwidth
 *  in the register 0x10 bits from 0 to 3
 *
 *
 *
 *
 *
 *  @param  v_bw_u8: The value of gyro bandwidth
 *  value   |  bandwidth
 * ---------|---------------
 *   0x00   |  BMG160_BW_500_HZ
 *   0x01   |  BMG160_BW_230_HZ
 *   0x02   |  BMG160_BW_116_HZ
 *   0x03   |  BMG160_BW_47_HZ
 *   0x04   |  BMG160_BW_23_HZ
 *   0x05   |  BMG160_BW_12_HZ
 *   0x06   |  BMG160_BW_64_HZ
 *   0x07   |  BMG160_BW_32_HZ
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_bw(u8 *v_bw_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read gyro bandwidth*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr, BMG160_BW_ADDR__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_bw_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                       BMG160_BW_ADDR);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the gyro bandwidth
 *  in the register 0x10 bits from 0 to 3
 *
 *
 *
 *
 *
 *  @param  v_bw_u8: The value of gyro bandwidth
 *  value   |  bandwidth
 * ---------|---------------
 *   0x00   |  BMG160_BW_500_HZ
 *   0x01   |  BMG160_BW_230_HZ
 *   0x02   |  BMG160_BW_116_HZ
 *   0x03   |  BMG160_BW_47_HZ
 *   0x04   |  BMG160_BW_23_HZ
 *   0x05   |  BMG160_BW_12_HZ
 *   0x06   |  BMG160_BW_64_HZ
 *   0x07   |  BMG160_BW_32_HZ
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_bw(u8 v_bw_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    u8 v_mode_u8r  = BMG160_INIT_VALUE;
    u8 v_auto_sleep_dur = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_bw_u8 < BMG160_BIT_LENGTH_BW)
        {
            comres = bmg160_get_power_mode(&v_mode_u8r);
            if (v_mode_u8r == BMG160_MODE_ADVANCEDPOWERSAVING)
            {
                /* check the advance power save mode */
                comres = bmg160_get_auto_sleep_durn(
                             &v_auto_sleep_dur);
                comres = bmg160_set_auto_sleep_durn(
                             v_auto_sleep_dur,
                             v_bw_u8);
            }
            /* read gyro bandwidth*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_BW_ADDR__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_BW_ADDR, v_bw_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_BW_ADDR__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API used to get the status of
 *  External Trigger selection in the register 0x12h bits from 4 to 5
 *
 *
 *
 *
 *  @param v_pwu_ext_tri_select_u8 : The value of External Trigger selection
 *  v_pwu_ext_tri_select_u8  |  Trigger source
 * --------------------------|-------------------------
 *      0x00                 |      No
 *      0x01                 |   INT1 pin
 *      0x02                 |   INT2 pin
 *      0x03                 |  SDO pin(SPI3 mode)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_pmu_ext_tri_select(
    u8 *v_pwu_ext_tri_select_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* READ PMU TRIGGER*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_pwu_ext_tri_select_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                   BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT);
    }
    return comres;
}
/*!
 *  @brief This API used to set the status of
 *  External Trigger selection in the register 0x12h bits from 4 to 5
 *
 *
 *
 *
 *  @param v_pwu_ext_tri_select_u8 : The value of External Trigger selection
 *  v_pwu_ext_tri_select_u8  |  Trigger source
 * --------------------------|-------------------------
 *      0x00                 |      No
 *      0x01                 |   INT1 pin
 *      0x02                 |   INT2 pin
 *      0x03                 |  SDO pin(SPI3 mode)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_pmu_ext_tri_select(
    u8 v_pwu_ext_tri_select_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* WRITE PMU TRIGGER*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT, v_pwu_ext_tri_select_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_MODE_LPM2_ADDR_EXT_TRI_SELECT__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief  This API is used to get data high bandwidth
 *  in the register 0x13 bit 7
 *
 *
 *
 *  @param v_high_bw_u8 : The value of high bandwidth
 *  value   |  Description
 * ---------|--------------
 *    1     | unfiltered
 *    0     | filtered
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_bw(u8 *v_high_bw_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read high bandwidth*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_HIGH_BW__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_high_bw_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                            BMG160_HIGH_BW);
    }
    return comres;
}
/*!
 *  @brief  This API is used to set data high bandwidth
 *  in the register 0x13 bit 7
 *
 *
 *
 *  @param v_high_bw_u8 : The value of high bandwidth
 *  value   |  Description
 * ---------|--------------
 *    1     | unfiltered
 *    0     | filtered
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_bw(u8 v_high_bw_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_high_bw_u8 < BMG160_BIT_LENGTH_HIGH_BW)
        {
            /* write high bandwidth*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGH_BW__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGH_BW, v_high_bw_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGH_BW__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief  This API is used to get the shadow dis
 *  in the register 0x13 bit 6
 *
 *
 *
 *  @param v_shadow_dis_u8 : The value of shadow dis
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_shadow_dis(u8 *v_shadow_dis_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read shadow dis*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_SHADOW_DIS__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_shadow_dis_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_SHADOW_DIS);
    }
    return comres;
}
/*!
 *  @brief  This API is used to set the shadow dis
 *  in the register 0x13 bit 6
 *
 *
 *
 *  @param v_shadow_dis_u8 : The value of shadow dis
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_shadow_dis(u8 v_shadow_dis_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_shadow_dis_u8 < BMG160_BIT_LENGTH_SHADOW_DIS)
        {
            /* write shadow dis*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SHADOW_DIS__REG, &v_data_u8,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_SHADOW_DIS, v_shadow_dis_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_SHADOW_DIS__REG, &v_data_u8,
                       BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  This function is used for the soft reset
 *  The soft reset register will be written with 0xB6 in the register 0x14.
 *
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_soft_rst(void)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_soft_rst_u8  = BMG160_INIT_VALUE;

    v_soft_rst_u8 = BMG160_SOFT_RESET;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write soft reset*/
        comres = p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                 BMG160_BGW_SOFT_RST_ADDR, &v_soft_rst_u8,
                 BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the data(data_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 7
 *
 *
 *
 *
 *  @param v_data_enable_u8 : The value of data enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_enable(u8 *v_data_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the data enable interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_ENABLE0_DATA__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_data_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_INTR_ENABLE0_DATA);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the data(data_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 7
 *
 *
 *
 *
 *  @param v_data_enable_u8 : The value of data enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_data_enable(u8 v_data_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write the data enable interrupt*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_INTR_ENABLE0_DATA__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_ENABLE0_DATA, v_data_enable_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                  (p_bmg160->dev_addr,
                   BMG160_INTR_ENABLE0_DATA__REG,
                   &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the fifo(fifo_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 6
 *
 *
 *
 *
 *  @param v_fifo_enable_u8 : The value of  fifo enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_enable(u8 *v_fifo_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the fifo enable */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_ENABLE0_FIFO__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_INTR_ENABLE0_FIFO);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the fifo(fifo_enable)
 *  interrupt enable bits of the sensor in the registers 0x15 bit 6
 *
 *
 *
 *
 *  @param v_fifo_enable_u8 : The value of  fifo enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_enable(u8 v_fifo_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_fifo_enable_u8 < BMG160_BIT_LENGTH_FIFO)
        {
            /* write the fifo enable */
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE0_FIFO__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ENABLE0_FIFO, v_fifo_enable_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ENABLE0_FIFO__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the auto offset(auto_offset_enable) interrupt enable bits of
 *  the sensor in the registers 0x15 bit 3
 *
 *
 *
 *  @param v_offset_enable_u8 : The value of offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_auto_offset_enable(
    u8 *v_offset_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read auto offset*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_ENABLE0_AUTO_OFFSET__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_offset_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                              BMG160_INTR_ENABLE0_AUTO_OFFSET);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the auto offset(auto_offset_enable) interrupt enable bits of
 *  the sensor in the registers 0x15 bit 3
 *
 *
 *
 *  @param v_offset_enable_u8 : The value of offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_auto_offset_enable(u8 v_offset_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write auto offset */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_ENABLE0_AUTO_OFFSET__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_ENABLE0_AUTO_OFFSET, v_offset_enable_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_ENABLE0_AUTO_OFFSET__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the output type status in the register 0x16.
 *  @note INT1 -> bit 1
 *  @note INT2 -> bit 3
 *
 *  @param  v_param_u8: The value of output type selection number
 *    v_param_u8| output type
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param v_intr_output_type_u8: The value of output type
 *   value    |  output
 * -----------|-------------
 *    1       | open drain
 *    0       | push pull
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_output_type(u8 v_param_u8,
        u8 *v_intr_output_type_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* read output type*/
        case BMG160_INTR1:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr_output_type_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                     BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE);
            break;
        case BMG160_INTR2:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr_output_type_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                     BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the output type status in the register 0x16.
 *  @note INT1 -> bit 1
 *  @note INT2 -> bit 3
 *
 *  @param  v_param_u8: The value of output type selection number
 *    v_param_u8| output type
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param v_intr_output_type_u8: The value of output type
 *   value    |  output
 * -----------|-------------
 *    1       | open drain
 *    0       | push pull
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_output_type(u8 v_param_u8,
        u8 v_intr_output_type_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* write output type*/
        case BMG160_INTR1:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE,
                                            v_intr_output_type_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ENABLE1_IT1_OUTPUT_TYPE__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_INTR2:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE,
                                            v_intr_output_type_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ENABLE1_IT2_OUTPUT_TYPE__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  Active Level status in the register 0x16
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 2
 *
 *  @param  v_param_u8: The value of Active Level selection number
 *    v_param_u8| Active Level
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param  v_intr_level_u8: The  value of Active Level status value
 *   value    |  Active Level
 * -----------|-------------
 *    1       | Active HIGH
 *    0       | Active LOW
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_level(u8 v_param_u8,
        u8 *v_intr_level_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* read active level*/
        case BMG160_INTR1:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT1_LEVEL__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr_level_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                   BMG160_INTR_ENABLE1_IT1_LEVEL);
            break;
        case BMG160_INTR2:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT2_LEVEL__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr_level_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                   BMG160_INTR_ENABLE1_IT2_LEVEL);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  Active Level status in the register 0x16
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 2
 *
 *  @param  v_param_u8: The value of Active Level selection number
 *    v_param_u8| Active Level
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param  v_intr_level_u8: The  value of Active Level status value
 *   value    |  Active Level
 * -----------|-------------
 *    1       | Active HIGH
 *    0       | Active LOW
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_level(u8 v_param_u8,
        u8 v_intr_level_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* write active level*/
        case BMG160_INTR1:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT1_LEVEL__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ENABLE1_IT1_LEVEL, v_intr_level_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ENABLE1_IT1_LEVEL__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_INTR2:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ENABLE1_IT2_LEVEL__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ENABLE1_IT2_LEVEL, v_intr_level_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ENABLE1_IT2_LEVEL__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the high rate(int1_high) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 3
 *
 *
 *
 *  @param v_intr1_u8 : The value of interrupt1 high_rate enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr1_highrate(u8 *v_intr1_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read high_rate enable */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_intr1_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                          BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the high rate(int1_high) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 3
 *
 *
 *
 *  @param v_intr1_u8 : The value of interrupt1 high_rate enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr1_highrate(
    u8 v_intr1_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write high_rate enable */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE, v_intr1_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_MAP_ZERO_INTR1_HIGHRATE__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the any motion(int1_any) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 1
 *
 *
 *
 *  @param v_int1r_any_motion_u8 : The value of any motion interrupt1
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr1_any_motion(
    u8 *v_int1r_any_motion_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read any motion interrupt*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_int1r_any_motion_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the any motion(int1_any) interrupt1 enable bits of
 *  the sensor in the registers 0x17 bit 1
 *
 *
 *
 *  @param v_int1r_any_motion_u8 : The value of any motion interrupt1
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr1_any_motion(
    u8 v_int1r_any_motion_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write any motion interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION, v_int1r_any_motion_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_MAP_ZERO_INTR1_ANY_MOTION__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the data interrupt1 and interrupt2(int1_data and int2_data)
 *  in the register 0x18
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 7
 *
 *  @param  v_axis_u8: data interrupt selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      0       |   BMG160_INTR1_DATA
 *      1       |   BMG160_INTR2_DATA
 *
 *  @param  v_intr_data_u8: The value of data interrupt1 or interrupt2
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_data(u8 v_axis_u8,
        u8 *v_intr_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* read data interrupt */
        case BMG160_INTR1_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr_data_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                  BMG160_MAP_ONE_INTR1_DATA);
            break;
        case BMG160_INTR2_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr_data_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                  BMG160_MAP_ONE_INTR2_DATA);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the data interrupt1 and interrupt2(int1_data and int2_data)
 *  in the register 0x18
 *  @note INT1 -> bit 0
 *  @note INT2 -> bit 7
 *
 *  @param  v_axis_u8: data interrupt selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      0       |   BMG160_INTR1_DATA
 *      1       |   BMG160_INTR2_DATA
 *
 *  @param  v_intr_data_u8: The value of data interrupt1 or interrupt2
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_data(u8 v_axis_u8,
        u8 v_intr_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* write data interrupt*/
        case BMG160_INTR1_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR1_DATA, v_intr_data_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR1_DATA__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_INTR2_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR2_DATA, v_intr_data_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR2_DATA__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the fast offset(intr2_fast_offset) and auto offset(intr2_auto_offset)
 *  of interrupt2 in the register 0x18
 *  @note int2_fast_offset -> bit 6
  * @note int2_auto_offset -> bit 4
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr2_offset_u8: The value of fast/auto offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_offset(u8 v_axis_u8,
        u8 *v_intr2_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* read offset*/
        case BMG160_FAST_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_FAST_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr2_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_MAP_ONE_INTR2_FAST_OFFSET);
            break;
        case BMG160_AUTO_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_AUTO_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr2_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_MAP_ONE_INTR2_AUTO_OFFSET);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the fast offset(intr2_fast_offset) and auto offset(intr2_auto_offset)
 *  of interrupt2 in the register 0x18
 *  @note int2_fast_offset -> bit 6
  * @note int2_auto_offset -> bit 4
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr2_offset_u8: The value of fast/auto offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr2_offset(u8 v_axis_u8,
        u8 v_intr2_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* write offset */
        case BMG160_FAST_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_FAST_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR2_FAST_OFFSET, v_intr2_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR2_FAST_OFFSET__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_AUTO_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_AUTO_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR2_AUTO_OFFSET, v_intr2_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR2_AUTO_OFFSET__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the fast offset(int1_fast_offset) and auto offset(int1_auto_offset)
 *  of interrupt1 in the register 0x18
 *  @note int1_fast_offset -> bit 1
 *  @note int1_auto_offset -> bit 3
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr1_offset_u8: The value of fast/auto offset
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr_offset(u8 v_axis_u8,
        u8 *v_intr1_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* read offset*/
        case BMG160_FAST_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_FAST_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr1_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_MAP_ONE_INTR1_FAST_OFFSET);
            break;
        case BMG160_AUTO_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_AUTO_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_intr1_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_MAP_ONE_INTR1_AUTO_OFFSET);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the fast offset(int1_fast_offset) and auto offset(int1_auto_offset)
 *  of interrupt1 in the register 0x18
 *  @note int1_fast_offset -> bit 1
 *  @note int1_auto_offset -> bit 3
 *
 *  @param v_axis_u8: The value of fast/auto offset interrupts selection
 *    v_axis_u8 | Data interrupt
 *  ------------|--------------
 *      1       |   BMG160_FAST_OFFSET
 *      2       |   BMG160_AUTO_OFFSET
 *
 *  @param v_intr1_offset_u8: The value of fast/auto offset
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr1_offset(u8 v_axis_u8,
        u8 v_intr1_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* write offset */
        case BMG160_FAST_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_FAST_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR1_FAST_OFFSET, v_intr1_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR1_FAST_OFFSET__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_AUTO_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_AUTO_OFFSET__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR1_AUTO_OFFSET, v_intr1_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR1_AUTO_OFFSET__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the fifo(int2_fifo) interrupt2 enable bits of
 *  the sensor in the registers 0x18 bit 5
 *
 *
 *
 *  @param v_intr_fifo_u8 : The interrupt2 fifo value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_fifo(u8 *v_intr_fifo_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MAP_ONE_INTR2_FIFO__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_intr_fifo_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                              BMG160_MAP_ONE_INTR2_FIFO);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the fifo(int1_fifo) interrupt1 enable bits of
 *  the sensor in the registers 0x18 bit 5
 *
 *
 *
 *  @param v_intr_fifo_u8 : The interrupt1 fifo value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr1_fifo(u8 *v_intr_fifo_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MAP_ONE_INTR1_FIFO__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_intr_fifo_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                              BMG160_MAP_ONE_INTR1_FIFO);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the value of
 *  the fifo interrupt1 and interrupt2(int1_fifo and int2_fifo)
 *  in the register 0x18
 *  @note int1_fifo -> bit 2
 *  @note int2_fifo -> bit 5
 *
 *  @param v_axis_u8: The value of fifo interrupts selection
 *    v_axis_u8 | fifo interrupt
 *  ------------|--------------
 *      0       |   BMG160_INTR1
 *      1       |   BMG160_INTR2
 *
 *  @param v_intr_fifo_u8: the value of int1_fifo/int2_fifo enable/disable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr_fifo(u8 v_axis_u8,
        u8 v_intr_fifo_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* write fifo interrupt */
        case BMG160_INTR1:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR1_FIFO__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR1_FIFO, v_intr_fifo_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR1_FIFO__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_INTR2:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MAP_ONE_INTR2_FIFO__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MAP_ONE_INTR2_FIFO, v_intr_fifo_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MAP_ONE_INTR2_FIFO__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the high rate(int2_high_rate) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 3
 *
 *
 *
 *  @param v_intr2_highrate_u8 : The interrupt2 high_rate value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_highrate(
    u8 *v_intr2_highrate_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read high rate interrupt*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_intr2_highrate_u8 = BMG160_GET_BITSLICE(v_data_u8,
                               BMG160_INTR_MAP_TWO_INTR2_HIGHRATE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the high rate(int2_high_rate) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 3
 *
 *
 *
 *  @param v_intr2_highrate_u8 : The interrupt2 high_rate value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr2_highrate(
    u8 v_intr2_highrate_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write high rate interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(
                     p_bmg160->dev_addr,
                     BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__REG,
                     &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_MAP_TWO_INTR2_HIGHRATE, v_intr2_highrate_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_MAP_TWO_INTR2_HIGHRATE__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the any motion(int2_any_motion) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 1
 *
 *
 *
 *  @param v_intr2_any_motion_u8 : The value of interrupt2 any_motion
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_intr2_any_motion(
    u8 *v_intr2_any_motion_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read any motion interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_intr2_any_motion_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the any motion(int2_any_motion) interrupt2 enable bits of
 *  the sensor in the registers 0x19 bit 1
 *
 *
 *
 *  @param v_intr2_any_motion_u8 : The value of interrupt2 any_motion
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_intr2_any_motion(
    u8 v_intr2_any_motion_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write any motion interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION, v_intr2_any_motion_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_MAP_TWO_INTR2_ANY_MOTION__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the slow offset and fast offset unfilt data in the register 0x1A and 1B
 *  @note slow_offset_unfilt -> 0x1A bit 5
 *  @note fast_offset_unfilt -> 0x1B bit 7
 *
 *  @param  v_param_u8: The value of fast/slow offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      0       |   BMG160_SLOW_OFFSET
 *      1       |   BMG160_FAST_OFFSET
 *
 *  @param v_offset_unfilt_u8: The value of fast/slow offset unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_unfilt(u8 v_param_u8,
        u8 *v_offset_unfilt_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* read offset unfilt data */
        case BMG160_SLOW_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_unfilt_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                  BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT);
            break;
        case BMG160_FAST_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_unfilt_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                  BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the slow offset and fast offset unfilt data in the register 0x1A and 1B
 *  @note slow_offset_unfilt -> 0x1A bit 5
 *  @note fast_offset_unfilt -> 0x1B bit 7
 *
 *  @param  v_param_u8: The value of fast/slow offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      0       |   BMG160_SLOW_OFFSET
 *      1       |   BMG160_FAST_OFFSET
 *
 *  @param v_offset_unfilt_u8: The value of fast/slow offset unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_unfilt(u8 v_param_u8,
        u8 v_offset_unfilt_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* write offset unfilt data */
        case BMG160_SLOW_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT,
                                            v_offset_unfilt_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ZERO_ADDR_SLOW_OFFSET_UNFILT__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_FAST_OFFSET:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT,
                                            v_offset_unfilt_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ONE_ADDR_FAST_OFFSET_UNFILT__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the any motion  and high rate unfilt data in the register 0x1A
 *  @note any_unfilt_data -> bit 1
 *  @note high_unfilt_data -> bit 3
 *
 *  @param  v_param_u8: The value of any/high offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      1       |   BMG160_HIGHRATE_UNFILT_DATA
 *      3       |   BMG160_ANY_MOTION_UNFILT_DATA
 *
 *  @param v_unfilt_data_u8: The value of any/high unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_unfilt_data(u8 v_param_u8,
        u8 *v_unfilt_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* read unfilt data */
        case BMG160_HIGHRATE_UNFILT_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_unfilt_data_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                    BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA);
            break;
        case BMG160_ANY_MOTION_UNFILT_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_unfilt_data_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                    BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the any motion  and high rate unfilt data in the register 0x1A
 *  @note any_unfilt_data -> bit 1
 *  @note high_unfilt_data -> bit 3
 *
 *  @param  v_param_u8: The value of any/high offset unfilt data selection
 *   v_param_u8 | offset selection
 *  ------------|--------------
 *      1       |   BMG160_HIGHRATE_UNFILT_DATA
 *      3       |   BMG160_ANY_MOTION_UNFILT_DATA
 *
 *  @param v_unfilt_data_u8: The value of any/high unfilt data
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_unfilt_data(u8 v_param_u8,
        u8 v_unfilt_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* write unfilt data */
        case BMG160_HIGHRATE_UNFILT_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA,
                                            v_unfilt_data_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ZERO_ADDR_HIGHRATE_UNFILT_DATA__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_ANY_MOTION_UNFILT_DATA:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA,
                                            v_unfilt_data_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_ZERO_ADDR_ANY_MOTION_UNFILT_DATA__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get Any motion Threshold
 *  in the register 0x1B bit from 0 to 6
 *
 *
 *
 *  @param v_any_motion_thres_u8 : The value of any_motion Threshold
 *
 *  @note Any motion threshold can be calculate using
 *  @note ((1+ v_any_motion_thres_u8)*16LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_motion_thres(
    u8 *v_any_motion_thres_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read any motion threshold */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_any_motion_thres_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES);
    }
    return comres;
}
/*!
 *  @brief This API is used to set Any motion Threshold
 *  in the register 0x1B bit from 0 to 6
 *
 *
 *
 *  @param v_any_motion_thres_u8 : The value of any_motion Threshold
 *
 *  @note Any motion threshold can be calculate using
 *  @note ((1+ v_any_motion_thres_u8)*16LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_motion_thres(
    u8 v_any_motion_thres_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write any motion threshold*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES, v_any_motion_thres_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_ONE_ADDR_ANY_MOTION_THRES__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the awake Duration
 *  in the register 0x1C bit 6 and 7
 *
 *
 *
 *  @param v_awake_durn_u8 : The value of awake Duration
 *  value   |  Duration
 * ---------|-----------
 *   0x00   | 8 samples
 *   0x01   | 16 samples
 *   0x02   | 32 samples
 *   0x03   | 64 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_awake_durn(u8 *v_awake_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read awake duration*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_TWO_ADDR_AWAKE_DURN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_awake_durn_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_INTR_TWO_ADDR_AWAKE_DURN);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the awake Duration
 *  in the register 0x1C bit 6 and 7
 *
 *
 *
 *  @param v_awake_durn_u8 : The value of awake Duration
 *  value   |  Duration
 * ---------|-----------
 *   0x00   | 8 samples
 *   0x01   | 16 samples
 *   0x02   | 32 samples
 *   0x03   | 64 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_awake_durn(u8 v_awake_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write awake duration*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_TWO_ADDR_AWAKE_DURN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_TWO_ADDR_AWAKE_DURN, v_awake_durn_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_INTR_TWO_ADDR_AWAKE_DURN__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the any motion Duration samples in the register 0x1C bit 4 and 5
 *
 *
 *
 *  @param v_durn_sample_u8 : The value of any motion duration samples
 *  value   |  Samples
 * ---------|-----------
 *   0x00   | 4 samples
 *   0x01   | 8 samples
 *   0x02   | 12 samples
 *   0x03   | 16 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_motion_durn_sample(
    u8 *v_durn_sample_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read any motion awake samples*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_durn_sample_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the any motion Duration samples in the register 0x1C bit 4 and 5
 *
 *
 *
 *  @param v_durn_sample_u8 : The value of any motion duration samples
 *  value   |  Samples
 * ---------|-----------
 *   0x00   | 4 samples
 *   0x01   | 8 samples
 *   0x02   | 12 samples
 *   0x03   | 16 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_motion_durn_sample(
    u8 v_durn_sample_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write awake duration samples*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE,
                                        v_durn_sample_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(
                      p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_DURN_SAMPLE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of
 *  Any motion interrupt axis(X,Y,Z) enable channel
 *  @note BMG160_X_AXIS -> bit 0
 *  @note BMG160_Y_AXIS -> bit 1
 *  @note BMG160_Z_AXIS -> bit 2
 *
 *  @param v_channel_u8 : The value of Any Enable channel number
 *   v_channel_u8 | axis
 *  --------------|--------------
 *      0         | BMG160_X_AXIS
 *      1         | BMG160_Y_AXIS
 *      2         | BMG160_Z_AXIS
 *
 *  @param v_data_u8: The value of Any motion axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_motion_enable_axis(u8 v_channel_u8,
        u8 *v_any_motion_axis_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data1_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read any motion axis enable*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__REG,
                      &v_data1_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_any_motion_axis_u8 = BMG160_GET_BITSLICE(v_data1_u8,
                                    BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__REG,
                      &v_data1_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_any_motion_axis_u8 = BMG160_GET_BITSLICE(v_data1_u8,
                                    BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__REG,
                      &v_data1_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_any_motion_axis_u8 = BMG160_GET_BITSLICE(v_data1_u8,
                                    BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of
 *  Any motion interrupt axis(X,Y,Z) enable channel
 *  @note BMG160_X_AXIS -> bit 0
 *  @note BMG160_Y_AXIS -> bit 1
 *  @note BMG160_Z_AXIS -> bit 2
 *
 *  @param v_channel_u8 : The value of Any Enable channel number
 *   v_channel_u8 | axis
 *  --------------|--------------
 *      0         | BMG160_X_AXIS
 *      1         | BMG160_Y_AXIS
 *      2         | BMG160_Z_AXIS
 *
 *  @param v_any_motion_axis_u8: The value of Any motion axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_motion_enable_axis(u8 v_channel_u8,
        u8 v_any_motion_axis_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write any motion axis enable*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X,
                                            v_any_motion_axis_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_X__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y,
                                            v_any_motion_axis_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Y__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z,
                                            v_any_motion_axis_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_TWO_ADDR_ANY_MOTION_ENABLE_Z__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the status of fifo water mark in the register 0x1E bit 7
 *
 *
 *
 *  @param v_fifo_wm_enable_u8 : The value of fifo water mark enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_wm_enable(
    u8 *v_fifo_wm_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo water mark enable */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_INTR_4_FIFO_WM_ENABLE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_wm_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                               BMG160_INTR_4_FIFO_WM_ENABLE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the status of fifo water mark in the register 0x1E bit 7
 *
 *
 *
 *  @param v_fifo_wm_enable_u8 : The value of fifo water mark enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_wm_enable(
    u8 v_fifo_wm_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write fifo water mark enable*/
        if (v_fifo_wm_enable_u8 < BMG160_BIT_LENGTH_FIFO_WM)
        {
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_INTR_4_FIFO_WM_ENABLE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_INTR_4_FIFO_WM_ENABLE, v_fifo_wm_enable_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_INTR_4_FIFO_WM_ENABLE__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the Interrupt Reset
 *  in the register 0x21 bit 7
 *
 *
 *
 *  @param v_rst_int_u8: the value of reset interrupt
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_rst_intr(u8 v_rst_int_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write reset interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RST_LATCH_ADDR_RST_INTR__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_RST_LATCH_ADDR_RST_INTR, v_rst_int_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_RST_LATCH_ADDR_RST_INTR__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the offset Reset
 *  in the register 0x21 bit 6
 *
 *
 *
 *  @param v_offset_rst_u8: the value of reset offset
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_rst(
    u8 v_offset_rst_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write reset offset */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RST_LATCH_ADDR_OFFSET_RST__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_RST_LATCH_ADDR_OFFSET_RST, v_offset_rst_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_RST_LATCH_ADDR_OFFSET_RST__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the Latch Status
 *  in the register 0x21 bit 4
 *
 *
 *
 *  @param v_latch_stat_u8 : The value of latch status
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_latch_stat(
    u8 *v_latch_stat_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the latch status*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RST_LATCH_ADDR_LATCH_STAT__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_latch_stat_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_RST_LATCH_ADDR_LATCH_STAT);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the Latch Status
 *  in the register 0x21 bit 4
 *
 *
 *
 *  @param v_latch_stat_u8 : The value of latch status
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_latch_stat(
    u8 v_latch_stat_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write the latch status */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RST_LATCH_ADDR_LATCH_STAT__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_RST_LATCH_ADDR_LATCH_STAT, v_latch_stat_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_RST_LATCH_ADDR_LATCH_STAT__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the Latch interrupt
 *  in the register 0x21 bit from 0 to 3
 *
 *
 *
 *  @param v_latch_intr_u8 : The value of latch interrupt
 *      Latch Interrupt        |  Value
 * ----------------------------|-----------------
 * BMG160_NON_LATCH            | 0x00
 * BMG160_LATCH_250_MS         | 0x01
 * BMG160_LATCH_500_MS         | 0x02
 * BMG160_LATCH_1_SEC          | 0x03
 * BMG160_LATCH_2_SEC          | 0x04
 * BMG160_LATCH_4_SEC          | 0x05
 * BMG160_LATCH_8_SEC          | 0x06
 * BMG160_LATCH_LATCHED        | 0x07
 * BMG160_LATCH_NON_LATCHED    | 0x08
 * BMG160_LATCH_250_MICRO_SEC  | 0x09
 * BMG160_LATCH_500_MICRO_SEC  | 0x0A
 * BMG160_LATCH_1_MILLI_SEC    | 0x0B
 * BMG160_LATCH_12.5_MILLI_SEC | 0x0C
 * BMG160_LATCH_25_MILLI_SEC   | 0x0D
 * BMG160_LATCH_50_MILLI_SEC   | 0x0E
 * BMG160_LATCH_LATCHED        | 0x0F
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_latch_intr(u8 *v_latch_intr_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read latch interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RST_LATCH_ADDR_LATCH_INTR__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_latch_intr_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_RST_LATCH_ADDR_LATCH_INTR);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the Latch interrupt
 *  in the register 0x21 bit from 0 to 3
 *
 *
 *
 *  @param v_latch_intr_u8 : The value of latch interrupt
 *      Latch Interrupt        |  Value
 * ----------------------------|-----------------
 * BMG160_NON_LATCH            | 0x00
 * BMG160_LATCH_250_MS         | 0x01
 * BMG160_LATCH_500_MS         | 0x02
 * BMG160_LATCH_1_SEC          | 0x03
 * BMG160_LATCH_2_SEC          | 0x04
 * BMG160_LATCH_4_SEC          | 0x05
 * BMG160_LATCH_8_SEC          | 0x06
 * BMG160_LATCH_LATCHED        | 0x07
 * BMG160_LATCH_NON_LATCHED    | 0x08
 * BMG160_LATCH_250_MICRO_SEC  | 0x09
 * BMG160_LATCH_500_MICRO_SEC  | 0x0A
 * BMG160_LATCH_1_MILLI_SEC    | 0x0B
 * BMG160_LATCH_12.5_MILLI_SEC | 0x0C
 * BMG160_LATCH_25_MILLI_SEC   | 0x0D
 * BMG160_LATCH_50_MILLI_SEC   | 0x0E
 * BMG160_LATCH_LATCHED        | 0x0F
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_latch_intr(u8 v_latch_intr_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write latch interrupt */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_RST_LATCH_ADDR_LATCH_INTR__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_RST_LATCH_ADDR_LATCH_INTR, v_latch_intr_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_RST_LATCH_ADDR_LATCH_INTR__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of High
 *  Hysteresis of X,Y,Z axis in the registers 0x22,0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 6 and 7
 *  @note Y_AXIS - 0x24 bit 6 and 7
 *  @note Z_AXIS - 0x26 bit 6 and 7
 *
 *  @param v_channel_u8: The value of high Hysteresis channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_hyst_u8: The value of high Hysteresis
 *
 *  @note High hysteresis can be calculated by
 *  @note High_hyst = ((255+256 *v_highrate_hyst_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_hyst(u8 v_channel_u8,
        u8 *v_highrate_hyst_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read high hysteresis*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_HYST_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_hyst_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                  BMG160_HIGHRATE_HYST_X);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_HYST_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_hyst_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                  BMG160_HIGHRATE_HYST_Y);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_HYST_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_hyst_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                  BMG160_HIGHRATE_HYST_Z);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of High
 *  Hysteresis of X,Y,Z axis in the registers 0x22,0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 6 and 7
 *  @note Y_AXIS - 0x24 bit 6 and 7
 *  @note Z_AXIS - 0x26 bit 6 and 7
 *
 *  @param v_channel_u8: The value of high Hysteresis channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_hyst_u8: The value of high Hysteresis
 *
 *  @note High hysteresis can be calculated by
 *  @note High_hyst = ((255+256 *v_highrate_hyst_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_hyst(u8 v_channel_u8,
        u8 v_highrate_hyst_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write high hysteresis*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_HYST_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_HYST_X, v_highrate_hyst_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_HYST_X__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_HYST_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_HYST_Y, v_highrate_hyst_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_HYST_Y__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_HYST_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_HYST_Z, v_highrate_hyst_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_HYST_Z__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the value of High rate
 *  Threshold of X,Y,Z axis in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit from 1 to 5
 *  @note Y_AXIS - 0x24 bit from 1 to 5
 *  @note Z_AXIS - 0x26 bit from 1 to 5
 *
 *  @param  v_channel_u8 : The value of high threshold channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_thres_u8: the high threshold value
 *
 *  @note High Threshold can be calculated by
 *  @note High_thres = ((255+256 *v_highrate_thres_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_thres(u8 v_channel_u8,
        u8 *v_highrate_thres_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read high rate threshold*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_thres_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                   BMG160_HIGHRATE_THRES_X);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_thres_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                   BMG160_HIGHRATE_THRES_Y);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_thres_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                   BMG160_HIGHRATE_THRES_Z);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the value of High rate
 *  Threshold of X,Y,Z axis in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit from 1 to 5
 *  @note Y_AXIS - 0x24 bit from 1 to 5
 *  @note Z_AXIS - 0x26 bit from 1 to 5
 *
 *  @param  v_channel_u8 : The value of high threshold channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_thres_u8: the high threshold value
 *
 *  @note High Threshold can be calculated by
 *  @note High_thres = ((255+256 *v_highrate_thres_u8) * 4LSB)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_thres(u8 v_channel_u8,
        u8 v_highrate_thres_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write high rate threshold*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_THRES_X, v_highrate_thres_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_THRES_X__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_THRES_Y, v_highrate_thres_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_THRES_Y__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_THRES_Z, v_highrate_thres_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_THRES_Z__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 * @brief This API is used to get the status of High Enable
 * Channel X,Y,Z in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 0
 *  @note Y_AXIS - 0x24 bit 0
 *  @note Z_AXIS - 0x26 bit 0
 *
 *  @param v_channel_u8 : The value of high enable channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_enable_u8: The value of high axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_enable_axis(u8 v_channel_u8,
        u8 *v_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read high rate axis enable */
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_ENABLE_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_HIGHRATE_ENABLE_X);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_ENABLE_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_HIGHRATE_ENABLE_Y);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_ENABLE_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_enable_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_HIGHRATE_ENABLE_Z);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 * @brief This API is used to set the status of High Enable
 * Channel X,Y,Z in the registers 0x22, 0x24 and 0x26
 *  @note X_AXIS - 0x22 bit 0
 *  @note Y_AXIS - 0x24 bit 0
 *  @note Z_AXIS - 0x26 bit 0
 *
 *  @param v_channel_u8 : The value of high enable channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_enable_u8: The value of high axis enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_enable_axis(u8 v_channel_u8,
        u8 v_enable_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write high rate axis enable */
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_ENABLE_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_ENABLE_X, v_enable_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_ENABLE_X__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_ENABLE_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_ENABLE_Y, v_enable_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_ENABLE_Y__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_ENABLE_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_HIGHRATE_ENABLE_Z, v_enable_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_HIGHRATE_ENABLE_Z__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 * @brief This API is used to get the status
 * of High duration of X,Y,Z axis in
 * the registers 0x23, 0x25 and 0x27
 *  @note X_AXIS - 0x23 bit form 0 to 7
 *  @note Y_AXIS - 0x25 bit form 0 to 7
 *  @note Z_AXIS - 0x27 bit form 0 to 7
 *
 *
 *
 *  @param  v_channel_u8: The value of High Duration channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_durn_axis_u8: The value of high duration
 *
 *  @note High rate duration can be calculated by using the formula
 *  @note High_durn = ((1+v_highrate_durn_axis_u8)*2.5ms)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_highrate_durn_axis(u8 v_channel_u8,
        u8 *v_highrate_durn_axis_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read high rate duration*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_DURN_X_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_durn_axis_u8 = v_data_u8;
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Y_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_durn_axis_u8 = v_data_u8;
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Z_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_highrate_durn_axis_u8 = v_data_u8;
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 * @brief This API is used to set the value
 * of High duration of X,Y,Z axis in
 * the registers 0x23, 0x25 and 0x27
 *  @note X_AXIS - 0x23 bit form 0 to 7
 *  @note Y_AXIS - 0x25 bit form 0 to 7
 *  @note Z_AXIS - 0x27 bit form 0 to 7
 *
 *
 *
 *  @param  v_channel_u8: The value of High Duration channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_highrate_durn_axis_u8: The value of high duration
 *
 *  @note High rate duration can be calculated by using the formula
 *  @note High_durn = ((1+v_highrate_durn_axis_u8)*2.5ms)
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_highrate_durn_axis(u8 v_channel_u8,
        u8 v_highrate_durn_axis_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write high rate duration*/
        case BMG160_X_AXIS:
            v_data_u8 = v_highrate_durn_axis_u8;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_X_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            v_data_u8 = v_highrate_durn_axis_u8;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Y_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            v_data_u8 = v_highrate_durn_axis_u8;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_HIGHRATE_THRES_Z_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get Slow Offset Threshold
 *  status in the register 0x31 bit 6 and 7
 *
 *
 *
 *  @param v_offset_thres_u8 : The value of slow offset Threshold
 *  value    |   threshold
 * ----------|-------------
 *    0x00   | 0.1 degree/sec
 *    0x01   | 0.2 degree/sec
 *    0x02   | 0.5 degree/sec
 *    0x03   | 1 degree/sec
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_thres(
    u8 *v_offset_thres_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read slow offset threshold*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_SLOW_OFFSET_THRES__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_offset_thres_u8 = BMG160_GET_BITSLICE(v_data_u8,
                             BMG160_SLOW_OFFSET_THRES);
    }
    return comres;
}
/*!
 *  @brief This API is used to set Slow Offset Threshold
 *  status in the register 0x31 bit 6 and 7
 *
 *
 *
 *  @param v_offset_thres_u8 : The value of slow offset Threshold
 *  value    |   threshold
 * ----------|-------------
 *    0x00   | 0.1 degree/sec
 *    0x01   | 0.2 degree/sec
 *    0x02   | 0.5 degree/sec
 *    0x03   | 1 degree/sec
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_thres(u8 v_offset_thres_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write slow offset threshold*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_SLOW_OFFSET_THRES__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_SLOW_OFFSET_THRES, v_offset_thres_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_SLOW_OFFSET_THRES__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get Slow Offset duration
 *  status in the register 0x31 bit 4,5 and 6
 *
 *
 *
 *  @param v_offset_durn_u8 : The value of Slow Offset duration
 *   value    |  Duration
 * -----------|-----------
 *    0x00    | 40ms
 *    0x01    | 80ms
 *    0x02    | 160ms
 *    0x03    | 320ms
 *    0x04    | 640ms
 *    0x05    | 1280ms
 *    0x06    | unused
 *    0x07    | unused
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_durn(
    u8 *v_offset_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read slow offset duration*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_SLOW_OFFSET_DURN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_offset_durn_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_SLOW_OFFSET_DURN);
    }
    return comres;
}
/*!
 *  @brief This API is used to set Slow Offset duration
 *  status in the register 0x31 bit 4,5 and 6
 *
 *
 *
 *  @param v_offset_durn_u8 : The value of Slow Offset duration
 *   value    |  Duration
 * -----------|-----------
 *    0x00    | 40ms
 *    0x01    | 80ms
 *    0x02    | 160ms
 *    0x03    | 320ms
 *    0x04    | 640ms
 *    0x05    | 1280ms
 *    0x06    | unused
 *    0x07    | unused
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_durn(
    u8 v_offset_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write slow offset duration*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_SLOW_OFFSET_DURN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_SLOW_OFFSET_DURN, v_offset_durn_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_SLOW_OFFSET_DURN__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get Slow Offset Enable channel
 *  X,Y,Z in the register 0x31
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *  @param v_channel_u8: The value of slow offset channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_slow_offset_u8: The slow offset value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_enable_axis(
    u8 v_channel_u8, u8 *v_slow_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read slow offset axis enable */
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SLOW_OFFSET_ENABLE_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_slow_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                    BMG160_SLOW_OFFSET_ENABLE_X);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SLOW_OFFSET_ENABLE_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_slow_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                    BMG160_SLOW_OFFSET_ENABLE_Y);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SLOW_OFFSET_ENABLE_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_slow_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                    BMG160_SLOW_OFFSET_ENABLE_Z);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set Slow Offset Enable channel
 *  X,Y,Z in the register 0x31
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *  @param v_channel_u8: The value of slow offset channel number
 *  v_channel_u8  |    value
 *  --------------|--------------
 *  BMG160_X_AXIS |   0
 *  BMG160_Y_AXIS |   1
 *  BMG160_Z_AXIS |   2
 *
 *  @param v_slow_offset_u8: The slow offset value
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_enable_axis(
    u8 v_channel_u8, u8 v_slow_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write slow offset axis enable */
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SLOW_OFFSET_ENABLE_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_SLOW_OFFSET_ENABLE_X, v_slow_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_SLOW_OFFSET_ENABLE_X__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SLOW_OFFSET_ENABLE_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_SLOW_OFFSET_ENABLE_Y, v_slow_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_SLOW_OFFSET_ENABLE_Y__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_SLOW_OFFSET_ENABLE_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_SLOW_OFFSET_ENABLE_Z,
                                            v_slow_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_SLOW_OFFSET_ENABLE_Z__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  Fast Offset WordLength and Auto Offset WordLength in the register 0x32
 *  @note fast_offset_wordlength -> bit 4 and 5
 *  @note auto_offset_wordlength -> bit 6 and 7
 *
 *
 *  @param v_channel_u8: The value of WordLengthchannel number
 *  v_channel_u8          |    value
 *  ----------------------|--------------
 *  BMG160_AUTO_OFFSET_WL |   0
 *  BMG160_FAST_OFFSET_WL |   1
 *
 *  @param  v_offset_word_length_u8: The value of offset word length
 *   value    |  word length
 *  ----------|--------------
 *    0x00    | 32 samples
 *    0x01    | 64 samples
 *    0x02    | 128 samples
 *    0x03    | 256 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_word_length(u8 v_channel_u8,
        u8 *v_offset_word_length_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        case BMG160_AUTO_OFFSET_WORD_LENGHTH:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_AUTO_OFFSET_WORD_LENGHTH__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_word_length_u8 =
                BMG160_GET_BITSLICE(v_data_u8,
                                    BMG160_AUTO_OFFSET_WORD_LENGHTH);
            break;
        case BMG160_FAST_OFFSET_WORD_LENGHTH:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FAST_OFFSET_WORD_LENGHTH__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_word_length_u8 =
                BMG160_GET_BITSLICE(v_data_u8,
                                    BMG160_FAST_OFFSET_WORD_LENGHTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  Fast Offset WordLength and Auto Offset WordLength in the register 0x32
 *  @note fast_offset_wordlength -> bit 4 and 5
 *  @note auto_offset_wordlength -> bit 6 and 7
 *
 *
 *  @param v_channel_u8: The value of WordLengthchannel number
 *  v_channel_u8          |    value
 *  ----------------------|--------------
 *  BMG160_AUTO_OFFSET_WL |   0
 *  BMG160_FAST_OFFSET_WL |   1
 *
 *  @param  v_offset_word_length_u8: The value of offset word length
 *   value    |  word length
 *  ----------|--------------
 *    0x00    | 32 samples
 *    0x01    | 64 samples
 *    0x02    | 128 samples
 *    0x03    | 256 samples
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_word_length(
    u8 v_channel_u8, u8 v_offset_word_length_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        case BMG160_AUTO_OFFSET_WORD_LENGHTH:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_AUTO_OFFSET_WORD_LENGHTH__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_AUTO_OFFSET_WORD_LENGHTH,
                                            v_offset_word_length_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_AUTO_OFFSET_WORD_LENGHTH__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_FAST_OFFSET_WORD_LENGHTH:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FAST_OFFSET_WORD_LENGHTH__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FAST_OFFSET_WORD_LENGHTH,
                                            v_offset_word_length_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FAST_OFFSET_WORD_LENGHTH__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to enable fast offset
 *  in the register 0x32 bit 3 it is a write only register
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_enable_fast_offset(void)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FAST_OFFSET_ENABLE__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_FAST_OFFSET_ENABLE,
                                        BMG160_GEN_READ_WRITE_DATA_LENGTH);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_FAST_OFFSET_ENABLE__REG, &v_data_u8,
                  BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API read the Fast offset enable
 *  v_axis_u8(X,Y and Z) in the register 0x32
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *
 *  @param v_fast_offset_u8: The value of fast offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fast_offset_enable_axis(
    u8 *v_fast_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fast offset enable axis*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_FAST_OFFSET_ENABLE_XYZ__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fast_offset_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_FAST_OFFSET_ENABLE_XYZ);
    }
    return comres;
}
/*!
 *  @brief This API set the Fast offset enable
 *  v_axis_u8(X,Y and Z) in the register 0x32
 *  @note X_AXIS -> bit 0
 *  @note Y_AXIS -> bit 1
 *  @note Z_AXIS -> bit 2
 *
 *
 *  @param v_channel_u8: The value of fast offset channel select
 *  v_channel_u8    |    value
 *  ----------------|--------------
 *  BMG160_X_AXIS   |   0
 *  BMG160_Y_AXIS   |   1
 *  BMG160_Z_AXIS   |   2
 *
 *  @param v_fast_offset_u8: The value of fast offset enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fast_offset_enable_axis(
    u8 v_channel_u8, u8 v_fast_offset_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write fast offset enable axis*/
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FAST_OFFSET_ENABLE_X__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FAST_OFFSET_ENABLE_X, v_fast_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FAST_OFFSET_ENABLE_X__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FAST_OFFSET_ENABLE_Y__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FAST_OFFSET_ENABLE_Y, v_fast_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FAST_OFFSET_ENABLE_Y__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FAST_OFFSET_ENABLE_Z__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FAST_OFFSET_ENABLE_Z, v_fast_offset_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FAST_OFFSET_ENABLE_Z__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of nvm program
 *  remain in the register 0x33 bit from 4 to 7
 *
 *
 *  @param v_nvm_remain_u8: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  Do not trigger
 *    0       |  Trigger
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_remain(u8 *v_nvm_remain_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read NVM program*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_nvm_remain_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                               BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of nvm program
 *  remain in the register 0x33 bit from 4 to 7
 *
 *
 *  @param v_nvm_load_u8: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  Do not trigger
 *    0       |  Trigger
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_load(u8 v_nvm_load_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write NVM program*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD, v_nvm_load_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of nvm
 *  program in the register 0x33 bit 2
 *
 *  @param v_nvm_rdy_u8: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  NVM write is in progress
 *    0       |  NVM is ready to accept a new write
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_rdy(u8 *v_nvm_rdy_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_nvm_rdy_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                            BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of nvm
 *  ready in the register 0x33 bit 1
 *
 *  @param nvm_prog_trig: The value of nvm program
 *   value    |  Description
 * -----------|---------------
 *    1       |  program seq in progress
 *    0       |  program seq finished
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_prog_trig(u8 nvm_prog_trig)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG, nvm_prog_trig);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the status of nvm program mode in the register 0x33 bit 0
 *
 *
 *  @param nvm_prog_mode: The value of nvm program mode
 *   value    |  Description
 * -----------|---------------
 *    1       |  Unlock
 *    0       |  Lock nvm write
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_prog_mode(u8 *nvm_prog_mode)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *nvm_prog_mode = BMG160_GET_BITSLICE(v_data_u8,
                                             BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the status of nvm program mode in the register 0x33 bit 0
 *
 *
 *  @param nvm_prog_mode: The value of nvm program mode
 *   value    |  Description
 * -----------|---------------
 *    1       |  Unlock
 *    0       |  Lock nvm write
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_prog_mode(u8 nvm_prog_mode)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE, nvm_prog_mode);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief This API is used to get
 *  the status of i2c wdt select and enable in the register 0x34
 *  @note i2c_wdt_select -> bit 1
 *  @note i2c_wdt_enable -> bit 2
 *
 *  @param v_channel_u8: The value of i2c wdt channel number
 *  v_channel_u8            |    value
 *  ------------------------|--------------
 *  BMG160_I2C_WDT_ENABLE   |   1
 *  BMG160_I2C_WDT_SELECT   |   0
 *
 *  @param v_i2c_wdt_u8: The value of I2C enable and WDT select
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_i2c_wdt(u8 v_channel_u8,
        u8 *v_i2c_wdt_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* read i2c wdt*/
        case BMG160_I2C_WDT_ENABLE:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_i2c_wdt_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE);
            break;
        case BMG160_I2C_WDT_SELECT:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_i2c_wdt_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                                BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set
 *  the status of i2c wdt select and enable in the register 0x34
 *  @note i2c_wdt_select -> bit 1
 *  @note i2c_wdt_enable -> bit 2
 *
 *  @param v_channel_u8: The value of i2c wdt channel number
 *  v_channel_u8            |    value
 *  ------------------------|--------------
 *  BMG160_I2C_WDT_ENABLE   |   1
 *  BMG160_I2C_WDT_SELECT   |   0
 *
 *  @param v_i2c_wdt_u8: The value of I2C enable and WDT select
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_i2c_wdt(u8 v_channel_u8,
        u8 v_i2c_wdt_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_channel_u8)
        {
        /* write i2c wdt*/
        case BMG160_I2C_WDT_ENABLE:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE, v_i2c_wdt_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_ENABLE__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_I2C_WDT_SELECT:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT, v_i2c_wdt_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SELECT__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief  This API is used to get the status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  v_spi3_u8 : The value of spi3 enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_spi3(u8 *v_spi3_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(
                     p_bmg160->dev_addr,
                     BMG160_BGW_SPI3_WDT_ADDR_SPI3__REG,
                     &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_spi3_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                         BMG160_BGW_SPI3_WDT_ADDR_SPI3);
    }
    return comres;
}
/*!
 *  @brief  This API is used to set the status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  v_spi3_u8 : The value of spi3 enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_spi3(u8 v_spi3_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_BGW_SPI3_WDT_ADDR_SPI3__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                        BMG160_BGW_SPI3_WDT_ADDR_SPI3, v_spi3_u8);
        comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
                  BMG160_BGW_SPI3_WDT_ADDR_SPI3__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
    }
    return comres;
}
/*!
 *  @brief  This API is used to get the status of FIFO tag
 *  in the register 0x3D bit 7
 *
 *
 *
 *  @param  v_fifo_tag_u8 : The value of fifo tag enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_tag(u8 *v_fifo_tag_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo tag*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_CGF1_ADDR_TAG__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_tag_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                             BMG160_FIFO_CGF1_ADDR_TAG);
    }
    return comres;
}
/*!
 *  @brief  This API is used to set the status of FIFO tag
 *  in the register 0x3D bit 7
 *
 *
 *
 *  @param  v_fifo_tag_u8 : The value of fifo tag enable
 *   value    |  Description
 * -----------|---------------
 *    1       |  BMG160_ENABLE
 *    0       |  BMG160_DISABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_tag(u8 v_fifo_tag_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_fifo_tag_u8 < BMG160_BIT_LENGTH_FIFO_TAG)
        {
            /* write fifo tag */
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FIFO_CGF1_ADDR_TAG__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FIFO_CGF1_ADDR_TAG, v_fifo_tag_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FIFO_CGF1_ADDR_TAG__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get Water Mark Level
 *  in the register 0x3D bit from 0 to 6
 *
 *
 *
 *  @param v_fifo_wm_level_u8 : The value of fifo water mark level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_wm_level(
    u8 *v_fifo_wm_level_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_CGF1_ADDR_WML__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_wm_level_u8 = BMG160_GET_BITSLICE(v_data_u8,
                              BMG160_FIFO_CGF1_ADDR_WML);
    }
    return comres;
}
/*!
 *  @brief This API is used to set Water Mark Level
 *  in the register 0x3D bit from 0 to 6
 *
 *
 *
 *  @param v_fifo_wm_level_u8 : The value of fifo water mark level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_wm_level(
    u8 v_fifo_wm_level_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_fifo_wm_level_u8 < BMG160_FIFO_WM_LENGTH)
        {
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FIFO_CGF1_ADDR_WML__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FIFO_CGF1_ADDR_WML, v_fifo_wm_level_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FIFO_CGF1_ADDR_WML__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the value of offset
 *  X, Y and Z in the registers 0x36, 0x37, 0x38, 0x39 and 0x3A
 *  the offset is a 12bit value
 *  @note X_AXIS ->
 *      @note bit 0 and 1 is available in the register 0x3A bit 2 and 3
 *      @note bit 2 and 3 is available in the register 0x36 bit 6 and 7
 *      @note bit 4 to 11 is available in the register 0x37 bit 0 to 7
 *  @note Y_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 1
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 3,4 and 5
 *      @note bit 4 to 11 is available in the register 0x38 bit 0 to 7
 *  @note Z_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 0
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 0,1 and 3
 *      @note bit 4 to 11 is available in the register 0x39 bit 0 to 7
 *
 *  @param  v_axis_u8 : The value of offset axis selection
 *  v_axis_u8       |    value
 *  ----------------|--------------
 *  BMG160_X_AXIS   |   1
 *  BMG160_Y_AXIS   |   0
 *  BMG160_Z_AXIS   |   0
 *
 *  @param v_offset_s16: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset(u8 v_axis_u8,
        s16 *v_offset_s16)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data1_u8r = BMG160_INIT_VALUE;
    u8 v_data2_u8r = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* read offset */
        case BMG160_X_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP0_ADDR_OFFSET_X__REG,
                      &v_data1_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data1_u8r = BMG160_GET_BITSLICE(v_data1_u8r,
                                              BMG160_TRIM_GP0_ADDR_OFFSET_X);
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC1_ADDR_OFFSET_X__REG,
                      &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data2_u8r = BMG160_GET_BITSLICE(v_data2_u8r,
                                              BMG160_OFC1_ADDR_OFFSET_X);
            v_data2_u8r = ((v_data2_u8r <<
                            BMG160_SHIFT_BIT_POSITION_BY_02_BITS)
                           | v_data1_u8r);
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr, BMG160_OFC2_ADDR,
                      &v_data1_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_s16 = (s16)((((s16)
                                    ((s8)v_data1_u8r))
                                   << BMG160_SHIFT_BIT_POSITION_BY_04_BITS)
                                  | (v_data2_u8r));
            break;
        case BMG160_Y_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP0_ADDR_OFFSET_Y__REG,
                      &v_data1_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data1_u8r = BMG160_GET_BITSLICE(v_data1_u8r,
                                              BMG160_TRIM_GP0_ADDR_OFFSET_Y);
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC1_ADDR_OFFSET_Y__REG,
                      &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data2_u8r = BMG160_GET_BITSLICE(v_data2_u8r,
                                              BMG160_OFC1_ADDR_OFFSET_Y);
            v_data2_u8r = ((v_data2_u8r <<
                            BMG160_SHIFT_BIT_POSITION_BY_01_BIT)
                           | v_data1_u8r);
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC3_ADDR, &v_data1_u8r,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_s16 = (s16)((((s16)
                                    ((s8)v_data1_u8r))
                                   << BMG160_SHIFT_BIT_POSITION_BY_04_BITS)
                                  | (v_data2_u8r));
            break;
        case BMG160_Z_AXIS:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP0_ADDR_OFFSET_Z__REG,
                      &v_data1_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data1_u8r = BMG160_GET_BITSLICE(v_data1_u8r,
                                              BMG160_TRIM_GP0_ADDR_OFFSET_Z);
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC1_ADDR_OFFSET_Z__REG,
                      &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data2_u8r = BMG160_GET_BITSLICE(v_data2_u8r,
                                              BMG160_OFC1_ADDR_OFFSET_Z);
            v_data2_u8r = ((v_data2_u8r <<
                            BMG160_SHIFT_BIT_POSITION_BY_01_BIT)
                           | v_data1_u8r);
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC4_ADDR, &v_data1_u8r,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_offset_s16 = (s16)((((s16)
                                    ((s8)v_data1_u8r))
                                   << BMG160_SHIFT_BIT_POSITION_BY_04_BITS)
                                  | (v_data2_u8r));
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the value of offset
 *  X, Y and Z in the registers 0x36, 0x37, 0x38, 0x39 and 0x3A
 *  the offset is a 12bit value
 *  @note X_AXIS ->
 *      @note bit 0 and 1 is available in the register 0x3A bit 2 and 3
 *      @note bit 2 and 3 is available in the register 0x36 bit 6 and 7
 *      @note bit 4 to 11 is available in the register 0x37 bit 0 to 7
 *  @note Y_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 1
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 3,4 and 5
 *      @note bit 4 to 11 is available in the register 0x38 bit 0 to 7
 *  @note Z_AXIS ->
 *      @note bit 0 is available in the register 0x3A bit 0
 *      @note bit 1,2 and 3 is available in the register 0x36 bit 0,1 and 3
 *      @note bit 4 to 11 is available in the register 0x39 bit 0 to 7
 *
 *  @param  v_axis_u8 : The value of offset axis selection
 *  v_axis_u8       |    value
 *  ----------------|--------------
 *  BMG160_X_AXIS   |   1
 *  BMG160_Y_AXIS   |   0
 *  BMG160_Z_AXIS   |   0
 *
 *  @param v_offset_s16: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset(
    u8 v_axis_u8, s16 v_offset_s16)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data1_u8r = BMG160_INIT_VALUE;
    u8 v_data2_u8r = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_axis_u8)
        {
        /* write offset */
        case BMG160_X_AXIS:
            v_data1_u8r = ((s8)(v_offset_s16
                                & BMG160_OFFSET_MASK_BYTE_OF_DATA))
                          >> BMG160_SHIFT_BIT_POSITION_BY_04_BITS;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC2_ADDR, &v_data1_u8r,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);

            v_data1_u8r = (u8)(v_offset_s16
                               & BMG160_OFFSET_X_BIT_MASK1);
            v_data2_u8r = BMG160_SET_BITSLICE(v_data2_u8r,
                                              BMG160_OFC1_ADDR_OFFSET_X, v_data1_u8r);
            comres += p_bmg160->BMG160_BUS_READ_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_OFC1_ADDR_OFFSET_X__REG,
                       &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);

            v_data1_u8r = (u8)(v_offset_s16
                               & BMG160_OFFSET_X_BIT_MASK2);
            v_data2_u8r = BMG160_SET_BITSLICE(v_data2_u8r,
                                              BMG160_TRIM_GP0_ADDR_OFFSET_X, v_data1_u8r);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_TRIM_GP0_ADDR_OFFSET_X__REG,
                       &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Y_AXIS:
            v_data1_u8r = ((s8)(v_offset_s16
                                & BMG160_OFFSET_MASK_BYTE_OF_DATA)) >>
                          BMG160_SHIFT_BIT_POSITION_BY_04_BITS;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC3_ADDR, &v_data1_u8r,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);

            v_data1_u8r = (u8)(v_offset_s16
                               & BMG160_OFFSET_Y_Z_BIT_MASK2);
            v_data2_u8r = BMG160_SET_BITSLICE(v_data2_u8r,
                                              BMG160_OFC1_ADDR_OFFSET_Y, v_data1_u8r);
            comres += p_bmg160->BMG160_BUS_READ_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_OFC1_ADDR_OFFSET_Y__REG,
                       &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);

            v_data1_u8r = (u8)(v_offset_s16
                               & BMG160_OFFSET_Y_Z_BIT_MASK1);
            v_data2_u8r = BMG160_SET_BITSLICE(v_data2_u8r,
                                              BMG160_TRIM_GP0_ADDR_OFFSET_Y, v_data1_u8r);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_TRIM_GP0_ADDR_OFFSET_Y__REG,
                       &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_Z_AXIS:
            v_data1_u8r = ((s8)(v_offset_s16
                                & BMG160_OFFSET_MASK_BYTE_OF_DATA)) >>
                          BMG160_SHIFT_BIT_POSITION_BY_04_BITS;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_OFC4_ADDR, &v_data1_u8r,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);

            v_data1_u8r = (u8)(v_offset_s16
                               & BMG160_OFFSET_Y_Z_BIT_MASK2);
            v_data2_u8r = BMG160_SET_BITSLICE(v_data2_u8r,
                                              BMG160_OFC1_ADDR_OFFSET_Z, v_data1_u8r);
            comres += p_bmg160->BMG160_BUS_READ_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_OFC1_ADDR_OFFSET_Z__REG,
                       &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);

            v_data1_u8r = (u8)(v_offset_s16
                               & BMG160_OFFSET_Y_Z_BIT_MASK1);
            v_data2_u8r = BMG160_SET_BITSLICE(v_data2_u8r,
                                              BMG160_TRIM_GP0_ADDR_OFFSET_Z, v_data1_u8r);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_TRIM_GP0_ADDR_OFFSET_Z__REG,
                       &v_data2_u8r, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of general
 *  purpose register in the register 0x3A and 0x3B
 *
 *
 *
 *
 *  @param v_param_u8: The value of general purpose register select
 *  v_param_u8      |    value
 *  ----------------|--------------
 *  BMG160_GP0      |  0
 *  BMG160_GP1      |  1
 *
 *  @param v_gp_u8: The value of general purpose register
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_gp(u8 v_param_u8,
        u8 *v_gp_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* read general purpose register*/
        case BMG160_GP0:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP0_ADDR_GP0__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_gp_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                           BMG160_TRIM_GP0_ADDR_GP0);
            break;
        case BMG160_GP1:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP1_ADDR, &v_data_u8,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
            *v_gp_u8 = v_data_u8;
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of general
 *  purpose register in the register 0x3A and 0x3B
 *
 *
 *
 *
 *  @param v_param_u8: The value of general purpose register select
 *  v_param_u8      |    value
 *  ----------------|--------------
 *  BMG160_GP0      |  0
 *  BMG160_GP1      |  1
 *
 *  @param v_gp_u8: The value of general purpose register
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_gp(u8 v_param_u8,
        u8 v_gp_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        switch (v_param_u8)
        {
        /* write general purpose register*/
        case BMG160_GP0:
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP0_ADDR_GP0__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_TRIM_GP0_ADDR_GP0, v_gp_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_TRIM_GP0_ADDR_GP0__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMG160_GP1:
            v_data_u8 = v_gp_u8;
            comres = p_bmg160->BMG160_BUS_WRITE_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_TRIM_GP1_ADDR,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            comres = E_BMG160_OUT_OF_RANGE;
            break;
        }
    }
    return comres;
}
/*!
 * @brief Reads FIFO data from location 0x3F
 *
 *
 *
 *
 *  @param v_fifo_data_u8 : The data of fifo
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error result of communication routines
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_FIFO_data_reg(u8 *v_fifo_data_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the fifo data */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_DATA_ADDR, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_data_u8 = v_data_u8;
    }
    return comres;
}
/*!
 *  @brief this api is used to read the fifo status
 *  of frame_counter and overrun in the register 0x0E
 *  @note frame_counter > bit from 0 to 6
 *  @note overrun -> bit 7
 *
 *
 *
 *  @param v_fifo_stat_u8 : The value of fifo overrun and fifo counter
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_stat_reg(
    u8 *v_fifo_stat_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo over run and frame counter */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_STAT_ADDR, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_stat_u8 = v_data_u8;
    }
    return comres;
}
/*!
 *  @brief this API is used to get the fifo frame counter
 *  in the register 0x0E bit 0 to 6
 *
 *
 *
 *  @param v_fifo_frame_count_u8: The value of fifo frame counter
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_frame_count(
    u8 *v_fifo_frame_count_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8  = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo frame counter */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_STAT_FRAME_COUNTER__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_frame_count_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_FIFO_STAT_FRAME_COUNTER);
    }
    return comres;
}
/*!
 *  @brief this API is used to get the fifo over run
 *  in the register 0x0E bit 7
 *
 *
 *
 *  @param v_fifo_overrun_u8: The value of fifo over run
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_overrun(
    u8 *v_fifo_overrun_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo over run*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_STAT_OVERRUN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_overrun_u8 = BMG160_GET_BITSLICE(v_data_u8,
                             BMG160_FIFO_STAT_OVERRUN);
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of fifo mode
 *  in the register 0x3E bit 6 and 7
 *
 *
 *
 *  @param v_fifo_mode_u8 : The value of fifo mode
 *        mode      |    value
 *  ----------------|--------------
 *      BYPASS      |  0
 *      FIFO        |  1
 *      STREAM      |  2
 *      RESERVED    |  3
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_mode(u8 *v_fifo_mode_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo mode*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_CGF0_ADDR_MODE__REG, &v_data_u8,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_mode_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                              BMG160_FIFO_CGF0_ADDR_MODE);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of fifo mode
 *  in the register 0x3E bit 6 and 7
 *
 *
 *
 *  @param v_fifo_mode_u8 : The value of fifo mode
 *        mode      |    value
 *  ----------------|--------------
 *      BYPASS      |  0
 *      FIFO        |  1
 *      STREAM      |  2
 *      RESERVED    |  3
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_mode(u8 v_fifo_mode_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_fifo_mode_u8 < BMG160_BIT_LENGTH_FIFO_MODE)
        {
            /* write fifo mode*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FIFO_CGF0_ADDR_MODE__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FIFO_CGF0_ADDR_MODE, v_fifo_mode_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FIFO_CGF0_ADDR_MODE__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the status of fifo
 *  data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param v_fifo_data_select_u8 : The value of fifo data selection
 *      data selection         |    value
 *  ---------------------------|--------------
 *      X,Y and Z (DEFAULT)    |  0
 *      X only                 |  1
 *      Y only                 |  2
 *      Z only                 |  3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_data_select(
    u8 *v_fifo_data_select_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read fifo data select*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_FIFO_CGF0_ADDR_DATA_SELECT__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_fifo_data_select_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                 BMG160_FIFO_CGF0_ADDR_DATA_SELECT);
    }
    return comres;
}
/*!
 *  @brief This API is used to set the status of fifo
 *  data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param v_fifo_data_select_u8 : The value of fifo data selection
 *      data selection         |    value
 *  ---------------------------|--------------
 *      X,Y and Z (DEFAULT)    |  0
 *      X only                 |  1
 *      Y only                 |  2
 *      Z only                 |  3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_data_select(
    u8 v_fifo_data_select_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_fifo_data_select_u8 <
                BMG160_BIT_LENGTH_FIFO_DATA_SELECT)
        {
            /* write fifo data select*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_FIFO_CGF0_ADDR_DATA_SELECT__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_FIFO_CGF0_ADDR_DATA_SELECT,
                                            v_fifo_data_select_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_FIFO_CGF0_ADDR_DATA_SELECT__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to get the operating modes of the
 *  sensor in the registers 0x11 and 0x12
 *
 *
 *
 *  @param  v_power_mode_u8 :The value of power mode
 *  value     |   power mode
 * -----------|----------------
 *     0      | BMG160_MODE_NORMAL
 *     1      | BMG160_MODE_SUSPEND
 *     2      | BMG160_MODE_DEEPSUSPEND
 *     3      | BMG160_MODE_FASTPOWERUP
 *     4      | BMG160_MODE_ADVANCEDPOWERSAVING
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_power_mode(u8 *v_power_mode_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 data1 = BMG160_INIT_VALUE;
    u8 data2 = BMG160_INIT_VALUE;
    u8 data3 = BMG160_INIT_VALUE;

    if (p_bmg160 == BMG160_INIT_VALUE)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read the power mode*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MODE_LPM1_ADDR, &data1,
                                                BMG160_GEN_READ_WRITE_DATA_LENGTH);
        comres += p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                  BMG160_MODE_LPM2_ADDR, &data2,
                  BMG160_GEN_READ_WRITE_DATA_LENGTH);
        data1  = (data1 & 0xA0) >> 5;
        data3  = (data2 & 0x40) >> 6;
        data2  = (data2 & 0x80) >> 7;
        if (data3 == 0x01)
        {
            *v_power_mode_u8  = BMG160_MODE_ADVANCEDPOWERSAVING;
        }
        else
        {
            if ((data1 == 0x00) && (data2 == 0x00))
            {
                *v_power_mode_u8  = BMG160_MODE_NORMAL;
            }
            else
            {
                if ((data1 == 0x01) || (data1 == 0x05))
                {
                    *v_power_mode_u8  =
                        BMG160_MODE_DEEPSUSPEND;
                }
                else
                {
                    if ((data1 == 0x04) &&
                            (data2 == 0x00))
                    {
                        *v_power_mode_u8  =
                            BMG160_MODE_SUSPEND;
                    }
                    else
                    {
                        if ((data1 == 0x04) &&
                                (data2 == 0x01))
                            *v_power_mode_u8  =
                                BMG160_MODE_FASTPOWERUP;
                    }
                }
            }
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to set the operating modes of the
 *  sensor in the registers 0x11 and 0x12
 *
 *
 *
 *  @param  v_power_mode_u8 :The value of power mode
 *  value     |   power mode
 * -----------|----------------
 *     0      | BMG160_MODE_NORMAL
 *     1      | BMG160_MODE_SUSPEND
 *     2      | BMG160_MODE_DEEPSUSPEND
 *     3      | BMG160_MODE_FASTPOWERUP
 *     4      | BMG160_MODE_ADVANCEDPOWERSAVING
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_power_mode(u8 v_power_mode_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 data1 = BMG160_INIT_VALUE;
    u8 data2 = BMG160_INIT_VALUE;
    u8 data3 = BMG160_INIT_VALUE;
    u8 v_autosleepduration = BMG160_INIT_VALUE;
    u8 v_bw_u8r = BMG160_INIT_VALUE;

    if (p_bmg160 == BMG160_INIT_VALUE)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_power_mode_u8 < BMG160_BIT_LENGTH_POWER_MODE)
        {
            /* write the power mode*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MODE_LPM1_ADDR, &data1,
                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
            comres += p_bmg160->BMG160_BUS_READ_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MODE_LPM2_ADDR, &data2,
                       BMG160_GEN_READ_WRITE_DATA_LENGTH);
            switch (v_power_mode_u8)
            {
            case BMG160_MODE_NORMAL:
                data1  = BMG160_SET_BITSLICE(data1,
                                             BMG160_MODE_LPM1, BMG160_INIT_VALUE);
                data2  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_FAST_POWERUP,
                                             BMG160_INIT_VALUE);
                data3  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING,
                                             BMG160_INIT_VALUE);
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM1_ADDR, &data1,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                p_bmg160->delay_msec(BMG160_POWER_MODE_DELAY);
                /*A minimum delay of at least
                450us is required for Multiple write.*/
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM2_ADDR, &data3,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                break;
            case BMG160_MODE_DEEPSUSPEND:
                data1  = BMG160_SET_BITSLICE(data1,
                                             BMG160_MODE_LPM1,
                                             BMG160_GEN_READ_WRITE_DATA_LENGTH);
                data2  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_FAST_POWERUP,
                                             BMG160_INIT_VALUE);
                data3  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING,
                                             BMG160_INIT_VALUE);
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM1_ADDR, &data1,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                p_bmg160->delay_msec(BMG160_POWER_MODE_DELAY);
                /*A minimum delay of at least
                450us is required for Multiple write.*/
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM2_ADDR, &data3,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                break;
            case BMG160_MODE_SUSPEND:
                data1  = BMG160_SET_BITSLICE(data1,
                                             BMG160_MODE_LPM1, BMG160_BIT_MASK_MODE_LPM1);
                data2  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_FAST_POWERUP,
                                             BMG160_INIT_VALUE);
                data3  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING,
                                             BMG160_INIT_VALUE);
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM1_ADDR, &data1,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                p_bmg160->delay_msec(BMG160_POWER_MODE_DELAY);
                /*A minimum delay of at least
                450us is required for Multiple write.*/
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM2_ADDR, &data3,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                break;
            case BMG160_MODE_FASTPOWERUP:
                data1  = BMG160_SET_BITSLICE(data1,
                                             BMG160_MODE_LPM1, BMG160_BIT_MASK_MODE_LPM1);
                data2  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_FAST_POWERUP,
                                             BMG160_GEN_READ_WRITE_DATA_LENGTH);
                data3  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING,
                                             BMG160_INIT_VALUE);
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM1_ADDR, &data1,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                p_bmg160->delay_msec(BMG160_POWER_MODE_DELAY);
                /*A minimum delay of at least
                450us is required for Multiple write.*/
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM2_ADDR, &data3,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                break;
            case BMG160_MODE_ADVANCEDPOWERSAVING:
                /* Configuring the proper settings for auto
                sleep duration */
                bmg160_get_bw(&v_bw_u8r);
                bmg160_get_auto_sleep_durn(
                    &v_autosleepduration);
                bmg160_set_auto_sleep_durn(v_autosleepduration,
                                           v_bw_u8r);
                comres += p_bmg160->BMG160_BUS_READ_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM2_ADDR, &data2,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                /* Configuring the advanced power saving mode*/
                data1  = BMG160_SET_BITSLICE(data1,
                                             BMG160_MODE_LPM1, BMG160_INIT_VALUE);
                data2  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_FAST_POWERUP,
                                             BMG160_INIT_VALUE);
                data3  = BMG160_SET_BITSLICE(data2,
                                             BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING,
                                             BMG160_GEN_READ_WRITE_DATA_LENGTH);
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM1_ADDR, &data1,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                p_bmg160->delay_msec(BMG160_POWER_MODE_DELAY);
                /*A minimum delay of at least
                450us is required for Multiple write.*/
                comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                          (p_bmg160->dev_addr,
                           BMG160_MODE_LPM2_ADDR, &data3,
                           BMG160_GEN_READ_WRITE_DATA_LENGTH);
                break;
            }
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief This API is used to to do selftest to sensor
 *  sensor in the register 0x3C
 *
 *
 *
 *
 *  @param v_result_u8: The value of self test
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_selftest(u8 *v_result_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data1_u8 = BMG160_INIT_VALUE;
    u8 v_data2_u8 = BMG160_INIT_VALUE;

    comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                            BMG160_SELFTEST_ADDR, &v_data1_u8,
                                            BMG160_GEN_READ_WRITE_DATA_LENGTH);
    v_data2_u8  = BMG160_GET_BITSLICE(v_data1_u8,
                                      BMG160_SELFTEST_ADDR_RATEOK);
    v_data1_u8  = BMG160_SET_BITSLICE(v_data1_u8,
                                      BMG160_SELFTEST_ADDR_TRIGBIST,
                                      BMG160_GEN_READ_WRITE_DATA_LENGTH);
    comres += p_bmg160->BMG160_BUS_WRITE_FUNC(p_bmg160->dev_addr,
              BMG160_SELFTEST_ADDR_TRIGBIST__REG, &v_data1_u8,
              BMG160_GEN_READ_WRITE_DATA_LENGTH);

    /* Waiting time to complete the selftest process */
    p_bmg160->delay_msec(BMG160_SELFTEST_DELAY);

    /* Reading Selftest v_result_u8 bir bist_failure */
    comres += p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
              BMG160_SELFTEST_ADDR_BISTFAIL__REG, &v_data1_u8,
              BMG160_GEN_READ_WRITE_DATA_LENGTH);
    v_data1_u8  = BMG160_GET_BITSLICE(v_data1_u8,
                                      BMG160_SELFTEST_ADDR_BISTFAIL);
    if ((v_data1_u8 == BMG160_SELFTEST_BISTFAIL) &&
            (v_data2_u8 == BMG160_SELFTEST_RATEOK))
        *v_result_u8 = C_BMG160_SUCCESS;
    else
        *v_result_u8 = C_BMG160_FAILURE;
    return comres;
}
/*!
 *  @brief  This API is used to get the auto sleep duration
 *  in the register 0x12 bit 0 to 2
 *
 *
 *
 *  @param v_durn_u8 : The value of gyro auto sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               not allowed    |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               20ms           |   6
 *               40ms           |   7
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_auto_sleep_durn(u8 *v_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read auto sleep duration*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_durn_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                         BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN);
    }
    return comres;
}
/*!
 *  @brief  This API is used to set the auto sleep duration
 *  in the register 0x12 bit 0 to 2
 *
 *
 *
 *  @param v_durn_u8 : The value of gyro auto sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               not allowed    |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               20ms           |   6
 *               40ms           |   7
 *
 *  @param v_bw_u8 : The value of selected bandwidth
 *        v_bw_u8               |   value
 *  ----------------------------|----------
 *  C_BMG160_NO_FILTER_U8X      |   0
 *  C_BMG160_BW_230HZ_U8X       |   1
 *  C_BMG160_BW_116HZ_u8X       |   2
 *  C_BMG160_BW_47HZ_u8X        |   3
 *  C_BMG160_BW_23HZ_u8X        |   4
 *  C_BMG160_BW_12HZ_u8X        |   5
 *  C_BMG160_BW_64HZ_u8X        |   6
 *  C_BMG160_BW_32HZ_u8X        |   7
 *
 *  @note: sleep duration depends on selected power mode and bandwidth
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_auto_sleep_durn(u8 v_durn_u8,
        u8 v_bw_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    u8 v_auto_sleep_durn_u8r = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* write auto sleep duration*/
        comres = p_bmg160->BMG160_BUS_READ_FUNC
                 (p_bmg160->dev_addr,
                  BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__REG,
                  &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        if (v_durn_u8 < BMG160_BIT_LENGTH_DURN)
        {
            switch (v_bw_u8)
            {
            case C_BMG160_NO_FILTER_U8X:
                if (v_durn_u8 >
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_230HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_116HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_47HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_5MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_5MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_23HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_10MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_10MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_12HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_20MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_20MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_64HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_10MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_10MS_AUTO_SLEEP_DURN_U8X;
                break;
            case C_BMG160_BW_32HZ_U8X:
                if (v_durn_u8 >
                        C_BMG160_20MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_20MS_AUTO_SLEEP_DURN_U8X;
                break;
            default:
                if (v_durn_u8 >
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X)
                    v_auto_sleep_durn_u8r =
                        v_durn_u8;
                else
                    v_auto_sleep_durn_u8r =
                        C_BMG160_4MS_AUTO_SLEEP_DURN_U8X;
                break;
            }
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN,
                                            v_auto_sleep_durn_u8r);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MODE_LPM2_ADDR_AUTO_SLEEP_DURN__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}
/*!
 *  @brief  This API is used to get the sleep duration
 *  in the register 0x11 bit 1 to 3
 *
 *
 *
 *  @param v_durn_u8 : The value of sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               2ms            |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               18ms           |   6
 *               20ms           |   7
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_get_sleep_durn(u8 *v_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        /* read sleep duration */
        comres = p_bmg160->BMG160_BUS_READ_FUNC(p_bmg160->dev_addr,
                                                BMG160_MODELPM1_ADDR_SLEEP_DURN__REG,
                                                &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        *v_durn_u8 = BMG160_GET_BITSLICE(v_data_u8,
                                         BMG160_MODELPM1_ADDR_SLEEP_DURN);
    }
    return comres;
}
/*!
 *  @brief  This API is used to set the sleep duration
 *  in the register 0x11 bit 1 to 3
 *
 *
 *
 *  @param v_durn_u8 : The value of sleep duration
 *           sleep duration     |   value
 *  ----------------------------|----------
 *               2ms            |   0
 *               4ms            |   1
 *               5ms            |   2
 *               8ms            |   3
 *               10ms           |   4
 *               15ms           |   5
 *               18ms           |   6
 *               20ms           |   7
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_sleep_durn(u8 v_durn_u8)
{
    /* variable used to return the bus communication status*/
    BMG160_RETURN_FUNCTION_TYPE comres = ERROR;
    u8 v_data_u8 = BMG160_INIT_VALUE;
    /* check the p_bmg160 struct pointer is NULL*/
    if (p_bmg160 == BMG160_NULL)
    {
        return  E_BMG160_NULL_PTR;
    }
    else
    {
        if (v_durn_u8 < BMG160_BIT_LENGTH_DURN)
        {
            /* write sleep duration*/
            comres = p_bmg160->BMG160_BUS_READ_FUNC
                     (p_bmg160->dev_addr,
                      BMG160_MODELPM1_ADDR_SLEEP_DURN__REG,
                      &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMG160_SET_BITSLICE(v_data_u8,
                                            BMG160_MODELPM1_ADDR_SLEEP_DURN, v_durn_u8);
            comres += p_bmg160->BMG160_BUS_WRITE_FUNC
                      (p_bmg160->dev_addr,
                       BMG160_MODELPM1_ADDR_SLEEP_DURN__REG,
                       &v_data_u8, BMG160_GEN_READ_WRITE_DATA_LENGTH);
        }
        else
        {
            comres = E_BMG160_OUT_OF_RANGE;
        }
    }
    return comres;
}

