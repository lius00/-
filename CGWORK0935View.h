
// CGWORK0935View.h : CCGWORK0935View 类的接口
//
#include "afxtempl.h";
#include "Line.h";
//#include "SetStyleDlg.h"
#pragma once

//class SetStyleDlg;
const int N=3;
const int npoints = 50;
typedef enum{
	TRF_NONE,TRF_TRANSlATE,TRF_ROTATE}Type_Transform;

class Point{
public:
	double x,y;
	inline Point operator =(Point p){x = p.x;y = p.y;return (*this);};
};

class Point_3D{
public:
	double x,y,z;
	Point_3D(){};
	Point_3D(double xCoord,double yCoord,double zCoord){x = xCoord;y=yCoord;z=zCoord;};
	~Point_3D(){};
};

class CCGWORK0935View : public CView
{
protected: // 仅从序列化创建
	CCGWORK0935View();
	DECLARE_DYNCREATE(CCGWORK0935View)
// 特性
public:
//	friend class SetStyleDlg;
	CCGWORK0935Doc* GetDocument() const;
	int currentx1,currenty1,currentx2,currenty2;
	int m_iPolyDotNumbers;//多边形顶点个数(边的个数)
    CPoint m_ptPolyDotArrays[50];//存储多边形的顶点
// 操作
public:
	//CGWORK0935Doc* GetDocument();
	//5利用鼠标完成直线段的绘制
	void DDALine(CDC *pDC, int x1, int y1, int x2, int y2, COLORREF color);
	CPoint m_StartPoint,m_EndPoint;//橡皮线的两个端点
	bool m_LButtonDown;//判断鼠标左键是否按下
	//6实现重画
	CArray<Line,Line> list;
	// Operations
	int m_DrawType;//绘图类型
	BOOL m_isDraw;//是否正在绘图
	HCURSOR m_Cursor;//光标资源句柄
	int m_nCount;
	CPoint m_Newpoint;
	CPoint P[N+1];
	Point newP[N+1];
	CPoint bezier[npoints+1];
	Point newbezier[npoints+1];

	CPoint points[6];
	int count;
	CPoint point[100];
	int isPress;
    CPoint start;
    CPoint end;

	Point_3D m_LBB;
	CPoint m_2dLbb;
	Point_3D m_LBT;
	CPoint m_2dLbt;
	Point_3D m_LFB;
	CPoint m_2dLfb;
	Point_3D m_LFT;
    CPoint m_2dLft;
	Point_3D m_RBB;
	CPoint m_2dRbb;
	Point_3D m_RBT;
	CPoint m_2dRbt;
	Point_3D m_RFB;
	CPoint m_2dRfb;
	Point_3D m_RFT;
	CPoint m_2dRft;

	double m_Proj_Matri[4][4];

	Type_Transform m_type_transform;
	double m_xStep;
	double m_yStep;
	double m_zStep;
	CPoint m_prevPoint;
	BOOL m_bLBDown;
	BOOL m_bRBDown;
	double m_RotateStep;

	int translate;
	int rotate;

	int m_RecRGB1;
	int m_RecRGB2;
	int m_RecRGB3;
	int m_EllRGB1;
	int m_EllRGB2;
	int m_EllRGB3;

	void edgeMarkFill(int n,CPoint *points);

	int m_length;
	int m_angle;

	int m_Bord1;
	int m_Bord2;
	int m_Bord3;
	int m_Back1;
	int m_Back2;
	int m_Back3;

	void ClearScreen();
	void DrawRect(CPoint P1,CPoint P2,CPoint P3,CPoint P4,COLORREF c);
	void DrawCubic();
	void From3dTo2d();
	void OnPerspective();

	void bez_to_points(Point P[],int n,Point pts[],int npoints);
	Point decas(Point p[],int n,double t);

/*	void MutiTransMarix(double a[1][4],double b[4][4],double MutiResult[1][4]);
	void TransPointToMarix(ThPoint &tp,double a[1][4]);
	void TransMarixToPoint(double a[1][4],ThPoint &tp);
	void MoveTrans(double x,double y,double z);
	void ShadowTrans(double degree);
	void RotateTrans(double degree,CString rc);
	void OnMove();
	void OnRotate();
	void OnSize(UINT nType, int cx, int cy);*/

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCGWORK0935View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEllipse();
	afx_msg void OnRectangle();
    void DrawLButtonDown(UINT nFlags, CPoint point);
    //鼠标绘图时鼠标移动消息处理函数
    void DrawMouseMove(UINT nFlags, CPoint point);
    //鼠标绘图时鼠标左键抬起消息处理函数
    void DrawLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPloygon();
	afx_msg void OnOptionCube();
	afx_msg void OnUpdatePloygon(CCmdUI *pCmdUI);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBezier();

/*	void MutiTransMarix(double a[1][4],double b[4][4],double MutiResult[1][4]);
	void TransPointToMarix(ThPoint &tp,double a[1][4]);
	void TransMarixToPoint(double a[1][4],ThPoint &tp);
	void MoveTrans(double x,double y,double z);
	void ShadowTrans(int degree);
	void RotateTrans(double degree,CString rc);
	*/

	afx_msg void OnCube();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On3drotatez();
	afx_msg void On3dtranslatex();
	afx_msg void On3drotatex();
	afx_msg void On3drotatey();
	afx_msg void On3dtranslatey();
	afx_msg void On3dtranslatez();
	afx_msg void OnSetstyle();
	afx_msg void OnSetdata();
	afx_msg void OnClear();
	afx_msg void OnSetpcolor();
};

#ifndef _DEBUG  // CGWORK0935View.cpp 中的调试版本
inline CCGWORK0935Doc* CCGWORK0935View::GetDocument() const
   { return reinterpret_cast<CCGWORK0935Doc*>(m_pDocument); }
#endif

