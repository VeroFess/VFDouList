#include "VFDouList.h"

VFDouList::VFDouList(){
	if ((list = (pList)malloc(sizeof(*list))) == NULL) {
		return;
	}
	list->head = list->tail = NULL;
	list->len = 0;
}

VFDouList::~VFDouList(){
	if (!list) {
		return;
	}
	unsigned long len;
	plistNode current, next;
	current = list->head;
	len = list->len;
	while (len--) {
		next = current->next;
		if (current->data) {
			free(current->data);
		}
		free(current);                              
		current = next;
	}
	free(list);
}

BOOL VFDouList::AddHead(void * data,int size){
	plistNode pNode;
	if (!list) {
		return FALSE;
	}
	if ((pNode = (plistNode)malloc(sizeof(listNode))) == NULL) {
		return FALSE;
	}
	if ((pNode->data = malloc(size + 1)) == NULL) {
		free(pNode);
		return FALSE;
	}
	memset(pNode->data, 0, size + 1);
	memcpy(pNode->data, data, size);
	pNode->len = size;
	if (list->len == 0) {
		list->head = list->tail = pNode;
		pNode->prev = pNode->next = NULL;
	}else {
		pNode->prev = NULL;
		pNode->next = list->head;
		list->head->prev = pNode;
		list->head = pNode;
	}
	list->len++;
	return TRUE;
}

BOOL VFDouList::AddTail(void * data, int size){
	plistNode pNode;
	if (!list) {
		return FALSE;
	}
	if ((pNode = (plistNode)malloc(sizeof(listNode))) == NULL) {
		return FALSE;
	}
	if ((pNode->data = malloc(size + 1)) == NULL) {
		free(pNode);
		return FALSE;
	}
	memset(pNode->data, 0, size + 1);
	memcpy(pNode->data, data, size);
	pNode->len = size;
	if (list->len == 0) {
		list->head = list->tail = pNode;
		pNode->prev = pNode->next = NULL;
	}else {
		pNode->prev = list->tail;
		pNode->next = NULL;
		list->tail->next = pNode;
		list->tail = pNode;
	}
	list->len++;
	return TRUE;
}

BOOL VFDouList::Insert(long index, void * data,int size, bool after = true) {
	plistNode pNode,CurrentNode;
	if (!list) {
		return FALSE;
	}
	if (index < 0) {
		index = (-index) - 1;
		CurrentNode = list->tail;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->prev;
		}
	}else {
		CurrentNode = list->head;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->next;
		}
	}
	if (!CurrentNode) {
		return FALSE;
	}
	if ((pNode = (plistNode)malloc(sizeof(listNode))) == NULL) {
		return FALSE;
	}
	if ((pNode->data = malloc(size + 1)) == NULL) {
		free(pNode);
		return FALSE;
	}
	memset(pNode->data, 0, size + 1);
	memcpy(pNode->data, data, size);
	pNode->len = size;
	if (after) {
		pNode->prev = CurrentNode;
		pNode->next = CurrentNode->next;
		if (list->tail == CurrentNode) {
			list->tail = pNode;
		}
	}else {
		pNode->next = CurrentNode;
		pNode->prev = CurrentNode->prev;
		if (list->head == CurrentNode) {
			list->head = pNode;
		}
	}
	if (pNode->prev != NULL) {
		pNode->prev->next = pNode;
	}
	if (pNode->next != NULL) {
		pNode->next->prev = pNode;
	}
	list->len++;
	return TRUE;
}

BOOL VFDouList::RemoveAt(long index){
	plistNode CurrentNode;
	if (!list) {
		return FALSE;
	}
	if (index < 0) {
		index = (-index) - 1;
		CurrentNode = list->tail;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->prev;
		}
	}else {
		CurrentNode = list->head;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->next;
		}
	}
	if (!CurrentNode) {
		return FALSE;
	}
	if (CurrentNode->prev) {
		CurrentNode->prev->next = CurrentNode->next;
	}else {
		list->head = CurrentNode->next;
	}
	if (CurrentNode->next) {
		CurrentNode->next->prev = CurrentNode->prev;
	}else {
		list->tail = CurrentNode->prev;
	}
	if (CurrentNode->data) {
		free(CurrentNode->data);
	}
	free(CurrentNode);
	list->len--;
	return TRUE;
}

ULONG VFDouList::Find(void * data,UINT size){
	plistNode CurrentNode; int index = 0;
	CurrentNode = list->head;
	while (CurrentNode != list->tail) {
		if (memcmp(CurrentNode->data, data, size) == 0) {
			return index;
		}
		index++;
		CurrentNode = CurrentNode->next;
	}
	return -1;
}

LPVOID VFDouList::GetAt(long index) {
	plistNode CurrentNode;
	if (index < 0) {
		index = (-index) - 1;
		CurrentNode = list->tail;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->prev;
		}
	}else {
		CurrentNode = list->head;
		while (index-- && CurrentNode) { 
			CurrentNode = CurrentNode->next;
		}
	}
	return CurrentNode->data;
}

UINT VFDouList::GetLengthAt(long index) {
	plistNode CurrentNode;
	if (index < 0) {
		index = (-index) - 1;
		CurrentNode = list->tail;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->prev;
		}
	}
	else {
		CurrentNode = list->head;
		while (index-- && CurrentNode) {
			CurrentNode = CurrentNode->next;
		}
	}
	return CurrentNode->len;
}

ULONG VFDouList::GetLength() {
	return list->len;
}

/*


void listRotate(list *list) {
	listNode *tail = list->tail;
	if (listLength(list) <= 1) return;
	list->tail = tail->prev;
	list->tail->next = NULL;
	list->head->prev = tail;
	tail->prev = NULL;
	tail->next = list->head;
	list->head = tail;
}

*/

