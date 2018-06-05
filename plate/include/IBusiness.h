// $_FILEHEADER_BEGIN ***************************
// 版权声明:Copyright (C) 2015- ChangLiaoTianXia. All Rights Reserved
// 文件名称：IBusiness.h
// 创建日期: 20150623
// 文件说明: 所有业务层逻辑只需要按照此接口实现即可以被平台加载运行
// 原因:   创建文件
// $_FILEHEADER_END *****************************
#pragma once;
#include "IPlateService.h"

#define LIBEXPORT_CL BUSINESS_EXPORTS

#if defined _WIN32 || defined __CYGWIN__
#ifdef LIBEXPORT_CL
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__((dllimport))
#else
#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define DLL_LOCAL
#else
#if __GNUC__ >= 4
#define SO_INTERFACE_PUBLIC __attribute__ ((visibility("default")))
#define SO_INTERFACE_LOCAL  __attribute__ ((visibility("hidden")))
#else
#define SO_INTERFACE_PUBLIC
#define SO_INTERFACE_LOCAL
#endif
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

enum ENUM_PLATE_NOTIFY_TYPE
{
    enum_plate_notify_log_level_change = 0x0001,           //日志级别变化单独提示
    enum_plate_notify_other_config_item_change = 0x0002,   //配置文件变化此时应用可以把所有配置项更新一遍
    enum_plate_notify_add_new_server = 0x0004,             //新增服务
    //有其它类型事件再定义
};
//
struct STRU_PLATE_NOTIFY
{
    std::string moLogPath;
    int miLogLevel;
    int miMaxLogCount;
    int miParam;        //由它定义ENUM_PLATE_NOTIFY_TYPE 按位设置通知内容, miParam =0 时表示程序启动目前只需要创建日志文件
    char mszArgv[256];  //服务启动命令行参数
};

//initialize business
int SO_INTERFACE_PUBLIC InitBusiniess(IPlateSvc *apPlateSvc);

// uinitialize business
int SO_INTERFACE_PUBLIC FiniBusiniess();

//主要是因为日志不方便和平台写到一个文件所以增加此接口
//其实现方式参考实例即可
int SO_INTERFACE_PUBLIC onPlateNotify(const STRU_PLATE_NOTIFY& aoPlateNotify);

//start service
int SO_INTERFACE_PUBLIC StartBusiniess();

//stop service
int SO_INTERFACE_PUBLIC StopBusiniess();

//如果需要将日志写入同一个文件调用这个接口即可
void SO_INTERFACE_PUBLIC LogOneFile(int aiLogLevel, const char *format, ...);

#if defined(__cplusplus)
};
#endif

