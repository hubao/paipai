//
// Created by hubao on 2018/5/30.
//

#include "rpc/RpcService.h"
#include "thrift_cli/Src/client.h"
#include "ProtoService_types.h"
#include "BusinessHandler.h"
#include <iostream>

int main()
{
std::cout << "******************0*********************" << std::endl;

    IRpcClient *iClient;
    IClient *is = new IClient();

    iClient = (IRpcClient*)is;
    iClient->connect("127.0.0.1", 9234);

    //param1: proto_rpc::ProtoRequest &aoRequest
    //param2: proto_rpc::ProtoReply &aoResponse
    proto_rpc::ProtoRequest rq;
    proto_rpc::ProtoReply rs;

    rq.type = 0;
    rq.sharding_id = 0;
    rq.content = "hello world!";

    iClient->rpcSynRequest(rq, rs);

return 0;
}
