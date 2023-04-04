#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) 
{
	if (argc != 3) {
		printf("응애 그렇게 쓰는거 아닌뒙");
		return 0;
	}

	FILE* fread = open(argv[1], O_RDONLY);
	FILE* fwrite = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	
	if(fread == -1 && fwrite == -1) return 0;
	
	char buffer[BUFFER_SIZE];
	int bytes_read;

	while((bytes_read = read(fread, buffer, BUFFER_SIZE)) > 0) {
		write(fwrite, buffer, bytes_read);
	}	

	close(fread);
	close(fwrite);

	printf("다했다 임마");

	return 0;
}
