//
//  server.h
//  my_Account
//
//  Created by hubao on 2018/5/28.
//  Copyright © 2018年 cltx. All rights reserved.
//

#ifndef server_h
#define server_h

#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

#include <server/TSimpleServer.h>
#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>

#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>

#include "ProtoRpcService.h"
#include "RpcTypes.h"

#include "IRpcService.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

using namespace proto_rpc;

class ProtoRpcServiceHandler : virtual public ProtoRpcServiceIf {
public:
    ProtoRpcServiceHandler(IRpcEvent* apEvent = NULL) : _event(apEvent) {
        // Your initialization goes here
    }

    virtual ~ProtoRpcServiceHandler(){}

    void dealTwowayMessage(ProtoReply& _return, const ProtoRequest& rq){
        _event->callTwowayMsgDealerFunc(rq, _return);
    }
    void dealOnewayMessage(const ProtoRequest& rq){
        _event->callOnewayMsgDealerFunc(rq);
    }
private:
    IRpcEvent* _event;
};

class IServer : public IRpcService {
public:
    IServer(IRpcEvent* apEvent = NULL) : _event(apEvent){}
    virtual ~IServer(){}

    //初始化
    //返回0 表示成功 其它表示失败
    virtual int Open(const std::string& astrBindAddr, int aiPort, int aiThreads, bool isNBytes = false);

    //退出
    virtual int Close();
    
    //注册处理对象
    virtual int RegisteHandler(IRpcEvent *apRpcHander);


public:
    IRpcEvent* _event;
    //TThreadPoolServer *_server;
};

#endif /* server_h */
