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
#include <string.h>
#include "hal_emac.h"
#include "ethernet_phy.h"

/* LAN8720 PHY Address*/
#define EMAC_PHY_ADDRESS          0x00U
#define PHY_LINK_TO               ((uint32_t)0x00000FFFU)
#define PHY_AUTONEGO_COMPLETED_TO ((uint32_t)0x00000FFFU)
/* Section 3: Common PHY Registers */
#define PHY_BCR                     ((uint16_t)0x00U) /*!< Transceiver Basic Control Register   */
#define PHY_BSR                     ((uint16_t)0x01U) /*!< Transceiver Basic Status Register    */
#define PHY_BSR_100BASETXFULL       (1 << 14)
#define PHY_BSR_100BASETXHALF       (1 << 13)
#define PHY_BSR_10BASETXFULL        (1 << 12)
#define PHY_BSR_10BASETXHALF        (1 << 11)
#define PHY_RESET                   ((uint16_t)0x8000U) /*!< PHY Reset */
#define PHY_LOOPBACK                ((uint16_t)0x4000U) /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M         ((uint16_t)0x2100U) /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M         ((uint16_t)0x2000U) /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M          ((uint16_t)0x0100U) /*!< Set the full-duplex mode at 10 Mb/s  */
#define PHY_HALFDUPLEX_10M          ((uint16_t)0x0000U) /*!< Set the half-duplex mode at 10 Mb/s  */
#define PHY_AUTONEGOTIATION         ((uint16_t)0x1000U) /*!< Enable auto-negotiation function     */
#define PHY_RESTART_AUTONEGOTIATION ((uint16_t)0x0200U) /*!< Restart auto-negotiation function    */
#define PHY_POWERDOWN               ((uint16_t)0x0800U) /*!< Select the power down mode           */
#define PHY_ISOLATE                 ((uint16_t)0x0400U) /*!< Isolate PHY from MII                 */
#define PHY_AUTONEGO_COMPLETE       ((uint16_t)0x0020U) /*!< Auto-Negotiation process completed   */
#define PHY_LINKED_STATUS           ((uint16_t)0x0004U) /*!< Valid link established               */
#define PHY_JABBER_DETECTION        ((uint16_t)0x0002U) /*!< Jabber condition detected            */

#define PHY_PHYID1                  ((uint16_t)0x02U) /*!< PHY ID 1    */
#define PHY_PHYID2                  ((uint16_t)0x03U) /*!< PHY ID 2    */
#define PHY_ADVERTISE               ((uint16_t)0x04U) /*!< Auto-negotiation advertisement       */
#define PHY_ADVERTISE_100BASETXFULL (1 << 8)
#define PHY_ADVERTISE_100BASETXHALF (1 << 7)
#define PHY_ADVERTISE_10BASETXFULL  (1 << 6)
#define PHY_ADVERTISE_10BASETXHALF  (1 << 5)
#define PHY_ADVERTISE_8023          (1 << 0)
#define PHY_LPA                     ((uint16_t)0x05U) /*!< Auto-negotiation link partner base page ability    */
#define PHY_EXPANSION               ((uint16_t)0x06U) /*!< Auto-negotiation expansion           */
/* Section 4: Extended PHY Registers */
#define PHY_CTRL_STATUS           ((uint16_t)17U) /*!< PHY MODE CONTROL/STATUS REGISTER Offset     */
#define PHY_CTRL_STATUS_EDPWRDOWN (1 << 13)       /*!< EDPWRDOWN */
#define PHY_CTRL_STATUS_ENERGYON  (1 << 1)        /*!< ENERGYON */

#define PHY_SPECIAL_MODES              ((uint16_t)18U) /*!< PHY SPECIAL MODES REGISTER Offset     */
#define PHY_SPECIAL_MODES_MODE         (7 << 5)        /*!< Transceiver mode of operation */
#define PHY_SPECIAL_MODES_MODE_PWRDOWN (6 << 5)        /*!< All capable. Auto-negotiation enabled */
#define PHY_SPECIAL_MODES_MODE_ALL     (7 << 5)        /*!< All capable. Auto-negotiation enabled */
#define PHY_SPECIAL_MODES_PHYAD        (0x1F << 0)     /*!< PHY Address */

#define PHY_SR                                  ((uint16_t)0x1FU) /*!< PHY special control/ status register Offset     */
#define PHY_SR_SPEED_OFFSET                     (2)
#define PHY_SR_SPEED_MASK                       (0x7 << PHY_SR_SPEED_OFFSET)
#define PHY_SR_SPEED_10BASETXHALF               (0x1 << PHY_SR_SPEED_OFFSET)
#define PHY_SR_SPEED_10BASETXFULL               (0x5 << PHY_SR_SPEED_OFFSET)
#define PHY_SR_SPEED_100BASETXHALF              (0x2 << PHY_SR_SPEED_OFFSET)
#define PHY_SR_SPEED_100BASETXFULL              (0x6 << PHY_SR_SPEED_OFFSET)
#define PHY_SR_SPEED_MODE_COMPARE(status, mode) (!!(mode == (status & PHY_SR_SPEED_MASK)))
#define PHY_SPEED_STATUS                        ((uint16_t)0x0004U) /*!< PHY Speed mask                                  */
#define PHY_DUPLEX_STATUS                       ((uint16_t)0x0010U) /*!< PHY Duplex mask                                 */
#define PHY_ISFR                                ((uint16_t)0x1DU)   /*!< PHY Interrupt Source Flag register Offset       */
#define PHY_ISFR_INT4                           ((uint16_t)0x0010U) /*!< PHY Link down inturrupt                         */

static emac_phy_cfg_t *phy_8720_cfg = NULL;

int phy_8720_reset(void)
{
    int timeout = 1000;
    uint16_t regval = PHY_RESET;

    /* pull the PHY from power down mode if it is in */
    if (0 != emac_phy_reg_read(PHY_SPECIAL_MODES, &regval)) {
        return -1;
    }

    if (PHY_SPECIAL_MODES_MODE_PWRDOWN == (regval & PHY_SPECIAL_MODES_MODE)) {
        if (emac_phy_reg_write(PHY_SPECIAL_MODES, regval | PHY_SPECIAL_MODES_MODE_ALL) != 0) {
            return -1;
        }
    }

    /* disable energy detect powerdown mode for cable detect, this increase the power by 220mW */
    if (0 != emac_phy_reg_read(PHY_CTRL_STATUS, &regval)) {
        return -1;
    }

    if (emac_phy_reg_write(PHY_CTRL_STATUS, regval & (~PHY_CTRL_STATUS_EDPWRDOWN)) != 0) {
        return -1;
    }

    /* do sw reset */
    if (emac_phy_reg_write(PHY_BCR, PHY_RESET) != 0) {
        return -1;
    }

    for (; timeout; timeout--) {
        if (0 != emac_phy_reg_read(PHY_BCR, &regval)) {
            return -1;
        }

        if (!(regval & PHY_RESET)) {
            return 0;
        }

        arch_delay_ms(1);
    }

    return -1;
}

int phy_8720_auto_negotiate(emac_phy_cfg_t *cfg)
{
    uint16_t regval = 0;
    uint16_t phyid1 = 0, phyid2 = 0;
    uint16_t advertise = 0;
    uint16_t lpa = 0;
    uint32_t timeout = 100; //10s,in 100ms

    if (0 != emac_phy_reg_read(PHY_PHYID1, &phyid1)) {
        // MSG("read emac phy id 1 error\r\n");
        return -1;
    }

    if (0 != emac_phy_reg_read(PHY_PHYID2, &phyid2)) {
        MSG("read emac phy id 2 error\r\n");
        return -1;
    }
    MSG("emac phy id 1 =%08x\r\n",(unsigned int )phyid1);
    MSG("emac phy id 2 =%08x\r\n",(unsigned int )phyid2);
    if (cfg->phy_id != (((phyid1 << 16) | phyid2) & 0x000FFFF0)) {
        /* ID error */
        return -1;
    } else {
        cfg->phy_id = (phyid1 << 16) | phyid2;
    }

    if (0 != emac_phy_reg_read(PHY_BCR, &regval)) {
        return -1;
    }

    regval &= ~PHY_AUTONEGOTIATION;
    regval &= ~(PHY_LOOPBACK | PHY_POWERDOWN);
    regval |= PHY_ISOLATE;

    if (emac_phy_reg_write(PHY_BCR, regval) != 0) {
        return -1;
    }

    /* set advertisement mode */
    advertise = PHY_ADVERTISE_100BASETXFULL | PHY_ADVERTISE_100BASETXHALF |
                PHY_ADVERTISE_10BASETXFULL | PHY_ADVERTISE_10BASETXHALF |
                PHY_ADVERTISE_8023;

    if (emac_phy_reg_write(PHY_ADVERTISE, advertise) != 0) {
        return -1;
    }

    arch_delay_ms(16);

    if (0 != emac_phy_reg_read(PHY_BCR, &regval)) {
        return -1;
    }

    arch_delay_ms(16);
    regval |= (PHY_FULLDUPLEX_100M | PHY_AUTONEGOTIATION);

    if (emac_phy_reg_write(PHY_BCR, regval) != 0) {
        return -1;
    }

    arch_delay_ms(16);
    regval |= PHY_RESTART_AUTONEGOTIATION;
    regval &= ~PHY_ISOLATE;

    if (emac_phy_reg_write(PHY_BCR, regval) != 0) {
        return -1;
    }

    arch_delay_ms(100);

    while (1) {
        if (0 != emac_phy_reg_read(PHY_BSR, &regval)) {
            return -1;
        }

        if (regval & PHY_AUTONEGO_COMPLETE) {
            /* complete */
            break;
        }

        if (!(--timeout)) {
            return -1;
        }

        arch_delay_ms(100);
    }

    arch_delay_ms(100);

    if (0 != emac_phy_reg_read(PHY_LPA, &lpa)) {
        return -1;
    }

    if (((advertise & lpa) & PHY_ADVERTISE_100BASETXFULL) != 0) {
        /* 100BaseTX and Full Duplex */
        cfg->full_duplex = 1;
        cfg->speed = 100;
        cfg->phy_state = PHY_STATE_READY;
    } else if (((advertise & lpa) & PHY_ADVERTISE_10BASETXFULL) != 0) {
        /* 10BaseT and Full Duplex */
        cfg->full_duplex = 1;
        cfg->speed = 10;
        cfg->phy_state = PHY_STATE_READY;
    } else if (((advertise & lpa) & PHY_ADVERTISE_100BASETXHALF) != 0) {
        /* 100BaseTX and half Duplex */
        cfg->full_duplex = 0;
        cfg->speed = 100;
        cfg->phy_state = PHY_STATE_READY;
    } else if (((advertise & lpa) & PHY_ADVERTISE_10BASETXHALF) != 0) {
        /* 10BaseT and half Duplex */
        cfg->full_duplex = 0;
        cfg->speed = 10;
        cfg->phy_state = PHY_STATE_READY;
    }

    return 0;
}

int phy_8720_link_up(emac_phy_cfg_t *cfg)
{
    uint16_t phy_bsr = 0;
    uint16_t phy_sr = 0;

    arch_delay_ms(16);

    if (0 != emac_phy_reg_read(PHY_BSR, &phy_bsr)) {
        return -1;
    }

    arch_delay_ms(16);

    if (!(PHY_LINKED_STATUS & phy_bsr)) {
        return ERROR;
    }

    arch_delay_ms(16);

    if (0 != emac_phy_reg_read(PHY_SR, &phy_sr)) {
        return -1;
    }

    if ((phy_bsr & PHY_BSR_100BASETXFULL) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_100BASETXFULL)) {
        /* 100BaseTX and Full Duplex */
        cfg->full_duplex = 1;
        cfg->speed = 100;
        cfg->phy_state = PHY_STATE_UP;
    } else if ((phy_bsr & PHY_BSR_10BASETXFULL) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_10BASETXFULL)) {
        /* 10BaseT and Full Duplex */
        cfg->full_duplex = 1;
        cfg->speed = 10;
        cfg->phy_state = PHY_STATE_UP;
    } else if ((phy_bsr & PHY_BSR_100BASETXHALF) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_100BASETXHALF)) {
        /* 100BaseTX and half Duplex */
        cfg->full_duplex = 0;
        cfg->speed = 100;
        cfg->phy_state = PHY_STATE_UP;
    } else if ((phy_bsr & PHY_BSR_10BASETXHALF) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_10BASETXHALF)) {
        /* 10BaseT and half Duplex */
        cfg->full_duplex = 0;
        cfg->speed = 10;
        cfg->phy_state = PHY_STATE_UP;
    } else {
        /* 10BaseT and half Duplex */
        cfg->full_duplex = -1;
        cfg->speed = -1;
        cfg->phy_state = PHY_STATE_DOWN;
        return -1;
    }

    return 0;
}

/******************************************************************************
 * @brief  Use energy detector for cable plug in/out detect.
 *
 * @param  cfg: EMAC PHY configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
int phy_8720_poll_cable_status(emac_phy_cfg_t *cfg)
{
    uint16_t phy_regval = 0;

    CHECK_PARAM(NULL != phy_8720_cfg);

    if (0 != emac_phy_reg_read(PHY_CTRL_STATUS, &phy_regval)) {
        return -1;
    }

    phy_8720_cfg->phy_state = (PHY_CTRL_STATUS_ENERGYON & phy_regval) ?
                                  PHY_STATE_UP :
                                  PHY_STATE_DOWN;

    return !!(PHY_CTRL_STATUS_ENERGYON & phy_regval);
}

/****************************************************************************/ /**
 * @brief  Initialize EMAC PHY module
 *
 * @param  cfg: EMAC PHY configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
int emac_phy_init(emac_phy_cfg_t *cfg)
{
    uint16_t phyReg;

    CHECK_PARAM(NULL != cfg);

    phy_8720_cfg = cfg;

    emac_phy_set_address(cfg->phy_address);

    if (0 != phy_8720_reset()) {
        return -1;
    }

    if (cfg->auto_negotiation) {
        /*
        uint32_t cnt=0;
        do{
            if(emac_phy_reg_read(PHY_BSR, &phyReg) != SUCCESS){
                return ERROR;
            }
            cnt++;
            if(cnt>PHY_LINK_TO){
                return ERROR;
            }
        }while((phyReg & PHY_LINKED_STATUS) != PHY_LINKED_STATUS);
        */
        if (0 != phy_8720_auto_negotiate(cfg)) {
            return -1;
        }
    } else {
        if (emac_phy_reg_read(PHY_BCR, &phyReg) != 0) {
            return -1;
        }

        phyReg &= (~PHY_FULLDUPLEX_100M);

        if (cfg->speed == 10) {
            if (cfg->full_duplex == 1) {
                phyReg |= PHY_FULLDUPLEX_10M;
            } else {
                phyReg |= PHY_HALFDUPLEX_10M;
            }
        } else {
            if (cfg->full_duplex == 1) {
                phyReg |= PHY_FULLDUPLEX_100M;
            } else {
                phyReg |= PHY_HALFDUPLEX_100M;
            }
        }

        if ((emac_phy_reg_write(PHY_BCR, phyReg)) != 0) {
            return -1;
        }
    }

    emac_phy_config_full_duplex(cfg->full_duplex);

    return phy_8720_link_up(cfg);
}

emac_phy_status_t ethernet_phy_status_get()
{
    CHECK_PARAM(NULL != phy_8720_cfg);

    if ((100 == phy_8720_cfg->speed) &&
        (phy_8720_cfg->full_duplex) &&
        (PHY_STATE_UP == phy_8720_cfg->phy_state)) {
        return EMAC_PHY_STAT_100MBITS_FULLDUPLEX;
    } else if (PHY_STATE_UP == phy_8720_cfg->phy_state) {
        return EMAC_PHY_STAT_LINK_UP;
    } else {
        return EMAC_PHY_STAT_LINK_DOWN;
    }
}
