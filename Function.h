#ifndef ESCAPEMAZE_FUNCTION_H
#define ESCAPEMAZE_FUNCTION_H

#include"Memory.h"

//游戏运行
bool isGameOver(int x, int y);
void move(int& x, int& y, int direction,
	Map map[][10], Node* flower, Node* jewel, Node* bomb);
void spaceHit(int x, int y, Map map[][10], Node *flower);

// 控制区功能
void mouseControl(Node *flower, Node *jewel, Node *bomb, Map map[][10], char **name, int *x, int *y);
void mouseBounce(int y1, int y2, MOUSEMSG m, const char* img, const char* imgBack, const char* imgB,
				Map map[][10], Node *flower, Node *jewel, Node *bomb, char **name, 
				void (*pf)(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name));
void display(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);
void increase(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);
void empty(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);
void quit(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);

#endif // !ESCAPEMAZE_FUNCTION_H