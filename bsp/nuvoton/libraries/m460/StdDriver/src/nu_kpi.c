/**************************************************************************//**
 * @file     kpi.c
 * @version  V3.00
 * @brief    KPI driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup KPI_Driver KPI Driver
  @{
*/

/** @addtogroup KPI_EXPORTED_FUNCTIONS KPI Exported Functions
  @{
*/

static KPI_KEY_T *s_pKeyQueue = 0;
static volatile uint32_t s_u32MaxKeyCnt = 0;
static volatile uint32_t s_u32FirstKey = 0;
static volatile uint32_t s_u32LastKey = 0;

__WEAK void KPI_KeyHandler(KPI_KEY_T key)

{
    uint32_t u32Next;

    /* Move last to next available space */
    u32Next = s_u32LastKey + 1;
    if (u32Next >= s_u32MaxKeyCnt)
        u32Next = 0; // buffer wrap
    if (u32Next == s_u32FirstKey)
        return; // Queue full

    /* Push key to the queue */
    s_pKeyQueue[s_u32LastKey] = key;
    s_u32LastKey = u32Next;

}


void KPI_IRQHandler()
{
    int32_t i, j, idx, r;
    uint32_t u32KeyPress[2], u32KeyRelease[2], status;
    uint32_t row, col, mask;
    KPI_KEY_T key;

    /* cache key events ASAP */
    status = KPI->STATUS;
    u32KeyPress[0] = KPI->KPF[0];
    u32KeyPress[1] = KPI->KPF[1];
    u32KeyRelease[0] = KPI->KRF[0];
    u32KeyRelease[1] = KPI->KRF[1];

    if (status & KPI_STATUS_KIF_Msk)
    {
        /* Get current row/column setting */
        row = ((KPI->CTL & KPI_CTL_KROW_Msk) >> KPI_CTL_KROW_Pos) + 1;
        col = ((KPI->CTL & KPI_CTL_KCOL_Msk) >> KPI_CTL_KCOL_Pos) + 1;

        /* Deal with the key evernts */
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                /* Identify the specified key bit */
                idx = (i < 4) ? 0 : 1;
                r   = i - idx * 4;
                mask = 1ul << (r * 8 + j);

                /* Key Release */
                if (status & KPI_STATUS_KRIF_Msk)
                {
                    if (u32KeyRelease[idx] & mask)
                    {
                        /* Clean event */
                        KPI->KRF[idx] = mask;

                        /* Record the key */
                        key.x = i;
                        key.y = j;
                        key.st = KPI_RELEASE;

                        /* call handler */
                        KPI_KeyHandler(key);
                    }
                }
            }
        }

        /* Deal with the key evernts */
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                /* Identify the specified key bit */
                idx = (i < 4) ? 0 : 1;
                r   = i - idx * 4;
                mask = 1ul << (r * 8 + j);


                /* Key Press */
                if (status & KPI_STATUS_KPIF_Msk)
                {
                    if (u32KeyPress[idx] & mask)
                    {
                        /* Clean event */
                        KPI->KPF[idx] = mask;

                        /* Record the key */
                        key.x = i;
                        key.y = j;
                        key.st = KPI_PRESS;

                        /* call handler */
                        KPI_KeyHandler(key);
                    }
                }
            }
        }
    }

    if (status & KPI_STATUS_TKRIF_Msk)
    {
        /* Clear flag */
        KPI->STATUS = KPI_STATUS_TKRIF_Msk;

        printf("Three key press!!\n");

    }

}



/**
 *    @brief        Open Keypad interface
 *
 *    @param[in]    kpi        The pointer of the specified KPI module.
 *    @param[in]    u32Rows    The number of key rows for key scan. it could be 2 ~ 6.
 *    @param[in]    u32Columns The number of key columns for key scan. it could be 1 ~ 8.
 *    @param[in]    keyQueue   The FIFO queue of the key press/release status.
 *
 *    @retval       0   Sucessful
 *    @retval       -1  Failure
 *
 *    @details      The function is used to set row and column of keypad and start to key scan.
 */
int32_t KPI_Open(uint32_t u32Rows, uint32_t u32Columns, KPI_KEY_T *pkeyQueue, uint32_t u32MaxKeyCnt)
{
    /* Key ROW limitation */
    if ((u32Rows < 2) || (u32Rows > 6))
        return -1;

    /* Key COLUMN limitation */
    if (u32Columns > 8)
        return -1;

    /* Enable KPI Clock */
    CLK->APBCLK2 |= CLK_APBCLK2_KPICKEN_Msk;

    /* Seleck KPI Clock Source */
    CLK->CLKSEL3 |= CLK_CLKSEL3_KPISEL_HIRC;


    /* Reset KPI */
    SYS->IPRST3 |= SYS_IPRST3_KPIRST_Msk;
    SYS->IPRST3 ^= SYS_IPRST3_KPIRST_Msk;

    /* Set KPI */
    KPI->CTL = ((u32Rows - 1) << KPI_CTL_KROW_Pos) | ((u32Columns - 1) << KPI_CTL_KCOL_Pos) |
               KPI_CTL_KIEN_Msk | KPI_CTL_KPIEN_Msk | KPI_CTL_KRIEN_Msk |
               (3 << KPI_CTL_DBCLKSEL_Pos) |
               KPI_CTL_KPEN_Msk;

    NVIC_EnableIRQ(KPI_IRQn);

    /* Set up the queue of key */
    s_pKeyQueue = pkeyQueue;
    s_u32MaxKeyCnt = u32MaxKeyCnt;
    s_u32FirstKey = 0;
    s_u32LastKey = 0;

    return 0;
}

/**
 *    @brief        Close Keypad interface
 *
 *    @details      The function is used to stop and close key pad.
 */

void KPI_Close()
{
    /* Disable Keypad */
    KPI->CTL = 0;
}


/**
 *    @brief        Detect any key press
 *
 *
 *    @retval       1   Key pressed
 *    @retval       0   No key pressed
 *
 *    @details      The function is used to check if any key pressed.
 */
int32_t KPI_kbhit()
{
    if (s_u32FirstKey != s_u32LastKey)
        return 1;
    return 0;
}


/**
 *    @brief        Get pressed/released key
 *
 *    @return       return the pressed key information. If no key pressed, return key index is 0xff, 0xff.
 *
 *    @details      The function is get the key pressed or key released.
 */
KPI_KEY_T KPI_GetKey()
{
    KPI_KEY_T key = {0xff, 0xff, 0xffff};

    /* Check if queue is empty */
    if (s_u32FirstKey != s_u32LastKey)
    {
        /* Pop the key from queue */
        key = s_pKeyQueue[s_u32FirstKey++];

        /* Wrap around check */
        if (s_u32FirstKey >= s_u32MaxKeyCnt)
            s_u32FirstKey = 0;
    }

    return key;
}


/**
 *    @brief        Set key sample time
 *
 *    @param[in]    ms        The key sample time in milliseconds.
 *
 *    @details      The function is used to set key sample time. The maximum time is 1398 milliseconds.
 */
void KPI_SetSampleTime(uint32_t ms)
{
    if (ms >= 1398)
        ms = 1398;

    KPI->DLYCTL = 0x1F | ((__HIRC / 1000) * ms << 8);
}


/*@}*/ /* end of group KPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group KPI_Driver */

/*@}*/ /* end of group Standard_Driver */
