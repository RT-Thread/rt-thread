/**************************************************************************//**
 * @file     pdma.h
 * @version  V1.00
 * $Revision: 8 $
 * $Date: 14/06/05 5:16p $
 * @brief    NUC472/NUC442 PDMA driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PDMA_H__
#define __PDMA_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_PDMA_Driver PDMA Driver
  @{
*/

/** @addtogroup NUC472_442_PDMA_EXPORTED_CONSTANTS PDMA Exported Constants
  @{
*/
#define PDMA_CH_MAX    16   /*!< Specify Maximum Channels of PDMA  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  operation Mode Constant Definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_OP_STOP        0x00000000UL            /*!<DMA Stop Mode  \hideinitializer */
#define PDMA_OP_BASIC       0x00000001UL            /*!<DMA Basic Mode  \hideinitializer */
#define PDMA_OP_SCATTER     0x00000002UL            /*!<DMA Scatter-gather Mode  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Data Width Constant Definitions                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_WIDTH_8        0x00000000UL            /*!<DMA Transfer Width 8-bit  \hideinitializer */
#define PDMA_WIDTH_16       0x00001000UL            /*!<DMA Transfer Width 16-bit  \hideinitializer */
#define PDMA_WIDTH_32       0x00002000UL            /*!<DMA Transfer Width 32-bit  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Address Attribute Constant Definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_SAR_INC        0x00000000UL            /*!<DMA SAR increment  \hideinitializer */
#define PDMA_SAR_FIX        0x00000300UL            /*!<DMA SAR fix address  \hideinitializer */
#define PDMA_DAR_INC        0x00000000UL            /*!<DMA DAR increment  \hideinitializer */
#define PDMA_DAR_FIX        0x00000C00UL            /*!<DMA DAR fix address  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Burst Mode Constant Definitions                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_REQ_SINGLE     0x00000004UL            /*!<DMA Single Request  \hideinitializer */
#define PDMA_REQ_BURST      0x00000000UL            /*!<DMA Burst Request  \hideinitializer */

#define PDMA_BURST_128      0x00000000UL            /*!<DMA Burst 128 Transfers  \hideinitializer */
#define PDMA_BURST_64       0x00000010UL            /*!<DMA Burst 64 Transfers  \hideinitializer */
#define PDMA_BURST_32       0x00000020UL            /*!<DMA Burst 32 Transfers  \hideinitializer */
#define PDMA_BURST_16       0x00000030UL            /*!<DMA Burst 16 Transfers  \hideinitializer */
#define PDMA_BURST_8        0x00000040UL            /*!<DMA Burst 8 Transfers  \hideinitializer */
#define PDMA_BURST_4        0x00000050UL            /*!<DMA Burst 4 Transfers  \hideinitializer */
#define PDMA_BURST_2        0x00000060UL            /*!<DMA Burst 2 Transfers  \hideinitializer */
#define PDMA_BURST_1        0x00000070UL            /*!<DMA Burst 1 Transfers  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Peripheral Transfer Mode Constant Definitions                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_SPI0_TX        0x00000000UL            /*!<DMA Connect to SPI0 TX  \hideinitializer */
#define PDMA_SPI1_TX        0x00000001UL            /*!<DMA Connect to SPI1 TX  \hideinitializer */
#define PDMA_SPI2_TX        0x00000002UL            /*!<DMA Connect to SPI2 TX  \hideinitializer */
#define PDMA_SPI3_TX        0x00000003UL            /*!<DMA Connect to SPI3 TX  \hideinitializer */
#define PDMA_UART0_TX       0x00000004UL            /*!<DMA Connect to UART0 TX  \hideinitializer */
#define PDMA_UART1_TX       0x00000005UL            /*!<DMA Connect to UART1 TX  \hideinitializer */
#define PDMA_UART2_TX       0x00000006UL            /*!<DMA Connect to UART2 TX  \hideinitializer */
#define PDMA_UART3_TX       0x00000007UL            /*!<DMA Connect to UART3 TX  \hideinitializer */
#define PDMA_UART4_TX       0x00000008UL            /*!<DMA Connect to UART4 TX  \hideinitializer */
#define PDMA_UART5_TX       0x00000009UL            /*!<DMA Connect to UART5 TX  \hideinitializer */
#define PDMA_I2S0_TX        0x0000000BUL            /*!<DMA Connect to I2S TX  \hideinitializer */
#define PDMA_I2S1_TX        0x0000000CUL            /*!<DMA Connect to I2S1 TX  \hideinitializer */
#define PDMA_SPI0_RX        0x0000000DUL            /*!<DMA Connect to SPI0 RX  \hideinitializer */
#define PDMA_SPI1_RX        0x0000000EUL            /*!<DMA Connect to SPI1 RX  \hideinitializer */
#define PDMA_SPI2_RX        0x0000000FUL            /*!<DMA Connect to SPI2 RX  \hideinitializer */
#define PDMA_SPI3_RX        0x00000010UL            /*!<DMA Connect to SPI3 RX  \hideinitializer */
#define PDMA_UART0_RX       0x00000011UL            /*!<DMA Connect to UART0 RX  \hideinitializer */
#define PDMA_UART1_RX       0x00000012UL            /*!<DMA Connect to UART1 RX  \hideinitializer */
#define PDMA_UART2_RX       0x00000013UL            /*!<DMA Connect to UART2 RX  \hideinitializer */
#define PDMA_UART3_RX       0x00000014UL            /*!<DMA Connect to UART3 RX  \hideinitializer */
#define PDMA_UART4_RX       0x00000015UL            /*!<DMA Connect to UART4 RX  \hideinitializer */
#define PDMA_UART5_RX       0x00000016UL            /*!<DMA Connect to UART5 RX  \hideinitializer */
#define PDMA_ADC            0x00000018UL            /*!<DMA Connect to ADC  \hideinitializer */
#define PDMA_I2S0_RX        0x00000019UL            /*!<DMA Connect to I2S TX  \hideinitializer */
#define PDMA_I2S1_RX        0x0000001AUL            /*!<DMA Connect to I2S1 TX  \hideinitializer */
#define PDMA_MEM            0x0000001FUL            /*!<DMA Connect to Memory  \hideinitializer */

/*@}*/ /* end of group NUC472_442_PDMA_EXPORTED_CONSTANTS */

/** @addtogroup NUC472_442_PDMA_EXPORTED_FUNCTIONS PDMA Exported Functions
  @{
*/

/**
 * @brief       Get PDMA Interrupt Status
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This macro gets the interrupt status.
 *  \hideinitializer 
 */
#define PDMA_GET_INT_STATUS()   ((uint32_t)(PDMA->INTSTS))

/**
 * @brief       Get Transfer Done Interrupt Status
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     Get the transfer done Interrupt status.
 *  \hideinitializer 
 */
#define PDMA_GET_TD_STS()           ((uint32_t)(PDMA->TDSTS))

/**
 * @brief       Clear Transfer Done Interrupt Status
 *
 * @param[in]   u32Mask     The channel mask
 *
 * @return      None
 *
 * @details     Clear the transfer done Interrupt status.
 *  \hideinitializer 
 */
#define PDMA_CLR_TD_FLAG(u32Mask)   ((uint32_t)(PDMA->TDSTS = u32Mask))

/**
 * @brief       Get Target Abort Interrupt Status
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     Get the target abort Interrupt status.
 *  \hideinitializer 
 */
#define PDMA_GET_ABORT_STS()        ((uint32_t)(PDMA->ABTSTS))

/**
 * @brief       Clear Target Abort Interrupt Status
 *
 * @param[in]   u32Mask     The channel mask
 *
 * @return      None
 *
 * @details     Clear the target abort Interrupt status.
 *  \hideinitializer 
 */
#define PDMA_CLR_ABORT_FLAG(u32Mask)    ((uint32_t)(PDMA->ABTSTS = u32Mask))

/**
 * @brief       Get Scatter-Gather Table Empty Interrupt Status
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     Get the scatter-gather table empty Interrupt status.
 *  \hideinitializer 
 */
#define PDMA_GET_EMPTY_STS()        ((uint32_t)(PDMA->SCATSTS))

/**
 * @brief       Clear Scatter-Gather Table Empty Interrupt Status
 *
 * @param[in]   u32Mask     The channel mask
 *
 * @return      None
 *
 * @details     Clear the scatter-gather table empty Interrupt status.
 *  \hideinitializer 
 */
#define PDMA_CLR_EMPTY_FLAG(u32Mask)    ((uint32_t)(PDMA->SCATSTS = u32Mask))


/**
 * @brief       Check Channel Status
 *
 * @param[in]   u32Ch     The selected channel
 *
 * @return      0 = idle; 1 = busy
 *
 * @details     Check the selected channel is busy or not.
 *  \hideinitializer 
 */
#define PDMA_IS_CH_BUSY(u32Ch)    ((uint32_t)(PDMA->TRGSTS & (1 << u32Ch))? 1 : 0)

/**
 * @brief       Set Source Address
 *
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Addr   The selected address
 *
 * @return      None
 *
 * @details     This macro set the selected channel source address.
 *  \hideinitializer 
 */
#define PDMA_SET_SRC_ADDR(u32Ch, u32Addr) ((uint32_t)(PDMA->DSCT[u32Ch].ENDSA = u32Addr))

/**
 * @brief       Set Destination Address
 *
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Addr   The selected address
 *
 * @return      None
 *
 * @details     This macro set the selected channel destination address.
 *  \hideinitializer 
 */
#define PDMA_SET_DST_ADDR(u32Ch, u32Addr) ((uint32_t)(PDMA->DSCT[u32Ch].ENDDA = u32Addr))

/**
 * @brief       Set Transfer Count
 *
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Count  Transfer Count
 *
 * @return      None
 *
 * @details     This macro set the selected channel transfer count.
 *  \hideinitializer 
 */
#define PDMA_SET_TRANS_CNT(u32Ch, u32Count) ((uint32_t)(PDMA->DSCT[u32Ch].CTL=(PDMA->DSCT[u32Ch].CTL&~PDMA_DSCT_CTL_TXCNT_Msk)|((u32Count-1) << PDMA_DSCT_CTL_TXCNT_Pos))

/**
 * @brief       Set Scatter-gather descriptor Address
 *
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Addr   The descriptor address
 *
 * @return      None
 *
 * @details     This macro set the selected channel scatter-gather descriptor address.
 *  \hideinitializer 
 */
#define PDMA_SET_SCATTER_DESC(u32Ch, u32Addr) ((uint32_t)(PDMA->DSCT[u32Ch].NEXT = u32Addr - (PDMA->SCATBA)))

/**
 * @brief       Stop the channel
 *
 * @param[in]   u32Ch     The selected channel
 *
 * @return      None
 *
 * @details     This macro stop the selected channel.
 *  \hideinitializer 
 */
#define PDMA_STOP(u32Ch) ((uint32_t)(PDMA->STOP = (1 << u32Ch)))



void PDMA_Open(uint32_t u32Mask);
void PDMA_Close(void);
void PDMA_SetTransferCnt(uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount);
void PDMA_SetTransferAddr(uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl);
void PDMA_SetTransferMode(uint32_t u32Ch, uint32_t u32Periphral, uint32_t u32ScatterEn, uint32_t u32DescAddr);
void PDMA_SetBurstType(uint32_t u32Ch, uint32_t u32BurstType, uint32_t u32BurstSize);
void PDMA_Trigger(uint32_t u32Ch);
void PDMA_EnableInt(uint32_t u32Ch, uint32_t u32Mask);
void PDMA_DisableInt(uint32_t u32Ch, uint32_t u32Mask);



/*@}*/ /* end of group NUC472_442_PDMA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_PDMA_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__PDMA_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
