/*!
*******************************************************************************
**
** \file      gmodids.h
**
** \brief     Global module IDs.
**
**            This header file defines all global FD and FM specific module
**            IDs required to build module specific error code enumerations.
**
**            Unused IDs are defined as "__unused_module_id<number>__".
**
**            (C) Copyright 2012-2013 by Goke Microelectronics Shanghai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Revision: 1.0 $
**
******************************************************************************/
#ifndef GMODIDS_H
    #define GMODIDS_H

    /*
    ************************************************************
    **
    ** GD lib specific module IDs
    **
    ************************************************************
    */
    #define GD_ADC_MODULE_ID             1
    #define GD_CRYPTO_MODULE_ID          2
    #define GD_DMA_MODULE_ID             3
    #define GD_ETH_MODULE_ID             4
    #define GD_GPIO_MODULE_ID            5
    #define GD_I2C_MODULE_ID             6
    #define GD_I2S_MODULE_ID             7
    #define GD_INT_MODULE_ID             8
    #define GD_IR_MODULE_ID              9
    #define GD_PWM_MODULE_ID            10
    #define GD_SDIO_MODULE_ID           11
    #define GD_SENSOR_MODULE_ID         12
    #define GD_SFLASH_MODULE_ID         13
    #define GD_SPI_MODULE_ID            14
    #define GD_SPI_EEPROM_MODULE_ID     15
    #define GD_TIMER_MODULE_ID          16
    #define GD_UART_MODULE_ID           17
    #define GD_USB_MODULE_ID            18
    #define GD_ICC_MODULE_ID            19
    #define GD_WDOG_MODULE_ID           20
	#define GD_AUDIO_MODULE_ID          21
    /*
    ************************************************************
    **
    ** FM lib specific module IDs
    **
    ************************************************************
    */
    #define GM_PSI_MODULE_ID            30
    #define GM_DVBSI_MODULE_ID          31
    #define GM_IR_MODULE_ID             32
    #define GM_SVL_MODULE_ID            33
    #define GM_DEBUG_MODULE_ID          34
    #define GM_DRAW_MODULE_ID           35
    #define __unused_module_id36__      36
    #define GM_EEPROM_MODULE_ID         37
    #define GM_FONT_MODULE_ID           38
    #define GM_TSL_MODULE_ID            39
    #define GM_SI_MODULE_ID             40
    #define GM_CHL_MODULE_ID            41
    #define GM_EI_MODULE_ID             42
    #define GM_SF_MODULE_ID             43
    #define __unused_module_id44__      44
    #define GM_FTP_MODULE_ID            45
    #define GM_V2O_MODULE_ID            46
    #define GM_USB_MSC_MODULE_ID        47
    #define GM_USB_SERIAL_MODULE_ID     48
    #define __unused_module_id49__      49

    /*
    ************************************************************
    **
    ** Other 3rd party FM module IDs
    **
    ************************************************************
    */
    #define GM_FSUB_MODULE_ID           50
    #define __unused_module_id51__      51
    #define __unused_module_id52__      52
    #define __unused_module_id53__      53
    #define __unused_module_id54__      54
    #define __unused_module_id55__      55
    #define __unused_module_id56__      56
    #define __unused_module_id57__      57
    #define __unused_module_id58__      58
    #define __unused_module_id59__      59
    #define __unused_module_id60__      60
    #define __unused_module_id61__      61
    #define __unused_module_id62__      62
    #define __unused_module_id63__      63
    #define __unused_module_id64__      64
    #define __unused_module_id65__      65
    #define __unused_module_id66__      66
    #define __unused_module_id67__      67
    #define __unused_module_id68__      68
    #define __unused_module_id69__      69

    /*
    ************************************************************
    **
    ** Application specific module IDs
    **
    ************************************************************
    */
    #define APPL_DEMO2_MODULE_ID        100
    #define APPL_BOOTLDR_MODULE_ID      101
    #define APPL_FCHL_MODULE_ID         102
    #define APPL_FDVR_TS_MODULE_ID      103
    #define APPL_ALLDEMO_MODULE_ID      104
    #define __unused_module_id105__     105
    #define __unused_module_id106__     106
    #define __unused_module_id107__     107
    #define __unused_module_id108__     108
    #define __unused_module_id109__     109
    #define __unused_module_id110__     110
    #define __unused_module_id111__     111
    #define __unused_module_id112__     112
    #define __unused_module_id113__     113
    #define __unused_module_id114__     114
    #define __unused_module_id115__     115
    #define __unused_module_id116__     116
    #define __unused_module_id117__     117
    #define __unused_module_id118__     118
    #define __unused_module_id119__     119

#endif
