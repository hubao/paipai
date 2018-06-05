//// $_FILEHEADER_BEGIN *******************************************************
// 版权声明:北京畅聊天下科技公司版权所有
//			Copyright (C) 2015-  ChangLiaoTianXia Corporation. All Rights
// 文件名称：BusinessInclude.h
// 创建日期：20150826
// 创 建 人：luojie
// 文件说明：游戏数据存储服务
//
// 原    因：创建新文件
// $_FILEHEADER_END *********************************************************


#ifndef __BUSINESS_INCLUDE_H__
#define __BUSINESS_INCLUDE_H__

#include <iostream>
#include <string>
#include "base0/platform.h"
#include "common/Debug_log.h"
#include "common/basefun.h"
#include "common/System.h"
#include "common/Atomic.h"
#include "const/constdef.h"
#include "const/SvrConstDef.h"
#include "struct/SvrBaseStruct.h"
#include "common/CriticalSection.h"
#include "const/ErrorCodeDef.h"

/*
 * 检查是否是NPC用户(下面的定义只在内网使用)
 */
#define CHECK_IS_NPC_USER(user_id)                                              \
(((user_id)&0x3FFFFFFFFFll) >= 10000000000ll && ((user_id)&0x3FFFFFFFFFll) <= 50000000000ll)


// 服务主逻辑
class CBusinessMain;
extern CBusinessMain theBusinessMain;

#endif
