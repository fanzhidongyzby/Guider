
#pragma once 
#include"Graph.h"
////////////////////////////////////////////////////////////////////////////�ص�//////////////////////////////////////// 
class Site
{
public:
	static int _ID_;//�ص�����ȫ��IDֵ[�����Ǿ�̬��������֤ID���ظ������캯�����Լӣ��ڸ��Ƶ�id]
	Site * Next;//����������

	int ID;//���������id
	CPoint Position;//����
	char Style;//��ʽ
	COLORREF Color;//��ɫ
	int Size;//��С
	CString SiteInfo;//�ص���Ϣ

	Site();
	Site(CPoint p);
	Site(int x,int y);
	Site(Site&s);//���ƹ��죬���ļ�ʱ������������
	void Draw(CDC* pDC);
	bool OnRegion(int x,int y);
	void SiteWriteFile(CString PathName);
	friend CArchive & operator<<(CArchive&ar,Site & s);
	friend CArchive & operator>>(CArchive&ar,Site & s);
};


////////////////////////////////////////////////////////////////////·��///////////////////////////////////////////

struct RoutePoint///////////////////////////////////////////////////////////////�۵�ṹ��
{
	CPoint pos;
	int size;
	COLORREF color;
	RoutePoint * next ;
	RoutePoint(CPoint p);
};


class Route///////////////////////////////////////////////////////////////////////·����
{
public:
	Route*Next;//����������
	int ID1;
	int ID2;//�����˵��ID

	RoutePoint * Points;//�����۵��������
	COLORREF Color;//��ɫ
	int Width;//���
	CString RouteInfo;//·����Ϣ

	Route();
	Route( Site * s1, Site * s2);
	Route(Route & r);
	~Route();
	void Destroy();//��������
	void AddPoint(CPoint p);//����һ��
	void AddPoint(int x,int y);//����һ��
	void Draw(CDC* pDC);
	bool OnRegion(int x,int y);
	double Length();//�󳤶�
	void ToPointArray(int id1, int id2,CPoint *pts,int &ptNum);//������ת��Ϊ������,id

	friend CArchive & operator<<(CArchive&ar,Route & r);
	friend CArchive & operator>>(CArchive&ar,Route & r);
};



//////////////////////////////////////////////////////////////�ص�����////////////////////////////////////////

class SiteList
{
public:
	Site*Head;//�ص������ͷָ��
	Site*Tail;//βָ��
	SiteList();
	~SiteList();
	int AddSite(Site * s);//�ڣ�x,y������ӵص�
	int RemoveSite(int id);//ɾ��IDֵ�ĵص�
	void Draw(CDC*pDC);//ͼ�λ���
	int OnSite(int x, int y);//�Ƿ����ڵص��ϣ����ڷ���0�����򷵻�ID
	// ��ȡ����idֵ�Ķ����ָ��
	Site * GetOfID(int id);

	void Destroy();
	// ���ص�д�����ļ�
	friend CArchive & operator<<(CArchive&ar,SiteList & sl);
	void SiteListReadFile(CArchive&ar,Graph<int ,double> &g);
};


//////////////////////////////////////////////////////////////·������////////////////////////////////////////

class RouteList
{
public:
	Route*Head;//·�������ͷָ��
	Route*Tail;//βָ��
	RouteList();
	~RouteList();
	void Destroy();
	void AddRoute(Route * r ,int & id1,int & id2);//���
	void RemoveRoute(int id1,int id2);//ɾ��ID1,2ֵ��·��
	void Draw(CDC*pDC);//ͼ�λ���	
	Route* OnRoute(int x, int y);// �Ƿ���·��������
	// ������ID��ȡ·������
	Route * GetOfID(int id1, int id2);
	// ɾ�����ӵ�id�ص���ϵ�����·��
	int RemoveRoutesOfSite(int id);
	// //���Ӧid��·���ĳ��ȣ���Ȩֵ
	double GetRouteLength(int id1, int id2);

	friend CArchive & operator<<(CArchive&ar,RouteList & rl);
	void RouteListReadFile(CArchive&ar,Graph<int ,double> &g);
};

