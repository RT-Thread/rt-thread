/*
 * File      : bmi055_sensor.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author           Notes
 * 2015-1-11     RT_learning      the first version
 */
#ifndef __BMI055_H__
#define __BMI055_H__

#include <sensor.h>

/**************************************************************************************************/
/************************************Register map accelerometer************************************/

#define	BMI055_ACC_I2C_ADDR1			   	0x18        //SDO is low(GND)
#define BMI055_ACC_I2C_ADDR2			   	0x19		//SDO is high(VCC)

#define BMI055_ACC_DEFAULT_ADDRESS     BMI055_ACC_I2C_ADDR2	//in the LPC54102 SPM-S 

#define BMI055_ACC_BGW_CHIPID_VALUE			0xFA

#define BMI055_ACC_BGW_CHIPID			   	0x00
/**<Address of ACC Chip ID Register					 	   	*/
#define	BMI055_ACCD_X_LSB					0x02		   
/**<        Address of X axis ACC LSB Register       	   	*/
#define	BMI055_ACCD_X_MSB					0x03		   
/**<        Address of X axis ACC MSB Register       	   	*/
#define	BMI055_ACCD_Y_LSB					0x04		   
/**<        Address of Y axis ACC LSB Register       	   	*/
#define	BMI055_ACCD_Y_MSB					0x05		   
/**<        Address of Y axis ACC MSB Register       	   	*/
#define	BMI055_ACCD_Z_LSB					0x06		   
/**<        Address of Z axis ACC LSB Register       	   	*/
#define BMI055_ACCD_Z_MSB					0x07		   
/**<        Address of Z axis ACC MSB Register       	   	*/
#define BMI055_ACCD_TEMP					0x08		   
/**<        Address of Temperature Data  Register  	 	   	*/
		                                                   
/* Status Register */		                               
#define BMI055_INT_STATUS_0					0x09		   
/**<        Address of Interrupt status Register 0   	    */
#define BMI055_INT_STATUS_1					0x0A		   
/**<        Address of Interrupt status Register 1   	    */
#define BMI055_INT_STATUS_2					0x0B		   
/**<        Address of Interrupt status Register 2   	    */
#define BMI055_INT_STATUS_3					0x0C		   
/**<        Address of Interrupt status Register 3   	    */
#define BMI055_FIFO_STATUS					0x0E		   
/**<        Address of FIFO status Register          	    */

/* Control Register */
#define BMI055_PMU_RANGE					0x0F
/**<        Address of Range address Register     	  		*/
#define BMI055_PMU_BW						0x10		    
/**<        Address of Bandwidth Register             		*/
#define BMI055_PMU_LPW						0x11		    
/**<        Address of PMU LPW			             		*/
#define BMI055_PMU_LOW_POWER				0x12	  		
/**<        Address of PMU LOW POWER     	        		*/
#define	BMI055_ACCD_HBW						0x13	  		
/**<        Address of ACCD HBW			             		*/
#define	BMI055_BGW_SOFTRESET				0x14	  		
/**<        Address of BGW SOFTRESET	             		*/	
#define	BMI055_INT_EN_0						0x16	  		
/**<        Address of interrupt engines in group 0    		*/
#define	BMI055_INT_EN_1						0x17	  		
/**<        Address of interrupt engines in group 1   		*/
#define	BMI055_INT_EN_2						0x18	  			
/**<        Address of interrupt engines in group 2   		*/
#define	BMI055_INT_MAP_0					0x19	  		
/**<        Address of Interrupt MAP 0				   		*/
#define BMI055_INT_MAP_1					0x1A
/**<        Address of Interrupt MAP 1			     		*/
#define BMI055_INT_MAP_2					0x1B
/**<        Address of Interrupt MAP 2	             		*/
#define BMI055_INT_SRC						0x1E
/**<        Address of Interrupt source             		*/
#define BMI055_INT_OUT_CTRL					0x20
/**<        Address of Interrupt Register             		*/
#define BMI055_INT_RST_LATCH				0x21
/**<        Address of Interrupt reset and mode  Register	*/
#define BMI055_INT_0						0x22
/**<        Address of low-g Interrupt delay time Register	*/
#define BMI055_INT_1						0x23
/**<        Address of low-g Interrupt threshold Register	*/
#define BMI055_INT_2						0x24
/**<        Address of Interrupt 2 Register					*/
#define BMI055_INT_3						0x25
/**<        Address of high-g Interrupt delay time Register */
#define BMI055_INT_4						0x26
/**<        Address of high-g Interrupt threshold Register  */
#define BMI055_INT_5						0x27
/**<        Address of high-g Interrupt 5 Register		    */
#define BMI055_INT_6						0x28
/**<   Address of any-motion Interrupt threshold Register   */
#define BMI055_INT_7						0x29
/**< Address of slow/no-motion interrupt threshold Register */
#define BMI055_INT_8						0x2A
/**<        Address of high-g Interrupt 8 Register		    */
#define BMI055_INT_9						0x2B
/**<        Address of high-g Interrupt 9 Register		    */
#define BMI055_INT_A						0x2C
/**<        Address of Interrupt A Register		    		*/
#define BMI055_INT_B						0x2D
/**<        Address of Interrupt B Register		    		*/
#define BMI055_INT_C						0x2E
/**<        Address of Interrupt C Register		    		*/
#define BMI055_INT_D						0x2F
/**<        Address of Interrupt D Register		    		*/
#define BMI055_FIFO_CONFIG_0				0x30
/**<        Address of FIFO CONFIG 0 Register		    	*/
#define BMI055_PMU_SELF_TEST				0x32
/**<        Address of PMU SELF TEST Register		    	*/
#define BMI055_TRIM_NVM_CTRL				0x33
/**<        Address of TRIM NVM CTRL Register		    	*/
#define BMI055_BGW_SPI3_WDT					0x34
/**<        Address of BGW SPI3 WDT Register		    	*/
#define BMI055_OFC_CTRL						0x36
/**<        Address of OFC CTRL Register			    	*/
#define BMI055_OFC_SETTING					0x37
/**<        Address of OFC SETTING Register			    	*/
#define BMI055_OFC_OFFSET_X					0x38
/**<        Address of OFC OFFSET X Register			    */
#define BMI055_OFC_OFFSET_Y					0x39
/**<        Address of OFC OFFSET Y Register			    */
#define BMI055_OFC_OFFSET_Z					0x3A
/**<        Address of OFC OFFSET Z Register			    */

/* Trim Register */
#define BMI055_TRIM_GP0						0x3B
/**<        Address of TRIM GP0 Register				    */
#define BMI055_TRIM_GP1						0x3C
/**<        Address of TRIM GP1 Register				    */

/* Control Register */
#define BMI055_FIFO_CONFIG_1				0x3E
/**<        Address of FIFO CONFIG 1 Register			    */

/* Data Register */
#define BMI055_FIFO_DATA					0x3F
/**<        Address of FIFO DATA Register				    */


/**************************************************************************************************/




/**************************************************************************************************/
/************************************Register map gyroscope****************************************/


/**< This refers BMI055 return type as signed */

// #define	BMI055_I2C_ADDR1				0x68		//SDO is low(GND)
// #define	BMI055_I2C_ADDR2				0x69		//SDO is high(VCC)
#define	BMI055_GYRO_I2C_ADDR1				0x68		//SDO is low(GND)
#define	BMI055_GYRO_I2C_ADDR2				0x69		//SDO is high(VCC)

#define BMI055_GYRO_DEFAULT_ADDRESS     BMI055_GYRO_I2C_ADDR2

#define BMI055_GRRO_CHIP_ID					0x0F

/*Define of registers*/

/* Hard Wired */
#define BMI055_CHIP_ID_ADDR						 0x00
/**<Address of Chip ID Register*/

/* Data Register */
#define BMI055_RATE_X_LSB_ADDR                    0x02
/**<        Address of X axis Rate LSB Register       		*/	
#define BMI055_RATE_X_MSB_ADDR                    0x03		
/**<        Address of X axis Rate MSB Register       		*/	
#define BMI055_RATE_Y_LSB_ADDR                    0x04		
/**<        Address of Y axis Rate LSB Register       		*/	
#define BMI055_RATE_Y_MSB_ADDR                     0x05		
/**<        Address of Y axis Rate MSB Register      		*/	
#define BMI055_RATE_Z_LSB_ADDR                     0x06		
/**<        Address of Z axis Rate LSB Register       		*/	
#define BMI055_RATE_Z_MSB_ADDR                     0x07		
/**<        Address of Z axis Rate MSB Register       		*/	
#define BMI055_TEMP_ADDR                           0x08		
/**<        Address of Temperature Data LSB Register  		*/	
		                                                    
/* Status Register */		                                
#define BMI055_INTR_STAT0_ADDR                     0x09		
/**<        Address of Interrupt status Register 0    		*/	
#define BMI055_INTR_STAT1_ADDR                     0x0A		
/**<        Address of Interrupt status Register 1    		*/	
#define BMI055_INTR_STAT2_ADDR                     0x0B		
/**<        Address of Interrupt status Register 2    		*/	
#define BMI055_INTR_STAT3_ADDR                     0x0C		
/**<        Address of Interrupt status Register 3    		*/	
#define BMI055_FIFO_STAT_ADDR                      0x0E		
/**<        Address of FIFO status Register           		*/	

/* Control Register */
#define BMI055_RANGE_ADDR                         0x0F
/**<        Address of Range address Register     			*/
#define BMI055_BW_ADDR                            0x10
/**<        Address of Bandwidth Register         			*/
#define BMI055_MODE_LPM1_ADDR                     0x11
/**<        Address of Mode LPM1 Register         			*/
#define BMI055_MODE_LPM2_ADDR                     0x12
/**<        Address of Mode LPM2 Register         			*/
#define BMI055_HIGH_BW_ADDR                       0x13
/**<        Address of Rate HIGH_BW Register       			*/
#define BMI055_BGW_SOFT_RST_ADDR                  0x14
/**<        Address of BGW Softreset Register      			*/
#define BMI055_INTR_ENABLE0_ADDR                  0x15
/**<        Address of Interrupt Enable 0             		*/
#define BMI055_INTR_ENABLE1_ADDR                  0x16
/**<        Address of Interrupt Enable 1             		*/
#define BMI055_INTR_MAP_ZERO_ADDR                 0x17
/**<        Address of Interrupt MAP 0                		*/
#define BMI055_INTR_MAP_ONE_ADDR                  0x18
/**<        Address of Interrupt MAP 1                		*/
#define BMI055_INTR_MAP_TWO_ADDR                  0x19
/**<        Address of Interrupt MAP 2                		*/
#define BMI055_INTR_ZERO_ADDR                     0x1A
/**<        Address of Interrupt 0 register   				*/
#define BMI055_INTR_ONE_ADDR                      0x1B
/**<        Address of Interrupt 1 register   				*/
#define BMI055_INTR_TWO_ADDR                      0x1C
/**<        Address of Interrupt 2 register   				*/
#define BMI055_INTR_4_ADDR                        0x1E
/**<        Address of Interrupt 4 register   				*/
#define BMI055_RST_LATCH_ADDR                     0x21
/**<        Address of Reset Latch Register           		*/
#define BMI055_HIGHRATE_THRES_X_ADDR              0x22
/**<        Address of High Th x Address register     		*/
#define BMI055_HIGHRATE_DURN_X_ADDR               0x23
/**<        Address of High Dur x Address register    		*/
#define BMI055_HIGHRATE_THRES_Y_ADDR              0x24
/**<        Address of High Th y  Address register    		*/
#define BMI055_HIGHRATE_DURN_Y_ADDR               0x25
/**<        Address of High Dur y Address register    		*/
#define BMI055_HIGHRATE_THRES_Z_ADDR              0x26
/**<        Address of High Th z Address register  			*/
#define BMI055_HIGHRATE_DURN_Z_ADDR               0x27
/**<        Address of High Dur z Address register  		*/
#define BMI055_SOC_ADDR                           0x31
/**<        Address of SOC register        					*/
#define BMI055_A_FOC_ADDR                         0x32
/**<        Address of A_FOC Register        				*/
#define BMI055_TRIM_NVM_CTRL_ADDR                 0x33
/**<        Address of Trim NVM control register    		*/
#define BMI055_BGW_SPI3_WDT_ADDR                  0x34
/**<        Address of BGW SPI3,WDT Register           		*/

/* Trim Register */
#define BMI055_OFC1_ADDR                   0x36
/**<        Address of OFC1 Register          				*/
#define BMI055_OFC2_ADDR                   0x37
/**<        Address of OFC2 Register          				*/
#define BMI055_OFC3_ADDR                   0x38
/**<        Address of OFC3 Register          				*/
#define BMI055_OFC4_ADDR                   0x39
/**<        Address of OFC4 Register          				*/
#define BMI055_TRIM_GP0_ADDR               0x3A
/**<        Address of Trim GP0 Register              		*/
#define BMI055_TRIM_GP1_ADDR               0x3B
/**<        Address of Trim GP1 Register              		*/
#define BMI055_SELECTF_TEST_ADDR            0x3C
/**<        Address of BGW Self test Register         		*/

/* Control Register */
#define BMI055_FIFO_CGF1_ADDR              0x3D
/**<        Address of FIFO CGF0 Register             		*/
#define BMI055_FIFO_CGF0_ADDR              0x3E
/**<        Address of FIFO CGF1 Register             		*/

/* Data Register */
#define BMI055_FIFO_DATA_ADDR              0x3F
/**<        Address of FIFO Data Register             		*/


/**************************************************************************************************/

class BMI055 :public SensorBase
{
public:
    BMI055(int sensor_type, const char* iic_bus, int addr);

    int read_reg(rt_uint8_t reg, rt_uint8_t* value);
    int write_reg(rt_uint8_t reg, rt_uint8_t value);
    int read_buffer(rt_uint8_t reg, rt_uint8_t* value, rt_size_t size);

private:
    struct rt_i2c_bus_device *i2c_bus;
    int i2c_addr;
};

class BMI055_Accelerometer:public BMI055
{
public:
    BMI055_Accelerometer(const char* iic_name, int addr);

    virtual int configure(SensorConfig *config);
    virtual int activate(int enable);

    virtual int poll(sensors_event_t *event);
    virtual void getSensor(sensor_t *sensor);

private:
	rt_int16_t x_offset, y_offset, z_offset;
	
	rt_bool_t enable;
	float sensitivity;
};

class BMI055_Gyroscope:public BMI055
{
public:
    BMI055_Gyroscope(const char* iic_name, int addr);

    virtual int configure(SensorConfig *config);
    virtual int activate(int enable);

    virtual int poll(sensors_event_t *event);
    virtual void getSensor(sensor_t *sensor);

private:
	rt_int16_t x_offset, y_offset, z_offset;
	
	rt_bool_t enable;
	float sensitivity;
};

#endif
