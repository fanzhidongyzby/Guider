#pragma once
#include "afxwin.h"


// Dlg_App_Set �Ի���

class Dlg_App_Set : public CDialog
{
	DECLARE_DYNAMIC(Dlg_App_Set)

public:
	Dlg_App_Set(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_App_Set();

// �Ի�������
	enum { IDD = IDD_DIALOG_APP_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	////�ص�
    CString SiteStyle;
	BYTE SiteColorR;
	BYTE SiteColorG;
	BYTE SiteColorB;
	BYTE SiteSize;
	CString SiteInfo;
	////·��
	//����
	BYTE RouteWidth;
	CString RouteInfo;
	BYTE RouteColorR;
	BYTE RouteColorG;
	BYTE RouteColorB;
	BOOL RouteShowLength;
	//�۵�
	BYTE RoutePointSize;
	BYTE RoutePointColorR;
	BYTE RoutePointColorG;
	BYTE RoutePointColorB;
	afx_msg void OnBnClickedOk();
	
	
	BOOL ShowSiteInfo;
};
