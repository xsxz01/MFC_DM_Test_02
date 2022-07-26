// DialogAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFC_DM_Test_02.h"
#include "afxdialogex.h"
#include "DialogAdd.h"


// DialogAdd 对话框

IMPLEMENT_DYNAMIC(DialogAdd, CDialogEx)

DialogAdd::DialogAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_TASK, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

DialogAdd::~DialogAdd()
{
}

void DialogAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, username);
	DDX_Control(pDX, IDC_EDIT3, user_age);
	DDX_Control(pDX, IDC_COMBO2, user_sex);
}


BEGIN_MESSAGE_MAP(DialogAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogAdd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &DialogAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// DialogAdd 消息处理程序


void DialogAdd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnClose();
}

#include "MFC_DM_Test_02Dlg.h"
void DialogAdd::OnBnClickedButton2()
{

	// TODO: 在此添加控件通知处理程序代码

	CMFCDMTest02Dlg* parent = (CMFCDMTest02Dlg*)GetParent();
	CString cs_username;
	CString cs_user_age;
	CString cs_user_sex;
	this->username.GetWindowTextA(cs_username);
	this->user_age.GetWindowTextA(cs_user_age);
	this->user_sex.GetLBText(this->user_sex.GetCurSel(), cs_user_sex);
	parent->task_list.InsertItem(0,__T(cs_username));
	int j = 0;
	parent->task_list.SetItemText(0, ++j, __T(cs_user_age));
	parent->task_list.SetItemText(0, ++j, __T(cs_user_sex));
}
