// CAngleDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication 20190814.h"
#include "CAngleDialog.h"
#include "afxdialogex.h"


// CAngleDialog 대화 상자

IMPLEMENT_DYNAMIC(CAngleDialog, CDialogEx)

CAngleDialog::CAngleDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANGLEINPUT, pParent)
	, m_iAngle(0)
{

}

CAngleDialog::~CAngleDialog()
{
}

void CAngleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_ANGLE, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleDialog, CDialogEx)
END_MESSAGE_MAP()


// CAngleDialog 메시지 처리기
