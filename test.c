#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

char filename[256][256];
int len = 0;
char chk[256];

int is_dir(char * filename)
{
	struct stat buf;
	int ret = stat(filename,&buf);

	if(0 == ret){
		if(buf.st_mode & S_IFDIR){
			return 0;
		}
		else{
			return 1;
		}
	}
	return -1;
}

int space = 0;

int delete_dir(char * dirname)
{
	space ++;
	int i;
	char chBuf[256];
	DIR * dir = NULL;
	struct dirent *ptr;
	int ret = 0;

	dir = opendir(dirname);
	if(NULL == dir){
		return -1;
	}
	while((ptr = readdir(dir)) != NULL){
		ret = strcmp(ptr->d_name, ".");
		if(0 == ret){
			continue;
		}
		ret = strcmp(ptr->d_name, "..");
		if(0 == ret){
			continue;
		}
		snprintf(chBuf, 256, "%s/%s", dirname, ptr->d_name);
		ret = is_dir(chBuf);
		if(0 == ret){
			for(i=0;i<space;i++){printf("\t");}
			printf("Delete dir %s\n", chBuf);
			ret = delete_dir(chBuf);
			if(0 != ret){
				return -1;
			}
		}
		else if(1 == ret){
			for(i=0;i<space;i++){printf("\t");}
			printf("Delete file %s\n", chBuf);
			ret = remove(chBuf);
			if(0 != ret){
				return -1;
			}
		}
	}
	(void)closedir(dir);

	ret = remove(dirname);
	if(0 != ret){
		return -1;
	}
	space --;
	return 0;
}

int trave_dir(char* path, char* extpath)
{
	DIR *d;
	struct dirent *file;
	struct stat sb;    
   
	if(!(d = opendir(path))){
		printf("error opendir %s!!!\n",path);
		return -1;
	}

	while((file = readdir(d)) != NULL){
		if(strncmp(file->d_name, ".", 1) == 0)
			continue;
		if(strncmp(file->d_name, "media", 5) == 0){
			printf("\n===================\n");
			printf("Skip directoty /data/media\n");
			continue;
		}
		printf("\n===================\n");
		strcpy(chk, "data/");
		strcat(chk, file->d_name);
		if(is_dir(chk) == 0){
			printf("Delete dir %s\n", chk);
			delete_dir(chk);
		}
		else{
			printf("Delete file %s\n", chk);
			remove(chk);
		}
	}

	closedir(d);
	return 0;
}
int main()
{
	trave_dir("data", "data/media");

	printf("\n");
	return 0;
}
