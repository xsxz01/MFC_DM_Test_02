
// MFC_DM_Test_02Dlg.h: 头文件
//

#pragma once


// CMFCDMTest02Dlg 对话框
class CMFCDMTest02Dlg : public CDialogEx
{
// 构造
public:
	CMFCDMTest02Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	void parse_code(long code);
	void msg(LPCSTR content, LPCSTR title);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DM_TEST_02_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	dmsoft dm;
	// 大漠插件版本
	CStatic label_version;
//	afx_msg void OnEnKillfocusEdit2();
	CEdit edit_enum_window;
	bool PicCache = TRUE;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	// 设定图色的获取方式，默认是显示器或者后台窗口(具体参考BindWindow)
	CComboBox DisplayInput;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnKillfocusEdit2();
	bool SpeedNormalGraphic = FALSE;
	afx_msg void OnBnClickedButton9();
	// show 整形数: 0表示不打开,1表示打开
	long ShowErrorMsg = 1;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	// 任务列表
	CListCtrl task_list;
	afx_msg void OnBnClickedMfcbutton1();
};
