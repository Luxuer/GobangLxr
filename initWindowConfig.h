// InitWindowConfig.h
// 设置一些全局参数

#if !defined(INIWINDOWCONFIG_H)
#define INIWINDOWCONFIG_H







// 在这里设置程序刚运行的时候窗口的位置, 宽度和高度
const int WINDOW_POSITION_X = 50;
const int WINDOW_POSITION_Y = 50;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;



// 棋子和棋盘的尺寸
const int NUM_ROW = 15;		// 行数=列数
const int PIECE_WIDTH = 50;	//  棋子宽度(直径)
const int CHESSBOARD_WIDTH = PIECE_WIDTH*(NUM_ROW-1);
// 重新开始键的位置
const int RESET_BUTTON_LEFT = (NUM_ROW+1)*PIECE_WIDTH;
const int RESET_BUTTON_RIGHT = (NUM_ROW+3)*PIECE_WIDTH;
const int RESET_BUTTON_TOP = PIECE_WIDTH;
const int RESET_BUTTON_BOTTOM = 2*PIECE_WIDTH;

// 悔棋键的位置
const int REGRET_BUTTON_LEFT = (NUM_ROW+1)*PIECE_WIDTH;
const int REGRET_BUTTON_RIGHT = (NUM_ROW+3)*PIECE_WIDTH;
const int REGRET_BUTTON_TOP = 3*PIECE_WIDTH;
const int REGRET_BUTTON_BOTTOM = 4*PIECE_WIDTH;

// 退出游戏键的位置
const int EXIT_BUTTON_LEFT = (NUM_ROW+1)*PIECE_WIDTH;
const int EXIT_BUTTON_RIGHT = (NUM_ROW+3)*PIECE_WIDTH;
const int EXIT_BUTTON_TOP = 10*PIECE_WIDTH;
const int EXIT_BUTTON_BOTTOM = 11*PIECE_WIDTH;

// 棋子的种类
const int NONE = 0;
const int WHITE = -1;
const int BLACK = 1;















#endif
