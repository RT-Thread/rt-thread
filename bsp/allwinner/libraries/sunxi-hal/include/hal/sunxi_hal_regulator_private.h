/*
 * Copyright (c) 2020 Allwinner Technology Co., Ltd. ALL rights reserved.
 */

#ifndef __SUNXI_HAL_REGULATOR_PRI_H__
#define __SUNXI_HAL_REGULATOR_PRI_H__
#ifdef __cplusplus
extern "C" {
#endif

typedef short           s16;
typedef long long int       s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long long int  u64;
int hal_axp_byte_read(struct regulator_dev *rdev, u8 reg, u8 *reg_val);
int hal_axp_byte_write(struct regulator_dev *rdev, u8 reg, u8 reg_val);
int hal_axp_byte_update(struct regulator_dev *rdev, u8 reg, u8 val, u8 mask);

#ifdef __cplusplus
}
#endif

#endif
