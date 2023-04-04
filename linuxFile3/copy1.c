#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("사용법\n");
		printf("copy file [source filename] [out filename]\n");
		return 0;
	}

	// 1. line 으로 읽어와서 변수에 저장
	// 2. 읽은 거 새로운 파일에 쓰기
	
	FILE* fileRead = fopen(argv[1], "rb");
	FILE* fileWrite = fopen(argv[2], "wb");

	if (fileRead == NULL || fileWrite == NULL) return 0;

	char file;

	while(!feof(fileRead))
	{
		fread(&file, sizeof(char), 1, fileRead);
		fwrite(&file, sizeof(char), 1, fileWrite);
	}

	fclose(fileRead);
	fclose(fileWrite);

	return 0;
}

