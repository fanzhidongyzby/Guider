
#pragma once 
#include"Graph.h"
////////////////////////////////////////////////////////////////////////////地点//////////////////////////////////////// 
class Site
{
public:
	static int _ID_;//地点对象的全局ID值[必须是静态变量！保证ID不重复，构造函数内自加，在复制到id]
	Site * Next;//供链表所用

	int ID;//对象自身的id
	CPoint Position;//坐标
	char Style;//样式
	COLORREF Color;//颜色
	int Size;//大小
	CString SiteInfo;//地点信息

	Site();
	Site(CPoint p);
	Site(int x,int y);
	Site(Site&s);//复制构造，读文件时拷贝对象所用
	void Draw(CDC* pDC);
	bool OnRegion(int x,int y);
	void SiteWriteFile(CString PathName);
	friend CArchive & operator<<(CArchive&ar,Site & s);
	friend CArchive & operator>>(CArchive&ar,Site & s);
};


////////////////////////////////////////////////////////////////////路径///////////////////////////////////////////

struct RoutePoint///////////////////////////////////////////////////////////////折点结构体
{
	CPoint pos;
	int size;
	COLORREF color;
	RoutePoint * next ;
	RoutePoint(CPoint p);
};


class Route///////////////////////////////////////////////////////////////////////路径类
{
public:
	Route*Next;//供链表所用
	int ID1;
	int ID2;//两个端点的ID

	RoutePoint * Points;//所有折点的链表集合
	COLORREF Color;//颜色
	int Width;//宽度
	CString RouteInfo;//路径信息

	Route();
	Route( Site * s1, Site * s2);
	Route(Route & r);
	~Route();
	void Destroy();//撤销操作
	void AddPoint(CPoint p);//增加一点
	void AddPoint(int x,int y);//增加一点
	void Draw(CDC* pDC);
	bool OnRegion(int x,int y);
	double Length();//求长度
	void ToPointArray(int id1, int id2,CPoint *pts,int &ptNum);//将链表转换为点数组,id

	friend CArchive & operator<<(CArchive&ar,Route & r);
	friend CArchive & operator>>(CArchive&ar,Route & r);
};



//////////////////////////////////////////////////////////////地点链表////////////////////////////////////////

class SiteList
{
public:
	Site*Head;//地点链表的头指针
	Site*Tail;//尾指针
	SiteList();
	~SiteList();
	int AddSite(Site * s);//在（x,y）处添加地点
	int RemoveSite(int id);//删除ID值的地点
	void Draw(CDC*pDC);//图形绘制
	int OnSite(int x, int y);//是否点击在地点上，不在返回0，否则返回ID
	// 获取参数id值的对象的指针
	Site * GetOfID(int id);

	void Destroy();
	// 将地点写入入文件
	friend CArchive & operator<<(CArchive&ar,SiteList & sl);
	void SiteListReadFile(CArchive&ar,Graph<int ,double> &g);
};


//////////////////////////////////////////////////////////////路径链表////////////////////////////////////////

class RouteList
{
public:
	Route*Head;//路径链表的头指针
	Route*Tail;//尾指针
	RouteList();
	~RouteList();
	void Destroy();
	void AddRoute(Route * r ,int & id1,int & id2);//添加
	void RemoveRoute(int id1,int id2);//删除ID1,2值的路径
	void Draw(CDC*pDC);//图形绘制	
	Route* OnRoute(int x, int y);// 是否在路径区域上
	// 由两个ID获取路径对象
	Route * GetOfID(int id1, int id2);
	// 删除链接到id地点的上的所有路径
	int RemoveRoutesOfSite(int id);
	// //求对应id的路径的长度，即权值
	double GetRouteLength(int id1, int id2);

	friend CArchive & operator<<(CArchive&ar,RouteList & rl);
	void RouteListReadFile(CArchive&ar,Graph<int ,double> &g);
};

