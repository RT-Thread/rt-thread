/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_anatop_ai.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.anatop_ai"
#endif

uint32_t ANATOP_AI_Access(anatop_ai_itf_t itf, bool isWrite, anatop_ai_reg_t addr, uint32_t wdata)
{
    uint32_t temp;
    uint32_t rdata;
    uint32_t pre_toggle_done;
    uint32_t toggle_done;

    switch (itf)
    {
        case kAI_Itf_Ldo:
            if (isWrite)
            {
                ANADIG_MISC->VDDSOC_AI_CTRL &= ~ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AIRWB_MASK;
                temp = ANADIG_MISC->VDDSOC_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AI_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AI_ADDR_SHIFT) &
                        ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AI_ADDR_MASK;
                ANADIG_MISC->VDDSOC_AI_CTRL  = temp;
                ANADIG_MISC->VDDSOC_AI_WDATA = wdata;                                     /* write ai data */
                ANADIG_PMU->PMU_LDO_PLL ^= ANADIG_PMU_PMU_LDO_PLL_LDO_PLL_AI_TOGGLE_MASK; /* toggle */
            }
            else /* read */
            {
                temp = ANADIG_MISC->VDDSOC_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AIRWB_MASK;
                temp |= (1UL << ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AIRWB_SHIFT) &
                        ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AIRWB_MASK;
                ANADIG_MISC->VDDSOC_AI_CTRL = temp;
                temp                        = ANADIG_MISC->VDDSOC_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AI_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AI_ADDR_SHIFT) &
                        ANADIG_MISC_VDDSOC_AI_CTRL_VDDSOC_AI_ADDR_MASK;
                ANADIG_MISC->VDDSOC_AI_CTRL = temp;
                ANADIG_PMU->PMU_LDO_PLL ^= ANADIG_PMU_PMU_LDO_PLL_LDO_PLL_AI_TOGGLE_MASK; /* toggle */
                rdata = ANADIG_MISC->VDDSOC_AI_RDATA;                                     /* read data */
                return rdata;
            }
            break;
        case kAI_Itf_1g:
            if (isWrite)
            {
                pre_toggle_done =
                    ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G &
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AITOGGLE_DONE_1G_MASK; /* get pre_toggle_done */
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIRWB_1G_MASK;
                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIADDR_1G_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIADDR_1G_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIADDR_1G_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G  = temp;
                ANADIG_MISC->VDDSOC2PLL_AI_WDATA_1G = wdata; /* write ai data */
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G ^=
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AITOGGLE_1G_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        (ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G &
                         ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AITOGGLE_DONE_1G_MASK); /*  wait toggle done
                                                                                                 toggle */
                } while (toggle_done == pre_toggle_done);
            }
            else
            {
                pre_toggle_done =
                    (ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G &
                     ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AITOGGLE_DONE_1G_MASK); /* get pre_toggle_done */
                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIRWB_1G_MASK;
                temp |= (1UL << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIRWB_1G_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIRWB_1G_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G = temp;
                temp                               = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIADDR_1G_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIADDR_1G_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AIADDR_1G_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G = temp;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G ^=
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AITOGGLE_1G_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        (ANADIG_MISC->VDDSOC2PLL_AI_CTRL_1G &
                         ANADIG_MISC_VDDSOC2PLL_AI_CTRL_1G_VDDSOC2PLL_AITOGGLE_DONE_1G_MASK); /*  wait toggle done
                                                                                                 toggle */
                } while (toggle_done == pre_toggle_done);
                rdata = ANADIG_MISC->VDDSOC2PLL_AI_RDATA_1G; /* read data */
                return rdata;
            }
            break;
        case kAI_Itf_Audio:
            if (isWrite)
            {
                pre_toggle_done =
                    ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO &
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AITOGGLE_DONE_AUDIO_MASK; /* get pre_toggle_done */
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO &=
                    ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AIRWB_AUDIO_MASK;
                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AI_ADDR_AUDIO_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AI_ADDR_AUDIO_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AI_ADDR_AUDIO_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO  = temp;
                ANADIG_MISC->VDDSOC2PLL_AI_WDATA_AUDIO = wdata; /* write ai data */
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO ^=
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AITOGGLE_AUDIO_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        (ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO &
                         ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AITOGGLE_DONE_AUDIO_MASK); /*  wait toggle done
                                                                                                       toggle */
                } while (toggle_done == pre_toggle_done);
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO &=
                    ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AIRWB_AUDIO_MASK;
            }
            else
            {
                pre_toggle_done =
                    (ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO &
                     ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AITOGGLE_DONE_AUDIO_MASK); /* get pre_toggle_done
                                                                                                 */

                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AIRWB_AUDIO_MASK;
                temp |= (1UL << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AIRWB_AUDIO_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AIRWB_AUDIO_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO = temp;

                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AI_ADDR_AUDIO_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AI_ADDR_AUDIO_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AI_ADDR_AUDIO_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO = temp;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO ^=
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AITOGGLE_AUDIO_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        ANADIG_MISC->VDDSOC2PLL_AI_CTRL_AUDIO &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_AUDIO_VDDSOC2PLL_AITOGGLE_DONE_AUDIO_MASK; /*  wait toggle done
                                                                                                     toggle */
                } while (toggle_done == pre_toggle_done);
                rdata = ANADIG_MISC->VDDSOC2PLL_AI_RDATA_AUDIO; /* read data */
                return rdata;
            }
            break;
        case kAI_Itf_Video:
            if (isWrite)
            {
                pre_toggle_done =
                    ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO &
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AITOGGLE_DONE_VIDEO_MASK; /* get pre_toggle_done */

                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO &=
                    ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIRWB_VIDEO_MASK;

                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIADDR_VIDEO_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIADDR_VIDEO_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIADDR_VIDEO_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO  = temp;
                ANADIG_MISC->VDDSOC2PLL_AI_WDATA_VIDEO = wdata; /* write ai data */
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO ^=
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AITOGGLE_VIDEO_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AITOGGLE_DONE_VIDEO_MASK; /*  wait toggle done
                                                                                                     toggle */
                } while (toggle_done == pre_toggle_done);
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO &=
                    ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIRWB_VIDEO_MASK;
            }
            else
            {
                pre_toggle_done =
                    ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO &
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AITOGGLE_DONE_VIDEO_MASK; /* get pre_toggle_done */
                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIRWB_VIDEO_MASK;
                temp |= (1UL << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIRWB_VIDEO_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIRWB_VIDEO_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO = temp;

                temp = ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO;
                temp &= ~ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIADDR_VIDEO_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIADDR_VIDEO_SHIFT) &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AIADDR_VIDEO_MASK;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO = temp;
                ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO ^=
                    ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AITOGGLE_VIDEO_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        ANADIG_MISC->VDDSOC2PLL_AI_CTRL_VIDEO &
                        ANADIG_MISC_VDDSOC2PLL_AI_CTRL_VIDEO_VDDSOC2PLL_AITOGGLE_DONE_VIDEO_MASK; /*  wait toggle done
                                                                                                     toggle */
                } while (toggle_done == pre_toggle_done);
                rdata = ANADIG_MISC->VDDSOC2PLL_AI_RDATA_VIDEO; /* read data */
                return rdata;
            }
            break;
        case kAI_Itf_400m:
            if (isWrite)
            {
                pre_toggle_done =
                    ANADIG_MISC->VDDLPSR_AI400M_CTRL &
                    ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AITOGGLE_DONE_400M_MASK; /* get pre_toggle_done */
                ANADIG_MISC->VDDLPSR_AI400M_CTRL &= ~ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_RWB_MASK;

                temp = ANADIG_MISC->VDDLPSR_AI400M_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_ADDR_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_ADDR_MASK;
                ANADIG_MISC->VDDLPSR_AI400M_CTRL  = temp;
                ANADIG_MISC->VDDLPSR_AI400M_WDATA = wdata; /* write ai data */
                ANADIG_MISC->VDDLPSR_AI400M_CTRL ^=
                    ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AITOGGLE_400M_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        ANADIG_MISC->VDDLPSR_AI400M_CTRL &
                        ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AITOGGLE_DONE_400M_MASK; /*  wait toggle done toggle */
                } while (toggle_done == pre_toggle_done);
            }
            else
            {
                pre_toggle_done =
                    ANADIG_MISC->VDDLPSR_AI400M_CTRL &
                    ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AITOGGLE_DONE_400M_MASK; /* get pre_toggle_done */

                temp = ANADIG_MISC->VDDLPSR_AI400M_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_RWB_MASK;
                temp |= (1UL << ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_RWB_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_RWB_MASK;
                ANADIG_MISC->VDDLPSR_AI400M_CTRL = temp;

                temp = ANADIG_MISC->VDDLPSR_AI400M_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_ADDR_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AI400M_ADDR_MASK;
                ANADIG_MISC->VDDLPSR_AI400M_CTRL = temp;
                ANADIG_MISC->VDDLPSR_AI400M_CTRL ^=
                    ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AITOGGLE_400M_MASK; /*  toggle  */
                do
                {
                    toggle_done =
                        ANADIG_MISC->VDDLPSR_AI400M_CTRL &
                        ANADIG_MISC_VDDLPSR_AI400M_CTRL_VDDLPSR_AITOGGLE_DONE_400M_MASK; /*  wait toggle done toggle */
                } while (toggle_done == pre_toggle_done);
                rdata = ANADIG_MISC->VDDLPSR_AI400M_RDATA; /* read data */
                return rdata;
            }
            break;
        case kAI_Itf_Temp:
            if (isWrite)
            {
                ANADIG_MISC->VDDLPSR_AI_CTRL &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_MASK;

                temp = ANADIG_MISC->VDDLPSR_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                ANADIG_MISC->VDDLPSR_AI_CTRL  = temp;
                ANADIG_MISC->VDDLPSR_AI_WDATA = wdata; /* write ai data */
                ANADIG_TEMPSENSOR->TEMPSENSOR ^= ANADIG_TEMPSENSOR_TEMPSENSOR_TEMPSNS_AI_TOGGLE_MASK; /*  toggle */
            }
            else
            {
                temp = ANADIG_MISC->VDDLPSR_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_MASK;
                temp |= (1UL << ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_MASK;
                ANADIG_MISC->VDDLPSR_AI_CTRL = temp;

                temp = ANADIG_MISC->VDDLPSR_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                ANADIG_MISC->VDDLPSR_AI_CTRL = temp;
                ANADIG_TEMPSENSOR->TEMPSENSOR ^= ANADIG_TEMPSENSOR_TEMPSENSOR_TEMPSNS_AI_TOGGLE_MASK; /*  toggle  */
                rdata = ANADIG_MISC->VDDLPSR_AI_RDATA_TMPSNS;                                         /* read data */
                return rdata;
            }
            break;
        case kAI_Itf_Bandgap:
            if (isWrite)
            {
                ANADIG_MISC->VDDLPSR_AI_CTRL &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_MASK;

                temp = ANADIG_MISC->VDDLPSR_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                ANADIG_MISC->VDDLPSR_AI_CTRL  = temp;
                ANADIG_MISC->VDDLPSR_AI_WDATA = wdata;                                  /* write ai data */
                ANADIG_PMU->PMU_REF_CTRL ^= ANADIG_PMU_PMU_REF_CTRL_REF_AI_TOGGLE_MASK; /* toggle */
            }
            else
            {
                temp = ANADIG_MISC->VDDLPSR_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_MASK;
                temp |= (1UL << ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AIRWB_MASK;
                ANADIG_MISC->VDDLPSR_AI_CTRL = temp;

                temp = ANADIG_MISC->VDDLPSR_AI_CTRL;
                temp &= ~ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                temp |= ((uint32_t)addr << ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_SHIFT) &
                        ANADIG_MISC_VDDLPSR_AI_CTRL_VDDLPSR_AI_ADDR_MASK;
                ANADIG_MISC->VDDLPSR_AI_CTRL = temp;
                ANADIG_PMU->PMU_REF_CTRL ^= ANADIG_PMU_PMU_REF_CTRL_REF_AI_TOGGLE_MASK; /* toggle */
                rdata = ANADIG_MISC->VDDLPSR_AI_RDATA_REFTOP;                           /* read data */
                return rdata;
            }
            break;
        default:
            /* This branch should never be hit. */
            break;
    }
    return 0;
}

void ANATOP_AI_Write(anatop_ai_itf_t itf, anatop_ai_reg_t addr, uint32_t wdata)
{
    (void)ANATOP_AI_Access(itf, true, addr, wdata);
}

uint32_t ANATOP_AI_Read(anatop_ai_itf_t itf, anatop_ai_reg_t addr)
{
    uint32_t rdata;
    rdata = ANATOP_AI_Access(itf, false, addr, 0);
    return rdata;
}

void ANATOP_AI_WriteWithMaskShift(
    anatop_ai_itf_t itf, anatop_ai_reg_t addr, uint32_t wdata, uint32_t mask, uint32_t shift)
{
    uint32_t rdata;
    rdata = ANATOP_AI_Read(itf, addr);
    rdata = (rdata & (~mask)) | ((wdata << shift) & mask);
    ANATOP_AI_Write(itf, addr, rdata);
}
