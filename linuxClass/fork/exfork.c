#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("L0\n");
	if(fork() != 0) {
		printf("L1\n");
		if(fork() != 0) {
			printf("L2\n");
		}
	}
	printf("BYE\n");
}
