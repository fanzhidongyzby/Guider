#pragma once
#include "afxwin.h"


// Dlg_Dynamic_Site_Attribute 对话框

class Dlg_Dynamic_Site_Attribute : public CDialog
{
	DECLARE_DYNAMIC(Dlg_Dynamic_Site_Attribute)

public:
	Dlg_Dynamic_Site_Attribute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_Dynamic_Site_Attribute();

// 对话框数据
	enum { IDD = IDD_DIALOG_DYNAMIC_SITE_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int DynamicSiteID;
	CString DynamicSitePosition;

	CString DynamicSiteStyle;
	BYTE DynamicSiteColorR;
	BYTE DynamicSiteColorG;
	BYTE DynamicSiteColorB;
	BYTE DynamicSiteSize;
	CString DynamicSiteInfo;

	afx_msg void OnBnClickedOk();
};
