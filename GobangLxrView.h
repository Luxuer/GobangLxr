// GobangLxrView.h : interface of the CGobangLxrView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOBANGLXRVIEW_H__AA725BD8_586C_4C29_8050_92FCBC9AAE33__INCLUDED_)
#define AFX_GOBANGLXRVIEW_H__AA725BD8_586C_4C29_8050_92FCBC9AAE33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InitWindowConfig.h"

class CGobangLxrView : public CView
{
protected: // create from serialization only
	CGobangLxrView();
	DECLARE_DYNCREATE(CGobangLxrView)

// Attributes
public:
	CGobangLxrDoc* GetDocument();

//	CPoint m_mousePos;
	int m_record[NUM_ROW*NUM_ROW+10][NUM_ROW][NUM_ROW];  // 记录每一步的棋局
	int m_numGames;
	int m_currentColor;
	CBitmap m_chessboard;
	CBitmap m_blackpiece;
	CBitmap m_whitepiece;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGobangLxrView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawExit(CDC * pDC);
	void DrawRemind(CDC *pDC);
	void DrawRegret(CDC * pDC);
	void DrawReset(CDC *pDC);
	bool SomebodyWin(int x, int y);
	void DrawChesses(CDC *pDC);
	void DrawChessboard(CDC * pDC);
	virtual ~CGobangLxrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGobangLxrView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in GobangLxrView.cpp
inline CGobangLxrDoc* CGobangLxrView::GetDocument()
   { return (CGobangLxrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOBANGLXRVIEW_H__AA725BD8_586C_4C29_8050_92FCBC9AAE33__INCLUDED_)
