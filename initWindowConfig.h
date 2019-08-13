// InitWindowConfig.h
// ����һЩȫ�ֲ���

#if !defined(INIWINDOWCONFIG_H)
#define INIWINDOWCONFIG_H







// ���������ó�������е�ʱ�򴰿ڵ�λ��, ��Ⱥ͸߶�
const int WINDOW_POSITION_X = 50;
const int WINDOW_POSITION_Y = 50;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;



// ���Ӻ����̵ĳߴ�
const int NUM_ROW = 15;		// ����=����
const int PIECE_WIDTH = 50;	//  ���ӿ��(ֱ��)
const int CHESSBOARD_WIDTH = PIECE_WIDTH*(NUM_ROW-1);
// ���¿�ʼ����λ��
const int RESET_BUTTON_LEFT = (NUM_ROW+1)*PIECE_WIDTH;
const int RESET_BUTTON_RIGHT = (NUM_ROW+3)*PIECE_WIDTH;
const int RESET_BUTTON_TOP = PIECE_WIDTH;
const int RESET_BUTTON_BOTTOM = 2*PIECE_WIDTH;

// �������λ��
const int REGRET_BUTTON_LEFT = (NUM_ROW+1)*PIECE_WIDTH;
const int REGRET_BUTTON_RIGHT = (NUM_ROW+3)*PIECE_WIDTH;
const int REGRET_BUTTON_TOP = 3*PIECE_WIDTH;
const int REGRET_BUTTON_BOTTOM = 4*PIECE_WIDTH;

// �˳���Ϸ����λ��
const int EXIT_BUTTON_LEFT = (NUM_ROW+1)*PIECE_WIDTH;
const int EXIT_BUTTON_RIGHT = (NUM_ROW+3)*PIECE_WIDTH;
const int EXIT_BUTTON_TOP = 10*PIECE_WIDTH;
const int EXIT_BUTTON_BOTTOM = 11*PIECE_WIDTH;

// ���ӵ�����
const int NONE = 0;
const int WHITE = -1;
const int BLACK = 1;















#endif
