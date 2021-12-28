#include <U8g2lib.h>
#include <rtthread.h>
#define OLED_SPI_PIN_MOSI           GET_PIN(A,7)
#define OLED_SPI_PIN_SCK            GET_PIN(A,5)

// Use a different pin here rather than default SPI pins, which may cause issue
#define OLED_SPI_PIN_RES            GET_PIN(A,4)
#define OLED_SPI_PIN_DC             GET_PIN(A,6)
#define OLED_SPI_PIN_CS             GET_PIN(A,3)

// Check https://github.com/olikraus/u8g2/wiki/u8g2setupcpp for all supported devices
static U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0,\
                                            /* clock=*/ OLED_SPI_PIN_SCK,\
                                            /* data=*/ OLED_SPI_PIN_MOSI,\
                                            /* cs=*/ OLED_SPI_PIN_CS,\
                                            /* dc=*/ OLED_SPI_PIN_DC,\
                                            /* reset=*/ OLED_SPI_PIN_RES);

void test_ssd1327_oled_128_128()
{
    u8g2.begin();
    u8g2.clearBuffer();                         // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_tr);            // choose a suitable font
    u8g2.drawStr(1, 18, "U8g2 on SW SPI");   // write something to the internal memory
    u8g2.sendBuffer();                          // transfer internal memory to the display
    u8g2.setFont(u8g2_font_unifont_t_symbols);
    u8g2.drawGlyph(112, 56, 0x2603 );
    u8g2.sendBuffer();
}

