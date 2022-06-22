## Table of Contents
- [Introduction](#intro)
- [Version](#ver)
- [Integration details](#integration)
- [Driver files information](#fileinfo)
- [Supported sensor interface](#interface)
- [Copyright](#copy)

### Introduction<a name=intro></a>
- This package contains the Bosch Sensortec MEMS accelerometer sensor driver (sensor API)
- The sensor driver package includes bma2x2.h, bma2x2.c and bma2x2_support.c files
- BMA2x2 sensor driver supports the following Bosch MEMS sensors
	* BMA280
	* BMA255
	* BMA253
	* BMA250E
	* BMA22E
	* BMA220
	* BMI055 - Combination of bma2x2 + bmg160 APIs
	* BMX055 - Combination of bma2x2 + bmg160 + bmm050 APIs
	* BMC150 - Combination of bma2x2 + bmm050 APIs
	* BMC056 - Combination of bma2x2 + bmm050 APIs

### Version<a name=ver></a>
- Version of bma2x2 sensor driver is:

Driver files     | Version 
-----------------|---------
bma2x2.c 	 |  2.0.7  
bma2x2.h 	 |  2.0.7  
bma2x2_support.c |  1.0.4  

### Integration details<a name=integration></a>
- Integrate bma2x2.h and bma2x2.c file in to your project.
- The bma2x2_support.c file contains only examples for API use cases, so it is not required to integrate into project.

### Driver files information<a name=fileinfo></a>
- bma2x2.h
    - This header file has the register address definition, constant definitions, data type definition and supported sensor driver calls declarations.
- bma2x2.c
    - This file contains the implementation for the sensor driver APIs.
- bma2x2_support.c
    - This file shall be used as an user guidance, here you can find samples of
            - Initialize the sensor with I2C/SPI communication
                    - Add your code to the SPI and/or I2C bus read and bus write functions.
                            - Return value can be chosen by yourself
                        - API just passes that value to your application code
                    - Add your code to the delay function
                    - Change I2C address accordingly in bma2x2.h
        - Power mode configuration of the sensor
        - Get and set functions usage
        - Reading the sensor read out data

### Supported sensor interface<a name=interface></a>
- This accelerometer sensor driver supports SPI and I2C interfaces

### Copyright<a name=copy></a>
- Copyright (C) 2015 - 2016 Bosch Sensortec GmbH

