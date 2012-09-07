
#include <rtgui/widgets/plot.h>

#include "demo_view.h"

/* sin data */
rt_int16_t sin_ydata[] = {
    0, 9, 19, 29, 38, 47, 56, 64, 71, 78, 84, 89, 93, 96, 98, 99, 99, 99, 97,
    94, 90, 86, 80, 74, 67, 59, 51, 42, 33, 23, 14, 4, -5, -15, -25, -35, -44,
    -52, -61, -68, -75, -81, -87, -91, -95, -97, -99, -99, -99, -98, -95, -92,
    -88, -83, -77, -70, -63, -55, -46, -37, -27, -18, -8, 1, 11, 21, 31
};
rt_int16_t cos_ydata[] = {
    50, 49, 46, 41, 34, 27, 18, 8, -1, -11, -20, -29, -36, -42, -47, -49, -49,
    -48, -44, -39, -32, -24, -15, -5, 4, 14, 23, 31, 38, 44, 48, 49, 49, 47,
    43, 37, 30, 21, 12, 2, -7, -16, -25, -33, -40, -45, -48, -49, -49, -46,
    -41, -35, -28, -19, -9, 0, 10, 19, 28, 36, 42, 46, 49, 49, 48, 45, 40, 33,
    25, 16, 6, -3, -12, -22, -30, -37, -43, -47, -49, -49, -47, -44, -38, -31,
    -23, -13, -3, 6, 15, 24, 33, 39, 45, 48, 49, 49, 46, 42, 36, 29, 20, 10, 1,
    -8, -18, -27, -35, -41, -46, -49, -49, -48, -45, -41, -34, -26, -17, -8, 1,
    11, 21, 29, 37, 43, 47, 49, 49, 48, 44, 39, 32, 24, 14, 5, -4, -14, -23,
    -32, -39, -44, -48, -49, -49, -47, -43, -37, -30, -21, -12, -2, 7, 17, 26,
    34, 40, 45, 48, 49, 49, 46, 41, 35, 27, 18, 9, 0, -10, -20, -28, -36, -42,
    -46, -49, -49, -48, -45, -40, -33, -25, -16, -6, 3, 13, 22, 31, 38, 43, 47,
    49, 49, 47, 43, 38
};

struct rtgui_container* demo_plot(void)
{
    struct rtgui_container *cnt;
    struct rtgui_plot_curve *curve1, *curve2, *curve3;
    struct rtgui_plot *plot;
    struct rtgui_rect rect;

    cnt = demo_view("ÇúÏß»æÍ¼");

    curve1 = rtgui_plot_curve_create();
    curve1->y_data = sin_ydata;
    curve1->length = sizeof(sin_ydata)/sizeof(sin_ydata[0]);
    curve1->color = red;

    plot = rtgui_plot_create(curve1);

    curve2 = rtgui_plot_curve_create();
    curve2->y_data = cos_ydata;
    curve2->length = sizeof(cos_ydata)/sizeof(cos_ydata[0]);
    curve2->color = blue;
    rtgui_plot_append_curve(plot, curve2);

    curve3 = rtgui_plot_curve_create();
    curve3->x_data = cos_ydata;
    curve3->y_data = sin_ydata;
    curve3->length = sizeof(sin_ydata)/sizeof(sin_ydata[0]);
    curve3->color = black;
    rtgui_plot_append_curve(plot, curve3);

    rtgui_widget_get_rect(RTGUI_WIDGET(cnt), &rect);
    rtgui_widget_set_rect(RTGUI_WIDGET(plot), &rect);
    rtgui_plot_set_base_point(plot,
            rtgui_rect_width(rect)/3, rtgui_rect_height(rect)/2);

    rtgui_container_add_child(cnt, RTGUI_WIDGET(plot));

    return cnt;
}
