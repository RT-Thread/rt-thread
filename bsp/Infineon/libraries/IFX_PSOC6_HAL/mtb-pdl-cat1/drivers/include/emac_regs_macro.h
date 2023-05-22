 /**********************************************************************
 * Copyright (C) 2016 Cadence Design Systems, Inc.- http://www.cadence.com
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***********************************************************************/


#ifndef __REG_EMAC_REGS_MACRO_H__
#define __REG_EMAC_REGS_MACRO_H__


/* macros for BlueprintGlobalNameSpace::emac_regs::network_control */
#ifndef __EMAC_REGS__NETWORK_CONTROL_MACRO__
#define __EMAC_REGS__NETWORK_CONTROL_MACRO__

/* macros for field loopback */
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__SHIFT                           0
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__WIDTH                           1
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__MASK                  0x00000001U
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__RESET                           0
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field loopback_local */
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__SHIFT                     1
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__WIDTH                     1
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__MASK            0x00000002U
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__RESET                     0
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field enable_receive */
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__SHIFT                     2
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__WIDTH                     1
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__MASK            0x00000004U
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__RESET                     0
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field enable_transmit */
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__SHIFT                    3
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__WIDTH                    1
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__MASK           0x00000008U
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__RESET                    0
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__NETWORK_CONTROL__ENABLE_TRANSMIT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field man_port_en */
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SHIFT                        4
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__WIDTH                        1
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__MASK               0x00000010U
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__RESET                        0
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field clear_all_stats_regs */
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SHIFT               5
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__WIDTH               1
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__MASK      0x00000020U
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__RESET               0
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field inc_all_stats_regs */
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__SHIFT                 6
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__WIDTH                 1
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__MASK        0x00000040U
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__RESET                 0
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field stats_write_en */
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__SHIFT                     7
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__WIDTH                     1
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__MASK            0x00000080U
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__RESET                     0
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field back_pressure */
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__SHIFT                      8
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__WIDTH                      1
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__MASK             0x00000100U
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__RESET                      0
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000100U)
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | (((uint32_t)(src) <<\
                    8) & 0x00000100U)
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000100U)))
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field tx_start_pclk */
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__SHIFT                      9
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__WIDTH                      1
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__MASK             0x00000200U
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__RESET                      0
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__NETWORK_CONTROL__TX_START_PCLK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field tx_halt_pclk */
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__SHIFT                      10
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__WIDTH                       1
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__MASK              0x00000400U
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__RESET                       0
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000400U)
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | (((uint32_t)(src) <<\
                    10) & 0x00000400U)
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000400U)))
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__NETWORK_CONTROL__TX_HALT_PCLK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field tx_pause_frame_req */
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__SHIFT                11
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__WIDTH                 1
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__MASK        0x00000800U
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__RESET                 0
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field tx_pause_frame_zero */
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__SHIFT               12
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__WIDTH                1
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__MASK       0x00001000U
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__RESET                0
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field stats_take_snap */
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__SHIFT                   13
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__WIDTH                    1
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__MASK           0x00002000U
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__RESET                    0
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field stats_read_snap */
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__SHIFT                   14
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__WIDTH                    1
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__MASK           0x00004000U
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__RESET                    0
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x00004000U)
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | (((uint32_t)(src) <<\
                    14) & 0x00004000U)
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x00004000U)))
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field store_rx_ts */
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__SHIFT                       15
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__WIDTH                        1
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__MASK               0x00008000U
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__RESET                        0
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field pfc_enable */
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__SHIFT                        16
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__WIDTH                         1
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__MASK                0x00010000U
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__RESET                         0
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field transmit_pfc_priority_based_pause_frame */
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__SHIFT \
                    17
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__WIDTH \
                    1
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__MASK \
                    0x00020000U
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__RESET \
                    0
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field flush_rx_pkt_pclk */
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__SHIFT                 18
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__WIDTH                  1
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__MASK         0x00040000U
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__RESET                  0
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__NETWORK_CONTROL__FLUSH_RX_PKT_PCLK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field tx_lpi_en */
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__SHIFT                         19
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__WIDTH                          1
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__MASK                 0x00080000U
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__RESET                          0
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00080000U)
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | (((uint32_t)(src) <<\
                    19) & 0x00080000U)
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00080000U)))
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field ptp_unicast_ena */
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__SHIFT                   20
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__WIDTH                    1
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__MASK           0x00100000U
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__RESET                    0
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00100000U) >> 20)
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00100000U)
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | (((uint32_t)(src) <<\
                    20) & 0x00100000U)
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00100000U)))
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field alt_sgmii_mode */
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__SHIFT                    21
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__WIDTH                     1
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__MASK            0x00200000U
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__RESET                     0
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00200000U) >> 21)
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 21) & 0x00200000U)
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | (((uint32_t)(src) <<\
                    21) & 0x00200000U)
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 21) & ~0x00200000U)))
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field store_udp_offset */
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__SHIFT                  22
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__WIDTH                   1
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__MASK          0x00400000U
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__RESET                   0
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00400000U) >> 22)
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__WRITE(src) \
                    (((uint32_t)(src)\
                    << 22) & 0x00400000U)
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | (((uint32_t)(src) <<\
                    22) & 0x00400000U)
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 22) & ~0x00400000U)))
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field ext_tsu_port_enable */
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__SHIFT               23
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__WIDTH                1
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__MASK       0x00800000U
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__RESET                0
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x00800000U)
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | (((uint32_t)(src) <<\
                    23) & 0x00800000U)
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x00800000U)))
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field one_step_sync_mode */
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__SHIFT                24
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__WIDTH                 1
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__MASK        0x01000000U
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__RESET                 0
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field pfc_ctrl */
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__SHIFT                          25
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__WIDTH                           1
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__MASK                  0x02000000U
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__RESET                           0
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__READ(src) \
                    (((uint32_t)(src)\
                    & 0x02000000U) >> 25)
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x02000000U)
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | (((uint32_t)(src) <<\
                    25) & 0x02000000U)
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x02000000U)))
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field ext_rxq_sel_en */
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__SHIFT                    26
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__WIDTH                     1
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__MASK            0x04000000U
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__RESET                     0
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x04000000U) >> 26)
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x04000000U)
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | (((uint32_t)(src) <<\
                    26) & 0x04000000U)
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x04000000U)))
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__NETWORK_CONTROL__EXT_RXQ_SEL_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field oss_correction_field */
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__SHIFT              27
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__WIDTH               1
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__MASK      0x08000000U
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__RESET               0
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__WRITE(src) \
                    (((uint32_t)(src)\
                    << 27) & 0x08000000U)
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | (((uint32_t)(src) <<\
                    27) & 0x08000000U)
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 27) & ~0x08000000U)))
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__NETWORK_CONTROL__OSS_CORRECTION_FIELD__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field sel_mii_on_rgmii */
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__SHIFT                  28
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__WIDTH                   1
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__MASK          0x10000000U
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__RESET                   0
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field two_pt_five_gig */
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__SHIFT                   29
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__WIDTH                    1
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__MASK           0x20000000U
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__RESET                    0
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__READ(src) \
                    (((uint32_t)(src)\
                    & 0x20000000U) >> 29)
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__NETWORK_CONTROL__TWO_PT_FIVE_GIG__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field ifg_eats_qav_credit */
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__SHIFT               30
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__WIDTH                1
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__MASK       0x40000000U
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__RESET                0
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0x40000000U)
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | (((uint32_t)(src) <<\
                    30) & 0x40000000U)
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0x40000000U)))
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__NETWORK_CONTROL__IFG_EATS_QAV_CREDIT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31 */
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__SHIFT                       31
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__WIDTH                        1
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__MASK               0x80000000U
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__RESET                        0
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__NETWORK_CONTROL__RESERVED_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__NETWORK_CONTROL__TYPE                               uint32_t
#define EMAC_REGS__NETWORK_CONTROL__READ                            0xfff9c19fU
#define EMAC_REGS__NETWORK_CONTROL__WRITE                           0xfff9c19fU

#endif /* __EMAC_REGS__NETWORK_CONTROL_MACRO__ */


/* macros for network_control */
#define INST_NETWORK_CONTROL__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::network_config */
#ifndef __EMAC_REGS__NETWORK_CONFIG_MACRO__
#define __EMAC_REGS__NETWORK_CONFIG_MACRO__

/* macros for field speed */
#define EMAC_REGS__NETWORK_CONFIG__SPEED__SHIFT                               0
#define EMAC_REGS__NETWORK_CONFIG__SPEED__WIDTH                               1
#define EMAC_REGS__NETWORK_CONFIG__SPEED__MASK                      0x00000001U
#define EMAC_REGS__NETWORK_CONFIG__SPEED__RESET                               0
#define EMAC_REGS__NETWORK_CONFIG__SPEED__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__NETWORK_CONFIG__SPEED__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__NETWORK_CONFIG__SPEED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__NETWORK_CONFIG__SPEED__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__NETWORK_CONFIG__SPEED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__NETWORK_CONFIG__SPEED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field full_duplex */
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SHIFT                         1
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__WIDTH                         1
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__MASK                0x00000002U
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__RESET                         0
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field discard_non_vlan_frames */
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__SHIFT             2
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__WIDTH             1
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__MASK    0x00000004U
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__RESET             0
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field jumbo_frames */
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__SHIFT                        3
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__WIDTH                        1
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__MASK               0x00000008U
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__RESET                        0
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field copy_all_frames */
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__SHIFT                     4
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__WIDTH                     1
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__MASK            0x00000010U
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__RESET                     0
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field no_broadcast */
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__SHIFT                        5
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__WIDTH                        1
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__MASK               0x00000020U
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__RESET                        0
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field multicast_hash_enable */
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__SHIFT               6
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__WIDTH               1
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__MASK      0x00000040U
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__RESET               0
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field unicast_hash_enable */
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__SHIFT                 7
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__WIDTH                 1
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__MASK        0x00000080U
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__RESET                 0
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field receive_1536_byte_frames */
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SHIFT            8
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__WIDTH            1
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__MASK   0x00000100U
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__RESET            0
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000100U)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | (((uint32_t)(src) <<\
                    8) & 0x00000100U)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000100U)))
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field external_address_match_enable */
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__SHIFT       9
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__WIDTH       1
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__MASK \
                    0x00000200U
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__RESET       0
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field gigabit_mode_enable */
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SHIFT                10
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__WIDTH                 1
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__MASK        0x00000400U
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__RESET                 0
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000400U)
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | (((uint32_t)(src) <<\
                    10) & 0x00000400U)
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000400U)))
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field pcs_select */
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__SHIFT                         11
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__WIDTH                          1
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__MASK                 0x00000800U
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__RESET                          0
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field retry_test */
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__SHIFT                         12
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__WIDTH                          1
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__MASK                 0x00001000U
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__RESET                          0
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field pause_enable */
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__SHIFT                       13
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__WIDTH                        1
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__MASK               0x00002000U
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__RESET                        0
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field receive_buffer_offset */
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__SHIFT              14
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__WIDTH               2
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MASK      0x0000c000U
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__RESET               0
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000c000U) >> 14)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x0000c000U)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000c000U) | (((uint32_t)(src) <<\
                    14) & 0x0000c000U)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x0000c000U)))

/* macros for field length_field_error_frame_discard */
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SHIFT   16
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__WIDTH    1
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__MASK \
                    0x00010000U
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__RESET    0
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field fcs_remove */
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__SHIFT                         17
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__WIDTH                          1
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__MASK                 0x00020000U
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__RESET                          0
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00020000U) >> 17)
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field mdc_clock_division */
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__SHIFT                 18
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__WIDTH                  3
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__MASK         0x001c0000U
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__RESET                  2
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__READ(src) \
                    (((uint32_t)(src)\
                    & 0x001c0000U) >> 18)
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x001c0000U)
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x001c0000U) | (((uint32_t)(src) <<\
                    18) & 0x001c0000U)
#define EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x001c0000U)))

/* macros for field data_bus_width */
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__SHIFT                     21
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__WIDTH                      2
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__MASK             0x00600000U
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__RESET                      0
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00600000U) >> 21)
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__WRITE(src) \
                    (((uint32_t)(src)\
                    << 21) & 0x00600000U)
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00600000U) | (((uint32_t)(src) <<\
                    21) & 0x00600000U)
#define EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 21) & ~0x00600000U)))

/* macros for field disable_copy_of_pause_frames */
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SHIFT       23
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__WIDTH        1
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__MASK \
                    0x00800000U
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__RESET        0
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x00800000U)
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | (((uint32_t)(src) <<\
                    23) & 0x00800000U)
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x00800000U)))
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field receive_checksum_offload_enable */
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SHIFT    24
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__WIDTH     1
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__MASK \
                    0x01000000U
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__RESET     0
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field en_half_duplex_rx */
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SHIFT                  25
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__WIDTH                   1
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__MASK          0x02000000U
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__RESET                   0
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x02000000U) >> 25)
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x02000000U)
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | (((uint32_t)(src) <<\
                    25) & 0x02000000U)
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x02000000U)))
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field ignore_rx_fcs */
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__SHIFT                      26
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__WIDTH                       1
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__MASK              0x04000000U
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__RESET                       0
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x04000000U) >> 26)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x04000000U)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | (((uint32_t)(src) <<\
                    26) & 0x04000000U)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x04000000U)))
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field sgmii_mode_enable */
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__SHIFT                  27
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__WIDTH                   1
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__MASK          0x08000000U
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__RESET                   0
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 27) & 0x08000000U)
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | (((uint32_t)(src) <<\
                    27) & 0x08000000U)
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 27) & ~0x08000000U)))
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field ipg_stretch_enable */
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__SHIFT                 28
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__WIDTH                  1
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__MASK         0x10000000U
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__RESET                  0
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__NETWORK_CONFIG__IPG_STRETCH_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field nsp_change */
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__SHIFT                         29
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__WIDTH                          1
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__MASK                 0x20000000U
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__RESET                          0
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x20000000U) >> 29)
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field ignore_ipg_rx_er */
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__SHIFT                   30
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__WIDTH                    1
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__MASK           0x40000000U
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__RESET                    0
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0x40000000U)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | (((uint32_t)(src) <<\
                    30) & 0x40000000U)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0x40000000U)))
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field uni_direction_enable */
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SHIFT               31
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__WIDTH                1
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__MASK       0x80000000U
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__RESET                0
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__NETWORK_CONFIG__TYPE                                uint32_t
#define EMAC_REGS__NETWORK_CONFIG__READ                             0xffffffffU
#define EMAC_REGS__NETWORK_CONFIG__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__NETWORK_CONFIG_MACRO__ */


/* macros for network_config */
#define INST_NETWORK_CONFIG__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::network_status */
#ifndef __EMAC_REGS__NETWORK_STATUS_MACRO__
#define __EMAC_REGS__NETWORK_STATUS_MACRO__

/* macros for field pcs_link_state */
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__SHIFT                      0
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__WIDTH                      1
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__MASK             0x00000001U
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__RESET                      0
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field mdio_in */
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__SHIFT                             1
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__WIDTH                             1
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__MASK                    0x00000002U
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__RESET                             0
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__NETWORK_STATUS__MDIO_IN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field man_done */
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__SHIFT                            2
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__WIDTH                            1
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__MASK                   0x00000004U
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__RESET                            1
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__NETWORK_STATUS__MAN_DONE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field mac_full_duplex */
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__SHIFT                     3
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__WIDTH                     1
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__MASK            0x00000008U
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__RESET                     0
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field mac_pause_rx_en */
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__SHIFT                     4
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__WIDTH                     1
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__MASK            0x00000010U
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__RESET                     0
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field mac_pause_tx_en */
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__SHIFT                     5
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__WIDTH                     1
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__MASK            0x00000020U
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__RESET                     0
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field pfc_negotiate_pclk */
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__SHIFT                  6
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__WIDTH                  1
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__MASK         0x00000040U
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__RESET                  0
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__NETWORK_STATUS__PFC_NEGOTIATE_PCLK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field lpi_indicate_pclk */
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__SHIFT                   7
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__WIDTH                   1
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__MASK          0x00000080U
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__RESET                   0
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__NETWORK_STATUS__LPI_INDICATE_PCLK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_31_8 */
#define EMAC_REGS__NETWORK_STATUS__RESERVED_31_8__SHIFT                       8
#define EMAC_REGS__NETWORK_STATUS__RESERVED_31_8__WIDTH                      24
#define EMAC_REGS__NETWORK_STATUS__RESERVED_31_8__MASK              0xffffff00U
#define EMAC_REGS__NETWORK_STATUS__RESERVED_31_8__RESET                       0
#define EMAC_REGS__NETWORK_STATUS__RESERVED_31_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffff00U) >> 8)
#define EMAC_REGS__NETWORK_STATUS__TYPE                                uint32_t
#define EMAC_REGS__NETWORK_STATUS__READ                             0xffffffffU

#endif /* __EMAC_REGS__NETWORK_STATUS_MACRO__ */


/* macros for network_status */
#define INST_NETWORK_STATUS__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::user_io_register */
#ifndef __EMAC_REGS__USER_IO_REGISTER_MACRO__
#define __EMAC_REGS__USER_IO_REGISTER_MACRO__

/* macros for field user_programmable_outputs */
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__SHIFT         0
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__WIDTH        16
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__MASK \
                    0x0000ffffU
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__RESET         0
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field user_programmable_inputs */
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__SHIFT         16
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__WIDTH         16
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__MASK 0xffff0000U
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__RESET          0
#define EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__USER_IO_REGISTER__TYPE                              uint32_t
#define EMAC_REGS__USER_IO_REGISTER__READ                           0xffffffffU
#define EMAC_REGS__USER_IO_REGISTER__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__USER_IO_REGISTER_MACRO__ */


/* macros for user_io_register */
#define INST_USER_IO_REGISTER__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::dma_config */
#ifndef __EMAC_REGS__DMA_CONFIG_MACRO__
#define __EMAC_REGS__DMA_CONFIG_MACRO__

/* macros for field amba_burst_length */
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__SHIFT                       0
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__WIDTH                       5
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__MASK              0x0000001fU
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__RESET                       4
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000001fU)
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000001fU)
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000001fU) | ((uint32_t)(src) &\
                    0x0000001fU)
#define EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000001fU)))

/* macros for field hdr_data_splitting_en */
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__SHIFT                   5
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__WIDTH                   1
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__MASK          0x00000020U
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__RESET                 0b0
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field endian_swap_management */
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__SHIFT                  6
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__WIDTH                  1
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__MASK         0x00000040U
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__RESET                  1
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field endian_swap_packet */
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__SHIFT                      7
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__WIDTH                      1
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__MASK             0x00000080U
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__RESET                      1
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field rx_pbuf_size */
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__SHIFT                            8
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__WIDTH                            2
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__MASK                   0x00000300U
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__RESET                            3
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000300U) >> 8)
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000300U)
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000300U) | (((uint32_t)(src) <<\
                    8) & 0x00000300U)
#define EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000300U)))

/* macros for field tx_pbuf_size */
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__SHIFT                           10
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__WIDTH                            1
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__MASK                   0x00000400U
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__RESET                            1
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000400U)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | (((uint32_t)(src) <<\
                    10) & 0x00000400U)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000400U)))
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field tx_pbuf_tcp_en */
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SHIFT                         11
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__WIDTH                          1
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__MASK                 0x00000800U
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__RESET                          0
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field infinite_last_dbuf_size_en */
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__SHIFT             12
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__WIDTH              1
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__MASK     0x00001000U
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__RESET              0
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__DMA_CONFIG__INFINITE_LAST_DBUF_SIZE_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field crc_error_report */
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__SHIFT                       13
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__WIDTH                        1
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__MASK               0x00002000U
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__RESET                        0
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__DMA_CONFIG__CRC_ERROR_REPORT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field reserved_15_14 */
#define EMAC_REGS__DMA_CONFIG__RESERVED_15_14__SHIFT                         14
#define EMAC_REGS__DMA_CONFIG__RESERVED_15_14__WIDTH                          2
#define EMAC_REGS__DMA_CONFIG__RESERVED_15_14__MASK                 0x0000c000U
#define EMAC_REGS__DMA_CONFIG__RESERVED_15_14__RESET                          0
#define EMAC_REGS__DMA_CONFIG__RESERVED_15_14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000c000U) >> 14)

/* macros for field rx_buf_size */
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__SHIFT                            16
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__WIDTH                             8
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__MASK                    0x00ff0000U
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__RESET                             2
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field force_discard_on_err */
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__SHIFT                   24
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__WIDTH                    1
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__MASK           0x01000000U
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__RESET                    0
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field force_max_amba_burst_rx */
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__SHIFT                25
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__WIDTH                 1
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__MASK        0x02000000U
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__RESET                 0
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x02000000U) >> 25)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x02000000U)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | (((uint32_t)(src) <<\
                    25) & 0x02000000U)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x02000000U)))
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field force_max_amba_burst_tx */
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__SHIFT                26
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__WIDTH                 1
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__MASK        0x04000000U
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__RESET                 0
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x04000000U) >> 26)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x04000000U)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | (((uint32_t)(src) <<\
                    26) & 0x04000000U)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x04000000U)))
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field reserved_27 */
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__SHIFT                            27
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__WIDTH                             1
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__MASK                    0x08000000U
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__RESET                             0
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__DMA_CONFIG__RESERVED_27__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field rx_bd_extended_mode_en */
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__SHIFT                 28
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__WIDTH                  1
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__MASK         0x10000000U
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__RESET                  0
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field tx_bd_extended_mode_en */
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__SHIFT                 29
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__WIDTH                  1
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__MASK         0x20000000U
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__RESET                  0
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x20000000U) >> 29)
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field dma_addr_bus_width_1 */
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__SHIFT                   30
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__WIDTH                    1
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__MASK           0x40000000U
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__RESET                    0
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0x40000000U)
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | (((uint32_t)(src) <<\
                    30) & 0x40000000U)
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0x40000000U)))
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31 */
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__SHIFT                            31
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__WIDTH                             1
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__MASK                    0x80000000U
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__RESET                             0
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__DMA_CONFIG__RESERVED_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__DMA_CONFIG__TYPE                                    uint32_t
#define EMAC_REGS__DMA_CONFIG__READ                                 0xffffffffU
#define EMAC_REGS__DMA_CONFIG__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__DMA_CONFIG_MACRO__ */


/* macros for dma_config */
#define INST_DMA_CONFIG__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::transmit_status */
#ifndef __EMAC_REGS__TRANSMIT_STATUS_MACRO__
#define __EMAC_REGS__TRANSMIT_STATUS_MACRO__

/* macros for field used_bit_read */
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__SHIFT                      0
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__WIDTH                      1
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__MASK             0x00000001U
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__RESET                      0
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)

/* macros for field collision_occurred */
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__SHIFT                 1
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__WIDTH                 1
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__MASK        0x00000002U
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__RESET                 0
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)

/* macros for field retry_limit_exceeded */
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__SHIFT               2
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__WIDTH               1
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__MASK      0x00000004U
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__RESET               0
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)

/* macros for field transmit_go */
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__SHIFT                        3
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__WIDTH                        1
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__MASK               0x00000008U
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__RESET                        0
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field amba_error */
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__SHIFT                         4
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__WIDTH                         1
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__MASK                0x00000010U
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__RESET                         0
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)

/* macros for field transmit_complete */
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__SHIFT                  5
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__WIDTH                  1
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__MASK         0x00000020U
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__RESET                  0
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)

/* macros for field transmit_under_run */
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__SHIFT                 6
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__WIDTH                 1
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__MASK        0x00000040U
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__RESET                 0
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)

/* macros for field late_collision_occurred */
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__SHIFT            7
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__WIDTH            1
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__MASK   0x00000080U
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__RESET            0
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)

/* macros for field resp_not_ok */
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__SHIFT                        8
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__WIDTH                        1
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__MASK               0x00000100U
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__RESET                        0
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000100U)
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | (((uint32_t)(src) <<\
                    8) & 0x00000100U)
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000100U)))
#define EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)

/* macros for field reserved_31_9 */
#define EMAC_REGS__TRANSMIT_STATUS__RESERVED_31_9__SHIFT                      9
#define EMAC_REGS__TRANSMIT_STATUS__RESERVED_31_9__WIDTH                     23
#define EMAC_REGS__TRANSMIT_STATUS__RESERVED_31_9__MASK             0xfffffe00U
#define EMAC_REGS__TRANSMIT_STATUS__RESERVED_31_9__RESET                      0
#define EMAC_REGS__TRANSMIT_STATUS__RESERVED_31_9__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffe00U) >> 9)
#define EMAC_REGS__TRANSMIT_STATUS__TYPE                               uint32_t
#define EMAC_REGS__TRANSMIT_STATUS__READ                            0xffffffffU
#define EMAC_REGS__TRANSMIT_STATUS__WRITE                           0xffffffffU
#define EMAC_REGS__TRANSMIT_STATUS__WOCLR                           0x000001f7U

#endif /* __EMAC_REGS__TRANSMIT_STATUS_MACRO__ */


/* macros for transmit_status */
#define INST_TRANSMIT_STATUS__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::receive_q_ptr */
#ifndef __EMAC_REGS__RECEIVE_Q_PTR_MACRO__
#define __EMAC_REGS__RECEIVE_Q_PTR_MACRO__

/* macros for field dma_rx_dis_q */
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__SHIFT                         0
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__WIDTH                         1
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__MASK                0x00000001U
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__RESET                       0b0
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_DIS_Q__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_1_1 */
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__SHIFT                         1
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__WIDTH                         1
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__MASK                0x00000002U
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__RESET                       0b0
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__RECEIVE_Q_PTR__RESERVED_1_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field dma_rx_q_ptr */
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__SHIFT                         2
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__WIDTH                        30
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__MASK                0xfffffffcU
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__RESET                         0
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffffcU) >> 2)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0xfffffffcU)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xfffffffcU) | (((uint32_t)(src) <<\
                    2) & 0xfffffffcU)
#define EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0xfffffffcU)))
#define EMAC_REGS__RECEIVE_Q_PTR__TYPE                                 uint32_t
#define EMAC_REGS__RECEIVE_Q_PTR__READ                              0xffffffffU
#define EMAC_REGS__RECEIVE_Q_PTR__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__RECEIVE_Q_PTR_MACRO__ */


/* macros for receive_q_ptr */
#define INST_RECEIVE_Q_PTR__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::transmit_q_ptr */
#ifndef __EMAC_REGS__TRANSMIT_Q_PTR_MACRO__
#define __EMAC_REGS__TRANSMIT_Q_PTR_MACRO__

/* macros for field dma_tx_dis_q */
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__SHIFT                        0
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__WIDTH                        1
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__MASK               0x00000001U
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__RESET                      0b0
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_DIS_Q__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_1_1 */
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__SHIFT                        1
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__WIDTH                        1
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__MASK               0x00000002U
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__RESET                      0b0
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__TRANSMIT_Q_PTR__RESERVED_1_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field dma_tx_q_ptr */
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__SHIFT                        2
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__WIDTH                       30
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__MASK               0xfffffffcU
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__RESET                        0
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffffcU) >> 2)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0xfffffffcU)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xfffffffcU) | (((uint32_t)(src) <<\
                    2) & 0xfffffffcU)
#define EMAC_REGS__TRANSMIT_Q_PTR__DMA_TX_Q_PTR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0xfffffffcU)))
#define EMAC_REGS__TRANSMIT_Q_PTR__TYPE                                uint32_t
#define EMAC_REGS__TRANSMIT_Q_PTR__READ                             0xffffffffU
#define EMAC_REGS__TRANSMIT_Q_PTR__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__TRANSMIT_Q_PTR_MACRO__ */


/* macros for transmit_q_ptr */
#define INST_TRANSMIT_Q_PTR__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::receive_status */
#ifndef __EMAC_REGS__RECEIVE_STATUS_MACRO__
#define __EMAC_REGS__RECEIVE_STATUS_MACRO__

/* macros for field buffer_not_available */
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__SHIFT                0
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__WIDTH                1
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__MASK       0x00000001U
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__RESET                0
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)

/* macros for field frame_received */
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__SHIFT                      1
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__WIDTH                      1
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__MASK             0x00000002U
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__RESET                      0
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)

/* macros for field receive_overrun */
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__SHIFT                     2
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__WIDTH                     1
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__MASK            0x00000004U
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__RESET                     0
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)

/* macros for field resp_not_ok */
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__SHIFT                         3
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__WIDTH                         1
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__MASK                0x00000008U
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__RESET                         0
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)

/* macros for field reserved_31_4 */
#define EMAC_REGS__RECEIVE_STATUS__RESERVED_31_4__SHIFT                       4
#define EMAC_REGS__RECEIVE_STATUS__RESERVED_31_4__WIDTH                      28
#define EMAC_REGS__RECEIVE_STATUS__RESERVED_31_4__MASK              0xfffffff0U
#define EMAC_REGS__RECEIVE_STATUS__RESERVED_31_4__RESET                       0
#define EMAC_REGS__RECEIVE_STATUS__RESERVED_31_4__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffff0U) >> 4)
#define EMAC_REGS__RECEIVE_STATUS__TYPE                                uint32_t
#define EMAC_REGS__RECEIVE_STATUS__READ                             0xffffffffU
#define EMAC_REGS__RECEIVE_STATUS__WRITE                            0xffffffffU
#define EMAC_REGS__RECEIVE_STATUS__WOCLR                            0x0000000fU

#endif /* __EMAC_REGS__RECEIVE_STATUS_MACRO__ */


/* macros for receive_status */
#define INST_RECEIVE_STATUS__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_status */
#ifndef __EMAC_REGS__INT_STATUS_MACRO__
#define __EMAC_REGS__INT_STATUS_MACRO__

/* macros for field management_frame_sent */
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__SHIFT                   0
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__WIDTH                   1
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__MASK          0x00000001U
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__RESET                 0b0
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field receive_complete */
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__SHIFT                        1
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__WIDTH                        1
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__MASK               0x00000002U
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__RESET                      0b0
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field rx_used_bit_read */
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__SHIFT                        2
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__WIDTH                        1
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__MASK               0x00000004U
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__RESET                      0b0
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field tx_used_bit_read */
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__SHIFT                        3
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__WIDTH                        1
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__MASK               0x00000008U
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__RESET                      0b0
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field transmit_under_run */
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__SHIFT                      4
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__WIDTH                      1
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__MASK             0x00000010U
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__RESET                    0b0
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field retry_limit_exceeded_or_late_collision */
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__SHIFT  5
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__WIDTH  1
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__MASK \
                    0x00000020U
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__RESET \
                    0b0
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field amba_error */
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__SHIFT                              6
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__WIDTH                              1
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__MASK                     0x00000040U
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__RESET                            0b0
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_STATUS__AMBA_ERROR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field transmit_complete */
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__SHIFT                       7
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__WIDTH                       1
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__MASK              0x00000080U
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__RESET                     0b0
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_8 */
#define EMAC_REGS__INT_STATUS__RESERVED_8__SHIFT                              8
#define EMAC_REGS__INT_STATUS__RESERVED_8__WIDTH                              1
#define EMAC_REGS__INT_STATUS__RESERVED_8__MASK                     0x00000100U
#define EMAC_REGS__INT_STATUS__RESERVED_8__RESET                              0
#define EMAC_REGS__INT_STATUS__RESERVED_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__INT_STATUS__RESERVED_8__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__INT_STATUS__RESERVED_8__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field link_change */
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__SHIFT                             9
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__WIDTH                             1
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__MASK                    0x00000200U
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__RESET                           0b0
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__INT_STATUS__LINK_CHANGE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field receive_overrun */
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__SHIFT                        10
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__WIDTH                         1
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__MASK                0x00000400U
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__RESET                       0b0
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000400U)
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | (((uint32_t)(src) <<\
                    10) & 0x00000400U)
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000400U)))
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field resp_not_ok */
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__SHIFT                            11
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__WIDTH                             1
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__MASK                    0x00000800U
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__RESET                           0b0
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_STATUS__RESP_NOT_OK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field pause_frame_with_non_zero_pause_quantum_received */
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__SHIFT \
                    12
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__WIDTH \
                    1
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__MASK \
                    0x00001000U
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__RESET \
                    0b0
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field pause_time_elapsed */
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__SHIFT                     13
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__WIDTH                      1
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__MASK             0x00002000U
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__RESET                    0b0
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field pause_frame_transmitted */
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__SHIFT                14
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__WIDTH                 1
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__MASK        0x00004000U
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__RESET               0b0
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x00004000U)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | (((uint32_t)(src) <<\
                    14) & 0x00004000U)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x00004000U)))
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field external_interrupt */
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__SHIFT                     15
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__WIDTH                      1
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__MASK             0x00008000U
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__RESET                    0b0
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field pcs_auto_negotiation_complete */
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__SHIFT          16
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__WIDTH           1
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__MASK  0x00010000U
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__RESET         0b0
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field pcs_link_partner_page_received */
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__SHIFT         17
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__WIDTH          1
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__MASK 0x00020000U
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__RESET        0b0
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00020000U) >> 17)
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field ptp_delay_req_frame_received */
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__SHIFT           18
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__WIDTH            1
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__MASK   0x00040000U
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__RESET          0b0
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00040000U) >> 18)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field ptp_sync_frame_received */
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__SHIFT                19
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__WIDTH                 1
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__MASK        0x00080000U
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__RESET               0b0
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00080000U)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | (((uint32_t)(src) <<\
                    19) & 0x00080000U)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00080000U)))
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field ptp_delay_req_frame_transmitted */
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__SHIFT        20
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__WIDTH         1
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__MASK \
                    0x00100000U
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__RESET       0b0
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00100000U) >> 20)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00100000U)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | (((uint32_t)(src) <<\
                    20) & 0x00100000U)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00100000U)))
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field ptp_sync_frame_transmitted */
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__SHIFT             21
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__WIDTH              1
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__MASK     0x00200000U
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__RESET            0b0
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00200000U) >> 21)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 21) & 0x00200000U)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | (((uint32_t)(src) <<\
                    21) & 0x00200000U)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 21) & ~0x00200000U)))
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field ptp_pdelay_req_frame_received */
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__SHIFT          22
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__WIDTH           1
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__MASK  0x00400000U
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__RESET         0b0
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00400000U) >> 22)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 22) & 0x00400000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | (((uint32_t)(src) <<\
                    22) & 0x00400000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 22) & ~0x00400000U)))
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field ptp_pdelay_resp_frame_received */
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__SHIFT         23
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__WIDTH          1
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__MASK 0x00800000U
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__RESET        0b0
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x00800000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | (((uint32_t)(src) <<\
                    23) & 0x00800000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x00800000U)))
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field ptp_pdelay_req_frame_transmitted */
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__SHIFT       24
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__WIDTH        1
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__MASK \
                    0x01000000U
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__RESET      0b0
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field ptp_pdelay_resp_frame_transmitted */
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__SHIFT      25
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__WIDTH       1
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__MASK \
                    0x02000000U
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__RESET     0b0
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x02000000U) >> 25)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x02000000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | (((uint32_t)(src) <<\
                    25) & 0x02000000U)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x02000000U)))
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field tsu_seconds_register_increment */
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__SHIFT         26
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__WIDTH          1
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__MASK 0x04000000U
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__RESET        0b0
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x04000000U) >> 26)
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x04000000U)
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | (((uint32_t)(src) <<\
                    26) & 0x04000000U)
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x04000000U)))
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field receive_lpi_indication_status_bit_change */
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__SHIFT \
                    27
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__WIDTH \
                    1
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__MASK \
                    0x08000000U
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__RESET \
                    0b0
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 27) & 0x08000000U)
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | (((uint32_t)(src) <<\
                    27) & 0x08000000U)
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 27) & ~0x08000000U)))
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field wol_interrupt */
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__SHIFT                          28
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__WIDTH                           1
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__MASK                  0x10000000U
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__RESET                         0b0
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__INT_STATUS__WOL_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field tsu_timer_comparison_interrupt */
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__SHIFT         29
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__WIDTH          1
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__MASK 0x20000000U
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__RESET        0b0
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x20000000U) >> 29)
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field reserved_30_30 */
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__SHIFT                         30
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__WIDTH                          1
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__MASK                 0x40000000U
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__RESET                          0
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__INT_STATUS__RESERVED_30_30__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31_31 */
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__SHIFT                         31
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__WIDTH                          1
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__MASK                 0x80000000U
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__RESET                          0
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__INT_STATUS__RESERVED_31_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__INT_STATUS__TYPE                                    uint32_t
#define EMAC_REGS__INT_STATUS__READ                                 0xffffffffU
#define EMAC_REGS__INT_STATUS__RCLR                                 0x3ffffeffU
#define EMAC_REGS__INT_STATUS__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__INT_STATUS_MACRO__ */


/* macros for int_status */
#define INST_INT_STATUS__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_enable */
#ifndef __EMAC_REGS__INT_ENABLE_MACRO__
#define __EMAC_REGS__INT_ENABLE_MACRO__

/* macros for field enable_management_done_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__SHIFT        0
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__WIDTH        1
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__MASK \
                    0x00000001U
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__RESET        0
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field enable_receive_complete_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SHIFT       1
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__WIDTH       1
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__MASK \
                    0x00000002U
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__RESET       0
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field enable_receive_used_bit_read_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SHIFT  2
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__WIDTH  1
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__MASK \
                    0x00000004U
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__RESET  0
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field enable_transmit_used_bit_read_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SHIFT 3
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__WIDTH 1
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__MASK \
                    0x00000008U
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__RESET 0
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field enable_transmit_buffer_under_run_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SHIFT \
                    4
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__MASK \
                    0x00000010U
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field enable_retry_limit_exceeded_or_late_collision_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SHIFT \
                    5
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MASK \
                    0x00000020U
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field enable_transmit_frame_corruption_due_to_amba_error_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SHIFT \
                    6
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MASK \
                    0x00000040U
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field enable_transmit_complete_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SHIFT      7
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__WIDTH      1
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__MASK \
                    0x00000080U
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__RESET      0
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field not_used */
#define EMAC_REGS__INT_ENABLE__NOT_USED__SHIFT                                8
#define EMAC_REGS__INT_ENABLE__NOT_USED__WIDTH                                1
#define EMAC_REGS__INT_ENABLE__NOT_USED__MASK                       0x00000100U
#define EMAC_REGS__INT_ENABLE__NOT_USED__RESET                                0
#define EMAC_REGS__INT_ENABLE__NOT_USED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__INT_ENABLE__NOT_USED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__INT_ENABLE__NOT_USED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field enable_link_change_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__SHIFT            9
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__WIDTH            1
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__MASK   0x00000200U
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__RESET            0
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field enable_receive_overrun_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__SHIFT       10
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__WIDTH        1
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__MASK \
                    0x00000400U
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__RESET        0
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000400U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | (((uint32_t)(src) <<\
                    10) & 0x00000400U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000400U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field enable_resp_not_ok_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SHIFT           11
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__WIDTH            1
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__MASK   0x00000800U
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__RESET            0
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field enable_pause_frame_with_non_zero_pause_quantum_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SHIFT \
                    12
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__MASK \
                    0x00001000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field enable_pause_time_zero_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__SHIFT       13
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__WIDTH        1
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__MASK \
                    0x00002000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__RESET        0
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field enable_pause_frame_transmitted_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SHIFT \
                    14
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__MASK \
                    0x00004000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x00004000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | (((uint32_t)(src) <<\
                    14) & 0x00004000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x00004000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field enable_external_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__SHIFT              15
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__WIDTH               1
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__MASK      0x00008000U
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__RESET               0
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field enable_pcs_auto_negotiation_complete_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SHIFT \
                    16
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__MASK \
                    0x00010000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field enable_pcs_link_partner_page_received */
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SHIFT  17
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__WIDTH   1
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__MASK \
                    0x00020000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__RESET   0
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field enable_ptp_delay_req_frame_received */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SHIFT    18
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__WIDTH     1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__MASK \
                    0x00040000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__RESET     0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field enable_ptp_sync_frame_received */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__SHIFT         19
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__WIDTH          1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__MASK 0x00080000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__RESET          0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00080000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | (((uint32_t)(src) <<\
                    19) & 0x00080000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00080000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field enable_ptp_delay_req_frame_transmitted */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SHIFT 20
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__WIDTH  1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__MASK \
                    0x00100000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__RESET  0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00100000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | (((uint32_t)(src) <<\
                    20) & 0x00100000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00100000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field enable_ptp_sync_frame_transmitted */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__SHIFT      21
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__WIDTH       1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__MASK \
                    0x00200000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__RESET       0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 21) & 0x00200000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | (((uint32_t)(src) <<\
                    21) & 0x00200000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 21) & ~0x00200000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field enable_ptp_pdelay_req_frame_received */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SHIFT   22
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__WIDTH    1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__MASK \
                    0x00400000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__RESET    0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 22) & 0x00400000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | (((uint32_t)(src) <<\
                    22) & 0x00400000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 22) & ~0x00400000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field enable_ptp_pdelay_resp_frame_received */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SHIFT  23
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__WIDTH   1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__MASK \
                    0x00800000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__RESET   0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x00800000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | (((uint32_t)(src) <<\
                    23) & 0x00800000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x00800000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field enable_ptp_pdelay_req_frame_transmitted */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SHIFT \
                    24
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__WIDTH 1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__MASK \
                    0x01000000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__RESET 0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field enable_ptp_pdelay_resp_frame_transmitted */
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SHIFT \
                    25
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__WIDTH \
                    1
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__MASK \
                    0x02000000U
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__RESET \
                    0
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x02000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | (((uint32_t)(src) <<\
                    25) & 0x02000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x02000000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field enable_tsu_seconds_register_increment */
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__SHIFT  26
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__WIDTH   1
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__MASK \
                    0x04000000U
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__RESET   0
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x04000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | (((uint32_t)(src) <<\
                    26) & 0x04000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x04000000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field enable_rx_lpi_indication_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__SHIFT     27
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__WIDTH      1
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__MASK \
                    0x08000000U
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__RESET      0
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 27) & 0x08000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | (((uint32_t)(src) <<\
                    27) & 0x08000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 27) & ~0x08000000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field enable_wol_event_received_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__SHIFT    28
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__WIDTH     1
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__MASK \
                    0x10000000U
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__RESET     0
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field enable_tsu_timer_comparison_interrupt */
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__SHIFT  29
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__WIDTH   1
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__MASK \
                    0x20000000U
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__RESET 0b0
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field reserved_30_30 */
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__SHIFT                         30
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__WIDTH                          1
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__MASK                 0x40000000U
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__RESET                          0
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__INT_ENABLE__RESERVED_30_30__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31_31 */
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__SHIFT                         31
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__WIDTH                          1
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__MASK                 0x80000000U
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__RESET                          0
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__INT_ENABLE__RESERVED_31_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__INT_ENABLE__TYPE                                    uint32_t
#define EMAC_REGS__INT_ENABLE__READ                                 0xc0000100U
#define EMAC_REGS__INT_ENABLE__WRITE                                0xc0000100U

#endif /* __EMAC_REGS__INT_ENABLE_MACRO__ */


/* macros for int_enable */
#define INST_INT_ENABLE__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_disable */
#ifndef __EMAC_REGS__INT_DISABLE_MACRO__
#define __EMAC_REGS__INT_DISABLE_MACRO__

/* macros for field disable_management_done_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__SHIFT      0
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__WIDTH      1
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__MASK \
                    0x00000001U
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__RESET      0
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field disable_receive_complete_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SHIFT     1
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__WIDTH     1
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__MASK \
                    0x00000002U
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__RESET     0
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field disable_receive_used_bit_read_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SHIFT \
                    2
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__MASK \
                    0x00000004U
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field disable_transmit_used_bit_read_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SHIFT \
                    3
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__MASK \
                    0x00000008U
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field disable_transmit_buffer_under_run_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SHIFT \
                    4
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__MASK \
                    0x00000010U
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field disable_retry_limit_exceeded_or_late_collision_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SHIFT \
                    5
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MASK \
                    0x00000020U
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field disable_transmit_frame_corruption_due_to_amba_error_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SHIFT \
                    6
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MASK \
                    0x00000040U
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field disable_transmit_complete_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SHIFT    7
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__WIDTH    1
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__MASK \
                    0x00000080U
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__RESET    0
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field not_used */
#define EMAC_REGS__INT_DISABLE__NOT_USED__SHIFT                               8
#define EMAC_REGS__INT_DISABLE__NOT_USED__WIDTH                               1
#define EMAC_REGS__INT_DISABLE__NOT_USED__MASK                      0x00000100U
#define EMAC_REGS__INT_DISABLE__NOT_USED__RESET                               0
#define EMAC_REGS__INT_DISABLE__NOT_USED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__INT_DISABLE__NOT_USED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__INT_DISABLE__NOT_USED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field disable_link_change_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__SHIFT          9
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__WIDTH          1
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__MASK 0x00000200U
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__RESET          0
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field disable_receive_overrun_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__SHIFT     10
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__WIDTH      1
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__MASK \
                    0x00000400U
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__RESET      0
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000400U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | (((uint32_t)(src) <<\
                    10) & 0x00000400U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000400U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field disable_resp_not_ok_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SHIFT         11
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__WIDTH          1
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__MASK 0x00000800U
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__RESET          0
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field disable_pause_frame_with_non_zero_pause_quantum_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SHIFT \
                    12
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__MASK \
                    0x00001000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field disable_pause_time_zero_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__SHIFT     13
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__WIDTH      1
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__MASK \
                    0x00002000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__RESET      0
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field disable_pause_frame_transmitted_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SHIFT \
                    14
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__MASK \
                    0x00004000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x00004000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | (((uint32_t)(src) <<\
                    14) & 0x00004000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x00004000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field disable_external_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__SHIFT            15
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__WIDTH             1
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__MASK    0x00008000U
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__RESET             0
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field disable_pcs_auto_negotiation_complete_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SHIFT \
                    16
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__MASK \
                    0x00010000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field disable_pcs_link_partner_page_received */
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SHIFT \
                    17
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__WIDTH 1
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__MASK \
                    0x00020000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__RESET 0
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field disable_ptp_delay_req_frame_received */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SHIFT  18
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__WIDTH   1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__MASK \
                    0x00040000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__RESET   0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field disable_ptp_sync_frame_received */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__SHIFT       19
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__WIDTH        1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__MASK \
                    0x00080000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__RESET        0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00080000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | (((uint32_t)(src) <<\
                    19) & 0x00080000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00080000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field disable_ptp_delay_req_frame_transmitted */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SHIFT \
                    20
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__MASK \
                    0x00100000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00100000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | (((uint32_t)(src) <<\
                    20) & 0x00100000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00100000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field disable_ptp_sync_frame_transmitted */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__SHIFT    21
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__WIDTH     1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__MASK \
                    0x00200000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__RESET     0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 21) & 0x00200000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | (((uint32_t)(src) <<\
                    21) & 0x00200000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 21) & ~0x00200000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field disable_ptp_pdelay_req_frame_received */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SHIFT 22
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__WIDTH  1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__MASK \
                    0x00400000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__RESET  0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 22) & 0x00400000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | (((uint32_t)(src) <<\
                    22) & 0x00400000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 22) & ~0x00400000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field disable_ptp_pdelay_resp_frame_received */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SHIFT \
                    23
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__WIDTH 1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__MASK \
                    0x00800000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__RESET 0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x00800000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | (((uint32_t)(src) <<\
                    23) & 0x00800000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x00800000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field disable_ptp_pdelay_req_frame_transmitted */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SHIFT \
                    24
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__MASK \
                    0x01000000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field disable_ptp_pdelay_resp_frame_transmitted */
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SHIFT \
                    25
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__WIDTH \
                    1
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__MASK \
                    0x02000000U
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__RESET \
                    0
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x02000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | (((uint32_t)(src) <<\
                    25) & 0x02000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x02000000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field disable_tsu_seconds_register_increment */
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__SHIFT \
                    26
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__WIDTH 1
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__MASK \
                    0x04000000U
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__RESET 0
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x04000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | (((uint32_t)(src) <<\
                    26) & 0x04000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x04000000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field disable_rx_lpi_indication_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__SHIFT   27
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__WIDTH    1
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__MASK \
                    0x08000000U
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__RESET    0
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 27) & 0x08000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | (((uint32_t)(src) <<\
                    27) & 0x08000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 27) & ~0x08000000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field disable_wol_event_received_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__SHIFT  28
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__WIDTH   1
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__MASK \
                    0x10000000U
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__RESET   0
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field disable_tsu_timer_comparison_interrupt */
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__SHIFT \
                    29
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__WIDTH 1
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__MASK \
                    0x20000000U
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__RESET \
                    0b0
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field reserved_30_30 */
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__SHIFT                        30
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__WIDTH                         1
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__MASK                0x40000000U
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__RESET                         0
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__INT_DISABLE__RESERVED_30_30__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31_31 */
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__SHIFT                        31
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__WIDTH                         1
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__MASK                0x80000000U
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__RESET                         0
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__INT_DISABLE__RESERVED_31_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__INT_DISABLE__TYPE                                   uint32_t
#define EMAC_REGS__INT_DISABLE__READ                                0xc0000100U
#define EMAC_REGS__INT_DISABLE__WRITE                               0xc0000100U

#endif /* __EMAC_REGS__INT_DISABLE_MACRO__ */


/* macros for int_disable */
#define INST_INT_DISABLE__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_mask */
#ifndef __EMAC_REGS__INT_MASK_MACRO__
#define __EMAC_REGS__INT_MASK_MACRO__

/* macros for field management_done_interrupt_mask */
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__SHIFT            0
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__WIDTH            1
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__MASK   0x00000001U
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__RESET            1
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field receive_complete_interrupt_mask */
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__SHIFT           1
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__WIDTH           1
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__MASK  0x00000002U
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__RESET           1
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field receive_used_bit_read_interrupt_mask */
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__SHIFT      2
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__WIDTH      1
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__MASK \
                    0x00000004U
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__RESET      1
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field transmit_used_bit_read_interrupt_mask */
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__SHIFT     3
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__WIDTH     1
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__MASK \
                    0x00000008U
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__RESET     1
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field transmit_buffer_under_run_interrupt_mask */
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__SHIFT  4
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__WIDTH  1
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__MASK \
                    0x00000010U
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__RESET  1
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field retry_limit_exceeded_or_late_collision_mask */
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__SHIFT \
                    5
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__WIDTH \
                    1
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__MASK \
                    0x00000020U
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__RESET \
                    1
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field amba_error_interrupt_mask */
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__SHIFT                 6
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__WIDTH                 1
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__MASK        0x00000040U
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__RESET                 1
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field transmit_complete_interrupt_mask */
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__SHIFT          7
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__WIDTH          1
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__MASK 0x00000080U
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__RESET          1
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field not_used */
#define EMAC_REGS__INT_MASK__NOT_USED__SHIFT                                  8
#define EMAC_REGS__INT_MASK__NOT_USED__WIDTH                                  1
#define EMAC_REGS__INT_MASK__NOT_USED__MASK                         0x00000100U
#define EMAC_REGS__INT_MASK__NOT_USED__RESET                                  1
#define EMAC_REGS__INT_MASK__NOT_USED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__INT_MASK__NOT_USED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__INT_MASK__NOT_USED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field link_change_interrupt_mask */
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__SHIFT                9
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__WIDTH                1
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__MASK       0x00000200U
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__RESET                1
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field receive_overrun_interrupt_mask */
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__SHIFT           10
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__WIDTH            1
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__MASK   0x00000400U
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__RESET            1
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field resp_not_ok_interrupt_mask */
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__SHIFT               11
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__WIDTH                1
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__MASK       0x00000800U
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__RESET                1
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field pause_frame_with_non_zero_pause_quantum_interrupt_mask */
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__SHIFT \
                    12
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__WIDTH \
                    1
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__MASK \
                    0x00001000U
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__RESET \
                    1
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field pause_time_zero_interrupt_mask */
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__SHIFT           13
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__WIDTH            1
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__MASK   0x00002000U
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__RESET            1
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field pause_frame_transmitted_interrupt_mask */
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__SHIFT   14
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__WIDTH    1
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__MASK \
                    0x00004000U
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__RESET    1
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field external_interrupt_mask */
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__SHIFT                  15
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__WIDTH                   1
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__MASK          0x00008000U
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__RESET                   1
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field pcs_auto_negotiation_complete_interrupt_mask */
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__SHIFT \
                    16
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__WIDTH \
                    1
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__MASK \
                    0x00010000U
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__RESET \
                    1
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field pcs_link_partner_page_mask */
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__SHIFT               17
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__WIDTH                1
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__MASK       0x00020000U
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__RESET                1
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00020000U) >> 17)
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field ptp_delay_req_frame_received_mask */
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__SHIFT        18
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__WIDTH         1
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__MASK \
                    0x00040000U
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__RESET         1
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00040000U) >> 18)
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field ptp_sync_frame_received_mask */
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__SHIFT             19
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__WIDTH              1
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__MASK     0x00080000U
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__RESET              1
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field ptp_delay_req_frame_transmitted_mask */
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__SHIFT     20
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__WIDTH      1
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__MASK \
                    0x00100000U
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__RESET      1
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00100000U) >> 20)
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field ptp_sync_frame_transmitted_mask */
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__SHIFT          21
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__WIDTH           1
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__MASK  0x00200000U
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__RESET           1
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00200000U) >> 21)
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field ptp_pdelay_req_frame_received_mask */
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__SHIFT       22
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__WIDTH        1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__MASK \
                    0x00400000U
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__RESET        1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00400000U) >> 22)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field ptp_pdelay_resp_frame_received_mask */
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__SHIFT      23
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__WIDTH       1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__MASK \
                    0x00800000U
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__RESET       1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field ptp_pdelay_req_frame_transmitted_mask */
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__SHIFT    24
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__WIDTH     1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__MASK \
                    0x01000000U
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__RESET     1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field ptp_pdelay_resp_frame_transmitted_mask */
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__SHIFT   25
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__WIDTH    1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__MASK \
                    0x02000000U
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__RESET    1
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x02000000U) >> 25)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field tsu_seconds_register_increment_mask */
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__SHIFT      26
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__WIDTH       1
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__MASK \
                    0x04000000U
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__RESET       1
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x04000000U) >> 26)
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field rx_lpi_indication_mask */
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__SHIFT                   27
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__WIDTH                    1
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__MASK           0x08000000U
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__RESET                    1
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field wol_event_received_mask */
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__SHIFT                  28
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__WIDTH                   1
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__MASK          0x10000000U
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__RESET                   1
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field tsu_timer_comparison_mask */
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__SHIFT                29
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__WIDTH                 1
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__MASK        0x20000000U
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__RESET                 1
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x20000000U) >> 29)
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field reserved_30_30 */
#define EMAC_REGS__INT_MASK__RESERVED_30_30__SHIFT                           30
#define EMAC_REGS__INT_MASK__RESERVED_30_30__WIDTH                            1
#define EMAC_REGS__INT_MASK__RESERVED_30_30__MASK                   0x40000000U
#define EMAC_REGS__INT_MASK__RESERVED_30_30__RESET                            0
#define EMAC_REGS__INT_MASK__RESERVED_30_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__INT_MASK__RESERVED_30_30__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__INT_MASK__RESERVED_30_30__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31_31 */
#define EMAC_REGS__INT_MASK__RESERVED_31_31__SHIFT                           31
#define EMAC_REGS__INT_MASK__RESERVED_31_31__WIDTH                            1
#define EMAC_REGS__INT_MASK__RESERVED_31_31__MASK                   0x80000000U
#define EMAC_REGS__INT_MASK__RESERVED_31_31__RESET                            0
#define EMAC_REGS__INT_MASK__RESERVED_31_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__INT_MASK__RESERVED_31_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__INT_MASK__RESERVED_31_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__INT_MASK__TYPE                                      uint32_t
#define EMAC_REGS__INT_MASK__READ                                   0xffffffffU

#endif /* __EMAC_REGS__INT_MASK_MACRO__ */


/* macros for int_mask */
#define INST_INT_MASK__NUM                                                    1

/* macros for BlueprintGlobalNameSpace::emac_regs::phy_management */
#ifndef __EMAC_REGS__PHY_MANAGEMENT_MACRO__
#define __EMAC_REGS__PHY_MANAGEMENT_MACRO__

/* macros for field phy_write_read_data */
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__SHIFT                 0
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__WIDTH                16
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__MASK        0x0000ffffU
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__RESET                 0
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field write10 */
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__SHIFT                            16
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__WIDTH                             2
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__MASK                    0x00030000U
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__RESET                             0
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00030000U) >> 16)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00030000U)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00030000U) | (((uint32_t)(src) <<\
                    16) & 0x00030000U)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE10__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00030000U)))

/* macros for field register_address */
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__SHIFT                   18
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__WIDTH                    5
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__MASK           0x007c0000U
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__RESET                    0
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x007c0000U) >> 18)
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x007c0000U)
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x007c0000U) | (((uint32_t)(src) <<\
                    18) & 0x007c0000U)
#define EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x007c0000U)))

/* macros for field phy_address */
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__SHIFT                        23
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__WIDTH                         5
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__MASK                0x0f800000U
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__RESET                         0
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0f800000U) >> 23)
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x0f800000U)
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0f800000U) | (((uint32_t)(src) <<\
                    23) & 0x0f800000U)
#define EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x0f800000U)))

/* macros for field operation */
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__SHIFT                          28
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__WIDTH                           2
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__MASK                  0x30000000U
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__RESET                           0
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__READ(src) \
                    (((uint32_t)(src)\
                    & 0x30000000U) >> 28)
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x30000000U)
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x30000000U) | (((uint32_t)(src) <<\
                    28) & 0x30000000U)
#define EMAC_REGS__PHY_MANAGEMENT__OPERATION__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x30000000U)))

/* macros for field write1 */
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__SHIFT                             30
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__WIDTH                              1
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__MASK                     0x40000000U
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__RESET                              0
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0x40000000U)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | (((uint32_t)(src) <<\
                    30) & 0x40000000U)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0x40000000U)))
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field write0 */
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__SHIFT                             31
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__WIDTH                              1
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__MASK                     0x80000000U
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__RESET                              0
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__PHY_MANAGEMENT__WRITE0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__PHY_MANAGEMENT__TYPE                                uint32_t
#define EMAC_REGS__PHY_MANAGEMENT__READ                             0xffffffffU
#define EMAC_REGS__PHY_MANAGEMENT__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__PHY_MANAGEMENT_MACRO__ */


/* macros for phy_management */
#define INST_PHY_MANAGEMENT__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::pause_time */
#ifndef __EMAC_REGS__PAUSE_TIME_MACRO__
#define __EMAC_REGS__PAUSE_TIME_MACRO__

/* macros for field quantum */
#define EMAC_REGS__PAUSE_TIME__QUANTUM__SHIFT                                 0
#define EMAC_REGS__PAUSE_TIME__QUANTUM__WIDTH                                16
#define EMAC_REGS__PAUSE_TIME__QUANTUM__MASK                        0x0000ffffU
#define EMAC_REGS__PAUSE_TIME__QUANTUM__RESET                                 0
#define EMAC_REGS__PAUSE_TIME__QUANTUM__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PAUSE_TIME__RESERVED_31_16__SHIFT                         16
#define EMAC_REGS__PAUSE_TIME__RESERVED_31_16__WIDTH                         16
#define EMAC_REGS__PAUSE_TIME__RESERVED_31_16__MASK                 0xffff0000U
#define EMAC_REGS__PAUSE_TIME__RESERVED_31_16__RESET                          0
#define EMAC_REGS__PAUSE_TIME__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PAUSE_TIME__TYPE                                    uint32_t
#define EMAC_REGS__PAUSE_TIME__READ                                 0xffffffffU

#endif /* __EMAC_REGS__PAUSE_TIME_MACRO__ */


/* macros for pause_time */
#define INST_PAUSE_TIME__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_pause_quantum */
#ifndef __EMAC_REGS__TX_PAUSE_QUANTUM_MACRO__
#define __EMAC_REGS__TX_PAUSE_QUANTUM_MACRO__

/* macros for field quantum */
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__SHIFT                           0
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__WIDTH                          16
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__MASK                  0x0000ffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__RESET                      0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field quantum_p1 */
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__SHIFT                       16
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__WIDTH                       16
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__MASK               0xffff0000U
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__RESET                   0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffff0000U) | (((uint32_t)(src) <<\
                    16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0xffff0000U)))
#define EMAC_REGS__TX_PAUSE_QUANTUM__TYPE                              uint32_t
#define EMAC_REGS__TX_PAUSE_QUANTUM__READ                           0xffffffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__TX_PAUSE_QUANTUM_MACRO__ */


/* macros for tx_pause_quantum */
#define INST_TX_PAUSE_QUANTUM__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::pbuf_txcutthru */
#ifndef __EMAC_REGS__PBUF_TXCUTTHRU_MACRO__
#define __EMAC_REGS__PBUF_TXCUTTHRU_MACRO__

/* macros for field dma_tx_cutthru_threshold */
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__SHIFT            0
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__WIDTH           14
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__MASK   0x00003fffU
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__RESET        16383
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00003fffU)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00003fffU)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00003fffU) | ((uint32_t)(src) &\
                    0x00003fffU)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU_THRESHOLD__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00003fffU)))

/* macros for field reserved */
#define EMAC_REGS__PBUF_TXCUTTHRU__RESERVED__SHIFT                           14
#define EMAC_REGS__PBUF_TXCUTTHRU__RESERVED__WIDTH                           17
#define EMAC_REGS__PBUF_TXCUTTHRU__RESERVED__MASK                   0x7fffc000U
#define EMAC_REGS__PBUF_TXCUTTHRU__RESERVED__RESET                            0
#define EMAC_REGS__PBUF_TXCUTTHRU__RESERVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7fffc000U) >> 14)

/* macros for field dma_tx_cutthru */
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__SHIFT                     31
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__WIDTH                      1
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__MASK             0x80000000U
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__RESET                      0
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__PBUF_TXCUTTHRU__DMA_TX_CUTTHRU__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__PBUF_TXCUTTHRU__TYPE                                uint32_t
#define EMAC_REGS__PBUF_TXCUTTHRU__READ                             0xffffffffU
#define EMAC_REGS__PBUF_TXCUTTHRU__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__PBUF_TXCUTTHRU_MACRO__ */


/* macros for pbuf_txcutthru */
#define INST_PBUF_TXCUTTHRU__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::pbuf_rxcutthru */
#ifndef __EMAC_REGS__PBUF_RXCUTTHRU_MACRO__
#define __EMAC_REGS__PBUF_RXCUTTHRU_MACRO__

/* macros for field dma_rx_cutthru_threshold */
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__SHIFT            0
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__WIDTH           11
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__MASK   0x000007ffU
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__RESET         2047
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000007ffU)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000007ffU)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000007ffU) | ((uint32_t)(src) &\
                    0x000007ffU)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000007ffU)))

/* macros for field reserved */
#define EMAC_REGS__PBUF_RXCUTTHRU__RESERVED__SHIFT                           11
#define EMAC_REGS__PBUF_RXCUTTHRU__RESERVED__WIDTH                           20
#define EMAC_REGS__PBUF_RXCUTTHRU__RESERVED__MASK                   0x7ffff800U
#define EMAC_REGS__PBUF_RXCUTTHRU__RESERVED__RESET                            0
#define EMAC_REGS__PBUF_RXCUTTHRU__RESERVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7ffff800U) >> 11)

/* macros for field dma_rx_cutthru */
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__SHIFT                     31
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__WIDTH                      1
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__MASK             0x80000000U
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__RESET                      0
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__PBUF_RXCUTTHRU__TYPE                                uint32_t
#define EMAC_REGS__PBUF_RXCUTTHRU__READ                             0xffffffffU
#define EMAC_REGS__PBUF_RXCUTTHRU__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__PBUF_RXCUTTHRU_MACRO__ */


/* macros for pbuf_rxcutthru */
#define INST_PBUF_RXCUTTHRU__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::jumbo_max_length */
#ifndef __EMAC_REGS__JUMBO_MAX_LENGTH_MACRO__
#define __EMAC_REGS__JUMBO_MAX_LENGTH_MACRO__

/* macros for field jumbo_max_length */
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__SHIFT                  0
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__WIDTH                 14
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__MASK         0x00003fffU
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__RESET              10240
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00003fffU)
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00003fffU)
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00003fffU) | ((uint32_t)(src) &\
                    0x00003fffU)
#define EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00003fffU)))

/* macros for field reserved_31_14 */
#define EMAC_REGS__JUMBO_MAX_LENGTH__RESERVED_31_14__SHIFT                   14
#define EMAC_REGS__JUMBO_MAX_LENGTH__RESERVED_31_14__WIDTH                   18
#define EMAC_REGS__JUMBO_MAX_LENGTH__RESERVED_31_14__MASK           0xffffc000U
#define EMAC_REGS__JUMBO_MAX_LENGTH__RESERVED_31_14__RESET                    0
#define EMAC_REGS__JUMBO_MAX_LENGTH__RESERVED_31_14__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffc000U) >> 14)
#define EMAC_REGS__JUMBO_MAX_LENGTH__TYPE                              uint32_t
#define EMAC_REGS__JUMBO_MAX_LENGTH__READ                           0xffffffffU
#define EMAC_REGS__JUMBO_MAX_LENGTH__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__JUMBO_MAX_LENGTH_MACRO__ */


/* macros for jumbo_max_length */
#define INST_JUMBO_MAX_LENGTH__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::external_fifo_interface */
#ifndef __EMAC_REGS__EXTERNAL_FIFO_INTERFACE_MACRO__
#define __EMAC_REGS__EXTERNAL_FIFO_INTERFACE_MACRO__

/* macros for field external_fifo_interface */
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__SHIFT    0
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__WIDTH    1
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__MASK \
                    0x00000001U
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__RESET    0
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__EXTERNAL_FIFO_INTERFACE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_31_1 */
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__RESERVED_31_1__SHIFT              1
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__RESERVED_31_1__WIDTH             31
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__RESERVED_31_1__MASK     0xfffffffeU
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__RESERVED_31_1__RESET              0
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__RESERVED_31_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffffeU) >> 1)
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__TYPE                       uint32_t
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__READ                    0xffffffffU
#define EMAC_REGS__EXTERNAL_FIFO_INTERFACE__WRITE                   0xffffffffU

#endif /* __EMAC_REGS__EXTERNAL_FIFO_INTERFACE_MACRO__ */


/* macros for external_fifo_interface */
#define INST_EXTERNAL_FIFO_INTERFACE__NUM                                     1

/* macros for BlueprintGlobalNameSpace::emac_regs::axi_max_pipeline */
#ifndef __EMAC_REGS__AXI_MAX_PIPELINE_MACRO__
#define __EMAC_REGS__AXI_MAX_PIPELINE_MACRO__

/* macros for field ar2r_max_pipeline */
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__SHIFT                 0
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__WIDTH                 8
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__MASK        0x000000ffU
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__RESET                 1
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field aw2w_max_pipeline */
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__SHIFT                 8
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__WIDTH                 8
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__MASK        0x0000ff00U
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__RESET                 1
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field use_aw2b_fill */
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__SHIFT                    16
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__WIDTH                     1
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__MASK            0x00010000U
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__RESET                     0
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__AXI_MAX_PIPELINE__USE_AW2B_FILL__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field reserved */
#define EMAC_REGS__AXI_MAX_PIPELINE__RESERVED__SHIFT                         17
#define EMAC_REGS__AXI_MAX_PIPELINE__RESERVED__WIDTH                         15
#define EMAC_REGS__AXI_MAX_PIPELINE__RESERVED__MASK                 0xfffe0000U
#define EMAC_REGS__AXI_MAX_PIPELINE__RESERVED__RESET                          0
#define EMAC_REGS__AXI_MAX_PIPELINE__RESERVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__AXI_MAX_PIPELINE__TYPE                              uint32_t
#define EMAC_REGS__AXI_MAX_PIPELINE__READ                           0xffffffffU
#define EMAC_REGS__AXI_MAX_PIPELINE__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__AXI_MAX_PIPELINE_MACRO__ */


/* macros for axi_max_pipeline */
#define INST_AXI_MAX_PIPELINE__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::rsc_control */
#ifndef __EMAC_REGS__RSC_CONTROL_MACRO__
#define __EMAC_REGS__RSC_CONTROL_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__SHIFT                             0
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__WIDTH                             1
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__MASK                    0x00000001U
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__RESET                             0
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__RSC_CONTROL__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field rsc_control */
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__SHIFT                            1
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__WIDTH                           15
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__MASK                   0x0000fffeU
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__RESET                            0
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000fffeU) >> 1)
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x0000fffeU)
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000fffeU) | (((uint32_t)(src) <<\
                    1) & 0x0000fffeU)
#define EMAC_REGS__RSC_CONTROL__RSC_CONTROL__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x0000fffeU)))

/* macros for field rsc_clr_mask */
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__SHIFT                          16
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__WIDTH                           1
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__MASK                  0x00010000U
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__RESET                           0
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__RSC_CONTROL__RSC_CLR_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field reserved_31_17 */
#define EMAC_REGS__RSC_CONTROL__RESERVED_31_17__SHIFT                        17
#define EMAC_REGS__RSC_CONTROL__RESERVED_31_17__WIDTH                        15
#define EMAC_REGS__RSC_CONTROL__RESERVED_31_17__MASK                0xfffe0000U
#define EMAC_REGS__RSC_CONTROL__RESERVED_31_17__RESET                         0
#define EMAC_REGS__RSC_CONTROL__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__RSC_CONTROL__TYPE                                   uint32_t
#define EMAC_REGS__RSC_CONTROL__READ                                0xffffffffU
#define EMAC_REGS__RSC_CONTROL__WRITE                               0xffffffffU

#endif /* __EMAC_REGS__RSC_CONTROL_MACRO__ */


/* macros for rsc_control */
#define INST_RSC_CONTROL__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_moderation */
#ifndef __EMAC_REGS__INT_MODERATION_MACRO__
#define __EMAC_REGS__INT_MODERATION_MACRO__

/* macros for field rx_int_moderation */
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__SHIFT                   0
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__WIDTH                   8
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__MASK          0x000000ffU
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__RESET                   0
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field reserved_15_8 */
#define EMAC_REGS__INT_MODERATION__RESERVED_15_8__SHIFT                       8
#define EMAC_REGS__INT_MODERATION__RESERVED_15_8__WIDTH                       8
#define EMAC_REGS__INT_MODERATION__RESERVED_15_8__MASK              0x0000ff00U
#define EMAC_REGS__INT_MODERATION__RESERVED_15_8__RESET                       0
#define EMAC_REGS__INT_MODERATION__RESERVED_15_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)

/* macros for field tx_int_moderation */
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__SHIFT                  16
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__WIDTH                   8
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__MASK          0x00ff0000U
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__RESET                   0
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field reserved_31_24 */
#define EMAC_REGS__INT_MODERATION__RESERVED_31_24__SHIFT                     24
#define EMAC_REGS__INT_MODERATION__RESERVED_31_24__WIDTH                      8
#define EMAC_REGS__INT_MODERATION__RESERVED_31_24__MASK             0xff000000U
#define EMAC_REGS__INT_MODERATION__RESERVED_31_24__RESET                      0
#define EMAC_REGS__INT_MODERATION__RESERVED_31_24__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__INT_MODERATION__TYPE                                uint32_t
#define EMAC_REGS__INT_MODERATION__READ                             0xffffffffU
#define EMAC_REGS__INT_MODERATION__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__INT_MODERATION_MACRO__ */


/* macros for int_moderation */
#define INST_INT_MODERATION__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::sys_wake_time */
#ifndef __EMAC_REGS__SYS_WAKE_TIME_MACRO__
#define __EMAC_REGS__SYS_WAKE_TIME_MACRO__

/* macros for field sys_wake_time */
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__SHIFT                        0
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__WIDTH                       16
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__MASK               0x0000ffffU
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__RESET                        0
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SYS_WAKE_TIME__SYS_WAKE_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__SYS_WAKE_TIME__RESERVED_31_16__SHIFT                      16
#define EMAC_REGS__SYS_WAKE_TIME__RESERVED_31_16__WIDTH                      16
#define EMAC_REGS__SYS_WAKE_TIME__RESERVED_31_16__MASK              0xffff0000U
#define EMAC_REGS__SYS_WAKE_TIME__RESERVED_31_16__RESET                       0
#define EMAC_REGS__SYS_WAKE_TIME__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__SYS_WAKE_TIME__TYPE                                 uint32_t
#define EMAC_REGS__SYS_WAKE_TIME__READ                              0xffffffffU
#define EMAC_REGS__SYS_WAKE_TIME__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__SYS_WAKE_TIME_MACRO__ */


/* macros for sys_wake_time */
#define INST_SYS_WAKE_TIME__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::hash_bottom */
#ifndef __EMAC_REGS__HASH_BOTTOM_MACRO__
#define __EMAC_REGS__HASH_BOTTOM_MACRO__

/* macros for field address */
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__SHIFT                                0
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__WIDTH                               32
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__MASK                       0xffffffffU
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__RESET                                0
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__HASH_BOTTOM__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__HASH_BOTTOM__TYPE                                   uint32_t
#define EMAC_REGS__HASH_BOTTOM__READ                                0xffffffffU
#define EMAC_REGS__HASH_BOTTOM__WRITE                               0xffffffffU

#endif /* __EMAC_REGS__HASH_BOTTOM_MACRO__ */


/* macros for hash_bottom */
#define INST_HASH_BOTTOM__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::hash_top */
#ifndef __EMAC_REGS__HASH_TOP_MACRO__
#define __EMAC_REGS__HASH_TOP_MACRO__

/* macros for field address */
#define EMAC_REGS__HASH_TOP__ADDRESS__SHIFT                                   0
#define EMAC_REGS__HASH_TOP__ADDRESS__WIDTH                                  32
#define EMAC_REGS__HASH_TOP__ADDRESS__MASK                          0xffffffffU
#define EMAC_REGS__HASH_TOP__ADDRESS__RESET                                   0
#define EMAC_REGS__HASH_TOP__ADDRESS__READ(src) ((uint32_t)(src) & 0xffffffffU)
#define EMAC_REGS__HASH_TOP__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__HASH_TOP__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__HASH_TOP__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__HASH_TOP__TYPE                                      uint32_t
#define EMAC_REGS__HASH_TOP__READ                                   0xffffffffU
#define EMAC_REGS__HASH_TOP__WRITE                                  0xffffffffU

#endif /* __EMAC_REGS__HASH_TOP_MACRO__ */


/* macros for hash_top */
#define INST_HASH_TOP__NUM                                                    1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_add_bottom */
#ifndef __EMAC_REGS__SPEC_ADD_BOTTOM_MACRO__
#define __EMAC_REGS__SPEC_ADD_BOTTOM_MACRO__

/* macros for field address */
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__SHIFT                            0
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__WIDTH                           32
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__MASK                   0xffffffffU
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__RESET                            0
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__SPEC_ADD_BOTTOM__TYPE                               uint32_t
#define EMAC_REGS__SPEC_ADD_BOTTOM__READ                            0xffffffffU
#define EMAC_REGS__SPEC_ADD_BOTTOM__WRITE                           0xffffffffU

#endif /* __EMAC_REGS__SPEC_ADD_BOTTOM_MACRO__ */


/* macros for spec_add1_bottom */
#define INST_SPEC_ADD1_BOTTOM__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_add_top_no_mask */
#ifndef __EMAC_REGS__SPEC_ADD_TOP_NO_MASK_MACRO__
#define __EMAC_REGS__SPEC_ADD_TOP_NO_MASK_MACRO__

/* macros for field address */
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__SHIFT                       0
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__WIDTH                      16
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__MASK              0x0000ffffU
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__RESET                       0
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field filter_type */
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__SHIFT                  16
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__WIDTH                   1
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__MASK          0x00010000U
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__RESET                   0
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field reserved_31_17 */
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__RESERVED_31_17__SHIFT               17
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__RESERVED_31_17__WIDTH               15
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__RESERVED_31_17__MASK       0xfffe0000U
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__RESERVED_31_17__RESET                0
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__TYPE                          uint32_t
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__READ                       0xffffffffU
#define EMAC_REGS__SPEC_ADD_TOP_NO_MASK__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__SPEC_ADD_TOP_NO_MASK_MACRO__ */


/* macros for spec_add1_top */
#define INST_SPEC_ADD1_TOP__NUM                                               1

/* macros for spec_add2_bottom */
#define INST_SPEC_ADD2_BOTTOM__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_add_top */
#ifndef __EMAC_REGS__SPEC_ADD_TOP_MACRO__
#define __EMAC_REGS__SPEC_ADD_TOP_MACRO__

/* macros for field address */
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__SHIFT                               0
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__WIDTH                              16
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__MASK                      0x0000ffffU
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__RESET                               0
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SPEC_ADD_TOP__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field filter_type */
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__SHIFT                          16
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__WIDTH                           1
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__MASK                  0x00010000U
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__RESET                           0
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field reserved_23_17 */
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_23_17__SHIFT                       17
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_23_17__WIDTH                        7
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_23_17__MASK               0x00fe0000U
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_23_17__RESET                        0
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_23_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00fe0000U) >> 17)

/* macros for field filter_byte_mask */
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__SHIFT                     24
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__WIDTH                      6
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__MASK             0x3f000000U
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__RESET                      0
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x3f000000U) >> 24)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x3f000000U)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3f000000U) | (((uint32_t)(src) <<\
                    24) & 0x3f000000U)
#define EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x3f000000U)))

/* macros for field reserved_31_30 */
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_31_30__SHIFT                       30
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_31_30__WIDTH                        2
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_31_30__MASK               0xc0000000U
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_31_30__RESET                        0
#define EMAC_REGS__SPEC_ADD_TOP__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__SPEC_ADD_TOP__TYPE                                  uint32_t
#define EMAC_REGS__SPEC_ADD_TOP__READ                               0xffffffffU
#define EMAC_REGS__SPEC_ADD_TOP__WRITE                              0xffffffffU

#endif /* __EMAC_REGS__SPEC_ADD_TOP_MACRO__ */


/* macros for spec_add2_top */
#define INST_SPEC_ADD2_TOP__NUM                                               1

/* macros for spec_add3_bottom */
#define INST_SPEC_ADD3_BOTTOM__NUM                                            1

/* macros for spec_add3_top */
#define INST_SPEC_ADD3_TOP__NUM                                               1

/* macros for spec_add4_bottom */
#define INST_SPEC_ADD4_BOTTOM__NUM                                            1

/* macros for spec_add4_top */
#define INST_SPEC_ADD4_TOP__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_type1 */
#ifndef __EMAC_REGS__SPEC_TYPE1_MACRO__
#define __EMAC_REGS__SPEC_TYPE1_MACRO__

/* macros for field match */
#define EMAC_REGS__SPEC_TYPE1__MATCH__SHIFT                                   0
#define EMAC_REGS__SPEC_TYPE1__MATCH__WIDTH                                  16
#define EMAC_REGS__SPEC_TYPE1__MATCH__MASK                          0x0000ffffU
#define EMAC_REGS__SPEC_TYPE1__MATCH__RESET                                   0
#define EMAC_REGS__SPEC_TYPE1__MATCH__READ(src) ((uint32_t)(src) & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE1__MATCH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE1__MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE1__MATCH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_30_16 */
#define EMAC_REGS__SPEC_TYPE1__RESERVED_30_16__SHIFT                         16
#define EMAC_REGS__SPEC_TYPE1__RESERVED_30_16__WIDTH                         15
#define EMAC_REGS__SPEC_TYPE1__RESERVED_30_16__MASK                 0x7fff0000U
#define EMAC_REGS__SPEC_TYPE1__RESERVED_30_16__RESET                          0
#define EMAC_REGS__SPEC_TYPE1__RESERVED_30_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7fff0000U) >> 16)

/* macros for field enable_copy */
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__SHIFT                            31
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__WIDTH                             1
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__MASK                    0x80000000U
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__RESET                             0
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__SPEC_TYPE1__TYPE                                    uint32_t
#define EMAC_REGS__SPEC_TYPE1__READ                                 0xffffffffU
#define EMAC_REGS__SPEC_TYPE1__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__SPEC_TYPE1_MACRO__ */


/* macros for spec_type1 */
#define INST_SPEC_TYPE1__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_type2 */
#ifndef __EMAC_REGS__SPEC_TYPE2_MACRO__
#define __EMAC_REGS__SPEC_TYPE2_MACRO__

/* macros for field match */
#define EMAC_REGS__SPEC_TYPE2__MATCH__SHIFT                                   0
#define EMAC_REGS__SPEC_TYPE2__MATCH__WIDTH                                  16
#define EMAC_REGS__SPEC_TYPE2__MATCH__MASK                          0x0000ffffU
#define EMAC_REGS__SPEC_TYPE2__MATCH__RESET                                   0
#define EMAC_REGS__SPEC_TYPE2__MATCH__READ(src) ((uint32_t)(src) & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE2__MATCH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE2__MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE2__MATCH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_30_16 */
#define EMAC_REGS__SPEC_TYPE2__RESERVED_30_16__SHIFT                         16
#define EMAC_REGS__SPEC_TYPE2__RESERVED_30_16__WIDTH                         15
#define EMAC_REGS__SPEC_TYPE2__RESERVED_30_16__MASK                 0x7fff0000U
#define EMAC_REGS__SPEC_TYPE2__RESERVED_30_16__RESET                          0
#define EMAC_REGS__SPEC_TYPE2__RESERVED_30_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7fff0000U) >> 16)

/* macros for field enable_copy */
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__SHIFT                            31
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__WIDTH                             1
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__MASK                    0x80000000U
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__RESET                             0
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__SPEC_TYPE2__TYPE                                    uint32_t
#define EMAC_REGS__SPEC_TYPE2__READ                                 0xffffffffU
#define EMAC_REGS__SPEC_TYPE2__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__SPEC_TYPE2_MACRO__ */


/* macros for spec_type2 */
#define INST_SPEC_TYPE2__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_type3 */
#ifndef __EMAC_REGS__SPEC_TYPE3_MACRO__
#define __EMAC_REGS__SPEC_TYPE3_MACRO__

/* macros for field match */
#define EMAC_REGS__SPEC_TYPE3__MATCH__SHIFT                                   0
#define EMAC_REGS__SPEC_TYPE3__MATCH__WIDTH                                  16
#define EMAC_REGS__SPEC_TYPE3__MATCH__MASK                          0x0000ffffU
#define EMAC_REGS__SPEC_TYPE3__MATCH__RESET                                   0
#define EMAC_REGS__SPEC_TYPE3__MATCH__READ(src) ((uint32_t)(src) & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE3__MATCH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE3__MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE3__MATCH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_30_16 */
#define EMAC_REGS__SPEC_TYPE3__RESERVED_30_16__SHIFT                         16
#define EMAC_REGS__SPEC_TYPE3__RESERVED_30_16__WIDTH                         15
#define EMAC_REGS__SPEC_TYPE3__RESERVED_30_16__MASK                 0x7fff0000U
#define EMAC_REGS__SPEC_TYPE3__RESERVED_30_16__RESET                          0
#define EMAC_REGS__SPEC_TYPE3__RESERVED_30_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7fff0000U) >> 16)

/* macros for field enable_copy */
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__SHIFT                            31
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__WIDTH                             1
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__MASK                    0x80000000U
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__RESET                             0
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__SPEC_TYPE3__TYPE                                    uint32_t
#define EMAC_REGS__SPEC_TYPE3__READ                                 0xffffffffU
#define EMAC_REGS__SPEC_TYPE3__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__SPEC_TYPE3_MACRO__ */


/* macros for spec_type3 */
#define INST_SPEC_TYPE3__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::spec_type4 */
#ifndef __EMAC_REGS__SPEC_TYPE4_MACRO__
#define __EMAC_REGS__SPEC_TYPE4_MACRO__

/* macros for field match */
#define EMAC_REGS__SPEC_TYPE4__MATCH__SHIFT                                   0
#define EMAC_REGS__SPEC_TYPE4__MATCH__WIDTH                                  16
#define EMAC_REGS__SPEC_TYPE4__MATCH__MASK                          0x0000ffffU
#define EMAC_REGS__SPEC_TYPE4__MATCH__RESET                                   0
#define EMAC_REGS__SPEC_TYPE4__MATCH__READ(src) ((uint32_t)(src) & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE4__MATCH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE4__MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SPEC_TYPE4__MATCH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_30_16 */
#define EMAC_REGS__SPEC_TYPE4__RESERVED_30_16__SHIFT                         16
#define EMAC_REGS__SPEC_TYPE4__RESERVED_30_16__WIDTH                         15
#define EMAC_REGS__SPEC_TYPE4__RESERVED_30_16__MASK                 0x7fff0000U
#define EMAC_REGS__SPEC_TYPE4__RESERVED_30_16__RESET                          0
#define EMAC_REGS__SPEC_TYPE4__RESERVED_30_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7fff0000U) >> 16)

/* macros for field enable_copy */
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__SHIFT                            31
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__WIDTH                             1
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__MASK                    0x80000000U
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__RESET                             0
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__SPEC_TYPE4__TYPE                                    uint32_t
#define EMAC_REGS__SPEC_TYPE4__READ                                 0xffffffffU
#define EMAC_REGS__SPEC_TYPE4__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__SPEC_TYPE4_MACRO__ */


/* macros for spec_type4 */
#define INST_SPEC_TYPE4__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::wol_register */
#ifndef __EMAC_REGS__WOL_REGISTER_MACRO__
#define __EMAC_REGS__WOL_REGISTER_MACRO__

/* macros for field addr */
#define EMAC_REGS__WOL_REGISTER__ADDR__SHIFT                                  0
#define EMAC_REGS__WOL_REGISTER__ADDR__WIDTH                                 16
#define EMAC_REGS__WOL_REGISTER__ADDR__MASK                         0x0000ffffU
#define EMAC_REGS__WOL_REGISTER__ADDR__RESET                                  0
#define EMAC_REGS__WOL_REGISTER__ADDR__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__WOL_REGISTER__ADDR__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__WOL_REGISTER__ADDR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__WOL_REGISTER__ADDR__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field wol_mask_0 */
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__SHIFT                           16
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__WIDTH                            1
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__MASK                   0x00010000U
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__RESET                            0
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00010000U) >> 16)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field wol_mask_1 */
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__SHIFT                           17
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__WIDTH                            1
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__MASK                   0x00020000U
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__RESET                            0
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00020000U) >> 17)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field wol_mask_2 */
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__SHIFT                           18
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__WIDTH                            1
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__MASK                   0x00040000U
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__RESET                            0
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00040000U) >> 18)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_2__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field wol_mask_3 */
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__SHIFT                           19
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__WIDTH                            1
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__MASK                   0x00080000U
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__RESET                            0
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00080000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | (((uint32_t)(src) <<\
                    19) & 0x00080000U)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00080000U)))
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__WOL_REGISTER__WOL_MASK_3__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field reserved_31_20 */
#define EMAC_REGS__WOL_REGISTER__RESERVED_31_20__SHIFT                       20
#define EMAC_REGS__WOL_REGISTER__RESERVED_31_20__WIDTH                       12
#define EMAC_REGS__WOL_REGISTER__RESERVED_31_20__MASK               0xfff00000U
#define EMAC_REGS__WOL_REGISTER__RESERVED_31_20__RESET                        0
#define EMAC_REGS__WOL_REGISTER__RESERVED_31_20__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfff00000U) >> 20)
#define EMAC_REGS__WOL_REGISTER__TYPE                                  uint32_t
#define EMAC_REGS__WOL_REGISTER__READ                               0xffffffffU
#define EMAC_REGS__WOL_REGISTER__WRITE                              0xffffffffU

#endif /* __EMAC_REGS__WOL_REGISTER_MACRO__ */


/* macros for wol_register */
#define INST_WOL_REGISTER__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::stretch_ratio */
#ifndef __EMAC_REGS__STRETCH_RATIO_MACRO__
#define __EMAC_REGS__STRETCH_RATIO_MACRO__

/* macros for field ipg_stretch */
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__SHIFT                          0
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__WIDTH                         16
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__MASK                 0x0000ffffU
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__RESET                          0
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__STRETCH_RATIO__IPG_STRETCH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__STRETCH_RATIO__RESERVED_31_16__SHIFT                      16
#define EMAC_REGS__STRETCH_RATIO__RESERVED_31_16__WIDTH                      16
#define EMAC_REGS__STRETCH_RATIO__RESERVED_31_16__MASK              0xffff0000U
#define EMAC_REGS__STRETCH_RATIO__RESERVED_31_16__RESET                       0
#define EMAC_REGS__STRETCH_RATIO__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__STRETCH_RATIO__TYPE                                 uint32_t
#define EMAC_REGS__STRETCH_RATIO__READ                              0xffffffffU
#define EMAC_REGS__STRETCH_RATIO__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__STRETCH_RATIO_MACRO__ */


/* macros for stretch_ratio */
#define INST_STRETCH_RATIO__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::stacked_vlan */
#ifndef __EMAC_REGS__STACKED_VLAN_MACRO__
#define __EMAC_REGS__STACKED_VLAN_MACRO__

/* macros for field match */
#define EMAC_REGS__STACKED_VLAN__MATCH__SHIFT                                 0
#define EMAC_REGS__STACKED_VLAN__MATCH__WIDTH                                16
#define EMAC_REGS__STACKED_VLAN__MATCH__MASK                        0x0000ffffU
#define EMAC_REGS__STACKED_VLAN__MATCH__RESET                            0x0000
#define EMAC_REGS__STACKED_VLAN__MATCH__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__STACKED_VLAN__MATCH__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__STACKED_VLAN__MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__STACKED_VLAN__MATCH__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_30_16 */
#define EMAC_REGS__STACKED_VLAN__RESERVED_30_16__SHIFT                       16
#define EMAC_REGS__STACKED_VLAN__RESERVED_30_16__WIDTH                       15
#define EMAC_REGS__STACKED_VLAN__RESERVED_30_16__MASK               0x7fff0000U
#define EMAC_REGS__STACKED_VLAN__RESERVED_30_16__RESET                        0
#define EMAC_REGS__STACKED_VLAN__RESERVED_30_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0x7fff0000U) >> 16)

/* macros for field enable_processing */
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__SHIFT                    31
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__WIDTH                     1
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__MASK            0x80000000U
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__RESET                     0
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__STACKED_VLAN__TYPE                                  uint32_t
#define EMAC_REGS__STACKED_VLAN__READ                               0xffffffffU
#define EMAC_REGS__STACKED_VLAN__WRITE                              0xffffffffU

#endif /* __EMAC_REGS__STACKED_VLAN_MACRO__ */


/* macros for stacked_vlan */
#define INST_STACKED_VLAN__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_pfc_pause */
#ifndef __EMAC_REGS__TX_PFC_PAUSE_MACRO__
#define __EMAC_REGS__TX_PFC_PAUSE_MACRO__

/* macros for field vector_enable */
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__SHIFT                         0
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__WIDTH                         8
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__MASK                0x000000ffU
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__RESET                         0
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field vector */
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__SHIFT                                8
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__WIDTH                                8
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__MASK                       0x0000ff00U
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__RESET                                0
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__TX_PFC_PAUSE__VECTOR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__TX_PFC_PAUSE__RESERVED_31_16__SHIFT                       16
#define EMAC_REGS__TX_PFC_PAUSE__RESERVED_31_16__WIDTH                       16
#define EMAC_REGS__TX_PFC_PAUSE__RESERVED_31_16__MASK               0xffff0000U
#define EMAC_REGS__TX_PFC_PAUSE__RESERVED_31_16__RESET                        0
#define EMAC_REGS__TX_PFC_PAUSE__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TX_PFC_PAUSE__TYPE                                  uint32_t
#define EMAC_REGS__TX_PFC_PAUSE__READ                               0xffffffffU
#define EMAC_REGS__TX_PFC_PAUSE__WRITE                              0xffffffffU

#endif /* __EMAC_REGS__TX_PFC_PAUSE_MACRO__ */


/* macros for tx_pfc_pause */
#define INST_TX_PFC_PAUSE__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::mask_add1_bottom */
#ifndef __EMAC_REGS__MASK_ADD1_BOTTOM_MACRO__
#define __EMAC_REGS__MASK_ADD1_BOTTOM_MACRO__

/* macros for field address_mask */
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__SHIFT                      0
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__WIDTH                     32
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__MASK             0xffffffffU
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__RESET                      0
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__MASK_ADD1_BOTTOM__TYPE                              uint32_t
#define EMAC_REGS__MASK_ADD1_BOTTOM__READ                           0xffffffffU
#define EMAC_REGS__MASK_ADD1_BOTTOM__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__MASK_ADD1_BOTTOM_MACRO__ */


/* macros for mask_add1_bottom */
#define INST_MASK_ADD1_BOTTOM__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::mask_add1_top */
#ifndef __EMAC_REGS__MASK_ADD1_TOP_MACRO__
#define __EMAC_REGS__MASK_ADD1_TOP_MACRO__

/* macros for field address_mask */
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__SHIFT                         0
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__WIDTH                        16
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__MASK                0x0000ffffU
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__RESET                         0
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__MASK_ADD1_TOP__RESERVED_31_16__SHIFT                      16
#define EMAC_REGS__MASK_ADD1_TOP__RESERVED_31_16__WIDTH                      16
#define EMAC_REGS__MASK_ADD1_TOP__RESERVED_31_16__MASK              0xffff0000U
#define EMAC_REGS__MASK_ADD1_TOP__RESERVED_31_16__RESET                       0
#define EMAC_REGS__MASK_ADD1_TOP__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__MASK_ADD1_TOP__TYPE                                 uint32_t
#define EMAC_REGS__MASK_ADD1_TOP__READ                              0xffffffffU
#define EMAC_REGS__MASK_ADD1_TOP__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__MASK_ADD1_TOP_MACRO__ */


/* macros for mask_add1_top */
#define INST_MASK_ADD1_TOP__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::dma_addr_or_mask */
#ifndef __EMAC_REGS__DMA_ADDR_OR_MASK_MACRO__
#define __EMAC_REGS__DMA_ADDR_OR_MASK_MACRO__

/* macros for field mask_enable */
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__SHIFT                       0
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__WIDTH                       4
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__MASK              0x0000000fU
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__RESET                       0
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000000fU) | ((uint32_t)(src) &\
                    0x0000000fU)
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000000fU)))

/* macros for field reserved_27_4 */
#define EMAC_REGS__DMA_ADDR_OR_MASK__RESERVED_27_4__SHIFT                     4
#define EMAC_REGS__DMA_ADDR_OR_MASK__RESERVED_27_4__WIDTH                    24
#define EMAC_REGS__DMA_ADDR_OR_MASK__RESERVED_27_4__MASK            0x0ffffff0U
#define EMAC_REGS__DMA_ADDR_OR_MASK__RESERVED_27_4__RESET                     0
#define EMAC_REGS__DMA_ADDR_OR_MASK__RESERVED_27_4__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0ffffff0U) >> 4)

/* macros for field mask_value */
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__SHIFT                       28
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__WIDTH                        4
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__MASK               0xf0000000U
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__RESET                        0
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0xf0000000U)
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xf0000000U) | (((uint32_t)(src) <<\
                    28) & 0xf0000000U)
#define EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0xf0000000U)))
#define EMAC_REGS__DMA_ADDR_OR_MASK__TYPE                              uint32_t
#define EMAC_REGS__DMA_ADDR_OR_MASK__READ                           0xffffffffU
#define EMAC_REGS__DMA_ADDR_OR_MASK__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__DMA_ADDR_OR_MASK_MACRO__ */


/* macros for dma_addr_or_mask */
#define INST_DMA_ADDR_OR_MASK__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_ptp_unicast */
#ifndef __EMAC_REGS__RX_PTP_UNICAST_MACRO__
#define __EMAC_REGS__RX_PTP_UNICAST_MACRO__

/* macros for field address */
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__SHIFT                             0
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__WIDTH                            32
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__MASK                    0xffffffffU
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__RESET                             0
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__RX_PTP_UNICAST__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__RX_PTP_UNICAST__TYPE                                uint32_t
#define EMAC_REGS__RX_PTP_UNICAST__READ                             0xffffffffU
#define EMAC_REGS__RX_PTP_UNICAST__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__RX_PTP_UNICAST_MACRO__ */


/* macros for rx_ptp_unicast */
#define INST_RX_PTP_UNICAST__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_ptp_unicast */
#ifndef __EMAC_REGS__TX_PTP_UNICAST_MACRO__
#define __EMAC_REGS__TX_PTP_UNICAST_MACRO__

/* macros for field address */
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__SHIFT                             0
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__WIDTH                            32
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__MASK                    0xffffffffU
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__RESET                             0
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__TX_PTP_UNICAST__ADDRESS__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__TX_PTP_UNICAST__TYPE                                uint32_t
#define EMAC_REGS__TX_PTP_UNICAST__READ                             0xffffffffU
#define EMAC_REGS__TX_PTP_UNICAST__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__TX_PTP_UNICAST_MACRO__ */


/* macros for tx_ptp_unicast */
#define INST_TX_PTP_UNICAST__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_nsec_cmp */
#ifndef __EMAC_REGS__TSU_NSEC_CMP_MACRO__
#define __EMAC_REGS__TSU_NSEC_CMP_MACRO__

/* macros for field comparison_value */
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__SHIFT                      0
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__WIDTH                     22
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__MASK             0x003fffffU
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__RESET                      0
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x003fffffU)
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x003fffffU)
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x003fffffU) | ((uint32_t)(src) &\
                    0x003fffffU)
#define EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x003fffffU)))

/* macros for field reserved_31_22 */
#define EMAC_REGS__TSU_NSEC_CMP__RESERVED_31_22__SHIFT                       22
#define EMAC_REGS__TSU_NSEC_CMP__RESERVED_31_22__WIDTH                       10
#define EMAC_REGS__TSU_NSEC_CMP__RESERVED_31_22__MASK               0xffc00000U
#define EMAC_REGS__TSU_NSEC_CMP__RESERVED_31_22__RESET                        0
#define EMAC_REGS__TSU_NSEC_CMP__RESERVED_31_22__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffc00000U) >> 22)
#define EMAC_REGS__TSU_NSEC_CMP__TYPE                                  uint32_t
#define EMAC_REGS__TSU_NSEC_CMP__READ                               0xffffffffU
#define EMAC_REGS__TSU_NSEC_CMP__WRITE                              0xffffffffU

#endif /* __EMAC_REGS__TSU_NSEC_CMP_MACRO__ */


/* macros for tsu_nsec_cmp */
#define INST_TSU_NSEC_CMP__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_sec_cmp */
#ifndef __EMAC_REGS__TSU_SEC_CMP_MACRO__
#define __EMAC_REGS__TSU_SEC_CMP_MACRO__

/* macros for field comparison_value */
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__SHIFT                       0
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__WIDTH                      32
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__MASK              0xffffffffU
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__RESET                       0
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__TSU_SEC_CMP__TYPE                                   uint32_t
#define EMAC_REGS__TSU_SEC_CMP__READ                                0xffffffffU
#define EMAC_REGS__TSU_SEC_CMP__WRITE                               0xffffffffU

#endif /* __EMAC_REGS__TSU_SEC_CMP_MACRO__ */


/* macros for tsu_sec_cmp */
#define INST_TSU_SEC_CMP__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_msb_sec_cmp */
#ifndef __EMAC_REGS__TSU_MSB_SEC_CMP_MACRO__
#define __EMAC_REGS__TSU_MSB_SEC_CMP_MACRO__

/* macros for field comparison_value */
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__SHIFT                   0
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__WIDTH                  16
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__MASK          0x0000ffffU
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__RESET                   0
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_MSB_SEC_CMP__RESERVED_31_16__SHIFT                    16
#define EMAC_REGS__TSU_MSB_SEC_CMP__RESERVED_31_16__WIDTH                    16
#define EMAC_REGS__TSU_MSB_SEC_CMP__RESERVED_31_16__MASK            0xffff0000U
#define EMAC_REGS__TSU_MSB_SEC_CMP__RESERVED_31_16__RESET                     0
#define EMAC_REGS__TSU_MSB_SEC_CMP__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_MSB_SEC_CMP__TYPE                               uint32_t
#define EMAC_REGS__TSU_MSB_SEC_CMP__READ                            0xffffffffU
#define EMAC_REGS__TSU_MSB_SEC_CMP__WRITE                           0xffffffffU

#endif /* __EMAC_REGS__TSU_MSB_SEC_CMP_MACRO__ */


/* macros for tsu_msb_sec_cmp */
#define INST_TSU_MSB_SEC_CMP__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_ptp_tx_msb_sec */
#ifndef __EMAC_REGS__TSU_PTP_TX_MSB_SEC_MACRO__
#define __EMAC_REGS__TSU_PTP_TX_MSB_SEC_MACRO__

/* macros for field timer_seconds */
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__SHIFT                   0
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__WIDTH                  16
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__MASK          0x0000ffffU
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__RESET                   0
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__RESERVED_31_16__SHIFT                 16
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__RESERVED_31_16__WIDTH                 16
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__RESERVED_31_16__MASK         0xffff0000U
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__RESERVED_31_16__RESET                  0
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__TYPE                            uint32_t
#define EMAC_REGS__TSU_PTP_TX_MSB_SEC__READ                         0xffffffffU

#endif /* __EMAC_REGS__TSU_PTP_TX_MSB_SEC_MACRO__ */


/* macros for tsu_ptp_tx_msb_sec */
#define INST_TSU_PTP_TX_MSB_SEC__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_ptp_rx_msb_sec */
#ifndef __EMAC_REGS__TSU_PTP_RX_MSB_SEC_MACRO__
#define __EMAC_REGS__TSU_PTP_RX_MSB_SEC_MACRO__

/* macros for field timer_seconds */
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__SHIFT                   0
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__WIDTH                  16
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__MASK          0x0000ffffU
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__RESET                   0
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__RESERVED_31_16__SHIFT                 16
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__RESERVED_31_16__WIDTH                 16
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__RESERVED_31_16__MASK         0xffff0000U
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__RESERVED_31_16__RESET                  0
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__TYPE                            uint32_t
#define EMAC_REGS__TSU_PTP_RX_MSB_SEC__READ                         0xffffffffU

#endif /* __EMAC_REGS__TSU_PTP_RX_MSB_SEC_MACRO__ */


/* macros for tsu_ptp_rx_msb_sec */
#define INST_TSU_PTP_RX_MSB_SEC__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_peer_tx_msb_sec */
#ifndef __EMAC_REGS__TSU_PEER_TX_MSB_SEC_MACRO__
#define __EMAC_REGS__TSU_PEER_TX_MSB_SEC_MACRO__

/* macros for field timer_seconds */
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__SHIFT                  0
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__WIDTH                 16
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__MASK         0x0000ffffU
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__RESET                  0
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__RESERVED_31_16__SHIFT                16
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__RESERVED_31_16__WIDTH                16
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__RESERVED_31_16__MASK        0xffff0000U
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__RESERVED_31_16__RESET                 0
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__TYPE                           uint32_t
#define EMAC_REGS__TSU_PEER_TX_MSB_SEC__READ                        0xffffffffU

#endif /* __EMAC_REGS__TSU_PEER_TX_MSB_SEC_MACRO__ */


/* macros for tsu_peer_tx_msb_sec */
#define INST_TSU_PEER_TX_MSB_SEC__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_peer_rx_msb_sec */
#ifndef __EMAC_REGS__TSU_PEER_RX_MSB_SEC_MACRO__
#define __EMAC_REGS__TSU_PEER_RX_MSB_SEC_MACRO__

/* macros for field timer_seconds */
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__SHIFT                  0
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__WIDTH                 16
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__MASK         0x0000ffffU
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__RESET                  0
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__RESERVED_31_16__SHIFT                16
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__RESERVED_31_16__WIDTH                16
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__RESERVED_31_16__MASK        0xffff0000U
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__RESERVED_31_16__RESET                 0
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__TYPE                           uint32_t
#define EMAC_REGS__TSU_PEER_RX_MSB_SEC__READ                        0xffffffffU

#endif /* __EMAC_REGS__TSU_PEER_RX_MSB_SEC_MACRO__ */


/* macros for tsu_peer_rx_msb_sec */
#define INST_TSU_PEER_RX_MSB_SEC__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::dpram_fill_dbg */
#ifndef __EMAC_REGS__DPRAM_FILL_DBG_MACRO__
#define __EMAC_REGS__DPRAM_FILL_DBG_MACRO__

/* macros for field dma_tx_rx_fill_level_select */
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__SHIFT         0
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__WIDTH         1
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__MASK \
                    0x00000001U
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__RESET         0
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL_SELECT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_3_1 */
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_3_1__SHIFT                        1
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_3_1__WIDTH                        3
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_3_1__MASK               0x0000000eU
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_3_1__RESET                        0
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_3_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000000eU) >> 1)

/* macros for field dma_tx_q_fill_level_select */
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__SHIFT          4
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__WIDTH          4
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__MASK 0x000000f0U
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__RESET          0
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000f0U) >> 4)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x000000f0U)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000f0U) | (((uint32_t)(src) <<\
                    4) & 0x000000f0U)
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_Q_FILL_LEVEL_SELECT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x000000f0U)))

/* macros for field reserved_15_8 */
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_15_8__SHIFT                       8
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_15_8__WIDTH                       8
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_15_8__MASK              0x0000ff00U
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_15_8__RESET                       0
#define EMAC_REGS__DPRAM_FILL_DBG__RESERVED_15_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)

/* macros for field dma_tx_rx_fill_level */
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL__SHIFT               16
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL__WIDTH               16
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL__MASK       0xffff0000U
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL__RESET                0
#define EMAC_REGS__DPRAM_FILL_DBG__DMA_TX_RX_FILL_LEVEL__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__DPRAM_FILL_DBG__TYPE                                uint32_t
#define EMAC_REGS__DPRAM_FILL_DBG__READ                             0xffffffffU
#define EMAC_REGS__DPRAM_FILL_DBG__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__DPRAM_FILL_DBG_MACRO__ */


/* macros for dpram_fill_dbg */
#define INST_DPRAM_FILL_DBG__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::revision_reg */
#ifndef __EMAC_REGS__REVISION_REG_MACRO__
#define __EMAC_REGS__REVISION_REG_MACRO__

/* macros for field module_revision */
#define EMAC_REGS__REVISION_REG__MODULE_REVISION__SHIFT                       0
#define EMAC_REGS__REVISION_REG__MODULE_REVISION__WIDTH                      16
#define EMAC_REGS__REVISION_REG__MODULE_REVISION__MASK              0x0000ffffU
#define EMAC_REGS__REVISION_REG__MODULE_REVISION__RESET                     265
#define EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field module_identification_number */
#define EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__SHIFT         16
#define EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__WIDTH         12
#define EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__MASK 0x0fff0000U
#define EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__RESET        263
#define EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0fff0000U) >> 16)

/* macros for field fix_number */
#define EMAC_REGS__REVISION_REG__FIX_NUMBER__SHIFT                           28
#define EMAC_REGS__REVISION_REG__FIX_NUMBER__WIDTH                            4
#define EMAC_REGS__REVISION_REG__FIX_NUMBER__MASK                   0xf0000000U
#define EMAC_REGS__REVISION_REG__FIX_NUMBER__RESET                            0
#define EMAC_REGS__REVISION_REG__FIX_NUMBER__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__REVISION_REG__TYPE                                  uint32_t
#define EMAC_REGS__REVISION_REG__READ                               0xffffffffU

#endif /* __EMAC_REGS__REVISION_REG_MACRO__ */


/* macros for revision_reg */
#define INST_REVISION_REG__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::octets_txed_bottom */
#ifndef __EMAC_REGS__OCTETS_TXED_BOTTOM_MACRO__
#define __EMAC_REGS__OCTETS_TXED_BOTTOM_MACRO__

/* macros for field count */
#define EMAC_REGS__OCTETS_TXED_BOTTOM__COUNT__SHIFT                           0
#define EMAC_REGS__OCTETS_TXED_BOTTOM__COUNT__WIDTH                          32
#define EMAC_REGS__OCTETS_TXED_BOTTOM__COUNT__MASK                  0xffffffffU
#define EMAC_REGS__OCTETS_TXED_BOTTOM__COUNT__RESET                           0
#define EMAC_REGS__OCTETS_TXED_BOTTOM__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__OCTETS_TXED_BOTTOM__TYPE                            uint32_t
#define EMAC_REGS__OCTETS_TXED_BOTTOM__READ                         0xffffffffU
#define EMAC_REGS__OCTETS_TXED_BOTTOM__RCLR                         0xffffffffU

#endif /* __EMAC_REGS__OCTETS_TXED_BOTTOM_MACRO__ */


/* macros for octets_txed_bottom */
#define INST_OCTETS_TXED_BOTTOM__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::octets_txed_top */
#ifndef __EMAC_REGS__OCTETS_TXED_TOP_MACRO__
#define __EMAC_REGS__OCTETS_TXED_TOP_MACRO__

/* macros for field count */
#define EMAC_REGS__OCTETS_TXED_TOP__COUNT__SHIFT                              0
#define EMAC_REGS__OCTETS_TXED_TOP__COUNT__WIDTH                             16
#define EMAC_REGS__OCTETS_TXED_TOP__COUNT__MASK                     0x0000ffffU
#define EMAC_REGS__OCTETS_TXED_TOP__COUNT__RESET                              0
#define EMAC_REGS__OCTETS_TXED_TOP__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__OCTETS_TXED_TOP__RESERVED_31_16__SHIFT                    16
#define EMAC_REGS__OCTETS_TXED_TOP__RESERVED_31_16__WIDTH                    16
#define EMAC_REGS__OCTETS_TXED_TOP__RESERVED_31_16__MASK            0xffff0000U
#define EMAC_REGS__OCTETS_TXED_TOP__RESERVED_31_16__RESET                     0
#define EMAC_REGS__OCTETS_TXED_TOP__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__OCTETS_TXED_TOP__TYPE                               uint32_t
#define EMAC_REGS__OCTETS_TXED_TOP__READ                            0xffffffffU
#define EMAC_REGS__OCTETS_TXED_TOP__RCLR                            0x0000ffffU

#endif /* __EMAC_REGS__OCTETS_TXED_TOP_MACRO__ */


/* macros for octets_txed_top */
#define INST_OCTETS_TXED_TOP__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_ok */
#ifndef __EMAC_REGS__FRAMES_TXED_OK_MACRO__
#define __EMAC_REGS__FRAMES_TXED_OK_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_OK__COUNT__SHIFT                               0
#define EMAC_REGS__FRAMES_TXED_OK__COUNT__WIDTH                              32
#define EMAC_REGS__FRAMES_TXED_OK__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__FRAMES_TXED_OK__COUNT__RESET                               0
#define EMAC_REGS__FRAMES_TXED_OK__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_OK__TYPE                                uint32_t
#define EMAC_REGS__FRAMES_TXED_OK__READ                             0xffffffffU
#define EMAC_REGS__FRAMES_TXED_OK__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_OK_MACRO__ */


/* macros for frames_txed_ok */
#define INST_FRAMES_TXED_OK__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::broadcast_txed */
#ifndef __EMAC_REGS__BROADCAST_TXED_MACRO__
#define __EMAC_REGS__BROADCAST_TXED_MACRO__

/* macros for field count */
#define EMAC_REGS__BROADCAST_TXED__COUNT__SHIFT                               0
#define EMAC_REGS__BROADCAST_TXED__COUNT__WIDTH                              32
#define EMAC_REGS__BROADCAST_TXED__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__BROADCAST_TXED__COUNT__RESET                               0
#define EMAC_REGS__BROADCAST_TXED__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__BROADCAST_TXED__TYPE                                uint32_t
#define EMAC_REGS__BROADCAST_TXED__READ                             0xffffffffU
#define EMAC_REGS__BROADCAST_TXED__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__BROADCAST_TXED_MACRO__ */


/* macros for broadcast_txed */
#define INST_BROADCAST_TXED__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::multicast_txed */
#ifndef __EMAC_REGS__MULTICAST_TXED_MACRO__
#define __EMAC_REGS__MULTICAST_TXED_MACRO__

/* macros for field count */
#define EMAC_REGS__MULTICAST_TXED__COUNT__SHIFT                               0
#define EMAC_REGS__MULTICAST_TXED__COUNT__WIDTH                              32
#define EMAC_REGS__MULTICAST_TXED__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__MULTICAST_TXED__COUNT__RESET                               0
#define EMAC_REGS__MULTICAST_TXED__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__MULTICAST_TXED__TYPE                                uint32_t
#define EMAC_REGS__MULTICAST_TXED__READ                             0xffffffffU
#define EMAC_REGS__MULTICAST_TXED__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__MULTICAST_TXED_MACRO__ */


/* macros for multicast_txed */
#define INST_MULTICAST_TXED__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::pause_frames_txed */
#ifndef __EMAC_REGS__PAUSE_FRAMES_TXED_MACRO__
#define __EMAC_REGS__PAUSE_FRAMES_TXED_MACRO__

/* macros for field count */
#define EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__SHIFT                            0
#define EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__WIDTH                           16
#define EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__MASK                   0x0000ffffU
#define EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__RESET                            0
#define EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PAUSE_FRAMES_TXED__RESERVED_31_16__SHIFT                  16
#define EMAC_REGS__PAUSE_FRAMES_TXED__RESERVED_31_16__WIDTH                  16
#define EMAC_REGS__PAUSE_FRAMES_TXED__RESERVED_31_16__MASK          0xffff0000U
#define EMAC_REGS__PAUSE_FRAMES_TXED__RESERVED_31_16__RESET                   0
#define EMAC_REGS__PAUSE_FRAMES_TXED__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PAUSE_FRAMES_TXED__TYPE                             uint32_t
#define EMAC_REGS__PAUSE_FRAMES_TXED__READ                          0xffffffffU
#define EMAC_REGS__PAUSE_FRAMES_TXED__RCLR                          0x0000ffffU

#endif /* __EMAC_REGS__PAUSE_FRAMES_TXED_MACRO__ */


/* macros for pause_frames_txed */
#define INST_PAUSE_FRAMES_TXED__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_64 */
#ifndef __EMAC_REGS__FRAMES_TXED_64_MACRO__
#define __EMAC_REGS__FRAMES_TXED_64_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_64__COUNT__SHIFT                               0
#define EMAC_REGS__FRAMES_TXED_64__COUNT__WIDTH                              32
#define EMAC_REGS__FRAMES_TXED_64__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__FRAMES_TXED_64__COUNT__RESET                               0
#define EMAC_REGS__FRAMES_TXED_64__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_64__TYPE                                uint32_t
#define EMAC_REGS__FRAMES_TXED_64__READ                             0xffffffffU
#define EMAC_REGS__FRAMES_TXED_64__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_64_MACRO__ */


/* macros for frames_txed_64 */
#define INST_FRAMES_TXED_64__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_65 */
#ifndef __EMAC_REGS__FRAMES_TXED_65_MACRO__
#define __EMAC_REGS__FRAMES_TXED_65_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_65__COUNT__SHIFT                               0
#define EMAC_REGS__FRAMES_TXED_65__COUNT__WIDTH                              32
#define EMAC_REGS__FRAMES_TXED_65__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__FRAMES_TXED_65__COUNT__RESET                               0
#define EMAC_REGS__FRAMES_TXED_65__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_65__TYPE                                uint32_t
#define EMAC_REGS__FRAMES_TXED_65__READ                             0xffffffffU
#define EMAC_REGS__FRAMES_TXED_65__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_65_MACRO__ */


/* macros for frames_txed_65 */
#define INST_FRAMES_TXED_65__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_128 */
#ifndef __EMAC_REGS__FRAMES_TXED_128_MACRO__
#define __EMAC_REGS__FRAMES_TXED_128_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_128__COUNT__SHIFT                              0
#define EMAC_REGS__FRAMES_TXED_128__COUNT__WIDTH                             32
#define EMAC_REGS__FRAMES_TXED_128__COUNT__MASK                     0xffffffffU
#define EMAC_REGS__FRAMES_TXED_128__COUNT__RESET                              0
#define EMAC_REGS__FRAMES_TXED_128__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_128__TYPE                               uint32_t
#define EMAC_REGS__FRAMES_TXED_128__READ                            0xffffffffU
#define EMAC_REGS__FRAMES_TXED_128__RCLR                            0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_128_MACRO__ */


/* macros for frames_txed_128 */
#define INST_FRAMES_TXED_128__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_256 */
#ifndef __EMAC_REGS__FRAMES_TXED_256_MACRO__
#define __EMAC_REGS__FRAMES_TXED_256_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_256__COUNT__SHIFT                              0
#define EMAC_REGS__FRAMES_TXED_256__COUNT__WIDTH                             32
#define EMAC_REGS__FRAMES_TXED_256__COUNT__MASK                     0xffffffffU
#define EMAC_REGS__FRAMES_TXED_256__COUNT__RESET                              0
#define EMAC_REGS__FRAMES_TXED_256__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_256__TYPE                               uint32_t
#define EMAC_REGS__FRAMES_TXED_256__READ                            0xffffffffU
#define EMAC_REGS__FRAMES_TXED_256__RCLR                            0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_256_MACRO__ */


/* macros for frames_txed_256 */
#define INST_FRAMES_TXED_256__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_512 */
#ifndef __EMAC_REGS__FRAMES_TXED_512_MACRO__
#define __EMAC_REGS__FRAMES_TXED_512_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_512__COUNT__SHIFT                              0
#define EMAC_REGS__FRAMES_TXED_512__COUNT__WIDTH                             32
#define EMAC_REGS__FRAMES_TXED_512__COUNT__MASK                     0xffffffffU
#define EMAC_REGS__FRAMES_TXED_512__COUNT__RESET                              0
#define EMAC_REGS__FRAMES_TXED_512__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_512__TYPE                               uint32_t
#define EMAC_REGS__FRAMES_TXED_512__READ                            0xffffffffU
#define EMAC_REGS__FRAMES_TXED_512__RCLR                            0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_512_MACRO__ */


/* macros for frames_txed_512 */
#define INST_FRAMES_TXED_512__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_1024 */
#ifndef __EMAC_REGS__FRAMES_TXED_1024_MACRO__
#define __EMAC_REGS__FRAMES_TXED_1024_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_1024__COUNT__SHIFT                             0
#define EMAC_REGS__FRAMES_TXED_1024__COUNT__WIDTH                            32
#define EMAC_REGS__FRAMES_TXED_1024__COUNT__MASK                    0xffffffffU
#define EMAC_REGS__FRAMES_TXED_1024__COUNT__RESET                             0
#define EMAC_REGS__FRAMES_TXED_1024__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_1024__TYPE                              uint32_t
#define EMAC_REGS__FRAMES_TXED_1024__READ                           0xffffffffU
#define EMAC_REGS__FRAMES_TXED_1024__RCLR                           0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_1024_MACRO__ */


/* macros for frames_txed_1024 */
#define INST_FRAMES_TXED_1024__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_txed_1519 */
#ifndef __EMAC_REGS__FRAMES_TXED_1519_MACRO__
#define __EMAC_REGS__FRAMES_TXED_1519_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_TXED_1519__COUNT__SHIFT                             0
#define EMAC_REGS__FRAMES_TXED_1519__COUNT__WIDTH                            32
#define EMAC_REGS__FRAMES_TXED_1519__COUNT__MASK                    0xffffffffU
#define EMAC_REGS__FRAMES_TXED_1519__COUNT__RESET                             0
#define EMAC_REGS__FRAMES_TXED_1519__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_TXED_1519__TYPE                              uint32_t
#define EMAC_REGS__FRAMES_TXED_1519__READ                           0xffffffffU
#define EMAC_REGS__FRAMES_TXED_1519__RCLR                           0xffffffffU

#endif /* __EMAC_REGS__FRAMES_TXED_1519_MACRO__ */


/* macros for frames_txed_1519 */
#define INST_FRAMES_TXED_1519__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_underruns */
#ifndef __EMAC_REGS__TX_UNDERRUNS_MACRO__
#define __EMAC_REGS__TX_UNDERRUNS_MACRO__

/* macros for field count */
#define EMAC_REGS__TX_UNDERRUNS__COUNT__SHIFT                                 0
#define EMAC_REGS__TX_UNDERRUNS__COUNT__WIDTH                                10
#define EMAC_REGS__TX_UNDERRUNS__COUNT__MASK                        0x000003ffU
#define EMAC_REGS__TX_UNDERRUNS__COUNT__RESET                                 0
#define EMAC_REGS__TX_UNDERRUNS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_22 */
#define EMAC_REGS__TX_UNDERRUNS__RESERVED_22__SHIFT                          10
#define EMAC_REGS__TX_UNDERRUNS__RESERVED_22__WIDTH                          22
#define EMAC_REGS__TX_UNDERRUNS__RESERVED_22__MASK                  0xfffffc00U
#define EMAC_REGS__TX_UNDERRUNS__RESERVED_22__RESET                           0
#define EMAC_REGS__TX_UNDERRUNS__RESERVED_22__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__TX_UNDERRUNS__TYPE                                  uint32_t
#define EMAC_REGS__TX_UNDERRUNS__READ                               0xffffffffU
#define EMAC_REGS__TX_UNDERRUNS__RCLR                               0x000003ffU

#endif /* __EMAC_REGS__TX_UNDERRUNS_MACRO__ */


/* macros for tx_underruns */
#define INST_TX_UNDERRUNS__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::single_collisions */
#ifndef __EMAC_REGS__SINGLE_COLLISIONS_MACRO__
#define __EMAC_REGS__SINGLE_COLLISIONS_MACRO__

/* macros for field count */
#define EMAC_REGS__SINGLE_COLLISIONS__COUNT__SHIFT                            0
#define EMAC_REGS__SINGLE_COLLISIONS__COUNT__WIDTH                           18
#define EMAC_REGS__SINGLE_COLLISIONS__COUNT__MASK                   0x0003ffffU
#define EMAC_REGS__SINGLE_COLLISIONS__COUNT__RESET                            0
#define EMAC_REGS__SINGLE_COLLISIONS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0003ffffU)

/* macros for field reserved_31_18 */
#define EMAC_REGS__SINGLE_COLLISIONS__RESERVED_31_18__SHIFT                  18
#define EMAC_REGS__SINGLE_COLLISIONS__RESERVED_31_18__WIDTH                  14
#define EMAC_REGS__SINGLE_COLLISIONS__RESERVED_31_18__MASK          0xfffc0000U
#define EMAC_REGS__SINGLE_COLLISIONS__RESERVED_31_18__RESET                   0
#define EMAC_REGS__SINGLE_COLLISIONS__RESERVED_31_18__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffc0000U) >> 18)
#define EMAC_REGS__SINGLE_COLLISIONS__TYPE                             uint32_t
#define EMAC_REGS__SINGLE_COLLISIONS__READ                          0xffffffffU
#define EMAC_REGS__SINGLE_COLLISIONS__RCLR                          0x0003ffffU

#endif /* __EMAC_REGS__SINGLE_COLLISIONS_MACRO__ */


/* macros for single_collisions */
#define INST_SINGLE_COLLISIONS__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::multiple_collisions */
#ifndef __EMAC_REGS__MULTIPLE_COLLISIONS_MACRO__
#define __EMAC_REGS__MULTIPLE_COLLISIONS_MACRO__

/* macros for field count */
#define EMAC_REGS__MULTIPLE_COLLISIONS__COUNT__SHIFT                          0
#define EMAC_REGS__MULTIPLE_COLLISIONS__COUNT__WIDTH                         18
#define EMAC_REGS__MULTIPLE_COLLISIONS__COUNT__MASK                 0x0003ffffU
#define EMAC_REGS__MULTIPLE_COLLISIONS__COUNT__RESET                          0
#define EMAC_REGS__MULTIPLE_COLLISIONS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0003ffffU)

/* macros for field reserved_31_18 */
#define EMAC_REGS__MULTIPLE_COLLISIONS__RESERVED_31_18__SHIFT                18
#define EMAC_REGS__MULTIPLE_COLLISIONS__RESERVED_31_18__WIDTH                14
#define EMAC_REGS__MULTIPLE_COLLISIONS__RESERVED_31_18__MASK        0xfffc0000U
#define EMAC_REGS__MULTIPLE_COLLISIONS__RESERVED_31_18__RESET                 0
#define EMAC_REGS__MULTIPLE_COLLISIONS__RESERVED_31_18__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffc0000U) >> 18)
#define EMAC_REGS__MULTIPLE_COLLISIONS__TYPE                           uint32_t
#define EMAC_REGS__MULTIPLE_COLLISIONS__READ                        0xffffffffU
#define EMAC_REGS__MULTIPLE_COLLISIONS__RCLR                        0x0003ffffU

#endif /* __EMAC_REGS__MULTIPLE_COLLISIONS_MACRO__ */


/* macros for multiple_collisions */
#define INST_MULTIPLE_COLLISIONS__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::excessive_collisions */
#ifndef __EMAC_REGS__EXCESSIVE_COLLISIONS_MACRO__
#define __EMAC_REGS__EXCESSIVE_COLLISIONS_MACRO__

/* macros for field count */
#define EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__SHIFT                         0
#define EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__WIDTH                        10
#define EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__MASK                0x000003ffU
#define EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__RESET                         0
#define EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__EXCESSIVE_COLLISIONS__RESERVED_31_10__SHIFT               10
#define EMAC_REGS__EXCESSIVE_COLLISIONS__RESERVED_31_10__WIDTH               22
#define EMAC_REGS__EXCESSIVE_COLLISIONS__RESERVED_31_10__MASK       0xfffffc00U
#define EMAC_REGS__EXCESSIVE_COLLISIONS__RESERVED_31_10__RESET                0
#define EMAC_REGS__EXCESSIVE_COLLISIONS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__EXCESSIVE_COLLISIONS__TYPE                          uint32_t
#define EMAC_REGS__EXCESSIVE_COLLISIONS__READ                       0xffffffffU
#define EMAC_REGS__EXCESSIVE_COLLISIONS__RCLR                       0x000003ffU

#endif /* __EMAC_REGS__EXCESSIVE_COLLISIONS_MACRO__ */


/* macros for excessive_collisions */
#define INST_EXCESSIVE_COLLISIONS__NUM                                        1

/* macros for BlueprintGlobalNameSpace::emac_regs::late_collisions */
#ifndef __EMAC_REGS__LATE_COLLISIONS_MACRO__
#define __EMAC_REGS__LATE_COLLISIONS_MACRO__

/* macros for field count */
#define EMAC_REGS__LATE_COLLISIONS__COUNT__SHIFT                              0
#define EMAC_REGS__LATE_COLLISIONS__COUNT__WIDTH                             10
#define EMAC_REGS__LATE_COLLISIONS__COUNT__MASK                     0x000003ffU
#define EMAC_REGS__LATE_COLLISIONS__COUNT__RESET                              0
#define EMAC_REGS__LATE_COLLISIONS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__LATE_COLLISIONS__RESERVED_31_10__SHIFT                    10
#define EMAC_REGS__LATE_COLLISIONS__RESERVED_31_10__WIDTH                    22
#define EMAC_REGS__LATE_COLLISIONS__RESERVED_31_10__MASK            0xfffffc00U
#define EMAC_REGS__LATE_COLLISIONS__RESERVED_31_10__RESET                     0
#define EMAC_REGS__LATE_COLLISIONS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__LATE_COLLISIONS__TYPE                               uint32_t
#define EMAC_REGS__LATE_COLLISIONS__READ                            0xffffffffU
#define EMAC_REGS__LATE_COLLISIONS__RCLR                            0x000003ffU

#endif /* __EMAC_REGS__LATE_COLLISIONS_MACRO__ */


/* macros for late_collisions */
#define INST_LATE_COLLISIONS__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::deferred_frames */
#ifndef __EMAC_REGS__DEFERRED_FRAMES_MACRO__
#define __EMAC_REGS__DEFERRED_FRAMES_MACRO__

/* macros for field count */
#define EMAC_REGS__DEFERRED_FRAMES__COUNT__SHIFT                              0
#define EMAC_REGS__DEFERRED_FRAMES__COUNT__WIDTH                             18
#define EMAC_REGS__DEFERRED_FRAMES__COUNT__MASK                     0x0003ffffU
#define EMAC_REGS__DEFERRED_FRAMES__COUNT__RESET                              0
#define EMAC_REGS__DEFERRED_FRAMES__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0003ffffU)

/* macros for field reserved_31_18 */
#define EMAC_REGS__DEFERRED_FRAMES__RESERVED_31_18__SHIFT                    18
#define EMAC_REGS__DEFERRED_FRAMES__RESERVED_31_18__WIDTH                    14
#define EMAC_REGS__DEFERRED_FRAMES__RESERVED_31_18__MASK            0xfffc0000U
#define EMAC_REGS__DEFERRED_FRAMES__RESERVED_31_18__RESET                     0
#define EMAC_REGS__DEFERRED_FRAMES__RESERVED_31_18__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffc0000U) >> 18)
#define EMAC_REGS__DEFERRED_FRAMES__TYPE                               uint32_t
#define EMAC_REGS__DEFERRED_FRAMES__READ                            0xffffffffU
#define EMAC_REGS__DEFERRED_FRAMES__RCLR                            0x0003ffffU

#endif /* __EMAC_REGS__DEFERRED_FRAMES_MACRO__ */


/* macros for deferred_frames */
#define INST_DEFERRED_FRAMES__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::crs_errors */
#ifndef __EMAC_REGS__CRS_ERRORS_MACRO__
#define __EMAC_REGS__CRS_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__CRS_ERRORS__COUNT__SHIFT                                   0
#define EMAC_REGS__CRS_ERRORS__COUNT__WIDTH                                  10
#define EMAC_REGS__CRS_ERRORS__COUNT__MASK                          0x000003ffU
#define EMAC_REGS__CRS_ERRORS__COUNT__RESET                                   0
#define EMAC_REGS__CRS_ERRORS__COUNT__READ(src) ((uint32_t)(src) & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__CRS_ERRORS__RESERVED_31_10__SHIFT                         10
#define EMAC_REGS__CRS_ERRORS__RESERVED_31_10__WIDTH                         22
#define EMAC_REGS__CRS_ERRORS__RESERVED_31_10__MASK                 0xfffffc00U
#define EMAC_REGS__CRS_ERRORS__RESERVED_31_10__RESET                          0
#define EMAC_REGS__CRS_ERRORS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__CRS_ERRORS__TYPE                                    uint32_t
#define EMAC_REGS__CRS_ERRORS__READ                                 0xffffffffU
#define EMAC_REGS__CRS_ERRORS__RCLR                                 0x000003ffU

#endif /* __EMAC_REGS__CRS_ERRORS_MACRO__ */


/* macros for crs_errors */
#define INST_CRS_ERRORS__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::octets_rxed_bottom */
#ifndef __EMAC_REGS__OCTETS_RXED_BOTTOM_MACRO__
#define __EMAC_REGS__OCTETS_RXED_BOTTOM_MACRO__

/* macros for field count */
#define EMAC_REGS__OCTETS_RXED_BOTTOM__COUNT__SHIFT                           0
#define EMAC_REGS__OCTETS_RXED_BOTTOM__COUNT__WIDTH                          32
#define EMAC_REGS__OCTETS_RXED_BOTTOM__COUNT__MASK                  0xffffffffU
#define EMAC_REGS__OCTETS_RXED_BOTTOM__COUNT__RESET                           0
#define EMAC_REGS__OCTETS_RXED_BOTTOM__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__OCTETS_RXED_BOTTOM__TYPE                            uint32_t
#define EMAC_REGS__OCTETS_RXED_BOTTOM__READ                         0xffffffffU
#define EMAC_REGS__OCTETS_RXED_BOTTOM__RCLR                         0xffffffffU

#endif /* __EMAC_REGS__OCTETS_RXED_BOTTOM_MACRO__ */


/* macros for octets_rxed_bottom */
#define INST_OCTETS_RXED_BOTTOM__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::octets_rxed_top */
#ifndef __EMAC_REGS__OCTETS_RXED_TOP_MACRO__
#define __EMAC_REGS__OCTETS_RXED_TOP_MACRO__

/* macros for field count */
#define EMAC_REGS__OCTETS_RXED_TOP__COUNT__SHIFT                              0
#define EMAC_REGS__OCTETS_RXED_TOP__COUNT__WIDTH                             16
#define EMAC_REGS__OCTETS_RXED_TOP__COUNT__MASK                     0x0000ffffU
#define EMAC_REGS__OCTETS_RXED_TOP__COUNT__RESET                              0
#define EMAC_REGS__OCTETS_RXED_TOP__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__OCTETS_RXED_TOP__RESERVED_31_16__SHIFT                    16
#define EMAC_REGS__OCTETS_RXED_TOP__RESERVED_31_16__WIDTH                    16
#define EMAC_REGS__OCTETS_RXED_TOP__RESERVED_31_16__MASK            0xffff0000U
#define EMAC_REGS__OCTETS_RXED_TOP__RESERVED_31_16__RESET                     0
#define EMAC_REGS__OCTETS_RXED_TOP__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__OCTETS_RXED_TOP__TYPE                               uint32_t
#define EMAC_REGS__OCTETS_RXED_TOP__READ                            0xffffffffU
#define EMAC_REGS__OCTETS_RXED_TOP__RCLR                            0x0000ffffU

#endif /* __EMAC_REGS__OCTETS_RXED_TOP_MACRO__ */


/* macros for octets_rxed_top */
#define INST_OCTETS_RXED_TOP__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_ok */
#ifndef __EMAC_REGS__FRAMES_RXED_OK_MACRO__
#define __EMAC_REGS__FRAMES_RXED_OK_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_OK__COUNT__SHIFT                               0
#define EMAC_REGS__FRAMES_RXED_OK__COUNT__WIDTH                              32
#define EMAC_REGS__FRAMES_RXED_OK__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__FRAMES_RXED_OK__COUNT__RESET                               0
#define EMAC_REGS__FRAMES_RXED_OK__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_OK__TYPE                                uint32_t
#define EMAC_REGS__FRAMES_RXED_OK__READ                             0xffffffffU
#define EMAC_REGS__FRAMES_RXED_OK__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_OK_MACRO__ */


/* macros for frames_rxed_ok */
#define INST_FRAMES_RXED_OK__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::broadcast_rxed */
#ifndef __EMAC_REGS__BROADCAST_RXED_MACRO__
#define __EMAC_REGS__BROADCAST_RXED_MACRO__

/* macros for field count */
#define EMAC_REGS__BROADCAST_RXED__COUNT__SHIFT                               0
#define EMAC_REGS__BROADCAST_RXED__COUNT__WIDTH                              32
#define EMAC_REGS__BROADCAST_RXED__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__BROADCAST_RXED__COUNT__RESET                               0
#define EMAC_REGS__BROADCAST_RXED__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__BROADCAST_RXED__TYPE                                uint32_t
#define EMAC_REGS__BROADCAST_RXED__READ                             0xffffffffU
#define EMAC_REGS__BROADCAST_RXED__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__BROADCAST_RXED_MACRO__ */


/* macros for broadcast_rxed */
#define INST_BROADCAST_RXED__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::multicast_rxed */
#ifndef __EMAC_REGS__MULTICAST_RXED_MACRO__
#define __EMAC_REGS__MULTICAST_RXED_MACRO__

/* macros for field count */
#define EMAC_REGS__MULTICAST_RXED__COUNT__SHIFT                               0
#define EMAC_REGS__MULTICAST_RXED__COUNT__WIDTH                              32
#define EMAC_REGS__MULTICAST_RXED__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__MULTICAST_RXED__COUNT__RESET                               0
#define EMAC_REGS__MULTICAST_RXED__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__MULTICAST_RXED__TYPE                                uint32_t
#define EMAC_REGS__MULTICAST_RXED__READ                             0xffffffffU
#define EMAC_REGS__MULTICAST_RXED__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__MULTICAST_RXED_MACRO__ */


/* macros for multicast_rxed */
#define INST_MULTICAST_RXED__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::pause_frames_rxed */
#ifndef __EMAC_REGS__PAUSE_FRAMES_RXED_MACRO__
#define __EMAC_REGS__PAUSE_FRAMES_RXED_MACRO__

/* macros for field count */
#define EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__SHIFT                            0
#define EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__WIDTH                           16
#define EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__MASK                   0x0000ffffU
#define EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__RESET                            0
#define EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PAUSE_FRAMES_RXED__RESERVED_31_16__SHIFT                  16
#define EMAC_REGS__PAUSE_FRAMES_RXED__RESERVED_31_16__WIDTH                  16
#define EMAC_REGS__PAUSE_FRAMES_RXED__RESERVED_31_16__MASK          0xffff0000U
#define EMAC_REGS__PAUSE_FRAMES_RXED__RESERVED_31_16__RESET                   0
#define EMAC_REGS__PAUSE_FRAMES_RXED__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PAUSE_FRAMES_RXED__TYPE                             uint32_t
#define EMAC_REGS__PAUSE_FRAMES_RXED__READ                          0xffffffffU
#define EMAC_REGS__PAUSE_FRAMES_RXED__RCLR                          0x0000ffffU

#endif /* __EMAC_REGS__PAUSE_FRAMES_RXED_MACRO__ */


/* macros for pause_frames_rxed */
#define INST_PAUSE_FRAMES_RXED__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_64 */
#ifndef __EMAC_REGS__FRAMES_RXED_64_MACRO__
#define __EMAC_REGS__FRAMES_RXED_64_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_64__COUNT__SHIFT                               0
#define EMAC_REGS__FRAMES_RXED_64__COUNT__WIDTH                              32
#define EMAC_REGS__FRAMES_RXED_64__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__FRAMES_RXED_64__COUNT__RESET                               0
#define EMAC_REGS__FRAMES_RXED_64__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_64__TYPE                                uint32_t
#define EMAC_REGS__FRAMES_RXED_64__READ                             0xffffffffU
#define EMAC_REGS__FRAMES_RXED_64__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_64_MACRO__ */


/* macros for frames_rxed_64 */
#define INST_FRAMES_RXED_64__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_65 */
#ifndef __EMAC_REGS__FRAMES_RXED_65_MACRO__
#define __EMAC_REGS__FRAMES_RXED_65_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_65__COUNT__SHIFT                               0
#define EMAC_REGS__FRAMES_RXED_65__COUNT__WIDTH                              32
#define EMAC_REGS__FRAMES_RXED_65__COUNT__MASK                      0xffffffffU
#define EMAC_REGS__FRAMES_RXED_65__COUNT__RESET                               0
#define EMAC_REGS__FRAMES_RXED_65__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_65__TYPE                                uint32_t
#define EMAC_REGS__FRAMES_RXED_65__READ                             0xffffffffU
#define EMAC_REGS__FRAMES_RXED_65__RCLR                             0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_65_MACRO__ */


/* macros for frames_rxed_65 */
#define INST_FRAMES_RXED_65__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_128 */
#ifndef __EMAC_REGS__FRAMES_RXED_128_MACRO__
#define __EMAC_REGS__FRAMES_RXED_128_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_128__COUNT__SHIFT                              0
#define EMAC_REGS__FRAMES_RXED_128__COUNT__WIDTH                             32
#define EMAC_REGS__FRAMES_RXED_128__COUNT__MASK                     0xffffffffU
#define EMAC_REGS__FRAMES_RXED_128__COUNT__RESET                              0
#define EMAC_REGS__FRAMES_RXED_128__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_128__TYPE                               uint32_t
#define EMAC_REGS__FRAMES_RXED_128__READ                            0xffffffffU
#define EMAC_REGS__FRAMES_RXED_128__RCLR                            0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_128_MACRO__ */


/* macros for frames_rxed_128 */
#define INST_FRAMES_RXED_128__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_256 */
#ifndef __EMAC_REGS__FRAMES_RXED_256_MACRO__
#define __EMAC_REGS__FRAMES_RXED_256_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_256__COUNT__SHIFT                              0
#define EMAC_REGS__FRAMES_RXED_256__COUNT__WIDTH                             32
#define EMAC_REGS__FRAMES_RXED_256__COUNT__MASK                     0xffffffffU
#define EMAC_REGS__FRAMES_RXED_256__COUNT__RESET                              0
#define EMAC_REGS__FRAMES_RXED_256__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_256__TYPE                               uint32_t
#define EMAC_REGS__FRAMES_RXED_256__READ                            0xffffffffU
#define EMAC_REGS__FRAMES_RXED_256__RCLR                            0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_256_MACRO__ */


/* macros for frames_rxed_256 */
#define INST_FRAMES_RXED_256__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_512 */
#ifndef __EMAC_REGS__FRAMES_RXED_512_MACRO__
#define __EMAC_REGS__FRAMES_RXED_512_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_512__COUNT__SHIFT                              0
#define EMAC_REGS__FRAMES_RXED_512__COUNT__WIDTH                             32
#define EMAC_REGS__FRAMES_RXED_512__COUNT__MASK                     0xffffffffU
#define EMAC_REGS__FRAMES_RXED_512__COUNT__RESET                              0
#define EMAC_REGS__FRAMES_RXED_512__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_512__TYPE                               uint32_t
#define EMAC_REGS__FRAMES_RXED_512__READ                            0xffffffffU
#define EMAC_REGS__FRAMES_RXED_512__RCLR                            0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_512_MACRO__ */


/* macros for frames_rxed_512 */
#define INST_FRAMES_RXED_512__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_1024 */
#ifndef __EMAC_REGS__FRAMES_RXED_1024_MACRO__
#define __EMAC_REGS__FRAMES_RXED_1024_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_1024__COUNT__SHIFT                             0
#define EMAC_REGS__FRAMES_RXED_1024__COUNT__WIDTH                            32
#define EMAC_REGS__FRAMES_RXED_1024__COUNT__MASK                    0xffffffffU
#define EMAC_REGS__FRAMES_RXED_1024__COUNT__RESET                             0
#define EMAC_REGS__FRAMES_RXED_1024__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_1024__TYPE                              uint32_t
#define EMAC_REGS__FRAMES_RXED_1024__READ                           0xffffffffU
#define EMAC_REGS__FRAMES_RXED_1024__RCLR                           0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_1024_MACRO__ */


/* macros for frames_rxed_1024 */
#define INST_FRAMES_RXED_1024__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::frames_rxed_1519 */
#ifndef __EMAC_REGS__FRAMES_RXED_1519_MACRO__
#define __EMAC_REGS__FRAMES_RXED_1519_MACRO__

/* macros for field count */
#define EMAC_REGS__FRAMES_RXED_1519__COUNT__SHIFT                             0
#define EMAC_REGS__FRAMES_RXED_1519__COUNT__WIDTH                            32
#define EMAC_REGS__FRAMES_RXED_1519__COUNT__MASK                    0xffffffffU
#define EMAC_REGS__FRAMES_RXED_1519__COUNT__RESET                             0
#define EMAC_REGS__FRAMES_RXED_1519__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__FRAMES_RXED_1519__TYPE                              uint32_t
#define EMAC_REGS__FRAMES_RXED_1519__READ                           0xffffffffU
#define EMAC_REGS__FRAMES_RXED_1519__RCLR                           0xffffffffU

#endif /* __EMAC_REGS__FRAMES_RXED_1519_MACRO__ */


/* macros for frames_rxed_1519 */
#define INST_FRAMES_RXED_1519__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::undersize_frames */
#ifndef __EMAC_REGS__UNDERSIZE_FRAMES_MACRO__
#define __EMAC_REGS__UNDERSIZE_FRAMES_MACRO__

/* macros for field count */
#define EMAC_REGS__UNDERSIZE_FRAMES__COUNT__SHIFT                             0
#define EMAC_REGS__UNDERSIZE_FRAMES__COUNT__WIDTH                            10
#define EMAC_REGS__UNDERSIZE_FRAMES__COUNT__MASK                    0x000003ffU
#define EMAC_REGS__UNDERSIZE_FRAMES__COUNT__RESET                             0
#define EMAC_REGS__UNDERSIZE_FRAMES__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__UNDERSIZE_FRAMES__RESERVED_31_10__SHIFT                   10
#define EMAC_REGS__UNDERSIZE_FRAMES__RESERVED_31_10__WIDTH                   22
#define EMAC_REGS__UNDERSIZE_FRAMES__RESERVED_31_10__MASK           0xfffffc00U
#define EMAC_REGS__UNDERSIZE_FRAMES__RESERVED_31_10__RESET                    0
#define EMAC_REGS__UNDERSIZE_FRAMES__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__UNDERSIZE_FRAMES__TYPE                              uint32_t
#define EMAC_REGS__UNDERSIZE_FRAMES__READ                           0xffffffffU
#define EMAC_REGS__UNDERSIZE_FRAMES__RCLR                           0x000003ffU

#endif /* __EMAC_REGS__UNDERSIZE_FRAMES_MACRO__ */


/* macros for undersize_frames */
#define INST_UNDERSIZE_FRAMES__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::excessive_rx_length */
#ifndef __EMAC_REGS__EXCESSIVE_RX_LENGTH_MACRO__
#define __EMAC_REGS__EXCESSIVE_RX_LENGTH_MACRO__

/* macros for field count */
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__SHIFT                          0
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__WIDTH                         10
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__MASK                 0x000003ffU
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__RESET                          0
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__RESERVED_31_10__SHIFT                10
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__RESERVED_31_10__WIDTH                22
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__RESERVED_31_10__MASK        0xfffffc00U
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__RESERVED_31_10__RESET                 0
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__TYPE                           uint32_t
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__READ                        0xffffffffU
#define EMAC_REGS__EXCESSIVE_RX_LENGTH__RCLR                        0x000003ffU

#endif /* __EMAC_REGS__EXCESSIVE_RX_LENGTH_MACRO__ */


/* macros for excessive_rx_length */
#define INST_EXCESSIVE_RX_LENGTH__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_jabbers */
#ifndef __EMAC_REGS__RX_JABBERS_MACRO__
#define __EMAC_REGS__RX_JABBERS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_JABBERS__COUNT__SHIFT                                   0
#define EMAC_REGS__RX_JABBERS__COUNT__WIDTH                                  10
#define EMAC_REGS__RX_JABBERS__COUNT__MASK                          0x000003ffU
#define EMAC_REGS__RX_JABBERS__COUNT__RESET                                   0
#define EMAC_REGS__RX_JABBERS__COUNT__READ(src) ((uint32_t)(src) & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__RX_JABBERS__RESERVED_31_10__SHIFT                         10
#define EMAC_REGS__RX_JABBERS__RESERVED_31_10__WIDTH                         22
#define EMAC_REGS__RX_JABBERS__RESERVED_31_10__MASK                 0xfffffc00U
#define EMAC_REGS__RX_JABBERS__RESERVED_31_10__RESET                          0
#define EMAC_REGS__RX_JABBERS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__RX_JABBERS__TYPE                                    uint32_t
#define EMAC_REGS__RX_JABBERS__READ                                 0xffffffffU
#define EMAC_REGS__RX_JABBERS__RCLR                                 0x000003ffU

#endif /* __EMAC_REGS__RX_JABBERS_MACRO__ */


/* macros for rx_jabbers */
#define INST_RX_JABBERS__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::fcs_errors */
#ifndef __EMAC_REGS__FCS_ERRORS_MACRO__
#define __EMAC_REGS__FCS_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__FCS_ERRORS__COUNT__SHIFT                                   0
#define EMAC_REGS__FCS_ERRORS__COUNT__WIDTH                                  10
#define EMAC_REGS__FCS_ERRORS__COUNT__MASK                          0x000003ffU
#define EMAC_REGS__FCS_ERRORS__COUNT__RESET                                   0
#define EMAC_REGS__FCS_ERRORS__COUNT__READ(src) ((uint32_t)(src) & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__FCS_ERRORS__RESERVED_31_10__SHIFT                         10
#define EMAC_REGS__FCS_ERRORS__RESERVED_31_10__WIDTH                         22
#define EMAC_REGS__FCS_ERRORS__RESERVED_31_10__MASK                 0xfffffc00U
#define EMAC_REGS__FCS_ERRORS__RESERVED_31_10__RESET                          0
#define EMAC_REGS__FCS_ERRORS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__FCS_ERRORS__TYPE                                    uint32_t
#define EMAC_REGS__FCS_ERRORS__READ                                 0xffffffffU
#define EMAC_REGS__FCS_ERRORS__RCLR                                 0x000003ffU

#endif /* __EMAC_REGS__FCS_ERRORS_MACRO__ */


/* macros for fcs_errors */
#define INST_FCS_ERRORS__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_length_errors */
#ifndef __EMAC_REGS__RX_LENGTH_ERRORS_MACRO__
#define __EMAC_REGS__RX_LENGTH_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_LENGTH_ERRORS__COUNT__SHIFT                             0
#define EMAC_REGS__RX_LENGTH_ERRORS__COUNT__WIDTH                            10
#define EMAC_REGS__RX_LENGTH_ERRORS__COUNT__MASK                    0x000003ffU
#define EMAC_REGS__RX_LENGTH_ERRORS__COUNT__RESET                             0
#define EMAC_REGS__RX_LENGTH_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__RX_LENGTH_ERRORS__RESERVED_31_10__SHIFT                   10
#define EMAC_REGS__RX_LENGTH_ERRORS__RESERVED_31_10__WIDTH                   22
#define EMAC_REGS__RX_LENGTH_ERRORS__RESERVED_31_10__MASK           0xfffffc00U
#define EMAC_REGS__RX_LENGTH_ERRORS__RESERVED_31_10__RESET                    0
#define EMAC_REGS__RX_LENGTH_ERRORS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__RX_LENGTH_ERRORS__TYPE                              uint32_t
#define EMAC_REGS__RX_LENGTH_ERRORS__READ                           0xffffffffU
#define EMAC_REGS__RX_LENGTH_ERRORS__RCLR                           0x000003ffU

#endif /* __EMAC_REGS__RX_LENGTH_ERRORS_MACRO__ */


/* macros for rx_length_errors */
#define INST_RX_LENGTH_ERRORS__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_symbol_errors */
#ifndef __EMAC_REGS__RX_SYMBOL_ERRORS_MACRO__
#define __EMAC_REGS__RX_SYMBOL_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__SHIFT                             0
#define EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__WIDTH                            10
#define EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__MASK                    0x000003ffU
#define EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__RESET                             0
#define EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__RX_SYMBOL_ERRORS__RESERVED_31_10__SHIFT                   10
#define EMAC_REGS__RX_SYMBOL_ERRORS__RESERVED_31_10__WIDTH                   22
#define EMAC_REGS__RX_SYMBOL_ERRORS__RESERVED_31_10__MASK           0xfffffc00U
#define EMAC_REGS__RX_SYMBOL_ERRORS__RESERVED_31_10__RESET                    0
#define EMAC_REGS__RX_SYMBOL_ERRORS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__RX_SYMBOL_ERRORS__TYPE                              uint32_t
#define EMAC_REGS__RX_SYMBOL_ERRORS__READ                           0xffffffffU
#define EMAC_REGS__RX_SYMBOL_ERRORS__RCLR                           0x000003ffU

#endif /* __EMAC_REGS__RX_SYMBOL_ERRORS_MACRO__ */


/* macros for rx_symbol_errors */
#define INST_RX_SYMBOL_ERRORS__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::alignment_errors */
#ifndef __EMAC_REGS__ALIGNMENT_ERRORS_MACRO__
#define __EMAC_REGS__ALIGNMENT_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__ALIGNMENT_ERRORS__COUNT__SHIFT                             0
#define EMAC_REGS__ALIGNMENT_ERRORS__COUNT__WIDTH                            10
#define EMAC_REGS__ALIGNMENT_ERRORS__COUNT__MASK                    0x000003ffU
#define EMAC_REGS__ALIGNMENT_ERRORS__COUNT__RESET                             0
#define EMAC_REGS__ALIGNMENT_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__ALIGNMENT_ERRORS__RESERVED_31_10__SHIFT                   10
#define EMAC_REGS__ALIGNMENT_ERRORS__RESERVED_31_10__WIDTH                   22
#define EMAC_REGS__ALIGNMENT_ERRORS__RESERVED_31_10__MASK           0xfffffc00U
#define EMAC_REGS__ALIGNMENT_ERRORS__RESERVED_31_10__RESET                    0
#define EMAC_REGS__ALIGNMENT_ERRORS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__ALIGNMENT_ERRORS__TYPE                              uint32_t
#define EMAC_REGS__ALIGNMENT_ERRORS__READ                           0xffffffffU
#define EMAC_REGS__ALIGNMENT_ERRORS__RCLR                           0x000003ffU

#endif /* __EMAC_REGS__ALIGNMENT_ERRORS_MACRO__ */


/* macros for alignment_errors */
#define INST_ALIGNMENT_ERRORS__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_resource_errors */
#ifndef __EMAC_REGS__RX_RESOURCE_ERRORS_MACRO__
#define __EMAC_REGS__RX_RESOURCE_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_RESOURCE_ERRORS__COUNT__SHIFT                           0
#define EMAC_REGS__RX_RESOURCE_ERRORS__COUNT__WIDTH                          18
#define EMAC_REGS__RX_RESOURCE_ERRORS__COUNT__MASK                  0x0003ffffU
#define EMAC_REGS__RX_RESOURCE_ERRORS__COUNT__RESET                           0
#define EMAC_REGS__RX_RESOURCE_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0003ffffU)

/* macros for field reserved_31_18 */
#define EMAC_REGS__RX_RESOURCE_ERRORS__RESERVED_31_18__SHIFT                 18
#define EMAC_REGS__RX_RESOURCE_ERRORS__RESERVED_31_18__WIDTH                 14
#define EMAC_REGS__RX_RESOURCE_ERRORS__RESERVED_31_18__MASK         0xfffc0000U
#define EMAC_REGS__RX_RESOURCE_ERRORS__RESERVED_31_18__RESET                  0
#define EMAC_REGS__RX_RESOURCE_ERRORS__RESERVED_31_18__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffc0000U) >> 18)
#define EMAC_REGS__RX_RESOURCE_ERRORS__TYPE                            uint32_t
#define EMAC_REGS__RX_RESOURCE_ERRORS__READ                         0xffffffffU
#define EMAC_REGS__RX_RESOURCE_ERRORS__RCLR                         0x0003ffffU

#endif /* __EMAC_REGS__RX_RESOURCE_ERRORS_MACRO__ */


/* macros for rx_resource_errors */
#define INST_RX_RESOURCE_ERRORS__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_overruns */
#ifndef __EMAC_REGS__RX_OVERRUNS_MACRO__
#define __EMAC_REGS__RX_OVERRUNS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_OVERRUNS__COUNT__SHIFT                                  0
#define EMAC_REGS__RX_OVERRUNS__COUNT__WIDTH                                 10
#define EMAC_REGS__RX_OVERRUNS__COUNT__MASK                         0x000003ffU
#define EMAC_REGS__RX_OVERRUNS__COUNT__RESET                                  0
#define EMAC_REGS__RX_OVERRUNS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000003ffU)

/* macros for field reserved_31_10 */
#define EMAC_REGS__RX_OVERRUNS__RESERVED_31_10__SHIFT                        10
#define EMAC_REGS__RX_OVERRUNS__RESERVED_31_10__WIDTH                        22
#define EMAC_REGS__RX_OVERRUNS__RESERVED_31_10__MASK                0xfffffc00U
#define EMAC_REGS__RX_OVERRUNS__RESERVED_31_10__RESET                         0
#define EMAC_REGS__RX_OVERRUNS__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__RX_OVERRUNS__TYPE                                   uint32_t
#define EMAC_REGS__RX_OVERRUNS__READ                                0xffffffffU
#define EMAC_REGS__RX_OVERRUNS__RCLR                                0x000003ffU

#endif /* __EMAC_REGS__RX_OVERRUNS_MACRO__ */


/* macros for rx_overruns */
#define INST_RX_OVERRUNS__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_ip_ck_errors */
#ifndef __EMAC_REGS__RX_IP_CK_ERRORS_MACRO__
#define __EMAC_REGS__RX_IP_CK_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_IP_CK_ERRORS__COUNT__SHIFT                              0
#define EMAC_REGS__RX_IP_CK_ERRORS__COUNT__WIDTH                              8
#define EMAC_REGS__RX_IP_CK_ERRORS__COUNT__MASK                     0x000000ffU
#define EMAC_REGS__RX_IP_CK_ERRORS__COUNT__RESET                              0
#define EMAC_REGS__RX_IP_CK_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)

/* macros for field reserved_31_8 */
#define EMAC_REGS__RX_IP_CK_ERRORS__RESERVED_31_8__SHIFT                      8
#define EMAC_REGS__RX_IP_CK_ERRORS__RESERVED_31_8__WIDTH                     24
#define EMAC_REGS__RX_IP_CK_ERRORS__RESERVED_31_8__MASK             0xffffff00U
#define EMAC_REGS__RX_IP_CK_ERRORS__RESERVED_31_8__RESET                      0
#define EMAC_REGS__RX_IP_CK_ERRORS__RESERVED_31_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffff00U) >> 8)
#define EMAC_REGS__RX_IP_CK_ERRORS__TYPE                               uint32_t
#define EMAC_REGS__RX_IP_CK_ERRORS__READ                            0xffffffffU
#define EMAC_REGS__RX_IP_CK_ERRORS__RCLR                            0x000000ffU

#endif /* __EMAC_REGS__RX_IP_CK_ERRORS_MACRO__ */


/* macros for rx_ip_ck_errors */
#define INST_RX_IP_CK_ERRORS__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_tcp_ck_errors */
#ifndef __EMAC_REGS__RX_TCP_CK_ERRORS_MACRO__
#define __EMAC_REGS__RX_TCP_CK_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__SHIFT                             0
#define EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__WIDTH                             8
#define EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__MASK                    0x000000ffU
#define EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__RESET                             0
#define EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)

/* macros for field reserved_31_8 */
#define EMAC_REGS__RX_TCP_CK_ERRORS__RESERVED_31_8__SHIFT                     8
#define EMAC_REGS__RX_TCP_CK_ERRORS__RESERVED_31_8__WIDTH                    24
#define EMAC_REGS__RX_TCP_CK_ERRORS__RESERVED_31_8__MASK            0xffffff00U
#define EMAC_REGS__RX_TCP_CK_ERRORS__RESERVED_31_8__RESET                     0
#define EMAC_REGS__RX_TCP_CK_ERRORS__RESERVED_31_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffff00U) >> 8)
#define EMAC_REGS__RX_TCP_CK_ERRORS__TYPE                              uint32_t
#define EMAC_REGS__RX_TCP_CK_ERRORS__READ                           0xffffffffU
#define EMAC_REGS__RX_TCP_CK_ERRORS__RCLR                           0x000000ffU

#endif /* __EMAC_REGS__RX_TCP_CK_ERRORS_MACRO__ */


/* macros for rx_tcp_ck_errors */
#define INST_RX_TCP_CK_ERRORS__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_udp_ck_errors */
#ifndef __EMAC_REGS__RX_UDP_CK_ERRORS_MACRO__
#define __EMAC_REGS__RX_UDP_CK_ERRORS_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__SHIFT                             0
#define EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__WIDTH                             8
#define EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__MASK                    0x000000ffU
#define EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__RESET                             0
#define EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)

/* macros for field reserved_31_8 */
#define EMAC_REGS__RX_UDP_CK_ERRORS__RESERVED_31_8__SHIFT                     8
#define EMAC_REGS__RX_UDP_CK_ERRORS__RESERVED_31_8__WIDTH                    24
#define EMAC_REGS__RX_UDP_CK_ERRORS__RESERVED_31_8__MASK            0xffffff00U
#define EMAC_REGS__RX_UDP_CK_ERRORS__RESERVED_31_8__RESET                     0
#define EMAC_REGS__RX_UDP_CK_ERRORS__RESERVED_31_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffff00U) >> 8)
#define EMAC_REGS__RX_UDP_CK_ERRORS__TYPE                              uint32_t
#define EMAC_REGS__RX_UDP_CK_ERRORS__READ                           0xffffffffU
#define EMAC_REGS__RX_UDP_CK_ERRORS__RCLR                           0x000000ffU

#endif /* __EMAC_REGS__RX_UDP_CK_ERRORS_MACRO__ */


/* macros for rx_udp_ck_errors */
#define INST_RX_UDP_CK_ERRORS__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::auto_flushed_pkts */
#ifndef __EMAC_REGS__AUTO_FLUSHED_PKTS_MACRO__
#define __EMAC_REGS__AUTO_FLUSHED_PKTS_MACRO__

/* macros for field count */
#define EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__SHIFT                            0
#define EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__WIDTH                           16
#define EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__MASK                   0x0000ffffU
#define EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__RESET                            0
#define EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__AUTO_FLUSHED_PKTS__RESERVED_31_16__SHIFT                  16
#define EMAC_REGS__AUTO_FLUSHED_PKTS__RESERVED_31_16__WIDTH                  16
#define EMAC_REGS__AUTO_FLUSHED_PKTS__RESERVED_31_16__MASK          0xffff0000U
#define EMAC_REGS__AUTO_FLUSHED_PKTS__RESERVED_31_16__RESET                   0
#define EMAC_REGS__AUTO_FLUSHED_PKTS__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__AUTO_FLUSHED_PKTS__TYPE                             uint32_t
#define EMAC_REGS__AUTO_FLUSHED_PKTS__READ                          0xffffffffU
#define EMAC_REGS__AUTO_FLUSHED_PKTS__RCLR                          0x0000ffffU

#endif /* __EMAC_REGS__AUTO_FLUSHED_PKTS_MACRO__ */


/* macros for auto_flushed_pkts */
#define INST_AUTO_FLUSHED_PKTS__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_timer_incr_sub_nsec */
#ifndef __EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC_MACRO__
#define __EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC_MACRO__

/* macros for field sub_ns_incr */
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__SHIFT                0
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__WIDTH               16
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__MASK       0x0000ffffU
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__RESET                0
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_23_16 */
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__RESERVED_23_16__SHIFT            16
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__RESERVED_23_16__WIDTH             8
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__RESERVED_23_16__MASK    0x00ff0000U
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__RESERVED_23_16__RESET             0
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__RESERVED_23_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)

/* macros for field sub_ns_incr_lsb */
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__SHIFT           24
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__WIDTH            8
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__MASK   0xff000000U
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__RESET            0
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0xff000000U)
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xff000000U) | (((uint32_t)(src) <<\
                    24) & 0xff000000U)
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0xff000000U)))
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__TYPE                       uint32_t
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__READ                    0xffffffffU
#define EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__WRITE                   0xffffffffU

#endif /* __EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC_MACRO__ */


/* macros for tsu_timer_incr_sub_nsec */
#define INST_TSU_TIMER_INCR_SUB_NSEC__NUM                                     1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_timer_msb_sec */
#ifndef __EMAC_REGS__TSU_TIMER_MSB_SEC_MACRO__
#define __EMAC_REGS__TSU_TIMER_MSB_SEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__SHIFT                            0
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__WIDTH                           16
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__MASK                   0x0000ffffU
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__RESET                            0
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_TIMER_MSB_SEC__RESERVED_31_16__SHIFT                  16
#define EMAC_REGS__TSU_TIMER_MSB_SEC__RESERVED_31_16__WIDTH                  16
#define EMAC_REGS__TSU_TIMER_MSB_SEC__RESERVED_31_16__MASK          0xffff0000U
#define EMAC_REGS__TSU_TIMER_MSB_SEC__RESERVED_31_16__RESET                   0
#define EMAC_REGS__TSU_TIMER_MSB_SEC__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_TIMER_MSB_SEC__TYPE                             uint32_t
#define EMAC_REGS__TSU_TIMER_MSB_SEC__READ                          0xffffffffU
#define EMAC_REGS__TSU_TIMER_MSB_SEC__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__TSU_TIMER_MSB_SEC_MACRO__ */


/* macros for tsu_timer_msb_sec */
#define INST_TSU_TIMER_MSB_SEC__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_strobe_msb_sec */
#ifndef __EMAC_REGS__TSU_STROBE_MSB_SEC_MACRO__
#define __EMAC_REGS__TSU_STROBE_MSB_SEC_MACRO__

/* macros for field strobe */
#define EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__SHIFT                          0
#define EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__WIDTH                         16
#define EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__MASK                 0x0000ffffU
#define EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__RESET                          0
#define EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__TSU_STROBE_MSB_SEC__RESERVED_31_16__SHIFT                 16
#define EMAC_REGS__TSU_STROBE_MSB_SEC__RESERVED_31_16__WIDTH                 16
#define EMAC_REGS__TSU_STROBE_MSB_SEC__RESERVED_31_16__MASK         0xffff0000U
#define EMAC_REGS__TSU_STROBE_MSB_SEC__RESERVED_31_16__RESET                  0
#define EMAC_REGS__TSU_STROBE_MSB_SEC__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TSU_STROBE_MSB_SEC__TYPE                            uint32_t
#define EMAC_REGS__TSU_STROBE_MSB_SEC__READ                         0xffffffffU

#endif /* __EMAC_REGS__TSU_STROBE_MSB_SEC_MACRO__ */


/* macros for tsu_strobe_msb_sec */
#define INST_TSU_STROBE_MSB_SEC__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_strobe_sec */
#ifndef __EMAC_REGS__TSU_STROBE_SEC_MACRO__
#define __EMAC_REGS__TSU_STROBE_SEC_MACRO__

/* macros for field strobe */
#define EMAC_REGS__TSU_STROBE_SEC__STROBE__SHIFT                              0
#define EMAC_REGS__TSU_STROBE_SEC__STROBE__WIDTH                             32
#define EMAC_REGS__TSU_STROBE_SEC__STROBE__MASK                     0xffffffffU
#define EMAC_REGS__TSU_STROBE_SEC__STROBE__RESET                              0
#define EMAC_REGS__TSU_STROBE_SEC__STROBE__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_STROBE_SEC__TYPE                                uint32_t
#define EMAC_REGS__TSU_STROBE_SEC__READ                             0xffffffffU

#endif /* __EMAC_REGS__TSU_STROBE_SEC_MACRO__ */


/* macros for tsu_strobe_sec */
#define INST_TSU_STROBE_SEC__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_strobe_nsec */
#ifndef __EMAC_REGS__TSU_STROBE_NSEC_MACRO__
#define __EMAC_REGS__TSU_STROBE_NSEC_MACRO__

/* macros for field strobe */
#define EMAC_REGS__TSU_STROBE_NSEC__STROBE__SHIFT                             0
#define EMAC_REGS__TSU_STROBE_NSEC__STROBE__WIDTH                            30
#define EMAC_REGS__TSU_STROBE_NSEC__STROBE__MASK                    0x3fffffffU
#define EMAC_REGS__TSU_STROBE_NSEC__STROBE__RESET                             0
#define EMAC_REGS__TSU_STROBE_NSEC__STROBE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)

/* macros for field reserved_31_30 */
#define EMAC_REGS__TSU_STROBE_NSEC__RESERVED_31_30__SHIFT                    30
#define EMAC_REGS__TSU_STROBE_NSEC__RESERVED_31_30__WIDTH                     2
#define EMAC_REGS__TSU_STROBE_NSEC__RESERVED_31_30__MASK            0xc0000000U
#define EMAC_REGS__TSU_STROBE_NSEC__RESERVED_31_30__RESET                     0
#define EMAC_REGS__TSU_STROBE_NSEC__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TSU_STROBE_NSEC__TYPE                               uint32_t
#define EMAC_REGS__TSU_STROBE_NSEC__READ                            0xffffffffU

#endif /* __EMAC_REGS__TSU_STROBE_NSEC_MACRO__ */


/* macros for tsu_strobe_nsec */
#define INST_TSU_STROBE_NSEC__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_timer_sec */
#ifndef __EMAC_REGS__TSU_TIMER_SEC_MACRO__
#define __EMAC_REGS__TSU_TIMER_SEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__SHIFT                                0
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__WIDTH                               32
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__MASK                       0xffffffffU
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__RESET                                0
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__TSU_TIMER_SEC__TIMER__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__TSU_TIMER_SEC__TYPE                                 uint32_t
#define EMAC_REGS__TSU_TIMER_SEC__READ                              0xffffffffU
#define EMAC_REGS__TSU_TIMER_SEC__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__TSU_TIMER_SEC_MACRO__ */


/* macros for tsu_timer_sec */
#define INST_TSU_TIMER_SEC__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_timer_nsec */
#ifndef __EMAC_REGS__TSU_TIMER_NSEC_MACRO__
#define __EMAC_REGS__TSU_TIMER_NSEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__SHIFT                               0
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__WIDTH                              30
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__MASK                      0x3fffffffU
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__RESET                               0
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__TSU_TIMER_NSEC__TIMER__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field reserved_31_30 */
#define EMAC_REGS__TSU_TIMER_NSEC__RESERVED_31_30__SHIFT                     30
#define EMAC_REGS__TSU_TIMER_NSEC__RESERVED_31_30__WIDTH                      2
#define EMAC_REGS__TSU_TIMER_NSEC__RESERVED_31_30__MASK             0xc0000000U
#define EMAC_REGS__TSU_TIMER_NSEC__RESERVED_31_30__RESET                      0
#define EMAC_REGS__TSU_TIMER_NSEC__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TSU_TIMER_NSEC__TYPE                                uint32_t
#define EMAC_REGS__TSU_TIMER_NSEC__READ                             0xffffffffU
#define EMAC_REGS__TSU_TIMER_NSEC__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__TSU_TIMER_NSEC_MACRO__ */


/* macros for tsu_timer_nsec */
#define INST_TSU_TIMER_NSEC__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_timer_adjust */
#ifndef __EMAC_REGS__TSU_TIMER_ADJUST_MACRO__
#define __EMAC_REGS__TSU_TIMER_ADJUST_MACRO__

/* macros for field increment_value */
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__SHIFT                   0
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__WIDTH                  30
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__MASK          0x3fffffffU
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__RESET                   0
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field reserved_30_30 */
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__SHIFT                   30
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__WIDTH                    1
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__MASK           0x40000000U
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__RESET                    0
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__TSU_TIMER_ADJUST__RESERVED_30_30__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field add_subtract */
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__SHIFT                     31
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__WIDTH                      1
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__MASK             0x80000000U
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__RESET                      0
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 31) & 0x80000000U)
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | (((uint32_t)(src) <<\
                    31) & 0x80000000U)
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 31) & ~0x80000000U)))
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__TSU_TIMER_ADJUST__TYPE                              uint32_t
#define EMAC_REGS__TSU_TIMER_ADJUST__READ                           0x40000000U
#define EMAC_REGS__TSU_TIMER_ADJUST__WRITE                          0x40000000U

#endif /* __EMAC_REGS__TSU_TIMER_ADJUST_MACRO__ */


/* macros for tsu_timer_adjust */
#define INST_TSU_TIMER_ADJUST__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_timer_incr */
#ifndef __EMAC_REGS__TSU_TIMER_INCR_MACRO__
#define __EMAC_REGS__TSU_TIMER_INCR_MACRO__

/* macros for field ns_increment */
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__SHIFT                        0
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__WIDTH                        8
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__MASK               0x000000ffU
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__RESET                        0
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field alt_ns_incr */
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__SHIFT                         8
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__WIDTH                         8
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__MASK                0x0000ff00U
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__RESET                         0
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field num_incs */
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__SHIFT                           16
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__WIDTH                            8
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__MASK                   0x00ff0000U
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__RESET                            0
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field reserved_31_24 */
#define EMAC_REGS__TSU_TIMER_INCR__RESERVED_31_24__SHIFT                     24
#define EMAC_REGS__TSU_TIMER_INCR__RESERVED_31_24__WIDTH                      8
#define EMAC_REGS__TSU_TIMER_INCR__RESERVED_31_24__MASK             0xff000000U
#define EMAC_REGS__TSU_TIMER_INCR__RESERVED_31_24__RESET                      0
#define EMAC_REGS__TSU_TIMER_INCR__RESERVED_31_24__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__TSU_TIMER_INCR__TYPE                                uint32_t
#define EMAC_REGS__TSU_TIMER_INCR__READ                             0xffffffffU
#define EMAC_REGS__TSU_TIMER_INCR__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__TSU_TIMER_INCR_MACRO__ */


/* macros for tsu_timer_incr */
#define INST_TSU_TIMER_INCR__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_ptp_tx_sec */
#ifndef __EMAC_REGS__TSU_PTP_TX_SEC_MACRO__
#define __EMAC_REGS__TSU_PTP_TX_SEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PTP_TX_SEC__TIMER__SHIFT                               0
#define EMAC_REGS__TSU_PTP_TX_SEC__TIMER__WIDTH                              32
#define EMAC_REGS__TSU_PTP_TX_SEC__TIMER__MASK                      0xffffffffU
#define EMAC_REGS__TSU_PTP_TX_SEC__TIMER__RESET                               0
#define EMAC_REGS__TSU_PTP_TX_SEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_PTP_TX_SEC__TYPE                                uint32_t
#define EMAC_REGS__TSU_PTP_TX_SEC__READ                             0xffffffffU

#endif /* __EMAC_REGS__TSU_PTP_TX_SEC_MACRO__ */


/* macros for tsu_ptp_tx_sec */
#define INST_TSU_PTP_TX_SEC__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_ptp_tx_nsec */
#ifndef __EMAC_REGS__TSU_PTP_TX_NSEC_MACRO__
#define __EMAC_REGS__TSU_PTP_TX_NSEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__SHIFT                              0
#define EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__WIDTH                             30
#define EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__MASK                     0x3fffffffU
#define EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__RESET                              0
#define EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)

/* macros for field reserved_31_30 */
#define EMAC_REGS__TSU_PTP_TX_NSEC__RESERVED_31_30__SHIFT                    30
#define EMAC_REGS__TSU_PTP_TX_NSEC__RESERVED_31_30__WIDTH                     2
#define EMAC_REGS__TSU_PTP_TX_NSEC__RESERVED_31_30__MASK            0xc0000000U
#define EMAC_REGS__TSU_PTP_TX_NSEC__RESERVED_31_30__RESET                     0
#define EMAC_REGS__TSU_PTP_TX_NSEC__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TSU_PTP_TX_NSEC__TYPE                               uint32_t
#define EMAC_REGS__TSU_PTP_TX_NSEC__READ                            0xffffffffU

#endif /* __EMAC_REGS__TSU_PTP_TX_NSEC_MACRO__ */


/* macros for tsu_ptp_tx_nsec */
#define INST_TSU_PTP_TX_NSEC__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_ptp_rx_sec */
#ifndef __EMAC_REGS__TSU_PTP_RX_SEC_MACRO__
#define __EMAC_REGS__TSU_PTP_RX_SEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PTP_RX_SEC__TIMER__SHIFT                               0
#define EMAC_REGS__TSU_PTP_RX_SEC__TIMER__WIDTH                              32
#define EMAC_REGS__TSU_PTP_RX_SEC__TIMER__MASK                      0xffffffffU
#define EMAC_REGS__TSU_PTP_RX_SEC__TIMER__RESET                               0
#define EMAC_REGS__TSU_PTP_RX_SEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_PTP_RX_SEC__TYPE                                uint32_t
#define EMAC_REGS__TSU_PTP_RX_SEC__READ                             0xffffffffU

#endif /* __EMAC_REGS__TSU_PTP_RX_SEC_MACRO__ */


/* macros for tsu_ptp_rx_sec */
#define INST_TSU_PTP_RX_SEC__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_ptp_rx_nsec */
#ifndef __EMAC_REGS__TSU_PTP_RX_NSEC_MACRO__
#define __EMAC_REGS__TSU_PTP_RX_NSEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__SHIFT                              0
#define EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__WIDTH                             30
#define EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__MASK                     0x3fffffffU
#define EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__RESET                              0
#define EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)

/* macros for field reserved_31_30 */
#define EMAC_REGS__TSU_PTP_RX_NSEC__RESERVED_31_30__SHIFT                    30
#define EMAC_REGS__TSU_PTP_RX_NSEC__RESERVED_31_30__WIDTH                     2
#define EMAC_REGS__TSU_PTP_RX_NSEC__RESERVED_31_30__MASK            0xc0000000U
#define EMAC_REGS__TSU_PTP_RX_NSEC__RESERVED_31_30__RESET                     0
#define EMAC_REGS__TSU_PTP_RX_NSEC__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TSU_PTP_RX_NSEC__TYPE                               uint32_t
#define EMAC_REGS__TSU_PTP_RX_NSEC__READ                            0xffffffffU

#endif /* __EMAC_REGS__TSU_PTP_RX_NSEC_MACRO__ */


/* macros for tsu_ptp_rx_nsec */
#define INST_TSU_PTP_RX_NSEC__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_peer_tx_sec */
#ifndef __EMAC_REGS__TSU_PEER_TX_SEC_MACRO__
#define __EMAC_REGS__TSU_PEER_TX_SEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PEER_TX_SEC__TIMER__SHIFT                              0
#define EMAC_REGS__TSU_PEER_TX_SEC__TIMER__WIDTH                             32
#define EMAC_REGS__TSU_PEER_TX_SEC__TIMER__MASK                     0xffffffffU
#define EMAC_REGS__TSU_PEER_TX_SEC__TIMER__RESET                              0
#define EMAC_REGS__TSU_PEER_TX_SEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_PEER_TX_SEC__TYPE                               uint32_t
#define EMAC_REGS__TSU_PEER_TX_SEC__READ                            0xffffffffU

#endif /* __EMAC_REGS__TSU_PEER_TX_SEC_MACRO__ */


/* macros for tsu_peer_tx_sec */
#define INST_TSU_PEER_TX_SEC__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_peer_tx_nsec */
#ifndef __EMAC_REGS__TSU_PEER_TX_NSEC_MACRO__
#define __EMAC_REGS__TSU_PEER_TX_NSEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__SHIFT                             0
#define EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__WIDTH                            30
#define EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__MASK                    0x3fffffffU
#define EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__RESET                             0
#define EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)

/* macros for field reserved_31_30 */
#define EMAC_REGS__TSU_PEER_TX_NSEC__RESERVED_31_30__SHIFT                   30
#define EMAC_REGS__TSU_PEER_TX_NSEC__RESERVED_31_30__WIDTH                    2
#define EMAC_REGS__TSU_PEER_TX_NSEC__RESERVED_31_30__MASK           0xc0000000U
#define EMAC_REGS__TSU_PEER_TX_NSEC__RESERVED_31_30__RESET                    0
#define EMAC_REGS__TSU_PEER_TX_NSEC__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TSU_PEER_TX_NSEC__TYPE                              uint32_t
#define EMAC_REGS__TSU_PEER_TX_NSEC__READ                           0xffffffffU

#endif /* __EMAC_REGS__TSU_PEER_TX_NSEC_MACRO__ */


/* macros for tsu_peer_tx_nsec */
#define INST_TSU_PEER_TX_NSEC__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_peer_rx_sec */
#ifndef __EMAC_REGS__TSU_PEER_RX_SEC_MACRO__
#define __EMAC_REGS__TSU_PEER_RX_SEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PEER_RX_SEC__TIMER__SHIFT                              0
#define EMAC_REGS__TSU_PEER_RX_SEC__TIMER__WIDTH                             32
#define EMAC_REGS__TSU_PEER_RX_SEC__TIMER__MASK                     0xffffffffU
#define EMAC_REGS__TSU_PEER_RX_SEC__TIMER__RESET                              0
#define EMAC_REGS__TSU_PEER_RX_SEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__TSU_PEER_RX_SEC__TYPE                               uint32_t
#define EMAC_REGS__TSU_PEER_RX_SEC__READ                            0xffffffffU

#endif /* __EMAC_REGS__TSU_PEER_RX_SEC_MACRO__ */


/* macros for tsu_peer_rx_sec */
#define INST_TSU_PEER_RX_SEC__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::tsu_peer_rx_nsec */
#ifndef __EMAC_REGS__TSU_PEER_RX_NSEC_MACRO__
#define __EMAC_REGS__TSU_PEER_RX_NSEC_MACRO__

/* macros for field timer */
#define EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__SHIFT                             0
#define EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__WIDTH                            30
#define EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__MASK                    0x3fffffffU
#define EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__RESET                             0
#define EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)

/* macros for field reserved_31_30 */
#define EMAC_REGS__TSU_PEER_RX_NSEC__RESERVED_31_30__SHIFT                   30
#define EMAC_REGS__TSU_PEER_RX_NSEC__RESERVED_31_30__WIDTH                    2
#define EMAC_REGS__TSU_PEER_RX_NSEC__RESERVED_31_30__MASK           0xc0000000U
#define EMAC_REGS__TSU_PEER_RX_NSEC__RESERVED_31_30__RESET                    0
#define EMAC_REGS__TSU_PEER_RX_NSEC__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TSU_PEER_RX_NSEC__TYPE                              uint32_t
#define EMAC_REGS__TSU_PEER_RX_NSEC__READ                           0xffffffffU

#endif /* __EMAC_REGS__TSU_PEER_RX_NSEC_MACRO__ */


/* macros for tsu_peer_rx_nsec */
#define INST_TSU_PEER_RX_NSEC__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_control */
#ifndef __EMAC_REGS__PCS_CONTROL_MACRO__
#define __EMAC_REGS__PCS_CONTROL_MACRO__

/* macros for field reserved_5_0 */
#define EMAC_REGS__PCS_CONTROL__RESERVED_5_0__SHIFT                           0
#define EMAC_REGS__PCS_CONTROL__RESERVED_5_0__WIDTH                           6
#define EMAC_REGS__PCS_CONTROL__RESERVED_5_0__MASK                  0x0000003fU
#define EMAC_REGS__PCS_CONTROL__RESERVED_5_0__RESET                           0
#define EMAC_REGS__PCS_CONTROL__RESERVED_5_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000003fU)

/* macros for field speed_select_bit_0 */
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__SHIFT                     6
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__WIDTH                     1
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__MASK            0x00000040U
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__RESET                     1
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field collision_test */
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__SHIFT                         7
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__WIDTH                         1
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__MASK                0x00000080U
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__RESET                         0
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__PCS_CONTROL__COLLISION_TEST__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field mac_duplex_state */
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__SHIFT                       8
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__WIDTH                       1
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__MASK              0x00000100U
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__RESET                       0
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__PCS_CONTROL__MAC_DUPLEX_STATE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field restart_auto_neg */
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__SHIFT                       9
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__WIDTH                       1
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__MASK              0x00000200U
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__RESET                       0
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field reserved_11_10 */
#define EMAC_REGS__PCS_CONTROL__RESERVED_11_10__SHIFT                        10
#define EMAC_REGS__PCS_CONTROL__RESERVED_11_10__WIDTH                         2
#define EMAC_REGS__PCS_CONTROL__RESERVED_11_10__MASK                0x00000c00U
#define EMAC_REGS__PCS_CONTROL__RESERVED_11_10__RESET                         0
#define EMAC_REGS__PCS_CONTROL__RESERVED_11_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000c00U) >> 10)

/* macros for field enable_auto_neg */
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__SHIFT                       12
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__WIDTH                        1
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__MASK               0x00001000U
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__RESET                        1
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field speed_select_bit_1 */
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__SHIFT                    13
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__WIDTH                     1
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__MASK            0x00002000U
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__RESET                     0
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__PCS_CONTROL__SPEED_SELECT_BIT_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field loopback_mode */
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__SHIFT                         14
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__WIDTH                          1
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__MASK                 0x00004000U
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__RESET                          0
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x00004000U)
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | (((uint32_t)(src) <<\
                    14) & 0x00004000U)
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x00004000U)))
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field pcs_software_reset */
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__SHIFT                    15
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__WIDTH                     1
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__MASK            0x00008000U
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__RESET                     1
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_CONTROL__RESERVED_31_16__SHIFT                        16
#define EMAC_REGS__PCS_CONTROL__RESERVED_31_16__WIDTH                        16
#define EMAC_REGS__PCS_CONTROL__RESERVED_31_16__MASK                0xffff0000U
#define EMAC_REGS__PCS_CONTROL__RESERVED_31_16__RESET                         0
#define EMAC_REGS__PCS_CONTROL__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_CONTROL__TYPE                                   uint32_t
#define EMAC_REGS__PCS_CONTROL__READ                                0xffffffffU
#define EMAC_REGS__PCS_CONTROL__WRITE                               0xffffffffU

#endif /* __EMAC_REGS__PCS_CONTROL_MACRO__ */


/* macros for pcs_control */
#define INST_PCS_CONTROL__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_status */
#ifndef __EMAC_REGS__PCS_STATUS_MACRO__
#define __EMAC_REGS__PCS_STATUS_MACRO__

/* macros for field extended_capabilities */
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__SHIFT                   0
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__WIDTH                   1
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__MASK          0x00000001U
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__RESET                   1
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__PCS_STATUS__EXTENDED_CAPABILITIES__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_1 */
#define EMAC_REGS__PCS_STATUS__RESERVED_1__SHIFT                              1
#define EMAC_REGS__PCS_STATUS__RESERVED_1__WIDTH                              1
#define EMAC_REGS__PCS_STATUS__RESERVED_1__MASK                     0x00000002U
#define EMAC_REGS__PCS_STATUS__RESERVED_1__RESET                              0
#define EMAC_REGS__PCS_STATUS__RESERVED_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__PCS_STATUS__RESERVED_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__PCS_STATUS__RESERVED_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field link_status */
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__SHIFT                             2
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__WIDTH                             1
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__MASK                    0x00000004U
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__RESET                             0
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__PCS_STATUS__LINK_STATUS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field auto_neg_ability */
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__SHIFT                        3
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__WIDTH                        1
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__MASK               0x00000008U
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__RESET                        1
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_ABILITY__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field remote_fault */
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__SHIFT                            4
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__WIDTH                            1
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__MASK                   0x00000010U
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__RESET                            0
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__PCS_STATUS__REMOTE_FAULT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field auto_neg_complete */
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__SHIFT                       5
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__WIDTH                       1
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__MASK              0x00000020U
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__RESET                       0
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field reserved_7_6 */
#define EMAC_REGS__PCS_STATUS__RESERVED_7_6__SHIFT                            6
#define EMAC_REGS__PCS_STATUS__RESERVED_7_6__WIDTH                            2
#define EMAC_REGS__PCS_STATUS__RESERVED_7_6__MASK                   0x000000c0U
#define EMAC_REGS__PCS_STATUS__RESERVED_7_6__RESET                            0
#define EMAC_REGS__PCS_STATUS__RESERVED_7_6__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000c0U) >> 6)

/* macros for field extended_status */
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__SHIFT                         8
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__WIDTH                         1
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__MASK                0x00000100U
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__RESET                         1
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__PCS_STATUS__EXTENDED_STATUS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field base_100_t2_half_duplex */
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__SHIFT                 9
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__WIDTH                 1
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__MASK        0x00000200U
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__RESET                 0
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_HALF_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field base_100_t2_full_duplex */
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__SHIFT                10
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__WIDTH                 1
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__MASK        0x00000400U
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__RESET                 0
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__PCS_STATUS__BASE_100_T2_FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field mbps_10_half_duplex */
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__SHIFT                    11
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__WIDTH                     1
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__MASK            0x00000800U
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__RESET                     0
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__PCS_STATUS__MBPS_10_HALF_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field mbps_10_full_duplex */
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__SHIFT                    12
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__WIDTH                     1
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__MASK            0x00001000U
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__RESET                     0
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__PCS_STATUS__MBPS_10_FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field base_100_x_half_duplex */
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__SHIFT                 13
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__WIDTH                  1
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__MASK         0x00002000U
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__RESET                  0
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__PCS_STATUS__BASE_100_X_HALF_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field base_100_x_full_duplex */
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__SHIFT                 14
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__WIDTH                  1
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__MASK         0x00004000U
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__RESET                  0
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_STATUS__BASE_100_X_FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field base_100_t4 */
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__SHIFT                            15
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__WIDTH                             1
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__MASK                    0x00008000U
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__RESET                             0
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_STATUS__BASE_100_T4__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_STATUS__RESERVED_31_16__SHIFT                         16
#define EMAC_REGS__PCS_STATUS__RESERVED_31_16__WIDTH                         16
#define EMAC_REGS__PCS_STATUS__RESERVED_31_16__MASK                 0xffff0000U
#define EMAC_REGS__PCS_STATUS__RESERVED_31_16__RESET                          0
#define EMAC_REGS__PCS_STATUS__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_STATUS__TYPE                                    uint32_t
#define EMAC_REGS__PCS_STATUS__READ                                 0xffffffffU

#endif /* __EMAC_REGS__PCS_STATUS_MACRO__ */


/* macros for pcs_status */
#define INST_PCS_STATUS__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_an_adv */
#ifndef __EMAC_REGS__PCS_AN_ADV_MACRO__
#define __EMAC_REGS__PCS_AN_ADV_MACRO__

/* macros for field reserved_4_0 */
#define EMAC_REGS__PCS_AN_ADV__RESERVED_4_0__SHIFT                            0
#define EMAC_REGS__PCS_AN_ADV__RESERVED_4_0__WIDTH                            5
#define EMAC_REGS__PCS_AN_ADV__RESERVED_4_0__MASK                   0x0000001fU
#define EMAC_REGS__PCS_AN_ADV__RESERVED_4_0__RESET                            0
#define EMAC_REGS__PCS_AN_ADV__RESERVED_4_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000001fU)

/* macros for field full_duplex */
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__SHIFT                             5
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__WIDTH                             1
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__MASK                    0x00000020U
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__RESET                             1
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field half_duplex */
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__SHIFT                             6
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__WIDTH                             1
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__MASK                    0x00000040U
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__RESET                             0
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field pause */
#define EMAC_REGS__PCS_AN_ADV__PAUSE__SHIFT                                   7
#define EMAC_REGS__PCS_AN_ADV__PAUSE__WIDTH                                   2
#define EMAC_REGS__PCS_AN_ADV__PAUSE__MASK                          0x00000180U
#define EMAC_REGS__PCS_AN_ADV__PAUSE__RESET                                   0
#define EMAC_REGS__PCS_AN_ADV__PAUSE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000180U) >> 7)
#define EMAC_REGS__PCS_AN_ADV__PAUSE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000180U)
#define EMAC_REGS__PCS_AN_ADV__PAUSE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000180U) | (((uint32_t)(src) <<\
                    7) & 0x00000180U)
#define EMAC_REGS__PCS_AN_ADV__PAUSE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000180U)))

/* macros for field reserved_11_9 */
#define EMAC_REGS__PCS_AN_ADV__RESERVED_11_9__SHIFT                           9
#define EMAC_REGS__PCS_AN_ADV__RESERVED_11_9__WIDTH                           3
#define EMAC_REGS__PCS_AN_ADV__RESERVED_11_9__MASK                  0x00000e00U
#define EMAC_REGS__PCS_AN_ADV__RESERVED_11_9__RESET                           0
#define EMAC_REGS__PCS_AN_ADV__RESERVED_11_9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000e00U) >> 9)

/* macros for field remote_fault */
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__SHIFT                           12
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__WIDTH                            2
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__MASK                   0x00003000U
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__RESET                            0
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00003000U) >> 12)
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00003000U)
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00003000U) | (((uint32_t)(src) <<\
                    12) & 0x00003000U)
#define EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00003000U)))

/* macros for field reserved_14 */
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__SHIFT                            14
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__WIDTH                             1
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__MASK                    0x00004000U
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__RESET                             0
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_AN_ADV__RESERVED_14__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field next_page */
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__SHIFT                              15
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__WIDTH                               1
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__MASK                      0x00008000U
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__RESET                               0
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_AN_ADV__RESERVED_31_16__SHIFT                         16
#define EMAC_REGS__PCS_AN_ADV__RESERVED_31_16__WIDTH                         16
#define EMAC_REGS__PCS_AN_ADV__RESERVED_31_16__MASK                 0xffff0000U
#define EMAC_REGS__PCS_AN_ADV__RESERVED_31_16__RESET                          0
#define EMAC_REGS__PCS_AN_ADV__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_AN_ADV__TYPE                                    uint32_t
#define EMAC_REGS__PCS_AN_ADV__READ                                 0xffffffffU
#define EMAC_REGS__PCS_AN_ADV__WRITE                                0xffffffffU

#endif /* __EMAC_REGS__PCS_AN_ADV_MACRO__ */


/* macros for pcs_an_adv */
#define INST_PCS_AN_ADV__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_an_lp_base */
#ifndef __EMAC_REGS__PCS_AN_LP_BASE_MACRO__
#define __EMAC_REGS__PCS_AN_LP_BASE_MACRO__

/* macros for field reserved_4_0 */
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_4_0__SHIFT                        0
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_4_0__WIDTH                        5
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_4_0__MASK               0x0000001fU
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_4_0__RESET                        0
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_4_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000001fU)

/* macros for field link_partner_full_duplex */
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__SHIFT            5
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__WIDTH            1
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__MASK   0x00000020U
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__RESET            0
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field link_partner_half_duplex */
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__SHIFT            6
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__WIDTH            1
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__MASK   0x00000040U
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__RESET            0
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field pause */
#define EMAC_REGS__PCS_AN_LP_BASE__PAUSE__SHIFT                               7
#define EMAC_REGS__PCS_AN_LP_BASE__PAUSE__WIDTH                               2
#define EMAC_REGS__PCS_AN_LP_BASE__PAUSE__MASK                      0x00000180U
#define EMAC_REGS__PCS_AN_LP_BASE__PAUSE__RESET                               0
#define EMAC_REGS__PCS_AN_LP_BASE__PAUSE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000180U) >> 7)

/* macros for field speed_reserved */
#define EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__SHIFT                      9
#define EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__WIDTH                      3
#define EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__MASK             0x00000e00U
#define EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__RESET                      0
#define EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000e00U) >> 9)

/* macros for field link_partner_remote_fault_duplex_mode */
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__SHIFT \
                    12
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__WIDTH \
                    2
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__MASK \
                    0x00003000U
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__RESET \
                    0
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00003000U) >> 12)

/* macros for field link_partner_acknowledge */
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__SHIFT           14
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__WIDTH            1
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__MASK   0x00004000U
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__RESET            0
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field link_partner_next_page_status */
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__SHIFT      15
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__WIDTH       1
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__MASK \
                    0x00008000U
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__RESET       0
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_31_16__SHIFT                     16
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_31_16__WIDTH                     16
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_31_16__MASK             0xffff0000U
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_31_16__RESET                      0
#define EMAC_REGS__PCS_AN_LP_BASE__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_AN_LP_BASE__TYPE                                uint32_t
#define EMAC_REGS__PCS_AN_LP_BASE__READ                             0xffffffffU

#endif /* __EMAC_REGS__PCS_AN_LP_BASE_MACRO__ */


/* macros for pcs_an_lp_base */
#define INST_PCS_AN_LP_BASE__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_an_exp */
#ifndef __EMAC_REGS__PCS_AN_EXP_MACRO__
#define __EMAC_REGS__PCS_AN_EXP_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__SHIFT                              0
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__WIDTH                              1
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__MASK                     0x00000001U
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__RESET                              0
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__PCS_AN_EXP__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field page_received */
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__SHIFT                           1
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__WIDTH                           1
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__MASK                  0x00000002U
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__RESET                           0
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field next_page_capability */
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__SHIFT                    2
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__WIDTH                    1
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__MASK           0x00000004U
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__RESET                    1
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__PCS_AN_EXP__NEXT_PAGE_CAPABILITY__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field reserved_31_3 */
#define EMAC_REGS__PCS_AN_EXP__RESERVED_31_3__SHIFT                           3
#define EMAC_REGS__PCS_AN_EXP__RESERVED_31_3__WIDTH                          29
#define EMAC_REGS__PCS_AN_EXP__RESERVED_31_3__MASK                  0xfffffff8U
#define EMAC_REGS__PCS_AN_EXP__RESERVED_31_3__RESET                           0
#define EMAC_REGS__PCS_AN_EXP__RESERVED_31_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffff8U) >> 3)
#define EMAC_REGS__PCS_AN_EXP__TYPE                                    uint32_t
#define EMAC_REGS__PCS_AN_EXP__READ                                 0xffffffffU

#endif /* __EMAC_REGS__PCS_AN_EXP_MACRO__ */


/* macros for pcs_an_exp */
#define INST_PCS_AN_EXP__NUM                                                  1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_an_np_tx */
#ifndef __EMAC_REGS__PCS_AN_NP_TX_MACRO__
#define __EMAC_REGS__PCS_AN_NP_TX_MACRO__

/* macros for field message */
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__SHIFT                               0
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__WIDTH                              11
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__MASK                      0x000007ffU
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__RESET                               0
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000007ffU)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000007ffU)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000007ffU) | ((uint32_t)(src) &\
                    0x000007ffU)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000007ffU)))

/* macros for field reserved_11 */
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__SHIFT                          11
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__WIDTH                           1
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__MASK                  0x00000800U
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__RESET                           0
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_11__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field acknowledge_2 */
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__SHIFT                        12
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__WIDTH                         1
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__MASK                0x00001000U
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__RESET                         0
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field message_page_indicator */
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__SHIFT               13
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__WIDTH                1
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__MASK       0x00002000U
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__RESET                0
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x00002000U)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | (((uint32_t)(src) <<\
                    13) & 0x00002000U)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x00002000U)))
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field reserved_14 */
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__SHIFT                          14
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__WIDTH                           1
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__MASK                  0x00004000U
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__RESET                           0
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_14__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field next_page_to_transmit */
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__SHIFT                15
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__WIDTH                 1
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__MASK        0x00008000U
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__RESET                 0
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 15) & 0x00008000U)
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | (((uint32_t)(src) <<\
                    15) & 0x00008000U)
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 15) & ~0x00008000U)))
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_31_16__SHIFT                       16
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_31_16__WIDTH                       16
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_31_16__MASK               0xffff0000U
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_31_16__RESET                        0
#define EMAC_REGS__PCS_AN_NP_TX__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_AN_NP_TX__TYPE                                  uint32_t
#define EMAC_REGS__PCS_AN_NP_TX__READ                               0xffffffffU
#define EMAC_REGS__PCS_AN_NP_TX__WRITE                              0xffffffffU

#endif /* __EMAC_REGS__PCS_AN_NP_TX_MACRO__ */


/* macros for pcs_an_np_tx */
#define INST_PCS_AN_NP_TX__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_an_lp_np */
#ifndef __EMAC_REGS__PCS_AN_LP_NP_MACRO__
#define __EMAC_REGS__PCS_AN_LP_NP_MACRO__

/* macros for field message */
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE__SHIFT                               0
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE__WIDTH                              11
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE__MASK                      0x000007ffU
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE__RESET                               0
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000007ffU)

/* macros for field toggle */
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__SHIFT                               11
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__WIDTH                                1
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__MASK                       0x00000800U
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__RESET                                0
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__PCS_AN_LP_NP__TOGGLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field acknowledge_2 */
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__SHIFT                        12
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__WIDTH                         1
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__MASK                0x00001000U
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__RESET                         0
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field message_page_indicator */
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__SHIFT               13
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__WIDTH                1
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__MASK       0x00002000U
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__RESET                0
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field acknowledge */
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__SHIFT                          14
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__WIDTH                           1
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__MASK                  0x00004000U
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__RESET                           0
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field next_page_to_receive */
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__SHIFT                 15
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__WIDTH                  1
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__MASK         0x00008000U
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__RESET                  0
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_AN_LP_NP__RESERVED_31_16__SHIFT                       16
#define EMAC_REGS__PCS_AN_LP_NP__RESERVED_31_16__WIDTH                       16
#define EMAC_REGS__PCS_AN_LP_NP__RESERVED_31_16__MASK               0xffff0000U
#define EMAC_REGS__PCS_AN_LP_NP__RESERVED_31_16__RESET                        0
#define EMAC_REGS__PCS_AN_LP_NP__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_AN_LP_NP__TYPE                                  uint32_t
#define EMAC_REGS__PCS_AN_LP_NP__READ                               0xffffffffU

#endif /* __EMAC_REGS__PCS_AN_LP_NP_MACRO__ */


/* macros for pcs_an_lp_np */
#define INST_PCS_AN_LP_NP__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::pcs_an_ext_status */
#ifndef __EMAC_REGS__PCS_AN_EXT_STATUS_MACRO__
#define __EMAC_REGS__PCS_AN_EXT_STATUS_MACRO__

/* macros for field reserved_11_0 */
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_11_0__SHIFT                    0
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_11_0__WIDTH                   12
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_11_0__MASK           0x00000fffU
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_11_0__RESET                    0
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_11_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000fffU)

/* macros for field half_duplex_1000base_t */
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__SHIFT          12
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__WIDTH           1
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__MASK  0x00001000U
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__RESET           0
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_T__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field full_duplex_1000base_t */
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__SHIFT          13
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__WIDTH           1
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__MASK  0x00002000U
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__RESET           0
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_T__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field half_duplex_1000base_x */
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__SHIFT          14
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__WIDTH           1
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__MASK  0x00004000U
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__RESET           0
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__PCS_AN_EXT_STATUS__HALF_DUPLEX_1000BASE_X__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field full_duplex_1000base_x */
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__SHIFT          15
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__WIDTH           1
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__MASK  0x00008000U
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__RESET           1
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__PCS_AN_EXT_STATUS__FULL_DUPLEX_1000BASE_X__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field reserved_31_16 */
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_31_16__SHIFT                  16
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_31_16__WIDTH                  16
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_31_16__MASK          0xffff0000U
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_31_16__RESET                   0
#define EMAC_REGS__PCS_AN_EXT_STATUS__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__PCS_AN_EXT_STATUS__TYPE                             uint32_t
#define EMAC_REGS__PCS_AN_EXT_STATUS__READ                          0xffffffffU

#endif /* __EMAC_REGS__PCS_AN_EXT_STATUS_MACRO__ */


/* macros for pcs_an_ext_status */
#define INST_PCS_AN_EXT_STATUS__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_pause_quantum1 */
#ifndef __EMAC_REGS__TX_PAUSE_QUANTUM1_MACRO__
#define __EMAC_REGS__TX_PAUSE_QUANTUM1_MACRO__

/* macros for field quantum_p2 */
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__SHIFT                       0
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__WIDTH                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__MASK              0x0000ffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__RESET                  0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field quantum_p3 */
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__SHIFT                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__WIDTH                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__MASK              0xffff0000U
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__RESET                  0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffff0000U) | (((uint32_t)(src) <<\
                    16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0xffff0000U)))
#define EMAC_REGS__TX_PAUSE_QUANTUM1__TYPE                             uint32_t
#define EMAC_REGS__TX_PAUSE_QUANTUM1__READ                          0xffffffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM1__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__TX_PAUSE_QUANTUM1_MACRO__ */


/* macros for tx_pause_quantum1 */
#define INST_TX_PAUSE_QUANTUM1__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_pause_quantum2 */
#ifndef __EMAC_REGS__TX_PAUSE_QUANTUM2_MACRO__
#define __EMAC_REGS__TX_PAUSE_QUANTUM2_MACRO__

/* macros for field quantum_p4 */
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__SHIFT                       0
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__WIDTH                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__MASK              0x0000ffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__RESET                  0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field quantum_p5 */
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__SHIFT                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__WIDTH                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__MASK              0xffff0000U
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__RESET                  0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffff0000U) | (((uint32_t)(src) <<\
                    16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0xffff0000U)))
#define EMAC_REGS__TX_PAUSE_QUANTUM2__TYPE                             uint32_t
#define EMAC_REGS__TX_PAUSE_QUANTUM2__READ                          0xffffffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM2__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__TX_PAUSE_QUANTUM2_MACRO__ */


/* macros for tx_pause_quantum2 */
#define INST_TX_PAUSE_QUANTUM2__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_pause_quantum3 */
#ifndef __EMAC_REGS__TX_PAUSE_QUANTUM3_MACRO__
#define __EMAC_REGS__TX_PAUSE_QUANTUM3_MACRO__

/* macros for field quantum_p6 */
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__SHIFT                       0
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__WIDTH                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__MASK              0x0000ffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__RESET                  0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field quantum_p7 */
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__SHIFT                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__WIDTH                      16
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__MASK              0xffff0000U
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__RESET                  0xFFFF
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffff0000U) | (((uint32_t)(src) <<\
                    16) & 0xffff0000U)
#define EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0xffff0000U)))
#define EMAC_REGS__TX_PAUSE_QUANTUM3__TYPE                             uint32_t
#define EMAC_REGS__TX_PAUSE_QUANTUM3__READ                          0xffffffffU
#define EMAC_REGS__TX_PAUSE_QUANTUM3__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__TX_PAUSE_QUANTUM3_MACRO__ */


/* macros for tx_pause_quantum3 */
#define INST_TX_PAUSE_QUANTUM3__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_lpi */
#ifndef __EMAC_REGS__RX_LPI_MACRO__
#define __EMAC_REGS__RX_LPI_MACRO__

/* macros for field count */
#define EMAC_REGS__RX_LPI__COUNT__SHIFT                                       0
#define EMAC_REGS__RX_LPI__COUNT__WIDTH                                      16
#define EMAC_REGS__RX_LPI__COUNT__MASK                              0x0000ffffU
#define EMAC_REGS__RX_LPI__COUNT__RESET                                       0
#define EMAC_REGS__RX_LPI__COUNT__READ(src)     ((uint32_t)(src) & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__RX_LPI__RESERVED_31_16__SHIFT                             16
#define EMAC_REGS__RX_LPI__RESERVED_31_16__WIDTH                             16
#define EMAC_REGS__RX_LPI__RESERVED_31_16__MASK                     0xffff0000U
#define EMAC_REGS__RX_LPI__RESERVED_31_16__RESET                              0
#define EMAC_REGS__RX_LPI__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__RX_LPI__TYPE                                        uint32_t
#define EMAC_REGS__RX_LPI__READ                                     0xffffffffU
#define EMAC_REGS__RX_LPI__RCLR                                     0x0000ffffU

#endif /* __EMAC_REGS__RX_LPI_MACRO__ */


/* macros for rx_lpi */
#define INST_RX_LPI__NUM                                                      1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_lpi_time */
#ifndef __EMAC_REGS__RX_LPI_TIME_MACRO__
#define __EMAC_REGS__RX_LPI_TIME_MACRO__

/* macros for field lpi_time */
#define EMAC_REGS__RX_LPI_TIME__LPI_TIME__SHIFT                               0
#define EMAC_REGS__RX_LPI_TIME__LPI_TIME__WIDTH                              24
#define EMAC_REGS__RX_LPI_TIME__LPI_TIME__MASK                      0x00ffffffU
#define EMAC_REGS__RX_LPI_TIME__LPI_TIME__RESET                               0
#define EMAC_REGS__RX_LPI_TIME__LPI_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00ffffffU)

/* macros for field reserved_31_24 */
#define EMAC_REGS__RX_LPI_TIME__RESERVED_31_24__SHIFT                        24
#define EMAC_REGS__RX_LPI_TIME__RESERVED_31_24__WIDTH                         8
#define EMAC_REGS__RX_LPI_TIME__RESERVED_31_24__MASK                0xff000000U
#define EMAC_REGS__RX_LPI_TIME__RESERVED_31_24__RESET                         0
#define EMAC_REGS__RX_LPI_TIME__RESERVED_31_24__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__RX_LPI_TIME__TYPE                                   uint32_t
#define EMAC_REGS__RX_LPI_TIME__READ                                0xffffffffU
#define EMAC_REGS__RX_LPI_TIME__RCLR                                0x00ffffffU

#endif /* __EMAC_REGS__RX_LPI_TIME_MACRO__ */


/* macros for rx_lpi_time */
#define INST_RX_LPI_TIME__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_lpi */
#ifndef __EMAC_REGS__TX_LPI_MACRO__
#define __EMAC_REGS__TX_LPI_MACRO__

/* macros for field count */
#define EMAC_REGS__TX_LPI__COUNT__SHIFT                                       0
#define EMAC_REGS__TX_LPI__COUNT__WIDTH                                      16
#define EMAC_REGS__TX_LPI__COUNT__MASK                              0x0000ffffU
#define EMAC_REGS__TX_LPI__COUNT__RESET                                       0
#define EMAC_REGS__TX_LPI__COUNT__READ(src)     ((uint32_t)(src) & 0x0000ffffU)

/* macros for field reserved_31_16 */
#define EMAC_REGS__TX_LPI__RESERVED_31_16__SHIFT                             16
#define EMAC_REGS__TX_LPI__RESERVED_31_16__WIDTH                             16
#define EMAC_REGS__TX_LPI__RESERVED_31_16__MASK                     0xffff0000U
#define EMAC_REGS__TX_LPI__RESERVED_31_16__RESET                              0
#define EMAC_REGS__TX_LPI__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TX_LPI__TYPE                                        uint32_t
#define EMAC_REGS__TX_LPI__READ                                     0xffffffffU
#define EMAC_REGS__TX_LPI__RCLR                                     0x0000ffffU

#endif /* __EMAC_REGS__TX_LPI_MACRO__ */


/* macros for tx_lpi */
#define INST_TX_LPI__NUM                                                      1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_lpi_time */
#ifndef __EMAC_REGS__TX_LPI_TIME_MACRO__
#define __EMAC_REGS__TX_LPI_TIME_MACRO__

/* macros for field lpi_time */
#define EMAC_REGS__TX_LPI_TIME__LPI_TIME__SHIFT                               0
#define EMAC_REGS__TX_LPI_TIME__LPI_TIME__WIDTH                              24
#define EMAC_REGS__TX_LPI_TIME__LPI_TIME__MASK                      0x00ffffffU
#define EMAC_REGS__TX_LPI_TIME__LPI_TIME__RESET                               0
#define EMAC_REGS__TX_LPI_TIME__LPI_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00ffffffU)

/* macros for field reserved_31_24 */
#define EMAC_REGS__TX_LPI_TIME__RESERVED_31_24__SHIFT                        24
#define EMAC_REGS__TX_LPI_TIME__RESERVED_31_24__WIDTH                         8
#define EMAC_REGS__TX_LPI_TIME__RESERVED_31_24__MASK                0xff000000U
#define EMAC_REGS__TX_LPI_TIME__RESERVED_31_24__RESET                         0
#define EMAC_REGS__TX_LPI_TIME__RESERVED_31_24__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__TX_LPI_TIME__TYPE                                   uint32_t
#define EMAC_REGS__TX_LPI_TIME__READ                                0xffffffffU
#define EMAC_REGS__TX_LPI_TIME__RCLR                                0x00ffffffU

#endif /* __EMAC_REGS__TX_LPI_TIME_MACRO__ */


/* macros for tx_lpi_time */
#define INST_TX_LPI_TIME__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug1 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG1_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG1_MACRO__

/* macros for field no_pcs */
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__SHIFT                            0
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__WIDTH                            1
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__MASK                   0x00000001U
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__RESET                            0
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field exclude_qbv */
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__SHIFT                       1
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__WIDTH                       1
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__MASK              0x00000002U
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__RESET                       0
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_QBV__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field reserved_3_2 */
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_3_2__SHIFT                      2
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_3_2__WIDTH                      2
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_3_2__MASK             0x0000000cU
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_3_2__RESET                      0
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_3_2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000000cU) >> 2)

/* macros for field int_loopback */
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__SHIFT                      4
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__WIDTH                      1
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__MASK             0x00000010U
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__RESET                      1
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field reserved_5 */
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__SHIFT                        5
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__WIDTH                        1
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__MASK               0x00000020U
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__RESET                        0
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_5__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field ext_fifo_interface */
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__SHIFT                6
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__WIDTH                1
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__MASK       0x00000040U
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__RESET                0
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field reserved_7 */
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__SHIFT                        7
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__WIDTH                        1
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__MASK               0x00000080U
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__RESET                        0
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_7__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_8 */
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__SHIFT                        8
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__WIDTH                        1
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__MASK               0x00000100U
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__RESET                        1
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_8__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field user_io */
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__SHIFT                           9
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__WIDTH                           1
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__MASK                  0x00000200U
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__RESET                           1
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field user_out_width */
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__SHIFT                   10
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__WIDTH                    5
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__MASK           0x00007c00U
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__RESET                   16
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00007c00U) >> 10)

/* macros for field user_in_width */
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__SHIFT                    15
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__WIDTH                     5
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__MASK            0x000f8000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__RESET                    16
#define EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000f8000U) >> 15)

/* macros for field reserved_20 */
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__SHIFT                      20
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__WIDTH                       1
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__MASK              0x00100000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__RESET                       1
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00100000U) >> 20)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__DESIGNCFG_DEBUG1__RESERVED_20__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field no_stats */
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__SHIFT                         21
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__WIDTH                          1
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__MASK                 0x00200000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__RESET                          0
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00200000U) >> 21)
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field no_snapshot */
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__SHIFT                      22
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__WIDTH                       1
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__MASK              0x00400000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__RESET                       0
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00400000U) >> 22)
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field irq_read_clear */
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__SHIFT                   23
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__WIDTH                    1
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__MASK           0x00800000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__RESET                    1
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field exclude_cbs */
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__SHIFT                      24
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__WIDTH                       1
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__MASK              0x01000000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__RESET                       0
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field dma_bus_width */
#define EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__SHIFT                    25
#define EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__WIDTH                     3
#define EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__MASK            0x0e000000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__RESET                     2
#define EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0e000000U) >> 25)

/* macros for field axi_cache_value */
#define EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__SHIFT                  28
#define EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__WIDTH                   4
#define EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__MASK          0xf0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__RESET                   0
#define EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__DESIGNCFG_DEBUG1__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG1__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG1_MACRO__ */


/* macros for designcfg_debug1 */
#define INST_DESIGNCFG_DEBUG1__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug2 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG2_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG2_MACRO__

/* macros for field jumbo_max_length */
#define EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__SHIFT                  0
#define EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__WIDTH                 14
#define EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__MASK         0x00003fffU
#define EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__RESET              10240
#define EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00003fffU)

/* macros for field reserved_15_14 */
#define EMAC_REGS__DESIGNCFG_DEBUG2__RESERVED_15_14__SHIFT                   14
#define EMAC_REGS__DESIGNCFG_DEBUG2__RESERVED_15_14__WIDTH                    2
#define EMAC_REGS__DESIGNCFG_DEBUG2__RESERVED_15_14__MASK           0x0000c000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__RESERVED_15_14__RESET                    0
#define EMAC_REGS__DESIGNCFG_DEBUG2__RESERVED_15_14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000c000U) >> 14)

/* macros for field hprot_value */
#define EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__SHIFT                      16
#define EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__WIDTH                       4
#define EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__MASK              0x000f0000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__RESET                       1
#define EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000f0000U) >> 16)

/* macros for field rx_pkt_buffer */
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__SHIFT                    20
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__WIDTH                     1
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__MASK            0x00100000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__RESET                     1
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00100000U) >> 20)
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field tx_pkt_buffer */
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__SHIFT                    21
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__WIDTH                     1
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__MASK            0x00200000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__RESET                     1
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00200000U) >> 21)
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field rx_pbuf_addr */
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__SHIFT                     22
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__WIDTH                      4
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__MASK             0x03c00000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__RESET                     11
#define EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x03c00000U) >> 22)

/* macros for field tx_pbuf_addr */
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__SHIFT                     26
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__WIDTH                      4
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__MASK             0x3c000000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__RESET                     14
#define EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x3c000000U) >> 26)

/* macros for field axi */
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__SHIFT                              30
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__WIDTH                               1
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__MASK                      0x40000000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__RESET                               1
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__DESIGNCFG_DEBUG2__AXI__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field spram */
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__SHIFT                            31
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__WIDTH                             1
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__MASK                    0x80000000U
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__RESET                             0
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__DESIGNCFG_DEBUG2__SPRAM__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__DESIGNCFG_DEBUG2__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG2__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG2_MACRO__ */


/* macros for designcfg_debug2 */
#define INST_DESIGNCFG_DEBUG2__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug3 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG3_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG3_MACRO__

/* macros for field reserved_23_0 */
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_23_0__SHIFT                     0
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_23_0__WIDTH                    24
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_23_0__MASK            0x00ffffffU
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_23_0__RESET                     0
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_23_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00ffffffU)

/* macros for field num_spec_add_filters */
#define EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__SHIFT             24
#define EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__WIDTH              6
#define EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__MASK     0x3f000000U
#define EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__RESET             36
#define EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x3f000000U) >> 24)

/* macros for field reserved_31_30 */
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_31_30__SHIFT                   30
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_31_30__WIDTH                    2
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_31_30__MASK           0xc0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_31_30__RESET                    0
#define EMAC_REGS__DESIGNCFG_DEBUG3__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__DESIGNCFG_DEBUG3__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG3__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG3_MACRO__ */


/* macros for designcfg_debug3 */
#define INST_DESIGNCFG_DEBUG3__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug4 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG4_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG4_MACRO__

/* macros for field reserved_31_0 */
#define EMAC_REGS__DESIGNCFG_DEBUG4__RESERVED_31_0__SHIFT                     0
#define EMAC_REGS__DESIGNCFG_DEBUG4__RESERVED_31_0__WIDTH                    32
#define EMAC_REGS__DESIGNCFG_DEBUG4__RESERVED_31_0__MASK            0xffffffffU
#define EMAC_REGS__DESIGNCFG_DEBUG4__RESERVED_31_0__RESET                     0
#define EMAC_REGS__DESIGNCFG_DEBUG4__RESERVED_31_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__DESIGNCFG_DEBUG4__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG4__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG4_MACRO__ */


/* macros for designcfg_debug4 */
#define INST_DESIGNCFG_DEBUG4__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug5 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG5_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG5_MACRO__

/* macros for field rx_fifo_cnt_width */
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__SHIFT                 0
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__WIDTH                 4
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__MASK        0x0000000fU
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__RESET                 5
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)

/* macros for field tx_fifo_cnt_width */
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__SHIFT                 4
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__WIDTH                 4
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__MASK        0x000000f0U
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__RESET                 4
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000f0U) >> 4)

/* macros for field tsu */
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__SHIFT                               8
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__WIDTH                               1
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__MASK                      0x00000100U
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__RESET                               1
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field phy_ident */
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__SHIFT                         9
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__WIDTH                         1
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__MASK                0x00000200U
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__RESET                         1
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field dma_bus_width_def */
#define EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__SHIFT                10
#define EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__WIDTH                 2
#define EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__MASK        0x00000c00U
#define EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__RESET                 0
#define EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000c00U) >> 10)

/* macros for field mdc_clock_div */
#define EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__SHIFT                    12
#define EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__WIDTH                     3
#define EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__MASK            0x00007000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__RESET                     2
#define EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00007000U) >> 12)

/* macros for field endian_swap_def */
#define EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__SHIFT                  15
#define EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__WIDTH                   2
#define EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__MASK          0x00018000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__RESET                   3
#define EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00018000U) >> 15)

/* macros for field rx_pbuf_size_def */
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__SHIFT                 17
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__WIDTH                  2
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__MASK         0x00060000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__RESET                  3
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00060000U) >> 17)

/* macros for field tx_pbuf_size_def */
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__SHIFT                 19
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__WIDTH                  1
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__MASK         0x00080000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__RESET                  1
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field rx_buffer_length_def */
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__SHIFT             20
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__WIDTH              8
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__MASK     0x0ff00000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__RESET              2
#define EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0ff00000U) >> 20)

/* macros for field tsu_clk */
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__SHIFT                          28
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__WIDTH                           1
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__MASK                  0x10000000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__RESET                           1
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field axi_prot_value */
#define EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__SHIFT                   29
#define EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__WIDTH                    3
#define EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__MASK           0xe0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__RESET                    2
#define EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__READ(src) \
                    (((uint32_t)(src)\
                    & 0xe0000000U) >> 29)
#define EMAC_REGS__DESIGNCFG_DEBUG5__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG5__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG5_MACRO__ */


/* macros for designcfg_debug5 */
#define INST_DESIGNCFG_DEBUG5__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug6 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG6_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG6_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__SHIFT                        0
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__WIDTH                        1
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__MASK               0x00000001U
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__RESET                        0
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field dma_priority_queue1 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__SHIFT               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__MASK      0x00000002U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field dma_priority_queue2 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__SHIFT               2
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__MASK      0x00000004U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field dma_priority_queue3 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__SHIFT               3
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__MASK      0x00000008U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field dma_priority_queue4 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__SHIFT               4
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__MASK      0x00000010U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field dma_priority_queue5 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__SHIFT               5
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__MASK      0x00000020U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field dma_priority_queue6 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__SHIFT               6
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__MASK      0x00000040U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field dma_priority_queue7 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__SHIFT               7
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__MASK      0x00000080U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field dma_priority_queue8 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__SHIFT               8
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__MASK      0x00000100U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field dma_priority_queue9 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__SHIFT               9
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__MASK      0x00000200U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field dma_priority_queue10 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__SHIFT             10
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__WIDTH              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__MASK     0x00000400U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__RESET              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field dma_priority_queue11 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__SHIFT             11
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__WIDTH              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__MASK     0x00000800U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__RESET              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field dma_priority_queue12 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__SHIFT             12
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__WIDTH              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__MASK     0x00001000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__RESET              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field dma_priority_queue13 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__SHIFT             13
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__WIDTH              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__MASK     0x00002000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__RESET              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00002000U) >> 13)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(1) << 13)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00002000U) | ((uint32_t)(0) << 13)

/* macros for field dma_priority_queue14 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__SHIFT             14
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__WIDTH              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__MASK     0x00004000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__RESET              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00004000U) >> 14)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(1) << 14)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00004000U) | ((uint32_t)(0) << 14)

/* macros for field dma_priority_queue15 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__SHIFT             15
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__WIDTH              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__MASK     0x00008000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__RESET              1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field tx_pbuf_queue_segment_size */
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__SHIFT       16
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__WIDTH        4
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__MASK \
                    0x000f0000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__RESET        4
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000f0000U) >> 16)

/* macros for field ext_tsu_timer */
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__SHIFT                    20
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__WIDTH                     1
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__MASK            0x00100000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__RESET                     1
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00100000U) >> 20)
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field tx_add_fifo_if */
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__SHIFT                   21
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__WIDTH                    1
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__MASK           0x00200000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__RESET                    0
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00200000U) >> 21)
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field host_if_soft_select */
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__SHIFT              22
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__WIDTH               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__MASK      0x00400000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__RESET               1
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00400000U) >> 22)
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field dma_addr_width_is_64b */
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__SHIFT            23
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__WIDTH             1
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__MASK    0x00800000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__RESET             0
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field pfc_multi_quantum */
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__SHIFT                24
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__WIDTH                 1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__MASK        0x01000000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__RESET                 1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field pbuf_cutthru */
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__SHIFT                     25
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__WIDTH                      1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__MASK             0x02000000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__RESET                      1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__READ(src) \
                    (((uint32_t)(src)\
                    & 0x02000000U) >> 25)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(1) << 25)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_CUTTHRU__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x02000000U) | ((uint32_t)(0) << 25)

/* macros for field pbuf_rsc */
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__SHIFT                         26
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__WIDTH                          1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__MASK                 0x04000000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__RESET                          1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__READ(src) \
                    (((uint32_t)(src)\
                    & 0x04000000U) >> 26)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(1) << 26)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x04000000U) | ((uint32_t)(0) << 26)

/* macros for field pbuf_lso */
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__SHIFT                         27
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__WIDTH                          1
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__MASK                 0x08000000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__RESET                          0
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field reserved_31_28 */
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_31_28__SHIFT                   28
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_31_28__WIDTH                    4
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_31_28__MASK           0xf0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_31_28__RESET                    0
#define EMAC_REGS__DESIGNCFG_DEBUG6__RESERVED_31_28__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__DESIGNCFG_DEBUG6__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG6__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG6_MACRO__ */


/* macros for designcfg_debug6 */
#define INST_DESIGNCFG_DEBUG6__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug7 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG7_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG7_MACRO__

/* macros for field tx_pbuf_num_segments_q0 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__SHIFT           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__MASK  0x0000000fU
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)

/* macros for field tx_pbuf_num_segments_q1 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__SHIFT           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__MASK  0x000000f0U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000f0U) >> 4)

/* macros for field tx_pbuf_num_segments_q2 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__SHIFT           8
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__MASK  0x00000f00U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000f00U) >> 8)

/* macros for field tx_pbuf_num_segments_q3 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__SHIFT          12
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__MASK  0x0000f000U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000f000U) >> 12)

/* macros for field tx_pbuf_num_segments_q4 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__SHIFT          16
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__MASK  0x000f0000U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000f0000U) >> 16)

/* macros for field tx_pbuf_num_segments_q5 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__SHIFT          20
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__MASK  0x00f00000U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00f00000U) >> 20)

/* macros for field tx_pbuf_num_segments_q6 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__SHIFT          24
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__MASK  0x0f000000U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0f000000U) >> 24)

/* macros for field tx_pbuf_num_segments_q7 */
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__SHIFT          28
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__MASK  0xf0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__DESIGNCFG_DEBUG7__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG7__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG7_MACRO__ */


/* macros for designcfg_debug7 */
#define INST_DESIGNCFG_DEBUG7__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug8 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG8_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG8_MACRO__

/* macros for field num_scr2_compare_regs */
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__SHIFT             0
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__WIDTH             8
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__MASK    0x000000ffU
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__RESET            32
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)

/* macros for field num_scr2_ethtype_regs */
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__SHIFT             8
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__WIDTH             8
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__MASK    0x0000ff00U
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__RESET             8
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)

/* macros for field num_type2_screeners */
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__SHIFT              16
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__WIDTH               8
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__MASK      0x00ff0000U
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__RESET              16
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)

/* macros for field num_type1_screeners */
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__SHIFT              24
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__WIDTH               8
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__MASK      0xff000000U
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__RESET              16
#define EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__DESIGNCFG_DEBUG8__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG8__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG8_MACRO__ */


/* macros for designcfg_debug8 */
#define INST_DESIGNCFG_DEBUG8__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug9 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG9_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG9_MACRO__

/* macros for field tx_pbuf_num_segments_q8 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__SHIFT           0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__MASK  0x0000000fU
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)

/* macros for field tx_pbuf_num_segments_q9 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__SHIFT           4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__WIDTH           4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__MASK  0x000000f0U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__RESET           0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000f0U) >> 4)

/* macros for field tx_pbuf_num_segments_q10 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__SHIFT          8
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__WIDTH          4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__MASK 0x00000f00U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__RESET          0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000f00U) >> 8)

/* macros for field tx_pbuf_num_segments_q11 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__SHIFT         12
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__WIDTH          4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__MASK 0x0000f000U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__RESET          0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000f000U) >> 12)

/* macros for field tx_pbuf_num_segments_q12 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__SHIFT         16
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__WIDTH          4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__MASK 0x000f0000U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__RESET          0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000f0000U) >> 16)

/* macros for field tx_pbuf_num_segments_q13 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__SHIFT         20
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__WIDTH          4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__MASK 0x00f00000U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__RESET          0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00f00000U) >> 20)

/* macros for field tx_pbuf_num_segments_q14 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__SHIFT         24
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__WIDTH          4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__MASK 0x0f000000U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__RESET          0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0f000000U) >> 24)

/* macros for field tx_pbuf_num_segments_q15 */
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__SHIFT         28
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__WIDTH          4
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__MASK 0xf0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__RESET          0
#define EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__DESIGNCFG_DEBUG9__TYPE                              uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG9__READ                           0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG9_MACRO__ */


/* macros for designcfg_debug9 */
#define INST_DESIGNCFG_DEBUG9__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::designcfg_debug10 */
#ifndef __EMAC_REGS__DESIGNCFG_DEBUG10_MACRO__
#define __EMAC_REGS__DESIGNCFG_DEBUG10_MACRO__

/* macros for field axi_rx_descr_wr_buff_bits */
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_WR_BUFF_BITS__SHIFT        0
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_WR_BUFF_BITS__WIDTH        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_WR_BUFF_BITS__MASK \
                    0x0000000fU
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_WR_BUFF_BITS__RESET        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_WR_BUFF_BITS__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)

/* macros for field axi_tx_descr_wr_buff_bits */
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_WR_BUFF_BITS__SHIFT        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_WR_BUFF_BITS__WIDTH        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_WR_BUFF_BITS__MASK \
                    0x000000f0U
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_WR_BUFF_BITS__RESET        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_WR_BUFF_BITS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000f0U) >> 4)

/* macros for field axi_rx_descr_rd_buff_bits */
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_RD_BUFF_BITS__SHIFT        8
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_RD_BUFF_BITS__WIDTH        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_RD_BUFF_BITS__MASK \
                    0x00000f00U
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_RD_BUFF_BITS__RESET        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_RX_DESCR_RD_BUFF_BITS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000f00U) >> 8)

/* macros for field axi_tx_descr_rd_buff_bits */
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_RD_BUFF_BITS__SHIFT       12
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_RD_BUFF_BITS__WIDTH        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_RD_BUFF_BITS__MASK \
                    0x0000f000U
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_RD_BUFF_BITS__RESET        4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_TX_DESCR_RD_BUFF_BITS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000f000U) >> 12)

/* macros for field axi_access_pipeline_bits */
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__SHIFT        16
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__WIDTH         4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__MASK \
                    0x000f0000U
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__RESET         4
#define EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000f0000U) >> 16)

/* macros for field rx_pbuf_data */
#define EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__SHIFT                    20
#define EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__WIDTH                     4
#define EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__MASK            0x00f00000U
#define EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__RESET                     2
#define EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00f00000U) >> 20)

/* macros for field tx_pbuf_data */
#define EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__SHIFT                    24
#define EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__WIDTH                     4
#define EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__MASK            0x0f000000U
#define EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__RESET                     2
#define EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0f000000U) >> 24)

/* macros for field emac_bus_width */
#define EMAC_REGS__DESIGNCFG_DEBUG10__EMAC_BUS_WIDTH__SHIFT                  28
#define EMAC_REGS__DESIGNCFG_DEBUG10__EMAC_BUS_WIDTH__WIDTH                   4
#define EMAC_REGS__DESIGNCFG_DEBUG10__EMAC_BUS_WIDTH__MASK          0xf0000000U
#define EMAC_REGS__DESIGNCFG_DEBUG10__EMAC_BUS_WIDTH__RESET                   2
#define EMAC_REGS__DESIGNCFG_DEBUG10__EMAC_BUS_WIDTH__READ(src) \
                    (((uint32_t)(src)\
                    & 0xf0000000U) >> 28)
#define EMAC_REGS__DESIGNCFG_DEBUG10__TYPE                             uint32_t
#define EMAC_REGS__DESIGNCFG_DEBUG10__READ                          0xffffffffU

#endif /* __EMAC_REGS__DESIGNCFG_DEBUG10_MACRO__ */


/* macros for designcfg_debug10 */
#define INST_DESIGNCFG_DEBUG10__NUM                                           1

/* macros for spec_add5_bottom */
#define INST_SPEC_ADD5_BOTTOM__NUM                                            1

/* macros for spec_add5_top */
#define INST_SPEC_ADD5_TOP__NUM                                               1

/* macros for spec_add6_bottom */
#define INST_SPEC_ADD6_BOTTOM__NUM                                            1

/* macros for spec_add6_top */
#define INST_SPEC_ADD6_TOP__NUM                                               1

/* macros for spec_add7_bottom */
#define INST_SPEC_ADD7_BOTTOM__NUM                                            1

/* macros for spec_add7_top */
#define INST_SPEC_ADD7_TOP__NUM                                               1

/* macros for spec_add8_bottom */
#define INST_SPEC_ADD8_BOTTOM__NUM                                            1

/* macros for spec_add8_top */
#define INST_SPEC_ADD8_TOP__NUM                                               1

/* macros for spec_add9_bottom */
#define INST_SPEC_ADD9_BOTTOM__NUM                                            1

/* macros for spec_add9_top */
#define INST_SPEC_ADD9_TOP__NUM                                               1

/* macros for spec_add10_bottom */
#define INST_SPEC_ADD10_BOTTOM__NUM                                           1

/* macros for spec_add10_top */
#define INST_SPEC_ADD10_TOP__NUM                                              1

/* macros for spec_add11_bottom */
#define INST_SPEC_ADD11_BOTTOM__NUM                                           1

/* macros for spec_add11_top */
#define INST_SPEC_ADD11_TOP__NUM                                              1

/* macros for spec_add12_bottom */
#define INST_SPEC_ADD12_BOTTOM__NUM                                           1

/* macros for spec_add12_top */
#define INST_SPEC_ADD12_TOP__NUM                                              1

/* macros for spec_add13_bottom */
#define INST_SPEC_ADD13_BOTTOM__NUM                                           1

/* macros for spec_add13_top */
#define INST_SPEC_ADD13_TOP__NUM                                              1

/* macros for spec_add14_bottom */
#define INST_SPEC_ADD14_BOTTOM__NUM                                           1

/* macros for spec_add14_top */
#define INST_SPEC_ADD14_TOP__NUM                                              1

/* macros for spec_add15_bottom */
#define INST_SPEC_ADD15_BOTTOM__NUM                                           1

/* macros for spec_add15_top */
#define INST_SPEC_ADD15_TOP__NUM                                              1

/* macros for spec_add16_bottom */
#define INST_SPEC_ADD16_BOTTOM__NUM                                           1

/* macros for spec_add16_top */
#define INST_SPEC_ADD16_TOP__NUM                                              1

/* macros for spec_add17_bottom */
#define INST_SPEC_ADD17_BOTTOM__NUM                                           1

/* macros for spec_add17_top */
#define INST_SPEC_ADD17_TOP__NUM                                              1

/* macros for spec_add18_bottom */
#define INST_SPEC_ADD18_BOTTOM__NUM                                           1

/* macros for spec_add18_top */
#define INST_SPEC_ADD18_TOP__NUM                                              1

/* macros for spec_add19_bottom */
#define INST_SPEC_ADD19_BOTTOM__NUM                                           1

/* macros for spec_add19_top */
#define INST_SPEC_ADD19_TOP__NUM                                              1

/* macros for spec_add20_bottom */
#define INST_SPEC_ADD20_BOTTOM__NUM                                           1

/* macros for spec_add20_top */
#define INST_SPEC_ADD20_TOP__NUM                                              1

/* macros for spec_add21_bottom */
#define INST_SPEC_ADD21_BOTTOM__NUM                                           1

/* macros for spec_add21_top */
#define INST_SPEC_ADD21_TOP__NUM                                              1

/* macros for spec_add22_bottom */
#define INST_SPEC_ADD22_BOTTOM__NUM                                           1

/* macros for spec_add22_top */
#define INST_SPEC_ADD22_TOP__NUM                                              1

/* macros for spec_add23_bottom */
#define INST_SPEC_ADD23_BOTTOM__NUM                                           1

/* macros for spec_add23_top */
#define INST_SPEC_ADD23_TOP__NUM                                              1

/* macros for spec_add24_bottom */
#define INST_SPEC_ADD24_BOTTOM__NUM                                           1

/* macros for spec_add24_top */
#define INST_SPEC_ADD24_TOP__NUM                                              1

/* macros for spec_add25_bottom */
#define INST_SPEC_ADD25_BOTTOM__NUM                                           1

/* macros for spec_add25_top */
#define INST_SPEC_ADD25_TOP__NUM                                              1

/* macros for spec_add26_bottom */
#define INST_SPEC_ADD26_BOTTOM__NUM                                           1

/* macros for spec_add26_top */
#define INST_SPEC_ADD26_TOP__NUM                                              1

/* macros for spec_add27_bottom */
#define INST_SPEC_ADD27_BOTTOM__NUM                                           1

/* macros for spec_add27_top */
#define INST_SPEC_ADD27_TOP__NUM                                              1

/* macros for spec_add28_bottom */
#define INST_SPEC_ADD28_BOTTOM__NUM                                           1

/* macros for spec_add28_top */
#define INST_SPEC_ADD28_TOP__NUM                                              1

/* macros for spec_add29_bottom */
#define INST_SPEC_ADD29_BOTTOM__NUM                                           1

/* macros for spec_add29_top */
#define INST_SPEC_ADD29_TOP__NUM                                              1

/* macros for spec_add30_bottom */
#define INST_SPEC_ADD30_BOTTOM__NUM                                           1

/* macros for spec_add30_top */
#define INST_SPEC_ADD30_TOP__NUM                                              1

/* macros for spec_add31_bottom */
#define INST_SPEC_ADD31_BOTTOM__NUM                                           1

/* macros for spec_add31_top */
#define INST_SPEC_ADD31_TOP__NUM                                              1

/* macros for spec_add32_bottom */
#define INST_SPEC_ADD32_BOTTOM__NUM                                           1

/* macros for spec_add32_top */
#define INST_SPEC_ADD32_TOP__NUM                                              1

/* macros for spec_add33_bottom */
#define INST_SPEC_ADD33_BOTTOM__NUM                                           1

/* macros for spec_add33_top */
#define INST_SPEC_ADD33_TOP__NUM                                              1

/* macros for spec_add34_bottom */
#define INST_SPEC_ADD34_BOTTOM__NUM                                           1

/* macros for spec_add34_top */
#define INST_SPEC_ADD34_TOP__NUM                                              1

/* macros for spec_add35_bottom */
#define INST_SPEC_ADD35_BOTTOM__NUM                                           1

/* macros for spec_add35_top */
#define INST_SPEC_ADD35_TOP__NUM                                              1

/* macros for spec_add36_bottom */
#define INST_SPEC_ADD36_BOTTOM__NUM                                           1

/* macros for spec_add36_top */
#define INST_SPEC_ADD36_TOP__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_q_status */
#ifndef __EMAC_REGS__INT_Q_STATUS_MACRO__
#define __EMAC_REGS__INT_Q_STATUS_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__SHIFT                            0
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__WIDTH                            1
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__MASK                   0x00000001U
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__RESET                            0
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_Q_STATUS__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field receive_complete */
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__SHIFT                      1
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__WIDTH                      1
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__MASK             0x00000002U
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__RESET                      0
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field rx_used_bit_read */
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__SHIFT                      2
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__WIDTH                      1
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__MASK             0x00000004U
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__RESET                      0
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field reserved_4_3 */
#define EMAC_REGS__INT_Q_STATUS__RESERVED_4_3__SHIFT                          3
#define EMAC_REGS__INT_Q_STATUS__RESERVED_4_3__WIDTH                          2
#define EMAC_REGS__INT_Q_STATUS__RESERVED_4_3__MASK                 0x00000018U
#define EMAC_REGS__INT_Q_STATUS__RESERVED_4_3__RESET                          0
#define EMAC_REGS__INT_Q_STATUS__RESERVED_4_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000018U) >> 3)

/* macros for field retry_limit_exceeded_or_late_collision */
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__SHIFT \
                    5
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__WIDTH \
                    1
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__MASK \
                    0x00000020U
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__RESET \
                    0
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field amba_error */
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__SHIFT                            6
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__WIDTH                            1
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__MASK                   0x00000040U
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__RESET                            0
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field transmit_complete */
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__SHIFT                     7
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__WIDTH                     1
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__MASK            0x00000080U
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__RESET                     0
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_9_8 */
#define EMAC_REGS__INT_Q_STATUS__RESERVED_9_8__SHIFT                          8
#define EMAC_REGS__INT_Q_STATUS__RESERVED_9_8__WIDTH                          2
#define EMAC_REGS__INT_Q_STATUS__RESERVED_9_8__MASK                 0x00000300U
#define EMAC_REGS__INT_Q_STATUS__RESERVED_9_8__RESET                          0
#define EMAC_REGS__INT_Q_STATUS__RESERVED_9_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000300U) >> 8)

/* macros for field receive_overrun */
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__SHIFT                      10
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__WIDTH                       1
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__MASK              0x00000400U
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__RESET                       0
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000400U) >> 10)
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(1) << 10)
#define EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000400U) | ((uint32_t)(0) << 10)

/* macros for field resp_not_ok */
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__SHIFT                          11
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__WIDTH                           1
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__MASK                  0x00000800U
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__RESET                         0b0
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field reserved_31_12 */
#define EMAC_REGS__INT_Q_STATUS__RESERVED_31_12__SHIFT                       12
#define EMAC_REGS__INT_Q_STATUS__RESERVED_31_12__WIDTH                       20
#define EMAC_REGS__INT_Q_STATUS__RESERVED_31_12__MASK               0xfffff000U
#define EMAC_REGS__INT_Q_STATUS__RESERVED_31_12__RESET                        0
#define EMAC_REGS__INT_Q_STATUS__RESERVED_31_12__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffff000U) >> 12)
#define EMAC_REGS__INT_Q_STATUS__TYPE                                  uint32_t
#define EMAC_REGS__INT_Q_STATUS__READ                               0xffffffffU
#define EMAC_REGS__INT_Q_STATUS__RCLR                               0x00000ce6U

#endif /* __EMAC_REGS__INT_Q_STATUS_MACRO__ */


/* macros for int_q1_status */
#define INST_INT_Q1_STATUS__NUM                                               1

/* macros for int_q2_status */
#define INST_INT_Q2_STATUS__NUM                                               1

/* macros for int_q3_status */
#define INST_INT_Q3_STATUS__NUM                                               1

/* macros for int_q4_status */
#define INST_INT_Q4_STATUS__NUM                                               1

/* macros for int_q5_status */
#define INST_INT_Q5_STATUS__NUM                                               1

/* macros for int_q6_status */
#define INST_INT_Q6_STATUS__NUM                                               1

/* macros for int_q7_status */
#define INST_INT_Q7_STATUS__NUM                                               1

/* macros for int_q8_status */
#define INST_INT_Q8_STATUS__NUM                                               1

/* macros for int_q9_status */
#define INST_INT_Q9_STATUS__NUM                                               1

/* macros for int_q10_status */
#define INST_INT_Q10_STATUS__NUM                                              1

/* macros for int_q11_status */
#define INST_INT_Q11_STATUS__NUM                                              1

/* macros for int_q12_status */
#define INST_INT_Q12_STATUS__NUM                                              1

/* macros for int_q13_status */
#define INST_INT_Q13_STATUS__NUM                                              1

/* macros for int_q14_status */
#define INST_INT_Q14_STATUS__NUM                                              1

/* macros for int_q15_status */
#define INST_INT_Q15_STATUS__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::transmit_qx_ptr */
#ifndef __EMAC_REGS__TRANSMIT_QX_PTR_MACRO__
#define __EMAC_REGS__TRANSMIT_QX_PTR_MACRO__

/* macros for field dma_tx_dis_q */
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__SHIFT                       0
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__WIDTH                       1
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__MASK              0x00000001U
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__RESET                     0b0
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_DIS_Q__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_1_1 */
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__SHIFT                       1
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__WIDTH                       1
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__MASK              0x00000002U
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__RESET                     0b0
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__TRANSMIT_QX_PTR__RESERVED_1_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field dma_tx_q_ptr */
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__SHIFT                       2
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__WIDTH                      30
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__MASK              0xfffffffcU
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__RESET                       0
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffffcU) >> 2)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0xfffffffcU)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xfffffffcU) | (((uint32_t)(src) <<\
                    2) & 0xfffffffcU)
#define EMAC_REGS__TRANSMIT_QX_PTR__DMA_TX_Q_PTR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0xfffffffcU)))
#define EMAC_REGS__TRANSMIT_QX_PTR__TYPE                               uint32_t
#define EMAC_REGS__TRANSMIT_QX_PTR__READ                            0xffffffffU
#define EMAC_REGS__TRANSMIT_QX_PTR__WRITE                           0xffffffffU

#endif /* __EMAC_REGS__TRANSMIT_QX_PTR_MACRO__ */


/* macros for transmit_q1_ptr */
#define INST_TRANSMIT_Q1_PTR__NUM                                             1

/* macros for transmit_q2_ptr */
#define INST_TRANSMIT_Q2_PTR__NUM                                             1

/* macros for transmit_q3_ptr */
#define INST_TRANSMIT_Q3_PTR__NUM                                             1

/* macros for transmit_q4_ptr */
#define INST_TRANSMIT_Q4_PTR__NUM                                             1

/* macros for transmit_q5_ptr */
#define INST_TRANSMIT_Q5_PTR__NUM                                             1

/* macros for transmit_q6_ptr */
#define INST_TRANSMIT_Q6_PTR__NUM                                             1

/* macros for transmit_q7_ptr */
#define INST_TRANSMIT_Q7_PTR__NUM                                             1

/* macros for transmit_q8_ptr */
#define INST_TRANSMIT_Q8_PTR__NUM                                             1

/* macros for transmit_q9_ptr */
#define INST_TRANSMIT_Q9_PTR__NUM                                             1

/* macros for transmit_q10_ptr */
#define INST_TRANSMIT_Q10_PTR__NUM                                            1

/* macros for transmit_q11_ptr */
#define INST_TRANSMIT_Q11_PTR__NUM                                            1

/* macros for transmit_q12_ptr */
#define INST_TRANSMIT_Q12_PTR__NUM                                            1

/* macros for transmit_q13_ptr */
#define INST_TRANSMIT_Q13_PTR__NUM                                            1

/* macros for transmit_q14_ptr */
#define INST_TRANSMIT_Q14_PTR__NUM                                            1

/* macros for transmit_q15_ptr */
#define INST_TRANSMIT_Q15_PTR__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::receive_qx_ptr */
#ifndef __EMAC_REGS__RECEIVE_QX_PTR_MACRO__
#define __EMAC_REGS__RECEIVE_QX_PTR_MACRO__

/* macros for field dma_rx_dis_q */
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__SHIFT                        0
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__WIDTH                        1
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__MASK               0x00000001U
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__RESET                      0b0
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_DIS_Q__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field reserved_1_1 */
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__SHIFT                        1
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__WIDTH                        1
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__MASK               0x00000002U
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__RESET                      0b0
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__RECEIVE_QX_PTR__RESERVED_1_1__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field dma_rx_q_ptr */
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__SHIFT                        2
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__WIDTH                       30
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__MASK               0xfffffffcU
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__RESET                        0
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffffcU) >> 2)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0xfffffffcU)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xfffffffcU) | (((uint32_t)(src) <<\
                    2) & 0xfffffffcU)
#define EMAC_REGS__RECEIVE_QX_PTR__DMA_RX_Q_PTR__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0xfffffffcU)))
#define EMAC_REGS__RECEIVE_QX_PTR__TYPE                                uint32_t
#define EMAC_REGS__RECEIVE_QX_PTR__READ                             0xffffffffU
#define EMAC_REGS__RECEIVE_QX_PTR__WRITE                            0xffffffffU

#endif /* __EMAC_REGS__RECEIVE_QX_PTR_MACRO__ */


/* macros for receive_q1_ptr */
#define INST_RECEIVE_Q1_PTR__NUM                                              1

/* macros for receive_q2_ptr */
#define INST_RECEIVE_Q2_PTR__NUM                                              1

/* macros for receive_q3_ptr */
#define INST_RECEIVE_Q3_PTR__NUM                                              1

/* macros for receive_q4_ptr */
#define INST_RECEIVE_Q4_PTR__NUM                                              1

/* macros for receive_q5_ptr */
#define INST_RECEIVE_Q5_PTR__NUM                                              1

/* macros for receive_q6_ptr */
#define INST_RECEIVE_Q6_PTR__NUM                                              1

/* macros for receive_q7_ptr */
#define INST_RECEIVE_Q7_PTR__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::dma_rxbuf_size_q */
#ifndef __EMAC_REGS__DMA_RXBUF_SIZE_Q_MACRO__
#define __EMAC_REGS__DMA_RXBUF_SIZE_Q_MACRO__

/* macros for field dma_rx_q_buf_size */
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__SHIFT                 0
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__WIDTH                 8
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__MASK        0x000000ffU
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__RESET                 2
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field reserved_31_8 */
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__RESERVED_31_8__SHIFT                     8
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__RESERVED_31_8__WIDTH                    24
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__RESERVED_31_8__MASK            0xffffff00U
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__RESERVED_31_8__RESET                     0
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__RESERVED_31_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffff00U) >> 8)
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__TYPE                              uint32_t
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__READ                           0xffffffffU
#define EMAC_REGS__DMA_RXBUF_SIZE_Q__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__DMA_RXBUF_SIZE_Q_MACRO__ */


/* macros for dma_rxbuf_size_q1 */
#define INST_DMA_RXBUF_SIZE_Q1__NUM                                           1

/* macros for dma_rxbuf_size_q2 */
#define INST_DMA_RXBUF_SIZE_Q2__NUM                                           1

/* macros for dma_rxbuf_size_q3 */
#define INST_DMA_RXBUF_SIZE_Q3__NUM                                           1

/* macros for dma_rxbuf_size_q4 */
#define INST_DMA_RXBUF_SIZE_Q4__NUM                                           1

/* macros for dma_rxbuf_size_q5 */
#define INST_DMA_RXBUF_SIZE_Q5__NUM                                           1

/* macros for dma_rxbuf_size_q6 */
#define INST_DMA_RXBUF_SIZE_Q6__NUM                                           1

/* macros for dma_rxbuf_size_q7 */
#define INST_DMA_RXBUF_SIZE_Q7__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::cbs_control */
#ifndef __EMAC_REGS__CBS_CONTROL_MACRO__
#define __EMAC_REGS__CBS_CONTROL_MACRO__

/* macros for field cbs_enable_queue_a */
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__SHIFT                     0
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__WIDTH                     1
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__MASK            0x00000001U
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__RESET                     0
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_A__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field cbs_enable_queue_b */
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__SHIFT                     1
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__WIDTH                     1
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__MASK            0x00000002U
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__RESET                     0
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__CBS_CONTROL__CBS_ENABLE_QUEUE_B__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field reserved_31_2 */
#define EMAC_REGS__CBS_CONTROL__RESERVED_31_2__SHIFT                          2
#define EMAC_REGS__CBS_CONTROL__RESERVED_31_2__WIDTH                         30
#define EMAC_REGS__CBS_CONTROL__RESERVED_31_2__MASK                 0xfffffffcU
#define EMAC_REGS__CBS_CONTROL__RESERVED_31_2__RESET                          0
#define EMAC_REGS__CBS_CONTROL__RESERVED_31_2__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffffcU) >> 2)
#define EMAC_REGS__CBS_CONTROL__TYPE                                   uint32_t
#define EMAC_REGS__CBS_CONTROL__READ                                0xffffffffU
#define EMAC_REGS__CBS_CONTROL__WRITE                               0xffffffffU

#endif /* __EMAC_REGS__CBS_CONTROL_MACRO__ */


/* macros for cbs_control */
#define INST_CBS_CONTROL__NUM                                                 1

/* macros for BlueprintGlobalNameSpace::emac_regs::cbs_idleslope_q_a */
#ifndef __EMAC_REGS__CBS_IDLESLOPE_Q_A_MACRO__
#define __EMAC_REGS__CBS_IDLESLOPE_Q_A_MACRO__

/* macros for field idleslope_a */
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__SHIFT                      0
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__WIDTH                     32
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__MASK             0xffffffffU
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__RESET                      0
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__IDLESLOPE_A__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__TYPE                             uint32_t
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__READ                          0xffffffffU
#define EMAC_REGS__CBS_IDLESLOPE_Q_A__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__CBS_IDLESLOPE_Q_A_MACRO__ */


/* macros for cbs_idleslope_q_a */
#define INST_CBS_IDLESLOPE_Q_A__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::cbs_idleslope_q_b */
#ifndef __EMAC_REGS__CBS_IDLESLOPE_Q_B_MACRO__
#define __EMAC_REGS__CBS_IDLESLOPE_Q_B_MACRO__

/* macros for field idleslope_b */
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__SHIFT                      0
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__WIDTH                     32
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__MASK             0xffffffffU
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__RESET                      0
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__IDLESLOPE_B__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__TYPE                             uint32_t
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__READ                          0xffffffffU
#define EMAC_REGS__CBS_IDLESLOPE_Q_B__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__CBS_IDLESLOPE_Q_B_MACRO__ */


/* macros for cbs_idleslope_q_b */
#define INST_CBS_IDLESLOPE_Q_B__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::upper_tx_q_base_addr */
#ifndef __EMAC_REGS__UPPER_TX_Q_BASE_ADDR_MACRO__
#define __EMAC_REGS__UPPER_TX_Q_BASE_ADDR_MACRO__

/* macros for field upper_tx_q_base_addr */
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__SHIFT          0
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__WIDTH         32
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__MASK 0xffffffffU
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__RESET          0
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__TYPE                          uint32_t
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__READ                       0xffffffffU
#define EMAC_REGS__UPPER_TX_Q_BASE_ADDR__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__UPPER_TX_Q_BASE_ADDR_MACRO__ */


/* macros for upper_tx_q_base_addr */
#define INST_UPPER_TX_Q_BASE_ADDR__NUM                                        1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_bd_control */
#ifndef __EMAC_REGS__TX_BD_CONTROL_MACRO__
#define __EMAC_REGS__TX_BD_CONTROL_MACRO__

/* macros for field reserved_3_0 */
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_3_0__SHIFT                         0
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_3_0__WIDTH                         4
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_3_0__MASK                0x0000000fU
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_3_0__RESET                         0
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_3_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)

/* macros for field tx_bd_ts_mode */
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__SHIFT                        4
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__WIDTH                        2
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__MASK               0x00000030U
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__RESET                        0
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000030U) >> 4)
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000030U)
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000030U) | (((uint32_t)(src) <<\
                    4) & 0x00000030U)
#define EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000030U)))

/* macros for field reserved_31_6 */
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_31_6__SHIFT                        6
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_31_6__WIDTH                       26
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_31_6__MASK               0xffffffc0U
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_31_6__RESET                        0
#define EMAC_REGS__TX_BD_CONTROL__RESERVED_31_6__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffffc0U) >> 6)
#define EMAC_REGS__TX_BD_CONTROL__TYPE                                 uint32_t
#define EMAC_REGS__TX_BD_CONTROL__READ                              0xffffffffU
#define EMAC_REGS__TX_BD_CONTROL__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__TX_BD_CONTROL_MACRO__ */


/* macros for tx_bd_control */
#define INST_TX_BD_CONTROL__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::rx_bd_control */
#ifndef __EMAC_REGS__RX_BD_CONTROL_MACRO__
#define __EMAC_REGS__RX_BD_CONTROL_MACRO__

/* macros for field reserved_3_0 */
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_3_0__SHIFT                         0
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_3_0__WIDTH                         4
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_3_0__MASK                0x0000000fU
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_3_0__RESET                         0
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_3_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)

/* macros for field rx_bd_ts_mode */
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__SHIFT                        4
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__WIDTH                        2
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__MASK               0x00000030U
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__RESET                        0
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000030U) >> 4)
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000030U)
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000030U) | (((uint32_t)(src) <<\
                    4) & 0x00000030U)
#define EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000030U)))

/* macros for field reserved_31_6 */
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_31_6__SHIFT                        6
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_31_6__WIDTH                       26
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_31_6__MASK               0xffffffc0U
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_31_6__RESET                        0
#define EMAC_REGS__RX_BD_CONTROL__RESERVED_31_6__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffffffc0U) >> 6)
#define EMAC_REGS__RX_BD_CONTROL__TYPE                                 uint32_t
#define EMAC_REGS__RX_BD_CONTROL__READ                              0xffffffffU
#define EMAC_REGS__RX_BD_CONTROL__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__RX_BD_CONTROL_MACRO__ */


/* macros for rx_bd_control */
#define INST_RX_BD_CONTROL__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::upper_rx_q_base_addr */
#ifndef __EMAC_REGS__UPPER_RX_Q_BASE_ADDR_MACRO__
#define __EMAC_REGS__UPPER_RX_Q_BASE_ADDR_MACRO__

/* macros for field upper_rx_q_base_addr */
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__SHIFT          0
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__WIDTH         32
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MASK 0xffffffffU
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__RESET          0
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__READ(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0xffffffffU)
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffffffffU) | ((uint32_t)(src) &\
                    0xffffffffU)
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0xffffffffU)))
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__TYPE                          uint32_t
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__READ                       0xffffffffU
#define EMAC_REGS__UPPER_RX_Q_BASE_ADDR__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__UPPER_RX_Q_BASE_ADDR_MACRO__ */


/* macros for upper_rx_q_base_addr */
#define INST_UPPER_RX_Q_BASE_ADDR__NUM                                        1

/* macros for BlueprintGlobalNameSpace::emac_regs::screening_type_1_register */
#ifndef __EMAC_REGS__SCREENING_TYPE_1_REGISTER_MACRO__
#define __EMAC_REGS__SCREENING_TYPE_1_REGISTER_MACRO__

/* macros for field queue_number */
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__SHIFT             0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__WIDTH             4
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__MASK    0x0000000fU
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__RESET             0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000000fU) | ((uint32_t)(src) &\
                    0x0000000fU)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000000fU)))

/* macros for field dstc_match */
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__SHIFT               4
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__WIDTH               8
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__MASK      0x00000ff0U
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__RESET               0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000ff0U) >> 4)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000ff0U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000ff0U) | (((uint32_t)(src) <<\
                    4) & 0x00000ff0U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000ff0U)))

/* macros for field udp_port_match */
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__SHIFT          12
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__WIDTH          16
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__MASK  0x0ffff000U
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__RESET           0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0ffff000U) >> 12)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x0ffff000U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0ffff000U) | (((uint32_t)(src) <<\
                    12) & 0x0ffff000U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x0ffff000U)))

/* macros for field dstc_enable */
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__SHIFT             28
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__WIDTH              1
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__MASK     0x10000000U
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__RESET              0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x10000000U) >> 28)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x10000000U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | (((uint32_t)(src) <<\
                    28) & 0x10000000U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x10000000U)))
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(1) << 28)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x10000000U) | ((uint32_t)(0) << 28)

/* macros for field udp_port_match_enable */
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__SHIFT   29
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__WIDTH    1
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__MASK \
                    0x20000000U
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__RESET    0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x20000000U) >> 29)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 29) & 0x20000000U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | (((uint32_t)(src) <<\
                    29) & 0x20000000U)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 29) & ~0x20000000U)))
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(1) << 29)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x20000000U) | ((uint32_t)(0) << 29)

/* macros for field reserved_31_30 */
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__RESERVED_31_30__SHIFT          30
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__RESERVED_31_30__WIDTH           2
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__RESERVED_31_30__MASK  0xc0000000U
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__RESERVED_31_30__RESET           0
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__RESERVED_31_30__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__TYPE                     uint32_t
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__READ                  0xffffffffU
#define EMAC_REGS__SCREENING_TYPE_1_REGISTER__WRITE                 0xffffffffU

#endif /* __EMAC_REGS__SCREENING_TYPE_1_REGISTER_MACRO__ */


/* macros for screening_type_1_register_0 */
#define INST_SCREENING_TYPE_1_REGISTER_0__NUM                                 1

/* macros for screening_type_1_register_1 */
#define INST_SCREENING_TYPE_1_REGISTER_1__NUM                                 1

/* macros for screening_type_1_register_2 */
#define INST_SCREENING_TYPE_1_REGISTER_2__NUM                                 1

/* macros for screening_type_1_register_3 */
#define INST_SCREENING_TYPE_1_REGISTER_3__NUM                                 1

/* macros for screening_type_1_register_4 */
#define INST_SCREENING_TYPE_1_REGISTER_4__NUM                                 1

/* macros for screening_type_1_register_5 */
#define INST_SCREENING_TYPE_1_REGISTER_5__NUM                                 1

/* macros for screening_type_1_register_6 */
#define INST_SCREENING_TYPE_1_REGISTER_6__NUM                                 1

/* macros for screening_type_1_register_7 */
#define INST_SCREENING_TYPE_1_REGISTER_7__NUM                                 1

/* macros for screening_type_1_register_8 */
#define INST_SCREENING_TYPE_1_REGISTER_8__NUM                                 1

/* macros for screening_type_1_register_9 */
#define INST_SCREENING_TYPE_1_REGISTER_9__NUM                                 1

/* macros for screening_type_1_register_10 */
#define INST_SCREENING_TYPE_1_REGISTER_10__NUM                                1

/* macros for screening_type_1_register_11 */
#define INST_SCREENING_TYPE_1_REGISTER_11__NUM                                1

/* macros for screening_type_1_register_12 */
#define INST_SCREENING_TYPE_1_REGISTER_12__NUM                                1

/* macros for screening_type_1_register_13 */
#define INST_SCREENING_TYPE_1_REGISTER_13__NUM                                1

/* macros for screening_type_1_register_14 */
#define INST_SCREENING_TYPE_1_REGISTER_14__NUM                                1

/* macros for screening_type_1_register_15 */
#define INST_SCREENING_TYPE_1_REGISTER_15__NUM                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::screening_type_2_register */
#ifndef __EMAC_REGS__SCREENING_TYPE_2_REGISTER_MACRO__
#define __EMAC_REGS__SCREENING_TYPE_2_REGISTER_MACRO__

/* macros for field queue_number */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__SHIFT             0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__WIDTH             4
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__MASK    0x0000000fU
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__RESET             0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000000fU)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000000fU) | ((uint32_t)(src) &\
                    0x0000000fU)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000000fU)))

/* macros for field vlan_priority */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__SHIFT            4
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__WIDTH            3
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__MASK   0x00000070U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__RESET            0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000070U) >> 4)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000070U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000070U) | (((uint32_t)(src) <<\
                    4) & 0x00000070U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000070U)))

/* macros for field reserved_7 */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__SHIFT               7
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__WIDTH               1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__MASK      0x00000080U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__RESET               0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_7__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field vlan_enable */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__SHIFT              8
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__WIDTH              1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__MASK     0x00000100U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__RESET              0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000100U) >> 8)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000100U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | (((uint32_t)(src) <<\
                    8) & 0x00000100U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000100U)))
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(1) << 8)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000100U) | ((uint32_t)(0) << 8)

/* macros for field index */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__SHIFT                    9
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__WIDTH                    3
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__MASK           0x00000e00U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__RESET                    0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000e00U) >> 9)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000e00U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000e00U) | (((uint32_t)(src) <<\
                    9) & 0x00000e00U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000e00U)))

/* macros for field ethertype_enable */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__SHIFT        12
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__WIDTH         1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__MASK \
                    0x00001000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__RESET         0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00001000U) >> 12)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00001000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | (((uint32_t)(src) <<\
                    12) & 0x00001000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00001000U)))
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(1) << 12)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00001000U) | ((uint32_t)(0) << 12)

/* macros for field compare_a */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__SHIFT               13
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__WIDTH                5
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__MASK       0x0003e000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__RESET                0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0003e000U) >> 13)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__WRITE(src) \
                    (((uint32_t)(src)\
                    << 13) & 0x0003e000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0003e000U) | (((uint32_t)(src) <<\
                    13) & 0x0003e000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 13) & ~0x0003e000U)))

/* macros for field compare_a_enable */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__SHIFT        18
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__WIDTH         1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__MASK \
                    0x00040000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__RESET         0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00040000U) >> 18)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field compare_b */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__SHIFT               19
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__WIDTH                5
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__MASK       0x00f80000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__RESET                0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00f80000U) >> 19)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00f80000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00f80000U) | (((uint32_t)(src) <<\
                    19) & 0x00f80000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00f80000U)))

/* macros for field compare_b_enable */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__SHIFT        24
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__WIDTH         1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__MASK \
                    0x01000000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__RESET         0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x01000000U) >> 24)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x01000000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | (((uint32_t)(src) <<\
                    24) & 0x01000000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x01000000U)))
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(1) << 24)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x01000000U) | ((uint32_t)(0) << 24)

/* macros for field compare_c */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__SHIFT               25
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__WIDTH                5
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__MASK       0x3e000000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__RESET                0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__READ(src) \
                    (((uint32_t)(src)\
                    & 0x3e000000U) >> 25)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__WRITE(src) \
                    (((uint32_t)(src)\
                    << 25) & 0x3e000000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3e000000U) | (((uint32_t)(src) <<\
                    25) & 0x3e000000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 25) & ~0x3e000000U)))

/* macros for field compare_c_enable */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__SHIFT        30
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__WIDTH         1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__MASK \
                    0x40000000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__RESET         0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__READ(src) \
                    (((uint32_t)(src)\
                    & 0x40000000U) >> 30)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0x40000000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | (((uint32_t)(src) <<\
                    30) & 0x40000000U)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0x40000000U)))
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(1) << 30)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x40000000U) | ((uint32_t)(0) << 30)

/* macros for field reserved_31 */
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__SHIFT             31
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__WIDTH              1
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__MASK     0x80000000U
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__RESET              0
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__RESERVED_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__TYPE                     uint32_t
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__READ                  0xffffffffU
#define EMAC_REGS__SCREENING_TYPE_2_REGISTER__WRITE                 0xffffffffU

#endif /* __EMAC_REGS__SCREENING_TYPE_2_REGISTER_MACRO__ */


/* macros for screening_type_2_register_0 */
#define INST_SCREENING_TYPE_2_REGISTER_0__NUM                                 1

/* macros for screening_type_2_register_1 */
#define INST_SCREENING_TYPE_2_REGISTER_1__NUM                                 1

/* macros for screening_type_2_register_2 */
#define INST_SCREENING_TYPE_2_REGISTER_2__NUM                                 1

/* macros for screening_type_2_register_3 */
#define INST_SCREENING_TYPE_2_REGISTER_3__NUM                                 1

/* macros for screening_type_2_register_4 */
#define INST_SCREENING_TYPE_2_REGISTER_4__NUM                                 1

/* macros for screening_type_2_register_5 */
#define INST_SCREENING_TYPE_2_REGISTER_5__NUM                                 1

/* macros for screening_type_2_register_6 */
#define INST_SCREENING_TYPE_2_REGISTER_6__NUM                                 1

/* macros for screening_type_2_register_7 */
#define INST_SCREENING_TYPE_2_REGISTER_7__NUM                                 1

/* macros for screening_type_2_register_8 */
#define INST_SCREENING_TYPE_2_REGISTER_8__NUM                                 1

/* macros for screening_type_2_register_9 */
#define INST_SCREENING_TYPE_2_REGISTER_9__NUM                                 1

/* macros for screening_type_2_register_10 */
#define INST_SCREENING_TYPE_2_REGISTER_10__NUM                                1

/* macros for screening_type_2_register_11 */
#define INST_SCREENING_TYPE_2_REGISTER_11__NUM                                1

/* macros for screening_type_2_register_12 */
#define INST_SCREENING_TYPE_2_REGISTER_12__NUM                                1

/* macros for screening_type_2_register_13 */
#define INST_SCREENING_TYPE_2_REGISTER_13__NUM                                1

/* macros for screening_type_2_register_14 */
#define INST_SCREENING_TYPE_2_REGISTER_14__NUM                                1

/* macros for screening_type_2_register_15 */
#define INST_SCREENING_TYPE_2_REGISTER_15__NUM                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_sched_ctrl */
#ifndef __EMAC_REGS__TX_SCHED_CTRL_MACRO__
#define __EMAC_REGS__TX_SCHED_CTRL_MACRO__

/* macros for field tx_sched_q1 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__SHIFT                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__MASK                 0x00000003U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000003U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000003U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000003U) | ((uint32_t)(src) &\
                    0x00000003U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q1__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000003U)))

/* macros for field tx_sched_q2 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__SHIFT                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__MASK                 0x0000000cU
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000000cU) >> 2)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x0000000cU)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000000cU) | (((uint32_t)(src) <<\
                    2) & 0x0000000cU)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q2__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x0000000cU)))

/* macros for field tx_sched_q3 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__SHIFT                          4
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__MASK                 0x00000030U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000030U) >> 4)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000030U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000030U) | (((uint32_t)(src) <<\
                    4) & 0x00000030U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q3__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000030U)))

/* macros for field tx_sched_q4 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__SHIFT                          6
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__MASK                 0x000000c0U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000000c0U) >> 6)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x000000c0U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000c0U) | (((uint32_t)(src) <<\
                    6) & 0x000000c0U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q4__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x000000c0U)))

/* macros for field tx_sched_q5 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__SHIFT                          8
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__MASK                 0x00000300U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000300U) >> 8)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000300U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000300U) | (((uint32_t)(src) <<\
                    8) & 0x00000300U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q5__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000300U)))

/* macros for field tx_sched_q6 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__SHIFT                         10
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__MASK                 0x00000c00U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000c00U) >> 10)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__WRITE(src) \
                    (((uint32_t)(src)\
                    << 10) & 0x00000c00U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000c00U) | (((uint32_t)(src) <<\
                    10) & 0x00000c00U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q6__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 10) & ~0x00000c00U)))

/* macros for field tx_sched_q7 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__SHIFT                         12
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__MASK                 0x00003000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00003000U) >> 12)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00003000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00003000U) | (((uint32_t)(src) <<\
                    12) & 0x00003000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q7__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00003000U)))

/* macros for field tx_sched_q8 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__SHIFT                         14
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__MASK                 0x0000c000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000c000U) >> 14)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__WRITE(src) \
                    (((uint32_t)(src)\
                    << 14) & 0x0000c000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000c000U) | (((uint32_t)(src) <<\
                    14) & 0x0000c000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q8__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 14) & ~0x0000c000U)))

/* macros for field tx_sched_q9 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__SHIFT                         16
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__WIDTH                          2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__MASK                 0x00030000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__RESET                          0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00030000U) >> 16)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00030000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00030000U) | (((uint32_t)(src) <<\
                    16) & 0x00030000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q9__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00030000U)))

/* macros for field tx_sched_q10 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__SHIFT                        18
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__MASK                0x000c0000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x000c0000U) >> 18)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x000c0000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000c0000U) | (((uint32_t)(src) <<\
                    18) & 0x000c0000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q10__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x000c0000U)))

/* macros for field tx_sched_q11 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__SHIFT                        20
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__MASK                0x00300000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00300000U) >> 20)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00300000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00300000U) | (((uint32_t)(src) <<\
                    20) & 0x00300000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q11__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00300000U)))

/* macros for field tx_sched_q12 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__SHIFT                        22
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__MASK                0x00c00000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00c00000U) >> 22)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__WRITE(src) \
                    (((uint32_t)(src)\
                    << 22) & 0x00c00000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00c00000U) | (((uint32_t)(src) <<\
                    22) & 0x00c00000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q12__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 22) & ~0x00c00000U)))

/* macros for field tx_sched_q13 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__SHIFT                        24
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__MASK                0x03000000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__READ(src) \
                    (((uint32_t)(src)\
                    & 0x03000000U) >> 24)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x03000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x03000000U) | (((uint32_t)(src) <<\
                    24) & 0x03000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q13__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x03000000U)))

/* macros for field tx_sched_q14 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__SHIFT                        26
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__MASK                0x0c000000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0c000000U) >> 26)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__WRITE(src) \
                    (((uint32_t)(src)\
                    << 26) & 0x0c000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0c000000U) | (((uint32_t)(src) <<\
                    26) & 0x0c000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q14__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 26) & ~0x0c000000U)))

/* macros for field tx_sched_q15 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__SHIFT                        28
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__MASK                0x30000000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__READ(src) \
                    (((uint32_t)(src)\
                    & 0x30000000U) >> 28)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x30000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x30000000U) | (((uint32_t)(src) <<\
                    28) & 0x30000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q15__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x30000000U)))

/* macros for field tx_sched_q16 */
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__SHIFT                        30
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__WIDTH                         2
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__MASK                0xc0000000U
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__RESET                         0
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__TX_SCHED_CTRL__TX_SCHED_Q16__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__TX_SCHED_CTRL__TYPE                                 uint32_t
#define EMAC_REGS__TX_SCHED_CTRL__READ                              0xffffffffU
#define EMAC_REGS__TX_SCHED_CTRL__WRITE                             0xffffffffU

#endif /* __EMAC_REGS__TX_SCHED_CTRL_MACRO__ */


/* macros for tx_sched_ctrl */
#define INST_TX_SCHED_CTRL__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::bw_rate_limit_q0to3 */
#ifndef __EMAC_REGS__BW_RATE_LIMIT_Q0TO3_MACRO__
#define __EMAC_REGS__BW_RATE_LIMIT_Q0TO3_MACRO__

/* macros for field dwrr_ets_weight_q0 */
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__SHIFT             0
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__MASK    0x000000ffU
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q0__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field dwrr_ets_weight_q1 */
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__SHIFT             8
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__MASK    0x0000ff00U
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q1__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field dwrr_ets_weight_q2 */
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__SHIFT            16
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__MASK    0x00ff0000U
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q2__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field dwrr_ets_weight_q3 */
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__SHIFT            24
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__MASK    0xff000000U
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xff000000U) | (((uint32_t)(src) <<\
                    24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__DWRR_ETS_WEIGHT_Q3__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0xff000000U)))
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__TYPE                           uint32_t
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__READ                        0xffffffffU
#define EMAC_REGS__BW_RATE_LIMIT_Q0TO3__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__BW_RATE_LIMIT_Q0TO3_MACRO__ */


/* macros for bw_rate_limit_q0to3 */
#define INST_BW_RATE_LIMIT_Q0TO3__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::bw_rate_limit_q4to7 */
#ifndef __EMAC_REGS__BW_RATE_LIMIT_Q4TO7_MACRO__
#define __EMAC_REGS__BW_RATE_LIMIT_Q4TO7_MACRO__

/* macros for field dwrr_ets_weight_q4 */
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__SHIFT             0
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__MASK    0x000000ffU
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q4__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field dwrr_ets_weight_q5 */
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__SHIFT             8
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__MASK    0x0000ff00U
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q5__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field dwrr_ets_weight_q6 */
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__SHIFT            16
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__MASK    0x00ff0000U
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q6__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field dwrr_ets_weight_q7 */
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__SHIFT            24
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__WIDTH             8
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__MASK    0xff000000U
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__RESET             0
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xff000000U) | (((uint32_t)(src) <<\
                    24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__DWRR_ETS_WEIGHT_Q7__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0xff000000U)))
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__TYPE                           uint32_t
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__READ                        0xffffffffU
#define EMAC_REGS__BW_RATE_LIMIT_Q4TO7__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__BW_RATE_LIMIT_Q4TO7_MACRO__ */


/* macros for bw_rate_limit_q4to7 */
#define INST_BW_RATE_LIMIT_Q4TO7__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::bw_rate_limit_q8to11 */
#ifndef __EMAC_REGS__BW_RATE_LIMIT_Q8TO11_MACRO__
#define __EMAC_REGS__BW_RATE_LIMIT_Q8TO11_MACRO__

/* macros for field dwrr_ets_weight_q8 */
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__SHIFT            0
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__WIDTH            8
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__MASK   0x000000ffU
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__RESET            0
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q8__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field dwrr_ets_weight_q9 */
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__SHIFT            8
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__WIDTH            8
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__MASK   0x0000ff00U
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__RESET            0
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q9__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field dwrr_ets_weight_q10 */
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__SHIFT          16
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__WIDTH           8
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__MASK  0x00ff0000U
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__RESET           0
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q10__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field dwrr_ets_weight_q11 */
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__SHIFT          24
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__WIDTH           8
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__MASK  0xff000000U
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__RESET           0
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xff000000U) | (((uint32_t)(src) <<\
                    24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__DWRR_ETS_WEIGHT_Q11__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0xff000000U)))
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__TYPE                          uint32_t
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__READ                       0xffffffffU
#define EMAC_REGS__BW_RATE_LIMIT_Q8TO11__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__BW_RATE_LIMIT_Q8TO11_MACRO__ */


/* macros for bw_rate_limit_q8to11 */
#define INST_BW_RATE_LIMIT_Q8TO11__NUM                                        1

/* macros for BlueprintGlobalNameSpace::emac_regs::bw_rate_limit_q12to15 */
#ifndef __EMAC_REGS__BW_RATE_LIMIT_Q12TO15_MACRO__
#define __EMAC_REGS__BW_RATE_LIMIT_Q12TO15_MACRO__

/* macros for field dwrr_ets_weight_q12 */
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__SHIFT          0
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__WIDTH          8
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__MASK 0x000000ffU
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__RESET          0
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__READ(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x000000ffU) | ((uint32_t)(src) &\
                    0x000000ffU)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q12__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x000000ffU)))

/* macros for field dwrr_ets_weight_q13 */
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__SHIFT          8
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__WIDTH          8
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__MASK 0x0000ff00U
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__RESET          0
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ff00U) | (((uint32_t)(src) <<\
                    8) & 0x0000ff00U)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q13__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x0000ff00U)))

/* macros for field dwrr_ets_weight_q14 */
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__SHIFT         16
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__WIDTH          8
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__MASK 0x00ff0000U
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__RESET          0
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00ff0000U) >> 16)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00ff0000U) | (((uint32_t)(src) <<\
                    16) & 0x00ff0000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q14__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00ff0000U)))

/* macros for field dwrr_ets_weight_q15 */
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__SHIFT         24
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__WIDTH          8
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__MASK 0xff000000U
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__RESET          0
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xff000000U) | (((uint32_t)(src) <<\
                    24) & 0xff000000U)
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__DWRR_ETS_WEIGHT_Q15__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0xff000000U)))
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__TYPE                         uint32_t
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__READ                      0xffffffffU
#define EMAC_REGS__BW_RATE_LIMIT_Q12TO15__WRITE                     0xffffffffU

#endif /* __EMAC_REGS__BW_RATE_LIMIT_Q12TO15_MACRO__ */


/* macros for bw_rate_limit_q12to15 */
#define INST_BW_RATE_LIMIT_Q12TO15__NUM                                       1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_q_seg_alloc_q0to7 */
#ifndef __EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7_MACRO__
#define __EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7_MACRO__

/* macros for field segment_alloc_q0 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__SHIFT              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__MASK     0x00000007U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000007U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000007U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000007U) | ((uint32_t)(src) &\
                    0x00000007U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q0__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000007U)))

/* macros for field reserved_3_3 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__SHIFT                  3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__WIDTH                  1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__MASK         0x00000008U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__RESET                  0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_3_3__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field segment_alloc_q1 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__SHIFT              4
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__MASK     0x00000070U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000070U) >> 4)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000070U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000070U) | (((uint32_t)(src) <<\
                    4) & 0x00000070U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q1__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000070U)))

/* macros for field reserved_7_7 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__SHIFT                  7
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__WIDTH                  1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__MASK         0x00000080U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__RESET                  0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_7_7__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field segment_alloc_q2 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__SHIFT              8
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__MASK     0x00000700U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000700U) >> 8)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000700U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000700U) | (((uint32_t)(src) <<\
                    8) & 0x00000700U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q2__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000700U)))

/* macros for field reserved_11_11 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__SHIFT               11
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__WIDTH                1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__MASK       0x00000800U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__RESET                0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_11_11__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field segment_alloc_q3 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__SHIFT             12
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__MASK     0x00007000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00007000U) >> 12)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00007000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00007000U) | (((uint32_t)(src) <<\
                    12) & 0x00007000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q3__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00007000U)))

/* macros for field reserved_15_15 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__SHIFT               15
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__WIDTH                1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__MASK       0x00008000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__RESET                0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_15_15__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field segment_alloc_q4 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__SHIFT             16
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__MASK     0x00070000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00070000U) >> 16)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00070000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00070000U) | (((uint32_t)(src) <<\
                    16) & 0x00070000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q4__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00070000U)))

/* macros for field reserved_19_19 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__SHIFT               19
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__WIDTH                1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__MASK       0x00080000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__RESET                0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_19_19__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field segment_alloc_q5 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__SHIFT             20
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__MASK     0x00700000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00700000U) >> 20)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00700000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00700000U) | (((uint32_t)(src) <<\
                    20) & 0x00700000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q5__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00700000U)))

/* macros for field reserved_23_23 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__SHIFT               23
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__WIDTH                1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__MASK       0x00800000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__RESET                0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_23_23__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field segment_alloc_q6 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__SHIFT             24
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__MASK     0x07000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__READ(src) \
                    (((uint32_t)(src)\
                    & 0x07000000U) >> 24)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x07000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x07000000U) | (((uint32_t)(src) <<\
                    24) & 0x07000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q6__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x07000000U)))

/* macros for field reserved_27_27 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__SHIFT               27
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__WIDTH                1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__MASK       0x08000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__RESET                0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_27_27__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field segment_alloc_q7 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__SHIFT             28
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__WIDTH              3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__MASK     0x70000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__RESET              0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x70000000U) >> 28)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x70000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x70000000U) | (((uint32_t)(src) <<\
                    28) & 0x70000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__SEGMENT_ALLOC_Q7__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x70000000U)))

/* macros for field reserved_31_31 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__SHIFT               31
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__WIDTH                1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__MASK       0x80000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__RESET                0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__RESERVED_31_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__TYPE                          uint32_t
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__READ                       0xffffffffU
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__TX_Q_SEG_ALLOC_Q0TO7_MACRO__ */


/* macros for tx_q_seg_alloc_q0to7 */
#define INST_TX_Q_SEG_ALLOC_Q0TO7__NUM                                        1

/* macros for BlueprintGlobalNameSpace::emac_regs::tx_q_seg_alloc_q8to15 */
#ifndef __EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15_MACRO__
#define __EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15_MACRO__

/* macros for field segment_alloc_q8 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__SHIFT             0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__WIDTH             3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__MASK    0x00000007U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__RESET             0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000007U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000007U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000007U) | ((uint32_t)(src) &\
                    0x00000007U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q8__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000007U)))

/* macros for field reserved_3_3 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__SHIFT                 3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__WIDTH                 1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__MASK        0x00000008U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__RESET                 0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_3_3__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field segment_alloc_q9 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__SHIFT             4
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__WIDTH             3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__MASK    0x00000070U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__RESET             0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000070U) >> 4)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000070U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000070U) | (((uint32_t)(src) <<\
                    4) & 0x00000070U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q9__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000070U)))

/* macros for field reserved_7_7 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__SHIFT                 7
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__WIDTH                 1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__MASK        0x00000080U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__RESET                 0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_7_7__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field segment_alloc_q10 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__SHIFT            8
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__WIDTH            3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__MASK   0x00000700U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__RESET            0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000700U) >> 8)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__WRITE(src) \
                    (((uint32_t)(src)\
                    << 8) & 0x00000700U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000700U) | (((uint32_t)(src) <<\
                    8) & 0x00000700U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q10__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 8) & ~0x00000700U)))

/* macros for field reserved_11_11 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__SHIFT              11
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__WIDTH               1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__MASK      0x00000800U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__RESET               0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_11_11__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field segment_alloc_q11 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__SHIFT           12
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__WIDTH            3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__MASK   0x00007000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__RESET            0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00007000U) >> 12)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__WRITE(src) \
                    (((uint32_t)(src)\
                    << 12) & 0x00007000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00007000U) | (((uint32_t)(src) <<\
                    12) & 0x00007000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q11__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 12) & ~0x00007000U)))

/* macros for field reserved_15_15 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__SHIFT              15
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__WIDTH               1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__MASK      0x00008000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__RESET               0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00008000U) >> 15)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(1) << 15)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_15_15__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00008000U) | ((uint32_t)(0) << 15)

/* macros for field segment_alloc_q12 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__SHIFT           16
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__WIDTH            3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__MASK   0x00070000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__RESET            0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00070000U) >> 16)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00070000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00070000U) | (((uint32_t)(src) <<\
                    16) & 0x00070000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q12__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00070000U)))

/* macros for field reserved_19_19 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__SHIFT              19
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__WIDTH               1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__MASK      0x00080000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__RESET               0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00080000U) >> 19)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_19_19__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field segment_alloc_q13 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__SHIFT           20
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__WIDTH            3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__MASK   0x00700000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__RESET            0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00700000U) >> 20)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00700000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00700000U) | (((uint32_t)(src) <<\
                    20) & 0x00700000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q13__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00700000U)))

/* macros for field reserved_23_23 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__SHIFT              23
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__WIDTH               1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__MASK      0x00800000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__RESET               0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00800000U) >> 23)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_23_23__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field segment_alloc_q14 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__SHIFT           24
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__WIDTH            3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__MASK   0x07000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__RESET            0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x07000000U) >> 24)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__WRITE(src) \
                    (((uint32_t)(src)\
                    << 24) & 0x07000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x07000000U) | (((uint32_t)(src) <<\
                    24) & 0x07000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q14__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 24) & ~0x07000000U)))

/* macros for field reserved_27_27 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__SHIFT              27
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__WIDTH               1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__MASK      0x08000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__RESET               0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__READ(src) \
                    (((uint32_t)(src)\
                    & 0x08000000U) >> 27)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(1) << 27)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_27_27__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x08000000U) | ((uint32_t)(0) << 27)

/* macros for field segment_alloc_q15 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__SHIFT           28
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__WIDTH            3
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__MASK   0x70000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__RESET            0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__READ(src) \
                    (((uint32_t)(src)\
                    & 0x70000000U) >> 28)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__WRITE(src) \
                    (((uint32_t)(src)\
                    << 28) & 0x70000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x70000000U) | (((uint32_t)(src) <<\
                    28) & 0x70000000U)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__SEGMENT_ALLOC_Q15__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 28) & ~0x70000000U)))

/* macros for field reserved_31_31 */
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__SHIFT              31
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__WIDTH               1
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__MASK      0x80000000U
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__RESET               0
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__READ(src) \
                    (((uint32_t)(src)\
                    & 0x80000000U) >> 31)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(1) << 31)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__RESERVED_31_31__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x80000000U) | ((uint32_t)(0) << 31)
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__TYPE                         uint32_t
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__READ                      0xffffffffU
#define EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15__WRITE                     0xffffffffU

#endif /* __EMAC_REGS__TX_Q_SEG_ALLOC_Q8TO15_MACRO__ */


/* macros for tx_q_seg_alloc_q8to15 */
#define INST_TX_Q_SEG_ALLOC_Q8TO15__NUM                                       1

/* macros for receive_q8_ptr */
#define INST_RECEIVE_Q8_PTR__NUM                                              1

/* macros for receive_q9_ptr */
#define INST_RECEIVE_Q9_PTR__NUM                                              1

/* macros for receive_q10_ptr */
#define INST_RECEIVE_Q10_PTR__NUM                                             1

/* macros for receive_q11_ptr */
#define INST_RECEIVE_Q11_PTR__NUM                                             1

/* macros for receive_q12_ptr */
#define INST_RECEIVE_Q12_PTR__NUM                                             1

/* macros for receive_q13_ptr */
#define INST_RECEIVE_Q13_PTR__NUM                                             1

/* macros for receive_q14_ptr */
#define INST_RECEIVE_Q14_PTR__NUM                                             1

/* macros for receive_q15_ptr */
#define INST_RECEIVE_Q15_PTR__NUM                                             1

/* macros for dma_rxbuf_size_q8 */
#define INST_DMA_RXBUF_SIZE_Q8__NUM                                           1

/* macros for dma_rxbuf_size_q9 */
#define INST_DMA_RXBUF_SIZE_Q9__NUM                                           1

/* macros for dma_rxbuf_size_q10 */
#define INST_DMA_RXBUF_SIZE_Q10__NUM                                          1

/* macros for dma_rxbuf_size_q11 */
#define INST_DMA_RXBUF_SIZE_Q11__NUM                                          1

/* macros for dma_rxbuf_size_q12 */
#define INST_DMA_RXBUF_SIZE_Q12__NUM                                          1

/* macros for dma_rxbuf_size_q13 */
#define INST_DMA_RXBUF_SIZE_Q13__NUM                                          1

/* macros for dma_rxbuf_size_q14 */
#define INST_DMA_RXBUF_SIZE_Q14__NUM                                          1

/* macros for dma_rxbuf_size_q15 */
#define INST_DMA_RXBUF_SIZE_Q15__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_q_enable */
#ifndef __EMAC_REGS__INT_Q_ENABLE_MACRO__
#define __EMAC_REGS__INT_Q_ENABLE_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__SHIFT                            0
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__WIDTH                            1
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__MASK                   0x00000001U
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__RESET                            0
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field enable_receive_complete_interrupt */
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SHIFT     1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__WIDTH     1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__MASK \
                    0x00000002U
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__RESET     0
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field enable_rx_used_bit_read_interrupt */
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__SHIFT     2
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__WIDTH     1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__MASK \
                    0x00000004U
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__RESET     0
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field reserved_4_3 */
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_4_3__SHIFT                          3
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_4_3__WIDTH                          2
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_4_3__MASK                 0x00000018U
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_4_3__RESET                          0
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_4_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000018U) >> 3)

/* macros for field enable_retry_limit_exceeded_or_late_collision_interrupt */
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SHIFT \
                    5
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MASK \
                    0x00000020U
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field enable_transmit_frame_corruption_due_to_amba_error_interrupt */
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SHIFT \
                    6
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MASK \
                    0x00000040U
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field enable_transmit_complete_interrupt */
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SHIFT    7
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__WIDTH    1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__MASK \
                    0x00000080U
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__RESET    0
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_10_8 */
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_10_8__SHIFT                         8
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_10_8__WIDTH                         3
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_10_8__MASK                0x00000700U
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_10_8__RESET                         0
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_10_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000700U) >> 8)

/* macros for field enable_resp_not_ok_interrupt */
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SHIFT         11
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__WIDTH          1
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__MASK 0x00000800U
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__RESET          0
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field reserved_31_12 */
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_31_12__SHIFT                       12
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_31_12__WIDTH                       20
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_31_12__MASK               0xfffff000U
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_31_12__RESET                        0
#define EMAC_REGS__INT_Q_ENABLE__RESERVED_31_12__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffff000U) >> 12)
#define EMAC_REGS__INT_Q_ENABLE__TYPE                                  uint32_t
#define EMAC_REGS__INT_Q_ENABLE__READ                               0xfffff719U
#define EMAC_REGS__INT_Q_ENABLE__WRITE                              0xfffff719U

#endif /* __EMAC_REGS__INT_Q_ENABLE_MACRO__ */


/* macros for int_q1_enable */
#define INST_INT_Q1_ENABLE__NUM                                               1

/* macros for int_q2_enable */
#define INST_INT_Q2_ENABLE__NUM                                               1

/* macros for int_q3_enable */
#define INST_INT_Q3_ENABLE__NUM                                               1

/* macros for int_q4_enable */
#define INST_INT_Q4_ENABLE__NUM                                               1

/* macros for int_q5_enable */
#define INST_INT_Q5_ENABLE__NUM                                               1

/* macros for int_q6_enable */
#define INST_INT_Q6_ENABLE__NUM                                               1

/* macros for int_q7_enable */
#define INST_INT_Q7_ENABLE__NUM                                               1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_q_disable */
#ifndef __EMAC_REGS__INT_Q_DISABLE_MACRO__
#define __EMAC_REGS__INT_Q_DISABLE_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__SHIFT                           0
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__WIDTH                           1
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__MASK                  0x00000001U
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__RESET                           0
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field disable_receive_complete_interrupt */
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SHIFT   1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__WIDTH   1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__MASK \
                    0x00000002U
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__RESET   0
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field disable_rx_used_bit_read_interrupt */
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__SHIFT   2
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__WIDTH   1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__MASK \
                    0x00000004U
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__RESET   0
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field reserved_4_3 */
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_4_3__SHIFT                         3
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_4_3__WIDTH                         2
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_4_3__MASK                0x00000018U
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_4_3__RESET                         0
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_4_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000018U) >> 3)

/* macros for field disable_retry_limit_exceeded_or_late_collision_interrupt */
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SHIFT \
                    5
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MASK \
                    0x00000020U
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field disable_transmit_frame_corruption_due_to_amba_error_interrupt */
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SHIFT \
                    6
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WIDTH \
                    1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MASK \
                    0x00000040U
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__RESET \
                    0
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field disable_transmit_complete_interrupt */
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SHIFT  7
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__WIDTH  1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__MASK \
                    0x00000080U
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__RESET  0
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_10_8 */
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_10_8__SHIFT                        8
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_10_8__WIDTH                        3
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_10_8__MASK               0x00000700U
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_10_8__RESET                        0
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_10_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000700U) >> 8)

/* macros for field disable_resp_not_ok_interrupt */
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SHIFT       11
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__WIDTH        1
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__MASK \
                    0x00000800U
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__RESET        0
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__WRITE(src) \
                    (((uint32_t)(src)\
                    << 11) & 0x00000800U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | (((uint32_t)(src) <<\
                    11) & 0x00000800U)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 11) & ~0x00000800U)))
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field reserved_31_12 */
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_31_12__SHIFT                      12
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_31_12__WIDTH                      20
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_31_12__MASK              0xfffff000U
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_31_12__RESET                       0
#define EMAC_REGS__INT_Q_DISABLE__RESERVED_31_12__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffff000U) >> 12)
#define EMAC_REGS__INT_Q_DISABLE__TYPE                                 uint32_t
#define EMAC_REGS__INT_Q_DISABLE__READ                              0xfffff719U
#define EMAC_REGS__INT_Q_DISABLE__WRITE                             0xfffff719U

#endif /* __EMAC_REGS__INT_Q_DISABLE_MACRO__ */


/* macros for int_q1_disable */
#define INST_INT_Q1_DISABLE__NUM                                              1

/* macros for int_q2_disable */
#define INST_INT_Q2_DISABLE__NUM                                              1

/* macros for int_q3_disable */
#define INST_INT_Q3_DISABLE__NUM                                              1

/* macros for int_q4_disable */
#define INST_INT_Q4_DISABLE__NUM                                              1

/* macros for int_q5_disable */
#define INST_INT_Q5_DISABLE__NUM                                              1

/* macros for int_q6_disable */
#define INST_INT_Q6_DISABLE__NUM                                              1

/* macros for int_q7_disable */
#define INST_INT_Q7_DISABLE__NUM                                              1

/* macros for BlueprintGlobalNameSpace::emac_regs::int_q_mask */
#ifndef __EMAC_REGS__INT_Q_MASK_MACRO__
#define __EMAC_REGS__INT_Q_MASK_MACRO__

/* macros for field reserved_0 */
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__SHIFT                              0
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__WIDTH                              1
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__MASK                     0x00000001U
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__RESET                              0
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__INT_Q_MASK__RESERVED_0__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field receive_complete_interrupt_mask */
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__SHIFT         1
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__WIDTH         1
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__MASK \
                    0x00000002U
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__RESET         1
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field rx_used_interrupt_mask */
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__SHIFT                  2
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__WIDTH                  1
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__MASK         0x00000004U
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__RESET                  1
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field reserved_4_3 */
#define EMAC_REGS__INT_Q_MASK__RESERVED_4_3__SHIFT                            3
#define EMAC_REGS__INT_Q_MASK__RESERVED_4_3__WIDTH                            2
#define EMAC_REGS__INT_Q_MASK__RESERVED_4_3__MASK                   0x00000018U
#define EMAC_REGS__INT_Q_MASK__RESERVED_4_3__RESET                            0
#define EMAC_REGS__INT_Q_MASK__RESERVED_4_3__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000018U) >> 3)

/* macros for field retry_limit_exceeded_or_late_collision_interrupt_mask */
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__SHIFT \
                    5
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__WIDTH \
                    1
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__MASK \
                    0x00000020U
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__RESET \
                    1
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field amba_error_interrupt_mask */
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__SHIFT               6
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__WIDTH               1
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__MASK      0x00000040U
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__RESET               1
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field transmit_complete_interrupt_mask */
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__SHIFT        7
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__WIDTH        1
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__MASK \
                    0x00000080U
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__RESET        1
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_10_8 */
#define EMAC_REGS__INT_Q_MASK__RESERVED_10_8__SHIFT                           8
#define EMAC_REGS__INT_Q_MASK__RESERVED_10_8__WIDTH                           3
#define EMAC_REGS__INT_Q_MASK__RESERVED_10_8__MASK                  0x00000700U
#define EMAC_REGS__INT_Q_MASK__RESERVED_10_8__RESET                           0
#define EMAC_REGS__INT_Q_MASK__RESERVED_10_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000700U) >> 8)

/* macros for field resp_not_ok_interrupt_mask */
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__SHIFT             11
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__WIDTH              1
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__MASK     0x00000800U
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__RESET              1
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000800U) >> 11)
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(1) << 11)
#define EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000800U) | ((uint32_t)(0) << 11)

/* macros for field reserved_31_12 */
#define EMAC_REGS__INT_Q_MASK__RESERVED_31_12__SHIFT                         12
#define EMAC_REGS__INT_Q_MASK__RESERVED_31_12__WIDTH                         20
#define EMAC_REGS__INT_Q_MASK__RESERVED_31_12__MASK                 0xfffff000U
#define EMAC_REGS__INT_Q_MASK__RESERVED_31_12__RESET                          0
#define EMAC_REGS__INT_Q_MASK__RESERVED_31_12__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffff000U) >> 12)
#define EMAC_REGS__INT_Q_MASK__TYPE                                    uint32_t
#define EMAC_REGS__INT_Q_MASK__READ                                 0xffffffffU

#endif /* __EMAC_REGS__INT_Q_MASK_MACRO__ */


/* macros for int_q1_mask */
#define INST_INT_Q1_MASK__NUM                                                 1

/* macros for int_q2_mask */
#define INST_INT_Q2_MASK__NUM                                                 1

/* macros for int_q3_mask */
#define INST_INT_Q3_MASK__NUM                                                 1

/* macros for int_q4_mask */
#define INST_INT_Q4_MASK__NUM                                                 1

/* macros for int_q5_mask */
#define INST_INT_Q5_MASK__NUM                                                 1

/* macros for int_q6_mask */
#define INST_INT_Q6_MASK__NUM                                                 1

/* macros for int_q7_mask */
#define INST_INT_Q7_MASK__NUM                                                 1

/* macros for int_q8_enable */
#define INST_INT_Q8_ENABLE__NUM                                               1

/* macros for int_q9_enable */
#define INST_INT_Q9_ENABLE__NUM                                               1

/* macros for int_q10_enable */
#define INST_INT_Q10_ENABLE__NUM                                              1

/* macros for int_q11_enable */
#define INST_INT_Q11_ENABLE__NUM                                              1

/* macros for int_q12_enable */
#define INST_INT_Q12_ENABLE__NUM                                              1

/* macros for int_q13_enable */
#define INST_INT_Q13_ENABLE__NUM                                              1

/* macros for int_q14_enable */
#define INST_INT_Q14_ENABLE__NUM                                              1

/* macros for int_q15_enable */
#define INST_INT_Q15_ENABLE__NUM                                              1

/* macros for int_q8_disable */
#define INST_INT_Q8_DISABLE__NUM                                              1

/* macros for int_q9_disable */
#define INST_INT_Q9_DISABLE__NUM                                              1

/* macros for int_q10_disable */
#define INST_INT_Q10_DISABLE__NUM                                             1

/* macros for int_q11_disable */
#define INST_INT_Q11_DISABLE__NUM                                             1

/* macros for int_q12_disable */
#define INST_INT_Q12_DISABLE__NUM                                             1

/* macros for int_q13_disable */
#define INST_INT_Q13_DISABLE__NUM                                             1

/* macros for int_q14_disable */
#define INST_INT_Q14_DISABLE__NUM                                             1

/* macros for int_q15_disable */
#define INST_INT_Q15_DISABLE__NUM                                             1

/* macros for int_q8_mask */
#define INST_INT_Q8_MASK__NUM                                                 1

/* macros for int_q9_mask */
#define INST_INT_Q9_MASK__NUM                                                 1

/* macros for int_q10_mask */
#define INST_INT_Q10_MASK__NUM                                                1

/* macros for int_q11_mask */
#define INST_INT_Q11_MASK__NUM                                                1

/* macros for int_q12_mask */
#define INST_INT_Q12_MASK__NUM                                                1

/* macros for int_q13_mask */
#define INST_INT_Q13_MASK__NUM                                                1

/* macros for int_q14_mask */
#define INST_INT_Q14_MASK__NUM                                                1

/* macros for int_q15_mask */
#define INST_INT_Q15_MASK__NUM                                                1

/* macros for BlueprintGlobalNameSpace::emac_regs::screening_type_2_ethertype_reg */
#ifndef __EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG_MACRO__
#define __EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG_MACRO__

/* macros for field compare_value */
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__SHIFT       0
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__WIDTH      16
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__MASK \
                    0x0000ffffU
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__RESET       0
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field reserved_31_16 */
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__RESERVED_31_16__SHIFT     16
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__RESERVED_31_16__WIDTH     16
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__RESERVED_31_16__MASK \
                    0xffff0000U
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__RESERVED_31_16__RESET      0
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__RESERVED_31_16__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__TYPE                uint32_t
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__READ             0xffffffffU
#define EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__WRITE            0xffffffffU

#endif /* __EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG_MACRO__ */


/* macros for screening_type_2_ethertype_reg_0 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_0__NUM                            1

/* macros for screening_type_2_ethertype_reg_1 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_1__NUM                            1

/* macros for screening_type_2_ethertype_reg_2 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_2__NUM                            1

/* macros for screening_type_2_ethertype_reg_3 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_3__NUM                            1

/* macros for screening_type_2_ethertype_reg_4 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_4__NUM                            1

/* macros for screening_type_2_ethertype_reg_5 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_5__NUM                            1

/* macros for screening_type_2_ethertype_reg_6 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_6__NUM                            1

/* macros for screening_type_2_ethertype_reg_7 */
#define INST_SCREENING_TYPE_2_ETHERTYPE_REG_7__NUM                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::type2_compare_word_0 */
#ifndef __EMAC_REGS__TYPE2_COMPARE_WORD_0_MACRO__
#define __EMAC_REGS__TYPE2_COMPARE_WORD_0_MACRO__

/* macros for field mask_value */
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__SHIFT                    0
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__WIDTH                   16
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__MASK           0x0000ffffU
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__RESET                    0
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000ffffU)
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000ffffU) | ((uint32_t)(src) &\
                    0x0000ffffU)
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000ffffU)))

/* macros for field compare_value */
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__SHIFT                16
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__WIDTH                16
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__MASK        0xffff0000U
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__RESET                 0
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__READ(src) \
                    (((uint32_t)(src)\
                    & 0xffff0000U) >> 16)
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0xffff0000U)
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xffff0000U) | (((uint32_t)(src) <<\
                    16) & 0xffff0000U)
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0xffff0000U)))
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__TYPE                          uint32_t
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__READ                       0xffffffffU
#define EMAC_REGS__TYPE2_COMPARE_WORD_0__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__TYPE2_COMPARE_WORD_0_MACRO__ */


/* macros for type2_compare_0_word_0 */
#define INST_TYPE2_COMPARE_0_WORD_0__NUM                                      1

/* macros for BlueprintGlobalNameSpace::emac_regs::type2_compare_word_1 */
#ifndef __EMAC_REGS__TYPE2_COMPARE_WORD_1_MACRO__
#define __EMAC_REGS__TYPE2_COMPARE_WORD_1_MACRO__

/* macros for field offset_value */
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__SHIFT                  0
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__WIDTH                  7
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MASK         0x0000007fU
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__RESET                  0
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0000007fU)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0000007fU)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0000007fU) | ((uint32_t)(src) &\
                    0x0000007fU)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0000007fU)))

/* macros for field compare_offset */
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__SHIFT                7
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__WIDTH                2
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MASK       0x00000180U
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__RESET                0
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000180U) >> 7)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000180U)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000180U) | (((uint32_t)(src) <<\
                    7) & 0x00000180U)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000180U)))

/* macros for field disable_mask */
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__SHIFT                  9
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__WIDTH                  1
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__MASK         0x00000200U
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__RESET                  0
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000200U) >> 9)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__WRITE(src) \
                    (((uint32_t)(src)\
                    << 9) & 0x00000200U)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | (((uint32_t)(src) <<\
                    9) & 0x00000200U)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 9) & ~0x00000200U)))
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(1) << 9)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000200U) | ((uint32_t)(0) << 9)

/* macros for field reserved_31_10 */
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__RESERVED_31_10__SHIFT               10
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__RESERVED_31_10__WIDTH               22
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__RESERVED_31_10__MASK       0xfffffc00U
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__RESERVED_31_10__RESET                0
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__RESERVED_31_10__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffffc00U) >> 10)
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__TYPE                          uint32_t
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__READ                       0xffffffffU
#define EMAC_REGS__TYPE2_COMPARE_WORD_1__WRITE                      0xffffffffU

#endif /* __EMAC_REGS__TYPE2_COMPARE_WORD_1_MACRO__ */


/* macros for type2_compare_0_word_1 */
#define INST_TYPE2_COMPARE_0_WORD_1__NUM                                      1

/* macros for type2_compare_1_word_0 */
#define INST_TYPE2_COMPARE_1_WORD_0__NUM                                      1

/* macros for type2_compare_1_word_1 */
#define INST_TYPE2_COMPARE_1_WORD_1__NUM                                      1

/* macros for type2_compare_2_word_0 */
#define INST_TYPE2_COMPARE_2_WORD_0__NUM                                      1

/* macros for type2_compare_2_word_1 */
#define INST_TYPE2_COMPARE_2_WORD_1__NUM                                      1

/* macros for type2_compare_3_word_0 */
#define INST_TYPE2_COMPARE_3_WORD_0__NUM                                      1

/* macros for type2_compare_3_word_1 */
#define INST_TYPE2_COMPARE_3_WORD_1__NUM                                      1

/* macros for type2_compare_4_word_0 */
#define INST_TYPE2_COMPARE_4_WORD_0__NUM                                      1

/* macros for type2_compare_4_word_1 */
#define INST_TYPE2_COMPARE_4_WORD_1__NUM                                      1

/* macros for type2_compare_5_word_0 */
#define INST_TYPE2_COMPARE_5_WORD_0__NUM                                      1

/* macros for type2_compare_5_word_1 */
#define INST_TYPE2_COMPARE_5_WORD_1__NUM                                      1

/* macros for type2_compare_6_word_0 */
#define INST_TYPE2_COMPARE_6_WORD_0__NUM                                      1

/* macros for type2_compare_6_word_1 */
#define INST_TYPE2_COMPARE_6_WORD_1__NUM                                      1

/* macros for type2_compare_7_word_0 */
#define INST_TYPE2_COMPARE_7_WORD_0__NUM                                      1

/* macros for type2_compare_7_word_1 */
#define INST_TYPE2_COMPARE_7_WORD_1__NUM                                      1

/* macros for type2_compare_8_word_0 */
#define INST_TYPE2_COMPARE_8_WORD_0__NUM                                      1

/* macros for type2_compare_8_word_1 */
#define INST_TYPE2_COMPARE_8_WORD_1__NUM                                      1

/* macros for type2_compare_9_word_0 */
#define INST_TYPE2_COMPARE_9_WORD_0__NUM                                      1

/* macros for type2_compare_9_word_1 */
#define INST_TYPE2_COMPARE_9_WORD_1__NUM                                      1

/* macros for type2_compare_10_word_0 */
#define INST_TYPE2_COMPARE_10_WORD_0__NUM                                     1

/* macros for type2_compare_10_word_1 */
#define INST_TYPE2_COMPARE_10_WORD_1__NUM                                     1

/* macros for type2_compare_11_word_0 */
#define INST_TYPE2_COMPARE_11_WORD_0__NUM                                     1

/* macros for type2_compare_11_word_1 */
#define INST_TYPE2_COMPARE_11_WORD_1__NUM                                     1

/* macros for type2_compare_12_word_0 */
#define INST_TYPE2_COMPARE_12_WORD_0__NUM                                     1

/* macros for type2_compare_12_word_1 */
#define INST_TYPE2_COMPARE_12_WORD_1__NUM                                     1

/* macros for type2_compare_13_word_0 */
#define INST_TYPE2_COMPARE_13_WORD_0__NUM                                     1

/* macros for type2_compare_13_word_1 */
#define INST_TYPE2_COMPARE_13_WORD_1__NUM                                     1

/* macros for type2_compare_14_word_0 */
#define INST_TYPE2_COMPARE_14_WORD_0__NUM                                     1

/* macros for type2_compare_14_word_1 */
#define INST_TYPE2_COMPARE_14_WORD_1__NUM                                     1

/* macros for type2_compare_15_word_0 */
#define INST_TYPE2_COMPARE_15_WORD_0__NUM                                     1

/* macros for type2_compare_15_word_1 */
#define INST_TYPE2_COMPARE_15_WORD_1__NUM                                     1

/* macros for type2_compare_16_word_0 */
#define INST_TYPE2_COMPARE_16_WORD_0__NUM                                     1

/* macros for type2_compare_16_word_1 */
#define INST_TYPE2_COMPARE_16_WORD_1__NUM                                     1

/* macros for type2_compare_17_word_0 */
#define INST_TYPE2_COMPARE_17_WORD_0__NUM                                     1

/* macros for type2_compare_17_word_1 */
#define INST_TYPE2_COMPARE_17_WORD_1__NUM                                     1

/* macros for type2_compare_18_word_0 */
#define INST_TYPE2_COMPARE_18_WORD_0__NUM                                     1

/* macros for type2_compare_18_word_1 */
#define INST_TYPE2_COMPARE_18_WORD_1__NUM                                     1

/* macros for type2_compare_19_word_0 */
#define INST_TYPE2_COMPARE_19_WORD_0__NUM                                     1

/* macros for type2_compare_19_word_1 */
#define INST_TYPE2_COMPARE_19_WORD_1__NUM                                     1

/* macros for type2_compare_20_word_0 */
#define INST_TYPE2_COMPARE_20_WORD_0__NUM                                     1

/* macros for type2_compare_20_word_1 */
#define INST_TYPE2_COMPARE_20_WORD_1__NUM                                     1

/* macros for type2_compare_21_word_0 */
#define INST_TYPE2_COMPARE_21_WORD_0__NUM                                     1

/* macros for type2_compare_21_word_1 */
#define INST_TYPE2_COMPARE_21_WORD_1__NUM                                     1

/* macros for type2_compare_22_word_0 */
#define INST_TYPE2_COMPARE_22_WORD_0__NUM                                     1

/* macros for type2_compare_22_word_1 */
#define INST_TYPE2_COMPARE_22_WORD_1__NUM                                     1

/* macros for type2_compare_23_word_0 */
#define INST_TYPE2_COMPARE_23_WORD_0__NUM                                     1

/* macros for type2_compare_23_word_1 */
#define INST_TYPE2_COMPARE_23_WORD_1__NUM                                     1

/* macros for type2_compare_24_word_0 */
#define INST_TYPE2_COMPARE_24_WORD_0__NUM                                     1

/* macros for type2_compare_24_word_1 */
#define INST_TYPE2_COMPARE_24_WORD_1__NUM                                     1

/* macros for type2_compare_25_word_0 */
#define INST_TYPE2_COMPARE_25_WORD_0__NUM                                     1

/* macros for type2_compare_25_word_1 */
#define INST_TYPE2_COMPARE_25_WORD_1__NUM                                     1

/* macros for type2_compare_26_word_0 */
#define INST_TYPE2_COMPARE_26_WORD_0__NUM                                     1

/* macros for type2_compare_26_word_1 */
#define INST_TYPE2_COMPARE_26_WORD_1__NUM                                     1

/* macros for type2_compare_27_word_0 */
#define INST_TYPE2_COMPARE_27_WORD_0__NUM                                     1

/* macros for type2_compare_27_word_1 */
#define INST_TYPE2_COMPARE_27_WORD_1__NUM                                     1

/* macros for type2_compare_28_word_0 */
#define INST_TYPE2_COMPARE_28_WORD_0__NUM                                     1

/* macros for type2_compare_28_word_1 */
#define INST_TYPE2_COMPARE_28_WORD_1__NUM                                     1

/* macros for type2_compare_29_word_0 */
#define INST_TYPE2_COMPARE_29_WORD_0__NUM                                     1

/* macros for type2_compare_29_word_1 */
#define INST_TYPE2_COMPARE_29_WORD_1__NUM                                     1

/* macros for type2_compare_30_word_0 */
#define INST_TYPE2_COMPARE_30_WORD_0__NUM                                     1

/* macros for type2_compare_30_word_1 */
#define INST_TYPE2_COMPARE_30_WORD_1__NUM                                     1

/* macros for type2_compare_31_word_0 */
#define INST_TYPE2_COMPARE_31_WORD_0__NUM                                     1

/* macros for type2_compare_31_word_1 */
#define INST_TYPE2_COMPARE_31_WORD_1__NUM                                     1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q8 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q8_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q8_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__SHIFT                 0
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__WIDTH                30
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__MASK        0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__SHIFT                 30
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__WIDTH                  2
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__MASK         0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__RESET                  0
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q8__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q8__TYPE                            uint32_t
#define EMAC_REGS__ENST_START_TIME_Q8__READ                         0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q8__WRITE                        0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q8_MACRO__ */


/* macros for enst_start_time_q8 */
#define INST_ENST_START_TIME_Q8__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q9 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q9_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q9_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__SHIFT                 0
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__WIDTH                30
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__MASK        0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__SHIFT                 30
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__WIDTH                  2
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__MASK         0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__RESET                  0
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q9__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q9__TYPE                            uint32_t
#define EMAC_REGS__ENST_START_TIME_Q9__READ                         0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q9__WRITE                        0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q9_MACRO__ */


/* macros for enst_start_time_q9 */
#define INST_ENST_START_TIME_Q9__NUM                                          1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q10 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q10_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q10_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__SHIFT                0
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__WIDTH               30
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__MASK       0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__RESET                0
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__SHIFT                30
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__WIDTH                 2
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__MASK        0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q10__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q10__TYPE                           uint32_t
#define EMAC_REGS__ENST_START_TIME_Q10__READ                        0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q10__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q10_MACRO__ */


/* macros for enst_start_time_q10 */
#define INST_ENST_START_TIME_Q10__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q11 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q11_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q11_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__SHIFT                0
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__WIDTH               30
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__MASK       0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__RESET                0
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__SHIFT                30
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__WIDTH                 2
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__MASK        0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q11__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q11__TYPE                           uint32_t
#define EMAC_REGS__ENST_START_TIME_Q11__READ                        0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q11__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q11_MACRO__ */


/* macros for enst_start_time_q11 */
#define INST_ENST_START_TIME_Q11__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q12 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q12_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q12_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__SHIFT                0
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__WIDTH               30
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__MASK       0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__RESET                0
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__SHIFT                30
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__WIDTH                 2
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__MASK        0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q12__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q12__TYPE                           uint32_t
#define EMAC_REGS__ENST_START_TIME_Q12__READ                        0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q12__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q12_MACRO__ */


/* macros for enst_start_time_q12 */
#define INST_ENST_START_TIME_Q12__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q13 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q13_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q13_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__SHIFT                0
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__WIDTH               30
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__MASK       0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__RESET                0
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__SHIFT                30
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__WIDTH                 2
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__MASK        0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q13__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q13__TYPE                           uint32_t
#define EMAC_REGS__ENST_START_TIME_Q13__READ                        0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q13__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q13_MACRO__ */


/* macros for enst_start_time_q13 */
#define INST_ENST_START_TIME_Q13__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q14 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q14_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q14_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__SHIFT                0
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__WIDTH               30
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__MASK       0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__RESET                0
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__SHIFT                30
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__WIDTH                 2
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__MASK        0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q14__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q14__TYPE                           uint32_t
#define EMAC_REGS__ENST_START_TIME_Q14__READ                        0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q14__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q14_MACRO__ */


/* macros for enst_start_time_q14 */
#define INST_ENST_START_TIME_Q14__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_start_time_q15 */
#ifndef __EMAC_REGS__ENST_START_TIME_Q15_MACRO__
#define __EMAC_REGS__ENST_START_TIME_Q15_MACRO__

/* macros for field start_time_nsec */
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__SHIFT                0
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__WIDTH               30
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__MASK       0x3fffffffU
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__RESET                0
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__READ(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x3fffffffU) | ((uint32_t)(src) &\
                    0x3fffffffU)
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_NSEC__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x3fffffffU)))

/* macros for field start_time_sec */
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__SHIFT                30
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__WIDTH                 2
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__MASK        0xc0000000U
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__RESET                 0
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__READ(src) \
                    (((uint32_t)(src)\
                    & 0xc0000000U) >> 30)
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__WRITE(src) \
                    (((uint32_t)(src)\
                    << 30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0xc0000000U) | (((uint32_t)(src) <<\
                    30) & 0xc0000000U)
#define EMAC_REGS__ENST_START_TIME_Q15__START_TIME_SEC__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 30) & ~0xc0000000U)))
#define EMAC_REGS__ENST_START_TIME_Q15__TYPE                           uint32_t
#define EMAC_REGS__ENST_START_TIME_Q15__READ                        0xffffffffU
#define EMAC_REGS__ENST_START_TIME_Q15__WRITE                       0xffffffffU

#endif /* __EMAC_REGS__ENST_START_TIME_Q15_MACRO__ */


/* macros for enst_start_time_q15 */
#define INST_ENST_START_TIME_Q15__NUM                                         1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q8 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q8_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q8_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__SHIFT                            0
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__WIDTH                           17
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__MASK                   0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__RESET                      0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q8__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q8__RESERVED_31_17__SHIFT                    17
#define EMAC_REGS__ENST_ON_TIME_Q8__RESERVED_31_17__WIDTH                    15
#define EMAC_REGS__ENST_ON_TIME_Q8__RESERVED_31_17__MASK            0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q8__RESERVED_31_17__RESET                     0
#define EMAC_REGS__ENST_ON_TIME_Q8__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q8__TYPE                               uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q8__READ                            0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q8__WRITE                           0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q8_MACRO__ */


/* macros for enst_on_time_q8 */
#define INST_ENST_ON_TIME_Q8__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q9 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q9_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q9_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__SHIFT                            0
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__WIDTH                           17
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__MASK                   0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__RESET                      0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q9__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q9__RESERVED_31_17__SHIFT                    17
#define EMAC_REGS__ENST_ON_TIME_Q9__RESERVED_31_17__WIDTH                    15
#define EMAC_REGS__ENST_ON_TIME_Q9__RESERVED_31_17__MASK            0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q9__RESERVED_31_17__RESET                     0
#define EMAC_REGS__ENST_ON_TIME_Q9__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q9__TYPE                               uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q9__READ                            0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q9__WRITE                           0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q9_MACRO__ */


/* macros for enst_on_time_q9 */
#define INST_ENST_ON_TIME_Q9__NUM                                             1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q10 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q10_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q10_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__SHIFT                           0
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__WIDTH                          17
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__MASK                  0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__RESET                     0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q10__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q10__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_ON_TIME_Q10__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_ON_TIME_Q10__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q10__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_ON_TIME_Q10__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q10__TYPE                              uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q10__READ                           0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q10__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q10_MACRO__ */


/* macros for enst_on_time_q10 */
#define INST_ENST_ON_TIME_Q10__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q11 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q11_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q11_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__SHIFT                           0
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__WIDTH                          17
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__MASK                  0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__RESET                     0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q11__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q11__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_ON_TIME_Q11__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_ON_TIME_Q11__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q11__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_ON_TIME_Q11__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q11__TYPE                              uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q11__READ                           0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q11__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q11_MACRO__ */


/* macros for enst_on_time_q11 */
#define INST_ENST_ON_TIME_Q11__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q12 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q12_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q12_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__SHIFT                           0
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__WIDTH                          17
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__MASK                  0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__RESET                     0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q12__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q12__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_ON_TIME_Q12__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_ON_TIME_Q12__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q12__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_ON_TIME_Q12__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q12__TYPE                              uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q12__READ                           0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q12__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q12_MACRO__ */


/* macros for enst_on_time_q12 */
#define INST_ENST_ON_TIME_Q12__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q13 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q13_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q13_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__SHIFT                           0
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__WIDTH                          17
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__MASK                  0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__RESET                     0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q13__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q13__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_ON_TIME_Q13__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_ON_TIME_Q13__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q13__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_ON_TIME_Q13__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q13__TYPE                              uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q13__READ                           0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q13__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q13_MACRO__ */


/* macros for enst_on_time_q13 */
#define INST_ENST_ON_TIME_Q13__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q14 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q14_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q14_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__SHIFT                           0
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__WIDTH                          17
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__MASK                  0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__RESET                     0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q14__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q14__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_ON_TIME_Q14__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_ON_TIME_Q14__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q14__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_ON_TIME_Q14__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q14__TYPE                              uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q14__READ                           0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q14__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q14_MACRO__ */


/* macros for enst_on_time_q14 */
#define INST_ENST_ON_TIME_Q14__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_on_time_q15 */
#ifndef __EMAC_REGS__ENST_ON_TIME_Q15_MACRO__
#define __EMAC_REGS__ENST_ON_TIME_Q15_MACRO__

/* macros for field on_time */
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__SHIFT                           0
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__WIDTH                          17
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__MASK                  0x0001ffffU
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__RESET                     0x1FFFF
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_ON_TIME_Q15__ON_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_ON_TIME_Q15__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_ON_TIME_Q15__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_ON_TIME_Q15__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_ON_TIME_Q15__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_ON_TIME_Q15__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_ON_TIME_Q15__TYPE                              uint32_t
#define EMAC_REGS__ENST_ON_TIME_Q15__READ                           0xffffffffU
#define EMAC_REGS__ENST_ON_TIME_Q15__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_ON_TIME_Q15_MACRO__ */


/* macros for enst_on_time_q15 */
#define INST_ENST_ON_TIME_Q15__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q8 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q8_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q8_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__SHIFT                          0
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__WIDTH                         17
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__MASK                 0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__RESET                          0
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q8__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q8__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_OFF_TIME_Q8__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_OFF_TIME_Q8__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q8__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_OFF_TIME_Q8__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q8__TYPE                              uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q8__READ                           0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q8__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q8_MACRO__ */


/* macros for enst_off_time_q8 */
#define INST_ENST_OFF_TIME_Q8__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q9 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q9_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q9_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__SHIFT                          0
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__WIDTH                         17
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__MASK                 0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__RESET                          0
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q9__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q9__RESERVED_31_17__SHIFT                   17
#define EMAC_REGS__ENST_OFF_TIME_Q9__RESERVED_31_17__WIDTH                   15
#define EMAC_REGS__ENST_OFF_TIME_Q9__RESERVED_31_17__MASK           0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q9__RESERVED_31_17__RESET                    0
#define EMAC_REGS__ENST_OFF_TIME_Q9__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q9__TYPE                              uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q9__READ                           0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q9__WRITE                          0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q9_MACRO__ */


/* macros for enst_off_time_q9 */
#define INST_ENST_OFF_TIME_Q9__NUM                                            1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q10 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q10_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q10_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__SHIFT                         0
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__WIDTH                        17
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__MASK                0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__RESET                         0
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q10__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q10__RESERVED_31_17__SHIFT                  17
#define EMAC_REGS__ENST_OFF_TIME_Q10__RESERVED_31_17__WIDTH                  15
#define EMAC_REGS__ENST_OFF_TIME_Q10__RESERVED_31_17__MASK          0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q10__RESERVED_31_17__RESET                   0
#define EMAC_REGS__ENST_OFF_TIME_Q10__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q10__TYPE                             uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q10__READ                          0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q10__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q10_MACRO__ */


/* macros for enst_off_time_q10 */
#define INST_ENST_OFF_TIME_Q10__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q11 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q11_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q11_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__SHIFT                         0
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__WIDTH                        17
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__MASK                0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__RESET                         0
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q11__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q11__RESERVED_31_17__SHIFT                  17
#define EMAC_REGS__ENST_OFF_TIME_Q11__RESERVED_31_17__WIDTH                  15
#define EMAC_REGS__ENST_OFF_TIME_Q11__RESERVED_31_17__MASK          0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q11__RESERVED_31_17__RESET                   0
#define EMAC_REGS__ENST_OFF_TIME_Q11__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q11__TYPE                             uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q11__READ                          0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q11__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q11_MACRO__ */


/* macros for enst_off_time_q11 */
#define INST_ENST_OFF_TIME_Q11__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q12 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q12_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q12_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__SHIFT                         0
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__WIDTH                        17
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__MASK                0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__RESET                         0
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q12__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q12__RESERVED_31_17__SHIFT                  17
#define EMAC_REGS__ENST_OFF_TIME_Q12__RESERVED_31_17__WIDTH                  15
#define EMAC_REGS__ENST_OFF_TIME_Q12__RESERVED_31_17__MASK          0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q12__RESERVED_31_17__RESET                   0
#define EMAC_REGS__ENST_OFF_TIME_Q12__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q12__TYPE                             uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q12__READ                          0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q12__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q12_MACRO__ */


/* macros for enst_off_time_q12 */
#define INST_ENST_OFF_TIME_Q12__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q13 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q13_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q13_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__SHIFT                         0
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__WIDTH                        17
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__MASK                0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__RESET                         0
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q13__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q13__RESERVED_31_17__SHIFT                  17
#define EMAC_REGS__ENST_OFF_TIME_Q13__RESERVED_31_17__WIDTH                  15
#define EMAC_REGS__ENST_OFF_TIME_Q13__RESERVED_31_17__MASK          0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q13__RESERVED_31_17__RESET                   0
#define EMAC_REGS__ENST_OFF_TIME_Q13__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q13__TYPE                             uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q13__READ                          0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q13__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q13_MACRO__ */


/* macros for enst_off_time_q13 */
#define INST_ENST_OFF_TIME_Q13__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q14 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q14_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q14_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__SHIFT                         0
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__WIDTH                        17
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__MASK                0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__RESET                         0
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q14__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q14__RESERVED_31_17__SHIFT                  17
#define EMAC_REGS__ENST_OFF_TIME_Q14__RESERVED_31_17__WIDTH                  15
#define EMAC_REGS__ENST_OFF_TIME_Q14__RESERVED_31_17__MASK          0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q14__RESERVED_31_17__RESET                   0
#define EMAC_REGS__ENST_OFF_TIME_Q14__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q14__TYPE                             uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q14__READ                          0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q14__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q14_MACRO__ */


/* macros for enst_off_time_q14 */
#define INST_ENST_OFF_TIME_Q14__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_off_time_q15 */
#ifndef __EMAC_REGS__ENST_OFF_TIME_Q15_MACRO__
#define __EMAC_REGS__ENST_OFF_TIME_Q15_MACRO__

/* macros for field off_time */
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__SHIFT                         0
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__WIDTH                        17
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__MASK                0x0001ffffU
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__RESET                         0
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__READ(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x0001ffffU) | ((uint32_t)(src) &\
                    0x0001ffffU)
#define EMAC_REGS__ENST_OFF_TIME_Q15__OFF_TIME__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x0001ffffU)))

/* macros for field reserved_31_17 */
#define EMAC_REGS__ENST_OFF_TIME_Q15__RESERVED_31_17__SHIFT                  17
#define EMAC_REGS__ENST_OFF_TIME_Q15__RESERVED_31_17__WIDTH                  15
#define EMAC_REGS__ENST_OFF_TIME_Q15__RESERVED_31_17__MASK          0xfffe0000U
#define EMAC_REGS__ENST_OFF_TIME_Q15__RESERVED_31_17__RESET                   0
#define EMAC_REGS__ENST_OFF_TIME_Q15__RESERVED_31_17__READ(src) \
                    (((uint32_t)(src)\
                    & 0xfffe0000U) >> 17)
#define EMAC_REGS__ENST_OFF_TIME_Q15__TYPE                             uint32_t
#define EMAC_REGS__ENST_OFF_TIME_Q15__READ                          0xffffffffU
#define EMAC_REGS__ENST_OFF_TIME_Q15__WRITE                         0xffffffffU

#endif /* __EMAC_REGS__ENST_OFF_TIME_Q15_MACRO__ */


/* macros for enst_off_time_q15 */
#define INST_ENST_OFF_TIME_Q15__NUM                                           1

/* macros for BlueprintGlobalNameSpace::emac_regs::enst_control */
#ifndef __EMAC_REGS__ENST_CONTROL_MACRO__
#define __EMAC_REGS__ENST_CONTROL_MACRO__

/* macros for field enst_enable_q8 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__SHIFT                        0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__WIDTH                        1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__MASK               0x00000001U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__RESET                        0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__READ(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__WRITE(src) \
                    ((uint32_t)(src)\
                    & 0x00000001U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | ((uint32_t)(src) &\
                    0x00000001U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__VERIFY(src) \
                    (!(((uint32_t)(src)\
                    & ~0x00000001U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(1)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q8__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000001U) | (uint32_t)(0)

/* macros for field enst_enable_q9 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__SHIFT                        1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__WIDTH                        1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__MASK               0x00000002U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__RESET                        0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000002U) >> 1)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__WRITE(src) \
                    (((uint32_t)(src)\
                    << 1) & 0x00000002U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | (((uint32_t)(src) <<\
                    1) & 0x00000002U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 1) & ~0x00000002U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(1) << 1)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q9__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000002U) | ((uint32_t)(0) << 1)

/* macros for field enst_enable_q10 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__SHIFT                       2
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__MASK              0x00000004U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000004U) >> 2)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__WRITE(src) \
                    (((uint32_t)(src)\
                    << 2) & 0x00000004U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | (((uint32_t)(src) <<\
                    2) & 0x00000004U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 2) & ~0x00000004U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(1) << 2)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q10__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000004U) | ((uint32_t)(0) << 2)

/* macros for field enst_enable_q11 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__SHIFT                       3
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__MASK              0x00000008U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000008U) >> 3)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__WRITE(src) \
                    (((uint32_t)(src)\
                    << 3) & 0x00000008U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | (((uint32_t)(src) <<\
                    3) & 0x00000008U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 3) & ~0x00000008U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(1) << 3)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q11__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000008U) | ((uint32_t)(0) << 3)

/* macros for field enst_enable_q12 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__SHIFT                       4
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__MASK              0x00000010U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000010U) >> 4)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__WRITE(src) \
                    (((uint32_t)(src)\
                    << 4) & 0x00000010U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | (((uint32_t)(src) <<\
                    4) & 0x00000010U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 4) & ~0x00000010U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(1) << 4)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q12__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000010U) | ((uint32_t)(0) << 4)

/* macros for field enst_enable_q13 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__SHIFT                       5
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__MASK              0x00000020U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000020U) >> 5)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__WRITE(src) \
                    (((uint32_t)(src)\
                    << 5) & 0x00000020U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | (((uint32_t)(src) <<\
                    5) & 0x00000020U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 5) & ~0x00000020U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(1) << 5)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q13__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000020U) | ((uint32_t)(0) << 5)

/* macros for field enst_enable_q14 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__SHIFT                       6
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__MASK              0x00000040U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000040U) >> 6)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__WRITE(src) \
                    (((uint32_t)(src)\
                    << 6) & 0x00000040U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | (((uint32_t)(src) <<\
                    6) & 0x00000040U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 6) & ~0x00000040U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(1) << 6)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q14__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000040U) | ((uint32_t)(0) << 6)

/* macros for field enst_enable_q15 */
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__SHIFT                       7
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__MASK              0x00000080U
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__READ(src) \
                    (((uint32_t)(src)\
                    & 0x00000080U) >> 7)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__WRITE(src) \
                    (((uint32_t)(src)\
                    << 7) & 0x00000080U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | (((uint32_t)(src) <<\
                    7) & 0x00000080U)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 7) & ~0x00000080U)))
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(1) << 7)
#define EMAC_REGS__ENST_CONTROL__ENST_ENABLE_Q15__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00000080U) | ((uint32_t)(0) << 7)

/* macros for field reserved_15_8 */
#define EMAC_REGS__ENST_CONTROL__RESERVED_15_8__SHIFT                         8
#define EMAC_REGS__ENST_CONTROL__RESERVED_15_8__WIDTH                         8
#define EMAC_REGS__ENST_CONTROL__RESERVED_15_8__MASK                0x0000ff00U
#define EMAC_REGS__ENST_CONTROL__RESERVED_15_8__RESET                         0
#define EMAC_REGS__ENST_CONTROL__RESERVED_15_8__READ(src) \
                    (((uint32_t)(src)\
                    & 0x0000ff00U) >> 8)

/* macros for field enst_disable_q8 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__SHIFT                      16
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__MASK              0x00010000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__WRITE(src) \
                    (((uint32_t)(src)\
                    << 16) & 0x00010000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | (((uint32_t)(src) <<\
                    16) & 0x00010000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 16) & ~0x00010000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(1) << 16)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q8__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00010000U) | ((uint32_t)(0) << 16)

/* macros for field enst_disable_q9 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__SHIFT                      17
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__WIDTH                       1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__MASK              0x00020000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__RESET                       0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__WRITE(src) \
                    (((uint32_t)(src)\
                    << 17) & 0x00020000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | (((uint32_t)(src) <<\
                    17) & 0x00020000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 17) & ~0x00020000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(1) << 17)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q9__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00020000U) | ((uint32_t)(0) << 17)

/* macros for field enst_disable_q10 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__SHIFT                     18
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__WIDTH                      1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__MASK             0x00040000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__RESET                      0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__WRITE(src) \
                    (((uint32_t)(src)\
                    << 18) & 0x00040000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | (((uint32_t)(src) <<\
                    18) & 0x00040000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 18) & ~0x00040000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(1) << 18)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q10__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00040000U) | ((uint32_t)(0) << 18)

/* macros for field enst_disable_q11 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__SHIFT                     19
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__WIDTH                      1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__MASK             0x00080000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__RESET                      0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__WRITE(src) \
                    (((uint32_t)(src)\
                    << 19) & 0x00080000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | (((uint32_t)(src) <<\
                    19) & 0x00080000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 19) & ~0x00080000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(1) << 19)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q11__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00080000U) | ((uint32_t)(0) << 19)

/* macros for field enst_disable_q12 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__SHIFT                     20
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__WIDTH                      1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__MASK             0x00100000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__RESET                      0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__WRITE(src) \
                    (((uint32_t)(src)\
                    << 20) & 0x00100000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | (((uint32_t)(src) <<\
                    20) & 0x00100000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 20) & ~0x00100000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(1) << 20)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q12__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00100000U) | ((uint32_t)(0) << 20)

/* macros for field enst_disable_q13 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__SHIFT                     21
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__WIDTH                      1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__MASK             0x00200000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__RESET                      0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__WRITE(src) \
                    (((uint32_t)(src)\
                    << 21) & 0x00200000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | (((uint32_t)(src) <<\
                    21) & 0x00200000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 21) & ~0x00200000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(1) << 21)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q13__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00200000U) | ((uint32_t)(0) << 21)

/* macros for field enst_disable_q14 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__SHIFT                     22
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__WIDTH                      1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__MASK             0x00400000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__RESET                      0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__WRITE(src) \
                    (((uint32_t)(src)\
                    << 22) & 0x00400000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | (((uint32_t)(src) <<\
                    22) & 0x00400000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 22) & ~0x00400000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(1) << 22)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q14__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00400000U) | ((uint32_t)(0) << 22)

/* macros for field enst_disable_q15 */
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__SHIFT                     23
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__WIDTH                      1
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__MASK             0x00800000U
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__RESET                      0
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__WRITE(src) \
                    (((uint32_t)(src)\
                    << 23) & 0x00800000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__MODIFY(dst, src) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | (((uint32_t)(src) <<\
                    23) & 0x00800000U)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__VERIFY(src) \
                    (!((((uint32_t)(src)\
                    << 23) & ~0x00800000U)))
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__SET(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(1) << 23)
#define EMAC_REGS__ENST_CONTROL__ENST_DISABLE_Q15__CLR(dst) \
                    (dst) = ((dst) &\
                    ~0x00800000U) | ((uint32_t)(0) << 23)

/* macros for field reserved_31_24 */
#define EMAC_REGS__ENST_CONTROL__RESERVED_31_24__SHIFT                       24
#define EMAC_REGS__ENST_CONTROL__RESERVED_31_24__WIDTH                        8
#define EMAC_REGS__ENST_CONTROL__RESERVED_31_24__MASK               0xff000000U
#define EMAC_REGS__ENST_CONTROL__RESERVED_31_24__RESET                        0
#define EMAC_REGS__ENST_CONTROL__RESERVED_31_24__READ(src) \
                    (((uint32_t)(src)\
                    & 0xff000000U) >> 24)
#define EMAC_REGS__ENST_CONTROL__TYPE                                  uint32_t
#define EMAC_REGS__ENST_CONTROL__READ                               0xff00ffffU
#define EMAC_REGS__ENST_CONTROL__WRITE                              0xff00ffffU

#endif /* __EMAC_REGS__ENST_CONTROL_MACRO__ */


/* macros for enst_control */
#define INST_ENST_CONTROL__NUM                                                1

#endif /* __REG_EMAC_REGS_MACRO_H__ */
