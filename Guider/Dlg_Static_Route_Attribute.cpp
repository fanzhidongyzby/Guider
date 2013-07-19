// Dlg_Static_Route_Attribute.cpp : 实现文件
//

#include "stdafx.h"
#include "Guider.h"
#include "Dlg_Static_Route_Attribute.h"


// Dlg_Static_Route_Attribute 对话框

IMPLEMENT_DYNAMIC(Dlg_Static_Route_Attribute, CDialog)

Dlg_Static_Route_Attribute::Dlg_Static_Route_Attribute(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Static_Route_Attribute::IDD, pParent)
	, S_P_C_R(0)
	, S_P_P_C_G(255)
	, S_P_P_C_B(0)
	, S_P_P_W(1)
	, S_R_P_W(1)
	, S_R_P_C_R(0)
	, S_R_P_C_G(255)
	, S_R_P_C_B(0)
	, S_L_P_W(3)
	, S_L_P_C_R(247)
	, S_L_P_C_G(118)
	, S_L_P_C_B(2)
	, S_L_S(5)
	, S_W_S_P_L(FALSE)
{

}

Dlg_Static_Route_Attribute::~Dlg_Static_Route_Attribute()
{
}

void Dlg_Static_Route_Attribute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SSCR, S_P_C_R);
	DDV_MinMaxInt(pDX, S_P_C_R, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SSCG, S_P_P_C_G);
	DDV_MinMaxInt(pDX, S_P_P_C_G, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SSCB, S_P_P_C_B);
	DDV_MinMaxInt(pDX, S_P_P_C_B, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SSS, S_P_P_W);
	DDV_MinMaxInt(pDX, S_P_P_W, 0, 10);
	DDX_Text(pDX, IDC_EDIT_SRW, S_R_P_W);
	DDV_MinMaxInt(pDX, S_R_P_W, 0, 10);
	DDX_Text(pDX, IDC_EDIT_SRCR, S_R_P_C_R);
	DDV_MinMaxInt(pDX, S_R_P_C_R, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SRCG, S_R_P_C_G);
	DDV_MinMaxInt(pDX, S_R_P_C_G, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SRCB, S_R_P_C_B);
	DDV_MinMaxInt(pDX, S_R_P_C_B, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SRPS, S_L_P_W);
	DDV_MinMaxInt(pDX, S_L_P_W, 1, 10);
	DDX_Text(pDX, IDC_EDIT_SRPCR, S_L_P_C_R);
	DDV_MinMaxInt(pDX, S_L_P_C_R, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SRPCG, S_L_P_C_G);
	DDV_MinMaxInt(pDX, S_L_P_C_G, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SRPCB, S_L_P_C_B);
	DDV_MinMaxInt(pDX, S_L_P_C_B, 0, 255);
	DDX_Text(pDX, IDC_EDIT4, S_L_S);
	DDV_MinMaxInt(pDX, S_L_S, 1, 10);
	DDX_Check(pDX, IDC_CHECK1, S_W_S_P_L);
}


BEGIN_MESSAGE_MAP(Dlg_Static_Route_Attribute, CDialog)
END_MESSAGE_MAP()


// Dlg_Static_Route_Attribute 消息处理程序
