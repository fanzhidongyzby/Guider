#pragma once


// Dlg_Static_Site_Attribute �Ի���

class Dlg_Static_Site_Attribute : public CDialog
{
	DECLARE_DYNAMIC(Dlg_Static_Site_Attribute)

public:
	Dlg_Static_Site_Attribute(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_Static_Site_Attribute();

// �Ի�������
	enum { IDD = IDD_DIALOG_STATIC_SITE_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
