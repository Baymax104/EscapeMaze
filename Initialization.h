#ifndef ESCAPEMAZE_INITIALIZATION_H
#define ESCAPEMAZE_INITIALIZATION_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<ctype.h>
#include<Windows.h>
#include<io.h>
#include<mmsyscom.h>
#pragma comment(lib, "Winmm.lib")

#define  UP_KEY    72
#define  DOWN_KEY  80
#define  LEFT_KEY  75
#define  RIGHT_KEY 77

#define LEVEL 3

// ����Ԫ��
enum Stuff {
	PATH,
	WALL,
	ORIGIN,
	FLOWER,
	PERSON
};

// ��״̬
enum Status {
	JEWEL,
	BOMB
};

// ����
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// ��ͼ����
typedef struct list {
	int property;
	int isFLower;
	int isPerson;
}Map;

// ����ڵ�
typedef struct node {
	int score;
	int status;
	bool isExpose;
	int x;
	int y;
	struct node* next;
}Node;

// ���ļ���ȡ������
typedef struct info {
	int x;
	int y;
}MemoryInfo;

// ϵͳ��ʼ��
void initialize(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name, char *mapFile);
void initMapFile(char*** mapFile);

// ���沼��ģ��
bool start();
void initBoundary(Map map[][10], Node* flower, char **name, int& numberOfFlower, char *mapFile);
void initFile(char **name, int numberOfFlower, Node *flower);
void resetBoundary(Map map[][10], char *mapFile, Node *flower);
int enterNumber();
void enterName(char **name);
void putImageNB(const char* back, const char* image, int width, int height, int x, int y);


// ����ģ��
Node* initNode();
void create(Node* head, int X, int Y);
void attach(Node* flower, Node *jewel, Node *bomb, int x, int y);
void clear(Node* head);
void createAcquire(Node* head, int score);

#endif // !ESCAPE_INITIALIZATION_H