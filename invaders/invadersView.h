
// invadersView.h : interface of the CinvadersView class
//

#pragma once


class CinvadersView : public CView
{
protected: // create from serialization only
	CinvadersView();
	DECLARE_DYNCREATE(CinvadersView)

// Attributes
public:
	CinvadersDoc* GetDocument() const;
	UINT_PTR MyTimer;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CinvadersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnS();
	afx_msg void OnOptionsJedimaster();
	afx_msg void OnOptionsJedi();
	afx_msg void OnOptionsPadawan();
	afx_msg void OnOptionsYoungpadawan();
	afx_msg void OnOptionsHansolo();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
};

#ifndef _DEBUG  // debug version in invadersView.cpp
inline CinvadersDoc* CinvadersView::GetDocument() const
   { return reinterpret_cast<CinvadersDoc*>(m_pDocument); }
#endif

