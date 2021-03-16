#include"Initialization.h"
IMAGE wall, background,func, info, temp;
IMAGE path[12][10] = { NULL };// �洢��λ�õĵ���
void initialize(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	int numberOfFlower = 0;
	initBoundary(map, flower, name, numberOfFlower);
	initFile(name, numberOfFlower);
}
void initBoundary(Map map[][10], Node* flower, char **name, int& numberOfFlower) {
	FILE* fp = fopen("resource\\map.txt", "r");
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 10; j++) {
			fscanf(fp, "%d", &map[i][j].property);
		}
	}
	fclose(fp);
	initgraph(960, 768);
	loadimage(&wall, (LPCTSTR)"resource\\1.png", 64, 64);
	loadimage(&background, (LPCTSTR)"resource\\0.png", 640, 768);
	putimage(0, 0, &background);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 10; j++) {
			switch (map[i][j].property) {
			case PATH:
				getimage(&path[i][j], j * 64, i * 64, 64, 64);
				break;
			case WALL:
				putImageNB("resource\\1_b.png", "resource\\1.png", 64, 64, j * 64, i * 64);
				break;
			case ORIGIN:
				getimage(&path[i][j], j * 64, i * 64, 64, 64);
				getimage(&temp, j * 64 - 1, i * 64, 64, 64);
				putImageNB("resource\\2_b.png", "resource\\2.png", 64, 64, j * 64, i * 64);
				map[i][j].isPerson = PERSON;
			default:
				break;
			}
		}
	}
	loadimage(&func, (LPCTSTR)"resource\\FuncArea.png", 320, 480);
	loadimage(&info, (LPCTSTR)"resource\\InfoArea.png", 320, 288);
	putimage(640, 0, &func);
	putimage(640, 480, &info);
	putImageNB("resource\\func1_b.png", "resource\\func1_c.png", 250, 60, 675, 35);
	putImageNB("resource\\func2_b.png", "resource\\func2_c.png", 250, 60, 675, 105);
	putImageNB("resource\\func3_b.png", "resource\\func3_c.png", 250, 60, 675, 175);
	putImageNB("resource\\func4_b.png", "resource\\func4_c.png", 250, 60, 675, 245);
	putImageNB("resource\\func5_b.png", "resource\\func5_c.png", 250, 60, 675, 315);
	putImageNB("resource\\func6_b.png", "resource\\func6_c.png", 250, 60, 675, 385);
	enterName(name);
	numberOfFlower = enterNumber();
	int x, y;
	srand((unsigned)time(NULL));
	int count = 0;
	while (1) {
		x = rand() % 10;
		y = rand() % 12;
		if (map[y][x].property == PATH && map[y][x].isFLower != FLOWER) {
			if (count == numberOfFlower) {
				break;
			}
			//getimage(&path[y][x], x * 64, y * 64, 64, 64);
			putImageNB("resource\\3_b.png", "resource\\3.png", 64, 64, x * 64, y * 64);
			map[y][x].isFLower = FLOWER;
			create(flower, x, y);
			count++;
		}
	}
}
void initFile(char **name, int numberOfFlower) {
	char fileName[50];
	time_t now;
	time(&now);
	struct tm* tmNow;
	tmNow = localtime(&now);
	if (strcmp((*name), "") == 0) {
		*name = (char*)"Default";
	}
	sprintf(fileName, "AppData\\%s.txt", *name);
	FILE* fp = fopen(fileName, "w");
	fprintf(fp, "Username:%s\nScore:0\nTime:%d-%d-%d\n", *name, tmNow->tm_year + 1900, 
			tmNow->tm_mon + 1, tmNow->tm_mday);
	fprintf(fp, "--------------------------------------\n");
	fprintf(fp, "Person:\n");
	fprintf(fp, "x = 9, y = 2\n");
	fprintf(fp, "--------------------------------------\n");
	fprintf(fp, "Acquired Jewel:0\n");
	fprintf(fp, "\n");
	fprintf(fp, "Acquired bomb:0\n");
	fprintf(fp, "\n");
	fprintf(fp, "--------------------------------------\n");
	fprintf(fp, "Flower:\nnumber:%d\n", numberOfFlower);
	fclose(fp);
}
int enterNumber() {
	char num[3];
	InputBox((LPTSTR)num, 3, "������С�����ɵ�����:", "�ӳ��Թ�", "5", 0, 0, true);
	int number = atoi(num);
	return number;
}
void enterName(char **name) {
	InputBox((LPTSTR)(*name), 20, "�����������û���:", "�ӳ��Թ�", "Default", 0, 0, true);
}
void putImageNB(const char* back, const char* image, int width, int height, int x, int y) {
	IMAGE img, imgBack;
	loadimage(&imgBack, (LPCTCH)back, width, height);
	loadimage(&img, (LPCTCH)image, width, height);
	putimage(x, y, &imgBack, SRCAND);
	putimage(x, y, &img, SRCPAINT);
}
Node* initNode() {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node) {
		node->next = NULL;
		node->x = -1;
		node->y = -1;
		node->isExpose = false;
		node->score = 0;
		node->status = 0;
		return node;
	}
	return NULL;
}
void create(Node *head, int X, int Y) {
	Node* s = (Node*)malloc(sizeof(Node));
	if (s) {
		s->score = (rand() % 9) + 1;
		s->status = rand() % 2;
		s->isExpose = false;
		s->x = X;
		s->y = Y;
		s->next = head->next;
		head->next = s;
	}
}
void attach(Node* flower, Node* jewel, Node* bomb, int x, int y) {
	Node* preSwap = flower;
	Node* swap;
	if (preSwap) {
		while (preSwap->next) {
			if (preSwap->next->x == x && preSwap->next->y == y) {
				break;
			}
			preSwap = preSwap->next;
		}
		if (preSwap->next->status == JEWEL) {
			swap = preSwap->next;
			preSwap->next = swap->next;
			swap->next = jewel->next;
			jewel->next = swap;
		} else if (preSwap->next->status == BOMB) {
			swap = preSwap->next;
			preSwap->next = swap->next;
			swap->next = bomb->next;
			bomb->next = swap;
		}
	}
}
void clear(Node* head) {
	Node* freeNode;
	Node* current = head->next;
	while (current) {
		freeNode = current;
		current = freeNode->next;
		free(freeNode);
	}
	head->next = NULL;
}
void createAcquire(Node* head, int score) {
	Node* s = (Node*)malloc(sizeof(Node));
	if (s) {
		s->isExpose = false;
		s->status = 0;
		s->x = 0;
		s->y = 0;
		s->score = score;
		s->next = head->next;
		head->next = s;
	}
}