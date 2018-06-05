//
//  server.cpp
//  my_Account
//
//  Created by hubao on 2018/5/29.
//  Copyright © 2018年 cltx. All rights reserved.
//

#include "server.h"
#include <iostream>

int IServer::Open(const std::string& astrBindAddr,
                  int aiPort,
                  int aiThreads,
                  bool isNBytes/* = false*/)
{

    int liPort = isNBytes ? htons(aiPort) : aiPort;

    boost::shared_ptr<ProtoRpcServiceIf> handler(new ProtoRpcServiceHandler(_event));
    boost::shared_ptr<TProcessor> processor(new ProtoRpcServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(astrBindAddr.c_str(), liPort));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(aiThreads);
    boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());

    threadManager->threadFactory(threadFactory);
    threadManager->start();

    boost::shared_ptr<TThreadPoolServer> server(new TThreadPoolServer(processor,serverTransport,transportFactory,protocolFactory,threadManager));
    //TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);

    std::cout << "Starting the server..." << std::endl;
    server->serve();

    std::cout << "Done." << std::endl;

    return 0;
}

int IServer::Close() {
    return 0;
}

int IServer::RegisteHandler(IRpcEvent *apRpcHander){

    _event = apRpcHander;
    //_handler = new ProtoRpcServiceHandler(apRpcHander);
    return _event == NULL ? -1 : 0;
}