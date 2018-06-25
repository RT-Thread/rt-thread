#ifndef    USER_APP
#define USER_APP
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbutils.h"

/* -----------------------Slave Defines -------------------------------------*/
#define S_DISCRETE_INPUT_START        0
#define S_DISCRETE_INPUT_NDISCRETES   16
#define S_COIL_START                  0
#define S_COIL_NCOILS                 64
#define S_REG_INPUT_START             (0x0000)
#define S_REG_INPUT_NREGS             (0x0006 - 0x0000)
#define S_REG_HOLDING_START           0
#define S_REG_HOLDING_NREGS           (0x004B)
/* salve mode: holding register's all address */
#define          S_HD_RESERVE                     0
/* salve mode: input register's all address */
#define          S_IN_RESERVE                     0
/* salve mode: coil's all address */
#define          S_CO_RESERVE                     0
/* salve mode: discrete's all address */
#define          S_DI_RESERVE                     0
/* slave mode: holding register"s startup address */

/* -----------------------Master Defines -------------------------------------*/
#define M_DISCRETE_INPUT_START        1
#define M_DISCRETE_INPUT_NDISCRETES   16
#define M_COIL_START                  1
#define M_COIL_NCOILS                 64
#define M_REG_INPUT_START             1
#define M_REG_INPUT_NREGS             100
#define M_REG_HOLDING_START           1
#define M_REG_HOLDING_NREGS           100
/* master mode: holding register's all address */
#define          M_HD_RESERVE                     0
/* master mode: input register's all address */
#define          M_IN_RESERVE                     0
/* master mode: coil's all address */
#define          M_CO_RESERVE                     0
/* master mode: discrete's all address */
#define          M_DI_RESERVE                     0

#endif
