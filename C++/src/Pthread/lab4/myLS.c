#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>

#define DIR_SIZE 2014

int main(int atgv, char **argv) {

	char currentDir[DIR_SIZE];
	char *currentPtr = NULL;
	DIR *Dirptr = NULL;
	if((currentPtr = getcwd(currentDir, sizeof(currentDir))) == NULL) {
		printf("can't find directory\n");
		return -1;
	}else if((Dirptr = opendir(currentDir)) == NULL) {
		printf("fatal: Can't open directory\n");
		return -1;
	}

	struct dirent *dirPtr;
	struct stat statPtr;
	while((dirPtr = readdir(Dirptr)) != NULL) {
	
		if(lstat(dirPtr->d_name, &statPtr) == -1) {
			printf("fatal: file resovling error\n");
			return -1;
		}
		//source directory string operation	
		char src[DIR_SIZE];
		strcpy(src, currentDir);	
		strcat(src, "/");
		char des[DIR_SIZE] = "/home/haotian/";	
		//not a dir...	
		if(!S_ISDIR(statPtr.st_mode)) {
			int pid = fork();
			if(pid > 0) {
				waitpid(pid, NULL, WNOHANG);
			}else if(pid == 0) {
				/*
				Warning!!!
				using myCP in ./dir1/dir2/myCP
				this version of myCP is slightly different from the one of Lab2:
					since the mechanism of main's parameter passing didn't match execl's in this lab
					main: arg[1]  arg[2]
					execl arg[0] arg[1]
				so you have to recompile code of lab2	
				*/
				if(execl("./dir1/dir2/myCP", strcat(src, dirPtr->d_name), strcat(des, dirPtr->d_name), NULL) == -1) {
					printf("exe error!\n");
					return -1;
				}	
			}else if(pid < 0) {
				printf("error fork!\n");
				return -1;
			}


		}//if 
	}//while	
}//main
