#pragma once


// Dlg_Static_Route_Attribute 对话框

class Dlg_Static_Route_Attribute : public CDialog
{
	DECLARE_DYNAMIC(Dlg_Static_Route_Attribute)

public:
	Dlg_Static_Route_Attribute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_Static_Route_Attribute();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATIC_ROUTE_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int S_P_C_R;
	int S_P_P_C_G;
	int S_P_P_C_B;
	int S_P_P_W;
	int S_R_P_W;
	int S_R_P_C_R;
	int S_R_P_C_G;
	int S_R_P_C_B;
	int S_L_P_W;
	int S_L_P_C_R;
	int S_L_P_C_G;
	int S_L_P_C_B;
	int S_L_S;
	BOOL S_W_S_P_L;
};
