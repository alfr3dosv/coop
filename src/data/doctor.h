#ifndef DOCTOR_H
#define DOCTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "StringList.h"
#include "../objects.h"
#include "../files.h"
#include "../console.h"

//doctor
typedef struct {
    int id;
    char nombre[MAXLINE];
    int especialidad;
    int turno;
    bool estatus;
    struct Doctor_vt *vt;
} Doctor;

//global
extern int g_doctor_last_id;
extern Doctor *doctor_this;
extern int g_doctores_elements;
extern int g_doctores_size;
extern Doctor *g_doctores[1000];

//init
Doctor *doctor_new();
//setters
void doctor_setThis(Doctor *);
void doctor_setNombre(char *nombre); 
void doctor_setId(int id); 
void doctor_setTurno(int turno); 
void doctor_setEstatus(bool estatus); 
void doctor_setEspecialidad(int especialidad); 
Doctor *doctor_alta(); 

//getters
char *doctor_getNombre();
int doctor_getId();
int doctor_getTurno();
bool doctor_getEstatus();
int doctor_getEspecialidad();
void doctor_printf(); 

//aux
void doctores_openFile(char *);
void doctores_saveFile(char *);
Doctor *doctores_init(); 
Doctor *doctor_getById(int id); 
Doctor *doctor_getByName(char *name); 

struct Doctor_vt {
    void (*setThis)(Doctor *);
    void (*setNombre)(char *nombre); 
    void (*setId)(int id); 
    void (*setTurno)(int turno); 
    void (*setEstatus)(bool estatus); 
    void (*setEspecialidad)(int especialidad); 
    //getters
    char *(*getNombre)();
    int (*getId)();
    int (*getTurno)();
    bool (*getEstatus)();
    int (*getEspecialidad)();
    Doctor *(*alta)(); 
    void (*printf)(); 
} static doctor_vt = {
    //setters
    doctor_setThis,
    doctor_setNombre,
    doctor_setId,
    doctor_setTurno,
    doctor_setEstatus,
    doctor_setEspecialidad,
    //getters
    doctor_getNombre,
    doctor_getId,
    doctor_getTurno,
    doctor_getEstatus,
    doctor_getEspecialidad,
    doctor_alta,
    doctor_printf,
};

#endif