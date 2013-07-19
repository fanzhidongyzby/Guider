
#pragma once 

//////////////////////////////////////////////////////////////////////////////////ȫ�ֱ�����//////////////////////////////////////////

class App_Veriable
{
public:
	//���õص��Ĭ�����Բ��� 
	static char DefaultSiteStyle;//����[C-Բ��T-�����Σ�R-����]
	static COLORREF DefaultSiteColor;//��ɫ
	static int DefaultSiteSize;//��С
	static CString DefaultSiteInfo;//�ص���Ϣ

	//����·����Ĭ�����Բ���
	static COLORREF DefaultRouteColor;//��ɫ
	static int DefaultRouteWidth;//���
	static CString DefaultRouteInfo;//·����Ϣ

	static int DefaultRoutePointSize;//�۵�Ĵ�С
	static COLORREF DefaultRoutePointColor;//�۵���ɫ

	static bool IsAddingRoute;//������ӽڵ�
	static int RouteBeginID;//��¼����·��ʱ����ʼ�ص��IDֵ

	static CPoint RelativeContextMenuPos;//��������Ĳ˵�λ��

	static COLORREF DefaultSiteSeletedModeColor;//�ص�ѡ����ɫ
	static COLORREF SelectingSiteColor;//�ص�ѡ��֮ǰ����ɫ

	static COLORREF DefaultRouteSeletedModeColor;//·��ѡ����ɫ
	static COLORREF SelectingRouteColor;//·��ѡ��֮ǰ����ɫ

	static COLORREF DefaultRoutePointSeletedModeColor;//�۵��ѡ����ɫ
	static COLORREF SelectingRoutePointColor;//�۵�ѡ��֮ǰ����ɫ

	static int SelectedSiteID;//ѡ�е��ID
	static int SelectedRouteID1;//ѡ��·����ID1
	static int SelectedRouteID2;//ѡ��·����ID2

	static bool LBDown;//��¼���״̬

	static bool ShowRouteLength;//��ʾ·������
	static bool ShowSiteInfo;//��ʾ�ڵ���Ϣ

	static int ShortestRouteBeginID;//��¼���·����ʼ���ID

	static CPoint LastMovePoint;//����ƶ��м�¼��һ����

	static CString FileOpenPathName;//�ļ��򿪵�·��

	static bool FileIsSaved;//�ļ��Ƿ��Ѿ�����

	static void App_Save(CArchive & ar);
	static void App_Open(CArchive & ar);

	static CString SiteInfoForMove;//�ƶ��ص��ʱ���¼�Ľڵ���Ϣ
};