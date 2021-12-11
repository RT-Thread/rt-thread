/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#include <Arduino.h>
#include <board.h>

const pin_map_t pin_map_table[ARDUINO_LAYOUT_PIN_MAX]=
#ifdef RT_USING_ARDUINO_UNO_LAYOUT
{
    /*{RT-Thread Style, Arduino Style}*/
    {0, 0}, /* D0, RX */
    {0, 1}, /* D1, TX */
    {GET_PIN(D,10), 2}, /* D2, BSP:KEY0 */
    {0, 3}, /* D3, PWM */
    {GET_PIN(D,9), 4}, /* D4, BSP:KEY1 */
    {GET_PIN(D,8), 5}, /* D5, BSP:KEY2 */
    {0, 6}, /* D6, PWM */
    {0, 7}, /* D7 */
    {0, 8}, /* D8 */
    {0, 9}, /* D9, PWM */
    {GET_PIN(E,9), 10}, /* D10, PWM, BSP: RGB-BLUE */
    {GET_PIN(E,7), 11}, /* D11, PWM, BSP: RGB-RED */
    {GET_PIN(B,2), 12}, /* D12, BSP: BEEP */
    {GET_PIN(E,8), 13}, /* D13, LED_BUILTIN, BSP: RGB-GREEN */
    {0, A0}, /* D14, A0 */
    {0, A1}, /* D15, A1 */
    {0, A2}, /* D16, A2 */
    {0, A3}, /* D17, A3 */
    {0, A4}, /* D18, A4 */
    {0, A5} /* D19, A5 */
};
#endif /* RT_USING_ARDUINO_UNO_LAYOUT*/

void initVariant(void)
{

}
