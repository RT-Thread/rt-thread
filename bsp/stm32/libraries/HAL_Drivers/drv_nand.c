/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-09-28     mingmiaojing      first version
 */

#include <rtconfig.h>
#ifdef BSP_USING_NAND1
#include <board.h>
#include "drv_nand.h"
#include "drv_config.h"

#include <lpm.h>

#define NAND_PAGE_SIZE             ((uint16_t)2048)
#define NAND1_RW_TEST
#ifndef RT_FIOGETXIPADDR
    #define RT_FIOGETXIPADDR 0x52540001U
#endif

struct rt_device _hw_nand1;
NAND_HandleTypeDef hnand1;

/* FSMC initialization function */
static void rt_nand_init(void)
{
  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NAND_PCC_TimingTypeDef ComSpaceTiming = {0};
  FSMC_NAND_PCC_TimingTypeDef AttSpaceTiming = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the NAND1 memory initialization sequence
  */
  hnand1.Instance = FSMC_NAND_DEVICE;
  /* hnand1.Init */
  hnand1.Init.NandBank = FSMC_NAND_BANK2;
  hnand1.Init.Waitfeature = FSMC_NAND_PCC_WAIT_FEATURE_ENABLE;
  hnand1.Init.MemoryDataWidth = FSMC_NAND_PCC_MEM_BUS_WIDTH_8;
  hnand1.Init.EccComputation = FSMC_NAND_ECC_ENABLE;
  hnand1.Init.ECCPageSize = FSMC_NAND_ECC_PAGE_SIZE_512BYTE;
  hnand1.Init.TCLRSetupTime = 0;
  hnand1.Init.TARSetupTime = 0;
  /* hnand1.Config */
  hnand1.Config.PageSize = NAND_PAGE_SIZE;
  hnand1.Config.SpareAreaSize = 64;
  hnand1.Config.BlockSize = 64;
  hnand1.Config.BlockNbr = 1024;
  hnand1.Config.PlaneNbr = 1;
  hnand1.Config.PlaneSize = 1024;
  hnand1.Config.ExtraCommandEnable = DISABLE;
  /* ComSpaceTiming */
  ComSpaceTiming.SetupTime = 4;
  ComSpaceTiming.WaitSetupTime = 3;
  ComSpaceTiming.HoldSetupTime = 2;
  ComSpaceTiming.HiZSetupTime = 4;
  /* AttSpaceTiming */
  AttSpaceTiming.SetupTime = 4;
  AttSpaceTiming.WaitSetupTime = 3;
  AttSpaceTiming.HoldSetupTime = 2;
  AttSpaceTiming.HiZSetupTime = 4;

  if (HAL_NAND_Init(&hnand1, &ComSpaceTiming, &AttSpaceTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

rt_err_t  rt_nand_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

rt_err_t  rt_nand_control(rt_device_t dev, int cmd, void *args)
{
    if(RT_DEVICE_CTRL_BLK_GETGEOME == cmd)
    {
        struct rt_device_blk_geometry *geometry = (struct rt_device_blk_geometry *)args;
        geometry->bytes_per_sector = 2048;
        geometry->sector_count = 64 * 1024;
        geometry->block_size = 2048 * 64;
        return RT_EOK;
    }
    else if(RT_FIOGETXIPADDR == cmd)
    {
        uint32_t *start_addr = (uint32_t *)args;
        *start_addr = 0;
        return RT_EOK;
    }
    else if(RT_DEVICE_CTRL_BLK_ERASE == cmd)
    {
        uint32_t *blk = (uint32_t *)args;
        NAND_AddressTypeDef Addr;
        Addr.Plane = 0x00;
        Addr.Block = *blk;
        Addr.Page = 0x00;
        HAL_NAND_Erase_Block(&hnand1,&Addr);
        return RT_EOK;
    }

    return -RT_ERROR;
}

/*pos: sector offset   size: page count*/
rt_ssize_t rt_nand_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    uint32_t page_cnt = size;
    NAND_AddressTypeDef ReadAddr;
    ReadAddr.Page = pos%64;
    ReadAddr.Plane = 0;
    ReadAddr.Block = pos/64;
    HAL_NAND_Read_Page(&hnand1, &ReadAddr, (uint8_t *)buffer, page_cnt);
    return RT_EOK;
}

rt_ssize_t rt_nand_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    uint32_t page_cnt = size;
    NAND_AddressTypeDef WriteAddr;
    WriteAddr.Page = pos%64;
    WriteAddr.Plane = 0;
    WriteAddr.Block = pos/64;
    HAL_NAND_Write_Page(&hnand1, &WriteAddr, (uint8_t *)buffer, page_cnt);
    return RT_EOK;
}

static int stm32_nand1_init(void)
{
    NAND_IDTypeDef NAND_ID;
    rt_nand_init();
    HAL_NAND_Read_ID(&hnand1, &NAND_ID);
    rt_kprintf("Nand Flash ID = 0x%02X,0x%02X,0x%02X,0x%02X",
                NAND_ID.Maker_Id, NAND_ID.Device_Id,
                NAND_ID.Third_Id, NAND_ID.Fourth_Id);

#ifdef NAND1_RW_TEST
    uint32_t i = 0;
    static uint8_t TxBuffer [NAND_PAGE_SIZE];
    static uint8_t RxBuffer [NAND_PAGE_SIZE];
    NAND_AddressTypeDef WriteReadAddr;

    WriteReadAddr.Plane = 0x00;
    WriteReadAddr.Block = 0x00;
    WriteReadAddr.Page = 0x00;

    /* Erase the NAND first Block */
    for(i = 0; i < 64; i++)
    {
        WriteReadAddr.Block = i;
        HAL_NAND_Erase_Block(&hnand1,&WriteReadAddr);
    }

//  /* Fill the buffer to send */
//  for (i = 0; i < NAND_PAGE_SIZE; i++ )
//  {
//      TxBuffer[i] = i;
//  }
//
//  /* Write data to FMC NAND memory */
//  HAL_NAND_Write_Page(&hnand1, &WriteReadAddr, TxBuffer, 1);
//  rt_kprintf("\r\nWritten to the number:\r\n");
//  for(i = 0; i < 2048; i++)
//  {
//      rt_kprintf("0x%02X \t",TxBuffer[i]);
//  }
//  rt_kprintf("\n");
//  HAL_Delay(100);
    /* Read data from FMC NAND memory */
    WriteReadAddr.Block = 0;
    HAL_NAND_Read_Page(&hnand1, &WriteReadAddr, RxBuffer, 1);
    rt_kprintf("\r\nRead receive: \r\n");
    for(i = 0; i < 16; i++)
    {
      rt_kprintf("0x%02X \t",RxBuffer[i]);
    }
    rt_kprintf("\n");
#endif

    //_hw_nand1.ops    = &_hw_nand1;
    _hw_nand1.type     = RT_Device_Class_MTD;
    _hw_nand1.init     = RT_NULL;//rt_nand_init
    _hw_nand1.open     = rt_nand_open;
    _hw_nand1.close    = RT_NULL;
    _hw_nand1.read     = rt_nand_read;
    _hw_nand1.write    = rt_nand_write;
    _hw_nand1.control  = rt_nand_control;
    _hw_nand1.user_data  = RT_NULL;

    rt_device_register(&_hw_nand1,"nand1", RT_DEVICE_FLAG_RDWR);

    rt_kprintf("nand1 init done\n");

    lpm_init();
    lpm_dev_blk_append(&_hw_nand1);
    return 0;
}
INIT_BOARD_EXPORT(stm32_nand1_init);


#endif
