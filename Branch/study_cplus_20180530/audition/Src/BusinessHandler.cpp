//
// Created by hubao on 2018/5/30.
//

#include "BusinessHandler.h"
#include <iostream>

void CBusinessHandler::callOnewayMsgDealerFunc(const proto_rpc::ProtoRequest &aoRequest) {
    std::cout << __FUNCTION__ << std::endl;
}

void CBusinessHandler::callTwowayMsgDealerFunc(const proto_rpc::ProtoRequest &aoRequest,
                                               proto_rpc::ProtoReply &aoResponse) {
    std::cout << __FUNCTION__ << std::endl;
}