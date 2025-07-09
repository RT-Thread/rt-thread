/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_asrc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.asrc"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/*! @brief Typedef for asrc tx interrupt handler. */
typedef void (*asrc_isr_t)(ASRC_Type *base, asrc_handle_t *asrcHandle);
/*! @brief ASRC support maximum channel number */
#define ASRC_SUPPORT_MAXIMUM_CHANNEL_NUMER (10U)
#define ASRC_SAMPLE_RATIO_DECIMAL_DEPTH    (26U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief ASRC read non blocking.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 * @param destAddress dest buffer address.
 * @param samples number of samples to read.
 * @param sampleWidth the width that one sample takes.
 */
static void ASRC_ReadNonBlocking(
    ASRC_Type *base, asrc_channel_pair_t channelPair, uint32_t *destAddress, uint32_t samples, uint32_t sampleWidth);

/*!
 * @brief ASRC write non blocking.
 *
 * @param base ASRC base pointer.
 * @param channelPair ASRC channel pair.
 * @param srcAddress source buffer address.
 * @param samples number of samples to read.
 * @param sampleMask the mask of sample data.
 * @param sampleWidth the width that one sample takes.
 */
static void ASRC_WriteNonBlocking(ASRC_Type *base,
                                  asrc_channel_pair_t channelPair,
                                  const uint32_t *srcAddress,
                                  uint32_t samples,
                                  uint32_t sampleMask,
                                  uint32_t sampleWidth);

/*!
 * @brief ASRC calculate divider and prescaler.
 *
 * @param sampleRate_Hz sample rate.
 * @param sourceClock_Hz source clock.
 */
static uint32_t ASRC_CalculateClockDivider(uint32_t sampleRate_Hz, uint32_t sourceClock_Hz);

/*!
 * @brief ASRC pre/post processing selection.
 *
 * @param inSampleRate in audio data sample rate.
 * @param outSampleRate out audio data sample rate.
 * @param preProc pre processing selection.
 * @param postProc post precessing selection.
 */
static status_t ASRC_ProcessSelection(uint32_t inSampleRate,
                                      uint32_t outSampleRate,
                                      uint32_t *preProc,
                                      uint32_t *postProc);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Base pointer array */
static ASRC_Type *const s_asrcBases[] = ASRC_BASE_PTRS;
/*!@brief asrc handle pointer */
static asrc_handle_t *s_asrcHandle[ARRAY_SIZE(s_asrcBases)][FSL_ASRC_CHANNEL_PAIR_COUNT];
/* IRQ number array */
static const IRQn_Type s_asrcIRQ[] = ASRC_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name array */
static const clock_ip_name_t s_asrcClock[] = ASRC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
/*! @brief Pointer to IRQ handler for each instance. */
static asrc_isr_t s_asrcIsr;
/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t ASRC_GetInstance(ASRC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_asrcBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_asrcBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_asrcBases));

    return instance;
}

static void ASRC_ReadNonBlocking(
    ASRC_Type *base, asrc_channel_pair_t channelPair, uint32_t *destAddress, uint32_t samples, uint32_t sampleWidth)
{
    uint32_t i                 = 0U;
    uint32_t *destAddr         = destAddress;
    volatile uint32_t *srcAddr = ASRC_ASRDO_ADDR(base, channelPair);

    for (i = 0U; i < samples; i++)
    {
        *destAddr = *srcAddr;
        destAddr  = (uint32_t *)((uint32_t)destAddr + sampleWidth);
    }
}

static void ASRC_WriteNonBlocking(ASRC_Type *base,
                                  asrc_channel_pair_t channelPair,
                                  const uint32_t *srcAddress,
                                  uint32_t samples,
                                  uint32_t sampleMask,
                                  uint32_t sampleWidth)
{
    uint32_t i                  = 0U;
    const uint32_t *srcAddr     = srcAddress;
    volatile uint32_t *destAddr = ASRC_ASRDI_ADDR(base, channelPair);

    for (i = 0U; i < samples; i++)
    {
        *destAddr = *srcAddr & sampleMask;
        srcAddr   = (uint32_t *)((uint32_t)srcAddr + sampleWidth);
    }
}

static uint32_t ASRC_CalculateClockDivider(uint32_t sampleRate_Hz, uint32_t sourceClock_Hz)
{
    assert(sourceClock_Hz >= sampleRate_Hz);

    uint32_t divider   = sourceClock_Hz / sampleRate_Hz;
    uint32_t prescaler = 0U;

    /* sourceClock_Hz = sampleRate_Hz * divider * (2 ^ prescaler) */
    while (divider > 8U)
    {
        divider >>= 1U;
        prescaler++;
    }
    /* Hardware limitation:
     * If the prescaler is set to 1, the clock divider can only be set to 1 and the clock source must have a 50% duty
     * cycle
     */
    if ((prescaler == 1U) && (divider != 1U))
    {
        divider >>= 1U;
        prescaler++;
    }
    /* fine tuning */
    if (sourceClock_Hz / ((1UL << prescaler) * divider) > sampleRate_Hz)
    {
        divider++;
    }

    return ((divider - 1U) << 3U) | (prescaler & 0x7U);
}

static status_t ASRC_ProcessSelection(uint32_t inSampleRate,
                                      uint32_t outSampleRate,
                                      uint32_t *preProc,
                                      uint32_t *postProc)
{
    bool op2Cond = false;
    bool op0Cond = false;

    op2Cond = (((inSampleRate * 15U > outSampleRate * 16U) && (outSampleRate < 56000U)) ||
               ((inSampleRate > 56000U) && (outSampleRate < 56000U)));
    op0Cond = (inSampleRate * 23U < outSampleRate * 8U);

    /* preProc == 4 or preProc == 5 is not support now */
    if ((inSampleRate * 8U > 129U * outSampleRate) || ((inSampleRate * 8U > 65U * outSampleRate)))
    {
        return kStatus_ASRCNotSupport;
    }

    if (inSampleRate * 8U > 33U * outSampleRate)
    {
        *preProc = 2U;
    }
    else if (inSampleRate * 8U > 15U * outSampleRate)
    {
        if (inSampleRate > 152000U)
        {
            *preProc = 2U;
        }
        else
        {
            *preProc = 1U;
        }
    }
    else if (inSampleRate < 76000U)
    {
        *preProc = 0;
    }
    else if (inSampleRate > 152000U)
    {
        *preProc = 2;
    }
    else
    {
        *preProc = 1;
    }

    if (op2Cond)
    {
        *postProc = 2;
    }
    else if (op0Cond)
    {
        *postProc = 0;
    }
    else
    {
        *postProc = 1;
    }

    return kStatus_Success;
}

/*!
 * brief Map register sample width to real sample width.
 *
 * note This API is depends on the ASRC configuration, should be called after the ASRC_SetChannelPairConfig.
 * param base asrc base pointer.
 * param channelPair asrc channel pair index.
 * param inWidth ASRC channel pair number.
 * param outWidth input sample rate.
 * retval input sample mask value.
 */
uint32_t ASRC_MapSamplesWidth(ASRC_Type *base, asrc_channel_pair_t channelPair, uint32_t *inWidth, uint32_t *outWidth)
{
    uint32_t sampleMask   = 0U,
             inRegWidth   = (ASRC_ASRMCR1(base, channelPair) & ASRC_ASRMCR1_IWD_MASK) >> ASRC_ASRMCR1_IWD_SHIFT,
             outRegWidth  = ASRC_ASRMCR1(base, channelPair) & ASRC_ASRMCR1_OW16_MASK,
             inDataAlign  = (ASRC_ASRMCR1(base, channelPair) & ASRC_ASRMCR1_IMSB_MASK) >> ASRC_ASRMCR1_IMSB_SHIFT,
             outDataAlign = (ASRC_ASRMCR1(base, channelPair) & ASRC_ASRMCR1_OMSB_MASK) >> ASRC_ASRMCR1_OMSB_SHIFT;
    /* get in sample width */
    if (inRegWidth == (uint32_t)kASRC_DataWidth8Bit)
    {
        *inWidth   = 1U;
        sampleMask = 0xFFU;
        if (inDataAlign == (uint32_t)kASRC_DataAlignMSB)
        {
            *inWidth   = 2U;
            sampleMask = 0xFF00U;
        }
    }
    else if (inRegWidth == (uint32_t)kASRC_DataWidth16Bit)
    {
        *inWidth   = 2U;
        sampleMask = 0xFFFFU;
        if (inDataAlign == (uint32_t)kASRC_DataAlignMSB)
        {
            *inWidth   = 4U;
            sampleMask = 0xFFFF0000U;
        }
    }
    else
    {
        *inWidth   = 3U;
        sampleMask = 0xFFFFFFU;

        if (inDataAlign == (uint32_t)kASRC_DataAlignMSB)
        {
            sampleMask = 0xFFFFFF00U;
            *inWidth   = 4U;
        }
    }
    /* get out sample width */
    if (outRegWidth == (uint32_t)kASRC_DataWidth16Bit)
    {
        *outWidth = 2U;
        if (outDataAlign == (uint32_t)kASRC_DataAlignMSB)
        {
            *outWidth = 4U;
        }
    }
    else
    {
        *outWidth = 4U;
    }

    return sampleMask;
}

/*!
 * brief ASRC configure ideal ratio.
 * The ideal ratio should be used when input clock source is not avalible.
 *
 * param base ASRC base pointer.
 * param channelPair ASRC channel pair.
 * param inputSampleRate input audio data sample rate.
 * param outputSampleRate output audio data sample rate.
 */
status_t ASRC_SetIdealRatioConfig(ASRC_Type *base,
                                  asrc_channel_pair_t channelPair,
                                  uint32_t inputSampleRate,
                                  uint32_t outputSampleRate)
{
    uint32_t ratio = 0U, i = 0U;
    uint32_t preProc = 0U, postProc = 0U;
    uint32_t asrcfg = base->ASRCFG;
    /* caculate integer part */
    ratio = (inputSampleRate / outputSampleRate) << ASRC_SAMPLE_RATIO_DECIMAL_DEPTH;

    inputSampleRate %= outputSampleRate;
    /* get decimal part */
    for (i = 1U; i <= ASRC_SAMPLE_RATIO_DECIMAL_DEPTH; i++)
    {
        inputSampleRate <<= 1;

        if (inputSampleRate < outputSampleRate)
        {
            continue;
        }

        ratio |= 1UL << (ASRC_SAMPLE_RATIO_DECIMAL_DEPTH - i);
        inputSampleRate -= outputSampleRate;

        if (0U == inputSampleRate)
        {
            break;
        }
    }
    /* select pre/post precessing option */
    if (ASRC_ProcessSelection(inputSampleRate, outputSampleRate, &preProc, &postProc) != kStatus_Success)
    {
        return kStatus_ASRCNotSupport;
    }

    ASRC_IDEAL_RATIO_HIGH(base, channelPair) = ASRC_ASRIDRHA_IDRATIOA_H(ratio >> 24U);
    ASRC_IDEAL_RATIO_LOW(base, channelPair)  = ASRC_ASRIDRLA_IDRATIOA_L(ratio);
    base->ASRCTR &= ~ASRC_ASRCTR_AT_MASK(channelPair);
    asrcfg &= ~(ASRC_ASRCFG_PRE_MODE_MASK(channelPair) | ASRC_ASRCFG_POST_MODE_MASK(channelPair));
    asrcfg |= ASRC_ASRCFG_PRE_MODE(preProc, channelPair) | ASRC_ASRCFG_POST_MODE(postProc, channelPair);
    base->ASRCFG = asrcfg;

    return kStatus_Success;
}

/*!
 * brief Initializes the asrc peripheral.
 *
 * This API gates the asrc clock. The asrc module can't operate unless ASRC_Init is called to enable the clock.
 *
 * param base asrc base pointer.
 * param asrcPeripheralClock_Hz peripheral clock of ASRC.
 */
void ASRC_Init(ASRC_Type *base, uint32_t asrcPeripheralClock_Hz)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the asrc clock */
    CLOCK_EnableClock(s_asrcClock[ASRC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* disable ASRC channel pair, enable ASRC */
    base->ASRCTR = 1U;

    /* disable all the interrupt */
    base->ASRIER = 0U;

#if (defined FSL_FEATURE_ASRC_PARAMETER_REGISTER_NAME_ASRPM) && FSL_FEATURE_ASRC_PARAMETER_REGISTER_NAME_ASRPM
    /* set paramter register to default configurations per recommand value in reference manual */
    base->ASRPM[0] = 0x7fffffU;
    base->ASRPM[1] = 0x255555U;
    base->ASRPM[2] = 0xff7280U;
    base->ASRPM[3] = 0xff7280U;
    base->ASRPM[4] = 0xff7280U;
#else
    /* set paramter register to default configurations per recommand value in reference manual */
    base->ASRPMn[0] = 0x7fffffU;
    base->ASRPMn[1] = 0x255555U;
    base->ASRPMn[2] = 0xff7280U;
    base->ASRPMn[3] = 0xff7280U;
    base->ASRPMn[4] = 0xff7280U;
#endif /*FSL_FEATURE_ASRC_PARAMETER_REGISTER_NAME_ASRPM*/
    /* set task queue fifo */
    base->ASRTFR1 = ASRC_ASRTFR1_TF_BASE(0x7C);
    /* 76K/56K divider */
    base->ASR76K = ASRC_ASR76K_ASR76K(asrcPeripheralClock_Hz / 76000U);
    base->ASR56K = ASRC_ASR56K_ASR56K(asrcPeripheralClock_Hz / 56000U);
}

/*!
 * brief De-initializes the ASRC peripheral.
 *
 * This API gates the ASRC clock and disable ASRC module. The ASRC module can't operate unless ASRC_Init
 *
 * param base ASRC base pointer.
 */
void ASRC_Deinit(ASRC_Type *base)
{
    /* disable ASRC module */
    ASRC_ModuleEnable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_asrcClock[ASRC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Do software reset .
 *
 * This software reset bit is self-clear bit, it will generate a software reset signal inside ASRC.
 * After 9 cycles of the ASRC processing clock, this reset process will stop and this bit will cleared
 * automatically.
 *
 * param base ASRC base pointer
 */
void ASRC_SoftwareReset(ASRC_Type *base)
{
    base->ASRCTR |= ASRC_ASRCTR_SRST_MASK;
    /* polling reset clear automatically */
    while ((base->ASRCTR & ASRC_ASRCTR_SRST_MASK) != 0U)
    {
    }
}

/*!
 * brief ASRC configure channel pair.
 *
 * param base ASRC base pointer.
 * param channelPair index of channel pair, reference _asrc_channel_pair.
 * param config ASRC channel pair configuration pointer.
 * param inputSampleRate in audio data sample rate.
 * param outSampleRate out audio data sample rate.
 */
status_t ASRC_SetChannelPairConfig(ASRC_Type *base,
                                   asrc_channel_pair_t channelPair,
                                   asrc_channel_pair_config_t *config,
                                   uint32_t inputSampleRate,
                                   uint32_t outputSampleRate)
{
    assert(config != NULL);

    if (config->outDataWidth == kASRC_DataWidth8Bit)
    {
        return kStatus_InvalidArgument;
    }

    if (((inputSampleRate < (uint32_t)kASRC_SampleRate_8000HZ) ||
         (inputSampleRate > (uint32_t)kASRC_SampleRate_192000HZ)) ||
        ((outputSampleRate < (uint32_t)kASRC_SampleRate_8000HZ) ||
         (outputSampleRate > (uint32_t)kASRC_SampleRate_192000HZ)) ||
        (((outputSampleRate > (uint32_t)kASRC_SampleRate_8000HZ) &&
          (outputSampleRate < (uint32_t)kASRC_SampleRate_30000HZ)) &&
         (inputSampleRate / outputSampleRate > 8U || outputSampleRate / inputSampleRate > 24U)))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t i = 0U;
    /* channel pair processing selection and ratio configuration */
    uint32_t asrctr = base->ASRCTR & (~(ASRC_ASRCTR_AT_MASK(channelPair) | ASRC_ASRCTR_RATIO_MASK(channelPair)));
    /* use automatic selection for processing option by default */
    asrctr |= ASRC_ASRCTR_AT_MASK(channelPair);
    /* ratio configuration */
    asrctr |= ASRC_ASRCTR_RATIO(config->sampleRateRatio, channelPair);
    base->ASRCTR = asrctr;

    /* audio data channel counter configurations */
    uint32_t asrcncr = base->ASRCNCR & (~ASRC_ASRCNCR_CHANNEL_COUNTER_MASK(channelPair));
    base->ASRCNCR    = asrcncr | ASRC_ASRCNCR_CHANNEL_COUNTER(config->audioDataChannels, channelPair);

    /* in clock source and out clock source configurations */
    uint32_t asrcsr =
        base->ASRCSR &
        (~(ASRC_ASRCSR_INPUT_CLOCK_SOURCE_MASK(channelPair) | ASRC_ASRCSR_OUTPUT_CLOCK_SOURCE_MASK(channelPair)));
    if (config->outClockSource < 0 || config->outClockSource > kASRC_ClockSourceBitClocke_MQS_CLOCK_ROOT) {
        return kStatus_InvalidArgument;
    }
    asrcsr |= ASRC_ASRCSR_OUTPUT_CLOCK_SOURCE(config->outClockSource, channelPair);
    if (config->inClockSource != kASRC_ClockSourceNotAvalible)
    {
        asrcsr |= ASRC_ASRCSR_INPUT_CLOCK_SOURCE(config->inClockSource, channelPair);
    }
    base->ASRCSR = asrcsr;

    /* clock divider configuration */
    uint32_t asrcdr =
        base->ASRCDR1 &
        (~(ASRC_ASRCDR_INPUT_PRESCALER_MASK(channelPair) | ASRC_ASRCDR_INPUT_DIVIDER_MASK(channelPair) |
           ASRC_ASRCDR_OUTPUT_PRESCALER_MASK(channelPair) | ASRC_ASRCDR_OUTPUT_DIVIDER_MASK(channelPair)));

    asrcdr |= ASCR_ASRCDR_OUTPUT_CLOCK_DIVIDER_PRESCALER(
        ASRC_CalculateClockDivider(outputSampleRate, config->outSourceClock_Hz), channelPair);
    if (config->inClockSource != kASRC_ClockSourceNotAvalible)
    {
        asrcdr |= ASCR_ASRCDR_INPUT_CLOCK_DIVIDER_PRESCALER(
            ASRC_CalculateClockDivider(inputSampleRate, config->inSourceClock_Hz), channelPair);
    }

    if (channelPair == kASRC_ChannelPairC)
    {
        base->ASRCDR2 = asrcdr;
    }
    else
    {
        base->ASRCDR1 = asrcdr;
    }

    /* data width/sign extension/data align configuration */
    ASRC_ASRMCR1(base, channelPair) = ASRC_ASRMCR1_OW16(config->outDataWidth) | ASRC_ASRMCR1_IWD(config->inDataWidth) |
                                      ASRC_ASRMCR1_OSGN(config->outSignExtension) |
                                      ASRC_ASRMCR1_OMSB(config->outDataAlign) | ASRC_ASRMCR1_IMSB(config->inDataAlign);
    /* data configurations, MISC */
    uint32_t asrmcra = ASRC_ASRMCR(base, channelPair) &
                       (~(ASRC_ASRMCRA_BUFSTALLA_MASK | ASRC_ASRMCRA_EXTTHRSHA_MASK |
                          ASRC_ASRMCRA_INFIFO_THRESHOLDA_MASK | ASRC_ASRMCRA_OUTFIFO_THRESHOLDA_MASK));
    /* buffer stall */
    asrmcra |= ASRC_ASRMCRA_BUFSTALLA(config->bufStallWhenFifoEmptyFull ? 1U : 0U);
    /* in fifo and out fifo threshold */
    asrmcra |= ASRC_ASRMCRA_EXTTHRSHA_MASK | ASRC_ASRMCRA_INFIFO_THRESHOLDA(config->inFifoThreshold - 1UL) |
               ASRC_ASRMCRA_OUTFIFO_THRESHOLDA(config->outFifoThreshold - 1UL);
    ASRC_ASRMCR(base, channelPair) = asrmcra;

    if (config->sampleRateRatio == kASRC_RatioUseIdealRatio)
    {
        if (ASRC_SetIdealRatioConfig(base, channelPair, inputSampleRate, outputSampleRate) != kStatus_Success)
        {
            return kStatus_ASRCChannelPairConfigureFailed;
        }
    }

    /* channel pair enable */
    ASRC_ChannelPairEnable(base, channelPair, true);

    /* wait channel initial served */
    while (!ASRC_GetChannelPairInitialStatus(base, channelPair))
    {
    }

    for (i = 0U; i < (uint32_t)config->audioDataChannels * 4U; i++)
    {
        ASRC_ChannelPairWriteData(base, channelPair, 0U);
    }

    return kStatus_Success;
}

/*!
 * brief Get output sample buffer size.
 *
 * note This API is depends on the ASRC output configuration, should be called after the ASRC_SetChannelPairConfig.
 *
 * param base asrc base pointer.
 * param channelPair ASRC channel pair number.
 * param inSampleRate input sample rate.
 * param outSampleRate output sample rate.
 * param inSamples input sampleS size.
 * retval output buffer size in byte.
 */
uint32_t ASRC_GetOutSamplesSize(ASRC_Type *base,
                                asrc_channel_pair_t channelPair,
                                uint32_t inSampleRate,
                                uint32_t outSampleRate,
                                uint32_t inSamplesize)
{
    uint32_t inSamples         = 0U;
    uint32_t outSamples        = 0U;
    uint32_t outSamplesBufSize = 0U, audioChannels = ASRC_GET_CHANNEL_COUNTER(base, channelPair);
    ;
    asrc_data_width_t outWdith = (base->ASRMCR1[channelPair] & ASRC_ASRMCR1_OW16_MASK) == ASRC_ASRMCR1_OW16_MASK ?
                                     kASRC_DataWidth16Bit :
                                     kASRC_DataWidth24Bit;
    asrc_data_align_t outAlign = (base->ASRMCR1[channelPair] & ASRC_ASRMCR1_OMSB_MASK) == ASRC_ASRMCR1_OMSB_MASK ?
                                     kASRC_DataAlignMSB :
                                     kASRC_DataAlignLSB;
    uint32_t inWdith          = (base->ASRMCR1[channelPair] & ASRC_ASRMCR1_IWD_MASK) >> ASRC_ASRMCR1_IWD_SHIFT;
    asrc_data_align_t inAlign = (base->ASRMCR1[channelPair] & ASRC_ASRMCR1_IMSB_MASK) == ASRC_ASRMCR1_IMSB_MASK ?
                                    kASRC_DataAlignMSB :
                                    kASRC_DataAlignLSB;

    bool signExtend = (base->ASRMCR1[channelPair] & ASRC_ASRMCR1_OSGN_MASK) == ASRC_ASRMCR1_OSGN_MASK ? true : false;

    /* 24bit input data */
    if (inWdith == 0U)
    {
        inSamples = inSamplesize / (inAlign == kASRC_DataAlignMSB ? 4U : 3U);
    }
    /* 16bit input data */
    else if (inWdith == 1U)
    {
        inSamples = inSamplesize / (inAlign == kASRC_DataAlignMSB ? 4U : 2U);
    }
    /* 8bit input data */
    else
    {
        inSamples = inSamplesize / (inAlign == kASRC_DataAlignMSB ? 2U : 1U);
    }

    /* Cert-compliant overflow check */
    if (inSamples > UINT32_MAX / outSampleRate) {
        return kStatus_OutOfRange;
    }
    else
    {
        outSamples = inSamples * outSampleRate / inSampleRate;
    }
    /* make sure output samples is in group */
    outSamples = outSamples - outSamples % audioChannels;

    if (outWdith == kASRC_DataWidth16Bit)
    {
        if ((outAlign == kASRC_DataAlignMSB) || signExtend)
        {
            /* Cert-compliant overflow check */
            if (outSamples > UINT32_MAX / 4U) {
                return kStatus_OutOfRange;
            } else {
                outSamplesBufSize = outSamples * 4U;
            }
        }
        else
        {
            /* Cert-compliant overflow check */
            if (outSamples > UINT32_MAX / 2U) {
                return kStatus_OutOfRange;
            } else {
                outSamplesBufSize = outSamples * 2U;
            }
        }
    }

    if (outWdith == kASRC_DataWidth24Bit)
    {
        /* Cert-compliant overflow check */
        if (outSamples > UINT32_MAX / 4U) {
            return kStatus_OutOfRange;
        } else {
            outSamplesBufSize = outSamples * 4U;
        }
    }

    return outSamplesBufSize;
}

/*!
 * brief Performs an blocking convert on asrc.
 *
 * note This API returns immediately after the convert finished.
 *
 * param base asrc base pointer.
 * param channelPair channel pair index.
 * param xfer Pointer to the ASRC_transfer_t structure.
 * retval kStatus_Success Successfully started the data receive.
 */
status_t ASRC_TransferBlocking(ASRC_Type *base, asrc_channel_pair_t channelPair, asrc_transfer_t *xfer)
{
    assert(xfer != NULL);

    uint32_t inWaterMark  = ASRC_ASRMCR(base, channelPair) & ASRC_ASRMCRA_INFIFO_THRESHOLDA_MASK,
             outWaterMark = (ASRC_ASRMCR(base, channelPair) & ASRC_ASRMCRA_OUTFIFO_THRESHOLDA_MASK) >>
                            ASRC_ASRMCRA_OUTFIFO_THRESHOLDA_SHIFT,
             audioChannels = ASRC_GET_CHANNEL_COUNTER(base, channelPair);
    uint8_t *inAddr = (uint8_t *)xfer->inData, *outAddr = (uint8_t *)xfer->outData;
    uint32_t onceWriteSamples = 0U;
    uint32_t status = 0U, inSampleMask = 0U, inSamples = 0U, outSamples = 0U, inWidth = 0U, outWidth = 0U;

    inSampleMask = ASRC_MapSamplesWidth(base, channelPair, &inWidth, &outWidth);
    inSamples    = xfer->inDataSize / inWidth;
    outSamples   = xfer->outDataSize / outWidth;
    inWaterMark *= audioChannels;
    outWaterMark *= audioChannels;

    while (outSamples != 0U)
    {
        status = ASRC_GetStatus(base);

        if ((status & (1UL << ((uint32_t)channelPair + ASRC_ASRSTR_AIDEA_SHIFT))) != 0U)
        {
            onceWriteSamples =
                MIN(inSamples, (size_t)((FSL_ASRC_CHANNEL_PAIR_FIFO_DEPTH * audioChannels - inWaterMark)));
            ASRC_WriteNonBlocking(base, channelPair, (uint32_t *)(uint32_t)inAddr, onceWriteSamples, inSampleMask,
                                  inWidth);
            /* Cert-compliant overflow check */
            if (onceWriteSamples > (UINT32_MAX - (uint32_t)inAddr) / inWidth)
            {
                return kStatus_OutOfRange;
            }
            inAddr = (uint8_t *)((uint32_t)inAddr + onceWriteSamples * inWidth);
            inSamples -= onceWriteSamples;
        }

        if (outSamples > outWaterMark)
        {
            if ((status & (1UL << ((uint32_t)channelPair + ASRC_ASRSTR_AODFA_SHIFT))) != 0U)
            {
                ASRC_ReadNonBlocking(base, channelPair, (uint32_t *)(uint32_t)outAddr, outWaterMark, outWidth);
                /* Cert-compliant overflow check */
                if (outWaterMark > (UINT32_MAX - (uint32_t)outAddr) / outWidth)
                {
                  return kStatus_OutOfRange;
                }
                outAddr = (uint8_t *)((uint32_t)outAddr + outWaterMark * outWidth);
                outSamples -= outWaterMark;
            }
        }
        else
        {
            uint32_t samplesProcessed = ASRC_GetRemainFifoSamples(base, channelPair,
                                (uint32_t *)(uint32_t)outAddr, outWidth, outSamples);
            /* Cert-compliant overflow check */
            if (samplesProcessed > outSamples) {
                return kStatus_OutOfRange;
            }
            outSamples -= samplesProcessed;
            continue;
        }
    }

    return kStatus_Success;
}

/*!
 * brief ASRC configure channel pair.
 *
 * param base ASRC base pointer.
 * param handle ASRC transactional handle pointer.
 * param config ASRC channel pair configuration pointer.
 * param inputSampleRate in audio data sample rate.
 * param outputSampleRate out audio data sample rate.
 */
status_t ASRC_TransferSetChannelPairConfig(ASRC_Type *base,
                                           asrc_handle_t *handle,
                                           asrc_channel_pair_config_t *config,
                                           uint32_t inputSampleRate,
                                           uint32_t outputSampleRate)
{
    assert(handle != NULL);

    handle->in.fifoThreshold  = config->inFifoThreshold * (uint32_t)config->audioDataChannels;
    handle->out.fifoThreshold = config->outFifoThreshold * (uint32_t)config->audioDataChannels;
    handle->audioDataChannels = config->audioDataChannels;

    if (ASRC_SetChannelPairConfig(base, handle->channelPair, config, inputSampleRate, outputSampleRate) !=
        kStatus_Success)
    {
        return kStatus_ASRCChannelPairConfigureFailed;
    }

    handle->in.sampleMask =
        ASRC_MapSamplesWidth(base, handle->channelPair, &handle->in.sampleWidth, &handle->out.sampleWidth);

    return kStatus_Success;
}

/*!
 * brief Get left samples in fifo.
 *
 * param base asrc base pointer.
 * param channelPair ASRC channel pair number.
 * param buffer input sample numbers.
 * param outSampleWidth output sample width.
 * param remainSamples output sample rate.
 * retval remain samples number.
 */
uint32_t ASRC_GetRemainFifoSamples(
    ASRC_Type *base, asrc_channel_pair_t channelPair, uint32_t *buffer, uint32_t outSampleWidth, uint32_t remainSamples)
{
    uint32_t remainSamplesInFifo = 0U;
    uint32_t audioChannels       = ASRC_GET_CHANNEL_COUNTER(base, channelPair);
    remainSamplesInFifo =
        ((ASRC_ASRFST_ADDR(base, channelPair) & ASRC_ASRFSTA_OUTFIFO_FILLA_MASK) >> ASRC_ASRFSTA_OUTFIFO_FILLA_SHIFT) *
        audioChannels;

    if (remainSamples < remainSamplesInFifo)
    {
        remainSamplesInFifo = remainSamples;
    }

    ASRC_ReadNonBlocking(base, channelPair, (uint32_t *)buffer, remainSamplesInFifo, outSampleWidth);

    return remainSamplesInFifo;
}

/*!
 * brief Initializes the ASRC handle.
 *
 * This function initializes the handle for the ASRC transactional APIs. Call
 * this function once to get the handle initialized.
 *
 * param base ASRC base pointer
 * param handle ASRC handle pointer.
 * param inCallback Pointer to the user callback function.
 * param outCallback Pointer to the user callback function.
 * param userData User parameter passed to the callback function
 */
void ASRC_TransferCreateHandle(ASRC_Type *base,
                               asrc_handle_t *handle,
                               asrc_channel_pair_t channelPair,
                               asrc_transfer_callback_t inCallback,
                               asrc_transfer_callback_t outCallback,
                               void *userData)
{
    assert(handle != NULL);

    uint32_t instance = ASRC_GetInstance(base);

    (void)memset(handle, 0, sizeof(*handle));

    s_asrcHandle[instance][channelPair] = handle;

    handle->in.callback  = inCallback;
    handle->out.callback = outCallback;
    handle->userData     = userData;
    handle->channelPair  = channelPair;
    /* Set the isr pointer */
    s_asrcIsr = ASRC_TransferHandleIRQ;

    (void)EnableIRQ(s_asrcIRQ[instance]);
}

/*!
 * brief Performs an interrupt non-blocking convert on asrc.
 *
 * note This API returns immediately after the transfer initiates, application should check the wait and check the
 * callback status.
 *
 * param base asrc base pointer.
 * param handle Pointer to the asrc_handle_t structure which stores the transfer state.
 * param xfer Pointer to the ASRC_transfer_t structure.
 * retval kStatus_Success Successfully started the data receive.
 * retval kStatus_ASRCBusy Previous receive still not finished.
 */
status_t ASRC_TransferNonBlocking(ASRC_Type *base, asrc_handle_t *handle, asrc_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    /* Check if the queue is full */
    if ((handle->in.asrcQueue[handle->in.queueUser] != NULL) || (handle->out.asrcQueue[handle->out.queueUser] != NULL))
    {
        return kStatus_ASRCBusy;
    }

    /* Add into queue */
    handle->in.transferSamples[handle->in.queueUser] = xfer->inDataSize / handle->in.sampleWidth;
    handle->in.asrcQueue[handle->in.queueUser]       = xfer->inData;
    handle->in.queueUser                             = (handle->in.queueUser + 1U) % ASRC_XFER_QUEUE_SIZE;

    handle->out.asrcQueue[handle->out.queueUser]       = xfer->outData;
    handle->out.transferSamples[handle->out.queueUser] = xfer->outDataSize / handle->out.sampleWidth;
    handle->out.queueUser                              = (handle->out.queueUser + 1U) % ASRC_XFER_QUEUE_SIZE;

    if (handle->state != (uint32_t)kStatus_ASRCBusy)
    {
        /* enable channel pair interrupt */
        ASRC_EnableInterrupt(base, ASRC_ASRIER_INPUT_INTERRUPT_MASK(handle->channelPair) |
                                       (uint32_t)kASRC_OverLoadInterruptMask |
                                       ASRC_ASRIER_OUTPUTPUT_INTERRUPT_MASK(handle->channelPair));
    }

    /* Set the state to busy */
    handle->state = kStatus_ASRCBusy;

    return kStatus_Success;
}

/*!
 * brief Gets a set byte count.
 *
 * param base asrc base pointer.
 * param handle Pointer to the ASRC_handle_t structure which stores the transfer state.
 * param count Bytes count sent.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ASRC_TransferGetConvertedCount(ASRC_Type *base, asrc_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kStatus_ASRCBusy)
    {
        status = kStatus_ASRCIdle;
    }
    else
    {
        *count = handle->out.transferSamples[handle->out.queueDriver];
    }

    return status;
}

/*!
 * brief Aborts the current convert.
 *
 * note This API can be called any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base asrc base pointer.
 * param handle Pointer to the ASRC_handle_t structure which stores the transfer state.
 */
void ASRC_TransferAbortConvert(ASRC_Type *base, asrc_handle_t *handle)
{
    assert(handle != NULL);

    /* enable ASRC module */
    ASRC_ModuleEnable(base, false);

    handle->state = kStatus_ASRCIdle;

    handle->in.queueDriver  = 0;
    handle->in.queueUser    = 0;
    handle->out.queueDriver = 0;
    handle->out.queueUser   = 0;
}

/*!
 * brief Terminate all asrc convert.
 *
 * This function will clear all transfer slots buffered in the asrc queue. If users only want to abort the
 * current transfer slot, please call ASRC_TransferAbortSend.
 *
 * param base asrc base pointer.
 * param handle asrc eDMA handle pointer.
 */
void ASRC_TransferTerminateConvert(ASRC_Type *base, asrc_handle_t *handle)
{
    assert(handle != NULL);

    /* Abort the current transfer */
    ASRC_TransferAbortConvert(base, handle);

    /* Clear all the internal information */
    (void)memset(handle->in.asrcQueue, 0, sizeof(handle->in.asrcQueue));
    (void)memset(handle->in.transferSamples, 0, sizeof(handle->in.transferSamples));
    (void)memset(handle->out.asrcQueue, 0, sizeof(handle->out.asrcQueue));
    (void)memset(handle->out.transferSamples, 0, sizeof(handle->out.transferSamples));
}

/*!
 * brief ASRC convert interrupt handler.
 *
 * param base asrc base pointer.
 * param handle Pointer to the asrc_handle_t structure.
 */
void ASRC_TransferHandleIRQ(ASRC_Type *base, asrc_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t status = base->ASRSTR;

    /* Handle Error */
    if ((status & (uint32_t)kASRC_StatusInputError) != 0U)
    {
        /* Call the callback */
        if (handle->in.callback != NULL)
        {
            (handle->in.callback)(base, handle, kStatus_ASRCConvertError, handle->userData);
        }
    }

    if ((status & (uint32_t)kASRC_StatusOutputError) != 0U)
    {
        /* Call the callback */
        if (handle->out.callback != NULL)
        {
            (handle->out.callback)(base, handle, kStatus_ASRCConvertError, handle->userData);
        }
    }

    /* Handle transfer */
    if ((status & (1UL << ((uint32_t)handle->channelPair + ASRC_ASRSTR_AODFA_SHIFT))) != 0U)
    {
        if (handle->out.transferSamples[handle->out.queueDriver] != 0U)
        {
            ASRC_ReadNonBlocking(base, handle->channelPair,
                                 (uint32_t *)(uint32_t)handle->out.asrcQueue[handle->out.queueDriver],
                                 handle->out.fifoThreshold, handle->out.sampleWidth);
            handle->out.transferSamples[handle->out.queueDriver] -= handle->out.fifoThreshold;
            handle->out.asrcQueue[handle->out.queueDriver] =
                (uint8_t *)((uint32_t)handle->out.asrcQueue[handle->out.queueDriver] +
                            handle->out.fifoThreshold * handle->out.sampleWidth);
        }
    }

    if ((status & (1UL << ((uint32_t)handle->channelPair + ASRC_ASRSTR_AIDEA_SHIFT))) != 0U)
    {
        /* Judge if the data need to transmit is less than space */
        uint32_t size = MIN((handle->in.transferSamples[handle->in.queueDriver]),
                            (size_t)((FSL_ASRC_CHANNEL_PAIR_FIFO_DEPTH * (uint32_t)handle->audioDataChannels -
                                      handle->in.fifoThreshold)));
        ASRC_WriteNonBlocking(base, handle->channelPair,
                              (uint32_t *)(uint32_t)handle->in.asrcQueue[handle->in.queueDriver], size,
                              handle->in.sampleMask, handle->in.sampleWidth);
        handle->in.transferSamples[handle->in.queueDriver] -= size;
        /* Cert-compliant overflow check */
        if (size < (UINT32_MAX - (uint32_t)handle->in.asrcQueue[handle->in.queueDriver]) / handle->in.sampleWidth)
        {
            handle->in.asrcQueue[handle->in.queueDriver] =
                (uint8_t *)((uint32_t)handle->in.asrcQueue[handle->in.queueDriver] + size * handle->in.sampleWidth);
        }
    }

    /* If finished a block, call the callback function */
    if (handle->in.transferSamples[handle->in.queueDriver] == 0U)
    {
        handle->in.asrcQueue[handle->in.queueDriver] = NULL;
        handle->in.queueDriver                       = (handle->in.queueDriver + 1U) % ASRC_XFER_QUEUE_SIZE;
        if (handle->in.callback != NULL)
        {
            (handle->in.callback)(base, handle, kStatus_ASRCIdle, handle->userData);
        }
    }

    if (handle->out.transferSamples[handle->out.queueDriver] < (handle->out.fifoThreshold + 1U))
    {
        uint32_t samplesProcessed = ASRC_GetRemainFifoSamples(
            base, handle->channelPair, (uint32_t *)(uint32_t)handle->out.asrcQueue[handle->out.queueDriver],
            handle->out.sampleWidth, handle->out.transferSamples[handle->out.queueDriver]);

        /* Cert-compliant overflow check */
        if (samplesProcessed <= handle->out.transferSamples[handle->out.queueDriver]) {
            handle->out.transferSamples[handle->out.queueDriver] -= samplesProcessed;
        } else {
            /* Handle error condition (should never occur given function implementation) */
            handle->out.transferSamples[handle->out.queueDriver] = 0;
        }
    }

    if (handle->out.transferSamples[handle->out.queueDriver] == 0U)
    {
        handle->out.asrcQueue[handle->out.queueDriver] = NULL;
        handle->out.queueDriver                        = (handle->out.queueDriver + 1U) % ASRC_XFER_QUEUE_SIZE;
        if (handle->out.callback != NULL)
        {
            (handle->out.callback)(base, handle, kStatus_ASRCIdle, handle->userData);
        }
    }

    /* If all data finished, just stop the transfer */
    if (handle->out.asrcQueue[handle->out.queueDriver] == NULL)
    {
        ASRC_TransferAbortConvert(base, handle);
    }
}

#if defined ASRC
void ASRC_DriverIRQHandler(void);
void ASRC_DriverIRQHandler(void)
{
    /* channel PAIR A interrupt handling*/
    if ((ASRC->ASRSTR & (uint32_t)kASRC_StatusPairAInterrupt) != 0U)
    {
        s_asrcIsr(ASRC, s_asrcHandle[0][0U]);
    }
    /* channel PAIR B interrupt handling*/
    if ((ASRC->ASRSTR & (uint32_t)kASRC_StatusPairBInterrupt) != 0U)
    {
        s_asrcIsr(ASRC, s_asrcHandle[0][1U]);
    }
    /* channel PAIR C interrupt handling*/
    if ((ASRC->ASRSTR & (uint32_t)kASRC_StatusPairCInterrupt) != 0U)
    {
        s_asrcIsr(ASRC, s_asrcHandle[0][2U]);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif /* ASRC */
