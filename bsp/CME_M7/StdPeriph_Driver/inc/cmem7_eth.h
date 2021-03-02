/**
    *****************************************************************************
    * @file     cmem7_eth.h
    *
    * @brief    CMEM7 ethernet header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_ETH_H
#define __CMEM7_ETH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup ETH_SPEED
  * @{
  */
#define ETH_SPEED_10M               0x0
#define ETH_SPEED_100M              0x1
#define ETH_SPEED_1000M             0x2

#define IS_ETH_SPEED(SPEED)             (((SPEED) == ETH_SPEED_10M)  || \
                                     ((SPEED) == ETH_SPEED_100M) || \
                                                                         ((SPEED) == ETH_SPEED_1000M))
/**
  * @}
  */

/** @defgroup ETH_DUPLEX
  * @{
  */
#define ETH_DUPLEX_HALF             0x0
#define ETH_DUPLEX_FULL             0x1

#define IS_ETH_DUPLEX(DUPLEX)           (((DUPLEX) == ETH_DUPLEX_HALF) || \
                                                                         ((DUPLEX) == ETH_DUPLEX_FULL))
/**
  * @}
  */

/** @defgroup ETH_INT
  * @{
  */
#define ETH_INT_TX_COMPLETE_FRAME       0x0001
#define ETH_INT_TX_STOP             0x0002
#define ETH_INT_TX_BUF_UNAVAI       0x0004
#define ETH_INT_RX_OVERFLOW                 0x0010
#define ETH_INT_TX_UNDERFLOW                0x0020
#define ETH_INT_RX_COMPLETE_FRAME   0x0040
#define ETH_INT_RX_BUF_UNAVAI       0x0080
#define ETH_INT_RX_STOP             0x0100
#define ETH_INT_BUS_FATAL_ERROR     0x2000
#define ETH_INT_ALL                 (ETH_INT_TX_COMPLETE_FRAME | \
                                     ETH_INT_TX_STOP           | \
                                                                         ETH_INT_TX_BUF_UNAVAI     | \
                                                                         ETH_INT_RX_OVERFLOW       | \
                                                                         ETH_INT_TX_UNDERFLOW      | \
                                                                         ETH_INT_RX_COMPLETE_FRAME | \
                                                                         ETH_INT_RX_BUF_UNAVAI     | \
                                                                         ETH_INT_RX_STOP           | \
                                                                         ETH_INT_BUS_FATAL_ERROR)

#define IS_ETH_INT(INT)             (((INT) != 0) && (((INT) & ~ETH_INT_ALL) == 0))
/**
  * @}
  */
/**
  * @brief  EFUSE receive filter structure
    */
typedef struct
{
    BOOL ETH_BroadcastFilterEnable;   /*!< Broadcast is dropped or passed                                       */
    BOOL ETH_OwnFilterEnable;           /*!< source address filter is on or off                                 */
    BOOL ETH_SelfDrop;                          /*!< Only own address is dropped or passed                              */
    BOOL ETH_SourceFilterEnable;        /*!< source address filter is on or off                                 */
    BOOL ETH_SourceDrop;                      /*!< Only specific source address is dropped or passed    */
    uint8_t ETH_SourceMacAddr[6];     /*!< Source MAC address                                   */
} ETH_FrameFilter;

/**
  * @brief  Ethernet initialization structure
    */
typedef struct
{
    BOOL ETH_LinkUp;                   /*!< If ETH is linked up and it can be retrieved from PHY */
    uint8_t ETH_Speed;                 /*!< speed of ETH, refer as @ref ETH_SPEED                */
    uint8_t ETH_Duplex;                /*!< duplex mode of ETH, refer as @ref ETH_DUPLEX                 */
    BOOL ETH_RxEn;                     /*!< Rx enable                                            */
    BOOL ETH_TxEn;                     /*!< Tx enable                                            */
    BOOL ETH_ChecksumOffload;          /*!< Checksum offload enable                              */
    BOOL ETH_JumboFrame;               /*!< Jumbo Frame Enable                                   */
    uint8_t ETH_MacAddr[6];            /*!< MAC address                                          */
    ETH_FrameFilter *ETH_Filter;       /*!< Received frame address filter, receive all if null   */
} ETH_InitTypeDef;

/**
  * @brief  Ethernet Tx descriptor structure
    */
typedef struct {
    union {
    uint32_t  TX0;

        struct {
            uint32_t                                :  1;
            uint32_t UNDERFLOW_ERR  :  1;    /*!< [OUT] Underflow error                                                     */
            uint32_t                                :  1;
            uint32_t COLLISION_CNT  :  4;        /*!< [OUT] Collision count                                       */
            uint32_t                                :  1;
            uint32_t EX_COLLISION   :  1;        /*!< [OUT] Excessive collision error                         */
            uint32_t LATE_COLLISION :  1;        /*!< [OUT] Late collision error                              */
            uint32_t NO_CARRIER     :  1;        /*!< [OUT] No carrier error                                    */
            uint32_t LOSS_CARRIER   :  1;        /*!< [OUT] loss of carrier error                           */
            uint32_t PAYLOAD_ERR        :  1;        /*!< [OUT] IP payload error                                    */
            uint32_t                                :  2;
            uint32_t ERR_SUM                :  1;        /*!< [OUT] Error summary                                           */
            uint32_t HEADER_ERR         :  1;        /*!< [OUT] IP header error                                         */
            uint32_t                                :  8;
            uint32_t TTSE           :  1;    /*!< enables IEEE1588 hardware timestamping in first segment */
            uint32_t                                :  2;
            uint32_t FS             :  1;    /*!< first segment flag                                    */
            uint32_t LS             :  1;    /*!< last segment flag                                     */
            uint32_t                                :  2;
        } TX0_b;
    } TX_0;

    union {
    uint32_t  TX1;

        struct {
            uint32_t SIZE                       : 13;       /*!< buffer size                                       */
            uint32_t                : 19;
        } TX1_b;
    } TX_1;

    uint32_t bufAddr;                                           /*!< address of buffer                                           */
    uint32_t nextDescAddr;                              /*!< address of next descriptor                          */
  uint64_t reserved;
    uint64_t timeStamp;                                     /*!< time stamp while last segment                     */
} ETH_TX_DESC;

/**
  * @brief  Ethernet Rx descriptor structure
    */
typedef struct {
    union {
    uint32_t  RX0;

        struct {
            uint32_t                                :  1;
            uint32_t CRC_ERR        :  1;    /*!< [OUT] CRC error while last segment                        */
            uint32_t                                :  5;
            uint32_t TTSE           :  1;    /*!< timestamp available while last segment                */
            uint32_t LS             :  1;    /*!< [OUT] last segment flag                               */
            uint32_t FS             :  1;    /*!< [OUT] first segment flag                              */
            uint32_t                                :  1;
            uint32_t OVERFLOW_ERR   :  1;    /*!< [OUT] FIFO overflow while last segment                */
            uint32_t LENGTH_ERR     :  1;    /*!< [OUT] length error while last segment                 */
            uint32_t                                :  2;
            uint32_t ERR_SUM        :  1;    /*!< [OUT] Error summary while last segment                */
            uint32_t FL             : 14;    /*!< [OUT] frame length while last segment                 */
            uint32_t                    :  2;
        } RX0_b;
    } RX_0;

    union {
    uint32_t  RX1;

        struct {
            uint32_t SIZE                       : 13;       /*!< buffer size                                       */
            uint32_t                : 19;
        } RX1_b;
    } RX_1;

    uint32_t bufAddr;                                           /*!< buffer address                                    */
    uint32_t nextDescAddr;                              /*!< address of next descriptor                        */
  uint64_t reserved;
    uint64_t timeStamp;                                     /*!< time stamp while the last segment                 */
} ETH_RX_DESC;

/**
  * @brief  Read data from phy chip
    * @param[in] phyAddr Address of phy chip
    * @param[in] phyReg Address of phy's register to be read
  * @retval uint32_t value of phy's register
    */
uint32_t ETH_PhyRead(uint32_t phyAddr, uint32_t phyReg);

/**
  * @brief  Write data to phy chip
    * @param[in] phyAddr Address of phy chip
    * @param[in] phyReg Address of phy's register to be written
    * @param[in] data Data to be written
  * @retval None
    */
void ETH_PhyWrite(uint32_t phyAddr, uint32_t phyReg, uint32_t data);
/**
  * @brief  Fills each ETH_InitStruct member with its default value.
  * @param ETH_InitStruct: pointer to a ETH_InitTypeDef structure
  *   which will be initialized.
  * @retval : None
  */
void ETH_StructInit(ETH_InitTypeDef* init);
/**
  * @brief  Ethernet initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] init A pointer to structure ETH_InitTypeDef
  * @retval BOOL The bit indicates if ethernet is initialized successfully
    */
BOOL ETH_Init(ETH_InitTypeDef *init);

/**
  * @brief  Enable or disable ethernet interrupt.
    * @param[in] Int interrupt mask bits, which can be the combination of @ref ETH_INT
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void ETH_ITConfig(uint32_t Int, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] Int interrupt mask bits, which can be the combination of @ref ETH_INT
  * @retval BOOL The bit indicates if specific interrupts are set or not
    */
BOOL ETH_GetITStatus(uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @param[in] Int interrupt mask bits, which can be the combination of @ref ETH_INT
  * @retval None
    */
void ETH_ClearITPendingBit(uint32_t Int);

/**
  * @brief  Get ethernte MAC address
    * @param[in] mac A user-allocated buffer to fetch MAC to be read, 6 bytes.
    * @retval None
    */
void ETH_GetMacAddr(uint8_t *mac);

/**
  * @brief  Set ethernet transmission descriptor ring
    * @note     Make sure that memory occupied by descriptors should be in physical
    *                   memory and keep valid before ethernet transmission is finished.
    * @param[in] ring A pointer to header of ETH_TX_DESC ring, whose last node
    *                   has a 'nextDescAddr' pointed to first node.
  * @retval BOOL The bit indicates if valid ring is set
    */
BOOL ETH_SetTxDescRing(ETH_TX_DESC *ring);

/**
  * @brief  Start ethernet transmission
    * @param    None
  * @retval None
    */
void ETH_StartTx(void);

/**
  * @brief  Stop ethernet transmission
    * @param    None
  * @retval None
    */
void ETH_StopTx(void);

/**
  * @brief  Resume ethernet transmission\n
    *               While ethernet doesn't have enough buffer to transmit data, it will
    *                   pause and inform users by interrupt 'ETH_INT_TX_BUF_UNAVAI'. Users
    *                   must call this function to start ethernet again after new buffer
    *                   prepared.
    * @param    None
  * @retval None
    */
void ETH_ResumeTx(void);

/**
  * @brief  Get free transmission descriptor\n
    * @param    None
  * @retval ETH_TX_DESC* A pointer of free transmission descriptor,
    *                   NULL if no free descriptor
    */
ETH_TX_DESC *ETH_AcquireFreeTxDesc(void);

/**
  * @brief  Check if a transmission descriptor is free or not
    * @param[in] desc A pointer of a transmission descriptor
  * @retval BOOL True if the transmission descriptor is free, or flase.
    */
BOOL ETH_IsFreeTxDesc(ETH_TX_DESC *desc);

/**
  * @brief  Release a transmission descriptor to ethernet\n
    *                   After users prepared data in the buffer of a free descriptor,
    *                   They must call this function to change ownership of the
    *                   descriptor to hardware.
    * @param[in] desc A pointer of a transmission descriptor
  * @retval None
    */
void ETH_ReleaseTxDesc(ETH_TX_DESC *desc);

/**
  * @brief  Set buffer address of the specific TX descriptor
    * @param[in] desc A pointer of a transmission descriptor
  * @param[in] bufAddr buffer address to be sent
  * @retval None
    */
void ETH_SetTxDescBufAddr(ETH_TX_DESC *desc, uint32_t bufAddr);

/**
  * @brief  Get buffer address of the specific TX descriptor
    * @param[in] desc A pointer of a transmission descriptor
  * @retval uint32_t buffer address to be gotten
    */
uint32_t ETH_GetTxDescBufAddr(ETH_TX_DESC *desc);

/**
  * @brief  Set ethernet receive descriptor ring
    * @note     Make sure that memory occupied by descriptors should be in physical
    *                   memory and keep valid before ethernet receive is finished.
    * @param[in] ring A pointer to header of ETH_TX_DESC ring, whose last node
    *                   has a 'nextDescAddr' pointed to first node.
  * @retval BOOL The bit indicates if valid ring is set
    */
BOOL ETH_SetRxDescRing(ETH_RX_DESC *ring);

/**
  * @brief  Start ethernet receive
    * @param    None
  * @retval None
    */
void ETH_StartRx(void);

/**
  * @brief  Stop ethernet receive
    * @param    None
  * @retval None
    */
void ETH_StopRx(void);

/**
  * @brief  Resume ethernet receive\n
    *               While ethernet doesn't have enough buffer to receive data, it will
    *                   pause and inform users by interrupt 'ETH_INT_RX_BUF_UNAVAI'. Users
    *                   must call this function to start ethernet again after new buffer
    *                   prepared.
    * @param    None
  * @retval None
    */
void ETH_ResumeRx(void);

/**
  * @brief  Get the free descriptor which contains received data\n
    * @param    None
  * @retval ETH_RX_DESC* A pointer of free receive descriptor,
    *                   NULL if no free descriptor
    */
ETH_RX_DESC *ETH_AcquireFreeRxDesc(void);

/**
  * @brief  Check if a receive descriptor is free or not
    * @param[in] desc A pointer of a receive descriptor
  * @retval BOOL True if the receive descriptor is free, or flase.
    */
BOOL ETH_IsFreeRxDesc(ETH_RX_DESC *desc);

/**
  * @brief  Release a receive descriptor to ethernet\n
    *                   After users handled data in the buffer of a free descriptor,
    *                   They must call this function to change ownership of the
    *                   descriptor to hardware.
    * @param[in] desc A pointer of a transmission descriptor
  * @retval None
    */
void ETH_ReleaseRxDesc(ETH_RX_DESC *desc);

/**
  * @brief  Set buffer address of the specific RX descriptor
    * @param[in] desc A pointer of a receive descriptor
  * @param[in] bufAddr buffer address to be received
  * @retval None
    */
void ETH_SetRxDescBufAddr(ETH_RX_DESC *desc, uint32_t bufAddr);

/**
  * @brief  Get buffer address of the specific RX descriptor
    * @param[in] desc A pointer of a receive descriptor
  * @retval uint32_t buffer address to be gotten
    */
uint32_t ETH_GetRxDescBufAddr(ETH_RX_DESC *desc);

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_ETH_H */

