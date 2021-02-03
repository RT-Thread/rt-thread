/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MPU6050
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note		
					接线定义：
					------------------------------------ 
						软件IIC
                        SCL                 查看SEEKFREE_IIC文件内的SEEKFREE_SCL宏定义
						SDA                 查看SEEKFREE_IIC文件内的SEEKFREE_SDA宏定义
                            
                        硬件IIC
                        SCL                 查看init_mpu6050_hardware函数内IIC初始化时所带参数
						SDA                 查看init_mpu6050_hardware函数内IIC初始化时所带参数    
					------------------------------------ 
 ********************************************************************************************************************/

//#include "zf_iic.h"
#include "zf_stm_systick.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MPU6050.h"

int16 mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
int16 mpu_acc_x,mpu_acc_y,mpu_acc_z;





//-------------------------------------------------------------------------------------------------------------------
//  @brief      MPU6050自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_self1_check(void)
{
    simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	//解除休眠状态
    simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);   //125HZ采样率
    while(0x07 != simiic_read_reg(MPU6050_DEV_ADDR, SMPLRT_DIV,SIMIIC))
    {
        //卡在这里原因有以下几点
        //1 MPU6050坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
		//4 可能没有调用模拟IIC的初始化函数
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化MPU6050
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void mpu6050_init(void)
{
	simiic_init();
    systick_delay_ms(STM0, 100);                                   //上电延时

    mpu6050_self1_check();
    simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	//解除休眠状态
    simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);   //125HZ采样率
    simiic_write_reg(MPU6050_DEV_ADDR, MPU6050_CONFIG, 0x04);       //
    simiic_write_reg(MPU6050_DEV_ADDR, GYRO_CONFIG, 0x18);  //2000
    simiic_write_reg(MPU6050_DEV_ADDR, ACCEL_CONFIG, 0x10); //8g
	simiic_write_reg(MPU6050_DEV_ADDR, User_Control, 0x00);
    simiic_write_reg(MPU6050_DEV_ADDR, INT_PIN_CFG, 0x02);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取MPU6050加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_accdata(void)
{
    uint8 dat[6];

    simiic_read_regs(MPU6050_DEV_ADDR, ACCEL_XOUT_H, dat, 6, SIMIIC);  
    mpu_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    mpu_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    mpu_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取MPU6050陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_gyro(void)
{
    uint8 dat[6];

    simiic_read_regs(MPU6050_DEV_ADDR, GYRO_XOUT_H, dat, 6, SIMIIC);  
    mpu_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    mpu_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    mpu_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  以上函数是使用软件IIC通信，相比较硬件IIC，软件IIC引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------





////-------------------------------------------------------------------------------------------------------------------
////  以下函数是使用硬件IIC通信，相比较软件IIC，硬件IIC速度可以做到更快。
////-------------------------------------------------------------------------------------------------------------------
//
//#define IIC_NUM         IIC_1
//#define IIC_SDA_PIN     IIC1_SDA_B17
//#define IIC_SCL_PIN     IIC1_SCL_B16
////-------------------------------------------------------------------------------------------------------------------
////  @brief      MPU6050自检函数
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void mpu6050_self2_check(void)
//{
//    uint8 dat=0;
//
//    iic_write_reg(IIC_NUM, MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	//解除休眠状态
//    iic_write_reg(IIC_NUM, MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07); //125HZ采样率
//    while(0x07 != dat)
//    {
//        iic_read_reg(IIC_NUM, MPU6050_DEV_ADDR, SMPLRT_DIV, &dat);
//        systick_delay_ms(STM0, 10);
//        //卡在这里原因有以下几点
//        //1 MPU6050坏了，如果是新的这样的概率极低
//        //2 接线错误或者没有接好
//        //3 可能你需要外接上拉电阻，上拉到3.3V
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      初始化MPU6050
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void mpu6050_init_hardware(void)
//{
//    systick_delay_ms(STM0, 100);                                      //上电延时
//    iic_init(IIC_NUM, IIC_SDA_PIN, IIC_SCL_PIN,400*1000);       //硬件IIC初始化     波特率400K
//
//    mpu6050_self2_check();
//    iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	//解除休眠状态
//    iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, SMPLRT_DIV, 0x07);    //125HZ采样率
//    iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, MPU6050_CONFIG, 0x04);        //
//    iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, GYRO_CONFIG, 0x18);   //2000
//    iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, ACCEL_CONFIG, 0x10);  //8g
//	iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, User_Control, 0x00);
//    iic_write_reg(IIC_NUM,MPU6050_DEV_ADDR, INT_PIN_CFG, 0x02);
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      获取MPU6050加速度计数据
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:				执行该函数后，直接查看对应的变量即可
////-------------------------------------------------------------------------------------------------------------------
//void get_accdata_hardware(void)
//{
//    uint8 dat[6];
//
//    iic_read_reg_bytes(IIC_NUM,MPU6050_DEV_ADDR, ACCEL_XOUT_H, dat, 6);
//    mpu_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
//    mpu_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
//    mpu_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      获取MPU6050陀螺仪数据
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:				执行该函数后，直接查看对应的变量即可
////-------------------------------------------------------------------------------------------------------------------
//void get_gyro_hardware(void)
//{
//    uint8 dat[6];
//
//    iic_read_reg_bytes(IIC_NUM,MPU6050_DEV_ADDR, GYRO_XOUT_H, dat, 6);
//    mpu_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
//    mpu_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
//    mpu_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
//}








