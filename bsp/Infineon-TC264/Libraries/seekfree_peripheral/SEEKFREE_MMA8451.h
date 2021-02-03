/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MMA8451
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
						SCL                 查看SEEKFREE_IIC文件内的SEEKFREE_SCL宏定义
						SDA                 查看SEEKFREE_IIC文件内的SEEKFREE_SDA宏定义
					------------------------------------ 
 ********************************************************************************************************************/



#ifndef _SEEKFREEMMA8451_H__
#define _SEEKFREEMMA8451_H__

#include "common.h"


//MSB方式下:SA0=0;Write add 0x38,read add 0x39
//LSB方式下:SA0=1;Write add 0x3a,read add 0x3b
#define MMA8451_DEV_ADD		  0x38>>1

#define STATUS_00_REG         0x00

//  XYZ Data Registers
#define OUT_X_MSB_REG         0x01
#define OUT_X_LSB_REG         0x02
#define OUT_Y_MSB_REG         0x03
#define OUT_Y_LSB_REG         0x04
#define OUT_Z_MSB_REG         0x05
#define OUT_Z_LSB_REG         0x06



//  WHO_AM_I Device ID Register
#define WHO_AM_I_REG          0x0D
#define MMA8451Q_ID           0x1A
#define MMA8452Q_ID           0x2A
#define MMA8453Q_ID           0x3A


//  F_STATUS FIFO Status Register
#define F_STATUS_REG          0x00




//  F_SETUP FIFO Setup Register
#define F_SETUP_REG           0x09




// TRIG CFG Register
#define TRIG_CFG_REG          0x0A
//
#define ZYXDR_MASK            0x08


//  SYSMOD System Mode Register
#define SYSMOD_REG            0x0B
//
#define FGERR_MASK            0x80
#define FGT_4MASK             0x40
#define FGT_3MASK             0x20
#define FGT_2MASK             0x10
#define FGT_1MASK             0x08
#define FGT_0MASK             0x04
#define FGT_MASK              0x7C
#define SYSMOD1_MASK          0x02
#define SYSMOD0_MASK          0x01
#define SYSMOD_MASK           0x03


//  INT_SOURCE System Interrupt Status Register
#define INT_SOURCE_REG        0x0C
//
#define SRC_ASLP_MASK         0x80
#define SRC_FIFO_MASK         0x40
#define SRC_TRANS_MASK        0x20
#define SRC_LNDPRT_MASK       0x10
#define SRC_PULSE_MASK        0x08
#define SRC_FF_MT_1_MASK      0x04
#define SRC_FF_MT_2_MASK      0x02
#define SRC_DRDY_MASK         0x01



//  XYZ_DATA_CFG Sensor Data Configuration Register
#define XYZ_DATA_CFG_REG      0x0E
//
#define HPF_OUT_BIT           Bit._4
#define FS1_BIT               Bit._1
#define FS0_BIT               Bit._0
//
#define HPF_OUT_MASK          0x10
#define FS1_MASK              0x02
#define FS0_MASK              0x01
#define FS_MASK               0x03

#define FULL_SCALE_8G         FS1_MASK
#define FULL_SCALE_4G         FS0_MASK
#define FULL_SCALE_2G         0x00


//  HP_FILTER_CUTOFF High Pass Filter Register
#define HP_FILTER_CUTOFF_REG  0x0F
//
#define PULSE_HPF_BYP         Bit._5
#define PULSE_LPF_EN          Bit._4
#define SEL1_BIT              Bit._1
#define SEL0_BIT              Bit._0
//
#define PULSE_HPF_BYP_MASK    0x20
#define PULSE_LPF_EN_MASK     0x10
#define SEL1_MASK             0x02
#define SEL0_MASK             0x01
#define SEL_MASK              0x03


//  PL_STATUS Portrait/Landscape Status Register
//  PL_PRE_STATUS Portrait/Landscape Previous Data Status Register
#define PL_STATUS_REG         0x10
//
#define NEWLP_MASK            0x80
#define LO_MASK               0x40
#define LAPO1_MASK            0x04
#define LAPO0_MASK            0x02
#define LAPO_MASK             0x06
#define BAFRO_MASK            0x01



//  PL_CFG Portrait/Landscape Configuration Register
#define PL_CFG_REG            0x11
//
#define DBCNTM_BIT            Bit._7
#define PL_EN_BIT             Bit._6
//
#define DBCNTM_MASK           0x80
#define PL_EN_MASK            0x40


//  PL_COUNT Portrait/Landscape Debounce Register
#define PL_COUNT_REG          0x12


//  PL_BF_ZCOMP Back/Front and Z Compensation Register
#define PL_BF_ZCOMP_REG       0x13
//
#define BKFR1_MASK            0x80
#define BKFR0_MASK            0x40
#define ZLOCK2_MASK           0x04
#define ZLOCK1_MASK           0x02
#define ZLOCK0_MASK           0x01
#define BKFR_MASK             0xC0
#define ZLOCK_MASK            0x07


//  PL_P_L_THS Portrait to Landscape Threshold Registers
#define PL_P_L_THS_REG        0x14	   

//  FF_MT_CFG Freefall and Motion Configuration Registers
#define FF_MT_CFG_1_REG       0x15
#define FF_MT_CFG_2_REG       0x19

#define ELE_MASK              0x80
#define OAE_MASK              0x40
#define ZEFE_MASK             0x20
#define YEFE_MASK             0x10
#define XEFE_MASK             0x08


//  FF_MT_SRC Freefall and Motion Source Registers
#define FF_MT_SRC_1_REG       0x16
#define FF_MT_SRC_2_REG       0x1A
//
#define EA_MASK               0x80
#define ZHE_MASK              0x20
#define ZHP_MASK              0x10
#define YHE_MASK              0x08
#define YHP_MASK              0x04
#define XHE_MASK              0x02
#define XHP_MASK              0x01


//  FF_MT_THS Freefall and Motion Threshold Registers
//  TRANSIENT_THS Transient Threshold Register
#define FT_MT_THS_1_REG       0x17
#define FT_MT_THS_2_REG       0x1B
#define TRANSIENT_THS_REG     0x1F
//
#define DBCNTM_MASK           0x80
#define THS6_MASK             0x40
#define THS5_MASK             0x20
#define THS4_MASK             0x10
#define THS3_MASK             0x08
#define THS2_MASK             0x04
#define TXS1_MASK             0x02
#define THS0_MASK             0x01
#define THS_MASK              0x7F


//  FF_MT_COUNT Freefall Motion Count Registers
#define FF_MT_COUNT_1_REG     0x18
#define FF_MT_COUNT_2_REG     0x1C


//  TRANSIENT_CFG Transient Configuration Register
#define TRANSIENT_CFG_REG     0x1D	
//
#define TELE_MASK             0x10
#define ZTEFE_MASK            0x08
#define YTEFE_MASK            0x04
#define XTEFE_MASK            0x02
#define HPF_BYP_MASK          0x01


//  TRANSIENT_SRC Transient Source Register
#define TRANSIENT_SRC_REG     0x1E
//
#define TEA_MASK              0x40
#define ZTRANSE_MASK          0x20
#define ZTRANSEPOL_MASK       0x10
#define YTRANSE_MASK          0x08
#define YTRANSEPOL_MASK       0x04
#define XTRANSE_MASK          0x02
#define XTRANSEPOL_MASK       0x01


//  TRANSIENT_COUNT Transient Debounce Register
#define TRANSIENT_COUNT_REG   0x20


//  PULSE_CFG Pulse Configuration Register
#define PULSE_CFG_REG         0x21
//
#define DPA_MASK              0x80
#define PELE_MASK             0x40
#define ZDPEFE_MASK           0x20
#define ZSPEFE_MASK           0x10
#define YDPEFE_MASK           0x08
#define YSPEFE_MASK           0x04
#define XDPEFE_MASK           0x02
#define XSPEFE_MASK           0x01


//  PULSE_SRC Pulse Source Register
#define PULSE_SRC_REG         0x22
//
#define PEA_MASK              0x80
#define PAXZ_MASK             0x40
#define PAXY_MASK             0x20
#define PAXX_MASK             0x10
#define PDPE_MASK             0x08
#define POLZ_MASK             0x04
#define POLY_MASK             0x02
#define POLX_MASK             0x01


//  PULSE_THS XYZ Pulse Threshold Registers
#define PULSE_THSX_REG        0x23
#define PULSE_THSY_REG        0x24
#define PULSE_THSZ_REG        0x25
//
#define PTHS_MASK             0x7F


//  PULSE_TMLT Pulse Time Window Register
#define PULSE_TMLT_REG        0x26

//  PULSE_LTCY Pulse Latency Timer Register

#define PULSE_LTCY_REG        0x27


//  PULSE_WIND Second Pulse Time Window Register
#define PULSE_WIND_REG        0x28


//  ASLP_COUNT Auto Sleep Inactivity Timer Register
#define ASLP_COUNT_REG        0x29


//  CTRL_REG1 System Control 1 Register
#define CTRL_REG1             0x2A	
//
#define ASLP_RATE1_MASK       0x80
#define ASLP_RATE0_MASK       0x40
#define DR2_MASK              0x20
#define DR1_MASK              0x10
#define DR0_MASK              0x08
#define LNOISE_MASK           0x04
#define FREAD_MASK            0x02
#define ACTIVE_MASK           0x01
#define ASLP_RATE_MASK        0xC0
#define DR_MASK               0x38
//                      
#define ASLP_RATE_20MS        0x00
#define ASLP_RATE_80MS        ASLP_RATE0_MASK
#define ASLP_RATE_160MS       ASLP_RATE1_MASK
#define ASLP_RATE_640MS       ASLP_RATE1_MASK+ASLP_RATE0_MASK
//
#define DATA_RATE_1250US      0x00
#define DATA_RATE_2500US      DR0_MASK
#define DATA_RATE_5MS         DR1_MASK
#define DATA_RATE_10MS        DR1_MASK+DR0_MASK
#define DATA_RATE_20MS        DR2_MASK
#define DATA_RATE_80MS        DR2_MASK+DR0_MASK
#define DATA_RATE_160MS       DR2_MASK+DR1_MASK
#define DATA_RATE_640MS       DR2_MASK+DR1_MASK+DR0_MASK


//  CTRL_REG2 System Control 2 Register
#define CTRL_REG2             0x2B	
//
#define ST_MASK               0x80
#define BOOT_MASK             0x40
#define SMODS1_MASK           0x20
#define SMODS0_MASK           0x10
#define SLPE_MASK             0x04
#define MODS1_MASK            0x02
#define MODS0_MASK            0x01
#define SMODS_MASK            0x18
#define MODS_MASK             0x03


//  CTRL_REG3 Interrupt Control Register
#define CTRL_REG3             0x2C	 
//
#define FIFO_GATE_MASK        0x80
#define WAKE_TRANS_MASK       0x40
#define WAKE_LNDPRT_MASK      0x20
#define WAKE_PULSE_MASK       0x10
#define WAKE_FF_MT_1_MASK     0x08
#define WAKE_FF_MT_2_MASK     0x04
#define IPOL_MASK             0x02
#define PP_OD_MASK            0x01


//  CTRL_REG4 Interrupt Enable Register
#define CTRL_REG4             0x2D	
//
#define INT_EN_ASLP_MASK      0x80
#define INT_EN_FIFO_MASK      0x40
#define INT_EN_TRANS_MASK     0x20
#define INT_EN_LNDPRT_MASK    0x10
#define INT_EN_PULSE_MASK     0x08
#define INT_EN_FF_MT_1_MASK   0x04
#define INT_EN_FF_MT_2_MASK   0x02
#define INT_EN_DRDY_MASK      0x01


//  CTRL_REG5 Interrupt Configuration Register
#define CTRL_REG5             0x2E 
//
#define INT_CFG_ASLP_MASK     0x80
#define INT_CFG_FIFO_MASK     0x40
#define INT_CFG_TRANS_MASK    0x20
#define INT_CFG_LNDPRT_MASK   0x10
#define INT_CFG_PULSE_MASK    0x08
#define INT_CFG_FF_MT_1_MASK  0x04
#define INT_CFG_FF_MT_2_MASK  0x02
#define INT_CFG_DRDY_MASK     0x01


//  XYZ Offset Correction Registers
#define OFF_X_REG             0x2F
#define OFF_Y_REG             0x30
#define OFF_Z_REG             0x31



extern int16 acc_x, acc_y, acc_z;


uint8 mma845x_init(void);
void  get_mma8451(void);




















#endif 
