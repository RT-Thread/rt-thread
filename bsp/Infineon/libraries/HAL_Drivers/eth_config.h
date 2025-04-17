#ifndef CY_ETH_USER_CONFIG
#define CY_ETH_USER_CONFIG

#include "cy_ethif.h"
#include "cy_ephy.h"
/*#include "cy_ecm.h"*/

#define CY_GIG_ETH_TYPE                        ETH1
#define CY_GIG_ETH_INSTANCE_NUM                (1)

#define ETH_REG_BASE                           CY_GIG_ETH_TYPE

#define CY_GIG_ETH_TX_CLK_PORT                 GPIO_PRT26
#define CY_GIG_ETH_TX_CLK_PIN                  2
#define CY_GIG_ETH_TX_CLK_PIN_MUX              P26_2_ETH1_TX_CLK

#define CY_GIG_ETH_TX_CTL_PORT                 GPIO_PRT26
#define CY_GIG_ETH_TX_CTL_PIN                  1
#define CY_GIG_ETH_TX_CTL_PIN_MUX              P26_1_ETH1_TX_CTL

#define CY_GIG_ETH_TD0_PORT                    GPIO_PRT26
#define CY_GIG_ETH_TD0_PIN                     3
#define CY_GIG_ETH_TD0_PIN_MUX                 P26_3_ETH1_TXD0

#define CY_GIG_ETH_TD1_PORT                    GPIO_PRT26
#define CY_GIG_ETH_TD1_PIN                     4
#define CY_GIG_ETH_TD1_PIN_MUX                 P26_4_ETH1_TXD1

#define CY_GIG_ETH_TD2_PORT                    GPIO_PRT26
#define CY_GIG_ETH_TD2_PIN                     5
#define CY_GIG_ETH_TD2_PIN_MUX                 P26_5_ETH1_TXD2

#define CY_GIG_ETH_TD3_PORT                    GPIO_PRT26
#define CY_GIG_ETH_TD3_PIN                     6
#define CY_GIG_ETH_TD3_PIN_MUX                 P26_6_ETH1_TXD3

#define CY_GIG_ETH_RX_CLK_PORT                 GPIO_PRT27
#define CY_GIG_ETH_RX_CLK_PIN                  4
#define CY_GIG_ETH_RX_CLK_PIN_MUX              P27_4_ETH1_RX_CLK

#define CY_GIG_ETH_RX_CTL_PORT                 GPIO_PRT27
#define CY_GIG_ETH_RX_CTL_PIN                  3
#define CY_GIG_ETH_RX_CTL_PIN_MUX              P27_3_ETH1_RX_CTL

#define CY_GIG_ETH_RD0_PORT                    GPIO_PRT26
#define CY_GIG_ETH_RD0_PIN                     7
#define CY_GIG_ETH_RD0_PIN_MUX                 P26_7_ETH1_RXD0

#define CY_GIG_ETH_RD1_PORT                    GPIO_PRT27
#define CY_GIG_ETH_RD1_PIN                     0
#define CY_GIG_ETH_RD1_PIN_MUX                 P27_0_ETH1_RXD1

#define CY_GIG_ETH_RD2_PORT                    GPIO_PRT27
#define CY_GIG_ETH_RD2_PIN                     1
#define CY_GIG_ETH_RD2_PIN_MUX                 P27_1_ETH1_RXD2

#define CY_GIG_ETH_RD3_PORT                    GPIO_PRT27
#define CY_GIG_ETH_RD3_PIN                     2
#define CY_GIG_ETH_RD3_PIN_MUX                 P27_2_ETH1_RXD3

#define CY_GIG_ETH_MDC_PORT                    GPIO_PRT27
#define CY_GIG_ETH_MDC_PIN                     6
#define CY_GIG_ETH_MDC_PIN_MUX                 P27_6_ETH1_MDC

#define CY_GIG_ETH_MDIO_PORT                   GPIO_PRT27
#define CY_GIG_ETH_MDIO_PIN                    5
#define CY_GIG_ETH_MDIO_PIN_MUX                P27_5_ETH1_MDIO

#define CY_GIG_ETH_REF_CLK_PORT                GPIO_PRT26
#define CY_GIG_ETH_REF_CLK_PIN                 0
#define CY_GIG_ETH_REF_CLK_PIN_MUX             P26_0_ETH1_REF_CLK

/* Setup IRQ source for 0, 1, and 2 priority queue */
#define CY_GIG_ETH_IRQN0                       eth_1_interrupt_eth_0_IRQn
#define CY_GIG_ETH_IRQN1                       eth_1_interrupt_eth_1_IRQn
#define CY_GIG_ETH_IRQN2                       eth_1_interrupt_eth_2_IRQn

#endif /* CY_ETH_USER_CONFIG */
