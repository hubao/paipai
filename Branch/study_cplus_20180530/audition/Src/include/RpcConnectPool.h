// $_FILEHEADER_BEGIN ***************************
// 版权声明: 北京畅聊天下科技公司版权所有
//			Copyright (C) 2015-  ChangLiaoTianXia Corporation. All Rights
// 文件名称: PayGameAward.h
// 创建日期: 2016/12/8
// 创 建 人: hubao
// 文件说明：
// 原   因:  创建文件
// $_FILEHEADER_END *****************************

#ifndef __RPC_CONNECT_POOL_H__
#define __RPC_CONNECT_POOL_H__

#include "Cha15.8_RefCounter.h"

template<class T>
class CRpcConnPool
{
public:
	CRpcConnPool(void);
	virtual ~CRpcConnPool(void);

	const T* operator->() const
	{
		return p.operator->();
	}
	/*
	 * 初始化接口 用于cgk
	 * return 0 成功 other 失败
	 */
	int init();

	T* getConnect();

public:
	T	*mpObj;

	Handle<T> p;
private:
	int			miConnectCount;
	long		miCounter;
};


template<class T>
CRpcConnPool<T>::CRpcConnPool(void)
{
	miCounter		= 0;
	miConnectCount  = 0;
	mpObj			= NULL;
	return;
}

template<class T>
CRpcConnPool<T>::~CRpcConnPool(void)
{
	delete [] mpObj;
	mpObj = NULL;

	return;
}

template<class T>
int CRpcConnPool<T>::init()
{
	miConnectCount = 2;
	mpObj = new T[miConnectCount]();

	p = new T();
}

template<class T>
T *CRpcConnPool<T>::getConnect()
{
	long liCounter = miCounter++ % miConnectCount;

	if(liCounter >= miConnectCount || liCounter < 0) {
		liCounter = 0;
	}

	cout <<" Success. "
		<<" liCounter = " << liCounter
		<<" miConnectCount = " << miConnectCount
		<<" liObj = " << &mpObj[liCounter] << endl;
	
	//return &mpObj[liCounter];
	return p.operator->();
}

#endif // __RPC_CONNECT_POOL_H__