/**
    *****************************************************************************
    * @file     cmem7_efuse.c
    *
    * @brief    CMEM7 EFUSE source file
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

#include "cmem7_efuse.h"

static void efuse_SetClock(uint8_t dividor) {
    if (dividor <= 2) {
        GLOBAL_CTRL->CLK_SEL_1_b.EFUSE_CLK = 0;
    } else if (dividor <= 4) {
        GLOBAL_CTRL->CLK_SEL_1_b.EFUSE_CLK = 1;
    } else if (dividor <= 8) {
        GLOBAL_CTRL->CLK_SEL_1_b.EFUSE_CLK = 2;
    } else {
        GLOBAL_CTRL->CLK_SEL_1_b.EFUSE_CLK = 3;
    }
}

static uint32_t efuse_GetClock() {
    return SYSTEM_CLOCK_FREQ / (1 << (GLOBAL_CTRL->CLK_SEL_1_b.EFUSE_CLK + 1));
}

// static uint8_t efuse_Crc8Bit(uint8_t data, uint8_t crc) {
//  uint8_t newCrc;
//  uint8_t d[8], c[8], i;
//
//  for (i = 0; i < 8; i++) {
//      d[i] = (data >> i) & 0x01;
//      c[i] = (crc >> i) & 0x01;
//  }
//
//  newCrc = d[7] ^ d[6] ^ d[0] ^ c[0] ^ c[6] ^ c[7];
//  newCrc |= (d[6] ^ d[1] ^ d[0] ^ c[0] ^ c[1] ^ c[6]) << 1;
//  newCrc |= (d[6] ^ d[2] ^ d[1] ^ d[0] ^ c[0] ^ c[1] ^ c[2] ^ c[6]) << 2;
//  newCrc |= (d[7] ^ d[3] ^ d[2] ^ d[1] ^ c[1] ^ c[2] ^ c[3] ^ c[7]) << 3;
//  newCrc |= (d[4] ^ d[3] ^ d[2] ^ c[2] ^ c[3] ^ c[4]) << 4;
//  newCrc |= (d[5] ^ d[4] ^ d[3] ^ c[3] ^ c[4] ^ c[5]) << 5;
//  newCrc |= (d[6] ^ d[5] ^ d[4] ^ c[4] ^ c[5] ^ c[6]) << 6;
//  newCrc |= (d[7] ^ d[6] ^ d[5] ^ c[5] ^ c[6] ^ c[7]) << 1;
//
//  return newCrc;
// }

// static uint8_t efuse_Crc(EFUSE_AesKey* key, uint8_t lock, BOOL isLowRegion) {
//  uint8_t crc = 0;
//
//  if (isLowRegion) {
//      crc = efuse_Crc8Bit(key->key0, crc);
//      crc = efuse_Crc8Bit(key->key0 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key0 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key0 >> 24, crc);
//      crc = efuse_Crc8Bit(key->key1, crc);
//      crc = efuse_Crc8Bit(key->key1 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key1 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key1 >> 24, crc);
//      crc = efuse_Crc8Bit(key->key2, crc);
//      crc = efuse_Crc8Bit(key->key2 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key2 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key2 >> 24, crc);
//      crc = efuse_Crc8Bit(key->key3, crc);
//      crc = efuse_Crc8Bit(key->key3 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key3 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key3 >> 24, crc);
//      crc = efuse_Crc8Bit(lock, crc);
//      crc = efuse_Crc8Bit(0x0, crc);
//      crc = efuse_Crc8Bit(0x0, crc);
//  } else {
//      crc = efuse_Crc8Bit(key->key4, crc);
//      crc = efuse_Crc8Bit(key->key4 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key4 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key4 >> 24, crc);
//      crc = efuse_Crc8Bit(key->key5, crc);
//      crc = efuse_Crc8Bit(key->key5 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key5 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key5 >> 24, crc);
//      crc = efuse_Crc8Bit(key->key6, crc);
//      crc = efuse_Crc8Bit(key->key6 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key6 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key6 >> 24, crc);
//      crc = efuse_Crc8Bit(key->key7, crc);
//      crc = efuse_Crc8Bit(key->key7 >> 8, crc);
//      crc = efuse_Crc8Bit(key->key7 >> 16, crc);
//      crc = efuse_Crc8Bit(key->key7 >> 24, crc);
//      crc = efuse_Crc8Bit(lock, crc);
//      crc = efuse_Crc8Bit(0x0, crc);
//      crc = efuse_Crc8Bit(0x0, crc);
//  }
//
//  return crc;
// }

void EFUSE_Init(EFUSE_InitTypeDef* init) {
    assert_param(init);
    assert_param(IS_EFUSE_TMRF(init->EFUSE_TMRF));

    efuse_SetClock(init->EFUSE_ClockDividor);
    EFUSE->USER_CTRL_LOW_b.TMRF = init->EFUSE_TMRF;
    EFUSE->USER_CTRL_HI_b.TMRF = init->EFUSE_TMRF;
    if (init->timing) {
        uint32_t value;

        value = (init->timing->EFUSE_Tpwph * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TPWPH = value >> 2;
        EFUSE->TIMING_1_b.TPWPH = value & 0x00000003;

        value = (init->timing->EFUSE_Trac * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TRAC = value;

        value = (init->timing->EFUSE_Trah * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TRAH = value;

        value = (init->timing->EFUSE_Trpw * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TRPW = value;

        value = (init->timing->EFUSE_Trc * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TRC = value;

        value = (init->timing->EFUSE_Tesr * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TESR = value;

        value = (init->timing->EFUSE_Tprs * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_0_b.TPRS = value;

        value = (init->timing->EFUSE_Tpi * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_1_b.TPIT = value;

        value = (init->timing->EFUSE_Tpp * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_1_b.TPP = value;

        value = (init->timing->EFUSE_Teps * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_1_b.TEPS = value;

        value = (init->timing->EFUSE_Teps * (efuse_GetClock() / 1000000) / 1000);
        value = (value == 0) ? 1 : value;
        EFUSE->TIMING_1_b.TPWPS = value;
    }
}

/* It only can be written once */
// BOOL EFUSE_Write(EFUSE_AesKey* key) {
//   assert_param(key);
//
//  if ((EFUSE->USER_CTRL_LOW_b.LOCK || EFUSE->USER_CTRL_LOW_b.BUSY) ||
//      (EFUSE->USER_CTRL_HI_b.LOCK || EFUSE->USER_CTRL_HI_b.BUSY)) {
//      return FALSE;
//  }
//
//  // write low region
//  EFUSE->USER_DATA0_LOW = key->key0;
//  EFUSE->USER_DATA1_LOW = key->key1;
//  EFUSE->USER_DATA2_LOW = key->key2;
//  EFUSE->USER_DATA3_LOW = key->key3;
//  EFUSE->USER_DATA4_LOW_b.CRC = efuse_Crc(key, 0x1, TRUE);
//  EFUSE->USER_DATA4_LOW_b.LOCK = 1;
//  EFUSE->USER_CTRL_LOW_b.WR_EN = FALSE;
//  EFUSE->USER_CTRL_LOW_b.WR_EN = TRUE;
//
//  udelay(1000);
//  while (EFUSE->USER_CTRL_LOW_b.BUSY) ;
//
//  if (EFUSE->USER_CTRL_LOW_b.WR_CRC_ERR) {
//      return FALSE;
//  }
//
//  // write high region
//  EFUSE->USER_DATA0_HI = key->key4;
//  EFUSE->USER_DATA1_HI = key->key5;
//  EFUSE->USER_DATA2_HI = key->key6;
//  EFUSE->USER_DATA3_HI = key->key7;
//  EFUSE->USER_DATA4_HI_b.CRC = efuse_Crc(key, 0x1, FALSE);
//  EFUSE->USER_DATA4_HI_b.LOCK = 1;
//  EFUSE->USER_CTRL_HI_b.WR_EN = FALSE;
//  EFUSE->USER_CTRL_HI_b.WR_EN = TRUE;
//
//  udelay(1000);
//  while (EFUSE->USER_CTRL_HI_b.BUSY) ;
//
//  if (EFUSE->USER_CTRL_HI_b.WR_CRC_ERR) {
//      return FALSE;
//  }
//  return TRUE;
// }

BOOL EFUSE_Compare(EFUSE_AesKey* key) {
  assert_param(key);

    if (EFUSE->USER_CTRL_LOW_b.BUSY || EFUSE->USER_CTRL_HI_b.BUSY) {
        return FALSE;
    }

    // compare low region
    EFUSE->USER_DATA0_LOW = key->key0;
    EFUSE->USER_DATA1_LOW = key->key1;
    EFUSE->USER_DATA2_LOW = key->key2;
    EFUSE->USER_DATA3_LOW = key->key3;
    EFUSE->USER_CTRL_LOW_b.RD_EN = FALSE;
    EFUSE->USER_CTRL_LOW_b.RD_EN = TRUE;

    udelay(2);
    while (EFUSE->USER_CTRL_LOW_b.BUSY) ;

    if (EFUSE->USER_CTRL_LOW_b.COMPARE_FAIL) {
        return FALSE;
    }

    // compare high region
    EFUSE->USER_DATA0_HI = key->key4;
    EFUSE->USER_DATA1_HI = key->key5;
    EFUSE->USER_DATA2_HI = key->key6;
    EFUSE->USER_DATA3_HI = key->key7;
    EFUSE->USER_CTRL_HI_b.RD_EN = FALSE;
    EFUSE->USER_CTRL_HI_b.RD_EN = TRUE;

    udelay(2);
    while (EFUSE->USER_CTRL_HI_b.BUSY) ;

    if (EFUSE->USER_CTRL_HI_b.COMPARE_FAIL) {
        return FALSE;
    }

    return TRUE;
}

