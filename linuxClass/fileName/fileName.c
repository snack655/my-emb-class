#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {
    DIR *dir;
    struct dirent *ent;
    char* dir_path = argv[1]; // 지정된 디렉토리 경로
    
    // 지정된 디렉토리 열기
    if ((dir = opendir(dir_path)) != NULL) {
        printf("%s 디렉토리의 파일과 디렉토리 목록:\n", dir_path);
        
        // 디렉토리에서 파일과 디렉토리 이름 출력
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir); // 디렉토리 닫기
    }
    else {
        printf("디렉토리를 열 수 없습니다.");
        return 1;
    }
    
    // 파일의 전체 경로 출력
    char file_name[] = "fileName.c";
    char file_path[strlen(dir_path) + strlen(file_name) + 2];
    strcpy(file_path, dir_path);
    strcat(file_path, "/");
    strcat(file_path, file_name);
    printf("\n%s 파일의 전체 경로:\n%s\n", file_name, file_path);
    
    return 0;
}

