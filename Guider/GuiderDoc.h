// GuiderDoc.h : CGuiderDoc 类的接口
//


#pragma once
#include "Graph.h"


class CGuiderDoc : public CDocument
{
protected: // 仅从序列化创建
	CGuiderDoc();
	DECLARE_DYNCREATE(CGuiderDoc)

// 属性
public:
	CPoint points[100];//地点数组
	CPoint roads[200];//路径数组
	int roadNum;
	Graph<int ,double> graph_doc;//图

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CGuiderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 修改标题栏
	void SetTitle(LPCTSTR lpszTitle);
};


