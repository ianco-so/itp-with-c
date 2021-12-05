#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
	srand(10);
	for (int i = 0; i < 100; i++) {
		printf("%d ", rand() % 5);
	}
	return 0;
}