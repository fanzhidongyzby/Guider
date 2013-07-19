#pragma once


// Dlg_Static_Site_Attribute 对话框

class Dlg_Static_Site_Attribute : public CDialog
{
	DECLARE_DYNAMIC(Dlg_Static_Site_Attribute)

public:
	Dlg_Static_Site_Attribute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_Static_Site_Attribute();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATIC_SITE_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
