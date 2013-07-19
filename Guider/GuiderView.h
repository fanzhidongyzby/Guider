// GuiderView.h : CGuiderView ��Ľӿ�
//


#pragma once

#include"map.h"
#include "GuiderDoc.h"
#include"Dlg_Dynamic_Site_Attribute.h"
#include"Dlg_Dynamic_Route_Attribute.h"
#include "Dlg_Static_Route_Attribute.h"

class CGuiderView : public CView
{
protected: // �������л�����
	CGuiderView();
	DECLARE_DYNCREATE(CGuiderView)

// ����
public:
	CGuiderDoc* GetDocument() const;
	CBrush m_brushBackground;
	int p[4];  //����ʱ��ע�ڼ�����
	double length;  //��¼��Ӧ�ߵĳ���

	//���������������˸���⣩
	CBitmap* m_pOldBitmap;
	CBitmap* m_pMemBitmap; //�����ڴ��г�����ʱͼ���λͼ
	CDC* m_pMemDC;   //�������ڻ�����ͼ���ڴ�DC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�ص�����
	SiteList sitelist;
	//·������
	RouteList routelist;
///////////////////////////////////
	Dlg_Dynamic_Site_Attribute dlgDySiteAttr;//��̬�ص����ԶԻ���
	Dlg_Dynamic_Route_Attribute dlgDyRouteAttr;//��̬·�����ԶԻ���
	Dlg_Static_Route_Attribute dlgStaticAttribute;

// ����
public:
	void Draw ();//ר�����ڻ�ͼ�ĺ���������OnDraw��ְ�ܣ�����

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//bool OnEraseBkgnd(CDC* pDC);  //���� ������˸

// ʵ��
public:
	virtual ~CGuiderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void paint_road_point();
	//  ��CPoint�ĵ㼯Ϊ��������ֱ��
	void MyLine(int num, int p0, int p1, int p2=0, int p3=0);
	// // �ж�����Ƿ��ڱ��ϣ��ڵĻ�����true
	bool WhetherOnRoad(int poi_x, int poi_y);
	//  �ж�����Ƿ��ڵ���
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

#ifndef _DEBUG  // GuiderView.cpp �еĵ��԰汾
inline CGuiderDoc* CGuiderView::GetDocument() const
   { return reinterpret_cast<CGuiderDoc*>(m_pDocument); }
#endif

