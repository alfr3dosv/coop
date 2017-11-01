#ifndef PACIENTE_H
#define PACIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "StringList.h"
#include "../objects.h"
#include "../files.h"
#include "../console.h"

typedef struct {
    int id;
    char nombre[MAXLINE];
    Fecha fecha;
    StringList *alergias;
    int peso;
    int talla;
    bool estatus;
    struct Paciente_vt *vt;
} Paciente;


//global
extern int g_paciente_last_id;
extern Paciente *paciente_this;
extern int g_pacientes_elements;
extern int g_pacientes_size;
extern Paciente *g_pacientes[1000];

//init
Paciente *paciente_new();
//setters
void paciente_setThis(Paciente *this);
void paciente_setNombre(char *nombre);
void paciente_setId(int id);
void paciente_setPeso(int peso); 
void paciente_setTalla(int talla);
void paciente_setEstatus(bool estatus);
void paciente_setFecha(Fecha fecha);
void paciente_setAlergias(StringList *); 
Paciente *paciente_alta();

//getters
char *paciente_getNombre();
int paciente_getId(); 
int paciente_getPeso();
int paciente_getTalla();
bool paciente_getEstatus();
Fecha *paciente_getFecha();
void paciente_printf();
StringList *paciente_getAlergias(); 
//aux
void pacientes_openFile(char *);
void pacientes_saveFile(char *);
Paciente *pacientes_init();
Paciente *paciente_getById(int id);
Paciente *paciente_getByName(char *name);

//virtual table
struct Paciente_vt
{
    void (*setThis)(Paciente *);
    void (*setNombre)(char*);
    void (*setId)(int);
    void (*setPeso)(int);
    void (*setTalla)(int);
    void (*setEstatus)(bool);
    void (*setFecha)(Fecha fecha);
    void (*setAlergias)(StringList *); 
    Paciente *(*alta)();
    char *(*getNombre)();
    int (*getId)();
    int (*getPeso)();
    int (*getTalla)();
    bool (*getEstatus)();
    Fecha *(*getFecha)();
    StringList *(*getAlergias)(); 
    void (*printf)();
} static paciente_vt = {
    paciente_setThis,
    paciente_setNombre,
    paciente_setId,
    paciente_setPeso,
    paciente_setTalla,
    paciente_setEstatus,
    paciente_setFecha,
    paciente_setAlergias,
    paciente_alta,
    paciente_getNombre,
    paciente_getId,
    paciente_getPeso,
    paciente_getTalla,
    paciente_getEstatus,
    paciente_getFecha,
    paciente_getAlergias,
    paciente_printf
};

#endif