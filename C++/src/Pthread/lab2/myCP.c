#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#define BUF_SIZE 1024

extern errorno;


int main(int argc, char **argv) {

	char *des;
	char *src;

	src = argv[1];
	des = argv[2];
		
	/*
	Warning!!!
		The following code is for lab4
		src = argv[0];
		des = arg[1];
	*/	
	int srcFd;
	int desFd;
	
	//buf 	
	unsigned char buf[BUF_SIZE];
	int realRead;
 
//	printf("argv[0] is %s\n", src);
//	printf("argv[1] is %s\n", des);

	if((srcFd = open(src, O_RDONLY)) == -1) {
		printf("fatal! %s not exists\n", src);
		return -1;
	}

	if((desFd = open(des, O_RDWR | O_CREAT)) == -1) {
		printf("fatal! %s can't be opened\n", des);	
		return -1;
	}

	
	while((realRead = read(srcFd, buf, BUF_SIZE)) > 0) {
		write(desFd, buf, realRead);
	}		
	
		
	//printf(strerror(errno));	
	printf("\n");	
	close(srcFd);
	close(desFd);		
}
