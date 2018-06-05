//
// Created by hubao on 2018/5/30.
//



#include "thrift_svr/Src/server.h"
#include "BusinessHandler.h"
#include <iostream>

int main()
{
std::cout << "******************0*********************" << std::endl;

    IRpcService *iServer;
    IServer *is = new IServer();

   iServer = (IRpcService*)is;

   CBusinessHandler *handler = new CBusinessHandler;

   iServer->RegisteHandler(handler);
  iServer->Open("127.0.0.1", 9234, 5);
return 0;
}
