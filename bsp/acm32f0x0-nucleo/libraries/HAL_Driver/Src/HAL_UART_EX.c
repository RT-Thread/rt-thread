/*
  ******************************************************************************
  * @file    HAL_UART_EX.c
  * @version V1.0.0
  * @date    2021
  * @brief   LIN HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the extensional module: Local Interconnect Network Peripheral (LIN).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/************************************************************************
 * function   : HAL_UART_LIN_Master_Transmit
 * Description: Uart lin master transmit data
 * input :none
 *         UART_HandleTypeDef *huart: Serial port number
 *         uint8_t Lin_Version: LIN version ,should be UART_LIN_V1D3 or UART_LIN_V2DX.
 *         uint8_t Lin_Id: LIN id
 *         uint8_t *pData: point to the transmit data buffer.
 *         uint8_t Size: Transmit buffer Size.
 * return: none
 ************************************************************************/
void HAL_UART_LIN_Master_Transmit(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t Lin_Id, uint8_t *pData, uint8_t Size)
{
    uint8_t Lin_P0,Lin_P1,ucI;
    uint16_t Lin_Check_Sum = 0;

    if((Size>8)||(pData == 0))
        return;

    CLEAR_BIT(huart->Instance->IE, UART_EX_IE_LBDI);
    huart->Instance->CR = 0x0101; //disable uart_rx

    MODIFY_REG(huart->Instance->BCNT, UART_EX_BCNT_VALUE_MASK, (13)<<UART_EX_BCNT_VALUE_POS);
    //Transmit break field.
    SET_BIT(huart->Instance->BCNT, UART_EX_BCNT_START);
    SET_BIT(huart->Instance->LCRH, UART_LCRH_BRK);

    while(!(READ_BIT(huart->Instance->RIS, UART_EX_RIS_BCNTI))){}  //Check BCNTI.
    CLEAR_BIT(huart->Instance->LCRH, UART_LCRH_BRK);

    HAL_UART_Transmit(huart, (uint8_t*)"\x55", 1, 0);   //Transmit sync field

    Lin_Id &= 0x3F; //Lin address check, 0-63.
    Lin_P0 = (Lin_Id^(Lin_Id>>1)^(Lin_Id>>2)^(Lin_Id>>4))&0x01;         //P0 = ID0^ID1^ID2^ID4
    Lin_P1 = (~((Lin_Id>>1)^(Lin_Id>>3)^(Lin_Id>>4)^(Lin_Id>>5)))&0x01;    //P1 = ~(ID1^ID3^ID4^ID5)
    Lin_Id = Lin_Id | (Lin_P0<<6) | (Lin_P1<<7);

    HAL_UART_Transmit(huart, &Lin_Id, 1, 0);   //Transmit pid field

    if((Lin_Version==UART_LIN_V2DX)&&(Lin_Id !=0x3C && Lin_Id!=0x3D))
        Lin_Check_Sum = Lin_Id;       //LIN 2.X check sum calc with PID.

    if(Size)
    {
        for(ucI=0;ucI<Size;ucI++)
        {
            Lin_Check_Sum += pData[ucI];
            if(Lin_Check_Sum>0xFF)
                Lin_Check_Sum = ((Lin_Check_Sum>>8)+Lin_Check_Sum)&0xFF;
        }
        Lin_Check_Sum = (~Lin_Check_Sum) & 0xFF;

        HAL_UART_Transmit(huart, pData, Size, 0);   //Transmit data field

        HAL_UART_Transmit(huart, (uint8_t*)&Lin_Check_Sum, 1, 0);   //Transmit Lin_Check_Sum field
    }
}

/************************************************************************
 * function   : HAL_UART_LIN_Slave_Transmit
 * Description: Uart lin slave transmit data
 * input :none
 *         UART_HandleTypeDef *huart: Serial port number
 *         uint8_t Lin_Version: LIN version ,should be UART_LIN_V1D3 or UART_LIN_V2DX.
 *         uint8_t Lin_Id: LIN id
 *         uint8_t *pData: point to the transmit data buffer.
 *         uint8_t Size: Transmit buffer Size.
 * return: none
 ************************************************************************/
void HAL_UART_LIN_Slave_Transmit(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t Lin_Id, uint8_t *pData, uint8_t Size)
{
    uint8_t ucI;
    uint16_t Lin_Check_Sum = 0;

    if((Size>8)||(pData == 0))
        return;

    CLEAR_BIT(huart->Instance->IE, UART_EX_IE_LBDI);//disable LBDI int
    huart->Instance->CR = 0x0101; //disable uart_rx

    if((Lin_Version==UART_LIN_V2DX)&&(Lin_Id !=0x3C && Lin_Id!=0x3D))
        Lin_Check_Sum = Lin_Id;       //LIN 2.X check sum calc with PID.

    for(ucI=0;ucI<Size;ucI++)
    {
        Lin_Check_Sum += pData[ucI];
        if(Lin_Check_Sum>0xFF)
            Lin_Check_Sum = ((Lin_Check_Sum>>8)+Lin_Check_Sum)&0xFF;
    }
    Lin_Check_Sum = (~Lin_Check_Sum) & 0xFF;

    HAL_UART_Transmit(huart, pData, Size, 0);   //Transmit data field

    HAL_UART_Transmit(huart, (uint8_t*)&Lin_Check_Sum, 1, 0);   //Transmit Lin_Check_Sum field
}

/************************************************************************
 * function   : HAL_UART_LIN_Master_Receive
 * Description: Uart lin master receive data
 * input :none
 *         UART_HandleTypeDef *huart: Serial port number
 *         uint8_t Lin_Version: LIN version ,should be UART_LIN_V1D3 or UART_LIN_V2DX.
 *         uint8_t Lin_Id: LIN id
 *         uint8_t *pData: point to the data buffer.
 * return: uint8_t RxSize
 ************************************************************************/
uint8_t HAL_UART_LIN_Master_Receive(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t Lin_Id, uint8_t *pData, uint32_t Timeout)
{
    uint8_t ucI,RxSize;
    uint8_t Lin_Rx_Buf[16];
    uint16_t Lin_Check_Sum = 0;

    if(pData == 0)
        return 0;

    huart->Instance->CR =  0x0201; //disable uart_tx
    huart->Instance->ICR =  0xfff; //clear int
    huart->Instance->LCRH = 0x70;  //8 data bit,1 stop bit,0 verify bit,enable FIFO
    huart->Instance->IFLS = 0x12; //FIFO send and receive number is 8
    huart->Instance->IE = 0x00;  //Disable all interrupt

    HAL_UART_Receive(huart, Lin_Rx_Buf, sizeof(Lin_Rx_Buf), Timeout);

    if((Lin_Version==UART_LIN_V2DX)&&(Lin_Id !=0x3C && Lin_Id!=0x3D))
        Lin_Check_Sum = Lin_Id;       //LIN 2.X check sum calc with PID.

    if(huart->lu32_RxCount)
    {
        for(ucI=0;ucI<(huart->lu32_RxCount-1);ucI++)
        {
            Lin_Check_Sum += Lin_Rx_Buf[ucI];
            if(Lin_Check_Sum>0xFF)
                Lin_Check_Sum = ((Lin_Check_Sum>>8)+Lin_Check_Sum)&0xFF;
        }
        Lin_Check_Sum = (~Lin_Check_Sum) & 0xFF;
        if((uint8_t)Lin_Check_Sum == Lin_Rx_Buf[ucI])
        {
            RxSize = huart->lu32_RxCount;
            memcpy(pData, (uint8_t*)Lin_Rx_Buf, RxSize);
        }
        else
            RxSize = 0xFF;
    }
    else
        RxSize = 0;

    return RxSize;
}

/************************************************************************
 * function   : HAL_UART_LIN_Slave_Receive
 * Description: Uart lin slave receive head
 * input :none
 *         UART_HandleTypeDef *huart: Serial port number
 *         uint8_t Lin_Version: LIN version ,should be UART_LIN_V1D3 or UART_LIN_V2DX.
 *         uint8_t *pData: point to the data buffer.
 * return: uint8_t RxSize
 ************************************************************************/
uint8_t HAL_UART_LIN_Slave_Receive(UART_HandleTypeDef *huart, uint8_t Lin_Version, uint8_t *pData, uint32_t Timeout)
{
    uint8_t ucI,RxSize;
    uint8_t Lin_Rx_Buf[16];
    uint16_t Lin_Check_Sum = 0;
    uint32_t u32_Timeout;

    if(pData == 0)
        return 0;

    huart->Instance->CR =  0x0201; //disable uart_tx
    huart->Instance->ICR =  0xfff; //clear int
    CLEAR_BIT(huart->Instance->IE, UART_EX_IE_LBDI); //Disable LBDI int

    if (Timeout == 0)
    {
        while(!READ_BIT(huart->Instance->RIS, UART_EX_RIS_LBDI));
    }
    else
    {
        u32_Timeout = Timeout * 0xFF;

        while(!READ_BIT(huart->Instance->RIS, UART_EX_RIS_LBDI))
        {
            if (u32_Timeout-- == 0)
            {
                return 0;
            }
        }
    }
    CLEAR_BIT(huart->Instance->RIS, UART_EX_RIS_LBDI);

    huart->Instance->LCRH = 0x70;  //8 data bit,1 stop bit,0 verify bit,enable FIFO
    huart->Instance->IFLS = 0x12; //FIFO send and receive number is 8
    huart->Instance->IE = 0x00;  //Disable all interrupt

    HAL_UART_Receive(huart, Lin_Rx_Buf, sizeof(Lin_Rx_Buf), Timeout);  //waitting rx completed.

    if(huart->lu32_RxCount > 3)
    {
        if((Lin_Version==UART_LIN_V2DX)&&(Lin_Rx_Buf[2] !=0x3C && Lin_Rx_Buf[2]!=0x3D))
            Lin_Check_Sum = Lin_Rx_Buf[2];       //LIN 2.X check sum calc with PID.

        if(huart->lu32_RxCount)
        {
            for(ucI=3;ucI<(huart->lu32_RxCount-1);ucI++)
            {
                Lin_Check_Sum += Lin_Rx_Buf[ucI];
                if(Lin_Check_Sum>0xFF)
                    Lin_Check_Sum = ((Lin_Check_Sum>>8)+Lin_Check_Sum)&0xFF;
            }
            Lin_Check_Sum = (~Lin_Check_Sum) & 0xFF;
            if((uint8_t)Lin_Check_Sum == Lin_Rx_Buf[ucI])
            {
                RxSize = huart->lu32_RxCount;
                memcpy(pData, (uint8_t*)Lin_Rx_Buf, RxSize);
            }
            else
                RxSize = 0xFF;
        }
    }
    else if(huart->lu32_RxCount<=3)
    {
        RxSize = huart->lu32_RxCount;
        memcpy(pData, (uint8_t*)Lin_Rx_Buf, RxSize);
    }
    else
        RxSize = 0;

    return RxSize;
}
