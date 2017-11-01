#ifndef FILES_H
#define FILES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../objects.h"
#include "../data/data.h"

typedef struct 
{
	FILE *file;
	struct Files_vt *vt;
} Files;

Files *files_new();
void files_setThis(Files *);
void files_open(char *);
void files_close();
//read
int files_readInt(); 
char *files_readString(char *); 
void files_next(); 
//write
int files_writeInt(int); 
char *files_writeString(char *); 
char *files_newLine(); 

struct Files_vt {
	void (*setThis)(Files *);
	void (*open)(char *);
	void (*close)();
	int (*readInt)(); 
	char *(*readString)(char *); 
	void (*next)(); 
	int (*writeInt)(int); 
	char *(*writeString)(char *); 
	char *(*newLine)(); 	
};

extern struct Files_vt files_vt;

#endif
