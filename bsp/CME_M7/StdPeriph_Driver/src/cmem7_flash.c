/**
    *****************************************************************************
    * @file     cmem7_flash.c
    *
    * @brief    CMEM7 flash controller source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_flash.h"

typedef struct {
  union {
    uint16_t  STATUS;                         /*!< status register                     */

    struct {
      uint16_t  WIP:  1;                      /*!< in writting                         */
      uint16_t  WEL:  1;                      /*!< write enable                        */
      uint16_t  BP:  5;                       /*!< protection region                   */
      uint16_t  SRP:  2;                      /*!< protection mode                     */
      uint16_t  QE:  1;                       /*!< Quad mode                           */
    } STATUS_b;                               /*!< BitSize                             */
  } INNER;
} FLASH_INNER_STATUS;


#define NS_IN_A_SECOND                            (1000000000)

#define FLASH_MAX_SIZE                            0x800000
#define FLASH_PAGE_SIZE                           0x100
#define FLASH_SECTOR_SIZE                         0x001000
#define FLASH_BLOCK_32K_SIZE                      0x008000
#define FLASH_BLOCK_64K_SIZE                      0x010000

#define FLASH_CMD_RD_INNER_STATUS_LOW             0x05
#define FLASH_CMD_RD_INNER_STATUS_HIGH            0x35

#define FLASH_CMD_WR_WRITE_ENABLE                 0x06
#define FLASH_CMD_WR_WRITE_DISABLE                0x04

#define FLASH_CME_WR_STATUS_REG                   0x01

#define FLASH_CME_ERASE_SECTOR                    0x20
#define FLASH_CME_ERASE_BLOCK_32K                 0x52
#define FLASH_CME_ERASE_BLOCK_64K                 0xD8
#define FLASH_CME_ERASE_CHIP                      0xC7

#define FLASH_CME_WR_ENTER_DEEP_PD                0xB9
#define FLASH_CME_WR_EXIT_DEEP_PD                 0xAB

#define FLASH_CME_RD_NORMAL                       0x03
#define FLASH_CME_RD_FAST                         0x0B
#define FLASH_CME_RD_FAST_DUAL                    0x3B
#define FLASH_CME_RD_FAST_QUAD                    0x6B

#define FLASH_CME_WR                              0x02

typedef void (*WAIT)(void);
static WAIT wait;

static void flash_setClock(uint8_t dividor) {
    dividor = (dividor < 2) ? 2 : dividor;
    NOR_FLASH->CTRL0_b.DIV = dividor / 2 - 1;
}

static void flash_cleanOperation() {
    NOR_FLASH->TRIGGER_b.OP_CLEAN = TRUE;
    while (NOR_FLASH->STATUS_b.BUSY);

    NOR_FLASH->TRIGGER_b.OP_CLEAN = FALSE;
    while (NOR_FLASH->STATUS_b.BUSY);
}

static uint8_t flash_ReadInnerStatusLow() {
    NOR_FLASH->CTRL0_b.RW_BYTE_CNT = 1;
    NOR_FLASH->CTRL1_b.CMD = FLASH_CMD_RD_INNER_STATUS_LOW;
    NOR_FLASH->TRIGGER_b.OP_START = TRUE;

    while (NOR_FLASH->STATUS_b.BUSY);

    return (uint8_t)NOR_FLASH->DATA;
}

static uint8_t flash_ReadInnerStatusHigh() {
  NOR_FLASH->CTRL0_b.RW_BYTE_CNT = 1;
    NOR_FLASH->CTRL1_b.CMD = FLASH_CMD_RD_INNER_STATUS_HIGH;
    NOR_FLASH->TRIGGER_b.OP_START = TRUE;

    while (NOR_FLASH->STATUS_b.BUSY);

    return (uint8_t)NOR_FLASH->DATA;
}

//static void flash_WaitInWritting() {
void flash_WaitInWritting(void) {
    FLASH_INNER_STATUS s;

    while (NOR_FLASH->STATUS_b.BUSY);

    do {
        s.INNER.STATUS = flash_ReadInnerStatusLow();
        if (!s.INNER.STATUS_b.WIP) {
            break;
        }

        if (wait) {
            (*wait)();
        }
    } while (1);
}

static void flash_WriteWriteEnable(BOOL enable) {
  NOR_FLASH->CTRL0_b.RW_BYTE_CNT = 0;
    NOR_FLASH->CTRL1_b.CMD =
      enable ? FLASH_CMD_WR_WRITE_ENABLE : FLASH_CMD_WR_WRITE_DISABLE;

    NOR_FLASH->TRIGGER_b.OP_START = TRUE;

    flash_WaitInWritting();
}

static void flash_WriteStatusReg(FLASH_INNER_STATUS *s) {
  uint16_t tmp = s->INNER.STATUS;

    NOR_FLASH->CTRL0_b.RW_BYTE_CNT = 2;
    NOR_FLASH->CTRL1_b.CMD = FLASH_CME_WR_STATUS_REG;
    NOR_FLASH->DATA = ((tmp << 8) | (tmp >> 8)) << 16;
    NOR_FLASH->TRIGGER_b.OP_START = TRUE;

    flash_WaitInWritting();
}

static void flash_Erase(uint8_t cmd, uint32_t addr) {
    NOR_FLASH->CTRL0_b.RW_BYTE_CNT = 0;
    NOR_FLASH->CTRL1_b.CMD = cmd;
    NOR_FLASH->CTRL1_b.ADDRESS = addr;
    NOR_FLASH->TRIGGER_b.OP_START = TRUE;

    flash_WaitInWritting();
}

static void flash_WriteDeepPowerDownEnable(BOOL enable) {
  NOR_FLASH->CTRL0_b.RW_BYTE_CNT = 0;
    NOR_FLASH->CTRL1_b.CMD =
      enable ? FLASH_CME_WR_ENTER_DEEP_PD : FLASH_CME_WR_EXIT_DEEP_PD;

    NOR_FLASH->TRIGGER_b.OP_START = TRUE;

    flash_WaitInWritting();
}

static void flash_RwReq(uint8_t cmd, uint32_t addr, uint16_t size) {
    NOR_FLASH->CTRL0_b.RW_BYTE_CNT = size;
    NOR_FLASH->CTRL1_b.CMD = cmd;
    NOR_FLASH->CTRL1_b.ADDRESS = addr;

    NOR_FLASH->TRIGGER_b.OP_START = TRUE;
}

//static void flash_WaitReadFifoNotEmpty() {
void flash_WaitReadFifoNotEmpty(void) {
    while (NOR_FLASH->STATUS_b.RD_FIFO_EMPTY) {
        if (wait) {
            (*wait)();
        }
    }
}

//static uint16_t flash_ReadFifo(uint16_t size, uint8_t* data) {
uint16_t flash_ReadFifo(uint16_t size, uint8_t* data) {
    uint16_t count = 0;

    while (!NOR_FLASH->STATUS_b.RD_FIFO_EMPTY && size != 0) {
    uint32_t d =    NOR_FLASH->DATA;
        if (size > 3) {
            *(data + count++) = d >> 24;
            *(data + count++) = (d & 0x00FF0000) >> 16;
            *(data + count++) = (d & 0x0000FF00) >> 8;
            *(data + count++) = (d & 0x000000FF);
            size -= 4;
        } else if (size == 3) {
            *(data + count++) = (d & 0x00FF0000) >> 16;
            *(data + count++) = (d & 0x0000FF00) >> 8;
            *(data + count++) = (d & 0x000000FF);
            size -= 3;
        } else if (size == 2) {
            *(data + count++) = (d & 0x0000FF00) >> 8;
            *(data + count++) = (d & 0x000000FF);
            size -= 2;
        } else if (size == 1) {
            *(data + count++) = (d & 0x000000FF);
            size -= 1;
        }
    }

    return count;
}

static uint16_t flash_WriteFifo(uint16_t size, uint8_t* data) {
    uint16_t count = 0;

    while (!NOR_FLASH->STATUS_b.WR_FIFO_FULL && size != 0) {
        uint32_t d = 0;

        if (size > 3) {
            d = *(data + count++) << 24;
            d |= *(data + count++) << 16;
            d |= *(data + count++) << 8;
            d |= *(data + count++);
            size -= 4;
        } else if (size == 3) {
            d = *(data + count++) << 24;
            d |= *(data + count++) << 16;
            d |= *(data + count++) << 8;
            size -= 3;
        } else if (size == 2) {
            d = *(data + count++) << 24;
            d |= *(data + count++) << 16;
            size -= 2;
        } else if (size == 1) {
            d = *(data + count++) << 24;
            size -= 1;
        }

        NOR_FLASH->DATA = d;
    }

    return count;
}

static uint16_t flash_WritePage(uint32_t addr, uint16_t size, uint8_t* data) {
    uint16_t actualSize, retSize;

    flash_WriteWriteEnable(TRUE);

    actualSize = FLASH_PAGE_SIZE - (addr & (FLASH_PAGE_SIZE - 1));
    actualSize = (size > actualSize) ? actualSize : size;
  retSize = actualSize;

    flash_RwReq(FLASH_CME_WR, addr, actualSize);

    while (actualSize != 0) {
        uint8_t count = flash_WriteFifo(actualSize, data);

        actualSize -= count;
        data += count;
    }

    flash_WaitInWritting();

    return retSize;
}

void FLASH_Init(FLASH_InitTypeDef* init) {
    FLASH_INNER_STATUS s;

    assert_param(init);
    assert_param(IS_FLASH_PROTECT_MODE(init->FLASH_ProtectMode));
    assert_param(IS_FLASH_PROTECT_REGION(init->FLASH_ProtectRegion));

    wait = init->FLASH_Wait;
    flash_setClock(init->FLASH_ClockDividor);

    flash_cleanOperation();

    flash_WaitInWritting();

    s.INNER.STATUS = flash_ReadInnerStatusLow();
    s.INNER.STATUS |= ((uint16_t)flash_ReadInnerStatusHigh()) << 8;
    s.INNER.STATUS_b.BP = init->FLASH_ProtectRegion;
    s.INNER.STATUS_b.SRP = init->FLASH_ProtectMode;
    s.INNER.STATUS_b.QE = init->FLASH_QuadEnable;

    flash_WriteWriteEnable(TRUE);
    flash_WriteStatusReg(&s);
}

void FLASH_GetStatus(uint8_t* ProtectMode, uint8_t* ProtectRegion, BOOL* QuadEnable) {
    FLASH_INNER_STATUS s;

    assert_param(ProtectMode);
    assert_param(ProtectRegion);
    assert_param(QuadEnable);

    flash_WaitInWritting();

    s.INNER.STATUS = flash_ReadInnerStatusLow();
    s.INNER.STATUS |= ((uint16_t)flash_ReadInnerStatusHigh()) << 8;
    *ProtectRegion = s.INNER.STATUS_b.BP;
    *ProtectMode = s.INNER.STATUS_b.SRP;
    *QuadEnable = (s.INNER.STATUS_b.QE == 1) ?  TRUE : FALSE;
}

void FLASH_EraseSector(uint32_t addr) {
    flash_WaitInWritting();
    flash_WriteWriteEnable(TRUE);

    addr = (addr << 8) >> 8;
    addr = addr / FLASH_SECTOR_SIZE * FLASH_SECTOR_SIZE;
    flash_Erase(FLASH_CME_ERASE_SECTOR, addr);
}

void FLASH_Erase32kBlock(uint32_t addr) {
    flash_WaitInWritting();
    flash_WriteWriteEnable(TRUE);

    addr = (addr << 8) >> 8;
    addr = addr / FLASH_BLOCK_32K_SIZE * FLASH_BLOCK_32K_SIZE;
    flash_Erase(FLASH_CME_ERASE_BLOCK_32K, addr);
}

void FLASH_Erase64kBlock(uint32_t addr) {
    flash_WaitInWritting();
    flash_WriteWriteEnable(TRUE);

    addr = (addr << 8) >> 8;
    addr = addr / FLASH_BLOCK_64K_SIZE * FLASH_BLOCK_64K_SIZE;
    flash_Erase(FLASH_CME_ERASE_BLOCK_64K, addr);
}

void FLASH_EraseChip(void) {
    flash_WaitInWritting();
    flash_WriteWriteEnable(TRUE);
    flash_Erase(FLASH_CME_ERASE_CHIP, 0x0);
}

void FLASH_EnableDeepPowerDown(BOOL enable) {
    flash_WaitInWritting();
    flash_WriteWriteEnable(TRUE);
    flash_WriteDeepPowerDownEnable(enable);
}

void FLASH_Read(uint8_t ReadMode, uint32_t addr, uint16_t size, uint8_t* data) {
    uint8_t cmd;

    assert_param(IS_FLASH_READ_MODE(ReadMode));
    assert_param(addr + size <= FLASH_MAX_SIZE);
    assert_param(data);

    if (size == 0) {
        return ;
    }

    flash_WaitInWritting();

    if (ReadMode == FLASH_READ_MODE_NORMAL) {
        cmd = FLASH_CME_RD_NORMAL;
    } else if (ReadMode == FLASH_READ_MODE_FAST) {
        cmd = FLASH_CME_RD_FAST;
    } else if (ReadMode == FLASH_READ_MODE_FAST_DUAL) {
        cmd = FLASH_CME_RD_FAST_DUAL;
    } else {
        cmd = FLASH_CME_RD_FAST_QUAD;
    }

    flash_RwReq(cmd, addr, size);

  while (size > 0) {
        uint16_t count = 0;

    flash_WaitReadFifoNotEmpty();

      count = flash_ReadFifo(size, data);
        size -= count;
        data += count;
    }
}

void FLASH_Write(uint32_t addr, uint16_t size, uint8_t* data) {
    assert_param(addr + size <= FLASH_MAX_SIZE);
    assert_param(data);

    flash_WaitInWritting();

    while (size > 0) {
      uint16_t count = flash_WritePage(addr, size, data);

        addr += count;
        size -= count;
        data += count;
    }
}

