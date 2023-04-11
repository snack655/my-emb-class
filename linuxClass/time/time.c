#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	struct timeval tv;
	time_t t = time(NULL);
	struct tm *tm_info = localtime(&t);
	gettimeofday(&tv, NULL);
	time_t rawtime;
	char time_str[50];
	strftime(time_str, 50, "strftime : %a %b %d %H:%M:%S %Y", tm_info);
	time(&rawtime); // 현재의 시간 구하기
	printf("time : %u\n", (unsigned)rawtime); // 현재의 시간을 화면에 출력
	printf("gettimeofday : %ld/%ld\n", tv.tv_sec, tv.tv_usec);
	printf("ctime : %s", ctime(&t));
	printf("asctime : %s", asctime(tm_info));
	printf("%s\n", time_str);
	
	return 0;
}
