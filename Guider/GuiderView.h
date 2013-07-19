// GuiderView.h : CGuiderView 类的接口
//


#pragma once

#include"map.h"
#include "GuiderDoc.h"
#include"Dlg_Dynamic_Site_Attribute.h"
#include"Dlg_Dynamic_Route_Attribute.h"
#include "Dlg_Static_Route_Attribute.h"

class CGuiderView : public CView
{
protected: // 仅从序列化创建
	CGuiderView();
	DECLARE_DYNCREATE(CGuiderView)

// 属性
public:
	CGuiderDoc* GetDocument() const;
	CBrush m_brushBackground;
	int p[4];  //画线时标注第几个点
	double length;  //记录对应边的长度

	//参数声明（解决闪烁问题）
	CBitmap* m_pOldBitmap;
	CBitmap* m_pMemBitmap; //声明内存中承载临时图象的位图
	CDC* m_pMemDC;   //声明用于缓冲作图的内存DC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//地点链表
	SiteList sitelist;
	//路径链表
	RouteList routelist;
///////////////////////////////////
	Dlg_Dynamic_Site_Attribute dlgDySiteAttr;//动态地点属性对话框
	Dlg_Dynamic_Route_Attribute dlgDyRouteAttr;//动态路径属性对话框
	Dlg_Static_Route_Attribute dlgStaticAttribute;

// 操作
public:
	void Draw ();//专门用于绘图的函数，代替OnDraw的职能！！！

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//bool OnEraseBkgnd(CDC* pDC);  //避免 背景闪烁

// 实现
public:
	virtual ~CGuiderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void paint_road_point();
	//  以CPoint的点集为基础绘制直线
	void MyLine(int num, int p0, int p1, int p2=0, int p3=0);
	// // 判断鼠标是否在边上，在的话返回true
	bool WhetherOnRoad(int poi_x, int poi_y);
	//  判断鼠标是否在点上
	int WhetherOnPoint(int poi_x, int poi_y);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnAddSite();
	afx_msg void OnAddRoute();
	afx_msg void OnDelete();
	afx_msg void OnRefrash();
	afx_msg void OnAttribute();


	afx_msg void OnShortestRoute();
	afx_msg void OnStaticSet();
	afx_msg void OnFileSave();
	afx_msg void OnFileNew();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GuiderView.cpp 中的调试版本
inline CGuiderDoc* CGuiderView::GetDocument() const
   { return reinterpret_cast<CGuiderDoc*>(m_pDocument); }
#endif

