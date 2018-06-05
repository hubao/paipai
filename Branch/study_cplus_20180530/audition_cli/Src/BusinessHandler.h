//
// Created by hubao on 2018/5/30.
//

#ifndef ACCOUNT_BUSINESSHANDLER_H
#define ACCOUNT_BUSINESSHANDLER_H

#include "rpc/RpcService.h"
#include "include/ProtoService_types.h"

class CBusinessHandler : public IRpcEvent{
public:
    CBusinessHandler(){}
    virtual ~CBusinessHandler(){}

    virtual void callOnewayMsgDealerFunc(const proto_rpc::ProtoRequest &aoRequest);

    virtual void callTwowayMsgDealerFunc(const proto_rpc::ProtoRequest &aoRequest, proto_rpc::ProtoReply &aoResponse);

};

#endif //ACCOUNT_BUSINESSHANDLER_H
