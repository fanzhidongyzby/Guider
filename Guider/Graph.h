#pragma once


#define defaultvertices 100
#define maxweight 10000
//#include<fstream.h>
//#include<stdlib.h>
#include <math.h>


template<class T,class E>
struct Edge  //边
{
	int dest;
	E cost;
	Edge<T,E> *link;
	Edge(){}
	Edge(int num,E weight)
	{
		dest=num;cost=weight;link=NULL;
	}
	
};

template<class T,class E>
//结点
struct vertex
{
	T data;//结点名称
	//CPoint po;
	Edge<T,E>*adj; //邻接表
};



template<class T,class E>
class Graph
{
public:

	Graph(int sz=defaultvertices);
    ~Graph();
	////对图进行读操作
	void create();
	//读取存储位置为i的节点的名称
    T getvalue(int i){return (i>=0&&i<numvertices)?nodetable[i].data:0;}
	
	E getw(T v1,T v2);         //读取两点之间边的权值
    int getnv(){return numvertices;}  //点的个数
	int getne(){return numEdges;}   //边的个数
	bool insertv(const T &v);       //插入点
	bool inserte(T v1,T v2,E cost);//插入边
	bool removev(T v);              //删除点
	bool removee(T v1,T v2);       //删除边

	void Destroy();
	
    //求最短路径//将最短路径返回，并以数组spath[]形式返回最短路径途经的个点
    double shortpath(T vv,T w0,T * spath,int &); 
	bool depth(Graph<T,E>&g,T v);//深度遍历
	bool depth(Graph<T,E>&g,int v,bool * visited);//深度遍历
	//给出点位置为v的第一个邻接点的位置 找不到时返回-1
	int getfirstneighbor(int v);
	//给出点位置为v的邻接点w的下一个邻接点的位置 没找到时返回-1
	int getnextneighbor(int v,int w);

	bool Link(T,T);
	
	int getvertexpos(T vertex)//名称为vertex的点在存储数组中的位置，
	{
		for(int i=0;i<numvertices;i++)
			if(nodetable[i].data==vertex)return i;//成功，则返回位置
		return -1;                                ///否则返回-1；
	}
private:
	vertex<T,E> *nodetable;  //存储点的数组
	int maxvertices;
	int numEdges;
	int numvertices;
//public:
//	CPoint point_te;  //用来比较的点
//	bool IfOnLine;  //判断某点是否在边上

	//double print(Graph<T,E>&g,T v,T w,T *spath,E dist[],int path[]);
	
	
};




template<class T,class E>
Graph<T,E>::Graph(int sz)
{
	maxvertices=sz;
	numvertices=0;
	numEdges=0;
	//point_te=CPoint(0,0);
	nodetable=new vertex<T,E>[maxvertices];
    //if(nodetable==NULL);//{cerr<<"存储分配错误"<<endl;exit(1);}
	for(int j=0;j<maxvertices;j++)
		nodetable[j].adj=NULL;
};


template<class T,class E>
Graph<T,E>::~Graph()
{
	Destroy();
	delete []nodetable;
};

template<class T,class E>
void Graph<T,E>:: Destroy()
{
	for(int i=0;i<numvertices;i++)
	{
		Edge<T,E> *p=nodetable[i].adj;
		while(p!=NULL)
		{
			nodetable[i].adj=p->link;
			delete p;
			p=nodetable[i].adj;
		}
	}
	numEdges=0;
	numvertices=0;
	delete [] nodetable;
	nodetable=new vertex<T,E>[maxvertices];
	for(int j=0;j<maxvertices;j++)
		nodetable[j].adj=NULL;

};

template<class T,class E>
E Graph<T,E>::getw(T n1,T n2)
{
	int v1=getvertexpos(n1);
	int v2=getvertexpos(n2);
	if(v1!=-1&&v2!=-1)
	{
		Edge<T,E> *p=nodetable[v1].adj;
		while(p!=NULL&&p->dest!=v2)
			p=p->link;
		if(p!=NULL)return p->cost;
	}
	return maxweight;
};

template<class T,class E>
bool Graph<T,E>::insertv(const T &v)  //插入顶点
{	
	if(numvertices==maxvertices)return false;
	nodetable[numvertices].data=v;
	numvertices++;
	return true;
};
template<class T,class E>
bool Graph<T,E>::inserte(T n1,T n2,E w)
{
	int v1=getvertexpos(n1);
	int v2=getvertexpos(n2);
    bool x=Link(n1,n2);
		if(x==true)
		{
			if(v1>=0&&v1<numvertices&&v2>=0&&v2<numvertices)
			{
				Edge<T,E> *q;
				Edge<T,E> *n;
				q=new Edge<T,E>;
				n=new Edge<T,E>;
				q->dest=v2;
				q->cost=w;
				q->link=nodetable[v1].adj;
				nodetable[v1].adj=q;
				n->dest=v1;
				n->cost=w;
				n->link=nodetable[v2].adj;
				nodetable[v2].adj=n;
				numEdges++;
				return true;
			}
		}
	return 0;
};
template<class T,class E>
bool Graph<T,E>::removev(T n)
{       
	int v=getvertexpos(n);
	if(v<0||v>=numvertices||numvertices==1)return false;
	Edge<T,E> *p;
    Edge<T,E>*q;
    Edge<T,E>*t;
	for(int i=0;i<numvertices;i++)
	{
		if(i==v)continue;
		q=nodetable[i].adj;
		while(q)
		{
			if(nodetable[i].adj->dest==v){nodetable[i].adj=nodetable[i].adj->link;numEdges--;break;}
			if(q->dest==v){t->link=q->link;delete q;numEdges--;break;}
			t=q;
			q=q->link;
		}
		
	}
	while(nodetable[v].adj)
	{
		p=nodetable[v].adj;
		nodetable[v].adj=p->link;
		delete p;
		numEdges--;
	}
	nodetable[v].adj=nodetable[numvertices-1].adj;
	nodetable[v]=nodetable[numvertices-1];
	numvertices--;
	return true;
};


template<class T,class E>
bool Graph<T,E>::removee(T n1,T n2)
{
	int v1=getvertexpos(n1);
	int v2=getvertexpos(n2);
	if(v1!=-1&&v2!=-1)
	{ 
		Edge<T,E>*q=NULL;
		Edge<T,E> *n=nodetable[v2].adj;
		Edge<T,E> *p=nodetable[v1].adj;
		if(p->dest==v2){nodetable[v1].adj=nodetable[v1].adj->link;delete p;}
		else
		{
			while(p&&p->dest!=v2)
			{
				q=p;
				p=p->link;
			}
			if(p)
			{
				q->link=p->link;
				
				delete p;
			}
		}
		if(n->dest==v1)
		{
			nodetable[v2].adj=nodetable[v2].adj->link;
			delete n;
		}
		else
		{
			while(n&&n->dest!=v1)
			{
				q=n;
				n=n->link;
			}
			if(n)
			{
				q->link=n->link;
	
				delete n;
			}
			
		}
		numEdges--;
		return true;
	}	
    return false;
};




template<class T,class E>
void Graph<T,E>::create()
{
	T term;
	T term1;
	T term2;
	E weig;
	ifstream infid("ID.txt",ios::in);//读取 ID 文件
	while(!infid.eof())
	{
		infid>>term;
		if(term!=0)insertv(term);
		
	}
	infid.close();
	
    ifstream infedge("Edge.txt",ios::in);//读取 边 文件
	while(!infedge.eof())
	{
		infedge>>term1>>term2>>weig;
		inserte(term1,term2,weig);
		
	}
	infedge.close();
};






template<class T,class E>
double Graph<T,E>::shortpath(T vv,T w0,T * spath,int & number )
{
	E dist[defaultvertices];
	int path[defaultvertices];
	int n=getnv();
	int v=getvertexpos(vv);
	bool *s=new bool[n];
	int i,j,k;
	E w,min;
	T zz;
	T x ;
	T aa;
	T yy;
	int bb=0;
	spath[bb++]=w0;
	for(i=0;i<n;i++)
	{  
		x=getvalue(i);
		dist[i]=getw(vv,x);//路径长度数组初始化
		s[i]=false;
		if(i!=v&&dist[i]<maxweight)path[i]=v;
		else path[i]=-1;
	}
	s[v]=true;
	dist[v]=0;
	int u=v;
	for(i=0;i<n-1;i++)
	{
		min=maxweight;
		for(j=0;j<n;j++)
			if(s[j]==false&&dist[j]<min){u=j;min=dist[j];}
		if(u==v)break;
		s[u]=true;
		
		for(k=0;k<n;k++)
		{
			zz=getvalue(k);
			aa=getvalue(u);
			w=getw(aa,zz);
			if(s[k]==false&&w<maxweight&&dist[u]+w<dist[k])
			{
				dist[k]=dist[u]+w;
				path[k]=u;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		x=getvalue(i);
		if(x==w0)
		{
			int j=path[i];
			while(j!=v&&j!=-1)
			{
				yy=getvalue(j);
				spath[bb++]=yy;
				j=path[j];
			}
			spath[bb++]=vv;
			number=bb;
			
			for(int k=0;k<number/2;k++)
			{
				T temp;
				temp=spath[k];
				spath[k]=spath[number-k-1];
				spath[number-k-1]=temp;
			}
			return dist[i];
		}        
	}	
};

template<class T,class E>
int Graph<T,E>::getfirstneighbor(int v)
{
	if(v!=-1)
	{
		Edge<T,E> *p=nodetable[v].adj;
		if(p!=NULL)
			return p->dest;
	}
	return -1;
};



template<class T,class E>
int Graph<T,E>::getnextneighbor(int v,int w)
{
	if(v!=-1)
	{	
		Edge<T,E> *p=nodetable[v].adj;
		while(p!=NULL&&p->dest!=w)
			p=p->link;
		if(p!=NULL&&p->link!=NULL)
		    return p->link->dest;
	}
	return -1;
};





template<class T,class E>
bool Graph<T,E>::depth(Graph<T,E>&g, T v)
{
	int i, loc, n=getnv(); 
	bool visited[100];
   	for(i=0; i<100;i++) visited[i]=false;					      
	loc=getvertexpos(v);
     return depth(g,loc,visited);
};



template<class T,class E>
bool Graph<T,E>::depth(Graph<T,E>&g ,int v,bool * visited)
{ 
	T a=g.getvalue(v);

	visited[v]=true;
	int w=g.getfirstneighbor(v);
	for(;w!=-1;)  
	{
		if(visited[w]==false)
		{
			//...................................................................................判断是否选中边
			//double x1, x2, y1, y2, d0, d1, d2, d3, x0, y0, ave;
			//x1 = (double)this->nodetable [v].po .x ;
			//y1 = (double)this->nodetable [v].po .y ;
			//x2 = (double)this->nodetable [w].po .x ;
			//y2 = (double)this->nodetable [w].po .y ;
			////点击坐标
			//x0 = this->point_te .x ;
			//y0 = this->point_te .y ;
			//if ((x0 > x1 && x0 < x2) || (x0 > x2 && x0 < x1))//判断点击位置是否在范围以内
			//{
			//	d1 = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));//点击位置到起点距离
			//	d2 = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));//点击位置到终点距离
			//	d3 = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));//直线距离
			//	ave = (d1 + d2 + d3) / 2;
			//	d0 = sqrt(ave * (ave - d1) * (ave - d2) * (ave - d3)) / d3;//点击位置到直线的距离
			//	if (d0 < 5) 
			//		Graph<T,E>::IfOnLine =true;		
			//}
			/////////////////////////////////////////////////////////////////////////////////////////
			//.....................状态栏－－－检验用--失败
			//CString str,str1;
			//str1.Format (L"爱生活，爱遍历");
			//str.Format (L"%d - %d   %s",x0,y0,str1);
			//CStatusBar * pStatus=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow (ID_VIEW_STATUS_BAR);
			//pStatus->SetPaneText (0,str);
			/////////////////////////////////////////////////////////////////////////////////////////


			depth(g,w,visited);
		}
		else
			w=g.getnextneighbor(v,w);
	}
	return false;

};

template<class T,class E>
bool Graph<T,E>::Link(T v,T w)
{
	int v1=getvertexpos(v);
	int v2=getvertexpos(w);
	//CString s;
	//s.Format(L"v1=%d,v2=%d",v1,v2);
	//AfxMessageBox(s);
	if(v1==v2)return false;
	Edge<T,E> *p;
	p=nodetable[v1].adj;
	while(p)
		if(p->dest==v2)return false;
		else p=p->link;
	return true;
};

