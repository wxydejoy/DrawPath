// DrawPathDlg.cpp : implementation file
//1

#include "stdafx.h"
#include "DrawPath.h"
#include "DrawPathDlg.h"
#include "math.h"

#define PI 3.1415926 
#define Region_W  300
#define Region_H  300


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawPathDlg dialog

CDrawPathDlg::CDrawPathDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawPathDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawPathDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawPathDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawPathDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawPathDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ReDraw, OnBUTTONReDraw)
	ON_BN_CLICKED(IDC_BUTTON_Continue, OnBUTTONContinue)
	ON_BN_CLICKED(IDC_BUTTON_Pause, OnBUTTONPause)
	ON_BN_CLICKED(IDC_BUTTON_StopDrawWorkSpace, OnBUTTONStopDrawWorkSpace)
	ON_BN_CLICKED(IDC_BUTTON_DrawLine, OnBUTTONDrawLine)
	ON_BN_CLICKED(IDC_BUTTON_Control, OnBUTTONControl)
	ON_BN_CLICKED(IDC_BUTTON_CalcAngle, OnBUTTONCalcAngle)
	ON_EN_CHANGE(IDC_EDIT_R, OnChangeEditR)
	ON_EN_CHANGE(IDC_EDIT_StartX2, OnChangeEDITStartX2)
	ON_BN_CLICKED(IDC_PIC, OnPic)
	ON_BN_CLICKED(IDC_STATIC_ALPHA, OnStaticAlpha)
//	ON_EN_CHANGE(IDC_EDIT_ALPHA, OnChangeEDITALPHA)
//	ON_EN_CHANGE(IDC_EDIT_ALPHA, OnChangeEditAlpha)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_StartX, &CDrawPathDlg::OnEnChangeEditStartx)
	ON_EN_CHANGE(IDC_EDIT_EndX, &CDrawPathDlg::OnEnChangeEditEndx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawPathDlg message handlers

BOOL CDrawPathDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
//	AfxMessageBox("FIRSY");
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//为变量赋初始值

	m_bIsDrawing = false ;
	m_bIsPause = false ;

	angle_moving.Angle1 = 10 ;
	angle_moving.Angle2 = 170 ;
	angle_moving.Angle3 = -170 ; 
	
	
	m_iLength1 = 150 ;
	m_iLength2 =  120 ;
    m_iLength3 = 60 ;    
	brick_Length = 40;
		//物块姿态角
     //end_alpha = 80;

	angle_moving.Angle1Max = 360 ;
	angle_moving.Angle1Min = 0 ;


	angle_moving.Angle2Max = 360 ;
	angle_moving.Angle2Min = 0 ;

	angle_moving.Angle1Max = 360;
	angle_moving.Angle1Min = 0 ;

	m_iRVaule = 255 ;//红色值
	m_iGVaule = 0 ;//绿色值
	m_iBVaule = 0 ;//蓝色值
	m_iWidth= 2 ;//画笔宽度值


	//将值显示在控件中
	CString strTemp ;

	//显示连杆长度1
	strTemp.Format("%d",m_iLength1);
	SetDlgItemText(IDC_EDIT_Length1,strTemp) ;

	//显示连杆长度2
	strTemp.Format("%d",m_iLength2);
	SetDlgItemText(IDC_EDIT_Length2,strTemp) ;

	//显示连杆长度3
	strTemp.Format("%d",m_iLength3);                  //1
	SetDlgItemText(IDC_EDIT_Length3,strTemp) ;        //1

	//显示关节角度1
	strTemp.Format("%.3f",angle_moving.Angle1);
	SetDlgItemText(IDC_EDIT_Angle1,strTemp) ;

	//显示关节角度2
	strTemp.Format("%.3f",angle_moving.Angle2);
	SetDlgItemText(IDC_EDIT_Angle2,strTemp) ;

	//显示关节角度3
 	strTemp.Format("%.3f",angle_moving.Angle3);                //1
	SetDlgItemText(IDC_EDIT_Angle3,strTemp) ;        //1

	//显示关节角度3
 //	strTemp.Format("%.3f",alpha);                //1
//	SetDlgItemText(IDC_EDIT_ALPHA,strTemp) ;        //


/*
	//显示关节角度1最大值
	strTemp.Format("%.3f",angle_moving.Angle1Max);
	SetDlgItemText(IDC_EDIT_Angle1Max,strTemp) ;

	//显示关节角度2最大值
	strTemp.Format("%.3f",angle_moving.Angle2Max);
	SetDlgItemText(IDC_EDIT_Angle2Max,strTemp) ;

	//显示关节角度1最小值
	strTemp.Format("%.3f",angle_moving.Angle1Min);
	SetDlgItemText(IDC_EDIT_Angle1Min,strTemp) ;

	//显示关节角度2最小值
	strTemp.Format("%.3f",angle_moving.Angle2Min);
	SetDlgItemText(IDC_EDIT_Angle2Min,strTemp) ;
*/
	//显示连杆的颜色值和宽度值
	strTemp.Format("%d",m_iRVaule);
	SetDlgItemText(IDC_EDIT_R,strTemp) ;

	strTemp.Format("%d",m_iGVaule);
	SetDlgItemText(IDC_EDIT_G,strTemp) ;

	strTemp.Format("%d",m_iBVaule);
	SetDlgItemText(IDC_EDIT_B,strTemp) ;

	strTemp.Format("%d",m_iWidth);
	SetDlgItemText(IDC_EDIT_W,strTemp) ;


	pWnd = GetDlgItem(IDC_PIC); // 获得对话框上的picture的窗口句柄
    pWnd->GetClientRect(&rect);         //获取绘图区域大小

	pDC = pWnd->GetDC();                 // 获得对话框上的picture的设备指针
    pOldBmp = NULL;                           // 将旧的位图指针置空
    // 创建内存绘图设备，使内存位图的DC与控件的DC关联
    memDC.CreateCompatibleDC(pDC); 
    memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
    pOldBmp = memDC.SelectObject(&memBitmap);

	//设置中心点坐标（连杆1的起始点坐标）
	ptCenter.x = rect.Width()/2 ;
	ptCenter.y =  rect.Height() ;

	//绘图初始化线段的起始点和结束点
	ptStartForDraw.x = 400 ;
	ptStartForDraw.y =400 ;
	ptEndForDraw.x = 60 ;
	ptEndForDraw.y = 20 ;




	//将绘图线段起始点和终点坐标显示在控件中
	strTemp.Format("%d",ptStartForDraw.x);
	SetDlgItemText(IDC_EDIT_StartX,strTemp) ;

	strTemp.Format("%d",ptStartForDraw.y);
	SetDlgItemText(IDC_EDIT_StartY,strTemp) ;

	strTemp.Format("%d",ptEndForDraw.x);
	SetDlgItemText(IDC_EDIT_EndX,strTemp) ;

	strTemp.Format("%d",ptEndForDraw.y);
	SetDlgItemText(IDC_EDIT_EndY,strTemp) ;

	//控制点的个数
	m_iControlPointNumber = 10 ;

	//显示控制点的个数
	strTemp.Format("%d",m_iControlPointNumber);
	SetDlgItemText(IDC_EDIT_Number,strTemp) ;
	
	//计算两个连杆末端点的位置
	Calculate() ;

	//将绘图坐标转换为计算坐标
	DrawToCalc() ;
	//将计算坐标显示在控件中
	ShowCalcPoint() ;
	DrawBrick();
	//为控制点数组分配存储空间
	ControlPointForDraw = new CPoint[1000] ;
	ControlPointForCalc = new fPoint[1000] ; 
	ControlAngleForMove = new fAngle[1000] ; 


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDrawPathDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDrawPathDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	//绘制绘图区域
	memDC.Rectangle(0,0,rect.Width(),rect.Height());

	//绘图
	//根据界面上设定的参数创建画笔	
	CPen Pen;
	Pen.CreatePen(PS_SOLID,m_iWidth,RGB(m_iRVaule, m_iGVaule, m_iBVaule));
	CPen *oldPen;
	//选择创建的画笔
	oldPen = memDC.SelectObject(&Pen);

	//绘制机器人
	DrawRobot() ;
	
	int R = 3 ;
	for(int i = 0 ; i <= m_iControlPointNumber + 1; i++)
	{
		memDC.Ellipse(ControlPointForDraw[i].x - R ,ControlPointForDraw[i].y - R,ControlPointForDraw[i].x + R ,ControlPointForDraw[i].y + R) ;
	}
	
	//选择原来的画笔
	memDC.SelectObject(oldPen) ;
	DrawBrick();
	//绘制线段
	DrawTestLine() ;

	//删除创建的画笔
	DeleteObject(Pen) ;

	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY);

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawPathDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//绘图时计算连杆末端点的坐标
void CDrawPathDlg::Calculate()
{
	//end_alpha = float(atan((ptEndForCalc.y - ptStartForCalc.y)/(ptEndForCalc.x - ptStartForCalc.x)) );
	
	//angle_moving.Angle3 =  end_alpha  - angle_moving.Angle2 - angle_moving.Angle1;
	
	//计算连杆1末端点坐标
	pt1.x = ptCenter.x + (int)(m_iLength1 * cos(angle_moving.Angle1*PI/180) + 0.5) ;
	pt1.y = ptCenter.y - (int)(m_iLength1 * sin(angle_moving.Angle1*PI/180) + 0.5) ;

	//计算连杆2末端点坐标
	pt2.x = pt1.x + (int)(m_iLength2 * cos((angle_moving.Angle1 + angle_moving.Angle2)*PI/180) + 0.5) ;
	pt2.y = pt1.y - (int)(m_iLength2 * sin((angle_moving.Angle1 + angle_moving.Angle2)*PI/180) + 0.5) ;

		//计算连杆3末端点坐标
	pt3.x = pt2.x + (int)(m_iLength3 * cos(( angle_moving.Angle1 + angle_moving.Angle2 + angle_moving.Angle3)*PI/180)+ 0.5) ;
	pt3.y = pt2.y - (int)(m_iLength3 * sin((angle_moving.Angle1 + angle_moving.Angle2 + angle_moving.Angle3)*PI/180)+ 0.5) ;

	float angle_temp = angle_moving.Angle1 + angle_moving.Angle2 + angle_moving.Angle3;//弧度
	brick_width = 40;
	//计算爪子坐标，从杆3终点坐标开始，逆时针依次为z1,2,3,4
	z1.x = pt3.x +(int)( brick_width * cos( (angle_temp -90 )* PI / 180) / 2);
	z1.y = pt3.y - (int)(brick_width  * sin((angle_temp - 90) * PI / 180) / 2);

	z2.x = z1.x + (int)(brick_width * cos((angle_temp ) * PI / 180) / 2);
	z2.y = z1.y - (int)(brick_width * sin((angle_temp ) * PI / 180) / 2);

	z4.x = pt3.x + (int)(brick_width * cos((angle_temp + 90) * PI / 180) / 2);
	z4.y = pt3.y - (int)(brick_width * sin((angle_temp + 90) * PI / 180) / 2);

	z3.x = z4.x + (int)(brick_width * cos((angle_temp ) * PI / 180) / 2);
	z3.y = z4.y - (int)(brick_width * sin((angle_temp ) * PI / 180) / 2);

	
	
}


//绘制三根杆
void CDrawPathDlg::DrawRobot()
{
	//绘制连杆1
	memDC.MoveTo(ptCenter) ;
	memDC.LineTo(pt1) ;

	//绘制连杆2
	memDC.MoveTo(pt1) ;
	memDC.LineTo(pt2) ;

//	pt3.x=50;//记得删掉
//	pt3.y=50;

	//绘制连杆3
	memDC.MoveTo(pt2) ;
	memDC.LineTo(pt3) ;
	//绘制爪子
	memDC.MoveTo(pt3);
	memDC.LineTo(z1);

	memDC.MoveTo(pt3);
	memDC.LineTo(z4);

	memDC.MoveTo(z1);
	memDC.LineTo(z2);

	memDC.MoveTo(z4);
	memDC.LineTo(z3);

	memDC.Rectangle(400,400,0,0 );

}




void CDrawPathDlg::DrawBrick()
{
	
	//brickcenter.y
	brick_width = 40;

brick1.x = brickcenter.x + (int)(brick_width * cos((end_alpha - 90) * PI / 180) / 2);
brick1.y = brickcenter.y - (int)(brick_width * sin((end_alpha - 90) * PI / 180) / 2);

brick2.x = brick1.x + (int)(brick_width * cos((end_alpha)*PI / 180) / 2);
brick2.y = brick1.y - (int)(brick_width * sin((end_alpha)*PI / 180) / 2);

brick4.x = brickcenter.x + (int)(brick_width * cos((end_alpha + 90) * PI / 180) / 2);
brick4.y = brickcenter.y - (int)(brick_width * sin((end_alpha + 90) * PI / 180) / 2);

brick3.x = brick4.x + (int)(brick_width * cos((end_alpha)*PI / 180) / 2);
brick3.y = brick4.y - (int)(brick_width * sin((end_alpha)*PI / 180) / 2);


//CString strTemp;
	//strTemp.Format("angle1.2,%f,%f,,%f,%f", brick1.x, brickcenter.x, brickcenter.y);
	//SetDlgItemText(IDC_EDIT1_dd, strTemp);

}

void CDrawPathDlg::DrawTestLine()
{
	memDC.MoveTo(ptStartForDraw) ;
	memDC.LineTo(ptEndForDraw) ;
	
	//memDC.rect
	//memDC.Rectangle
}

void CDrawPathDlg::GetDataFromControl()
{
	//将控件中输入的值取出，赋值给变量
	CString strTemp ;
	GetDlgItemText(IDC_EDIT_Angle1, strTemp) ;
	angle_moving.Angle1 = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字

	GetDlgItemText(IDC_EDIT_Length1, strTemp) ;
	m_iLength1 = atoi(strTemp) ;//将字符串转换成整型数字

	GetDlgItemText(IDC_EDIT_Angle2, strTemp) ;
	angle_moving.Angle2 = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字

	GetDlgItemText(IDC_EDIT_Length2, strTemp) ;
	m_iLength2 = atoi(strTemp) ;//将字符串转换成整型数字

	GetDlgItemText(IDC_EDIT_Angle3, strTemp) ;                         //1 
	angle_moving.Angle3 = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字    //1

	GetDlgItemText(IDC_EDIT_Length3, strTemp) ;                               //1
	m_iLength3 = atoi(strTemp) ;//将字符串转换成整型数字     
	
	
//	GetDlgItemText(IDC_EDIT_ALPHA, strTemp) ;                               //1
//	alpha = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字    //1

	
	
	

	
	//1
/*
	GetDlgItemText(IDC_EDIT_Angle1Max, strTemp) ;
	angle_moving.Angle1Max = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字

	GetDlgItemText(IDC_EDIT_Angle2Max, strTemp) ;
	angle_moving.Angle2Max = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字


	GetDlgItemText(IDC_EDIT_Angle1Min, strTemp) ;
	angle_moving.Angle1Min = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字

	GetDlgItemText(IDC_EDIT_Angle2Min, strTemp) ;
	angle_moving.Angle2Min = (float)(atof(strTemp)) ;//将字符串转换成浮点型数字

	GetDlgItemText(IDC_EDIT_R, strTemp) ;
	m_iRVaule = atoi(strTemp) ;//将字符串转换成整型数字

	GetDlgItemText(IDC_EDIT_G, strTemp) ;
	m_iGVaule = atoi(strTemp) ;//将字符串转换成整型数字

	GetDlgItemText(IDC_EDIT_B, strTemp) ;
	m_iBVaule = atoi(strTemp) ;//将字符串转换成整型数字

	GetDlgItemText(IDC_EDIT_W, strTemp) ;
	m_iWidth = atoi(strTemp) ;//将字符串转换成整型数字
*/
	//获取绘图线段起始和结束点的坐标
//IDC_EDIT_StartX   物块长度


	GetDlgItemText(IDC_EDIT_EndY, strTemp);
	brick_Length = atoi(strTemp);//将字符串转换成整型数字

	GetDlgItemText(IDC_EDIT_EndX, strTemp);
	end_alpha = atoi(strTemp);//将字符串转换成整型数字
	end_alpha = -end_alpha / 180 * PI;

	GetDlgItemText(IDC_EDIT_StartX, strTemp) ;
	float stemp= atoi(strTemp) ;//将字符串转换成整型数字
	ptStartForDraw.x = stemp - (m_iLength3 + 2 * brick_Length) * cos(end_alpha);
	brickcenter.x = stemp -  brick_Length * cos(end_alpha);


	GetDlgItemText(IDC_EDIT_StartY, strTemp) ;
	float stemp1 = atoi(strTemp)  ;//将字符串转换成整型数字
	ptStartForDraw.y = stemp1+ (m_iLength3 + 2 * brick_Length) * sin(-end_alpha);//将字符串转换成整型数字
	brickcenter.y = stemp1+ brick_Length * sin(-end_alpha);
	//1
	
	//GetDlgItemText(IDC_EDIT_EndX, strTemp) ;
	//ptEndForDraw.x = atoi(strTemp) ;//将字符串转换成整型数字

	

	
	ptEndForDraw.x = (float)(ptStartForDraw.x + (brick_Length)*cos(end_alpha));
	ptEndForDraw.y = (float)(ptStartForDraw.y + (brick_Length)*sin(end_alpha));

	//CString strTemp;
	strTemp.Format("angle1.2,%f,%f,,%f,%f", end_alpha, ptEndForDraw.x, ptEndForDraw.y);
	SetDlgItemText(IDC_EDIT1_dd, strTemp);


	DrawToCalc() ;
	ShowCalcPoint() ;

	//获取控制点的个数
	//GetDlgItemText(IDC_EDIT_Number, strTemp) ;
//	m_iControlPointNumber = atoi(strTemp) ;//将字符串转换成整型数字
}

void CDrawPathDlg::DrawToCalc()
{
	//将绘图坐标系中的坐标转换为计算坐标系
	ptStartForCalc.x = ptStartForDraw.x - ptCenter.x;
	ptStartForCalc.y = -ptStartForDraw.y + ptCenter.y;





	ptEndForCalc.x = ptEndForDraw.x - ptCenter.x;
	ptEndForCalc.y = -ptEndForDraw.y + ptCenter.y;


	AngleJudge();
	
	//将绘图坐标系中的坐标转换为计算坐标系
	//ptStartForCalc.x = ptStartForDraw.x - ptCenter.x ;
	//ptStartForCalc.y = -ptStartForDraw.y + ptCenter.y ;
	//ptStartForCalc.x = ptStartForDraw.x ;
	//ptStartForCalc.y = ptStartForDraw.y ;

	//ptEndForCalc.x =(float)( ptStartForCalc.x + brick_Length * cos(end_alpha ));
	//ptEndForCalc.y = (float)(ptStartForCalc.x + brick_Length * sin(end_alpha));

	
	//CString strTemp;
	//strTemp.Format("angle1.2,%d,%d,%f", ptEndForCalc.y, ptStartForCalc.y, end_alpha);
	//SetDlgItemText(IDC_EDIT1_dd, strTemp);
		//调试用
	//ptEndForCalc.x = ptEndForDraw.x - ptCenter.x ;
	//ptEndForCalc.y = -ptEndForDraw.y + ptCenter.y ;

	
	
	//end_alpha = (float) (atan((float)(ptEndForCalc.y - ptStartForCalc.y)/(float)(ptEndForCalc.x - ptStartForCalc.x)) *180 / PI );


	
	

//	if( end_alpha < 0) {end_alpha = 180 + end_alpha ;}

}

void CDrawPathDlg::AngleJudge() {

	float	dy= (float)(ptEndForCalc.y - ptStartForCalc.y);
	float	dx = (float)(ptEndForCalc.x - ptStartForCalc.x);
	float temp = sqrt(dx * dx + dy * dy);
	float angle_cos = dx / temp;
	end_alpha = acos(angle_cos) * 180 / PI;
	if (dy < 0)  end_alpha = -end_alpha;



}

void CDrawPathDlg::ShowCalcPoint()
{
	CString strTemp ;
	//将计算坐标系起始点和终点坐标显示在控件中
	strTemp.Format("%d",ptStartForCalc.x);
	SetDlgItemText(IDC_EDIT_StartX2,strTemp) ;

	strTemp.Format("%d",ptStartForCalc.y);
	SetDlgItemText(IDC_EDIT_StartY2,strTemp) ;

	
	//AfxMessageBox("ShowCalcPoint");

	strTemp.Format("%d",ptEndForCalc.x);
	SetDlgItemText(IDC_EDIT_EndX2,strTemp) ;

	strTemp.Format("%d",ptEndForCalc.y);
	SetDlgItemText(IDC_EDIT_EndY2,strTemp) ;
}

//重新绘制函数
void CDrawPathDlg::OnBUTTONReDraw() 
{
	GetDataFromControl() ;
	Calculate();
	Invalidate(FALSE);

}



//运动过程函数
void CDrawPathDlg::Moving()
{

//计算余弦值
/*	float temp1 = float(ptEndForCalc.x - ptStartForCalc.x);
	float temp2 = float((ptEndForCalc.x - ptStartForCalc.x)*(ptEndForCalc.x - ptStartForCalc.x)+(ptEndForCalc.y - ptStartForCalc.y)*(ptEndForCalc.y - ptStartForCalc.y));
	float temp3 = acos(temp1 / sqrt(temp2));
	end_alpha = float( acos(temp1 / sqrt(temp2))) ;

	//调试用
	CString strTemp ;
	strTemp.Format("angle1.2,%.3f,%.3f,,%.3f,%.3f",temp1,temp2,temp3,end_alpha);
	SetDlgItemText(IDC_EDIT1_dd,strTemp) ;
*/

	//end_alpha = (float) 2;

	


	angle_moving.Angle1 = 10;
	angle_moving.Angle2 = 170;
	angle_moving.Angle3 = -170;
    
//	float end_angle1,end_angle2,end_angle3;
    float t = 0.5;//变化量
    float s = 2;//t<=s
	
    fAngle angle_end[2];
	fPoint point_moving;
	
	point_moving.x =(float)( ptStartForCalc.x);
	point_moving.y =(float)( ptStartForCalc.y);
	


	InverseKinematic(point_moving,angle_end);




while(((abs(angle_moving.Angle1 - angle_end[0].Angle1)< s) + (abs(angle_moving.Angle2 - angle_end[0].Angle2)< s) ) != 2
 /* 判断是否到达位置*/ ){



    //theta 1
    if(abs(angle_moving.Angle1 - angle_end[0].Angle1) >  (s - 0.5)){
        if(angle_moving.Angle1 < angle_end[0].Angle1){
            angle_moving.Angle1 += t;
        }else{
            angle_moving.Angle1 -= t;
        }
    }
    
	if(abs(angle_moving.Angle2 - angle_end[0].Angle2) > (s - 0.5)){
        if(angle_moving.Angle2 < angle_end[0].Angle2){
            angle_moving.Angle2 += t;
        }else{
            angle_moving.Angle2 -= t;
        }
    }
    /* 
    if(abs(angle_moving.Angle3- angle_end[0].Angle3) > s){
        if(angle_moving.Angle3 < angle_end[0].Angle3){
            angle_moving.Angle3 += t;
        }else{
            angle_moving.Angle3 -= t;
        }
    }
    */

	//调试用
//	CString strTemp ;
//	strTemp.Format("angle1.2,%.3f,%.3f,,%.3f,%.3f",angle_moving.Angle1,angle_end[0].Angle1,angle_moving.Angle2,angle_end[0].Angle2);
//	SetDlgItemText(IDC_EDIT1_dd,strTemp) ;



    Calculate() ;
	Invalidate(FALSE);
 //   printf("angle1: %.1f,angle2: %.1f,angle3: %.1f\n",angle_moving.Angle1,angle_moving.Angle2,angle_moving.Angle3);
	Sleep(1) ;
    }



while( (abs(angle_moving.Angle3 - angle_end[0].Angle3)< s) != 1){
if(abs(angle_moving.Angle3 - angle_end[0].Angle3) > (s - 0.5) ){
        if(angle_moving.Angle3 < angle_end[0].Angle3){
            angle_moving.Angle3 += t;
        }else{
            angle_moving.Angle3 -= t;
        }


    }
    


    Calculate() ;
	Invalidate(FALSE);
 //   printf("angle1: %.1f,angle2: %.1f,angle3: %.1f\n",angle_moving.Angle1,angle_moving.Angle2,angle_moving.Angle3);
	Sleep(1) ;
}
//CString strTemp;
//strTemp.Format("angle1.2,%.3f,%.3f,,%.3f,%.3f", end_alpha, ptEndForCalc.y, ptEndForCalc.x);
//SetDlgItemText(IDC_EDIT1_dd, strTemp);

}





//连杆运动函数-----
void CDrawPathDlg::Move()
{

	Moving();


	fPoint point = ControlPointForCalc[0];
	fAngle angle[2] ;

	//调试用
//	CString strTemp ;
//strTemp.Format("move%.3f,%.3f,%.3f",angle[0].Angle1,point.y,alpha);
//	SetDlgItemText(IDC_EDIT1_dd,strTemp) ;


	int iCount = InverseKinematic(point,angle) ;

//调试用
//	CString strTemp ;
//	strTemp.Format("move%.3f,%.3f,%.3f",iCount,point.y,alpha);
//	SetDlgItemText(IDC_EDIT1_dd,strTemp) ;

	if(iCount == 0)
	{


		//调试用
		AfxEndThread(0);

		//AfxMessageBox("不能到达改位置");
		//break ;
	}
	else if(iCount == 1)
	{


		angle_moving.Angle1 = angle[0].Angle1 ;
		angle_moving.Angle2 = angle[0].Angle2 ;
		angle_moving.Angle3 = end_alpha - angle_moving.Angle1 - angle_moving.Angle2;
		





		Calculate() ;
		Invalidate(FALSE);
		Sleep(10) ;
	}
	else
	{




		//选择一个角度作为起始姿态
		angle_moving.Angle1 = angle[0].Angle1 ;
		angle_moving.Angle2 = angle[0].Angle2 ;
		angle_moving.Angle3 = end_alpha - angle_moving.Angle1 - angle_moving.Angle2;

		Calculate() ;
		Invalidate(FALSE);
		Sleep(10) ;
	}



	for(int i = 1 ; i < m_iControlPointNumber + 2; i++)
	{
		fPoint point = ControlPointForCalc[i];
		fAngle angle[2] ;

		int iCount = InverseKinematic(point,angle) ;

		if(iCount == 0)
		{
			//AfxMessageBox("move不能到达改位置") ;
			//break ;
		}
		else if(iCount == 1)
		{
			angle_moving.Angle1 = angle[0].Angle1 ;
			angle_moving.Angle2 = angle[0].Angle2 ;
			angle_moving.Angle3 = end_alpha - angle_moving.Angle1 - angle_moving.Angle2;

			Calculate() ;
			Invalidate(FALSE);
			Sleep(100) ;
		}
		else
		{
			float temp1 = angle_moving.Angle1 - angle[0].Angle1 ;
			if(temp1 < 0)
			{
				temp1 = -temp1 ;
			}
			float temp2 = angle_moving.Angle1 - angle[1].Angle1 ;
			if(temp2 < 0)
			{
				 temp2 = -temp2;
			}

			if(temp2 > temp1)
			{
				angle_moving.Angle1 = angle[0].Angle1 ;
				angle_moving.Angle2 = angle[0].Angle2 ;
				angle_moving.Angle3 = end_alpha - angle_moving.Angle1 - angle_moving.Angle2;
			}
			else
			{
				angle_moving.Angle1 = angle[1].Angle1 ;
				angle_moving.Angle2 = angle[1].Angle2 ;
				angle_moving.Angle3 = end_alpha - angle_moving.Angle1 - angle_moving.Angle2;
			}

			Calculate() ;
			Invalidate(FALSE);
			Sleep(100) ;
		}
	}
}

//连杆运动线程函数
UINT CDrawPathDlg::MoveThread(void *param)
{
	CDrawPathDlg *pDlg = (CDrawPathDlg*)param ;	
	pDlg->Move() ;
	return 0 ;
}

void CDrawPathDlg::OnBUTTONContinue() 
{
	
}

void CDrawPathDlg::OnBUTTONPause() 
{
	
}

void CDrawPathDlg::OnBUTTONStopDrawWorkSpace() 
{
	
}

void CDrawPathDlg::OnBUTTONDrawLine() 
{
	GetDataFromControl() ;
	OnBUTTONControl() ;
	OnBUTTONCalcAngle();
	Invalidate(FALSE);
}


//机械手正运动学,计算末端点的坐标
//输入：关节角度值
//输出：目标点的坐标
//Px = L1*C1 + L2*C12 ;
//Py = L1*S1 + L2*S12 ;

//C1为关节角度1的余弦
//S1为关节角度1的正弦
//S12为两个角度和的正弦
//C12为两个角度和的余弦
//-----
fPoint CDrawPathDlg::ForwardKinematic(float Angle1, float Angle2 )
{
	fPoint point ;
	point.x = (float)(m_iLength1 * cos(Angle1*PI/180) + m_iLength2 * cos((Angle1+Angle2)*PI/180) ) ;
	point.y = (float)(m_iLength1 * sin(Angle1*PI/180) + m_iLength2 * sin((Angle1+Angle2)*PI/180) ) ;
	//调试用
//	CString strTemp ;
//	strTemp.Format("111%.3f,%.3f",point.x,point.y);
//	SetDlgItemText(IDC_EDIT1_dd,strTemp) ;
	return point ;
}

//判断两个浮点数是否接近，接近就认为相等
bool CDrawPathDlg::bEqualForFloat(float a, float b)
{
	if((a-b)> -0.1 && (a-b)< 0.1)
	{
		return true ;
	}

	return false ;
}

//机械手逆运动学,计算达到目标点的位置时对应的关节角度
//输入：目标点的坐标,存放关节角度的数组
//输出：关节角度解及解的个数 0---无解（不能达到目标点）1---唯一解（杆共线）  2---两解
int CDrawPathDlg::InverseKinematic(fPoint point,fAngle angle[2])
{
	//最优解为角度变化量最小值

	float	tem1 = sqrt(point.x * point.x + point.y * point.y);
	float tem2 = m_iLength1 + m_iLength2;
				
	float	tem3 = sqrt(ptEndForCalc.x * ptEndForCalc.x + ptEndForCalc.y * ptEndForCalc.y);
	
	

	if ((tem1 > tem2)||(tem3 > tem2)) {



		AfxMessageBox("不能到达改位置");
		AfxEndThread( 0);
	}






	
	int iResultCount = 2 ;
	float angle2[2] ;

	AngleJudge();

	//point.x = (float)(point.x - m_iLength3 * cos(end_alpha));
	//point.y = (float)(point.y - m_iLength3 * sin(end_alpha));










	float temp1 = (float)(point.x*point.x + point.y*point.y - m_iLength1*m_iLength1 - m_iLength2*m_iLength2) ;
	float temp2 = (float)(2*m_iLength1*m_iLength2) ;
	float C2 = temp1/temp2 ;

	if(C2 > 1 || C2 < -1)
	{
		iResultCount = 0 ;
		return 0 ;
	}
	else if(C2 == 1)
	{
		angle2[0] = 0 ;
		iResultCount = 1 ;
	}
	else if(C2 == -1)
	{
		angle2[0] = 180 ;
		iResultCount = 1 ;
	}
	else
	{
		angle2[0] = (float)(acos(C2) / PI * 180) ;
		angle2[1] = -(float)(acos(C2) / PI * 180) ;
		iResultCount = 2 ;
	}




	float A = (float)(point.x*point.x + m_iLength1*m_iLength1 + point.y*point.y - m_iLength2*m_iLength2 ) ;
	float B = -2*point.x*m_iLength1 ;
	float C = 2*point.y*m_iLength1 ;

	float m = B*B + C*C ;
	float n = 2*A*B ;
	float p = A*A -C*C ;

	float temp3_1 = (float)(-n + sqrt(n*n - 4*m*p)) ;
	float temp3_2 = (float)(-n - sqrt(n*n - 4*m*p)) ;
	float temp4 = 2*m ;
	float C1_1 = temp3_1/temp4 ;
	float C1_2 = temp3_2/temp4 ;

	float angle1[4] ;
	angle1[0] = (float)(acos(C1_1) / PI * 180) ;
	angle1[1] = -(float)(acos(C1_1) / PI * 180) ;
	angle1[2] = (float)(acos(C1_2) / PI * 180) ;
	angle1[3] = -(float)(acos(C1_2) / PI * 180) ;

	for(int i = 0 ; i < iResultCount; i++)
	{
		angle[i].Angle2 = angle2[i] ;
		for(int j = 0 ; j < 4; j++)
		{
			fPoint target = ForwardKinematic(angle1[j], angle2[i]) ;
			if((bEqualForFloat(point.x, target.x)) && (bEqualForFloat(point.y, target.y)))
			{
				angle[i].Angle1 = angle1[j] ;
				angle[i].Angle3 = end_alpha - angle[i].Angle2 -  angle[i].Angle1;

			}
		}
		angle[i].Angle3 = end_alpha - angle[i].Angle2 -  angle[i].Angle1;
	}

	return iResultCount ;
}

void CDrawPathDlg::OnBUTTONControl() 
{
	GetDataFromControl() ;

	float tempX = (float)(ptEndForDraw.x - ptStartForDraw.x) / (float)(m_iControlPointNumber+1) ;
	float tempY = (float)(ptEndForDraw.y - ptStartForDraw.y) / (float)(m_iControlPointNumber+1) ;

	ControlPointForDraw[0].x = ptStartForDraw.x ;
	ControlPointForDraw[0].y = ptStartForDraw.y ;

	ControlPointForDraw[m_iControlPointNumber + 1].x = ptEndForDraw.x ;
	ControlPointForDraw[m_iControlPointNumber + 1].y = ptEndForDraw.y ;

	for(int i = 0 ; i < m_iControlPointNumber; i++)
	{
		ControlPointForDraw[i+1].x = (int)(ptStartForDraw.x + tempX * (i+1) + 0.5) ;
		ControlPointForDraw[i+1].y = (int)(ptStartForDraw.y + tempY * (i+1)+ 0.5) ;
	}

	for(int i = 0 ; i < m_iControlPointNumber + 2; i++)
	{
		ControlPointForCalc[i].x = (float)(ControlPointForDraw[i].x - ptCenter.x) ;
		ControlPointForCalc[i].y = (float)(-ControlPointForDraw[i].y + ptCenter.y) ;
//调试用
//	CString strTemp ;
//	strTemp.Format("for%.3f,%.3f,%.3f",ControlPointForCalc[i].x,ControlPointForCalc[i].y,alpha);
//	SetDlgItemText(IDC_EDIT1_dd,strTemp) ;

	}

	Invalidate(FALSE);
	
	

}

void CDrawPathDlg::OnBUTTONCalcAngle() 
{
	AfxBeginThread(MoveThread, this) ;
}

void CDrawPathDlg::running() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDrawPathDlg::OnChangeEditR() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDrawPathDlg::OnChangeEDITStartX2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDrawPathDlg::OnPic() 
{
	// TODO: Add your control notification handler code here
	
}

void CDrawPathDlg::OnStaticAlpha() 
{
	// TODO: Add your control notification handler code here
	
}

void CDrawPathDlg::OnChangeEDITALPHA() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDrawPathDlg::OnChangeEditAlpha() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}


void CDrawPathDlg::OnEnChangeEditStartx()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDrawPathDlg::OnEnChangeEditEndx()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
