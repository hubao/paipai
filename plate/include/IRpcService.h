// $_FILEHEADER_BEGIN ***************************
// 版权声明:Copyright (C) 2015- ChangLiaoTianXia. All Rights Reserved
// 文件名称：IRPCService.h
// 创建日期: 20150713
// 创 建 人: zhjx
// 文件说明: 平台暂时做一个可用的版本，后面再逐步把它的框架建立起来展开 丰富功能
// 原因:   创建文件
// $_FILEHEADER_END *****************************
#pragma once;

class IRpcEvent
{
public:
    IRpcEvent(){}
    ~IRpcEvent(){}
    virtual void callTwowayMsgDealerFunc(const int32_t msgType, proto_rpc::ProtoReply& aoReply, const proto_rpc::ProtoRequest& aoRequest) = 0;
    virtual void callOnewayMsgDealerFunc(const int32_t msgType, const proto_rpc::ProtoRequest& msg) = 0;
};

class IRpcService
{
public:
    IRpcService(){};
    virtual ~IRpcService(){};

    //初始化
    //返回0 表示成功 其它表示失败
    //
    virtual int Open(IPTYPE aiBindAddr, int aiPort, int aiThreads) = 0;

    //退出
    virtual int Close() = 0;

    //注册处理对象
    virtual int RegisteHandler(IRpcEvent *apRpcHander) = 0;
};
