#include"Function.h"
extern IMAGE wall, background, func, info, temp;
extern IMAGE path[12][10];
int main() {
	Map map[12][10] = { {0, 0, 0} };
	Node* flower = initNode();
	Node* jewel = initNode();
	Node* bomb = initNode();
	char userName[20] = {"\0"};
	char* ptrName = userName;
	int xCurrent = 9;
	int yCurrent = 2;
	int key;
	// 初始化界面
	initialize(map, flower, jewel, bomb, &ptrName);
	while (1) {
		// 存储
		store(userName, map, flower, jewel, bomb);
		// 显示信息
		showInfo(userName);
		// 鼠标功能
		if (MouseHit()) {
			mouseControl(flower, jewel, bomb, map, &ptrName, &xCurrent, &yCurrent);
		}
		// 移动功能
		key = -1;
		if (_kbhit()) {
			int pre = _getch();
			if (pre == 0xE0) {
				key = _getch();
				switch (key) {
				case UP_KEY:
					move(xCurrent, yCurrent, UP, map, flower, jewel, bomb);
					break;
				case DOWN_KEY:
					move(xCurrent, yCurrent, DOWN, map, flower, jewel, bomb);
					break;
				case LEFT_KEY:
					move(xCurrent, yCurrent, LEFT, map, flower, jewel, bomb);
					break;
				case RIGHT_KEY:
					move(xCurrent, yCurrent, RIGHT, map, flower, jewel, bomb);
					break;
				default:
					break;
				}
			}
			if (pre == ' ') {
				spaceHit(xCurrent, yCurrent, map, flower);
			}
		}
		// 游戏结束
		if (isGameOver(xCurrent, yCurrent)) {
			store(userName, map, flower, jewel, bomb);
			if (MessageBox(GetHWnd(), (LPCSTR)"再来一局?", (LPCSTR)"逃出迷宫", MB_OKCANCEL) == IDOK) {
				clear(flower);
				clear(jewel);
				clear(bomb);
				initialize(map, flower, jewel, bomb, &ptrName);
				map[1][0].isPerson = 0;
				xCurrent = 9;
				yCurrent = 2;
			} else {
				exit(EXIT_SUCCESS);
			}
		}
	}
	system("pause");
	return 0;
}
