/**
    *****************************************************************************
    * @file     cmem7_i2c.c
    *
    * @brief    CMEM7 I2C source file
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

#include "cmem7_i2c.h"

#define I2C_INNER_INT_ALL               0x3FF

typedef struct {
    union {
    uint32_t  DATA_CMD;

    struct {
      uint32_t  DATA       :  8;
      uint32_t  RD_CMD     :  1;
      uint32_t  WR_CMD     :  1;
      uint32_t  WR_RD_CMD  :  1;
    } DATA_CMD_b;
  } INNER;
} I2C_INNER_DATA_CMD;

static uint32_t i2c_GetClock(I2C0_Type* I2Cx) {
    uint32_t dividor;
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    if ((uint32_t)I2Cx == (uint32_t)I2C0) {
        dividor = GLOBAL_CTRL->CLK_SEL_0_b.I2C0_CLK;
    } else if ((uint32_t)I2Cx == (uint32_t)I2C1) {
        dividor = GLOBAL_CTRL->CLK_SEL_0_b.I2C1_CLK;
    }

    return SYSTEM_CLOCK_FREQ / (1 << (dividor + 1));
}

static uint16_t i2c_NormalizeAddr(I2C0_Type* I2Cx, uint16_t addr) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    if (I2Cx->CTRL_b.MODE == I2C_Mode_Master) {
        if (I2Cx->CTRL_b.MASTER_ADDR_WIDTH == I2C_ADDR_WIDTH_7BIT) {
            addr &= 0x007F;
        } else {
            addr &= 0x3FF;
        }
    }

    if (I2Cx->CTRL_b.MODE == I2C_Mode_Slave) {
        if (I2Cx->CTRL_b.SLAVE_ADDR_WIDTH == I2C_ADDR_WIDTH_7BIT) {
            addr &= 0x007F;
        } else {
            addr &= 0x3FF;
        }
    }

    return addr;
}

static void i2c_ReadClear(uint32_t bit) {
    uint32_t tmp;
    tmp = bit;
    tmp = tmp;
}

void I2C_Init(I2C0_Type* I2Cx, I2C_InitTypeDef* I2C_Init) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(I2C_Init);
    assert_param(IS_I2C_MODE(I2C_Init->I2C_Mode));
    assert_param(IS_I2C_ADDR_WIDTH(I2C_Init->I2C_AddressWidth));

    // reset
    I2Cx->ENABLE_b.RESET = FALSE;
    I2Cx->ENABLE_b.RESET = TRUE;

    // clear interrupt
    I2Cx->INT_MASK = I2C_INNER_INT_ALL;
    i2c_ReadClear(I2Cx->CLR_ALL_INT_b.CLEAR);

    I2Cx->CTRL_b.MODE = I2C_Init->I2C_Mode;
    if (I2Cx->CTRL_b.MODE == I2C_Mode_Master) {
        I2Cx->CTRL_b.MASTER_ADDR_WIDTH = I2C_Init->I2C_AddressWidth;
        I2Cx->TAR_b.START_BYTE = TRUE;
        I2Cx->TAR_b.ADDR10 = i2c_NormalizeAddr(I2Cx, I2C_Init->I2C_Address);
    }
    if (I2Cx->CTRL_b.MODE == I2C_Mode_Slave) {
        I2Cx->CTRL_b.SLAVE_ADDR_WIDTH = I2C_Init->I2C_AddressWidth;
        I2Cx->SAR_b.ADDR10 = i2c_NormalizeAddr(I2Cx, I2C_Init->I2C_Address);
    }

    I2Cx->RX_TL_b.THRESHOLD = 0;
    I2Cx->TX_TL_b.THRESHOLD = 0;

    I2Cx->SLAVE_NACK_b.NACK = FALSE;

    if (I2C_Init->timing) {
        I2Cx->SCL_CNT_b.HIGH_LEVEL_TICK =
          i2c_GetClock(I2Cx) / I2C_Init->timing->I2C_Freq / 2;
        I2Cx->SCL_CNT_b.LOW_LEVEL_TICK =
          i2c_GetClock(I2Cx) / I2C_Init->timing->I2C_Freq / 2;
        I2Cx->SDA_SETUP_b.TSU_DAT = ((uint64_t)I2C_Init->timing->I2C_TsuDat) *
          i2c_GetClock(I2Cx) / 1000000000;
        I2Cx->SDA_SETUP_b.TSETUP = ((uint64_t)I2C_Init->timing->I2C_Tsetup) *
          i2c_GetClock(I2Cx) / 1000000000;
        I2Cx->TSU_STA_SETUP_b.TBUF = ((uint64_t)I2C_Init->timing->I2C_Tbuf) *
          i2c_GetClock(I2Cx) / 1000000000;
        I2Cx->TSU_STA_SETUP_b.TSU_STA = ((uint64_t)I2C_Init->timing->I2C_TsuSta) *
          i2c_GetClock(I2Cx) / 1000000000;
        I2Cx->TSU_STA_SETUP_b.SDA_FILTER_EN = I2C_Init->timing->I2C_SdaFilterEn;
        I2Cx->TSU_STA_SETUP_b.SDA_FILTER_CNT = I2C_Init->timing->I2C_SdaFilterSpike;
        I2Cx->TSU_STA_SETUP_b.SCL_FILTER_EN = I2C_Init->timing->I2C_SclFilterEn;
        I2Cx->TSU_STA_SETUP_b.SCL_FILTER_CNT = I2C_Init->timing->I2C_SclFilterSpike;
  }
}

void I2C_Enable(I2C0_Type* I2Cx, BOOL enable) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    I2Cx->ENABLE_b.EN = enable;
}

void I2C_EnableInt(I2C0_Type* I2Cx, uint32_t Int, BOOL enable) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_INT(Int));

    if (enable) {
      I2Cx->INT_MASK &= ~Int;
    } else {
        I2Cx->INT_MASK |= Int;
    }
}

BOOL I2C_GetIntStatus(I2C0_Type* I2Cx, uint32_t Int) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_INT(Int));

    if (0 != (I2Cx->INT_STATUS & Int)) {
        return TRUE;
    }

    return FALSE;
}
void I2C_ClearInt(I2C0_Type* I2Cx, uint32_t Int) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_INT(Int));

    if (Int == I2C_INT_RX_FIFO_NOT_EMPTY) {
        // It can't be clear by sw but read data
    }

    if (Int == I2C_INT_RD_REQUEST) {
        i2c_ReadClear(I2Cx->CLR_RD_REQ_b.CLEAR);
    }

    if (Int == I2C_INT_TX_ABORT) {
        i2c_ReadClear(I2Cx->CLR_TX_ABRT_b.CLEAR);
    }

    if (Int == I2C_INT_RX_DONE) {
        i2c_ReadClear(I2Cx->CLR_RX_DONE_b.CLEAR);
    }

    if (Int == I2C_INT_TX_DONE) {
        i2c_ReadClear(I2Cx->CLR_TX_DONE_b.CLEAR);
    }
}

BOOL I2C_GetStatus(I2C0_Type* I2Cx, uint32_t Status) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_STATUS(Status));

    if (0 != (I2Cx->STATUS & Status)) {
        return TRUE;
    }

    return FALSE;
}

void I2C_ClearStatus(I2C0_Type* I2Cx, uint32_t Status) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_STATUS(Status));

    if (Status & I2C_STATUS_RX_FIFO_NOT_EMPTY) {
        // It can't be clear by sw but read
    }

    if (Status & I2C_STATUS_RD_REQUEST) {
        i2c_ReadClear(I2Cx->CLR_RD_REQ_b.CLEAR);
    }

    if (Status & I2C_STATUS_TX_ABORT) {
        i2c_ReadClear(I2Cx->CLR_TX_ABRT_b.CLEAR);
    }

    if (Status & I2C_STATUS_RX_DONE) {
        i2c_ReadClear(I2Cx->CLR_RX_DONE_b.CLEAR);
    }

    if (Status & I2C_STATUS_TX_DONE) {
        i2c_ReadClear(I2Cx->CLR_TX_DONE_b.CLEAR);
    }
}

BOOL I2C_MasterReadReq(I2C0_Type* I2Cx, uint8_t size) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    if (!I2Cx->ENABLE_b.EN || I2Cx->STATUS_b.BUSY) {
        return FALSE;
    }

    if (I2Cx->CTRL_b.MODE == I2C_Mode_Slave) {
      return FALSE;
    }

    if (size == 0) {
        return FALSE;
    }

    I2Cx->WRITE_READ_CNT_b.RD_BYTE_CNT = size;
    if (size != 0) {
    I2C_INNER_DATA_CMD inner;

    inner.INNER.DATA_CMD_b.DATA = 0;
        inner.INNER.DATA_CMD_b.RD_CMD = TRUE;
        inner.INNER.DATA_CMD_b.WR_CMD = FALSE;
        inner.INNER.DATA_CMD_b.WR_RD_CMD = FALSE;

        I2Cx->DATA_CMD = inner.INNER.DATA_CMD;
    }

    return TRUE;
}

uint8_t I2C_ReadFifo(I2C0_Type* I2Cx, uint8_t size, uint8_t* data) {
    uint8_t count;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(data);

    if (!I2Cx->ENABLE_b.EN) {
        return 0;
    }

    count = 0;
    while (I2Cx->STATUS_b.RX_FIFO_NOT_EMPTY && count < size) {
        *(data + count++) = I2Cx->DATA_CMD_b.DATA;
    }

    return count;
}

BOOL I2C_WriteReq(I2C0_Type* I2Cx, uint8_t size, uint8_t firstData) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    if (!I2Cx->ENABLE_b.EN || I2Cx->STATUS_b.BUSY) {
        return FALSE;
    }

    if (size == 0) {
        return FALSE;
    }

    I2Cx->WRITE_READ_CNT_b.WR_BYTE_CNT = size;
    if (size != 0) {
    I2C_INNER_DATA_CMD inner;

    inner.INNER.DATA_CMD_b.DATA = firstData ;
        inner.INNER.DATA_CMD_b.RD_CMD = FALSE;
        inner.INNER.DATA_CMD_b.WR_CMD =
          (I2Cx->CTRL_b.MODE == I2C_Mode_Slave) ? FALSE : TRUE;
        inner.INNER.DATA_CMD_b.WR_RD_CMD = FALSE;

        I2Cx->DATA_CMD = inner.INNER.DATA_CMD;
    }

    return TRUE;
}

uint8_t I2C_WriteFifo(I2C0_Type* I2Cx, uint8_t size, uint8_t* data) {
    uint8_t count;

    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(data);

    if (!I2Cx->ENABLE_b.EN) {
        return 0;
    }

    count = 0;
    while (I2Cx->STATUS_b.TX_FIFO_NOT_FULL && count < size) {
      I2Cx->DATA_CMD_b.DATA = *(data + count++);
    }

    return count;
}

BOOL I2C_StopReq(I2C0_Type* I2Cx) {
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    udelay(600);

    return TRUE;
}
