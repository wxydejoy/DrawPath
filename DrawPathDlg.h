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
	
	void GetDataFromControl();//�ӿؼ��н�������ֵȡ����
	void Calculate();//����˵�ĩ�˵�����
	void DrawRobot();//��������
	void Move() ;//�����˶�
	void Moving() ;//�����˶�����
	
	//ԭ����ϵ
	CPoint ptCenter ;//���ĵ�����

	CPoint pt1 ;//����1ĩ�˵������
	CPoint pt2 ;//����2ĩ�˵������
	CPoint pt3 ;//����3ĩ�˵������
	CPoint z1,z2,z3,z4;//צ�������


	fAngle angle_moving;

	CDrawPathDlg(CWnd* pParent = NULL);	// standard constructor

	CWnd* pWnd ;// ��ͼ�ؼ���ָ��
	CDC* pDC ;// �ؼ�����Ļ��ͼ�豸ָ��

	//=========================================================
	CRect rect;                  // �洢��ͼ�ؼ��Ļ�ͼ����
	//��ֹ��ͼ��˸
	CDC memDC;              // �ڴ��ͼ�豸
    CBitmap memBitmap;  // �����ڴ��ͼ��λͼ  
    CBitmap* pOldBmp;    // ���ݾɵ�λͼָ�� 
	//=========================================================

	float m_fAngle1 ;//�ؽڽǶ�1
	float m_fAngle2 ;//�ؽڽǶ�2
	float m_fAngle3 ;//�ؽڽǶ�3

	float end_alpha;//��̬��
	int m_iLength1 ;//�˳�1
	int m_iLength2 ;//�˳�2
    int m_iLength3 ;//�˳�3

	float brick_Length;//��鳤��
	float brick_width;//�����

	//������ 44-790
	//������90 - 700

	float m_fAngle1Max ;//�ؽڽǶ�1���ֵ
	float m_fAngle1Min ;//�ؽڽǶ�1��Сֵ

	float m_fAngle2Max ;//�ؽڽǶ�2���ֵ
	float m_fAngle2Min ;//�ؽڽǶ�2��Сֵ

	float m_fAngle3Max ;//�ؽڽǶ�3���ֵ
	float m_fAngle3Min ;//�ؽڽǶ�3��Сֵ

	static UINT MoveThread(void *param);//���ƹ����ռ��̺߳���

	bool m_bIsDrawing ;//�Ƿ����ڻ���
	bool m_bIsPause ;//�Ƿ���ͣ



	//����������Ϣ
	int	m_iRVaule;//��ɫֵ
	int	m_iGVaule;//��ɫֵ
	int	m_iBVaule;//��ɫֵ
	int	m_iWidth;//���ʿ��ֵ


	//����·����صı����ͺ���
	CPoint ptStartForDraw ;//���ڻ�ͼ��ʼ������
	CPoint ptEndForDraw ;//���ڻ�ͼ����������
	void DrawTestLine() ;//���ݽ�������յ�����߶�

	CPoint ptStartForCalc ;//���ڼ������ʼ������
	CPoint ptEndForCalc ;//���ڼ���Ľ���������
	void DrawToCalc() ;//����ͼ����ת��Ϊ��������
	void ShowCalcPoint() ;//������������ʾ�ڿؼ���
	void AngleJudge();//����Ƕȣ�-180-180��

	CPoint* ControlPointForDraw ;//���ڴ洢��ͼ�Ŀ��Ƶ�
	fPoint* ControlPointForCalc ;//���ڴ洢����Ŀ��Ƶ�
	fAngle* ControlAngleForMove ;//���ڴ洢�˶��Ŀ��Ƶ�

	int m_iControlPointNumber ;//���Ƶ�ĸ���


	//�ж������������Ƿ����
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
