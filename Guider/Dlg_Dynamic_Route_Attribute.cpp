// Dlg_Dynamic_Route_Attribute.cpp : 实现文件
//

#include "stdafx.h"
#include "Guider.h"
#include "Dlg_Dynamic_Route_Attribute.h"
#include"MainFrm.h"
#include"GuiderView.h"
#include"app_veriable.h"


// Dlg_Dynamic_Route_Attribute 对话框

IMPLEMENT_DYNAMIC(Dlg_Dynamic_Route_Attribute, CDialog)

Dlg_Dynamic_Route_Attribute::Dlg_Dynamic_Route_Attribute(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Dynamic_Route_Attribute::IDD, pParent)
	, DynamicRouteID1(0)
	, DynamicRoutePosition1(_T(""))
	, DynamicRouteID2(0)
	, DynamicRoutePosition2(_T(""))
	, DynamicRouteLength(_T(""))
	, DynamicRouteWidth(0)
	, DynamicRouteColorR(0)
	, DynamicRouteColorG(0)
	, DynamicRouteColorB(0)
	, DynamicRouteInfo(_T(""))
	, DynamicRoutePointSize(0)
	, DynamicRoutePointColorR(0)
	, DynamicRoutePointColorG(0)
	, DynamicRoutePointColorB(0)
{

}

Dlg_Dynamic_Route_Attribute::~Dlg_Dynamic_Route_Attribute()
{
}

void Dlg_Dynamic_Route_Attribute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DRID1, DynamicRouteID1);
	DDX_Text(pDX, IDC_STATIC_DRP1, DynamicRoutePosition1);
	DDX_Text(pDX, IDC_STATIC_DRID2, DynamicRouteID2);
	DDX_Text(pDX, IDC_STATIC_DRP2, DynamicRoutePosition2);
	DDX_Text(pDX, IDC_STATIC_DRL, DynamicRouteLength);

	DDX_Text(pDX, IDC_EDIT_DRW, DynamicRouteWidth);
	DDV_MinMaxByte(pDX, DynamicRouteWidth, 1, 10);
	DDX_Text(pDX, IDC_EDIT_DRCR, DynamicRouteColorR);
	DDV_MinMaxByte(pDX, DynamicRouteColorR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DRCG, DynamicRouteColorG);
	DDV_MinMaxByte(pDX, DynamicRouteColorG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DRCB, DynamicRouteColorB);
	DDV_MinMaxByte(pDX, DynamicRouteColorB, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DRI, DynamicRouteInfo);
	DDX_Text(pDX, IDC_EDIT_DRPS, DynamicRoutePointSize);
	DDV_MinMaxByte(pDX, DynamicRoutePointSize, 1, 10);
	DDX_Text(pDX, IDC_EDIT_DRPCR, DynamicRoutePointColorR);
	DDV_MinMaxByte(pDX, DynamicRoutePointColorR, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DRPCG, DynamicRoutePointColorG);
	DDV_MinMaxByte(pDX, DynamicRoutePointColorG, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DRPCB, DynamicRoutePointColorB);
	DDV_MinMaxByte(pDX, DynamicRoutePointColorB, 0, 255);
}


BEGIN_MESSAGE_MAP(Dlg_Dynamic_Route_Attribute, CDialog)

	ON_BN_CLICKED(IDOK, &Dlg_Dynamic_Route_Attribute::OnBnClickedOk)
END_MESSAGE_MAP()


// Dlg_Dynamic_Route_Attribute 消息处理程序


void Dlg_Dynamic_Route_Attribute::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * fr=(CMainFrame*)AfxGetMainWnd();
	CGuiderView * pv=(CGuiderView * )fr->GetActiveView();

	UpdateData(TRUE);   //   DDX,获取数据   
	//if(pv->dlgDyRouteAttr.DoModal()==IDOK)
	{
		//MessageBox(L"aaa");
		if(App_Veriable::SelectedRouteID1!=0&&App_Veriable::SelectedRouteID2!=0)//路径
		{

			Route*rp=pv->routelist.GetOfID(App_Veriable::SelectedRouteID1,App_Veriable::SelectedRouteID2);

			rp->Width=pv->dlgDyRouteAttr.DynamicRouteWidth;

			COLORREF c=RGB(
				pv->dlgDyRouteAttr.DynamicRouteColorR
				,pv->dlgDyRouteAttr.DynamicRouteColorG
				,pv->dlgDyRouteAttr.DynamicRouteColorB);
			rp->Color=c;

			rp->RouteInfo=pv->dlgDyRouteAttr.DynamicRouteInfo;

			rp->Points->size=pv->dlgDyRouteAttr.DynamicRoutePointSize;

			c=RGB(
				pv->dlgDyRouteAttr.DynamicRoutePointColorR
				,pv->dlgDyRouteAttr.DynamicRoutePointColorG
				,pv->dlgDyRouteAttr.DynamicRoutePointColorB);
			rp->Points->color=c;
		}
	}
	pv->Invalidate();
	OnOK();
}
