// GobangLxrDoc.cpp : implementation of the CGobangLxrDoc class
//

#include "stdafx.h"
#include "GobangLxr.h"

#include "GobangLxrDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrDoc

IMPLEMENT_DYNCREATE(CGobangLxrDoc, CDocument)

BEGIN_MESSAGE_MAP(CGobangLxrDoc, CDocument)
	//{{AFX_MSG_MAP(CGobangLxrDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrDoc construction/destruction

CGobangLxrDoc::CGobangLxrDoc()
{
	// TODO: add one-time construction code here

}

CGobangLxrDoc::~CGobangLxrDoc()
{
}

BOOL CGobangLxrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGobangLxrDoc serialization

void CGobangLxrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrDoc diagnostics

#ifdef _DEBUG
void CGobangLxrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGobangLxrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrDoc commands
