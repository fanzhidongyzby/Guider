// Guider.h : Guider Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGuiderApp:
// �йش����ʵ�֣������ Guider.cpp
//

class CGuiderApp : public CWinApp
{
public:
	CGuiderApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGuiderApp theApp;