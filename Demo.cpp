#include "VFDouList.h"
#include <stdio.h>

int main() {
	VFDouList DouList;
	DWORD i; int n = 1000;
	printf("Test For %d Data\n",n);
	i = GetTickCount();
	for (int i = 0; i < n; i++) {
		DouList.AddTail(&i, 4);
	}
	printf("\nMakeList Time:%ld ms\n", GetTickCount() - i);
	i = GetTickCount();
	for (int i = 0; i < n; i++) {
		DouList.RemoveAt(0);
	}
	printf("\nFree Time:%ld ms\n", GetTickCount() - i);
	system("pause");
	return 0;
}
