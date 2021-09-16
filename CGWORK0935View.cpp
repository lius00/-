
// CGWORK0935View.cpp : CCGWORK0935View ���ʵ��
//

#include "stdafx.h"
#include "SetPColorDlg.h"
#include "SetDataDlg.h"
#include "SetStyleDlg.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CGWORK0935.h"
#endif

#include "CGWORK0935Doc.h"
#include "CGWORK0935View.h"

#include<vector>;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "math.h"
//���ܹ�������һ����Ÿ������͵Ķ��󣬼򵥵�˵��vector��һ���ܹ�����������͵Ķ�̬����
	struct node
{
//���ڶ���һ���ջ�ģ�����xs��ys���Ƕ�Ӧ��
	vector<int> xs;//����ζ��������
	vector<int> ys;//����ζ���������
	node* next;
};
	//������б�
	node* pl;
// CCGWORK0935View
	
IMPLEMENT_DYNCREATE(CCGWORK0935View, CView)

BEGIN_MESSAGE_MAP(CCGWORK0935View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCGWORK0935View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_ELLIPSE, &CCGWORK0935View::OnEllipse)
	ON_COMMAND(ID_RECTANGLE, &CCGWORK0935View::OnRectangle)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_CUBE, &CCGWORK0935View::OnOptionCube)
	ON_COMMAND(ID_PLOYGON, &CCGWORK0935View::OnPloygon)
	ON_COMMAND(ID_CUBE, &CCGWORK0935View::OnCube)
	ON_WM_MBUTTONDBLCLK()
	ON_COMMAND(ID_BEZIER, &CCGWORK0935View::OnBezier)
	ON_COMMAND(ID_CUBE, &CCGWORK0935View::OnCube)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_3DROTATEZ, &CCGWORK0935View::On3drotatez)
	ON_COMMAND(ID_3DTRANSLATEX, &CCGWORK0935View::On3dtranslatex)
	ON_COMMAND(ID_3DROTATEX, &CCGWORK0935View::On3drotatex)
	ON_COMMAND(ID_3DROTATEY, &CCGWORK0935View::On3drotatey)
	ON_COMMAND(ID_3DTRANSLATEY, &CCGWORK0935View::On3dtranslatey)
	ON_COMMAND(ID_3DTRANSLATEZ, &CCGWORK0935View::On3dtranslatez)
	ON_COMMAND(ID_SETSTYLE, &CCGWORK0935View::OnSetstyle)
	ON_COMMAND(ID_SETDATA, &CCGWORK0935View::OnSetdata)
	ON_COMMAND(ID_CLEAR, &CCGWORK0935View::OnClear)
	ON_COMMAND(ID_SETPCOLOR, &CCGWORK0935View::OnSetpcolor)
END_MESSAGE_MAP()

// CCGWORK0935View ����/����

CCGWORK0935View::CCGWORK0935View()
{
	// TODO: �ڴ˴���ӹ������
	count = 0;
	m_nCount = 0;
	currentx1=currenty1=0;
    currentx2=currenty2=100;
	m_iPolyDotNumbers=0;
	pl=new node;
	pl->next=NULL;
	isPress=0;
/*	cyClient = 100;
	cxClient = 100;
	//cpoints[8] = {{-1,0},{0,0},{0,-1},{-1,-1},{0,1},{1,0},{1,1},{-1,1}};
	cpoints[8];{(0,0),(0,1),(1,0),(1,1),(1,1),(1,1),(1,1),(2,2);};*/
	double Left_Bd = -50;
	double Right_Bd = 50;//x
	double Botton_Bd = -50;
	double Top_Bd = 50;//y
	double Back_Bd = -50;
	double Front_Bd = 50;//z

	m_LBB = Point_3D(Left_Bd,Back_Bd,Botton_Bd);
	m_LBT = Point_3D(Left_Bd,Back_Bd,Top_Bd);
	m_LFB = Point_3D(Left_Bd,Front_Bd,Botton_Bd);
	m_LFT = Point_3D(Left_Bd,Front_Bd,Top_Bd);
	m_RBB = Point_3D(Right_Bd,Back_Bd,Botton_Bd);
	m_RBT = Point_3D(Right_Bd,Back_Bd,Top_Bd);
	m_RFB = Point_3D(Right_Bd,Front_Bd,Botton_Bd);
	m_RFT = Point_3D(Right_Bd,Front_Bd,Top_Bd);

	m_length=1;
	m_angle=10;

	m_type_transform = TRF_NONE;
	m_xStep = m_length;
	m_yStep = m_length;
	m_zStep = m_length;
	m_prevPoint = 0;
	m_bLBDown = FALSE;
	m_bRBDown = FALSE;
	m_RotateStep = 0.05;

	m_RecRGB1=0;
	m_RecRGB2=0;
	m_RecRGB3=0;
	m_EllRGB1=0;
	m_EllRGB2=0;
	m_EllRGB3=0;

	m_Bord1=0;
	m_Bord2=0;
	m_Bord3=0;
	m_Back1=0;
	m_Back2=0;
	m_Back3=0;
}
 
CCGWORK0935View::~CCGWORK0935View()
{
}

BOOL CCGWORK0935View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

void CCGWORK0935View::edgeMarkFill(int n,CPoint *points)
{
	CClientDC dc(this);
	 int flag=0;//��־λ���ж���ͼ��������(1)������������(0)
	 COLORREF c1,c2;//c1Ϊ�߽�ɫ��c2Ϊ����ɫ
	 int maxX=0,minX=0,maxY=0,minY=0;
	 int i=0,j=0;
 
	 for(int i=0;i<m_iPolyDotNumbers;i++){
		 if(points[i].x>maxX)
			 maxX=points[i].x;
		 if(points[i].x<minX)
			 minX=points[i].x;
		 if(points[i].y>maxY)
			 maxY=points[i].y;
		 if(points[i].y<minY)
			 minY=points[i].y;
	 }
	 //������б߱�־���
	 for(i=minY+1;i<maxY;i++)
	 {
	  for(j=minX;j<=maxX;j++)
	  {
		  c2=RGB(0,0,0);
	   c1=c2;
	   c2=dc.GetPixel(j,i);//getpixel()����ֵΪ�����ص��RGBֵ
	   if(c1==RGB(0,0,0)&&c2==RGB(255,255,255))
		flag=!flag;
	   if(flag)
		   dc.SetPixel(j,i,RGB(0,0,0));
	  }
 
	  //Ϊ��ʵЧ�����ӳ�ʱ��Ŀ�ѭ��
	  for(int cc=0;cc<10000000;cc++);
 
	 }
}



/*
//********************
//����ĳ˷�
//*********************
void CCGWORK0935View::MutiTransMarix(double a[1][4],double b[4][4],double MutiResult[1][4])
{
 for(int i=0;i<4;i++) MutiResult[0][i] = 0;
 for(int i=0; i<1;i++)
  for(int j=0;j<4;j++)
   for(int k=0;k<4;k++)
    MutiResult[i][j] += a[i][k]*b[k][j];
}
//******************************
//������ת��Ϊ������ʽ(����)
//******************************
void CCGWORK0935View::TransPointToMarix(ThPoint &tp,double a[1][4])
{
 a[0][0] = tp.x;
 a[0][1] = tp.y;
 a[0][2] = tp.z;
 a[0][3] = 1;
}
//******************************
//������(����)ת��Ϊ��ά������ʽ
//******************************
void CCGWORK0935View::TransMarixToPoint(double a[1][4],ThPoint &tp)
{
 tp.x = a[0][0];
 tp.y = a[0][1];
 tp.z = a[0][2];
}
//******************************
//�������ƽ���㷨
//******************************
void CCGWORK0935View::MoveTrans(double x,double y,double z)
{
    double a[8][4],result[1][4];
 double moveMarix[4][4] =
 {
  {1,0,0,0},{0,1,0,0},
  {0,0,1,0},{x,y,z,1}
 };
 
     for(int i=0;i<8;i++)
 {
          TransPointToMarix(ppoints[i],a+i);
   MutiTransMarix(a+i,moveMarix,result);
   TransMarixToPoint(result,ppoints[i]);
 }
 ShadowTrans(-45);
}
//****************************************************
//�������б��ͶӰ�㷨(����ά����ת��Ϊ��ά����Ļ��ʾ)
//****************************************************
void CCGWORK0935View::ShadowTrans(double degree)
{
 double a[8][4],result[1][4];
 ThPoint pts[8];
 for(int i=0;i<8;i++)
 {
  pts[i].x = ppoints[i].x;
  pts[i].y = ppoints[i].y;
  pts[i].z = ppoints[i].z;
 }
 double shadowMarix[4][4] =
 {
  {1,0,0,0},{0,1,0,0},
  {cos(degree),sin(degree),0,0},{0,0,0,1}
 };
 
    for(int i=0;i<8;i++)
 {
          TransPointToMarix(pts[i],a+i);
   MutiTransMarix(a+i,shadowMarix,result);
   TransMarixToPoint(result,pts[i]);
 }
 for(int i=0;i<8;i++)
 {
  cpoints[i].x = (int)pts[i].x;
  cpoints[i].y = (int)pts[i].y;
 }
}
//***************************************
//��������ת�㷨����ת���Ŀ�����x,y��z��
//degree��ת�Ķ����� rc��ת����
//****************************************
void CCGWORK0935View::RotateTrans(double degree,CString rc)
{ 
    double a[8][4],result[1][4];
    int i = 0;
   
 if(rc == "z")
 {
  double xRotateMarix[4][4] =
   {
    {cos(degree*3.14/180),sin(degree*3.14/180),0,0},
    {-sin(degree*3.14/180),cos(degree*3.14/180),0,0},
    {0,0,1,0},{0,0,0,1},
   };
         for(i=0;i<8;i++)
   {
           TransPointToMarix(ppoints[i],a+i);
        MutiTransMarix(a+i,xRotateMarix,result);
     TransMarixToPoint(result,ppoints[i]);
   }
 }
 else if(rc == "x")
  {
  double yRotateMarix[4][4]=
   {
    {1,0,0,0},
    {0,cos(degree*3.14/180),sin(degree*3.14/180),0},
    {0,-sin(degree*3.14/180),cos(degree*3.14/180),0},
    {0,0,0,1}
   };
               for(i=0;i<8;i++)
   {
                   TransPointToMarix(ppoints[i],a+i);
            MutiTransMarix(a+i,yRotateMarix,result);
     TransMarixToPoint(result,ppoints[i]);
   }
     
  }
  else if(rc == "y")
  {
  double zRotateMarix[4][4]=
   {
    {cos(degree*3.14/180),0,-sin(degree*3.14/180),0},
    {0,1,0,0},
    {sin(degree*3.14/180),0,cos(degree*3.14/180),0},
    {0,0,0,1}
  };
         for(i=0;i<8;i++)
   {
           TransPointToMarix(ppoints[i],a+i);
        MutiTransMarix(a+i,zRotateMarix,result);
     TransMarixToPoint(result,ppoints[i]);
   }
     
  }
    ShadowTrans(-45);
}

/////////////////////////////////////////////////////////////////////////////
// CTransGraphicsView message handlers
//********************************
//��ȡ��Ļ�Ĵ�С
//********************************
void CCGWORK0935View::OnSize(UINT nType, int cx, int cy)
{
 CView::OnSize(nType, cx, cy);
 
 // TODO: Add your message handler code here
 cxClient = cx;
 cyClient = cy;
}
//********************************
//���ݶԻ�������Ĳ�������ƽ�Ʊ任
//********************************
void CCGWORK0935View::OnMove()
{
 // TODO: Add your command handler code here
CMoveDialog M_dlg;
 if(IDOK == M_dlg.DoModal())
 {
        MoveTrans(M_dlg.m_dx,M_dlg.m_dy,M_dlg.m_dz);
 }
 Invalidate();
 UpdateWindow();
}
//********************************
//���ݶԻ�������Ĳ���������ת�任
//********************************
void CCGWORK0935View::OnRotate()
{
 // TODO: Add your command handler code here
 RoateDialog BT_dlg;
 if(IDOK == BT_dlg.DoModal())
 {
      RotateTrans(BT_dlg.m_degree,BT_dlg.m_rc);
 }
 Invalidate();
 UpdateWindow();
}
*/
// CCGWORK0935View ����

void CCGWORK0935View::DrawRect(CPoint P1,CPoint P2,CPoint P3,CPoint P4,COLORREF c){
	CClientDC dc(this);

	dc.MoveTo(P1);
	dc.LineTo(P2);
	dc.LineTo(P3);
	dc.LineTo(P4);
	dc.LineTo(P1);
	CPen cPen;//��������
	dc.SetROP2(R2_COPYPEN);
cPen.CreatePen(PS_DASH,1,c);
dc.SelectObject(&cPen);
	dc.LineTo(P3);
//	dc.Rectangle(P1.x,P1.y,P3.x,P3.y);
cPen.DeleteObject();
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CBrush* oldbrush = dc.SelectObject(&brush);
	dc.SelectObject(&brush);
	dc.SelectObject(oldbrush);
	//dc.SelectObject(oldbrush);
}
void CCGWORK0935View::DrawCubic(){
	CClientDC dc(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(20,200,20));
//	CBrush* oldbrush = dc.SelectObject(&brush);
	dc.SelectObject(&brush);
	DrawRect(m_2dLbb,m_2dLbt,m_2dLft,m_2dLfb,RGB(20,100,20));
	
//	dc.SelectObject(&brush);
//	dc.SelectObject(oldbrush);
	DrawRect(m_2dRbb,m_2dRbt,m_2dRft,m_2dRfb,RGB(0,255,0));
	DrawRect(m_2dLbb,m_2dLbt,m_2dRbt,m_2dRbb,RGB(0,0,225));
	DrawRect(m_2dLfb,m_2dLft,m_2dRft,m_2dRfb,RGB(255,0,0));
	DrawRect(m_2dLbb,m_2dLfb,m_2dRfb,m_2dRbb,RGB(133,0,155));
	DrawRect(m_2dLbt,m_2dLft,m_2dRft,m_2dRbt,RGB(90,255,180));
}
void CCGWORK0935View::From3dTo2d(){
	m_2dLbb.x=m_LBB.x*m_Proj_Matri[0][0]+m_LBB.y*m_Proj_Matri[0][1]+m_LBB.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dLbb.y=m_LBB.x*m_Proj_Matri[1][0]+m_LBB.y*m_Proj_Matri[1][1]+m_LBB.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
	m_2dLbt.x=m_LBT.x*m_Proj_Matri[0][0]+m_LBT.y*m_Proj_Matri[0][1]+m_LBT.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dLbt.y=m_LBT.x*m_Proj_Matri[1][0]+m_LBT.y*m_Proj_Matri[1][1]+m_LBT.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
	m_2dLfb.x=m_LFB.x*m_Proj_Matri[0][0]+m_LFB.y*m_Proj_Matri[0][1]+m_LFB.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dLfb.y=m_LFB.x*m_Proj_Matri[1][0]+m_LFB.y*m_Proj_Matri[1][1]+m_LFB.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
	m_2dLft.x=m_LFT.x*m_Proj_Matri[0][0]+m_LFT.y*m_Proj_Matri[0][1]+m_LFT.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dLft.y=m_LFT.x*m_Proj_Matri[1][0]+m_LFT.y*m_Proj_Matri[1][1]+m_LFT.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];

	m_2dRbb.x=m_RBB.x*m_Proj_Matri[0][0]+m_RBB.y*m_Proj_Matri[0][1]+m_RBB.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dRbb.y=m_RBB.x*m_Proj_Matri[1][0]+m_RBB.y*m_Proj_Matri[1][1]+m_RBB.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
	m_2dRbt.x=m_RBT.x*m_Proj_Matri[0][0]+m_RBT.y*m_Proj_Matri[0][1]+m_RBT.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dRbt.y=m_RBT.x*m_Proj_Matri[1][0]+m_RBT.y*m_Proj_Matri[1][1]+m_RBT.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
	m_2dRfb.x=m_RFB.x*m_Proj_Matri[0][0]+m_RFB.y*m_Proj_Matri[0][1]+m_RFB.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dRfb.y=m_RFB.x*m_Proj_Matri[1][0]+m_RFB.y*m_Proj_Matri[1][1]+m_RFB.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
	m_2dRft.x=m_RFT.x*m_Proj_Matri[0][0]+m_RFT.y*m_Proj_Matri[0][1]+m_RFT.z*m_Proj_Matri[0][2]+m_Proj_Matri[0][3];
	m_2dRft.y=m_RFT.x*m_Proj_Matri[1][0]+m_RFT.y*m_Proj_Matri[1][1]+m_RFT.z*m_Proj_Matri[1][2]+m_Proj_Matri[1][3];
}
void CCGWORK0935View::ClearScreen(){//����
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}
void CCGWORK0935View::OnPerspective(){//͸��ͶӰ
//	ClearScreen();
	double x0=2;
	double y0=1;
	double d=2;
	m_Proj_Matri[0][0]=1; m_Proj_Matri[0][1]=0; m_Proj_Matri[0][2]=x0/d;  m_Proj_Matri[0][3]=0;
	m_Proj_Matri[1][0]=0; m_Proj_Matri[1][1]=1; m_Proj_Matri[1][2]=y0/d;  m_Proj_Matri[1][3]=0;
	m_Proj_Matri[2][0]=0; m_Proj_Matri[2][1]=0; m_Proj_Matri[2][2]=0;      m_Proj_Matri[2][3]=0;
	m_Proj_Matri[3][0]=0; m_Proj_Matri[3][1]=0; m_Proj_Matri[3][2]=1.0/d;  m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
}
void CCGWORK0935View::OnDraw(CDC* pDC)
{
	CCGWORK0935Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CClientDC dc(this);
	CPen cPen;//��������
cPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
dc.SelectObject(&cPen);///////////////////////////////////////
//dc.Polygon(m_ptPolyDotArrays,m_iPolyDotNumbers);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,0));
//	CBrush* oldbrush = dc.SelectObject(&brush);
	dc.SelectObject(&brush);
//	dc.SelectObject(oldbrush);
//	dc.Rectangle(0,0,100,100);
	cPen.DeleteObject();
	brush.DeleteObject();

	//OnPerspective();
	//OnCube(p);
	//DDALine(pDC,10,10,50,100,RGB(255,0,0));
	//pDC->Rectangle(currentx1,currenty1,currentx2,currenty2);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CCGWORK0935View::DDALine(CDC *pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	double dx,dy,e,x,y;
	dx = x2 -x1;
	dy = y2- y1;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx):fabs(dy);
	dx/=e;
	dy/=e;
	x = x1;
	y = y1;
	for (int i=1;i<=e;i++)
	{
		pDC->SetPixel((int)(x+0.5),(int)(y+0.5),color);
		x+=dx;
		y+=dy;
	}
}


// CCGWORK0935View ��ӡ


void CCGWORK0935View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCGWORK0935View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCGWORK0935View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCGWORK0935View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CCGWORK0935View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCGWORK0935View ���

#ifdef _DEBUG
void CCGWORK0935View::AssertValid() const
{
	CView::AssertValid();
}

void CCGWORK0935View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGWORK0935Doc* CCGWORK0935View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGWORK0935Doc)));
	return (CCGWORK0935Doc*)m_pDocument;
}
#endif //_DEBUG


// CCGWORK0935View ��Ϣ�������


void CCGWORK0935View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//5����������ֱ�߶εĻ���
	/*if (m_LButtonDown){
		CDC* pDC = this->GetDC();//�����豸��������
		pDC->SetROP2(R2_NOT);//���û�ͼģʽΪR2_NOT
		//���»���ǰһ������ƶ���Ϣ���������Ƶ�ֱ�߶�
		//��Ϊ��ͼģʽ��ԭ�򣬽�����ǲ����˸��߶�
		DDALine(pDC,m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y,RGB(0,0,0));
		//�����µ�ֱ�߶�
		DDALine(pDC,m_StartPoint.x,m_StartPoint.y,point.x,point.y,RGB(0,0,0));
		//�����µ�ֱ�߶��յ�
		m_EndPoint = point;
	}
	
	CView::OnMouseMove(nFlags, point);*/
	/*
	if(m_nCount>0&&m_nCount<=3){
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(P[m_nCount-1]);
		dc.LineTo(m_Newpoint);
		dc.MoveTo(P[m_nCount-1]);
		dc.LineTo(point);
		m_Newpoint = point;//��ŵ�ǰ���λ��
	}*/
	if (m_isDraw)
		this->DrawMouseMove(nFlags,point);
	CView::OnMouseMove(nFlags, point);

}
void CCGWORK0935View::bez_to_points(Point P[],int n,Point pts[],int npoints){//�ƽ������ߵ���������pts
	double t=0,delta;
	delta=1.0/(double)npoints;
	for(int i=0;i<=npoints;i++){
		pts[i]=decas(P,n,t);

		t+=delta;
	}
}

Point CCGWORK0935View::decas(Point P[],int n,double t){
	int m,i;
	Point *R,*Q,P0;
	R = new Point[n+1];//���ƶ���
	Q = new Point[n+1];
	for(i =0;i<=n;i++)
		R[i]=P[i];
	for(m=n;m>0;m--){
		for(i=0;i<=m-1;i++){
			Q[i].x = R[i].x+t*(R[i+1].x-R[i].x);
			Q[i].y = R[i].y+t*(R[i+1].y-R[i].y);
		}
		for(i=0;i<=m-1;i++){
			R[i]=Q[i];
		}
	}
	P0=R[0];
	delete R;
	delete Q;
	return (P0);
}



BOOL CCGWORK0935View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CCGWORK0935View::OnMove(int x, int y)
{

	CView::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
}


void CCGWORK0935View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDblClk(nFlags, point);
}


void CCGWORK0935View::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	// TODO: Add your message handler code here and/or call default
	//5����������ֱ�߶εĻ���
/*	this->SetCapture();//��׽���
	//���ÿ�ʼ�����ֹ�㣬��ʱΪͬһ��
	m_StartPoint = point;//ֱ�߶���㣬�õ��ڻ�ͼ�����в���
	m_EndPoint = point;//ֱ�߶��յ�
	m_LButtonDown = true;//��������������
	
	CView::OnLButtonDown(nFlags, point);
	//���ڻ�ͼ״̬ʱ��������ͼʱ���������´�����*/
/*	P[m_nCount] = point;
	m_Newpoint = point;
	m_nCount = (++m_nCount)%4;*/
/*	(pl->next->xs).push_back(point.x);
    (pl->next->ys).push_back(point.y);*/
	if (m_isDraw)
		this->DrawLButtonDown(nFlags,point);
	CView::OnLButtonDown(nFlags, point);

}


void CCGWORK0935View::OnLButtonUp(UINT nFlags, CPoint point)
{
/*	ReleaseCapture();//�ͷ����
	m_LButtonDown = false;//������̧�𣬻�ͼ����
	
	//������󲢼����б�
	Line line;
	line.x1 = m_StartPoint.x;
	line.y1 = m_StartPoint.y;
	line.x2 = m_EndPoint.x;
	line.y2 = m_EndPoint.y;
	list.Add(line);//���ͼԪ��ͼԪ�б���

	CView::OnLButtonUp(nFlags, point);*/
	//���ڻ�ͼ״̬ʱ��������ͼʱ������̧������
	ReleaseCapture();//�ͷ����

/*	int i;
	if(m_nCount ==0){
		CClientDC dc(this);
		for(i=0;i<4;i++){
			newP[i].x=P[i].x;
			newP[i].y = P[i].y;
		}
		bez_to_points(newP,N,newbezier,npoints);
		for(int i = 0;i<=npoints;i++){
			bezier[i].x = (int)newbezier[i].x;
			bezier[i].y = (int)newbezier[i].y;
		}
		dc.Polyline(bezier,npoints+1);
	}*/
	m_LButtonDown = false;//������̧�𣬻�ͼ����
	if (m_isDraw)
		this->DrawLButtonUp(nFlags,point);
	CView::OnLButtonUp(nFlags, point);

}


void CCGWORK0935View::OnEllipse()
{
	// TODO: �ڴ���������������
	/*CClientDC dc(this);
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP1
	CBrush brush,*oldbrush;
	brush.CreatePatternBrush(&bm);
	oldbrush = dc.SelectObject(&brush);
	
	dc.Ellipse(20,20,100,100);
	dc.SelectObject(oldbrush);*/
	m_DrawType = 3;//3��ʾ������Բ����
	m_isDraw = true;//��ǰ���ڻ�ͼ״̬

}


void CCGWORK0935View::OnRectangle()
{
	m_DrawType = 4;//4��ʾ���ƾ�������
	m_isDraw = true;//��ǰ���ڻ�ͼ״̬
}

void CCGWORK0935View::DrawLButtonDown(UINT nFlags, CPoint point)
{
	SetCursor(m_Cursor);//����ʹ�ù����Դ

	this->SetCapture();//��׽���
	if(m_DrawType==6){
		P[m_nCount] = point;
	    m_Newpoint = point;
	    m_nCount = (++m_nCount)%4;
	}
	if(m_DrawType==5){
		//����λ���
		ASSERT(m_iPolyDotNumbers<50);
CClientDC dc(this);
m_ptPolyDotArrays[m_iPolyDotNumbers]=point;
//����Ĵ�����Ƶ�ǰ����ĵ�����ɫ���
dc.Ellipse(m_ptPolyDotArrays[m_iPolyDotNumbers].x-2,m_ptPolyDotArrays[m_iPolyDotNumbers].y-2,m_ptPolyDotArrays[m_iPolyDotNumbers].x+2,m_ptPolyDotArrays[m_iPolyDotNumbers].y+2);
CRect rect(m_ptPolyDotArrays[m_iPolyDotNumbers].x-3,m_ptPolyDotArrays[m_iPolyDotNumbers].y-3,m_ptPolyDotArrays[m_iPolyDotNumbers].x+3,m_ptPolyDotArrays[m_iPolyDotNumbers].y+3);
CBrush brush(RGB(0,0,255));
dc.FillRect(rect,&brush);
 
++m_iPolyDotNumbers;
 
//����Ĵ�����Ƴ���ǰ�㣨���һ���㣩����ĵ��ú�ɫ���
for (int i=0;i<m_iPolyDotNumbers-1;i++)
{
dc.Ellipse(m_ptPolyDotArrays[i].x-2,m_ptPolyDotArrays[i].y-2,m_ptPolyDotArrays[i].x+2,m_ptPolyDotArrays[i].y+2);
CRect rect(m_ptPolyDotArrays[i].x-3,m_ptPolyDotArrays[i].y-3,m_ptPolyDotArrays[i].x+3,m_ptPolyDotArrays[i].y+3);
CBrush brush(RGB(255,0,0));
dc.FillRect(rect,&brush);
}

if (m_iPolyDotNumbers>2)
{
		CClientDC dc(this);
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP1
	CBrush brush,*oldbrush;
	brush.CreatePatternBrush(&bm);
	oldbrush = dc.SelectObject(&brush);
//	dc.SelectObject(oldbrush);
CPen cPen;//��������
cPen.CreatePen(PS_SOLID,1,RGB(m_Bord1,m_Bord2,m_Bord3));
dc.SelectObject(&cPen);///////////////////////////////////////
dc.Polygon(m_ptPolyDotArrays,m_iPolyDotNumbers);
cPen.DeleteObject();
}
	//	(pl->next->xs).push_back(point.x);
      //  (pl->next->ys).push_back(point.y
//edgeMarkFill(m_iPolyDotNumbers,m_ptPolyDotArrays);
    	
	}
	if(m_DrawType==7){
		m_bLBDown = TRUE;
		m_prevPoint = point;
	}
	//���ÿ�ʼ�����ֹ�㣬��ʱΪͬһ��
	m_StartPoint = point;
	m_EndPoint = point;
	m_LButtonDown = true;//��������������
}

//����ͼʱ����ƶ�������
void CCGWORK0935View::DrawMouseMove(UINT nFlags, CPoint point)
{
	SetCursor(m_Cursor);//����ʹ�ù����Դ
	CClientDC dc(this);//�����豸��������
	

	//�ж�����ƶ���ͬʱ���������£�����Ҫ���Ƶ���ֱ�߶�
	if (m_LButtonDown && m_DrawType == 1)
	{
		dc.SetROP2(R2_NOT);//���û�ͼģʽΪR2_NOT
		//���»���ǰһ������ƶ���Ϣ���������Ƶ�ֱ�߶�
		//��Ϊ��ͼģʽ��ԭ�򣬽���ǲ����˸��߶�
		dc.MoveTo(m_StartPoint);
		dc.LineTo(m_EndPoint);
		//�����µ�ֱ�߶�
		dc.MoveTo(m_StartPoint);
		dc.LineTo(point);
		//�����µ�ֱ�߶��յ�
		m_EndPoint = point;
	}
	if(m_LButtonDown && m_DrawType == 7){
		int delta = 0;
		double c;
		double s;
		double x,y,Alpha,L;
		switch(m_type_transform){
		case TRF_NONE:
			break;
		case TRF_ROTATE:
			if(m_bLBDown){
				ClearScreen();
				delta = point.y-m_prevPoint.y;
				m_prevPoint=point;
				c=cos(delta*m_RotateStep);
				s=sin(delta*m_RotateStep);
				x=m_LBB.x;y=m_LBB.y;
				m_LBB.x=x*c-y*s;m_LBB.y=x*s-y*c;
				x=m_LBT.x;y=m_LBT.y;
				m_LBT.x=x*c-y*s;m_LBT.y=x*s-y*c;
				x=m_LFB.x;y=m_LFB.y;
				m_LFB.x=x*c-y*s;m_LFB.y=x*s-y*c;
				x=m_LFT.x;y=m_LFT.y;
				m_LFT.x=x*c-y*s;m_LFT.y=x*s-y*c;

				x=m_RBB.x;y=m_RBB.y;
				m_RBB.x=x*c-y*s;m_RBB.y=x*s-y*c;
				x=m_RBT.x;y=m_RBT.y;
				m_RBT.x=x*c-y*s;m_RBT.y=x*s-y*c;
				x=m_RFB.x;y=m_RFB.y;
				m_RFB.x=x*c-y*s;m_RFB.y=x*s-y*c;
				x=m_RFT.x;y=m_RFT.y;
				m_RFT.x=x*c-y*s;m_RFT.y=x*s-y*c;
				L=2/sqrt(3.0);
				Alpha=20;
				Alpha*=3.1415926/180;
				c=cos(Alpha);
				s=sin(Alpha);
				m_Proj_Matri[0][0]=1;  m_Proj_Matri[0][1]=0;  m_Proj_Matri[0][2]=L*c;  m_Proj_Matri[0][3]=0;
	            m_Proj_Matri[0][0]=0;  m_Proj_Matri[0][1]=1;  m_Proj_Matri[0][1]=L*s;  m_Proj_Matri[0][3]=0;
	            m_Proj_Matri[0][0]=0;  m_Proj_Matri[0][1]=0;  m_Proj_Matri[0][1]=0;  m_Proj_Matri[0][3]=0;
	            m_Proj_Matri[0][0]=0;  m_Proj_Matri[0][1]=0;  m_Proj_Matri[0][1]=0;  m_Proj_Matri[0][3]=1;
	            From3dTo2d();
	            DrawCubic();
			}
			break;

		}
	}
	if (m_LButtonDown && (m_DrawType == 2 || m_DrawType ==3))
{
	dc.SetROP2(R2_NOT);//���û�ͼģʽΪR2_NOT
	//����ǰһ�κ�������ʱ���Ƶ���Բ�߽���
	dc.Arc(m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y,
		m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y);
	dc.Arc(m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y,
		m_EndPoint.x,m_EndPoint.y,m_StartPoint.x,m_StartPoint.y);
	//�����µ���Բ�߽���
	dc.Arc(m_StartPoint.x,m_StartPoint.y,point.x,point.y,
		m_StartPoint.x,m_StartPoint.y,point.x,point.y);
	dc.Arc(m_StartPoint.x,m_StartPoint.y,point.x,point.y,
		point.x,point.y,m_StartPoint.x,m_StartPoint.y);
	//�����µ���ֹ��
	m_EndPoint = point;
}
	if (m_LButtonDown && m_DrawType == 4)
{
	
	dc.SetROP2(R2_NOT);//���û�ͼģʽΪR2_NOT
	//����ǰһ�κ�������ʱ���Ƶľ��α߽���
	dc.MoveTo(m_StartPoint);
	dc.LineTo(m_StartPoint.x,m_EndPoint.y);
	dc.LineTo(m_EndPoint);
	dc.LineTo(m_EndPoint.x,m_StartPoint.y);
	dc.LineTo(m_StartPoint);


	//�����µľ��α߽���
	dc.MoveTo(m_StartPoint);
	dc.LineTo(m_StartPoint.x,point.y);
	dc.LineTo(point);
	dc.LineTo(point.x,m_StartPoint.y);
	dc.LineTo(m_StartPoint);
	//�����µ���ֹ��
	m_EndPoint = point;
}

	if(m_LButtonDown && m_DrawType == 6){
		if(m_nCount>0&&m_nCount<=3){
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(P[m_nCount-1]);
		dc.LineTo(m_Newpoint);
		dc.MoveTo(P[m_nCount-1]);
		dc.LineTo(point);
		m_Newpoint = point;//��ŵ�ǰ���λ��
	}
	}

}

//����ͼʱ������̧������
void CCGWORK0935View::DrawLButtonUp(UINT nFlags, CPoint point)
{
	SetCursor(m_Cursor);//����ʹ�ù����Դ
	ReleaseCapture();//�ͷ����
	CClientDC dc(this);//�����豸��������

	//���Ƶ���ֱ�߶�
	if (m_DrawType == 1)
	{
		//��������Ҫ���Ƶ�ֱ�߶�
		dc.MoveTo(m_StartPoint);
		dc.LineTo(m_EndPoint);
	}
	if (m_DrawType == 2)
{

	//������Բ�߽���
	dc.Arc(m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y,
		m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y);
	dc.Arc(m_StartPoint.x,m_StartPoint.y,m_EndPoint.x,m_EndPoint.y,
		m_EndPoint.x,m_EndPoint.y,m_StartPoint.x,m_StartPoint.y);
}

//���Ƶ�����Բ����
if (m_DrawType == 3)
{
	//������Բ����
	CClientDC dc(this);
CPen cPen;//��������
cPen.CreatePen(PS_SOLID,1,RGB(m_EllRGB1,m_EllRGB2,m_EllRGB3));
dc.SelectObject(&cPen);///////////////////////////////////////
/*	
    CClientDC dc(this);   
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP1
	CBrush brush,*oldbrush;
	brush.CreatePatternBrush(&bm);
	oldbrush = dc.SelectObject(&brush);
	dc.SelectObject(oldbrush);*/
	//dc.Ellipse(20,20,100,100);
	
	dc.Ellipse(m_StartPoint.x,m_StartPoint.y,
		m_EndPoint.x,m_EndPoint.y);
//	dc.SelectObject(oldbrush);
	cPen.DeleteObject();
}
if (m_DrawType == 4)
{
	int c;
	//ȷ��m_StartPointȷʵΪ������������Ͻ�
	//m_EndPointȷʵ�Ǿ�����������½�
	if (m_StartPoint.x > m_EndPoint.x)
	{
		c = m_StartPoint.x;
		m_StartPoint.x = m_EndPoint.x;
		m_EndPoint.x = c;
	}
	if (m_StartPoint.y > m_EndPoint.y)
	{
		c = m_StartPoint.y;
		m_StartPoint.y = m_EndPoint.y;
		m_EndPoint.y = c;
	}
			CClientDC dc(this);
CPen cPen;//��������
cPen.CreatePen(PS_SOLID,1,RGB(m_RecRGB1,m_RecRGB2,m_RecRGB3));
dc.SelectObject(&cPen);///////////////////////////////////////
	//���ƾ�������
/*	CClientDC dc(this);
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP1
	CBrush brush,*oldbrush;
	brush.CreatePatternBrush(&bm);
	oldbrush = dc.SelectObject(&brush);*/
	dc.Rectangle(m_StartPoint.x,m_StartPoint.y,
		m_EndPoint.x+1,m_EndPoint.y+1);
//	dc.SelectObject(oldbrush);
	cPen.DeleteObject();
}
if(m_DrawType==6){
	int i;
	if(m_nCount ==0){
		CClientDC dc(this);
		for(i=0;i<4;i++){
			newP[i].x=P[i].x;
			newP[i].y = P[i].y;
		}
		bez_to_points(newP,N,newbezier,npoints);
		for(int i = 0;i<=npoints;i++){
			bezier[i].x = (int)newbezier[i].x;
			bezier[i].y = (int)newbezier[i].y;
		}
		dc.Polyline(bezier,npoints+1);
	}
}
if(m_DrawType==7){
		m_bLBDown = FALSE;
		m_prevPoint = point;
	}

}

void CCGWORK0935View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_xStep=m_length;
	m_yStep=m_length;
	m_zStep=m_length;
	int delta = 1;
	if(translate == 0){
	if(nChar == 'L'){
				ClearScreen();
				//���¾������ݲ�������
				m_LBB.x-=delta*(int)m_xStep,0;
				m_LBT.x-=delta*(int)m_xStep,0;
				m_LFB.x-=delta*(int)m_xStep,0;
				m_LFT.x-=delta*(int)m_xStep,0;
				m_RBB.x-=delta*(int)m_xStep,0;
				m_RBT.x-=delta*(int)m_xStep,0;
				m_RFB.x-=delta*(int)m_xStep,0;
				m_RFT.x-=delta*(int)m_xStep,0;
				From3dTo2d();
				DrawCubic();
			}
	if(nChar == 'A'){
		ClearScreen();
				//���¾������ݲ�������
				m_LBB.x+=delta*(int)m_xStep,0;
				m_LBT.x+=delta*(int)m_xStep,0;
				m_LFB.x+=delta*(int)m_xStep,0;
				m_LFT.x+=delta*(int)m_xStep,0;
				m_RBB.x+=delta*(int)m_xStep,0;
				m_RBT.x+=delta*(int)m_xStep,0;
				m_RFB.x+=delta*(int)m_xStep,0;
				m_RFT.x+=delta*(int)m_xStep,0;
				From3dTo2d();
				DrawCubic();
	}
	}
	if(translate==1){
	if(nChar == 'L'){
				ClearScreen();
				//���¾������ݲ�������
				m_LBB.y-=delta*(int)m_yStep,0;
				m_LBT.y-=delta*(int)m_yStep,0;
				m_LFB.y-=delta*(int)m_yStep,0;
				m_LFT.y-=delta*(int)m_yStep,0;
				m_RBB.y-=delta*(int)m_yStep,0;
				m_RBT.y-=delta*(int)m_yStep,0;
				m_RFB.y-=delta*(int)m_yStep,0;
				m_RFT.y-=delta*(int)m_yStep,0;
				From3dTo2d();
				DrawCubic();
			}
			if(nChar == 'A'){
				ClearScreen();
				//���¾������ݲ�������
				m_LBB.y+=delta*(int)m_yStep,0;
				m_LBT.y+=delta*(int)m_yStep,0;
				m_LFB.y+=delta*(int)m_yStep,0;
				m_LFT.y+=delta*(int)m_yStep,0;
				m_RBB.y+=delta*(int)m_yStep,0;
				m_RBT.y+=delta*(int)m_yStep,0;
				m_RFB.y+=delta*(int)m_yStep,0;
				m_RFT.y+=delta*(int)m_yStep,0;
				From3dTo2d();
				DrawCubic();
			}
	}
	if(translate == 2){
          if(nChar == 'L'){
				ClearScreen();
				//���¾������ݲ�������
				m_LBB.z+=delta*(int)m_zStep,0;
				m_LBT.z+=delta*(int)m_zStep,0;
				m_LFB.z+=delta*(int)m_zStep,0;
				m_LFT.z+=delta*(int)m_zStep,0;
				m_RBB.z+=delta*(int)m_zStep,0;
				m_RBT.z+=delta*(int)m_zStep,0;
				m_RFB.z+=delta*(int)m_zStep,0;
				m_RFT.z+=delta*(int)m_zStep,0;
				From3dTo2d();
				DrawCubic();
			}
			if(nChar == 'A'){
				ClearScreen();
				//���¾������ݲ�������
				m_LBB.z+=delta*(int)m_zStep,0;
				m_LBT.z+=delta*(int)m_zStep,0;
				m_LFB.z+=delta*(int)m_zStep,0;
				m_LFT.z+=delta*(int)m_zStep,0;
				m_RBB.z+=delta*(int)m_zStep,0;
				m_RBT.z+=delta*(int)m_zStep,0;
				m_RFB.z+=delta*(int)m_zStep,0;
				m_RFT.z+=delta*(int)m_zStep,0;
				From3dTo2d();
				DrawCubic();
			}
	}
	if(rotate==0){
		if(nChar == 'A'){
			ClearScreen();
	double L = 2/sqrt(3.0);
	double Alpha = m_angle;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][1]=1;  m_Proj_Matri[1][0]=0;  m_Proj_Matri[2][0]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][2]=0;  m_Proj_Matri[1][1]=L*c;   m_Proj_Matri[2][1]=L*s;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][3]=0;    m_Proj_Matri[1][2]=-L*s;     m_Proj_Matri[2][2]=L*c;    m_Proj_Matri[3][2]=0;
	m_Proj_Matri[0][4]=0;    m_Proj_Matri[1][3]=0;     m_Proj_Matri[2][3]=0;    m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
		}
		if(nChar == 'L'){
			ClearScreen();
	double L = 2/sqrt(3.0);
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][1]=-1;  m_Proj_Matri[1][0]=0;  m_Proj_Matri[2][0]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][2]=0;  m_Proj_Matri[1][1]=-L*c;   m_Proj_Matri[2][1]=-L*s;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][3]=0;    m_Proj_Matri[1][2]=L*s;     m_Proj_Matri[2][2]=-L*c;    m_Proj_Matri[3][2]=0;
	m_Proj_Matri[0][4]=0;    m_Proj_Matri[1][3]=0;     m_Proj_Matri[2][3]=0;    m_Proj_Matri[3][3]=-1;
	From3dTo2d();
	DrawCubic();
		}
	}
	if(rotate==1){
		if(nChar == 'A'){
		ClearScreen();
	double L = 2/sqrt(3.0);
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][1]=L*c;  m_Proj_Matri[1][0]=0;  m_Proj_Matri[2][0]=L*s;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][2]=0;  m_Proj_Matri[1][1]=1;   m_Proj_Matri[2][1]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][3]=L*s;    m_Proj_Matri[1][2]=0;     m_Proj_Matri[2][2]=L*c;    m_Proj_Matri[3][2]=0;
	m_Proj_Matri[0][4]=0;    m_Proj_Matri[1][3]=0;     m_Proj_Matri[2][3]=0;    m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
	}
		if(nChar == 'L'){
		ClearScreen();
	double L = 2/sqrt(3.0);
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][1]=-L*c;  m_Proj_Matri[1][0]=0;  m_Proj_Matri[2][0]=-L*s;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][2]=0;  m_Proj_Matri[1][1]=-1;   m_Proj_Matri[2][1]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][3]=-L*s;    m_Proj_Matri[1][2]=0;     m_Proj_Matri[2][2]=-L*c;    m_Proj_Matri[3][2]=0;
	m_Proj_Matri[0][4]=0;    m_Proj_Matri[1][3]=0;     m_Proj_Matri[2][3]=0;    m_Proj_Matri[3][3]=-1;
	From3dTo2d();
	DrawCubic();
	}
	}
	if(rotate==2){
		if(nChar == 'A'){
		ClearScreen();
	double L = 1;//2/sqrt(3.0);
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][1]=L*c;  m_Proj_Matri[1][0]=-L*s;  m_Proj_Matri[2][0]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][2]=L*s;  m_Proj_Matri[1][1]=L*c;   m_Proj_Matri[2][1]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][3]=0;    m_Proj_Matri[1][2]=0;     m_Proj_Matri[2][2]=1;    m_Proj_Matri[3][2]=0;
	m_Proj_Matri[0][4]=0;    m_Proj_Matri[1][3]=0;     m_Proj_Matri[2][3]=0;    m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
	}
		if(nChar == 'L'){
		ClearScreen();
	double L = 1;//2/sqrt(3.0);
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][1]=-L*c;  m_Proj_Matri[1][0]=L*s;  m_Proj_Matri[2][0]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][2]=-L*s;  m_Proj_Matri[1][1]=-L*c;   m_Proj_Matri[2][1]=0;    m_Proj_Matri[3][1]=0;
	m_Proj_Matri[0][3]=0;    m_Proj_Matri[1][2]=0;     m_Proj_Matri[2][2]=-1;    m_Proj_Matri[3][2]=0;
	m_Proj_Matri[0][4]=0;    m_Proj_Matri[1][3]=0;     m_Proj_Matri[2][3]=0;    m_Proj_Matri[3][3]=-1;
	From3dTo2d();
	DrawCubic();
	}
	}

}


void CCGWORK0935View::OnPloygon()
{
	// TODO: �ڴ���������������
	m_DrawType = 5;//4��ʾ���ƾ�������
	m_isDraw = true;//��ǰ���ڻ�ͼ״̬
/*	CDC *pDC=GetDC();
		node *q=pl->next;
      //�Ӷ�����б������ÿһ�������//ÿ���ڵ����һ�������//�ڵ���Ķ�Ӧxs��ys���Ƕ���θ�����
		while(q)
		{
			//����νڵ���ֻ��һ����
			if(q->xs.size()<2)
			{
				q=q->next;
				continue;
			}
			//�ж����
			for(int i=0;i<(q->xs.size())-1;i++)
			{
				pDC->MoveTo(q->xs[i],q->ys[i]);
				pDC->LineTo(q->xs[i+1],q->ys[i+1]);
			}
			//���һ����͵�һ��������
			pDC->MoveTo(q->xs[q->xs.size()-1],q->ys[q->xs.size()-1]);
			pDC->LineTo(q->xs[0],q->ys[0]);
			q=q->next;
		}*/
}
/*
//********************
//����ĳ˷�
//*********************
void CCGWORK0935View::MutiTransMarix(double a[1][4],double b[4][4],double MutiResult[1][4])
{
 for(int i=0;i<4;i++) MutiResult[0][i] = 0;
 for(i=0; i<1;i++)
  for(int j=0;j<4;j++)
   for(int k=0;k<4;k++)
    MutiResult[i][j] += a[i][k]*b[k][j];
}
//******************************
//������ת��Ϊ������ʽ(����)
//******************************
void CCGWORK0935View::TransPointToMarix(ThPoint &tp,double a[1][4])
{
 a[0][0] = tp.x;
 a[0][1] = tp.y;
 a[0][2] = tp.z;
 a[0][3] = 1;
}
//******************************
//������(����)ת��Ϊ��ά������ʽ
//******************************
void CCGWORK0935View::TransMarixToPoint(double a[1][4],ThPoint &tp)
{
 tp.x = a[0][0];
 tp.y = a[0][1];
 tp.z = a[0][2];
}
//******************************
//�������ƽ���㷨
//******************************
void CCGWORK0935View::MoveTrans(double x,double y,double z)
{
    double a[8][4],result[1][4];
 double moveMarix[4][4] =
 {
  {1,0,0,0},{0,1,0,0},
  {0,0,1,0},{x,y,z,1}
 };
 
     for(int i=0;i<8;i++)
 {
          TransPointToMarix(points[i],a+i);
   MutiTransMarix(a+i,moveMarix,result);
   TransMarixToPoint(result,points[i]);
 }
 ShadowTrans(-45);
}
//****************************************************
//�������б��ͶӰ�㷨(����ά����ת��Ϊ��ά����Ļ��ʾ)
//****************************************************
void CCGWORK0935View::ShadowTrans(int degree)
{
 double a[8][4],result[1][4];
 ThPoint pts[8];
 for(int i=0;i<8;i++)
 {
  pts[i].x = points[i].x;
  pts[i].y = points[i].y;
  pts[i].z = points[i].z;
 }
 double shadowMarix[4][4] =
 {
  {1,0,0,0},{0,1,0,0},
  {cos(degree),sin(degree),0,0},{0,0,0,1}
 };
 
    for(i=0;i<8;i++)
 {
          TransPointToMarix(pts[i],a+i);
   MutiTransMarix(a+i,shadowMarix,result);
   TransMarixToPoint(result,pts[i]);
 }
 for(i=0;i<8;i++)
 {
  cpoints[i].x = (int)pts[i].x;
  cpoints[i].y = (int)pts[i].y;
 }
}
//***************************************
//��������ת�㷨����ת���Ŀ�����x,y��z��
//degree��ת�Ķ����� rc��ת����
//****************************************
void CCGWORK0935View::RotateTrans(double degree,CString rc)
{ 
    double a[8][4],result[1][4];
    int i = 0;
   
 if(rc == "z")
 {
  double xRotateMarix[4][4] =
   {
    {cos(degree*3.14/180),sin(degree*3.14/180),0,0},
    {-sin(degree*3.14/180),cos(degree*3.14/180),0,0},
    {0,0,1,0},{0,0,0,1},
   };
         for(i=0;i<8;i++)
   {
           TransPointToMarix(points[i],a+i);
        MutiTransMarix(a+i,xRotateMarix,result);
     TransMarixToPoint(result,points[i]);
   }
 }
 else if(rc == "x")
  {
  double yRotateMarix[4][4]=
   {
    {1,0,0,0},
    {0,cos(degree*3.14/180),sin(degree*3.14/180),0},
    {0,-sin(degree*3.14/180),cos(degree*3.14/180),0},
    {0,0,0,1}
   };
               for(i=0;i<8;i++)
   {
                   TransPointToMarix(points[i],a+i);
            MutiTransMarix(a+i,yRotateMarix,result);
     TransMarixToPoint(result,points[i]);
   }
     
  }
  else if(rc == "y")
  {
  double zRotateMarix[4][4]=
   {
    {cos(degree*3.14/180),0,-sin(degree*3.14/180),0},
    {0,1,0,0},
    {sin(degree*3.14/180),0,cos(degree*3.14/180),0},
    {0,0,0,1}
  };
         for(i=0;i<8;i++)
   {
           TransPointToMarix(points[i],a+i);
        MutiTransMarix(a+i,zRotateMarix,result);
     TransMarixToPoint(result,points[i]);
   }
     
  }
    ShadowTrans(-45);
}
*/
void CCGWORK0935View::OnOptionCube()
{
	OnPerspective();
	m_DrawType = 7;
	m_isDraw = true;
}

void CCGWORK0935View::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
if(m_DrawType==5){
	CDC *pDC = this->GetDC();
	points[count] = point;
	pDC->MoveTo(points[count-1]);
	pDC->LineTo(points[count]);
	count++;
	pDC->MoveTo(points[count-1]);
	pDC->LineTo(points[0]);
}
	CView::OnMButtonDblClk(nFlags, point);

}


void CCGWORK0935View::OnBezier()
{
	// TODO: �ڴ���������������
	m_DrawType = 6;//4��ʾ���ƾ�������
	m_isDraw = true;//��ǰ���ڻ�ͼ״̬*
}


void CCGWORK0935View::OnCube()
{
	// TODO: �ڴ���������������
	OnPerspective();
	m_DrawType = 7;
	m_isDraw = true;
}


void CCGWORK0935View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_DrawType==7){
		m_bRBDown = TRUE;
		m_prevPoint = point;
	}
	CView::OnRButtonDown(nFlags, point);
}

void CCGWORK0935View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	if(m_DrawType==7){
		m_bRBDown = FALSE;
		m_prevPoint = point;
	}
}

void CCGWORK0935View::On3drotatez()
{
	// TODO: �ڴ���������������
	rotate=0;
}


void CCGWORK0935View::On3dtranslatex()
{
	// TODO: �ڴ���������������
	translate=0;
}


void CCGWORK0935View::On3drotatex()
{
	// TODO: �ڴ���������������
	rotate=0;
}


void CCGWORK0935View::On3drotatey()
{
	// TODO: �ڴ���������������
	rotate=1;
}


void CCGWORK0935View::On3dtranslatey()
{
	// TODO: �ڴ���������������
	translate =1;
}


void CCGWORK0935View::On3dtranslatez()
{
	// TODO: �ڴ���������������
	translate = 2;
}


void CCGWORK0935View::OnSetstyle()
{
	// TODO: �ڴ���������������
	CSetStyleDlg dlg;
	dlg.SetStyle(m_RecRGB1,m_RecRGB2,m_RecRGB3,m_EllRGB1,m_EllRGB2,m_EllRGB3);
	if (dlg.DoModal() == IDOK){
		m_RecRGB1=dlg.m_edit1;
		m_RecRGB2=dlg.m_edit2;
		m_RecRGB3=dlg.m_edit3;
		m_EllRGB1=dlg.m_edit4;
		m_EllRGB2=dlg.m_edit5;
		m_EllRGB3=dlg.m_edit6;
	}
}


void CCGWORK0935View::OnSetdata()
{
	// TODO: �ڴ���������������
	CSetDataDlg dlg;
	dlg.SetData(m_length,m_angle);
	if(dlg.DoModal() == IDOK){
		m_length=dlg.m_edit1;
		m_angle=dlg.m_edit2;
	}
}


void CCGWORK0935View::OnClear()
{
	// TODO: �ڴ���������������
	ClearScreen();
}


void CCGWORK0935View::OnSetpcolor()
{
	// TODO: �ڴ���������������
	CSetPColorDlg dlg;
	dlg.SetStyle(m_Bord1,m_Bord2,m_Bord3,m_Back1,m_Back2,m_Back3);
	if (dlg.DoModal() == IDOK){
		m_Bord1=dlg.m_edit1;
		m_Bord2=dlg.m_edit2;
		m_Bord3=dlg.m_edit3;
		m_Back1=dlg.m_edit4;
		m_Back2=dlg.m_edit5;
		m_Back3=dlg.m_edit6;
	}
}
