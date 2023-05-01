#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int ac, char *av[]) {
	FILE *w_fp;
	char buff[2048 + 1];
	int rtn = 0;

	w_fp = popen("./psCall3_2", "w");
	if(!w_fp) {
		printf("popen ERROR (%d)\n", errno);
		return -1;
	}

	memset(buff, 0x00, sizeof(buff));
	sprintf(buff, "Thank_you_for_reading!");

	fwrite(buff, sizeof(char), sizeof(buff), w_fp);

	pclose(w_fp);

	return 1;
}
