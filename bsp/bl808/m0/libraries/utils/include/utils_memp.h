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
#ifndef __UTILS_MEMP_H__
#define __UTILS_MEMP_H__


struct utils_memp_node {
    struct utils_memp_node *next;
};

typedef struct pool {
    uint32_t node_size;
    uint32_t pool_cap;
    uint32_t pool_size;
    uint8_t align_req;
    uint32_t padded_node_size;
    void *first_node;
    void *last_node;
    struct utils_memp_node *mem;
}utils_memp_pool_t;

int utils_memp_init(utils_memp_pool_t **pool, uint16_t node_size, uint16_t pool_cap, uint8_t align_req);
int utils_memp_init_alloced(utils_memp_pool_t *pool, uint16_t node_size, uint16_t pool_cap, uint8_t align_req);
int utils_memp_deinit(utils_memp_pool_t *pool);
void *utils_memp_malloc(utils_memp_pool_t *pool);
int utils_memp_free(utils_memp_pool_t *pool, void *node);

#endif
