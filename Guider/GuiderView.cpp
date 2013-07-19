// GuiderView.cpp : CGuiderView ���ʵ��
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
	// ��׼��ӡ����
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

// CGuiderView ����/����

CGuiderView::CGuiderView()
{
	// TODO: �ڴ˴���ӹ������
	CBitmap bmp;
	//bmp.LoadBitmapW(IDB_BITMAP2); ///����λͼ
	bmp.LoadBitmapW (131);
	m_brushBackground.CreatePatternBrush(&bmp); ///����λͼ��ˢ
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGuiderView ����

void CGuiderView::OnDraw(CDC* pDC)
{

	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//..................................................................����
	CRect rect;
	GetClientRect(rect);///ȡ�ÿͻ�����
	pDC->FillRect(rect,&m_brushBackground); ///�ñ�����ˢ�������
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

// CGuiderView ��ӡ

BOOL CGuiderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGuiderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGuiderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CGuiderView ���

#ifdef _DEBUG
void CGuiderView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGuiderDoc* CGuiderView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGuiderDoc)));
	return (CGuiderDoc*)m_pDocument;
}
#endif //_DEBUG


// CGuiderView ��Ϣ�������
BOOL CGuiderView::OnEraseBkgnd(CDC* pDC)//���ⱳ������˸
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnEraseBkgnd(pDC);
	return true;
}
int CGuiderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	// TODO:  �ڴ������ר�õĴ�������
	//int x=GetSystemMetrics(SM_CXSCREEN);
	//int y=GetSystemMetrics(SM_CYSCREEN);
	//CDC* pDC=GetDC();
	//m_pMemDC->CreateCompatibleDC(pDC); //��������DC���������ڴ�DC
	//m_pMemBitmap->CreateCompatibleBitmap(pDC,x,y); //��������λͼ
	//m_pOldBitmap=m_pMemDC->SelectObject(m_pMemBitmap); //��λͼѡ���ڴ�DC,ԭλͼ���浽m_pOldBitmap
	//CBrush brush(RGB(255,255,255));
	//m_pMemDC->FillRect(CRect(0,0,x,y),&brush);    //���ÿͻ�������Ϊ��ɫ
	//ReleaseDC(pDC);

	return 0;
}
////////////////////////////////////////////////�Զ��庯��
void CGuiderView::paint_road_point()
{

	//..................��ȡָ��
	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC*pDC=this->GetDC ();
	//........................................����
	CPen pen; 
	CPen *oldPen; //A2 
	pen.CreatePen(PS_SOLID, this->dlgStaticAttribute .S_P_P_W ,RGB(this->dlgStaticAttribute .S_P_C_R ,this->dlgStaticAttribute .S_P_P_C_G ,this->dlgStaticAttribute .S_P_P_C_B /*attri.P_R_C ,attri.P_G_C ,attri.P_B_C*/ ));//B
	oldPen=pDC->SelectObject(&pen); //C
	////.........................................��ˢ
	//CBrush brush;
	//CBrush * oldBrush;
	//brush.CreateHatchBrush (5,RGB(255,255,0));
	//oldBrush=pDC->SelectObject (&brush);

	////ѡ�л�ˢ�����Ƶ�
	//pDC->SelectObject (brush); 
	for(int i=0;i<64;i++)
	{
		if(i==32)continue;
		else
			pDC->Ellipse (pDoc->points [i].x -4,pDoc->points [i].y -4,pDoc->points [i].x +4,pDoc->points [i].y +4);
	}

	////ѡ�л��ʣ����Ʊ�
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

//  ��CPoint�ĵ㼯Ϊ��������ֱ��
void CGuiderView::MyLine(int num, int p0, int p1, int p2, int p3)
{
	//..................��ȡָ��
	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC*pDC=this->GetDC ();
	//.....................��������
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
		pDC->MoveTo (pDoc->points [p[0]]);  //����
		pDC->LineTo  (pDoc->points[p[num]]);

		double length=sqrt((double)(pDoc->points [p[0]].x -pDoc->points[p[num]].x )*(pDoc->points [p[0]].x -pDoc->points[p[num]].x )+(double)((pDoc->points [p[0]].y -pDoc->points[p[num]].y )*(pDoc->points [p[0]].y -pDoc->points[p[num]].y )));
		length*=2.287;
		pDoc->graph_doc .inserte(-(p[0]+1),-(p[num]+1),length);  //��ӱ���ͼ

		if(this->dlgStaticAttribute .S_W_S_P_L )
		{
			str.Format (L"%d",(int)length);
			pDC->TextOutW ((pDoc->points [p[0]].x+pDoc->points[p[num]].x )/2,(pDoc->points [p[0]].y+pDoc->points[p[num]].y )/2,str);
		}

		pDoc->roads [pDoc->roadNum ].x =p[0];  //�����¼��
		pDoc->roads [pDoc->roadNum ].y =p[num];
		pDoc->roadNum ++;

		num--;  //��һ��
	}
	ReleaseDC(pDC);
}

// // �ж�����Ƿ��ڱ��ϣ��ڵĻ�����true
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
		//�������
		x0 = poi_x ;
		y0 = poi_y ;
		if ((x0 > x1 && x0 < x2) || (x0 > x2 && x0 < x1)  ||  (((x1=x2)||(x1>x2&&(x1-x2)<10)||(x1<x2&&(x2-x1)<10))&&(y0 > y1 && y0 < y2) || (y0 > y2 && y0 < y1)))//�жϵ��λ���Ƿ��ڷ�Χ����
		{
			d1 = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));//���λ�õ�������
			d2 = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));//���λ�õ��յ����
			d3  = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));//ֱ�߾���
			ave = (d1 + d2 + d3) / 2;
			d0 = sqrt(ave * (ave - d1) * (ave - d2) * (ave - d3)) / d3;//���λ�õ�ֱ�ߵľ���
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

//  �ж�����Ƿ��ڵ���
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
////////////////////////////////////////////////////�����Ӧ����



//˫�������·��
void CGuiderView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int ClickID=sitelist.OnSite(point.x,point.y);//��ȡID
	if(ClickID!=0)//˫���ص�,��·������
	{
		if(App_Veriable::IsAddingRoute==false&&App_Veriable::RouteBeginID==0)//û�л���·��
		{
			if(ClickID<0)return ;
			App_Veriable::IsAddingRoute=true;//��ʼ����·��
			App_Veriable::RouteBeginID=ClickID;//��ʼ�����ID
			Site* s=sitelist.GetOfID(ClickID);//��ȡֵ��ID�Ķ���
			Route*r=new Route();//����·��
			r->ID1=ClickID;//��ʼ����ʼ��ID,�ն�IDΪ0������
			r->AddPoint(s->Position);//������
			int id1,id2;
			routelist.AddRoute(r,id1,id2);//��ӵ�·������,����idӦ���ڳɹ�֮�󴫵�
			Invalidate();
		}
		else//���ڻ���·��
		{
			CGuiderDoc* pDoc = GetDocument();

			//bool Graph_Link=false;//���ʱ��graph.Link(int id1,int id2)//�ж������Ƿ��Ѿ�����

			if(App_Veriable::RouteBeginID==ClickID||pDoc->graph_doc.Link(App_Veriable::RouteBeginID,ClickID)==false)//��ĩ��ͬ������·��
			{				
				routelist.RemoveRoute(App_Veriable::RouteBeginID,0);//ɾ����ӹ������·������
				App_Veriable::RouteBeginID=0;//��ԭȫ�ֱ���
				App_Veriable::IsAddingRoute=false;
				Invalidate();
			}
			else//�ҵ��յ㣬Ҫ����id��Ȩֵ������
			{
				CGuiderDoc* pDoc = GetDocument();

				Route * r=routelist.GetOfID (App_Veriable::RouteBeginID,0);//���ڴ��������·��

				int ClickID2=sitelist.OnSite(point.x,point.y);//��ȡID
				Site* s=sitelist.GetOfID(ClickID2);//��ȡֵ��ID2�Ķ���
				r->AddPoint(s->Position);//����յ�
				r->ID2=ClickID2;
				//���Ȩֵ��·������ͼ
				double w=routelist.GetRouteLength(r->ID1,r->ID2);

				pDoc->graph_doc.inserte(r->ID1,r->ID2,w);

				App_Veriable::RouteBeginID=0;//��ԭȫ�ֱ���
				App_Veriable::IsAddingRoute=false;

				Invalidate();
			}

		}
	}
	else//˫���հ�����
	{
		if(App_Veriable::IsAddingRoute==true||App_Veriable::RouteBeginID!=0)//���ڻ���·��
		{
			int ClickID2=this->WhetherOnPoint(point.x,point.y);
			CGuiderDoc* pDoc = GetDocument();


			if(ClickID2!=0)//�����̬��
			{
				if(pDoc->graph_doc.Link(App_Veriable::RouteBeginID,ClickID2)==false)//����·��
				{
					routelist.RemoveRoute(App_Veriable::RouteBeginID,0);//ɾ����ӹ������·������
					App_Veriable::RouteBeginID=0;//��ԭȫ�ֱ���
					App_Veriable::IsAddingRoute=false;
					Invalidate();
				}
				else
				{
					Route * r=routelist.GetOfID (App_Veriable::RouteBeginID,0);//���ڴ��������·��
					r->AddPoint(pDoc->points[-ClickID2-1]);//�յ�
					r->ID2=ClickID2;

					Site *s=new Site(pDoc->points[-ClickID2-1]);//�����ص㸱����Ϊ�˺Ͷ�̬������·���ϱ��ּ���
					s->ID=ClickID2;
					sitelist.AddSite(s);//�ػ�ʱ������ID<0�ĵ�,�����������õ�
					//���Ȩֵ��·������ͼ
					double w=routelist.GetRouteLength(r->ID1,r->ID2);				

					pDoc->graph_doc.inserte(r->ID1,r->ID2,w);

					App_Veriable::RouteBeginID=0;//��ԭȫ�ֱ���
					App_Veriable::IsAddingRoute=false;

					Invalidate();
				}
			}
			else 
			{
				Route * r=routelist.GetOfID (App_Veriable::RouteBeginID,0);//���ڴ����Ĳ�����·��
				r->AddPoint(point);//����۵�
				Invalidate();
			}
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
}

//�Ҽ��˵�
void CGuiderView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	//CMainFrame::m_bAutoMenuEnable=false;//��Ӧ�������Ӧ�������Ĺ������ʼ��

	////cstring   ss_test; 
	////cstring   ss_test1(""); 

	/////*ss_test.format("%d",point.x);   
	////ss_test1+=ss_test;
	////ss_test.format("%d",point.y);  
	////ss_test1+="+";
	////ss_test1+=ss_test;
	////afxmessagebox(ss_test1);  */

	//����ת��
	CPoint p=point;
	this->ScreenToClient(&p);
	App_Veriable::RelativeContextMenuPos=p;//��ʼ���˵����λ��
	//ת�����������p��
	if(App_Veriable::IsAddingRoute==false&&App_Veriable::ShortestRouteBeginID==0)//���·��,Ѱ�����·��ʱ�����в˵�
	{
		CMenu popMenu;
		popMenu.LoadMenuW(IDR_MENU1);
		CMenu*pSubMenu=popMenu.GetSubMenu(0);

		if(sitelist.OnSite(p.x,p.y)==0&&routelist.OnRoute(p.x,p.y)==NULL)//����հ�
		{		
			pSubMenu->EnableMenuItem(ID_ADD_SITE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_ADD_ROUTE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_DELETE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_SHORTEST_ROUTE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_ATTRIBUTE,MF_GRAYED);
			//�����޸����ԣ�����ʾ
		}
		else if(sitelist.OnSite(p.x,p.y)!=0)//����
		{
			pSubMenu->EnableMenuItem(ID_ADD_SITE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_ADD_ROUTE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_DELETE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_SHORTEST_ROUTE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_ATTRIBUTE,MF_ENABLED);
		}
		else//����
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

/////////////////////////////////////////////�˵���
//��ӵص�˵�
void CGuiderView::OnAddSite()
{
	// TODO: �ڴ���������������
	CPoint p;
	if(App_Veriable::RelativeContextMenuPos.x==-1&&App_Veriable::RelativeContextMenuPos.y==-1)//û�в˵�
	{
		//��ݼ�
		GetCursorPos(&p);
		this->ScreenToClient(&p);
	}
	else//�в˵�
	{
		p=App_Veriable::RelativeContextMenuPos;		
	}
	Site * e=new Site(p);
	sitelist.AddSite(e);//�˴�Ӧ�÷���ID��ͼʹ��

	CGuiderDoc* pDoc = GetDocument();
	pDoc->graph_doc.insertv(e->ID);//��ͼ�в���ص�

	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����
	Invalidate();
}
//���·���˵���û�������������Ч·����ʵ������˫����������п�����ӣ�����
void CGuiderView::OnAddRoute()
{
	// TODO: �ڴ���������������
	int sp=sitelist.OnSite(App_Veriable::RelativeContextMenuPos.x,App_Veriable::RelativeContextMenuPos.y);//��ȡ�һ��ص����
	if(sp!=0)//����
	{
		App_Veriable::IsAddingRoute=true;//֪ͨ����Ҫ����·����
		App_Veriable::RouteBeginID=sp;

		Site* s=sitelist.GetOfID(sp);//��ȡIDֵ��sp�Ķ���
		Route*r=new Route();//����·��
		r->ID1=sp;//��ʼ����ʼ��ID,�ն�IDΪ0������
		r->AddPoint(s->Position);//������
		int id1,id2;
		routelist.AddRoute(r,id1,id2);//��ӵ�·������

		CPoint q(-1,-1);
		App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����
		Invalidate();
	}
}

//ɾ���˵�
void CGuiderView::OnDelete()
{
	// TODO: �ڴ���������������
	CPoint p;
	if(App_Veriable::RelativeContextMenuPos.x==-1&&App_Veriable::RelativeContextMenuPos.y==-1)//û�в˵�
	{
		//��ݼ�
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
	else//�в˵�
	{
		p=App_Veriable::RelativeContextMenuPos;
	}

	int sp=sitelist.OnSite(p.x,p.y);//��ȡ�ص����
	Route* rp=routelist.OnRoute(p.x,p.y);//��ȡ·������
	if(sp!=0)//����ɾ���ص㣬ͬʱɾ��·��������
	{
		sitelist.RemoveSite(sp);
		//���ɾ���ߵĴ���
		routelist.RemoveRoutesOfSite(sp);
		//��ͼ�ĵȼ۲���
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
	App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����
	Invalidate();
}

//ˢ�²˵�
void CGuiderView::OnRefrash()
{
	// TODO: �ڴ���������������
	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����
	Invalidate();
}

//���Բ˵�
void CGuiderView::OnAttribute()
{
	// TODO: �ڴ���������������
	CPoint p;
	if(App_Veriable::RelativeContextMenuPos.x==-1&&App_Veriable::RelativeContextMenuPos.y==-1)//û�в˵�
	{
		//��ݼ�
		GetCursorPos(&p);
		this->ScreenToClient(&p);
	}
	else//�в˵�
	{
		p=App_Veriable::RelativeContextMenuPos;	
	}
	int sp=sitelist.OnSite(p.x,p.y);//��ȡ�ص����
	Route* rp=routelist.OnRoute(p.x,p.y);//��ȡ·������
	if(sp!=0)//����ѡ�еص�
	{
		Site * s=sitelist.GetOfID(sp);
		dlgDySiteAttr.DynamicSiteID=s->ID;

		CString s0;
		s0.Format(L"(%d,%d)",s->Position.x,s->Position.y);
		dlgDySiteAttr.DynamicSitePosition=s0;

		switch(s->Style)
		{
		case'C':s0.Format(L"Բ");break;
		case'T':s0.Format(L"������");break;
		case'R':s0.Format(L"����");break;
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
		l*=2.287;//����ϵ��
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
	App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����
}


//������£�ѡ��״̬
void CGuiderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����

	///////////////////////////////////////////////////////////////
	CPoint p=point;
	int sp=sitelist.OnSite(p.x,p.y);//��ȡ�ص����
	Route* rp=routelist.OnRoute(p.x,p.y);//��ȡ·������
	if(sp!=0)//����ѡ�еص�
	{
		App_Veriable::LBDown=true;//���״̬,������ѡ�еص�ʱ������

		Site* s=sitelist.GetOfID(sp);

		//��¼��Ϣ
		App_Veriable::SiteInfoForMove=s->SiteInfo;
		s->SiteInfo=L"";//��ʱ����ʾ������Ϣ???


		App_Veriable::SelectedSiteID=sp;//��ʼ��ȫ�ֱ���
		App_Veriable::SelectingSiteColor=s->Color;//��ʼ��ȫ�ֱ���
		//��ԭ·����ȫ�ֱ���
		App_Veriable::SelectedRouteID1=0;//��ʼ��ȫ�ֱ���
		App_Veriable::SelectedRouteID2=0;
		App_Veriable::SelectingRouteColor=RGB(-1,-1,-1);
		App_Veriable::SelectingRoutePointColor=RGB(-1,-1,-1);
		Invalidate();
	}
	else if(rp!=NULL)
	{
		//��ԭ�ص��ȫ�ֱ���
		App_Veriable::SelectedSiteID=0;//��ʼ��ȫ�ֱ���
		App_Veriable::SelectingSiteColor=RGB(-1,-1,-1);//��ʼ��ȫ�ֱ���
		App_Veriable::SelectedRouteID1=rp->ID1;//��ʼ��ȫ�ֱ���
		App_Veriable::SelectedRouteID2=rp->ID2;
		App_Veriable::SelectingRouteColor=rp->Color;
		App_Veriable::SelectingRoutePointColor=rp->Points->color;
		Invalidate();
		//double len=routelist.GetRouteLength(rp->ID1,rp->ID2);
		//CString s;
		//s.Format("%f",len);			
		//AfxMessageBox(s);
	}
	else//�����հ�
	{
		//if(!(App_Veriable::SelectedSiteID==0&&App_Veriable::SelectingSiteColor==RGB(-1,-1,-1)
		//	&&App_Veriable::SelectedRouteID1==0&&App_Veriable::SelectedRouteID2==0
		//	&&App_Veriable::SelectingRouteColor==RGB(-1,-1,-1)&&App_Veriable::SelectingRoutePointColor==RGB(-1,-1,-1)))
		//	Invalidate();//��������������ˢ�´���
		//else//��ԭ�ص��ȫ�ֱ���
		//{		
		CString inf("");
		/*if(App_Veriable::SiteInfoForMove!=inf&&App_Veriable::SiteInfoForMove!=App_Veriable::DefaultSiteInfo)
		{
			Site * s=sitelist.GetOfID(App_Veriable::SelectedSiteID);
			s->SiteInfo=App_Veriable::SiteInfoForMove;					
		}*/
		App_Veriable::SiteInfoForMove=L"";	
		App_Veriable::SelectedSiteID=0;//��ʼ��ȫ�ֱ���
		App_Veriable::SelectingSiteColor=RGB(-1,-1,-1);//��ʼ��ȫ�ֱ���
		//��ԭ·����ȫ�ֱ���
		App_Veriable::SelectedRouteID1=0;//��ʼ��ȫ�ֱ���
		App_Veriable::SelectedRouteID2=0;
		App_Veriable::SelectingRouteColor=RGB(-1,-1,-1);
		App_Veriable::SelectingRoutePointColor=RGB(-1,-1,-1);		
		Invalidate();
		//}
	}
	CView::OnLButtonDown(nFlags, point);
}

//����ƶ����ƶ�����
void CGuiderView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	

	CGuiderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC*pDC=this->GetDC ();



	int i=0;//�ж����λ��
	if(this->WhetherOnPoint (point.x ,point.y )!=0)  //��
		i=1;
	else if(this->WhetherOnRoad (point.x ,point.y ))   //��
		i=2;
	///////////////////////////////////////////////////////////////////////////
	int sp=sitelist.OnSite(point.x,point.y);
	Site * s=sitelist.GetOfID(sp);
	Route *rp=routelist.OnRoute(point.x,point.y);
	if(i==0)
	{		
		if(sp!=0)
			i=3;//�ǵص�
		if(rp!=NULL)
			i=4;//��·��
	}


	/////////////////////////////////////////////////////////////
	//...........................................................�޸�״̬��-����2-�ɹ�
	CString str,str1;
	switch(i)
	{
	case 0:str1.Format (L"�½��ص�...");break;
	case 1:str1.Format (L"·��");break;
	case 2:str1.Format (L"·  ���ȣ�%d",(int)this->length );break;
	case 3:str1.Format(L"%s",s->SiteInfo);break;
	case 4:
		double l=rp->Length();
		l*=2.287;
		str1.Format(L"%s ���ȣ�%d",rp->RouteInfo,int(l));break;
	}
	str.Format (L"%d - %d  %s",point.x ,point.y,str1);
	CStatusBar * pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow (ID_VIEW_STATUS_BAR);
	pStatus->SetPaneText (0,str);
	//////////////////////////////////////////////////////////////
	if(App_Veriable::LBDown==true&&App_Veriable::IsAddingRoute==false)//���·����Ҫ�ƶ�����ֹ��ɾ������
	{
		int i=routelist.RemoveRoutesOfSite(App_Veriable::SelectedSiteID);//ɾ����Χ·��
		if(i!=0)//�ȱ�֤���ƶ�֮ǰ��ȫ��ˢ�£��ֱ�������������Moveˢ�£�
			Invalidate();
		//////////////////////////////////////////////ɾ��һ��ϵ�еıߵ�ʱ��Ĵ�����////////////////////////////
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.removev(App_Veriable::SelectedSiteID);//ɾ�������Χ��·��
		pDoc->graph_doc.insertv(App_Veriable::SelectedSiteID);//�ָ�ɾ���ĵ�

		Site*s=sitelist.GetOfID(App_Veriable::SelectedSiteID);//����갴�µĵص����
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


//��������������ȫ�ֱ���
void CGuiderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	App_Veriable::LBDown=false;//���״̬
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

		////////////////////////////////////////////////////////////���ҳ�ʼ�յ��ID/////////////////////////////
		int id1=App_Veriable::ShortestRouteBeginID;
		int id2=WhetherOnPoint(point.x,point.y);//��ȡ��̬�ص����ID
		if(id2==0)
			id2=sitelist.OnSite(point.x,point.y);//���ȡ��̬�ص����ID
		//�������,�Լ����Լ�������
		if(id1==id2||id2==0)
		{
			App_Veriable::ShortestRouteBeginID=0;
			return ;
		}

		///////////////////////////////////////////////////////////�����·��/////////////////////////////////////
		int SiteID[100] ;//�������·�����صĲ���{·�������������еص㣬�Լ���Ŀ}
		int SiteNum;		
		double ShortestLength=pDoc->graph_doc.shortpath(id1,id2,SiteID,SiteNum);

		/*SiteID[0]=1;
		SiteID[1]=-1;
		SiteID[2]=-2;
		SiteID[3]=2;
		SiteNum=4;
		ShortestLength=100;*/

		//��Ŀ���������,û��·������0
		if(SiteNum==2&&ShortestLength==10000)
		{
			App_Veriable::ShortestRouteBeginID=0;
			return ;
		}
		///////////////////////////////////////////////////////////��¼���е��۵�////////////////////////////////
		CPoint pts[100];//��¼·�������е��۵�(�����ص�)
		int ptNum =0;//��¼·�������е��۵�(�����ص�)������Ŀ

		CPoint TempPt;//��ʱ��

		//�ȼ�¼��һ�㣬����ѭ��һ��
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
			if(SiteID[i]<0&&SiteID[i+1]<0)//��̬·��,���Ǽ�¼·�����׵�֮��ĵ㣬����һ��
			{
				pts[ptNum]=pDoc->points[-SiteID[i+1]-1];
				ptNum++;
			}
			else
			{
				//���ն�̬·�����صĵ����飬����֮���ӵ���������(��ȥͷ��㣬�����±��1��ʼ)
				CPoint RoutePts[100];
				int RoutePtNum;
				Route*r=routelist.GetOfID(SiteID[i],SiteID[i+1]);
				r->ToPointArray(SiteID[i],SiteID[i+1],RoutePts,RoutePtNum);//˳���ɲ�������
				//����
				for(int j=1;j<RoutePtNum;j++)
				{
					pts[ptNum]=RoutePts[j];
					ptNum++;
				}
			}
		}
		/////////////////////////////////////////////////////////////��������������//////////////////////////////////////
		//��ӻ��ƶ����Ĵ���;������CPoint pts[100];Ԫ�ظ�����ptNum;

		/*CString s;
		s.Format(L"���е�ĸ����ǣ�%d x  %d %d %d %d %d %d",ptNum,pts[0].x,pts[1].x,pts[2].x,pts[3].x,pts[4].x,pts[5].x);
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

		CPoint current_point;  //������ʼ��
		int move_Length;  //���߳���
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
	///////////////////////////////////////////////////////////////��ԭȫ�ֱ���//////////////////////////////////////
	App_Veriable::ShortestRouteBeginID=0;


	//Invalidate();
	CView::OnLButtonUp(nFlags, point);
}
//�Ҽ����£�ѡ��״̬
void CGuiderView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnLButtonDown(nFlags,  point);
	App_Veriable::LBDown=false;//���״̬

	CView::OnRButtonDown(nFlags, point);
}



//�����·��
void CGuiderView::OnShortestRoute()
{
	// TODO: �ڴ���������������
	CPoint p=App_Veriable::RelativeContextMenuPos;
	App_Veriable::ShortestRouteBeginID=sitelist.OnSite(p.x,p.y);//��ȡ�ص����ID

	CPoint q(-1,-1);
	App_Veriable::RelativeContextMenuPos=q;//��ԭ�˵�����
}

void CGuiderView::OnStaticSet()
{
	// TODO: �ڴ���������������
	dlgStaticAttribute.DoModal ();

	CDC *pDC=GetDC();
	CGuiderView::OnDraw (pDC);
	ReleaseDC(pDC);
}

void CGuiderView::OnFileSave()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	if((sitelist.Head!=NULL||routelist.Head!=NULL))//�в���
	{
		App_Veriable::FileOpenPathName=L"";
		if(App_Veriable::FileIsSaved==false)
		{
			if(IDOK==MessageBoxW(L"�Ƿ񱣴������ĸ��ģ�",L"Guider",1))
			{
				OnFileSave();
			}
		}

		sitelist.Destroy();
		routelist.Destroy();
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.Destroy();
		for(int i=0;i<64;i++)      //�������ͼ��
			pDoc->graph_doc.insertv (-(i+1));
		pDoc->graph_doc .removev (-33);
		paint_road_point();

		Site::_ID_=0;//��յص�����ȫ��ID������0
		App_Veriable::FileIsSaved=false;
		Invalidate();
	}
}

void CGuiderView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if(sitelist.Head!=NULL||routelist.Head!=NULL)//�в���
	{
		CFileDialog fileDlg(FALSE);//���� �Ի���
		fileDlg.m_ofn.lpstrTitle= L"���Ϊ";//������
		fileDlg.m_ofn.lpstrFilter=L"Guider(*.gdr)\0\0�����ļ�(*.*)\0\0";
		fileDlg.m_ofn.lpstrDefExt=L"gdr";//�����ļ���ʽ��*.map*.*
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
	// TODO: �ڴ���������������
	CGuiderDoc* pDoc = GetDocument();
	CFileDialog fileDlg(TRUE);//ϵͳ�Դ��ĶԻ���
	fileDlg.m_ofn.lpstrTitle=L"��";
	fileDlg.m_ofn.lpstrFilter=L"Guider(*.gdr)\0\0�����ļ�(*.*)\0\0";
	fileDlg.m_ofn.lpstrDefExt=L"Guider";//�Լ������ �ļ���ʽ
	if(IDOK==fileDlg.DoModal())//���ok��ʱ�� ִ���ļ���//Map File(*.whd)\0*.map\0�����ļ�(*.*)\0*.*\0\0
	{
		sitelist.Destroy();
		routelist.Destroy();
		
		CGuiderDoc* pDoc = GetDocument();
		pDoc->graph_doc.Destroy();//���ͼ������ջָ���̬����������
		for(int i=0;i<64;i++)      //�������ͼ��
			pDoc->graph_doc.insertv (-(i+1));
		pDoc->graph_doc .removev (-33);
		paint_road_point();

		//this->MyLine(

		Site::_ID_=0;//��յص�����ȫ��ID������0
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
