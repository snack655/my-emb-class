#include <stdio.h>
#include <string.h>

int main(int ac, char *av[]) {
	char buff[2048 + 1];

	memset(buff, 0x00, sizeof(buff));
	scanf("%s", buff);

	printf("INPUT: %s\n", buff);

	return 1;
}
