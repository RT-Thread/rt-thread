/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#ifndef ETHERNET_PHY_MAIN_H
#define ETHERNET_PHY_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include <ethernet_phy.h>

extern struct ethernet_phy_descriptor MACIF_PHY_desc;

void ethernet_phys_init(void);
void MACIF_PHY_example(void);

/**
 * \brief Ethernet PHY devices
 */
void ethernet_phys_init(void);

#ifdef __cplusplus
}
#endif

#endif /* ETHERNET_PHY_MAIN_H */
