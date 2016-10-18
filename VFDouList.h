#pragma once
#include <Windows.h>

/* list�ڵ�*/
typedef struct taglistNode {
	struct taglistNode * prev;
	struct taglistNode * next;
	void * data;
	size_t len;
} listNode, *plistNode;
/*����ṹ*/
typedef struct tagList {
	taglistNode * head;
	taglistNode * tail;
	unsigned long len;
} List , *pList;

class VFDouList
{
public:
	VFDouList();
	~VFDouList();
	BOOL AddHead(void * data, int size);
	BOOL AddTail(void * data, int size);
	BOOL Insert(long index, void * data, int size, bool after);
	BOOL RemoveAt(long index);
	ULONG Find(void * data, UINT size);
	LPVOID GetAt(long index);
	UINT GetLengthAt(long index);
	ULONG GetLength();
private:
	pList list = NULL;

};

