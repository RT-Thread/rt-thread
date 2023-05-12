/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fnand_id.c
 * Date: 2022-07-06 08:34:27
 * LastEditTime: 2022-07-06 08:34:27
 * Description:  This file is for functions in this file are the read id required functions
 * for this driver. 
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */
#include "fdebug.h"
#include "fnand.h"
#include "fnand_id.h"
#include "fnand_common_cmd.h"
#include "fdebug.h"
#include "fkernel.h"
#include "sdkconfig.h"

#define CONFIG_FNAND_ID_DEBUG_EN
#define FNAND_ID_DEBUG_TAG "FNAND_ID"
#ifdef CONFIG_FNAND_ID_DEBUG_EN

    #define FNAND_ID_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_ID_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_ID_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_ID_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_ID_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_ID_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_ID_DEBUG_D(format, ...) FT_DEBUG_PRINT_D(FNAND_ID_DEBUG_TAG, format, ##__VA_ARGS__)
#else
    #define FNAND_ID_DEBUG_I(format, ...)
    #define FNAND_ID_DEBUG_W(format, ...)
    #define FNAND_ID_DEBUG_E(format, ...)
    #define FNAND_ID_DEBUG_D(format, ...)
#endif


/*
 * NAND Flash Manufacturer ID Codes
 */
#define NAND_MFR_TOSHIBA    0x98


/* Cell info constants */
#define NAND_CI_CHIPNR_MSK  0x03
#define NAND_CI_CELLTYPE_MSK    0x0C
#define NAND_CI_CELLTYPE_SHIFT  2



#define NAND_MAX_ID_LEN 8



extern FError FNandToggleInit(FNand *instance_p, u32 chip_addr);
extern FError FNandOnfiInit(FNand *instance_p, u32 chip_addr);
extern FError FNandTimingInterfaceUpdate(FNand *instance_p, u32 chip_addr);

extern const struct FNandManuFacturerOps toshiba_ops;

static const FNandManuFacturer fnand_manufacturers[] =
{
    {NAND_MFR_TOSHIBA, "Toshiba", &toshiba_ops},
};

static int FnandIdHasPeriod(u8 *id_data_p, int arrlen, int period)
{
    int i, j;
    for (i = 0; i < period; i++)
        for (j = i + period; j < arrlen; j += period)
            if (id_data_p[i] != id_data_p[j])
            {
                return 0;
            }
    return 1;
}

static int FNandIdLen(u8 *id_data_p, int data_length)
{
    int last_nonzero, period;

    for (last_nonzero = data_length - 1; last_nonzero >= 0; last_nonzero--)
        if (id_data_p[last_nonzero])
        {
            break;
        }

    /* All zeros */
    if (last_nonzero < 0)
    {
        return 0;
    }

    /* Calculate wraparound period */
    for (period = 1; period < data_length; period++)
        if (FnandIdHasPeriod(id_data_p, data_length, period))
        {
            break;
        }

    /* There's a repeated pattern */
    if (period < data_length)
    {
        return period;
    }

    /* There are trailing zeros */
    if (last_nonzero < data_length - 1)
    {
        return last_nonzero + 1;
    }

    /* No pattern detected */
    return data_length;

}


const FNandManuFacturer *FNandGetManuFacturer(u8 id)
{
    u32 i;

    for (i = 0; i < ARRAY_SIZE(fnand_manufacturers); i++)
    {
        if (fnand_manufacturers[i].id == id)
        {
            return &fnand_manufacturers[i];
        }
    }
    return NULL;
}


static FError FNandIdDetect(FNand *instance_p, u32 chip_addr)
{
    FError ret;
    u32 i;
    FNandId nand_id;
    u8 *id_data = (u8 *)&nand_id.data;
    u8 maf_id, dev_id;
    const FNandManuFacturer *manufacturer_p ;


    ret = FNandFlashReset(instance_p, chip_addr);
    if (ret != FT_SUCCESS)
    {
        FNAND_ID_DEBUG_E("FNandFlashReset is error");
        return ret;
    }

    /* step2  read device ID */
    ret = FNandFlashReadId(instance_p, 0, id_data, 2, chip_addr);
    if (ret != FT_SUCCESS)
    {
        FNAND_ID_DEBUG_E("FNandFlashReadId is error");
        return ret;
    }

    /* Read manufacturer and device IDs */
    maf_id = id_data[0];
    dev_id = id_data[1];

    /* step 3 get entire device ID*/
    ret = FNandFlashReadId(instance_p, 0, id_data, sizeof(nand_id.data), chip_addr);
    if (ret != FT_SUCCESS)
    {
        FNAND_ID_DEBUG_E("FNandFlashReadId is error");
        return ret;
    }
    /* step 5 compare ID string and device id */
    if (id_data[0] != maf_id || id_data[1] != dev_id)
    {
        FNAND_ID_DEBUG_E("Second ID read did not match %02x,%02x against %02x,%02x\n",
                         maf_id, dev_id, id_data[0], id_data[1]);
        return FNAND_ERR_NOT_MATCH;
    }

    nand_id.len = FNandIdLen(id_data, ARRAY_SIZE(nand_id.data));

    /* step 6 通过maf_id获取对应的参数 */
    manufacturer_p = FNandGetManuFacturer(maf_id);

    if (manufacturer_p == NULL)
    {
        FNAND_ID_DEBUG_E("Manufacturer not in list");
        return FNAND_ERR_NOT_MATCH;
    }

    FNAND_ID_DEBUG_I("Find manufacturer");
    if (manufacturer_p->ops->detect)
    {
        FNAND_ID_DEBUG_I("manufacturer_p->ops->detect function work");
        return manufacturer_p->ops->detect(instance_p, &nand_id, chip_addr);
    }
    else
    {
        FNAND_ID_DEBUG_E("Manufacturer detect is empty");
        return FNAND_ERR_NOT_MATCH;
    }

    return FT_SUCCESS;
}

FError FNandDetect(FNand *instance_p)
{
    FError ret;
    u32 i = 0;

    for (i = 0; i < FNAND_CONNECT_MAX_NUM; i++)
    {
        ret = FNandIdDetect(instance_p, i);
        if (ret != FT_SUCCESS)
        {
            FNAND_ID_DEBUG_W("Normal flash is not found");
        }
        else
        {
            FNandFlashFuncRegister(instance_p) ;
            FNAND_ID_DEBUG_I("Normal flash is found");
            continue;
        }


        ret = FNandToggleInit(instance_p, i); /* toggle 1.0 */
        if (ret != FT_SUCCESS)
        {
            FNAND_ID_DEBUG_W("Toggle flash is not found");
        }
        else
        {
            FNAND_ID_DEBUG_I("Scan %d nand is toggle mode", i);
            instance_p->nand_flash_interface[i] = FNAND_TOGGLE_MODE;
            ret = FNandTimingInterfaceUpdate(instance_p, i);
            if (ret != FT_SUCCESS)
            {
                FNAND_ID_DEBUG_E("FNandTimingInterfaceUpdate is error");
                return ret;
            }
            /* open ecc length config */
            FNandFlashFuncRegister(instance_p) ;
            FNAND_ID_DEBUG_I("Toggle flash is found");
            continue;
        }

        ret = FNandOnfiInit(instance_p, i);
        if (ret != FT_SUCCESS)
        {
            FNAND_ID_DEBUG_W("Onfi flash is not found");
        }
        else
        {
            instance_p->nand_flash_interface[i] = FNAND_ONFI_MODE;
            ret = FNandTimingInterfaceUpdate(instance_p, i);
            if (ret != FT_SUCCESS)
            {
                FNAND_ID_DEBUG_E("FNandTimingInterfaceUpdate is error");
                return ret;
            }
            /* open ecc length config ,需要确保 ecc 校验的空间必须小于oob 的空间*/
            FNandFlashFuncRegister(instance_p) ;
            FNAND_ID_DEBUG_I("Onfi flash is found");
            continue;
        }

    }
    return FT_SUCCESS;
}
