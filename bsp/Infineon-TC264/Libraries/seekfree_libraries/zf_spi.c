/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		spi
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
 

#include "IFXQSPI_REGDEF.h"
#include "IfxQspi_SpiMaster.h"
#include "IfxQspi.h"
#include "zf_assert.h"
#include "zf_spi.h"


#define MAX_BAUD	50000000


void spi_mux(SPIN_enum spi_n, SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, SPI_PIN_enum cs_pin, IfxQspi_SpiMaster_Pins *set_pin, IfxQspi_SpiMaster_Output *set_cs)
{
	set_pin->mrstMode = IfxPort_InputMode_pullDown;
	set_pin->mtsrMode = IfxPort_OutputMode_pushPull;
	set_pin->sclkMode = IfxPort_OutputMode_pushPull;
	set_pin->pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;

	set_cs->driver = IfxPort_PadDriver_cmosAutomotiveSpeed1;
	set_cs->mode = IfxPort_OutputMode_pushPull;

	switch(spi_n)
	{
		case SPI_0:
		{
			if		(SPI0_SCLK_P20_11 == sck_pin)	set_pin->sclk = &IfxQspi0_SCLK_P20_11_OUT;
			else if	(SPI0_SCLK_P20_13 == sck_pin)	set_pin->sclk = &IfxQspi0_SCLK_P20_13_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI0_MOSI_P20_12 == mosi_pin)	set_pin->mtsr = &IfxQspi0_MTSR_P20_12_OUT;
			else if	(SPI0_MOSI_P20_14 == mosi_pin)	set_pin->mtsr = &IfxQspi0_MTSR_P20_14_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI0_MISO_P20_12 == miso_pin)	set_pin->mrst = &IfxQspi0_MRSTA_P20_12_IN;
			else	ZF_ASSERT(FALSE);

			if		(SPI0_CS0_P20_8   == cs_pin)	set_cs->pin = &IfxQspi0_SLSO0_P20_8_OUT;
			else if (SPI0_CS1_P20_9   == cs_pin)	set_cs->pin = &IfxQspi0_SLSO1_P20_9_OUT;
			else if (SPI0_CS2_P20_13  == cs_pin)	set_cs->pin = &IfxQspi0_SLSO2_P20_13_OUT;
			else if (SPI0_CS3_P11_10  == cs_pin)	set_cs->pin = &IfxQspi0_SLSO3_P11_10_OUT;
			else if (SPI0_CS4_P11_11  == cs_pin)	set_cs->pin = &IfxQspi0_SLSO4_P11_11_OUT;
			else if (SPI0_CS5_P11_2   == cs_pin)	set_cs->pin = &IfxQspi0_SLSO5_P11_2_OUT;
			else if (SPI0_CS6_P20_10  == cs_pin)	set_cs->pin = &IfxQspi0_SLSO6_P20_10_OUT;
			else if (SPI0_CS7_P33_5   == cs_pin)	set_cs->pin = &IfxQspi0_SLSO7_P33_5_OUT;
			else if (SPI0_CS8_P20_6   == cs_pin)	set_cs->pin = &IfxQspi0_SLSO8_P20_6_OUT;
			else if (SPI0_CS9_P20_3   == cs_pin)	set_cs->pin = &IfxQspi0_SLSO9_P20_3_OUT;
			else if (SPI0_CS13_P15_0  == cs_pin)	set_cs->pin = &IfxQspi0_SLSO13_P15_0_OUT;
			else	ZF_ASSERT(FALSE);

		}break;

		case SPI_1:
		{
			if		(SPI1_SCLK_P10_2 == sck_pin)	set_pin->sclk = &IfxQspi1_SCLK_P10_2_OUT;
			else if	(SPI1_SCLK_P11_6 == sck_pin)	set_pin->sclk = &IfxQspi1_SCLK_P11_6_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI1_MOSI_P10_1 == mosi_pin)	set_pin->mtsr = &IfxQspi1_MTSR_P10_1_OUT;
			else if	(SPI1_MOSI_P10_3 == mosi_pin)	set_pin->mtsr = &IfxQspi1_MTSR_P10_3_OUT;
			else if	(SPI1_MOSI_P10_4 == mosi_pin)	set_pin->mtsr = &IfxQspi1_MTSR_P10_4_OUT;
			else if	(SPI1_MOSI_P11_9 == mosi_pin)	set_pin->mtsr = &IfxQspi1_MTSR_P11_9_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI1_MISO_P10_1 == miso_pin)	set_pin->mrst = &IfxQspi1_MRSTA_P10_1_IN;
			else if	(SPI1_MISO_P11_3 == miso_pin)	set_pin->mrst = &IfxQspi1_MRSTB_P11_3_IN;
			else	ZF_ASSERT(FALSE);

			if		(SPI1_CS0_P20_8   == cs_pin)	set_cs->pin = &IfxQspi1_SLSO0_P20_8_OUT;
			else if (SPI1_CS1_P20_9   == cs_pin)	set_cs->pin = &IfxQspi1_SLSO1_P20_9_OUT;
			else if (SPI1_CS2_P20_13  == cs_pin)	set_cs->pin = &IfxQspi1_SLSO2_P20_13_OUT;
			else if (SPI1_CS3_P11_10  == cs_pin)	set_cs->pin = &IfxQspi1_SLSO3_P11_10_OUT;
			else if (SPI1_CS4_P11_11  == cs_pin)	set_cs->pin = &IfxQspi1_SLSO4_P11_11_OUT;
			else if (SPI1_CS5_P11_2   == cs_pin)	set_cs->pin = &IfxQspi1_SLSO5_P11_2_OUT;
			else if (SPI1_CS6_P33_10  == cs_pin)	set_cs->pin = &IfxQspi1_SLSO6_P33_10_OUT;
			else if (SPI1_CS7_P33_5   == cs_pin)	set_cs->pin = &IfxQspi1_SLSO7_P33_5_OUT;
			else if (SPI1_CS8_P10_4   == cs_pin)	set_cs->pin = &IfxQspi1_SLSO8_P10_4_OUT;
			else if (SPI1_CS9_P10_5   == cs_pin)	set_cs->pin = &IfxQspi1_SLSO9_P10_5_OUT;
			else if (SPI1_CS10_P10_0  == cs_pin)	set_cs->pin = &IfxQspi1_SLSO10_P10_0_OUT;
			else	ZF_ASSERT(FALSE);
		}break;

		case SPI_2:
		{
			if		(SPI2_SCLK_P13_0  == sck_pin)	set_pin->sclk = &IfxQspi2_SCLKN_P13_0_OUT;
			else if	(SPI2_SCLK_P13_1  == sck_pin)	set_pin->sclk = &IfxQspi2_SCLKP_P13_1_OUT;
			else if	(SPI2_SCLK_P15_3  == sck_pin)	set_pin->sclk = &IfxQspi2_SCLK_P15_3_OUT;
			else if	(SPI2_SCLK_P15_6  == sck_pin)	set_pin->sclk = &IfxQspi2_SCLK_P15_6_OUT;
			else if	(SPI2_SCLK_P15_8  == sck_pin)	set_pin->sclk = &IfxQspi2_SCLK_P15_8_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI2_MOSI_P13_2  == mosi_pin)	set_pin->mtsr = &IfxQspi2_MTSRN_P13_2_OUT;
			else if	(SPI2_MOSI_P13_3  == mosi_pin)	set_pin->mtsr = &IfxQspi2_MTSRP_P13_3_OUT;
			else if	(SPI2_MOSI_P15_5  == mosi_pin)	set_pin->mtsr = &IfxQspi2_MTSR_P15_5_OUT;
			else if	(SPI2_MOSI_P15_6  == mosi_pin)	set_pin->mtsr = &IfxQspi2_MTSR_P15_6_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI2_MISO_P15_2  == miso_pin)	set_pin->mrst = &IfxQspi2_MRSTE_P15_2_IN;
			else if	(SPI2_MISO_P15_4  == miso_pin)	set_pin->mrst = &IfxQspi2_MRSTA_P15_4_IN;
			else if	(SPI2_MISO_P15_7  == miso_pin)	set_pin->mrst = &IfxQspi2_MRSTB_P15_7_IN;
			else if	(SPI2_MISO_P21_2  == miso_pin)	set_pin->mrst = &IfxQspi2_MRSTCN_P21_2_IN;
			else if	(SPI2_MISO_P21_3  == miso_pin)	set_pin->mrst = &IfxQspi2_MRSTCP_P21_3_IN;
			else	ZF_ASSERT(FALSE);

			if		(SPI2_CS0_P15_2   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO0_P15_2_OUT;
			else if (SPI2_CS1_P14_2   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO1_P14_2_OUT;
			else if (SPI2_CS2_P14_6   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO2_P14_6_OUT;
			else if (SPI2_CS3_P14_3   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO3_P14_3_OUT;
			else if (SPI2_CS4_P14_7   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO4_P14_7_OUT;
			else if (SPI2_CS5_P15_1   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO5_P15_1_OUT;
			else if (SPI2_CS6_P33_13  == cs_pin)	set_cs->pin = &IfxQspi2_SLSO6_P33_13_OUT;
			else if (SPI2_CS7_P20_10  == cs_pin)	set_cs->pin = &IfxQspi2_SLSO7_P20_10_OUT;
			else if (SPI2_CS8_P20_6   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO8_P20_6_OUT;
			else if (SPI2_CS9_P20_3   == cs_pin)	set_cs->pin = &IfxQspi2_SLSO9_P20_3_OUT;
			else	ZF_ASSERT(FALSE);
		}break;

		case SPI_3:
		{
			if		(SPI3_SCLK_P02_7  == sck_pin)	set_pin->sclk = &IfxQspi3_SCLK_P02_7_OUT;
			else if	(SPI3_SCLK_P10_8  == sck_pin)	set_pin->sclk = &IfxQspi3_SCLK_P10_8_OUT;
			else if	(SPI3_SCLK_P22_0  == sck_pin)	set_pin->sclk = &IfxQspi3_SCLKN_P22_0_OUT;
			else if	(SPI3_SCLK_P22_1  == sck_pin)	set_pin->sclk = &IfxQspi3_SCLKP_P22_1_OUT;
			else if	(SPI3_SCLK_P22_3  == sck_pin)	set_pin->sclk = &IfxQspi3_SCLK_P22_3_OUT;
			else if	(SPI3_SCLK_P33_11 == sck_pin)	set_pin->sclk = &IfxQspi3_SCLK_P33_11_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI3_MOSI_P02_6  == mosi_pin)	set_pin->mtsr = &IfxQspi3_MTSR_P02_6_OUT;
			else if	(SPI3_MOSI_P10_6  == mosi_pin)	set_pin->mtsr = &IfxQspi3_MTSR_P10_6_OUT;
			else if	(SPI3_MOSI_P22_0  == mosi_pin)	set_pin->mtsr = &IfxQspi3_MTSR_P22_0_OUT;
			else if	(SPI3_MOSI_P22_2  == mosi_pin)	set_pin->mtsr = &IfxQspi3_MTSRN_P22_2_OUT;
			else if	(SPI3_MOSI_P22_3  == mosi_pin)	set_pin->mtsr = &IfxQspi3_MTSRP_P22_3_OUT;
			else if	(SPI3_MOSI_P33_12 == mosi_pin)	set_pin->mtsr = &IfxQspi3_MTSR_P33_12_OUT;
			else	ZF_ASSERT(FALSE);

			if		(SPI3_MISO_P02_5  == miso_pin)	set_pin->mrst = &IfxQspi3_MRSTA_P02_5_IN;
			else if	(SPI3_MISO_P10_7  == miso_pin)	set_pin->mrst = &IfxQspi3_MRSTB_P10_7_IN;
			else if	(SPI3_MISO_P22_1  == miso_pin)	set_pin->mrst = &IfxQspi3_MRSTE_P22_1_IN;
			else if	(SPI3_MISO_P21_2  == miso_pin)	set_pin->mrst = &IfxQspi3_MRSTFN_P21_2_IN;
			else if	(SPI3_MISO_P21_3  == miso_pin)	set_pin->mrst = &IfxQspi3_MRSTFP_P21_3_IN;
			else if	(SPI3_MISO_P33_13  == miso_pin)	set_pin->mrst = &IfxQspi3_MRSTD_P33_13_IN;
			else	ZF_ASSERT(FALSE);

			if		(SPI3_CS0_P02_4   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO0_P02_4_OUT;
			else if (SPI3_CS1_P02_0   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO1_P02_0_OUT;
			else if (SPI3_CS1_P33_9   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO1_P33_9_OUT;
			else if (SPI3_CS2_P02_1   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO2_P02_1_OUT;
			else if (SPI3_CS2_P33_8   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO2_P33_8_OUT;
			else if (SPI3_CS3_P02_2   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO3_P02_2_OUT;
			else if (SPI3_CS4_P02_3   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO4_P02_3_OUT;
			else if (SPI3_CS4_P23_5   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO4_P23_5_OUT;
			else if (SPI3_CS5_P02_8   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO5_P02_8_OUT;
			else if (SPI3_CS5_P23_4   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO5_P23_4_OUT;
			else if (SPI3_CS6_P00_8   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO6_P00_8_OUT;
			else if (SPI3_CS7_P00_9   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO7_P00_9_OUT;
			else if (SPI3_CS7_P33_7   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO7_P33_7_OUT;
			else if (SPI3_CS8_P10_5   == cs_pin)	set_cs->pin = &IfxQspi3_SLSO8_P10_5_OUT;
			else if (SPI3_CS11_P33_10 == cs_pin)	set_cs->pin = &IfxQspi3_SLSO11_P33_10_OUT;
			else if (SPI3_CS12_P22_2  == cs_pin)	set_cs->pin = &IfxQspi3_SLSO12_P22_2_OUT;
			else if (SPI3_CS13_P23_1  == cs_pin)	set_cs->pin = &IfxQspi3_SLSO13_P23_1_OUT;
			else	ZF_ASSERT(FALSE);
		}break;
	}
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI初始化
//  @param      spi_n           选择SPI模块(SPI_1-SPI_4)
//  @param      cs_pin          选择SPI片选引脚
//  @param      sck_pin         选择SPI时钟引脚
//  @param      mosi_pin        选择SPI MOSI引脚
//  @param      miso_pin        选择SPI MISO引脚
//  @param      mode            SPI模式 0：CPOL=0 CPHA=0    1：CPOL=0 CPHA=1   2：CPOL=1 CPHA=0   3：CPOL=1 CPHA=1 //具体细节可自行百度
//  @param      baud            设置SPI的波特率
//  @return     void
//  Sample usage:               spi_init(SPI_2, SPI2_SCLK_P15_3, SPI2_MOSI_P15_5, SPI2_MISO_P15_4, SPI2_CS0_P15_2, 0, 1*1000*1000);//硬件SPI初始化  模式0 波特率为1Mhz
//-------------------------------------------------------------------------------------------------------------------
void spi_init(SPIN_enum spi_n, SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, SPI_PIN_enum cs_pin, uint8 mode, uint32 baud)
{

	IfxQspi_SpiMaster_Config MasterConfig;
	IfxQspi_SpiMaster MasterHandle;
	IfxQspi_SpiMaster_Channel MasterChHandle;
	IfxQspi_SpiMaster_Pins MasterPins;
	IfxQspi_SpiMaster_Output SlsoPin;
	volatile Ifx_QSPI *moudle;

	moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);

	spi_mux(spi_n, sck_pin, mosi_pin, miso_pin, cs_pin, &MasterPins, &SlsoPin);

	IfxQspi_SpiMaster_initModuleConfig(&MasterConfig, moudle);
	MasterConfig.base.mode = SpiIf_Mode_master;
	MasterConfig.base.maximumBaudrate = MAX_BAUD;
	MasterConfig.base.isrProvider = IfxSrc_Tos_cpu0;


	MasterConfig.pins = &MasterPins;
	IfxQspi_SpiMaster_initModule(&MasterHandle, &MasterConfig);

	IfxQspi_SpiMaster_ChannelConfig MasterChConfig;
	IfxQspi_SpiMaster_initChannelConfig(&MasterChConfig, &MasterHandle);


	MasterChConfig.base.baudrate = (float)baud;
	switch(mode)
	{
		case 0:
		{
			MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleLow;//CPOL
			MasterChConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;//CPHA
		}break;
		case 1:
		{
			MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleLow;
			MasterChConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
		}break;
		case 2:
		{
			MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleHigh;
			MasterChConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;
		}break;
		case 3:
		{
			MasterChConfig.base.mode.clockPolarity = SpiIf_ClockPolarity_idleHigh;
			MasterChConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
		}break;
	}

	MasterChConfig.base.mode.dataHeading = SpiIf_DataHeading_msbFirst;
	MasterChConfig.base.mode.dataWidth = 8;

	MasterChConfig.base.mode.csActiveLevel = Ifx_ActiveState_low;
	MasterChConfig.sls.output = SlsoPin;
	IfxQspi_SpiMaster_initChannel(&MasterChHandle, &MasterChConfig);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SPI发送接收函数
//  @param      spi_n           选择SPI模块   (SPI_1-SPI_4)
//  @param      cs_pin          选择SPI片选引脚
//  @param      modata          发送的数据缓冲区地址
//  @param      midata          发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
//  @param      len             发送的字节数
//  @param      continuous      本次通信是CS是否持续保持有效状态 1:持续保持  0:每传输完一个字节关闭CS(一般设置为1 即可)
//  @return     void
//  @since      v2.0
//  Sample usage:       		spi_mosi(SPI_2,SPI2_CS0_P15_2,buf,buf,1,1);    //发送buff的内容，并接收到buf里，长度为1字节 通信期间CS持续拉低
//-------------------------------------------------------------------------------------------------------------------
void spi_mosi(SPIN_enum spi_n, SPI_PIN_enum cs_pin, uint8 *modata, uint8 *midata, uint32 len, uint8 continuous)
{
	uint32 i;
	Ifx_QSPI_BACON bacon;
	volatile Ifx_QSPI *moudle;

	moudle = IfxQspi_getAddress((IfxQspi_Index)spi_n);

	bacon.U = moudle->BACON.U;

	bacon.B.DL = 7;
	bacon.B.IDLE = 1;
	bacon.B.IPRE = 1;
	bacon.B.LEAD = 1;
	bacon.B.LPRE = 1;
	bacon.B.MSB = 1;
	bacon.B.PARTYP = 0;
	bacon.B.BYTE = 0;
	bacon.B.TRAIL = 1;
	bacon.B.TPRE = 1;
	bacon.B.CS = cs_pin%102/6-3;
	if(continuous)	IfxQspi_writeBasicConfigurationBeginStream(moudle, bacon.U);//发送数据后CS继续保持为低
	else			IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);	//每发送一个字节CS信号拉高一次

	if(len>1)
	{
		i = 0;
		while(i < (len-1))
		{
			while(moudle->STATUS.B.TXFIFOLEVEL != 0);
			IfxQspi_write8(moudle, IfxQspi_ChannelId_0, modata, 1);
			while(moudle->STATUS.B.RXFIFOLEVEL == 0);
			if(NULL != midata)	
			{
				IfxQspi_read8(moudle,midata,1);
				midata++;
			}
			else				(void)moudle->RXEXIT.U;
			modata++;
			
			i++;
		}
	}

	//发送最后一个数据
	if(continuous)	IfxQspi_writeBasicConfigurationEndStream(moudle, bacon.U);
	IfxQspi_writeTransmitFifo(moudle, *modata);
	while(moudle->STATUS.B.TXFIFOLEVEL != 0);

	while(moudle->STATUS.B.RXFIFOLEVEL == 0);
	if(NULL != midata)	IfxQspi_read8(moudle,midata,1);
	else				(void)moudle->RXEXIT.U;
}




