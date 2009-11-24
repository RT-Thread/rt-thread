#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>
#include <string.h>

#include "listview.h"
#include "filelist.h"

static const char * next_xpm[] = {
"24 24 149 2",
"  	c None",
". 	c #373737",
"+ 	c #383838",
"@ 	c #3A3A3A",
"# 	c #393939",
"$ 	c #434343",
"% 	c #676767",
"& 	c #9D9D9D",
"* 	c #C1C1C1",
"= 	c #D3D3D3",
"- 	c #404040",
"; 	c #707070",
"> 	c #EDEDED",
", 	c #F5F5F5",
"' 	c #4A4A4A",
") 	c #909090",
"! 	c #D9D9D9",
"~ 	c #4B4B4B",
"{ 	c #939393",
"] 	c #CECECE",
"^ 	c #E4E4E4",
"/ 	c #E5E5E5",
"( 	c #444444",
"_ 	c #8B8B8B",
": 	c #ABABAB",
"< 	c #DCDCDC",
"[ 	c #D4D4D4",
"} 	c #D2D2D2",
"| 	c #DDDDDD",
"1 	c #DEDEDE",
"2 	c #DFDFDF",
"3 	c #414141",
"4 	c #B8B8B8",
"5 	c #BBBBBB",
"6 	c #ADADAD",
"7 	c #B7B7B7",
"8 	c #CFCFCF",
"9 	c #D8D8D8",
"0 	c #D6D6D6",
"a 	c #B2B2B2",
"b 	c #AEAEAE",
"c 	c #B6B6B6",
"d 	c #4C4C4C",
"e 	c #989898",
"f 	c #9E9E9E",
"g 	c #CDCDCD",
"h 	c #C5C5C5",
"i 	c #C7C7C7",
"j 	c #A1A1A1",
"k 	c #B3B3B3",
"l 	c #9F9F9F",
"m 	c #A2A2A2",
"n 	c #CACACA",
"o 	c #696969",
"p 	c #A0A0A0",
"q 	c #B1B1B1",
"r 	c #F1F1F1",
"s 	c #E3E3E3",
"t 	c #CCCCCC",
"u 	c #C6C6C6",
"v 	c #D1D1D1",
"w 	c #C2C2C2",
"x 	c #464646",
"y 	c #848484",
"z 	c #A4A4A4",
"A 	c #A9A9A9",
"B 	c #BFBFBF",
"C 	c #959595",
"D 	c #EFEFEF",
"E 	c #EEEEEE",
"F 	c #929292",
"G 	c #808080",
"H 	c #CBCBCB",
"I 	c #858585",
"J 	c #B9B9B9",
"K 	c #A5A5A5",
"L 	c #494949",
"M 	c #A7A7A7",
"N 	c #B0B0B0",
"O 	c #888888",
"P 	c #EAEAEA",
"Q 	c #777777",
"R 	c #6C6C6C",
"S 	c #C4C4C4",
"T 	c #757575",
"U 	c #A8A8A8",
"V 	c #A3A3A3",
"W 	c #949494",
"X 	c #9C9C9C",
"Y 	c #EBEBEB",
"Z 	c #575757",
"` 	c #4D4D4D",
" .	c #ACACAC",
"..	c #6B6B6B",
"+.	c #9A9A9A",
"@.	c #E9E9E9",
"#.	c #D7D7D7",
"$.	c #BDBDBD",
"%.	c #515151",
"&.	c #E8E8E8",
"*.	c #E2E2E2",
"=.	c #9B9B9B",
"-.	c #4E4E4E",
";.	c #B4B4B4",
">.	c #525252",
",.	c #BEBEBE",
"'.	c #8C8C8C",
").	c #AAAAAA",
"!.	c #AFAFAF",
"~.	c #E7E7E7",
"{.	c #5D5D5D",
"].	c #7E7E7E",
"^.	c #616161",
"/.	c #C8C8C8",
"(.	c #747474",
"_.	c #B5B5B5",
":.	c #6D6D6D",
"<.	c #4F4F4F",
"[.	c #5A5A5A",
"}.	c #A6A6A6",
"|.	c #919191",
"1.	c #8D8D8D",
"2.	c #DBDBDB",
"3.	c #7F7F7F",
"4.	c #E0E0E0",
"5.	c #C0C0C0",
"6.	c #828282",
"7.	c #595959",
"8.	c #C9C9C9",
"9.	c #E1E1E1",
"0.	c #E6E6E6",
"a.	c #D5D5D5",
"b.	c #626262",
"c.	c #ECECEC",
"d.	c #636363",
"e.	c #646464",
"f.	c #F0F0F0",
"g.	c #F3F3F3",
"h.	c #F4F4F4",
"i.	c #F6F6F6",
"j.	c #F7F7F7",
"k.	c #5E5E5E",
"l.	c #898989",
"m.	c #F9F9F9",
"n.	c #F8F8F8",
"o.	c #8A8A8A",
"p.	c #656565",
"q.	c #5C5C5C",
"r.	c #5F5F5F",
"                  . + @ @ + .                   ",
"            # $ % & * = = * & % $ #             ",
"          - ; * > , , , , , , > * ; -           ",
"        ' ) ! > > > > > > > > > > ! ) '         ",
"      ~ { ] ^ ^ / / / / / / / / / / ] { ~       ",
"    ( _ : < [ } | 1 2 2 2 2 1 | < < < : _ (     ",
"  3 ; & 4 = 5 6 7 8 9 ! ! ! 0 a b c = 4 & ; 3   ",
"  d e f 4 g b h i j k ] [ [ g l } m n 4 f e d   ",
"  o & p q i j * r s b { k t u ) v { w q j f o   ",
"x y l z A B C 4 D D E v F _ : G H I J A K j y x ",
"L { m M : N O N > > > > P 4 Q R S T U : U V W L ",
"~ X K A b 6 ; K Y Y Y Y Y Y 2 k S Z K b : M & ~ ",
"` f M  .N N ..+.@.@.@.@.@.@.#.f $.%.M a k q V ` ",
"` e U b a a R +.&.&.&.&.*.=.-.( ;.>.b ,.,.$.f ` ",
"-.'.).!.;.;.R +.&.&.~.7 {.Z ].L ;.^.B /./.i ) -.",
"  (.).N _.;.:.+.&.] T <.G ).A %.h _ n } } i (.  ",
"  [.}.q _.;.:.|.) ` :.K B t /.1.= l [ 2.2.c [.  ",
"  >.G _.B B 3.[.o =.,.= 4./ 2.K 5.k | s #.6.>.  ",
"    7.l S H 7 q 8.#.9.0.@.@./ g H a.&.0.M 7.    ",
"      b. .8 a.9 1 ^ &.Y c.E > c.c.E > 7 d.      ",
"        e.}.= s ~.Y > f.r g.h.i.j.@. .e.        ",
"          k.l.5.1 E g.i.j.m.n.Y /.o.k.          ",
"            [.p.6.m 5 H H ,.z 6.p.[.            ",
"                  q.k.r.r.k.q.                  "};

static const char * prev_xpm[] = {
"24 24 153 2",
"  	c None",
". 	c #373737",
"+ 	c #383838",
"@ 	c #3A3A3A",
"# 	c #393939",
"$ 	c #434343",
"% 	c #676767",
"& 	c #9D9D9D",
"* 	c #C1C1C1",
"= 	c #D3D3D3",
"- 	c #404040",
"; 	c #707070",
"> 	c #EDEDED",
", 	c #F5F5F5",
"' 	c #4A4A4A",
") 	c #909090",
"! 	c #D9D9D9",
"~ 	c #4B4B4B",
"{ 	c #939393",
"] 	c #CECECE",
"^ 	c #E5E5E5",
"/ 	c #E4E4E4",
"( 	c #444444",
"_ 	c #8B8B8B",
": 	c #ABABAB",
"< 	c #DCDCDC",
"[ 	c #DDDDDD",
"} 	c #DEDEDE",
"| 	c #DFDFDF",
"1 	c #D5D5D5",
"2 	c #D2D2D2",
"3 	c #DADADA",
"4 	c #414141",
"5 	c #B8B8B8",
"6 	c #D4D4D4",
"7 	c #BBBBBB",
"8 	c #AEAEAE",
"9 	c #AFAFAF",
"0 	c #D0D0D0",
"a 	c #D8D8D8",
"b 	c #ADADAD",
"c 	c #B5B5B5",
"d 	c #B7B7B7",
"e 	c #4C4C4C",
"f 	c #989898",
"g 	c #9E9E9E",
"h 	c #AAAAAA",
"i 	c #CCCCCC",
"j 	c #A3A3A3",
"k 	c #D1D1D1",
"l 	c #A1A1A1",
"m 	c #CDCDCD",
"n 	c #A5A5A5",
"o 	c #C5C5C5",
"p 	c #696969",
"q 	c #A0A0A0",
"r 	c #B1B1B1",
"s 	c #C8C8C8",
"t 	c #C9C9C9",
"u 	c #949494",
"v 	c #CACACA",
"w 	c #B9B9B9",
"x 	c #959595",
"y 	c #A7A7A7",
"z 	c #F1F1F1",
"A 	c #969696",
"B 	c #BCBCBC",
"C 	c #464646",
"D 	c #848484",
"E 	c #9F9F9F",
"F 	c #A4A4A4",
"G 	c #A9A9A9",
"H 	c #C2C2C2",
"I 	c #868686",
"J 	c #8E8E8E",
"K 	c #8C8C8C",
"L 	c #EFEFEF",
"M 	c #C6C6C6",
"N 	c #888888",
"O 	c #B2B2B2",
"P 	c #494949",
"Q 	c #A2A2A2",
"R 	c #828282",
"S 	c #777777",
"T 	c #737373",
"U 	c #E7E7E7",
"V 	c #C0C0C0",
"W 	c #797979",
"X 	c #A8A8A8",
"Y 	c #9C9C9C",
"Z 	c #B0B0B0",
"` 	c #686868",
" .	c #B6B6B6",
"..	c #EBEBEB",
"+.	c #5D5D5D",
"@.	c #9A9A9A",
"#.	c #4D4D4D",
"$.	c #ACACAC",
"%.	c #B3B3B3",
"&.	c #636363",
"*.	c #CFCFCF",
"=.	c #E9E9E9",
"-.	c #575757",
";.	c #515151",
">.	c #E8E8E8",
",.	c #BEBEBE",
"'.	c #BDBDBD",
").	c #4E4E4E",
"!.	c #B4B4B4",
"~.	c #646464",
"{.	c #525252",
"].	c #5F5F5F",
"^.	c #565656",
"/.	c #666666",
"(.	c #C7C7C7",
"_.	c #747474",
":.	c #929292",
"<.	c #555555",
"[.	c #6B6B6B",
"}.	c #C3C3C3",
"|.	c #5A5A5A",
"1.	c #A6A6A6",
"2.	c #C4C4C4",
"3.	c #BABABA",
"4.	c #838383",
"5.	c #DBDBDB",
"6.	c #808080",
"7.	c #BFBFBF",
"8.	c #858585",
"9.	c #5E5E5E",
"0.	c #E0E0E0",
"a.	c #E2E2E2",
"b.	c #D7D7D7",
"c.	c #595959",
"d.	c #E3E3E3",
"e.	c #E6E6E6",
"f.	c #626262",
"g.	c #D6D6D6",
"h.	c #ECECEC",
"i.	c #EEEEEE",
"j.	c #EAEAEA",
"k.	c #F0F0F0",
"l.	c #F3F3F3",
"m.	c #F4F4F4",
"n.	c #F6F6F6",
"o.	c #F7F7F7",
"p.	c #898989",
"q.	c #F9F9F9",
"r.	c #F8F8F8",
"s.	c #8A8A8A",
"t.	c #656565",
"u.	c #CBCBCB",
"v.	c #5C5C5C",
"                  . + @ @ + .                   ",
"            # $ % & * = = * & % $ #             ",
"          - ; * > , , , , , , > * ; -           ",
"        ' ) ! > > > > > > > > > > ! ) '         ",
"      ~ { ] ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ / / ] { ~       ",
"    ( _ : < < < [ } } | | | } } 1 2 3 : _ (     ",
"  4 ; & 5 6 7 8 9 0 a ! ! ! = 7 b c 0 d & ; 4   ",
"  e f g 5 ] h i j * k 6 k 5 l * m n o d g f e   ",
"  p & q r s & t u c v w x y } z m A B 9 l g p   ",
"C D E F G * ) H I q J K v > L L M N O y n l D C ",
"P { Q y : O R 7 S T 9 U > > > > V W E X X j u P ",
"~ Y n G 8 Z `  . .3 ............ .+.@.: : y & ~ ",
"#.g y $.r %.&.b j *.=.=.=.=.=.=.8 -.& Z %.r j #.",
"#.f X 8 %.c &.X ;.' ) } >.>.>.>.8 -.j B ,.'.g #.",
").K h 9 !.d ~.X {.W ].^.$.^ >.>.8 /. .(.s (.) ).",
"  _.h Z c 5 ~.X {.:.O :.<.[.o =.H J }.0 2 (._.  ",
"  |.1.r c 5 ~.X {.f 2.i 3.4.T !.s Q ] ! 5. .|.  ",
"  {.6.c 7.H S 8.9.n *.} 0.[ *.O X  .! a.b.R {.  ",
"    c.E 2.m  .j G m 0.U =.=.U d.b.b.e.e.y c.    ",
"      f.$.0 g.g.a | U ..h.i.i.L i.L h.d &.      ",
"        ~.1.= d.U j.> k.z l.m.n.o.=.$.~.        ",
"          9.p.V } i.l.n.o.q.r...s s.9.          ",
"            |.t.R Q 7 u.u.,.F R t.|.            ",
"                  v.9.].].9.v.                  "};

static rtgui_image_t *background = RT_NULL;
static rtgui_image_t *next = RT_NULL, *prev = RT_NULL;

static struct rtgui_view* function_view;
static struct rtgui_view* home_view;
static struct rtgui_workbench* workbench;

void player_play_list(const char** list);
void player_play_file(const char * fn);
void player_next(void);
void player_prev(void);

void function_filelist(void* parameter)
{
	rtgui_rect_t rect;
	filelist_view_t *view;

	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	view = filelist_view_create(workbench, "/", "*.*", &rect);
	if (view != RT_NULL)
	{
	    if (rtgui_view_show(RTGUI_VIEW(view), RT_TRUE) == RTGUI_MODAL_OK)
	    {
			char fn[64];
			
	    	/* get open file */
			rt_kprintf("dir %s\n", view->current_directory);
			rt_kprintf("item %s\n", view->items[view->current_item].name);
			
			rt_snprintf(fn, 64, "%s/%s", view->current_directory,
				view->items[view->current_item].name);

			rtgui_view_show(home_view, RT_FALSE);

			player_play_file(fn);
	    }
		
		/* destroy view */
		filelist_view_destroy(view);
	}

	return;
}

void function_device(void* parameter)
{
	rtgui_view_t *view;
	extern rtgui_view_t* device_view_create(rtgui_workbench_t* workbench);
	
	view = device_view_create(workbench);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

void function_player(void* parameter)
{
    rtgui_view_show(home_view, RT_FALSE);
	return;
}

void function_action(void* parameter)
{
	rt_kprintf("item action!\n");
	return;
}

struct list_item function_list[] =
{
	{"选择电台", RT_NULL, function_action, RT_NULL},
	{"更新电台", RT_NULL, function_action, RT_NULL},
	{"播放文件", RT_NULL, function_filelist, RT_NULL},
	{"设备信息", RT_NULL, function_device, RT_NULL},
	{"返回播放器", RT_NULL, function_player, RT_NULL},
};

static rt_bool_t home_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);

		/* draw background */
	    background = rtgui_image_create_from_file("hdc",
	        "/resource/bg.hdc", RT_FALSE);
		if (background != RT_NULL)
		{
            rtgui_image_blit(background, dc, &rect);
			rtgui_image_destroy(background);
			
			background = RT_NULL;
		}
		else
		{
			rtgui_dc_fill_rect(dc, &rect);
		}

		/* draw playing information */
		rect.x1 = 10; rect.y1 = 260;
		rect.x2 = 25; rect.y2 = 285;
		if (prev != RT_NULL) rtgui_image_blit(prev, dc, &rect);
		if (next != RT_NULL)
		{
			rect.x2 = 230; rect.x1 = rect.x2 - 25;
			rtgui_image_blit(next, dc, &rect);
		}

		rect.x1 = 35; rect.y1 = 260;
		rect.x2 = 205; rect.y2 = 285;
		rtgui_dc_fill_rect(dc, &rect);
		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}
	else if (event->type == RTGUI_EVENT_KBD)
	{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		if (ekbd->type == RTGUI_KEYDOWN)
		{
			switch (ekbd->key)
			{
			case RTGUIK_RIGHT:
			case RTGUIK_LEFT:
				break;

			case RTGUIK_DOWN:
                rtgui_view_show(function_view, RT_FALSE);
				break;
			}
		}
		return RT_FALSE;
	}

	return rtgui_view_event_handler(widget, event);
}

rt_bool_t today_workbench_event_handler(rtgui_widget_t *widget, rtgui_event_t *event)
{
    if (event->type == RTGUI_EVENT_KBD)
    {
        struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
        if ((ekbd->type == RTGUI_KEYUP) && ekbd->key == RTGUIK_HOME)
        {
            /* active home view */
            if (workbench->current_view != home_view)
            {
                rtgui_view_show(home_view, RT_FALSE);
                return RT_FALSE;
            }
        }
    }

    return rtgui_workbench_event_handler(widget, event);
}

static void player_entry(void* parameter)
{
	rt_mq_t mq;
	rtgui_rect_t rect;

	mq = rt_mq_create("qPlayer", 256, 4, RT_IPC_FLAG_FIFO);
	rtgui_thread_register(rt_thread_self(), mq);

	next = rtgui_image_create_from_mem("xpm", (rt_uint8_t*)next_xpm, 
		sizeof(next_xpm));
	prev = rtgui_image_create_from_mem("xpm", (rt_uint8_t*)prev_xpm,
		sizeof(prev_xpm));

	workbench = rtgui_workbench_create("main", "workbench");
	if (workbench == RT_NULL) return;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(workbench), today_workbench_event_handler);

    /* add home view */
	home_view = rtgui_view_create("Home");
	rtgui_widget_set_event_handler(RTGUI_WIDGET(home_view), home_view_event_handler);

	rtgui_workbench_add_view(workbench, home_view);
	/* this view can be focused */
	RTGUI_WIDGET(home_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	/* set widget focus */
	rtgui_widget_focus(RTGUI_WIDGET(home_view));

	rtgui_view_show(home_view, RT_FALSE);

    /* add function view */
	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	function_view = (struct rtgui_view*)list_view_create(function_list,
		sizeof(function_list)/sizeof(struct list_item),
		&rect);
	rtgui_workbench_add_view(workbench, function_view);

	rtgui_workbench_event_loop(workbench);

	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

enum PLAYER_MODE
{
	PLAYER_SINGLE,
	PLAYER_FILE,
	PLAYER_RADIO,
};

enum PLAYER_REQUEST_TYPE
{
	PLAYER_REQUEST_PLAY_SINGLE_FILE,
	PLAYER_REQUEST_PLAY_LIST,
	PLAYER_REQUEST_STOP,
	PLAYER_REQUEST_NEXT,
	PLAYER_REQUEST_PREV,
};

struct player_request
{
	enum PLAYER_REQUEST_TYPE type;

	char fn[64];
};
static rt_mq_t player_thread_mq;

void player_play_list(const char** list)
{
}

void player_play_file(const char* fn)
{
	struct player_request request;
	request.type = PLAYER_REQUEST_PLAY_SINGLE_FILE;
	strncpy(request.fn, fn, sizeof(request.fn));

	/* send to message queue */
	rt_mq_send(player_thread_mq, (void*)&request, sizeof(struct player_request));
}

void player_stop()
{
}

void player_next()
{
}

void player_prev()
{
}

void player_thread(void* parameter)
{
	rt_err_t result;
	struct player_request request;
	
	while(1)
	{
		/* get request from message queue */
		result = rt_mq_recv(player_thread_mq, (void*)&request, 
			sizeof(struct player_request), RT_WAITING_FOREVER);
		if (result == RT_EOK)
		{
			switch (request.type)
			{
			case PLAYER_REQUEST_PLAY_SINGLE_FILE:
				if ((strstr(request.fn, ".mp3") != RT_NULL) ||
					(strstr(request.fn, ".MP3") != RT_NULL))
				{
					mp3(request.fn);
				}
				else if ((strstr(request.fn, ".wav") != RT_NULL) ||
					(strstr(request.fn, ".WAV") != RT_NULL))
				{
					wav(request.fn);
				}
				break;
			}
		}
	}
}

void player_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("player",
        player_entry, RT_NULL,
        2048, RTGUI_APP_THREAD_PRIORITY, RTGUI_APP_THREAD_TIMESLICE);

    if (tid != RT_NULL) rt_thread_startup(tid);

	/* create player thread */
	player_thread_mq = rt_mq_create("player", sizeof(struct player_request),
		8, RT_IPC_FLAG_FIFO);
	RT_ASSERT(player_thread_mq != RT_NULL);

	tid = rt_thread_create("pthread", player_thread, RT_NULL,
		2048, RTGUI_APP_THREAD_PRIORITY, RTGUI_APP_THREAD_TIMESLICE);
	if (tid != RT_NULL) rt_thread_startup(tid);
}

