// Dlg_Dynamic_Site.cpp : 实现文件
//

#include "stdafx.h"
#include "Guider.h"
#include "Dlg_Dynamic_Site.h"


// Dlg_Dynamic_Site 对话框

IMPLEMENT_DYNAMIC(Dlg_Dynamic_Site, CDialog)

Dlg_Dynamic_Site::Dlg_Dynamic_Site(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Dynamic_Site::IDD, pParent)
{

}

Dlg_Dynamic_Site::~Dlg_Dynamic_Site()
{
}

void Dlg_Dynamic_Site::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dlg_Dynamic_Site, CDialog)
END_MESSAGE_MAP()


// Dlg_Dynamic_Site 消息处理程序
