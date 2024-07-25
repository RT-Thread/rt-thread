#include "drv_lpadc.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_inputmux.h"
#include "fsl_romapi.h"
#include "fsl_clock.h"
#include "fsl_reset.h"

#include <rtdevice.h>

#define SECTOR_INDEX_FROM_END 2U /* start from the last 2 page*/
#define BUFFER_LEN 512 / 4

struct mcx_mtd_chipflash
{
    struct rt_mtd_nor_device mtd_device;
    flash_config_t s_flashDriver;     //flash driver
    uint32_t s_buffer[BUFFER_LEN];
    uint32_t destAdrss;/* Address of the target location */
    uint32_t pflashBlockBase ;//块基地址
    uint32_t pflashTotalSize ;//扇区大小
    uint32_t pflashSectorSize;//flash 总大小
    uint32_t PflashPageSize  ;//页大小
};

struct mcx_mtd_chipflash mtd;

rt_err_t nxp_chipflash_read_id (struct rt_mtd_nor_device* device)
{
    //因为是片上flash 就不读id了
    return 0;
}
/**
 * device MTD nor 设备句柄
 * offset 偏移量
 * data 读取的数据
 * length 读取的数据长度
 */
rt_ssize_t nxp_chipflash_read   (struct rt_mtd_nor_device* device, rt_off_t offset, rt_uint8_t* data, rt_size_t length)
{
    for(int i = 0; i < length; i++)
    {
        *(data + i) = *(volatile rt_uint8_t *)(mtd.destAdrss + offset + i);
    }
    return length;
}

/**
 * device MTD nor 设备句柄
 * offset 偏移量
 * data 读取的数据
 * length 读取的数据长度
 */
rt_ssize_t nxp_chipflash_write   (struct rt_mtd_nor_device* device, rt_off_t offset, const rt_uint8_t* data, rt_size_t length)
{
    //rt_kprintf("%s %d\n","nxp_chipflash_write", *data);
    int32_t status = FLASH_API->flash_program_page(&mtd.s_flashDriver, mtd.destAdrss + offset, (uint8_t *)data, length);
    if (status != kStatus_Success)
    {
        return 0;
    }
    return length;
}

/**
 * device MTD nor 设备句柄
 * offset 偏移量
 * length 长度
 */
rt_err_t nxp_chipflash_erase_block (struct rt_mtd_nor_device* device, rt_off_t offset, rt_size_t length)
{
    FLASH_API->flash_erase_sector(&mtd.s_flashDriver, mtd.destAdrss, mtd.pflashSectorSize, kFLASH_ApiEraseKey);
    return RT_EOK;
}

struct rt_mtd_nor_driver_ops mcx_mtd_chipflashops =
{
    nxp_chipflash_read_id,
    nxp_chipflash_read,
    nxp_chipflash_write,
    nxp_chipflash_erase_block,
};

rt_err_t rt_onchipflash_init(const char* mtd_name)
{
    
    memset(&mtd.s_flashDriver, 0, sizeof(flash_config_t));
    if (FLASH_API->flash_init(&mtd.s_flashDriver) != kStatus_Success)
    {
        return RT_ERROR;
    }
    //获取参数
    FLASH_API->flash_get_property(&mtd.s_flashDriver, kFLASH_PropertyPflashBlockBaseAddr, &mtd.pflashBlockBase);
    FLASH_API->flash_get_property(&mtd.s_flashDriver, kFLASH_PropertyPflashSectorSize, &mtd.pflashSectorSize);
    FLASH_API->flash_get_property(&mtd.s_flashDriver, kFLASH_PropertyPflashTotalSize, &mtd.pflashTotalSize);
    FLASH_API->flash_get_property(&mtd.s_flashDriver, kFLASH_PropertyPflashPageSize, &mtd.PflashPageSize);
    //记录flash地址数据 
    //flsh基地址+ flash中大小 - 数量* 扇区大小
    mtd.destAdrss = mtd.pflashBlockBase + (mtd.pflashTotalSize - (SECTOR_INDEX_FROM_END) * mtd.pflashSectorSize);
    int32_t status = FLASH_API->flash_erase_sector(&mtd.s_flashDriver, mtd.destAdrss, mtd.pflashSectorSize, kFLASH_ApiEraseKey);
    if (status != kStatus_Success)
    {
        return RT_ERROR;
    }
    mtd.mtd_device.block_start = 512;
    mtd.mtd_device.block_start = 0;
    mtd.mtd_device.ops = &mcx_mtd_chipflashops;
    rt_mtd_nor_register_device(mtd_name, &(mtd.mtd_device));
    return RT_EOK;

}

