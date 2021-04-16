#include"Function.h"
extern IMAGE wall, wallBack, background, func, info, temp;
extern IMAGE path[12][10];
extern IMAGE p, pBack, f, fBack, j, jBack, b, bBack;
int main() {
	Map map[12][10] = { {0, false, false} };
	Node* flower = initNode(); 
	Node* jewel = initNode();
	Node* bomb = initNode();
	char userName[20] = {"\0"};
	char* ptrName = userName;
	char** mapFile;
	int xCurrent = 9;
	int yCurrent = 2;
	int key = -1;
	MOUSEMSG m;
	int level = 0;
	initMapFile(&mapFile);
	if (start()) {
		cleardevice();

		// 初始化界面
		initialize(map, flower, jewel, bomb, &ptrName, mapFile[level]);

		// 显示信息
		showInfo(userName);

		// 播放音乐
		PlaySound((LPCSTR)"resource\\music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		FlushMouseMsgBuffer();
		while (1) {

			// 鼠标功能
			if (MouseHit()) {
				m = GetMouseMsg();
				mouseControl(flower, jewel, bomb, map, &ptrName, &xCurrent, &yCurrent, 
							mapFile, &level, m);
				FlushMouseMsgBuffer();
				store(userName, map, flower, jewel, bomb, level + 1);
			}

			// 移动功能
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
					key = -1;

					// 存储
					store(userName, map, flower, jewel, bomb, level + 1);

					// 显示信息
					showInfo(userName);
				}

				// 空格机制
				if (pre == ' ') {
					spaceHit(xCurrent, yCurrent, map, flower);
				}
			}

			// 游戏结束
			if (isGameOver(xCurrent, yCurrent)) {
				level++;
				if (level != LEVEL) {
					xCurrent = 9;
					yCurrent = 2;
					resetBoundary(map, mapFile[level], flower);
					store(userName, map, flower, jewel, bomb, level + 1);
					showInfo(userName);
				} else {
					if (MessageBox(GetHWnd(), (LPCSTR)"再来一局?", (LPCSTR)"逃出迷宫", MB_OKCANCEL) == IDOK) {

						// 清空链表
						clear(flower);
						clear(jewel);
						clear(bomb);

						// 重置关卡
						level = 0;
						initialize(map, flower, jewel, bomb, &ptrName, mapFile[level]);

						// 重置人物
						map[1][0].isPerson = false;
						xCurrent = 9;
						yCurrent = 2;
						showInfo(userName);
					} else {
						for (int i = 0; i < LEVEL; i++) {
							free(mapFile[i]);
						}
						free(mapFile);
						exit(EXIT_SUCCESS);
					}
				}
			}
		}
	} else {
		for (int i = 0; i < LEVEL; i++) {
			free(mapFile[i]);
		}
		free(mapFile);
		exit(EXIT_SUCCESS);
	}
	system("pause");
	return 0;
}
