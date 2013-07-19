// GuiderDoc.h : CGuiderDoc ��Ľӿ�
//


#pragma once
#include "Graph.h"


class CGuiderDoc : public CDocument
{
protected: // �������л�����
	CGuiderDoc();
	DECLARE_DYNCREATE(CGuiderDoc)

// ����
public:
	CPoint points[100];//�ص�����
	CPoint roads[200];//·������
	int roadNum;
	Graph<int ,double> graph_doc;//ͼ

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGuiderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	// �޸ı�����
	void SetTitle(LPCTSTR lpszTitle);
};


