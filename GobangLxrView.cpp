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
	m_currentColor = BLACK;  // 默认黑色先行

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


	CDC dcMem;                                                  //用于缓冲作图的内存DC
	CBitmap bmp;                                                 //内存中承载临时图象的位图
	dcMem.CreateCompatibleDC(pDC);               //依附窗口DC创建兼容内存DC
	bmp.CreateCompatibleBitmap(&dcMem,rect.Width(),rect.Height());//创建兼容位图
	dcMem.SelectObject(&bmp);   //将位图选择进内存DC
	dcMem.FillSolidRect(rect,  pDC->GetBkColor());//按原来背景填充客户区，不然会是黑色

	dcMem.SetBkMode(TRANSPARENT);

	DrawRemind(&dcMem);			// 提示当前是黑子行, 还是白子行, 以及总步数, 黑子数
	DrawChessboard(&dcMem);		// 画棋盘
	DrawChesses(&dcMem);		// 画棋子
	DrawReset(&dcMem);			// 画重新开始键
	DrawRegret(&dcMem);			// 画悔棋键
	DrawExit(&dcMem);			// 退出游戏键


	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);//将内存DC上的图象拷贝到前台
	dcMem.DeleteDC();                                       //删除DC
	bmp.DeleteObject();                                        //删除位图
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

// 按下鼠标左键时的处理函数
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
		
		for(i=0;i<NUM_ROW;i++)  // 先把上一个棋局复制到新棋局
			for(j=0;j<NUM_ROW;j++)
				m_record[m_numGames][i][j] = m_record[m_numGames-1][i][j];
		m_record[m_numGames][x][y]=m_currentColor; // 在新棋局落下当前子
		m_currentColor = -m_currentColor;  // 改变当前子的颜色
		Invalidate(TRUE);

		if(SomebodyWin(x, y))
		{
			cs.Format("恭喜%s方, 你获得了胜利！", m_record[m_numGames][x][y]==BLACK ? "黑":"白");
			AfxMessageBox(cs); // 弹出对话框
			if(dlg.DoModal()==IDOK)
			{
				memset(m_record, NONE, sizeof(m_record));
				m_numGames = 0;
				m_currentColor = BLACK;  // 默认黑色先行
				Invalidate(TRUE);
			}else AfxGetMainWnd()->PostMessage(WM_QUIT,0,0);  // 关闭程序
			
		}
	}else if( point.x>=RESET_BUTTON_LEFT && point.x<=RESET_BUTTON_RIGHT && 
		      point.y>=RESET_BUTTON_TOP && point.y<=RESET_BUTTON_BOTTOM )
	{
		memset(m_record, NONE, sizeof(m_record));
		m_numGames = 0;
		m_currentColor = BLACK;  // 默认黑色先行
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
		PostMessage(WM_QUIT);	// 退出游戏, 关闭程序
		//PostQuitMessage(0);
		//AfxGetMainWnd()->PostMessage(WM_QUIT,0,0);  
	}
	CView::OnLButtonDown(nFlags, point);
}

// 绘制棋盘
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

// 绘制已经下过的棋子
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

// 判断当前下子人是否获胜, 下子的位置为(x, y)
bool CGobangLxrView::SomebodyWin(int x, int y)
{
	const int leftBorder = 0;//(0 > x-4) ? 0 : x-4;
	const int rightBorder = NUM_ROW - 1;// (NUM_ROW - 1 < x + 4) ? NUM_ROW - 1 : x + 4;
	const int topBorder = 0;// (0 > y - 4) ? 0 : y - 4;
	const int bottomBorder = NUM_ROW - 1;// (NUM_ROW - 1 < y + 4) ? 0 : x - 4;

	const int pieceType = m_record[m_numGames][x][y];
	int count;
	int i, j;
	// 横向数
	count = 1;
	for(i=x-1;i>=leftBorder && pieceType==m_record[m_numGames][i][y];i--) // 往左数
		count++; 
	for(i=x+1;i<=rightBorder && pieceType==m_record[m_numGames][i][y];i++)  // 往右数
		count++;
	if(count>=5) return TRUE;

	// 纵向数
	count = 1;
	for(j=y-1;j>=topBorder && pieceType==m_record[m_numGames][x][j];j--) // 往上数
		count++; 
	for(j=y+1;j<=bottomBorder && pieceType==m_record[m_numGames][x][j];j++)  // 往下数
		count++;
	if(count>=5) return TRUE;

	// 往左上和右下数
	count = 1;
	for(i=x-1, j=y-1;i>=leftBorder && j>=topBorder && pieceType==m_record[m_numGames][i][j];i--, j--) // 往左上
		count++; 
	for(i=x+1, j=y+1;i<=rightBorder && j<=bottomBorder && pieceType==m_record[m_numGames][i][j];i++, j++)  // 右下数
		count++;
	if(count>=5) return TRUE;


	// 往左下和右上数
	count = 1;
	for(i=x-1, j=y+1;i>=leftBorder && j<=bottomBorder && pieceType==m_record[m_numGames][i][j];i--, j++) // 往左下
		count++; 
	for(i=x+1, j=y-1;i<=rightBorder && j>=topBorder && pieceType== m_record[m_numGames][i][j];i++, j--)  // 右上数
		count++;
	if(count>=5) return TRUE;

	return FALSE;

}

// 绘制"重新开始"键
void CGobangLxrView::DrawReset(CDC *pDC)
{
	pDC->RoundRect(RESET_BUTTON_LEFT, RESET_BUTTON_TOP, RESET_BUTTON_RIGHT, RESET_BUTTON_BOTTOM, 
						PIECE_WIDTH/3, PIECE_WIDTH/3);
	pDC->TextOut(RESET_BUTTON_LEFT+PIECE_WIDTH/3+2, RESET_BUTTON_TOP+PIECE_WIDTH/4+3, "重新开始");
}

// 绘制"悔    棋"键
void CGobangLxrView::DrawRegret(CDC *pDC)
{
	pDC->RoundRect(REGRET_BUTTON_LEFT, REGRET_BUTTON_TOP, REGRET_BUTTON_RIGHT, REGRET_BUTTON_BOTTOM, 
						PIECE_WIDTH/3, PIECE_WIDTH/3);
	pDC->TextOut(REGRET_BUTTON_LEFT+PIECE_WIDTH/3+10, REGRET_BUTTON_TOP+PIECE_WIDTH/4+3, "悔    棋");
}

// 绘制提醒信息
void CGobangLxrView::DrawRemind(CDC *pDC)
{
	CString cs;
	// 提醒轮到黑子还是白子
	cs.Format("%s%s", "轮到", m_currentColor==BLACK ? "黑子":"白子");
	pDC->TextOut(REGRET_BUTTON_LEFT+8, REGRET_BUTTON_TOP+PIECE_WIDTH*2+5, cs);
	pDC->SelectStockObject(m_currentColor==BLACK ? BLACK_BRUSH : WHITE_BRUSH);	
	pDC->Ellipse(REGRET_BUTTON_LEFT+2*PIECE_WIDTH-10, REGRET_BUTTON_TOP+2*PIECE_WIDTH, REGRET_BUTTON_LEFT+2*PIECE_WIDTH+PIECE_WIDTH/2-10, REGRET_BUTTON_TOP+2*PIECE_WIDTH+PIECE_WIDTH/2);

	// 提醒下棋的总步数(棋盘上总棋子数)
	cs.Format("下棋总步数为%d", m_numGames);
	pDC->TextOut(REGRET_BUTTON_LEFT+8, REGRET_BUTTON_TOP+PIECE_WIDTH*3+20, cs);

	// 提醒黑子数
	cs.Format("黑子数为%d", m_numGames/2+1);
	pDC->TextOut(REGRET_BUTTON_LEFT+8, REGRET_BUTTON_TOP+PIECE_WIDTH*4+30, cs);


}

// 绘制"退出游戏"键
void CGobangLxrView::DrawExit(CDC *pDC)
{
	pDC->RoundRect(EXIT_BUTTON_LEFT, EXIT_BUTTON_TOP, EXIT_BUTTON_RIGHT, EXIT_BUTTON_BOTTOM, 
						PIECE_WIDTH/3, PIECE_WIDTH/3);
	pDC->TextOut(EXIT_BUTTON_LEFT+PIECE_WIDTH/3+2, EXIT_BUTTON_TOP+PIECE_WIDTH/4+3, "退出游戏");
}


void CGobangLxrView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnRButtonDown(nFlags, point);
}
