// GobangLxrView.cpp : implementation of the CGobangLxrView class
//

#include "stdafx.h"
#include "GobangLxr.h"

#include "GobangLxrDoc.h"
#include "GobangLxrView.h"
#include "InitWindowConfig.h"
#include "IfAgainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrView

IMPLEMENT_DYNCREATE(CGobangLxrView, CView)

BEGIN_MESSAGE_MAP(CGobangLxrView, CView)
	//{{AFX_MSG_MAP(CGobangLxrView)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrView construction/destruction

CGobangLxrView::CGobangLxrView()
{
	// TODO: add construction code here
//	m_mousePos.x = 0;
//	m_mousePos.y = 0;

	memset(m_record, NONE, sizeof(m_record));

	m_numGames = 0;
	m_currentColor = BLACK;  // Ĭ�Ϻ�ɫ����

	m_chessboard.LoadBitmap(IDB_CHESSBOARD);
	m_blackpiece.LoadBitmap(IDB_BLACKPIECE);
	m_whitepiece.LoadBitmap(IDB_WHITEPIECE);
}

CGobangLxrView::~CGobangLxrView()
{
}

BOOL CGobangLxrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrView drawing

void CGobangLxrView::OnDraw(CDC* pDC)
{
	CGobangLxrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect   rect;
	GetClientRect(&rect);


	CDC dcMem;                                                  //���ڻ�����ͼ���ڴ�DC
	CBitmap bmp;                                                 //�ڴ��г�����ʱͼ���λͼ
	dcMem.CreateCompatibleDC(pDC);               //��������DC���������ڴ�DC
	bmp.CreateCompatibleBitmap(&dcMem,rect.Width(),rect.Height());//��������λͼ
	dcMem.SelectObject(&bmp);   //��λͼѡ����ڴ�DC
	dcMem.FillSolidRect(rect,  pDC->GetBkColor());//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ

	dcMem.SetBkMode(TRANSPARENT);

	DrawRemind(&dcMem);			// ��ʾ��ǰ�Ǻ�����, ���ǰ�����, �Լ��ܲ���, ������
	DrawChessboard(&dcMem);		// ������
	DrawChesses(&dcMem);		// ������
	DrawReset(&dcMem);			// �����¿�ʼ��
	DrawRegret(&dcMem);			// �������
	DrawExit(&dcMem);			// �˳���Ϸ��


	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
	dcMem.DeleteDC();                                       //ɾ��DC
	bmp.DeleteObject();                                        //ɾ��λͼ
}

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrView printing

BOOL CGobangLxrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGobangLxrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGobangLxrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrView diagnostics

#ifdef _DEBUG
void CGobangLxrView::AssertValid() const
{
	CView::AssertValid();
}

void CGobangLxrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGobangLxrDoc* CGobangLxrView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGobangLxrDoc)));
	return (CGobangLxrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGobangLxrView message handlers

void CGobangLxrView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*	int x = point.x/pieceWidth;
	int y = point.y/pieceWidth;

//	m_mousePos
	CClientDC dc(this);
	dc.TextOut(x*pieceWidth, y*pieceWidth, "hello");
	
//	Invalidate(TRUE);
*/
	CView::OnMouseMove(nFlags, point);
}

BOOL CGobangLxrView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

// ����������ʱ�Ĵ�����
void CGobangLxrView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString cs;
	IfAgainDlg dlg;

	int x = (point.x-PIECE_WIDTH/2)/PIECE_WIDTH;
	int y = (point.y-PIECE_WIDTH/2)/PIECE_WIDTH;
	int i, j;
	if( x>-1 && x<NUM_ROW && y>-1 && y<NUM_ROW && m_record[m_numGames][x][y]==NONE )
	{
		m_numGames++;
		
		for(i=0;i<NUM_ROW;i++)  // �Ȱ���һ����ָ��Ƶ������
			for(j=0;j<NUM_ROW;j++)
				m_record[m_numGames][i][j] = m_record[m_numGames-1][i][j];
		m_record[m_numGames][x][y]=m_currentColor; // ����������µ�ǰ��
		m_currentColor = -m_currentColor;  // �ı䵱ǰ�ӵ���ɫ
		Invalidate(TRUE);

		if(SomebodyWin(x, y))
		{
			cs.Format("��ϲ%s��, ������ʤ����", m_record[m_numGames][x][y]==BLACK ? "��":"��");
			AfxMessageBox(cs); // �����Ի���
			if(dlg.DoModal()==IDOK)
			{
				memset(m_record, NONE, sizeof(m_record));
				m_numGames = 0;
				m_currentColor = BLACK;  // Ĭ�Ϻ�ɫ����
				Invalidate(TRUE);
			}else AfxGetMainWnd()->PostMessage(WM_QUIT,0,0);  // �رճ���
			
		}
	}else if( point.x>=RESET_BUTTON_LEFT && point.x<=RESET_BUTTON_RIGHT && 
		      point.y>=RESET_BUTTON_TOP && point.y<=RESET_BUTTON_BOTTOM )
	{
		memset(m_record, NONE, sizeof(m_record));
		m_numGames = 0;
		m_currentColor = BLACK;  // Ĭ�Ϻ�ɫ����
		Invalidate(TRUE);
	}else if(point.x>=REGRET_BUTTON_LEFT && point.x<=REGRET_BUTTON_RIGHT && 
		     point.y>=REGRET_BUTTON_TOP && point.y<=REGRET_BUTTON_BOTTOM )
	{
		m_numGames--;
		m_currentColor = -m_currentColor;
		Invalidate(TRUE);
	}else if(point.x>=EXIT_BUTTON_LEFT && point.x<=EXIT_BUTTON_RIGHT && 
		     point.y>=EXIT_BUTTON_TOP && point.y<=EXIT_BUTTON_BOTTOM)
	{
		PostMessage(WM_QUIT);	// �˳���Ϸ, �رճ���
		//PostQuitMessage(0);
		//AfxGetMainWnd()->PostMessage(WM_QUIT,0,0);  
	}
	CView::OnLButtonDown(nFlags, point);
}

// ��������
void CGobangLxrView::DrawChessboard(CDC *pDC)
{
	int i;
	for(i=1;i<NUM_ROW+1;i++)
	{
		pDC->MoveTo(PIECE_WIDTH, i*PIECE_WIDTH);
		pDC->LineTo(PIECE_WIDTH + CHESSBOARD_WIDTH, i*PIECE_WIDTH);
	}

	for(i=1;i<NUM_ROW+1;i++)
	{
		pDC->MoveTo(i*PIECE_WIDTH, PIECE_WIDTH);
		pDC->LineTo(i*PIECE_WIDTH, PIECE_WIDTH + CHESSBOARD_WIDTH);
	}

}

// �����Ѿ��¹�������
void CGobangLxrView::DrawChesses(CDC *pDC)
{
	int i, j;
	for(i=0;i<NUM_ROW;i++)
		for(j=0;j<NUM_ROW;j++)
			if(m_record[m_numGames][i][j] != NONE)
			{
				pDC->SelectStockObject((m_record[m_numGames][i][j]==BLACK) ? BLACK_BRUSH : WHITE_BRUSH);
				pDC->Ellipse((i+1)*PIECE_WIDTH-PIECE_WIDTH/2, (j+1)*PIECE_WIDTH-PIECE_WIDTH/2, 
							 (i+1)*PIECE_WIDTH+PIECE_WIDTH/2, (j+1)*PIECE_WIDTH+PIECE_WIDTH/2);
			}
	pDC->SelectStockObject(WHITE_BRUSH);
}

// �жϵ�ǰ�������Ƿ��ʤ, ���ӵ�λ��Ϊ(x, y)
bool CGobangLxrView::SomebodyWin(int x, int y)
{
	const int leftBorder = 0;//(0 > x-4) ? 0 : x-4;
	const int rightBorder = NUM_ROW - 1;// (NUM_ROW - 1 < x + 4) ? NUM_ROW - 1 : x + 4;
	const int topBorder = 0;// (0 > y - 4) ? 0 : y - 4;
	const int bottomBorder = NUM_ROW - 1;// (NUM_ROW - 1 < y + 4) ? 0 : x - 4;

	const int pieceType = m_record[m_numGames][x][y];
	int count;
	int i, j;
	// ������
	count = 1;
	for(i=x-1;i>=leftBorder && pieceType==m_record[m_numGames][i][y];i--) // ������
		count++; 
	for(i=x+1;i<=rightBorder && pieceType==m_record[m_numGames][i][y];i++)  // ������
		count++;
	if(count>=5) return TRUE;

	// ������
	count = 1;
	for(j=y-1;j>=topBorder && pieceType==m_record[m_numGames][x][j];j--) // ������
		count++; 
	for(j=y+1;j<=bottomBorder && pieceType==m_record[m_numGames][x][j];j++)  // ������
		count++;
	if(count>=5) return TRUE;

	// �����Ϻ�������
	count = 1;
	for(i=x-1, j=y-1;i>=leftBorder && j>=topBorder && pieceType==m_record[m_numGames][i][j];i--, j--) // ������
		count++; 
	for(i=x+1, j=y+1;i<=rightBorder && j<=bottomBorder && pieceType==m_record[m_numGames][i][j];i++, j++)  // ������
		count++;
	if(count>=5) return TRUE;


	// �����º�������
	count = 1;
	for(i=x-1, j=y+1;i>=leftBorder && j<=bottomBorder && pieceType==m_record[m_numGames][i][j];i--, j++) // ������
		count++; 
	for(i=x+1, j=y-1;i<=rightBorder && j>=topBorder && pieceType== m_record[m_numGames][i][j];i++, j--)  // ������
		count++;
	if(count>=5) return TRUE;

	return FALSE;

}

// ����"���¿�ʼ"��
void CGobangLxrView::DrawReset(CDC *pDC)
{
	pDC->RoundRect(RESET_BUTTON_LEFT, RESET_BUTTON_TOP, RESET_BUTTON_RIGHT, RESET_BUTTON_BOTTOM, 
						PIECE_WIDTH/3, PIECE_WIDTH/3);
	pDC->TextOut(RESET_BUTTON_LEFT+PIECE_WIDTH/3+2, RESET_BUTTON_TOP+PIECE_WIDTH/4+3, "���¿�ʼ");
}

// ����"��    ��"��
void CGobangLxrView::DrawRegret(CDC *pDC)
{
	pDC->RoundRect(REGRET_BUTTON_LEFT, REGRET_BUTTON_TOP, REGRET_BUTTON_RIGHT, REGRET_BUTTON_BOTTOM, 
						PIECE_WIDTH/3, PIECE_WIDTH/3);
	pDC->TextOut(REGRET_BUTTON_LEFT+PIECE_WIDTH/3+10, REGRET_BUTTON_TOP+PIECE_WIDTH/4+3, "��    ��");
}

// ����������Ϣ
void CGobangLxrView::DrawRemind(CDC *pDC)
{
	CString cs;
	// �����ֵ����ӻ��ǰ���
	cs.Format("%s%s", "�ֵ�", m_currentColor==BLACK ? "����":"����");
	pDC->TextOut(REGRET_BUTTON_LEFT+8, REGRET_BUTTON_TOP+PIECE_WIDTH*2+5, cs);
	pDC->SelectStockObject(m_currentColor==BLACK ? BLACK_BRUSH : WHITE_BRUSH);	
	pDC->Ellipse(REGRET_BUTTON_LEFT+2*PIECE_WIDTH-10, REGRET_BUTTON_TOP+2*PIECE_WIDTH, REGRET_BUTTON_LEFT+2*PIECE_WIDTH+PIECE_WIDTH/2-10, REGRET_BUTTON_TOP+2*PIECE_WIDTH+PIECE_WIDTH/2);

	// ����������ܲ���(��������������)
	cs.Format("�����ܲ���Ϊ%d", m_numGames);
	pDC->TextOut(REGRET_BUTTON_LEFT+8, REGRET_BUTTON_TOP+PIECE_WIDTH*3+20, cs);

	// ���Ѻ�����
	cs.Format("������Ϊ%d", m_numGames/2+1);
	pDC->TextOut(REGRET_BUTTON_LEFT+8, REGRET_BUTTON_TOP+PIECE_WIDTH*4+30, cs);


}

// ����"�˳���Ϸ"��
void CGobangLxrView::DrawExit(CDC *pDC)
{
	pDC->RoundRect(EXIT_BUTTON_LEFT, EXIT_BUTTON_TOP, EXIT_BUTTON_RIGHT, EXIT_BUTTON_BOTTOM, 
						PIECE_WIDTH/3, PIECE_WIDTH/3);
	pDC->TextOut(EXIT_BUTTON_LEFT+PIECE_WIDTH/3+2, EXIT_BUTTON_TOP+PIECE_WIDTH/4+3, "�˳���Ϸ");
}


void CGobangLxrView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnRButtonDown(nFlags, point);
}
