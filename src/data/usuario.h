#ifndef USUARIO_H
#define USUARIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "StringList.h"
#include "../objects.h"
#include "../files.h"
#include "../console.h"

typedef struct
{
    int id;
    char usuario[MAXLINE];
    char password[MAXLINE];
    char nombre[MAXLINE];
    int estatus;
    int tipo;
    int idDoctor;
} Usuario;

//global
extern int g_usuarios_elements;
extern int g_usuarios_size;
extern Usuario *g_usuarios[];

void usuarios_init(void);
void usuarios_openFile(char *path);

#endif