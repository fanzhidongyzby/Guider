
#pragma once 

//////////////////////////////////////////////////////////////////////////////////全局变量类//////////////////////////////////////////

class App_Veriable
{
public:
	//设置地点的默认属性参数 
	static char DefaultSiteStyle;//类型[C-圆，T-三角形，R-矩形]
	static COLORREF DefaultSiteColor;//颜色
	static int DefaultSiteSize;//大小
	static CString DefaultSiteInfo;//地点信息

	//设置路径的默认属性参数
	static COLORREF DefaultRouteColor;//颜色
	static int DefaultRouteWidth;//宽度
	static CString DefaultRouteInfo;//路径信息

	static int DefaultRoutePointSize;//折点的大小
	static COLORREF DefaultRoutePointColor;//折点颜色

	static bool IsAddingRoute;//正在添加节点
	static int RouteBeginID;//记录创建路径时，开始地点的ID值

	static CPoint RelativeContextMenuPos;//相对上下文菜单位置

	static COLORREF DefaultSiteSeletedModeColor;//地点选中颜色
	static COLORREF SelectingSiteColor;//地点选中之前的颜色

	static COLORREF DefaultRouteSeletedModeColor;//路径选中颜色
	static COLORREF SelectingRouteColor;//路径选中之前的颜色

	static COLORREF DefaultRoutePointSeletedModeColor;//折点点选中颜色
	static COLORREF SelectingRoutePointColor;//折点选中之前的颜色

	static int SelectedSiteID;//选中点的ID
	static int SelectedRouteID1;//选中路径的ID1
	static int SelectedRouteID2;//选中路径的ID2

	static bool LBDown;//记录左键状态

	static bool ShowRouteLength;//显示路径长度
	static bool ShowSiteInfo;//显示节点信息

	static int ShortestRouteBeginID;//记录最短路径起始点的ID

	static CPoint LastMovePoint;//鼠标移动中记录上一个点

	static CString FileOpenPathName;//文件打开的路径

	static bool FileIsSaved;//文件是否已经保存

	static void App_Save(CArchive & ar);
	static void App_Open(CArchive & ar);

	static CString SiteInfoForMove;//移动地点的时候记录的节点信息
};