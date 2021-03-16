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

#define  UP_KEY    72
#define  DOWN_KEY  80
#define  LEFT_KEY  75
#define  RIGHT_KEY 77

enum Stuff {
	PATH,
	WALL,
	ORIGIN,
	FLOWER,
	PERSON
};
enum Status {
	JEWEL,
	BOMB
};
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
typedef struct list {
	int property;
	int isFLower;
	int isPerson;
}Map;
typedef struct node {
	int score;
	int status;
	bool isExpose;
	int x;
	int y;
	struct node* next;
}Node;
typedef struct info {
	int x;
	int y;
}MemoryInfo;

// 系统初始化
void initialize(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);

// 界面布局模块
void initBoundary(Map map[][10], Node* flower, char **name, int& numberOfFlower);
void initFile(char **name, int numberOfFlower);
void putImageNB(const char* back, const char* image, int width, int height, int x, int y);
int enterNumber();
void enterName(char **name);


// 链表模块
Node* initNode();
void create(Node* head, int X, int Y);
void attach(Node* flower, Node *jewel, Node *bomb, int x, int y);
void clear(Node* head);
void createAcquire(Node* head, int score);

#endif // !ESCAPE_INITIALIZATION_H