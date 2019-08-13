// GobangLxrDoc.h : interface of the CGobangLxrDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOBANGLXRDOC_H__81E5BBC2_CD12_427E_AC1C_C00646AA0365__INCLUDED_)
#define AFX_GOBANGLXRDOC_H__81E5BBC2_CD12_427E_AC1C_C00646AA0365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGobangLxrDoc : public CDocument
{
protected: // create from serialization only
	CGobangLxrDoc();
	DECLARE_DYNCREATE(CGobangLxrDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGobangLxrDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGobangLxrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGobangLxrDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOBANGLXRDOC_H__81E5BBC2_CD12_427E_AC1C_C00646AA0365__INCLUDED_)
