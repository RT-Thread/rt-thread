#ifndef _LED_MATRIX
#define _LED_MATRIX
#include <rtthread.h>

typedef struct RGBColor_TypeDef
{
    uint8_t G;
    uint8_t R;
    uint8_t B;
} RGBColor_TypeDef; // 颜色结构体

extern const RGBColor_TypeDef DARK;
extern const RGBColor_TypeDef GREEN;
extern const RGBColor_TypeDef RED;
extern const RGBColor_TypeDef BLUE;
extern const RGBColor_TypeDef WHITE;

extern void Set_LEDColor(uint16_t LedId, RGBColor_TypeDef Color);
extern void RGB_Reflash(void);
extern void led_matrix_rst();
#endif
