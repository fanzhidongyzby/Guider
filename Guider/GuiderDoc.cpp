// GuiderDoc.cpp : CGuiderDoc ���ʵ��
//

#include "stdafx.h"
#include "Guider.h"

#include "GuiderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGuiderDoc

IMPLEMENT_DYNCREATE(CGuiderDoc, CDocument)

BEGIN_MESSAGE_MAP(CGuiderDoc, CDocument)
END_MESSAGE_MAP()


// CGuiderDoc ����/����

CGuiderDoc::CGuiderDoc()
{
	// TODO: �ڴ����һ���Թ������
	for(int j=0;j<100;j++)  //��ʼ����
		points[j]=CPoint(0,0);
	for(int j=0;j<200;j++)  //��ʼ����
		roads[j]=CPoint(0,0);
	roadNum=0;
	//������
	points [0]=CPoint(278,15);  //����
	points [1]=CPoint(278,64);  //����
	points [2]=CPoint(320,102); //����
	points [3]=CPoint(355,102); //ѧ6
	points [4]=CPoint(420,102); //���
	points [5]=CPoint(420,158); //����
	points [6]=CPoint(500,158); //������
	points [7]=CPoint(500,244); //ѧ11-1
	points [8]=CPoint(509,244); //������-����
	points [9]=CPoint(588,244); //������-����
	points [10]=CPoint(588,274); //������-��
	points [11]=CPoint(613,274); //����

	points [12]=CPoint(509,274); //������-��

	points [13]=CPoint(420,216); //�ۺϷ���¥
	points [14]=CPoint(422,274); //1��

	points [15]=CPoint(427,363); //������-1����
	points [16]=CPoint(427,428); //������-�Ͻ�1
	points [17]=CPoint(434,480); //���ͺ�-���
	points [18]=CPoint(614,414); //���ͺ�-����
	points [19]=CPoint(614,494); //���ͺ�-��
	points [20]=CPoint(493,503); //���ͺ�-��
	points [21]=CPoint(493,558); //���ͺ�-��

	points [22]=CPoint(618,618); //���ͺ�-����
	points [23]=CPoint(419,618); //���ͺ�-����

	points [24]=CPoint(355,216);  //ѧ1
	points [25]=CPoint(355,274);  //��ѧ���Ļ������
	points [26]=CPoint(360,363);  //Сѧ
	points [27]=CPoint(362,428);  //������-�Ͻ�2
	points [28]=CPoint(258,428);  //Ψ��Ψʵ--�Ͻ�3
	points [29]=CPoint(278,622);  //����

	points [30]=CPoint(235,107); //��ͨѧԺ
	points [31]=CPoint(194,107); //������
	//points [32]=CPoint(161,107); //ӡˢ��
	points [33]=CPoint(138,107); //Զ�̽������� 
	points [34]=CPoint(67,107); //װ�䳧
	points [35]=CPoint(67,152); //4��-����
	points [36]=CPoint(67,216); //��ѧ-��
	points [37]=CPoint(65,274); //��ѧ-��
	points [38]=CPoint(12,274); //����-��

	points [39]=CPoint(216,64); //����ʵ��¥
	points [40]=CPoint(355,172); //����壭��
	points [41]=CPoint(258,172); //ͼ��ݣ��ɹ�
	points [42]=CPoint(258,216); //2��
	points [43]=CPoint(194,172); //���̣���
	points [44]=CPoint(194,152); //���̣�����
	points [45]=CPoint(64,48); //ѧУ������
	points [46]=CPoint(194,216); //����
	points [47]=CPoint(132,216); //����¥����
	points [48]=CPoint(132,274); //����¥����
	points [49]=CPoint(222,274); //��¥-����
	points [50]=CPoint(258,274); //����¥����
	points [51]=CPoint(222,216); //��¥-����
	points [52]=CPoint(166,216); //��¥-����
	points [53]=CPoint(166,274); //��¥-����

	points [54]=CPoint(132,355); //̫���㳡-����
	points [55]=CPoint(64,355); //54-��
	points [56]=CPoint(194,355); //̫���㳡-��
	points [57]=CPoint(258,355); //̫���㳡-����
	points [58]=CPoint(258,364); //57-��

	points [59]=CPoint(12,428); //����-��
	points [60]=CPoint(64,428); //�Ͻ�-6
	points [61]=CPoint(132,428); //�Ͻ�-5
	points [62]=CPoint(194,428); //�Ͻ�-4

	points [63]=CPoint(138,152); //����ʵϰ����




	for(int i=0;i<64;i++)      //�������ͼ��
		graph_doc.insertv (-(i+1));
	this->graph_doc .removev (-33);

}

CGuiderDoc::~CGuiderDoc()
{
}

BOOL CGuiderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGuiderDoc ���л�

void CGuiderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGuiderDoc ���

#ifdef _DEBUG
void CGuiderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGuiderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// �޸ı�����

void CGuiderDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle (L"�й�ʯ�ʹ�ѧ��������- -У԰����ϵͳ");
}
