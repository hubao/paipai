#pragma once

// $_FILEHEADER_BEGIN *********************************************************

// 文件名称：TemplateSendPack.h
// 创建日期：20150726
// 创建人：	 
// 文件说明：基于平台所有需要发包的都可以使用的模板
// $_FILEHEADER_END ***********************************************************

//1 服务器端在当前请求上直接回proto 包的模板
template<class T>
inline int Send2ESProtoPackV2(USERID aiUserID, uint32 aiESID, uint64 aiSessionID, uint32 aiToken, ITcpSvr *apTcpSvr, int afd, IPTYPE aiIP, WORD awPort, T& aoSendPack)
{
    if (NULL != apTcpSvr)
    {
        STRU_SVR_ES_PB_GENERAL_PACKAGE_P<T> loSendPack; 
        loSendPack.miID = aiUserID;
        loSendPack.miESID = aiESID;
        loSendPack.miESSession = aiSessionID;
        loSendPack.miToken = aiToken;
        loSendPack.mpUserLoad =&aoSendPack;

        BYTE lpBuffer[DEF_MAX_GENERAL_PACK_LEN];
        int  lwPacketLength= loSendPack.Pack(lpBuffer, DEF_MAX_GENERAL_PACK_LEN);
        if (-1 == lwPacketLength)
        {
            LOG_TRACE(3,false,__FUNCTION__,__LINE__<<" Error Pack Fail!"
                <<" UserID = "<<aiUserID
                <<" IP = "<<GetIPString(aiIP)
                <<" : "<<ntohs(awPort)
                );
            return -1;
        }

        LOG_TRACE(7, true, __FUNCTION__, __LINE__<<" Notify send pack!"
            <<" UserID = "<<aiUserID
            <<" IP = "<<GetIPString(aiIP)
            <<" : "<<ntohs(awPort)
            <<" packetlegth = "<<lwPacketLength
            <<" fd = "<<afd
            );
        return apTcpSvr->SendData(afd, lpBuffer, lwPacketLength);
    }
    else
    {
        LOG_TRACE(3,false,__FUNCTION__,__LINE__<<" Error: ITcpSvr pointer is NULL can not send pack!"
            <<" UserID = "<<aiUserID
            <<" IP = "<<GetIPString(aiIP)
            <<" : "<<ntohs(awPort)
            );
        return -1;
    }
    return -1;
}

template<class T>
INT SendPack(SERVERID aiServerID, SESSIONID aiESSession,USERID aiUserID,int32 aiToken, int aiFD,
     ITcpSvr *apTcpSvr, IPTYPE aiIP, WORD awPort, T &aoSendStruct)
{
    if (NULL == apTcpSvr)
    {
        return -1;
    }
    
    STRU_SVR_ES_GENERAL_PACKAGE_P<T> loSendPacket;
    loSendPacket.miESID = aiServerID;
    loSendPacket.miESSession = aiESSession;
    loSendPacket.miID = aiUserID;
    loSendPacket.miToken = aiToken;
    loSendPacket.mpoUserLoad= &aoSendStruct;

    int32 lwLen = 0;
    BYTE lpBuffer[DEF_MAX_GENERAL_PACK_LEN];
    lwLen = loSendPacket.Pack(lpBuffer, DEF_MAX_GENERAL_PACK_LEN);
    if(lwLen<=0)
    {
        LOG_TRACE(3, 0, __FUNCTION__, " pack error type:"<< loSendPacket.GetPackType()
            <<" aiFD="<<aiFD
            <<" aiServerID=" <<aiServerID
            <<" aiESSession=" <<aiESSession
            <<" UserID=" <<aiUserID
            <<" Token"<<aiToken
            <<" IP = "<<GetIPString(aiIP)
            <<" : "<<ntohs(awPort)
            );
        return -1;
    };

    LOG_TRACE(7, true, __FUNCTION__, __LINE__<<" Notify send pack!"
        <<" UserID = "<<aiUserID
        <<" : "<<ntohs(awPort)
        <<" packetlegth = "<<lwLen
        <<" IP = "<<GetIPString(aiIP)
        <<" : "<<ntohs(awPort)
        <<" fd = "<<aiFD
        );

    return apTcpSvr->SendData(aiFD, lpBuffer, lwLen);
}

