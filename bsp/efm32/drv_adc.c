/***************************************************************************//**
 * @file    drv_adc.c
 * @brief   ADC driver of RT-Thread RTOS for EFM32
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-02-21   onelife     Initial creation for EFM32
 * 2011-07-14   onelife     Add multiple channels support for scan mode
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_adc.h"

#if defined(RT_USING_ADC0)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_ADC_DEBUG
#define adc_debug(format,args...)           rt_kprintf(format, ##args)
#else
#define adc_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
#ifdef RT_USING_ADC0
static struct rt_device adc0_device;
#endif
static rt_uint32_t adcErrataShift = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Calibrate offset and gain for the specified reference.
 *   Supports currently only single ended gain calibration.
 *   Could easily be expanded to support differential gain calibration.
 *
 * @details
 *   The offset calibration routine measures 0 V with the ADC, and adjust
 *   the calibration register until the converted value equals 0.
 *   The gain calibration routine needs an external reference voltage equal
 *   to the top value for the selected reference. For example if the 2.5 V
 *   reference is to be calibrated, the external supply must also equal 2.5V.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] ref
 *   Reference used during calibration. Can be both external and internal
 *   references.
 *
 * @param[in] input
 *   Input channel used during calibration.
 *
 * @return
 *   The final value of the calibration register, note that the calibration
 *   register gets updated with this value during the calibration.
 *   No need to load the calibration values after the function returns.
 ******************************************************************************/
rt_uint32_t efm32_adc_calibration(
    ADC_TypeDef             *adc,
    ADC_Ref_TypeDef         ref,
    ADC_SingleInput_TypeDef input)
{
    rt_uint32_t     cal;
    rt_int32_t      sample;
    rt_int8_t       high, mid, low, tmp;
    ADC_InitSingle_TypeDef singleInit   = ADC_INITSINGLE_DEFAULT;

    /* Init for single conversion use, measure diff 0 with selected reference. */
    singleInit.reference    = ref;
    singleInit.input        = adcSingleInpDiff0;
    singleInit.acqTime      = adcAcqTime32;
    singleInit.diff         = true;
    /* Enable oversampling rate */
    singleInit.resolution   = adcResOVS;
    ADC_InitSingle(adc, &singleInit);

    /* ADC is now set up for offset calibration */
    /* Offset calibration register is a 7 bit signed 2's complement value. */
    /* Use unsigned indexes for binary search, and convert when calibration */
    /* register is written to. */
    high = 63;
    low = -64;

    /* Do binary search for offset calibration*/
    while (low < high)
    {
        /* Calculate midpoint */
        mid = low + (high - low) / 2;

        /* Midpoint is converted to 2's complement and written to both scan and */
        /* single calibration registers */
        cal = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SCANOFFSET_MASK);
        tmp = mid < 0 ? (((mid & 0x3F) ^ 0x3F) | 0x40) + 1 : mid;
        cal |= tmp << _ADC_CAL_SINGLEOFFSET_SHIFT;
        cal |= tmp << _ADC_CAL_SCANOFFSET_SHIFT;
        adc_debug("adc->CAL = %x, cal = %x, tmp = %x\n", adc->CAL, cal, tmp);
        adc->CAL = cal;

        /* Do a conversion */
        ADC_Start(adc, adcStartSingle);

        /* Wait while conversion is active */
        while (adc->STATUS & ADC_STATUS_SINGLEACT) ;

        /* Get ADC result */
        sample = ADC_DataSingleGet(adc);

        /* Check result and decide in which part of to repeat search */
        /* Calibration register has negative effect on result */
        if (sample < 0)
        {
            /* Repeat search in bottom half. */
            high = mid;
        }
        else if (sample > 0)
        {
            /* Repeat search in top half. */
            low = mid + 1;
        }
        else
        {
            /* Found it, exit while loop */
            break;
        }
    }
    adc_debug("adc->CAL = %x\n", adc->CAL);

    /* Now do gain calibration, only input and diff settings needs to be changed */
    adc->SINGLECTRL &= ~(_ADC_SINGLECTRL_INPUTSEL_MASK | _ADC_SINGLECTRL_DIFF_MASK);
    adc->SINGLECTRL |= (input << _ADC_SINGLECTRL_INPUTSEL_SHIFT);
    adc->SINGLECTRL |= (false << _ADC_SINGLECTRL_DIFF_SHIFT);

    /* ADC is now set up for gain calibration */
    /* Gain calibration register is a 7 bit unsigned value. */
    high = 127;
    low = 0;

    /* Do binary search for gain calibration */
    while (low < high)
    {
        /* Calculate midpoint and write to calibration register */
        mid = low + (high - low) / 2;

        /* Midpoint is converted to 2's complement */
        cal      = adc->CAL & ~(_ADC_CAL_SINGLEGAIN_MASK | _ADC_CAL_SCANGAIN_MASK);
        cal     |= mid << _ADC_CAL_SINGLEGAIN_SHIFT;
        cal     |= mid << _ADC_CAL_SCANGAIN_SHIFT;
        adc_debug("adc->CAL = %x, cal = %x, mid = %x\n", adc->CAL, cal, mid);
        adc->CAL = cal;

        /* Do a conversion */
        ADC_Start(adc, adcStartSingle);

        /* Wait while conversion is active */
        while (adc->STATUS & ADC_STATUS_SINGLEACT) ;

        /* Get ADC result */
        sample = ADC_DataSingleGet(adc);

        /* Check result and decide in which part to repeat search */
        /* Compare with a value atleast one LSB's less than top to avoid overshooting */
        /* Since oversampling is used, the result is 16 bits, but a couple of lsb's */
        /* applies to the 12 bit result value, if 0xffe is the top value in 12 bit, this */
        /* is in turn 0xffe0 in the 16 bit result. */
        /* Calibration register has positive effect on result */
        if (sample > 0xffd0)
        {
          /* Repeat search in bottom half. */
          high = mid;
        }
        else if (sample < 0xffd0)
        {
          /* Repeat search in top half. */
          low = mid + 1;
        }
        else
        {
          /* Found it, exit while loop */
          break;
        }
    }
    adc_debug("adc->CAL = %x\n", adc->CAL);

    return adc->CAL;
}

/***************************************************************************//**
 * @brief
 *   Configure DMA for ADC
 *
 * @details
 *
 * @note
 *
 * @param[in] adc_device
 *   Pointer to ADC registers base address
 *
 * @param[in] mode
 *   ADC mode
 *
 * @param[in] channel
 *   DMA channel
 ******************************************************************************/
void efm32_adc_cfg_dma(
        ADC_TypeDef             *adc_device,
        rt_uint8_t              mode,
        rt_uint8_t              channel)
{
    DMA_CfgChannel_TypeDef  chnlCfg;
    DMA_CfgDescr_TypeDef    descrCfg;

    if (channel == (rt_uint8_t)EFM32_NO_DMA)
    {
        return;
    }

    /* Set up DMA channel */
    chnlCfg.highPri     = false;
    chnlCfg.enableInt   = false;
    if (adc_device == ADC0)
    {
        switch (mode & ADC_MASK_MODE)
        {
        case ADC_MODE_SINGLE:
            chnlCfg.select = DMAREQ_ADC0_SINGLE;
            break;

        case ADC_MODE_SCAN:
            chnlCfg.select = DMAREQ_ADC0_SCAN;
            break;

        default:
            return;
        }
    }
    else
    {
        // TODO: Any other channel?
        return;
    }
    chnlCfg.cb          = RT_NULL;
    DMA_CfgChannel((rt_uint32_t)channel, &chnlCfg);

    /* Setting up DMA channel descriptor */
    descrCfg.dstInc     = dmaDataInc4;
    descrCfg.srcInc     = dmaDataIncNone;
    descrCfg.size       = dmaDataSize4;
    descrCfg.arbRate    = dmaArbitrate1;
    descrCfg.hprot      = 0;
    DMA_CfgDescr((rt_uint32_t)channel, true, &descrCfg);
}

/***************************************************************************//**
 * @brief
 *   Activate DMA for ADC
 *
 * @details
 *
 * @note
 *
 * @param[in] adc_device
 *   Pointer to ADC registers base address
 *
 * @param[in] mode
 *   ADC mode
 *
 * @param[in] count
 *   ADC channel count
 *
 * @param[in] channel
 *   DMA channel
 *
 * @param[out] buffer
 *   Pointer to ADC results buffer
 ******************************************************************************/
void efm32_adc_on_dma(
        ADC_TypeDef             *adc_device,
        rt_uint8_t              mode,
        rt_uint8_t              count,
        rt_uint8_t              channel,
        void                    *buffer)
{
    switch (mode & ADC_MASK_MODE)
    {
    case ADC_MODE_SINGLE:
        /* Activate DMA */
        DMA_ActivateBasic(
            (rt_uint32_t)channel,
            true,
            false,
            buffer,
            (void *)&(adc_device->SINGLEDATA),
            count - 1);
        break;

    case ADC_MODE_SCAN:
        DMA_ActivateBasic(
            (rt_uint32_t)channel,
            true,
            false,
            buffer,
            (void *)&(adc_device->SCANDATA),
            count - 1);
        break;

    default:
        return;
    }
}

/***************************************************************************//**
 * @brief
 *   Initialize ADC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
 static rt_err_t rt_adc_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    rt_uint32_t temp;

    struct efm32_adc_device_t *adc;

    adc = (struct efm32_adc_device_t *)(dev->user_data);

    temp = efm32_adc_calibration(adc->adc_device, ADC_CALI_REF, ADC_CALI_CH);

    adc_debug("adc->CAL = %x\n", temp);
    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  Configure ADC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 *
 * @param[in] cmd
 *  ADC control command
 *
 * @param[in] args
 *  Arguments
 *
 * @return
 *  Error code
 ******************************************************************************/
static rt_err_t rt_adc_control(
    rt_device_t     dev,
    rt_uint8_t      cmd,
    void            *args)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_adc_device_t *adc;

    adc = (struct efm32_adc_device_t *)(dev->user_data);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* Suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        adc->adc_device->CMD = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;
        break;

    case RT_DEVICE_CTRL_RESUME:
        {
            /* Resume device */
            struct efm32_adc_result_t *control = \
                (struct efm32_adc_result_t *)args;

            dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;

            switch (control->mode)
            {
            case ADC_MODE_SINGLE:
                if (adc->singleDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                {
                    efm32_adc_on_dma(
                        adc->adc_device,
                        control->mode,
                        adc->singleCount,
                        adc->singleDmaChannel,
                        control->buffer);
                }
                ADC_Start(adc->adc_device, adcStartSingle);
                break;

            case ADC_MODE_SCAN:
                if (adc->scanDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                {
                    efm32_adc_on_dma(
                        adc->adc_device,
                        control->mode,
                        adc->scanCount,
                        adc->scanDmaChannel,
                        control->buffer);
                }
                ADC_Start(adc->adc_device, adcStartScan);
                break;

            case ADC_MODE_TAILGATE:
                {
                    void *index = control->buffer;

                    if (adc->scanDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                    {
                        efm32_adc_on_dma(
                            adc->adc_device,
                            control->mode,
                            adc->scanCount,
                            adc->scanDmaChannel,
                            index);
                        index += adc->scanCount;
                    }
                    if (adc->singleDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                    {
                        efm32_adc_on_dma(
                            adc->adc_device,
                            control->mode,
                            adc->singleCount,
                            adc->singleDmaChannel,
                            index);
                        index += adc->singleCount;
                    }
                    ADC_Start(adc->adc_device, adcStartScanAndSingle);
                }

                break;

            default:
                return -RT_ERROR;
            }
        }
        break;

    case RT_DEVICE_CTRL_ADC_MODE:
        {
            /* change device setting */
            struct efm32_adc_control_t *control = \
                (struct efm32_adc_control_t *)args;

            switch (control->mode)
            {
            case ADC_MODE_SINGLE:
                ADC_InitSingle(adc->adc_device, control->single.init);
                break;

            case ADC_MODE_SCAN:
                ADC_InitScan(adc->adc_device, control->scan.init);
                break;

            case ADC_MODE_TAILGATE:
                ADC_InitSingle(adc->adc_device, control->single.init);
                ADC_InitScan(adc->adc_device, control->scan.init);
                break;

            default:
                return -RT_ERROR;
            }

            if (control->mode == ADC_MODE_TAILGATE)
            {
                adc->mode = ADC_MODE_TAILGATE;
            }
            else
            {
                adc->mode &= ~(rt_uint8_t)ADC_MODE_TAILGATE;
                adc->mode |= control->mode;
            }
            if ((control->mode == ADC_MODE_TAILGATE) || \
                (control->mode == ADC_MODE_SINGLE))
            {
                if (control->single.init->rep)
                {
                    adc->mode |= ADC_OP_SINGLE_REPEAT;
                }
                adc->singleCount = control->single.count;
                adc->singleDmaChannel = control->single.dmaChannel;
                efm32_adc_cfg_dma(adc->adc_device, control->mode, adc->singleDmaChannel);
            }
            if ((control->mode == ADC_MODE_TAILGATE) || \
                (control->mode == ADC_MODE_SCAN))
            {
                if (control->scan.init->rep)
                {
                    adc->mode |= ADC_OP_SCAN_REPEAT;
                }
                adc->scanCount = control->scan.count;
                adc->scanDmaChannel = control->scan.dmaChannel;
                efm32_adc_cfg_dma(adc->adc_device, control->mode, adc->scanDmaChannel);
            }
        }
        break;

    case RT_DEVICE_CTRL_ADC_RESULT:
        {
            struct efm32_adc_result_t *control = \
                (struct efm32_adc_result_t *)args;

            switch (control->mode)
            {
            case ADC_MODE_SINGLE:
                if (adc->singleDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                {
                    if (adc->mode & ADC_OP_SINGLE_REPEAT)
                    {
                        if (!(DMA->IF & (1 << adc->singleDmaChannel)))
                        {
                            efm32_adc_on_dma(
                                adc->adc_device,
                                control->mode,
                                adc->singleCount,
                                adc->singleDmaChannel,
                                control->buffer);
                        }
                        while (!(DMA->IF & (1 << adc->singleDmaChannel)));
                    }
                    else
                    {
                        while (adc->adc_device->STATUS & ADC_STATUS_SINGLEACT);
                    }
                }
                else
                {
                    while (adc->adc_device->STATUS & ADC_STATUS_SINGLEACT);
                    *((rt_uint32_t *)control->buffer) = \
                        ADC_DataSingleGet(adc->adc_device) << adcErrataShift;
                }
                break;

            case ADC_MODE_SCAN:
                if (adc->scanDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                {
                    if (adc->mode & ADC_OP_SCAN_REPEAT)
                    {
                        if (!(DMA->IF & (1 << adc->scanDmaChannel)))
                        {
                            efm32_adc_on_dma(
                                adc->adc_device,
                                control->mode,
                                adc->scanCount,
                                adc->scanDmaChannel,
                                control->buffer);
                        }
                        while (!(DMA->IF & (1 << adc->scanDmaChannel)));
                    }
                    else
                    {
                        while (adc->adc_device->STATUS & ADC_STATUS_SCANACT);
                    }
                }
                else
                {
                    while (adc->adc_device->STATUS & ADC_STATUS_SCANACT);
                    *((rt_uint32_t *)control->buffer) = \
                        ADC_DataScanGet(adc->adc_device) << adcErrataShift;
                }
                break;

            case ADC_MODE_TAILGATE:
                {
                    void *index = control->buffer;

                    if ((adc->scanDmaChannel != (rt_uint8_t)EFM32_NO_DMA) && \
                        !(adc->mode & ADC_OP_SCAN_REPEAT))
                    {
                        index += adc->scanCount;
                    }
                    if ((adc->singleDmaChannel != (rt_uint8_t)EFM32_NO_DMA) && \
                        !(adc->mode & ADC_OP_SINGLE_REPEAT))
                    {
                        index += adc->singleCount;
                    }

                    if (adc->scanDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                    {
                        if (adc->mode & ADC_OP_SCAN_REPEAT)
                        {
                            if (!(DMA->IF & (1 << adc->scanDmaChannel)))
                            {
                                efm32_adc_on_dma(
                                    adc->adc_device,
                                    control->mode,
                                    adc->scanCount,
                                    adc->scanDmaChannel,
                                    index);
                                index += adc->scanCount;
                            }
                            while (!(DMA->IF & (1 << adc->scanDmaChannel)));
                        }
                        else
                        {
                            while (adc->adc_device->STATUS & ADC_STATUS_SCANACT);
                        }
                    }
                    else
                    {
                        while (adc->adc_device->STATUS & ADC_STATUS_SCANACT);
                        *(rt_uint32_t *)(index++) = \
                            ADC_DataScanGet(adc->adc_device) << adcErrataShift;
                    }
                    if (adc->singleDmaChannel != (rt_uint8_t)EFM32_NO_DMA)
                    {
                        if (adc->mode & ADC_OP_SINGLE_REPEAT)
                        {
                            if (!(DMA->IF & (1 << adc->singleDmaChannel)))
                            {
                                efm32_adc_on_dma(
                                    adc->adc_device,
                                    control->mode,
                                    adc->singleCount,
                                    adc->singleDmaChannel,
                                    index);
                                index += adc->singleCount;
                            }
                            while (!(DMA->IF & (1 << adc->singleDmaChannel)));
                        }
                        else
                        {
                            while (adc->adc_device->STATUS & ADC_STATUS_SINGLEACT);
                        }
                    }
                    else
                    {
                        while (adc->adc_device->STATUS & ADC_STATUS_SINGLEACT);
                        *(rt_uint32_t *)(index++) = \
                            ADC_DataSingleGet(adc->adc_device) << adcErrataShift;
                    }
                }
                break;

            default:
                return -RT_ERROR;
            }
        }
        break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  Register ADC device
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 *
 * @param[in] name
 *  Device name
 *
 * @param[in] flag
 *  Configuration flags
 *
 * @param[in] adc
 *  Pointer to ADC device descriptor
 *
 * @return
 *  Error code
 ******************************************************************************/
rt_err_t rt_hw_adc_register(
    rt_device_t     device,
    const char      *name,
    rt_uint32_t     flag,
    struct efm32_adc_device_t *adc)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char; /* fixme: should be adc type */
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_adc_init;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_adc_control;
    device->user_data   = adc;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

/***************************************************************************//**
 * @brief
 *  Initialize the specified ADC unit
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 *
 * @param[in] unitNumber
 *  Unit number
 *
 * @return
 *  Pointer to ADC device
 ******************************************************************************/
static struct efm32_adc_device_t *rt_hw_adc_unit_init(
    rt_device_t device,
    rt_uint8_t  unitNumber)
{
    struct efm32_adc_device_t       *adc;
    CMU_Clock_TypeDef               adcClock;
    ADC_Init_TypeDef                init = ADC_INIT_DEFAULT;

    do
    {
        /* Allocate device and set default value */
        adc = rt_malloc(sizeof(struct efm32_adc_device_t));
        if (adc == RT_NULL)
        {
            adc_debug("no memory for ADC%d driver\n", unitNumber);
            break;
        }
        adc->mode               = 0;
        adc->singleCount        = 0;
        adc->singleDmaChannel   = (rt_uint8_t)EFM32_NO_DMA;
        adc->scanCount          = 0;
        adc->scanDmaChannel     = (rt_uint8_t)EFM32_NO_DMA;

        /* Initialization */
        if (unitNumber >= ADC_COUNT)
        {
            break;
        }
        switch (unitNumber)
        {
        case 0:
            adc->adc_device     = ADC0;
            adcClock            = (CMU_Clock_TypeDef)cmuClock_ADC0;
            break;

        default:
            break;
        }

        /* Enable ADC clock */
        CMU_ClockEnable(adcClock, true);

        /* Reset */
        ADC_Reset(adc->adc_device);

        /* Configure ADC */
        // TODO: Fixed oversampling rate?
        init.ovsRateSel         = adcOvsRateSel4096;
        init.timebase           = ADC_TimebaseCalc(0);
        init.prescale           = ADC_PrescaleCalc(ADC_CONVERT_FREQUENCY, 0);
        ADC_Init(adc->adc_device, &init);

        return adc;
    } while(0);

    if (adc)
    {
        rt_free(adc);
    }
    rt_kprintf("ADC: Init failed!\n");
    return RT_NULL;
}

/***************************************************************************//**
 * @brief
 *  Initialize all ADC module related hardware and register ADC device to kernel
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void rt_hw_adc_init(void)
{
    SYSTEM_ChipRevision_TypeDef chipRev;
    struct efm32_adc_device_t   *adc;

#ifdef RT_USING_ADC0
    if ((adc = rt_hw_adc_unit_init(&adc0_device, 0)) != RT_NULL)
    {
        rt_hw_adc_register(&adc0_device, RT_ADC0_NAME, EFM32_NO_DATA, adc);
    }
#endif

    /* ADC errata for rev B when using VDD as reference, need to multiply */
    /* result by 2 */
    SYSTEM_ChipRevisionGet(&chipRev);
    if ((chipRev.major == 0x01) && (chipRev.minor == 0x01))
    {
      adcErrataShift = 1;
    }
}

#endif
/***************************************************************************//**
 * @}
 ******************************************************************************/
