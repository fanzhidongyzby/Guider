// GuiderView.cpp : CGuiderView 类的实现
//

#include "stdafx.h"
#include "Guider.h"


#include "GuiderView.h"

#include"MainFrm.h"
#include"app_veriable.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGuiderView

IMPLEMENT_DYNCREATE(CGuiderView, CView)

BEGIN_MESSAGE_MAP(CGuiderView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ADD_SITE, &CGuiderView::OnAddSite)
	ON_COMMAND(ID_ADD_ROUTE, &CGuiderView::OnAddRoute)
	ON_COMMAND(ID_DELETE, &CGuiderView::OnDelete)
	ON_COMMAND(ID_REFRASH, &CGuiderView::OnRefrash)
	ON_COMMAND(ID_ATTRIBUTE, &CGuiderView::OnAttribute)



	ON_COMMAND(ID_SHORTEST_ROUTE, &CGuiderView::OnShortestRoute)
	ON_COMMAND(ID_STATIC_SET, &CGuiderView::OnStaticSet)
	ON_COMMAND(ID_FILE_SAVE, &CGuiderView::OnFileSave)
	ON_COMMAND(ID_FILE_NEW, &CGuiderView::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE_AS, &CGuiderView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &CGuiderView::OnFileOpen)
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGuiderView 构造/析构

CGuiderView::CGuiderView()
{
	// TODO: 在此处添加构造代码
	CBitmap bmp;
	//bmp.LoadBitmapW(IDB_BITMAP2); ///加载位图
	bmp.LoadBitmapW (131);
	m_brushBackground.CreatePatternBrush(&bmp); ///创建位图画刷
	////////////////////////////////////////////////////////////////////////////
	m_pMemDC=new CDC();
	m_pMemBitmap=new CBitmap();

}

CGuiderView::~CGuiderView()
{
	delete m_pMemBitmap;
	delete m_pMemDC;
}

BOOL CGuiderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGuiderView 绘制

void CGuiderView::OnDraw(CDC* pDC)
{

	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//..................................................................背景
	CRect rect;
	GetClientRect(rect);///取得客户区域
	pDC->FillRect(rect,&m_brushBackground); ///用背景画刷填充区域
	/////////////////////////////////////////////////////////////////////////
	paint_road_point();
	///////////////////////////////////////////////////////////////////////////
	sitelist.Draw(pDC);
	routelist.Draw(pDC);
}

void CGuiderView::Draw()
{
	sitelist.Draw(m_pMemDC);
	routelist.Draw(m_pMemDC);
}

// CGuiderView 打印

BOOL CGuiderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGuiderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGuiderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CGuiderView 诊断

#ifdef _DEBUG
void CGuiderView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGuiderDoc* CGuiderView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGuiderDoc)));
	return (CGuiderDoc*)m_pDocument;
}
#endif //_DEBUG


// CGuiderView 消息处理程序
BOOL CGuiderView::OnEraseBkgnd(CDC* pDC)//避免背景的闪烁
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return true;
}
int CGuiderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// TODO:  在此添加您专用的创建代码
	//int x=GetSystemMetrics(SM_CXSCREEN);
	//int y=GetSystemMetrics(SM_CYSCREEN);
	//CDC* pDC=GetDC();
	//m_pMemDC->CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC
	//m_pMemBitmap->CreateCompatibleBitmap(pDC,x,y); //创建兼容位图
	//m_pOldBitmap=m_pMemDC->SelectObject(m_pMemBitmap); //将位图选进内存DC,原位图保存到m_pOldBitmap
	//CBrush brush(RGB(255,255,255));
	//m_pMemDC->FillRect(CRect(0,0,x,y),&brush);    //设置客户区背景为白色
	//ReleaseDC(pDC);

	return 0;
}
////////////////////////////////////////////////自定义函数
void CGuiderView::paint_road_point()
{

	//..................获取指针
	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC*pDC=this->GetDC ();
	//........................................画笔
	CPen pen; 
	CPen *oldPen; //A2 
	pen.CreatePen(PS_SOLID, this->dlgStaticAttribute .S_P_P_W ,RGB(this->dlgStaticAttribute .S_P_C_R ,this->dlgStaticAttribute .S_P_P_C_G ,this->dlgStaticAttribute .S_P_P_C_B /*attri.P_R_C ,attri.P_G_C ,attri.P_B_C*/ ));//B
	oldPen=pDC->SelectObject(&pen); //C
	////.........................................画刷
	//CBrush brush;
	//CBrush * oldBrush;
	//brush.CreateHatchBrush (5,RGB(255,255,0));
	//oldBrush=pDC->SelectObject (&brush);

	////选中画刷，绘制点
	//pDC->SelectObject (brush); 
	for(int i=0;i<64;i++)
	{
		if(i==32)continue;
		else
			pDC->Ellipse (pDoc->points [i].x -4,pDoc->points [i].y -4,pDoc->points [i].x +4,pDoc->points [i].y +4);
	}

	////选中画笔，绘制边
	//pen.DeleteObject ();
	//pen.CreatePen(PS_SOLID, 2,RGB(255,0,255));
	//pDC->SelectObject (pen);  

	this->MyLine (1,0,1);
	//	CGuiderDoc* pDoc = GetDocument();
	//pDoc->graph_doc.removee(-1,-2);
	this->MyLine (2,1,30,39);
	this->MyLine (1,1,2);
	this->MyLine (1,2,3);
	this->MyLine (2,3,4,40);
	this->MyLine (1,4,5);
	this->MyLine (2,5,6,13);
	this->MyLine (2,7,6,8);
	this->MyLine (2,8,9,12);
	this->MyLine (2,10,9,11);
	this->MyLine (2,13,14,24);
	this->MyLine (3,14,25,15,12);
	this->MyLine (2,15,16,26);
	this->MyLine (2,16,17,27);
	this->MyLine (2,17,18,23);
	this->MyLine (1,18,19);
	this->MyLine (2,20,21,19);
	this->MyLine (2,22,19,23);
	this->MyLine (3,24,40,42,25);
	this->MyLine (3,26,25,27,58);
	this->MyLine (2,58,57,28);
	this->MyLine (3,28,27,29,62);
	this->MyLine (3,41,40,42,43);
	this->MyLine (2,42,50,51);
	this->MyLine (3,50,25,57,49);
	this->MyLine (3,31,30,33,44);
	this->MyLine (3,46,43,51,52);
	this->MyLine (3,63,44,35,33);
	this->MyLine (3,53,48,52,49);
	this->MyLine (3,56,54,57,62);
	this->MyLine (3,61,62,60,54);
	this->MyLine (2,60,59,55);
	this->MyLine (3,37,55,38,36);
	this->MyLine (2,54,55,48);
	this->MyLine (3,47,48,36,52);
	this->MyLine (3,34,33,35,45);
	this->MyLine (1,35,36);
	this->MyLine (1,37,48);
	this->MyLine (1,43,44);
	this->MyLine (1,49,51);

	pen.DeleteObject(); //G
	//brush.DeleteObject ();

	pDC->SelectObject(oldPen);
	ReleaseDC(pDC);
}

//  以CPoint的点集为基础绘制直线
void CGuiderView::MyLine(int num, int p0, int p1, int p2, int p3)
{
	//..................获取指针
	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC*pDC=this->GetDC ();
	//.....................创建画笔
	CPen pen; 
	CPen *oldPen; //A2 
	pen.CreatePen(PS_DOT,this->dlgStaticAttribute .S_R_P_W ,RGB(this->dlgStaticAttribute .S_R_P_C_R ,this->dlgStaticAttribute .S_R_P_C_G ,this->dlgStaticAttribute .S_R_P_C_B ));//B
	oldPen=pDC->SelectObject(&pen); //C

	HDC hdc=pDC->GetSafeHdc ();
	CString str;
	::SetBkMode(hdc,TRANSPARENT);
	::SetTextColor (hdc,RGB(255-this->dlgStaticAttribute .S_R_P_C_R ,255-this->dlgStaticAttribute .S_R_P_C_G ,255-this->dlgStaticAttribute .S_R_P_C_B));

	p[0]=p0;
	p[1]=p1;
	p[2]=p2;
	p[3]=p3;
	while(num>0)
	{
		pDC->MoveTo (pDoc->points [p[0]]);  //画线
		pDC->LineTo  (pDoc->points[p[num]]);

		double length=sqrt((double)(pDoc->points [p[0]].x -pDoc->points[p[num]].x )*(pDoc->points [p[0]].x -pDoc->points[p[num]].x )+(double)((pDoc->points [p[0]].y -pDoc->points[p[num]].y )*(pDoc->points [p[0]].y -pDoc->points[p[num]].y )));
		length*=2.287;
		pDoc->graph_doc .inserte(-(p[0]+1),-(p[num]+1),length);  //添加边至图

		if(this->dlgStaticAttribute .S_W_S_P_L )
		{
			str.Format (L"%d",(int)length);
			pDC->TextOutW ((pDoc->points [p[0]].x+pDoc->points[p[num]].x )/2,(pDoc->points [p[0]].y+pDoc->points[p[num]].y )/2,str);
		}

		pDoc->roads [pDoc->roadNum ].x =p[0];  //程序记录边
		pDoc->roads [pDoc->roadNum ].y =p[num];
		pDoc->roadNum ++;

		num--;  //下一条
	}
	ReleaseDC(pDC);
}

// // 判断鼠标是否在边上，在的话返回true
bool CGuiderView::WhetherOnRoad(int poi_x, int poi_y)
{
	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;
	CDC*pDC=this->GetDC ();

	for(int num=0;num<pDoc->roadNum ;num++)
	{
		double x1, x2, y1, y2, d0, d1, d2, d3, x0, y0, ave;
		x1 = (double)pDoc->points [pDoc->roads [num].x ].x ;
		y1 = (double)pDoc->points [pDoc->roads [num].x ].y ;
		x2 = (double)pDoc->points [pDoc->roads [num].y ].x ;
		y2 = (double)pDoc->points [pDoc->roads [num].y ].y ;
		//点击坐标
		x0 = poi_x ;
		y0 = poi_y ;
		if ((x0 > x1 && x0 < x2) || (x0 > x2 && x0 < x1)  ||  (((x1=x2)||(x1>x2&&(x1-x2)<10)||(x1<x2&&(x2-x1)<10))&&(y0 > y1 && y0 < y2) || (y0 > y2 && y0 < y1)))//判断点击位置是否在范围以内
		{
			d1 = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));//点击位置到起点距离
			d2 = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));//点击位置到终点距离
			d3  = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));//直线距离
			ave = (d1 + d2 + d3) / 2;
			d0 = sqrt(ave * (ave - d1) * (ave - d2) * (ave - d3)) / d3;//点击位置到直线的距离
			if (d0 < 2) 
			{
				this->length =d3;
				ReleaseDC(pDC);
				return true;	
			}
		}
	}
	ReleaseDC(pDC);
	return false;
}

//  判断鼠标是否在点上
int CGuiderView::WhetherOnPoint(int poi_x, int poi_y)
{
	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;
	CDC*pDC=this->GetDC ();


	for(int i=0;i<63;i++)
	{
		double length=sqrt((double)(pDoc->points [i].x -poi_x )*(pDoc->points [i].x -poi_x )+(double)((pDoc->points [i].y -poi_y )*(pDoc->points [i].y -poi_y )));
		if(length<10)
		{
			ReleaseDC(pDC);
			return -(i+1);
		}
	}
	ReleaseDC(pDC);
	return 0;
}
////////////////////////////////////////////////////鼠标响应函数



//双击，添加路径
void CGuiderView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int ClickID=sitelist.OnSite(point.x,point.y);//获取ID
	if(ClickID!=0)//双击地点,对路径操作
	{
		if(App_Veriable::IsAddingRoute==false&&App_Veriable::RouteBeginID==0)//没有绘制路径
		{
			if(ClickID<0)return ;
			App_Veriable::IsAddingRoute=true;//开始创建路径
			App_Veriable::RouteBeginID=ClickID;//初始化起点ID
			Site* s=sitelist.GetOfID(ClickID);//获取值是ID的对象
			Route*r=new Route();//创建路径
			r->ID1=ClickID;//初始化起始端ID,终端ID为0！！！
			r->AddPoint(s->Position);//添加起点
			int id1,id2;
			routelist.AddRoute(r,id1,id2);//添加到路径链表,两个id应该在成功之后传递
			Invalidate();
		}
		else//正在绘制路径
		{
			CGuiderDoc* pDoc = GetDocument();

			//bool Graph_Link=false;//结合时用graph.Link(int id1,int id2)//判断两点是否已经连接

			if(App_Veriable::RouteBeginID==ClickID||pDoc->graph_doc.Link(App_Veriable::RouteBeginID,ClickID)==false)//首末相同或已有路径
			{				
				routelist.RemoveRoute(App_Veriable::RouteBeginID,0);//删除添加过的起点路径对象
				App_Veriable::RouteBeginID=0;//还原全局变量
				App_Veriable::IsAddingRoute=false;
				Invalidate();
			}
			else//找到终点，要传递id和权值！！！
			{
				CGuiderDoc* pDoc = GetDocument();

				Route * r=routelist.GetOfID (App_Veriable::RouteBeginID,0);//正在创建的最后路径

				int ClickID2=sitelist.OnSite(point.x,point.y);//获取ID
				Site* s=sitelist.GetOfID(ClickID2);//获取值是ID2的对象
				r->AddPoint(s->Position);//添加终点
				r->ID2=ClickID2;
				//添加权值（路径）到图
				double w=routelist.GetRouteLength(r->ID1,r->ID2);

				pDoc->graph_doc.inserte(r->ID1,r->ID2,w);

				App_Veriable::RouteBeginID=0;//还原全局变量
				App_Veriable::IsAddingRoute=false;

				Invalidate();
			}

		}
	}
	else//双击空白区域
	{
		if(App_Veriable::IsAddingRoute==true||App_Veriable::RouteBeginID!=0)//正在绘制路径
		{
			int ClickID2=this->WhetherOnPoint(point.x,point.y);
			CGuiderDoc* pDoc = GetDocument();


			if(ClickID2!=0)//点击静态点
			{
				if(pDoc->graph_doc.Link(App_Veriable::RouteBeginID,ClickID2)==false)//已有路径
				{
					routelist.RemoveRoute(App_Veriable::RouteBeginID,0);//删除添加过的起点路径对象
					App_Veriable::RouteBeginID=0;//还原全局变量
					App_Veriable::IsAddingRoute=false;
					Invalidate();
				}
				else
				{
					Route * r=routelist.GetOfID (App_Veriable::RouteBeginID,0);//正在创建的最后路径
					r->AddPoint(pDoc->points[-ClickID2-1]);//终点
					r->ID2=ClickID2;

					Site *s=new Site(pDoc->points[-ClickID2-1]);//创建地点副本，为了和动态点再求路径上保持兼容
					s->ID=ClickID2;
					sitelist.AddSite(s);//重绘时不绘制ID<0的点,区域函数跳过该点
					//添加权值（路径）到图
					double w=routelist.GetRouteLength(r->ID1,r->ID2);				

					pDoc->graph_doc.inserte(r->ID1,r->ID2,w);

					App_Veriable::RouteBeginID=0;//还原全局变量
					App_Veriable::IsAddingRoute=false;

					Invalidate();
				}
			}
			else 
			{
				Route * r=routelist.GetOfID (App_Veriable::RouteBeginID,0);//正在创建的不完整路径
				r->AddPoint(point);//添加折点
				Invalidate();
			}
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
}

//右键菜单
void CGuiderView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	//CMainFrame::m_bAutoMenuEnable=false;//不应该在这里，应该在它的构造里初始化

	////cstring   ss_test; 
	////cstring   ss_test1(""); 

	/////*ss_test.format("%d",point.x);   
	////ss_test1+=ss_test;
	////ss_test.format("%d",point.y);  
	////ss_test1+="+";
	////ss_test1+=ss_test;
	////afxmessagebox(ss_test1);  */

	//坐标转换
	CPoint p=point;
	this->ScreenToClient(&p);
	App_Veriable::RelativeContextMenuPos=p;//初始化菜单相对位置
	//转换后的坐标在p中
	if(App_Veriable::IsAddingRoute==false&&App_Veriable::ShortestRouteBeginID==0)//添加路径,寻找最短路径时候不再有菜单
	{
		CMenu popMenu;
		popMenu.LoadMenuW(IDR_MENU1);
		CMenu*pSubMenu=popMenu.GetSubMenu(0);

		if(sitelist.OnSite(p.x,p.y)==0&&routelist.OnRoute(p.x,p.y)==NULL)//点击空白
		{		
			pSubMenu->EnableMenuItem(ID_ADD_SITE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_ADD_ROUTE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_DELETE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_SHORTEST_ROUTE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_ATTRIBUTE,MF_GRAYED);
			//首先修改属性，再显示
		}
		else if(sitelist.OnSite(p.x,p.y)!=0)//点上
		{
			pSubMenu->EnableMenuItem(ID_ADD_SITE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_ADD_ROUTE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_DELETE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_SHORTEST_ROUTE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_ATTRIBUTE,MF_ENABLED);
		}
		else//线上
		{
			pSubMenu->EnableMenuItem(ID_ADD_SITE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_ADD_ROUTE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_DELETE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_SHORTEST_ROUTE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_ATTRIBUTE,MF_ENABLED);
		}
		pSubMenu->TrackPopupMenu (TPM_LEFTALIGN,point.x,point.y,pWnd);
	}
}

/////////////////////////////////////////////菜单项
//添加地点菜单
void CGuiderView::OnAddSite()
{
	// TODO: 在此添加命令处理程序代码
	CPoint p;
	if(App_Veriable::RelativeContextMenuPos.x==-1&&App_Veriable::RelativeContextMenuPos.y==-1)//没有菜单
	{
		//快捷键
		GetCursorPos(&p);
		this->ScreenToClient(&p);
	}
	else//有菜单
	{
		p=App_Veriable::RelativeContextMenuPos;		
	}
	Site * e=new Site(p);
	sitelist.AddSite(e);//此处应该返回ID供图使用

	CGuiderDoc* pDoc = GetDocument();
	pDoc->graph_doc.insertv(e->ID);//在图中插入地点

	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//还原菜单变量
	Invalidate();
}
//添加路径菜单，没有真正的添加有效路径，实际上在双击函数里才有可能添加！！！
void CGuiderView::OnAddRoute()
{
	// TODO: 在此添加命令处理程序代码
	int sp=sitelist.OnSite(App_Veriable::RelativeContextMenuPos.x,App_Veriable::RelativeContextMenuPos.y);//获取右击地点对象
	if(sp!=0)//点中
	{
		App_Veriable::IsAddingRoute=true;//通知程序要创建路径了
		App_Veriable::RouteBeginID=sp;

		Site* s=sitelist.GetOfID(sp);//获取ID值是sp的对象
		Route*r=new Route();//创建路径
		r->ID1=sp;//初始化起始端ID,终端ID为0！！！
		r->AddPoint(s->Position);//添加起点
		int id1,id2;
		routelist.AddRoute(r,id1,id2);//添加到路径链表

		CPoint q(-1,-1);
		App_Veriable::RelativeContextMenuPos=q;//还原菜单变量
		Invalidate();
	}
}

//删除菜单
void CGuiderView::OnDelete()
{
	// TODO: 在此添加命令处理程序代码
	CPoint p;
	if(App_Veriable::RelativeContextMenuPos.x==-1&&App_Veriable::RelativeContextMenuPos.y==-1)//没有菜单
	{
		//快捷键
		GetCursorPos(&p);
		this->ScreenToClient(&p);
	}
	/*if(App_Veriable::SelectedSiteID!=0)
	{
	sitelist.RemoveSite(App_Veriable::SelectedSiteID);
	routelist.RemoveRoutesOfSite(App_Veriable::RouteBeginID);
	}
	else if(App_Veriable::SelectedRouteID1!=0&&App_Veriable::SelectedRouteID2!=0)
	{
	routelist.RemoveRoute(App_Veriable::SelectedRouteID1,App_Veriable::SelectedRouteID2);
	}*/
	else//有菜单
	{
		p=App_Veriable::RelativeContextMenuPos;
	}

	int sp=sitelist.OnSite(p.x,p.y);//获取地点对象
	Route* rp=routelist.OnRoute(p.x,p.y);//获取路径对象
	if(sp!=0)//优先删除地点，同时删除路径！！！
	{
		sitelist.RemoveSite(sp);
		//添加删除边的代码
		routelist.RemoveRoutesOfSite(sp);
		//对图的等价操作
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.removev(sp);
	}
	else if(rp!=NULL)
	{
		CGuiderDoc* pDoc = GetDocument();		
		pDoc->graph_doc.removee(rp->ID1,rp->ID2);
		routelist.RemoveRoute(rp->ID1,rp->ID2);		
	}
	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//还原菜单变量
	Invalidate();
}

//刷新菜单
void CGuiderView::OnRefrash()
{
	// TODO: 在此添加命令处理程序代码
	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//还原菜单变量
	Invalidate();
}

//属性菜单
void CGuiderView::OnAttribute()
{
	// TODO: 在此添加命令处理程序代码
	CPoint p;
	if(App_Veriable::RelativeContextMenuPos.x==-1&&App_Veriable::RelativeContextMenuPos.y==-1)//没有菜单
	{
		//快捷键
		GetCursorPos(&p);
		this->ScreenToClient(&p);
	}
	else//有菜单
	{
		p=App_Veriable::RelativeContextMenuPos;	
	}
	int sp=sitelist.OnSite(p.x,p.y);//获取地点对象
	Route* rp=routelist.OnRoute(p.x,p.y);//获取路径对象
	if(sp!=0)//优先选中地点
	{
		Site * s=sitelist.GetOfID(sp);
		dlgDySiteAttr.DynamicSiteID=s->ID;

		CString s0;
		s0.Format(L"(%d,%d)",s->Position.x,s->Position.y);
		dlgDySiteAttr.DynamicSitePosition=s0;

		switch(s->Style)
		{
		case'C':s0.Format(L"圆");break;
		case'T':s0.Format(L"三角形");break;
		case'R':s0.Format(L"矩形");break;
		default:s0.Format(L"");break;
		}
		dlgDySiteAttr.DynamicSiteStyle=s0;

		dlgDySiteAttr.DynamicSiteColorR=GetRValue(s->Color);
		dlgDySiteAttr.DynamicSiteColorG=GetGValue(s->Color);
		dlgDySiteAttr.DynamicSiteColorB=GetBValue(s->Color);

		dlgDySiteAttr.DynamicSiteSize=s->Size;

		dlgDySiteAttr.DynamicSiteInfo=s->SiteInfo;

		dlgDySiteAttr.DoModal();
	}
	else if(rp!=NULL)
	{
		dlgDyRouteAttr.DynamicRouteID1=rp->ID1;
		Site * s=sitelist.GetOfID(rp->ID1);
		CString s1;
		s1.Format(L"(%d,%d)",s->Position.x,s->Position.y);
		dlgDyRouteAttr.DynamicRoutePosition1=s1;

		dlgDyRouteAttr.DynamicRouteID2=rp->ID2;
		s=sitelist.GetOfID(rp->ID2);
		s1.Format(L"(%d,%d)",s->Position.x,s->Position.y);
		dlgDyRouteAttr.DynamicRoutePosition2=s1;

		double l=routelist.GetRouteLength(rp->ID1,rp->ID2);
		l*=2.287;//长度系数
		s1.Format(_T("%.4f m"),l);
		dlgDyRouteAttr.DynamicRouteLength=s1;

		dlgDyRouteAttr.DynamicRouteWidth=rp->Width;

		dlgDyRouteAttr.DynamicRouteColorR=GetRValue(rp->Color);
		dlgDyRouteAttr.DynamicRouteColorG=GetGValue(rp->Color);
		dlgDyRouteAttr.DynamicRouteColorB=GetBValue(rp->Color);

		dlgDyRouteAttr.DynamicRouteInfo=rp->RouteInfo;


		dlgDyRouteAttr.DynamicRoutePointSize=rp->Points->size;

		dlgDyRouteAttr.DynamicRoutePointColorR=GetRValue(rp->Points->color);
		dlgDyRouteAttr.DynamicRoutePointColorG=GetGValue(rp->Points->color);
		dlgDyRouteAttr.DynamicRoutePointColorB=GetBValue(rp->Points->color);

		dlgDyRouteAttr.DoModal();
	}

	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//还原菜单变量
}


//左键按下，选中状态
void CGuiderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//还原菜单变量

	///////////////////////////////////////////////////////////////
	CPoint p=point;
	int sp=sitelist.OnSite(p.x,p.y);//获取地点对象
	Route* rp=routelist.OnRoute(p.x,p.y);//获取路径对象
	if(sp!=0)//优先选中地点
	{
		App_Veriable::LBDown=true;//左键状态,必须在选中地点时！！！

		Site* s=sitelist.GetOfID(sp);

		//记录信息
		App_Veriable::SiteInfoForMove=s->SiteInfo;
		s->SiteInfo=L"";//暂时不显示名字信息???


		App_Veriable::SelectedSiteID=sp;//初始化全局变量
		App_Veriable::SelectingSiteColor=s->Color;//初始化全局变量
		//还原路径的全局变量
		App_Veriable::SelectedRouteID1=0;//初始化全局变量
		App_Veriable::SelectedRouteID2=0;
		App_Veriable::SelectingRouteColor=RGB(-1,-1,-1);
		App_Veriable::SelectingRoutePointColor=RGB(-1,-1,-1);
		Invalidate();
	}
	else if(rp!=NULL)
	{
		//还原地点的全局变量
		App_Veriable::SelectedSiteID=0;//初始化全局变量
		App_Veriable::SelectingSiteColor=RGB(-1,-1,-1);//初始化全局变量
		App_Veriable::SelectedRouteID1=rp->ID1;//初始化全局变量
		App_Veriable::SelectedRouteID2=rp->ID2;
		App_Veriable::SelectingRouteColor=rp->Color;
		App_Veriable::SelectingRoutePointColor=rp->Points->color;
		Invalidate();
		//double len=routelist.GetRouteLength(rp->ID1,rp->ID2);
		//CString s;
		//s.Format("%f",len);			
		//AfxMessageBox(s);
	}
	else//单击空白
	{
		//if(!(App_Veriable::SelectedSiteID==0&&App_Veriable::SelectingSiteColor==RGB(-1,-1,-1)
		//	&&App_Veriable::SelectedRouteID1==0&&App_Veriable::SelectedRouteID2==0
		//	&&App_Veriable::SelectingRouteColor==RGB(-1,-1,-1)&&App_Veriable::SelectingRoutePointColor==RGB(-1,-1,-1)))
		//	Invalidate();//控制条件，减少刷新次数
		//else//还原地点的全局变量
		//{		
		CString inf("");
		/*if(App_Veriable::SiteInfoForMove!=inf&&App_Veriable::SiteInfoForMove!=App_Veriable::DefaultSiteInfo)
		{
			Site * s=sitelist.GetOfID(App_Veriable::SelectedSiteID);
			s->SiteInfo=App_Veriable::SiteInfoForMove;					
		}*/
		App_Veriable::SiteInfoForMove=L"";	
		App_Veriable::SelectedSiteID=0;//初始化全局变量
		App_Veriable::SelectingSiteColor=RGB(-1,-1,-1);//初始化全局变量
		//还原路径的全局变量
		App_Veriable::SelectedRouteID1=0;//初始化全局变量
		App_Veriable::SelectedRouteID2=0;
		App_Veriable::SelectingRouteColor=RGB(-1,-1,-1);
		App_Veriable::SelectingRoutePointColor=RGB(-1,-1,-1);		
		Invalidate();
		//}
	}
	CView::OnLButtonDown(nFlags, point);
}

//鼠标移动，移动对象
void CGuiderView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC*pDC=this->GetDC ();



	int i=0;//判断鼠标位置
	if(this->WhetherOnPoint (point.x ,point.y )!=0)  //点
		i=1;
	else if(this->WhetherOnRoad (point.x ,point.y ))   //边
		i=2;
	///////////////////////////////////////////////////////////////////////////
	int sp=sitelist.OnSite(point.x,point.y);
	Site * s=sitelist.GetOfID(sp);
	Route *rp=routelist.OnRoute(point.x,point.y);
	if(i==0)
	{		
		if(sp!=0)
			i=3;//是地点
		if(rp!=NULL)
			i=4;//是路径
	}


	/////////////////////////////////////////////////////////////
	//...........................................................修改状态栏-方案2-成功
	CString str,str1;
	switch(i)
	{
	case 0:str1.Format (L"新建地点...");break;
	case 1:str1.Format (L"路口");break;
	case 2:str1.Format (L"路  长度：%d",(int)this->length );break;
	case 3:str1.Format(L"%s",s->SiteInfo);break;
	case 4:
		double l=rp->Length();
		l*=2.287;
		str1.Format(L"%s 长度：%d",rp->RouteInfo,int(l));break;
	}
	str.Format (L"%d - %d  %s",point.x ,point.y,str1);
	CStatusBar * pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow (ID_VIEW_STATUS_BAR);
	pStatus->SetPaneText (0,str);
	//////////////////////////////////////////////////////////////
	if(App_Veriable::LBDown==true&&App_Veriable::IsAddingRoute==false)//添加路径不要移动，防止误删！！！
	{
		int i=routelist.RemoveRoutesOfSite(App_Veriable::SelectedSiteID);//删除周围路径
		if(i!=0)//既保证了移动之前的全屏刷新，又避免了无条件的Move刷新！
			Invalidate();
		//////////////////////////////////////////////删除一起系列的边的时候的处理方法////////////////////////////
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.removev(App_Veriable::SelectedSiteID);//删除点和周围的路径
		pDoc->graph_doc.insertv(App_Veriable::SelectedSiteID);//恢复删除的点

		Site*s=sitelist.GetOfID(App_Veriable::SelectedSiteID);//找鼠标按下的地点对象
		s->Position=point;
		
		//Invalidate();
		CRect rectOld(App_Veriable::LastMovePoint .x -s->Size ,App_Veriable::LastMovePoint .y -s->Size ,App_Veriable::LastMovePoint .x +s->Size ,App_Veriable::LastMovePoint .y +s->Size );
		this->InvalidateRect (rectOld);
		App_Veriable::LastMovePoint =point;
		CRect rectNew(App_Veriable::LastMovePoint .x -s->Size,App_Veriable::LastMovePoint .y -s->Size ,App_Veriable::LastMovePoint .x +s->Size,App_Veriable::LastMovePoint .y +s->Size);
		this->InvalidateRect (rectOld);
	}
	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}


//单击函数，控制全局变量
void CGuiderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	App_Veriable::LBDown=false;//左键状态
	CString inf("");
	if(App_Veriable::SiteInfoForMove!=inf)
	{
		Site * s=sitelist.GetOfID(App_Veriable::SelectedSiteID);
		s->SiteInfo=App_Veriable::SiteInfoForMove;
		App_Veriable::SiteInfoForMove=L"";
		Invalidate();
	}
	
	//////////////////////////////////////////////////////////////////////////
	if(App_Veriable::ShortestRouteBeginID!=0)
	{
		CGuiderDoc* pDoc = GetDocument();

		////////////////////////////////////////////////////////////先找出始终点的ID/////////////////////////////
		int id1=App_Veriable::ShortestRouteBeginID;
		int id2=WhetherOnPoint(point.x,point.y);//获取静态地点对象ID
		if(id2==0)
			id2=sitelist.OnSite(point.x,point.y);//后获取动态地点对象ID
		//意外情况,自己求自己！！！
		if(id1==id2||id2==0)
		{
			App_Veriable::ShortestRouteBeginID=0;
			return ;
		}

		///////////////////////////////////////////////////////////求最短路径/////////////////////////////////////
		int SiteID[100] ;//接收最短路径返回的参数{路径所经过的所有地点，以及数目}
		int SiteNum;		
		double ShortestLength=pDoc->graph_doc.shortpath(id1,id2,SiteID,SiteNum);

		/*SiteID[0]=1;
		SiteID[1]=-1;
		SiteID[2]=-2;
		SiteID[3]=2;
		SiteNum=4;
		ShortestLength=100;*/

		//数目的意外情况,没有路径返回0
		if(SiteNum==2&&ShortestLength==10000)
		{
			App_Veriable::ShortestRouteBeginID=0;
			return ;
		}
		///////////////////////////////////////////////////////////记录所有的折点////////////////////////////////
		CPoint pts[100];//记录路径上所有的折点(包含地点)
		int ptNum =0;//记录路径上所有的折点(包含地点)现有数目

		CPoint TempPt;//临时点

		//先记录第一点，保持循环一致
		if(SiteID[0]<0)
			TempPt=pDoc->points[-SiteID[0]-1];
		else 
		{
			Site * s=sitelist.GetOfID(SiteID[0]);
			TempPt=s->Position;
		}
		pts[0]=TempPt;
		ptNum++;

		for(int i=0;i<SiteNum-1;i++)
		{
			if(SiteID[i]<0&&SiteID[i+1]<0)//静态路径,总是记录路径的首点之后的点，保持一致
			{
				pts[ptNum]=pDoc->points[-SiteID[i+1]-1];
				ptNum++;
			}
			else
			{
				//接收动态路径返回的点数组，并将之链接到点数组上(除去头结点，数组下标从1开始)
				CPoint RoutePts[100];
				int RoutePtNum;
				Route*r=routelist.GetOfID(SiteID[i],SiteID[i+1]);
				r->ToPointArray(SiteID[i],SiteID[i+1],RoutePts,RoutePtNum);//顺序由参数决定
				//链接
				for(int j=1;j<RoutePtNum;j++)
				{
					pts[ptNum]=RoutePts[j];
					ptNum++;
				}
			}
		}
		/////////////////////////////////////////////////////////////根据数组做动画//////////////////////////////////////
		//添加绘制动画的代码;数组是CPoint pts[100];元素个数是ptNum;

		/*CString s;
		s.Format(L"所有点的个数是：%d x  %d %d %d %d %d %d",ptNum,pts[0].x,pts[1].x,pts[2].x,pts[3].x,pts[4].x,pts[5].x);
		AfxMessageBox(s);	*/	
		CDC * pDC=this->GetDC ();
		CPen pen;
		pen.CreatePen (PS_SOLID,2,RGB(this->dlgStaticAttribute .S_L_P_C_R ,this->dlgStaticAttribute .S_L_P_C_G ,this->dlgStaticAttribute .S_L_P_C_B ));
		pDC->SelectObject (pen);

		HDC hdc=pDC->GetSafeHdc ();
		CString str;
		//::SetBkMode(hdc,TRANSPARENT);
		::SetTextColor (hdc,RGB(255 ,255,0));
		::SetBkColor(hdc,RGB(0 ,0,255));

		CPoint current_point;  //动画起始点
		int move_Length;  //划线长度
		double all_Length=0;
		for(int i=0;i<ptNum-1;i++)
		{
			current_point=pts[i];
			move_Length=(int)sqrt(double(pts[i].x -pts[i+1].x )*(pts[i].x -pts[i+1].x )+double(pts[i].y -pts[i+1].y)*(pts[i].y -pts[i+1].y));
			for(int j=0;j<move_Length;j+=5)
			{
				current_point=pts[i]+CPoint((pts[i+1].x -pts[i].x)*j/move_Length ,(pts[i+1].y -pts[i].y)*j/move_Length);
				pDC->Ellipse (current_point.x-this->dlgStaticAttribute .S_L_P_W ,current_point.y -this->dlgStaticAttribute .S_L_P_W ,current_point.x+this->dlgStaticAttribute .S_L_P_W  ,current_point.y+this->dlgStaticAttribute .S_L_P_W );


				//if(move_Length-j<10)
				//{
				//	CRect rect(101,543,130,563);
				//	this->InvalidateRect (rect);
				//}

				all_Length+=2.287*5;
				str.Format (L"%d",(int)all_Length);
				pDC->TextOutW (pts[0].x+10 ,pts[0].y -5,str);


				Sleep((11-this->dlgStaticAttribute .S_L_S)*9 );
			}
		}
		ReleaseDC(pDC);
	}
	///////////////////////////////////////////////////////////////还原全局变量//////////////////////////////////////
	App_Veriable::ShortestRouteBeginID=0;


	//Invalidate();
	CView::OnLButtonUp(nFlags, point);
}
//右键按下，选中状态
void CGuiderView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnLButtonDown(nFlags,  point);
	App_Veriable::LBDown=false;//左键状态

	CView::OnRButtonDown(nFlags, point);
}



//求最短路径
void CGuiderView::OnShortestRoute()
{
	// TODO: 在此添加命令处理程序代码
	CPoint p=App_Veriable::RelativeContextMenuPos;
	App_Veriable::ShortestRouteBeginID=sitelist.OnSite(p.x,p.y);//获取地点对象ID

	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//还原菜单变量
}

void CGuiderView::OnStaticSet()
{
	// TODO: 在此添加命令处理程序代码
	dlgStaticAttribute.DoModal ();

	CDC *pDC=GetDC();
	CGuiderView::OnDraw (pDC);
	ReleaseDC(pDC);
}

void CGuiderView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	if(App_Veriable::FileIsSaved==false)
	{
		if(App_Veriable::FileOpenPathName==L"")
			OnFileSaveAs();
		else
		{
			CFile file(App_Veriable::FileOpenPathName,CFile::modeCreate | CFile::modeWrite|CFile::shareDenyNone);
			CArchive ar(&file,CArchive::store);
			App_Veriable::App_Save(ar);
			ar<<sitelist;
			ar<<routelist;
			App_Veriable::FileIsSaved=true;
		}
	}

}

void CGuiderView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	if((sitelist.Head!=NULL||routelist.Head!=NULL))//有操作
	{
		App_Veriable::FileOpenPathName=L"";
		if(App_Veriable::FileIsSaved==false)
		{
			if(IDOK==MessageBoxW(L"是否保存所做的更改？",L"Guider",1))
			{
				OnFileSave();
			}
		}

		sitelist.Destroy();
		routelist.Destroy();
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.Destroy();
		for(int i=0;i<64;i++)      //将点插入图中
			pDoc->graph_doc.insertv (-(i+1));
		pDoc->graph_doc .removev (-33);
		paint_road_point();

		Site::_ID_=0;//清空地点链表全局ID必须清0
		App_Veriable::FileIsSaved=false;
		Invalidate();
	}
}

void CGuiderView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if(sitelist.Head!=NULL||routelist.Head!=NULL)//有操作
	{
		CFileDialog fileDlg(FALSE);//创建 对话框。
		fileDlg.m_ofn.lpstrTitle= L"另存为";//标题栏
		fileDlg.m_ofn.lpstrFilter=L"Guider(*.gdr)\0\0所有文件(*.*)\0\0";
		fileDlg.m_ofn.lpstrDefExt=L"gdr";//保存文件格式。*.map*.*
		if(IDOK==fileDlg.DoModal())
		{
			App_Veriable::FileOpenPathName=fileDlg.GetPathName();
			CFile file(fileDlg.GetPathName(),CFile::modeCreate | CFile::modeWrite|CFile::shareDenyNone);
			CArchive ar(&file,CArchive::store);
			App_Veriable::App_Save(ar);
			ar<<sitelist;
			ar<<routelist;
			App_Veriable::FileIsSaved=true;
		}
	}
}

void CGuiderView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CGuiderDoc* pDoc = GetDocument();
	CFileDialog fileDlg(TRUE);//系统自带的对话框
	fileDlg.m_ofn.lpstrTitle=L"打开";
	fileDlg.m_ofn.lpstrFilter=L"Guider(*.gdr)\0\0所有文件(*.*)\0\0";
	fileDlg.m_ofn.lpstrDefExt=L"Guider";//自己定义的 文件格式
	if(IDOK==fileDlg.DoModal())//点击ok的时候 执行文件。//Map File(*.whd)\0*.map\0所有文件(*.*)\0*.*\0\0
	{
		sitelist.Destroy();
		routelist.Destroy();
		
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.Destroy();//清空图，不清空恢复静态操作！！！
		for(int i=0;i<64;i++)      //将点插入图中
			pDoc->graph_doc.insertv (-(i+1));
		pDoc->graph_doc .removev (-33);
		paint_road_point();

		//this->MyLine(

		Site::_ID_=0;//清空地点链表全局ID必须清0
		CFile file(fileDlg.GetPathName(),CFile::modeRead);
		App_Veriable::FileOpenPathName=fileDlg.GetPathName();
		CArchive ar(&file,CArchive::load);
		App_Veriable::App_Open(ar);
		sitelist.SiteListReadFile(ar,pDoc->graph_doc);
		routelist.RouteListReadFile(ar,pDoc->graph_doc);

		//App_Veriable::FileIsSaved=true;
	}
	Invalidate();
}

void CGuiderView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CString inf("");
	if(App_Veriable::SiteInfoForMove!=inf)
	{
		Site * s=sitelist.GetOfID(App_Veriable::SelectedSiteID);
		s->SiteInfo=App_Veriable::SiteInfoForMove;
		App_Veriable::SiteInfoForMove=L"";
		Invalidate();
	}
	CView::OnRButtonUp(nFlags, point);
}
