/**
    *****************************************************************************
    * @file     cmem7_spi.c
    *
    * @brief    CMEM7 SPI source file
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

#include "cmem7_spi.h"

void SPI_Init(SPI0_Type* SPIx, SPI_InitTypeDef *init) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(init);
    assert_param(IS_SPI_MODE(init->SPI_Mode));
    assert_param(init->SPI_BitLength != 0);

    if (init->SPI_Mode == SPI_MODE_CPOL_0_CPHA_0) {
        SPIx->CTRL_b.CLK_HIGH = FALSE;
        SPIx->CTRL_b.NEG_EDGE = TRUE;
  } else if (init->SPI_Mode == SPI_MODE_CPOL_0_CPHA_1) {
        SPIx->CTRL_b.CLK_HIGH = FALSE;
        SPIx->CTRL_b.NEG_EDGE = FALSE;
  } else if (init->SPI_Mode == SPI_MODE_CPOL_1_CPHA_0) {
        SPIx->CTRL_b.CLK_HIGH = TRUE;
        SPIx->CTRL_b.NEG_EDGE = FALSE;
  } else {
        SPIx->CTRL_b.CLK_HIGH = TRUE;
        SPIx->CTRL_b.NEG_EDGE = TRUE;
  }

    SPIx->CTRL_b.RX_EN = init->SPI_RxEn;
    SPIx->BCNT_b.CNT = init->SPI_BitLength - 1;
    SPIx->DIV = init->SPI_ClockDividor;
    SPIx->GAP = (init->SPI_Gap == 0) ? 0 : init->SPI_Gap / 2 + 1;
}

void SPI_Enable(SPI0_Type* SPIx, BOOL enable) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

  SPIx->CTRL_b.EN = enable;
}

void SPI_EnableInt(SPI0_Type* SPIx, uint32_t Int, BOOL enable) {
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_INT(Int));

  if (enable) {
      SPIx->INT_MASK &= ~Int;
    } else {
        SPIx->INT_MASK |= Int;
    }

    SPIx->INT_MASK &= SPI_INT_ALL;
}

BOOL SPI_GetIntStatus(SPI0_Type* SPIx, uint32_t Int) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_INT(Int));

    if (0 != (SPIx->INT_STATUS & Int)) {
        return TRUE;
    }

    return FALSE;
}
void SPI_ClearInt(SPI0_Type* SPIx, uint32_t Int) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_INT(Int));

    SPIx->INT_STATUS = Int;
}

uint8_t SPI_ReadFifo(SPI0_Type* SPIx, uint8_t size, uint32_t* data) {
    uint8_t count;

    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(data);

    if (!SPIx->CTRL_b.EN) {
        return 0;
    }

    count = 0;
    while (!SPIx->STATUS_b.RFIFO_EMPTY && count < size) {
      uint32_t d = SPIx->RW_DATA;
      d <<= (32 - SPIx->BCNT_b.CNT - 1);
      d >>= (32 - SPIx->BCNT_b.CNT - 1);
        *(data + count++) = d;
    }

    return count;
}

uint8_t SPI_WriteFifo(SPI0_Type* SPIx, uint8_t Size, uint32_t* data) {
    uint8_t count;

    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(data);

    if (!SPIx->CTRL_b.EN) {
        return 0;
    }

    count = 0;
    while (!SPIx->STATUS_b.TFIFO_FULL && count < Size) {
      uint32_t d = *(data + count++);
        d <<= (32 - SPIx->BCNT_b.CNT - 1);
        SPIx->RW_DATA = d;
    }

    return count;
}

BOOL SPI_Transcation(SPI0_Type* SPIx, uint8_t size) {
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(size);

    if (!SPIx->CTRL_b.EN) {
        return FALSE;
    }

    SPIx->TRANS_CNT = size - 1;
    SPIx->TRANS_START_b.TX_TRIGGER = TRUE;

    return TRUE;
}

