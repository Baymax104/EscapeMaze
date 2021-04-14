#include"Memory.h"
extern IMAGE wall, wallBack, background, func, info, temp;
extern IMAGE path[12][10];
extern IMAGE p, pBack, f, fBack, j, jBack, b, bBack;
void store(char *name, Map map[][10], Node* flower, Node* jewel, Node* bomb, int level) {
	char fileName[50];
	sprintf(fileName, "AppData\\%s.txt", name);
	int score = 0;
	int numberOfFlower = 0;
	int numberOfJewel = 0;
	int numberOfBomb = 0;
	int jewelScore[50];
	int bombScore[50];
	MemoryInfo position[50] = {0};
	int xPerson = 0, yPerson = 0;
	time_t now;
	time(&now);
	struct tm* tmNow;
	tmNow = localtime(&now);

	// 获取jewel得分、总得分和个数
	for (int i = 0; jewel->next; i++) {
		jewel = jewel->next;
		score += jewel->score;
		jewelScore[i] = jewel->score;
		numberOfJewel++;
	}

	// 获取bomb得分、总得分和个数
	for (int i = 0; bomb->next; i++) {
		bomb = bomb->next;
		score -= bomb->score;
		bombScore[i] = bomb->score;
		numberOfBomb++;
	}

	// 获取花的个数及坐标
	for (int i = 0; flower->next; i++) {
		flower = flower->next;
		position[i].x = flower->x;
		position[i].y = flower->y;
		numberOfFlower++;
	}

	// 获取人的坐标
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j].isPerson == PERSON) {
				xPerson = j;
				yPerson = i;
			}
		}
	}

	// 打开文件写入
	FILE* fp = fopen(fileName, "w");
	fprintf(fp, "Username:%s\nLevel:%d\nScore:%d\n", name, level, score);
	fprintf(fp, "Time:%d-%d-%d\n", tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday);
	fprintf(fp, "--------------------------------------\n");
	fprintf(fp, "Person:\nx = %d y = %d\n", xPerson, yPerson);
	fprintf(fp, "--------------------------------------\n");
	fprintf(fp, "Acquired Jewel:%d\n", numberOfJewel);
	for (int i = 0; i < numberOfJewel; i++) {
		fprintf(fp, "%d ", jewelScore[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "Acquired Bomb:%d\n", numberOfBomb);
	for (int i = 0; i < numberOfBomb; i++) {
		fprintf(fp, "%d ", bombScore[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "--------------------------------------\n");
	fprintf(fp, "Flower:\nnumber:%d\n", numberOfFlower);
	for (int i = 0; i < numberOfFlower; i++) {
		fprintf(fp, "x = %d y = %d\n", position[i].x, position[i].y);
	}
	fclose(fp);
}
void showInfo(char* name) {
	char fileName[50];
	sprintf(fileName, "AppData\\%s.txt", name);
	char userName[20];
	char score[20];
	char timeNow[20];
	char level[10];

	// 获取需要显示的信息
	FILE* fp = fopen(fileName, "r");
	fgets(userName, 20, fp);
	fgets(level, 10, fp);
	fgets(score, 20, fp);
	fgets(timeNow, 20, fp);
	fclose(fp);

	// 设置文字样式
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 15, (LPCTSTR)"Consolas");

	// 文字输出
	BeginBatchDraw();
	putimage(640, 480, &info);
	outtextxy(675, 510, (LPCTSTR)userName);
	outtextxy(675, 560, (LPCTSTR)level);
	outtextxy(675, 610, (LPCTSTR)score);
	outtextxy(675, 660, (LPCTSTR)timeNow);
	EndBatchDraw();
}
void conserveData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	// 由于每次移动都进行了存储，实现了自动存储，故不需要额外实现
	MessageBox(GetHWnd(), (LPCSTR)"存档成功!", (LPCSTR)"逃出迷宫", MB_OK);
}
void importData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name, int *x, int *y, int level) {
	
	char fileName[50];
	char importName[20];
	MemoryInfo position[50] = { {0, 0} };
	MemoryInfo *ptrPos = position;
	int jewelScore[50] = {0};
	int bombScore[50] = {0};
	int numberOfJewel = 0;
	int numberOfBomb = 0;
	bool confirm = InputBox((LPTSTR)importName, 20, "请输入导入的用户名:", "逃出迷宫", "Default", 0, 0, false);
	if (confirm) {
		store(*name, map, flower, jewel, bomb, level);
		sprintf(fileName, "AppData\\%s.txt", importName);
		if (_access(fileName, 0) == 0) {

			// 读取文件
			scanFile(fileName, jewelScore, bombScore, ptrPos, 
					jewel, bomb, &numberOfJewel, &numberOfBomb);

			// 初始化
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 10; j++) {
					if (map[i][j].isFLower == FLOWER) {
						putimage(j * 64, i * 64, &path[i][j]);
						map[i][j].isFLower = 0;
					}
					if (map[i][j].isPerson == PERSON) {
						putimage(j * 64, i * 64, &path[i][j]);
						map[i][j].isPerson = 0;
					}
				}
			}
			clear(flower);
			clear(jewel);
			clear(bomb);

			// 绘图
			for (int i = 1; position[i].x != 0 && position[i].y != 0; i++) {
				map[position[i].y][position[i].x].isFLower = FLOWER;
				putimage(position[i].x * 64, position[i].y * 64, &fBack, SRCAND);
				putimage(position[i].x * 64, position[i].y * 64, &f, SRCPAINT);
			}

			// 创建链表
			for (int i = 0; i < numberOfJewel; i++) {
				createAcquire(jewel, jewelScore[i]);
			}
			for (int i = 0; i < numberOfBomb; i++) {
				createAcquire(bomb, bombScore[i]);
			}
			for (int i = 1; position[i].x != 0 && position[i].y != 0; i++) {
				create(flower, position[i].x, position[i].y);
			}

			// 修改当前信息
			map[position[0].y][position[0].x].isPerson = PERSON;
			memset(*name, '\0', sizeof(*name));
			strcpy(*name, importName);
			if (position[0].x == 0 && position[0].y == 1) {
				*x = 9;
				*y = 2;
				//initialize(map, flower, jewel, bomb, name);
			} else {
				*x = position[0].x;
				*y = position[0].y;
				putimage(position[0].x * 64, position[0].y * 64, &pBack, SRCAND);
				putimage(position[0].x * 64, position[0].y * 64, &p, SRCPAINT);
			}
			showInfo(*name);
		} else {
			MessageBox(GetHWnd(), (LPCSTR)"文件不存在!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
		}
	}
}
void scanFile(char *fileName, int jewelScore[], int bombScore[], MemoryInfo position[],
			Node* jewel, Node* bomb, int *numberOfJewel, int *numberOfBomb) {

	int numberOfFlower = 0;
	FILE* fp = fopen(fileName, "r");
	char buffer[50] = { '\0' };
	int line = 0;

	// 创建文本数组
	while (fgets(buffer, 50, fp) != NULL) {
		line++;
	}
	if (line < 14) {
		MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	char** text = (char**)malloc(sizeof(char*) * line);
	if (!text) {
		MessageBox(GetHWnd(), (LPCSTR)"内存错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < line; i++) {
		text[i] = (char*)malloc(sizeof(char) * 50);
		if (!text[i]) {
			MessageBox(GetHWnd(), (LPCSTR)"内存错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

	// 读取文本
	rewind(fp);
	for (int i = 0; i < line; i++) {
		fgets(text[i], 50, fp);
	}
	fclose(fp);

	// 读取文本数据
	if (!sscanf(text[5], "x = %d y = %d", &position[0].x, &position[0].y)) {
		MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (!sscanf(text[7], "Acquired Jewel:%d", numberOfJewel)) {
		MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (!sscanf(text[9], "Acquired Bomb:%d", numberOfBomb)) {
		MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < *numberOfJewel; i++) {
		if (!sscanf(text[8], "%d", &jewelScore[i])) {
			MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < *numberOfBomb; i++) {
		if (!sscanf(text[10], "%d", &bombScore[i])) {
			MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 14, k = 1; i < line; i++, k++) {
		if (!sscanf(text[i], "x = %d y = %d", &position[k].x, &position[k].y)) {
			MessageBox(GetHWnd(), (LPCSTR)"读取错误!", (LPCSTR)"逃出迷宫", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

	// 释放空间
	for (int i = 0; i < line; i++) {
		if (text[i]) {
			free(text[i]);
		}
	}
	free(text);
}
