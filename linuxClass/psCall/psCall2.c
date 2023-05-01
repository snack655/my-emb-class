#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int ac, char *av[]) {
	FILE *r_fp;
	char buff[2048 + 1];
	int rtn = 0;

	memset(buff, 0x00, sizeof(buff));
	r_fp = popen("pwd", "r");
	if(!r_fp) {
		printf("popen ERROR (%d)\n", errno);
		return -1;
	}

	rtn = fread(buff, sizeof(char), sizeof(buff), r_fp);
	if(rtn > 0)
		printf("READ: %s\n", buff);
	pclose(r_fp);

	return 1;
}
