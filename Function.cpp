#include"Function.h"
extern IMAGE wall, wallBack, background, func, info, temp;
extern IMAGE path[12][10];
extern IMAGE p, pBack, f, fBack, j, jBack, b, bBack;
void move(int& x, int& y,int direction,
	Map map[][10], Node* flower, Node* jewel, Node* bomb) {

	bool isStart = true;
	int count = 0;
	int up, down, left, right;
	bool stop = false;
	int crossing = 0;
	int isFlower = 0;

	// 消除花、刷新人的坐标
	if (map[y][x].isPerson) {
		map[y][x].isPerson = 0;
		if (map[y][x].isFLower) {
			map[y][x].isFLower = 0;
			attach(flower, jewel, bomb, x, y);
		}
	}
	putimage(x * 64, y * 64, &temp);

	// 移动
	while (1) {
		BeginBatchDraw();
		switch (direction) {
		case UP: {
			if (map[y - 1][x].isFLower) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y - 1][x].property == WALL) {
				stop = true;
			}
			if ((((map[y - 2][x].property == PATH || map[y - 2][x].isFLower) &&
				(map[y - 1][x - 1].property == PATH || map[y - 1][x - 1].isFLower))) ||
				(((map[y - 2][x].property == PATH || map[y - 2][x].isFLower) &&
				(map[y - 1][x + 1].property == PATH || map[y - 1][x + 1].isFLower)))) {
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
			putimage(x * 64, up, &pBack, SRCAND);
			putimage(x * 64, up, &p, SRCPAINT);
			FlushBatchDraw();
			Sleep(12);
			break;
		}
		case DOWN: {
			if (map[y + 1][x].isFLower) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y + 1][x].property == WALL) {
				stop = true;
			}
			if ((((map[y + 2][x].property == PATH || map[y + 2][x].isFLower) &&
				(map[y + 1][x - 1].property == PATH || map[y + 1][x - 1].isFLower))) ||
				(((map[y + 2][x].property == PATH || map[y + 2][x].isFLower) &&
				(map[y + 1][x + 1].property == PATH || map[y + 1][x + 1].isFLower)))) {
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
			putimage(x * 64, down, &pBack, SRCAND);
			putimage(x * 64, down, &p, SRCPAINT);
			FlushBatchDraw();
			Sleep(12);
			break;
		}
		case LEFT: {
			if (map[y][x - 1].isFLower) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y][x - 1].property == WALL) {
				stop = true;
			}
			if ((((map[y][x - 2].property == PATH || map[y][x - 2].isFLower) &&
				(map[y - 1][x - 1].property == PATH || map[y - 1][x - 1].isFLower))) ||
				(((map[y][x - 2].property == PATH || map[y][x - 2].isFLower) &&
				(map[y + 1][x - 1].property == PATH || map[y + 1][x - 1].isFLower)))) {
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
			putimage(left, y * 64, &pBack, SRCAND);
			putimage(left, y * 64, &p, SRCPAINT);
			FlushBatchDraw();
			Sleep(12);
			break;
		}
		case RIGHT: {
			if (map[y][x + 1].isFLower) {
				isFlower++;
				if (isFlower == 64) {
					stop = true;
				}
			}
			if (map[y][x + 1].property == WALL) {
				stop = true;
			}
			if ((((map[y][x + 2].property == PATH || map[y][x + 2].isFLower || 
				map[y][x + 2].property == ORIGIN) &&
				(map[y - 1][x + 1].property == PATH || map[y - 1][x + 1].isFLower))) ||
				(((map[y][x + 2].property == PATH || map[y][x + 2].isFLower) &&
				(map[y + 1][x + 1].property == PATH || map[y + 1][x + 1].isFLower)))) {
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
			putimage(right, y * 64, &pBack, SRCAND);
			putimage(right, y * 64, &p, SRCPAINT);
			FlushBatchDraw();
			Sleep(12);
			break;
		}
		default:
			stop = true;
			break;
		}
		EndBatchDraw();
		if (stop == true) {
			// 停下时刷新人的坐标
			map[y][x].isPerson = true;
			break;
		}
	}
}
void spaceHit(int x, int y, Map map[][10], Node *flower) {
	Node* current = flower;

	// 通过坐标定位
	while (current->next) {
		current = current->next;
		if (current->x == x && current->y == y) {
			break;
		}
	}

	// 判断该位置上花的状态
	if (map[y][x].isFLower && map[y][x].isPerson && current->isExpose == false) {
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
	else if (map[y][x].isFLower && map[y][x].isPerson && current->isExpose == true) {
		putimage(x * 64, y * 64, &path[y][x]);
		putImageNB("resource\\23_b.png", "resource\\23.png", 64, 64, x * 64, y * 64);
		current->isExpose = false;
	}
}
void mouseControl(Node* flower, Node* jewel, Node* bomb, Map map[][10], 
				char **name, int *x, int *y, char **mapFile, int *level, MOUSEMSG m) {

	// 通过mouseBounce连接函数
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

	// importData参数不同, 需要当前坐标
	if ((m.x >= 675 && m.x <= 925) && (m.y >= 385 && m.y <= 445) && m.uMsg == WM_LBUTTONDOWN) {
		putImageNB("resource\\func6_b.png", "resource\\func6_cc.png", 250, 60, 675, 385);
	}
	else if ((m.x >= 675 && m.x <= 925) && (m.y >= 385 && m.y <= 445) && m.uMsg == WM_LBUTTONUP) {
		putImageNB("resource\\func6_b.png", "resource\\func6_c.png", 250, 60, 675, 385);
		importData(map, flower, jewel, bomb, name, x, y, mapFile, level);
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

	// 通过链表判断当前的花是否暴露
	while (fCurrent != NULL) {
		if (fCurrent->status == JEWEL && fCurrent->isExpose == false && 
			map[fCurrent->y][fCurrent->x].isFLower && 
			map[fCurrent->y][fCurrent->x].isPerson == false) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putimage(fCurrent->x * 64, fCurrent->y * 64, &jBack, SRCAND);
			putimage(fCurrent->x * 64, fCurrent->y * 64, &j, SRCPAINT);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->status == JEWEL && fCurrent->isExpose == false &&
				map[fCurrent->y][fCurrent->x].isFLower && 
				map[fCurrent->y][fCurrent->x].isPerson) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\24_b.png", "resource\\24.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->status == BOMB && fCurrent->isExpose == false && 
				map[fCurrent->y][fCurrent->x].isFLower && 
				map[fCurrent->y][fCurrent->x].isPerson == false) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putimage(fCurrent->x * 64, fCurrent->y * 64, &bBack, SRCAND);
			putimage(fCurrent->x * 64, fCurrent->y * 64, &b, SRCPAINT);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->status == BOMB && fCurrent->isExpose == false &&
				map[fCurrent->y][fCurrent->x].isFLower && 
				map[fCurrent->y][fCurrent->x].isPerson) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\25_b.png", "resource\\25.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = true;
		}
		else if (fCurrent->isExpose == true && map[fCurrent->y][fCurrent->x].isFLower && 
				map[fCurrent->y][fCurrent->x].isPerson == false) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putimage(fCurrent->x * 64, fCurrent->y * 64, &fBack, SRCAND);
			putimage(fCurrent->x * 64, fCurrent->y * 64, &f, SRCPAINT);
			fCurrent->isExpose = false;
		}
		else if (fCurrent->isExpose == true && map[fCurrent->y][fCurrent->x].isFLower &&
			map[fCurrent->y][fCurrent->x].isPerson) {
			putimage(fCurrent->x * 64, fCurrent->y * 64, &path[fCurrent->y][fCurrent->x]);
			putImageNB("resource\\23_b.png", "resource\\23.png", 64, 64, fCurrent->x * 64, fCurrent->y * 64);
			fCurrent->isExpose = false;
		}
		fCurrent = fCurrent->next;
	}
}
void increase(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {

	// 获取随机数坐标
	srand((unsigned)time(NULL));
	int x = rand() % 10;
	int y = rand() % 12;
	int count = 0;

	// 通过循环不断取坐标直到符合条件
	while (1) {
		if (map[y][x].property == PATH && map[y][x].isFLower == false && map[y][x].isPerson == false) {
			create(flower, x, y);
			Node* s = flower->next;

			// 根据链表判断当前花是否暴露
			if (s->next) {
				if (s->next->isExpose == true) {
					switch (s->status) {
					case JEWEL:
						getimage(&path[y][x], x * 64, y * 64, 64, 64);
						putimage(x * 64, y * 64, &jBack, SRCAND);
						putimage(x * 64, y * 64, &j, SRCPAINT);
						s->isExpose = true;
						map[y][x].isFLower = true;
						break;
					case BOMB:
						getimage(&path[y][x], x * 64, y * 64, 64, 64);
						putimage(x * 64, y * 64, &bBack, SRCAND);
						putimage(x * 64, y * 64, &b, SRCPAINT);
						s->isExpose = true;
						map[y][x].isFLower = true;
						break;
					default:
						break;
					}
				}
				else {
					getimage(&path[y][x], x * 64, y * 64, 64, 64);
					putimage(x * 64, y * 64, &fBack, SRCAND);
					putimage(x * 64, y * 64, &f, SRCPAINT);
					map[y][x].isFLower = true;
				}
			}
			else {
				getimage(&path[y][x], x * 64, y * 64, 64, 64);
				putimage(x * 64, y * 64, &fBack, SRCAND);
				putimage(x * 64, y * 64, &f, SRCPAINT);
				map[y][x].isFLower = true;
			}
			break;
		}

		// 判断当前花的数量, 不大于47
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

		// 继续取随机数坐标
		x = rand() % 10;
		y = rand() % 12;
	}
}
void empty(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	int selection = MessageBox(GetHWnd(), (LPCSTR)"这会删除您的所有数据，确定要清空吗?", (LPCSTR)"逃出迷宫",									MB_OKCANCEL | MB_ICONEXCLAMATION);
	if (selection == IDOK) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 10; j++) {

				// 将有花的位置清空
				if (map[i][j].isFLower) {
					putimage(j * 64, i * 64, &path[i][j]);
					map[i][j].isFLower = 0;

					// 若花上有人，则重新贴人
					if (map[i][j].isPerson) {
						putimage(j * 64, i * 64, &pBack, SRCAND);
						putimage(j * 64, i * 64, &p, SRCPAINT);
					}
				}
			}
		}
		clear(flower);
	}
}
void quit(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	int selection = MessageBox(GetHWnd(), (LPCSTR)"确定要退出游戏吗?", (LPCSTR)"逃出迷宫", MB_OKCANCEL |									MB_ICONQUESTION);
	if (selection == IDOK) {
		exit(EXIT_SUCCESS);
	}
}
bool isGameOver(int x, int y) {
	if (x == 0 && y == 1) {
		MessageBox(GetHWnd(), (LPCSTR)"通关成功!", (LPCSTR)"逃出迷宫", MB_OK);
		return true;
	}
	return false;
}
