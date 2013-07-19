// Dlg_Dynamic_Site_Attribute.cpp : 实现文件
//
#include "stdafx.h"
#include "Guider.h"
#include "Dlg_Dynamic_Site_Attribute.h"
#include"MainFrm.h"
#include"GuiderView.h"
#include"app_veriable.h"


// Dlg_Dynamic_Site_Attribute 对话框

IMPLEMENT_DYNAMIC(Dlg_Dynamic_Site_Attribute, CDialog)

Dlg_Dynamic_Site_Attribute::Dlg_Dynamic_Site_Attribute(CWnd* pParent /*=NULL*/)
: CDialog(Dlg_Dynamic_Site_Attribute::IDD, pParent)
, DynamicSiteColorR(0)
, DynamicSiteID(0)
, DynamicSitePosition(_T(""))
, DynamicSiteColorG(0)
, DynamicSiteColorB(0)
, DynamicSiteSize(0)
, DynamicSiteInfo(_T(""))
, DynamicSiteStyle(_T("yuan"))
{

}

Dlg_Dynamic_Site_Attribute::~Dlg_Dynamic_Site_Attribute()
{
}

void Dlg_Dynamic_Site_Attribute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DSCR, DynamicSiteColorR);
	DDV_MinMaxByte(pDX, DynamicSiteColorR, 0, 255);
	DDX_Text(pDX, IDC_STATIC_DSID, DynamicSiteID);
	DDX_Text(pDX, IDC_STATIC_DSP, DynamicSitePosition);
	DDX_Text(pDX, IDC_EDIT_DSCG, DynamicSiteColorG);
	DDV_MinMaxByte(pDX, DynamicSiteColorG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DSCB, DynamicSiteColorB);
	DDV_MinMaxByte(pDX, DynamicSiteColorB, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DSS, DynamicSiteSize);
	DDV_MinMaxByte(pDX, DynamicSiteSize, 10, 20);
	DDX_Text(pDX, IDC_DSI, DynamicSiteInfo);
	DDX_CBString(pDX, IDC_COMBO_DSS, DynamicSiteStyle);
}


BEGIN_MESSAGE_MAP(Dlg_Dynamic_Site_Attribute, CDialog)
	ON_BN_CLICKED(IDOK, &Dlg_Dynamic_Site_Attribute::OnBnClickedOk)
END_MESSAGE_MAP()


// Dlg_Dynamic_Site_Attribute 消息处理程序

void Dlg_Dynamic_Site_Attribute::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * fr=(CMainFrame*)AfxGetMainWnd();
	CGuiderView * pv=(CGuiderView * )fr->GetActiveView();

	UpdateData(TRUE);   //   DDX,获取数据   
	//if(pv->dlgDyRouteAttr.DoModal()==IDOK)
	{
		//MessageBox(L"aaa");
		if(App_Veriable::SelectedSiteID!=0)//地点
		{
			Site * s=pv->sitelist.GetOfID(App_Veriable::SelectedSiteID);

			if(pv->dlgDySiteAttr.DynamicSiteStyle=="圆")s->Style='C';
			else if(pv->dlgDySiteAttr.DynamicSiteStyle=="三角形")s->Style='T';
			else if(pv->dlgDySiteAttr.DynamicSiteStyle=="矩形")s->Style='R';
			else s->Style='C';

			COLORREF c=RGB(pv->dlgDySiteAttr.DynamicSiteColorR
				,pv->dlgDySiteAttr.DynamicSiteColorG
				,pv->dlgDySiteAttr.DynamicSiteColorB);
			s->Color=c;

			s->Size=pv->dlgDySiteAttr.DynamicSiteSize;

			s->SiteInfo=pv->dlgDySiteAttr.DynamicSiteInfo;
		}
	}
	pv->Invalidate();
	OnOK();
}
