/**
  ******************************************************************************
  * @file    bl702_snflash.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
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

#include "bl702_snflash.h"
#include "bl702_psram.h"

#define PSRAM_ADDR            (0x24000000)
#define DISK_SECTOR_SIZE      (512)
#define PSRAM_READ_ERITE_SIZE (256)

static void Nandflash_Erase(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t blockNum);
static void Nandflash_PageReadToPsram(uint32_t addr, uint32_t len);
static void ATTR_TCM_SECTION Nandflash_Psram_Write(uint8_t *buff, uint32_t len, uint32_t psramWriteOffsite);
static void ATTR_TCM_SECTION Nandflash_Psram_Read(uint8_t *buff, uint32_t readLen, uint32_t psramReadOffsite);
static void Nandflash_PageWriteToPsram(const uint8_t *buff, uint32_t addr, uint32_t len);
static void Nandflash_PageProgramFromPsram(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t blockNum);

NANDFLASH_CFG_Type nfCfg = {
    .spiNo = SPI_ID_0,
    .spiCfg = {
        DISABLE,                      /* Disable de-glitch function */
        DISABLE,                      /* Disable master continuous transfer mode */
        SPI_BYTE_INVERSE_BYTE0_FIRST, /* The byte 0 is sent first in SPI transfer */
        SPI_BIT_INVERSE_MSB_FIRST,    /* MSB is sent first in SPI transfer */
        SPI_CLK_PHASE_INVERSE_0,      /* SPI clock phase */
        SPI_CLK_POLARITY_LOW,         /* SPI clock plarity */
        SPI_FRAME_SIZE_8              /* SPI frame size 8-bit(also the valid width for each fifo entry) */
    },
    .clockCfg = {
        1, /* Length of start condition */
        1, /* Length of stop condition */
        1, /* Length of data phase 0,affecting clock */
        1, /* Length of data phase 1,affecting clock */
        1  /* Length of interval between frame */
    }
};

static void ATTR_TCM_SECTION Nandflash_Psram_Write(uint8_t *buff, uint32_t len, uint32_t psramWriteOffsite)
{
    uint32_t i = 0;
    uint32_t psramStartAddr = PSRAM_ADDR + psramWriteOffsite;

    for (i = 0; i < len / PSRAM_READ_ERITE_SIZE; i++) {
        BL702_MemCpy_Fast((void *)(psramStartAddr + i * PSRAM_READ_ERITE_SIZE), buff, PSRAM_READ_ERITE_SIZE);
        buff += PSRAM_READ_ERITE_SIZE;
    }

    /*if len is not an integral multiple of PSRAM_READ_ERITE_SIZE need memcpy once again*/
    if (len % PSRAM_READ_ERITE_SIZE != 0) {
        BL702_MemCpy_Fast((void *)(psramStartAddr + i * PSRAM_READ_ERITE_SIZE), buff, len % PSRAM_READ_ERITE_SIZE);
        buff += (len % PSRAM_READ_ERITE_SIZE);
    }
}

static void ATTR_TCM_SECTION Nandflash_Psram_Read(uint8_t *buff, uint32_t readLen, uint32_t psramReadOffsite)
{
    uint32_t i = 0;
    uint32_t psramStartAddr = PSRAM_ADDR + psramReadOffsite;

    for (i = 0; i < readLen / PSRAM_READ_ERITE_SIZE; i++) {
        BL702_MemCpy_Fast(buff, (void *)(psramStartAddr + i * PSRAM_READ_ERITE_SIZE), PSRAM_READ_ERITE_SIZE);
        buff += PSRAM_READ_ERITE_SIZE;
    }

    /*if len is not an integral multiple of PSRAM_READ_ERITE_SIZE need memcpy once again*/
    if (readLen % PSRAM_READ_ERITE_SIZE != 0) {
        BL702_MemCpy_Fast(buff, (void *)(psramStartAddr + i * PSRAM_READ_ERITE_SIZE), readLen % PSRAM_READ_ERITE_SIZE);
    }
}

void ATTR_TCM_SECTION Nandflash_Psram_Cfg()
{
    GLB_GPIO_Cfg_Type gpioCfg = {
        .gpioPin = GLB_GPIO_PIN_17,
        .gpioFun = GPIO17_FUN_SF_IO_0_SF2_CS2,
        .gpioMode = GPIO_MODE_OUTPUT,
        .pullType = GPIO_PULL_UP,
        .drive = 3,
        .smtCtrl = 1,
    };

    SPI_Psram_Cfg_Type apMemory1604 = {
        .readIdCmd = 0x9F,
        .readIdDmyClk = 0,
        .burstToggleCmd = 0xC0,
        .resetEnableCmd = 0x66,
        .resetCmd = 0x99,
        .enterQuadModeCmd = 0x35,
        .exitQuadModeCmd = 0xF5,
        .readRegCmd = 0xB5,
        .readRegDmyClk = 1,
        .writeRegCmd = 0xB1,
        .readCmd = 0x03,
        .readDmyClk = 0,
        .fReadCmd = 0x0B,
        .fReadDmyClk = 1,
        .fReadQuadCmd = 0xEB,
        .fReadQuadDmyClk = 3,
        .writeCmd = 0x02,
        .quadWriteCmd = 0x38,
        .pageSize = 512,
        .ctrlMode = PSRAM_SPI_CTRL_MODE,
        .driveStrength = PSRAM_DRIVE_STRENGTH_50_OHMS,
        .burstLength = PSRAM_BURST_LENGTH_512_BYTES,
    };

    SF_Ctrl_Cmds_Cfg cmdsCfg = {
        .cmdsEn = ENABLE,
        .burstToggleEn = ENABLE,
        .wrapModeEn = DISABLE,
        .wrapLen = SF_CTRL_WRAP_LEN_512,
    };

    SF_Ctrl_Psram_Cfg sfCtrlPsramCfg = {
        .owner = SF_CTRL_OWNER_SAHB,
        .padSel = SF_CTRL_PAD_SEL_DUAL_CS_SF2,
        .bankSel = SF_CTRL_SEL_PSRAM,
        .psramRxClkInvertSrc = ENABLE,
        .psramRxClkInvertSel = ENABLE,
        .psramDelaySrc = ENABLE,
        .psramClkDelay = 0,
    };
    uint8_t psramId[8] = { 0 };
    uint32_t wt_en = 1;
    uint32_t wb_en = 0;
    uint32_t wa_en = 0;
    uint32_t i = 0;

    GLB_GPIO_Init(&gpioCfg);

    Psram_Init(&apMemory1604, &cmdsCfg, &sfCtrlPsramCfg);
    Psram_SoftwareReset(&apMemory1604, apMemory1604.ctrlMode);
    Psram_ReadId(&apMemory1604, psramId);

    Psram_Cache_Write_Set(&apMemory1604, SF_CTRL_QIO_MODE, wt_en, wb_en, wa_en);
    L1C_Cache_Enable_Set(0x0f);
}

void Nandflash_Gpio_Init(GLB_GPIO_Type clk, GLB_GPIO_Type mosi, GLB_GPIO_Type miso)
{
    GLB_GPIO_Cfg_Type gpioCfg = {
        .gpioPin = GLB_GPIO_PIN_0,
        .gpioFun = GPIO_FUN_SPI0,
        .gpioMode = GPIO_MODE_OUTPUT,
        .pullType = GPIO_PULL_NONE,
        .drive = 0,
        .smtCtrl = 1
    };

    /* cs */
    gpioCfg.gpioPin = SPI_PIN_CS;
    gpioCfg.gpioFun = 11;
    GLB_GPIO_Init(&gpioCfg);
    GLB_GPIO_INPUT_Disable(gpioCfg.gpioPin);
    GLB_GPIO_OUTPUT_Enable(gpioCfg.gpioPin);
    Nandflash_CS_High();

    /* clk */
    gpioCfg.gpioPin = clk;
    gpioCfg.gpioFun = GPIO_FUN_SPI0;
    GLB_GPIO_Init(&gpioCfg);
    GLB_GPIO_INPUT_Disable(gpioCfg.gpioPin);
    GLB_GPIO_OUTPUT_Enable(gpioCfg.gpioPin);

    /* mosi */
    gpioCfg.gpioPin = mosi;
    gpioCfg.gpioFun = GPIO_FUN_SPI0;
    GLB_GPIO_Init(&gpioCfg);
    GLB_GPIO_INPUT_Enable(gpioCfg.gpioPin);
    GLB_GPIO_OUTPUT_Enable(gpioCfg.gpioPin);

    /* miso */
    gpioCfg.gpioPin = miso;
    gpioCfg.gpioFun = GPIO_FUN_SPI0;
    GLB_GPIO_Init(&gpioCfg);
    GLB_GPIO_INPUT_Enable(gpioCfg.gpioPin);
    GLB_GPIO_OUTPUT_Enable(gpioCfg.gpioPin);

    GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);
}

void Nandflash_CS_High(void)
{
    GLB_GPIO_Write(SPI_PIN_CS, 1);
}

void Nandflash_CS_Low(void)
{
    GLB_GPIO_Write(SPI_PIN_CS, 0);
}

void Nandflash_Clock_Init(uint8_t enable, uint8_t div)
{
    GLB_Set_SPI_CLK(enable, div);
    GLB_AHB_Slave1_Clock_Gate(DISABLE, BL_AHB_SLAVE1_SPI);
}

void Nandflash_SPI_Init(NANDFLASH_CFG_Type *pNandflashCfg)
{
    SPI_Disable(SPI_ID_0, SPI_WORK_MODE_MASTER);
    SPI_IntMask(SPI_ID_0, SPI_INT_ALL, MASK);
    SPI_Init(pNandflashCfg->spiNo, &(pNandflashCfg->spiCfg));
    SPI_ClockConfig(pNandflashCfg->spiNo, &(pNandflashCfg->clockCfg));
    SPI_Enable(SPI_ID_0, SPI_WORK_MODE_MASTER);
}

void Nandflash_SendRecv(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *sendBuff, uint8_t *recvBuff, uint32_t len)
{
    SPI_SendRecv_8bits(pNandflashCfg->spiNo, sendBuff, recvBuff, len, SPI_TIMEOUT_DISABLE);
}

void Nandflash_WriteEnable(NANDFLASH_CFG_Type *pNandflashCfg)
{
    uint8_t cmd[1] = { 0 };
    uint8_t pBlockLock = 0xff;

    cmd[0] = NANDFLASH_WRITE_ENABLE;
    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 1, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    /*check block lock status*/
    Nandflash_Get_BlockLock(pNandflashCfg, &pBlockLock);

    if (pBlockLock != 0) {
        // MSG_ERR("Get BlockLock in Nandflash Write Enable and return %0x\r\n", pBlockLock);
    }
}

void Nandflash_WriteDisable(NANDFLASH_CFG_Type *pNandflashCfg)
{
    uint8_t cmd[1] = { 0 };

    cmd[0] = NANDFLASH_WRITE_DISABLE;
    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 1, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();
}

void Nandflash_Get_BlockLock(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pBlockLock)
{
    uint8_t cmd[2] = { 0 };
    uint8_t ack[1] = { 0 };

    cmd[0] = NANDFLASH_GET_FEATURES;
    cmd[1] = NANDFLASH_BLOCK_LOCK_ADDR;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 2, SPI_TIMEOUT_DISABLE);
    SPI_Recv_8bits(pNandflashCfg->spiNo, ack, 1, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    *pBlockLock = ack[0];
}

void Nandflash_Set_BlockLock(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pBlockLock)
{
    uint8_t cmd[3] = { 0 };

    cmd[0] = NANDFLASH_SET_FEATURES;
    cmd[1] = NANDFLASH_BLOCK_LOCK_ADDR;
    cmd[2] = *pBlockLock;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 3, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();
}

void Nandflash_Get_Feature(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pFeature)
{
    uint8_t cmd[2] = { 0 };
    uint8_t ack[1] = { 0 };

    cmd[0] = NANDFLASH_GET_FEATURES;
    cmd[1] = NANDFLASH_FEATURE_ADDR;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 2, SPI_TIMEOUT_DISABLE);
    SPI_Recv_8bits(pNandflashCfg->spiNo, ack, 1, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    *pFeature = ack[0];
}

void Nandflash_Set_Feature(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pFeature)
{
    uint8_t cmd[3] = { 0 };

    cmd[0] = NANDFLASH_GET_FEATURES;
    cmd[1] = NANDFLASH_FEATURE_ADDR;
    cmd[2] = *pFeature;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 3, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();
}

void Nandflash_Get_Status(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pStatus)
{
    uint8_t cmd[2] = { 0 };
    uint8_t ack[1] = { 0 };

    cmd[0] = NANDFLASH_GET_FEATURES;
    cmd[1] = NANDFLASH_STATUS_ADDR;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 2, SPI_TIMEOUT_DISABLE);
    SPI_Recv_8bits(pNandflashCfg->spiNo, ack, 1, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    *pStatus = ack[0];
}

void Nandflash_Set_Status(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pStatus)
{
    uint8_t cmd[3] = { 0 };

    cmd[0] = NANDFLASH_GET_FEATURES;
    cmd[1] = NANDFLASH_STATUS_ADDR;
    cmd[2] = *pStatus;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 3, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();
}

NANDFLASH_ECC_Type Nandflash_CheckBadBlock(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t blockNum, uint8_t *buff, uint32_t len)
{
    uint32_t pageNum = 0, pageAddr = 0;
    NANDFLASH_ECC_Type ecc = 0;

    pageNum = blockNum * NANDFLASH_PAGES_PER_BLOCK;

    pageAddr = pageNum * NANDFLASH_PAGE_SIZE;

    if (len) {
        //read to cache
        ecc = Nandflash_PageReadToCache(pNandflashCfg, pageAddr);

        /* read from cache */
        Nandflash_ReadFromCache(pNandflashCfg, NANDFLASH_PAGE_SIZE, buff, len);
    }

    return ecc;
}

NANDFLASH_ECC_Type Nandflash_PageRead(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr, uint8_t *buff, uint32_t len)
{
    NANDFLASH_ECC_Type ecc = 0;
    uint32_t pageAddr = addr & 0xFFFFF800;
    uint32_t readLen = 0;
    uint32_t pageOffset = addr - pageAddr;

    if ((pageOffset + len) <= NANDFLASH_PAGE_SIZE) {
        readLen = len;
    } else {
        readLen = NANDFLASH_PAGE_SIZE - pageOffset;
    }

    memset(buff, 0, len);

    if (readLen) {
        /* read to cache */
        ecc = Nandflash_PageReadToCache(pNandflashCfg, pageAddr);

        /* read from cache */
        Nandflash_ReadFromCache(pNandflashCfg, pageOffset, buff, readLen);
    }

    return ecc;
}

NANDFLASH_ECC_Type Nandflash_PagesRead(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr, uint8_t *buff, uint32_t len)
{
    NANDFLASH_ECC_Type ecc = 0;
    uint32_t startPageNum = 0, endPageNum = 0, absolutePageNum = 0;
    uint32_t readLen = 0, pageOffset = 0, beginAddr = addr;

    startPageNum = addr / NANDFLASH_PAGE_SIZE;
    endPageNum = (addr + len - 1) / NANDFLASH_PAGE_SIZE;

    memset(buff, 0, len);

    if (len > 0) {
        for (absolutePageNum = startPageNum; absolutePageNum <= endPageNum; absolutePageNum++) {
            pageOffset = addr % NANDFLASH_PAGE_SIZE;

            if (absolutePageNum == startPageNum) {
                if (beginAddr + len >= NANDFLASH_PAGE_SIZE) {
                    readLen = (startPageNum + 1) * NANDFLASH_PAGE_SIZE - beginAddr;
                } else {
                    readLen = len;
                }
            } else if ((startPageNum < absolutePageNum) && (absolutePageNum < endPageNum)) {
                readLen = NANDFLASH_PAGE_SIZE;
            } else if (absolutePageNum == endPageNum) {
                readLen = (beginAddr + len) - (endPageNum * NANDFLASH_PAGE_SIZE);
            }

            /* read to cache */
            ecc = Nandflash_PageReadToCache(pNandflashCfg, absolutePageNum * NANDFLASH_PAGE_SIZE);
            /* read from cache */
            Nandflash_ReadFromCache(pNandflashCfg, pageOffset, buff, readLen);

            addr = (absolutePageNum + 1) * NANDFLASH_PAGE_SIZE;
            buff += readLen;
        }
    }

    return ecc;
}
NANDFLASH_ECC_Type Nandflash_PageReadToCache(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr)
{
    uint8_t feature = 0;
    uint8_t cmd[4] = { 0 };
    uint8_t status = 0xff;
    uint8_t pBlockLock = 0xff;
    NANDFLASH_ECC_Type ecc = 0;
    uint32_t blockNum = 0;
    uint32_t pageNum = 0;
    uint32_t absolutePageNum = 0;
    uint16_t cmds = 0;
    /* enable ECC */
    Nandflash_Get_Feature(pNandflashCfg, &feature);
    ((NANDFLASH_FEATURE_Type *)(&feature))->ECC_EN = 1;
    Nandflash_Set_Feature(pNandflashCfg, &feature);

    absolutePageNum = addr / NANDFLASH_PAGE_SIZE;
    blockNum = absolutePageNum / NANDFLASH_PAGES_PER_BLOCK;
    pageNum = absolutePageNum % NANDFLASH_PAGES_PER_BLOCK;
    /* page read to cache */
    cmd[0] = NANDFLASH_PAGE_READ_TO_CACHE;
    cmd[1] = NANDFLASH_DUMMY_BYTE;
    cmds = (uint16_t)(blockNum << 6) | (uint16_t)pageNum;
    cmd[2] = (uint8_t)(cmds >> 8);
    cmd[3] = (uint8_t)(cmds >> 0);
    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 4, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    /*check block lock status*/
    Nandflash_Get_BlockLock(pNandflashCfg, &pBlockLock);

    if (pBlockLock != 0) {
        // MSG_ERR("Get BlockLock in Nandflash PageRead To Cache and return %0x\r\n", pBlockLock);
    }

    BL702_Delay_MS(20);

    /* Operation In Progress */
    do {
        Nandflash_Get_Status(pNandflashCfg, &status);
    } while ((((NANDFLASH_STATUS_Type *)(&status))->OIP));

    /* get ecc */
    Nandflash_Get_Status(pNandflashCfg, &status);
    ecc = status;

    return ecc;
}

void Nandflash_ReadFromCache(NANDFLASH_CFG_Type *pNandflashCfg, uint16_t offset, uint8_t *buff, uint32_t len)
{
    uint32_t readLen = len;
    uint8_t cmd[4] = { 0 };
    uint8_t pBlockLock = 0xff;

    if (!buff) {
        return;
    }

    if (readLen > NANDFLASH_PAGE_SIZE) {
        readLen = NANDFLASH_PAGE_SIZE;
    }

    /* read from cache */
    cmd[0] = NANDFLASH_READ_FROM_CACHE;
    cmd[1] = (uint8_t)((offset >> 8) & 0x0F);
    cmd[2] = (uint8_t)((offset >> 0) & 0xFF);
    cmd[3] = NANDFLASH_DUMMY_BYTE;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 4, SPI_TIMEOUT_DISABLE);
    SPI_Recv_8bits(pNandflashCfg->spiNo, buff, readLen, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    /*check block lock status*/
    Nandflash_Get_BlockLock(pNandflashCfg, &pBlockLock);

    if (pBlockLock != 0) {
        // MSG_ERR("Get BlockLock in Nandflash Read From Cache Erase and return %0x\r\n", pBlockLock);
    }
}

void Nandflash_ReadID(NANDFLASH_CFG_Type *pNandflashCfg, uint8_t *pManufactureID, uint8_t *pDeviceID)
{
    uint8_t cmd[2] = { 0 };
    uint8_t ack[2] = { 0 };

    cmd[0] = NANDFLASH_READ_ID;
    cmd[1] = NANDFLASH_DUMMY_BYTE;

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 2, SPI_TIMEOUT_DISABLE);
    SPI_Recv_8bits(pNandflashCfg->spiNo, ack, 2, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    *pManufactureID = ack[0];
    *pDeviceID = ack[1];
}

void Nandflash_PageProgram(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr, const uint8_t *buff, uint32_t len)
{
    uint32_t pageAddr = addr & 0xFFFFF800;
    uint32_t writeLen = 0;
    uint32_t pageOffset = addr - pageAddr;

    if ((pageOffset + len) <= NANDFLASH_PAGE_SIZE) {
        writeLen = len;
    } else {
        writeLen = NANDFLASH_PAGE_SIZE - pageOffset;
    }

    if (writeLen) {
        /* program load */
        Nandflash_ProgramLoad(pNandflashCfg, pageOffset, buff, writeLen);

        /* write enable */
        Nandflash_WriteEnable(pNandflashCfg);

        /* program execute */
        Nandflash_ProgramExecute(pNandflashCfg, pageAddr);
    }

    return;
}

void Nandflash_PagesProgram(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr, const uint8_t *buff, uint32_t len)
{
    int32_t startPageNum = 0, endPageNum = 0, absolutePageNum = 0;
    uint32_t writeLen = 0, pageAddr = 0;
    uint32_t pageOffset = 0, begin_addr = addr;

    startPageNum = addr / NANDFLASH_PAGE_SIZE;
    endPageNum = (addr + len - 1) / NANDFLASH_PAGE_SIZE;

    if (len > 0) {
        for (absolutePageNum = startPageNum; absolutePageNum <= endPageNum; absolutePageNum++) {
            pageOffset = 0;
            pageAddr = absolutePageNum * NANDFLASH_PAGE_SIZE;

            if (absolutePageNum == startPageNum) {
                if (begin_addr + len >= NANDFLASH_PAGE_SIZE) {
                    writeLen = (startPageNum + 1) * NANDFLASH_PAGE_SIZE - begin_addr;
                } else {
                    writeLen = len;
                }

                pageOffset = begin_addr % NANDFLASH_PAGE_SIZE;
            } else if ((startPageNum < absolutePageNum) && (absolutePageNum < endPageNum)) {
                writeLen = NANDFLASH_PAGE_SIZE;
                pageOffset = 0;
            } else if (absolutePageNum == endPageNum) {
                writeLen = (begin_addr + len) - (endPageNum * NANDFLASH_PAGE_SIZE);
                pageOffset = 0;
            }

            if (writeLen) {
                /* program load */
                Nandflash_ProgramLoad(pNandflashCfg, pageOffset, buff, writeLen);

                /* write enable */
                Nandflash_WriteEnable(pNandflashCfg);

                /* program execute */
                Nandflash_ProgramExecute(pNandflashCfg, pageAddr);
            }

            buff += writeLen;
        }
    }
}

void Nandflash_ProgramLoad(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t pageOffset, const uint8_t *buff, uint32_t len)
{
    uint8_t cmd[3] = { 0 };
    uint32_t writeLen = len;
    uint8_t pBlockLock = 0xff;

    if (!buff) {
        return;
    }

    if (len > NANDFLASH_PAGE_SIZE) {
        writeLen = NANDFLASH_PAGE_SIZE;
    } else {
    }

    cmd[0] = NANDFLASH_PROGRAM_LOAD;
    cmd[1] = (uint8_t)((pageOffset >> 8) & 0x0F);
    cmd[2] = (uint8_t)((pageOffset >> 0) & 0xFF);

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 3, SPI_TIMEOUT_DISABLE);
    SPI_Send_8bits(pNandflashCfg->spiNo, (uint8_t *)buff, writeLen, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    /*check block lock status*/
    Nandflash_Get_BlockLock(pNandflashCfg, &pBlockLock);

    if (pBlockLock != 0) {
        // MSG_ERR("Get BlockLock in Nandflash Program Load and return %0x\r\n", pBlockLock);
    }
}

void Nandflash_ProgramExecute(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr)
{
    uint8_t feature = 0;
    uint8_t cmd[4] = { 0 };
    uint8_t status = 0xff;
    uint8_t pBlockLock = 0xff;
    uint32_t absolutePageNum = 0;
    uint16_t cmds = 0;
    uint32_t blockNum = 0;
    uint32_t pageNum = 0;
    absolutePageNum = addr / NANDFLASH_PAGE_SIZE;
    blockNum = absolutePageNum / NANDFLASH_PAGES_PER_BLOCK;
    pageNum = absolutePageNum % NANDFLASH_PAGES_PER_BLOCK;

    /* enable ECC */
    Nandflash_Get_Feature(pNandflashCfg, &feature);
    ((NANDFLASH_FEATURE_Type *)(&feature))->ECC_EN = 1;
    Nandflash_Set_Feature(pNandflashCfg, &feature);

    /* program execute */
    cmd[0] = NANDFLASH_PROGRAM_EXECUTE;
    cmd[1] = NANDFLASH_DUMMY_BYTE;
    cmds = (uint16_t)(blockNum << 6) | (uint16_t)pageNum;
    cmd[2] = (uint8_t)(cmds >> 8);
    cmd[3] = (uint8_t)(cmds >> 0);

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 4, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    /*check block lock status*/
    Nandflash_Get_BlockLock(pNandflashCfg, &pBlockLock);

    if (pBlockLock != 0) {
        // MSG_ERR("Get BlockLock in Nandflash Program Execute and return %0x\r\n", pBlockLock);
    }

    /* Operation In Progress */
    do {
        Nandflash_Get_Status(pNandflashCfg, &status);
    } while ((((NANDFLASH_STATUS_Type *)(&status))->OIP));
}

void Nandflash_InternalDataMove(NANDFLASH_CFG_Type *pNandflashCfg)
{
}

void Nandflash_ProgramLoadRandomData(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr, uint8_t *buff, uint32_t len)
{
}

static void Nandflash_Erase(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t blockNum)
{
    uint8_t cmd[4] = { 0 };
    uint16_t cmds = 0;
    uint8_t pBlockLock = 0xff;

    /* block erase */
    cmd[0] = NANDFLASH_BLOCK_ERASE;
    cmd[1] = NANDFLASH_DUMMY_BYTE;
    cmds = (uint16_t)(blockNum << 6);
    cmd[2] = (uint8_t)(cmds >> 8);
    cmd[3] = (uint8_t)(cmds >> 0);

    Nandflash_CS_High();
    Nandflash_CS_Low();
    SPI_Send_8bits(pNandflashCfg->spiNo, cmd, 4, SPI_TIMEOUT_DISABLE);
    Nandflash_CS_High();

    /*check block lock status*/
    Nandflash_Get_BlockLock(pNandflashCfg, &pBlockLock);

    if (pBlockLock != 0) {
        // MSG_ERR("Get BlockLock in Nandflash Erase and return %0x\r\n", pBlockLock);
    }
}

void Nandflash_BlockErase(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t addr)
{
    uint8_t status = 0xff;
    uint32_t blockNum = 0;
    blockNum = addr / NANDFLASH_BLOCK_SIZE;

    Nandflash_WriteEnable(pNandflashCfg);
    Nandflash_Erase(pNandflashCfg, blockNum);

    /* Operation In Progress */
    do {
        Nandflash_Get_Status(pNandflashCfg, &status);
    } while ((((NANDFLASH_STATUS_Type *)(&status))->OIP));
}

void Nandflash_Reset(NANDFLASH_CFG_Type *pNandflashCfg)
{
}

void Nandflash_WriteUnprotect(NANDFLASH_CFG_Type *pNandflashCfg)
{
}

NANDFLASH_ECC_Type Nandflash_Check_ECC_Status(NANDFLASH_CFG_Type *pNandflashCfg)
{
    return NO_BIT_ERROR;
}

int Nandflash_Disk_Status(void)
{
    return 0;
}

int Nandflash_Disk_Initialize(void)
{
    return 0;
}

int Nandflash_Disk_Read(BYTE *buff, LBA_t sector, UINT count)
{
    //512 bytes in a sector
    uint32_t startAddr = sector * DISK_SECTOR_SIZE;
    uint32_t len = count * DISK_SECTOR_SIZE;
    NANDFLASH_ECC_Type ecc = 0;

    if (len > 0) {
        ecc = Nandflash_PagesRead(&nfCfg, startAddr, buff, len);
    }

    return 0;
}

void Nandflash_PageReadToPsram(uint32_t addr, uint32_t len)
{
    uint32_t startPageNum = 0, endPageNum = 0, absolutePageNum = 0;
    uint32_t beginAddr = addr, psramWriteOffsite = 0;
    uint8_t readBuff[NANDFLASH_PAGE_SIZE];

    startPageNum = addr / NANDFLASH_PAGE_SIZE;
    endPageNum = (addr + len - 1) / NANDFLASH_PAGE_SIZE;

    if (len > 0) {
        for (absolutePageNum = startPageNum; absolutePageNum <= endPageNum; absolutePageNum++) {
            memset(readBuff, 0, sizeof(readBuff));

            Nandflash_PageRead(&nfCfg, beginAddr, readBuff, NANDFLASH_PAGE_SIZE);
            Nandflash_Psram_Write(readBuff, NANDFLASH_PAGE_SIZE, psramWriteOffsite);

            beginAddr = (absolutePageNum + 1) * NANDFLASH_PAGE_SIZE;
            psramWriteOffsite += NANDFLASH_PAGE_SIZE;
        }
    }
}

static void Nandflash_PageWriteToPsram(const uint8_t *buff, uint32_t psramWriteOffsite, uint32_t len)
{
    if (len > 0) {
        return Nandflash_Psram_Write((uint8_t *)buff, len, psramWriteOffsite);
    }
}

static void Nandflash_PageProgramFromPsram(NANDFLASH_CFG_Type *pNandflashCfg, uint32_t blockNum)
{
    uint8_t psramReadBuf[NANDFLASH_PAGE_SIZE];
    uint32_t startPageNum = 0, endPageNum = 0, absolutePageNum = 0;
    uint32_t psramReadOffsite = 0;

    startPageNum = blockNum * NANDFLASH_PAGES_PER_BLOCK;
    endPageNum = (blockNum + 1) * NANDFLASH_PAGES_PER_BLOCK - 1;

    for (absolutePageNum = startPageNum; absolutePageNum <= endPageNum; absolutePageNum++) {
        memset(psramReadBuf, 0, NANDFLASH_PAGE_SIZE);
        Nandflash_Psram_Read(psramReadBuf, NANDFLASH_PAGE_SIZE, psramReadOffsite);
        Nandflash_PageProgram(pNandflashCfg, absolutePageNum * NANDFLASH_PAGE_SIZE, psramReadBuf, NANDFLASH_PAGE_SIZE);
        psramReadOffsite += NANDFLASH_PAGE_SIZE;
    }
}

int Nandflash_Disk_Write(const BYTE *buff, LBA_t sector, UINT count)
{
    uint32_t addr = sector * DISK_SECTOR_SIZE;
    uint32_t len = count * DISK_SECTOR_SIZE;
    uint32_t startBlockNum = 0, endBlockNum = 0, absoluteBlockNum = 0;
    uint32_t writeLen = 0, beginAddr = addr;

    startBlockNum = addr / NANDFLASH_BLOCK_SIZE;
    endBlockNum = (addr + len - 1) / NANDFLASH_BLOCK_SIZE;

    if (len > 0) {
        Nandflash_Psram_Cfg();

        for (absoluteBlockNum = startBlockNum; absoluteBlockNum <= endBlockNum; absoluteBlockNum++) {
            if (absoluteBlockNum == startBlockNum) {
                if (addr + len >= NANDFLASH_BLOCK_SIZE) {
                    writeLen = (absoluteBlockNum + 1) * NANDFLASH_BLOCK_SIZE - addr;
                } else {
                    writeLen = len;
                }
            } else if ((startBlockNum < absoluteBlockNum) && (absoluteBlockNum < endBlockNum)) {
                writeLen = NANDFLASH_BLOCK_SIZE;
            } else if (absoluteBlockNum == endBlockNum) {
                writeLen = (addr + len) - (endBlockNum * NANDFLASH_BLOCK_SIZE);
            }

            /*read data from block to psram*/
            Nandflash_PageReadToPsram(absoluteBlockNum * NANDFLASH_BLOCK_SIZE, NANDFLASH_BLOCK_SIZE);
            /*update program data to psram*/
            Nandflash_PageWriteToPsram(buff, beginAddr % NANDFLASH_BLOCK_SIZE, writeLen);
            /*erase block*/
            Nandflash_BlockErase(&nfCfg, absoluteBlockNum * NANDFLASH_BLOCK_SIZE);
            /*program data from psram to block*/
            Nandflash_PageProgramFromPsram(&nfCfg, absoluteBlockNum);

            buff += writeLen;
            beginAddr = (absoluteBlockNum + 1) * NANDFLASH_BLOCK_SIZE;
        }
    }

    return 0;
}

int Nandflash_Disk_Ioctl(BYTE cmd, void *buff)
{
    return 0;
}

void Nandflash_Init()
{
    Nandflash_Gpio_Init(SPI_PIN_CLK, SPI_PIN_MISO, SPI_PIN_MOSI);
    Nandflash_Clock_Init(ENABLE, 0x1F);
    Nandflash_SPI_Init(&nfCfg);
}
