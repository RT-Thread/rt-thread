#ifndef __APP_PHY_H
#define __APP_PHY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7_includes.h"

#define PHY_SPEED_10                    0x0         /*!< SPEED : 10M  */
#define PHY_SPEED_100                   0x1         /*!< SPEED : 100M  */
#define PHY_SPEED_1000                  0x2         /*!< SPEED : 1000M  */

#define PHY_DUPLEX_HALF                 0x0         /*!< DUPLEX : half  */
#define PHY_DUPLEX_FULL                 0x1         /*!< DUPLEX : full  */

void phy_Reset(void);
void phy_AutoNeg(void);
BOOL phy_IsLink(void);
BOOL phy_PartnerCanAutoNeg(void);
uint32_t phy_GetSpeed(void);
uint32_t phy_GetDuplex(void);
BOOL phy_Init(void);

#ifdef __cplusplus
}
#endif

#endif



