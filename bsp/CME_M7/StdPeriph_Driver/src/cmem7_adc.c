/**
    *****************************************************************************
    * @file     cmem7_adc.c
    *
    * @brief    CMEM7 ADC source file
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

#include "cmem7_adc.h"
#include "cmem7.h"

#define ADC_SYSTEM_MODE_IDLE       0

static BOOL adc_IsMultiChannel(uint32_t channel) {
    uint32_t i = 0;

    for (i = 0; channel != 0; i++) {
    channel &= (channel - 1);
    }

    return ((i > 1) ? TRUE : FALSE);
}

static uint8_t adc_GetChannel(uint32_t channel) {
    uint32_t i = 0;

    for (i = 0; channel > 1; i++) {
    channel >>= 1;
    }

    return i;
}

static void adc_Reset(uint8_t adc, BOOL enable) {
    if (adc == ADC_PERIPH_1) {
        ADC->POWERDOWN_RESET_b.POWERDOWN_ADC1 = TRUE;
        ADC->POWERDOWN_RESET_b.RESET_ADC1 = TRUE;
        udelay(8000);
        if (enable) {
            ADC->POWERDOWN_RESET_b.POWERDOWN_ADC1 = FALSE;
            ADC->POWERDOWN_RESET_b.RESET_ADC1 = FALSE;
            udelay(8000);
        }
    } else {
        ADC->POWERDOWN_RESET_b.POWERDOWN_ADC2 = TRUE;
        ADC->POWERDOWN_RESET_b.RESET_ADC2 = TRUE;
        udelay(8000);
        if (enable) {
            ADC->POWERDOWN_RESET_b.POWERDOWN_ADC2 = FALSE;
            ADC->POWERDOWN_RESET_b.RESET_ADC2 = FALSE;
            udelay(8000);
        }
    }
}

void ADC_Init(ADC_InitTypeDef* init) {
    assert_param(init);
    assert_param(IS_ADC_PHASE_CTRL(init->ADC_PhaseCtrl));
    assert_param(IS_ADC_VSEN(init->ADC_VsenSelection));

    SOFT_RESET->SOFTRST_b.ADC_n = 0;
    SOFT_RESET->SOFTRST_b.ADC_n = 1;

    ADC->CFG0_b.PHASE_CTRL = init->ADC_PhaseCtrl;
    ADC->CFG0_b.VSEN = init->ADC_VsenSelection;
}

void ADC_Enable(uint8_t adc, BOOL enable) {
    assert_param(IS_ADC_ALL_PERIPH(adc));

    adc_Reset(adc, enable);
}

void ADC_EnableInt(uint32_t Int, BOOL enable) {
    assert_param(IS_ADC_INT(Int));

    if (enable) {
      ADC->INT_MASK &= ~Int;
    } else {
        ADC->INT_MASK |= Int;
    }
}

BOOL ADC_GetIntStatus(uint32_t Int) {
    assert_param(IS_ADC_INT(Int));

    if (0 != (ADC->INT_STATUS & Int)) {
        return TRUE;
    }

    return FALSE;
}

void ADC_ClearInt(uint32_t Int) {
    assert_param(IS_ADC_INT(Int));

    ADC->INT_STATUS = Int;
}

BOOL ADC_StartConversion(uint8_t adc, uint8_t convMode, uint32_t channel) {
    assert_param(IS_ADC_ALL_PERIPH(adc));
    assert_param(IS_ADC_CONVERSION(convMode));

    if (adc == ADC_PERIPH_1) {
        assert_param(IS_ADC1_CHANNEL(channel));
        if (ADC->BUSY_b.ADC1_BUSY) {
            return FALSE;
        }

        if (adc_IsMultiChannel(channel)) {
            ADC->CFG_ADC1_b.SYSTEM_MODE = ADC_SYSTEM_MODE_SINGLE_CONV;
            ADC->CFG_ADC1_b.MULTI_CHANNEL_BIT = channel;
            ADC->CFG_ADC1_b.MULTI_CHANNEL_CONTINUE_SCAN =
                (convMode == ADC_SYSTEM_MODE_CONTINUOUS_CONV) ? 1 : 0;
        } else {
            ADC->CFG_ADC1_b.SYSTEM_MODE = convMode;

            if (convMode == ADC_SYSTEM_MODE_CONTINUOUS_CONV) {
                ADC->CFG_ADC1_b.CHANNEL_SEL = adc_GetChannel(channel);
            } else {
                ADC->CFG_ADC1_b.MULTI_CHANNEL_BIT = channel;
                ADC->CFG_ADC1_b.MULTI_CHANNEL_CONTINUE_SCAN = 0;
            }
        }

        ADC->ADC1_START_b.EN = TRUE;
    } else {
        assert_param(IS_ADC2_CHANNEL(channel));
        if (ADC->BUSY_b.ADC2_BUSY) {
            return FALSE;
        }

        if (adc_IsMultiChannel(channel)) {
            ADC->CFG_ADC2_b.SYSTEM_MODE = ADC_SYSTEM_MODE_SINGLE_CONV;
            ADC->CFG_ADC2_b.MULTI_CHANNEL_BIT = channel;
            ADC->CFG_ADC2_b.MULTI_CHANNEL_CONTINUE_SCAN =
                (convMode == ADC_SYSTEM_MODE_CONTINUOUS_CONV) ? 1 : 0;
        } else {
            ADC->CFG_ADC2_b.SYSTEM_MODE = convMode;

            if (convMode == ADC_SYSTEM_MODE_CONTINUOUS_CONV) {
                ADC->CFG_ADC2_b.CHANNEL_SEL = adc_GetChannel(channel);
            } else {
                ADC->CFG_ADC2_b.MULTI_CHANNEL_BIT = channel;
                ADC->CFG_ADC2_b.MULTI_CHANNEL_CONTINUE_SCAN = 0;
            }
        }

        ADC->ADC2_START_b.EN = TRUE;
    }

    return TRUE;
}

BOOL ADC_StartCalibration(uint8_t adc, uint8_t calibration) {
    assert_param(IS_ADC_ALL_PERIPH(adc));
    assert_param(IS_ADC_CALIBRATION(calibration));

    if (adc == ADC_PERIPH_1) {
        if (ADC->BUSY_b.ADC1_BUSY) {
            return FALSE;
        }

        ADC->CFG_ADC1_b.SYSTEM_MODE = calibration;
        ADC->ADC1_START_b.EN = TRUE;
    } else {
        if (ADC->BUSY_b.ADC2_BUSY) {
            return FALSE;
        }

        ADC->CFG_ADC2_b.SYSTEM_MODE = calibration;
        ADC->ADC2_START_b.EN = TRUE;
    }

    return TRUE;
}

void ADC_Stop(uint8_t adc) {
    assert_param(IS_ADC_ALL_PERIPH(adc));

    if (adc == ADC_PERIPH_1) {
        if (IS_ADC_CONVERSION(ADC->CFG_ADC1_b.SYSTEM_MODE)) {
            ADC->ADC1_STOP_b.EN = TRUE;
        }
        while (ADC->BUSY_b.ADC1_BUSY) ;

        ADC->ADC1_FIFO_CLEAR_b.CLEAR = TRUE;
        //udelay(1000);
        ADC->ADC1_FIFO_CLEAR_b.CLEAR = FALSE;
    } else {
        if (IS_ADC_CONVERSION(ADC->CFG_ADC2_b.SYSTEM_MODE)) {
            ADC->ADC2_STOP_b.EN = TRUE;
        }
        while (ADC->BUSY_b.ADC2_BUSY) ;

        ADC->ADC2_FIFO_CLEAR_b.CLEAR = TRUE;
        //udelay(1000);
        ADC->ADC2_FIFO_CLEAR_b.CLEAR = FALSE;
    }
}

BOOL ADC_IsBusy(uint8_t adc) {
    assert_param(IS_ADC_ALL_PERIPH(adc));

    if (adc == ADC_PERIPH_1) {
        if (ADC->BUSY_b.ADC1_BUSY) {
            return TRUE;
        }
    } else {
        if (ADC->BUSY_b.ADC2_BUSY) {
            return TRUE;
        }
    }

    return FALSE;
}

/* return value is actual read data size */
uint8_t ADC_Read(uint8_t adc, uint8_t size, ADC_Data* data) {
    uint8_t count = 0;
    uint8_t sysMode;
    uint32_t tmp = 0;
    assert_param(IS_ADC_ALL_PERIPH(adc));
    assert_param(data);

    if (adc == ADC_PERIPH_1) {
        sysMode = ADC->CFG_ADC1_b.SYSTEM_MODE;
    } else {
        sysMode = ADC->CFG_ADC2_b.SYSTEM_MODE;
    }

    if ((sysMode == ADC_SYSTEM_MODE_SINGLE_CONV) ||
        (sysMode == ADC_SYSTEM_MODE_CONTINUOUS_CONV)) {
        while (count < size) {
            if (adc == ADC_PERIPH_1) {
                if (ADC->STATUS_b.ADC1_READ_EMPTY) {
                    break;
                }

                tmp = ADC->ADC1_FIFO_READ;
                (data + count)->channel = 1 << ((tmp&0xf000) >> 12);
                (data + count++)->data = (tmp & 0xfff);
            } else {
                if (ADC->STATUS_b.ADC2_READ_EMPTY) {
                    break;
                }
                tmp = ADC->ADC2_FIFO_READ;
                (data + count)->channel = 1 << ((tmp&0xf000) >> 12);
                (data + count++)->data = (tmp & 0xfff);
            }
        }
    } else if (sysMode == ADC_CALIBRATION_OFFSET) {
        if (adc == ADC_PERIPH_1) {
            if (!ADC->BUSY_b.ADC1_BUSY) {
                (data + count)->channel = ADC_CHANNEL_CALIBRATION;
                (data + count++)->data = ADC->ADC1_OUT_OFFSET_CALIBRATION;
          }
        } else {
            if (!ADC->BUSY_b.ADC2_BUSY) {
                (data + count)->channel = ADC_CHANNEL_CALIBRATION;
                (data + count++)->data = ADC->ADC2_OUT_OFFSET_CALIBRATION;
          }
        }
    } else if (sysMode == ADC_CALIBRATION_NEGTIVE_GAIN) {
        if (adc == ADC_PERIPH_1) {
            if (!ADC->BUSY_b.ADC1_BUSY) {
                (data + count)->channel = ADC_CHANNEL_CALIBRATION;
                (data + count++)->data = ADC->ADC1_OUT_NEGTIVE_GAIN_CALIBRATION;
            }
        } else {
            if (!ADC->BUSY_b.ADC2_BUSY) {
              (data + count)->channel = ADC_CHANNEL_CALIBRATION;
                (data + count++)->data = ADC->ADC2_OUT_NEGTIVE_GAIN_CALIBRATION;
          }
        }
    } else {
        if (adc == ADC_PERIPH_1) {
            if (!ADC->BUSY_b.ADC1_BUSY) {
                (data + count)->channel = ADC_CHANNEL_CALIBRATION;
                (data + count++)->data = ADC->ADC1_OUT_POSITIVE_GAIN_CALIBRATION;
            }
        } else {
            if (!ADC->BUSY_b.ADC2_BUSY) {
              (data + count)->channel = ADC_CHANNEL_CALIBRATION;
                (data + count++)->data = ADC->ADC2_OUT_POSITIVE_GAIN_CALIBRATION;
          }
        }
    }

    return count;
}
