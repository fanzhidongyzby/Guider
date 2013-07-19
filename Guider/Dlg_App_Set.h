#pragma once
#include "afxwin.h"


// Dlg_App_Set 对话框

class Dlg_App_Set : public CDialog
{
	DECLARE_DYNAMIC(Dlg_App_Set)

public:
	Dlg_App_Set(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_App_Set();

// 对话框数据
	enum { IDD = IDD_DIALOG_APP_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	////地点
    CString SiteStyle;
	BYTE SiteColorR;
	BYTE SiteColorG;
	BYTE SiteColorB;
	BYTE SiteSize;
	CString SiteInfo;
	////路径
	//折线
	BYTE RouteWidth;
	CString RouteInfo;
	BYTE RouteColorR;
	BYTE RouteColorG;
	BYTE RouteColorB;
	BOOL RouteShowLength;
	//折点
	BYTE RoutePointSize;
	BYTE RoutePointColorR;
	BYTE RoutePointColorG;
	BYTE RoutePointColorB;
	afx_msg void OnBnClickedOk();
	
	
	BOOL ShowSiteInfo;
};
