// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PlanetryMotionView.cpp : implementation of the CPlanetryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetryMotion.h"
#endif

#include "PlanetryMotionDoc.h"
#include "PlanetryMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetryMotionView

IMPLEMENT_DYNCREATE(CPlanetryMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPlanetryMotionView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CPlanetryMotionView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CPlanetryMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CPlanetryMotionView construction/destruction

CPlanetryMotionView::CPlanetryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;
	x = 400;
	y = 200;
	x1 = 300 + 150 * cos(3);
	y1 = 200 + 150 * sin(3);

}

CPlanetryMotionView::~CPlanetryMotionView()
{
}

BOOL CPlanetryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetryMotionView drawing

void CPlanetryMotionView::OnDraw(CDC* pDC)
{
	
	
	CPlanetryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen redPen;
	redPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	// TODO: add draw code for native data here
	CPen* pOldPen = pDC->SelectObject(&redPen);
	pDC->Ellipse(450, 350, 150, 50);
	pDC->Ellipse(400, 300, 200, 100);
	pDC->Ellipse(330, 230, 270, 170);

	for (int i = 0; i < m_PointArray.GetSize(); i++) {
		pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);
		pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);

	}

	
	pDC->SelectObject(pOldPen);
	
	
	
}


// CPlanetryMotionView printing


void CPlanetryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetryMotionView diagnostics

#ifdef _DEBUG
void CPlanetryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetryMotionDoc* CPlanetryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetryMotionDoc)));
	return (CPlanetryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetryMotionView message handlers


void CPlanetryMotionView::OnButtonStart()
{
	// TODO: Add your command handler code here
	/*AfxMessageBox(_T("Start"));*/
	m_pCurrentThread = AfxBeginThread(CPlanetryMotionView::StartThread, this);
}


void CPlanetryMotionView::OnButtonStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread -> SuspendThread();
}


void CPlanetryMotionView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread -> ResumeThread();
	
}


unsigned int CPlanetryMotionView::StartThread(LPVOID param)
{
	// TODO: Add your implementation code here.
	CPlanetryMotionView* pView = (CPlanetryMotionView*)param;
	CPoint MyPoint(0,0);

	int j = 0;
	while (1) {
		j = j + 6;
		MyPoint.x= 300 + 100 * cos(j);
		MyPoint.y = 200 + 100 * sin(j);

		pView->x = 300 + 100 * cos(j);
		pView->y = 200 + 100 * sin(j);

		
		pView->y1 = 200 + 150 * cos(j + 3);
		pView->x1 = 300 + 150 * sin(j+3 );
		

		pView->m_PointArray.Add(MyPoint);
		pView->Invalidate();
		pView->UpdateWindow();
		Sleep(300);
	}

	return 0;
}
 