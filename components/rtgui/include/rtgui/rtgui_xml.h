#ifndef __RTGUI_XML_H__
#define __RTGUI_XML_H__

#include <rtgui/rtgui.h>

/* Types of events: start element, end element, text, attr name, attr
   val and start/end document. Other events can be ignored! */
enum {
	EVENT_START = 0, /* Start tag */
	EVENT_END,       /* End tag */
	EVENT_TEXT,      /* Text */
	EVENT_NAME,      /* Attribute name */
	EVENT_VAL,       /* Attribute value */
	EVENT_END_DOC,   /* End of document */
	EVENT_COPY,      /* Internal only; copies to internal buffer */
	EVENT_NONE       /* Internal only; should never see this event */
};

/* xml structure typedef */
typedef struct rtgui_xml rtgui_xml_t;
typedef int (*rtgui_xml_event_handler_t)(rt_uint8_t event, const char* text, rt_size_t len, void* user);

/* create a xml parser context */
rtgui_xml_t* rtgui_xml_create(rt_size_t buffer_size, rtgui_xml_event_handler_t handler, void* user);
/* destroy a xml parser context */
void rtgui_xml_destroy(rtgui_xml_t* rtgui_xml);

/* parse xml buffer */
int rtgui_xml_parse(rtgui_xml_t* rtgui_xml, const char* buf, rt_size_t len);

/* event string */
const char* rtgui_xml_event_str(rt_uint8_t event);

#endif
