#ifndef ESCAPEMAZE_MEMORY_H
#define ESCAPEMAZE_MEMORY_H

#include"Initialization.h"

// 存储
void store(char *name, Map map[][10], Node* flower, Node* jewel, Node* bomb);

// 显示信息
void showInfo(char* name);

// 存档
void conserveData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);

// 导入
void importData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name, int *x, int *y);

// 扫描文件
void scanFile(char *fileName,int jewelScore[], int bombScore[], MemoryInfo position[], 
			Node* jewel, Node* bomb, int *numberOfJewel, int *numberOfBomb);

#endif // !ESCAPEMAZE_MEMORY_H