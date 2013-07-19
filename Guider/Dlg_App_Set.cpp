// Dlg_App_Set.cpp : 实现文件
//

#include "stdafx.h"
#include "Guider.h"
#include "Dlg_App_Set.h"
#include"MainFrm.h"
#include"GuiderView.h"
#include"app_veriable.h"

// Dlg_App_Set 对话框

IMPLEMENT_DYNAMIC(Dlg_App_Set, CDialog)

Dlg_App_Set::Dlg_App_Set(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_App_Set::IDD, pParent)
	, SiteStyle(_T(""))//App_Veriable::DefaultSiteStyle ::DefaultSiteColor
	, SiteColorR(0)
	, SiteColorG(0)
	, SiteColorB(0)
	, SiteSize(0)
	, SiteInfo(_T(""))
	, RouteWidth(1)
	, RouteInfo(_T(""))
	, RouteShowLength(FALSE)
	, RoutePointSize(0)	
	, RouteColorR(0)
	, RouteColorG(0)
	, RouteColorB(0)
	, RoutePointColorR(0)
	, RoutePointColorG(0)
	, RoutePointColorB(0)
	, ShowSiteInfo(FALSE)
{
	////地点
	CString s0;
	switch(App_Veriable::DefaultSiteStyle)
	{
	case'C':s0.Format(L"圆");break;
	case'T':s0.Format(L"三角形");break;
	case'R':s0.Format(L"矩形");break;
	default:s0.Format(L"");break;
	}
	SiteStyle=s0;

	ShowSiteInfo=App_Veriable::ShowSiteInfo;

	SiteColorR=GetRValue(App_Veriable::DefaultSiteColor);
	SiteColorG=GetGValue(App_Veriable::DefaultSiteColor);
	SiteColorB=GetBValue(App_Veriable::DefaultSiteColor);

	SiteSize=App_Veriable::DefaultSiteSize;
	SiteInfo=App_Veriable::DefaultSiteInfo;
	////路径
	//折线
	RouteWidth=App_Veriable::DefaultRouteWidth;
	RouteColorR=GetRValue(App_Veriable::DefaultRouteColor);
	RouteColorG=GetGValue(App_Veriable::DefaultRouteColor);
	RouteColorB=GetBValue(App_Veriable::DefaultRouteColor);

	RouteInfo=App_Veriable::DefaultRouteInfo;
	RouteShowLength=App_Veriable::ShowRouteLength;
	//折点
	RoutePointSize=App_Veriable::DefaultRoutePointSize;
	RoutePointColorR=GetRValue(App_Veriable::DefaultRoutePointColor);
	RoutePointColorG=GetGValue(App_Veriable::DefaultRoutePointColor);
	RoutePointColorB=GetBValue(App_Veriable::DefaultRoutePointColor);
}

Dlg_App_Set::~Dlg_App_Set()
{
}

void Dlg_App_Set::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SCR, SiteColorR);
	DDV_MinMaxByte(pDX, SiteColorR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SCG, SiteColorG);
	DDV_MinMaxByte(pDX, SiteColorG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SCB, SiteColorB);
	DDV_MinMaxByte(pDX, SiteColorB, 0, 255);
	DDX_Text(pDX, IDC_EDIT_SS, SiteSize);
	DDV_MinMaxByte(pDX, SiteSize, 10, 20);
	DDX_Text(pDX, IDC_SI, SiteInfo);
	DDX_Text(pDX, IDC_EDIT_RW, RouteWidth);
	DDV_MinMaxByte(pDX, RouteWidth, 1, 10);
	DDX_Text(pDX, IDC_EDIT_RI, RouteInfo);
	DDX_Check(pDX, IDC_CHECK_RSL, RouteShowLength);
	DDX_Text(pDX, IDC_EDIT_RPS, RoutePointSize);
	DDV_MinMaxByte(pDX, RoutePointSize, 1, 10);
	DDX_CBString(pDX, IDC_COMBO_SS, SiteStyle);

	DDX_Text(pDX, IDC_EDIT_RCR, RouteColorR);
	DDV_MinMaxByte(pDX, RouteColorR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RCG, RouteColorG);
	DDV_MinMaxByte(pDX, RouteColorG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RCB, RouteColorB);
	DDV_MinMaxByte(pDX, RouteColorB, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RPCR, RoutePointColorR);
	DDV_MinMaxByte(pDX, RoutePointColorR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RPCG, RoutePointColorG);
	DDV_MinMaxByte(pDX, RoutePointColorG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_RPCB, RoutePointColorB);
	DDV_MinMaxByte(pDX, RoutePointColorB, 0, 255);
	DDX_Check(pDX, IDC_CHECK_SSI, ShowSiteInfo);
}


BEGIN_MESSAGE_MAP(Dlg_App_Set, CDialog)


	ON_BN_CLICKED(IDOK, &Dlg_App_Set::OnBnClickedOk)
END_MESSAGE_MAP()


// Dlg_App_Set 消息处理程序




void Dlg_App_Set::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * fr=(CMainFrame*)AfxGetMainWnd();
	CGuiderView * pv=(CGuiderView * )fr->GetActiveView();

	UpdateData(TRUE);   //   DDX,获取数据   
	////地点

	App_Veriable::ShowSiteInfo=ShowSiteInfo;
	if(SiteStyle=="圆")App_Veriable::DefaultSiteStyle='C';
	else if(SiteStyle=="三角形")App_Veriable::DefaultSiteStyle='T';
	else if(SiteStyle=="矩形")App_Veriable::DefaultSiteStyle='R';
	else App_Veriable::DefaultSiteStyle='C';

	COLORREF sc=RGB(SiteColorR,SiteColorG,SiteColorB);
	App_Veriable::DefaultSiteColor=sc;


	App_Veriable::DefaultSiteSize=SiteSize;
	App_Veriable::DefaultSiteInfo=SiteInfo;
	////路径
	//折线
	App_Veriable::DefaultRouteWidth=RouteWidth;
	COLORREF rc=RGB(RouteColorR,RouteColorG,RouteColorB);
	App_Veriable::DefaultRouteColor=rc;



	App_Veriable::DefaultRouteInfo=RouteInfo;
	App_Veriable::ShowRouteLength=RouteShowLength;
	//折点
	App_Veriable::DefaultRoutePointSize=RoutePointSize;

	COLORREF rpc=RGB(RoutePointColorR,RoutePointColorG,RoutePointColorB);
	App_Veriable::DefaultRoutePointColor=rpc;

	pv->Invalidate();
	OnOK();
}
