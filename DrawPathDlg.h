// DrawPathDlg.h : header file
//

#if !defined(AFX_DRAWPATHDLG_H__B337D843_6DBA_4C13_9BBB_6B24235C0E53__INCLUDED_)
#define AFX_DRAWPATHDLG_H__B337D843_6DBA_4C13_9BBB_6B24235C0E53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct fPoint
{
	float x;
	float y ;
}fPoint ;

typedef struct fAngle
{
	float Angle1;
	float Angle2;
	float Angle3;
	float Angle1Max;
	float Angle1Min;
	float Angle2Max;
	float Angle2Min;
	float Angle3Max;
	float Angle3Min;
}fAngle ;

/////////////////////////////////////////////////////////////////////////////
// CDrawPathDlg dialog

class CDrawPathDlg : public CDialog
{
// Construction
public:
	
	void GetDataFromControl();//从控件中将变量的值取出来
	void Calculate();//计算杆的末端点坐标
	void DrawRobot();//绘制连杆
	void Move() ;//连杆运动
	void Moving() ;//连杆运动过程
	
	//原坐标系
	CPoint ptCenter ;//中心点坐标

	CPoint pt1 ;//连杆1末端点的坐标
	CPoint pt2 ;//连杆2末端点的坐标
	CPoint pt3 ;//连杆3末端点的坐标
	CPoint z1,z2,z3,z4;//爪子坐标点


	fAngle angle_moving;

	CDrawPathDlg(CWnd* pParent = NULL);	// standard constructor

	CWnd* pWnd ;// 绘图控件的指针
	CDC* pDC ;// 控件的屏幕绘图设备指针

	//=========================================================
	CRect rect;                  // 存储绘图控件的绘图区域
	//防止绘图闪烁
	CDC memDC;              // 内存绘图设备
    CBitmap memBitmap;  // 用于内存绘图的位图  
    CBitmap* pOldBmp;    // 备份旧的位图指针 
	//=========================================================

	float m_fAngle1 ;//关节角度1
	float m_fAngle2 ;//关节角度2
	float m_fAngle3 ;//关节角度3

	float end_alpha;//姿态角
	int m_iLength1 ;//杆长1
	int m_iLength2 ;//杆长2
    int m_iLength3 ;//杆长3

	float brick_Length;//物块长度
	float brick_width;//物块宽度

	//横坐标 44-790
	//纵坐标90 - 700

	float m_fAngle1Max ;//关节角度1最大值
	float m_fAngle1Min ;//关节角度1最小值

	float m_fAngle2Max ;//关节角度2最大值
	float m_fAngle2Min ;//关节角度2最小值

	float m_fAngle3Max ;//关节角度3最大值
	float m_fAngle3Min ;//关节角度3最小值

	static UINT MoveThread(void *param);//绘制工作空间线程函数

	bool m_bIsDrawing ;//是否正在绘制
	bool m_bIsPause ;//是否暂停



	//连杆其他信息
	int	m_iRVaule;//红色值
	int	m_iGVaule;//绿色值
	int	m_iBVaule;//蓝色值
	int	m_iWidth;//画笔宽度值


	//绘制路径相关的变量和函数
	CPoint ptStartForDraw ;//用于绘图起始点坐标
	CPoint ptEndForDraw ;//用于绘图结束点坐标
	void DrawTestLine() ;//根据结束点和终点绘制线段

	CPoint ptStartForCalc ;//用于计算的起始点坐标
	CPoint ptEndForCalc ;//用于计算的结束点坐标
	void DrawToCalc() ;//将绘图坐标转换为计算坐标
	void ShowCalcPoint() ;//将计算坐标显示在控件中
	void AngleJudge();//计算角度（-180-180）

	CPoint* ControlPointForDraw ;//用于存储绘图的控制点
	fPoint* ControlPointForCalc ;//用于存储计算的控制点
	fAngle* ControlAngleForMove ;//用于存储运动的控制点

	int m_iControlPointNumber ;//控制点的个数


	//判断两个浮点数是否相等
	bool bEqualForFloat(float a, float b) ;	
	fPoint ForwardKinematic(float Angle1, float Angle2 );
	int InverseKinematic(fPoint point,fAngle angle[2]) ;



// Dialog Data
	//{{AFX_DATA(CDrawPathDlg)
	enum { IDD = IDD_DRAWPATH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawPathDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDrawPathDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONReDraw();
	afx_msg void OnBUTTONContinue();
	afx_msg void OnBUTTONPause();
	afx_msg void OnBUTTONStopDrawWorkSpace();
	afx_msg void OnBUTTONDrawLine();
	afx_msg void OnBUTTONControl();
	afx_msg void OnBUTTONCalcAngle();
	afx_msg void running();
	afx_msg void OnChangeEditR();
	afx_msg void OnChangeEDITStartX2();
	afx_msg void OnPic();
	afx_msg void OnStaticAlpha();
	afx_msg void OnChangeEDITALPHA();
	afx_msg void OnChangeEditAlpha();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditStartx();
	afx_msg void OnEnChangeEditEndx();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWPATHDLG_H__B337D843_6DBA_4C13_9BBB_6B24235C0E53__INCLUDED_)
