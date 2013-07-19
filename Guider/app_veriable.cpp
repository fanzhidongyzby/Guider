#include "stdafx.h"
#include "app_veriable.h"
#include"map.h"
//////////////////////////////////////////////////////////////////////////////////全局变量类//////////////////////////////////////////


//设置地点的默认属性参数 
char App_Veriable::DefaultSiteStyle='T';//类型[C-圆，T-三角形，R-矩形]
COLORREF App_Veriable::DefaultSiteColor=RGB(255,0,0);//颜色
int App_Veriable::DefaultSiteSize=10;//大小
CString App_Veriable::DefaultSiteInfo=CString("请输入地点信息...");//地点信息

//设置路径的默认属性参数
COLORREF App_Veriable::DefaultRouteColor=RGB(0,255,0);//颜色
int App_Veriable::DefaultRouteWidth=1;//宽度
CString App_Veriable::DefaultRouteInfo=CString("请输入路径信息...");//路径信息

int App_Veriable::DefaultRoutePointSize=5;//折点的大小
COLORREF App_Veriable::DefaultRoutePointColor=RGB(0,0,255);//折点颜色

bool App_Veriable::IsAddingRoute=false;//正在添加节点
int App_Veriable::RouteBeginID=0;//ID为无效值

const CPoint p(-1,-1);
CPoint App_Veriable::RelativeContextMenuPos=p;//相对上下文菜单位置

//选中颜色反色表示
COLORREF App_Veriable::DefaultSiteSeletedModeColor=RGB(255,100,0);//地点选中颜色
COLORREF App_Veriable::SelectingSiteColor=RGB(-1,-1,-1);//地点选中之前的颜色

COLORREF App_Veriable::DefaultRouteSeletedModeColor=RGB(100,0,0);//路径选中颜色
COLORREF App_Veriable::SelectingRouteColor=RGB(-1,-1,-1);//路径选中之前的颜色

COLORREF App_Veriable::DefaultRoutePointSeletedModeColor=RGB(0,0,100);//折点点选中颜色
COLORREF App_Veriable::SelectingRoutePointColor=RGB(-1,-1,-1);//折点选中之前的颜色

int App_Veriable::SelectedSiteID=0;//选中点的ID
int App_Veriable::SelectedRouteID1=0;//选中路径的ID1
int App_Veriable::SelectedRouteID2=0;//选中路径的ID2

bool App_Veriable::LBDown=false;//记录左键状态

bool App_Veriable::ShowRouteLength=false;//显示路径长度
bool App_Veriable::ShowSiteInfo=false;//显示节点信息


int App_Veriable::ShortestRouteBeginID=0;//记录最短路径起始点的ID

CPoint App_Veriable::LastMovePoint=p;

CString App_Veriable::FileOpenPathName=L"";//文件打开的路径

bool App_Veriable::FileIsSaved=false;//文件是否已经保存

CString App_Veriable::SiteInfoForMove=L"";//移动地点的时候记录的节点信息

void App_Veriable::App_Save(CArchive & ar)
{
	ar<<Site::_ID_;//全局ID
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
	ar>>Site::_ID_;//全局ID
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