//
//  RpcService.h
//  my_Account
//
//  Created by hubao on 2018/5/28.
//  Copyright © 2018年 cltx. All rights reserved.
//

#ifndef RpcService_h
#define RpcService_h

#include "typedef.h"
#include "ProtoService_types.h"

class IRpcEvent
{
public:
    IRpcEvent(){}
    ~IRpcEvent(){}
    virtual void callTwowayMsgDealerFunc(const proto_rpc::ProtoRequest &aoRequest, proto_rpc::ProtoReply &aoResponse) = 0;
    virtual void callOnewayMsgDealerFunc(const proto_rpc::ProtoRequest &aoRequest) = 0;
};

class IRpcService
{
public:
    IRpcService(){}
    virtual ~IRpcService(){};
    
    //初始化
    //返回0 表示成功 其它表示失败
    //
    virtual int Open(const std::string& astrBindAddr, int aiPort, int aiThreads, bool isNBytes = false) = 0;

    //退出
    virtual int Close() = 0;
    
    //注册处理对象
    virtual int RegisteHandler(IRpcEvent *apRpcHander) = 0;
};

#endif /* RpcService_h */
