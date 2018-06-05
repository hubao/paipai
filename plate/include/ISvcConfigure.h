#pragma once

// $_FILEHEADER_BEGIN *********************************************************
// 文件名称：ISvcConfigure.h
// 创建日期：20151023
// 创建人：	 zhjx
// 文件说明：数据库配置信息读取服务接口
// $_FILEHEADER_END ***********************************************************

#include <vector>

#define DEF_BUFF_LEN (64)
#define DEF_FOR_RELEASE_TEST_SERVER  (10000)
struct STRU_DB_CONFIG_INFO
{
    uint32  miDbID;                      //数据库id 唯一
    char    mszDbName[DEF_BUFF_LEN];     //数据库名
    char    mszDbUser[DEF_BUFF_LEN];     //用户名
    char    mszDbPwd[DEF_BUFF_LEN];      //登录密码
    int     miDbConnNum;                 //数据库连接数
    int     miShardingNum;    //按ID分片库的个数
    int     miShardingType;   //数据库拆分类型 按天 2，按月 3 ，按ID 1
    char    mszDbAddr[DEF_BUFF_LEN];     //当前地址
    char    mszDbAddrBak[DEF_BUFF_LEN];  //备用地址
    uint16  miDbPort;                    //当前端口
    uint16  miDbPortBak;                 //备用服务端口

    STRU_DB_CONFIG_INFO()
    {
        init();
    }
    void init()
    {
        miDbID = 0;
        memset(mszDbName, 0, DEF_BUFF_LEN);
        memset(mszDbUser, 0, DEF_BUFF_LEN);
        memset(mszDbPwd, 0, DEF_BUFF_LEN);
        miDbConnNum = 0;
        memset(mszDbAddr, 0, DEF_BUFF_LEN);
        memset(mszDbAddrBak, 0, DEF_BUFF_LEN);
        miDbPort = 0;
        miDbPortBak = 0;
        miShardingNum = 0;
        miShardingType = 0;
    }
};

struct STRU_SERVER_INFO                        //服务器地址信息
{
    uint32      miServerID;                    //每个服务id唯一
    uint32      miServerTypeID;                //每种服务单独定义类型
    char        mszServerName[DEF_BUFF_LEN];   //服务名
    char        mszAddr[DEF_BUFF_LEN];         //服务地址
    char        mszAddrBak[DEF_BUFF_LEN];      //备用服务地址
    WORD        mwPort;                        //Rpc服务端口
    WORD        mwPortRpcBak;                  //备用Rpc服务端口
    int         miLinkWeight;                  //均衡负载所承担的权重,增加一个特殊意义用于线上服务测试 DEF_FOR_RELEASE_TEST_SERVER 时为测试服务
    uint32      miShardingID;                  // 分片索引    0:不分片
    uint32      miWorkerCount;
    uint32      miBeginPackID;
    uint32      miEndPackID;
    WORD        mwTcpPort;                     //扩展一个字段Tcp服务端口 //对于一个服务监听两个端口时可以分开使用
    WORD        mwPortTcpBak;                  // 备用Tcp服务端口
    WORD        miStatus;                      // 运行状态(链接老版本CGK服务此项无效)，0:停止, 1:运行
    int32       miShardingNum;                 // 分片数量， -1:无效
    int32       miMaxConnection;
    int32       miTcpConnection;
    int32       miRpcConnection;
    int32       miGroupID;                     // 集群ID, -1:本集群
    STRU_SERVER_INFO()
    {
        init();
    }

    void init()
    {
        mwPort = 0;
        mwTcpPort = 0;
        miServerID = 0;
        miServerTypeID = 0;
        miLinkWeight = 1;

        miShardingID = 0;
        miWorkerCount = 0;
        miBeginPackID = 0;
        miEndPackID = 0;
        mwPortRpcBak = 0;

        mwPortTcpBak = 0;
        memset(mszAddr, 0, DEF_BUFF_LEN);
        memset(mszServerName, 0, DEF_BUFF_LEN);
        memset(mszAddrBak, 0, DEF_BUFF_LEN);

        miStatus = 0;
        miShardingNum = -1;
        miMaxConnection = 0;
        miTcpConnection = 0;
        miRpcConnection = 0;
        miGroupID = -1;
    }
};

struct STRU_SERVER_INFO_V3  : public      STRU_SERVER_INFO                 //服务器地址信息
{
    uint32      miPackMapID;                   // 包类型MapID, 包类型变化通知:ID
    STRU_SERVER_INFO_V3()
    {
        init();
    }
    void init()
    {
    	STRU_SERVER_INFO::init();
        miPackMapID = 0;
    }
};

struct STRU_BACKEND_SERVER_INFO                //服务器地址信息
{
    uint32      miServerID;                    //每个服务id唯一
    uint32      miServerTypeID;                //每种服务单独定义类型
    char        mszServerName[DEF_BUFF_LEN];   //服务名
    char        mszAddr[DEF_BUFF_LEN];         //服务地址
    WORD        mwRpcPort;                        //服务端口

    WORD        mwTcpPort;                     //扩展一个字段Tcp服务端口 //对于一个服务监听两个端口时可以分开使用
    char        mszAddrBak[DEF_BUFF_LEN];     //备用服务地址， 当mszAddr不能用时使用
    WORD        mwRpcPortBak;                  //备用服务端口
    WORD        mwTcpPortBak;                  //扩展一个字段Tcp服务端口 //对于一个服务监听两个端口时可以分开使用
    int         miLinkWeight;                  //均衡负载所承担的权重
    WORD        miStatus;                      // 运行状态(链接老版本CGK服务此项无效)，0:停止, 1:运行
    int32       miMaxConnection;
    int32       miTcpConnection;
    int32       miRpcConnection;
    int32       miGroupID;                     // 集群ID, -1:本集群
    uint32      miWorkerCount;
    uint32      miShardingID;                  // 分片索引    0:不分片
    int32       miShardingNum;                 // 分片数量， -1:无效
    STRU_BACKEND_SERVER_INFO()
    {
        init();
    }

    void init()
    {
        mwRpcPort = 0;
        mwTcpPort = 0;
        miServerID = 0;
        miServerTypeID = 0;
        miLinkWeight = 1;

        mwRpcPortBak = 0;
        mwTcpPortBak = 0;
        memset(mszAddr, 0, DEF_BUFF_LEN);
        memset(mszAddrBak, 0, DEF_BUFF_LEN);
        memset(mszServerName, 0, DEF_BUFF_LEN);

        miStatus = 0;
        miMaxConnection = 0;
        miTcpConnection = 0;
        miRpcConnection = 0;
        miGroupID = -1;
        miWorkerCount = 0;
		miShardingID = 0;
		miShardingNum = -1;
    }
};


enum ENUM_CGK_DATA_TYPE_V3{
	ENUM_CGK_DATA_TYPE_V3_NONE = 0,  // 无
	ENUM_CGK_DATA_TYPE_V3_DB = 1,    // 数据库
	ENUM_CGK_DATA_TYPE_V3_SVR_BACKEND = 2,   // 后端服务
	ENUM_CGK_DATA_TYPE_V3_SVR_FRONTEND = 3,  // 前端服务
	ENUM_CGK_DATA_TYPE_V3_SVR_PACK = 4,      // 服务包类型
	ENUM_CGK_DATA_TYPE_V3_SVR_PROXY = 5,     // 集群代理后端服务
	ENUM_CGK_DATA_TYPE_V3_ERROR = 6,         // 错误描述
	ENUM_CGK_DATA_TYPE_V3_ALL = 100,
};

enum ENUM_CGK_DATA_CHANGE_TYPE{
	ENUM_CGK_DATA_CHANGE_TYPE_NONE = 0,  // 未变动
	ENUM_CGK_DATA_CHANGE_TYPE_ADD = 1,   // 增加
	ENUM_CGK_DATA_CHANGE_TYPE_MODIFY = 2,// 修改
	ENUM_CGK_DATA_CHANGE_TYPE_DEL = 3,   // 删除
	ENUM_CGK_DATA_CHANGE_TYPE_ALL = 4,   // 多重类型
};

/*
 * 数据变更结构体
 * miID 说明：
 *		(miDataType == ENUM_CGK_DATA_TYPE_V3_DB) miID is miDbID;
 *      (miDataType == ENUM_CGK_DATA_TYPE_V3_SVR_BACKEND) miID is miServerID;
 *      (miDataType == ENUM_CGK_DATA_TYPE_V3_SVR_FRONTEND) miID is miServerID;
 *		(miDataType == ENUM_CGK_DATA_TYPE_V3_SVR_PACK) miID is miPackMapID;
 *		(miDataType == ENUM_CGK_DATA_TYPE_V3_SVR_PROXY) miID is miServerID;
 *      (miDataType == ENUM_CGK_DATA_TYPE_V3_ERROR) miID is aiErrorID;
 * */
struct STRU_DATA_CHANGE_DATA
{
	ENUM_CGK_DATA_CHANGE_TYPE miChangeType;  // 数据变化类型
	ENUM_CGK_DATA_TYPE_V3 miDataType;           // 数据类型
	uint32 miID;                              // 数据ID
	int32  miGroupID;                         // 集群ID
	STRU_DATA_CHANGE_DATA()
	{
		miChangeType = ENUM_CGK_DATA_CHANGE_TYPE_NONE;
		miDataType = ENUM_CGK_DATA_TYPE_V3_NONE;
		miID = 0;
		miGroupID = 0;
	}
};

class ISvcConfigureEvent
{
public:

	// $_FUNCTION_BEGIN ******************************
	// 方法名: OnIsLoadComplete
	// 访  问: public
    // 参  数: moEventList  变更列表
	// 返回值: int
	// 说  明: 数据变更通知
	// $_FUNCTION_END ********************************
    virtual void OnDataChange(const std::vector<STRU_DATA_CHANGE_DATA> &moEventList) = 0;
};

class ISvcConfigure
{
public:
    ISvcConfigure(){};
    virtual ~ISvcConfigure(){};
 
    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetDataBaseInfo
    // 函数参数：   
    // aiDatabaseID 数据库ID
    // aoDbInfo 输出的数据库配置信息
    // 成功返回 0 ， 失败 非零
    // 函数说明：读取数据库配置信息
    // $_FUNCTION_END ********************************
    virtual int GetDataBaseInfo(int aiDatabaseID, STRU_DB_CONFIG_INFO &aoDbInfo) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetDescriptByErrorCode
    // 函数参数：   
    // aiErrorID 错误码
    // apszDescript 输出对应的错误信息
    // aiLen 代表 apszDescript 指向内存的长度
    // 成功返回 0 ， 失败 非零
    // 函数说明：读取数据库配置信息
    // $_FUNCTION_END ********************************
    virtual int GetDescriptByErrorCode(int aiErrorID, char *apszDescript, int aiLen) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetServerByServerType
    // 函数参数：
    // aiServerType 错误码
    // aoServerList 输出对应的服务地址列表, 建议最好在调用此接口前aoServerList 提前分配好足够多的对象
    // 成功返回 读取到指定服务类型的服务个数, 失败 -1
    // 函数说明：这个接口代理专用, 建议使用:
    // GetServerByServerType(int aiServerType, std::vector<STRU_SERVER_INFO_V3> &aoServerList)
    // $_FUNCTION_END ********************************
    virtual int GetServerByServerType(int aiServerType, std::vector<STRU_SERVER_INFO> &aoServerList) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：SetVersion
    // 函数参数：
    // aszVersion 服务版本信息，以字符串形式
    // 函数说明：设置当前服务版本信息，服务启动时进行设置
    // $_FUNCTION_END ********************************
    virtual void SetVersion(const char *aszVersion) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetBackendServer
    // 函数参数：
    // aoServerList 输出对应的服务地址列表
    // 成功返回 读取到指定服务类型的服务个数, 失败 -1
    // 函数说明：业务服务使用这个接口
    // $_FUNCTION_END ********************************
    virtual int GetBackendServer(std::vector<STRU_BACKEND_SERVER_INFO> &aoServerList) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetClusterServer
    // 函数参数：
    // aoClusterServerList 输出对应的服务地址列表
    // 成功返回 读取到指定服务类型的服务个数, 失败 -1
    // 函数说明：跨机群代理使用这个接口
    // $_FUNCTION_END ********************************
    virtual int GetClusterServer(std::vector<STRU_SERVER_INFO> &aoClusterServerList) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetServerByServerType
    // 函数参数：
    // aiServerType 服务类型，默认:0
    // aoServerList 输出对应的服务地址列表, 建议最好在调用此接口前aoServerList 提前分配好足够多的对象
    // 成功返回 读取到指定服务类型的服务个数, 失败 -1
    // 函数说明：这个接口代理专用
    // $_FUNCTION_END ********************************
    virtual int GetServerByServerType(int aiServerType, std::vector<STRU_SERVER_INFO_V3> &aoServerList) = 0;

	// $_FUNCTION_BEGIN ******************************
	// 函数名称：RegisterHandler
	// 函数参数：
	// 返 回 值：0 成功，非零失败
	// 函数说明：通过这个接口注册收包处理函数
	// $_FUNCTION_END ********************************
	virtual int RegisterHandler(ISvcConfigureEvent *apServerChgEvent) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetGroupID
    // 函数参数：
    // aiGroupID                 [out] 集群ID -1:未识别
    // 成功返回 0 ， 失败 非零
    // 函数说明：获取CGK Server所属集群ID
    // $_FUNCTION_END ********************************
    virtual int GetGroupID(int &aiGroupID) = 0;

    // $_FUNCTION_BEGIN ******************************
    // 函数名称：GetMyServerInfo
    // 函数参数：
    // aoServerInfo 本服务信息
    // 返回值: 成功返回 0 ， 失败 非零
    // 函数说明：获取本服务信息
    // $_FUNCTION_END ********************************
    virtual int GetMyServerInfo(STRU_BACKEND_SERVER_INFO &aoServerInfo) = 0;
};
