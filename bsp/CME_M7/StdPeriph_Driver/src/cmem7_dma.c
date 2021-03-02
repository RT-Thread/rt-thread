/**
    *****************************************************************************
    * @file     cmem7_dma.c
    *
    * @brief    CMEM7 DMA source file
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

#include "cmem7_dma.h"

typedef struct {
    union {
    uint32_t  CTL_LOW;

    struct {
      uint32_t  INT_EN     :  1;
      uint32_t  DST_TR_WIDTH:  3;
      uint32_t  SRC_TR_WIDTH:  3;
      uint32_t  DINC       :  2;
      uint32_t  SINC       :  2;
      uint32_t  DEST_MSIZE :  3;
      uint32_t  SRC_MSIZE  :  3;
      uint32_t  SRC_GATHER_EN:  1;
      uint32_t  DST_SCATTER_EN:  1;
      uint32_t             :  1;
      uint32_t  TT_FC      :  3;
      uint32_t  DMS        :  2;
      uint32_t  SMS        :  2;
      uint32_t  LLP_DST_EN :  1;
      uint32_t  LLP_SRC_EN :  1;
    } CTL_LOW_b;
  } INNER;
} INNER_CTL_LOW;

typedef struct {
  union {
    uint32_t  CTL_HI;

    struct {
      uint32_t  BLOCK_TS   : 12;
      uint32_t  DONE       :  1;
    } CTL_HI_b;
  } INNER;
} INNER_CTL_HIGH;

typedef struct {
    uint32_t srcAddr;
    uint32_t dstAddr;
    uint32_t nextBlock;
    INNER_CTL_LOW low;
    INNER_CTL_HIGH high;
} INNER_BLOCK_DESC;


#define DMA_MAX_CHANNEL_NUM                  8

#define DMA_TR_WIDTH_8_BIT                   0
#define DMA_TR_WIDTH_16_BIT                  1
#define DMA_TR_WIDTH_32_BIT                  2
#define DMA_TR_WIDTH_64_BIT                  3
#define DMA_TR_WIDTH_128_BIT                 4
#define DMA_TR_WIDTH_256_BIT                 5

#define DMA_INC_INCREMENT                    0
#define DMA_INC_DECREMENT                    1
#define DMA_INC_NO_CHANGE                    2

#define DMA_LOCK_DMA_TRANSFER                0
#define DMA_LOCK_DMA_BLOCK_TRANSFER          1
#define DMA_LOCK_DMA_BLOCK_TRANSACTION       2


void DMA_Init() {
    DMA->DMA_EN_b.EN = TRUE;

    // only open channel 0
    DMA->CH_EN = (0xFF << DMA_MAX_CHANNEL_NUM) | 0x0;

    DMA_ClearInt(DMA_Int_All);
    DMA_EnableInt(DMA_Int_All, FALSE);

    DMA->SAR0 = 0x0;
    DMA->DAR0 = 0x0;

    DMA->CTL_HI0_b.BLOCK_TS             = 0;
    DMA->CTL_LOW0_b.INT_EN              = FALSE;
    DMA->CTL_LOW0_b.DST_TR_WIDTH    = DMA_TR_WIDTH_32_BIT;
    DMA->CTL_LOW0_b.SRC_TR_WIDTH    = DMA_TR_WIDTH_32_BIT;
    DMA->CTL_LOW0_b.DINC                    = DMA_INC_INCREMENT;
    DMA->CTL_LOW0_b.SINC                    = DMA_INC_INCREMENT;
    DMA->CTL_LOW0_b.DEST_MSIZE      = 0;
    DMA->CTL_LOW0_b.SRC_MSIZE       = 0;
    DMA->CTL_LOW0_b.SRC_GATHER_EN = FALSE;
    DMA->CTL_LOW0_b.DST_SCATTER_EN = FALSE;
    DMA->CTL_LOW0_b.TT_FC               = 0;
  DMA->CTL_LOW0_b.DMS                   = 0;
    DMA->CTL_LOW0_b.SMS                 = 0;
    DMA->CTL_LOW0_b.LLP_DST_EN      = FALSE;
    DMA->CTL_LOW0_b.LLP_SRC_EN      = FALSE;

  DMA->LLP0_b.LOC = 0;
    DMA->LLP0_b.LMS = 0;

  DMA->SGR0_b.SGC = 0x1;
    DMA->SGR0_b.SGI = 0x0;

    DMA->DSR0_b.DSC = 0x0;
    DMA->DSR0_b.DSI = 0x0;

  DMA->SSTATAR0 = 0x0;
    DMA->DSTATAR0 = 0x0;

    DMA->CFG_HI0                                = 0x0;
    DMA->CFG_LOW0_b.CH_PRIOR        = 0;
    DMA->CFG_LOW0_b.CH_SUSP         = 0;
    DMA->CFG_LOW0_b.HS_SEL_DST  = 0;
    DMA->CFG_LOW0_b.LOCK_B_L        = 0;
  DMA->CFG_LOW0_b.HS_SEL_SRC    = 0;
    DMA->CFG_LOW0_b.LOCK_CH_L   = DMA_LOCK_DMA_TRANSFER;
  DMA->CFG_LOW0_b.LOCK_B_L      = DMA_LOCK_DMA_TRANSFER;
    DMA->CFG_LOW0_b.LOCK_CH         = TRUE;
    DMA->CFG_LOW0_b.LOCK_B          = TRUE;
    DMA->CFG_LOW0_b.DST_HS_POL  = 0;
    DMA->CFG_LOW0_b.SRC_HS_POL  = 0;
    DMA->CFG_LOW0_b.RELOAD_SRC  = FALSE;
    DMA->CFG_LOW0_b.RELOAD_DST  = FALSE;
}

void DMA_EnableInt(uint32_t Int, BOOL enable) {
    assert_param(IS_DMA_INT(Int));

  if (enable) {
        if (Int & DMA_Int_TfrComplete) {
            DMA->INT_EN_TFR = (0x1 << DMA_MAX_CHANNEL_NUM) | 0x1;
        }

        if (Int & DMA_Int_Err) {
            DMA->INT_EN_ERR = (0x1 << DMA_MAX_CHANNEL_NUM) | 0x1;
        }
    } else {
        if (Int & DMA_Int_TfrComplete) {
            DMA->INT_EN_TFR = (0x1 << DMA_MAX_CHANNEL_NUM) | 0x0;
        }

        if (Int & DMA_Int_Err) {
            DMA->INT_EN_ERR = (0x1 << DMA_MAX_CHANNEL_NUM) | 0x0;
        }
    }
}

BOOL DMA_GetIntStatus(uint32_t Int) {
    assert_param(IS_DMA_INT(Int));

    if (Int & DMA_Int_TfrComplete) {
        if (DMA->INT_TFR) {
            return TRUE;
        }
    }

    if (Int & DMA_Int_Err) {
        if (DMA->INT_ERR) {
            return TRUE;
        }
    }

    return FALSE;
}

void DMA_ClearInt(uint32_t Int) {
    assert_param(IS_DMA_INT(Int));

    if (Int & DMA_Int_TfrComplete) {
        DMA->INT_CLEAR_TFR = 0x1;
    }

    if (Int & DMA_Int_Err) {
        DMA->INT_CLEAR_ERR = 0x1;
    }
}

BOOL DMA_IsBusy() {
    return (DMA->CH_EN_b.EN) ? TRUE : FALSE;
}

BOOL DMA_Transfer(BLOCK_DESC *blockList) {
    BLOCK_DESC *p;
    if (!blockList) {
        return FALSE;
    }

    if (DMA_IsBusy()) {
        return FALSE;
    }

    p = blockList;
    while (p) {
        BOOL llp = FALSE;
        INNER_BLOCK_DESC *inner = (INNER_BLOCK_DESC *)p;
        if (p->nextBlock) {
            llp = TRUE;
        }

        inner->high.INNER.CTL_HI = 0;
        inner->high.INNER.CTL_HI_b.BLOCK_TS = (p->number >> DMA_TR_WIDTH_32_BIT);
        inner->high.INNER.CTL_HI_b.DONE = 0;

        inner->nextBlock = p->nextBlock;

        inner->low.INNER.CTL_LOW = 0;
        inner->low.INNER.CTL_LOW_b.INT_EN = TRUE;
        inner->low.INNER.CTL_LOW_b.DST_TR_WIDTH     = DMA_TR_WIDTH_32_BIT;
      inner->low.INNER.CTL_LOW_b.SRC_TR_WIDTH   = DMA_TR_WIDTH_32_BIT;
      inner->low.INNER.CTL_LOW_b.DINC                   = DMA_INC_INCREMENT;
      inner->low.INNER.CTL_LOW_b.SINC                   = DMA_INC_INCREMENT;
      inner->low.INNER.CTL_LOW_b.DEST_MSIZE         = 0;
      inner->low.INNER.CTL_LOW_b.SRC_MSIZE        = 0;
      inner->low.INNER.CTL_LOW_b.SRC_GATHER_EN  = FALSE;
      inner->low.INNER.CTL_LOW_b.DST_SCATTER_EN = FALSE;
      inner->low.INNER.CTL_LOW_b.TT_FC                  = 0;
    inner->low.INNER.CTL_LOW_b.DMS                  = 0;
      inner->low.INNER.CTL_LOW_b.SMS                    = 0;
      inner->low.INNER.CTL_LOW_b.LLP_DST_EN     = llp;
      inner->low.INNER.CTL_LOW_b.LLP_SRC_EN     = llp;

        if ((uint32_t)inner == (uint32_t)blockList) {
            // copy to DMA
            DMA->SAR0 = llp ? 0x0 : inner->srcAddr ;
            DMA->DAR0 = llp ? 0x0 : inner->dstAddr ;

            DMA->CTL_HI0 = llp ? 0x0 : inner->high.INNER.CTL_HI;
            DMA->CTL_LOW0 = inner->low.INNER.CTL_LOW;

            DMA->LLP0 = llp ? (uint32_t)inner : 0x0;
        }

        p = (BLOCK_DESC *)inner->nextBlock;
    }

    // open channel 0
    DMA->CH_EN = (0x1 << DMA_MAX_CHANNEL_NUM) | 0x1;

    return TRUE;
}

