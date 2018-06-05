#pragma once

// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ITcpSvr.h
// 创建日期：20150719
// 创建人：	 zhjx
// 文件说明：先做一个简单的接口吧，由于我们底层的网络库导出的接口限制比较多导致这一层现在
// 无法为应用层提供更好的接口;暂时先做到可用吧
// $_FILEHEADER_END ***********************************************************

//
// 服务器环境信息
//
struct IOCONTEXT_INFO
{
    int m_iServerId;			// 服务器id
    char m_szIp[32];			// ip
    int m_iPort;				// port
    int m_iConnectTime;			// 连接时间
    int m_iSendTimes;			// 发送次数
    int m_iSendBytes;			// 发送字节
    int m_iRecvTimes;			// 接收次数
    int m_iRecvBytes;			// 接收字节
};

struct STRU_LISTENER_OPTION
{
    int mulIPAddr;
    int mwPort;
    int mbyDealThreadCount;
    int mbyRecvThreadCount;
    int muiMaxConnCount;
    int miMaxRecvPackageCount;
    int miMaxSendPackageCount;
    int miLogLevel;
    int mbIsServer;
    int muiKeepAlive;
    int mbUseRelationPtr;
    char mszAppName[DEF_MAX_APP_NAME];
    void init()
    {
        mulIPAddr = 0;
        mwPort = 0;
        mbyDealThreadCount = 0;
        mbyRecvThreadCount = 0;
        muiMaxConnCount = 0;
        miMaxRecvPackageCount = 0;
        miMaxSendPackageCount = 0;
        miLogLevel = 0;
        mbIsServer = 0;
        muiKeepAlive = 0;
        mbUseRelationPtr = 0;
        memset(mszAppName, 0, sizeof(mszAppName));
    }
};

//ITcpSvrContext用于保存服务器收到数据时保存该连接的上下文
class ITcpSvrContext
{
public:
    //目前这两个引用计数接口还没有实现
    virtual int AddRef() = 0;
    virtual int ReleaseRef() = 0;

    //读取当前连接的描述符
    virtual int Getfd() = 0;

    //获取客户端IP
    virtual int GetClientAddr() = 0;

    //获取客户端端口
    virtual WORD GetClientPort() = 0;

    //通信token
    virtual uint32 GetToken() = 0;

    //设置通信token
    virtual void SetToken(uint32 aiToken) = 0;
};

//tcp服务端事件回调接口
class ITcpSvrEvent
{
public:
    //有客户端新连接
    virtual void OnConnect(ITcpSvrContext &aoContext) = 0;

    //有客户端连接关闭
    virtual void OnClosed(ITcpSvrContext &aoContext) = 0;

    //收到客户端数据包
    virtual int OnReceive(ITcpSvrContext &aoContext, BYTE* apAppData, int anDataLen) = 0;
};

//
// 监听服务,这里先按照只能监听一个端口的服务开发
// 以后如果有需要再考虑支持同时监听多个端口的服务
//
class ITcpSvr
{
public:
    // $_FUNCTION_BEGIN ******************************
    // 函数名称：RegisterHandler
    // 函数参数：
    // 返 回 值：0 成功，非零失败
    // 函数说明：通过这个接口注册收包处理函数
    // 注意事项：给socket的另一端发送数据，既可以使用这个接口
    // $_FUNCTION_END ********************************
    virtual int RegisterHandler(ITcpSvrEvent *apSvrEvent) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：SendData
    // 函数参数：
    // 返 回 值：	
    // 函数说明：发送数据
    // 注意事项：给socket的另一端发送数据，既可以使用这个接口
    // $_FUNCTION_END ********************************
    virtual int SendData(int afd, BYTE* apAppData, int anDataLen) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：AddRecvEvent
    // 函数参数：
    // 返 回 值：-1 失败， 0 成功	
    // 函数说明：模拟外部收到请求插入到接收消息的处理队列
    // $_FUNCTION_END ********************************
    virtual int AddRecvEvent(BYTE* apAppData, int anDataLen) = 0;
};
