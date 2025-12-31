/**
  **************************************************************************
  * @file      ft32f4xx_eth.c
  * @author    xcao
  * @brief     heth module driver
  *            This file provides firmware functions to manage the following
  *            functionalities of the Ethernet (heth) peripheral:
  *             + Initialization and deinitialization functions
  *             + IO operation :functions
  *             + Peripheral Control funtions
  *             + Peripheral State and Errors functions
  *
  **************************************************************************
  * @attention
  *
  **************************************************************************
  @verbatim
  ==========================================================================
                           #### How to use this driver
  ==========================================================================
    [..]
    The heth driver can be used as follows:

    (#)Declare a ETH_HandleTypeDef handle structure, for example:
       ETH_HandleTypeDef heth;

    (#)Fill parameter of Init structure in heth handle

    (#)Call ETH_Init() API to initialize the Ethernet peripheral (MAC,DMA ...)

    (#)Initialize the heth low level resources through the ETH_MspInit() API:
      (##) Enable the Ethernet interface clock using
          (+++)  RCC_ETHMAC_CLK_ENABLE()
          (+++)  RCC_ETHTX_CLK_ENABLE()
          (+++)  RCC_ETHRX_CLK_ENABLE()

      (##) Initialize the related GPIO clocks
      (##) Configure Ethernet pinout
      (##) Configure Ethernet NVIC interrupt (in Interrupt mode)

    (#) Ethernet data reception is asynchronous, so call the following API
        to start the listening mode:
        (##) ETH_Start():
             This API starts the MAC and DMA transmission and reception process,
             without enabling end of transfer interrupts, in this mode user
             has to poll for data reception by calling ETH_ReadData()
        (##) ETH_Start_IT():
             This API starts the MAC and DMA transmission and reception process,
             end of transfer interrupts are enabled in this mode,
             ETH_RxCpltCallback() will be executed when an Ethernet packet is received

    (#) When data is received user can call the following API to get received data:
        (##) ETH_ReadData(): Read a received packet

    (#) For transmission path, two APIs are available:
        (##) ETH_Transmit(): Transmit an heth frame in blocking mode
        (##) ETH_Transmit_IT(): Transmit an heth frame in interrupt mode,
             ETH_TxCpltCallback() will be executed when end of transfer occur

    (#) Communication with an external PHY device:
        (##) ETH_ReadPHYRegister(): Read a register from an external PHY
        (##) ETH_WritePHYRegister(): Write data to an external RHY register

    (#) Configure the Ethernet MAC after heth peripheral initialization
        (##) ETH_GetMACConfig(): Get MAC actual configuration into ETH_MACConfigTypeDef
        (##) ETH_SetMACConfig(): Set MAC configuration based on ETH_MACConfigTypeDef

    (#) Configure the Ethernet DMA after heth peripheral initialization
        (##) ETH_GetDMAConfig(): Get DMA actual configuration into ETH_DMAConfigTypeDef
        (##) ETH_SetDMAConfig(): Set DMA configuration based on ETH_DMAConfigTypeDef

    (#) Configure the Ethernet PTP after heth peripheral initialization
        (##) Define ETH_USE_PTP to use PTP APIs.
        (##) ETH_PTP_GetConfig(): Get PTP actual configuration into ETH_PTP_ConfigTypeDef
        (##) ETH_PTP_SetConfig(): Set PTP configuration based on ETH_PTP_ConfigTypeDef
        (##) ETH_PTP_GetTime(): Get Seconds and Nanoseconds for the Ethernet PTP registers
        (##) ETH_PTP_SetTime(): Set Seconds and Nanoseconds for the Ethernet PTP registers
        (##) ETH_PTP_AddTimeOffset(): Add Seconds and Nanoseconds offset for the Ethernet PTP registers
        (##) ETH_PTP_InsertTxTimestamp(): Insert Timestamp in transmission
        (##) ETH_PTP_GetTxTimestamp(): Get transmission timestamp
        (##) ETH_PTP_GetRxTimestamp(): Get reception timestamp


  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_eth.h"
#include "ft32f4xx_misc.h"

//#if defined(eth)

/** @defgroup eth eth
  * @brief eth module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup ETH_Private_Constants heth Private Constants
  * @{
  */
#define ETH_MAC_CFG_MASK               0x0FFBFF7FU
#define ETH_MAC_EXTDCFG_MASK           0x3F073FFFU
#define ETH_MAC_PKTFILT_MASK           0x800107FFU
#define ETH_MAC_WTDTO_MASK             0x0000010FU
#define ETH_MAC_TXFLCTL_MASK           0xFFFF00F3U
#define ETH_MAC_RXFLCTL_MASK           0x00000003U
#define ETH_MTL_TXQOPMODE_MASK         0x00000073U
#define ETH_MTL_RXQOPMODE_MASK         0x0000007BU

#define ETH_DMA_OPMODE_MASK            0x00037A03U
#define ETH_DMA_SYSBUSMODE_MASK        0x0000D001U
#define ETH_DMA_CTL_MASK               0x001D0000U
#define ETH_DMA_TXCTL_MASK             0x007F0011U
#define ETH_DMA_RXCTL_MASK             0x807F7FFFU
#define ETH_MAC_PMTCTLSTU_MASK         (ETH_MAC_PMTCTLSTU_PWRDWN | ETH_MAC_PMTCTLSTU_RWKPKTEN | \
                                        ETH_MAC_PMTCTLSTU_MGKPKTEN | ETH_MAC_PMTCTLSTU_GLBLUCAST | \
                                        ETH_MAC_PMTCTLSTU_RWKPFE)

/* Timeout values */
#define ETH_DMARXNDESCWBF_ERRORS_MASK  ((uint32_t) (ETH_DMARXNDESCWBF_DE | ETH_DMARXNDESCWBF_RE | \
                                                    ETH_DMARXNDESCWBF_OE | ETH_DMARXNDESCWBF_RWT |\
                                                    ETH_DMARXNDESCWBF_GP | ETH_DMARXNDESCWBF_CE))

#define ETH_PTP_TSCTL_MASK             0x110FFF3FU
#define ETH_PTP_SYSTMSECUPDT           0xFFFFFFFFU
#define ETH_PTP_SYSTMNSECUPDT          0xFFFFFFFFU
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup ETH_Private_Macros heth Private Macros
  * @{
  */
/* Helper macros for TX descriptor handling */
#define INCR_TX_DESC_INDEX(inx, offset) do {\
                                             (inx) += (offset);\
                                             if ((inx) >= (uint32_t)ETH_TX_DESC_CNT){\
                                             (inx) = ((inx) - (uint32_t)ETH_TX_DESC_CNT);}\
                                           } while (0)

/* Helper macros for RX descriptor handling */
#define INCR_RX_DESC_INDEX(inx, offset) do {\
                                             (inx) += (offset);\
                                             if ((inx) >= (uint32_t)ETH_RX_DESC_CNT){\
                                             (inx) = ((inx) - (uint32_t)ETH_RX_DESC_CNT);}\
                                           } while (0)


//#define CLEAR_REG(REG)  ((REG) = (0x0))

//#define WRITE_REG(REG,VAL)  ((REG) = (VAL))

//#define READ_REG(REG)  ((REG))

//#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup ETH_Private_Functions   heth Private Functions
  * @{
  */


/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup ETH_Exported_Functions heth Exported Functions
  * @{
  */

/** @defgroup ETH_Exported_Functions_Group1 Initialization and deinitialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the heth peripheral:

      (+) User must Implement ETH_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO and NVIC ).

      (+) Call the function ETH_Init() to configure the selected device with
          the selected configuration:
        (++) MAC address
        (++) Media interface (MII or RMII)
        (++) Rx DMA Descriptors Tab
        (++) Tx DMA Descriptors Tab
        (++) Length of Rx Buffers

      (+) Call the function ETH_DeInit() to restore the default configuration
          of the selected heth peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the Ethernet peripheral registers.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval uint32_t
  */
uint32_t ETH_Init(ETH_HandleTypeDef *heth)
{
    uint32_t tickstart;

    if (heth->gState == ETH_STATE_RESET)
    {

        heth->gState = ETH_STATE_BUSY;
        /* Init the low level hardware : GPIO, CLOCK, NVIC. */
        ETH_MspInit(heth);
    }

    /* TODO __RCC_SYSCFG_CLK_ENABLE();*/
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    if (heth->Init.MediaInterface == ETH_MII_MODE)
    {
        SYSCFG->PMC &= ~SYSCFG_PMC_MII_RMII_SEL;
    }
    else
    {
        SYSCFG->PMC |= SYSCFG_PMC_MII_RMII_SEL;
    }

    /* Ethernet Software reset */
    /* Set the SWR bit: resets all MAC subsystem internal registers and logic */
    /* After reset all the registers holds their respective reset values */
    heth->Instance->ETH_DMA_OPMODE |= ETH_DMA_OPMODE_SWR;

    /* TODO Get tick */
    tickstart = GetTick();//somi

    /* TODO Wait for software reset */
    while (READ_BIT(heth->Instance->ETH_DMA_OPMODE, ETH_DMA_OPMODE_SWR) > 0U)
    {
        if (((GetTick() - tickstart) > ETH_SWRESET_TIMEOUT))
        {
            heth->ErrorCode = ETH_ERROR_TIMEOUT;
            heth->gState = ETH_STATE_ERROR;
            return ERROR;
        }
    }

    /*------------------ MAC, MTL and DMA default Configuration ----------------*/
    ETH_MACDMAConfig(heth);

    /* SET DSL to 64 bit */
    heth->Instance->ETH_DMA_CTL   |= ETH_DMA_CTL_DSL_64BIT;

    /* Set Receive Buffers Length (must be a multiple of 4) */
    if ((heth->Init.RxBuffLen % 0x4U) != 0x0U)
    {
        /* Set Error Code */
        heth->ErrorCode = ETH_ERROR_PARAM;
        /* Set State as Error */
        heth->gState = ETH_STATE_ERROR;
        /* Return Error */
        return HAL_ERROR;
    }
    else
    {
        /* Set Receive Buffers Length (must be a multiple of 4) */
        heth->Instance->ETH_DMA_RXCTL = (((heth->Instance->ETH_DMA_RXCTL) & (~(ETH_DMA_RXCTL_RBSZ))) | ((heth->Init.RxBuffLen) << 1));
    }

    /*------------------ DMA Tx Descriptors Configuration ----------------------*/
    ETH_DMATxDescListInit(heth);

    /*------------------ DMA Rx Descriptors Configuration ----------------------*/
    ETH_DMARxDescListInit(heth);

    /*--------------------- ETHERNET MAC Address Configuration ------------------*/
    /* Set MAC addr bits 32 to 47 */
    heth->Instance->ETH_MAC_ADDRH0 = (((uint32_t)(heth->Init.MACAddr[5]) << 8) | (uint32_t)heth->Init.MACAddr[4]);
    /* Set MAC addr bits 0 to 31 */
    heth->Instance->ETH_MAC_ADDRL0 = (((uint32_t)(heth->Init.MACAddr[3]) << 24) | ((uint32_t)(heth->Init.MACAddr[2]) << 16) |
                                      ((uint32_t)(heth->Init.MACAddr[1]) << 8) | (uint32_t)heth->Init.MACAddr[0]);

    /* Disable Rx MMC Interrupts */
    heth->Instance->ETH_MMC_RXIRMSK = (ETH_MMC_RXIRMSK_RXCRCERPIM | ETH_MMC_RXIRMSK_RXALGNERPIM | ETH_MMC_RXIRMSK_RXUCGPIM);
    /* Disable Tx MMC Interrupts */
    heth->Instance->ETH_MMC_TXIRMSK = (ETH_MMC_TXIRMSK_TXSCOLGPIM | ETH_MMC_TXIRMSK_TXMCOLGPIM);

    heth->ErrorCode = ETH_ERROR_NONE;
    heth->gState = ETH_STATE_READY;

    return HAL_OK;
}

/**
  * @brief  DeInitializes the heth peripheral.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval uint32_t
  */
uint32_t ETH_DeInit(ETH_HandleTypeDef *heth)
{

    /* Set the ETH peripheral state to BUSY */
    heth->gState = ETH_STATE_BUSY;
    /* De-Init the low level hardware : GPIO, CLOCK, NVIC. */
    ETH_MspDeInit(heth);
    /* Set ETH HAL state to Disabled */
    heth->gState = ETH_STATE_RESET;

    return HAL_OK;
}

/**
  * @brief  Initializes the heth MSP.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
//__weak void ETH_MspInit(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_MspInit(ETH_HandleTypeDef *heth)
{
    UNUSED(heth);
}

/**
  * @brief  DeInitializes heth MSP.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
//__weak void ETH_MspDeInit(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_MspDeInit(ETH_HandleTypeDef *heth)
{
    UNUSED(heth);
}

/** @defgroup ETH_Exported_Functions_Group2 IO operation functions
  *  @brief heth Transmit and Receive functions
  *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the heth
    data transfer.
@endverbatim
  * @{
  */

/**
  * @brief  Enables Ethernet MAC and DMA reception and transmission
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval uint32_t
  */
uint32_t ETH_Start(ETH_HandleTypeDef *heth)
{
    if (heth->gState == ETH_STATE_READY)
    {
        heth->gState = ETH_STATE_BUSY;

        /* Set number of descriptors to build */
        heth->RxDescList.RxBuildDescCnt = ETH_RX_DESC_CNT;

        /* Build all descriptors */
        ETH_UpdateDescriptor(heth);

        /* Enable the MAC transmission and reception*/
        heth->Instance->ETH_MAC_CFG |= (ETH_MAC_CFG_RE | ETH_MAC_CFG_TE);

        /* Set the Flush Transmit FIFO bit */
        heth->Instance->ETH_MTL_TXQOPMODE |= ETH_MTL_TXQOPMODE_FTQ;

        /* Enable the DMA transmission */
        heth->Instance->ETH_DMA_TXCTL |= ETH_DMA_TXCTL_ST;

        /* Enable the DMA reception */
        heth->Instance->ETH_DMA_RXCTL |= ETH_DMA_RXCTL_SR;

        /* Clear Tx and Rx process stopped flags */
        heth->Instance->ETH_DMA_STU |= (ETH_DMA_STU_RPS | ETH_DMA_STU_TPS);

        heth->gState = ETH_STATE_STARTED;

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

/**
  * @brief  Enables Ethernet MAC and DMA reception/transmission in Interrupt mode
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval uint32_t
  */
uint32_t ETH_Start_IT(ETH_HandleTypeDef *heth)
{
    if (heth->gState == ETH_STATE_READY)
    {
        heth->gState = ETH_STATE_BUSY;

        /* save IT mode to heth Handle */
        heth->RxDescList.ItMode = 1U;

        /* Set number of descriptors to build */
        heth->RxDescList.RxBuildDescCnt = ETH_RX_DESC_CNT;

        /* Build all descriptors */
        ETH_UpdateDescriptor(heth);

        /* Enable the DMA transmission */
        heth->Instance->ETH_DMA_TXCTL |= ETH_DMA_TXCTL_ST;

        /* Enable the DMA reception */
        heth->Instance->ETH_DMA_RXCTL |= ETH_DMA_RXCTL_SR;

        /* Clear Tx and Rx process stopped flags */
        heth->Instance->ETH_DMA_STU |= (ETH_DMA_STU_RPS | ETH_DMA_STU_TPS);

        /* Set the Flush Transmit FIFO bit */
        heth->Instance->ETH_MTL_TXQOPMODE |= ETH_MTL_TXQOPMODE_FTQ;

        /* Enable the MAC transmission */
        heth->Instance->ETH_MAC_CFG |= ETH_MAC_CFG_TE;

        /* Enable the MAC reception */
        heth->Instance->ETH_MAC_CFG |= ETH_MAC_CFG_RE;

        /* Enable heth DMA interrupts:
        - Tx complete interrupt
        - Rx complete interrupt
        - Fatal bus interrupt
        */
        heth->Instance->ETH_DMA_INTRENA |= (ETH_DMA_INTREN_NIE | ETH_DMA_INTREN_RIE | ETH_DMA_INTREN_TIE |
                                            ETH_DMA_INTREN_FBEE | ETH_DMA_INTREN_AIE | ETH_DMA_INTREN_RBUE);

        heth->gState = ETH_STATE_STARTED;
        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

/**
  * @brief  Stop Ethernet MAC and DMA reception/transmission
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval uint32_t
  */
uint32_t ETH_Stop(ETH_HandleTypeDef *heth)
{
    if (heth->gState == ETH_STATE_STARTED)
    {
        /* Set the ETH peripheral state to BUSY */
        heth->gState = ETH_STATE_BUSY;

        /* Disable the DMA transmission */
        heth->Instance->ETH_DMA_TXCTL &= (~ETH_DMA_TXCTL_ST);

        /* Disable the DMA reception */
        heth->Instance->ETH_DMA_RXCTL &= (~ETH_DMA_RXCTL_SR);

        /* Disable the MAC reception */
        heth->Instance->ETH_MAC_CFG &= (~ETH_MAC_CFG_RE);

        /* Set the Flush Transmit FIFO bit */
        heth->Instance->ETH_MTL_TXQOPMODE |= ETH_MTL_TXQOPMODE_FTQ;

        /* Disable the MAC transmission */
        heth->Instance->ETH_MAC_CFG &= (~ETH_MAC_CFG_TE);

        heth->gState = ETH_STATE_READY;

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

/**
  * @brief  Stop Ethernet MAC and DMA reception/transmission in Interrupt mode
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval uint32_t
  */
uint32_t ETH_Stop_IT(ETH_HandleTypeDef *heth)
{
    ETH_DMADescTypeDef *dmarxdesc;
    uint32_t descindex;

    if (heth->gState == ETH_STATE_STARTED)
    {
        /* Set the ETH peripheral state to BUSY */
        heth->gState = ETH_STATE_BUSY;

        /* Disable interrupts:
        - Tx complete interrupt
        - Rx complete interrupt
        - Fatal bus interrupt
        */
        heth->Instance->ETH_DMA_INTRENA &= (~(ETH_DMA_INTREN_NIE | ETH_DMA_INTREN_RIE | ETH_DMA_INTREN_TIE |
                                              ETH_DMA_INTREN_FBEE | ETH_DMA_INTREN_AIE | ETH_DMA_INTREN_RBUE));

        /* Disable the DMA transmission */
        heth->Instance->ETH_DMA_TXCTL &= (~ETH_DMA_TXCTL_ST);

        /* Disable the DMA reception */
        heth->Instance->ETH_DMA_RXCTL &= (~ETH_DMA_RXCTL_SR);

        /* Disable the MAC reception */
        heth->Instance->ETH_MAC_CFG &= (~ETH_MAC_CFG_RE);

        /* Set the Flush Transmit FIFO bit */
        heth->Instance->ETH_MTL_TXQOPMODE |= ETH_MTL_TXQOPMODE_FTQ;

        /* Disable the MAC reception */
        heth->Instance->ETH_MAC_CFG &= (~ETH_MAC_CFG_RE);

        /* Clear IOC bit to all Rx descriptors */
        for (descindex = 0; descindex < (uint32_t)ETH_RX_DESC_CNT; descindex++)
        {
            dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descindex];
            dmarxdesc->DESC3 &= (~ETH_DMARXNDESCRF_IOC);
        }

        heth->RxDescList.ItMode = 0U;

        heth->gState = ETH_STATE_READY;

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

/**
  * @brief  Sends an Ethernet Packet in polling mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pTxConfig: Hold the configuration of packet to be transmitted
  * @param  Timeout: timeout value
  * @retval uint32_t
  */
uint32_t ETH_Transmit(ETH_HandleTypeDef *heth, ETH_TxPacketConfigTypeDef *pTxConfig, uint32_t Timeout)
{
    uint32_t tickstart;
    ETH_DMADescTypeDef *dmatxdesc;

    if (pTxConfig == NULL)
    {
        heth->ErrorCode |= ETH_ERROR_PARAM;
    }

    if (heth->gState == ETH_STATE_STARTED)
    {
        /* Config DMA Tx descriptor by Tx Packet info */
        if (ETH_Prepare_Tx_Descriptors(heth, pTxConfig, 0) != ETH_ERROR_NONE)
        {
            /* Config DMA Tx descriptor by Tx Packet info */
            heth->ErrorCode |= ETH_ERROR_BUSY;
            return HAL_ERROR;
        }

        /* Ensure completion of descriptor preparation before transmission start */
        __DSB();

        dmatxdesc = (ETH_DMADescTypeDef *)(&heth->TxDescList)->TxDesc[heth->TxDescList.CurTxDesc];

        /* Incr current tx desc index */
        INCR_TX_DESC_INDEX(heth->TxDescList.CurTxDesc, 1U);

        tickstart = GetTick();

        /* Start transmission */
        /* issue a poll command to Tx DMA by writing address of next immediate free descriptor */
        heth->Instance->ETH_DMA_TXDESCTAILPTR = ((uint32_t)(heth->TxDescList.TxDesc[heth->TxDescList.CurTxDesc]));


        /* Wait for data to be transmitted or timeout occurred */
        while ((dmatxdesc->DESC3 & ETH_DMATXNDESCWBF_OWN) != (uint32_t)0U)
        {
            if ((heth->Instance->ETH_DMA_STU & ETH_DMA_STU_FBE) != (uint32_t)0U)
            {
                heth->ErrorCode |= ETH_ERROR_DMA;
                heth->DMAErrorCode = heth->Instance->ETH_DMA_STU;
                return HAL_ERROR;
            }


            /* Check for the Timeout */
            //if (Timeout != MAX_DELAY)
            if (Timeout != 0xFFFFFFFFU)
            {
                if (((GetTick() - tickstart) > Timeout) || (Timeout == 0U))
                {
                    heth->ErrorCode |= ETH_ERROR_TIMEOUT;
                    /* Clear TX descriptor so that we can proceed */
                    dmatxdesc->DESC3 = (ETH_DMATXNDESCWBF_FD | ETH_DMATXNDESCWBF_LD);
                }
            }
        }
        /* Return function status */
        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

/**
  * @brief  Sends an Ethernet Packet in interrupt mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pTxConfig: Hold the configuration of packet to be transmitted
  * @retval uint32_t
  */
uint32_t ETH_Transmit_IT(ETH_HandleTypeDef *heth, ETH_TxPacketConfigTypeDef *pTxConfig)
{
    if (pTxConfig == NULL)
    {
        heth->ErrorCode |= ETH_ERROR_PARAM;
        //return ERROR;
        return HAL_ERROR;
    }

    if (heth->gState == ETH_STATE_STARTED)
    {
        /* Save the packet pointer to release.  */
        heth->TxDescList.CurrentPacketAddress = (uint32_t *)pTxConfig->pData;

        /* Config DMA Tx descriptor by Tx Packet info */
        if (ETH_Prepare_Tx_Descriptors(heth, pTxConfig, 1) != ETH_ERROR_NONE)
        {
            heth->ErrorCode |= ETH_ERROR_BUSY;
            return HAL_ERROR;
        }

        /* Ensure completion of descriptor preparation before transmission start */
        __DSB();

        /* Incr current tx desc index */
        INCR_TX_DESC_INDEX(heth->TxDescList.CurTxDesc, 1U);

        /* Start transmission */
        /* issue a poll command to Tx DMA by writing address of next immediate free descriptor */
        heth->Instance->ETH_DMA_TXDESCTAILPTR = ((uint32_t)(heth->TxDescList.TxDesc[heth->TxDescList.CurTxDesc]));

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

/**
  * @brief  Read a received packet.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pAppBuff: Pointer to an application buffer to receive the packet.
  * @retval uint32_t
  */
uint32_t ETH_ReadData(ETH_HandleTypeDef *heth, void **pAppBuff)
{
    uint32_t descidx;
    ETH_DMADescTypeDef *dmarxdesc;
    uint32_t desccnt = 0U;
    uint32_t desccntmax;
    uint32_t bufflength;
    uint8_t rxdataready = 0U;

    if (pAppBuff == NULL)
    {
        heth->ErrorCode |= ETH_ERROR_PARAM;
        return HAL_ERROR;
    }

    if (heth->gState != ETH_STATE_STARTED)
    {
        return HAL_ERROR;
    }

    descidx = heth->RxDescList.RxDescIdx;
    dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descidx];
    desccntmax = ETH_RX_DESC_CNT - heth->RxDescList.RxBuildDescCnt;

    /* Check if descriptor is not owned by DMA */
    while ((((dmarxdesc->DESC3)&ETH_DMARXNDESCWBF_OWN) == (uint32_t)(0x0U)) && (desccnt < desccntmax) && (rxdataready == 0U))
    {
        if (((dmarxdesc->DESC3)&ETH_DMARXNDESCWBF_CTXT) != (uint32_t)(0x0U))
        {
            /* Get timestamp high */
            heth->RxDescList.TimeStamp.TimeStampHigh = dmarxdesc->DESC1;
            /* Get timestamp low */
            heth->RxDescList.TimeStamp.TimeStampLow  = dmarxdesc->DESC0;
        }

        if ((((dmarxdesc->DESC3)&ETH_DMARXNDESCWBF_FD) != (uint32_t)(0x0U)) || (heth->RxDescList.pRxStart != NULL))
        {
            /* Check if first descriptor */
            if (((dmarxdesc->DESC3)&ETH_DMARXNDESCWBF_FD) != (uint32_t)(0x0U))
            {
                heth->RxDescList.RxDescCnt = 0;
                heth->RxDescList.RxDataLength = 0;
            }

            /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
            bufflength = ((dmarxdesc->DESC3) & ETH_DMARXNDESCWBF_PL) - heth->RxDescList.RxDataLength;

            /* Check if last descriptor */
            if (((dmarxdesc->DESC3)&ETH_DMARXNDESCWBF_LD) != (uint32_t)(0x0U))
            {
                /* Save Last descriptor index */
                heth->RxDescList.pRxLastRxDesc = dmarxdesc->DESC3;

                /* Packet ready */
                rxdataready = 1;
            }

            /* Link data */
            WRITE_REG(dmarxdesc->BackupAddr0, dmarxdesc->DESC0);
            /* Link callback */
            ETH_RxLinkCallback(&heth->RxDescList.pRxStart, &heth->RxDescList.pRxEnd,
                               (uint8_t *)dmarxdesc->BackupAddr0, (uint16_t) bufflength);

            heth->RxDescList.RxDescCnt++;

            heth->RxDescList.RxDataLength += bufflength;

            /* Clear buffer pointer */
            dmarxdesc->BackupAddr0 = 0;
        }

        /* Increment current rx descriptor index */
        INCR_RX_DESC_INDEX(descidx, 1U);
        /* Get current descriptor address */
        dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descidx];
        desccnt++;
    }

    heth->RxDescList.RxBuildDescCnt += desccnt;
    if ((heth->RxDescList.RxBuildDescCnt) != 0U)
    {
        /* Update Descriptors */
        ETH_UpdateDescriptor(heth);
    }

    heth->RxDescList.RxDescIdx = descidx;

    if (rxdataready == 1U)
    {
        /* Return received packet */
        *pAppBuff = heth->RxDescList.pRxStart;
        /* Reset first element */
        heth->RxDescList.pRxStart = NULL;

        return HAL_OK;
    }

    return HAL_ERROR;
}

/**
  * @brief  This function gives back Rx Desc of the last received Packet
  *         to the DMA, so heth DMA will be able to use these descriptors
  *         to receive next Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval void
  */
static void ETH_UpdateDescriptor(ETH_HandleTypeDef *heth)
{
    uint32_t descidx;
    uint32_t tailidx;
    uint32_t desccount;
    ETH_DMADescTypeDef *dmarxdesc;
    uint8_t *buff = NULL;
    uint8_t allocStatus = 1U;

    descidx = heth->RxDescList.RxBuildDescIdx;
    dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descidx];
    desccount = heth->RxDescList.RxBuildDescCnt;

    while ((desccount > 0U) && (allocStatus != 0U))
    {
        /* Check if a buffer's attached the descriptor */
        if ((dmarxdesc->BackupAddr0) == 0U)
        {
            /*Allocate callback*/
            ETH_RxAllocateCallback(&buff);
            if (buff == NULL)
            {
                allocStatus = 0U;
            }
            else
            {
                dmarxdesc->BackupAddr0 = (uint32_t)buff;
                dmarxdesc->DESC0 = (uint32_t)buff;
            }
        }

        if (allocStatus != 0U)
        {
            if (heth->RxDescList.ItMode != 0U)
            {
                dmarxdesc->DESC3 |= (ETH_DMARXNDESCRF_OWN | ETH_DMARXNDESCRF_BUF1V | ETH_DMARXNDESCRF_IOC);
            }
            else
            {
                dmarxdesc->DESC3 |= (ETH_DMARXNDESCRF_OWN | ETH_DMARXNDESCRF_BUF1V);
            }

            /* Increment current rx descriptor index */
            INCR_RX_DESC_INDEX(descidx, 1U);
            /* Get current descriptor address */
            dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descidx];
            desccount--;
        }
    }

    if (heth->RxDescList.RxBuildDescCnt != desccount)
    {
        /* Set the tail pointer index */
        tailidx = (descidx + 1U) % ETH_RX_DESC_CNT;

        /* DMB instruction to avoid race condition */
        __DMB();

        /* Set the Tail pointer address */
        heth->Instance->ETH_DMA_RXDESCTAILPTR |= ((uint32_t)(heth->Init.RxDesc + (tailidx)));

        heth->RxDescList.RxBuildDescIdx = descidx;
        heth->RxDescList.RxBuildDescCnt = desccount;
    }
}

/**
  * @brief  Register the Rx alloc callback.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  rxAllocateCallback: pointer to function to alloc buffer
  * @retval int
  */
uint32_t ETH_RegisterRxAllocateCallback(ETH_HandleTypeDef *heth,
                                        pETH_rxAllocateCallbackTypeDef rxAllocateCallback)
{
    if (rxAllocateCallback == NULL)
    {
        /* No buffer to save */
        //return ERROR;
        return HAL_ERROR;
    }

    /* Set function to allocate buffer */
    heth->rxAllocateCallback = rxAllocateCallback;

    return HAL_OK;
}

/**
  * @brief  Unregister the Rx alloc callback.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval void
  */
void ETH_UnRegisterRxAllocateCallback(ETH_HandleTypeDef *heth)
{
    /* Set function to allocate buffer */
    heth->rxAllocateCallback = ETH_RxAllocateCallback;
}

/**
  * @brief  Rx Allocate callback.
  * @param  buff: pointer to allocated buffer
  * @retval None
  */

/*The definition belowed need to exit at ft32f4xx_def.h file*/
/*TODO*/


//__weak void ETH_RxAllocateCallback(uint8_t **buff)
void __attribute__((weak)) ETH_RxAllocateCallback(uint8_t **buff)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(buff);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_RxAllocateCallback could be implemented in the user file
    */
}


/**
  * @brief  Rx Link callback.
  * @param  pStart: pointer to packet start
  * @param  pEnd: pointer to packet end
  * @param  buff: pointer to received data
  * @param  Length: received data length
  * @retval None
  */
//__weak void ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length)
void __attribute__((weak)) ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(pStart);
    UNUSED(pEnd);
    UNUSED(buff);
    UNUSED(Length);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_RxLinkCallback could be implemented in the user file
    */
}

/**
  * @brief  Set the Rx link data function.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  rxLinkCallback: pointer to function to link data
  * @retval int
  */
uint32_t ETH_RegisterRxLinkCallback(ETH_HandleTypeDef *heth, pETH_rxLinkCallbackTypeDef rxLinkCallback)
{
    if (rxLinkCallback == NULL)
    {
        /* No buffer to save */
        //return ERROR;
        return HAL_ERROR;
    }

    /* Set function to link data */
    heth->rxLinkCallback = rxLinkCallback;

    return HAL_OK;
}

/**
  * @brief  Unregister the Rx link callback.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval void
  */
void ETH_UnRegisterRxLinkCallback(ETH_HandleTypeDef *heth)
{
    /* Set function to allocate buffer */
    heth->rxLinkCallback = ETH_RxLinkCallback;
}

/**
  * @brief  Get the error state of the last received packet.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pErrorCode: pointer to uint32_t to hold the error code
  * @retval void
  */
void ETH_GetRxDataErrorCode(const ETH_HandleTypeDef *heth, uint32_t *pErrorCode)
{
    /* Get error bits. */
    *pErrorCode = ((heth->RxDescList.pRxLastRxDesc) & ETH_DMARXNDESCWBF_ERRORS_MASK);
}

/**
  * @brief  Set the Tx free function.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  txFreeCallback: pointer to function to release the packet
  * @retval int
  */
uint32_t ETH_RegisterTxFreeCallback(ETH_HandleTypeDef *heth, pETH_txFreeCallbackTypeDef txFreeCallback)
{
    if (txFreeCallback == NULL)
    {
        /* No buffer to save */
        //return ERROR;
        return HAL_ERROR;
    }

    /* Set function to free transmmitted packet */
    heth->txFreeCallback = txFreeCallback;

    return HAL_OK;
}

/**
  * @brief  Unregister the Tx free callback.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval void
  */
void ETH_UnRegisterTxFreeCallback(ETH_HandleTypeDef *heth)
{
    /* Set function to allocate buffer */
    heth->txFreeCallback = ETH_TxFreeCallback;

    //return OK;
}

/**
  * @brief  Tx Free callback.
  * @param  buff: pointer to buffer to free
  * @retval None
  */
//__weak void ETH_TxFreeCallback(uint32_t *buff)
void __attribute__((weak)) ETH_TxFreeCallback(uint32_t *buff)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(buff);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_TxFreeCallback could be implemented in the user file
    */
}

/**
  * @brief  Release transmitted Tx packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval void
  */
void ETH_ReleaseTxPacket(ETH_HandleTypeDef *heth)
{
    ETH_TxDescListTypeDef *dmatxdesclist = &heth->TxDescList;
    uint32_t numOfBuf =  dmatxdesclist->BuffersInUse;
    uint32_t idx =       dmatxdesclist->releaseIndex;
    uint8_t pktTxStatus = 1U;
    uint8_t pktInUse;
#ifdef ETH_USE_PTP
    ETH_TimeStampTypeDef *timestamp = &heth->TxTimestamp;
#endif /* ETH_USE_PTP */

    /* Loop through buffers in use.  */
    while ((numOfBuf != 0U) && (pktTxStatus != 0U))
    {
        pktInUse = 1U;
        numOfBuf--;
        /* If no packet, just examine the next packet.  */
        if (dmatxdesclist->PacketAddress[idx] == NULL)
        {
            /* No packet in use, skip to next.  */
            INCR_TX_DESC_INDEX(idx, 1U);
            pktInUse = 0U;
        }

        if (pktInUse != 0U)
        {
            /* Determine if the packet has been transmitted.  */
            if ((heth->Init.TxDesc[idx].DESC3 & ETH_DMATXNDESCRF_OWN) == 0U)
            {
#ifdef ETH_USE_PTP
                /* Disable Ptp transmission */
                heth->Init.TxDesc[idx].DESC3 &= (~(0x40000000U));

                if ((heth->Init.TxDesc[idx].DESC3 & ETH_DMATXNDESCWBF_LD)
                        && (heth->Init.TxDesc[idx].DESC3 & ETH_DMATXNDESCWBF_TTSS))
                {
                    /* Get timestamp low */
                    timestamp->TimeStampLow = heth->Init.TxDesc[idx].DESC0;
                    /* Get timestamp high */
                    timestamp->TimeStampHigh = heth->Init.TxDesc[idx].DESC1;
                }
                else
                {
                    timestamp->TimeStampHigh = timestamp->TimeStampLow = UINT32_MAX;
                }

                /* Handle Ptp */
                if (timestamp->TimeStampHigh != UINT32_MAX && timestamp->TimeStampLow != UINT32_MAX)
                {
                    ETH_TxPtpCallback(dmatxdesclist->PacketAddress[idx], timestamp);
                }

#endif /* ETH_USE_PTP */

                /* Release the packet.  */
                ETH_TxFreeCallback(dmatxdesclist->PacketAddress[idx]);

                /* Clear the entry in the in-use array.  */
                dmatxdesclist->PacketAddress[idx] = NULL;

                /* Update the transmit relesae index and number of buffers in use.  */
                INCR_TX_DESC_INDEX(idx, 1U);
                dmatxdesclist->BuffersInUse = numOfBuf;
                dmatxdesclist->releaseIndex = idx;
            }
            else
            {
                /* Get out of the loop!  */
                pktTxStatus = 0U;
            }
        }
    }
    //return HAL_OK;
}

#ifdef ETH_USE_PTP
/**
  * @brief  Set the Ethernet PTP configuration.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  ptpconfig: pointer to a ETH_PTP_ConfigTypeDef structure that contains
  *         the configuration information for PTP
  * @retval int
  */
uint32_t ETH_PTP_SetConfig(ETH_HandleTypeDef *heth, ETH_PTP_ConfigTypeDef *ptpconfig)
{
    uint32_t tmpTSCR;
    ETH_TimeTypeDef time;

    if (ptpconfig == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    tmpTSCR = ptpconfig->Timestamp |
              ((uint32_t)ptpconfig->TimestampUpdate << ETH_PTP_TSCTL_TSUPDT_Pos) |
              ((uint32_t)ptpconfig->TimestampAll << ETH_PTP_TSCTL_TSENALL_Pos) |
              ((uint32_t)ptpconfig->TimestampRolloverMode << ETH_PTP_TSCTL_TSCTRLSSR_Pos) |
              ((uint32_t)ptpconfig->TimestampV2 << ETH_PTP_TSCTL_TSVER2ENA_Pos) |
              ((uint32_t)ptpconfig->TimestampEthernet << ETH_PTP_TSCTL_TSIPENA_Pos) |
              ((uint32_t)ptpconfig->TimestampIPv6 << ETH_PTP_TSCTL_TSIPV6ENA_Pos) |
              ((uint32_t)ptpconfig->TimestampIPv4 << ETH_PTP_TSCTL_TSIPV4ENA_Pos) |
              ((uint32_t)ptpconfig->TimestampEvent << ETH_PTP_TSCTL_TSEVNTENA_Pos) |
              ((uint32_t)ptpconfig->TimestampMaster << ETH_PTP_TSCTL_TSENMACADDR_Pos) |
              ((uint32_t)ptpconfig->TimestampSnapshots << ETH_PTP_TSCTL_SNAPTYPSEL_Pos) |
              ((uint32_t)ptpconfig->TimestampFilter << ETH_PTP_TSCTL_TSENMACADDR_Pos) |
              ((uint32_t)ptpconfig->TimestampChecksumCorrection << ETH_PTP_TSCTL_CSC_Pos) |
              ((uint32_t)ptpconfig->TimestampStatusMode << ETH_PTP_TSCTL_TXTSSISM_Pos);

    /* Write to PTP_TSCTL */
    heth->Instance->ETH_PTP_TSCTL = (((heth->Instance->ETH_PTP_TSCTL) & ((~ETH_PTP_TSCTL_MASK))) | (tmpTSCR));

    /* Enable Timestamp */
    heth->Instance->ETH_PTP_TSCTL |= ETH_PTP_TSCTL_TSENA;
    heth->Instance->ETH_PTP_SUBSECINR = (ptpconfig->TimestampSubsecondInc);
    heth->Instance->ETH_PTP_TSADD = ptpconfig->TimestampAddend;

    /* Enable Timestamp */
    if (ptpconfig->TimestampAddendUpdate == ENABLE)
    {
        heth->Instance->ETH_PTP_TSCTL |= ETH_PTP_TSCTL_TSADDREG;
        while (((heth->Instance->ETH_PTP_TSCTL)&ETH_PTP_TSCTL_TSADDREG) != 0)
        {

        }
    }

    /* Ptp Init */
    heth->Instance->ETH_PTP_TSCTL |= ETH_PTP_TSCTL_TSINIT;

    /* Set PTP Configuration done */
    heth->IsPtpConfigured = ETH_PTP_CONFIGURED;

    /* Set Seconds */
    time.Seconds = heth->Instance->ETH_PTP_SYSTMSEC;

    /* Set NanoSeconds */
    time.NanoSeconds = heth->Instance->ETH_PTP_SYSTMNSEC;

    ETH_PTP_SetTime(heth, &time);

    return HAL_OK;
}

/**
  * @brief  Get the Ethernet PTP configuration.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  ptpconfig: pointer to a ETH_PTP_ConfigTypeDef structure that contains
  *         the configuration information for PTP
  * @retval int
  */

uint32_t ETH_PTP_GetConfig(ETH_HandleTypeDef *heth, ETH_PTP_ConfigTypeDef *ptpconfig)
{
    if (ptpconfig == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }
    ptpconfig->Timestamp = ((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSENA);

    ptpconfig->TimestampUpdate = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSCFUPDT)\
                                   >> ETH_PTP_TSCTL_TSCFUPDT_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampAll = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSENALL)\
                                >> ETH_PTP_TSCTL_TSENALL_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampRolloverMode = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSCTRLSSR)\
                                         >> ETH_PTP_TSCTL_TSCTRLSSR_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampV2 = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSVER2ENA)\
                               >> ETH_PTP_TSCTL_TSVER2ENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampEthernet = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSIPENA)\
                                     >> ETH_PTP_TSCTL_TSIPENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampIPv6 = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSIPV6ENA)\
                                 >> ETH_PTP_TSCTL_TSIPV6ENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampIPv4 = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSIPV4ENA)\
                                 >> ETH_PTP_TSCTL_TSIPV4ENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampEvent = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSEVNTENA)\
                                  >> ETH_PTP_TSCTL_TSEVNTENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampMaster = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSMSTRENA)\
                                   >> ETH_PTP_TSCTL_TSMSTRENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampSnapshots = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSMSTRENA)\
                                      >> ETH_PTP_TSCTL_TSMSTRENA_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampFilter = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TSENMACADDR)\
                                   >> ETH_PTP_TSCTL_TSENMACADDR_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampChecksumCorrection = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_CSC)\
        >> ETH_PTP_TSCTL_CSC_Pos) > 0U) ? ENABLE : DISABLE;

    ptpconfig->TimestampStatusMode = ((((heth->Instance->ETH_PTP_TSCTL) & ETH_PTP_TSCTL_TXTSSISM)\
                                       >> ETH_PTP_TSCTL_TXTSSISM_Pos) > 0U) ? ENABLE : DISABLE;

    return HAL_OK;
}

/**
  * @brief  Set Seconds and Nanoseconds for the Ethernet PTP registers.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  time: pointer to a ETH_TimeTypeDef structure that contains
  *         time to set
  * @retval int
  */
uint32_t ETH_PTP_SetTime(ETH_HandleTypeDef *heth, ETH_TimeTypeDef *time)
{
    if (heth->IsPtpConfigured == ETH_PTP_CONFIGURED)
    {
        /* Set Seconds */
        heth->Instance->ETH_PTP_SYSTMSECUPDT = time->Seconds;

        /* Set NanoSeconds */
        heth->Instance->ETH_PTP_SYSTMNSECUPDT = time->NanoSeconds;

        /* the system time is updated */
        heth->Instance->ETH_PTP_TSCTL = ETH_PTP_TSCTL_TSUPDT;
    }
    else
    {
        /* Return function status */
        //return ERROR;
        return HAL_ERROR;
    }
}

/**
  * @brief  Get Seconds and Nanoseconds for the Ethernet PTP registers.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  time: pointer to a ETH_TimeTypeDef structure that contains
  *         time to get
  * @retval int
  */
uint32_t ETH_PTP_GetTime(ETH_HandleTypeDef *heth, ETH_TimeTypeDef *time)
{
    if (heth->IsPtpConfigured == ETH_PTP_CONFIGURED)
    {
        /* Get Seconds */
        time->Seconds = heth->Instance->ETH_PTP_SYSTMSEC;
        /* Get NanoSeconds */
        time->NanoSeconds = heth->Instance->ETH_PTP_SYSTMNSEC;
    }
    else
    {
        /* Return function status */
        //return ERROR;
        return HAL_ERROR;
    }
}

/**
  * @brief  Update time for the Ethernet PTP registers.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  timeoffset: pointer to a ETH_PtpUpdateTypeDef structure that contains
  *         the time update information
  * @retval int
  */
uint32_t ETH_PTP_AddTimeOffset(ETH_HandleTypeDef *heth, ETH_PtpUpdateTypeDef ptpoffsettype,
                               ETH_TimeTypeDef *timeoffset)
{
    if (heth->IsPtpConfigured == ETH_PTP_CONFIGURED)
    {
        if (ptpoffsettype ==  ETH_PTP_NEGATIVE_UPDATE)
        {
            /* Set Seconds update */
            heth->Instance->ETH_PTP_SYSTMSECUPDT = ETH_MACSTSUR_VALUE - timeoffset->Seconds + 1U;

            if (((heth->Instance->ETH_PTP_TSCTL)&ETH_PTP_TSCTL_TSCTRLSSR) == ETH_PTP_TSCTL_TSCTRLSSR)
            {
                /* Set nanoSeconds update */
                heth->Instance->ETH_PTP_SYSTMNSECUPDT = ETH_MACSTNUR_VALUE - timeoffset->NanoSeconds;
            }
            else
            {
                /* Set nanoSeconds update */
                heth->Instance->ETH_PTP_SYSTMNSECUPDT = ETH_MACSTSUR_VALUE - timeoffset->NanoSeconds + 1U;
            }
        }
        else
        {
            /* Set Seconds update */
            heth->Instance->ETH_PTP_SYSTMSECUPDT = timeoffset->Seconds;
            /* Set nanoSeconds update */
            heth->Instance->ETH_PTP_SYSTMNSECUPDT = timeoffset->NanoSeconds;
        }

        heth->Instance->ETH_PTP_TSCTL |= ETH_PTP_TSCTL_TSUPDT;

        return HAL_OK;
    }
    else
    {
        /* Return function status */
        //return ERROR;
        return HAL_ERROR;
    }
}

/**
  * @brief  Insert Timestamp in transmission.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval int
  */
uint32_t ETH_PTP_InsertTxTimestamp(ETH_HandleTypeDef *heth)
{
    ETH_TxDescListTypeDef *dmatxdesclist = &heth->TxDescList;
    uint32_t descidx = dmatxdesclist->CurTxDesc;
    ETH_DMADescTypeDef *dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];

    if (heth->IsPtpConfigured == ETH_PTP_CONFIGURED)
    {
        /* Enable Time Stamp transmission */
        dmatxdesc->DESC2 |= ETH_DMATXNDESCRF_TTSE;

        return HAL_OK;
    }
    else
    {
        /* Return function status */
        // return ERROR;
        return HAL_ERROR;
    }
}

/**
  * @brief  Get transmission timestamp.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  timestamp: pointer to ETH_TIMESTAMPTypeDef structure that contains
  *         transmission timestamp
  * @retval int
  */
uint32_t ETH_PTP_GetTxTimestamp(ETH_HandleTypeDef *heth, ETH_TimeStampTypeDef *timestamp)
{
    ETH_TxDescListTypeDef *dmatxdesclist = &heth->TxDescList;
    uint32_t idx =       dmatxdesclist->releaseIndex;
    ETH_DMADescTypeDef *dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[idx];

    if (heth->IsPtpConfigured == ETH_PTP_CONFIGURED)
    {
        /* Get timestamp low */
        timestamp->TimeStampLow = dmatxdesc->DESC0;
        /* Get timestamp high */
        timestamp->TimeStampHigh = dmatxdesc->DESC1;

        return HAL_OK;
    }
    else
    {
        /* Return function status */
        //return ERROR;
        return HAL_ERROR;
    }
}

/**
  * @brief  Get receive timestamp.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  timestamp: pointer to ETH_TIMESTAMPTypeDef structure that contains
  *         receive timestamp
  * @retval int
  */
uint32_t ETH_PTP_GetRxTimestamp(ETH_HandleTypeDef *heth, ETH_TimeStampTypeDef *timestamp)
{
    if (heth->IsPtpConfigured == ETH_PTP_CONFIGURED)
    {
        /* Get timestamp low */
        timestamp->TimeStampLow = heth->RxDescList.TimeStamp.TimeStampLow;
        /* Get timestamp high */
        timestamp->TimeStampHigh = heth->RxDescList.TimeStamp.TimeStampHigh;

        return HAL_OK;
    }
    else
    {
        /* Return function status */
        //return ERROR;
        return HAL_ERROR;
    }
}

/**
  * @brief  Register the Tx Ptp callback.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  txPtpCallback: Function to handle Ptp transmission
  * @retval int
  */
uint32_t ETH_RegisterTxPtpCallback(ETH_HandleTypeDef *heth, pETH_txPtpCallbackTypeDef txPtpCallback)
{
    if (txPtpCallback == NULL)
    {
        /* No buffer to save */
        //return ERROR;
        return HAL_ERROR;
    }
    /* Set Function to handle Tx Ptp */
    heth->txPtpCallback = txPtpCallback;

    return HAL_OK;
}

/**
  * @brief  Unregister the Tx Ptp callback.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval int
  */
uint32_t ETH_UnRegisterTxPtpCallback(ETH_HandleTypeDef *heth)
{
    /* Set function to allocate buffer */
    heth->txPtpCallback = ETH_TxPtpCallback;

    //return OK;
    return HAL_OK;
}

/**
  * @brief  Tx Ptp callback.
  * @param  buff: pointer to application buffer
  * @param  timestamp: pointer to ETH_TimeStampTypeDef structure that contains
  *         transmission timestamp
  * @retval None
  */
//__weak void ETH_TxPtpCallback(uint32_t *buff, ETH_TimeStampTypeDef *timestamp)
void __attribute__((weak)) ETH_TxPtpCallback(uint32_t *buff, ETH_TimeStampTypeDef *timestamp)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(buff);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_TxPtpCallback could be implemented in the user file
    */
}
#endif  /* ETH_USE_PTP */

/**
  * @brief  This function handles heth interrupt request.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval void
  */
void ETH_IRQHandler(ETH_HandleTypeDef *heth)
{
    uint32_t mac_flag = (heth->Instance->ETH_MAC_IRSTU);
    uint32_t dma_flag = (heth->Instance->ETH_DMA_STU);
    uint32_t dma_itsource = (heth->Instance->ETH_DMA_INTRENA);
    uint32_t exti_flag = (EXTI->PR);

    /* Packet received */
    if (((dma_flag & ETH_DMA_STU_RI) != 0U) && ((dma_itsource & ETH_DMA_INTREN_RIE) != 0U))
    {
        /* Clear the heth DMA Rx IT pending bits */
        heth->Instance->ETH_DMA_STU = (ETH_DMA_STU_RI | ETH_DMA_STU_NIS);
        /* Receive complete callback */
        ETH_RxCpltCallback(heth);
    }

    /* Packet transmitted */
    if (((dma_flag & ETH_DMA_STU_TI) != 0U) && ((dma_itsource & ETH_DMA_INTREN_TIE) != 0U))
    {
        /* Clear the heth DMA Tx IT pending bits */
        heth->Instance->ETH_DMA_STU = (ETH_DMA_STU_TI | ETH_DMA_STU_NIS);

        ETH_TxCpltCallback(heth);
    }

    /* heth DMA Error */
    if (((dma_flag & ETH_DMA_STU_AIS) != 0U) && ((dma_itsource & ETH_DMA_INTREN_AIE) != 0U))
    {
        heth->ErrorCode |= ETH_ERROR_DMA;
        /* if fatal bus error occurred */
        if ((dma_flag & ETH_DMA_STU_FBE) != 0U)
        {
            /* Get DMA error code  */
            heth->DMAErrorCode = ((heth->Instance->ETH_DMA_STU) & (ETH_DMA_STU_FBE | ETH_DMA_STU_TPS | ETH_DMA_STU_RPS));

            /* Disable all interrupts */
            __ETH_DMA_DISABLE_IT(heth, ETH_DMA_INTREN_NIE | ETH_DMA_INTREN_AIE);

            /* Set state to ERROR */
            heth->gState = ETH_STATE_ERROR;
        }
        else
        {
            /* Get DMA error status  */
            heth->DMAErrorCode = ((heth->Instance->ETH_DMA_STU) & (ETH_DMA_STU_CDE | ETH_DMA_STU_ETI | ETH_DMA_STU_RWT |
                                  ETH_DMA_STU_RBU | ETH_DMA_STU_AIS));

            /* Clear the interrupt summary flag */
            __ETH_DMA_CLEAR_IT(heth, (ETH_DMA_STU_CDE | ETH_DMA_STU_ETI | ETH_DMA_STU_RWT |
                                      ETH_DMA_STU_RBU | ETH_DMA_STU_AIS));
        }

        /* Ethernet DMA Error callback */
        ETH_ErrorCallback(heth);
    }

    /* heth MAC Error IT */
    if (((mac_flag & ETH_MAC_IREN_RXSTSIE) == ETH_MAC_IREN_RXSTSIE) || \
            ((mac_flag & ETH_MAC_IREN_TXSTSIE) == ETH_MAC_IREN_TXSTSIE))
    {
        heth->ErrorCode |= ETH_ERROR_MAC;

        /* Get MAC Rx Tx status and clear Status register pending bit */
        heth->MACErrorCode = (heth->Instance->ETH_MAC_RXTXSTU);

        heth->gState = ETH_STATE_ERROR;

        /* Ethernet Error callback */
        ETH_ErrorCallback(heth);

        heth->MACErrorCode = (uint32_t)(0x0U);
    }

    /* heth PMT IT */
    if ((mac_flag & ETH_MAC_PMT_IT) != 0U)
    {
        /* Get MAC Wake-up source and clear the status register pending bit */
        heth->MACWakeUpEvent = ((heth->Instance->ETH_MAC_PMTCTLSTU) & (ETH_MAC_PMTCTLSTU_RWKPRCVD | ETH_MAC_PMTCTLSTU_MGKPRCVD));

        /* Ethernet PMT callback */
        ETH_PMTCallback(heth);

        heth->MACWakeUpEvent = (uint32_t)(0x0U);
    }

    /* check heth WAKEUP exti flag */
    if ((exti_flag & ETH_WAKEUP_EXTI_LINE) != 0U)
    {
        /* Clear heth WAKEUP Exti pending bit */
        __ETH_WAKEUP_EXTI_CLEAR_FLAG(ETH_WAKEUP_EXTI_LINE);

        /* heth WAKEUP callback */
        ETH_WakeUpCallback(heth);
    }
}


/**
  * @brief  Tx Transfer completed callbacks.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
//__weak void ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(heth);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_TxCpltCallback could be implemented in the user file
    */
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
//__weak void ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(heth);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_RxCpltCallback could be implemented in the user file
    */
}

/**
* @brief  Ethernet transfer error callbacks
* @param  heth: pointer to a ETH_HandleTypeDef structure that contains
*         the configuration information for ETHERNET module
* @retval None
*/
//__weak void ETH_ErrorCallback(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(heth);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_ErrorCallback could be implemented in the user file
    */
}

/**
  * @brief  Ethernet Power Management module IT callback
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
//__weak void ETH_PMTCallback(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_PMTCallback(ETH_HandleTypeDef *heth)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(heth);
    /* NOTE : This function Should not be modified, when the callback is needed,
    the ETH_PMTCallback could be implemented in the user file
    */
}

/**
  * @brief  heth WAKEUP interrupt callback
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
//__weak void ETH_WakeUpCallback(ETH_HandleTypeDef *heth)
void __attribute__((weak)) ETH_WakeUpCallback(ETH_HandleTypeDef *heth)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(heth);
    /* NOTE : This function Should not be modified, when the callback is needed,
              the ETH_WakeUpCallback could be implemented in the user file
     */
}

/**
  * @brief  Read a PHY register
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  PHYAddr: PHY port address, must be a value from 0 to 31
  * @param  PHYReg: PHY register address, must be a value from 0 to 31
  * @param  pRegValue: parameter to hold read value
  * @retval int
  */
uint32_t ETH_ReadPHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg,
                             uint32_t *pRegValue)
{
    uint32_t tickstart;
    uint32_t tmpreg;

    /* Check for the Busy flag */
    if (((heth->Instance->ETH_MAC_MDIOADDR)&ETH_MAC_MDIOADDR_GB) != (uint32_t)(0x0U))
    {
        //return ERROR;
        return HAL_ERROR;
    }

    /* Get the  MAC_MDIOADDR value */
    tmpreg = heth->Instance->ETH_MAC_MDIOADDR;

    /* Prepare the MDIO Address Register value
       - Set the PHY device address
       - Set the PHY register address
       - Set the read mode
       - Set the MII Busy bit */

    MODIFY_REG(tmpreg, ETH_MAC_MDIOADDR_PA, (PHYAddr << 21));
    MODIFY_REG(tmpreg, ETH_MAC_MDIOADDR_RDA, (PHYReg << 16));
    MODIFY_REG(tmpreg, ETH_MAC_MDIOADDR_GOC, ETH_MAC_MDIOADDR_GOC_RD);
    tmpreg |= ETH_MAC_MDIOADDR_GB;

    /* Write the result value into the MII Address register */
    WRITE_REG(heth->Instance->ETH_MAC_MDIOADDR, tmpreg);

    /*TODO*/
    tickstart = GetTick();

    /* Wait for the Busy flag */
    while (((heth->Instance->ETH_MAC_MDIOADDR)&ETH_MAC_MDIOADDR_GB) > 0U)
    {
        if (((GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
        {
            return ERROR;
        }
    }

    /* Get ETH_MAC_MDIODATA value */
    WRITE_REG(*pRegValue, (uint16_t)heth->Instance->ETH_MAC_MDIODATA);

    return HAL_OK;
}

/**
  * @brief  Writes to a PHY register.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  PHYAddr: PHY port address, must be a value from 0 to 31
  * @param  PHYReg: PHY register address, must be a value from 0 to 31
  * @param  RegValue: the value to write
  * @retval void
  */
uint32_t ETH_WritePHYRegister(const ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg,
                              uint32_t RegValue)
{
    uint32_t tickstart;
    uint32_t tmpreg;

    /* Check for the Busy flag */
    if (((heth->Instance->ETH_MAC_MDIOADDR)&ETH_MAC_MDIOADDR_GB) != (uint32_t)(0x0U))
    {
        return HAL_ERROR;
    }

    /* Get the ETH_MAC_MDIOADDR  value */
    WRITE_REG(tmpreg, heth->Instance->ETH_MAC_MDIOADDR);

    /* Prepare the MDIO Address Register value
       - Set the PHY device address
       - Set the PHY register address
       - Set the write mode
       - Set the MII Busy bit */
    MODIFY_REG(tmpreg, ETH_MAC_MDIOADDR_PA, (PHYAddr << 21));
    MODIFY_REG(tmpreg, ETH_MAC_MDIOADDR_RDA, (PHYReg << 16));
    MODIFY_REG(tmpreg, ETH_MAC_MDIOADDR_GOC, ETH_MAC_MDIOADDR_GOC_WR);
    tmpreg |= ETH_MAC_MDIOADDR_GB;

    /* Give the value to the MII data register */
    WRITE_REG(heth->Instance->ETH_MAC_MDIODATA, (uint16_t)RegValue);

    /* Write the result value into the MII Address register */
    WRITE_REG(heth->Instance->ETH_MAC_MDIOADDR, tmpreg);

    /*TODO*/
    //tickstart = GetTick();

    /* Wait for the Busy flag */
    while (((heth->Instance->ETH_MAC_MDIOADDR)&ETH_MAC_MDIOADDR_GB) > 0U)
    {
        //  if (((GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
        //  {
        //    return ERROR;
        //  }
    }

    return HAL_OK;
}
/**
  * @}
  */

/** @defgroup ETH_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   heth control functions
  *
@verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control the heth
    peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Get the configuration of the MAC and MTL subsystems.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  macconf: pointer to a ETH_MACConfigTypeDef structure that will hold
  *         the configuration of the MAC.
  * @retval int
  */
uint32_t ETH_GetMACConfig(const ETH_HandleTypeDef *heth, ETH_MACConfigTypeDef *macconf)
{
    if (macconf == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    /* Get MAC parameters */
    macconf->PreambleLength = ((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_PRELEN);
    macconf->DeferralCheck = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_DC) >> 4) > 0U) ? ENABLE : DISABLE;
    macconf->BackOffLimit = ((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_BL);
    macconf->RetryTransmission = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_DR) >> 8) == 0U) ? ENABLE : DISABLE;
    macconf->CarrierSenseDuringTransmit = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_DCRS) >> 9) == 0U) ? ENABLE : DISABLE;
    macconf->ReceiveOwn = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_DO) >> 10) == 0U) ? ENABLE : DISABLE;
    macconf->CarrierSenseBeforeTransmit = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_ECRSFD) >> 11) > 0U) ? ENABLE : DISABLE;
    macconf->LoopbackMode = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_LM) >> 12) > 0U) ? ENABLE : DISABLE;
    macconf->DuplexMode = ((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_DM);
    macconf->Speed = ((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_FES);
    macconf->JumboPacket = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_JE) >> 16) > 0U) ? ENABLE : DISABLE;
    macconf->Jabber = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_JD) >> 17) > 0U) ? ENABLE : DISABLE;
    macconf->Watchdog = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_WD) >> 19) > 0U) ? ENABLE : DISABLE;
    macconf->AutomaticPadCRCStrip = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_ACS) >> 20) > 0U) ? ENABLE : DISABLE;
    macconf->CRCStripTypePacket = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_CST) >> 21) > 0U) ? ENABLE : DISABLE;
    macconf->Support2KPacket = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_S2KP) >> 22) > 0U) ? ENABLE : DISABLE;
    macconf->GiantPacketSizeLimitControl = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_GPSLCE) >> 23) > 0U) ? ENABLE : DISABLE;
    macconf->InterPacketGapVal = ((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_IPG);
    macconf->ChecksumOffload = ((((heth->Instance->ETH_MAC_CFG)&ETH_MAC_CFG_IPC) >> 27) > 0U) ? ENABLE : DISABLE;

    macconf->GiantPacketSizeLimit = ((heth->Instance->ETH_MAC_EXTDCFG)&ETH_MAC_EXTDCFG_GPSL);
    macconf->CRCCheckingRxPackets = ((((heth->Instance->ETH_MAC_EXTDCFG)&ETH_MAC_EXTDCFG_DCRCC) >> 16) > 0U) ? ENABLE : DISABLE;
    macconf->SlowProtocolDetect = ((((heth->Instance->ETH_MAC_EXTDCFG)&ETH_MAC_EXTDCFG_SPEN) >> 17) > 0U) ? ENABLE : DISABLE;
    macconf->UnicastSlowProtocolPacketDetect = ((((heth->Instance->ETH_MAC_EXTDCFG)&ETH_MAC_EXTDCFG_USP) >> 18) > 0U) ? ENABLE : DISABLE;
    macconf->ExtendedInterPacketGap = ((((heth->Instance->ETH_MAC_EXTDCFG)&ETH_MAC_EXTDCFG_EIPGEN) >> 24) > 0U) ? ENABLE : DISABLE;
    macconf->ExtendedInterPacketGapVal = (((heth->Instance->ETH_MAC_EXTDCFG)&ETH_MAC_EXTDCFG_EIPG) >> 25);

    macconf->ProgrammableWatchdog = ((((heth->Instance->ETH_MAC_WTDTO)&ETH_MAC_WTDTO_PWE) >> 8) > 0U) ? ENABLE : DISABLE;
    macconf->WatchdogTimeout = ((heth->Instance->ETH_MAC_WTDTO)&ETH_MAC_WTDTO_WTO);

    macconf->TransmitFlowControl = ((((heth->Instance->ETH_MAC_TXFLCTL)&ETH_MAC_TXFLCTL_TFE) >> 1) > 0U) ? ENABLE : DISABLE;
    macconf->ZeroQuantaPause = ((((heth->Instance->ETH_MAC_TXFLCTL)&ETH_MAC_TXFLCTL_DZPQ) >> 7) == 0U) ? ENABLE : DISABLE;
    macconf->PauseLowThreshold = ((heth->Instance->ETH_MAC_TXFLCTL)&ETH_MAC_TXFLCTL_PLT);
    macconf->PauseTime = (((heth->Instance->ETH_MAC_TXFLCTL)&ETH_MAC_TXFLCTL_PT) >> 16);

    macconf->ReceiveFlowControl = (((heth->Instance->ETH_MAC_RXFLCTL)&ETH_MAC_RXFLCTL_RFE) > 0U) ? ENABLE : DISABLE;
    macconf->UnicastPausePacketDetect = ((((heth->Instance->ETH_MAC_RXFLCTL)&ETH_MAC_RXFLCTL_UP) >> 1) > 0U) ? ENABLE : DISABLE;

    macconf->TransmitQueueMode = ((heth->Instance->ETH_MTL_TXQOPMODE) & (ETH_MTL_TXQOPMDDE_TTC | ETH_MTL_TXQOPMDDE_TSF));

    macconf->ReceiveQueueMode = ((heth->Instance->ETH_MTL_RXQOPMODE) & (ETH_MTL_RXQOPMODE_RTC | ETH_MTL_RXQ0OPMD_RSF));
    macconf->ForwardRxUndersizedGoodPacket = ((((heth->Instance->ETH_MTL_RXQOPMODE)&ETH_MTL_RXQOPMODE_FUP) >> 3) > 0U) ? ENABLE : DISABLE;
    macconf->ForwardRxErrorPacket = ((((heth->Instance->ETH_MTL_RXQOPMODE)&ETH_MTL_RXQOPMODE_FEP) >> 4) > 0U) ? ENABLE : DISABLE;
    macconf->DropTCPIPChecksumErrorPacket = ((((heth->Instance->ETH_MTL_RXQOPMODE)&ETH_MTL_RXQOPMODE_DIS_TCP_EF) >> 6) > 0U) ? ENABLE : DISABLE;

    return HAL_OK;
}

/**
  * @brief  Get the configuration of the DMA.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  dmaconf: pointer to a ETH_DMAConfigTypeDef structure that will hold
  *         the configuration of the heth DMA.
  * @retval int
  */
uint32_t ETH_GetDMAConfig(const ETH_HandleTypeDef *heth, ETH_DMAConfigTypeDef *dmaconf)
{
    if (dmaconf == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    dmaconf->AddressAlignedBeats = ((((heth->Instance->ETH_DMA_SYSBUSMODE)&ETH_DMA_SYSBMODE_AAL) >> 12) > 0U) ? ENABLE : DISABLE;
    dmaconf->BurstMode = ((heth->Instance->ETH_DMA_SYSBUSMODE) & (ETH_DMA_SYSBMODE_FB | ETH_DMA_SYSBMODE_MB));
    dmaconf->RebuildINCRxBurst = ((((heth->Instance->ETH_DMA_SYSBUSMODE)&ETH_DMA_SYSBMODE_RB) >> 15) > 0U) ? ENABLE : DISABLE;

    dmaconf->DMAArbitration = ((heth->Instance->ETH_DMA_OPMODE) & (ETH_DMA_OPMODE_TXPR | ETH_DMA_OPMODE_PR | ETH_DMA_OPMODE_DA));

    dmaconf->PBLx8Mode = ((((heth->Instance->ETH_DMA_CTL)&ETH_DMA_CTL_8PBL) >> 16) > 0U) ? ENABLE : DISABLE;

    dmaconf->FlushRxPacket = ((((heth->Instance->ETH_DMA_RXCTL)&ETH_DMA_CH0RXCTL_RPF) >> 31) > 0U) ? ENABLE : DISABLE;
    dmaconf->RxDMABurstLength = ((heth->Instance->ETH_DMA_RXCTL)&ETH_DMA_RXCTL_RPBL);

    dmaconf->SecondPacketOperate = ((((heth->Instance->ETH_DMA_TXCTL)&ETH_DMA_CH0TXCTL_OSF) >> 4) > 0U) ? ENABLE : DISABLE;
    dmaconf->TxDMABurstLength = ((heth->Instance->ETH_DMA_TXCTL)&ETH_DMA_TXCTL_TPBL);

    return HAL_OK;
}

/**
  * @brief  Configures the Clock range of heth MDIO interface.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void ETH_SetMDIOClockRange(ETH_HandleTypeDef *heth)
{
    uint32_t hclk;
    uint32_t tmpreg;
    uint32_t tmpreg1 = 0;

    uint32_t pllp = 2;
    uint32_t pllsource = 0;
    uint32_t pllm = 2;
    uint32_t pllvco = 0;

    /* Get the ETHERNET MAC_MDIOADDR value */
    tmpreg = (heth->Instance)->ETH_MAC_MDIOADDR;

    /* Clear CSR Clock Range bits */
    tmpreg &= ~ETH_MAC_MDIOADDR_CR;

    /* Get hclk frequency value */
    //hclk = RCC_GetHCLKFreq();

    /*TODO*/
    tmpreg1 = RCC->CFGR & RCC_CFGR_SWS;
    switch (tmpreg1)
    {
    case 0x00:
        hclk = 16000000;
        break;
    case 0x04:
        hclk = 25000000;
        break;
    case 0x08:
        pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 14;
        pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

        if (pllsource != 0)
        {
            /*HSE used as PLL clock source*/
            pllvco = (25000000U / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }
        else
        {
            /*HSI used as PLL clock source*/
            pllvco = (16000000U / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }

        pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 17) + 1) * 2;
        hclk = pllvco / pllp;
    }


    /* Set CR bits depending on hclk value */
    if (hclk < 35000000U)
    {
        /* CSR Clock Range between 20-35 MHz */
        tmpreg |= (uint32_t)ETH_MAC_MDIOADDR_CR_DIV16;
    }
    else if (hclk < 60000000U)
    {
        /* CSR Clock Range between 35-60 MHz */
        tmpreg |= (uint32_t)ETH_MAC_MDIOADDR_CR_DIV26;
    }
    else if (hclk < 100000000U)
    {
        /* CSR Clock Range between 60-100 MHz */
        tmpreg |= (uint32_t)ETH_MAC_MDIOADDR_CR_DIV42;
    }
    else if (hclk < 150000000U)
    {
        /* CSR Clock Range between 100-150 MHz */
        tmpreg |= (uint32_t)ETH_MAC_MDIOADDR_CR_DIV62;
    }
    else
    {
        /* CSR Clock Range between 150-250 MHz */
        tmpreg |= (uint32_t)ETH_MAC_MDIOADDR_CR_DIV102;
    }

    /* Configure the CSR Clock Range */
    (heth->Instance)-> ETH_MAC_MDIOADDR = (uint32_t)tmpreg;
}

/**
  * @brief  Set the heth MAC (L2) Filters configuration.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pFilterConfig: pointer to a ETH_MACFilterConfigTypeDef structure that contains
  *         the configuration of the heth MAC filters.
  * @retval int
  */
uint32_t ETH_SetMACFilterConfig(ETH_HandleTypeDef *heth, const ETH_MACFilterConfigTypeDef *pFilterConfig)
{
    uint32_t filterconfig;

    if (pFilterConfig == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    filterconfig = ((uint32_t)pFilterConfig->PromiscuousMode |
                    ((uint32_t)pFilterConfig->HashUnicast << 1) |
                    ((uint32_t)pFilterConfig->HashMulticast << 2)  |
                    ((uint32_t)pFilterConfig->DestAddrInverseFiltering << 3) |
                    ((uint32_t)pFilterConfig->PassAllMulticast << 4) |
                    ((uint32_t)((pFilterConfig->BroadcastFilter == DISABLE) ? 1U : 0U) << 5) |
                    ((uint32_t)pFilterConfig->SrcAddrInverseFiltering << 8) |
                    ((uint32_t)pFilterConfig->SrcAddrFiltering << 9) |
                    ((uint32_t)pFilterConfig->HachOrPerfectFilter << 10) |
                    ((uint32_t)pFilterConfig->ReceiveAllMode << 31) |
                    pFilterConfig->ControlPacketsFilter);

    MODIFY_REG(heth->Instance->ETH_MAC_PKTFILT, ETH_MAC_PKTFILT_MASK, filterconfig);

    return HAL_OK;
}

/**
  * @brief  Get the heth MAC (L2) Filters configuration.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pFilterConfig: pointer to a ETH_MACFilterConfigTypeDef structure that will hold
  *         the configuration of the heth MAC filters.
  * @retval int
  */
uint32_t ETH_GetMACFilterConfig(const ETH_HandleTypeDef *heth, ETH_MACFilterConfigTypeDef *pFilterConfig)
{
    if (pFilterConfig == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    pFilterConfig->PromiscuousMode = (((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_PR) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->HashUnicast = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_HUC) >> 1) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->HashMulticast = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_HMC) >> 2) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->DestAddrInverseFiltering = ((((heth->Instance->ETH_MAC_PKTFILT)&
        ETH_MAC_PKTFILT_DAIF) >> 3) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->PassAllMulticast = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_PM) >> 4) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->BroadcastFilter = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_DBF) >> 5) == 0U) ? ENABLE : DISABLE;
    pFilterConfig->ControlPacketsFilter = ((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_PCF);
    pFilterConfig->SrcAddrInverseFiltering = ((((heth->Instance->ETH_MAC_PKTFILT)&
        ETH_MAC_PKTFILT_SAIF) >> 8) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->SrcAddrFiltering = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_SAF) >> 9) > 0U) ? ENABLE : DISABLE;
    pFilterConfig->HachOrPerfectFilter = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_HPF) >> 10) > 0U)
                                         ? ENABLE : DISABLE;
    pFilterConfig->ReceiveAllMode = ((((heth->Instance->ETH_MAC_PKTFILT)&ETH_MAC_PKTFILT_RA) >> 31) > 0U) ? ENABLE : DISABLE;

    return HAL_OK;
}

/**
  * @brief  Set the source MAC Address to be matched.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  AddrNbr: The MAC address to configure
  *          This parameter must be a value of the following:
  *            ETH_MAC_ADDRESS1
  *            ETH_MAC_ADDRESS2
  *            ETH_MAC_ADDRESS3
  * @param  pMACAddr: Pointer to MAC address buffer data (6 bytes)
  * @retval int
  */
uint32_t ETH_SetSourceMACAddrMatch(const ETH_HandleTypeDef *heth, uint32_t AddrNbr,
                                   const uint8_t *pMACAddr)
{
    uint32_t macaddrlr;
    uint32_t macaddrhr;

    if (pMACAddr == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    /* Get mac addr high reg offset */
    macaddrhr = ((uint32_t) & (heth->Instance->ETH_MAC_ADDRH0) + AddrNbr);
    /* Get mac addr low reg offset */
    macaddrlr = ((uint32_t) & (heth->Instance->ETH_MAC_ADDRL0) + AddrNbr);

    /* Set MAC addr bits 32 to 47 */
    (*(__IO uint32_t *)macaddrhr) = (((uint32_t)(pMACAddr[5]) << 8) | (uint32_t)pMACAddr[4]);
    /* Set MAC addr bits 0 to 31 */
    (*(__IO uint32_t *)macaddrlr) = (((uint32_t)(pMACAddr[3]) << 24) | ((uint32_t)(pMACAddr[2]) << 16) |
                                     ((uint32_t)(pMACAddr[1]) << 8) | (uint32_t)pMACAddr[0]);

    /* Enable address and set source address bit */
    (*(__IO uint32_t *)macaddrhr) |= (ETH_MAC_ADDRH_SA | ETH_MAC_ADDRH_AE);

    return HAL_OK;
}

/**
  * @brief  Set the heth Hash Table Value.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pHashTable: pointer to a table of two 32 bit values, that contains
  *         the 64 bits of the hash table.
  * @retval int
  */
uint32_t ETH_SetHashTable(ETH_HandleTypeDef *heth, uint32_t *pHashTable)
{
    if (pHashTable == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    heth->Instance->ETH_MAC_HASHTB0 = pHashTable[0];
    heth->Instance->ETH_MAC_HASHTB1 = pHashTable[1];

    //return OK;
    return HAL_OK;
}

/**
  * @brief  Set the VLAN Identifier for Rx packets
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  ComparisonBits: 12 or 16 bit comparison mode
            must be a value of @ref ETH_VLAN_Tag_Comparison
  * @param  VLANIdentifier: VLAN Identifier value
  * @retval None
  */
void ETH_SetRxVLANIdentifier(ETH_HandleTypeDef *heth, uint32_t ComparisonBits, uint32_t VLANIdentifier)
{
    if (ComparisonBits == ETH_VLANTAGCOMPARISON_16BIT)
    {
        MODIFY_REG(heth->Instance->ETH_MAC_VLANT, ETH_MAC_VLANT_VL, VLANIdentifier);
        (heth->Instance->ETH_MAC_VLANT) &= (~ETH_MAC_VLANT_ETV);
    }
    else
    {
        MODIFY_REG(heth->Instance->ETH_MAC_VLANT, ETH_MAC_VLANT_VL_VID, VLANIdentifier);
        //SET_BIT(heth->Instance->ETH_MAC_VLANT, ETH_MAC_VLANT_ETV);
        heth->Instance->ETH_MAC_VLANT |= ETH_MAC_VLANT_ETV;
    }
}

/**
  * @brief  Enters the Power down mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pPowerDownConfig: a pointer to ETH_PowerDownConfigTypeDef structure
  *         that contains the Power Down configuration
  * @retval None.
  */
void ETH_EnterPowerDownMode(ETH_HandleTypeDef *heth, const ETH_PowerDownConfigTypeDef *pPowerDownConfig)
{
    uint32_t powerdownconfig;

    powerdownconfig = (((uint32_t)pPowerDownConfig->MagicPacket << 1) |
                       ((uint32_t)pPowerDownConfig->WakeUpPacket << 2) |
                       ((uint32_t)pPowerDownConfig->GlobalUnicast << 9) |
                       ((uint32_t)pPowerDownConfig->WakeUpForward << 10) |
                       ETH_MAC_PMTCTLSTU_PWRDWN);

    /* Enable PMT interrupt */
    __ETH_MAC_ENABLE_IT(heth, ETH_MAC_IREN_PMTIE);

    MODIFY_REG(heth->Instance->ETH_MAC_PMTCTLSTU, ETH_MAC_PMTCTLSTU_MASK, powerdownconfig);
}

/**
  * @brief  Exits from the Power down mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None.
  */
void ETH_ExitPowerDownMode(ETH_HandleTypeDef *heth)
{
    /* clear wake up sources */
    heth->Instance->ETH_MAC_PMTCTLSTU &= (~(ETH_MAC_PMTCTLSTU_RWKPKTEN | ETH_MAC_PMTCTLSTU_MGKPKTEN | ETH_MAC_PMTCTLSTU_GLBLUCAST |
                                            ETH_MAC_PMTCTLSTU_RWKPFE));

    if (((heth->Instance->ETH_MAC_PMTCTLSTU) & (ETH_MAC_PMTCTLSTU_PWRDWN)) != ((uint32_t)0x0U))
    {
        /* Exit power down mode */
        (heth->Instance->ETH_MAC_PMTCTLSTU) &= (~(ETH_MAC_PMTCTLSTU_PWRDWN));
    }

    /* Disable PMT interrupt */
    __ETH_MAC_DISABLE_IT(heth, ETH_MAC_IREN_PMTIE);
}

/**
  * @brief  Set the WakeUp filter.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pFilter: pointer to filter registers values
  * @param  Count: number of filter registers, must be from 1 to 8.
  * @retval int.
  */
uint32_t ETH_SetWakeUpFilter(ETH_HandleTypeDef *heth, uint32_t *pFilter, uint32_t Count)
{
    uint32_t regindex;

    if (pFilter == NULL)
    {
        //return ERROR;
        return HAL_ERROR;
    }

    /* Reset Filter Pointer */
    (heth->Instance->ETH_MAC_PMTCTLSTU) |= (ETH_MAC_PMTCTLSTU_RWKFILTRST);

    /* Wake up packet filter config */
    for (regindex = 0; regindex < Count; regindex++)
    {
        /* Write filter regs */
        ((heth->Instance->ETH_MAC_RWKPKTFILT) &= (pFilter[regindex]));
    }

    //return OK;
    return HAL_OK;
}

/**
  * @}
  */

/** @defgroup ETH_Exported_Functions_Group4 Peripheral State and Errors functions
  *  @brief   heth State and Errors functions
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================
 [..]
   This subsection provides a set of functions allowing to return the State of
   heth communication process, return Peripheral Errors occurred during communication
   process


@endverbatim
  * @{
  */

/**
  * @brief  Returns the heth state.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL state
  */
uint32_t ETH_GetState(const ETH_HandleTypeDef *heth)
{
    return heth->gState;
}

/**
  * @brief  Returns the heth error code
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval heth Error Code
  */
uint32_t ETH_GetError(const ETH_HandleTypeDef *heth)
{
    //return heth->ErrorCode;
    return heth->ErrorCode;
}

/**
  * @brief  Returns the heth DMA error code
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval heth DMA Error Code
  */
uint32_t ETH_GetDMAError(const ETH_HandleTypeDef *heth)
{
    return heth->DMAErrorCode;
}

/**
  * @brief  Returns the heth MAC error code
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval heth MAC Error Code
  */
uint32_t ETH_GetMACError(const ETH_HandleTypeDef *heth)
{
    return heth->MACErrorCode;
}

/**
  * @brief  Returns the heth MAC WakeUp event source
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval heth MAC WakeUp event source
  */
uint32_t ETH_GetMACWakeUpSource(const ETH_HandleTypeDef *heth)
{
    return heth->MACWakeUpEvent;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup ETH_Private_Functions   heth Private Functions
  * @{
  */
uint32_t ETH_SetMACConfig(ETH_HandleTypeDef *heth,  ETH_MACConfigTypeDef *macconf)
{
    if (macconf == NULL)
    {
        return HAL_ERROR;
    }
    else
    {
        HAL_ETH_SetMACConfig(heth, macconf);

        return HAL_OK;
    }

}
static void HAL_ETH_SetMACConfig(ETH_HandleTypeDef *heth, const ETH_MACConfigTypeDef *macconf)
{
    uint32_t macregval;

    /*------------------------ ETH_MAC_CFG Configuration --------------------*/
    macregval = (macconf->InterPacketGapVal |
                 ((uint32_t)macconf->ChecksumOffload << 27) |
                 ((uint32_t)macconf->GiantPacketSizeLimitControl << 23) |
                 ((uint32_t)macconf->Support2KPacket  << 22) |
                 ((uint32_t)macconf->CRCStripTypePacket << 21) |
                 ((uint32_t)macconf->AutomaticPadCRCStrip << 20) |
                 ((uint32_t)((macconf->Watchdog == DISABLE) ? 1U : 0U) << 19) |
                 ((uint32_t)((macconf->Jabber == DISABLE) ? 1U : 0U) << 17) |
                 ((uint32_t)macconf->JumboPacket << 16) |
                 macconf->Speed |
                 macconf->DuplexMode |
                 ((uint32_t)macconf->LoopbackMode << 12) |
                 ((uint32_t)macconf->CarrierSenseBeforeTransmit << 11) |
                 ((uint32_t)((macconf->ReceiveOwn == DISABLE) ? 1U : 0U) << 10) |
                 ((uint32_t)((macconf->CarrierSenseDuringTransmit == DISABLE) ? 1U : 0U) << 9) |
                 ((uint32_t)((macconf->RetryTransmission == DISABLE) ? 1U : 0U) << 8) |
                 macconf->BackOffLimit |
                 ((uint32_t)macconf->DeferralCheck << 4) |
                 macconf->PreambleLength);

    /* Write to ETH_MAC_CFG */
    MODIFY_REG(heth->Instance->ETH_MAC_CFG, ETH_MAC_CFG_MASK, macregval);

    /*------------------------ ETH_MAC_EXTDCFG Configuration --------------------*/
    macregval = ((macconf->ExtendedInterPacketGapVal << 25) |
                 ((uint32_t)macconf->ExtendedInterPacketGap << 24) |
                 ((uint32_t)macconf->UnicastSlowProtocolPacketDetect << 18) |
                 ((uint32_t)macconf->SlowProtocolDetect << 17) |
                 ((uint32_t)((macconf->CRCCheckingRxPackets == DISABLE) ? 1U : 0U) << 16) |
                 macconf->GiantPacketSizeLimit);

    /* Write to ETH_MAC_EXTDCFG */
    MODIFY_REG(heth->Instance->ETH_MAC_EXTDCFG, ETH_MAC_EXTDCFG_MASK, macregval);

    /*------------------------ ETH_MAC_WTDTO Configuration --------------------*/
    macregval = (((uint32_t)macconf->ProgrammableWatchdog << 8) |
                 macconf->WatchdogTimeout);

    /* Write to ETH_MAC_WTDTO */
    MODIFY_REG(heth->Instance->ETH_MAC_WTDTO, ETH_MAC_WTDTO_MASK, macregval);

    /*------------------------ ETH_MAC_TXFLCTL Configuration --------------------*/
    macregval = (((uint32_t)macconf->TransmitFlowControl << 1) |
                 macconf->PauseLowThreshold |
                 ((uint32_t)((macconf->ZeroQuantaPause == DISABLE) ? 1U : 0U) << 7) |
                 (macconf->PauseTime << 16));

    /* Write to ETH_MAC_TXFLCTL */
    MODIFY_REG(heth->Instance->ETH_MAC_TXFLCTL, ETH_MAC_TXFLCTL_MASK, macregval);

    /*------------------------ ETH_MAC_RXFLCTL Configuration --------------------*/
    macregval = ((uint32_t)macconf->ReceiveFlowControl |
                 ((uint32_t)macconf->UnicastPausePacketDetect << 1));

    /* Write to ETH_MAC_RXFLCTL */
    MODIFY_REG(heth->Instance->ETH_MAC_RXFLCTL, ETH_MAC_RXFLCTL_MASK, macregval);

    /*------------------------ ETH_MTL_TXQOPMODE Configuration --------------------*/
    /* Write to ETH_MTL_TXQOPMODE */
    MODIFY_REG(heth->Instance->ETH_MTL_TXQOPMODE, ETH_MTL_TXQOPMODE_MASK, macconf->TransmitQueueMode);

    /*------------------------ ETH_MTL_RXQOPMODE Configuration --------------------*/
    macregval = (macconf->ReceiveQueueMode |
                 ((uint32_t)((macconf->DropTCPIPChecksumErrorPacket == DISABLE) ? 1U : 0U) << 6) |
                 ((uint32_t)macconf->ForwardRxErrorPacket << 4) |
                 ((uint32_t)macconf->ForwardRxUndersizedGoodPacket << 3));

    /* Write to ETH_MTL_RXQOPMODE */
    MODIFY_REG(heth->Instance->ETH_MTL_RXQOPMODE, ETH_MTL_RXQOPMODE_MASK, macregval);
}


static void ETH_SetDMAConfig(ETH_HandleTypeDef *heth, const ETH_DMAConfigTypeDef *dmaconf)
{
    uint32_t dmaregval;

    /*------------------------ETH_DMA_OPMODE  Configuration --------------------*/
    MODIFY_REG(heth->Instance->ETH_DMA_OPMODE, ETH_DMA_OPMODE_MASK, dmaconf->DMAArbitration);

    /*------------------------ETH_DMA_SYSBUSMODE_MASK  Configuration --------------------*/
    dmaregval = (((uint32_t)dmaconf->AddressAlignedBeats << 12) |
                 dmaconf->BurstMode |
                 ((uint32_t)dmaconf->RebuildINCRxBurst << 15));

    MODIFY_REG(heth->Instance->ETH_DMA_SYSBUSMODE, ETH_DMA_SYSBUSMODE_MASK, dmaregval);

    /*------------------------ ETH_DMA_CTL Configuration --------------------*/
    dmaregval = ((uint32_t)dmaconf->PBLx8Mode << 16) ;

    MODIFY_REG(heth->Instance->ETH_DMA_CTL, ETH_DMA_CTL_MASK, dmaregval);

    /*------------------------ ETH_DMA_TXCTL Configuration --------------------*/
    dmaregval = (dmaconf->TxDMABurstLength | ((uint32_t)dmaconf->SecondPacketOperate << 4));

    MODIFY_REG(heth->Instance->ETH_DMA_TXCTL, ETH_DMA_TXCTL_MASK, dmaregval);

    /*------------------------ ETH_DMA_RXCTL Configuration --------------------*/
    dmaregval = (((uint32_t)dmaconf->FlushRxPacket  << 31) | dmaconf->RxDMABurstLength);

    /* Write to ETH_DMA_RXCTL */
    MODIFY_REG(heth->Instance->ETH_DMA_RXCTL, ETH_DMA_RXCTL_MASK, dmaregval);
}

/**
  * @brief  Configures Ethernet MAC and DMA with default parameters.
  *         called by ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval none
  */
static void ETH_MACDMAConfig(ETH_HandleTypeDef *heth)
{
    ETH_MACConfigTypeDef macDefaultConf;
    ETH_DMAConfigTypeDef dmaDefaultConf;

    /*--------------- ETHERNET MAC registers default Configuration --------------*/
    macDefaultConf.AutomaticPadCRCStrip = ENABLE;
    macDefaultConf.BackOffLimit = ETH_BACKOFFLIMIT_10;
    macDefaultConf.CarrierSenseBeforeTransmit = DISABLE;
    macDefaultConf.CarrierSenseDuringTransmit = ENABLE;
    macDefaultConf.ChecksumOffload = ENABLE;
    macDefaultConf.CRCCheckingRxPackets = ENABLE;
    macDefaultConf.CRCStripTypePacket = ENABLE;
    macDefaultConf.DeferralCheck = DISABLE;
    macDefaultConf.DropTCPIPChecksumErrorPacket = ENABLE;
    macDefaultConf.DuplexMode = ETH_FULLDUPLEX_MODE;
    macDefaultConf.ExtendedInterPacketGap = DISABLE;
    macDefaultConf.ExtendedInterPacketGapVal = 0x0U;
    macDefaultConf.ForwardRxErrorPacket = DISABLE;
    macDefaultConf.ForwardRxUndersizedGoodPacket = DISABLE;
    macDefaultConf.GiantPacketSizeLimit = 0x618U;
    macDefaultConf.GiantPacketSizeLimitControl = DISABLE;
    macDefaultConf.InterPacketGapVal = ETH_INTERPACKETGAP_96BIT;
    macDefaultConf.Jabber = ENABLE;
    macDefaultConf.JumboPacket = DISABLE;
    macDefaultConf.LoopbackMode = DISABLE;
    macDefaultConf.PauseLowThreshold = ETH_PAUSELOWTHRESHOLD_MINUS_4;
    macDefaultConf.PauseTime = 0x0U;
    macDefaultConf.PreambleLength = ETH_PREAMBLELENGTH_7;
    macDefaultConf.ProgrammableWatchdog = DISABLE;
    macDefaultConf.ReceiveFlowControl = DISABLE;
    macDefaultConf.ReceiveOwn = ENABLE;
    macDefaultConf.ReceiveQueueMode = ETH_RECEIVESTOREFORWARD;
    macDefaultConf.RetryTransmission = ENABLE;
    macDefaultConf.SlowProtocolDetect = DISABLE;
    macDefaultConf.Speed = ETH_SPEED_100M;
    macDefaultConf.Support2KPacket = DISABLE;
    macDefaultConf.TransmitQueueMode = ETH_TRANSMITSTOREFORWARD;
    macDefaultConf.TransmitFlowControl = DISABLE;
    macDefaultConf.UnicastPausePacketDetect = DISABLE;
    macDefaultConf.UnicastSlowProtocolPacketDetect = DISABLE;
    macDefaultConf.Watchdog = ENABLE;
    macDefaultConf.WatchdogTimeout =  ETH_WATCHDOGTIMEOUT_2KB;
    macDefaultConf.ZeroQuantaPause = ENABLE;

    /* MAC default configuration */
    ETH_SetMACConfig(heth, &macDefaultConf);

    /*--------------- ETHERNET DMA registers default Configuration --------------*/
    dmaDefaultConf.AddressAlignedBeats = ENABLE;
    dmaDefaultConf.BurstMode = ETH_BURSTLENGTH_FIXED;
    dmaDefaultConf.DMAArbitration = ETH_DMAARBITRATION_RX1_TX1;
    dmaDefaultConf.FlushRxPacket = DISABLE;
    dmaDefaultConf.PBLx8Mode = DISABLE;
    dmaDefaultConf.RebuildINCRxBurst = DISABLE;
    dmaDefaultConf.RxDMABurstLength = ETH_RXDMABURSTLENGTH_32BEAT;
    dmaDefaultConf.SecondPacketOperate = DISABLE;
    dmaDefaultConf.TxDMABurstLength = ETH_TXDMABURSTLENGTH_32BEAT;

    /* DMA default configuration */
    ETH_SetDMAConfig(heth, &dmaDefaultConf);
}

/**
  * @brief  Initializes the DMA Tx descriptors.
  *         called by ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
static void ETH_DMATxDescListInit(ETH_HandleTypeDef *heth)
{
    ETH_DMADescTypeDef *dmatxdesc;
    uint32_t i;

    /* Fill each DMATxDesc descriptor with the right values */
    for (i = 0; i < (uint32_t)ETH_TX_DESC_CNT; i++)
    {
        dmatxdesc = heth->Init.TxDesc + i;

        WRITE_REG(dmatxdesc->DESC0, 0x0U);
        WRITE_REG(dmatxdesc->DESC1, 0x0U);
        WRITE_REG(dmatxdesc->DESC2, 0x0U);
        WRITE_REG(dmatxdesc->DESC3, 0x0U);

        WRITE_REG(heth->TxDescList.TxDesc[i], (uint32_t)dmatxdesc);

        /*TODO*/
        //printf("TxDescList TxDesc[%d] addr = %p\n",i,heth->TxDescList.TxDesc[i]);
    }

    heth->TxDescList.CurTxDesc = 0;

    /* Set Transmit Descriptor Ring Length */
    WRITE_REG(heth->Instance->ETH_DMA_TXDESCRINGLEN, (ETH_TX_DESC_CNT - 1U));

    /* Set Transmit Descriptor List Address */
    WRITE_REG(heth->Instance->ETH_DMA_TXDESCLSTADDR, (uint32_t) heth->Init.TxDesc);

    /* Set Transmit Descriptor Tail pointer */
    WRITE_REG(heth->Instance->ETH_DMA_TXDESCTAILPTR, (uint32_t) heth->Init.TxDesc);
}

/**
  * @brief  Initializes the DMA Rx descriptors in chain mode.
  *         called by ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
static void ETH_DMARxDescListInit(ETH_HandleTypeDef *heth)
{
    ETH_DMADescTypeDef *dmarxdesc;
    uint32_t i;

    for (i = 0; i < (uint32_t)ETH_RX_DESC_CNT; i++)
    {
        dmarxdesc =  heth->Init.RxDesc + i;

        WRITE_REG(dmarxdesc->DESC0, 0x0U);
        WRITE_REG(dmarxdesc->DESC1, 0x0U);
        WRITE_REG(dmarxdesc->DESC2, 0x0U);
        WRITE_REG(dmarxdesc->DESC3, 0x0U);
        WRITE_REG(dmarxdesc->BackupAddr0, 0x0U);
        WRITE_REG(dmarxdesc->BackupAddr1, 0x0U);

        /* Set Rx descritors addresses */
        WRITE_REG(heth->RxDescList.RxDesc[i], (uint32_t)dmarxdesc);

        /*TODO*/
        //printf("RxDescList RxDesc[%d] addr = %p\n",i,heth->RxDescList.RxDesc[i]);
    }

    WRITE_REG(heth->RxDescList.RxDescIdx, 0U);
    WRITE_REG(heth->RxDescList.RxDescCnt, 0U);
    WRITE_REG(heth->RxDescList.RxBuildDescIdx, 0U);
    WRITE_REG(heth->RxDescList.RxBuildDescCnt, 0U);
    WRITE_REG(heth->RxDescList.ItMode, 0U);

    /* Set Receive Descriptor Ring Length */
    WRITE_REG(heth->Instance->ETH_DMA_RXCTL2, ((uint32_t)(ETH_RX_DESC_CNT - 1U)));

    /* Set Receive Descriptor List Address */
    WRITE_REG(heth->Instance->ETH_DMA_RXDESCLSTADDR, (uint32_t) heth->Init.RxDesc);

    /* Set Receive Descriptor Tail pointer Address */
    WRITE_REG(heth->Instance->ETH_DMA_RXDESCTAILPTR, ((uint32_t)(heth->Init.RxDesc + (uint32_t)(ETH_RX_DESC_CNT - 1U))));
}

/**
  * @brief  Prepare Tx DMA descriptor before transmission.
  *         called by ETH_Transmit and ETH_Transmit_IT() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pTxConfig: Tx packet configuration
  * @param  ItMode: Enable or disable Tx EOT interrept
  * @retval Status
  */
static uint32_t ETH_Prepare_Tx_Descriptors(ETH_HandleTypeDef *heth, const ETH_TxPacketConfigTypeDef *pTxConfig,
        uint32_t ItMode)
{
    ETH_TxDescListTypeDef *dmatxdesclist = &heth->TxDescList;
    uint32_t descidx = dmatxdesclist->CurTxDesc;
    uint32_t firstdescidx = dmatxdesclist->CurTxDesc;
    uint32_t idx;
    uint32_t descnbr = 0;
    ETH_DMADescTypeDef *dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];

    ETH_BufferTypeDef  *txbuffer = pTxConfig->TxBuffer;

    /*TODO*/
    //printf("Prepare TxDESC[%d],addr=%p\n",descidx,dmatxdesclist->TxDesc[descidx]);
    //printf("ETH Buffer addr = %p\n",*txbuffer);

    uint32_t bd_count = 0;
    uint32_t primask_bit;

    /* Current Tx Descriptor Owned by DMA: cannot be used by the application  */
    if ((((dmatxdesc->DESC3)&ETH_DMATXNDESCWBF_OWN) == ETH_DMATXNDESCWBF_OWN)
            || (dmatxdesclist->PacketAddress[descidx] != NULL))
    {
        return ETH_ERROR_BUSY;
    }



    /***************************************************************************/
    /*****************    Normal descriptors configuration     *****************/
    /***************************************************************************/
    descnbr += 1U;

    /* Set header or buffer 1 address */
    WRITE_REG(dmatxdesc->DESC0, (uint32_t)txbuffer->buffer);
    /* Set header or buffer 1 Length */
    MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B1L, txbuffer->len);

    //if (READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_CSUM) != (uint32_t)RESET)
    if ((((pTxConfig->Attributes)&ETH_TX_PACKETS_FEATURES_CSUM)) != (uint32_t)(0x0U))
    {
        MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CIC, pTxConfig->ChecksumCtrl);
    }

    //if (READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_CRCPAD) != (uint32_t)RESET)
    if (((pTxConfig->Attributes)&ETH_TX_PACKETS_FEATURES_CRCPAD) != (uint32_t)(0x0U))
    {
        MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CPC, pTxConfig->CRCPadCtrl);
    }
    //}

    if (((pTxConfig->Attributes)&ETH_TX_PACKETS_FEATURES_VLANTAG) != (uint32_t)(0x0U))
    {
        /* Set Vlan Tag control */
        MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_VTIR, pTxConfig->VlanCtrl);
    }

    if (txbuffer->next != NULL)
    {
        txbuffer = txbuffer->next;
        /* Set buffer 2 address */
        WRITE_REG(dmatxdesc->DESC1, (uint32_t)txbuffer->buffer);
        /* Set buffer 2 Length */
        MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, (txbuffer->len << 16));
    }
    else
    {
        WRITE_REG(dmatxdesc->DESC1, 0x0U);
        /* Set buffer 2 Length */
        MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, 0x0U);
    }
    //if (((pTxConfig->Attributes)&ETH_TX_PACKETS_FEATURES_TSO) != (uint32_t)(0x0U))
    //{
    //  /* Set TCP Header length */
    //  MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_THL, (pTxConfig->TCPHeaderLen << 19));
    //  /* Set TCP payload length */
    //  MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TPL, pTxConfig->PayloadLen);
    //  /* Set TCP Segmentation Enabled bit */
    //  dmatxdesc->DESC3 |= ETH_DMATXNDESCRF_TSE;
    //}
    //else
    //{
    MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FL, pTxConfig->Length);

    /* Mark it as First Descriptor */
    //SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FD);
    dmatxdesc->DESC3 |= ETH_DMATXNDESCRF_FD;
    /* Mark it as NORMAL descriptor */
    //CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CTXT);
    dmatxdesc->DESC3 &= (~(ETH_DMATXNDESCRF_CTXT));
    /* Ensure rest of descriptor is written to RAM before the OWN bit */
    __DMB();
    /* set OWN bit of FIRST descriptor */
    //SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN);
    dmatxdesc->DESC3 |= ETH_DMATXNDESCRF_OWN;

    /* If source address insertion/replacement is enabled for this packet */
    if (((pTxConfig->Attributes)&ETH_TX_PACKETS_FEATURES_SAIC) != (uint32_t)(0x0U))
    {
        MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_SAIC, pTxConfig->SrcAddrCtrl);
    }

    /* only if the packet is split into more than one descriptors > 1 */
    while (txbuffer->next != NULL)
    {
        /* Clear the LD bit of previous descriptor */
        //CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_LD);
        dmatxdesc->DESC3 &= (~(ETH_DMATXNDESCRF_LD));
        /* Increment current tx descriptor index */
        INCR_TX_DESC_INDEX(descidx, 1U);
        /* Get current descriptor address */
        dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];

        /* Clear the FD bit of new Descriptor */
        //CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FD);
        dmatxdesc->DESC3 &= (~(ETH_DMATXNDESCRF_FD));

        /* Current Tx Descriptor Owned by DMA: cannot be used by the application  */
        if ((((dmatxdesc->DESC3)&ETH_DMATXNDESCRF_OWN) == ETH_DMATXNDESCRF_OWN)
                || (dmatxdesclist->PacketAddress[descidx] != NULL))
        {
            descidx = firstdescidx;
            dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];

            /* clear previous desc own bit */
            for (idx = 0; idx < descnbr; idx ++)
            {
                /* Ensure rest of descriptor is written to RAM before the OWN bit */
                __DMB();

                //CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN);
                dmatxdesc->DESC3 &= (~(ETH_DMATXNDESCRF_OWN));

                /* Increment current tx descriptor index */
                INCR_TX_DESC_INDEX(descidx, 1U);
                /* Get current descriptor address */
                dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];
            }

            return ETH_ERROR_BUSY;
        }

        descnbr += 1U;

        /* Get the next Tx buffer in the list */
        txbuffer = txbuffer->next;

        /* Set header or buffer 1 address */
        WRITE_REG(dmatxdesc->DESC0, (uint32_t)txbuffer->buffer);
        /* Set header or buffer 1 Length */
        MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B1L, txbuffer->len);

        if (txbuffer->next != NULL)
        {
            /* Get the next Tx buffer in the list */
            txbuffer = txbuffer->next;
            /* Set buffer 2 address */
            WRITE_REG(dmatxdesc->DESC1, (uint32_t)txbuffer->buffer);
            /* Set buffer 2 Length */
            MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, (txbuffer->len << 16));
        }
        else
        {
            WRITE_REG(dmatxdesc->DESC1, 0x0U);
            /* Set buffer 2 Length */
            MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, 0x0U);
        }

        //if (READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_TSO) != (uint32_t)RESET)
        //if (((pTxConfig->Attributes) & ETH_TX_PACKETS_FEATURES_TSO) != (uint32_t)(0x0U))
        //{
        //  /* Set TCP payload length */
        //  MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TPL, pTxConfig->PayloadLen);
        //  /* Set TCP Segmentation Enabled bit */
        //  //SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TSE);
        //  dmatxdesc->DESC3 |= ETH_DMATXNDESCRF_TSE;
        //}
        //else
        //{
        /* Set the packet length */
        MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FL, pTxConfig->Length);

        //if (READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_CSUM) != (uint32_t)RESET)
        if (((pTxConfig->Attributes) & ETH_TX_PACKETS_FEATURES_CSUM) != (uint32_t)(0x0U))
        {
            /* Checksum Insertion Control */
            MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CIC, pTxConfig->ChecksumCtrl);
        }
        //}

        bd_count += 1U;

        /* Ensure rest of descriptor is written to RAM before the OWN bit */
        __DMB();
        /* Set Own bit */
        //SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN);
        dmatxdesc->DESC3 |= ETH_DMATXNDESCRF_OWN;
        /* Mark it as NORMAL descriptor */
        //CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CTXT);
        dmatxdesc->DESC3 &= (~(ETH_DMATXNDESCRF_CTXT));
    }

    //if (ItMode != ((uint32_t)RESET))
    if (ItMode != ((uint32_t)(0x0U)))
    {
        /* Set Interrupt on completion bit */
        //SET_BIT(dmatxdesc->DESC2, ETH_DMATXNDESCRF_IOC);
        dmatxdesc->DESC2 |= ETH_DMATXNDESCRF_IOC;
    }
    else
    {
        /* Clear Interrupt on completion bit */
        //CLEAR_BIT(dmatxdesc->DESC2, ETH_DMATXNDESCRF_IOC);
        dmatxdesc->DESC2 &= (~(ETH_DMATXNDESCRF_IOC));
    }

    /* Mark it as LAST descriptor */
    //SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_LD);
    dmatxdesc->DESC3 |= ETH_DMATXNDESCRF_LD;
    /* Save the current packet address to expose it to the application */
    dmatxdesclist->PacketAddress[descidx] = dmatxdesclist->CurrentPacketAddress;

    dmatxdesclist->CurTxDesc = descidx;

    /* Enter critical section */
    primask_bit = __get_PRIMASK();
    __set_PRIMASK(1);

    dmatxdesclist->BuffersInUse += bd_count + 1U;

    /* Exit critical section: restore previous priority mask */
    __set_PRIMASK(primask_bit);

    /* Return function status */
    return ETH_ERROR_NONE;
}

/**
  * @}
  */

/**
  * @}
  */

//#endif /* heth */

/**
  * @}
  */
