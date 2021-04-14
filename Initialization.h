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

// 界面元素
enum Stuff {
	PATH,
	WALL,
	ORIGIN,
	FLOWER,
	PERSON
};

// 花状态
enum Status {
	JEWEL,
	BOMB
};

// 方向
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// 地图属性
typedef struct list {
	int property;
	int isFLower;
	int isPerson;
}Map;

// 链表节点
typedef struct node {
	int score;
	int status;
	bool isExpose;
	int x;
	int y;
	struct node* next;
}Node;

// 从文件读取的坐标
typedef struct info {
	int x;
	int y;
}MemoryInfo;

// 系统初始化
void initialize(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name, char *mapFile);
void initMapFile(char*** mapFile);

// 界面布局模块
bool start();
void initBoundary(Map map[][10], Node* flower, char **name, int& numberOfFlower, char *mapFile);
void initFile(char **name, int numberOfFlower, Node *flower);
void resetBoundary(Map map[][10], char *mapFile, Node *flower);
int enterNumber();
void enterName(char **name);
void putImageNB(const char* back, const char* image, int width, int height, int x, int y);


// 链表模块
Node* initNode();
void create(Node* head, int X, int Y);
void attach(Node* flower, Node *jewel, Node *bomb, int x, int y);
void clear(Node* head);
void createAcquire(Node* head, int score);

#endif // !ESCAPE_INITIALIZATION_H