
// MFC_DM_Test_02.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include "obj.h"

// CMFCDMTest02App:
// 有关此类的实现，请参阅 MFC_DM_Test_02.cpp
//

class CMFCDMTest02App : public CWinApp
{
public:
	CMFCDMTest02App();
	// 定义一个全局的dm对象
	dmsoft* g_dm = NULL;
	void init_dm();
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMFCDMTest02App theApp;
