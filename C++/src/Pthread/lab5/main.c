#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

#define DIR_SIZE 1024
#define BUF_SIZE 1024

	
int  myCP(void *para) {
	//pthread_create multi-para passing 
	struct argv{        
		  char *argv_1;
        	  char *argv_2;    
	}; 	
	
	struct argv *arg;
	arg = (struct argv *)para; 


	unsigned char buf[BUF_SIZE];	
	int readRead;
	int srcFd;
	int desFd;

	//printf("source is %s\n", arg->argv_1);	
	//printf("des is %s\n", arg->argv_2);
	if((srcFd = open(arg->argv_1, O_RDONLY)) == -1) {
		printf("fatal %s not exist\n", arg->argv_1);
		return -1;
	}		

	int realRead;	
	if((desFd = open(arg->argv_2, O_RDWR | O_CREAT)) == -1) {
		printf("fatal %s not opened\n", arg->argv_2);
	}	

	while((realRead = read(srcFd, buf, BUF_SIZE)) > 0) {
		write(desFd, buf, realRead);	
	}	
	
	
	close(srcFd);
	close(desFd);
}


int myLS() {

	//get current directory
	char currentDir[DIR_SIZE];
	if(getcwd(currentDir, sizeof(currentDir)) == NULL) {
		printf("error find directory!\n");
		return -1;	
	}	

	//get the struct DIR
	DIR *Dirptr = NULL;	
	if((Dirptr = opendir(currentDir)) == NULL) {
		printf("error open directory!\n");
		return -1;
	}
	
		
	//get the struct dirent
	struct dirent *dirPtr;
	struct stat statPtr;
	while((dirPtr = readdir(Dirptr)) != NULL) {
		if(lstat(dirPtr->d_name, &statPtr) == -1) {
			printf("fatal, file resolving error!\n");	
			return -1;
		}	
		
		//pthread sub
		if(!S_ISDIR(statPtr.st_mode)) {
				
			struct argv {
				char *argv_1;					
				char *argv_2;
			};
			
			char src[DIR_SIZE];
			strcpy(src, currentDir);
			strcat(src, "/");
			char des[DIR_SIZE] = "/home/haotian/";
			struct argv arg;
	
			arg.argv_1 = strcat(src, dirPtr->d_name);
			//printf("source is %s\n", arg.argv_1);
			arg.argv_2 = strcat(des, dirPtr->d_name);
			//printf("destina is %s\n", arg.argv_2);
			pthread_t tid;
			pthread_create(&tid, NULL, (void *)myCP, &arg);				    pthread_join(tid, NULL);			
			
		}		

	}				

	closedir(Dirptr);

}
int main(int argc, char **argv) {

	pthread_t uit;
	pthread_create(&uit, NULL, (void *)myLS, NULL);
	pthread_join(uit, NULL);
	return 0;

}









