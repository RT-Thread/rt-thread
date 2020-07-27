
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
	- This package contains the Bosch Sensortec MEMS gyroscope sensor driver (sensor API)
	- The sensor driver package includes bmg160.h, bmg160.c and bmg160_support.c files
	- BMG160 sensor driver supports the following sensors
		* BMG160
		* BMI055 - combination of bma2x2 + bmg160
		* BMX055 - combination of bma2x2 + bmg160 + bmm050

VERSION
=========
	- Version of bmg160 sensor driver is:
		* bmg160.c 		- V2.0.4
		* bmg160.h 		- V2.0.4
		* bmg160_support.c 	- V1.0.5

INTEGRATION DETAILS
=====================
	- Integrate bmg160.h and bmg160.c file in to your project.
	- The bmg160_support.c file contains only examples for API use cases, so it is not required to integrate into project.

DRIVER FILES INFORMATION
===========================
	bmg160.h
	-----------
		* This header file has the register address definition, constant definitions, data type definition and supported sensor driver calls declarations.

	 bmg160.c
	------------
		* This file contains the implementation for the sensor driver APIs.

	 bmg160_support.c
	----------------------
		* This file shall be used as an user guidance, here you can find samples of
    			* Initialize the sensor with I2C/SPI communication
        				- Add your code to the SPI and/or I2C bus read and bus write functions.
            					- Return value can be chosen by yourself
           					- API just passes that value to your application code
        				- Add your code to the delay function
        				- Change I2C address accordingly in bmg160.h
   			* Power mode configuration of the sensor
   			* Get and set functions usage
			* Reading the sensor read out data

SUPPORTED SENSOR INTERFACE
====================================
	- This gyroscope sensor driver supports SPI and I2C interfaces


COPYRIGHT
===========
	- Copyright (C) 2010 - 2015 Bosch Sensortec GmbH

