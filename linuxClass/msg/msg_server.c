#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSQKEY 51234

struct msgbuf {
	long mtype;
	char mtext[BUFSIZ];
};

int main(int argc, char **argv) {
	key_t key;
	int n, msqid;
	struct msgbuf mb;
