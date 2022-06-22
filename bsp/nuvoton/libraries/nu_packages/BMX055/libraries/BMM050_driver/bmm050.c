/*
****************************************************************************
* Copyright (C) 2015 - 2016 Bosch Sensortec GmbH
*
* bmm050.c
* Date: 2016/03/17
* Revision: 2.0.6 $
*
* Usage: Sensor Driver for  BMM050 and BMM150 sensor
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
/****************************************************************************/


#include "bmm050.h"

static struct bmm050_t *p_bmm050;
/*!
 *  @brief This function is used for initialize
 *  bus read and bus write functions
 *  assign the chip id and device address
 *  chip id is read in the register 0x40 bit from 0 to 7
 *
 *  @note While changing the parameter of the bmm050
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
BMM050_RETURN_FUNCTION_TYPE bmm050_init(struct bmm050_t *bmm050)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /*Array holding the mag chip id
    v_data_u8[0] - chip id
    */
    u8 v_data_u8[BMM050_INIT_DATA_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };

    p_bmm050 = bmm050;

    /* set device from suspend into sleep mode */
    com_rslt = bmm050_set_power_mode(BMM050_ON);

    /* wait two millisecond for bmc to settle */
    p_bmm050->delay_msec(BMM050_DELAY_SETTLING_TIME);

    /*Read CHIP_ID and REv. info */
    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_CHIP_ID, v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    p_bmm050->company_id = v_data_u8[BMM050_CHIP_ID_DATA];

    /* Function to initialise trim values */
    com_rslt += bmm050_init_trim_registers();
    /* set the preset mode as regular*/
    com_rslt += bmm050_set_presetmode(BMM050_PRESETMODE_REGULAR);
    return com_rslt;
}
/*!
 *  @brief This API used to get the preset modes
 *
 *  @note The preset mode setting is
 *  depend on Data Rate, XY and Z repetitions
 *
 *
 *
 *  @param v_presetmode_u8: The value of selected preset mode
 *  value    | preset_mode
 * ----------|-----------------
 *    1      | BMM050_PRESETMODE_LOWPOWER
 *    2      | BMM050_PRESETMODE_REGULAR
 *    3      | BMM050_PRESETMODE_HIGHACCURACY
 *    4      | BMM050_PRESETMODE_ENHANCED
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_presetmode(
    u8 *v_presetmode_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_rate_u8 = BMM050_INIT_VALUE;
    u8 rep_xy = BMM050_INIT_VALUE;
    u8 rep_z = BMM050_INIT_VALUE;
    /* Get the current data rate */
    com_rslt = bmm050_get_data_rate(&v_data_rate_u8);
    /* Get the preset number of XY Repetitions */
    com_rslt += bmm050_get_rep_XY(&rep_xy);
    /* Get the preset number of Z Repetitions */
    com_rslt += bmm050_get_rep_Z(&rep_z);
    if ((v_data_rate_u8 == BMM050_LOWPOWER_DR) && (
                rep_xy == BMM050_LOWPOWER_REPXY) && (
                rep_z == BMM050_LOWPOWER_REPZ))
    {
        *v_presetmode_u8 = BMM050_PRESETMODE_LOWPOWER;
    }
    else
    {
        if ((v_data_rate_u8 == BMM050_REGULAR_DR) && (
                    rep_xy == BMM050_REGULAR_REPXY) && (
                    rep_z == BMM050_REGULAR_REPZ))
        {
            *v_presetmode_u8 = BMM050_PRESETMODE_REGULAR;
        }
        else
        {
            if ((v_data_rate_u8 == BMM050_HIGHACCURACY_DR) && (
                        rep_xy == BMM050_HIGHACCURACY_REPXY) && (
                        rep_z == BMM050_HIGHACCURACY_REPZ))
            {
                *v_presetmode_u8 =
                    BMM050_PRESETMODE_HIGHACCURACY;
            }
            else
            {
                if ((v_data_rate_u8 == BMM050_ENHANCED_DR) && (
                            rep_xy == BMM050_ENHANCED_REPXY) && (
                            rep_z == BMM050_ENHANCED_REPZ))
                {
                    *v_presetmode_u8 =
                        BMM050_PRESETMODE_ENHANCED;
                }
                else
                {
                    *v_presetmode_u8 =
                        E_BMM050_UNDEFINED_MODE;
                }
            }
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the preset modes
 *
 *  @note The preset mode setting is
 *  depend on Data Rate, XY and Z repetitions
 *
 *
 *
 *  @param v_presetmode_u8: The value of selected preset mode
 *  value    | preset_mode
 * ----------|-----------------
 *    1      | BMM050_PRESETMODE_LOWPOWER
 *    2      | BMM050_PRESETMODE_REGULAR
 *    3      | BMM050_PRESETMODE_HIGHACCURACY
 *    4      | BMM050_PRESETMODE_ENHANCED
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_presetmode(u8 v_presetmode_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    switch (v_presetmode_u8)
    {
    case BMM050_PRESETMODE_LOWPOWER:
        /* Set the data rate for Low Power mode */
        com_rslt = bmm050_set_data_rate(BMM050_LOWPOWER_DR);
        /* Set the XY-repetitions number for Low Power mode */
        com_rslt += bmm050_set_rep_XY(BMM050_LOWPOWER_REPXY);
        /* Set the Z-repetitions number  for Low Power mode */
        com_rslt += bmm050_set_rep_Z(BMM050_LOWPOWER_REPZ);
        break;
    case BMM050_PRESETMODE_REGULAR:
        /* Set the data rate for Regular mode */
        com_rslt = bmm050_set_data_rate(BMM050_REGULAR_DR);
        /* Set the XY-repetitions number for Regular mode */
        com_rslt += bmm050_set_rep_XY(BMM050_REGULAR_REPXY);
        /* Set the Z-repetitions number  for Regular mode */
        com_rslt += bmm050_set_rep_Z(BMM050_REGULAR_REPZ);
        break;
    case BMM050_PRESETMODE_HIGHACCURACY:
        /* Set the data rate for High Accuracy mode */
        com_rslt = bmm050_set_data_rate(BMM050_HIGHACCURACY_DR);
        /* Set the XY-repetitions number for High Accuracy mode */
        com_rslt += bmm050_set_rep_XY(BMM050_HIGHACCURACY_REPXY);
        /* Set the Z-repetitions number  for High Accuracy mode */
        com_rslt += bmm050_set_rep_Z(BMM050_HIGHACCURACY_REPZ);
        break;
    case BMM050_PRESETMODE_ENHANCED:
        /* Set the data rate for Enhanced Accuracy mode */
        com_rslt = bmm050_set_data_rate(BMM050_ENHANCED_DR);
        /* Set the XY-repetitions number for High Enhanced mode */
        com_rslt += bmm050_set_rep_XY(BMM050_ENHANCED_REPXY);
        /* Set the Z-repetitions number  for High Enhanced mode */
        com_rslt += bmm050_set_rep_Z(BMM050_ENHANCED_REPZ);
        break;
    default:
        com_rslt = E_BMM050_OUT_OF_RANGE;
        break;
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the functional state
 *  in the register 0x4C and 0x4B
 *  @note 0x4C bit 1 and 2
 *  @note 0x4B bit 0
 *
 *
 *  @param  v_functional_state_u8: The value of functional mode
 *  value     |   functional state
 * -----------|-------------------
 *   0x00     | BMM050_NORMAL_MODE
 *   0x01     | BMM050_SUSPEND_MODE
 *   0x02     | BMM050_FORCED_MODE
 *   0x03     | BMM050_SLEEP_MODE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_functional_state(
    u8 v_functional_state_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return E_BMM050_NULL_PTR;
    }
    else
    {
        /* select the functional state*/
        switch (v_functional_state_u8)
        {
        /* write the functional state*/
        case BMM050_NORMAL_MODE:
            com_rslt = bmm050_get_power_mode(&v_data_u8);
            if (v_data_u8 == BMM050_OFF)
            {
                com_rslt += bmm050_set_power_mode(BMM050_ON);
                p_bmm050->delay_msec(
                    BMM050_DELAY_SUSPEND_SLEEP);
            }
            com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(
                            p_bmm050->dev_addr,
                            BMM050_CONTROL_OPERATION_MODE__REG,
                            &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMM050_SET_BITSLICE(
                            v_data_u8,
                            BMM050_CONTROL_OPERATION_MODE,
                            BMM050_NORMAL_MODE);
            com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                            p_bmm050->dev_addr,
                            BMM050_CONTROL_OPERATION_MODE__REG,
                            &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMM050_SUSPEND_MODE:
            com_rslt = bmm050_set_power_mode(BMM050_OFF);
            break;
        case BMM050_FORCED_MODE:
            com_rslt = bmm050_get_power_mode(&v_data_u8);
            if (v_data_u8 == BMM050_OFF)
            {
                com_rslt += bmm050_set_power_mode(BMM050_ON);
                p_bmm050->delay_msec(
                    BMM050_DELAY_SUSPEND_SLEEP);
            }
            com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(
                            p_bmm050->dev_addr,
                            BMM050_CONTROL_OPERATION_MODE__REG,
                            &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMM050_SET_BITSLICE(
                            v_data_u8,
                            BMM050_CONTROL_OPERATION_MODE, BMM050_ON);
            com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                            p_bmm050->dev_addr,
                            BMM050_CONTROL_OPERATION_MODE__REG,
                            &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            break;
        case BMM050_SLEEP_MODE:
            com_rslt = bmm050_get_power_mode(&v_data_u8);
            if (v_data_u8 == BMM050_OFF)
            {
                com_rslt += bmm050_set_power_mode(BMM050_ON);
                p_bmm050->delay_msec(
                    BMM050_DELAY_SUSPEND_SLEEP);
            }
            com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(
                            p_bmm050->dev_addr,
                            BMM050_CONTROL_OPERATION_MODE__REG,
                            &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            v_data_u8 = BMM050_SET_BITSLICE(
                            v_data_u8,
                            BMM050_CONTROL_OPERATION_MODE,
                            BMM050_SLEEP_MODE);
            com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                            p_bmm050->dev_addr,
                            BMM050_CONTROL_OPERATION_MODE__REG,
                            &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            break;
        default:
            com_rslt = E_BMM050_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the functional state
 *  in the register 0x4C bit 1 and 2
 *
 *
 *
 *
 *  @param v_functional_state_u8: The value of functional mode
 *  value     |  functional state
 * -----------|--------------------
 *    0x00    |  Normal
 *    0x03    |  Sleep
 *  @note If user set the functional state as Force mode(0x01) and read the
 *  register it returns the value as 0x03 that is sleep mode.
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_functional_state(
    u8 *v_functional_state_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read the functional state*/
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_CONTROL_OPERATION_MODE__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        *v_functional_state_u8 = BMM050_GET_BITSLICE(
                                     v_data_u8, BMM050_CONTROL_OPERATION_MODE);
    }
    return com_rslt;
}
/*!
 * @brief This API reads compensated Magnetometer
 * data of X,Y,Z values
 * from location 0x42 to 0x49
 *
 *
 *
 *
 *  @param  mag_data : The data of mag compensated XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_mag_data_XYZ(
    struct bmm050_mag_data_s16_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* structure used to store the mag raw xyz and r data */
    struct
    {
        s16 raw_data_x;
        s16 raw_data_y;
        s16 raw_data_z;
        u16 raw_data_r;
    } raw_data_xyz_t;

    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read the mag xyz and r data*/
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_DATA_X_LSB, v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);

        if (!com_rslt)
        {
            /* Reading data for X axis */
            v_data_u8[BMM050_XLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_XLSB_DATA],
                                    BMM050_DATA_X_LSB_BIT);
            raw_data_xyz_t.raw_data_x = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_XMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_XLSB_DATA]);

            /* Reading data for Y axis */
            v_data_u8[BMM050_YLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_YLSB_DATA],
                                    BMM050_DATA_Y_LSB_BIT);
            raw_data_xyz_t.raw_data_y = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_YLSB_DATA]);

            /* Reading data for Z axis */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            raw_data_xyz_t.raw_data_z = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_ZMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                              | v_data_u8[BMM050_ZLSB_DATA]);


            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);



            /* Reading data for Resistance*/
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            raw_data_xyz_t.raw_data_r = (u16)((((u32)
                                                v_data_u8[BMM050_RMSB_DATA]) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                              | v_data_u8[BMM050_RLSB_DATA]);



            /* Compensation for X axis */
            mag_data->datax = bmm050_compensate_X(
                                  raw_data_xyz_t.raw_data_x,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Y axis */
            mag_data->datay = bmm050_compensate_Y(
                                  raw_data_xyz_t.raw_data_y,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Z axis */
            mag_data->dataz = bmm050_compensate_Z(
                                  raw_data_xyz_t.raw_data_z,
                                  raw_data_xyz_t.raw_data_r);

            /* Output raw resistance value */
            mag_data->resistance = raw_data_xyz_t.raw_data_r;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API reads remapped compensated Magnetometer
 *  data of X,Y,Z values
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *
 *
 *  @param  mag_data : The data of remapped compensated mag xyz data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_bmx055_remapped_mag_data_XYZ(
    struct bmm050_remapped_mag_s16_data_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* structure used to store the mag raw xyz and r data */
    struct
    {
        s16 raw_data_x;
        s16 raw_data_y;
        s16 raw_data_z;
        u16 raw_data_r;
    } raw_data_xyz_t;

    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_REMAPPED_BMX055_DATA_Y_LSB,
                   v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);

        if (!com_rslt)
        {
            /* Reading data for Y axis */
            v_data_u8[BMM050_REMAPPED_YLSB_DATA] =
                BMM050_GET_BITSLICE(
                    v_data_u8[BMM050_REMAPPED_YLSB_DATA],
                    BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT);
            raw_data_xyz_t.raw_data_y = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_REMAPPED_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_REMAPPED_YLSB_DATA]);


            /* Reading data for X axis */
            v_data_u8[BMM050_REMAPPED_XLSB_DATA] =
                BMM050_GET_BITSLICE(
                    v_data_u8[BMM050_REMAPPED_XLSB_DATA],
                    BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT);
            raw_data_xyz_t.raw_data_x = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_REMAPPED_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_REMAPPED_XLSB_DATA]);
            raw_data_xyz_t.raw_data_x = -raw_data_xyz_t.raw_data_x;

            /* Reading data for Z axis */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            raw_data_xyz_t.raw_data_z = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_ZMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                              | v_data_u8[BMM050_ZLSB_DATA]);



            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);

            /* Reading data for Resistance*/
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            raw_data_xyz_t.raw_data_r = (u16)((((u32)
                                                v_data_u8[BMM050_RMSB_DATA]) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                              | v_data_u8[BMM050_RLSB_DATA]);



            /* Compensation for X axis */
            mag_data->datax = bmm050_compensate_X(
                                  raw_data_xyz_t.raw_data_x,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Y axis */
            mag_data->datay = bmm050_compensate_Y(
                                  raw_data_xyz_t.raw_data_y,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Z axis */
            mag_data->dataz = bmm050_compensate_Z(
                                  raw_data_xyz_t.raw_data_z,
                                  raw_data_xyz_t.raw_data_r);

            /* Output raw resistance value */
            mag_data->resistance = raw_data_xyz_t.raw_data_r;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API reads compensated magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z  as s32
 *
 *
 *  @param mag_data : The data of compensated XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_mag_data_XYZ_s32(
    struct bmm050_mag_s32_data_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* structure used to store the mag raw xyz and r data */
    struct
    {
        s16 raw_data_x;
        s16 raw_data_y;
        s16 raw_data_z;
        u16 raw_data_r;
    } raw_data_xyz_t;

    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_DATA_X_LSB, v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);

        if (!com_rslt)
        {
            /* Reading data for X axis */
            v_data_u8[BMM050_XLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_XLSB_DATA],
                                    BMM050_DATA_X_LSB_BIT);
            raw_data_xyz_t.raw_data_x = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_XMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_XLSB_DATA]);

            /* Reading data for Y axis */
            v_data_u8[BMM050_YLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_YLSB_DATA],
                                    BMM050_DATA_Y_LSB_BIT);
            raw_data_xyz_t.raw_data_y = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_YLSB_DATA]);

            /* Reading data for Z axis */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            raw_data_xyz_t.raw_data_z = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_ZMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                              | v_data_u8[BMM050_ZLSB_DATA]);


            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);

            /* Reading data for Resistance*/
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            raw_data_xyz_t.raw_data_r = (u16)((((u32)
                                                v_data_u8[BMM050_RMSB_DATA]) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                              | v_data_u8[BMM050_RLSB_DATA]);


            /* Compensation for X axis */
            mag_data->datax = bmm050_compensate_X_s32(
                                  raw_data_xyz_t.raw_data_x,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Y axis */
            mag_data->datay = bmm050_compensate_Y_s32(
                                  raw_data_xyz_t.raw_data_y,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Z axis */
            mag_data->dataz = bmm050_compensate_Z_s32(
                                  raw_data_xyz_t.raw_data_z,
                                  raw_data_xyz_t.raw_data_r);

            /* Output raw resistance value */
            mag_data->resistance = raw_data_xyz_t.raw_data_r;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API reads remapped compensated magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z  as s32
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *
 *  @param mag_data : The data of remapped compensated XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_bmx055_remapped_mag_data_XYZ_s32(
    struct bmm050_remapped_mag_s32_data_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* structure used to store the mag raw xyz and r data */
    struct
    {
        s16 raw_data_x;
        s16 raw_data_y;
        s16 raw_data_z;
        u16 raw_data_r;
    } raw_data_xyz_t;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_REMAPPED_BMX055_DATA_Y_LSB,
                   v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);

        if (!com_rslt)
        {
            /* Reading data for Y axis */
            v_data_u8[BMM050_REMAPPED_YLSB_DATA] =
                BMM050_GET_BITSLICE(
                    v_data_u8[BMM050_REMAPPED_YLSB_DATA],
                    BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT);
            raw_data_xyz_t.raw_data_y = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_REMAPPED_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_REMAPPED_YLSB_DATA]);


            /* Reading data for X axis */
            v_data_u8[BMM050_REMAPPED_XLSB_DATA] =
                BMM050_GET_BITSLICE(
                    v_data_u8[BMM050_REMAPPED_XLSB_DATA],
                    BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT);
            raw_data_xyz_t.raw_data_x = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_REMAPPED_XMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_REMAPPED_XLSB_DATA]);
            raw_data_xyz_t.raw_data_x = -raw_data_xyz_t.raw_data_x;

            /* Reading data for Z axis */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            raw_data_xyz_t.raw_data_z = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_ZMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                              | v_data_u8[BMM050_ZLSB_DATA]);


            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);


            /* Reading data for Resistance*/
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            raw_data_xyz_t.raw_data_r = (u16)((((u32)
                                                v_data_u8[BMM050_RMSB_DATA]) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                              | v_data_u8[BMM050_RLSB_DATA]);




            /* Compensation for X axis */
            mag_data->datax = bmm050_compensate_X_s32(
                                  raw_data_xyz_t.raw_data_x,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Y axis */
            mag_data->datay = bmm050_compensate_Y_s32(
                                  raw_data_xyz_t.raw_data_y,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Z axis */
            mag_data->dataz = bmm050_compensate_Z_s32(
                                  raw_data_xyz_t.raw_data_z,
                                  raw_data_xyz_t.raw_data_r);

            /* Output raw resistance value */
            mag_data->resistance = raw_data_xyz_t.raw_data_r;
        }
    }
    return com_rslt;
}
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API reads compensated Magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z as float
 *
 *
 *
 *  @param mag_data : The value of compensated XYZ float data
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_mag_data_XYZ_float(
    struct bmm050_mag_data_float_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* structure used to store the mag raw xyz and r data */
    struct
    {
        s16 raw_data_x;
        s16 raw_data_y;
        s16 raw_data_z;
        s16 raw_data_r;
    } raw_data_xyz_t;

    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_DATA_X_LSB, v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);

        if (!com_rslt)
        {
            /* Reading data for X axis */
            v_data_u8[BMM050_XLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_XLSB_DATA],
                                    BMM050_DATA_X_LSB_BIT);
            raw_data_xyz_t.raw_data_x = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_XMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_XLSB_DATA]);

            /* Reading data for Y axis */
            v_data_u8[BMM050_YLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_YLSB_DATA],
                                    BMM050_DATA_Y_LSB_BIT);
            raw_data_xyz_t.raw_data_y = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_YLSB_DATA]);

            /* Reading data for Z axis */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            raw_data_xyz_t.raw_data_z = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_ZMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                              | v_data_u8[BMM050_ZLSB_DATA]);




            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);

            /* Reading data for Resistance*/
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            raw_data_xyz_t.raw_data_r = (u16)((((u32)
                                                v_data_u8[BMM050_RMSB_DATA]) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                              | v_data_u8[BMM050_RLSB_DATA]);


            /* Compensation for X axis */
            mag_data->datax = bmm050_compensate_X_float(
                                  raw_data_xyz_t.raw_data_x,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Y axis */
            mag_data->datay = bmm050_compensate_Y_float(
                                  raw_data_xyz_t.raw_data_y,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Z axis */
            mag_data->dataz = bmm050_compensate_Z_float(
                                  raw_data_xyz_t.raw_data_z,
                                  raw_data_xyz_t.raw_data_r);

            /* Output raw resistance value */
            mag_data->resistance = raw_data_xyz_t.raw_data_r;
        }
    }
    return com_rslt;
}
#endif
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API reads remapped compensated Magnetometer
 *  data of X,Y,Z values
 *  @note The output value of compensated X, Y, Z as float
 *
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *  @param mag_data : The value of remapped compensated XYZ float data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_read_bmx055_remapped_mag_data_XYZ_float(
    struct bmm050_remapped_mag_data_float_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* structure used to store the mag raw xyz and r data */
    struct
    {
        s16 raw_data_x;
        s16 raw_data_y;
        s16 raw_data_z;
        u16 raw_data_r;
    } raw_data_xyz_t;

    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_REMAPPED_BMX055_DATA_Y_LSB, v_data_u8,
                   BMM050_ALL_DATA_FRAME_LENGTH);

        if (!com_rslt)
        {
            /* Reading data for Y axis */
            v_data_u8[BMM050_REMAPPED_YLSB_DATA] =
                BMM050_GET_BITSLICE(
                    v_data_u8[BMM050_REMAPPED_YLSB_DATA],
                    BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT);
            raw_data_xyz_t.raw_data_y = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_REMAPPED_YMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_REMAPPED_YLSB_DATA]);

            /* Reading data for X axis */
            v_data_u8[BMM050_REMAPPED_XLSB_DATA] =
                BMM050_GET_BITSLICE(
                    v_data_u8[BMM050_REMAPPED_XLSB_DATA],
                    BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT);
            raw_data_xyz_t.raw_data_x = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_REMAPPED_XMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                              | v_data_u8[BMM050_REMAPPED_XLSB_DATA]);
            raw_data_xyz_t.raw_data_x = -raw_data_xyz_t.raw_data_x;

            /* Reading data for Z axis */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            raw_data_xyz_t.raw_data_z = (s16)((((s32)
                                                ((s8)v_data_u8[BMM050_ZMSB_DATA])) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                              | v_data_u8[BMM050_ZLSB_DATA]);



            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);


            /* Reading data for Resistance*/
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            raw_data_xyz_t.raw_data_r = (u16)((((u32)
                                                v_data_u8[BMM050_RMSB_DATA]) <<
                                               BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                              | v_data_u8[BMM050_RLSB_DATA]);


            /* Compensation for X axis */
            mag_data->datax = bmm050_compensate_X_float(
                                  raw_data_xyz_t.raw_data_x,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Y axis */
            mag_data->datay = bmm050_compensate_Y_float(
                                  raw_data_xyz_t.raw_data_y,
                                  raw_data_xyz_t.raw_data_r);

            /* Compensation for Z axis */
            mag_data->dataz = bmm050_compensate_Z_float(
                                  raw_data_xyz_t.raw_data_z,
                                  raw_data_xyz_t.raw_data_r);

            /* Output raw resistance value */
            mag_data->resistance = raw_data_xyz_t.raw_data_r;
        }
    }
    return com_rslt;
}
#endif
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
BMM050_RETURN_FUNCTION_TYPE bmm050_read_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   v_addr_u8, v_data_u8, v_len_u8);
    }
    return com_rslt;
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
BMM050_RETURN_FUNCTION_TYPE bmm050_write_register(u8 v_addr_u8,
        u8 *v_data_u8, u8 v_len_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_WRITE_FUNC(p_bmm050->dev_addr,
                   v_addr_u8, v_data_u8, v_len_u8);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the self test of the sensor
 *  in the register 0x4C bit 0
 *
 *
 *
 *  @param  v_selftest_u8 : The value of selftest
 *  @note write 0x01 to start self test
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_selftest(u8 v_selftest_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr, BMM050_CONTROL_SELFTEST__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(
                        v_data_u8, BMM050_CONTROL_SELFTEST, v_selftest_u8);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr, BMM050_CONTROL_SELFTEST__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to read the selftest of the sensor
 *
 *
 *
 *
 *  @param v_selftest_xyz: The self test value of XYZ
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_selftest_XYZ(
    u8 *v_selftest_xyz)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8[BMM050_SELFTEST_DATA_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    u8 v_result_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read self test*/
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr, BMM050_DATA_X_LSB_TESTX__REG,
                       v_data_u8, BMM050_SELFTEST_DATA_LENGTH);

        if (!com_rslt)
        {
            v_result_u8 =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_TESTZ);

            v_result_u8 = (v_result_u8
                           << BMM050_SHIFT_BIT_POSITION_BY_01_BIT);
            v_result_u8 = (v_result_u8 | BMM050_GET_BITSLICE(
                               v_data_u8[BMM050_YLSB_DATA], BMM050_DATA_Y_LSB_TESTY));

            v_result_u8 = (v_result_u8
                           << BMM050_SHIFT_BIT_POSITION_BY_01_BIT);
            v_result_u8 = (v_result_u8 | BMM050_GET_BITSLICE(
                               v_data_u8[BMM050_XLSB_DATA], BMM050_DATA_X_LSB_TESTX));

            *v_selftest_xyz = v_result_u8;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the spi3
 *  in the register 0x4B bit 2
 *
 *
 *
 *  @param  v_value_u8 : the value of spi3
 *  value  | Description
 * --------|------------
 *   0     | Disable
 *   1     | Enable
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_spi3(u8 v_value_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* write spi3 */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_POWER_CONTROL_SPI3_ENABLE__REG,
                   &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(v_data_u8,
                                        BMM050_POWER_CONTROL_SPI3_ENABLE, v_value_u8);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(p_bmm050->dev_addr,
                    BMM050_POWER_CONTROL_SPI3_ENABLE__REG,
                    &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the data rate of the sensor
 *  in the register 0x4C bit 3 to 5
 *
 *
 *
 *  @param  v_data_rate_u8 : The value of data rate
 *  value     |       Description
 * -----------|-----------------------
 *   0x00     |  BMM050_DATA_RATE_10HZ
 *   0x01     |  BMM050_DATA_RATE_02HZ
 *   0x02     |  BMM050_DATA_RATE_06HZ
 *   0x03     |  BMM050_DATA_RATE_08HZ
 *   0x04     |  BMM050_DATA_RATE_15HZ
 *   0x05     |  BMM050_DATA_RATE_20HZ
 *   0x06     |  BMM050_DATA_RATE_25HZ
 *   0x07     |  BMM050_DATA_RATE_30HZ
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_data_rate(u8 v_data_rate_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* set the data rate */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_CONTROL_DATA_RATE__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(v_data_u8,
                                        BMM050_CONTROL_DATA_RATE, v_data_rate_u8);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_CONTROL_DATA_RATE__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the data rate of the sensor
 *  in the register 0x4C bit 3 to 5
 *
 *
 *
 *  @param  v_data_rate_u8 : The value of data rate
 *  value     |       Description
 * -----------|-----------------------
 *   0x00     |  BMM050_DATA_RATE_10HZ
 *   0x01     |  BMM050_DATA_RATE_02HZ
 *   0x02     |  BMM050_DATA_RATE_06HZ
 *   0x03     |  BMM050_DATA_RATE_08HZ
 *   0x04     |  BMM050_DATA_RATE_15HZ
 *   0x05     |  BMM050_DATA_RATE_20HZ
 *   0x06     |  BMM050_DATA_RATE_25HZ
 *   0x07     |  BMM050_DATA_RATE_30HZ
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_data_rate(u8 *v_data_rate_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_CONTROL_DATA_RATE__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        *v_data_rate_u8 = BMM050_GET_BITSLICE(v_data_u8,
                                              BMM050_CONTROL_DATA_RATE);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to perform the
 *  advanced self test
 *
 *
 *
 *  @param v_diff_z_s16 : The output of advance self test
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_perform_advanced_selftest(
    s16 *v_diff_z_s16)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    s16 result_positive = BMM050_INIT_VALUE;
    s16 result_negative  = BMM050_INIT_VALUE;
    struct bmm050_mag_data_s16_t mag_data = {BMM050_INIT_VALUE,
               BMM050_INIT_VALUE, BMM050_INIT_VALUE,
               BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* set sleep mode to prepare for forced measurement.
        * If sensor is off, this will turn it on
        * and respect needed delays. */
        com_rslt = bmm050_set_functional_state(BMM050_SLEEP_MODE);

        /* set normal accuracy mode */
        com_rslt += bmm050_set_rep_Z(BMM050_LOWPOWER_REPZ);
        /* 14 repetitions Z in normal accuracy mode */

        /* disable X, Y channel */
        com_rslt += bmm050_set_control_measurement_x(
                        BMM050_CHANNEL_DISABLE);
        com_rslt += bmm050_set_control_measurement_y(
                        BMM050_CHANNEL_DISABLE);

        /* enable positive current and force a
        * measurement with positive field */
        com_rslt += bmm050_set_advanced_selftest(
                        BMM050_ADVANCED_SELFTEST_POSITIVE);
        com_rslt += bmm050_set_functional_state(BMM050_FORCED_MODE);
        /* wait for measurement to complete */
        p_bmm050->delay_msec(BMM050_SELFTEST_DELAY);

        /* read result from positive field measurement */
        com_rslt += bmm050_read_mag_data_XYZ(&mag_data);
        result_positive = mag_data.dataz;

        /* enable negative current and force a
        * measurement with negative field */
        com_rslt += bmm050_set_advanced_selftest(
                        BMM050_ADVANCED_SELFTEST_NEGATIVE);
        com_rslt += bmm050_set_functional_state(BMM050_FORCED_MODE);
        p_bmm050->delay_msec(BMM050_SELFTEST_DELAY);
        /* wait for measurement to complete */

        /* read result from negative field measurement */
        com_rslt += bmm050_read_mag_data_XYZ(&mag_data);
        result_negative = mag_data.dataz;

        /* turn off self test current */
        com_rslt += bmm050_set_advanced_selftest(
                        BMM050_ADVANCED_SELFTEST_OFF);

        /* enable X, Y channel */
        com_rslt += bmm050_set_control_measurement_x(
                        BMM050_CHANNEL_ENABLE);
        com_rslt += bmm050_set_control_measurement_y(
                        BMM050_CHANNEL_ENABLE);

        /* write out difference in positive and negative field.
        * This should be ~ 200 mT = 3200 LSB */
        *v_diff_z_s16 = (result_positive - result_negative);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the trim values
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_init_trim_registers(void)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8[BMM050_TRIM_DATA_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
               BMM050_DIG_X1, (u8 *)&p_bmm050->dig_x1,
               BMM050_GEN_READ_WRITE_DATA_LENGTH);
    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_Y1, (u8 *)&p_bmm050->dig_y1,
                BMM050_GEN_READ_WRITE_DATA_LENGTH);
    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_X2, (u8 *)&p_bmm050->dig_x2,
                BMM050_GEN_READ_WRITE_DATA_LENGTH);
    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_Y2, (u8 *)&p_bmm050->dig_y2,
                BMM050_GEN_READ_WRITE_DATA_LENGTH);
    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_XY1, (u8 *)&p_bmm050->dig_xy1,
                BMM050_GEN_READ_WRITE_DATA_LENGTH);
    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_XY2, (u8 *)&p_bmm050->dig_xy2,
                BMM050_GEN_READ_WRITE_DATA_LENGTH);

    /* shorts can not be recast into (u8*)
    * due to possible mix up between trim data
    * arrangement and memory arrangement */

    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_Z1_LSB, v_data_u8, BMM050_TRIM_DATA_LENGTH);
    p_bmm050->dig_z1 = (u16)((((u32)((u8)
                                     v_data_u8[BMM050_TRIM_DIG_Z1_MSB_DATA])) <<
                              BMM050_SHIFT_BIT_POSITION_BY_08_BITS)
                             | v_data_u8[BMM050_TRIM_DIG_Z1_LSB_DATA]);

    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_Z2_LSB, v_data_u8, BMM050_TRIM_DATA_LENGTH);
    p_bmm050->dig_z2 = (s16)((((s32)(
                                   (s8)v_data_u8[BMM050_TRIM_DIG_Z2_MSB_DATA])) <<
                              BMM050_SHIFT_BIT_POSITION_BY_08_BITS)
                             | v_data_u8[BMM050_TRIM_DIG_Z2_LSB_DATA]);

    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_Z3_LSB, v_data_u8, BMM050_TRIM_DATA_LENGTH);
    p_bmm050->dig_z3 = (s16)((((s32)(
                                   (s8)v_data_u8[BMM050_TRIM_DIG_Z3_MSB_DATA])) <<
                              BMM050_SHIFT_BIT_POSITION_BY_08_BITS)
                             | v_data_u8[BMM050_TRIM_DIG_Z3_LSB_DATA]);

    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_Z4_LSB, v_data_u8, BMM050_TRIM_DATA_LENGTH);
    p_bmm050->dig_z4 = (s16)((((s32)(
                                   (s8)v_data_u8[BMM050_TRIM_DIG_Z4_MSB_DATA])) <<
                              BMM050_SHIFT_BIT_POSITION_BY_08_BITS)
                             | v_data_u8[BMM050_TRIM_DIG_Z4_LSB_DATA]);

    com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                BMM050_DIG_XYZ1_LSB, v_data_u8, BMM050_TRIM_DATA_LENGTH);
    v_data_u8[BMM050_TRIM_DIG_XYZ1_MSB_DATA] =
        BMM050_GET_BITSLICE(v_data_u8[BMM050_TRIM_DIG_XYZ1_MSB_DATA],
                            BMM050_DIG_XYZ1_MSB);
    p_bmm050->dig_xyz1 = (u16)((((u32)
                                 ((u8)v_data_u8[BMM050_TRIM_DIG_XYZ1_MSB_DATA])) <<
                                BMM050_SHIFT_BIT_POSITION_BY_08_BITS)
                               | v_data_u8[BMM050_TRIM_DIG_XYZ1_LSB_DATA]);
    return com_rslt;
}
/*!
 *  @brief This API used to set the advanced self test
 *  in the register 0x4C bit 6 and 7
 *
 *
 *
 *  @param  v_advanced_selftest_u8 : The output value of advanced self test
 *    value      |   Status
 *  -------------|-------------------
 *       0       |  BMM050_ADVANCED_SELFTEST_OFF
 *       2       |  BMM050_ADVANCED_SELFTEST_NEGATIVE
 *       3       |  BMM050_ADVANCED_SELFTEST_POSITIVE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_advanced_selftest(
    u8 v_advanced_selftest_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        switch (v_advanced_selftest_u8)
        {
        /* perform advanced self test*/
        case BMM050_ADVANCED_SELFTEST_OFF:
            com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                           p_bmm050->dev_addr,
                           BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                           &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            if (!com_rslt)
            {
                v_data_u8 = BMM050_SET_BITSLICE(
                                v_data_u8,
                                BMM050_CONTROL_ADVANCED_SELFTEST,
                                BMM050_ADVANCED_SELFTEST_OFF);

                com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                                p_bmm050->dev_addr,
                                BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                                &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            }
            break;
        case BMM050_ADVANCED_SELFTEST_POSITIVE:
            com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                           p_bmm050->dev_addr,
                           BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                           &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            if (!com_rslt)
            {
                v_data_u8 = BMM050_SET_BITSLICE(
                                v_data_u8,
                                BMM050_CONTROL_ADVANCED_SELFTEST,
                                BMM050_ADVANCED_SELFTEST_POSITIVE);

                com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                                p_bmm050->dev_addr,
                                BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                                &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            }
            break;
        case BMM050_ADVANCED_SELFTEST_NEGATIVE:
            com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                           p_bmm050->dev_addr,
                           BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                           &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            if (!com_rslt)
            {
                v_data_u8 = BMM050_SET_BITSLICE(
                                v_data_u8,
                                BMM050_CONTROL_ADVANCED_SELFTEST,
                                BMM050_ADVANCED_SELFTEST_NEGATIVE);
                com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                                p_bmm050->dev_addr,
                                BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                                &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
            }
            break;
        default:
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the advanced self test
 *  in the register 0x4C bit 6 and 7
 *
 *
 *
 *  @param  v_advanced_selftest_u8 : The output value of advanced self test
 *    value      |   Status
 *  -------------|-------------------
 *       0       |  BMM050_ADVANCED_SELFTEST_OFF
 *       2       |  BMM050_ADVANCED_SELFTEST_NEGATIVE
 *       3       |  BMM050_ADVANCED_SELFTEST_POSITIVE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_advanced_selftest(
    u8 *v_advanced_selftest_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read advanced self test */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_CONTROL_ADVANCED_SELFTEST__REG,
                   &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        if (!com_rslt)
        {
            *v_advanced_selftest_u8 = BMM050_GET_BITSLICE(v_data_u8,
                                      BMM050_CONTROL_ADVANCED_SELFTEST);
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the power control bit
 *  in the register 0x4B bit 0
 *
 *
 *
 *  @param v_power_mode_u8 : The value of power control bit enable
 *   value     |  status
 *  -----------|------------
 *      0      | Disable the power control bit
 *      1      | Enable the power control bit
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_power_mode(u8 *v_power_mode_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read power control bit */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_POWER_CONTROL_POWER_CONTROL_BIT__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        if (!com_rslt)
        {
            *v_power_mode_u8 = BMM050_GET_BITSLICE(v_data_u8,
                                                   BMM050_POWER_CONTROL_POWER_CONTROL_BIT);
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the power control bit
 *  in the register 0x4B bit 0
 *
 *
 *
 *  @param v_power_mode_u8 : The value of power control bit enable
 *   value     |  status
 *  -----------|------------
 *      0      | Disable the power control bit
 *      1      | Enable the power control bit
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_power_mode(u8 v_power_mode_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* write power control bit*/
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_POWER_CONTROL_POWER_CONTROL_BIT__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(v_data_u8,
                                        BMM050_POWER_CONTROL_POWER_CONTROL_BIT, v_power_mode_u8);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_POWER_CONTROL_POWER_CONTROL_BIT__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the x and y
 *  repetition in the register 0x51 bit 0 to 7
 *
 *
 *
 *  @param v_rep_xy_u8 : The value of x and y repetitions
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_rep_XY(
    u8 *v_rep_xy_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read XY repetitions*/
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_REP_XY,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        *v_rep_xy_u8 = v_data_u8;
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the x and y
 *  repetition in the register 0x51 bit 0 to 7
 *
 *
 *
 *  @param v_rep_xy_u8 : The value of x and y repetitions
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_rep_XY(
    u8 v_rep_xy_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* write XY repetitions*/
        v_data_u8 = v_rep_xy_u8;
        com_rslt = p_bmm050->BMM050_BUS_WRITE_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_REP_XY,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the z repetition in the
 *  register 0x52 bit 0 to 7
 *
 *
 *
 *  @param v_rep_z_u8 : The value of z repetitions
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_rep_Z(
    u8 *v_rep_z_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read Z repetitions*/
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_REP_Z,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        *v_rep_z_u8 = v_data_u8;
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the z repetition in the
 *  register 0x52 bit 0 to 7
 *
 *
 *
 *  @param v_rep_z_u8 : The value of z repetitions
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_rep_Z(
    u8 v_rep_z_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* write Z repetitions*/
        v_data_u8 = v_rep_z_u8;
        com_rslt = p_bmm050->BMM050_BUS_WRITE_FUNC(p_bmm050->dev_addr,
                   BMM050_REP_Z, &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to get the compensated X data
 *  the out put of X as s16
 *
 *
 *
 *  @param  mag_data_x : The value of raw X data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated X data value output as s16
 *
*/
s16 bmm050_compensate_X(s16 mag_data_x, u16 data_r)
{
    s16 inter_retval = BMM050_INIT_VALUE;
    /* no overflow */
    if (mag_data_x != BMM050_FLIP_OVERFLOW_ADCVAL)
    {
        if ((data_r != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE))
        {
            inter_retval = ((s16)(((u16)
                                   ((((s32)p_bmm050->dig_xyz1)
                                     << BMM050_SHIFT_BIT_POSITION_BY_14_BITS) /
                                    (data_r != BMM050_INIT_VALUE ?
                                     data_r : p_bmm050->dig_xyz1))) -
                                  ((u16)0x4000)));
        }
        else
        {
            inter_retval = BMM050_OVERFLOW_OUTPUT;
            return inter_retval;
        }
        inter_retval = ((s16)((((s32)mag_data_x) *
                               ((((((((s32)p_bmm050->dig_xy2) *
                                     ((((s32)inter_retval) *
                                       ((s32)inter_retval)) >>
                                      BMM050_SHIFT_BIT_POSITION_BY_07_BITS)) +
                                    (((s32)inter_retval) *
                                     ((s32)(((s16)p_bmm050->dig_xy1)
                                            << BMM050_SHIFT_BIT_POSITION_BY_07_BITS))))
                                   >> BMM050_SHIFT_BIT_POSITION_BY_09_BITS) +
                                  ((s32)0x100000)) *
                                 ((s32)(((s16)p_bmm050->dig_x2) +
                                        ((s16)0xA0)))) >>
                                BMM050_SHIFT_BIT_POSITION_BY_12_BITS))
                              >> BMM050_SHIFT_BIT_POSITION_BY_13_BITS)) +
                       (((s16)p_bmm050->dig_x1)
                        << BMM050_SHIFT_BIT_POSITION_BY_03_BITS);
    }
    else
    {
        /* overflow */
        inter_retval = BMM050_OVERFLOW_OUTPUT;
    }
    return inter_retval;
}
/*!
 *  @brief This API used to get the compensated X data
 *  the out put of X as s32
 *
 *
 *
 *  @param  mag_data_x : The value of raw X data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated X data value output as s32
 *
*/
s32 bmm050_compensate_X_s32(s16 mag_data_x, u16 data_r)
{
    s32 retval = BMM050_INIT_VALUE;

    retval = bmm050_compensate_X(mag_data_x, data_r);
    if (retval == (s32)BMM050_OVERFLOW_OUTPUT)
        retval = BMM050_OVERFLOW_OUTPUT_S32;
    return retval;
}
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API used to get the compensated X data
 *  the out put of X as float
 *
 *
 *
 *  @param  mag_data_x : The value of raw X data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated X data value output as float
 *
*/
float bmm050_compensate_X_float(s16 mag_data_x, u16 data_r)
{
    float inter_retval = BMM050_INIT_VALUE;

    if (mag_data_x != BMM050_FLIP_OVERFLOW_ADCVAL   /* no overflow */
       )
    {
        if ((data_r != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE))
        {
            inter_retval = ((((float)p_bmm050->dig_xyz1)
                             * 16384.0 / data_r) - 16384.0);
        }
        else
        {
            inter_retval = BMM050_OVERFLOW_OUTPUT_FLOAT;
            return inter_retval;
        }
        inter_retval = (((mag_data_x * ((((((float)p_bmm050->dig_xy2) *
                                           (inter_retval * inter_retval /
                                            268435456.0) +
                                           inter_retval * ((float)p_bmm050->dig_xy1)
                                           / 16384.0)) + 256.0) *
                                        (((float)p_bmm050->dig_x2) + 160.0)))
                         / 8192.0)
                        + (((float)p_bmm050->dig_x1) *
                           8.0)) / 16.0;
    }
    else
    {
        inter_retval = BMM050_OVERFLOW_OUTPUT_FLOAT;
    }
    return inter_retval;
}
#endif
/*!
 *  @brief This API used to get the compensated Y data
 *  the out put of Y as s16
 *
 *
 *
 *  @param  mag_data_y : The value of raw Y data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Y data value output as s16
 *
*/
s16 bmm050_compensate_Y(s16 mag_data_y, u16 data_r)
{
    s16 inter_retval = BMM050_INIT_VALUE;
    /* no overflow */
    if (mag_data_y != BMM050_FLIP_OVERFLOW_ADCVAL)
    {
        if ((data_r != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE))
        {
            inter_retval = ((s16)(((u16)(((
                                              (s32)p_bmm050->dig_xyz1)
                                          << BMM050_SHIFT_BIT_POSITION_BY_14_BITS) /
                                         (data_r != BMM050_INIT_VALUE ?
                                          data_r : p_bmm050->dig_xyz1))) -
                                  ((u16)0x4000)));
        }
        else
        {
            inter_retval = BMM050_OVERFLOW_OUTPUT;
            return inter_retval;
        }
        inter_retval = ((s16)((((s32)mag_data_y) * ((((((((s32)
                               p_bmm050->dig_xy2) * ((((s32) inter_retval) *
                                       ((s32)inter_retval)) >>
                                       BMM050_SHIFT_BIT_POSITION_BY_07_BITS))
                               + (((s32)inter_retval) *
                                  ((s32)(((s16)p_bmm050->dig_xy1) <<
                                         BMM050_SHIFT_BIT_POSITION_BY_07_BITS))))
                               >> BMM050_SHIFT_BIT_POSITION_BY_09_BITS) +
                               ((s32)0x100000)) *
                               ((s32)(((s16)p_bmm050->dig_y2)
                                      + ((s16)0xA0))))
                               >> BMM050_SHIFT_BIT_POSITION_BY_12_BITS))
                              >> BMM050_SHIFT_BIT_POSITION_BY_13_BITS)) +
                       (((s16)p_bmm050->dig_y1)
                        << BMM050_SHIFT_BIT_POSITION_BY_03_BITS);
    }
    else
    {
        /* overflow */
        inter_retval = BMM050_OVERFLOW_OUTPUT;
    }
    return inter_retval;
}
/*!
 *  @brief This API used to get the compensated Y data
 *  the out put of Y as s32
 *
 *
 *
 *  @param  mag_data_y : The value of raw Y data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Y data value output as s32
 *
*/
s32 bmm050_compensate_Y_s32(s16 mag_data_y, u16 data_r)
{
    s32 retval = BMM050_INIT_VALUE;

    retval = bmm050_compensate_Y(mag_data_y, data_r);
    if (retval == BMM050_OVERFLOW_OUTPUT)
        retval = BMM050_OVERFLOW_OUTPUT_S32;
    return retval;
}
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API used to get the compensated Y data
 *  the out put of Y as float
 *
 *
 *
 *  @param  mag_data_y : The value of raw Y data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Y data value output as float
 *
*/
float bmm050_compensate_Y_float(s16 mag_data_y, u16 data_r)
{
    float inter_retval = BMM050_INIT_VALUE;

    if (mag_data_y != BMM050_FLIP_OVERFLOW_ADCVAL /* no overflow */
       )
    {
        if ((data_r != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE))
        {
            inter_retval = ((((float)p_bmm050->dig_xyz1)
                             * 16384.0
                             / data_r) - 16384.0);
        }
        else
        {
            inter_retval = BMM050_OVERFLOW_OUTPUT_FLOAT;
            return inter_retval;
        }
        inter_retval = (((mag_data_y * ((((((float)p_bmm050->dig_xy2) *
                                           (inter_retval * inter_retval
                                            / 268435456.0) +
                                           inter_retval * ((float)p_bmm050->dig_xy1)
                                           / 16384.0)) +
                                         256.0) *
                                        (((float)p_bmm050->dig_y2) + 160.0)))
                         / 8192.0) +
                        (((float)p_bmm050->dig_y1) * 8.0))
                       / 16.0;
    }
    else
    {
        /* overflow, set output to 0.0f */
        inter_retval = BMM050_OVERFLOW_OUTPUT_FLOAT;
    }
    return inter_retval;
}
#endif
/*!
 *  @brief This API used to get the compensated Z data
 *  the out put of Z as s16
 *
 *
 *
 *  @param  mag_data_z : The value of raw Z data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Z data value output as s16
 *
*/
s16 bmm050_compensate_Z(s16 mag_data_z, u16 data_r)
{
    s32 retval = BMM050_INIT_VALUE;

    if ((mag_data_z != BMM050_HALL_OVERFLOW_ADCVAL) /* no overflow */
       )
    {
        if ((p_bmm050->dig_z2 != BMM050_INIT_VALUE)
                && (p_bmm050->dig_z1 != BMM050_INIT_VALUE)
                && (data_r != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE))
        {
            retval = (((((s32)(mag_data_z - p_bmm050->dig_z4))
                        << BMM050_SHIFT_BIT_POSITION_BY_15_BITS) -
                       ((((s32)p_bmm050->dig_z3) * ((s32)(((s16)data_r) -
                                                    ((s16) p_bmm050->dig_xyz1))))
                        >> BMM050_SHIFT_BIT_POSITION_BY_02_BITS)) /
                      (p_bmm050->dig_z2 + ((s16)(((((s32)
                                                    p_bmm050->dig_z1) * ((((s16)data_r)
                                                            << BMM050_SHIFT_BIT_POSITION_BY_01_BIT))) +
                                                  (1 << BMM050_SHIFT_BIT_POSITION_BY_15_BITS))
                                                 >> BMM050_SHIFT_BIT_POSITION_BY_16_BITS))));
        }
        else
        {
            retval = BMM050_OVERFLOW_OUTPUT;
            return retval;
        }
        /* saturate result to +/- 2 microTesla */
        if (retval > BMM050_POSITIVE_SATURATION_Z)
        {
            retval =  BMM050_POSITIVE_SATURATION_Z;
        }
        else
        {
            if (retval < BMM050_NEGATIVE_SATURATION_Z)
                retval = BMM050_NEGATIVE_SATURATION_Z;
        }
    }
    else
    {
        /* overflow */
        retval = BMM050_OVERFLOW_OUTPUT;
    }
    return (s16)retval;
}
/*!
 *  @brief This API used to get the compensated Z data
 *  the out put of Z as s32
 *
 *
 *
 *  @param  mag_data_z : The value of raw Z data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Z data value output as s32
 *
*/
s32 bmm050_compensate_Z_s32(s16 mag_data_z, u16 data_r)
{
    s32 retval = BMM050_INIT_VALUE;

    if (mag_data_z != BMM050_HALL_OVERFLOW_ADCVAL)
    {
        if ((p_bmm050->dig_z2 != BMM050_INIT_VALUE)
                && (p_bmm050->dig_z1 != BMM050_INIT_VALUE)
                && (data_r != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE))
        {
            retval = (((((s32)(mag_data_z
                               - p_bmm050->dig_z4))
                        << BMM050_SHIFT_BIT_POSITION_BY_15_BITS) -
                       ((((s32)p_bmm050->dig_z3) *
                         ((s32)(((s16)data_r) -
                                ((s16)p_bmm050->dig_xyz1))))
                        >> BMM050_SHIFT_BIT_POSITION_BY_02_BITS)) /
                      (p_bmm050->dig_z2 +
                       ((s16)(((((s32)p_bmm050->dig_z1) *
                                ((((s16)data_r)
                                  << BMM050_SHIFT_BIT_POSITION_BY_01_BIT))) +
                               (1 << BMM050_SHIFT_BIT_POSITION_BY_15_BITS))
                              >> BMM050_SHIFT_BIT_POSITION_BY_16_BITS))));
        }
        else
        {
            retval = BMM050_OVERFLOW_OUTPUT_S32;
            return retval;
        }
    }
    else
    {
        retval = BMM050_OVERFLOW_OUTPUT_S32;
    }
    return retval;
}
#ifdef ENABLE_FLOAT
/*!
 *  @brief This API used to get the compensated Z data
 *  the out put of Z as float
 *
 *
 *
 *  @param  mag_data_z : The value of raw Z data
 *  @param  data_r : The value of R data
 *
 *  @return results of compensated Z data value output as float
 *
*/
float bmm050_compensate_Z_float(s16 mag_data_z, u16 data_r)
{
    float inter_retval = BMM050_INIT_VALUE;
    /* no overflow */
    if (mag_data_z != BMM050_HALL_OVERFLOW_ADCVAL)
    {
        if ((p_bmm050->dig_z2 != BMM050_INIT_VALUE)
                && (p_bmm050->dig_z1 != BMM050_INIT_VALUE)
                && (p_bmm050->dig_xyz1 != BMM050_INIT_VALUE)
                && (data_r != BMM050_INIT_VALUE))
        {
            inter_retval = ((((((float)mag_data_z) -
                               ((float)p_bmm050->dig_z4)) * 131072.0) -
                             (((float)p_bmm050->dig_z3) * (((float)data_r)
                                     - ((float)p_bmm050->dig_xyz1))))
                            / ((((float)p_bmm050->dig_z2) +
                                ((float)p_bmm050->dig_z1) * ((float)data_r) /
                                32768.0) * 4.0)) / 16.0;
        }
    }
    else
    {
        /* overflow, set output to 0.0f */
        inter_retval = BMM050_OVERFLOW_OUTPUT_FLOAT;
    }
    return inter_retval;
}
#endif
/*!
 *  @brief This API used to set the control measurement
 *  X data in the register 0x4E bit 3
 *
 *
 *  @param  v_enable_disable_u8: The value of control measurement-x
 *   value  |  Status
 *  --------|----------
 *     1    | ENABLE
 *     0    | DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_control_measurement_x(
    u8 v_enable_disable_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read control measurement */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_SENS_CONTROL_CHANNELX__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(v_data_u8,
                                        BMM050_SENS_CONTROL_CHANNELX,
                                        v_enable_disable_u8);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_SENS_CONTROL_CHANNELX__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used to set the control measurement
 *  Y data in the register 0x4E bit 4
 *
 *
 *  @param  v_enable_disable_u8: The value of control measurement-y
 *   value  |  Status
 *  --------|----------
 *     1    | ENABLE
 *     0    | DISABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_set_control_measurement_y(
    u8 v_enable_disable_u8)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        /* read control measurement */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_SENS_CONTROL_CHANNELY__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(
                        v_data_u8,
                        BMM050_SENS_CONTROL_CHANNELY,
                        v_enable_disable_u8);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_SENS_CONTROL_CHANNELY__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API used reset the register values to default
 *  in the register 0x4B
 *
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_soft_rst(void)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 v_data_u8 = BMM050_INIT_VALUE;
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        v_data_u8 = BMM050_ON;
        /* write soft rest */
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(
                       p_bmm050->dev_addr,
                       BMM050_POWER_CONTROL_SOFT_RST_7__REG,
                       &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(v_data_u8,
                                        BMM050_POWER_CONTROL_SOFT_RST_7,
                                        BMM050_SOFT_RESET7_ON);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_POWER_CONTROL_SOFT_RST_7__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);

        com_rslt += p_bmm050->BMM050_BUS_READ_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_POWER_CONTROL_SOFT_RST_1__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);
        v_data_u8 = BMM050_SET_BITSLICE(v_data_u8,
                                        BMM050_POWER_CONTROL_SOFT_RST_1,
                                        BMM050_SOFT_RESET1_ON);
        com_rslt += p_bmm050->BMM050_BUS_WRITE_FUNC(
                        p_bmm050->dev_addr,
                        BMM050_POWER_CONTROL_SOFT_RST_1__REG,
                        &v_data_u8, BMM050_GEN_READ_WRITE_DATA_LENGTH);

        p_bmm050->delay_msec(BMM050_DELAY_SOFTRESET);
    }
    return com_rslt;
}
/*!
 *  @brief This API reads Magnetometer
 *  raw data of X,Y,Z values and RHALL values
 *  from location 0x42 to 0x49
 *
 *
 *
 *
 *  @param  mag_data : The data of raw XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_raw_xyz(
    struct bmm050_mag_data_s16_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_DATA_X_LSB, v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);
        if (!com_rslt)
        {
            /* x data */
            v_data_u8[BMM050_XLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_XLSB_DATA],
                                    BMM050_DATA_X_LSB_BIT);
            mag_data->datax = (s16)((((s32)
                                      ((s8)v_data_u8[BMM050_XMSB_DATA]))
                                     << BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                    | v_data_u8[BMM050_XLSB_DATA]);
            /* y data */
            v_data_u8[BMM050_YLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_YLSB_DATA],
                                    BMM050_DATA_Y_LSB_BIT);
            mag_data->datay = (s16)((((s32)
                                      ((s8)v_data_u8[BMM050_YMSB_DATA]))
                                     << BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                    | v_data_u8[BMM050_YLSB_DATA]);
            /* z data */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            mag_data->dataz = (s16)((((s32)
                                      ((s8)v_data_u8[BMM050_ZMSB_DATA]))
                                     << BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                    | v_data_u8[BMM050_ZLSB_DATA]);


            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);




            /* r data */
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            mag_data->resistance = (u16)((((u32)
                                           v_data_u8[BMM050_RMSB_DATA]) <<
                                          BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                         | v_data_u8[BMM050_RLSB_DATA]);
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API reads remapped Magnetometer
 *  raw data of X,Y,Z values and RHALL values
 *  from location 0x42 to 0x49
 *
 *  @note In this function X and Y axis is remapped
 *  @note X is read from the address 0x44 & 0x45
 *  @note Y is read from the address 0x42 & 0x43
 *  @note this API is only applicable for BMX055 sensor
 *
 *
 *
 *  @param  mag_data : The data of remapped raw XYZ data
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
*/
BMM050_RETURN_FUNCTION_TYPE bmm050_get_bmx055_remapped_raw_xyz(
    struct bmm050_remapped_mag_s16_data_t *mag_data)
{
    /* variable used to return the bus communication result*/
    BMM050_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the mag XYZ and R data
    v_data_u8[0] - X LSB
    v_data_u8[1] - X MSB
    v_data_u8[2] - Y LSB
    v_data_u8[3] - Y MSB
    v_data_u8[4] - Z LSB
    v_data_u8[5] - Z MSB
    v_data_u8[6] - R LSB
    v_data_u8[7] - R MSB
    */
    u8 v_data_u8[BMM050_DATA_FRAME_SIZE] =
    {
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE,
        BMM050_INIT_VALUE, BMM050_INIT_VALUE
    };
    /* check the p_bmm050 pointer is NULL*/
    if (p_bmm050 == BMM050_NULL)
    {
        return  E_BMM050_NULL_PTR;
    }
    else
    {
        com_rslt = p_bmm050->BMM050_BUS_READ_FUNC(p_bmm050->dev_addr,
                   BMM050_REMAPPED_BMX055_DATA_Y_LSB,
                   v_data_u8, BMM050_ALL_DATA_FRAME_LENGTH);
        if (!com_rslt)
        {
            /* x data */
            v_data_u8[BMM050_XLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_XLSB_DATA],
                                    BMM050_REMAPPED_BMX055_DATA_Y_LSB_BIT);
            mag_data->datay = (s16)((((s32)
                                      ((s8)v_data_u8[BMM050_XMSB_DATA]))
                                     << BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                    | v_data_u8[BMM050_XLSB_DATA]);
            /* y data */
            v_data_u8[BMM050_YLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_YLSB_DATA],
                                    BMM050_REMAPPED_BMX055_DATA_X_LSB_BIT);
            mag_data->datax = (s16)((((s32)
                                      ((s8)v_data_u8[BMM050_YMSB_DATA]))
                                     << BMM050_SHIFT_BIT_POSITION_BY_05_BITS)
                                    | v_data_u8[BMM050_YLSB_DATA]);
            mag_data->datax = -mag_data->datax;
            /* z data */
            v_data_u8[BMM050_ZLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_ZLSB_DATA],
                                    BMM050_DATA_Z_LSB_BIT);
            mag_data->dataz = (s16)((((s32)
                                      ((s8)v_data_u8[BMM050_ZMSB_DATA]))
                                     << BMM050_SHIFT_BIT_POSITION_BY_07_BITS)
                                    | v_data_u8[BMM050_ZLSB_DATA]);


            /* read the data ready status*/
            mag_data->data_ready = BMM050_GET_BITSLICE(
                                       v_data_u8[BMM050_RLSB_DATA],
                                       BMM050_DATA_RDYSTAT);


            /* r data */
            v_data_u8[BMM050_RLSB_DATA] =
                BMM050_GET_BITSLICE(v_data_u8[BMM050_RLSB_DATA],
                                    BMM050_DATA_R_LSB_BIT);
            mag_data->resistance = (u16)((((u32)
                                           v_data_u8[BMM050_RMSB_DATA]) <<
                                          BMM050_SHIFT_BIT_POSITION_BY_06_BITS)
                                         | v_data_u8[BMM050_RLSB_DATA]);
        }
    }
    return com_rslt;
}
