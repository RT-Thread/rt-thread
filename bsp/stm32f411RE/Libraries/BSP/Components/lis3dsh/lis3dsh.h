/**
  ******************************************************************************
  * @file    lis3dsh.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    03-August-2015
  * @brief   This file contains all the functions prototypes for the lis3dsh.c
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIS3DSH_H
#define __LIS3DSH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../Common/accelero.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 

/** @addtogroup LIS302DL
  * @{
  */

/** @defgroup LIS3DSH_Exported_Types
  * @{
  */
/* LIS3DSH struct */
typedef struct
{
  uint8_t Output_DataRate;              /* Output Data Rate into CTRL_REG4 register */
  uint8_t Axes_Enable;                  /* Axes enable into CTRL_REG4 register */
  uint8_t SPI_Wire;                     /* SPI Wire into CTRL_REG5 register */
  uint8_t Self_Test;                    /* Self test into CTRL_REG5 register */  
  uint8_t Full_Scale;                   /* Full scale into CTRL_REG5 register */
  uint8_t Filter_BW;                    /* Filter BW into CTRL_REG5 register */
}LIS3DSH_InitTypeDef;

/* LIS3DSH Interrupt struct */
typedef struct
{
  uint8_t Interrupt_Request;            /* Latch/Pulse Interrupt request into CTRL_REG3 register */
  uint8_t Interrupt_Selection_Enable;   /* Interrupt1/2 selection enable into CTRL_REG3 register */
  uint8_t Interrupt_Signal;             /* Interrupt signal active Low/High into CTRL_REG3 register */  
  uint8_t State_Machine1_Enable;        /* State Machine 1 enable/disable into CTRL_REG1 register */ 
  uint8_t State_Machine1_Interrupt;     /* State Machine 1 routed Interrupt into CTRL_REG1 register */
  uint8_t State_Machine2_Enable;        /* State Machine 2 enable/disable into CTRL_REG2 register */  
  uint8_t State_Machine2_Interrupt;     /* State Machine 2 routed Interrupt into CTRL_REG1 register */
}LIS3DSH_InterruptConfigTypeDef;  
/**
  * @}
  */
  
/** @defgroup LIS3DSH_Exported_Constants
  * @{
  */

/******************************************************************************/
/*************************** START REGISTER MAPPING  **************************/
/******************************************************************************/

/*******************************************************************************
*  OUT_T Register: Temperature Output Register
*  Read only register
*  Default value: 0x21
*  7:0 Temp7-Temp0: Temperature output Data
*******************************************************************************/
#define LIS3DSH_OUT_T_ADDR                   0x0C

/*******************************************************************************
*  INFO1 Register: Information Register 1
*  Read only register
*  Default value: 0x21
*******************************************************************************/
#define LIS3DSH_INFO1_ADDR                   0x0D

/*******************************************************************************
*  INFO2 Register: Information Register 2
*  Read only register
*  Default value: 0x00
*******************************************************************************/
#define LIS3DSH_INFO2_ADDR                   0x0E

/*******************************************************************************
*  WHO_AM_I Register: Device Identification Register
*  Read only register
*  Default value: 0x3F
*******************************************************************************/
#define LIS3DSH_WHO_AM_I_ADDR                0x0F

/*******************************************************************************
*  OFF_X Register: X-axis Offset Compensation Register
*  Read Write register
*  Default value: 0x00
*  7:0 OFFx_7-OFFx_0: X-axis Offset Compensation Value
*******************************************************************************/
#define LIS3DSH_OFF_X_ADDR                   0x10

/*******************************************************************************
*  OFF_Y Register: Y-axis Offset Compensation Register
*  Read Write register
*  Default value: 0x00
*  7:0 OFFy_7-OFFy_0: Y-axis Offset Compensation Value
*******************************************************************************/
#define LIS3DSH_OFF_Y_ADDR                   0x11

/*******************************************************************************
*  OFF_Z Register: Z-axis Offset Compensation Register
*  Read Write register
*  Default value: 0x00
*  7:0 OFFz_7-OFFz_0: Z-axis Offset Compensation Value
*******************************************************************************/
#define LIS3DSH_OFF_Z_ADDR                   0x12

/*******************************************************************************
*  CS_X Register: X-axis Constant Shift Register
*  Read Write register
*  Default value: 0x00
*  7:0 CS_7-CS_0: X-axis Constant Shift Value
*******************************************************************************/
#define LIS3DSH_CS_X_ADDR                    0x13

/*******************************************************************************
*  CS_Y Register: Y-axis Constant Shift Register
*  Read Write register
*  Default value: 0x00
*  7:0 CS_7-CS_0: Y-axis Constant Shift Value
*******************************************************************************/
#define LIS3DSH_CS_Y_ADDR                    0x14

/*******************************************************************************
*  CS_Z Register: Z-axis Constant Shift Value Register
*  Read Write register
*  Default value: 0x00
*  7:0 CS_7-CS_0: Z-axis Constant Shift Value
*******************************************************************************/
#define LIS3DSH_CS_Z_ADDR                    0x15

/*******************************************************************************
*  LC_L Register: Long Counter Low Register
*  Read Write register
*  Default value: 0x01
*  7:0 LC_L_7-LC_L_0: Long Counter Low Value
*******************************************************************************/
#define LIS3DSH_LC_L_ADDR                    0x16

/*******************************************************************************
*  LC_H Register: Long Counter High Register
*  Read Write register
*  Default value: 0x00
*  7:0 LC_H_7-LC_H_0: Long Counter Low Value
*******************************************************************************/
#define LIS3DSH_LC_H_ADDR                    0x17

/*******************************************************************************
*  STAT Register: State Machine Register
*  Read only register
*  Default value: 0x00
*  7 LONG: LONG flag common to both State Machines
*          0 - no interrupt
*          1 - LongCounter interrupt flag
*  6 SYNCW: Common information for OUTW host action waiting
*           0 - no action waiting from Host
*           1 - Host action is waiting after OUTW command
*  5 SYNC1: 
*           0 - State Machine 1 running normally
*           1 - SM1 stopped and waiting for restart request from SM2
*  4 SYNC2: 
*           0 - State Machine 2 running normally
*           1 - SM2 stopped and waiting for restart request from SM1
*  3 INT_SM1: Interrupt signal on SM1 is reset when OUTS1 register is read  
*             0 - no interrupt on State Machine 1 
*             1 - State Machine 1 interrupt happened       
*  2 INT_SM2: Interrupt signal on SM2 is reset when OUTS2 register is read  
*             0 - no interrupt on State Machine 2 
*             1 - State Machine 2 interrupt happened
*  1 DOR: Data OverRun bit 
*         0 - no overrun 
*         1 - data overrun
*  0 DRDY: New data are ready in output registers
*         0 - data not ready
*         1 - data ready
*******************************************************************************/
#define LIS3DSH_STAT_ADDR                    0x18

/*******************************************************************************
*  PEAK1 Register: Peak 1 Register
*  Read only register
*  Default value: 0x00
*  7:0 PKx_7-PKx_0: Peak 1 Value for SM1
*******************************************************************************/
#define LIS3DSH_PEAK1_ADDR                   0x19

/*******************************************************************************
*  PEAK2 Register: Peak 2 Register
*  Read only register
*  Default value: 0x00
*  7:0 PKx_7-PKx_0: Peak 2 value for SM2
*******************************************************************************/
#define LIS3DSH_PEAK2_ADDR                   0x1A

/*******************************************************************************
*  VFC_1 Register: Vector Filter Coefficient 1 Register
*  Read Write register
*  Default value: 0x00
*  7:0 VFC1_7-VFC1_0: Vector Filter Coefficient 1 Value
*******************************************************************************/
#define LIS3DSH_VFC_1_ADDR                   0x1B

/*******************************************************************************
*  VFC_2 Register: Vector Filter Coefficient 2 Register
*  Read Write register
*  Default value: 0x00
*  7:0 VFC2_7-VFC2_0: Vector Filter Coefficient 2 Value
*******************************************************************************/
#define LIS3DSH_VFC_2_ADDR                   0x1C

/*******************************************************************************
*  VFC_3 Register: Vector Filter Coefficient 3 Register
*  Read Write register
*  Default value: 0x00
*  7:0 VFC3_7-VFC3_0: Vector Filter Coefficient 3 Value
*******************************************************************************/
#define LIS3DSH_VFC_3_ADDR                   0x1D

/*******************************************************************************
*  VFC_4 Register: Vector Filter Coefficient 4 Register
*  Read Write register
*  Default value: 0x00
*  7:0 VFC4_7-VFC4_0: Vector Filter Coefficient 4 Value
*******************************************************************************/
#define LIS3DSH_VFC_4_ADDR                   0x1E

/*******************************************************************************
*  THRS3 Register: Threshold Value 3 Register
*  Read Write register
*  Default value: 0x00
*  7:0 THRS3_7-THRS3_0: Common Threshold for Overrun Detection Value
*******************************************************************************/
#define LIS3DSH_THRS3_ADDR                   0x1F

/*******************************************************************************
*  CTRL_REG4 Register: Control Register 4
*  Read Write register
*  Default value: 0x07
*  7:4 ODR3-ODR0: Data rate selection
*            ODR3 | ODR2 | ODR1 | ORD0 | ORD Selection
*            -------------------------------------------
*              0  |  0   |  0   |  0   | Power Down (Default)
*              0  |  0   |  0   |  1   | 3.125 Hz
*              0  |  0   |  1   |  0   | 6.25 Hz
*              0  |  0   |  1   |  1   | 12.5 Hz
*              0  |  1   |  0   |  0   | 25 Hz
*              0  |  1   |  0   |  1   | 50 Hz
*              0  |  1   |  1   |  0   | 100 Hz
*              0  |  1   |  1   |  1   | 400 Hz
*              1  |  0   |  0   |  0   | 800 Hz
*              1  |  0   |  0   |  1   | 1600 Hz
*
*  3 BDU: Block data update
*         0: Output register not updated until High and Low reading (Default)
*         1: Continuous update
*  2 ZEN: 
*         0: Z-axis disable (Default)
*         1: Z-axis enable
*  1 YEN:  
*         0: Y-axis disable (Default)
*         1: Y-axis enable
*  0 XEN:  
*         0: Y-axis disable (Default)
*         1: Y-axis enable
*******************************************************************************/
#define LIS3DSH_CTRL_REG4_ADDR               0x20

/*******************************************************************************
*  CTRL_REG1 Register: Control Register 1 (SM1 interrupt configuration register)
*  Read Write register
*  Default value: 0x00
*  7:5 HYST1_2-HYST1_0: Hysteresis which is added or subtracted from the  
*                       threshold values (THRS1_1 and THRS2_1) of SM1.
*                       000 = 0 (Default)
*                       111 = 7 (maximum Hysteresis)
*  4 Reserved
*  3 SM1_INT: 
*            0: State Machine 1 interrupt routed to INT1 (Default)
*            1: State Machine 1 interrupt routed to INT2
*  2 Reserved
*  1 Reserved
*  0 SM1_EN: 
*           0: State Machine 1 disabled. Temporary memories and registers 
*              related to this State Machine are left intact. (Default)
*           1: State Machine 1 enabled. 
*******************************************************************************/
#define LIS3DSH_CTRL_REG1_ADDR               0x21

/*******************************************************************************
*  CTRL_REG2 Register: Control Register 2 (SM2 interrupt configuration register)
*  Read Write register
*  Default value: 0x00
*  7:5 HYST2_2-HYST2_0: Hysteresis which is added or subtracted from the  
*                       threshold values (THRS1_2 and THRS2_2) of SM1.
*                       000 = 0 (Default)
*                       111 = 7 (maximum Hysteresis)
*  4 Reserved
*  3 SM2_INT: 
*            0: State Machine 2 interrupt routed to INT1 (Default)
*            1: State Machine 2 interrupt routed to INT2
*  2 Reserved
*  1 Reserved
*  0 SM2_EN: 
*           0: State Machine 2 disabled. Temporary memories and registers 
*              related to this State Machine are left intact. (Default)
*           1: State Machine 2 enabled. 
*******************************************************************************/
#define LIS3DSH_CTRL_REG2_ADDR               0x22

/*******************************************************************************
*  CTRL_REG3 Register: Control Register 3
*  Read Write register
*  Default value: 0x00
*  7 DR_EN: Data-ready interrupt
*          0 - Data-ready interrupt disabled (Default)
*          1 - Data-ready interrupt enabled and routed to INT1
*  6 IEA:  
*         0 - Interrupt signal active LOW (Default)
*         1 - Interrupt signal active HIGH
*  5 IEL: 
*         0 - Interrupt latched (Default)
*         1 - Interrupt pulsed
*  4 INT2_EN: 
*             0 - INT2 signal disabled (High-Z state) (Default)
*             1 - INT2 signal enabled (signal pin fully functional)
*  3 INT1_EN:  
*             0 - INT1 (DRDY) signal disabled (High-Z state) (Default)
*             1 - INT1 (DRDY) signal enabled (signal pin fully functional) DR_EN bit in CTRL_REG3 register should be taken into account too
*  2 VLIFT:  
*           0 - Vector filter disabled (Default)
*           1 - Vector filter enabled
*  1 Reserved  
*  0 STRT: Soft Reset  
*          0 - (Default)
*          1 - it resets the whole internal logic circuitry. It automatically returns to 0.
*******************************************************************************/
#define LIS3DSH_CTRL_REG3_ADDR               0x23              

/*******************************************************************************
*  CTRL_REG5 Register: Control Register 5
*  Read Write register
*  Default value: 0x00
*  7:6 BW2-BW1: Anti aliasing filter bandwidth
*            BW2 | BW1 | BW Selection
*            -------------------------
*             0  |  0  | 800 Hz (Default)
*             0  |  1  | 40 Hz
*             1  |  0  | 200 Hz
*             1  |  1  | 50 Hz
*
*  5:3 FSCALE2-FSCALE0: Full scale selection
*            FSCALE2 | FSCALE1 | FSCALE0 | Full scale selection
*            --------------------------------------------------
*               0    |    0    |    0    | +/-2g (Default)
*               0    |    0    |    1    | +/-4g
*               0    |    1    |    0    | +/-6g
*               0    |    1    |    1    | +/-8g
*               1    |    0    |    0    | +/-16g
*
*  2:1 ST2_ST1: Self-test Enable
*            ST2 | ST1 | ST Selection
*            -------------------------
*             0  |  0  | Normal Mode (Default)
*             0  |  1  | Positive sign self-test
*             1  |  0  | Negative sign-test
*             1  |  1  | Not Allowed
*
*  0 SIM: SPI serial internal interface mode selection  
*         0: 4-wire interface (Default)
*         1: 3-wire interface
*******************************************************************************/
#define LIS3DSH_CTRL_REG5_ADDR               0x24

/*******************************************************************************
*  CTRL_REG6 Register: Control Register 6
*  Read Write register
*  Default value: 0x00
*  7 BOOT: Force reboot, cleared as soon as the reboot is finished. Active High. 
*  6 FIFO_EN: FIFO Enable 
*             0: disable (Default)
*             1: enable
*  5 STP_WTM: Stop on Watermark - FIFO depth can be limited at the Watermark value, by setting to “1” the STP_WTM bit. 
*             0: disable (Default)
*             1: enable
*  4 IF_ADD_INC: Register address automatically increased during a multiple byte access with a serial interface (I2C or SPI)
*                0: disable (Default)
*                1: enable
*  3 I1_EMPTY: Enable FIFO Empty indication on INT1 pin.
*              0: disable (Default)
*              1: enable
*  2 I1_WTM: FIFO Watermark interrupt on INT1 pin.
*            0: disable (Default)
*            1: enable
*  1 I1_OVERRUN: FIFO Overrun interrupt on INT1 pin.
*                0: disable (Default)
*                1: enable
*  0 I2_BOOT: BOOT interrupt on INT2 pin. 
*                0: disable (Default)
*                1: enable
*******************************************************************************/
#define LIS3DSH_CTRL_REG6_ADDR               0x25

/*******************************************************************************
*  STATUS Register: Status Data Register
*  Read only register
*  Default value: 0x00
*  7 ZYXOR: X, Y and Z-axis Data Overrun.  
*           0: no Overrun has occurred (Default)
*           1: a new set of data has overwritten the previous ones
*  6 ZOR: Z-axis Data Overrun.  
*         0: no Overrun has occurred (Default)
*         1: a new data for the Z-axis has overwritten the previous ones
*  5 YOR: Y-axis Data Overrun.  
*         0: no Overrun has occurred (Default)
*         1: a new data for the Y-axis has overwritten the previous ones
*  4 XOR: X-axis Data Overrun.  
*         0: no Overrun has occurred (Default)
*         1: a new data for the X-axis has overwritten the previous ones
*  3 ZYXDA: X, Y and Z-axis new Data Available.  
*           0: a new set of data is not yet available (Default)
*           1: a new set of data is available
*  2 ZDA: Z-axis new data available.  
*         0: a new data for the Z-axis is not yet available (Default)
*         1: a new data for Z-axis is available
*  1 YDA: Y-axis new data available.  
*         0: a new data for the Y-axis is not yet available (Default)
*         1: a new data for Y-axis is available
*  0 XDA: X-axis new data available.  
*         0: a new data for the X-axis is not yet available (Default)
*         1: a new data for X-axis is available
*******************************************************************************/
#define LIS3DSH_STATUS_ADDR                  0x27

/*******************************************************************************
*  OUT_X_L Register: X-axis Output Acceleration Low Data
*  Read only register
*  Default value: output
*  7:0 XD7-XD0: X-axis output Data
*******************************************************************************/
#define LIS3DSH_OUT_X_L_ADDR                 0x28

/*******************************************************************************
*  OUT_X_H Register: X-axis Output Acceleration High Data
*  Read only register
*  Default value: output
*  15:8 XD15-XD8: X-axis output Data
*******************************************************************************/
#define LIS3DSH_OUT_X_H_ADDR                 0x29

/*******************************************************************************
*  OUT_Y_L Register: Y-axis Output Acceleration Low Data
*  Read only register
*  Default value: output
*  7:0 YD7-YD0: Y-axis output Data
*******************************************************************************/
#define LIS3DSH_OUT_Y_L_ADDR                 0x2A

/*******************************************************************************
*  OUT_Y_H Register: Y-axis Output Acceleration High Data
*  Read only register
*  Default value: output
*  15:8 YD15-YD8: Y-axis output Data
*******************************************************************************/
#define LIS3DSH_OUT_Y_H_ADDR                 0x2B

/*******************************************************************************
*  OUT_Z_L Register: Z-axis Output Acceleration Low Data
*  Read only register
*  Default value: output
*  7:0 ZD7-ZD0: Z-axis output Data
*******************************************************************************/
#define LIS3DSH_OUT_Z_L_ADDR                 0x2C

/*******************************************************************************
*  OUT_Z_H Register: Z-axis Output Acceleration High Data
*  Read only register
*  Default value: output
*  15:8 ZD15-ZD8: Z-axis output Data
*******************************************************************************/
#define LIS3DSH_OUT_Z_H_ADDR                 0x2D

/*******************************************************************************
*  FIFO_CTRL Register: FIFO Control Register
*  Read/Write register
*  Default value: 0x00
*  7:5 FMODE2-FMODE0: FIFO mode
*        FMODE2 | FMODE1 | FMODE0 | Mode description
*        --------------------------------------------------
*          0    |    0   |    0   | Bypass mode. FIFO turned off. (Default)
*          0    |    0   |    1   | FIFO mode. Stop collecting data when FIFO is full.
*          0    |    1   |    0   | Stream mode. If the FIFO is full, the new sample overwrites the older one (circular buffer). 
*          0    |    1   |    1   | Stream mode until trigger is de-asserted, then FIFO mode.
*          1    |    0   |    0   | Bypass mode until trigger is de-asserted, then Stream mode.
*          1    |    0   |    1   | Not to use.
*          1    |    1   |    0   | Not to use. 
*          1    |    1   |    1   | Bypass mode until trigger is de-asserted, then FIFO mode.
*
*  4:0 WTMP4-WTMP0: FIFO Watermark pointer. It is the FIFO depth when the Watermark is enabled
*******************************************************************************/
#define LIS3DSH_FIFO_CTRL_ADDR               0x2E

/*******************************************************************************
*  FIFO_SRC Register: FIFO Source Register
*  Read only register
*  Default value: 0x00
*  7 WTM: Watermark status.  
*         0: FIFO filling is lower than WTM level (Default)
*         1: FIFO filling is equal or higher than WTM level 
*  6 OVRN_FIFO: Overrun bit status.  
*               0: FIFO is not completely filled (Default)
*               1: FIFO is completely filled
*  5 EMPTY: Overrun bit status.  
*           0: FIFO not empty (Default)
*           1: FIFO empty
*  4:0 FSS: Number of samples stored in the FIFO - 1
*******************************************************************************/
#define LIS3DSH_FIFO_SRC_ADDR                0x2F

/*******************************************************************************
*  ST1_X Register: State Machine 1 Code Registers
*  Write only register
*  Default value: 0x00
*  7:0 ST1_7-ST1_0: State Machine 1 Code Registers
*******************************************************************************/
#define LIS3DSH_ST1_1_ADDR                   0x40
#define LIS3DSH_ST1_2_ADDR                   0x41
#define LIS3DSH_ST1_3_ADDR                   0x42
#define LIS3DSH_ST1_4_ADDR                   0x43
#define LIS3DSH_ST1_5_ADDR                   0x44
#define LIS3DSH_ST1_6_ADDR                   0x45
#define LIS3DSH_ST1_7_ADDR                   0x46
#define LIS3DSH_ST1_8_ADDR                   0x47
#define LIS3DSH_ST1_9_ADDR                   0x48
#define LIS3DSH_ST1_10_ADDR                  0x49
#define LIS3DSH_ST1_11_ADDR                  0x4A
#define LIS3DSH_ST1_12_ADDR                  0x4B
#define LIS3DSH_ST1_13_ADDR                  0x4C
#define LIS3DSH_ST1_14_ADDR                  0x4D
#define LIS3DSH_ST1_15_ADDR                  0x4E
#define LIS3DSH_ST1_16_ADDR                  0x4F

/*******************************************************************************
*  TIM4_1 Register: SM1 General Timer 4 Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM1 Timer 4 Counter 1 Value
*******************************************************************************/
#define LIS3DSH_TIM4_1_ADDR                  0x50

/*******************************************************************************
*  TIM3_1 Register: SM1 General Timer 3 Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM1 Timer 3 Counter 1 Value
*******************************************************************************/
#define LIS3DSH_TIM3_1_ADDR                  0x51 

/*******************************************************************************
*  TIM2_1_L Register: SM1 General Timer 2 Low Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM1 Timer 2 Counter 1 Low Value
*******************************************************************************/
#define LIS3DSH_TIM2_1_L_ADDR                0x52 

/*******************************************************************************
*  TIM2_1_H Register: SM1 General Timer 2 High Register
*  Write only register
*  Default value: 0x00
*  15:8 TM_15-TM_8: SM1 Timer 2 Counter 1 High Value
*******************************************************************************/
#define LIS3DSH_TIM2_1_H_ADDR                0x53 

/*******************************************************************************
*  TIM1_1_L Register: SM1 General Timer 1 Low Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM1 Timer 1 Counter 1 Low Value
*******************************************************************************/
#define LIS3DSH_TIM1_1_L_ADDR                0x54

/*******************************************************************************
*  TIM1_1_H Register: SM1 General Timer 1 High Register
*  Write only register
*  Default value: 0x00
*  15:8 TM_15-TM_8: SM1 Timer 1 Counter 1 High Value
*******************************************************************************/
#define LIS3DSH_TIM1_1_H_ADDR                0x55

/*******************************************************************************
*  THRS2_1 Register: SM1 Threshold Value 1 Register
*  Write only register
*  Default value: 0x00
*  7:0 THS7-THS0: SM1 Threshold Value 1
*******************************************************************************/
#define LIS3DSH_THRS2_1_ADDR                 0x56

/*******************************************************************************
*  THRS1_1 Register: SM1 Threshold Value 2 Register
*  Write only register
*  Default value: 0x00
*  7:0 THS7-THS0: SM1 Threshold Value 2
*******************************************************************************/
#define LIS3DSH_THRS1_1_ADDR                 0x57

/*******************************************************************************
*  MASK1_B Register: SM1 Swap Axis and Sign Mask Register
*  Write only register
*  Default value: 0x00
*  7 P_X: X-Axis Positive Motion Detection 
*         0: X+ disabled 
*         1: X+ enabled
*  6 N_X: X-Axis Negative Motion Detection 
*         0: X- disabled 
*         1: X- enabled
*  5 P_Y: Y-Axis Positive Motion Detection 
*         0: Y+ disabled 
*         1: Y+ enabled
*  4 N_Y: Y-Axis Negative Motion Detection 
*         0: Y- disabled 
*         1: Y- enabled
*  3 P_Z: X-Axis Positive Motion Detection 
*         0: Z+ disabled 
*         1: Z+ enabled
*  2 N_Z: X-Axis Negative Motion Detection 
*         0: Z- disabled 
*         1: Z- enabled
*  1 P_V: 
*         0: V+ disabled 
*         1: V+ enabled
*  0 N_V:  
*         0: V- disabled 
*         1: V- enabled
*******************************************************************************/
#define LIS3DSH_MASK1_B_ADDR                 0x59

/*******************************************************************************
*  MASK1_A Register: SM1 Default Axis and Sign Mask Register
*  Write only register
*  Default value: 0x00
*  7 P_X: X-Axis Positive Motion Detection 
*         0: X+ disabled 
*         1: X+ enabled
*  6 N_X: X-Axis Negative Motion Detection 
*         0: X- disabled 
*         1: X- enabled
*  5 P_Y: Y-Axis Positive Motion Detection 
*         0: Y+ disabled 
*         1: Y+ enabled
*  4 N_Y: Y-Axis Negative Motion Detection 
*         0: Y- disabled 
*         1: Y- enabled
*  3 P_Z: X-Axis Positive Motion Detection 
*         0: Z+ disabled 
*         1: Z+ enabled
*  2 N_Z: X-Axis Negative Motion Detection 
*         0: Z- disabled 
*         1: Z- enabled
*  1 P_V: 
*         0: V+ disabled 
*         1: V+ enabled
*  0 N_V:  
*         0: V- disabled 
*         1: V- enabled
*******************************************************************************/
#define LIS3DSH_MASK1_A_ADDR                 0x5A

/*******************************************************************************
*  SETT1 Register: SM1 Detection Settings Register
*  Write only register
*  Default value: 0x00
*  7 P_DET: SM1 peak detection bit 
*           0: peak detection disabled (Default) 
*           1: peak detection enabled
*  6 THR3_SA:  
*             0: no action (Default)
*             1: threshold 3 enabled for axis and sign mask reset (MASK1_B)
*  5 ABS:  
*         0: unsigned thresholds THRSx (Default)
*         1: signed thresholds THRSx
*  4 Reserved
*  3 Reserved
*  2 THR3_MA:  
*             0: no action (Default)
*             1: threshold 3 enabled for axis and sign mask reset (MASK1_A)
*  1 R_TAM: Next condition validation flag
*           0: mask frozen on the axis that triggers the condition (Default)
*           1: standard mask always evaluated
*  0 SITR:  
*          0: no actions (Default) 
*          1: STOP and CONT commands generate an interrupt and perform output 
*             actions as OUTC command.
*******************************************************************************/
#define LIS3DSH_SETT1_ADDR                   0x5B

/*******************************************************************************
*  PR1 Register: SM1 Program and Reset Pointers Register
*  Read only register
*  Default value: 0x00
*  7:4 PP3-PP0: SM1 program pointer address
*  3:0 RP3-RP0: SM1 reset pointer address
*******************************************************************************/
#define LIS3DSH_PR1_ADDR                     0x5C

/*******************************************************************************
*  TC1_L Register: SM1 General Timer Counter Low Register
*  Read only register
*  Default value: 0x00
*  7:0 TC1_7-TC1_0: SM1 General Timer Counter Low Value
*******************************************************************************/
#define LIS3DSH_TC1_L_ADDR                   0x5D

/*******************************************************************************
*  TC1_H Register: SM1 General Timer Counter High Register
*  Read only register
*  Default value: 0x00
*  15:8 TC1_15-TC1_8: SM1 General Timer Counter High Value
*******************************************************************************/
#define LIS3DSH_TC1_H_ADDR                   0x5E

/*******************************************************************************
*  OUTS1 Register: SM1 Output Set Flag Register
*  Read only register
*  Default value: 0x00
*  7 P_X: 
*         0: X+ noshow 
*         1: X+ show
*  6 N_X: 
*         0: X- noshow
*         1: X- show
*  5 P_Y:  
*         0: Y+ noshow 
*         1: Y+ show
*  4 N_Y:  
*         0: Y- noshow
*         1: Y- show
*  3 P_Z:  
*         0: Z+ noshow 
*         1: Z+ show
*  2 N_Z:  
*         0: Z- noshow
*         1: Z- show
*  1 P_V: 
*         0: V+ noshow
*         1: V+ show
*  0 N_V:  
*         0: V- noshow
*         1: V- show
*******************************************************************************/
#define LIS3DSH_OUTS1_ADDR                   0x5F

/*******************************************************************************
*  ST2_X Register: State Machine 2 Code Registers
*  Write only register
*  Default value: 0x00
*  7:0 ST2_7-ST2_0: State Machine 2 Code Registers
*******************************************************************************/
#define LIS3DSH_ST2_1_ADDR                   0x60
#define LIS3DSH_ST2_2_ADDR                   0x61
#define LIS3DSH_ST2_3_ADDR                   0x62
#define LIS3DSH_ST2_4_ADDR                   0x63
#define LIS3DSH_ST2_5_ADDR                   0x64
#define LIS3DSH_ST2_6_ADDR                   0x65
#define LIS3DSH_ST2_7_ADDR                   0x66
#define LIS3DSH_ST2_8_ADDR                   0x67
#define LIS3DSH_ST2_9_ADDR                   0x68
#define LIS3DSH_ST2_10_ADDR                  0x69
#define LIS3DSH_ST2_11_ADDR                  0x6A
#define LIS3DSH_ST2_12_ADDR                  0x6B
#define LIS3DSH_ST2_13_ADDR                  0x6C
#define LIS3DSH_ST2_14_ADDR                  0x6D
#define LIS3DSH_ST2_15_ADDR                  0x6E
#define LIS3DSH_ST2_16_ADDR                  0x6F

/*******************************************************************************
*  TIM4_2 Register: SM2 General Timer 4 Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM2 Timer 4 Counter 1 Value
*******************************************************************************/
#define LIS3DSH_TIM4_2_ADDR                  0x70 

/*******************************************************************************
*  TIM3_2 Register: SM2 General Timer 3 Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM2 Timer 3 Counter 2 Value
*******************************************************************************/
#define LIS3DSH_TIM3_2_ADDR                  0x71

/*******************************************************************************
*  TIM2_2_L Register: SM2 General Timer 2 Low Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM2 Timer 2 Counter 2 Low Value
*******************************************************************************/
#define LIS3DSH_TIM2_2_L_ADDR                0x72

/*******************************************************************************
*  TIM2_2_H Register: SM2 General Timer 2 High Register
*  Write only register
*  Default value: 0x00
*  15:8 TM_15-TM_8: SM2 Timer 2 Counter 2 High Value
*******************************************************************************/
#define LIS3DSH_TIM2_2_H_ADDR                0x73

/*******************************************************************************
*  TIM1_2_L Register: SM2 General Timer 1 Low Register
*  Write only register
*  Default value: 0x00
*  7:0 TM_7-TM_0: SM2 Timer 1 Counter 2 Low Value
*******************************************************************************/
#define LIS3DSH_TIM1_2_L_ADDR                0x74

/*******************************************************************************
*  TIM1_2_H Register: SM2 General Timer 1 High Register
*  Write only register
*  Default value: 0x00
*  15:8 TM_15-TM_8: SM2 Timer 1 Counter 2 High Value
*******************************************************************************/
#define LIS3DSH_TIM1_2_H_ADDR                0x75

/*******************************************************************************
*  THRS2_2 Register: SM2 Threshold Value 1 Register
*  Write only register
*  Default value: 0x00
*  7:0 THS7-THS0: SM2 Threshold Value
*******************************************************************************/
#define LIS3DSH_THRS2_2_ADDR                 0x76

/*******************************************************************************
*  THRS1_2 Register: SM2 Threshold Value 2 Register
*  Write only register
*  Default value: 0x00
*  7:0 THS7-THS0: SM2 Threshold Value
*******************************************************************************/
#define LIS3DSH_THRS1_2_ADDR                 0x77

/*******************************************************************************
*  DES2 Register: SM2 Decimation Counter Value Register
*  Write only register
*  Default value: 0x00
*  7:0 D7-D0: SM2 Decimation Counter Value
*******************************************************************************/
#define LIS3DSH_DES2_ADDR                    0x78

/*******************************************************************************
*  MASK2_B Register: SM2 Axis and Sign Mask Register
*  Write only register
*  Default value: 0x00
*  7 P_X: X-Axis Positive Motion Detection 
*         0: X+ disabled 
*         1: X+ enabled
*  6 N_X: X-Axis Negative Motion Detection 
*         0: X- disabled 
*         1: X- enabled
*  5 P_Y: Y-Axis Positive Motion Detection 
*         0: Y+ disabled 
*         1: Y+ enabled
*  4 N_Y: Y-Axis Negative Motion Detection 
*         0: Y- disabled 
*         1: Y- enabled
*  3 P_Z: X-Axis Positive Motion Detection 
*         0: Z+ disabled 
*         1: Z+ enabled
*  2 N_Z: X-Axis Negative Motion Detection 
*         0: Z- disabled 
*         1: Z- enabled
*  1 P_V: 
*         0: V+ disabled 
*         1: V+ enabled
*  0 N_V:  
*         0: V- disabled 
*         1: V- enabled
*******************************************************************************/
#define LIS3DSH_MASK2_B_ADDR                 0x79

/*******************************************************************************
*  MASK2_A Register: SM2 Axis and Sign Mask Register
*  Write only register
*  Default value: 0x00
*  7 P_X: X-Axis Positive Motion Detection 
*         0: X+ disabled 
*         1: X+ enabled
*  6 N_X: X-Axis Negative Motion Detection 
*         0: X- disabled 
*         1: X- enabled
*  5 P_Y: Y-Axis Positive Motion Detection 
*         0: Y+ disabled 
*         1: Y+ enabled
*  4 N_Y: Y-Axis Negative Motion Detection 
*         0: Y- disabled 
*         1: Y- enabled
*  3 P_Z: X-Axis Positive Motion Detection 
*         0: Z+ disabled 
*         1: Z+ enabled
*  2 N_Z: X-Axis Negative Motion Detection 
*         0: Z- disabled 
*         1: Z- enabled
*  1 P_V: 
*         0: V+ disabled 
*         1: V+ enabled
*  0 N_V:  
*         0: V- disabled 
*         1: V- enabled
*******************************************************************************/
#define LIS3DSH_MASK2_A_ADDR                 0x7A

/*******************************************************************************
*  SETT2 Register: SM2 Detection Settings Register
*  Write only register
*  Default value: 0x00
*  7 P_DET: SM2 peak detection 
*           0: peak detection disabled (Default) 
*           1: peak detection enabled
*  6 THR3_SA:  
*             0: no action (Default)
*             1: threshold 3 limit value for axis and sign mask reset (MASK2_B)
*  5 ABS:  
*         0: unsigned thresholds (Default)
*         1: signed thresholds
*  4 RADI:  
*          0: raw data 
*          1: diff data for State Machine 2 
*  3 D_CS:  
*          0: DIFF2 enabled (difference between current data and previous data)
*          1: constant shift enabled (difference between current data and constant values)     
*  2 THR3_MA:  
*             0: no action (Default)
*             1: threshold 3 enabled for axis and sign mask reset (MASK2_A)
*  1 R_TAM: Next condition validation flag
*           0: mask frozen on the axis that triggers the condition (Default)
*           1: standard mask always evaluated
*  0 SITR:  
*          0: no actions (Default) 
*          1: STOP and CONT commands generate an interrupt and perform output 
*             actions as OUTC command.
*******************************************************************************/
#define LIS3DSH_SETT2_ADDR                   0x7B

/*******************************************************************************
*  PR2 Register: SM2 Program and Reset Pointers Register
*  Read only register
*  Default value: 0x00
*  7:4 PP3-PP0: SM1 program pointer address
*  3:0 RP3-RP0: SM1 reset pointer address
*******************************************************************************/
#define LIS3DSH_PR2_ADDR                     0x7C

/*******************************************************************************
*  TC2_L Register: SM2 General Timer Counter Low Register
*  Read only register
*  Default value: 0x00
*  7:0 TC2_7-TC2_0: SM2 General Timer Counter Low Value
*******************************************************************************/
#define LIS3DSH_TC2_L_ADDR                   0x7D

/*******************************************************************************
*  TC2_H Register: SM2 General Timer Counter High Register
*  Read only register
*  Default value: 0x00
*  15:8 TC2_15-TC2_8: SM2 General Timer Counter High Value
*******************************************************************************/
#define LIS3DSH_TC2_H_ADDR                   0x7E

/*******************************************************************************
*  OUTS2 Register: SM2 Output Set Flag Register
*  Read only register
*  Default value: 0x00
*  7 P_X: 
*         0: X+ noshow 
*         1: X+ show
*  6 N_X: 
*         0: X- noshow
*         1: X- show
*  5 P_Y:  
*         0: Y+ noshow 
*         1: Y+ show
*  4 N_Y:  
*         0: Y- noshow
*         1: Y- show
*  3 P_Z:  
*         0: Z+ noshow 
*         1: Z+ show
*  2 N_Z:  
*         0: Z- noshow
*         1: Z- show
*  1 P_V: 
*         0: V+ noshow
*         1: V+ show
*  0 N_V:  
*         0: V- noshow
*         1: V- show
*******************************************************************************/
#define LIS3DSH_OUTS2_ADDR                   0x7F

/******************************************************************************/
/**************************** END REGISTER MAPPING  ***************************/
/******************************************************************************/
#define I_AM_LIS3DSH                         0x3F

/** @defgroup Sensitivity_selection               
  * @{
  */
#define LIS3DSH_SENSITIVITY_0_06G            0.06  /* 0.06 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_12G            0.12  /* 0.12 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_18G            0.18  /* 0.18 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_24G            0.24  /* 0.24 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_73G            0.73  /* 0.73 mg/digit*/
/**
  * @}
  */

/** @defgroup Data_Rate_Power_Mode_selection                
  * @{
  */
#define LIS3DSH_DATARATE_POWERDOWN           ((uint8_t)0x00)  /* Power Down Mode*/
#define LIS3DSH_DATARATE_3_125               ((uint8_t)0x10)  /* 3.125 Hz Normal Mode */
#define LIS3DSH_DATARATE_6_25                ((uint8_t)0x20)  /* 6.25  Hz Normal Mode */
#define LIS3DSH_DATARATE_12_5                ((uint8_t)0x30)  /* 12.5  Hz Normal Mode */
#define LIS3DSH_DATARATE_25                  ((uint8_t)0x40)  /* 25    Hz Normal Mode */
#define LIS3DSH_DATARATE_50                  ((uint8_t)0x50)  /* 50    Hz Normal Mode */
#define LIS3DSH_DATARATE_100                 ((uint8_t)0x60)  /* 100   Hz Normal Mode */
#define LIS3DSH_DATARATE_400                 ((uint8_t)0x70)  /* 400   Hz Normal Mode */
#define LIS3DSH_DATARATE_800                 ((uint8_t)0x80)  /* 800   Hz Normal Mode */
#define LIS3DSH_DATARATE_1600                ((uint8_t)0x90)  /* 1600  Hz Normal Mode */
/**
  * @}
  */
  
/** @defgroup Full_Scale_selection 
  * @{
  */
#define LIS3DSH_FULLSCALE_2                  ((uint8_t)0x00)  /* 2 g  */
#define LIS3DSH_FULLSCALE_4                  ((uint8_t)0x08)  /* 4 g  */
#define LIS3DSH_FULLSCALE_6                  ((uint8_t)0x10)  /* 6 g  */
#define LIS3DSH_FULLSCALE_8                  ((uint8_t)0x18)  /* 8 g  */
#define LIS3DSH_FULLSCALE_16                 ((uint8_t)0x20)  /* 16 g */
#define LIS3DSH__FULLSCALE_SELECTION         ((uint8_t)0x38)
/**
  * @}
  */
    
/** @defgroup Anti-Aliasing_Filter_Bandwidth 
  * @{
  */
#define LIS3DSH_FILTER_BW_800                ((uint8_t)0x00)  /* 800 Hz */
#define LIS3DSH_FILTER_BW_40                 ((uint8_t)0x08)  /* 40 Hz  */
#define LIS3DSH_FILTER_BW_200                ((uint8_t)0x10)  /* 200 Hz */
#define LIS3DSH_FILTER_BW_50                 ((uint8_t)0x18)  /* 50 Hz  */
/**
  * @}
  */
  
/** @defgroup Self_Test_selection
  * @{
  */
#define LIS3DSH_SELFTEST_NORMAL              ((uint8_t)0x00)
#define LIS3DSH_SELFTEST_P                   ((uint8_t)0x02)
#define LIS3DSH_SELFTEST_M                   ((uint8_t)0x04)
/**
  * @}
  */  

/** @defgroup Direction_XYZ_selection  
  * @{
  */
#define LIS3DSH_X_ENABLE                     ((uint8_t)0x01)
#define LIS3DSH_Y_ENABLE                     ((uint8_t)0x02)
#define LIS3DSH_Z_ENABLE                     ((uint8_t)0x04)
#define LIS3DSH_XYZ_ENABLE                   ((uint8_t)0x07)
/**
  * @}
  */
 
/** @defgroup SPI_Serial_Interface_Mode_selection  
  * @{
  */
#define LIS3DSH_SERIALINTERFACE_4WIRE        ((uint8_t)0x00)
#define LIS3DSH_SERIALINTERFACE_3WIRE        ((uint8_t)0x01)
/**
  * @}
  */ 

/** @defgroup Interrupt_Request_selection    Interrupt_Selection_Enable
  * @{
  */
#define LIS3DSH_INTERRUPT_REQUEST_LATCHED    ((uint8_t)0x00)
#define LIS3DSH_INTERRUPT_REQUEST_PULSED     ((uint8_t)0x20)
/**
  * @}
  */ 

/** @defgroup Interrupt_Selection_Enable
  * @{
  */
#define LIS3DSH_INTERRUPT_1_ENABLE           ((uint8_t)0x88)
#define LIS3DSH_INTERRUPT_2_ENABLE           ((uint8_t)0x00)
#define LIS3DSH_INTERRUPT_1_2_ENABLE         ((uint8_t)0x88)
/**
  * @}
  */ 

/** @defgroup Interrupt_Signal_Active_Selection
  * @{
  */
#define LIS3DSH_INTERRUPT_SIGNAL_LOW         ((uint8_t)0x00)
#define LIS3DSH_INTERRUPT_SIGNAL_HIGH        ((uint8_t)0x40)
/**
  * @}
  */ 

/** @defgroup State_Machine_Enable
  * @{
  */
#define LIS3DSH_SM_ENABLE                   ((uint8_t)0x01)
#define LIS3DSH_SM_DISABLE                  ((uint8_t)0x00)
/**
  * @}
  */ 
     
/** @defgroup State_Machine_Routed_Interrupt
  * @{
  */
#define LIS3DSH_SM_INT1                     ((uint8_t)0x00)
#define LIS3DSH_SM_INT2                     ((uint8_t)0x08)
/**
  * @}
  */ 

/** @defgroup Boot_Mode_selection
  * @{
  */
#define LIS3DSH_BOOT_NORMALMODE              ((uint8_t)0x00)
#define LIS3DSH_BOOT_FORCED                  ((uint8_t)0x80)
/**
  * @}
  */   


/** @defgroup FIFO_Mode_selection 
  * @{
  */
#define LIS3DSH_FIFO_BYPASS_MODE             ((uint8_t)0x00)
#define LIS3DSH_FIFO_MODE                    ((uint8_t)0x20)
#define LIS3DSH_FIFO_STREAM_MODE             ((uint8_t)0x40)
#define LIS3DSH_FIFO_SF_TRIGGER_MODE         ((uint8_t)0x60)
#define LIS3DSH_FIFO_BS_TRIGGER_MODE         ((uint8_t)0x80)
#define LIS3DSH_FIFO_BF_TRIGGER_MODE         ((uint8_t)0xE0)
/**
  * @}
  */

/**
  * @}
  */ 
  
/** @defgroup LIS3DSH_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup LIS3DSH_Exported_Functions
  * @{
  */ 
void    LIS3DSH_Init(uint16_t InitStruct);
void    LIS3DSH_DeInit(void);
uint8_t LIS3DSH_ReadID(void);
void    LIS3DSH_InterruptConfig(LIS3DSH_InterruptConfigTypeDef *LIS3DSH_IntConfigStruct);
void    LIS3DSH_Click_IntConfig(void);
void    LIS3DSH_ODR_LowpowerCmd(uint8_t ODR_LowPowerMode);
void    LIS3DSH_DataRateCmd(uint8_t DataRateValue);
void    LIS3DSH_FullScaleCmd(uint8_t FS_value);
void    LIS3DSH_RebootCmd(void);
void    LIS3DSH_ReadACC(int16_t *pData);

/* Accelerometer driver structure */
extern ACCELERO_DrvTypeDef Lis3dshDrv;

/* Accelerometer IO functions */  
void    ACCELERO_IO_Init(void);
void    ACCELERO_IO_ITConfig(void);
void    ACCELERO_IO_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void    ACCELERO_IO_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);

#ifdef __cplusplus
}
#endif

#endif /* __LIS3DSH_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
