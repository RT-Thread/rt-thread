/*!
****************************************************************************
* Copyright (C) 2015 - 2016 Bosch Sensortec GmbH
*
* bma2x2.c
* Date: 2016/11/14
* Revision: 2.0.7 $
*
* Usage: Sensor Driver for BMA2x2 sensor
*
****************************************************************************
* Disclaimer
*
* Common:
* Bosch Sensortec products are developed for the consumer goods industry.
* They may only be used within the parameters of the respective valid
* product data sheet.  Bosch Sensortec products are provided with the
* express understanding that there is no warranty of fitness for a
* particular purpose.They are not fit for use in life-sustaining,
* safety or security sensitive systems or any system or device
* that may lead to bodily harm or property damage if the system
* or device malfunctions. In addition,Bosch Sensortec products are
* not fit for use in products which interact with motor vehicle systems.
* The resale and or use of products are at the purchasers own risk and
* his own responsibility. The examination of fitness for the intended use
* is the sole responsibility of the Purchaser.
*
* The purchaser shall indemnify Bosch Sensortec from all third party
* claims, including any claims for incidental, or consequential damages,
* arising from any product use not covered by the parameters of
* the respective valid product data sheet or not approved by
* Bosch Sensortec and reimburse Bosch Sensortec for all costs in
* connection with such claims.
*
* The purchaser must monitor the market for the purchased products,
* particularly with regard to product safety and inform Bosch Sensortec
* without delay of all security relevant incidents.
*
* Engineering Samples are marked with an asterisk (*) or (e).
* Samples may vary from the valid technical specifications of the product
* series. They are therefore not intended or fit for resale to third
* parties or for use in end products. Their sole purpose is internal
* client testing. The testing of an engineering sample may in no way
* replace the testing of a product series. Bosch Sensortec assumes
* no liability for the use of engineering samples.
* By accepting the engineering samples, the Purchaser agrees to indemnify
* Bosch Sensortec from all claims arising from the use of engineering
* samples.
*
* Special:
* This software module (hereinafter called "Software") and any information
* on application-sheets (hereinafter called "Information") is provided
* free of charge for the sole purpose to support your application work.
* The Software and Information is subject to the following
* terms and conditions:
*
* The Software is specifically designed for the exclusive use for
* Bosch Sensortec products by personnel who have special experience
* and training. Do not use this Software if you do not have the
* proper experience or training.
*
* This Software package is provided `` as is `` and without any expressed
* or implied warranties,including without limitation, the implied warranties
* of merchantability and fitness for a particular purpose.
*
* Bosch Sensortec and their representatives and agents deny any liability
* for the functional impairment
* of this Software in terms of fitness, performance and safety.
* Bosch Sensortec and their representatives and agents shall not be liable
* for any direct or indirect damages or injury, except as
* otherwise stipulated in mandatory applicable law.
*
* The Information provided is believed to be accurate and reliable.
* Bosch Sensortec assumes no responsibility for the consequences of use
* of such Information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of Bosch. Specifications mentioned in the Information are
* subject to change without notice.
**************************************************************************/
/*! file <BMA2x2 >
    brief <Sensor driver for BMA2x2> */
#include "bma2x2.h"
/*! user defined code to be added here ... */
static struct bma2x2_t *p_bma2x2;
/*! Based on Bit resolution value_u8 should be modified */
//u8 V_BMA2x2RESOLUTION_U8 = BMA2x2_14_RESOLUTION;
u8 V_BMA2x2RESOLUTION_U8 = BMA2x2_12_RESOLUTION;

/****************************************************************************/
/*! Static Function Declarations
*****************************************************************************/
/*!
 *  @brief This API computes the number of bytes of accel FIFO data
 *  which is to be parsed.
 *
 *  @param[out] data_index       : The start index for parsing data
 *  @param[out] data_read_length : No of bytes to be parsed from FIFO buffer
 *  @param[in] accel_frame_count : Number of accelerometer frames to be read
 *  @param[in] fifo_data_select  : Denoting enabled axes data stored in FIFO
 *  @param[in] fifo_conf         : FIFO configuration structure
 *
 */
static void get_accel_len_to_parse(u8 *data_index, u8 *data_read_length,
                                   u8 accel_frame_count, u8 fifo_data_select,
                                   struct fifo_configuration *fifo_conf);

/*!
 *  @brief This API is used to parse the accelerometer frame from the
 *  user defined FIFO data buffer mapped to the structure fifo_conf and store
 *  it in the union fifo_frame
 *
 *  @note It update the data_index value which is used to store the index of
 *  the current data byte which is parsed.
 *
 *  @note The parsed accel frames stored in the union fifo_conf contains data
 *  in accordance with the enabled data axes to be stored in FIFO
 *  (XYZ axes or individual axis)
 *
 *  @param[in,out] accel_frame  : Instance of union fifo_frame
 *  @param[in,out] data_index   : Index value of noumber of bytes parsed
 *  @param[in,out] accel_index  : Index value of accelerometer frame parsed
 *  @param[in] fifo_data_select : Denoting enabled axes data stored in FIFO
 *  @param[in] fifo_conf        : FIFO configuration structure
 *
 */
static void unpack_accel_frame(union fifo_frame *accel_frame, u8 *data_index,
                               u8 *accel_index, u8 fifo_data_select,
                               struct fifo_configuration *fifo_conf);

/*!
 *  @brief This API is used to parse the accelerometer data and
 *  store it in the union fifo_frame
 *  It also updates the data_index value which stores the index of
 *  the current data byte which is parsed
 *
 *  @param[in,out] accel_frame  : Instance of union fifo_frame
 *  @param[in,out] data_index   : Index value of noumber of bytes parsed
 *  @param[in] fifo_conf        : FIFO configuration structure
 *
 */
static void unpack_accel_xyz(union fifo_frame *accel_frame, u8 *data_index,
                             struct fifo_configuration *fifo_conf);
/*!
 * @brief
 *  This API reads the data from
 *  the given register continuously
 *
 *
 *  @param addr_u8 -> Address of the register
 *  @param data_u8 -> The data from the register
 *  @param len_u32 -> no of bytes to read
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_burst_read(u8 addr_u8,
        u8 *data_u8, u32 len_u32)
{
    /* Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the data from the register*/
        com_rslt = p_bma2x2->BMA2x2_BURST_READ_FUNC
                   (p_bma2x2->dev_addr, addr_u8, data_u8, len_u32);
    }
    return com_rslt;
}
/*!
 *  @brief
 *  This function is used for initialize
 *  bus read and bus write functions
 *  assign the chip id and device address
 *  chip id is read in the register 0x00 bit from 0 to 7
 *
 *  @param bma2x2 : structure pointer
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *  @note
 *  While changing the parameter of the bma2x2_t
 *  consider the following point:
 *  Changing the reference value of the parameter
 *  will changes the local copy or local reference
 *  make sure your changes will not
 *  affect the reference value of the parameter
 *  (Better case don't change the reference value of the parameter)
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_init(struct bma2x2_t *bma2x2)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 config_data_u8 = BMA2x2_INIT_VALUE;
    /* assign bma2x2 ptr */
    p_bma2x2 = bma2x2;
    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read Chip Id */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_CHIP_ID_REG, &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        p_bma2x2->chip_id = data_u8;    /* get bit slice */
        /* read the fifo config register and update
        the value to the fifo_config*/
        com_rslt += bma2x2_read_reg(BMA2x2_FIFO_MODE_REG,
                                    &config_data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        p_bma2x2->fifo_config = config_data_u8;
    }
    return com_rslt;
}
/*!
 * @brief
 *  This API gives data to the given register and
 *  the data is written in the corresponding register address
 *
 *
 *  @param adr_u8  -> Address of the register
 *  @param data_u8 -> The data to the register
 *  @param len_u8 -> no of bytes to read
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_write_reg(u8 adr_u8,
        u8 *data_u8, u8 len_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Write the data to the register*/
        com_rslt = p_bma2x2->BMA2x2_BUS_WRITE_FUNC
                   (p_bma2x2->dev_addr, adr_u8, data_u8, len_u8);

        if (p_bma2x2->power_mode_u8 != BMA2x2_MODE_NORMAL)
        {
            /*A minimum interface idle time delay
            of atleast 450us is required as per the data sheet.*/
            p_bma2x2->delay_msec(BMA2x2_INTERFACE_IDLE_TIME_DELAY);
        }
    }
    return com_rslt;
}
/*!
 * @brief This API reads the data from
 *           the given register address
 *
 *
 *  @param adr_u8 -> Address of the register
 *  @param data_u8 -> The data from the register
 *  @param len_u8 -> no of bytes to read
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_reg(u8 adr_u8,
        u8 *data_u8, u8 len_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /*Read the data from the register*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, adr_u8, data_u8, len_u8);
    }
    return com_rslt;
}
/*!
 * @brief
 *  This API reads acceleration data X values
 *  from location 02h and 03h
 *
 *
 *  @param   accel_x_s16 : pointer holding the data of accel X
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_x(s16 *accel_x_s16)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the accel x value
    data_u8[0] - x->LSB
    data_u8[1] - x->MSB
    */
    u8  data_u8[BMA2x2_ACCEL_DATA_SIZE] =
    {
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE
    };
    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (V_BMA2x2RESOLUTION_U8)
        {
        /* This case used for the resolution bit 12*/
        case BMA2x2_12_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_X12_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_x_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB] &
                                  BMA2x2_RESOLUTION_12_MASK));
            *accel_x_s16 = *accel_x_s16 >>
                           BMA2x2_SHIFT_FOUR_BITS;
            break;
        /* This case used for the resolution bit 10*/
        case BMA2x2_10_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_X10_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_x_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB] &
                                  BMA2x2_RESOLUTION_10_MASK));
            *accel_x_s16 = *accel_x_s16 >>
                           BMA2x2_SHIFT_SIX_BITS;
            break;
        /* This case used for the resolution bit 14*/
        case BMA2x2_14_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_X14_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_x_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB] &
                                  BMA2x2_RESOLUTION_14_MASK));
            *accel_x_s16 = *accel_x_s16 >>
                           BMA2x2_SHIFT_TWO_BITS;
            break;
        default:
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief
 *  This API reads acceleration data X values
 *  from location 02h and 03h bit resolution support 8bit
 *
 *
 *  @param   accel_x_s8 : pointer holding the data of accel X
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_x(
    s8 *accel_x_s8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8  data = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the sensor X data*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_X_AXIS_MSB_ADDR, &data,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *accel_x_s8 = BMA2x2_GET_BITSLICE(data,
                                          BMA2x2_ACCEL_X_MSB);
    }
    return com_rslt;
}
/*!
 * @brief
 *  This API reads acceleration data Y values
 *  from location 04h and 05h
 *
 *  @param   accel_y_s16 : pointer holding the data of accel Y
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_y(s16 *accel_y_s16)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the accel y value
    data_u8[0] - y->LSB
    data_u8[1] - y->MSB
    */
    u8 data_u8[BMA2x2_ACCEL_DATA_SIZE] = {BMA2x2_INIT_VALUE,
                                          BMA2x2_INIT_VALUE
                                         };

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (V_BMA2x2RESOLUTION_U8)
        {
        /* This case used for the resolution bit 12*/
        case BMA2x2_12_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_Y12_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_y_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB] &
                                  BMA2x2_12_BIT_SHIFT));
            *accel_y_s16 = *accel_y_s16 >>
                           BMA2x2_SHIFT_FOUR_BITS;
            break;
        /* This case used for the resolution bit 10*/
        case BMA2x2_10_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_Y10_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_y_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB] &
                                  BMA2x2_10_BIT_SHIFT));
            *accel_y_s16 = *accel_y_s16 >>
                           BMA2x2_SHIFT_SIX_BITS;
            break;
        /* This case used for the resolution bit 14*/
        case BMA2x2_14_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_Y14_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_y_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB] &
                                  BMA2x2_14_BIT_SHIFT));
            *accel_y_s16 = *accel_y_s16 >>
                           BMA2x2_SHIFT_TWO_BITS;
            break;
        default:
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API reads acceleration data Y values of
 * 8bit  resolution  from location 05h
 *
 *
 *
 *
 *  @param accel_y_s8   The data of y
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_y(
    s8 *accel_y_s8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8  data = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_Y_AXIS_MSB_ADDR, &data,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *accel_y_s8 = BMA2x2_GET_BITSLICE(data,
                                          BMA2x2_ACCEL_Y_MSB);
    }
    return com_rslt;
}
/*!
 * @brief This API reads acceleration data Z values
 *                          from location 06h and 07h
 *
 *
 *  @param   accel_z_s16 : pointer holding the data of accel Z
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_z(s16 *accel_z_s16)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the accel z value
    data_u8[0] - z->LSB
    data_u8[1] - z->MSB
    */
    u8 data_u8[BMA2x2_ACCEL_DATA_SIZE] = {BMA2x2_INIT_VALUE,
                                          BMA2x2_INIT_VALUE
                                         };

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (V_BMA2x2RESOLUTION_U8)
        {
        case BMA2x2_12_RESOLUTION:
            /* This case used for the resolution bit 12*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_Z12_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_z_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB]
                                  & BMA2x2_12_BIT_SHIFT));
            *accel_z_s16 = *accel_z_s16 >>
                           BMA2x2_SHIFT_FOUR_BITS;
            break;
        /* This case used for the resolution bit 10*/
        case BMA2x2_10_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_Z10_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_z_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB]
                                  & BMA2x2_10_BIT_SHIFT));
            *accel_z_s16 = *accel_z_s16 >>
                           BMA2x2_SHIFT_SIX_BITS;
            break;
        /* This case used for the resolution bit 14*/
        case BMA2x2_14_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ACCEL_Z14_LSB_REG, data_u8,
                        BMA2x2_LSB_MSB_READ_LENGTH);
            *accel_z_s16 = (s16)((((s32)((s8)
                                         data_u8[BMA2x2_SENSOR_DATA_ACCEL_MSB]))
                                  << BMA2x2_SHIFT_EIGHT_BITS) |
                                 (data_u8[BMA2x2_SENSOR_DATA_ACCEL_LSB]
                                  & BMA2x2_14_BIT_SHIFT));
            *accel_z_s16 = *accel_z_s16 >>
                           BMA2x2_SHIFT_TWO_BITS;
            break;
        default:
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief
 *  This API reads acceleration data Z values of
 *  8bit  resolution  from location 07h
 *
 *
 *
 *
 *  \@aram  accel_z_s8 : the data of z
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_z(
    s8 *accel_z_s8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8  data = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_Z_AXIS_MSB_ADDR, &data,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *accel_z_s8 = BMA2x2_GET_BITSLICE(data,
                                          BMA2x2_ACCEL_Z_MSB);
    }
    return com_rslt;
}
/*!
 *  @brief This API reads acceleration data X,Y,Z values
 *  from location 02h to 07h
 *
 *  @param accel : pointer holding the data of accel
 *             value       |   resolution
 *       ----------------- | --------------
 *              0          | BMA2x2_12_RESOLUTION
 *              1          | BMA2x2_10_RESOLUTION
 *              2          | BMA2x2_14_RESOLUTION
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_xyz(
    struct bma2x2_accel_data *accel)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    /* Array holding the accel xyz value
    data_u8[0] - x->LSB
    data_u8[1] - x->MSB
    data_u8[2] - y->MSB
    data_u8[3] - y->MSB
    data_u8[4] - z->MSB
    data_u8[5] - z->MSB
    */
    u8 data_u8[BMA2x2_ACCEL_XYZ_DATA_SIZE] =
    {
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE,
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE,
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE
    };

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (V_BMA2x2RESOLUTION_U8)
        {
        /* This case used for the resolution bit 12*/
        case BMA2x2_12_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_ACCEL_X12_LSB_REG,
                        data_u8, BMA2x2_SHIFT_SIX_BITS);
            /* read the x data_u8*/
            accel->x = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_X_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_X_LSB] &
                              BMA2x2_12_BIT_SHIFT));
            accel->x = accel->x >> BMA2x2_SHIFT_FOUR_BITS;

            /* read the y data_u8*/
            accel->y = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_LSB] &
                              BMA2x2_12_BIT_SHIFT));
            accel->y = accel->y >> BMA2x2_SHIFT_FOUR_BITS;

            /* read the z data_u8*/
            accel->z = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_LSB] &
                              BMA2x2_12_BIT_SHIFT));
            accel->z = accel->z >> BMA2x2_SHIFT_FOUR_BITS;

            break;
        case BMA2x2_10_RESOLUTION:
            /* This case used for the resolution bit 10*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_ACCEL_X10_LSB_REG,
                        data_u8, BMA2x2_SHIFT_SIX_BITS);
            /* read the x data_u8*/
            accel->x = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_X_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_X_LSB] &
                              BMA2x2_10_BIT_SHIFT));
            accel->x = accel->x >> BMA2x2_SHIFT_SIX_BITS;

            /* read the y data_u8*/
            accel->y = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_LSB] &
                              BMA2x2_10_BIT_SHIFT));
            accel->y = accel->y >> BMA2x2_SHIFT_SIX_BITS;

            /* read the z data_u8*/
            accel->z = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_LSB]
                              & BMA2x2_10_BIT_SHIFT));
            accel->z = accel->z >> BMA2x2_SHIFT_SIX_BITS;
            break;
        /* This case used for the resolution bit 14*/
        case BMA2x2_14_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_ACCEL_X14_LSB_REG,
                        data_u8, BMA2x2_SHIFT_SIX_BITS);

            /* read the x data_u8*/
            accel->x = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_X_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_X_LSB]
                              & BMA2x2_14_BIT_SHIFT));
            accel->x = accel->x >> BMA2x2_SHIFT_TWO_BITS;

            /* read the y data_u8*/
            accel->y = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_LSB]
                              & BMA2x2_14_BIT_SHIFT));
            accel->y = accel->y >> BMA2x2_SHIFT_TWO_BITS;

            /* read the z data_u8*/
            accel->z = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_LSB]
                              & BMA2x2_14_BIT_SHIFT));
            accel->z = accel->z >> BMA2x2_SHIFT_TWO_BITS;
            break;
        default:
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API reads acceleration of 8 bit resolution
 * data of X,Y,Z values
 * from location 03h , 05h and 07h
 *
 *
 *
 *
 *  @param accel : pointer holding the data of accel
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_xyz(
    struct bma2x2_accel_eight_resolution *accel)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8  data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_X_AXIS_MSB_ADDR, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->x = BMA2x2_GET_BITSLICE(data_u8,
                                       BMA2x2_ACCEL_X_MSB);

        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_Y_AXIS_MSB_ADDR, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->y = BMA2x2_GET_BITSLICE(data_u8,
                                       BMA2x2_ACCEL_Y_MSB);

        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_Z_AXIS_MSB_ADDR, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->z = BMA2x2_GET_BITSLICE(data_u8,
                                       BMA2x2_ACCEL_Z_MSB);
    }
    return com_rslt;
}
/*!
 *  @brief This API read tap-sign, tap-first-xyz
 *  slope-sign, slope-first-xyz status register byte
 *  from location 0Bh
 *
 *   @param stat_tap_u8 : The status of tap and slope
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_tap_stat(
    u8 *stat_tap_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the interrupt status register 0x0B*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_STAT_TAP_SLOPE_ADDR,
                    stat_tap_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API read orient, high-sign and high-first-xyz
 *  status register byte from location 0Ch
 *
 *
 *  @param stat_orient_u8 : The status of orient and high
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_orient_stat(
    u8 *stat_orient_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the interrupt status register 0x0C*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_STAT_ORIENT_HIGH_ADDR,
                    stat_orient_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API reads fifo overrun and fifo frame counter
 *  status register byte  from location 0Eh
 *
 *  @param stat_fifo_u8 : The status of fifo overrun and frame counter
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_stat(
    u8 *stat_fifo_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the interrupt status register 0x0E*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_STAT_FIFO_ADDR,
                       stat_fifo_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API read fifo frame count
 *  from location 0Eh bit position 0 to 6
 *
 *
 * @param frame_count_u8 : The status of fifo frame count
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_frame_count(
    u8 *frame_count_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the FIFO frame count*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_FIFO_FRAME_COUNT_STAT_REG,
                       &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *frame_count_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                              BMA2x2_FIFO_FRAME_COUNT_STAT);
    }
    return com_rslt;
}
/*!
 *  @brief This API read fifo overrun
 *  from location 0Eh bit position 7
 *
 *
 * @param fifo_overrun_u8 : The status of fifo overrun
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_overrun(
    u8 *fifo_overrun_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the status of fifo over run*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_FIFO_OVERRUN_STAT_REG,
                       &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *fifo_overrun_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                               BMA2x2_FIFO_OVERRUN_STAT);
    }
    return com_rslt;
}
/*!
 *  @brief This API read interrupt status of flat, orient, single tap,
 *  double tap, slow no motion, slope, highg and lowg from location 09h
 *
 *
 *
 *  @param  intr_stat_u8 : The value of interrupt status
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_stat(
    u8 *intr_stat_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the interrupt status register 0x09*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_STAT1_ADDR, intr_stat_u8,
                       BMA2x2_SHIFT_FOUR_BITS);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get the ranges(g values) of the sensor
 *  in the register 0x0F bit from 0 to 3
 *
 *
 *  @param range_u8 : The value of range
 *        range_u8       |   result
 *       ----------------- | --------------
 *              0x03       | BMA2x2_RANGE_2G
 *              0x05       | BMA2x2_RANGE_4G
 *              0x08       | BMA2x2_RANGE_8G
 *              0x0C       | BMA2x2_RANGE_16G
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_range(u8 *range_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the range register 0x0F*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(p_bma2x2->dev_addr,
                   BMA2x2_RANGE_SELECT_REG, &data_u8,
                   BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_GET_BITSLICE(data_u8, BMA2x2_RANGE_SELECT);
        *range_u8 = data_u8;
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set the ranges(g values) of the sensor
 *  in the register 0x0F bit from 0 to 3
 *
 *
 *  @param range_u8 : The value of range
 *        range_u8 |   result
 *       ----------------- | --------------
 *              0x03       | BMA2x2_RANGE_2G
 *              0x05       | BMA2x2_RANGE_4G
 *              0x08       | BMA2x2_RANGE_8G
 *              0x0C       | BMA2x2_RANGE_16G
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_range(u8 range_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if ((range_u8 == BMA2x2_RANGE_2G) ||
                (range_u8 == BMA2x2_RANGE_4G) ||
                (range_u8 == BMA2x2_RANGE_8G) ||
                (range_u8 == BMA2x2_RANGE_16G))
        {
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_RANGE_SELECT_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            switch (range_u8)
            {
            case BMA2x2_RANGE_2G:
                data_u8  = BMA2x2_SET_BITSLICE(data_u8,
                                               BMA2x2_RANGE_SELECT,
                                               BMA2x2_RANGE_2G);
                break;
            case BMA2x2_RANGE_4G:
                data_u8  = BMA2x2_SET_BITSLICE(data_u8,
                                               BMA2x2_RANGE_SELECT,
                                               BMA2x2_RANGE_4G);
                break;
            case BMA2x2_RANGE_8G:
                data_u8  = BMA2x2_SET_BITSLICE(data_u8,
                                               BMA2x2_RANGE_SELECT,
                                               BMA2x2_RANGE_8G);
                break;
            case BMA2x2_RANGE_16G:
                data_u8  = BMA2x2_SET_BITSLICE(data_u8,
                                               BMA2x2_RANGE_SELECT,
                                               BMA2x2_RANGE_16G);
                break;
            default:
                break;
            }
            /* Write the range register 0x0F*/
            com_rslt += bma2x2_write_reg(BMA2x2_RANGE_SELECT_REG,
                                         &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get the bandwidth of the sensor in the register
 *  0x10 bit from 0 to 4
 *
 *
 *  @param bw_u8 : The value of bandwidth
 *          bw_u8          |   result
 *       ----------------- | --------------
 *              0x08       | BMA2x2_BW_7_81HZ
 *              0x09       | BMA2x2_BW_15_63HZ
 *              0x0A       | BMA2x2_BW_31_25HZ
 *              0x0B       | BMA2x2_BW_62_50HZ
 *              0x0C       | BMA2x2_BW_125HZ
 *              0x0D       | BMA2x2_BW_250HZ
 *              0x0E       | BMA2x2_BW_500HZ
 *              0x0F       | BMA2x2_BW_1000HZ
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_bw(u8 *bw_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the bandwidth register 0x10*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_BW_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_GET_BITSLICE(data_u8, BMA2x2_BW);
        *bw_u8 = data_u8;
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set the bandwidth of the sensor
 *      in the register
 *  0x10 bit from 0 to 4
 *
 *
 *  @param bw_u8 : The value of bandwidth
 *        bw_u8          |   result
 *       ----------------- | --------------
 *              0x08       | BMA2x2_BW_7_81HZ
 *              0x09       | BMA2x2_BW_15_63HZ
 *              0x0A       | BMA2x2_BW_31_25HZ
 *              0x0B       | BMA2x2_BW_62_50HZ
 *              0x0C       | BMA2x2_BW_125HZ
 *              0x0D       | BMA2x2_BW_250HZ
 *              0x0E       | BMA2x2_BW_500HZ
 *              0x0F       | BMA2x2_BW_1000HZ
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_bw(u8 bw_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 data_bw_u8 = BMA2x2_INIT_VALUE;
    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Check the chip id 0xFB, it support upto 500Hz*/
        if (p_bma2x2->chip_id == BANDWIDTH_DEFINE)
        {
            if (bw_u8 > BMA2x2_ACCEL_BW_MIN_RANGE &&
                    bw_u8 < BMA2x2_ACCEL_BW_1000HZ_RANGE)
            {
                switch (bw_u8)
                {
                case BMA2x2_BW_7_81HZ:
                    data_bw_u8 = BMA2x2_BW_7_81HZ;

                    /*  7.81 Hz      64000 uS   */
                    break;
                case BMA2x2_BW_15_63HZ:
                    data_bw_u8 = BMA2x2_BW_15_63HZ;

                    /*  15.63 Hz     32000 uS   */
                    break;
                case BMA2x2_BW_31_25HZ:
                    data_bw_u8 = BMA2x2_BW_31_25HZ;

                    /*  31.25 Hz     16000 uS   */
                    break;
                case BMA2x2_BW_62_50HZ:
                    data_bw_u8 = BMA2x2_BW_62_50HZ;

                    /*  62.50 Hz     8000 uS   */
                    break;
                case BMA2x2_BW_125HZ:
                    data_bw_u8 = BMA2x2_BW_125HZ;

                    /*  125 Hz       4000 uS   */
                    break;
                case BMA2x2_BW_250HZ:
                    data_bw_u8 = BMA2x2_BW_250HZ;

                    /*  250 Hz       2000 uS   */
                    break;
                case BMA2x2_BW_500HZ:
                    data_bw_u8 = BMA2x2_BW_500HZ;

                    /*  500 Hz       1000 uS   */
                    break;
                default:
                    break;
                }
                /* Write the bandwidth register */
                com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                           (p_bma2x2->dev_addr,
                            BMA2x2_BW_REG, &data_u8,
                            BMA2x2_GEN_READ_WRITE_LENGTH);
                data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                              BMA2x2_BW, data_bw_u8);
                com_rslt += bma2x2_write_reg
                            (BMA2x2_BW_REG, &data_u8,
                             BMA2x2_GEN_READ_WRITE_LENGTH);
            }
            else
            {
                com_rslt = E_OUT_OF_RANGE;
            }
        }
        else
        {
            if (bw_u8 > BMA2x2_ACCEL_BW_MIN_RANGE &&
                    bw_u8 < BMA2x2_ACCEL_BW_MAX_RANGE)
            {
                switch (bw_u8)
                {
                case BMA2x2_BW_7_81HZ:
                    data_bw_u8 = BMA2x2_BW_7_81HZ;

                    /*  7.81 Hz      64000 uS   */
                    break;
                case BMA2x2_BW_15_63HZ:
                    data_bw_u8 = BMA2x2_BW_15_63HZ;

                    /*  15.63 Hz     32000 uS   */
                    break;
                case BMA2x2_BW_31_25HZ:
                    data_bw_u8 = BMA2x2_BW_31_25HZ;

                    /*  31.25 Hz     16000 uS   */
                    break;
                case BMA2x2_BW_62_50HZ:
                    data_bw_u8 = BMA2x2_BW_62_50HZ;

                    /*  62.50 Hz     8000 uS   */
                    break;
                case BMA2x2_BW_125HZ:
                    data_bw_u8 = BMA2x2_BW_125HZ;

                    /*  125 Hz       4000 uS   */
                    break;
                case BMA2x2_BW_250HZ:
                    data_bw_u8 = BMA2x2_BW_250HZ;

                    /*  250 Hz       2000 uS   */
                    break;
                case BMA2x2_BW_500HZ:
                    data_bw_u8 = BMA2x2_BW_500HZ;

                    /*!  500 Hz       1000 uS   */
                    break;
                case BMA2x2_BW_1000HZ:
                    data_bw_u8 = BMA2x2_BW_1000HZ;

                    /*  1000 Hz      500 uS   */
                    break;
                default:
                    break;
                }
                /* Write the bandwidth register */
                com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                           (p_bma2x2->dev_addr,
                            BMA2x2_BW_REG, &data_u8,
                            BMA2x2_GEN_READ_WRITE_LENGTH);
                data_u8 = BMA2x2_SET_BITSLICE
                          (data_u8, BMA2x2_BW, data_bw_u8);
                com_rslt += bma2x2_write_reg(
                                BMA2x2_BW_REG, &data_u8,
                                BMA2x2_GEN_READ_WRITE_LENGTH);
            }
            else
            {
                com_rslt = E_OUT_OF_RANGE;
            }
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get the operating
 *  modes of the sensor in the register 0x11 and 0x12
 *  @note Register 0x11 - bit from 5 to 7
 *  @note Register 0x12 - bit from 5 and 6
 *
 *
 *  @param power_mode_u8 : The value of power mode
 *  power_mode_u8           |value  |   0x11  |   0x12
 *  ------------------------- |-------| --------|--------
 *  BMA2x2_MODE_NORMAL        |  0    |  0x00   |  0x00
 *  BMA2x2_MODE_LOWPOWER1     |  1    |  0x02   |  0x00
 *  BMA2x2_MODE_SUSPEND       |  2    |  0x06   |  0x00
 *  BMA2x2_MODE_DEEP_SUSPEND  |  3    |  0x01   |  0x00
 *  BMA2x2_MODE_LOWPOWER2     |  4    |  0x02   |  0x01
 *  BMA2x2_MODE_STANDBY       |  5    |  0x04   |  0x00
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_power_mode(
    u8 *power_mode_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 data2_u8 = BMA2x2_INIT_VALUE;
    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_MODE_CTRL_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        com_rslt += p_bma2x2->BMA2x2_BUS_READ_FUNC
                    (p_bma2x2->dev_addr, BMA2x2_LOW_NOISE_CTRL_ADDR,
                     &data2_u8, BMA2x2_GEN_READ_WRITE_LENGTH);

        data_u8  = (data_u8 &
                    BMA2x2_POWER_MODE_HEX_E_ZERO_MASK) >>
                   BMA2x2_SHIFT_FIVE_BITS;
        data2_u8  = (data2_u8 &
                     BMA2x2_POWER_MODE_HEX_4_ZERO_MASK) >>
                    BMA2x2_SHIFT_SIX_BITS;

        if ((data_u8 ==
                BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK) &&
                (data2_u8 ==
                 BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK))
        {
            *power_mode_u8  = BMA2x2_MODE_NORMAL;
        }
        else
        {
            if ((data_u8 ==
                    BMA2x2_POWER_MODE_HEX_ZERO_TWO_MASK) &&
                    (data2_u8 ==
                     BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK))
            {
                *power_mode_u8  =
                    BMA2x2_MODE_LOWPOWER1;
            }
            else
            {
                if ((data_u8 ==
                        BMA2x2_POWER_MODE_HEX_ZERO_FOUR_MASK
                        || data_u8 ==
                        BMA2x2_POWER_MODE_HEX_ZERO_SIX_MASK) &&
                        (data2_u8 ==
                         BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK))
                {
                    *power_mode_u8  =
                        BMA2x2_MODE_SUSPEND;
                }
                else
                {
                    if (((data_u8 &
                            BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK)
                            == BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK))
                    {
                        *power_mode_u8  =
                            BMA2x2_MODE_DEEP_SUSPEND;
                    }
                    else
                    {
                        if ((data_u8 ==
                                BMA2x2_POWER_MODE_HEX_ZERO_TWO_MASK)
                                && (data2_u8 ==
                                    BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK))
                        {
                            *power_mode_u8  =
                                BMA2x2_MODE_LOWPOWER2;
                        }
                        else
                        {
                            if ((data_u8 ==
                                    BMA2x2_POWER_MODE_HEX_ZERO_FOUR_MASK) &&
                                    (data2_u8 ==
                                     BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK))
                                *power_mode_u8  =
                                    BMA2x2_MODE_STANDBY;
                            else
                                *power_mode_u8 =
                                    BMA2x2_MODE_DEEP_SUSPEND;
                        }
                    }
                }
            }
        }
    }
    p_bma2x2->power_mode_u8 = *power_mode_u8;
    return com_rslt;
}
/*!
 *  @brief This API is used to set the operating
 *  modes of the sensor in the register 0x11 and 0x12
 *  @note Register 0x11 - bit from 5 to 7
 *  @note Register 0x12 - bit from 5 and 6
 *
 *
 *  @param power_mode_u8 : The value of power mode
 *  power_mode_u8         |value  |   0x11  |   0x12
 *  ------------------------- |-------| --------|--------
 *  BMA2x2_MODE_NORMAL        |  0    |  0x00   |  0x00
 *  BMA2x2_MODE_LOWPOWER1     |  1    |  0x02   |  0x00
 *  BMA2x2_MODE_SUSPEND       |  2    |  0x06   |  0x00
 *  BMA2x2_MODE_DEEP_SUSPEND  |  3    |  0x01   |  0x00
 *  BMA2x2_MODE_LOWPOWER2     |  4    |  0x02   |  0x01
 *  BMA2x2_MODE_STANDBY       |  5    |  0x04   |  0x00
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_power_mode(u8 power_mode_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 mode_ctr_eleven_reg = BMA2x2_INIT_VALUE;
    u8 mode_ctr_twel_reg = BMA2x2_INIT_VALUE;
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 data2_u8 = BMA2x2_INIT_VALUE;
    u8 pre_fifo_config_data = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(p_bma2x2->dev_addr,
                   BMA2x2_MODE_CTRL_REG, &data_u8, 1);
        com_rslt += p_bma2x2->BMA2x2_BUS_READ_FUNC(p_bma2x2->dev_addr,
                    BMA2x2_LOW_POWER_MODE_REG, &data2_u8, 1);

        /* write the previous FIFO mode and data select*/
        pre_fifo_config_data = p_bma2x2->fifo_config;
        pre_fifo_config_data |= 0x0C;

        com_rslt += bma2x2_set_mode_value(power_mode_u8);
        mode_ctr_eleven_reg = p_bma2x2->ctrl_mode_reg;
        mode_ctr_twel_reg =  p_bma2x2->low_mode_reg;

        /* write the power mode to the register 0x12*/
        data2_u8  = BMA2x2_SET_BITSLICE(data2_u8, BMA2x2_LOW_POWER_MODE,
                                        mode_ctr_twel_reg);
        com_rslt += bma2x2_write_reg(BMA2x2_LOW_POWER_MODE_REG,
                                     &data2_u8, 1);

        /*A minimum delay of atleast 450us is required for
        the low power modes, as per the data sheet.*/
        p_bma2x2->delay_msec(BMA2x2_INTERFACE_IDLE_TIME_DELAY);

        if (((p_bma2x2->power_mode_u8 == BMA2x2_MODE_LOWPOWER1) ||
                (p_bma2x2->power_mode_u8 == BMA2x2_MODE_LOWPOWER2)) &&
                (power_mode_u8 == BMA2x2_MODE_NORMAL))
        {
            /* Enter the power mode to suspend*/
            data_u8  = BMA2x2_SET_BITSLICE(data_u8,
                                           BMA2x2_MODE_CTRL, BMA2x2_SHIFT_FOUR_BITS);
            /* write the power mode to suspend*/
            com_rslt += bma2x2_write_reg(
                            BMA2x2_MODE_CTRL_REG, &data_u8,
                            BMA2x2_GEN_READ_WRITE_LENGTH);
            /*re-write FIFO_CONFIG_0 register*/
            com_rslt += bma2x2_write_reg(
                            BMA2x2_FIFO_MODE_REG, &pre_fifo_config_data, 1);
        }

        /* write the power mode to 0x11 register*/
        data_u8  = BMA2x2_SET_BITSLICE(data_u8, BMA2x2_MODE_CTRL,
                                       mode_ctr_eleven_reg);
        com_rslt += bma2x2_write_reg(BMA2x2_MODE_CTRL_REG, &data_u8, 1);
        /*A minimum delay of atleast 450us is required for
        the low power modes, as per the data sheet.*/
        p_bma2x2->delay_msec(BMA2x2_INTERFACE_IDLE_TIME_DELAY);

        com_rslt += bma2x2_write_reg(BMA2x2_FIFO_MODE_REG,
                                     &pre_fifo_config_data, 1);

        /*Assigning the power mode to the global variable*/
        p_bma2x2->power_mode_u8 = power_mode_u8;
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to assign the power mode values
 *  modes of the sensor in the register 0x11 and 0x12
 *  @note Register 0x11 - bit from 5 to 7
 *  @note Register 0x12 - bit from 5 and 6
 *
 *
 *  @param power_mode_u8 : The value of power mode
 *  power_mode_u8           |value  |   0x11  |   0x12
 *  ------------------------- |-------| --------|--------
 *  BMA2x2_MODE_NORMAL        |  0    |  0x00   |  0x00
 *  BMA2x2_MODE_LOWPOWER1     |  1    |  0x02   |  0x00
 *  BMA2x2_MODE_SUSPEND       |  2    |  0x06   |  0x00
 *  BMA2x2_MODE_DEEP_SUSPEND  |  3    |  0x01   |  0x00
 *  BMA2x2_MODE_LOWPOWER2     |  4    |  0x02   |  0x01
 *  BMA2x2_MODE_STANDBY       |  5    |  0x04   |  0x00
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_mode_value(u8 power_mode_u8)
{
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = SUCCESS;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (power_mode_u8 < BMA2x2_POWER_MODE_RANGE)
        {
            switch (power_mode_u8)
            {
            case BMA2x2_MODE_NORMAL:
                p_bma2x2->ctrl_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK;
                p_bma2x2->low_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK;
                break;
            case BMA2x2_MODE_LOWPOWER1:
                p_bma2x2->ctrl_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_TWO_MASK;
                p_bma2x2->low_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK;
                break;
            case BMA2x2_MODE_LOWPOWER2:
                p_bma2x2->ctrl_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_TWO_MASK;
                p_bma2x2->low_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK;
                break;
            case BMA2x2_MODE_SUSPEND:
                p_bma2x2->ctrl_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_FOUR_MASK;
                p_bma2x2->low_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ZERO_MASK;
                break;
            case BMA2x2_MODE_STANDBY:
                p_bma2x2->ctrl_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_FOUR_MASK;
                p_bma2x2->low_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK;
                break;
            case BMA2x2_MODE_DEEP_SUSPEND:
                p_bma2x2->ctrl_mode_reg =
                    BMA2x2_POWER_MODE_HEX_ZERO_ONE_MASK;
                break;
            }
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the sleep duration of the sensor in the register 0x11
 *  Register 0x11 - bit from 0 to 3
 *
 *
 *  @param  sleep_durn_u8 : The value of sleep duration time
 *         sleep_durn_u8 |   result
 *       ----------------- | ----------------------
 *              0x05       | BMA2x2_SLEEP_DURN_0_5MS
 *              0x06       | BMA2x2_SLEEP_DURN_1MS
 *              0x07       | BMA2x2_SLEEP_DURN_2MS
 *              0x08       | BMA2x2_SLEEP_DURN_4MS
 *              0x09       | BMA2x2_SLEEP_DURN_6MS
 *              0x0A       | BMA2x2_SLEEP_DURN_10MS
 *              0x0B       | BMA2x2_SLEEP_DURN_25MS
 *              0x0C       | BMA2x2_SLEEP_DURN_50MS
 *              0x0D       | BMA2x2_SLEEP_DURN_100MS
 *              0x0E       | BMA2x2_SLEEP_DURN_500MS
 *              0x0F       | BMA2x2_SLEEP_DURN_1S
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_sleep_durn(u8 *sleep_durn_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the sleep duration */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_SLEEP_DURN_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *sleep_durn_u8 = BMA2x2_GET_BITSLICE
                         (data_u8, BMA2x2_SLEEP_DURN);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the sleep duration of the sensor in the register 0x11
 *  Register 0x11 - bit from 0 to 3
 *
 *
 *
 *
 *  @param  sleep_durn_u8 : The value of sleep duration time
 *        sleep_durn_u8  |   result
 *       ----------------- | ----------------------
 *              0x05       | BMA2x2_SLEEP_DURN_0_5MS
 *              0x06       | BMA2x2_SLEEP_DURN_1MS
 *              0x07       | BMA2x2_SLEEP_DURN_2MS
 *              0x08       | BMA2x2_SLEEP_DURN_4MS
 *              0x09       | BMA2x2_SLEEP_DURN_6MS
 *              0x0A       | BMA2x2_SLEEP_DURN_10MS
 *              0x0B       | BMA2x2_SLEEP_DURN_25MS
 *              0x0C       | BMA2x2_SLEEP_DURN_50MS
 *              0x0D       | BMA2x2_SLEEP_DURN_100MS
 *              0x0E       | BMA2x2_SLEEP_DURN_500MS
 *              0x0F       | BMA2x2_SLEEP_DURN_1S
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_sleep_durn(u8 sleep_durn_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_sleep_durn_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (sleep_durn_u8 > BMA2x2_SLEEP_DURN_MIN_RANGE &&
                sleep_durn_u8 < BMA2x2_SLEEP_DURN_MAX_RANGE)
        {
            switch (sleep_durn_u8)
            {
            case BMA2x2_SLEEP_DURN_0_5MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_0_5MS;

                /*  0.5 MS   */
                break;
            case BMA2x2_SLEEP_DURN_1MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_1MS;

                /*  1 MS  */
                break;
            case BMA2x2_SLEEP_DURN_2MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_2MS;

                /*  2 MS  */
                break;
            case BMA2x2_SLEEP_DURN_4MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_4MS;

                /*  4 MS   */
                break;
            case BMA2x2_SLEEP_DURN_6MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_6MS;

                /*  6 MS  */
                break;
            case BMA2x2_SLEEP_DURN_10MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_10MS;

                /*  10 MS  */
                break;
            case BMA2x2_SLEEP_DURN_25MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_25MS;

                /*  25 MS  */
                break;
            case BMA2x2_SLEEP_DURN_50MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_50MS;

                /*  50 MS   */
                break;
            case BMA2x2_SLEEP_DURN_100MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_100MS;

                /*  100 MS  */
                break;
            case BMA2x2_SLEEP_DURN_500MS:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_500MS;

                /*  500 MS   */
                break;
            case BMA2x2_SLEEP_DURN_1S:
                data_sleep_durn_u8 = BMA2x2_SLEEP_DURN_1S;

                /*!  1 SECS   */
                break;
            default:
                break;
            }
            /* write the sleep duration */
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_SLEEP_DURN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_SLEEP_DURN, data_sleep_durn_u8);
            com_rslt += bma2x2_write_reg(BMA2x2_SLEEP_DURN_REG,
                                         &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get the sleep timer mode
 *  in the register 0x12 bit 5
 *
 *
 *
 *
 *  @param  sleep_timer_u8 : The value of sleep timer mode
 *        sleep_timer_u8 |   result
 *       ----------------- | ----------------------
 *              0          | enable EventDrivenSampling(EDT)
 *              1          | enable Equidistant sampling mode(EST)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_sleep_timer_mode(
    u8 *sleep_timer_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /*Read the SLEEP TIMER MODE*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_SLEEP_TIMER_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *sleep_timer_u8 = BMA2x2_GET_BITSLICE
                          (data_u8, BMA2x2_SLEEP_TIMER);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set the sleep timer mode
 *  in the register 0x12 bit 5
 *
 *
 *
 *
 *  @param  sleep_timer_u8 : The value of sleep timer mode
 *        sleep_timer_u8 |   result
 *       ----------------- | ----------------------
 *              0          | enable EventDrivenSampling(EDT)
 *              1          | enable Equidistant sampling mode(EST)
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_sleep_timer_mode(u8 sleep_timer_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (sleep_timer_u8 < BMA2x2_SLEEP_TIMER_MODE_RANGE)
        {
            /* write the SLEEP TIMER MODE*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_SLEEP_TIMER_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_SLEEP_TIMER, sleep_timer_u8);
            com_rslt += bma2x2_write_reg(BMA2x2_SLEEP_TIMER_REG,
                                         &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get high bandwidth
 *      in the register 0x13 bit 7
 *
 *  @param  high_bw_u8 : The value of high bandwidth
 *         high_bw_u8    |   result
 *       ----------------- | ----------------------
 *              0          | Unfiltered High Bandwidth
 *              1          | Filtered Low Bandwidth
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_high_bw(u8 *high_bw_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        return  E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the high bandwidth*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_ENABLE_DATA_HIGH_BW_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *high_bw_u8 = BMA2x2_GET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_DATA_HIGH_BW);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to write high bandwidth
 *      in the register 0x13 bit 7
 *
 *  @param  high_bw_u8 : The value of high bandwidth
 *         high_bw_u8    |   result
 *       ----------------- | ----------------------
 *              0          | Unfiltered High Bandwidth
 *              1          | Filtered Low Bandwidth
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_high_bw(u8 high_bw_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        return  E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Write the high bandwidth*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_ENABLE_DATA_HIGH_BW_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_ENABLE_DATA_HIGH_BW, high_bw_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_ENABLE_DATA_HIGH_BW_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get shadow dis
 *  in the register 0x13 bit 6
 *
 *  @param  shadow_dis_u8 : The value of shadow dis
 *        shadow_dis_u8  |   result
 *       ----------------- | ------------------
 *              0          | MSB is Locked
 *              1          | No MSB Locking
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_shadow_dis(u8 *shadow_dis_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        return  E_BMA2x2_NULL_PTR;
    }
    else
    {
        /*Read the shadow dis*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_DIS_SHADOW_PROC_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *shadow_dis_u8 = BMA2x2_GET_BITSLICE
                         (data_u8, BMA2x2_DIS_SHADOW_PROC);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set shadow dis
 *  in the register 0x13 bit 6
 *
 *  @param  shadow_dis_u8 : The value of shadow dis
 *        shadow_dis_u8  |   result
 *       ----------------- | ------------------
 *              0          | MSB is Locked
 *              1          | No MSB Locking
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_shadow_dis(u8 shadow_dis_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        return  E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Write the shadow dis*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_DIS_SHADOW_PROC_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_DIS_SHADOW_PROC, shadow_dis_u8);
        com_rslt += bma2x2_write_reg(BMA2x2_DIS_SHADOW_PROC_REG,
                                     &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This function is used for the soft reset
 *  The soft reset register will be written
 *  with 0xB6 in the register 0x14.
 *
 *
 *
 *  \param : None
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_soft_rst(void)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_ENABLE_SOFT_RESET_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /*! To reset the sensor
        0xB6 value_u8 will be written */
        com_rslt = bma2x2_write_reg(BMA2x2_RST_ADDR,
                                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to update the register values
 *
 *
 *
 *
 *  @param : None
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_update_image(void)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        return  E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Write the update image*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_UPDATE_IMAGE_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_UPDATE_IMAGE,
                   BMA2x2_GEN_READ_WRITE_LENGTH);
        com_rslt += bma2x2_write_reg(BMA2x2_UPDATE_IMAGE_REG,
                                     &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  interrupt enable bits of the sensor in the registers 0x16 and 0x17
 *  @note It reads the flat enable, orient enable,
 *  @note single tap enable, double tap enable
 *  @note slope-x enable, slope-y enable, slope-z enable,
 *  @note fifo watermark enable,
 *  @note fifo full enable, data enable, low-g enable,
 *  @note high-z enable, high-y enable
 *  @note high-z enable
 *
 *
 *
 *  @param intr_type_u8: The value of interrupts
 *        intr_type_u8   |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_LOW_G_INTR
 *              1          | BMA2x2_HIGH_G_X_INTR
 *              2          | BMA2x2_HIGH_G_Y_INTR
 *              3          | BMA2x2_HIGH_G_Z_INTR
 *              4          | BMA2x2_DATA_ENABLE
 *              5          | SLOPE_X_INTR
 *              6          | SLOPE_Y_INTR
 *              7          | SLOPE_Z_INTR
 *              8          | SINGLE_TAP_INTR
 *              9          | SINGLE_TAP_INTR
 *              10         | ORIENT_INT
 *              11         | FLAT_INT
 *
 *  @param value_u8 : The value of interrupts enable
 *        value_u8       |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
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
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_enable(u8 intr_type_u8,
        u8 *value_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (intr_type_u8)
        {
        case BMA2x2_LOW_G_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_LOW_G_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_LOW_G_INTR);
            break;
        case BMA2x2_HIGH_G_X_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_HIGH_G_X_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_HIGH_G_X_INTR);
            break;
        case BMA2x2_HIGH_G_Y_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_HIGH_G_Y_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_HIGH_G_Y_INTR);
            break;
        case BMA2x2_HIGH_G_Z_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_HIGH_G_Z_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_HIGH_G_Z_INTR);
            break;
        case BMA2x2_DATA_ENABLE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_NEW_DATA_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_NEW_DATA_INTR);
            break;
        case BMA2x2_SLOPE_X_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOPE_X_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_SLOPE_X_INTR);
            break;
        case BMA2x2_SLOPE_Y_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOPE_Y_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_SLOPE_Y_INTR);
            break;
        case BMA2x2_SLOPE_Z_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOPE_Z_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_SLOPE_Z_INTR);
            break;
        case BMA2x2_SINGLE_TAP_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SINGLE_TAP_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_SINGLE_TAP_INTR);
            break;
        case BMA2x2_DOUBLE_TAP_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_DOUBLE_TAP_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_DOUBLE_TAP_INTR);
            break;
        case BMA2x2_ORIENT_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_ORIENT_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_ORIENT_INTR);
            break;
        case BMA2x2_FLAT_INTR:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_FLAT_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *value_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_ENABLE_FLAT_INTR);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  interrupt enable bits of the sensor in the registers 0x16 and 0x17
 *  @note It reads the flat enable, orient enable,
 *  @note single tap enable, double tap enable
 *  @note slope-x enable, slope-y enable, slope-z enable,
 *  @note fifo watermark enable,
 *  @note fifo full enable, data enable, low-g enable,
 *  @note high-z enable, high-y enable
 *  @note high-z enable
 *
 *
 *
 *  @param intr_type_u8: The value of interrupts
 *        intr_type_u8   |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_LOW_G_INTR
 *              1          | BMA2x2_HIGH_G_X_INTR
 *              2          | BMA2x2_HIGH_G_Y_INTR
 *              3          | BMA2x2_HIGH_G_Z_INTR
 *              4          | BMA2x2_DATA_ENABLE
 *              5          | SLOPE_X_INTR
 *              6          | SLOPE_Y_INTR
 *              7          | SLOPE_Z_INTR
 *              8          | SINGLE_TAP_INTR
 *              9          | SINGLE_TAP_INTR
 *              10         | ORIENT_INT
 *              11         | FLAT_INT
 *
 *  @param value_u8 : The value of interrupts enable
 *        value_u8       |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
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
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_enable(u8 intr_type_u8,
        u8 value_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 data2_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_INTR_ENABLE1_ADDR,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        com_rslt += p_bma2x2->BMA2x2_BUS_READ_FUNC
                    (p_bma2x2->dev_addr, BMA2x2_INTR_ENABLE2_ADDR,
                     &data2_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        value_u8 = value_u8 & BMA2x2_GEN_READ_WRITE_LENGTH;
        switch (intr_type_u8)
        {
        case BMA2x2_LOW_G_INTR:
            /* Low G Interrupt  */
            data2_u8 = BMA2x2_SET_BITSLICE(data2_u8,
                                           BMA2x2_ENABLE_LOW_G_INTR, value_u8);
            break;
        case BMA2x2_HIGH_G_X_INTR:
            /* High G X Interrupt */
            data2_u8 = BMA2x2_SET_BITSLICE(data2_u8,
                                           BMA2x2_ENABLE_HIGH_G_X_INTR, value_u8);
            break;
        case BMA2x2_HIGH_G_Y_INTR:
            /* High G Y Interrupt */
            data2_u8 = BMA2x2_SET_BITSLICE(data2_u8,
                                           BMA2x2_ENABLE_HIGH_G_Y_INTR, value_u8);
            break;
        case BMA2x2_HIGH_G_Z_INTR:
            /* High G Z Interrupt */
            data2_u8 = BMA2x2_SET_BITSLICE(data2_u8,
                                           BMA2x2_ENABLE_HIGH_G_Z_INTR, value_u8);
            break;
        case BMA2x2_DATA_ENABLE:
            /*Data En Interrupt  */
            data2_u8 = BMA2x2_SET_BITSLICE(data2_u8,
                                           BMA2x2_ENABLE_NEW_DATA_INTR, value_u8);
            break;
        case BMA2x2_SLOPE_X_INTR:
            /* Slope X Interrupt */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_SLOPE_X_INTR, value_u8);
            break;
        case BMA2x2_SLOPE_Y_INTR:
            /* Slope Y Interrupt */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_SLOPE_Y_INTR, value_u8);
            break;
        case BMA2x2_SLOPE_Z_INTR:
            /* Slope Z Interrupt */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_SLOPE_Z_INTR, value_u8);
            break;
        case BMA2x2_SINGLE_TAP_INTR:
            /* Single Tap Interrupt */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_SINGLE_TAP_INTR, value_u8);
            break;
        case BMA2x2_DOUBLE_TAP_INTR:
            /* Double Tap Interrupt */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_DOUBLE_TAP_INTR, value_u8);
            break;
        case BMA2x2_ORIENT_INTR:
            /* Orient Interrupt  */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_ORIENT_INTR, value_u8);
            break;
        case BMA2x2_FLAT_INTR:
            /* Flat Interrupt */
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_FLAT_INTR, value_u8);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
        /* write the interrupt*/
        com_rslt += bma2x2_write_reg
                    (BMA2x2_INTR_ENABLE1_ADDR,
                     &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        com_rslt += bma2x2_write_reg
                    (BMA2x2_INTR_ENABLE2_ADDR,
                     &data2_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the interrupt fifo full enable interrupt status
 *  in the register 0x17 bit 5
 *
 *
 *  @param fifo_full_u8 The value of fifo full interrupt enable
 *        fifo_full_u8   |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_fifo_full(u8 *fifo_full_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read fifo full interrupt */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *fifo_full_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                            BMA2x2_INTR_FIFO_FULL_ENABLE_INTR);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the interrupt fifo full enable interrupt status
 *  in the register 0x17 bit 5
 *
 *
 *  @param fifo_full_u8 The value of fifo full interrupt enable
 *        fifo_full_u8   |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_fifo_full(u8 fifo_full_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (fifo_full_u8 < BMA2x2_FIFO_MODE_STATUS_RANGE)
        {
            /* Write fifo full interrupt */
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_INTR_FIFO_FULL_ENABLE_INTR,
                       fifo_full_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR_FIFO_FULL_ENABLE_INTR_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 *  the interrupt fifo watermark enable interrupt status
 *  in the register 0x17 bit 6
 *
 *
 *
 *
 *  @param fifo_wm_u8 : the value FIFO Water Mark
 *        fifo_wm_u8     |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_fifo_wm(u8 *fifo_wm_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the fifo water mark*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_INTR_FIFO_WM_ENABLE_INTR_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *fifo_wm_u8 = BMA2x2_GET_BITSLICE
                      (data_u8, BMA2x2_INTR_FIFO_WM_ENABLE_INTR);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 *  the interrupt fifo watermark enable interrupt status
 *  in the register 0x17 bit 6
 *
 *
 *
 *
 *  @param fifo_wm_u8 : the value FIFO Water Mark
 *        fifo_wm_u8     |   result
 *       ----------------- | ------------------
 *              0x00       | INTR_DISABLE
 *              0x01       | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_fifo_wm(u8 fifo_wm_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (fifo_wm_u8 < BMA2x2_FIFO_MODE_STATUS_RANGE)
        {
            /* Write the fifo water mark interrupt*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_FIFO_WM_ENABLE_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_INTR_FIFO_WM_ENABLE_INTR,
                       fifo_wm_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR_FIFO_WM_ENABLE_INTR_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt status of slow/no motion select and slow no motion
 * enable xyz interrupt in the register 0x18 bit from 0 to 3
 *
 *
 *  @param  channel_u8 : The value of slow/no motion select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_X
 *              1          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Y
 *              2          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Z
 *              3          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_SEL
 *
 *  @param slow_no_motion_u8 : The value of slow no motion interrupt enable
 *        slow_no_motion_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_slow_no_motion(u8 channel_u8,
        u8 *slow_no_motion_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the slow no motion interrupt */
        switch (channel_u8)
        {
        case BMA2x2_SLOW_NO_MOTION_ENABLE_X:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_no_motion_u8 = BMA2x2_GET_BITSLICE
                                 (data_u8, BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR);
            break;
        case BMA2x2_SLOW_NO_MOTION_ENABLE_Y:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_no_motion_u8 = BMA2x2_GET_BITSLICE
                                 (data_u8, BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR);
            break;
        case BMA2x2_SLOW_NO_MOTION_ENABLE_Z:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_no_motion_u8 = BMA2x2_GET_BITSLICE
                                 (data_u8, BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR);
            break;
        case BMA2x2_SLOW_NO_MOTION_ENABLE_SELECT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_no_motion_u8 = BMA2x2_GET_BITSLICE
                                 (data_u8,
                                  BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt status of slow/no motion select and slow no motion
 * enable xyz interrupt in the register 0x18 bit from 0 to 3
 *
 *
 *  @param  channel_u8 : The value of slow/no motion select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_X
 *              1          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Y
 *              2          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_Z
 *              3          | BMA2x2_ACCEL_SLOW_NO_MOTION_ENABLE_SEL
 *
 *  @param slow_no_motion_u8 : The value of slow no motion
 *      interrupt enable
 *        slow_no_motion_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_slow_no_motion(u8 channel_u8,
        u8 slow_no_motion_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Write the slow no motion interrupt*/
        switch (channel_u8)
        {
        case BMA2x2_SLOW_NO_MOTION_ENABLE_X:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR,
                       slow_no_motion_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_NO_MOTION_ENABLE_Y:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR,
                       slow_no_motion_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_NO_MOTION_ENABLE_Z:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR,
                       slow_no_motion_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_NO_MOTION_ENABLE_SELECT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR,
                       slow_no_motion_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief  This API is used to get
 * the interrupt enable of low_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_Low_g -> register 0x19 bit 0
 * @note INTR2_Low_g -> register 0x1B bit 0
 *
 *
 *
 *
 * @param channel_u8 : The value of low interrupt selection channel
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_LOW_G
 *              1          | BMA2x2_ACCEL_INTR2_LOW_G
 *
 * @param intr_low_g_u8 : the value of low_g interrupt
 *        intr_low_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_low_g(u8 channel_u8,
        u8 *intr_low_g_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Read the low_g interrupt*/
        case BMA2x2_INTR1_LOW_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_LOW_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_low_g_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_ENABLE_INTR1_PAD_LOW_G);
            break;
        case BMA2x2_INTR2_LOW_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_LOW_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_low_g_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_ENABLE_INTR2_PAD_LOW_G);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief  This API is used to set
 * the interrupt enable of low_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_Low_g -> register 0x19 bit 0
 * @note INTR2_Low_g -> register 0x1B bit 0
 *
 *
 *
 *
 * @param channel_u8 : The value of low interrupt selection channel
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_LOW_G
 *              1          | BMA2x2_ACCEL_INTR2_LOW_G
 *
 * @param intr_low_u8 : the value of low_g interrupt
 *        intr_low_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_low_g(u8 channel_u8,
        u8 intr_low_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_INTR1_LOW_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_LOW_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_INTR1_PAD_LOW_G, intr_low_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_LOW_G_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_LOW_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_LOW_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_INTR2_PAD_LOW_G,
                       intr_low_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_LOW_G_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt enable of high_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_high_g -> register 0x19 bit 1
 * @note INTR2_high_g -> register 0x1B bit 1
 *
 *
 *  @param  channel_u8: The value of high_g interrupt selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_HIGH_G
 *              1          | BMA2x2_ACCEL_INTR2_HIGH_G
 *
 * @param intr_high_g_u8 : the value of high_g interrupt
 *        intr_high_g_u8        |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_high_g(u8 channel_u8,
        u8 *intr_high_g_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* read the high_g interrupt*/
        case BMA2x2_INTR1_HIGH_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_HIGH_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_high_g_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_ENABLE_INTR1_PAD_HIGH_G);
            break;
        case BMA2x2_INTR2_HIGH_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_HIGH_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_high_g_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_ENABLE_INTR2_PAD_HIGH_G);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt enable of high_g interrupt in the register 0x19 and 0x1B
 * @note INTR1_high_g -> register 0x19 bit 1
 * @note INTR2_high_g -> register 0x1B bit 1
 *
 *
 *  @param  channel_u8: The value of high_g interrupt selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_HIGH_G
 *              1          | BMA2x2_ACCEL_INTR2_HIGH_G
 *
 * @param intr_high_g_u8 : the value of high_g interrupt
 *        intr_high_g_u8        |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_high_g(u8 channel_u8,
        u8 intr_high_g_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the high_g interrupt*/
        switch (channel_u8)
        {
        case BMA2x2_INTR1_HIGH_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_HIGH_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_INTR1_PAD_HIGH_G,
                       intr_high_g_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_HIGH_G_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_HIGH_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_HIGH_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_INTR2_PAD_HIGH_G,
                       intr_high_g_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_HIGH_G_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt enable of slope interrupt in the register 0x19 and 0x1B
 * @note INTR1_slope -> register 0x19 bit 2
 * @note INTR2_slope -> register 0x1B bit 2
 *
 *
 *
 * @param channel_u8: the value of slope channel select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SLOPE
 *              1          | BMA2x2_ACCEL_INTR2_SLOPE
 *
 * @param intr_slope_u8 : The slope value enable value
 *        intr_slope_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_slope(u8 channel_u8,
        u8 *intr_slope_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the slope value */
        switch (channel_u8)
        {
        case BMA2x2_INTR1_SLOPE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_SLOPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_slope_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_ENABLE_INTR1_PAD_SLOPE);
            break;
        case BMA2x2_INTR2_SLOPE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_SLOPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_slope_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_ENABLE_INTR2_PAD_SLOPE);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt enable of slope interrupt in the register 0x19 and 0x1B
 * @note INTR1_slope -> register 0x19 bit 2
 * @note INTR2_slope -> register 0x1B bit 2
 *
 *
 *
 * @param channel_u8: the value of slope channel select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SLOPE
 *              1          | BMA2x2_ACCEL_INTR2_SLOPE
 *
 * @param intr_slope_u8 : The slope value enable value
 *        intr_slope_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_slope(u8 channel_u8,
        u8 intr_slope_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Write the slope value */
        case BMA2x2_INTR1_SLOPE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_SLOPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_INTR1_PAD_SLOPE,
                       intr_slope_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_SLOPE_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_SLOPE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_SLOPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_INTR2_PAD_SLOPE,
                       intr_slope_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_SLOPE_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt enable of slow/no motion interrupt in
 * the register 0x19 and 0x1B
 * @note INTR1_slow_no_motion -> register 0x19 bit 3
 * @note INTR2_slow_no_motion -> register 0x1B bit 3
 *
 *
 *
 *
 *  @param channel_u8 : The value of slow/no motion selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_INTR1_SLOW_NO_MOTION
 *              1          | BMA2x2_INTR2_SLOW_NO_MOTION
 *
 *  @param intr_slow_no_motion_u8:  the slow_no_motion enable value
 *       intr_slow_no_motion_u8 |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_slow_no_motion(u8 channel_u8,
        u8 *intr_slow_no_motion_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the slow no motion interrupt */
        switch (channel_u8)
        {
        case BMA2x2_INTR1_SLOW_NO_MOTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_slow_no_motion_u8 = BMA2x2_GET_BITSLICE
                                      (data_u8, BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION);
            break;
        case BMA2x2_INTR2_SLOW_NO_MOTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_slow_no_motion_u8 = BMA2x2_GET_BITSLICE
                                      (data_u8, BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt enable of slow/no motion interrupt in
 * the register 0x19 and 0x1B
 * @note INTR1_slow_no_motion -> register 0x19 bit 3
 * @note INTR2_slow_no_motion -> register 0x1B bit 3
 *
 *
 *
 *
 *  @param channel_u8 : The value of slow/no motion selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_INTR1_SLOW_NO_MOTION
 *              1          | BMA2x2_INTR2_SLOW_NO_MOTION
 *
 *  @param intr_slow_no_motion_u8:  the slow_no_motion enable value
 *       intr_slow_no_motion_u8 |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_slow_no_motion(u8 channel_u8,
        u8 intr_slow_no_motion_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Write the slow no motion interrupt */
        case BMA2x2_INTR1_SLOW_NO_MOTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION,
                       intr_slow_no_motion_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_SLOW_NO_MOTION_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_SLOW_NO_MOTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION,
                       intr_slow_no_motion_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_SLOW_NO_MOTION_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt enable of double tap interrupt
 * in the register 0x19 and 0x1B
 * @note INTR1_double -> register 0x19 bit 4
 * @note INTR2_double -> register 0x1B bit 4
 *
 *
 *
 *
 *  @param channel_u8: The value of double tap selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_DOUBLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_DOUBLE_TAP
 *
 *  @param intr_double_tap_u8: The double tap interrupt enable value
 *       intr_double_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_double_tap(u8 channel_u8,
        u8 *intr_double_tap_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the double tap*/
        switch (channel_u8)
        {
        case BMA2x2_INTR1_DOUBLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_double_tap_u8 = BMA2x2_GET_BITSLICE
                                  (data_u8, BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP);
            break;
        case BMA2x2_INTR2_DOUBLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_double_tap_u8 = BMA2x2_GET_BITSLICE
                                  (data_u8, BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt enable of double tap interrupt
 * in the register 0x19 and 0x1B
 * @note INTR1_double -> register 0x19 bit 4
 * @note INTR2_double -> register 0x1B bit 4
 *
 *
 *
 *
 *  @param channel_u8: The value of double tap selection
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_DOUBLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_DOUBLE_TAP
 *
 *  @param intr_double_tap_u8: The double tap interrupt enable value
 *       intr_double_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_double_tap(u8 channel_u8,
        u8 intr_double_tap_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the double tap*/
        case BMA2x2_INTR1_DOUBLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP,
                       intr_double_tap_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_DOUBLE_TAP_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_DOUBLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP,
                       intr_double_tap_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_DOUBLE_TAP_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt enable of single tap
 * interrupt in the register 0x19 and 0x1B
 * @note INTR1_single_tap -> register 0x19 bit 5
 * @note INTR2_single_tap -> register 0x1B bit 5
 *
 *
 *  @param channel_u8: The value of single tap interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SINGLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_SINGLE_TAP
 *
 *  @param intr_single_tap_u8: The single tap interrupt enable value
 *       intr_single_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_single_tap(u8 channel_u8,
        u8 *intr_single_tap_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Read the single tap value*/
        case BMA2x2_INTR1_SINGLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_single_tap_u8 = BMA2x2_GET_BITSLICE
                                  (data_u8, BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP);
            break;
        case BMA2x2_INTR2_SINGLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_single_tap_u8 = BMA2x2_GET_BITSLICE
                                  (data_u8, BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt enable of single tap
 * interrupt in the register 0x19 and 0x1B
 * @note INTR1_single_tap -> register 0x19 bit 5
 * @note INTR2_single_tap -> register 0x1B bit 5
 *
 *
 *  @param channel_u8: The value of single tap interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_SINGLE_TAP
 *              1          | BMA2x2_ACCEL_INTR2_SINGLE_TAP
 *
 *  @param intr_single_tap_u8: The single tap interrupt enable value
 *       intr_single_tap_u8     |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_single_tap(u8 channel_u8,
        u8 intr_single_tap_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the single tap value*/
        case BMA2x2_INTR1_SINGLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP,
                                          intr_single_tap_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_SINGLE_TAP_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_SINGLE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP,
                       intr_single_tap_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_SINGLE_TAP_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt status of orient interrupt in the register 0x19 and 0x1B
 * @note INTR1_orient -> register 0x19 bit 6
 * @note INTR2_orient -> register 0x1B bit 6
 *
 *
 * @param channel_u8: The value of orient interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_ORIENT
 *              1          | BMA2x2_ACCEL_INTR2_ORIENT
 *
 *  @param intr_orient_u8: The value of orient interrupt enable
 *       intr_orient_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_orient(u8 channel_u8,
        u8 *intr_orient_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Read orient interrupt*/
        case BMA2x2_INTR1_ORIENT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_ORIENT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_orient_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_ENABLE_INTR1_PAD_ORIENT);
            break;
        case BMA2x2_INTR2_ORIENT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_ORIENT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_orient_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_ENABLE_INTR2_PAD_ORIENT);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt status of orient interrupt in the register 0x19 and 0x1B
 * @note INTR1_orient -> register 0x19 bit 6
 * @note INTR2_orient -> register 0x1B bit 6
 *
 *
 * @param channel_u8: The value of orient interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_ORIENT
 *              1          | BMA2x2_ACCEL_INTR2_ORIENT
 *
 *  @param intr_orient_u8: The value of orient interrupt enable
 *       intr_orient_u8         |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_orient(u8 channel_u8,
        u8 intr_orient_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Write orient interrupt */
        case BMA2x2_INTR1_ORIENT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_ORIENT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR1_PAD_ORIENT, intr_orient_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_ORIENT_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_ORIENT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_ORIENT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_ORIENT, intr_orient_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_ORIENT_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt enable of flat interrupt in the register 0x19 and 0x1B
 * @note INTR1_flat -> register 0x19 bit 7
 * @note INTR2_flat -> register 0x1B bit 7
 *
 *
 *
 *
 * @param channel_u8: The value of flat interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_FLAT
 *              1          | BMA2x2_ACCEL_INTR2_FLAT
 *
 * @param intr_flat_u8: The flat interrupt enable value
 *       intr_flat_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_flat(u8 channel_u8,
        u8 *intr_flat_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Read flat interrupt */
        case BMA2x2_INTR1_FLAT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_FLAT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_flat_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_INTR1_PAD_FLAT);
            break;
        case BMA2x2_INTR2_FLAT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_FLAT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_flat_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_INTR2_PAD_FLAT);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt enable of flat interrupt in the register 0x19 and 0x1B
 * @note INTR1_flat -> register 0x19 bit 7
 * @note INTR2_flat -> register 0x1B bit 7
 *
 *
 *
 *
 * @param channel_u8: The value of flat interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_FLAT
 *              1          | BMA2x2_ACCEL_INTR2_FLAT
 *
 * @param intr_flat_u8: The flat interrupt enable value
 *       intr_flat_u8           |   result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_flat(u8 channel_u8,
        u8 intr_flat_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write flat interrupt */
        case BMA2x2_INTR1_FLAT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_FLAT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR1_PAD_FLAT, intr_flat_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_FLAT_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_FLAT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_FLAT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_FLAT, intr_flat_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_FLAT_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the interrupt status of new data in the register 0x19
 * @note INTR1_data -> register 0x19 bit 0
 * @note INTR2_data -> register 0x19 bit 7
 *
 *
 *
 *  @param channel_u8: The value of new data interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_NEWDATA
 *              1          | BMA2x2_ACCEL_INTR2_NEWDATA
 *
 *  @param intr_newdata_u8: The new data interrupt enable value
 *       intr_newdata_u8          |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_new_data(u8 channel_u8,
        u8 *intr_newdata_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Read the data interrupt*/
        case BMA2x2_INTR1_NEWDATA:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_NEWDATA_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_newdata_u8 = BMA2x2_GET_BITSLICE
                               (data_u8, BMA2x2_ENABLE_INTR1_PAD_NEWDATA);
            break;
        case BMA2x2_INTR2_NEWDATA:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_NEWDATA_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_newdata_u8 = BMA2x2_GET_BITSLICE
                               (data_u8, BMA2x2_ENABLE_INTR2_PAD_NEWDATA);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the interrupt status of new data in the register 0x19
 * @note INTR1_data -> register 0x19 bit 0
 * @note INTR2_data -> register 0x19 bit 7
 *
 *
 *
 *  @param channel_u8: The value of new data interrupt select
 *        channel_u8     |   result
 *       ----------------- | ------------------
 *              0          | BMA2x2_ACCEL_INTR1_NEWDATA
 *              1          | BMA2x2_ACCEL_INTR2_NEWDATA
 *
 *  @param intr_newdata_u8: The new data interrupt enable value
 *       intr_newdata_u8          |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_new_data(u8 channel_u8,
        u8 intr_newdata_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the new data interrupt */
        case BMA2x2_INTR1_NEWDATA:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_NEWDATA_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR1_PAD_NEWDATA, intr_newdata_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_NEWDATA_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_NEWDATA:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_NEWDATA_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_NEWDATA, intr_newdata_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_NEWDATA_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get the fifo watermark interrupt1 data
 * in the register 0x1A bit 1
 *
 *  @param  intr1_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr1_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr1_fifo_wm(u8 *intr1_fifo_wm_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the fifo watermark interrupt */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *intr1_fifo_wm_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_INTR1_PAD_FIFO_WM);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set the fifo watermark interrupt1 data
 * in the register 0x1A bit 1
 *
 *  @param  intr1_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr1_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr1_fifo_wm(u8 intr1_fifo_wm_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (intr1_fifo_wm_u8 <
                BMA2x2_FIFO_MODE_STATUS_RANGE)
        {
            /* write the fifo watermark interrupt */
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR1_PAD_FIFO_WM, intr1_fifo_wm_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_FIFO_WM_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get the fifo watermark interrupt2 data
 * in the register 0x1A bit 6
 *
 *  @param  intr2_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr2_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr2_fifo_wm(u8 *intr2_fifo_wm_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the fifo watermark interrupt2*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *intr2_fifo_wm_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_INTR2_PAD_FIFO_WM);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set the fifo watermark interrupt2 data
 * in the register 0x1A bit 6
 *
 *  @param  intr2_fifo_wm_u8 : The value of interrupt1 FIFO watermark enable
 *       intr2_fifo_wm_u8       |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr2_fifo_wm(u8 intr2_fifo_wm_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (intr2_fifo_wm_u8 <
                BMA2x2_FIFO_MODE_STATUS_RANGE)
        {
            /* write the fifo watermark interrupt2*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_FIFO_WM, intr2_fifo_wm_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_FIFO_WM_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the fifo full interrupt1 in the register 0x1A bit 2
 *
 *
 *
 *  @param intr1_fifo_full_u8 : The value of fifo full interrupt enable
 *       intr1_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr1_fifo_full(u8 *intr1_fifo_full_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the fifo full interrupt1*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *intr1_fifo_full_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the fifo full interrupt1 in the register 0x1A bit 2
 *
 *
 *
 *  @param intr1_fifo_full_u8 : The value of fifo full interrupt enable
 *       intr1_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr1_fifo_full(u8 intr1_fifo_full_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (intr1_fifo_full_u8 <
                BMA2x2_FIFO_MODE_STATUS_RANGE)
        {
            /* write the fifo full interrupt1*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL,
                       intr1_fifo_full_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR1_PAD_FIFO_FULL_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the fifo full interrupt2 in the register 0x1A bit 5
 *
 *
 *
 *  @param intr2_fifo_full_u8 : Thee vale of fifo full enable
 *       intr2_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr2_fifo_full(u8 *intr2_fifo_full_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the fifo full interrupt2*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *intr2_fifo_full_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the fifo full interrupt2 in the register 0x1A bit 5
 *
 *
 *
 *  @param intr2_fifo_full_u8 : Thee vale of fifo full enable
 *       intr2_fifo_full_u8     |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr2_fifo_full(u8 intr2_fifo_full_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (intr2_fifo_full_u8 <
                BMA2x2_FIFO_MODE_STATUS_RANGE)
        {
            /* write the fifo full interrupt2*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL,
                       intr2_fifo_full_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_INTR2_PAD_FIFO_FULL_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the source data status of source data,
 *  source slow no motion, source slope, source high
 *  and source low in the register 0x1E bit from 0 to 5
 *
 *
 *
 *  @param channel_u8 : The value of source select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_SOURCE_LOW_G
 *               1        | BMA2x2_ACCEL_SOURCE_HIGH_G
 *               2        | BMA2x2_ACCEL_SOURCE_SLOPE
 *               3        | BMA2x2_ACCEL_SOURCE_SLOW_NO_MOTION
 *               4        | BMA2x2_ACCEL_SOURCE_TAP
 *               5        | BMA2x2_ACCEL_SOURCE_DATA
 *
 *  @param intr_source_u8: The source status enable value
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_source(u8 channel_u8,
        u8 *intr_source_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        return  E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the source interrupt register */
        switch (channel_u8)
        {
        case BMA2x2_SOURCE_LOW_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_LOW_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_source_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_UNFILT_INTR_SOURCE_LOW_G);
            break;
        case BMA2x2_SOURCE_HIGH_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_source_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_UNFILT_INTR_SOURCE_HIGH_G);
            break;
        case BMA2x2_SOURCE_SLOPE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_SLOPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_source_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_UNFILT_INTR_SOURCE_SLOPE);
            break;
        case BMA2x2_SOURCE_SLOW_NO_MOTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_source_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION);
            break;
        case BMA2x2_SOURCE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_source_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_UNFILT_INTR_SOURCE_TAP);
            break;
        case BMA2x2_SOURCE_DATA:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_DATA_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_source_u8 = BMA2x2_GET_BITSLICE
                              (data_u8, BMA2x2_UNFILT_INTR_SOURCE_DATA);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the source data status of source data,
 *  source slow no motion, source slope, source high
 *  and source low in the register 0x1E bit from 0 to 5
 *
 *
 *
 *  @param channel_u8 : The value of source select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_SOURCE_LOW_G
 *               1        | BMA2x2_ACCEL_SOURCE_HIGH_G
 *               2        | BMA2x2_ACCEL_SOURCE_SLOPE
 *               3        | BMA2x2_ACCEL_SOURCE_SLOW_NO_MOTION
 *               4        | BMA2x2_ACCEL_SOURCE_TAP
 *               5        | BMA2x2_ACCEL_SOURCE_DATA
 *
 *  @param intr_source_u8: The source status enable value
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x00              | INTR_DISABLE
 *              0x01              | INTR_ENABLE
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_source(u8 channel_u8,
        u8 intr_source_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    if (p_bma2x2 == BMA2x2_NULL)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the source interrupt register*/
        case BMA2x2_SOURCE_LOW_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_LOW_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_UNFILT_INTR_SOURCE_LOW_G, intr_source_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_UNFILT_INTR_SOURCE_LOW_G_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SOURCE_HIGH_G:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_UNFILT_INTR_SOURCE_HIGH_G, intr_source_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_UNFILT_INTR_SOURCE_HIGH_G_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SOURCE_SLOPE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_SLOPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_UNFILT_INTR_SOURCE_SLOPE, intr_source_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_UNFILT_INTR_SOURCE_SLOPE_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SOURCE_SLOW_NO_MOTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION,
                       intr_source_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SOURCE_TAP:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_TAP_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_UNFILT_INTR_SOURCE_TAP,
                       intr_source_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_UNFILT_INTR_SOURCE_TAP_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SOURCE_DATA:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_UNFILT_INTR_SOURCE_DATA_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_UNFILT_INTR_SOURCE_DATA,
                       intr_source_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_UNFILT_INTR_SOURCE_DATA_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the interrupt output type in the register 0x20.
 *  @note INTR1 -> bit 1
 *  @note INTR2 -> bit 3
 *
 *  @param channel_u8: The value of output type select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_OUTPUT
 *               1        | BMA2x2_ACCEL_INTR2_OUTPUT
 *
 *  @param intr_output_type_u8: The value of output type select
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x01              | OPEN_DRAIN
 *              0x00              | PUSS_PULL
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_output_type(u8 channel_u8,
        u8 *intr_output_type_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* read the output type */
        case BMA2x2_INTR1_OUTPUT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR1_PAD_OUTPUT_TYPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_output_type_u8 = BMA2x2_GET_BITSLICE
                                   (data_u8, BMA2x2_INTR1_PAD_OUTPUT_TYPE);
            break;
        case BMA2x2_INTR2_OUTPUT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR2_PAD_OUTPUT_TYPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_output_type_u8 = BMA2x2_GET_BITSLICE
                                   (data_u8, BMA2x2_INTR2_PAD_OUTPUT_TYPE);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the interrupt output type in the register 0x20.
 *  @note INTR1 -> bit 1
 *  @note INTR2 -> bit 3
 *
 *  @param channel_u8: The value of output type select
 *         channel_u8   |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_OUTPUT
 *               1        | BMA2x2_ACCEL_INTR2_OUTPUT
 *
 *  @param intr_output_type_u8: The value of output type select
 *       intr_source_u8         |    result
 *       ------------------------ | ------------------
 *              0x01              | OPEN_DRAIN
 *              0x00              | PUSS_PULL
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_output_type(u8 channel_u8,
        u8 intr_output_type_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the output type*/
        case BMA2x2_INTR1_OUTPUT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR1_PAD_OUTPUT_TYPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR1_PAD_OUTPUT_TYPE, intr_output_type_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR1_PAD_OUTPUT_TYPE_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_OUTPUT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR2_PAD_OUTPUT_TYPE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR2_PAD_OUTPUT_TYPE, intr_output_type_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR2_PAD_OUTPUT_TYPE_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  Active Level status in the register 0x20
 *  @note INTR1 -> bit 0
 *  @note INTR2 -> bit 2
 *
 *  @param channel_u8: The value of Active Level select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_LEVEL
 *               1        | BMA2x2_ACCEL_INTR2_LEVEL
 *
 *  @param intr_level_u8: The Active Level status enable value
 *        intr_level_u8         |    result
 *       ------------------------ | ------------------
 *              0x01              | ACTIVE_HIGH
 *              0x00              | ACTIVE_LOW
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_intr_level(u8 channel_u8,
        u8 *intr_level_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* read the active level*/
        case BMA2x2_INTR1_LEVEL:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR1_PAD_ACTIVE_LEVEL_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_level_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_INTR1_PAD_ACTIVE_LEVEL);
            break;
        case BMA2x2_INTR2_LEVEL:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR2_PAD_ACTIVE_LEVEL_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *intr_level_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_INTR2_PAD_ACTIVE_LEVEL);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  Active Level status in the register 0x20
 *  @note INTR1 -> bit 0
 *  @note INTR2 -> bit 2
 *
 *  @param channel_u8: The value of Active Level select
 *       channel_u8     |    result
 *       -----------------| ------------------
 *               0        | BMA2x2_ACCEL_INTR1_LEVEL
 *               1        | BMA2x2_ACCEL_INTR2_LEVEL
 *
 *  @param intr_level_u8: The Active Level status enable value
 *       intr_level_u8          |    result
 *       ------------------------ | ------------------
 *              0x01              | ACTIVE_HIGH
 *              0x00              | ACTIVE_LOW
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_intr_level(u8 channel_u8,
        u8 intr_level_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the active level */
        case BMA2x2_INTR1_LEVEL:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR1_PAD_ACTIVE_LEVEL_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR1_PAD_ACTIVE_LEVEL, intr_level_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR1_PAD_ACTIVE_LEVEL_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_INTR2_LEVEL:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_INTR2_PAD_ACTIVE_LEVEL_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_INTR2_PAD_ACTIVE_LEVEL, intr_level_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_INTR2_PAD_ACTIVE_LEVEL_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the reset interrupt in the register 0x21 bit 7
 *
 *
 *
 *  @param  rst_intr_u8: The value of reset interrupt
 *          rst_intr_u8         |  result
 *       ------------------------ | ------------------
 *              0x01              | clear any latch interrupt
 *              0x00              | keep latch interrupt active
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_rst_intr(u8 rst_intr_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_RESET_INTR_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_RESET_INTR, rst_intr_u8);
        com_rslt += bma2x2_write_reg(BMA2x2_RESET_INTR_REG,
                                     &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the latch duration in the register 0x21 bit from 0 to 3
 *
 *  @param latch_intr_u8: The value of latch duration
 *        latch_intr_u8 |  result
 *       -----------------| ------------------
 *               0x00     | BMA2x2_LATCH_DURN_NON_LATCH
 *               0x01     | BMA2x2_LATCH_DURN_250MS
 *               0x02     | BMA2x2_LATCH_DURN_500MS
 *               0x03     | BMA2x2_LATCH_DURN_1S
 *               0x04     | BMA2x2_LATCH_DURN_2S
 *               0x05     | BMA2x2_LATCH_DURN_4S
 *               0x06     | BMA2x2_LATCH_DURN_8S
 *               0x07     | BMA2x2_LATCH_DURN_LATCH
 *               0x08     | BMA2x2_LATCH_DURN_NON_LATCH1
 *               0x09     | BMA2x2_LATCH_DURN_250US
 *               0x0A     | BMA2x2_LATCH_DURN_500US
 *               0x0B     | BMA2x2_LATCH_DURN_1MS
 *               0x0C     | BMA2x2_LATCH_DURN_12_5MS
 *               0x0D     | BMA2x2_LATCH_DURN_25MS
 *               0x0E     | BMA2x2_LATCH_DURN_50MS
 *               0x0F     | BMA2x2_LATCH_DURN_LATCH1
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_latch_intr(u8 *latch_intr_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the latch duration */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_LATCH_INTR_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *latch_intr_u8 = BMA2x2_GET_BITSLICE
                         (data_u8, BMA2x2_LATCH_INTR);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the latch duration in the register 0x21 bit from 0 to 3
 *
 *  @param latch_intr_u8: The value of latch duration
 *        latch_intr_u8 |  result
 *       -----------------| ------------------
 *               0x00     | BMA2x2_LATCH_DURN_NON_LATCH
 *               0x01     | BMA2x2_LATCH_DURN_250MS
 *               0x02     | BMA2x2_LATCH_DURN_500MS
 *               0x03     | BMA2x2_LATCH_DURN_1S
 *               0x04     | BMA2x2_LATCH_DURN_2S
 *               0x05     | BMA2x2_LATCH_DURN_4S
 *               0x06     | BMA2x2_LATCH_DURN_8S
 *               0x07     | BMA2x2_LATCH_DURN_LATCH
 *               0x08     | BMA2x2_LATCH_DURN_NON_LATCH1
 *               0x09     | BMA2x2_LATCH_DURN_250US
 *               0x0A     | BMA2x2_LATCH_DURN_500US
 *               0x0B     | BMA2x2_LATCH_DURN_1MS
 *               0x0C     | BMA2x2_LATCH_DURN_12_5MS
 *               0x0D     | BMA2x2_LATCH_DURN_25MS
 *               0x0E     | BMA2x2_LATCH_DURN_50MS
 *               0x0F     | BMA2x2_LATCH_DURN_LATCH1
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_latch_intr(u8 latch_intr_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 latch_durn_u8 = BMA2x2_INIT_VALUE;
    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (latch_intr_u8 < BMA2x2_ACCEL_BW_MAX_RANGE)
        {
            switch (latch_intr_u8)
            {
            case BMA2x2_LATCH_DURN_NON_LATCH:
                latch_durn_u8 = BMA2x2_LATCH_DURN_NON_LATCH;

                /*  NON LATCH   */
                break;
            case BMA2x2_LATCH_DURN_250MS:
                latch_durn_u8 = BMA2x2_LATCH_DURN_250MS;

                /*  250 MS  */
                break;
            case BMA2x2_LATCH_DURN_500MS:
                latch_durn_u8 = BMA2x2_LATCH_DURN_500MS;

                /*  500 MS  */
                break;
            case BMA2x2_LATCH_DURN_1S:
                latch_durn_u8 = BMA2x2_LATCH_DURN_1S;

                /*  1 S   */
                break;
            case BMA2x2_LATCH_DURN_2S:
                latch_durn_u8 = BMA2x2_LATCH_DURN_2S;

                /*  2 S  */
                break;
            case BMA2x2_LATCH_DURN_4S:
                latch_durn_u8 = BMA2x2_LATCH_DURN_4S;

                /*  4 S  */
                break;
            case BMA2x2_LATCH_DURN_8S:
                latch_durn_u8 = BMA2x2_LATCH_DURN_8S;

                /*  8 S  */
                break;
            case BMA2x2_LATCH_DURN_LATCH:
                latch_durn_u8 = BMA2x2_LATCH_DURN_LATCH;

                /*  LATCH  */
                break;
            case BMA2x2_LATCH_DURN_NON_LATCH1:
                latch_durn_u8 = BMA2x2_LATCH_DURN_NON_LATCH1;

                /*  NON LATCH1  */
                break;
            case BMA2x2_LATCH_DURN_250US:
                latch_durn_u8 = BMA2x2_LATCH_DURN_250US;

                /*  250 US   */
                break;
            case BMA2x2_LATCH_DURN_500US:
                latch_durn_u8 = BMA2x2_LATCH_DURN_500US;

                /*  500 US   */
                break;
            case BMA2x2_LATCH_DURN_1MS:
                latch_durn_u8 = BMA2x2_LATCH_DURN_1MS;

                /*  1 MS   */
                break;
            case BMA2x2_LATCH_DURN_12_5MS:
                latch_durn_u8 = BMA2x2_LATCH_DURN_12_5MS;

                /*  12.5 MS   */
                break;
            case BMA2x2_LATCH_DURN_25MS:
                latch_durn_u8 = BMA2x2_LATCH_DURN_25MS;

                /*  25 MS   */
                break;
            case BMA2x2_LATCH_DURN_50MS:
                latch_durn_u8 = BMA2x2_LATCH_DURN_50MS;

                /*  50 MS   */
                break;
            case BMA2x2_LATCH_DURN_LATCH1:
                latch_durn_u8 = BMA2x2_LATCH_DURN_LATCH1;

                /*  LATCH1   */
                break;
            default:
                break;
            }
            /* write the latch duration */
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_LATCH_INTR_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_LATCH_INTR, latch_durn_u8);
            com_rslt += bma2x2_write_reg(BMA2x2_LATCH_INTR_REG,
                                         &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get the duration of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_DURN      -> register 0x22 bit form 0 to 7
 *  @note HIGH_DURN     -> register 0x25 bit form 0 to 7
 *  @note SLOPE_DURN        -> register 0x27 bit form 0 to 1
 *  @note SLO_NO_MOT_DURN -> register 0x27 bit form 2 to 7
 *
 *  @param channel_u8: The value of duration select
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_DURN
 *               1    | BMA2x2_ACCEL_HIGH_DURN
 *               2    | BMA2x2_ACCEL_SLOPE_DURN
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_DURN
 *
 *  @param durn_u8: The value of duration
 *
 *  @note :
 *     Duration           |    result
 * -----------------------| ------------------
 * BMA2x2_ACCEL_LOW_DURN  | Low-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 20ms
 * BMA2x2_ACCEL_HIGH_DURN | high-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 32ms
 * BMA2x2_ACCEL_SLOPE_DURN| slope interrupt trigger
 *         -              | if[durn_u8<1:0>+1] consecutive data points
 *         -              | are above the slope interrupt threshold
 * SLO_NO_MOT_DURN        | Refer data sheet for clear information
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_durn(u8 channel_u8,
        u8 *durn_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the duration data */
        switch (channel_u8)
        {
        case BMA2x2_LOW_DURN:
            /*LOW DURATION*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_LOW_DURN_ADDR,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *durn_u8 = data_u8;
            break;
        case BMA2x2_HIGH_DURN:
            /*HIGH DURATION*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_HIGH_DURN_ADDR,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *durn_u8 = data_u8;
            break;
        case BMA2x2_SLOPE_DURN:
            /*SLOPE DURATION*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_SLOPE_DURN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *durn_u8 = BMA2x2_GET_BITSLICE
                       (data_u8, BMA2x2_SLOPE_DURN);
            break;
        case BMA2x2_SLOW_NO_MOTION_DURN:
            /*SLO NO MOT DURATION*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_SLOW_NO_MOTION_DURN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *durn_u8 = BMA2x2_GET_BITSLICE
                       (data_u8, BMA2x2_SLOW_NO_MOTION_DURN);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set the duration of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_DURN      -> register 0x22 bit form 0 to 7
 *  @note HIGH_DURN     -> register 0x25 bit form 0 to 7
 *  @note SLOPE_DURN        -> register 0x27 bit form 0 to 1
 *  @note SLO_NO_MOT_DURN -> register 0x27 bit form 2 to 7
 *
 *  @param channel_u8: The value of duration select
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_DURN
 *               1    | BMA2x2_ACCEL_HIGH_DURN
 *               2    | BMA2x2_ACCEL_SLOPE_DURN
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_DURN
 *
 *  @param durn_u8: The value of duration
 *
 *  @note :
 *     Duration           |    result
 * -----------------------| ------------------
 * BMA2x2_ACCEL_LOW_DURN  | Low-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 20ms
 * BMA2x2_ACCEL_HIGH_DURN | high-g interrupt trigger
 *         -              | delay according to([durn_u8 +1]*2)ms
 *         -              | range from 2ms to 512ms. default is 32ms
 * BMA2x2_ACCEL_SLOPE_DURN| slope interrupt trigger
 *         -              | if[durn_u8<1:0>+1] consecutive data points
 *         -              | are above the slope interrupt threshold
 * SLO_NO_MOT_DURN        | Refer data sheet for clear information
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_durn(u8 channel_u8,
        u8 durn_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write duration data */
        switch (channel_u8)
        {
        case BMA2x2_LOW_DURN:
            /*LOW DURATION*/
            data_u8 = durn_u8;
            com_rslt = bma2x2_write_reg(BMA2x2_LOW_DURN_ADDR,
                                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_HIGH_DURN:
            /*HIGH DURATION*/
            data_u8 = durn_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_HIGH_DURN_ADDR,
                           &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOPE_DURN:
            /*SLOPE DURATION*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_SLOPE_DURN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_SLOPE_DURN, durn_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_SLOPE_DURN_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_NO_MOTION_DURN:
            /*SLO NO MOT DURATION*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_SLOW_NO_MOTION_DURN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_SLOW_NO_MOTION_DURN, durn_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_SLOW_NO_MOTION_DURN_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get the threshold of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_THRES     -> register 0x23 bit form 0 to 7
 *  @note HIGH_THRES        -> register 0x26 bit form 0 to 7
 *  @note SLOPE_THRES       -> register 0x28 bit form 0 to 7
 *  @note SLO_NO_MOT_THRES -> register 0x29 bit form 0 to 7
 *
 *  @param channel_u8: The value of threshold selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_THRES
 *               1    | BMA2x2_ACCEL_HIGH_THRES
 *               2    | BMA2x2_ACCEL_SLOPE_THRES
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_THRES
 *
 *  @param thres_u8: The threshold value of selected interrupts
 *
 *  @note : LOW-G THRESHOLD
 *     Threshold                    |    result
 * ---------------------------------| ------------------
 * BMA2x2_ACCEL_LOW_THRES           | Low-threshold interrupt trigger
 *                                  | according to(thres_u8 * 7.81) mg
 *                                  | range from 0g to 1.992g
 *                                  | default is 375mg
 *  @note : HIGH-G THRESHOLD
 *  @note Threshold of high-g interrupt according to accel g range
 *    g-range           |      High-g threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 7.81) mg
 *     4g               |    (thres_u8 * 15.63) mg
 *     8g               |    (thres_u8 * 31.25) mg
 *     16g              |    (thres_u8 * 62.5) mg
 *
 *  @note : SLOPE THRESHOLD
 *  @note Threshold of slope interrupt according to accel g range
 *    g-range           |      Slope threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *  @note : SLOW NO MOTION THRESHOLD
 *  @note Threshold of slow no motion interrupt according to accel g range
 *    g-range           |   slow no motion threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_thres(u8 channel_u8,
        u8 *thres_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* Read the threshold value */
        case BMA2x2_LOW_THRES:
            /*LOW THRESHOLD*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_LOW_THRES_ADDR,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *thres_u8 = data_u8;
            break;
        case BMA2x2_HIGH_THRES:
            /*HIGH THRESHOLD*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_HIGH_THRES_ADDR,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *thres_u8 = data_u8;
            break;
        case BMA2x2_SLOPE_THRES:
            /*SLOPE THRESHOLD*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_SLOPE_THRES_ADDR,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *thres_u8 = data_u8;
            break;
        case BMA2x2_SLOW_NO_MOTION_THRES:
            /*SLO NO MOT THRESHOLD*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_SLOW_NO_MOTION_THRES_ADDR,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *thres_u8 = data_u8;
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set the threshold of
 *  Low, High, Slope and slow no motion interrupts in the registers
 *  @note LOW_THRES     -> register 0x23 bit form 0 to 7
 *  @note HIGH_THRES        -> register 0x26 bit form 0 to 7
 *  @note SLOPE_THRES       -> register 0x28 bit form 0 to 7
 *  @note SLO_NO_MOT_THRES -> register 0x29 bit form 0 to 7
 *
 *  @param channel_u8: The value of threshold selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *               0    | BMA2x2_ACCEL_LOW_THRES
 *               1    | BMA2x2_ACCEL_HIGH_THRES
 *               2    | BMA2x2_ACCEL_SLOPE_THRES
 *               3    | BMA2x2_ACCEL_SLOW_NO_MOTION_THRES
 *
 *  @param thres_u8: The threshold value of selected interrupts
 *
 *  @note : LOW-G THRESHOLD
 *     Threshold                    |    result
 * ---------------------------------| ------------------
 * BMA2x2_ACCEL_LOW_THRES           | Low-threshold interrupt trigger
 *                                  | according to(thres_u8 * 7.81) mg
 *                                  | range from 0g to 1.992g
 *                                  | default is 375mg
 *  @note : HIGH-G THRESHOLD
 *  @note Threshold of high-g interrupt according to accel g range
 *    g-range           |      High-g threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 7.81) mg
 *     4g               |    (thres_u8 * 15.63) mg
 *     8g               |    (thres_u8 * 31.25) mg
 *     16g              |    (thres_u8 * 62.5) mg
 *
 *  @note : SLOPE THRESHOLD
 *  @note Threshold of slope interrupt according to accel g range
 *    g-range           |      Slope threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *  @note : SLOW NO MOTION THRESHOLD
 *  @note Threshold of slow no motion interrupt according to accel g range
 *    g-range           |   slow no motion threshold
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 3.19) mg
 *     4g               |    (thres_u8 * 7.81) mg
 *     8g               |    (thres_u8 * 15.63) mg
 *     16g              |    (thres_u8 * 31.25) mg
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_thres(u8 channel_u8,
        u8 thres_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the threshold value*/
        case BMA2x2_LOW_THRES:
            /*LOW THRESHOLD*/
            data_u8 = thres_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_LOW_THRES_ADDR, &data_u8,
                           BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_HIGH_THRES:
            /*HIGH THRESHOLD*/
            data_u8 = thres_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_HIGH_THRES_ADDR, &data_u8,
                           BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOPE_THRES:
            /*SLOPE THRESHOLD*/
            data_u8 = thres_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_SLOPE_THRES_ADDR, &data_u8,
                           BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_NO_MOTION_THRES:
            /*SLO NO MOT THRESHOLD*/
            data_u8 = thres_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_SLOW_NO_MOTION_THRES_ADDR,
                           &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the low high hysteresis in the registers 0x24
 *  @note LOW_G_HYST  -> bit form 0 to 1
 *  @note HIGH_G_HYST  -> bit from 6 to 7
 *
 *  @param channel_u8: The value of hysteresis selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *           0        | BMA2x2_ACCEL_LOW_G_HYST
 *           1        | BMA2x2_ACCEL_HIGH_G_HYST
 *
 *  @param hyst_u8: The hysteresis data
 *
 *  @note LOW HYSTERESIS
 *  @note Hysteresis of low-g interrupt according to (hyst_u8 * 125)mg
 *
 *  @note HIGH HYSTERESIS
 *  @note High hysteresis depends on the accel range selection
 *    g-range           |    High Hysteresis
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 125) mg
 *     4g               |    (thres_u8 * 250) mg
 *     8g               |    (thres_u8 * 500) mg
 *     16g              |    (thres_u8 * 1000) mg
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_low_high_g_hyst(u8 channel_u8,
        u8 *hyst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* read the hysteresis data */
        case BMA2x2_LOW_G_HYST:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_LOW_G_HYST_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *hyst_u8 = BMA2x2_GET_BITSLICE
                       (data_u8, BMA2x2_LOW_G_HYST);
            break;
        case BMA2x2_HIGH_G_HYST:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_HIGH_G_HYST_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *hyst_u8 = BMA2x2_GET_BITSLICE
                       (data_u8, BMA2x2_HIGH_G_HYST);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the low high hysteresis in the registers 0x24
 *  @note LOW_G_HYST  -> bit form 0 to 1
 *  @note HIGH_G_HYST  -> bit from 6 to 7
 *
 *  @param channel_u8: The value of hysteresis selection
 *     channel_u8   | result
 *   -----------------| ------------------
 *           0        | BMA2x2_ACCEL_LOW_G_HYST
 *           1        | BMA2x2_ACCEL_HIGH_G_HYST
 *
 *  @param hyst_u8: The hysteresis data
 *
 *  @note LOW HYSTERESIS
 *  @note Hysteresis of low-g interrupt according to (hyst_u8 * 125)mg
 *
 *  @note HIGH HYSTERESIS
 *  @note High hysteresis depends on the accel range selection
 *    g-range           |    High Hysteresis
 *  --------------------|----------------------------
 *     2g               |    (thres_u8 * 125) mg
 *     4g               |    (thres_u8 * 250) mg
 *     8g               |    (thres_u8 * 500) mg
 *     16g              |    (thres_u8 * 1000) mg
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_low_high_g_hyst(u8 channel_u8,
        u8 hyst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write the hysteresis data  */
        case BMA2x2_LOW_G_HYST:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_LOW_G_HYST_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_LOW_G_HYST, hyst_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_LOW_G_HYST_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_HIGH_G_HYST:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_HIGH_G_HYST_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_HIGH_G_HYST, hyst_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_HIGH_G_HYST_REG,
                            &data_u8,  BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  low_g  mode in the registers 0x24 bit 2
 *
 *
 *  @param low_g_mode_u8: The value of Low_G mode
 *      low_g_mode_u8   |  g-result
 *  --------------------|----------------------------
 *     0x00             | LOW_G_SINGLE_AXIS_MODE
 *     0x01             | LOW_G_SUMMING_MODE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_low_g_mode(u8 *low_g_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the low-g mode*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_LOW_G_INTR_MODE_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *low_g_mode_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                             BMA2x2_LOW_G_INTR_MODE);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  low_g  mode in the registers 0x24 bit 2
 *
 *
 *  @param low_g_mode_u8: The value of Low_G mode
 *    low_g_mode_u8   |    result
 *  --------------------|----------------------------
 *     0x00             | LOW_G_SINGLE_AXIS_MODE
 *     0x01             | LOW_G_SUMMING_MODE
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_low_g_mode(u8 low_g_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the low-g mode*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_LOW_G_INTR_MODE_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_LOW_G_INTR_MODE, low_g_mode_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_LOW_G_INTR_MODE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the tap duration in the register 0x2A bit form 0 to 2
 *
 *
 *  @param tap_durn_u8: The value of tap duration
 *    tap_durn_u8     |    result
 *  --------------------|----------------------------
 *     0x00             | TAP_DURN_50_MS
 *     0x01             | TAP_DURN_100_MS
 *     0x02             | TAP_DURN_150_MS
 *     0x03             | TAP_DURN_200_MS
 *     0x04             | TAP_DURN_250_MS
 *     0x05             | TAP_DURN_375_MS
 *     0x06             | TAP_DURN_500_MS
 *     0x07             | TAP_DURN_700_MS
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_durn(u8 *tap_durn_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the tap duration*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_DURN_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *tap_durn_u8 = BMA2x2_GET_BITSLICE
                       (data_u8, BMA2x2_TAP_DURN);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the tap duration in the register 0x2A bit form 0 to 2
 *
 *
 *  @param tap_durn_u8: The value of tap duration
 *    tap_durn_u8     |    result
 *  --------------------|----------------------
 *     0x00             | TAP_DURN_50_MS
 *     0x01             | TAP_DURN_100_MS
 *     0x02             | TAP_DURN_150_MS
 *     0x03             | TAP_DURN_200_MS
 *     0x04             | TAP_DURN_250_MS
 *     0x05             | TAP_DURN_375_MS
 *     0x06             | TAP_DURN_500_MS
 *     0x07             | TAP_DURN_700_MS
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_durn(u8 tap_durn_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the tap duration */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_TAP_DURN_REG, &data_u8,
                       BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_TAP_DURN, tap_durn_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_TAP_DURN_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the tap shock form the register 0x2A bit 6
 *
 *
 *
 *  @param tap_shock_u8: The value of tap shock
 *    tap_shock_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_SHOCK_50_MS
 *     0x01             | TAP_SHOCK_75_MS
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_shock(u8 *tap_shock_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read tap shock value */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_SHOCK_DURN_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *tap_shock_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                            BMA2x2_TAP_SHOCK_DURN);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the tap shock form the register 0x2A bit 6
 *
 *
 *
 *  @param tap_shock_u8: The value of tap shock
 *    tap_shock_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_SHOCK_50_MS
 *     0x01             | TAP_SHOCK_75_MS
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_shock(u8 tap_shock_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write tap shock value*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_SHOCK_DURN_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_TAP_SHOCK_DURN, tap_shock_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_TAP_SHOCK_DURN_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the tap quiet in the register 0x2A bit 7
 *
 *
 *
 *  @param  tap_quiet_u8 : The value of tap quiet
 *    tap_quiet_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_QUIET_30_MS
 *     0x01             | TAP_QUIET_20_MS
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_quiet(u8 *tap_quiet_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the tap quiet value*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_QUIET_DURN_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *tap_quiet_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_TAP_QUIET_DURN);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the tap quiet in the register 0x2A bit 7
 *
 *
 *
 *  @param  tap_quiet_u8 : The value of tap quiet
 *    tap_quiet_u8    |    result
 *  --------------------|----------------------
 *     0x00             | TAP_QUIET_30_MS
 *     0x01             | TAP_QUIET_20_MS
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_quiet(u8 tap_quiet_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the tap quiet value*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_QUIET_DURN_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_TAP_QUIET_DURN, tap_quiet_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_TAP_QUIET_DURN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the tap threshold in the register 0x2B bit from 0 to 4
 *
 *
 *
 *  @param tap_thres_u8 : The value of tap threshold
 *  @note Tap threshold of single and double tap corresponding
 *     to accel range
 *     range            |    Tap threshold
 *  --------------------|----------------------
 *     2g               | (tap_thres_u8 * 62.5)mg
 *     4g               | (tap_thres_u8 * 125)mg
 *     8g               | (tap_thres_u8 * 250)mg
 *     16g              | (tap_thres_u8 * 500)mg
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_thres(u8 *tap_thres_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the tap threshold*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_THRES_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *tap_thres_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_TAP_THRES);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the tap threshold in the register 0x2B bit from 0 to 4
 *
 *
 *
 *  @param tap_thres_u8 : The value of tap threshold
 *  @note Tap threshold of single and double tap corresponding to accel range
 *     range            |    Tap threshold
 *  --------------------|----------------------
 *     2g               | (tap_thres_u8 * 62.5)mg
 *     4g               | (tap_thres_u8 * 125)mg
 *     8g               | (tap_thres_u8 * 250)mg
 *     16g              | (tap_thres_u8 * 500)mg
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_thres(u8 tap_thres_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_THRES_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_TAP_THRES, tap_thres_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_TAP_THRES_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the tap sample in the register 0x2B bit 6 and 7
 *
 *
 *
 *  @param   *tap_sample_u8 : The value of tap sample
 *     tap_sample_u8  |    result
 *  --------------------|----------------------
 *     0x00             | 2 samples
 *     0x01             | 4 samples
 *     0x02             | 8 samples
 *     0x03             | 16 samples
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_tap_sample(u8 *tap_sample_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read tap samples */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_TAP_SAMPLES_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *tap_sample_u8 = BMA2x2_GET_BITSLICE
                         (data_u8, BMA2x2_TAP_SAMPLES);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the tap sample in the register 0x2B bit 6 and 7
 *
 *
 *
 *  @param   *tap_sample_u8 : The value of tap sample
 *     tap_sample_u8  |    result
 *  --------------------|----------------------
 *     0x00             | 2 samples
 *     0x01             | 4 samples
 *     0x02             | 8 samples
 *     0x03             | 16 samples
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_tap_sample(u8 tap_sample_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write tap samples */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr, BMA2x2_TAP_SAMPLES_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_TAP_SAMPLES, tap_sample_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_TAP_SAMPLES_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the orient mode in the register 0x2C bit 0 and 1
 *
 *
 *
 *  @param orient_mode_u8 : The value of orient mode
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | symmetrical
 *     0x01             | high asymmetrical
 *     0x02             | low asymmetrical
 *     0x03             | symmetrical
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_mode(u8 *orient_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_ORIENT_MODE_REG, &data_u8,
                       BMA2x2_GEN_READ_WRITE_LENGTH);
        *orient_mode_u8 = BMA2x2_GET_BITSLICE(
                              data_u8, BMA2x2_ORIENT_MODE);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the orient mode in the register 0x2C bit 0 and 1
 *
 *
 *
 *  @param orient_mode_u8 : The value of orient mode
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | symmetrical
 *     0x01             | high asymmetrical
 *     0x02             | low asymmetrical
 *     0x03             | symmetrical
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_mode(u8 orient_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_MODE_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_ORIENT_MODE, orient_mode_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_ORIENT_MODE_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the orient block in the register 0x2C bit 2 and 3
 *
 *
 *
 *  @param orient_block_u8 : The value of orient block
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | no blocking
 *     0x01             | theta blocking or
 *                      | acceleration slope in any axis > 1.5g
 *     0x02             | theta blocking or
 *                      | acceleration slope in any axis > 0.2g
 *                      | acceleration in any axis > 1.5g
 *     0x03             | theta blocking or
 *                      | acceleration slope in any axis > 0.4g
 *                      | acceleration in any axis > 1.5g
 *                      | value of orient is not stable for at lease 100ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_block(
    u8 *orient_block_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* Read the orient block data */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_BLOCK_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *orient_block_u8 = BMA2x2_GET_BITSLICE
                           (data_u8, BMA2x2_ORIENT_BLOCK);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the orient block in the register 0x2C bit 2 and 3
 *
 *
 *
 *  @param orient_block_u8 : The value of orient block
 *     orient_mode_u8 |    result
 *  --------------------|------------------
 *     0x00             | no blocking
 *     0x01             | theta blocking or
 *                      | acceleration slope in any axis > 1.5g
 *     0x02             | theta blocking or
 *                      | acceleration slope in any axis > 0.2g
 *                      | acceleration in any axis > 1.5g
 *     0x03             | theta blocking or
 *                      | acceleration slope in any axis > 0.4g
 *                      | acceleration in any axis > 1.5g
 *                      | value of orient is not stable for at lease 100ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_block(u8 orient_block_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the orient block data */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_BLOCK_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_ORIENT_BLOCK, orient_block_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_ORIENT_BLOCK_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the orient hysteresis in the register 0x2C bit 4 to 6
 *
 *
 *
 *  @param orient_hyst_u8 : The value of orient hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_hyst(u8 *orient_hyst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the orient hysteresis data*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_HYST_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *orient_hyst_u8 = BMA2x2_GET_BITSLICE
                          (data_u8, BMA2x2_ORIENT_HYST);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the orient hysteresis in the register 0x2C bit 4 to 6
 *
 *
 *
 *  @param orient_hyst_u8 : The value of orient hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_hyst(u8 orient_hyst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the orient hysteresis data */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_HYST_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_ORIENT_HYST, orient_hyst_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_ORIENT_HYST_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief  This API is used to get
 *  the theta value of orient and flat interrupts
 *  @note ORIENT_THETA -> register 0x2D bit 0 to 5
 *  @note FLAT_THETA   -> register 0x2E bit 0 to 5
 *
 *  @param channel_u8: The value of theta selection
 *     channel_u8     |    result
 *  --------------------|------------------
 *     0x00             | BMA2x2_ACCEL_ORIENT_THETA
 *     0x01             | BMA2x2_ACCEL_FLAT_THETA
 * @note
 * @note FLAT_THETA : Defines a blocking angle between 0 deg to 44.8 deg
 * @note ORIENT_THETA : Defines threshold for detection of flat position
 *                in range from 0 deg to 44.8 deg
 *
 *  @param theta_u8: The value of theta
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_theta(u8 channel_u8,
        u8 *theta_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write theta value*/
        case BMA2x2_ORIENT_THETA:
            /*ORIENT THETA*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_THETA_BLOCK_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            *theta_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_THETA_BLOCK);
            break;
        case BMA2x2_FLAT_THETA:
            /*FLAT THETA*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_THETA_FLAT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *theta_u8 = data_u8;
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief  This API is used to set
 *  the theta value of orient and flat interrupts
 *  @note ORIENT_THETA -> register 0x2D bit 0 to 5
 *  @note FLAT_THETA   -> register 0x2E bit 0 to 5
 *
 *  @param channel_u8: The value of theta selection
 *     channel_u8     |    result
 *  --------------------|------------------
 *     0x00             | BMA2x2_ACCEL_ORIENT_THETA
 *     0x01             | BMA2x2_ACCEL_FLAT_THETA
 * @note
 * @note FLAT_THETA : Defines a blocking angle between 0 deg to 44.8 deg
 * @note ORIENT_THETA : Defines threshold for detection of flat position
 *                in range from 0 deg to 44.8 deg
 *
 *  @param theta_u8: The value of theta
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_theta(u8 channel_u8,
        u8 theta_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        /* write flat value */
        case BMA2x2_ORIENT_THETA:
            /*ORIENT THETA*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_THETA_BLOCK_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_THETA_BLOCK, theta_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_THETA_BLOCK_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_FLAT_THETA:
            /*FLAT THETA*/
            data_u8 = theta_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_THETA_FLAT_REG,
                           &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the interrupt enable of orient ud_enable in the register 0x2D bit 6
 *
 *
 *  @param orient_enable_u8 : The value of orient ud_enable
 *     orient_enable_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | Generates Interrupt
 *     0x01                   | Do not generate interrupt
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_orient_enable(u8 *orient_enable_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_UD_ENABLE_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *orient_enable_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ORIENT_UD_ENABLE);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the interrupt enable of orient ud_enable in the register 0x2D bit 6
 *
 *
 *  @param orient_enable_u8 : The value of orient ud_enable
 *     orient_enable_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | Generates Interrupt
 *     0x01                   | Do not generate interrupt
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_orient_enable(u8 orient_enable_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ORIENT_UD_ENABLE_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_ORIENT_UD_ENABLE, orient_enable_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_ORIENT_UD_ENABLE_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the interrupt enable of flat hysteresis("flat_hy)
 *  in the register 0x2F bit 0 to 2
 *
 *
 *
 *
 *  @param flat_hyst_u8 : The value of flat hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_flat_hyst(u8 *flat_hyst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_FLAT_HYST_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *flat_hyst_u8 = BMA2x2_GET_BITSLICE
                        (data_u8, BMA2x2_FLAT_HYST);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the interrupt enable of flat hysteresis("flat_hy)
 *  in the register 0x2F bit 0 to 2
 *
 *
 *
 *
 *  @param flat_hyst_u8 : The value of flat hysteresis
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_flat_hyst(u8 flat_hyst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_FLAT_HYST_REG,
                       &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_FLAT_HYST, flat_hyst_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_FLAT_HYST_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the interrupt enable of flat hold time(flat_hold_time)
 *  in the register 0x2F bit 4 and 5
 *
 *
 *  @param  flat_hold_time_u8 : The value of flat hold time
 *     flat_hold_time_u8    |    result
 *  ------------------------- |------------------
 *     0x00                   | 0ms
 *     0x01                   | 512ms
 *     0x02                   | 1024ms
 *     0x03                   | 2048ms
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_flat_hold_time(
    u8 *flat_hold_time_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the flat hold time */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_FLAT_HOLD_TIME_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *flat_hold_time_u8 = BMA2x2_GET_BITSLICE
                             (data_u8, BMA2x2_FLAT_HOLD_TIME);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the interrupt enable of flat hold time(flat_hold_time)
 *  in the register 0x2F bit 4 and 5
 *
 *
 *  @param  flat_hold_time_u8 : The value of flat hold time
 *     flat_hold_time_u8    |    result
 *  ------------------------- |------------------
 *     0x00                   | 0ms
 *     0x01                   | 512ms
 *     0x02                   | 1024ms
 *     0x03                   | 2048ms
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_flat_hold_time(
    u8 flat_hold_time_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the flat hold time */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_FLAT_HOLD_TIME_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_FLAT_HOLD_TIME, flat_hold_time_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_FLAT_HOLD_TIME_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the fifo water mark level trigger in the register 0x30 bit from 0 to 5
 *
 *
 *
 *
 *  @param fifo_wml_trig: The value of fifo watermark trigger level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_wml_trig(
    u8 *fifo_wml_trig)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the fifo water mark trigger */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_FIFO_WML_TRIG_RETAIN_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *fifo_wml_trig = BMA2x2_GET_BITSLICE
                         (data_u8, BMA2x2_FIFO_WML_TRIG_RETAIN);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the fifo water mark level trigger in the register 0x30 bit from 0 to 5
 *
 *
 *
 *
 *  @param fifo_wml_trig: The value of fifo watermark trigger level
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_fifo_wml_trig(
    u8 fifo_wml_trig)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 power_mode = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (fifo_wml_trig < BMA2x2_FIFO_WML_RANGE)
        {
            /* write the fifo watermark trigger*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_FIFO_WML_TRIG_RETAIN_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_FIFO_WML_TRIG_RETAIN,
                       fifo_wml_trig);
            com_rslt += bma2x2_get_power_mode(&power_mode);
            com_rslt += bma2x2_set_power_mode(BMA2x2_MODE_STANDBY);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_FIFO_WML_TRIG_RETAIN_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            com_rslt += bma2x2_set_power_mode(power_mode);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is for to get
 *  the self test axis(self_test_axis) in the register ox32 bit 0 to 2
 *
 *
 *
 *  @param selftest_axis_u8 : The value of selftest axis
 *     selftest_axis_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | self test disable
 *     0x01                   | x-axis
 *     0x02                   | y-axis
 *     0x03                   | z-axis
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_selftest_axis(
    u8 *selftest_axis_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the self test axis*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_SELFTEST_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *selftest_axis_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_SELFTEST);
    }
    return com_rslt;
}
/*!
 *  @brief This API is for to set
 *  the self test axis(self_test_axis) in the register ox32 bit 0 to 2
 *
 *
 *
 *  @param selftest_axis_u8 : The value of selftest axis
 *     selftest_axis_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | self test disable
 *     0x01                   | x-axis
 *     0x02                   | y-axis
 *     0x03                   | z-axis
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_selftest_axis(
    u8 selftest_axis_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (selftest_axis_u8 < BMA2x2_SELF_TEST_AXIS_RANGE)
        {
            /* write the self test axis*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SELFTEST_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_ENABLE_SELFTEST, selftest_axis_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_SELFTEST_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is for to get
 *  the Self Test sign(selftest_sign) in the register 0x32 bit 2
 *
 *
 *
 *  @param selftest_sign_u8 : The value of self test sign
 *     selftest_sign_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | negative sign
 *     0x01                   | positive sign
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_selftest_sign(
    u8 *selftest_sign_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read self test sign */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_NEG_SELFTEST_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *selftest_sign_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_NEG_SELFTEST);
    }
    return com_rslt;
}
/*!
 *  @brief This API is for to set
 *  the Self Test sign(selftest_sign) in the register 0x32 bit 2
 *
 *
 *
 *  @param selftest_sign_u8 : The value of self test sign
 *     selftest_sign_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | negative sign
 *     0x01                   | positive sign
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_selftest_sign(
    u8 selftest_sign_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (selftest_sign_u8 <
                BMA2x2_SELF_TEST_SIGN_RANGE)
        {
            /* write self test sign */
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_NEG_SELFTEST_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_NEG_SELFTEST, selftest_sign_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_NEG_SELFTEST_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the nvm program mode(nvm_prog_mode)in the register 0x33 bit 0
 *
 *
 *  @param  nvmprog_mode_u8 : The value of nvm program mode
 *     nvmprog_mode_u8      |    result
 *  ------------------------- |------------------
 *     0x00                   | Disable program mode
 *     0x01                   | Enable program mode
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_nvmprog_mode(
    u8 *nvmprog_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the nvm program mode*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_UNLOCK_EE_PROG_MODE_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *nvmprog_mode_u8 = BMA2x2_GET_BITSLICE
                           (data_u8, BMA2x2_UNLOCK_EE_PROG_MODE);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the nvm program mode(nvm_prog_mode)in the register 0x33 bit 0
 *
 *
 *  @param  nvmprog_mode_u8 : The value of nvm program mode
 *     nvmprog_mode_u8      |    result
 *  ------------------------- |------------------
 *     0x00                   | Disable program mode
 *     0x01                   | Enable program mode
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_nvmprog_mode(u8 nvmprog_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the nvm program mode*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_UNLOCK_EE_PROG_MODE_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_UNLOCK_EE_PROG_MODE, nvmprog_mode_u8);
        com_rslt += bma2x2_write_reg
                    (BMA2x2_UNLOCK_EE_PROG_MODE_REG,
                     &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the value of nvm program trig in the register 0x33 bit 1
 *
 *
 *
 *
 *  @param nvprog_trig_u8: The value of nvm program trig
 *     nvprog_trig_u8       |    result
 *  ------------------------- |------------------
 *     0x00                   | Do not trigger nvm program
 *     0x01                   | Trigger nvm program
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_nvprog_trig(u8 nvprog_trig_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* set the nvm program trigger */
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_START_EE_PROG_TRIG_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_START_EE_PROG_TRIG, nvprog_trig_u8);
        com_rslt += bma2x2_write_reg
                    (BMA2x2_START_EE_PROG_TRIG_REG,
                     &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the nvm program ready in the register bit 2
 *
 *
 *  @param nvprog_ready_u8: The value of nvm program ready
 *     nvprog_ready_u8      |    result
 *  ------------------------- |------------------
 *     0x00                   | nvm write/update operation is in progress
 *     0x01                   | nvm is ready to accept a new write
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_nvmprog_ready(u8 *nvprog_ready_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the nvm program ready*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_EE_PROG_READY_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *nvprog_ready_u8 = BMA2x2_GET_BITSLICE
                           (data_u8, BMA2x2_EE_PROG_READY);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the nvm program ready in the register bit 2
 *
 *
 *  @param nvprog_remain_u8: The value of nvm program ready
 *     nvprog_remain_u8     |    result
 *  ------------------------- |------------------
 *     0x00                   | nvm write/update operation is in progress
 *     0x01                   | nvm is ready to accept a new write
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_nvmprog_remain(u8 *nvprog_remain_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /* Check the struct p_bma2x2 is empty */
    if (BMA2x2_NULL == p_bma2x2)
    {
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the nvm program ready*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_EE_REMAIN_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        *nvprog_remain_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_EE_REMAIN);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get the enable status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  spi3_u8 : The value of SPI 3 or 4 wire enable
 *     spi3_u8              |    result
 *  ------------------------- |------------------
 *     0x00                   |     spi4
 *     0x01                   |     spi3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_spi3(u8 *spi3_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* read the spi status*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_SPI_MODE_3_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *spi3_u8 = BMA2x2_GET_BITSLICE
                   (data_u8, BMA2x2_ENABLE_SPI_MODE_3);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set the enable status of spi3
 *  in the register 0x34 bit 0
 *
 *
 *
 *  @param  spi3_u8 : The value of SPI 3 or 4 wire enable
 *     spi3_u8              |    result
 *  ------------------------- |------------------
 *     0x00                   |     spi4
 *     0x01                   |     spi3
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_spi3(u8 spi3_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* write the spi status*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_ENABLE_SPI_MODE_3_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_ENABLE_SPI_MODE_3, spi3_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_ENABLE_SPI_MODE_3_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get the i2c
 *  watch dog timer period and I2C interface mode is selected
 *  in the register 0x34 bit 1 and 2
 *
 *
 *  @param channel_u8: The i2c option selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_I2C_SELECT
 *        1                   |   BMA2x2_ACCEL_I2C_ENABLE
 *
 *  @param i2c_wdt_u8: watch dog timer period
 *  and I2C interface mode is selected
 *     BMA2x2_ACCEL_I2C_SELECT|    result
 *  ------------------------- |------------------
 *     0x00                   | Disable the watchdog at SDI pin
 *     0x01                   | Enable watchdog
 *
 *     BMA2x2_I2C_ENABLE      |    result
 *  ------------------------- |------------------
 *     0x00                   | 1ms
 *     0x01                   | 50ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_i2c_wdt(u8 channel_u8,
        u8 *i2c_wdt_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_I2C_SELECT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_I2C_WDT_PERIOD_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *i2c_wdt_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                              BMA2x2_I2C_WDT_PERIOD);
            break;
        case BMA2x2_I2C_ENABLE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_I2C_WDT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *i2c_wdt_u8 = BMA2x2_GET_BITSLICE
                          (data_u8, BMA2x2_ENABLE_I2C_WDT);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set the i2c
 *  watch dog timer period and I2C interface mode is selected
 *  in the register 0x34 bit 1 and 2
 *
 *
 *  @param channel_u8: The i2c option selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_I2C_SELECT
 *        1                   |   BMA2x2_ACCEL_I2C_ENABLE
 *
 *  @param i2c_wdt_u8: watch dog timer period
 *  and I2C interface mode is selected
 *     BMA2x2_ACCEL_I2C_SELECT|    result
 *  ------------------------- |------------------
 *     0x00                   | Disable the watchdog at SDI pin
 *     0x01                   | Enable watchdog
 *
 *     BMA2x2_I2C_ENABLE      |    result
 *  ------------------------- |------------------
 *     0x00                   | 1ms
 *     0x01                   | 50ms
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_i2c_wdt(u8 channel_u8,
        u8 i2c_wdt_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_I2C_SELECT:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_I2C_WDT_PERIOD_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_I2C_WDT_PERIOD, i2c_wdt_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_I2C_WDT_PERIOD_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_I2C_ENABLE:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_I2C_WDT_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_I2C_WDT, i2c_wdt_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_I2C_WDT_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  slow compensation(hp_x_enable, hp_y_enable and hp_z_enable) enable
 *  in the register 0x36 bit 0 to 2
 *  @note SLOW_COMP_X -> bit 0
 *  @note SLOW_COMP_Y -> bit 1
 *  @note SLOW_COMP_Z -> bit 2
 *
 *
 *  @param channel_u8: The value of slow compensation selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_SLOW_COMP_X
 *        1                   |   BMA2x2_ACCEL_SLOW_COMP_Y
 *        2                   |   BMA2x2_ACCEL_SLOW_COMP_Z
 *
 *  @param slow_comp_u8: The value of slow compensation enable
 *     slow_comp_u8         |    result
 *  ------------------------- |------------------
 *         0x00               |    Disable
 *        0x01                |    Enable
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_slow_comp(u8 channel_u8,
        u8 *slow_comp_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_SLOW_COMP_X:
            /*SLOW COMP X*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOW_COMP_X_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_comp_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_SLOW_COMP_X);
            break;
        case BMA2x2_SLOW_COMP_Y:
            /*SLOW COMP Y*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOW_COMP_Y_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_comp_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_SLOW_COMP_Y);
            break;
        case BMA2x2_SLOW_COMP_Z:
            /*SLOW COMP Z*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOW_COMP_Z_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *slow_comp_u8 = BMA2x2_GET_BITSLICE
                            (data_u8, BMA2x2_ENABLE_SLOW_COMP_Z);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  slow compensation(hp_x_enable, hp_y_enable and hp_z_enable) enable
 *  in the register 0x36 bit 0 to 2
 *  @note SLOW_COMP_X -> bit 0
 *  @note SLOW_COMP_Y -> bit 1
 *  @note SLOW_COMP_Z -> bit 2
 *
 *
 *  @param channel_u8: The value of slow compensation selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_SLOW_COMP_X
 *        1                   |   BMA2x2_ACCEL_SLOW_COMP_Y
 *        2                   |   BMA2x2_ACCEL_SLOW_COMP_Z
 *
 *  @param slow_comp_u8: The value of slow compensation enable
 *     slow_comp_u8         |    result
 *  ------------------------- |------------------
 *         0x00               |    Disable
 *        0x01                |    Enable
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_slow_comp(u8 channel_u8,
        u8 slow_comp_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_SLOW_COMP_X:
            /*SLOW COMP X*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOW_COMP_X_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_SLOW_COMP_X, slow_comp_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_SLOW_COMP_X_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_COMP_Y:
            /*SLOW COMP Y*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOW_COMP_Y_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_SLOW_COMP_Y, slow_comp_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_SLOW_COMP_Y_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_SLOW_COMP_Z:
            /*SLOW COMP Z*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_ENABLE_SLOW_COMP_Z_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_ENABLE_SLOW_COMP_Z, slow_comp_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_ENABLE_SLOW_COMP_Z_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the status of fast offset compensation(cal_rdy) in the register 0x36
 *  bit 4(Read Only Possible)
 *
 *
 *
 *  @param  cal_rdy_u8: The value of cal_ready
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
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_cal_rdy(u8 *cal_rdy_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_FAST_CAL_RDY_STAT_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *cal_rdy_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                          BMA2x2_FAST_CAL_RDY_STAT);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the status of fast offset compensation(cal_rdy) in the register 0x36
 *  bit 4(Read Only Possible)
 *
 *
 *
 *  @param  cal_trigger_u8: The value of cal_ready
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
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_cal_trigger(u8 cal_trigger_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_CAL_TRIGGER_REG, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                      BMA2x2_CAL_TRIGGER, cal_trigger_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_CAL_TRIGGER_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the offset reset(offset_reset) in the register 0x36
 *  bit 7(Write only possible)
 *
 *
 *
 *  @param  offset_rst_u8: The offset reset value
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_offset_rst(u8 offset_rst_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_RST_OFFSET_REG,
                    &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        data_u8 = BMA2x2_SET_BITSLICE
                  (data_u8, BMA2x2_RST_OFFSET,
                   offset_rst_u8);
        com_rslt += bma2x2_write_reg(
                        BMA2x2_RST_OFFSET_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the status of offset target axis(offset_target_x, offset_target_y and
 *  offset_target_z) and cut_off in the register 0x37
 *  @note CUT_OFF -> bit 0
 *  @note OFFSET_TRIGGER_X -> bit 1 and 2
 *  @note OFFSET_TRIGGER_Y -> bit 3 and 4
 *  @note OFFSET_TRIGGER_Z -> bit 5 and 6
 *
 *
 *  @param channel_u8: The value of offset axis selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_CUT_OFF
 *        1                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_X
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Y
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Z
 *
 *  @param  offset_u8: The offset target value
 *     CUT_OFF                |    result
 *  ------------------------- |------------------
 *        0                   |   1Hz
 *        1                   |   10Hz
 *
 *
 *     OFFSET_TRIGGER         |    result
 *  ------------------------- |------------------
 *        0x00                |   0g
 *        0x01                |   +1g
 *        0x02                |   -1g
 *        0x03                |   0g
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_offset_target(u8 channel_u8,
        u8 *offset_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_CUT_OFF:
            /*CUT-OFF*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_CUTOFF_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                             BMA2x2_COMP_CUTOFF);
            break;
        case BMA2x2_OFFSET_TRIGGER_X:
            /*OFFSET TRIGGER X*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_TARGET_OFFSET_X_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                             BMA2x2_COMP_TARGET_OFFSET_X);
            break;
        case BMA2x2_OFFSET_TRIGGER_Y:
            /*OFFSET TRIGGER Y*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_TARGET_OFFSET_Y_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                             BMA2x2_COMP_TARGET_OFFSET_Y);
            break;
        case BMA2x2_OFFSET_TRIGGER_Z:
            /*OFFSET TRIGGER Z*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_TARGET_OFFSET_Z_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = BMA2x2_GET_BITSLICE
                         (data_u8, BMA2x2_COMP_TARGET_OFFSET_Z);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the status of offset target axis(offset_target_x, offset_target_y and
 *  offset_target_z) and cut_off in the register 0x37
 *  @note CUT_OFF -> bit 0
 *  @note OFFSET_TRIGGER_X -> bit 1 and 2
 *  @note OFFSET_TRIGGER_Y -> bit 3 and 4
 *  @note OFFSET_TRIGGER_Z -> bit 5 and 6
 *
 *
 *  @param channel_u8: The value of offset axis selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_CUT_OFF
 *        1                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_X
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Y
 *        2                   |   BMA2x2_ACCEL_OFFSET_TRIGGER_Z
 *
 *  @param  offset_u8: The offset target value
 *     CUT_OFF                |    result
 *  ------------------------- |------------------
 *        0                   |   1Hz
 *        1                   |   10Hz
 *
 *
 *     OFFSET_TRIGGER         |    result
 *  ------------------------- |------------------
 *        0x00                |   0g
 *        0x01                |   +1g
 *        0x02                |   -1g
 *        0x03                |   0g
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_offset_target(u8 channel_u8,
        u8 offset_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_CUT_OFF:
            /*CUT-OFF*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_CUTOFF_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_COMP_CUTOFF, offset_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_COMP_CUTOFF_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_OFFSET_TRIGGER_X:
            /*OFFSET TARGET X*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_TARGET_OFFSET_X_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_COMP_TARGET_OFFSET_X, offset_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_COMP_TARGET_OFFSET_X_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_OFFSET_TRIGGER_Y:
            /*OFFSET TARGET Y*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_TARGET_OFFSET_Y_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_COMP_TARGET_OFFSET_Y, offset_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_COMP_TARGET_OFFSET_Y_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_OFFSET_TRIGGER_Z:
            /*OFFSET TARGET Z*/
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_COMP_TARGET_OFFSET_Z_REG,
                        &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8, BMA2x2_COMP_TARGET_OFFSET_Z, offset_u8);
            com_rslt += bma2x2_write_reg(
                            BMA2x2_COMP_TARGET_OFFSET_Z_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get the status of offset
 *  (offset_x, offset_y and offset_z) in the registers 0x38,0x39 and 0x3A
 *  @note offset_x -> register 0x38 bit 0 to 7
 *  @note offset_y -> register 0x39 bit 0 to 7
 *  @note offset_z -> register 0x3A bit 0 to 7
 *
 *
 *  @param channel_u8: The value of offset selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_X_AXIS
 *        1                   |   BMA2x2_ACCEL_Y_AXIS
 *        2                   |   BMA2x2_ACCEL_Z_AXIS
 *
 *  @param offset_u8: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_offset(u8 channel_u8,
        s8 *offset_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_X_AXIS:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_OFFSET_X_AXIS_ADDR, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = (s8)data_u8;
            break;
        case BMA2x2_Y_AXIS:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_OFFSET_Y_AXIS_ADDR, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = (s8)data_u8;
            break;
        case BMA2x2_Z_AXIS:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_OFFSET_Z_AXIS_ADDR, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            *offset_u8 = (s8)data_u8;
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set the status of offset
 *  (offset_x, offset_y and offset_z) in the registers 0x38,0x39 and 0x3A
 *  @note offset_x -> register 0x38 bit 0 to 7
 *  @note offset_y -> register 0x39 bit 0 to 7
 *  @note offset_z -> register 0x3A bit 0 to 7
 *
 *
 *  @param channel_u8: The value of offset selection
 *     channel_u8           |    result
 *  ------------------------- |------------------
 *        0                   |   BMA2x2_ACCEL_X_AXIS
 *        1                   |   BMA2x2_ACCEL_Y_AXIS
 *        2                   |   BMA2x2_ACCEL_Z_AXIS
 *
 *  @param offset_u8: The value of offset
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_offset(u8 channel_u8,
        s8 offset_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (channel_u8)
        {
        case BMA2x2_X_AXIS:
            data_u8 = offset_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_OFFSET_X_AXIS_ADDR, &data_u8,
                           BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_Y_AXIS:
            data_u8 = offset_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_OFFSET_Y_AXIS_ADDR, &data_u8,
                           BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        case BMA2x2_Z_AXIS:
            data_u8 = offset_u8;
            com_rslt = bma2x2_write_reg(
                           BMA2x2_OFFSET_Z_AXIS_ADDR, &data_u8,
                           BMA2x2_GEN_READ_WRITE_LENGTH);
            break;
        default:
            com_rslt = E_OUT_OF_RANGE;
            break;
        }
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to get
 *  the status of fifo (fifo_mode) in the register 0x3E bit 6 and 7
 *
 *
 *  @param fifo_mode_u8 : The value of fifo mode
 *     fifo_mode_u8         |    result
 *  ------------------------- |------------------
 *        0x00                |   BYPASS
 *        0x01                |   FIFO
 *        0x02                |   STREAM
 *        0x03                |   RESERVED
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_mode(u8 *fifo_mode_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_FIFO_MODE_REG, &data_u8,
                       BMA2x2_GEN_READ_WRITE_LENGTH);
        *fifo_mode_u8 = BMA2x2_GET_BITSLICE(data_u8,
                                            BMA2x2_FIFO_MODE);
    }
    return com_rslt;
}
/*!
 *  @brief This API is used to set
 *  the status of fifo (fifo_mode) in the register 0x3E bit 6 and 7
 *
 *
 *  @param fifo_mode_u8 : The value of fifo mode
 *     fifo_mode_u8         |    result
 *  ------------------------- |------------------
 *        0x00                |   BYPASS
 *        0x01                |   FIFO
 *        0x02                |   STREAM
 *        0x03                |   RESERVED
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *  @retval -127 -> Null Pointer Error
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_fifo_mode(u8 fifo_mode_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 power_mode = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (fifo_mode_u8 < BMA2x2_FIFO_MODE_RANGE)
        {
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_FIFO_MODE_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE(data_u8,
                                          BMA2x2_FIFO_MODE, fifo_mode_u8);
            data_u8 |= 0x0C;
            /*Power mode is switched to Standby power mode*/
            com_rslt += bma2x2_get_power_mode(&power_mode);
            com_rslt += bma2x2_set_power_mode(BMA2x2_MODE_STANDBY);
            /*Configure the mode in FIFO_CONFIG registers*/
            com_rslt += bma2x2_write_reg(
                            BMA2x2_FIFO_MODE_REG,
                            &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
            if (com_rslt == SUCCESS)
            {
                /*FIFO config is stored in struct p_bma2x2*/
                p_bma2x2->fifo_config = data_u8;
            }
            /*Power mode is reverted to previously set mode */
            com_rslt += bma2x2_set_power_mode(power_mode);

        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API is used to get
 * the axis enable of fifo data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param fifo_data_select_u8 : The value of FIFO axis data select
 *   fifo_data_select_u8    |    result
 *  ------------------------- |------------------
 *        0x00                |   XYZ
 *        0x01                |   Y
 *        0x02                |   X
 *        0x03                |   Z
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_data_select(
    u8 *fifo_data_select_u8)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_FIFO_DATA_SELECT_REG,
                       &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *fifo_data_select_u8 = BMA2x2_GET_BITSLICE(data_u8,
                               BMA2x2_FIFO_DATA_SELECT);
    }
    return com_rslt;
}
/*!
 * @brief This API is used to set
 * the axis enable of fifo data select in the register 0x3E bit 0 and 1
 *
 *
 *  @param fifo_data_select_u8 : The value of FIFO axis data select
 *   fifo_data_select_u8      |    result
 *  ------------------------- |------------------
 *        0x00                |   XYZ
 *        0x01                |   Y
 *        0x02                |   X
 *        0x03                |   Z
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *  @retval -127 -> Null Pointer Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_set_fifo_data_select(
    u8 fifo_data_select_u8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    u8 power_mode = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        if (fifo_data_select_u8 < BMA2x2_FIFO_DATA_SELECT_RANGE)
        {
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr,
                        BMA2x2_FIFO_DATA_SELECT_REG, &data_u8,
                        BMA2x2_GEN_READ_WRITE_LENGTH);
            data_u8 = BMA2x2_SET_BITSLICE
                      (data_u8,
                       BMA2x2_FIFO_DATA_SELECT, fifo_data_select_u8);
            data_u8 |= 0x0C;
            /*Power mode is switched to Standby power mode*/
            com_rslt += bma2x2_get_power_mode(&power_mode);
            com_rslt += bma2x2_set_power_mode(BMA2x2_MODE_STANDBY);
            /* Configure appropriate (X,Y,Z) axes data to be
            available in FIFO*/
            com_rslt += bma2x2_write_reg(
                            BMA2x2_FIFO_DATA_SELECT_REG, &data_u8, 1);
            if (com_rslt == SUCCESS)
            {
                /*FIFO config is stored in struct p_bma2x2*/
                p_bma2x2->fifo_config = data_u8;
            }
            /*Power mode is reverted to previously set mode */
            com_rslt += bma2x2_set_power_mode(power_mode);
        }
        else
        {
            com_rslt = E_OUT_OF_RANGE;
        }
    }
    return com_rslt;
}

/*!
 *  @brief This API reads the FIFO data from the register 0x3F
 *  and store the data in the user defined buffer mapped to the member
 *  of structure "fifo_configuration"
 *
 *  @note Before calling this API user must map the following FIFO settings
 *  required to read the FIFO data to the structure "fifo_configuration"
 *    - Data buffer to store the FIFO data is mapped to
 *      the structure member "fifo_data"
 *    - Number of bytes to be read from FIFO is mapped to
 *      the structure member "fifo_length"
 *
 *  @note The number of bytes to be read from the FIFO is specified in the
 *  member "fifo_length" of the structure "fifo_configuration"
 *
 *  @param[in,out] fifo_conf : Structure containing the FIFO configurations
 *  is passed as input and FIFO data of specified length is obtained as output
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *  @retval -127 -> Null Pointer Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_fifo_data(
    struct fifo_configuration *fifo_conf)
{
    u8 fifo_frame_count = 0;
    u8 fifo_data_bytes = 0;
    u8 fifo_data_select = 0;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL || fifo_conf->fifo_data == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /*Resetting the FIFO data byte index*/
        fifo_conf->accel_byte_start_index = 0;
        /*Frames in FIFO is stored */
        com_rslt = bma2x2_get_fifo_frame_count(&fifo_frame_count);
        /*FIFO data select value is stored*/
        com_rslt += bma2x2_get_fifo_data_select(&fifo_data_select);
        /*Number of bytes in FIFO is calculated*/
        if (fifo_data_select == BMA2x2_FIFO_XYZ_DATA_ENABLED)
        {
            /*Number of bytes in FIFO when XYZ data are enabled*/
            fifo_data_bytes = fifo_frame_count *
                              BMA2x2_FIFO_XYZ_AXES_FRAME_SIZE;
        }
        else
        {
            /*No of bytes in FIFO when single axis data enabled*/
            fifo_data_bytes = fifo_frame_count *
                              BMA2x2_FIFO_SINGLE_AXIS_FRAME_SIZE;
        }
        /*Handled the case where user requests to read more FIFO
        length than available FIFO data*/
        if (fifo_conf->fifo_length > fifo_data_bytes)
        {
            /*Number of bytes in FIFO is read entirely when user
            reads more FIFO data than available*/
            fifo_conf->fifo_length = fifo_data_bytes;
        }
        /*Read the FIFO data*/
        com_rslt += p_bma2x2->BMA2x2_BUS_READ_FUNC(p_bma2x2->dev_addr,
                    BMA2x2_FIFO_DATA_OUTPUT_ADDR, fifo_conf->fifo_data,
                    fifo_conf->fifo_length);
    }
    return com_rslt;
}

/*!
 *  @brief This API extracts the accel data from the FIFO frames
 *
 *  @note The bma2x2_extract_accel() API should be called only after reading
 *  the FIFO data by calling the bma2x2_read_fifo_data() API
 *
 *  @param[in,out] accel_frame      : Instance of the union where accel data
 *                                    in FIFO is parsed and stored
 *
 *  @param[in,out] accel_frame_count: Number of Accel frames requested by user
 *                                    is got as input and number of
 *                                    accel frames parsed and stored is
 *                                    returned as output to user
 *
 *  @param[in, out] fifo_conf       : FIFO configuration structure.
 *                                    It provides the following as input
 *                                        - user defined buffer
 *                                        - length of FIFO data read
 *                                    It returns the accel_byte_start_index
 *                                    (index of accel bytes parsed from FIFO)
 *
 *  @return results of API execution status
 *  @retval 0 -> Success
 *  @retval -127 -> Error
 *
 */
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_extract_accel(union fifo_frame *accel_frame,
        u8 *accel_frame_count, struct fifo_configuration *fifo_conf)
{
    u8 data_index = 0;
    u8 accel_index = 0;
    u8 data_read_length = 0;
    u8 fifo_data_select = 0;
    /*  Variable used to return value of communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = 0;

    if (p_bma2x2 == BMA2x2_NULL || fifo_conf->fifo_data == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty and FIFO data buffer
        not being mapped to  fifo_configuration structure */
        com_rslt = E_BMA2x2_NULL_PTR;
    }
    else
    {
        /* FIFO data enable value is stored in fifo_data_select*/
        fifo_data_select = p_bma2x2->fifo_config &
                           BMA2x2_FIFO_DATA_ENABLED_MASK;
        /* FIFO bytes available for parsing is obtained in
        data_read_length*/
        get_accel_len_to_parse(&data_index, &data_read_length,
                               *accel_frame_count, fifo_data_select, fifo_conf);
        /*Parse the FIFO data from accel byte start index to
        data_read_length*/
        for (; data_index < data_read_length;)
        {
            unpack_accel_frame(accel_frame, &data_index,
                               &accel_index, fifo_data_select, fifo_conf);
        }
        /* update number of accel data read*/
        *accel_frame_count = accel_index;
        /*update the accel byte index*/
        fifo_conf->accel_byte_start_index = data_index;
    }
    return com_rslt;
}

/*!
 *  @brief This API computes the number of bytes of accel FIFO data
 *  which is to be parsed.
 */
static void get_accel_len_to_parse(u8 *data_index, u8 *data_read_length,
                                   u8 accel_frame_count, u8 fifo_data_select,
                                   struct fifo_configuration *fifo_conf)
{
    /*Current data index is set to accel_byte_start_index*/
    *data_index = fifo_conf->accel_byte_start_index;
    /* FIFO bytes corresponding to the requested FIFO frames is obtained*/
    if (fifo_data_select == BMA2x2_FIFO_XYZ_DATA_ENABLED)
    {
        /*Number of bytes in FIFO when XYZ data are enabled*/
        *data_read_length = accel_frame_count *
                            BMA2x2_FIFO_XYZ_AXES_FRAME_SIZE;
    }
    else
    {
        /*No of bytes in FIFO when single axis data enabled*/
        *data_read_length = accel_frame_count *
                            BMA2x2_FIFO_SINGLE_AXIS_FRAME_SIZE;
    }
    if ((*data_read_length) > fifo_conf->fifo_length)
    {
        /*Handling the case where more FIFO frame is requested
        than available*/
        *data_read_length = fifo_conf->fifo_length;
    }
}

/*!
 *  @brief This API is used to parse the accelerometer frame from the
 *  user defined FIFO data buffer mapped to the structure fifo_conf and store
 *  it in the union fifo_frame
 *
 *  @note It update the data_index value which is used to store the index of
 *  the current data byte which is parsed.
 *
 *  @note The parsed accel frames stored in the union fifo_conf contains data
 *  in accordance with the enabled data axes to be stored in FIFO
 *  (XYZ axes or individual axis)
 */
static void unpack_accel_frame(union fifo_frame *accel_frame, u8 *data_index,
                               u8 *accel_index, u8 fifo_data_select,
                               struct fifo_configuration *fifo_conf)
{
    u16 data_lsb = 0;
    u16 data_msb = 0;

    switch (fifo_data_select)
    {

    case BMA2x2_FIFO_XYZ_DATA_ENABLED:
        unpack_accel_xyz(&accel_frame[*accel_index], data_index,
                         fifo_conf);
        /* Accel index is updated*/
        (*accel_index)++;
        break;

    case BMA2x2_FIFO_X_DATA_ENABLED:
        /* Accel raw x data */
        data_lsb = fifo_conf->fifo_data[(*data_index)++];
        data_msb = fifo_conf->fifo_data[(*data_index)++];
        accel_frame[*accel_index].x = (u16)((data_msb << 8) | data_lsb);

        /* Resolution based data from FIFO is updated */
        if (V_BMA2x2RESOLUTION_U8 == BMA2x2_12_RESOLUTION)
        {
            accel_frame[*accel_index].x =
                (accel_frame[*accel_index].x >> 4);
        }
        else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_14_RESOLUTION)
        {
            accel_frame[*accel_index].x =
                (accel_frame[*accel_index].x >> 2);
        }
        else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_10_RESOLUTION)
        {
            accel_frame[*accel_index].x =
                (accel_frame[*accel_index].x >> 6);
        }
        /* Accel index is updated*/
        (*accel_index)++;
        break;

    case BMA2x2_FIFO_Y_DATA_ENABLED:
        /* Accel raw y data */
        data_lsb = fifo_conf->fifo_data[(*data_index)++];
        data_msb = fifo_conf->fifo_data[(*data_index)++];
        accel_frame[*accel_index].y = (u16)((data_msb << 8) | data_lsb);

        /* Resolution based data from FIFO is updated */
        if (V_BMA2x2RESOLUTION_U8 == BMA2x2_12_RESOLUTION)
        {
            accel_frame[*accel_index].y =
                (accel_frame[*accel_index].y >> 4);
        }
        else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_14_RESOLUTION)
        {
            accel_frame[*accel_index].y =
                (accel_frame[*accel_index].y >> 2);
        }
        else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_10_RESOLUTION)
        {
            accel_frame[*accel_index].y =
                (accel_frame[*accel_index].y >> 6);
        }
        /* Accel index is updated*/
        (*accel_index)++;
        break;

    case BMA2x2_FIFO_Z_DATA_ENABLED:
        /* Accel raw z data */
        data_lsb = fifo_conf->fifo_data[(*data_index)++];
        data_msb = fifo_conf->fifo_data[(*data_index)++];
        accel_frame[*accel_index].z = (u16)((data_msb << 8) | data_lsb);

        /* Resolution based data from FIFO is updated */
        if (V_BMA2x2RESOLUTION_U8 == BMA2x2_12_RESOLUTION)
        {
            accel_frame[*accel_index].z =
                (accel_frame[*accel_index].z >> 4);
        }
        else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_14_RESOLUTION)
        {
            accel_frame[*accel_index].z =
                (accel_frame[*accel_index].z >> 2);
        }
        else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_10_RESOLUTION)
        {
            accel_frame[*accel_index].z =
                (accel_frame[*accel_index].z >> 6);
        }
        /* Accel index is updated*/
        (*accel_index)++;
        break;

    default:
        break;
    }
}

/*!
 *  @brief This API is used to parse the accelerometer data and
 *  store it in the union fifo_frame
 *  It also updates the data_index value which stores the index of
 *  the current data byte which is parsed
 *
 */
static void unpack_accel_xyz(union fifo_frame *accel_frame, u8 *data_index,
                             struct fifo_configuration *fifo_conf)
{
    u16 data_lsb = 0;
    u16 data_msb = 0;

    /* Accel raw x data */
    data_lsb = fifo_conf->fifo_data[(*data_index)++];
    data_msb = fifo_conf->fifo_data[(*data_index)++];
    accel_frame->accel_data.x = (u16)((data_msb << 8) | data_lsb);

    /* Accel raw y data */
    data_lsb = fifo_conf->fifo_data[(*data_index)++];
    data_msb = fifo_conf->fifo_data[(*data_index)++];
    accel_frame->accel_data.y = (u16)((data_msb << 8) | data_lsb);

    /* Accel raw z data */
    data_lsb = fifo_conf->fifo_data[(*data_index)++];
    data_msb = fifo_conf->fifo_data[(*data_index)++];
    accel_frame->accel_data.z = (u16)((data_msb << 8) | data_lsb);

    /* Resolution based data from FIFO is updated */
    if (V_BMA2x2RESOLUTION_U8 == BMA2x2_12_RESOLUTION)
    {
        accel_frame->accel_data.x = (accel_frame->accel_data.x >> 4);
        accel_frame->accel_data.y = (accel_frame->accel_data.y >> 4);
        accel_frame->accel_data.z = (accel_frame->accel_data.z >> 4);
    }
    else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_14_RESOLUTION)
    {
        accel_frame->accel_data.x = (accel_frame->accel_data.x >> 2);
        accel_frame->accel_data.y = (accel_frame->accel_data.y >> 2);
        accel_frame->accel_data.z = (accel_frame->accel_data.z >> 2);
    }
    else if (V_BMA2x2RESOLUTION_U8 == BMA2x2_10_RESOLUTION)
    {
        accel_frame->accel_data.x = (accel_frame->accel_data.x >> 6);
        accel_frame->accel_data.y = (accel_frame->accel_data.y >> 6);
        accel_frame->accel_data.z = (accel_frame->accel_data.z >> 6);
    }
}

/*!
 * @brief This API is used to read the temp
 * from register 0x08
 *
 *
 *
 *  @param  temp_s8: The value of temperature
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_temp(s8 *temp_s8)
{
    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_TEMP_ADDR,
                       &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *temp_s8 = (s8)data_u8;
    }
    return com_rslt;
}
/*!
 * @brief This API reads accelerometer data X,Y,Z values and
 * temperature data from location 02h to 08h
 *
 *
 *
 *
 *  @param accel : The value of accel xyz and temperature data
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_xyzt(
    struct bma2x2_accel_data_temp *accel)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8 data_u8[BMA2x2_ACCEL_XYZ_TEMP_DATA_SIZE] =
    {
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE,
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE,
        BMA2x2_INIT_VALUE, BMA2x2_INIT_VALUE,
        BMA2x2_INIT_VALUE
    };
    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        switch (V_BMA2x2RESOLUTION_U8)
        {
        case BMA2x2_12_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_ACCEL_X12_LSB_REG,
                        data_u8, BMA2x2_ACCEL_BW_MIN_RANGE);

            /* read x data_u8*/
            accel->x = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_X_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_X_LSB]
                              & BMA2x2_12_BIT_SHIFT));
            accel->x = accel->x >> BMA2x2_SHIFT_FOUR_BITS;

            /* read y data_u8*/
            accel->y = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_LSB]
                              & BMA2x2_12_BIT_SHIFT));
            accel->y = accel->y >> BMA2x2_SHIFT_FOUR_BITS;

            /* read z data_u8*/
            accel->z = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_MSB]))
                              << BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_LSB]
                              & BMA2x2_12_BIT_SHIFT));
            accel->z = accel->z >> BMA2x2_SHIFT_FOUR_BITS;
            /*Accessing the sixth element of array*/
            accel->temp = (s8)data_u8[BMA2x2_SENSOR_DATA_TEMP];
            break;
        case BMA2x2_10_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_ACCEL_X10_LSB_REG,
                        data_u8, BMA2x2_ACCEL_BW_MIN_RANGE);

            /* read x data_u8*/
            accel->x = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_X_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_X_LSB]
                              & BMA2x2_10_BIT_SHIFT));
            accel->x = accel->x >> BMA2x2_SHIFT_SIX_BITS;

            /* read y data_u8*/
            accel->y = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_LSB]
                              & BMA2x2_10_BIT_SHIFT));
            accel->y = accel->y >> BMA2x2_SHIFT_SIX_BITS;

            /* read z data_u8*/
            accel->z = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_LSB]
                              & BMA2x2_10_BIT_SHIFT));
            accel->z = accel->z >> BMA2x2_SHIFT_SIX_BITS;

            /* read temp_s8 data_u8*/
            /*Accessing the sixth element of array*/
            accel->temp = (s8)data_u8[BMA2x2_SENSOR_DATA_TEMP];
            break;
        case BMA2x2_14_RESOLUTION:
            com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                       (p_bma2x2->dev_addr, BMA2x2_ACCEL_X14_LSB_REG,
                        data_u8, BMA2x2_ACCEL_BW_MIN_RANGE);

            /* read x data_u8*/
            accel->x = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_X_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_X_LSB]
                              & BMA2x2_14_BIT_SHIFT));
            accel->x = accel->x >> BMA2x2_SHIFT_TWO_BITS;

            /* read y data_u8*/
            accel->y = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Y_LSB]
                              & BMA2x2_14_BIT_SHIFT));
            accel->y = accel->y >> BMA2x2_SHIFT_TWO_BITS;

            /* read z data_u8*/
            accel->z = (s16)((((s32)((s8)
                                     data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_MSB])) <<
                              BMA2x2_SHIFT_EIGHT_BITS) |
                             (data_u8[BMA2x2_SENSOR_DATA_XYZ_Z_LSB]
                              & BMA2x2_14_BIT_SHIFT));
            accel->z = accel->z >> BMA2x2_SHIFT_TWO_BITS;
            /* read temp data_u8*/
            /*Accessing the sixth element of array*/
            accel->temp = (s8)data_u8[BMA2x2_SENSOR_DATA_TEMP];
            break;
        default:
            break;
        }
    }
    return com_rslt;
}
/*!
 * @brief This API reads accelerometer data X,Y,Z values and
 * temperature data from location 0x02 to 0x08
 *
 *
 *
 *
 *  @param accel : The value of accel xyz and temperature data
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_read_accel_eight_resolution_xyzt(
    struct bma2x2_accel_eight_resolution_temp *accel)
{
    /*  Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;
    u8  data_u8 = BMA2x2_INIT_VALUE;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_X_AXIS_MSB_ADDR, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->x = BMA2x2_GET_BITSLICE(data_u8,
                                       BMA2x2_ACCEL_X_MSB);

        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_Y_AXIS_MSB_ADDR, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->y = BMA2x2_GET_BITSLICE(data_u8,
                                       BMA2x2_ACCEL_Y_MSB);

        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC
                   (p_bma2x2->dev_addr,
                    BMA2x2_Z_AXIS_MSB_ADDR, &data_u8,
                    BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->z = BMA2x2_GET_BITSLICE(data_u8,
                                       BMA2x2_ACCEL_Z_MSB);

        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr, BMA2x2_TEMP_ADDR, &data_u8,
                       BMA2x2_GEN_READ_WRITE_LENGTH);
        accel->temp = (s8)data_u8;
    }
    return com_rslt;
}
#if 0   // avoid compile wranning
/*!
 *  @brief This API is used to get
 *  the fifo data in the register 0x3F bit 0 to 7
 *
 *
 *  @param  output_reg_u8 : The value of fifo data
 *
 *
 *
 *  @return results of bus communication function
 *  @retval 0 -> Success
 *  @retval -1 -> Error
 *
 *
*/
BMA2x2_RETURN_FUNCTION_TYPE bma2x2_get_fifo_data_output_reg(
    u8 *output_reg_u8)
{
#warning This API is deprecated ,Instead use the \
"bma2x2_read_fifo_data" API for reading FIFO data

    u8 data_u8 = BMA2x2_INIT_VALUE;
    /*Variable used to return value of
    communication routine*/
    BMA2x2_RETURN_FUNCTION_TYPE com_rslt = ERROR;

    if (p_bma2x2 == BMA2x2_NULL)
    {
        /* Check the struct p_bma2x2 is empty */
        return E_BMA2x2_NULL_PTR;
    }
    else
    {
        /*GET FIFO DATA OUTPUT REGISTER*/
        com_rslt = p_bma2x2->BMA2x2_BUS_READ_FUNC(
                       p_bma2x2->dev_addr,
                       BMA2x2_FIFO_DATA_OUTPUT_ADDR,
                       &data_u8, BMA2x2_GEN_READ_WRITE_LENGTH);
        *output_reg_u8 = data_u8;
    }
    return com_rslt;
}
#endif
