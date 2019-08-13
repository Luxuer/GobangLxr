// IfAgainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GobangLxr.h"
#include "IfAgainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IfAgainDlg dialog


IfAgainDlg::IfAgainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IfAgainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(IfAgainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void IfAgainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IfAgainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IfAgainDlg, CDialog)
	//{{AFX_MSG_MAP(IfAgainDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IfAgainDlg message handlers


