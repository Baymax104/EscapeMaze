#ifndef ESCAPEMAZE_MEMORY_H
#define ESCAPEMAZE_MEMORY_H

#include"Initialization.h"

// �洢
void store(char *name, Map map[][10], Node* flower, Node* jewel, Node* bomb);

// ��ʾ��Ϣ
void showInfo(char* name);

// �浵
void conserveData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name);

// ����
void importData(Map map[][10], Node* flower, Node* jewel, Node* bomb, char **name, int *x, int *y);

// ɨ���ļ�
void scanFile(char *fileName,int jewelScore[], int bombScore[], MemoryInfo position[], 
			Node* jewel, Node* bomb, int *numberOfJewel, int *numberOfBomb);

#endif // !ESCAPEMAZE_MEMORY_H