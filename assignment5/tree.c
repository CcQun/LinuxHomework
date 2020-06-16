#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

char *vline = "│   ";
char *bnull = "    ";
char *middle = "├── ";
char *last = "└── ";
int a = 0,d = 0;

void tree(char *ph,char *pf);
int is_dir(char *path);
int is_file(char *path);
char **file_array(char *path,int *length);
char *path_cat(char *father,char *son);
int is_exe(char *path);

int main(int argc,char **argv){
	char *path = ".";
	char *option = " ";
	
	if(argc == 2){
		path = argv[1];
	}else if(argc == 3){
		path = argv[1];
		option = argv[2];
	}
	
	if(strcmp(option,"-a") == 0){
		a = 1;
	}
	if(strcmp(option,"-d") == 0){
		d = 1;
	}

	
	char *prefix="";
	
	printf("%s\n",path);


	tree(path,prefix);

	return 0;
}

void tree(char *ph,char *pf){
	if(is_dir(ph)){
		chdir(ph);

		char where[200];
		getcwd(where,sizeof(where));


		char **ft;
		int total = 0;
		ft = file_array(where,&total);

		char **flist = (char **)malloc(total * sizeof(char*));
		int k = 0;
		for(int k = 0;k < total;k++){
			flist[k] = ft[k];
		}


		int i = 0;	
		for(i = 0;i < total;i++){
			if(is_file(flist[i])){
				if(i == total - 1){
					if(is_exe(flist[i])){
						printf("%s%s\033[1;32m%s\n\033[0m",pf,last,flist[i]);
					}else{
						printf("%s%s%s\n",pf,last,flist[i]);
					}	
				}else{
					if(is_exe(flist[i])){
						printf("%s%s\033[1;32m%s\n\033[0m",pf,middle,flist[i]);
					}else{
						printf("%s%s%s\n",pf,middle,flist[i]);
					}       
				}
			}else if(is_dir(flist[i])){
				if(i == total - 1){
					char *flisti = (char *)malloc(sizeof(char) * 50);
					strcpy(flisti,flist[i]);

					printf("%s%s\033[34m%s\n\033[0m",pf,last,flisti);

				
					char *pre = (char *)malloc(sizeof(char) * 8000);
					strcpy(pre,pf);
					strcat(pre,bnull);


					char *son_path = (char *)malloc(sizeof(char) * 100);
					strcpy(son_path,where);
					strcat(son_path,"/");
					strcat(son_path,flisti);

					tree(son_path,pre);

					free(flisti);
					free(pre);
					free(son_path);

					chdir(where);
				}else{
					char *flisti = (char *)malloc(sizeof(char) * 50);
					strcpy(flisti,flist[i]);
					printf("%s%s\033[34m%s\n\033[0m",pf,middle,flisti);

					char *pre = (char *)malloc(sizeof(char) * 8000);
					strcpy(pre,pf);
					strcat(pre,vline);
					
					char *son_path = (char *)malloc(sizeof(char) * 100);
					strcpy(son_path,where);
					strcat(son_path,"/");
					strcat(son_path,flist[i]);

					tree(son_path,pre);
					
					free(flisti);
                                        free(pre);
                                        free(son_path);
					
					chdir(where);

				}
			}
		}
		free(flist);
		free(ft);
	}
}

int is_dir(char *path){
	struct stat s_buf;
	stat(path,&s_buf);
	return S_ISDIR(s_buf.st_mode);
}

int is_file(char *path){
	struct stat s_buf;
	stat(path,&s_buf);
	return S_ISREG(s_buf.st_mode);
}

int is_exe(char *path){
	struct stat s_buf;
        stat(path,&s_buf);
	if (S_ISDIR(s_buf.st_mode))
		return 0;
	else if (s_buf.st_mode&S_IEXEC)
		return 1;
	else
		return 0;
}

char **file_array(char *path,int *length){
	char **fa = (char **)malloc(sizeof(char *) * 1);;
	int i = 0;
	DIR *dir = NULL;
	struct dirent *entry;
	if((dir = opendir(path))==NULL){
		printf("opendir failed!");
		return NULL;
	}else{
		while(entry=readdir(dir)){
			char *fn = entry->d_name;

			if((strcmp(fn,".") != 0) && (strcmp(fn,"..") != 0)){

				if(a == 1){ 
					fa = (char **)realloc(fa,(i + 1) * sizeof(char *));
					fa[i] = fn;
					i++;
				}else if((a == 0) && (fn[0] != '.')){
					if((d == 1) && (is_dir(fn))){

						fa = (char **)realloc(fa,(i + 1) * sizeof(char *));
						fa[i] = fn;
						i++;
					}else if(d == 0){
						fa = (char **)realloc(fa,(i + 1) * sizeof(char *));
						fa[i] = fn;
						i++;
					}
				}
			}
		}
		closedir(dir);		
	       	*length = i;	
		return fa;
	}		
}
