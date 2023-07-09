/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-05-29     Meco Man      port to RTduino
 */

/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <RTduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library

// ST7789 TFT module connections
#define TFT_CS    D36  // define chip select pin
#define TFT_DC    D38  // define data/command pin
#define TFT_RST   D37  // define reset pin, or set to -1 and connect to Arduino RESET pin
#define TFT_PWR   D39  // LCD screen power with PWM control

// Initialize Adafruit ST7789 TFT library
static Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void testlines(uint16_t color)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6)
    {
        tft.drawLine(0, 0, x, tft.height()-1, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6)
    {
        tft.drawLine(0, 0, tft.width()-1, y, color);
    }

    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6)
    {
        tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6)
    {
        tft.drawLine(tft.width()-1, 0, 0, y, color);
    }

    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6)
    {
        tft.drawLine(0, tft.height()-1, x, 0, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6)
    {
        tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    }

    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6)
    {
        tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6)
    {
        tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    }
}

void testdrawtext(char *text, uint16_t color)
{
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t y=0; y < tft.height(); y+=5)
    {
        tft.drawFastHLine(0, y, tft.width(), color1);
    }
    for (int16_t x=0; x < tft.width(); x+=5)
    {
        tft.drawFastVLine(x, 0, tft.height(), color2);
    }
}

void testdrawrects(uint16_t color)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6)
    {
        tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
    }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t x=tft.width()-1; x > 6; x-=6)
    {
        tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
        tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
    }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
    for (int16_t x=radius; x < tft.width(); x+=radius*2)
    {
        for (int16_t y=radius; y < tft.height(); y+=radius*2)
        {
            tft.fillCircle(x, y, radius, color);
        }
    }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
    for (int16_t x=0; x < tft.width()+radius; x+=radius*2)
    {
        for (int16_t y=0; y < tft.height()+radius; y+=radius*2)
        {
            tft.drawCircle(x, y, radius, color);
        }
    }
}

void testtriangles(void)
{
    tft.fillScreen(ST77XX_BLACK);
    int color = 0xF800;
    int t;
    int w = tft.width()/2;
    int x = tft.height()-1;
    int y = 0;
    int z = tft.width();
    for(t = 0 ; t <= 15; t++)
    {
        tft.drawTriangle(w, y, y, x, z, x, color);
        x-=4;
        y+=4;
        z-=4;
        color+=100;
    }
}

void testroundrects(void)
{
    tft.fillScreen(ST77XX_BLACK);
    int color = 100;
    int i;
    int t;
    for(t = 0 ; t <= 4; t+=1)
    {
        int x = 0;
        int y = 0;
        int w = tft.width()-2;
        int h = tft.height()-2;
        for(i = 0 ; i <= 16; i+=1)
        {
            tft.drawRoundRect(x, y, w, h, 5, color);
            x+=2;
            y+=3;
            w-=4;
            h-=6;
            color+=1100;
        }
        color+=100;
    }
}

void tftPrintTest(void)
{
    tft.setTextWrap(false);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(2);
    tft.println("Hello RT-Thread!");
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.println("Hello RTduino!");
    tft.setTextColor(ST77XX_BLUE);
    tft.setTextSize(4);
    tft.print(1234.567);
    delay(1500);
    tft.setCursor(0, 0);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(0);
    tft.println("Hello World!");
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_GREEN);
    tft.print(PI, 6);
    tft.println(" Want pi?");
    tft.println(" ");
    tft.print(8675309, HEX); // print 8,675,309 out in HEX!
    tft.println(" Print HEX!");
    tft.println(" ");
    tft.setTextColor(ST77XX_WHITE);
    tft.println("Sketch has been");
    tft.println("running for: ");
    tft.setTextColor(ST77XX_MAGENTA);
    tft.print(millis() / 1000);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(" seconds.");
}

void mediabuttons(void)
{
    // play
    tft.fillScreen(ST77XX_BLACK);
    tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
    tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
    delay(500);
    // pause
    tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
    tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
    tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
    delay(500);
    // play color
    tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
    delay(50);
    // pause color
    tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
    tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
    // play color
    tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

static void st7789_setup(void)
{
    Serial.begin();
    Serial.println(F("Hello! ST77xx TFT Test"));

    // if the display has CS pin try with SPI_MODE0
    tft.init(240, 240, SPI_MODE0);    // Init ST7789 display 240x240 pixel
    analogWrite(TFT_PWR, 255); // set the PWM background LED as max

    // if the screen is flipped, remove this command
    tft.setRotation(2);

    Serial.println(F("Initialized"));

    uint16_t time = millis();
    tft.fillScreen(ST77XX_BLACK);
    time = millis() - time;
    Serial.print("Fill the screen spend: ");
    Serial.print(time, DEC);
    Serial.println(" ms");

    time = millis();
    testdrawtext((char *)"RTduino is an open source project which is compatible with Arduino APIs so that RT-Thread beginners can easily get start to use RT-Thread through Arduino APIs, which significantly reduces the difficulty of learning RT-Thread.", ST77XX_WHITE);
    time = millis() - time;
    Serial.print("write text spend: ");
    Serial.print(time, DEC);
    Serial.println(" ms");
    delay(1500);

    // tft print function!
    tftPrintTest();
    delay(4000);

    // a single pixel
    tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
    delay(500);

    // line draw test
    time = millis();
    testlines(ST77XX_YELLOW);
    time = millis() - time;
    Serial.print("testlines spend: ");
    Serial.print(time, DEC);
    Serial.println(" ms");
    delay(500);

    // optimized lines
    testfastlines(ST77XX_RED, ST77XX_BLUE);
    delay(500);

    testdrawrects(ST77XX_GREEN);
    delay(500);

    testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
    delay(500);

    tft.fillScreen(ST77XX_BLACK);
    testfillcircles(10, ST77XX_BLUE);
    testdrawcircles(10, ST77XX_WHITE);
    delay(500);

    testroundrects();
    delay(500);

    testtriangles();
    delay(500);

    mediabuttons();
    delay(500);

    Serial.println("done");
    delay(1000);
}

static void st7789_loop(void)
{
    tft.invertDisplay(true);
    delay(500);
    tft.invertDisplay(false);
    delay(500);
}
RTDUINO_SKETCH_LOADER("ST7789", st7789_setup, st7789_loop);
