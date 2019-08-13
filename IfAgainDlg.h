#if !defined(AFX_IFAGAINDLG_H__AFFE8FD4_716D_4A9C_A18B_D98D42B39769__INCLUDED_)
#define AFX_IFAGAINDLG_H__AFFE8FD4_716D_4A9C_A18B_D98D42B39769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IfAgainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IfAgainDlg dialog

class IfAgainDlg : public CDialog
{
// Construction
public:
	IfAgainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IfAgainDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IfAgainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IfAgainDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFAGAINDLG_H__AFFE8FD4_716D_4A9C_A18B_D98D42B39769__INCLUDED_)
