//
//  client.h
//  my_Account
//
//  Created by hubao on 2018/5/29.
//  Copyright © 2018年 cltx. All rights reserved.
//

#ifndef client_h
#define client_h


#include "concurrency/ThreadManager.h"
#include "concurrency/PosixThreadFactory.h"
#include "protocol/TBinaryProtocol.h"
#include "transport/TServerSocket.h"
#include "transport/TBufferTransports.h"
#include "server/TSimpleServer.h"
#include "server/TNonblockingServer.h"

#include "ProtoRpcService.h"
#include "RpcTypes.h"

#include "IRpcClient.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

using namespace proto_rpc;

class IClient : public IRpcClient
{

public:
    IClient() : miConnMs(2000),miRecvMs(2000),miSendMs(2000),_client(NULL){}
    
    virtual ~IClient(){};
    
    //成功返回 0， 失败返回1
    virtual int connect(const std::string& astrAddr, int aiPort, bool isNBytes =false);

    //不再使用此RPC时关闭
    virtual void close();
    
    //重建当前连接
    virtual int reConnect();
    
    //201604新增rpc请求超时设置接口
    //设置连接超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
    virtual void setConnTimeout(int aims);
    
    //设置接收数据超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
    virtual void setRecvTimeout(int aims);
    
    //设置发送超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
    virtual void setSendTimeout(int aims);
    
    //返回值 0 表示rpc接口调用正常返回， -1 表示rpc接口调用内部出现问题
    virtual int rpcOnwayRequest(const proto_rpc::ProtoRequest &aoRequest);
    
    //发送同步的rpc请求 发送成功返回 0， 失败 -1
    //此接口内部是非线程安全的，多线程调用时外部需要加锁
    virtual int rpcSynRequest(const proto_rpc::ProtoRequest &aoRequest, proto_rpc::ProtoReply &aoResponse);

private:
    boost::shared_ptr<TTransport> _transport;
    ProtoRpcServiceClient* _client;
    
    int miConnMs;
    int miRecvMs;
    int miSendMs;
    
};

#endif /* client_h */

