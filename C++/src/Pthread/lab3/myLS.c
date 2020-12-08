#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>


#define DIR_SIZE 1024


int main(int argc, char **argv) {


	char currentDir[DIR_SIZE];
	char tmp[DIR_SIZE];	
	char *currentPtr = NULL;
	DIR *Dirptr = NULL;
	if((currentPtr = getcwd(currentDir, sizeof(currentDir))) == NULL) {
		printf("can't find directory!\n");
		return -1;
	}else if((Dirptr = opendir(currentDir)) == NULL) {
		printf("fatal: Can't open directory!\n");
		return -1;
	}	
		
//	printf("the directory is %s\n", currentDir);

	
	struct dirent *dirPtr;
	struct stat statPtr;
	while((dirPtr = readdir(Dirptr)) != NULL) {

		if(lstat(dirPtr->d_name, &statPtr) == -1) {
			printf("fatal, file resolving error\n");
			return -1;
		}

/*		printf("%d ",statPtr->st_nlink );	
		//printf("%s\n", tmp);
		printf("%s\n ", strcat(tmp, dirPtr->d_name));
		printf("------------------------------------------------\n");
*/
			
		//type
		char *my_type;
		if(S_ISREG(statPtr.st_mode)) 	my_type = "-";
		else if(S_ISDIR(statPtr.st_mode))	my_type = "d";
		else if(S_ISCHR(statPtr.st_mode)) 	my_type = "c";
		else if(S_ISBLK(statPtr.st_mode)) 	my_type = "b";
		else if(S_ISFIFO(statPtr.st_mode)) 	my_type = "p";
		else if(S_ISSOCK(statPtr.st_mode)) 	my_type = "s";
		else if(S_ISLNK(statPtr.st_mode))	my_type = "l";
	
		//perm
		char *usr_Rperm;
		char *usr_Wperm;
		char *usr_Xperm;
		char *grp_Rperm;
		char *grp_Wperm;	
		char *grp_Xperm;
		char *otr_Rperm;
		char *otr_Wperm;
		char *otr_Xperm;
		if((S_IRUSR & statPtr.st_mode) == S_IRUSR) usr_Rperm = "r";
		else usr_Rperm = "-";

		if((S_IWUSR & statPtr.st_mode) == S_IWUSR)  usr_Wperm = "w"; 
		else usr_Wperm = "-";

		if((S_IXUSR & statPtr.st_mode) == S_IXUSR)  usr_Xperm = "x"; 
		else usr_Xperm = "-";
	
		if((S_IRGRP & statPtr.st_mode) == S_IRGRP)  grp_Rperm = "r"; 
		else grp_Rperm = "-";
		
		
		if((S_IWGRP & statPtr.st_mode) == S_IWGRP)  grp_Wperm = "w"; 
		else grp_Wperm = "-";

		if((S_IXGRP & statPtr.st_mode) == S_IXGRP)  grp_Xperm = "x"; 	
		else grp_Xperm = "-";

		if((S_IROTH & statPtr.st_mode) == S_IROTH)  otr_Rperm = "r";
		else otr_Rperm = "-";

		if((S_IWOTH & statPtr.st_mode)  == S_IWOTH)  otr_Wperm = "w"; 
		else otr_Wperm = "-";

		if((S_IXOTH & statPtr.st_mode) == S_IXOTH)   otr_Xperm = "x"; 
		else  otr_Xperm = "-";
	
		//user name 
		struct passwd *my_info;
		my_info = getpwuid(statPtr.st_uid);		
		
		//group  name
		struct group *group_info;
		group_info = getgrgid(statPtr.st_gid);

		
		//time printf	
		char *my_time;
		my_time = ctime(&statPtr.st_mtime);	
		my_time[strlen(my_time) - 1] = 0;	
		

		//printf output
		printf("%s", my_type);
		printf("%s", usr_Rperm);
		printf("%s", usr_Wperm);
		printf("%s", usr_Xperm);
		printf("%s", grp_Rperm);
		printf("%s", grp_Wperm);
		printf("%s", grp_Xperm);
		printf("%s", otr_Rperm);
		printf("%s", otr_Wperm);
		printf("%s  ", otr_Xperm);


		printf("%d ", statPtr.st_nlink);	
		printf("%s ", my_info->pw_name);
		printf("%s ", group_info->gr_name);
		printf("%u ", statPtr.st_size);
		printf("%s  ", my_time);
		printf("%s\n", dirPtr->d_name);
	}
	closedir(Dirptr);
	return 0;
}
