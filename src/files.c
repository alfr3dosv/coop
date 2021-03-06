#include "files.h"

struct Files_vt files_vt = {
	files_setThis,
	files_open,
	files_close,
	files_readInt, 
	*files_readString,
	files_next, 
	files_writeInt,
	*files_writeString,
	*files_newLine, 
};

Files *files_this;
#define this files_this

//init
Files *files_new()
{
	Files *files = malloc(sizeof(files));
	files->vt = &files_vt;
	return files;
}

void files_open(char *path) {
	this->file = fopen(path, "r+");
	if(this->file == NULL) {
        this->file = fopen(path,"w");
 	    $(this).writeInt(0);
 	    $(this).close();
        this->file = fopen(path, "r+");
    }
}

void files_close() {
	fclose(this->file);
}

void files_setThis(Files *self) 
{	
	this = self;
}

int files_readInt() 
{
	int n;
    fscanf(this->file,"%i", &n);
    return n;
}

char *files_readString(char *str) 
{
    do {
        fgets(str, MAXLINE, this->file);
    } while(strlen(str) < 2);
    char *newline = strchr(str,'\n');
    *newline = '\0';
}

void files_next() 
{
	char str[MAXLINE];
	fgets(str,MAXLINE, this->file);
}

int files_writeInt(int n) 
{
	fprintf(this->file,"%i",n);
	$(this).newLine();
}

char *files_writeString(char *str) 
{
	fputs(str,this->file);
	$(this).newLine();
}

char *files_newLine() 
{
	fputs("\n",this->file);
}

#undef this