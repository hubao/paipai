//
//  client.cpp
//  my_Account
//
//  Created by hubao on 2018/5/29.
//  Copyright © 2018年 cltx. All rights reserved.
//

#include "client.h"

//重建当前连接
int IClient::reConnect() {
    std::cout << "暂未实现" << std::endl;
    return 0;
}

//201604新增rpc请求超时设置接口
//设置连接超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
void IClient::setConnTimeout(int aims)
{
    miConnMs = aims;
}

//设置接收数据超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
void IClient::setRecvTimeout(int aims)
{
    miRecvMs = aims;
}

//设置发送超时时间 ， 单位毫秒 如果不调用此接口进行设置则默认超时时间为毫秒
void IClient::setSendTimeout(int aims)
{
    miSendMs = aims;
}

//返回值 0 表示rpc接口调用正常返回， -1 表示rpc接口调用内部出现问题
int IClient::rpcOnwayRequest(const proto_rpc::ProtoRequest &aoRequest)
{
    std::cout << "暂未实现" << std::endl;
    return 0;
}

int IClient::connect(const std::string& astrAddr, int aiPort, bool isNBytes/*=false*/)
{
    if(0 == astrAddr.length())
        return -1;

    int liPort = isNBytes ? htons(aiPort) : aiPort;

    boost::shared_ptr<TSocket> socket(new TSocket(astrAddr.c_str(), liPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    //apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> protocol(new TBinaryProtocol(transport));
    
    socket->setConnTimeout(miConnMs);
    socket->setRecvTimeout(miRecvMs);
    socket->setSendTimeout(miSendMs);
    
    _client = new ProtoRpcServiceClient(protocol);
    
    _transport = transport;
    _transport->open();

    std::cout << "open succ. -"<< astrAddr <<":"<< liPort << std::endl;

    return 0;
}

void IClient::close(){
    _transport->close();
}

int IClient::rpcSynRequest(const proto_rpc::ProtoRequest &aoRequest, proto_rpc::ProtoReply &aoResponse){
    std::cout << "Begin "<< __FUNCTION__ << std::endl;
    _client->dealTwowayMessage(aoResponse, aoRequest);
    std::cout << "End "<< __FUNCTION__ << std::endl;
    return 0;
}

