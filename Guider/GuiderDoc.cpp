// GuiderDoc.cpp : CGuiderDoc 类的实现
//

#include "stdafx.h"
#include "Guider.h"

#include "GuiderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGuiderDoc

IMPLEMENT_DYNCREATE(CGuiderDoc, CDocument)

BEGIN_MESSAGE_MAP(CGuiderDoc, CDocument)
END_MESSAGE_MAP()


// CGuiderDoc 构造/析构

CGuiderDoc::CGuiderDoc()
{
	// TODO: 在此添加一次性构造代码
	for(int j=0;j<100;j++)  //初始化点
		points[j]=CPoint(0,0);
	for(int j=0;j<200;j++)  //初始化边
		roads[j]=CPoint(0,0);
	roadNum=0;
	//点坐标
	points [0]=CPoint(278,15);  //北门
	points [1]=CPoint(278,64);  //国旗
	points [2]=CPoint(320,102); //电信
	points [3]=CPoint(355,102); //学6
	points [4]=CPoint(420,102); //球馆
	points [5]=CPoint(420,158); //澡堂
	points [6]=CPoint(500,158); //体育场
	points [7]=CPoint(500,244); //学11-1
	points [8]=CPoint(509,244); //体育馆-西北
	points [9]=CPoint(588,244); //体育馆-东北
	points [10]=CPoint(588,274); //体育馆-东
	points [11]=CPoint(613,274); //东门

	points [12]=CPoint(509,274); //体育馆-西

	points [13]=CPoint(420,216); //综合服务楼
	points [14]=CPoint(422,274); //1餐

	points [15]=CPoint(427,363); //家属区-1餐南
	points [16]=CPoint(427,428); //家属区-南街1
	points [17]=CPoint(434,480); //荟萃湖-入口
	points [18]=CPoint(614,414); //荟萃湖-东北
	points [19]=CPoint(614,494); //荟萃湖-东
	points [20]=CPoint(493,503); //荟萃湖-桥
	points [21]=CPoint(493,558); //荟萃湖-岛

	points [22]=CPoint(618,618); //荟萃湖-东南
	points [23]=CPoint(419,618); //荟萃湖-西南

	points [24]=CPoint(355,216);  //学1
	points [25]=CPoint(355,274);  //大学生文化活动中心
	points [26]=CPoint(360,363);  //小学
	points [27]=CPoint(362,428);  //家属区-南街2
	points [28]=CPoint(258,428);  //唯真唯实--南街3
	points [29]=CPoint(278,622);  //南门

	points [30]=CPoint(235,107); //计通学院
	points [31]=CPoint(194,107); //出版社
	//points [32]=CPoint(161,107); //印刷厂
	points [33]=CPoint(138,107); //远程教育中心 
	points [34]=CPoint(67,107); //装配厂
	points [35]=CPoint(67,152); //4教-西北
	points [36]=CPoint(67,216); //中学-北
	points [37]=CPoint(65,274); //中学-南
	points [38]=CPoint(12,274); //西门-北

	points [39]=CPoint(216,64); //物理实验楼
	points [40]=CPoint(355,172); //外语村－南
	points [41]=CPoint(258,172); //图书馆－旧馆
	points [42]=CPoint(258,216); //2教
	points [43]=CPoint(194,172); //４教－东
	points [44]=CPoint(194,152); //４教－东北
	points [45]=CPoint(64,48); //学校东北角
	points [46]=CPoint(194,216); //三教
	points [47]=CPoint(132,216); //西配楼－北
	points [48]=CPoint(132,274); //西配楼－南
	points [49]=CPoint(222,274); //主楼-东南
	points [50]=CPoint(258,274); //东配楼－南
	points [51]=CPoint(222,216); //主楼-东北
	points [52]=CPoint(166,216); //主楼-西北
	points [53]=CPoint(166,274); //主楼-西南

	points [54]=CPoint(132,355); //太阳广场-西南
	points [55]=CPoint(64,355); //54-西
	points [56]=CPoint(194,355); //太阳广场-南
	points [57]=CPoint(258,355); //太阳广场-东南
	points [58]=CPoint(258,364); //57-南

	points [59]=CPoint(12,428); //西门-南
	points [60]=CPoint(64,428); //南街-6
	points [61]=CPoint(132,428); //南街-5
	points [62]=CPoint(194,428); //南街-4

	points [63]=CPoint(138,152); //工程实习中心




	for(int i=0;i<64;i++)      //将点插入图中
		graph_doc.insertv (-(i+1));
	this->graph_doc .removev (-33);

}

CGuiderDoc::~CGuiderDoc()
{
}

BOOL CGuiderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGuiderDoc 序列化

void CGuiderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGuiderDoc 诊断

#ifdef _DEBUG
void CGuiderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGuiderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// 修改标题栏

void CGuiderDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle (L"中国石油大学（华东）- -校园导航系统");
}
