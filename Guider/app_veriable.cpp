#include "stdafx.h"
#include "app_veriable.h"
#include"map.h"
//////////////////////////////////////////////////////////////////////////////////ȫ�ֱ�����//////////////////////////////////////////


//���õص��Ĭ�����Բ��� 
char App_Veriable::DefaultSiteStyle='T';//����[C-Բ��T-�����Σ�R-����]
COLORREF App_Veriable::DefaultSiteColor=RGB(255,0,0);//��ɫ
int App_Veriable::DefaultSiteSize=10;//��С
CString App_Veriable::DefaultSiteInfo=CString("������ص���Ϣ...");//�ص���Ϣ

//����·����Ĭ�����Բ���
COLORREF App_Veriable::DefaultRouteColor=RGB(0,255,0);//��ɫ
int App_Veriable::DefaultRouteWidth=1;//���
CString App_Veriable::DefaultRouteInfo=CString("������·����Ϣ...");//·����Ϣ

int App_Veriable::DefaultRoutePointSize=5;//�۵�Ĵ�С
COLORREF App_Veriable::DefaultRoutePointColor=RGB(0,0,255);//�۵���ɫ

bool App_Veriable::IsAddingRoute=false;//������ӽڵ�
int App_Veriable::RouteBeginID=0;//IDΪ��Чֵ

const CPoint p(-1,-1);
CPoint App_Veriable::RelativeContextMenuPos=p;//��������Ĳ˵�λ��

//ѡ����ɫ��ɫ��ʾ
COLORREF App_Veriable::DefaultSiteSeletedModeColor=RGB(255,100,0);//�ص�ѡ����ɫ
COLORREF App_Veriable::SelectingSiteColor=RGB(-1,-1,-1);//�ص�ѡ��֮ǰ����ɫ

COLORREF App_Veriable::DefaultRouteSeletedModeColor=RGB(100,0,0);//·��ѡ����ɫ
COLORREF App_Veriable::SelectingRouteColor=RGB(-1,-1,-1);//·��ѡ��֮ǰ����ɫ

COLORREF App_Veriable::DefaultRoutePointSeletedModeColor=RGB(0,0,100);//�۵��ѡ����ɫ
COLORREF App_Veriable::SelectingRoutePointColor=RGB(-1,-1,-1);//�۵�ѡ��֮ǰ����ɫ

int App_Veriable::SelectedSiteID=0;//ѡ�е��ID
int App_Veriable::SelectedRouteID1=0;//ѡ��·����ID1
int App_Veriable::SelectedRouteID2=0;//ѡ��·����ID2

bool App_Veriable::LBDown=false;//��¼���״̬

bool App_Veriable::ShowRouteLength=false;//��ʾ·������
bool App_Veriable::ShowSiteInfo=false;//��ʾ�ڵ���Ϣ


int App_Veriable::ShortestRouteBeginID=0;//��¼���·����ʼ���ID

CPoint App_Veriable::LastMovePoint=p;

CString App_Veriable::FileOpenPathName=L"";//�ļ��򿪵�·��

bool App_Veriable::FileIsSaved=false;//�ļ��Ƿ��Ѿ�����

CString App_Veriable::SiteInfoForMove=L"";//�ƶ��ص��ʱ���¼�Ľڵ���Ϣ

void App_Veriable::App_Save(CArchive & ar)
{
	ar<<Site::_ID_;//ȫ��ID
	ar<<DefaultSiteStyle<<DefaultSiteColor<<DefaultSiteSize<<DefaultSiteInfo
		<<DefaultRouteColor<<DefaultRouteWidth<<DefaultRouteInfo
		<<DefaultRoutePointSize<<DefaultRoutePointColor
		<<IsAddingRoute<<RouteBeginID
		<<RelativeContextMenuPos
		<<DefaultSiteSeletedModeColor<<SelectingSiteColor
		<<DefaultRouteSeletedModeColor<<SelectingRouteColor
		<<DefaultRoutePointSeletedModeColor<<SelectingRoutePointColor
		<<SelectedSiteID<<SelectedRouteID1<<SelectedRouteID2
		<<LBDown
		<<ShowRouteLength<<ShowSiteInfo
		<<ShortestRouteBeginID
		<<LastMovePoint
		<<FileOpenPathName
		<<FileIsSaved
		<<SiteInfoForMove;
}
void App_Veriable::App_Open(CArchive & ar)
{
	ar>>Site::_ID_;//ȫ��ID
	ar>>DefaultSiteStyle>>DefaultSiteColor>>DefaultSiteSize>>DefaultSiteInfo
		>>DefaultRouteColor>>DefaultRouteWidth>>DefaultRouteInfo
		>>DefaultRoutePointSize>>DefaultRoutePointColor
		>>IsAddingRoute>>RouteBeginID
		>>RelativeContextMenuPos
		>>DefaultSiteSeletedModeColor>>SelectingSiteColor
		>>DefaultRouteSeletedModeColor>>SelectingRouteColor
		>>DefaultRoutePointSeletedModeColor>>SelectingRoutePointColor
		>>SelectedSiteID>>SelectedRouteID1>>SelectedRouteID2
		>>LBDown
		>>ShowRouteLength>>ShowSiteInfo
		>>ShortestRouteBeginID
		>>LastMovePoint
		>>FileOpenPathName
		>>FileIsSaved
		>>SiteInfoForMove;
}