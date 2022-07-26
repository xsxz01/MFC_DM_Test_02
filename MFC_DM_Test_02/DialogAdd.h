#pragma once
#include "afxdialogex.h"


// DialogAdd 对话框

class DialogAdd : public CDialogEx
{
	DECLARE_DYNAMIC(DialogAdd)

public:
	DialogAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_TASK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	// 姓名
	CEdit username;
	// 年龄
	CEdit user_age;
	// 性别
	CComboBox user_sex;
};
