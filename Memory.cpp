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
	int *jewelScore;
	int *bombScore;
	MemoryInfo *position;
	int xPerson = 0, yPerson = 0;
	int currentLevel = level + 1;
	time_t now;
	time(&now);
	struct tm* tmNow;
	tmNow = localtime(&now);

	if (!(jewelScore = (int*)malloc(sizeof(int) * 160))) {
		MessageBox(GetHWnd(), (LPCSTR)"�ڴ����1!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	} else {
		memset(jewelScore, 0, sizeof(int) * 160);
	}
	if (!(bombScore = (int*)malloc(sizeof(int) * 160))) {
		MessageBox(GetHWnd(), (LPCSTR)"�ڴ����2!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	} else {
		memset(bombScore, 0, sizeof(int) * 160);
	}
	if (!(position = (MemoryInfo*)malloc(sizeof(MemoryInfo) * 60))) {
		MessageBox(GetHWnd(), (LPCSTR)"�ڴ����3!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	} else {
		memset(position, 0, sizeof(MemoryInfo) * 60);
	}

	// ��ȡjewel�÷֡��ܵ÷ֺ͸���
	for (int i = 0; jewel->next; i++) {
		jewel = jewel->next;
		score += jewel->score;
		jewelScore[i] = jewel->score;
		numberOfJewel++;
	}

	// ��ȡbomb�÷֡��ܵ÷ֺ͸���
	for (int i = 0; bomb->next; i++) {
		bomb = bomb->next;
		score -= bomb->score;
		bombScore[i] = bomb->score;
		numberOfBomb++;
	}

	// ��ȡ���ĸ���������
	for (int i = 0; flower->next; i++) {
		flower = flower->next;
		position[i].x = flower->x;
		position[i].y = flower->y;
		numberOfFlower++;
	}

	// ��ȡ�˵�����
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j].isPerson) {
				xPerson = j;
				yPerson = i;
			}
		}
	}

	// ���ļ�д��
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
	free(jewelScore);
	free(bombScore);
	free(position);
}
void showInfo(char* name) {
	char fileName[50];
	sprintf(fileName, "AppData\\%s.txt", name);
	char userName[20];
	char score[20];
	char timeNow[20];
	char level[10];

	// ��ȡ��Ҫ��ʾ����Ϣ
	FILE* fp = fopen(fileName, "r");
	fgets(userName, 20, fp);
	fgets(level, 10, fp);
	fgets(score, 20, fp);
	fgets(timeNow, 20, fp);
	fclose(fp);

	// ����������ʽ
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 15, (LPCTSTR)"Consolas");

	// �������
	BeginBatchDraw();
	putimage(640, 480, &info);
	outtextxy(675, 510, (LPCTSTR)userName);
	outtextxy(675, 560, (LPCTSTR)level);
	outtextxy(675, 610, (LPCTSTR)score);
	outtextxy(675, 660, (LPCTSTR)timeNow);
	EndBatchDraw();
}
void conserveData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name) {
	// ����ÿ���ƶ������д洢��ʵ�����Զ��洢���ʲ���Ҫ����ʵ��
	MessageBox(GetHWnd(), (LPCSTR)"�浵�ɹ�!", (LPCSTR)"�ӳ��Թ�", MB_OK);
}
void importData(Map map[][10], Node* flower, Node* jewel, Node* bomb, 
				char **name, int *x, int *y, char **mapFile, int *level) {
	
	char fileName[50];
	char importName[20];
	MemoryInfo *position;
	int *jewelScore;
	int *bombScore;
	int numberOfJewel = 0;
	int numberOfBomb = 0;
	int currentLevel = 0;
	bool confirm = InputBox((LPTSTR)importName, 20, "�����뵼����û���:", "�ӳ��Թ�", "Default", 0, 0, false);
	if (confirm) {
		sprintf(fileName, "AppData\\%s.txt", importName);
		if (_access(fileName, 0) == 0) {

			// Ϊ����������ڴ�
			jewelScore = (int*)malloc(sizeof(int) * 160);
			memset(jewelScore, 0, sizeof(int) * 160);
			bombScore = (int*)malloc(sizeof(int) * 160);
			memset(bombScore, 0, sizeof(int) * 160);
			position = (MemoryInfo*)malloc(sizeof(MemoryInfo) * 60);
			memset(position, 0, sizeof(MemoryInfo) * 60);

			// ��ȡ�ļ�
			scanFile(fileName, jewelScore, bombScore, position, 
					jewel, bomb, &numberOfJewel, &numberOfBomb, &currentLevel);
			currentLevel--;
			*level = currentLevel;

			// �޸ĵ�ǰ�û���
			memset(*name, '\0', sizeof(*name));
			strcpy(*name, importName);

			// �жϵ�����ļ��Ƿ��ڵ�����ͨ��
			if (position[0].x == 0 && position[0].y == 1) {

				// ��������
				map[0][1].isPerson = false;
				*x = 9;
				*y = 2;

				// �������
				clear(jewel);
				clear(bomb);

				// ���ùؿ�
				*level = 0;
				resetBoundary(map, mapFile[0], flower);
				store(*name, map, flower, jewel, bomb, 1);
			} else {

				// ��յ�ͼ����
				for (int i = 0; i < 12; i++) {
					memset(map[i], 0, sizeof(Map) * 10);
				}

				// ���õ�ͼ����
				FILE* fp = fopen(mapFile[currentLevel], "r");
				for (int i = 0; i < 12; i++) {
					for (int j = 0; j < 10; j++) {
						if (!fscanf(fp, "%d", &map[i][j].property)) {
							MessageBox(GetHWnd(), (LPCSTR)"��ȡ��ͼ����!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
							exit(EXIT_FAILURE);
						}
					}
				}
				fclose(fp);

				// �������
				clear(flower);
				clear(jewel);
				clear(bomb);

				// ���»��Ƶ�ͼ
				clearrectangle(0, 0, 640, 768);
				putimage(0, 0, &background);
				for (int i = 0; i < 12; i++) {
					for (int j = 0; j < 10; j++) {
						switch (map[i][j].property) {
						case PATH:
							// ��ȡ���е�·�汳��ͼ
							getimage(&path[i][j], j * 64, i * 64, 64, 64);
							break;
						case WALL:
							putimage(j * 64, i * 64, &wallBack, SRCAND);
							putimage(j * 64, i * 64, &wall, SRCPAINT);
							break;
						case ORIGIN:
							getimage(&path[i][j], j * 64, i * 64, 64, 64);
							break;
						default:
							break;
						}
					}
				}

				// ����ʣ��С��
				for (int i = 1; position[i].x != 0 && position[i].y != 0; i++) {
					map[position[i].y][position[i].x].isFLower = true;
					putimage(position[i].x * 64, position[i].y * 64, &fBack, SRCAND);
					putimage(position[i].x * 64, position[i].y * 64, &f, SRCPAINT);
					create(flower, position[i].x, position[i].y);
				}

				// ��������
				for (int i = 0; i < numberOfJewel; i++) {
					createAcquire(jewel, jewelScore[i]);
				}
				for (int i = 0; i < numberOfBomb; i++) {
					createAcquire(bomb, bombScore[i]);
				}

				// �޸�����������Ϣ
				*x = position[0].x;
				*y = position[0].y;
				putimage(position[0].x * 64, position[0].y * 64, &pBack, SRCAND);
				putimage(position[0].x * 64, position[0].y * 64, &p, SRCPAINT);
				map[position[0].y][position[0].x].isPerson = true;
			}
			showInfo(importName);
			free(jewelScore);
			free(bombScore);
			free(position);
		} else {
			MessageBox(GetHWnd(), (LPCSTR)"�ļ�������!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		}
	}
}
void scanFile(char *fileName, int jewelScore[], int bombScore[], MemoryInfo position[],
			Node* jewel, Node* bomb, int *numberOfJewel, int *numberOfBomb, int *level) {

	int numberOfFlower = 0;
	FILE* fp = fopen(fileName, "r");
	char buffer[50] = { '\0' };
	int line = 0;

	// ��ȡ����
	while (fgets(buffer, 50, fp) != NULL) {
		line++;
	}
	fclose(fp);

	// �����ı�����
	if (line < 15) {
		MessageBox(GetHWnd(), (LPCSTR)"��ȡ����1!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	char** text = (char**)malloc(sizeof(char*) * line);
	if (!text) {
		MessageBox(GetHWnd(), (LPCSTR)"�ı��ڴ����1!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < line; i++) {
		text[i] = (char*)malloc(sizeof(char) * 50);
		if (!text[i]) {
			MessageBox(GetHWnd(), (LPCSTR)"�ı��ڴ����2!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
		memset(text[i], '\0', sizeof(char) * 50);
	}

	// ��ȡ�ı�
	fp = fopen(fileName, "r");
	for (int i = 0; i < line; i++) {
		fgets(text[i], 50, fp);
	}
	fclose(fp);

	// ���ı���ȡ����
	if (!sscanf(text[1], "Level:%d", level)) {
		MessageBox(GetHWnd(), (LPCSTR)"��ȡ����2!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (!sscanf(text[6], "x = %d y = %d", &position[0].x, &position[0].y)) {
		MessageBox(GetHWnd(), (LPCSTR)"��ȡ����3!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (!sscanf(text[8], "Acquired Jewel:%d", numberOfJewel)) {
		MessageBox(GetHWnd(), (LPCSTR)"��ȡ����4!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	if (!sscanf(text[10], "Acquired Bomb:%d", numberOfBomb)) {
		MessageBox(GetHWnd(), (LPCSTR)"��ȡ����5!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	int i = 0;
	int n = 0;
	while (text[9][i] != '\0') {
		if (isdigit(text[9][i])) {
			jewelScore[n] = text[9][i] - '0';
			n++;
		}
		i++;
	}
	i = 0;
	n = 0;
	while (text[11][i] != '\0') {
		if (isdigit(text[11][i])) {
			bombScore[n] = text[11][i] - '0';
			n++;
		}
		i++;
	}
	for (int i = 15, k = 1; i < line; i++, k++) {
		if (!sscanf(text[i], "x = %d y = %d\n", &position[k].x, &position[k].y)) {
			MessageBox(GetHWnd(), (LPCSTR)"��ȡ����6!", (LPCSTR)"�ӳ��Թ�", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

	// �ͷſռ�
	for (int i = 0; i < line; i++) {
		if (text[i]) {
			free(text[i]);
		}
	}
	free(text);
}
