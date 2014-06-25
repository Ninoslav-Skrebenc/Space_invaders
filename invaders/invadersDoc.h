
// invadersDoc.h : interface of the CinvadersDoc class
//


#pragma once
#include "space.h"


class CinvadersDoc : public CDocument
{
protected: // create from serialization only
	CinvadersDoc();
	DECLARE_DYNCREATE(CinvadersDoc)

// Attributes
public:

// Operations
	void MoveLeft() {return sp.MoveLeft();};
	void MoveRight() {return sp.MoveRight();};
	void AMove() {return sp.AMove();};
	void PRocketMove() {return sp.PRocketMove();}
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CinvadersDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	space sp;
	
protected:

// Generated message map functions
	
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
