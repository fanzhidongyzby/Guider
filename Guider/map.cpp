#include "stdafx.h"
#include "map.h"
#include"app_veriable.h"
#include"Graph.h"

#include<cmath>


////////////////////////////////////////////////////////////////////////////地点//////////////////////////////////////// 


int Site::_ID_=0;//ID类外初始化

Site::Site()
{
	_ID_++;//创建对象，ID自加
	Next=NULL;
	ID=_ID_;//id复制
	Style=App_Veriable::DefaultSiteStyle;
	Color=App_Veriable::DefaultSiteColor;
	Size=App_Veriable::DefaultSiteSize;
	SiteInfo=App_Veriable::DefaultSiteInfo;
}

Site::Site(CPoint p)
{
	_ID_++;//创建对象，ID自加
	Next=NULL;
	ID=_ID_;
	Position=p;
	Style=App_Veriable::DefaultSiteStyle;
	Color=App_Veriable::DefaultSiteColor;
	Size=App_Veriable::DefaultSiteSize;
	SiteInfo=App_Veriable::DefaultSiteInfo;
}

Site::Site(int x,int y)
{
	CPoint p(x,y);
	_ID_++;//创建对象，ID自加
	Next=NULL;
	ID=_ID_;
	Position=p;
	Style=App_Veriable::DefaultSiteStyle;
	Color=App_Veriable::DefaultSiteColor;
	Size=App_Veriable::DefaultSiteSize;
	SiteInfo=App_Veriable::DefaultSiteInfo;
}
Site::Site(Site&s)//完全拷贝！！！
{
	Next=NULL;
	ID=s.ID;
	Position=s.Position;
	Style=s.Style;
	Color=s.Color;
	Size=s.Size;
	SiteInfo=s.SiteInfo;
}

void Site::Draw(CDC* pDC)
{	
	//设置TextOut的属性
	CFont   font;   
	LOGFONT   lf;   
	memset(&lf,   0,   sizeof(LOGFONT));   
	lf.lfHeight   =   15;         //字体的高   
	lf.lfWidth    =   8;         //字体宽
	font.CreateFontIndirect(&lf);
	pDC->SelectObject(&font);

	HDC hdc=pDC->GetSafeHdc ();
	::SetBkMode(hdc,TRANSPARENT);
	::SetTextColor (hdc,	RGB(255,255,0));
	if(ID>0)//只绘制动态点，静态点副本不绘制！
	{
		COLORREF c=RGB(255-GetRValue(Color)
			,255-GetGValue(Color)
			,255-GetBValue(Color));
		App_Veriable::DefaultSiteSeletedModeColor=c;
		CPen pen;
		if(ID==App_Veriable::SelectedSiteID)//选中的路径
		{
			pen.CreatePen (PS_SOLID,1,App_Veriable::DefaultSiteSeletedModeColor);
		}
		else
			pen.CreatePen (PS_SOLID,1,Color);
		pDC->SelectObject(pen);

		if(Style=='C')
			pDC->Ellipse(Position.x-Size/2,Position.y-Size/2,Position.x+Size/2,Position.y+Size/2);
		if(Style=='T')
		{
			pDC->MoveTo(Position.x,Position.y-sqrt(3.0)*Size/3);
			pDC->LineTo(Position.x-Size/2,Position.y+sqrt(3.0)*Size/6);

			pDC->MoveTo(Position.x-Size/2,Position.y+sqrt(3.0)*Size/6);
			pDC->LineTo(Position.x+Size/2,Position.y+sqrt(3.0)*Size/6);

			pDC->MoveTo(Position.x+Size/2,Position.y+sqrt(3.0)*Size/6);
			pDC->LineTo(Position.x,Position.y-sqrt(3.0)*Size/3);
		}
		if(Style=='R')
			pDC->Rectangle(Position.x-Size/2,Position.y-Size/2,Position.x+Size/2,Position.y+Size/2);

		pen.DeleteObject();

		CBrush brush;
		if(ID==App_Veriable::SelectedSiteID)//选中的路径
			brush.CreateSolidBrush (App_Veriable::DefaultSiteSeletedModeColor);
		else
			brush.CreateSolidBrush (Color);
		pDC->SelectObject(brush);

		if(Style=='C')
		{
			/*CRgn c;
			c.CreateEllipticRgn(Position.x-Size/2,Position.y-Size/2,Position.x+Size/2,Position.x+Size/2);
			pDC->FillRgn (&c,&brush);
			c.DeleteObject();*/
			pDC->Ellipse(Position.x-Size/2,Position.y-Size/2,Position.x+Size/2,Position.y+Size/2);//效果更好？？？
		}
		if(Style=='T')
		{
			CPoint points[3];
			points[0].x=Position.x;
			points[0].y=Position.y-sqrt(3.0)*Size/3;
			points[1].x=Position.x-Size/2;
			points[1].y=Position.y+sqrt(3.0)*Size/6;
			points[2].x=Position.x+Size/2;
			points[2].y=Position.y+sqrt(3.0)*Size/6;
			CRgn c;
			c.CreatePolygonRgn (points,3,WINDING);
			pDC->FillRgn (&c,&brush);
			c.DeleteObject();
		}
		if(Style=='R')
		{
			CRgn c;
			c.CreateRectRgn (Position.x-Size/2,Position.y-Size/2,Position.x+Size/2,Position.y+Size/2);
			pDC->FillRgn (&c,&brush);
			c.DeleteObject();
			/*pDC->Rectangle(Position.x-Size/2,Position.y-Size/2,Position.x+Size/2,Position.x+Size/2);*///不能用，好奇怪？？？
		}

		if(this->SiteInfo!=App_Veriable::DefaultSiteInfo&&App_Veriable::ShowSiteInfo)
			pDC->TextOutW(this->Position.x,this->Position.y,this->SiteInfo);

		brush.DeleteObject();
	}

}



bool Site::OnRegion(int x,int y)
{
	switch (Style)
	{
	case'C':
		int x0,y0;
		x0=Position.x;
		y0=Position.y;
		double r;
		r=sqrt((double)(x-x0)*(x-x0)+(y-y0)*(y-y0));
		if(r<=Size/2)
			return true;
	case'T':
		if(x>Position.x-Size/2&&x<Position.x+Size/2&&y>Position.y-sqrt(3.0)*Size/3&&y<Position.y+sqrt(3.0)*Size/6)//在矩形范围内
		{
			if(x>Position.x)
				x=2*Position.x-x;//右边对称向左转换
			double l;
			l=sqrt(3.0)*(x-Position.x +Size/2);
			if((Position.y+sqrt(3.0)*Size/6-y)<=l)
				return true;
		}
	case'R':
		if(x>(Position.x-Size/2)&&x<(Position.x+Size/2)&&y>(Position.y-Size/2)&&(y<Position.y+Size/2))
			return true;
	default:
		return false;
	}
}


CArchive & operator<<(CArchive&ar,Site & s)
{
	ar<<s.ID<<s.Color<<s.Position<<s.Size<<s.Style;
	return ar;
}

CArchive & operator>>(CArchive&ar,Site & s)
{
	ar>>s.ID>>s.Color>>s.Position>>s.Size>>s.Style;
	return ar;
}


////////////////////////////////////////////////////////////////////路径///////////////////////////////////////////

///////////////////////////////////////////////////////////////折点结构体
RoutePoint::RoutePoint(CPoint p)
{
	pos=p;
	size=App_Veriable::DefaultRoutePointSize;
	color=App_Veriable::DefaultRoutePointColor;
	next=NULL;
}
///////////////////////////////////////////////////////////////////////路径类

//Route()用于先初始化ID1，再初始化ID2，一般不要用！主要用于新创建路径
Route::Route()
{
	ID1=0;
	ID2=0;
	Next=NULL;

	Points=NULL;
	Color=App_Veriable::DefaultRouteColor;
	Width=App_Veriable::DefaultRouteWidth;
	RouteInfo=App_Veriable::DefaultRouteInfo;
}

Route::Route( Site * s1, Site * s2)
{
	ID1=s1->ID;
	ID2=s2->ID;
	Next=NULL;

	//Points=NULL;//忘记初始化为空了！！！
	//AddPoint(s1->Position);
	//AddPoint(s2->Position);
	Points=new RoutePoint(s1->Position);
	Points->next=new RoutePoint(s2->Position);

	Color=App_Veriable::DefaultRouteColor;
	Width=App_Veriable::DefaultRouteWidth;
	RouteInfo=App_Veriable::DefaultRouteInfo;
}


Route::Route(Route & r)
{
	ID1=r.ID1;	
	ID2=r.ID2;
	Next=NULL;

	//Points=NULL;//忘记初始化为空了！！！
	//AddPoint(s1->Position);
	//AddPoint(s2->Position);
	/*Points=new RoutePoint(s1->Position);
	Points->next=new RoutePoint(s2->Position);*/
	Points=NULL;

	RoutePoint * p;

	for(p=r.Points;p!=NULL;p=p->next)
	{
		this->AddPoint(p->pos);
		/*CString s;
		s.Format(L"%d %d ",p->pos.x,p->pos.y);
		AfxMessageBox(s);*/
	}
	

	Points->color=r.Points->color;
	Points->size=r.Points->size;//折点的属性

	Color=r.Color;
	Width=r.Width;
	RouteInfo=r.RouteInfo;
}

void Route::AddPoint(CPoint p)
{
	if(Points==NULL)//空链表
		Points=new RoutePoint(p);
	else if(Points->next==NULL)//单元素链表
		Points->next=new RoutePoint(p);
	else
	{
		RoutePoint*q,*r;
		//if(ID2==0)//无尾
		{
			for(q=Points;q->next!=NULL;q=q->next);
			//q指向尾节点
			q->next=new RoutePoint(p);//插入节点
			q=q->next;//向后指
			q->next=NULL;//指向尾节点
		}
		//if(ID2!=0)//有尾
		//{
		//	for(q=Points;q->next->next!=NULL;q=q->next);
		//	//q指向尾节点的前一个
		//	r=q->next;//记录尾节点
		//	q->next=new RoutePoint(p);//插入节点
		//	q=q->next;//向后指
		//	q->next=r;//还原尾节点
		//}
		//else
		//{
		//	
		//}
	}


}

void Route::AddPoint(int x,int y)
{
	CPoint p(x,y);
	AddPoint(p);
}

void Route::Destroy()
{
	RoutePoint * p;
	while(Points!=NULL)
	{
		p=Points;
		Points=Points->next;
		delete p;		
	}
}

Route::~Route()
{
	Destroy();
}

void Route::Draw(CDC*pDC)
{
	//设置TextOut的属性
	HDC hdc=pDC->GetSafeHdc ();
	::SetBkMode(hdc,TRANSPARENT);
	::SetTextColor (hdc,
		RGB(255-GetRValue(Color)
		,255-GetGValue(Color)
		,255-GetBValue(Color)));

	COLORREF c=RGB(255-GetRValue(Color)
		,255-GetGValue(Color)
		,255-GetBValue(Color));
	App_Veriable::DefaultRouteSeletedModeColor=c;

	COLORREF pc=RGB(255-GetRValue(Points->color)
		,255-GetGValue(Points->color)
		,255-GetBValue(Points->color));
	App_Veriable::DefaultRoutePointSeletedModeColor=pc;


	RoutePoint* p,*q;
	for(p=Points;p!=NULL;p=p->next)
	{
		CPen pen;
		if((p!=Points&&p->next!=NULL)||(ID2==0&&p!=Points))//首末不画的条件
		{ 
			if(ID1==App_Veriable::SelectedRouteID1&&ID2==App_Veriable::SelectedRouteID2)//选中的路径
				pen.CreatePen (PS_SOLID,1,App_Veriable::DefaultRoutePointSeletedModeColor);
			else
				pen.CreatePen (PS_SOLID,1,Points->color);
			pDC->SelectObject(pen);


			pDC->Ellipse(p->pos.x-Points->size/2,p->pos.y-Points->size/2,p->pos.x+Points->size/2,p->pos.y+Points->size/2);//绘制折点

			CBrush brush;

			if(ID1==App_Veriable::SelectedRouteID1&&ID2==App_Veriable::SelectedRouteID2)//选中的路径
				brush.CreateSolidBrush (App_Veriable::DefaultRoutePointSeletedModeColor);
			else
				brush.CreateSolidBrush (Points->color);
			pDC->SelectObject(brush);

			pDC->Ellipse(p->pos.x-Points->size/2,p->pos.y-Points->size/2,p->pos.x+Points->size/2,p->pos.y+Points->size/2);//填充折点

			pen.DeleteObject();
			brush.DeleteObject();	
		}

		q=p->next;
		if(q!=NULL)//有下一点
		{
			if(ID1==App_Veriable::SelectedRouteID1&&ID2==App_Veriable::SelectedRouteID2)//选中的路径
				pen.CreatePen (PS_SOLID,Width+1,App_Veriable::DefaultRouteSeletedModeColor);
			else
				pen.CreatePen (PS_SOLID,Width,Color);
			pDC->SelectObject(pen);

			/*CString s;
			int R=GetRValue(App_Veriable::DefaultRouteColor);
			int G=GetGValue(App_Veriable::DefaultRouteColor);
			int B=GetBValue(App_Veriable::DefaultRouteColor);
			s.Format(L"R=%d,G=%d,B=%d.",R,G,B);
			AfxMessageBox(s);*/
			pDC->MoveTo(p->pos);//绘制路径
			pDC->LineTo(q->pos);
			//若是第一道折线，显示该路径的长度
			if(App_Veriable::ShowRouteLength==true)
			{
				if(p==Points&&q==Points->next)//第一道折线
				{
					CString s;
					int l=2.287*Length();
					s.Format(L"%d",l);
					pDC->TextOutW ((p->pos.x+q->pos.x)/2,(p->pos.y+q->pos.y)/2,s);
				}
			}

			pen.DeleteObject();
		}
	}
}

bool Route::OnRegion(int x, int y)
{    
	RoutePoint* p,*q;

	if(Points==NULL||Points->next==NULL)//没有路径
		return false;

	for(p=Points;p->next!=NULL;p=p->next)
	{
		q=p->next;

		double x1, x2, y1, y2, d0, d1, d2, d3, x0, y0, ave;

		x1 = (double)p->pos.x;
		y1 = (double)p->pos.y;
		x2 = (double)q->pos.x;
		y2 = (double)q->pos.y;

		//点击坐标
		x0 = x;
		y0 = y;

		if ((x0 > x1 && x0 < x2) || (x0 > x2 && x0 < x1)|| (((x1=x2)||(x1>x2&&(x1-x2)<10)||(x1<x2&&(x2-x1)<10))&&(y0 > y1 && y0 < y2) || (y0 > y2 && y0 < y1)))//判断点击位置是否在范围以内
		{
			d1 = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));//点击位置到起点距离
			d2 = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));//点击位置到终点距离
			d3 = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));//直线距离
			ave = (d1 + d2 + d3) / 2;
			d0 = sqrt(ave * (ave - d1) * (ave - d2) * (ave - d3)) / d3;//点击位置到直线的距离

			if (d0 <= 2||d0<Width)
				return true;
		}
	}
	return false;//全部遍历没有返回
}


//求长度
double Route::Length()
{
	RoutePoint* p,*q;
	double len=0;//长度变量，初始化为0；

	if(Points==NULL||Points->next==NULL)//没有路径
		return 0;

	for(p=Points;p->next!=NULL;p=p->next)//有路径开始遍历
	{
		q=p->next;//找分段起始点

		double x1, x2, y1, y2;

		x1 = (double)p->pos.x;
		y1 = (double)p->pos.y;
		x2 = (double)q->pos.x;
		y2 = (double)q->pos.y;

		double l=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));//分段计算
		len+=l;
	}
	return len;		
}

void Route::ToPointArray(int id1, int id2,CPoint * pts,int &ptNum)//将链表转换为点数组
{
	RoutePoint * p;
	ptNum=0;//记录元素个数的变动

	for(p=Points;p!=NULL;p=p->next)
	{
		pts[ptNum]=p->pos;
		ptNum++;
	}
	if(ID1==id1&&ID2==id2)//正序
		return ;
	else if(ID1==id2&&ID2==id1)//逆序
	{	
		CPoint t;
		for(int i=0;i<ptNum/2;i++)
		{
			t=pts[i];
			pts[i]=pts[ptNum-i-1];
			pts[ptNum-i-1]=t;
		}
	}
}



CArchive & operator<<(CArchive&ar,Route & r)
{
	ar<<r.ID1<<r.ID2<<r.Color<<r.Width<<r.RouteInfo;//路径的基本属性
	RoutePoint * p;
	int rpNum=0;//记录元素个数的变动
	for(p=r.Points;p!=NULL;p=p->next)
		rpNum++;

	ar<<rpNum;
	
	for(p=r.Points;p!=NULL;p=p->next)
		ar<<p->pos;
	ar<<r.Points->color<<r.Points->size;//折点的属性
	return ar;
}

CArchive & operator>>(CArchive&ar,Route & r)
{
	//ar>>r.ID1>>r.ID2>>r.Color>>r.Width>>r.RouteInfo;//路径的基本属性
	//int rpNum;
	//ar>>rpNum;	

	//CPoint pt;
	//for(int i=0;i<rpNum;i++)
	//{
	//	ar>>pt;
	//	r.AddPoint(pt);
	//}
	//ar>>r.Points->color>>r.Points->size;//折点的属性
	
	return ar;
}

//////////////////////////////////////////////////////////////地点链表////////////////////////////////////////
SiteList::SiteList()
{
	Head=Tail=NULL;
}

void SiteList::Destroy()
{
	Site*p=Head;
	while(p!=NULL)
	{
		p=p->Next;
		delete Head;
		Head=p;
	}
}

SiteList::~SiteList()
{
	Destroy();
}

int SiteList::AddSite(Site * s)
{
	if(Head==NULL)//空链表
	{
		Head=Tail=s;
	}
	else
	{
		Tail->Next=s;
		Tail=Tail->Next;
	}
	return s->ID;;//返回添加节点的ID
}

int SiteList::RemoveSite(int id)
{
	Site*p;
	for(p=Head;p!=NULL;p=p->Next)//寻找id
	{
		if(p->ID==id||p->Next->ID==id)
			break;
		//第一种情况是头节点是目标点，其他情况均是提前一步锁定
		//只有选中的话才能激活删除函数，id值必然存在！不会出现意外的值
	}
	if(p->ID==id)//头结点
	{
		Head=Head->Next;
		delete p;
	}
	else if(p->Next->ID==id)
	{
		if(p->Next->Next==NULL)//千万不要忘记尾指针！！
		{
			Tail=p;//尾指针向前指
		}
		Site *q=p->Next;
		p->Next=q->Next;
		delete q;
	}
	return id;//将ID返回。使图的数据保持一致

}

void SiteList::Draw(CDC *pDC)
{
	Site*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		p->Draw(pDC);
	}
}

int SiteList::OnSite(int x, int y)
{
	Site*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		if(p->ID<=0)
			continue;//出现“无效”地点的时候跳过
		else if(p->OnRegion(x,y))
			return p->ID;
	}
	return 0;
}

// 获取参数id值的对象的指针
Site * SiteList::GetOfID(int id)
{
	Site*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		if(p->ID==id)
			return p;
	}
	return NULL;
}

// 将地点写入入文件
CArchive & operator<<(CArchive&ar,SiteList & s)
{
	Site*p;
	int SiteNum=0;
	for(p=s.Head;p!=NULL;p=p->Next)
	{
		SiteNum++;
	}
	ar<<SiteNum;

	for(p=s.Head;p!=NULL;p=p->Next)
	{
		ar<<*p;
	}
	return ar;
}

void SiteList::SiteListReadFile(CArchive&ar,Graph<int ,double> &g)
{
	Site*q;
	Site p;//_ID_会自加！！！
	Site::_ID_--;
	//q->_ID_=0;
	int SiteNum=0;

	ar>>SiteNum;

	for(int i=0;i<SiteNum;i++)
	{
		ar>>p;
		q=new Site(p);
		this->AddSite(q);//加入地点链表
		g.insertv(q->ID);
	}
}

//////////////////////////////////////////////////////////////路径链表////////////////////////////////////////
RouteList::RouteList()
{
	Head=Tail=NULL;
}
void RouteList::Destroy()
{
	Route*p=Head;
	while(p!=NULL)
	{
		p=p->Next;
		delete Head;
		Head=p;
	}
}

RouteList::~RouteList()
{
	Destroy();
}

void RouteList::AddRoute(Route * r ,int & id1,int & id2)
{
	if(Head==NULL)//空链表
	{
		Head=Tail= r ;
	}
	else
	{
		Tail->Next= r ;
		Tail=Tail->Next;
	}
	id1=r->ID1;
	id2=r->ID2;
}
void RouteList::RemoveRoute(int id1,int id2)
{
	Route*p;
	for(p=Head;p!=NULL;p=p->Next)//寻找id
	{
		if(p->ID1==id1&&p->ID2==id2||p->Next->ID1==id1&&p->Next->ID2==id2)
			break;
		//第一种情况是头节点是目标点，其他情况均是提前一步锁定
		//只有选中的话才能激活删除函数，id值必然存在！不会出现意外的值
	}
	if(p->ID1==id1&&p->ID2==id2)//头结点
	{
		Head=Head->Next;
		delete p;
	}
	else if(p->Next->ID1==id1&&p->Next->ID2==id2)
	{
		if(p->Next->Next==NULL)//千万不要忘记尾指针！！
		{
			Tail=p;//尾指针向前指
		}
		Route *q=p->Next;
		p->Next=q->Next;//p->Next,不能少啊！！！
		delete q;
	}
}

void RouteList::Draw(CDC *pDC)
{
	Route*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		p->Draw(pDC);
	}
}


// 是否在路径区域上
Route* RouteList::OnRoute(int x, int y)
{
	Route*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		if(p->OnRegion(x,y))
			return p;
	}
	return NULL;
}



// 由两个ID获取路径对象
Route * RouteList::GetOfID(int id1, int id2)
{
	Route*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		if(p->ID1==id1&&p->ID2==id2||p->ID1==id2&&p->ID2==id1)//既然是无向图，参数先后就无所谓了
			return p;
	}
	return NULL;
}

// 删除链接到id地点的上的所有路径,删除到边返回删除边的个数
int RouteList::RemoveRoutesOfSite(int id)
{
	int  Num=0;//记录删除边的个数
	Route*p,*q;
	if(Head==NULL)return Num ;
	for(p=Head,q=Head->Next;q!=NULL;)
	{
		if(q->ID1==id||q->ID2==id)//要删除的点
		{
			if(q->Next==NULL)//尾节点
			{
				Tail=p;
				delete q;
				Num++;
				p->Next=NULL;//此句不要忘记
				break;
			}
			else//普通结点
			{
				p->Next=q->Next;
				delete q;
				Num++;
				q=p->Next;
				continue;
			}
		}
		else
		{
			p=p->Next;
			q=q->Next;
		}
	}
	if(Head->ID1==id||Head->ID2==id)//头结点，必须最后删除！！！
	{
		p=Head;
		Head=Head->Next;
		delete p;
		Num++;
	}
	return Num;
}

// //求对应id的路径的长度，即权值
double RouteList::GetRouteLength(int id1, int id2)
{
	Route*p;
	for(p=Head;p!=NULL;p=p->Next)
	{
		if(p->ID1==id1&&p->ID2==id2)
			return p->Length();
	}
	return 0;
}

CArchive & operator<<(CArchive&ar,RouteList & rl)
{
	int RouteNum=0;
	Route*p;
	for(p=rl.Head;p!=NULL;p=p->Next)
	{
		RouteNum++;
	}
	ar<<RouteNum;

	for(p=rl.Head;p!=NULL;p=p->Next)
	{
		ar<<*p;
	}
	return ar;
}
void RouteList::RouteListReadFile(CArchive&ar,Graph<int ,double> &g)
{
	Route*q;
	//Route r;
	int RouteNum=0;  

	ar>>RouteNum;

	for(int i=0;i<RouteNum;i++)
	{
		//ar>>p;
		Route r;
		ar>>r.ID1>>r.ID2>>r.Color>>r.Width>>r.RouteInfo;//路径的基本属性
		int rpNum;
		ar>>rpNum;	

		CPoint pt;
		for(int i=0;i<rpNum;i++)
		{
			ar>>pt;
			r.AddPoint(pt);
		}
		ar>>r.Points->color>>r.Points->size;//折点的属性


		q=NULL;
		q=new Route(r);
		int id1,id2;
		this->AddRoute(q,id1,id2);
		g.inserte(q->ID1,q->ID2,q->Length());

	}
}


