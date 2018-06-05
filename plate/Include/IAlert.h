#pragma once

// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：IAlert.h.h
// 创建日期：20151109
// 创建人：	 
// 文件说明：统计报警
// $_FILEHEADER_END ***********************************************************

//内部会处理关于服务类型，邮件标题，每种消息的最大发送次数，以及邮件接收人


//内部每分钟执行一次错误值检测，检测到错误发报警邮件
//如果同时有多个报警项目可以合并累积成一封邮件，邮件字节数最大不超过4k
class IAlert
{
public:
    IAlert(){}
    virtual ~IAlert(){}

    //1 创建报警项目: alertid 支持范围 100-1000单个进程内应该足够用了
    //  aoAlertName 报警项名称 报警邮件中会展示此名称
    //  aiAlertTime 默认1分钟校验一次是否报警，调整单位为分钟，支持首次 3秒内即报警; 
    //  与 monitor 接口区别 这个接口明确只接收程序出现的异常数据，相关数据不收入监控系统展示只做即时报警使用
    virtual int createAlertItem(int alertid, const std::string &aoAlertName, int aiAlertTime=1) = 0;
    
    //2 调用一次累积一个错误值
    virtual void IncreaseAlert(int alertid) = 0;

    //3 数据收入到监控系统；在后台生成图表可以进行查询
    /*
    监控上报,monitor可统计此接口设置过的累加值、最大值、最小值、平均值以及每n秒内的第一次上报和最后一次上报。
    @param  in  service_name  服务名称,最大长度不超过MONITOR_MAX_NAME_LEN，命名规则：【业务名称.服务名称】首字母大些，以点隔开，如：Monitor.MonitorApi 。
    @param  in  attr_name     属性名称,最大长度不超过MONITOR_MAX_NAME_LEN，命名规则：【模块.监控点】首字母大些，以点隔开，如：MemoryQueue.TotalProcessCount 。
    @param  in  value         上报值
    @param  in  op_mask       对数据操作掩码，参见：MONITOR_OP_TYPE_*         
    @return
        MONITOR_ERR_OK - 成功
        其它  - 错误
        MONITOR_ERR_OK - 成功
        其它  - 错误
        agent服务使用的共享内存名称 
        #define MONITOR_AGENT_MMAP_FILE "/data/server/monitor-agent/monitor.mmap"

        名字最大长度 
        #define MONITOR_MAX_NAME_LEN 64 

        错误码定义 
        #define MONITOR_ERR_OK                  0    成功 
        #define MONITOR_ERR_FAILD               -1  未知错误  
        #define MONITOR_ERR_MEM_QUEUE_FALL      -2   共享内存队列满  
        #define MONITOR_ERR_OPEN_MEM_QUEUE      -3   打开共享内存失败 
        #define MONITOR_ERR_EMPTY_NAME          -4   名字为空 
        #define MONITOR_ERR_INVALID_CHARACTER   -5  名字中含有非法字符 
        #define MONITOR_ERR_NAME_OVER_MAX_LEN   -6   名字超过最大长度，参见：MONITOR_MAX_NAME_LEN  

        上报值操作类型 
        #define MONITOR_OP_TYPE_COUNT   (1<<1)   上报次数  
        #define MONITOR_OP_TYPE_ADD     (1<<2)   对上报的值进行累加操作 
        #define MONITOR_OP_TYPE_MAX     (1<<3)   取上报值的最大值 
        #define MONITOR_OP_TYPE_MIN     (1<<4)   取上报值的最小值  
        #define MONITOR_OP_TYPE_AVERAGE (1<<5)   取上报值的平均值 
        #define MONITOR_OP_TYPE_LAST    (1<<6)   取上报值中最后一次上报 
        #define MONITOR_OP_TYPE_FIRST   (1<<7)   取上报值中第一次上报  
  */
    virtual int monitor(const char* service_name, const char* attr_name, int64_t value, int32_t op_mask) = 0;
};

