
// MFC_DM_Test_02Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_DM_Test_02.h"
#include "MFC_DM_Test_02Dlg.h"
#include "afxdialogex.h"
#include "DialogAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDMTest02Dlg 对话框



CMFCDMTest02Dlg::CMFCDMTest02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DM_TEST_02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDMTest02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_Version, label_version);
	//  DDX_Text(pDX, IDC_EDIT2, default_enum_window);
	//  DDX_Control(pDX, IDC_EDIT2, edit_enum_window);
	//  DDX_Text(pDX, IDC_EDIT2, default_enum_window);
	DDX_Control(pDX, IDC_EDIT2, edit_enum_window);
	DDX_Control(pDX, IDC_COMBO1, DisplayInput);
	DDX_Control(pDX, IDC_LIST1, task_list);
}

BEGIN_MESSAGE_MAP(CMFCDMTest02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_EN_KILLFOCUS(IDC_EDIT2, &CMFCDMTest02Dlg::OnEnKillfocusEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDMTest02Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDMTest02Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCDMTest02Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCDMTest02Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCDMTest02Dlg::OnBnClickedButton6)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCDMTest02Dlg::OnCbnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CMFCDMTest02Dlg::OnEnKillfocusEdit2)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCDMTest02Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCDMTest02Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCDMTest02Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCDMTest02Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMFCDMTest02Dlg::OnBnClickedMfcbutton1)
END_MESSAGE_MAP()


// CMFCDMTest02Dlg 消息处理程序

BOOL CMFCDMTest02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 设置版本号
	auto version = new CString("版本号：");
	version->Append(dm.Ver());
	this->label_version.SetWindowText(version->GetString());
	// 设置默认窗口枚举时间
	auto enum_window = 10000;
	CString str;
	str.Format(__T("%d"), enum_window);
	this->edit_enum_window.SetWindowText(str);
	int result_code = this->dm.SetEnumWindowDelay(enum_window);
	/*switch (result_code)
	{
	case 1:
		::MessageBoxA(NULL, "成功", "提示", MB_OK);
		break;
	case 0:
		::MessageBoxA(NULL, "失败", "错误", MB_OK);
		break;
	default:
		break;
	}*/
	// 图色的获取方式选项
	this->DisplayInput.AddString(__T("mem:addr,size"));
	this->DisplayInput.AddString(__T("pic:file"));
	this->DisplayInput.AddString(__T("screen"));
	// 加载报表列表框
	CString head[] = { TEXT("姓名"),TEXT("年龄"),TEXT("性别") };
	CString name[] = { TEXT("李白"),TEXT("鲁班"),TEXT("韩信"),
					TEXT("亚索"),TEXT("达摩"),TEXT("小明") };
	// 动态插入列标题
	int arr_len = sizeof(head) / sizeof(head[0]);
	for (size_t i = 0; i < arr_len; i++)
	{
		CString tHead = head[i];
		this->task_list.InsertColumn(i, head[i], LVCFMT_LEFT, 100);
	}
	/*this->task_list.InsertColumn(0, head[0], LVCFMT_LEFT, 100);
	this->task_list.InsertColumn(1, head[1], LVCFMT_LEFT, 100);
	this->task_list.InsertColumn(2, head[2], LVCFMT_LEFT, 100);*/
	
	// 插入正文内容
	//for (int i = 0;i < 6;i++) {
	//	//	CString str;
	//	//  str.Format(TEXT("张三_%d"),i);
	//	//	str.Format(TEXT("name[i]_%d"),i);

	//		//确定行数
	//	this->task_list.InsertItem(i, name[i]);

	//	//设置列内容
	//	int j = 0;
	//	int age = 23;
	//	this->task_list.SetItemText(i, ++j, TEXT("23"));//怎么设置int
	//	this->task_list.SetItemText(i, ++j, TEXT("男"));

	//}
	//设置风格样式
	//LVS_EX_GRIDLINES 网格
	//LVS_EX_FULLROWSELECT 选中整行
	this->task_list.SetExtendedStyle(this->task_list.GetExtendedStyle()
		| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDMTest02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDMTest02Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDMTest02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMFCDMTest02Dlg::OnEnKillfocusEdit2()
//{
	// TODO: 在此添加控件通知处理程序代码
//}


void CMFCDMTest02Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	bool current_value = this->PicCache;
	current_value = !current_value;
	long result_code = this->dm.EnablePicCache(current_value);
	this->parse_code(result_code);
	if (current_value)
	{
		this->msg("开启成功", "提示");
	}
	else
	{
		this->msg("关闭成功", "提示");
	}
	this->PicCache = current_value;
}

void CMFCDMTest02Dlg::parse_code(long code) {
	switch (code)
	{
	case 1:
		::MessageBoxA(NULL, "成功", "提示", MB_OK);
		break;
	case 0:
		::MessageBoxA(NULL, "失败", "错误", MB_OK);
		break;
	default:
		break;
	}
}

void CMFCDMTest02Dlg::msg(LPCSTR content, LPCSTR title) {
	::MessageBoxA(NULL, content, title, MB_OK);
}

void CMFCDMTest02Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path = this->dm.GetBasePath();
	this->msg((LPCSTR)path, "提示");
}


void CMFCDMTest02Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	long count = this->dm.GetDmCount();
	CString current_count;
	current_count.Format(__T("当前进程已经创建的dm对象个数：%d"), count);
	this->msg((LPCSTR)current_count, "提示");
}


void CMFCDMTest02Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	long id = this->dm.GetID();
	CString current_id;
	current_id.Format(__T("当前对象id：%d"), id);
	this->msg((LPCSTR)current_id, "提示");
}


void CMFCDMTest02Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path = this->dm.GetPath();
	this->msg((LPCSTR)path, "提示");
}


void CMFCDMTest02Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = this->DisplayInput.GetCurSel();
	CString mode;
	this->DisplayInput.GetLBText(index, mode);
	long result_code = this->dm.SetDisplayInput(mode);
	this->parse_code(result_code);
}


void CMFCDMTest02Dlg::OnEnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_enum_window;
	this->edit_enum_window.GetWindowTextA(str_enum_window);
	// 字符串转long
	long enum_window = atol(str_enum_window);
	this->dm.SetEnumWindowDelay(enum_window);
}


void CMFCDMTest02Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	bool current_value = this->SpeedNormalGraphic;
	current_value = !current_value;
	long result_code = this->dm.SpeedNormalGraphic(current_value);
	this->parse_code(result_code);
	if (current_value)
	{
		this->msg("开启成功", "提示");
	}
	else
	{
		this->msg("关闭成功", "提示");
	}
	this->SpeedNormalGraphic = current_value;
}


void CMFCDMTest02Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	long current_value = this->ShowErrorMsg;
	current_value = current_value == 1 ? 0 : 1;
	long result_code = this->dm.SetShowErrorMsg(current_value);
	this->parse_code(result_code);
	if (current_value)
	{
		this->msg("开启成功", "提示");
	}
	else
	{
		this->msg("关闭成功", "提示");
	}
	this->ShowErrorMsg = current_value;
}


void CMFCDMTest02Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	long result_code = this->dm.GetLastError();
	switch (result_code)
	{
	case 0:
		this->msg("无错误", "提示");
		break;
	case -1:
		this->msg("你使用了绑定里的收费功能，但是没注册，无法使用.", "提示");
		break;
	case -2:
		this->msg("使用模式0 2 时出现，因为目标窗口有保护. ", "提示");
		break;
	case -3:
		this->msg("使用模式0 2 时出现，可能目标窗口有保护，也可能是异常错误. ", "提示");
		break;
	case -4:
		this->msg("使用模式101 103时出现，这是异常错误.", "提示");
		break;
	case -5:
		this->msg("使用模式101 103时出现, 这个错误的解决办法就是关闭目标窗口，重新打开再绑定即可. ", "提示");
		break;
	case -6:
		this->msg("被安全软件拦截。", "提示");
		break;
	case -7:
	case -9:
		this->msg("使用模式101 103时出现,异常错误. 还有可能是安全软件的问题，比如360等。尝试卸载360.", "提示");
		break;
	case -8:
	case -10:
		this->msg("使用模式101 103时出现, 目标进程可能有保护,也可能是插件版本过老，试试新的或许可以解决.", "提示");
		break;
	case -11:
	case -12:
	case -37:
		this->msg("使用模式101 103时出现, 目标进程有保护. 告诉我解决.", "提示");
		break;
	case -13:
		this->msg("使用模式101 103时出现, 目标进程有保护. 或者是因为上次的绑定没有解绑导致。", "提示");
		break;
	case -14:
		this->msg("可能系统缺少部分DLL,尝试安装d3d. ", "提示");
		break;
	case -16:
		this->msg("可能使用了绑定模式 0 和 101，然后可能指定了一个子窗口.导致不支持.可以换模式2或者103来尝试.  ", "提示");
		break;
	case -17:
		this->msg("模式101 103时出现. 这个是异常错误. 告诉我解决. ", "提示");
		break;
	case -18:
		this->msg("句柄无效. ", "提示");
		break;
	case -19:
		this->msg("使用模式0 11 101时出现,这是异常错误,告诉我解决. ", "提示");
		break;
	case -20:
		this->msg("使用模式101 103 时出现,说明目标进程里没有解绑，并且子绑定达到了最大. ", "提示");
		break;
	case -21:
		this->msg("使用模式任何模式时出现,说明目标进程已经存在了绑定 ", "提示");
		break;
	case -22:
		this->msg("使用模式0 2,绑定64位进程窗口时出现,因为安全软件拦截插件释放的EXE文件导致. ", "提示");
		break;
	case -23:
		this->msg("使用模式0 2,绑定64位进程窗口时出现,因为安全软件拦截插件释放的DLL文件导致 ", "提示");
		break;
	case -24:
	case -25:
		this->msg("使用模式0 2,绑定64位进程窗口时出现,因为安全软件拦截插件运行释放的EXE ", "提示");
		break;
	case -26:
		this->msg("使用模式0 2,绑定64位进程窗口时出现, 因为目标窗口有保护.  ", "提示");
		break;
	case -27:
	case -28:
		this->msg("绑定32位进程窗口时出现，因为使用了不支持的模式，目前暂时只支持模式0 2 11 13 101 103", "提示");
		break;
	case -38:
	case -40:
		this->msg("是用了大于2的绑定模式,并且使用了dx.public.inject.c时，分配内存失败. 可以考虑开启memory系列盾来尝试.", "提示");
		break;
	case -39:
	case -41:
		this->msg("是用了大于2的绑定模式,并且使用了dx.public.inject.c时的异常错误. 可以联系我解决.", "提示");
		break;
	case -42:
		this->msg("绑定时,创建映射内存失败. ", "提示");
		break;
	case -43:
		this->msg("绑定时,映射内存失败.", "提示");
		break;
	case -100:
		this->msg("调用读写内存函数后，发现无效的窗口句柄", "提示");
		break;
	case -101:
		this->msg("读写内存函数失败", "提示");
		break;
	case -200:
		this->msg("AsmCall失败", "提示");
		break;
	default:
		break;
	}

}


void CMFCDMTest02Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	// 以下是文件选择
	/*CFileDialog fdlg(TRUE, _T("文件"), NULL, OFN_HIDEREADONLY, _T("HEX文件(*.hex)|*.hex|所有文件(*.*)|*.*|"), NULL);
	fdlg.m_ofn.lpstrTitle = _T("选择文件夹");
	if (fdlg.DoModal() == IDOK)
	{
		CString str = fdlg.GetPathName();
		MessageBox(str);
		str = fdlg.GetFileName();
		MessageBox(str);
		str = fdlg.GetFileExt();
		MessageBox(str);
		str = fdlg.GetFileTitle();
		MessageBox(str);
		str = fdlg.GetFolderPath();
		MessageBox(str);
	}*/
	char szPath[MAX_PATH] = { '0' };     //存放选择的目录路径 
	CString str;

	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));     //作用为给所有参数都设为0，即NULL
	bi.hwndOwner = GetSafeHwnd();   //bi.hwndOwner = m_hWnd;           
	bi.pidlRoot = NULL;    //设置开始搜索位置，为NULL默认从the desktop folder开始
	bi.pszDisplayName = szPath;   //被选中的文件夹缓冲区地址
	bi.lpszTitle = _T("请选择目录：");   // //该浏览文件夹对话框对话框的显示文本，用来提示该浏览文件夹对话框的功能、作用和目的。
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;   //文件也能被选中
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);  //SHBrowseForFolder用来显示一个让用户可以选择文件夹的对话框，返回值是指向选定的文件夹相对应于所选择根目录地址的路径标识符指针。 
	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		str.Format("%s", szPath);
		long result_code = this->dm.SetPath(str);
		this->parse_code(result_code);
		//AfxMessageBox(str);
	}
	else
		AfxMessageBox("无效的目录，请重新选择");

}


void CMFCDMTest02Dlg::OnBnClickedMfcbutton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 此处跳转到另一个窗口
	DialogAdd d_add;
	d_add.DoModal();
}
