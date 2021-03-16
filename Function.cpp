#include"Function.h"
extern IMAGE wall, background, func, info, temp;
extern IMAGE path[12][10];
void move(int& x, int& y,int direction,
	Map map[][10], Node* flower, Node* jewel, Node* bomb) {

	bool isStart = true;
	int count = 0;
	int up, down, left, right;
	bool stop = false;
	int crossing = 0;
	int isFlower = 0;
	// 吃掉
	if (map[y][x].isPerson == PERSON) {
		map[y][x].isPerson = 0;
		if (map[y][x].isFLower == FLOWER) {
			map[y][x].isFLower = 0;
			attach(flower, jewel, bomb, x, y);
		}
	}
	putimage(x * 64, y * 64, &temp);
	while (1) {
		BeginBatchDraw();
		switch (direction) {
		case UP: {
			if (map[y - 1][x].isFLower == FLOWER) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y - 1][x].property == WALL) {
				stop = true;
			}
			if ((((map[y - 2][x].property == PATH || map[y - 2][x].isFLower == FLOWER) &&
				(map[y - 1][x - 1].property == PATH || map[y - 1][x - 1].isFLower == FLOWER))) ||
				(((map[y - 2][x].property == PATH || map[y - 2][x].isFLower == FLOWER) &&
				(map[y - 1][x + 1].property == PATH || map[y - 1][x + 1].isFLower == FLOWER)))) {
				crossing++;
				if (crossing == 64) {
					stop = true;
				}
			}
			if (isStart == true) {
				putimage(x * 64, y * 64, &path[y][x]);
				isStart = false;
				up = y * 64;
				up--;
				count++;
			}
			else {
				putimage(x * 64, up, &temp);
				up--;
				count++;
			}
			if (count % 64 == 0) {
				y--;
			}
			getimage(&temp, x * 64, up, 64, 64);
			putImageNB("resource\\2_b.png", "resource\\2.png", 64, 64, x * 64, up);
			FlushBatchDraw();
			Sleep(15);
			break;
		}
		case DOWN: {
			if (map[y + 1][x].isFLower == FLOWER) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y + 1][x].property == WALL) {
				stop = true;
			}
			if ((((map[y + 2][x].property == PATH || map[y + 2][x].isFLower == FLOWER) &&
				(map[y + 1][x - 1].property == PATH || map[y + 1][x - 1].isFLower == FLOWER))) ||
				(((map[y + 2][x].property == PATH || map[y + 2][x].isFLower == FLOWER) &&
				(map[y + 1][x + 1].property == PATH || map[y + 1][x + 1].isFLower == FLOWER)))) {
				crossing++;
				if (crossing == 64) {
					stop = true;
				}
			}
			if (isStart == true) {
				putimage(x * 64, y * 64, &path[y][x]);
				isStart = false;
				down = y * 64;
				down++;
				count++;
			}
			else {
				putimage(x * 64, down, &temp);
				down++;
				count++;
			}
			if (count % 64 == 0) {
				y++;
			}
			getimage(&temp, x * 64, down, 64, 64);
			putImageNB("resource\\2_b.png", "resource\\2.png", 64, 64, x * 64, down);
			FlushBatchDraw();
			Sleep(15);
			break;
		}
		case LEFT: {
			if (map[y][x - 1].isFLower == FLOWER) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y][x - 1].property == WALL) {
				stop = true;
			}
			if ((((map[y][x - 2].property == PATH || map[y][x - 2].isFLower == FLOWER) &&
				(map[y - 1][x - 1].property == PATH || map[y - 1][x - 1].isFLower == FLOWER))) ||
				(((map[y][x - 2].property == PATH || map[y][x - 2].isFLower == FLOWER) &&
				(map[y + 1][x - 1].property == PATH || map[y + 1][x - 1].isFLower == FLOWER)))) {
				crossing++;
				if (crossing == 64) {
					stop = true;
				}
			}
			if (isStart == true) {
				putimage(x * 64, y * 64, &path[y][x]);
				isStart = false;
				left = x * 64;
				left--;
				count++;
			}
			else {
				putimage(left, y * 64, &temp);
				left--;
				count++;
			}
			if (count % 64 == 0) {
				x--;
			}
			getimage(&temp, left, y * 64, 64, 64);
			putImageNB("resource\\2_b.png", "resource\\2.png", 64, 64, left, y * 64);
			FlushBatchDraw();
			Sleep(15);
			break;
		}
		case RIGHT: {
			if (map[y][x + 1].isFLower == FLOWER) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y][x + 1].property == WALL) {
				stop = true;
			}
			if ((((map[y][x + 2].property == PATH || map[y][x + 2].isFLower == FLOWER || 
				map[y][x + 2].property == ORIGIN) &&
				(map[y - 1][x + 1].property == PATH || map[y - 1][x + 1].isFLower == FLOWER))) ||
				(((map[y][x + 2].property == PATH || map[y][x + 2].isFLower == FLOWER) &&
				(map[y + 1][x + 1].property == PATH || map[y + 1][x + 1].isFLower == FLOWER)))) {
				crossing++;
				if (crossing == 64) {
					stop = true;
				}
			}
			if (isStart == true) {
				putimage(x * 64, y * 64, &path[y][x]);
				isStart = false;
				right = x * 64;
				right++;
				count++;
			}
			else {
				putimage(right, y * 64, &temp);
				right++;
				count++;
			}
			if (count % 64 == 0) {
				x++;
			}
			getimage(&temp, right, y * 64, 64, 64);
			putImageNB("resource\\2_b.png", "resource\\2.png", 64, 64, right, y * 64);
			FlushBatchDraw();
			Sleep(15);
			break;
		}
		default:
			stop = true;
			break;
		}
		EndBatchDraw();
		if (stop == true) {
			map[y][x].isPerson = PERSON;
			break;
		}
	}
}
void spaceHit(int x, int y, Map map[][10], Node *flower) {
	Node* current = flower;
	while (current->next) {
		current = current->next;
		if (current->x == x && current->y == y) {
			break;
		}
	}
	if (map[y][x].isFLower == FLOWER  && map[y][x].isPerson == PERSON && current->isExpose == false) {
		if (current->status == JEWEL) {
			putimage(x * 64, y * 64, &path[y][x]);
			putImageNB("resource\\24_b.png", "resource\\24.png", 64, 64, x * 64, y * 64);
			current->isExpose = true;
		} else if (current->status == BOMB) {
			putimage(x * 64, y * 64, &path[y][x]);
			putImageNB("resource\\25_b.png", "resource\\25.png", 64, 64, x * 64, y * 64);
			current->isExpose = true;
		}
	}
	else if (map[y][x].isFLower == FLOWER && map[y][x].isPerson == PERSON && current->isExpose == true) {
		putimage(x * 64, y * 64, &path[y][x]);
		putImageNB("resource\\23_b.png", "resource\\23.png", 64, 64, x * 64, y * 64);
		current->isExpose = false;
	}
}
void mouseControl(Node* flower, Node* jewel, Node* bomb, Map map[][10], char **name, int *x, int *y) {
	MOUSEMSG m;
	m = GetMouseMsg();
	mouseBounce(35, 95, m, "resource\\func1_c.png", "resource\\func1_b.png", "resource\\func1_cc.png",
				map, flower, jewel, bomb, name, display);
	mouseBounce(105, 165, m, "resource\\func2_c.png", "resource\\func2_b.png", "resource\\func2_cc.png",
				map, flower, jewel, bomb, name, increase);
	mouseBounce(175, 235, m, "resource\\func3_c.png", "resource\\func3_b.png", "resource\\func3_cc.png",
				map, flower, jewel, bomb, name, empty);
	mouseBounce(245, 305, m, "resource\\func4_c.png", "resource\\func4_b.png", "resource\\func4_cc.png",
				map, flower, jewel, bomb, name, quit);
	mouseBounce(315, 375, m, "resource\\func5_c.png", "resource\\func5_b.png", "resource\\func5_cc.png",
				map, flower, jewel, bomb, name, conserveData);
	if ((m.x >= 675 && m.x <= 925) && (m.y >= 385 && m.y <= 445) && m.uMsg == WM_LBUTTONDOWN) {
		putImageNB("resource\\func6_b.png", "resource\\func6_cc.png", 250, 60, 675, 385);
	}
	else if ((m.x >= 675 && m.x <= 925) && (m.y >= 385 && m.y <= 445) && m.uMsg == WM_LBUTTONUP) {
		putImageNB("resource\\func6_b.png", "resource\\func6_c.png", 250, 60, 675, 385);
		importData(map, flower, jewel, bomb, name, x, y);
	}
}
void mouseBounce(int y1, int y2, MOUSEMSG m, const char* img, const char* imgBack, const char* imgB,
				Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name, 
				void (*pf)(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name)) {

	if ((m.x >= 675 && m.x <= 925) && (m.y >= y1 && m.y <= y2) && m.uMsg == WM_LBUTTONDOWN) {
		if (*pf == display && flower->next != NULL && flower->next->isExpose == true) {
			putImageNB(imgBack, "resource\\func1_cc1.png", 250, 60, 675, y1);
		} else {
			putImageNB(imgBack, imgB, 250, 60, 675, y1);
		}
	}
	else if ((m.x >= 675 && m.x <= 925) && (m.y >= y1 && m.y <= y2) && m.uMsg == WM_LBUTTONUP) {
		if (*pf == display && flower->next != NULL && flower->next->isExpose == false) {
			putImageNB(imgBack, "resource\\func1_c1.png", 250, 60, 675, y1);
		} else {
			putImageNB(imgBack, img, 250, 60, 675, y1);
		}
		(*pf)(map, flower, jewel, bomb, name);
	}
}
void display(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	Node* fCurrent = flower->next;
	while (fCurrent != NULL) {
		if (fCurrent->status == JEWEL && fCurrent->isExpose == false && 
			map[fCurrent->y][fCurrent->x].isFLower == FLOWER && 
			map[fCurrent->y][fCurrent->x].isPerson != PERSON) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\4_b.png", "resource\\4.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->status == JEWEL && fCurrent->isExpose == false &&
				map[fCurrent->y][fCurrent->x].isFLower == FLOWER && 
				map[fCurrent->y][fCurrent->x].isPerson == PERSON) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\24_b.png", "resource\\24.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->status == BOMB && fCurrent->isExpose == false && 
				map[fCurrent->y][fCurrent->x].isFLower == FLOWER && 
				map[fCurrent->y][fCurrent->x].isPerson != PERSON) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\5_b.png", "resource\\5.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->status == BOMB && fCurrent->isExpose == false &&
				map[fCurrent->y][fCurrent->x].isFLower == FLOWER && 
				map[fCurrent->y][fCurrent->x].isPerson == PERSON) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\25_b.png", "resource\\25.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->isExpose == true && map[fCurrent->y][fCurrent->x].isFLower == FLOWER && 
				map[fCurrent->y][fCurrent->x].isPerson != PERSON) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\3_b.png", "resource\\3.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = false;
		}
		else if (fCurrent->isExpose == true && map[fCurrent->y][fCurrent->x].isFLower == FLOWER &&
			map[fCurrent->y][fCurrent->x].isPerson == PERSON) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\23_b.png", "resource\\23.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = false;
		}
		fCurrent = fCurrent->next;
	}
}
void increase(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	srand((unsigned)time(NULL));
	int x = rand() % 10;
	int y = rand() % 12;
	int count = 0;
	while (1) {
		if (map[y][x].property == PATH && map[y][x].isFLower != FLOWER && map[y][x].isPerson != PERSON) {
			create(flower, x, y);
			Node* s = flower->next;
			if (s->next) {
				if (s->next->isExpose == true) {
					switch (s->status) {
					case JEWEL:
						getimage(&path[y][x], x * 64, y * 64, 64, 64);
						putImageNB("resource\\4_b.png", "resource\\4.png", 64, 64, x * 64, y * 64);
						s->isExpose = true;
						map[y][x].isFLower = FLOWER;
						break;
					case BOMB:
						getimage(&path[y][x], x * 64, y * 64, 64, 64);
						putImageNB("resource\\5_b.png", "resource\\5.png", 64, 64, x * 64, y * 64);
						s->isExpose = true;
						map[y][x].isFLower = FLOWER;
						break;
					default:
						break;
					}
				}
				else {
					getimage(&path[y][x], x * 64, y * 64, 64, 64);
					putImageNB("resource\\3_b.png", "resource\\3.png", 64, 64, x * 64, y * 64);
					map[y][x].isFLower = FLOWER;
				}
			}
			else {
				getimage(&path[y][x], x * 64, y * 64, 64, 64);
				putImageNB("resource\\3_b.png", "resource\\3.png", 64, 64, x * 64, y * 64);
				map[y][x].isFLower = FLOWER;
			}
			break;
		}
		Node* current = flower;
		while (current->next) {
			current = current->next;
			count++;
		}
		if (count == 47) {
			break;
		} else {
			count = 0;
		}
		x = rand() % 10;
		y = rand() % 12;
	}
}
void empty(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	int selection = MessageBox(GetHWnd(), (LPCSTR)"这会删除您的所有数据，确定要清空吗?", (LPCSTR)"逃出迷宫",									MB_OKCANCEL | MB_ICONEXCLAMATION);
	if (selection == IDOK) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 10; j++) {
				if (map[i][j].isFLower == FLOWER) {
					putimage(j * 64, i * 64, &path[i][j]);
					map[i][j].isFLower = 0;
					if (map[i][j].isPerson == PERSON) {
						putImageNB("resource\\2_b.png", "resource\\2.png", 64, 64, j * 64, i * 64);
					}
				}
			}
		}
		clear(flower);
		clear(jewel);
		clear(bomb);
		//initFile(name, 0);
	}
}
void quit(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	int selection = MessageBox(GetHWnd(), (LPCSTR)"确定要退出游戏吗?", (LPCSTR)"逃出迷宫", MB_OKCANCEL |									MB_ICONQUESTION);
	if (selection == IDOK) {
		store(*name, map, flower, jewel, bomb);
		exit(EXIT_SUCCESS);
	}
}
bool isGameOver(int x, int y) {
	if (x == 0 && y == 1) {
		MessageBox(GetHWnd(), (LPCSTR)"通关成功!", (LPCSTR)"逃出迷宫", MB_OK);
		return true;
	} else {
		return false;
	}
}
