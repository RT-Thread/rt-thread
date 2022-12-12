/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 * 2022-07-11     shiwa        add examples for es32f3696
 */

#include <Arduino.h>
#include <rtthread.h>
#include <SPI.h>
#include <Wire.h>
#define  ARDU_TEST_GPIO
#define ARDU_TEST_PWM
//#define  ARDU_TEST_ADAFRUIT_I2C
//#define  ARDU_TEST_ADAFRUIT_SPI
//#define  ARDU_TEST_SPI
//#define  ARDU_TEST_I2C
#define  ARDU_TEST_INT
#define  ARDU_TEST_DIGITAL_READ
//#define  ARDU_TEST_ADC_READ
//#define ARDU_TEST_BMI160_PKG

#if defined(ARDU_TEST_ADAFRUIT_I2C) || defined(ARDU_TEST_ADAFRUIT_SPI)
#include <Adafruit_BusIO_Register.h>
#endif
#ifdef ARDU_TEST_ADAFRUIT_I2C
#include <Adafruit_I2CDevice.h>
Adafruit_I2CDevice i2c_dev(0x2D);
Adafruit_BusIO_Register i2c_reg(&i2c_dev, 0x6261, 2, 0, 2);
#endif
#ifdef ARDU_TEST_ADAFRUIT_SPI
#include "Adafruit_SPIDevice.h"
Adafruit_SPIDevice spi_dev(D10, 100000);
#endif
#ifdef ARDU_TEST_BMI160_PKG
#include "DFRobot_BMI160.h"
DFRobot_BMI160 *bmi160;
#endif


static char buf[16] = {"test"};
static char buf2[16] = {"AB"};

void test_int()
{
    Serial.println("Interrupt Triggered\r\n");
}
void setup(void)
{
    /* put your setup code here, to run once: */
    //串口
    Serial.write("Hello from Arduino\r\n");

#ifdef ARDU_TEST_GPIO //数字管脚输出
    pinMode(D2, OUTPUT);
    pinMode(D4, OUTPUT);
    digitalWrite(D4, 1);
    pinMode(D7, OUTPUT);
    digitalWrite(D7, 0);
    pinMode(D18, OUTPUT); //LED6
#endif

    pinMode(D21, INPUT);


#ifdef ARDU_TEST_PWM //测试PWM输出
    analogWriteFrequency(10);
    analogWrite(D3, 80);
    analogWrite(D5, 127);
    analogWrite(D6, 200);
#endif

#ifdef ARDU_TEST_ADAFRUIT_I2C  //ADAFRUIT I2C
    i2c_dev.begin();
#endif
#ifdef ARDU_TEST_ADAFRUIT_SPI  //ADAFRUIT SPI
    spi_dev.begin();
#endif

#ifdef ARDU_TEST_I2C //I2C
    Wire.begin();
#endif

#ifdef ARDU_TEST_SPI //SPI
    SPI.begin();
    SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1));
    pinMode(D10, OUTPUT);
    digitalWrite(D10, HIGH);
#endif

#ifdef ARDU_TEST_INT  //中断输入
    attachInterrupt(digitalPinToInterrupt(D24), test_int, FALLING);
#endif

#ifdef ARDU_TEST_DIGITAL_READ //数字管脚输入
    pinMode(D20,INPUT);
    pinMode(D21,INPUT);
    pinMode(D22,INPUT);
    pinMode(D23,INPUT);
#endif
#ifdef ARDU_TEST_BMI160_PKG
    bmi160=new DFRobot_BMI160();
    int result= bmi160->I2cInit();
    if (result)
    {
        rt_kprintf("BMI160 Init failed.%d\r\n",result);
    }
    bmi160->setStepPowerMode(bmi160->stepNormalPowerMode);
#endif
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    static int count = 0;
    count++;
#ifdef ARDU_TEST_GPIO
    digitalWrite(D2, 1);
    digitalWrite(D18, 0);
#endif
    delay(250);
#ifdef ARDU_TEST_GPIO
    digitalWrite(D2, 0);
    digitalWrite(D18, 1);
#endif
    delay(250);

#ifdef ARDU_TEST_ADC_READ
    int val = analogRead(A0 + count % 6);
    rt_kprintf("A%d=%d\r\n", count % 6, val);
#endif

#ifdef ARDU_TEST_ADAFRUIT_I2C
    i2c_dev.write((uint8_t *)buf, strlen(buf), true, (uint8_t *)buf2, 2);
    i2c_reg.write((uint8_t *)buf, 4);
#endif

#ifdef ARDU_TEST_ADAFRUIT_SPI
    spi_dev.beginTransactionWithAssertingCS();
    spi_dev.transfer((uint8_t *)buf, strlen(buf));
    spi_dev.endTransactionWithDeassertingCS();
#endif

#ifdef ARDU_TEST_I2C
    Wire.beginTransmission(0x2D);
    Wire.write((uint8_t *)buf, strlen(buf));
    Wire.endTransmission();
#endif

#ifdef ARDU_TEST_SPI
    digitalWrite(D10, LOW);
    SPI.transfer((uint8_t *)buf, 4);
    digitalWrite(D10, HIGH);
    buf[4] = 0;
    Serial.print(buf);
#endif

#ifdef ARDU_TEST_DIGITAL_READ
    if (digitalRead(D20) == LOW) {
        Serial.println("UP");
    }
    if (digitalRead(D21) == LOW) {
        Serial.println("DOWN");
    }
    if (digitalRead(D22) == LOW) {
        Serial.println("LEFT");
    }
    if (digitalRead(D23) == LOW) {
        Serial.println("RIGHT");
    }
#endif
#ifdef ARDU_TEST_BMI160_PKG
    int16_t data[16]={0,0,0};
    int result=bmi160->getAccelData(data);
    rt_kprintf("Accel[R=%d]:%d,%d,%d\r\n",result,data[0],data[1],data[2]);
    result=bmi160->getAccelGyroData(data);
    rt_kprintf("Gyro [R=%d]:%d,%d,%d\r\n",result,data[0],data[1],data[2]);
#endif

}
