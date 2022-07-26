
// MFC_DM_Test_02.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFC_DM_Test_02.h"
#include "MFC_DM_Test_02Dlg.h"
#include "obj.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDMTest02App

BEGIN_MESSAGE_MAP(CMFCDMTest02App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCDMTest02App 构造

CMFCDMTest02App::CMFCDMTest02App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCDMTest02App 对象

CMFCDMTest02App theApp;


// CMFCDMTest02App 初始化

BOOL CMFCDMTest02App::InitInstance()
{
	AfxOleInit();
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	// 初始化大漠插件
	this->init_dm();

	CMFCDMTest02Dlg dlg;
	m_pMainWnd = &dlg;
	// 执行到这里时，窗口并不会显示，只有DoModal才会显示，并且直到用户关闭对话框才返回
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	// 销毁数据
	delete g_dm;
	return FALSE;
}

void CMFCDMTest02App::init_dm() {
	// 初始化COM(mta)
// 指明基于当前线程的并发模式和初始化选项
	HRESULT result = CoInitializeEx(NULL, COINITBASE_MULTITHREADED);
	/*if (S_OK == result)
	{
		::MessageBoxA(NULL, "COM库初始化成功。", "", MB_OK);
	}
	else */
	if (S_FALSE == result) {
		::MessageBoxA(NULL, "当前线程上，COM库已经被初始化。", "", MB_OK);
	}
	else if (RPC_E_CHANGED_MODE == result) {
		::MessageBoxA(NULL, "COM库已经被初始化且传入参数设置的并发模式和本次不同。", "", MB_OK);
	}

	// 创建对象
	g_dm = new dmsoft;
	if (g_dm == NULL)
	{
		::MessageBoxA(NULL, "大漠插件初始化失败", "错误", MB_OK);
		exit(-1);
	}

	// 注册大漠插件
	auto code = __T("qq15027249575284a1b427a6508c76a5dd615840ac99");
	auto vinfo = __T("0ab");
	long result_login_code = this->g_dm->Reg(code, vinfo);
	//::MessageBoxA(NULL, CW2A(this->g_dm->Ver().GetString()), "提示", MB_OK);
	switch (result_login_code)
	{
	case 1:
		::MessageBoxA(NULL, "大漠插件注册成功", "提示", MB_OK);
		break;
	case -1:
		::MessageBoxA(NULL, "无法连接网络,(可能防火墙拦截,如果可以正常访问大漠插件网站，那就可以肯定是被防火墙拦截)", "错误", MB_OK);
		exit(-1);
		break;
	case -2:
		::MessageBoxA(NULL, "进程没有以管理员方式运行. (出现在win7 win8 vista 2008.建议关闭uac)", "提示", MB_OK);
		exit(-1);
		break;
	case 0:
		::MessageBoxA(NULL, "失败 (未知错误)，请联系管理员或开发者", "提示", MB_OK);
		exit(-1);
		break;
	case 2:
		::MessageBoxA(NULL, "余额不足", "提示", MB_OK);
		exit(-1);
		break;
	case 3:
		::MessageBoxA(NULL, "绑定了本机器，但是账户余额不足50元.", "提示", MB_OK);
		exit(-1);
		break;
	case 4:
		::MessageBoxA(NULL, "注册码错误", "提示", MB_OK);
		exit(-1);
		break;
	case 5:
		::MessageBoxA(NULL, "你的机器或者IP在黑名单列表中或者不在白名单列表中.", "提示", MB_OK);
		exit(-1);
		break;
	case 6:
		exit(-1);
		::MessageBoxA(NULL, "非法使用插件.", "提示", MB_OK);
		break;
	case 7:
		::MessageBoxA(NULL, "你的帐号因为非法使用被封禁.", "提示", MB_OK);
		exit(-1);
		break;
	case 8:
		::MessageBoxA(NULL, "ver_info不在你设置的附加白名单中.", "提示", MB_OK);
		exit(-1);
		break;
	case 77:
		::MessageBoxA(NULL, "机器码或者IP因为非法使用，而被封禁.", "提示", MB_OK);
		exit(-1);
		break;
	case 777:
		::MessageBoxA(NULL, "同一个机器码注册次数超过了服务器限制,被暂时封禁.", "提示", MB_OK);
		exit(-1);
		break;
	case -8:
		::MessageBoxA(NULL, "版本附加信息长度超过了20", "提示", MB_OK);
		exit(-1);
		break;
	case -9:
		::MessageBoxA(NULL, "版本附加信息里包含了非法字母.", "提示", MB_OK);
		exit(-1);
		break;
	default:
		::MessageBoxA(NULL, "出现未知情况，请联系管理员或开发者", "提示", MB_OK);
		exit(-1);
		break;
	}
}