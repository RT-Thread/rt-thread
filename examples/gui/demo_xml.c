#include <rtthread.h>

#include <rtgui/rtgui_xml.h>

static int xml_event_handler(rt_uint8_t event, const char* text, rt_size_t len, void* user)
{
	rt_kprintf("%s: %s\n", rtgui_xml_event_str(event), text);
	return 1;
}

const char xml_str[] = "<?xml version=\"1.0\"?><note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>";
void demo_xml()
{
	rtgui_xml_t *xml;

	xml = rtgui_xml_create(512, xml_event_handler, RT_NULL);
	if (xml != RT_NULL)
	{
		rtgui_xml_parse(xml, xml_str, sizeof(xml_str));
		rtgui_xml_destroy(xml);
	}
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(demo_xml, show the demo of xml parser);
#endif
