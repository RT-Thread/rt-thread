////////////////////////////////////////////////////////////////////////////////
/// @file     reg_iwdg.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_ETH_H
#define __REG_ETH_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

#include "reg_common.h"


#if defined ( __CC_ARM )
#pragma anon_unions
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief IWDG Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_BASE                       (AHBPERIPH_BASE + 0x8000)              ///< Base Address: 0x40028000


#define ETH                             ((ETH_TypeDef*) ETH_BASE)
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 MACCR;                                                        ///< configuration register                         offset 0x0000
    __IO u32 MACFFR;                                                       ///< frame filter register                          offset 0x0004
    __IO u32 MACHTHR;                                                      ///< Hash list high register                        offset 0x0008
    __IO u32 MACHTLR;                                                      ///< Hash list low register                         offset 0x000C
    __IO u32 MACMIIAR;                                                     ///< MII address register                           offset 0x0010
    __IO u32 MACMIIDR;                                                     ///< MII data register                              offset 0x0014
    __IO u32 MACFCR;                                                       ///< flow control register                          offset 0x0018
    __IO u32 MACVLANTR;                                                    ///< VLAN label register                            offset 0x001C
    __IO u32 RESERVEDX0020[2];                                             /// 0x0020 ~ 0x0024
    __IO u32 MACRWUFFR;                                                    /// 0x0028
    __IO u32 MACPMTCSR;                                                    /// 0x002C
    __IO u32 RESERVEDX0030[4];                                             /// 0x0030 ~ 0x003C
    __IO u32 MACA0HR;                                                      ///< address 0 high register                        offset 0x0040
    __IO u32 MACA0LR;                                                      ///< address 0 low register                         offset 0x0044
    __IO u32 MACA1HR;                                                      ///< address 1 high register                        offset 0x0048
    __IO u32 MACA1LR;                                                      ///< address 1 low register                         offset 0x004C
    __IO u32 MACA2HR;                                                      ///< address 2 high register                        offset 0x0050
    __IO u32 MACA2LR;                                                      ///< address 2 low register                         offset 0x0054
    __IO u32 MACA3HR;                                                      ///< address 3 high register                        offset 0x0058
    __IO u32 MACA3LR;                                                      ///< address 3 low register                         offset 0x005C
    __IO u32 MACA4HR;                                                      ///< address 4 high register                        offset 0x0060
    __IO u32 MACA4LR;                                                      ///< address 4 low register                         offset 0x0064
    __IO u32 MACA5HR;                                                      ///< address 5 high register                        offset 0x0068
    __IO u32 MACA5LR;                                                      ///< address 5 low register                         offset 0x006C
    __IO u32 MACA6HR;                                                      ///< address 6 high register                        offset 0x0070
    __IO u32 MACA6LR;                                                      ///< address 6 low register                         offset 0x0074
    __IO u32 MACA7HR;                                                      ///< address 7 high register                        offset 0x0078
    __IO u32 MACA7LR;                                                      ///< address 7 low register                         offset 0x007C
    __IO u32 MACA8HR;                                                      ///< address 8 high register                        offset 0x0080
    __IO u32 MACA8LR;                                                      ///< address 8 low register                         offset 0x0084
    __IO u32 MACA9HR;                                                      ///< address 9 high register                        offset 0x0088
    __IO u32 MACA9LR;                                                      ///< address 9 low register                         offset 0x008C
    __IO u32 MACA10HR;                                                     ///< address 10 high register                        offset 0x0090
    __IO u32 MACA10LR;                                                     ///< address 10 low register                         offset 0x0094
    __IO u32 MACA11HR;                                                     ///< address 11 high register                        offset 0x0098
    __IO u32 MACA11LR;                                                     ///< address 11 low register                         offset 0x009C
    __IO u32 MACA12HR;                                                     ///< address 12 high register                        offset 0x00A0
    __IO u32 MACA12LR;                                                     ///< address 12 low register                         offset 0x00A4
    __IO u32 MACA13HR;                                                     ///< address 13 high register                        offset 0x00A8
    __IO u32 MACA13LR;                                                     ///< address 13 low register                         offset 0x00AC
    __IO u32 MACA14HR;                                                     ///< address 14 high register                        offset 0x00B0
    __IO u32 MACA14LR;                                                     ///< address 14 low register                         offset 0x00B4
    __IO u32 MACA15HR;                                                     ///< address 15 high register                        offset 0x00B8
    __IO u32 MACA15LR;                                                     ///< address 15 low register                         offset 0x00BC
    __IO u32 MACANCR;                                                      ///< Automatic negotiation control register           offset 0x00C0
    __IO u32 MACANSR;                                                      ///< Automatic negotiation of the status register     offset 0x00C4
    __IO u32 MACANAR;                                                      ///< Automatic negotiation of broadcast registers     offset 0x00C8
    __IO u32 MACANLPAR;                                                    ///< Automatic negotiation of link partner capability register  offset 0x00CC
    __IO u32 MACANER;                                                      ///< Automatic negotiation of extension registers     offset 0x00D0
    __IO u32 MACTBIER;                                                     ///< Ten - place interface extension register         offset 0x00D4
    __IO u32 MACMIISR;                                                     ///< MII status register                              offset 0x00D8
    __IO u32 RESERVEDX00DC[9];                                             ///<                                                  offset 0x00DC ~ 0x00FC
    __IO u32 MMCCR;                                                        ///< MMC controls registers  offset 0x0100
    __IO u32 MMCRIR;                                                       ///< The MMC receives the interrupt register  offset 0x0104
    __IO u32 MMCTIR;                                                       ///< The MMC sends the interrupt register  offset 0x0108
    __IO u32 MMCRIMR;                                                      ///< The MMC receives the interrupt mask register  offset 0x010C
    __IO u32 MMCTIMR;                                                      ///< MMC sends interrupt masking registers  offset 0x0110
    __IO u32 RESERVEDX0114[14];                                            ///<   offset 0x0114 ~ 0x0148
    __IO u32 MMCTGFSCCR;                                                   ///< A good frame counter register that MMC sends after a single conflict  offset 0x014C
    __IO u32 MMCTGFMSCCR;                                                  ///< A good frame counter register that MMC sends after multiple collisions  offset 0x0150
    __IO u32 RESERVEDX0154[5];                                             ///<   offset 0x0154 ~ 0x0164
    __IO u32 MMCTGFCR;                                                     ///< Good frame counter register sent by MMC  offset 0x0168
    __IO u32 RESERVEDX016C[10];                                            ///<   offset 0x016C ~ 0x0190
    __IO u32 MMCRFCECR;                                                    ///< Ethernet MMC with CRC error counter register receives frame register  offset 0x0194
    __IO u32 MMCRFAECR;                                                    ///< Ethernet MMC receives frames with alignment error counter registers  offset 0x0198
    __IO u32 RESERVEDX019C[10];                                            ///<   offset 0x019C ~ 0x01C0
    __IO u32 MMCRGUFCR;                                                    ///< Good unicast frame counter register received by MMC  offset 0x01C4
    __IO u32 RESERVEDx01C8[910];                                           ///<   offset 0x01C8 ~ 0x0FFC
    __IO u32 DMABMR;                                                       ///< Bus mode register                               offset 0x1000
    __IO u32 DMATPDR;                                                      ///< DMA sends the polling request register          offset 0x1004
    __IO u32 DMARPDR;                                                      ///< DMA receives the polling request register       offset 0x1008
    __IO u32 DMARDLAR;                                                     ///< DMA receives a list of descriptor addresses     offset 0x100C
    __IO u32 DMATDLAR;                                                     ///< DMA sends the descriptor list address           offset 0x1010
    __IO u32 DMASR;                                                        ///< DMA status register                             offset 0x1014
    __IO u32 DMAOMR;                                                       ///< DMA working mode register                       offset 0x1018
    __IO u32 DMAIER;                                                       ///< DMA interrupt enablement register               offset 0x101C
    __IO u32 DMAMFBOCR;                                                    ///< DMA lost frames and cache overflow counter registers offset 0x1020
    __IO u32 DMARSWTR;                                                     /// 0x1024
    __IO u32 RESERVEDX1028[8];                                             /// 0x1028 ~ 0x1044
    __IO u32 DMACHTDR;                                                     /// 0x1048
    __IO u32 DMACHRDR;                                                     /// 0x104C
    __IO u32 DMACHTBAR;                                                    ///< DMA is currently sending the cache address register  offset 0x1050
    __IO u32 DMACHRBAR;                                                    ///< DMA currently receives the cache address register    offset 0x1054
} ETH_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACCR_WD_Pos                (23)
#define ETH_MACCR_WD                    (0x01U << ETH_MACCR_WD_Pos)                  ///< Watchdog disable
#define ETH_MACCR_JD_Pos                (22)
#define ETH_MACCR_JD                    (0x01U << ETH_MACCR_JD_Pos)                  ///< Jabber disable
#define ETH_MACCR_FBE_Pos               (21)
#define ETH_MACCR_FBE                   (0x01U << ETH_MACCR_FBE_Pos)                 ///< Frame Burst Enable
#define ETH_MACCR_JE_Pos                (20)
#define ETH_MACCR_JE                    (0x01U << ETH_MACCR_JE_Pos)                  ///< Jumbo Frame Enable
#define ETH_MACCR_IFG_Pos               (17)                                         ///< Inter-frame gap
#define ETH_MACCR_IFG_96Bit             (0x00U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 96Bit
#define ETH_MACCR_IFG_88Bit             (0x01U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 88Bit
#define ETH_MACCR_IFG_80Bit             (0x02U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 80Bit
#define ETH_MACCR_IFG_72Bit             (0x03U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 72Bit
#define ETH_MACCR_IFG_64Bit             (0x04U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 64Bit
#define ETH_MACCR_IFG_56Bit             (0x05U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 56Bit
#define ETH_MACCR_IFG_48Bit             (0x06U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 48Bit
#define ETH_MACCR_IFG_40Bit             (0x07U << ETH_MACCR_IFG_Pos)                 ///< Minimum IFG between frames during transmission is 40Bit
#define ETH_MACCR_FES_Pos               (14)
#define ETH_MACCR_FES                   (0x01U << ETH_MACCR_FES_Pos)                  ///< Fast ethernet speed
#define ETH_MACCR_ROD_Pos               (13)
#define ETH_MACCR_ROD                   (0x01U << ETH_MACCR_ROD_Pos)                  ///< Receive own disable
#define ETH_MACCR_LM_Pos                (12)
#define ETH_MACCR_LM                    (0x01U << ETH_MACCR_LM_Pos)                   ///< loopback mode
#define ETH_MACCR_DM_Pos                (11)
#define ETH_MACCR_DM                    (0x01U << ETH_MACCR_DM_Pos)                   ///< Duplex mode
#define ETH_MACCR_IPCO_Pos              (10)
#define ETH_MACCR_IPCO                  (0x01U << ETH_MACCR_IPCO_Pos)                 ///< IP Checksum offload
#define ETH_MACCR_RD_Pos                (9)
#define ETH_MACCR_RD                    (0x01U << ETH_MACCR_RD_Pos)                   ///< Retry disable
#define ETH_MACCR_APCS_Pos              (8)
#define ETH_MACCR_APCS                  (0x01U << ETH_MACCR_APCS_Pos)                 ///< Automatic Pad/CRC stripping
#define ETH_MACCR_BL_Pos                (5)                                           ///< Back-off limit: random integer number (r) of slot time delays before rescheduling a transmission attempt during retries after a collision: 0 =< r <2^k
#define ETH_MACCR_BL_10                 (0x00U << ETH_MACCR_BL_Pos)                   ///< k = min (n, 10)
#define ETH_MACCR_BL_8                  (0x01U << ETH_MACCR_BL_Pos)                   ///< k = min (n, 8)
#define ETH_MACCR_BL_4                  (0x02U << ETH_MACCR_BL_Pos)                   ///< k = min (n, 4)
#define ETH_MACCR_BL_1                  (0x03U << ETH_MACCR_BL_Pos)                   ///< k = min (n, 1)
#define ETH_MACCR_DC_Pos                (4)
#define ETH_MACCR_DC                    (0x01U << ETH_MACCR_DC_Pos)                  ///< Defferal check
#define ETH_MACCR_TE_Pos                (3)
#define ETH_MACCR_TE                    (0x01U << ETH_MACCR_TE_Pos)                  ///< Transmitter enable
#define ETH_MACCR_RE_Pos                (2)
#define ETH_MACCR_RE                    (0x01U << ETH_MACCR_RE_Pos)                  ///< Receiver enable
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACFFR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACFFR_RA_Pos               (31)
#define ETH_MACFFR_RA                   (0x01U << ETH_MACFFR_RA_Pos)                  ///< Receive all 

#define ETH_MACFFR_SAF_Pos              (9)
#define ETH_MACFFR_SAF                  (0x01U << ETH_MACFFR_SAF_Pos)                  ///< Source address filter enable 
#define ETH_MACFFR_SAIF_Pos             (8)
#define ETH_MACFFR_SAIF                 (0x01U << ETH_MACFFR_SAIF_Pos)                 ///< SA inverse filtering 
#define ETH_MACFFR_PCF_Pos              (6)
#define ETH_MACFFR_PCF                  (0x03U << ETH_MACFFR_PCF_Pos)                  ///< Pass control frames: 3 cases 
#define ETH_MACFFR_PCF_BlockAll         (0x01U << ETH_MACFFR_PCF_Pos)                  ///< MAC filters all control frames from reaching the application 
#define ETH_MACFFR_PCF_ForwardAll       (0x02U << ETH_MACFFR_PCF_Pos)                  ///< MAC forwards all control frames to application even if they fail the Address Filter 
#define ETH_MACFFR_PCF_ForwardPassedAddrFilter (0x03U << ETH_MACFFR_PCF_Pos)           ///< MAC forwards control frames that pass the Address Filter. 
#define ETH_MACFFR_BFD_Pos              (5)
#define ETH_MACFFR_BFD                  (0x01U << ETH_MACFFR_BFD_Pos)                  ///< Broadcast frame disable 
#define ETH_MACFFR_PAM_Pos              (4)
#define ETH_MACFFR_PAM                  (0x01U << ETH_MACFFR_PAM_Pos)                  ///< Pass all mutlicast 
#define ETH_MACFFR_DAIF_Pos             (3)
#define ETH_MACFFR_DAIF                 (0x01U << ETH_MACFFR_DAIF_Pos)                 ///< DA Inverse filtering 
#define ETH_MACFFR_HM_Pos               (2)
#define ETH_MACFFR_HM                   (0x01U << ETH_MACFFR_HM_Pos)                  ///< Hash multicast 
#define ETH_MACFFR_HU_Pos               (1)
#define ETH_MACFFR_HU                   (0x01U << ETH_MACFFR_HU_Pos)                  ///< Hash unicast 
#define ETH_MACFFR_PM_Pos               (0)
#define ETH_MACFFR_PM                   (0x01U << ETH_MACFFR_PM_Pos)                  ///< Promiscuous mode 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACHTHR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACHTHR_HTH                 (0xFFFFFFFFU)                                 ///< Hash table high

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACHTLR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACHTLR_HTL                 (0xFFFFFFFFU)                                ///< Hash table low

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACMIIAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACMIIAR_PA_Pos             (11)
#define ETH_MACMIIAR_PA                 (0x1FU << ETH_MACMIIAR_PA_Pos)              ///< Physical layer address
#define ETH_MACMIIAR_MR_Pos             (6)
#define ETH_MACMIIAR_MR                 (0x1FU << ETH_MACMIIAR_MR_Pos)              ///< MII register in the selected PHY
#define ETH_MACMIIAR_CR_Pos             (2)
#define ETH_MACMIIAR_CR                 (0x07U << ETH_MACMIIAR_CR_Pos)              ///< CR clock range: 6 cases
#define ETH_MACMIIAR_CR_Div42           (0x00U << ETH_MACMIIAR_CR_Pos)              ///< HCLK:60-100 MHz; MDC clock= HCLK/42
#define ETH_MACMIIAR_CR_Div62           (0x01U << ETH_MACMIIAR_CR_Pos)              ///< HCLK:100-150 MHz; MDC clock= HCLK/62
#define ETH_MACMIIAR_CR_Div16           (0x02U << ETH_MACMIIAR_CR_Pos)              ///< HCLK:20-35 MHz; MDC clock= HCLK/16
#define ETH_MACMIIAR_CR_Div26           (0x03U << ETH_MACMIIAR_CR_Pos)              ///< HCLK:35-60 MHz; MDC clock= HCLK/26
#define ETH_MACMIIAR_CR_Div102          (0x04U << ETH_MACMIIAR_CR_Pos)              ///< HCLK:150-168 MHz; MDC clock= HCLK/102
#define ETH_MACMIIAR_MW_Pos             (1)
#define ETH_MACMIIAR_MW                 (0x01U << ETH_MACMIIAR_MW_Pos)              ///< MII write
#define ETH_MACMIIAR_MB_Pos             (0)
#define ETH_MACMIIAR_MB                 (0x01U << ETH_MACMIIAR_MB_Pos)              ///< MII busy

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACMIIDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACMIIDR_MD                 (0x0000FFFFU)                               ///< MII data: read/write data from/to PHY 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACFCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACFCR_PT_Pos               (16)
#define ETH_MACFCR_PT                   ((u32)0xFFFF << ETH_MACFCR_PT_Pos) ///< Pause time
#define ETH_MACFCR_PLT_Pos              (4)
#define ETH_MACFCR_PLT                  (0x03U << ETH_MACFCR_PLT_Pos)                  ///< Pause low threshold: 4 cases 
#define ETH_MACFCR_PLT_Minus4           (0x00U << ETH_MACFCR_PLT_Pos)                  ///< Pause time minus 4 slot times 
#define ETH_MACFCR_PLT_Minus28          (0x01U << ETH_MACFCR_PLT_Pos)                  ///< Pause time minus 28 slot times 
#define ETH_MACFCR_PLT_Minus144         (0x02U << ETH_MACFCR_PLT_Pos)                  ///< Pause time minus 144 slot times 
#define ETH_MACFCR_PLT_Minus256         (0x03U << ETH_MACFCR_PLT_Pos)                  ///< Pause time minus 256 slot times 
#define ETH_MACFCR_UPFD_Pos             (3)
#define ETH_MACFCR_UPFD                 (0x01U << ETH_MACFCR_UPFD_Pos)                  ///< Unicast pause frame detect 
#define ETH_MACFCR_RFCE_Pos             (2)
#define ETH_MACFCR_RFCE                 (0x01U << ETH_MACFCR_RFCE_Pos)                  ///< Receive flow control enable 
#define ETH_MACFCR_TFCE_Pos             (1)
#define ETH_MACFCR_TFCE                 (0x01U << ETH_MACFCR_TFCE_Pos)                  ///< Transmit flow control enable 
#define ETH_MACFCR_FCBBPA_Pos           (0)
#define ETH_MACFCR_FCBBPA               (0x01U << ETH_MACFCR_FCBBPA_Pos)                ///< Flow control busy/backpressure activate 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACVLANTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACVLANTR_VLANTI            (0x0000FFFFU)                                  ///< VLAN tag identifier (for receive frames) 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACRWUFFR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACRWUFFR_D                 (0xFFFFFFFFU)                                  ///< Wake-up frame filter register data 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACPMTCSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACPMTCSR_WFFRPR_Pos        (31)                                     ///< Wake-Up Frame Filter Register Pointer Reset
#define ETH_MACPMTCSR_WFFRPR            (0x01U << ETH_MACPMTCSR_WFFRPR_Pos)                  ///< Wake-Up Frame Filter Register Pointer Reset
#define ETH_MACPMTCSR_GU_Pos            (9)
#define ETH_MACPMTCSR_GU                (0x01U << ETH_MACPMTCSR_GU_Pos)                   ///< Global Unicast 
#define ETH_MACPMTCSR_WFR_Pos           (6)
#define ETH_MACPMTCSR_WFR               (0x01U << ETH_MACPMTCSR_WFR_Pos)                  ///< Wake-Up Frame Received 
#define ETH_MACPMTCSR_MPR_Pos           (5)
#define ETH_MACPMTCSR_MPR               (0x01U << ETH_MACPMTCSR_MPR_Pos)                  ///< Magic Packet Received 
#define ETH_MACPMTCSR_WFE_Pos           (2)
#define ETH_MACPMTCSR_WFE               (0x01U << ETH_MACPMTCSR_WFE_Pos)                  ///< Wake-Up Frame Enable 
#define ETH_MACPMTCSR_MPE_Pos           (1)
#define ETH_MACPMTCSR_MPE               (0x01U << ETH_MACPMTCSR_MPE_Pos)                  ///< Magic Packet Enable 
#define ETH_MACPMTCSR_PD_Pos            (0)
#define ETH_MACPMTCSR_PD                (0x01U << ETH_MACPMTCSR_PD_Pos)                  ///< Power Down 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACA0HR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACA0HR_MACA0H              ((u32)0x0000FFFF)                  ///< MAC address0 high 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACA0LR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACA0LR_MACA0L              ((u32)0xFFFFFFFF)                  ///< MAC address0 low 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACA1HR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACA1HR_AE_Pos              (31)
#define ETH_MACA1HR_AE                  (0x01U << ETH_MACA1HR_AE_Pos)                  ///< Address enable 
#define ETH_MACA1HR_SA_Pos              (30)
#define ETH_MACA1HR_SA                  (0x01U << ETH_MACA1HR_SA_Pos)                  ///< Source address 
#define ETH_MACA1HR_MBC_Pos             (24)
#define ETH_MACA1HR_MBC                 (0x3FU << ETH_MACA1HR_MBC_Pos)                  ///< Mask byte control: bits to mask for comparison of the MAC Address bytes 
#define ETH_MACA1HR_MBC_HBits15_8       (0x20U << ETH_MACA1HR_MBC_Pos)                  ///< Mask MAC Address high reg bits [15:8] 
#define ETH_MACA1HR_MBC_HBits7_0        (0x10U << ETH_MACA1HR_MBC_Pos)                  ///< Mask MAC Address high reg bits [7:0] 
#define ETH_MACA1HR_MBC_LBits31_24      (0x08U << ETH_MACA1HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [31:24] 
#define ETH_MACA1HR_MBC_LBits23_16      (0x04U << ETH_MACA1HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [23:16] 
#define ETH_MACA1HR_MBC_LBits15_8       (0x02U << ETH_MACA1HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [15:8] 
#define ETH_MACA1HR_MBC_LBits7_0        (0x00U << ETH_MACA1HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [7:0] 
#define ETH_MACA1HR_MACA1H_Pos          (0)
#define ETH_MACA1HR_MACA1H              (0x0000FFFFU << ETH_MACA1HR_MACA1H_Pos)         ///< MAC address1 high 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACA1LR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACA1LR_MACA1L              (0xFFFFFFFFU)                                  ///< MAC address1 low 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACA2HR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACA2HR_AE_Pos              (31)
#define ETH_MACA2HR_AE                  (0x01U << ETH_MACA2HR_AE_Pos)                  ///< Address enable 
#define ETH_MACA2HR_SA_Pos              (30)
#define ETH_MACA2HR_SA                  (0x01U << ETH_MACA2HR_SA_Pos)                  ///< Source address 
#define ETH_MACA2HR_MBC_Pos             (24)
#define ETH_MACA2HR_MBC                 (0x3FU << ETH_MACA2HR_MBC_Pos)                  ///< Mask byte control: bits to mask for comparison of the MAC Address bytes 
#define ETH_MACA2HR_MBC_HBits15_8       (0x20U << ETH_MACA2HR_MBC_Pos)                  ///< Mask MAC Address high reg bits [15:8] 
#define ETH_MACA2HR_MBC_HBits7_0        (0x10U << ETH_MACA2HR_MBC_Pos)                  ///< Mask MAC Address high reg bits [7:0] 
#define ETH_MACA2HR_MBC_LBits31_24      (0x08U << ETH_MACA2HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [31:24] 
#define ETH_MACA2HR_MBC_LBits23_16      (0x04U << ETH_MACA2HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [23:16] 
#define ETH_MACA2HR_MBC_LBits15_8       (0x02U << ETH_MACA2HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [15:8] 
#define ETH_MACA2HR_MBC_LBits7_0        (0x00U << ETH_MACA2HR_MBC_Pos)                  ///< Mask MAC Address low reg bits [7:0] 
#define ETH_MACA2HR_MACA2H_Pos          (0)
#define ETH_MACA2HR_MACA2H              (0x0000FFFFU << ETH_MACA2HR_MACA2H_Pos)         ///< MAC address2 high 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACA2LR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACA2LR_MACA2L              (0xFFFFFFFFU)                                  ///< MAC address2 low 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACANCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACANCR_LR_Pos              (17)
#define ETH_MACANCR_LR                  (0x01U << ETH_MACANCR_LR_Pos)                   ///< Lock to Reference
#define ETH_MACANCR_ECD_Pos             (16)
#define ETH_MACANCR_ECD                 (0x01U << ETH_MACANCR_ECD_Pos)                  ///< Enable Comma Detect 
#define ETH_MACANCR_ELE_Pos             (14)
#define ETH_MACANCR_ELE                 (0x01U << ETH_MACANCR_ELE_Pos)                  ///< External Loopback Enable
#define ETH_MACANCR_ANE_Pos             (12)
#define ETH_MACANCR_ANE                 (0x01U << ETH_MACANCR_ANE_Pos)                  ///< Auto-Negotiation Enable 
#define ETH_MACANCR_RAN_Pos             (9)
#define ETH_MACANCR_RAN                 (0x01U << ETH_MACANCR_RAN_Pos)                  ///< Restart Auto-Negotiation 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACANSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACANSR_ES_Pos              (8)
#define ETH_MACANSR_ES                  (0x01U << ETH_MACANSR_ES_Pos)                   ///< Extended Status
#define ETH_MACANSR_ANC_Pos             (5)
#define ETH_MACANSR_ANC                 (0x01U << ETH_MACANSR_ANC_Pos)                  ///< Auto-Negotiation Complete 
#define ETH_MACANSR_ANA_Pos             (3)
#define ETH_MACANSR_ANA                 (0x01U << ETH_MACANSR_ANA_Pos)                  ///< Auto-Negotiation Ability
#define ETH_MACANSR_LS_Pos              (2)
#define ETH_MACANSR_LS                  (0x01U << ETH_MACANSR_LS_Pos)                  ///< Link Status 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACANAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACANAR_NP_Pos              (15)
#define ETH_MACANAR_NP                  (0x01U << ETH_MACANAR_NP_Pos)                   ///< Next Page Support
#define ETH_MACANAR_RFE_Pos             (12)
#define ETH_MACANAR_RFE                 (0x01U << ETH_MACANAR_RFE_Pos)                  ///< Remote Fault Encoding
#define ETH_MACANAR_PSE_Pos             (7)
#define ETH_MACANAR_PSE                 (0x01U << ETH_MACANAR_PSE_Pos)                  ///< Pause Encoding
#define ETH_MACANAR_HD_Pos              (6)
#define ETH_MACANAR_HD                  (0x01U << ETH_MACANAR_HD_Pos)                  ///< support Half-Duplex 
#define ETH_MACANAR_FD_Pos              (5)
#define ETH_MACANAR_FD                  (0x01U << ETH_MACANAR_FD_Pos)                  ///< support Full-Durplex 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACANLPAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACANLPAR_NP_Pos              (15)
#define ETH_MACANLPAR_NP                  (0x01U << ETH_MACANLPAR_NP_Pos)                   ///< Next Page Support
#define ETH_MACANLPAR_ACK_Pos             (14)
#define ETH_MACANLPAR_ACK                 (0x01U << ETH_MACANLPAR_ACK_Pos)                ///< Acknowledge
#define ETH_MACANLPAR_RFE_Pos             (12)
#define ETH_MACANLPAR_RFE                 (0x01U << ETH_MACANLPAR_RFE_Pos)                  ///< Remote Fault Encoding
#define ETH_MACANLPAR_PSE_Pos             (7)
#define ETH_MACANLPAR_PSE                 (0x01U << ETH_MACANLPAR_PSE_Pos)                  ///< Pause Encoding
#define ETH_MACANLPAR_HD_Pos              (6)
#define ETH_MACANLPAR_HD                  (0x01U << ETH_MACANLPAR_HD_Pos)                  ///< support Half-Duplex 
#define ETH_MACANLPAR_FD_Pos              (5)
#define ETH_MACANLPAR_FD                  (0x01U << ETH_MACANLPAR_FD_Pos)                  ///< support Full-Durplex 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACANER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACANER_NPA_Pos              (2)
#define ETH_MACANER_NPA                  (0x01U << ETH_MACANER_NPA_Pos)                   ///< Next Page Ability
#define ETH_MACANER_NPR_Pos              (1)
#define ETH_MACANER_NPR                  (0x01U << ETH_MACANER_NPR_Pos)                   ///< New Page Received
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACTBIER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACTBIER_GFD_Pos              (15)
#define ETH_MACTBIER_GFD                  (0x01U << ETH_MACTBIER_GFD_Pos)                   ///< 1000BASE-X Full-Duplex Capable
#define ETH_MACTBIER_GHD_Pos              (14)
#define ETH_MACTBIER_GHD                  (0x01U << ETH_MACTBIER_GHD_Pos)                   ///< 1000BASE-X Half-Duplex Capable
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MACMIISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MACMIISR_LS_Pos               (3)
#define ETH_MACMIISR_LS                   (0x01U << ETH_MACMIISR_LS_Pos)                   ///< Link Status
#define ETH_MACMIISR_LSP_Pos              (1)
#define ETH_MACMIISR_LSP_2_5              (0x00U << ETH_MACMIISR_LSP_Pos)                   ///< Link Speed 2.5 MHz
#define ETH_MACMIISR_LSP_25               (0x01U << ETH_MACMIISR_LSP_Pos)                   ///< Link Speed 25  MHz
#define ETH_MACMIISR_LSP_125              (0x02U << ETH_MACMIISR_LSP_Pos)                   ///< Link Speed 125 MHz
#define ETH_MACMIISR_LM_Pos               (0)
#define ETH_MACMIISR_LM                   (0x01U << ETH_MACMIISR_LM_Pos)                   ///< Link Mode : Full-Duplex Capable

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCCR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCCR_MCFHP                 ((u32)0x00000020)                  ///< MMC counter Full-Half preset
#define ETH_MMCCR_MCP                   ((u32)0x00000010)                  ///< MMC counter preset
#define ETH_MMCCR_MCF                   ((u32)0x00000008)                  ///< MMC Counter Freeze
#define ETH_MMCCR_ROR_Pos               (2)
#define ETH_MMCCR_ROR                   (0x01U << ETH_MMCCR_ROR_Pos)                  ///< Reset on Read 
#define ETH_MMCCR_CSR_Pos               (1)
#define ETH_MMCCR_CSR                   (0x01U << ETH_MMCCR_CSR_Pos)                  ///< Counter Stop Rollover 
#define ETH_MMCCR_CR_Pos                (0)
#define ETH_MMCCR_CR                    (0x01U << ETH_MMCCR_CR_Pos)                  ///< Counters Reset 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCRIR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCRIR_RGUF_Pos             (17)
#define ETH_MMCRIR_RGUFS                (0x01U << ETH_MMCRIR_RGUF_Pos)                  ///< Set when Rx good unicast frames counter reaches half the maximum value 
#define ETH_MMCRIR_RFAES_Pos            (6)
#define ETH_MMCRIR_RFAES                (0x01U << ETH_MMCRIR_RFAES_Pos)                 ///< Set when Rx alignment error counter reaches half the maximum value 
#define ETH_MMCRIR_RFCES_Pos            (5)
#define ETH_MMCRIR_RFCES                (0x01U << ETH_MMCRIR_RFCES_Pos)                 ///< Set when Rx crc error counter reaches half the maximum value 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCTIR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCTIR_TGFS_Pos             (21)
#define ETH_MMCTIR_TGFS                 (0x01U << ETH_MMCTIR_TGFS_Pos)                  ///< Set when Tx good frame count counter reaches half the maximum value 
#define ETH_MMCTIR_TGFMSCS_Pos          (15)
#define ETH_MMCTIR_TGFMSCS              (0x01U << ETH_MMCTIR_TGFMSCS_Pos)               ///< Set when Tx good multi col counter reaches half the maximum value 
#define ETH_MMCTIR_TGFSCS_Pos           (14)
#define ETH_MMCTIR_TGFSCS               (0x01U << ETH_MMCTIR_TGFSCS_Pos)                ///< Set when Tx good single col counter reaches half the maximum value 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCRIMR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCRIMR_RGUFM_Pos            (17)
#define ETH_MMCRIMR_RGUFM                (0x01U << ETH_MMCRIMR_RGUFM_Pos)                ///< Mask the interrupt when Rx good unicast frames counter reaches half the maximum value 
#define ETH_MMCRIMR_RFAEM_Pos            (6)
#define ETH_MMCRIMR_RFAEM                (0x01U << ETH_MMCRIMR_RFAEM_Pos)                ///< Mask the interrupt when when Rx alignment error counter reaches half the maximum value 
#define ETH_MMCRIMR_RFCEM_Pos            (5)
#define ETH_MMCRIMR_RFCEM                (0x01U << ETH_MMCRIMR_RFCEM_Pos)                ///< Mask the interrupt when Rx crc error counter reaches half the maximum value 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCTIMR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCTIMR_TGFM_Pos             (21)
#define ETH_MMCTIMR_TGFM                 (0x01U << ETH_MMCTIMR_TGFM_Pos)                  ///< Mask the interrupt when Tx good frame count counter reaches half the maximum value 
#define ETH_MMCTIMR_TGFMSCM_Pos          (15)
#define ETH_MMCTIMR_TGFMSCM              (0x01U << ETH_MMCTIMR_TGFMSCM_Pos)               ///< Mask the interrupt when Tx good multi col counter reaches half the maximum value 
#define ETH_MMCTIMR_TGFSCM_Pos           (14)
#define ETH_MMCTIMR_TGFSCM               (0x01U << ETH_MMCTIMR_TGFSCM_Pos)                ///< Mask the interrupt when Tx good single col counter reaches half the maximum value 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCTGFSCCR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCTGFSCCR_TGFSCC           (0xFFFFFFFFU)                                     ///< Number of successfully transmitted frames after a single collision in Half-duplex mode. 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCTGFMSCCR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCTGFMSCCR_TGFMSCC         (0xFFFFFFFFU)                                    ///< Number of successfully transmitted frames after more than a single collision in Half-duplex mode. 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCTGFCR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCTGFCR_TGFC               (0xFFFFFFFFU)                                    ///< Number of good frames transmitted. 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCRFCECR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCRFCECR_RFCEC             (0xFFFFFFFFU)                                    ///< Number of frames received with CRC error. 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCRFAECR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCRFAECR_RFAEC             (0xFFFFFFFFU)                                   ///< Number of frames received with alignment (dribble) error 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_MMCRGUFCR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_MMCRGUFCR_RGUFC             (0xFFFFFFFFU)                                  ///< Number of good unicast frames received. 
/// @brief ETH_DMABMR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMABMR_FB_Pos               (16)
#define ETH_DMABMR_FB                   (0x01U << ETH_DMABMR_FB_Pos)            ///< Fixed Burst 
#define ETH_DMABMR_RTPR_Pos             (14)
#define ETH_DMABMR_RTPR                 (0x03U << ETH_DMABMR_RTPR_Pos)          ///< Rx Tx priority ratio 
#define ETH_DMABMR_RTPR_1_1             (0x00U << ETH_DMABMR_RTPR_Pos)          ///< Rx Tx priority ratio 
#define ETH_DMABMR_RTPR_2_1             (0x01U << ETH_DMABMR_RTPR_Pos)          ///< Rx Tx priority ratio 
#define ETH_DMABMR_RTPR_3_1             (0x02U << ETH_DMABMR_RTPR_Pos)          ///< Rx Tx priority ratio 
#define ETH_DMABMR_RTPR_4_1             (0x03U << ETH_DMABMR_RTPR_Pos)          ///< Rx Tx priority ratio 
#define ETH_DMABMR_PBL_Pos              (8)
#define ETH_DMABMR_PBL                  (0x3FU<< ETH_DMABMR_PBL_Pos)            //< Programmable burst length 
#define ETH_DMABMR_PBL_1Beat            (0x01U << ETH_DMABMR_PBL_Pos)           ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 1 
#define ETH_DMABMR_PBL_2Beat            (0x02U << ETH_DMABMR_PBL_Pos)           ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 2 
#define ETH_DMABMR_PBL_4Beat            (0x04U << ETH_DMABMR_PBL_Pos)           ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 
#define ETH_DMABMR_PBL_8Beat            (0x08U << ETH_DMABMR_PBL_Pos)           ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 
#define ETH_DMABMR_PBL_16Beat           (0x10U << ETH_DMABMR_PBL_Pos)           ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 
#define ETH_DMABMR_PBL_32Beat           (0x20U << ETH_DMABMR_PBL_Pos)           ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 
#define ETH_DMABMR_PBL_4xPBL_4Beat      (0x10001U << ETH_DMABMR_PBL_Pos)        ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 4 
#define ETH_DMABMR_PBL_4xPBL_8Beat      (0x10002U << ETH_DMABMR_PBL_Pos)        ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 8 
#define ETH_DMABMR_PBL_4xPBL_16Beat     (0x10004U << ETH_DMABMR_PBL_Pos)        ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 16 
#define ETH_DMABMR_PBL_4xPBL_32Beat     (0x10008U << ETH_DMABMR_PBL_Pos)        ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 32 
#define ETH_DMABMR_PBL_4xPBL_64Beat     (0x10010U << ETH_DMABMR_PBL_Pos)        ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 64 
#define ETH_DMABMR_PBL_4xPBL_128Beat    (0x10020U << ETH_DMABMR_PBL_Pos)        ///< maximum number of beats to be transferred in one TxDMA (or both) transaction is 128 

#define ETH_DMABMR_DSL_Pos              (2)
#define ETH_DMABMR_DSL                  (0x01U << ETH_DMABMR_DSL_Pos)            ///< Descriptor Skip Length 
#define ETH_DMABMR_DA_Pos               (1)
#define ETH_DMABMR_DA                   (0x1FU << ETH_DMABMR_DA_Pos)             ///< DMA arbitration scheme 
#define ETH_DMABMR_SR_Pos               (0)
#define ETH_DMABMR_SR                   (0x01U << ETH_DMABMR_SR_Pos)             ///< Software reset 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMATPDR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMATPDR_TPD                 (0xFFFFFFFFU)                            ///< Transmit poll demand 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMARPDR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMARPDR_RPD                 (0xFFFFFFFFU)                            ///< Receive poll demand  
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMARDLAR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMARDLAR_SRL                (0xFFFFFFFFU)                            ///< Start of receive list 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMATDLAR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMATDLAR_STL                (0xFFFFFFFFU)                            ///< Start of transmit list 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMASR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMASR_PMTS_Pos              (28)
#define ETH_DMASR_PMTS                  (0x01U << ETH_DMASR_PMTS_Pos)                ///< PMT status 
#define ETH_DMASR_MMCS_Pos              (27)
#define ETH_DMASR_MMCS                  (0x01U << ETH_DMASR_MMCS_Pos)                ///< MMC status 
#define ETH_DMASR_LIS_Pos               (26)
#define ETH_DMASR_LIS                   (0x01U << ETH_DMASR_LIS_Pos)                ///< GMAC Line interface Status 

#define ETH_DMASR_EBS_Pos               (23)
#define ETH_DMASR_EBS                   (0x07U << ETH_DMASR_EBS_Pos)                ///< Error bits status 
#define ETH_DMASR_EBS_DescAccess        (0x04U << ETH_DMASR_EBS_Pos)                ///< Error bits 0-data buffer, 1-desc. access 
#define ETH_DMASR_EBS_ReadTransf        (0x02U << ETH_DMASR_EBS_Pos)                ///< Error bits 0-write trnsf, 1-read transfr 
#define ETH_DMASR_EBS_DataTransfTx      (0x01U << ETH_DMASR_EBS_Pos)                ///< Error bits 0-Rx DMA, 1-Tx DMA 
#define ETH_DMASR_TPS_Pos               (20)
#define ETH_DMASR_TPS                   (0x007U << ETH_DMASR_TPS_Pos)                  ///< Transmit process state 
#define ETH_DMASR_TPS_Stopped           (0x000U << ETH_DMASR_TPS_Pos)                  ///< Stopped - Reset or Stop Tx Command issued  
#define ETH_DMASR_TPS_Fetching          (0x001U << ETH_DMASR_TPS_Pos)                  ///< Running - fetching the Tx descriptor 
#define ETH_DMASR_TPS_Waiting           (0x002U << ETH_DMASR_TPS_Pos)                  ///< Running - waiting for status 
#define ETH_DMASR_TPS_Reading           (0x003U << ETH_DMASR_TPS_Pos)                  ///< Running - reading the data from host memory 
#define ETH_DMASR_TPS_Suspended         (0x006U << ETH_DMASR_TPS_Pos)                  ///< Suspended - Tx Descriptor unavailabe 
#define ETH_DMASR_TPS_Closing           (0x007U << ETH_DMASR_TPS_Pos)                  ///< Running - closing Rx descriptor 
#define ETH_DMASR_RPS_Pos               (17)
#define ETH_DMASR_RPS                   (0x07U << ETH_DMASR_RPS_Pos)                  ///< Receive process state 
#define ETH_DMASR_RPS_Stopped           (0x00U << ETH_DMASR_RPS_Pos)                  ///< Stopped - Reset or Stop Rx Command issued 
#define ETH_DMASR_RPS_Fetching          (0x01U << ETH_DMASR_RPS_Pos)                  ///< Running - fetching the Rx descriptor 
#define ETH_DMASR_RPS_Waiting           (0x03U << ETH_DMASR_RPS_Pos)                  ///< Running - waiting for packet 
#define ETH_DMASR_RPS_Suspended         (0x04U << ETH_DMASR_RPS_Pos)                  ///< Suspended - Rx Descriptor unavailable 
#define ETH_DMASR_RPS_Closing           (0x05U << ETH_DMASR_RPS_Pos)                  ///< Running - closing descriptor 
#define ETH_DMASR_RPS_Queuing           (0x07U << ETH_DMASR_RPS_Pos)                  ///< Running - queuing the recieve frame into host memory 
#define ETH_DMASR_NIS_Pos               (16)
#define ETH_DMASR_NIS                   (0x01U << ETH_DMASR_NIS_Pos )                  ///< Normal interrupt summary 
#define ETH_DMASR_AIS_Pos               (15)
#define ETH_DMASR_AIS                   (0x01U << ETH_DMASR_AIS_Pos )                  ///< Abnormal interrupt summary 
#define ETH_DMASR_ERS_Pos               (14)
#define ETH_DMASR_ERS                   (0x01U << ETH_DMASR_ERS_Pos )                  ///< Early receive status 
#define ETH_DMASR_FBES_Pos              (13)
#define ETH_DMASR_FBES                  (0x01U << ETH_DMASR_FBES_Pos)                  ///< Fatal bus error status 
#define ETH_DMASR_ETS_Pos               (10)
#define ETH_DMASR_ETS                   (0x01U << ETH_DMASR_ETS_Pos )                  ///< Early transmit status 
#define ETH_DMASR_RWTS_Pos              (9)
#define ETH_DMASR_RWTS                  (0x01U << ETH_DMASR_RWTS_Pos)                  ///< Receive watchdog timeout status 
#define ETH_DMASR_RPSS_Pos              (8)
#define ETH_DMASR_RPSS                  (0x01U << ETH_DMASR_RPSS_Pos)                  ///< Receive process stopped status 
#define ETH_DMASR_RBUS_Pos              (7)
#define ETH_DMASR_RBUS                  (0x01U << ETH_DMASR_RBUS_Pos)                  ///< Receive buffer unavailable status 
#define ETH_DMASR_RS_Pos                (6)
#define ETH_DMASR_RS                    (0x01U << ETH_DMASR_RS_Pos  )                  ///< Receive status 
#define ETH_DMASR_TUS_Pos               (5)
#define ETH_DMASR_TUS                   (0x01U << ETH_DMASR_TUS_Pos )                  ///< Transmit underflow status 
#define ETH_DMASR_ROS_Pos               (4)
#define ETH_DMASR_ROS                   (0x01U << ETH_DMASR_ROS_Pos )                  ///< Receive overflow status 
#define ETH_DMASR_TJTS_Pos              (3)
#define ETH_DMASR_TJTS                  (0x01U << ETH_DMASR_TJTS_Pos)                  ///< Transmit jabber timeout status 
#define ETH_DMASR_TBUS_Pos              (2)
#define ETH_DMASR_TBUS                  (0x01U << ETH_DMASR_TBUS_Pos)                  ///< Transmit buffer unavailable status 
#define ETH_DMASR_TPSS_Pos              (1)
#define ETH_DMASR_TPSS                  (0x01U << ETH_DMASR_TPSS_Pos)                  ///< Transmit process stopped status 
#define ETH_DMASR_TS_Pos                (0)
#define ETH_DMASR_TS                    (0x01U << ETH_DMASR_TS_Pos  )                  ///< Transmit status 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMAOMR Registers bits definition
////////////////////////////////////////////////////////////////////////////////

#define ETH_DMAOMR_TSF_Pos              (21)
#define ETH_DMAOMR_TSF                  (0x01U << ETH_DMAOMR_TSF_Pos)                  ///< Transmit store and forward 
#define ETH_DMAOMR_FTF_Pos              (20)
#define ETH_DMAOMR_FTF                  (0x01U << ETH_DMAOMR_FTF_Pos)                  ///< Flush transmit FIFO 
#define ETH_DMAOMR_TTC_Pos              (14)
#define ETH_DMAOMR_TTC                  (0x07U << ETH_DMAOMR_TTC_Pos)                  ///< Transmit threshold control 
#define ETH_DMAOMR_TTC_64Bytes          (0x00U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 64 Bytes 
#define ETH_DMAOMR_TTC_128Bytes         (0x01U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 128 Bytes 
#define ETH_DMAOMR_TTC_192Bytes         (0x02U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 192 Bytes 
#define ETH_DMAOMR_TTC_256Bytes         (0x03U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 256 Bytes 
#define ETH_DMAOMR_TTC_40Bytes          (0x04U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 40 Bytes 
#define ETH_DMAOMR_TTC_32Bytes          (0x05U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 32 Bytes 
#define ETH_DMAOMR_TTC_24Bytes          (0x06U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 24 Bytes 
#define ETH_DMAOMR_TTC_16Bytes          (0x07U << ETH_DMAOMR_TTC_Pos)                  ///< threshold level of the MTL Transmit FIFO is 16 Bytes 
#define ETH_DMAOMR_ST_Pos               (13)
#define ETH_DMAOMR_ST                   (0x01U << ETH_DMAOMR_ST_Pos  )                  ///< Start/stop transmission command 
#define ETH_DMAOMR_RFD_Pos              (11)
#define ETH_DMAOMR_RFD1                 (0x00U << ETH_DMAOMR_RFD_Pos  )                 ///< Threshold for failure flow control 1 byte
#define ETH_DMAOMR_RFD2                 (0x01U << ETH_DMAOMR_RFD_Pos  )                 ///< Threshold for failure flow control 2 byte
#define ETH_DMAOMR_RFD3                 (0x02U << ETH_DMAOMR_RFD_Pos  )                 ///< Threshold for failure flow control 3 byte
#define ETH_DMAOMR_RFD4                 (0x03U << ETH_DMAOMR_RFD_Pos  )                 ///< Threshold for failure flow control 4 byte
#define ETH_DMAOMR_RFA_Pos              (9)
#define ETH_DMAOMR_RFA1                 (0x00U << ETH_DMAOMR_RFA_Pos  )                 ///< Activate the threshold for flow control 1 byte
#define ETH_DMAOMR_RFA2                 (0x01U << ETH_DMAOMR_RFA_Pos  )                 ///< Activate the threshold for flow control 2 byte
#define ETH_DMAOMR_RFA3                 (0x02U << ETH_DMAOMR_RFA_Pos  )                 ///< Activate the threshold for flow control 3 byte
#define ETH_DMAOMR_RFA4                 (0x03U << ETH_DMAOMR_RFA_Pos  )                 ///< Activate the threshold for flow control 4 byte

#define ETH_DMAOMR_EFC_Pos              (8)
#define ETH_DMAOMR_EFC                  (0x01U << ETH_DMAOMR_EFC_Pos )                  ///< Enable HW Flow Control 
#define ETH_DMAOMR_FEF_Pos              (7)
#define ETH_DMAOMR_FEF                  (0x01U << ETH_DMAOMR_FEF_Pos )                  ///< Forward error frames 
#define ETH_DMAOMR_FUGF_Pos             (6)
#define ETH_DMAOMR_FUGF                 (0x01U << ETH_DMAOMR_FUGF_Pos)                  ///< Forward undersized good frames 
#define ETH_DMAOMR_RTC_Pos              (3)
#define ETH_DMAOMR_RTC                  (0x03U << ETH_DMAOMR_RTC_Pos)                  ///< receive threshold control 
#define ETH_DMAOMR_RTC_64Bytes          (0x00U << ETH_DMAOMR_RTC_Pos)                  ///< threshold level of the MTL Receive FIFO is 64 Bytes 
#define ETH_DMAOMR_RTC_32Bytes          (0x01U << ETH_DMAOMR_RTC_Pos)                  ///< threshold level of the MTL Receive FIFO is 32 Bytes 
#define ETH_DMAOMR_RTC_96Bytes          (0x02U << ETH_DMAOMR_RTC_Pos)                  ///< threshold level of the MTL Receive FIFO is 96 Bytes 
#define ETH_DMAOMR_RTC_128Bytes         (0x03U << ETH_DMAOMR_RTC_Pos)                  ///< threshold level of the MTL Receive FIFO is 128 Bytes 
#define ETH_DMAOMR_OSF_Pos              (2)
#define ETH_DMAOMR_OSF                  (0x01U << ETH_DMAOMR_OSF_Pos)                  ///< operate on second frame 
#define ETH_DMAOMR_SR_Pos               (1)
#define ETH_DMAOMR_SR                   (0x01U << ETH_DMAOMR_SR_Pos )                  ///< Start/stop receive 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMAIER Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMAIER_NISE_Pos             (16)
#define ETH_DMAIER_NISE                 (0x01U << ETH_DMAIER_NISE_Pos )                  ///< Normal interrupt summary enable 
#define ETH_DMAIER_AISE_Pos             (15)
#define ETH_DMAIER_AISE                 (0x01U << ETH_DMAIER_AISE_Pos )                  ///< Abnormal interrupt summary enable 
#define ETH_DMAIER_ERIE_Pos             (14)
#define ETH_DMAIER_ERIE                 (0x01U << ETH_DMAIER_ERIE_Pos )                  ///< Early receive interrupt enable 
#define ETH_DMAIER_FBEIE_Pos            (13)
#define ETH_DMAIER_FBEIE                (0x01U << ETH_DMAIER_FBEIE_Pos)                  ///< Fatal bus error interrupt enable 
#define ETH_DMAIER_ETIE_Pos             (10)
#define ETH_DMAIER_ETIE                 (0x01U << ETH_DMAIER_ETIE_Pos )                  ///< Early transmit interrupt enable 
#define ETH_DMAIER_RWTIE_Pos            (9)
#define ETH_DMAIER_RWTIE                (0x01U << ETH_DMAIER_RWTIE_Pos)                  ///< Receive watchdog timeout interrupt enable 
#define ETH_DMAIER_RPSIE_Pos            (8)
#define ETH_DMAIER_RPSIE                (0x01U << ETH_DMAIER_RPSIE_Pos)                  ///< Receive process stopped interrupt enable 
#define ETH_DMAIER_RBUIE_Pos            (7)
#define ETH_DMAIER_RBUIE                (0x01U << ETH_DMAIER_RBUIE_Pos)                  ///< Receive buffer unavailable interrupt enable 
#define ETH_DMAIER_RIE_Pos              (6)
#define ETH_DMAIER_RIE                  (0x01U << ETH_DMAIER_RIE_Pos  )                  ///< Receive interrupt enable 
#define ETH_DMAIER_TUIE_Pos             (5)
#define ETH_DMAIER_TUIE                 (0x01U << ETH_DMAIER_TUIE_Pos )                  ///< Transmit Underflow interrupt enable 
#define ETH_DMAIER_ROIE_Pos             (4)
#define ETH_DMAIER_ROIE                 (0x01U << ETH_DMAIER_ROIE_Pos )                  ///< Receive Overflow interrupt enable 
#define ETH_DMAIER_TJTIE_Pos            (3)
#define ETH_DMAIER_TJTIE                (0x01U << ETH_DMAIER_TJTIE_Pos)                  ///< Transmit jabber timeout interrupt enable 
#define ETH_DMAIER_TBUIE_Pos            (2)
#define ETH_DMAIER_TBUIE                (0x01U << ETH_DMAIER_TBUIE_Pos)                  ///< Transmit buffer unavailable interrupt enable 
#define ETH_DMAIER_TPSIE_Pos            (1)
#define ETH_DMAIER_TPSIE                (0x01U << ETH_DMAIER_TPSIE_Pos)                  ///< Transmit process stopped interrupt enable 
#define ETH_DMAIER_TIE_Pos              (0)
#define ETH_DMAIER_TIE                  (0x01U << ETH_DMAIER_TIE_Pos  )                  ///< Transmit interrupt enable 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMAMFBOCR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMAMFBOCR_OFOC_Pos          (28)
#define ETH_DMAMFBOCR_OFOC              (0x01U << ETH_DMAMFBOCR_OFOC_Pos)                  ///< Overflow bit for FIFO overflow counter 

#define ETH_DMAMFBOCR_MFA_Pos           (17)
#define ETH_DMAMFBOCR_MFA               (0x7FFU << ETH_DMAMFBOCR_MFA_Pos )                 ///< Number of frames missed by the application 

#define ETH_DMAMFBOCR_OMFC_Pos          (16)
#define ETH_DMAMFBOCR_OMFC              (0x01U << ETH_DMAMFBOCR_OMFC_Pos)                  ///< Overflow bit for missed frame counter 

#define ETH_DMAMFBOCR_MFC_Pos           (0)
#define ETH_DMAMFBOCR_MFC               (0xFFFFU << ETH_DMAMFBOCR_MFC_Pos )                ///< Number of frames missed by the controller 

////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMACHTDR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMACHTDR_HTDAP              (0xFFFFFFFFU)                                      ///< Host transmit descriptor address pointer 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMACHRDR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMACHRDR_HRDAP              (0xFFFFFFFFU)                                      ///< Host receive descriptor address pointer 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMACHTBAR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMACHTBAR_HTBAP             (0xFFFFFFFFU)                                      ///< Host transmit buffer address pointer 
////////////////////////////////////////////////////////////////////////////////
/// @brief ETH_DMACHRBAR Registers bits definition
////////////////////////////////////////////////////////////////////////////////
#define ETH_DMACHRBAR_HRBAP             (0xFFFFFFFFU)                                     ///< Host receive buffer address pointer 


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
