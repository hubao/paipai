#pragma once

// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：IMailSender.h.h
// 创建日期：20151109
// 创建人：	 
// 文件说明：应用层发送服务运行过程中业务执行状态监控邮件
// $_FILEHEADER_END ***********************************************************

//内部会处理关于服务类型，邮件标题，每种消息的最大发送次数，以及邮件接收人

class IMailSender
{
public:
	// $_FUNCTION_BEGIN ******************************
	// 函数名称：ErrorMailSender
	// 函数参数：aoErrorMsg			[in]	邮件内容
    // int aiMailID                 [in]    邮件的消息ID, 每个业务的每种消息自己分配一个唯一的ID
	// 函数说明：服务内部数据或者逻辑错误必须在线上处理，消除错误；否则业务将无法继续执行
	// $_FUNCTION_END ********************************
	virtual void ErrorMailSender(int aiMailID, std::string &aoErrorMsg) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：AlertMailSender
    // 函数参数：aoAlertMsg			[in]	邮件内容
    // int aiMailID                 [in]    邮件的消息ID, 每个业务的每种消息自己分配一个唯一的ID
    // 函数说明：服务内部数据或逻辑错误，但不影响线上业务继续执行， 需要引起关注查看原因
    // $_FUNCTION_END ********************************
    virtual void AlertMailSender(int aiMailID, std::string &aoAlertMsg) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：NotifyMailSender
    // 函数参数：aoNotifyMsg		[in]	邮件内容
    // int aiMailID                 [in]    邮件的消息ID, 每个业务的每种消息自己分配一个唯一的ID
    // 函数说明：服务运行状态正常上报 
    // $_FUNCTION_END ********************************
    virtual void NotifyMailSender(int aiMailID, std::string &aoNotifyMsg) = 0;
};
