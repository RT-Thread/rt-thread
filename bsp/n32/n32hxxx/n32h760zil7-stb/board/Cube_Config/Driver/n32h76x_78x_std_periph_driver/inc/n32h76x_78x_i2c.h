/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_i2c.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_I2C_H__
#define __N32H76X_78X_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/**  n32h76x_78x_StdPeriph_Driver **/

/** I2C Init structure definition **/

typedef struct
{
  uint32_t Timing;              /* Specifies the I2C_BUSTIM_register value.
                                  This parameter calculated by referring to I2C initialization
                                         section in Reference manual */
    
  uint32_t HSTiming;              /* Specifies the I2C_HSBUSTIM_register value.
                                  This parameter calculated by referring to I2C initialization
                                         section in Reference manual */

  uint32_t OwnAddress1;         /* Specifies the first device own address.
                                  This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddressingMode;      /* Specifies if 7-bit or 10-bit addressing mode is selected. */

  uint32_t DualAddressMode;     /* Specifies if dual addressing mode is selected. */

  uint32_t OwnAddress2;         /* Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */

  uint32_t OwnAddress2Masks;    /* Specifies the acknowledge mask address second device own address if dual addressing mode is selected */

  uint32_t GeneralCallMode;     /* Specifies if general call mode is selected. */

  uint32_t NoStretchMode;       /* Specifies if nostretch mode is selected. */
        
} I2C_InitType;



#define  I2C_REG_BIT_MASK   ((uint32_t)0x00000000U)
#define  TIMING_CLEAR_MASK   (0xF0FFFFFFU)  
#define  CTRL1_CLEAR_MASK    (~(I2C_CTRL1_GENC|I2C_CTRL1_NOSTRCH))
#define  CTRL2_CLEAR_MASK    (~(I2C_CTRL2_ADR10|I2C_CTRL2_AUTOSTOP|I2C_CTRL2_NAK)) 

/** High speed setting with sys_clk = 30Mhz **/
#define I2C_H_SPEED_2_7_4_MHZ                        0x00010204
#define I2C_H_SPEED_3_MHZ                            0x00010104
#define I2C_H_SPEED_3_3_4_MHZ                        0x00010103
#define I2C_H_SPEED_3_7_7_MHZ                        0x00010102
#define I2C_TIMING          0x50210607    //48Mhz Sys_Clk :400Khz   

/** I2C_ADDRESSING_MODE I2C Addressing Mode **/
#define I2C_ADDRESSINGMODE_7BIT         (0x00000001U)
#define I2C_ADDRESSINGMODE_10BIT        (0x00000002U)

/** I2C_DUAL_ADDRESSING_MODE I2C Dual Addressing Mode **/
#define I2C_DUALADDRESS_DISABLE         (I2C_REG_BIT_MASK)
#define I2C_DUALADDRESS_ENABLE          I2C_ADR2_AD2EN

/** I2C AD2MASK mask **/
#define I2C_ADDRESS2MASK_NONE         (I2C_REG_BIT_MASK)
#define I2C_ADDRESS2MASK_1            (I2C_ADR2_AD2MSK_0)
#define I2C_ADDRESS2MASK_2_1          (I2C_ADR2_AD2MSK_1)
#define I2C_ADDRESS2MASK_3_1          (I2C_ADR2_AD2MSK_0|I2C_ADR2_AD2MSK_1)
#define I2C_ADDRESS2MASK_4_1          (I2C_ADR2_AD2MSK_2)
#define I2C_ADDRESS2MASK_5_1          (I2C_ADR2_AD2MSK_0|I2C_ADR2_AD2MSK_2)
#define I2C_ADDRESS2MASK_6_1          (I2C_ADR2_AD2MSK_1|I2C_ADR2_AD2MSK_2)
#define I2C_ADDRESS2MASK_7_1          (I2C_ADR2_AD2MSK)

/** I2C_GENERAL_CALL_ADDRESSING_MODE I2C General Call Addressing Mode **/
#define I2C_GENERALCALL_DISABLE         (I2C_REG_BIT_MASK)
#define I2C_GENERALCALL_ENABLE          I2C_CTRL1_GENC

/** I2C_NOSTRCH_MODE I2C No-Stretch Mode **/
#define I2C_NOSTRCH_DISABLE           (I2C_REG_BIT_MASK)
#define I2C_NOSTRCH_ENABLE            I2C_CTRL1_NOSTRCH


/** I2C Private Defines **/

/** I2C SPE mask **/
#define CTRL1_SPEN_SET                           I2C_CTRL1_I2CEN
#define CTRL1_SPEN_RESET                         (~I2C_CTRL1_I2CEN)

/** I2C DF mask **/
#define CTRL1_DF_SET                               I2C_CTRL1_DF
/** I2C DFX filter mask **/
#define CTRL1_DFX_SET                           I2C_CTRL1_DFX

#define CTRL1_DF10_RESET                        (~(I2C_CTRL1_DFX | I2C_CTRL1_DF))

/** I2C AF mask **/
#define CTRL1_AF_SET                                I2C_CTRL1_AFOFF
#define CTRL1_AF_RESET                              (~I2C_CTRL1_AFOFF)

/** I2C DMA TRANSMISSION mask **/
#define CTRL1_DMAWREN_TRANSMISSION_SET       I2C_CTRL1_DMAWREN
#define CTRL1_DMAWREN_TRANSMISSION_RESET     (~I2C_CTRL1_DMAWREN)

/** I2C DMA RECEPTION mask **/
#define CTRL1_DMARDEN_RECEPTION_SET           I2C_CTRL1_DMARDEN
#define CTRL1_DMARDEN_RECEPTION_RESET         (~I2C_CTRL1_DMARDEN)

/** I2C (SBCTL)SLAVE BYTE CONTROL mask **/
#define CTRL1_SBCTL_SET                       I2C_CTRL1_SBCTL
#define CTRL1_SBCTL_RESET                     (~I2C_CTRL1_SBCTL)

/** I2C NOSTRETCH mask **/
#define CTRL1_NOSTRETCH_SET                   I2C_CTRL1_NOSTRCH
#define CTRL1_NOSTRETCH_RESET                 (~I2C_CTRL1_NOSTRCH)

/** I2C GENC mask **/
#define CTRL1_GENC_SET                        I2C_CTRL1_GENC
#define CTRL1_GENC_RESET                      (~I2C_CTRL1_GENC)

/** I2C SMBH mask **/
#define CTRL1_SMBH_SET                        I2C_CTRL1_SMBH
#define CTRL1_SMBH_RESET                      (~I2C_CTRL1_SMBH)

/** I2C SMBD mask **/
#define CTRL1_SMBD_SET                        I2C_CTRL1_SMBD
#define CTRL1_SMBD_RESET                      (~I2C_CTRL1_SMBD)

/** I2C ALRTEN mask **/
#define CTRL1_ALRTEN_SET                       I2C_CTRL1_ALRTEN
#define CTRL1_ALRTEN_RESET                     (~I2C_CTRL1_ALRTEN)

/** I2C CRC mask **/
#define CTRL1_CRCEN_SET                       I2C_CTRL1_CRCEN
#define CTRL1_CRCEN_RESET                     (~I2C_CTRL1_CRCEN)

/** I2C RX FIFO INTERRUPT mask **/
#define CTRL1_FRXIE_SET                       I2C_CTRL1_FRXIE
#define CTRL1_FRXIE_RESET                     (~I2C_CTRL1_FRXIE)

/** I2C TX FIFO INTERRUPT mask **/
#define CTRL1_FTXIE_SET                       I2C_CTRL1_FTXIE
#define CTRL1_FTXIE_RESET                     (~I2C_CTRL1_FTXIE)

/** I2C NAK mask **/
#define STSINT_ADRRCV_MASK                    I2C_STSINT_ADRRCV

/** I2C MASTER TRANSFER DIRECTION **/
#define CTRL2_MASTER_WRITE                    (~I2C_CTRL2_RD_RWNN)
#define CTRL2_MASTER_READ                      I2C_CTRL2_RD_RWNN

/** I2C 10/7 addressing mode **/
#define CTRL2_ADR10                         I2C_CTRL2_ADR10
#define CTRL2_ADR7                          (~I2C_CTRL2_ADR10)

/** I2C HDR10 mask **/
#define CTRL2_HDR10_ENABLE                  I2C_CTRL2_HDR10
#define CTRL2_HDR10_DISABLE                 (~I2C_CTRL2_HDR10)

/** I2C START mask **/
#define CTRL2_START_ENABLE                  I2C_CTRL2_START
#define CTRL2_START_DISABLE                 (~I2C_CTRL2_START)

/** I2C STOP mask **/
#define CTRL2_STOP_ENABLE                   I2C_CTRL2_STOP
#define CTRL2_STOP_DISABLE                  (~I2C_CTRL2_STOP)

/** I2C NAK mask **/
#define CTRL2_NACK                          I2C_CTRL2_NAK
#define CTRL2_ACK                           (~I2C_CTRL2_NAK)

/** I2C REFILL **/
#define CTRL2_REFILL_ENABLE                   I2C_CTRL2_REFILL
#define CTRL2_REFILL_DISABLE                  (~I2C_CTRL2_REFILL)

/** I2C AUTOSTOP **/
#define CTRL2_AUTO_STOP                        I2C_CTRL2_AUTOSTOP
#define CTRL2_SOFTWARE_STOP                    (~I2C_CTRL2_AUTOSTOP)

/** I2C CRCBYTE mask **/
#define CTRL2_CRCBYTE_ENABLE                   I2C_CTRL2_CRCBYTE
#define CTRL2_CRCBYTE_DISABLE                  (~I2C_CTRL2_CRCBYTE)

/** I2C own ADR1 mask **/
#define ADR1_OWN_ADR1_ENABLE                   I2C_ADR1_AD1EN
#define ADR1_OWN_ADR1_DISABLE                  (~I2C_ADR1_AD1EN)

/** I2C AD1MODE mask **/
#define ADR1MODE_10_BIT_ADDR                   I2C_ADR1_AD1MODE
#define ADR1MODE_7_BIT_ADDR                    (~I2C_ADR1_AD1MODE)

/** I2C AD2 mask **/
#define ADR2_ENABLE                            I2C_ADR2_AD2EN
#define ADR2_DISABLE                           (~I2C_ADR2_AD2EN)

/** I2C ADD2 mask **/
#define ADR2_AD2_RESET                        (~I2C_ADR2_AD2)                                        
#define ADR2_AD2_SET                          I2C_ADR2_AD2

/** I2C TMOUTA idle clok timeout detection **/
#define TMOUTA_SCL_LOW_TMOUT                  (~I2C_TMOUTR_TMIDLE)
#define TMOUTA_SCL_SDA_LOW_TMOUT              I2C_TMOUTR_TMIDLE

/** I2C TMOUTEN mask **/
#define TMOUTEN_ENABLE                        I2C_TMOUTR_TMOUTEN
#define TMOUTEN_DISABLE                       (~I2C_TMOUTR_TMOUTEN)

/** I2C TMEXTEN mask **/
#define TMEXTEN_ENABLE                        I2C_TMOUTR_TMEXTEN
#define TMEXTEN_DISABLE                       (~I2C_TMOUTR_TMEXTEN)

/** I2C TX FIFO active **/
#define TFE_ENABLE                           I2C_FIFOCSR_TFE
#define TFE_DISABLE                           (~I2C_FIFOCSR_TFE)

/** I2C RX FIFO active **/
#define RFE_ENABLE                           I2C_FIFOCSR_RFE
#define RFE_DISABLE                           (~I2C_FIFOCSR_RFE)

/** I2C TX_ILEVEL **/
#define TX_ILEVEL_1                           I2C_FIFOCSR_TX_ILEVEL01
#define TX_ILEVEL_2                           I2C_FIFOCSR_TX_ILEVEL02
#define TX_ILEVEL_3                           I2C_FIFOCSR_TX_ILEVEL03
#define TX_ILEVEL_4                           I2C_FIFOCSR_TX_ILEVEL04
#define TX_ILEVEL_5                           I2C_FIFOCSR_TX_ILEVEL05
#define TX_ILEVEL_6                           I2C_FIFOCSR_TX_ILEVEL06
#define TX_ILEVEL_7                           I2C_FIFOCSR_TX_ILEVEL07
#define TX_ILEVEL_8                           I2C_FIFOCSR_TX_ILEVEL08

/** I2C RX_ILEVEL **/
#define RX_ILEVEL_1                           I2C_FIFOCSR_RX_ILEVEL01
#define RX_ILEVEL_2                           I2C_FIFOCSR_RX_ILEVEL02
#define RX_ILEVEL_3                           I2C_FIFOCSR_RX_ILEVEL03
#define RX_ILEVEL_4                           I2C_FIFOCSR_RX_ILEVEL04
#define RX_ILEVEL_5                           I2C_FIFOCSR_RX_ILEVEL05
#define RX_ILEVEL_6                           I2C_FIFOCSR_RX_ILEVEL06
#define RX_ILEVEL_7                           I2C_FIFOCSR_RX_ILEVEL07
#define RX_ILEVEL_8                           I2C_FIFOCSR_RX_ILEVEL08

/** I2C QUICK COMMAND **/
#define QCMD_ENABLE                            I2C_QCMD_QCMDEN
#define QCMD_DISABLE                           (~I2C_QCMD_QCMDEN)

#define QCMDAD_MASK                            (~I2C_QCMD_QCMDAD)

/** I2C SCL ANALOG FILTER mask **/
#define SCLAFENN_ENABLE                       I2C_GFLTRCTRL_SCLAFENN
#define SCLAFENN_DISABLE                      (~I2C_GFLTRCTRL_SCLAFENN)

/** I2C bus timeout **/
#define I2C_TMOUTA_MASK                       (~I2C_TMOUTR_TMOUTA)
#define I2C_TMOUTB_MASK                       (~I2C_TMOUTR_TMOUTB)

#define I2C_TMOUTA_DETECT_SCL_LOW             (I2C_REG_BIT_MASK)
#define I2C_TMOUTA_DETECT_BUS_IDLE            (I2C_TMOUTR_TMIDLE)

/** I2C Analogue Filter Width **/
/* I2C GFLTRCTRL mask */
#define I2C_SDAAFW_MASK                       (~I2C_GFLTRCTRL_SDAAFW)
#define I2C_SCLAFW_MASK                       (~I2C_GFLTRCTRL_SCLAFW)

#define I2C_ANALOG_FILTER_WIDTH_5NS           (I2C_REG_BIT_MASK)        
#define I2C_ANALOG_FILTER_WIDTH_15NS          (I2C_GFLTRCTRL_SDAAFW_0)            
#define I2C_ANALOG_FILTER_WIDTH_25NS          (I2C_GFLTRCTRL_SDAAFW_1)        
#define I2C_ANALOG_FILTER_WIDTH_35NS          (I2C_GFLTRCTRL_SDAAFW)

/** I2C SDA ANALOG FILTER mask **/
#define SDAAFENN_ENABLE                       I2C_GFLTRCTRL_SDAAFENN
#define SDAAFENN_DISABLE                      (~I2C_GFLTRCTRL_SDAAFENN)

#define I2C_SADR_RWN_MASK                    (~(I2C_CTRL2_RWN|I2C_CTRL2_SADR))
#define I2C_SADR_MASK                    (I2C_CTRL2_SADR)
#define I2C_DIRECTION_SEND                   (I2C_REG_BIT_MASK)
#define I2C_DIRECTION_RECV                   (I2C_CTRL2_RWN)

/**  I2C Flag definition **/
#define I2C_FLAG_WRE                    I2C_STSINT_WRE
#define I2C_FLAG_WRAVL                  I2C_STSINT_WRAVL 
#define I2C_FLAG_RDAVL                  I2C_STSINT_RDAVL
#define I2C_FLAG_ADR                    I2C_STSINT_ADR
#define I2C_FLAG_NAKF                   I2C_STSINT_NAKF
#define I2C_FLAG_STOPF                  I2C_STSINT_STOPF
#define I2C_FLAG_TFC                    I2C_STSINT_TFC
#define I2C_FLAG_TFCR                   I2C_STSINT_TFCR
#define I2C_FLAG_BSER                   I2C_STSINT_BSER
#define I2C_FLAG_ABLO                   I2C_STSINT_ABLO
#define I2C_FLAG_OVF                    I2C_STSINT_OVF
#define I2C_FLAG_CRCERR                 I2C_STSINT_CRCERR
#define I2C_FLAG_TMOUT                  I2C_STSINT_TMOUT
#define I2C_FLAG_ALRT                   I2C_STSINT_ALRT
#define I2C_FLAG_QADR                   I2C_STSINT_QADR
#define I2C_FLAG_BUSY                   I2C_STSINT_BUSY
#define I2C_FLAG_DIR                    I2C_STSINT_DIR
#define I2C_FLAG_FRXNE                  I2C_STSINT_FRXNE                        
#define I2C_FLAG_FTXIS                  I2C_STSINT_FTXIS

/** I2C_interrupts_definition **/
#define I2C_INT_WDR                      I2C_CTRL1_WDRIE    /* TX interrupt enable */
#define I2C_INT_RDR                      I2C_CTRL1_RDRIE    /* RX interrupt enable */
#define I2C_INT_ADR                      I2C_CTRL1_ADRIE
#define I2C_INT_NACK                     I2C_CTRL1_NAKIE /* Address match interrupt enable */
#define I2C_INT_STOP                     I2C_CTRL1_STOPIE /* Stop detection interrupt enable */
#define I2C_INT_TFC                      I2C_CTRL1_TFCIE /* Transfer complete interrupt enable */
#define I2C_INT_ERR                      I2C_CTRL1_ERRIE /* Error interrupt enable */
#define I2C_INT_RXFIFO                   I2C_CTRL1_FRXIE   /* FIFO RX interrupt enable */
#define I2C_INT_TXFIFO                   I2C_CTRL1_FTXIE /* FIFO TX interrupt enable */

/* I2C BYTENUM byte number mask */
#define BYTENUM_Mask                      (~I2C_CTRL2_BYTECNT)        
/* I2C FIFO_TX_ILEVEL mask */
#define FIFO_TX_ILEVEL_Mask               (~I2C_FIFOCSR_TXILEVEL)
/* I2C FIFO_RX_ILEVEL mask */
#define FIFO_RX_ILEVEL_Mask               (~I2C_FIFOCSR_RXILEVEL)  
/* I2C FIFO_TX_ILEVEL mask */
#define FIFO_TX_FLEVEL_Mask               (I2C_FIFOCSR_TXFLEVEL)
/* I2C FIFO_RX_ILEVEL mask */
#define FIFO_RX_FLEVEL_Mask               (I2C_FIFOCSR_RXFLEVEL)  

/** I2C_Exported_Macros **/

/** I2C_Exported_Functions **/
void I2C_DeInit(I2C_Module* I2Cx);
void I2C_Init(I2C_Module* I2Cx, I2C_InitType* I2C_InitStruct);
void I2C_InitStruct(I2C_InitType* I2C_StructInit);
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigSendAddress(I2C_Module* I2Cx, uint32_t address, uint32_t direction);
void I2C_Enable10bitAddressHeader(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableAutomaticEnd(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableReload(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t Address);
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSlaveByteControl(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSMBusAlert(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSMBusDefaultAddr(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSMBusHostAddr(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SendData(I2C_Module* I2Cx, uint8_t Data);
uint8_t I2C_RecvData(I2C_Module* I2Cx);
void I2C_SendCRC(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableCRC(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableQuickCommand(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigQuickCommandAddr(I2C_Module* I2Cx, uint8_t Address);
void I2C_EnableTXFIFO(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableRXFIFO(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableTXDMA(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableRXDMA(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetTransferByteNumber(I2C_Module* I2Cx, uint8_t Number_Of_bytes);
void I2C_SetTXFIFO_ILEVEL(I2C_Module* I2Cx, uint8_t TX_ILEVEL);
void I2C_SetRXFIFO_ILEVEL(I2C_Module* I2Cx, uint8_t RX_ILEVEL);
void I2C_EnableSCLTimeoutDetection(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableExtenClkTimeout(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetBusTimeoutA(I2C_Module* I2Cx, uint32_t bus_timeout);
void I2C_SetBusTimeoutB(I2C_Module* I2Cx, uint32_t bus_timeout);
void I2C_ConfigIdleClockTimeout(I2C_Module* I2Cx, uint32_t bus_timeout);
void I2C_EnableAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSDAAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSCLAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetSCLAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetSDAAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetDigitalFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG);
void I2C_ConfigInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd);

uint8_t I2C_GetTXFIFO_FLEVEL(I2C_Module* I2Cx);
uint8_t I2C_GetRXFIFO_FLEVEL(I2C_Module* I2Cx);
uint8_t I2C_GetCRC(I2C_Module* I2Cx);
uint8_t I2C_GetReceiveAddress(I2C_Module* I2Cx);
FlagStatus I2C_GetFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG);

#ifdef __cplusplus
}
#endif

#endif /*__N32H76X_78X_I2C_H__ */

