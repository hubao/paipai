cmake_minimum_required(VERSION 3.8)
project(Account)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Branch/study_cplus_20180530/audition/Src/Algorithm_Interview.h
        Branch/study_cplus_20180530/audition/Src/BaseCachedObj.h
        Branch/study_cplus_20180530/audition/Src/BusinessHandler.h
        Branch/study_cplus_20180530/audition/Src/BusinessInclude.h
        Branch/study_cplus_20180530/audition/Src/Cha13.4_MsgHandler.h
        Branch/study_cplus_20180530/audition/Src/Cha14_OverrideOperator.h
        Branch/study_cplus_20180530/audition/Src/Cha15.8_RefCounter.h
        Branch/study_cplus_20180530/audition/Src/Cha15.9_TextQuery.h
        Branch/study_cplus_20180530/audition/Src/Cha16.4.7_CTStatic.h
        Branch/study_cplus_20180530/audition/Src/Cha16.6_SpecialCTQueue.h
        Branch/study_cplus_20180530/audition/Src/DesignPattern-Create.h
        Branch/study_cplus_20180530/audition/Src/main.cpp
        Branch/study_cplus_20180530/audition/Src/MergeSort.h
        Branch/study_cplus_20180530/audition/Src/RpcConnectPool.h
        Branch/study_cplus_20180530/audition/main.cpp
        import/include/common/basefun.h
        import/include/common/typedef.h
        import/include/export/thrift/thrift_cli/linux_prj/version.h
        import/include/export/thrift/thrift_cli/Src/client.cpp
        import/include/export/thrift/thrift_cli/Src/client.h
        import/include/export/thrift/thrift_cli/Src/RpcClient.h
        import/include/export/thrift/thrift_rpc/ProtoRpcService.cpp
        import/include/export/thrift/thrift_rpc/ProtoRpcService_server.skeleton.cpp
        import/include/export/thrift/thrift_rpc/ProtoService_constants.cpp
        import/include/export/thrift/thrift_rpc/ProtoService_types.cpp
        import/include/export/thrift/thrift_svr/linux_prj/version.h
        import/include/export/thrift/thrift_svr/Src/RpcService.h
        import/include/export/thrift/thrift_svr/Src/server.cpp
        import/include/export/thrift/thrift_svr/Src/server.h
        import/include/rpc/ProtoRpcInterface.h
        import/include/rpc/ProtoRpcService.h
        import/include/rpc/ProtoService_constants.h
        import/include/rpc/ProtoService_types.h
        import/include/rpc/RpcTypes.h)

add_executable(Account ${SOURCE_FILES})