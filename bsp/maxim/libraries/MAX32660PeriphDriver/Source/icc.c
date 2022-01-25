/* *****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include <stdint.h>
#include <stdio.h>
#include "mxc_config.h"
#include "mxc_errors.h"
#include "icc_regs.h"
#include "icc.h"

static int ICC_Ready(void)
{
    return (MXC_ICC->cache_ctrl & MXC_F_ICC_CACHE_CTRL_CACHE_RDY);
}

int ICC_ID(icc_cache_id_t cid)
{
    switch (cid) {
        case ICC_CACHE_ID_RELNUM:
            return ((MXC_ICC->cache_id & MXC_F_ICC_CACHE_ID_RELNUM) >> MXC_F_ICC_CACHE_ID_RELNUM_POS);
        case ICC_CACHE_ID_PARTNUM:
            return ((MXC_ICC->cache_id & MXC_F_ICC_CACHE_ID_PARTNUM) >> MXC_F_ICC_CACHE_ID_PARTNUM_POS);
        case ICC_CACHE_ID_CCHID:
            return ((MXC_ICC->cache_id & MXC_F_ICC_CACHE_ID_CCHID) >> MXC_F_ICC_CACHE_ID_CCHID_POS);
        default:
            return E_BAD_PARAM;
    }
}

void ICC_Enable(void)
{
    // Invalidate cache and wait until ready
    MXC_ICC->invalidate = 1;
    while (!(ICC_Ready()));
    
    // Enable Cache
    MXC_ICC->cache_ctrl |= MXC_F_ICC_CACHE_CTRL_CACHE_EN;
}

void ICC_Disable(void)
{
    // Disable Cache
    MXC_ICC->cache_ctrl &= ~MXC_F_ICC_CACHE_CTRL_CACHE_EN;
}

void ICC_Flush(void)
{
    ICC_Disable();
    ICC_Enable();
}
