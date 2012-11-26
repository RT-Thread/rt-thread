#ifndef __RTGUI_PROGRESSBAR_H__
#define __RTGUI_PROGRESSBAR_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(progressbar);
/** Gets the type of a progressbar */
#define RTGUI_PROGRESSBAR_TYPE       (RTGUI_TYPE(progressbar))
/** Casts the object to a rtgui_progressbar */
#define RTGUI_PROGRESSBAR(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_PROGRESSBAR_TYPE, rtgui_progressbar_t))
/** Checks if the object is a rtgui_progressbar */
#define RTGUI_IS_PROGRESSBAR(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_PROGRESSBAR_TYPE))

#define DEFAULT_WIDTH           100
#define DEFAULT_HEIGHT          20

struct rtgui_progressbar
{
    struct rtgui_widget parent;

    int orient;

    int range;
    int position;
};
typedef struct rtgui_progressbar rtgui_progressbar_t;

struct rtgui_progressbar *rtgui_progressbar_create(int orientation, int range, rtgui_rect_t *r);
void rtgui_progressbar_destroy(struct rtgui_progressbar *p_bar);

rt_bool_t rtgui_progressbar_event_handler(struct rtgui_object *object,
        struct rtgui_event *event);

void rtgui_progressbar_set_value(struct rtgui_progressbar *p_bar, int value);
int rtgui_progressbar_get_value(struct rtgui_progressbar *p_bar);
void rtgui_progressbar_set_range(struct rtgui_progressbar *p_bar, int range);
int rtgui_progressbar_get_range(struct rtgui_progressbar *p_bar);

#endif
