/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-10-05     Meco Man      port to RTduino
 */

#include <RTduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;

static void st7789_setup(void)
{
    Serial.begin();

    // lcd init
    tft.init();
    tft.fillScreen(TFT_DARKCYAN);
    Serial.println("screen init success.");

    // lcd test
    tft.setTextColor(TFT_BLACK);
    tft.setCursor (12, 5);
    tft.print("Original ADAfruit font!");

    // The new larger fonts do not use the .setCursor call, coords are embedded
    tft.setTextColor(TFT_BLACK, TFT_BLACK); // Do not plot the background colour

    // Overlay the black text on top of the rainbow plot (the advantage of not drawing the backgorund colour!)
    tft.drawCentreString("Font size 2", 120, 14, 2); // Draw text centre at position 80, 12 using font 2

    tft.drawCentreString("Font size 4", 120, 30, 4); // Draw text centre at position 80, 24 using font 4

    tft.drawCentreString("12.34", 120, 54, 6); // Draw text centre at position 80, 24 using font 6

    tft.drawCentreString("12.34 is in font size 6", 120, 92, 2); // Draw text centre at position 80, 90 using font 2
}

static void st7789_loop(void)
{
    delay(500);
}
RTDUINO_SKETCH_LOADER("ST7789", st7789_setup, st7789_loop);
