#include <rthw.h>
#include <rtthread.h>
#include <s3c24x0.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

/* ADCCON Register Bits */
#define S3C2410_ADCCON_ECFLG		(1<<15)
#define S3C2410_ADCCON_PRSCEN		(1<<14)
#define S3C2410_ADCCON_PRSCVL(x)	(((x)&0xFF)<<6)
#define S3C2410_ADCCON_PRSCVLMASK	(0xFF<<6)
#define S3C2410_ADCCON_SELMUX(x)	(((x)&0x7)<<3)
#define S3C2410_ADCCON_MUXMASK		(0x7<<3)
#define S3C2410_ADCCON_STDBM		(1<<2)
#define S3C2410_ADCCON_READ_START	(1<<1)
#define S3C2410_ADCCON_ENABLE_START	(1<<0)
#define S3C2410_ADCCON_STARTMASK	(0x3<<0)


/* ADCTSC Register Bits */
#define S3C2410_ADCTSC_UD_SEN		(1<<8) /* ghcstop add for s3c2440a */
#define S3C2410_ADCTSC_YM_SEN		(1<<7)
#define S3C2410_ADCTSC_YP_SEN		(1<<6)
#define S3C2410_ADCTSC_XM_SEN		(1<<5)
#define S3C2410_ADCTSC_XP_SEN		(1<<4)
#define S3C2410_ADCTSC_PULL_UP_DISABLE	(1<<3)
#define S3C2410_ADCTSC_AUTO_PST		(1<<2)
#define S3C2410_ADCTSC_XY_PST(x)	(((x)&0x3)<<0)

/* ADCDAT0 Bits */
#define S3C2410_ADCDAT0_UPDOWN		(1<<15)
#define S3C2410_ADCDAT0_AUTO_PST	(1<<14)
#define S3C2410_ADCDAT0_XY_PST		(0x3<<12)
#define S3C2410_ADCDAT0_XPDATA_MASK	(0x03FF)

/* ADCDAT1 Bits */
#define S3C2410_ADCDAT1_UPDOWN		(1<<15)
#define S3C2410_ADCDAT1_AUTO_PST	(1<<14)
#define S3C2410_ADCDAT1_XY_PST		(0x3<<12)
#define S3C2410_ADCDAT1_YPDATA_MASK	(0x03FF)

#define WAIT4INT(x)  (((x)<<8) | \
		     S3C2410_ADCTSC_YM_SEN | S3C2410_ADCTSC_YP_SEN | S3C2410_ADCTSC_XP_SEN | \
		     S3C2410_ADCTSC_XY_PST(3))

#define AUTOPST	     (S3C2410_ADCTSC_YM_SEN | S3C2410_ADCTSC_YP_SEN | S3C2410_ADCTSC_XP_SEN | \
		     S3C2410_ADCTSC_AUTO_PST | S3C2410_ADCTSC_XY_PST(0))

struct s3c2410ts
{
	long xp;
	long yp;
	int count;
	int shift;

	int delay;
	int presc;

	char phys[32];
};
static struct s3c2410ts ts;

#define X_MIN		74
#define X_MAX		934
#define Y_MIN		89
#define Y_MAX		920

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
void report_touch_input(int updown)
{
	long xp, yp;
	struct rtgui_event_mouse emouse;

	xp = ts.xp >> ts.shift;
	yp = ts.yp >> ts.shift;

	xp = 240 * (xp-X_MIN)/(X_MAX-X_MIN);
	yp = 320 - (320*(yp-Y_MIN)/(Y_MAX-Y_MIN));

	emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
	emouse.parent.sender = RT_NULL;

	emouse.x = xp;
	emouse.y = yp;

	/* set emouse button */
	if (updown)
	{
		emouse.button = RTGUI_MOUSE_BUTTON_DOWN;
	}
	else
	{
		emouse.button = RTGUI_MOUSE_BUTTON_UP;
	}

	/* rt_kprintf("touch %s: ts.x: %d, ts.y: %d, count:%d\n", updown? "down" : "up",
		xp, yp, ts.count); */

	emouse.button |= RTGUI_MOUSE_BUTTON_LEFT;

	rtgui_server_post_event((&emouse.parent), sizeof(emouse));
}
#endif

static int first_down_report;
/* fixed me, use timer to support move action */
static void touch_timer_fire(void)
{
	if (ts.count == 3)
	{
		 if (first_down_report)
		{
#ifdef RT_USING_RTGUI
			report_touch_input(1);
			first_down_report = 0;
#endif
		}
	}

	ADCTSC = S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST;
	ADCCON |= S3C2410_ADCCON_ENABLE_START;
}

void s3c2410_adc_stylus_action()
{
	rt_uint32_t data0;
	rt_uint32_t data1;

	SUBSRCPND |= BIT_SUB_ADC;

	data0 = ADCDAT0;
	data1 = ADCDAT1;
	
	ts.xp += data0 & S3C2410_ADCDAT0_XPDATA_MASK;
	ts.yp += data1 & S3C2410_ADCDAT1_YPDATA_MASK;
	ts.count++;

	if (ts.count < (1<<ts.shift))
	{
		ADCTSC = S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST;
		ADCCON |= S3C2410_ADCCON_ENABLE_START;
	}
	else
	{
		//touch_timer_fire();
		ADCTSC = WAIT4INT(1);
	}
}

void s3c2410_intc_stylus_updown()
{
	rt_uint32_t data0;
	rt_uint32_t data1;
	int updown;

	SUBSRCPND |= BIT_SUB_TC;

	data0 = ADCDAT0;
	data1 = ADCDAT1;

	updown = (!(data0 & S3C2410_ADCDAT0_UPDOWN)) && (!(data1 & S3C2410_ADCDAT0_UPDOWN));

	if (updown) 
	{
		touch_timer_fire();
	}
	else
	{
		if (ts.xp >= 0 && ts.yp >= 0)
		{
		#ifdef RT_USING_RTGUI
			report_touch_input(1);
			report_touch_input(0);
			first_down_report = 1;
		#endif
		}

		ts.xp = 0;
		ts.yp = 0;
		ts.count = 0;
	
		ADCTSC = WAIT4INT(0);
	}
}

void rt_touch_handler(int irqno)
{
	if (SUBSRCPND & (1 << 10))
	{
		/* INT_SUB_ADC */
		s3c2410_adc_stylus_action();
	}

	if (SUBSRCPND & (1 << 9))
	{
		/* INT_SUB_TC */
		s3c2410_intc_stylus_updown();
	}

	/* clear interrupt */
	INTPND |= (rt_uint32_t)(1 << INTADC);
}

void rt_hw_touch_init()
{
	/* init touch screen structure */
	rt_memset(&ts, 0, sizeof(struct s3c2410ts));

	ts.delay = 50000;
	ts.presc = 9;
	ts.shift = 2;
	ts.count = 0;
	ts.xp = ts.yp = 0;

	ADCCON = S3C2410_ADCCON_PRSCEN | S3C2410_ADCCON_PRSCVL(ts.presc);
	ADCDLY = ts.delay;

	ADCTSC = WAIT4INT(0);

	rt_hw_interrupt_install(INTADC, rt_touch_handler, RT_NULL);
	rt_hw_interrupt_umask(INTADC);

	/* clear interrupt */
	INTPND |= (rt_uint32_t)(1 << INTADC);
	
	SUBSRCPND |= BIT_SUB_TC;
	SUBSRCPND |= BIT_SUB_ADC;

	/* install interrupt handler */
	INTSUBMSK &= ~BIT_SUB_ADC;
	INTSUBMSK &= ~BIT_SUB_TC;

	first_down_report = 1;
}
