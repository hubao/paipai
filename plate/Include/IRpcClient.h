#pragma once
// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：IRpcClient.h
// 创建日期：20150719
// 创建人：	 zhjx
// 文件说明：每个连接创建一个 IRpcClient 对象，多连接创建多个此对象即可
// $_FILEHEADER_END ***********************************************************

//
class IRpcClient
{
public:
    IRpcClient(){};
    virtual ~IRpcClient(){};

    //成功返回 0， 失败返回1
    virtual int connect(const char *aszAddr, int aiPort) = 0;
    
    //发送同步的rpc请求 发送成功返回 0， 失败 -1
    //此接口内部是非线程安全的，多线程调用时外部需要加锁
    virtual int rpcSynRequest(const proto_rpc::ProtoRequest &aoRequest, proto_rpc::ProtoReply &aoResponse) = 0;

    //不再使用此RPC时关闭
    virtual void close() = 0;

    //重建当前连接
    virtual int reConnect() = 0;
    
    //201604新增rpc请求超时设置接口
    //设置连接超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
    virtual void setConnTimeout(int aims) = 0;

    //设置接收数据超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
    virtual void setRecvTimeout(int aims) = 0;

    //设置发送超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
    virtual void setSendTimeout(int aims) = 0;

    //返回值 0 表示rpc接口调用正常返回， -1 表示rpc接口调用内部出现问题
    virtual int rpcOnwayRequest(const proto_rpc::ProtoRequest &aoRequest) = 0;

    //设置备用地址，当前地址不可用时会使用这里的备用地址自动进行重连
    virtual void setBakAddr(const char *aszAddr, int aiPort) = 0;
};
