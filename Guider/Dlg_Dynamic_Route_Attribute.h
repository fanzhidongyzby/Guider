#pragma once


// Dlg_Dynamic_Route_Attribute 对话框

class Dlg_Dynamic_Route_Attribute : public CDialog
{
	DECLARE_DYNAMIC(Dlg_Dynamic_Route_Attribute)

public:
	Dlg_Dynamic_Route_Attribute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_Dynamic_Route_Attribute();

// 对话框数据
	enum { IDD = IDD_DIALOG_DYNAMIC_ROUTE_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int DynamicRouteID1;
	CString DynamicRoutePosition1;
	int DynamicRouteID2;
	CString DynamicRoutePosition2;

	CString DynamicRouteLength;
	BYTE DynamicRouteWidth;
	BYTE DynamicRouteColorR;
	BYTE DynamicRouteColorG;
	BYTE DynamicRouteColorB;
	CString DynamicRouteInfo;

	BYTE DynamicRoutePointSize;
	BYTE DynamicRoutePointColorR;
	BYTE DynamicRoutePointColorG;
	BYTE DynamicRoutePointColorB;
	afx_msg void OnBnClickedOk();
};
