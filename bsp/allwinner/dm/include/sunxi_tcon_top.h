/* SPDX-License-Identifier: Apache-2.0 */
#ifndef SUNXI_TCON_TOP_H
#define SUNXI_TCON_TOP_H

#include <rtdevice.h>

rt_err_t sunxi_tcon_top_route(struct rt_ofw_node *node, unsigned int mixer,
                              unsigned int tcon, rt_bool_t hdmi);

#endif
