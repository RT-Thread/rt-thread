/**
    *****************************************************************************
    * @file     cmem7_can.c
    *
    * @brief    CMEM7 CAN source file
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

#include "cmem7_can.h"

typedef struct {
  union {
    __IO uint8_t   FI;                        /*!< Transmit Frame Information if writting or Receive Frame Information
                                                   if reading, ACR[0] if reset mode                                      */

    struct {
      __IO uint8_t   DLC        :  4;         /*!< byte number in the data                                               */
           uint8_t              :  2;
      __IO uint8_t   RTR        :  1;         /*!< 1 indicates a remote frame; 0 indicates a data frame                  */
      __IO uint8_t   FF         :  1;         /*!< 1 selects Extended Frame Format (EFF); 0 selects Standard Frame
                                                   Format (SFF)                                                          */
    } FI_b;                                   /*!< BitSize                                                               */
  } U;
} CAN_FRAME_INFO;

typedef struct {
    union {
    uint16_t  ID;                             /*!< ID                                  */

    struct {
      uint16_t  ID28_21   :  8;               /*!< ID28 to ID21                        */
      uint16_t            :  4;
      uint16_t  RTR       :  1;               /*!< if remote frame                     */
      uint16_t  ID20_18   :  3;               /*!< ID20 to ID18                        */
    } ID_b;                                   /*!< BitSize                             */
  } U;
} CAN_STANDARD_ID;

typedef struct {
  union {
    uint32_t  ID;                             /*!< ID                                  */

    struct {
      uint32_t  ID28_21   :  8;               /*!< ID28 to ID21                        */
      uint32_t  ID20_13   :  8;               /*!< ID20 to ID13                        */
            uint32_t  ID12_5    :  8;               /*!< ID12 to ID5                         */
            uint32_t            :  2;
      uint32_t  RTR       :  1;               /*!< if remote frame                     */
      uint32_t  ID4_0     :  5;               /*!< ID4 to ID0                          */
    } ID_b;                                   /*!< BitSize                             */
  } U;
} CAN_EXTENDED_ID;

#define CAN_MODE_NORMAL            0x00000000
#define CAN_MODE_RESET             0x00000001
#define CAN_MODE_LISTEN_ONLY       0x00000002
#define CAN_MODE_SELF_TEST         0x00000004
#define CAN_MODE_SINGLE_FILTER     0x00000008
#define CAN_MODE_SLEEP             0x00000010

#define CAN_OCR_NORMAL             0x02
#define CAN_OCR_CLOCK              0x03

static BOOL can_SetFilter(CAN0_Type* CANx, CAN_FILTER *f1, CAN_FILTER *f2) {
    if (!f1) {
        return FALSE;
    }

    if (!IS_CAN_FLT_TYPE(f1->type)) {
        return FALSE;
    }

    if(IS_CAN_FLT_DUAL(f1->type)) {
        if (!f2 || IS_CAN_FLT_SINGLE(f2->type)) {
            return FALSE;
        }
    }

    if (f1->type == CAN_FLT_STANDARD_SINGLE) {
      CANx->FI_OR_ACR0 = f1->ACCEPT.sf.ID28_18 >> 3;
        CANx->DI0_OR_ACR1 = (f1->ACCEPT.sf.ID28_18 & 0x07) << 5;
        CANx->DI0_OR_ACR1 |= f1->ACCEPT.sf.RTR << 4;
        CANx->DI1_OR_ACR2 = f1->ACCEPT.sf.data1;
        CANx->DI2_OR_ACR3 = f1->ACCEPT.sf.data2;

        CANx->DI3_OR_AMR0 = f1->MASK.sf.ID28_18 >> 3;
        CANx->DI4_OR_AMR1 = (f1->MASK.sf.ID28_18 & 0x07) << 5;
        CANx->DI4_OR_AMR1 |= f1->MASK.sf.RTR << 4;
        CANx->DI5_OR_AMR2 = f1->MASK.sf.data1;
        CANx->DI6_OR_AMR3 = f1->MASK.sf.data2;
    } else if (f1->type == CAN_FLT_STANDARD_DUAL) {
      CANx->FI_OR_ACR0 = f1->ACCEPT.sf.ID28_18 >> 3;
        CANx->DI0_OR_ACR1 = (f1->ACCEPT.sf.ID28_18 & 0x07) << 5;
        CANx->DI0_OR_ACR1 |= f1->ACCEPT.sf.RTR << 4;
        CANx->DI0_OR_ACR1 |= f1->ACCEPT.sf.data1 >> 4;
        CANx->DI2_OR_ACR3 = f1->ACCEPT.sf.data1 & 0x0F;

        CANx->DI3_OR_AMR0 = f1->MASK.sf.ID28_18 >> 3;
        CANx->DI4_OR_AMR1 = (f1->MASK.sf.ID28_18 & 0x07) << 5;
        CANx->DI4_OR_AMR1 |= f1->MASK.sf.RTR << 4;
        CANx->DI4_OR_AMR1 = f1->MASK.sf.data1 >> 4;
        CANx->DI6_OR_AMR3 = f1->MASK.sf.data1 & 0x0F;
    } else if (f1->type == CAN_FLT_EXTENDED_SINGLE) {
      CANx->FI_OR_ACR0 = f1->ACCEPT.ef.ID28_13 >> 8;
        CANx->DI0_OR_ACR1 = f1->ACCEPT.ef.ID28_13 & 0xFF;
        CANx->DI1_OR_ACR2 = f1->ACCEPT.ef.ID12_0 >> 5;
        CANx->DI2_OR_ACR3 = (f1->ACCEPT.ef.ID12_0 & 0x1F) << 3;
        CANx->DI2_OR_ACR3 |= f1->ACCEPT.ef.RTR << 2;

        CANx->DI3_OR_AMR0 = f1->MASK.ef.ID28_13 >> 8;
        CANx->DI4_OR_AMR1 = f1->MASK.ef.ID28_13 & 0xFF;
        CANx->DI5_OR_AMR2 = f1->MASK.ef.ID12_0 >> 5;
        CANx->DI6_OR_AMR3 = (f1->MASK.ef.ID12_0 & 0x1F) << 3;
        CANx->DI6_OR_AMR3 |= f1->MASK.ef.RTR << 2;
    } else {
      CANx->FI_OR_ACR0 = f1->ACCEPT.ef.ID28_13 >> 8;
        CANx->DI0_OR_ACR1 = f1->ACCEPT.ef.ID28_13 & 0xFF;

        CANx->DI3_OR_AMR0 = f1->MASK.ef.ID28_13 >> 8;
        CANx->DI4_OR_AMR1 = f1->MASK.ef.ID28_13 & 0xFF;
    }

    if (IS_CAN_FLT_DUAL(f1->type)) {
        if (f2->type == CAN_FLT_STANDARD_DUAL) {
            CANx->DI1_OR_ACR2 = f2->ACCEPT.sf.ID28_18 >> 3;
            CANx->DI2_OR_ACR3 |= (f2->ACCEPT.sf.ID28_18 & 0x07) << 5;
            CANx->DI2_OR_ACR3 |= f2->ACCEPT.sf.RTR << 4;

            CANx->DI5_OR_AMR2 = f2->MASK.sf.ID28_18 >> 3;
            CANx->DI6_OR_AMR3 |= (f2->MASK.sf.ID28_18 & 0x07) << 5;
            CANx->DI6_OR_AMR3 |= f2->MASK.sf.RTR << 4;
        } else {
            CANx->DI1_OR_ACR2 = f2->ACCEPT.ef.ID28_13 >> 8;
            CANx->DI2_OR_ACR3 = f2->ACCEPT.ef.ID28_13 & 0xFF;

            CANx->DI5_OR_AMR2 = f2->MASK.ef.ID28_13 >> 8;
            CANx->DI6_OR_AMR3 = f2->MASK.ef.ID28_13 & 0xFF;
        }
    }

    if (IS_CAN_FLT_SINGLE(f1->type)) {
        CANx->MODE_b.AFM = 1;
    } else {
      CANx->MODE_b.AFM = 0;
    }

    return TRUE;
}

BOOL CAN_Init(CAN0_Type* CANx, CAN_InitTypeDef* Init,
  CAN_FILTER *f1, CAN_FILTER *f2) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(Init);
    assert_param(IS_CAN_CDR_DIV(Init->CAN_ClockDiv));

    /* Quit to sleep mode in operation mode */
    if (CANx->MODE_b.SM) {
        CANx->MODE_b.RM = FALSE;
        CANx->MODE_b.SM = FALSE;
    }

    /* switch to reset mode to set parameter */
    CANx->MODE_b.RM = TRUE;

    /* disable all interrupts and clear except receive interrupt */
    {
        uint8_t tmp;
        CANx->INT_EN &= ~CAN_INT_All;
        tmp = CANx->INT;
        tmp = tmp;
    }

    CANx->MODE_b.LOM = (Init->CAN_TxEn) ? FALSE : TRUE;

    CANx->MODE_b.STM = Init->CAN_Loopback;

    CANx->CDR_b.OFF = FALSE;
    CANx->CDR_b.DIVIDER = Init->CAN_ClockDiv;

    CANx->BTR0_b.BRP = Init->CAN_Prescaler;
    CANx->BTR0_b.SJW = Init->CAN_SJW;

    CANx->BTR1_b.TSEG1 = Init->CAN_TSEG1;
    CANx->BTR1_b.TSEG2 = Init->CAN_TSEG2;
    CANx->BTR1_b.SAM = !Init->CAN_HighSpeed;

    CANx->OCR_b.MODE = CAN_OCR_CLOCK;

  if (!can_SetFilter(CANx, f1, f2)) {
        return FALSE;
    }

    /* switch to operation mode */
    CANx->MODE_b.RM = FALSE;

    return TRUE;
}

void CAN_SetSleepMode(CAN0_Type* CANx, BOOL enable) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* switch to operation mode */
    CANx->MODE_b.RM = FALSE;

    CANx->MODE_b.SM = enable;
}

void CAN_EnableInt(CAN0_Type* CANx, uint32_t Int, BOOL enable) {
  assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_INT(Int));

    if (enable) {
        CANx->INT_EN |= CAN_INT_All;
    } else {
        CANx->INT_EN &= ~CAN_INT_All;
    }
}

uint8_t CAN_GetIntStatus(CAN0_Type* CANx) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    return CANx->INT;
}

BOOL CAN_Transmit(CAN0_Type* CANx, CAN_Frame* frame) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    if (!frame) {
        return FALSE;
    }

    if (CANx->MODE_b.LOM) {
        return FALSE;
    }

    if (CANx->MODE_b.SM) {
        CANx->MODE_b.RM = FALSE;
        CANx->MODE_b.SM = FALSE;
    }

    {
        CAN_FRAME_INFO fi;

        fi.U.FI_b.FF = !frame->SFF;
        fi.U.FI_b.RTR = frame->RTR;
        fi.U.FI_b.DLC = frame->DLC;

        CANx->FI_OR_ACR0 = fi.U.FI;
  }

  if (frame->SFF) {
        CAN_STANDARD_ID id;

        id.U.ID_b.ID28_21 = frame->Id >> 3;
        id.U.ID_b.RTR = frame->RTR;
        id.U.ID_b.ID20_18 = frame->Id & 0x07;

        CANx->DI0_OR_ACR1 = id.U.ID & 0xFF;
        CANx->DI1_OR_ACR2 = id.U.ID >> 8;

        CANx->DI2_OR_ACR3 = frame->Data[0];
        CANx->DI3_OR_AMR0 = frame->Data[1];
        CANx->DI4_OR_AMR1 = frame->Data[2];
        CANx->DI5_OR_AMR2 = frame->Data[3];
        CANx->DI6_OR_AMR3 = frame->Data[4];
        CANx->DI7 = frame->Data[5];
        CANx->DI8 = frame->Data[6];
        CANx->DI9 = frame->Data[7];
    } else {
        CAN_EXTENDED_ID id;

        id.U.ID_b.ID28_21 = frame->Id >> 21;
        id.U.ID_b.ID20_13 = (frame->Id >> 13) & 0xFF;
        id.U.ID_b.ID12_5 = (frame->Id >> 5) & 0xFF;
        id.U.ID_b.RTR = frame->RTR;
        id.U.ID_b.ID4_0 = frame->Id & 0x1F;

        CANx->DI0_OR_ACR1 = id.U.ID & 0xFF;
        CANx->DI1_OR_ACR2 = (id.U.ID >> 8) & 0xFF;
        CANx->DI2_OR_ACR3 = (id.U.ID >> 16) & 0xFF;
        CANx->DI3_OR_AMR0 = (id.U.ID >> 24) & 0xFF;

        CANx->DI4_OR_AMR1 = frame->Data[0];
        CANx->DI5_OR_AMR2 = frame->Data[1];
        CANx->DI6_OR_AMR3 = frame->Data[2];
        CANx->DI7 = frame->Data[3];
        CANx->DI8 = frame->Data[4];
        CANx->DI9 = frame->Data[5];
        CANx->DI10 = frame->Data[6];
        CANx->DI11 = frame->Data[7];
    }

  if (CANx->MODE_b.STM) {
      CANx->CMD_b.SSR = TRUE;
    } else {
        CANx->CMD_b.TR = TRUE;
    }

  return TRUE;
}

BOOL CAN_Receive(CAN0_Type* CANx, CAN_Frame* frame) {
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    if (!frame) {
        return FALSE;
    }

    if (CANx->MODE_b.SM) {
        CANx->MODE_b.RM = FALSE;
        CANx->MODE_b.SM = FALSE;
    }

    {
        CAN_FRAME_INFO fi;

        fi.U.FI = CANx->FI_OR_ACR0;

        frame->SFF = fi.U.FI_b.FF ? FALSE : TRUE;
        frame->RTR = fi.U.FI_b.RTR ? TRUE : FALSE;
        frame->DLC = fi.U.FI_b.DLC;
  }

  if (frame->SFF) {
        CAN_STANDARD_ID id;

        id.U.ID = CANx->DI0_OR_ACR1;
        id.U.ID |= CANx->DI1_OR_ACR2 << 8;

        frame->Id = id.U.ID_b.ID28_21 << 3;
        frame->Id |= id.U.ID_b.ID20_18;

        frame->Data[0] = CANx->DI2_OR_ACR3;
        frame->Data[1] = CANx->DI3_OR_AMR0;
        frame->Data[2] = CANx->DI4_OR_AMR1;
        frame->Data[3] = CANx->DI5_OR_AMR2;
        frame->Data[4] = CANx->DI6_OR_AMR3;
        frame->Data[5] = CANx->DI7;
        frame->Data[6] = CANx->DI8;
        frame->Data[7] = CANx->DI9;
    } else {
        CAN_EXTENDED_ID id;

        id.U.ID = CANx->DI0_OR_ACR1;
        id.U.ID |= CANx->DI1_OR_ACR2 << 8;
        id.U.ID |= CANx->DI2_OR_ACR3 << 16;
        id.U.ID |= CANx->DI3_OR_AMR0 << 24;

    frame->Id = id.U.ID_b.ID28_21 << 21;
        frame->Id |= id.U.ID_b.ID20_13 << 13;
        frame->Id |= id.U.ID_b.ID12_5 << 5;
        frame->Id |= id.U.ID_b.ID4_0;

        frame->Data[0] = CANx->DI4_OR_AMR1;
        frame->Data[1] = CANx->DI5_OR_AMR2;
        frame->Data[2] = CANx->DI6_OR_AMR3;
        frame->Data[3] = CANx->DI7;
        frame->Data[4] = CANx->DI8;
        frame->Data[5] = CANx->DI9;
        frame->Data[6] = CANx->DI10;
        frame->Data[7] = CANx->DI11;
    }

  CANx->CMD_b.RRB = TRUE;

  return TRUE;
}

