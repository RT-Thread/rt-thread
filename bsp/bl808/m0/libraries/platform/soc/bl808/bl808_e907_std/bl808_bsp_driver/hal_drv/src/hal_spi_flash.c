/**
 * @file spi_hal_flash.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "bl808_common.h"
#include "bl808_glb.h"
#include "bl808_gpio.h"
#include "bl808_spi.h"
#include "hal_spi_flash.h"


#define SPI_USE_ID                              SPI0_ID
#define SPI_PAD_ACT                             GLB_SPI_PAD_ACT_AS_MASTER
#define SPI_USE_IRQ                             SPI0_IRQn
#define SPI_FLASH_BLK32K_SIZE                   (32 * 1024)
#define SPI_FLASH_BLK64K_SIZE                   (64 * 1024)
#define SPI_FLASH_DELAY_L                       (arch_delay_ms(1))
#define SPI_FLASH_DELAY_H                       (arch_delay_ms(2))

static uint8_t spi_flash_cs_gpio = GLB_GPIO_PIN_4;
static uint8_t spi_flash_clk_gpio = GLB_GPIO_PIN_3;
static uint8_t spi_flash_mosi_gpio = GLB_GPIO_PIN_2;
static uint8_t spi_flash_miso_gpio = GLB_GPIO_PIN_1;


/**
 * @brief SPI interrupt callback
 *
 * @return None
 */
static void SPI_Int_Callback(void)
{

}

/**
 * @brief spi flash pull cs gpio low
 *
 * @return None
 */
static __inline void spi_flash_pull_cs_low(void)
{
    GLB_GPIO_Write(spi_flash_cs_gpio, 0);
}

/**
 * @brief spi flash pull cs gpio high
 *
 * @return None
 */
static __inline void spi_flash_pull_cs_high(void)
{
    GLB_GPIO_Write(spi_flash_cs_gpio, 1);
}

/**
 * @brief spi flash gpio init
 *
 * @return None
 */
static void spi_flash_gpio_init(void)
{
    GLB_GPIO_Type gpioPins[3] = {spi_flash_clk_gpio, spi_flash_mosi_gpio, spi_flash_miso_gpio};
    GLB_GPIO_Cfg_Type gpioCfg = {
        /* CS */
        .gpioPin=spi_flash_cs_gpio,
        .gpioFun=11,
        .gpioMode=GPIO_MODE_OUTPUT,
        .pullType=GPIO_PULL_NONE,
        .drive=3,
        .smtCtrl=1
    };

    GLB_GPIO_Func_Init(GPIO_FUN_SPI0, (GLB_GPIO_Type *)gpioPins, sizeof(gpioPins)/sizeof(gpioPins[0]));
    GLB_GPIO_Init(&gpioCfg);
    spi_flash_pull_cs_high();

    if(SPI0_ID == SPI_USE_ID){
        GLB_Set_MCU_SPI_0_ACT_MOD_Sel(SPI_PAD_ACT);
    }else{
        GLB_Set_DSP_SPI_0_ACT_MOD_Sel(SPI_PAD_ACT);
    }
}

/**
 * @brief write enable
 *
 * @return None
 */
static void spi_flash_write_enable(void)
{
    uint8_t cmd[256] = {0};

    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_8);
    spi_flash_pull_cs_low();
    cmd[0] = 0x06;
    SPI_SendData(SPI_USE_ID,cmd,1,SPI_TIMEOUT_ENABLE);
    spi_flash_pull_cs_high();
}

/**
 * @brief wait not busy
 *
 * @return None
 */
static void spi_flash_wait_notbusy(void)
{
    uint32_t wdata[1] = {0x05};
    uint32_t rdata[1] = {0};

    while(1){
        spi_flash_pull_cs_low();
        SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_24);
        SPI_SendRecvData(SPI_USE_ID, wdata, rdata, 1, SPI_TIMEOUT_ENABLE);
        spi_flash_pull_cs_high();

        if(((uint8_t *)rdata)[1]&0x1){
            continue;
        }else{
            break;
        }
    }
}

/****************************************************************************//**
 * @brief  wait WEL 0
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
/**
 * @brief wait WEL 0
 *
 * @return None
 */
static void spi_flash_wait_wel_0(void)
{
    uint32_t wdata[1] = {0x05};
    uint32_t rdata[1] = {0};

    while(1){
        spi_flash_pull_cs_low();
        SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_24);
        SPI_SendRecvData(SPI_USE_ID, wdata, rdata, 1, SPI_TIMEOUT_ENABLE);
        spi_flash_pull_cs_high();

        if(((uint8_t *)rdata)[1]&(1<<1)){
            continue;
        }else{
            break;
        }
    }
}

/**
 * @brief wait WEL 1
 *
 * @return None
 */
static void spi_flash_wait_wel_1(void)
{
    uint32_t wdata[1] = {0x05};
    uint32_t rdata[1] = {0};

    while(1){
        spi_flash_pull_cs_low();
        SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_24);
        SPI_SendRecvData(SPI_USE_ID, wdata, rdata, 1, SPI_TIMEOUT_ENABLE);
        spi_flash_pull_cs_high();

        if(((uint8_t *)rdata)[1]&(1<<1)){
            break;
        }else{
            continue;
        }
    }
}

/**
 * @brief spi flash sector erase
 *
 * @param sector number
 * @return BL_Err_Type
 */
static BL_Err_Type spi_flash_sector_erase(uint32_t secNum)
{
    BL_Err_Type stat = SUCCESS;
    uint32_t wdata[1] = {0};

    spi_flash_wait_notbusy();
    spi_flash_write_enable();

    spi_flash_pull_cs_low();
    ((uint8_t *)wdata)[0] = 0x20;
    ((uint8_t *)wdata)[1] = ((secNum*4*1024)>>16)&0xFF;
    ((uint8_t *)wdata)[2] = ((secNum*4*1024)>>8)&0xFF;
    ((uint8_t *)wdata)[3] = ((secNum*4*1024)>>0)&0xFF;

    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_32);
    stat = SPI_SendData(SPI_USE_ID, wdata, 1, SPI_TIMEOUT_ENABLE);
    spi_flash_pull_cs_high();

    spi_flash_wait_notbusy();
    spi_flash_wait_wel_0();

    return stat;
}

/**
 * @brief spi flash block 32k erase
 *
 * @param block number
 * @return BL_Err_Type
 */
static BL_Err_Type spi_flash_blk32_erase(uint32_t blkNum)
{
    BL_Err_Type stat = SUCCESS;
    uint32_t wdata[1] = {0};

    spi_flash_wait_notbusy();
    spi_flash_write_enable();

    spi_flash_pull_cs_low();
    ((uint8_t *)wdata)[0] = 0x52;
    ((uint8_t *)wdata)[1] = ((blkNum*SPI_FLASH_BLK32K_SIZE)>>16)&0xFF;
    ((uint8_t *)wdata)[2] = ((blkNum*SPI_FLASH_BLK32K_SIZE)>>8)&0xFF;
    ((uint8_t *)wdata)[3] = ((blkNum*SPI_FLASH_BLK32K_SIZE)>>0)&0xFF;

    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_32);
    stat = SPI_SendData(SPI_USE_ID, wdata, 1, SPI_TIMEOUT_ENABLE);
    spi_flash_pull_cs_high();

    spi_flash_wait_notbusy();
    spi_flash_wait_wel_0();

    return stat;
}

/**
 * @brief spi flash block 64k erase
 *
 * @param block number
 * @return BL_Err_Type
 */
static BL_Err_Type spi_flash_blk64_erase(uint32_t blkNum)
{
    BL_Err_Type stat = SUCCESS;
    uint32_t wdata[1] = {0};

    spi_flash_wait_notbusy();
    spi_flash_write_enable();

    spi_flash_pull_cs_low();
    ((uint8_t *)wdata)[0] = 0xd8;
    ((uint8_t *)wdata)[1] = ((blkNum*SPI_FLASH_BLK64K_SIZE)>>16)&0xFF;
    ((uint8_t *)wdata)[2] = ((blkNum*SPI_FLASH_BLK64K_SIZE)>>8)&0xFF;
    ((uint8_t *)wdata)[3] = ((blkNum*SPI_FLASH_BLK64K_SIZE)>>0)&0xFF;

    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_32);
    stat = SPI_SendData(SPI_USE_ID, wdata, 1, SPI_TIMEOUT_ENABLE);
    spi_flash_pull_cs_high();

    spi_flash_wait_notbusy();
    spi_flash_wait_wel_0();

    return stat;
}

/**
 * @brief spi flash page write
 *
 * @param  flashAddr: flash address
 * @param  wBuff: write buff
 * @param  wLen: write length
 * @return BL_Err_Type
 */
static BL_Err_Type spi_flash_page_write(uint32_t flashAddr, uint8_t *wBuff, uint32_t wLen)
{
    uint32_t i;
    uint8_t cmd[260] = {0};

    if ((!wLen) || (wLen>256)) {
        SPI_FLASH_DELAY_H;
        return ERROR;
    }
    if (flashAddr & 0xFF) {
        SPI_FLASH_DELAY_H;
    }

    spi_flash_wait_notbusy();
    spi_flash_write_enable();
    spi_flash_wait_wel_1();

    spi_flash_pull_cs_low();
    cmd[0] = 0x02;
    cmd[1] = (flashAddr>>16)&0xFF;
    cmd[2] = (flashAddr>>8)&0xFF;
    cmd[3] = (flashAddr>>0)&0xFF;
    for (i=0; i<wLen; i++) {
        cmd[i+4] = wBuff[i];
    }
    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_8);
    SPI_SendData(SPI_USE_ID, cmd, wLen+4, SPI_TIMEOUT_DISABLE);
    spi_flash_pull_cs_high();

    return SUCCESS;
}

/**
 * @brief spi flash page read
 *
 * @param  flashAddr: flash address
 * @param  rBuff: read buff
 * @param  rLen: read length
 * @return BL_Err_Type
 */
static BL_Err_Type spi_flash_page_read(uint32_t flashAddr, uint8_t *rBuff, uint32_t rLen)
{
    uint32_t i;
    uint8_t cmd[260] = {0};
    uint8_t resp[260] = {0};
    BL_Err_Type stat = SUCCESS;

    if ((!rLen) || (rLen>256)) {
        SPI_FLASH_DELAY_L;
        return ERROR;
    }
    if (flashAddr & 0xFF) {
        SPI_FLASH_DELAY_H;
    }

    spi_flash_wait_notbusy();

    spi_flash_pull_cs_low();
    cmd[0] = 0x03;
    cmd[1] = (flashAddr>>16)&0xFF;
    cmd[2] = (flashAddr>>8)&0xFF;
    cmd[3] = (flashAddr>>0)&0xFF;
    for (i=4; i<260; i++) {
        cmd[i] = 0;
    }
    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_8);
    stat = SPI_SendRecvData(SPI_USE_ID, cmd, resp, rLen+4, SPI_TIMEOUT_DISABLE);
    spi_flash_pull_cs_high();
    if(stat != SUCCESS){
        return stat;
    }

    arch_memcpy(rBuff, resp+4, rLen);

    return SUCCESS;
}


/**
 * @brief spi flash select gpio
 *
 * @param  clk: clk gpio
 * @param  cs: cs gpio
 * @param  mosi: mosi gpio
 * @param  miso: miso gpio
 * @return None
 */
void spi_flash_set_gpio(uint8_t clk, uint8_t cs, uint8_t mosi, uint8_t miso)
{
    spi_flash_cs_gpio = cs;
    spi_flash_clk_gpio = clk;
    spi_flash_mosi_gpio = mosi;
    spi_flash_miso_gpio = miso;
}

/**
 * @brief spi flash init
 *
 * @return BL_Err_Type
 */
BL_Err_Type spi_flash_init(void)
{
    SPI_CFG_Type spiCfg = {
        DISABLE,                         /* Disable de-glitch function */
        SPI_SLAVE_PIN_4,                 /* SPI 4-pin mode(CS is enabled) */
        ENABLE,                          /* Disable master continuous transfer mode */
        SPI_BYTE_INVERSE_BYTE0_FIRST,    /* The byte 0 is sent first in SPI transfer */
        SPI_BIT_INVERSE_MSB_FIRST,       /* MSB is sent first in SPI transfer */
        SPI_CLK_PHASE_INVERSE_0,         /* SPI clock phase */
        SPI_CLK_POLARITY_LOW,            /* SPI clock plarity */
        SPI_FRAME_SIZE_32                /* SPI frame size 8-bit(also the valid width for each fifo entry) */
    };

    SPI_ClockCfg_Type clockCfg = {
        1,                               /* Length of start condition */
        1,                               /* Length of stop condition */
        1,                               /* Length of data phase 0,affecting clock */
        1,                               /* Length of data phase 1,affecting clock */
        1                                /* Length of interval between frame */
    };

    /* gpio and pad init */
    spi_flash_gpio_init();

    /* GLB SPI clock config */
    GLB_Set_DSP_SPI_CLK(ENABLE, GLB_DSP_SPI_CLK_DSP_MUXPLL_160M, 0);

    /* SPI interrupt config */
    SPI_Int_Callback_Install(SPI_USE_ID, SPI_INT_END, SPI_Int_Callback);
    SPI_IntMask(SPI_USE_ID, SPI_INT_ALL, MASK);
    SPI_IntMask(SPI_USE_ID, SPI_INT_END, UNMASK);
    CPU_Interrupt_Enable(SPI_USE_IRQ);
    System_NVIC_SetPriority(SPI_USE_IRQ, 4, 1);

    /* SPI config */
    SPI_Init(SPI_USE_ID, &spiCfg);

    /* Set SPI clock */
    SPI_ClockConfig(SPI_USE_ID, &clockCfg);

    /* Enable spi master mode */
    SPI_Enable(SPI_USE_ID, SPI_WORK_MODE_MASTER);

    return SUCCESS;
}

/**
 * @brief spi flash read jedec id
 *
 * @param jedecid
 * @return BL_Err_Type
 */
BL_Err_Type spi_flash_read_jedec_id(uint8_t *data)
{
    uint32_t wdata[1] = {0x9f};
    uint32_t rdata[1] = {0};
    BL_Err_Type stat = SUCCESS;

    SPI_SetFrameSize(SPI_USE_ID, SPI_FRAME_SIZE_32);
    spi_flash_pull_cs_low();
    stat = SPI_SendRecvData(SPI_USE_ID, wdata, rdata, 1, SPI_TIMEOUT_ENABLE);
    if(stat != SUCCESS) {
        return stat;
    }
    spi_flash_pull_cs_high();
    if((0xFF==((uint8_t *)rdata)[1]) && (0xFF==((uint8_t *)rdata)[2]) && (0xFF==((uint8_t *)rdata)[3])) {
        return ERROR;
    }

    rdata[0] = (rdata[0]>>8);
    arch_memcpy((uint8_t *)data, (uint8_t *)&rdata[0], 3);

    return stat;
}

/**
 * @brief spi flash read data
 *
 * @param addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
BL_Err_Type spi_flash_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    BL_Err_Type stat = SUCCESS;
    uint32_t i;
    uint32_t curLen;

    for (i = 0; i < len;) {
        curLen = len - i;
        if (curLen >= 256) {
            curLen = 256;
        }

        stat = spi_flash_page_read(addr, data, curLen);
        if (stat != SUCCESS) {
            return stat;
        }
        spi_flash_wait_notbusy();

        /* Adjust address and programmed length */
        addr += curLen;
        i += curLen;
        data += curLen;
    }

    return SUCCESS;
}

/**
 * @brief spi flash write data
 *
 * @param addr
 * @param data
 * @param len
 * @return BL_Err_Type
 */
BL_Err_Type spi_flash_write(uint32_t addr, uint8_t *data, uint32_t len)
{
    BL_Err_Type stat = SUCCESS;
    uint32_t i;
    uint32_t curLen;

    for (i = 0; i < len;) {
        /* Get current programmed length within page size */
        curLen = 256 - addr % 256;

        if (curLen > len - i) {
            curLen = len - i;
        }

        stat = spi_flash_page_write(addr, data, curLen);
        if (stat != SUCCESS) {
            return stat;
        }
        spi_flash_wait_notbusy();

        /* Adjust address and programmed length */
        addr += curLen;
        i += curLen;
        data += curLen;
    }

    return SUCCESS;
}

/**
 * @brief spi flash erase
 *
 * @param startaddr
 * @param erase len
 * @return BL_Err_Type
 */
BL_Err_Type spi_flash_erase(uint32_t startaddr, uint32_t len)
{
    uint32_t eraseLen = 0;
    uint32_t endaddr = startaddr + len - 1;
    BL_Err_Type stat = SUCCESS;

    if (startaddr > endaddr) {
        return ERROR;
    }

    while (startaddr <= endaddr) {
        len = endaddr - startaddr + 1;

        if ((startaddr & (SPI_FLASH_BLK64K_SIZE - 1)) == 0 &&
            len > (SPI_FLASH_BLK64K_SIZE - 4 * 1024)) {
            /* 64K margin address,and length > 64K-sector size, erase one first */
            stat = spi_flash_blk64_erase(startaddr / SPI_FLASH_BLK64K_SIZE);
            eraseLen = SPI_FLASH_BLK64K_SIZE;
        } else if ((startaddr & (SPI_FLASH_BLK32K_SIZE - 1)) == 0 &&
                   len > (SPI_FLASH_BLK32K_SIZE - 4 * 1024)) {
            /* 32K margin address,and length > 32K-sector size, erase one first */
            stat = spi_flash_blk32_erase(startaddr / SPI_FLASH_BLK32K_SIZE);
            eraseLen = SPI_FLASH_BLK32K_SIZE;
        } else {
            /* Sector erase */
            startaddr = ((startaddr) & (~(4 - 1)));
            stat = spi_flash_sector_erase(startaddr / 4 / 1024);
            eraseLen = 4 * 1024;
        }

        startaddr += eraseLen;

        if (stat != SUCCESS) {
            return ERROR;
        }
    }

    return SUCCESS;
}
