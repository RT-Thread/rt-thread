
CONTENTS OF THIS FILE
=======================
	* Introduction
	* Version
	* Integration details
	* Driver files information
	* Supported sensor interface
	* Copyright


INTRODUCTION
===============
	- This package contains the Bosch Sensortec MEMS magnetometer sensor driver (sensor API)
	- The sensor driver package includes bmm050.h, bmm050.c and bmm050_support.c files
	- BMM050 sensor driver supports the following Bosch MEMS sensors
		* BMM050
		* BMM150
		* BMC150 - Combination of bma2x2 + bmm050 APIs
		* BMC056 - Combination of bma2x2 + bmm050 APIs
		* BMX055 - Combination of bma2x2 + bmg160 + bmm050 APIs

VERSION
=========
	- Version of bmm050 sensor driver is:
		* bmm050.c 		- V2.0.6
		* bmm050.h 		- V2.0.5
		* bmm050_support.c 	- V1.0.6

INTEGRATION DETAILS
=====================
	- Integrate bmm050.h and bmm050.c file in to your project.
	- The bmm050_support.c file contains only examples for API use cases, so it is not required to integrate into project.

DRIVER FILES INFORMATION
===========================
	bmm050.h
	-----------
		* This header file has the register address definition, constant definitions, data type definition and supported sensor driver calls declarations.

	 bmm050.c
	------------
		* This file contains the implementation for the sensor driver APIs.

	 bmm050_support.c
	----------------------
		* This file shall be used as an user guidance, here you can find samples of
    			* Initialize the sensor with I2C/SPI communication
        				- Add your code to the SPI and/or I2C bus read and bus write functions.
            					- Return value can be chosen by yourself
           					- API just passes that value to your application code
        				- Add your code to the delay function
        				- Change I2C address accordingly in bmm050.h
   			* Power mode configuration of the sensor
   			* Get and set functions usage
			* Reading the sensor read out data

SUPPORTED SENSOR INTERFACE
====================================
	- This magnetometer sensor driver supports SPI and I2C interfaces


COPYRIGHT
===========
	- Copyright (C) 2015 - 2016 Bosch Sensortec GmbH


