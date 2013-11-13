#ifndef	USER_APP
#define USER_APP
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbutils.h"

/* -----------------------Slave Defines -------------------------------------*/
#define S_DISCRETE_INPUT_START        1
#define S_DISCRETE_INPUT_NDISCRETES   16
#define S_COIL_START                  1
#define S_COIL_NCOILS                 64
#define S_REG_INPUT_START             1
#define S_REG_INPUT_NREGS             100
#define S_REG_HOLDING_START           1
#define S_REG_HOLDING_NREGS           100
//从机模式：在保持寄存器中，各个地址对应的功能定义
#define          S_HD_RESERVE                     0		  //保留
#define          S_HD_CPU_USAGE_MAJOR             1         //当前CPU利用率的整数位
#define          S_HD_CPU_USAGE_MINOR             2         //当前CPU利用率的小数位

//从机模式：在输入寄存器中，各个地址对应的功能定义
#define          S_IN_RESERVE                     0		  //保留

//从机模式：在线圈中，各个地址对应的功能定义
#define          S_CO_RESERVE                     2		  //保留

//从机模式：在离散输入中，各个地址对应的功能定义
#define          S_DI_RESERVE                     1		  //保留

/* -----------------------Master Defines -------------------------------------*/
#define M_DISCRETE_INPUT_START        1
#define M_DISCRETE_INPUT_NDISCRETES   16
#define M_COIL_START                  1
#define M_COIL_NCOILS                 64
#define M_REG_INPUT_START             1
#define M_REG_INPUT_NREGS             100
#define M_REG_HOLDING_START           1
#define M_REG_HOLDING_NREGS           100
//主机模式：在保持寄存器中，各个地址对应的功能定义
#define          M_HD_RESERVE                     0		  //保留

//主机模式：在输入寄存器中，各个地址对应的功能定义
#define          M_IN_RESERVE                     0		  //保留

//主机模式：在线圈中，各个地址对应的功能定义
#define          M_CO_RESERVE                     2		  //保留

//主机模式：在离散输入中，各个地址对应的功能定义
#define          M_DI_RESERVE                     1		  //保留

#endif
