/*************************************************************************************
 *
 *	File name:	sep4020.h
 *
 * Change Logs:
 * Date           Author       Notes	        
 * 2010-03-17     zchong      first version		      	
 **************************************************************************************/

#ifndef __SEP4020_H__
#define __SEP4020_H__

/*************************************
	macros for INTC
*************************************/

/*interrupt resources */

#define     INTGLOBAL		        32

#define		INT_RTC					31		        
#define		INT_DMAC				30	                
#define		INT_EMI					29              
#define		INT_MAC		  			28                  
#define		INT_TIMER1				27                  
#define		INT_TIMER2				26              
#define 	INT_TIMER3 				25              
#define		INT_UART0				24              
#define		INT_UART1				23              
#define		INT_UART2				22              
#define		INT_UART3			    21              
#define		INT_PWM					20	                
#define		INT_LCDC	   			19	            
#define		INT_I2S			    	18              
#define		INT_SSI 				17	            
#define		INT_NOTUSED16			16
#define		INT_USB 				15              
#define		INT_SMC0				14				
#define		INT_SMC1				13              
#define		INT_SDIO				12              
#define		INT_EXINT10				11              
#define		INT_EXINT9 				10              
#define		INT_EXINT8 				9               
#define		INT_EXINT7 				8               
#define		INT_EXINT6 				7               
#define		INT_EXINT5 				6               
#define		INT_EXINT4 				5               
#define		INT_EXINT3 				4               
#define		INT_EXINT2 				3               
#define		INT_EXINT1 				2               
#define		INT_EXINT0				1
#define		INT_NOTUSED0			0

/******************************************************************************************
 *  INTC模块
 *  基址: 0x10000000
 ******************************************************************************************/

#define INTC_IER        (*(volatile unsigned *)0x10000000)  /* IRQ interrupt enable register    */
#define INTC_IMR        (*(volatile unsigned *)0x10000008)  /* IRQ interrupt mask register      */
#define INTC_IFR        (*(volatile unsigned *)0x10000010)  /* IRQ软件强制中断寄存器    */
#define INTC_IRSR       (*(volatile unsigned *)0x10000018)  /* IRQ未处理中断状态寄存器  */
#define INTC_ISR        (*(volatile unsigned *)0x10000020)  /* IRQ中断状态寄存器        */
#define INTC_IMSR       (*(volatile unsigned *)0x10000028)  /* IRQ屏蔽中断状态寄存器    */
#define INTC_IFSR       (*(volatile unsigned *)0x10000030)  /* IRQ中断最终状态寄存器    */
#define INTC_FIER       (*(volatile unsigned *)0x100000C0)  /* FIQ中断允许寄存器        */
#define INTC_FIMR       (*(volatile unsigned *)0x100000C4)  /* FIQ中断屏蔽寄存器        */
#define INTC_FIFR       (*(volatile unsigned *)0x100000C8)  /* FIQ软件强制中断寄存器    */
#define INTC_FIRSR      (*(volatile unsigned *)0x100000CC)  /* FIQ未处理中断状态寄存器  */
#define INTC_FISR       (*(volatile unsigned *)0x100000D0)  /* FIQ中断状态寄存器        */
#define INTC_FIFSR      (*(volatile unsigned *)0x100000D4)  /* FIQ中断最终状态寄存器    */
#define INTC_IPLR       (*(volatile unsigned *)0x100000D8)  /* IRQ中断优先级寄存器      */
#define INTC_ICR1       (*(volatile unsigned *)0x100000DC)  /* IRQ内部中断优先级控制寄存器1 */
#define INTC_ICR2       (*(volatile unsigned *)0x100000E0)  /* IRQ内部中断优先级控制寄存器2 */
#define INTC_EXICR1     (*(volatile unsigned *)0x100000E4)  /* IRQ外部中断优先级控制寄存器1 */
#define INTC_EXICR2     (*(volatile unsigned *)0x100000E8)  /* IRQ外部中断优先级控制寄存器2 */


/******************************************************************************************
 *  PMC模块
 *  基址: 0x10001000
 ******************************************************************************************/

#define PMC_PLTR        (*(volatile unsigned *)0x10001000)  /* PLL的稳定过渡时间 */
#define PMC_PMCR        (*(volatile unsigned *)0x10001004)  /* 系统主时钟PLL的控制寄存器 */
#define PMC_PUCR        (*(volatile unsigned *)0x10001008)  /* USB时钟PLL的控制寄存器 */
#define PMC_PCSR        (*(volatile unsigned *)0x1000100C)  /* 内部模块时钟源供给的控制寄存器 */
#define PMC_PDSLOW      (*(volatile unsigned *)0x10001010)  /* SLOW状态下时钟的分频因子 */
#define PMC_PMDR        (*(volatile unsigned *)0x10001014)  /* 芯片工作模式寄存器 */
#define PMC_RCTR        (*(volatile unsigned *)0x10001018)  /* Reset控制寄存器 */
#define PMC_CLRWAKUP    (*(volatile unsigned *)0x1000101C)  /* WakeUp清除寄存器 */


/******************************************************************************************
 *  RTC模块
 *  基址: 0x10002000
 ******************************************************************************************/

#define RTC_STA_YMD         (*(volatile unsigned *)0x10002000)  /* 年, 月, 日计数寄存器 */
#define RTC_STA_HMS         (*(volatile unsigned *)0x10002004)  /* 小时, 分钟, 秒寄存器 */
#define RTC_ALARM_ALL       (*(volatile unsigned *)0x10002008)  /* 定时月, 日, 时, 分寄存器 */
#define RTC_CTR             (*(volatile unsigned *)0x1000200C)  /* 控制寄存器 */
#define RTC_INT_EN          (*(volatile unsigned *)0x10002010)  /* 中断使能寄存器 */
#define RTC_INT_STS         (*(volatile unsigned *)0x10002014)  /* 中断状态寄存器 */
#define RTC_SAMP            (*(volatile unsigned *)0x10002018)  /* 采样周期寄存器 */
#define RTC_WD_CNT          (*(volatile unsigned *)0x1000201C)  /* Watch-Dog计数值寄存器 */
#define RTC_WD_SEV          (*(volatile unsigned *)0x10002020)  /* Watch-Dog服务寄存器 */ 
#define RTC_CONFIG_CHECK    (*(volatile unsigned *)0x10002024)  /* 配置时间确认寄存器 (在配置时间之前先写0xaaaaaaaa) */
#define RTC_SOFTRESET       (*(volatile unsigned *)0x10002028)  /* 软件复位控制寄存器, 4020中被去掉了 */
#define RTC_KEY0            (*(volatile unsigned *)0x1000202C)  /* 密钥寄存器0, 4020中只有这一个寄存器 */
#define RTC_KEY1            (*(volatile unsigned *)0x10002030)  /* 密钥寄存器1 */
#define RTC_KEY2            (*(volatile unsigned *)0x10002034)  /* 密钥寄存器2 */
#define RTC_KEY3            (*(volatile unsigned *)0x10002038)  /* 密钥寄存器3 */
#define RTC_KEY4            (*(volatile unsigned *)0x1000203C)  /* 密钥寄存器4 */
#define RTC_KEY5            (*(volatile unsigned *)0x10002040)  /* 密钥寄存器5 */


/******************************************************************************************
 *  TIMER模块
 *  基址: 0x10003000
 ******************************************************************************************/

#define TIMER_T1LCR         (*(volatile unsigned *)0x10003000)  /* 通道1加载计数寄存器 */
#define TIMER_T1CCR         (*(volatile unsigned *)0x10003004)  /* 通道1当前计数值寄存器 */
#define TIMER_T1CR          (*(volatile unsigned *)0x10003008)  /* 通道1控制寄存器 */
#define TIMER_T1ISCR        (*(volatile unsigned *)0x1000300C)  /* 通道1中断状态清除寄存器 */
#define TIMER_T1IMSR        (*(volatile unsigned *)0x10003010)  /* 通道1中断屏蔽状态寄存器 */
#define TIMER_T2LCR         (*(volatile unsigned *)0x10003020)  /* 通道2加载计数寄存器 */
#define TIMER_T2CCR         (*(volatile unsigned *)0x10003024)  /* 通道2当前计数值寄存器 */
#define TIMER_T2CR          (*(volatile unsigned *)0x10003028)  /* 通道2控制寄存器 */
#define TIMER_T2ISCR        (*(volatile unsigned *)0x1000302C)  /* 通道2中断状态清除寄存器 */
#define TIMER_T2IMSR        (*(volatile unsigned *)0x10003030)  /* 通道2中断屏蔽状态寄存器 */
#define TIMER_T3LCR         (*(volatile unsigned *)0x10003040)  /* 通道3加载计数寄存器 */
#define TIMER_T3CCR         (*(volatile unsigned *)0x10003044)  /* 通道3当前计数值寄存器 */
#define TIMER_T3CR          (*(volatile unsigned *)0x10003048)  /* 通道3控制寄存器 */
#define TIMER_T3ISCR        (*(volatile unsigned *)0x1000304C)  /* 通道3中断状态清除寄存器 */
#define TIMER_T3IMSR        (*(volatile unsigned *)0x10003050)  /* 通道3中断屏蔽状态寄存器 */
#define TIMER_T3CAPR        (*(volatile unsigned *)0x10003054)  /* 通道3捕获寄存器 */
#define TIMER_T4LCR         (*(volatile unsigned *)0x10003060)  /* 通道4加载计数寄存器 */
#define TIMER_T4CCR         (*(volatile unsigned *)0x10003064)  /* 通道4当前计数值寄存器 */
#define TIMER_T4CR          (*(volatile unsigned *)0x10003068)  /* 通道4控制寄存器 */
#define TIMER_T4ISCR        (*(volatile unsigned *)0x1000306C)  /* 通道4中断状态清除寄存器 */
#define TIMER_T4IMSR        (*(volatile unsigned *)0x10003070)  /* 通道4中断屏蔽状态寄存器 */
#define TIMER_T4CAPR        (*(volatile unsigned *)0x10003074)  /* 通道4捕获寄存器 */
#define TIMER_T5LCR         (*(volatile unsigned *)0x10003080)  /* 通道5加载计数寄存器 */
#define TIMER_T5CCR         (*(volatile unsigned *)0x10003084)  /* 通道5当前计数值寄存器 */
#define TIMER_T5CR          (*(volatile unsigned *)0x10003088)  /* 通道5控制寄存器 */
#define TIMER_T5ISCR        (*(volatile unsigned *)0x1000308C)  /* 通道5中断状态清除寄存器 */
#define TIMER_T5IMSR        (*(volatile unsigned *)0x10003090)  /* 通道5中断屏蔽状态寄存器 */
#define TIMER_T5CAPR        (*(volatile unsigned *)0x10003094)  /* 通道5捕获寄存器 */
#define TIMER_T6LCR         (*(volatile unsigned *)0x100030A0)  /* 通道6加载计数寄存器 */
#define TIMER_T6CCR         (*(volatile unsigned *)0x100030A4)  /* 通道6当前计数值寄存器 */
#define TIMER_T6CR          (*(volatile unsigned *)0x100030A8)  /* 通道6控制寄存器 */
#define TIMER_T6ISCR        (*(volatile unsigned *)0x100030AC)  /* 通道6中断状态清除寄存器 */
#define TIMER_T6IMSR        (*(volatile unsigned *)0x100030B0)  /* 通道6中断屏蔽状态寄存器 */
#define TIMER_T6CAPR        (*(volatile unsigned *)0x100030B4)  /* 通道6捕获寄存器 */
#define TIMER_T7LCR         (*(volatile unsigned *)0x100030C0)  /* 通道7加载计数寄存器 */
#define TIMER_T7CCR         (*(volatile unsigned *)0x100030C4)  /* 通道7当前计数值寄存器 */
#define TIMER_T7CR          (*(volatile unsigned *)0x100030C8)  /* 通道7控制寄存器 */
#define TIMER_T7ISCR        (*(volatile unsigned *)0x100030CC)  /* 通道7中断状态清除寄存器 */
#define TIMER_T7IMSR        (*(volatile unsigned *)0x100030D0)  /* 通道7中断屏蔽状态寄存器 */
#define TIMER_T8LCR         (*(volatile unsigned *)0x100030E0)  /* 通道8加载计数寄存器 */
#define TIMER_T8CCR         (*(volatile unsigned *)0x100030E4)  /* 通道8当前计数值寄存器 */
#define TIMER_T8CR          (*(volatile unsigned *)0x100030E8)  /* 通道8控制寄存器 */
#define TIMER_T8ISCR        (*(volatile unsigned *)0x100030EC)  /* 通道8中断状态清除寄存器 */
#define TIMER_T8IMSR        (*(volatile unsigned *)0x100030F0)  /* 通道8中断屏蔽状态寄存器 */
#define TIMER_T9LCR         (*(volatile unsigned *)0x10003100)  /* 通道9加载计数寄存器 */
#define TIMER_T9CCR         (*(volatile unsigned *)0x10003104)  /* 通道9当前计数值寄存器 */
#define TIMER_T9CR          (*(volatile unsigned *)0x10003108)  /* 通道9控制寄存器 */
#define TIMER_T9ISCR        (*(volatile unsigned *)0x1000310C)  /* 通道9中断状态清除寄存器 */
#define TIMER_T9IMSR        (*(volatile unsigned *)0x10003110)  /* 通道9中断屏蔽状态寄存器 */
#define TIMER_T10LCR        (*(volatile unsigned *)0x10003120)  /* 通道10加载计数寄存器 */
#define TIMER_T10CCR        (*(volatile unsigned *)0x10003124)  /* 通道10当前计数值寄存器 */
#define TIMER_T10CR         (*(volatile unsigned *)0x10003128)  /* 通道10控制寄存器 */
#define TIMER_T10ISCR       (*(volatile unsigned *)0x1000312C)  /* 通道10中断状态清除寄存器 */
#define TIMER_T10IMSR       (*(volatile unsigned *)0x10003130)  /* 通道10中断屏蔽状态寄存器 */
#define TIMER_TIMSR         (*(volatile unsigned *)0x10003140)  /* TIMER中断屏蔽状态寄存器 */
#define TIMER_TISCR         (*(volatile unsigned *)0x10003144)  /* TIMER中断状态清除寄存器 */
#define TIMER_TISR          (*(volatile unsigned *)0x10003148)  /* TIMER中断状态寄存器 */


/******************************************************************************************
 *  PWM模块
 *  基址: 0x10004000
 ******************************************************************************************/

#define PWM1_CTRL           (*(volatile unsigned *)0x10004000)  /* PWM1控制寄存器 */
#define PWM1_DIV            (*(volatile unsigned *)0x10004004)  /* PWM1分频寄存器 */
#define PWM1_PERIOD         (*(volatile unsigned *)0x10004008)  /* PWM1周期寄存器 */
#define PWM1_DATA           (*(volatile unsigned *)0x1000400C)  /* PWM1数据寄存器 */
#define PWM1_CNT            (*(volatile unsigned *)0x10004010)  /* PWM1计数寄存器 */
#define PWM1_STATUS         (*(volatile unsigned *)0x10004014)  /* PWM1状态寄存器 */
#define PWM2_CTRL           (*(volatile unsigned *)0x10004020)  /* PWM2控制寄存器 */
#define PWM2_DIV            (*(volatile unsigned *)0x10004024)  /* PWM2分频寄存器 */
#define PWM2_PERIOD         (*(volatile unsigned *)0x10004028)  /* PWM2周期寄存器 */
#define PWM2_DATA           (*(volatile unsigned *)0x1000402C)  /* PWM2数据寄存器 */
#define PWM2_CNT            (*(volatile unsigned *)0x10004030)  /* PWM2计数寄存器 */
#define PWM2_STATUS         (*(volatile unsigned *)0x10004034)  /* PWM2状态寄存器 */
#define PWM3_CTRL           (*(volatile unsigned *)0x10004040)  /* PWM3控制寄存器 */
#define PWM3_DIV            (*(volatile unsigned *)0x10004044)  /* PWM3分频寄存器 */
#define PWM3_PERIOD         (*(volatile unsigned *)0x10004048)  /* PWM3周期寄存器 */
#define PWM3_DATA           (*(volatile unsigned *)0x1000404C)  /* PWM3数据寄存器 */
#define PWM3_CNT            (*(volatile unsigned *)0x10004050)  /* PWM3计数寄存器 */
#define PWM3_STATUS         (*(volatile unsigned *)0x10004054)  /* PWM3状态寄存器 */
#define PWM4_CTRL           (*(volatile unsigned *)0x10004060)  /* PWM4控制寄存器 */
#define PWM4_DIV            (*(volatile unsigned *)0x10004064)  /* PWM4分频寄存器 */
#define PWM4_PERIOD         (*(volatile unsigned *)0x10004068)  /* PWM4周期寄存器 */
#define PWM4_DATA           (*(volatile unsigned *)0x1000406C)  /* PWM4数据寄存器 */
#define PWM4_CNT            (*(volatile unsigned *)0x10004070)  /* PWM4计数寄存器 */
#define PWM4_STATUS         (*(volatile unsigned *)0x10004074)  /* PWM4状态寄存器 */
#define PWM_INTMASK         (*(volatile unsigned *)0x10004080)  /* PWM中断屏蔽寄存器 */
#define PWM_INT             (*(volatile unsigned *)0x10004084)  /* PWM中断寄存器 */
#define PWM_ENABLE          (*(volatile unsigned *)0x10004088)    /* PWM使能寄存器 */


/******************************************************************************************
 *  UART0模块
 *  基址: 0x10005000
 ******************************************************************************************/
#define UART0BASE            ((volatile unsigned *)0x10005000)
#define UART0_DLBL          (*(volatile unsigned char*)0x10005000)  /* 波特率设置低八位寄存器 */
#define UART0_RXFIFO        (*(volatile unsigned char*)0x10005000)  /* 接收FIFO */
#define UART0_TXFIFO        (*(volatile unsigned char*)0x10005000)  /* 发送FIFO */
#define UART0_DLBH          (*(volatile unsigned char*)0x10005004)  /* 波特率设置高八位寄存器 */
#define UART0_IER           (*(volatile unsigned char*)0x10005004)  /* 中断使能寄存器 */
#define UART0_IIR           (*(volatile unsigned *)0x10005008)  /* 中断识别寄存器 */
#define UART0_FCR           (*(volatile unsigned *)0x10005008)  /* FIFO控制寄存器 */
#define UART0_LCR           (*(volatile unsigned *)0x1000500C)  /* 行控制寄存器 */
#define UART0_MCR           (*(volatile unsigned *)0x10005010)  /* Modem控制寄存器 */
#define UART0_LSR           (*(volatile unsigned *)0x10005014)  /* 行状态寄存器 */
#define UART0_MSR           (*(volatile unsigned *)0x10005018)  /* Modem状态寄存器 */


/******************************************************************************************
 *  UART1模块
 *  基址: 0x10006000
 ******************************************************************************************/
 #define UART1BASE            ((volatile unsigned *)0x10006000)
#define UART1_DLBL          (*(volatile unsigned *)0x10006000)  /* 波特率设置低八位寄存器 */
#define UART1_RXFIFO        (*(volatile unsigned *)0x10006000)  /* 接收FIFO */
#define UART1_TXFIFO        (*(volatile unsigned *)0x10006000)  /* 发送FIFO */
#define UART1_DLBH          (*(volatile unsigned *)0x10006004)  /* 波特率设置高八位寄存器 */
#define UART1_IER           (*(volatile unsigned *)0x10006004)  /* 中断使能寄存器 */
#define UART1_IIR           (*(volatile unsigned *)0x10006008)  /* 中断识别寄存器 */
#define UART1_FCR           (*(volatile unsigned *)0x10006008)  /* FIFO控制寄存器 */
#define UART1_LCR           (*(volatile unsigned *)0x1000600C)  /* 行控制寄存器 */
#define UART1_MCR           (*(volatile unsigned *)0x10006010)  /* Modem控制寄存器 */
#define UART1_LSR           (*(volatile unsigned *)0x10006014)  /* 行状态寄存器 */
#define UART1_MSR           (*(volatile unsigned *)0x10006018)  /* Modem状态寄存器 */


/******************************************************************************************
 *  UART2模块
 *  基址: 0x10007000
 ******************************************************************************************/
#define UART2BASE            ((volatile unsigned *)0x10007000)
#define UART2_DLBL          (*(volatile unsigned *)0x10007000)  /* 波特率设置低八位寄存器 */
#define UART2_RXFIFO        (*(volatile unsigned *)0x10007000)  /* 接收FIFO */
#define UART2_TXFIFO        (*(volatile unsigned *)0x10007000)  /* 发送FIFO */
#define UART2_DLBH          (*(volatile unsigned *)0x10007004)  /* 波特率设置高八位寄存器 */
#define UART2_IER           (*(volatile unsigned *)0x10007004)  /* 中断使能寄存器 */
#define UART2_IIR           (*(volatile unsigned *)0x10007008)  /* 中断识别寄存器 */
#define UART2_FCR           (*(volatile unsigned *)0x10007008)  /* FIFO控制寄存器 */
#define UART2_LCR           (*(volatile unsigned *)0x1000700C)  /* 行控制寄存器 */
#define UART2_MCR           (*(volatile unsigned *)0x10007010)  /* Modem控制寄存器 */
#define UART2_LSR           (*(volatile unsigned *)0x10007014)  /* 行状态寄存器 */
#define UART2_MSR           (*(volatile unsigned *)0x10007018)  /* Modem状态寄存器 */


/******************************************************************************************
 *  UART3模块
 *  基址: 0x10008000
 ******************************************************************************************/
#define UART3BASE            ((volatile unsigned *)0x10008000)
#define UART3_DLBL          (*(volatile unsigned *)0x10008000)  /* 波特率设置低八位寄存器 */
#define UART3_RXFIFO        (*(volatile unsigned *)0x10008000)  /* 接收FIFO */
#define UART3_TXFIFO        (*(volatile unsigned *)0x10008000)  /* 发送FIFO */
#define UART3_DLBH          (*(volatile unsigned *)0x10008004)  /* 波特率设置高八位寄存器 */
#define UART3_IER           (*(volatile unsigned *)0x10008004)  /* 中断使能寄存器 */
#define UART3_IIR           (*(volatile unsigned *)0x10008008)  /* 中断识别寄存器 */
#define UART3_FCR           (*(volatile unsigned *)0x10008008)  /* FIFO控制寄存器 */
#define UART3_LCR           (*(volatile unsigned *)0x1000800C)  /* 行控制寄存器 */
#define UART3_MCR           (*(volatile unsigned *)0x10008010)  /* Modem控制寄存器 */
#define UART3_LSR           (*(volatile unsigned *)0x10008014)  /* 行状态寄存器 */
#define UART3_MSR           (*(volatile unsigned *)0x10008018)  /* Modem状态寄存器 */


/******************************************************************************************
 *  SSI模块
 *  基址: 0x10009000
 ******************************************************************************************/

#define SSI_CONTROL0        (*(volatile unsigned *)0x10009000)  /* 控制寄存器0 */
#define SSI_CONTROL1        (*(volatile unsigned *)0x10009004)  /* 控制寄存器1 */
#define SSI_SSIENR          (*(volatile unsigned *)0x10009008)  /* SSI使能寄存器 */
#define SSI_MWCR            (*(volatile unsigned *)0x1000900C)  /* Microwire控制寄存器 */
#define SSI_SER             (*(volatile unsigned *)0x10009010)  /* 从设备使能寄存器 */
#define SSI_BAUDR           (*(volatile unsigned *)0x10009014)  /* 波特率设置寄存器 */
#define SSI_TXFTLR          (*(volatile unsigned *)0x10009018)  /* 发送FIFO阈值寄存器 */
#define SSI_RXFTLR          (*(volatile unsigned *)0x1000901C)  /* 接收FIFO阈值寄存器 */
#define SSI_TXFLR           (*(volatile unsigned *)0x10009020)  /* 发送FIFO状态寄存器 */
#define SSI_RXFLR           (*(volatile unsigned *)0x10009024)  /* 接收FIFO状态寄存器 */
#define SSI_SR              (*(volatile unsigned *)0x10009028)  /* 状态寄存器 */
#define SSI_IMR             (*(volatile unsigned *)0x1000902C)  /* 中断屏蔽寄存器 */
#define SSI_ISR             (*(volatile unsigned *)0x10009030)  /* 中断最终状态寄存器 */
#define SSI_RISR            (*(volatile unsigned *)0x10009034)  /* 中断原始状态寄存器 */
#define SSI_TXOICR          (*(volatile unsigned *)0x10009038)  /* 发送FIFO上溢中断清除寄存器 */
#define SSI_RXOICR          (*(volatile unsigned *)0x1000903C)  /* 接收FIFO上溢中断清除寄存器 */
#define SSI_RXUICR          (*(volatile unsigned *)0x10009040)  /* 接收FIFO下溢中断清除寄存器 */
#define SSI_ICR             (*(volatile unsigned *)0x1000902C)  /* 中断清除寄存器 */
#define SSI_DMACR           (*(volatile unsigned *)0x1000904C)  /* DMA控制寄存器 */
#define SSI_DMATDLR         (*(volatile unsigned *)0x10009050)  /* DMA发送状态寄存器 */
#define SSI_DMARDLR         (*(volatile unsigned *)0x10009054)  /* DMA接收状态寄存器 */
#define SSI_DR              (*(volatile unsigned *)0x10009060)  /* 数据寄存器 */


/******************************************************************************************
 *  I2S模块
 *  基址: 0x1000A000
 ******************************************************************************************/

#define I2S_CTRL            (*(volatile unsigned *)0x1000A000)  /* I2S控制寄存器 */
#define I2S_DATA            (*(volatile unsigned *)0x1000A004)  /* I2S数据寄存器 */
#define I2S_INT             (*(volatile unsigned *)0x1000A008)  /* I2S中断寄存器 */
#define I2S_STATUS          (*(volatile unsigned *)0x1000A00C)  /* I2S状态寄存器 */


/******************************************************************************************
 *  GPIO模块
 *  基址: 0x1000F000
 ******************************************************************************************/

#define GPIO_DBCLK_DIV      (*(volatile unsigned *)0x1000F000)  /* 去毛刺采用时钟分频比配置寄存器 */
#define GPIO_PORTA_DIR      (*(volatile unsigned *)0x1000F004)  /* A组端口输入输出方向配置寄存器 */
#define GPIO_PORTA_SEL      (*(volatile unsigned *)0x1000F008)  /* A组端口通用用途选择配置寄存器 */
#define GPIO_PORTA_INCTL    (*(volatile unsigned *)0x1000F00C)  /* A组端口通用用途输入时类型配置寄存器 */
#define GPIO_PORTA_INTRCTL  (*(volatile unsigned *)0x1000F010)  /* A组端口中断触发类型配置寄存器 */
#define GPIO_PORTA_INTRCLR  (*(volatile unsigned *)0x1000F014)  /* A组端口通用用途中断清除配置寄存器 */
#define GPIO_PORTA_DATA     (*(volatile unsigned *)0x1000F018)  /* A组端口通用用途数据配置寄存器 */
#define GPIO_PORTB_DIR      (*(volatile unsigned *)0x1000F01C)  /* B组端口输入输出方向配置寄存器 */
#define GPIO_PORTB_SEL      (*(volatile unsigned *)0x1000F020)  /* B组端口通用用途选择配置寄存器 */
#define GPIO_PORTB_DATA     (*(volatile unsigned *)0x1000F024)  /* B组端口通用用途数据配置寄存器 */
#define GPIO_PORTC_DIR      (*(volatile unsigned *)0x1000F028)  /* C组端口输入输出方向配置寄存器 */
#define GPIO_PORTC_SEL      (*(volatile unsigned *)0x1000F02C)  /* C组端口通用用途选择配置寄存器 */
#define GPIO_PORTC_DATA     (*(volatile unsigned *)0x1000F030)  /* C组端口通用用途数据配置寄存器 */
#define GPIO_PORTD_DIR      (*(volatile unsigned *)0x1000F034)  /* D组端口输入输出方向配置寄存器 */
#define GPIO_PORTD_SEL      (*(volatile unsigned *)0x1000F038)  /* D组端口通用用途选择配置寄存器 */
#define GPIO_PORTD_SPECII   (*(volatile unsigned *)0x1000F03C)  /* D组端口专用用途2选择配置寄存器 */
#define GPIO_PORTD_DATA     (*(volatile unsigned *)0x1000F040)  /* D组端口通用用途数据配置寄存器 */
#define GPIO_PORTE_DIR      (*(volatile unsigned *)0x1000F044)  /* E组端口输入输出方向配置寄存器 */
#define GPIO_PORTE_SEL      (*(volatile unsigned *)0x1000F048)  /* E组端口通用用途选择配置寄存器 */
#define GPIO_PORTE_DATA     (*(volatile unsigned *)0x1000F04C)  /* E组端口通用用途数据配置寄存器 */
#define GPIO_PORTF_DIR      (*(volatile unsigned *)0x1000F050)  /* F组端口输入输出方向配置寄存器 */
#define GPIO_PORTF_SEL      (*(volatile unsigned *)0x1000F054)  /* F组端口通用用途选择配置寄存器 */
#define GPIO_PORTF_INCTL    (*(volatile unsigned *)0x1000F058)  /* F组端口通用用途输入时类型配置寄存器 */
#define GPIO_PORTF_INTRCTL  (*(volatile unsigned *)0x1000F05C)  /* F组端口中断触发类型配置寄存器 */
#define GPIO_PORTF_INTRCLR  (*(volatile unsigned *)0x1000F060)  /* F组端口通用用途中断清除配置寄存器 */
#define GPIO_PORTF_DATA     (*(volatile unsigned *)0x1000F064)  /* F组端口通用用途数据配置寄存器 */
#define GPIO_PORTG_DIR      (*(volatile unsigned *)0x1000F068)  /* G组端口输入输出方向配置寄存器 */
#define GPIO_PORTG_SEL      (*(volatile unsigned *)0x1000F06C)  /* G组端口通用用途选择配置寄存器 */
#define GPIO_PORTG_DATA     (*(volatile unsigned *)0x1000F070)  /* G组端口通用用途数据配置寄存器 */
#define GPIO_PORTH_DIR      (*(volatile unsigned *)0x1000F074)  /* H组端口输入输出方向配置寄存器 */
#define GPIO_PORTH_SEL      (*(volatile unsigned *)0x1000F078)  /* H组端口通用用途选择配置寄存器 */
#define GPIO_PORTH_DATA     (*(volatile unsigned *)0x1000F07c)  /* H组端口通用用途数据配置寄存器 */
#define GPIO_PORTI_DIR      (*(volatile unsigned *)0x1000F080)  /* I组端口输入输出方向配置寄存器 */
#define GPIO_PORTI_SEL      (*(volatile unsigned *)0x1000F084)  /* I组端口通用用途选择配置寄存器 */
#define GPIO_PORTI_DATA     (*(volatile unsigned *)0x1000F088)  /* I组端口通用用途数据配置寄存器 */


/******************************************************************************************
 *  SMC0模块
 *  基址: 0x1000C000
 ******************************************************************************************/

#define SMC0_CTRL           (*(volatile unsigned *)0x1000C000)  /* SMC0控制寄存器 */
#define SMC0_INT            (*(volatile unsigned *)0x1000C004)  /* SMC0中断寄存器 */
#define SMC0_FD             (*(volatile unsigned *)0x1000C008)  /* SMC0基本单元时间寄存器 */
#define SMC0_CT             (*(volatile unsigned *)0x1000C00C)  /* SMC0字符传输时间寄存器 */
#define SMC0_BT             (*(volatile unsigned *)0x1000C010)  /* SMC0块传输时间寄存器 */


/******************************************************************************************
 *  SMC1模块
 *  基址: 0x1000D000
 ******************************************************************************************/

#define SMC1_CTRL           (*(volatile unsigned *)0x1000D000)  /* SMC1控制寄存器 */
#define SMC1_INT            (*(volatile unsigned *)0x1000D004)  /* SMC1中断寄存器 */
#define SMC1_FD             (*(volatile unsigned *)0x1000D008)  /* SMC1基本单元时间寄存器 */
#define SMC1_CT             (*(volatile unsigned *)0x1000D00C)  /* SMC1字符传输时间寄存器 */
#define SMC1_BT             (*(volatile unsigned *)0x1000D010)  /* SMC1块传输时间寄存器 */


/******************************************************************************************
 *  USBD模块
 *  基址: 0x1000E000
 ******************************************************************************************/

#define USBD_PROTOCOLINTR           (*(volatile unsigned *)0x1000E000)  /* USB协议中断寄存器 */
#define USBD_INTRMASK               (*(volatile unsigned *)0x1000E004)  /* USB中断屏蔽寄存器 */
#define USBD_INTRCTRL               (*(volatile unsigned *)0x1000E008)  /* USB中断类型控制寄存器 */
#define USBD_EPINFO                 (*(volatile unsigned *)0x1000E00C)  /* USB活动端点状态寄存器 */
#define USBD_BCONFIGURATIONVALUE    (*(volatile unsigned *)0x1000E010)  /* SET_CCONFIGURATION记录 */
#define USBD_BMATTRIBUTES           (*(volatile unsigned *)0x1000E014)  /* 当前配置属性寄存器 */
#define USBD_DEVSPEED               (*(volatile unsigned *)0x1000E018)  /* 当前设备工作速度寄存器 */
#define USBD_FRAMENUMBER            (*(volatile unsigned *)0x1000E01C)  /* 记录当前SOF包内的帧号 */
#define USBD_EPTRANSACTIONS0        (*(volatile unsigned *)0x1000E020)  /* 记录下次要求的传输次数 */
#define USBD_EPTRANSACTIONS1        (*(volatile unsigned *)0x1000E024)  /* 记录下次要求的传输次数 */
#define USBD_APPIFUPDATE            (*(volatile unsigned *)0x1000E028)  /* 接口号快速更新寄存器 */
#define USBD_CFGINTERFACE0          (*(volatile unsigned *)0x1000E02c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE1          (*(volatile unsigned *)0x1000E030)  /* 记录接口的值 */
#define USBD_CFGINTERFACE2          (*(volatile unsigned *)0x1000E034)  /* 记录接口的值 */
#define USBD_CFGINTERFACE3          (*(volatile unsigned *)0x1000E038)  /* 记录接口的值 */
#define USBD_CFGINTERFACE4          (*(volatile unsigned *)0x1000E03c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE5          (*(volatile unsigned *)0x1000E040)  /* 记录接口的值 */
#define USBD_CFGINTERFACE6          (*(volatile unsigned *)0x1000E044)  /* 记录接口的值 */
#define USBD_CFGINTERFACE7          (*(volatile unsigned *)0x1000E048)  /* 记录接口的值 */
#define USBD_CFGINTERFACE8          (*(volatile unsigned *)0x1000E04c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE9          (*(volatile unsigned *)0x1000E050)  /* 记录接口的值 */
#define USBD_CFGINTERFACE10         (*(volatile unsigned *)0x1000E054)  /* 记录接口的值 */
#define USBD_CFGINTERFACE11         (*(volatile unsigned *)0x1000E058)  /* 记录接口的值 */
#define USBD_CFGINTERFACE12         (*(volatile unsigned *)0x1000E05c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE13         (*(volatile unsigned *)0x1000E060)  /* 记录接口的值 */
#define USBD_CFGINTERFACE14         (*(volatile unsigned *)0x1000E064)  /* 记录接口的值 */
#define USBD_CFGINTERFACE15         (*(volatile unsigned *)0x1000E068)  /* 记录接口的值 */
#define USBD_CFGINTERFACE16         (*(volatile unsigned *)0x1000E06c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE17         (*(volatile unsigned *)0x1000E070)  /* 记录接口的值 */
#define USBD_CFGINTERFACE18         (*(volatile unsigned *)0x1000E074)  /* 记录接口的值 */
#define USBD_CFGINTERFACE19         (*(volatile unsigned *)0x1000E078)  /* 记录接口的值 */
#define USBD_CFGINTERFACE20         (*(volatile unsigned *)0x1000E07c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE21         (*(volatile unsigned *)0x1000E080)  /* 记录接口的值 */
#define USBD_CFGINTERFACE22         (*(volatile unsigned *)0x1000E084)  /* 记录接口的值 */
#define USBD_CFGINTERFACE23         (*(volatile unsigned *)0x1000E088)  /* 记录接口的值 */
#define USBD_CFGINTERFACE24         (*(volatile unsigned *)0x1000E08c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE25         (*(volatile unsigned *)0x1000E090)  /* 记录接口的值 */
#define USBD_CFGINTERFACE26         (*(volatile unsigned *)0x1000E094)  /* 记录接口的值 */
#define USBD_CFGINTERFACE27         (*(volatile unsigned *)0x1000E098)  /* 记录接口的值 */
#define USBD_CFGINTERFACE28         (*(volatile unsigned *)0x1000E09c)  /* 记录接口的值 */
#define USBD_CFGINTERFACE29         (*(volatile unsigned *)0x1000E0a0)  /* 记录接口的值 */
#define USBD_CFGINTERFACE30         (*(volatile unsigned *)0x1000E0a4)  /* 记录接口的值 */
#define USBD_CFGINTERFACE31         (*(volatile unsigned *)0x1000E0a8)  /* 记录接口的值 */
#define USBD_PKTPASSEDCTRL          (*(volatile unsigned *)0x1000E0ac)  /* 记录成功接收的包数 */
#define USBD_PKTDROPPEDCTRL         (*(volatile unsigned *)0x1000E0b0)  /* 记录丢失的包数 */
#define USBD_CRCERRCTRL             (*(volatile unsigned *)0x1000E0b4)  /* 记录CRC错误的包数 */
#define USBD_BITSTUFFERRCTRL        (*(volatile unsigned *)0x1000E0b8)  /* 记录位填充错误的包数 */
#define USBD_PIDERRCTRL             (*(volatile unsigned *)0x1000E0bc)  /* 记录PID错误的包数 */
#define USBD_FRAMINGERRCTL          (*(volatile unsigned *)0x1000E0c0)  /* 记录有SYNC和EOP的包数 */
#define USBD_TXPKTCTRL              (*(volatile unsigned *)0x1000E0c4)  /* 记录发送包的数量 */
#define USBD_STATCTRLOV             (*(volatile unsigned *)0x1000E0c8)  /* 记录统计寄存器溢出情况 */
#define USBD_TXLENGTH               (*(volatile unsigned *)0x1000E0cc)  /* 记录每次IN传输事务包长度 */
#define USBD_RXLENGTH               (*(volatile unsigned *)0x1000E0d0)  /* 记录OUT传输事务包长度 */
#define USBD_RESUME                 (*(volatile unsigned *)0x1000E0d4)  /* USB唤醒寄存器 */
#define USBD_READFLAG               (*(volatile unsigned *)0x1000E0d8)  /* 读异步状态寄存器标志 */
#define USBD_RECEIVETYPE            (*(volatile unsigned *)0x1000E0dc)  /* 传输状态寄存器 */
#define USBD_APPLOCK                (*(volatile unsigned *)0x1000E0e0)  /* 锁信号寄存器 */
#define USBD_EP0OUTADDR             (*(volatile unsigned *)0x1000E100)  /* 端点0端点号和方向 */
#define USBD_EP0OUTBMATTR           (*(volatile unsigned *)0x1000E104)  /* 端点0类型寄存器 */
#define USBD_EP0OUTMAXPKTSIZE       (*(volatile unsigned *)0x1000E108)  /* 端点0最大包尺寸寄存器 */
#define USBD_EP0OUTIFNUM            (*(volatile unsigned *)0x1000E10c)  /* 端点0接口号寄存器 */
#define USBD_EP0OUTSTAT             (*(volatile unsigned *)0x1000E110)  /* 端点0状态寄存器 */
#define USBD_EP0OUTBMREQTYPE        (*(volatile unsigned *)0x1000E114)  /* 端点0 SETUP事务请求类 */
#define USBD_EP0OUTBREQUEST         (*(volatile unsigned *)0x1000E118)  /* 端点0 SETUP事务请求内容 */
#define USBD_EP0OUTWVALUE           (*(volatile unsigned *)0x1000E11c)  /* 端点0 SETUP事务请求值 */
#define USBD_EP0OUTWINDEX           (*(volatile unsigned *)0x1000E120)  /* 端点0 SETUP事务请求索引 */
#define USBD_EP0OUTWLENGTH          (*(volatile unsigned *)0x1000E120)  /* 端点0 SETUP事务请求长度 */
#define USBD_EP0OUTSYNCHFRAME       (*(volatile unsigned *)0x1000E128)  /* 端点0同步包帧号 */
#define USBD_EP1OUTADDR             (*(volatile unsigned *)0x1000E12c)  /* 端点1输出端点号和方向 */
#define USBD_EP1OUTBMATTR           (*(volatile unsigned *)0x1000E130)  /* 端点1输出类型寄存器 */
#define USBD_EP1OUTMAXPKTSIZE       (*(volatile unsigned *)0x1000E134)  /* 端点1输出最大包尺寸寄存器 */
#define USBD_EP1OUTIFNUM            (*(volatile unsigned *)0x1000E138)  /* 端点1输出接口号寄存器 */
#define USBD_EP1OUTSTAT             (*(volatile unsigned *)0x1000E13c)  /* 端点1输出状态寄存器 */
#define USBD_EP1OUTBMREQTYPE        (*(volatile unsigned *)0x1000E140)  /* 端点1输出SETUP事务请求类型 */
#define USBD_EP1OUTBREQUEST         (*(volatile unsigned *)0x1000E144)  /* 端点1输出SETUP事务请求内容 */
#define USBD_EP1OUTWVALUE           (*(volatile unsigned *)0x1000E148)  /* 端点1输出SETUP事务请求值 */
#define USBD_EP1OUTWINDX            (*(volatile unsigned *)0x1000E14c)  /* 端点1输出SETUP事务请求索引 */
#define USBD_EP1OUTWLENGH           (*(volatile unsigned *)0x1000E150)  /* 端点1输出SETUP事务请求域长度 */
#define USBD_EP1OUTSYNCHFRAME       (*(volatile unsigned *)0x1000E154)  /* 端点1输出同步包帧号 */
#define USBD_EP1INADDR              (*(volatile unsigned *)0x1000E158)  /* 端点1输入端点号和方向 */
#define USBD_EP1INBMATTR            (*(volatile unsigned *)0x1000E15c)  /* 端点1输入类型寄存器 */
#define USBD_EP1INMAXPKTSIZE        (*(volatile unsigned *)0x1000E160)  /* 端点1输入最大包尺寸寄存器 */
#define USBD_EP1INIFNUM             (*(volatile unsigned *)0x1000E164)  /* 端点1输入接口号寄存器 */
#define USBD_EP1INSTAT              (*(volatile unsigned *)0x1000E168)  /* 端点1输入状态寄存器 */
#define USBD_EP1INBMREQTYPE         (*(volatile unsigned *)0x1000E16c)  /* 端点1输入SETUP事务请求类型 */
#define USBD_EP1INBREQUEST          (*(volatile unsigned *)0x1000E170)  /* 端点1输入SETUP事务请求内容 */
#define USBD_EP1INWVALUE            (*(volatile unsigned *)0x1000E174)  /* 端点1输入SETUP事务请求值 */
#define USBD_EP1INWINDEX            (*(volatile unsigned *)0x1000E178)  /* 端点1输入SETUP事务请求索引 */
#define USBD_EP1INWLENGTH           (*(volatile unsigned *)0x1000E17c)  /* 端点1输入SETUP事务请求域长度 */
#define USBD_EP1INSYNCHFRAME        (*(volatile unsigned *)0x1000E180)  /* 端点1输入同步包帧号 */
#define USBD_EP2OUTADDR             (*(volatile unsigned *)0x1000E184)  /* 端点2输出端点号和方向 */
#define USBD_EP2OUTBMATTR           (*(volatile unsigned *)0x1000E188)  /* 端点2输出类型寄存器 */
#define USBD_EP2OUTMAXPKTSIZE       (*(volatile unsigned *)0x1000E18c)  /* 端点2输出最大包尺寸寄存器 */
#define USBD_EP2OUTIFNUM            (*(volatile unsigned *)0x1000E190)  /* 端点2输出接口号寄存器 */
#define USBD_EP2OUTSTAT             (*(volatile unsigned *)0x1000E194)  /* 端点2输出状态寄存器 */
#define USBD_EP2OUTBMREQTYPE        (*(volatile unsigned *)0x1000E198)  /* 端点2输出SETUP事务请求类型 */
#define USBD_EP2OUTBREQUEST         (*(volatile unsigned *)0x1000E19c)  /* 端点2输出SETUP事务请求内容 */
#define USBD_EP2OUTWVALUE           (*(volatile unsigned *)0x1000E1a0)  /* 端点2输出SETUP事务请求值 */
#define USBD_EP2OUTWINDEX           (*(volatile unsigned *)0x1000E1a4)  /* 端点2输出SETUP事务请求索引 */
#define USBD_EP2OUTWLENGTH          (*(volatile unsigned *)0x1000E1a8)  /* 端点2输出SETUP事务请求域长度 */
#define USBD_EP2OUTSYNCHFRAME       (*(volatile unsigned *)0x1000E1ac)  /* 端点2输出同步包帧号 */
#define USBD_EP2INADDR              (*(volatile unsigned *)0x1000E1b0)  /* 端点2输入端点号和方向 */
#define USBD_EP2INBMATTR            (*(volatile unsigned *)0x1000E1b4)  /* 端点2输入类型寄存器 */
#define USBD_EP2INMAXPKTSIZE        (*(volatile unsigned *)0x1000E1b8)  /* 端点2输入最大包尺寸寄存器 */
#define USBD_EP2INIFNUM             (*(volatile unsigned *)0x1000E1bc)  /* 端点2输入接口号寄存器 */
#define USBD_EP2INSTAT              (*(volatile unsigned *)0x1000E1c0)  /* 端点2输入状态寄存器 */
#define USBD_EP2INBMREQTYPE         (*(volatile unsigned *)0x1000E1c4)  /* 端点2输入SETUP事务请求类型 */
#define USBD_EP2INBREQUEST          (*(volatile unsigned *)0x1000E1c8)  /* 端点2输入SETUP事务请求内容 */
#define USBD_EP2INWVALUE            (*(volatile unsigned *)0x1000E1cc)  /* 端点2输入SETUP事务请求值 */
#define USBD_EP2INWINDEX            (*(volatile unsigned *)0x1000E1d0)  /* 端点2输入SETUP事务请求索引 */
#define USBD_EP2INWLENGTH           (*(volatile unsigned *)0x1000E1d4)  /* 端点2输入SETUP事务请求域长度 */
#define USBD_EP2INSYNCHFRAME        (*(volatile unsigned *)0x1000E1d8)  /* 端点2输入同步包帧号 */
#define USBD_RXFIFO                 (*(volatile unsigned *)0x1000E200)  /* 接受FIFO */
#define USBD_TXFIFO                 (*(volatile unsigned *)0x1000E300)  /* 发送FIFO */


/******************************************************************************************
 *  EMI模块
 *  基址: 0x11000000
 ******************************************************************************************/

#define EMI_CSACONF                 (*(volatile unsigned *)0x11000000)  /* CSA参数配置寄存器 */
#define EMI_CSBCONF                 (*(volatile unsigned *)0x11000004)  /* CSB参数配置寄存器 */
#define EMI_CSCCONF                 (*(volatile unsigned *)0x11000008)  /* CSC参数配置寄存器 */
#define EMI_CSDCONF                 (*(volatile unsigned *)0x1100000c)  /* CSD参数配置寄存器 */
#define EMI_CSECONF                 (*(volatile unsigned *)0x11000010)  /* CSE参数配置寄存器 */
#define EMI_CSFCONF                 (*(volatile unsigned *)0x11000014)  /* CSF参数配置寄存器 */
#define EMI_SDCONF1                 (*(volatile unsigned *)0x11000018)  /* SDRAM时序配置寄存器1 */
#define EMI_SDCONF2                 (*(volatile unsigned *)0x1100001c)  /* SDRAM时序配置寄存器2, SDRAM初始化用到的配置信息 */
#define EMI_REMAPCONF               (*(volatile unsigned *)0x11000020)  /* 片选空间及地址映射REMAP配置寄存器 */
#define EMI_NAND_ADDR1              (*(volatile unsigned *)0x11000100)  /* NAND FLASH的地址寄存器1 */
#define EMI_NAND_COM                (*(volatile unsigned *)0x11000104)  /* NAND FLASH的控制字寄存器 */
#define EMI_NAND_STA                (*(volatile unsigned *)0x1100010c)  /* NAND FLASH的状态寄存器 */
#define EMI_ERR_ADDR1               (*(volatile unsigned *)0x11000110)  /* 读操作出错的地址寄存器1 */
#define EMI_ERR_ADDR2               (*(volatile unsigned *)0x11000114)  /* 读操作出错的地址寄存器2 */
#define EMI_NAND_CONF1              (*(volatile unsigned *)0x11000118)  /* NAND FLASH的配置器存器1 */
#define EMI_NAND_INTR               (*(volatile unsigned *)0x1100011c)  /* NAND FLASH中断寄存器 */
#define EMI_NAND_ECC                (*(volatile unsigned *)0x11000120)  /* ECC校验完成寄存器 */
#define EMI_NAND_IDLE               (*(volatile unsigned *)0x11000124)  /* NAND FLASH空闲寄存器 */
#define EMI_NAND_CONF2              (*(volatile unsigned *)0x11000128)  /* NAND FLASH的配置器存器2 */
#define EMI_NAND_ADDR2              (*(volatile unsigned *)0x1100012c)  /* NAND FLASH的地址寄存器2 */
#define EMI_NAND_ID                 (*(volatile unsigned *)0x11000130)  /* NAND FLASH的ID寄存器*/
#define EMI_NAND_DATA               (*(volatile unsigned *)0x11000200)  /* NAND FLASH的数据寄存器 */


/******************************************************************************************
 *  DMAC模块
 *  基址: 0x11001000
 ******************************************************************************************/

#define DMAC_INTSTATUS              (*(volatile unsigned *)0x11001020)  /* DAMC中断状态寄存器。 */
#define DMAC_INTTCSTATUS            (*(volatile unsigned *)0x11001050)  /* DMAC传输完成中断状态寄存器 */
#define DMAC_INTTCCLEAR             (*(volatile unsigned *)0x11001060)  /* DMAC传输完成中断状态清除寄存器 */
#define DMAC_INTERRORSTATUS         (*(volatile unsigned *)0x11001080)  /* DMAC传输错误中断状态寄存器 */
#define DMAC_INTERRCLR              (*(volatile unsigned *)0x11001090)  /* DMAC传输错误中断状态清除寄存器 */
#define DMAC_ENBLDCHNS              (*(volatile unsigned *)0x110010b0)  /* DMAC通道使能状态寄存器 */
#define DMAC_C0SRCADDR              (*(volatile unsigned *)0x11001000)  /* DMAC道0源地址寄存器 */
#define DMAC_C0DESTADD              (*(volatile unsigned *)0x11001004)  /* DMAC道0目的地址寄存器 */
#define DMAC_C0CONTROL              (*(volatile unsigned *)0x1100100c)  /* DMAC道0控制寄存器 */
#define DMAC_C0CONFIGURATION        (*(volatile unsigned *)0x11001010)  /* DMAC道0配置寄存器 */
#define DMAC_C0DESCRIPTOR           (*(volatile unsigned *)0x11001014)  /* DMAC道0链表地址寄存器 */
#define DMAC_C1SRCADDR              (*(volatile unsigned *)0x11001100)  /* DMAC道1源地址寄存器 */
#define DMAC_C1DESTADDR             (*(volatile unsigned *)0x11001104)  /* DMAC道1目的地址寄存器 */
#define DMAC_C1CONTROL              (*(volatile unsigned *)0x1100110c)  /* DMAC道1控制寄存器 */
#define DMAC_C1CONFIGURATION        (*(volatile unsigned *)0x11001110)  /* DMAC道1配置寄存器 */
#define DMAC_C1DESCRIPTOR           (*(volatile unsigned *)0x11001114)  /* DMAC道1链表地址寄存器 */
#define DMAC_C2SRCADDR              (*(volatile unsigned *)0x11001200)  /* DMAC道2源地址寄存器 */
#define DMAC_C2DESTADDR             (*(volatile unsigned *)0x11001204)  /* DMAC道2目的地址寄存器 */
#define DMAC_C2CONTROL              (*(volatile unsigned *)0x1100120c)  /* DMAC道2控制寄存器 */
#define DMAC_C2CONFIGURATION        (*(volatile unsigned *)0x11001210)  /* DMAC道2配置寄存器 */
#define DMAC_C2DESCRIPTOR           (*(volatile unsigned *)0x11001214)  /* DMAC道2链表地址寄存器 */
#define DMAC_C3SRCADDR              (*(volatile unsigned *)0x11001300)  /* DMAC道3源地址寄存器 */
#define DMAC_C3DESTADDR             (*(volatile unsigned *)0x11001304)  /* DMAC道3目的地址寄存器 */
#define DMAC_C3CONTROL              (*(volatile unsigned *)0x1100130c)  /* DMAC道3控制寄存器 */
#define DMAC_C3CONFIGURATION        (*(volatile unsigned *)0x11001310)  /* DMAC道3配置寄存器 */
#define DMAC_C3DESCRIPTOR           (*(volatile unsigned *)0x11001314)  /* DMAC道3链表地址寄存器 */
#define DMAC_C4SRCADDR              (*(volatile unsigned *)0x11001400)  /* DMAC道4源地址寄存器 */
#define DMAC_C4DESTADDR             (*(volatile unsigned *)0x11001404)  /* DMAC道4目的地址寄存器 */
#define DMAC_C4CONTROL              (*(volatile unsigned *)0x1100140c)  /* DMAC道4控制寄存器 */
#define DMAC_C4CONFIGURATION        (*(volatile unsigned *)0x11001410)  /* DMAC道4配置寄存器 */
#define DMAC_C4DESCRIPTOR           (*(volatile unsigned *)0x11001414)  /* DMAC道4链表地址寄存器 */
#define DMAC_C5SRCADDR              (*(volatile unsigned *)0x11001500)  /* DMAC道5源地址寄存器 */
#define DMAC_C5DESTADDR             (*(volatile unsigned *)0x11001504)  /* DMAC道5目的地址寄存器 */
#define DMAC_C5CONTROL              (*(volatile unsigned *)0x1100150c)  /* DMAC道5控制寄存器 */
#define DMAC_C5CONFIGURATION        (*(volatile unsigned *)0x11001510)  /* DMAC道5配置寄存器 */
#define DMAC_C5DESCRIPTOR           (*(volatile unsigned *)0x11001514)  /* DMAC道5链表地址寄存器 */


/******************************************************************************************
 *  LCDC模块
 *  基址: 0x11002000
 ******************************************************************************************/

#define LCDC_SSA                    (*(volatile unsigned *)0x11002000)  /* 屏幕起始地址寄存器 */
#define LCDC_SIZE                   (*(volatile unsigned *)0x11002004)  /* 屏幕尺寸寄存器 */
#define LCDC_PCR                    (*(volatile unsigned *)0x11002008)  /* 面板配置寄存器 */
#define LCDC_HCR                    (*(volatile unsigned *)0x1100200c)  /* 水平配置寄存器 */
#define LCDC_VCR                    (*(volatile unsigned *)0x11002010)  /* 垂直配置寄存器 */
#define LCDC_PWMR                   (*(volatile unsigned *)0x11002014)  /* PWM对比度控制寄存器 */
#define LCDC_LECR                   (*(volatile unsigned *)0x11002018)  /* 使能控制寄存器 */
#define LCDC_DMACR                  (*(volatile unsigned *)0x1100201c)  /* DMA控制寄存器 */
#define LCDC_LCDISREN               (*(volatile unsigned *)0x11002020)  /* 中断使能寄存器 */
#define LCDC_LCDISR                 (*(volatile unsigned *)0x11002024)  /* 中断状态寄存器 */
#define LCDC_LGPMR                  (*(volatile unsigned *)0x11002040)  /* 灰度调色映射寄存器组 */
                                                                        /*(0x40-0x7c 16个32bit寄存器) */


/******************************************************************************************
 *  MAC模块
 *  基址: 0x11003000
 ******************************************************************************************/

#define MAC_CTRL                    (*(volatile unsigned *)0x11003000)  /* MAC控制寄存器 */
#define MAC_INTSRC                  (*(volatile unsigned *)0x11003004)  /* MAC中断源寄存器 */
#define MAC_INTMASK                 (*(volatile unsigned *)0x11003008)  /* MAC中断屏蔽寄存器 */
#define MAC_IPGT                    (*(volatile unsigned *)0x1100300c)  /* 连续帧间隔寄存器 */
#define MAC_IPGR1                   (*(volatile unsigned *)0x11003010)  /* 等待窗口寄存器 */
#define MAC_IPGR2                   (*(volatile unsigned *)0x11003014)  /* 等待窗口寄存器 */
#define MAC_PACKETLEN               (*(volatile unsigned *)0x11003018)  /* 帧长度寄存器 */
#define MAC_COLLCONF                (*(volatile unsigned *)0x1100301c)  /* 碰撞重发寄存器 */
#define MAC_TXBD_NUM                (*(volatile unsigned *)0x11003020)  /* 发送描述符寄存器 */
#define MAC_FLOWCTRL                (*(volatile unsigned *)0x11003024)  /* 流控寄存器 */
#define MAC_MII_CTRL                (*(volatile unsigned *)0x11003028)  /* PHY控制寄存器 */
#define MAC_MII_CMD                 (*(volatile unsigned *)0x1100302c)  /* PHY命令寄存器 */
#define MAC_MII_ADDRESS             (*(volatile unsigned *)0x11003030)  /* PHY地址寄存器 */
#define MAC_MII_TXDATA              (*(volatile unsigned *)0x11003034)  /* PHY写数据寄存器 */
#define MAC_MII_RXDATA              (*(volatile unsigned *)0x11003038)  /* PHY读数据寄存器 */
#define MAC_MII_STATUS              (*(volatile unsigned *)0x1100303c)  /* PHY状态寄存器 */
#define MAC_ADDR0                   (*(volatile unsigned *)0x11003040)  /* MAC地址寄存器 */
#define MAC_ADDR1                   (*(volatile unsigned *)0x11003044)  /* MAC地址寄存器 */
#define MAC_HASH0                   (*(volatile unsigned *)0x11003048)  /* MAC HASH寄存器 */
#define MAC_HASH1                   (*(volatile unsigned *)0x1100304c)  /* MAC HASH寄存器 */
#define MAC_TXPAUSE                 (*(volatile unsigned *)0x11003050)  /* MAC控制帧寄存器 */
#define MAC_BD                      /* 0x4*/


#endif

/*******************END OF FILE*************************/
