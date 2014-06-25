
// invadersView.cpp : implementation of the CinvadersView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "invaders.h"

#endif

#include "invadersDoc.h"
#include "invadersView.h"
#include "space.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CinvadersView

IMPLEMENT_DYNCREATE(CinvadersView, CView)

BEGIN_MESSAGE_MAP(CinvadersView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(VK_S, &CinvadersView::OnS)
	ON_COMMAND(ID_OPTIONS_JEDIMASTER, &CinvadersView::OnOptionsJedimaster)
	ON_COMMAND(ID_OPTIONS_JEDI, &CinvadersView::OnOptionsJedi)
	ON_COMMAND(ID_OPTIONS_PADAWAN, &CinvadersView::OnOptionsPadawan)
	ON_COMMAND(ID_OPTIONS_YOUNGPADAWAN, &CinvadersView::OnOptionsYoungpadawan)
	ON_COMMAND(ID_OPTIONS_HANSOLO, &CinvadersView::OnOptionsHansolo)
	ON_WM_ERASEBKGND()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CinvadersView construction/destruction

CinvadersView::CinvadersView()
{
	// TODO: add construction code here
	
	
	
}

CinvadersView::~CinvadersView()
{
}

BOOL CinvadersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// CinvadersView drawing

void CinvadersView::OnDraw(CDC* pDC)
{
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//drawbackground
	CBitmap bitmap;
	CDC dcMemory;
	if(pDoc->sp.level==1){
		bitmap.LoadBitmapW(IDB_BITMAP1);}
	if(pDoc->sp.level==2){
		bitmap.LoadBitmapW(IDB_BITMAP2);}
	if(pDoc->sp.level==3){
		bitmap.LoadBitmapW(IDB_BITMAP3);}
	if(pDoc->sp.level==4){
		bitmap.LoadBitmapW(IDB_BITMAP4);}
	if(pDoc->sp.level==5){
		bitmap.LoadBitmapW(IDB_BITMAP5);}
	dcMemory.CreateCompatibleDC(pDC);
	dcMemory.SelectObject(bitmap);



	HICON player;
	HICON alien1;
	HICON alien2;
	HICON alien3;
	HICON alien4;
	HICON pRocket;
	HICON aRocket;
	HICON explo;
	player=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	alien1=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON2));
	alien2=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON3));
	alien3=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON4));
	alien4=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON5));
	pRocket=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON6));
	aRocket=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON6));
	explo=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON7));
	//draw player
	dcMemory.DrawIcon(pDoc->sp.player.left,pDoc->sp.player.top,player);

	//draw rocket
	if(pDoc->sp.pRock==true)dcMemory.DrawIcon(pDoc->sp.pRocket.left,pDoc->sp.pRocket.top,pRocket);
	if(pDoc->sp.aRock==true)dcMemory.DrawIcon(pDoc->sp.aRocket.left,pDoc->sp.aRocket.top,aRocket);

	if(pDoc->sp.exploa==true)dcMemory.DrawIcon(pDoc->sp.pRocket.left,pDoc->sp.pRocket.top,explo);pDoc->sp.exploa=false;
	if(pDoc->sp.explop==true)dcMemory.DrawIcon(pDoc->sp.player.left,pDoc->sp.player.top,explo);pDoc->sp.explop=false;
	//draw invaders
	for(int i=0;i<pDoc->sp.aliens.size();i++){
		if(pDoc->sp.aliens.at(i).i==0){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien4);}
		if(pDoc->sp.aliens.at(i).i==1){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien3);}
		if(pDoc->sp.aliens.at(i).i==2){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien2);}
		if(pDoc->sp.aliens.at(i).i==3){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien1);}
	}
	//drawscore&level
	dcMemory.TextOutW(200,pDoc->sp.border.bottom-20,pDoc->sp.llvl);
	dcMemory.TextOutW(250,pDoc->sp.border.bottom-20,pDoc->sp.lvl);
	dcMemory.TextOutW(300,pDoc->sp.border.bottom-20,pDoc->sp.lliv);
	dcMemory.TextOutW(350,pDoc->sp.border.bottom-20,pDoc->sp.liv);
	dcMemory.TextOutW(400,pDoc->sp.border.bottom-20,pDoc->sp.str);
	dcMemory.TextOutW(450,pDoc->sp.border.bottom-20,pDoc->sp.scr);
	//drawend
 

	if(pDoc->sp.gameOver==true){
		dcMemory.TextOutW(320,240,pDoc->sp.scr);
	}
	
	pDC->BitBlt(pDoc->sp.border.left,pDoc->sp.border.top,640,480,&dcMemory,0,0,SRCCOPY);	
}


// CinvadersView diagnostics

#ifdef _DEBUG
void CinvadersView::AssertValid() const
{
	CView::AssertValid();
}

void CinvadersView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CinvadersDoc* CinvadersView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CinvadersDoc)));
	return (CinvadersDoc*)m_pDocument;
}
#endif //_DEBUG


// CinvadersView message handlers


void CinvadersView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: Add your message handler code here and/or call default
	switch(nChar){
	case VK_LEFT: pDoc->sp.pMoveL=true;break;
	case VK_RIGHT: pDoc->sp.pMoveR=true;break;
	case VK_SPACE: pDoc->sp.PShoot();break;
	case VK_S: pDoc->sp.Pause();break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CinvadersView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	// TODO: Add your message handler code here and/or call default
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch(nChar){
	case VK_LEFT: pDoc->sp.pMoveL=false;break;
	case VK_RIGHT: pDoc->sp.pMoveR=false;break;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CinvadersView::OnTimer(UINT_PTR nIDEvent)
{   // TODO: Add your message handler code here and/or call default
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->sp.gameOver==true)KillTimer(MyTimer);
	if(pDoc->sp.game==true){
			if(pDoc->sp.pRock==true)pDoc->sp.PRocketMove();
			if(pDoc->sp.pMoveL==true)pDoc->sp.MoveLeft();
			if(pDoc->sp.pMoveR==true)pDoc->sp.MoveRight();
			pDoc->sp.AMove();
			pDoc->sp.AShoot();
			pDoc->sp.ARocketMove();

			Invalidate();
		}
    	CView::OnTimer(nIDEvent);
}


void CinvadersView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	MyTimer=SetTimer(1,50,0);
	CRect cr;
	CRect wr;
	CRect c;
    GetParent()->GetClientRect(cr);
  	GetParent()->GetWindowRect(wr);
	int dx=wr.Width()-cr.Width()+4;
	int dy=wr.Height()-cr.Height();
	GetParent()->SetWindowPos(0,0,0,pDoc->sp.border.Width()+dx, pDoc->sp.border.Height()+dy,SWP_NOMOVE|SWP_NOZORDER);

}


void CinvadersView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate();
}


void CinvadersView::OnS()
{
	// TODO: Add your command handler code here
		CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 pDoc->sp.Pause();
}
void CinvadersView::OnOptionsJedimaster()
{
	// TODO: Add your command handler code here
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->sp.Reset();
	 pDoc->sp.lives=1;
	 pDoc->sp.liv.Format(_T("%d"),pDoc->sp.lives);
	 Invalidate();
}


void CinvadersView::OnOptionsJedi()
{
	// TODO: Add your command handler code here
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->sp.Reset();
	 pDoc->sp.lives=3;
	 pDoc->sp.liv.Format(_T("%d"),pDoc->sp.lives);
	 Invalidate();
}


void CinvadersView::OnOptionsPadawan()
{
	// TODO: Add your command handler code here
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->sp.Reset();
	 pDoc->sp.lives=5;
	 pDoc->sp.liv.Format(_T("%d"),pDoc->sp.lives);
	 Invalidate();
}


void CinvadersView::OnOptionsYoungpadawan()
{
	// TODO: Add your command handler code here
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->sp.Reset();
	 pDoc->sp.lives=9;
	 pDoc->sp.liv.Format(_T("%d"),pDoc->sp.lives);
	 Invalidate();
}


void CinvadersView::OnOptionsHansolo()
{
	// TODO: Add your command handler code here
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->sp.Reset();
	 pDoc->sp.lives=100;
	 pDoc->sp.liv.Format(_T("%d"),pDoc->sp.lives);
	 Invalidate();
}


BOOL CinvadersView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}

