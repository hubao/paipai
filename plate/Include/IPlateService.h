// $_FILEHEADER_BEGIN ***************************
// 版权声明:Copyright (C) 2015- ChangLiaoTianXia. All Rights Reserved
// 文件名称：PlateService.h
// 创建日期: 20150708
// 创 建 人: zhjx
// 文件说明:  定义平台导出的服务接口及类型, 
// 目的是以平台形式提高代码的重用性和可维护性；提高开发效率，尽量使今后的开发专注在业务逻辑层
// 第一版先实现个简单的框架和一些比较常用的接口
// 今后会根据具体情况逐步将此平台完善
// 原因: 创建文件
// $_FILEHEADER_END *****************************

#pragma once

enum ENUM_PLATE_SERVICE
{
    enum_min_svc_id = 1000,
    enum_timer_svc = 1001,                         //定时 接口typeid, 已实现可以使用
    enum_config_svc = 1002,                        //配置文件加载接口typeid, 已实现可以使用
    enum_rpc_client_svc = 1003,                    //rpc 客户端接口typeid, 已实现可以使用
    enum_rpc_server_svc = 1004,                    //rpc 服务接口typeid, 已实现可以使用
    enum_normal_tcp_client_svc = 1005,             //私有协议 tcp客户端接口typeid, 已实现可以使用
    enum_normal_tcp_server_svc = 1006,             //私有协议 tcp服务端接口typeid, 已实现可以使用
    enum_mail_svc = 1007,                          //邮件发送服务接口typeid ###未实现无法使用
    enum_configure_info_svc = 1008,                //应用层服务数据库信息 错误信息 服务器地址信息读取接口 
    enum_redis_connects_svc = 1009,                // redis连接管理
    enum_db_connects_svc = 1010,                   // database连接管理
    enum_rpc_connects_svc = 1011,                  // rpc连接管理
    enum_alert_svc = 1012,                         //内部统计基于秒级的报警 

    enum_max_svc_id = 2000,                        //
};


//平台导出服务调用接口
//平台会将此接口直接通过调用参数传给业务库
class IPlateSvc
{
public:
    //$_FUNCTION_BEGIN ******************************************************
    // 函数名称：GetInterface
    // 函数参数：apInterface		[out]	输出接口指针
    //			 aiID				[in]	接口对应的枚举值 ENUM_PLATE_SERVICE
    // 返 回 值：成功返回大于等于0的值；失败返回小于0的值
    // 函数说明：获取平台服务接口
    //$_FUNCTION_END ********************************************************
    virtual int GetInterface(void **apInterface, const int aiID) = 0;
};


