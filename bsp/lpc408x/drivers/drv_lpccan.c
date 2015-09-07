/*
 * File      : drv_lpccan.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author                Notes
 * 2015-06-30     aubrcool@qq.com       first version
 * 2015-07-10     aozima@rt-thread.com  add CAN2 driver.
 */
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_lpccan.h>
#ifdef RT_USING_COMPONENTS_INIT
#include <components.h>
#endif

#ifdef RT_USING_CAN

#include "lpc_types.h"
#include "lpc_can.h"
#include "lpc_pinsel.h"
#include "lpc_exti.h"
#include "lpc_clkpwr.h"

#define MAXLPCHDR 1024

static struct rt_can_device *lpccanid2dev(en_CAN_unitId id);

static struct rt_can_hdr lpccanhdr[MAXLPCHDR] =
{
    {0,},
};
static struct rt_mutex lpcfilterlock;

#define LPCFILTERLOCK()     rt_mutex_take(&lpcfilterlock, RT_WAITING_FOREVER)
#define LPCFILTERUNLOCK()   rt_mutex_release(&lpcfilterlock)
struct lpccandata
{
    en_CAN_unitId id;
};

static LPC_CAN_TypeDef  *lcpcan_get_reg_base(rt_uint32_t id)
{
    LPC_CAN_TypeDef *pCan;

    switch (id)
    {
    case CAN_ID_1:
        pCan = LPC_CAN1;
        break;

    case CAN_ID_2:
        pCan = LPC_CAN2;
        break;
    default:
        pCan = NULL;
    }
    return pCan;
}

static void lpccan_irqstate_init(rt_uint32_t id)
{
    LPC_CAN_TypeDef *pCan = lcpcan_get_reg_base(id);
    volatile rt_int32_t i;

    pCan->MOD = 1; // Enter Reset Mode
    pCan->IER = 0; // Disable All CAN Interrupts
    pCan->GSR = 0;

    /* Request command to release Rx, Tx buffer and clear data overrun */
    //pCan->CMR = CAN_CMR_AT | CAN_CMR_RRB | CAN_CMR_CDO;
    pCan->CMR = (1 << 1) | (1 << 2) | (1 << 3);

    /* Read to clear interrupt pending in interrupt capture register */
    i = pCan->ICR;
    i = i;

    pCan->MOD = 0;// Return Normal operating
}

static rt_err_t lpccan_baud_set(rt_uint32_t id, rt_uint32_t baud)
{
    uint32_t result = 0;
    uint8_t NT, TSEG1, TSEG2;
    uint32_t CANPclk = 0;
    uint32_t BRP;
    LPC_CAN_TypeDef *pCan = lcpcan_get_reg_base(id);

    CANPclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);
    result = CANPclk / baud;

    /* Calculate suitable nominal time value
     * NT (nominal time) = (TSEG1 + TSEG2 + 3)
     * NT <= 24
     * TSEG1 >= 2*TSEG2
     */
    for (NT = 24; NT > 0; NT = NT - 2)
    {
        if ((result % NT) == 0)
        {
            BRP = result / NT - 1;
            NT--;
            TSEG2 = (NT / 3) - 1;
            TSEG1 = NT - (NT / 3) - 1;
            break;
        }
    }

    /* Enter reset mode */
    pCan->MOD = 0x01;
    /* Set bit timing
     * Default: SAM = 0x00;
     *          SJW = 0x03;
     */
    pCan->BTR = (TSEG2 << 20) | (TSEG1 << 16) | (3 << 14) | BRP;
    /* Return to normal operating */
    pCan->MOD = 0;

    return RT_EOK;
}

static void lpccan_init_alut_ram(void)
{
    //Reset CANAF value
    LPC_CANAF->AFMR = 0x01;
    //clear ALUT RAM
    rt_memset((void *)LPC_CANAF_RAM->mask, 0, 2048);
    LPC_CANAF->SFF_sa = 0;
    LPC_CANAF->SFF_GRP_sa = 0;
    LPC_CANAF->EFF_sa = 0;
    LPC_CANAF->EFF_GRP_sa = 0;
    LPC_CANAF->ENDofTable = 0;
    LPC_CANAF->AFMR = 0x00;
    // Set AF Mode
    CAN_SetAFMode(CAN_NORMAL);
}

#ifdef RT_USING_LPCCAN1
static void lpccan1_filter_init(struct rt_can_device *can)
{
}

static void lpccan1_hw_init(uint32_t baud, CAN_MODE_Type mode)
{
    if (mode != CAN_SELFTEST_MODE)
    {
#ifndef LPCCAN1_USEING_GPIO_SECOND
        PINSEL_ConfigPin(0, 0, 1);
        PINSEL_ConfigPin(0, 1, 1);
#else
        PINSEL_ConfigPin(0, 21, 4);
        PINSEL_ConfigPin(0, 22, 4);
#endif
    }

    lpccan_irqstate_init(CAN_1);
    lpccan_init_alut_ram();
    lpccan_baud_set(CAN_1, baud);
    CAN_ModeConfig(CAN_1, mode, ENABLE);
    if (mode == CAN_SELFTEST_MODE)
    {
        //CAN_ModeConfig(CAN_1, CAN_TEST_MODE, ENABLE);
        CAN_SetAFMode(CAN_ACC_BP);
    }
}
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
static void lpccan2_filter_init(struct rt_can_device *can)
{
}

static void lpccan2_hw_init(uint32_t baud,  CAN_MODE_Type mode)
{
    if (mode != CAN_SELFTEST_MODE)
    {
#ifndef LPCCAN2_USEING_GPIO_SECOND
        PINSEL_ConfigPin(0, 4, 2);
        PINSEL_ConfigPin(0, 5, 2);
#else
        PINSEL_ConfigPin(2, 7, 1);
        PINSEL_ConfigPin(2, 8, 1);
#endif
    }

    lpccan_irqstate_init(CAN_2);
#ifndef RT_USING_LPCCAN1
    lpccan_init_alut_ram();
#endif /*RT_USING_LPCCAN1*/
    lpccan_baud_set(CAN_2, baud);
    CAN_ModeConfig(CAN_2, mode, ENABLE);
    if (mode == CAN_SELFTEST_MODE)
    {
        CAN_SetAFMode(CAN_ACC_BP);
    }
}
#endif /*RT_USING_LPCCAN2*/

static rt_err_t configure(struct rt_can_device *can, struct can_configure *cfg)
{
    CAN_MODE_Type mode;
    rt_uint32_t canid;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        mode = CAN_OPERATING_MODE;
        break;
    case RT_CAN_MODE_LISEN:
        mode = CAN_LISTENONLY_MODE;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        mode = CAN_SELFTEST_MODE;
        break;
    default:
        return RT_EIO;
    }

    canid = ((struct lpccandata *) can->parent.user_data)->id;
#ifdef RT_USING_LPCCAN1
    if (canid == CAN_1)
    {
        lpccan1_hw_init(cfg->baud_rate, mode);
        lpccan1_filter_init(can);
    }
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
    if (canid == CAN_2)
    {
        lpccan2_hw_init(cfg->baud_rate, mode);
        lpccan2_filter_init(can);
    }
#endif /*RT_USING_LPCCAN2*/

    return RT_EOK;
}
//the can filter data struct
//in current version we don't use fullcanmode
//so we always set fullcancnt 0
static struct
{
    rt_uint16_t fullcancnt;
    rt_uint16_t af_std_cnt;
    rt_uint16_t af_gstd_cnt;
    rt_uint16_t af_ext_cnt;
    rt_uint16_t af_gext_cnt;
}   lpccan_filterdata =
{
    0,
};
static rt_bool_t std_lesser(void *val1, void *val2)
{
    return (*((rt_uint32_t *) val1) < * ((rt_uint32_t *) val2));
}
rt_bool_t std_greater(void *val1, void *val2)
{
    return (*((rt_uint32_t *) val1) > *((rt_uint32_t *) val2));
}
static rt_bool_t std_getval(volatile void *base, rt_int32_t index, void *val)
{
    if (index & 0x01)
    {
        *(rt_uint32_t *)val = ((rt_uint32_t *)base)[index >> 1] & 0x0000E7FF;
    }
    else
    {
        *(rt_uint32_t *)val = (((rt_uint32_t *)base)[index >> 1] >> 16) & 0x0000E7FF;
    }
    return RT_TRUE;
}
static rt_bool_t std_setval(volatile void *base, rt_int32_t index, void *val)
{
    rt_uint32_t swpval;
    if (index & 0x01)
    {
        swpval = ((rt_uint32_t *)base)[index >> 1] & 0x0000E7FF;
        ((rt_uint32_t *)base)[index >> 1] &= ~ 0x0000FFFF;
        ((rt_uint32_t *)base)[index >> 1] |= (*(rt_uint32_t *)val) & 0x0000FFFF;
        *(rt_uint32_t *)val = swpval;
    }
    else
    {
        swpval = (((rt_uint32_t *)base)[index >> 1] >> 16) & 0x0000E7FF;
        ((rt_uint32_t *)base)[index >> 1] &= ~ 0xFFFF0000;
        ((rt_uint32_t *)base)[index >> 1] |= ((*(rt_uint32_t *)val) & 0x0000FFFF) << 16;
        *(rt_uint32_t *)val = swpval;
    }
    return RT_TRUE;
}
static rt_uint32_t std_data;
static rt_bool_t gstd_lesser(void *val1, void *val2)
{
    return (((*(rt_uint32_t *) val2) >> 16) & 0xE7FF) > ((*(rt_uint32_t *) val1) & 0xE7FF);
}
static rt_bool_t gstd_greater(void *val1, void *val2)
{
    return (((*(rt_uint32_t *) val1) >> 16) & 0xE7FF) > ((*(rt_uint32_t *) val2) & 0xE7FF);
}
static rt_bool_t gstd_getval(volatile void *base, rt_int32_t index, void *val)
{
    *(rt_uint32_t *)val = ((rt_uint32_t *)base)[index];
    return RT_TRUE;
}
static rt_bool_t gstd_setval(volatile void *base, rt_int32_t index, void *val)
{
    rt_uint32_t swpval;
    swpval = ((rt_uint32_t *)base)[index];
    ((rt_uint32_t *)base)[index] = *(rt_uint32_t *)val;
    *(rt_uint32_t *)val = swpval;
    return RT_TRUE;
}
static rt_uint32_t gstd_data;
static rt_bool_t ext_lesser(void *val1, void *val2)
{
    return std_lesser(val1, val2);
}
static rt_bool_t ext_greater(void *val1, void *val2)
{
    return std_greater(val1, val2);
}
static rt_bool_t ext_getval(volatile void *base, rt_int32_t index, void *val)
{
    *(rt_uint32_t *)val = ((rt_uint32_t *)base)[index];
    return RT_TRUE;
}
static rt_bool_t ext_setval(volatile void *base, rt_int32_t index, void *val)
{
    rt_uint32_t swpval;
    swpval = ((rt_uint32_t *)base)[index];
    ((rt_uint32_t *)base)[index] = *(rt_uint32_t *)val;
    *(rt_uint32_t *)val = swpval;
    return RT_TRUE;
}
static rt_uint32_t ext_data;
static rt_bool_t gext_lesser(void *val1, void *val2)
{
    return ((rt_uint32_t *) val2)[0] > ((rt_uint32_t *) val1)[1];
}
static rt_bool_t gext_greater(void *val1, void *val2)
{
    return ((rt_uint32_t *) val1)[0] > ((rt_uint32_t *) val2)[1];
}
static rt_bool_t gext_getval(volatile void *base, rt_int32_t index, void *val)
{
    ((rt_uint32_t *) val)[0] = ((rt_uint32_t *)base)[2 * index + 0];
    ((rt_uint32_t *) val)[1] = ((rt_uint32_t *)base)[2 * index + 1];
    return RT_TRUE;
}
static rt_bool_t gext_setval(volatile void *base, rt_int32_t index, void *val)
{
    rt_uint32_t swpval[2];
    swpval[0] = ((rt_uint32_t *)base)[2 * index + 0];
    swpval[1] = ((rt_uint32_t *)base)[2 * index + 1];
    ((rt_uint32_t *)base)[2 * index + 0] = ((rt_uint32_t *)val)[0];
    ((rt_uint32_t *)base)[2 * index + 1] = ((rt_uint32_t *)val)[1];
    ((rt_uint32_t *)val)[0] = swpval[0];
    ((rt_uint32_t *)val)[1] = swpval[1];
    return RT_TRUE;
}
static rt_uint32_t gext_data[2];
static const struct lpccanfilteralgorithm
{
    rt_bool_t (*lesser)(void *val1, void *val2);
    rt_bool_t (*greater)(void *val1, void *val2);
    rt_bool_t (*getval)(volatile void *base, rt_int32_t index, void *val);
    rt_bool_t (*setval)(volatile void *base, rt_int32_t index, void *val);
    void *data;
}   lpccanfilteralgorithms[4] = //4 section algorithm
{
    {
        std_lesser,
        std_greater,
        std_getval,
        std_setval,
        &std_data,
    },
    {
        gstd_lesser,
        gstd_greater,
        gstd_getval,
        gstd_setval,
        &gstd_data,
    },
    {
        ext_lesser,
        ext_greater,
        ext_getval,
        ext_setval,
        &ext_data,
    },
    {
        gext_lesser,
        gext_greater,
        gext_getval,
        gext_setval,
        &gext_data,
    },
};
#define LPCCAN_FILTER_NOTEXIST          -1
#define LPCCAN_FILTER_CANNOTINSERT      -2
#define LPCCAN_FILTER_GRPINVALID        -3
#define LPCCAN_OK                        0
static rt_int32_t bisearchfilter
(
    const struct lpccanfilteralgorithm *algorithm,
    volatile void *base,
    rt_uint32_t cnt,
    void *data,
    rt_int32_t *insertoff
)
{
    rt_int32_t begin, end, mid;
    *insertoff = -1;
    if (cnt != 0)
    {
        begin = 0;
        end = cnt - 1;
        while (begin < end)
        {
            mid = (begin + end) >> 1;
            algorithm->getval(base, mid, algorithm->data);
            if (algorithm->greater(algorithm->data, data))
            {
                end = mid - 1;
                continue;
            }
            else if (algorithm->lesser(algorithm->data, data))
            {
                begin = mid + 1;
                continue;
            }
            else
            {
                *insertoff = mid;
                return LPCCAN_OK;
            }
        }
        algorithm->getval(base, begin, algorithm->data);
        if (algorithm->greater(algorithm->data, data))
        {
            *insertoff = begin;
        }
        else if (algorithm->lesser(algorithm->data, data))
        {
            *insertoff = begin + 1;
        }
        else
        {
            *insertoff = begin;
            return LPCCAN_OK;
        }
    }
    else
    {
        *insertoff = 0;
    }
    return LPCCAN_FILTER_NOTEXIST;
}
static inline int gethdrtype(struct rt_can_filter_item *pitem)
{
    return (pitem->mode | (pitem->ide << 1));
    //0 std
    //1 std group
    //2 ext
    //3 ext group
}
static inline volatile uint32_t *gethdrbase(rt_int32_t type)
{
    int index;
    switch (type)
    {
    case 0:
        index = (lpccan_filterdata.fullcancnt + 1) >> 1;
        break;
    case 1:
        index = ((lpccan_filterdata.fullcancnt + 1) >> 1) +
                ((lpccan_filterdata.af_std_cnt + 1) >> 1);
        break;
    case 2:
        index = ((lpccan_filterdata.fullcancnt + 1) >> 1) +
                ((lpccan_filterdata.af_std_cnt + 1) >> 1) +
                lpccan_filterdata.af_gstd_cnt;
        break;
    case 3:
        index = ((lpccan_filterdata.fullcancnt + 1) >> 1) +
                ((lpccan_filterdata.af_std_cnt + 1) >> 1) +
                lpccan_filterdata.af_gstd_cnt +
                lpccan_filterdata.af_ext_cnt;
        break;
    }
    return &LPC_CANAF_RAM->mask[index];
}
static rt_int32_t findfilter
(
    struct lpccandata *plpccan,
    struct rt_can_filter_item *pitem,
    rt_int32_t *pos
)
{
    rt_uint32_t result;
    *pos = -1;
    rt_uint32_t canid = plpccan->id;
    rt_uint32_t filterdata[2];
    rt_int32_t cnt;
    rt_int32_t type = gethdrtype(pitem);
    switch (type)
    {
    case 0:
        filterdata[0] = pitem->id | (canid << 13);
        cnt = lpccan_filterdata.af_std_cnt;
        break;
    case 1:
        filterdata[0] = (pitem->id << 16) | (pitem->mask) | (canid << 13) | (canid << 29);
        cnt = lpccan_filterdata.af_gstd_cnt;
        break;
    case 2:
        filterdata[0] = pitem->id | (canid << 29);
        cnt = lpccan_filterdata.af_ext_cnt;
        break;
    case 3:
        filterdata[0] = pitem->id | (canid << 29);
        filterdata[1] = pitem->mask | (canid << 29);
        cnt = lpccan_filterdata.af_gext_cnt;
        break;
    }
    result = bisearchfilter
             (
                 &lpccanfilteralgorithms[type],
                 gethdrbase(type),
                 cnt,
                 filterdata,
                 pos
             );
    if (!(type & 1) || result != LPCCAN_OK)
    {
        return result;
    }
    lpccanfilteralgorithms[type].getval
    (
        gethdrbase(type),
        *pos,
        lpccanfilteralgorithms[type].data
    );
    if (type == 1)
    {
        if ((*((rt_uint32_t *)lpccanfilteralgorithms[1].data) & 0xE7FFE7FF) == filterdata[0])
        {
            return LPCCAN_OK;
        }
        else
        {
            return LPCCAN_FILTER_CANNOTINSERT;
        }
    }
    else
    {
        if (((rt_uint32_t *)lpccanfilteralgorithms[3].data)[0] == filterdata[0] &&
                ((rt_uint32_t *)lpccanfilteralgorithms[3].data)[1] == filterdata[1])
        {
            return LPCCAN_OK;
        }
        else
        {
            return LPCCAN_FILTER_CANNOTINSERT;
        }
    }
    return LPCCAN_OK;
}
static void lpcmovehdr(struct lpccandata *plpccan, rt_int32_t dest, rt_int32_t src)
{
    struct rt_can_device *pcan;
    struct rt_can_hdr *phdrhead = lpccanhdr;
    rt_memmove(&phdrhead[dest].filter, &phdrhead[src].filter, sizeof(phdrhead[0].filter));
    if (phdrhead[dest].msgs)
    {
        pcan = lpccanid2dev(plpccan->id);
        if (pcan && phdrhead[dest].filter.ind)
        {
            phdrhead[dest].filter.ind((rt_device_t) pcan, phdrhead[dest].filter.args, dest,
                                      sizeof(struct rt_can_msg) * phdrhead[dest].msgs);
        }
    }
}
static rt_err_t setfilter(struct lpccandata *plpccan, struct rt_can_filter_config *pconfig)
{
    struct rt_can_filter_item *pitem = pconfig->items;
    rt_uint32_t count = pconfig->count, swaped[2], endpos, canid, beginpos;
    volatile uint32_t *movebegin, *moveend;
    rt_int32_t result, pos, type;
    struct rt_can_hdr *phdrhead = lpccanhdr;
    LPCFILTERLOCK();
    while (count)
    {
        result = findfilter(plpccan, pitem, &pos);

        if (result == LPCCAN_FILTER_NOTEXIST && pconfig->actived)
        {
            //need to insert this filter
            type = gethdrtype(pitem);
            LPC_CANAF->AFMR = 0x01;
            canid = plpccan->id;
            switch (type)
            {
            case 0:
                if (!(lpccan_filterdata.af_std_cnt & 0x01))
                {
                    //move the other section
                    movebegin = gethdrbase(1);
                    moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt;
                    while (moveend > movebegin)
                    {
                        *moveend = *(moveend - 1);
                        moveend --;
                    }
                    LPC_CANAF->SFF_GRP_sa += 0x04;
                    LPC_CANAF->EFF_sa     += 0x04;
                    LPC_CANAF->EFF_GRP_sa += 0x04;
                    LPC_CANAF->ENDofTable += 0x04;
                }
                movebegin = gethdrbase(type);
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = endpos; i > pos; i--)
                {
                    lpcmovehdr(plpccan, i, i - 1);
                }
                rt_memcpy(&phdrhead[pos].filter, pitem, sizeof(phdrhead[pos].filter));
                phdrhead[pos].connected = 1;
                swaped[0] =  pitem->id | (canid << 13);
                lpccan_filterdata.af_std_cnt++;
                endpos = lpccan_filterdata.af_std_cnt;
                while (pos < endpos) //insert new filter
                {
                    lpccanfilteralgorithms[type].setval(movebegin, pos, swaped);
                    pos++;
                }
                if (lpccan_filterdata.af_std_cnt & 1)
                {
                    swaped[0] = 0xFFFF;
                    lpccanfilteralgorithms[type].setval(movebegin, pos, swaped);
                }
                break;
            case 1:
                movebegin = &gethdrbase(type)[pos];
                moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt;
                while (moveend > movebegin)
                {
                    *moveend = *(moveend - 1);
                    moveend --;
                }
                LPC_CANAF->EFF_sa     += 0x04;
                LPC_CANAF->EFF_GRP_sa += 0x04;
                LPC_CANAF->ENDofTable += 0x04;
                swaped[0] = (pitem->id << 16) | (pitem->mask) | (canid << 13) | (canid << 29);
                lpccanfilteralgorithms[type].setval(movebegin, 0, swaped);
                beginpos = lpccan_filterdata.af_std_cnt + pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = endpos; i > beginpos; i--)
                {
                    lpcmovehdr(plpccan, i, i - 1);
                }
                rt_memcpy(&phdrhead[beginpos].filter, pitem, sizeof(phdrhead[beginpos].filter));
                phdrhead[beginpos].connected = 1;
                lpccan_filterdata.af_gstd_cnt++;
                break;
            case 2:
                movebegin = &gethdrbase(type)[pos];
                moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt;
                while (moveend > movebegin)
                {
                    *moveend = *(moveend - 1);
                    moveend --;
                }
                LPC_CANAF->EFF_GRP_sa += 0x04;
                LPC_CANAF->ENDofTable += 0x04;
                swaped[0] =  pitem->id | (canid << 29);
                lpccanfilteralgorithms[type].setval(movebegin, 0, swaped);
                beginpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt + pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = endpos; i > beginpos; i--)
                {
                    lpcmovehdr(plpccan, i, i - 1);
                }
                rt_memcpy(&phdrhead[beginpos].filter, pitem, sizeof(phdrhead[beginpos].filter));
                phdrhead[beginpos].connected = 1;
                lpccan_filterdata.af_ext_cnt++;
                break;
            case 3:
                movebegin = &gethdrbase(type)[pos * 2];
                moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt;
                while (moveend >= movebegin)
                {
                    *(moveend + 2) = *(moveend);
                    moveend --;
                }
                LPC_CANAF->ENDofTable += 0x08;
                swaped[0] =  pitem->id | (canid << 29);
                swaped[1] =  pitem->mask | (canid << 29);
                lpccanfilteralgorithms[type].setval(movebegin, 0, swaped);
                beginpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                           lpccan_filterdata.af_ext_cnt + pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = endpos; i > beginpos; i--)
                {
                    lpcmovehdr(plpccan, i, i - 1);
                }
                rt_memcpy(&phdrhead[beginpos].filter, pitem, sizeof(phdrhead[beginpos].filter));
                phdrhead[beginpos].connected = 1;
                lpccan_filterdata.af_gext_cnt++;
                break;
            }
            LPC_CANAF->AFMR = 0x00; // Normal mode
        }
        else if (result == LPCCAN_OK && !pconfig->actived)
        {
            //need to delete this filter
            type = gethdrtype(pitem);
            LPC_CANAF->AFMR = 0x01;
            switch (type)
            {
            case 0:
                movebegin = gethdrbase(type);
                beginpos = pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = beginpos; i < endpos; i++)
                {
                    lpcmovehdr(plpccan, i, i + 1);
                }
                while (!rt_list_isempty(&phdrhead[endpos].list))
                {
                    rt_list_remove(phdrhead[endpos].list.next);
                }
                rt_memset(&phdrhead[endpos].filter, 0, sizeof(phdrhead[0].filter));
                lpccan_filterdata.af_std_cnt--;
                endpos = lpccan_filterdata.af_std_cnt;
                lpccanfilteralgorithms[type].getval(movebegin, endpos, swaped);
                while (pos < endpos) //insert new filter
                {
                    lpccanfilteralgorithms[type].setval(movebegin, endpos - 1, swaped);
                    endpos--;
                }
                if (!(lpccan_filterdata.af_std_cnt & 0x01))
                {
                    //move the other section
                    movebegin = gethdrbase(1);
                    moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt;
                    while (moveend > movebegin)
                    {
                        *movebegin = *(movebegin + 1);
                        movebegin++;
                    }
                    *moveend = 0;
                    LPC_CANAF->SFF_GRP_sa -= 0x04;
                    LPC_CANAF->EFF_sa     -= 0x04;
                    LPC_CANAF->EFF_GRP_sa -= 0x04;
                    LPC_CANAF->ENDofTable -= 0x04;
                }
                else
                {
                    swaped[0] = 0xFFFF;
                    lpccanfilteralgorithms[type].setval(movebegin, lpccan_filterdata.af_std_cnt, swaped);
                }
                break;
            case 1:
                movebegin = &gethdrbase(type)[pos];
                moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt - 1;
                while (moveend > movebegin)
                {
                    *movebegin = *(movebegin + 1);
                    movebegin++;
                }
                *moveend = 0;
                LPC_CANAF->EFF_sa     -= 0x04;
                LPC_CANAF->EFF_GRP_sa -= 0x04;
                LPC_CANAF->ENDofTable -= 0x04;
                beginpos = lpccan_filterdata.af_std_cnt + pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = beginpos; i < endpos; i++)
                {
                    lpcmovehdr(plpccan, i, i + 1);
                }
                while (!rt_list_isempty(&phdrhead[endpos].list))
                {
                    rt_list_remove(phdrhead[endpos].list.next);
                }
                rt_memset(&phdrhead[endpos].filter, 0, sizeof(phdrhead[0].filter));
                lpccan_filterdata.af_gstd_cnt--;
                break;
            case 2:
                movebegin = &gethdrbase(type)[pos];
                moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt;
                while (moveend > movebegin)
                {
                    *movebegin = *(movebegin + 1);
                    movebegin++;
                }
                *moveend = 0;
                LPC_CANAF->EFF_GRP_sa -= 0x04;
                LPC_CANAF->ENDofTable -= 0x04;
                beginpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                           lpccan_filterdata.af_ext_cnt + pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = beginpos; i < endpos; i++)
                {
                    lpcmovehdr(plpccan, i, i + 1);
                }
                while (!rt_list_isempty(&phdrhead[endpos].list))
                {
                    rt_list_remove(phdrhead[endpos].list.next);
                }
                rt_memset(&phdrhead[endpos].filter, 0, sizeof(phdrhead[0].filter));
                lpccan_filterdata.af_ext_cnt--;
                break;
            case 3:
                movebegin = &gethdrbase(type)[pos * 2];
                moveend = gethdrbase(3) + 2 * lpccan_filterdata.af_gext_cnt - 1;
                while (moveend >= movebegin)
                {
                    *movebegin = *(movebegin + 2);
                    movebegin++;
                }
                *moveend = 0;
                *(moveend + 1) = 0;
                LPC_CANAF->ENDofTable -= 0x08;
                beginpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                           lpccan_filterdata.af_ext_cnt + pos;
                endpos = lpccan_filterdata.af_std_cnt + lpccan_filterdata.af_gstd_cnt +
                         lpccan_filterdata.af_ext_cnt + lpccan_filterdata.af_gext_cnt;
                for (int i = beginpos; i < endpos; i++)
                {
                    lpcmovehdr(plpccan, i, i + 1);
                }
                while (!rt_list_isempty(&phdrhead[endpos].list))
                {
                    rt_list_remove(phdrhead[endpos].list.next);
                }
                rt_memset(&phdrhead[endpos].filter, 0, sizeof(phdrhead[0].filter));
                lpccan_filterdata.af_gext_cnt--;
                break;
            }
            LPC_CANAF->AFMR = 0x00; // Normal mode
        }
        pitem++;
        count--;
    }
    LPCFILTERUNLOCK();
    return RT_EOK;
}

static rt_err_t control(struct rt_can_device *can, int cmd, void *arg)
{
    struct lpccandata *plpccan;
    rt_uint32_t argval;
    rt_base_t level;
    CAN_MODE_Type mode;

    plpccan = (struct lpccandata *)  can->parent.user_data;
    RT_ASSERT(plpccan != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_RIE, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_DOIE, DISABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_TIE1, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE2, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE3, DISABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_IRQCmd(plpccan->id, CANINT_EIE, DISABLE);
            CAN_IRQCmd(plpccan->id, CANINT_BEIE, DISABLE);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_RIE, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_DOIE, ENABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            CAN_IRQCmd(plpccan->id, CANINT_TIE1, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE2, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_TIE3, ENABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            CAN_IRQCmd(plpccan->id, CANINT_EIE, ENABLE);
            CAN_IRQCmd(plpccan->id, CANINT_BEIE, ENABLE);
        }
        break;

    case RT_CAN_CMD_SET_FILTER:
        return setfilter(plpccan, (struct rt_can_filter_config *) arg);

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL ||
                argval != RT_CAN_MODE_LISEN)
        {
            return RT_ERROR;
        }
        if (argval != can->config.mode)
        {
            can->config.mode = argval;
            switch (argval)
            {
            case RT_CAN_MODE_NORMAL:
                mode = CAN_OPERATING_MODE;
                break;
            case RT_CAN_MODE_LISEN:
                mode = CAN_LISTENONLY_MODE;
                break;
            case RT_CAN_MODE_LOOPBACKANLISEN:
                mode = CAN_SELFTEST_MODE;
                break;
            default:
                return RT_EIO;
            }
            CAN_ModeConfig(plpccan->id, mode, ENABLE);
            if (mode == CAN_SELFTEST_MODE)
            {
                //CAN_ModeConfig(CAN_1, CAN_TEST_MODE, ENABLE);
                CAN_SetAFMode(CAN_ACC_BP);
            }
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != can->config.baud_rate)
        {
            can->config.baud_rate = argval;
            level = rt_hw_interrupt_disable();
            if (can->parent.ref_count)
            {
                rt_hw_interrupt_enable(level);
                return lpccan_baud_set(plpccan->id, (rt_uint32_t) arg);
            }
            rt_hw_interrupt_enable(level);
        }
        break;

    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV ||
                argval != RT_CAN_MODE_NOPRIV)
        {
            return RT_ERROR;
        }
        if (argval != can->config.privmode)
        {
            can->config.privmode = argval;
            CAN_ModeConfig(plpccan->id, CAN_TXPRIORITY_MODE, ENABLE);
        }
        break;

    case RT_CAN_CMD_GET_STATUS:
    {
        can->status.rcverrcnt = 0;
        can->status.snderrcnt = 0;
        can->status.errcode = 0;
        if (arg != &can->status)
        {
            rt_memcpy(arg, &can->status, sizeof(can->status));
        }
    }
    break;

    }
    return RT_EOK;
}

static int sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    struct lpccandata *plpccan;
    LPC_CAN_TypeDef *pCan;
    struct rt_can_msg *pmsg;
    rt_uint32_t SR_Mask;
    rt_uint32_t CMRMsk;

    plpccan = (struct lpccandata *)  can->parent.user_data;
    RT_ASSERT(plpccan != RT_NULL);

    pCan = lcpcan_get_reg_base(plpccan->id);
    RT_ASSERT(pCan != RT_NULL);

    pmsg = (struct rt_can_msg *) buf;

    if (boxno > 2)
    {
        return RT_ERROR;
    }

    CMRMsk = 0x01 | (0x01 << (boxno + 5));
    SR_Mask = 0x01 << (boxno * 8 + 2);

    if (pCan->SR & SR_Mask)
    {
        volatile unsigned int  *pTFI = (&pCan->TFI1 + 0 + 4 * boxno);
        volatile unsigned int  *pTID = (&pCan->TFI1 + 1 + 4 * boxno);
        volatile unsigned int  *pTDA = (&pCan->TFI1 + 2 + 4 * boxno);
        volatile unsigned int  *pTDB = (&pCan->TFI1 + 3 + 4 * boxno);
        rt_uint32_t data;

        /* Transmit Channel 1 is available */
        /* Write frame informations and frame data into its CANxTFI1,
         * CANxTID1, CANxTDA1, CANxTDB1 register */
        data = (pmsg->len & 0x0F) << 16;
        if (pmsg->rtr == REMOTE_FRAME)
        {
            data |= (1 << 30); //set bit RTR
        }
        else
        {
            data &= ~(1 << 30);
        }

        if (pmsg->ide == EXT_ID_FORMAT)
        {
            data |= (((uint32_t)1) << 31); //set bit FF
        }
        else
        {
            data &= ~(((uint32_t)1) << 31);
        }

        if (can->config.privmode)
        {
            data |= pmsg->priv;
        }
        *pTFI = data;

        /* Write CAN ID*/
        *pTID = pmsg->id;
        /*Write first 4 data bytes*/
        data = (pmsg->data[0]) | (((pmsg->data[1])) << 8) | ((pmsg->data[2]) << 16) | ((pmsg->data[3]) << 24);
        *pTDA = data;
        /*Write second 4 data bytes*/
        data = (pmsg->data[4]) | (((pmsg->data[5])) << 8) | ((pmsg->data[6]) << 16) | ((pmsg->data[7]) << 24);
        *pTDB = data;

        /*Write transmission request*/
        pCan->CMR = CMRMsk;
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

static int recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    struct lpccandata *plpccan;
    LPC_CAN_TypeDef *pCan;

    plpccan = (struct lpccandata *)  can->parent.user_data;
    RT_ASSERT(plpccan != RT_NULL);
    pCan = lcpcan_get_reg_base(plpccan->id);
    RT_ASSERT(pCan != RT_NULL);

    //CAN_ReceiveMsg
    //check status of Receive Buffer
    if ((pCan->SR & 0x00000001))
    {
        uint32_t data;
        struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

        /* Receive message is available */
        /* Read frame informations */
        pmsg->ide = (uint8_t)(((pCan->RFS) & 0x80000000) >> 31);
        pmsg->rtr = (uint8_t)(((pCan->RFS) & 0x40000000) >> 30);
        pmsg->len = (uint8_t)(((pCan->RFS) & 0x000F0000) >> 16);
        /* Read CAN message identifier */
        pmsg->id = pCan->RID;
        /* Read the data if received message was DATA FRAME */
        if (!pmsg->rtr)
        {
            /* Read first 4 data bytes */
            data = pCan->RDA;
            pmsg->data[0] = data & 0x000000FF;
            pmsg->data[1] = (data & 0x0000FF00) >> 8;
            pmsg->data[2] = (data & 0x00FF0000) >> 16;
            pmsg->data[3] = (data & 0xFF000000) >> 24;
            /* Read second 4 data bytes */
            if (pmsg->len > 4)
            {
                data = pCan->RDB;
                pmsg->data[4] = data & 0x000000FF;
                pmsg->data[5] = (data & 0x0000FF00) >> 8;
                pmsg->data[6] = (data & 0x00FF0000) >> 16;
                pmsg->data[7] = (data & 0xFF000000) >> 24;
            }
            pmsg->hdr = 0;
            /*release receive buffer*/
            pCan->CMR = 0x04;
        }
        else
        {
            /* Received Frame is a Remote Frame, not have data, we just receive
             * message information only */
            pCan->CMR = 0x04; /*release receive buffer*/
            return SUCCESS;
        }
    }
    else
    {
        // no receive message available
        return ERROR;
    }
    return RT_EOK;
}
static int insertothdrlist(struct rt_can_device *can, struct rt_can_msg_list *msglist)
{
    struct rt_can_hdr *phdrhead = lpccanhdr;
    rt_int32_t hdr = msglist->data.hdr;
    RT_ASSERT(hdr < can->config.maxhdr && hdr >= 0);
    if (phdrhead[hdr].connected)
    {
        rt_list_insert_before(&phdrhead[hdr].list, &msglist->hdrlist);
        msglist->owner = &phdrhead[hdr];
        phdrhead[hdr].msgs++;
    }
    return RT_EOK;
}
static struct rt_can_msg_list *getfromhdrlist(struct rt_can_device *can, rt_int32_t hdr)
{
    struct rt_can_msg_list *listmsg = RT_NULL;
    struct rt_can_hdr *phdrhead = lpccanhdr;
    if (hdr >= 0 && hdr < can->config.maxhdr && !rt_list_isempty(&phdrhead[hdr].list))
    {
        listmsg = rt_list_entry(phdrhead[hdr].list.next, struct rt_can_msg_list, hdrlist);
        rt_list_remove(&listmsg->hdrlist);
        if (phdrhead[hdr].msgs)
        {
            phdrhead[hdr].msgs--;
        }
        listmsg->owner = RT_NULL;
        return listmsg;
    }
    return RT_NULL;
}
static int dettachhdrlist(struct rt_can_device *can,  struct rt_can_msg_list *msglist)
{
    rt_list_remove(&msglist->hdrlist);
    if (msglist->owner != RT_NULL && msglist->owner->msgs)
    {
        msglist->owner->msgs--;
    }
    msglist->owner = RT_NULL;
    return RT_EOK;
}
static int indicatehdrlist(struct rt_can_device *can,  struct rt_can_msg_list *msglist)
{
    struct rt_can_hdr *phdrhead = lpccanhdr;
    rt_int32_t hdr = msglist->data.hdr;
    rt_base_t level;
    RT_ASSERT(msglist->data.hdr < can->config.maxhdr && msglist->data.hdr >= 0);
    if (phdrhead[hdr].connected && phdrhead[hdr].filter.ind)
    {
        rt_size_t rx_length;
        level = rt_hw_interrupt_disable();
        rx_length = phdrhead[hdr].msgs * sizeof(struct rt_can_msg);
        rt_hw_interrupt_enable(level);
        phdrhead[hdr].filter.ind(&can->parent, phdrhead[hdr].filter.args, hdr, rx_length);
        return RT_EOK;
    }
    return RT_ERROR;
}
static int inithdrlist(struct rt_can_device *can,  struct rt_can_msg_list *msglist)
{
    RT_ASSERT(msglist != RT_NULL);
    rt_list_init(&msglist->hdrlist);
    msglist->owner = RT_NULL;
    return RT_EOK;
}
static const struct rt_can_ops canops =
{
    configure,
    control,
    sendmsg,
    recvmsg,
#ifdef RT_CAN_USING_HDR
    insertothdrlist,
    getfromhdrlist,
    dettachhdrlist,
    indicatehdrlist,
    inithdrlist,
#endif
};

#ifdef RT_USING_LPCCAN1
static struct lpccandata lpccandata1 =
{
    CAN_ID_1,
};
static struct rt_can_device lpccan1;
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
static struct lpccandata lpccandata2 =
{
    CAN_ID_2,
};
static struct rt_can_device lpccan2;
#endif /*RT_USING_LPCCAN2*/

static struct rt_can_device *lpccanid2dev(en_CAN_unitId id)
{
#ifdef RT_USING_LPCCAN1
    if (id == CAN_ID_1)
    {
        return &lpccan1;
    }
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
    if (id == CAN_ID_2)
    {
        return &lpccan2;
    }
#endif /*RT_USING_LPCCAN2*/
    return RT_NULL;
}
/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief        Event Router IRQ Handler
 * @param[in]    None
 * @return       None
 **********************************************************************/
void CAN_IRQHandler(void)
{
    rt_uint32_t IntStatus;

#ifdef RT_USING_LPCCAN1
    IntStatus = CAN_IntGetStatus(CAN_1);

    //check receive interrupt
    if ((IntStatus >> CANINT_RIE) & 0x01)
    {
        static uint32_t count = 0;

        count++;
        //rt_kprintf("\nIRQ RIE: %d\n", count);
        rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_RX_IND | 0 << 8);
    }

    //check Transmit Interrupt  interrupt1
    if ((IntStatus >> CANINT_TIE1) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_STS);
        if (state & (0x01 << 3))
        {
            rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
    }

    if ((IntStatus >> CANINT_BEIE) & 0x01)
    {
        int boxno;
        LPC_CAN_TypeDef *pCan = lcpcan_get_reg_base(CAN_1);

        pCan->MOD = 0; // set Normal operating.
        for (boxno = 0; boxno < 3; boxno++)
        {
            if (!((pCan->SR >> (8 * boxno)) & (1 << 3)))
            {
                uint32_t CMRMsk = 0x01 | (0x01 << (boxno + 5));
                pCan->CMR = CMRMsk;
            }
        }
    }

    //check Error Warning Interrupt
    if ((IntStatus >> CANINT_EIE) & 0x01)
    {
        rt_uint32_t errtype;
        rt_uint32_t state;

        errtype = (IntStatus >> 16);
        if (errtype & 0x1F && lpccan1.status.lasterrtype == (errtype & 0x1F))
        {
            switch ((errtype & 0x1F))
            {
            case 0x03: // 00011 Start of Frame
            case 0x02: // 00010 ID28 ... ID21
            case 0x06: // 00110 ID20 ... ID18
            case 0x04: // 00100 SRTR Bit
            case 0x05: // 00101 IDE bit
            case 0x07: // 00111 ID17 ... 13
            case 0x0F: // 01111 ID12 ... ID5
            case 0x0E: // 01110 ID4 ... ID0
            case 0x0C: // 01100 RTR Bit
            case 0x0B: // 01011 Data Length Code
            case 0x0A: // 01010 Data Field
                lpccan1.status.formaterrcnt++;
                break;

            case 0x0D: // 01101 Reserved Bit 1
            case 0x09: // 01001 Reserved Bit 0
                lpccan1.status.bitpaderrcnt++;
                break;

            case 0x08: // 01000 CRC Sequence
            case 0x18: // 11000 CRC Delimiter
                lpccan1.status.crcerrcnt++;
                break;

            case 0x19: // 11001 Acknowledge Slot
            case 0x1B: // 11011 Acknowledge Delimiter
                lpccan1.status.ackerrcnt++;
                break;

            case 0x1A: // 11010 End of Frame
            case 0x12: // 10010 Intermission
                lpccan1.status.formaterrcnt++;
                break;
            }
            lpccan1.status.lasterrtype = errtype & 0x1F;
        }

        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_GLOBAL_STS);
        lpccan1.status.rcverrcnt = (state >> 16) & 0xFF;
        lpccan1.status.snderrcnt = (state >> 24) & 0xFF;
        lpccan1.status.errcode = (state >> 5) & 0x06;
    }

    //check Data Overrun Interrupt Interrupt
    if ((IntStatus >> CANINT_DOIE) & 0x01)
    {
        rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_RXOF_IND | 0 << 8);
    }

    //check Transmit Interrupt  interrupt2
    if ((IntStatus >> CANINT_TIE2) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_STS);
        if (state & (0x01 << 11))
        {
            rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
    }

    //check Transmit Interrupt  interrupt3
    if ((IntStatus >> CANINT_TIE3) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_1, CANCTRL_STS);
        if (state & (0x01 << 19))
        {
            rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&lpccan1, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
    }
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
    IntStatus = CAN_IntGetStatus(CAN_2);

    //check receive interrupt
    if ((IntStatus >> CANINT_RIE) & 0x01)
    {
        rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_RX_IND | 0 << 8);
    }

    //check Transmit Interrupt  interrupt1
    if ((IntStatus >> CANINT_TIE1) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_STS);
        if (state & (0x01 << 3))
        {
            rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
    }

    //check Error Warning Interrupt
    if ((IntStatus >> CANINT_EIE) & 0x01)
    {
        rt_uint32_t state = 0;
        rt_uint32_t errtype;

        errtype = (IntStatus >> 16);
        if (errtype & 0x1F && lpccan2.status.lasterrtype == (errtype & 0x1F))
        {
            switch ((errtype & 0x1F))
            {
            case 0x03: // 00011 Start of Frame
            case 0x02: // 00010 ID28 ... ID21
            case 0x06: // 00110 ID20 ... ID18
            case 0x04: // 00100 SRTR Bit
            case 0x05: // 00101 IDE bit
            case 0x07: // 00111 ID17 ... 13
            case 0x0F: // 01111 ID12 ... ID5
            case 0x0E: // 01110 ID4 ... ID0
            case 0x0C: // 01100 RTR Bit
            case 0x0B: // 01011 Data Length Code
            case 0x0A: // 01010 Data Field
                lpccan2.status.formaterrcnt++;
                break;

            case 0x0D: // 01101 Reserved Bit 1
            case 0x09: // 01001 Reserved Bit 0
                lpccan2.status.bitpaderrcnt++;
                break;

            case 0x08: // 01000 CRC Sequence
            case 0x18: // 11000 CRC Delimiter
                lpccan2.status.crcerrcnt++;
                break;

            case 0x19: // 11001 Acknowledge Slot
            case 0x1B: // 11011 Acknowledge Delimiter
                lpccan2.status.ackerrcnt++;
                break;

            case 0x1A: // 11010 End of Frame
            case 0x12: // 10010 Intermission
                lpccan2.status.formaterrcnt++;
                break;
            }
            lpccan2.status.lasterrtype = errtype & 0x1F;
        }

        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_GLOBAL_STS);
        lpccan2.status.rcverrcnt = (state >> 16) & 0xFF;
        lpccan2.status.snderrcnt = (state >> 24) & 0xFF;
        lpccan2.status.errcode = (state >> 5) & 0x06;
    }

    //check Data Overrun Interrupt Interrupt
    if ((IntStatus >> CANINT_DOIE) & 0x01)
    {
        rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_RXOF_IND | 0 << 8);
    }

    //check Transmit Interrupt  interrupt2
    if ((IntStatus >> CANINT_TIE2) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_STS);
        if (state & (0x01 << 11))
        {
            rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
    }

    //check Transmit Interrupt  interrupt3
    if ((IntStatus >> CANINT_TIE3) & 0x01)
    {
        rt_uint32_t state = 0;
        state = CAN_GetCTRLStatus(CAN_2, CANCTRL_STS);
        if (state & (0x01 << 19))
        {
            rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&lpccan2, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
    }
#endif /*RT_USING_LPCCAN2*/

}

int lpc_can_init(void)
{
    rt_mutex_init(&lpcfilterlock, "canfltr", RT_IPC_FLAG_PRIO);
#ifdef RT_CAN_USING_HDR
    int i;
    for (i = 0; i < MAXLPCHDR; i++)
    {
        rt_list_init(&lpccanhdr[i].list);
    }
#endif
#ifdef RT_USING_LPCCAN1
    lpccan1.config.baud_rate = CAN1MBaud;
    lpccan1.config.msgboxsz = 16;
    lpccan1.config.sndboxnumber = 3;
    lpccan1.config.mode = RT_CAN_MODE_NORMAL;
    lpccan1.config.privmode = 0;
#ifdef RT_CAN_USING_HDR
    lpccan1.config.maxhdr = MAXLPCHDR;
#endif
    lpccan1.config.ticks = 50;

    // enable CAN clock.
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAN1, ENABLE);
    rt_hw_can_register(&lpccan1, "lpccan1", &canops, &lpccandata1);
#endif /*RT_USING_LPCCAN1*/

#ifdef RT_USING_LPCCAN2
    lpccan2.config.baud_rate = CAN1MBaud;
    lpccan2.config.msgboxsz = 16;
    lpccan2.config.sndboxnumber = 3;
    lpccan2.config.mode = RT_CAN_MODE_NORMAL;
    lpccan2.config.privmode = 0;
#ifdef RT_CAN_USING_HDR
    lpccan2.config.maxhdr = MAXLPCHDR;
#endif

    lpccan2.config.ticks = 50;

#ifdef RT_CAN_USING_HDR
#endif

    // enable CAN clock.
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCAN2, ENABLE);
    rt_hw_can_register(&lpccan2, "lpccan2", &canops, &lpccandata2);
#endif /*RT_USING_LPCCAN2*/

    //Enable CAN Interrupt
    NVIC_EnableIRQ(CAN_IRQn);

    return RT_EOK;
}
INIT_BOARD_EXPORT(lpc_can_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
static void __can_dump(LPC_CAN_TypeDef *pCan)
{
    rt_kprintf("MOD : 0x%08X\n", pCan->MOD);
    //rt_kprintf("CMR : 0x%08X\n", pCan->CMR); // WO
    rt_kprintf("GSR : 0x%08X, RXERR: %d, TXERR: %d\n", pCan->GSR, (pCan->GSR >> 16) & 0xFF, (pCan->GSR >> 24) & 0xFF);
    rt_kprintf("ICR : 0x%08X\n", pCan->ICR);
    rt_kprintf("IER : 0x%08X\n", pCan->IER);
    rt_kprintf("BTR : 0x%08X\n", pCan->BTR);
    rt_kprintf("EWL : 0x%08X\n", pCan->EWL);
    rt_kprintf("SR  : 0x%08X\n", pCan->SR);
    rt_kprintf("RFS : 0x%08X\n", pCan->RFS);
    rt_kprintf("RID : 0x%08X\n", pCan->RID);
    //rt_kprintf("RDA: 0x%08X\n", pCan->RDA); // D[3:0]
    //rt_kprintf("RDB: 0x%08X\n", pCan->RDB); // D[7:4]
    rt_kprintf("TFI1: 0x%08X\n", pCan->TFI1);
    rt_kprintf("TID1: 0x%08X\n", pCan->TID1);
    rt_kprintf("TFI2: 0x%08X\n", pCan->TFI2);
    rt_kprintf("TID2: 0x%08X\n", pCan->TID2);
    rt_kprintf("TFI3: 0x%08X\n", pCan->TFI3);
    rt_kprintf("TID3: 0x%08X\n", pCan->TID3);
}

static int lpccan_dump(void)
{
#ifdef RT_USING_LPCCAN1
    rt_kprintf("CAN 1:\n");
    __can_dump(LPC_CAN1);
#endif

#ifdef RT_USING_LPCCAN2
    rt_kprintf("\nCAN 2:\n");
    __can_dump(LPC_CAN2);
#endif

    return 0;
}
FINSH_FUNCTION_EXPORT(lpccan_dump, dump LPC CAN register.);
#endif /*RT_USING_FINSH*/

#endif /*RT_USING_CAN*/
