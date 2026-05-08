#include <lvgl.h>
#include <rtthread.h>

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        rt_kprintf("LVGL button clicked!\n");
    }
}

static lv_obj_t *label;

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    lv_label_set_text_fmt(label, "%d%%", (int)lv_slider_get_value(slider));
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -10);
}

void lv_user_gui_init(void)
{
    lv_obj_t *scr = lv_scr_act();

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "Hello RT-Thread + LVGL!");
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t *btn = lv_btn_create(scr);
    lv_obj_set_size(btn, 120, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click Me!");

    lv_obj_t *slider = lv_slider_create(scr);
    lv_obj_set_width(slider, 200);
    lv_obj_align(slider, LV_ALIGN_BOTTOM_MID, 0, -40);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    label = lv_label_create(scr);
    lv_label_set_text(label, "0%");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -10);

    rt_kprintf("LVGL user GUI initialized\n");
}
