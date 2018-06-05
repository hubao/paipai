#pragma once

// $_FILEHEADER_BEGIN *********************************************************

// 文件名称：ITimerSvc.h
// 创建日期：20150705
// 创建人：	 
// 文件说明：时间回调处理方法
// $_FILEHEADER_END ***********************************************************

enum ENUM_TIMER_TYPE {
    enum_timeout_by_month = 1,			//按月执行的定时类型
    enum_timeout_by_week = 2,			//按周执行的定时类型
    enum_timeout_by_day = 3,			//按天执行的定时类型
    enum_timeout_by_stable_period = 4,  //确定周期的定时器
    enum_unused = 5,					//不使用
};

class ITimerHandler
{
public:
	// $_FUNCTION_BEGIN ******************************
	// 函数名称：HandleTimeOut
	// 函数参数：aoIniTime			[in]	第一次超时的时间值结构
	//           aiTimerID			[in]	当前超时定时器的ID
	//           apParam			[in]	保留参数
	// 返 回 值：小于0表示停止当前的定时器，大于等于0表示继续运行当前的定时器
	// 函数说明：处理定时器超时事件，根据返回值是定时器自动停止或复位
	// $_FUNCTION_END ********************************
	virtual int HandleTimeOut(int aiTimerID, void* apParam) = 0;

	// $_FUNCTION_BEGIN ******************************
	// 函数名称：HandleClose
	// 函数参数：aiParma			[in]	定时器时为所移除定时器的ID
	// 返 回 值：0 表示成功， -1 失败
	// 函数说明：当接口关闭的时候调用
	// $_FUNCTION_END ********************************
	virtual int HandleClose(int aiParam) = 0;
};

class ITimerSvc
{
public:
    ITimerSvc(){}
    virtual ~ITimerSvc(){}
	// $_FUNCTION_BEGIN ******************************
	//Function:RegisterTimer()
	//函数参数： 用于设置周期性的定时器
	//aiFirstTimeInterval:    首次溢出的时间间隔，小于等于零表示以当前时间为起点，首次超时在ai64Period之后触发
	//ai64Period: 循环溢出时间周期以秒为单位，这个值必须设置否则返回失败
	//apHandler:  定时器超时后的处理类
	//aiPparam:   超时处理相关的数据
	//return: -1 失败 其它表注册成功后的定时器ID
	// $_FUNCTION_END ********************************
	virtual int RegisterTimer(int aiFirstTimeInterval, INT64 ai64Period, ITimerHandler *apHandler, void* aiParam) = 0;

	// $_FUNCTION_BEGIN ******************************
	//Function:RegisterTimer()
	//函数参数： 主要用于一些比较复杂的定时条件注册定时器
	//aiTimeOutType [输入] 取值参考 ENUM_TIMER_TYPE 的按月 周 天三种类型的定时器
	//aiHour		[输入] 定时器设定超时在几点取值范围是 0 - 23 点
	//aiMinute:		[输入] 定时器设定超时在几点取值范围是 0 - 59 分
	//aiStartDay	
	//aiEndDay		[输入] aiEndDay和aiStartDay 根据aiTimeOutType的不同类型，表示不同意义
		//aiTimeOutType只能取下面三种值:
		//enum_timeout_by_month	表示从每月的 几号到几号       比如每月的 2号 -  20号;
		//当aiStartDay和aiEndDay相等时表示每月只在这一天执行;值大于28时认为是月底
		//aiEndDay>=aiStartDay
		
		//enum_timeout_by_week	表示从每周的 星期几 到 星期几 比如每周的 星期日 -  到星期六取值为 0 - 6, 注意这里星期日用0表示 星期一到六 用 1-6表示
		//enum_timeout_by_day	aiStartDay和aiEndDay此时表示从一天的几点开始定时到几点结束，此时aiHour和aiMinute将被忽略，请把二者设置为 0 
	//ai64PeriodSeconds				[输入] 定时器执行的周期，使用秒值， 类似取值为 300秒 ，1000秒...
	//apHandler:  [输入] 定时器超时后的处理类
	//aiPparam:   [输入] 超时处理业务需要的相关数据的指针
	//return: -1 失败 其它表注册成功后的定时器ID
	/*下面是一些示例供参考:
	按月的定时器
	1 每月1号3点15分执行
	2 每月2-12日 12:00执行
	3 每月月底执行 23:59执行

	按周的定时器
	1 每周1 3:00 执行
	2 每周1-5 8:00执行
	3 每周日 9:00执行

	按天的定时器
	1 每天 3:00 - 6:00执行,每5分钟执行一次
	2 每天 5:00执行一次
	1)
	//enum_timeout_by_month,按月定时器的周期最大值就是 31 * 24 * 60 * 60 秒了
	int startDay=1, endDay=1;					//startDay endDay相等都为 1 表示每月1日
	int hour=3, min=15;
	int ai64PeriodSeconds=31 * 24 * 60 * 60;	//周期设置为一个月31天的秒数，对于月份不是31天的内部会处理
	RegisterTimer(enum_timeout_by_month, startDay, endDay, hour, min, ai64PeriodSeconds, this, "每月1号 3:15 执行");

	int startDay=2, endDay=31;
	int hour=12, min=0;
	int ai64PeriodSeconds= 24 * 60 * 60;		//周期设置为一个24小时的秒数，对于月份不是31天的内部会处理
	RegisterTimer(enum_timeout_by_month, startDay, endDay, hour, min, ai64PeriodSeconds, this, "每月2-31日 12:00 执行");

	int startDay=31, endDay=31;					//startDay endDay相等都为 31 表示每月的最后一天
	int hour=23, min=59;
	int ai64PeriodSeconds=31 * 24 * 60 * 60;	//周期设置为一个月31天的秒数，对于月份不是31天的内部会处理
	RegisterTimer(enum_timeout_by_month, startDay, endDay, hour, min, ai64PeriodSeconds, this, "每月月底执行 23:59 执行");

	2)
	//enum_timeout_by_week,按周定时器的周期最大值就是 7 * 24 * 60 * 60 秒了
	int startDay=1, endDay=1;					//startDay endDay相等都为 1 表示每周一
	int hour=3, min=10;
	int ai64PeriodSeconds=7 * 24 * 60 * 60;		//周期设置为1 周时间的秒数
	RegisterTimer(enum_timeout_by_week, startDay, endDay, hour, min, ai64PeriodSeconds, this, " 每周 1 3:00 执行");

	int startDay=1, endDay=5;
	int hour=8, min=10;
	int ai64PeriodSeconds=24 * 60 * 60;			//周期设置为24小时时间秒数
	RegisterTimer(enum_timeout_by_week, startDay, endDay, hour, min, ai64PeriodSeconds, this, "每周 一 - 五 8:10 执行");

	int startDay=0, endDay=0;					// 0 表示周日，1-6表示周一至周六
	int hour=9, min=0;
	int ai64PeriodSeconds=7 * 24 * 60 * 60;		//周期设置为 1 周时间的秒数
	RegisterTimer(enum_timeout_by_week, startDay, endDay, hour, min,ai64PeriodSeconds, this, "每周 日 9:00 执行");

	3)
	//enum_timeout_by_day 每天 3:00 - 6:00执行
	int startDay=3, endDay=6;					//按天时start和end表示，每天开始执行的时间从几点到几点开始定时，24小时制，取值范围是 0 - 23
	int hour=0, min=0;							//此时hour和min设置无效取零
	int ai64PeriodSeconds=5 * 60;				//周期设置为实际需要时间的秒数，这里为三分钟
	RegisterTimer(enum_timeout_by_day, startDay, endDay, 0, 0, ai64PeriodSeconds, this, "每天 3:00 - 6:00 五分钟执行一次");

	int startDay=0, endDay=0;					//每天指定时间点执行一次定时，start和end取值为0， 由hour和min指定具体的时间点
	int hour=5, min=15;
	int ai64PeriodSeconds=24 * 60 * 60;			//周期设置为24小时时间秒数
	RegisterTimer(enum_timeout_by_day, startDay, endDay, hour, min, ai64PeriodSeconds, this, "每天 5:15 执行");
	*/
	// $_FUNCTION_END ********************************
	virtual int RegisterTimer(ENUM_TIMER_TYPE aiTimeOutType, int aiStartDay, int aiEndDay, int aiHour, int aiMinute, INT64 ai64PeriodSeconds, ITimerHandler *apHandler, void* aiParam) = 0;

	// $_FUNCTION_BEGIN ******************************
	// 函数名称：RemoveTimer
	// 输入参数：aiTimerID	[in]   注册成功的定时器ID
	// 返 回 值：成功返回0；失败返回-1。
	// 函数说明：用于自动删除一个定时器，不提供外部调用权限
	// $_FUNCTION_END ********************************
	virtual int RemoveTimer(int aiTimerID) = 0;
};

