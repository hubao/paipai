#pragma once

// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ITcpClient.h
// 创建日期：20150719
// 创建人：	 zhjx
// 文件说明：客户端也是先做一个简单的接口吧，由于我们底层的网络库导出的接口限制比较多导致这一层现在
// 无法为应用层提供更好的接口;暂时先做到可用吧
// $_FILEHEADER_END ***********************************************************

class CIOContext
{
public:
    //目前这两个引用计数接口还没有实现
    virtual void AddRef() = 0;
    virtual void ReleaseRef() = 0;
    
    //获取当前连接ID
    virtual int GetSessionID() = 0;

    //获取服务端地址信息
    virtual int GetSvrInfo(int aiAddr, WORD awPort) = 0;

    //使用当前连接回包给服务端
    virtual int sendData(BYTE *apData, int aiDataLen) = 0;
};

class ITcpClient;
struct STRU_CONNECTION_INFO
{
    char mszpConnectionName[128];//连接名，比如 connection of achivement server
    char mszAddr[128];     //为服务端IP地址如:127.0.0.1
    WORD mwPort;           //为服务器所监听端口
    int  miConnectionCount;//连接数大于1 将创建出到指定服务器的多个连接;
    int  miSessionID;      //连接ID,由RegisterClientHandler成功后返回
};

//
//如果有多个不同的服务需要连接，可以创建出多个ITcpCliCreator实例；每个实例对应一个服务器
//
class ITcpCliCreator
{
public:
    //实现 ITcpClient 此接口后将其注册到client creator里面,本函数返回后内部就开始执行建立连接操作，如果连接建立成功，ITcpClient将收到连接已建立的通知
    //必须先执行 RegisterClientHandler 连接成功后才可以调用 SendDataBySessionID
    //其实这里如果用serverid 可能会更好一些
    //注册成功后内部会通过ITcpClient::SetSessionID() 为此连接池分配一个唯一的sessionid, 此sessionid为后面调用 SendDataBySessionID 的第三个参数
    //0成功， 非零失败
    virtual int RegisterClientHandler(ITcpClient *apTcpClient) = 0;
    
    //外部打包好以后，此接口只管发送数据不关心格式以及内容
    //aiSessionID必须是从RegisterClientHandler 返回的值,否则会出错
    //apData 为待发送的数据
    //aiDataLen 数据长度
    //0成功， 非零失败
    virtual int SendDataBySessionID(BYTE *apData, int aiDataLen, int aiSessionID) = 0;
};

//
//应用层需要实现ITcpClient此接口,来完成接收和发送数据
//由于底层接口没有连接建立通知所以这里也没有了
class ITcpClient
{
public:
    //aoSvrInfo 返回需要连接的服务器相关信息用于创建连接
    virtual void GetServerInfo(STRU_CONNECTION_INFO &aoSvrInfo) = 0;

    //连接客户注册成功后会通过此接口为此对象分配一个sessionid
    virtual void SetSessionID(int aiSessionID) = 0;

    //收到数据
    virtual void OnRecvData(CIOContext& aoCliContext, BYTE *apData, int aiDataLen) = 0;

    //服务端主动断开连接连接断开
    //底层没有提供客户端主动断开连接接口这里也没有了
    virtual void OnSessionClose(CIOContext& aoCliContext) = 0;

    //连接成功
    virtual void OnConnect(CIOContext& aoCliContext) = 0;
};

