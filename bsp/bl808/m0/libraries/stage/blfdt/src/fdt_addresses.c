/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "libfdt_env.h"

#include <fdt.h>
#include <libfdt.h>

#include "libfdt_internal.h"

static int fdt_cells(const void *fdt, int nodeoffset, const char *name)
{
    const fdt32_t *c;
    int val;
    int len;

    c = fdt_getprop(fdt, nodeoffset, name, &len);
    if (!c)
        return len;

    if (len != sizeof(*c))
        return -FDT_ERR_BADNCELLS;

    val = fdt32_to_cpu(*c);
    if ((val <= 0) || (val > FDT_MAX_NCELLS))
        return -FDT_ERR_BADNCELLS;

    return val;
}

int fdt_address_cells(const void *fdt, int nodeoffset)
{
    int val;

    val = fdt_cells(fdt, nodeoffset, "#address-cells");
    if (val == -FDT_ERR_NOTFOUND)
        return 2;
    return val;
}

int fdt_size_cells(const void *fdt, int nodeoffset)
{
    int val;

    val = fdt_cells(fdt, nodeoffset, "#size-cells");
    if (val == -FDT_ERR_NOTFOUND)
        return 1;
    return val;
}
