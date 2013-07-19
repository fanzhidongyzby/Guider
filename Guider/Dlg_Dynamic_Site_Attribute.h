#pragma once
#include "afxwin.h"


// Dlg_Dynamic_Site_Attribute �Ի���

class Dlg_Dynamic_Site_Attribute : public CDialog
{
	DECLARE_DYNAMIC(Dlg_Dynamic_Site_Attribute)

public:
	Dlg_Dynamic_Site_Attribute(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_Dynamic_Site_Attribute();

// �Ի�������
	enum { IDD = IDD_DIALOG_DYNAMIC_SITE_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
